package runtime_test

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
)

// Everything in this file uses a SYNTHETIC producer report, clearly marked as
// such. The real spore-recomp artifacts are exercised by the integration tests in
// package cli, which skip when the sibling checkout is absent.
//
// The distinction is not pedantry. A fixture built from the real report would be
// indistinguishable from the real report after one run, and a "real" observation
// that a test synthesised would be exactly the invented production evidence this
// bridge must never contain.

// syntheticReport builds a producer report with the shape spore-recomp emits.
type syntheticReport struct {
	SchemaVersion string `json:"schema_version"`
	EntryVA       string `json:"entry_va"`
	Outcome       string `json:"outcome"`
	OutcomeDetail string `json:"outcome_detail"`
	FinalEIP      string `json:"final_eip"`
	FinalKind     string `json:"final_kind"`
	Steps         int    `json:"steps"`
	PeakCallDepth int    `json:"peak_call_depth"`
	CallEdgeCount int    `json:"call_edge_count"`
	Image         struct {
		Loaded    bool   `json:"loaded"`
		BinarySHA string `json:"binary_sha256"`
		ImageBase string `json:"image_base"`
		EntryRVA  string `json:"entry_rva"`
	} `json:"image"`
	Registers map[string]string `json:"registers"`
	Imports   struct {
		Bindings      int `json:"bindings"`
		Modelled      int `json:"modelled"`
		IATCellChecks []struct {
			SlotVA      string `json:"slot_va"`
			LoadedValue string `json:"loaded_value"`
			Module      string `json:"module"`
			Symbol      string `json:"symbol"`
			Bound       bool   `json:"bound"`
		} `json:"iat_cell_checks"`
	} `json:"imports"`
	CallEdges []struct {
		CallsiteVA    string `json:"callsite_va"`
		TargetVA      string `json:"target_va"`
		Count         int    `json:"count"`
		FirstSequence int64  `json:"first_sequence"`
		MinDepth      int    `json:"min_depth"`
		MaxDepth      int    `json:"max_depth"`
	} `json:"call_edges"`
	Events []struct {
		Sequence         int64  `json:"sequence"`
		Class            string `json:"class"`
		CallerFunctionVA string `json:"caller_function_va"`
		CallsiteVA       string `json:"callsite_va"`
		TargetVA         string `json:"target_va"`
		ReturnAddress    string `json:"return_address"`
		CallDepth        int    `json:"call_depth"`
		Detail           string `json:"detail"`
	} `json:"events"`
}

