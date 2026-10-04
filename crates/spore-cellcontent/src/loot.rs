//! `cCellLootTableResource` — what killing a cell yields.
//!
//! Type id `0xD92AF091`. 36-byte header + `n` 28-byte `cLootTableEntry` rows.
//!
//! ```text
//! @000  u32   entries           dead pointer slot
//! @004  i32   numEntries        0..=9 observed
//! @008  f32   minRadius
//! @012  f32   maxRadius
//! @016  f32   initialAlpha
//! @020  f32   expelForce
//! @024  i32   effect            zero on every observed record
//! @028  u8    mustHavePart      @029..@032 = 3 pad bytes
//! @032  f32   delay
//! @036  cLootTableEntry * n    28 B each
//! ```
//!
//! # The three pad bytes at +29 are the honest case in miniature
//!
//! They are read, stored as [`CellLootTable::header_padding`] and checked, and
//! **their meaning is recorded as a non-finding**
//! ([`crate::claims::LOOT_HEADER_PADDING`]). All three are zero on every
//! observed record. That is an observation about *position and width* at
//! [`spore_core::EvidenceLevel::Observed`] and an absence at
//! [`spore_core::Fact::unavailable`] about *meaning*, and the crate keeps both
//! rather than collapsing them: the decoder does not skip the bytes (so a
//! non-zero byte is an observable `PaddingNonZero` issue rather than a silent
//! loss) and the claim table says nobody knows what they are.
//!
//! # `weight` is a percentage, not a fraction
//!
//! Observed values run about 0.01 to 90. Both oracles bound it `0..=1000`, which
//! is why this crate uses that bound rather than `0..=1`.

use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of a loot-table record.
pub const LOOT_TABLE_TYPE: u32 = spore_core::record::type_id::CELL_LOOT_TABLE;

/// Byte length of a loot-table record's header.
pub const LOOT_TABLE_HEADER_SIZE: usize = 36;

/// Byte stride of one `cLootTableEntry`.
pub const LOOT_ENTRY_SIZE: usize = 28;

/// A loot-table record's declared entries must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One decoded `cLootTableEntry`: one reward row.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CellLootEntry {
    /// 0 = Nothing, 1 = Cell, 2 = Table observed.
    pub entry_type: u32,
    /// A `0xDFAD9F51` (cell) instance id, or 0.
    pub cell: u32,
    /// A `0xD92AF091` (loot-table) instance id, or 0.
    pub table: u32,
    /// Selection weight, percent-ish.
    pub weight: f32,
    /// How many, 0..=4 observed.
    pub count: i32,
    /// 0 or 1 observed.
    pub count_delta: i32,
    /// -3..=1 observed.
    pub level_offset: i32,
}

/// The decoded `cCellLootTableResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellLootTable {
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// Declared entry count, as read.
    pub num_entries: u32,
    pub min_radius: f32,
    pub max_radius: f32,
    pub initial_alpha: f32,
    pub expel_force: f32,
    /// Zero on every observed record.
    pub effect: i32,
    /// 0 or 1 observed. Kept as the byte that was read.
    pub must_have_part: u8,
    /// The three bytes at +29..+32. Zero on every observed record; read rather
    /// than skipped so a non-zero byte is observable.
    pub header_padding: [u8; 3],
    pub delay: f32,
    /// The reward rows.
    pub entries: Vec<CellLootEntry>,
}

impl CellLootTable {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        LOOT_TABLE_TYPE
    }

    /// The five header floats, in layout order, with their names.
    pub fn header_floats(&self) -> [(&'static str, f32); 5] {
        [
            ("minRadius", self.min_radius),
            ("maxRadius", self.max_radius),
            ("initialAlpha", self.initial_alpha),
            ("expelForce", self.expel_force),
            ("delay", self.delay),
        ]
    }
}

/// Reads a loot-table record.
///
/// # Note on the C++ reference's two checks
///
/// `src/assets/CellResource.cpp` calls `countFits` at offset 8 *and*
/// `spanMatches` at offset 36. The first is implied by the second: if
/// `36 + 28*n == size` then `8 + 28*n <= size` always holds. So the binding rule
/// is [`SpanRule::ExactFit`] and the redundant early check changes no outcome.
/// It is not reproduced here, and `tests/decode.rs` pins the outcome rather than
/// the call sequence.
pub fn decode(bytes: &[u8]) -> Result<CellLootTable, CellContentError> {
    if bytes.len() < LOOT_TABLE_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: LOOT_TABLE_TYPE,
            actual: bytes.len(),
            minimum: LOOT_TABLE_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let entries_ptr = r.u32();
    let num_entries = r.u32();

    check_span(
        SPAN_RULE,
        LOOT_TABLE_TYPE,
        "numEntries",
        LOOT_TABLE_HEADER_SIZE,
        LOOT_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let min_radius = r.f32();
    let max_radius = r.f32();
    let initial_alpha = r.f32();
    let expel_force = r.f32();
    let effect = r.i32();
    let must_have_part = r.u8();
    let header_padding = r.bytes3();
    let delay = r.f32();

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let entry_type = r.u32();
        let cell = r.u32();
        let table = r.u32();
        let weight = r.f32();
        let count = r.i32();
        let count_delta = r.i32();
        let level_offset = r.i32();
        entries.push(CellLootEntry {
            entry_type,
            cell,
            table,
            weight,
            count,
            count_delta,
            level_offset,
        });
    }

    Ok(CellLootTable {
        entries_ptr,
        num_entries,
        min_radius,
        max_radius,
        initial_alpha,
        expel_force,
        effect,
        must_have_part,
        header_padding,
        delay,
        entries,
    })
}
