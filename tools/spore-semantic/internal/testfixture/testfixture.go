// Package testfixture builds a minimal but shape-accurate OpenSpore checkout
// in a temp directory: the same artifacts, the same column orders and the same
// value vocabularies the real exporter reads, at a size a test can reason
// about.
//
// The fixtures are hand-written to the documented shapes rather than trimmed
// from the real checkout, so a test failure means the reader or the schema
// changed -- not that a 58k-row export moved. The real checkout is exercised
// separately by the integration tests in package cli.
package testfixture

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
)

// BinarySHA is the canonical SporeApp.exe 3.1.0.22 digest.
const BinarySHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"

// OtherSHA is a different binary, used for mismatch tests.
const OtherSHA = "0000000000000000000000000000000000000000000000000000000000000000"

// ImageBase is the Spore PE ImageBase in canonical spelling.
const ImageBase = "0x00400000"

// Function is one row of the frozen Ghidra universe export.
type Function struct {
	VA      uint32
	Name    string
	Size    int
	IsThunk bool
}

// Triage is one row of the triage classifier's JSONL.
type Triage struct {
	VA          uint32
	GhidraName  string
	SDKName     string
	Category    string
	Priority    string
	Evidence    string
	Subsystem   string
	Cluster     string
	Structs     []string
	VTableAddrs []string
	SCCSize     int
}

// XRef is one row of the closure-validated call-graph export.
type XRef struct {
	Caller  uint32
	Callee  uint32
	RefType string
}

// DataRef is one row of the data-reference sidecar.
type DataRef struct {
	Caller uint32
	Target uint32
	Access string
}

// Membership is one (table, slot) pair in the sound vftable scan.
type Membership struct {
	VA    uint32
	Table uint32
	Slot  int
}

// Tree is a synthetic OpenSpore checkout under construction.
type Tree struct {
	Root string

	Functions   []Function
	Triage      []Triage
	XRefs       []XRef
	DataRefs    []DataRef
	Memberships []Membership

	// ABIRecords maps a VA to the raw JSON of its evidence pack's
	// abi_derived value. A nil entry writes a pack with no abi_derived value.
	ABIRecords map[uint32]json.RawMessage
	// Packs is the set of VAs that get an evidence pack at all.
	Packs map[uint32]bool
	// Validation is the validation report body per VA.
	Validation map[uint32]ValidationDoc
	// Promoted is the set of VAs that get a promotion record.
	Promoted map[uint32]bool
	// RecordOverrides lets a test inject or replace knowledge-index records.
	RecordOverrides map[string]map[string]any
	// BinarySHA overrides the declared binary identity.
	BinarySHA string
	// ImageBase overrides the declared image base.
	ImageBase string
	// OmitVTableScan drops the sound vftable scan, to test the absent-input path.
	OmitVTableScan bool
	// OmitFunctionsTSV drops the git-ignored universe export, to test the
	// tracked-coverage-ledger fallback.
	OmitFunctionsTSV bool
}

// ValidationDoc is the shape of validation.json's checks block.
type ValidationDoc struct {
	Schema string
	Checks map[string]Check
	Static map[string]any
}

// Check is one dimension verdict.
type Check struct {
	Status   string
	Coverage string
	Detail   string
}

// New starts a tree in a fresh temp directory.
func New(t interface{ Fatalf(string, ...any) }) *Tree {
	dir, err := os.MkdirTemp("", "spore-semantic-fixture-*")
	if err != nil {
		t.Fatalf("MkdirTemp: %v", err)
	}
	return &Tree{
		Root:            dir,
		BinarySHA:       BinarySHA,
		ImageBase:       ImageBase,
		ABIRecords:      map[uint32]json.RawMessage{},
		Packs:           map[uint32]bool{},
		Validation:      map[uint32]ValidationDoc{},
		Promoted:        map[uint32]bool{},
		RecordOverrides: map[string]map[string]any{},
	}
}

