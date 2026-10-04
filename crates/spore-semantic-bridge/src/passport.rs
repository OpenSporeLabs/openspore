//! One function's passport: identity, names, classification, and the seven
//! fact groups, each graded and carrying its provenance.
//!
//! # What this module exposes, and what it deliberately leaves behind
//!
//! The passport is a *research* record with an engine sitting at the end of it.
//! Everything the format declares is **validated** — an unknown field anywhere,
//! including inside a block this crate does not retain, is refused — but only
//! what an engine can act on is **retained**. The blocks that are parsed and
//! discarded are listed on [`Passport`] and in `crate::claims`; the short reason
//! is that carrying prose a machine must not confuse with a machine fact is worse
//! than not carrying it. `abi.value.declared` is the clearest case: the format's
//! own rule is that a hand-written `"__thiscall observed"` must never be mistaken
//! for an inferred `convention`, and the only way to guarantee that is not to
//! hold the prose at all.

use crate::address::Va;
use crate::envelope::{
    fact_group, graded_scalar, opt_u32_field, schema, u32_field, va_field, va_list,
};
use crate::json::{JsonError, JsonErrorKind, Obj, Parser, Val};
use crate::schema::function_spec;
use spore_core::{EvidenceLevel, Fact, Provenance, ProvenanceMode, SourceClass};
use std::collections::BTreeMap;
use std::fmt;

/// The committed snapshot's path, relative to the repository root. Used as the
/// provenance reference for the passport's plain nullable fields, which the
/// format does not wrap in an envelope and therefore does not source itself.
pub const SNAPSHOT_REFERENCE: &str = "knowledge/semantic/function-passport-v1.jsonl";

/// Schema id this build implements. Anything else is refused.
pub const SNAPSHOT_SCHEMA: &str = "spore-semantic-snapshot-1";

/// The file name the committed snapshot uses under `knowledge/semantic/`.
pub const SNAPSHOT_FILE_NAME: &str = "function-passport-v1.jsonl";

/// Bridge-local absence reason: the record states no SDK name.
pub const REASON_NO_SDK_NAME: &str = "no_sdk_name_stated";

/// Bridge-local absence reason: the record states no subsystem.
pub const REASON_NO_SUBSYSTEM: &str = "no_subsystem_stated";

/// Bridge-local absence reason: an ABI record exists and its `convention` is
/// `null`, which means undetermined — *not* "no convention applies".
pub const REASON_CONVENTION_UNDETERMINED: &str = "convention_undetermined";

/// The three-valued boolean the exchange format spells as strings.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, Default)]
pub enum TriState {
    /// `"true"`.
    True,
    /// `"false"` — stated, and it is false.
    False,
    /// `"null"` — looked for, undetermined.
    ///
    /// Load-bearing and not a synonym for [`TriState::False`]: in the ABI engine
    /// a `present: null` receiver blocks two inference rules and makes the
    /// record abstain. Collapsing it to `false` turns "we did not look" into
    /// "we looked and found none".
    #[default]
    Undetermined,
}

impl TriState {
    /// The format's own spelling.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::True => "true",
            Self::False => "false",
            Self::Undetermined => "null",
        }
    }

    pub(crate) fn parse(text: &str) -> Result<Self, JsonError> {
        match text {
            "true" => Ok(Self::True),
            "false" => Ok(Self::False),
            "null" => Ok(Self::Undetermined),
            other => Err(JsonError {
                kind: JsonErrorKind::Schema,
                path: String::new(),
                message: format!(
                    "{other:?} is not one of \"true\", \"false\", \"null\"; the format spells this \
                     vocabulary as strings precisely so the three states stay distinct"
                ),
            }),
        }
    }
}

impl fmt::Display for TriState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// How a requested address was matched against the function universe.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum Canonicalization {
    /// The requested address *is* a function entry.
    FunctionEntry,
    /// The requested address is inside a known body and was resolved to the
    /// entry that contains it.
    ContainingFunctionEntry,
    /// The requested address is not an entry and is not inside any body —
    /// padding between two bodies, or an address the universe cannot place.
    ///
    /// This is an answer, not a gap. `0x00925050` is the live case: it was
    /// reached through a real vtable indirect call and it still resolves to
    /// nothing, because re-pointing an address the universe cannot place is the
    /// same class of error as inventing a mapping.
    NonFunctionEntity,
}

impl Canonicalization {
    /// The rule name, identical to the Go CLI's spelling so the two can be
    /// compared by string.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::FunctionEntry => "function_entry",
            Self::ContainingFunctionEntry => "containing_function_entry",
            Self::NonFunctionEntity => "non_function_entity",
        }
    }

    /// Parses a rule name as the Go CLI prints it.
    pub fn parse(text: &str) -> Option<Self> {
        match text {
            "function_entry" => Some(Self::FunctionEntry),
            "containing_function_entry" => Some(Self::ContainingFunctionEntry),
            "non_function_entity" => Some(Self::NonFunctionEntity),
            _ => None,
        }
    }
}

impl fmt::Display for Canonicalization {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// The outcome of placing one address in the function universe.
///
/// `canonical` and `offset` are optional on purpose. The required shape was
/// `canonical: u32, offset: u32`, but [`Canonicalization::NonFunctionEntity`] has
/// neither: a zero there would be a fabricated address, and
/// `0x00000000` is a real address that means something else. `Option` here is
/// the difference between "nothing" and "zero".
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct AddressResolution {
    /// The address that was asked about.
    pub requested: u32,
    /// The entry it resolved to. `None` only for a non-function entity.
    pub canonical: Option<u32>,
    /// Which rule fired.
    pub rule: Canonicalization,
    /// The byte distance into the containing body: `Some(0)` for an entry, the
    /// real offset for an interior address, `None` for a non-function entity.
    pub offset: Option<u32>,
    /// The exclusive end of the containing body. Interior addresses only.
    pub end: Option<u32>,
}

impl AddressResolution {
    /// The canonical VA, when there is one.
    pub fn canonical_va(&self) -> Option<u32> {
        self.canonical
    }

    /// Whether the address could be placed at all.
    pub const fn is_resolved(&self) -> bool {
        self.canonical.is_some()
    }

    /// The canonical spelling of `requested`.
    pub fn requested_text(&self) -> String {
        Va::new(self.requested).canonical()
    }

    /// The canonical spelling of the resolved entry, when there is one.
    pub fn canonical_text(&self) -> Option<String> {
        self.canonical.map(Va::new).map(Va::canonical)
    }
}

impl fmt::Display for AddressResolution {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{} -> {} ({}, offset {})",
            self.requested_text(),
            self.canonical_text().unwrap_or_else(|| "-".to_owned()),
            self.rule,
            self.offset
                .map(|o| o.to_string())
                .unwrap_or_else(|| "-".to_owned())
        )
    }
}

/// A non-entry address the exporter has already mapped onto an entry.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RecordedResolution {
    /// The rule name as recorded, `containing_function_entry` on the current
    /// snapshot.
    pub rule: String,
    /// The entry the record claims it resolved to.
    pub canonical_va: u32,
    /// Every address the record says it moved, with its byte offset.
    pub requested: Vec<(u32, u32)>,
}

/// Mechanical identity of one function.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Identity {
    /// The canonical VA, as a number.
    pub canonical_va: u32,
    /// `canonical_va - image_base`.
    pub rva: u32,
    /// The body size in bytes. Meaningful only when [`Identity::size_known`].
    pub size: u32,
    /// Whether the universe stated a size at all.
    pub size_known: bool,
    /// Whether the universe marks this entry as a thunk.
    pub is_thunk: bool,
    /// The section the entry lies in, `.text` throughout the current snapshot.
    pub section: String,
}

