//! EA QFS (RefPack) decompression.
//!
//! # Stream layout
//!
//! ```text
//! data[0]      0x10 or 0x50   header variant
//! data[1]      0xFB           fixed
//! data[2..5]   u24 BIG-ENDIAN decompressed size
//! data[5..]    token stream
//! ```
//!
//! **The 24-bit decompressed size is the only big-endian field in the entire
//! DBPF/QFS format.** Every other multi-byte value — the header words, the
//! index rows, the token operands — is little-endian. This one is big-endian in
//! the original EA implementation and in both references here
//! (`src/assets/Dbpf.cpp` spells out the three shifts; `dbpf.py` writes
//! `(buf[2] << 16) | (buf[3] << 8) | buf[4]`). Reading it little-endian
//! produces a plausible-looking size that is usually wrong, so it is
//! byte-shifted explicitly rather than through a typed LE reader.
//!
//! # The token grammar
//!
//! Each token is one control byte `c`, plus a class-dependent number of
//! operand bytes. A token emits its **literals first** and then its **copies**,
//! each copy being a single-byte back-reference `out.push(out[len - distance])`
//! evaluated one byte at a time, so `distance == 1` legitimately re-emits the
//! byte just written (a run-length expansion of one byte).
//!
//! | control byte | operand bytes | literals | copies | distance |
//! |---|---|---|---|---|
//! | `c >= 252` | 0 | `c & 3` | 0 | — |
//! | `224 <= c < 252` | 0 | `((c & 0x1F) << 2) + 4` | 0 | — |
//! | `192 <= c < 224` | 3 | `c & 3` | `((c & 0x0C) << 6) + b3 + 5` | `((c & 0x10) << 12) + (b1 << 8) + b2 + 1` |
//! | `128 <= c < 192` | 2 | `(b1 & 0xC0) >> 6` | `(c & 0x3F) + 4` | `((b1 & 0x3F) << 8) + b2 + 1` |
//! | `c < 128` | 1 | `c & 3` | `((c & 0x1C) >> 2) + 3` | `((c & 0x60) << 3) + b1 + 1` |
//!
//! The `+ 1` on every distance formula is part of the encoding, not a decoder
//! convenience: the stored value is `distance - 1`, so a *stored* `0` means
//! "copy the byte one position back", not "distance zero". A decoder that
//! treated the operand as a raw distance would reject every legitimate
//! single-byte repeat. Distances therefore start at 1, and the rejection test
//! is `distance > produced` (not `>=`).
//!
//! # Deliberate strictness
//!
//! Two conditions fail the stream rather than being tolerated:
//!
//! * a distance reaching before the start of the output, and
//! * a copy run that would push the output past the declared decompressed size.
//!
//! Both mean the stream is corrupt or hostile. The alternative — clamping, or
//! sizing the output buffer to whatever the tokens happen to produce — turns a
//! corrupt asset into silently wrong geometry. Trailing bytes *after* the
//! declared output are tolerated, matching the C++, because the decompressed
//! size is the authority on where the record ends.

use crate::cursor::{array_at, Cursor};
use crate::entry::{COMPRESSION_NONE, COMPRESSION_QFS};
use crate::error::DbpfError;

/// Size of the QFS record header: variant byte, magic byte, 24-bit size.
pub const QFS_HEADER_SIZE: usize = 5;

/// The two accepted first bytes, `data[0]`.
pub const QFS_MAGIC_VARIANTS: [u8; 2] = [0x10, 0x50];

/// The fixed second header byte, `data[1]`.
pub const QFS_MAGIC: u8 = 0xFB;

/// Lowest control byte of the "up to 3 literals, no copies" class.
const CTRL_SHORT_LITERALS: u8 = 252;

/// Lowest control byte of the "4..=112 literals" class.
const CTRL_LITERAL_RUN: u8 = 224;

/// Lowest control byte of the long-match class (3 operand bytes).
const CTRL_LONG_MATCH: u8 = 192;

/// Lowest control byte of the mid-match class (2 operand bytes).
const CTRL_MID_MATCH: u8 = 128;

