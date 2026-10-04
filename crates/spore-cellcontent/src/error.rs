//! Typed failures of cell-content decoding and of cross-record reference
//! resolution.
//!
//! Two families, because two different questions fail for two different reasons:
//!
//! * [`CellContentError`] — *these bytes are not this record*. Every variant
//!   names the record type id and the numbers needed to find the offending
//!   field, because the failure a caller meets is almost always "this record
//!   claims to hold 24 entries" or "this record is 795 bytes", and neither is
//!   actionable without the arithmetic.
//! * [`CellReferenceError`] — *this record is fine but points at something that
//!   is not here*. Each variant names the source key, the reference field and
//!   the entry index.
//!
//! # A missing target is not a zero target
//!
//! [`CellReferenceError::NotFound`] exists so that a reference which resolves to
//! nothing can be reported as a **non-finding** rather than collapsed into
//! "instance 0" or "type 0". There is a third distinction here that is easy to
//! lose and is preserved deliberately: a reference whose *type word* is unknown
//! ([`CellReferenceError::UnknownTypeWord`]) and one that points outside this
//! record family ([`CellReferenceError::OutsideFamily`]) are neither "found" nor
//! "not found" — we do not know what to look for. Collapsing either into
//! `NotFound` would assert that a search happened and came up empty.
//!
//! # `PartialEq`, not `Eq`
//!
//! Several variants carry `f32`-derived observations through
//! [`crate::issue::CellIssue`], where `NaN != NaN` is the point. This type does
//! derive `Eq` because nothing here holds a float.

use spore_core::ResourceKey;
use thiserror::Error;

use crate::reference::CellReferenceField;

/// Every way decoding a cell-content record can fail.
#[derive(Debug, Clone, PartialEq, Eq, Error)]
pub enum CellContentError {
    /// The type id is not one of the twelve this crate decodes.
    ///
    /// This is the *loader* boundary: a package holds thousands of record types
    /// and exactly twelve of them are cell-stage gameplay configuration. Naming
    /// the id is the whole point; refusing by name is what stops a `gmdl` from
    /// being handed to the globals decoder and reported as plausible garbage.
    #[error("cell content: unsupported record type 0x{type_id:08x}")]
    UnsupportedType {
        /// The type word that was refused.
        type_id: u32,
    },

    /// A fixed-extent record did not have exactly its documented length.
    ///
    /// Applies to `globals` (276 bytes), `cell` (796) and `powers` (8). Both
    /// the C++ reference and the Python oracles compare against the constant
    /// rather than against a minimum, so one byte short is as much an error as
    /// one byte long.
    #[error(
        "cell content: 0x{type_id:08x} is {actual} bytes, which is not the fixed extent \
         {expected}"
    )]
    ExtentMismatch {
        /// The record type word.
        type_id: u32,
        /// How many bytes were supplied.
        actual: usize,
        /// The documented extent.
        expected: usize,
    },

    /// The record is shorter than its own header.
    ///
    /// A counted record cannot be read at all below its header length, so this
    /// is checked before the count is trusted. Nothing else can be reported
    /// yet: the count does not exist in the buffer.
    #[error(
        "cell content: 0x{type_id:08x} is {actual} bytes, shorter than its {minimum}-byte header"
    )]
    HeaderTooSmall {
        /// The record type word.
        type_id: u32,
        /// How many bytes were supplied.
        actual: usize,
        /// The header length.
        minimum: usize,
    },

    /// The header count is negative.
    ///
    /// Refused by name. Reinterpreting it as an unsigned length is how a corrupt
    /// count turns into a multi-gigabyte span request.
    #[error("cell content: 0x{type_id:08x} header field `{field}` is {count}, which is negative")]
    NegativeCount {
        /// The record type word.
        type_id: u32,
        /// Which header field held the count.
        field: &'static str,
        /// The raw signed count.
        count: i32,
    },

    /// The declared entries do not fit in the remaining bytes.
    #[error(
        "cell content: 0x{type_id:08x} header field `{field}` claims {count} entries of \
         {item_size} bytes, needing {needed} bytes, but only {available} remain"
    )]
    CountTooLarge {
        /// The record type word.
        type_id: u32,
        /// Which header field held the count.
        field: &'static str,
        /// The count read from the header.
        count: u32,
        /// The entry stride this build decodes.
        item_size: usize,
        /// `header + count * item_size`.
        needed: usize,
        /// `size - header`.
        available: usize,
    },

    /// The declared entries end before the record does.
    ///
    /// Only reachable under a [`crate::reader::SpanRule::ExactFit`] record, so
    /// this is the "trailing bytes are a hard error" rule made explicit.
    ///
    /// There is deliberately **no** `item_size` here, unlike
    /// [`Self::CountTooLarge`]: what a remainder means is already fully
    /// described by `count`, `field` and `trailing`, and `world` — whose two
    /// counts share one span — has no single item size to report. Reporting a
    /// made-up stride would be worse than reporting none.
    #[error(
        "cell content: 0x{type_id:08x} header field `{field}` declares {count} entries, \
         leaving {trailing} unexplained trailing bytes"
    )]
    TrailingBytes {
        /// The record type word.
        type_id: u32,
        /// Which header field held the count.
        field: &'static str,
        /// The count the header declared. For a two-count record this is the
        /// sum of both.
        count: u32,
        /// `size - header - count * item_size`.
        trailing: usize,
    },
}

