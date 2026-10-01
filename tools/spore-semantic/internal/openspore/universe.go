package openspore

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

// Entry is one row of the pinned function universe.
type Entry struct {
	Addr  uint32
	Name  string
	Size  int
	Known bool // Size was stated by the artifact
	Thunk bool
	// Section is the PE section the entry lives in, e.g. ".text".
	Section string
}

// Universe is the authoritative set of function entries, sorted ascending by
// address and suitable for bisection.
//
// It comes from .spore-analysis/ghidra-exports/functions.tsv -- the frozen
// Ghidra export that tools/triage/classify.py, tools/triage/export_xrefs.py,
// tools/triage/export_datarefs.py and tools/reconstruction_knowledge.py all
// read as the function-entry universe, each asserting the same 58,757-row
// count. When that git-ignored export is not present (a consumer's checkout,
// or an export run elsewhere), the git-tracked coverage ledger is used
// instead: knowledgegraph/research/21-decompilation-coverage.json carries
// ledger[].va and ledger[].function_body_size_bytes for the same universe.
// The fallback loses names, which the triage JSONL supplies anyway.
type Universe struct {
	Entries  []Entry
	Source   string // repo-relative path actually used
	Fallback bool
}

const universeHeader = "address\tname\tsize\tis_thunk\tis_external\tsection"

// LoadUniverse reads the pinned function-entry universe.
func LoadUniverse(root string) (*Universe, []Absent, error) {
	primary := root + "/" + RelUniverse
	if FileExists(primary) {
		entries, err := loadFunctionsTSV(primary)
		if err != nil {
			return nil, nil, err
		}
		return &Universe{Entries: entries, Source: RelUniverse}, nil, nil
	}

	alt := root + "/" + RelUniverseAlt
	if FileExists(alt) {
		entries, err := loadCoverageLedger(alt)
		if err != nil {
			return nil, nil, err
		}
		return &Universe{Entries: entries, Source: RelUniverseAlt, Fallback: true}, []Absent{{
			Path:   RelUniverse,
			Reason: "the frozen Ghidra functions.tsv export is absent from this checkout (it is git-ignored); fell back to the git-tracked coverage ledger for canonical identity and body sizes",
		}}, nil
	}

	return nil, []Absent{{
		Path:   RelUniverse,
		Reason: "not present: the frozen Ghidra functions.tsv export is git-ignored and knowledgegraph/research/21-decompilation-coverage.json is also missing",
	}, {
		Path:   RelUniverseAlt,
		Reason: "not present: the git-tracked coverage ledger that carries va and function_body_size_bytes is missing",
	}}, ErrUniverseUnavailable
}

// ErrUniverseUnavailable is returned when neither universe source is present.
// The export refuses to run rather than minting passports for a guessed
// universe, because an empty universe would make every address a non-entry.
var ErrUniverseUnavailable = fmt.Errorf("function universe unavailable")

func loadFunctionsTSV(path string) ([]Entry, error) {
	f, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<20)

	if !sc.Scan() {
		return nil, fmt.Errorf("%s: empty file", path)
	}
	if got := strings.TrimRight(sc.Text(), "\r\n"); got != universeHeader {
		return nil, fmt.Errorf("%s: header is %q, expected the frozen %q", path, got, universeHeader)
	}

	var entries []Entry
	seen := make(map[uint32]struct{})
	for line := 2; sc.Scan(); line++ {
		text := strings.TrimRight(sc.Text(), "\r\n")
		if text == "" {
			continue
		}
		cols := strings.Split(text, "\t")
		if len(cols) != 6 {
			return nil, fmt.Errorf("%s:%d: expected 6 columns, got %d", path, line, len(cols))
		}
		addr, err := parseBareAddr(cols[0])
		if err != nil {
			return nil, fmt.Errorf("%s:%d: %w", path, line, err)
		}
		if _, dup := seen[addr]; dup {
			return nil, fmt.Errorf("%s:%d: duplicate canonical VA %08x", path, line, addr)
		}
		seen[addr] = struct{}{}

		size, err := strconv.Atoi(cols[2])
		if err != nil {
			return nil, fmt.Errorf("%s:%d: size %q is not a decimal integer", path, line, cols[2])
		}
		entries = append(entries, Entry{
			Addr:    addr,
			Name:    cols[1],
			Size:    size,
			Known:   true,
			Thunk:   cols[3] == "true",
			Section: cols[5],
		})
	}
	if err := sc.Err(); err != nil {
		return nil, err
	}
	sort.Slice(entries, func(i, j int) bool { return entries[i].Addr < entries[j].Addr })
	return entries, nil
}

// coverageLedger is the slice of 21-decompilation-coverage.json this reader
// needs. Decoding the whole 49 MB document is avoided by streaming only the
// ledger entries, but the file is a single JSON object so it is read whole; the
// struct keeps the payload small.
type coverageLedger struct {
	Ledger []struct {
		VA   string `json:"va"`
		Size *int   `json:"function_body_size_bytes"`
	} `json:"ledger"`
}

func loadCoverageLedger(path string) ([]Entry, error) {
	raw, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	var doc coverageLedger
	if err := json.Unmarshal(raw, &doc); err != nil {
		return nil, fmt.Errorf("%s: %w", path, err)
	}
	if len(doc.Ledger) == 0 {
		return nil, fmt.Errorf("%s: ledger[] is empty", path)
	}
	entries := make([]Entry, 0, len(doc.Ledger))
	seen := make(map[uint32]struct{}, len(doc.Ledger))
	for i, row := range doc.Ledger {
		addr, err := parseBareAddr(row.VA)
		if err != nil {
			return nil, fmt.Errorf("%s: ledger[%d]: %w", path, i, err)
		}
		if _, dup := seen[addr]; dup {
			return nil, fmt.Errorf("%s: ledger[%d]: duplicate canonical VA %08x", path, i, addr)
		}
		seen[addr] = struct{}{}
		e := Entry{Addr: addr, Section: ".text"}
		if row.Size != nil && *row.Size > 0 {
			e.Size = *row.Size
			e.Known = true
		}
		entries = append(entries, e)
	}
	sort.Slice(entries, func(i, j int) bool { return entries[i].Addr < entries[j].Addr })
	return entries, nil
}

func parseBareAddr(text string) (uint32, error) {
	t := strings.TrimSpace(text)
	if len(t) != 8 {
		return 0, fmt.Errorf("not a canonical 8-lowercase-hex VA8: %q", text)
	}
	v, err := strconv.ParseUint(t, 16, 32)
	if err != nil {
		return 0, fmt.Errorf("not a canonical 8-lowercase-hex VA8: %q", text)
	}
	return uint32(v), nil
}
