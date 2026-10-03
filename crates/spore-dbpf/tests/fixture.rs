//! Differential tests against the committed fixture
//! `tests/fixtures/mini_package.dbpf`.
//!
//! Every expected value here is transcribed from
//! `tests/fixtures/gen_fixtures.py::build_package()`, which is deterministic and
//! regenerates the file byte-for-byte. Nothing in this file was read out of the
//! binary by hand: the generator is the specification of what the bytes mean.

mod support;

use spore_core::ResourceKey;
use spore_dbpf::{
    decompress, extract_record, find_entry, parse_index, DbpfEntry, DbpfError, PackageIndex,
    COMPRESSION_NONE, COMPRESSION_QFS, SIZE_MASK,
};

use support::qfs_encoder::{compress, compress_literal_runs, wrap};

/// The committed fixture. Path is relative to the workspace root.
const FIXTURE: &str = concat!(
    env!("CARGO_MANIFEST_DIR"),
    "/../../tests/fixtures/mini_package.dbpf"
);

fn fixture() -> Vec<u8> {
    let bytes = std::fs::read(FIXTURE).unwrap_or_else(|error| panic!("reading {FIXTURE}: {error}"));
    assert_eq!(bytes.len(), 685, "the committed fixture is 685 bytes");
    assert_eq!(&bytes[0..4], b"DBPF", "fixture magic");
    bytes
}

// ---- the generator's payloads ---------------------------------------------

/// `REC0 = bytes(range(16))`, the `TSTX` record.
fn rec0() -> Vec<u8> {
    (0..16u8).collect()
}

/// `QFS_PAYLOAD = bytes(range(112)) + bytes(300)`, the `QFS1` record.
fn qfs_payload() -> Vec<u8> {
    let mut out: Vec<u8> = (0..112u8).collect();
    out.extend(std::iter::repeat_n(0u8, 300));
    assert_eq!(out.len(), 412);
    out
}

/// `REC2 = bytes((i * 7) & 0xFF for i in range(64))`, the `RAWB` record.
fn rec2() -> Vec<u8> {
    (0..64u32).map(|i| (i * 7) as u8).collect()
}

/// The exact three rows `build_package()` writes, as expected values.
fn expected_entries() -> Vec<DbpfEntry> {
    vec![
        // 4CC 'TSTX', stored 16 / memory 16, uncompressed.
        DbpfEntry::new(
            0x5854_5354,
            0x1111_1111,
            0x2222_2222,
            184,
            16,
            16,
            COMPRESSION_NONE,
            false,
        ),
        // 4CC 'QFS1', stored 421 / memory 412, QFS.
        DbpfEntry::new(
            0x3153_4651,
            0x3333_3333,
            0x4444_4444,
            200,
            421,
            412,
            COMPRESSION_QFS,
            false,
        ),
        // 4CC 'RAWB', stored 64 / memory 64, uncompressed.
        DbpfEntry::new(
            0x4257_4152,
            0x5555_5555,
            0x6666_6666,
            621,
            64,
            64,
            COMPRESSION_NONE,
            false,
        ),
    ]
}

// ---- 1. index parse --------------------------------------------------------

#[test]
fn the_fixture_index_matches_the_generator() {
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    let expected = expected_entries();

    assert_eq!(entries.len(), 3, "the generator declares three records");
    assert_eq!(entries, expected, "every field of every row, exactly");

    // Field by field as well, so a failure names the field that moved.
    for (index, (got, want)) in entries.iter().zip(expected.iter()).enumerate() {
        assert_eq!(got.type_id, want.type_id, "row {index} type");
        assert_eq!(got.group_id, want.group_id, "row {index} group");
        assert_eq!(got.instance_id, want.instance_id, "row {index} instance");
        assert_eq!(got.offset, want.offset, "row {index} offset");
        assert_eq!(got.stored_size, want.stored_size, "row {index} stored size");
        assert_eq!(got.memory_size, want.memory_size, "row {index} memory size");
        assert_eq!(got.compression, want.compression, "row {index} compression");
        assert_eq!(
            got.compressed, want.compressed,
            "row {index} compressed flag"
        );
        assert_eq!(got.saved, want.saved, "row {index} saved flag");
        assert_eq!(got.key, want.key, "row {index} key projection");
        assert!(got.key.is_complete(), "row {index} key has no wildcard");
    }
}

