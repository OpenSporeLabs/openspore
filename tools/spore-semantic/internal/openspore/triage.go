package openspore

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// TriageRow is one line of
// knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl.
//
// Field spellings are the classifier's, reproduced exactly. Note that the rows
// still carry "classifier_version": "triage-v5" even though the file is the v6
// snapshot; only the summary declares v6. That discrepancy is recorded in
// knowledgegraph/research/00-baseline-inventory.json and is why the row field
// is kept separate from any label this exporter writes.
type TriageRow struct {
	VA                string   `json:"va"`
	RVA               string   `json:"rva"`
	GhidraName        string   `json:"ghidra_name"`
	NormName          string   `json:"norm_name"`
	SDKName           *string  `json:"sdk_name"`
	Category          string   `json:"category"`
	Priority          string   `json:"priority"`
	Evidence          string   `json:"evidence"`
	Subsystem         *string  `json:"subsystem"`
	Cluster           *string  `json:"cluster"`
	StructNames       []string `json:"struct_names"`
	VTableAddrs       []string `json:"vtable_addrs"`
	VTableFamily      *string  `json:"vtable_family"`
	DecompPath        *string  `json:"decomp_path"`
	SCCSize           *int     `json:"scc_size"`
	CallerCount       *int     `json:"caller_count"`
	CalleeCount       *int     `json:"callee_count"`
	SnapshotSHA256    string   `json:"snapshot_sha256"`
	ClassifierVersion string   `json:"classifier_version"`
}

// Triage is the per-function classifier projection, keyed by canonical VA.
type Triage struct {
	ByAddr map[uint32]*TriageRow
	Path   string
}

// LoadTriage reads the triage JSONL.
func LoadTriage(root string) (*Triage, []Absent, error) {
	path := root + "/" + RelTriage
	if !FileExists(path) {
		return nil, []Absent{{Path: RelTriage, Reason: "not present in this checkout"}}, nil
	}
	f, err := os.Open(path)
	if err != nil {
		return nil, nil, err
	}
	defer f.Close()

	out := &Triage{ByAddr: make(map[uint32]*TriageRow), Path: RelTriage}
	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<22)
	for line := 1; sc.Scan(); line++ {
		text := sc.Bytes()
		if len(text) == 0 {
			continue
		}
		var row TriageRow
		if err := json.Unmarshal(text, &row); err != nil {
			return nil, nil, fmt.Errorf("%s:%d: %w", RelTriage, line, err)
		}
		addr, err := parseBareAddr(row.VA)
		if err != nil {
			return nil, nil, fmt.Errorf("%s:%d: %w", RelTriage, line, err)
		}
		if _, dup := out.ByAddr[addr]; dup {
			return nil, nil, fmt.Errorf("%s:%d: duplicate canonical VA %08x", RelTriage, line, addr)
		}
		r := row
		out.ByAddr[addr] = &r
	}
	if err := sc.Err(); err != nil {
		return nil, nil, err
	}
	return out, nil, nil
}

// SDKNameSource names the artifact a passport's sdk_name was copied from, so a
// consumer never has to guess whether a name came from the SDK or from the
// classifier.
const SDKNameSource = "sdk_functions.tsv"

// LevelOf maps a triage / ABI confidence string onto the shared scale, passing
// through anything already valid and reporting an off-scale value as UNKNOWN
// rather than inventing a rung.
func LevelOf(value string) semantic.EvidenceLevel {
	if semantic.KnownEvidenceLevel(value) {
		return semantic.EvidenceLevel(value)
	}
	return semantic.LevelUnknown
}