// Write materialises the tree.
func (t *Tree) Write() error {
	paths := []string{
		filepath.Join(t.Root, "knowledgegraph/triage"),
		filepath.Join(t.Root, "reconstruction/knowledge"),
		filepath.Join(t.Root, ".spore-analysis/ghidra-exports"),
		filepath.Join(t.Root, ".spore-analysis/cache"),
	}
	for _, p := range paths {
		if err := os.MkdirAll(p, 0o755); err != nil {
			return err
		}
	}
	if err := t.writeFunctions(); err != nil {
		return err
	}
	if err := t.writeTriage(); err != nil {
		return err
	}
	if err := t.writeIndex(); err != nil {
		return err
	}
	if err := t.writeXrefs(); err != nil {
		return err
	}
	if err := t.writeEvidence(); err != nil {
		return err
	}
	if t.OmitVTableScan {
		// Remove rather than skip, so a test can flip the flag after an initial
		// Write and get a checkout that genuinely lacks the artifact.
		if err := removeIfPresent(filepath.Join(t.Root, ".spore-analysis/cache", "vftables-"+t.BinarySHA+".json")); err != nil {
			return err
		}
	} else if err := t.writeVTableScan(); err != nil {
		return err
	}
	if t.OmitFunctionsTSV {
		if err := removeIfPresent(filepath.Join(t.Root, ".spore-analysis/ghidra-exports/functions.tsv")); err != nil {
			return err
		}
		if err := t.WriteCoverageLedger(); err != nil {
			return err
		}
	}
	return nil
}

// WriteCoverageLedger writes the git-tracked universe fallback.
func (t *Tree) WriteCoverageLedger() error {
	ledger := make([]map[string]any, 0, len(t.Functions))
	for _, f := range t.Functions {
		ledger = append(ledger, map[string]any{
			"va":                          fmt.Sprintf("%08x", f.VA),
			"function_body_size_bytes":    f.Size,
			"function_body_end_exclusive": fmt.Sprintf("%08x", f.VA+uint32(f.Size)),
		})
	}
	doc := map[string]any{
		"schema": "openspore-decompilation-coverage-1",
		"scope":  map[string]any{"canonical_universe": map[string]any{"count": len(ledger)}},
		"ledger": ledger,
	}
	return writeJSONFile(filepath.Join(t.Root, "knowledgegraph/research/21-decompilation-coverage.json"), doc)
}

func (t *Tree) writeFunctions() error {
	var b []byte
	b = append(b, []byte("address\tname\tsize\tis_thunk\tis_external\tsection\n")...)
	for _, f := range t.Functions {
		thunk := "false"
		if f.IsThunk {
			thunk = "true"
		}
		b = append(b, []byte(fmt.Sprintf("%08x\t%s\t%d\t%s\tfalse\t.text\n", f.VA, f.Name, f.Size, thunk))...)
	}
	return writeFile(filepath.Join(t.Root, ".spore-analysis/ghidra-exports/functions.tsv"), b)
}

func (t *Tree) writeTriage() error {
	var b []byte
	for _, r := range t.Triage {
		row := map[string]any{
			"va":                 fmt.Sprintf("%08x", r.VA),
			"rva":                fmt.Sprintf("%08x", r.VA-0x400000),
			"ghidra_name":        r.GhidraName,
			"norm_name":          r.GhidraName,
			"category":           r.Category,
			"priority":           r.Priority,
			"evidence":           r.Evidence,
			"scc_size":           r.SCCSize,
			"snapshot_sha256":    "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
			"classifier_version": "triage-v5",
		}
		if r.SDKName != "" {
			row["sdk_name"] = r.SDKName
		} else {
			row["sdk_name"] = nil
		}
		if r.Subsystem != "" {
			row["subsystem"] = r.Subsystem
		}
		if r.Cluster != "" {
			row["cluster"] = r.Cluster
		}
		if r.Structs != nil {
			row["struct_names"] = r.Structs
		}
		if r.VTableAddrs != nil {
			row["vtable_addrs"] = r.VTableAddrs
		}
		line, err := json.Marshal(row)
		if err != nil {
			return err
		}
		b = append(b, line...)
		b = append(b, '\n')
	}
	return writeFile(filepath.Join(t.Root, "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl"), b)
}

func (t *Tree) writeIndex() error {
	records := map[string]map[string]any{}
	for _, f := range t.Functions {
		key := fmt.Sprintf("0x%08x", f.VA)
		// Only the always-present mechanical keys. Campaign fields (status,
		// package, runtime gates, semantics) come from RecordOverrides, so a
		// function with no override is genuinely unreconstructed and the
		// passport says so explicitly.
		rec := map[string]any{
			"va":                   key,
			"name":                 f.Name,
			"normalized_symbol":    f.Name,
			"globals":              []string{},
			"types":                []string{},
			"vtables":              []string{},
			"unresolved_questions": []string{},
		}
		for k, v := range t.RecordOverrides[key] {
			rec[k] = v
		}
		records[key] = rec
	}
	doc := map[string]any{
		"$schema": "openspore-reconstruction-knowledge-index-1",
		"binary": map[string]any{
			"architecture":   "x86:LE:32",
			"ghidra_program": "SporeApp.exe",
			"image_base":     t.ImageBase,
			"program":        "SporeApp.exe",
			"sha256":         t.BinarySHA,
			"version":        "3.1.0.22",
		},
		"records":           records,
		"packages":          map[string]any{},
		"semantic_families": []any{},
	}
	return writeJSONFile(filepath.Join(t.Root, "reconstruction/knowledge/index.json"), doc)
}

