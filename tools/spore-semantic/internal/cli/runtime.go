package cli

import (
	"errors"
	"flag"
	"fmt"
	"io"
	"path/filepath"
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/index"
	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
)

// shortSHA abbreviates a digest for display. The full value is always present in
// the JSON; the abbreviation is only ever a terminal-width convenience.
func shortSHA(s string) string {
	if len(s) > 16 {
		return s[:16]
	}
	return s
}

// This file is the `spore-semantic runtime` namespace: the read-only consumer
// side of the exchange.
//
// The separation it enforces is architectural, not stylistic:
//
//   - an overlay is LOADED and READ. Nothing in this file writes to a snapshot,
//     an evidence pack, the knowledge index, a validation report or a promotion
//     marker, and there is no code path that could;
//   - the static snapshot is OPTIONAL for every runtime command. A consumer with
//     an overlay and no OpenSpore checkout can validate, join-by-requested-VA,
//     frontier and stats it. Nothing here needs the checkout to exist, and the
//     reverse dependency does not exist either: spore-recomp never needs this
//     tool.
//
// There is deliberately no `runtime merge` that writes a file. A command named
// "merge" invites a caller to produce a combined artifact and then trust it as
// one; the join in `runtime lookup` and `runtime frontier` is a VIEW over two
// artifacts that stay separate on disk, which is the property that keeps a
// runtime observation from ever becoming a static fact.

// ExitRuntimeImageBase is the exit code for an overlay that carries the right
// binary digest but disagrees about the image base.
//
// It is separate from ExitBinaryMismatch because the two are different defects
// with different fixes: a SHA mismatch means the producer analysed a different
// binary, while an image-base mismatch means it analysed the right binary at a
// different load address, which makes every address in the overlay mean
// something other than what a static address of the same value means.
const ExitRuntimeImageBase = 9

// repeatString collects a flag that may be given more than once, for --va.
type repeatString []string

func (r *repeatString) String() string { return strings.Join(*r, ",") }
func (r *repeatString) Set(v string) error {
	*r = append(*r, v)
	return nil
}

// runRuntime dispatches a `runtime` subcommand.
func runRuntime(args []string, env Env) int {
	if len(args) == 0 {
		usageRuntime(env.Stderr)
		return ExitUsage
	}
	switch args[0] {
	case "validate":
		return runRuntimeValidate(args[1:], env)
	case "lookup":
		return runRuntimeLookup(args[1:], env)
	case "frontier":
		return runRuntimeFrontier(args[1:], env)
	case "stats":
		return runRuntimeStats(args[1:], env)
	case "import-recomp":
		return runRuntimeImportRecomp(args[1:], env)
	case "census":
		return runRuntimeCensus(args[1:], env)
	case "help", "-h", "--help":
		usageRuntime(env.Stdout)
		return ExitOK
	default:
		fmt.Fprintf(env.Stderr, "spore-semantic runtime: unknown subcommand %q\n\n", args[0])
		usageRuntime(env.Stderr)
		return ExitUsage
	}
}

func usageRuntime(w io.Writer) {
	fmt.Fprint(w, `spore-semantic runtime -- consume EXTERNAL runtime observations

An overlay is a separate artifact keyed by binary_sha256 + canonical VA. It is
read-only data: nothing here writes to the static snapshot, and no runtime fact
can change a static verdict. The static snapshot stays independently consumable.

usage:
  spore-semantic runtime validate        [--overlay PATH] [--json]
  spore-semantic runtime lookup   <VA>    [--overlay PATH] [--snapshot PATH] [--json]
  spore-semantic runtime frontier         [--overlay PATH] [--census PATH]
                                         [--snapshot PATH] [--va VA]... [--json]
  spore-semantic runtime stats            [--overlay PATH] [--snapshot PATH] [--json]
  spore-semantic runtime import-recomp --report PATH [--out PATH]
                                         [--artifact ID] [--version V]
  spore-semantic runtime census           [--root DIR] [--out PATH] [--json]

There is no "runtime merge". The join is a VIEW over two artifacts that stay
separate on disk, so no combined artifact can be mistaken for one source of truth.

The snapshot is optional everywhere. With no OpenSpore checkout, --overlay alone
validates, joins by requested VA, frontiers and stats. An overlay is refused when
its binary_sha256 differs from the one you require (exit 4) or its image_base
differs (exit 9).

Exit codes: shared with the top-level tool -- 0 ok, 1 usage, 2 unknown address
(statically and at runtime), 4 binary mismatch, 5 corrupted overlay,
6 unsupported schema, 7 overlay/census/snapshot unavailable, 9 image base
mismatch.
`)
}

// ---- shared loading -------------------------------------------------------

