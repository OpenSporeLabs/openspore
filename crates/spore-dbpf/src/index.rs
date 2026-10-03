//! The 96-byte DBPF v3 header and the file-index block that follows it.
//!
//! Header layout, from `tools/spore/dbpf/dbpf.py`'s module docstring (which
//! transcribes the community-documented DBPF spec) and confirmed byte for byte
//! by `src/assets/Dbpf.cpp` and `tests/fixtures/mini_package.dbpf`:
//!
//! ```text
//! 0x00  4  magic "DBPF"          ("DBBF" is the 64-bit variant, rejected)
//! 0x04  4  major version         never read - see "Versions are not validated"
//! 0x08  4  minor version         never read
//! 0x0c 20  reserved
//! 0x20  4  index major version   never read
//! 0x24  4  index entry count     <-- read
//! 0x28  4  reserved
//! 0x2c  4  index block size      never read (recomputed from the row stride)
//! 0x30 12  reserved
//! 0x3c  4  index minor version   never read
//! 0x40  4  index offset          <-- read
//! 0x44 28  reserved
//! ```

use spore_core::ResourceKey;

use crate::cursor::Cursor;
use crate::entry::DbpfEntry;
use crate::error::DbpfError;

/// Size of the fixed DBPF v3 header.
pub const HEADER_SIZE: usize = 96;

/// Byte offset of the index entry count inside the header (`0x24`).
pub const OFF_INDEX_COUNT: usize = 0x24;

/// Byte offset of the index block offset inside the header (`0x40`).
pub const OFF_INDEX_OFFSET: usize = 0x40;

/// Index flag: one shared type id follows the flags word.
pub const INDEX_FLAG_SHARED_TYPE: u32 = 1 << 0;

/// Index flag: one shared group id follows the (optional) shared type id.
pub const INDEX_FLAG_SHARED_GROUP: u32 = 1 << 1;

/// Index flag: a shared *instance* id follows the other shared ids.
///
/// **Deliberately not honoured.** Both the C++ (`r.skip(4)`) and the Python
/// oracle (`o += 4`) step over these four bytes without reading them, and no
/// row-size term is derived from them. Honouring the word would substitute one
/// instance id for every row's own instance id and silently change every
/// record's identity, which is far worse than ignoring an unused flag. The
/// flag is therefore only used to advance the cursor.
///
/// Note the flag ordering is *positional*: the shared words appear in the order
/// type, group, instance regardless of which flags are set, so a package with
/// `flags & 2` but not `flags & 1` still carries a group word in the second
/// slot.
pub const INDEX_FLAG_SHARED_INSTANCE: u32 = 1 << 2;

/// Mask applied to a row's on-disk size word.
///
/// Bit 31 of the stored size is a format-level flag, not a size bit. Without
/// this mask a 16-byte record would read as `0x8000_0010` and every extent
/// check would fail on a perfectly valid package.
pub const SIZE_MASK: u32 = 0x7FFF_FFFF;

/// Row stride when neither the type id nor the group id is shared: 28 bytes.
pub const ROW_SIZE_PLAIN: usize = 28;

/// Row stride when both the type id and the group id are shared: 20 bytes.
///
/// `(instance, offset, stored, memory, compression, saved, padding)` is
/// `4 + 4 + 4 + 4 + 2 + 1 + 1 = 20`.
pub const ROW_SIZE_BOTH_SHARED: usize = 20;

