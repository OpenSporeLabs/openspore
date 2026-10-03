//! RenderWare 4 (RW4) **section directory** walker — the Rust counterpart of
//! `src/assets/Rw4.cpp`.
//!
//! # What this crate is (and is not)
//!
//! An RW4 record (`type_id` `0x2F4E_681B`) is a RenderWare 4 container: a
//! fixed header, a `SectionManifest`, a `SectionTypes` block naming the
//! section types in use, an array of 24-byte section rows, and an arena holding
//! the section payloads. This crate decodes the **directory only** — header,
//! manifest, type-code table, section rows.
//!
//! **Section payload decoding is out of scope here on purpose.** No raster
//! texel layout, no mesh vertex/index layout, no skeleton, no animation track.
//! Those belong to their own crates. A reader who feels the urge to open
//! `data_address..data_address + size` here should not: the section directory
//! has no opinion about what a payload means, and inventing one in the walker
//! is how a directory starts lying.
//!
//! # Why a `png`-named record lands here
//!
//! In Spore, records named `png` are **RW4 containers, not raw PNG** (verified
//! 60/60 on sampled records). So this crate is directly on the path to
//! PNG/JPEG decode: the section directory tells you which record holds the
//! raster and where its bytes start. Getting that directory right is the
//! prerequisite; the codec is the next crate.
//!
//! # Layout (little-endian throughout)
//!
//! ## Magic — 28 bytes, byte-exact
//!
//! ```text
//! 89 52 57 34 77 33 32 00  0D 0A 1A 0A  00 20 04 00
//! 34 35 34 00 30 30 30 00  00 00 00 00
//! ```
//!
//! **Warning — `src/assets/Rw4.hpp` line 7 carries a WRONG ASCII literal for
//! this constant.** It renders bytes 12..15 as `" 4\x00"`, i.e. `0x20 0x34 0x00`
//! , while the real bytes are `00 20 04 00`. Both the C++ array in `Rw4.cpp`
//! and `rw4.py` agree on `00 20 04 00`, and so does every real record. Do not
//! transcribe from that header comment; this crate uses the byte array for
//! exactly that reason.
//!
//! ## Header — absolute offsets
//!
//! | Offset | Field |
//! |---|---|
//! | `0x00` | `magic[28]` |
//! | `0x1C` | `file_type` — must be 1 (Model), `0x04000000` (Texture) or `0xCAFED00D` (Special) |
//! | `0x20` | `object_count` (recorded, **not** validated) |
//! | `0x24` | `section_count` |
//! | `0x28` | `unknown_28` |
//! | `0x2C` | `unknown_2c` |
//! | `0x30` | `section_info_pointer` |
//! | `0x34` | `unknown_34` |
//! | `0x44` | `buffer_pointer` (arena base) |
//! | `0x48` | `unknown_48` |
//! | `0x4C` | `buffer_size` |
//!
//! ## SectionManifest — fixed at `0x98`, `0x1C` bytes
//!
//! | Rel | Field |
//! |---|---|
//! | `+0x00` | u32 type code, must be `0x10004` |
//! | `+0x0C` | u32 `o1` — **manifest-RELATIVE** offset to the SectionTypes block |
//! | `+0x04`, `+0x08`, `+0x10`, `+0x14`, `+0x18` | not read |
//!
//! `o1` is relative to the manifest, so the SectionTypes block lives at
//! **`0x98 + o1`** and *not* at `o1`. A parser that adds nothing reads the
//! wrong words, gets a zero type code, and reports a plausible-looking
//! "types typecode 0x0" instead of admitting the offset is relative. On the
//! real corpus `o1` is always `0x1C`, so the mistake is *invisible* until you
//! meet a record with padding — which is why the synthetic builder emits one.
//!
//! ## SectionTypes — at `0x98 + o1`
//!
//! | Rel | Field |
//! |---|---|
//! | `+0x00` | u32 type code, must be `0x10005` |
//! | `+0x04` | u32 `n_types` |
//! | `+0x08` | `n_types` × u32 type codes |
//!
//! ## Section rows — 24-byte stride, at `section_info_pointer`
//!
//! | Rel | Type | Field |
//! |---|---|---|
//! | `+0x00` | u32 | `data_pointer` (raw, as stored) |
//! | `+0x04` | u32 | `unknown_04` |
//! | `+0x08` | **i32** | `size` |
//! | `+0x0C` | **i32** | `align` |
//! | `+0x10` | **i32** | `type_code_index` |
//! | `+0x14` | **i32** (stored as u32) | `type_code` |
//!
//! # The one non-obvious rule: address adjustment
//!
//! ```text
//! data_address = if type_code == 0x10030 /* BaseResource */ { data_pointer + buffer_pointer }
//!                else                      { data_pointer }
//! ```
//!
//! A **BaseResource** section's `data_pointer` is an offset **relative to the
//! arena base** (`buffer_pointer`); every other section's is an **absolute**
//! offset into the record. Both are stored in the same column of the same
//! table, which is why the rule is easy to miss and why the fixture asserts
//! the two cases side by side. Measured on the real corpus: the BaseResource
//! row in `mini_rw4.rw4` stores `0x00` and resolves to `0x138`; the Raster row
//! next to it stores `0x144` and resolves to `0x144`.
//!
//! "Simplifying" this to always adding, or always not adding, corrupts every
//! section of one kind. It is not a special case to be tidied away.
//!
//! # Deliberate divergences from the C++ reference
//!
//! 1. **Completeness is not a parse failure.** The C++ ends `parseRw4` with
//!    `if (!parsed.complete()) return false;`. This crate returns `Ok` and lets
//!    the caller read [`Rw4::is_complete`]. A truncated-payload record is a
//!    parseable *directory* describing sections that do not fit; refusing to
//!    produce the directory is what loses the diagnosis. Callers that want the
//!    C++ behaviour check `is_complete()` themselves.
//! 2. **`type_code_index` is validated.** The C++ reads it and ignores it (the
//!    row already carries `type_code`). See
//!    [`Rw4Error::BadSectionTypeCodeIndex`] for the measurement showing this
//!    refuses nothing in the real corpus.
//! 3. **Errors are typed and split per condition**; the C++ folds several into
//!    one string.
//!
//! # Oracle compatibility
//!
//! [`Rw4::describe`] reproduces `tools/spore/rw4/rw4.py::describe`
//! **character for character**, which is what lets `tests/test_rw4.py` diff the
//! two walkers over all 1,131 real records. That means lowercase hex, no zero
//! padding, decimal `obj`/`sec`/`buf`/`s`, and a ` | `-separated section list.

