// Package index is the in-memory lookup surface over a loaded snapshot.
//
// At ~59k records a map is the right structure: the snapshot loads in
// milliseconds, startup is immediate, and there is no database to migrate. No
// measurement has asked for anything more, so nothing more exists.
package index

import (
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/snapshot"
)

// Index resolves a canonical VA to its passport, a name to its passports, and
// a non-entry VA to the entry that contains it.
type Index struct {
	data   *snapshot.Data
	byAddr map[uint32]*semantic.Passport
	// symbols maps a lowercased name to the canonical VAs carrying it, sorted.
	symbols map[string][]uint32
	// bounds is the entry table used for interior resolution.
	bounds  []Bound
	base    semantic.Addr
	hasSize bool
}

// Bound is one function entry, sorted ascending.
type Bound struct {
	Addr uint32
	Size int
}

// New builds an Index from a loaded snapshot.
func New(data *snapshot.Data) *Index {
	ix := &Index{
		data:    data,
		byAddr:  make(map[uint32]*semantic.Passport, len(data.Order)),
		symbols: map[string][]uint32{},
		base:    data.ImageBase(),
	}
	ix.bounds = make([]Bound, 0, len(data.Order))
	starts := make([]uint32, 0, len(data.Order))
	for _, addr := range data.Order {
		p := data.Passports[addr]
		ix.byAddr[addr] = p
		ix.bounds = append(ix.bounds, Bound{Addr: addr, Size: p.Identity.Size})
		starts = append(starts, addr)
		if p.Identity.SizeKnown {
			ix.hasSize = true
		}
		for _, name := range namesOf(p) {
			key := strings.ToLower(name)
			ix.symbols[key] = append(ix.symbols[key], addr)
		}
	}
	for key := range ix.symbols {
		list := ix.symbols[key]
		sort.Slice(list, func(i, j int) bool { return list[i] < list[j] })
		ix.symbols[key] = list
	}
	return ix
}

// namesOf lists the names a passport can be found by, in the order they are
// searched. SDK and ghidra names are both indexed, because a consumer looking
// up "RenderWare::CompiledState::SetRaster" means the SDK name and a consumer
// looking up "FUN_00401000" means the ghidra name.
//
// The list is de-duplicated case-insensitively: for most functions
// normalized_symbol and ghidra_name are the same string, and indexing it twice
// would make every such lookup report a spurious ambiguity.
func namesOf(p *semantic.Passport) []string {
	var out []string
	seen := map[string]struct{}{}
	add := func(s string) {
		if s == "" {
			return
		}
		key := strings.ToLower(s)
		if _, dup := seen[key]; dup {
			return
		}
		seen[key] = struct{}{}
		out = append(out, s)
	}
	if p.Names.NormalizedSymbol != nil {
		add(*p.Names.NormalizedSymbol)
	}
	if p.Names.SDKName != nil {
		add(*p.Names.SDKName)
	}
	add(p.Names.GhidraName)
	return out
}

// Data returns the underlying snapshot.
func (ix *Index) Data() *snapshot.Data { return ix.data }

// ImageBase returns the snapshot's declared image base.
func (ix *Index) ImageBase() semantic.Addr { return ix.base }

// Len returns the number of passports.
func (ix *Index) Len() int { return len(ix.byAddr) }

// ResolutionKind names how a requested VA was matched.
type ResolutionKind string

const (
	// KindExact: the requested VA is itself a function entry.
	KindExact ResolutionKind = "function_entry"
	// KindInterior: the requested VA is inside a known function body and was
	// resolved to the containing entry.
	KindInterior ResolutionKind = "containing_function_entry"
	// KindUnknown: the requested VA is not an entry and is not inside any
	// body. This includes padding between bodies and addresses outside the
	// universe entirely.
	KindUnknown ResolutionKind = "non_function_entity"
)

// Resolution is the outcome of resolving a requested VA.
type Resolution struct {
	Requested semantic.Addr
	Kind      ResolutionKind
	Passport  *semantic.Passport
	// Offset is the byte distance into the containing body. Meaningful only
	// for KindInterior.
	Offset int
	// End is the exclusive end of the containing body, for KindInterior.
	End semantic.Addr
}

// Resolve applies the repository's canonical-identity rule to a requested VA.
//
// The rule is the one in tools/reconstruction_knowledge.py::canonical_identity:
// bisect on entry starts, then require start <= a < start + size. An address
// that is already an entry is KindExact. An address in the gap between bodies
// resolves to nothing and is reported as KindUnknown -- the conservative
// direction, because re-pointing an address the universe cannot place is the
// same class of error as inventing a mapping.
func (ix *Index) Resolve(va semantic.Addr) Resolution {
	res := Resolution{Requested: va, Kind: KindUnknown}
	if p, ok := ix.byAddr[uint32(va)]; ok {
		res.Kind = KindExact
		res.Passport = p
		return res
	}
	if !ix.hasSize {
		return res
	}
	i := sort.Search(len(ix.bounds), func(i int) bool { return ix.bounds[i].Addr > uint32(va) }) - 1
	if i < 0 {
		return res
	}
	b := ix.bounds[i]
	if b.Size <= 0 {
		return res
	}
	end := b.Addr + uint32(b.Size)
	if uint32(va) >= b.Addr && uint32(va) < end {
		res.Kind = KindInterior
		res.Passport = ix.byAddr[b.Addr]
		res.Offset = int(uint32(va) - b.Addr)
		res.End = semantic.Addr(end)
	}
	return res
}

// SymbolMatch is one passport found by name.
type SymbolMatch struct {
	Name     string
	Passport *semantic.Passport
}

// LookupSymbol returns every passport carrying name, ordered by canonical VA.
//
// A name may legitimately be ambiguous: the triage classifier's own notes
// record 92 duplicate normalized-name groups across 190 rows in the canonical
// universe, which is exactly why address identity stays authoritative. The
// caller decides whether ambiguity is an error.
func (ix *Index) LookupSymbol(name string) []SymbolMatch {
	addrs := ix.symbols[strings.ToLower(strings.TrimSpace(name))]
	out := make([]SymbolMatch, 0, len(addrs))
	for _, addr := range addrs {
		out = append(out, SymbolMatch{Name: ix.byAddr[addr].Names.GhidraName, Passport: ix.byAddr[addr]})
	}
	return out
}

// SymbolCount returns the number of distinct indexed names.
func (ix *Index) SymbolCount() int { return len(ix.symbols) }

// AmbiguousNameCount returns how many indexed names map to more than one
// function. It is reported by `stats` because it is a property of the
// identity model, not a defect: names are a convenience index, addresses are
// the key.
func (ix *Index) AmbiguousNameCount() int {
	n := 0
	for _, addrs := range ix.symbols {
		if len(addrs) > 1 {
			n++
		}
	}
	return n
}
