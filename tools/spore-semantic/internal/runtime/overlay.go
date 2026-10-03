package runtime

import (
	"bufio"
	"bytes"
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// Errors a load can report. Callers map these onto stable exit codes; none of
// them is ever reported as an empty overlay, because an empty overlay is
// indistinguishable from "the producer observed nothing".
var (
	// ErrMissing means no overlay file was found.
	ErrMissing = errors.New("runtime overlay not found")
	// ErrSchema means the file is a readable document of a contract this build
	// does not implement: a different schema id, an unknown observation kind, or
	// a field this build has never heard of.
	ErrSchema = errors.New("unsupported overlay schema")
	// ErrBinaryMismatch means the overlay describes a different binary than the
	// caller required. This is the load-bearing refusal: runtime observations of
	// one binary say nothing about another.
	ErrBinaryMismatch = errors.New("binary mismatch")
	// ErrImageBaseMismatch means the overlay's image base disagrees with the
	// caller's. It is separate from a binary mismatch because a producer can
	// carry the right SHA-256 and still disagree about where the image loads,
	// which makes every address in the overlay mean something different.
	ErrImageBaseMismatch = errors.New("image base mismatch")
	// ErrCorrupt means the file is not a readable overlay: bad JSON, a truncated
	// line, out-of-order records, a duplicate address, a negative count, an
	// internally contradictory tri-state, or a content digest that does not
	// match.
	ErrCorrupt = errors.New("corrupted runtime overlay")
)

// Overlay is a loaded runtime overlay.
type Overlay struct {
	Path     string
	Metadata *Metadata
	// Entries maps requested VA to its record.
	Entries map[uint32]*Entry
	// Order lists requested VAs ascending, which is the file's record order.
	Order []uint32
	// byCanonical indexes entries by the canonical VA their producer claimed, so
	// a lookup on a canonical address also finds the observations a producer
	// recorded against a non-entry address that resolves there. It is a
	// convenience index over producer CLAIMS; the authority for identity is
	// internal/index, and a disagreement between the two is reported, not
	// resolved here.
	byCanonical map[uint32][]uint32
	// Bytes is the on-disk size, or -1 when unknown.
	Bytes int64
}

// ImageBase returns the overlay's declared image base.
func (o *Overlay) ImageBase() semantic.Addr {
	if o.Metadata != nil {
		if b, ok := o.Metadata.Binary.ImageBaseAddr(); ok {
			return b
		}
	}
	return semantic.DefaultImageBase
}

// Len returns the number of entry records.
func (o *Overlay) Len() int { return len(o.Order) }

// EntriesFor returns every entry reachable from va: the one whose
// requested_va is va, plus every entry whose producer-claimed canonical_va is
// va. Results are ordered by requested VA.
func (o *Overlay) EntriesFor(va semantic.Addr) []*Entry {
	var out []*Entry
	if e, ok := o.Entries[uint32(va)]; ok {
		out = append(out, e)
	}
	for _, addr := range o.byCanonical[uint32(va)] {
		if addr == uint32(va) {
			continue // already added as the exact match
		}
		out = append(out, o.Entries[addr])
	}
	sort.Slice(out, func(i, j int) bool { return out[i].RequestedVA < out[j].RequestedVA })
	return out
}

// Has reports whether any entry is reachable from va.
func (o *Overlay) Has(va semantic.Addr) bool {
	_, exact := o.Entries[uint32(va)]
	return exact || len(o.byCanonical[uint32(va)]) > 0
}

// Load reads and fully verifies an overlay.
//
// requireSHA, when non-empty, additionally asserts the overlay describes that
// binary; a mismatch is ErrBinaryMismatch and never a warning. requireImageBase,
// when non-zero, is checked the same way.
//
// Every check is fail-closed: the loader returns an error rather than a
// partially-trusted overlay. A producer is an external party, and a runtime
// overlay that is silently half-read is a fabricated negative at best and a
// wrong identity at worst.
func Load(path string, requireSHA string, requireImageBase semantic.Addr) (*Overlay, error) {
	f, err := os.Open(path)
	if err != nil {
		if os.IsNotExist(err) {
			return nil, fmt.Errorf("%w: %s", ErrMissing, path)
		}
		return nil, err
	}
	defer f.Close()

	o := &Overlay{
		Path:        path,
		Entries:     map[uint32]*Entry{},
		byCanonical: map[uint32][]uint32{},
	}
	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<24)

	h := sha256.New()
	haveHeader := false
	lineNo := 0
	for sc.Scan() {
		lineNo++
		line := sc.Bytes()
		if len(bytes.TrimSpace(line)) == 0 {
			continue
		}
		if !haveHeader {
			if err := loadHeader(o, line, lineNo, requireSHA, requireImageBase); err != nil {
				return nil, err
			}
			haveHeader = true
			continue
		}
		var e Entry
		if err := unmarshalStrict(line, &e); err != nil {
			// An unknown field is a contract this build does not implement, which
			// is a DIFFERENT diagnosis from a corrupt file and gets a different
			// exit code. Wrapping it as corruption here would erase that.
			if errors.Is(err, ErrSchema) {
				return nil, fmt.Errorf("%w: %s:%d: %v", ErrSchema, path, lineNo, err)
			}
			return nil, fmt.Errorf("%w: %s:%d: %v", ErrCorrupt, path, lineNo, err)
		}
		if e.Record != RecordEntry {
			return nil, fmt.Errorf("%w: %s:%d: record is %q, expected %q", ErrCorrupt, path, lineNo, e.Record, RecordEntry)
		}
		addr, err := canonicalAddr(e.RequestedVA)
		if err != nil {
			return nil, fmt.Errorf("%w: %s:%d: requested_va %q: %v", ErrCorrupt, path, lineNo, e.RequestedVA, err)
		}
		if len(o.Order) > 0 && uint32(addr) <= o.Order[len(o.Order)-1] {
			kind := "out of order"
			if uint32(addr) == o.Order[len(o.Order)-1] {
				kind = "duplicate requested_va"
			}
			return nil, fmt.Errorf("%w: %s:%d: %s %s; records must be strictly ascending by requested_va", ErrCorrupt, path, lineNo, kind, e.RequestedVA)
		}
		if err := validateEntry(&e, addr); err != nil {
			return nil, fmt.Errorf("%w: %s:%d: %s: %v", ErrCorrupt, path, lineNo, e.RequestedVA, err)
		}
		// The digest covers the exact bytes on disk, before any normalisation.
		h.Write(line)
		h.Write([]byte{'\n'})
		o.Entries[uint32(addr)] = &e
		o.Order = append(o.Order, uint32(addr))
		if e.CanonicalVA != nil {
			canon, err := canonicalAddr(*e.CanonicalVA)
			if err != nil {
				return nil, fmt.Errorf("%w: %s:%d: canonical_va %q: %v", ErrCorrupt, path, lineNo, *e.CanonicalVA, err)
			}
			o.byCanonical[uint32(canon)] = append(o.byCanonical[uint32(canon)], uint32(addr))
		}
	}
	if err := sc.Err(); err != nil {
		return nil, fmt.Errorf("%w: %s: %v", ErrCorrupt, path, err)
	}
	if !haveHeader {
		return nil, fmt.Errorf("%w: %s: no metadata record on line 1", ErrCorrupt, path)
	}
	if len(o.Order) == 0 {
		// An overlay with a valid header and no entries is legal only if the
		// header says so. Silently accepting it would let a truncated producer
		// run look like a run that observed nothing.
		if o.Metadata.Counts.Entries != 0 {
			return nil, fmt.Errorf("%w: %s: metadata declares %d entries, the file carries none",
				ErrCorrupt, path, o.Metadata.Counts.Entries)
		}
	}
	if st, err := f.Stat(); err == nil {
		o.Bytes = st.Size()
	}
	if want := o.Metadata.ContentSHA256; want != "" {
		got := hex.EncodeToString(h.Sum(nil))
		if got != want {
			return nil, fmt.Errorf("%w: %s: content_sha256 is %s, recomputed %s over %d record lines",
				ErrCorrupt, path, want, got, len(o.Order))
		}
	}
	return o, nil
}

