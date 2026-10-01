package openspore

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

// Edge is one row of the closure-validated call-graph export.
type Edge struct {
	Caller uint32
	Callee uint32
	// CalleeExt is the verbatim EXT:<library>::<name> token when the callee is
	// an imported symbol rather than an address in the pinned universe.
	CalleeExt    string
	CalleeIsVTab bool
	RefType      string
	Callsite     string
}

// Graph is the per-function call graph projected from the xref export.
type Graph struct {
	Callers         map[uint32][]uint32
	Callees         map[uint32][]uint32
	ExternalCallees map[uint32][]string
	VTableRefs      map[uint32]int
	Edges           int
}

// NewGraph returns an empty Graph.
func NewGraph() *Graph {
	return &Graph{
		Callers:         map[uint32][]uint32{},
		Callees:         map[uint32][]uint32{},
		ExternalCallees: map[uint32][]string{},
		VTableRefs:      map[uint32]int{},
	}
}

const (
	xrefHeader  = "caller_va\tcallee_va\treference_type\tcallsite_va\tsource\tsnapshot_sha256"
	datarefHead = "caller_va\ttarget_va\taccess_mode\tsegment\tcallsite_va\tsource\tsnapshot_sha256"
)

// LoadGraph reads knowledgegraph/triage/xrefs-2540f2ca.tsv.
//
// The export is closure-validated: tools/triage/export_xrefs.py asserts that
// every caller and every non-EXT/non-VT callee is in the pinned 58,757-VA
// universe, and that every EXT token is on the externals allowlist. This reader
// therefore does not re-validate membership -- it would either agree or
// contradict the exporter's assertion -- but it does preserve the VT tokens and
// EXT tokens verbatim rather than dropping a callee it cannot resolve to a VA.
func LoadGraph(root string) (*Graph, []Absent, []Digest, error) {
	path := root + "/" + RelXrefs
	g := NewGraph()
	if !FileExists(path) {
		return g, []Absent{{
			Path:   RelXrefs,
			Reason: "not present in this checkout; callers, callees and external callees are unavailable",
		}}, nil, nil
	}
	f, err := os.Open(path)
	if err != nil {
		return nil, nil, nil, err
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<20)
	if !sc.Scan() {
		return nil, nil, nil, &ParseError{Path: RelXrefs, Msg: "empty file"}
	}
	if got := strings.TrimRight(sc.Text(), "\r\n"); got != xrefHeader {
		return nil, nil, nil, &ParseError{Path: RelXrefs, Msg: "header is " + got + ", expected " + xrefHeader}
	}

	extSeen := map[uint32]map[string]struct{}{}
	calleeSeen := map[uint32]map[uint32]struct{}{}
	callerSeen := map[uint32]map[uint32]struct{}{}
	vtSeen := map[uint32]map[string]struct{}{}

	for line := 2; sc.Scan(); line++ {
		text := strings.TrimRight(sc.Text(), "\r\n")
		if text == "" {
			continue
		}
		cols := strings.Split(text, "\t")
		if len(cols) < 4 {
			return nil, nil, nil, &ParseError{Path: RelXrefs, Line: line, Msg: "fewer than 4 columns"}
		}
		caller, err := parseBareAddr(cols[0])
		if err != nil {
			return nil, nil, nil, &ParseError{Path: RelXrefs, Line: line, Msg: err.Error()}
		}
		rawCallee := cols[1]
		g.Edges++

		switch {
		case strings.HasPrefix(rawCallee, "EXT:"):
			tok := rawCallee
			if extSeen[caller] == nil {
				extSeen[caller] = map[string]struct{}{}
			}
			extSeen[caller][tok] = struct{}{}
		case strings.HasPrefix(rawCallee, "VT:"):
			tok := rawCallee
			if vtSeen[caller] == nil {
				vtSeen[caller] = map[string]struct{}{}
			}
			if _, seen := vtSeen[caller][tok]; !seen {
				vtSeen[caller][tok] = struct{}{}
				g.VTableRefs[caller]++
			}
		default:
			callee, err := parseBareAddr(rawCallee)
			if err != nil {
				return nil, nil, nil, &ParseError{Path: RelXrefs, Line: line, Msg: err.Error()}
			}
			if calleeSeen[caller] == nil {
				calleeSeen[caller] = map[uint32]struct{}{}
			}
			if _, seen := calleeSeen[caller][callee]; !seen {
				calleeSeen[caller][callee] = struct{}{}
				g.Callees[caller] = append(g.Callees[caller], callee)
			}
			if callerSeen[callee] == nil {
				callerSeen[callee] = map[uint32]struct{}{}
			}
			callerSeen[callee][caller] = struct{}{}
		}
	}
	if err := sc.Err(); err != nil {
		return nil, nil, nil, err
	}

	for caller, set := range callerSeen {
		list := make([]uint32, 0, len(set))
		for c := range set {
			list = append(list, c)
		}
		sort.Slice(list, func(i, j int) bool { return list[i] < list[j] })
		g.Callers[caller] = list
	}
	for caller := range g.Callees {
		sort.Slice(g.Callees[caller], func(i, j int) bool { return g.Callees[caller][i] < g.Callees[caller][j] })
	}
	for caller, set := range extSeen {
		list := make([]string, 0, len(set))
		for tok := range set {
			list = append(list, tok)
		}
		sort.Strings(list)
		g.ExternalCallees[caller] = list
	}
	digests, err := digestOrFail(root, path)
	if err != nil {
		return nil, nil, nil, err
	}
	return g, nil, digests, nil
}

