package runtime_test

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"testing"

	"github.com/openspore/spore-semantic/internal/index"
	"github.com/openspore/spore-semantic/internal/openspore"
	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/snapshot"
	"github.com/openspore/spore-semantic/internal/testfixture"
)

// The representative addresses the task names. Each one has a DIFFERENT identity
// answer, which is the point of testing them together: a canonicalisation rule
// that gets three of four right is not a rule, it is a coincidence.
const (
	vaCanonicalEntry  = 0x00402000 // a function entry, SDK-named
	vaInteriorAddress = 0x00402010 // inside the body above
	vaPaddingAddress  = 0x00925050 // between FUN_00925000 (0x4a) and FUN_009250c0
	vaRuntimeOnly     = 0x00697c40 // in no body at all; what spore-recomp reached
	vaUnknownABI      = 0x00401020 // an evidence pack whose ABI record abstains
	vaUnpackaged      = 0x00925000 // has no pack, so no ABI record at all
)

func fixtureIndex(t *testing.T) *index.Index {
	t.Helper()
	tr := canonicalizationFixture(t)
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	srcs, err := openspore.LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	bin, err := srcs.BinaryIdentity()
	if err != nil {
		t.Fatalf("BinaryIdentity: %v", err)
	}
	passports, counts, notes, err := openspore.BuildPassports(srcs)
	if err != nil {
		t.Fatalf("BuildPassports: %v", err)
	}
	path := filepath.Join(tr.Root, "passport.jsonl")
	if _, err := snapshot.Write(path, passports, counts, snapshot.Options{
		Binary: bin, Export: notes,
	}); err != nil {
		t.Fatalf("snapshot.Write: %v", err)
	}
	data, err := snapshot.Load(path, bin.SHA256)
	if err != nil {
		t.Fatalf("snapshot.Load: %v", err)
	}
	return index.New(data)
}

func canonicalizationFixture(t *testing.T) *testfixture.Tree {
	t.Helper()
	tr := testfixture.New(t)
	t.Cleanup(func() { os.RemoveAll(tr.Root) })
	tr.BinarySHA = sporeSHA
	tr.ImageBase = sporeImg
	tr.Functions = []testfixture.Function{
		{VA: 0x00401000, Name: "FUN_00401000", Size: 0x20},
		{VA: 0x00401020, Name: "FUN_00401020", Size: 0x10},
		{VA: 0x00402000, Name: "FUN_00402000", Size: 0x40},
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
	tr.Packs[0x00401020] = true
	tr.Packs[0x00402000] = true
	// The ABI record that abstains: convention null, receiver present null.
	tr.ABIRecords[0x00401020] = testfixture.ABIRecordJSON(nil, "UNKNOWN", nil, nil)
	tr.ABIRecords[0x00402000] = testfixture.ABIRecordJSON(sPtr("__thiscall"), "INFERRED", bPtr(true), nil)
	tr.Validation[0x00402000] = testfixture.ValidationDoc{
		Schema: "openspore-structural-validation-1",
		Checks: map[string]testfixture.Check{
			"ABI":               {Status: "PASS", Coverage: "partial", Detail: "convention present"},
			"RETURN SEMANTICS":  {Status: "NOT_AVAILABLE", Coverage: "none", Detail: "the machine return state is UNCLASSIFIED"},
			"VIRTUAL DISPATCH":  {Status: "WARN", Coverage: "partial", Detail: "one membership, no attributed slot"},
			"EVIDENCE COVERAGE": {Status: "PASS", Coverage: "complete", Detail: "all categories available"},
		},
	}
	tr.Promoted[0x00402000] = true
	return tr
}

func sPtr(s string) *string { return &s }
func bPtr(b bool) *bool     { return &b }

// ---- identity --------------------------------------------------------------

func TestResolveIdentityCoversAllFourCases(t *testing.T) {
	ix := fixtureIndex(t)
	cases := []struct {
		name       string
		va         semantic.Addr
		wantCanon  *string
		wantRule   string
		wantStatus string
		wantOffset int
	}{
		{"canonical entry", vaCanonicalEntry, sPtr("0x00402000"), runtime.CanonicalEntry, runtime.StaticStatusKnown, 0},
		{"interior address", vaInteriorAddress, sPtr("0x00402000"), runtime.CanonicalInterior, runtime.StaticStatusInterior, 0x10},
		{"padding address", vaPaddingAddress, nil, runtime.CanonicalNonEntity, runtime.StaticStatusUnknownEntity, 0},
		{"runtime-only unknown function", vaRuntimeOnly, nil, runtime.CanonicalNonEntity, runtime.StaticStatusUnknownEntity, 0},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			canon, rule, status, offset, _ := runtime.ResolveIdentity(ix, tc.va)
			if rule != tc.wantRule {
				t.Fatalf("rule = %q, want %q", rule, tc.wantRule)
			}
			if status != tc.wantStatus {
				t.Fatalf("static_status = %q, want %q", status, tc.wantStatus)
			}
			if offset != tc.wantOffset {
				t.Fatalf("offset = %d, want %d", offset, tc.wantOffset)
			}
			switch {
			case tc.wantCanon == nil && canon != nil:
				t.Fatalf("canonical_va = %q, want null", *canon)
			case tc.wantCanon != nil && canon == nil:
				t.Fatalf("canonical_va = null, want %q", *tc.wantCanon)
			case tc.wantCanon != nil && *canon != *tc.wantCanon:
				t.Fatalf("canonical_va = %q, want %q", *canon, *tc.wantCanon)
			}
		})
	}
}

