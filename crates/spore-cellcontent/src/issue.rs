//! The domain invariants: what the corpus says a sane record looks like.
//!
//! # Issues, not booleans
//!
//! Every checker returns [`Vec<CellIssue>`], never a `bool`. A boolean answers
//! "is this record sane?" and throws away the only useful part; an issue names
//! the field, the entry index, what was observed, what was expected, and how
//! strong the expectation is. `tools/spore/cellres/cellpop.py` prints
//! `ISSUES 0x…: size=70`; this crate prints the same information as data.
//!
//! # Where each bound comes from
//!
//! Every bound below is transcribed from a Python oracle's `issues()` and from
//! `src/assets/CellResource.cpp`'s `*Issues` functions, and **the two do not
//! always agree**. This crate follows the Python oracle, because the repo's rule
//! is that the corpus outranks the port, and because the Python bounds are the
//! observed sets and ranges while the C++ bounds are the looser envelopes around
//! them. Each disagreement is listed in the module documentation of the record it
//! belongs to and in the crate root; none of them changes a decode outcome, only
//! whether a value is called an issue.
//!
//! # What is *not* checked, and why
//!
//! * `world.populate[i].populate` is emitted as a hard reference by the C++ layer
//!   but **no oracle measures whether it resolves**
//!   ([`crate::claims::WORLD_POPULATE_RESOLUTION_UNMEASURED`]). It resolves
//!   through [`crate::reference::CellReferenceResolver`] like every other
//!   reference, but [`world_issues`] does not assert it: an unmeasured invariant
//!   asserted in a checker is a guess with a green tick next to it.
//! * `cMarker.encounterScale` and `cCellStructureResource.numAttachments` beyond
//!   the C++ range: neither oracle bounds them, so this crate follows the C++
//!   only where the C++ is the sole source and says so.
//! * Soft ids (`creatureID`, effect ids) are **not** issues. They are
//!   non-findings, reported through `Fact::unavailable`, because there is no
//!   registry to check them against.

use spore_core::{EvidenceLevel, ResourceKey};

use crate::cell::{CellAi, CellCell, CELL_TYPE};
use crate::globals::{CellGlobals, GLOBALS_TYPE};
use crate::look::{CellLookAlgorithm, CellLookTable, LOOK_ALGORITHM_TYPE, LOOK_TABLE_TYPE};
use crate::loot::{CellLootTable, LOOT_TABLE_TYPE};
use crate::maps::{CellBackgroundMap, CellEffectMap, BACKGROUND_MAP_TYPE, EFFECT_MAP_TYPE};
use crate::populate::{CellPopulate, POPULATE_TYPE};
use crate::reference::CellCatalogue;
use crate::scalar::Scalar;
use crate::spawn::{CellPowers, CellRandomCreature, POWERS_TYPE, RANDOM_CREATURE_TYPE};
use crate::structure::{CellStructure, STRUCTURE_TYPE};
use crate::world::{CellWorld, WORLD_TYPE};

/// The entry index used by a record-level (non-list) field.
pub const RECORD_LEVEL: usize = usize::MAX;

/// What kind of invariant an issue violates.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum IssueKind {
    /// A float is `NaN` or infinite.
    NotFinite,
    /// A value is outside the observed range or set.
    OutOfRange,
    /// A value is not one of the enumerated constants the corpus uses.
    NotAnEnumMember,
    /// A one-byte flag is neither 0 nor 1.
    NotABoolean,
    /// A field that reads as zero everywhere observed is non-zero here.
    DeadFieldNonZero,
    /// Alignment padding is non-zero.
    PaddingNonZero,
    /// A non-null reference names an instance the catalogue does not hold.
    UnresolvedReference,
    /// An integer bound is inverted — `min > max` with no "any" sentinel.
    InvertedRange,
}

/// How strongly an invariant is believed.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum IssueConfidence {
    /// The corpus value set is a closed enumeration, not an interval. A value
    /// outside it is a value this build has never seen.
    ObservedSet,
    /// The corpus bound is an interval that no observed record reaches. Values
    /// outside it are unexpected but not impossible.
    ObservedRange,
    /// The invariant is a cross-record resolution claim.
    Resolution,
}

impl IssueConfidence {
    /// The evidence grade matching this confidence.
    pub const fn level(self) -> EvidenceLevel {
        match self {
            Self::ObservedSet | Self::ObservedRange => EvidenceLevel::Observed,
            Self::Resolution => EvidenceLevel::Verified,
        }
    }
}

/// What was observed at the offending field.
#[derive(Debug, Clone, PartialEq)]
pub enum IssueValue {
    /// A decoded scalar.
    Scalar(Scalar),
    /// Raw bytes, used for padding.
    Bytes(Vec<u8>),
}

impl IssueValue {
    /// The scalar, when that is what was observed.
    pub fn scalar(&self) -> Option<Scalar> {
        match self {
            Self::Scalar(value) => Some(*value),
            Self::Bytes(_) => None,
        }
    }
}

/// One violated domain invariant.
#[derive(Debug, Clone, PartialEq)]
pub struct CellIssue {
    /// What sort of invariant this breaks.
    pub kind: IssueKind,
    /// The record type word of the record that carries the field.
    pub record_type: u32,
    /// The field's name in the record's own spelling.
    pub field: &'static str,
    /// The entry index, or [`RECORD_LEVEL`] for a record-level field.
    pub index: usize,
    /// What the record actually holds.
    pub observed: IssueValue,
    /// What the corpus says it should hold, in prose.
    pub expected: &'static str,
    /// How strongly `expected` is believed.
    pub confidence: IssueConfidence,
}

impl CellIssue {
    /// The evidence grade of this issue's expectation.
    pub const fn level(&self) -> EvidenceLevel {
        self.confidence.level()
    }

    /// The record type word of the offending record.
    pub const fn type_id(&self) -> u32 {
        self.record_type
    }

