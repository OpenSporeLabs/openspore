//! Typed errors for every rejection path in the DBPF/QFS decoder.

/// Why a DBPF index, a record extent, or a QFS stream could not be decoded.
///
/// Every variant maps 1:1 onto an error string the C++ reference
/// (`src/assets/Dbpf.cpp`) emits, so a Rust failure can be lined up with a C++
/// log line without a translation table. Where this port is deliberately
/// *stricter* than the C++, the variant's doc comment says so.
///
/// # One C++ error path that is deliberately absent
///
/// The C++ has `dbpf: truncated header`. It cannot fire, and keeping an
/// unreachable variant would be a lie to the next reader: it guards the two
/// header reads at `0x24` and `0x40`, which end at bytes 40 and 68. Both fit
/// inside the 96-byte header that [`DbpfError::ImageTooShort`] has already
/// enforced, so the earlier check subsumes it entirely.
///
/// Its sibling `dbpf: truncated index row N` is equally unreachable but is
/// **kept** as [`DbpfError::TruncatedIndexRow`], because there the guard and
/// the row walk are separate arithmetic that a future edit could unlink, and a
/// typed error is the right degradation.
#[derive(Debug, Clone, PartialEq, Eq, thiserror::Error)]
pub enum DbpfError {
    /// The image is shorter than the 96-byte DBPF header.
    ///
    /// C++: `dbpf: image smaller than 96-byte header`.
    #[error("dbpf: image is {len} bytes, smaller than the {expected}-byte header")]
    ImageTooShort {
        /// Length of the supplied image.
        len: usize,
        /// The fixed header size, [`crate::HEADER_SIZE`].
        expected: usize,
    },

    /// The 64-bit `DBBF` variant was supplied.
    ///
    /// C++: `dbpf: DBBF 64-bit variant not supported (offsets are 8 bytes)`.
    /// A `DBBF` index row stores `chunkOffset` as a `u64`, which changes the
    /// row stride from 28 to 32 bytes and every offset in the file. Silently
    /// mis-parsing it would hand out extents that point into the wrong place,
    /// so it is refused with its own error rather than as "bad magic".
    #[error("dbpf: DBBF 64-bit variant not supported (row offsets are 8 bytes)")]
    Unsupported64BitVariant,

    /// The four magic bytes are neither `DBPF` nor `DBBF`.
    ///
    /// C++: `dbpf: bad magic (want DBPF)`.
    #[error("dbpf: bad magic {found:02x?} (want 44425046 = \"DBPF\")")]
    BadMagic {
        /// The first four bytes of the image, verbatim.
        found: [u8; 4],
    },

    /// `index_offset` points inside the 96-byte header.
    ///
    /// C++: `dbpf: index offset overlaps header`.
    #[error("dbpf: index offset 0x{offset:08x} overlaps the {expected}-byte header")]
    IndexOffsetOverlapsHeader {
        /// The declared index offset, verbatim from the header.
        offset: u32,
        /// [`crate::HEADER_SIZE`].
        expected: usize,
    },

    /// `index_offset` is at or past the end of the image, so not even the
    /// 4-byte index flags word is readable.
    ///
    /// C++: `dbpf: index offset past end of image`.
    #[error("dbpf: index offset 0x{offset:08x} + 4 leaves a {len}-byte image")]
    IndexOffsetPastEnd {
        /// The declared index offset, verbatim from the header.
        offset: u32,
        /// Length of the supplied image.
        len: usize,
    },

    /// The index header (the flags word and the shared id fields it announces)
    /// runs past the end of the image.
    ///
    /// C++: `dbpf: truncated index header`.
    ///
    /// Reachable: `index_offset + 4 <= len` is checked by the caller, but
    /// nothing guarantees the shared type/group words after it exist.
    #[error("dbpf: truncated index header (flags/shared-id fields run past the image)")]
    TruncatedIndexHeader,