func loadHeader(o *Overlay, line []byte, lineNo int, requireSHA string, requireImageBase semantic.Addr) error {
	var meta Metadata
	if err := unmarshalStrict(line, &meta); err != nil {
		return fmt.Errorf("%w: %s:%d: %v", ErrCorrupt, o.Path, lineNo, err)
	}
	if meta.Record != RecordMetadata {
		return fmt.Errorf("%w: %s:%d: first record is %q, expected %q", ErrCorrupt, o.Path, lineNo, meta.Record, RecordMetadata)
	}
	if meta.Schema != OverlaySchema {
		return fmt.Errorf("%w: %s declares %q, this build implements %q", ErrSchema, o.Path, meta.Schema, OverlaySchema)
	}
	if meta.Binary.SHA256 == "" {
		return fmt.Errorf("%w: %s:%d: metadata states no binary_sha256; an overlay without binary identity cannot be joined to anything", ErrCorrupt, o.Path, lineNo)
	}
	if err := checkHexDigest(meta.Binary.SHA256); err != nil {
		return fmt.Errorf("%w: %s:%d: binary_sha256: %v", ErrCorrupt, o.Path, lineNo, err)
	}
	if _, ok := meta.Binary.ImageBaseAddr(); !ok {
		return fmt.Errorf("%w: %s:%d: metadata states no usable image_base (%q)", ErrCorrupt, o.Path, lineNo, meta.Binary.ImageBase)
	}
	if meta.Producer.Project == "" || meta.Producer.Name == "" {
		return fmt.Errorf("%w: %s:%d: metadata names no producer (project=%q name=%q); an unattributable observation is not evidence",
			ErrCorrupt, o.Path, lineNo, meta.Producer.Project, meta.Producer.Name)
	}
	if requireSHA != "" && meta.Binary.SHA256 != requireSHA {
		return fmt.Errorf("%w: overlay describes %s, caller requires %s", ErrBinaryMismatch, shortSHA(meta.Binary.SHA256), shortSHA(requireSHA))
	}
	if requireImageBase != 0 {
		base, _ := meta.Binary.ImageBaseAddr()
		if base != requireImageBase {
			return fmt.Errorf("%w: overlay declares image base %s, caller requires %s",
				ErrImageBaseMismatch, meta.Binary.ImageBase, requireImageBase.String())
		}
	}
	o.Metadata = &meta
	return nil
}

