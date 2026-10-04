//! `cCellCellResource` — one cell species' whole definition.
//!
//! Type id `0xDFAD9F51`, exactly **796 bytes**.
//!
//! # Shape
//!
//! ```text
//! @000  u32          structure          0x4B9EF6DC instance
//! @004  wchar16[80]  name               160 bytes of UTF-16 code units
//! @164  u32          localeInstanceID   164 bytes total for the pair
//! @168  i32          hp
//! @172  u8           fixedOrientation   + 3 pad
//! @176  u32          flags
//! @180  u32          cellType
//! @184  u32          unlockType
//! @188  u32          density
//! @192  u32          sound
//! @196  u32          break              reference, no type word
//! @200  u32          pieces             reference, no type word
//! @204  u32          leak               reference, no type word
//! @208  u32          expel              reference, no type word
//! @212  u32          explosionTable     reference, no type word
//! @216  u32          loot               0xD92AF091 instance
//! @220  u32          poison             reference, no type word
//! @224  cAIData[180] ai                 normal difficulty
//! @404  cAIData[180] aiHard
//! @584  cAIData[180] aiEasy
//! @764  i32          friendGroup
//! @768  u8           wontAttackPlayer       + 2 pad
//! @769  u8           wontAttackPlayerWhenSmall
//! @772  f32          sizeMin
//! @776  f32          sizeMax
//! @780  cEatData[12] eat                 780..792
//! @792  u8           triggersEscapeMission  + 3 pad -> 796
//! ```
//!
//! # The three AI blocks are at 224, 404 and 584
//!
//! Those offsets are load-bearing and are pinned by
//! `tests/decode.rs::the_three_ai_blocks_land_at_224_404_and_584`. Each is
//! [`AI_BLOCK_SIZE`] = 180 bytes, and 584 + 180 = 764 which is exactly where
//! `friendGroup` starts — so the layout has no slack in it. A cell with one AI
//! block at the wrong offset still reaches 796; only the three exact offsets
//! make the fields after them plausible.
//!
//! # The name is UTF-16, and a full buffer is not truncated
//!
//! `name` is 80 UTF-16 code units followed by `localeInstanceID` — 164 bytes,
//! not 160. See [`decode_name`] for the decoding rule and for what this crate
//! decides about an unterminated buffer.

use spore_core::Fact;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{Reader, SpanRule};
use crate::scalar::Scalar;

/// The record type id of a cell record.
pub const CELL_TYPE: u32 = spore_core::record::type_id::CELL;

/// The exact byte extent of a cell record.
pub const CELL_SIZE: usize = 796;

/// How many UTF-16 code units the `name` field holds.
pub const NAME_UNITS: usize = 80;

/// Byte extent of the `name` + `localeInstanceID` pair.
pub const NAME_FIELD_SIZE: usize = 164;

/// Byte extent of one embedded `cAIData` block.
pub const AI_BLOCK_SIZE: usize = 180;

/// Byte offset of the `ai` block.
pub const AI_OFFSET: usize = 224;

/// Byte offset of the `aiHard` block.
pub const AI_HARD_OFFSET: usize = 404;

/// Byte offset of the `aiEasy` block.
pub const AI_EASY_OFFSET: usize = 584;

/// A cell record has a fixed extent, so it has no counted-entry span.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// The `cAIData.type` value that marks a zeroed "no AI" block.
pub const AI_TYPE_EMPTY: u32 = 0xFFFF_FFFF;

