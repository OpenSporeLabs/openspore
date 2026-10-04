//! Synthetic record builders.
//!
//! # Why this module exists and is shared
//!
//! There are **no committed fixtures** for the Cell-stage records: they exist
//! only inside the git-ignored `SPORE/` tree, and the repository rule is that no
//! *Spore* byte is ever committed. So every decoder test builds its bytes here.
//!
//! The builders are not decoration — they are the specification made executable.
//! Each writes a record whose every field is a value **distinguishable from its
//! neighbours**, so a decoder that reads a field from the wrong offset produces a
//! different value rather than accidentally producing zero. Header slots get
//! values that differ (`count` is small, the dead pointer slot is zero), so a
//! decoder that swaps them fails the extent check loudly.
//!
//! Values are in **domain** by default: `cellType = 4`, `food = 3`,
//! `numArcs = i`, every flag `0` or `1`, every magnitude small. That is
//! deliberate — it means `tests/issues.rs` can assert *zero* issues on a
//! synthetic record and therefore prove the checkers do not manufacture
//! findings. The out-of-domain values used by the checker tests are poked in
//! afterwards, one at a time.

#![allow(dead_code)]

use spore_core::ResourceKey;

use spore_cellcontent::{
    cell, spawn, FieldKind, BACKGROUND_MAP_TYPE, CELL_TYPE, EFFECT_MAP_TYPE, GLOBALS_FIELD_COUNT,
    GLOBALS_SIZE, GLOBALS_TYPE, LOOK_ALGORITHM_TYPE, LOOK_TABLE_TYPE, LOOT_TABLE_TYPE,
    POPULATE_TYPE, POWERS_TYPE, RANDOM_CREATURE_TYPE, STRUCTURE_TYPE, WORLD_TYPE,
};

/// A growable little-endian byte builder.
///
/// Not a general-purpose writer: it exposes exactly the writes the twelve
/// layouts need, so a builder cannot accidentally emit a layout this crate does
/// not claim to decode.
#[derive(Debug, Clone, Default)]
pub struct Bytes {
    inner: Vec<u8>,
}

impl Bytes {
    /// An empty buffer.
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }

    /// A buffer of `len` zero bytes.
    pub fn zeroed(len: usize) -> Self {
        Self {
            inner: vec![0u8; len],
        }
    }

    /// How many bytes have been written.
    pub fn len(&self) -> usize {
        self.inner.len()
    }

    /// Whether nothing has been written.
    pub fn is_empty(&self) -> bool {
        self.inner.is_empty()
    }

    /// Appends one byte.
    pub fn u8(&mut self, value: u8) -> &mut Self {
        self.inner.push(value);
        self
    }

    /// Appends two raw bytes.
    pub fn pad2(&mut self, value: [u8; 2]) -> &mut Self {
        self.inner.extend_from_slice(&value);
        self
    }

    /// Appends three raw bytes (alignment padding).
    pub fn pad3(&mut self, value: [u8; 3]) -> &mut Self {
        self.inner.extend_from_slice(&value);
        self
    }

    /// Appends raw bytes.
    pub fn raw(&mut self, bytes: &[u8]) -> &mut Self {
        self.inner.extend_from_slice(bytes);
        self
    }

    /// Appends a little-endian `u16`.
    pub fn u16(&mut self, value: u16) -> &mut Self {
        self.inner.extend_from_slice(&value.to_le_bytes());
        self
    }

    /// Appends a little-endian `u32`.
    pub fn u32(&mut self, value: u32) -> &mut Self {
        self.inner.extend_from_slice(&value.to_le_bytes());
        self
    }

    /// Appends a little-endian `i32`.
    pub fn i32(&mut self, value: i32) -> &mut Self {
        self.inner.extend_from_slice(&value.to_le_bytes());
        self
    }

    /// Appends a little-endian `f32`.
    pub fn f32(&mut self, value: f32) -> &mut Self {
        self.inner.extend_from_slice(&value.to_bits().to_le_bytes());
        self
    }

    /// Overwrites four bytes at `offset`. Used by the mutation tests.
    pub fn poke_u32(&mut self, offset: usize, value: u32) {
        self.inner[offset..offset + 4].copy_from_slice(&value.to_le_bytes());
    }

    /// Overwrites one byte at `offset`.
    pub fn poke_u8(&mut self, offset: usize, value: u8) {
        self.inner[offset] = value;
    }

    /// The finished bytes.
    pub fn build(&self) -> Vec<u8> {
        self.inner.clone()
    }
}

