package openspore

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
)

// EvidencePack is the subset of reconstruction/evidence/<bare8>/evidence.json
// this exporter projects.
//
// The pack's category envelope --
// {availability, evidence_level, evidence_state, provenance, reason, value}
// -- is the shape the passport adopts for every optional fact group, so the
// consumer learns one vocabulary instead of five.
type EvidencePack struct {
	Schema        string `json:"schema"`
	EvidenceState string `json:"evidence_state"`
	ContentSHA256 string `json:"content_sha256"`
	Target        struct {
		VA          string `json:"va"`
		AddressKind string `json:"address_kind"`
	} `json:"target"`
	Categories map[string]EvidenceCategory `json:"categories"`
	Provenance []EvidenceProvenance        `json:"provenance"`
}

// EvidenceCategory is one pack category's envelope.
type EvidenceCategory struct {
	Availability  string          `json:"availability"`
	EvidenceLevel string          `json:"evidence_level"`
	EvidenceState string          `json:"evidence_state"`
	Provenance    []string        `json:"provenance"`
	Reason        *string         `json:"reason"`
	Value         json.RawMessage `json:"value"`
}

// EvidenceProvenance is one pack provenance entry.
type EvidenceProvenance struct {
	Mode        string `json:"mode"`
	Ref         string `json:"ref"`
	SourceClass string `json:"source_class"`
}

// ABIRecord is the subset of an "openspore-abi-inference-1" record that reaches
// a passport. The full record carries the rule graph, every observation and the
// abstention codes; none of that belongs in an exchange surface, so only the
// decided fields are decoded here.
type ABIRecord struct {
	Schema       string `json:"schema"`
	Verdict      string `json:"verdict"`
	Completeness string `json:"completeness"`
	Conventions  struct {
		CallingConvention    *string  `json:"calling_convention"`
		Confidence           string   `json:"confidence"`
		CandidateConventions []string `json:"candidate_conventions"`
		Corroboration        string   `json:"corroboration"`
	} `json:"conventions"`
	Receiver struct {
		Present        *bool   `json:"present"`
		Register       *string `json:"register"`
		Confidence     string  `json:"confidence"`
		Shape          *string `json:"shape"`
		Provenance     *string `json:"provenance"`
		BoundsOnly     *bool   `json:"bounds_only"`
		MaxOffset      *int    `json:"max_offset"`
		WrittenThrough *int    `json:"written_through"`
	} `json:"receiver"`
	Cleanup struct {
		Side          *string `json:"side"`
		Bytes         *int    `json:"bytes"`
		Confidence    string  `json:"confidence"`
		Corroboration *string `json:"corroboration"`
		Evidence      *string `json:"evidence"`
	} `json:"cleanup"`
	Return struct {
		Register          *string `json:"register"`
		RegisterClass     *string `json:"register_class"`
		Confidence        string  `json:"confidence"`
		Type              *string `json:"type"`
		VoidPossible      *bool   `json:"void_possible"`
		AggregateEvidence struct {
			BulkWrite bool `json:"bulk_write"`
		} `json:"aggregate_evidence"`
	} `json:"return"`
	SRET struct {
		Present              *bool   `json:"present"`
		Slot                 *int    `json:"slot"`
		Confidence           string  `json:"confidence"`
		Ambiguity            *string `json:"ambiguity"`
		HypothesisConfidence *string `json:"hypothesis_confidence"`
	} `json:"sret"`
	Variadic       *string `json:"variadic"`
	SEHorCookie    *bool   `json:"seh_or_cookie_frame"`
	StackArguments struct {
		ObservedSlots int    `json:"observed_slots"`
		DerivedSlots  int    `json:"derived_slots"`
		TotalSlots    int    `json:"total_bytes"`
		Confidence    string `json:"confidence"`
	} `json:"stack_arguments"`
	Inferences []struct {
		ID         string          `json:"id"`
		BasedOn    []string        `json:"based_on"`
		Rule       *string         `json:"rule"`
		Confidence string          `json:"confidence"`
		Value      json.RawMessage `json:"value"`
	} `json:"inferences"`
}

// VFTInference is the value shape of an R1-VFT / R2-VFT / V1-VFT inference.
type VFTInference struct {
	Table              string  `json:"table"`
	SlotIndex          *int    `json:"slot_index"`
	ReceiverProvenance *string `json:"receiver_provenance"`
	MembershipCount    *int    `json:"membership_count"`
	CleanupSide        *string `json:"cleanup_side"`
}

// VFTRules are the ABI engine's three vftable-membership rules.
var VFTRules = []string{"R1-VFT", "R2-VFT", "V1-VFT"}

// IsVFTRule reports whether id is one of the vftable-membership rules.
func IsVFTRule(id string) bool {
	for _, r := range VFTRules {
		if r == id {
			return true
		}
	}
	return false
}