func TestPaddingIsNeverMappedToAFunction(t *testing.T) {
	// The whole point of the conservative rule. 0x00925000 ends at 0x0092504a,
	// so 0x00925050 is neither in it nor in FUN_009250c0.
	ix := fixtureIndex(t)
	for _, va := range []semantic.Addr{0x0092504a, 0x00925050, 0x009250bf} {
		canon, _, _, _, _ := runtime.ResolveIdentity(ix, va)
		if canon != nil {
			t.Fatalf("%s was resolved to %s; padding must resolve to nothing", va, *canon)
		}
	}
	// And 0x00925049, one byte inside the first body, DOES resolve.
	canon, rule, _, _, _ := runtime.ResolveIdentity(ix, 0x00925049)
	if canon == nil || *canon != "0x00925000" || rule != runtime.CanonicalInterior {
		t.Fatalf("0x00925049 resolved to %v / %q", canon, rule)
	}
}

func TestResolveIdentityWithNoIndexReportsAbsence(t *testing.T) {
	// An overlay must be consumable with no snapshot at all, so this must be a
	// supported state rather than a panic or a fabricated answer.
	canon, rule, status, _, _ := runtime.ResolveIdentity(nil, vaCanonicalEntry)
	if canon != nil {
		t.Fatalf("canonical_va = %q with no snapshot", *canon)
	}
	if rule != runtime.CanonicalUnknown || status != runtime.StaticStatusAbsent {
		t.Fatalf("rule/status = %q/%q", rule, status)
	}
}

// ---- the join --------------------------------------------------------------

