package runtime

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// This file adapts spore-recomp's own runtime report into the overlay schema.
//
// It is a ONE-WAY, READ-ONLY adapter. It reads a producer artifact, it never
// asks spore-recomp to change, it never writes into that repository, and it
// introduces no OpenSpore dependency on the spore-recomp side: spore-recomp can
// stop emitting these reports tomorrow and nothing here breaks, and it can start
// emitting a different shape without knowing this adapter exists.
//
// Everything below is a PROJECTION. Facts are copied with the producer's own
// vocabulary preserved (its event classes, its import module/symbol spellings,
// its final register dump). The adapter derives exactly one thing, and it is
// purely mechanical: the SET of addresses the report mentions, with how many
// observed transfer edges each one was involved in.
//
// It derives nothing about ABI, return width, vtable slot or function identity.
// It does not even decide which addresses are function entries: canonical_va is
// left null on every entry, because that question belongs to OpenSpore's
// canonical-identity rule, and an adapter that answered it would be creating a
// second identity scheme.

// RecompReport is the subset of a spore-recomp startup-recovery report the
// overlay needs.
//
// Unknown fields are IGNORED, not refused. The producer owns this schema and
// will keep adding fields to it; an adapter that rejected an unknown field would
// turn a harmless producer improvement into a broken ingestion path. The unknown
// *schema id* is still refused (see RecompSupportedSchemas), because that one
// means the fields an adapter reads may have MOVED, which would decode into
// plausible-looking zeroes.
type RecompReport struct {
	SchemaVersion string `json:"schema_version"`
	EntryVA       string `json:"entry_va"`
	Outcome       string `json:"outcome"`
	OutcomeDetail string `json:"outcome_detail"`
	FinalEIP      string `json:"final_eip"`
	FinalKind     string `json:"final_kind"`
	Steps         int    `json:"steps"`
	PeakCallDepth int    `json:"peak_call_depth"`
	CallEdgeCount int    `json:"call_edge_count"`
	Image         struct {
		Loaded      bool   `json:"loaded"`
		Error       string `json:"error"`
		BinarySHA   string `json:"binary_sha256"`
		ImageBase   string `json:"image_base"`
		EntryRVA    string `json:"entry_rva"`
		SizeOfImage int64  `json:"size_of_image"`
		Sections    []struct {
			Name            string `json:"name"`
			VA              string `json:"va"`
			RVA             string `json:"rva"`
			VirtualSize     int64  `json:"virtual_size"`
			SizeOfRawData   int64  `json:"size_of_raw_data"`
			MappedBytes     int64  `json:"mapped_bytes"`
			Characteristics string `json:"characteristics"`
		} `json:"sections"`
	} `json:"image"`
	Registers map[string]string `json:"registers"`
	Imports   struct {
		Bindings       int      `json:"bindings"`
		Modelled       int      `json:"modelled"`
		Unresolved     int      `json:"unresolved"`
		IATCellsWrite  int      `json:"iat_cells_written"`
		ModelledTokens []string `json:"modelled_tokens"`
		IATCellChecks  []struct {
			SlotVA      string `json:"slot_va"`
			LoadedValue string `json:"loaded_value"`
			Module      string `json:"module"`
			Symbol      string `json:"symbol"`
			Bound       bool   `json:"bound"`
		} `json:"iat_cell_checks"`
	} `json:"imports"`
	CallEdges []struct {
		CallsiteVA    string `json:"callsite_va"`
		TargetVA      string `json:"target_va"`
		Count         int    `json:"count"`
		FirstSequence int64  `json:"first_sequence"`
		MinDepth      int    `json:"min_depth"`
		MaxDepth      int    `json:"max_depth"`
	} `json:"call_edges"`
	Events []struct {
		Sequence         int64  `json:"sequence"`
		Class            string `json:"class"`
		CallerFunctionVA string `json:"caller_function_va"`
		CallsiteVA       string `json:"callsite_va"`
		TargetVA         string `json:"target_va"`
		ReturnAddress    string `json:"return_address"`
		CallDepth        int    `json:"call_depth"`
		Detail           string `json:"detail"`
	} `json:"events"`
}

// RecompSupportedSchemas lists the producer report schema ids this adapter has
// been written against. An unknown id is refused rather than read.
var RecompSupportedSchemas = []string{"1.1.0"}