func newSyntheticReport() *syntheticReport {
	r := &syntheticReport{
		SchemaVersion: "1.1.0",
		EntryVA:       "0x011e11a0",
		Outcome:       "STOPPED_UNRESOLVED_TARGET",
		OutcomeDetail: "the guest called a guest address with no recovered function",
		FinalEIP:      "0x00925b2b",
		FinalKind:     "unresolved_target",
		Steps:         1836,
		PeakCallDepth: 13,
		Registers: map[string]string{
			"eax": "0x00000004", "esp": "0x0012fecc", "eip": "0x00925b2b", "eflags": "0x00000283",
		},
	}
	r.Image.Loaded = true
	r.Image.BinarySHA = sporeSHA
	r.Image.ImageBase = sporeImg
	r.Image.EntryRVA = "0x00de11a0"

	r.CallEdges = append(r.CallEdges,
		struct {
			CallsiteVA    string `json:"callsite_va"`
			TargetVA      string `json:"target_va"`
			Count         int    `json:"count"`
			FirstSequence int64  `json:"first_sequence"`
			MinDepth      int    `json:"min_depth"`
			MaxDepth      int    `json:"max_depth"`
		}{CallsiteVA: "0x011e11a5", TargetVA: "0x011e1548", Count: 1, FirstSequence: 1, MinDepth: 1, MaxDepth: 1},
		struct {
			CallsiteVA    string `json:"callsite_va"`
			TargetVA      string `json:"target_va"`
			Count         int    `json:"count"`
			FirstSequence int64  `json:"first_sequence"`
			MinDepth      int    `json:"min_depth"`
			MaxDepth      int    `json:"max_depth"`
		}{CallsiteVA: "0x00925b33", TargetVA: "0x00925050", Count: 1, FirstSequence: 2, MinDepth: 13, MaxDepth: 13},
	)
	r.CallEdgeCount = len(r.CallEdges)

	r.Events = append(r.Events, struct {
		Sequence         int64  `json:"sequence"`
		Class            string `json:"class"`
		CallerFunctionVA string `json:"caller_function_va"`
		CallsiteVA       string `json:"callsite_va"`
		TargetVA         string `json:"target_va"`
		ReturnAddress    string `json:"return_address"`
		CallDepth        int    `json:"call_depth"`
		Detail           string `json:"detail"`
	}{
		Sequence: 1, Class: "UNRESOLVED_TARGET",
		CallerFunctionVA: "0x00925b00", CallsiteVA: "0x00925b33", TargetVA: "0x00925050",
		ReturnAddress: "0x00925b2b", CallDepth: 13,
		Detail: "call to 0x00925050, nothing registered there",
	})

	r.Imports.Bindings = 495
	r.Imports.Modelled = 495
	r.Imports.IATCellChecks = append(r.Imports.IATCellChecks, struct {
		SlotVA      string `json:"slot_va"`
		LoadedValue string `json:"loaded_value"`
		Module      string `json:"module"`
		Symbol      string `json:"symbol"`
		Bound       bool   `json:"bound"`
	}{SlotVA: "0x013cc1cc", LoadedValue: "0x700001b8", Module: "KERNEL32.dll", Symbol: "GetSystemTimeAsFileTime", Bound: true})
	return r
}

func writeReport(t *testing.T, r *syntheticReport) string {
	t.Helper()
	raw, err := json.MarshalIndent(r, "", "  ")
	if err != nil {
		t.Fatal(err)
	}
	path := filepath.Join(t.TempDir(), "synthetic-report.json")
	if err := os.WriteFile(path, append(raw, '\n'), 0o644); err != nil {
		t.Fatal(err)
	}
	return path
}

func convert(t *testing.T, r *syntheticReport) (*runtime.RecompResult, string) {
	t.Helper()
	path := writeReport(t, r)
	conv, err := runtime.ConvertRecomp(path, sporeSHA, runtime.RecompOptions{
		Artifact: "work/reports/synthetic.json",
	})
	if err != nil {
		t.Fatalf("ConvertRecomp: %v", err)
	}
	return conv, path
}

func TestConvertRecompProjectsTheProducerReport(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())

	if conv.Metadata.Binary.SHA256 != sporeSHA {
		t.Fatalf("binary_sha256 = %q", conv.Metadata.Binary.SHA256)
	}
	if conv.Metadata.Producer.Project != runtime.RecompProject {
		t.Fatalf("producer project = %q", conv.Metadata.Producer.Project)
	}
	if conv.Metadata.Producer.SourceSchema != "spore-recomp-runtime-report-1.1.0" {
		t.Fatalf("source_schema = %q", conv.Metadata.Producer.SourceSchema)
	}
	if conv.Unresolved != 1 {
		t.Fatalf("unresolved targets = %d, want the one UNRESOLVED_TARGET event", conv.Unresolved)
	}
	if conv.Imports != 1 {
		t.Fatalf("imports = %d", conv.Imports)
	}

	// Every entry must leave canonical_va null: the adapter does not decide
	// identity, and an adapter that did would be creating a second scheme.
	for _, e := range conv.Entries {
		if e.CanonicalVA != nil {
			t.Fatalf("%s got canonical_va %q from the adapter; identity is OpenSpore's to decide",
				e.RequestedVA, *e.CanonicalVA)
		}
		if e.Canonicalization != runtime.CanonicalUnknown {
			t.Fatalf("%s canonicalization = %q", e.RequestedVA, e.Canonicalization)
		}
		if len(e.Provenance) == 0 || e.Provenance[0].SourceClass != runtime.ProvenanceSourceRuntime {
			t.Fatalf("%s provenance = %+v", e.RequestedVA, e.Provenance)
		}
		if strings.Contains(e.Provenance[0].Artifact, "/datos") {
			t.Fatalf("the report's filesystem path leaked into provenance: %q", e.Provenance[0].Artifact)
		}
	}
}

