// Package runtime defines the RUNTIME OVERLAY: an external, read-only record
// of what actually executed in the analysed binary.
//
// The relationship to the static snapshot is the whole point of this package:
//
//	FunctionPassport   -- what OpenSpore knows from static analysis
//	RuntimeOverlay     -- what some other project observed while executing
//
// Both are keyed by binary_sha256 + canonical VA. Neither ever writes the
// other. An overlay is DATA: nothing here executes, links or imports anything a
// producer supplies, and no runtime fact can change a static verdict.
//
// Format: JSON Lines, deliberately the same shape as the static snapshot.
// Line 1 is the metadata record; lines 2..N are entry records sorted strictly
// ascending by requested_va. metadata.content_sha256 covers the entry lines
// only, so the header stays first and a consumer can check binary identity
// before parsing the body, without the digest being self-referential.
//
// The stream carries no timestamp, no PID, no absolute path and no host name.
// Two overlays built from the same producer report are byte-identical, which is
// what makes the artifact diffable across producer runs.
package runtime

import (
	"encoding/json"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// Schema identifier written into, and accepted from, an overlay.
const (
	// OverlaySchema is the only schema id this build implements. A different id
	// is refused rather than partially read, for the same reason the static
	// snapshot refuses one: a consumer must not read a future contract as if it
	// were today's.
	OverlaySchema = "spore-semantic-runtime-overlay-1"
	// OverlayFile is the conventional filename. It is not a default lookup
	// path: an overlay always arrives from outside, so its location is the
	// caller's decision.
	OverlayFile = "runtime-overlay-v1.jsonl"
	// CensusSchema is the blocker census projection, read by `runtime frontier`.
	// The census is OpenSpore-side and stays OUT of the overlay, because it is
	// static knowledge about blockers, not something a producer observed.
	CensusSchema = "openspore-runtime-blocker-census-1"
	// CensusFile is the conventional census filename.
	CensusFile = "blocker-census-v1.json"
)

// Record-kind discriminators, mirroring semantic.RecordMetadata/RecordFunction.
const (
	RecordMetadata = "metadata"
	RecordEntry    = "entry"
	RecordCensus   = "census"
)

// Tri-state vocabulary, reused from the static snapshot rather than re-invented
// so a consumer learns one rule for both halves of the join.
//
// The load-bearing distinction this package exists to preserve:
//
//	"true"      observed to be true
//	"false"     observed to be false
//	"null"      the producer did not observe or state it
//
// A producer that did not watch an import is not the same as a producer that
// watched it and saw it not called. Collapsing the two is how a runtime
// observation becomes a fabricated negative.
const (
	TriTrue  = semantic.TriTrue
	TriFalse = semantic.TriFalse
	TriNull  = semantic.TriNull
)

// CanonicalizationKind is the closed vocabulary describing how a requested VA
// was related to function identity. The three values are verbatim the
// ResolutionKind vocabulary of internal/index, because this package must not
// define a second identity scheme: index.Resolve is the authority, and these
// names exist only so a producer's claim can be COMPARED with it.
const (
	// CanonicalEntry: the requested VA is itself a function entry.
	CanonicalEntry = "function_entry"
	// CanonicalInterior: the requested VA is inside a known function body.
	CanonicalInterior = "containing_function_entry"
	// CanonicalNonEntity: the requested VA is neither an entry nor inside a
	// body -- inter-body padding, or outside the image entirely. Padding is
	// never mapped to a function.
	CanonicalNonEntity = "non_function_entity"
	// CanonicalUnknown: the producer stated no canonicalization at all.
	CanonicalUnknown = "not_stated"
)

// KnownCanonicalization reports whether s is a member of the closed vocabulary.
func KnownCanonicalization(s string) bool {
	switch s {
	case CanonicalEntry, CanonicalInterior, CanonicalNonEntity, CanonicalUnknown:
		return true
	}
	return false
}

// ObservationKind is the closed vocabulary of typed runtime observations.
//
// The kinds are TYPED rather than one free-form blob, for two reasons. A blob
// would make "the producer observed an import" and "the producer emitted the
// word import in a log line" indistinguishable; and it would force the loader
// to trust producer-supplied field names for addresses it is supposed to check.
type ObservationKind string

const (
	ObsEntry        ObservationKind = "entry"
	ObsCall         ObservationKind = "call"
	ObsIndirectCall ObservationKind = "indirect_call"
	ObsReturn       ObservationKind = "return"
	ObsImport       ObservationKind = "import"
	ObsException    ObservationKind = "exception"
	ObsMemory       ObservationKind = "memory"
	ObsRegister     ObservationKind = "register"
	ObsStack        ObservationKind = "stack"
)

// ObservationKinds lists the vocabulary in declaration order. It is the closed
// set: an unknown kind is a schema this build does not implement.
var ObservationKinds = []ObservationKind{
	ObsEntry, ObsCall, ObsIndirectCall, ObsReturn,
	ObsImport, ObsException, ObsMemory, ObsRegister, ObsStack,
}

// KnownObservationKind reports whether k is a member of the closed vocabulary.
func KnownObservationKind(k ObservationKind) bool {
	for _, v := range ObservationKinds {
		if v == k {
			return true
		}
	}
	return false
}

// AccessMode is the closed vocabulary for a memory observation's direction.
const (
	AccessRead  = "read"
	AccessWrite = "write"
)

// ---------------------------------------------------------------------------
// Metadata (line 1)
// ---------------------------------------------------------------------------

// Metadata is line 1 of an overlay. It carries binary identity and producer
// identity, and nothing else that could vary between two runs of the same
// producer: no timestamp, no host, no absolute path.
//
// It carries no timestamp for the same reason semantic.Metadata does. A clock
// cannot be both written into the file and excluded from a byte comparison, so
// an overlay with a timestamp could not be diffed against itself across two
// producer runs -- which is precisely the check an evidence artifact needs.
type Metadata struct {
	Record   string                  `json:"record"`
	Schema   string                  `json:"schema"`
	Binary   semantic.BinaryIdentity `json:"binary"`
	Producer Producer                `json:"producer"`

	// Counts are the producer's own tallies over the entry lines. They are
	// cross-checked against the loaded body by Verify(), exactly as the static
	// snapshot's counters are, so a hand-edited header is caught even when the
	// content digest still matches.
	Counts Counts `json:"counts"`

	// ContentSHA256 is SHA-256 over the entry lines only, each terminated by a
	// newline. Empty means the producer stated no digest and verification of it
	// is skipped -- allowed, and reported as such, because the binary digest is
	// the identity that actually matters and it is mandatory.
	ContentSHA256 string `json:"content_sha256"`
}

// Producer identifies who generated the overlay. Cross-project traceability
// lives here and in each entry's provenance; nothing else names a producer.
//
// Artifact is a PORTABLE identifier -- a repo-relative path such as
// "work/reports/startup-recovery14.json" -- and never an absolute filesystem
// path. An absolute path would make the overlay non-portable and would embed
// one machine's directory layout into another project's artifact, and it would
// also vary between two runs on two machines, breaking byte-identity.
type Producer struct {
	Project  string `json:"project"`
	Name     string `json:"name"`
	Version  string `json:"version"`
	Artifact string `json:"artifact"`
	// SourceSchema is the producer's OWN report schema id, when it has one. It
	// lets a consumer tell "this overlay was adapted from producer schema X"
	// from "this overlay was produced directly", which matters because an
	// adapter and a direct producer can differ in what "not observed" means.
	SourceSchema string `json:"source_schema"`
}

// Counts are the overlay's own tallies, recomputed on load.
type Counts struct {
	Entries          int `json:"entries"`
	Reached          int `json:"reached"`
	ReachedUnknown   int `json:"reached_unknown"`
	NotReached       int `json:"not_reached"`
	TotalEntryCount  int `json:"total_entry_count"`
	RuntimeOnly      int `json:"runtime_only"`
	RuntimeCallers   int `json:"runtime_callers"`
	RuntimeTargets   int `json:"runtime_targets"`
	RuntimeImports   int `json:"runtime_imports"`
	Observations     int `json:"observations"`
	Exceptions       int `json:"exceptions"`
	DistinctProducer int `json:"distinct_producers"`
}

// ---------------------------------------------------------------------------
// Entry (lines 2..N)
// ---------------------------------------------------------------------------

// Entry is one address a producer observed, plus everything it stated about
// what happened there.
//
// Every field is either a required scalar or an explicit tri-state. Nothing is
// omitted to mean "unknown": an absent runtime fact is a null or an empty list,
// and the two are different statements (see the tri-state note above).
//
// Field order below IS the JSON field order; encoding never uses a map, so
// byte-for-byte output is stable across runs and Go versions.
type Entry struct {
	Record string `json:"record"`

	// RequestedVA is the address the producer observed, verbatim, in canonical
	// "0x%08x" spelling. It is required and is never rewritten. An overlay that
	// only stored canonical VAs could not represent a runtime-only address.
	RequestedVA string `json:"requested_va"`

	// CanonicalVA is the producer's own canonicalization, or null when it
	// established none. It is a CLAIM, not the join decision: when a static
	// snapshot is available the join recomputes identity itself and reports any
	// disagreement rather than preferring either side.
	CanonicalVA *string `json:"canonical_va"`

	// Canonicalization names the rule the producer applied. NotStated means the
	// producer supplied only RequestedVA, which is the common case for an
	// address the producer has no reason to believe is a function.
	Canonicalization string `json:"canonicalization"`

	// CanonicalOffset is the byte offset into the containing body. Non-null only
	// when Canonicalization is CanonicalInterior.
	CanonicalOffset *int `json:"canonical_offset"`

	// Reached is the tri-state "did the original process execute this address".
	Reached semantic.TriBool `json:"reached"`

	// EntryCount is how many times the address was entered. Non-null means the
	// producer counted; null means it did not count. Zero is a real observation
	// and is reported as such.
	EntryCount *int `json:"entry_count"`

	// FirstReachedFrom is the address of the first entry into this one.
	FirstReachedFrom *string `json:"first_reached_from"`

	// MaxCallDepth is the deepest observed call stack at this address, or null
	// when the producer did not track depth.
	MaxCallDepth *int `json:"max_call_depth"`

	// RuntimeCallers, RuntimeTargets and RuntimeImports are always present as
	// arrays, never null, so "the producer looked and found none" ([]) is
	// distinguishable from "the producer had nothing to say" (which the
	// producer signals by omitting the whole entry). They are sorted ascending
	// and de-duplicated.
	RuntimeCallers []RuntimeCaller    `json:"runtime_callers"`
	RuntimeTargets []RuntimeTarget    `json:"runtime_targets"`
	RuntimeImports []RuntimeImportRef `json:"runtime_imports"`

	// Observations are typed facts, sorted by (kind, sequence, callsite) so the
	// ordering is total and the file diffs cleanly. Never null.
	Observations []Observation `json:"observations"`

	// Provenance says which producer artifact this entry came from. It is
	// REQUIRED and never empty: an observation with no attributable producer is
	// not evidence, it is an assertion.
	Provenance []ProvenanceEntry `json:"provenance"`
}

// RuntimeCaller is one observed caller edge into this address.
//
// CallsiteVA is separate from CallerFunctionVA because a callsite and the
// function containing it are different facts: the callsite is where the transfer
// happened, the function is OpenSpore's identity for the code around it. A
// producer that only knows one of them says so by nulling the other.
type RuntimeCaller struct {
	CallerFunctionVA *string `json:"caller_function_va"`
	CallsiteVA       string  `json:"callsite_va"`
	// Count is the number of observed transfers on this edge. Non-nil only when
	// the producer counted edges separately from entries.
	Count *int `json:"count"`
	// MinDepth and MaxDepth bound the observed stack depth. Non-nil only when
	// the producer tracked depth.
	MinDepth *int `json:"min_depth"`
	MaxDepth *int `json:"max_depth"`
}

// RuntimeTarget is one observed transfer FROM this address.
type RuntimeTarget struct {
	TargetVA string `json:"target_va"`
	// Indirect is tri-state. "true" means the producer established the target
	// came from an indirect (vtable or memory) dispatch rather than a direct
	// call; "false" means direct; "null" means the producer did not say. This is
	// the single most valuable field for the vftable questions OpenSpore cannot
	// settle statically, and it must not be inferred from the target's address.
	Indirect semantic.TriBool `json:"indirect"`
	// Unresolved is tri-state and means the producer had no recovered code at
	// TargetVA. That is the state OpenSpore's static universe cannot reach at
	// all, and it is why an overlay can carry addresses the snapshot cannot.
	Unresolved semantic.TriBool `json:"unresolved"`
	// Classification is the producer's own label for the transfer shape
	// ("call", "indirect_call", "tail_call"), verbatim. It is reported, never
	// interpreted: only Observation kinds carry OpenSpore's vocabulary.
	Classification string `json:"classification"`
}

// RuntimeImportRef names an import the producer observed reaching.
//
// Module and Symbol are the producer's spelling, reproduced verbatim: a DLL
// name is not something OpenSpore can adjudicate, and normalising it would lose
// the only evidence that the producer's import resolution differs from ours.
type RuntimeImportRef struct {
	Module       string           `json:"module"`
	Symbol       string           `json:"symbol"`
	SlotVA       *string          `json:"slot_va"`
	LoadedValue  *string          `json:"loaded_value"`
	Bound        semantic.TriBool `json:"bound"`
	ReachedCount *int             `json:"reached_count"`
}

// Observation is one typed runtime fact.
//
// Fields are shared across kinds rather than being nine structs, because a
// closed union in encoding/json without a discriminator per variant is a
// readability trap: a `call` observation carrying a `stack` field would be
// indistinguishable from a malformed one. The validator therefore enforces that
// the address-bearing fields a kind does not use are null, and that every kind
// uses the ones it must.
type Observation struct {
	Kind ObservationKind `json:"kind"`

	// Sequence is the producer's own ordinal, so a reader can reconstruct
	// order. Non-nil only when the producer ordered its events.
	Sequence *int64 `json:"sequence"`

	// EIP is where the processor was. Used by entry, and by any observation that
	// is not anchored to a call edge.
	EIP *string `json:"eip"`

	// Call fields, used by call / indirect_call / return.
	CallerFunctionVA *string `json:"caller_function_va"`
	CallsiteVA       *string `json:"callsite_va"`
	TargetVA         *string `json:"target_va"`
	ReturnAddress    *string `json:"return_address"`

	// Indirect is tri-state on indirect_call: whether the dispatch was indirect.
	Indirect semantic.TriBool `json:"indirect"`

	// CallDepth is the observed stack depth at the observation.
	CallDepth *int `json:"call_depth"`

	// Count is the number of times this observation recurred.
	Count *int `json:"count"`

	// Register and RegisterValue are used by register observations: which
	// register, and what it held.
	Register      *string `json:"register"`
	RegisterValue *string `json:"register_value"`

	// ReturnRegister names the register the producer saw carrying the return
	// value, verbatim ("EAX"). It is an OBSERVATION of a register name, not a
	// claim about the function's return width: OpenSpore's return-width question
	// is about how many bytes the ABI says are meaningful, which a register name
	// alone does not answer. The bridge reports the observation and never
	// promotes it to a return-semantics verdict.
	ReturnRegister *string `json:"return_register"`

	// Stack fields are used by stack observations.
	EntryESP  *string `json:"entry_esp"`
	ReturnESP *string `json:"return_esp"`
	// StackDeltaBytes is observed_esp_at_return - observed_esp_at_entry. Signed:
	// a callee may return with ESP above where it started.
	StackDeltaBytes *int `json:"stack_delta_bytes"`

	// Memory fields are used by memory observations.
	Address *string `json:"address"`
	Access  string  `json:"access"`
	// WidthBytes and Value are null unless the producer read them.
	WidthBytes *int    `json:"width_bytes"`
	Value      *string `json:"value"`

	// Import fields are used by import observations.
	Module *string `json:"module"`
	Symbol *string `json:"symbol"`
	SlotVA *string `json:"slot_va"`

	// Exception fields are used by exception observations. Class is the
	// producer's own name for the condition, verbatim.
	Class  *string `json:"exception_class"`
	Detail string  `json:"detail"`
}

// ProvenanceEntry attributes one observation to one producer artifact.
//
// SourceClass is "runtime" for every entry produced by this schema. It is a
// distinct value from the static exchange's vocabulary
// (generated_index / committed_artifact / ghidra / derived), and it is
// deliberately NOT one of them: an observation of execution is a different kind
// of claim from a decompilation, and giving it a familiar label would invite a
// future importer to treat it as one.
type ProvenanceEntry struct {
	SourceClass string `json:"source_class"`
	Producer    string `json:"producer"`
	Artifact    string `json:"artifact"`
}

// ProvenanceSourceRuntime is the only SourceClass this schema emits.
const ProvenanceSourceRuntime = "runtime"

// KnownProvenanceSource reports whether s is a source class this schema
// accepts. Only "runtime" is accepted today: an overlay that claimed
// "ghidra" provenance would be a static artifact wearing a runtime file's
// schema, which is the confusion this package exists to prevent.
func KnownProvenanceSource(s string) bool { return s == ProvenanceSourceRuntime }

// ---------------------------------------------------------------------------
// Census (OpenSpore-side static input, never produced by a runtime producer)
// ---------------------------------------------------------------------------

// Census is the projection of OpenSpore's own per-target blocker statements. It
// exists so `runtime frontier` can intersect a static blocker with runtime
// evidence without re-deriving the frontier in a second language and without
// widening the static passport.
//
// It is a single JSON document rather than JSON Lines: it is an OpenSpore
// artifact, not an exchange artifact, so it follows the repository's other
// sidecar schemas rather than the snapshot's.
type Census struct {
	Schema        string                  `json:"schema"`
	Binary        semantic.BinaryIdentity `json:"binary"`
	Source        CensusSource            `json:"source"`
	Targets       []CensusTarget          `json:"targets"`
	ContentSHA256 string                  `json:"content_sha256"`
}

// CensusSource records which OpenSpore artifacts the census was projected from,
// so a reader can tell a census that reflects today's index from one that does
// not. Promotion is read from the marker files rather than the knowledge index,
// because the index lags promotion by design.
type CensusSource struct {
	Index            string `json:"index"`
	IndexSHA256      string `json:"index_sha256"`
	PromotionMarkers string `json:"promotion_markers"`
	PromotedCount    int    `json:"promoted_count"`
	MarkerGlob       string `json:"marker_glob"`
}

// CensusTarget is one target's static blocker statements, verbatim.
type CensusTarget struct {
	VA     string `json:"va"`
	Name   string `json:"name"`
	Status string `json:"status"`
	// Reconstructed and Promoted are separate booleans because the index's
	// `reconstructed` flag and the promotion marker disagree by design: the
	// marker is authoritative and self-maintaining, the index lags it.
	Reconstructed bool `json:"reconstructed"`
	Promoted      bool `json:"promoted"`
	// EvidenceLevel is the index's own rung, or null.
	EvidenceLevel *string `json:"evidence_level"`
	// RuntimeGated is the index's gate flag: a target whose runtime gate is open
	// is one whose missing evidence is specifically a runtime observation. That
	// is the join this census exists for.
	RuntimeGated       bool     `json:"runtime_gated"`
	RuntimeValidated   int      `json:"runtime_validated"`
	RuntimeGates       []string `json:"runtime_gates"`
	RuntimeBlockReason []string `json:"runtime_blocking_reason"`
	// Blockers is index.json's free-text blocker prose, verbatim. It is prose,
	// not codes, and the census does not invent codes for it.
	Blockers []string `json:"blockers"`
	// UnresolvedQuestions is the same artifact's open questions, verbatim.
	UnresolvedQuestions []string `json:"unresolved_questions"`
	Claimability        string   `json:"claimability"`
	Package             *string  `json:"package"`
}

// HasBlocker reports whether the target carries any static blocker statement.
// A census row with neither blockers nor unresolved questions is not a blocker
// target, and `runtime frontier` says so rather than showing an empty blocker.
func (t CensusTarget) HasBlocker() bool {
	return len(t.Blockers) > 0 || len(t.UnresolvedQuestions) > 0
}

// RawJSON exposes the census document for a schema check without re-decoding.
type RawJSON = json.RawMessage
