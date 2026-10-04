//! `cCellEffectMapResource` and `cCellBackgroundMapResource` — where the
//! effects are and what the water looks like.
//!
//! | record | type id | header | entry |
//! |---|---|---|---|
//! | `cCellEffectMapResource` | `0x433FB70C` | `{i32 count, u32 dead_ptr}` | 28 B |
//! | `cCellBackgroundMapResource` | `0x612B3191` | `{i32 count, u32 dead_ptr}` | 16 B |
//!
//! # Four of a background-map row's fields and five of an effect-map row's are
//! # positional
//!
//! `cBackgroundMapEntry`'s `field_c` and four of `cEffectMapEntry`'s five floats
//! are named by **offset only**. Their position and width are
//! [`spore_core::EvidenceLevel::Observed`] and their meaning is
//! [`spore_core::Fact::unavailable`] ([`crate::claims::EFFECT_MAP_FIELD_MEANING`]).
//! The one exception is the background row's RGB triple, which is a colour ramp
//! and whose meaning is `CONFIRMED` (see [`crate::claims::BACKGROUND_RAMP_IS_RGB`]).
//!
//! # The background ladder is geometric
//!
//! The observed `field_c` values are `0, 0.5, 1.5, 5, 15, 50, 150, 500, 1500,
//! 5000, 15000, 100000` — a factor of about 3.33 per stop, tracking the cell
//! world's scale. That observation is what [`sample_background_color`]'s
//! log-space interpolation between the surrounding stops is based on; the claim
//! is [`crate::claims::BACKGROUND_LADDER_IS_GEOMETRIC`].

use spore_core::Fact;

use crate::claims;
use crate::error::CellContentError;
use crate::reader::{check_span, Reader, SpanRule};

/// The record type id of an effect-map record.
pub const EFFECT_MAP_TYPE: u32 = spore_core::record::type_id::CELL_EFFECT_MAP;

/// The record type id of a background-map record.
pub const BACKGROUND_MAP_TYPE: u32 = spore_core::record::type_id::CELL_BACKGROUND_MAP;

/// Byte length of an effect-map record's header.
pub const EFFECT_MAP_HEADER_SIZE: usize = 8;

/// Byte stride of one `cEffectMapEntry`.
pub const EFFECT_MAP_ENTRY_SIZE: usize = 28;

/// Byte length of a background-map record's header.
pub const BACKGROUND_MAP_HEADER_SIZE: usize = 8;

/// Byte stride of one `cBackgroundMapEntry`.
pub const BACKGROUND_MAP_ENTRY_SIZE: usize = 16;

/// Both map records' declared entries must account for the whole record.
pub const SPAN_RULE: SpanRule = SpanRule::ExactFit;

/// One decoded `cEffectMapEntry`.
#[derive(Debug, Clone, Copy, PartialEq)]
#[allow(missing_docs)]
pub struct CellEffectMapEntry {
    /// A soft effect id. Most observed values are absent from these packages.
    pub effect_id: u32,
    /// 2, 3 or 5 observed.
    pub entry_type: u32,
    /// -1.0 sentinel, or 0.42..=5700.
    pub field_8: f32,
    /// -1.0 sentinel, or 0.7..=14950.
    pub field_c: f32,
    /// 0.75..=20000.
    pub field_10: f32,
    /// 0.9..=20000.
    pub field_14: f32,
    /// 0, 3 or 11 observed.
    pub field_18: i32,
}

impl CellEffectMapEntry {
    /// What the five positional fields mean.
    ///
    /// Always a non-finding: the corpus constrains their values but names none of
    /// them.
    pub fn positional_meaning(&self) -> Fact<&'static str> {
        claims::non_finding(claims::EFFECT_MAP_FIELD_MEANING)
    }

    /// The four float fields, in layout order, with their names.
    pub fn floats(&self) -> [(&'static str, f32); 4] {
        [
            ("field_8", self.field_8),
            ("field_C", self.field_c),
            ("field_10", self.field_10),
            ("field_14", self.field_14),
        ]
    }
}

/// The decoded `cCellEffectMapResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellEffectMap {
    /// Declared entry count, as read.
    pub num_entries: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// The rows.
    pub entries: Vec<CellEffectMapEntry>,
}

impl CellEffectMap {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        EFFECT_MAP_TYPE
    }
}

/// One decoded `cBackgroundMapEntry`: one stop of the background colour ramp.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CellBackgroundMapEntry {
    /// Red, 0..=1.
    pub r: f32,
    /// Green, 0..=1.
    pub g: f32,
    /// Blue, 0..=1.
    pub b: f32,
    /// The ramp key: `0, 0.5, 1.5, 5, ... 100000` observed.
    pub field_c: f32,
}

impl CellBackgroundMapEntry {
    /// The ramp colour as an `[r, g, b]` triple.
    pub const fn rgb(&self) -> [f32; 3] {
        [self.r, self.g, self.b]
    }
}

/// The decoded `cCellBackgroundMapResource`.
#[derive(Debug, Clone, PartialEq)]
pub struct CellBackgroundMap {
    /// Declared entry count, as read.
    pub num_entries: u32,
    /// Dead serialized-pointer slot. Carried, never interpreted.
    pub entries_ptr: u32,
    /// The ramp stops, in record order.
    pub entries: Vec<CellBackgroundMapEntry>,
}

