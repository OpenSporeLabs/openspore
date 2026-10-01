package semantic

import "encoding/json"

// Schema identifiers written into, and accepted from, a snapshot.
const (
	SnapshotSchema = "spore-semantic-snapshot-1"
	SnapshotFile   = "function-passport-v1.jsonl"
)

// Record-kind discriminators for the JSON Lines stream.
const (
	RecordMetadata = "metadata"
	RecordFunction = "function"
)

// Tri-state vocabulary.
//
// Every optional fact group is published as an Envelope. A group with
// state=StateUnavailable and a non-nil reason is an explicit statement that
// OpenSpore looked and did not find the fact -- which is not the same as
// OpenSpore never having looked. The vocabulary is the one the evidence packs
// already use (availability / evidence_state / evidence_level), reproduced
// rather than re-invented.
const (
	StateAvailable   = "available"
	StateUnavailable = "unavailable"
)

const (
	EvidenceLive      = "LIVE"
	EvidenceDerived   = "DERIVED"
	EvidencePersisted = "PERSISTED"
	EvidenceMissing   = "MISSING"
)

// EvidenceLevel is OpenSpore's shared confidence scale
// (knowledgegraph/scale.py::EV_ORDER, mirrored by abi_infer.CONFIDENCE_ORDER).
// UNKNOWN is a real value, not an omitted field.
type EvidenceLevel string

const (
	LevelUnknown   EvidenceLevel = "UNKNOWN"
	LevelApprox    EvidenceLevel = "APPROXIMATION"
	LevelInferred  EvidenceLevel = "INFERRED"
	LevelSupported EvidenceLevel = "SUPPORTED"
	LevelObserved  EvidenceLevel = "OBSERVED"
	LevelConfirmed EvidenceLevel = "CONFIRMED"
	LevelVerified  EvidenceLevel = "VERIFIED"
)

// KnownEvidenceLevel reports whether s is a member of the shared scale.
// Consumers get an explicit "not in the vocabulary" rather than a silent pass,
// because a future scale extension must not be misread as today's maximum.
func KnownEvidenceLevel(s string) bool {
	switch EvidenceLevel(s) {
	case LevelUnknown, LevelApprox, LevelInferred, LevelSupported,
		LevelObserved, LevelConfirmed, LevelVerified:
		return true
	}
	return false
}

// Envelope wraps one optional fact group with its own provenance, so a
// consumer can answer "why does OpenSpore believe this?" per group rather than
// per document.
//
// Invariants, which the encoder relies on to keep the file small:
//
//   - state == "unavailable" implies evidence_level == UNKNOWN and
//     evidence_state == MISSING. Those two are always emitted anyway, because
//     a consumer scanning for an explicit UNKNOWN must find one; they are not
//     derivable-and-omitted.
//   - value is OMITTED when unavailable and PRESENT when available. A JSON
//     null would be a weaker statement than state:"unavailable", and an empty
//     object skeleton would be a lie about what was searched.
//   - provenance is omitted when the group carries none, and reason is omitted
//     when the group is available. An UNAVAILABLE envelope deliberately carries
//     no provenance list: the provenance of a non-finding is fully determined by
//     its reason code (the closed vocabulary below maps each code to the
//     artifact that was consulted), and repeating five long repo paths on all
//     59k records would cost ~21 MB to say nothing that is not already implied.
//     An AVAILABLE envelope always carries its provenance list.
//
// Reason codes are a CLOSED vocabulary. The prose explanations live in
// docs/tooling/semantic-exchange.md, not repeated on all 59k records; a source
// that supplied its own reason text (an evidence pack's `reason`) is carried
// verbatim instead of being reduced to a code.
type Envelope[T any] struct {
	State         EvidenceLevelState `json:"state"`
	EvidenceLevel EvidenceLevel      `json:"evidence_level"`
	EvidenceState string             `json:"evidence_state"`
	Provenance    []string           `json:"provenance,omitempty"`
	Reason        string             `json:"reason,omitempty"`
	Value         *T                 `json:"value,omitempty"`
}