func TestConvertRecompRecordsTheRuntimeOnlyAddress(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())
	var found *runtime.Entry
	for _, e := range conv.Entries {
		if e.RequestedVA == "0x00925050" {
			found = e
		}
	}
	if found == nil {
		t.Fatalf("0x00925050 is missing from the overlay; it is the address the whole bridge exists for")
	}
	if found.Reached != runtime.TriTrue {
		t.Fatalf("reached = %q, want true: the producer recorded an arrival", found.Reached)
	}
	if found.CanonicalVA != nil {
		t.Fatalf("canonical_va = %q, want null", *found.CanonicalVA)
	}
	// The caller edge must be on the TARGET, with the producer's caller function.
	if len(found.RuntimeCallers) == 0 {
		t.Fatalf("no runtime_callers on the target entry")
	}
	var sawFunction bool
	for _, c := range found.RuntimeCallers {
		if c.CallerFunctionVA != nil && *c.CallerFunctionVA == "0x00925b00" {
			sawFunction = true
		}
	}
	if !sawFunction {
		t.Fatalf("the producer's caller function 0x00925b00 was dropped: %+v", found.RuntimeCallers)
	}

	// The unresolved target must be on the CALLER, with the producer's own class
	// as the classification and indirect=true, which is the single most valuable
	// field for OpenSpore's open vftable questions.
	var caller *runtime.Entry
	for _, e := range conv.Entries {
		if e.RequestedVA == "0x00925b00" {
			caller = e
		}
	}
	if caller == nil {
		t.Fatal("the caller entry 0x00925b00 is missing")
	}
	var sawUnresolved bool
	for _, tg := range caller.RuntimeTargets {
		if tg.TargetVA == "0x00925050" && tg.Unresolved == runtime.TriTrue && tg.Indirect == runtime.TriTrue {
			sawUnresolved = true
			if tg.Classification != "UNRESOLVED_TARGET" {
				t.Fatalf("classification = %q, want the producer's own class verbatim", tg.Classification)
			}
		}
	}
	if !sawUnresolved {
		t.Fatalf("the unresolved target edge was lost: %+v", caller.RuntimeTargets)
	}
}

func TestConvertRecompLeavesReachedNullWhereTheReportDoesNotEstablishIt(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())
	for _, e := range conv.Entries {
		switch e.RequestedVA {
		case "0x011e11a0", "0x00925050":
			if e.Reached != runtime.TriTrue {
				t.Fatalf("%s reached = %q, want true", e.RequestedVA, e.Reached)
			}
		default:
			// A callsite was certainly passed through, but the report does not say
			// it was ENTERED, so the flag stays null and the count speaks.
			if e.Reached != runtime.TriNull {
				t.Fatalf("%s reached = %q, want null: a call-edge callsite is not an entry claim",
					e.RequestedVA, e.Reached)
			}
		}
	}
}

func TestConvertRecompEmitsNoFabricatedStackDelta(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())
	for _, e := range conv.Entries {
		for _, o := range e.Observations {
			if o.Kind == runtime.ObsStack {
				t.Fatalf("%s carries a stack observation from a single register sample: %+v",
					e.RequestedVA, o)
			}
		}
		// The registers that WERE sampled are reported as register observations.
		var sawEAX bool
		for _, o := range e.Observations {
			if o.Kind == runtime.ObsRegister && o.Register != nil && *o.Register == "eax" {
				sawEAX = true
			}
		}
		if e.RequestedVA == conv.Report.FinalEIP && !sawEAX {
			t.Fatalf("the final address carries no register observation; the producer's register dump was dropped")
		}
	}
}

