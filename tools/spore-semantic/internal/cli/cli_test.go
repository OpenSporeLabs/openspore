package cli

import (
	"bytes"
	"encoding/json"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/testfixture"
)

// ---- harness --------------------------------------------------------------

type result struct {
	code   int
	stdout string
	stderr string
}

func (r result) json(t *testing.T) map[string]any {
	t.Helper()
	var out map[string]any
	if err := json.Unmarshal([]byte(r.stdout), &out); err != nil {
		t.Fatalf("stdout is not JSON (%v):\n%s", err, r.stdout)
	}
	return out
}

func run(t *testing.T, args ...string) result {
	t.Helper()
	var so, se bytes.Buffer
	code := Run(args, Env{Stdout: &so, Stderr: &se})
	return result{code: code, stdout: so.String(), stderr: se.String()}
}

// fixtureExport exports a snapshot from a synthetic checkout and returns its
// path.
func fixtureExport(t *testing.T, tr *testfixture.Tree) string {
	t.Helper()
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	snap := filepath.Join(tr.Root, "passport.jsonl")
	r := run(t, "export", "--root", tr.Root, "--out", snap)
	if r.code != ExitOK {
		t.Fatalf("export failed with %d: %s%s", r.code, r.stdout, r.stderr)
	}
	return snap
}

