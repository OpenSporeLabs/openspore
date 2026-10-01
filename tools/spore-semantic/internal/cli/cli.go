// Package cli implements the spore-semantic command surface.
//
// Five commands, no orchestration: export, lookup, lookup-symbol, explain,
// stats, validate. Every failure is explicit and carries a stable exit code;
// nothing silently returns an empty object.
package cli

import (
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strconv"
	"strings"

	"github.com/openspore/spore-semantic/internal/index"
	"github.com/openspore/spore-semantic/internal/openspore"
	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/snapshot"
)

// Exit codes. Stable, so a caller can branch on them.
const (
	ExitOK                = 0
	ExitUsage             = 1
	ExitUnknownFunction   = 2
	ExitUnknownSymbol     = 3
	ExitBinaryMismatch    = 4
	ExitCorruptSnapshot   = 5
	ExitUnsupportedSchema = 6
	ExitUnavailable       = 7
	ExitAmbiguousSymbol   = 8
)

// Env carries the process environment so the CLI is testable as a library.
type Env struct {
	Stdout io.Writer
	Stderr io.Writer
	// Root is the OpenSpore checkout. Empty means resolve it.
	Root string
	// SnapshotPath overrides the default snapshot location.
	SnapshotPath string
	// RequireSHA, when non-empty, is the binary_sha256 a consumer requires.
	// When empty it falls back to $OPENSPORE_REQUIRE_SHA, so a consumer that
	// only copies the snapshot and the executable can still pin the identity it
	// is willing to trust.
	RequireSHA string
}

// Run dispatches one invocation and returns the process exit code.
func Run(args []string, env Env) int {
	if env.Stdout == nil {
		env.Stdout = os.Stdout
	}
	if env.Stderr == nil {
		env.Stderr = os.Stderr
	}
	if env.RequireSHA == "" {
		env.RequireSHA = os.Getenv("OPENSPORE_REQUIRE_SHA")
	}
	if len(args) == 0 {
		usage(env.Stderr)
		return ExitUsage
	}
	switch args[0] {
	case "export":
		return runExport(args[1:], env)
	case "lookup":
		return runLookup(args[1:], env)
	case "lookup-symbol":
		return runLookupSymbol(args[1:], env)
	case "explain":
		return runExplain(args[1:], env)
	case "stats":
		return runStats(args[1:], env)
	case "validate":
		return runValidate(args[1:], env)
	case "help", "-h", "--help":
		usage(env.Stdout)
		return ExitOK
	case "version", "--version":
		fmt.Fprintf(env.Stdout, "%s %s (snapshot schema %s)\n",
			semantic.GeneratorName, semantic.GeneratorVersion, semantic.SnapshotSchema)
		return ExitOK
	default:
		fmt.Fprintf(env.Stderr, "spore-semantic: unknown command %q\n\n", args[0])
		usage(env.Stderr)
		return ExitUsage
	}
}

func usage(w io.Writer) {
	fmt.Fprint(w, `spore-semantic -- read-only semantic exchange over OpenSpore's function knowledge

usage:
  spore-semantic export        [--out PATH] [--root DIR]
  spore-semantic lookup        <VA>      [--snapshot PATH] [--json]
  spore-semantic lookup-symbol <NAME>    [--snapshot PATH] [--json]
  spore-semantic explain       <VA>      [--snapshot PATH]
  spore-semantic stats                   [--snapshot PATH] [--json]
  spore-semantic validate                [--snapshot PATH] [--json]
  spore-semantic version

Identity is binary_sha256 + canonical VA. A VA spelling is always "0x%08x".
Input accepts 0x-prefixed, bare, upper or lower case HEX, explicit decimal
("dec:" or "0d"), and the explicit "rva:" form, which is the only spelling that
is offset by the image base -- so an RVA is never confused with a VA.

Set OPENSPORE_REQUIRE_SHA to refuse any snapshot whose binary_sha256 differs,
and OPENSPORE_ROOT to point at the checkout without passing --root.

Exit codes: 0 ok, 1 usage, 2 unknown function, 3 unknown symbol,
4 binary mismatch, 5 corrupted snapshot, 6 unsupported schema,
7 source or snapshot unavailable, 8 ambiguous symbol.
`)
}

// parseArgs splits args into flags and positionals itself, so that a VA may
// appear before or after the flags. Go's flag package stops at the first
// non-flag argument, which makes `lookup 0x00401000 --json` silently drop the
// --json -- an agent will write it that way.
func parseArgs(fs *flag.FlagSet, args []string) ([]string, error) {
	takesValue := map[string]bool{}
	fs.VisitAll(func(f *flag.Flag) {
		if bf, ok := f.Value.(interface{ IsBoolFlag() bool }); ok && bf.IsBoolFlag() {
			return
		}
		takesValue[f.Name] = true
	})
	var flagArgs, positional []string
	for i := 0; i < len(args); i++ {
		a := args[i]
		if a == "--" {
			positional = append(positional, args[i+1:]...)
			break
		}
		if len(a) > 1 && a[0] == '-' {
			flagArgs = append(flagArgs, a)
			name := strings.TrimLeft(a, "-")
			if eq := strings.IndexByte(name, '='); eq >= 0 {
				continue
			}
			if takesValue[name] && i+1 < len(args) {
				i++
				flagArgs = append(flagArgs, args[i])
			}
			continue
		}
		positional = append(positional, a)
	}
	if err := fs.Parse(flagArgs); err != nil {
		return nil, err
	}
	return positional, nil
}

// ---- export ---------------------------------------------------------------