/// Decompresses one EA QFS / RefPack record.
///
/// `data` is the record's *stored* image exactly as it appears on disk. The
/// output buffer is pre-allocated to the declared decompressed size and every
/// write is bounds-checked against that size before it happens, so the returned
/// vector is always exactly as long as the header claims -- never longer, never
/// shorter.
///
/// See the module docs for the token grammar and the reasoning behind the two
/// deliberate failure conditions.
pub fn decompress(data: &[u8]) -> Result<Vec<u8>, DbpfError> {
    let [variant, magic, size_hi, size_mid, size_lo] =
        array_at::<QFS_HEADER_SIZE>(data, 0).ok_or(DbpfError::QfsHeaderTooShort {
            len: data.len(),
            expected: QFS_HEADER_SIZE,
        })?;

    if !QFS_MAGIC_VARIANTS.contains(&variant) || magic != QFS_MAGIC {
        return Err(DbpfError::QfsBadMagic {
            first: variant,
            second: magic,
        });
    }

    // The one big-endian field in the format. See the module docs.
    let want = (usize::from(size_hi) << 16) | (usize::from(size_mid) << 8) | usize::from(size_lo);

    let mut out: Vec<u8> = Vec::with_capacity(want);
    let mut cur = Cursor::new(data, QFS_HEADER_SIZE);

    while out.len() < want {
        let control = cur.u8().ok_or(DbpfError::QfsTruncatedControlByte)?;

        // (literal count, copy count, back-reference distance). `distance` is
        // already the true distance, i.e. the stored operand plus one.
        let (literals, copies, distance): (usize, usize, usize) = if control >= CTRL_SHORT_LITERALS
        {
            (usize::from(control & 3), 0, 0)
        } else if control >= CTRL_LITERAL_RUN {
            ((usize::from(control & 0x1F) << 2) + 4, 0, 0)
        } else if control >= CTRL_LONG_MATCH {
            let b1 = cur.u8().ok_or(DbpfError::QfsTruncatedLongMatchToken)?;
            let b2 = cur.u8().ok_or(DbpfError::QfsTruncatedLongMatchToken)?;
            let b3 = cur.u8().ok_or(DbpfError::QfsTruncatedLongMatchToken)?;
            let copies = (usize::from(control & 0x0C) << 6) + usize::from(b3) + 5;
            let distance =
                (usize::from(control & 0x10) << 12) + (usize::from(b1) << 8) + usize::from(b2) + 1;
            (usize::from(control & 3), copies, distance)
        } else if control >= CTRL_MID_MATCH {
            let b1 = cur.u8().ok_or(DbpfError::QfsTruncatedMidMatchToken)?;
            let b2 = cur.u8().ok_or(DbpfError::QfsTruncatedMidMatchToken)?;
            let literals = usize::from(b1 & 0xC0) >> 6;
            let copies = usize::from(control & 0x3F) + 4;
            let distance = (usize::from(b1 & 0x3F) << 8) + usize::from(b2) + 1;
            (literals, copies, distance)
        } else {
            let b1 = cur.u8().ok_or(DbpfError::QfsTruncatedShortMatchToken)?;
            let literals = usize::from(control & 3);
            let copies = (usize::from(control & 0x1C) >> 2) + 3;
            let distance = (usize::from(control & 0x60) << 3) + usize::from(b1) + 1;
            (literals, copies, distance)
        };

        let produced = out.len();
        // `produced <= want` is an invariant: literals are bounded below and
        // copies are bounded above before either runs, so the subtractions
        // here cannot underflow.
        debug_assert!(produced <= want, "output overran the declared size");

        // Literals come first. The C++ folds "input exhausted" and "would
        // overrun the declared output" into one error; keeping them together
        // preserves its message for the far more common truncated-input case.
        if literals > 0 {
            let within_output = literals <= want - produced;
            match cur.take(literals) {
                Some(chunk) if within_output => out.extend_from_slice(chunk),
                _ => return Err(DbpfError::QfsTruncatedLiteralRun { literals }),
            }
        }

        // Mirror of the C++ guard: fail when the back-reference reaches before
        // the output start, or when the copy run would pass the declared size,
        // but only for a token that actually has copies. A literal-only token
        // has `copies == 0` and `distance == 0`, so its (already-checked)
        // literal bound cannot trip this arm.
        let overruns_output = copies > want - out.len();
        if (distance > out.len() || overruns_output) && (copies > 0 || distance > out.len()) {
            return Err(invalid_back_reference(distance, out.len(), copies));
        }

        if copies > 0 {
            for _ in 0..copies {
                // The guard above already proved both bounds. The `get` keeps
                // this panic-free even if that proof were ever invalidated.
                let Some(index) = out.len().checked_sub(distance) else {
                    return Err(invalid_back_reference(distance, out.len(), copies));
                };
                let Some(byte) = out.get(index).copied() else {
                    return Err(invalid_back_reference(distance, out.len(), copies));
                };
                out.push(byte);
            }
        }
    }

    debug_assert_eq!(
        out.len(),
        want,
        "the loop runs until out.len() == want, and every write is bounded by want"
    );
    Ok(out)
}