// joinFixture writes an overlay that carries observations at all four
// representative addresses plus the unknown-ABI one.
func joinFixture(t *testing.T) *runtime.Overlay {
	t.Helper()
	prov := prov()

	entryAddr := entry(0x00402000)
	entryAddr.Canonicalization = runtime.CanonicalEntry
	entryAddr.CanonicalVA = sPtr("0x00402000")
	entryAddr.SetReached(true, 9)
	entryAddr.RuntimeCallers = []runtime.RuntimeCaller{{
		CallerFunctionVA: sPtr("0x00925000"), CallsiteVA: "0x00925010", Count: runtime.Ptr(3),
	}}
	entryAddr.RuntimeTargets = []runtime.RuntimeTarget{{
		TargetVA: "0x00401000", Indirect: runtime.TriFalse, Unresolved: runtime.TriFalse, Classification: "direct_call",
	}}
	entryAddr.Observations = []runtime.Observation{
		{Kind: runtime.ObsCall, Sequence: i64(1), CallsiteVA: sPtr("0x00925010"), TargetVA: sPtr("0x00402000"), CallDepth: runtime.Ptr(2), Count: runtime.Ptr(3)},
		// A stack observation: relevant to RETURN SEMANTICS and to ABI.
		{Kind: runtime.ObsStack, EntryESP: sPtr("0x0012fffc"), ReturnESP: sPtr("0x0012ffe8"), StackDeltaBytes: runtime.Ptr(-20), Detail: "callee cleaned its own frame"},
	}
	entryAddr.Provenance = prov

	interior := entry(0x00402010)
	interior.Canonicalization = runtime.CanonicalInterior
	interior.CanonicalVA = sPtr("0x00402000")
	interior.CanonicalOffset = runtime.Ptr(0x10)
	interior.SetReached(true, 9)
	interior.Observations = []runtime.Observation{{Kind: runtime.ObsRegister, Register: sPtr("EAX"), RegisterValue: sPtr("0x00000004")}}
	interior.Provenance = prov

	padding := entry(vaPaddingAddress)
	padding.Canonicalization = runtime.CanonicalNonEntity
	padding.SetReached(true, 1)
	padding.RuntimeCallers = []runtime.RuntimeCaller{{
		CallerFunctionVA: sPtr("0x00925b00"), CallsiteVA: "0x00925b33", Count: runtime.Ptr(1),
		MinDepth: runtime.Ptr(13), MaxDepth: runtime.Ptr(13),
	}}
	padding.Observations = []runtime.Observation{{
		Kind: runtime.ObsEntry, Sequence: i64(1), EIP: sPtr("0x00925050"), CallDepth: runtime.Ptr(13),
		Detail: "arrival recorded by producer event UNRESOLVED_TARGET",
	}}
	padding.Provenance = prov

	only := entry(vaRuntimeOnly)
	only.SetReached(true, 1)
	only.Observations = []runtime.Observation{{
		Kind: runtime.ObsEntry, EIP: sPtr("0x00697c40"), Detail: "arrival recorded by producer event UNRESOLVED_TARGET",
	}}
	only.Provenance = prov

	abstain := entry(vaUnknownABI)
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
	abstain.Provenance = prov

	imported := entry(0x013cc1cc)
	imported.Canonicalization = runtime.CanonicalNonEntity
	imported.RuntimeImports = []runtime.RuntimeImportRef{{
		Module: "KERNEL32.dll", Symbol: "InitializeCriticalSectionAndSpinCount",
		SlotVA: sPtr("0x013cc1cc"), LoadedValue: sPtr("0x700001b8"), Bound: runtime.TriTrue,
	}}
	imported.Observations = []runtime.Observation{
		{Kind: runtime.ObsImport, Address: sPtr("0x013cc1cc"), SlotVA: sPtr("0x013cc1cc"), Module: sPtr("KERNEL32.dll"), Symbol: sPtr("InitializeCriticalSectionAndSpinCount"), Detail: "IAT cell contents"},
		{Kind: runtime.ObsException, EIP: sPtr("0x013cc1cc"), Class: sPtr("ACCESS_VIOLATION"), CallDepth: runtime.Ptr(0), Detail: "modelled stub raised"},
	}
	imported.Provenance = prov

	path := writeOverlay(t, baseMeta(), entryAddr, interior, padding, only, abstain, imported)
	return mustLoad(t, path)
}

func i64(v int64) *int64 { return &v }

