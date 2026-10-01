package snapshot

import (
	"errors"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/semantic"
)

func samplePassports() []*semantic.Passport {
	return samplePassportsAtBase(semantic.DefaultImageBase)
}

func samplePassportsAtBase(base semantic.Addr) []*semantic.Passport {
	mk := func(va uint32, size int, sdk string, promoted semantic.TriBool) *semantic.Passport {
		p := &semantic.Passport{
			Record: semantic.RecordFunction,
			Identity: semantic.IdentityBlock{
				CanonicalVA: semantic.Addr(va).String(),
				Size:        size,
				SizeKnown:   true,
				Section:     ".text",
			},
			Names:   semantic.NamesBlock{GhidraName: "FUN_" + semantic.Addr(va).Bare()},
			ABI:     semantic.Unavailable[semantic.ABIBlock](semantic.ReasonNoEvidencePack),
			VTable:  semantic.Unavailable[semantic.VTableBlock](semantic.ReasonNoVTableMembership),
			Globals: semantic.Unavailable[[]string](semantic.ReasonNoGlobalRefs),
			Types:   semantic.Unavailable[[]string](semantic.ReasonNoTypes),
			Semantics: semantic.Unavailable[semantic.SemanticsBlock](
				semantic.ReasonNoSemanticRecord),
			Reconstruction: semantic.Unavailable[semantic.ReconstructionBlock](
				semantic.ReasonNoReconstruction),
		}
		if rva, ok := semantic.Addr(va).RVA(base); ok {
			p.Identity.RVA = rva.String()
		}
		if sdk != "" {
			s := sdk
			p.Names.SDKName = &s
			p.Names.SDKNameSource = semantic.StrPtr("sdk_functions.tsv")
		}
		if promoted == semantic.TriTrue {
			p.Reconstruction = semantic.Available(semantic.ReconstructionBlock{
				Package:      semantic.StrPtr("PKG-TEST"),
				Promoted:     semantic.TriTrue,
				StaticStatus: semantic.StrPtr("PASS"),
			}, semantic.LevelConfirmed, semantic.EvidencePersisted, "reconstruction/evidence")
		}
		return p
	}
	return []*semantic.Passport{
		mk(0x00401000, 10, "", semantic.TriFalse),
		mk(0x00401010, 10, "Editors::IBakeManager::Get", semantic.TriFalse),
		mk(0x00401020, 10, "", semantic.TriTrue),
	}
}

func write(t *testing.T, passports []*semantic.Passport, counts semantic.Counts) (string, Result) {
	t.Helper()
	path := filepath.Join(t.TempDir(), semantic.SnapshotFile)
	res, err := Write(path, passports, counts, Options{
		Binary: semantic.BinaryIdentity{
			SHA256:    "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
			ImageBase: "0x00400000", Architecture: "x86:LE:32",
			Program: "SporeApp.exe", Version: "3.1.0.22",
		},
	})
	if err != nil {
		t.Fatalf("Write: %v", err)
	}
	return path, res
}

func TestWriteIsByteIdenticalOnRepeatedGeneration(t *testing.T) {
	passports := samplePassports()
	dir := t.TempDir()
	var prev []byte
	for i := 0; i < 5; i++ {
		path := filepath.Join(dir, "run"+string(rune('a'+i))+".jsonl")
		if _, err := Write(path, passports, semantic.Counts{Functions: 3}, Options{
			Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
		}); err != nil {
			t.Fatalf("Write: %v", err)
		}
		data, err := os.ReadFile(path)
		if err != nil {
			t.Fatalf("ReadFile: %v", err)
		}
		if prev != nil && string(data) != string(prev) {
			t.Fatalf("generation %d is not byte-identical to generation %d", i, i-1)
		}
		prev = data
	}
}