/// A vftable membership: one `(table, slot)` pair from the sound scan.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct VTableMembership {
    /// The table's VA.
    pub table_va: u32,
    /// The slot index **within the table**.
    pub slot: u32,
    /// The table's slot count when the sound scan knew it.
    pub slot_width: Option<u32>,
}

impl Default for VTableRecord {
    fn default() -> Self {
        Self {
            memberships: Vec::new(),
            attributed_rule: None,
            attributed_table: None,
            attributed_slot: None,
            attributed_confidence: EvidenceLevel::Unknown,
            triage_addresses: Vec::new(),
            triage_family: None,
        }
    }
}

impl VTableMembership {
    /// Bytes per slot on `x86:LE:32`.
    pub const POINTER_SIZE: u32 = 4;

    /// The slot's byte displacement from the table's base.
    ///
    /// # Reach a slot by displacement, never by array subscript
    ///
    /// `table[1].slot1` advances by `sizeof(StateInterface)` — a *whole pair* of
    /// slots — while `MOV EDX,[EAX+n]` advances by `n * 4`. They agree only at
    /// `n == 0`. `0x0068f9b0`'s body had exactly this bug: it read `table+0xC`
    /// where `MOV EDX,[EAX+0x4]` proves `table+0x4`, and because the two tables
    /// in the fixture were adjacent the wrong index aliased a *callable pointer*
    /// and produced a plausible wrong answer instead of a crash.
    ///
    /// So this accessor exists to make the safe spelling the easy one.
    pub const fn byte_displacement(&self) -> u32 {
        self.slot * Self::POINTER_SIZE
    }
}

/// The call graph block, from the closure-validated xref export.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct Graph {
    /// How many canonical callers the export records.
    pub caller_count: u32,
    /// How many canonical callees plus external callees the export records.
    pub callee_count: u32,
    /// Canonical caller VAs, ascending and de-duplicated.
    pub callers: Vec<u32>,
    /// Canonical callee VAs, ascending and de-duplicated.
    pub callees: Vec<u32>,
    /// Imported callees, verbatim: `EXT:KERNEL32.DLL::fopen`.
    pub external_callees: Vec<String>,
    /// How many vtable references the xref export records.
    pub vtable_reference_count: u32,
    /// How many data references the dataref export records. The addresses
    /// /// themselves stay in the authoritative TSV; only the count is projected.
    pub data_reference_count: u32,
    /// The Tarjan component size triage computed, when it stated one.
    pub scc_size: Option<u32>,
    /// Triage's own fan-in counter, when it stated one.
    ///
    /// Deliberately **not** a [`Fact`]: the format declares these two as plain
    /// nullable pointers with no envelope and no `reason`, so publishing a graded
    /// absence for them would invent a statement the artifact never made. `None`
    /// here means "the triage row stated none" — a weaker statement than
    /// [`Fact::unavailable`], and the doc comment says so. On the current
    /// snapshot both are absent from every record, while the upstream docs call
    /// them triage's own counters that "may legitimately differ" from the ones
    /// above.
    pub fan_in: Option<u32>,
    /// Triage's own fan-out counter. See [`Graph::fan_in`].
    pub fan_out: Option<u32>,
}

/// The triage classifier's view plus the subsystem taxonomy.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Classification {
    /// The triage category, verbatim.
    pub category: String,
    /// The triage priority, `P0`..`P3` or `IGNORE`.
    pub priority: String,
    /// The classifier's grade, **verbatim**.
    ///
    /// This is the one place the snapshot's grade vocabulary is *not* the shared
    /// 7-rung scale: the current snapshot writes `"APPROX"` on 1 500 records,
    /// where the scale spells it `APPROXIMATION`. The raw spelling is preserved
    /// here and [`Classification::evidence_level`] degrades it to
    /// [`EvidenceLevel::Unknown`] rather than inventing the mapping — see
    /// `crate::claims`.
    pub evidence: String,
    /// The triage subsystem, when stated.
    pub subsystem: Option<String>,
    /// Triage's cluster, when stated. Null on 58 389 of 58 757 records, which is
    /// why the engine-facing API routes on [`Classification::subsystem`].
    pub cluster: Option<String>,
    /// `/Spore/...` type names triage associated.
    pub sdk_structs: Vec<String>,
    /// Non-null only for the 23 RenderWare rows.
    pub renderware_role: Option<String>,
    /// Which of the three fallback inputs supplied [`Classification::subsystem`],
    /// so a mixed vocabulary is explainable rather than mysterious.
    pub subsystem_source: Option<String>,
}

impl Classification {
    /// The classifier's grade mapped onto the shared scale.
    ///
    /// A spelling off the scale becomes [`EvidenceLevel::Unknown`]: a grade this
    /// build does not understand is not evidence this build understands. The
    /// verbatim spelling stays available in [`Classification::evidence`], so no
    /// information is lost — but no rung is invented either.
    pub fn evidence_level(&self) -> EvidenceLevel {
        EvidenceLevel::parse(&self.evidence)
    }

    /// Whether the subsystem is a real name rather than the source's own
    /// `"Unknown"` sentinel.
    ///
    /// The literal string `"Unknown"` is what the triage classifier writes for
    /// 49 340 of 58 757 records. It is **not** the exchange format's absence
    /// vocabulary — it is a value the source chose — so this crate reports it
    /// verbatim and offers this predicate instead of quietly folding it into
    /// [`Fact::unavailable`]. Routing on it is the difference between a 122-entry
    /// subsystem vocabulary and a 49 340-entry bucket called `Unknown`.
    pub fn has_named_subsystem(&self) -> bool {
        self.subsystem
            .as_deref()
            .is_some_and(|value| !value.is_empty() && value != "Unknown")
    }
}

/// The machine-derived ABI record, projected onto decided fields.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct AbiRecord {
    /// Always `abi_inference`.
    pub origin: String,
    /// The inference contract that produced the values.
    pub schema: String,
    /// `__cdecl`, `__stdcall`, `__thiscall` or `__fastcall`, when determined.
    pub convention: Option<String>,
    /// Named globals, verbatim.
    pub convention_confidence: EvidenceLevel,
    /// The engine's own verdict, e.g. `ABI_INFERRED`, `ABI_UNKNOWN`.
    pub verdict: Option<String>,
    /// e.g. `CORE_RESOLVED`.
    pub completeness: Option<String>,
    /// The receiver record. Its `present` is tri-state and load-bearing.
    pub receiver: Option<Receiver>,
    /// Stack cleanup: who pops, and how many bytes.
    pub cleanup: Option<Cleanup>,
    /// The return register and its class. `type` is **always** `null` by
    /// contract, so it is not carried: a field that is null in every record of
    /// the format is a field with no information in it.
    pub return_register: Option<String>,
    /// The return confidence rung.
    pub return_confidence: EvidenceLevel,
    /// The sret hypothesis, including its ambiguity.
    pub sret: Option<Sret>,
    /// Free-form `"UNKNOWN"`/boolean-ish text as the engine wrote it.
    pub variadic: Option<String>,
    /// How many ordinary stack argument slots.
    pub stack_argument_slots: Option<i64>,
    /// Whether the body sets up an SEH or security-cookie frame.
    pub seh_or_cookie_frame: Option<bool>,
}