func TestJoinedLookupCoversTheRepresentativeAddresses(t *testing.T) {
	ix := fixtureIndex(t)
	ov := joinFixture(t)

	t.Run("static function with runtime observations", func(t *testing.T) {
		s := ov.Summarize(vaCanonicalEntry)
		if s == nil {
			t.Fatal("no runtime summary")
		}
		if s.Reached != runtime.TriTrue {
			t.Fatalf("reached = %q", s.Reached)
		}
		// Summarize merges EVERY entry reachable from this VA: the exact one and
		// the interior entry whose producer-claimed canonical VA is this address.
		// Two entries at 9 each is 18.
		if s.EntryCount == nil || *s.EntryCount != 18 {
			t.Fatalf("entry_count = %v, want the merged sum 18", countText(s.EntryCount))
		}
		if len(s.RuntimeCallers) != 1 || s.RuntimeCallers[0].CallerFunctionVA == nil || *s.RuntimeCallers[0].CallerFunctionVA != "0x00925000" {
			t.Fatalf("runtime_callers = %+v", s.RuntimeCallers)
		}
		if len(s.RuntimeTargets) != 1 {
			t.Fatalf("runtime_targets = %+v", s.RuntimeTargets)
		}
		if len(s.Provenance) != 1 || s.Provenance[0].SourceClass != runtime.ProvenanceSourceRuntime {
			t.Fatalf("provenance = %+v", s.Provenance)
		}
	})

	t.Run("interior address joins onto its containing entry", func(t *testing.T) {
		// The overlay recorded the interior address; the join must keep the
		// requested VA and report the producer's own canonicalization, while
		// OpenSpore's rule independently agrees.
		canon, rule, status, offset, _ := runtime.ResolveIdentity(ix, vaInteriorAddress)
		if canon == nil || *canon != "0x00402000" || rule != runtime.CanonicalInterior || status != runtime.StaticStatusInterior {
			t.Fatalf("identity = %v/%q/%q", canon, rule, status)
		}
		if offset != 0x10 {
			t.Fatalf("offset = %d", offset)
		}
		s := ov.Summarize(vaInteriorAddress)
		if s == nil || s.RequestedVA != "0x00402010" {
			t.Fatalf("summary requested_va = %+v", s)
		}
		if len(s.Observations) != 1 || s.Observations[0].Kind != runtime.ObsRegister {
			t.Fatalf("the interior entry's own observations were lost: %+v", s.Observations)
		}
	})

	t.Run("padding address keeps its runtime facts and gains no identity", func(t *testing.T) {
		canon, rule, status, _, _ := runtime.ResolveIdentity(ix, vaPaddingAddress)
		if canon != nil || rule != runtime.CanonicalNonEntity || status != runtime.StaticStatusUnknownEntity {
			t.Fatalf("identity = %v/%q/%q", canon, rule, status)
		}
		s := ov.Summarize(vaPaddingAddress)
		if s == nil {
			t.Fatal("the runtime half is missing; the discrepancy must not erase the observation")
		}
		if s.CanonicalVA != nil {
			t.Fatalf("canonical_va = %q, want null", *s.CanonicalVA)
		}
		if s.Reached != runtime.TriTrue {
			t.Fatalf("reached = %q, want true", s.Reached)
		}
		if len(s.RuntimeCallers) != 1 {
			t.Fatalf("runtime_callers = %+v", s.RuntimeCallers)
		}
	})

	t.Run("runtime-only unknown function", func(t *testing.T) {
		canon, _, status, _, _ := runtime.ResolveIdentity(ix, vaRuntimeOnly)
		if canon != nil {
			t.Fatalf("canonical_va = %q; OpenSpore must not manufacture an identity", *canon)
		}
		if status != runtime.StaticStatusUnknownEntity {
			t.Fatalf("static_status = %q", status)
		}
		if ov.Summarize(vaRuntimeOnly) == nil {
			t.Fatal("the runtime half is missing")
		}
	})

	t.Run("UNKNOWN static ABI with a runtime observation", func(t *testing.T) {
		p := ix.Resolve(vaUnknownABI).Passport
		if p == nil {
			t.Fatal("no passport")
		}
		if p.ABI.IsAvailable() && p.ABI.Deref().Convention != nil {
			t.Fatalf("the fixture is meant to have an abstaining ABI record, got %v", p.ABI.Deref().Convention)
		}
		blockers := runtime.StaticBlockers(p)
		var found bool
		for _, b := range blockers {
			if b.Dimension == "ABI_RECORD" && b.Status == "UNKNOWN" {
				found = true
			}
		}
		if !found {
			t.Fatalf("blockers = %+v, want an ABI_RECORD UNKNOWN blocker", blockers)
		}
		s := ov.Summarize(vaUnknownABI)
		interp := runtime.Interpret(runtime.StaticStatusKnown, blockers, s, map[string][]runtime.ObservationKind{
			"ABI_RECORD": {runtime.ObsIndirectCall},
		})
		if len(interp.StaticBlockers) == 0 || len(interp.RuntimeFacts) == 0 {
			t.Fatalf("interpretation = %+v", interp)
		}
		if interp.VerdictUnchanged == "" {
			t.Fatal("the interpretation does not state that no verdict changed")
		}
		// The indirect call observation must be visible as an observation, never as
		// a convention.
		if len(s.Observations) != 1 || s.Observations[0].Kind != runtime.ObsIndirectCall || s.Observations[0].Indirect != runtime.TriTrue {
			t.Fatalf("observations = %+v", s.Observations)
		}
	})

	t.Run("import and exception observations", func(t *testing.T) {
		s := ov.Summarize(0x013cc1cc)
		if s == nil {
			t.Fatal("no summary")
		}
		if len(s.RuntimeImports) != 1 || s.RuntimeImports[0].Symbol != "InitializeCriticalSectionAndSpinCount" {
			t.Fatalf("runtime_imports = %+v", s.RuntimeImports)
		}
		if s.ExceptionCount != 1 {
			t.Fatalf("exception_count = %d, want 1", s.ExceptionCount)
		}
		if s.RuntimeImports[0].ReachedCount != nil {
			t.Fatalf("reached_count = %v; an IAT cell check does not establish that the import was called",
				*s.RuntimeImports[0].ReachedCount)
		}
	})
}