#![forbid(unsafe_code)]
#![warn(missing_docs, missing_debug_implementations)]

mod error;
mod type_codes;

use core::fmt;

pub use error::Rw4Error;
pub use type_codes::{
    cpp_type_name, known_type_code, python_type_name, CPP_TYPE_CODES, CPP_UNNAMED_TYPE_CODES,
    PYTHON_TYPE_CODES, SPORE_ONLY_TYPE_CODES,
};

/// DBPF record type id for an RW4 container.
///
/// Spore's `png`/`plt` records carry this type id; they are RW4 containers, not
/// raw PNG.
pub const RW4_TYPE: u32 = spore_core::record::type_id::RW4;

/// The 28-byte RW4 magic, byte-exact.
///
/// ```text
/// 89 52 57 34 77 33 32 00  0D 0A 1A 0A  00 20 04 00
/// 34 35 34 00 30 30 30 00  00 00 00 00
/// ```
///
/// **Bytes 12..15 are `00 20 04 00`.** `src/assets/Rw4.hpp`'s ASCII comment
/// spells them `" 4\0"` and is wrong; see the crate docs. Do not transcribe
/// the magic from that header comment.
pub const MAGIC: [u8; 28] = [
    0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32, 0x00, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x20, 0x04, 0x00,
    0x34, 0x35, 0x34, 0x00, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
];

/// Length of [`MAGIC`], as a `usize`.
pub const MAGIC_LEN: usize = MAGIC.len();