impl CellContentError {
    /// A coarse tag for callers that branch on the failure without matching
    /// every arm.
    pub const fn kind(&self) -> CellContentErrorKind {
        match self {
            Self::UnsupportedType { .. } => CellContentErrorKind::UnsupportedType,
            Self::ExtentMismatch { .. } => CellContentErrorKind::ExtentMismatch,
            Self::HeaderTooSmall { .. } => CellContentErrorKind::HeaderTooSmall,
            Self::NegativeCount { .. }
            | Self::CountTooLarge { .. }
            | Self::TrailingBytes { .. } => CellContentErrorKind::Extent,
        }
    }

    /// The record type word the failure is about.
    pub const fn type_id(&self) -> u32 {
        match self {
            Self::UnsupportedType { type_id }
            | Self::ExtentMismatch { type_id, .. }
            | Self::HeaderTooSmall { type_id, .. }
            | Self::NegativeCount { type_id, .. }
            | Self::CountTooLarge { type_id, .. }
            | Self::TrailingBytes { type_id, .. } => *type_id,
        }
    }
}

/// A coarse classification of [`CellContentError`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum CellContentErrorKind {
    /// Not one of the twelve record types.
    UnsupportedType,
    /// A fixed-extent record was not its documented length.
    ExtentMismatch,
    /// Shorter than the record's own header.
    HeaderTooSmall,
    /// The declared count does not agree with the record length.
    Extent,
}

/// Every way resolving a cell-content cross-record reference can fail.
#[derive(Debug, Clone, PartialEq, Eq, Error)]
pub enum CellReferenceError {
    /// The source record's key is not a complete `(type, group, instance)`
    /// triple, so it names no record to point *from*.
    #[error("cell reference: source key `{key}` is incomplete, so it names no record")]
    IncompleteSource {
        /// The offending source key.
        key: ResourceKey,
    },

