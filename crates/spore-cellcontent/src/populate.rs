//! `cCellPopulateResource` — the scene spawners of one level.
//!
//! Type id `0xDA141C1B`. 16-byte header + `n` 76-byte `cMarker` rows.
//!
//! ```text
//! @000  u32   scale            0 = any, 3 / 4 observed
//! @004  u32   maskTexture      all zero on every observed record (dead ref)
//! @008  u32   numMarkers
//! @012  u32   markersPtr       dead pointer slot; observed 0 / 16 (= header size)
//! @016  cMarker * n           76 B each
//! ```
//!
//! # Four of a marker's nineteen fields are dead, and this crate still carries
//! # them
//!
//! `field_0`, `field_4`, `field_8` and `field_14` are zero on every marker of
//! every observed record. **That is an observation, not a meaning.** Their
//! positions and widths are [`spore_core::EvidenceLevel::Observed`] — the bytes
//! are there and they are read — while what they *are* is
//! [`spore_core::Fact::unavailable`] with the reason
//! [`crate::claims::DEAD_MARKER_FIELD`]. `CellMarker::dead_fields_meaning()`
//! returns that non-finding.
//!
//! Zeroing them in the decoder would have been the wrong move twice over: it
//! would make "the record says zero" indistinguishable from "this build has no
//! field here", and it would make the domain checker's `dead field nonzero`
//! invariant unreachable.

use spore_core::Fact;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of a populate record.
pub const POPULATE_TYPE: u32 = spore_core::record::type_id::CELL_POPULATE;

/// Byte length of a populate record's header.
pub const POPULATE_HEADER_SIZE: usize = 16;

/// Byte stride of one `cMarker`.
pub const MARKER_SIZE: usize = 76;

/// A populate record's declared markers must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// The one decoded `cMarker`: a scene spawner.
#[derive(Debug, Clone, Copy, PartialEq)]
#[allow(missing_docs)]
pub struct CellMarker {
    pub field_0: u32,
    pub field_4: u32,
    pub field_8: u32,
    pub z_offset: f32,
    pub z_offset_max: f32,
    pub field_14: u32,
    /// A `0xDFAD9F51` (cell) instance id, or 0 for "none".
    pub distribute_cell: u32,
    /// A `0xDFAD9F51` (cell) instance id, or 0 for "none".
    pub cluster_cell: u32,
    /// Zero on every observed marker. Carried, not interpreted.
    pub encounter_populate: u32,
    pub plant_type: u32,
    pub marker_type: u32,
    pub count: f32,
    pub count_easy: f32,
    pub count_medium: f32,
    pub count_hard: f32,
    pub size: i32,
    pub parts: i32,
    pub linear: i32,
    /// Zero on every observed marker. Carried, not interpreted.
    pub encounter_scale: i32,
}

impl CellMarker {
    /// The four fields that are zero on every observed marker.
    pub fn dead_fields(&self) -> [(&'static str, u32); 4] {
        [
            ("field_0", self.field_0),
            ("field_4", self.field_4),
            ("field_8", self.field_8),
            ("field_14", self.field_14),
        ]
    }

    /// The four count floats, in layout order.
    pub fn counts(&self) -> [(&'static str, f32); 4] {
        [
            ("count", self.count),
            ("count_easy", self.count_easy),
            ("count_med", self.count_medium),
            ("count_hard", self.count_hard),
        ]
    }

    /// What the dead fields *are*.
    ///
    /// Always a non-finding: all four read as zero everywhere observed, and a
    /// constant is not evidence about what a field means.
    pub fn dead_fields_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::DEAD_MARKER_FIELD)
    }
}

/// The decoded `cCellPopulateResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellPopulate {
    /// Level scale; 0 means "any".
    pub scale: u32,
    /// Dead reference; zero on every observed record.
    pub mask_texture: u32,
    /// Declared marker count, as read.
    pub num_markers: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub markers_ptr: u32,
    /// The markers.
    pub markers: Vec<CellMarker>,
}

impl CellPopulate {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        POPULATE_TYPE
    }
}

/// Reads a populate record.
pub fn decode(bytes: &[u8]) -> Result<CellPopulate, CellContentError> {
    if bytes.len() < POPULATE_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: POPULATE_TYPE,
            actual: bytes.len(),
            minimum: POPULATE_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let scale = r.u32();
    let mask_texture = r.u32();
    let num_markers = r.u32();
    let markers_ptr = r.u32();

    check_span(
        SPAN_RULE,
        POPULATE_TYPE,
        "numMarkers",
        POPULATE_HEADER_SIZE,
        MARKER_SIZE,
        num_markers as i32,
        bytes.len(),
    )?;

    let mut markers = Vec::with_capacity(num_markers as usize);
    for _ in 0..num_markers {
        let field_0 = r.u32();
        let field_4 = r.u32();
        let field_8 = r.u32();
        let z_offset = r.f32();
        let z_offset_max = r.f32();
        let field_14 = r.u32();
        let distribute_cell = r.u32();
        let cluster_cell = r.u32();
        let encounter_populate = r.u32();
        let plant_type = r.u32();
        let marker_type = r.u32();
        let count = r.f32();
        let count_easy = r.f32();
        let count_medium = r.f32();
        let count_hard = r.f32();
        let size = r.i32();
        let parts = r.i32();
        let linear = r.i32();
        let encounter_scale = r.i32();
        markers.push(CellMarker {
            field_0,
            field_4,
            field_8,
            z_offset,
            z_offset_max,
            field_14,
            distribute_cell,
            cluster_cell,
            encounter_populate,
            plant_type,
            marker_type,
            count,
            count_easy,
            count_medium,
            count_hard,
            size,
            parts,
            linear,
            encounter_scale,
        });
    }

    Ok(CellPopulate {
        scale,
        mask_texture,
        num_markers,
        markers_ptr,
        markers,
    })
}
