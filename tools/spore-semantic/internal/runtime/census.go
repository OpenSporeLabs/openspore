package runtime

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"errors"
	"fmt"
	"os"
)

// Census load errors. Distinct from the overlay errors because the census is an
// OpenSpore-side artifact: a bad census is a repository problem, not a foreign
// producer's.
var (
	// ErrCensusMissing means no census file was found.
	ErrCensusMissing = errors.New("blocker census not found")
	// ErrCensusSchema means the census declares a schema this build does not
	// implement.
	ErrCensusSchema = errors.New("unsupported blocker census schema")
	// ErrCensusCorrupt means the census is unreadable or internally
	// inconsistent -- duplicate targets, unsorted targets, or a target with no
	// address.
	ErrCensusCorrupt = errors.New("corrupted blocker census")
)

// LoadCensus reads and validates a blocker census.
//
// The census is trusted less than it looks: it is generated, it can be stale, and
// a stale census intersecting a runtime overlay produces a confident wrong
// answer. So it carries its source artifact's digest, it must be sorted and
// duplicate-free, and every target must name a canonical address.
func LoadCensus(path string, requireSHA string) (*Census, error) {
	raw, err := os.ReadFile(path)
	if err != nil {
		if os.IsNotExist(err) {
			return nil, fmt.Errorf("%w: %s", ErrCensusMissing, path)
		}
		return nil, err
	}
	dec := json.NewDecoder(bytesReader(raw))
	dec.DisallowUnknownFields()
	var doc Census
	if err := dec.Decode(&doc); err != nil {
		if isUnknownField(err) {
			return nil, fmt.Errorf("%w: %s: %v", ErrCensusSchema, path, err)
		}
		return nil, fmt.Errorf("%w: %s: %v", ErrCensusCorrupt, path, err)
	}
	if doc.Schema != CensusSchema {
		return nil, fmt.Errorf("%w: %s declares %q, this build implements %q", ErrCensusSchema, path, doc.Schema, CensusSchema)
	}
	if doc.Binary.SHA256 == "" {
		return nil, fmt.Errorf("%w: %s: census states no binary_sha256", ErrCensusCorrupt, path)
	}
	if requireSHA != "" && doc.Binary.SHA256 != requireSHA {
		return nil, fmt.Errorf("%w: census describes %s, caller requires %s", ErrBinaryMismatch, shortSHA(doc.Binary.SHA256), shortSHA(requireSHA))
	}
	if doc.Source.Index == "" || doc.Source.IndexSHA256 == "" {
		return nil, fmt.Errorf("%w: %s: census names no source artifact digest, so its staleness is unknowable", ErrCensusCorrupt, path)
	}
	prev := uint32(0)
	for i := range doc.Targets {
		t := &doc.Targets[i]
		addr, err := canonicalAddr(t.VA)
		if err != nil {
			return nil, fmt.Errorf("%w: %s: targets[%d].va %q: %v", ErrCensusCorrupt, path, i, t.VA, err)
		}
		if uint32(addr) <= prev && i > 0 {
			reason := "out of order"
			if uint32(addr) == prev {
				reason = "duplicate va"
			}
			return nil, fmt.Errorf("%w: %s: targets[%d] %s; targets must be sorted ascending and unique", ErrCensusCorrupt, path, i, reason)
		}
		prev = uint32(addr)
	}
	if doc.Targets == nil {
		doc.Targets = []CensusTarget{}
	}
	return &doc, nil
}

// WriteCensus serialises a census deterministically: targets sorted by VA, no
// timestamps, no absolute paths.
//
// content_sha256 is computed over the canonical COMPACT encoding of the target
// array, so it is a function of the census content alone and not of the
// indentation used to write the file. That way a reader can verify it without
// having to reproduce the pretty-printer.
func WriteCensus(path string, doc Census) (string, error) {
	sortCensus(doc.Targets)
	if doc.Targets == nil {
		doc.Targets = []CensusTarget{}
	}
	canonical, err := json.Marshal(doc.Targets)
	if err != nil {
		return "", err
	}
	sum := sha256.Sum256(canonical)
	doc.ContentSHA256 = hex.EncodeToString(sum[:])

	raw, err := json.MarshalIndent(doc, "", "  ")
	if err != nil {
		return "", err
	}
	raw = append(raw, '\n')
	if err := os.MkdirAll(dirOf(path), 0o755); err != nil {
		return "", err
	}
	return doc.ContentSHA256, os.WriteFile(path, raw, 0o644)
}

// VerifyCensus recomputes the census content digest and reports a mismatch.
func VerifyCensus(doc *Census) []string {
	var problems []string
	if doc.ContentSHA256 == "" {
		problems = append(problems, "content_sha256 is empty; the census cannot be tied to its content")
		return problems
	}
	sortCensus(doc.Targets)
	if doc.Targets == nil {
		doc.Targets = []CensusTarget{}
	}
	canonical, err := json.Marshal(doc.Targets)
	if err != nil {
		return []string{"targets cannot be canonicalised: " + err.Error()}
	}
	sum := sha256.Sum256(canonical)
	got := hex.EncodeToString(sum[:])
	if got != doc.ContentSHA256 {
		problems = append(problems, fmt.Sprintf("content_sha256 is %s, recomputed %s over %d targets", doc.ContentSHA256, got, len(doc.Targets)))
	}
	return problems
}