/// A record identity for a synthetic record of `type_id`.
pub fn key(type_id: u32, group: u32, instance: u32) -> ResourceKey {
    ResourceKey::new(type_id, group, instance)
}

// ---------------------------------------------------------------------------
// globals -- 276 bytes, 69 four-byte fields
// ---------------------------------------------------------------------------

/// Whether globals field `index` is an `f32`, from the authoritative layout
/// table.
pub fn globals_is_float(index: usize) -> bool {
    matches!(
        spore_cellcontent::globals::GLOBALS_LAYOUT[index].kind,
        FieldKind::F32
    )
}

/// The raw `u32` word globals field `index` holds in [`globals_distinct`].
pub fn globals_word(index: usize) -> u32 {
    0x0100_0000u32.wrapping_add(index as u32)
}

/// Builds a globals record whose field `i` holds the raw word
/// [`globals_word`], with `f32` fields written as the bit pattern of
/// `1.5 + i/4`.
///
/// A raw-word API rather than a typed one, because a test needs to be able to
/// put an arbitrary bit pattern — `0x7FC0_0000` for a NaN — into a float field
/// and read it back through `Scalar::F32`.
pub fn globals_distinct() -> Vec<u8> {
    let mut out = Bytes::new();
    for index in 0..GLOBALS_FIELD_COUNT {
        if globals_is_float(index) {
            out.f32(1.5 + index as f32 * 0.25);
        } else {
            out.u32(globals_word(index));
        }
    }
    assert_eq!(out.len(), GLOBALS_SIZE);
    out.build()
}

/// A globals record whose 17 reference-bearing slots all hold a non-null
/// instance id, so the reference layer has something to enumerate.
pub fn globals_with_refs() -> Vec<u8> {
    let mut out = Bytes::new();
    for (index, spec) in spore_cellcontent::globals::GLOBALS_LAYOUT
        .iter()
        .enumerate()
    {
        let is_ref = spore_cellcontent::globals::GLOBALS_REFERENCE_FIELDS
            .iter()
            .any(|(name, _)| *name == spec.name);
        if is_ref {
            out.u32(0x0000_0100 + index as u32);
        } else if globals_is_float(index) {
            out.f32(globals_f32(index));
        } else {
            out.u32(globals_word(index));
        }
    }
    assert_eq!(out.len(), GLOBALS_SIZE);
    out.build()
}

/// The `f32` value globals field `index` holds in [`globals_distinct`].
pub fn globals_f32(index: usize) -> f32 {
    1.5 + index as f32 * 0.25
}

/// A globals record with **every** field zero.
///
/// Zero is in domain for every `f32` field, but `gameMode = 0` and the enum
/// bounds hold too, so this record produces zero domain issues.
pub fn globals_zeroed() -> Vec<u8> {
    Bytes::zeroed(GLOBALS_SIZE).build()
}

// ---------------------------------------------------------------------------
// cell -- 796 bytes
// ---------------------------------------------------------------------------

