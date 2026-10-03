package runtime

import (
	"bufio"
	"bytes"
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// Result reports what a write produced.
type Result struct {
	Path       string
	Bytes      int64
	Entries    int
	ContentSHA string
}

// Normalize makes one entry canonical before it is written.
//
// It does three things, all of them about determinism rather than meaning:
//
//   - a nil list becomes an empty array, so "observed none" is [] on disk and
//     never null, and two producers that agree about emptiness agree bytewise;
//   - every list is sorted into the total order the loader validates, so the
//     writer cannot emit a file its own loader would refuse;
//   - absent optional fields stay absent, so an unavailable fact never becomes a
//     zero value.
//
// It deliberately does NOT canonicalize addresses. requested_va is reproduced
// verbatim: an overlay that rewrote the producer's address into OpenSpore's idea
// of the right one would be doing identity work, and identity is not this
// package's to do.
func Normalize(e *Entry) {
	if e.RuntimeCallers == nil {
		e.RuntimeCallers = []RuntimeCaller{}
	}
	if e.RuntimeTargets == nil {
		e.RuntimeTargets = []RuntimeTarget{}
	}
	if e.RuntimeImports == nil {
		e.RuntimeImports = []RuntimeImportRef{}
	}
	if e.Observations == nil {
		e.Observations = []Observation{}
	}
	if e.Provenance == nil {
		e.Provenance = []ProvenanceEntry{}
	}
	if e.Canonicalization == "" {
		e.Canonicalization = CanonicalUnknown
	}
	// Every tri-state is written in its explicit form, so "null" is on disk
	// rather than being an absent field. An absent tri-state and a "null"
	// tri-state mean the same thing, but only one of them is greppable, and a
	// validator that has to guess which was meant is a validator that can be
	// fooled.
	e.Reached = triState(e.Reached)
	for i := range e.RuntimeTargets {
		e.RuntimeTargets[i].Indirect = triState(e.RuntimeTargets[i].Indirect)
		e.RuntimeTargets[i].Unresolved = triState(e.RuntimeTargets[i].Unresolved)
	}
	for i := range e.RuntimeImports {
		e.RuntimeImports[i].Bound = triState(e.RuntimeImports[i].Bound)
	}
	for i := range e.Observations {
		e.Observations[i].Indirect = triState(e.Observations[i].Indirect)
	}

	sort.SliceStable(e.RuntimeCallers, func(i, j int) bool {
		a, b := e.RuntimeCallers[i], e.RuntimeCallers[j]
		if a.CallsiteVA != b.CallsiteVA {
			return a.CallsiteVA < b.CallsiteVA
		}
		return derefStr(a.CallerFunctionVA) < derefStr(b.CallerFunctionVA)
	})
	e.RuntimeCallers = dedupeCallers(e.RuntimeCallers)

	sort.SliceStable(e.RuntimeTargets, func(i, j int) bool {
		return e.RuntimeTargets[i].TargetVA < e.RuntimeTargets[j].TargetVA
	})
	e.RuntimeTargets = dedupeTargets(e.RuntimeTargets)

	sort.SliceStable(e.RuntimeImports, func(i, j int) bool {
		a, b := e.RuntimeImports[i], e.RuntimeImports[j]
		ka := a.Module + "\x00" + a.Symbol + "\x00" + derefStr(a.SlotVA)
		kb := b.Module + "\x00" + b.Symbol + "\x00" + derefStr(b.SlotVA)
		return ka < kb
	})
	e.RuntimeImports = dedupeImports(e.RuntimeImports)

	sort.SliceStable(e.Observations, func(i, j int) bool {
		ki, kj := observationSortKey(&e.Observations[i]), observationSortKey(&e.Observations[j])
		if ki != kj {
			return ki < kj
		}
		bi, _ := json.Marshal(&e.Observations[i])
		bj, _ := json.Marshal(&e.Observations[j])
		return bytes.Compare(bi, bj) < 0
	})
	e.Observations = dedupeObservations(e.Observations)
}

func dedupeCallers(in []RuntimeCaller) []RuntimeCaller {
	out := in[:0]
	seen := map[string]bool{}
	for _, c := range in {
		k := c.CallsiteVA + "\x00" + derefStr(c.CallerFunctionVA)
		if seen[k] {
			continue
		}
		seen[k] = true
		out = append(out, c)
	}
	return out
}

func dedupeTargets(in []RuntimeTarget) []RuntimeTarget {
	out := in[:0]
	seen := map[string]bool{}
	for _, t := range in {
		if seen[t.TargetVA] {
			continue
		}
		seen[t.TargetVA] = true
		out = append(out, t)
	}
	return out
}

func dedupeImports(in []RuntimeImportRef) []RuntimeImportRef {
	out := in[:0]
	seen := map[string]bool{}
	for _, r := range in {
		k := r.Module + "\x00" + r.Symbol + "\x00" + derefStr(r.SlotVA)
		if seen[k] {
			continue
		}
		seen[k] = true
		out = append(out, r)
	}
	return out
}

func dedupeObservations(in []Observation) []Observation {
	out := in[:0]
	seen := map[string]bool{}
	for _, o := range in {
		raw, err := json.Marshal(&o)
		if err != nil {
			continue
		}
		if seen[string(raw)] {
			continue
		}
		seen[string(raw)] = true
		out = append(out, o)
	}
	return out
}

// Write serialises an overlay to path atomically, in the same shape the static
// snapshot uses: metadata first, entry lines after, content_sha256 over the
// entry lines only.
//
// Sorting happens here rather than being trusted from the caller, because the
// ordering is part of the format's contract and an unsorted overlay is a
// different file.
func Write(path string, entries []*Entry, meta Metadata) (Result, error) {
	ordered := append([]*Entry(nil), entries...)
	for _, e := range ordered {
		Normalize(e)
	}
	sort.SliceStable(ordered, func(i, j int) bool { return ordered[i].RequestedVA < ordered[j].RequestedVA })

	var body bytes.Buffer
	h := sha256.New()
	for i, e := range ordered {
		if i > 0 && ordered[i-1].RequestedVA == e.RequestedVA {
			return Result{}, fmt.Errorf("%w: duplicate requested_va %s", ErrCorrupt, e.RequestedVA)
		}
		if e.Record == "" {
			e.Record = RecordEntry
		}
		line, err := json.Marshal(e)
		if err != nil {
			return Result{}, fmt.Errorf("encoding %s: %w", e.RequestedVA, err)
		}
		line = append(line, '\n')
		h.Write(line)
		body.Write(line)
	}

	probe := &Overlay{Entries: map[uint32]*Entry{}}
	for _, e := range ordered {
		addr, err := canonicalAddr(e.RequestedVA)
		if err != nil {
			return Result{}, fmt.Errorf("entry %q: %w", e.RequestedVA, err)
		}
		if _, dup := probe.Entries[uint32(addr)]; dup {
			return Result{}, fmt.Errorf("%w: duplicate requested_va %s", ErrCorrupt, e.RequestedVA)
		}
		probe.Entries[uint32(addr)] = e
		probe.Order = append(probe.Order, uint32(addr))
	}

	meta.Record = RecordMetadata
	meta.Schema = OverlaySchema
	meta.ContentSHA256 = hex.EncodeToString(h.Sum(nil))
	meta.Counts = probe.Recount()
	header, err := json.Marshal(&meta)
	if err != nil {
		return Result{}, err
	}
	header = append(header, '\n')

	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		return Result{}, err
	}
	tmp, err := os.CreateTemp(filepath.Dir(path), filepath.Base(path)+".*")
	if err != nil {
		return Result{}, err
	}
	tmpName := tmp.Name()
	defer os.Remove(tmpName)

	w := bufio.NewWriterSize(tmp, 1<<20)
	if _, err := w.Write(header); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if _, err := w.Write(body.Bytes()); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := w.Flush(); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := tmp.Sync(); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := tmp.Close(); err != nil {
		return Result{}, err
	}
	if err := os.Chmod(tmpName, 0o644); err != nil {
		return Result{}, err
	}
	if err := os.Rename(tmpName, path); err != nil {
		return Result{}, err
	}
	return Result{
		Path:       path,
		Bytes:      int64(len(header) + body.Len()),
		Entries:    len(ordered),
		ContentSHA: meta.ContentSHA256,
	}, nil
}

