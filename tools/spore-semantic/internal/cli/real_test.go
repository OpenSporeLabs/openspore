package cli

import (
	"bytes"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"testing"
)

// repoRoot walks up from the test's working directory to the OpenSpore
// checkout, identified by the two git-tracked artifacts this tool reads.
func repoRoot(t *testing.T) string {
	t.Helper()
	dir, err := os.Getwd()
	if err != nil {
		t.Fatalf("Getwd: %v", err)
	}
	for {
		if fileExists(filepath.Join(dir, "reconstruction/knowledge/index.json")) &&
			fileExists(filepath.Join(dir, "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl")) {
			return dir
		}
		parent := filepath.Dir(dir)
		if parent == dir {
			t.Skip("no OpenSpore checkout above the test working directory")
		}
		dir = parent
	}
}

func fileExists(path string) bool {
	st, err := os.Stat(path)
	return err == nil && st.Mode().IsRegular()
}

const (
	sporeBinarySHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
	sporeImageBase = "0x00400000"
)

// realSnapshot is exported once for the whole package into a directory that
// outlives any single test, because t.TempDir() is per-test and the real
// export is ~2s of work.
var (
	realSnapshotOnce sync.Once
	realSnapshotPath string
	realSnapshotErr  error
)

// TestMain owns the shared snapshot's directory.
func TestMain(m *testing.M) {
	code := m.Run()
	if realDir != "" {
		os.RemoveAll(realDir)
	}
	os.Exit(code)
}

var realDir string

func exportReal(t *testing.T) string {
	t.Helper()
	realSnapshotOnce.Do(func() {
		if realDir == "" {
			realDir, realSnapshotErr = os.MkdirTemp("", "spore-semantic-real-*")
			if realSnapshotErr != nil {
				return
			}
		}
		root := repoRoot(t)
		realSnapshotPath = filepath.Join(realDir, "passport.jsonl")
		r := run(t, "export", "--root", root, "--out", realSnapshotPath)
		if r.code != ExitOK {
			realSnapshotErr = fmt.Errorf("export from the real checkout failed (%d): %s%s", r.code, r.stdout, r.stderr)
		}
	})
	if realSnapshotErr != nil {
		if strings.Contains(realSnapshotErr.Error(), "no OpenSpore checkout") {
			t.Skip(realSnapshotErr.Error())
		}
		t.Fatal(realSnapshotErr)
	}
	return realSnapshotPath
}

func lookupJSON(t *testing.T, snap, va string) (result, map[string]any) {
	t.Helper()
	r := run(t, "lookup", va, "--snapshot", snap, "--json")
	var payload map[string]any
	if strings.HasPrefix(strings.TrimSpace(r.stdout), "{") {
		if err := json.Unmarshal([]byte(r.stdout), &payload); err != nil {
			t.Fatalf("lookup %s emitted invalid JSON: %v\n%s", va, err, r.stdout)
		}
	}
	return r, payload
}

// TestRealExportCoversThePinnedUniverse asserts the exported population against
// numbers the repository itself states, not against a snapshot of itself.
func TestRealExportCoversThePinnedUniverse(t *testing.T) {
	snap := exportReal(t)
	r := run(t, "stats", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("stats failed: %s", r.stderr)
	}
	p := r.json(t)
	if p["binary_sha256"] != sporeBinarySHA {
		t.Fatalf("binary_sha256 = %v, want %s", p["binary_sha256"], sporeBinarySHA)
	}
	if p["image_base"] != sporeImageBase {
		t.Fatalf("image_base = %v, want %s", p["image_base"], sporeImageBase)
	}
	// Every committed statement of the function-universe size: the 58,757-row
	// assertion in tools/triage/export_xrefs.py and classify.py, the
	// xrefs-2540f2ca.summary.json closure note, and
	// knowledgegraph/research/21-decompilation-coverage.json's canonical_universe.
	if got := p["functions"].(float64); got != 58757 {
		t.Fatalf("exported %v functions, want the pinned universe of 58757", got)
	}
	r2 := run(t, "validate", "--snapshot", snap)
	if r2.code != ExitOK {
		t.Fatalf("validate failed on a freshly exported snapshot: %s%s", r2.stdout, r2.stderr)
	}
}