// canonicalAddr parses an address that MUST already be in the canonical
// "0x%08x" spelling.
//
// The strictness is the point. An overlay keyed on requested_va is a canonical
// artifact; if the loader accepted "925050", "0x925050" and "0x00925050" as three
// spellings of one address, then duplicate detection (which compares strings
// under a total order) would pass a file that contains the same address three
// times, and the three copies would carry three different reach counts. The
// strict spelling is the same rule ParseBareAddr states for the committed TSV
// exports: a canonical artifact whose keys sort differently under two spellings
// of one address is a file that can disagree with itself.
func canonicalAddr(s string) (semantic.Addr, error) {
	// The prefix must be lowercase too: "0X00401000" is a different string from
	// "0x00401000", and a canonical artifact that keys under two spellings of one
	// address is a file that can disagree with itself.
	if len(s) != 10 || s[:2] != "0x" {
		return 0, &semantic.ParseAddrError{Input: s, Reason: "not the canonical \"0x%08x\" spelling"}
	}
	addr, err := semantic.ParseAddr(s, 0)
	if err != nil {
		return 0, err
	}
	if addr.String() != strings.ToLower(s) {
		return 0, &semantic.ParseAddrError{Input: s, Reason: "not lowercase zero-padded canonical form (" + addr.String() + ")"}
	}
	return addr, nil
}

func checkHexDigest(s string) error {
	if len(s) != 64 {
		return fmt.Errorf("not 64 hex characters (got %d)", len(s))
	}
	if _, err := hex.DecodeString(s); err != nil {
		return fmt.Errorf("not hexadecimal: %v", err)
	}
	return nil
}