func baseFixture(t *testing.T) *testfixture.Tree {
	t.Helper()
	tr := testfixture.New(t)
	t.Cleanup(func() { os.RemoveAll(tr.Root) })
	tr.Functions = []testfixture.Function{
		{VA: 0x00401000, Name: "FUN_00401000", Size: 0x20},
		{VA: 0x00401020, Name: "FUN_00401020", Size: 0x10},
		{VA: 0x00401030, Name: "thunk_FUN_00401000", Size: 0x06, IsThunk: true},
		{VA: 0x00402000, Name: "Editors::IBakeManager::Get", Size: 0x40},
		{VA: 0x00925000, Name: "FUN_00925000", Size: 0x4a},
		{VA: 0x009250c0, Name: "FUN_009250c0", Size: 0x30},
		{VA: 0x00401200, Name: "FUN_dupe", Size: 0x10},
		{VA: 0x00401300, Name: "FUN_dupe", Size: 0x10},
	}
	tr.Triage = []testfixture.Triage{
		{VA: 0x00401000, GhidraName: "FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App", SCCSize: 1},
		{VA: 0x00401020, GhidraName: "FUN_00401020", Category: "UNKNOWN", Priority: "P3", Evidence: "UNKNOWN", SCCSize: 1},
		{VA: 0x00401030, GhidraName: "thunk_FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "IGNORE", Evidence: "UNKNOWN", SCCSize: 1},
		{VA: 0x00402000, GhidraName: "Editors::IBakeManager::Get", SDKName: "Editors::IBakeManager::Get", Category: "ENGINE_INTERFACE", Priority: "P3", Evidence: "CONFIRMED", Subsystem: "Editors", Structs: []string{"/Spore/Editors/IBakeManager"}, SCCSize: 1},
		{VA: 0x00925000, GhidraName: "FUN_00925000", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P1", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
		{VA: 0x009250c0, GhidraName: "FUN_009250c0", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P2", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
		{VA: 0x00401200, GhidraName: "FUN_dupe", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App", SCCSize: 1},
		{VA: 0x00401300, GhidraName: "FUN_dupe", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App", SCCSize: 1},
	}
	tr.XRefs = []testfixture.XRef{
		{Caller: 0x00402000, Callee: 0x00401000, RefType: "direct-call"},
		{Caller: 0x00401000, Callee: 0x00925000, RefType: "direct-call"},
	}
	tr.DataRefs = []testfixture.DataRef{{Caller: 0x00401000, Target: 0x015d0c00, Access: "read"}}
	tr.Memberships = []testfixture.Membership{
		{VA: 0x00401000, Table: 0x013eb308, Slot: 2},
		{VA: 0x00401020, Table: 0x013eb2f0, Slot: 0},
	}
	tr.Packs[0x00401000] = true
	tr.Packs[0x00401020] = true
	slot := 8
	tr.ABIRecords[0x00401000] = testfixture.ABIRecordJSON(ptr("__thiscall"), "INFERRED", ptrB(true), &slot)
	// An ABI record that abstains: the convention is null. This is the
	// UNKNOWN-ABI case, and it is different from having no pack at all.
	tr.ABIRecords[0x00401020] = testfixture.ABIRecordJSON(nil, "UNKNOWN", nil, nil)
	tr.Validation[0x00401000] = testfixture.ValidationDoc{
		Schema: "openspore-structural-validation-1",
		Checks: map[string]testfixture.Check{
			"ABI":     {Status: "PASS", Coverage: "partial", Detail: "convention present"},
			"GLOBALS": {Status: "NOT_AVAILABLE", Coverage: "none", Detail: "no data refs"},
		},
	}
	tr.Promoted[0x00401000] = true
	tr.RecordOverrides["0x00401000"] = map[string]any{
		"package": "PKG-FIXTURE", "status": "reconstructed",
		"review_status": "approved", "integration_status": "integrated",
		"runtime_gated": true, "runtime_validated": 0,
		"semantic": map[string]any{
			"classification": "BOUNDED_SEMANTIC",
			"confidence":     map[string]any{"identity": "SUPPORTED", "mechanics": 0.72},
			"evidence":       []any{map[string]any{"claim": "reads +0x10", "class": "direct_body", "source": "ghidra://x"}},
		},
		"unresolved_questions": []string{"what the selector hash is OF"},
		"globals":              []string{"global:0x015d0c00"},
		"types":                []string{"Transform"},
	}
	return tr
}

func ptr(s string) *string { return &s }
func ptrB(b bool) *bool    { return &b }

// ---- lookup ---------------------------------------------------------------

func TestLookupExactVA(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	if p["requested_va"] != "0x00401000" || p["canonical_va"] != "0x00401000" {
		t.Fatalf("identity echoed wrong: requested=%v canonical=%v", p["requested_va"], p["canonical_va"])
	}
	if p["identity_resolution"] != nil {
		t.Fatalf("an exact entry reported a resolution: %v", p["identity_resolution"])
	}
	if p["binary_sha256"] != testfixture.BinarySHA {
		t.Fatalf("binary_sha256 = %v", p["binary_sha256"])
	}
	if p["rva"] != "0x00001000" {
		t.Fatalf("rva = %v, want 0x00001000", p["rva"])
	}
	abi := p["abi"].(map[string]any)
	if abi["state"] != "available" {
		t.Fatalf("abi state = %v", abi["state"])
	}
	abiVal := abi["value"].(map[string]any)
	if abiVal["convention"] != "__thiscall" || abiVal["convention_confidence"] != "INFERRED" {
		t.Fatalf("abi value = %v", abiVal)
	}
	receiver := abiVal["receiver"].(map[string]any)
	if receiver["present"] != "true" || receiver["register"] != "ECX" {
		t.Fatalf("receiver = %v", receiver)
	}
}

func TestLookupAcceptsEveryAddressSpelling(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	// All of these name 0x00401000. Bare digits are hex; decimal is explicit.
	inputs := []string{
		"0x00401000", "0x401000", "00401000", "401000",
		"0X00401000", "dec:4198400", "0d4198400",
		"rva:00001000", "  0x00401000 ",
	}
	var first map[string]any
	for _, in := range inputs {
		r := run(t, "lookup", in, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("lookup %q exited %d: %s", in, r.code, r.stderr)
		}
		p := r.json(t)
		if p["canonical_va"] != "0x00401000" {
			t.Fatalf("lookup %q resolved to %v, want 0x00401000", in, p["canonical_va"])
		}
		if first == nil {
			first = p
			continue
		}
		// requested_va is canonicalised, so two spellings of one address must
		// produce byte-identical output.
		if mustJSON(t, p) != mustJSON(t, first) {
			t.Fatalf("lookup %q produced different JSON from the first spelling", in)
		}
	}
}

func TestLookupRejectsAnRVAspelledAsAVA(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	// 0x00001000 as a VA is below the image base and is not a function; the
	// rva: spelling is the one that reaches 0x00401000. They must differ.
	bare := run(t, "lookup", "0x00001000", "--snapshot", snap, "--json")
	if bare.code != ExitUnknownFunction {
		t.Fatalf("an RVA spelled as a VA returned exit %d, want %d", bare.code, ExitUnknownFunction)
	}
	viaRVA := run(t, "lookup", "rva:00001000", "--snapshot", snap, "--json")
	if viaRVA.code != ExitOK {
		t.Fatalf("the explicit rva: spelling failed with %d: %s", viaRVA.code, viaRVA.stderr)
	}
	if viaRVA.json(t)["canonical_va"] != "0x00401000" {
		t.Fatalf("rva: did not resolve to 0x00401000")
	}
}

func TestLookupInteriorVACanonicalizes(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401010", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	if p["requested_va"] != "0x00401010" || p["canonical_va"] != "0x00401000" {
		t.Fatalf("interior lookup echoed requested=%v canonical=%v", p["requested_va"], p["canonical_va"])
	}
	res := p["identity_resolution"].(map[string]any)
	if res["rule"] != "containing_function_entry" {
		t.Fatalf("rule = %v", res["rule"])
	}
	if res["offset"].(float64) != 16 {
		t.Fatalf("offset = %v, want 16", res["offset"])
	}
	rng := res["range"].(map[string]any)
	if rng["start"] != "0x00401000" || rng["end"] != "0x00401020" {
		t.Fatalf("range = %v", rng)
	}
}

func TestLookupUnknownVAIsExplicitNotEmpty(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	// 0x00925050 is in the padding between two known bodies.
	r := run(t, "lookup", "0x00925050", "--snapshot", snap, "--json")
	if r.code != ExitUnknownFunction {
		t.Fatalf("exit %d, want %d", r.code, ExitUnknownFunction)
	}
	p := r.json(t)
	if p["error"] != "unknown_function" {
		t.Fatalf("error = %v", p["error"])
	}
	if p["identity_resolution"] != nil {
		t.Fatalf("an unknown VA reported a resolution: %v", p["identity_resolution"])
	}
	msg, _ := p["message"].(string)
	if !strings.Contains(msg, "0x00925050") || !strings.Contains(msg, testfixture.BinarySHA[:16]) {
		t.Fatalf("the message does not name the address and the binary: %q", msg)
	}
	if strings.Contains(r.stdout, `"identity":`) {
		t.Fatalf("an unknown lookup emitted a record-shaped object")
	}

	// And the human form goes to stderr with the same exit code.
	h := run(t, "lookup", "0x00925050", "--snapshot", snap)
	if h.code != ExitUnknownFunction {
		t.Fatalf("human-form exit %d, want %d", h.code, ExitUnknownFunction)
	}
	if !strings.Contains(h.stderr, "unknown function") {
		t.Fatalf("human-form stderr = %q", h.stderr)
	}
	if strings.TrimSpace(h.stdout) != "" {
		t.Fatalf("human-form failure wrote to stdout: %q", h.stdout)
	}
}

func TestLookupIsByteStableAcrossRepeatedRuns(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	var prev string
	for i := 0; i < 5; i++ {
		r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if i > 0 && r.stdout != prev {
			t.Fatalf("run %d produced different JSON from run 0", i)
		}
		prev = r.stdout
	}
}

func TestLookupUnknownABIAndReceiver(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401020", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	abi := r.json(t)["abi"].(map[string]any)
	if abi["state"] != "available" {
		t.Fatalf("the ABI group should be available (a record exists); got %v", abi["state"])
	}
	if abi["evidence_level"] != "UNKNOWN" {
		t.Fatalf("an abstaining ABI record reported %v", abi["evidence_level"])
	}
	v := abi["value"].(map[string]any)
	if v["convention"] != nil {
		t.Fatalf("convention = %v, want null for an undetermined convention", v["convention"])
	}
	if v["verdict"] != "ABI_UNKNOWN" {
		t.Fatalf("verdict = %v, want ABI_UNKNOWN", v["verdict"])
	}
	recv := v["receiver"].(map[string]any)
	if recv["present"] != "null" {
		t.Fatalf("receiver.present = %v, want the string null so an unknown receiver is not read as false", recv["present"])
	}
	if recv["register"] != nil {
		t.Fatalf("receiver.register = %v, want null", recv["register"])
	}

	// The human form must also render null distinctly from false.
	h := run(t, "lookup", "0x00401020", "--snapshot", snap)
	if !strings.Contains(h.stdout, "present=null") {
		t.Fatalf("human output did not render an unknown receiver distinctly:\n%s", h.stdout)
	}
	if strings.Contains(h.stdout, "present=false") {
		t.Fatalf("human output rendered an unknown receiver as false")
	}
	if !strings.Contains(h.stdout, "convention        UNKNOWN") {
		t.Fatalf("human output did not render an UNKNOWN convention:\n%s", h.stdout)
	}
}

func TestLookupKnownAndMissingVTable(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)

	known := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	vt := known.json(t)["vtable"].(map[string]any)
	if vt["state"] != "available" {
		t.Fatalf("vtable state = %v", vt["state"])
	}
	v := vt["value"].(map[string]any)
	members := v["memberships"].([]any)
	if len(members) != 1 {
		t.Fatalf("memberships = %v, want 1", members)
	}
	m := members[0].(map[string]any)
	if m["table_va"] != "0x013eb308" || m["slot"].(float64) != 2 {
		t.Fatalf("membership = %v", m)
	}
	attributed := v["abi_attributed"].(map[string]any)
	if attributed["table_va"] != "0x013f57f8" || attributed["slot"].(float64) != 8 ||
		attributed["rule"] != "R1-VFT" || attributed["confidence"] != "INFERRED" {
		t.Fatalf("abi_attributed = %v", attributed)
	}

	// 0x00402000 has no membership anywhere: an explicit absence, not a
	// claim that the function is not virtual.
	missing := run(t, "lookup", "0x00402000", "--snapshot", snap, "--json")
	mvt := missing.json(t)["vtable"].(map[string]any)
	if mvt["state"] != "unavailable" {
		t.Fatalf("vtable state = %v, want unavailable", mvt["state"])
	}
	if mvt["evidence_level"] != "UNKNOWN" || mvt["evidence_state"] != "MISSING" {
		t.Fatalf("an absent vtable group lost its UNKNOWN/MISSING markers: %v", mvt)
	}
	if mvt["reason"] != semantic.ReasonNoVTableMembership {
		t.Fatalf("reason = %v", mvt["reason"])
	}
	if _, present := mvt["value"]; present {
		t.Fatalf("an unavailable group emitted a value")
	}
	h := run(t, "lookup", "0x00402000", "--snapshot", snap)
	if !strings.Contains(h.stdout, "NOT to be virtual") {
		t.Fatalf("the human form did not explain the absence:\n%s", h.stdout)
	}
}

func TestLookupPromotedAndUnpromotedReconstruction(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)

	promoted := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	rec := promoted.json(t)["reconstruction"].(map[string]any)
	if rec["state"] != "available" {
		t.Fatalf("reconstruction state = %v", rec["state"])
	}
	v := rec["value"].(map[string]any)
	if v["package"] != "PKG-FIXTURE" || v["promoted"] != "true" ||
		v["static_status"] != "PASS" || v["promotion_schema"] != "openspore-promotion-record-1" {
		t.Fatalf("promoted record = %v", v)
	}
	checks := v["validation"].(map[string]any)["coverage"].(map[string]any)
	if checks["GLOBALS"].(map[string]any)["status"] != "NOT_AVAILABLE" {
		t.Fatalf("the validation vocabulary was not preserved verbatim: %v", checks["GLOBALS"])
	}
	if checks["GLOBALS"].(map[string]any)["coverage"] != "none" {
		t.Fatalf("validation coverage vocabulary was not preserved: %v", checks["GLOBALS"])
	}

	// 0x00401020 has an evidence pack and an ABI record but no campaign record
	// at all: an explicit absence, and promoted is an explicit FALSE, not an
	// unknown.
	unpromoted := run(t, "lookup", "0x00401020", "--snapshot", snap, "--json")
	urec := unpromoted.json(t)["reconstruction"].(map[string]any)
	if urec["state"] != "unavailable" {
		t.Fatalf("reconstruction state = %v", urec["state"])
	}
	if urec["reason"] != semantic.ReasonNoReconstruction {
		t.Fatalf("reason = %v", urec["reason"])
	}
	if urec["evidence_level"] != "UNKNOWN" || urec["evidence_state"] != "MISSING" {
		t.Fatalf("an absent reconstruction group lost its UNKNOWN/MISSING markers: %v", urec)
	}
	if _, present := urec["value"]; present {
		t.Fatalf("an unavailable reconstruction group emitted a value")
	}
	// Its evidence block still pins the pack that exists, and states that no
	// promotion record does.
	uev := unpromoted.json(t)["evidence"].(map[string]any)
	if uev["pack"] == nil {
		t.Fatalf("the existing evidence pack was dropped")
	}
	if uev["promotion_record"] != nil {
		t.Fatalf("a promotion record path was invented: %v", uev["promotion_record"])
	}
	if uev["validation_report"] == nil {
		t.Fatalf("the validation report path was dropped although none exists; it must be stated as absent")
	}
}

func TestLookupPreservesProvenance(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	prov := r.json(t)["provenance"].([]any)
	if len(prov) == 0 {
		t.Fatalf("provenance was dropped")
	}
	classes := map[string]bool{}
	for _, e := range prov {
		m := e.(map[string]any)
		for _, k := range []string{"mode", "ref", "source_class"} {
			if _, ok := m[k]; !ok {
				t.Fatalf("provenance entry is missing %q: %v", k, m)
			}
		}
		classes[m["source_class"].(string)] = true
	}
	if !classes["ghidra"] || !classes["generated_index"] {
		t.Fatalf("provenance lost a source class; got %v", classes)
	}
	// The evidence block pins the exact bytes projected from.
	ev := r.json(t)["evidence"].(map[string]any)
	if ev["pack"] == nil || ev["pack_state"] == nil || ev["target_address_kind"] != "linked_va" {
		t.Fatalf("evidence block = %v", ev)
	}
	// The ABI group's own provenance names the artifact it came from.
	abiProv := r.json(t)["abi"].(map[string]any)["provenance"].([]any)
	if len(abiProv) == 0 {
		t.Fatalf("an available ABI group carries no provenance")
	}
}

func TestLookupKeepsMachineAndSemanticFactsApart(t *testing.T) {
	tr := baseFixture(t)
	// Merge rather than replace, so the semantic record stays in place.
	override := tr.RecordOverrides["0x00401000"]
	override["abi"] = map[string]any{
		// A hand-written claim, in the same namespace as the machine record
		// but not from it.
		"calling_convention": "__thiscall observed",
		"return_type":        "Transform*",
	}
	tr.RecordOverrides["0x00401000"] = override
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	abiVal := r.json(t)["abi"].(map[string]any)["value"].(map[string]any)
	if abiVal["convention"] != "__thiscall" {
		t.Fatalf("the machine convention was overwritten by the declared one: %v", abiVal["convention"])
	}
	declared := abiVal["declared"].(map[string]any)
	if declared["calling_convention"] != "__thiscall observed" {
		t.Fatalf("the declared ABI was not carried in its own block: %v", declared)
	}
	if abiVal["origin"] != "abi_inference" {
		t.Fatalf("the machine ABI block does not say where it came from: %v", abiVal["origin"])
	}
	// Semantic interpretation lives in its own group.
	sem := r.json(t)["semantics"].(map[string]any)
	if sem["state"] != "available" || sem["value"].(map[string]any)["classification"] != "BOUNDED_SEMANTIC" {
		t.Fatalf("semantics = %v", sem)
	}
}

func TestSemanticsConfidenceKeepsMixedValueTypes(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	conf := r.json(t)["semantics"].(map[string]any)["value"].(map[string]any)["confidence"].(map[string]any)
	if conf["identity"] != "SUPPORTED" {
		t.Fatalf("a rung value lost its spelling: %v", conf["identity"])
	}
	if conf["mechanics"] != 0.72 {
		t.Fatalf("a numeric confidence was coerced into a string: %v (%T)", conf["mechanics"], conf["mechanics"])
	}
	h := run(t, "lookup", "0x00401000", "--snapshot", snap)
	if !strings.Contains(h.stdout, "mechanics") || !strings.Contains(h.stdout, "0.72") {
		t.Fatalf("the human form did not render the numeric confidence:\n%s", h.stdout)
	}
}

func TestRenderwareFunctionCarriesItsClassification(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00925000", "--snapshot", snap, "--json")
	cls := r.json(t)["semantic_classification"].(map[string]any)
	if cls["renderware_role"] != "RenderWare" {
		t.Fatalf("renderware_role = %v", cls["renderware_role"])
	}
	if cls["subsystem"] != "RenderWare" {
		t.Fatalf("subsystem = %v", cls["subsystem"])
	}
}

// ---- lookup-symbol --------------------------------------------------------

func TestLookupSymbolSingleMatch(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup-symbol", "FUN_00401000", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	if p["matches"] != float64(1) {
		t.Fatalf("matches = %v", p["matches"])
	}
	if p["result"].(map[string]any)["canonical_va"] != "0x00401000" {
		t.Fatalf("resolved to the wrong function")
	}
}

func TestLookupSymbolAmbiguous(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup-symbol", "FUN_dupe", "--snapshot", snap, "--json")
	if r.code != ExitAmbiguousSymbol {
		t.Fatalf("exit %d, want %d", r.code, ExitAmbiguousSymbol)
	}
	p := r.json(t)
	if p["error"] != "ambiguous_symbol" {
		t.Fatalf("error = %v", p["error"])
	}
	vas := p["canonical_vas"].([]any)
	if len(vas) != 2 {
		t.Fatalf("canonical_vas = %v", vas)
	}
	// The human form lists both so the caller can pick by address.
	h := run(t, "lookup-symbol", "FUN_dupe", "--snapshot", snap)
	if !strings.Contains(h.stderr, "0x00401200") || !strings.Contains(h.stderr, "0x00401300") {
		t.Fatalf("human ambiguity report does not list both addresses:\n%s", h.stderr)
	}
}

func TestLookupSymbolMissing(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup-symbol", "NoSuchSymbolAnywhere", "--snapshot", snap, "--json")
	if r.code != ExitUnknownSymbol {
		t.Fatalf("exit %d, want %d", r.code, ExitUnknownSymbol)
	}
	if r.json(t)["error"] != "unknown_symbol" {
		t.Fatalf("error = %v", r.json(t)["error"])
	}
	if strings.Contains(r.stdout, `"identity":`) {
		t.Fatalf("a missing symbol emitted a record-shaped object")
	}
}

// ---- explain --------------------------------------------------------------

func TestExplainShowsProvenanceAndOpenQuestions(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "explain", "0x00401000", "--snapshot", snap)
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	for _, want := range []string{
		"WHY OPENSPORE BELIEVES THIS",
		"abi_inference",
		"UNRESOLVED QUESTIONS",
		"VALIDATION DETAIL",
		"vftable_slot",
	} {
		if !strings.Contains(r.stdout, want) {
			t.Fatalf("explain output is missing %q:\n%s", want, r.stdout)
		}
	}
}

