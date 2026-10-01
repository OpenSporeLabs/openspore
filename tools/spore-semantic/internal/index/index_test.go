package index

import (
	"os"
	"path/filepath"
	"testing"

	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/snapshot"
)

// build writes a small snapshot and returns an index over it.
func build(t *testing.T, passports []*semantic.Passport) (*Index, *snapshot.Data) {
	t.Helper()
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	if _, err := snapshot.Write(path, passports, semantic.Counts{Functions: len(passports)}, snapshot.Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	data, err := snapshot.Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	return New(data), data
}

func mk(va uint32, size int, names ...string) *semantic.Passport {
	p := &semantic.Passport{
		Record: semantic.RecordFunction,
		Identity: semantic.IdentityBlock{
			CanonicalVA: semantic.Addr(va).String(),
			Size:        size,
			SizeKnown:   true,
			Section:     ".text",
		},
		ABI:            semantic.Unavailable[semantic.ABIBlock](semantic.ReasonNoEvidencePack),
		VTable:         semantic.Unavailable[semantic.VTableBlock](semantic.ReasonNoVTableMembership),
		Globals:        semantic.Unavailable[[]string](semantic.ReasonNoGlobalRefs),
		Types:          semantic.Unavailable[[]string](semantic.ReasonNoTypes),
		Semantics:      semantic.Unavailable[semantic.SemanticsBlock](semantic.ReasonNoSemanticRecord),
		Reconstruction: semantic.Unavailable[semantic.ReconstructionBlock](semantic.ReasonNoReconstruction),
	}
	if len(names) > 0 {
		p.Names.GhidraName = names[0]
	}
	if len(names) > 1 {
		s := names[1]
		p.Names.NormalizedSymbol = &s
	}
	return p
}

func sample() []*semantic.Passport {
	return []*semantic.Passport{
		mk(0x00401000, 0x20, "FUN_00401000"),
		mk(0x00401020, 0x10, "FUN_00401020"),
		// A gap of 0x00401030..0x004010ff between two bodies.
		mk(0x00401100, 0x10, "FUN_00401100"),
		// Two functions sharing one name: the repository's own notes record
		// duplicate normalized-name groups, which is why the VA is the key.
		mk(0x00401200, 0x10, "FUN_dupe", "fun_dupe"),
		mk(0x00401300, 0x10, "FUN_dupe", "fun_dupe"),
		// One carrying both an SDK name and a different normalized symbol.
		mk(0x00402000, 0x40, "Editors::IBakeManager::Get", "bake_manager_get"),
	}
}

func TestResolveExactVA(t *testing.T) {
	ix, _ := build(t, sample())
	for _, va := range []uint32{0x00401000, 0x00401020, 0x00401100, 0x00402000} {
		res := ix.Resolve(semantic.Addr(va))
		if res.Kind != KindExact {
			t.Fatalf("0x%08x resolved as %q, want function_entry", va, res.Kind)
		}
		if res.Passport == nil || res.Passport.Identity.CanonicalVA != semantic.Addr(va).String() {
			t.Fatalf("0x%08x resolved to the wrong passport", va)
		}
		if res.Requested != semantic.Addr(va) {
			t.Fatalf("requested VA was not echoed: %s", res.Requested)
		}
	}
}

func TestResolveInteriorVACanonicalizes(t *testing.T) {
	ix, _ := build(t, sample())
	res := ix.Resolve(0x00401010)
	if res.Kind != KindInterior {
		t.Fatalf("interior 0x00401010 resolved as %q, want containing_function_entry", res.Kind)
	}
	if res.Passport.Identity.CanonicalVA != "0x00401000" {
		t.Fatalf("interior VA resolved to %s, want 0x00401000", res.Passport.Identity.CanonicalVA)
	}
	if res.Offset != 0x10 {
		t.Fatalf("offset = %d, want 16", res.Offset)
	}
	if res.End != 0x00401020 {
		t.Fatalf("range end = %s, want the exclusive body end 0x00401020", res.End)
	}
	// The last byte of a body is inside it.
	if res := ix.Resolve(0x0040101f); res.Kind != KindInterior || res.Passport.Identity.CanonicalVA != "0x00401000" {
		t.Fatalf("the last byte of a body resolved as %q", res.Kind)
	}
}

func TestResolveDoesNotInventAnIdentityForPadding(t *testing.T) {
	ix, _ := build(t, sample())
	// Between 0x00401030 (one past the first body's end) and 0x00401100.
	for _, va := range []uint32{0x00401030, 0x00401050, 0x004010ff} {
		res := ix.Resolve(semantic.Addr(va))
		if res.Kind != KindUnknown || res.Passport != nil {
			t.Fatalf("padding address 0x%08x resolved as %q; the rule must leave it alone", va, res.Kind)
		}
	}
	// Below the first entry, and far outside the image.
	for _, va := range []uint32{0x00000010, 0x7fff0000} {
		if res := ix.Resolve(semantic.Addr(va)); res.Passport != nil {
			t.Fatalf("out-of-range address 0x%08x resolved to a passport", va)
		}
	}
}

func TestResolveIsConsistentAcrossRepeatedIndexBuilds(t *testing.T) {
	passports := sample()
	ixA, _ := build(t, passports)
	ixB, _ := build(t, passports)
	for va := uint32(0x00401000); va < 0x00401120; va++ {
		a := ixA.Resolve(semantic.Addr(va))
		b := ixB.Resolve(semantic.Addr(va))
		if a.Kind != b.Kind || a.Offset != b.Offset {
			t.Fatalf("0x%08x resolved differently across builds: %+v vs %+v", va, a, b)
		}
		if (a.Passport == nil) != (b.Passport == nil) {
			t.Fatalf("0x%08x produced a passport in one build and not the other", va)
		}
	}
}

func TestLookupSymbolFindsEachNameSpace(t *testing.T) {
	ix, _ := build(t, sample())
	if got := ix.LookupSymbol("FUN_00401000"); len(got) != 1 {
		t.Fatalf("ghidra-name lookup returned %d matches, want 1", len(got))
	}
	if got := ix.LookupSymbol("bake_manager_get"); len(got) != 1 {
		t.Fatalf("normalized-symbol lookup returned %d matches, want 1", len(got))
	}
	if got := ix.LookupSymbol("fun_dupe"); len(got) != 2 {
		t.Fatalf("duplicate-symbol lookup returned %d matches, want 2", len(got))
	}
	if got := ix.LookupSymbol("FUN_DUPE"); len(got) != 2 {
		t.Fatalf("symbol lookup is case-sensitive; want 2 case-insensitive matches")
	}
	if got := ix.LookupSymbol("  FUN_00401000  "); len(got) != 1 {
		t.Fatalf("symbol lookup did not trim whitespace")
	}
	if got := ix.LookupSymbol("no_such_symbol"); len(got) != 0 {
		t.Fatalf("a missing symbol returned %d matches, want none", len(got))
	}
}

func TestSymbolIndexDoesNotDoubleCountOneNameInOneRecord(t *testing.T) {
	// Most functions carry the same string as normalized_symbol and
	// ghidra_name. Indexing it twice would make every such lookup look
	// ambiguous, which is the difference between "ambiguous" and "wrong".
	ix, _ := build(t, sample())
	if got := ix.LookupSymbol("FUN_00401020"); len(got) != 1 {
		t.Fatalf("a name that appears twice in one record produced %d matches, want 1", len(got))
	}
	if ix.AmbiguousNameCount() != 1 {
		t.Fatalf("AmbiguousNameCount = %d, want 1 (only fun_dupe)", ix.AmbiguousNameCount())
	}
}

func TestDuplicateSymbolMatchesAreOrderedByCanonicalVA(t *testing.T) {
	ix, _ := build(t, sample())
	got := ix.LookupSymbol("fun_dupe")
	if len(got) != 2 {
		t.Fatalf("got %d matches, want 2", len(got))
	}
	first, err := semantic.ParseAddr(got[0].Passport.Identity.CanonicalVA, 0)
	if err != nil {
		t.Fatalf("ParseAddr: %v", err)
	}
	second, err := semantic.ParseAddr(got[1].Passport.Identity.CanonicalVA, 0)
	if err != nil {
		t.Fatalf("ParseAddr: %v", err)
	}
	if first >= second {
		t.Fatalf("ambiguous matches are not ordered by canonical VA: %s then %s", first, second)
	}
}

func TestIndexReadsTheDeclaredImageBase(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	if _, err := snapshot.Write(path, sample(), semantic.Counts{Functions: 6}, snapshot.Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x500000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	data, err := snapshot.Load(path, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	if got := New(data).ImageBase(); got != 0x00500000 {
		t.Fatalf("ImageBase() = %s, want the snapshot's declared 0x00500000, not the built-in default", got)
	}
}

func TestIndexDoesNotResolveWhenNoSizesAreKnown(t *testing.T) {
	// Without a stated body size there is no containment test to run, and the
	// rule must not guess one.
	passports := sample()
	for _, p := range passports {
		p.Identity.SizeKnown = false
		p.Identity.Size = 0
	}
	ix, _ := build(t, passports)
	if res := ix.Resolve(0x00401010); res.Passport != nil {
		t.Fatalf("an interior address resolved although no body size is known")
	}
	if res := ix.Resolve(0x00401000); res.Kind != KindExact {
		t.Fatalf("an exact entry failed to resolve: %q", res.Kind)
	}
}

func TestLoadRejectsASnapshotWhoseRecordsAreNotSorted(t *testing.T) {
	// The loader tolerates it; Verify is what reports it. Both behaviours are
	// asserted so neither can change silently.
	dir := t.TempDir()
	path := filepath.Join(dir, semantic.SnapshotFile)
	passports := sample()
	if _, err := snapshot.Write(path, passports, semantic.Counts{Functions: 6}, snapshot.Options{
		Binary: semantic.BinaryIdentity{SHA256: "abc", ImageBase: "0x00400000"},
	}); err != nil {
		t.Fatalf("Write: %v", err)
	}
	raw, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("ReadFile: %v", err)
	}
	lines := splitLines(string(raw))
	if len(lines) < 4 {
		t.Fatalf("fixture snapshot is too small to reorder")
	}
	lines[1], lines[2] = lines[2], lines[1]
	out := filepath.Join(t.TempDir(), semantic.SnapshotFile)
	// Rewriting the body changes the content digest, so recompute it by
	// writing through snapshot.Write with the reordered slice is not possible
	// (Write sorts). Blank the digest so the ordering check is what fires.
	lines[0] = blankDigest(lines[0])
	if err := os.WriteFile(out, []byte(joinLines(lines)), 0o644); err != nil {
		t.Fatalf("WriteFile: %v", err)
	}
	data, err := snapshot.Load(out, "")
	if err != nil {
		t.Fatalf("Load: %v", err)
	}
	found := false
	for _, p := range data.Verify() {
		if p == "records are not sorted ascending by identity.canonical_va" {
			found = true
		}
	}
	if !found {
		t.Fatalf("Verify did not report the out-of-order records: %v", data.Verify())
	}
}

func blankDigest(header string) string {
	const key = `"content_sha256":"`
	i := indexOf(header, key)
	if i < 0 {
		return header
	}
	j := indexOf(header[i+len(key):], `"`)
	if j < 0 {
		return header
	}
	return header[:i+len(key)] + header[i+len(key)+j:]
}

func splitLines(s string) []string {
	var out []string
	start := 0
	for i := 0; i < len(s); i++ {
		if s[i] == '\n' {
			if i > start {
				out = append(out, s[start:i])
			}
			start = i + 1
		}
	}
	return out
}

func joinLines(in []string) string {
	var out string
	for _, l := range in {
		out += l + "\n"
	}
	return out
}

func indexOf(s, sub string) int {
	for i := 0; i+len(sub) <= len(s); i++ {
		if s[i:i+len(sub)] == sub {
			return i
		}
	}
	return -1
}