/// The receiver record inside [`AbiRecord`].
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Receiver {
    /// Tri-state on purpose: `Undetermined` is what makes the ABI engine
    /// abstain, and it is not `False`.
    pub present: TriState,
    /// Which register holds it, when stated.
    pub register: Option<String>,
    /// The confidence rung.
    pub confidence: EvidenceLevel,
    /// The receiver's shape, e.g. `R-ALIAS`.
    pub shape: Option<String>,
    /// The ABI engine's own statement of where this claim came from.
    pub provenance: Option<String>,
    /// Whether only the receiver's bounds were proven.
    pub bounds_only: Option<bool>,
    /// How deep the receiver's proven bounds go.
    pub max_offset: Option<u32>,
    /// How far through the receiver writes were proven.
    pub written_through: Option<u32>,
}

/// Stack cleanup, inside [`AbiRecord`].
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Cleanup {
    /// `caller`, `callee`, `CONFLICT`, or `None`. `CONFLICT` is uppercase and is
    /// not a calling convention.
    pub side: Option<String>,
    /// `PASS` / `WARN` / `FAIL` / `UNKNOWN` / `NOT_AVAILABLE`, verbatim.
    pub bytes: Option<i64>,
    /// `none` / `partial` / `complete`, verbatim.
    pub confidence: EvidenceLevel,
    /// The corroboration note, e.g. `not_available`.
    pub corroboration: Option<String>,
    /// The disassembly evidence, e.g. `ret 0x4`.
    pub evidence: Option<String>,
}

/// The sret hypothesis, inside [`AbiRecord`].
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Sret {
    /// Whether the sret hypothesis holds.
    pub present: TriState,
    /// The stack slot the hypothesis names.
    pub slot: Option<i64>,
    /// The confidence rung of the sret record.
    pub confidence: EvidenceLevel,
    /// e.g. `sret_vs_out_param`.
    pub ambiguity: Option<String>,
    /// The confidence of the hypothesis itself.
    pub hypothesis_confidence: EvidenceLevel,
}

/// The vftable block.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct VTableRecord {
    /// Memberships from the sound scan — the only source the ABI engine accepts.
    pub memberships: Vec<VTableMembership>,
    /// The engine's own attribution, when a VFT rule fired.
    pub attributed_rule: Option<String>,
    /// Which table the attribution names.
    pub attributed_table: Option<u32>,
    /// Which slot of it.
    pub attributed_slot: Option<u32>,
    /// The confidence rung the attribution carries.
    pub attributed_confidence: EvidenceLevel,
    /// Which tables the triage classifier associated, with no slot. A weaker,
    /// differently-sourced statement, kept separate on purpose.
    pub triage_addresses: Vec<u32>,
    /// The vtable family triage named, if any.
    pub triage_family: Option<String>,
}

/// The semantic-interpretation layer: research claims, never merged with the
/// machine facts.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct SemanticsRecord {
    /// The researcher's classification, verbatim.
    pub classification: Option<String>,
    /// The free-form semantic status, e.g. `static_reconstruction_runtime_gated`.
    pub status: Option<String>,
    /// A human-readable name for the function, if a researcher gave one.
    pub name: Option<String>,
    /// The subsystem the semantic record names.
    pub subsystem: Option<String>,
    /// How far the record claims to be triangulated.
    pub triangulation_status: Option<String>,
    /// How many downstream unlocks the record claims.
    pub downstream_unlock_count: Option<i64>,
    /// Where the semantic record came from.
    pub source: Option<String>,
    /// Labelled claims, each with its own class and source.
    pub claims: Vec<SemanticClaim>,
    /// Free-text notes, verbatim.
    pub notes: Vec<String>,
    /// Open questions, copied verbatim. See [`Passport::unresolved_questions`].
    pub unresolved_questions: Vec<String>,
    /// The research family.
    pub family: Option<String>,
    /// Which workers wrote it.
    pub source_workers: Vec<String>,
}

/// One labelled research claim.
#[derive(Debug, Clone, PartialEq, Eq)]
/// The static validation status of the promotion record.
pub struct SemanticClaim {
    /// Whether the promotion record replaced an earlier one.
    pub claim: String,
    /// How many runtime validations are recorded.
    pub class: String,
    /// What backs it.
    pub source: String,
}

/// The campaign view: what was built, whether it promoted, whether it validated.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ReconstructionRecord {
    /// The campaign package name, when stated.
    pub package: Option<String>,
    /// `reconstructed` / `candidate` / `unresolved` / `queued` / `implemented` / `blocked`.
    pub status: Option<String>,
    /// The review status.
    pub review_status: Option<String>,
    /// The integration status.
    pub integration_status: Option<String>,
    /// Whether a body was actually reconstructed.
    pub reconstructed: Option<bool>,
    /// Whether the reconstruction is blocked.
    pub blocked: Option<bool>,
    /// Tri-state: `False` means "no promotion record exists", which for a
    /// reconstructed function is a real answer rather than a non-finding.
    pub promoted: TriState,
    /// The promotion record's schema id.
    pub promotion_schema: Option<String>,
    /// The previous promotion record, verbatim. Open-shaped by design: it
    /// carries the whole build log, so the exporter stores it raw and this crate
    /// hands the bytes over untouched.
    pub promotion_supersedes: Option<String>,
    /// Repo-relative paths that name the SDK type.
    pub static_status: Option<String>,
    /// Repo-relative source paths the reconstruction generated.
    pub generated_source: Vec<String>,
    /// Handoff records.
    pub handoffs: Vec<String>,
    /// Metadata sidecars.
    pub metadata: Vec<String>,
    /// The runtime gate, as a three-state answer.
    pub runtime_gate: RuntimeGate,
    /// How many runtime validations are recorded.
    pub runtime_validated: Option<i64>,
    /// Verbatim; the source spells it as a string for 617 records and a list for
    /// one, and normalising it would lose the difference.
    pub runtime_blocking_reason: Option<String>,
    /// the current snapshot; see `crate::claims`.
    pub validation: Option<ValidationSummary>,
}

/// The state of a reconstruction's runtime gate.
///
/// # `Open` is neither a pass nor a failure
///
/// The format is explicit: `runtime.gated: true` means *the gate is open,
/// nothing was attempted, and nothing failed*. It is a fourth state, and the
/// enum exists so it cannot be read as either of the other two. A caller that
/// wants "is this done?" must say which question it means: `Open` answers "can
/// runtime evidence be gathered here?" and `Closed` answers "must it be?".
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum RuntimeGate {
    /// `runtime_gated: false` — the gate is closed.
    Closed,
    /// `runtime_gated: true` — open; nothing attempted, nothing failed.
    Open,
    /// The reconstruction record states no `runtime_gated`. A *stated* absence
    /// within an available record, which is why it is not
    /// [`Fact::unavailable`].
    #[default]
    Unstated,
}

impl RuntimeGate {
    /// Reads the format's boolean, mapping "absent" to [`RuntimeGate::Unstated`].
    pub const fn from_bool(value: Option<bool>) -> Self {
        match value {
            Some(true) => Self::Open,
            Some(false) => Self::Closed,
            None => Self::Unstated,
        }
    }

    /// The format's boolean, or `None` when unstated.
    pub const fn as_bool(self) -> Option<bool> {
        match self {
            Self::Open => Some(true),
            Self::Closed => Some(false),
            Self::Unstated => None,
        }
    }

    /// Whether runtime evidence could be gathered for this function.
    pub const fn accepts_runtime_evidence(self) -> bool {
        matches!(self, Self::Open | Self::Unstated)
    }
}

impl Default for ReconstructionRecord {
    fn default() -> Self {
        Self {
            package: None,
            status: None,
            review_status: None,
            integration_status: None,
            reconstructed: None,
            blocked: None,
            promoted: TriState::Undetermined,
            promotion_schema: None,
            promotion_supersedes: None,
            static_status: None,
            generated_source: Vec::new(),
            handoffs: Vec::new(),
            metadata: Vec::new(),
            runtime_gate: RuntimeGate::Unstated,
            runtime_validated: None,
            runtime_blocking_reason: None,
            validation: None,
        }
    }
}