// validateEntry enforces every structural rule on one entry. Each error names
// the specific rule, because "invalid overlay" is not actionable to whoever has
// to fix the producer.
func validateEntry(e *Entry, addr semantic.Addr) error {
	if e.CanonicalVA != nil {
		canon, err := canonicalAddr(*e.CanonicalVA)
		if err != nil {
			return fmt.Errorf("canonical_va %q: %v", *e.CanonicalVA, err)
		}
		if e.Canonicalization != CanonicalEntry && e.Canonicalization != CanonicalInterior {
			return fmt.Errorf("canonical_va is stated but canonicalization is %q; only %q and %q may carry a canonical VA",
				e.Canonicalization, CanonicalEntry, CanonicalInterior)
		}
		if e.Canonicalization == CanonicalInterior && canon == addr {
			return fmt.Errorf("canonicalization is %q but canonical_va equals requested_va", CanonicalInterior)
		}
	}
	if !KnownCanonicalization(e.Canonicalization) {
		return fmt.Errorf("canonicalization %q is outside the closed vocabulary %v", e.Canonicalization, canonicalVocabulary())
	}
	if e.Canonicalization == CanonicalInterior {
		if e.CanonicalOffset == nil {
			return fmt.Errorf("canonicalization is %q but canonical_offset is null", CanonicalInterior)
		}
		if *e.CanonicalOffset <= 0 {
			return fmt.Errorf("canonical_offset %d is not positive; an interior address has a positive offset", *e.CanonicalOffset)
		}
	} else if e.CanonicalOffset != nil {
		return fmt.Errorf("canonical_offset is stated but canonicalization is %q", e.Canonicalization)
	}
	switch e.Reached {
	case TriTrue, TriFalse, TriNull:
	default:
		return fmt.Errorf("reached is %q; the tri-state vocabulary is true/false/null", e.Reached)
	}
	if e.EntryCount != nil {
		if *e.EntryCount < 0 {
			return fmt.Errorf("entry_count %d is negative; an unobserved count is null, not a negative number", *e.EntryCount)
		}
		if e.Reached == TriFalse && *e.EntryCount > 0 {
			return fmt.Errorf("reached is false but entry_count is %d; the producer contradicts itself", *e.EntryCount)
		}
	}
	if e.FirstReachedFrom != nil {
		if err := optionalAddr("first_reached_from", *e.FirstReachedFrom); err != nil {
			return err
		}
	}
	if err := optionalNonNegative("max_call_depth", e.MaxCallDepth); err != nil {
		return err
	}
	if err := validateCallers(e.RuntimeCallers); err != nil {
		return err
	}
	if err := validateTargets(e.RuntimeTargets); err != nil {
		return err
	}
	if err := validateImports(e.RuntimeImports); err != nil {
		return err
	}
	if err := validateObservations(e.Observations); err != nil {
		return err
	}
	if err := validateProvenance(e.Provenance); err != nil {
		return err
	}
	return nil
}

func validateCallers(in []RuntimeCaller) error {
	prev := ""
	for i, c := range in {
		if c.CallsiteVA == "" {
			return fmt.Errorf("runtime_callers[%d]: callsite_va is required", i)
		}
		if err := addrNotBelow("callsite_va", c.CallsiteVA); err != nil {
			return fmt.Errorf("runtime_callers[%d]: %v", i, err)
		}
		if c.CallerFunctionVA != nil {
			if err := optionalAddr("caller_function_va", *c.CallerFunctionVA); err != nil {
				return fmt.Errorf("runtime_callers[%d]: %v", i, err)
			}
		}
		for name, v := range map[string]*int{"count": c.Count, "min_depth": c.MinDepth, "max_depth": c.MaxDepth} {
			if err := optionalNonNegative(name, v); err != nil {
				return fmt.Errorf("runtime_callers[%d]: %v", i, err)
			}
		}
		if c.MinDepth != nil && c.MaxDepth != nil && *c.MinDepth > *c.MaxDepth {
			return fmt.Errorf("runtime_callers[%d]: min_depth %d exceeds max_depth %d", i, *c.MinDepth, *c.MaxDepth)
		}
		key := c.CallsiteVA + "\x00" + derefStr(c.CallerFunctionVA)
		if i > 0 && key <= prev {
			return fmt.Errorf("runtime_callers[%d]: not sorted ascending and de-duplicated by (callsite_va, caller_function_va)", i)
		}
		prev = key
	}
	return nil
}

