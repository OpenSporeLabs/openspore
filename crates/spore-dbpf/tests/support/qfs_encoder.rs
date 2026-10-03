#![allow(dead_code)]

//! A synthetic EA QFS (RefPack) **encoder**, written for the tests only.
//!
//! The decoder in `src/qfs.rs` has no encoder beside it on purpose: an encoder
//! that shares code with the decoder proves nothing, because a shared mistake
//! round-trips perfectly. This module is written from the token grammar in the
//! decoder's module docs — the *inverse* of each formula — so a
//! `decompress(compress(x)) == x` assertion is evidence about the token table
//! rather than about a shared helper.
//!
//! Each integration test binary compiles its own copy of this module, and not
//! every one of them exercises every token class, so unused items are allowed
//! rather than warned about.
//!
//! Every token emitter validates its arguments against the class's documented
//! range and panics on an out-of-range value. That is deliberate: this is test
//! code, so a mis-encoded token should fail the test loudly at the call site
//! rather than quietly produce a stream that happens to decode.

/// Lowest control byte of the "0..=3 literals, no copies" class.
pub const CTRL_SHORT_LITERALS: u8 = 252;
/// Lowest control byte of the "4..=112 literals" class.
pub const CTRL_LITERAL_RUN: u8 = 224;
/// Lowest control byte of the long-match class (3 operand bytes).
pub const CTRL_LONG_MATCH: u8 = 192;
/// Lowest control byte of the mid-match class (2 operand bytes).
pub const CTRL_MID_MATCH: u8 = 128;

/// Maximum literals in one `224..251` token.
pub const MAX_LITERAL_RUN: usize = 112;
/// Minimum literals in one `224..251` token.
pub const MIN_LITERAL_RUN: usize = 4;
/// Maximum literals in one `c >= 252` token.
pub const MAX_SHORT_LITERALS: usize = 3;

/// Copy-count range per class: `(min, max)`.
pub const SHORT_COPIES: (usize, usize) = (3, 10);
pub const MID_COPIES: (usize, usize) = (4, 67);
pub const LONG_COPIES: (usize, usize) = (5, 1028);

/// Maximum back-reference distance per class.
///
/// Each class stores its distance as a whole number of 256-byte units in the
/// control byte or `b1`, plus the remainder in the next byte:
/// `((c & 0x60) << 3)` is 0/256/512/768 for the short class, `((b1 & 0x3F) << 8)`
/// is 0..16128 for the mid class, and `((c & 0x10) << 12)` is a single 65536
/// unit for the long class. Hence 1024, 16384 and 131072.
pub const SHORT_DISTANCE: usize = 1024;
pub const MID_DISTANCE: usize = 16384;
pub const LONG_DISTANCE: usize = 131072;

/// Builds a QFS stream token by token.
///
/// `declared` is the decompressed size written into the header;
/// [`QfsWriter::finish`] asserts the tokens actually produced that many bytes,
/// so a stream can never claim a size it does not deliver.
#[derive(Debug)]
pub struct QfsWriter {
    tokens: Vec<u8>,
    declared: usize,
    produced: usize,
}

impl QfsWriter {
    /// Starts a stream that declares `declared_len` decompressed bytes.
    pub fn new(declared_len: usize) -> Self {
        assert!(declared_len <= 0x00FF_FFFF, "the declared size is 24 bits");
        Self {
            tokens: Vec::new(),
            declared: declared_len,
            produced: 0,
        }
    }

    /// `c < 128`: up to 3 literals then `copies` copies at `distance`.
    ///
    /// Control bits 2..4 hold `copies - 3`, bits 0..1 the literal count, and
    /// bits 5..6 hold the 256-byte units of `distance - 1`; the low 8 bits of
    /// the stored distance go in the operand byte.
    pub fn short_match(&mut self, literals: &[u8], copies: usize, distance: usize) -> &mut Self {
        assert!(
            copies >= SHORT_COPIES.0 && copies <= SHORT_COPIES.1,
            "short copies {copies}"
        );
        assert!(
            literals.len() <= MAX_SHORT_LITERALS,
            "short literals {}",
            literals.len()
        );
        assert!(
            (1..=SHORT_DISTANCE).contains(&distance),
            "short distance {distance}"
        );
        let stored = distance - 1;
        let control: u8 = (((copies - SHORT_COPIES.0) << 2) as u8)
            | (literals.len() as u8)
            | (((stored >> 8) as u8 & 0x03) << 5);
        assert!(
            control < CTRL_MID_MATCH,
            "short control {control} out of class"
        );
        self.tokens.push(control);
        self.tokens.push((stored & 0xFF) as u8);
        self.tokens.extend_from_slice(literals);
        self.produced += literals.len() + copies;
        self
    }

