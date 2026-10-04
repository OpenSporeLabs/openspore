//! One decoded scalar, plus the name it has in the source record.
//!
//! # Why a scalar enum exists at all
//!
//! Two independent needs produce this type:
//!
//! * the `globals` record is a flat run of 69 four-byte fields whose names come
//!   from the SDK struct but whose *kinds* vary, and a caller that wants to look
//!   one up by name needs to be handed a value without knowing in advance
//!   whether it is a `u32` or an `f32`;
//! * a domain issue has to report **what was observed**, and "field
//!   `movementStyle` was 0x1234" and "field `speed` was f0x7f800000" are not the
//!   same statement.
//!
//! `f32` is carried as its raw bit pattern in [`Scalar::F32`]'s `Display`, not
//! as a decimal, because the repository's determinism discipline requires two
//! decodes of the same record to produce identical text — and `NaN`, `-0.0` and
//! `0.1` do not all round-trip through every decimal formatter identically.
//! `Display` therefore spells a float as its IEEE-754 bits.

use core::fmt;

/// The declared kind of a field in a flat layout table.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum FieldKind {
    /// A `u32`: an enum value, a count, a flag word or a resource-reference key.
    U32,
    /// An `f32` tuning value.
    F32,
}

impl FieldKind {
    /// The canonical spelling used in claims and dumps.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::U32 => "u32",
            Self::F32 => "f32",
        }
    }

    /// The byte width of one field of this kind.
    pub const fn width(self) -> usize {
        4
    }
}

/// One decoded scalar value.
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Scalar {
    /// An unsigned 32-bit field.
    U32(u32),
    /// A signed 32-bit field.
    I32(i32),
    /// A 32-bit float field.
    F32(f32),
    /// A one-byte boolean field, kept as the byte that was read.
    ///
    /// Kept as `u8` rather than collapsed to `bool` on purpose: the Python
    /// oracle `tools/spore/cellres/cell.py` requires these bytes to be `0` or
    /// `1`, and converting to `bool` in the decoder destroys the very thing the
    /// invariant checks. See the crate documentation, "Where the two oracles
    /// disagree".
    U8(u8),
}

impl Scalar {
    /// The value as a `u32` when it is one of the unsigned shapes.
    pub const fn as_u32(self) -> Option<u32> {
        match self {
            Self::U32(v) => Some(v),
            Self::U8(v) => Some(v as u32),
            Self::I32(_) | Self::F32(_) => None,
        }
    }

    /// The value as an `i32` when it is one of the signed shapes.
    pub const fn as_i32(self) -> Option<i32> {
        match self {
            Self::I32(v) => Some(v),
            Self::U8(v) => Some(v as i32),
            Self::U32(_) | Self::F32(_) => None,
        }
    }

    /// The value as an `f32` when it is the float shape.
    pub const fn as_f32(self) -> Option<f32> {
        match self {
            Self::F32(v) => Some(v),
            Self::U32(_) | Self::I32(_) | Self::U8(_) => None,
        }
    }

    /// The value as the `u8` boolean byte when it is that shape.
    pub const fn as_u8(self) -> Option<u8> {
        match self {
            Self::U8(v) => Some(v),
            Self::U32(_) | Self::I32(_) | Self::F32(_) => None,
        }
    }

    /// Whether this scalar is the float `NaN`.
    ///
    /// Written as a bit test rather than `v != v` so it is a total predicate and
    /// reads the same as the oracles' `v != v` check without relying on the
    /// float comparison operators not being optimised into an assumption.
    pub const fn is_nan(self) -> bool {
        match self {
            Self::F32(v) => v.to_bits() & 0x7fff_ffff > 0x7f80_0000,
            _ => false,
        }
    }

    /// Whether this scalar is finite (`true` for every non-float shape).
    pub const fn is_finite(self) -> bool {
        match self {
            Self::F32(v) => v.to_bits() & 0x7f80_0000 != 0x7f80_0000,
            _ => true,
        }
    }
}

impl fmt::Display for Scalar {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::U32(v) => write!(f, "0x{v:08x}"),
            Self::I32(v) => write!(f, "{v}"),
            Self::F32(v) => write!(f, "f0x{:08x}", v.to_bits()),
            Self::U8(v) => write!(f, "{v}"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_float_prints_as_its_bits_so_two_decodes_print_the_same_text() {
        assert_eq!(Scalar::F32(1.0).to_string(), "f0x3f800000");
        assert_eq!(Scalar::F32(f32::NAN).to_string(), "f0x7fc00000");
        assert_eq!(Scalar::F32(-0.0).to_string(), "f0x80000000");
        assert_eq!(Scalar::U32(0x1234_5678).to_string(), "0x12345678");
        assert_eq!(Scalar::I32(-1).to_string(), "-1");
        assert_eq!(Scalar::U8(1).to_string(), "1");
    }

    #[test]
    fn nan_and_infinity_are_distinguished_from_a_large_finite_value() {
        assert!(Scalar::F32(f32::NAN).is_nan());
        assert!(!Scalar::F32(f32::INFINITY).is_nan());
        assert!(!Scalar::F32(-1.0e30).is_nan());
        assert!(!Scalar::F32(f32::INFINITY).is_finite());
        assert!(Scalar::F32(1.0e30).is_finite());
        assert!(Scalar::U32(0xFFFF_FFFF).is_finite());
        assert!(!Scalar::U32(0xFFFF_FFFF).is_nan());
    }

    #[test]
    fn accessors_refuse_a_shape_mismatch_rather_than_coercing() {
        assert_eq!(Scalar::U8(7).as_u32(), Some(7));
        assert_eq!(Scalar::U8(7).as_i32(), Some(7));
        assert_eq!(Scalar::U8(7).as_u8(), Some(7));
        assert_eq!(Scalar::U8(7).as_f32(), None);
        assert_eq!(Scalar::F32(1.0).as_u32(), None);
        assert_eq!(Scalar::I32(1).as_f32(), None);
        assert_eq!(Scalar::U32(1).as_u8(), None);
    }
}