// EvidenceLevelState is the availability half of the envelope. It is a
// separate named type purely so the two axes cannot be swapped by accident.
type EvidenceLevelState = string

// Closed vocabulary of reason codes for explicit absences. A code says WHAT
// OpenSpore looked for and did not find; it never encodes a guess about what
// the answer would have been.
const (
	// ReasonNoEvidencePack: no evidence pack exists for this VA, so no ABI
	// inference record was ever derived.
	ReasonNoEvidencePack = "no_evidence_pack"
	// ReasonNoABIDerived: a pack exists but carries no abi_derived value.
	ReasonNoABIDerived = "no_abi_derived_record"
	// ReasonNoVTableMembership: neither the sound vftable scan nor the triage
	// vtable index associates a table with this function.
	ReasonNoVTableMembership = "no_vtable_membership"
	// ReasonVTableScanAbsent: the sound vftable scan is not in the exporting
	// checkout, so vtable membership could not be consulted at all.
	ReasonVTableScanAbsent = "vftable_scan_absent"
	// ReasonNoGlobalRefs: the knowledge index records no global reference.
	ReasonNoGlobalRefs = "no_global_references"
	// ReasonNoTypes: the knowledge index associates no type.
	ReasonNoTypes = "no_associated_types"
	// ReasonNoSemanticRecord: no semantic research record exists.
	ReasonNoSemanticRecord = "no_semantic_record"
	// ReasonNoReconstruction: no package, staged source, validation report or
	// promotion record exists.
	ReasonNoReconstruction = "no_reconstruction_package"
	// ReasonNoValidation: a reconstruction exists but carries no validation
	// report.
	ReasonNoValidation = "no_validation_report"
	// ReasonSourceSupplied: the source artifact stated its own reason; the
	// reason string is that text, verbatim.
	ReasonSourceSupplied = "source_supplied"
)

// Unavailable builds an explicit-absence envelope: OpenSpore looked, found
// nothing, and says so. reasonCode is never empty -- an unexplained absence
// would be indistinguishable from a bug in the exporter.
// provenance is accepted and ignored for an unavailable group; it is retained
// in the signature so call sites read the same either way, and so a future
// source-supplied absence can opt into carrying it.
func Unavailable[T any](reasonCode string, _ ...string) Envelope[T] {
	return Envelope[T]{
		State:         StateUnavailable,
		EvidenceLevel: LevelUnknown,
		EvidenceState: EvidenceMissing,
		Reason:        reasonCode,
		Value:         nil,
	}
}

// Available builds a present-fact envelope.
func Available[T any](value T, level EvidenceLevel, evidenceState string, provenance ...string) Envelope[T] {
	v := value
	return Envelope[T]{
		State:         StateAvailable,
		EvidenceLevel: level,
		EvidenceState: evidenceState,
		Provenance:    provenance,
		Value:         &v,
	}
}

// IsAvailable reports whether the group carries a value.
//
// It requires BOTH the state and a non-nil value, not just the state: a file
// claiming state:"available" while omitting "value" is malformed, and treating
// that as a present fact would turn a corrupt snapshot into confident
// nonsense.
func (e Envelope[T]) IsAvailable() bool { return e.State == StateAvailable && e.Value != nil }

// Deref returns the group's value, or the zero value when it is unavailable.
// Callers that need to distinguish must check IsAvailable first.
func (e Envelope[T]) Deref() T {
	var zero T
	if e.Value == nil {
		return zero
	}
	return *e.Value
}

// ---------------------------------------------------------------------------
// FunctionPassport
// ---------------------------------------------------------------------------

