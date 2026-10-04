//! `cCellLookTableResource` and `cCellLookAlgorithmResource` — how a cell's
//! appearance is chosen.
//!
//! Two records, both with an 8-byte header of `{u32 dead_ptr, i32 count}`:
//!
//! | record | type id | entry size | entries |
//! |---|---|---|---|
//! | `cCellLookTableResource` | `0x8C042499` | 8 | `{i32 type, f32 value}` |
//! | `cCellLookAlgorithmResource` | `0xDBA35AE2` | 20 | `{u32 type, u32 action, u32 player, u32 npc, u32 epic}` |
//!
//! # The header order differs from the counted records that put the count first
//!
//! Both look records put the **dead pointer slot first and the count second**;
//! `effectMap`, `backgroundMap`, `randomCreature` and every other counted record
//! put the count first. Getting that backwards still lands on an 8-byte header,
//! so a record with one entry decodes to *something* either way — but the
//! pointers observed in the corpus are non-zero (0x10, 0x28, 0x100), so reading
//! the pointer as the count fails the span check loudly rather than silently.
//! `tests/decode.rs` pins the order with a header whose count and pointer differ.
//!
//! # `action`: the C++ and Python conditions are the same set
//!
//! The Python oracle writes `action not in (0, 18..22, 0xFFFFFFFF) and action >
//! 60` and the C++ writes `action > 60 and action != 0xFFFFFFFF`. These agree on
//! every `u32`: the Python form additionally exempts 0, 18..22 — but none of
//! those exceeds 60, so the exemption never fires. Both reduce to "the only
//! offenders are 61..=0xFFFFFFFE". This crate uses the Python form because it
//! states the permitted values; see `is_action_plausible`.

use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of a look-table record.
pub const LOOK_TABLE_TYPE: u32 = spore_core::record::type_id::CELL_LOOK_TABLE;

/// The record type id of a look-algorithm record.
pub const LOOK_ALGORITHM_TYPE: u32 = spore_core::record::type_id::CELL_LOOK_ALGORITHM;

/// Byte length of either look record's header.
pub const LOOK_HEADER_SIZE: usize = 8;

/// Byte stride of one `cLookTableEntry`.
pub const LOOK_ENTRY_SIZE: usize = 8;

/// Byte stride of one `cLookAlgorithmEntry`.
pub const LOOK_ALGORITHM_ENTRY_SIZE: usize = 20;

/// Both look records' declared entries must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// The `action` value that means "no action".
pub const LOOK_ACTION_NONE: u32 = 0;

/// The `action` sentinel that means "unset".
pub const LOOK_ACTION_UNSET: u32 = 0xFFFF_FFFF;

/// One decoded `cLookTableEntry`.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CellLookEntry {
    /// Which appearance axis; 0..=11 observed.
    pub entry_type: i32,
    /// The value on that axis; 1, 5 or 10 observed.
    pub value: f32,
}

/// The decoded `cCellLookTableResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellLookTable {
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// Declared entry count, as read.
    pub num_entries: u32,
    /// The rows.
    pub entries: Vec<CellLookEntry>,
}

impl CellLookTable {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        LOOK_TABLE_TYPE
    }
}

/// One decoded `cLookAlgorithmEntry`.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct CellLookAlgorithmEntry {
    /// 0, 1 or 2 observed.
    pub entry_type: u32,
    /// 0, 18..=22, or the unset sentinel.
    pub action: u32,
    /// A `0x8C042499` (look-table) instance id, or 0.
    pub player: u32,
    /// A `0x8C042499` (look-table) instance id, or 0.
    pub npc: u32,
    /// A `0x8C042499` (look-table) instance id, or 0.
    pub epic: u32,
}

impl CellLookAlgorithmEntry {
    /// Whether `action` is one of the values the corpus uses.
    ///
    /// Equivalent to the C++ reference's `action > 60 && action != 0xFFFFFFFF`
    /// for every `u32`, and written the way the Python oracle writes it so the
    /// permitted set is visible in the source.
    pub const fn is_action_plausible(action: u32) -> bool {
        matches!(action, 0 | 18 | 19 | 20 | 21 | 22 | LOOK_ACTION_UNSET) || action <= 60
    }

    /// The three look-table references, in the order the reference layer
    /// enumerates them (`player`, `npc`, `epic`).
    pub fn look_tables(&self) -> [u32; 3] {
        [self.player, self.npc, self.epic]
    }
}

/// The decoded `cCellLookAlgorithmResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellLookAlgorithm {
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// Declared entry count, as read.
    pub num_entries: u32,
    /// The rows.
    pub entries: Vec<CellLookAlgorithmEntry>,
}

impl CellLookAlgorithm {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        LOOK_ALGORITHM_TYPE
    }
}

/// Reads a look-table record.
pub fn decode_table(bytes: &[u8]) -> Result<CellLookTable, CellContentError> {
    if bytes.len() < LOOK_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: LOOK_TABLE_TYPE,
            actual: bytes.len(),
            minimum: LOOK_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let entries_ptr = r.u32();
    let num_entries = r.u32();

    check_span(
        SPAN_RULE,
        LOOK_TABLE_TYPE,
        "numEntries",
        LOOK_HEADER_SIZE,
        LOOK_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let entry_type = r.i32();
        let value = r.f32();
        entries.push(CellLookEntry { entry_type, value });
    }

    Ok(CellLookTable {
        entries_ptr,
        num_entries,
        entries,
    })
}

/// Reads a look-algorithm record.
pub fn decode_algorithm(bytes: &[u8]) -> Result<CellLookAlgorithm, CellContentError> {
    if bytes.len() < LOOK_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: LOOK_ALGORITHM_TYPE,
            actual: bytes.len(),
            minimum: LOOK_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let entries_ptr = r.u32();
    let num_entries = r.u32();

    check_span(
        SPAN_RULE,
        LOOK_ALGORITHM_TYPE,
        "numEntries",
        LOOK_HEADER_SIZE,
        LOOK_ALGORITHM_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let entry_type = r.u32();
        let action = r.u32();
        let player = r.u32();
        let npc = r.u32();
        let epic = r.u32();
        entries.push(CellLookAlgorithmEntry {
            entry_type,
            action,
            player,
            npc,
            epic,
        });
    }

    Ok(CellLookAlgorithm {
        entries_ptr,
        num_entries,
        entries,
    })
}