/// The `cAIData` block for AI tier `index`.
///
/// `kind` is `0x1000 + index`, inside the observed `0x1000..=0x10FF` band, so
/// the synthetic AI blocks are in domain.
pub fn ai(index: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(0x1000 + index as u32); // kind
    out.f32(10.0 + index as f32); // awarenessRadius
    out.f32(11.0 + index as f32); // awarenessRadiusFood
    out.f32(12.0 + index as f32); // awarenessRadiusPredator
    out.u32(0b0111); // movementStyle: jet | flagella | cilia
    out.u8(1); // flocking
    out.pad3([0, 0, 0]);
    out.f32(1.0 + index as f32); // speed
    out.f32(1.5 + index as f32); // chaseSpeed
    out.f32(2.0 + index as f32); // wanderSpeed
    out.f32(2.5 + index as f32); // fleeSpeed
    out.f32(0.5); // fearsNearbyDamageRadius
    out.f32(0.75); // fearsNearbyDeathRadius
    out.f32(1.25); // fearsNearbyDamageTime
    out.f32(1.5); // fearsNearbyDeathTime
    out.f32(2.0); // protectRadius
    out.f32(2.5); // protectTime
    out.f32(3.0); // turnFactor
    out.u8(1); // axialMovement
    out.pad3([0, 0, 0]);
    out.f32(4.0); // spawnTime
    out.f32(4.5); // spawnRestTime
    out.u32(0); // spawnOutput: a reference, left null
    out.f32(5.0); // arcLength
    out.f32(5.5); // arcLengthSecondary
    out.i32(index as i32); // numArcs
    out.u32(0); // keyTransformation
    out.u32(0); // keyProjectile
    out.u32(3); // food: 3 is one of the two observed values
    out.i32(index as i32); // growCount
    out.i32(index as i32 + 1); // digestionCount
    out.f32(6.0); // digestionTime
    out.u32(0); // digestionOutput: a reference, left null
    out.f32(7.0); // fleeTime
    out.f32(7.5); // fleeRestTime
    out.f32(8.0); // chaseTime
    out.f32(8.5); // chaseRestTime
    for _ in 0..7 {
        out.u8(1); // the seven consecutive one-byte flags
    }
    out.u8(0); // the single padding byte after them
    out.f32(9.0); // awakeTime
    out.f32(9.5); // sleepTime
    out.i32(index as i32); // growAmount
    out.f32(10.0); // hatchDuration
    out.f32(11.0); // poisonRecharge
    out.f32(12.0); // electricRecharge
    out.f32(13.0); // electricRechargeVsSmall
    out.f32(14.0); // electricDischarge
    assert_eq!(out.len(), cell::AI_BLOCK_SIZE);
    out.build()
}

/// Builds the UTF-16 name buffer for `text`, zero-filled to 80 units.
pub fn name_buffer(text: &str) -> [u16; cell::NAME_UNITS] {
    let mut units = [0u16; cell::NAME_UNITS];
    let encoded: Vec<u16> = text.encode_utf16().collect();
    assert!(
        encoded.len() < cell::NAME_UNITS,
        "the caller asked for a name that does not fit"
    );
    units[..encoded.len()].copy_from_slice(&encoded);
    units
}

/// A name buffer with all 80 units occupied and **no terminator**.
pub fn name_buffer_full() -> [u16; cell::NAME_UNITS] {
    let mut units = [0u16; cell::NAME_UNITS];
    for (index, unit) in units.iter_mut().enumerate() {
        *unit = 0x41 + (index % 26) as u16;
    }
    units
}