/// Parses the DBPF header and file index out of a whole-package image.
///
/// `data` is the entire package, not just the header: the index offset is
/// absolute from the image start, and record extents are validated against
/// this same image by [`crate::extract_record`].
///
/// # Versions are not validated
///
/// The `major`/`minor` words at `0x04`/`0x08` (and their index-block twins at
/// `0x20`/`0x3c`) are never read. "DBPF v3" is a naming convention for the
/// 32-bit 96-byte-header layout, not a checked field: the C++ reference does
/// not read them either, and refusing an otherwise well-formed package because
/// it claims version 2 would throw away a file the reference implementation
/// reads without complaint. This parser also derives the row stride from the
/// index flags rather than trusting the `index block size` word at `0x2c`,
/// which is what makes it correct for the 20-byte-row layout too.
///
/// # Compression is not validated here
///
/// A row with an unrecognised `compression` word parses successfully, matching
/// the C++ `parseDbpfIndex`. The rejection happens at extraction time, where
/// the extent and the payload are in hand.
pub fn parse_index(data: &[u8]) -> Result<Vec<DbpfEntry>, DbpfError> {
    let header = data.get(..HEADER_SIZE).ok_or(DbpfError::ImageTooShort {
        len: data.len(),
        expected: HEADER_SIZE,
    })?;

    if header.starts_with(&crate::entry::MAGIC_64) {
        return Err(DbpfError::Unsupported64BitVariant);
    }
    if !header.starts_with(&crate::entry::MAGIC) {
        return Err(DbpfError::BadMagic {
            found: read_magic(header),
        });
    }

    // Both words end at bytes 40 and 68, inside the 96 bytes just validated, so
    // these reads cannot fail. `ok_or` rather than `unwrap` keeps the function
    // total without an `unreachable!()` in library code.
    let count = u32_at(header, OFF_INDEX_COUNT).ok_or(DbpfError::ImageTooShort {
        len: data.len(),
        expected: HEADER_SIZE,
    })?;
    let index_offset = u32_at(header, OFF_INDEX_OFFSET).ok_or(DbpfError::ImageTooShort {
        len: data.len(),
        expected: HEADER_SIZE,
    })?;

    if (index_offset as usize) < HEADER_SIZE {
        return Err(DbpfError::IndexOffsetOverlapsHeader {
            offset: index_offset,
            expected: HEADER_SIZE,
        });
    }
    let index_start = index_offset as usize;
    match index_start.checked_add(4) {
        Some(end) if end <= data.len() => {}
        _ => {
            return Err(DbpfError::IndexOffsetPastEnd {
                offset: index_offset,
                len: data.len(),
            });
        }
    }

    let mut cur = Cursor::new(data, index_start);
    let flags = cur.u32_le().ok_or(DbpfError::TruncatedIndexHeader)?;

    let mut shared_type = 0u32;
    let have_type = flags & INDEX_FLAG_SHARED_TYPE != 0;
    if have_type {
        shared_type = cur.u32_le().ok_or(DbpfError::TruncatedIndexHeader)?;
    }

    let mut shared_group = 0u32;
    let have_group = flags & INDEX_FLAG_SHARED_GROUP != 0;
    if have_group {
        shared_group = cur.u32_le().ok_or(DbpfError::TruncatedIndexHeader)?;
    }

    if flags & INDEX_FLAG_SHARED_INSTANCE != 0 {
        // Four bytes are present and are stepped over. See
        // `INDEX_FLAG_SHARED_INSTANCE` for why honouring them would corrupt
        // every row's identity.
        cur.take(4).ok_or(DbpfError::TruncatedIndexHeader)?;
    }

    let row_size = row_size(have_type, have_group);
    // `count > remaining / row_size` in 64-bit arithmetic, exactly as the C++
    // Reader computes it. Comparing in `usize` would be a latent overflow on a
    // 32-bit host; both operands are widened first.
    let available = cur.remaining() as u64;
    if u64::from(count) > available / row_size as u64 {
        return Err(DbpfError::IndexCountExceedsIndex {
            count,
            row_size,
            available: cur.remaining(),
        });
    }

    // The count guard above proved `count * row_size <= cur.remaining()`, and
    // every row consumes exactly `row_size` bytes, so the reads below cannot
    // fail in practice. The `else` arm is kept anyway: that invariant is a
    // property of two separate pieces of arithmetic, and a future edit to
    // either must degrade to a typed error rather than a panic or, worse, a
    // zero-filled row.
    let mut entries = Vec::with_capacity(count as usize);
    for row in 0..count {
        let type_id = if have_type {
            Some(shared_type)
        } else {
            cur.u32_le()
        };
        let group_id = if have_group {
            Some(shared_group)
        } else {
            cur.u32_le()
        };
        let instance_id = cur.u32_le();
        let offset = cur.u32_le();
        let stored_size = cur.u32_le();
        let memory_size = cur.u32_le();
        let compression = cur.u16_le();
        let saved = cur.u8();
        // Trailing pad byte. Consumed so the cursor lands on the next row; its
        // value is undefined in the format and is not carried.
        let _pad = cur.u8();

        let (
            Some(type_id),
            Some(group_id),
            Some(instance_id),
            Some(offset),
            Some(stored_size),
            Some(memory_size),
            Some(compression),
            Some(saved),
        ) = (
            type_id,
            group_id,
            instance_id,
            offset,
            stored_size,
            memory_size,
            compression,
            saved,
        )
        else {
            return Err(DbpfError::TruncatedIndexRow { row });
        };

        entries.push(DbpfEntry::new(
            type_id,
            group_id,
            instance_id,
            offset,
            stored_size & SIZE_MASK,
            memory_size,
            compression,
            saved != 0,
        ));
    }

    Ok(entries)
}

