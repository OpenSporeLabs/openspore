//! `cCellWorldResource` — which populate records a level uses, and how the
//! current drifts.
//!
//! Type id `0x9B8E862F`. Header + `nPop` 12-byte level entries + `nAdv` 24-byte
//! advect entries.
//!
//! ```text
//! @000  u32   numPopulate
//! @004  u32   populatePtr      dead pointer slot, observed 0 / 0x10
//! @008  u32   numAdvect
//! @012  u32   advectPtr        dead pointer slot, observed 0 / 0x28 / 0x100
//! @016  cLevelEntry  * nPop    12 B each
//!        cAdvectEntry * nAdv    24 B each
//! ```
//!
//! # Two counts, one exact extent
//!
//! Both oracles compute `16 + 12*nPop + 24*nAdv` and compare it against the
//! record length with `!=`. The C++ reference writes it the long way round — a
//! `countFits` on `numPopulate`, then a `countFits` on `numAdvect` **and** an
//! equality check on the total — but the binding constraint is still the
//! equality, so the reproduced rule is [`SpanRule::ExactFit`]. `SPAN_RULE` is
//! published so that the question has one answer per record.
//!
//! # The advect floats are floats, not ints
//!
//! **Documented drift.** The SDK types `strength`, `variance` and `period` as
//! `int`; the file stores `f32` and they decode as clean values (0.5..3.5, 0.0,
//! 1.0). Both oracles read them with `<f`. This crate follows the file, and the
//! claim is [`crate::claims::ADVECT_FLOAT_OVERRIDES_SDK_INT`].
//!
//! # `advectID` points outside this family
//!
//! Each advect entry names a flow-field resource. The C++ reference spells its
//! type `0x04805684`; that id is not one of the twelve cell-content records, so
//! this crate can never resolve it and says so with
//! [`CellReferenceError::OutsideFamily`] rather than reporting a missing record.
//! The id itself is [`crate::claims::ADVERT_FLOW_FIELD_TYPE`], graded `INFERRED`
//! because only the C++ reference states it and no oracle resolves the field.

use crate::error::CellContentError;
use crate::reader::{Reader, SpanRule};

/// The record type id of a cell-world record.
pub const WORLD_TYPE: u32 = spore_core::record::type_id::CELL_WORLD;

/// The record type id an advect entry's `advectID` names.
///
/// Not one of this family's twelve. See [`crate::claims::ADVERT_FLOW_FIELD_TYPE`].
pub const ADVERT_FLOW_FIELD_TYPE: u32 = 0x0480_5684;

/// Byte length of a `world` record's header.
pub const WORLD_HEADER_SIZE: usize = 16;

/// Byte stride of one `cLevelEntry`.
pub const LEVEL_ENTRY_SIZE: usize = 12;

/// Byte stride of one `cAdvectEntry`.
pub const ADVECT_ENTRY_SIZE: usize = 24;

/// A world record's declared entries must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One `cLevelEntry`: which populate record, at which player scale.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct CellLevelEntry {
    /// A `0xDA141C1B` (populate) instance id.
    pub populate: u32,
    /// 0 or 1. Read as one byte; the three bytes after it are padding and are
    /// skipped rather than interpreted.
    pub start_tile: u8,
    /// 1..=10, or [`spore_core::WILDCARD`] for "any".
    pub player_size: u32,
}

/// One `cAdvectEntry`: how the current drifts at one stage scale.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CellAdvectEntry {
    /// Stage scale, 1..=13 observed.
    pub stage_scale: u32,
    /// Player size, or -1 for "any".
    pub player_size: i32,
    /// Advect strength. **Stored as `f32`; the SDK types it `int`** — see the
    /// module documentation.
    pub strength: f32,
    /// Advect variance. Also stored as `f32`.
    pub variance: f32,
    /// Advect period. Also stored as `f32`.
    pub period: f32,
    /// A flow-field instance id. See [`ADVERT_FLOW_FIELD_TYPE`].
    pub advect_id: u32,
}

impl CellAdvectEntry {
    /// The three float fields, in declaration order.
    pub fn floats(&self) -> [f32; 3] {
        [self.strength, self.variance, self.period]
    }
}