// EvidenceBlock locates the per-function artifacts behind the facts on this
// passport.
//
// Every field is a pointer. A nil pointer is an EXPLICIT statement that the
// exporter looked for that artifact under reconstruction/evidence/<bare8>/ and
// it is not there -- not an omission, and not a claim that the fact is false.
// It replaces inferring pack existence from provenance text, which silently
// undercounts packs whose provenance list happens to omit the index entry.
type EvidenceBlock struct {
	// Pack is the repo-relative evidence.json path.
	Pack *string `json:"pack"`
	// PackState is the pack's own evidence_state (LIVE / DERIVED / PERSISTED).
	PackState *string `json:"pack_state"`
	// PackContentSHA256 is the pack's self-digest: SHA-256 over its canonical
	// JSON with content_sha256 set to null. It pins exactly which bytes OpenSpore
	// projected from.
	PackContentSHA256 *string `json:"pack_content_sha256"`
	// TargetAddressKind is the pack's own statement of what its target
	// addresses are ("linked_va" in every current pack).
	TargetAddressKind *string `json:"target_address_kind"`
	// ValidationReport and PromotionRecord locate the sibling artifacts in the
	// same directory.
	ValidationReport *string `json:"validation_report"`
	PromotionRecord  *string `json:"promotion_record"`

	// AdditionalPacks are evidence packs whose own VA is NOT a function entry
	// but which resolve into this entry's body. They are attached here, with the
	// rule and offset that moved them, so the knowledge is reachable instead
	// of being orphaned in a directory no passport key matches.
	AdditionalPacks []AdditionalPack `json:"additional_packs,omitempty"`
}

// AdditionalPack is an evidence pack filed under a non-entry address.
type AdditionalPack struct {
	Pack              string  `json:"pack"`
	RequestedVA       string  `json:"requested_va"`
	Offset            int     `json:"offset"`
	Rule              string  `json:"rule"`
	PackState         *string `json:"pack_state"`
	PackContentSHA256 *string `json:"pack_content_sha256"`
}

// Passport is one function's exchange record: the whole of what OpenSpore
// knows about one canonical function entry, in a shape a sibling project can
// consume without reading OpenSpore.
//
// Field order below IS the JSON field order. Encoding uses struct order
// (never a map) so that byte-for-byte output is stable across runs and Go
// versions.
type Passport struct {
	Record string `json:"record"`

	Identity       IdentityBlock                 `json:"identity"`
	Names          NamesBlock                    `json:"names"`
	Classification ClassificationBlock           `json:"classification"`
	ABI            Envelope[ABIBlock]            `json:"abi"`
	VTable         Envelope[VTableBlock]         `json:"vtable"`
	Graph          GraphBlock                    `json:"graph"`
	Globals        Envelope[[]string]            `json:"globals"`
	Types          Envelope[[]string]            `json:"types"`
	Semantics      Envelope[SemanticsBlock]      `json:"semantics"`
	Reconstruction Envelope[ReconstructionBlock] `json:"reconstruction"`
	Evidence       EvidenceBlock                 `json:"evidence"`
	Provenance     []ProvenanceEntry             `json:"provenance,omitempty"`
}

// IdentityBlock is the mechanical identity of the function. Every field here
// is either always present or an explicitly optional pointer -- no zero value
// is ever allowed to stand for "unknown".
type IdentityBlock struct {
	CanonicalVA string `json:"canonical_va"`
	RVA         string `json:"rva"`
	// Size is the Ghidra function body size in bytes (functions.tsv column 3,
	// a decimal integer). Zero means the artifact stated zero, which the
	// pinned universe never does; SizeKnown distinguishes the two.
	Size      int    `json:"size"`
	SizeKnown bool   `json:"size_known"`
	IsThunk   bool   `json:"is_thunk"`
	Section   string `json:"section"`

	// Requested lists non-entry addresses OpenSpore has already resolved to
	// this entry, with their byte offsets. Sorted by VA. Empty when none.
	Requested []RequestedAddr `json:"requested,omitempty"`
	// IdentityResolution names the rule that produced Requested, or null when
	// no resolution happened. The lookup command recomputes resolution itself
	// and reports it separately as the lookup-level identity_resolution.
	IdentityResolution *IdentityResolution `json:"identity_resolution"`
}