/// The row stride implied by the index header's shared-id flags.
///
/// `20 + (have_type ? 0 : 4) + (have_group ? 0 : 4)`, which is 28 when neither
/// id is shared, 24 when exactly one is, and 20 when both are.
const fn row_size(have_type: bool, have_group: bool) -> usize {
    20 + if have_type { 0 } else { 4 } + if have_group { 0 } else { 4 }
}

/// Reads the first four bytes of `header` for the error report.
///
/// The slice is at least `HEADER_SIZE` bytes by the caller's check; the
/// `unwrap_or` is a total fallback, not an expectation.
fn read_magic(header: &[u8]) -> [u8; 4] {
    header
        .get(..4)
        .and_then(|bytes| bytes.try_into().ok())
        .unwrap_or([0, 0, 0, 0])
}

/// Reads a little-endian `u32` at `at`, or `None` when `header` is too short.
fn u32_at(header: &[u8], at: usize) -> Option<u32> {
    let bytes = header.get(at..at.checked_add(4)?)?;
    let [b0, b1, b2, b3] = bytes.try_into().ok()?;
    Some(u32::from_le_bytes([b0, b1, b2, b3]))
}

/// Linear lookup of an index row by exact identity.
///
/// Returns the **first** matching row, matching the C++ `findDbpfEntry`
/// (which returns the lowest index and has no duplicate detection). A package
/// with two rows of the same identity is malformed, and first-wins is the
/// C++-compatible answer rather than an error this crate would have to invent.
pub fn find_entry<'a>(entries: &'a [DbpfEntry], key: &ResourceKey) -> Option<&'a DbpfEntry> {
    entries.iter().find(|entry| entry.key == *key)
}

/// A parsed index with lookup helpers.
///
/// This is a convenience over [`parse_index`]; the free functions remain the
/// contract, so a consumer that needs nothing but rows can ignore this type.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct PackageIndex {
    entries: Vec<DbpfEntry>,
}

impl PackageIndex {
    /// Parses `data` as a package image and keeps the resulting rows.
    pub fn parse(data: &[u8]) -> Result<Self, DbpfError> {
        Ok(Self {
            entries: parse_index(data)?,
        })
    }

    /// The parsed rows, in file order.
    pub fn entries(&self) -> &[DbpfEntry] {
        &self.entries
    }

    /// Number of rows.
    pub fn len(&self) -> usize {
        self.entries.len()
    }

    /// True when the package declares no records.
    pub fn is_empty(&self) -> bool {
        self.entries.is_empty()
    }