    /// A one-line rendering, for logs and test failures.
    pub fn describe(&self) -> String {
        let where_ = if self.index == RECORD_LEVEL {
            format!("{} {}", self.record_name(), self.field)
        } else {
            format!(
                "{} {}#{index}",
                self.record_name(),
                self.field,
                index = self.index
            )
        };
        let observed = match &self.observed {
            IssueValue::Scalar(value) => value.to_string(),
            IssueValue::Bytes(bytes) => format!(
                "[{}]",
                bytes
                    .iter()
                    .map(|byte| format!("{byte:02x}"))
                    .collect::<Vec<_>>()
                    .join(" ")
            ),
        };
        format!(
            "{where_}: {} = {observed}, want {}",
            self.kind_name(),
            self.expected
        )
    }

    const fn record_name(&self) -> &'static str {
        record_name(self.record_type)
    }

    const fn kind_name(&self) -> &'static str {
        match self.kind {
            IssueKind::NotFinite => "non-finite float",
            IssueKind::OutOfRange => "out of range",
            IssueKind::NotAnEnumMember => "not an observed value",
            IssueKind::NotABoolean => "not a boolean",
            IssueKind::DeadFieldNonZero => "dead field is non-zero",
            IssueKind::PaddingNonZero => "padding is non-zero",
            IssueKind::UnresolvedReference => "unresolved reference",
            IssueKind::InvertedRange => "inverted range",
        }
    }
}

const fn record_name(type_id: u32) -> &'static str {
    match type_id {
        GLOBALS_TYPE => "globals",
        EFFECT_MAP_TYPE => "effectMap",
        BACKGROUND_MAP_TYPE => "backgroundMap",
        STRUCTURE_TYPE => "structure",
        WORLD_TYPE => "world",
        RANDOM_CREATURE_TYPE => "randomCreature",
        POWERS_TYPE => "powers",
        LOOK_TABLE_TYPE => "look_table",
        LOOK_ALGORITHM_TYPE => "look_algorithm",
        LOOT_TABLE_TYPE => "lootTable",
        POPULATE_TYPE => "populate",
        CELL_TYPE => "cell",
        _ => "unknown",
    }
}

fn scalar_issue(
    kind: IssueKind,
    record_type: u32,
    field: &'static str,
    index: usize,
    observed: Scalar,
    expected: &'static str,
    confidence: IssueConfidence,
) -> CellIssue {
    CellIssue {
        kind,
        record_type,
        field,
        index,
        observed: IssueValue::Scalar(observed),
        expected,
        confidence,
    }
}

fn in_f32(value: f32, low: f32, high: f32) -> bool {
    // Written as a positive predicate so that NaN fails it. `value >= low` alone
    // is false for NaN, and `value <= high` is false for NaN, so the conjunction
    // is false -- which is what we want, and is stated here rather than relied
    // upon as a floating-point curiosity.
    (value >= low) && (value <= high)
}

fn finite_and_in(value: f32, low: f32, high: f32) -> bool {
    value.is_finite() && in_f32(value, low, high)
}

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------

/// The `globals` enum fields `cellres.py` bounds at `<= 8`.
const GLOBALS_ENUM_FIELDS: &[&str] = &[
    "gameMode",
    "controlMethod",
    "editorMethod",
    "tutorialMethod",
    "endingMethod",
    "eyeMethod",
    "field_208",
];

/// The `globals` count fields `cellres.py` bounds at `<= 1024`.
const GLOBALS_SMALL_INT_FIELDS: &[&str] = &["numHighLOD_FG", "numHighLOD_BG"];

/// Checks a globals record.
///
/// Bounds, all from `cellres.py::validate`:
///
/// * every float field is finite and `|v| <= 1e6`;
/// * `gameMode`, `controlMethod`, `editorMethod`, `tutorialMethod`,
///   `endingMethod`, `eyeMethod` and `field_208` are at most 8;
/// * `numHighLOD_FG` and `numHighLOD_BG` are at most 1024.
///
/// **The C++ reference checks none of this.** `parseCellGlobals` in
/// `src/assets/CellResource.cpp` returns after reading the 69 fields and has no
/// `cellGlobalsIssues` counterpart at all, so the whole of this function is
/// Python-only. It is reported here because the oracle's bounds hold on the one
/// real record, and because a caller wanting a sanity check should not have to
/// re-derive it.
///
/// In addition, the seventeen reference-bearing slots are resolved against
/// `catalogue` — the cross-record half of "the globals record is consistent",
/// which no oracle checks because `cellres.py` only ever loads the single EP1
/// record and has no other catalogue to resolve against.
pub fn globals_issues(globals: &CellGlobals, catalogue: &CellCatalogue) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (name, value) in globals.entries() {
        match value {
            Scalar::F32(v) => {
                if !finite_and_in(v, -1.0e6, 1.0e6) {
                    out.push(scalar_issue(
                        IssueKind::NotFinite,
                        GLOBALS_TYPE,
                        name,
                        RECORD_LEVEL,
                        value,
                        "a finite float with |v| <= 1e6",
                        IssueConfidence::ObservedRange,
                    ));
                }
            }
            Scalar::U32(v) => {
                if GLOBALS_ENUM_FIELDS.contains(&name) && v > 8 {
                    out.push(scalar_issue(
                        IssueKind::OutOfRange,
                        GLOBALS_TYPE,
                        name,
                        RECORD_LEVEL,
                        value,
                        "<= 8",
                        IssueConfidence::ObservedRange,
                    ));
                }
                if GLOBALS_SMALL_INT_FIELDS.contains(&name) && v > 1024 {
                    out.push(scalar_issue(
                        IssueKind::OutOfRange,
                        GLOBALS_TYPE,
                        name,
                        RECORD_LEVEL,
                        value,
                        "<= 1024",
                        IssueConfidence::ObservedRange,
                    ));
                }
            }
            Scalar::I32(_) | Scalar::U8(_) => {}
        }
    }
    for (name, value) in globals.reference_slots() {
        if value == 0 {
            continue;
        }
        // A slot with no type word is a reference non-finding, not a failed
        // lookup, so it is skipped here and reported by the reference layer.
        let Some(target) = reference_target_for(name) else {
            continue;
        };
        if !catalogue.holds_instance(target, value) {
            out.push(scalar_issue(
                IssueKind::UnresolvedReference,
                GLOBALS_TYPE,
                name,
                RECORD_LEVEL,
                Scalar::U32(value),
                "an instance the catalogue holds",
                IssueConfidence::Resolution,
            ));
        }
    }
    out
}

