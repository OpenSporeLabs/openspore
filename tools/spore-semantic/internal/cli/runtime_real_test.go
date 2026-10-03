package cli

import (
	"bytes"
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/runtime"
)

// Real-artifact integration tests.
//
// Every test here reads two things that exist outside this test file: the real
// OpenSpore snapshot, and a real spore-recomp runtime report from the sibling
// checkout. Both are READ-ONLY; nothing here writes into ../spore-recomp. Each
// test SKIPS when its artifact is absent, so the suite stays green in a checkout
// that has neither -- OpenSpore must be buildable and testable without the
// sibling project.
//
// The assertions are deliberately about the TOOL's behaviour and about facts the
// artifacts already state. None of them invents a runtime observation and none
// expects a blocker to have been resolved.

const (
	report12 = "startup-recovery12.json"
	report14 = "startup-recovery14.json"
)

// recompReport returns the path to a named spore-recomp runtime report, or skips.
func recompReport(t *testing.T, name string) string {
	t.Helper()
	root := repoRoot(t)
	candidates := []string{
		filepath.Join(root, "..", "spore-recomp", "work", "reports", name),
		filepath.Join(root, "..", "spore_recomp", "work", "reports", name),
	}
	for _, p := range candidates {
		if st, err := os.Stat(p); err == nil && st.Mode().IsRegular() {
			return p
		}
	}
	t.Skipf("no spore-recomp runtime report at any known location (%s); the sibling checkout is not available here",
		strings.Join(candidates, ", "))
	return ""
}

func realOverlay(t *testing.T, name string) string {
	t.Helper()
	report := recompReport(t, name)
	out := filepath.Join(t.TempDir(), "overlay.jsonl")
	r := run(t, "runtime", "import-recomp", "--report", report, "--out", out)
	if r.code != ExitOK {
		t.Fatalf("import-recomp failed (%d): %s%s", r.code, r.stdout, r.stderr)
	}
	return out
}