/// True when `compression` names a codec this crate can decode.
///
/// `0` is "stored" and `0xFFFF` is QFS; every other value is refused rather
/// than decoded on a guess. This is the single place that decision lives, and
/// it is deliberately *not* the same test as
/// [`crate::DbpfEntry::compressed`], which is false for an unsupported value.
pub fn is_supported_compression(compression: u16) -> bool {
    compression == COMPRESSION_NONE || compression == COMPRESSION_QFS
}

fn invalid_back_reference(distance: usize, produced: usize, copies: usize) -> DbpfError {
    DbpfError::QfsInvalidBackReference {
        distance,
        produced,
        copies,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Wraps a token stream in a QFS header declaring `want` output bytes.
    fn stream(want: usize, tokens: &[u8]) -> Vec<u8> {
        let mut out = vec![0x10, QFS_MAGIC];
        out.push(((want >> 16) & 0xFF) as u8);
        out.push(((want >> 8) & 0xFF) as u8);
        out.push((want & 0xFF) as u8);
        out.extend_from_slice(tokens);
        out
    }

    /// Appends tokens that emit `payload` verbatim.
    ///
    /// Uses 4-literal tokens (control `0xE0`, the floor of the `224..252`
    /// class) and finishes with a `252 + n` token for a 1..=3 byte tail. This
    /// is deliberately the least efficient encoding that can express any byte
    /// string, so a test can hand it any seed without first solving the
    /// tokenisation problem.
    fn push_literals(tokens: &mut Vec<u8>, payload: &[u8]) {
        let mut at = 0;
        while payload.len() - at >= 4 {
            tokens.push(0xE0);
            tokens.extend_from_slice(&payload[at..at + 4]);
            at += 4;
        }
        let tail = payload.len() - at;
        if tail > 0 {
            tokens.push(CTRL_SHORT_LITERALS + tail as u8);
            tokens.extend_from_slice(&payload[at..]);
        }
    }

    fn run(n: usize, b: u8) -> Vec<u8> {
        vec![b; n]
    }

    // ---- header -----------------------------------------------------------

    #[test]
    fn a_zero_length_stream_decodes_to_nothing() {
        assert_eq!(decompress(&stream(0, &[])).unwrap(), Vec::<u8>::new());
    }

    #[test]
    fn both_magic_variants_are_accepted() {
        for variant in QFS_MAGIC_VARIANTS {
            let mut bytes = stream(4, &[0xE0, b'A', b'B', b'C', b'D']);
            bytes[0] = variant;
            assert_eq!(decompress(&bytes).unwrap(), b"ABCD");
        }
    }

    #[test]
    fn a_record_shorter_than_the_header_is_refused() {
        for len in 0..QFS_HEADER_SIZE {
            let bytes = run(len, 0x11);
            assert_eq!(
                decompress(&bytes),
                Err(DbpfError::QfsHeaderTooShort {
                    len,
                    expected: QFS_HEADER_SIZE
                })
            );
        }
    }

    #[test]
    fn a_wrong_variant_or_magic_byte_is_refused() {
        for first in [0x00u8, 0x11, 0x20, 0x51, 0xFF] {
            let mut bytes = stream(4, &[0xE0, 1, 2, 3, 4]);
            bytes[0] = first;
            assert_eq!(
                decompress(&bytes),
                Err(DbpfError::QfsBadMagic {
                    first,
                    second: QFS_MAGIC
                })
            );
        }
        let mut bytes = stream(4, &[0xE0, 1, 2, 3, 4]);
        bytes[1] = 0xFA;
        assert_eq!(
            decompress(&bytes),
            Err(DbpfError::QfsBadMagic {
                first: 0x10,
                second: 0xFA
            })
        );
    }

    #[test]
    fn the_declared_size_is_read_big_endian() {
        // 0x010203 little-endian would be 0x030201 = 197121; read big-endian
        // the stream claims 0x010203 = 66051 and runs out of tokens at once.
        let mut bytes = stream(0, &[]);
        bytes[2] = 0x01;
        bytes[3] = 0x02;
        bytes[4] = 0x03;
        assert_eq!(decompress(&bytes), Err(DbpfError::QfsTruncatedControlByte));
    }

    // ---- token classes ----------------------------------------------------

    #[test]
    fn short_literal_class_emits_up_to_three_bytes() {
        for count in 1..=3usize {
            let control = CTRL_SHORT_LITERALS + count as u8;
            let mut tokens = vec![control];
            tokens.extend_from_slice(&[0x11, 0x22, 0x33]);
            let decoded = decompress(&stream(count, &tokens)).unwrap();
            assert_eq!(decoded, &[0x11, 0x22, 0x33][..count]);
        }
        // Control 0xFC carries no literals at all: the class floor is a no-op
        // token, which is legal and simply contributes nothing.
        let bytes = stream(4, &[0xFC, 0xE0, 1, 2, 3, 4]);
        assert_eq!(decompress(&bytes).unwrap(), [1, 2, 3, 4]);
    }

    #[test]
    fn literal_run_class_emits_four_to_one_hundred_twelve_bytes() {
        for count in [4usize, 8, 40, 112] {
            let payload: Vec<u8> = (0..count).map(|i| i as u8).collect();
            let mut tokens = vec![CTRL_LITERAL_RUN + ((count as u8 - 4) >> 2)];
            tokens.extend_from_slice(&payload);
            assert_eq!(decompress(&stream(count, &tokens)).unwrap(), payload);
        }
    }

    #[test]
    fn short_match_class_copies_three_to_ten_bytes() {
        // Control 0x01: 1 literal, 3 copies, distance 1. The copy source is the
        // literal just emitted, so this is a four-byte run of one value.
        assert_eq!(
            decompress(&stream(4, &[0x01, 0x00, 0xAA])).unwrap(),
            run(4, 0xAA)
        );

        // Control 0x1F: 3 literals, 10 copies (the class ceiling), distance 1.
        let mut tokens = vec![0x1F, 0x00];
        tokens.extend_from_slice(b"ABC");
        let decoded = decompress(&stream(13, &tokens)).unwrap();
        assert_eq!(decoded, b"ABCCCCCCCCCCC");
        assert_eq!(decoded.len(), 13);

        // Control 0x1C: 0 literals, 10 copies, distance 4 -- the copy source
        // must already exist, so a literal token seeds it first.
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(b"WXYZ");
        tokens.extend_from_slice(&[0x1C, 0x03]);
        let decoded = decompress(&stream(14, &tokens)).unwrap();
        let expected: Vec<u8> = (0..14).map(|i| b"WXYZ"[i % 4]).collect();
        assert_eq!(decoded, expected);
        assert_eq!(decoded.len(), 14);
    }

    #[test]
    fn mid_match_class_copies_four_to_sixty_seven_bytes() {
        // Control 0x83: (c & 0x3F) + 4 == 7 copies; b1 = 0x01, b2 = 0x00 give
        // distance (1 << 8) + 0 + 1 = 257.
        let seed: Vec<u8> = (0..257u32).map(|i| i as u8).collect();
        let mut tokens = Vec::new();
        push_literals(&mut tokens, &seed);
        tokens.extend_from_slice(&[0x83, 0x01, 0x00]);
        let decoded = decompress(&stream(264, &tokens)).unwrap();
        let mut expected = seed.clone();
        expected.extend_from_slice(&seed[..7]);
        assert_eq!(decoded, expected);

        // Control 0xBF: (c & 0x3F) + 4 == 67 copies (the ceiling); b1 = 0 and
        // b2 = 0 give distance 1.
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(b"seed");
        tokens.extend_from_slice(&[0x80 | 63, 0x00, 0x00]);
        let decoded = decompress(&stream(71, &tokens)).unwrap();
        assert_eq!(decoded.len(), 71);
        assert_eq!(&decoded[..4], b"seed");
        assert!(
            decoded[4..].iter().all(|&b| b == b'd'),
            "distance 1 repeats the last seed byte"
        );
    }

    #[test]
    fn long_match_class_copies_five_to_one_thousand_twenty_eight_bytes() {
        // Control 0xFD emits one literal, then control 0xC0 asks for 5 copies
        // (the class floor) at distance 1.
        let decoded = decompress(&stream(6, &[0xFD, 0x7E, 0xC0, 0x00, 0x00, 0x00])).unwrap();
        assert_eq!(decoded, run(6, 0x7E));

        // Ceiling: (c & 0x0C) << 6 == 768, plus b3 == 255, plus 5 -> 1028 copies.
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(b"abcd");
        tokens.extend_from_slice(&[0xC0 | 0x0C, 0x00, 0x00, 0xFF]);
        let decoded = decompress(&stream(1032, &tokens)).unwrap();
        assert_eq!(decoded.len(), 1032);
        assert!(decoded[4..].iter().all(|&b| b == b'd'));

        // The distance high bit lives in control bit 4 and contributes
        // `0x10 << 12 == 0x10000`, so exercising it needs 64 KiB of output
        // first. Control 0xD0, b1 = b2 = b3 = 0 gives distance 65537 and
        // 5 copies.
        let seed: Vec<u8> = (0..=0x1_0000u32).map(|i| i as u8).collect();
        let mut tokens = Vec::new();
        push_literals(&mut tokens, &seed);
        tokens.extend_from_slice(&[0xD0, 0x00, 0x00, 0x00]);
        let decoded = decompress(&stream(seed.len() + 5, &tokens)).unwrap();
        assert_eq!(decoded.len(), seed.len() + 5);
        assert_eq!(&decoded[..seed.len()], &seed[..]);
        assert_eq!(&decoded[seed.len()..], &seed[..5]);
    }

    #[test]
    fn literals_are_emitted_before_copies() {
        // One literal then three copies at distance 1: the source is the byte
        // just written, not the one before it.
        assert_eq!(
            decompress(&stream(4, &[0x01, 0x00, 0x2A])).unwrap(),
            run(4, 0x2A)
        );

        // Two literals 'A','B' then three copies at distance 2 repeat the pair,
        // proving the copies start after both literals, not after the first.
        let mut tokens = vec![0x02, 0x01];
        tokens.extend_from_slice(b"AB");
        assert_eq!(decompress(&stream(5, &tokens)).unwrap(), b"ABABA");
    }

    #[test]
    fn a_distance_equal_to_the_output_length_copies_the_first_byte() {
        // 8 bytes produced, then distance 8 -- legal, it copies out[0].
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(&run(4, 0x5A));
        tokens.push(0xE0);
        tokens.extend_from_slice(&run(4, 0x5A));
        // Control 0x80: (c & 0x3F) + 4 == 4 copies; b1 = 0, b2 = 7 give
        // distance 0 + 7 + 1 == 8 == produced.
        tokens.extend_from_slice(&[0x80, 0x00, 0x07]);
        assert_eq!(decompress(&stream(12, &tokens)).unwrap(), run(12, 0x5A));
    }

    #[test]
    fn a_self_referential_repeat_of_one_byte_is_legal() {
        // Control 0x1D: 1 literal, 10 copies (the class ceiling), distance 1.
        // The copy source is the literal, so this expands one byte into
        // eleven -- the legitimate `distance == produced` boundary case.
        let decoded = decompress(&stream(11, &[0x1D, 0x00, 0xC3])).unwrap();
        assert_eq!(decoded, run(11, 0xC3));
        assert_eq!(decoded.len(), 11);
    }

    // ---- failure paths ----------------------------------------------------

    #[test]
    fn a_token_stream_that_ends_before_the_control_byte_is_refused() {
        // Declares 8 bytes, supplies 4.
        let bytes = stream(8, &[0xE0, 1, 2, 3, 4]);
        assert_eq!(decompress(&bytes), Err(DbpfError::QfsTruncatedControlByte));
    }

    #[test]
    fn a_missing_operand_byte_names_its_token_class() {
        // Long match (needs 3), mid match (needs 2), short match (needs 1).
        assert_eq!(
            decompress(&stream(16, &[0xC0, 0x00])),
            Err(DbpfError::QfsTruncatedLongMatchToken)
        );
        assert_eq!(
            decompress(&stream(16, &[0x80, 0x00])),
            Err(DbpfError::QfsTruncatedMidMatchToken)
        );
        assert_eq!(
            decompress(&stream(16, &[0x40])),
            Err(DbpfError::QfsTruncatedShortMatchToken)
        );
    }

    #[test]
    fn a_literal_run_that_runs_off_the_input_is_refused() {
        // Control 0xFB asks for 112 literals; only 3 bytes follow.
        let bytes = stream(112, &[0xFB, 1, 2, 3]);
        assert_eq!(
            decompress(&bytes),
            Err(DbpfError::QfsTruncatedLiteralRun { literals: 112 })
        );
    }

    #[test]
    fn a_literal_run_that_passes_the_declared_size_is_refused() {
        // Declares 4 bytes; the token asks for 112 literals.
        let mut bytes = stream(4, &[0xFB]);
        bytes.extend_from_slice(&run(112, 0));
        assert_eq!(
            decompress(&bytes),
            Err(DbpfError::QfsTruncatedLiteralRun { literals: 112 })
        );
    }

    #[test]
    fn a_back_reference_before_the_output_start_is_refused() {
        // Nothing produced yet, so even distance 1 reaches before the start.
        assert_eq!(
            decompress(&stream(4, &[0x00, 0x00, 0xAA])),
            Err(DbpfError::QfsInvalidBackReference {
                distance: 1,
                produced: 0,
                copies: 3
            })
        );

        // One byte produced, distance 2 reaches before the start.
        assert_eq!(
            decompress(&stream(4, &[0xFD, 0x11, 0x00, 0x01])),
            Err(DbpfError::QfsInvalidBackReference {
                distance: 2,
                produced: 1,
                copies: 3
            })
        );
    }

    #[test]
    fn a_copy_run_past_the_declared_size_is_refused() {
        // 8 bytes produced with room for 2 more, then a short match asking for
        // 3: 8 + 3 > 10.
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(&run(4, 0x00));
        tokens.push(0xE0);
        tokens.extend_from_slice(&run(4, 0x00));
        tokens.extend_from_slice(&[0x00, 0x00]);
        assert_eq!(
            decompress(&stream(10, &tokens)),
            Err(DbpfError::QfsInvalidBackReference {
                distance: 1,
                produced: 8,
                copies: 3
            })
        );
    }

    #[test]
    fn a_copy_run_that_exactly_fills_the_output_is_accepted() {
        let mut tokens = vec![0xE0];
        tokens.extend_from_slice(&run(4, 0x11));
        tokens.push(0xE0);
        tokens.extend_from_slice(&run(4, 0x11));
        tokens.extend_from_slice(&[0x00, 0x00]);
        assert_eq!(decompress(&stream(11, &tokens)).unwrap(), run(11, 0x11));
    }

    #[test]
    fn trailing_bytes_after_the_declared_output_are_ignored() {
        let mut bytes = stream(4, &[0xE0, b'A', b'B', b'C', b'D']);
        bytes.extend_from_slice(&[0xFF, 0xFF, 0xFF]);
        assert_eq!(decompress(&bytes).unwrap(), b"ABCD");
    }

    #[test]
    fn no_input_length_panics() {
        // Exhaustive over every prefix of a valid stream and of a hostile one.
        let base = stream(16, &[0xE0, 1, 2, 3, 4, 0xE0, 5, 6, 7, 8, 0x40, 0x00]);
        for len in 0..=base.len() {
            let _ = decompress(&base[..len]);
        }
        let hostile: Vec<u8> = (0..=255u8).collect();
        for len in 0..=hostile.len() {
            let _ = decompress(&hostile[..len]);
        }
        // Also: every prefix of a stream whose declared size walks 0..=255 in
        // the low byte, so the 24-bit size field meets real token data.
        for low in 0..=255usize {
            let mut mutated = base.clone();
            mutated[5] = 0xE0;
            mutated[2] = 0;
            mutated[3] = 0;
            mutated[4] = low as u8;
            let _ = decompress(&mutated);
        }
    }

    #[test]
    fn compression_support_is_the_pair_none_and_qfs() {
        assert!(is_supported_compression(COMPRESSION_NONE));
        assert!(is_supported_compression(COMPRESSION_QFS));
        assert!(!is_supported_compression(1));
        assert!(!is_supported_compression(0xFFFE));
        assert!(!is_supported_compression(0x1234));
    }
}