/// The record type a globals reference slot declares, or `None` when the slot
/// stores no type word — in which case there is nothing to resolve and nothing
/// to report.
fn reference_target_for(name: &str) -> Option<u32> {
    crate::globals::GLOBALS_REFERENCE_FIELDS
        .iter()
        .find(|(field, _)| *field == name)
        .and_then(|(_, type_id)| *type_id)
}

// ---------------------------------------------------------------------------
// cell
// ---------------------------------------------------------------------------

const CELL_TYPES: &[u32] = &[0, 1, 2, 3, 4, 5, 6, 7];
const CELL_UNLOCK_TYPES: &[u32] = &[0, 2, 4, 5, 6, 7, 8, 10];
const CELL_DENSITIES: &[u32] = &[0, 1, 3, 4];
const AI_FOODS: &[u32] = &[0, 3];

fn check_ai_block(ai: &CellAi, index: usize, out: &mut Vec<CellIssue>) {
    let kind_ok = ai.kind == 0
        || ai.kind == crate::cell::AI_TYPE_EMPTY
        || (0x1000..=0x10FF).contains(&ai.kind);
    if !kind_ok {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            CELL_TYPE,
            "ai.type",
            index,
            Scalar::U32(ai.kind),
            "0, 0x1000..=0x10FF, or 0xFFFFFFFF",
            IssueConfidence::ObservedSet,
        ));
    }
    if ai.movement_style & !0xF != 0 {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            CELL_TYPE,
            "ai.movementStyle",
            index,
            Scalar::U32(ai.movement_style),
            "a value with no bits above 0xF",
            IssueConfidence::ObservedRange,
        ));
    }
    if !AI_FOODS.contains(&ai.food) {
        out.push(scalar_issue(
            IssueKind::NotAnEnumMember,
            CELL_TYPE,
            "ai.food",
            index,
            Scalar::U32(ai.food),
            "0 or 3",
            IssueConfidence::ObservedSet,
        ));
    }
    if !(0..64).contains(&ai.num_arcs) {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            CELL_TYPE,
            "ai.numArcs",
            index,
            Scalar::I32(ai.num_arcs),
            "0..=63",
            IssueConfidence::ObservedRange,
        ));
    }
    for (name, value) in ai.flags() {
        if value > 1 {
            out.push(scalar_issue(
                IssueKind::NotABoolean,
                CELL_TYPE,
                name,
                index,
                Scalar::U8(value),
                "0 or 1",
                IssueConfidence::ObservedSet,
            ));
        }
    }
    for (slot, value) in ai.floats().into_iter().enumerate() {
        if !finite_and_in(value, -1.0e4, 1.0e4) {
            out.push(scalar_issue(
                IssueKind::NotFinite,
                CELL_TYPE,
                AI_FLOAT_FIELD_NAMES[slot],
                index,
                Scalar::F32(value),
                "a finite float with |v| <= 1e4",
                IssueConfidence::ObservedRange,
            ));
        }
    }
}

/// The 30 `cAIData` float fields, in layout order, matching
/// [`CellAi::floats`].
pub const AI_FLOAT_FIELD_NAMES: &[&str] = &[
    "awarenessRadius",
    "awarenessRadiusFood",
    "awarenessRadiusPredator",
    "speed",
    "chaseSpeed",
    "wanderSpeed",
    "fleeSpeed",
    "fearsNearbyDamageRadius",
    "fearsNearbyDeathRadius",
    "fearsNearbyDamageTime",
    "fearsNearbyDeathTime",
    "protectRadius",
    "protectTime",
    "turnFactor",
    "spawnTime",
    "spawnRestTime",
    "arcLength",
    "arcLengthSecondary",
    "digestionTime",
    "fleeTime",
    "fleeRestTime",
    "chaseTime",
    "chaseRestTime",
    "awakeTime",
    "sleepTime",
    "hatchDuration",
    "poisonRecharge",
    "electricRecharge",
    "electricRechargeVsSmall",
    "electricDischarge",
];

/// The three AI tier names, matching the order of [`crate::cell::CellCell::ai_tiers`].
pub const AI_TIER_NAMES: &[&str] = &["ai", "aiHard", "aiEasy"];

