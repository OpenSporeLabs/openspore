//! QFS token round-trips in both directions.
//!
//! `src/qfs.rs` proves the decoder handles hand-built streams and rejects
//! corrupt ones. This file proves the token table is *symmetric*: a separate
//! encoder, written from the grammar in the decoder's module docs, emits a
//! control byte and operands for each of the five classes, and
//! `decompress(compress(x)) == x` holds for every class and for the awkward
//! payload shapes (pure literals, pure runs, a 1..=3 byte tail, a payload with
//! no matchable content at all).
//!
//! The encoder is `tests/support/qfs_encoder.rs` and shares no code with the
//! decoder. A round-trip that passes is therefore evidence about the token
//! formulas, not about a helper both sides happen to agree on.

mod support;

use spore_dbpf::{decompress, DbpfError, QFS_HEADER_SIZE};

use support::qfs_encoder::{
    compress, compress_literal_runs, wrap, QfsWriter, LONG_COPIES, LONG_DISTANCE, MAX_LITERAL_RUN,
    MAX_SHORT_LITERALS, MID_COPIES, MID_DISTANCE, SHORT_COPIES, SHORT_DISTANCE,
};

/// A run of `n` identical bytes.
fn run(n: usize, b: u8) -> Vec<u8> {
    vec![b; n]
}

/// Emits `seed` as 4-literal tokens plus a 0..=3 byte literal tail.
fn seed_writer(seed: &[u8], extra: usize) -> QfsWriter {
    let mut writer = QfsWriter::new(seed.len() + extra);
    let mut at = 0;
    while seed.len() - at >= 4 {
        writer.literal_run(&seed[at..at + 4]);
        at += 4;
    }
    writer
}

/// The 0..=3 seed bytes a match token still has to carry itself.
fn seed_tail(seed: &[u8]) -> &[u8] {
    let at = seed.len() - seed.len() % 4;
    &seed[at..]
}

/// Every payload shape a round-trip is run against.
fn corpus() -> Vec<Vec<u8>> {
    vec![
        // Empty.
        Vec::new(),
        // The awkward short payloads: 1..=3 bytes go through the `c >= 252`
        // class, the only one that can express them.
        vec![0x42],
        vec![0x42, 0x43],
        vec![0x42, 0x43, 0x44],
        // Exactly one literal-run token, and one chunk past its ceiling.
        run(4, 0x11),
        run(MAX_LITERAL_RUN, 0x22),
        run(MAX_LITERAL_RUN + 4, 0x23),
        // Pure runs of one byte: the self-referential distance-1 expansion at
        // every run-plan remainder the encoder's planner can produce.
        run(4, 0x7E),
        run(5, 0x7E),
        run(11, 0x7E),
        run(12, 0x7E),
        run(13, 0x7E),
        run(14, 0x7E),
        run(15, 0x7E),
        run(300, 0x00),
        run(1024, 0xAB),
        // Incompressible: 256 distinct bytes, so every token is a literal run.
        (0..=255u8).collect(),
        // Alternating: no run long enough to tokenise and no repeat long enough
        // to copy across, so this is literal-only with a mixed tail.
        (0..255u16)
            .map(|i| if i % 2 == 0 { 0xAA } else { 0x55 })
            .collect(),
        // The committed fixture's payload: 112 distinct bytes then 300 zeros.
        {
            let mut payload: Vec<u8> = (0..112u8).collect();
            payload.extend(std::iter::repeat_n(0u8, 300));
            payload
        },
    ]
}

#[test]
fn the_greedy_encoder_round_trips_the_whole_corpus() {
    for payload in corpus() {
        let stream = compress(&payload);
        assert_eq!(
            decompress(&stream).unwrap(),
            payload,
            "round-trip failed for a {} byte payload",
            payload.len()
        );
    }
}

#[test]
fn the_literal_run_encoder_round_trips_the_whole_corpus() {
    for payload in corpus() {
        let stream = compress_literal_runs(&payload);
        assert_eq!(
            decompress(&stream).unwrap(),
            payload,
            "{} bytes",
            payload.len()
        );
    }
}

#[test]
fn a_pure_literal_run_uses_one_literal_token() {
    // 112 distinct bytes: exactly one `224..251` token, nothing else.
    let payload: Vec<u8> = (0..112u8).collect();
    let stream = compress(&payload);
    assert_eq!(stream.len(), QFS_HEADER_SIZE + 1 + 112);
    assert_eq!(stream[5], 251, "control 224 + (112 - 4) / 4 = 251");
    assert_eq!(decompress(&stream).unwrap(), payload);
}