/// Offset of the [`FileType`] discriminator in the header.
pub const FILE_TYPE_OFFSET: usize = 0x1C;

/// Offset of the `object_count` word in the header.
pub const OBJECT_COUNT_OFFSET: usize = 0x20;

/// Offset of the `section_count` word in the header.
pub const SECTION_COUNT_OFFSET: usize = 0x24;

/// Offset of the `section_info_pointer` word in the header.
pub const SECTION_INFO_POINTER_OFFSET: usize = 0x30;

/// Offset of the `buffer_pointer` (arena base) word in the header.
pub const BUFFER_POINTER_OFFSET: usize = 0x44;

/// Offset of the `buffer_size` word in the header.
pub const BUFFER_SIZE_OFFSET: usize = 0x4C;

/// Fixed offset of the `SectionManifest`, immediately after the header.
pub const MANIFEST_OFFSET: usize = 0x98;

/// Size of the `SectionManifest` structure.
pub const MANIFEST_SIZE: usize = 0x1C;

/// Relative offset of the SectionTypes pointer `o1` inside the manifest.
pub const MANIFEST_TYPES_OFFSET_OFFSET: usize = 0x0C;

/// Type code a `SectionManifest` must carry.
pub const MANIFEST_TC: u32 = 0x10004;

/// Type code a `SectionTypes` block must carry.
pub const TYPES_TC: u32 = 0x10005;

/// Type code of a `BaseResource` section — **the only one whose
/// `data_pointer` is arena-relative**.
///
/// See the crate docs: this single asymmetry is the one rule a future reader
/// will try to "simplify" away.
pub const BASE_RESOURCE_TC: u32 = 0x10030;

/// Stride of one section-info row, in bytes.
pub const SECTION_ROW_SIZE: usize = 24;

/// Smallest record length for which a *successful* parse is possible:
/// the `0x98`-byte header plus the `0x1C`-byte manifest that starts at `0x98`.
pub const MIN_RECORD_SIZE: usize = MANIFEST_OFFSET + MANIFEST_SIZE;

/// The three `file_type` values an RW4 header may carry.
///
/// A record whose `file_type` is anything else is refused outright, so
/// [`FileType::Unknown`] cannot be produced by [`parse`] — it exists so callers
/// can classify a word they read elsewhere without writing the match themselves.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum FileType {
    /// `1` — model container (meshes, skeletons, keyframe anims).
    Model,
    /// `0x04000000` — texture container.
    Texture,
    /// `0xCAFED00D` — special container. Every one of the 1,131 RW4 records in
    /// `Spore_Content.package` is `Special`.
    Special,
    /// A word that is none of the above. Never produced by [`parse`].
    Unknown(u32),
}

impl FileType {
    /// Raw word for [`FileType::Model`].
    pub const MODEL: u32 = 1;
    /// Raw word for [`FileType::Texture`].
    pub const TEXTURE: u32 = 0x0400_0000;
    /// Raw word for [`FileType::Special`].
    pub const SPECIAL: u32 = 0xCAFE_D00D;

    /// Classify a raw `file_type` word.
    ///
    /// Total: unlike [`parse`], this never fails — an unrecognised word becomes
    /// [`FileType::Unknown`] rather than an error.
    #[must_use]
    pub const fn from_raw(raw: u32) -> Self {
        match raw {
            Self::MODEL => Self::Model,
            Self::TEXTURE => Self::Texture,
            Self::SPECIAL => Self::Special,
            other => Self::Unknown(other),
        }
    }

    /// The raw word this variant stands for.
    #[must_use]
    pub const fn raw(self) -> u32 {
        match self {
            Self::Model => Self::MODEL,
            Self::Texture => Self::TEXTURE,
            Self::Special => Self::SPECIAL,
            Self::Unknown(raw) => raw,
        }
    }

    /// True for the three variants [`parse`] accepts.
    #[must_use]
    pub const fn is_known(self) -> bool {
        !matches!(self, Self::Unknown(_))
    }
}