    /// Iterates the rows in file order.
    pub fn iter(&self) -> core::slice::Iter<'_, DbpfEntry> {
        self.entries.iter()
    }

    /// Exact-identity lookup, first match wins.
    pub fn find(&self, key: &ResourceKey) -> Option<&DbpfEntry> {
        find_entry(&self.entries, key)
    }

    /// Identity lookup that honours [`spore_core::WILDCARD`] components.
    ///
    /// A key with [`spore_core::ResourceKey::is_complete`] set behaves exactly
    /// like [`PackageIndex::find`]. A wildcard component matches any value in
    /// that position, which is how a reference that names "some instance of
    /// this type in this group" is resolved against a concrete index. The
    /// first row in file order wins, as in [`PackageIndex::find`].
    pub fn find_matching(&self, key: &ResourceKey) -> Option<&DbpfEntry> {
        let matches = |entry: &DbpfEntry| {
            (key.type_id == spore_core::WILDCARD || entry.type_id == key.type_id)
                && (key.group_id == spore_core::WILDCARD || entry.group_id == key.group_id)
                && (key.instance_id == spore_core::WILDCARD || entry.instance_id == key.instance_id)
        };
        self.entries.iter().find(|entry| matches(entry))
    }

    /// Every row of one type, in file order.
    pub fn of_type(&self, type_id: u32) -> impl Iterator<Item = &DbpfEntry> {
        self.entries
            .iter()
            .filter(move |entry| entry.type_id == type_id)
    }

    /// Extracts one record by identity, resolving the row and reading the
    /// package image in one step.
    ///
    /// Returns [`DbpfError::Unsupported64BitVariant`]'s sibling case: an absent
    /// identity is not a decode failure, so it is reported as `Ok(None)`
    /// rather than an error the caller has to pattern-match around.
    pub fn extract(&self, package: &[u8], key: &ResourceKey) -> Result<Option<Vec<u8>>, DbpfError> {
        match self.find(key) {
            Some(entry) => Ok(Some(crate::extract_record(package, entry)?)),
            None => Ok(None),
        }
    }

    /// Takes ownership of the rows.
    pub fn into_entries(self) -> Vec<DbpfEntry> {
        self.entries
    }
}

impl From<Vec<DbpfEntry>> for PackageIndex {
    fn from(entries: Vec<DbpfEntry>) -> Self {
        Self { entries }
    }
}

impl<'a> IntoIterator for &'a PackageIndex {
    type Item = &'a DbpfEntry;
    type IntoIter = core::slice::Iter<'a, DbpfEntry>;