impl CellBackgroundMap {
    /// The record type id of this record.
    pub const fn type_id(&self) -> u32 {
        BACKGROUND_MAP_TYPE
    }
}

/// Reads an effect-map record.
pub fn decode_effect_map(bytes: &[u8]) -> Result<CellEffectMap, CellContentError> {
    if bytes.len() < EFFECT_MAP_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: EFFECT_MAP_TYPE,
            actual: bytes.len(),
            minimum: EFFECT_MAP_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let num_entries = r.u32();
    let entries_ptr = r.u32();

    check_span(
        SPAN_RULE,
        EFFECT_MAP_TYPE,
        "numEntries",
        EFFECT_MAP_HEADER_SIZE,
        EFFECT_MAP_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let effect_id = r.u32();
        let entry_type = r.u32();
        let field_8 = r.f32();
        let field_c = r.f32();
        let field_10 = r.f32();
        let field_14 = r.f32();
        let field_18 = r.i32();
        entries.push(CellEffectMapEntry {
            effect_id,
            entry_type,
            field_8,
            field_c,
            field_10,
            field_14,
            field_18,
        });
    }

    Ok(CellEffectMap {
        num_entries,
        entries_ptr,
        entries,
    })
}

/// Reads a background-map record.
pub fn decode_background_map(bytes: &[u8]) -> Result<CellBackgroundMap, CellContentError> {
    if bytes.len() < BACKGROUND_MAP_HEADER_SIZE {
        return Err(CellContentError::HeaderTooSmall {
            type_id: BACKGROUND_MAP_TYPE,
            actual: bytes.len(),
            minimum: BACKGROUND_MAP_HEADER_SIZE,
        });
    }
    let mut r = Reader::new(bytes);
    let num_entries = r.u32();
    let entries_ptr = r.u32();

    check_span(
        SPAN_RULE,
        BACKGROUND_MAP_TYPE,
        "numEntries",
        BACKGROUND_MAP_HEADER_SIZE,
        BACKGROUND_MAP_ENTRY_SIZE,
        num_entries as i32,
        bytes.len(),
    )?;

    let mut entries = Vec::with_capacity(num_entries as usize);
    for _ in 0..num_entries {
        let r_channel = r.f32();
        let g = r.f32();
        let b = r.f32();
        let field_c = r.f32();
        entries.push(CellBackgroundMapEntry {
            r: r_channel,
            g,
            b,
            field_c,
        });
    }

    Ok(CellBackgroundMap {
        num_entries,
        entries_ptr,
        entries,
    })
}

/// Samples the background colour ramp at a point on the geometric ladder.
///
/// Interpolates in `log2` space between the two surrounding stops, except
/// between the `0` stop and its successor where `log2` is undefined and the
/// interpolation is linear. Values below the first stop or above the last clamp
/// to the end stop's colour.
///
/// Returns `None` when the ramp has no usable entries, which is a **non-finding**
/// and not a black colour: an empty ramp means there is nothing to sample, and
/// answering `(0.0, 0.0, 0.0)` would be indistinguishable from a genuinely black
/// ramp.
pub fn sample_background_color(ramp: &CellBackgroundMap, ladder: f32) -> Option<[f32; 3]> {
    let first = ramp.entries.first()?;
    let last = ramp.entries.last()?;
    if ladder <= first.field_c {
        return Some(first.rgb());
    }
    if ladder >= last.field_c {
        return Some(last.rgb());
    }
    for pair in ramp.entries.windows(2) {
        let (a, b) = (&pair[0], &pair[1]);
        if ladder < a.field_c || ladder > b.field_c {
            continue;
        }
        let t = if a.field_c <= 0.0 {
            if b.field_c > a.field_c {
                (ladder - a.field_c) / (b.field_c - a.field_c)
            } else {
                0.0
            }
        } else {
            let la = a.field_c.log2();
            let lb = b.field_c.log2();
            if lb > la {
                (ladder.log2() - la) / (lb - la)
            } else {
                0.0
            }
        };
        let t = t.clamp(0.0, 1.0);
        return Some([
            a.r + (b.r - a.r) * t,
            a.g + (b.g - a.g) * t,
            a.b + (b.b - a.b) * t,
        ]);
    }
    // The ladder is inside the ramp's overall range but no stop pair brackets
    // it, which happens when the ladder is not monotonic. Answering the last
    // stop matches the C++ reference and is a defined, documented outcome
    // rather than a fabricated one.
    Some(last.rgb())
}

/// Per-channel `min`/`max` envelope of the ramp: `[rmin, gmin, bmin, rmax, gmax,
/// bmax]`.
///
/// `None` for an empty ramp, for the same non-finding reason as
/// [`sample_background_color`].
pub fn background_color_envelope(ramp: &CellBackgroundMap) -> Option<[f32; 6]> {
    let first = ramp.entries.first()?;
    let mut envelope = [first.r, first.g, first.b, first.r, first.g, first.b];
    for entry in &ramp.entries {
        envelope[0] = envelope[0].min(entry.r);
        envelope[1] = envelope[1].min(entry.g);
        envelope[2] = envelope[2].min(entry.b);
        envelope[3] = envelope[3].max(entry.r);
        envelope[4] = envelope[4].max(entry.g);
        envelope[5] = envelope[5].max(entry.b);
    }
    Some(envelope)
}