impl fmt::Display for FileType {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Model => f.write_str("MODEL"),
            Self::Texture => f.write_str("TEXTURE"),
            Self::Special => f.write_str("SPECIAL"),
            Self::Unknown(raw) => write!(f, "0x{raw:08x}"),
        }
    }
}

/// One 24-byte section-info row, with its **adjusted** data address.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Section {
    /// Raw `data_pointer` exactly as stored at `row + 0x00`.
    ///
    /// For a [`BASE_RESOURCE_TC`] section this is an *arena-relative* offset;
    /// for every other type it is an absolute record offset. Read
    /// [`Section::data_address`] instead of computing from this.
    pub data_pointer: u32,
    /// Uninterpreted word at `row + 0x04` (frequently 0 or 1).
    pub unknown_04: u32,
    /// Signed payload size at `row + 0x08`. Negative values are legal to store
    /// and make [`Rw4::is_complete`] report `false`.
    pub size: i32,
    /// Signed alignment at `row + 0x0C`.
    pub align: i32,
    /// Index into [`Rw4::type_codes`], as stored at `row + 0x10`.
    ///
    /// The row *also* carries its own [`Section::type_code`], which is what the
    /// reference walkers use; this index is validated by [`parse`] but never
    /// needed to resolve the type.
    pub type_code_index: i32,
    /// Section type code. Stored as `i32` in the record, kept here as `u32` so
    /// hex formatting matches both references byte for byte.
    pub type_code: u32,
    /// **Adjusted** absolute data address:
    /// `data_pointer + buffer_pointer` for a [`BASE_RESOURCE_TC`] section,
    /// `data_pointer` otherwise. See the crate docs before changing this.
    pub data_address: u32,
    /// Absolute offset of this row's 24 bytes within the record. Diagnostics
    /// only — no consumer needs it to parse.
    pub row_offset: usize,
}

impl Section {
    /// End of the section payload, `data_address + size`, in 64-bit so a large
    /// `size` cannot wrap. `None` when `size` is negative.
    #[must_use]
    pub const fn end_address(&self) -> Option<u64> {
        if self.size < 0 {
            None
        } else {
            Some(self.data_address as u64 + self.size as u64)
        }
    }

    /// `true` when the row's type code is absent from the C++ known set.
    ///
    /// Informational: an unknown code is **not** a structural failure.
    #[must_use]
    pub fn has_unknown_type_code(&self) -> bool {
        !known_type_code(self.type_code)
    }
}

/// A decoded RW4 section directory.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Rw4 {
    /// `file_type` word at `0x1C`. Always one of the three values
    /// [`FileType`] names, because anything else is refused.
    pub file_type: u32,
    /// `object_count` at `0x20`. Recorded, never validated.
    pub object_count: u32,
    /// `section_count` at `0x24` — the count the header *claims*.
    pub section_count: u32,
    /// `section_info_pointer` at `0x30`.
    pub section_info_pointer: u32,
    /// `buffer_pointer` at `0x44`: the arena base.
    pub buffer_pointer: u32,
    /// `buffer_size` at `0x4C`: the arena extent.
    pub buffer_size: u32,
    /// Type codes from the SectionTypes block, in stored order.
    pub type_codes: Vec<u32>,
    /// The section rows, in stored order.
    pub sections: Vec<Section>,
    /// Length of the record these fields were decoded from.
    pub record_size: usize,
    /// Uninterpreted word at `0x28`.
    pub unknown_28: u32,
    /// Uninterpreted word at `0x2C`.
    pub unknown_2c: u32,
    /// Uninterpreted word at `0x34`.
    pub unknown_34: u32,
    /// Uninterpreted word at `0x48`.
    pub unknown_48: u32,
}

impl Rw4 {
    /// Classified [`Rw4::file_type`].
    ///
    /// Always one of the three known variants, because [`parse`] refuses every
    /// other word.
    #[must_use]
    pub const fn file_type_enum(&self) -> FileType {
        FileType::from_raw(self.file_type)
    }