// loadOverlay reads and verifies an overlay. It never touches the OpenSpore
// checkout, which is what makes an overlay consumable by a project that has the
// overlay and nothing else.
func loadOverlay(path, requireSHA string, env Env) (*runtime.Overlay, int) {
	if path == "" {
		fmt.Fprintln(env.Stderr, "spore-semantic runtime: --overlay is required")
		return nil, ExitUsage
	}
	ov, err := runtime.Load(path, requireSHA, 0)
	if err != nil {
		return nil, fail(env, classifyRuntimeError(err), classifyRuntimeLoadError(err), err)
	}
	return ov, ExitOK
}

func classifyRuntimeError(err error) int {
	switch {
	case errors.Is(err, runtime.ErrMissing):
		return ExitUnavailable
	case errors.Is(err, runtime.ErrSchema):
		return ExitUnsupportedSchema
	case errors.Is(err, runtime.ErrBinaryMismatch):
		return ExitBinaryMismatch
	case errors.Is(err, runtime.ErrImageBaseMismatch):
		return ExitRuntimeImageBase
	default:
		return ExitCorruptSnapshot
	}
}

func classifyRuntimeLoadError(err error) string {
	switch {
	case errors.Is(err, runtime.ErrMissing):
		return "overlay_not_found"
	case errors.Is(err, runtime.ErrSchema):
		return "unsupported_schema"
	case errors.Is(err, runtime.ErrBinaryMismatch):
		return "binary_mismatch"
	case errors.Is(err, runtime.ErrImageBaseMismatch):
		return "image_base_mismatch"
	default:
		return "corrupted_overlay"
	}
}

// loadIndexBestEffort loads the static snapshot when one is reachable, and
// reports whether it was.
//
// A nil index is a supported state, not a failure: it means the joined view has
// no static half, and every field derived from static knowledge is then null
// rather than zero. Failing the command instead would make an overlay
// unusable by a consumer that only has an overlay.
func loadIndexBestEffort(snapPath, root string, env Env) (*index.Index, *snapshotInfo) {
	// An ABSOLUTE snapshot path needs no checkout at all. That is what lets a
	// consumer join an overlay with a snapshot it shipped itself, in a directory
	// that is not an OpenSpore tree.
	path := snapPath
	if path != "" && filepath.IsAbs(path) {
		return loadIndexAt(path, env)
	}
	r, err := resolveRoot(root)
	if err != nil {
		return nil, &snapshotInfo{Available: false, Path: snapPath, Reason: err.Error()}
	}
	if path == "" {
		path = defaultSnapshotPath(r)
	}
	if !filepath.IsAbs(path) {
		path = filepath.Join(r, path)
	}
	return loadIndexAt(path, env)
}

func loadIndexAt(path string, env Env) (*index.Index, *snapshotInfo) {
	data, err := snapshotLoad(path, env.RequireSHA)
	if err != nil {
		return nil, &snapshotInfo{Available: false, Path: path, Reason: err.Error()}
	}
	return index.New(data), &snapshotInfo{
		Available:    true,
		Path:         data.Path,
		BinarySHA256: data.Metadata.Binary.SHA256,
		ImageBase:    data.Metadata.Binary.ImageBase,
		Schema:       data.Metadata.Schema,
		ContentSHA:   data.Metadata.ContentSHA256,
		Functions:    len(data.Order),
	}
}

type snapshotInfo struct {
	Available    bool   `json:"available"`
	Path         string `json:"path,omitempty"`
	BinarySHA256 string `json:"binary_sha256,omitempty"`
	ImageBase    string `json:"image_base,omitempty"`
	Schema       string `json:"schema,omitempty"`
	ContentSHA   string `json:"content_sha256,omitempty"`
	Functions    int    `json:"functions,omitempty"`
	Reason       string `json:"unavailable_reason,omitempty"`
}

// crossCheckBinary reports an overlay/snapshot identity disagreement.
//
// It is a WARNING, not a refusal: the two artifacts may legitimately describe
// different runs of the same binary, and the command still answers. But it is
// never silent, because joining observations of one binary onto a passport for
// another is the failure this whole package exists to make impossible to do by
// accident.
func crossCheckBinary(ov *runtime.Overlay, snap *snapshotInfo, env Env) string {
	if ov == nil || snap == nil || !snap.Available {
		return ""
	}
	if ov.Metadata.Binary.SHA256 == snap.BinarySHA256 {
		return ""
	}
	msg := fmt.Sprintf("overlay describes binary %s but the snapshot describes %s; the joined view mixes two binaries and its static half does not apply to its runtime half",
		shortSHA(ov.Metadata.Binary.SHA256), shortSHA(snap.BinarySHA256))
	fmt.Fprintf(env.Stderr, "spore-semantic runtime: warning: %s\n", msg)
	return msg
}