// RequestedAddr is one address that OpenSpore mapped onto this entry.
type RequestedAddr struct {
	VA     string `json:"va"`
	Offset int    `json:"offset"`
}

// IdentityResolution records the canonical-identity correction OpenSpore has
// itself already applied to this VA: which rule fired, which entry it resolved
// to, and every non-entry address that was moved there.
//
// It is emitted only when a correction happened. Its presence is itself the
// signal that the identity was changed, which is why a record that was already
// a function entry has no such key at all.
type IdentityResolution struct {
	Rule        string          `json:"rule"`
	CanonicalVA string          `json:"canonical_va"`
	Requested   []RequestedAddr `json:"requested"`
}

// CanonicalIdentityRule is the verbatim rule name emitted by
// tools/reconstruction_knowledge.py for a resolved interior address.
const CanonicalIdentityRule = "containing_function_entry"

// NamesBlock keeps the four name spaces apart. Collapsing them would lose the
// single most important provenance distinction in the whole exchange: a name
// the SDK declared is not a name OpenSpore derived, and a name a worker
// refuted is not a name anyone believes.
type NamesBlock struct {
	GhidraName       string  `json:"ghidra_name"`
	NormalizedSymbol *string `json:"normalized_symbol"`
	SDKName          *string `json:"sdk_name"`
	SDKNameSource    *string `json:"sdk_name_source,omitempty"`
	// IdentityRefuted is non-null when a worker metadata sidecar (schema
	// openspore-worker-metadata-1) overrode the SDK/triage-derived name.
	IdentityRefuted *RefutedIdentity `json:"identity_refuted"`
}

// RefutedIdentity is index.json's identity_refuted block: the record of a
// worker metadata sidecar overriding a name that OpenSpore had derived.
//
// Reason and Refuted are raw JSON, not strings or bools, because the single
// live instance carries an OBJECT keyed by failure mode
// ("decompiler_artefact_not_followed": {finding, evidence}). Flattening it to
// text would lose the key that says which failure mode fired.
type RefutedIdentity struct {
	Name             string          `json:"name"`
	Superseded       string          `json:"superseded"`
	SupersededSource string          `json:"superseded_source"`
	DeclaredBy       *string         `json:"declared_by"`
	Reason           json.RawMessage `json:"reason"`
	Refuted          json.RawMessage `json:"refuted"`
}

// ClassificationBlock is the triage classifier's view, plus the subsystem
// taxonomy. category / priority / evidence / cluster come from the triage
// JSONL; subsystem comes from the knowledge index's documented three-way
// fallback, which mixes dotted and single-word vocabularies by design.
type ClassificationBlock struct {
	Category   string   `json:"category"`
	Priority   string   `json:"priority"`
	Evidence   string   `json:"evidence"`
	Subsystem  *string  `json:"subsystem"`
	Cluster    *string  `json:"cluster"`
	SDKStructs []string `json:"sdk_structs,omitempty"`
	// RenderwareRole is non-null only when the triage classifier assigned the
	// RenderWare subsystem. The render-boundary research artifact is keyed by
	// boundary id rather than VA and is therefore not projected here.
	RenderwareRole *string `json:"renderware_role"`
	// SubsystemSource names which of the three fallback inputs supplied
	// Subsystem, so a mixed vocabulary is explainable rather than mysterious.
	SubsystemSource *string `json:"subsystem_source"`
}