/// The decoded `cCellWorldResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellWorld {
    /// Declared level-entry count, as read (before the span check).
    pub num_populate: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub populate_ptr: u32,
    /// Declared advect-entry count, as read.
    pub num_advect: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub advect_ptr: u32,
    /// The level entries.
    pub populate: Vec<CellLevelEntry>,
    /// The advect entries.
    pub advect: Vec<CellAdvectEntry>,
}

impl CellWorld {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        WORLD_TYPE
    }
}

/// Reads a cell-world record.
///
/// The span check runs on the **combined** extent `16 + 12*nPop + 24*nAdv`, in
/// `u64` arithmetic, so a record declaring `0x7FFFFFFF` of either kind produces
/// a typed [`CellContentError::CountTooLarge`] naming the arithmetic rather than
/// an overflow.
pub fn decode(bytes: &[u8]) -> Result<CellWorld, CellContentError> {
    if bytes.len() < WORLD_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: WORLD_TYPE,
            actual: bytes.len(),
            minimum: WORLD_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let num_populate = r.u32();
    let populate_ptr = r.u32();
    let num_advect = r.u32();
    let advect_ptr = r.u32();

    // One rule, one arithmetic, one error per offending count. Everything is `i64`
    // so that two `0x7FFFFFFF` counts cannot overflow the sum.
    let n_pop = num_populate as i32;
    let n_adv = num_advect as i32;
    if n_pop < 0 {
        return Err(CellContentError::NegativeCount {
            type_id: WORLD_TYPE,
            field: "numPopulate",
            count: n_pop,
        });
    }
    if n_adv < 0 {
        return Err(CellContentError::NegativeCount {
            type_id: WORLD_TYPE,
            field: "numAdvect",
            count: n_adv,
        });
    }
    let available = (bytes.len() - WORLD_HEADER_SIZE) as i64;
    // Step 1: do the populate entries themselves fit? Reported against
    // `numPopulate` alone so the message names the count that is too big, which
    // is the form the C++ reference's first `countFits` produces too.
    let pop_span = LEVEL_ENTRY_SIZE as i64 * n_pop as i64;
    if pop_span > available {
        return Err(CellContentError::CountTooLarge {
            type_id: WORLD_TYPE,
            field: "numPopulate",
            count: n_pop as u32,
            item_size: LEVEL_ENTRY_SIZE,
            needed: (WORLD_HEADER_SIZE + pop_span as usize),
            available: bytes.len(),
        });
    }
    // Step 2: do the advect entries fit in what is left?
    let adv_span = ADVECT_ENTRY_SIZE as i64 * n_adv as i64;
    if pop_span + adv_span > available {
        return Err(CellContentError::CountTooLarge {
            type_id: WORLD_TYPE,
            field: "numAdvect",
            count: n_adv as u32,
            item_size: ADVECT_ENTRY_SIZE,
            needed: (WORLD_HEADER_SIZE + (pop_span + adv_span) as usize),
            available: bytes.len(),
        });
    }
    // Step 3: does the pair account for the whole record? Under `ExactFit` a
    // remainder is an error naming the pair, because neither count alone is
    // responsible for it.
    let needed = pop_span + adv_span;
    if SPAN_RULE == SpanRule::ExactFit && needed != available {
        return Err(CellContentError::TrailingBytes {
            type_id: WORLD_TYPE,
            field: "numPopulate+numAdvect",
            count: (n_pop as u32).wrapping_add(n_adv as u32),
            trailing: (available - needed) as usize,
        });
    }

    let mut populate = Vec::with_capacity(num_populate as usize);
    for _ in 0..num_populate {
        let populate_ref = r.u32();
        let start_tile = r.u8();
        r.skip(3);
        let player_size = r.u32();
        populate.push(CellLevelEntry {
            populate: populate_ref,
            start_tile,
            player_size,
        });
    }
    let mut advect = Vec::with_capacity(num_advect as usize);
    for _ in 0..num_advect {
        let stage_scale = r.u32();
        let player_size = r.i32();
        let strength = r.f32();
        let variance = r.f32();
        let period = r.f32();
        let advect_id = r.u32();
        advect.push(CellAdvectEntry {
            stage_scale,
            player_size,
            strength,
            variance,
            period,
            advect_id,
        });
    }

    Ok(CellWorld {
        num_populate,
        populate_ptr,
        num_advect,
        advect_ptr,
        populate,
        advect,
    })
}