// Producer identity recorded in every converted overlay.
const (
	RecompProject    = "spore-recomp"
	RecompReportName = "spore-recomp startup recovery report"
	// RecompArtifactPrefix is the producer repo-relative directory reports live
	// under. It is used to derive a portable artifact identifier, never a
	// filesystem path.
	RecompArtifactPrefix = "work/reports"
)

// RecompOptions configure one conversion.
type RecompOptions struct {
	// Artifact is the PORTABLE identifier recorded in provenance, such as
	// "work/reports/startup-recovery14.json". It is required: the report's
	// filesystem path is never embedded, and defaulting one would silently
	// attribute one producer's observations to another report.
	Artifact string
	// Version overrides the recorded producer version. When empty the report's
	// own schema_version is recorded.
	Version string
}

// RecompResult reports what a conversion produced, so a caller can print the
// facts a reviewer needs before trusting the file.
type RecompResult struct {
	Result      Result
	Report      *RecompReport
	Entries     []*Entry
	Metadata    Metadata
	Addresses   int
	Reached     int
	RuntimeOnly int
	Unresolved  int
	Imports     int
	Notes       []string
}

// DefaultRecompArtifact derives the portable artifact identifier from a report
// path.
//
// It only does so when the path actually contains a "reports" component, because
// that is what makes "work/reports/<name>" the right repo-relative identifier.
// For any other path the caller must state the identifier explicitly: guessing
// would produce an identifier that looks portable and is not.
func DefaultRecompArtifact(reportPath string) (string, bool) {
	dir, file := filepath.Split(filepath.ToSlash(reportPath))
	if file == "" {
		return "", false
	}
	for _, part := range strings.Split(strings.TrimSuffix(dir, "/"), "/") {
		if part == "reports" {
			return RecompArtifactPrefix + "/" + file, true
		}
	}
	return "", false
}

// ConvertRecomp reads a spore-recomp runtime report and returns the overlay it
// projects to. Nothing is written; the caller decides the destination.
//
// requireSHA is the binary identity the caller insists on. Empty accepts
// whatever the report claims, which is only appropriate when building a fixture.
// A report with no SHA-256 is refused outright: an overlay with no binary
// identity cannot be joined to anything and would be a floating file.
func ConvertRecomp(path string, requireSHA string, opts RecompOptions) (*RecompResult, error) {
	if opts.Artifact == "" {
		return nil, fmt.Errorf("a portable artifact identifier is required: the report's filesystem path (%q) is not portable and must not be embedded in an overlay", path)
	}
	raw, err := os.ReadFile(path)
	if err != nil {
		if os.IsNotExist(err) {
			return nil, fmt.Errorf("%w: %s", ErrMissing, path)
		}
		return nil, err
	}
	var rep RecompReport
	if err := json.Unmarshal(raw, &rep); err != nil {
		return nil, fmt.Errorf("%w: %s: %v", ErrCorrupt, path, err)
	}
	if !supportedRecompSchema(rep.SchemaVersion) {
		return nil, fmt.Errorf("%w: %s declares producer schema %q; this adapter implements %s",
			ErrSchema, path, rep.SchemaVersion, strings.Join(RecompSupportedSchemas, ", "))
	}
	if rep.Image.BinarySHA == "" {
		return nil, fmt.Errorf("%w: %s: producer states no binary_sha256", ErrCorrupt, path)
	}
	if err := checkHexDigest(rep.Image.BinarySHA); err != nil {
		return nil, fmt.Errorf("%w: %s: binary_sha256: %v", ErrCorrupt, path, err)
	}
	if requireSHA != "" && rep.Image.BinarySHA != requireSHA {
		return nil, fmt.Errorf("%w: producer report describes %s, caller requires %s",
			ErrBinaryMismatch, shortSHA(rep.Image.BinarySHA), shortSHA(requireSHA))
	}
	if _, ok := imageBaseOf(rep.Image.ImageBase); !ok {
		return nil, fmt.Errorf("%w: %s: producer states no usable image base (%q)", ErrCorrupt, path, rep.Image.ImageBase)
	}

	version := opts.Version
	if version == "" {
		version = rep.SchemaVersion
	}
	prov := ProvenanceEntry{SourceClass: ProvenanceSourceRuntime, Producer: RecompProject, Artifact: opts.Artifact}
	entries, notes := recompEntries(&rep, prov)

	res := &RecompResult{
		Report:  &rep,
		Entries: entries,
		Metadata: Metadata{
			Binary: semantic.BinaryIdentity{
				SHA256:       rep.Image.BinarySHA,
				ImageBase:    rep.Image.ImageBase,
				Architecture: "x86:LE:32",
				Program:      "SporeApp.exe",
			},
			Producer: Producer{
				Project:      RecompProject,
				Name:         RecompReportName,
				Version:      version,
				Artifact:     opts.Artifact,
				SourceSchema: "spore-recomp-runtime-report-" + rep.SchemaVersion,
			},
		},
		Addresses: len(entries),
		Notes:     notes,
	}
	for _, e := range entries {
		if e.Reached == TriTrue {
			res.Reached++
		}
		if e.CanonicalVA == nil {
			res.RuntimeOnly++
		}
		for _, t := range e.RuntimeTargets {
			if t.Unresolved == TriTrue {
				res.Unresolved++
			}
		}
		res.Imports += len(e.RuntimeImports)
	}
	return res, nil
}