/// Decodes the 80-code-unit `name` buffer.
///
/// # The rule, and why
///
/// Read up to the first `U+0000`, or all 80 units when there is none.
///
/// * **No truncation at 79.** Both oracles stop at the first zero unit and read
///   the full array otherwise; neither reserves a "last unit must be zero" rule.
///   A 79-character name leaves `unit[79] == 0` and decodes to 79 characters,
///   and a buffer with *no* zero at all decodes to all 80 code units. Dropping
///   the 80th would be a silent loss of a byte the record actually stores.
/// * **Surrogate pairs are honoured.** The C++ reference maps each code unit to
///   one code point and emits at most three UTF-8 bytes, so a surrogate pair
///   becomes two three-byte sequences (CESU-8 mojibake); the Python oracle's
///   `chr(c)`-per-unit agrees with it for BMP characters and produces lone
///   surrogates above it. `String::from_utf16_lossy` instead follows the UTF-16
///   standard: a well-formed pair becomes one astral code point and a lone
///   surrogate becomes U+FFFD rather than invalid text.
///
///   No record in a stock install exercises the second case — every observed
///   name is ASCII (`PLACEHOLDER_*`) — so this is
///   [`spore_core::EvidenceLevel::Inferred`] for the pairing rule and
///   [`spore_core::EvidenceLevel::Observed`] for the width, terminator and
///   ASCII decoding. Both halves are in [`crate::claims`].
///
/// Because the result is built with `from_utf16_lossy`, **no input produces
/// invalid UTF-8 and no input panics**, which a hand-rolled encoder could not
/// promise for a lone surrogate.
pub fn decode_name(units: &[u16; NAME_UNITS]) -> String {
    let end = units.iter().position(|&u| u == 0).unwrap_or(NAME_UNITS);
    String::from_utf16_lossy(&units[..end])
}

/// The decoded `cAIData` block: one AI difficulty tier of one cell.
///
/// The layout is 45 four-byte slots with two one-byte flags that each occupy a
/// whole slot (`flocking` at +20, `axialMovement` at +68) and a run of seven
/// consecutive one-byte flags at +140..+146. Nothing is inferred from the
/// padding after those seven: it is skipped, and the skip is in the source at
/// `read_ai`.
///
/// Field names come from the SDK struct `cAIData` (Ghidra struct family 61866).
/// `movement_style` is a bitfield over `{1 = Jet, 2 = Flagella, 4 = Cilia}` and
/// `food` is a food type; **neither mapping has a registry in this build**, so
/// [`CellAi::movement_style_meaning`] and [`CellAi::food_meaning`] are
/// non-findings.
#[derive(Debug, Clone, PartialEq)]
#[allow(missing_docs)]
pub struct CellAi {
    pub kind: u32,
    pub awareness_radius: f32,
    pub awareness_radius_food: f32,
    pub awareness_radius_predator: f32,
    pub movement_style: u32,
    pub flocking: u8,
    pub speed: f32,
    pub chase_speed: f32,
    pub wander_speed: f32,
    pub flee_speed: f32,
    pub fears_nearby_damage_radius: f32,
    pub fears_nearby_death_radius: f32,
    pub fears_nearby_damage_time: f32,
    pub fears_nearby_death_time: f32,
    pub protect_radius: f32,
    pub protect_time: f32,
    pub turn_factor: f32,
    pub axial_movement: u8,
    pub spawn_time: f32,
    pub spawn_rest_time: f32,
    pub spawn_output: u32,
    pub arc_length: f32,
    pub arc_length_secondary: f32,
    pub num_arcs: i32,
    pub key_transformation: u32,
    pub key_projectile: u32,
    pub food: u32,
    pub grow_count: i32,
    pub digestion_count: i32,
    pub digestion_time: f32,
    pub digestion_output: u32,
    pub flee_time: f32,
    pub flee_rest_time: f32,
    pub chase_time: f32,
    pub chase_rest_time: f32,
    pub chases_damage: u8,
    pub fears_mouths: u8,
    pub fears_weapons: u8,
    pub fears_electric: u8,
    pub fears_poison: u8,
    pub fears_damage: u8,
    pub ignores_food: u8,
    pub awake_time: f32,
    pub sleep_time: f32,
    pub grow_amount: i32,
    pub hatch_duration: f32,
    pub poison_recharge: f32,
    pub electric_recharge: f32,
    pub electric_recharge_vs_small: f32,
    pub electric_discharge: f32,
}

impl CellAi {
    /// Whether this is the zeroed "no AI for this tier" block.
    pub const fn is_empty(&self) -> bool {
        self.kind == AI_TYPE_EMPTY
    }