/// Builds a cell record.
///
/// `structure`, `loot` and `break_ref` are written where the reference layer
/// expects them so a resolution test can point them at real catalogue entries.
pub fn cell(structure: u32, name: &str, loot: u32, break_ref: u32) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(structure);
    out.raw(&name_buffer(name).map(|unit| unit.to_le_bytes()).concat());
    out.u32(0x1234_5678); // localeInstanceID
    out.i32(3); // hp
    out.u8(0); // fixedOrientation
    out.pad3([0, 0, 0]);
    out.u32(0x0F0F_0F0F); // flags
    out.u32(4); // cellType
    out.u32(8); // unlockType
    out.u32(3); // density
    out.u32(0x00AB_CDEF); // sound
    out.u32(break_ref); // break: an instance id with no type word
    out.u32(0); // pieces
    out.u32(0); // leak
    out.u32(0); // expel
    out.u32(0); // explosionTable
    out.u32(loot); // loot
    out.u32(0); // poison
    out.raw(&ai(0));
    out.raw(&ai(1));
    out.raw(&ai(2));
    out.i32(-2); // friendGroup
    out.u8(0); // wontAttackPlayer
    out.u8(1); // wontAttackPlayerWhenSmall
    out.pad2([0, 0]);
    out.f32(1.0); // sizeMin
    out.f32(4.0); // sizeMax
    out.i32(7); // eatFoodValue
    out.i32(2); // eatHpValue
    out.u8(0); // eatBomb
    out.u8(1); // eatPoisonNova
    out.pad2([0, 0]);
    out.u8(1); // triggersEscapeMission
    out.pad3([0, 0, 0]);
    assert_eq!(out.len(), cell::CELL_SIZE);
    out.build()
}

// ---------------------------------------------------------------------------
// counted records
// ---------------------------------------------------------------------------

/// An effect-map record with `entries` rows.
pub fn effect_map(entries: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(entries as u32);
    out.u32(0); // dead pointer slot
    for index in 0..entries {
        out.u32(0x1000 + index as u32); // effectID
        out.u32((index % 6) as u32 + 2); // type
        out.f32(42.0 + index as f32); // field_8
        out.f32(43.0 + index as f32); // field_C
        out.f32(44.0 + index as f32); // field_10
        out.f32(45.0 + index as f32); // field_14
        out.i32((index % 12) as i32); // field_18
    }
    out.build()
}

/// A background-map record with `entries` stops.
pub fn background_map(entries: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(entries as u32);
    out.u32(0);
    for index in 0..entries {
        out.f32(0.1 * (index % 10 + 1) as f32 / 10.0); // r
        out.f32(0.2 * (index % 5 + 1) as f32 / 5.0); // g
        out.f32(0.3 * (index % 4 + 1) as f32 / 4.0); // b
        out.f32(3.333_f32.powi(index as i32 + 1)); // field_C
    }
    out.build()
}

/// A random-creature record with `entries` rows.
pub fn random_creature(entries: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(entries as u32);
    out.u32(0);
    for index in 0..entries {
        out.u32((index % 2) as u32); // type
        out.u32(0x9000_0000 + index as u32); // creatureID: a soft id, never resolved
        out.f32(1.0); // weight
        out.i32(0); // speedMin
        out.i32(2); // speedMax
        out.i32(1); // dangerMin
        out.i32(3); // dangerMax
    }
    out.build()
}

/// A powers record.
pub fn powers() -> Vec<u8> {
    let mut out = Bytes::new();
    out.i32(10); // teleportCost
    out.f32(10.0); // teleportRange
    assert_eq!(out.len(), spawn::POWERS_SIZE);
    out.build()
}

/// A look-table record with `entries` rows.
///
/// **The header order is pointer-first, count-second** for both look records,
/// which is the opposite of the other counted records. The two slots are given
/// distinguishable values here (`0` and `entries`) so a decoder that reads them
/// in the wrong order fails the extent check.
pub fn look_table(entries: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(0); // dead pointer slot, FIRST
    out.u32(entries as u32); // count, SECOND
    for index in 0..entries {
        out.i32((index % 12) as i32); // type
        out.f32((index % 3 + 1) as f32 * 5.0); // value
    }
    out.build()
}

/// A look-algorithm record with `entries` rows.
pub fn look_algorithm(entries: usize, tables: [u32; 3]) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(0);
    out.u32(entries as u32);
    for index in 0..entries {
        out.u32((index % 3) as u32); // type
        out.u32(18 + (index % 5) as u32); // action: 18..=22
        out.u32(tables[0]); // player
        out.u32(tables[1]); // npc
        out.u32(tables[2]); // epic
    }
    out.build()
}