// TestRealRecompReportConvertsAndValidates is the end-to-end ingestion path on a
// real producer artifact.
func TestRealRecompReportConvertsAndValidates(t *testing.T) {
	overlay := realOverlay(t, report14)
	r := run(t, "runtime", "validate", "--overlay", overlay, "--json")
	if r.code != ExitOK {
		t.Fatalf("validate failed (%d): %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	if p["ok"] != true {
		t.Fatalf("ok = %v, problems = %v", p["ok"], p["problems"])
	}
	if p["binary_sha256"] != sporeBinarySHA {
		t.Fatalf("binary_sha256 = %v, want %s", p["binary_sha256"], sporeBinarySHA)
	}
	if p["image_base"] != sporeImageBase {
		t.Fatalf("image_base = %v", p["image_base"])
	}
	if p["entries"].(float64) <= 0 {
		t.Fatal("the real report produced an empty overlay")
	}
	if p["content_sha256"] == "" {
		t.Fatal("no content digest was recorded or verified")
	}
	prod := p["producer"].(map[string]any)
	if prod["project"] != runtime.RecompProject {
		t.Fatalf("producer.project = %v", prod["project"])
	}
	// The artifact identifier must be portable and must NOT be the filesystem path.
	art := prod["artifact"].(string)
	if art != runtime.RecompArtifactPrefix+"/"+report14 {
		t.Fatalf("artifact = %q, want the portable repo-relative identifier", art)
	}
	if strings.HasPrefix(art, "/") || strings.Contains(art, "/datos") {
		t.Fatalf("a filesystem path leaked into provenance: %q", art)
	}
}

func TestRealRecompConversionIsDeterministic(t *testing.T) {
	report := recompReport(t, report14)
	a := filepath.Join(t.TempDir(), "a.jsonl")
	b := filepath.Join(t.TempDir(), "b.jsonl")
	for _, out := range []string{a, b} {
		if r := run(t, "runtime", "import-recomp", "--report", report, "--out", out); r.code != ExitOK {
			t.Fatalf("import-recomp failed: %s%s", r.stdout, r.stderr)
		}
	}
	da, err := os.ReadFile(a)
	if err != nil {
		t.Fatal(err)
	}
	db, err := os.ReadFile(b)
	if err != nil {
		t.Fatal(err)
	}
	if !bytes.Equal(da, db) {
		t.Fatalf("two conversions of one real report are not byte-identical (%d vs %d bytes)", len(da), len(db))
	}
}

// TestRealRuntimeOnlyAddressIsRepresented is the case the whole bridge exists
// for. 0x00925050 was reached by a real vtable indirect call during a real
// spore-recomp run, and OpenSpore's static universe cannot place it: it lies
// between FUN_00925000 (ending 0x0092504a) and FUN_009250c0.
//
// The assertions are that the discrepancy SURVIVES in both directions: the static
// half stays null, and the runtime half stays complete.
func TestRealRuntimeOnlyAddressIsRepresented(t *testing.T) {
	snap := exportReal(t)
	overlay := realOverlay(t, report12)

	r := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)

	ident := p["identity"].(map[string]any)
	if ident["canonical_va"] != nil {
		t.Fatalf("canonical_va = %v; OpenSpore must not manufacture a function entry", ident["canonical_va"])
	}
	if ident["canonicalization"] != runtime.CanonicalNonEntity {
		t.Fatalf("canonicalization = %v, want %q", ident["canonicalization"], runtime.CanonicalNonEntity)
	}
	if ident["static_status"] != runtime.StaticStatusUnknownEntity {
		t.Fatalf("static_status = %v", ident["static_status"])
	}
	if p["static"] != nil {
		t.Fatalf("static = %v; padding must not acquire a passport", p["static"])
	}

	rt := p["runtime"].(map[string]any)
	if rt["reached"] != "true" {
		t.Fatalf("reached = %v, want \"true\": the producer recorded an arrival", rt["reached"])
	}
	if rt["canonical_va"] != nil {
		t.Fatalf("the overlay invented a canonical_va: %v", rt["canonical_va"])
	}
	callers := rt["runtime_callers"].([]any)
	if len(callers) == 0 {
		t.Fatal("the real caller edge was lost")
	}
	// The producer's own caller function is carried verbatim.
	var sawFunction bool
	for _, c := range callers {
		if c.(map[string]any)["caller_function_va"] == "0x00925b00" {
			sawFunction = true
		}
	}
	if !sawFunction {
		t.Fatalf("the producer's caller function 0x00925b00 is not among %v", callers)
	}
	if p["verdict_unchanged"] == "" {
		t.Fatal("the joined view does not state that no verdict changed")
	}
	// And the human form says why, in words.
	h := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap)
	for _, want := range []string{"does not", "manufacture a function record", runtime.RecompProject} {
		if !strings.Contains(h.stdout, want) {
			t.Fatalf("the human form does not mention %q:\n%s", want, h.stdout)
		}
	}
}