func TestRealExportIsByteIdenticalTwice(t *testing.T) {
	root := repoRoot(t)
	a := filepath.Join(t.TempDir(), "a.jsonl")
	b := filepath.Join(t.TempDir(), "b.jsonl")
	for _, out := range []string{a, b} {
		if r := run(t, "export", "--root", root, "--out", out); r.code != ExitOK {
			t.Fatalf("export failed: %s%s", r.stdout, r.stderr)
		}
	}
	da, err := os.ReadFile(a)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	db, err := os.ReadFile(b)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	if !bytes.Equal(da, db) {
		t.Fatalf("two exports from the same checkout state are not byte-identical (%d vs %d bytes)", len(da), len(db))
	}
	if len(da) == 0 {
		t.Fatalf("export produced an empty file")
	}
}

// TestRealRepresentativeLookups walks the representative cases the tool is
// meant to answer, using VAs whose evidence is already established in the
// repository. Nothing here invents an expected semantic: each assertion is
// about what an artifact states, or about the tool's own behaviour.
func TestRealRepresentativeLookups(t *testing.T) {
	snap := exportReal(t)

	t.Run("promoted function with a full reconstruction record", func(t *testing.T) {
		// 0x0040ccb0: Wave 6 presentation package, SDK-named, evidence pack,
		// validation report, integrated and approved. Its promotion state is
		// whatever the artifacts say -- the assertion is that the group is
		// available and carries a tri-state promotion, not a guess.
		r, p := lookupJSON(t, snap, "0x0040ccb0")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if p["canonical_va"] != "0x0040ccb0" {
			t.Fatalf("canonical_va = %v", p["canonical_va"])
		}
		names := p["names"].(map[string]any)
		if names["sdk_name"] == nil {
			t.Fatalf("this function is SDK-named in the triage export; the sdk_name was dropped")
		}
		if names["sdk_name_source"] != "sdk_functions.tsv" {
			t.Fatalf("sdk_name_source = %v", names["sdk_name_source"])
		}
		rec := p["reconstruction"].(map[string]any)
		if rec["state"] != "available" {
			t.Fatalf("reconstruction state = %v", rec["state"])
		}
		v := rec["value"].(map[string]any)
		if v["package"] == nil {
			t.Fatalf("reconstruction package was dropped")
		}
		promoted, ok := v["promoted"].(string)
		if !ok || (promoted != "true" && promoted != "false") {
			t.Fatalf("promoted = %v, want an explicit true or false", v["promoted"])
		}
		if promoted == "true" && v["promotion_schema"] == nil {
			t.Fatalf("promoted without a promotion record schema")
		}
		abi := p["abi"].(map[string]any)
		if abi["state"] != "available" {
			t.Fatalf("this function has an evidence pack with an ABI record; abi state = %v", abi["state"])
		}
		abiVal := abi["value"].(map[string]any)
		if abiVal["origin"] != "abi_inference" {
			t.Fatalf("abi origin = %v", abiVal["origin"])
		}
		recv := abiVal["receiver"].(map[string]any)
		if recv["present"] != "true" && recv["present"] != "false" && recv["present"] != "null" {
			t.Fatalf("receiver.present = %v, want a tri-state", recv["present"])
		}
	})

	t.Run("UNKNOWN ABI function", func(t *testing.T) {
		// 0x0041dc10 has an evidence pack whose ABI record abstains.
		r, p := lookupJSON(t, snap, "0x0041dc10")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		abi := p["abi"].(map[string]any)
		if abi["state"] != "available" {
			t.Fatalf("abi state = %v, want available (a record exists)", abi["state"])
		}
		if abi["evidence_level"] != "UNKNOWN" {
			t.Fatalf("an abstaining ABI record reported level %v", abi["evidence_level"])
		}
		v := abi["value"].(map[string]any)
		if v["convention"] != nil {
			t.Fatalf("convention = %v, want null", v["convention"])
		}
		if v["verdict"] != "ABI_UNKNOWN" {
			t.Fatalf("verdict = %v", v["verdict"])
		}
		recv := v["receiver"].(map[string]any)
		if recv["present"] != "null" {
			t.Fatalf("receiver.present = %v, want null", recv["present"])
		}
		h := run(t, "lookup", "0x0041dc10", "--snapshot", snap)
		if !strings.Contains(h.stdout, "present=null") {
			t.Fatalf("human output did not keep the unknown receiver distinct:\n%s", h.stdout)
		}
	})

	t.Run("vftable-backed function", func(t *testing.T) {
		// 0x00402ab0 is a member of two scanned tables; the assertion is that
		// (table_va, slot) pairs come through with a width where the scan
		// stated one.
		r, p := lookupJSON(t, snap, "0x00402ab0")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		vt := p["vtable"].(map[string]any)
		if vt["state"] != "available" {
			t.Fatalf("vtable state = %v", vt["state"])
		}
		v := vt["value"].(map[string]any)
		members, _ := v["memberships"].([]any)
		if len(members) == 0 {
			t.Fatalf("no memberships for a function the scan lists as a member")
		}
		first := members[0].(map[string]any)
		if first["table_va"] == nil || first["slot"] == nil {
			t.Fatalf("membership lacks table_va/slot: %v", first)
		}
		if _, ok := v["abi_attributed"]; !ok {
			t.Fatalf("abi_attributed key is missing entirely; it must be null when absent, not omitted")
		}
	})

	t.Run("RenderWare function", func(t *testing.T) {
		// 0x011ee700 is RenderWare::CompiledState::SetRaster in the triage
		// export: an SDK name, an /Spore/RenderWare/... struct and the
		// RenderWare subsystem.
		r, p := lookupJSON(t, snap, "0x011ee700")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		cls := p["semantic_classification"].(map[string]any)
		if cls["renderware_role"] == nil {
			t.Fatalf("RenderWare classification was dropped for %v", p["canonical_va"])
		}
		names := p["names"].(map[string]any)
		if names["sdk_name"] != "RenderWare::CompiledState::SetRaster" {
			t.Fatalf("sdk_name = %v", names["sdk_name"])
		}
		structs, _ := cls["sdk_structs"].([]any)
		found := false
		for _, s := range structs {
			if strings.Contains(s.(string), "RenderWare") {
				found = true
			}
		}
		if !found {
			t.Fatalf("sdk_structs = %v, expected a RenderWare struct", structs)
		}
	})

	t.Run("interior VA resolves to its containing function", func(t *testing.T) {
		// 0x00e3a400 is an interior address of 0x00e3a270; the knowledge index
		// already records that resolution, so the snapshot must agree.
		r, p := lookupJSON(t, snap, "0x00e3a400")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if p["requested_va"] != "0x00e3a400" {
			t.Fatalf("requested_va = %v", p["requested_va"])
		}
		if p["canonical_va"] != "0x00e3a270" {
			t.Fatalf("canonical_va = %v, want 0x00e3a270", p["canonical_va"])
		}
		res := p["identity_resolution"].(map[string]any)
		if res["rule"] != "containing_function_entry" {
			t.Fatalf("rule = %v", res["rule"])
		}
		if res["offset"].(float64) != 400 {
			t.Fatalf("offset = %v, want 400", res["offset"])
		}
		recorded := res["recorded"].(map[string]any)
		if recorded["canonical_va"] != "0x00e3a270" {
			t.Fatalf("the knowledge index's own recorded resolution was dropped: %v", recorded)
		}
	})

	t.Run("padding VA is not a function", func(t *testing.T) {
		// 0x00925050 lies between FUN_00925000 (0x4a bytes, ending 0x0092504a)
		// and FUN_009250c0. The conservative rule must leave it alone.
		r, p := lookupJSON(t, snap, "0x00925050")
		if r.code != ExitUnknownFunction {
			t.Fatalf("exit %d, want %d for an address in the gap between two bodies", r.code, ExitUnknownFunction)
		}
		if p["error"] != "unknown_function" {
			t.Fatalf("error = %v", p["error"])
		}
		if p["requested_va"] != "0x00925050" {
			t.Fatalf("the failure does not name the requested address: %v", p["requested_va"])
		}
		// And the human form says it too.
		h := run(t, "lookup", "0x00925050", "--snapshot", snap)
		if !strings.Contains(h.stderr, "0x00925050") {
			t.Fatalf("stderr does not name the requested address: %q", h.stderr)
		}
	})

	t.Run("address far outside the universe", func(t *testing.T) {
		r, _ := lookupJSON(t, snap, "0x7fff0000")
		if r.code != ExitUnknownFunction {
			t.Fatalf("exit %d, want %d", r.code, ExitUnknownFunction)
		}
	})

	t.Run("refuted identity is carried", func(t *testing.T) {
		// 0x008414c0: the knowledge index records one identity refutation, the
		// worker metadata overriding ArgScript::FormatParser::ParseFloat.
		r, p := lookupJSON(t, snap, "0x008414c0")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		ref := p["names"].(map[string]any)["identity_refuted"]
		if ref == nil {
			t.Fatalf("the recorded identity refutation was dropped")
		}
		m := ref.(map[string]any)
		if m["superseded"] != "ArgScript::FormatParser::ParseFloat" {
			t.Fatalf("superseded = %v", m["superseded"])
		}
		// reason is an object keyed by failure mode and must not be flattened.
		if _, isObject := m["reason"].(map[string]any); !isObject {
			t.Fatalf("the refutation reason lost its shape: %#v", m["reason"])
		}
	})

	t.Run("validation vocabulary is preserved verbatim", func(t *testing.T) {
		// 0x00c0bbd0 has a promotion record and a validation report.
		r, p := lookupJSON(t, snap, "0x00c0bbd0")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		rec := p["reconstruction"].(map[string]any)
		if rec["state"] != "available" {
			t.Fatalf("reconstruction state = %v", rec["state"])
		}
		v := rec["value"].(map[string]any)
		if v["promoted"] != "true" {
			t.Fatalf("promoted = %v; this function has a promotion record", v["promoted"])
		}
		validation := v["validation"].(map[string]any)
		if validation["schema"] != "openspore-structural-validation-1" {
			t.Fatalf("validation schema = %v", validation["schema"])
		}
		checks := validation["coverage"].(map[string]any)
		abi, ok := checks["ABI"].(map[string]any)
		if !ok {
			t.Fatalf("the ABI dimension is missing: %v", checks)
		}
		switch abi["status"] {
		case "PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE":
		default:
			t.Fatalf("validation status %v is outside the documented vocabulary", abi["status"])
		}
		switch abi["coverage"] {
		case "none", "partial", "complete":
		default:
			t.Fatalf("validation coverage %v is outside the documented vocabulary", abi["coverage"])
		}
		rt := validation["runtime"].(map[string]any)
		if rt["status"] != "GATED" {
			t.Fatalf("runtime status = %v", rt["status"])
		}
		if !strings.Contains(rt["detail"].(string), "nothing was attempted") {
			t.Fatalf("the runtime gate's own wording was lost: %v", rt["detail"])
		}
	})
}