/// A loot-table record with `entries` rows.
pub fn loot_table(entries: usize, cell_ref: u32, table_ref: u32) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(0); // dead pointer slot
    out.u32(entries as u32);
    out.f32(0.0); // minRadius
    out.f32(0.0); // maxRadius
    out.f32(1.0); // initialAlpha
    out.f32(1.0); // expelForce
    out.i32(0); // effect
    out.u8(1); // mustHavePart
    out.pad3([0, 0, 0]); // the three pad bytes at +29..+32
    out.f32(0.0); // delay
    for index in 0..entries {
        out.u32((index % 3) as u32); // type
        out.u32(cell_ref); // cell
        out.u32(table_ref); // table
        out.f32(25.0 + index as f32); // weight
        out.i32(2); // count
        out.i32(1); // countDelta
        out.i32(-1); // levelOffset
    }
    out.build()
}

/// A populate record with `markers` rows.
pub fn populate(markers: usize, distribute: u32, cluster: u32) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(4); // scale
    out.u32(0); // maskTexture
    out.u32(markers as u32);
    out.u32(0); // dead pointer slot
    for index in 0..markers {
        out.u32(0); // field_0
        out.u32(0); // field_4
        out.u32(0); // field_8
        out.f32(index as f32); // zOffset
        out.f32(index as f32 + 1.0); // zOffsetMax
        out.u32(0); // field_14
        out.u32(distribute); // distributeCell
        out.u32(cluster); // clusterCell
        out.u32(0); // encounterPopulate
        out.u32(index as u32 % 3); // plantType
        out.u32(index as u32 % 3); // type
        out.f32(10.0 + index as f32); // count
        out.f32(1.0); // count_easy
        out.f32(2.0); // count_med
        out.f32(3.0); // count_hard
        out.i32(index as i32); // size
        out.i32(3); // parts
        out.i32(index as i32 % 2); // linear
        out.i32(0); // encounterScale
    }
    out.build()
}

/// A structure record with `attachments` rows.
pub fn structure(attachments: usize, random_creature_ref: u32) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(101); // onDeath
    out.u32(0); // onDeathSmall
    out.u32(0); // onDeathLarge
    out.u32(0); // onHatch
    out.u32(0); // onStartHatch
    out.u32(0); // dead pointer slot
    out.u32(attachments as u32);
    for index in 0..attachments {
        out.i32([0, 3, -1][index % 3]); // bone
        out.u32((index % 7) as u32); // type
        out.u32(0); // structure: dead everywhere
        out.u32(random_creature_ref); // randomCreature
        out.i32(100 + index as i32); // effectID: positive, so it is a reference
        out.i32(0); // levelMin
        out.i32(10); // levelMax
        out.f32(1.0); // color.r
        out.f32(0.5); // color.g
        out.f32(0.25); // color.b
    }
    out.build()
}

/// A world record with `populates` level entries and `advects` advect entries.
pub fn world(populates: usize, populate_ref: u32, advects: usize) -> Vec<u8> {
    let mut out = Bytes::new();
    out.u32(populates as u32);
    out.u32(0); // dead pointer slot
    out.u32(advects as u32);
    out.u32(0); // dead pointer slot
    for index in 0..populates {
        out.u32(populate_ref); // populate
        out.u8((index % 2) as u8); // startTile
        out.pad3([0, 0, 0]);
        out.u32((index % 10 + 1) as u32); // playerSize
    }
    for index in 0..advects {
        out.u32((index + 1) as u32); // stageScale
        out.i32(-1); // playerSize: "any"
        out.f32(1.5); // strength
        out.f32(0.0); // variance
        out.f32(1.0); // period
        out.u32(0x1234_5678); // advectID: a flow-field reference
    }
    out.build()
}

// ---------------------------------------------------------------------------
// catalogue helpers
// ---------------------------------------------------------------------------