/// Checks a cell record.
///
/// Bounds, from `cell.py::sanity` and `cellCellIssues`:
///
/// * `cellType` in `0..=7`; `unlockType` in `{0,2,4,5,6,7,8,10}`;
///   `density` in `{0,1,3,4}`; `hp` in `1..=4`.
/// * `0 <= sizeMin <= 10` and `sizeMin <= sizeMax <= 10`. **NaN fails here** —
///   the Python form `0.0 <= sizeMin <= 10.0` rejects NaN and the C++ form
///   `sizeMin < 0 || sizeMin > 10 || sizeMin > sizeMax` does not. This crate
///   follows Python; see the crate documentation.
/// * the six record-level flags are 0 or 1. **Python-only**: the C++ reference
///   stores them as `bool`, so the value 2 is destroyed before any check could
///   run. This crate keeps them as `u8` so the invariant is expressible at all.
/// * each AI tier's `type`, `movementStyle`, `food`, `numArcs`, nine flags and
///   thirty floats.
/// * `eatFoodValue >= 0` and `eatHpValue >= 0`.
/// * `structure` resolves to a real `0x4B9EF6DC` instance. This is
///   `cellstruct.py`'s cross-check (`refs_ok == len(cell_refs)`, 165 of 165),
///   reported here rather than in `cellstruct.py` because the direction of the
///   reference is `cell -> structure`.
pub fn cell_issues(cell: &CellCell, catalogue: &CellCatalogue) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (name, value) in cell.scalars() {
        match (name, value) {
            ("cellType", Scalar::U32(v)) if !CELL_TYPES.contains(&v) => out.push(scalar_issue(
                IssueKind::OutOfRange,
                CELL_TYPE,
                name,
                RECORD_LEVEL,
                value,
                "0..=7",
                IssueConfidence::ObservedRange,
            )),
            ("unlockType", Scalar::U32(v)) if !CELL_UNLOCK_TYPES.contains(&v) => {
                out.push(scalar_issue(
                    IssueKind::NotAnEnumMember,
                    CELL_TYPE,
                    name,
                    RECORD_LEVEL,
                    value,
                    "0, 2, 4, 5, 6, 7, 8 or 10",
                    IssueConfidence::ObservedSet,
                ))
            }
            ("density", Scalar::U32(v)) if !CELL_DENSITIES.contains(&v) => out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                CELL_TYPE,
                name,
                RECORD_LEVEL,
                value,
                "0, 1, 3 or 4",
                IssueConfidence::ObservedSet,
            )),
            ("hp", Scalar::I32(v)) if !(1..=4).contains(&v) => out.push(scalar_issue(
                IssueKind::OutOfRange,
                CELL_TYPE,
                name,
                RECORD_LEVEL,
                value,
                "1..=4",
                IssueConfidence::ObservedSet,
            )),
            ("eatFoodValue", Scalar::I32(v)) | ("eatHpValue", Scalar::I32(v)) if v < 0 => {
                out.push(scalar_issue(
                    IssueKind::OutOfRange,
                    CELL_TYPE,
                    name,
                    RECORD_LEVEL,
                    value,
                    ">= 0",
                    IssueConfidence::ObservedRange,
                ))
            }
            ("sizeMin", Scalar::F32(v)) | ("sizeMax", Scalar::F32(v)) if !in_f32(v, 0.0, 10.0) => {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    CELL_TYPE,
                    name,
                    RECORD_LEVEL,
                    value,
                    "0.0..=10.0 (NaN fails)",
                    IssueConfidence::ObservedRange,
                ))
            }
            (_, Scalar::U8(v)) if v > 1 => out.push(scalar_issue(
                IssueKind::NotABoolean,
                CELL_TYPE,
                name,
                RECORD_LEVEL,
                Scalar::U8(v),
                "0 or 1",
                IssueConfidence::ObservedSet,
            )),
            _ => {}
        }
    }
    if cell.size_min > cell.size_max {
        out.push(scalar_issue(
            IssueKind::InvertedRange,
            CELL_TYPE,
            "sizeMin",
            RECORD_LEVEL,
            Scalar::F32(cell.size_min),
            "sizeMin <= sizeMax",
            IssueConfidence::ObservedRange,
        ));
    }
    for (index, ai) in cell.ai_tiers().iter().enumerate() {
        check_ai_block(ai, index, &mut out);
    }
    if cell.structure != 0 && !catalogue.holds_instance(STRUCTURE_TYPE, cell.structure) {
        out.push(scalar_issue(
            IssueKind::UnresolvedReference,
            CELL_TYPE,
            "structure",
            RECORD_LEVEL,
            Scalar::U32(cell.structure),
            "an instance the catalogue holds",
            IssueConfidence::Resolution,
        ));
    }
    out
}

// ---------------------------------------------------------------------------
// world
// ---------------------------------------------------------------------------

/// Checks a cell-world record.
///
/// Bounds, from `cellworld.py::issues`: `numPopulate <= 64`, `numAdvect <= 64`,
/// `startTile` in `{0,1}`, `playerSize` equal to `0xFFFFFFFF` or in `1..=10`,
/// `stageScale` in `0..=30`, advect `playerSize` in `-1..=30`, and
/// `strength`/`variance`/`period` finite with `|v| <= 10`.
pub fn world_issues(world: &CellWorld) -> Vec<CellIssue> {
    let mut out = Vec::new();
    if world.num_populate > 64 {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            WORLD_TYPE,
            "numPopulate",
            RECORD_LEVEL,
            Scalar::U32(world.num_populate),
            "<= 64",
            IssueConfidence::ObservedRange,
        ));
    }
    if world.num_advect > 64 {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            WORLD_TYPE,
            "numAdvect",
            RECORD_LEVEL,
            Scalar::U32(world.num_advect),
            "<= 64",
            IssueConfidence::ObservedRange,
        ));
    }
    for (index, entry) in world.populate.iter().enumerate() {
        if entry.start_tile > 1 {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                WORLD_TYPE,
                "level.startTile",
                index,
                Scalar::U8(entry.start_tile),
                "0 or 1",
                IssueConfidence::ObservedSet,
            ));
        }
        let any = entry.player_size == spore_core::WILDCARD;
        if !any && (entry.player_size == 0 || entry.player_size > 10) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                WORLD_TYPE,
                "level.playerSize",
                index,
                Scalar::U32(entry.player_size),
                "1..=10, or 0xFFFFFFFF for any",
                IssueConfidence::ObservedSet,
            ));
        }
    }
    for (index, entry) in world.advect.iter().enumerate() {
        if entry.stage_scale > 30 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                WORLD_TYPE,
                "advect.stageScale",
                index,
                Scalar::U32(entry.stage_scale),
                "0..=30",
                IssueConfidence::ObservedRange,
            ));
        }
        if !(-1..=30).contains(&entry.player_size) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                WORLD_TYPE,
                "advect.playerSize",
                index,
                Scalar::I32(entry.player_size),
                "-1..=30",
                IssueConfidence::ObservedRange,
            ));
        }
        for (value, name) in crate::world::CellAdvectEntry::floats(entry)
            .into_iter()
            .zip(["advect.strength", "advect.variance", "advect.period"])
        {
            if !finite_and_in(value, -10.0, 10.0) {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    WORLD_TYPE,
                    name,
                    index,
                    Scalar::F32(value),
                    "a finite float with |v| <= 10",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
    }
    out
}

// ---------------------------------------------------------------------------
// populate
// ---------------------------------------------------------------------------