#[test]
fn the_fixture_stored_sizes_carry_the_format_flag_bit() {
    // `gen_fixtures.py::dbpf_item` writes `csize | 0x80000000`, so the mask is
    // not decorative: without it every extent check in this file would fail.
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    for (index, entry) in entries.iter().enumerate() {
        // Row layout: type +0, group +4, instance +8, offset +12, stored +16,
        // memory +20, compression +24, saved +26, pad +27.
        let at = 96 + 4 + 28 * index + 16;
        let raw = u32::from_le_bytes(bytes[at..at + 4].try_into().unwrap());
        assert_eq!(raw & !SIZE_MASK, 1 << 31, "bit 31 is the flag bit");
        assert_eq!(
            raw & SIZE_MASK,
            entry.stored_size,
            "the mask recovers the size"
        );
    }
}

#[test]
fn the_fixture_records_are_byte_for_byte_where_the_generator_puts_them() {
    let bytes = fixture();
    for (entry, payload) in parse_index(&bytes)
        .unwrap()
        .iter()
        .zip([rec0(), qfs_payload(), rec2()])
    {
        let start = entry.offset as usize;
        let stored = &bytes[start..start + entry.stored_size as usize];
        if entry.compressed {
            // The QFS record's stored bytes are a compressed form; compare the
            // decoded form in `extraction_returns_the_generators_payloads`.
            assert_eq!(decompress(stored).unwrap(), payload);
        } else {
            assert_eq!(stored, &payload[..], "a stored record is its own payload");
        }
    }
}

#[test]
fn the_fixture_type_ids_render_as_the_generators_four_character_codes() {
    let entries = parse_index(&fixture()).unwrap();
    let codes: Vec<Option<String>> = entries.iter().map(|e| e.type_fourcc()).collect();
    assert_eq!(
        codes,
        vec![
            Some("TSTX".to_string()),
            Some("QFS1".to_string()),
            Some("RAWB".to_string())
        ]
    );
    // Synthetic ids, so no canonical name resolves.
    assert!(entries.iter().all(|e| e.type_name().is_none()));
}

// ---- 2 & 3. QFS round-trip and extraction ----------------------------------

#[test]
fn extraction_returns_the_generators_payloads() {
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    let payloads = [rec0(), qfs_payload(), rec2()];

    for (index, (entry, payload)) in entries.iter().zip(payloads.iter()).enumerate() {
        let extracted = extract_record(&bytes, entry)
            .unwrap_or_else(|error| panic!("record {index} extraction: {error}"));
        assert_eq!(&extracted, payload, "record {index} bytes");
        assert_eq!(
            extracted.len(),
            entry.memory_size as usize,
            "record {index} length equals the index memory_size"
        );
        assert_eq!(
            entry.stored_size as usize + entry.offset as usize,
            {
                // Every extent ends exactly where the next one begins; the last
                // one ends at the end of the file. This is the layout invariant
                // that makes the offsets above self-checking.
                if index + 1 < entries.len() {
                    entries[index + 1].offset as usize
                } else {
                    bytes.len()
                }
            },
            "record {index} extent is contiguous"
        );
    }
}