func TestRealLookupIsStableAndFastEnough(t *testing.T) {
	snap := exportReal(t)
	var prev string
	for i := 0; i < 3; i++ {
		r := run(t, "lookup", "0x0040ccb0", "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if i > 0 && r.stdout != prev {
			t.Fatalf("repeated loads of the same snapshot gave different JSON")
		}
		prev = r.stdout
	}
}

func TestRealLookupSymbolResolvesAndReportsAmbiguity(t *testing.T) {
	snap := exportReal(t)
	r := run(t, "lookup-symbol", "RenderWare::CompiledState::SetRaster", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("SDK-name lookup failed (%d): %s", r.code, r.stderr)
	}
	if !strings.Contains(r.stdout, "0x011ee700") {
		t.Fatalf("SDK-name lookup did not reach the SDK-named function:\n%s", r.stdout)
	}
	missing := run(t, "lookup-symbol", "definitely::not::a::symbol", "--snapshot", snap)
	if missing.code != ExitUnknownSymbol {
		t.Fatalf("missing symbol exited %d, want %d", missing.code, ExitUnknownSymbol)
	}
}

func TestRealStatsCoversWhatTheExportPromised(t *testing.T) {
	snap := exportReal(t)
	r := run(t, "stats", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("stats failed: %s", r.stderr)
	}
	counts := r.json(t)["counts"].(map[string]any)
	checks := map[string]int{
		// Floors only. Each is bounded above by the corresponding artifact's
		// own size, which is why these can be asserted without inventing
		// semantics.
		"with_sdk_name":          1000,
		"with_abi_data":          400,
		"with_abi_unknown":       200,
		"with_vtable_membership": 6000,
		"with_promotion":         90,
		"with_validation":        670,
		"with_semantics":         500,
		"with_subsystem":         50000,
	}
	for name, floor := range checks {
		got, ok := counts[name].(float64)
		if !ok {
			t.Fatalf("counts.%s is missing", name)
		}
		if int(got) < floor {
			t.Fatalf("counts.%s = %v, expected at least %d", name, got, floor)
		}
	}
	// The SDK export has 1,663 unique VAs and 1,186 of them are NOT function
	// entries, so the ceiling is 1,663.
	if got := counts["with_sdk_name"].(float64); got > 1663 {
		t.Fatalf("with_sdk_name = %v, above the 1,663 unique rows in sdk_functions.tsv", got)
	}
	// Every function gets a subsystem from either the index or the triage row.
	if got := counts["with_subsystem"].(float64); got != 58757 {
		t.Fatalf("with_subsystem = %v, want all 58757", got)
	}
	if counts["explicitly_unavailable"].(float64) <= 0 {
		t.Fatalf("explicitly_unavailable = %v, want a positive count", counts["explicitly_unavailable"])
	}
}