#[test]
fn a_pure_match_run_uses_only_short_match_tokens_at_distance_one() {
    // 64 identical bytes cost one literal plus 63 copies, and a short-match
    // token carries at most 10, so this is 7 tokens: six of 11 bytes and one of
    // 10.
    let payload = run(64, 0x5A);
    let stream = compress(&payload);
    assert_eq!(stream.len(), QFS_HEADER_SIZE + 7 * 2 + 1);
    assert_eq!(decompress(&stream).unwrap(), payload);

    // The first token carries the literal; the rest carry none, so the literal
    // count in their control byte is zero. Walking the tokens is the only way
    // to find them: the first is three bytes long (control, operand, literal)
    // and the rest are two.
    // Walk the tokens: the first is three bytes long (control, operand, its one
    // literal) and the rest are two. Control bits 0..1 are the literal count
    // and bits 2..4 are `copies - 3`, so this reads the plan back out.
    assert_eq!(stream[5] & 0x03, 1, "one literal in the first token");
    let mut at = 5 + 3;
    let mut copies = 3 + ((stream[5] >> 2) & 0x07) as usize;
    let mut pure = 0;
    while at < stream.len() {
        assert_eq!(stream[at] & 0x03, 0, "token at {at} should be pure copies");
        assert_eq!(stream[at + 1], 0x00, "token at {at}: distance 1");
        copies += 3 + ((stream[at] >> 2) & 0x07) as usize;
        pure += 1;
        at += 2;
    }
    assert_eq!(pure, 6, "six pure-copy tokens carry the other 63 bytes");
    assert_eq!(
        copies, 63,
        "one literal plus 63 copies is the whole 64-byte run"
    );
}

#[test]
fn a_self_referential_repeat_expands_one_byte() {
    // One literal, then the class maximum of 10 copies at distance 1.
    let mut writer = QfsWriter::new(11);
    writer.short_match(&[0xC3], SHORT_COPIES.1, 1);
    assert_eq!(decompress(&writer.finish()).unwrap(), run(11, 0xC3));

    // Every copy count the short class allows, at distance 1.
    for copies in SHORT_COPIES.0..=SHORT_COPIES.1 {
        let mut writer = QfsWriter::new(1 + copies);
        writer.short_match(&[0x01], copies, 1);
        assert_eq!(decompress(&writer.finish()).unwrap(), run(1 + copies, 0x01));
    }
}

#[test]
fn the_short_match_class_round_trips_its_whole_range() {
    for copies in SHORT_COPIES.0..=SHORT_COPIES.1 {
        // 1, 2 and 3 also exercise the 0..=3 literal slot of the control byte
        // and the 3-bit distance operand; the rest straddle the operand
        // boundaries at 8 and the class ceiling at 2048.
        for distance in [1usize, 2, 3, 4, 7, 8, 9, 100, SHORT_DISTANCE] {
            let seed = run(distance, 0x9E);
            let mut writer = seed_writer(&seed, copies);
            writer.short_match(seed_tail(&seed), copies, distance);
            let expected = run(seed.len() + copies, 0x9E);
            assert_eq!(
                decompress(&writer.finish()).unwrap(),
                expected,
                "d={distance} n={copies}"
            );
        }
    }
}

#[test]
fn the_mid_match_class_round_trips_its_whole_range() {
    for copies in MID_COPIES.0..=MID_COPIES.1 {
        // Straddles the literal-count bits of `b1` (needs 3 literals), the
        // 6-bit distance high field at 64, the `b2` boundary at 256, and the
        // class ceiling.
        for distance in [1usize, 2, 3, 63, 64, 65, 256, 257, MID_DISTANCE] {
            let seed = run(distance, 0x3C);
            let mut writer = seed_writer(&seed, copies);
            writer.mid_match(seed_tail(&seed), copies, distance);
            let expected = run(seed.len() + copies, 0x3C);
            assert_eq!(
                decompress(&writer.finish()).unwrap(),
                expected,
                "d={distance} n={copies}"
            );
        }
    }
}

#[test]
fn the_long_match_class_round_trips_its_whole_range() {
    for copies in [LONG_COPIES.0, 6, 260, 1027, LONG_COPIES.1] {
        // Straddles the `b3` boundary at 256, the copy-count high bits in
        // control bits 2..3, and the distance high bit at 0x10000.
        for distance in [1usize, 2, 3, 255, 256, 257, 65536, 65537, LONG_DISTANCE] {
            let seed = run(distance, 0x77);
            let mut writer = seed_writer(&seed, copies);
            writer.long_match(seed_tail(&seed), copies, distance);
            let expected = run(seed.len() + copies, 0x77);
            assert_eq!(
                decompress(&writer.finish()).unwrap(),
                expected,
                "d={distance} n={copies}"
            );
        }
    }
}

#[test]
fn every_literal_count_of_the_short_class_round_trips() {
    for literals in 1..=MAX_SHORT_LITERALS {
        let mut writer = QfsWriter::new(literals);
        writer.short_literals(&[0xAA, 0xBB, 0xCC][..literals]);
        let expected: Vec<u8> = [0xAA, 0xBB, 0xCC][..literals].to_vec();
        assert_eq!(decompress(&writer.finish()).unwrap(), expected);
    }
}

