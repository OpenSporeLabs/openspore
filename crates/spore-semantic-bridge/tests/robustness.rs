//! No input panics: every malformed line yields a typed error.
//!
//! The list below is deliberately unglamorous. Truncation, blank lines, a JSON
//! scalar where a record belongs, a valid record followed by a second JSON value
//! on one line — these are the shapes a half-written file or a bad pipe produces,
//! and the boundary a sibling project reads through must survive all of them.

mod support;

use spore_semantic_bridge::{BridgeError, Snapshot};
use support::{metadata_line, record, snapshot_file, TempFile};

fn open(contents: &str) -> Result<Snapshot, BridgeError> {
    let file = TempFile::new("robust", contents);
    Snapshot::open(file.path())
}

/// A snapshot whose single record line is `body`, with the metadata line intact.
fn open_body(body: &str) -> Result<Snapshot, BridgeError> {
    open(&format!("{}\n{body}\n", metadata_line(1, &"0".repeat(64))))
}

fn assert_typed(error: BridgeError, what: &str) {
    let text = error.to_string();
    assert!(!text.is_empty(), "{what}: an error must say something");
    match error {
        BridgeError::Corrupt { .. } | BridgeError::UnsupportedSchema { .. } => {}
        other => panic!("{what}: expected a typed refusal, got {other:?}"),
    }
}

#[test]
fn a_truncated_record_is_refused() {
    let full = record("0x00401000", "0x00001000", 10);
    for cut in [1usize, 20, 60, 120, 300, 600] {
        let truncated = &full[..cut.min(full.len())];
        let error = open_body(truncated).expect_err("must be refused");
        assert_typed(error, &format!("cut at {cut}"));
    }
}

#[test]
fn a_record_with_no_terminator_at_end_of_file_is_read() {
    // Not an error: the last line of a file need not end in a newline, and the Go
    // loader accepts one. The digest still covers it, because the reader adds
    // the terminator the file did not have.
    let contents = format!(
        "{}\n{}",
        metadata_line(1, &"0".repeat(64)),
        record("0x00401000", "0x00001000", 10)
    );
    let file = TempFile::new("robust", &contents);
    let snapshot = Snapshot::open(file.path()).expect("a final line without a newline is valid");
    assert_eq!(snapshot.function_count(), 1);
    assert_eq!(
        snapshot
            .lookup(0x0040_1000)
            .expect("readable")
            .canonical_va(),
        0x0040_1000
    );
    match snapshot.verify() {
        Err(BridgeError::ContentDigestMismatch {
            declared, computed, ..
        }) => {
            assert_eq!(declared, "0".repeat(64));
            assert_eq!(computed.len(), 64);
        }
        other => panic!("expected a digest mismatch, got {other:?}"),
    }
}

#[test]
fn a_blank_or_whitespace_only_line_is_refused() {
    for blank in ["", " ", "\t", "   \t  "] {
        let contents = format!(
            "{}\n{}\n{}\n",
            metadata_line(1, &"0".repeat(64)),
            blank,
            record("0x00401010", "0x00001010", 10)
        );
        let error = open(&contents).expect_err("must be refused");
        match error {
            BridgeError::Corrupt { line, detail, .. } => {
                assert_eq!(line, 2, "the blank line is line 2");
                assert!(detail.contains("blank"), "{detail}");
            }
            other => panic!("expected corruption, got {other:?}"),
        }
    }
}

#[test]
fn a_json_scalar_where_a_record_belongs_is_refused() {
    for scalar in [
        "7",
        "-3",
        "\"function\"",
        "true",
        "null",
        "[]",
        "[{\"canonical_va\":\"0x00401000\"}]",
    ] {
        let error = open_body(scalar).expect_err("must be refused");
        match error {
            BridgeError::UnsupportedSchema { line, .. } => assert_eq!(line, 2, "{scalar}"),
            other => panic!("{scalar}: expected a schema refusal, got {other:?}"),
        }
    }
}

