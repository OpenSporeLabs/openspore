//! `cCellStructureResource` — a cell's skeleton plus the effects attached to it.
//!
//! Type id `0x4B9EF6DC`. 28-byte header + `n` 40-byte `cSPAttachment` rows.
//!
//! ```text
//! @000  u32  onDeath            effect reference (no type word)
//! @004  u32  onDeathSmall       effect reference (no type word)
//! @008  u32  onDeathLarge       effect reference (no type word)
//! @012  u32  onHatch            effect reference (no type word)
//! @016  u32  onStartHatch       zero on every observed record
//! @020  u32  attachments        dead pointer slot
//! @024  i32  numAttachments     1..=3 observed
//! @028  cSPAttachment * n      40 B each
//! ```
//!
//! # Two fields of an attachment are opaque, in two different ways
//!
//! * `structure` is zero on every observed attachment. Position and width are
//!   [`spore_core::EvidenceLevel::Observed`]; what it would name is
//!   [`spore_core::Fact::unavailable`]
//!   ([`crate::claims::ATTACHMENT_STRUCTURE_FIELD`]).
//! * `effect_id` holds 128 distinct values across the corpus and **may be
//!   negative**. It is a *soft* effect id: this build has no effect registry, so
//!   [`crate::claims::EFFECT_ID_REGISTRY`] is a non-finding and
//!   `attachment.effect_id_meaning()` returns it.
//!
//! There is also a trap worth naming. The C++ reference emits
//! `effect_id` as a reference with `static_cast<uint32_t>(effectID)`, so a
//! negative effect id becomes a huge instance id — `0xFFFFFFFF` for `-1` —
//! which then looks exactly like a "no reference" sentinel. This crate carries
//! the signed value unchanged and refuses it as a reference explicitly; see
//! [`crate::claims::NEGATIVE_EFFECT_ID_IS_NOT_A_REFERENCE`].

use spore_core::Fact;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of a structure record.
pub const STRUCTURE_TYPE: u32 = spore_core::record::type_id::CELL_STRUCTURE;

/// Byte length of a structure record's header.
pub const STRUCTURE_HEADER_SIZE: usize = 28;

/// Byte stride of one `cSPAttachment`.
pub const ATTACHMENT_SIZE: usize = 40;

/// A structure record's declared attachments must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One decoded `cSPAttachment`: an attachable effect on a structure bone.
#[derive(Debug, Clone, Copy, PartialEq)]
#[allow(missing_docs)]
pub struct CellStructureAttachment {
    /// Bone index; 0, 3 or -1 observed.
    pub bone: i32,
    pub attachment_type: u32,
    /// A `0x4B9EF6DC` instance id; zero on every observed attachment.
    pub structure: u32,
    /// A `0xF9C3D770` (random-creature) instance id, or 0.
    pub random_creature: u32,
    /// A soft effect id. Negative values occur and are **not** references.
    pub effect_id: i32,
    pub level_min: i32,
    pub level_max: i32,
    /// RGB, each 0..=1.5 observed.
    pub color: [f32; 3],
}

impl CellStructureAttachment {
    /// What the `structure` field would name.
    ///
    /// Always a non-finding: zero on every observed attachment.
    pub fn structure_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::ATTACHMENT_STRUCTURE_FIELD)
    }

    /// What the `effect_id` names.
    ///
    /// Always a non-finding: no effect-name registry exists in this build or in
    /// the reference implementation.
    pub fn effect_id_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::EFFECT_ID_REGISTRY)
    }
}

/// The decoded `cCellStructureResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellStructure {
    /// Effect reference (no type word).
    pub on_death: u32,
    /// Effect reference (no type word).
    pub on_death_small: u32,
    /// Effect reference (no type word).
    pub on_death_large: u32,
    /// Effect reference (no type word).
    pub on_hatch: u32,
    /// Zero on every observed record. Carried, not interpreted.
    pub on_start_hatch: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub attachments_ptr: u32,
    /// Declared attachment count, as read.
    pub num_attachments: u32,
    /// The attachments.
    pub attachments: Vec<CellStructureAttachment>,
}

impl CellStructure {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        STRUCTURE_TYPE
    }

    /// The five header effect slots, in layout order, with the index the
    /// reference layer uses for each.
    pub fn header_effects(&self) -> [(&'static str, u32); 5] {
        [
            ("onDeath", self.on_death),
            ("onDeathSmall", self.on_death_small),
            ("onDeathLarge", self.on_death_large),
            ("onHatch", self.on_hatch),
            ("onStartHatch", self.on_start_hatch),
        ]
    }
}

/// Reads a structure record.
pub fn decode(bytes: &[u8]) -> Result<CellStructure, CellContentError> {
    if bytes.len() < STRUCTURE_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: STRUCTURE_TYPE,
            actual: bytes.len(),
            minimum: STRUCTURE_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let on_death = r.u32();
    let on_death_small = r.u32();
    let on_death_large = r.u32();
    let on_hatch = r.u32();
    let on_start_hatch = r.u32();
    let attachments_ptr = r.u32();
    let num_attachments = r.u32();

    check_span(
        SPAN_RULE,
        STRUCTURE_TYPE,
        "numAttachments",
        STRUCTURE_HEADER_SIZE,
        ATTACHMENT_SIZE,
        num_attachments as i32,
        bytes.len(),
    )?;

    let mut attachments = Vec::with_capacity(num_attachments as usize);
    for _ in 0..num_attachments {
        let bone = r.i32();
        let attachment_type = r.u32();
        let structure = r.u32();
        let random_creature = r.u32();
        let effect_id = r.i32();
        let level_min = r.i32();
        let level_max = r.i32();
        let color = [r.f32(), r.f32(), r.f32()];
        attachments.push(CellStructureAttachment {
            bone,
            attachment_type,
            structure,
            random_creature,
            effect_id,
            level_min,
            level_max,
            color,
        });
    }

    Ok(CellStructure {
        on_death,
        on_death_small,
        on_death_large,
        on_hatch,
        on_start_hatch,
        attachments_ptr,
        num_attachments,
        attachments,
    })
}