// MergeProvenance returns the union of two provenance lists, sorted by
// (source_class, producer, artifact) and de-duplicated. It is exported because
// an adapter that folds two producer artifacts into one overlay has to combine
// attribution without losing or duplicating it.
func MergeProvenance(in ...[]ProvenanceEntry) []ProvenanceEntry {
	seen := map[string]bool{}
	var out []ProvenanceEntry
	for _, list := range in {
		for _, p := range list {
			k := p.SourceClass + "\x00" + p.Producer + "\x00" + p.Artifact
			if seen[k] {
				continue
			}
			seen[k] = true
			out = append(out, p)
		}
	}
	sort.Slice(out, func(i, j int) bool {
		a := out[i].SourceClass + "\x00" + out[i].Producer + "\x00" + out[i].Artifact
		b := out[j].SourceClass + "\x00" + out[j].Producer + "\x00" + out[j].Artifact
		return a < b
	})
	if out == nil {
		return []ProvenanceEntry{}
	}
	return out
}

// NewEntry builds an entry with the fields every producer states, so adapters
// and tests do not each invent the same boilerplate.
func NewEntry(requestedVA string) *Entry {
	return &Entry{
		Record:           RecordEntry,
		RequestedVA:      requestedVA,
		Canonicalization: CanonicalUnknown,
		Reached:          TriNull,
		RuntimeCallers:   []RuntimeCaller{},
		RuntimeTargets:   []RuntimeTarget{},
		RuntimeImports:   []RuntimeImportRef{},
		Observations:     []Observation{},
		Provenance:       []ProvenanceEntry{},
	}
}

// NewEmptyOverlay returns an overlay with no entries, for the case where a
// command was asked to run with no observation source. Every address then has no
// runtime summary, which is a real answer ("nothing was supplied") and not a
// fabricated "observed and not reached".
func NewEmptyOverlay() *Overlay {
	return &Overlay{Entries: map[uint32]*Entry{}, byCanonical: map[uint32][]uint32{}}
}

// Ptr returns a pointer to v. It exists so an adapter can populate optional
// fields without a named local for each one.
func Ptr[T any](v T) *T { return &v }

// SetReached sets the tri-state reached flag and, when the producer counted,
// keeps the count consistent with it.
func (e *Entry) SetReached(reached bool, count int) {
	if reached {
		e.Reached = TriTrue
	} else {
		e.Reached = TriFalse
	}
	e.EntryCount = Ptr(count)
}

// CanonicalAddr exposes the loader's canonical-spelling rule to adapters, so a
// producer-side conversion produces the same spelling the validator demands
// instead of guessing between "0x%08x" and bare hex.
func CanonicalAddr(s string) (semantic.Addr, error) { return canonicalAddr(s) }

// NormalizeAddr renders an address in the canonical spelling the overlay format
// requires.
func NormalizeAddr(a semantic.Addr) string { return a.String() }

// triState renders the Go zero value as the explicit "null" tri-state.
func triState(v semantic.TriBool) semantic.TriBool {
	if v == "" {
		return semantic.TriNull
	}
	return v
}