/// Per-dimension validation verdicts, reproduced unchanged.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct ValidationSummary {
    /// The validation document's schema id.
    pub schema: String,
    /// Dimension name to verdict. The dimension names are data upstream
    /// (`map[string]ValidationCheck`) and are *not* closed, so a new dimension
    /// appears here rather than being refused — but every verdict inside it is
    /// validated in full.
    pub coverage: BTreeMap<String, ValidationCheck>,
    /// The runtime dimension's own verdict.
    pub runtime: Option<ValidationCheck>,
}

/// One dimension's verdict.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ValidationCheck {
    /// `PASS` / `WARN` / `FAIL` / `UNKNOWN` / `NOT_AVAILABLE`, verbatim.
    ///
    /// Reproduced as a string rather than an enum on purpose: mapping it onto a
    /// Rust enum would collapse `FAIL` into `NOT_AVAILABLE`, and those are
    /// different answers.
    pub status: String,
    /// `none` / `partial` / `complete`, verbatim.
    pub coverage: String,
    /// The reasoning, verbatim. Long, and present on 672 records only.
    pub detail: String,
    /// Repo-relative artifact references backing the verdict.
    pub evidence: Vec<String>,
}

/// A JSON value kept exactly as the file wrote it.
///
/// The format stores a few fields as raw JSON because their shape is not its to
/// fix (see `crate::json`). This crate hands those bytes over untouched and never
/// interprets them, so a change inside them cannot be misread as a change of
/// meaning *here* — but it also cannot be validated here.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RawJson(String);

impl RawJson {
    /// The verbatim text.
    pub fn as_str(&self) -> &str {
        &self.0
    }
}

impl fmt::Display for RawJson {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.0)
    }
}

/// A name a worker refuted, with the evidence it did so.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RefutedIdentity {
    /// The name that took over.
    pub name: String,
    /// The SDK- or triage-derived name that was superseded.
    pub superseded: String,
    /// Which artifact the superseded name came from.
    pub superseded_source: String,
    /// The metadata sidecar that declared the replacement.
    pub declared_by: Option<String>,
    /// The reason, verbatim. Keyed by failure mode upstream, so flattening it to
    /// prose would lose the key that says which failure fired.
    pub reason: Option<RawJson>,
    /// The refutation record, verbatim.
    pub refuted: Option<RawJson>,
}

/// An evidence pack filed under a non-entry address that resolves into this
/// entry's body.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct AdditionalPack {
    /// The pack's repo-relative path.
    pub pack: String,
    /// The non-entry address the pack was filed under.
    pub requested_va: u32,
    /// The byte offset into the containing body.
    pub offset: u32,
    /// The rule that moved it, `containing_function_entry`.
    pub rule: String,
    /// The pack's own evidence state.
    pub pack_state: Option<String>,
    /// The pack's self-digest.
    pub pack_content_sha256: Option<String>,
}

/// The per-function evidence locations.
///
/// Every field is optional and each optionality is an *explicit* statement that
/// the exporter looked under `reconstruction/evidence/<bare8>/` and found
/// nothing — not an omission, and not a claim that the fact is false. This block
/// is deliberately a plain record rather than seven envelopes: the format
/// publishes no grades here, and inventing them would be a claim this crate
/// cannot support.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct EvidenceLocations {
    /// The pack's repo-relative path, or none.
    pub pack: Option<String>,
    /// The pack's own evidence state: `LIVE`, `DERIVED` or `PERSISTED`.
    pub pack_state: Option<String>,
    /// The pack's self-digest.
    pub pack_content_sha256: Option<String>,
    /// How the pack keys its target addresses, `linked_va`.
    pub target_address_kind: Option<String>,
    /// The sibling validation report.
    pub validation_report: Option<String>,
    /// Note: the current snapshot spells this path with a literal `00000000`
    /// for all 92 promoted VAs — an exporter formatting bug, faithfully carried
    /// here rather than repaired. See `crate::claims`.
    pub promotion_record: Option<String>,
    /// Packs filed under non-entry addresses inside this body.
    pub additional_packs: Vec<AdditionalPack>,
}

/// One function's exchange record.
///
/// # Parsed, validated, then mostly not retained
///
/// Validated in full: `identity`, `names`, `classification`, `abi` (including
/// `abi.value.declared`), `vtable`, `graph`, `globals`, `types`, `semantics`
/// (including its raw confidence map), `reconstruction` (including
/// `promotion_supersedes` and `runtime_blocking_reason`), `evidence`, and the
/// document-level `provenance`.
///
/// Retained: everything above except `abi.value.declared`, which is discarded on
/// purpose (see the module docs), plus `semantics.value.confidence` and
/// `validation.static_rollup`, which are raw by contract.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Passport {
    identity: Identity,
    ghidra_name: String,
    normalized_symbol: Option<String>,
    sdk_name: Option<String>,
    sdk_name_source: Option<String>,
    identity_refuted: Option<RefutedIdentity>,
    classification: Classification,
    abi: Fact<AbiRecord>,
    vtable: Fact<VTableRecord>,
    graph: Graph,
    globals: Fact<Vec<String>>,
    types: Fact<Vec<String>>,
    semantics: Fact<SemanticsRecord>,
    reconstruction: Fact<ReconstructionRecord>,
    evidence: EvidenceLocations,
    provenance: Vec<Provenance>,
    recorded_resolution: Option<RecordedResolution>,
}

impl Passport {
    /// Parses one record line. The only entry point; the reader is otherwise
    /// private so that nothing can produce a `Passport` the schema did not
    /// describe.
    pub(crate) fn parse(line: &str) -> Result<Self, JsonError> {
        let obj = Parser::new(line).parse_one(function_spec())?;
        let record = obj.req_str("record")?;
        if record != "function" {
            return Err(schema(
                &obj,
                "record",
                format!("expected \"function\", found {record:?}"),
            ));
        }

        let (identity, recorded_resolution) = parse_identity(&obj)?;
        let names = obj.req("names")?.as_object()?;
        let classification = obj.req("classification")?.as_object()?;
        let abi = obj.req("abi")?.as_object()?;
        let vtable = obj.req("vtable")?.as_object()?;
        let graph = obj.req("graph")?.as_object()?;
        let globals = obj.req("globals")?.as_object()?;
        let types = obj.req("types")?.as_object()?;
        let semantics = obj.req("semantics")?.as_object()?;
        let reconstruction = obj.req("reconstruction")?.as_object()?;
        let evidence = obj.req("evidence")?.as_object()?;

        // Fact groups. Each carries its own grade, state and provenance.
        let abi_fact = fact_group(abi, parse_abi)?;
        let vtable_fact = fact_group(vtable, parse_vtable)?;
        let globals_fact = fact_group(globals, |value| string_list(value))?;
        let types_fact = fact_group(types, |value| string_list(value))?;
        let semantics_fact = fact_group(semantics, parse_semantics)?;
        let reconstruction_fact = fact_group(reconstruction, parse_reconstruction)?;

        // Document-level provenance. Absent on every record without an evidence
        // pack, which is why it is not an envelope: the format publishes no
        // grade for the document's own sourcing.
        let provenance = match obj.opt("provenance") {
            None => Vec::new(),
            Some(value) => {
                let items = value.as_array()?;
                let path = obj.child("provenance");
                items
                    .iter()
                    .map(|item| parse_provenance_entry(item.as_object()?, &path))
                    .collect::<Result<Vec<_>, _>>()?
            }
        };

        Ok(Self {
            identity,
            ghidra_name: names.req_str("ghidra_name")?.to_owned(),
            normalized_symbol: names.opt_str("normalized_symbol")?.map(str::to_owned),
            sdk_name: names.opt_str("sdk_name")?.map(str::to_owned),
            sdk_name_source: names.opt_str("sdk_name_source")?.map(str::to_owned),
            identity_refuted: parse_identity_refuted(names)?,
            classification: parse_classification(classification)?,
            abi: abi_fact,
            vtable: vtable_fact,
            graph: parse_graph(graph)?,
            globals: globals_fact,
            types: types_fact,
            semantics: semantics_fact,
            reconstruction: reconstruction_fact,
            evidence: parse_evidence_locations(evidence)?,
            provenance,
            recorded_resolution,
        })
    }

