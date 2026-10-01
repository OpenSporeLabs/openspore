// Package semantic defines the stable exchange types and the deterministic
// JSON encoding used by the OpenSpore semantic snapshot.
//
// Canonical address spelling is always "0x%08x" lowercase, byte-for-byte the
// same string that tools/reconstruction_knowledge.py::normalize_va produces.
// That function is the repository's canonical normalizer; this package is a
// transcription of it, not a second opinion about what a VA is.
package semantic

import (
	"fmt"
	"strconv"
	"strings"
)

// Addr is a 32-bit virtual address (x86:LE:32). It is stored as a number so
// that sorting, bisection and range tests are exact; it is rendered as a
// string only at the JSON boundary.
type Addr uint32

// String renders the canonical "0x%08x" lowercase spelling.
func (a Addr) String() string { return fmt.Sprintf("0x%08x", uint32(a)) }

// Bare renders the bare 8-char lowercase hex spelling used by the committed
// triage/xref/datarefs TSV and JSONL artifacts.
func (a Addr) Bare() string { return fmt.Sprintf("%08x", uint32(a)) }

// BareAddr renders a bare 8-char lowercase hex string from a raw number,
// matching the spelling used by functions.tsv, the triage JSONL and the xref
// TSV. It is the exact inverse of Addr.Bare.
func BareAddr(v uint32) string { return fmt.Sprintf("%08x", v) }

// ImageBase is the PE ImageBase of the analysed SporeApp.exe 3.1.0.22.
// It is declared here only so address arithmetic has one home; the value that
// actually reaches a snapshot comes from the OpenSpore binary manifest.
const DefaultImageBase Addr = 0x00400000

// RVA returns the relative virtual address, i.e. va - imageBase.
// The repository's rule (tools/triage/classify.py) asserts va >= imageBase
// before subtracting; RVA reports ok=false rather than underflowing.
func (a Addr) RVA(imageBase Addr) (rva Addr, ok bool) {
	if a < imageBase {
		return 0, false
	}
	return a - imageBase, true
}

// AddrFromBase converts a relative virtual address back to a VA. It is used
// only where a consumer supplies an RVA explicitly, never to guess.
func AddrFromBase(rva, imageBase Addr) (Addr, bool) {
	v := uint64(rva) + uint64(imageBase)
	if v > 0xFFFFFFFF {
		return 0, false
	}
	return Addr(v), true
}

// ParseAddrError describes a rejected address spelling.
type ParseAddrError struct {
	Input  string
	Reason string
}

func (e *ParseAddrError) Error() string {
	return fmt.Sprintf("invalid address %q: %s", e.Input, e.Reason)
}

// Address input prefixes that force a reading the bare spelling would not pick.
//
// Bare digits are always HEX. That is the repository's own convention -- every
// committed OpenSpore artifact keys on a bare 8-char lowercase hex VA8 -- and
// it is also the only reading under which "925050" and "00925050" cannot be
// confused. Reading bare digits as decimal instead would silently answer a
// different question: `lookup 925050` would resolve to 0x000e1f92 instead of
// 0x00925050. Decimal therefore requires an explicit prefix.
const (
	prefixDecimal  = "dec:"
	prefixDecimal0 = "0d"
)

// ParseAddr accepts every address spelling the CLI contract promises:
//
//	"0x00925050"  "0x925050"  "925050"  "00925050"   hex, any case, 0x optional
//	"dec:9584208"  "0d9584208"                      explicit decimal
//	"rva:00525050"                                   relative, image base added
//
// An explicit RVA is the only form that is offset, so an RVA is never quietly
// treated as a VA and a VA is never quietly treated as an RVA.
func ParseAddr(input string, imageBase Addr) (Addr, error) {
	text := strings.TrimSpace(input)
	if text == "" {
		return 0, &ParseAddrError{Input: input, Reason: "empty"}
	}

	base := 16
	isRVA := false
	if rest, ok := cutPrefixFold(text, "rva:"); ok {
		text = strings.TrimSpace(rest)
		isRVA = true
	}
	if rest, ok := cutPrefixFold(text, prefixDecimal); ok {
		text = strings.TrimSpace(rest)
		base = 10
	} else if rest, ok := cutPrefixFold(text, prefixDecimal0); ok {
		text = strings.TrimSpace(rest)
		base = 10
	} else if rest, ok := cutPrefixFold(text, "0x"); ok {
		text = strings.TrimSpace(rest)
	}
	if text == "" {
		return 0, &ParseAddrError{Input: input, Reason: "no digits after prefix"}
	}
	if strings.ContainsAny(text, " _-") {
		return 0, &ParseAddrError{Input: input, Reason: "embedded separator"}
	}

	v, err := strconv.ParseUint(text, base, 64)
	if err != nil {
		return 0, &ParseAddrError{Input: input, Reason: "not a number in base " + strconv.Itoa(base)}
	}
	if isRVA {
		if v > 0xFFFFFFFF {
			return 0, &ParseAddrError{Input: input, Reason: "rva outside x86-32 range"}
		}
		addr, ok := AddrFromBase(Addr(v), imageBase)
		if !ok {
			return 0, &ParseAddrError{Input: input, Reason: "rva + image base outside x86-32 range"}
		}
		return addr, nil
	}
	if v > 0xFFFFFFFF {
		return 0, &ParseAddrError{Input: input, Reason: "va outside x86-32 range"}
	}
	return Addr(v), nil
}

// ParseBareAddr reads the bare 8-char lowercase hex spelling that the
// committed OpenSpore artifacts use as their key. It refuses a "0x" prefix
// rather than folding it, for the reason tools/triage/export_datarefs.py
// gives: a canonical artifact whose keys sort differently under two spellings
// of one address is a file that can disagree with itself.
func ParseBareAddr(input string) (Addr, error) {
	text := strings.TrimSpace(input)
	if len(text) != 8 {
		return 0, &ParseAddrError{Input: input, Reason: "not 8 hex digits"}
	}
	for i := 0; i < len(text); i++ {
		c := text[i]
		if !(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') {
			return 0, &ParseAddrError{Input: input, Reason: "not 8 lowercase hex digits"}
		}
	}
	v, err := strconv.ParseUint(text, 16, 32)
	if err != nil {
		return 0, &ParseAddrError{Input: input, Reason: err.Error()}
	}
	return Addr(v), nil
}

// CutPrefixAddr trims a canonical "0x%08x" or bare "8hex" spelling down to
// its digits, for reading artifacts that use either form.
func CutPrefixAddr(input string) string {
	text := strings.TrimSpace(input)
	if rest, ok := cutPrefixFold(text, "0x"); ok {
		return strings.TrimSpace(rest)
	}
	return text
}

func cutPrefixFold(text, prefix string) (string, bool) {
	if len(text) < len(prefix) {
		return text, false
	}
	if !strings.EqualFold(text[:len(prefix)], prefix) {
		return text, false
	}
	return text[len(prefix):], true
}