#[test]
fn the_compressed_record_decodes_to_the_same_bytes_it_was_made_from() {
    // The fixture's own QFS stream, decoded and re-encoded with a literal-only
    // encoder, must reproduce the exact stored bytes. That pins the decoder
    // against the generator's output rather than against itself.
    let bytes = fixture();
    let entry = &parse_index(&bytes).unwrap()[1];
    let start = entry.offset as usize;
    let stored = &bytes[start..start + entry.stored_size as usize];

    assert_eq!(stored.len(), 421, "the generator's QFS stream is 421 bytes");
    assert_eq!(&stored[0..2], &[0x10, 0xFB], "QFS variant byte and magic");
    assert_eq!(
        &stored[2..5],
        &[0x00, 0x01, 0x9C],
        "24-bit BIG-ENDIAN size 412"
    );

    let payload = qfs_payload();
    assert_eq!(
        decompress(stored).unwrap(),
        payload,
        "decodes to the generator's payload"
    );
    assert_eq!(
        compress_literal_runs(&payload),
        stored,
        "the literal-run encoder reproduces the generator's stored bytes exactly"
    );
    // The greedy encoder finds the 300-byte zero run the generator missed, so it
    // legitimately differs -- but it must still round-trip to the same payload.
    let greedy = compress(&payload);
    assert!(
        greedy.len() < stored.len(),
        "greedy: {} < literal-only: 421",
        greedy.len()
    );
    assert_eq!(decompress(&greedy).unwrap(), payload);
}

#[test]
fn extraction_is_deterministic() {
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    for entry in &entries {
        let first = extract_record(&bytes, entry).unwrap();
        let second = extract_record(&bytes, entry).unwrap();
        assert_eq!(first, second);
    }
}

// ---- 4. find_entry ---------------------------------------------------------

#[test]
fn find_entry_round_trips_every_fixture_row() {
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    for entry in &entries {
        let found = find_entry(&entries, &entry.key)
            .unwrap_or_else(|| panic!("{} not found by identity", entry.key));
        assert_eq!(found, entry, "find_entry returns the same row");
    }
    assert!(find_entry(&entries, &ResourceKey::new(1, 2, 3)).is_none());
    // A key that differs in one component must not match.
    let key = entries[0].key;
    assert!(find_entry(
        &entries,
        &ResourceKey::new(key.type_id + 1, key.group_id, key.instance_id)
    )
    .is_none());
    assert!(find_entry(
        &entries,
        &ResourceKey::new(key.type_id, key.group_id + 1, key.instance_id)
    )
    .is_none());
    assert!(find_entry(
        &entries,
        &ResourceKey::new(key.type_id, key.group_id, key.instance_id + 1)
    )
    .is_none());
}

// ---- 5. negative paths, one per error --------------------------------------

/// A copy of the fixture with `len` bytes replaced by `patch`, keeping its size.
fn patched_fixture(at: usize, patch: &[u8]) -> Vec<u8> {
    let mut bytes = fixture();
    bytes[at..at + patch.len()].copy_from_slice(patch);
    bytes
}

#[test]
fn a_bad_magic_is_refused_and_never_confused_with_the_64_bit_variant() {
    let dbbf = patched_fixture(0, b"DBBF");
    assert_eq!(parse_index(&dbbf), Err(DbpfError::Unsupported64BitVariant));

    for magic in [*b"XXXX", *b"dbpf", [0u8; 4]] {
        let bytes = patched_fixture(0, &magic);
        assert_eq!(
            parse_index(&bytes),
            Err(DbpfError::BadMagic { found: magic })
        );
    }
}

#[test]
fn an_index_offset_inside_the_header_is_refused() {
    for offset in [0u32, 1, 64, 95] {
        let bytes = patched_fixture(0x40, &offset.to_le_bytes());
        assert_eq!(
            parse_index(&bytes),
            Err(DbpfError::IndexOffsetOverlapsHeader {
                offset,
                expected: 96
            })
        );
    }
}

#[test]
fn a_truncated_index_block_is_refused() {
    // The index starts at 96; cutting the image right after the flags word
    // leaves no room for even one 28-byte row.
    let bytes = fixture()[..100].to_vec();
    assert_eq!(
        parse_index(&bytes),
        Err(DbpfError::IndexCountExceedsIndex {
            count: 3,
            row_size: 28,
            available: 0
        })
    );

    // An index offset that leaves not even the 4-byte flags word readable.
    let mut bytes = fixture();
    bytes[0x40..0x44].copy_from_slice(&(684u32).to_le_bytes());
    assert!(matches!(
        parse_index(&bytes),
        Err(DbpfError::IndexOffsetPastEnd { offset: 684, .. })
    ));
}