func validateTargets(in []RuntimeTarget) error {
	prev := ""
	for i, t := range in {
		if t.TargetVA == "" {
			return fmt.Errorf("runtime_targets[%d]: target_va is required", i)
		}
		if err := addrNotBelow("target_va", t.TargetVA); err != nil {
			return fmt.Errorf("runtime_targets[%d]: %v", i, err)
		}
		switch t.Indirect {
		case TriTrue, TriFalse, TriNull:
		default:
			return fmt.Errorf("runtime_targets[%d]: indirect is %q; the tri-state vocabulary is true/false/null", i, t.Indirect)
		}
		switch t.Unresolved {
		case TriTrue, TriFalse, TriNull:
		default:
			return fmt.Errorf("runtime_targets[%d]: unresolved is %q; the tri-state vocabulary is true/false/null", i, t.Unresolved)
		}
		if t.Indirect == TriTrue && t.Unresolved == TriFalse {
			return fmt.Errorf("runtime_targets[%d]: indirect is true but unresolved is false; an unresolved target cannot be a recovered dispatch target", i)
		}
		if i > 0 && t.TargetVA <= prev {
			return fmt.Errorf("runtime_targets[%d]: not sorted ascending and de-duplicated by target_va", i)
		}
		prev = t.TargetVA
	}
	return nil
}

func validateImports(in []RuntimeImportRef) error {
	prev := ""
	for i, r := range in {
		if r.Module == "" || r.Symbol == "" {
			return fmt.Errorf("runtime_imports[%d]: module and symbol are both required", i)
		}
		if r.SlotVA != nil {
			if err := optionalAddr("slot_va", *r.SlotVA); err != nil {
				return fmt.Errorf("runtime_imports[%d]: %v", i, err)
			}
		}
		if r.LoadedValue != nil {
			if err := optionalAddr("loaded_value", *r.LoadedValue); err != nil {
				return fmt.Errorf("runtime_imports[%d]: %v", i, err)
			}
		}
		switch r.Bound {
		case TriTrue, TriFalse, TriNull:
		default:
			return fmt.Errorf("runtime_imports[%d]: bound is %q; the tri-state vocabulary is true/false/null", i, r.Bound)
		}
		if err := optionalNonNegative("reached_count", r.ReachedCount); err != nil {
			return fmt.Errorf("runtime_imports[%d]: %v", i, err)
		}
		key := r.Module + "\x00" + r.Symbol + "\x00" + derefStr(r.SlotVA)
		if i > 0 && key <= prev {
			return fmt.Errorf("runtime_imports[%d]: not sorted ascending and de-duplicated by (module, symbol, slot_va)", i)
		}
		prev = key
	}
	return nil
}

// observationRequired lists, per kind, the fields the kind must carry. A field
// listed here may not be null; anything not listed must be null.
//
// Enforcing both halves is what makes a kind meaningful. Without it, an
// observation could claim kind "import" while carrying only a register value,
// and a consumer scanning for imports would find it.
var observationRequired = map[ObservationKind][]string{
	ObsEntry:        {"eip"},
	ObsCall:         {"callsite_va", "target_va"},
	ObsIndirectCall: {"callsite_va", "target_va"},
	ObsReturn:       {"return_address"},
	ObsImport:       {"module", "symbol"},
	ObsException:    {"eip", "exception_class"},
	ObsMemory:       {"address", "access"},
	ObsRegister:     {"register", "register_value"},
	ObsStack:        {"entry_esp", "return_esp"},
}

