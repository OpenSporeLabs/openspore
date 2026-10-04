//! `cCellGlobalsResource` — the single stage-wide globals record.
//!
//! Type id `0x2A3CE5B7`, exactly **276 bytes**, **69** four-byte fields.
//!
//! # It is flat, and that is the load-bearing claim
//!
//! There is no `CellSerializer` envelope. The C++ reference names a
//! `CellSerializer` in its comments and then reads `gameMode` at offset 0; the
//! Python oracle does the same. If an envelope existed (a name, an id, a
//! version word), every one of the 69 fields would be shifted by its size and
//! none would decode to a plausible value. All 69 do — round floats, small
//! enums, and resource-reference instance ids — on the one record in
//! `SPORE/DataEP1/Spore_EP1_Data.package` at group 0, instance `0xa426730b`.
//! That is what grades the layout `OBSERVED`; see
//! [`crate::claims::GLOBALS_LAYOUT`].
//!
//! # Named fields, positional records
//!
//! [`CellGlobals`] is a named struct because that is the usable API. The
//! authoritative layout table is [`GLOBALS_LAYOUT`], whose entries carry the
//! field's name **in the source record's own spelling**, its offset and its
//! kind. `tests/decode.rs` walks that table and matches every name against the
//! struct exhaustively, so the two cannot drift: a name added to the table
//! without a matching struct field fails the test, and a struct field without a
//! table entry is unreachable by name.
//!
//! # Which fields are references
//!
//! Seventeen of the 69 hold a resource-reference instance id, and
//! [`GLOBALS_REFERENCE_FIELDS`] splits them: **fifteen name a record type** (the
//! *world* / *background* / *start cell* / *look algorithm* family that
//! [`crate::reference`] resolves) and **one does not**.
//!
//! The exception is `startingCellKey`. The C++ reference emits it as a
//! `cCellCellResource` instance; the corpus says otherwise — the value at offset
//! 56 of the one real record, `0xA1C46DF2`, is a **`prop` record**
//! (`0x00B1B104`), while `startCell` at offset 52 is a real cell instance. So
//! this crate models it as a bare instance id with no type word, which makes it a
//! reference non-finding rather than a lookup that must fail. See
//! [`crate::claims::GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE`].

use spore_core::ResourceKey;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};
use crate::scalar::{FieldKind, Scalar};

/// The record type id of a globals record.
pub const GLOBALS_TYPE: u32 = spore_core::record::type_id::CELL_GLOBALS;

/// The exact byte extent of a globals record.
pub const GLOBALS_SIZE: usize = 276;

/// How many fields a globals record has.
pub const GLOBALS_FIELD_COUNT: usize = 69;

/// A globals record has a fixed extent, so it has no counted-entry span.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One entry of [`GLOBALS_LAYOUT`]: name in the record's own spelling, byte
/// offset, and declared kind.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct GlobalsFieldSpec {
    /// The field name as the C++ reference and the Python oracle spell it.
    pub name: &'static str,
    /// Byte offset from the start of the record.
    pub offset: usize,
    /// The declared field kind.
    pub kind: FieldKind,
}

