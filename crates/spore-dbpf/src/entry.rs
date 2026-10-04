//! One row of the DBPF file index.

use core::fmt;

use spore_core::record::{fourcc, RecordType};
use spore_core::ResourceKey;

/// One file-index row: a record's identity plus its on-disk extent.
///
/// The `(type_id, group_id, instance_id)` triple is the record's identity and
/// the only way anything addresses it — see [`spore_core::ResourceKey`]. The
/// three fields are also projected into [`DbpfEntry::key`] so callers can look
/// a row up with the same key type the rest of the workspace uses.
///
/// # The two size fields
///
/// * `stored_size` is what the bytes on disk occupy, **after** the row's top
///   size bit has been masked off. The DBPF row stores
///   `stored_size | 0x8000_0000`; bit 31 is a flag the format reserves, not a
///   gigabyte of payload. the `0x7FFF_FFFF` size mask is applied during parsing, so a
///   caller never sees the flag.
/// * `memory_size` is the decompressed byte count. It is what the payload's
///   length must equal after [`crate::extract_record`], for both the stored
///   and the QFS path.
///
/// # `key` is derived, not independent
///
/// The flat triple and [`DbpfEntry::key`] hold the same values, which is
/// unavoidable given that both are public. Build rows through
/// [`DbpfEntry::new`], and if you mutate an identity field in place call
/// [`DbpfEntry::sync_key`] to restore the invariant.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct DbpfEntry {
    /// Record type id.
    pub type_id: u32,
    /// Group id.
    pub group_id: u32,
    /// Instance id.
    pub instance_id: u32,
    /// The same identity as a [`ResourceKey`].
    pub key: ResourceKey,
    /// Absolute byte offset of the stored record, measured from the start of
    /// the package image (not from the start of the index).
    pub offset: u32,
    /// Bytes on disk, with the row's top-bit flag already masked off.
    pub stored_size: u32,
    /// Decompressed byte count.
    pub memory_size: u32,
    /// The row's raw `compression` word.
    ///
    /// Only [`COMPRESSION_NONE`] and [`COMPRESSION_QFS`] are decodable. Any
    /// other value parses (the C++ index parser does not look at it either)
    /// and is rejected by [`crate::extract_record`].
    pub compression: u16,
    /// `compression == [`COMPRESSION_QFS`]`.
    ///
    /// A convenience over the raw word, kept for parity with the C++
    /// `DbpfEntry::compressed` flag. Note it is `false` for an
    /// *unsupported* compression value too, which is why extraction validates
    /// `compression` rather than trusting this flag alone.
    pub compressed: bool,
    /// The row's `saved` byte.
    ///
    /// Carried for completeness. Nothing in this crate reads it: the C++ skips
    /// it too, and its meaning is undocumented in the format sources we have.
    pub saved: bool,
}

impl DbpfEntry {
    /// Builds a row and derives [`DbpfEntry::key`] from the identity.
    // A DBPF index row has exactly these eight independent fields; grouping
    // them into a parameter struct would only move the same eight values
    // behind another name at every call site.
    #[allow(clippy::too_many_arguments)]
    pub const fn new(
        type_id: u32,
        group_id: u32,
        instance_id: u32,
        offset: u32,
        stored_size: u32,
        memory_size: u32,
        compression: u16,
        saved: bool,
    ) -> Self {
        Self {
            type_id,
            group_id,
            instance_id,
            key: ResourceKey::new(type_id, group_id, instance_id),
            offset,
            stored_size,
            memory_size,
            compression,
            compressed: compression == COMPRESSION_QFS,
            saved,
        }
    }

    /// Recomputes [`DbpfEntry::key`] from the flat identity fields.
    ///
    /// Call this after mutating `type_id`, `group_id` or `instance_id` in
    /// place; the struct cannot keep the two views in sync on its own.
    pub fn sync_key(&mut self) {
        self.key = ResourceKey::new(self.type_id, self.group_id, self.instance_id);
        self.compressed = self.compression == COMPRESSION_QFS;
    }

    /// The record type as a display four-character code, if it renders as one.
    ///
    /// A convenience over [`spore_core::record::fourcc`]. Spore's real type ids
    /// are mostly *not* printable (`gmdl` = `0x00E6BCE5` renders as
    /// `____`), so this is for diagnostics, never for identity.
    pub fn type_fourcc(&self) -> Option<String> {
        fourcc(self.type_id)
    }

