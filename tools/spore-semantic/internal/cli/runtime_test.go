package cli

import (
	"bytes"
	"encoding/json"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/testfixture"
)

// The representative addresses. 0x0040ccb0 and 0x00e3a400 are the ones the
// existing static tests already pin, 0x00925050 is the padding case that
// spore-recomp reached in a real run, and 0x00f9fef0 is a live ceiling.
const (
	rtPromotedVA    = 0x00401000 // stands in for 0x0040ccb0: promoted, with a NOT_AVAILABLE RETURN SEMANTICS dimension
	rtUnknownABIVA  = 0x00401020
	rtInteriorVA    = 0x00401010
	rtPaddingVA     = 0x00925050
	rtRuntimeOnlyVA = 0x00697c40
	rtIATSlotVA     = 0x013cc1cc
	rtCeilingVA     = 0x009250c0
)

// runtimeFixture exports a synthetic snapshot and writes a synthetic overlay that
// observes the representative addresses. Every value here is invented for the
// test; the real-artifact path is exercised separately below.
//
// It builds its own tree rather than reusing baseFixture, because it needs a
// validation report whose RETURN SEMANTICS dimension is NOT_AVAILABLE and whose
// VIRTUAL DISPATCH dimension is WARN -- the two states the joined view has to
// render -- and adding those to baseFixture would perturb the existing static
// tests.
func runtimeFixture(t *testing.T) (snap string, overlay string) {
	t.Helper()
	tr := runtimeTree(t)
	snap = fixtureExport(t, tr)
	overlay = runtimeOverlayFixture(t, snap)
	return snap, overlay
}