/// The authoritative layout: 69 consecutive four-byte fields at offsets
/// `4 * i`, so field *i* starts at `4 * i` and the last one ends at 276.
///
/// Transcribed field-for-field from `tools/spore/cellres/cellres.py`
/// (`GLOBALS_FIELDS`) and checked against `src/assets/CellResource.cpp`'s
/// `kFields` table, which lists the same 69 names in the same order with the
/// same 17 reference slots.
pub const GLOBALS_LAYOUT: &[GlobalsFieldSpec] = &[
    GlobalsFieldSpec {
        name: "gameMode",
        offset: 0,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "world_1",
        offset: 4,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "world_2",
        offset: 8,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "world_3",
        offset: 12,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "world_4",
        offset: 16,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "world_5",
        offset: 20,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldBackground_1",
        offset: 24,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldBackground_2",
        offset: 28,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldBackground_3",
        offset: 32,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldBackground_4",
        offset: 36,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldBackground_5",
        offset: 40,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldRandom",
        offset: 44,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "worldRandomBg",
        offset: 48,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "startCell",
        offset: 52,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "startingCellKey",
        offset: 56,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "effectMapEntry",
        offset: 60,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "backgroundMapEntry",
        offset: 64,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "flowMultiplier",
        offset: 68,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "npcSpeedMultiplier",
        offset: 72,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "npcTurnSpeedMultiplier_Jet",
        offset: 76,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "npcTurnSpeedMultiplier_Flagella",
        offset: 80,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "npcTurnSpeedMultiplier_Cilia",
        offset: 84,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "densityRock",
        offset: 88,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "densitySolid",
        offset: 92,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "densityLiquid",
        offset: 96,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "densityAir",
        offset: 100,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "backgroundDistance",
        offset: 104,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "minDragCollisionSpeed",
        offset: 108,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "minImpactCollisionSpeed",
        offset: 112,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "ciliaSpeedAsJet",
        offset: 116,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaSpeedAsJet",
        offset: 120,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaSpeedAsCilia",
        offset: 124,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "ciliaSpeedAsFlagella",
        offset: 128,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "keyLookAlgorithm",
        offset: 132,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "beachDistance",
        offset: 136,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "finishLineDistance",
        offset: 140,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "noPartSpeed",
        offset: 144,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaRampMinFactor",
        offset: 148,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaRampTime",
        offset: 152,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaRampResetAngle",
        offset: 156,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaTurnSpeedRampStart",
        offset: 160,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaTurnSpeedRampEnd",
        offset: 164,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaTurnSpeedMin",
        offset: 168,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "flagellaTurnSpeedMax",
        offset: 172,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "ciliaTurnSpeed",
        offset: 176,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "jetTurnSpeed",
        offset: 180,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "startLevelNoCreatureRadius",
        offset: 184,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "startLevelNoAnythingRadius",
        offset: 188,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "numHighLOD_FG",
        offset: 192,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "numHighLOD_BG",
        offset: 196,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "percentAnimalFood",
        offset: 200,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "percentPlantFood",
        offset: 204,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "field_208",
        offset: 208,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "controlMethod",
        offset: 212,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "editorMethod",
        offset: 216,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "tutorialMethod",
        offset: 220,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "endingMethod",
        offset: 224,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "eyeMethod",
        offset: 228,
        kind: FieldKind::U32,
    },
    GlobalsFieldSpec {
        name: "timeToGoldyCinematic",
        offset: 232,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "missionTime",
        offset: 236,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "missionResetTime",
        offset: 240,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "escapeMinDistance",
        offset: 244,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "escapeMaxDistance",
        offset: 248,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "escapeDelayMedium",
        offset: 252,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "escapeTimerHard",
        offset: 256,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "nonAnimatingCiliaMovementFactor",
        offset: 260,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "nonAnimatingJetMovementFactor",
        offset: 264,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "mateTriggerDistance",
        offset: 268,
        kind: FieldKind::F32,
    },
    GlobalsFieldSpec {
        name: "mateSpawnDistance",
        offset: 272,
        kind: FieldKind::F32,
    },
];