    /// The index a caller needs to look a record up without re-parsing it.
    pub(crate) fn index_fields(&self) -> (u32, u32, bool, [Option<&str>; 3]) {
        (
            self.identity.canonical_va,
            self.identity.size,
            self.identity.size_known,
            [
                self.normalized_symbol.as_deref(),
                self.sdk_name.as_deref(),
                Some(self.ghidra_name.as_str()),
            ],
        )
    }

    /// The canonical VA, as a number.
    pub fn canonical_va(&self) -> u32 {
        self.identity.canonical_va
    }

    /// The canonical VA, as an address.
    pub fn va(&self) -> Va {
        Va::new(self.identity.canonical_va)
    }

    /// The canonical spelling of the VA.
    pub fn canonical_va_text(&self) -> String {
        self.va().canonical()
    }

    /// Mechanical identity.
    pub fn identity(&self) -> &Identity {
        &self.identity
    }

    /// The record's body size, when the universe stated one.
    ///
    /// This is the number the canonical-identity rule's containment test uses,
    /// so it is exposed as a first-class fact rather than a detail of
    /// [`Identity`].
    pub fn size(&self) -> Option<u32> {
        self.identity.size_known.then_some(self.identity.size)
    }

    /// The Ghidra name. Always present, but only a *derived* name — never a
    /// substitute for an SDK name where provenance matters.
    pub fn ghidra_name(&self) -> &str {
        &self.ghidra_name
    }

    /// The normalized symbol, when stated.
    pub fn normalized_symbol(&self) -> Option<&str> {
        self.normalized_symbol.as_deref()
    }

    /// The SDK-declared name, graded.
    ///
    /// Absent on 57 586 of 58 757 records, and the absence is real: no
    /// authoritative OpenSpore artifact states an SDK name for those functions.
    /// The grade is the triage classifier's own
    /// ([`Classification::evidence_level`]) because the snapshot attaches no
    /// grade of its own to a name.
    pub fn sdk_name(&self) -> Fact<&str> {
        graded_scalar(
            self.sdk_name.as_deref(),
            self.classification.evidence_level(),
            "names.sdk_name",
            self.sdk_name_source.as_deref(),
            REASON_NO_SDK_NAME,
        )
    }

    /// Which artifact stated [`Passport::sdk_name`], when it did.
    pub fn sdk_name_source(&self) -> Option<&str> {
        self.sdk_name_source.as_deref()
    }

    /// The `::`-prefix of [`Passport::sdk_name`], as a string convenience.
    ///
    /// Not an OpenSpore claim: the exporter states whole names and never splits
    /// them. `Graphics`, `UTFWin`, `App`, `Simulator`, `GameInput` and `Resource`
    /// are the engine-relevant namespaces on the current snapshot.
    pub fn sdk_namespace(&self) -> Option<&str> {
        self.sdk_name
            .as_deref()
            .and_then(|name| name.split_once("::").map(|(namespace, _)| namespace))
    }

    /// The one record whose SDK-derived identity a worker refuted.
    pub fn identity_refuted(&self) -> Option<&RefutedIdentity> {
        self.identity_refuted.as_ref()
    }

    /// The triage classifier's view.
    pub fn classification(&self) -> &Classification {
        &self.classification
    }

    /// The routing key: the triage subsystem, graded.
    ///
    /// Filter on this, not on [`Classification::cluster`]: `cluster` is null on
    /// 58 389 of 58 757 records. Note also that 49 340 of the subsystem values
    /// are the literal string `"Unknown"` — see
    /// [`Classification::has_named_subsystem`].
    pub fn subsystem(&self) -> Fact<&str> {
        graded_scalar(
            self.classification.subsystem.as_deref(),
            self.classification.evidence_level(),
            "classification.subsystem",
            self.classification.subsystem_source.as_deref(),
            REASON_NO_SUBSYSTEM,
        )
    }

    /// The triage category, graded: `ENGINE_INTERFACE`,
    /// `ENGINE_IMPLEMENTATION`, `GAMEPLAY_SUPPORT`, `GAMEPLAY_LOGIC`,
    /// `THIRD_PARTY_OR_RUNTIME` or `UNKNOWN`.
    pub fn category(&self) -> Fact<&str> {
        graded_scalar(
            Some(self.classification.category.as_str()),
            self.classification.evidence_level(),
            "classification.category",
            None,
            REASON_NO_SUBSYSTEM,
        )
    }

    /// The calling convention, graded.
    ///
    /// Three outcomes, all distinct:
    ///
    /// * the ABI group is unavailable — [`Fact::unavailable`] with the group's
    ///   own reason code (`no_evidence_pack` and friends);
    /// * an ABI record exists and `convention` is `null` — undetermined, carried
    ///   as [`Fact::unavailable`] with [`REASON_CONVENTION_UNDETERMINED`];
    /// * an ABI record exists and states one of `__cdecl`, `__stdcall`,
    ///   `__thiscall`, `__fastcall`.
    ///
    /// The second case is deliberately *not* a value: "we have a record and it
    /// declines to name a convention" is a different statement from "there is no
    /// convention", and the union type is what keeps them apart.
    pub fn convention(&self) -> Fact<&str> {
        let Some(record) = self.abi.value() else {
            return Fact::unavailable(
                self.abi
                    .reason()
                    .unwrap_or(REASON_CONVENTION_UNDETERMINED)
                    .to_owned(),
            );
        };
        match record.convention.as_deref() {
            Some(convention) => graded_scalar(
                Some(convention),
                record.convention_confidence,
                "abi.value.convention",
                Some(record.origin.as_str()),
                REASON_CONVENTION_UNDETERMINED,
            ),
            None => Fact::unavailable(REASON_CONVENTION_UNDETERMINED),
        }
    }

    /// The whole machine ABI record, graded. Unavailable on 58 117 of 58 757.
    pub fn abi(&self) -> &Fact<AbiRecord> {
        &self.abi
    }

    /// The receiver's tri-state presence, when an ABI record exists.
    pub fn receiver_present(&self) -> Option<TriState> {
        self.abi
            .value()
            .and_then(|record| record.receiver.as_ref())
            .map(|receiver| receiver.present)
    }

    /// The vftable memberships, graded.
    ///
    /// Unavailable on 52 045 of 58 757 records. Reach a slot through
    /// [`VTableMembership::byte_displacement`], never by subscripting a table
    /// struct.
    pub fn vtable_memberships(&self) -> Fact<&[VTableMembership]> {
        match self.vtable.value() {
            Some(record) => Fact::new(
                self.vtable.level(),
                self.vtable.evidence_state(),
                self.vtable.provenance().to_vec(),
                record.memberships.as_slice(),
            ),
            None => Fact::unavailable(self.vtable.reason().unwrap_or("no_vtable_membership")),
        }
    }

