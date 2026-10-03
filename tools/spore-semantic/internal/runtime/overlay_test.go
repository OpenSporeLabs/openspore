package runtime_test

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"errors"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
)

const (
	sporeSHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
	otherSHA = "0000000000000000000000000000000000000000000000000000000000000000"
	sporeImg = "0x00400000"
)

func baseMeta() runtime.Metadata {
	return runtime.Metadata{
		Binary: semantic.BinaryIdentity{
			SHA256: sporeSHA, ImageBase: sporeImg,
			Architecture: "x86:LE:32", Program: "SporeApp.exe", Version: "3.1.0.22",
		},
		Producer: runtime.Producer{
			Project: "spore-recomp", Name: "synthetic fixture", Version: "test",
			Artifact: "work/reports/synthetic.json",
		},
	}
}

func prov() []runtime.ProvenanceEntry {
	return []runtime.ProvenanceEntry{{
		SourceClass: runtime.ProvenanceSourceRuntime,
		Producer:    "spore-recomp",
		Artifact:    "work/reports/synthetic.json",
	}}
}

// writeOverlay serialises entries and returns the path.
func writeOverlay(t *testing.T, meta runtime.Metadata, entries ...*runtime.Entry) string {
	t.Helper()
	path := filepath.Join(t.TempDir(), "overlay.jsonl")
	if _, err := runtime.Write(path, entries, meta); err != nil {
		t.Fatalf("Write: %v", err)
	}
	return path
}

// entry builds a minimal valid entry at a canonical VA.
func entry(va uint32) *runtime.Entry {
	e := runtime.NewEntry(semantic.Addr(va).String())
	e.Provenance = prov()
	return e
}

func mustLoad(t *testing.T, path string) *runtime.Overlay {
	t.Helper()
	ov, err := runtime.Load(path, "", 0)
	if err != nil {
		t.Fatalf("Load(%s): %v", path, err)
	}
	return ov
}

// ---- the happy path -------------------------------------------------------

func TestValidOverlayLoadsAndVerifies(t *testing.T) {
	a := entry(0x00925050)
	a.SetReached(true, 412)
	a.Canonicalization = runtime.CanonicalNonEntity
	a.RuntimeCallers = []runtime.RuntimeCaller{{CallsiteVA: "0x00925b33", CallerFunctionVA: runtime.Ptr("0x00925b00"), Count: runtime.Ptr(1)}}
	a.RuntimeTargets = []runtime.RuntimeTarget{{TargetVA: "0x00e5c780", Indirect: runtime.TriNull, Unresolved: runtime.TriFalse, Classification: "direct_call"}}
	a.Observations = []runtime.Observation{
		{Kind: runtime.ObsEntry, EIP: runtime.Ptr("0x00925050"), CallDepth: runtime.Ptr(13),
			Detail: "arrival recorded by producer event UNRESOLVED_TARGET"},
	}
	path := writeOverlay(t, baseMeta(), a)

	ov := mustLoad(t, path)
	if ov.Len() != 1 {
		t.Fatalf("entries = %d, want 1", ov.Len())
	}
	if problems := ov.Verify(); len(problems) != 0 {
		t.Fatalf("Verify reported %v on a freshly written overlay", problems)
	}
	got := ov.Entries[0x00925050]
	if got == nil {
		t.Fatalf("entry 0x00925050 missing after load")
	}
	if got.Reached != runtime.TriTrue {
		t.Fatalf("reached = %q, want \"true\"", got.Reached)
	}
	if got.EntryCount == nil || *got.EntryCount != 412 {
		t.Fatalf("entry_count = %v, want 412", got.EntryCount)
	}
	if got.Canonicalization != runtime.CanonicalNonEntity {
		t.Fatalf("canonicalization = %q", got.Canonicalization)
	}
	if len(got.Observations) != 1 || got.Observations[0].Kind != runtime.ObsEntry {
		t.Fatalf("observations did not round-trip: %+v", got.Observations)
	}
	// A null tri-state must survive as the explicit string, not as "".
	if got.RuntimeTargets[0].Indirect != runtime.TriNull {
		t.Fatalf("indirect = %q, want the explicit \"null\"", got.RuntimeTargets[0].Indirect)
	}
}