/// Checks a populate record.
///
/// Bounds, from `cellpop.py::issues` plus `cellPopulateIssues`:
///
/// * `scale` in `{0,1,2,3,4}`. **The C++ bound is `scale <= 10`** — a
///   disagreement, resolved in favour of Python's closed observed set.
/// * `maskTexture == 0`; the four dead marker fields are zero; every
///   `encounterPopulate` is zero. All three are C++-only.
/// * `numMarkers <= 64`.
/// * every non-null `distributeCell` and `clusterCell` resolves to a `0xDFAD9F51`.
/// * `zOffset` and `zOffsetMax` in `0..=100`; `plantType <= 10`; `type <= 10`;
///   the four counts finite in `-1..=1000`; `size` in `0..=30`; `parts` in
///   `0..=30`; `linear` in `{0,1}`.
pub fn populate_issues(populate: &CellPopulate, catalogue: &CellCatalogue) -> Vec<CellIssue> {
    let mut out = Vec::new();
    if !matches!(populate.scale, 0..=4) {
        out.push(scalar_issue(
            IssueKind::NotAnEnumMember,
            POPULATE_TYPE,
            "scale",
            RECORD_LEVEL,
            Scalar::U32(populate.scale),
            "0, 1, 2, 3 or 4",
            IssueConfidence::ObservedSet,
        ));
    }
    if populate.mask_texture != 0 {
        out.push(scalar_issue(
            IssueKind::DeadFieldNonZero,
            POPULATE_TYPE,
            "maskTexture",
            RECORD_LEVEL,
            Scalar::U32(populate.mask_texture),
            "0 on every observed record",
            IssueConfidence::ObservedSet,
        ));
    }
    if populate.num_markers > 64 {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            POPULATE_TYPE,
            "numMarkers",
            RECORD_LEVEL,
            Scalar::U32(populate.num_markers),
            "<= 64",
            IssueConfidence::ObservedRange,
        ));
    }
    for (index, marker) in populate.markers.iter().enumerate() {
        for (name, value) in marker.dead_fields() {
            if value != 0 {
                out.push(scalar_issue(
                    IssueKind::DeadFieldNonZero,
                    POPULATE_TYPE,
                    name,
                    index,
                    Scalar::U32(value),
                    "0 on all 387 observed markers",
                    IssueConfidence::ObservedSet,
                ));
            }
        }
        if marker.encounter_populate != 0 {
            out.push(scalar_issue(
                IssueKind::DeadFieldNonZero,
                POPULATE_TYPE,
                "encounterPopulate",
                index,
                Scalar::U32(marker.encounter_populate),
                "0 on every observed marker",
                IssueConfidence::ObservedSet,
            ));
        }
        for (field, value) in [
            ("distributeCell", marker.distribute_cell),
            ("clusterCell", marker.cluster_cell),
        ] {
            if value != 0 && !catalogue.holds_instance(CELL_TYPE, value) {
                out.push(scalar_issue(
                    IssueKind::UnresolvedReference,
                    POPULATE_TYPE,
                    field,
                    index,
                    Scalar::U32(value),
                    "an instance the catalogue holds",
                    IssueConfidence::Resolution,
                ));
            }
        }
        if marker.plant_type > 10 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                POPULATE_TYPE,
                "plantType",
                index,
                Scalar::U32(marker.plant_type),
                "<= 10",
                IssueConfidence::ObservedRange,
            ));
        }
        if marker.marker_type > 10 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                POPULATE_TYPE,
                "type",
                index,
                Scalar::U32(marker.marker_type),
                "<= 10",
                IssueConfidence::ObservedRange,
            ));
        }
        for (name, value) in marker.counts() {
            if !finite_and_in(value, -1.0, 1000.0) {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    POPULATE_TYPE,
                    name,
                    index,
                    Scalar::F32(value),
                    "a finite float in -1.0..=1000.0",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
        if !(0..=30).contains(&marker.size) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                POPULATE_TYPE,
                "size",
                index,
                Scalar::I32(marker.size),
                "0..=30",
                IssueConfidence::ObservedRange,
            ));
        }
        if !(0..=30).contains(&marker.parts) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                POPULATE_TYPE,
                "parts",
                index,
                Scalar::I32(marker.parts),
                "0..=30",
                IssueConfidence::ObservedRange,
            ));
        }
        if marker.linear > 1 {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                POPULATE_TYPE,
                "linear",
                index,
                Scalar::I32(marker.linear),
                "0 or 1",
                IssueConfidence::ObservedSet,
            ));
        }
        for (field, value) in [
            ("zOffset", marker.z_offset),
            ("zOffsetMax", marker.z_offset_max),
        ] {
            if !in_f32(value, 0.0, 100.0) {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    POPULATE_TYPE,
                    field,
                    index,
                    Scalar::F32(value),
                    "0.0..=100.0 (NaN fails)",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
    }
    out
}

// ---------------------------------------------------------------------------
// structure
// ---------------------------------------------------------------------------