    /// The caller asked about a reference on a *different* record than the one
    /// holding the reference list.
    ///
    /// The second key is spelled `claimed` rather than `source` because
    /// `thiserror` treats a field called `source` as the error's cause and then
    /// requires it to implement [`std::error::Error`]. A `ResourceKey` does not
    /// and should not.
    #[error(
        "cell reference: asked about a reference on `{key}` but the reference names `{claimed}`"
    )]
    SourceMismatch {
        /// The key of the record actually supplied.
        key: ResourceKey,
        /// The source key the reference claims.
        claimed: ResourceKey,
    },

    /// The caller asked about a reference that the record does not emit at
    /// `(field, index, instance)`.
    ///
    /// This is the guard that makes [`CellContentRecord::references`] the single
    /// authority: a hand-built [`CellReference`](crate::reference::CellReference)
    /// that the record does not actually produce is refused rather than resolved.
    #[error(
        "cell reference: `{key}` has no `{field}` reference at index {index} to instance \
         0x{instance:08x}"
    )]
    NotAReference {
        /// The record that was asked about.
        key: ResourceKey,
        /// The claimed reference field.
        field: CellReferenceField,
        /// The claimed entry index.
        index: usize,
        /// The claimed target instance id.
        instance: u32,
    },

    /// The field stores an instance id but **no type word**, so the reference
    /// names no type of record and this crate cannot look it up.
    ///
    /// **This is a non-finding, not a failure to find.** The C++ reference
    /// carries these fields with `ResourceKey::kWildcard` as the type word, which
    /// is an explicit statement that the record does not say what it points at.
    /// Ten of the twenty-six reference fields are in this state: `cell.break`,
    /// `cell.pieces`, `cell.leak`, `cell.expel`, `cell.explosionTable`,
    /// `cell.poison`, both `cell.ai.*Output` fields, the five
    /// `structure` header effect slots, and `structure.attachment.effect`.
    #[error(
        "cell reference: `{key}` field `{field}` at index {index} holds instance \
         0x{instance:08x} but stores no type word, so it names no record type to look up"
    )]
    UnknownTypeWord {
        /// The record holding the reference.
        key: ResourceKey,
        /// The reference field.
        field: CellReferenceField,
        /// The entry index, or 0 for a record-level field.
        index: usize,
        /// The stored instance id.
        instance: u32,
    },

    /// The field names a record type that is **not** one of this family's
    /// twelve, so it points at a different subsystem entirely.
    ///
    /// One field does this today: `world.advect.advectID` names type
    /// `0x04805684`, a flow-field resource. The id is graded
    /// [`spore_core::EvidenceLevel::Inferred`] — it comes from the C++
    /// reference's own annotation and no oracle in `tools/spore/cellres/`
    /// resolves it — but whatever it is, it is not a cell-content record, so
    /// this catalogue can never answer it.
    #[error(
        "cell reference: `{key}` field `{field}` at index {index} names type 0x{type_id:08x}, \
         which is outside the twelve cell-content record types"
    )]
    OutsideFamily {
        /// The record holding the reference.
        key: ResourceKey,
        /// The reference field.
        field: CellReferenceField,
        /// The entry index.
        index: usize,
        /// The referenced type word.
        type_id: u32,
    },

    /// The caller asked for a target type that the field does not declare.
    ///
    /// The two type words are named for **who said what**: `field_type` is what
    /// the record itself declares, `requested_type` is what the caller passed.
    /// The record is the authority; the caller's value only ever narrows.
    #[error(
        "cell reference: `{key}` field `{field}` at index {index} declares a \
         0x{field_type:08x} target, not the requested 0x{requested_type:08x}"
    )]
    TargetTypeMismatch {
        /// The record holding the reference.
        key: ResourceKey,
        /// The reference field.
        field: CellReferenceField,
        /// The entry index.
        index: usize,
        /// The type word the caller asked for.
        requested_type: u32,
        /// The type word the field declares.
        field_type: u32,
    },

    /// No record in the catalogue has that `(type, instance)` pair.
    ///
    /// The searched catalogue's type and instance are named so a caller can say
    /// *what it looked for* and not only that it failed.
    #[error(
        "cell reference: `{key}` field `{field}` at index {index} wants instance \
         0x{instance:08x} of type 0x{type_id:08x}, which the catalogue does not hold"
    )]
    NotFound {
        /// The record holding the reference.
        key: ResourceKey,
        /// The reference field.
        field: CellReferenceField,
        /// The entry index.
        index: usize,
        /// The referenced type word.
        type_id: u32,
        /// The referenced instance id.
        instance: u32,
    },

    /// More than one catalogue record shares that `(type, instance)` pair.
    ///
    /// Possible because a reference carries no group id: `cell.structure` says
    /// "some 0x4B9EF6DC instance 0x…", and two groups may both hold that
    /// instance. Picking the first would be an invention, so it is refused.
    #[error(
        "cell reference: `{key}` field `{field}` at index {index} wants instance \
         0x{instance:08x} of type 0x{type_id:08x}, which {candidates} catalogue records share"
    )]
    Ambiguous {
        /// The record holding the reference.
        key: ResourceKey,
        /// The reference field.
        field: CellReferenceField,
        /// The entry index.
        index: usize,
        /// The referenced type word.
        type_id: u32,
        /// The referenced instance id.
        instance: u32,
        /// How many records matched.
        candidates: usize,
    },
}

impl CellReferenceError {
    /// The record the failing reference belongs to.
    pub fn key(&self) -> ResourceKey {
        match self {
            Self::IncompleteSource { key } => *key,
            Self::SourceMismatch { key, .. }
            | Self::NotAReference { key, .. }
            | Self::UnknownTypeWord { key, .. }
            | Self::OutsideFamily { key, .. }
            | Self::TargetTypeMismatch { key, .. }
            | Self::NotFound { key, .. }
            | Self::Ambiguous { key, .. } => *key,
        }
    }

    /// Whether this failure means *"we do not know what to look for"* rather
    /// than *"we looked and it is not there"*.
    ///
    /// The distinction matters for a caller that wants to report coverage: a
    /// `NotFound` is evidence about the catalogue, an `UnknownTypeWord` is
    /// evidence about the format.
    pub const fn is_non_finding(&self) -> bool {
        matches!(
            self,
            Self::UnknownTypeWord { .. } | Self::OutsideFamily { .. }
        )
    }
}
