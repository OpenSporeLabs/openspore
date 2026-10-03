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
	"github.com/openspore/spore-semantic/internal/openspore"
	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/snapshot"
)

// snapshotLoad is a thin alias so this file does not need the snapshot import
// name shadowed by anything.
func snapshotLoad(path, requireSHA string) (*snapshot.Data, error) {
	return snapshot.Load(path, requireSHA)
}

// ---- runtime stats --------------------------------------------------------

func runRuntimeStats(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime stats", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	overlay := fs.String("overlay", "", "runtime overlay path")
	snapPath := fs.String("snapshot", env.SnapshotPath, "static snapshot path (optional)")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	if _, err := parseArgs(fs, args); err != nil {
		return ExitUsage
	}
	ov, code := loadOverlay(*overlay, env.RequireSHA, env)
	if ov == nil {
		return code
	}
	ix, snap := loadIndexBestEffort(*snapPath, *root, env)
	crossCheckBinary(ov, snap, env)
	stats := runtime.ComputeStats(ov, ix)

	payload := map[string]any{
		"overlay":  overlayInfo{Path: ov.Path, Schema: ov.Metadata.Schema, BinarySHA256: ov.Metadata.Binary.SHA256, ImageBase: ov.Metadata.Binary.ImageBase, Producer: ov.Metadata.Producer, Entries: ov.Len()},
		"snapshot": derefSnapshot(snap),
		"analysis": stats,
		"note":     "every number here is a count of things two existing artifacts already state; none is a new authoritative fact",
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	fmt.Fprintf(env.Stdout, "overlay\n")
	fmt.Fprintf(env.Stdout, "  path              %s\n", ov.Path)
	fmt.Fprintf(env.Stdout, "  binary_sha256     %s\n", ov.Metadata.Binary.SHA256)
	fmt.Fprintf(env.Stdout, "  image_base        %s\n", ov.Metadata.Binary.ImageBase)
	fmt.Fprintf(env.Stdout, "  producer          %s / %s %s\n", ov.Metadata.Producer.Project, ov.Metadata.Producer.Name, ov.Metadata.Producer.Version)
	fmt.Fprintf(env.Stdout, "  artifact          %s\n", ov.Metadata.Producer.Artifact)
	fmt.Fprintf(env.Stdout, "\noverlay views  (producer side)\n")
	for _, r := range []struct {
		name string
		n    int
	}{
		{"runtime-observed addresses", stats.Overlay.Entries},
		{"  reached = true", stats.Overlay.Reached},
		{"  reached = false (observed, not reached)", stats.Overlay.NotReached},
		{"  reached = null (producer did not state)", stats.Overlay.ReachedUnknown},
		{"total entry_count", stats.Overlay.TotalEntryCount},
		{"observations", stats.Overlay.Observations},
		{"exceptions", stats.Overlay.Exceptions},
		{"imports", stats.Overlay.Imports},
		{"unresolved targets", stats.Overlay.UnresolvedTargets},
		{"indirect targets", stats.Overlay.IndirectTargets},
		{"distinct producers", stats.Overlay.DistinctProducers},
	} {
		fmt.Fprintf(env.Stdout, "  %-40s %7d\n", r.name, r.n)
	}
	if stats.Joined == nil {
		fmt.Fprintf(env.Stdout, "\njoined views\n  (no static snapshot was reachable; these views are null, not zero)\n")
		return ExitOK
	}
	j := stats.Joined
	fmt.Fprintf(env.Stdout, "\njoined views  (static side, %d functions indexed)\n", j.FunctionsIndexed)
	for _, r := range []struct {
		name string
		n    int
	}{
		{"runtime-observed with an OpenSpore passport", j.WithPassport},
		{"runtime-observed absent from the static universe", j.RuntimeOnly},
		{"runtime-observed at an interior address", j.InteriorAddress},
		{"runtime-observed statically reconstructed", j.Reconstructed},
		{"runtime-observed promoted", j.Promoted},
		{"runtime-observed ABI UNKNOWN", j.ABIUnknown},
		{"runtime-observed RETURN SEMANTICS not PASS", j.ReturnUnknown},
		{"runtime-observed RenderWare", j.Renderware},
		{"runtime-observed carrying a static blocker", j.WithBlockers},
	} {
		fmt.Fprintf(env.Stdout, "  %-50s %7d\n", r.name, r.n)
	}
	if len(j.RuntimeOnlyList) > 0 {
		fmt.Fprintf(env.Stdout, "\naddresses the runtime reached that OpenSpore cannot place in its function universe\n")
		fmt.Fprintf(env.Stdout, "  these are the discrepancies this bridge exists to surface; OpenSpore does not\n")
		fmt.Fprintf(env.Stdout, "  manufacture a function record for any of them\n")
		shown := j.RuntimeOnlyList
		if len(shown) > 40 {
			shown = shown[:40]
			fmt.Fprintf(env.Stdout, "  %d of %d:\n", len(shown), len(j.RuntimeOnlyList))
		} else {
			fmt.Fprintf(env.Stdout, "  %d of %d:\n", len(shown), len(j.RuntimeOnlyList))
		}
		for _, va := range shown {
			fmt.Fprintf(env.Stdout, "    %s\n", va)
		}
	}
	return ExitOK
}

// ---- runtime frontier -----------------------------------------------------

func runRuntimeFrontier(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime frontier", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	overlay := fs.String("overlay", "", "runtime overlay path (optional)")
	censusPath := fs.String("census", "", "blocker census path (optional)")
	snapPath := fs.String("snapshot", env.SnapshotPath, "static snapshot path (optional)")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	var vas repeatString
	fs.Var(&vas, "va", "target VA (repeatable)")
	blockersOnly := fs.Bool("blockers-only", true, "keep only targets carrying a static blocker statement")
	if _, err := parseArgs(fs, args); err != nil {
		return ExitUsage
	}
	if *overlay == "" && *censusPath == "" && len(vas) == 0 {
		fmt.Fprintln(env.Stderr, "spore-semantic runtime frontier: nothing to intersect; pass --overlay, --census or --va")
		return ExitUsage
	}

	var ov *runtime.Overlay
	if *overlay != "" {
		var code int
		ov, code = loadOverlay(*overlay, env.RequireSHA, env)
		if ov == nil {
			return code
		}
	}
	ix, snap := loadIndexBestEffort(*snapPath, *root, env)
	if ov != nil {
		crossCheckBinary(ov, snap, env)
	}

	inputs, censusSummary, code := frontierInputs(ix, *censusPath, vas, *blockersOnly, env)
	if code != ExitOK {
		return code
	}
	if ov == nil {
		// A frontier with no overlay has no runtime half; it degrades to the
		// static census, and says so, rather than reporting every target as
		// "not reached" when the truth is "no observation source was supplied".
		fmt.Fprintln(env.Stderr, "spore-semantic runtime frontier: no --overlay supplied; every target is classified as not_reached because no runtime source was given")
	}

	rows := runtime.Frontier(orEmptyOverlay(ov), inputs)

	payload := map[string]any{
		"requested_va":       vas,
		"targets":            rows,
		"summary":            frontierSummary(rows),
		"overlay":            optionalOverlayInfo(ov),
		"snapshot":           derefSnapshot(snap),
		"census":             censusSummary,
		"resolution_classes": runtime.ResolutionClasses,
		"verdict_unchanged":  "no static verdict was modified; this is a prioritisation report",
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	printFrontier(env.Stdout, rows, ov, snap, censusSummary)
	return ExitOK
}

// orEmptyOverlay lets Frontier run with no overlay. Every address then has no
// runtime summary, which the classifier reports as ResolutionNotReached -- the
// correct answer for "no runtime source was given", and visibly so because the
// command warns about it above.
func orEmptyOverlay(ov *runtime.Overlay) *runtime.Overlay {
	if ov != nil {
		return ov
	}
	return runtime.NewEmptyOverlay()
}

func optionalOverlayInfo(ov *runtime.Overlay) any {
	if ov == nil {
		return nil
	}
	return overlayInfo{Path: ov.Path, Schema: ov.Metadata.Schema, BinarySHA256: ov.Metadata.Binary.SHA256, ImageBase: ov.Metadata.Binary.ImageBase, Producer: ov.Metadata.Producer, Entries: ov.Len()}
}

// frontierInputs builds the target list, then ENRICHES it.
//
// One source chooses the targets and the others only add facts about them:
//
//	--va          exactly the addresses named (the census and snapshot enrich)
//	--census      every census target carrying a blocker statement
//	snapshot      every function whose own validation report is not PASS
//
// Keeping those roles apart is what makes the report usable. Appending 543 census
// rows to a list of ten named addresses buried the ten under the rest, and the
// alternative -- letting --va add to the census rather than replace it -- makes
// an explicit target list meaningless.
//
// It never re-derives eligibility: tools/reconstruction_tooling/frontier.py owns
// that, and duplicating the scoring in a second language would create a second
// answer to "which targets are eligible".
func frontierInputs(ix *index.Index, censusPath string, vas repeatString, blockersOnly bool, env Env) ([]runtime.FrontierInput, any, int) {
	var censusDoc *runtime.Census
	var censusSummary any
	if censusPath != "" {
		census, err := runtime.LoadCensus(censusPath, env.RequireSHA)
		if err != nil {
			fmt.Fprintf(env.Stderr, "spore-semantic runtime: %s: %v\n", classifyCensusError(err), err)
			return nil, nil, classifyCensusExit(err)
		}
		if problems := runtime.VerifyCensus(census); len(problems) > 0 {
			for _, p := range problems {
				fmt.Fprintf(env.Stderr, "spore-semantic runtime: %s\n", p)
			}
			return nil, nil, ExitCorruptSnapshot
		}
		censusDoc = census
		byVA := map[uint32]*runtime.CensusTarget{}
		for i := range census.Targets {
			if a, err := semantic.ParseAddr(census.Targets[i].VA, 0); err == nil {
				byVA[uint32(a)] = &census.Targets[i]
			}
		}
		censusSummary = map[string]any{
			"path":              censusPath,
			"schema":            census.Schema,
			"index":             census.Source.Index,
			"index_sha256":      census.Source.IndexSHA256,
			"promotion_markers": census.Source.PromotionMarkers,
			"promoted_count":    census.Source.PromotedCount,
			"targets":           len(census.Targets),
		}
		_ = byVA
	}

	build := func(addr semantic.Addr) runtime.FrontierInput {
		in := snapshotFrontierInput(ix, addr)
		if censusDoc != nil {
			if t, ok := censusLookup(censusDoc, addr); ok {
				in.Name = firstNonEmptyStr2(t.Name, in.Name, addr.String())
				// The census carries prose the snapshot cannot, and the promotion
				// marker is the authority on "promoted"; where the two disagree the
				// marker wins, which is why the census value is applied last.
				in.Blockers = mergeBlockers(in.Blockers, censusBlockers(*t))
				in.CensusProse = censusProse(*t)
				in.Reconstructed = in.Reconstructed || t.Reconstructed
				in.Promoted = in.Promoted || t.Promoted
				in.RuntimeGated = in.RuntimeGated || t.RuntimeGated
			}
		}
		return in
	}

	var inputs []runtime.FrontierInput
	switch {
	case len(vas) > 0:
		for _, raw := range vas {
			addr, err := semantic.ParseAddr(raw, 0)
			if err != nil {
				fmt.Fprintf(env.Stderr, "spore-semantic runtime frontier: %v\n", err)
				return nil, nil, ExitUsage
			}
			inputs = append(inputs, build(addr))
		}
	case censusDoc != nil:
		for _, t := range censusDoc.Targets {
			if blockersOnly && !t.HasBlocker() {
				continue
			}
			addr, err := semantic.ParseAddr(t.VA, 0)
			if err != nil {
				continue
			}
			in := build(addr)
			in.HasStaticIdentity = in.HasStaticIdentity || t.VA != ""
			inputs = append(inputs, in)
		}
	default:
		if ix == nil {
			fmt.Fprintln(env.Stderr, "spore-semantic runtime frontier: no --census and no --va, and no static snapshot was reachable; pass one of them")
			return nil, nil, ExitUnavailable
		}
		for _, in := range snapshotFrontierInputs(ix) {
			inputs = append(inputs, build(in.VA))
		}
	}
	if censusSummary != nil {
		if m, ok := censusSummary.(map[string]any); ok {
			m["targets_reported"] = len(inputs)
			m["role"] = censusRole(len(vas) > 0)
		}
	}
	return inputs, censusSummary, ExitOK
}

func censusRole(explicit bool) string {
	if explicit {
		return "enrichment only: --va chose the targets"
	}
	return "target source"
}

func censusLookup(c *runtime.Census, addr semantic.Addr) (*runtime.CensusTarget, bool) {
	i := sort.Search(len(c.Targets), func(i int) bool { return c.Targets[i].VA >= addr.String() })
	if i >= len(c.Targets) || c.Targets[i].VA != addr.String() {
		return nil, false
	}
	return &c.Targets[i], true
}

func mergeBlockers(in []runtime.Blocker, extra []runtime.Blocker) []runtime.Blocker {
	seen := map[string]bool{}
	var out []runtime.Blocker
	for _, b := range append(append([]runtime.Blocker{}, in...), extra...) {
		k := b.Dimension + "\x00" + b.Status + "\x00" + b.Source
		if seen[k] {
			continue
		}
		seen[k] = true
		out = append(out, b)
	}
	sort.SliceStable(out, func(i, j int) bool { return out[i].Dimension < out[j].Dimension })
	return out
}

func firstNonEmptyStr2(vals ...string) string {
	for _, v := range vals {
		if strings.TrimSpace(v) != "" {
			return v
		}
	}
	return ""
}

func censusBlockers(t runtime.CensusTarget) []runtime.Blocker {
	var out []runtime.Blocker
	if t.RuntimeGated {
		out = append(out, runtime.Blocker{
			Dimension: "RUNTIME",
			Status:    "GATED",
			Detail: firstNonEmptyString(t.RuntimeGates, t.RuntimeBlockReason,
				[]string{"the reconstruction is gated on a runtime observation this repository has never had"}),
			Source: "reconstruction/knowledge/index.json runtime_gated",
		})
	}
	if len(t.Blockers) > 0 {
		out = append(out, runtime.Blocker{
			Dimension: "INDEX",
			Status:    "BLOCKED",
			Detail:    t.Blockers[0],
			Source:    "reconstruction/knowledge/index.json blockers (free-text prose, reproduced verbatim)",
		})
	}
	sort.SliceStable(out, func(i, j int) bool { return out[i].Dimension < out[j].Dimension })
	return out
}

func censusProse(t runtime.CensusTarget) []string {
	var out []string
	for _, b := range t.Blockers {
		out = append(out, "blocker: "+b)
	}
	for _, q := range t.UnresolvedQuestions {
		out = append(out, "unresolved_question: "+q)
	}
	for _, g := range t.RuntimeGates {
		out = append(out, "runtime_gate: "+g)
	}
	for _, r := range t.RuntimeBlockReason {
		out = append(out, "runtime_blocking_reason: "+r)
	}
	return out
}

func firstNonEmptyString(in ...[]string) string {
	for _, list := range in {
		for _, s := range list {
			if s != "" {
				return s
			}
		}
	}
	return ""
}

func classifyCensusError(err error) string {
	switch {
	case isErr(err, runtime.ErrCensusMissing):
		return "census_not_found"
	case isErr(err, runtime.ErrCensusSchema):
		return "unsupported_census_schema"
	case isErr(err, runtime.ErrBinaryMismatch):
		return "binary_mismatch"
	default:
		return "corrupted_census"
	}
}

func classifyCensusExit(err error) int {
	switch {
	case isErr(err, runtime.ErrCensusMissing):
		return ExitUnavailable
	case isErr(err, runtime.ErrCensusSchema):
		return ExitUnsupportedSchema
	case isErr(err, runtime.ErrBinaryMismatch):
		return ExitBinaryMismatch
	default:
		return ExitCorruptSnapshot
	}
}

func printFrontier(w io.Writer, rows []runtime.FrontierRow, ov *runtime.Overlay, snap *snapshotInfo, censusSummary any) {
	fmt.Fprintf(w, "RUNTIME-ASSISTED BLOCKER REPORT\n")
	fmt.Fprintf(w, "  This is a PRIORITISATION report. No static verdict was modified, and no\n")
	fmt.Fprintf(w, "  blocker was resolved by anything below. `runtime_evidence_relevant` means\n")
	fmt.Fprintf(w, "  the overlay holds observations in categories this build maps to a recorded\n")
	fmt.Fprintf(w, "  blocker -- not that the blocker is settled.\n\n")
	if ov != nil {
		fmt.Fprintf(w, "  overlay   %s\n", ov.Path)
		fmt.Fprintf(w, "  producer  %s / %s %s (%s)\n", ov.Metadata.Producer.Project, ov.Metadata.Producer.Name, ov.Metadata.Producer.Version, ov.Metadata.Producer.Artifact)
	} else {
		fmt.Fprintf(w, "  overlay   none supplied\n")
	}
	if snap != nil && snap.Available {
		fmt.Fprintf(w, "  snapshot  %s (%d functions, %s)\n", snap.Path, snap.Functions, shortSHA(snap.BinarySHA256))
	} else {
		reason := "not requested"
		if snap != nil && snap.Reason != "" {
			reason = snap.Reason
		}
		fmt.Fprintf(w, "  snapshot  unavailable: %s\n", reason)
	}
	if censusSummary != nil {
		m, _ := censusSummary.(map[string]any)
		if m != nil {
			fmt.Fprintf(w, "  census    %v (%s; %v of %v targets, role: %v)\n",
				m["path"], "verified", m["targets_reported"], m["targets"], m["role"])
		}
	}
	fmt.Fprintf(w, "\n")

	for _, row := range rows {
		fmt.Fprintf(w, "%s  %s\n", row.VA, row.Name)
		fmt.Fprintf(w, "  static    reconstructed=%t promoted=%t runtime_gated=%t\n", row.Reconstructed, row.Promoted, row.RuntimeGated)
		if len(row.Blockers) == 0 && len(row.CensusProse) == 0 {
			fmt.Fprintf(w, "  blocker   %s\n", "none recorded by any OpenSpore artifact")
		}
		for _, b := range row.Blockers {
			fmt.Fprintf(w, "  blocker   %s %s [%s]\n", b.Dimension, b.Status, b.Source)
			fmt.Fprintf(w, "             %s\n", b.Detail)
		}
		for _, p := range row.CensusProse {
			fmt.Fprintf(w, "  census    %s\n", p)
		}
		if row.Runtime == nil {
			fmt.Fprintf(w, "  runtime   not observed (the overlay carries no entry for this VA; this is\n")
			fmt.Fprintf(w, "            NOT the same as observed-and-not-reached)\n")
		} else {
			rt := row.Runtime
			fmt.Fprintf(w, "  runtime   reached=%s entry_count=%s kinds=%v\n",
				rt.Reached, countOrNull(rt.EntryCount), rt.ObservationKinds)
			for _, c := range rt.RuntimeCallers {
				fmt.Fprintf(w, "             caller  %s@%s\n", derefStr(c.CallerFunctionVA), c.CallsiteVA)
			}
			for _, t := range rt.RuntimeTargets {
				fmt.Fprintf(w, "             target  %s indirect=%s unresolved=%s %s\n", t.TargetVA, t.Indirect, t.Unresolved, t.Classification)
			}
			for _, im := range rt.RuntimeImports {
				fmt.Fprintf(w, "             import  %s!%s slot=%s bound=%s\n", im.Module, im.Symbol, derefStr(im.SlotVA), im.Bound)
			}
			if rt.ExceptionCount > 0 {
				fmt.Fprintf(w, "             exception_count %d\n", rt.ExceptionCount)
			}
		}
		for dim, kinds := range row.RelevantByDimension {
			names := make([]string, 0, len(kinds))
			for _, k := range kinds {
				names = append(names, string(k))
			}
			fmt.Fprintf(w, "  relevant  %s <- %v\n", dim, names)
		}
		fmt.Fprintf(w, "  class     %s\n", row.ResolutionClass)
		fmt.Fprintf(w, "  action    new_static_task_justified=%t\n", row.NewStaticTaskJustified)
		fmt.Fprintf(w, "            %s\n", row.Justification)
		fmt.Fprintln(w)
	}

	fmt.Fprintf(w, "SUMMARY BY RESOLUTION CLASS\n")
	byClass := frontierSummary(rows)
	keys := make([]string, 0, len(byClass))
	for k := range byClass {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	for _, k := range keys {
		fmt.Fprintf(w, "  %-40s %d\n", k, byClass[k])
	}
}

func frontierSummary(rows []runtime.FrontierRow) map[string]int {
	out := map[string]int{}
	for _, r := range rows {
		out[r.ResolutionClass]++
	}
	for _, c := range runtime.ResolutionClasses {
		if _, ok := out[c]; !ok {
			out[c] = 0
		}
	}
	return out
}

// ---- runtime import-recomp ------------------------------------------------

func runRuntimeImportRecomp(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime import-recomp", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	report := fs.String("report", "", "spore-recomp runtime report path (read-only)")
	out := fs.String("out", "", "overlay path to write (default: stdout only)")
	artifact := fs.String("artifact", "", "portable artifact identifier, e.g. work/reports/startup-recovery14.json")
	version := fs.String("version", "", "producer version to record (default: the report's schema_version)")
	requireSHA := fs.String("require-sha", env.RequireSHA, "refuse a report describing a different binary")
	if _, err := parseArgs(fs, args); err != nil {
		return ExitUsage
	}
	if *report == "" {
		fmt.Fprintln(env.Stderr, "spore-semantic runtime import-recomp: --report is required")
		return ExitUsage
	}
	ident := *artifact
	if ident == "" {
		if guess, ok := runtime.DefaultRecompArtifact(*report); ok {
			ident = guess
		}
	}
	conv, err := runtime.ConvertRecomp(*report, *requireSHA, runtime.RecompOptions{Artifact: ident, Version: *version})
	if err != nil {
		return fail(env, classifyRuntimeError(err), classifyRuntimeLoadError(err), err)
	}
	res, err := runtime.Write(*out, conv.Entries, conv.Metadata)
	if err != nil {
		return fail(env, ExitUsage, "write_failed", err)
	}
	payload := map[string]any{
		"overlay_path":       res.Path,
		"binary_sha256":      conv.Metadata.Binary.SHA256,
		"image_base":         conv.Metadata.Binary.ImageBase,
		"producer":           conv.Metadata.Producer,
		"content_sha256":     res.ContentSHA,
		"bytes":              res.Bytes,
		"addresses":          conv.Addresses,
		"reached":            conv.Reached,
		"runtime_only":       conv.RuntimeOnly,
		"unresolved_targets": conv.Unresolved,
		"imports":            conv.Imports,
		"source": map[string]any{
			"report_outcome":  conv.Report.Outcome,
			"source_schema":   conv.Report.SchemaVersion,
			"steps":           conv.Report.Steps,
			"peak_call_depth": conv.Report.PeakCallDepth,
			"call_edges":      len(conv.Report.CallEdges),
			"iat_cell_checks": len(conv.Report.Imports.IATCellChecks),
		},
		"notes": conv.Notes,
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	fmt.Fprintf(env.Stdout, "wrote %s\n", res.Path)
	fmt.Fprintf(env.Stdout, "  binary_sha256       %s\n", conv.Metadata.Binary.SHA256)
	fmt.Fprintf(env.Stdout, "  image_base          %s\n", conv.Metadata.Binary.ImageBase)
	fmt.Fprintf(env.Stdout, "  producer            %s / %s %s\n", conv.Metadata.Producer.Project, conv.Metadata.Producer.Name, conv.Metadata.Producer.Version)
	fmt.Fprintf(env.Stdout, "  artifact            %s   (portable identifier; the report's filesystem path is not embedded)\n", conv.Metadata.Producer.Artifact)
	fmt.Fprintf(env.Stdout, "  addresses           %d\n", conv.Addresses)
	fmt.Fprintf(env.Stdout, "    reached=true      %d\n", conv.Reached)
	fmt.Fprintf(env.Stdout, "    no canonical_va   %d  (canonical_va is left null on every entry: identity is OpenSpore's to decide)\n", conv.RuntimeOnly)
	fmt.Fprintf(env.Stdout, "  unresolved targets  %d\n", conv.Unresolved)
	fmt.Fprintf(env.Stdout, "  imports             %d\n", conv.Imports)
	fmt.Fprintf(env.Stdout, "  content_sha256      %s (over %d entry lines)\n", res.ContentSHA, res.Entries)
	fmt.Fprintf(env.Stdout, "  bytes               %d\n", res.Bytes)
	fmt.Fprintf(env.Stdout, "  source report       outcome=%s steps=%d peak_depth=%d call_edges=%d\n",
		conv.Report.Outcome, conv.Report.Steps, conv.Report.PeakCallDepth, len(conv.Report.CallEdges))
	fmt.Fprintf(env.Stdout, "\n  notes\n")
	for _, n := range conv.Notes {
		fmt.Fprintf(env.Stdout, "    - %s\n", n)
	}
	return ExitOK
}

// ---- runtime census -------------------------------------------------------

func runRuntimeCensus(args []string, env Env) int {
	fs := flag.NewFlagSet("runtime census", flag.ContinueOnError)
	fs.SetOutput(env.Stderr)
	asJSON := fs.Bool("json", false, "emit machine-readable JSON")
	root := fs.String("root", env.Root, "OpenSpore checkout root")
	out := fs.String("out", "", "census path to write")
	blocked := fs.Bool("with-blockers", true, "report only targets that carry a blocker statement")
	stats := fs.Bool("stats", false, "print counts instead of writing")
	if _, err := parseArgs(fs, args); err != nil {
		return ExitUsage
	}
	r, err := resolveRoot(*root)
	if err != nil {
		return fail(env, ExitUnavailable, "root_unavailable", err)
	}
	census, absent, digests, err := openspore.BuildCensus(r)
	if err != nil {
		return fail(env, ExitUsage, "projection_failed", err)
	}
	// Counts are computed over the FULL projection, BEFORE the filter narrows
	// census.Targets. A count that shrank with the filter would be impossible to
	// check against the repository's own statements (AGENTS.md records 92
	// promoted VAs and 89 promotion markers), and an uncheckable number is not
	// evidence. This was a real bug once: the filter ran first and reported 90.
	full := append([]runtime.CensusTarget(nil), census.Targets...)
	all := len(full)
	kept := all
	if *blocked {
		kept = 0
		var narrowed []runtime.CensusTarget
		for _, t := range full {
			if t.HasBlocker() {
				narrowed = append(narrowed, t)
				kept++
			}
		}
		census.Targets = narrowed
	}
	path := *out
	if path == "" {
		path = filepath.Join(r, filepath.FromSlash(openspore.RelCensusRel))
	}
	if !*stats {
		if _, err := runtime.WriteCensus(path, *census); err != nil {
			return fail(env, ExitUsage, "write_failed", err)
		}
	}
	counts := censusCounters(full)
	counts["targets_projected"] = all
	counts["targets_reported"] = kept
	_ = digests
	payload := map[string]any{
		"schema":        census.Schema,
		"binary":        census.Binary,
		"source":        census.Source,
		"census_path":   path,
		"written":       !*stats,
		"counts":        counts,
		"absent_inputs": absent,
		"note":          "a projection of reconstruction/knowledge/index.json plus the promotion markers; it derives no eligibility, no scoring and no blocker codes",
	}
	if *asJSON {
		if err := writeJSON(env.Stdout, payload); err != nil {
			return fail(env, ExitUsage, "encode_failed", err)
		}
		return ExitOK
	}
	fmt.Fprintf(env.Stdout, "census           %s\n", path)
	fmt.Fprintf(env.Stdout, "schema           %s\n", census.Schema)
	fmt.Fprintf(env.Stdout, "binary_sha256    %s\n", census.Binary.SHA256)
	fmt.Fprintf(env.Stdout, "index            %s\n", census.Source.Index)
	fmt.Fprintf(env.Stdout, "index_sha256     %s\n", census.Source.IndexSHA256)
	fmt.Fprintf(env.Stdout, "markers          %s  (%d files)\n", census.Source.PromotionMarkers, census.Source.PromotedCount)
	fmt.Fprintf(env.Stdout, "targets          %d projected, %d reported\n", all, kept)
	fmt.Fprintf(env.Stdout, "  counts below are over ALL %d projected targets, before the filter, so they are checkable\n", all)
	fmt.Fprintf(env.Stdout, "  with blockers   %d\n", counts["with_blockers"])
	fmt.Fprintf(env.Stdout, "  runtime gated   %d\n", counts["runtime_gated"])
	fmt.Fprintf(env.Stdout, "  promoted        %d\n", counts["promoted"])
	fmt.Fprintf(env.Stdout, "  reconstructed   %d\n", counts["reconstructed"])
	for _, a := range absent {
		fmt.Fprintf(env.Stdout, "absent input     %s: %s\n", a.Path, a.Reason)
	}
	return ExitOK
}

func isErr(err, target error) bool { return err != nil && errors.Is(err, target) }

// snapshotFrontierInput builds a row for one address from the snapshot alone.
//
// It states plainly what it could not establish: an address with no passport
// becomes HasStaticIdentity=false, which is the honest answer and is what makes
// the runtime-only class reachable from the CLI without inventing a record.
func snapshotFrontierInput(ix *index.Index, addr semantic.Addr) runtime.FrontierInput {
	in := runtime.FrontierInput{VA: addr, Name: addr.String()}
	if ix == nil {
		return in
	}
	res := ix.Resolve(addr)
	if res.Passport == nil {
		return in
	}
	p := res.Passport
	in.Name = firstName(p)
	in.HasStaticIdentity = true
	in.Blockers = runtime.StaticBlockers(p)
	if p.Reconstruction.IsAvailable() {
		r := p.Reconstruction.Deref()
		in.Reconstructed = r.Reconstructed != nil && *r.Reconstructed
		in.Promoted = r.Promoted == semantic.TriTrue
		in.RuntimeGated = r.RuntimeGated != nil && *r.RuntimeGated
	}
	return in
}

// snapshotFrontierInputs sweeps the snapshot for functions whose own validation
// report says a dimension is not PASS.
//
// This reads the artifacts, it does not re-run the campaign: no scoring, no
// eligibility rule, no dependency analysis. A target the frontier tool would call
// eligible on other grounds is simply not surfaced here, and a target with no
// evidence pack has no adjudicated dimension to report at all.
func snapshotFrontierInputs(ix *index.Index) []runtime.FrontierInput {
	var out []runtime.FrontierInput
	for _, addr := range ix.Data().Order {
		p := ix.Data().Passports[addr]
		blockers := runtime.StaticBlockers(p)
		if len(blockers) == 0 {
			continue
		}
		in := runtime.FrontierInput{
			VA:                semantic.Addr(addr),
			Name:              firstName(p),
			Blockers:          blockers,
			HasStaticIdentity: true,
		}
		if p.Reconstruction.IsAvailable() {
			r := p.Reconstruction.Deref()
			in.Reconstructed = r.Reconstructed != nil && *r.Reconstructed
			in.Promoted = r.Promoted == semantic.TriTrue
			in.RuntimeGated = r.RuntimeGated != nil && *r.RuntimeGated
		}
		out = append(out, in)
	}
	return out
}

// censusCounters tallies a target list. It runs over the full projection, not
// the filtered one, so the numbers can be compared against the repository's own
// statements rather than against this command's own output.
func censusCounters(targets []runtime.CensusTarget) map[string]int {
	out := map[string]int{
		"with_blockers":      0,
		"runtime_gated":      0,
		"promoted":           0,
		"reconstructed":      0,
		"with_runtime_gates": 0,
	}
	for _, t := range targets {
		if len(t.Blockers) > 0 {
			out["with_blockers"]++
		}
		if t.RuntimeGated {
			out["runtime_gated"]++
		}
		if len(t.RuntimeGates) > 0 {
			out["with_runtime_gates"]++
		}
		if t.Promoted {
			out["promoted"]++
		}
		if t.Reconstructed {
			out["reconstructed"]++
		}
	}
	return out
}