// ABIBlock is the machine-derived ABI record projected onto decided fields
// only. Origin is always "abi_inference": these fields come from
// tools/reconstruction_tooling/abi_infer.py and are never re-derived here.
type ABIBlock struct {
	Origin string `json:"origin"`
	// Schema echoes the ABI engine's own record schema so a consumer can tell
	// which inference contract produced the values.
	Schema string `json:"schema"`

	// Convention is null when undetermined. There is no "UNKNOWN" sentinel and
	// no "none"; the ABI engine's vocabulary is
	// __cdecl/__stdcall/__thiscall/__fastcall.
	Convention           *string       `json:"convention"`
	ConventionConfidence EvidenceLevel `json:"convention_confidence"`
	Verdict              *string       `json:"verdict"`
	Completeness         *string       `json:"completeness"`

	Receiver      *ReceiverBlock `json:"receiver"`
	Cleanup       *CleanupBlock  `json:"cleanup"`
	Return        *ReturnBlock   `json:"return"`
	SRET          *SRETBlock     `json:"sret"`
	Variadic      *string        `json:"variadic"`
	StackArgSlots *int           `json:"stack_argument_slots"`
	SEHorCookie   *bool          `json:"seh_or_cookie_frame"`

	// Declared is the hand-authored ABI block from worker metadata. It is a
	// SEMANTIC INTERPRETATION and is kept out of the machine fields above so
	// a hand-written "__thiscall observed" is never mistaken for an inferred
	// convention.
	Declared *DeclaredABI `json:"declared"`
}

// ReceiverBlock projects abi_infer's receiver record. Present is a
// *TriBool: in the ABI engine `present: null` is a load-bearing known-unknown
// that blocks the C6/C9 rules and forces the record to abstain, so it must not
// be flattened to false.
type ReceiverBlock struct {
	Present        TriBool       `json:"present"`
	Register       *string       `json:"register"`
	Confidence     EvidenceLevel `json:"confidence"`
	Shape          *string       `json:"shape"`
	Provenance     *string       `json:"provenance"`
	BoundsOnly     *bool         `json:"bounds_only"`
	MaxOffset      *int          `json:"max_offset"`
	WrittenThrough *int          `json:"written_through"`
}

// CleanupBlock projects abi_infer's cleanup record. Side may be "callee",
// "caller", "CONFLICT" or null; "CONFLICT" is spelled uppercase by the engine
// and is not a member of the convention vocabulary.
type CleanupBlock struct {
	Side          *string       `json:"side"`
	Bytes         *int          `json:"bytes"`
	Confidence    EvidenceLevel `json:"confidence"`
	Corroboration *string       `json:"corroboration"`
	Evidence      *string       `json:"evidence"`
}

// ReturnBlock projects abi_infer's return record. Type is always null by the
// engine's own contract ("return.type is always null"), which is why it is a
// pointer rather than a string.
type ReturnBlock struct {
	Register          *string       `json:"register"`
	RegisterClass     *string       `json:"register_class"`
	Confidence        EvidenceLevel `json:"confidence"`
	Type              *string       `json:"type"`
	VoidPossible      *bool         `json:"void_possible"`
	BulkWriteEvidence *bool         `json:"bulk_write"`
}

// SRETBlock projects abi_infer's sret hypothesis record.
type SRETBlock struct {
	Present              TriBool       `json:"present"`
	Slot                 *int          `json:"slot"`
	Confidence           EvidenceLevel `json:"confidence"`
	Ambiguity            *string       `json:"ambiguity"`
	HypothesisConfidence EvidenceLevel `json:"hypothesis_confidence"`
}

// DeclaredABI is the free-form worker-declared ABI block from
// reconstruction/knowledge/index.json -> records[va].abi. Every field is
// prose written by a human or worker, so every field is a pointer.
type DeclaredABI struct {
	CallingConvention *string  `json:"calling_convention"`
	Architecture      *string  `json:"architecture"`
	HiddenReceiver    *string  `json:"hidden_receiver"`
	HiddenReceiverReg *string  `json:"hidden_this_register"`
	ReceiverRegister  *string  `json:"receiver_register"`
	HiddenThis        *bool    `json:"hidden_this"`
	ReturnRegister    *string  `json:"return_register"`
	ReturnType        *string  `json:"return_type"`
	ReturnSemantics   *string  `json:"return_semantics"`
	ReturnObservation *string  `json:"return_observation"`
	ReturnNote        *string  `json:"return_note"`
	ReturnWidthBytes  *int     `json:"return_width_bytes"`
	HiddenThisType    *string  `json:"hidden_this_type"`
	StackCleanupBytes *int     `json:"stack_cleanup_bytes"`
	StackCleanupOwner *string  `json:"stack_cleanup_owner"`
	StackArgSlots     *int     `json:"ordinary_stack_argument_slots"`
	Termination       *string  `json:"termination"`
	RetForm           *string  `json:"ret_form"`
	SavedRegisters    []string `json:"saved_registers"`
	Source            *string  `json:"source"`
}