func TestExplainInteriorVAReportsTheResolution(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "explain", "0x00401010", "--snapshot", snap)
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	if !strings.Contains(r.stdout, "0x00401010 -> 0x00401000") {
		t.Fatalf("explain did not report the canonicalization:\n%s", r.stdout)
	}
}

func TestExplainUnknownVA(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "explain", "0x00925050", "--snapshot", snap)
	if r.code != ExitUnknownFunction {
		t.Fatalf("exit %d, want %d", r.code, ExitUnknownFunction)
	}
	if strings.TrimSpace(r.stdout) != "" {
		t.Fatalf("explain wrote a report for an unknown function:\n%s", r.stdout)
	}
}

// ---- stats / validate -----------------------------------------------------

func TestStatsReportsCoverageAndAbsentInputs(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "stats", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	counts := p["counts"].(map[string]any)
	if counts["functions"].(float64) != 8 {
		t.Fatalf("functions = %v", counts["functions"])
	}
	if counts["with_sdk_name"].(float64) != 1 {
		t.Fatalf("with_sdk_name = %v", counts["with_sdk_name"])
	}
	if counts["with_abi_data"].(float64) != 1 || counts["with_abi_unknown"].(float64) != 1 {
		t.Fatalf("abi counters = %v / %v", counts["with_abi_data"], counts["with_abi_unknown"])
	}
	if counts["with_vtable_membership"].(float64) != 2 {
		t.Fatalf("with_vtable_membership = %v", counts["with_vtable_membership"])
	}
	if counts["with_promotion"].(float64) != 1 {
		t.Fatalf("with_promotion = %v", counts["with_promotion"])
	}
	if counts["explicitly_unavailable"].(float64) <= 0 {
		t.Fatalf("explicitly_unavailable = %v; explicit absences must be counted", counts["explicitly_unavailable"])
	}
	if p["ambiguous_names"].(float64) != 1 {
		t.Fatalf("ambiguous_names = %v", p["ambiguous_names"])
	}
	h := run(t, "stats", "--snapshot", snap)
	if !strings.Contains(h.stdout, "explicitly unavailable fact groups") {
		t.Fatalf("human stats omitted the explicit-absence rollup:\n%s", h.stdout)
	}
}

