//! `cCellRandomCreatureResource` and `cCellPowersResource` — what spawns, and
//! what the player can do.
//!
//! | record | type id | shape |
//! |---|---|---|
//! | `cCellRandomCreatureResource` | `0xF9C3D770` | `{i32 count, u32 dead_ptr}` + `n * 28` |
//! | `cCellPowersResource` | `0x754BE343` | fixed 8 bytes |
//!
//! # `creatureID` is a soft id, and must not be resolved as a reference
//!
//! `tools/spore/cellres/randcreature.py` is explicit: "soft creature id (NOT a
//! cell-record ref; some ids appear in other resource types, one is absent
//! everywhere -> validate as domain, not resolution)". This crate therefore does
//! **not** emit `creature_id` from [`crate::reference`] and
//! [`CellRandomCreatureEntry::creature_id_meaning`] is a non-finding
//! ([`crate::claims::CREATURE_ID_REGISTRY`]).
//!
//! That is the difference between "we looked and there is nothing there" and
//! "there is nothing there". Both are true here; only the first is something
//! this build can assert.

use spore_core::Fact;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of a random-creature record.
pub const RANDOM_CREATURE_TYPE: u32 = spore_core::record::type_id::CELL_RANDOM_CREATURE;

/// The record type id of a powers record.
pub const POWERS_TYPE: u32 = spore_core::record::type_id::CELL_POWERS;

/// Byte length of a random-creature record's header.
pub const RANDOM_CREATURE_HEADER_SIZE: usize = 8;

/// Byte stride of one `cRandomCreatureEntry`.
pub const RANDOM_CREATURE_ENTRY_SIZE: usize = 28;

/// The exact byte extent of a powers record.
pub const POWERS_SIZE: usize = 8;

/// A random-creature record's declared entries must account for the whole
/// record.
pub const RANDOM_CREATURE_SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// A powers record has a fixed extent, so it has no counted-entry span.
pub const POWERS_SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One decoded `cRandomCreatureEntry`.
#[derive(Debug, Clone, Copy, PartialEq)]
#[allow(missing_docs)]
pub struct CellRandomCreatureEntry {
    pub entry_type: u32,
    /// A soft creature id. **Not** a cell-record reference.
    pub creature_id: u32,
    pub weight: f32,
    pub speed_min: i32,
    pub speed_max: i32,
    pub danger_min: i32,
    pub danger_max: i32,
}

impl CellRandomCreatureEntry {
    /// What the `creature_id` names.
    ///
    /// Always a non-finding, and the reason matters: there is no creature
    /// registry in this build, and one of the observed ids is absent from every
    /// package, so resolving it would be inventing a target.
    pub fn creature_id_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::CREATURE_ID_REGISTRY)
    }

    /// The four stat bounds, in layout order.
    pub fn stats(&self) -> [(&'static str, i32); 4] {
        [
            ("speedMin", self.speed_min),
            ("speedMax", self.speed_max),
            ("dangerMin", self.danger_min),
            ("dangerMax", self.danger_max),
        ]
    }
}

/// The decoded `cCellRandomCreatureResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellRandomCreature {
    /// Declared entry count, as read.
    pub num_entries: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// The rows.
    pub entries: Vec<CellRandomCreatureEntry>,
}

impl CellRandomCreature {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        RANDOM_CREATURE_TYPE
    }
}

/// Reads a random-creature record.
pub fn decode_random_creature(bytes: &[u8]) -> Result<CellRandomCreature, CellContentError> {
    if bytes.len() < RANDOM_CREATURE_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: RANDOM_CREATURE_TYPE,
            actual: bytes.len(),
            minimum: RANDOM_CREATURE_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let num_entries = r.u32();
    let entries_ptr = r.u32();

    check_span(
        RANDOM_CREATURE_SPAN_RULE,
        RANDOM_CREATURE_TYPE,
        "numEntries",
        RANDOM_CREATURE_HEADER_SIZE,
        RANDOM_CREATURE_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let entry_type = r.u32();
        let creature_id = r.u32();
        let weight = r.f32();
        let speed_min = r.i32();
        let speed_max = r.i32();
        let danger_min = r.i32();
        let danger_max = r.i32();
        entries.push(CellRandomCreatureEntry {
            entry_type,
            creature_id,
            weight,
            speed_min,
            speed_max,
            danger_min,
            danger_max,
        });
    }

    Ok(CellRandomCreature {
        num_entries,
        entries_ptr,
        entries,
    })
}

/// The decoded `cCellPowersResource`: two fields, eight bytes.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CellPowers {
    /// Teleport cost; 10 on the one observed record.
    pub teleport_cost: i32,
    /// Teleport range; 10.0 on the one observed record.
    pub teleport_range: f32,
}

impl CellPowers {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        POWERS_TYPE
    }
}

/// Reads a powers record.
///
/// Fails unless `bytes.len() == [`POWERS_SIZE`] exactly.
pub fn decode_powers(bytes: &[u8]) -> Result<CellPowers, CellContentError> {
    if bytes.len() != POWERS_SIZE {
        return Err(CellContentError::ExtentMismatch {
            type_id: POWERS_TYPE,
            actual: bytes.len(),
            expected: POWERS_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    Ok(CellPowers {
        teleport_cost: r.i32(),
        teleport_range: r.f32(),
    })
}