    /// Every float field, in declaration order.
    ///
    /// Used by the domain checker, which applies one finiteness and magnitude
    /// rule to all 30 of them exactly as both oracles do.
    pub fn floats(&self) -> [f32; 30] {
        [
            self.awareness_radius,
            self.awareness_radius_food,
            self.awareness_radius_predator,
            self.speed,
            self.chase_speed,
            self.wander_speed,
            self.flee_speed,
            self.fears_nearby_damage_radius,
            self.fears_nearby_death_radius,
            self.fears_nearby_damage_time,
            self.fears_nearby_death_time,
            self.protect_radius,
            self.protect_time,
            self.turn_factor,
            self.spawn_time,
            self.spawn_rest_time,
            self.arc_length,
            self.arc_length_secondary,
            self.digestion_time,
            self.flee_time,
            self.flee_rest_time,
            self.chase_time,
            self.chase_rest_time,
            self.awake_time,
            self.sleep_time,
            self.hatch_duration,
            self.poison_recharge,
            self.electric_recharge,
            self.electric_recharge_vs_small,
            self.electric_discharge,
        ]
    }

    /// Every one-byte flag, in declaration order.
    ///
    /// Nine flags. They are kept as `u8` and not as `bool` because the Python
    /// oracle requires each to be `0` or `1`, and a `bool` conversion in the
    /// decoder would throw away the only thing that invariant can look at.
    pub fn flags(&self) -> [(&'static str, u8); 9] {
        [
            ("flocking", self.flocking),
            ("axialMovement", self.axial_movement),
            ("chasesDamage", self.chases_damage),
            ("fearsMouths", self.fears_mouths),
            ("fearsWeapons", self.fears_weapons),
            ("fearsElectric", self.fears_electric),
            ("fearsPoison", self.fears_poison),
            ("fearsDamage", self.fears_damage),
            ("ignoresFood", self.ignores_food),
        ]
    }

    /// What the `movementStyle` bitfield means.
    ///
    /// Always a non-finding. The bit assignments come from the C++ reference's
    /// comment, not from a table that can be checked against the data, and
    /// nothing in `tools/spore/cellres/` resolves them.
    pub fn movement_style_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::AI_MOVEMENT_STYLE_MEANING)
    }

    /// What the `food` field means.
    ///
    /// Always a non-finding: `food` takes only the values 0 and 3 across every
    /// observed record, and this build has no registry that names either.
    pub fn food_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::AI_FOOD_MEANING)
    }
}

fn read_ai(r: &mut Reader<'_>) -> CellAi {
    let kind = r.u32();
    let awareness_radius = r.f32();
    let awareness_radius_food = r.f32();
    let awareness_radius_predator = r.f32();
    let movement_style = r.u32();
    let flocking = r.u8();
    r.skip(3);
    let speed = r.f32();
    let chase_speed = r.f32();
    let wander_speed = r.f32();
    let flee_speed = r.f32();
    let fears_nearby_damage_radius = r.f32();
    let fears_nearby_death_radius = r.f32();
    let fears_nearby_damage_time = r.f32();
    let fears_nearby_death_time = r.f32();
    let protect_radius = r.f32();
    let protect_time = r.f32();
    let turn_factor = r.f32();
    let axial_movement = r.u8();
    r.skip(3);
    let spawn_time = r.f32();
    let spawn_rest_time = r.f32();
    let spawn_output = r.u32();
    let arc_length = r.f32();
    let arc_length_secondary = r.f32();
    let num_arcs = r.i32();
    let key_transformation = r.u32();
    let key_projectile = r.u32();
    let food = r.u32();
    let grow_count = r.i32();
    let digestion_count = r.i32();
    let digestion_time = r.f32();
    let digestion_output = r.u32();
    let flee_time = r.f32();
    let flee_rest_time = r.f32();
    let chase_time = r.f32();
    let chase_rest_time = r.f32();
    let chases_damage = r.u8();
    let fears_mouths = r.u8();
    let fears_weapons = r.u8();
    let fears_electric = r.u8();
    let fears_poison = r.u8();
    let fears_damage = r.u8();
    let ignores_food = r.u8();
    r.skip(1);
    let awake_time = r.f32();
    let sleep_time = r.f32();
    let grow_amount = r.i32();
    let hatch_duration = r.f32();
    let poison_recharge = r.f32();
    let electric_recharge = r.f32();
    let electric_recharge_vs_small = r.f32();
    let electric_discharge = r.f32();

    CellAi {
        kind,
        awareness_radius,
        awareness_radius_food,
        awareness_radius_predator,
        movement_style,
        flocking,
        speed,
        chase_speed,
        wander_speed,
        flee_speed,
        fears_nearby_damage_radius,
        fears_nearby_death_radius,
        fears_nearby_damage_time,
        fears_nearby_death_time,
        protect_radius,
        protect_time,
        turn_factor,
        axial_movement,
        spawn_time,
        spawn_rest_time,
        spawn_output,
        arc_length,
        arc_length_secondary,
        num_arcs,
        key_transformation,
        key_projectile,
        food,
        grow_count,
        digestion_count,
        digestion_time,
        digestion_output,
        flee_time,
        flee_rest_time,
        chase_time,
        chase_rest_time,
        chases_damage,
        fears_mouths,
        fears_weapons,
        fears_electric,
        fears_poison,
        fears_damage,
        ignores_food,
        awake_time,
        sleep_time,
        grow_amount,
        hatch_duration,
        poison_recharge,
        electric_recharge,
        electric_recharge_vs_small,
        electric_discharge,
    }
}

