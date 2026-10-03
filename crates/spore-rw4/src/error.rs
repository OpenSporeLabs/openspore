//! Typed failures for the RW4 section-directory walker.
//!
//! Every variant here is **reachable**: `parse` has a test for each one, either
//! against a mutated fixture or against a record emitted by the synthetic
//! builder in `crate::tests`. Where the C++ reference merges two conditions
//! into one message, this crate splits them into distinct variants — see the
//! notes on [`Rw4Error::SectionInfoPointerOutOfRange`] and
//! [`Rw4Error::SectionTableOverrunsRecord`].
//!
//! The C++ additionally rejects an *incomplete* record
//! (`Rw4::complete() == false`) as a parse failure. This crate deliberately
//! does **not**: completeness is a property reported by
//! [`crate::Rw4::is_complete`], not an error. See the crate-level docs.

use thiserror::Error;

/// Every way [`crate::parse`] can refuse an RW4 record.
///
/// The variants are ordered the way `parse` checks them, so the first `Err`
/// from a malformed record is also the earliest structural problem.
#[derive(Debug, Clone, PartialEq, Eq, Error)]
pub enum Rw4Error {
    /// The record is shorter than the fixed RW4 prefix requires.
    ///
    /// `needed` is the smallest length that would make the offending read
    /// well-defined: for the up-front check it is
    /// [`crate::MIN_RECORD_SIZE`] (0x98 + 0x1C = 180 bytes — the 0x98-byte
    /// header plus the 0x1C-byte SectionManifest that starts it); for a read
    /// that a *prior* bounds check already guaranteed, it is the first
    /// unreachable byte. The second case is defensive only and is not
    /// reachable through `parse`.
    #[error("rw4: record too short: {len} bytes, need at least {needed}")]
    TooShort {
        /// Length of the buffer handed to `parse`.
        len: usize,
        /// Minimum length that would satisfy the failing read.
        needed: usize,
    },

    /// A magic byte does not match [`crate::MAGIC`].
    ///
    /// The first differing byte is reported so a truncated or byte-swapped
    /// record is diagnosable without re-diffing 28 bytes by hand.
    #[error("rw4: bad magic at byte {offset}: found 0x{found:02x}, want 0x{want:02x}")]
    BadMagic {
        /// Index of the first mismatching byte within the 28-byte magic.
        offset: usize,
        /// Byte actually present.
        found: u8,
        /// Byte [`crate::MAGIC`] requires at that index.
        want: u8,
    },

    /// `file_type` at `0x1C` is none of Model / Texture / Special.
    #[error("rw4: unknown file type 0x{file_type:x}")]
    BadFileType {
        /// The rejected raw `file_type` word.
        file_type: u32,
    },

    /// The SectionManifest at `0x98` does not carry type code `0x10004`.
    ///
    /// The C++ has a *separate* `"record too small for manifest"` check here.
    /// That check can never fire in this crate because
    /// [`crate::Rw4Error::TooShort`] already guarantees the record is at least
    /// [`crate::MIN_RECORD_SIZE`] bytes long, which covers the manifest's
    /// `0x1C` bytes — so there is deliberately **no** `ManifestTooShort`
    /// variant rather than a variant that cannot fire.
    #[error("rw4: manifest type code 0x{found:x} != 0x10004")]
    ManifestTypeCode {
        /// Type code found at `0x98`.
        found: u32,
    },

    /// The SectionTypes block does not carry type code `0x10005`.
    #[error("rw4: section-types type code 0x{found:x} != 0x10005")]
    SectionTypesTypeCode {
        /// Type code found at `0x98 + o1`.
        found: u32,
    },

    /// `section_info_pointer` at `0x30` points past the end of the record.
    ///
    /// The C++ reports both this condition *and* a row-count overrun through
    /// one `"section-info table out of bounds"` string. They are genuinely
    /// different facts — one is a bad base pointer, the other a bad count — so
    /// this crate keeps them apart: see also
    /// [`Rw4Error::SectionTableOverrunsRecord`].
    #[error("rw4: section-info pointer 0x{ptr:x} is past the end of the 0x{len:x}-byte record")]
    SectionInfoPointerOutOfRange {
        /// The offending base pointer.
        ptr: u32,
        /// Length of the record.
        len: usize,
    },