    /// `128 <= c < 192`: up to 3 literals then `copies` copies at `distance`.
    ///
    /// The 14-bit stored distance splits as 6 high bits in `b1`'s low nibble
    /// and 8 in `b2`; `b1`'s top two bits carry the literal count.
    pub fn mid_match(&mut self, literals: &[u8], copies: usize, distance: usize) -> &mut Self {
        assert!(
            copies >= MID_COPIES.0 && copies <= MID_COPIES.1,
            "mid copies {copies}"
        );
        assert!(
            literals.len() <= MAX_SHORT_LITERALS,
            "mid literals {}",
            literals.len()
        );
        assert!(
            (1..=MID_DISTANCE).contains(&distance),
            "mid distance {distance}"
        );
        let stored = distance - 1;
        let b1 = (literals.len() as u8) << 6 | ((stored >> 8) as u8 & 0x3F);
        let control = CTRL_MID_MATCH | (copies - MID_COPIES.0) as u8;
        self.tokens.push(control);
        self.tokens.push(b1);
        self.tokens.push((stored & 0xFF) as u8);
        self.tokens.extend_from_slice(literals);
        self.produced += literals.len() + copies;
        self
    }

    /// `192 <= c < 224`: up to 3 literals then `copies` copies at `distance`.
    ///
    /// The 17-bit stored distance splits as 1 high bit in control bit 4, 8 in
    /// `b1` and 8 in `b2`; `b3` plus control bits 2..3 carry the copy count.
    pub fn long_match(&mut self, literals: &[u8], copies: usize, distance: usize) -> &mut Self {
        assert!(
            copies >= LONG_COPIES.0 && copies <= LONG_COPIES.1,
            "long copies {copies}"
        );
        assert!(
            literals.len() <= MAX_SHORT_LITERALS,
            "long literals {}",
            literals.len()
        );
        assert!(
            (1..=LONG_DISTANCE).contains(&distance),
            "long distance {distance}"
        );
        let stored = distance - 1;
        // The decoder reads the copy count as `((c & 0x0C) << 6) + b3`, i.e.
        // whole 256-byte units in the control byte plus the low 8 bits in b3.
        let copies_stored = copies - LONG_COPIES.0;
        let control = CTRL_LONG_MATCH
            | (((copies_stored >> 8) as u8 & 0x03) << 2)
            | ((stored >> 16) as u8 & 0x01) << 4
            | (literals.len() as u8);
        assert!(
            control < CTRL_LITERAL_RUN,
            "long control {control} out of class"
        );
        self.tokens.push(control);
        self.tokens.push((stored >> 8) as u8);
        self.tokens.push((stored & 0xFF) as u8);
        self.tokens.push((copies_stored & 0xFF) as u8);
        self.tokens.extend_from_slice(literals);
        self.produced += literals.len() + copies;
        self
    }

    /// `224 <= c < 252`: `bytes.len()` literals, no copies.
    ///
    /// The class encodes `(n - 4) >> 2`, so `n` must be `4, 8, 12, ... 112`.
    pub fn literal_run(&mut self, bytes: &[u8]) -> &mut Self {
        assert!(
            bytes.len() >= MIN_LITERAL_RUN
                && bytes.len() <= MAX_LITERAL_RUN
                && (bytes.len() - MIN_LITERAL_RUN) % 4 == 0,
            "literal run of {} bytes (want 4, 8, ... 112)",
            bytes.len()
        );
        let control = CTRL_LITERAL_RUN + ((bytes.len() - MIN_LITERAL_RUN) >> 2) as u8;
        self.tokens.push(control);
        self.tokens.extend_from_slice(bytes);
        self.produced += bytes.len();
        self
    }

    /// `c >= 252`: 1..=3 literals, no copies.
    pub fn short_literals(&mut self, bytes: &[u8]) -> &mut Self {
        assert!(
            (1..=MAX_SHORT_LITERALS).contains(&bytes.len()),
            "short literal run of {} bytes (want 1..=3)",
            bytes.len()
        );
        self.tokens.push(CTRL_SHORT_LITERALS + bytes.len() as u8);
        self.tokens.extend_from_slice(bytes);
        self.produced += bytes.len();
        self
    }

    /// Bytes emitted so far, for a caller that wants to check its bookkeeping.
    pub fn produced(&self) -> usize {
        self.produced
    }

    /// The token bytes accumulated so far, without the header.
    pub fn tokens(&self) -> &[u8] {
        &self.tokens
    }

    /// Finishes the stream, checking that it delivers its declared size.
    pub fn finish(self) -> Vec<u8> {
        assert_eq!(
            self.produced, self.declared,
            "stream produces {} bytes but declares {}",
            self.produced, self.declared
        );
        let mut out = vec![0x10, 0xFB];
        out.push(((self.declared >> 16) & 0xFF) as u8);
        out.push(((self.declared >> 8) & 0xFF) as u8);
        out.push((self.declared & 0xFF) as u8);
        out.extend_from_slice(&self.tokens);
        out
    }
}