/// Checks a structure record.
///
/// Bounds, from `cellstruct.py::issues` plus `cellStructureIssues`:
///
/// * `onStartHatch == 0` and `numAttachments` in `0..=16` (both C++-only).
/// * `bone` in `{0,3,-1}`; `type <= 10`; `structure == 0`; `levelMin` in
///   `{0,-1}`; `levelMax` in `{0,10,-1}`; each colour channel finite in
///   `0..=2`.
/// * every non-null `randomCreature` resolves to a `0xF9C3D770`. This is
///   C++-referenced and corpus-checkable but **no oracle asserts it**; the
///   confidence is therefore `Resolution` rather than `ObservedSet`.
/// * a negative `effectID` is **not** reported, because it is legitimate.
///   `src/assets/CellResource.hpp` documents the field as "128 distinct,
///   negative ok", and 108 of the real attachments carry a negative value. The
///   hazard is the *unsigned cast*, not the sign: the C++ reference emits the
///   value as a reference via `static_cast<uint32_t>`, which turns `-1` into
///   `0xFFFFFFFF` — the same word it uses for "unset". That collapse is handled
///   by [`crate::reference`] emitting the reference only for non-negative values,
///   which is a statement about the reference layer and not a domain finding.
pub fn structure_issues(structure: &CellStructure, catalogue: &CellCatalogue) -> Vec<CellIssue> {
    let mut out = Vec::new();
    if structure.on_start_hatch != 0 {
        out.push(scalar_issue(
            IssueKind::DeadFieldNonZero,
            STRUCTURE_TYPE,
            "onStartHatch",
            RECORD_LEVEL,
            Scalar::U32(structure.on_start_hatch),
            "0 on every observed record",
            IssueConfidence::ObservedSet,
        ));
    }
    if structure.num_attachments > 16 {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            STRUCTURE_TYPE,
            "numAttachments",
            RECORD_LEVEL,
            Scalar::U32(structure.num_attachments),
            "<= 16",
            IssueConfidence::ObservedRange,
        ));
    }
    for (index, attachment) in structure.attachments.iter().enumerate() {
        if !matches!(attachment.bone, 0 | 3 | -1) {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                STRUCTURE_TYPE,
                "bone",
                index,
                Scalar::I32(attachment.bone),
                "0, 3 or -1",
                IssueConfidence::ObservedSet,
            ));
        }
        if attachment.attachment_type > 10 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                STRUCTURE_TYPE,
                "type",
                index,
                Scalar::U32(attachment.attachment_type),
                "<= 10",
                IssueConfidence::ObservedRange,
            ));
        }
        if attachment.structure != 0 {
            out.push(scalar_issue(
                IssueKind::DeadFieldNonZero,
                STRUCTURE_TYPE,
                "attachment.structure",
                index,
                Scalar::U32(attachment.structure),
                "0 on every observed attachment",
                IssueConfidence::ObservedSet,
            ));
        }
        if !matches!(attachment.level_min, 0 | -1) {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                STRUCTURE_TYPE,
                "levelMin",
                index,
                Scalar::I32(attachment.level_min),
                "0 or -1",
                IssueConfidence::ObservedSet,
            ));
        }
        if !matches!(attachment.level_max, 0 | 10 | -1) {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                STRUCTURE_TYPE,
                "levelMax",
                index,
                Scalar::I32(attachment.level_max),
                "0, 10 or -1",
                IssueConfidence::ObservedSet,
            ));
        }
        for (channel, value) in attachment.color.iter().enumerate() {
            if !in_f32(*value, 0.0, 2.0) {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    STRUCTURE_TYPE,
                    ["color.r", "color.g", "color.b"][channel],
                    index,
                    Scalar::F32(*value),
                    "0.0..=2.0 (NaN fails)",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
        if attachment.random_creature != 0
            && !catalogue.holds_instance(RANDOM_CREATURE_TYPE, attachment.random_creature)
        {
            out.push(scalar_issue(
                IssueKind::UnresolvedReference,
                STRUCTURE_TYPE,
                "randomCreature",
                index,
                Scalar::U32(attachment.random_creature),
                "an instance the catalogue holds",
                IssueConfidence::Resolution,
            ));
        }
    }
    out
}

// ---------------------------------------------------------------------------
// loot table
// ---------------------------------------------------------------------------

/// Checks a loot-table record.
///
/// Bounds, from `cellloot.py::issues` plus `cellLootTableIssues`:
///
/// * `minRadius` and `maxRadius` in `0..=10`; `initialAlpha` in `0..=2`;
///   `expelForce` in `0..=100`; `delay` in `0..=10`. **The C++ bound is
///   `0..=1000` for all five** — a disagreement, resolved in favour of Python's
///   per-field observed ranges.
/// * `effect == 0`; `mustHavePart` in `{0,1}`.
/// * entry `type <= 5`; `weight` finite in `0..=1000`; `count` and `countDelta`
///   in `-10..=64`; `levelOffset` in `-16..=16`.
/// * every non-null entry `cell` and `table` resolves.
/// * the three header pad bytes are zero. Neither oracle reads them — `cellloot.py`
///   steps over them with `3x` — so this check is this crate's alone, made
///   possible only because the decoder stores them.
pub fn loot_table_issues(table: &CellLootTable, catalogue: &CellCatalogue) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (field, value, low, high) in [
        ("minRadius", table.min_radius, 0.0f32, 10.0f32),
        ("maxRadius", table.max_radius, 0.0f32, 10.0f32),
        ("initialAlpha", table.initial_alpha, 0.0f32, 2.0f32),
        ("expelForce", table.expel_force, 0.0f32, 100.0f32),
        ("delay", table.delay, 0.0f32, 10.0f32),
    ] {
        if !in_f32(value, low, high) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                LOOT_TABLE_TYPE,
                field,
                RECORD_LEVEL,
                Scalar::F32(value),
                "a finite float within the observed range",
                IssueConfidence::ObservedRange,
            ));
        }
    }
    if table.effect != 0 {
        out.push(scalar_issue(
            IssueKind::DeadFieldNonZero,
            LOOT_TABLE_TYPE,
            "effect",
            RECORD_LEVEL,
            Scalar::I32(table.effect),
            "0 on every observed record",
            IssueConfidence::ObservedSet,
        ));
    }
    if table.must_have_part > 1 {
        out.push(scalar_issue(
            IssueKind::NotAnEnumMember,
            LOOT_TABLE_TYPE,
            "mustHavePart",
            RECORD_LEVEL,
            Scalar::U8(table.must_have_part),
            "0 or 1",
            IssueConfidence::ObservedSet,
        ));
    }
    if !table.header_padding.iter().all(|byte| *byte == 0) {
        out.push(CellIssue {
            kind: IssueKind::PaddingNonZero,
            record_type: LOOT_TABLE_TYPE,
            field: "headerPadding",
            index: RECORD_LEVEL,
            observed: IssueValue::Bytes(table.header_padding.to_vec()),
            expected: "all zero on every observed record",
            confidence: IssueConfidence::ObservedSet,
        });
    }
    for (index, entry) in table.entries.iter().enumerate() {
        if entry.entry_type > 5 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                LOOT_TABLE_TYPE,
                "entry.type",
                index,
                Scalar::U32(entry.entry_type),
                "<= 5",
                IssueConfidence::ObservedRange,
            ));
        }
        if entry.cell != 0 && !catalogue.holds_instance(CELL_TYPE, entry.cell) {
            out.push(scalar_issue(
                IssueKind::UnresolvedReference,
                LOOT_TABLE_TYPE,
                "entry.cell",
                index,
                Scalar::U32(entry.cell),
                "an instance the catalogue holds",
                IssueConfidence::Resolution,
            ));
        }
        if entry.table != 0 && !catalogue.holds_instance(LOOT_TABLE_TYPE, entry.table) {
            out.push(scalar_issue(
                IssueKind::UnresolvedReference,
                LOOT_TABLE_TYPE,
                "entry.table",
                index,
                Scalar::U32(entry.table),
                "an instance the catalogue holds",
                IssueConfidence::Resolution,
            ));
        }
        if !in_f32(entry.weight, 0.0, 1000.0) {
            out.push(scalar_issue(
                IssueKind::NotFinite,
                LOOT_TABLE_TYPE,
                "entry.weight",
                index,
                Scalar::F32(entry.weight),
                "0.0..=1000.0 (NaN fails)",
                IssueConfidence::ObservedRange,
            ));
        }
        for (field, value, low, high) in [
            ("entry.count", entry.count, -10i32, 64i32),
            ("entry.countDelta", entry.count_delta, -10, 64),
            ("entry.levelOffset", entry.level_offset, -16, 16),
        ] {
            if value < low || value > high {
                out.push(scalar_issue(
                    IssueKind::OutOfRange,
                    LOOT_TABLE_TYPE,
                    field,
                    index,
                    Scalar::I32(value),
                    "within the observed bound",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
    }
    out
}

// ---------------------------------------------------------------------------
// look records
// ---------------------------------------------------------------------------

/// Checks a look-table record: `type` in `0..=31` and `value` finite in
/// `0..=100`, from `celllook.py::issues_table`.
pub fn look_table_issues(table: &CellLookTable) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (index, entry) in table.entries.iter().enumerate() {
        if !(0..=31).contains(&entry.entry_type) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                LOOK_TABLE_TYPE,
                "entry.type",
                index,
                Scalar::I32(entry.entry_type),
                "0..=31",
                IssueConfidence::ObservedRange,
            ));
        }
        if !in_f32(entry.value, 0.0, 100.0) {
            out.push(scalar_issue(
                IssueKind::NotFinite,
                LOOK_TABLE_TYPE,
                "entry.value",
                index,
                Scalar::F32(entry.value),
                "0.0..=100.0 (NaN fails)",
                IssueConfidence::ObservedRange,
            ));
        }
    }
    out
}