func TestRealExportReportsItsInputsAndAbsentOnes(t *testing.T) {
	snap := exportReal(t)
	raw, err := os.ReadFile(snap)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	firstLine := raw[:indexByte(raw, '\n')]
	var meta map[string]any
	if err := json.Unmarshal(firstLine, &meta); err != nil {
		t.Fatalf("metadata line is not JSON: %v\n%s", err, firstLine)
	}
	if meta["record"] != "metadata" {
		t.Fatalf("line 1 record = %v, want metadata", meta["record"])
	}
	if meta["content_sha256"] == "" {
		t.Fatalf("metadata carries no content digest")
	}
	inputs := meta["inputs"].([]any)
	paths := map[string]bool{}
	for _, in := range inputs {
		m := in.(map[string]any)
		if m["sha256"] == "" || m["sha256"] == nil {
			t.Fatalf("input %v has no digest", m["path"])
		}
		paths[m["path"].(string)] = true
	}
	for _, want := range []string{
		"knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
		"knowledgegraph/triage/xrefs-2540f2ca.tsv",
		"knowledgegraph/triage/datarefs-2540f2ca.tsv",
		"reconstruction/knowledge/index.json",
	} {
		if !paths[want] {
			t.Fatalf("the export did not record reading %s (recorded: %v)", want, keys(paths))
		}
	}
	// Evidence-pack digests are recorded per pack.
	foundPack := false
	for p := range paths {
		if strings.HasPrefix(p, "reconstruction/evidence/") {
			foundPack = true
		}
	}
	if !foundPack {
		t.Fatalf("no evidence pack digest recorded")
	}
}

func indexByte(b []byte, c byte) int {
	for i := range b {
		if b[i] == c {
			return i
		}
	}
	return len(b)
}

func keys(m map[string]bool) []string {
	out := make([]string, 0, len(m))
	for k := range m {
		out = append(out, k)
	}
	return out
}