    /// The record type's canonical name from the `typenames.json` table, if
    /// this build knows the id.
    pub fn type_name(&self) -> Option<&'static str> {
        RecordType::from(self.type_id).name()
    }

    /// The compressed spelling of the on-disk extent, for log lines.
    pub fn extent_text(&self) -> String {
        format!("0x{:08x}+{}", self.offset, self.stored_size)
    }
}

impl fmt::Display for DbpfEntry {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let name = self.type_fourcc().unwrap_or_else(|| "____".to_string());
        write!(
            f,
            "{name} {} stored={} mem={} comp=0x{:04x} saved={}",
            self.key.to_tgi(),
            self.stored_size,
            self.memory_size,
            self.compression,
            u8::from(self.saved)
        )
    }
}

/// `compression` word meaning "stored, not compressed".
pub const COMPRESSION_NONE: u16 = 0x0000;

/// `compression` word meaning EA QFS / RefPack.
///
/// `0xFFFF` is the only non-zero value in use; it is a sentinel rather than an
/// algorithm id, which is why any other non-zero value is a hard error instead
/// of a "best effort" decode.
pub const COMPRESSION_QFS: u16 = 0xFFFF;

/// The four magic bytes a 32-bit DBPF package starts with.
pub const MAGIC: [u8; 4] = *b"DBPF";

/// The four magic bytes of the 64-bit `DBBF` variant.
///
/// Recognised only so it can be rejected by name. Its index rows store
/// `chunkOffset` as a `u64`, which this build does not implement.
pub const MAGIC_64: [u8; 4] = *b"DBBF";

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn new_derives_key_and_compressed_flag() {
        let entry = DbpfEntry::new(0x5854_5354, 1, 2, 0x40, 10, 20, COMPRESSION_QFS, true);
        assert_eq!(entry.key, ResourceKey::new(0x5854_5354, 1, 2));
        assert!(entry.compressed);
        assert!(entry.saved);

        let entry = DbpfEntry::new(1, 2, 3, 0, 4, 4, COMPRESSION_NONE, false);
        assert!(!entry.compressed);
        assert_eq!(entry.key.to_tgi(), "0x00000001:0x00000002:0x00000003");
    }

    #[test]
    fn sync_key_repairs_a_hand_mutated_identity() {
        let mut entry = DbpfEntry::new(1, 2, 3, 0, 4, 4, COMPRESSION_NONE, false);
        entry.type_id = 0xDEAD_BEEF;
        entry.compression = COMPRESSION_QFS;
        entry.sync_key();
        assert_eq!(entry.key, ResourceKey::new(0xDEAD_BEEF, 2, 3));
        assert!(entry.compressed);
    }

    #[test]
    fn fourcc_and_type_name_read_from_spire_core() {
        // 0x58545354 little-endian is the bytes "TSTX".
        let entry = DbpfEntry::new(0x5854_5354, 1, 2, 0, 4, 4, COMPRESSION_NONE, false);
        assert_eq!(entry.type_fourcc().as_deref(), Some("TSTX"));
        assert_eq!(entry.type_name(), None);

        let entry = DbpfEntry::new(spore_core::record::type_id::GMDL, 1, 2, 0, 4, 4, 0, false);
        assert_eq!(entry.type_fourcc().as_deref(), Some("____"));
        assert_eq!(entry.type_name(), Some("gmdl"));
    }

    #[test]
    fn display_is_stable_and_contains_the_key() {
        let entry = DbpfEntry::new(
            0x3153_4651,
            0x3333_3333,
            0x4444_4444,
            200,
            421,
            412,
            COMPRESSION_QFS,
            false,
        );
        let text = entry.to_string();
        assert!(text.contains("QFS1"), "fourcc: {text}");
        assert!(text.contains("0x33333333:0x44444444"), "tgi: {text}");
        assert!(
            text.contains("stored=421 mem=412 comp=0xffff"),
            "sizes: {text}"
        );
    }

    #[test]
    fn extent_text_is_hex_offset_plus_decimal_size() {
        let entry = DbpfEntry::new(1, 2, 3, 0x26D, 64, 64, 0, false);
        assert_eq!(entry.extent_text(), "0x0000026d+64");
    }
}
