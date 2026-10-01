package semantic

import (
	"strings"
	"testing"
)

func TestParseAddrAcceptsEveryDocumentedSpelling(t *testing.T) {
	const base = DefaultImageBase
	cases := []struct {
		name  string
		input string
		want  Addr
	}{
		{"0x prefixed lowercase", "0x00925050", 0x00925050},
		{"0x prefixed uppercase digits", "0x00925050", 0x00925050},
		{"0x prefixed with letters", "0x00e3a400", 0x00e3a400},
		{"bare 8 hex lowercase", "00925050", 0x00925050},
		{"bare 8 hex uppercase", "00925050", 0x00925050},
		{"bare 8 hex with letters", "00e3a400", 0x00e3a400},
		{"bare short hex", "401000", 0x00401000},
		{"short 0x hex", "0x401000", 0x00401000},
		{"explicit decimal", "dec:9588816", 0x00925050},
		{"0d decimal prefix", "0d9588816", 0x00925050},
		{"explicit rva", "rva:00525050", 0x00925050},
		{"RVA uppercase prefix", "RVA:00525050", 0x00925050},
		{"surrounding space", "  0x00925050 ", 0x00925050},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			got, err := ParseAddr(c.input, base)
			if err != nil {
				t.Fatalf("ParseAddr(%q) returned error: %v", c.input, err)
			}
			if got != c.want {
				t.Fatalf("ParseAddr(%q) = %s, want %s", c.input, got, c.want)
			}
		})
	}
}

func TestParseAddrBareDigitsAreHexNotDecimal(t *testing.T) {
	// The trap this guards: reading bare digits as decimal makes
	// `lookup 925050` answer a different question (0x000e1f92) instead of
	// 0x00925050. Every committed OpenSpore artifact keys on bare 8-hex, so
	// bare means hex and decimal must be asked for explicitly.
	const base = DefaultImageBase
	got, err := ParseAddr("925050", base)
	if err != nil {
		t.Fatalf("ParseAddr: %v", err)
	}
	if got != 0x00925050 {
		t.Fatalf("ParseAddr(\"925050\") = %s, want 0x00925050", got)
	}
	// And the explicit decimal form reaches the same address, which is what
	// makes the two spellings checkable against each other.
	dec, err := ParseAddr("dec:9588816", base)
	if err != nil {
		t.Fatalf("ParseAddr: %v", err)
	}
	if dec != got {
		t.Fatalf("dec:9588816 = %s, want %s (same address as the hex form)", dec, got)
	}
}

func TestParseAddrRejectsBadInput(t *testing.T) {
	const base = DefaultImageBase
	cases := []struct {
		name  string
		input string
	}{
		{"empty", ""},
		{"prefix only", "0x"},
		{"embedded separator", "0x0040 1000"},
		{"non numeric", "0xzzzz"},
		{"beyond x86-32", "0x1ffffffff"},
		{"rva beyond x86-32", "rva:ffffffffff"},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			if _, err := ParseAddr(c.input, base); err == nil {
				t.Fatalf("ParseAddr(%q) accepted an invalid address", c.input)
			}
		})
	}
}

func TestParseBareAddrRefusesAnythingButCanonicalVA8(t *testing.T) {
	// This is the strictness tools/triage/export_datarefs.py insists on: a
	// canonical artifact whose keys sort differently under two spellings of one
	// address is a file that can disagree with itself.
	for _, bad := range []string{"0x00401000", "401000", "0040100G", "004010000", " 401000"} {
		if _, err := ParseBareAddr(bad); err == nil {
			t.Fatalf("ParseBareAddr(%q) accepted a non-canonical spelling", bad)
		}
	}
	got, err := ParseBareAddr("00401000")
	if err != nil {
		t.Fatalf("ParseBareAddr: %v", err)
	}
	if got != 0x00401000 {
		t.Fatalf("ParseBareAddr = %s, want 0x00401000", got)
	}
}

func TestAddressSpellingIsCanonicalEverywhere(t *testing.T) {
	a := Addr(0x00401000)
	if a.String() != "0x00401000" {
		t.Fatalf("String() = %q, want the canonical 0x%08x lowercase form", a.String(), uint32(a))
	}
	if a.Bare() != "00401000" {
		t.Fatalf("Bare() = %q, want bare 8-hex", a.Bare())
	}
	if BareAddr(uint32(a)) != a.Bare() {
		t.Fatalf("BareAddr and Bare disagree")
	}
}