    /// The declared entry count cannot fit in the bytes that follow the index
    /// header.
    ///
    /// C++: `dbpf: index count exceeds available bytes`.
    #[error(
        "dbpf: index count {count} exceeds the {available} bytes after the index header \
            ({row_size} bytes per row)"
    )]
    IndexCountExceedsIndex {
        /// The declared entry count.
        count: u32,
        /// Row stride implied by the index flags.
        row_size: usize,
        /// Bytes actually available for rows.
        available: usize,
    },

    /// Reads of one index row ran past the end of the image.
    ///
    /// C++: `dbpf: truncated index row N`.
    ///
    /// **Unreachable in practice, kept deliberately.** The count guard rejects
    /// when `count > remaining / row_size`, which is exactly
    /// `count * row_size > remaining`; since every row consumes `row_size`
    /// bytes, every row then fits. This variant is the second line of defence
    /// for that invariant rather than a reachable state: the guard and the row
    /// walk are separate arithmetic, and if a future edit breaks the link the
    /// right outcome is a typed error on a corrupt package, never a panic and
    /// never a row of silent zeroes.
    #[error("dbpf: truncated index row {row}")]
    TruncatedIndexRow {
        /// Zero-based row index that could not be read.
        row: u32,
    },

    /// A record's `[offset, offset + stored_size)` window is not inside the
    /// package image.
    ///
    /// C++: `dbpf: record extent past end of image`.
    ///
    /// The sum is evaluated in `u64`, so `offset = 0xFFFF_FFFF` with
    /// `stored_size = 0xFFFF_FFFF` is a clean error rather than a wrapped
    /// range that would slice a short image.
    #[error("dbpf: record extent 0x{offset:08x}+{stored_size} leaves a {len}-byte image")]
    RecordExtentPastEnd {
        /// Row's absolute byte offset.
        offset: u32,
        /// Row's on-disk size, after the top-bit flag mask.
        stored_size: u32,
        /// Length of the supplied package image.
        len: usize,
    },

    /// The row's `compression` word is neither `0` nor `0xFFFF`.
    ///
    /// The value is reported in hexadecimal because that is how the field is
    /// read in a hex dump and how the C++ log line names it.
    #[error("dbpf: unsupported compression 0x{compression:04x} (want 0x0000 none or 0xffff qfs)")]
    UnsupportedCompression {
        /// The row's raw `compression` word.
        compression: u16,
    },

    /// The decoded record length disagrees with the row's declared
    /// `memory_size`.
    ///
    /// C++ checks this only on the compressed path
    /// (`dbpf: decompressed size N != index memSize M`). This port checks it on
    /// **both** paths, so an uncompressed row whose `stored_size` disagrees with
    /// its `memory_size` is also rejected: either the index row or the payload
    /// is corrupt, and both fields being present makes a mismatch a fact about
    /// the file rather than a curiosity. See the crate docs, "Divergences".
    #[error("dbpf: decoded {actual} bytes != index memory_size {expected}")]
    SizeMismatch {
        /// Length actually decoded.
        actual: usize,
        /// Length the index row declares.
        expected: usize,
    },

    /// The stored record is shorter than the 5-byte QFS header.
    ///
    /// C++: `qfs: record shorter than 5-byte header`.
    #[error("qfs: record is {len} bytes, shorter than the {expected}-byte header")]
    QfsHeaderTooShort {
        /// Length of the supplied record image.
        len: usize,
        /// [`crate::QFS_HEADER_SIZE`].
        expected: usize,
    },

    /// The QFS magic is not `10 FB` or `50 FB`.
    ///
    /// C++: `qfs: bad header magic (want 10FB or 50FB)`.
    #[error("qfs: bad header magic {first:02x} {second:02x} (want 10 fb or 50 fb)")]
    QfsBadMagic {
        /// `data[0]`, which selects the `0x10` or `0x50` variant.
        first: u8,
        /// `data[1]`, always `0xFB`.
        second: u8,
    },

    /// The token stream ended where a control byte was required.
    ///
    /// C++: `qfs: truncated control byte`.
    #[error("qfs: truncated control byte (token stream ends mid-token)")]
    QfsTruncatedControlByte,

    /// A `192 <= c < 224` token is missing its three operand bytes.
    ///
    /// C++: `qfs: truncated long-match token`.
    #[error("qfs: truncated long-match token (needs 3 operand bytes)")]
    QfsTruncatedLongMatchToken,

    /// A `128 <= c < 192` token is missing its two operand bytes.
    ///
    /// C++: `qfs: truncated mid-match token`.
    #[error("qfs: truncated mid-match token (needs 2 operand bytes)")]
    QfsTruncatedMidMatchToken,

    /// A `c < 128` token is missing its one operand byte.
    ///
    /// C++: `qfs: truncated short-match token`.
    #[error("qfs: truncated short-match token (needs 1 operand byte)")]
    QfsTruncatedShortMatchToken,

    /// A literal run reaches past the end of the input, or past the declared
    /// decompressed size.
    ///
    /// C++: `qfs: truncated literal run`.
    #[error("qfs: truncated literal run of {literals} bytes (input or declared size ends first)")]
    QfsTruncatedLiteralRun {
        /// Number of literals the token asked for.
        literals: usize,
    },

    /// A back-reference reaches before the start of the output, or a copy run
    /// would push the output past its declared decompressed size.
    ///
    /// C++: `qfs: invalid back-reference`.
    ///
    /// This is defence, not paranoia: both conditions mean the stream is
    /// corrupt or hostile, and the only alternative to failing is reading
    /// outside the output buffer. Note that a distance equal to the number of
    /// bytes produced so far is *legal* (`distance == produced` copies the very
    /// first byte, and `distance == 1` re-emits the last byte), so the test is
    /// strictly `distance > produced`.
    #[error(
        "qfs: invalid back-reference (distance {distance} with {produced} bytes produced, \
            {copies} copies)"
    )]
    QfsInvalidBackReference {
        /// Requested distance back from the write cursor.
        distance: usize,
        /// Output length when the token was decoded.
        produced: usize,
        /// Copies the token asked for.
        copies: usize,
    },
}