// ValidationDoc is the subset of reconstruction/evidence/<bare8>/validation.json
// projected into a passport. Status and coverage vocabularies are reproduced
// unchanged.
type ValidationDoc struct {
	Schema string `json:"schema"`
	Checks map[string]struct {
		Status   string   `json:"status"`
		Coverage string   `json:"coverage"`
		Detail   string   `json:"detail"`
		Evidence []string `json:"evidence"`
	} `json:"checks"`
	Runtime *struct {
		Dimension string `json:"dimension"`
		Gated     bool   `json:"gated"`
		Status    string `json:"status"`
		Reason    string `json:"reason"`
		Validated int    `json:"validated"`
	} `json:"runtime"`
	Static *struct {
		Coverage map[string]json.RawMessage `json:"coverage"`
	} `json:"static"`
}

// PromotionRecord is the subset of reconstruction/evidence/<bare8>/promotion.json
// projected into a passport.
type PromotionRecord struct {
	Schema        string          `json:"schema"`
	VA            string          `json:"va"`
	Package       string          `json:"package"`
	SrcPackage    string          `json:"src_package"`
	Namespace     string          `json:"namespace"`
	Sources       []string        `json:"sources"`
	Headers       []string        `json:"headers"`
	StaticStatus  string          `json:"static_status"`
	RuntimeStatus string          `json:"runtime_status"`
	PromotedOn    string          `json:"promoted_on"`
	Provenance    []string        `json:"provenance"`
	Supersedes    json.RawMessage `json:"supersedes"`
}

// PerVAArtifacts bundles every per-function artifact that lives in
// reconstruction/evidence/<bare8>/. The directory name is the bare 8-hex
// spelling, which is what reconstruction/evidence/evidence.py writes
// (Path(root) / EVIDENCE_REL / normalize_va(va)[2:]).
type PerVAArtifacts struct {
	// Addr is the canonical function VA, taken from the directory name.
	Addr       uint32
	Evidence   *EvidencePack
	Validation *ValidationDoc
	Promotion  *PromotionRecord
	// RelPath is the repo-relative evidence.json path, for provenance.
	RelPath string
	// Extra holds packs whose own VA is not a function entry but which resolve
	// into this entry's body.
	Extra []AdditionalPackRecord
}

// AdditionalPackRecord mirrors semantic.AdditionalPack at the reader layer so
// the openspore package does not depend on the wire type.
type AdditionalPackRecord struct {
	Pack              string
	RequestedVA       string
	Offset            int
	Rule              string
	PackState         *string
	PackContentSHA256 *string
}

// LoadEvidence walks reconstruction/evidence/* and reads evidence.json,
// validation.json and promotion.json for each bare-8 directory.
//
// The directory listing is the only complete enumeration available:
// reconstruction/knowledge/coverage.json records 8 packs while 677 are on
// disk, so no committed manifest is trusted here.
func LoadEvidence(root string) (map[uint32]*PerVAArtifacts, []Absent, []Digest, error) {
	dir := root + "/" + RelEvidenceDir
	out := make(map[uint32]*PerVAArtifacts)
	if !DirExists(dir) {
		return out, []Absent{{
			Path:   RelEvidenceDir,
			Reason: "not present in this checkout; ABI inference records, validation verdicts and promotion records are unavailable",
		}}, nil, nil
	}

	names, err := os.ReadDir(dir)
	if err != nil {
		return nil, nil, nil, err
	}
	var digests []Digest
	for _, de := range names {
		if !de.IsDir() {
			continue
		}
		bare := de.Name()
		if len(bare) != 8 {
			continue
		}
		if _, err := parseBareAddr(bare); err != nil {
			continue
		}
		addr, _ := parseBareAddr(bare)
		sub := filepath.Join(dir, bare)

		art := &PerVAArtifacts{RelPath: RelEvidenceDir + "/" + bare + "/evidence.json"}
		if p := filepath.Join(sub, "evidence.json"); FileExists(p) {
			pack := &EvidencePack{}
			if err := readJSON(p, pack); err != nil {
				return nil, nil, nil, fmt.Errorf("%s: %w", RelEvidenceDir+"/"+bare+"/evidence.json", err)
			}
			art.Evidence = pack
			dg, err := FileDigest(root, p)
			if err != nil {
				return nil, nil, nil, err
			}
			digests = append(digests, dg)
		}
		if p := filepath.Join(sub, "validation.json"); FileExists(p) {
			doc := &ValidationDoc{}
			if err := readJSON(p, doc); err != nil {
				return nil, nil, nil, fmt.Errorf("%s: %w", RelEvidenceDir+"/"+bare+"/validation.json", err)
			}
			art.Validation = doc
		}
		if p := filepath.Join(sub, "promotion.json"); FileExists(p) {
			rec := &PromotionRecord{}
			if err := readJSON(p, rec); err != nil {
				return nil, nil, nil, fmt.Errorf("%s: %w", RelEvidenceDir+"/"+bare+"/promotion.json", err)
			}
			art.Promotion = rec
		}
		if art.Evidence == nil && art.Validation == nil && art.Promotion == nil {
			continue
		}
		if _, dup := out[addr]; dup {
			return nil, nil, nil, fmt.Errorf("%s: two artifact directories canonicalise to %08x", RelEvidenceDir, addr)
		}
		out[addr] = art
	}
	return out, nil, digests, nil
}

func readJSON(path string, into any) error {
	raw, err := os.ReadFile(path)
	if err != nil {
		return err
	}
	return json.Unmarshal(raw, into)
}