/// Wraps an already-built token stream in a header declaring `declared`.
pub fn wrap(declared: usize, tokens: &[u8]) -> Vec<u8> {
    assert!(declared <= 0x00FF_FFFF, "the declared size is 24 bits");
    let mut out = vec![0x10, 0xFB];
    out.push(((declared >> 16) & 0xFF) as u8);
    out.push(((declared >> 8) & 0xFF) as u8);
    out.push((declared & 0xFF) as u8);
    out.extend_from_slice(tokens);
    out
}

/// A greedy encoder: run tokens where they pay, literal runs otherwise.
///
/// Always succeeds for any payload, including the awkward tails (a 1..=3 byte
/// remainder is covered by the `c >= 252` class, and any run of 4 or more
/// identical bytes is covered by short-match tokens at distance 1).
pub fn compress(payload: &[u8]) -> Vec<u8> {
    let mut writer = QfsWriter::new(payload.len());
    let mut at = 0;
    while at < payload.len() {
        let run = identical_run(payload, at);
        if run >= 4 {
            encode_run(&mut writer, payload[at], run);
            at += run;
            continue;
        }
        // Take as many bytes as one literal-run token can carry, rounded down
        // to a multiple of 4 (the class's granularity). Whatever is left is
        // still encodable, because `literal_run_len` is never negative and a
        // 1..=3 byte remainder goes through `short_literals`.
        let mut take = payload.len() - at;
        if take >= MIN_LITERAL_RUN {
            take = take.min(MAX_LITERAL_RUN);
            take -= take % 4;
            writer.literal_run(&payload[at..at + take]);
        } else {
            writer.short_literals(&payload[at..]);
            take = payload.len() - at;
        }
        at += take;
    }
    writer.finish()
}

/// An encoder that emits only literal tokens, in maximal 112-byte chunks.
///
/// This reproduces the token stream `tests/fixtures/gen_fixtures.py` writes for
/// a payload it can encode, byte for byte, which is what lets a test pin the
/// committed fixture's stored bytes rather than only its decompressed ones.
/// It is deliberately *not* what [`compress`] does: the generator probes for a
/// run only at each token boundary, so it misses the 300-byte zero run that
/// begins at offset 112 of the fixture payload and emits literals instead.
pub fn compress_literal_runs(payload: &[u8]) -> Vec<u8> {
    let mut writer = QfsWriter::new(payload.len());
    let mut at = 0;
    while payload.len() - at >= MIN_LITERAL_RUN {
        let take = (payload.len() - at).min(MAX_LITERAL_RUN);
        let take = take - (take % 4);
        if take < MIN_LITERAL_RUN {
            break;
        }
        writer.literal_run(&payload[at..at + take]);
        at += take;
    }
    if at < payload.len() {
        writer.short_literals(&payload[at..]);
    }
    writer.finish()
}

/// The number of identical bytes starting at `at`.
fn identical_run(payload: &[u8], at: usize) -> usize {
    let first = payload[at];
    let mut len = 1;
    while at + len < payload.len() && payload[at + len] == first {
        len += 1;
    }
    len
}

/// Emits `count` identical bytes as short-match tokens at distance 1.
///
/// The first token carries the literal; every later token carries none and just
/// copies the byte the previous one left behind. So `count` bytes cost one
/// literal plus `count - 1` copies, and each token may carry 3..=10 copies.
fn encode_run(writer: &mut QfsWriter, byte: u8, count: usize) {
    let plan = run_copy_plan(count);
    let mut literals: &[u8] = &[byte];
    for copies in plan {
        writer.short_match(literals, copies, 1);
        literals = &[];
    }
}

/// Copy counts whose total is exactly `count - 1`, each in `3..=10`.
///
/// A remainder of 1 or 2 copies cannot be encoded on its own (the class floor
/// is 3), so when the remainder after a full 10-copy token would land on 1..=2
/// the token is shortened until the remainder is exactly 3.
fn run_copy_plan(count: usize) -> Vec<usize> {
    assert!(
        count >= 4,
        "run encoding needs at least 4 bytes, got {count}"
    );
    let mut remaining = count - 1;
    let mut plan = Vec::new();
    while remaining > SHORT_COPIES.1 {
        let after = remaining - SHORT_COPIES.1;
        let copies = if (1..=3).contains(&after) {
            // Land the remainder on exactly 3 copies.
            SHORT_COPIES.1 - (3 - after)
        } else {
            SHORT_COPIES.1
        };
        plan.push(copies);
        remaining -= copies;
    }
    assert!(
        remaining >= SHORT_COPIES.0,
        "run of {count} leaves {remaining} copies, below the class floor"
    );
    plan.push(remaining);
    // Only the first token carries a literal; the rest are pure copies.
    let total = 1 + plan.iter().sum::<usize>();
    assert_eq!(total, count, "run plan for {count} sums to {total}");
    plan
}
