package openspore

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

// VTableScan is the subset of the sound vftable scan
// (.spore-analysis/cache/vftables-<binary_sha256>.json) that reaches a
// passport.
//
// This is the ONLY vftable source the ABI engine accepts:
// tools/reconstruction_tooling/evidence.py hands abi_infer.py entries carrying
// basis "vftable_predicate", and abi_infer.py drops any membership that cannot
// state it. The triage artifact (docs/analysis/vtables.json, 5.6 MB, candidates
// with slots as a list of dicts) is a different, weaker product of a different
// script (tools/ghidra/VtableDetect.java) and is deliberately NOT read here.
type VTableScan struct {
	Schema       string `json:"schema"`
	BinarySHA256 string `json:"binary_sha256"`
	ImageBase    string `json:"image_base"`
	// Tables maps table VA string -> slot count.
	Tables map[string]int `json:"tables"`
	// Memberships maps function VA string -> list of [table_va_string, slot].
	Memberships map[string][][]json.RawMessage `json:"memberships"`
	Stats       map[string]int                 `json:"stats"`
}

// Membership is one resolved (table, slot) pair.
type Membership struct {
	TableVA uint32
	Slot    int
	Width   int
	Known   bool
}

// LoadVTableScan finds and reads the sound vftable scan cache for the given
// binary. The cache is named by binary digest, so a checkout holding the scan
// for a different binary is reported as absent rather than silently used.
func LoadVTableScan(root, binarySHA string) (map[uint32][]Membership, *VTableScan, []Absent, error) {
	dir := root + "/" + RelVftableDir
	if !DirExists(dir) {
		return nil, nil, []Absent{{
			Path:   RelVftableDir + "/vftables-" + binarySHA + ".json",
			Reason: "not present in this checkout (it is git-ignored); vftable memberships and slot indices are unavailable, and vtable membership for this binary is reported as an explicit absence rather than an empty set",
		}}, nil
	}
	entries, err := os.ReadDir(dir)
	if err != nil {
		return nil, nil, nil, err
	}
	wanted := "vftables-" + binarySHA + ".json"
	var found string
	for _, de := range entries {
		if de.IsDir() || !strings.HasSuffix(de.Name(), ".json") {
			continue
		}
		if de.Name() == wanted {
			found = filepath.Join(dir, de.Name())
			break
		}
	}
	if found == "" {
		var names []string
		for _, de := range entries {
			if !de.IsDir() && strings.HasPrefix(de.Name(), "vftables-") {
				names = append(names, de.Name())
			}
		}
		sort.Strings(names)
		reason := "not present in this checkout (it is git-ignored)"
		if len(names) > 0 {
			reason += "; caches present describe a different binary: " + strings.Join(names, ", ")
		}
		return nil, nil, []Absent{{Path: RelVftableDir + "/" + wanted, Reason: reason}}, nil
	}

	raw, err := os.ReadFile(found)
	if err != nil {
		return nil, nil, nil, err
	}
	var scan VTableScan
	if err := json.Unmarshal(raw, &scan); err != nil {
		return nil, nil, nil, fmt.Errorf("%s: %w", filepath.Base(found), err)
	}
	if scan.BinarySHA256 != "" && binarySHA != "" && scan.BinarySHA256 != binarySHA {
		return nil, nil, []Absent{{
			Path:   RelVftableDir + "/" + wanted,
			Reason: "the scan names binary_sha256 " + scan.BinarySHA256 + ", which is not the requested " + binarySHA,
		}}, nil
	}

	out := make(map[uint32][]Membership, len(scan.Memberships))
	for key, pairs := range scan.Memberships {
		addr, err := parseHexAddrLoose(key)
		if err != nil {
			return nil, nil, nil, fmt.Errorf("%s: memberships key %q: %w", filepath.Base(found), key, err)
		}
		list := make([]Membership, 0, len(pairs))
		for _, pair := range pairs {
			if len(pair) != 2 {
				return nil, nil, nil, fmt.Errorf("%s: memberships[%s]: expected a [table, slot] pair, got %d elements", filepath.Base(found), key, len(pair))
			}
			var tableStr string
			if err := json.Unmarshal(pair[0], &tableStr); err != nil {
				return nil, nil, nil, fmt.Errorf("%s: memberships[%s][0]: %w", filepath.Base(found), key, err)
			}
			var slot int
			if err := json.Unmarshal(pair[1], &slot); err != nil {
				return nil, nil, nil, fmt.Errorf("%s: memberships[%s][1]: %w", filepath.Base(found), key, err)
			}
			table, err := parseHexAddrLoose(tableStr)
			if err != nil {
				return nil, nil, nil, fmt.Errorf("%s: memberships[%s]: table %q: %w", filepath.Base(found), key, tableStr, err)
			}
			m := Membership{TableVA: table, Slot: slot}
			if w, ok := scan.Tables[tableStr]; ok {
				m.Width = w
				m.Known = true
			} else if w, ok := scan.Tables[fmt.Sprintf("0x%08x", table)]; ok {
				m.Width = w
				m.Known = true
			}
			list = append(list, m)
		}
		// Sort by (table, slot) so the JSON is stable regardless of the order
		// the scan happened to write.
		sort.Slice(list, func(i, j int) bool {
			if list[i].TableVA != list[j].TableVA {
				return list[i].TableVA < list[j].TableVA
			}
			return list[i].Slot < list[j].Slot
		})
		if _, dup := out[addr]; dup {
			return nil, nil, nil, fmt.Errorf("%s: duplicate membership key %q", filepath.Base(found), key)
		}
		out[addr] = list
	}
	return out, &scan, nil, nil
}

// parseHexAddrLoose accepts both address spellings the sound scan uses for
// keys: "0x013f57f8" and, in some cache versions, bare 8-hex.
func parseHexAddrLoose(text string) (uint32, error) {
	t := strings.TrimSpace(text)
	if strings.HasPrefix(strings.ToLower(t), "0x") {
		t = t[2:]
	}
	return parseBareAddr(t)
}