#[test]
fn two_json_values_on_one_line_are_refused() {
    let contents = format!(
        "{}\n{} {}\n",
        metadata_line(2, &"0".repeat(64)),
        record("0x00401000", "0x00001000", 10),
        record("0x00401010", "0x00001010", 10)
    );
    let error = open(&contents).expect_err("must be refused");
    match error {
        BridgeError::Corrupt { line, detail, .. } => {
            assert_eq!(line, 2);
            assert!(detail.contains("more than one JSON value"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn invalid_utf8_in_a_record_is_refused() {
    let file = TempFile::new(
        "utf8",
        &format!(
            "{}\n{}\n",
            metadata_line(1, &"0".repeat(64)),
            record("0x00401000", "0x00001000", 10)
        ),
    );
    // Overwrite one byte of the record line with a lone continuation byte.
    let mut bytes = std::fs::read(file.path()).expect("the fixture reads");
    let position = bytes.len() - 20;
    bytes[position] = 0xff;
    std::fs::write(file.path(), &bytes).expect("the fixture is writable");
    match Snapshot::open(file.path()) {
        Err(BridgeError::Corrupt { detail, .. }) => {
            assert!(detail.contains("UTF-8"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn a_metadata_line_that_is_not_an_object_is_refused() {
    for header in ["[]", "7", "\"metadata\"", "{}", "null"] {
        let contents = format!("{header}\n{}\n", record("0x00401000", "0x00001000", 10));
        let error = open(&contents).expect_err("must be refused");
        assert_typed(error, header);
    }
}

#[test]
fn a_metadata_line_without_a_binary_identity_is_refused() {
    let header = metadata_line(1, &"0".repeat(64))
        .replace(
            "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
            "NOT-HEX",
        )
        .replace(
            "\"image_base\":\"0x00400000\"",
            "\"image_base\":\"not a number\"",
        );
    let contents = format!("{header}\n{}\n", record("0x00401000", "0x00001000", 10));
    match open(&contents) {
        Err(BridgeError::Corrupt {
            line: 1, detail, ..
        }) => {
            assert!(detail.contains("binary_sha256"), "{detail}");
        }
        other => panic!("expected corruption on line 1, got {other:?}"),
    }
}

#[test]
fn a_metadata_line_with_a_non_canonical_image_base_is_refused() {
    let header = metadata_line(1, &"0".repeat(64))
        .replace("\"image_base\":\"0x00400000\"", "\"image_base\":\"400000\"");
    let contents = format!("{header}\n{}\n", record("0x00401000", "0x00001000", 10));
    match open(&contents) {
        Err(BridgeError::Corrupt {
            line: 1, detail, ..
        }) => {
            assert!(detail.contains("image_base"), "{detail}");
        }
        other => panic!("expected corruption on line 1, got {other:?}"),
    }
}

#[test]
fn a_file_with_metadata_but_no_records_is_refused() {
    let contents = format!("{}\n", metadata_line(0, &"0".repeat(64)));
    match open(&contents) {
        Err(BridgeError::Corrupt { detail, .. }) => {
            assert!(detail.contains("no function records"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn a_missing_trailing_newline_and_a_missing_final_record_are_different_failures() {
    // A file that ends mid-record is corruption at the line it ends on.
    let full = record("0x00401000", "0x00001000", 10);
    let contents = format!(
        "{}\n{}\n{}",
        metadata_line(2, &"0".repeat(64)),
        full,
        &full[..200]
    );
    match open(&contents) {
        Err(BridgeError::Corrupt { line, .. }) => assert_eq!(line, 3),
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn every_refusal_carries_a_file_and_a_line() {
    let contents = format!(
        "{}\n{}\n",
        metadata_line(2, &"0".repeat(64)),
        "{\"record\":\"function\"}"
    );
    match open(&contents) {
        Err(error) => {
            let text = error.to_string();
            assert!(text.contains("robust"), "{text}");
            assert!(text.contains(":2:"), "the line is in the message: {text}");
        }
        Ok(_) => panic!("a stub record must not open"),
    }
}

#[test]
fn a_snapshot_that_changes_after_it_is_opened_is_reported_not_mis_served() {
    // The index records each line's length, so a file replaced underneath a
    // long-lived engine cannot be served from the stale offsets.
    let contents = snapshot_file(&[
        record("0x00401000", "0x00001000", 9999),
        record("0x00401010", "0x00001010", 8888),
    ]);
    let file = TempFile::new("mutated", &contents);
    let snapshot = Snapshot::open(file.path()).expect("valid");
    assert_eq!(snapshot.function_count(), 2);

    // Same byte length, different content: the offsets stay valid, so only the
    // record's own identity check can notice. 9999 and 8888 are both four
    // digits, which is the point.
    let mut mutated = snapshot_file(&[
        record("0x00401000", "0x00001000", 9999),
        record("0x00401010", "0x00001010", 8888),
    ]);
    let original = mutated.clone();
    let needle = "\"size\":9999";
    let position = mutated.find(needle).expect("the needle is there");
    mutated.replace_range(position..position + needle.len(), "\"size\":8888");
    assert_eq!(
        mutated.len(),
        original.len(),
        "the mutation must not move any byte"
    );
    std::fs::write(file.path(), &mutated).expect("the fixture is writable");

    match snapshot.lookup(0x0040_1000) {
        Err(BridgeError::Corrupt { detail, .. }) => {
            assert!(detail.contains("changed after it was opened"), "{detail}");
            assert!(detail.contains("body size"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
    // The second record is untouched, so it still reads.
    assert_eq!(
        snapshot
            .lookup(0x0040_1010)
            .expect("untouched")
            .canonical_va(),
        0x0040_1010
    );
}