impl DbpfError {
    /// True when the error came from the QFS token decoder rather than from
    /// the DBPF container layer.
    ///
    /// Callers that want to log "the container is fine, the payload is
    /// corrupt" can branch on this instead of matching every QFS variant.
    pub fn is_qfs(&self) -> bool {
        matches!(
            self,
            Self::QfsHeaderTooShort { .. }
                | Self::QfsBadMagic { .. }
                | Self::QfsTruncatedControlByte
                | Self::QfsTruncatedLongMatchToken
                | Self::QfsTruncatedMidMatchToken
                | Self::QfsTruncatedShortMatchToken
                | Self::QfsTruncatedLiteralRun { .. }
                | Self::QfsInvalidBackReference { .. }
        )
    }

    /// True when the error is about the record *extent* or the *declared*
    /// sizes, i.e. the index row disagrees with the payload it points at.
    pub fn is_extent(&self) -> bool {
        matches!(
            self,
            Self::RecordExtentPastEnd { .. } | Self::SizeMismatch { .. }
        )
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn error_messages_name_the_field_they_rejected() {
        let err = DbpfError::UnsupportedCompression {
            compression: 0x1234,
        };
        assert_eq!(
            err.to_string(),
            "dbpf: unsupported compression 0x1234 (want 0x0000 none or 0xffff qfs)"
        );

        let err = DbpfError::Unsupported64BitVariant;
        assert!(
            err.to_string().contains("DBBF"),
            "the variant name is the whole message"
        );

        let err = DbpfError::BadMagic { found: *b"XXXX" };
        assert!(
            err.to_string().contains("want 44425046"),
            "the wanted magic is spelled out"
        );
    }

    #[test]
    fn qfs_and_extent_classifiers_are_disjoint() {
        assert!(DbpfError::QfsTruncatedControlByte.is_qfs());
        assert!(!DbpfError::QfsTruncatedControlByte.is_extent());

        assert!(DbpfError::SizeMismatch {
            actual: 1,
            expected: 2
        }
        .is_extent());
        assert!(!DbpfError::SizeMismatch {
            actual: 1,
            expected: 2
        }
        .is_qfs());

        assert!(!DbpfError::BadMagic { found: *b"XXXX" }.is_qfs());
        assert!(!DbpfError::BadMagic { found: *b"XXXX" }.is_extent());
    }

    #[test]
    fn errors_compare_by_value_so_tests_can_match_exactly() {
        assert_eq!(
            DbpfError::QfsBadMagic {
                first: 0x00,
                second: 0x00
            },
            DbpfError::QfsBadMagic {
                first: 0x00,
                second: 0x00
            }
        );
        assert_ne!(
            DbpfError::QfsBadMagic {
                first: 0x00,
                second: 0x00
            },
            DbpfError::QfsBadMagic {
                first: 0x10,
                second: 0xFB
            }
        );
    }
}