func TestStatsListsAbsentAuthoritativeInputs(t *testing.T) {
	tr := baseFixture(t)
	tr.OmitVTableScan = true
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	snap := filepath.Join(tr.Root, "passport.jsonl")
	if r := run(t, "export", "--root", tr.Root, "--out", snap); r.code != ExitOK {
		t.Fatalf("export: %s%s", r.stdout, r.stderr)
	}
	r := run(t, "stats", "--snapshot", snap, "--json")
	absent := r.json(t)["absent_inputs"].([]any)
	found := false
	for _, a := range absent {
		if strings.Contains(a.(map[string]any)["path"].(string), "vftables-") {
			found = true
			if a.(map[string]any)["reason"] == "" {
				t.Fatalf("an absent input was reported without a reason")
			}
		}
	}
	if !found {
		t.Fatalf("the absent vftable scan was not listed: %v", absent)
	}
	h := run(t, "stats", "--snapshot", snap)
	if !strings.Contains(h.stdout, "authoritative inputs absent") {
		t.Fatalf("human stats omitted the absent-inputs section:\n%s", h.stdout)
	}
}

func TestValidateAcceptsAFreshlyExportedSnapshot(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "validate", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	if p["ok"] != true {
		t.Fatalf("ok = %v, problems = %v", p["ok"], p["problems"])
	}
	if p["binary_sha256"] != testfixture.BinarySHA {
		t.Fatalf("binary_sha256 = %v", p["binary_sha256"])
	}
	if p["content_sha256"] == "" {
		t.Fatalf("validate did not report the content digest it checked")
	}
	h := run(t, "validate", "--snapshot", snap)
	if !strings.Contains(h.stdout, "result          OK") {
		t.Fatalf("human validate did not report OK:\n%s", h.stdout)
	}
}