    /// The vftable block, including triage's weaker association list.
    pub fn vtable(&self) -> &Fact<VTableRecord> {
        &self.vtable
    }

    /// The closure-validated call graph.
    pub fn graph(&self) -> &Graph {
        &self.graph
    }

    /// Canonical caller VAs, ascending.
    pub fn callers(&self) -> &[u32] {
        &self.graph.callers
    }

    /// Canonical callee VAs, ascending.
    pub fn callees(&self) -> &[u32] {
        &self.graph.callees
    }

    /// Imported callees, verbatim (`EXT:KERNEL32.DLL::fopen`).
    pub fn external_callees(&self) -> &[String] {
        &self.graph.external_callees
    }

    /// Referenced globals, verbatim. May be prose: the knowledge index writes
    /// sentences here and the exporter reproduces them rather than rewriting
    /// them.
    pub fn globals(&self) -> &Fact<Vec<String>> {
        &self.globals
    }

    /// Associated type names, verbatim.
    pub fn types(&self) -> &Fact<Vec<String>> {
        &self.types
    }

    /// The research-interpretation layer, graded.
    pub fn semantics(&self) -> &Fact<SemanticsRecord> {
        &self.semantics
    }

    /// Open research questions, graded.
    ///
    /// A [`Fact`] rather than a plain slice on purpose: an empty `&[String]`
    /// cannot distinguish "no semantic record exists" (58 221 records) from
    /// "a semantic record with no open questions" (536), and collapsing those two
    /// is the exact substitution the format forbids.
    pub fn unresolved_questions(&self) -> Fact<&[String]> {
        match self.semantics.value() {
            Some(record) => Fact::new(
                self.semantics.level(),
                self.semantics.evidence_state(),
                self.semantics.provenance().to_vec(),
                record.unresolved_questions.as_slice(),
            ),
            None => Fact::unavailable(self.semantics.reason().unwrap_or("no_semantic_record")),
        }
    }

    /// The campaign view, graded. Unavailable on 58 030 of 58 757.
    pub fn reconstruction(&self) -> &Fact<ReconstructionRecord> {
        &self.reconstruction
    }

    /// The reconstruction package name, graded.
    ///
    /// An `available` record with a `null` package is a real case (a candidate
    /// with no package yet), so the absence here means "the group says nothing
    /// about a package" and is reported as unavailable with a bridge-local code.
    pub fn reconstruction_package(&self) -> Fact<&str> {
        match self.reconstruction.value() {
            Some(record) => graded_scalar(
                record.package.as_deref(),
                self.reconstruction.level(),
                "reconstruction.value.package",
                record.package.as_deref(),
                "no_reconstruction_package",
            ),
            None => Fact::unavailable(
                self.reconstruction
                    .reason()
                    .unwrap_or("no_reconstruction_package"),
            ),
        }
    }

    /// Whether a promotion record exists for this function.
    ///
    /// [`Fact::unavailable`] when the reconstruction group itself is absent, so
    /// "no promotion record" and "no reconstruction at all" stay apart.
    pub fn promoted(&self) -> Fact<bool> {
        match self.reconstruction.value() {
            Some(record) => Fact::new(
                self.reconstruction.level(),
                self.reconstruction.evidence_state(),
                self.reconstruction.provenance().to_vec(),
                record.promoted == TriState::True,
            ),
            None => Fact::unavailable(
                self.reconstruction
                    .reason()
                    .unwrap_or("no_reconstruction_package"),
            ),
        }
    }

    /// The runtime gate's state, graded.
    ///
    /// [`RuntimeGate::Open`] means the gate is open, nothing was attempted and
    /// nothing failed. See that enum for why it is its own state.
    pub fn runtime_gate(&self) -> Fact<RuntimeGate> {
        match self.reconstruction.value() {
            Some(record) => Fact::new(
                self.reconstruction.level(),
                self.reconstruction.evidence_state(),
                self.reconstruction.provenance().to_vec(),
                record.runtime_gate,
            ),
            None => Fact::unavailable(
                self.reconstruction
                    .reason()
                    .unwrap_or("no_reconstruction_package"),
            ),
        }
    }

    /// The per-function evidence locations.
    pub fn evidence_locations(&self) -> &EvidenceLocations {
        &self.evidence
    }

    /// The document-level provenance, absent on every record without a pack.
    ///
    /// Every entry here is checked to be one of the **static** source classes;
    /// an entry claiming `runtime` is refused, because a static artifact may not
    /// wear a runtime file's vocabulary.
    pub fn document_provenance(&self) -> &[Provenance] {
        &self.provenance
    }

    /// What the exporter itself recorded about having corrected this address.
    ///
    /// Reported separately from a computed resolution on purpose: this crate
    /// recomputes canonicalization from the snapshot's own `size`, and this is
    /// the exporter's own claim. They are compared in the tests for the three
    /// known interior addresses, and a disagreement would be a real finding.
    pub fn recorded_identity_resolution(&self) -> Option<&RecordedResolution> {
        self.recorded_resolution.as_ref()
    }
}

// ---------------------------------------------------------------------------
// Parsers for the closed blocks
// ---------------------------------------------------------------------------

fn parse_identity(obj: &Obj<'_>) -> Result<(Identity, Option<RecordedResolution>), JsonError> {
    let identity = obj.req("identity")?.as_object()?;
    let recorded = match identity.opt("identity_resolution") {
        None => None,
        Some(value) => {
            let resolution = value.as_object()?;
            let rule = resolution.req_str("rule")?.to_owned();
            if rule != "containing_function_entry" {
                return Err(schema(
                    resolution,
                    "rule",
                    format!(
                        "{rule:?} is not a rule this build knows; the vocabulary is closed at \
                         \"containing_function_entry\""
                    ),
                ));
            }
            let requested = resolution.opt_object_array("requested")?;
            let mut moved = Vec::with_capacity(requested.len());
            for entry in &requested {
                moved.push((va_field(entry, "va")?, u32_field(entry, "offset")?));
            }
            Some(RecordedResolution {
                rule,
                canonical_va: va_field(resolution, "canonical_va")?,
                requested: moved,
            })
        }
    };

    if let Some(recorded) = &recorded {
        // A record that states a resolution must also list what it moved;
        // otherwise the correction is asserted and not shown.
        if recorded.requested.is_empty() {
            return Err(schema(
                identity,
                "identity_resolution.requested",
                "identity_resolution is present but lists no moved address",
            ));
        }
        if recorded.canonical_va != va_field(identity, "canonical_va")? {
            return Err(schema(
                identity,
                "identity_resolution.canonical_va",
                "identity_resolution names a different entry than the record it sits on",
            ));
        }
    }

    Ok((
        Identity {
            canonical_va: va_field(identity, "canonical_va")?,
            rva: va_field(identity, "rva")?,
            size: u32_field(identity, "size")?,
            size_known: identity.req_bool("size_known")?,
            is_thunk: identity.req_bool("is_thunk")?,
            section: identity.req_str("section")?.to_owned(),
        },
        recorded,
    ))
}

fn parse_classification(obj: &Obj<'_>) -> Result<Classification, JsonError> {
    Ok(Classification {
        category: obj.req_str("category")?.to_owned(),
        priority: obj.req_str("priority")?.to_owned(),
        evidence: obj.req_str("evidence")?.to_owned(),
        subsystem: obj.opt_str("subsystem")?.map(str::to_owned),
        cluster: obj.opt_str("cluster")?.map(str::to_owned),
        sdk_structs: obj
            .opt_str_array("sdk_structs")?
            .into_iter()
            .map(str::to_owned)
            .collect(),
        renderware_role: obj.opt_str("renderware_role")?.map(str::to_owned),
        subsystem_source: obj.opt_str("subsystem_source")?.map(str::to_owned),
    })
}