/// The reference-bearing globals fields, as `(name, target type)`, in layout
/// order. Seventeen slots; `None` means **the record stores no type word**, so
/// the field names an instance id and nothing more.
///
/// # `startingCellKey` is deliberately `None`, and the corpus is why
///
/// The C++ reference groups it with `startCell` and emits it as a
/// `cCellCellResource` instance. **The corpus contradicts that.** The one real
/// globals record holds `0xA1C46DF2` at offset 56, and that instance id is a
/// **`prop` record** (`0x00B1B104`) in `PatchData` -- it is not a cell record at
/// all, while `startCell` at offset 52 (`0xCBcd1287`) *is* a real cell instance
/// present in all three packages. So the two fields are not the same kind of
/// reference, and asserting otherwise would send a caller looking for a cell
/// that does not exist.
///
/// The honest model is the one this table encodes: `startCell` names a type,
/// `startingCellKey` does not. See
/// [`crate::claims::GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE`].
pub const GLOBALS_REFERENCE_FIELDS: &[(&str, Option<u32>)] = &[
    ("world_1", Some(crate::world::WORLD_TYPE)),
    ("world_2", Some(crate::world::WORLD_TYPE)),
    ("world_3", Some(crate::world::WORLD_TYPE)),
    ("world_4", Some(crate::world::WORLD_TYPE)),
    ("world_5", Some(crate::world::WORLD_TYPE)),
    ("worldBackground_1", Some(crate::world::WORLD_TYPE)),
    ("worldBackground_2", Some(crate::world::WORLD_TYPE)),
    ("worldBackground_3", Some(crate::world::WORLD_TYPE)),
    ("worldBackground_4", Some(crate::world::WORLD_TYPE)),
    ("worldBackground_5", Some(crate::world::WORLD_TYPE)),
    ("worldRandom", Some(crate::world::WORLD_TYPE)),
    ("worldRandomBg", Some(crate::world::WORLD_TYPE)),
    ("startCell", Some(crate::cell::CELL_TYPE)),
    // No type word. The value the corpus stores names a `prop`.
    ("startingCellKey", None),
    ("effectMapEntry", Some(crate::maps::EFFECT_MAP_TYPE)),
    ("backgroundMapEntry", Some(crate::maps::BACKGROUND_MAP_TYPE)),
    ("keyLookAlgorithm", Some(crate::look::LOOK_ALGORITHM_TYPE)),
];

/// The globals slots that name a record type in this family: sixteen.
pub const GLOBALS_TYPED_REFERENCE_FIELDS: usize = 16;

/// The globals slots that store a bare instance id: one, `startingCellKey`.
pub const GLOBALS_UNTYPED_REFERENCE_FIELDS: usize = 1;

/// The decoded `cCellGlobalsResource`.
///
/// Field names are this crate's Rust spelling; [`GLOBALS_LAYOUT`] carries the
/// record's own. Use [`CellGlobals::lookup`] to go from the record's spelling
/// to a value.
#[derive(Debug, Clone, PartialEq)]
#[allow(missing_docs)]
pub struct CellGlobals {
    pub game_mode: u32,
    pub world_1: u32,
    pub world_2: u32,
    pub world_3: u32,
    pub world_4: u32,
    pub world_5: u32,
    pub world_background_1: u32,
    pub world_background_2: u32,
    pub world_background_3: u32,
    pub world_background_4: u32,
    pub world_background_5: u32,
    pub world_random: u32,
    pub world_random_bg: u32,
    pub start_cell: u32,
    pub starting_cell_key: u32,
    pub effect_map_entry: u32,
    pub background_map_entry: u32,
    pub flow_multiplier: f32,
    pub npc_speed_multiplier: f32,
    pub npc_turn_speed_multiplier_jet: f32,
    pub npc_turn_speed_multiplier_flagella: f32,
    pub npc_turn_speed_multiplier_cilia: f32,
    pub density_rock: f32,
    pub density_solid: f32,
    pub density_liquid: f32,
    pub density_air: f32,
    pub background_distance: f32,
    pub min_drag_collision_speed: f32,
    pub min_impact_collision_speed: f32,
    pub cilia_speed_as_jet: f32,
    pub flagella_speed_as_jet: f32,
    pub flagella_speed_as_cilia: f32,
    pub cilia_speed_as_flagella: f32,
    pub key_look_algorithm: u32,
    pub beach_distance: f32,
    pub finish_line_distance: f32,
    pub no_part_speed: f32,
    pub flagella_ramp_min_factor: f32,
    pub flagella_ramp_time: f32,
    pub flagella_ramp_reset_angle: f32,
    pub flagella_turn_speed_ramp_start: f32,
    pub flagella_turn_speed_ramp_end: f32,
    pub flagella_turn_speed_min: f32,
    pub flagella_turn_speed_max: f32,
    pub cilia_turn_speed: f32,
    pub jet_turn_speed: f32,
    pub start_level_no_creature_radius: f32,
    pub start_level_no_anything_radius: f32,
    pub num_high_lod_fg: u32,
    pub num_high_lod_bg: u32,
    pub percent_animal_food: f32,
    pub percent_plant_food: f32,
    pub field_208: u32,
    pub control_method: u32,
    pub editor_method: u32,
    pub tutorial_method: u32,
    pub ending_method: u32,
    pub eye_method: u32,
    pub time_to_goldy_cinematic: f32,
    pub mission_time: f32,
    pub mission_reset_time: f32,
    pub escape_min_distance: f32,
    pub escape_max_distance: f32,
    pub escape_delay_medium: f32,
    pub escape_timer_hard: f32,
    pub non_animating_cilia_movement_factor: f32,
    pub non_animating_jet_movement_factor: f32,
    pub mate_trigger_distance: f32,
    pub mate_spawn_distance: f32,
}