func TestSummarizeIsDeterministic(t *testing.T) {
	ix := fixtureIndex(t)
	ov := joinFixture(t)
	first, err := jsonString(ov.Summarize(vaCanonicalEntry))
	if err != nil {
		t.Fatal(err)
	}
	for i := 0; i < 3; i++ {
		again, err := jsonString(ov.Summarize(vaCanonicalEntry))
		if err != nil {
			t.Fatal(err)
		}
		if again != first {
			t.Fatalf("summary %d differs:\n%s\n---\n%s", i, first, again)
		}
	}
	_ = ix
}

func TestSummarizeMergesEntriesReachableFromOneAddress(t *testing.T) {
	// Two overlay entries can be reachable from one VA: the exact one, and any
	// non-entry address whose producer claimed this canonical VA. Both sets of
	// producer facts must survive, because hiding the second entry would hide
	// that the producer ever saw the non-entry address.
	e1 := entry(vaCanonicalEntry)
	e1.Canonicalization = runtime.CanonicalEntry
	e1.CanonicalVA = sPtr("0x00402000")
	e1.SetReached(true, 5)
	e1.RuntimeCallers = []runtime.RuntimeCaller{{CallsiteVA: "0x00925010"}}

	e2 := entry(vaInteriorAddress)
	e2.Canonicalization = runtime.CanonicalInterior
	e2.CanonicalVA = sPtr("0x00402000")
	e2.CanonicalOffset = runtime.Ptr(0x10)
	e2.SetReached(true, 5)
	e2.RuntimeCallers = []runtime.RuntimeCaller{{CallsiteVA: "0x00402018"}}

	ov := mustLoad(t, writeOverlay(t, baseMeta(), e1, e2))
	s := ov.Summarize(vaCanonicalEntry)
	if s == nil {
		t.Fatal("no summary")
	}
	if len(s.RuntimeCallers) != 2 {
		t.Fatalf("runtime_callers = %+v, want both entries' facts", s.RuntimeCallers)
	}
	if s.EntryCount == nil || *s.EntryCount != 10 {
		t.Fatalf("entry_count = %v, want the sum 10", s.EntryCount)
	}
}

// ---- static blockers and frontier ------------------------------------------

func TestStaticBlockersComeFromAdjudicatedDimensions(t *testing.T) {
	ix := fixtureIndex(t)
	p := ix.Resolve(vaCanonicalEntry).Passport
	if p == nil {
		t.Fatal("no passport")
	}
	blockers := runtime.StaticBlockers(p)
	got := map[string]string{}
	for _, b := range blockers {
		got[b.Dimension] = b.Status
	}
	// The fixture states PASS for ABI and EVIDENCE COVERAGE, NOT_AVAILABLE for
	// RETURN SEMANTICS and WARN for VIRTUAL DISPATCH. Only the last two may appear.
	if got["RETURN SEMANTICS"] != "NOT_AVAILABLE" {
		t.Fatalf("RETURN SEMANTICS = %q", got["RETURN SEMANTICS"])
	}
	if got["VIRTUAL DISPATCH"] != "WARN" {
		t.Fatalf("VIRTUAL DISPATCH = %q", got["VIRTUAL DISPATCH"])
	}
	if _, present := got["ABI"]; present {
		t.Fatalf("a PASS dimension was reported as a blocker: %v", got)
	}
	if _, present := got["EVIDENCE COVERAGE"]; present {
		t.Fatalf("a PASS dimension was reported as a blocker: %v", got)
	}
}

