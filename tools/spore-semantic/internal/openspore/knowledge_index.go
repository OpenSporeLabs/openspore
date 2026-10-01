package openspore

import (
	"encoding/json"
	"fmt"
	"os"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// IndexDoc is the subset of reconstruction/knowledge/index.json this exporter
// projects. The document is read whole (it is ~9 MB); only the fields that
// reach a passport are decoded, so the reader cannot accidentally widen the
// exchange surface by adding a field to this struct.
type IndexDoc struct {
	Schema string `json:"$schema"`
	Binary struct {
		Architecture string `json:"architecture"`
		ImageBase    string `json:"image_base"`
		Program      string `json:"program"`
		GHIDRAProg   string `json:"ghidra_program"`
		SHA256       string `json:"sha256"`
		Version      string `json:"version"`
	} `json:"binary"`
	Records          map[string]*IndexRecord  `json:"records"`
	Packages         map[string]*IndexPackage `json:"packages"`
	SemanticFamilies []struct {
		Family        string   `json:"family"`
		Members       []string `json:"members"`
		SourceWorkers []string `json:"source_workers"`
	} `json:"semantic_families"`
	InputHashes map[string]string `json:"input_hashes"`
}

// IndexRecord is one record of the knowledge projection.
type IndexRecord struct {
	VA                 string          `json:"va"`
	Name               *string         `json:"name"`
	NormalizedSymbol   *string         `json:"normalized_symbol"`
	Subsystem          *string         `json:"subsystem"`
	EvidenceLevel      *string         `json:"evidence_level"`
	Status             *string         `json:"status"`
	SemanticStatus     *string         `json:"semantic_status"`
	ReviewStatus       *string         `json:"review_status"`
	IntegrationStatus  *string         `json:"integration_status"`
	Reconstructed      *bool           `json:"reconstructed"`
	Blocked            *bool           `json:"blocked"`
	RuntimeGated       *bool           `json:"runtime_gated"`
	RuntimeValidated   *int            `json:"runtime_validated"`
	Package            *string         `json:"package"`
	ClassType          *string         `json:"class_type"`
	Cluster            *string         `json:"cluster"`
	Globals            []string        `json:"globals"`
	Types              []string        `json:"types"`
	VTables            []string        `json:"vtables"`
	Semantic           *SemanticRecord `json:"semantic"`
	ABI                json.RawMessage `json:"abi"`
	IdentityResolution *struct {
		CanonicalVA string `json:"canonical_va"`
		Rule        string `json:"rule"`
		Requested   []struct {
			VA     string `json:"va"`
			Offset int    `json:"offset"`
		} `json:"requested"`
	} `json:"identity_resolution"`
	IdentityRefuted *semantic.RefutedIdentity `json:"identity_refuted"`
	Source          *struct {
		Files    []string `json:"files"`
		Handoffs []string `json:"handoffs"`
		Metadata []string `json:"metadata"`
	} `json:"source"`
	Triage *struct {
		Name       *string `json:"name"`
		Cluster    *string `json:"cluster"`
		Category   *string `json:"category"`
		Priority   *string `json:"priority"`
		Evidence   *string `json:"evidence"`
		Provenance *struct {
			Classifier *string `json:"classifier"`
			Snapshot   *string `json:"snapshot"`
		} `json:"provenance"`
	} `json:"triage"`
	Runtime *struct {
		BlockingReason json.RawMessage `json:"blocking_reason"`
		Validated      *int            `json:"validated"`
	} `json:"runtime"`
	UnresolvedQuestions []string `json:"unresolved_questions"`
}

// SemanticRecord is the semantic-interpretation block of a knowledge record.
// SemanticRecord is the semantic-interpretation block of a knowledge record.
//
// Several fields (package, readiness, interfaces, invariants, state_events,
// contradictions) are OBJECTS whose shape varies per record -- package is a
// caveat document, readiness is a readiness object. They are decoded as
// json.RawMessage and deliberately NOT projected: projecting them would put a
// record-shape guess in the exchange format, and the passport already carries
// the fields a cross-project lookup actually needs. Nothing else in the
// exchange reads them.
type SemanticRecord struct {
	Name              *string                    `json:"name"`
	VA                *string                    `json:"va"`
	Subsystem         *string                    `json:"subsystem"`
	Category          *string                    `json:"category"`
	Family            *string                    `json:"family"`
	Classification    *string                    `json:"classification"`
	Triangulation     *string                    `json:"triangulation_status"`
	DownstreamUnlocks *int                       `json:"downstream_unlock_count"`
	Confidence        map[string]json.RawMessage `json:"confidence"`
	Evidence          []SemanticEvidence         `json:"evidence"`
	Unresolved        []string                   `json:"unresolved_questions"`
	Source            *string                    `json:"source"`

	Package        json.RawMessage `json:"package"`
	Readiness      json.RawMessage `json:"readiness"`
	Interfaces     json.RawMessage `json:"interfaces"`
	Invariants     json.RawMessage `json:"invariants"`
	StateEvents    json.RawMessage `json:"state_events"`
	Contradictions json.RawMessage `json:"contradictions"`
}

// SemanticEvidence is one labelled claim inside a semantic record.
type SemanticEvidence struct {
	Claim  string `json:"claim"`
	Class  string `json:"class"`
	Source string `json:"source"`
}

// IndexPackage is one campaign package.
type IndexPackage struct {
	ID             string   `json:"id"`
	Package        string   `json:"package"`
	Status         string   `json:"status"`
	SrcPackage     string   `json:"src_package"`
	SourceOwner    string   `json:"source_owner"`
	CanonicalFiles []string `json:"canonical_files"`
	FunctionCount  int      `json:"function_count"`
	Readiness      string   `json:"readiness"`
}

// LoadIndex reads reconstruction/knowledge/index.json.
func LoadIndex(root string) (*IndexDoc, []Absent, []Digest, error) {
	path := root + "/" + RelIndex
	if !FileExists(path) {
		return nil, []Absent{{
			Path:   RelIndex,
			Reason: "not present in this checkout; reconstruction metadata, semantic interpretation, packages and validation pointers are unavailable",
		}}, nil, nil
	}
	raw, err := os.ReadFile(path)
	if err != nil {
		return nil, nil, nil, err
	}
	var doc IndexDoc
	if err := json.Unmarshal(raw, &doc); err != nil {
		return nil, nil, nil, fmt.Errorf("%s: %w", RelIndex, err)
	}
	dg, err := FileDigest(root, path)
	if err != nil {
		return nil, nil, nil, err
	}
	return &doc, nil, []Digest{dg}, nil
}

// NamesLikeRenderWare reports whether any of the record's own names carry the
// RenderWare SDK namespace prefix.
func (r *IndexRecord) NamesLikeRenderWare() bool {
	if r == nil {
		return false
	}
	for _, p := range []*string{r.Name, r.NormalizedSymbol} {
		if p != nil && strings.HasPrefix(*p, "RenderWare::") {
			return true
		}
	}
	return false
}

// SubsystemSource names which of the knowledge index's three fallback inputs
// supplied records[va].subsystem. tools/reconstruction_knowledge.py resolves
// it as manifest functions[].subsystem, else the triage queue's subsystem, else
// semantic-decomp. Because those three carry different vocabularies, the
// passport reports which one won instead of presenting a bare string.
func (r *IndexRecord) SubsystemSource() *string {
	if r == nil || r.Subsystem == nil {
		return nil
	}
	if r.Triage != nil && r.Triage.Cluster != nil {
		// The triage row is only consulted when the manifest has no subsystem,
		// which the index cannot record. A dotted name is the manifest's
		// convention; a single word is the triage vocabulary's.
		if strings.Contains(*r.Subsystem, ".") {
			return semantic.StrPtr("manifest_function")
		}
		return semantic.StrPtr("triage_queue")
	}
	return semantic.StrPtr("reconstruction_knowledge_index")
}