/// The decoded `cEatData`: what eating this cell yields. 12 bytes.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct CellEatData {
    /// Nutrition gained.
    pub food_value: i32,
    /// Hit points gained.
    pub hp_value: i32,
    /// Whether eating detonates. Kept as the byte that was read.
    pub bomb: u8,
    /// Whether eating releases a poison nova. Kept as the byte that was read.
    pub poison_nova: u8,
}

/// The decoded `cCellCellResource`.
#[derive(Debug, Clone, PartialEq)]
#[allow(missing_docs)]
pub struct CellCell {
    pub structure: u32,
    pub name: String,
    pub locale_instance_id: u32,
    pub hp: i32,
    pub fixed_orientation: u8,
    pub flags: u32,
    pub cell_type: u32,
    pub unlock_type: u32,
    pub density: u32,
    pub sound: u32,
    pub break_: u32,
    pub pieces: u32,
    pub leak: u32,
    pub expel: u32,
    pub explosion_table: u32,
    pub loot: u32,
    pub poison: u32,
    pub ai: CellAi,
    pub ai_hard: CellAi,
    pub ai_easy: CellAi,
    pub friend_group: i32,
    pub wont_attack_player: u8,
    pub wont_attack_player_when_small: u8,
    pub size_min: f32,
    pub size_max: f32,
    pub eat: CellEatData,
    pub triggers_escape_mission: u8,
}