impl CellGlobals {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        GLOBALS_TYPE
    }

    /// Looks a field up by the name the record's own layout table uses.
    ///
    /// Returns `None` for a name that is not in [`GLOBALS_LAYOUT`], which is a
    /// *different statement* from a field that happens to hold zero.
    pub fn lookup(&self, name: &str) -> Option<Scalar> {
        Some(match name {
            "gameMode" => Scalar::U32(self.game_mode),
            "world_1" => Scalar::U32(self.world_1),
            "world_2" => Scalar::U32(self.world_2),
            "world_3" => Scalar::U32(self.world_3),
            "world_4" => Scalar::U32(self.world_4),
            "world_5" => Scalar::U32(self.world_5),
            "worldBackground_1" => Scalar::U32(self.world_background_1),
            "worldBackground_2" => Scalar::U32(self.world_background_2),
            "worldBackground_3" => Scalar::U32(self.world_background_3),
            "worldBackground_4" => Scalar::U32(self.world_background_4),
            "worldBackground_5" => Scalar::U32(self.world_background_5),
            "worldRandom" => Scalar::U32(self.world_random),
            "worldRandomBg" => Scalar::U32(self.world_random_bg),
            "startCell" => Scalar::U32(self.start_cell),
            "startingCellKey" => Scalar::U32(self.starting_cell_key),
            "effectMapEntry" => Scalar::U32(self.effect_map_entry),
            "backgroundMapEntry" => Scalar::U32(self.background_map_entry),
            "flowMultiplier" => Scalar::F32(self.flow_multiplier),
            "npcSpeedMultiplier" => Scalar::F32(self.npc_speed_multiplier),
            "npcTurnSpeedMultiplier_Jet" => Scalar::F32(self.npc_turn_speed_multiplier_jet),
            "npcTurnSpeedMultiplier_Flagella" => {
                Scalar::F32(self.npc_turn_speed_multiplier_flagella)
            }
            "npcTurnSpeedMultiplier_Cilia" => Scalar::F32(self.npc_turn_speed_multiplier_cilia),
            "densityRock" => Scalar::F32(self.density_rock),
            "densitySolid" => Scalar::F32(self.density_solid),
            "densityLiquid" => Scalar::F32(self.density_liquid),
            "densityAir" => Scalar::F32(self.density_air),
            "backgroundDistance" => Scalar::F32(self.background_distance),
            "minDragCollisionSpeed" => Scalar::F32(self.min_drag_collision_speed),
            "minImpactCollisionSpeed" => Scalar::F32(self.min_impact_collision_speed),
            "ciliaSpeedAsJet" => Scalar::F32(self.cilia_speed_as_jet),
            "flagellaSpeedAsJet" => Scalar::F32(self.flagella_speed_as_jet),
            "flagellaSpeedAsCilia" => Scalar::F32(self.flagella_speed_as_cilia),
            "ciliaSpeedAsFlagella" => Scalar::F32(self.cilia_speed_as_flagella),
            "keyLookAlgorithm" => Scalar::U32(self.key_look_algorithm),
            "beachDistance" => Scalar::F32(self.beach_distance),
            "finishLineDistance" => Scalar::F32(self.finish_line_distance),
            "noPartSpeed" => Scalar::F32(self.no_part_speed),
            "flagellaRampMinFactor" => Scalar::F32(self.flagella_ramp_min_factor),
            "flagellaRampTime" => Scalar::F32(self.flagella_ramp_time),
            "flagellaRampResetAngle" => Scalar::F32(self.flagella_ramp_reset_angle),
            "flagellaTurnSpeedRampStart" => Scalar::F32(self.flagella_turn_speed_ramp_start),
            "flagellaTurnSpeedRampEnd" => Scalar::F32(self.flagella_turn_speed_ramp_end),
            "flagellaTurnSpeedMin" => Scalar::F32(self.flagella_turn_speed_min),
            "flagellaTurnSpeedMax" => Scalar::F32(self.flagella_turn_speed_max),
            "ciliaTurnSpeed" => Scalar::F32(self.cilia_turn_speed),
            "jetTurnSpeed" => Scalar::F32(self.jet_turn_speed),
            "startLevelNoCreatureRadius" => Scalar::F32(self.start_level_no_creature_radius),
            "startLevelNoAnythingRadius" => Scalar::F32(self.start_level_no_anything_radius),
            "numHighLOD_FG" => Scalar::U32(self.num_high_lod_fg),
            "numHighLOD_BG" => Scalar::U32(self.num_high_lod_bg),
            "percentAnimalFood" => Scalar::F32(self.percent_animal_food),
            "percentPlantFood" => Scalar::F32(self.percent_plant_food),
            "field_208" => Scalar::U32(self.field_208),
            "controlMethod" => Scalar::U32(self.control_method),
            "editorMethod" => Scalar::U32(self.editor_method),
            "tutorialMethod" => Scalar::U32(self.tutorial_method),
            "endingMethod" => Scalar::U32(self.ending_method),
            "eyeMethod" => Scalar::U32(self.eye_method),
            "timeToGoldyCinematic" => Scalar::F32(self.time_to_goldy_cinematic),
            "missionTime" => Scalar::F32(self.mission_time),
            "missionResetTime" => Scalar::F32(self.mission_reset_time),
            "escapeMinDistance" => Scalar::F32(self.escape_min_distance),
            "escapeMaxDistance" => Scalar::F32(self.escape_max_distance),
            "escapeDelayMedium" => Scalar::F32(self.escape_delay_medium),
            "escapeTimerHard" => Scalar::F32(self.escape_timer_hard),
            "nonAnimatingCiliaMovementFactor" => {
                Scalar::F32(self.non_animating_cilia_movement_factor)
            }
            "nonAnimatingJetMovementFactor" => Scalar::F32(self.non_animating_jet_movement_factor),
            "mateTriggerDistance" => Scalar::F32(self.mate_trigger_distance),
            "mateSpawnDistance" => Scalar::F32(self.mate_spawn_distance),
            _ => return None,
        })
    }

    /// Every `(name, value)` pair, in layout order.
    ///
    /// Total by construction: the `None` arms cannot be reached for a name that
    /// is in [`GLOBALS_LAYOUT`], and a name that is *not* in it has no field, so
    /// this never silently drops a decoded field.
    pub fn entries(&self) -> Vec<(&'static str, Scalar)> {
        GLOBALS_LAYOUT
            .iter()
            .map(|spec| {
                let value = self.lookup(spec.name).unwrap_or(Scalar::U32(0));
                (spec.name, value)
            })
            .collect()
    }

    /// The 17 reference-bearing slots as `(name, value)` pairs, layout order.
    pub fn reference_slots(&self) -> Vec<(&'static str, u32)> {
        GLOBALS_REFERENCE_FIELDS
            .iter()
            .map(|(name, _)| {
                (
                    *name,
                    self.lookup(name).and_then(Scalar::as_u32).unwrap_or(0),
                )
            })
            .collect()
    }

    /// The one graded claim that applies to this record type, or the non-finding
    /// for a subject this record type cannot carry.
    ///
    /// `None` means *not applicable to a globals record*, which is a third
    /// state distinct from [`spore_core::Fact::unavailable`] ("applicable, and
    /// we looked and found nothing").
    pub fn claim(&self, subject: &'static str) -> Option<spore_core::Fact<&'static str>> {
        match subject {
            claims::GLOBALS_LAYOUT => Some(claims::graded(
                claims::GLOBALS_LAYOUT,
                claims::PROV_CELLRES_ORACLE,
                "69 four-byte fields; the last ends at byte 276",
            )),
            claims::GLOBALS_FIELD_NAMES => Some(claims::graded(
                claims::GLOBALS_FIELD_NAMES,
                claims::PROV_SDK_STRUCT_61843,
                "field names transcribed from Simulator::Cell::cCellGlobalsResource",
            )),
            claims::GLOBALS_FIELD_208_MEANING => {
                Some(claims::non_finding(claims::GLOBALS_FIELD_208_MEANING))
            }
            claims::SERIALIZER_ENVELOPE_ABSENT => Some(claims::graded(
                claims::SERIALIZER_ENVELOPE_ABSENT,
                claims::PROV_CELLRES_ORACLE,
                "no name/id envelope precedes the 69 fields",
            )),
            claims::GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE => Some(claims::non_finding(
                claims::GLOBALS_STARTING_CELL_KEY_IS_A_REFERENCE,
            )),
            _ => None,
        }
    }
}