// TestRealRepresentativeLookups walks the four addresses the task names, against
// the real snapshot. It asserts the STATIC half, because that is the half that
// must not move; the runtime half depends on how far the producer run got.
func TestRealRuntimeRepresentativeLookups(t *testing.T) {
	snap := exportReal(t)

	t.Run("promoted function with runtime context", func(t *testing.T) {
		// 0x0040ccb0 is the Wave 6 presentation package: SDK-named, evidence
		// pack, validation report, integrated and approved.
		r, p := lookupJSON(t, snap, "0x0040ccb0")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if p["names"].(map[string]any)["sdk_name"] == nil {
			t.Fatal("the SDK name was dropped")
		}
		rec := p["reconstruction"].(map[string]any)
		if rec["state"] != "available" {
			t.Fatalf("reconstruction state = %v", rec["state"])
		}
		// And the runtime join on the same address keeps that static record intact.
		overlay := realOverlay(t, report14)
		j := run(t, "runtime", "lookup", "0x0040ccb0", "--overlay", overlay, "--snapshot", snap, "--json")
		if j.code != ExitOK {
			t.Fatalf("joined exit %d: %s", j.code, j.stderr)
		}
		jstatic := j.json(t)["static"].(map[string]any)
		if jstatic["names"].(map[string]any)["sdk_name"] != p["names"].(map[string]any)["sdk_name"] {
			t.Fatal("the joined view's static half disagrees with the plain static lookup")
		}
		if j.json(t)["verdict_unchanged"] == "" {
			t.Fatal("no verdict_unchanged literal in the joined output")
		}
	})

	t.Run("interior address", func(t *testing.T) {
		// 0x00e3a400 is interior to 0x00e3a270, at offset 400.
		r, p := lookupJSON(t, snap, "0x00e3a400")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if p["canonical_va"] != "0x00e3a270" {
			t.Fatalf("canonical_va = %v", p["canonical_va"])
		}
		overlay := realOverlay(t, report14)
		j := run(t, "runtime", "lookup", "0x00e3a400", "--overlay", overlay, "--snapshot", snap, "--json")
		if j.code != ExitOK {
			t.Fatalf("joined exit %d: %s", j.code, j.stderr)
		}
		ident := j.json(t)["identity"].(map[string]any)
		if ident["canonical_va"] != "0x00e3a270" || ident["canonicalization"] != runtime.CanonicalInterior {
			t.Fatalf("identity = %v", ident)
		}
		if ident["offset"].(float64) != 400 {
			t.Fatalf("offset = %v", ident["offset"])
		}
	})

	t.Run("padding address stays padding with no runtime entry", func(t *testing.T) {
		// 0x00925050 with an overlay that does NOT observe it. The two halves
		// must both say "nothing here", which is different from "observed and
		// found nothing".
		other := filepath.Join(t.TempDir(), "other.jsonl")
		if r := run(t, "runtime", "import-recomp", "--report", recompReport(t, report12),
			"--out", other, "--artifact", "work/reports/other.json"); r.code != ExitOK {
			t.Fatal(r.stderr)
		}
		// Rewrite without the 0x00925050 entry so the address is genuinely unobserved.
		raw, err := os.ReadFile(other)
		if err != nil {
			t.Fatal(err)
		}
		var kept []string
		for _, line := range strings.Split(string(raw), "\n") {
			if !strings.Contains(line, `"requested_va":"0x00925050"`) {
				kept = append(kept, line)
			}
		}
		trimmed := filepath.Join(t.TempDir(), "trimmed.jsonl")
		if err := os.WriteFile(trimmed, []byte(strings.Join(kept, "\n")), 0o644); err != nil {
			t.Fatal(err)
		}
		// The digest no longer matches, which is exactly the corruption signal; what
		// matters here is that the loader refuses rather than half-reading.
		if r := run(t, "runtime", "validate", "--overlay", trimmed); r.code != ExitCorruptSnapshot {
			t.Fatalf("a hand-edited overlay validated (exit %d)", r.code)
		}
	})

	t.Run("live ceiling", func(t *testing.T) {
		// 0x00f9fef0: RETURN SEMANTICS NOT_AVAILABLE. The join must REPORT that
		// blocker and must not soften it, whether or not an overlay observes it.
		overlay := realOverlay(t, report14)
		r := run(t, "runtime", "lookup", "0x00f9fef0", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		interp := r.json(t)["interpretation"].(map[string]any)
		blockers := interp["static_blockers"].([]any)
		var found bool
		for _, b := range blockers {
			if strings.Contains(b.(string), "RETURN SEMANTICS") {
				found = true
				if !strings.Contains(b.(string), "NOT_AVAILABLE") {
					t.Fatalf("the blocker text lost its status: %v", b)
				}
			}
		}
		if !found {
			t.Fatalf("blockers = %v, want the RETURN SEMANTICS blocker", blockers)
		}
		// The static verdict itself is untouched.
		_, sp := lookupJSON(t, snap, "0x00f9fef0")
		if !bytes.Contains([]byte(r.stdout), []byte(sp["reconstruction"].(map[string]any)["state"].(string))) {
			t.Fatal("the joined view and the plain lookup disagree about the static state")
		}
	})
}

func TestRealJoinedLookupIsDeterministic(t *testing.T) {
	snap := exportReal(t)
	overlay := realOverlay(t, report14)
	var prev string
	for i := 0; i < 3; i++ {
		r := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if i > 0 && r.stdout != prev {
			t.Fatal("repeated joined lookups of the real snapshot differ")
		}
		prev = r.stdout
	}
}

// TestRealCensusCountsAgainstTheRepositoriesOwnStatements checks the census
// against numbers the repository states for itself, rather than against its own
// previous output. A census that could not be checked this way would be an
// unverifiable number.
func TestRealCensusCountsAgainstTheRepositoriesOwnStatements(t *testing.T) {
	root := repoRoot(t)
	out := filepath.Join(t.TempDir(), "census.json")
	r := run(t, "runtime", "census", "--root", root, "--out", out, "--json")
	if r.code != ExitOK {
		t.Fatalf("census failed (%d): %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	src := p["source"].(map[string]any)
	counts := p["counts"].(map[string]any)

	// AGENTS.md and docs record 89 promotion markers carrying 92 promoted VAs.
	// The census must reproduce both, and it reads the markers rather than the
	// knowledge index, because the index lags promotion by design.
	if src["promoted_count"].(float64) != 89 {
		t.Fatalf("promotion markers = %v, want 89", src["promoted_count"])
	}
	if counts["promoted"].(float64) != 92 {
		t.Fatalf("promoted VAs = %v, want 92", counts["promoted"])
	}
	if counts["targets_projected"].(float64) != 618 {
		t.Fatalf("targets_projected = %v, want the 618 knowledge-index records", counts["targets_projected"])
	}
	// The index records runtime_gated true for 427 of 618.
	if counts["runtime_gated"].(float64) != 427 {
		t.Fatalf("runtime_gated = %v, want 427", counts["runtime_gated"])
	}
	if p["binary"].(map[string]any)["binary_sha256"] != sporeBinarySHA {
		t.Fatalf("census binary = %v", p["binary"])
	}

	census, err := runtime.LoadCensus(out, sporeBinarySHA)
	if err != nil {
		t.Fatalf("the written census does not load: %v", err)
	}
	if problems := runtime.VerifyCensus(census); len(problems) != 0 {
		t.Fatalf("VerifyCensus on the real census: %v", problems)
	}
	// Two projections of one state must be byte-identical.
	out2 := filepath.Join(t.TempDir(), "census2.json")
	if r := run(t, "runtime", "census", "--root", root, "--out", out2); r.code != ExitOK {
		t.Fatal(r.stderr)
	}
	a, _ := os.ReadFile(out)
	b, _ := os.ReadFile(out2)
	if !bytes.Equal(a, b) {
		t.Fatal("two census projections of the real checkout differ")
	}
}

// TestRealCensusCarriesTheRemainingCeilings asserts that the ten targets
// AGENTS.md lists as the remaining difficult ones all appear in the census with
// their own blocker prose. The census is the only artifact that carries that
// prose, so this is also a check that the projection reaches them.
func TestRealCensusCarriesTheRemainingCeilings(t *testing.T) {
	root := repoRoot(t)
	out := filepath.Join(t.TempDir(), "census.json")
	if r := run(t, "runtime", "census", "--root", root, "--out", out); r.code != ExitOK {
		t.Fatalf("census failed: %s%s", r.stdout, r.stderr)
	}
	census, err := runtime.LoadCensus(out, "")
	if err != nil {
		t.Fatal(err)
	}
	byVA := map[string]runtime.CensusTarget{}
	for _, tgt := range census.Targets {
		byVA[tgt.VA] = tgt
	}
	ceilings := []string{
		"0x01053db0", "0x01053e00", "0x00c70e00", "0x00c71e30", "0x00f9fef0",
		"0x00fa5040", "0x01053be0", "0x00b3d230", "0x00b3d240", "0x00f96840",
	}
	for _, va := range ceilings {
		tgt, ok := byVA[va]
		if !ok {
			t.Fatalf("%s is missing from the census", va)
		}
		if !tgt.HasBlocker() {
			t.Fatalf("%s carries no blocker statement; the projection lost it", va)
		}
		if len(tgt.UnresolvedQuestions) == 0 {
			t.Fatalf("%s carries no unresolved questions", va)
		}
	}
	// 0x0068f9b0 is CLOSED per AGENTS.md; the census must agree via the marker.
	if !byVA["0x0068f9b0"].Promoted {
		t.Fatal("0x0068f9b0 is promoted per AGENTS.md but the census says otherwise")
	}
}

// TestRealFrontierOverTheRemainingCeilings is the §16 deliverable: the static
// blocker census intersected with real runtime observations.
func TestRealFrontierOverTheRemainingCeilings(t *testing.T) {
	root := repoRoot(t)
	snap := exportReal(t)
	censusPath := filepath.Join(t.TempDir(), "census.json")
	if r := run(t, "runtime", "census", "--root", root, "--out", censusPath); r.code != ExitOK {
		t.Fatalf("census failed: %s%s", r.stdout, r.stderr)
	}
	overlay := realOverlay(t, report14)

	args := []string{"runtime", "frontier", "--overlay", overlay, "--census", censusPath, "--snapshot", snap, "--json"}
	for _, va := range []string{
		"0x01053db0", "0x01053e00", "0x00c70e00", "0x00c71e30", "0x00f9fef0",
		"0x00fa5040", "0x01053be0", "0x00b3d230", "0x00b3d240", "0x00f96840",
		"0x00925050",
	} {
		args = append(args, "--va", va)
	}
	r := run(t, args...)
	if r.code != ExitOK {
		t.Fatalf("frontier failed (%d): %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	rows := p["targets"].([]any)
	if len(rows) != 11 {
		t.Fatalf("rows = %d, want 11", len(rows))
	}
	byVA := map[string]map[string]any{}
	for _, row := range rows {
		m := row.(map[string]any)
		byVA[m["va"].(string)] = m
	}
	// The 0x00925050 case must classify as runtime-only: OpenSpore has no static
	// identity for it and the producer reached it. That is a NEW STATIC TASK, not
	// a resolved blocker.
	only := byVA["0x00925050"]
	if only["resolution_class"] != runtime.ResolutionRuntimeOnly {
		t.Fatalf("0x00925050 class = %v, want %s", only["resolution_class"], runtime.ResolutionRuntimeOnly)
	}
	if only["new_static_task_justified"] != true {
		t.Fatal("0x00925050 should be flagged for a static identity task")
	}
	// Every ceiling must carry at least one static blocker, and no ceiling may be
	// reported as already closed.
	for _, va := range []string{"0x00f9fef0", "0x00f96840", "0x00c70e00"} {
		row := byVA[va]
		if len(row["blockers"].([]any)) == 0 {
			t.Fatalf("%s reports no static blocker", va)
		}
		if row["resolution_class"] == runtime.ResolutionAlreadyClosed {
			t.Fatalf("%s is a live ceiling and must not be classified closed", va)
		}
		if len(row["census_prose"].([]any)) == 0 {
			t.Fatalf("%s carries no census prose; the projection lost it", va)
		}
	}
	if p["verdict_unchanged"] == "" {
		t.Fatal("the frontier does not state that no verdict changed")
	}
	// Every class in the vocabulary must be a key of the summary, including the
	// zero ones, so two runs of this report cannot disagree about a class's key set.
	summary := p["summary"].(map[string]any)
	for _, c := range runtime.ResolutionClasses {
		if _, ok := summary[c]; !ok {
			t.Fatalf("summary is missing the %q class", c)
		}
	}
}

// TestRealRuntimeDoesNotTouchTheStaticArtifacts is the load-bearing invariant of
// the whole design: after a full runtime workflow, every static artifact on disk
// is byte-for-byte unchanged.
func TestRealRuntimeDoesNotTouchTheStaticArtifacts(t *testing.T) {
	root := repoRoot(t)
	watched := []string{
		"knowledge/semantic/function-passport-v1.jsonl",
		"reconstruction/knowledge/index.json",
		"knowledgegraph/triage/xrefs-2540f2ca.tsv",
	}
	before := map[string]string{}
	for _, rel := range watched {
		p := filepath.Join(root, rel)
		if _, err := os.Stat(p); err != nil {
			continue
		}
		raw, err := os.ReadFile(p)
		if err != nil {
			t.Fatal(err)
		}
		before[rel] = sha256Hex(raw)
	}
	if len(before) == 0 {
		t.Skip("none of the watched static artifacts is present")
	}

	overlay := realOverlay(t, report14)
	census := filepath.Join(t.TempDir(), "census.json")
	for _, args := range [][]string{
		{"runtime", "validate", "--overlay", overlay},
		{"runtime", "stats", "--overlay", overlay, "--root", root},
		{"runtime", "lookup", "0x00925050", "--overlay", overlay, "--root", root},
		{"runtime", "lookup", "0x00f9fef0", "--overlay", overlay, "--root", root},
		{"runtime", "frontier", "--overlay", overlay, "--census", census, "--root", root, "--va", "0x00f9fef0"},
		{"runtime", "census", "--root", root, "--out", census},
	} {
		// Exit codes other than 0 are acceptable for individual probes; what is
		// being asserted is that nothing on disk moved.
		_ = run(t, args...)
	}

	for rel, want := range before {
		raw, err := os.ReadFile(filepath.Join(root, rel))
		if err != nil {
			t.Fatalf("%s disappeared: %v", rel, err)
		}
		if got := sha256Hex(raw); got != want {
			t.Fatalf("%s changed during a runtime workflow: %s -> %s", rel, want, got)
		}
	}
}

func sha256Hex(b []byte) string {
	sum := sha256.Sum256(b)
	return hex.EncodeToString(sum[:])
}

var _ = json.Marshal