func TestStaticBlockersForAnUnreconstructedFunction(t *testing.T) {
	ix := fixtureIndex(t)
	p := ix.Resolve(vaUnpackaged).Passport
	if p == nil {
		t.Fatal("no passport")
	}
	// No evidence pack, so no ABI record and no validation report. The only
	// honest answer is "no adjudicated blocker" -- not an inferred one.
	if b := runtime.StaticBlockers(p); len(b) != 0 {
		t.Fatalf("blockers = %+v, want none for a function with no adjudicated verdict", b)
	}
}

func TestFrontierClassification(t *testing.T) {
	ix := fixtureIndex(t)
	ov := joinFixture(t)

	withBlockers := runtime.StaticBlockers(ix.Resolve(vaCanonicalEntry).Passport)

	cases := []struct {
		name      string
		input     runtime.FrontierInput
		want      string
		justified bool
	}{
		{
			name: "reached with a relevant observation",
			input: runtime.FrontierInput{
				VA: vaCanonicalEntry, HasStaticIdentity: true,
				Blockers: []runtime.Blocker{{Dimension: "RETURN SEMANTICS", Status: "NOT_AVAILABLE", Detail: "d"}},
			},
			want: runtime.ResolutionEvidenceCandidate, justified: true,
		},
		{
			name: "reached without a relevant observation",
			input: runtime.FrontierInput{
				VA: vaCanonicalEntry, HasStaticIdentity: true,
				Blockers: []runtime.Blocker{{Dimension: "GLOBALS", Status: "NOT_AVAILABLE", Detail: "d"}},
			},
			want: runtime.ResolutionReachedOnly, justified: false,
		},
		{
			name: "not reached",
			input: runtime.FrontierInput{
				VA: 0x7fff0000, HasStaticIdentity: true,
				Blockers: []runtime.Blocker{{Dimension: "ABI", Status: "WARN", Detail: "d"}},
			},
			want: runtime.ResolutionNotReached, justified: false,
		},
		{
			name:  "runtime-only address",
			input: runtime.FrontierInput{VA: vaPaddingAddress, HasStaticIdentity: false},
			want:  runtime.ResolutionRuntimeOnly, justified: true,
		},
		{
			name: "already promoted",
			input: runtime.FrontierInput{
				VA: vaCanonicalEntry, HasStaticIdentity: true, Promoted: true,
				Blockers: []runtime.Blocker{{Dimension: "RETURN SEMANTICS", Status: "NOT_AVAILABLE", Detail: "d"}},
			},
			want: runtime.ResolutionAlreadyClosed, justified: false,
		},
		{
			name:  "no static blocker",
			input: runtime.FrontierInput{VA: vaUnpackaged, HasStaticIdentity: true},
			want:  runtime.ResolutionNoBlocker, justified: false,
		},
		{
			name: "a dimension this build has no relevance model for",
			input: runtime.FrontierInput{
				VA: vaCanonicalEntry, HasStaticIdentity: true,
				Blockers: []runtime.Blocker{{Dimension: "SOME NEW DIMENSION", Status: "WARN", Detail: "d"}},
			},
			want: runtime.ResolutionReachedOnly, justified: false,
		},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			rows := runtime.Frontier(ov, []runtime.FrontierInput{tc.input})
			if len(rows) != 1 {
				t.Fatalf("rows = %d", len(rows))
			}
			if rows[0].ResolutionClass != tc.want {
				t.Fatalf("class = %q, want %q (justification: %s)", rows[0].ResolutionClass, tc.want, rows[0].Justification)
			}
			if rows[0].NewStaticTaskJustified != tc.justified {
				t.Fatalf("new_static_task_justified = %t, want %t", rows[0].NewStaticTaskJustified, tc.justified)
			}
			if rows[0].Justification == "" {
				t.Fatal("every class must carry a justification")
			}
		})
	}

	// A promoted target with relevant observations is STILL classified as closed:
	// runtime evidence must not reopen a promotion.
	rows := runtime.Frontier(ov, []runtime.FrontierInput{{
		VA: vaCanonicalEntry, HasStaticIdentity: true, Promoted: true, Blockers: withBlockers,
	}})
	if rows[0].ResolutionClass != runtime.ResolutionAlreadyClosed {
		t.Fatalf("class = %q, want %q", rows[0].ResolutionClass, runtime.ResolutionAlreadyClosed)
	}
	if len(rows[0].RelevantByDimension) == 0 {
		t.Fatal("relevance was suppressed on a closed target; the evidence should still be reported")
	}
}