// ---- runtime validate -----------------------------------------------------

func runRuntimeValidate(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime validate", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	overlay := fs.String("overlay", "", "runtime overlay path")
	imageBase := fs.String("require-image-base", "", "refuse an overlay whose image_base differs")
	if _, err := parseArgs(fs, args); err != nil {
		return ExitUsage
	}
	ov, code := loadOverlay(*overlay, env.RequireSHA, env)
	if ov == nil {
		return code
	}
	var wantBase semantic.Addr
	if *imageBase != "" {
		a, err := semantic.ParseAddr(*imageBase, 0)
		if err != nil {
			return fail(env, ExitUsage, "invalid_image_base", err)
		}
		wantBase = a
		if got := ov.ImageBase(); got != wantBase {
			err := fmt.Errorf("%w: overlay declares image base %s, caller requires %s",
				runtime.ErrImageBaseMismatch, ov.Metadata.Binary.ImageBase, wantBase.String())
			return fail(env, ExitRuntimeImageBase, classifyRuntimeLoadError(err), err)
		}
	}

	problems := ov.Verify()
	problems = append(problems, verifyObservationVocabulary(ov)...)
	payload := map[string]any{
		"schema":         ov.Metadata.Schema,
		"overlay_path":   ov.Path,
		"binary_sha256":  ov.Metadata.Binary.SHA256,
		"image_base":     ov.Metadata.Binary.ImageBase,
		"producer":       ov.Metadata.Producer,
		"content_sha256": ov.Metadata.ContentSHA256,
		"entries":        ov.Len(),
		"overlay_bytes":  ov.Bytes,
		"ok":             len(problems) == 0,
		"problems":       orEmptyProblems(problems),
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
	} else {
		fmt.Fprintf(env.Stdout, "schema          %s\n", ov.Metadata.Schema)
		fmt.Fprintf(env.Stdout, "overlay         %s\n", ov.Path)
		fmt.Fprintf(env.Stdout, "binary_sha256   %s\n", ov.Metadata.Binary.SHA256)
		fmt.Fprintf(env.Stdout, "image_base      %s\n", ov.Metadata.Binary.ImageBase)
		fmt.Fprintf(env.Stdout, "producer        %s / %s %s\n", ov.Metadata.Producer.Project,
			ov.Metadata.Producer.Name, ov.Metadata.Producer.Version)
		fmt.Fprintf(env.Stdout, "artifact        %s   (portable identifier, never a filesystem path)\n", ov.Metadata.Producer.Artifact)
		if ov.Metadata.Producer.SourceSchema != "" {
			fmt.Fprintf(env.Stdout, "source_schema   %s\n", ov.Metadata.Producer.SourceSchema)
		}
		if ov.Metadata.ContentSHA256 != "" {
			fmt.Fprintf(env.Stdout, "content_sha256  %s (verified over %d entry lines)\n", ov.Metadata.ContentSHA256, ov.Len())
		} else {
			fmt.Fprintf(env.Stdout, "content_sha256  not stated by the producer; entry-line integrity unverified\n")
		}
		fmt.Fprintf(env.Stdout, "entries         %d, requested VAs unique and strictly ascending\n", ov.Len())
		fmt.Fprintf(env.Stdout, "observation vocabulary %s\n", runtime.ObservationKinds)
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

// verifyObservationVocabulary re-checks the closed vocabularies on a loaded
// overlay. The loader already enforces them, so this exists as a NAMED report:
// "validate" should say which vocabularies it checked, not only that nothing was
// wrong.
func verifyObservationVocabulary(ov *runtime.Overlay) []string {
	for _, addr := range ov.Order {
		e := ov.Entries[addr]
		if !runtime.KnownCanonicalization(e.Canonicalization) {
			return []string{fmt.Sprintf("%s: canonicalization %q is outside the closed vocabulary", e.RequestedVA, e.Canonicalization)}
		}
		for _, ob := range e.Observations {
			if !runtime.KnownObservationKind(ob.Kind) {
				return []string{fmt.Sprintf("%s: observation kind %q is outside the closed vocabulary", e.RequestedVA, ob.Kind)}
			}
		}
	}
	return nil
}

func orEmptyProblems(in []string) []string {
	if in == nil {
		return []string{}
	}
	return in
}

// ---- runtime lookup -------------------------------------------------------

// runtimeIdentityOut reports the identity question, and answers it from BOTH
// sides without preferring either.
//
// The producer's canonical_va is a CLAIM by an external party. OpenSpore's
// resolution is AUTHORITY. When they disagree the disagreement is the finding,
// so it is reported explicitly instead of one side silently overwriting the
// other -- and OpenSpore's static identity is never edited to match a producer.
type runtimeIdentityOut struct {
	RequestedVA      string            `json:"requested_va"`
	CanonicalVA      *string           `json:"canonical_va"`
	Canonicalization string            `json:"canonicalization"`
	StaticStatus     string            `json:"static_status"`
	Offset           int               `json:"offset,omitempty"`
	RangeEnd         string            `json:"range_end,omitempty"`
	ProducerClaim    *producerClaimOut `json:"producer_claim"`
	Disagreement     *string           `json:"disagreement"`
}

type producerClaimOut struct {
	CanonicalVA      *string `json:"canonical_va"`
	Canonicalization string  `json:"canonicalization"`
}

type runtimeLookupOut struct {
	BinarySHA256 string             `json:"binary_sha256"`
	ImageBase    string             `json:"image_base"`
	RequestedVA  string             `json:"requested_va"`
	Identity     runtimeIdentityOut `json:"identity"`
	// Static is null when no snapshot was reachable, or when OpenSpore has no
	// passport for this VA. Its shape is exactly the existing `lookup` output:
	// this is the same static projection, not a second one.
	Static  *lookupResultOut        `json:"static"`
	Runtime *runtime.RuntimeSummary `json:"runtime"`
	// Interpretation is the compact reading. It never contains a verdict change.
	Interpretation runtime.Interpretation `json:"interpretation"`
	// RelevantKinds maps a recorded static blocker dimension to the runtime
	// observation categories the overlay actually holds for it. It is a
	// PRIORITISATION map, not a resolution map: it says which observations a
	// human should read first, and nothing more.
	RelevantKinds map[string][]runtime.ObservationKind `json:"relevant_kinds,omitempty"`
	Overlay       overlayInfo                          `json:"overlay"`
	Snapshot      snapshotInfo                         `json:"snapshot"`
	// VerdictUnchanged is always the same literal. A joined view that omitted it
	// would let a reader infer that a verdict moved by the mere presence of the
	// runtime half.
	VerdictUnchanged string `json:"verdict_unchanged"`
}

type overlayInfo struct {
	Path         string           `json:"path"`
	Schema       string           `json:"schema"`
	BinarySHA256 string           `json:"binary_sha256"`
	ImageBase    string           `json:"image_base"`
	Producer     runtime.Producer `json:"producer"`
	Entries      int              `json:"entries"`
}

func runRuntimeLookup(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime lookup", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	overlay := fs.String("overlay", "", "runtime overlay path")
	snapPath := fs.String("snapshot", env.SnapshotPath, "static snapshot path (optional)")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	rest, err := parseArgs(fs, args)
	if err != nil {
		return ExitUsage
	}
	if len(rest) != 1 {
		fmt.Fprintln(env.Stderr, "spore-semantic runtime lookup: exactly one VA is required")
		return ExitUsage
	}
	ov, code := loadOverlay(*overlay, env.RequireSHA, env)
	if ov == nil {
		return code
	}
	ix, snap := loadIndexBestEffort(*snapPath, *root, env)
	va, err := semantic.ParseAddr(rest[0], ov.ImageBase())
	if err != nil {
		return fail(env, ExitUsage, "invalid_address", err)
	}
	crossCheckBinary(ov, snap, env)

	canon, canonKind, staticStatus, offset, end := runtime.ResolveIdentity(ix, va)
	rt := ov.Summarize(va)
	entries := ov.EntriesFor(va)

	if ix != nil {
		if res := ix.Resolve(va); res.Passport != nil {
			// Exactly the existing static projection, so the joined view cannot
			// disagree with `spore-semantic lookup` about the static half.
			return emitRuntimeLookup(env, ov, snap, *asJSON, va, canon, canonKind, staticStatus, offset, end, rt, entries,
				lookupResult(ix, res))
		}
	}
	if rt == nil {
		// Neither half knows this address. That is a real "unknown", and it
		// exits 2 so a caller scripting on the exit code is not handed an empty
		// object that looks like an answer.
		msg := fmt.Sprintf("unknown address: %s has no static passport in binary %s and no runtime overlay entry; it is neither a function entry nor a runtime observation",
			va.String(), shortSHA(ov.Metadata.Binary.SHA256))
		if *asJSON {
			_ = writeJSON(env.Stdout, map[string]any{
				"error": "unknown_address", "requested_va": va.String(),
				"binary_sha256": ov.Metadata.Binary.SHA256, "message": msg,
			})
		} else {
			fmt.Fprintln(env.Stderr, "spore-semantic runtime: "+msg)
		}
		return ExitUnknownFunction
	}
	// Runtime knows it, OpenSpore does not. This is the discrepancy the bridge
	// exists to surface, so it exits 0 with a complete record rather than 2.
	return emitRuntimeLookup(env, ov, snap, *asJSON, va, canon, canonKind, staticStatus, offset, end, rt, entries, nil)
}

func emitRuntimeLookup(env Env, ov *runtime.Overlay, snap *snapshotInfo, asJSON bool,
	va semantic.Addr, canon *string, canonKind, staticStatus string, offset int, end semantic.Addr,
	rt *runtime.RuntimeSummary, entries []*runtime.Entry, static *lookupResultOut) int {

	ident := runtimeIdentityOut{
		RequestedVA:      va.String(),
		CanonicalVA:      canon,
		Canonicalization: canonKind,
		StaticStatus:     staticStatus,
		Offset:           offset,
		ProducerClaim:    &producerClaimOut{},
	}
	if end != 0 {
		ident.RangeEnd = end.String()
	}
	var producerCanonicalizations []string
	for _, e := range entries {
		ident.ProducerClaim.CanonicalVA = e.CanonicalVA
		producerCanonicalizations = append(producerCanonicalizations, e.Canonicalization)
	}
	if len(producerCanonicalizations) == 1 {
		ident.ProducerClaim.Canonicalization = producerCanonicalizations[0]
	} else if len(producerCanonicalizations) > 1 {
		ident.ProducerClaim.Canonicalization = strings.Join(sortedUnique(producerCanonicalizations), ",")
	}

	// The disagreement check compares the producer's CLAIM with OpenSpore's
	// authority. It is informational: neither side is edited.
	switch {
	case ident.ProducerClaim.CanonicalVA == nil:
		// No claim means no disagreement. The absence of a claim is already
		// visible in producer_claim, and OpenSpore's own rule is already visible
		// in canonicalization and static_status; restating them here as a
		// "disagreement" would invent a conflict that does not exist.
	case ident.CanonicalVA == nil:
		ident.Disagreement = strPtr(fmt.Sprintf(
			"the producer claims canonical VA %s, but OpenSpore's canonical identity places %s outside every known function body; the claim is reported, not adopted",
			*ident.ProducerClaim.CanonicalVA, va.String()))
	case !strings.EqualFold(*ident.ProducerClaim.CanonicalVA, *ident.CanonicalVA):
		ident.Disagreement = strPtr(fmt.Sprintf(
			"the producer claims canonical VA %s; OpenSpore's canonical identity resolves %s to %s; the static identity is authoritative and was not changed",
			*ident.ProducerClaim.CanonicalVA, va.String(), *ident.CanonicalVA))
	}

	var blockers []runtime.Blocker
	if static != nil {
		// The blocker list is read from the SAME record the static half shows, so
		// a joined view and `spore-semantic explain` can never disagree about it.
		blockers = runtime.StaticBlockers(staticPassport(static))
	}
	rel := map[string][]runtime.ObservationKind{}
	for _, b := range blockers {
		var hits []runtime.ObservationKind
		for _, e := range entries {
			if ok, h := runtime.Relevance(b, e); ok {
				hits = append(hits, h...)
			}
		}
		if len(hits) > 0 {
			rel[b.Dimension] = sortedUniqueKinds(hits)
		}
	}

	out := &runtimeLookupOut{
		BinarySHA256:     ov.Metadata.Binary.SHA256,
		ImageBase:        ov.Metadata.Binary.ImageBase,
		RequestedVA:      va.String(),
		Identity:         ident,
		Static:           static,
		Runtime:          rt,
		Interpretation:   runtime.Interpret(staticStatus, blockers, rt, rel),
		RelevantKinds:    rel,
		Overlay:          overlayInfo{Path: ov.Path, Schema: ov.Metadata.Schema, BinarySHA256: ov.Metadata.Binary.SHA256, ImageBase: ov.Metadata.Binary.ImageBase, Producer: ov.Metadata.Producer, Entries: ov.Len()},
		Snapshot:         derefSnapshot(snap),
		VerdictUnchanged: "no static verdict was modified by this lookup",
	}
	if out.Interpretation.StaticBlockers == nil {
		out.Interpretation.StaticBlockers = []string{}
	}
	if out.Interpretation.RuntimeFacts == nil {
		out.Interpretation.RuntimeFacts = []string{}
	}
	if asJSON {
		if err := writeJSON(env.Stdout, out); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	printRuntimeLookup(env.Stdout, out)
	return ExitOK
}

func printRuntimeLookup(w io.Writer, out *runtimeLookupOut) {
	fmt.Fprintf(w, "%s\n", out.RequestedVA)
	fmt.Fprintf(w, "\nIDENTITY  binary %s  image base %s\n", shortSHA(out.BinarySHA256), out.ImageBase)
	fmt.Fprintf(w, "  requested_va       %s\n", out.Identity.RequestedVA)
	fmt.Fprintf(w, "  canonical_va       %s\n", derefStr(out.Identity.CanonicalVA))
	fmt.Fprintf(w, "  rule               %s\n", out.Identity.Canonicalization)
	fmt.Fprintf(w, "  static_status      %s\n", out.Identity.StaticStatus)
	if out.Identity.RangeEnd != "" {
		fmt.Fprintf(w, "  body               %s .. %s (offset %d)\n", derefStr(out.Identity.CanonicalVA), out.Identity.RangeEnd, out.Identity.Offset)
	}
	if out.Identity.ProducerClaim.CanonicalVA != nil {
		fmt.Fprintf(w, "  producer_claim     %s  (rule %s)\n", *out.Identity.ProducerClaim.CanonicalVA, out.Identity.ProducerClaim.Canonicalization)
	} else {
		fmt.Fprintf(w, "  producer_claim     none stated\n")
	}
	if out.Identity.Disagreement != nil {
		fmt.Fprintf(w, "  disagreement       %s\n", *out.Identity.Disagreement)
	}

	fmt.Fprintf(w, "\nSTATIC  -- what OpenSpore's own artifacts state\n")
	if out.Static == nil {
		fmt.Fprintf(w, "  no static passport. %s\n", staticAbsenceNote(out.Identity.StaticStatus))
		fmt.Fprintf(w, "  This is preserved as a discrepancy, not repaired: OpenSpore does not\n")
		fmt.Fprintf(w, "  manufacture a function record for an address the universe cannot place.\n")
	} else {
		p := out.Static
		name := "UNKNOWN (no name recorded)"
		if p.Names.SDKName != nil {
			name = *p.Names.SDKName
		} else if p.Names.NormalizedSymbol != nil {
			name = *p.Names.NormalizedSymbol
		} else if p.Names.GhidraName != "" {
			name = p.Names.GhidraName
		}
		fmt.Fprintf(w, "  sdk_name           %s\n", name)
		fmt.Fprintf(w, "  size               %d bytes (section %s, thunk=%t)\n", p.Identity.Size, p.Identity.Section, p.Identity.IsThunk)
		fmt.Fprintf(w, "  abi                %s\n", envelopeOneLine(p.ABI.State, p.ABI.EvidenceLevel, p.ABI.Reason))
		if p.ABI.IsAvailable() {
			a := p.ABI.Deref()
			fmt.Fprintf(w, "    convention       %s  verdict=%s\n", orUnknownPtr(a.Convention), orUnknownPtr(a.Verdict))
			if a.Receiver != nil {
				fmt.Fprintf(w, "    receiver         present=%s register=%s\n", a.Receiver.Present, orUnknownPtr(a.Receiver.Register))
			}
			if a.Return != nil {
				fmt.Fprintf(w, "    return           register=%s class=%s confidence=%s\n",
					orUnknownPtr(a.Return.Register), orUnknownPtr(a.Return.RegisterClass), a.Return.Confidence)
			}
		}
		fmt.Fprintf(w, "  vtable             %s\n", envelopeOneLine(p.VTable.State, p.VTable.EvidenceLevel, p.VTable.Reason))
		if p.VTable.IsAvailable() {
			v := p.VTable.Deref()
			if len(v.Memberships) == 0 {
				fmt.Fprintf(w, "    memberships      %s\n", noneRecorded)
			}
			for _, m := range v.Memberships {
				fmt.Fprintf(w, "    membership       %s slot %d\n", m.TableVA, m.Slot)
			}
			if v.ABIAttributed != nil {
				fmt.Fprintf(w, "    abi_attributed   %s slot %d by %s (%s)\n",
					v.ABIAttributed.TableVA, v.ABIAttributed.Slot, v.ABIAttributed.Rule, v.ABIAttributed.Confidence)
			}
		}
		fmt.Fprintf(w, "  globals            %s\n", envelopeOneLine(p.Globals.State, p.Globals.EvidenceLevel, p.Globals.Reason))
		if p.Globals.IsAvailable() && len(p.Globals.Deref()) > 0 {
			for _, g := range p.Globals.Deref() {
				fmt.Fprintf(w, "    %s\n", g)
			}
		}
		fmt.Fprintf(w, "  return_semantics   %s\n", returnSemanticsOneLine(p))
		fmt.Fprintf(w, "  reconstruction     %s\n", reconstructionOneLine(p))
		fmt.Fprintf(w, "  provenance         %d entr(ies)\n", len(p.Provenance))
		for _, pv := range p.Provenance {
			fmt.Fprintf(w, "    %-9s %-18s %s\n", pv.Mode, pv.SourceClass, pv.Ref)
		}
	}

	fmt.Fprintf(w, "\nRUNTIME  -- what %s observed\n", runtimeProducerLabel(out.Overlay.Producer))
	if out.Runtime == nil {
		fmt.Fprintf(w, "  the overlay records nothing for this address\n")
	} else {
		rt := out.Runtime
		fmt.Fprintf(w, "  reached            %s\n", rt.Reached)
		if rt.EntryCount != nil {
			fmt.Fprintf(w, "  entry_count        %d\n", *rt.EntryCount)
		} else {
			fmt.Fprintf(w, "  entry_count        null (the producer did not count; this is NOT a zero)\n")
		}
		if rt.MaxCallDepth != nil {
			fmt.Fprintf(w, "  max_call_depth     %d\n", *rt.MaxCallDepth)
		}
		if rt.FirstReachedFrom != nil {
			fmt.Fprintf(w, "  first_reached_from %s\n", *rt.FirstReachedFrom)
		}
		fmt.Fprintf(w, "  runtime_callers    %d\n", len(rt.RuntimeCallers))
		for _, c := range rt.RuntimeCallers {
			fn := derefStr(c.CallerFunctionVA)
			if fn == "" {
				fn = "(function not identified by the producer)"
			}
			fmt.Fprintf(w, "    %s  from %s@%s\n", c.CallsiteVA, fn, c.CallsiteVA)
		}
		fmt.Fprintf(w, "  runtime_targets    %d\n", len(rt.RuntimeTargets))
		for _, t := range rt.RuntimeTargets {
			fmt.Fprintf(w, "    %s  indirect=%s unresolved=%s %s\n", t.TargetVA, t.Indirect, t.Unresolved, t.Classification)
		}
		fmt.Fprintf(w, "  runtime_imports    %d\n", len(rt.RuntimeImports))
		for _, im := range rt.RuntimeImports {
			fmt.Fprintf(w, "    %s!%s  slot=%s bound=%s reached_count=%s\n",
				im.Module, im.Symbol, derefStr(im.SlotVA), im.Bound, countOrNull(im.ReachedCount))
		}
		fmt.Fprintf(w, "  observations       %d  kinds=%v\n", rt.ObservationCount, rt.ObservationKinds)
		for _, ob := range relevantSample(out) {
			fmt.Fprintf(w, "    %-14s %s\n", ob.Kind, observationOneLine(ob))
		}
		fmt.Fprintf(w, "  provenance\n")
		for _, p := range rt.Provenance {
			fmt.Fprintf(w, "    source_class=%s producer=%s artifact=%s\n", p.SourceClass, p.Producer, p.Artifact)
		}
	}

	fmt.Fprintf(w, "\nINTERPRETATION\n")
	fmt.Fprintf(w, "  static blocker\n")
	if len(out.Interpretation.StaticBlockers) == 0 {
		fmt.Fprintf(w, "    %s\n", "none recorded by any OpenSpore artifact")
	}
	for _, b := range out.Interpretation.StaticBlockers {
		fmt.Fprintf(w, "    %s\n", b)
	}
	fmt.Fprintf(w, "  runtime\n")
	for _, f := range out.Interpretation.RuntimeFacts {
		fmt.Fprintf(w, "    %s\n", f)
	}
	fmt.Fprintf(w, "\n  %s\n", out.VerdictUnchanged)
	fmt.Fprintf(w, "  A runtime observation never upgrades a static verdict here. It is evidence a\n")
	fmt.Fprintf(w, "  human weighs against the machine evidence, under the same proof/falsifier\n")
	fmt.Fprintf(w, "  discipline as any other OpenSpore inference.\n")
}

func staticAbsenceNote(status string) string {
	switch status {
	case runtime.StaticStatusUnknownEntity:
		return "The address is in the static universe's address range but in no known function body -- padding, or a gap between bodies. OpenSpore does not map padding to a function."
	case runtime.StaticStatusAbsent:
		return "No static snapshot was reachable, so no static identity was consulted."
	default:
		return "OpenSpore has no static identity for this address."
	}
}

// relevantSample returns the observations a reader should look at first: those
// in a category this build maps to at least one recorded static blocker. When
// there is no static blocker, every observation is shown, because then none of
// them is more relevant than another.
func relevantSample(out *runtimeLookupOut) []runtime.Observation {
	if out.Runtime == nil {
		return nil
	}
	keep := map[runtime.ObservationKind]bool{}
	for _, hits := range out.RelevantKinds {
		for _, k := range hits {
			keep[k] = true
		}
	}
	var out2 []runtime.Observation
	for _, ob := range out.Runtime.Observations {
		if len(keep) == 0 || keep[ob.Kind] {
			out2 = append(out2, ob)
		}
	}
	if len(out2) > 12 {
		out2 = out2[:12]
	}
	return out2
}

func observationOneLine(o runtime.Observation) string {
	var parts []string
	add := func(format string, args ...any) { parts = append(parts, fmt.Sprintf(format, args...)) }
	if o.CallsiteVA != nil {
		add("callsite=%s", *o.CallsiteVA)
	}
	if o.TargetVA != nil {
		add("target=%s", *o.TargetVA)
	}
	if o.EIP != nil {
		add("eip=%s", *o.EIP)
	}
	if o.ReturnAddress != nil {
		add("return_address=%s", *o.ReturnAddress)
	}
	if o.Module != nil {
		add("%s!%s", *o.Module, derefStr(o.Symbol))
	}
	if o.Indirect == runtime.TriTrue {
		add("indirect=true")
	}
	if o.CallDepth != nil {
		add("depth=%d", *o.CallDepth)
	}
	if o.Register != nil {
		add("%s=%s", *o.Register, derefStr(o.RegisterValue))
	}
	if o.Class != nil {
		add("class=%s", *o.Class)
	}
	if o.StackDeltaBytes != nil {
		add("stack_delta=%d", *o.StackDeltaBytes)
	}
	if o.Detail != "" {
		add("detail=%q", o.Detail)
	}
	return strings.Join(parts, " ")
}

func envelopeOneLine(state string, level semantic.EvidenceLevel, reason string) string {
	if state == semantic.StateAvailable {
		return fmt.Sprintf("available [%s]", level)
	}
	if reason == "" {
		reason = "no reason recorded"
	}
	return fmt.Sprintf("unavailable [%s] %s", level, reason)
}

func returnSemanticsOneLine(p *lookupResultOut) string {
	if p.Reconstruction.IsAvailable() {
		if v := p.Reconstruction.Deref().Validation; v != nil {
			if chk, ok := v.Coverage["RETURN SEMANTICS"]; ok {
				return fmt.Sprintf("validation dimension %s / %s -- %s", chk.Status, chk.Coverage, chk.Detail)
			}
		}
	}
	if p.ABI.IsAvailable() {
		if r := p.ABI.Deref().Return; r != nil {
			return fmt.Sprintf("no adjudicated dimension; derived record says register=%s class=%s confidence=%s",
				orUnknownPtr(r.Register), orUnknownPtr(r.RegisterClass), r.Confidence)
		}
	}
	return "no adjudicated RETURN SEMANTICS dimension and no derived return record"
}

func reconstructionOneLine(p *lookupResultOut) string {
	if !p.Reconstruction.IsAvailable() {
		return fmt.Sprintf("unavailable [%s] %s", p.Reconstruction.EvidenceLevel, p.Reconstruction.Reason)
	}
	r := p.Reconstruction.Deref()
	return fmt.Sprintf("package=%s status=%s promoted=%s runtime_gated=%s",
		orUnknownPtr(r.Package), orUnknownPtr(r.Status), r.Promoted, orUnknownBool(r.RuntimeGated))
}

func runtimeProducerLabel(p runtime.Producer) string {
	if p.Project == "" {
		return "the producer"
	}
	return p.Project
}

func countOrNull(p *int) string {
	if p == nil {
		return "null"
	}
	return fmt.Sprintf("%d", *p)
}

func derefStr(p *string) string {
	if p == nil {
		return "null"
	}
	return *p
}

func strPtr(s string) *string { return &s }

func sortedUnique(in []string) []string {
	seen := map[string]bool{}
	var out []string
	for _, s := range in {
		if seen[s] {
			continue
		}
		seen[s] = true
		out = append(out, s)
	}
	sort.Strings(out)
	return out
}

func sortedUniqueKinds(in []runtime.ObservationKind) []runtime.ObservationKind {
	seen := map[runtime.ObservationKind]bool{}
	var out []runtime.ObservationKind
	for _, s := range in {
		if seen[s] {
			continue
		}
		seen[s] = true
		out = append(out, s)
	}
	sort.Slice(out, func(i, j int) bool { return out[i] < out[j] })
	return out
}

// staticPassport recovers the passport behind an emitted static result, so the
// blocker list is read from the SAME record the static half shows.
func staticPassport(out *lookupResultOut) *semantic.Passport {
	if out == nil {
		return nil
	}
	return &semantic.Passport{
		Identity:       out.Identity,
		Names:          out.Names,
		Classification: out.Mechanical,
		ABI:            out.ABI,
		VTable:         out.VTable,
		Graph:          out.Graph,
		Globals:        out.Globals,
		Types:          out.Types,
		Semantics:      out.Semantics,
		Reconstruction: out.Reconstruction,
		Evidence:       out.Evidence,
		Provenance:     out.Provenance,
	}
}

func derefSnapshot(s *snapshotInfo) snapshotInfo {
	if s == nil {
		return snapshotInfo{Available: false, Reason: "no snapshot was requested"}
	}
	return *s
}