func TestConvertRecompImportsDoNotClaimToHaveBeenCalled(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())
	var slot *runtime.Entry
	for _, e := range conv.Entries {
		if e.RequestedVA == "0x013cc1cc" {
			slot = e
		}
	}
	if slot == nil {
		t.Fatal("the IAT slot entry is missing")
	}
	if len(slot.RuntimeImports) != 1 {
		t.Fatalf("runtime_imports = %+v", slot.RuntimeImports)
	}
	imp := slot.RuntimeImports[0]
	if imp.ReachedCount != nil {
		t.Fatalf("reached_count = %v; an IAT cell check does not establish a call", *imp.ReachedCount)
	}
	if imp.Bound != runtime.TriTrue {
		t.Fatalf("bound = %q", imp.Bound)
	}
	if imp.Module != "KERNEL32.dll" || imp.Symbol != "GetSystemTimeAsFileTime" {
		t.Fatalf("the producer's import spelling was not preserved verbatim: %+v", imp)
	}
}

func TestConvertRecompOutputValidatesAndIsDeterministic(t *testing.T) {
	conv, _ := convert(t, newSyntheticReport())
	a := filepath.Join(t.TempDir(), "a.jsonl")
	b := filepath.Join(t.TempDir(), "b.jsonl")
	if _, err := runtime.Write(a, conv.Entries, conv.Metadata); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Write(b, conv.Entries, conv.Metadata); err != nil {
		t.Fatal(err)
	}
	da, _ := os.ReadFile(a)
	db, _ := os.ReadFile(b)
	if string(da) != string(db) {
		t.Fatal("two conversions of the same report are not byte-identical")
	}
	ov, err := runtime.Load(a, sporeSHA, 0x00400000)
	if err != nil {
		t.Fatalf("the converted overlay does not load: %v", err)
	}
	if p := ov.Verify(); len(p) != 0 {
		t.Fatalf("the converted overlay fails its own verification: %v", p)
	}
	if ov.Len() != conv.Addresses {
		t.Fatalf("entries = %d, want %d", ov.Len(), conv.Addresses)
	}
}