/// Reads a globals record.
///
/// Fails unless `bytes.len() == [`GLOBALS_SIZE`] exactly. There is no counted
/// header and therefore no span rule to apply; [`SPAN_RULE`] is published only so
/// that every record type answers the question the same way.
pub fn decode(bytes: &[u8]) -> Result<CellGlobals, CellContentError> {
    if bytes.len() != GLOBALS_SIZE {
        return Err(CellContentError::ExtentMismatch {
            type_id: GLOBALS_TYPE,
            actual: bytes.len(),
            expected: GLOBALS_SIZE,
        });
    }
    // `SPAN_RULE` is ExactFit and the length was just checked, so this is a
    // tautology today. Calling it anyway means a future header addition goes
    // through the same rule the counted records use instead of silently needing
    // a second check.
    check_span(
        SPAN_RULE,
        GLOBALS_TYPE,
        "fixed",
        0,
        GLOBALS_SIZE,
        1,
        bytes.len(),
    )?;

    let mut r = Reader::new(bytes);
    Ok(CellGlobals {
        game_mode: r.u32(),
        world_1: r.u32(),
        world_2: r.u32(),
        world_3: r.u32(),
        world_4: r.u32(),
        world_5: r.u32(),
        world_background_1: r.u32(),
        world_background_2: r.u32(),
        world_background_3: r.u32(),
        world_background_4: r.u32(),
        world_background_5: r.u32(),
        world_random: r.u32(),
        world_random_bg: r.u32(),
        start_cell: r.u32(),
        starting_cell_key: r.u32(),
        effect_map_entry: r.u32(),
        background_map_entry: r.u32(),
        flow_multiplier: r.f32(),
        npc_speed_multiplier: r.f32(),
        npc_turn_speed_multiplier_jet: r.f32(),
        npc_turn_speed_multiplier_flagella: r.f32(),
        npc_turn_speed_multiplier_cilia: r.f32(),
        density_rock: r.f32(),
        density_solid: r.f32(),
        density_liquid: r.f32(),
        density_air: r.f32(),
        background_distance: r.f32(),
        min_drag_collision_speed: r.f32(),
        min_impact_collision_speed: r.f32(),
        cilia_speed_as_jet: r.f32(),
        flagella_speed_as_jet: r.f32(),
        flagella_speed_as_cilia: r.f32(),
        cilia_speed_as_flagella: r.f32(),
        key_look_algorithm: r.u32(),
        beach_distance: r.f32(),
        finish_line_distance: r.f32(),
        no_part_speed: r.f32(),
        flagella_ramp_min_factor: r.f32(),
        flagella_ramp_time: r.f32(),
        flagella_ramp_reset_angle: r.f32(),
        flagella_turn_speed_ramp_start: r.f32(),
        flagella_turn_speed_ramp_end: r.f32(),
        flagella_turn_speed_min: r.f32(),
        flagella_turn_speed_max: r.f32(),
        cilia_turn_speed: r.f32(),
        jet_turn_speed: r.f32(),
        start_level_no_creature_radius: r.f32(),
        start_level_no_anything_radius: r.f32(),
        num_high_lod_fg: r.u32(),
        num_high_lod_bg: r.u32(),
        percent_animal_food: r.f32(),
        percent_plant_food: r.f32(),
        field_208: r.u32(),
        control_method: r.u32(),
        editor_method: r.u32(),
        tutorial_method: r.u32(),
        ending_method: r.u32(),
        eye_method: r.u32(),
        time_to_goldy_cinematic: r.f32(),
        mission_time: r.f32(),
        mission_reset_time: r.f32(),
        escape_min_distance: r.f32(),
        escape_max_distance: r.f32(),
        escape_delay_medium: r.f32(),
        escape_timer_hard: r.f32(),
        non_animating_cilia_movement_factor: r.f32(),
        non_animating_jet_movement_factor: r.f32(),
        mate_trigger_distance: r.f32(),
        mate_spawn_distance: r.f32(),
    })
}