/// Checks a look-algorithm record: `type <= 5`, a plausible `action`, and every
/// non-null `player`/`npc`/`epic` resolving to a `0x8C042499` instance.
pub fn look_algorithm_issues(
    algorithm: &CellLookAlgorithm,
    catalogue: &CellCatalogue,
) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (index, entry) in algorithm.entries.iter().enumerate() {
        if entry.entry_type > 5 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                LOOK_ALGORITHM_TYPE,
                "entry.type",
                index,
                Scalar::U32(entry.entry_type),
                "<= 5",
                IssueConfidence::ObservedRange,
            ));
        }
        if !crate::look::CellLookAlgorithmEntry::is_action_plausible(entry.action) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                LOOK_ALGORITHM_TYPE,
                "entry.action",
                index,
                Scalar::U32(entry.action),
                "0, 18..=22, 0xFFFFFFFF, or any value <= 60",
                IssueConfidence::ObservedRange,
            ));
        }
        for (field, value) in [
            ("entry.player", entry.player),
            ("entry.npc", entry.npc),
            ("entry.epic", entry.epic),
        ] {
            if value != 0 && !catalogue.holds_instance(LOOK_TABLE_TYPE, value) {
                out.push(scalar_issue(
                    IssueKind::UnresolvedReference,
                    LOOK_ALGORITHM_TYPE,
                    field,
                    index,
                    Scalar::U32(value),
                    "an instance the catalogue holds",
                    IssueConfidence::Resolution,
                ));
            }
        }
    }
    out
}

// ---------------------------------------------------------------------------
// random creature and powers
// ---------------------------------------------------------------------------