func TestValidateRejectsACorruptedSnapshot(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	raw, err := os.ReadFile(snap)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	tampered := strings.Replace(string(raw), "FUN_00401000", "FUN_00401000X", 1)
	bad := filepath.Join(tr.Root, "corrupt.jsonl")
	if err := os.WriteFile(bad, []byte(tampered), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	r := run(t, "validate", "--snapshot", bad)
	if r.code != ExitCorruptSnapshot {
		t.Fatalf("exit %d, want %d", r.code, ExitCorruptSnapshot)
	}
	if !strings.Contains(r.stderr, "content_sha256") {
		t.Fatalf("the corruption was not named: %s", r.stderr)
	}
}

func TestValidateRejectsADuplicateCanonicalVA(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	raw, err := os.ReadFile(snap)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	lines := strings.Split(strings.TrimRight(string(raw), "\n"), "\n")
	dup := lines[2]
	lines = append(lines, dup)
	bad := filepath.Join(tr.Root, "dup.jsonl")
	if err := os.WriteFile(bad, []byte(strings.Join(lines, "\n")+"\n"), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	r := run(t, "validate", "--snapshot", bad)
	if r.code != ExitCorruptSnapshot || !strings.Contains(r.stderr, "duplicate canonical VA") {
		t.Fatalf("exit %d stderr %q, want a duplicate-VA corruption", r.code, r.stderr)
	}
}

// ---- failure modes --------------------------------------------------------

func TestBinaryMismatchIsItsOwnExitCode(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	var so, se bytes.Buffer
	code := Run([]string{"lookup", "0x00401000", "--snapshot", snap}, Env{
		Stdout: &so, Stderr: &se,
		RequireSHA: testfixture.OtherSHA,
	})
	if code != ExitBinaryMismatch {
		t.Fatalf("exit %d, want %d", code, ExitBinaryMismatch)
	}
	if !strings.Contains(se.String(), "binary mismatch") {
		t.Fatalf("stderr = %q", se.String())
	}
	if strings.Contains(se.String(), testfixture.BinarySHA[:16]) &&
		!strings.Contains(se.String(), "describes") {
		t.Fatalf("the mismatch message does not name the digests: %q", se.String())
	}
}

func TestUnsupportedSchemaIsItsOwnExitCode(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	raw, err := os.ReadFile(snap)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	bad := filepath.Join(tr.Root, "future.jsonl")
	txt := strings.Replace(string(raw), semantic.SnapshotSchema, "spore-semantic-snapshot-2", 1)
	if err := os.WriteFile(bad, []byte(txt), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	r := run(t, "lookup", "0x00401000", "--snapshot", bad)
	if r.code != ExitUnsupportedSchema {
		t.Fatalf("exit %d, want %d", r.code, ExitUnsupportedSchema)
	}
	if !strings.Contains(r.stderr, "unsupported schema") {
		t.Fatalf("stderr = %q", r.stderr)
	}
}

func TestMissingSnapshotIsItsOwnExitCode(t *testing.T) {
	dir := t.TempDir()
	r := run(t, "lookup", "0x00401000", "--snapshot", filepath.Join(dir, "nope.jsonl"))
	if r.code != ExitUnavailable {
		t.Fatalf("exit %d, want %d", r.code, ExitUnavailable)
	}
	if !strings.Contains(r.stderr, "snapshot not found") {
		t.Fatalf("stderr = %q", r.stderr)
	}
}

func TestUniverseUnavailableStopsTheExport(t *testing.T) {
	tr := baseFixture(t)
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	if err := os.Remove(filepath.Join(tr.Root, ".spore-analysis/ghidra-exports/functions.tsv")); err != nil {
		t.Fatalf("Remove: %v", err)
	}
	r := run(t, "export", "--root", tr.Root, "--out", filepath.Join(tr.Root, "x.jsonl"))
	if r.code != ExitUnavailable {
		t.Fatalf("exit %d, want %d", r.code, ExitUnavailable)
	}
	if !strings.Contains(r.stderr, "universe") {
		t.Fatalf("stderr = %q", r.stderr)
	}
}

func TestNoCommandIsAcceptedSilently(t *testing.T) {
	for _, args := range [][]string{
		{},
		{"nonsense"},
		{"lookup"},
		{"lookup", "0x00401000", "0x00401020"},
		{"lookup-symbol"},
		{"explain"},
		{"export", "extra-argument"},
		{"lookup", "--nosuchflag"},
	} {
		r := run(t, args...)
		if r.code != ExitUsage {
			t.Fatalf("args %v exited %d, want %d", args, r.code, ExitUsage)
		}
	}
}

func TestUsageAndVersion(t *testing.T) {
	u := run(t, "help")
	if u.code != ExitOK || !strings.Contains(u.stdout, "binary_sha256 + canonical VA") {
		t.Fatalf("help output = %q (exit %d)", u.stdout, u.code)
	}
	v := run(t, "version")
	if v.code != ExitOK || !strings.Contains(v.stdout, semantic.SnapshotSchema) {
		t.Fatalf("version output = %q", v.stdout)
	}
}

func TestFlagsMayFollowThePositionalArgument(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	r := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("a VA before the flags was not honoured: exit %d %s", r.code, r.stderr)
	}
	if !strings.HasPrefix(strings.TrimSpace(r.stdout), "{") {
		t.Fatalf("--json after the positional was dropped:\n%s", r.stdout)
	}
}

// ---- determinism ----------------------------------------------------------

func TestExportIsByteIdenticalOnRepeatedGeneration(t *testing.T) {
	tr := baseFixture(t)
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	var prev []byte
	for i := 0; i < 4; i++ {
		out := filepath.Join(t.TempDir(), "run.jsonl")
		r := run(t, "export", "--root", tr.Root, "--out", out)
		if r.code != ExitOK {
			t.Fatalf("export %d: %s%s", i, r.stdout, r.stderr)
		}
		data, err := os.ReadFile(out)
		if err != nil {
			t.Fatalf("ReadFile: %v", err)
		}
		if prev != nil && string(data) != string(prev) {
			t.Fatalf("export %d is not byte-identical to export 0", i)
		}
		prev = data
	}
}

func TestRepeatedLoadsGiveTheSameLookupResult(t *testing.T) {
	tr := baseFixture(t)
	snap := fixtureExport(t, tr)
	first := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json").stdout
	for i := 0; i < 4; i++ {
		again := run(t, "lookup", "0x00401000", "--snapshot", snap, "--json").stdout
		if again != first {
			t.Fatalf("load %d produced a different lookup result", i)
		}
	}
}

func mustJSON(t *testing.T, v any) string {
	t.Helper()
	b, err := json.Marshal(v)
	if err != nil {
		t.Fatalf("Marshal: %v", err)
	}
	return string(b)
}