/// The identity of the one globals record in a stock install.
///
/// Graded [`spore_core::EvidenceLevel::Observed`]: measured on
/// `SPORE/DataEP1/Spore_EP1_Data.package`. A modded install may hold more, so
/// this is documentation, not a constraint — [`decode`] never checks it.
pub const KNOWN_GLOBALS_KEY: ResourceKey = ResourceKey::new(GLOBALS_TYPE, 0x0000_0000, 0xA426_730B);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_layout_is_69_consecutive_four_byte_fields_ending_at_276() {
        assert_eq!(GLOBALS_LAYOUT.len(), GLOBALS_FIELD_COUNT);
        for (index, spec) in GLOBALS_LAYOUT.iter().enumerate() {
            assert_eq!(spec.offset, index * 4, "{} is out of order", spec.name);
            assert_eq!(spec.kind.width(), 4);
            assert_eq!(
                spec.offset % 4,
                0,
                "{}: every field is naturally aligned",
                spec.name
            );
        }
        let last = GLOBALS_LAYOUT[GLOBALS_FIELD_COUNT - 1];
        assert_eq!(last.offset + last.kind.width(), GLOBALS_SIZE);
        assert_eq!(last.name, "mateSpawnDistance");
        assert_eq!(first_name(), "gameMode");
    }

    fn first_name() -> &'static str {
        GLOBALS_LAYOUT[0].name
    }

    #[test]
    fn every_reference_field_name_is_in_the_layout() {
        for (name, _) in GLOBALS_REFERENCE_FIELDS {
            assert!(
                GLOBALS_LAYOUT.iter().any(|spec| spec.name == *name),
                "{name} is not a layout field"
            );
        }
        assert_eq!(GLOBALS_REFERENCE_FIELDS.len(), 17);
        let typed = GLOBALS_REFERENCE_FIELDS
            .iter()
            .filter(|(_, target)| target.is_some())
            .count();
        assert_eq!(typed, GLOBALS_TYPED_REFERENCE_FIELDS);
        assert_eq!(
            GLOBALS_REFERENCE_FIELDS.len() - typed,
            GLOBALS_UNTYPED_REFERENCE_FIELDS,
            "exactly one slot stores a bare instance id"
        );
        // And it is `startingCellKey`, which the corpus shows naming a `prop`.
        assert_eq!(
            GLOBALS_REFERENCE_FIELDS
                .iter()
                .filter(|(_, target)| target.is_none())
                .map(|(name, _)| *name)
                .collect::<Vec<_>>(),
            vec!["startingCellKey"]
        );
    }

    #[test]
    fn a_lookup_of_an_unknown_name_is_none_not_zero() {
        let globals = decode(&[0u8; GLOBALS_SIZE]).expect("all-zero globals decode");
        assert_eq!(globals.lookup("noSuchField"), None);
        assert_eq!(
            globals.lookup("gameMode"),
            Some(Scalar::U32(0)),
            "a known field holding zero is a value, not a non-finding"
        );
    }
}