fn parse_identity_refuted(names: &Obj<'_>) -> Result<Option<RefutedIdentity>, JsonError> {
    let Some(value) = names.opt("identity_refuted") else {
        return Ok(None);
    };
    let refuted = value.as_object()?;
    Ok(Some(RefutedIdentity {
        name: refuted.req_str("name")?.to_owned(),
        superseded: refuted.req_str("superseded")?.to_owned(),
        superseded_source: refuted.req_str("superseded_source")?.to_owned(),
        declared_by: refuted.opt_str("declared_by")?.map(str::to_owned),
        reason: raw_field(refuted, "reason")?,
        refuted: raw_field(refuted, "refuted")?,
    }))
}

fn parse_graph(obj: &Obj<'_>) -> Result<Graph, JsonError> {
    let callers = va_list(obj, "callers")?;
    let callees = va_list(obj, "callees")?;
    let external_callees: Vec<String> = obj
        .opt_str_array("external_callees")?
        .into_iter()
        .map(str::to_owned)
        .collect();
    let caller_count = u32_field(obj, "caller_count")?;
    let callee_count = u32_field(obj, "callee_count")?;

    // An invariant the format does not state but the current snapshot satisfies
    // on all 58 757 records: the lists are already de-duplicated, so the counts
    // are counts of addresses rather than of edges. Checking it here means a
    // `caller_count` that no longer matches its list cannot be read as "no
    // callers".
    if callers.len() as u32 != caller_count {
        return Err(JsonError {
            kind: JsonErrorKind::Schema,
            path: obj.child("caller_count"),
            message: format!(
                "caller_count is {caller_count} but the callers list holds {} address(es)",
                callers.len()
            ),
        });
    }
    if callees.len() as u32 + external_callees.len() as u32 != callee_count {
        return Err(JsonError {
            kind: JsonErrorKind::Schema,
            path: obj.child("callee_count"),
            message: format!(
                "callee_count is {callee_count} but the callee lists hold {} address(es) plus {} \
                 external token(s)",
                callees.len(),
                external_callees.len()
            ),
        });
    }

    Ok(Graph {
        caller_count,
        callee_count,
        callers,
        callees,
        external_callees,
        vtable_reference_count: u32_field(obj, "vtable_reference_count")?,
        data_reference_count: u32_field(obj, "data_reference_count")?,
        scc_size: opt_u32_field(obj, "scc_size")?,
        fan_in: opt_u32_field(obj, "fan_in")?,
        fan_out: opt_u32_field(obj, "fan_out")?,
    })
}

fn parse_abi(value: &Val<'_>) -> Result<AbiRecord, JsonError> {
    let obj = value.as_object()?;
    let receiver = match obj.opt("receiver") {
        None => None,
        Some(value) => {
            let r = value.as_object()?;
            Some(Receiver {
                present: TriState::parse(r.req_str("present")?)
                    .map_err(|e| e.at(r.child("present")))?,
                register: r.opt_str("register")?.map(str::to_owned),
                confidence: EvidenceLevel::parse(r.req_str("confidence")?),
                shape: r.opt_str("shape")?.map(str::to_owned),
                provenance: r.opt_str("provenance")?.map(str::to_owned),
                bounds_only: r.opt_bool("bounds_only")?,
                max_offset: opt_u32_field(r, "max_offset")?,
                written_through: opt_u32_field(r, "written_through")?,
            })
        }
    };
    let cleanup = match obj.opt("cleanup") {
        None => None,
        Some(value) => {
            let c = value.as_object()?;
            Some(Cleanup {
                side: c.opt_str("side")?.map(str::to_owned),
                bytes: c.opt_int("bytes")?,
                confidence: EvidenceLevel::parse(c.req_str("confidence")?),
                corroboration: c.opt_str("corroboration")?.map(str::to_owned),
                evidence: c.opt_str("evidence")?.map(str::to_owned),
            })
        }
    };
    let return_block = obj.opt("return").map(Val::as_object).transpose()?;
    let sret = match obj.opt("sret") {
        None => None,
        Some(value) => {
            let s = value.as_object()?;
            Some(Sret {
                present: TriState::parse(s.req_str("present")?)
                    .map_err(|e| e.at(s.child("present")))?,
                slot: s.opt_int("slot")?,
                confidence: EvidenceLevel::parse(s.req_str("confidence")?),
                ambiguity: s.opt_str("ambiguity")?.map(str::to_owned),
                hypothesis_confidence: EvidenceLevel::parse(s.req_str("hypothesis_confidence")?),
            })
        }
    };

    Ok(AbiRecord {
        origin: obj.req_str("origin")?.to_owned(),
        schema: obj.req_str("schema")?.to_owned(),
        convention: obj.opt_str("convention")?.map(str::to_owned),
        convention_confidence: EvidenceLevel::parse(obj.req_str("convention_confidence")?),
        verdict: obj.opt_str("verdict")?.map(str::to_owned),
        completeness: obj.opt_str("completeness")?.map(str::to_owned),
        receiver,
        cleanup,
        return_register: return_block
            .and_then(|r| r.opt_str("register").ok().flatten())
            .map(str::to_owned),
        return_confidence: return_block.map_or(EvidenceLevel::Unknown, |r| {
            EvidenceLevel::parse(r.req_str("confidence").unwrap_or("UNKNOWN"))
        }),
        sret,
        variadic: obj.opt_str("variadic")?.map(str::to_owned),
        stack_argument_slots: obj.opt_int("stack_argument_slots")?,
        seh_or_cookie_frame: obj.opt_bool("seh_or_cookie_frame")?,
    })
}

fn parse_vtable(value: &Val<'_>) -> Result<VTableRecord, JsonError> {
    let obj = value.as_object()?;
    let mut memberships = Vec::new();
    for entry in obj.opt_object_array("memberships")? {
        memberships.push(VTableMembership {
            table_va: va_field(entry, "table_va")?,
            slot: u32_field(entry, "slot")?,
            slot_width: opt_u32_field(entry, "slot_width")?,
        });
    }
    let attributed = match obj.opt("abi_attributed") {
        None => None,
        Some(value) => {
            let a = value.as_object()?;
            Some((
                a.req_str("rule")?.to_owned(),
                va_field(a, "table_va")?,
                u32_field(a, "slot")?,
                EvidenceLevel::parse(a.req_str("confidence")?),
            ))
        }
    };
    let triage_addresses = va_list(obj, "triage_addresses")?;
    Ok(VTableRecord {
        memberships,
        attributed_rule: attributed.as_ref().map(|a| a.0.clone()),
        attributed_table: attributed.as_ref().map(|a| a.1),
        attributed_slot: attributed.as_ref().map(|a| a.2),
        attributed_confidence: attributed.map_or(EvidenceLevel::Unknown, |a| a.3),
        triage_addresses,
        triage_family: obj.opt_str("triage_family")?.map(str::to_owned),
    })
}