func validateObservations(in []Observation) error {
	seen := map[string]int{}
	prevKey := ""
	prevJSON := ""
	for i := range in {
		o := &in[i]
		if !KnownObservationKind(o.Kind) {
			return fmt.Errorf("observations[%d]: kind %q is outside the closed vocabulary %v", i, o.Kind, ObservationKinds)
		}
		for _, name := range observationRequired[o.Kind] {
			if !observationFieldPresent(o, name) {
				return fmt.Errorf("observations[%d]: kind %q requires %s", i, o.Kind, name)
			}
		}
		for name, raw := range observationAddressFields(o) {
			if raw == nil {
				continue
			}
			if err := optionalAddr(name, *raw); err != nil {
				return fmt.Errorf("observations[%d]: kind %q: %v", i, o.Kind, err)
			}
		}
		for _, name := range []string{"count", "call_depth"} {
			if err := optionalNonNegative(name, observationInt(o, name)); err != nil {
				return fmt.Errorf("observations[%d]: kind %q: %v", i, o.Kind, err)
			}
		}
		if o.Kind == ObsMemory {
			switch o.Access {
			case AccessRead, AccessWrite:
			default:
				return fmt.Errorf("observations[%d]: kind %q has access %q; the vocabulary is %q/%q", i, o.Kind, o.Access, AccessRead, AccessWrite)
			}
			if o.WidthBytes != nil && *o.WidthBytes <= 0 {
				return fmt.Errorf("observations[%d]: width_bytes %d is not positive", i, *o.WidthBytes)
			}
		}
		if o.Kind != ObsMemory && o.Access != "" {
			return fmt.Errorf("observations[%d]: kind %q carries access %q, which only a %q observation may state", i, o.Kind, o.Access, ObsMemory)
		}
		if o.Kind == ObsStack {
			if o.StackDeltaBytes == nil {
				return fmt.Errorf("observations[%d]: kind %q requires stack_delta_bytes", i, o.Kind)
			}
		} else if o.StackDeltaBytes != nil {
			return fmt.Errorf("observations[%d]: kind %q carries stack_delta_bytes, which only a %q observation may state", i, o.Kind, ObsStack)
		}
		if o.Kind != ObsIndirectCall && o.Indirect != TriNull {
			return fmt.Errorf("observations[%d]: kind %q states indirect=%q, which only an %q observation may do", i, o.Kind, o.Indirect, ObsIndirectCall)
		}
		switch o.Kind {
		case ObsCall, ObsIndirectCall:
		default:
			if o.CallsiteVA != nil || o.TargetVA != nil {
				return fmt.Errorf("observations[%d]: kind %q carries a call edge, which only call/indirect_call observations may do", i, o.Kind)
			}
		}
		switch o.Kind {
		case ObsImport:
		default:
			if o.Module != nil || o.Symbol != nil || o.SlotVA != nil {
				return fmt.Errorf("observations[%d]: kind %q names an import, which only an %q observation may do", i, o.Kind, ObsImport)
			}
		}
		switch o.Kind {
		case ObsException:
		default:
			if o.Class != nil {
				return fmt.Errorf("observations[%d]: kind %q names an exception class, which only an %q observation may do", i, o.Kind, ObsException)
			}
		}
		switch o.Kind {
		case ObsRegister:
		default:
			if o.Register != nil || o.RegisterValue != nil {
				return fmt.Errorf("observations[%d]: kind %q names a register, which only a %q observation may do", i, o.Kind, ObsRegister)
			}
		}
		switch o.Kind {
		case ObsReturn:
		default:
			if o.ReturnRegister != nil {
				return fmt.Errorf("observations[%d]: kind %q names a return register, which only a %q observation may do", i, o.Kind, ObsReturn)
			}
		}

		raw, err := json.Marshal(o)
		if err != nil {
			return fmt.Errorf("observations[%d]: %v", i, err)
		}
		sum := string(raw)
		if at, dup := seen[sum]; dup {
			return fmt.Errorf("observations[%d]: byte-identical duplicate of observations[%d]", i, at)
		}
		seen[sum] = i

		// The ordering key is the tuple below, with the canonical JSON as a
		// final tiebreak so the order is TOTAL. A partial order would let two
		// producers emit the same observations in different orders, and the
		// overlay would stop being byte-identical across runs.
		key := observationSortKey(o)
		if i > 0 && (key < prevKey || (key == prevKey && sum <= prevJSON)) {
			return fmt.Errorf("observations[%d]: not sorted ascending by (sequence, kind, callsite, target, eip, canonical json)", i)
		}
		prevKey, prevJSON = key, sum
	}
	return nil
}

