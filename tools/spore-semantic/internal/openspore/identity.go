package openspore

import "sort"

// Resolution is the outcome of applying the repository's canonical-identity
// rule to an address that is not a function entry.
type Resolution struct {
	// Entry is the containing function's canonical VA.
	Entry uint32
	// Offset is the byte distance from Entry.
	Offset int
	// End is Entry + size, the exclusive end of the containing body.
	End uint32
	// Name is the entry's name when the universe supplied one.
	Name string
}

// CanonicalIdentity resolves a requested VA onto the function entry that
// contains it.
//
// This is a verbatim transcription of canonical_identity() in
// tools/reconstruction_knowledge.py, including its conservative direction: an
// address that is already an entry returns notFound; an address that falls in
// the gap between two entries -- real padding, or the last byte of a final
// instruction of a body whose size stops short -- also returns notFound. Only
// an address that passes the exact start <= a < start + size test is moved.
// The algorithm is deliberately NOT re-invented here; a second mapping rule
// would be a second source of truth for identity.
func (u *Universe) CanonicalIdentity(va uint32) (Resolution, bool) {
	if u == nil || len(u.Entries) == 0 {
		return Resolution{}, false
	}
	starts := make([]uint32, len(u.Entries))
	for i, e := range u.Entries {
		starts[i] = e.Addr
	}
	pos := sort.Search(len(starts), func(i int) bool { return starts[i] > va }) - 1
	if pos < 0 {
		return Resolution{}, false
	}
	e := u.Entries[pos]
	if e.Addr == va {
		return Resolution{}, false
	}
	end := e.Addr + uint32(max(e.Size, 0))
	if va >= e.Addr && va < end {
		return Resolution{Entry: e.Addr, Offset: int(va - e.Addr), End: end, Name: e.Name}, true
	}
	return Resolution{}, false
}

// Lookup returns the entry at exactly va.
func (u *Universe) Lookup(va uint32) (Entry, bool) {
	if u == nil || len(u.Entries) == 0 {
		return Entry{}, false
	}
	i := sort.Search(len(u.Entries), func(i int) bool { return u.Entries[i].Addr >= va })
	if i < len(u.Entries) && u.Entries[i].Addr == va {
		return u.Entries[i], true
	}
	return Entry{}, false
}

// Contains reports whether va falls inside any entry body. It is used to
// distinguish "this is a non-function entity inside the image" from "this is
// outside the code the universe covers".
func (u *Universe) Contains(va uint32) bool {
	_, ok := u.CanonicalIdentity(va)
	return ok
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
