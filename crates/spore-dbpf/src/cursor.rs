//! A bounds-checked little-endian read cursor.
//!
//! Every read returns `Option` instead of panicking, which is what lets the
//! library keep its promise of `#![forbid(unsafe_code)]` *and* "no panic on
//! hostile input": there is no code path that can index past the end of a
//! slice, and no code path that has to prove it cannot before indexing.
//!
//! This mirrors `src/assets/Stream.hpp`'s `Reader` in the C++ tree: reads
//! latch a failure flag and the caller checks once at the end. Rust's `Option`
//! makes the check local instead of latched, which is strictly more precise
//! (the C++ has to clear the whole entry vector when a *late* row read fails,
//! even though earlier rows were fine).

/// A forward-only cursor over a byte slice.
#[derive(Debug, Clone)]
pub(crate) struct Cursor<'a> {
    data: &'a [u8],
    pos: usize,
}

impl<'a> Cursor<'a> {
    /// Starts a cursor at `pos`. `pos` beyond `data` is tolerated: the first
    /// read simply reports "truncated", which is the same observable outcome
    /// as starting exactly at the end.
    pub(crate) fn new(data: &'a [u8], pos: usize) -> Self {
        Self { data, pos }
    }

    /// Bytes left to read. Saturating because `pos` can be seeded out of range.
    pub(crate) fn remaining(&self) -> usize {
        self.data.len().saturating_sub(self.pos)
    }

    /// Borrows the next `n` bytes and advances past them.
    pub(crate) fn take(&mut self, n: usize) -> Option<&'a [u8]> {
        let end = self.pos.checked_add(n)?;
        let slice = self.data.get(self.pos..end)?;
        self.pos = end;
        Some(slice)
    }

    /// Reads one byte.
    pub(crate) fn u8(&mut self) -> Option<u8> {
        let byte = self.data.get(self.pos).copied()?;
        self.pos += 1;
        Some(byte)
    }

    /// Reads a little-endian `u16`.
    pub(crate) fn u16_le(&mut self) -> Option<u16> {
        let bytes = self.take(2)?;
        let [low, high] = bytes.try_into().ok()?;
        Some(u16::from_le_bytes([low, high]))
    }

    /// Reads a little-endian `u32`.
    pub(crate) fn u32_le(&mut self) -> Option<u32> {
        let bytes = self.take(4)?;
        let [b0, b1, b2, b3] = bytes.try_into().ok()?;
        Some(u32::from_le_bytes([b0, b1, b2, b3]))
    }
}

/// Copies `N` bytes starting at `at` into an array, or `None` when the slice
/// is shorter than `at + N`.
///
/// The `checked_add` is what makes this total on a 32-bit host, where
/// `at + N` could otherwise wrap and hand back a plausible-looking window.
pub(crate) fn array_at<const N: usize>(data: &[u8], at: usize) -> Option<[u8; N]> {
    let end = at.checked_add(N)?;
    data.get(at..end)?.try_into().ok()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn reads_little_endian_values() {
        let data = [0x01, 0x02, 0x03, 0x04, 0x05, 0x06];
        let mut cur = Cursor::new(&data, 0);
        assert_eq!(cur.u32_le(), Some(0x0403_0201));
        assert_eq!(cur.pos, 4);
        assert_eq!(cur.u16_le(), Some(0x0605));
        assert_eq!(cur.remaining(), 0);
        assert_eq!(cur.u8(), None);
    }

    #[test]
    fn truncated_reads_report_none_instead_of_panicking() {
        let data = [0x01, 0x02, 0x03];
        let mut cur = Cursor::new(&data, 0);
        assert_eq!(cur.u32_le(), None);
        // A failed read must not advance the cursor: the C++ `Reader` also
        // leaves `pos_` alone, so the caller's row accounting stays aligned.
        assert_eq!(cur.pos, 0);
        assert_eq!(cur.take(3).map(<[u8]>::len), Some(3));
        assert_eq!(cur.take(1), None);
    }

    #[test]
    fn a_cursor_seeded_past_the_end_reads_nothing() {
        let data = [0x00, 0x01];
        let mut cur = Cursor::new(&data, 9);
        assert_eq!(cur.remaining(), 0);
        assert_eq!(cur.u8(), None);
        assert_eq!(
            cur.take(0),
            None,
            "a cursor past the end has nothing to take"
        );

        // A zero-length take at the exact end is the empty slice, not a failure.
        let mut at_end = Cursor::new(&data, data.len());
        assert_eq!(at_end.take(0).map(<[u8]>::len), Some(0));
    }

    #[test]
    fn array_at_is_bounds_checked_at_both_ends() {
        let data = [0xAA, 0xBB, 0xCC, 0xDD];
        assert_eq!(array_at::<4>(&data, 0), Some([0xAA, 0xBB, 0xCC, 0xDD]));
        assert_eq!(array_at::<2>(&data, 3), None);
        assert_eq!(array_at::<1>(&data, 3), Some([0xDD]));
        assert_eq!(array_at::<4>(&data, usize::MAX), None);
    }
}