func TestFrontierWithNoOverlayReportsNotReached(t *testing.T) {
	rows := runtime.Frontier(runtime.NewEmptyOverlay(), []runtime.FrontierInput{{
		VA: vaCanonicalEntry, HasStaticIdentity: true,
		Blockers: []runtime.Blocker{{Dimension: "ABI", Status: "WARN"}},
	}})
	if rows[0].Runtime != nil {
		t.Fatalf("Runtime = %+v, want null (nil means not observed, not observed-and-not-reached)", rows[0].Runtime)
	}
	if rows[0].ResolutionClass != runtime.ResolutionNotReached {
		t.Fatalf("class = %q", rows[0].ResolutionClass)
	}
}

func TestFrontierIsOrderedByVA(t *testing.T) {
	ov := joinFixture(t)
	in := []runtime.FrontierInput{
		{VA: 0x00925050, HasStaticIdentity: false},
		{VA: 0x00401020, HasStaticIdentity: true},
		{VA: 0x00402000, HasStaticIdentity: true},
	}
	first, _ := jsonString(runtime.Frontier(ov, in))
	shuffled := []runtime.FrontierInput{in[2], in[0], in[1]}
	second, _ := jsonString(runtime.Frontier(ov, shuffled))
	if first != second {
		t.Fatalf("frontier order depends on input order:\n%s\n---\n%s", first, second)
	}
}

func TestComputeStatsJoinsBothSides(t *testing.T) {
	ix := fixtureIndex(t)
	ov := joinFixture(t)
	s := runtime.ComputeStats(ov, ix)
	if s.Overlay.Entries != ov.Len() {
		t.Fatalf("entries = %d", s.Overlay.Entries)
	}
	if s.Overlay.Imports != 1 {
		t.Fatalf("imports = %d", s.Overlay.Imports)
	}
	if s.Overlay.Exceptions != 1 {
		t.Fatalf("exceptions = %d", s.Overlay.Exceptions)
	}
	if s.Joined == nil {
		t.Fatal("Joined is nil with a snapshot present")
	}
	if s.Joined.FunctionsIndexed != ix.Len() {
		t.Fatalf("functions_indexed = %d, want %d", s.Joined.FunctionsIndexed, ix.Len())
	}
	// 0x00401020 has an evidence pack whose ABI record abstains; 0x00402000 has a
	// stated convention. Exactly the abstaining one must count.
	if s.Joined.ABIUnknown != 1 {
		t.Fatalf("abi_unknown = %d, want 1 (the abstaining record)", s.Joined.ABIUnknown)
	}
	// 0x00925050 (padding), 0x00697c40 (unknown) and 0x013cc1cc (an IAT slot
	// outside every body) are all reachable at runtime and placeable nowhere.
	if s.Joined.RuntimeOnly < 3 {
		t.Fatalf("runtime_only = %d, want at least 3", s.Joined.RuntimeOnly)
	}
	if s.Joined.Promoted != 1 {
		t.Fatalf("promoted = %d", s.Joined.Promoted)
	}
	if s.Joined.ReturnUnknown < 1 {
		t.Fatalf("return_unknown = %d", s.Joined.ReturnUnknown)
	}
	// The joined list must be sorted so two runs produce identical output.
	for i := 1; i < len(s.Joined.RuntimeOnlyList); i++ {
		if s.Joined.RuntimeOnlyList[i-1] >= s.Joined.RuntimeOnlyList[i] {
			t.Fatalf("runtime_only_addresses is not sorted: %v", s.Joined.RuntimeOnlyList)
		}
	}
}

func TestComputeStatsWithNoIndexLeavesJoinedNull(t *testing.T) {
	s := runtime.ComputeStats(joinFixture(t), nil)
	if s.Joined != nil {
		t.Fatalf("Joined = %+v, want nil: no snapshot is not zero", s.Joined)
	}
	if s.Overlay.Entries == 0 {
		t.Fatal("the producer-side counts must still be reported without a snapshot")
	}
}
func jsonString(v any) (string, error) {
	b, err := json.Marshal(v)
	return string(b), err
}

func countText(p *int) string {
	if p == nil {
		return "null"
	}
	return fmt.Sprintf("%d", *p)
}