func supportedRecompSchema(id string) bool {
	for _, s := range RecompSupportedSchemas {
		if id == s {
			return true
		}
	}
	return false
}

// recompEntries projects a report into overlay entries.
//
// The address set comes from the four places where the report asserts something
// about an address:
//
//	call_edges[].callsite_va    -- a transfer left this address
//	call_edges[].target_va      -- a transfer arrived at this address
//	events[]                    -- a condition was observed at these addresses
//	entry_va / final_eip        -- execution began / stopped here
//
// Reached is set only where the report actually establishes it: at the declared
// entry point, at a target named by an event, and nowhere else. An address that
// appears only as a callsite was certainly passed through, but "entered" is a
// stronger claim, so the flag stays null and entry_count speaks.
func recompEntries(rep *RecompReport, prov ProvenanceEntry) ([]*Entry, []string) {
	type acc struct {
		e       *Entry
		edgeSum int
	}
	byAddr := map[uint32]*acc{}
	var order []uint32

	get := func(raw string) *acc {
		addr, ok := recompAddr(raw)
		if !ok {
			return nil
		}
		a, seen := byAddr[addr]
		if !seen {
			e := NewEntry(semantic.Addr(addr).String())
			e.Provenance = []ProvenanceEntry{prov}
			a = &acc{e: e}
			byAddr[addr] = a
			order = append(order, addr)
		}
		return a
	}

	notes := []string{}

	for _, edge := range rep.CallEdges {
		target := get(edge.TargetVA)
		if target == nil {
			notes = append(notes, fmt.Sprintf("call edge from %s names target %q, which is not a 32-bit address; that edge was dropped", edge.CallsiteVA, edge.TargetVA))
			continue
		}
		callsite := get(edge.CallsiteVA)
		// Direction matters. A call edge is a transfer FROM the callsite address
		// TO the target address, so the target belongs in the CALLER's
		// runtime_targets and the callsite in the TARGET's runtime_callers.
		// Getting this backwards would make every address appear to call itself.
		if callsite == nil {
			notes = append(notes, fmt.Sprintf("call edge to %s names callsite %q, which is not a 32-bit address; that edge was dropped", edge.TargetVA, edge.CallsiteVA))
			continue
		}
		// The producer's call_edges table measures direct transfers. It states
		// nothing about dispatch kind, so indirect stays null: "we did not
		// establish this", never "false".
		callsite.e.RuntimeTargets = append(callsite.e.RuntimeTargets, RuntimeTarget{
			TargetVA:       semantic.Addr(recompMust(edge.TargetVA)).String(),
			Indirect:       TriNull,
			Unresolved:     TriNull,
			Classification: "direct_call",
		})
		callsite.e.Observations = append(callsite.e.Observations, Observation{
			Kind:       ObsCall,
			Sequence:   int64Ptr(edge.FirstSequence),
			CallsiteVA: Ptr(semantic.Addr(recompMust(edge.CallsiteVA)).String()),
			TargetVA:   Ptr(semantic.Addr(recompMust(edge.TargetVA)).String()),
			CallDepth:  nonNegPtr(edge.MinDepth),
			Count:      nonNegPtr(edge.Count),
		})
		target.e.RuntimeCallers = append(target.e.RuntimeCallers, RuntimeCaller{
			CallsiteVA: semantic.Addr(recompMust(edge.CallsiteVA)).String(),
			Count:      nonNegPtr(edge.Count),
			MinDepth:   nonNegPtr(edge.MinDepth),
			MaxDepth:   nonNegPtr(edge.MaxDepth),
		})
		if edge.Count > 0 {
			callsite.edgeSum += edge.Count
			target.edgeSum += edge.Count
		}
		// The edge's depth is the stack depth at which the transfer happened, so
		// it describes the CALLER's position, not the callee's.
		if edge.MaxDepth > 0 {
			callsite.e.MaxCallDepth = maxPtr(callsite.e.MaxCallDepth, edge.MaxDepth)
		}
	}

	for _, ev := range rep.Events {
		host := get(ev.CallerFunctionVA)
		if host == nil {
			host = get(ev.CallsiteVA)
		}
		if host == nil {
			continue
		}
		if ev.TargetVA != "" {
			host.e.Observations = append(host.e.Observations, Observation{
				Kind:       ObsIndirectCall,
				Sequence:   int64Ptr(ev.Sequence),
				EIP:        optVA(ev.CallsiteVA),
				CallsiteVA: optVA(ev.CallsiteVA),
				TargetVA:   optVA(ev.TargetVA),
				// UNRESOLVED_TARGET is the producer's own label for a transfer to
				// a guest address it had no recovered code for. That label IS the
				// evidence of an unresolved dispatch, and it is the only class
				// the adapter reads as "indirect"; everything else stays null.
				Indirect:  indirectFromClass(ev.Class),
				CallDepth: nonNegPtr(ev.CallDepth),
				Detail:    ev.Detail,
			})
			host.e.RuntimeTargets = append(host.e.RuntimeTargets, RuntimeTarget{
				TargetVA:       semantic.Addr(recompMust(ev.TargetVA)).String(),
				Indirect:       indirectFromClass(ev.Class),
				Unresolved:     unresolvedFromClass(ev.Class),
				Classification: ev.Class,
			})
			if tv := get(ev.TargetVA); tv != nil {
				// The event names both the containing caller function and the
				// callsite, which is strictly more than a call_edges row carries.
				// Recording it as a caller edge preserves that.
				if csv, ok := recompAddr(ev.CallsiteVA); ok {
					tv.e.RuntimeCallers = append(tv.e.RuntimeCallers, RuntimeCaller{
						CallerFunctionVA: optVA(ev.CallerFunctionVA),
						CallsiteVA:       semantic.Addr(csv).String(),
						Count:            Ptr(1),
						MinDepth:         nonNegPtr(ev.CallDepth),
						MaxDepth:         nonNegPtr(ev.CallDepth),
					})
				}
				tv.e.Reached = TriTrue
				tv.e.Observations = append(tv.e.Observations, Observation{
					Kind:      ObsEntry,
					Sequence:  int64Ptr(ev.Sequence),
					EIP:       optVA(ev.TargetVA),
					CallDepth: nonNegPtr(ev.CallDepth),
					Detail:    "arrival recorded by producer event " + ev.Class,
				})
				// The producer's event is an observation of ARRIVAL, which is a
				// stronger statement than a transfer-graph count. It is recorded
				// as one entry so the number means "at least once", and the
				// event's own sequence and depth carry the precision.
				if tv.edgeSum == 0 {
					tv.edgeSum = 1
				}
				tv.e.MaxCallDepth = maxPtr(tv.e.MaxCallDepth, ev.CallDepth)
			}
		}
		if ev.ReturnAddress != "" {
			host.e.Observations = append(host.e.Observations, Observation{
				Kind:          ObsReturn,
				Sequence:      int64Ptr(ev.Sequence),
				ReturnAddress: optVA(ev.ReturnAddress),
				CallDepth:     nonNegPtr(ev.CallDepth),
				Detail:        ev.Detail,
			})
		}
	}

	if e := get(rep.EntryVA); e != nil {
		e.e.Reached = TriTrue
		e.e.Observations = append(e.e.Observations, Observation{
			Kind:   ObsEntry,
			EIP:    Ptr(e.e.RequestedVA),
			Detail: "processor entry point for this run, as declared by the producer report",
		})
	}
	if e := get(rep.FinalEIP); e != nil {
		e.e.Observations = append(e.e.Observations, Observation{
			Kind: ObsEntry,
			EIP:  Ptr(e.e.RequestedVA),
			Detail: fmt.Sprintf("last executed address before the producer stopped (%s: %s -- %s)",
				rep.Outcome, rep.FinalKind, rep.OutcomeDetail),
		})
		// The producer's register map is a single CPU sample at the stop point,
		// not an entry/return pair. Each register is therefore reported as its
		// own register observation, and NO stack_delta_bytes is emitted: a delta
		// derived from one sample would read as "the callee restored the stack",
		// which nothing observed.
		for _, name := range registerOrder {
			if v, ok := rep.Registers[name]; ok {
				e.e.Observations = append(e.e.Observations, Observation{
					Kind:          ObsRegister,
					Register:      Ptr(name),
					RegisterValue: optVA(v),
					Detail:        "register state at the producer's stop point; not an entry or return state",
				})
			}
		}
	}

	for _, cell := range rep.Imports.IATCellChecks {
		// An IAT cell check is a statement about the import TABLE, not about a
		// function. It is attached to the slot address and says exactly that.
		// ReachedCount stays null, because the producer did not establish that
		// the import was ever called.
		slot := get(cell.SlotVA)
		if slot == nil {
			continue
		}
		bound := TriFalse
		if cell.Bound {
			bound = TriTrue
		}
		slot.e.RuntimeImports = append(slot.e.RuntimeImports, RuntimeImportRef{
			Module:      cell.Module,
			Symbol:      cell.Symbol,
			SlotVA:      Ptr(slot.e.RequestedVA),
			LoadedValue: optVA(cell.LoadedValue),
			Bound:       bound,
		})
		slot.e.Observations = append(slot.e.Observations, Observation{
			Kind:    ObsImport,
			Address: Ptr(slot.e.RequestedVA),
			SlotVA:  Ptr(slot.e.RequestedVA),
			Module:  Ptr(cell.Module),
			Symbol:  Ptr(cell.Symbol),
			Detail:  "IAT cell contents as written by the producer's loader emulation; this states what the cell holds, not that the import was called",
		})
	}

	// The producer's final_eip is the address execution stopped at, which makes
	// it a genuine runtime CALLER of whatever it was about to enter. Recording it
	// as such is the one caller fact the report carries outside the events list.
	out := make([]*Entry, 0, len(order))
	for _, addr := range order {
		a := byAddr[addr]
		if a.edgeSum > 0 {
			a.e.EntryCount = Ptr(a.edgeSum)
		}
		out = append(out, a.e)
	}
	if len(rep.CallEdges) > 0 {
		notes = append(notes, "entry_count is the number of observed transfer edges touching an address, taken from the producer's call_edges table; it is not an instruction-retirement count and it does not distinguish entry from pass-through")
	}
	if len(rep.Imports.IATCellChecks) > 0 {
		notes = append(notes, "import observations record IAT cell contents written by the producer's loader emulation; reached_count is null because the report does not establish that an import was called")
	}
	notes = append(notes, "register observations come from a single CPU sample at the producer's stop point, so no stack delta and no return register are reported")
	return out, notes
}