#[test]
fn a_count_beyond_the_available_rows_is_refused() {
    // The guard is `count > remaining / row_size`, where `remaining` runs to the
    // end of the *file* -- payloads included. So a count only fails when the
    // image is too short to hold that many rows at all.
    let bytes = fixture()[..150].to_vec();
    assert_eq!(
        parse_index(&bytes),
        Err(DbpfError::IndexCountExceedsIndex {
            count: 3,
            row_size: 28,
            available: 50
        })
    );

    // 151 bytes leaves 51 -- still one row short of three (3 * 28 = 84).
    let bytes = fixture()[..151].to_vec();
    assert!(matches!(
        parse_index(&bytes),
        Err(DbpfError::IndexCountExceedsIndex {
            count: 3,
            row_size: 28,
            available: 51
        })
    ));

    // The message names the stride the flags imply, so a 20-byte-row package
    // reports 20 here rather than 28.
    let mut rows20 = fixture();
    rows20[96..100].copy_from_slice(&(0x03u32).to_le_bytes()); // flags: type + group shared
    rows20[100..104].copy_from_slice(&0x00E6_BCE5u32.to_le_bytes());
    rows20[104..108].copy_from_slice(&0x4061_6201u32.to_le_bytes());
    let message = parse_index(&rows20[..130]).unwrap_err().to_string();
    assert!(message.contains("(20 bytes per row)"), "message: {message}");
}