    /// `true` when the container is structurally well formed:
    ///
    /// * `sections.len() == section_count` (the rows the header claims are all
    ///   present — note this is `false` for a record whose `section_count`
    ///   exceeds its row array), **and**
    /// * every `size >= 0`, **and**
    /// * every `data_address + size <= record_size` (64-bit, so no wrap).
    ///
    /// This is a **property, not a parse result**. [`parse`] returns `Ok` for a
    /// record that fails it — see the crate docs, "Deliberate divergences".
    #[must_use]
    pub fn is_complete(&self) -> bool {
        if self.sections.len() != self.section_count as usize {
            return false;
        }
        self.sections.iter().all(|s| {
            s.size >= 0 && (s.data_address as u64 + s.size as u64) <= self.record_size as u64
        })
    }

    /// How many sections carry a type code outside the C++ known set.
    ///
    /// Informational only. On the real corpus this is 1,182 of 5,192 sections
    /// (`0x7000c` and `0x7000f`, 591 each) — which is exactly why an unknown
    /// type code is not an error: refusing those records would refuse the game.
    #[must_use]
    pub fn unknown_type_codes(&self) -> usize {
        self.sections
            .iter()
            .filter(|s| !known_type_code(s.type_code))
            .count()
    }

    /// The C++ known set's name for `tc`.
    ///
    /// Delegates to [`cpp_type_name`]; `self` is part of the signature so a
    /// future per-record overlay can take precedence without breaking callers.
    /// `None` means either "not in the C++ set" (test with
    /// [`known_type_code`]) or "in the set but unnamed" (`0x2000b`, `0x7000b`).
    #[must_use]
    pub fn type_code_name(&self, tc: u32) -> Option<&'static str> {
        cpp_type_name(tc)
    }

    /// Canonical one-line summary, **byte-for-byte identical** to
    /// `tools/spore/rw4/rw4.py::describe` for the same input.
    ///
    /// ```text
    /// <ftype:0xHEX> obj=<N> sec=<N> buf=<N> | <tc:HEX> d=<addr:0xHEX> s=<size> ...
    /// ```
    ///
    /// Rules that must not drift:
    ///
    /// * hex is lowercase with **no zero padding** (`0x1`, not `0x00000001`);
    /// * `file_type` and `data_address` carry the `0x` prefix, `type_code`
    ///   does not — the C++ calls these `hexNoPad` and `hexPlain`;
    /// * `obj`, `sec`, `buf` and `s` are decimal, and `s` is signed;
    /// * sections are joined by `" | "` with a leading space on each.
    ///
    /// The oracle guards its row loop with `if o + 24 > len(b): break`. That
    /// guard **cannot fire here**: [`parse`] has already proved
    /// `section_count` rows fit inside the record, or returned an error. So the
    /// `break` and a plain iteration produce the same string, and omitting the
    /// guard does not fork the format.
    #[must_use]
    pub fn describe(&self) -> String {
        let mut line = String::with_capacity(48 + self.sections.len() * 40);
        line.push_str(&format!("0x{:x}", self.file_type));
        line.push_str(" obj=");
        line.push_str(&self.object_count.to_string());
        line.push_str(" sec=");
        line.push_str(&self.section_count.to_string());
        line.push_str(" buf=");
        line.push_str(&self.buffer_size.to_string());
        for s in &self.sections {
            line.push_str(" | ");
            line.push_str(&format!("{:x}", s.type_code));
            line.push_str(" d=0x");
            line.push_str(&format!("{:x}", s.data_address));
            line.push_str(" s=");
            line.push_str(&s.size.to_string());
        }
        line
    }
}

/// Copies the 4 raw bytes at `off`, or `None` if they are not all present.
///
/// `checked_add` keeps this total: no crafted offset can wrap it. `try_into`
/// cannot fail here — the slice from `get` is exactly 4 bytes.
fn word_at(data: &[u8], off: usize) -> Option<[u8; 4]> {
    let end = off.checked_add(4)?;
    data.get(off..end)?.try_into().ok()
}