func TestWriteIsDeterministic(t *testing.T) {
	mk := func() string {
		a := entry(0x00401000)
		a.SetReached(true, 3)
		a.Canonicalization = runtime.CanonicalEntry
		a.CanonicalVA = runtime.Ptr("0x00401000")
		b := entry(0x00925050)
		b.Reached = runtime.TriFalse
		b.Canonicalization = runtime.CanonicalNonEntity
		return writeOverlay(t, baseMeta(), b, a) // deliberately out of order
	}
	first, second := mk(), mk()
	da, err := os.ReadFile(first)
	if err != nil {
		t.Fatal(err)
	}
	db, err := os.ReadFile(second)
	if err != nil {
		t.Fatal(err)
	}
	if string(da) != string(db) {
		t.Fatalf("two writes of the same entries differ:\n%s\n---\n%s", da, db)
	}
	// The header must come first so a consumer can check identity before parsing.
	if !strings.HasPrefix(string(da), `{"record":"metadata"`) {
		t.Fatalf("the metadata record is not line 1: %.80s", da)
	}
	// And the input order must not survive: the writer sorts.
	lines := strings.Split(strings.TrimSpace(string(da)), "\n")
	if !strings.Contains(lines[1], "0x00401000") || !strings.Contains(lines[2], "0x00925050") {
		t.Fatalf("records were not sorted ascending by requested_va:\n%s", da)
	}
}

// ---- identity refusals ----------------------------------------------------

func TestWrongBinarySHAIsRefused(t *testing.T) {
	m := baseMeta()
	m.Binary.SHA256 = otherSHA
	path := writeOverlay(t, m, entry(0x00401000))

	_, err := runtime.Load(path, sporeSHA, 0)
	if !errors.Is(err, runtime.ErrBinaryMismatch) {
		t.Fatalf("err = %v, want ErrBinaryMismatch", err)
	}
	// The same file loads when no digest is required, so the refusal is about the
	// REQUIREMENT and not about the file being unparseable.
	if _, err := runtime.Load(path, "", 0); err != nil {
		t.Fatalf("Load without a required sha failed: %v", err)
	}
}

func TestNonHexOrShortSHAIsRefused(t *testing.T) {
	for _, bad := range []string{"", "abc", sporeSHA + "00", strings.Repeat("z", 64)} {
		m := baseMeta()
		m.Binary.SHA256 = bad
		path := filepath.Join(t.TempDir(), "o.jsonl")
		// Hand-write the header so Write cannot reject it first.
		hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + bad +
			`","image_base":"` + sporeImg + `"},"producer":{"project":"p","name":"n","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":1,"reached":0,"reached_unknown":0,"not_reached":1,"total_entry_count":0,"runtime_only":1,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":1},"content_sha256":""}` + "\n"
		line := `{"record":"entry","requested_va":"0x00401000","canonical_va":null,"canonicalization":"not_stated","canonical_offset":null,"reached":"false","entry_count":null,"first_reached_from":null,"max_call_depth":null,"runtime_callers":[],"runtime_targets":[],"runtime_imports":[],"observations":[],"provenance":[{"source_class":"runtime","producer":"p","artifact":"a"}]}` + "\n"
		if err := os.WriteFile(path, []byte(hdr+line), 0o644); err != nil {
			t.Fatal(err)
		}
		_, err := runtime.Load(path, "", 0)
		if !errors.Is(err, runtime.ErrCorrupt) {
			t.Fatalf("binary_sha256 %q: err = %v, want ErrCorrupt", bad, err)
		}
	}
}

func TestWrongImageBaseIsRefused(t *testing.T) {
	path := writeOverlay(t, baseMeta(), entry(0x00401000))
	_, err := runtime.Load(path, "", 0x50000000)
	if !errors.Is(err, runtime.ErrImageBaseMismatch) {
		t.Fatalf("err = %v, want ErrImageBaseMismatch", err)
	}
	if _, err := runtime.Load(path, "", 0x00400000); err != nil {
		t.Fatalf("matching image base refused: %v", err)
	}
}

