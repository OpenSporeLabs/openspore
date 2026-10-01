package semantic

// BinaryIdentity is the cross-project join key. A snapshot is only valid for
// the exact binary it was produced from; consumers must match on
// binary_sha256 and may additionally check image_base.
type BinaryIdentity struct {
	SHA256       string `json:"binary_sha256"`
	ImageBase    string `json:"image_base"`
	Architecture string `json:"architecture"`
	Program      string `json:"program"`
	Version      string `json:"version"`
}

// ImageBaseAddr returns the image base as an Addr, or false when the snapshot
// did not state a usable one.
func (b BinaryIdentity) ImageBaseAddr() (Addr, bool) {
	text := CutPrefixAddr(b.ImageBase)
	if text == "" {
		return 0, false
	}
	v, err := ParseAddr(b.ImageBase, 0)
	if err != nil {
		return 0, false
	}
	return v, true
}

// Metadata is line 1 of the snapshot. It carries the binary identity, the
// schema version, the per-input digests that make the export reproducible, and
// the coverage counters.
//
// It deliberately carries NO timestamp. Determinism is a hard requirement, and
// a clock cannot be both written and excluded from the byte comparison; the
// reproducible identity of a snapshot is its content_sha256 over the record
// lines plus its inputs map, both of which are stable functions of repository
// state alone.
type Metadata struct {
	Record    string         `json:"record"`
	Schema    string         `json:"schema"`
	Binary    BinaryIdentity `json:"binary"`
	ImageBase Addr           `json:"-"`
	Generator Generator      `json:"generator"`

	// Inputs maps every repo-relative file the export read to its SHA-256.
	// Sorted by the encoder (it is emitted from a sorted slice).
	Inputs []InputDigest `json:"inputs"`

	// AbsentInputs names artifacts that are authoritative but were absent from
	// the exporting checkout. Listing them explicitly is what lets a consumer
	// tell "this snapshot has no vtable memberships" apart from "this snapshot
	// was built where the vftable scan does not exist".
	AbsentInputs []AbsentInput `json:"absent_inputs"`

	Counts        Counts `json:"counts"`
	ContentSHA256 string `json:"content_sha256"`

	// Export records facts about the WRITE, not about the records. These are
	// deliberately NOT in Counts: Counts is cross-checked against the record
	// bodies on load, and an export-side fact cannot be recomputed from them.
	Export ExportNotes `json:"export"`
}

// ExportNotes records what the export did that the record bodies cannot show.
type ExportNotes struct {
	// UniverseSource names which universe artifact supplied canonical identity.
	UniverseSource string `json:"universe_source"`
	// UniverseFallback is true when the git-ignored frozen Ghidra export was
	// absent and the git-tracked coverage ledger was used instead.
	UniverseFallback bool `json:"universe_fallback"`
	// EvidencePackDirsRead counts the reconstruction/evidence/<bare8>/
	// directories the export walked.
	EvidencePackDirsRead int `json:"evidence_pack_dirs_read"`
	// OrphanEvidencePacks counts evidence packs whose VA lies in no known
	// function body at all. They were read and hashed, and no passport can
	// reference them; reporting the number keeps that visible instead of
	// letting it look like they were skipped.
	OrphanEvidencePacks int `json:"orphan_evidence_packs"`
	// OrphanEvidencePackPaths lists them so a human can see which.
	OrphanEvidencePackPaths []string `json:"orphan_evidence_pack_paths"`
}

// Generator identifies the writer. The version is a constant of this program,
// not a build stamp, so it does not vary between two runs on one machine.
type Generator struct {
	Name    string `json:"name"`
	Version string `json:"version"`
}

// InputDigest is one file read during export.
type InputDigest struct {
	Path   string `json:"path"`
	SHA256 string `json:"sha256"`
	Bytes  int64  `json:"bytes"`
}

// AbsentInput names an authoritative artifact that was not present. The
// Reason is never empty: "not found at this path" is a statement a consumer
// can act on.
type AbsentInput struct {
	Path   string `json:"path"`
	Reason string `json:"reason"`
}

// AbsentInputEmpty forces an empty JSON array for the absent-input list, so two
// exports of the same repository state cannot disagree between null and [].
func (m *Metadata) AbsentInputEmpty() {
	m.AbsentInputs = []AbsentInput{}
}

// Counts are the coverage counters reported by `stats` and `validate`.
type Counts struct {
	Functions            int `json:"functions"`
	WithSDKName          int `json:"with_sdk_name"`
	WithABIData          int `json:"with_abi_data"`
	WithUnknownABI       int `json:"with_abi_unknown"`
	WithReceiver         int `json:"with_receiver"`
	WithReceiverUnknown  int `json:"with_receiver_unknown"`
	WithVTableMembership int `json:"with_vtable_membership"`
	WithVTableAttributed int `json:"with_vtable_attributed"`
	WithSubsystem        int `json:"with_subsystem"`
	WithRenderwareRole   int `json:"with_renderware_role"`
	WithReconstruction   int `json:"with_reconstruction_package"`
	WithPromoted         int `json:"with_promotion"`
	WithEvidencePack     int `json:"with_evidence_pack"`
	WithValidation       int `json:"with_validation"`
	WithSemantics        int `json:"with_semantics"`
	WithGlobals          int `json:"with_globals"`
	WithTypes            int `json:"with_types"`
	WithCallers          int `json:"with_callers"`
	WithCallees          int `json:"with_callees"`
	RefutedIdentities    int `json:"with_refuted_identity"`
	ResolvedInteriorVAs  int `json:"resolved_interior_addresses"`

	// AttachedStrayPacks counts evidence packs filed under a non-entry VA that
	// the canonical-identity rule placed inside a function body; they are
	// reachable through that entry's evidence.additional_packs. It IS
	// recomputable from the record bodies, so `validate` cross-checks it.
	AttachedStrayPacks int `json:"attached_stray_evidence_packs"`

	// ExplicitlyUnavailable counts the fact groups published as an explicit
	// absence (state=unavailable with a reason) rather than omitted. It is the
	// number that answers "how much of this snapshot is a stated 'we looked
	// and found nothing'".
	ExplicitlyUnavailable int `json:"explicitly_unavailable"`
	// TotalFactGroups is the denominator for the ratio above.
	TotalFactGroups int `json:"total_fact_groups"`
}

// Generator constants.
const (
	GeneratorName    = "spore-semantic"
	GeneratorVersion = "1"
)