#[test]
fn a_count_that_fits_the_file_but_not_the_index_is_still_parsed() {
    // Documented consequence of the guard being a *lower* bound: the index walk
    // trusts `count` as long as the file is long enough, so a count larger than
    // the real index reads a row out of the payload region. The C++ behaves
    // identically; the guard exists to stop the walk leaving the image, not to
    // validate the count. Rejecting such a row is `extract_record`'s job, and it
    // does: the bogus extent leaves the image.
    let bytes = patched_fixture(0x24, &4u32.to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert_eq!(entries.len(), 4);
    assert_eq!(
        &entries[..3],
        &expected_entries()[..],
        "the three real rows are intact"
    );
    let bogus = entries[3];
    assert!(
        extract_record(&bytes, &bogus).is_err(),
        "the phantom row's extent leaves the image"
    );
}

#[test]
fn an_unsupported_compression_word_is_refused_at_extraction_time() {
    // Row 1's compression word lives at 96 + 4 + 28 + 24 = 152.
    let bytes = patched_fixture(152, &0x1234u16.to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert_eq!(entries[1].compression, 0x1234);
    assert!(
        !entries[1].compressed,
        "an unsupported word is not 'compressed'"
    );
    assert_eq!(
        extract_record(&bytes, &entries[1]),
        Err(DbpfError::UnsupportedCompression {
            compression: 0x1234
        })
    );
    // Rows 0 and 2 are untouched and still extract.
    assert_eq!(extract_record(&bytes, &entries[0]).unwrap(), rec0());
    assert_eq!(extract_record(&bytes, &entries[2]).unwrap(), rec2());
}

#[test]
fn an_extent_past_the_end_of_the_package_is_refused() {
    // Row 0's offset word sits at 96 + 4 + 12 = 112.
    let bytes = patched_fixture(112, &(685u32 - 4).to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert_eq!(
        extract_record(&bytes, &entries[0]),
        Err(DbpfError::RecordExtentPastEnd {
            offset: 681,
            stored_size: 16,
            len: 685
        })
    );

    // An offset plus size that would wrap 32-bit arithmetic.
    let bytes = patched_fixture(112, &0xFFFF_FFF0u32.to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert!(matches!(
        extract_record(&bytes, &entries[0]),
        Err(DbpfError::RecordExtentPastEnd { .. })
    ));
}

#[test]
fn a_memory_size_that_disagrees_with_the_payload_is_refused() {
    // Row 1's memory-size word sits at 96 + 4 + 28 + 20 = 148.
    let bytes = patched_fixture(148, &411u32.to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert_eq!(
        extract_record(&bytes, &entries[1]),
        Err(DbpfError::SizeMismatch {
            actual: 412,
            expected: 411
        })
    );

    // Row 0 is stored, not compressed: the same invariant applies there.
    // Its memory-size word sits at 96 + 4 + 20 = 120.
    let bytes = patched_fixture(120, &15u32.to_le_bytes());
    let entries = parse_index(&bytes).unwrap();
    assert_eq!(
        extract_record(&bytes, &entries[0]),
        Err(DbpfError::SizeMismatch {
            actual: 16,
            expected: 15
        })
    );
}

#[test]
fn a_corrupt_qfs_stream_is_refused_rather_than_partly_decoded() {
    let bytes = fixture();
    let entry = parse_index(&bytes).unwrap()[1];
    let at = entry.offset as usize;

    // Bad variant byte.
    let broken = patched_fixture(at, &[0x11]);
    assert_eq!(
        extract_record(&broken, &entry),
        Err(DbpfError::QfsBadMagic {
            first: 0x11,
            second: 0xFB
        })
    );

    // Bad magic byte.
    let broken = patched_fixture(at + 1, &[0xFA]);
    assert_eq!(
        extract_record(&broken, &entry),
        Err(DbpfError::QfsBadMagic {
            first: 0x10,
            second: 0xFA
        })
    );

    // A declared decompressed size of 0 leaves the token stream unread, which is
    // legal; the record is then rejected by the memory_size invariant.
    let broken = patched_fixture(at + 2, &[0, 0, 0]);
    assert_eq!(
        extract_record(&broken, &entry),
        Err(DbpfError::SizeMismatch {
            actual: 0,
            expected: 412
        })
    );

    // Truncating the *record* is what exercises the token-level errors, since
    // the record slice is all the decoder ever sees. Every prefix is checked
    // for "does not panic" in `no_prefix_of_the_fixture_panics`.
    let stored = &bytes[at..at + entry.stored_size as usize];
    assert_eq!(
        decompress(&stored[..5]),
        Err(DbpfError::QfsTruncatedControlByte),
        "header only"
    );
    assert_eq!(
        decompress(&stored[..6]),
        Err(DbpfError::QfsTruncatedLiteralRun { literals: 112 }),
        "control byte with no operands and no literals behind it"
    );
    for len in 0..stored.len() {
        let _ = decompress(&stored[..len]);
    }
}

#[test]
fn qfs_failures_cover_every_stream_error_path() {
    // These streams are hand-built, because the committed fixture happens to
    // contain nothing but literal tokens: it exercises the `224..251` class and
    // the header, and no match token at all.
    // Short header.
    assert_eq!(
        decompress(&[0x10, 0xFB, 0x00]),
        Err(DbpfError::QfsHeaderTooShort {
            len: 3,
            expected: 5
        })
    );
    // Truncated control byte: declares 8, supplies one 4-literal token.
    assert_eq!(
        decompress(&wrap(8, &[0xE0, 1, 2, 3, 4])),
        Err(DbpfError::QfsTruncatedControlByte)
    );
    // Truncated token operands, one class at a time.
    assert_eq!(
        decompress(&wrap(16, &[0xC0, 0x00])),
        Err(DbpfError::QfsTruncatedLongMatchToken)
    );
    assert_eq!(
        decompress(&wrap(16, &[0x80, 0x00])),
        Err(DbpfError::QfsTruncatedMidMatchToken)
    );
    assert_eq!(
        decompress(&wrap(16, &[0x40])),
        Err(DbpfError::QfsTruncatedShortMatchToken)
    );
    // Truncated literal run: 112 literals promised, 3 supplied.
    assert_eq!(
        decompress(&wrap(112, &[0xFB, 1, 2, 3])),
        Err(DbpfError::QfsTruncatedLiteralRun { literals: 112 })
    );
    // Invalid back-reference: nothing produced, so distance 1 is already out.
    assert_eq!(
        decompress(&wrap(4, &[0x00, 0x00, 0xAA])),
        Err(DbpfError::QfsInvalidBackReference {
            distance: 1,
            produced: 0,
            copies: 3
        })
    );
    // Output past the declared size: 8 bytes produced, 3 copies, room for 2.
    assert_eq!(
        decompress(&wrap(10, &[0xE0, 1, 2, 3, 4, 0xE0, 5, 6, 7, 8, 0x00, 0x00])),
        Err(DbpfError::QfsInvalidBackReference {
            distance: 1,
            produced: 8,
            copies: 3
        })
    );
}

// ---- 7. truncation sweep ---------------------------------------------------

#[test]
fn no_prefix_of_the_fixture_panics() {
    let bytes = fixture();
    let full = parse_index(&bytes).unwrap();
    for len in 0..=bytes.len() {
        let prefix = &bytes[..len];
        // Parsing may succeed or fail; it may not panic and it may not return
        // a row whose extent leaves the prefix.
        if let Ok(entries) = parse_index(prefix) {
            for entry in &entries {
                // The index is valid even when the payload it names is not in
                // this prefix yet -- the index parse never inspects extents --
                // so the only requirement here is that extraction reports the
                // shortfall instead of reading past the end.
                let end = entry.offset as u64 + entry.stored_size as u64;
                if end > len as u64 {
                    assert!(
                        extract_record(prefix, entry).is_err(),
                        "len {len}: extent {} leaves the prefix yet extraction succeeded",
                        entry.extent_text()
                    );
                } else {
                    let _ = extract_record(prefix, entry);
                }
            }
        }
    }
    // Every entry of the full parse survives every truncation of the payload it
    // points into.
    for entry in &full {
        for len in 0..=bytes.len() {
            let _ = extract_record(&bytes[..len], entry);
        }
    }
}

#[test]
fn single_byte_mutations_never_panic() {
    // Deterministic sweep: no RNG, no proptest dependency. Each byte of the
    // header and index region is set to each of a few adversarial values.
    let bytes = fixture();
    for at in 0..184usize {
        for value in [0x00u8, 0x01, 0x7F, 0x80, 0xFF] {
            let mut mutated = bytes.clone();
            mutated[at] = value;
            if let Ok(entries) = parse_index(&mutated) {
                for entry in &entries {
                    let _ = extract_record(&mutated, entry);
                }
            }
        }
    }
}

// ---- PackageIndex over the fixture ----------------------------------------

#[test]
fn package_index_reads_the_fixture_and_extracts_by_identity() {
    let bytes = fixture();
    let index = PackageIndex::parse(&bytes).unwrap();
    assert_eq!(index.len(), 3);
    assert_eq!(index.entries(), &expected_entries()[..]);
    assert_eq!(index.iter().count(), 3);

    for (entry, payload) in index.entries().iter().zip([rec0(), qfs_payload(), rec2()]) {
        assert_eq!(
            index.extract(&bytes, &entry.key).unwrap().as_deref(),
            Some(payload.as_slice())
        );
    }
    assert_eq!(
        index.extract(&bytes, &ResourceKey::new(1, 2, 3)).unwrap(),
        None
    );

    // Wildcard lookup: "the only GMDL-ish row of this group".
    let key = ResourceKey::new(0x3153_4651, 0x3333_3333, spore_core::WILDCARD);
    assert_eq!(index.find_matching(&key).unwrap().instance_id, 0x4444_4444);
    assert_eq!(index.of_type(0x4257_4152).count(), 1);
}

#[test]
fn the_fixture_survives_a_parse_extract_parse_cycle_unchanged() {
    let bytes = fixture();
    let entries = parse_index(&bytes).unwrap();
    let mut rebuilt = Vec::new();
    for entry in &entries {
        rebuilt.extend_from_slice(&extract_record(&bytes, entry).unwrap());
    }
    assert_eq!(rebuilt.len(), 16 + 412 + 64);
    assert_eq!(rebuilt[0..16], rec0()[..]);
    assert_eq!(rebuilt[16..428], qfs_payload()[..]);
    assert_eq!(rebuilt[428..492], rec2()[..]);
}