/// Reads a little-endian `u32` at `off`.
///
/// Every call site in [`parse`] follows a bounds check that makes the `Err` arm
/// unreachable; mapping it to `TooShort` rather than a panic or a silent zero
/// keeps the claim honest either way.
fn u32_at(data: &[u8], off: usize) -> Result<u32, Rw4Error> {
    word_at(data, off)
        .map(u32::from_le_bytes)
        .ok_or(Rw4Error::TooShort {
            len: data.len(),
            needed: off.saturating_add(4),
        })
}

/// Reads a little-endian `i32` at `off`. See [`u32_at`] on the `Err` arm.
fn i32_at(data: &[u8], off: usize) -> Result<i32, Rw4Error> {
    word_at(data, off)
        .map(i32::from_le_bytes)
        .ok_or(Rw4Error::TooShort {
            len: data.len(),
            needed: off.saturating_add(4),
        })
}

/// Parses an RW4 record's section directory.
///
/// # Errors
///
/// Returns the first structural problem in check order — see [`Rw4Error`] for
/// one variant per mode. It deliberately does **not** return an error for an
/// incomplete container or for an unknown section type code; those are
/// properties ([`Rw4::is_complete`], [`Rw4::unknown_type_codes`]).
///
/// # Panics
///
/// None. Every read is bounds-checked and every offset computed in `usize` or
/// `u64` so it cannot wrap; the truncation sweep in the test module asserts
/// this over every prefix of the committed fixture.
pub fn parse(data: &[u8]) -> Result<Rw4, Rw4Error> {
    let len = data.len();
    let len64 = len as u64;

    // (1) Length. Covers the header AND the manifest, which is why there is no
    //     separate "too small for manifest" error.
    if len < MIN_RECORD_SIZE {
        return Err(Rw4Error::TooShort {
            len,
            needed: MIN_RECORD_SIZE,
        });
    }

    // (2) Magic. Report the first differing byte so a diagnosis does not
    //     require re-diffing 28 bytes by hand.
    for (i, want) in MAGIC.iter().enumerate() {
        // `i < MAGIC_LEN <= len` holds after the check in (1), so `get` is
        // `Some`; the `None` arm is unreachable and is mapped to the honest
        // error rather than a panic.
        match data.get(i) {
            Some(got) if got == want => {}
            Some(got) => {
                return Err(Rw4Error::BadMagic {
                    offset: i,
                    found: *got,
                    want: *want,
                })
            }
            None => return Err(Rw4Error::TooShort { len, needed: i + 1 }),
        }
    }

    // (3) Header words. Every offset below 0x98 is inside the length already
    //     proved in (1), so every read here succeeds.
    let file_type = u32_at(data, FILE_TYPE_OFFSET)?;
    let object_count = u32_at(data, OBJECT_COUNT_OFFSET)?;
    let section_count = u32_at(data, SECTION_COUNT_OFFSET)?;
    let section_info_pointer = u32_at(data, SECTION_INFO_POINTER_OFFSET)?;
    let buffer_pointer = u32_at(data, BUFFER_POINTER_OFFSET)?;
    let buffer_size = u32_at(data, BUFFER_SIZE_OFFSET)?;
    let unknown_28 = u32_at(data, 0x28)?;
    let unknown_2c = u32_at(data, 0x2C)?;
    let unknown_34 = u32_at(data, 0x34)?;
    let unknown_48 = u32_at(data, 0x48)?;

    // (4) Arena bounds, in 64-bit: `base <= len && size <= len - base`.
    if buffer_pointer as u64 > len64 || buffer_size as u64 > len64 - buffer_pointer as u64 {
        return Err(Rw4Error::ArenaBoundsViolation {
            base: buffer_pointer,
            size: buffer_size,
            len,
        });
    }

    // (5) file_type must be one of the three known values.
    if !FileType::from_raw(file_type).is_known() {
        return Err(Rw4Error::BadFileType { file_type });
    }

    // (6) Manifest. Its 0x1C bytes are inside MIN_RECORD_SIZE, so only the type
    //     code can be wrong here.
    let manifest_tc = u32_at(data, MANIFEST_OFFSET)?;
    if manifest_tc != MANIFEST_TC {
        return Err(Rw4Error::ManifestTypeCode { found: manifest_tc });
    }
    // o1 is MANIFEST-RELATIVE: the SectionTypes block is at 0x98 + o1, not o1.
    let o1 = u32_at(data, MANIFEST_OFFSET + MANIFEST_TYPES_OFFSET_OFFSET)?;
    let types_off = MANIFEST_OFFSET as u64 + o1 as u64;
    if types_off + 8 > len64 {
        return Err(Rw4Error::ManifestRelativeOffsetOutOfRange {
            offset: o1,
            absolute: types_off,
            len,
        });
    }

    // (7) SectionTypes block: type code, count, then the codes.
    let types_off_usize = types_off as usize;
    let types_tc = u32_at(data, types_off_usize)?;
    if types_tc != TYPES_TC {
        return Err(Rw4Error::SectionTypesTypeCode { found: types_tc });
    }
    let n_types = u32_at(data, types_off_usize + 4)?;
    let types_end = types_off + 8 + n_types as u64 * 4;
    if types_end > len64 {
        return Err(Rw4Error::TypesBlockOutOfRange {
            count: n_types,
            base: types_off,
            needed: types_end,
            avail: len64 - types_off,
        });
    }
    let mut type_codes = Vec::with_capacity(n_types as usize);
    for i in 0..n_types as usize {
        type_codes.push(u32_at(data, types_off_usize + 8 + i * 4)?);
    }

    // (8) Section-info table bounds. Split into two conditions because they are
    //     two different facts.
    if section_info_pointer as u64 > len64 {
        return Err(Rw4Error::SectionInfoPointerOutOfRange {
            ptr: section_info_pointer,
            len,
        });
    }
    let rows_needed = section_count as u64 * SECTION_ROW_SIZE as u64;
    let rows_avail = len64 - section_info_pointer as u64;
    if rows_needed > rows_avail {
        return Err(Rw4Error::SectionTableOverrunsRecord {
            count: section_count,
            ptr: section_info_pointer,
            needed: rows_needed,
            avail: rows_avail,
        });
    }

    // (9) Rows.
    let mut sections = Vec::with_capacity(section_count as usize);
    for i in 0..section_count as usize {
        let row = section_info_pointer as usize + i * SECTION_ROW_SIZE;
        let data_pointer = u32_at(data, row)?;
        let unknown_04 = u32_at(data, row + 0x04)?;
        let size = i32_at(data, row + 0x08)?;
        let align = i32_at(data, row + 0x0C)?;
        let type_code_index = i32_at(data, row + 0x10)?;
        // Stored as i32, kept as u32 so hex formatting matches both references.
        let type_code = u32_at(data, row + 0x14)?;

        // Stricter than both references, which read this and ignore it: a row
        // whose index points outside the record's own type table is corrupt.
        if type_code_index < 0 || type_code_index as usize >= type_codes.len() {
            return Err(Rw4Error::BadSectionTypeCodeIndex {
                index: i,
                index_value: type_code_index,
                count: type_codes.len(),
            });
        }

        // THE ADDRESS-ADJUSTMENT RULE. A BaseResource pointer is relative to the
        // arena base; every other section's is absolute. Do not "simplify".
        let data_address = if type_code == BASE_RESOURCE_TC {
            match data_pointer.checked_add(buffer_pointer) {
                Some(adjusted) => adjusted,
                None => {
                    return Err(Rw4Error::AddressAdjustmentOverflow {
                        index: i,
                        data_pointer,
                        buffer_pointer,
                    })
                }
            }
        } else {
            data_pointer
        };

        sections.push(Section {
            data_pointer,
            unknown_04,
            size,
            align,
            type_code_index,
            type_code,
            data_address,
            row_offset: row,
        });
    }

    Ok(Rw4 {
        file_type,
        object_count,
        section_count,
        section_info_pointer,
        buffer_pointer,
        buffer_size,
        type_codes,
        sections,
        record_size: len,
        unknown_28,
        unknown_2c,
        unknown_34,
        unknown_48,
    })
}

#[cfg(test)]
mod tests;