func runtimeTree(t *testing.T) *testfixture.Tree {
	t.Helper()
	tr := testfixture.New(t)
	t.Cleanup(func() { os.RemoveAll(tr.Root) })
	tr.Functions = []testfixture.Function{
		{VA: 0x00401000, Name: "FUN_00401000", Size: 0x20},
		{VA: 0x00401020, Name: "FUN_00401020", Size: 0x10},
		{VA: 0x00402000, Name: "Editors::IBakeManager::Get", Size: 0x40},
		{VA: 0x00925000, Name: "FUN_00925000", Size: 0x4a},
		{VA: 0x009250c0, Name: "FUN_009250c0", Size: 0x30},
	}
	tr.Triage = []testfixture.Triage{
		{VA: 0x00401000, GhidraName: "FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App"},
		{VA: 0x00401020, GhidraName: "FUN_00401020", Category: "UNKNOWN", Priority: "P3", Evidence: "UNKNOWN", Subsystem: "App"},
		{VA: 0x00402000, GhidraName: "Editors::IBakeManager::Get", SDKName: "Editors::IBakeManager::Get", Category: "ENGINE_INTERFACE", Priority: "P3", Evidence: "CONFIRMED", Subsystem: "Editors"},
		{VA: 0x00925000, GhidraName: "FUN_00925000", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P1", Evidence: "SUPPORTED", Subsystem: "RenderWare"},
		{VA: 0x009250c0, GhidraName: "FUN_009250c0", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P2", Evidence: "SUPPORTED", Subsystem: "RenderWare"},
	}
	tr.XRefs = []testfixture.XRef{{Caller: 0x00402000, Callee: 0x00401000, RefType: "direct-call"}}
	tr.Packs[0x00401000] = true
	tr.Packs[0x00401020] = true
	tr.ABIRecords[0x00401000] = testfixture.ABIRecordJSON(sPtr("__thiscall"), "INFERRED", bPtr(true), nil)
	tr.ABIRecords[0x00401020] = testfixture.ABIRecordJSON(nil, "UNKNOWN", nil, nil)
	tr.Validation[0x00401000] = testfixture.ValidationDoc{
		Schema: "openspore-structural-validation-1",
		Checks: map[string]testfixture.Check{
			"ABI":               {Status: "PASS", Coverage: "partial", Detail: "convention present"},
			"RETURN SEMANTICS":  {Status: "NOT_AVAILABLE", Coverage: "none", Detail: "the machine return state is UNCLASSIFIED"},
			"VIRTUAL DISPATCH":  {Status: "WARN", Coverage: "partial", Detail: "one membership, no attributed slot"},
			"EVIDENCE COVERAGE": {Status: "PASS", Coverage: "complete", Detail: "all categories available"},
		},
	}
	tr.Promoted[0x00401000] = true
	tr.RecordOverrides["0x00401000"] = map[string]any{
		"package": "PKG-FIXTURE", "status": "reconstructed",
		"review_status": "approved", "integration_status": "integrated",
		"runtime_gated": true, "runtime_validated": 0,
		"unresolved_questions": []string{"whether the selector hash is OF anything"},
	}
	tr.RecordOverrides["0x00402000"] = map[string]any{
		"package": "PKG-FIXTURE2", "status": "candidate",
	}
	return tr
}

func bPtr(b bool) *bool { return &b }

func runtimeOverlayFixture(t *testing.T, snap string) string {
	t.Helper()
	prov := []runtime.ProvenanceEntry{{
		SourceClass: runtime.ProvenanceSourceRuntime,
		Producer:    "spore-recomp",
		Artifact:    "work/reports/synthetic.json",
	}}
	mk := func(va uint32) *runtime.Entry {
		e := runtime.NewEntry(semantic.Addr(va).String())
		e.Provenance = prov
		return e
	}

	promoted := mk(rtPromotedVA)
	promoted.Canonicalization = runtime.CanonicalEntry
	promoted.CanonicalVA = sPtr("0x00401000")
	promoted.SetReached(true, 9)
	promoted.RuntimeCallers = []runtime.RuntimeCaller{{
		CallerFunctionVA: sPtr("0x00925000"), CallsiteVA: "0x00925010", Count: runtime.Ptr(3),
	}}
	promoted.RuntimeTargets = []runtime.RuntimeTarget{{
		TargetVA: "0x00401000", Indirect: runtime.TriFalse, Unresolved: runtime.TriFalse, Classification: "direct_call",
	}}
	promoted.Observations = []runtime.Observation{
		{Kind: runtime.ObsCall, CallsiteVA: sPtr("0x00925010"), TargetVA: sPtr("0x00401000"), CallDepth: runtime.Ptr(2), Count: runtime.Ptr(3)},
		{Kind: runtime.ObsStack, EntryESP: sPtr("0x0012fffc"), ReturnESP: sPtr("0x0012ffe8"), StackDeltaBytes: runtime.Ptr(-20),
			Detail: "callee cleaned its own frame"},
	}

	interior := mk(rtInteriorVA)
	interior.Canonicalization = runtime.CanonicalInterior
	interior.CanonicalVA = sPtr("0x00401000")
	interior.CanonicalOffset = runtime.Ptr(0x10)
	interior.SetReached(true, 9)
	interior.Observations = []runtime.Observation{{
		Kind: runtime.ObsRegister, Register: sPtr("EAX"), RegisterValue: sPtr("0x00000004"),
	}}

	padding := mk(rtPaddingVA)
	padding.Canonicalization = runtime.CanonicalNonEntity
	padding.SetReached(true, 1)
	padding.RuntimeCallers = []runtime.RuntimeCaller{{
		CallerFunctionVA: sPtr("0x00925b00"), CallsiteVA: "0x00925b33", Count: runtime.Ptr(1),
		MinDepth: runtime.Ptr(13), MaxDepth: runtime.Ptr(13),
	}}
	padding.Observations = []runtime.Observation{{
		Kind: runtime.ObsEntry, EIP: sPtr("0x00925050"), CallDepth: runtime.Ptr(13),
		Detail: "arrival recorded by producer event UNRESOLVED_TARGET",
	}}

	only := mk(rtRuntimeOnlyVA)
	only.SetReached(true, 1)
	only.Observations = []runtime.Observation{{
		Kind: runtime.ObsEntry, EIP: sPtr("0x00697c40"),
		Detail: "arrival recorded by producer event UNRESOLVED_TARGET",
	}}

	abstain := mk(rtUnknownABIVA)
	abstain.Canonicalization = runtime.CanonicalEntry
	abstain.CanonicalVA = sPtr("0x00401020")
	abstain.SetReached(true, 412)
	abstain.RuntimeTargets = []runtime.RuntimeTarget{{
		TargetVA: "0x00697c40", Indirect: runtime.TriTrue, Unresolved: runtime.TriTrue, Classification: "UNRESOLVED_TARGET",
	}}
	abstain.Observations = []runtime.Observation{{
		Kind: runtime.ObsIndirectCall, CallsiteVA: sPtr("0x00401028"), TargetVA: sPtr("0x00697c40"),
		Indirect: runtime.TriTrue, CallDepth: runtime.Ptr(7),
		Detail: "call to 0x00697c40, nothing registered there",
	}}

	iat := mk(rtIATSlotVA)
	iat.Canonicalization = runtime.CanonicalNonEntity
	iat.RuntimeImports = []runtime.RuntimeImportRef{{
		Module: "KERNEL32.dll", Symbol: "InitializeCriticalSectionAndSpinCount",
		SlotVA: sPtr("0x013cc1cc"), LoadedValue: sPtr("0x700001b8"), Bound: runtime.TriTrue,
	}}
	iat.Observations = []runtime.Observation{
		{Kind: runtime.ObsImport, Address: sPtr("0x013cc1cc"), SlotVA: sPtr("0x013cc1cc"),
			Module: sPtr("KERNEL32.dll"), Symbol: sPtr("InitializeCriticalSectionAndSpinCount"),
			Detail: "IAT cell contents as written by the producer's loader emulation"},
		{Kind: runtime.ObsException, EIP: sPtr("0x013cc1cc"), Class: sPtr("ACCESS_VIOLATION"),
			CallDepth: runtime.Ptr(0), Detail: "modelled stub raised"},
	}

	path := filepath.Join(t.TempDir(), "overlay.jsonl")
	if _, err := runtime.Write(path, []*runtime.Entry{promoted, interior, padding, only, abstain, iat},
		runtime.Metadata{
			Binary: semantic.BinaryIdentity{
				SHA256: sporeBinarySHA, ImageBase: sporeImageBase,
				Architecture: "x86:LE:32", Program: "SporeApp.exe", Version: "3.1.0.22",
			},
			Producer: runtime.Producer{
				Project: "spore-recomp", Name: "synthetic fixture", Version: "test",
				Artifact: "work/reports/synthetic.json", SourceSchema: "spore-recomp-runtime-report-1.1.0",
			},
		}); err != nil {
		t.Fatalf("runtime.Write: %v", err)
	}
	return path
}

func sPtr(s string) *string { return &s }

// ---- runtime validate -----------------------------------------------------

func TestRuntimeValidateAcceptsAGoodOverlay(t *testing.T) {
	_, overlay := runtimeFixture(t)
	r := run(t, "runtime", "validate", "--overlay", overlay, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	if p["ok"] != true {
		t.Fatalf("ok = %v, problems = %v", p["ok"], p["problems"])
	}
	if p["schema"] != runtime.OverlaySchema {
		t.Fatalf("schema = %v", p["schema"])
	}
	if p["binary_sha256"] != sporeBinarySHA {
		t.Fatalf("binary_sha256 = %v", p["binary_sha256"])
	}
	if p["content_sha256"] == "" {
		t.Fatal("validate did not report the content digest it verified")
	}
	h := run(t, "runtime", "validate", "--overlay", overlay)
	if !strings.Contains(h.stdout, "observation vocabulary") {
		t.Fatalf("the human form does not name the vocabulary it checked:\n%s", h.stdout)
	}
}

func TestRuntimeValidateRefusals(t *testing.T) {
	snap, overlay := runtimeFixture(t)

	t.Run("missing overlay", func(t *testing.T) {
		r := run(t, "runtime", "validate", "--overlay", filepath.Join(t.TempDir(), "nope.jsonl"))
		if r.code != ExitUnavailable {
			t.Fatalf("exit %d, want %d", r.code, ExitUnavailable)
		}
	})

	t.Run("required binary mismatch", func(t *testing.T) {
		r := run(t, "runtime", "validate", "--overlay", overlay, "--require-image-base", sporeImageBase)
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		// OPENSPORE_REQUIRE_SHA is the documented way to refuse another binary.
		var so, se bytes.Buffer
		code := Run([]string{"runtime", "validate", "--overlay", overlay},
			Env{Stdout: &so, Stderr: &se, RequireSHA: "00" + sporeBinarySHA[2:]})
		if code != ExitBinaryMismatch {
			t.Fatalf("exit %d, want %d: %s", code, ExitBinaryMismatch, se.String())
		}
	})

	t.Run("required image base mismatch", func(t *testing.T) {
		r := run(t, "runtime", "validate", "--overlay", overlay, "--require-image-base", "0x50000000")
		if r.code != ExitRuntimeImageBase {
			t.Fatalf("exit %d, want %d: %s", r.code, ExitRuntimeImageBase, r.stderr)
		}
	})

	t.Run("corrupt overlay", func(t *testing.T) {
		raw, err := os.ReadFile(overlay)
		if err != nil {
			t.Fatal(err)
		}
		bad := strings.Replace(string(raw), `"requested_va":"0x00401000"`, `"requested_va":"402000"`, 1)
		path := filepath.Join(t.TempDir(), "bad.jsonl")
		if err := os.WriteFile(path, []byte(bad), 0o644); err != nil {
			t.Fatal(err)
		}
		r := run(t, "runtime", "validate", "--overlay", path)
		if r.code != ExitCorruptSnapshot {
			t.Fatalf("exit %d, want %d: %s", r.code, ExitCorruptSnapshot, r.stderr)
		}
	})

	t.Run("unknown schema", func(t *testing.T) {
		raw, _ := os.ReadFile(overlay)
		bad := strings.Replace(string(raw), runtime.OverlaySchema, runtime.OverlaySchema+"-v2", 1)
		path := filepath.Join(t.TempDir(), "bad.jsonl")
		if err := os.WriteFile(path, []byte(bad), 0o644); err != nil {
			t.Fatal(err)
		}
		if r := run(t, "runtime", "validate", "--overlay", path); r.code != ExitUnsupportedSchema {
			t.Fatalf("exit %d, want %d", r.code, ExitUnsupportedSchema)
		}
	})

	t.Run("no overlay flag", func(t *testing.T) {
		if r := run(t, "runtime", "validate"); r.code != ExitUsage {
			t.Fatalf("exit %d", r.code)
		}
	})
	_ = snap
}

// ---- runtime lookup -------------------------------------------------------

func TestRuntimeLookupJoinedView(t *testing.T) {
	snap, overlay := runtimeFixture(t)

	t.Run("static function plus runtime observations", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x00401000", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		if p["requested_va"] != "0x00401000" {
			t.Fatalf("requested_va = %v", p["requested_va"])
		}
		ident := p["identity"].(map[string]any)
		if ident["canonical_va"] != "0x00401000" || ident["canonicalization"] != "function_entry" {
			t.Fatalf("identity = %v", ident)
		}
		static, ok := p["static"].(map[string]any)
		if !ok || static == nil {
			t.Fatalf("static half missing: %v", p["static"])
		}
		names := static["names"].(map[string]any)
		if names["ghidra_name"] != "FUN_00401000" {
			t.Fatalf("static ghidra_name = %v", names["ghidra_name"])
		}
		// And the SDK-named neighbour proves the static projection is the existing
		// one, not a second reduced copy.
		sdk := run(t, "runtime", "lookup", "0x00402000", "--overlay", overlay, "--snapshot", snap, "--json")
		if sdk.code != ExitOK {
			t.Fatalf("exit %d: %s", sdk.code, sdk.stderr)
		}
		if sdk.json(t)["static"].(map[string]any)["names"].(map[string]any)["sdk_name"] != "Editors::IBakeManager::Get" {
			t.Fatalf("sdk_name = %v", sdk.json(t)["static"])
		}
		rt := p["runtime"].(map[string]any)
		if rt["reached"] != "true" {
			t.Fatalf("reached = %v", rt["reached"])
		}
		if rt["entry_count"].(float64) != 18 {
			// The exact entry (9) plus the interior entry that claims it (9).
			t.Fatalf("entry_count = %v, want the merged 18", rt["entry_count"])
		}
		prov := rt["provenance"].([]any)[0].(map[string]any)
		if prov["source_class"] != "runtime" || prov["producer"] != "spore-recomp" {
			t.Fatalf("runtime provenance = %v", prov)
		}
		// The two halves carry DIFFERENT provenance vocabularies and must not be
		// merged into one. 0x00401000 is the fixture function that HAS an evidence
		// pack, so it has a static provenance list to compare against.
		withPack := run(t, "runtime", "lookup", "0x00401000", "--overlay", overlay, "--snapshot", snap, "--json")
		if withPack.code != ExitOK {
			t.Fatalf("exit %d: %s", withPack.code, withPack.stderr)
		}
		staticProv := withPack.json(t)["static"].(map[string]any)["provenance"].([]any)[0].(map[string]any)
		if staticProv["source_class"] == "runtime" {
			t.Fatalf("a static provenance entry claims source_class=runtime: %v", staticProv)
		}
		if staticProv["source_class"] != "ghidra" && staticProv["source_class"] != "generated_index" && staticProv["source_class"] != "committed_artifact" && staticProv["source_class"] != "derived" {
			t.Fatalf("the static provenance vocabulary changed: %v", staticProv)
		}
		interp := p["interpretation"].(map[string]any)
		if len(interp["static_blockers"].([]any)) == 0 {
			t.Fatalf("no static blockers reported for a promoted target with a NOT_AVAILABLE dimension: %v", interp)
		}
		if interp["verdict_unchanged"] != "no static verdict was modified" {
			t.Fatalf("verdict_unchanged = %v", interp["verdict_unchanged"])
		}
		if !strings.Contains(r.stdout, "no static verdict was modified") {
			t.Fatalf("the JSON output lost the verdict_unchanged literal:\n%s", r.stdout)
		}
	})

	t.Run("interior address", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x00401010", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		ident := p["identity"].(map[string]any)
		if ident["canonical_va"] != "0x00401000" || ident["canonicalization"] != "containing_function_entry" {
			t.Fatalf("identity = %v", ident)
		}
		if ident["offset"].(float64) != 16 {
			t.Fatalf("offset = %v", ident["offset"])
		}
	})

	t.Run("padding address keeps the discrepancy", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		if p["static"] != nil {
			t.Fatalf("static = %v; padding must not acquire a passport", p["static"])
		}
		human := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap)
		ident := p["identity"].(map[string]any)
		if ident["canonical_va"] != nil || ident["static_status"] != "static_non_function_entity" {
			t.Fatalf("identity = %v", ident)
		}
		rt := p["runtime"].(map[string]any)
		if rt["reached"] != "true" || rt["entry_count"].(float64) != 1 {
			t.Fatalf("runtime = %v", rt)
		}
		callers := rt["runtime_callers"].([]any)
		if len(callers) != 1 || callers[0].(map[string]any)["caller_function_va"] != "0x00925b00" {
			t.Fatalf("runtime_callers = %v", callers)
		}
		if !strings.Contains(human.stdout, "does not map padding to a function") {
			t.Fatalf("the discrepancy is not stated in the human form:\n%s", human.stdout)
		}
	})

	t.Run("runtime-only address OpenSpore cannot place", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x00697c40", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d, want 0: the whole point is that this is representable", r.code)
		}
		p := r.json(t)
		if p["static"] != nil {
			t.Fatalf("static = %v", p["static"])
		}
		if p["runtime"] == nil {
			t.Fatal("runtime half missing")
		}
		human := run(t, "runtime", "lookup", "0x00697c40", "--overlay", overlay, "--snapshot", snap)
		if !strings.Contains(human.stdout, "manufacture a function record") {
			t.Fatalf("the human form does not say the record was not manufactured:\n%s", human.stdout)
		}
	})

	t.Run("UNKNOWN static ABI with a runtime observation", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x00401020", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		static := p["static"].(map[string]any)
		abi := static["abi"].(map[string]any)
		v := abi["value"].(map[string]any)
		if v["verdict"] != "ABI_UNKNOWN" || v["convention"] != nil {
			t.Fatalf("abi = %v", v)
		}
		blockers := p["interpretation"].(map[string]any)["static_blockers"].([]any)
		found := false
		for _, b := range blockers {
			if strings.Contains(b.(string), "ABI_RECORD") {
				found = true
			}
		}
		if !found {
			t.Fatalf("blockers = %v, want the ABI abstention", blockers)
		}
		// The runtime half is present and the static verdict is untouched.
		rt := p["runtime"].(map[string]any)
		if rt["reached"] != "true" {
			t.Fatalf("runtime = %v", rt)
		}
		if v["convention"] != nil {
			t.Fatal("a runtime observation changed the static convention")
		}
	})

	t.Run("import and exception observations", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x013cc1cc", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		rt := p["runtime"].(map[string]any)
		imports := rt["runtime_imports"].([]any)
		if len(imports) != 1 {
			t.Fatalf("runtime_imports = %v", imports)
		}
		if imports[0].(map[string]any)["symbol"] != "InitializeCriticalSectionAndSpinCount" {
			t.Fatalf("import = %v", imports[0])
		}
		if rt["exception_count"].(float64) != 1 {
			t.Fatalf("exception_count = %v", rt["exception_count"])
		}
		if imports[0].(map[string]any)["reached_count"] != nil {
			t.Fatal("an IAT cell check was reported as a reached import")
		}
	})

	t.Run("address neither side knows", func(t *testing.T) {
		r := run(t, "runtime", "lookup", "0x7fff0000", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitUnknownFunction {
			t.Fatalf("exit %d, want %d", r.code, ExitUnknownFunction)
		}
		if r.json(t)["error"] != "unknown_address" {
			t.Fatalf("error = %v", r.json(t)["error"])
		}
	})

	t.Run("overlay without a snapshot still joins by requested VA", func(t *testing.T) {
		// A consumer with an overlay and no checkout must still get an answer.
		// --root points at an empty directory so the local checkout is not used.
		r := run(t, "runtime", "lookup", "0x00697c40", "--overlay", overlay, "--root", t.TempDir(), "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		p := r.json(t)
		if p["snapshot"].(map[string]any)["available"] != false {
			t.Fatalf("snapshot = %v", p["snapshot"])
		}
		if p["identity"].(map[string]any)["static_status"] != "no_static_identity" {
			t.Fatalf("static_status = %v", p["identity"])
		}
	})

	t.Run("a producer's wrong canonical claim is reported, not adopted", func(t *testing.T) {
		// The producer claims 0x00925050 canonicalises to 0x00925000. OpenSpore's
		// own rule says 0x00925050 is in no body at all. The claim must be shown
		// AND OpenSpore's answer must stand: the static identity is authoritative
		// and is never edited to match a producer.
		liar := filepath.Join(t.TempDir(), "liar.jsonl")
		e := runtime.NewEntry("0x00925050")
		e.Canonicalization = runtime.CanonicalInterior
		e.CanonicalVA = sPtr("0x00925000")
		e.CanonicalOffset = runtime.Ptr(0x50)
		e.SetReached(true, 1)
		e.Provenance = []runtime.ProvenanceEntry{{
			SourceClass: runtime.ProvenanceSourceRuntime, Producer: "spore-recomp", Artifact: "work/reports/synthetic.json",
		}}
		if _, err := runtime.Write(liar, []*runtime.Entry{e}, runtime.Metadata{
			Binary:   semantic.BinaryIdentity{SHA256: sporeBinarySHA, ImageBase: sporeImageBase},
			Producer: runtime.Producer{Project: "spore-recomp", Name: "n", Version: "v", Artifact: "work/reports/synthetic.json"},
		}); err != nil {
			t.Fatal(err)
		}
		r := run(t, "runtime", "lookup", "0x00925050", "--overlay", liar, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		ident := r.json(t)["identity"].(map[string]any)
		if ident["canonical_va"] != nil {
			t.Fatalf("canonical_va = %v; OpenSpore adopted the producer's claim", ident["canonical_va"])
		}
		claim := ident["producer_claim"].(map[string]any)
		if claim["canonical_va"] != "0x00925000" {
			t.Fatalf("the producer's claim was hidden rather than reported: %v", claim)
		}
		dis := ident["disagreement"].(string)
		if !strings.Contains(dis, "not adopted") {
			t.Fatalf("disagreement = %q, want it to say the claim is not adopted", dis)
		}
		h := run(t, "runtime", "lookup", "0x00925050", "--overlay", liar, "--snapshot", snap)
		if !strings.Contains(h.stdout, "disagreement") || !strings.Contains(h.stdout, "0x00925000") {
			t.Fatalf("the human form does not show the disagreement:\n%s", h.stdout)
		}
	})

	t.Run("snapshot and overlay describing different binaries warn", func(t *testing.T) {
		other := filepath.Join(t.TempDir(), "other.jsonl")
		oe := runtime.NewEntry("0x00401000")
		oe.Provenance = []runtime.ProvenanceEntry{{
			SourceClass: runtime.ProvenanceSourceRuntime, Producer: "spore-recomp", Artifact: "work/reports/other.json",
		}}
		if _, err := runtime.Write(other, []*runtime.Entry{oe},
			runtime.Metadata{
				Binary:   semantic.BinaryIdentity{SHA256: strings.Repeat("b", 64), ImageBase: sporeImageBase},
				Producer: runtime.Producer{Project: "spore-recomp", Name: "n", Version: "v", Artifact: "work/reports/other.json"},
			}); err != nil {
			t.Fatal(err)
		}
		r := run(t, "runtime", "lookup", "0x00401000", "--overlay", other, "--snapshot", snap)
		if !strings.Contains(r.stderr, "two binaries") {
			t.Fatalf("no cross-binary warning:\n%s%s", r.stdout, r.stderr)
		}
	})
}

func TestRuntimeLookupJoinedOutputIsDeterministic(t *testing.T) {
	snap, overlay := runtimeFixture(t)
	var prev string
	for i := 0; i < 3; i++ {
		r := run(t, "runtime", "lookup", "0x00401000", "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("exit %d: %s", r.code, r.stderr)
		}
		if i > 0 && r.stdout != prev {
			t.Fatalf("repeated joined lookups differ:\n%s\n---\n%s", prev, r.stdout)
		}
		prev = r.stdout
	}
	// And the human form is stable too.
	var prevText string
	for i := 0; i < 2; i++ {
		r := run(t, "runtime", "lookup", "0x00925050", "--overlay", overlay, "--snapshot", snap)
		if i > 0 && r.stdout != prevText {
			t.Fatalf("human output differs between runs:\n%s\n---\n%s", prevText, r.stdout)
		}
		prevText = r.stdout
	}
}

func TestRuntimeLookupAcceptsEveryAddressSpelling(t *testing.T) {
	snap, overlay := runtimeFixture(t)
	for _, spelling := range []string{"0x00401000", "00401000", "401000", "dec:4198400", "rva:00001000"} {
		r := run(t, "runtime", "lookup", spelling, "--overlay", overlay, "--snapshot", snap, "--json")
		if r.code != ExitOK {
			t.Fatalf("%q: exit %d: %s", spelling, r.code, r.stderr)
		}
		if r.json(t)["requested_va"] != "0x00401000" {
			t.Fatalf("%q resolved to %v", spelling, r.json(t)["requested_va"])
		}
	}
	if r := run(t, "runtime", "lookup", "not-an-address", "--overlay", overlay, "--snapshot", snap); r.code != ExitUsage {
		t.Fatalf("a malformed address exited %d, want %d", r.code, ExitUsage)
	}
}

// ---- runtime stats --------------------------------------------------------

func TestRuntimeStatsJoinsProducerAndStaticViews(t *testing.T) {
	snap, overlay := runtimeFixture(t)
	r := run(t, "runtime", "stats", "--overlay", overlay, "--snapshot", snap, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	p := r.json(t)
	ov := p["analysis"].(map[string]any)["overlay"].(map[string]any)
	if ov["entries"].(float64) != 6 {
		t.Fatalf("entries = %v", ov["entries"])
	}
	if ov["imports"].(float64) != 1 || ov["exceptions"].(float64) != 1 {
		t.Fatalf("overlay views = %v", ov)
	}
	j := p["analysis"].(map[string]any)["joined"].(map[string]any)
	if j == nil {
		t.Fatal("joined stats are null with a snapshot present")
	}
	if j["runtime_observed_absent_from_static_universe"].(float64) < 3 {
		t.Fatalf("runtime-only count = %v", j["runtime_observed_absent_from_static_universe"])
	}
	if j["runtime_observed_promoted"].(float64) != 1 {
		t.Fatalf("promoted = %v", j["runtime_observed_promoted"])
	}
	if j["runtime_observed_abi_unknown"].(float64) != 1 {
		t.Fatalf("abi_unknown = %v", j["runtime_observed_abi_unknown"])
	}
	h := run(t, "runtime", "stats", "--overlay", overlay, "--snapshot", snap)
	if !strings.Contains(h.stdout, "0x00925050") {
		t.Fatalf("the runtime-only address list does not name the discrepancy:\n%s", h.stdout)
	}
}

func TestRuntimeStatsWithoutASnapshot(t *testing.T) {
	_, overlay := runtimeFixture(t)
	r := run(t, "runtime", "stats", "--overlay", overlay, "--root", t.TempDir(), "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s", r.code, r.stderr)
	}
	analysis := r.json(t)["analysis"].(map[string]any)
	if analysis["joined"] != nil {
		t.Fatalf("joined = %v, want null when no snapshot was reachable", analysis["joined"])
	}
	if analysis["overlay"].(map[string]any)["entries"].(float64) != 6 {
		t.Fatal("the producer-side views must still be reported without a snapshot")
	}
}

// ---- runtime frontier -----------------------------------------------------

func TestRuntimeFrontierIntersectsBlockersWithRuntime(t *testing.T) {
	snap, overlay := runtimeFixture(t)
	census := fixtureCensus(t, snap)

	r := run(t, "runtime", "frontier", "--overlay", overlay, "--census", census,
		"--snapshot", snap, "--va", "0x00401000", "--va", "0x00925050",
		"--va", "0x00401020", "--va", "0x7fff0000", "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	rows := p["targets"].([]any)
	if len(rows) != 4 {
		t.Fatalf("rows = %d, want the four named addresses", len(rows))
	}
	byVA := map[string]map[string]any{}
	var order []string
	for _, row := range rows {
		m := row.(map[string]any)
		byVA[m["va"].(string)] = m
		order = append(order, m["va"].(string))
	}
	// Rows come back sorted by VA regardless of the order they were named in.
	for i := 1; i < len(order); i++ {
		if order[i-1] >= order[i] {
			t.Fatalf("frontier rows are not sorted: %v", order)
		}
	}

	// The promoted target with a NOT_AVAILABLE RETURN SEMANTICS dimension and a
	// relevant stack observation: closed, with the evidence still reported.
	closed := byVA["0x00401000"]
	if closed["resolution_class"] != runtime.ResolutionAlreadyClosed {
		t.Fatalf("0x00401000 class = %v (want %s): a promotion is not reopened by runtime evidence",
			closed["resolution_class"], runtime.ResolutionAlreadyClosed)
	}
	if closed["relevant_by_dimension"] == nil {
		t.Fatalf("the relevant observations were suppressed on a closed target: %v", closed)
	}

	// The padding address: runtime reached it, OpenSpore cannot place it.
	only := byVA["0x00925050"]
	if only["resolution_class"] != runtime.ResolutionRuntimeOnly {
		t.Fatalf("0x00925050 class = %v", only["resolution_class"])
	}
	if only["new_static_task_justified"] != true {
		t.Fatal("a runtime-only address should be flagged for a static IDENTITY task")
	}

	// The abstaining-ABI target. Its blocker is ABI_RECORD, a dimension name this
	// build's relevance table deliberately does NOT cover -- an unrecognised
	// dimension must yield no relevance rather than a default. So the target is
	// classified reached_without_relevant_observation, and the justification says
	// so. An indirect_call observation exists; it simply is not mapped to that
	// dimension.
	abstain := byVA["0x00401020"]
	if abstain["resolution_class"] != runtime.ResolutionReachedOnly {
		t.Fatalf("0x00401020 class = %v, want %s: an unmapped dimension must not borrow relevance",
			abstain["resolution_class"], runtime.ResolutionReachedOnly)
	}
	if abstain["new_static_task_justified"] != false {
		t.Fatal("an unmapped blocker dimension was flagged as justifying a task")
	}
	if !strings.Contains(abstain["justification"].(string), "no observation category") {
		t.Fatalf("justification = %v", abstain["justification"])
	}

	// The address neither side knows.
	if byVA["0x7fff0000"]["resolution_class"] != runtime.ResolutionNotReached {
		t.Fatalf("0x7fff0000 class = %v", byVA["0x7fff0000"]["resolution_class"])
	}

	if p["verdict_unchanged"] == "" {
		t.Fatal("the frontier does not state that no verdict changed")
	}
}

func TestRuntimeFrontierWithoutAnOverlaySaysNotReached(t *testing.T) {
	snap, _ := runtimeFixture(t)
	census := fixtureCensus(t, snap)
	r := run(t, "runtime", "frontier", "--census", census, "--snapshot", snap, "--va", "0x00401000")
	if !strings.Contains(r.stderr, "no --overlay supplied") {
		t.Fatalf("the command did not disclose that no runtime source was given:\n%s", r.stderr)
	}
	if !strings.Contains(r.stdout, "not_reached") {
		t.Fatalf("stdout:\n%s", r.stdout)
	}
}

func TestRuntimeFrontierNeedsATargetSource(t *testing.T) {
	if r := run(t, "runtime", "frontier", "--overlay", "x"); r.code != ExitUnavailable {
		// A missing overlay is reported by the overlay loader, not by usage.
		t.Fatalf("exit %d, want %d", r.code, ExitUnavailable)
	}
	if r := run(t, "runtime", "frontier"); r.code != ExitUsage {
		t.Fatalf("exit %d, want %d", r.code, ExitUsage)
	}
}

func TestRuntimeFrontierIsDeterministic(t *testing.T) {
	snap, overlay := runtimeFixture(t)
	census := fixtureCensus(t, snap)
	args := []string{"runtime", "frontier", "--overlay", overlay, "--census", census, "--snapshot", snap,
		"--va", "0x00925050", "--va", "0x00401000", "--json"}
	first := run(t, args...)
	shuffled := []string{"runtime", "frontier", "--overlay", overlay, "--census", census, "--snapshot", snap,
		"--va", "0x00401000", "--va", "0x00925050", "--json"}
	second := run(t, shuffled...)
	if first.code != ExitOK || second.code != ExitOK {
		t.Fatalf("exits %d/%d", first.code, second.code)
	}
	// The only permitted difference is the requested_va echo, which records the
	// caller's input verbatim.
	strip := func(s string) string {
		var m map[string]any
		if err := json.Unmarshal([]byte(s), &m); err != nil {
			t.Fatalf("not JSON: %v\n%s", err, s)
		}
		delete(m, "requested_va")
		out, _ := json.Marshal(m)
		return string(out)
	}
	if strip(first.stdout) != strip(second.stdout) {
		t.Fatalf("frontier output depends on the order the targets were named in")
	}
}

// ---- runtime import-recomp ------------------------------------------------

func TestRuntimeImportRecompConvertsASyntheticReport(t *testing.T) {
	dir := t.TempDir()
	report := filepath.Join(dir, "work", "reports", "synthetic.json")
	if err := os.MkdirAll(filepath.Dir(report), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(report, []byte(syntheticRecompReportJSON()), 0o644); err != nil {
		t.Fatal(err)
	}
	out := filepath.Join(dir, "overlay.jsonl")
	r := run(t, "runtime", "import-recomp", "--report", report, "--out", out)
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s%s", r.code, r.stdout, r.stderr)
	}
	if !strings.Contains(r.stdout, "work/reports/synthetic.json") {
		t.Fatalf("the portable artifact identifier was not derived:\n%s", r.stdout)
	}
	if !strings.Contains(r.stdout, "no canonical_va") {
		t.Fatalf("the command did not state that canonical_va is left null:\n%s", r.stdout)
	}
	v := run(t, "runtime", "validate", "--overlay", out)
	if v.code != ExitOK {
		t.Fatalf("the converted overlay does not validate:\n%s%s", v.stdout, v.stderr)
	}

	// Determinism: the same report converts to the same bytes.
	out2 := filepath.Join(dir, "overlay2.jsonl")
	if r := run(t, "runtime", "import-recomp", "--report", report, "--out", out2); r.code != ExitOK {
		t.Fatal(r.stderr)
	}
	a, _ := os.ReadFile(out)
	b, _ := os.ReadFile(out2)
	if !bytes.Equal(a, b) {
		t.Fatal("two conversions of one report are not byte-identical")
	}
}

func TestRuntimeImportRecompRefusesABinaryMismatch(t *testing.T) {
	dir := t.TempDir()
	report := filepath.Join(dir, "work", "reports", "synthetic.json")
	if err := os.MkdirAll(filepath.Dir(report), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(report, []byte(syntheticRecompReportJSON()), 0o644); err != nil {
		t.Fatal(err)
	}
	r := run(t, "runtime", "import-recomp", "--report", report,
		"--out", filepath.Join(dir, "o.jsonl"), "--require-sha", strings.Repeat("c", 64))
	if r.code != ExitBinaryMismatch {
		t.Fatalf("exit %d, want %d: %s", r.code, ExitBinaryMismatch, r.stderr)
	}
}

func TestRuntimeImportRecompRequiresAReport(t *testing.T) {
	if r := run(t, "runtime", "import-recomp"); r.code != ExitUsage {
		t.Fatalf("exit %d", r.code)
	}
}

// ---- runtime census -------------------------------------------------------

func TestRuntimeCensusProjectsTheFixtureTree(t *testing.T) {
	tr := baseFixture(t)
	// A promotion marker, so the census has an authoritative promoted source.
	pkgDir := filepath.Join(tr.Root, "src/reconstruction/pkg_fixture")
	if err := os.MkdirAll(pkgDir, 0o755); err != nil {
		t.Fatal(err)
	}
	marker := `{"namespace":"openspore::reconstruction::pkg_fixture","package":"pkg-fixture","schema":"openspore-promotion-1","src_package":"pkg_fixture","targets":[{"bare_va":"00401000","va":"0x00401000","static_status":"PASS","runtime_status":"GATED"}]}`
	if err := os.WriteFile(filepath.Join(pkgDir, "promotion.json"), []byte(marker), 0o644); err != nil {
		t.Fatal(err)
	}
	// A blocker statement and a runtime gate, so the census has something to carry.
	tr.RecordOverrides["0x00401020"] = map[string]any{
		"runtime_gated": true,
		"runtime":       map[string]any{"gated": true, "validated": 0, "gates": []string{"no original-process trace exists"}, "blocking_reason": "runtime never attempted"},
		"blockers":      []string{"the derived ABI record abstained"},
		"unresolved_questions": []string{
			"whether the register argument is a this",
		},
	}
	if err := tr.Write(); err != nil {
		t.Fatal(err)
	}
	out := filepath.Join(t.TempDir(), "census.json")
	r := run(t, "runtime", "census", "--root", tr.Root, "--out", out, "--json")
	if r.code != ExitOK {
		t.Fatalf("exit %d: %s%s", r.code, r.stdout, r.stderr)
	}
	p := r.json(t)
	if p["schema"] != runtime.CensusSchema {
		t.Fatalf("schema = %v", p["schema"])
	}
	counts := p["counts"].(map[string]any)
	if counts["promoted"].(float64) != 1 {
		t.Fatalf("promoted = %v, want 1 from the marker", counts["promoted"])
	}
	if counts["targets_projected"].(float64) != float64(len(tr.Functions)) {
		t.Fatalf("targets_projected = %v, want %d", counts["targets_projected"], len(tr.Functions))
	}

	census, err := runtime.LoadCensus(out, sporeBinarySHA)
	if err != nil {
		t.Fatalf("the written census does not load: %v", err)
	}
	if problems := runtime.VerifyCensus(census); len(problems) != 0 {
		t.Fatalf("VerifyCensus: %v", problems)
	}
	var gated *runtime.CensusTarget
	for i := range census.Targets {
		if census.Targets[i].VA == "0x00401020" {
			gated = &census.Targets[i]
		}
	}
	if gated == nil {
		t.Fatal("0x00401020 is missing from the census")
	}
	if !gated.RuntimeGated || len(gated.RuntimeGates) != 1 {
		t.Fatalf("runtime gate projection = %+v", gated)
	}
	if len(gated.Blockers) != 1 || !strings.Contains(gated.Blockers[0], "abstained") {
		t.Fatalf("blocker prose was not carried verbatim: %+v", gated.Blockers)
	}
	if !gated.HasBlocker() {
		t.Fatal("HasBlocker() = false for a gated target")
	}

	// The census is a projection, so two runs from one state are byte-identical.
	out2 := filepath.Join(t.TempDir(), "census2.json")
	if r := run(t, "runtime", "census", "--root", tr.Root, "--out", out2); r.code != ExitOK {
		t.Fatal(r.stderr)
	}
	a, _ := os.ReadFile(out)
	b, _ := os.ReadFile(out2)
	if !bytes.Equal(a, b) {
		t.Fatal("two census projections of one state differ")
	}
}

// ---- namespace plumbing ---------------------------------------------------

func TestRuntimeNamespacePlumbing(t *testing.T) {
	if r := run(t, "runtime"); r.code != ExitUsage {
		t.Fatalf("bare `runtime` exited %d, want %d", r.code, ExitUsage)
	}
	if r := run(t, "runtime", "nope"); r.code != ExitUsage {
		t.Fatalf("unknown subcommand exited %d", r.code)
	}
	r := run(t, "runtime", "help")
	if r.code != ExitOK || !strings.Contains(r.stdout, "runtime validate") {
		t.Fatalf("runtime help = %d\n%s", r.code, r.stdout)
	}
	if r := run(t, "help"); !strings.Contains(r.stdout, "runtime <subcommand>") {
		t.Fatalf("the top-level usage does not advertise the runtime namespace:\n%s", r.stdout)
	}
	// The static commands must be untouched by the new namespace.
	if r := run(t, "nope"); r.code != ExitUsage {
		t.Fatalf("exit %d", r.code)
	}
}

// ---- the fixture census ---------------------------------------------------

func fixtureCensus(t *testing.T, snap string) string {
	t.Helper()
	path := filepath.Join(t.TempDir(), "census.json")
	doc := runtime.Census{
		Schema: runtime.CensusSchema,
		Binary: semantic.BinaryIdentity{SHA256: sporeBinarySHA, ImageBase: sporeImageBase},
		Source: runtime.CensusSource{
			Index:            "reconstruction/knowledge/index.json",
			IndexSHA256:      strings.Repeat("d", 64),
			PromotionMarkers: "src/reconstruction/*/promotion.json",
			MarkerGlob:       "src/reconstruction/*/promotion.json",
			PromotedCount:    1,
		},
		Targets: []runtime.CensusTarget{
			{VA: "0x00401000", Name: "FUN_00401000", Status: "reconstructed", Reconstructed: true, Promoted: true,
				RuntimeGated: true, RuntimeGates: []string{"no original-process trace exists"},
				Blockers: []string{"runtime validation not attempted"}},
			{VA: "0x00401020", Name: "FUN_00401020", Status: "candidate", RuntimeGated: true,
				RuntimeGates: []string{"gate-unknown-abi"}, UnresolvedQuestions: []string{"which convention"}},
			{VA: "0x00402000", Name: "Editors::IBakeManager::Get", Status: "reconstructed", Reconstructed: true, Promoted: true},
			{VA: "0x00925000", Name: "FUN_00925000", Status: "candidate"},
		},
	}
	if _, err := runtime.WriteCensus(path, doc); err != nil {
		t.Fatalf("WriteCensus: %v", err)
	}
	_ = snap
	return path
}

// syntheticRecompReportJSON is a hand-written report with the shape spore-recomp
// emits. It is clearly synthetic: it observes only addresses the fixture snapshot
// already knows plus one it does not, and it invents no production observation.
func syntheticRecompReportJSON() string {
	return `{
  "schema_version": "1.1.0",
  "entry_va": "0x011e11a0",
  "outcome": "STOPPED_UNRESOLVED_TARGET",
  "outcome_detail": "the guest called a guest address with no recovered function",
  "final_eip": "0x00925b2b",
  "final_kind": "unresolved_target",
  "steps": 1836,
  "peak_call_depth": 13,
  "call_edge_count": 2,
  "image": {"loaded": true, "binary_sha256": "` + sporeBinarySHA + `", "image_base": "` + sporeImageBase + `", "entry_rva": "0x00de11a0"},
  "registers": {"eax": "0x00000004", "esp": "0x0012fecc", "eip": "0x00925b2b"},
  "imports": {
    "bindings": 495, "modelled": 495, "unresolved": 389,
    "iat_cell_checks": [
      {"slot_va": "0x013cc1cc", "loaded_value": "0x700001b8", "module": "KERNEL32.dll", "symbol": "GetSystemTimeAsFileTime", "bound": true}
    ]
  },
  "call_edges": [
    {"callsite_va": "0x011e11a5", "target_va": "0x011e1548", "count": 1, "first_sequence": 1, "min_depth": 1, "max_depth": 1},
    {"callsite_va": "0x00925b33", "target_va": "0x00925050", "count": 1, "first_sequence": 2, "min_depth": 13, "max_depth": 13}
  ],
  "events": [
    {"sequence": 1, "class": "UNRESOLVED_TARGET", "caller_function_va": "0x00925b00", "callsite_va": "0x00925b33", "target_va": "0x00925050", "return_address": "0x00925b2b", "call_depth": 13, "detail": "call to 0x00925050, nothing registered there"}
  ]
}
`
}

var _ = testfixture.BinarySHA
