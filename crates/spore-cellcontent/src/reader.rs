//! A bounds-checked little-endian cursor, and the counted-record extent rule.
//!
//! # Why the cursor cannot panic
//!
//! Every read goes through the private `take`, which uses slice indexing rather
//! than arithmetic offsets. A read past the end yields `0` and does not advance,
//! exactly like the C++ reference's `Reader` (which latches `ok() == false`).
//! Neither form panics, and neither form silently wraps: `checked_add` on the
//! offset means a `usize::MAX`-sized request is refused rather than wrapped to a
//! small one and read from the front of the buffer.
//!
//! That matters because this crate's contract is that **no input produces a
//! panic**, not merely that correct input decodes. The decoders check the
//! extent *before* reading any field, so an overrun cannot happen in practice;
//! the cursor is the second line of defence, and `tests/robustness.rs` feeds
//! every prefix length and several byte mutations through all twelve records to
//! keep it honest.
//!
//! # The extent rule
//!
//! Every counted record in this family carries its entry count in a header and
//! its entries immediately after. Two rules are possible and they are *not*
//! interchangeable:
//!
//! * [`SpanRule::ExactFit`] — `header + count * item == size`. Trailing bytes
//!   are a hard error: they are either a mis-parse or a record this build does
//!   not understand.
//! * [`SpanRule::FitsOnly`] — `header + count * item <= size`. Trailing bytes
//!   are tolerated and ignored.
//!
//! The C++ reference has both helpers (`spanMatches` and `countFits`) but, as
//! measured, its *binding* check is `spanMatches` for every record it decodes,
//! and every Python oracle that decodes a counted record
//! (`tools/spore/cellres/{cellworld,cellpop,cellstruct,cellloot,celleffectmap,celllook,randcreature}.py`)
//! writes `if len(blob) != header + n * size: raise`. Each record publishes its
//! own rule as an associated `const SPAN_RULE`, and
//! `tests/decode.rs::every_record_publishes_its_span_rule` pins the mapping.
//! See the crate documentation for the full finding.

use crate::error::CellContentError;

/// How a counted record's header count relates to the record's length.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum SpanRule {
    /// `header + count * item_size` must equal the record length exactly.
    ExactFit,
    /// `header + count * item_size` must be at most the record length; any
    /// remainder is ignored.
    FitsOnly,
}

impl SpanRule {
    /// The canonical spelling used in claims and error messages.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::ExactFit => "exact-fit",
            Self::FitsOnly => "fits-only",
        }
    }
}

/// Decides whether a counted record's declared extent is acceptable.
///
/// `count` is the raw `i32` read out of the header, so a negative count is
/// refused by name rather than being reinterpreted as an enormous `u32` — the
/// same refusal both oracles make, and the reason a corrupt count cannot ask
/// this function to walk a four-gigabyte span.
pub fn check_span(
    rule: SpanRule,
    type_id: u32,
    field: &'static str,
    header_len: usize,
    item_size: usize,
    count: i32,
    size: usize,
) -> Result<usize, CellContentError> {
    if count < 0 {
        return Err(CellContentError::NegativeCount {
            type_id,
            field,
            count,
        });
    }
    let count = count as u64;
    let needed = header_len as u64 + count * item_size as u64;
    let size = size as u64;
    match rule {
        SpanRule::ExactFit if needed > size => Err(CellContentError::CountTooLarge {
            type_id,
            field,
            count: count as u32,
            item_size,
            needed: needed as usize,
            available: size as usize,
        }),
        SpanRule::ExactFit if needed < size => Err(CellContentError::TrailingBytes {
            type_id,
            field,
            count: count as u32,
            trailing: (size - needed) as usize,
        }),
        SpanRule::FitsOnly if needed > size => Err(CellContentError::CountTooLarge {
            type_id,
            field,
            count: count as u32,
            item_size,
            needed: needed as usize,
            available: size as usize,
        }),
        SpanRule::ExactFit | SpanRule::FitsOnly => Ok(needed as usize),
    }
}

/// A non-panicking little-endian cursor over a byte slice.
#[derive(Debug, Clone)]
pub(crate) struct Reader<'a> {
    data: &'a [u8],
    pos: usize,
}