func (t *Tree) writeXrefs() error {
	var b []byte
	b = append(b, []byte("caller_va\tcallee_va\treference_type\tcallsite_va\tsource\tsnapshot_sha256\n")...)
	for _, e := range t.XRefs {
		b = append(b, []byte(fmt.Sprintf("%08x\t%08x\t%s\t%08x\tghidra:SporeApp.exe\tf0e310e0\n",
			e.Caller, e.Callee, e.RefType, e.Caller+1))...)
	}
	if err := writeFile(filepath.Join(t.Root, "knowledgegraph/triage/xrefs-2540f2ca.tsv"), b); err != nil {
		return err
	}
	b = nil
	b = append(b, []byte("caller_va\ttarget_va\taccess_mode\tsegment\tcallsite_va\tsource\tsnapshot_sha256\n")...)
	for _, d := range t.DataRefs {
		b = append(b, []byte(fmt.Sprintf("%08x\t%08x\t%s\t.data -wr\t%08x\tghidra:SporeApp.exe\tf0e310e0\n",
			d.Caller, d.Target, d.Access, d.Caller+1))...)
	}
	return writeFile(filepath.Join(t.Root, "knowledgegraph/triage/datarefs-2540f2ca.tsv"), b)
}

func (t *Tree) writeEvidence() error {
	for va, has := range t.Packs {
		if !has {
			continue
		}
		dir := filepath.Join(t.Root, "reconstruction/evidence", fmt.Sprintf("%08x", va))
		if err := os.MkdirAll(dir, 0o755); err != nil {
			return err
		}
		categories := map[string]any{}
		if raw, ok := t.ABIRecords[va]; ok {
			categories["abi_derived"] = map[string]any{
				"availability":   "available",
				"evidence_level": "INFERRED",
				"evidence_state": "DERIVED",
				"provenance":     []string{"reconstruction/knowledge/index.json"},
				"reason":         nil,
				"value":          raw,
			}
		} else {
			categories["abi_derived"] = map[string]any{
				"availability":   "unavailable",
				"evidence_level": "UNKNOWN",
				"evidence_state": "MISSING",
				"provenance":     []string{"reconstruction/knowledge/index.json"},
				"reason":         "no exact source evidence found",
				"value":          nil,
			}
		}
		pack := map[string]any{
			"schema":         "openspore-evidence-pack-1",
			"evidence_state": "PERSISTED",
			"content_sha256": nil,
			"target":         map[string]any{"va": fmt.Sprintf("0x%08x", va), "address_kind": "linked_va"},
			"binary": map[string]any{
				"architecture": "x86:LE:32", "ghidra_program": "SporeApp.exe",
				"image_base": t.ImageBase, "program": "SporeApp.exe",
				"sha256": t.BinarySHA, "version": "3.1.0.22",
			},
			"categories": categories,
			"provenance": []map[string]any{
				{"mode": "derived", "ref": "ephemeral reconstruction_knowledge.build_index", "source_class": "generated_index"},
				{"mode": "live", "ref": "GhidraMCP /disassemble_function", "source_class": "ghidra"},
			},
		}
		if err := writeJSONFile(filepath.Join(dir, "evidence.json"), pack); err != nil {
			return err
		}
		if vdoc, ok := t.Validation[va]; ok {
			checks := map[string]any{}
			for name, c := range vdoc.Checks {
				checks[name] = map[string]any{
					"status": c.Status, "coverage": c.Coverage, "detail": c.Detail,
					"evidence": []string{"reconstruction/knowledge/index.json"},
				}
			}
			body := map[string]any{
				"schema": "openspore-structural-validation-1",
				"checks": checks,
				"runtime": map[string]any{
					"dimension": "RUNTIME", "gated": true, "gates": []any{},
					"reason": "no original-process trace exists in this repository",
					"status": "GATED", "validated": 0,
				},
			}
			if vdoc.Static != nil {
				body["static"] = vdoc.Static
			}
			if err := writeJSONFile(filepath.Join(dir, "validation.json"), body); err != nil {
				return err
			}
		}
		if t.Promoted[va] {
			promo := map[string]any{
				"schema":         "openspore-promotion-record-1",
				"va":             fmt.Sprintf("0x%08x", va),
				"bare_va":        fmt.Sprintf("%08x", va),
				"package":        "PKG-FIXTURE",
				"src_package":    "pkg_fixture",
				"namespace":      "openspore::reconstruction::pkg_fixture",
				"sources":        []string{"fixture.cpp"},
				"headers":        []string{},
				"static_status":  "PASS",
				"runtime_status": "GATED",
				"promoted_on":    "2026-01-01",
				"provenance":     []string{"reconstruction/staging/pkg-fixture"},
				"supersedes":     nil,
			}
			if err := writeJSONFile(filepath.Join(dir, "promotion.json"), promo); err != nil {
				return err
			}
		}
	}
	return nil
}