impl CellCell {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        CELL_TYPE
    }

    /// The three AI blocks in tier order: normal, hard, easy.
    pub fn ai_tiers(&self) -> [&CellAi; 3] {
        [&self.ai, &self.ai_hard, &self.ai_easy]
    }

    /// The record-level one-byte flags, in layout order.
    pub fn flags(&self) -> [(&'static str, u8); 6] {
        [
            ("fixedOrientation", self.fixed_orientation),
            ("wontAttackPlayer", self.wont_attack_player),
            (
                "wontAttackPlayerWhenSmall",
                self.wont_attack_player_when_small,
            ),
            ("eatBomb", self.eat.bomb),
            ("eatPoisonNova", self.eat.poison_nova),
            ("triggersEscapeMission", self.triggers_escape_mission),
        ]
    }

    /// The record-level claims that apply to a cell record.
    pub fn claim(&self, subject: &'static str) -> Option<Fact<&'static str>> {
        match subject {
            claims::CELL_LAYOUT => Some(claims::graded(
                claims::CELL_LAYOUT,
                claims::PROV_CELL_ORACLE,
                "796 bytes; cAIData at 224/404/584, cEatData at 780",
            )),
            claims::CELL_NAME_ENCODING => Some(claims::graded(
                claims::CELL_NAME_ENCODING,
                claims::PROV_CELL_ORACLE,
                "wchar16[80] at +4 followed by u32 localeInstanceID at +164",
            )),
            claims::AI_SURROGATE_PAIRING => Some(claims::graded(
                claims::AI_SURROGATE_PAIRING,
                claims::PROV_CELLRESOURCE_CPP,
                "UTF-16 code units are paired per the standard; a lone unit decodes to U+FFFD",
            )),
            claims::AI_MOVEMENT_STYLE_MEANING => Some(self.ai.movement_style_meaning()),
            claims::AI_FOOD_MEANING => Some(self.ai.food_meaning()),
            _ => None,
        }
    }
}

/// Reads a cell record.
///
/// Fails unless `bytes.len() == [`CELL_SIZE`] exactly.
pub fn decode(bytes: &[u8]) -> Result<CellCell, CellContentError> {
    if bytes.len() != CELL_SIZE {
        return Err(CellContentError::ExtentMismatch {
            type_id: CELL_TYPE,
            actual: bytes.len(),
            expected: CELL_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let structure = r.u32();
    let mut units = [0u16; NAME_UNITS];
    for unit in &mut units {
        *unit = r.u16();
    }
    let name = decode_name(&units);
    let locale_instance_id = r.u32();
    let hp = r.i32();
    let fixed_orientation = r.u8();
    r.skip(3);
    let flags = r.u32();
    let cell_type = r.u32();
    let unlock_type = r.u32();
    let density = r.u32();
    let sound = r.u32();
    let break_ = r.u32();
    let pieces = r.u32();
    let leak = r.u32();
    let expel = r.u32();
    let explosion_table = r.u32();
    let loot = r.u32();
    let poison = r.u32();
    let ai = read_ai(&mut r);
    let ai_hard = read_ai(&mut r);
    let ai_easy = read_ai(&mut r);
    let friend_group = r.i32();
    let wont_attack_player = r.u8();
    let wont_attack_player_when_small = r.u8();
    r.skip(2);
    let size_min = r.f32();
    let size_max = r.f32();
    let food_value = r.i32();
    let hp_value = r.i32();
    let bomb = r.u8();
    let poison_nova = r.u8();
    r.skip(2);
    let triggers_escape_mission = r.u8();
    r.skip(3);

    debug_assert_eq!(
        r.offset(),
        CELL_SIZE,
        "the layout must account for 796 bytes"
    );

    Ok(CellCell {
        structure,
        name,
        locale_instance_id,
        hp,
        fixed_orientation,
        flags,
        cell_type,
        unlock_type,
        density,
        sound,
        break_,
        pieces,
        leak,
        expel,
        explosion_table,
        loot,
        poison,
        ai,
        ai_hard,
        ai_easy,
        friend_group,
        wont_attack_player,
        wont_attack_player_when_small,
        size_min,
        size_max,
        eat: CellEatData {
            food_value,
            hp_value,
            bomb,
            poison_nova,
        },
        triggers_escape_mission,
    })
}

/// The record-level scalars of a cell record that carry no reference role, for
/// the domain checker and for any caller that wants to enumerate them.
impl CellCell {
    /// `(name, value)` for every record-level field that is not a reference and
    /// not the name/AI/eat sub-records.
    pub fn scalars(&self) -> [(&'static str, Scalar); 14] {
        [
            ("hp", Scalar::I32(self.hp)),
            ("flags", Scalar::U32(self.flags)),
            ("cellType", Scalar::U32(self.cell_type)),
            ("unlockType", Scalar::U32(self.unlock_type)),
            ("density", Scalar::U32(self.density)),
            ("sound", Scalar::U32(self.sound)),
            ("friendGroup", Scalar::I32(self.friend_group)),
            ("sizeMin", Scalar::F32(self.size_min)),
            ("sizeMax", Scalar::F32(self.size_max)),
            ("eatFoodValue", Scalar::I32(self.eat.food_value)),
            ("eatHpValue", Scalar::I32(self.eat.hp_value)),
            ("localeInstanceID", Scalar::U32(self.locale_instance_id)),
            ("fixedOrientation", Scalar::U8(self.fixed_orientation)),
            (
                "triggersEscapeMission",
                Scalar::U8(self.triggers_escape_mission),
            ),
        ]
    }
}