    /// `section_count` rows of 24 bytes do not fit between
    /// `section_info_pointer` and the end of the record.
    #[error(
        "rw4: section table overruns record: {count} rows at 0x{ptr:x} need {needed} bytes, \
         {avail} available"
    )]
    SectionTableOverrunsRecord {
        /// `section_count` as declared in the header.
        count: u32,
        /// `section_info_pointer` as declared in the header.
        ptr: u32,
        /// `count * 24`, computed in 64-bit so it cannot wrap.
        needed: u64,
        /// `len - ptr`, computed in 64-bit.
        avail: u64,
    },

    /// The manifest-relative offset `o1` places the SectionTypes block outside
    /// the record.
    ///
    /// `o1` is measured **from the manifest at `0x98`**, not from the start of
    /// the record, so the absolute location is `0x98 + o1`.
    #[error(
        "rw4: manifest-relative offset 0x{offset:x} puts SectionTypes at 0x{absolute:x}, \
         past the end of the 0x{len:x}-byte record"
    )]
    ManifestRelativeOffsetOutOfRange {
        /// The manifest-relative offset as stored at `0x98 + 0x0C`.
        offset: u32,
        /// `0x98 + offset`, in 64-bit.
        absolute: u64,
        /// Length of the record.
        len: usize,
    },

    /// The SectionTypes block's declared type-code count runs past the record.
    #[error(
        "rw4: SectionTypes block at 0x{base:x} overruns record: {count} codes need {needed} \
         bytes, {avail} available"
    )]
    TypesBlockOutOfRange {
        /// `n_types` as declared at `0x98 + o1 + 0x04`.
        count: u32,
        /// Absolute offset of the SectionTypes block.
        base: u64,
        /// `base + 8 + count * 4`, in 64-bit.
        needed: u64,
        /// `len - base`, in 64-bit.
        avail: u64,
    },

    /// A BaseResource section's adjusted data address exceeds `u32::MAX`.
    ///
    /// Only BaseResource rows are adjusted (`data_pointer + buffer_pointer`), so
    /// only they can overflow.
    #[error(
        "rw4: section {index} data address overflows u32: 0x{data_pointer:x} + \
         0x{buffer_pointer:x}"
    )]
    AddressAdjustmentOverflow {
        /// Index of the offending section row.
        index: usize,
        /// Raw `data_pointer` from the row.
        data_pointer: u32,
        /// `buffer_pointer` from the header.
        buffer_pointer: u32,
    },

    /// `buffer_pointer` / `buffer_size` do not describe a sub-range of the
    /// record.
    ///
    /// Checked as `buffer_pointer <= len` and `buffer_size <= len -
    /// buffer_pointer`, both in 64-bit so the subtraction cannot wrap.
    #[error(
        "rw4: arena out of bounds: base 0x{base:x} size 0x{size:x} does not fit the \
         0x{len:x}-byte record"
    )]
    ArenaBoundsViolation {
        /// `buffer_pointer` from the header.
        base: u32,
        /// `buffer_size` from the header.
        size: u32,
        /// Length of the record.
        len: usize,
    },

    /// A section row's `type_code_index` is not a valid index into the
    /// SectionTypes table.
    ///
    /// This check has **no counterpart in either reference**: the C++
    /// (`inKnownSet` is only consulted for counting) and the Python oracle
    /// both read `tcIndex` and then ignore it, because the row also carries its
    /// own `type_code` word. This crate validates it anyway — the row's index
    /// pointing outside a table the record itself declares is a structural
    /// defect, not an unknown type code. The check measured clean over all
    /// 1,131 real RW4 records in `Spore_Content.package` (5,192 section rows,
    /// zero violations), so it does not refuse anything the corpus contains.
    #[error("rw4: section {index} type-code index {index_value} is outside the {count}-entry type table")]
    BadSectionTypeCodeIndex {
        /// Index of the offending section row.
        index: usize,
        /// `type_code_index` as stored at `row + 0x10`.
        index_value: i32,
        /// Number of entries in the SectionTypes table.
        count: usize,
    },
}