// sequenceFloor orders an absent sequence before every present one. It is below
// any int64 a producer is likely to use, and using a constant keeps the sort key
// a pure function of the record.
const sequenceFloor = -9223372036854775808

func observationSortKey(o *Observation) string {
	seq := strconv.FormatInt(sequenceFloor, 10)
	if o.Sequence != nil {
		seq = fmt.Sprintf("%020d", *o.Sequence)
	}
	parts := []string{
		seq,
		string(o.Kind),
		derefStr(o.CallsiteVA),
		derefStr(o.TargetVA),
		derefStr(o.EIP),
		derefStr(o.Address),
		derefStr(o.Register),
	}
	return strings.Join(parts, "\x00")
}

func observationFieldPresent(o *Observation, name string) bool {
	switch name {
	case "eip":
		return o.EIP != nil
	case "callsite_va":
		return o.CallsiteVA != nil
	case "target_va":
		return o.TargetVA != nil
	case "return_address":
		return o.ReturnAddress != nil
	case "module":
		return o.Module != nil
	case "symbol":
		return o.Symbol != nil
	case "exception_class":
		return o.Class != nil
	case "address":
		return o.Address != nil
	case "access":
		return o.Access != ""
	case "register":
		return o.Register != nil
	case "register_value":
		return o.RegisterValue != nil
	case "entry_esp":
		return o.EntryESP != nil
	case "return_esp":
		return o.ReturnESP != nil
	}
	return false
}

func observationAddressFields(o *Observation) map[string]*string {
	return map[string]*string{
		"eip":            o.EIP,
		"callsite_va":    o.CallsiteVA,
		"target_va":      o.TargetVA,
		"return_address": o.ReturnAddress,
		"slot_va":        o.SlotVA,
		"register_value": o.RegisterValue,
		"entry_esp":      o.EntryESP,
		"return_esp":     o.ReturnESP,
		"value":          o.Value,
		"address":        o.Address,
	}
}

func observationInt(o *Observation, name string) *int {
	switch name {
	case "count":
		return o.Count
	case "call_depth":
		return o.CallDepth
	}
	return nil
}

func validateProvenance(in []ProvenanceEntry) error {
	if len(in) == 0 {
		return fmt.Errorf("provenance is empty; an observation with no attributable producer is an assertion, not evidence")
	}
	for i, p := range in {
		if !KnownProvenanceSource(p.SourceClass) {
			return fmt.Errorf("provenance[%d]: source_class %q is not %q; a runtime overlay may only claim runtime provenance",
				i, p.SourceClass, ProvenanceSourceRuntime)
		}
		if p.Producer == "" || p.Artifact == "" {
			return fmt.Errorf("provenance[%d]: producer and artifact are both required", i)
		}
		if strings.HasPrefix(p.Artifact, "/") || strings.Contains(p.Artifact, "\\") {
			return fmt.Errorf("provenance[%d]: artifact %q looks like an absolute filesystem path; overlays carry portable artifact identifiers",
				i, p.Artifact)
		}
	}
	return nil
}

func optionalAddr(field, raw string) error {
	addr, err := semantic.ParseAddr(raw, 0)
	if err != nil {
		return fmt.Errorf("%s %q: %v", field, raw, err)
	}
	if addr.String() != strings.ToLower(raw) {
		return fmt.Errorf("%s %q is not the canonical %q spelling", field, raw, addr.String())
	}
	return nil
}

// addrNotBelow enforces canonical spelling for a REQUIRED address field.
func addrNotBelow(field, raw string) error { return optionalAddr(field, raw) }

func optionalNonNegative(field string, v *int) error {
	if v != nil && *v < 0 {
		return fmt.Errorf("%s is %d; an unobserved count is null, not a negative number", field, *v)
	}
	return nil
}

func derefStr(p *string) string {
	if p == nil {
		return ""
	}
	return *p
}