func TestWriteContainsNoTimestampOrAbsolutePath(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	passports := samplePassports()
	if _, err := Write(path, passports, semantic.Counts{Functions: 3}, Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	data, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	text := string(data)
	if strings.Contains(text, dir) {
		t.Fatalf("snapshot embeds the exporting machine's temp directory")
	}
	for _, banned := range []string{"generated_at", "timestamp", "/home/", "C:\\\\"} {
		if strings.Contains(text, banned) {
			t.Fatalf("snapshot contains volatile marker %q", banned)
		}
	}
}

func TestWriteOrdersRecordsByCanonicalVA(t *testing.T) {
	dir := t.TempDir()
	all := samplePassports()
	// Deliberately out of order on input.
	passports := []*semantic.Passport{all[2], all[0], all[1]}

	// Compute the counters from a first write/load round, then write again with
	// them, so Verify can check the header against the body it describes.
	probe := filepath.Join(dir, "probe.jsonl")
	if _, err := Write(probe, passports, semantic.Counts{Functions: 3}, Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	probeData, err := Load(probe, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}

	path := filepath.Join(dir, semantic.SnapshotFile)
	if _, err := Write(path, passports, probeData.Recount(), Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	data, err := Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	want := []uint32{0x00401000, 0x00401010, 0x00401020}
	if len(data.Order) != len(want) {
		t.Fatalf("loaded %d records, want %d", len(data.Order), len(want))
	}
	for i, va := range want {
		if data.Order[i] != va {
			t.Fatalf("record %d is 0x%08x, want 0x%08x", i, data.Order[i], va)
		}
	}
	if problems := data.Verify(); len(problems) != 0 {
		t.Fatalf("Verify reported problems on a freshly written snapshot: %v", problems)
	}
}

func TestLoadVerifiesContentDigest(t *testing.T) {
	path, _ := write(t, samplePassports(), semantic.Counts{Functions: 3})
	data, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	// Flip one byte inside a record's prose so the JSON still parses but the
	// digest no longer matches.
	tampered := strings.Replace(string(data), "Editors::IBakeManager::Get", "Editors::IBakeManager::GetX", 1)
	if tampered == string(data) {
		t.Fatalf("test could not find a byte to tamper with")
	}
	bad := filepath.Join(t.TempDir(), semantic.SnapshotFile)
	if err := os.WriteFile(bad, []byte(tampered), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	_, err = Load(bad, "")
	if !errors.Is(err, ErrCorrupt) {
		t.Fatalf("Load of a tampered snapshot returned %v, want ErrCorrupt", err)
	}
	if !strings.Contains(err.Error(), "content_sha256") {
		t.Fatalf("the corruption was not reported as a digest mismatch: %v", err)
	}
}

func TestLoadRejectsWrongBinarySHA(t *testing.T) {
	path, _ := write(t, samplePassports(), semantic.Counts{Functions: 3})
	_, err := Load(path, "1111111111111111111111111111111111111111111111111111111111111111")
	if !errors.Is(err, ErrBinaryMismatch) {
		t.Fatalf("Load with a wrong required digest returned %v, want ErrBinaryMismatch", err)
	}
	if !strings.Contains(err.Error(), "describes") || !strings.Contains(err.Error(), "requires") {
		t.Fatalf("the mismatch message does not name both digests: %v", err)
	}
	// The correct digest must load.
	if _, err := Load(path, "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"); err != nil {
		t.Fatalf("Load with the correct digest failed: %v", err)
	}
}

func TestLoadHonoursTheDeclaredImageBase(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	// A snapshot whose RVAs were derived against a base other than the Spore
	// default must still load, and must not be re-read against 0x00400000.
	passports := samplePassportsAtBase(0x00500000)
	for _, p := range passports {
		p.Identity.RVA = ""
	}
	if _, err := Write(path, passports, semantic.Counts{Functions: 3}, Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00500000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	data, err := Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	if got := data.Metadata.Binary.ImageBase; got != "0x00500000" {
		t.Fatalf("image base = %q, want the declared 0x00500000", got)
	}
	if got := data.ImageBase(); got != 0x00500000 {
		t.Fatalf("ImageBase() = %s, want 0x00500000", got)
	}
	// Every VA at or above the declared base must carry an RVA consistent with
	// that base, and a VA below it must carry none rather than underflow.
	const base = 0x00500000
	for addr, p := range data.Passports {
		want, ok := uint32(addr)-base, uint32(addr) >= base
		if ok {
			if p.Identity.RVA != semantic.Addr(want).String() {
				t.Fatalf("0x%08x has rva %q, want %s for base 0x%08x",
					addr, p.Identity.RVA, semantic.Addr(want).String(), base)
			}
		} else if p.Identity.RVA != "" {
			t.Fatalf("0x%08x is below the declared base yet carries rva %q", addr, p.Identity.RVA)
		}
	}
	// And a second load with no base requirement must give the same answer.
	again, err := Load(path, "")
	if err != nil {
		t.Fatalf("second Load: %v", err)
	}
	if again.ImageBase() != data.ImageBase() {
		t.Fatalf("repeated loads disagree on the image base")
	}
}

func TestLoadRejectsDuplicateCanonicalVA(t *testing.T) {
	path, _ := write(t, samplePassports(), semantic.Counts{Functions: 3})
	data, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	lines := strings.Split(strings.TrimRight(string(data), "\n"), "\n")
	dup := lines[2] // a duplicate of the second record
	lines = append(lines[:3], append([]string{dup}, lines[3:]...)...)
	out := filepath.Join(t.TempDir(), semantic.SnapshotFile)
	if err := os.WriteFile(out, []byte(strings.Join(lines, "\n")+"\n"), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	_, err = Load(out, "")
	if !errors.Is(err, ErrCorrupt) || !strings.Contains(err.Error(), "duplicate canonical VA") {
		t.Fatalf("Load of a snapshot with a duplicated VA returned %v, want a duplicate-VA corruption", err)
	}
}

func TestLoadRejectsUnsupportedSchema(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	header := `{"record":"metadata","schema":"spore-semantic-snapshot-99","binary":{"binary_sha256":"abc","image_base":"0x00400000"},"counts":{},"content_sha256":""}` + "\n"
	if err := os.WriteFile(path, []byte(header), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	_, err := Load(path, "")
	if !errors.Is(err, ErrSchema) {
		t.Fatalf("Load of an unknown schema returned %v, want ErrSchema", err)
	}
	if !strings.Contains(err.Error(), semantic.SnapshotSchema) {
		t.Fatalf("the schema error does not name the supported schema: %v", err)
	}
}

func TestLoadRejectsCorruptedJSON(t *testing.T) {
	cases := []struct {
		name string
		body string
	}{
		{"not json", "this is not json\n"},
		{"header only", `{"record":"metadata","schema":"spore-semantic-snapshot-1","binary":{"binary_sha256":"abc"}}
`},
		{"no binary identity", `{"record":"metadata","schema":"spore-semantic-snapshot-1","binary":{}}
{"record":"function"}
`},
		{"truncated record", `{"record":"metadata","schema":"spore-semantic-snapshot-1","binary":{"binary_sha256":"abc"}}
{"record":"function","identity":{"canonical_va":"0x00
`},
		{"first record is not metadata", `{"record":"function"}
`},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), semantic.SnapshotFile)
			if err := os.WriteFile(path, []byte(c.body), 0o644); err != nil {
				t.Fatalf("WriteFile: %v", err)
			}
			_, err := Load(path, "")
			if err == nil {
				t.Fatalf("Load accepted a %s snapshot", c.name)
			}
			if !errors.Is(err, ErrCorrupt) && !errors.Is(err, ErrSchema) {
				t.Fatalf("Load returned %v, want ErrCorrupt or ErrSchema", err)
			}
		})
	}
}

func TestLoadMissingFileIsReportedNotEmpty(t *testing.T) {
	_, err := Load(filepath.Join(t.TempDir(), "nope.jsonl"), "")
	if !errors.Is(err, ErrMissing) {
		t.Fatalf("Load of a missing file returned %v, want ErrMissing", err)
	}
}

func TestVerifyDetectsAHeaderEditedToMatchNothing(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	passports := samplePassports()
	counts := semantic.Counts{Functions: 3, WithSDKName: 1}
	if _, err := Write(path, passports, counts, Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	// Claim a coverage count the body cannot support. The content digest is
	// left intact, so Verify -- not the digest -- is what has to catch it: that
	// is the case a digest alone cannot see.
	data, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	text := strings.Replace(string(data), `"with_sdk_name":1`, `"with_sdk_name":99`, 1)
	if text == string(data) {
		t.Fatalf("test could not find the count to edit")
	}
	if err := os.WriteFile(path, []byte(text), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	loaded, err := Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	problems := loaded.Verify()
	found := false
	for _, p := range problems {
		if strings.Contains(p, "with_sdk_name") {
			found = true
		}
	}
	if !found {
		t.Fatalf("Verify did not catch a header claiming %s", "with_sdk_name: 99 against a body holding 1")
	}
}

func TestRecountMatchesTheBody(t *testing.T) {
	path, _ := write(t, samplePassports(), semantic.Counts{Functions: 3})
	data, err := Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	counts := data.Recount()
	if counts.Functions != 3 {
		t.Fatalf("Recount.Functions = %d, want 3", counts.Functions)
	}
	if counts.WithSDKName != 1 {
		t.Fatalf("Recount.WithSDKName = %d, want 1", counts.WithSDKName)
	}
	if counts.WithPromoted != 1 {
		t.Fatalf("Recount.WithPromoted = %d, want 1", counts.WithPromoted)
	}
	if counts.TotalFactGroups != 3*factGroupsPerPassport {
		t.Fatalf("Recount.TotalFactGroups = %d, want %d", counts.TotalFactGroups, 3*factGroupsPerPassport)
	}
}