func TestUnknownSchemaIsRefused(t *testing.T) {
	src := writeOverlay(t, baseMeta(), entry(0x00401000))
	raw, _ := os.ReadFile(src)
	bad := strings.Replace(string(raw), runtime.OverlaySchema, runtime.OverlaySchema+"-v2", 1)
	path := filepath.Join(t.TempDir(), "o.jsonl")
	if err := os.WriteFile(path, []byte(bad), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Load(path, "", 0); !errors.Is(err, runtime.ErrSchema) {
		t.Fatalf("err = %v, want ErrSchema", err)
	}
}

func TestUnknownFieldIsRefusedAsSchemaNotCorruption(t *testing.T) {
	// A field this build has never heard of means the contract moved, which is a
	// different diagnosis from a corrupt file and gets a different exit code.
	src := writeOverlay(t, baseMeta(), entry(0x00401000))
	raw, _ := os.ReadFile(src)
	bad := strings.Replace(string(raw), `"record":"entry"`, `"record":"entry","future_field":1`, 1)
	path := filepath.Join(t.TempDir(), "o.jsonl")
	if err := os.WriteFile(path, []byte(bad), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Load(path, "", 0); !errors.Is(err, runtime.ErrSchema) {
		t.Fatalf("err = %v, want ErrSchema", err)
	}
}

// ---- structural refusals --------------------------------------------------

// mutateOverlay rewrites the raw entry line of a one-entry overlay, so a test can
// inject exactly one defect without going through the writer (which would
// normalise it away).
func mutateOverlay(t *testing.T, from, to string) string {
	t.Helper()
	src := writeOverlay(t, baseMeta(), entry(0x00925050))
	raw, err := os.ReadFile(src)
	if err != nil {
		t.Fatal(err)
	}
	lines := strings.SplitN(string(raw), "\n", 3)
	if len(lines) < 2 {
		t.Fatalf("unexpected overlay shape: %q", raw)
	}
	if !strings.Contains(lines[1], from) {
		t.Fatalf("the mutation anchor %q is not in the entry line:\n%s", from, lines[1])
	}
	lines[1] = strings.Replace(lines[1], from, to, 1)
	path := filepath.Join(t.TempDir(), "o.jsonl")
	// The digest is recomputed so the injected defect is the ONLY problem: a test
	// that failed on the digest instead would prove nothing about the defect.
	body := lines[1] + "\n"
	sum := sha256.Sum256([]byte(body))
	lines[0] = strings.Replace(lines[0], `"content_sha256":"`+digestOf(src, t)+`"`, `"content_sha256":"`+hex.EncodeToString(sum[:])+`"`, 1)
	if err := os.WriteFile(path, []byte(strings.Join(lines, "\n")), 0o644); err != nil {
		t.Fatal(err)
	}
	return path
}

func digestOf(path string, t *testing.T) string {
	t.Helper()
	raw, err := os.ReadFile(path)
	if err != nil {
		t.Fatal(err)
	}
	lines := strings.Split(strings.TrimSpace(string(raw)), "\n")
	var m map[string]any
	if err := jsonUnmarshal([]byte(lines[0]), &m); err != nil {
		t.Fatal(err)
	}
	s, _ := m["content_sha256"].(string)
	return s
}

func TestDefectiveOverlaysAreRefused(t *testing.T) {
	cases := []struct {
		name     string
		from, to string
		want     string
	}{
		{
			name: "non-canonical VA spelling",
			from: `"requested_va":"0x00925050"`, to: `"requested_va":"925050"`,
			want: "canonical",
		},
		{
			name: "uppercase address prefix",
			from: `"requested_va":"0x00925050"`, to: `"requested_va":"0X00925050"`,
			want: "canonical",
		},
		{
			name: "negative entry_count",
			from: `"entry_count":null`, to: `"entry_count":-1`,
			want: "entry_count -1 is negative",
		},
		{
			name: "reached=false with a positive entry_count",
			from: `"reached":"null","entry_count":null`, to: `"reached":"false","entry_count":7`,
			want: "contradicts itself",
		},
		{
			name: "tri-state outside the vocabulary",
			from: `"reached":"null"`, to: `"reached":"maybe"`,
			want: "tri-state vocabulary",
		},
		{
			name: "canonicalization outside the closed vocabulary",
			from: `"canonicalization":"not_stated"`, to: `"canonicalization":"probably_a_function"`,
			want: "closed vocabulary",
		},
		{
			name: "canonical_va without a canonicalization",
			from: `"canonical_va":null,"canonicalization":"not_stated"`,
			to:   `"canonical_va":"0x00925000","canonicalization":"not_stated"`,
			want: "only \"function_entry\" and \"containing_function_entry\" may carry a canonical VA",
		},
		{
			name: "interior offset without the interior rule",
			from: `"canonicalization":"not_stated","canonical_offset":null`,
			to:   `"canonicalization":"not_stated","canonical_offset":4`,
			want: "canonical_offset is stated but canonicalization is",
		},
		{
			name: "no provenance",
			from: `"provenance":[{"source_class":"runtime","producer":"spore-recomp","artifact":"work/reports/synthetic.json"}]`,
			to:   `"provenance":[]`,
			want: "an assertion, not evidence",
		},
		{
			name: "provenance claiming a static source class",
			from: `"source_class":"runtime"`, to: `"source_class":"ghidra"`,
			want: "may only claim runtime provenance",
		},
		{
			name: "absolute filesystem path in provenance",
			from: `"artifact":"work/reports/synthetic.json"`, to: `"artifact":"/datos/spore_recomp/work/reports/x.json"`,
			want: "portable artifact identifiers",
		},
		{
			name: "unknown observation kind",
			from: `"observations":[]`, to: `"observations":[{"kind":"teleport","eip":null,"sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""}]`,
			want: "closed vocabulary",
		},
		{
			name: "observation kind missing its required field",
			from: `"observations":[]`, to: `"observations":[{"kind":"import","eip":null,"sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""}]`,
			want: `requires module`,
		},
		{
			name: "observation kind carrying a foreign field",
			from: `"observations":[]`, to: `"observations":[{"kind":"entry","eip":"0x00925050","sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""},{"kind":"register","eip":null,"sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""}]`,
			want: `requires register`,
		},
		{
			name: "duplicate observation",
			from: `"observations":[]`, to: `"observations":[{"kind":"entry","eip":"0x00925050","sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""},{"kind":"entry","eip":"0x00925050","sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""}]`,
			want: "duplicate",
		},
		{
			name: "non-canonical address inside an observation",
			from: `"observations":[]`, to: `"observations":[{"kind":"entry","eip":"00925050","sequence":null,"caller_function_va":null,"callsite_va":null,"target_va":null,"return_address":null,"indirect":"null","call_depth":null,"count":null,"register":null,"register_value":null,"return_register":null,"entry_esp":null,"return_esp":null,"stack_delta_bytes":null,"address":null,"access":"","width_bytes":null,"value":null,"module":null,"symbol":null,"slot_va":null,"exception_class":null,"detail":""}]`,
			want: "canonical",
		},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			path := mutateOverlay(t, tc.from, tc.to)
			_, err := runtime.Load(path, "", 0)
			if err == nil {
				t.Fatalf("the loader accepted a defective overlay")
			}
			if tc.want != "" && !strings.Contains(err.Error(), tc.want) {
				t.Fatalf("err = %v, want it to mention %q", err, tc.want)
			}
		})
	}
}