    fn into_iter(self) -> Self::IntoIter {
        self.entries.iter()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::entry::{MAGIC, MAGIC_64};

    /// One index row, as the values a test wants to see round-trip.
    #[derive(Debug, Clone, Copy)]
    struct Row {
        type_id: u32,
        group_id: u32,
        instance_id: u32,
        offset: u32,
        stored_size: u32,
        memory_size: u32,
        compression: u16,
        saved: u8,
    }

    const fn row(instance_id: u32) -> Row {
        Row {
            type_id: 0x1111_1111,
            group_id: 0x2222_2222,
            instance_id,
            offset: 0x40,
            stored_size: 8,
            memory_size: 8,
            compression: 0,
            saved: 0,
        }
    }

    /// A 96-byte header. `major` is written at `0x04` so the
    /// "versions are never validated" test has something to write.
    fn header(count: u32, index_offset: u32, major: u32) -> Vec<u8> {
        let mut out = vec![0u8; HEADER_SIZE];
        out[0..4].copy_from_slice(&MAGIC);
        out[4..8].copy_from_slice(&major.to_le_bytes());
        out[OFF_INDEX_COUNT..OFF_INDEX_COUNT + 4].copy_from_slice(&count.to_le_bytes());
        out[OFF_INDEX_OFFSET..OFF_INDEX_OFFSET + 4].copy_from_slice(&index_offset.to_le_bytes());
        out
    }

    fn push_u32(out: &mut Vec<u8>, value: u32) {
        out.extend_from_slice(&value.to_le_bytes());
    }

    /// Appends one row, omitting the shared ids the flags announce.
    fn push_row(out: &mut Vec<u8>, spec: &Row, have_type: bool, have_group: bool) {
        if !have_type {
            push_u32(out, spec.type_id);
        }
        if !have_group {
            push_u32(out, spec.group_id);
        }
        push_u32(out, spec.instance_id);
        push_u32(out, spec.offset);
        // Bit 31 set, exactly as `gen_fixtures.py::dbpf_item` writes it.
        push_u32(out, spec.stored_size | !SIZE_MASK);
        push_u32(out, spec.memory_size);
        out.extend_from_slice(&spec.compression.to_le_bytes());
        out.push(spec.saved);
        out.push(0xAA); // padding; its value must not matter
    }

    /// A complete image: header, index header, rows. No payloads.
    fn package(flags: u32, shared: &[u32], rows: &[Row], count: Option<u32>) -> Vec<u8> {
        let have_type = flags & INDEX_FLAG_SHARED_TYPE != 0;
        let have_group = flags & INDEX_FLAG_SHARED_GROUP != 0;
        let mut body = Vec::new();
        push_u32(&mut body, flags);
        for value in shared {
            push_u32(&mut body, *value);
        }
        for spec in rows {
            push_row(&mut body, spec, have_type, have_group);
        }
        let mut image = header(count.unwrap_or(rows.len() as u32), 0, 3);
        image.extend_from_slice(&body);
        let offset = (image.len() - body.len()) as u32;
        image[OFF_INDEX_OFFSET..OFF_INDEX_OFFSET + 4].copy_from_slice(&offset.to_le_bytes());
        image
    }

    // ---- happy paths ------------------------------------------------------

    #[test]
    fn the_plain_layout_is_twenty_eight_byte_rows() {
        let image = package(0, &[], &[row(1), row(2), row(3)], None);
        let entries = parse_index(&image).unwrap();
        assert_eq!(entries.len(), 3);
        assert_eq!(row_size(false, false), ROW_SIZE_PLAIN);
        assert_eq!(ROW_SIZE_PLAIN, 28);
        for (i, entry) in entries.iter().enumerate() {
            assert_eq!(entry.type_id, 0x1111_1111);
            assert_eq!(entry.group_id, 0x2222_2222);
            assert_eq!(entry.instance_id, i as u32 + 1);
            assert_eq!(entry.stored_size, 8, "bit 31 must be masked off");
            assert!(!entry.compressed);
            assert!(!entry.saved);
        }
    }

    #[test]
    fn the_shared_type_flag_shrinks_the_row_to_twenty_four_bytes() {
        let image = package(
            INDEX_FLAG_SHARED_TYPE,
            &[0x00E6_BCE5],
            &[row(1), row(2)],
            None,
        );
        let entries = parse_index(&image).unwrap();
        assert_eq!(entries.len(), 2);
        assert_eq!(row_size(true, false), 24);
        for entry in &entries {
            assert_eq!(
                entry.type_id, 0x00E6_BCE5,
                "the shared type applies to every row"
            );
            assert_eq!(entry.group_id, 0x2222_2222, "the group is still per row");
        }
    }

    #[test]
    fn the_shared_group_flag_also_shrinks_the_row() {
        let image = package(INDEX_FLAG_SHARED_GROUP, &[0x4061_6201], &[row(7)], None);
        let entries = parse_index(&image).unwrap();
        assert_eq!(row_size(false, true), 24);
        assert_eq!(entries[0].type_id, 0x1111_1111);
        assert_eq!(entries[0].group_id, 0x4061_6201);
        assert_eq!(entries[0].instance_id, 7);
    }

    #[test]
    fn both_ids_shared_is_twenty_byte_rows() {
        let image = package(
            INDEX_FLAG_SHARED_TYPE | INDEX_FLAG_SHARED_GROUP,
            &[0x00E6_BCE5, 0x4061_6201],
            &[row(1), row(2), row(3)],
            None,
        );
        let entries = parse_index(&image).unwrap();
        assert_eq!(row_size(true, true), ROW_SIZE_BOTH_SHARED);
        assert_eq!(ROW_SIZE_BOTH_SHARED, 20);
        assert_eq!(entries.len(), 3);
        assert_eq!(
            entries[2].key,
            ResourceKey::new(0x00E6_BCE5, 0x4061_6201, 3)
        );
    }

    #[test]
    fn the_shared_instance_flag_is_stepped_over_and_never_applied() {
        // A shared instance id of 0xDEADBEEF is announced and present. If it
        // were honoured, every row would report that instance instead of its
        // own -- silently corrupting every record's identity.
        let flags = INDEX_FLAG_SHARED_INSTANCE;
        let mut image = header(2, HEADER_SIZE as u32, 3);
        push_u32(&mut image, flags);
        push_u32(&mut image, 0xDEAD_BEEF); // the announced shared instance
        push_row(&mut image, &row(11), false, false);
        push_row(&mut image, &row(22), false, false);

        let entries = parse_index(&image).unwrap();
        assert_eq!(
            entries.len(),
            2,
            "the four skipped bytes must not become a row field"
        );
        assert_eq!(entries[0].instance_id, 11);
        assert_eq!(entries[1].instance_id, 22);
        assert_eq!(
            entries[0].type_id, 0x1111_1111,
            "row fields start after the skipped word"
        );
    }

    #[test]
    fn the_saved_byte_is_carried() {
        let mut spec = row(1);
        spec.saved = 0x01;
        let image = package(0, &[], &[spec], None);
        assert!(parse_index(&image).unwrap()[0].saved);

        spec.saved = 0xFF;
        let image = package(0, &[], &[spec], None);
        assert!(parse_index(&image).unwrap()[0].saved);

        spec.saved = 0x00;
        let image = package(0, &[], &[spec], None);
        assert!(!parse_index(&image).unwrap()[0].saved);
    }

    #[test]
    fn qfs_rows_report_the_compression_word_verbatim() {
        let mut spec = row(1);
        spec.compression = crate::COMPRESSION_QFS;
        let image = package(0, &[], &[spec], None);
        let entry = parse_index(&image).unwrap()[0];
        assert_eq!(entry.compression, 0xFFFF);
        assert!(entry.compressed);

        // An unsupported word parses (the C++ index parser does not look at
        // it either) and leaves `compressed` false; extraction rejects it.
        spec.compression = 0x1234;
        let image = package(0, &[], &[spec], None);
        let entry = parse_index(&image).unwrap()[0];
        assert_eq!(entry.compression, 0x1234);
        assert!(!entry.compressed);
        assert!(!crate::is_supported_compression(entry.compression));
    }

    #[test]
    fn versions_are_not_validated() {
        for major in [0u32, 1, 2, 4, 99, u32::MAX] {
            let image = package(0, &[], &[row(1)], None);
            let offset = u32::from_le_bytes(
                image[OFF_INDEX_OFFSET..OFF_INDEX_OFFSET + 4]
                    .try_into()
                    .unwrap(),
            );
            let mut rebuilt = header(1, offset, major);
            rebuilt.extend_from_slice(&image[HEADER_SIZE..]);
            assert_eq!(
                parse_index(&rebuilt).unwrap().len(),
                1,
                "major {major} must still parse"
            );
        }
    }

    #[test]
    fn a_count_of_zero_yields_no_rows() {
        let image = package(0, &[], &[], None);
        assert!(parse_index(&image).unwrap().is_empty());
    }

    // ---- rejections -------------------------------------------------------

    #[test]
    fn an_image_shorter_than_the_header_is_refused() {
        for len in 0..HEADER_SIZE {
            let image = vec![0u8; len];
            assert_eq!(
                parse_index(&image),
                Err(DbpfError::ImageTooShort {
                    len,
                    expected: HEADER_SIZE
                }),
                "len {len}"
            );
        }
    }

    #[test]
    fn the_64_bit_variant_is_refused_by_name() {
        let mut image = header(0, HEADER_SIZE as u32, 3);
        image[0..4].copy_from_slice(&MAGIC_64);
        assert_eq!(parse_index(&image), Err(DbpfError::Unsupported64BitVariant));
    }

    #[test]
    fn other_magic_is_refused_with_the_bytes_it_found() {
        for magic in [*b"XXXX", *b"dbpf", [0u8; 4], [0xFF; 4]] {
            let mut image = header(0, HEADER_SIZE as u32, 3);
            image[0..4].copy_from_slice(&magic);
            assert_eq!(
                parse_index(&image),
                Err(DbpfError::BadMagic { found: magic })
            );
        }
    }

    #[test]
    fn an_index_offset_inside_the_header_is_refused() {
        for offset in [0u32, 1, 95] {
            let mut image = header(0, offset, 3);
            image.resize(HEADER_SIZE + 64, 0);
            assert_eq!(
                parse_index(&image),
                Err(DbpfError::IndexOffsetOverlapsHeader {
                    offset,
                    expected: HEADER_SIZE
                })
            );
        }
    }

    #[test]
    fn an_index_offset_past_the_end_is_refused() {
        let mut image = header(0, 4096, 3);
        image.resize(HEADER_SIZE + 8, 0);
        assert_eq!(
            parse_index(&image),
            Err(DbpfError::IndexOffsetPastEnd {
                offset: 4096,
                len: image.len()
            })
        );

        // Exactly one byte short of the four-byte flags word.
        let mut image = header(0, HEADER_SIZE as u32 + 1, 3);
        image.resize(HEADER_SIZE + 1, 0);
        assert!(matches!(
            parse_index(&image),
            Err(DbpfError::IndexOffsetPastEnd { .. })
        ));
    }

    #[test]
    fn a_truncated_shared_id_word_is_refused() {
        // The flags word fits; the shared type id after it does not.
        let mut image = header(1, HEADER_SIZE as u32, 3);
        push_u32(&mut image, INDEX_FLAG_SHARED_TYPE);
        assert_eq!(parse_index(&image), Err(DbpfError::TruncatedIndexHeader));

        // One byte of the shared type id present.
        image.push(0x00);
        assert_eq!(parse_index(&image), Err(DbpfError::TruncatedIndexHeader));

        // Complete shared type, truncated shared group.
        let mut image = header(1, HEADER_SIZE as u32, 3);
        push_u32(&mut image, INDEX_FLAG_SHARED_TYPE | INDEX_FLAG_SHARED_GROUP);
        push_u32(&mut image, 1);
        assert_eq!(parse_index(&image), Err(DbpfError::TruncatedIndexHeader));
    }

    #[test]
    fn the_shared_instance_word_must_also_be_present() {
        // Announced but only three of its four bytes written: the skip still
        // has to be bounds-checked.
        let mut image = header(0, HEADER_SIZE as u32, 3);
        push_u32(&mut image, INDEX_FLAG_SHARED_INSTANCE);
        image.extend_from_slice(&[0, 0, 0]);
        assert_eq!(parse_index(&image), Err(DbpfError::TruncatedIndexHeader));
    }

    #[test]
    fn a_count_larger_than_the_available_rows_is_refused() {
        let image = package(0, &[], &[row(1), row(2)], Some(3));
        assert_eq!(
            parse_index(&image),
            Err(DbpfError::IndexCountExceedsIndex {
                count: 3,
                row_size: ROW_SIZE_PLAIN,
                available: ROW_SIZE_PLAIN * 2
            })
        );

        // One row's worth of slack short.
        let image = package(0, &[], &[row(1)], Some(2));
        assert!(matches!(
            parse_index(&image),
            Err(DbpfError::IndexCountExceedsIndex { count: 2, .. })
        ));
    }

    #[test]
    fn a_count_whose_rows_exactly_fill_the_image_parses() {
        let image = package(0, &[], &[row(1), row(2)], None);
        assert_eq!(parse_index(&image).unwrap().len(), 2);
        // Trailing bytes past the index are normal (payloads live there).
        let mut padded = image.clone();
        padded.extend_from_slice(&[0xAB; 64]);
        assert_eq!(parse_index(&padded).unwrap().len(), 2);
    }

    #[test]
    fn the_count_guard_accounts_for_the_shared_row_size() {
        // Two 20-byte rows are present; a claim of three rows must fail even
        // though three 28-byte rows would not have fit either.
        let image = package(
            INDEX_FLAG_SHARED_TYPE | INDEX_FLAG_SHARED_GROUP,
            &[1, 2],
            &[row(1), row(2)],
            Some(3),
        );
        assert!(matches!(
            parse_index(&image),
            Err(DbpfError::IndexCountExceedsIndex {
                count: 3,
                row_size: 20,
                ..
            })
        ));
    }

    // ---- lookup -----------------------------------------------------------

    #[test]
    fn find_entry_matches_the_exact_triple() {
        let entries = package(0, &[], &[row(1), row(2)], None);
        let entries = parse_index(&entries).unwrap();
        assert_eq!(
            find_entry(&entries, &ResourceKey::new(0x1111_1111, 0x2222_2222, 2))
                .unwrap()
                .instance_id,
            2
        );
        assert!(find_entry(&entries, &ResourceKey::new(0x1111_1111, 0x2222_2222, 3)).is_none());
        assert!(find_entry(&entries, &ResourceKey::new(9, 9, 9)).is_none());
    }

    #[test]
    fn find_entry_returns_the_first_duplicate_row() {
        // C++ `findDbpfEntry` returns the lowest index and has no duplicate
        // detection; first-wins is the compatible answer.
        let mut first = row(1);
        first.offset = 0x40;
        let mut second = row(1);
        second.offset = 0x80;
        let image = package(0, &[], &[first, second], None);
        let entries = parse_index(&image).unwrap();
        let found = find_entry(&entries, &ResourceKey::new(0x1111_1111, 0x2222_2222, 1)).unwrap();
        assert_eq!(found.offset, 0x40);
    }

    // ---- PackageIndex -----------------------------------------------------

    #[test]
    fn package_index_exposes_the_rows_and_lookups() {
        let image = package(0, &[], &[row(1), row(2), row(3)], None);
        let index = PackageIndex::parse(&image).unwrap();
        assert_eq!(index.len(), 3);
        assert!(!index.is_empty());
        assert_eq!(index.entries().len(), 3);
        assert_eq!(index.iter().count(), 3);
        assert_eq!((&index).into_iter().count(), 3);

        let key = ResourceKey::new(0x1111_1111, 0x2222_2222, 2);
        assert_eq!(index.find(&key).unwrap().instance_id, 2);
        assert_eq!(index.of_type(0x1111_1111).count(), 3);
        assert_eq!(index.of_type(0xDEAD_BEEF).count(), 0);
        assert!(index.find(&ResourceKey::new(1, 2, 99)).is_none());
    }

    #[test]
    fn find_matching_honours_wildcard_components() {
        let image = package(0, &[], &[row(1), row(2), row(3)], None);
        let index = PackageIndex::parse(&image).unwrap();

        // A complete key behaves exactly like `find`.
        assert_eq!(
            index
                .find_matching(&ResourceKey::new(0x1111_1111, 0x2222_2222, 3))
                .unwrap()
                .instance_id,
            3
        );
        // Any instance of this type/group.
        assert_eq!(
            index
                .find_matching(&ResourceKey::new(
                    0x1111_1111,
                    0x2222_2222,
                    spore_core::WILDCARD
                ))
                .unwrap()
                .instance_id,
            1,
            "the first matching row wins, as in `find`"
        );
        // Only the type is constrained.
        let any = ResourceKey::wildcard();
        assert_eq!(index.find_matching(&any).unwrap().instance_id, 1);
        // A wildcard that matches nothing.
        assert!(index
            .find_matching(&ResourceKey::new(0xDEAD_BEEF, 0, 0))
            .is_none());
    }

    #[test]
    fn extract_resolves_a_missing_identity_as_none_not_an_error() {
        let mut spec = row(1);
        spec.offset = 4096; // past the end of a 128-byte image
        let image = package(0, &[], &[spec], None);
        let index = PackageIndex::parse(&image).unwrap();
        assert!(matches!(
            index.extract(&image, &ResourceKey::new(0x1111_1111, 0x2222_2222, 1)),
            Err(DbpfError::RecordExtentPastEnd { .. })
        ));
        assert_eq!(
            index.extract(&image, &ResourceKey::new(9, 9, 9)).unwrap(),
            None
        );
    }

    #[test]
    fn package_index_can_be_built_from_rows_directly() {
        let rows = vec![DbpfEntry::new(1, 2, 3, 4, 5, 6, 0, false)];
        let index = PackageIndex::from(rows.clone());
        assert_eq!(index.entries(), rows.as_slice());
        assert_eq!(index.into_entries(), rows);
        assert!(PackageIndex::default().is_empty());
    }

    #[test]
    fn no_image_prefix_panics() {
        let image = package(
            INDEX_FLAG_SHARED_TYPE,
            &[0x00E6_BCE5],
            &[row(1), row(2)],
            None,
        );
        for len in 0..=image.len() {
            let _ = parse_index(&image[..len]);
        }
    }
}