#[test]
fn every_literal_run_length_of_its_class_round_trips() {
    for count in (4..=MAX_LITERAL_RUN).step_by(4) {
        let payload: Vec<u8> = (0..count).map(|i| (i * 31) as u8).collect();
        let mut writer = QfsWriter::new(count);
        writer.literal_run(&payload);
        assert_eq!(
            decompress(&writer.finish()).unwrap(),
            payload,
            "{count} literals"
        );
    }
}

#[test]
fn a_mixed_stream_of_all_five_classes_round_trips() {
    // One token of each class, in class order, against a growing output:
    //   1. 112 literals                      (`224..251`)
    //   2. 2 literals                        (`c >= 252`)
    //   3. 1 literal + 4 copies at distance 1 (`c < 128`)
    //   4. 4 literals + 4 copies at distance 4 (`128 <= c < 192`)
    //   5. 3 literals + 6 copies at distance 3 (`192 <= c < 224`)
    let mut expected: Vec<u8> = Vec::new();
    let mut tokens: Vec<u8> = Vec::new();

    let head: Vec<u8> = (0..112u8).collect();
    let mut writer = QfsWriter::new(head.len());
    writer.literal_run(&head);
    tokens.extend_from_slice(writer.tokens());
    expected.extend_from_slice(&head);

    let mut writer = QfsWriter::new(2);
    writer.short_literals(&[0xDE, 0xAD]);
    tokens.extend_from_slice(writer.tokens());
    expected.extend_from_slice(&[0xDE, 0xAD]);

    let mut writer = QfsWriter::new(5);
    writer.short_match(&[0xF0], 4, 1);
    tokens.extend_from_slice(writer.tokens());
    expected.extend_from_slice(&run(5, 0xF0));

    // 3 literals (the class maximum) + 5 copies at distance 3.
    let triple = [0x11, 0x22, 0x33];
    let mut writer = QfsWriter::new(8);
    writer.mid_match(&triple, 5, 3);
    tokens.extend_from_slice(writer.tokens());
    expected.extend_from_slice(&triple);
    expected.extend_from_slice(&triple[..3]);
    expected.extend_from_slice(&triple[..2]);

    let mut writer = QfsWriter::new(9);
    writer.long_match(&[0x99, 0x99, 0x99], 6, 3);
    tokens.extend_from_slice(writer.tokens());
    expected.extend_from_slice(&[0x99; 9]);

    assert_eq!(expected.len(), 112 + 2 + 5 + 8 + 9);
    assert_eq!(
        decompress(&wrap(expected.len(), &tokens)).unwrap(),
        expected
    );
}

// ---- the encoder's own boundaries -----------------------------------------

#[test]
#[should_panic(expected = "short copies")]
fn the_encoder_refuses_an_out_of_class_copy_count() {
    let mut writer = QfsWriter::new(4);
    writer.short_match(&[], SHORT_COPIES.0 - 1, 1);
}

#[test]
#[should_panic(expected = "mid distance")]
fn the_encoder_refuses_an_out_of_class_distance() {
    let mut writer = QfsWriter::new(8);
    writer.mid_match(&[], 4, MID_DISTANCE + 1);
}

#[test]
#[should_panic(expected = "literal run of 5 bytes")]
fn the_encoder_refuses_a_literal_run_the_class_cannot_express() {
    let mut writer = QfsWriter::new(5);
    writer.literal_run(&[0, 1, 2, 3, 4]);
}

#[test]
#[should_panic(expected = "but declares")]
fn the_encoder_refuses_to_declare_a_size_it_does_not_produce() {
    let mut writer = QfsWriter::new(99);
    writer.literal_run(&[0, 1, 2, 3]);
    let _ = writer.finish();
}

// ---- error paths, restated against encoder output ------------------------

#[test]
fn a_stream_whose_tokens_stop_short_of_the_declared_size_is_refused() {
    let mut writer = QfsWriter::new(8);
    writer.literal_run(&[1, 2, 3, 4]);
    writer.literal_run(&[5, 6, 7, 8]);
    let full = writer.finish();
    assert_eq!(decompress(&full).unwrap(), [1, 2, 3, 4, 5, 6, 7, 8]);

    // Keep the header (still declaring 8) and the first token, drop the second.
    let mut truncated = full.clone();
    truncated.truncate(QFS_HEADER_SIZE + 5);
    assert_eq!(
        decompress(&truncated),
        Err(DbpfError::QfsTruncatedControlByte)
    );
    // Keep part of the second token's literals: a literal run, not a control
    // byte, is what runs out.
    let mut cut = full.clone();
    cut.truncate(full.len() - 2);
    assert_eq!(
        decompress(&cut),
        Err(DbpfError::QfsTruncatedLiteralRun { literals: 4 })
    );
}

#[test]
fn a_back_reference_the_encoder_cannot_produce_is_still_refused() {
    // The encoder always seeds at least `distance` bytes, so this rejection is
    // reachable only by hand -- which is exactly why the decoder needs it.
    assert_eq!(
        decompress(&wrap(4, &[0x00, 0x00, 0xAA])),
        Err(DbpfError::QfsInvalidBackReference {
            distance: 1,
            produced: 0,
            copies: 3
        })
    );
}