impl<'a> Reader<'a> {
    /// Starts at offset zero.
    pub(crate) fn new(data: &'a [u8]) -> Self {
        Self { data, pos: 0 }
    }

    /// The current byte offset.
    pub(crate) fn offset(&self) -> usize {
        self.pos
    }

    /// Borrows `n` bytes and advances, or yields `None` and does not move.
    fn take(&mut self, n: usize) -> Option<&'a [u8]> {
        let end = self.pos.checked_add(n)?;
        let slice = self.data.get(self.pos..end)?;
        self.pos = end;
        Some(slice)
    }

    /// One byte, or `0` past the end.
    pub(crate) fn u8(&mut self) -> u8 {
        self.take(1).map_or(0, |s| s[0])
    }

    /// Three bytes, or zero past the end.
    pub(crate) fn skip(&mut self, n: usize) {
        let _ = self.take(n);
    }

    /// Three raw bytes of alignment padding, or three zeros past the end.
    pub(crate) fn bytes3(&mut self) -> [u8; 3] {
        self.take(3).map_or([0u8; 3], |s| [s[0], s[1], s[2]])
    }

    /// A little-endian `u16`, or `0` past the end.
    pub(crate) fn u16(&mut self) -> u16 {
        self.take(2).map_or(0, |s| u16::from_le_bytes([s[0], s[1]]))
    }

    /// A little-endian `u32`, or `0` past the end.
    pub(crate) fn u32(&mut self) -> u32 {
        self.take(4)
            .map_or(0, |s| u32::from_le_bytes([s[0], s[1], s[2], s[3]]))
    }

    /// A little-endian `i32`, or `0` past the end.
    pub(crate) fn i32(&mut self) -> i32 {
        self.u32() as i32
    }

    /// A little-endian `f32`, or `0.0` past the end.
    pub(crate) fn f32(&mut self) -> f32 {
        f32::from_bits(self.u32())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_reader_past_its_end_reads_zero_and_does_not_move() {
        let mut r = Reader::new(&[0xff, 0xff, 0xff, 0xff]);
        assert_eq!(r.u32(), 0xffff_ffff);
        assert_eq!(r.offset(), 4);
        assert_eq!(r.u32(), 0, "past the end reads zero");
        assert_eq!(r.offset(), 4, "and does not advance");
        assert_eq!(r.f32(), 0.0);
        assert_eq!(r.i32(), 0);
    }

    #[test]
    fn an_absurd_request_is_refused_rather_than_wrapped() {
        let mut r = Reader::new(&[0x11, 0x22, 0x33, 0x44]);
        assert!(r.take(usize::MAX).is_none());
        assert_eq!(r.offset(), 0, "a refused read must not move the cursor");
        assert_eq!(r.u16(), 0x2211);
    }

    #[test]
    fn span_rule_exact_fit_accepts_only_an_exact_length() {
        let ok = check_span(SpanRule::ExactFit, 1, "n", 8, 28, 2, 8 + 2 * 28);
        assert_eq!(ok, Ok(64));
        assert!(check_span(SpanRule::ExactFit, 1, "n", 8, 28, 2, 65).is_err());
        assert!(check_span(SpanRule::ExactFit, 1, "n", 8, 28, 3, 64).is_err());
    }

    #[test]
    fn span_rule_fits_only_tolerates_a_remainder() {
        assert_eq!(check_span(SpanRule::FitsOnly, 1, "n", 8, 28, 2, 64), Ok(64));
        assert_eq!(check_span(SpanRule::FitsOnly, 1, "n", 8, 28, 2, 65), Ok(64));
        assert!(check_span(SpanRule::FitsOnly, 1, "n", 8, 28, 3, 64).is_err());
    }

    #[test]
    fn a_negative_count_is_refused_before_it_can_be_a_huge_span() {
        assert_eq!(
            check_span(SpanRule::ExactFit, 0x1234, "numMarkers", 16, 76, -1, 16),
            Err(CellContentError::NegativeCount {
                type_id: 0x1234,
                field: "numMarkers",
                count: -1,
            })
        );
    }
}