func canonicalVocabulary() []string {
	return []string{CanonicalEntry, CanonicalInterior, CanonicalNonEntity, CanonicalUnknown}
}

// unmarshalStrict rejects unknown fields. A file whose header says this schema
// but whose records carry fields this build has never heard of is a contract
// this build does not implement, and ErrSchema says so -- exactly as the static
// snapshot loader does.
func unmarshalStrict(line []byte, into any) error {
	dec := json.NewDecoder(bytes.NewReader(line))
	dec.DisallowUnknownFields()
	if err := dec.Decode(into); err != nil {
		if strings.Contains(err.Error(), "unknown field") {
			return fmt.Errorf("%w: %v", ErrSchema, err)
		}
		return err
	}
	// A second value on the same line means the producer wrote two records on one
	// line, which would make the content digest depend on a line boundary the
	// producer chose. Reject it.
	if dec.More() {
		return fmt.Errorf("more than one JSON value on this line")
	}
	return nil
}

// Recount recomputes the overlay tallies from the loaded entries.
func (o *Overlay) Recount() Counts {
	var c Counts
	producers := map[string]struct{}{}
	c.Entries = len(o.Order)
	for _, addr := range o.Order {
		e := o.Entries[addr]
		switch e.Reached {
		case TriTrue:
			c.Reached++
		case TriFalse:
			c.NotReached++
		default:
			c.ReachedUnknown++
		}
		if e.EntryCount != nil {
			if *e.EntryCount < 0 {
				// Impossible after load; counted as an observation rather than
				// added, so a corrupted total is visible instead of silent.
				c.Exceptions++
			}
			c.TotalEntryCount += *e.EntryCount
		}
		if e.CanonicalVA == nil {
			c.RuntimeOnly++
		}
		c.RuntimeCallers += len(e.RuntimeCallers)
		c.RuntimeTargets += len(e.RuntimeTargets)
		c.RuntimeImports += len(e.RuntimeImports)
		c.Observations += len(e.Observations)
		for _, ob := range e.Observations {
			if ob.Kind == ObsException {
				c.Exceptions++
			}
		}
		for _, p := range e.Provenance {
			producers[p.Producer+"\x00"+p.Artifact] = struct{}{}
		}
	}
	c.DistinctProducer = len(producers)
	return c
}

// Verify cross-checks the producer's declared counts against the loaded body.
// A header edited by hand, or a file truncated after the header was written, is
// caught here even when the content digest still matches.
func (o *Overlay) Verify() []string {
	got := o.Recount()
	want := o.Metadata.Counts
	var problems []string
	for _, c := range []struct {
		name      string
		g, stored int
	}{
		{"entries", got.Entries, want.Entries},
		{"reached", got.Reached, want.Reached},
		{"not_reached", got.NotReached, want.NotReached},
		{"reached_unknown", got.ReachedUnknown, want.ReachedUnknown},
		{"total_entry_count", got.TotalEntryCount, want.TotalEntryCount},
		{"runtime_only", got.RuntimeOnly, want.RuntimeOnly},
		{"runtime_callers", got.RuntimeCallers, want.RuntimeCallers},
		{"runtime_targets", got.RuntimeTargets, want.RuntimeTargets},
		{"runtime_imports", got.RuntimeImports, want.RuntimeImports},
		{"observations", got.Observations, want.Observations},
		{"exceptions", got.Exceptions, want.Exceptions},
		{"distinct_producers", got.DistinctProducer, want.DistinctProducer},
	} {
		if c.g != c.stored {
			problems = append(problems, fmt.Sprintf("counts.%s: body has %d, metadata declares %d", c.name, c.g, c.stored))
		}
	}
	if want.Entries != len(o.Order) {
		problems = append(problems, fmt.Sprintf("counts.entries: body has %d records", len(o.Order)))
	}
	if !sort.SliceIsSorted(o.Order, func(i, j int) bool { return o.Order[i] < o.Order[j] }) {
		problems = append(problems, "records are not sorted ascending by requested_va")
	}
	return problems
}

func shortSHA(s string) string {
	if len(s) > 12 {
		return s[:12]
	}
	return s
}