fn parse_semantics(value: &Val<'_>) -> Result<SemanticsRecord, JsonError> {
    let obj = value.as_object()?;
    let mut claims = Vec::new();
    for entry in obj.opt_object_array("evidence")? {
        claims.push(SemanticClaim {
            claim: entry.req_str("claim")?.to_owned(),
            class: entry.req_str("class")?.to_owned(),
            source: entry.req_str("source")?.to_owned(),
        });
    }
    Ok(SemanticsRecord {
        classification: obj.opt_str("classification")?.map(str::to_owned),
        status: obj.opt_str("semantic_status")?.map(str::to_owned),
        name: obj.opt_str("name")?.map(str::to_owned),
        subsystem: obj.opt_str("subsystem")?.map(str::to_owned),
        triangulation_status: obj.opt_str("triangulation_status")?.map(str::to_owned),
        downstream_unlock_count: obj.opt_int("downstream_unlock_count")?,
        source: obj.opt_str("source")?.map(str::to_owned),
        claims,
        notes: obj
            .opt_str_array("notes")?
            .into_iter()
            .map(str::to_owned)
            .collect(),
        unresolved_questions: obj
            .opt_str_array("unresolved_questions")?
            .into_iter()
            .map(str::to_owned)
            .collect(),
        family: obj.opt_str("semantic_family")?.map(str::to_owned),
        source_workers: obj
            .opt_str_array("source_workers")?
            .into_iter()
            .map(str::to_owned)
            .collect(),
    })
}

fn parse_reconstruction(value: &Val<'_>) -> Result<ReconstructionRecord, JsonError> {
    let obj = value.as_object()?;
    let validation = match obj.opt("validation") {
        None => None,
        Some(value) => Some(parse_validation(value.as_object()?)?),
    };
    Ok(ReconstructionRecord {
        package: obj.opt_str("package")?.map(str::to_owned),
        status: obj.opt_str("status")?.map(str::to_owned),
        review_status: obj.opt_str("review_status")?.map(str::to_owned),
        integration_status: obj.opt_str("integration_status")?.map(str::to_owned),
        reconstructed: obj.opt_bool("reconstructed")?,
        blocked: obj.opt_bool("blocked")?,
        promoted: TriState::parse(obj.req_str("promoted")?)
            .map_err(|e| e.at(obj.child("promoted")))?,
        promotion_schema: obj.opt_str("promotion_schema")?.map(str::to_owned),
        promotion_supersedes: raw_field(obj, "promotion_supersedes")?.map(|raw| raw.0),
        static_status: obj.opt_str("static_status")?.map(str::to_owned),
        generated_source: owned_strings(obj, "generated_source")?,
        handoffs: owned_strings(obj, "handoffs")?,
        metadata: owned_strings(obj, "metadata")?,
        runtime_gate: RuntimeGate::from_bool(obj.opt_bool("runtime_gated")?),
        runtime_validated: obj.opt_int("runtime_validated")?,
        runtime_blocking_reason: raw_field(obj, "runtime_blocking_reason")?.map(|raw| raw.0),
        validation,
    })
}

fn parse_validation(obj: &Obj<'_>) -> Result<ValidationSummary, JsonError> {
    let mut coverage = BTreeMap::new();
    if let Some(value) = obj.opt("coverage") {
        let dimensions = value.as_object()?;
        for (key, value) in dimensions.iter() {
            coverage.insert(key.to_owned(), parse_check(value.as_object()?)?);
        }
    }
    let runtime = match obj.opt("runtime") {
        None => None,
        Some(value) => Some(parse_check(value.as_object()?)?),
    };
    Ok(ValidationSummary {
        schema: obj.req_str("schema")?.to_owned(),
        coverage,
        runtime,
    })
}

fn parse_check(obj: &Obj<'_>) -> Result<ValidationCheck, JsonError> {
    Ok(ValidationCheck {
        status: obj.req_str("status")?.to_owned(),
        coverage: obj.req_str("coverage")?.to_owned(),
        detail: obj.req_str("detail")?.to_owned(),
        evidence: owned_strings(obj, "evidence")?,
    })
}

fn parse_evidence_locations(obj: &Obj<'_>) -> Result<EvidenceLocations, JsonError> {
    let mut additional_packs = Vec::new();
    for entry in obj.opt_object_array("additional_packs")? {
        let rule = entry.req_str("rule")?.to_owned();
        if rule != "containing_function_entry" {
            return Err(schema(
                entry,
                "rule",
                format!(
                    "{rule:?} is not a rule this build knows; the vocabulary is closed at \
                     \"containing_function_entry\""
                ),
            ));
        }
        additional_packs.push(AdditionalPack {
            pack: entry.req_str("pack")?.to_owned(),
            requested_va: va_field(entry, "requested_va")?,
            offset: u32_field(entry, "offset")?,
            rule,
            pack_state: entry.opt_str("pack_state")?.map(str::to_owned),
            pack_content_sha256: entry.opt_str("pack_content_sha256")?.map(str::to_owned),
        });
    }
    Ok(EvidenceLocations {
        pack: obj.opt_str("pack")?.map(str::to_owned),
        pack_state: obj.opt_str("pack_state")?.map(str::to_owned),
        pack_content_sha256: obj.opt_str("pack_content_sha256")?.map(str::to_owned),
        target_address_kind: obj.opt_str("target_address_kind")?.map(str::to_owned),
        validation_report: obj.opt_str("validation_report")?.map(str::to_owned),
        promotion_record: obj.opt_str("promotion_record")?.map(str::to_owned),
        additional_packs,
    })
}

fn parse_provenance_entry(obj: &Obj<'_>, path: &str) -> Result<Provenance, JsonError> {
    let mode = obj.req_str("mode")?;
    let mode = match mode {
        "persisted" => ProvenanceMode::Persisted,
        "derived" => ProvenanceMode::Derived,
        "live" => ProvenanceMode::Live,
        other => {
            return Err(JsonError {
                kind: JsonErrorKind::Schema,
                path: format!("{path}[].mode"),
                message: format!(
                    "{other:?} is not one of persisted | derived | live; a static artifact may not \
                     claim another mode"
                ),
            })
        }
    };
    let reference = obj.req_str("ref")?.to_owned();
    let source_class = obj.req_str("source_class")?;
    let Some(class) = SourceClass::parse(source_class) else {
        return Err(JsonError {
            kind: JsonErrorKind::Schema,
            path: format!("{path}[].source_class"),
            message: format!(
                "{source_class:?} is not one of {}",
                SourceClass::static_classes()
                    .iter()
                    .chain(core::iter::once(&SourceClass::Runtime))
                    .map(|c| c.as_str())
                    .collect::<Vec<_>>()
                    .join(" | ")
            ),
        });
    };
    if !SourceClass::static_classes().contains(&class) {
        return Err(JsonError {
            kind: JsonErrorKind::Schema,
            path: format!("{path}[].source_class"),
            message: format!(
                "a static snapshot may not claim source_class {source_class:?}; that is a runtime \
                 artifact's vocabulary, and a static artifact wearing it is exactly the confusion \
                 the two vocabularies exist to prevent"
            ),
        });
    }
    Ok(Provenance::new(mode, reference, class))
}

fn string_list(value: &Val<'_>) -> Result<Vec<String>, JsonError> {
    match value {
        Val::Array(items) => items
            .iter()
            .map(|item| Ok(item.as_str()?.to_owned()))
            .collect(),
        other => Err(other.type_error("an array of strings")),
    }
}

fn owned_strings(obj: &Obj<'_>, key: &str) -> Result<Vec<String>, JsonError> {
    Ok(obj
        .opt_str_array(key)?
        .into_iter()
        .map(str::to_owned)
        .collect())
}

fn raw_field(obj: &Obj<'_>, key: &str) -> Result<Option<RawJson>, JsonError> {
    match obj.opt(key) {
        None => Ok(None),
        Some(Val::Raw(text)) => Ok(Some(RawJson((*text).to_owned()))),
        Some(other) => Err(other.type_error("a raw JSON value").at(obj.child(key))),
    }
}