func runExport(args []string, env Env) int {
	fs := flag.NewFlagSet("export", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	out := fs.String("out", "", "snapshot path to write")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	rest, err := parseArgs(fs, args)
	if err != nil {
		return ExitUsage
	}
	if len(rest) > 0 {
		fmt.Fprintf(env.Stderr, "spore-semantic export: unexpected argument %q\n", rest[0])
		return ExitUsage
	}

	r, err := resolveRoot(*root)
	if err != nil {
		return fail(env, ExitUnavailable, "unavailable", err)
	}
	env.Root = r

	srcs, err := openspore.LoadSources(r)
	if err != nil {
		if errors.Is(err, openspore.ErrUniverseUnavailable) {
			return fail(env, ExitUnavailable, "universe_unavailable", err)
		}
		return fail(env, ExitUsage, "source_error", err)
	}

	bin, err := srcs.BinaryIdentity()
	if err != nil {
		return fail(env, ExitUnavailable, "binary_identity_unavailable", err)
	}

	passports, counts, notes, err := openspore.BuildPassports(srcs)
	if err != nil {
		return fail(env, ExitUsage, "projection_failed", err)
	}
	// The export always writes in canonical VA order, regardless of how the
	// universe was ordered, so the byte output cannot depend on read order.
	sort.Slice(passports, func(i, j int) bool {
		return passports[i].Identity.CanonicalVA < passports[j].Identity.CanonicalVA
	})
	counts.Functions = len(passports)

	path := *out
	if path == "" {
		path = defaultSnapshotPath(r)
	}

	inputs := make([]semantic.InputDigest, 0, len(srcs.Digests))
	for _, d := range srcs.Digests {
		inputs = append(inputs, semantic.InputDigest{Path: d.Path, SHA256: d.SHA256, Bytes: d.Bytes})
	}
	inputs = append(inputs, semantic.InputDigest{
		Path:   srcs.Universe.Source,
		SHA256: "",
		Bytes:  0,
	})
	// Drop the duplicate universe digest: LoadSources already appended it.
	inputs = dedupeInputs(inputs)
	absent := make([]semantic.AbsentInput, 0, len(srcs.Absent))
	for _, a := range srcs.Absent {
		absent = append(absent, semantic.AbsentInput{Path: a.Path, Reason: a.Reason})
	}

	res, err := snapshot.Write(path, passports, counts, snapshot.Options{
		Binary:       bin,
		Inputs:       inputs,
		AbsentInputs: absent,
		Export:       notes,
	})
	if err != nil {
		return fail(env, ExitUsage, "write_failed", err)
	}

	fmt.Fprintf(env.Stdout, "wrote %s\n", res.Path)
	fmt.Fprintf(env.Stdout, "  binary_sha256  %s\n", bin.SHA256)
	fmt.Fprintf(env.Stdout, "  image_base     %s\n", bin.ImageBase)
	fmt.Fprintf(env.Stdout, "  functions      %d\n", res.Records)
	fmt.Fprintf(env.Stdout, "  bytes          %d\n", res.Bytes)
	fmt.Fprintf(env.Stdout, "  content_sha256 %s\n", res.ContentSHA)
	fmt.Fprintf(env.Stdout, "  universe       %s\n", srcs.Universe.Source)
	if srcs.Universe.Fallback {
		fmt.Fprintf(env.Stdout, "  note           fallback universe: %s is absent from this checkout\n", openspore.RelUniverse)
	}
	return ExitOK
}

func dedupeInputs(in []semantic.InputDigest) []semantic.InputDigest {
	sort.Slice(in, func(i, j int) bool {
		if in[i].Path != in[j].Path {
			return in[i].Path < in[j].Path
		}
		return in[i].SHA256 > in[j].SHA256
	})
	out := in[:0]
	for _, d := range in {
		if d.SHA256 == "" {
			continue
		}
		if len(out) > 0 && out[len(out)-1].Path == d.Path {
			continue
		}
		out = append(out, d)
	}
	return out
}

// ---- lookup ---------------------------------------------------------------

func runLookup(args []string, env Env) int {
	fs := flag.NewFlagSet("lookup", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	snapPath := fs.String("snapshot", env.SnapshotPath, "snapshot path")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	rest, err := parseArgs(fs, args)
	if err != nil {
		return ExitUsage
	}
	if len(rest) != 1 {
		fmt.Fprintln(env.Stderr, "spore-semantic lookup: exactly one VA is required")
		return ExitUsage
	}

	ix, code := load(args, *snapPath, *root, env)
	if ix == nil {
		return code
	}
	base := ix.ImageBase()
	va, err := semantic.ParseAddr(rest[0], base)
	if err != nil {
		return fail(env, ExitUsage, "invalid_address", err)
	}
	res := ix.Resolve(va)
	if res.Passport == nil {
		return reportUnknown(env, *asJSON, ix, va)
	}

	if *asJSON {
		if err := writeJSON(env.Stdout, lookupResult(ix, res)); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	printLookup(env.Stdout, ix, res)
	return ExitOK
}

type identityResolutionOut struct {
	Rule   string `json:"rule"`
	Offset int    `json:"offset"`
	Range  *struct {
		Start string `json:"start"`
		End   string `json:"end"`
	} `json:"range"`
	Recorded *semantic.IdentityResolution `json:"recorded"`
}

type lookupResultOut struct {
	BinarySHA256       string                 `json:"binary_sha256"`
	ImageBase          string                 `json:"image_base"`
	RequestedVA        string                 `json:"requested_va"`
	CanonicalVA        string                 `json:"canonical_va"`
	RVA                string                 `json:"rva"`
	IdentityResolution *identityResolutionOut `json:"identity_resolution"`

	Identity       semantic.IdentityBlock                          `json:"identity"`
	Names          semantic.NamesBlock                             `json:"names"`
	Mechanical     semantic.ClassificationBlock                    `json:"semantic_classification"`
	ABI            semantic.Envelope[semantic.ABIBlock]            `json:"abi"`
	VTable         semantic.Envelope[semantic.VTableBlock]         `json:"vtable"`
	Graph          semantic.GraphBlock                             `json:"graph"`
	Globals        semantic.Envelope[[]string]                     `json:"globals"`
	Types          semantic.Envelope[[]string]                     `json:"types"`
	Semantics      semantic.Envelope[semantic.SemanticsBlock]      `json:"semantics"`
	Reconstruction semantic.Envelope[semantic.ReconstructionBlock] `json:"reconstruction"`
	Evidence       semantic.EvidenceBlock                          `json:"evidence"`
	Provenance     []semantic.ProvenanceEntry                      `json:"provenance"`
}

func lookupResult(ix *index.Index, res index.Resolution) *lookupResultOut {
	p := res.Passport
	out := &lookupResultOut{
		BinarySHA256:   ix.Data().Metadata.Binary.SHA256,
		ImageBase:      ix.Data().Metadata.Binary.ImageBase,
		RequestedVA:    res.Requested.String(),
		CanonicalVA:    p.Identity.CanonicalVA,
		RVA:            p.Identity.RVA,
		Identity:       p.Identity,
		Names:          p.Names,
		Mechanical:     p.Classification,
		ABI:            p.ABI,
		VTable:         p.VTable,
		Graph:          p.Graph,
		Globals:        p.Globals,
		Types:          p.Types,
		Semantics:      p.Semantics,
		Reconstruction: p.Reconstruction,
		Evidence:       p.Evidence,
		Provenance:     p.Provenance,
	}
	switch res.Kind {
	case index.KindInterior:
		out.IdentityResolution = &identityResolutionOut{
			Rule:     string(index.KindInterior),
			Offset:   res.Offset,
			Recorded: p.Identity.IdentityResolution,
		}
		out.IdentityResolution.Range = &struct {
			Start string `json:"start"`
			End   string `json:"end"`
		}{Start: p.Identity.CanonicalVA, End: res.End.String()}
	case index.KindExact:
		// identity_resolution stays null: the requested VA was already an
		// entry, and emitting a rule for that would imply a correction
		// happened when none did.
		out.IdentityResolution = nil
	}
	return out
}

func printLookup(w io.Writer, ix *index.Index, res index.Resolution) {
	p := res.Passport
	fmt.Fprintf(w, "%s  %s\n", p.Identity.CanonicalVA, firstName(p))
	fmt.Fprintf(w, "  requested_va    %s", res.Requested.String())
	if res.Kind == index.KindInterior {
		fmt.Fprintf(w, "  -> resolved to containing entry, rule=%s offset=%d range=%s..%s",
			index.KindInterior, res.Offset, p.Identity.CanonicalVA, res.End.String())
	} else {
		fmt.Fprintf(w, "  (function entry)")
	}
	fmt.Fprintln(w)
	fmt.Fprintf(w, "  rva             %s\n", p.Identity.RVA)
	fmt.Fprintf(w, "  image_base      %s   binary %s\n",
		ix.Data().Metadata.Binary.ImageBase, short(ix.Data().Metadata.Binary.SHA256))
	fmt.Fprintf(w, "  size            %d bytes (section %s, thunk=%t)\n",
		p.Identity.Size, p.Identity.Section, p.Identity.IsThunk)

	fmt.Fprintf(w, "\n  identity\n")
	if p.Names.SDKName != nil {
		fmt.Fprintf(w, "    sdk_name          %s   [source: %s]\n", *p.Names.SDKName, deref(p.Names.SDKNameSource))
	} else {
		fmt.Fprintf(w, "    sdk_name          %s\n", unknownNote)
	}
	if p.Names.NormalizedSymbol != nil {
		fmt.Fprintf(w, "    normalized_symbol %s\n", *p.Names.NormalizedSymbol)
	} else {
		fmt.Fprintf(w, "    normalized_symbol %s\n", unknownNote)
	}
	if p.Names.IdentityRefuted != nil {
		fmt.Fprintf(w, "    refuted           %q superseded %q (source: %s)\n",
			p.Names.IdentityRefuted.Name, p.Names.IdentityRefuted.Superseded,
			p.Names.IdentityRefuted.SupersededSource)
	}

	fmt.Fprintf(w, "\n  classification\n")
	fmt.Fprintf(w, "    category          %s   evidence=%s priority=%s\n",
		orUnknown(p.Classification.Category), orUnknown(p.Classification.Evidence), orUnknown(p.Classification.Priority))
	fmt.Fprintf(w, "    subsystem         %s   [%s]\n",
		orUnknownPtr(p.Classification.Subsystem), orUnknown(deref(p.Classification.SubsystemSource)))
	if p.Classification.RenderwareRole != nil {
		fmt.Fprintf(w, "    renderware_role   %s\n", *p.Classification.RenderwareRole)
	}
	if len(p.Classification.SDKStructs) > 0 {
		fmt.Fprintf(w, "    sdk_structs       %s\n", strings.Join(p.Classification.SDKStructs, ", "))
	}

	printEnvelopeHeader(w, "  abi", p.ABI, p.ABI.EvidenceLevel)
	if p.ABI.IsAvailable() {
		a := p.ABI.Deref()
		fmt.Fprintf(w, "    origin            %s (schema %s)\n", a.Origin, orUnknown(a.Schema))
		fmt.Fprintf(w, "    convention        %s   confidence=%s verdict=%s\n",
			orUnknownPtr(a.Convention), a.ConventionConfidence, orUnknownPtr(a.Verdict))
		if a.Receiver != nil {
			fmt.Fprintf(w, "    receiver          present=%s register=%s confidence=%s",
				a.Receiver.Present, orUnknownPtr(a.Receiver.Register), a.Receiver.Confidence)
			if a.Receiver.Provenance != nil {
				fmt.Fprintf(w, " provenance=%s", *a.Receiver.Provenance)
			}
			if a.Receiver.BoundsOnly != nil && *a.Receiver.BoundsOnly {
				fmt.Fprintf(w, " bounds_only=true")
			}
			fmt.Fprintln(w)
		} else {
			fmt.Fprintf(w, "    receiver          %s\n", unknownNote)
		}
		if a.Cleanup != nil {
			fmt.Fprintf(w, "    cleanup           side=%s bytes=%s confidence=%s corroboration=%s\n",
				orUnknownPtr(a.Cleanup.Side), orUnknownInt(a.Cleanup.Bytes), a.Cleanup.Confidence,
				orUnknownPtr(a.Cleanup.Corroboration))
		}
		if a.Return != nil {
			fmt.Fprintf(w, "    return            register=%s class=%s confidence=%s type=%s\n",
				orUnknownPtr(a.Return.Register), orUnknownPtr(a.Return.RegisterClass),
				a.Return.Confidence, returnTypeText(a.Return.Type))
		}
		fmt.Fprintf(w, "    variadic          %s\n", orUnknownPtr(a.Variadic))
		if a.Declared != nil {
			fmt.Fprintf(w, "    declared          %s   [semantic interpretation, worker metadata]\n",
				orUnknownPtr(a.Declared.CallingConvention))
		}
	}

	printEnvelopeHeader(w, "  vtable", p.VTable, p.VTable.EvidenceLevel)
	if p.VTable.IsAvailable() {
		v := p.VTable.Deref()
		if len(v.Memberships) == 0 {
			fmt.Fprintf(w, "    memberships       %s\n", noneRecorded)
		} else {
			for i, m := range v.Memberships {
				width := ""
				if m.SlotWidth != nil {
					width = fmt.Sprintf("/%d", *m.SlotWidth)
				}
				label := "memberships     "
				if i > 0 {
					label = "                 "
				}
				fmt.Fprintf(w, "    %s   %s slot %d%s\n", label, m.TableVA, m.Slot, width)
			}
		}
		if v.ABIAttributed != nil {
			fmt.Fprintf(w, "    abi_attributed    %s slot %d by rule %s confidence=%s\n",
				v.ABIAttributed.TableVA, v.ABIAttributed.Slot, v.ABIAttributed.Rule, v.ABIAttributed.Confidence)
		} else {
			fmt.Fprintf(w, "    abi_attributed    %s\n", unknownNote)
		}
		if len(v.TriageAddresses) > 0 {
			fmt.Fprintf(w, "    triage_addresses  %s\n", strings.Join(v.TriageAddresses, ", "))
		}
	}

	fmt.Fprintf(w, "\n  graph\n")
	fmt.Fprintf(w, "    callers           %d", p.Graph.CallerCount)
	if p.Graph.CallerCount > 0 {
		fmt.Fprintf(w, "  %s", previewList(p.Graph.Callers, 6))
	}
	fmt.Fprintln(w)
	fmt.Fprintf(w, "    callees           %d", p.Graph.CalleeCount)
	if p.Graph.CalleeCount > 0 {
		fmt.Fprintf(w, "  %s", previewList(p.Graph.Callees, 6))
	}
	fmt.Fprintln(w)
	if len(p.Graph.ExternalCallees) > 0 {
		fmt.Fprintf(w, "    external_callees  %s\n", strings.Join(p.Graph.ExternalCallees, ", "))
	}
	fmt.Fprintf(w, "    data_refs         %d   vtable_refs %d\n",
		p.Graph.DataReferenceCount, p.Graph.VTableReferenceCount)

	printEnvelopeHeader(w, "  globals", p.Globals, p.Globals.EvidenceLevel)
	if p.Globals.IsAvailable() {
		for _, g := range p.Globals.Deref() {
			fmt.Fprintf(w, "    %s\n", g)
		}
	}
	printEnvelopeHeader(w, "  types", p.Types, p.Types.EvidenceLevel)
	if p.Types.IsAvailable() {
		fmt.Fprintf(w, "    %s\n", strings.Join(p.Types.Deref(), ", "))
	}

	printEnvelopeHeader(w, "  semantics", p.Semantics, p.Semantics.EvidenceLevel)
	if p.Semantics.IsAvailable() {
		s := p.Semantics.Deref()
		fmt.Fprintf(w, "    classification    %s\n", orUnknownPtr(s.Classification))
		fmt.Fprintf(w, "    semantic_status   %s\n", orUnknownPtr(s.Status))
		axes := make([]string, 0, len(s.Confidence))
		for k := range s.Confidence {
			axes = append(axes, k)
		}
		sort.Strings(axes)
		for _, k := range axes {
			fmt.Fprintf(w, "    confidence.%-14s %s\n", k, axisValue(s.Confidence[k]))
		}
		for _, e := range s.Evidence {
			fmt.Fprintf(w, "    evidence[%s] %s  {%s}\n", e.Class, e.Claim, e.Source)
		}
		if len(s.UnresolvedQuestions) > 0 {
			fmt.Fprintf(w, "    unresolved_questions %d (see `spore-semantic explain %s`)\n",
				len(s.UnresolvedQuestions), p.Identity.CanonicalVA)
		}
	}

	printEnvelopeHeader(w, "  reconstruction", p.Reconstruction, p.Reconstruction.EvidenceLevel)
	if p.Reconstruction.IsAvailable() {
		r := p.Reconstruction.Deref()
		fmt.Fprintf(w, "    package           %s   [%s]\n", orUnknownPtr(r.Package), orUnknownPtr(r.Status))
		fmt.Fprintf(w, "    review            %s   integration=%s\n",
			orUnknownPtr(r.ReviewStatus), orUnknownPtr(r.IntegrationStatus))
		fmt.Fprintf(w, "    promoted          %s", r.Promoted)
		if r.StaticStatus != nil {
			fmt.Fprintf(w, "   static_status=%s", *r.StaticStatus)
		}
		fmt.Fprintln(w)
		if len(r.GeneratedSource) > 0 {
			fmt.Fprintf(w, "    generated_source  %s\n", strings.Join(r.GeneratedSource, ", "))
		}
		fmt.Fprintf(w, "    runtime           gated=%s validated=%d\n",
			orUnknownBool(r.RuntimeGated), intOrZero(r.RuntimeValidated))
		if text := axisValue(r.RuntimeBlockingReason); text != "" && text != "null" {
			fmt.Fprintf(w, "    blocking_reason   %s\n", text)
		}
		if r.Validation != nil {
			dims := make([]string, 0, len(r.Validation.Coverage))
			for k := range r.Validation.Coverage {
				dims = append(dims, k)
			}
			sort.Strings(dims)
			for _, d := range dims {
				chk := r.Validation.Coverage[d]
				fmt.Fprintf(w, "    validation.%-20s %s (%s)\n", d, chk.Status, chk.Coverage)
			}
			if r.Validation.Runtime != nil {
				fmt.Fprintf(w, "    validation.RUNTIME %s -- %s\n", r.Validation.Runtime.Status, r.Validation.Runtime.Detail)
			}
		} else {
			fmt.Fprintf(w, "    validation        %s\n", unknownNote)
		}
	}

	if p.Evidence.Pack != nil {
		fmt.Fprintf(w, "\n  evidence artifacts\n")
		fmt.Fprintf(w, "    pack             %s", *p.Evidence.Pack)
		if p.Evidence.PackState != nil {
			fmt.Fprintf(w, "  [%s]", *p.Evidence.PackState)
		}
		fmt.Fprintln(w)
		if p.Evidence.PackContentSHA256 != nil {
			fmt.Fprintf(w, "    pack_sha256      %s\n", *p.Evidence.PackContentSHA256)
		}
		if p.Evidence.TargetAddressKind != nil {
			fmt.Fprintf(w, "    address_kind     %s\n", *p.Evidence.TargetAddressKind)
		}
		if p.Evidence.PromotionRecord != nil {
			fmt.Fprintf(w, "    promotion_record %s\n", *p.Evidence.PromotionRecord)
		}
		for _, ap := range p.Evidence.AdditionalPacks {
			fmt.Fprintf(w, "    additional_pack  %s  (requested %s, rule=%s, offset=%d)\n",
				ap.Pack, ap.RequestedVA, ap.Rule, ap.Offset)
		}
	}

	fmt.Fprintf(w, "\n  provenance\n")
	if len(p.Provenance) == 0 {
		fmt.Fprintf(w, "    %s\n", noneRecorded)
	}
	for _, pv := range p.Provenance {
		fmt.Fprintf(w, "    %-9s %-18s %s\n", pv.Mode, pv.SourceClass, pv.Ref)
	}
}

const (
	unknownNote  = "UNKNOWN (not stated by any authoritative OpenSpore artifact)"
	noneRecorded = "none recorded"
)

func printEnvelopeHeader[T any](w io.Writer, label string, e semantic.Envelope[T], level semantic.EvidenceLevel) {
	fmt.Fprintf(w, "\n  %s  [%s / %s / %s]\n", label, e.State, e.EvidenceState, level)
	if !e.IsAvailable() {
		fmt.Fprintf(w, "    reason: %s\n", e.Reason)
		fmt.Fprintf(w, "      %s\n", reasonText(e.Reason))
	}
	for _, pv := range e.Provenance {
		fmt.Fprintf(w, "    provenance: %s\n", pv)
	}
}

// reasonText expands a closed reason code into prose for human output. The
// snapshot carries the code, not the prose, because the same code applies to
// tens of thousands of records; the expansion lives here and in the docs.
func reasonText(code string) string {
	if text, ok := reasonProse[code]; ok {
		return text
	}
	return "no generic explanation: this reason was supplied verbatim by the source artifact"
}

var reasonProse = map[string]string{
	semantic.ReasonNoEvidencePack:     "no evidence pack exists for this VA, so no ABI inference record was ever derived; absence of a pack is not evidence of a convention",
	semantic.ReasonNoABIDerived:       "an evidence pack exists but its abi_derived category carries no value",
	semantic.ReasonNoVTableMembership: "neither the sound vftable scan nor the triage vtable index associates a table with this function; a function absent from a scanned table is not thereby known NOT to be virtual",
	semantic.ReasonVTableScanAbsent:   "the sound vftable scan is not present in the exporting checkout, so vtable membership could not be consulted at all",
	semantic.ReasonNoGlobalRefs:       "the knowledge index records no global reference for this function; the GLOBALS verdict in the validation report, when present, is the adjudicated statement about data references and is a different thing",
	semantic.ReasonNoTypes:            "the knowledge index associates no type with this function",
	semantic.ReasonNoSemanticRecord:   "no semantic research record exists; the knowledge index holds no interpretation of what this function means",
	semantic.ReasonNoReconstruction:   "no reconstruction package, staged source, validation report or promotion record exists; this is an unreconstructed triage target",
	semantic.ReasonNoValidation:       "a reconstruction record exists but carries no validation report",
}

func reportUnknown(env Env, asJSON bool, ix *index.Index, va semantic.Addr) int {
	msg := fmt.Sprintf(
		"unknown function: %s is not a function entry and is not inside any known function body in binary %s (image base %s); %d functions indexed",
		va.String(), short(ix.Data().Metadata.Binary.SHA256), ix.Data().Metadata.Binary.ImageBase, ix.Len())
	if asJSON {
		payload := map[string]any{
			"error":               "unknown_function",
			"requested_va":        va.String(),
			"binary_sha256":       ix.Data().Metadata.Binary.SHA256,
			"image_base":          ix.Data().Metadata.Binary.ImageBase,
			"identity_resolution": nil,
			"functions_indexed":   ix.Len(),
			"message":             msg,
		}
		_ = writeJSON(env.Stdout, payload)
	} else {
		fmt.Fprintln(env.Stderr, "spore-semantic: "+msg)
	}
	return ExitUnknownFunction
}

// ---- lookup-symbol --------------------------------------------------------

func runLookupSymbol(args []string, env Env) int {
	fs := flag.NewFlagSet("lookup-symbol", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	snapPath := fs.String("snapshot", env.SnapshotPath, "snapshot path")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	rest, err := parseArgs(fs, args)
	if err != nil {
		return ExitUsage
	}
	if len(rest) != 1 {
		fmt.Fprintln(env.Stderr, "spore-semantic lookup-symbol: exactly one name is required")
		return ExitUsage
	}
	ix, code := load(args, *snapPath, *root, env)
	if ix == nil {
		return code
	}
	name := rest[0]
	matches := ix.LookupSymbol(name)
	if len(matches) == 0 {
		msg := fmt.Sprintf("unknown symbol: %q matches no indexed name (normalised, SDK and ghidra names are indexed; %d distinct names, %d of them shared by more than one function)",
			name, ix.SymbolCount(), ix.AmbiguousNameCount())
		if *asJSON {
			_ = writeJSON(env.Stdout, map[string]any{
				"error": "unknown_symbol", "symbol": name, "message": msg,
			})
		} else {
			fmt.Fprintln(env.Stderr, "spore-semantic: "+msg)
		}
		return ExitUnknownSymbol
	}
	if len(matches) > 1 {
		msg := fmt.Sprintf("ambiguous symbol: %q matches %d canonical functions (%s); address identity is authoritative, so look each up by VA",
			name, len(matches), joinAddresses(matches))
		if *asJSON {
			payload := map[string]any{
				"error": "ambiguous_symbol", "symbol": name, "matches": len(matches),
				"canonical_vas": addressesOf(matches), "message": msg,
			}
			_ = writeJSON(env.Stdout, payload)
		} else {
			fmt.Fprintln(env.Stderr, "spore-semantic: "+msg)
			for _, m := range matches {
				fmt.Fprintf(env.Stderr, "  %s  %s\n", m.Passport.Identity.CanonicalVA, firstName(m.Passport))
			}
		}
		return ExitAmbiguousSymbol
	}

	if *asJSON {
		if err := writeJSON(env.Stdout, map[string]any{
			"binary_sha256": ix.Data().Metadata.Binary.SHA256,
			"image_base":    ix.Data().Metadata.Binary.ImageBase,
			"symbol":        name,
			"matches":       1,
			"result":        lookupResult(ix, index.Resolution{Kind: index.KindExact, Passport: matches[0].Passport, Requested: mustAddr(matches[0].Passport.Identity.CanonicalVA)}),
		}); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	printLookup(env.Stdout, ix, index.Resolution{Kind: index.KindExact, Passport: matches[0].Passport, Requested: mustAddr(matches[0].Passport.Identity.CanonicalVA)})
	return ExitOK
}

func joinAddresses(matches []index.SymbolMatch) string {
	var out []string
	for _, m := range matches {
		out = append(out, m.Passport.Identity.CanonicalVA)
	}
	return strings.Join(out, ", ")
}

func addressesOf(matches []index.SymbolMatch) []string {
	out := make([]string, 0, len(matches))
	for _, m := range matches {
		out = append(out, m.Passport.Identity.CanonicalVA)
	}
	return out
}

func mustAddr(s string) semantic.Addr {
	a, _ := semantic.ParseAddr(s, 0)
	return a
}

// explainLine is one labelled fact in the explain output.
type explainLine struct{ name, value string }

// ---- explain --------------------------------------------------------------

func runExplain(args []string, env Env) int {
	fs := flag.NewFlagSet("explain", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	snapPath := fs.String("snapshot", env.SnapshotPath, "snapshot path")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	rest, err := parseArgs(fs, args)
	if err != nil {
		return ExitUsage
	}
	if len(rest) != 1 {
		fmt.Fprintln(env.Stderr, "spore-semantic explain: exactly one VA is required")
		return ExitUsage
	}
	ix, code := load(args, *snapPath, *root, env)
	if ix == nil {
		return code
	}
	va, err := semantic.ParseAddr(rest[0], ix.ImageBase())
	if err != nil {
		return fail(env, ExitUsage, "invalid_address", err)
	}
	res := ix.Resolve(va)
	if res.Passport == nil {
		return reportUnknown(env, false, ix, va)
	}
	p := res.Passport
	w := env.Stdout

	fmt.Fprintf(w, "%s %s\n", p.Identity.CanonicalVA, firstName(p))
	fmt.Fprintf(w, "requested %s -> %s (%s)\n\n", va.String(), p.Identity.CanonicalVA, res.Kind)

	fmt.Fprintf(w, "WHY OPENSPORE BELIEVES THIS\n")
	fmt.Fprintf(w, "  every fact group below carries its own provenance; an absent group is published\n")
	fmt.Fprintf(w, "  as an explicit absence with a reason, never omitted.\n\n")

	groups := []struct {
		name  string
		lines []explainLine
	}{
		{"abi", abiLines(p)},
		{"vtable", vtableLines(p)},
		{"semantics", semanticsLines(p)},
		{"reconstruction", reconstructionLines(p)},
	}
	for _, g := range groups {
		fmt.Fprintf(w, "  %s\n", g.name)
		if len(g.lines) == 0 {
			fmt.Fprintf(w, "    %s\n", noneRecorded)
			continue
		}
		for _, l := range g.lines {
			fmt.Fprintf(w, "    %-22s %s\n", l.name, l.value)
		}
		fmt.Fprintln(w)
	}

	if p.Semantics.IsAvailable() && len(p.Semantics.Deref().UnresolvedQuestions) > 0 {
		fmt.Fprintf(w, "  UNRESOLVED QUESTIONS (%d) -- OpenSpore's own open questions about this function\n\n",
			len(p.Semantics.Deref().UnresolvedQuestions))
		for i, q := range p.Semantics.Deref().UnresolvedQuestions {
			fmt.Fprintf(w, "    [%d] %s\n\n", i+1, q)
		}
	}
	if p.Reconstruction.IsAvailable() {
		if v := p.Reconstruction.Deref().Validation; v != nil {
			dims := make([]string, 0, len(v.Coverage))
			for k := range v.Coverage {
				dims = append(dims, k)
			}
			sort.Strings(dims)
			fmt.Fprintf(w, "  VALIDATION DETAIL\n")
			for _, d := range dims {
				chk := v.Coverage[d]
				fmt.Fprintf(w, "    %s  %s / coverage=%s\n", d, chk.Status, chk.Coverage)
				if chk.Detail != "" {
					fmt.Fprintf(w, "      %s\n", chk.Detail)
				}
				if len(chk.Evidence) > 0 {
					fmt.Fprintf(w, "      evidence: %s\n", strings.Join(chk.Evidence, ", "))
				}
			}
			if v.Runtime != nil {
				fmt.Fprintf(w, "    RUNTIME  %s / %s\n", v.Runtime.Status, v.Runtime.Detail)
			}
		}
	}
	return ExitOK
}

func abiLines(p *semantic.Passport) []explainLine {
	if !p.ABI.IsAvailable() {
		return nil
	}
	a := p.ABI.Deref()
	var out []explainLine
	out = append(out, explainLine{"origin", a.Origin})
	out = append(out, explainLine{"record schema", orUnknown(a.Schema)})
	out = append(out, explainLine{"convention", orUnknownPtr(a.Convention) + " (" + string(a.ConventionConfidence) + ")"})
	out = append(out, explainLine{"verdict", orUnknownPtr(a.Verdict)})
	if a.Receiver != nil {
		out = append(out, explainLine{"receiver", fmt.Sprintf("present=%s register=%s confidence=%s",
			a.Receiver.Present, orUnknownPtr(a.Receiver.Register), a.Receiver.Confidence)})
	}
	if a.Cleanup != nil {
		out = append(out, explainLine{"cleanup", fmt.Sprintf("side=%s bytes=%s confidence=%s",
			orUnknownPtr(a.Cleanup.Side), orUnknownInt(a.Cleanup.Bytes), a.Cleanup.Confidence)})
	}
	if a.Return != nil {
		out = append(out, explainLine{"return", fmt.Sprintf("register=%s class=%s confidence=%s",
			orUnknownPtr(a.Return.Register), orUnknownPtr(a.Return.RegisterClass), a.Return.Confidence)})
	}
	if a.Declared != nil {
		out = append(out, explainLine{"declared", "semantic interpretation from worker metadata: " + orUnknownPtr(a.Declared.CallingConvention)})
	}
	return out
}

func vtableLines(p *semantic.Passport) []explainLine {
	if !p.VTable.IsAvailable() {
		return nil
	}
	v := p.VTable.Deref()
	var out []explainLine
	for _, m := range v.Memberships {
		out = append(out, explainLine{"membership", fmt.Sprintf("%s slot %d", m.TableVA, m.Slot)})
	}
	if v.ABIAttributed != nil {
		provenance := ""
		if v.ABIAttributed.ReceiverProvenance != nil {
			provenance = ", receiver_provenance=" + *v.ABIAttributed.ReceiverProvenance
		}
		out = append(out, explainLine{"abi attributed", fmt.Sprintf("%s slot %d via %s (%s%s)",
			v.ABIAttributed.TableVA, v.ABIAttributed.Slot, v.ABIAttributed.Rule,
			v.ABIAttributed.Confidence, provenance)})
	}
	for _, a := range v.TriageAddresses {
		out = append(out, explainLine{"triage address", a})
	}
	return out
}

func semanticsLines(p *semantic.Passport) []explainLine {
	if !p.Semantics.IsAvailable() {
		return nil
	}
	s := p.Semantics.Deref()
	var out []explainLine
	out = append(out, explainLine{"classification", orUnknownPtr(s.Classification)})
	out = append(out, explainLine{"semantic_status", orUnknownPtr(s.Status)})
	if len(s.Confidence) > 0 {
		axes := make([]string, 0, len(s.Confidence))
		for k := range s.Confidence {
			axes = append(axes, k)
		}
		sort.Strings(axes)
		for _, k := range axes {
			out = append(out, explainLine{"confidence." + k, axisValue(s.Confidence[k])})
		}
	}
	for _, e := range s.Evidence {
		out = append(out, explainLine{"evidence[" + e.Class + "]", e.Claim + "  {" + e.Source + "}"})
	}
	return out
}

func reconstructionLines(p *semantic.Passport) []explainLine {
	if !p.Reconstruction.IsAvailable() {
		return nil
	}
	r := p.Reconstruction.Deref()
	var out []explainLine
	out = append(out, explainLine{"package", orUnknownPtr(r.Package)})
	out = append(out, explainLine{"status", orUnknownPtr(r.Status)})
	out = append(out, explainLine{"review", orUnknownPtr(r.ReviewStatus)})
	out = append(out, explainLine{"integration", orUnknownPtr(r.IntegrationStatus)})
	out = append(out, explainLine{"promoted", string(r.Promoted)})
	if len(r.GeneratedSource) > 0 {
		out = append(out, explainLine{"generated_source", strings.Join(r.GeneratedSource, ", ")})
	}
	out = append(out, explainLine{"runtime", fmt.Sprintf("gated=%s validated=%d", orUnknownBool(r.RuntimeGated), intOrZero(r.RuntimeValidated))})
	return out
}

// ---- stats / validate -----------------------------------------------------

func runStats(args []string, env Env) int {
	fs := flag.NewFlagSet("stats", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	snapPath := fs.String("snapshot", env.SnapshotPath, "snapshot path")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	if err := fs.Parse(args); err != nil {
		return ExitUsage
	}
	ix, code := load(args, *snapPath, *root, env)
	if ix == nil {
		return code
	}
	d := ix.Data()
	counts := d.Recount()
	if *asJSON {
		if err := writeJSON(env.Stdout, map[string]any{
			"binary_sha256":   d.Metadata.Binary.SHA256,
			"image_base":      d.Metadata.Binary.ImageBase,
			"schema":          d.Metadata.Schema,
			"content_sha256":  d.Metadata.ContentSHA256,
			"snapshot_path":   d.Path,
			"snapshot_bytes":  d.Size(),
			"functions":       ix.Len(),
			"indexed_names":   ix.SymbolCount(),
			"ambiguous_names": ix.AmbiguousNameCount(),
			"counts":          counts,
			"export":          d.Metadata.Export,
			"absent_inputs":   d.Metadata.AbsentInputs,
		}); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	fmt.Fprintf(env.Stdout, "snapshot        %s\n", d.Path)
	fmt.Fprintf(env.Stdout, "schema          %s\n", d.Metadata.Schema)
	fmt.Fprintf(env.Stdout, "binary_sha256   %s\n", d.Metadata.Binary.SHA256)
	fmt.Fprintf(env.Stdout, "image_base      %s\n", d.Metadata.Binary.ImageBase)
	fmt.Fprintf(env.Stdout, "program         %s %s\n", d.Metadata.Binary.Program, d.Metadata.Binary.Version)
	fmt.Fprintf(env.Stdout, "content_sha256  %s\n", d.Metadata.ContentSHA256)
	fmt.Fprintf(env.Stdout, "bytes           %d\n", d.Size())
	fmt.Fprintf(env.Stdout, "functions       %d\n", counts.Functions)
	fmt.Fprintf(env.Stdout, "indexed names   %d (%d shared by more than one function)\n",
		ix.SymbolCount(), ix.AmbiguousNameCount())
	fmt.Fprintf(env.Stdout, "\ncoverage\n")
	rows := []struct {
		name string
		n    int
	}{
		{"sdk identities", counts.WithSDKName},
		{"abi data (convention stated)", counts.WithABIData},
		{"abi UNKNOWN (convention null)", counts.WithUnknownABI},
		{"receiver present", counts.WithReceiver},
		{"receiver UNKNOWN (present=null)", counts.WithReceiverUnknown},
		{"vtable memberships", counts.WithVTableMembership},
		{"vtable ABI-attributed", counts.WithVTableAttributed},
		{"subsystem", counts.WithSubsystem},
		{"RenderWare role", counts.WithRenderwareRole},
		{"semantic classification", counts.WithSemantics},
		{"reconstruction package", counts.WithReconstruction},
		{"promoted", counts.WithPromoted},
		{"validation report", counts.WithValidation},
		{"evidence pack", counts.WithEvidencePack},
		{"globals", counts.WithGlobals},
		{"types", counts.WithTypes},
		{"callers", counts.WithCallers},
		{"callees", counts.WithCallees},
		{"refuted identities", counts.RefutedIdentities},
		{"recorded interior resolutions", counts.ResolvedInteriorVAs},
		{"attached stray evidence packs", counts.AttachedStrayPacks},
	}
	for _, r := range rows {
		fmt.Fprintf(env.Stdout, "  %-32s %7d  (%s)\n", r.name, r.n, pct(r.n, counts.Functions))
	}
	e := d.Metadata.Export
	fmt.Fprintf(env.Stdout, "\nexport notes\n")
	fmt.Fprintf(env.Stdout, "  %-32s %7d\n", "evidence pack dirs read", e.EvidencePackDirsRead)
	fmt.Fprintf(env.Stdout, "  %-32s %7d\n", "packs attached to an entry", counts.AttachedStrayPacks)
	fmt.Fprintf(env.Stdout, "  %-32s %7d\n", "orphan packs (no body)", e.OrphanEvidencePacks)
	for _, p := range e.OrphanEvidencePackPaths {
		fmt.Fprintf(env.Stdout, "      %s\n", p)
	}
	fmt.Fprintf(env.Stdout, "\nexplicitly unavailable fact groups\n")
	fmt.Fprintf(env.Stdout, "  %-32s %7d  of %d groups (%s)\n",
		"state=unavailable with a reason", counts.ExplicitlyUnavailable,
		counts.TotalFactGroups, pct(counts.ExplicitlyUnavailable, counts.TotalFactGroups))
	if len(d.Metadata.AbsentInputs) > 0 {
		fmt.Fprintf(env.Stdout, "\nauthoritative inputs absent from the exporting checkout\n")
		for _, a := range d.Metadata.AbsentInputs {
			fmt.Fprintf(env.Stdout, "  %s\n    %s\n", a.Path, a.Reason)
		}
	}
	return ExitOK
}

func runValidate(args []string, env Env) int {
	fs := flag.NewFlagSet("validate", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	snapPath := fs.String("snapshot", env.SnapshotPath, "snapshot path")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	if err := fs.Parse(args); err != nil {
		return ExitUsage
	}
	ix, code := load(args, *snapPath, *root, env)
	if ix == nil {
		return code
	}
	d := ix.Data()
	problems := d.Verify()
	payload := map[string]any{
		"schema":         d.Metadata.Schema,
		"snapshot_path":  d.Path,
		"binary_sha256":  d.Metadata.Binary.SHA256,
		"image_base":     d.Metadata.Binary.ImageBase,
		"content_sha256": d.Metadata.ContentSHA256,
		"functions":      ix.Len(),
		"ok":             len(problems) == 0,
		"problems":       nonNilProblems(problems),
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
	} else {
		fmt.Fprintf(env.Stdout, "schema          %s\n", d.Metadata.Schema)
		fmt.Fprintf(env.Stdout, "binary_sha256   %s\n", d.Metadata.Binary.SHA256)
		fmt.Fprintf(env.Stdout, "image_base      %s\n", d.Metadata.Binary.ImageBase)
		fmt.Fprintf(env.Stdout, "content_sha256  %s (verified over %d record lines)\n", d.Metadata.ContentSHA256, len(d.Order))
		fmt.Fprintf(env.Stdout, "functions       %d, canonical VAs unique and ascending\n", len(d.Order))
		if len(problems) == 0 {
			fmt.Fprintf(env.Stdout, "result          OK\n")
		} else {
			fmt.Fprintf(env.Stdout, "result          %d problem(s)\n", len(problems))
			for _, p := range problems {
				fmt.Fprintf(env.Stdout, "  %s\n", p)
			}
		}
	}
	if len(problems) > 0 {
		return ExitCorruptSnapshot
	}
	return ExitOK
}

func nonNilProblems(in []string) []string {
	if in == nil {
		return []string{}
	}
	return in
}

// ---- shared helpers -------------------------------------------------------

// DefaultSnapshotRel is the snapshot path relative to the OpenSpore root.
const DefaultSnapshotRel = "knowledge/semantic/" + semantic.SnapshotFile

func defaultSnapshotPath(root string) string {
	return filepath.Join(root, filepath.FromSlash(DefaultSnapshotRel))
}

func resolveRoot(root string) (string, error) {
	if root != "" {
		abs, err := filepath.Abs(root)
		if err != nil {
			return "", err
		}
		if !openspore.DirExists(abs) {
			return "", fmt.Errorf("root %s is not a directory", abs)
		}
		return abs, nil
	}
	return openspore.ResolveRoot("")
}

func load(args []string, snapPath, root string, env Env) (*index.Index, int) {
	r, err := resolveRoot(root)
	if err != nil {
		if env.SnapshotPath != "" {
			return nil, fail(env, ExitUnavailable, "snapshot_unavailable", err)
		}
		return nil, fail(env, ExitUnavailable, "root_unavailable", err)
	}
	path := snapPath
	if path == "" {
		path = defaultSnapshotPath(r)
	}
	if !filepath.IsAbs(path) {
		path = filepath.Join(r, path)
	}
	data, err := snapshot.Load(path, env.RequireSHA)
	if err != nil {
		return nil, fail(env, classifyErrorCode(err), classifyLoadError(err), err)
	}
	return index.New(data), ExitOK
}

func classifyLoadError(err error) string {
	switch {
	case errors.Is(err, snapshot.ErrMissing):
		return "snapshot_not_found"
	case errors.Is(err, snapshot.ErrSchema):
		return "unsupported_schema"
	case errors.Is(err, snapshot.ErrBinaryMismatch):
		return "binary_mismatch"
	default:
		return "corrupted_snapshot"
	}
}

func classifyErrorCode(err error) int {
	switch {
	case errors.Is(err, snapshot.ErrMissing):
		return ExitUnavailable
	case errors.Is(err, snapshot.ErrSchema):
		return ExitUnsupportedSchema
	case errors.Is(err, snapshot.ErrBinaryMismatch):
		return ExitBinaryMismatch
	default:
		return ExitCorruptSnapshot
	}
}

func fail(env Env, code int, kind string, err error) int {
	fmt.Fprintf(env.Stderr, "spore-semantic: %s: %v\n", kind, err)
	return code
}

func writeJSON(w io.Writer, v any) error {
	enc := json.NewEncoder(w)
	enc.SetEscapeHTML(false)
	enc.SetIndent("", "  ")
	return enc.Encode(v)
}

func pct(n, total int) string {
	if total == 0 {
		return "n/a"
	}
	return fmt.Sprintf("%.1f%%", 100*float64(n)/float64(total))
}

// returnTypeText renders abi_infer's return.type. The engine's own invariant is
// that return.type is ALWAYS null: it classifies the register's class and the
// width evidence, and declines to name a type. Printing "UNKNOWN" there would
// suggest OpenSpore failed to work out a type, which is the opposite of what
// the record says.
func returnTypeText(p *string) string {
	if p == nil {
		return "null by contract (the ABI engine classifies register class and width, and never names a type)"
	}
	return *p
}

// axisValue renders a semantic confidence value. The axes are mixed: a rung
// name is rendered bare, a numeric score keeps its digits. Neither is coerced
// into the other.
func axisValue(raw json.RawMessage) string {
	text := strings.TrimSpace(string(raw))
	if text == "" {
		return ""
	}
	if unquoted, err := strconv.Unquote(text); err == nil {
		return unquoted
	}
	return text
}

func firstName(p *semantic.Passport) string {
	if p.Names.SDKName != nil && *p.Names.SDKName != "" {
		return *p.Names.SDKName
	}
	if p.Names.NormalizedSymbol != nil && *p.Names.NormalizedSymbol != "" {
		return *p.Names.NormalizedSymbol
	}
	return p.Names.GhidraName
}

func orUnknown(s string) string {
	if s == "" {
		return "UNKNOWN"
	}
	return s
}

func orUnknownPtr(p *string) string {
	if p == nil || *p == "" {
		return "UNKNOWN"
	}
	return *p
}

func orUnknownInt(p *int) string {
	if p == nil {
		return "UNKNOWN"
	}
	return fmt.Sprintf("%d", *p)
}

func orUnknownBool(p *bool) string {
	if p == nil {
		return "UNKNOWN"
	}
	return fmt.Sprintf("%t", *p)
}

func intOrZero(p *int) int {
	if p == nil {
		return 0
	}
	return *p
}

func deref(p *string) string {
	if p == nil {
		return "UNKNOWN"
	}
	return *p
}

func previewList(in []string, max int) string {
	if len(in) == 0 {
		return ""
	}
	if len(in) <= max {
		return strings.Join(in, " ")
	}
	return fmt.Sprintf("%s ... (%d more)", strings.Join(in[:max], " "), len(in)-max)
}

func short(sha string) string {
	if len(sha) > 16 {
		return sha[:16]
	}
	return sha
}