func TestConvertRecompRefusals(t *testing.T) {
	t.Run("no artifact identifier", func(t *testing.T) {
		path := writeReport(t, newSyntheticReport())
		_, err := runtime.ConvertRecomp(path, sporeSHA, runtime.RecompOptions{})
		if err == nil || !strings.Contains(err.Error(), "portable artifact identifier") {
			t.Fatalf("err = %v", err)
		}
	})

	t.Run("unknown producer schema", func(t *testing.T) {
		r := newSyntheticReport()
		r.SchemaVersion = "9.9.9"
		_, err := runtime.ConvertRecomp(writeReport(t, r), sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"})
		if !errors.Is(err, runtime.ErrSchema) {
			t.Fatalf("err = %v, want ErrSchema", err)
		}
	})

	t.Run("no binary sha", func(t *testing.T) {
		r := newSyntheticReport()
		r.Image.BinarySHA = ""
		_, err := runtime.ConvertRecomp(writeReport(t, r), sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"})
		if !errors.Is(err, runtime.ErrCorrupt) {
			t.Fatalf("err = %v, want ErrCorrupt", err)
		}
	})

	t.Run("wrong binary sha", func(t *testing.T) {
		r := newSyntheticReport()
		r.Image.BinarySHA = otherSHA
		_, err := runtime.ConvertRecomp(writeReport(t, r), sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"})
		if !errors.Is(err, runtime.ErrBinaryMismatch) {
			t.Fatalf("err = %v, want ErrBinaryMismatch", err)
		}
	})

	t.Run("unusable image base", func(t *testing.T) {
		r := newSyntheticReport()
		r.Image.ImageBase = ""
		_, err := runtime.ConvertRecomp(writeReport(t, r), sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"})
		if !errors.Is(err, runtime.ErrCorrupt) {
			t.Fatalf("err = %v, want ErrCorrupt", err)
		}
	})

	t.Run("malformed json", func(t *testing.T) {
		path := filepath.Join(t.TempDir(), "broken.json")
		if err := os.WriteFile(path, []byte("{ this is not json"), 0o644); err != nil {
			t.Fatal(err)
		}
		_, err := runtime.ConvertRecomp(path, sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"})
		if !errors.Is(err, runtime.ErrCorrupt) {
			t.Fatalf("err = %v, want ErrCorrupt", err)
		}
	})

	t.Run("missing file", func(t *testing.T) {
		_, err := runtime.ConvertRecomp(filepath.Join(t.TempDir(), "nope.json"), "", runtime.RecompOptions{Artifact: "a/b.json"})
		if !errors.Is(err, runtime.ErrMissing) {
			t.Fatalf("err = %v, want ErrMissing", err)
		}
	})
}

func TestConvertRecompIgnoresUnknownProducerFields(t *testing.T) {
	// The producer owns its schema and will keep adding fields. An adapter that
	// refused an unknown field would turn a producer improvement into a broken
	// ingestion path, so unknown fields are ignored -- while an unknown SCHEMA ID
	// is still refused, because that one means the fields may have moved.
	path := writeReport(t, newSyntheticReport())
	raw, _ := os.ReadFile(path)
	extended := strings.Replace(string(raw), `"schema_version"`, `"future_field":{"a":1},"schema_version"`, 1)
	if err := os.WriteFile(path, []byte(extended), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.ConvertRecomp(path, sporeSHA, runtime.RecompOptions{Artifact: "work/reports/synthetic.json"}); err != nil {
		t.Fatalf("an unknown producer field broke the adapter: %v", err)
	}
}

func TestDefaultRecompArtifact(t *testing.T) {
	got, ok := runtime.DefaultRecompArtifact("/datos/spore_recomp/work/reports/startup-recovery14.json")
	if !ok || got != "work/reports/startup-recovery14.json" {
		t.Fatalf("DefaultRecompArtifact = %q, %t", got, ok)
	}
	// A path with no reports component must NOT get a guessed identifier: the
	// guess would look portable and would not be.
	if got, ok := runtime.DefaultRecompArtifact("/tmp/whatever.json"); ok {
		t.Fatalf("DefaultRecompArtifact guessed %q from a path with no reports component", got)
	}
}

// ---- census ---------------------------------------------------------------

func mustBinary(t *testing.T) semantic.BinaryIdentity {
	t.Helper()
	return semantic.BinaryIdentity{SHA256: sporeSHA, ImageBase: sporeImg, Architecture: "x86:LE:32", Program: "SporeApp.exe", Version: "3.1.0.22"}
}

func TestCensusRoundTripAndVerification(t *testing.T) {
	doc := runtime.Census{
		Schema: runtime.CensusSchema,
		Binary: mustBinary(t),
		Source: runtime.CensusSource{
			Index:            "reconstruction/knowledge/index.json",
			IndexSHA256:      strings.Repeat("a", 64),
			PromotionMarkers: "src/reconstruction/*/promotion.json",
			MarkerGlob:       "src/reconstruction/*/promotion.json",
			PromotedCount:    89,
		},
		Targets: []runtime.CensusTarget{
			{VA: "0x00925000", Name: "FUN_00925000", Status: "queued", RuntimeGated: true,
				RuntimeGates: []string{"no original-process trace exists"}, Blockers: []string{"prose"}},
			{VA: "0x00402000", Name: "Get", Status: "reconstructed", Reconstructed: true, Promoted: true},
		},
	}
	path := filepath.Join(t.TempDir(), "census.json")
	sum, err := runtime.WriteCensus(path, doc)
	if err != nil {
		t.Fatal(err)
	}
	if len(sum) != 64 {
		t.Fatalf("digest = %q", sum)
	}
	loaded, err := runtime.LoadCensus(path, sporeSHA)
	if err != nil {
		t.Fatalf("LoadCensus: %v", err)
	}
	if problems := runtime.VerifyCensus(loaded); len(problems) != 0 {
		t.Fatalf("VerifyCensus: %v", problems)
	}
	// Targets are sorted by the writer, so the input order cannot leak into the
	// file or into a digest comparison.
	if loaded.Targets[0].VA != "0x00402000" {
		t.Fatalf("targets were not sorted: %+v", loaded.Targets)
	}
	if !loaded.Targets[0].Promoted {
		t.Fatal("the promoted flag was lost")
	}
	if !loaded.Targets[1].HasBlocker() {
		t.Fatal("HasBlocker() = false for a target carrying gate prose")
	}
	if loaded.Targets[0].HasBlocker() {
		t.Fatal("HasBlocker() = true for a fully closed promoted target")
	}

	// A hand-edited target list must be caught even with the digest present.
	loaded.Targets[0].Name = "tampered"
	if problems := runtime.VerifyCensus(loaded); len(problems) == 0 {
		t.Fatal("VerifyCensus accepted tampered targets")
	}
}

func TestCensusRefusals(t *testing.T) {
	base := `{"schema":"` + runtime.CensusSchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"source":{"index":"reconstruction/knowledge/index.json","index_sha256":"` +
		strings.Repeat("a", 64) + `","promotion_markers":"g","marker_glob":"g","promoted_count":1},"targets":[%s],"content_sha256":""}`
	tgt := func(va string) string {
		return `{"va":"` + va + `","name":"n","status":"s","reconstructed":false,"promoted":false,"evidence_level":null,"runtime_gated":false,"runtime_gates":[],"runtime_validated":0,"runtime_blocking_reason":[],"blockers":[],"unresolved_questions":[],"claimability":"","package":null}`
	}
	cases := []struct {
		name    string
		doc     string
		wantErr error
	}{
		{"unknown schema", strings.Replace(fmt.Sprintf(base, tgt("0x00401000")), `"`+runtime.CensusSchema+`"`, `"other-census-1"`, 1), runtime.ErrCensusSchema},
		{"unknown field", strings.Replace(fmt.Sprintf(base, tgt("0x00401000")), `"targets"`, `"future":1,"targets"`, 1), runtime.ErrCensusSchema},
		{"duplicate va", fmt.Sprintf(base, tgt("0x00401000")+","+tgt("0x00401000")), runtime.ErrCensusCorrupt},
		{"unsorted va", fmt.Sprintf(base, tgt("0x00402000")+","+tgt("0x00401000")), runtime.ErrCensusCorrupt},
		{"malformed va", fmt.Sprintf(base, tgt("00401000")), runtime.ErrCensusCorrupt},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), "c.json")
			if err := os.WriteFile(path, []byte(tc.doc), 0o644); err != nil {
				t.Fatal(err)
			}
			if _, err := runtime.LoadCensus(path, ""); !errors.Is(err, tc.wantErr) {
				t.Fatalf("err = %v, want %v", err, tc.wantErr)
			}
		})
	}
	t.Run("wrong binary", func(t *testing.T) {
		path := filepath.Join(t.TempDir(), "c.json")
		if err := os.WriteFile(path, []byte(fmt.Sprintf(base, tgt("0x00401000"))), 0o644); err != nil {
			t.Fatal(err)
		}
		if _, err := runtime.LoadCensus(path, otherSHA); !errors.Is(err, runtime.ErrBinaryMismatch) {
			t.Fatalf("err = %v, want ErrBinaryMismatch", err)
		}
	})
	t.Run("missing", func(t *testing.T) {
		if _, err := runtime.LoadCensus(filepath.Join(t.TempDir(), "nope.json"), ""); !errors.Is(err, runtime.ErrCensusMissing) {
			t.Fatalf("err = %v", err)
		}
	})
}
