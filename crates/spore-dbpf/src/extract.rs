//! Reading one record's bytes out of a package image.

use crate::entry::{DbpfEntry, COMPRESSION_NONE, COMPRESSION_QFS};
use crate::error::DbpfError;
use crate::qfs;

/// Extracts one record's payload from the package image.
///
/// The steps, in the order the C++ reference performs them:
///
/// 1. bound `[offset, offset + stored_size)` against the image,
/// 2. reject an unrecognised `compression` word,
/// 3. copy the stored bytes, or QFS-decompress them,
/// 4. require the result to be exactly `memory_size` long.
///
/// The order matters: the extent check is the cheapest way to reject a corrupt
/// index, and doing it first means a row pointing into another record's bytes
/// never reaches the decompressor at all.
///
/// # The size invariant
///
/// Step 4 is mandatory on **both** paths. The C++ applies it only after a QFS
/// decompression, because only there can the produced length disagree with the
/// index for reasons that are not obviously corruption. This port applies it to
/// stored records too: a row whose `stored_size` and `memory_size` disagree
/// while `compression == 0` is equally corrupt, and silently returning
/// `stored_size` bytes would hand the caller a payload of the wrong length with
/// no indication that anything was wrong. See the crate docs, "Divergences".
pub fn extract_record(package: &[u8], entry: &DbpfEntry) -> Result<Vec<u8>, DbpfError> {
    // 64-bit arithmetic on purpose. `offset` and `stored_size` are each up to
    // 2^32 - 1, so a 32-bit sum wraps, and `offset = 0xFFFF_FFFF` with
    // `stored_size = 0x10` would present as a valid-looking window near the
    // start of a short image. Widening first makes it a clean error.
    let end = u64::from(entry.offset) + u64::from(entry.stored_size);
    if end > package.len() as u64 {
        return Err(DbpfError::RecordExtentPastEnd {
            offset: entry.offset,
            stored_size: entry.stored_size,
            len: package.len(),
        });
    }

    if entry.compression != COMPRESSION_NONE && entry.compression != COMPRESSION_QFS {
        return Err(DbpfError::UnsupportedCompression {
            compression: entry.compression,
        });
    }

    let start = entry.offset as usize;
    // `end` is inside `package` by the check above; the `ok_or` keeps the slice
    // range total without an `unwrap` if the two ever drift apart.
    let raw = package
        .get(start..(end as usize))
        .ok_or(DbpfError::RecordExtentPastEnd {
            offset: entry.offset,
            stored_size: entry.stored_size,
            len: package.len(),
        })?;

    let payload = if entry.compressed {
        qfs::decompress(raw)?
    } else {
        raw.to_vec()
    };

    if payload.len() != entry.memory_size as usize {
        return Err(DbpfError::SizeMismatch {
            actual: payload.len(),
            expected: entry.memory_size as usize,
        });
    }

    Ok(payload)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::index::{parse_index, OFF_INDEX_COUNT, OFF_INDEX_OFFSET, SIZE_MASK};

    /// A minimal literal-only QFS stream.
    ///
    /// Enough to exercise the stored/compressed branches; the full token
    /// encoder and its round-trips live in `tests/qfs_tokens.rs`.
    fn compress_literals(payload: &[u8]) -> Vec<u8> {
        let mut out = vec![0x10, 0xFB, 0, 0, 0];
        out[2] = ((payload.len() >> 16) & 0xFF) as u8;
        out[3] = ((payload.len() >> 8) & 0xFF) as u8;
        out[4] = (payload.len() & 0xFF) as u8;
        let mut at = 0;
        while payload.len() - at >= 4 {
            out.push(0xE0);
            out.extend_from_slice(&payload[at..at + 4]);
            at += 4;
        }
        let tail = payload.len() - at;
        if tail > 0 {
            out.push(252 + tail as u8);
            out.extend_from_slice(&payload[at..]);
        }
        out
    }

    /// A one-record package image holding `payload`, compressed or not.
    ///
    /// Mirrors `tests/fixtures/gen_fixtures.py::dbpf_item`: the stored size
    /// word carries bit 31 set, and the reader must mask it off.
    fn package(payload: &[u8], compress: bool) -> Vec<u8> {
        let stored = if compress {
            compress_literals(payload)
        } else {
            payload.to_vec()
        };
        let offset = 96 + 4 + 28;
        let mut image = vec![0u8; 96];
        image[0..4].copy_from_slice(&crate::entry::MAGIC);
        image[OFF_INDEX_COUNT..OFF_INDEX_COUNT + 4].copy_from_slice(&1u32.to_le_bytes());
        image[OFF_INDEX_OFFSET..OFF_INDEX_OFFSET + 4].copy_from_slice(&96u32.to_le_bytes());
        image.extend_from_slice(&0u32.to_le_bytes());
        image.extend_from_slice(&0x1111_1111u32.to_le_bytes());
        image.extend_from_slice(&0x2222_2222u32.to_le_bytes());
        image.extend_from_slice(&0x3333_3333u32.to_le_bytes());
        image.extend_from_slice(&(offset as u32).to_le_bytes());
        // Bit 31 is the format's flag bit, so the reader must mask it off
        // (`stored_size & SIZE_MASK`) to recover the real length.
        image.extend_from_slice(&(stored.len() as u32 | !SIZE_MASK).to_le_bytes());
        image.extend_from_slice(&(payload.len() as u32).to_le_bytes());
        let compression: u16 = if compress {
            COMPRESSION_QFS
        } else {
            COMPRESSION_NONE
        };
        image.extend_from_slice(&compression.to_le_bytes());
        image.extend_from_slice(&[0, 0]);
        image.extend_from_slice(&stored);
        image
    }

    fn first_entry(image: &[u8]) -> DbpfEntry {
        let entries = parse_index(image).unwrap();
        entries[0]
    }

    #[test]
    fn a_stored_record_round_trips() {
        let payload = b"the quick brown fox";
        let image = package(payload, false);
        let entry = first_entry(&image);
        assert!(!entry.compressed);
        assert_eq!(entry.stored_size, payload.len() as u32);
        assert_eq!(entry.memory_size, payload.len() as u32);
        assert_eq!(extract_record(&image, &entry).unwrap(), payload);
    }

    #[test]
    fn a_compressed_record_round_trips() {
        let payload: Vec<u8> = (0..64u32).map(|i| i as u8).collect();
        let image = package(&payload, true);
        let entry = first_entry(&image);
        assert!(entry.compressed);
        assert_eq!(extract_record(&image, &entry).unwrap(), payload);
    }

    #[test]
    fn an_empty_record_is_legal() {
        let image = package(&[], false);
        let entry = first_entry(&image);
        assert_eq!(entry.stored_size, 0);
        assert_eq!(extract_record(&image, &entry).unwrap(), Vec::<u8>::new());
    }

    #[test]
    fn an_extent_past_the_end_of_the_image_is_refused() {
        let image = package(b"0123456789", false);
        let mut entry = first_entry(&image);
        entry.offset = (image.len() - 4) as u32;
        assert_eq!(
            extract_record(&image, &entry),
            Err(DbpfError::RecordExtentPastEnd {
                offset: entry.offset,
                stored_size: 10,
                len: image.len()
            })
        );
    }

    #[test]
    fn an_extent_that_would_overflow_32_bits_is_refused_not_wrapped() {
        let image = package(b"abcd", false);
        let mut entry = first_entry(&image);
        entry.offset = 0xFFFF_FFF0;
        entry.stored_size = 0x20;
        assert_eq!(
            extract_record(&image, &entry),
            Err(DbpfError::RecordExtentPastEnd {
                offset: 0xFFFF_FFF0,
                stored_size: 0x20,
                len: image.len()
            })
        );
    }

    #[test]
    fn an_unsupported_compression_word_is_refused() {
        let image = package(b"abcd", false);
        let mut entry = first_entry(&image);
        entry.compression = 0x1234;
        assert_eq!(
            extract_record(&image, &entry),
            Err(DbpfError::UnsupportedCompression {
                compression: 0x1234
            })
        );
    }

    #[test]
    fn a_stored_record_whose_size_disagrees_with_the_index_is_refused() {
        let image = package(b"abcd", false);
        let mut entry = first_entry(&image);
        entry.memory_size = 5;
        assert_eq!(
            extract_record(&image, &entry),
            Err(DbpfError::SizeMismatch {
                actual: 4,
                expected: 5
            })
        );
    }

    #[test]
    fn a_compressed_record_whose_size_disagrees_with_the_index_is_refused() {
        let payload: Vec<u8> = (0..16u32).map(|i| i as u8).collect();
        let image = package(&payload, true);
        let mut entry = first_entry(&image);
        entry.memory_size = 15;
        let error = extract_record(&image, &entry).unwrap_err();
        assert_eq!(
            error,
            DbpfError::SizeMismatch {
                actual: 16,
                expected: 15
            }
        );
        assert!(error.is_extent());
    }

    #[test]
    fn a_qfs_failure_inside_a_record_propagates_unchanged() {
        let image = package(b"abcd", true);
        let entry = first_entry(&image);
        // Corrupt the QFS variant byte inside the stored payload.
        let mut broken = image.clone();
        broken[entry.offset as usize] = 0x11;
        assert_eq!(
            extract_record(&broken, &entry),
            Err(DbpfError::QfsBadMagic {
                first: 0x11,
                second: 0xFB
            })
        );
    }
}