// registerOrder is the fixed order the producer's register map is projected in,
// so the output does not depend on Go's map iteration order.
var registerOrder = []string{"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp", "eip", "eflags"}

func recompAddr(raw string) (uint32, bool) {
	if strings.TrimSpace(raw) == "" {
		return 0, false
	}
	addr, err := semantic.ParseAddr(raw, 0)
	if err != nil {
		return 0, false
	}
	return uint32(addr), true
}

// recompMust is recompAddr for a value the caller has already established
// parses. A failure is a programming error in the adapter, and returning 0 makes
// it visible as address 0x00000000 rather than as a silently dropped field.
func recompMust(raw string) uint32 {
	addr, ok := recompAddr(raw)
	if !ok {
		return 0
	}
	return addr
}

func optVA(raw string) *string {
	addr, ok := recompAddr(raw)
	if !ok {
		return nil
	}
	s := semantic.Addr(addr).String()
	return &s
}

func nonNegPtr(v int) *int {
	if v < 0 {
		return nil
	}
	return &v
}

func int64Ptr(v int64) *int64 {
	if v <= 0 {
		return nil
	}
	return &v
}

func maxPtr(cur *int, v int) *int {
	if v < 0 {
		return cur
	}
	if cur == nil || v > *cur {
		return &v
	}
	return cur
}

// indirectFromClass maps a producer event class onto the tri-state. Only
// UNRESOLVED_TARGET yields "true", because that is the producer's own label for
// a transfer to a guest address with no recovered code. Every other class yields
// null.
func indirectFromClass(class string) semantic.TriBool {
	if class == "UNRESOLVED_TARGET" {
		return TriTrue
	}
	return TriNull
}

func unresolvedFromClass(class string) semantic.TriBool {
	if class == "UNRESOLVED_TARGET" {
		return TriTrue
	}
	return TriNull
}

func imageBaseOf(raw string) (semantic.Addr, bool) {
	return semantic.BinaryIdentity{ImageBase: raw}.ImageBaseAddr()
}