func TestUnsortedEntriesAreRefused(t *testing.T) {
	// Two entries, deliberately in descending order.
	path := filepath.Join(t.TempDir(), "o.jsonl")
	hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"producer":{"project":"p","name":"n","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":2,"reached":0,"reached_unknown":2,"not_reached":0,"total_entry_count":0,"runtime_only":2,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":1},"content_sha256":""}` + "\n"
	line := func(va string) string {
		return `{"record":"entry","requested_va":"` + va + `","canonical_va":null,"canonicalization":"not_stated","canonical_offset":null,"reached":"null","entry_count":null,"first_reached_from":null,"max_call_depth":null,"runtime_callers":[],"runtime_targets":[],"runtime_imports":[],"observations":[],"provenance":[{"source_class":"runtime","producer":"p","artifact":"a"}]}` + "\n"
	}
	if err := os.WriteFile(path, []byte(hdr+line("0x009250c0")+line("0x00925000")), 0o644); err != nil {
		t.Fatal(err)
	}
	_, err := runtime.Load(path, "", 0)
	if err == nil || !strings.Contains(err.Error(), "out of order") {
		t.Fatalf("err = %v, want an out-of-order refusal", err)
	}
}

func TestDuplicateRequestedVAIsRefused(t *testing.T) {
	path := filepath.Join(t.TempDir(), "o.jsonl")
	hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"producer":{"project":"p","name":"n","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":2,"reached":0,"reached_unknown":2,"not_reached":0,"total_entry_count":0,"runtime_only":2,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":1},"content_sha256":""}` + "\n"
	line := func(va string) string {
		return `{"record":"entry","requested_va":"` + va + `","canonical_va":null,"canonicalization":"not_stated","canonical_offset":null,"reached":"null","entry_count":null,"first_reached_from":null,"max_call_depth":null,"runtime_callers":[],"runtime_targets":[],"runtime_imports":[],"observations":[],"provenance":[{"source_class":"runtime","producer":"p","artifact":"a"}]}` + "\n"
	}
	if err := os.WriteFile(path, []byte(hdr+line("0x00925000")+line("0x00925000")), 0o644); err != nil {
		t.Fatal(err)
	}
	_, err := runtime.Load(path, "", 0)
	if err == nil || !strings.Contains(err.Error(), "duplicate requested_va") {
		t.Fatalf("err = %v, want a duplicate requested_va refusal", err)
	}
}

func TestTruncatedJSONIsRefused(t *testing.T) {
	src := writeOverlay(t, baseMeta(), entry(0x00401000))
	raw, err := os.ReadFile(src)
	if err != nil {
		t.Fatal(err)
	}
	truncated := raw[:len(raw)-40]
	path := filepath.Join(t.TempDir(), "o.jsonl")
	if err := os.WriteFile(path, truncated, 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Load(path, "", 0); err == nil {
		t.Fatalf("a truncated overlay was accepted")
	}
}

func TestHeaderOnlyOverlayIsRefusedWhenItClaimsEntries(t *testing.T) {
	// A producer that crashed after writing its header must not read as a run
	// that observed nothing.
	path := filepath.Join(t.TempDir(), "o.jsonl")
	hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"producer":{"project":"p","name":"n","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":9,"reached":0,"reached_unknown":0,"not_reached":0,"total_entry_count":0,"runtime_only":0,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":1},"content_sha256":""}` + "\n"
	if err := os.WriteFile(path, []byte(hdr), 0o644); err != nil {
		t.Fatal(err)
	}
	_, err := runtime.Load(path, "", 0)
	if err == nil || !strings.Contains(err.Error(), "the file carries none") {
		t.Fatalf("err = %v, want a header/body disagreement", err)
	}
}

func TestContentDigestMismatchIsRefused(t *testing.T) {
	src := writeOverlay(t, baseMeta(), entry(0x00401000))
	raw, _ := os.ReadFile(src)
	bad := strings.Replace(string(raw), digestOf(src, t), strings.Repeat("a", 64), 1)
	path := filepath.Join(t.TempDir(), "o.jsonl")
	if err := os.WriteFile(path, []byte(bad), 0o644); err != nil {
		t.Fatal(err)
	}
	_, err := runtime.Load(path, "", 0)
	if err == nil || !strings.Contains(err.Error(), "content_sha256") {
		t.Fatalf("err = %v, want a digest mismatch", err)
	}
}

func TestVerifyCatchesAHandEditedHeader(t *testing.T) {
	src := writeOverlay(t, baseMeta(), entry(0x00401000), entry(0x00401020))
	ov := mustLoad(t, src)
	if p := ov.Verify(); len(p) != 0 {
		t.Fatalf("fresh overlay reports %v", p)
	}
	// Recount the same body as if the producer had claimed fewer entries. The
	// digest still matches, so only the count cross-check can catch this.
	ov.Metadata.Counts.Entries = 99
	problems := ov.Verify()
	if len(problems) == 0 {
		t.Fatalf("Verify accepted a header whose counts disagree with its body")
	}
	if !strings.Contains(strings.Join(problems, " "), "counts.entries") {
		t.Fatalf("problems = %v, want a counts.entries complaint", problems)
	}
}

func TestMissingProducerIsRefused(t *testing.T) {
	path := filepath.Join(t.TempDir(), "o.jsonl")
	hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"producer":{"project":"","name":"","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":0,"reached":0,"reached_unknown":0,"not_reached":0,"total_entry_count":0,"runtime_only":0,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":0},"content_sha256":""}` + "\n"
	if err := os.WriteFile(path, []byte(hdr), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Load(path, "", 0); err == nil || !strings.Contains(err.Error(), "names no producer") {
		t.Fatalf("err = %v, want a missing-producer refusal", err)
	}
}

func TestTwoJSONValuesOnOneLineAreRefused(t *testing.T) {
	path := filepath.Join(t.TempDir(), "o.jsonl")
	hdr := `{"record":"metadata","schema":"` + runtime.OverlaySchema + `","binary":{"binary_sha256":"` + sporeSHA +
		`","image_base":"` + sporeImg + `"},"producer":{"project":"p","name":"n","version":"v","artifact":"a","source_schema":"s"},"counts":{"entries":1,"reached":0,"reached_unknown":1,"not_reached":0,"total_entry_count":0,"runtime_only":1,"runtime_callers":0,"runtime_targets":0,"runtime_imports":0,"observations":0,"exceptions":0,"distinct_producers":1},"content_sha256":""}` + "\n"
	line := `{"record":"entry","requested_va":"0x00401000","canonical_va":null,"canonicalization":"not_stated","canonical_offset":null,"reached":"null","entry_count":null,"first_reached_from":null,"max_call_depth":null,"runtime_callers":[],"runtime_targets":[],"runtime_imports":[],"observations":[],"provenance":[{"source_class":"runtime","producer":"p","artifact":"a"}]} {"record":"entry","requested_va":"0x00401020","canonical_va":null,"canonicalization":"not_stated","canonical_offset":null,"reached":"null","entry_count":null,"first_reached_from":null,"max_call_depth":null,"runtime_callers":[],"runtime_targets":[],"runtime_imports":[],"observations":[],"provenance":[{"source_class":"runtime","producer":"p","artifact":"a"}]}` + "\n"
	if err := os.WriteFile(path, []byte(hdr+line), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := runtime.Load(path, "", 0); err == nil || !strings.Contains(err.Error(), "more than one JSON value") {
		t.Fatalf("err = %v, want a one-record-per-line refusal", err)
	}
}

// ---- tri-state and absence semantics --------------------------------------

func TestNullIsDistinctFromFalseAndFromEmpty(t *testing.T) {
	// reached=null with no callers, versus reached=false with no callers. These
	// must stay distinguishable, because "the producer did not watch" and "the
	// producer watched and saw nothing" are different facts.
	notWatched := entry(0x00401000)
	notWatched.Reached = runtime.TriNull

	watched := entry(0x00401020)
	watched.Reached = runtime.TriFalse
	watched.EntryCount = runtime.Ptr(0)

	path := writeOverlay(t, baseMeta(), notWatched, watched)
	ov := mustLoad(t, path)
	if ov.Entries[0x00401000].Reached != runtime.TriNull {
		t.Fatalf("reached = %q, want \"null\"", ov.Entries[0x00401000].Reached)
	}
	if ov.Entries[0x00401020].Reached != runtime.TriFalse {
		t.Fatalf("reached = %q, want \"false\"", ov.Entries[0x00401020].Reached)
	}
	if ov.Entries[0x00401020].EntryCount == nil || *ov.Entries[0x00401020].EntryCount != 0 {
		t.Fatalf("an observed zero did not survive as 0: %v", ov.Entries[0x00401020].EntryCount)
	}
	counts := ov.Recount()
	if counts.ReachedUnknown != 1 || counts.NotReached != 1 || counts.Reached != 0 {
		t.Fatalf("recount collapsed the tri-state: %+v", counts)
	}
}

func TestNilListsBecomeEmptyArraysOnDisk(t *testing.T) {
	e := entry(0x00401000)
	e.RuntimeCallers = nil
	e.RuntimeTargets = nil
	e.RuntimeImports = nil
	e.Observations = nil
	path := writeOverlay(t, baseMeta(), e)
	raw, _ := os.ReadFile(path)
	for _, key := range []string{`"runtime_callers":[]`, `"runtime_targets":[]`, `"runtime_imports":[]`, `"observations":[]`} {
		if !strings.Contains(string(raw), key) {
			t.Fatalf("expected %s in the written line:\n%s", key, raw)
		}
	}
	if _, err := runtime.Load(path, "", 0); err != nil {
		t.Fatalf("an overlay with empty arrays was refused: %v", err)
	}
}

func TestNewEmptyOverlayIsUsableAndEmpty(t *testing.T) {
	ov := runtime.NewEmptyOverlay()
	if ov.Len() != 0 {
		t.Fatalf("Len = %d", ov.Len())
	}
	if ov.Has(0x00401000) {
		t.Fatalf("an empty overlay claims to know an address")
	}
	if ov.Summarize(0x00401000) != nil {
		t.Fatalf("Summarize on an empty overlay returned a summary")
	}
}

// ---- vocabulary guards ----------------------------------------------------

func TestClosedVocabularies(t *testing.T) {
	for _, k := range []string{"entry", "call", "indirect_call", "return", "import", "exception", "memory", "register", "stack"} {
		if !runtime.KnownObservationKind(runtime.ObservationKind(k)) {
			t.Fatalf("KnownObservationKind(%q) = false", k)
		}
	}
	for _, k := range []string{"teleport", "ENTRY", "", "Call"} {
		if runtime.KnownObservationKind(runtime.ObservationKind(k)) {
			t.Fatalf("KnownObservationKind(%q) = true", k)
		}
	}
	for _, c := range runtime.ResolutionClasses {
		if !runtime.KnownResolutionClass(c) {
			t.Fatalf("KnownResolutionClass(%q) = false", c)
		}
	}
	if runtime.KnownResolutionClass("resolved") {
		t.Fatalf("the vocabulary admitted an invented class")
	}
	for _, c := range []string{"function_entry", "containing_function_entry", "non_function_entity", "not_stated"} {
		if !runtime.KnownCanonicalization(c) {
			t.Fatalf("KnownCanonicalization(%q) = false", c)
		}
	}
	if runtime.KnownProvenanceSource("derived") {
		t.Fatalf("a static source_class was admitted into an overlay")
	}
}

func TestCanonicalAddrIsStrict(t *testing.T) {
	for _, good := range []string{"0x00401000", "0x00925050", "0x00000000", "0xffffffff"} {
		if _, err := runtime.CanonicalAddr(good); err != nil {
			t.Fatalf("CanonicalAddr(%q) = %v", good, err)
		}
	}
	for _, bad := range []string{"401000", "0x401000", "0X00401000", "0x004010000", "", " 0x00401000", "0x0040100g"} {
		if _, err := runtime.CanonicalAddr(bad); err == nil {
			t.Fatalf("CanonicalAddr(%q) accepted a non-canonical spelling", bad)
		}
	}
}
func jsonUnmarshal(b []byte, into any) error { return json.Unmarshal(b, into) }