/// A decoded cell record that points at `structure`.
pub fn cell_record(instance: u32, structure: u32) -> spore_cellcontent::CellContentRecord {
    spore_cellcontent::CellContentRecord::new(
        key(CELL_TYPE, 0, instance),
        spore_cellcontent::CellContent::Cell(
            cell::decode(&cell(structure, "PLACEHOLDER_Test", 0, 0)).expect("synthetic cell"),
        ),
    )
}

/// A decoded structure record.
pub fn structure_record(instance: u32) -> spore_cellcontent::CellContentRecord {
    spore_cellcontent::CellContentRecord::new(
        key(STRUCTURE_TYPE, 0, instance),
        spore_cellcontent::CellContent::Structure(
            spore_cellcontent::structure::decode(&structure(1, 0)).expect("synthetic structure"),
        ),
    )
}

/// Every record type paired with a small synthetic payload, for the
/// "every type decodes" and "every prefix length is refused cleanly" sweeps.
pub fn one_of_each() -> Vec<(u32, Vec<u8>)> {
    vec![
        (GLOBALS_TYPE, globals_zeroed()),
        (EFFECT_MAP_TYPE, effect_map(1)),
        (BACKGROUND_MAP_TYPE, background_map(3)),
        (STRUCTURE_TYPE, structure(1, 0)),
        (WORLD_TYPE, world(1, 0x1111, 1)),
        (RANDOM_CREATURE_TYPE, random_creature(1)),
        (POWERS_TYPE, powers()),
        (LOOK_TABLE_TYPE, look_table(1)),
        (LOOK_ALGORITHM_TYPE, look_algorithm(1, [0, 0, 0])),
        (LOOT_TABLE_TYPE, loot_table(1, 0, 0)),
        (POPULATE_TYPE, populate(1, 0, 0)),
        (CELL_TYPE, cell(0, "x", 0, 0)),
    ]
}

/// Every counted record with a single count field:
/// `(type id, byte offset of its count, stride, header field name)`.
///
/// Nine record types are counted; `world` is the ninth and is absent here
/// because it has **two** counts sharing one span, so it is exercised separately.
///
/// The count offset is the load-bearing column and it is **not** uniform: six
/// records put the count first and two (`look_table`, `look_algorithm`) put it
/// second, after a dead pointer slot. Poking the wrong slot yields a record that
/// fails the extent check loudly, which is why this table exists in the test
/// support rather than being recomputed.
pub const COUNTED: [(u32, usize, usize, &str); 8] = [
    (EFFECT_MAP_TYPE, 0, 28, "numEntries"),
    (BACKGROUND_MAP_TYPE, 0, 16, "numEntries"),
    (STRUCTURE_TYPE, 24, 40, "numAttachments"),
    (RANDOM_CREATURE_TYPE, 0, 28, "numEntries"),
    (LOOK_TABLE_TYPE, 4, 8, "numEntries"),
    (LOOK_ALGORITHM_TYPE, 4, 20, "numEntries"),
    (LOOT_TABLE_TYPE, 4, 28, "numEntries"),
    (POPULATE_TYPE, 8, 76, "numMarkers"),
];

/// A valid single-entry payload for each counted record type.
pub fn counted_payload(type_id: u32) -> Vec<u8> {
    match type_id {
        EFFECT_MAP_TYPE => effect_map(1),
        BACKGROUND_MAP_TYPE => background_map(1),
        STRUCTURE_TYPE => structure(1, 0),
        RANDOM_CREATURE_TYPE => random_creature(1),
        LOOK_TABLE_TYPE => look_table(1),
        LOOK_ALGORITHM_TYPE => look_algorithm(1, [0, 0, 0]),
        LOOT_TABLE_TYPE => loot_table(1, 0, 0),
        POPULATE_TYPE => populate(1, 0, 0),
        other => panic!("0x{other:08x} is not a counted record"),
    }
}

/// The twelve type ids, in declaration order.
pub fn all_types() -> [u32; 12] {
    spore_cellcontent::SUPPORTED_TYPES
}
