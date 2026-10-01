package openspore

import (
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/testfixture"
)

// fixture builds a synthetic checkout shaped like the real one.
func fixture(t *testing.T) *testfixture.Tree {
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
	}
	tr.Triage = []testfixture.Triage{
		{VA: 0x00401000, GhidraName: "FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App", SCCSize: 1},
		{VA: 0x00401020, GhidraName: "FUN_00401020", Category: "UNKNOWN", Priority: "P3", Evidence: "UNKNOWN", SCCSize: 1},
		{VA: 0x00401030, GhidraName: "thunk_FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "IGNORE", Evidence: "UNKNOWN", SCCSize: 1},
		{VA: 0x00402000, GhidraName: "Editors::IBakeManager::Get", SDKName: "Editors::IBakeManager::Get", Category: "ENGINE_INTERFACE", Priority: "P3", Evidence: "CONFIRMED", Subsystem: "Editors", Structs: []string{"/Spore/Editors/IBakeManager"}, SCCSize: 1},
		{VA: 0x00925000, GhidraName: "FUN_00925000", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P1", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
		{VA: 0x009250c0, GhidraName: "FUN_009250c0", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P2", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
	}
	tr.XRefs = []testfixture.XRef{
		{Caller: 0x00402000, Callee: 0x00401000, RefType: "direct-call"},
		{Caller: 0x00402000, Callee: 0x00401020, RefType: "direct-call"},
		{Caller: 0x00401000, Callee: 0x00925000, RefType: "direct-call"},
	}
	tr.DataRefs = []testfixture.DataRef{
		{Caller: 0x00401000, Target: 0x015d0c00, Access: "read"},
		{Caller: 0x00401000, Target: 0x015d0c04, Access: "read"},
	}
	tr.Memberships = []testfixture.Membership{
		{VA: 0x00401000, Table: 0x013eb308, Slot: 2},
		{VA: 0x00401000, Table: 0x013eb308, Slot: 7},
		{VA: 0x00401020, Table: 0x013eb2f0, Slot: 0},
	}
	tr.Packs[0x00401000] = true
	tr.Packs[0x00401020] = true
	tr.ABIRecords[0x00401000] = testfixture.ABIRecordJSON(strPtr("__thiscall"), "INFERRED", boolPtr(true), nil)
	// 0x00401020 gets a pack with NO abi_derived value: an explicit absence
	// inside a pack, which is different from having no pack at all.
	tr.Validation[0x00401000] = testfixture.ValidationDoc{
		Schema: "openspore-structural-validation-1",
		Checks: map[string]testfixture.Check{
			"ABI":     {Status: "PASS", Coverage: "partial", Detail: "convention present"},
			"GLOBALS": {Status: "WARN", Coverage: "partial", Detail: "no declaration"},
		},
		Static: map[string]any{"coverage": map[string]any{"pass": 1, "warn": 1, "total": 2}},
	}
	tr.Promoted[0x00401000] = true
	tr.RecordOverrides["0x00401000"] = map[string]any{
		"package":            "PKG-FIXTURE",
		"status":             "reconstructed",
		"review_status":      "approved",
		"integration_status": "integrated",
		"subsystem":          "Graphics.Transform",
		"semantic": map[string]any{
			"classification": "BOUNDED_SEMANTIC",
			"confidence":     map[string]any{"identity": "SUPPORTED", "mechanics": 0.72},
			"evidence":       []any{map[string]any{"claim": "reads +0x10", "class": "direct_body", "source": "ghidra://x"}},
		},
		"unresolved_questions": []string{"what the selector hash is OF"},
		"globals":              []string{"global:0x015d0c00"},
		"types":                []string{"Transform"},
		"identity_refuted": map[string]any{
			"name": "FUN_00401000", "superseded": "Editors::IBakeManager::Get",
			"superseded_source": "triage_queue",
			"reason":            map[string]any{"decompiler_artefact_not_followed": map[string]any{"finding": "no FPU opcode"}},
		},
	}
	tr.RecordOverrides["0x00401020"] = map[string]any{
		// A package with NO promotion record: the unpromoted-but-reconstructed
		// case, which must be an explicit false and not an unknown.
		"package":         "PKG-UNPROMOTED",
		"status":          "reconstructed",
		"semantic_status": "static_reconstruction_runtime_gated",
	}
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	return tr
}

func strPtr(s string) *string { return &s }
func boolPtr(b bool) *bool    { return &b }

func TestLoadSourcesReadsEveryAuthoritativeArtifact(t *testing.T) {
	tr := fixture(t)
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	if len(srcs.Universe.Entries) != 6 {
		t.Fatalf("universe has %d entries, want 6", len(srcs.Universe.Entries))
	}
	if srcs.Universe.Fallback {
		t.Fatalf("the primary universe export was present but the fallback was used")
	}
	if len(srcs.Triage.ByAddr) != 6 {
		t.Fatalf("triage has %d rows, want 6", len(srcs.Triage.ByAddr))
	}
	if len(srcs.Evidence) != 2 {
		t.Fatalf("evidence map has %d VAs, want 2", len(srcs.Evidence))
	}
	if srcs.VTablesNil {
		t.Fatalf("the sound vftable scan was present but reported absent")
	}
	if len(srcs.VTable) != 2 {
		t.Fatalf("vtable memberships keyed %d VAs, want 2", len(srcs.VTable))
	}
	if got := len(srcs.VTable[0x00401000]); got != 2 {
		t.Fatalf("0x00401000 has %d memberships, want 2", got)
	}
	if srcs.Graph.Callees[0x00402000] == nil || len(srcs.Graph.Callees[0x00402000]) != 2 {
		t.Fatalf("callees for 0x00402000 = %v, want 2 entries", srcs.Graph.Callees[0x00402000])
	}
	if len(srcs.Graph.Callers[0x00401000]) != 1 || srcs.Graph.Callers[0x00401000][0] != 0x00402000 {
		t.Fatalf("callers for 0x00401000 = %v, want [0x00402000]", srcs.Graph.Callers[0x00401000])
	}
	if srcs.DataRefs[0x00401000] != 2 {
		t.Fatalf("data refs for 0x00401000 = %d, want 2 distinct addresses", srcs.DataRefs[0x00401000])
	}
	if len(srcs.Digests) == 0 {
		t.Fatalf("no input digests recorded; reproducibility cannot be checked")
	}
	for i := 1; i < len(srcs.Digests); i++ {
		if srcs.Digests[i-1].Path > srcs.Digests[i].Path {
			t.Fatalf("input digests are not sorted by path, so the metadata would vary with read order")
		}
	}
}

func TestBuildPassportsProjectsTriStateNotZeroValues(t *testing.T) {
	tr := fixture(t)
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	passports, counts, _, err := BuildPassports(srcs)
	if err != nil {
		t.Fatalf("BuildPassports: %v", err)
	}
	byVA := map[uint32]*semantic.Passport{}
	for _, p := range passports {
		a, err := semantic.ParseAddr(p.Identity.CanonicalVA, 0)
		if err != nil {
			t.Fatalf("canonical_va %q: %v", p.Identity.CanonicalVA, err)
		}
		byVA[uint32(a)] = p
	}

	// Function with a pack, an ABI record, a receiver, a vtable, validation and
	// a promotion record.
	full := byVA[0x00401000]
	if full == nil {
		t.Fatalf("no passport for 0x00401000")
	}
	if !full.ABI.IsAvailable() || full.ABI.Deref().Convention == nil {
		t.Fatalf("0x00401000 should carry a convention")
	}
	if got := *full.ABI.Deref().Convention; got != "__thiscall" {
		t.Fatalf("convention = %q, want __thiscall", got)
	}
	if got := full.ABI.Deref().Receiver.Present; got != semantic.TriTrue {
		t.Fatalf("receiver.present = %q, want true", got)
	}
	if full.VTable.Deref().ABIAttributed != nil {
		t.Fatalf("0x00401000 has no VFT inference in the fixture but one was attributed")
	}
	if len(full.VTable.Deref().Memberships) != 2 {
		t.Fatalf("vtable memberships = %d, want 2", len(full.VTable.Deref().Memberships))
	}
	if full.VTable.Deref().Memberships[0].SlotWidth == nil {
		t.Fatalf("membership slot width was dropped although the scan stated a table width")
	}
	if full.Reconstruction.Deref().Promoted != semantic.TriTrue {
		t.Fatalf("promoted = %q, want true", full.Reconstruction.Deref().Promoted)
	}
	if full.Reconstruction.Deref().Validation == nil {
		t.Fatalf("validation summary missing although validation.json exists")
	}
	if got := full.Reconstruction.Deref().Validation.Coverage["ABI"].Status; got != "PASS" {
		t.Fatalf("validation ABI status = %q, want PASS", got)
	}
	if full.Evidence.Pack == nil || !strings.HasSuffix(*full.Evidence.Pack, "00401000/evidence.json") {
		t.Fatalf("evidence pack path = %v", full.Evidence.Pack)
	}
	if len(full.Provenance) == 0 {
		t.Fatalf("provenance entries were dropped")
	}
	if full.Names.IdentityRefuted == nil || full.Names.IdentityRefuted.Superseded != "Editors::IBakeManager::Get" {
		t.Fatalf("the refuted identity was not carried: %+v", full.Names.IdentityRefuted)
	}
	if full.Globals.Deref()[0] != "global:0x015d0c00" {
		t.Fatalf("globals = %v", full.Globals.Deref())
	}

	// Function with a pack but no abi_derived value: explicit absence INSIDE a
	// pack. The pack's own reason text is carried verbatim, not reduced to a
	// generic code.
	noABI := byVA[0x00401020]
	if noABI.ABI.IsAvailable() {
		t.Fatalf("0x00401020 abi group = %+v, want the pack's explicit absence", noABI.ABI)
	}
	if noABI.ABI.EvidenceLevel != semantic.LevelUnknown || noABI.ABI.EvidenceState != semantic.EvidenceMissing {
		t.Fatalf("an absent abi value lost its UNKNOWN/MISSING markers: %+v", noABI.ABI)
	}
	if noABI.ABI.Reason != "no exact source evidence found" {
		t.Fatalf("the pack's own reason was not carried verbatim: %q", noABI.ABI.Reason)
	}
	if !noABI.Reconstruction.IsAvailable() {
		t.Fatalf("a function with a reconstruction package reported an absent reconstruction group")
	}
	if noABI.Reconstruction.Deref().Promoted != semantic.TriFalse {
		t.Fatalf("promoted = %q, want an explicit false for a reconstructed function with no promotion record",
			noABI.Reconstruction.Deref().Promoted)
	}
	if noABI.Reconstruction.Deref().Package == nil || *noABI.Reconstruction.Deref().Package != "PKG-UNPROMOTED" {
		t.Fatalf("package = %v", noABI.Reconstruction.Deref().Package)
	}
	if noABI.Evidence.PromotionRecord != nil {
		t.Fatalf("a promotion record path was invented for a function with none")
	}
	if noABI.Evidence.PromotionRecord != nil {
		t.Fatalf("promotion record path was invented for a function with none")
	}

	// Function with no pack at all: the generic code applies.
	bare := byVA[0x00402000]
	if bare.ABI.IsAvailable() || bare.ABI.Reason != semantic.ReasonNoEvidencePack {
		t.Fatalf("0x00402000 abi group = %+v, want unavailable/no_evidence_pack", bare.ABI)
	}
	if bare.Names.SDKName == nil || *bare.Names.SDKName != "Editors::IBakeManager::Get" {
		t.Fatalf("sdk_name was not carried: %v", bare.Names.SDKName)
	}
	if bare.Names.SDKNameSource == nil {
		t.Fatalf("sdk_name without a source attribution")
	}
	if bare.Globals.IsAvailable() {
		t.Fatalf("globals should be an explicit absence for a function with none")
	}

	// Subsystem precedence: the knowledge index's reconciled value wins over
	// the triage row's, because that is what the index is for.
	if full.Classification.Subsystem == nil || *full.Classification.Subsystem != "Graphics.Transform" {
		t.Fatalf("subsystem = %v, want the index's Graphics.Transform", full.Classification.Subsystem)
	}

	// RenderWare is detected from either vocabulary.
	for _, va := range []uint32{0x00925000, 0x009250c0} {
		if byVA[va].Classification.RenderwareRole == nil {
			t.Fatalf("0x%08x lost its RenderWare classification", va)
		}
	}

	// Counts.
	if counts.Functions != 6 {
		t.Fatalf("counts.Functions = %d, want 6", counts.Functions)
	}
	if counts.WithSDKName != 1 {
		t.Fatalf("counts.WithSDKName = %d, want 1", counts.WithSDKName)
	}
	if counts.WithVTableMembership != 2 {
		t.Fatalf("counts.WithVTableMembership = %d, want 2", counts.WithVTableMembership)
	}
	if counts.WithPromoted != 1 {
		t.Fatalf("counts.WithPromoted = %d, want 1", counts.WithPromoted)
	}
	if counts.WithReconstruction != 2 {
		t.Fatalf("counts.WithReconstruction = %d, want 2", counts.WithReconstruction)
	}
	if counts.WithValidation != 1 {
		t.Fatalf("counts.WithValidation = %d, want 1", counts.WithValidation)
	}
}

func TestCanonicalIdentityMatchesTheRepositoryRule(t *testing.T) {
	tr := fixture(t)
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	u := srcs.Universe

	// An entry resolves to itself: the rule reports "already an entry", which
	// the index represents as no resolution at all.
	if _, ok := u.CanonicalIdentity(0x00401000); ok {
		t.Fatalf("an address that IS an entry was reported as resolved")
	}
	// An interior address resolves to its containing entry, with the offset.
	res, ok := u.CanonicalIdentity(0x00401010)
	if !ok || res.Entry != 0x00401000 || res.Offset != 0x10 {
		t.Fatalf("interior 0x00401010 resolved to %+v (ok=%t), want entry 0x00401000 offset 16", res, ok)
	}
	// The last byte of a body IS inside the body: start <= a < start + size.
	res, ok = u.CanonicalIdentity(0x0040101f)
	if !ok || res.Entry != 0x00401000 {
		t.Fatalf("the last byte of a body did not resolve: %+v (ok=%t)", res, ok)
	}
	// One past the end is the gap, and the gap resolves to nothing. This is the
	// conservative direction the repository chose on purpose.
	if _, ok := u.CanonicalIdentity(0x0092504a); ok {
		t.Fatalf("the exclusive end of a body was treated as inside it")
	}
	if _, ok := u.CanonicalIdentity(0x00925050); ok {
		t.Fatalf("padding between two entries resolved to a function; the rule must leave it alone")
	}
	if _, ok := u.CanonicalIdentity(0x00000010); ok {
		t.Fatalf("an address below the first entry resolved")
	}
}

func TestBuildIsDeterministic(t *testing.T) {
	tr := fixture(t)
	var first string
	for i := 0; i < 3; i++ {
		srcs, err := LoadSources(tr.Root)
		if err != nil {
			t.Fatalf("LoadSources: %v", err)
		}
		passports, _, _, err := BuildPassports(srcs)
		if err != nil {
			t.Fatalf("BuildPassports: %v", err)
		}
		var sb strings.Builder
		for _, p := range passports {
			line, err := semantic.MarshalLine(p)
			if err != nil {
				t.Fatalf("MarshalLine: %v", err)
			}
			sb.Write(line)
		}
		if i == 0 {
			first = sb.String()
			continue
		}
		if sb.String() != first {
			t.Fatalf("build %d differs from build 0", i)
		}
	}
}

func TestUniverseFallsBackToTheTrackedCoverageLedger(t *testing.T) {
	tr := fixture(t)
	tr.OmitFunctionsTSV = true
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	if FileExists(filepath.Join(tr.Root, RelUniverse)) {
		t.Fatalf("fixture still has the primary universe export")
	}
	u, absent, err := LoadUniverse(tr.Root)
	if err != nil {
		t.Fatalf("LoadUniverse: %v", err)
	}
	if !u.Fallback {
		t.Fatalf("the fallback universe was used but not reported as a fallback")
	}
	if u.Source != RelUniverseAlt {
		t.Fatalf("universe source = %q, want %q", u.Source, RelUniverseAlt)
	}
	if len(u.Entries) != 6 {
		t.Fatalf("fallback universe has %d entries, want 6", len(u.Entries))
	}
	if len(absent) == 0 || absent[0].Reason == "" {
		t.Fatalf("the absent primary artifact was not reported with a reason")
	}
	if _, ok := u.CanonicalIdentity(0x00401010); !ok {
		t.Fatalf("interior resolution does not work on the fallback universe")
	}
}

func TestMissingUniverseIsAnExplicitFailure(t *testing.T) {
	tr := fixture(t)
	if err := os.Remove(filepath.Join(tr.Root, RelUniverse)); err != nil {
		t.Fatalf("Remove: %v", err)
	}
	// The tracked fallback was never written by this fixture, so removing it is
	// a no-op; assert that rather than failing on the remove.
	_ = os.Remove(filepath.Join(tr.Root, RelUniverseAlt))
	_, _, err := LoadUniverse(tr.Root)
	if err == nil {
		t.Fatalf("LoadUniverse accepted a checkout with no universe at all")
	}
	if !strings.Contains(err.Error(), "universe") {
		t.Fatalf("the error does not name the missing concept: %v", err)
	}
}

func TestMissingVTableScanIsReportedAsAbsentNotEmpty(t *testing.T) {
	tr := fixture(t)
	tr.OmitVTableScan = true
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	if !srcs.VTablesNil {
		t.Fatalf("an absent scan was reported as present")
	}
	found := false
	for _, a := range srcs.Absent {
		if strings.Contains(a.Path, "vftables-") {
			found = true
			if a.Reason == "" {
				t.Fatalf("an absent authoritative input was reported without a reason")
			}
		}
	}
	if !found {
		t.Fatalf("the absent vftable scan was not listed in absent_inputs")
	}
	passports, _, _, err := BuildPassports(srcs)
	if err != nil {
		t.Fatalf("BuildPassports: %v", err)
	}
	for _, p := range passports {
		if p.VTable.IsAvailable() {
			t.Fatalf("%s claims vtable membership although the scan is absent", p.Identity.CanonicalVA)
		}
		if p.VTable.Reason != semantic.ReasonVTableScanAbsent && p.VTable.Reason != semantic.ReasonNoVTableMembership {
			t.Fatalf("%s vtable absence reason = %q", p.Identity.CanonicalVA, p.VTable.Reason)
		}
	}
}

func TestMismatchedVTableScanCacheIsRefused(t *testing.T) {
	tr := fixture(t)
	// A cache file NAMED for the requested binary whose CONTENTS declare a
	// different one must be refused, not silently believed.
	path := filepath.Join(tr.Root, RelVftableDir, "vftables-"+testfixture.BinarySHA+".json")
	raw, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	tampered := strings.Replace(string(raw), testfixture.BinarySHA, testfixture.OtherSHA, -1)
	if err := os.WriteFile(path, []byte(tampered), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	memb, scan, absent, err := LoadVTableScan(tr.Root, testfixture.BinarySHA)
	if err != nil {
		t.Fatalf("LoadVTableScan: %v", err)
	}
	if scan != nil || memb != nil {
		t.Fatalf("a cache whose contents name a different binary was accepted")
	}
	if len(absent) == 0 || !strings.Contains(absent[0].Reason, "is not the requested") {
		t.Fatalf("the mismatch was not explained: %+v", absent)
	}
}

func TestVTableScanForADifferentBinaryIsListedNotSubstituted(t *testing.T) {
	tr := fixture(t)
	memb, _, absent, err := LoadVTableScan(tr.Root, testfixture.OtherSHA)
	if err != nil {
		t.Fatalf("LoadVTableScan: %v", err)
	}
	if memb != nil {
		t.Fatalf("a scan for another binary was substituted")
	}
	if len(absent) == 0 || !strings.Contains(absent[0].Reason, "describe a different binary") {
		t.Fatalf("the absence did not say which caches exist: %+v", absent)
	}
}

func TestNonEntryEvidencePackIsAttachedToItsContainingEntry(t *testing.T) {
	tr := fixture(t)
	// A pack filed under an interior address of 0x00401000's body.
	interior := uint32(0x00401010)
	tr.Packs[interior] = true
	tr.ABIRecords[interior] = testfixture.ABIRecordJSON(strPtr("__cdecl"), "INFERRED", nil, nil)
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	passports, counts, notes, err := BuildPassports(srcs)
	if err != nil {
		t.Fatalf("BuildPassports: %v", err)
	}
	if counts.AttachedStrayPacks != 1 {
		t.Fatalf("counts.AttachedStrayPacks = %d, want 1", counts.AttachedStrayPacks)
	}
	if notes.OrphanEvidencePacks != 0 {
		t.Fatalf("notes.OrphanEvidencePacks = %d, want 0", notes.OrphanEvidencePacks)
	}
	for _, p := range passports {
		if p.Identity.CanonicalVA != "0x00401000" {
			continue
		}
		if len(p.Evidence.AdditionalPacks) != 1 {
			t.Fatalf("additional_packs = %d, want 1", len(p.Evidence.AdditionalPacks))
		}
		ap := p.Evidence.AdditionalPacks[0]
		if ap.RequestedVA != "0x00401010" || ap.Offset != 0x10 || ap.Rule != semantic.CanonicalIdentityRule {
			t.Fatalf("additional pack = %+v, want the interior address with offset and rule", ap)
		}
	}
}

func TestUnplaceableEvidencePackIsCountedAsAnOrphan(t *testing.T) {
	tr := fixture(t)
	// 0x00925050 is in the padding between two entries, so no passport can
	// reference it. It must be reported rather than silently dropped.
	tr.Packs[0x00925050] = true
	tr.ABIRecords[0x00925050] = testfixture.ABIRecordJSON(nil, "UNKNOWN", nil, nil)
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	srcs, err := LoadSources(tr.Root)
	if err != nil {
		t.Fatalf("LoadSources: %v", err)
	}
	_, counts, notes, err := BuildPassports(srcs)
	if err != nil {
		t.Fatalf("BuildPassports: %v", err)
	}
	if notes.OrphanEvidencePacks != 1 {
		t.Fatalf("notes.OrphanEvidencePacks = %d, want 1", notes.OrphanEvidencePacks)
	}
	if len(notes.OrphanEvidencePackPaths) != 1 ||
		!strings.HasSuffix(notes.OrphanEvidencePackPaths[0], "00925050/evidence.json") {
		t.Fatalf("orphan paths = %v", notes.OrphanEvidencePackPaths)
	}
	if counts.AttachedStrayPacks != 0 {
		t.Fatalf("an unplaceable pack was attached to something")
	}
}