// VTableBlock carries vftable membership. Memberships come from the sound
// scan that the ABI engine itself consumes (the only source that can state
// basis "vftable_predicate"); ABIAttributed is the engine's own conclusion.
type VTableBlock struct {
	Memberships   []VTableMembership `json:"memberships"`
	ABIAttributed *VTableAttribution `json:"abi_attributed"`
	// TriageAddresses is triage JSONL's vtable_addrs: which tables the triage
	// classifier associated with this function, with no slot. Kept separate
	// because it is a weaker, differently-sourced statement.
	TriageAddresses []string `json:"triage_addresses"`
	TriageFamily    *string  `json:"triage_family"`
}

// VTableMembership is one (table, slot) pair from the sound vftable scan.
type VTableMembership struct {
	TableVA string `json:"table_va"`
	Slot    int    `json:"slot"`
	// SlotWidth is the table's slot count when known (sound-scan `tables`).
	SlotWidth *int `json:"slot_width"`
}

// VTableAttribution is one of the ABI engine's VFT rules firing.
type VTableAttribution struct {
	Rule               string        `json:"rule"`
	TableVA            string        `json:"table_va"`
	Slot               int           `json:"slot"`
	Confidence         EvidenceLevel `json:"confidence"`
	ReceiverProvenance *string       `json:"receiver_provenance"`
	MembershipCount    *int          `json:"membership_count"`
}

// GraphBlock is the closure-validated call graph from
// knowledgegraph/triage/xrefs-2540f2ca.tsv. Callers and callees are sorted
// ascending and de-duplicated; ExternalCallees keeps the EXT tokens verbatim.
type GraphBlock struct {
	CallerCount          int      `json:"caller_count"`
	CalleeCount          int      `json:"callee_count"`
	Callers              []string `json:"callers,omitempty"`
	Callees              []string `json:"callees,omitempty"`
	ExternalCallees      []string `json:"external_callees,omitempty"`
	VTableReferenceCount int      `json:"vtable_reference_count"`
	DataReferenceCount   int      `json:"data_reference_count"`
	// SCCSize is triage's Tarjan component size; nil when the triage row did
	// not state one.
	SCCSize *int `json:"scc_size,omitempty"`
	// FanIn/FanOut are triage's own counters where available. They are
	// reproduced verbatim and may legitimately differ from the counts above,
	// which come from the pinned xref export.
	FanIn  *int `json:"fan_in,omitempty"`
	FanOut *int `json:"fan_out,omitempty"`
}

// SemanticsBlock is the SEMANTIC INTERPRETATION layer: research claims about
// what a function means. It is never merged with the machine facts above.
type SemanticsBlock struct {
	Classification    *string `json:"classification"`
	Status            *string `json:"semantic_status"`
	Name              *string `json:"name"`
	Subsystem         *string `json:"subsystem"`
	Triangulation     *string `json:"triangulation_status"`
	DownstreamUnlocks *int    `json:"downstream_unlock_count"`
	Source            *string `json:"source"`
	// Confidence is the per-axis map OpenSpore records (identity, mechanics,
	// ownership, persistence, runtime, events ...). The axis set is not
	// closed, and its values are MIXED: some axes carry a rung name
	// ("SUPPORTED"), others a numeric score (0.72). It is therefore carried as
	// raw JSON so neither spelling is coerced into the other. encoding/json
	// sorts map keys, so the encoding stays stable.
	Confidence          map[string]json.RawMessage `json:"confidence"`
	Evidence            []SemanticClaim            `json:"evidence"`
	Notes               []string                   `json:"notes"`
	UnresolvedQuestions []string                   `json:"unresolved_questions"`
	Family              *string                    `json:"semantic_family"`
	SourceWorkers       []string                   `json:"source_workers"`
}