func (t *Tree) writeVTableScan() error {
	memberships := map[string][][]any{}
	widths := map[string]int{}
	for _, m := range t.Memberships {
		key := fmt.Sprintf("0x%08x", m.VA)
		memberships[key] = append(memberships[key], []any{fmt.Sprintf("0x%08x", m.Table), m.Slot})
		widths[fmt.Sprintf("0x%08x", m.Table)] = 16
	}
	scan := map[string]any{
		"schema":        "openspore-vftable-scan-1",
		"cache_version": 3,
		"binary_sha256": t.BinarySHA,
		"image_base":    t.ImageBase,
		"tables":        widths,
		"memberships":   memberships,
		"stats":         map[string]int{"sound_tables": len(widths)},
	}
	return writeJSONFile(filepath.Join(t.Root, ".spore-analysis/cache", "vftables-"+t.BinarySHA+".json"), scan)
}

// ABIRecordJSON builds an openspore-abi-inference-1 value. Every field the
// passport projects is settable; anything left nil stays null, which is what a
// real abstaining record looks like.
func ABIRecordJSON(convention *string, confidence string, receiverPresent *bool, slot *int) json.RawMessage {
	rec := map[string]any{
		"schema":       "openspore-abi-inference-1",
		"verdict":      "ABI_UNKNOWN",
		"completeness": "PARTIAL",
		"conventions": map[string]any{
			"calling_convention":    convention,
			"confidence":            confidence,
			"candidate_conventions": []string{"__cdecl"},
			"corroboration":         "not_available",
		},
		"receiver": map[string]any{
			"present": receiverPresent, "register": nil, "confidence": "UNKNOWN",
			"bounds_only": true,
		},
		"cleanup": map[string]any{
			"side": nil, "bytes": nil, "confidence": "UNKNOWN", "corroboration": "not_available",
		},
		"return": map[string]any{
			"register": nil, "register_class": "unknown", "confidence": "UNKNOWN",
			"type": nil, "void_possible": false,
		},
		"sret":                map[string]any{"present": false, "confidence": "APPROXIMATION"},
		"variadic":            "UNKNOWN",
		"seh_or_cookie_frame": false,
		"stack_arguments": map[string]any{
			"observed_slots": 0, "derived_slots": 0, "confidence": "APPROXIMATION",
		},
		"inferences": []any{},
	}
	if convention != nil {
		rec["verdict"] = "ABI_INFERRED"
	}
	if receiverPresent != nil && *receiverPresent {
		rec["receiver"].(map[string]any)["register"] = "ECX"
		rec["receiver"].(map[string]any)["confidence"] = "INFERRED"
		rec["receiver"].(map[string]any)["shape"] = "R-DIRECT"
	}
	if slot != nil {
		rec["inferences"] = []any{map[string]any{
			"id": "R1-VFT", "based_on": []string{"obs-0001"}, "confidence": "INFERRED",
			"value": map[string]any{
				"table": "0x013f57f8", "slot_index": *slot,
				"receiver_provenance": "vftable_slot_dispatch", "membership_count": 1,
			},
		}}
	}
	out, err := json.Marshal(rec)
	if err != nil {
		panic(err)
	}
	return out
}

func removeIfPresent(path string) error {
	if err := os.Remove(path); err != nil && !os.IsNotExist(err) {
		return err
	}
	return nil
}

func writeFile(path string, data []byte) error {
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		return err
	}
	return os.WriteFile(path, data, 0o644)
}

func writeJSONFile(path string, v any) error {
	data, err := json.MarshalIndent(v, "", "  ")
	if err != nil {
		return err
	}
	return writeFile(path, append(data, '\n'))
}