func TestRVAAndImageBaseAreNotConfused(t *testing.T) {
	a := Addr(0x00925050)
	rva, ok := a.RVA(DefaultImageBase)
	if !ok {
		t.Fatalf("RVA reported failure for a VA above the image base")
	}
	if rva != 0x00525050 {
		t.Fatalf("RVA = %s, want 0x00525050", rva)
	}
	back, ok := AddrFromBase(rva, DefaultImageBase)
	if !ok || back != a {
		t.Fatalf("RVA round trip failed: %s -> %s", rva, back)
	}
	// A VA below the image base must be refused, not underflowed into a huge
	// RVA: that would let an RVA masquerade as a VA.
	if _, ok := Addr(0x00001000).RVA(DefaultImageBase); ok {
		t.Fatalf("RVA accepted a VA below the image base")
	}
	// The explicit RVA spelling and the explicit VA spelling must not collide:
	// rva:00525050 is 0x00925050, and there is no way to pass an RVA as a bare VA.
	if _, err := ParseAddr("rva:00525050", DefaultImageBase); err != nil {
		t.Fatalf("explicit rva spelling rejected: %v", err)
	}
}

func TestEnvelopeDistinguishesUnknownFromFalse(t *testing.T) {
	type block struct {
		Present TriBool `json:"present"`
	}
	unknown := Unavailable[block](ReasonNoEvidencePack)
	if unknown.IsAvailable() {
		t.Fatalf("an unavailable envelope reported itself available")
	}
	if unknown.State != StateUnavailable || unknown.EvidenceLevel != LevelUnknown || unknown.EvidenceState != EvidenceMissing {
		t.Fatalf("unavailable envelope lost its tri-state markers: %+v", unknown)
	}
	if unknown.Reason == "" {
		t.Fatalf("unavailable envelope carries no reason; an unexplained absence is indistinguishable from a bug")
	}
	if unknown.Value != nil {
		t.Fatalf("unavailable envelope carries a value")
	}

	known := Available(block{Present: TriFalse}, LevelObserved, EvidenceLive)
	if !known.IsAvailable() || known.Deref().Present != TriFalse {
		t.Fatalf("an available envelope holding a known-false was not available")
	}

	// A malformed envelope claiming to be available while omitting its value
	// must not be trusted: IsAvailable requires both.
	lying := Envelope[block]{State: StateAvailable, EvidenceLevel: LevelVerified}
	if lying.IsAvailable() {
		t.Fatalf("an envelope claiming state=available with no value was trusted")
	}
}

func TestTriBoolOfPreservesUnknown(t *testing.T) {
	if got := TriBoolOf(nil); got != TriNull {
		t.Fatalf("TriBoolOf(nil) = %q, want %q", got, TriNull)
	}
	if got := TriBoolOf(BoolPtr(true)); got != TriTrue {
		t.Fatalf("TriBoolOf(&true) = %q, want %q", got, TriTrue)
	}
	if got := TriBoolOf(BoolPtr(false)); got != TriFalse {
		t.Fatalf("TriBoolOf(&false) = %q, want %q", got, TriFalse)
	}
}

func TestMarshalLineIsStableAndUnescaped(t *testing.T) {
	type payload struct {
		Text string `json:"text"`
	}
	in := payload{Text: "a<b>c&d é"}
	first, err := MarshalLine(in)
	if err != nil {
		t.Fatalf("MarshalLine: %v", err)
	}
	if strings.Contains(string(first), `\u003c`) || strings.Contains(string(first), `\u0026`) {
		t.Fatalf("output was HTML-escaped; prose containing < > & would change bytes with the encoder default: %s", first)
	}
	if !strings.Contains(string(first), "a<b>c&d") {
		t.Fatalf("prose was mangled by the encoder: %s", first)
	}
	if !strings.HasSuffix(string(first), "\n") {
		t.Fatalf("record line is not newline-terminated, which the content digest depends on")
	}
	for i := 0; i < 50; i++ {
		again, err := MarshalLine(in)
		if err != nil {
			t.Fatalf("MarshalLine: %v", err)
		}
		if string(again) != string(first) {
			t.Fatalf("MarshalLine is not byte-stable across calls")
		}
	}
}

func TestKnownEvidenceLevelRejectsOffScaleValues(t *testing.T) {
	for _, s := range []string{"UNKNOWN", "APPROXIMATION", "INFERRED", "SUPPORTED", "OBSERVED", "CONFIRMED", "VERIFIED"} {
		if !KnownEvidenceLevel(s) {
			t.Fatalf("%q is on the shared scale but was rejected", s)
		}
	}
	// The scale the ABI tests document (PASS/SUPPORTED/WEAK/UNKNOWN) never
	// shipped; neither does NOT_AVAILABLE or REFUTED. They must not be accepted
	// as if they were rungs.
	for _, s := range []string{"PASS", "WEAK", "NOT_AVAILABLE", "REFUTED", "DERIVED", "", "inferred"} {
		if KnownEvidenceLevel(s) {
			t.Fatalf("%q is not on the shared scale but was accepted", s)
		}
	}
}