// SemanticClaim is one labelled evidence item inside a semantic record.
type SemanticClaim struct {
	Claim  string `json:"claim"`
	Class  string `json:"class"`
	Source string `json:"source"`
}

// ReconstructionBlock is the campaign view: what was built, whether it
// promoted, and whether it was validated. RuntimeGated is deliberately
// distinct from "failed": an open gate means nothing was attempted.
type ReconstructionBlock struct {
	Package           *string `json:"package"`
	Status            *string `json:"status"`
	ReviewStatus      *string `json:"review_status"`
	IntegrationStatus *string `json:"integration_status"`
	Reconstructed     *bool   `json:"reconstructed"`
	Blocked           *bool   `json:"blocked"`
	Promoted          TriBool `json:"promoted"`
	PromotionSchema   *string `json:"promotion_schema"`
	// Supersedes is the previous promotion record's coordinates when this
	// promotion replaced one; raw JSON because that shape is an object.
	Supersedes       json.RawMessage `json:"promotion_supersedes"`
	StaticStatus     *string         `json:"static_status"`
	GeneratedSource  []string        `json:"generated_source"`
	Handoffs         []string        `json:"handoffs"`
	Metadata         []string        `json:"metadata"`
	RuntimeGated     *bool           `json:"runtime_gated"`
	RuntimeValidated *int            `json:"runtime_validated"`
	// RuntimeBlockingReason is raw JSON: index.json states it as a string for
	// 617 of 618 records and as a LIST for one. It is carried verbatim rather
	// than normalised into a shape the source does not have.
	RuntimeBlockingReason json.RawMessage    `json:"runtime_blocking_reason,omitempty"`
	Validation            *ValidationSummary `json:"validation"`
}

// ValidationSummary is the adjudicated per-dimension verdict from
// reconstruction/evidence/<bare8>/validation.json.
type ValidationSummary struct {
	Schema   string                     `json:"schema"`
	Coverage map[string]ValidationCheck `json:"coverage"`
	Runtime  *ValidationCheck           `json:"runtime"`
	// StaticRollup is coverage.aggregate from the same document. Its values
	// are mixed counters and a float ratio, so they are carried raw.
	StaticRollup map[string]json.RawMessage `json:"static_rollup"`
}

// ValidationCheck is one dimension verdict. Status vocabulary is
// PASS/WARN/FAIL/UNKNOWN/NOT_AVAILABLE and Coverage is none/partial/complete,
// both reproduced unchanged.
type ValidationCheck struct {
	Status   string   `json:"status"`
	Coverage string   `json:"coverage"`
	Detail   string   `json:"detail"`
	Evidence []string `json:"evidence"`
}

// ProvenanceEntry answers "why does OpenSpore believe this?" at document
// level, using the evidence packs' own vocabulary.
type ProvenanceEntry struct {
	Mode        string `json:"mode"`
	Ref         string `json:"ref"`
	SourceClass string `json:"source_class"`
}

// TriBool is a three-valued boolean. The zero value is meaningless, so every
// use is a pointer or an explicit tri-state constant -- a plain Go bool cannot
// express "we looked and it is unknown", and a plain string sentinel would
// invent a vocabulary the repository does not have.
type TriBool string

const (
	TriTrue  TriBool = "true"
	TriFalse TriBool = "false"
	TriNull  TriBool = "null"
)

// TriBoolOf converts a *bool, preserving an unknown as TriNull.
func TriBoolOf(p *bool) TriBool {
	if p == nil {
		return TriNull
	}
	if *p {
		return TriTrue
	}
	return TriFalse
}

// BoolPtr returns a *bool for a Go bool, for the many optional bool fields.
func BoolPtr(v bool) *bool { return &v }

// StrPtr returns a *string for a Go string.
func StrPtr(v string) *string { return &v }

// IntPtr returns a *int for a Go int.
func IntPtr(v int) *int { return &v }