// LoadDataRefCounts reads knowledgegraph/triage/datarefs-2540f2ca.tsv and
// returns, per function, how many distinct data addresses its body references.
//
// Only the COUNT is projected. The addresses themselves stay in the committed
// TSV: a data-reference address is not a canonical function entity, so putting
// it in a function passport would invite a consumer to look one up as if it
// were a function.
func LoadDataRefCounts(root string) (map[uint32]int, []Absent, []Digest, error) {
	path := root + "/" + RelDatarefs
	counts := map[uint32]int{}
	if !FileExists(path) {
		return counts, []Absent{{
			Path:   RelDatarefs,
			Reason: "not present in this checkout; per-function data-reference counts are unavailable",
		}}, nil, nil
	}
	f, err := os.Open(path)
	if err != nil {
		return nil, nil, nil, err
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<20)
	if !sc.Scan() {
		return nil, nil, nil, &ParseError{Path: RelDatarefs, Msg: "empty file"}
	}
	if got := strings.TrimRight(sc.Text(), "\r\n"); got != datarefHead {
		return nil, nil, nil, &ParseError{Path: RelDatarefs, Msg: "header is " + got + ", expected " + datarefHead}
	}
	seen := map[uint32]map[string]struct{}{}
	for line := 2; sc.Scan(); line++ {
		text := strings.TrimRight(sc.Text(), "\r\n")
		if text == "" {
			continue
		}
		cols := strings.Split(text, "\t")
		if len(cols) < 2 {
			return nil, nil, nil, &ParseError{Path: RelDatarefs, Line: line, Msg: "fewer than 2 columns"}
		}
		caller, err := parseBareAddr(cols[0])
		if err != nil {
			return nil, nil, nil, &ParseError{Path: RelDatarefs, Line: line, Msg: err.Error()}
		}
		if seen[caller] == nil {
			seen[caller] = map[string]struct{}{}
		}
		if _, dup := seen[caller][cols[1]]; !dup {
			seen[caller][cols[1]] = struct{}{}
			counts[caller]++
		}
	}
	if err := sc.Err(); err != nil {
		return nil, nil, nil, err
	}
	digests, err := digestOrFail(root, path)
	if err != nil {
		return nil, nil, nil, err
	}
	return counts, nil, digests, nil
}

// ParseError locates a malformed authoritative artifact.
type ParseError struct {
	Path string
	Line int
	Msg  string
}

func (e *ParseError) Error() string {
	if e.Line > 0 {
		return e.Path + ":" + strconv.Itoa(e.Line) + ": " + e.Msg
	}
	return e.Path + ": " + e.Msg
}

func digestOrFail(root, path string) ([]Digest, error) {
	dg, err := FileDigest(root, path)
	if err != nil {
		return nil, err
	}
	return []Digest{dg}, nil
}