/// Checks a random-creature record, from `randcreature.py::issues_rc`.
///
/// `type` in `{0,1}`; `weight` finite in `0..=100`; the four stat bounds in
/// `-16..=64`; and `min <= max` unless either side is the `-1` "any" sentinel.
pub fn random_creature_issues(random_creature: &CellRandomCreature) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (index, entry) in random_creature.entries.iter().enumerate() {
        if entry.entry_type > 1 {
            out.push(scalar_issue(
                IssueKind::NotAnEnumMember,
                RANDOM_CREATURE_TYPE,
                "entry.type",
                index,
                Scalar::U32(entry.entry_type),
                "0 or 1",
                IssueConfidence::ObservedSet,
            ));
        }
        if !in_f32(entry.weight, 0.0, 100.0) {
            out.push(scalar_issue(
                IssueKind::NotFinite,
                RANDOM_CREATURE_TYPE,
                "entry.weight",
                index,
                Scalar::F32(entry.weight),
                "0.0..=100.0 (NaN fails)",
                IssueConfidence::ObservedRange,
            ));
        }
        for (name, value) in entry.stats() {
            if !(-16..=64).contains(&value) {
                out.push(scalar_issue(
                    IssueKind::OutOfRange,
                    RANDOM_CREATURE_TYPE,
                    name,
                    index,
                    Scalar::I32(value),
                    "-16..=64",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
        if entry.speed_min != -1 && entry.speed_max != -1 && entry.speed_min > entry.speed_max {
            out.push(scalar_issue(
                IssueKind::InvertedRange,
                RANDOM_CREATURE_TYPE,
                "speedMin",
                index,
                Scalar::I32(entry.speed_min),
                "speedMin <= speedMax unless either is -1",
                IssueConfidence::ObservedRange,
            ));
        }
        if entry.danger_min != -1 && entry.danger_max != -1 && entry.danger_min > entry.danger_max {
            out.push(scalar_issue(
                IssueKind::InvertedRange,
                RANDOM_CREATURE_TYPE,
                "dangerMin",
                index,
                Scalar::I32(entry.danger_min),
                "dangerMin <= dangerMax unless either is -1",
                IssueConfidence::ObservedRange,
            ));
        }
    }
    out
}

/// Checks a powers record, from `randcreature.py::issues_pw`: `teleportCost` in
/// `0..=10000` and `teleportRange` finite in `0..=1000`.
pub fn powers_issues(powers: &CellPowers) -> Vec<CellIssue> {
    let mut out = Vec::new();
    if !(0..=10000).contains(&powers.teleport_cost) {
        out.push(scalar_issue(
            IssueKind::OutOfRange,
            POWERS_TYPE,
            "teleportCost",
            RECORD_LEVEL,
            Scalar::I32(powers.teleport_cost),
            "0..=10000",
            IssueConfidence::ObservedRange,
        ));
    }
    if !in_f32(powers.teleport_range, 0.0, 1000.0) {
        out.push(scalar_issue(
            IssueKind::NotFinite,
            POWERS_TYPE,
            "teleportRange",
            RECORD_LEVEL,
            Scalar::F32(powers.teleport_range),
            "0.0..=1000.0 (NaN fails)",
            IssueConfidence::ObservedRange,
        ));
    }
    out
}

// ---------------------------------------------------------------------------
// maps
// ---------------------------------------------------------------------------

/// Checks an effect-map record, from `celleffectmap.py::issues_em`.
///
/// `type <= 31`; `field_8` and `field_C` finite in `-100..=100000` with `-1.0`
/// accepted as a sentinel; `field_10` and `field_14` finite in `0..=100000`; and
/// `field_18` in `-16..=64`.
pub fn effect_map_issues(effect_map: &CellEffectMap) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (index, entry) in effect_map.entries.iter().enumerate() {
        if entry.entry_type > 31 {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                EFFECT_MAP_TYPE,
                "entry.type",
                index,
                Scalar::U32(entry.entry_type),
                "<= 31",
                IssueConfidence::ObservedRange,
            ));
        }
        for (name, value, low, high, sentinel) in [
            ("field_8", entry.field_8, -100.0f32, 100000.0f32, true),
            ("field_C", entry.field_c, -100.0, 100000.0, true),
            ("field_10", entry.field_10, 0.0, 100000.0, false),
            ("field_14", entry.field_14, 0.0, 100000.0, false),
        ] {
            let ok = if sentinel && value == -1.0 {
                true
            } else {
                in_f32(value, low, high)
            };
            if !ok {
                out.push(scalar_issue(
                    IssueKind::OutOfRange,
                    EFFECT_MAP_TYPE,
                    name,
                    index,
                    Scalar::F32(value),
                    "a finite float in range, or the -1.0 sentinel",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
        if !(-16..=64).contains(&entry.field_18) {
            out.push(scalar_issue(
                IssueKind::OutOfRange,
                EFFECT_MAP_TYPE,
                "field_18",
                index,
                Scalar::I32(entry.field_18),
                "-16..=64",
                IssueConfidence::ObservedRange,
            ));
        }
    }
    out
}

/// Checks a background-map record, from `celleffectmap.py::issues_bm`: each
/// colour channel finite in `0..=1` and `field_c` finite in `0..=100000`.
pub fn background_map_issues(background_map: &CellBackgroundMap) -> Vec<CellIssue> {
    let mut out = Vec::new();
    for (index, entry) in background_map.entries.iter().enumerate() {
        for (name, value) in [("r", entry.r), ("g", entry.g), ("b", entry.b)] {
            if !in_f32(value, 0.0, 1.0) {
                out.push(scalar_issue(
                    IssueKind::NotFinite,
                    BACKGROUND_MAP_TYPE,
                    name,
                    index,
                    Scalar::F32(value),
                    "0.0..=1.0 (NaN fails)",
                    IssueConfidence::ObservedRange,
                ));
            }
        }
        if !in_f32(entry.field_c, 0.0, 100000.0) {
            out.push(scalar_issue(
                IssueKind::NotFinite,
                BACKGROUND_MAP_TYPE,
                "field_C",
                index,
                Scalar::F32(entry.field_c),
                "0.0..=100000.0 (NaN fails)",
                IssueConfidence::ObservedRange,
            ));
        }
    }
    out
}

// ---------------------------------------------------------------------------
// dispatch
// ---------------------------------------------------------------------------

impl crate::CellContent {
    /// Every issue this record has, given a catalogue to resolve references
    /// against.
    ///
    /// `None` for a record type with no checker, which today is none of the
    /// twelve.
    pub fn issues(&self, catalogue: &CellCatalogue) -> Vec<CellIssue> {
        use crate::CellContent as C;
        match self {
            C::Globals(globals) => globals_issues(globals, catalogue),
            C::EffectMap(map) => effect_map_issues(map),
            C::BackgroundMap(map) => background_map_issues(map),
            C::Structure(structure) => structure_issues(structure, catalogue),
            C::World(world) => world_issues(world),
            C::RandomCreature(random_creature) => random_creature_issues(random_creature),
            C::Powers(powers) => powers_issues(powers),
            C::LookTable(table) => look_table_issues(table),
            C::LookAlgorithm(algorithm) => look_algorithm_issues(algorithm, catalogue),
            C::LootTable(table) => loot_table_issues(table, catalogue),
            C::Populate(populate) => populate_issues(populate, catalogue),
            C::Cell(cell) => cell_issues(cell, catalogue),
        }
    }
}

/// The issues of one record, with the identity they belong to.
#[derive(Debug, Clone, PartialEq)]
pub struct CatalogueIssue {
    /// The identity of the offending record.
    pub key: ResourceKey,
    /// Everything wrong with it.
    pub issues: Vec<CellIssue>,
}

/// Validates a whole catalogue against itself.
///
/// Rows come back sorted on `(type, group, instance)` so two runs over the same
/// catalogue produce byte-identical output. Records with no issues are
/// **omitted** rather than listed with an empty vector: "no issues" is the normal
/// case, and listing it would bury the findings that matter.
pub fn validate_catalogue<'a, I>(catalogue: &CellCatalogue, records: I) -> Vec<CatalogueIssue>
where
    I: IntoIterator<Item = &'a crate::reference::CellContentRecord>,
{
    let mut sorted: Vec<&crate::reference::CellContentRecord> = records.into_iter().collect();
    sorted.sort_by_key(|record| record.key);
    sorted
        .into_iter()
        .filter_map(|record| {
            let issues = record.value.issues(catalogue);
            (!issues.is_empty()).then_some(CatalogueIssue {
                key: record.key,
                issues,
            })
        })
        .collect()
}
