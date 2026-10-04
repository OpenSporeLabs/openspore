//! `manifest`: row order, and the byte-identity of two runs.
//!
//! The reference tool's docstring states the property it is built around — it
//! drops and rebuilds its sidecar each run "so a double run is byte-identical".
//! That is the test this file exists for.

mod common;

use common::{osptool, Row, TempDir, TempFile};
use spore_tools::commands::manifest::STATS_TOP_N;
use spore_tools::{json::parse, EXIT_OK};

/// A package with a few records spread over three types and three groups.
fn mixed_package() -> Vec<u8> {
    common::package_of(&[
        Row::new(0x4257_4152, 0x5555_5555, 0x6666_6666, vec![0; 64]),
        Row::new(spore_gmdl::GMDL_TYPE, 0x4061_6201, 0x067a_0801, vec![0; 32]),
        Row::new(0x3153_4651, 0x3333_3333, 0x4444_4444, vec![0; 16]),
        Row::new(spore_gmdl::GMDL_TYPE, 0x4061_6201, 0x067a_0002, vec![0; 8]),
        Row::new(spore_core::record::type_id::PROP, 0, 1, vec![0; 4]),
    ])
}

#[test]
fn one_row_per_record_ascending_by_type_group_instance() {
    let file = TempFile::with("manifest-mixed", &mixed_package());
    let path = file.path().display().to_string();
    // No `--out` and no `--json`: the manifest goes to stdout as JSON Lines.
    let (code, out, err) = osptool(&["manifest", &path]);
    assert_eq!(code, EXIT_OK, "{err}");

    let lines: Vec<&str> = out.lines().collect();
    assert_eq!(lines.len(), 5, "one row per record:\n{out}");
    let keys: Vec<Vec<u32>> = lines
        .iter()
        .map(|line| {
            let value = parse(line).expect("each line is a JSON object");
            match value {
                spore_tools::json::Json::Obj(pairs) => pairs
                    .into_iter()
                    .filter(|(key, _)| key.ends_with("_id"))
                    .map(|(_, value)| match value {
                        spore_tools::json::Json::Str(text) => {
                            u32::from_str_radix(text.trim_start_matches("0x"), 16)
                                .expect("ids are hex strings")
                        }
                        other => panic!("an id must be a string, got {other}"),
                    })
                    .collect(),
                other => panic!("each line must be an object, got {other}"),
            }
        })
        .collect();
    // Ascending lexicographically on (type, group, instance). The index order of
    // the same package is different, which is the point of sorting.
    let mut sorted = keys.clone();
    sorted.sort();
    assert_eq!(keys, sorted, "rows must be ascending:\n{out}");
    assert_eq!(keys[0][0], 0x00b1_b104, "prop sorts first: {keys:?}");
    assert_eq!(keys[1][0], spore_gmdl::GMDL_TYPE);
    // Within gmdl, the smaller instance comes first.
    assert_eq!(keys[1][2], 0x067a_0002);
    assert_eq!(keys[2][2], 0x067a_0801);
    assert_eq!(keys[3][0], 0x3153_4651);
    assert_eq!(keys[4][0], 0x4257_4152);
}

#[test]
fn two_runs_produce_byte_identical_json_lines() {
    let file = TempFile::with("manifest-determinism", &mixed_package());
    let path = file.path().display().to_string();
    let first = TempFile::with("manifest-run1", b"");
    let second = TempFile::with("manifest-run2", b"");
    let (code1, out1, err1) = osptool(&[
        "manifest",
        &path,
        "--out",
        &first.path().display().to_string(),
    ]);
    let (code2, _out2, err2) = osptool(&[
        "manifest",
        &path,
        "--out",
        &second.path().display().to_string(),
    ]);
    assert_eq!(code1, EXIT_OK, "{err1}");
    assert_eq!(code2, EXIT_OK, "{err2}");

    let bytes1 = first.read();
    let bytes2 = second.read();
    assert_eq!(bytes1, bytes2, "a double run must be byte-identical");
    // The two reports differ only in the temporary path they name.
    let normalised =
        |report: &str, file: &TempFile| report.replace(&file.path().display().to_string(), "<OUT>");
    assert_eq!(
        normalised(&err1, &first),
        normalised(&err2, &second),
        "the reports must agree once the path is factored out"
    );
    assert_eq!(
        out1, "",
        "with --out, stdout carries no document unless --json was asked for"
    );
    assert!(
        err1.contains(&format!(
            "wrote {} (5 rows, {} bytes)",
            first.path().display(),
            bytes1.len()
        )),
        "{err1}"
    );
    // Every line ends with exactly one newline, and there are five of them.
    assert_eq!(bytes1.iter().filter(|byte| **byte == b'\n').count(), 5);
    assert!(bytes1.ends_with(b"\n"));
}

#[test]
fn the_json_view_and_the_file_view_agree_row_for_row() {
    let file = TempFile::with("manifest-views", &mixed_package());
    let path = file.path().display().to_string();
    let out_file = TempFile::with("manifest-views-out", b"");
    let (code, stdout, err) = osptool(&[
        "manifest",
        &path,
        "--json",
        "--out",
        &out_file.path().display().to_string(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    // The confirmation went to stderr, so stdout is the document and nothing else.
    assert!(err.contains("wrote "), "{err}");
    assert_eq!(
        stdout.lines().count(),
        1,
        "one JSON array on one line: {stdout}"
    );

    let from_file = String::from_utf8(out_file.read()).expect("utf-8");
    let lines: Vec<&str> = from_file.lines().collect();
    let array = parse(stdout.trim()).expect("valid JSON array");
    let spore_tools::json::Json::Arr(rows) = &array else {
        panic!("expected an array, got {array}")
    };
    assert_eq!(rows.len(), lines.len());
    for (row, line) in rows.iter().zip(lines.iter()) {
        assert_eq!(
            &row.to_string(),
            line,
            "the two views must render identically"
        );
    }
}

#[test]
fn the_stats_summary_reports_the_row_count_and_the_statuses() {
    let file = TempFile::with("manifest-stats", &mixed_package());
    let path = file.path().display().to_string();
    let (code, out, err) = osptool(&["manifest", &path, "--stats"]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(out.contains("rows              5"), "{out}");
    // Three named statuses and one empty bucket that this package does not hit.
    assert!(
        out.contains("type-level classification, not a per-record decode"),
        "{out}"
    );
    assert!(out.contains("container-undecoded"), "{out}");
    assert!(out.contains("undecoded"), "{out}");
    assert!(out.contains("top 20 type names"), "{out}");
    // The three names present, with the counts from the rows above.
    assert!(out.contains("gmdl"), "{out}");
    assert!(out.contains("prop"), "{out}");
    // `&<unnamed>` is this build's bucket for a type with no canonical name.
    assert!(out.contains("<unnamed>"), "{out}");
}

#[test]
fn the_stats_tie_break_is_stable_across_runs_and_package_orders() {
    let file = TempFile::with("manifest-tiebreak", &mixed_package());
    let path = file.path().display().to_string();
    let first = osptool(&["manifest", &path, "--stats"]);
    let second = osptool(&["manifest", &path, "--stats"]);
    assert_eq!(first, second);
}

#[test]
fn several_packages_deduplicate_by_identity_with_the_first_one_winning() {
    // Two packages holding the same identity: the store resolves first-match
    // wins, and the manifest describes what the store would hand back.
    let a = TempFile::with("manifest-a", &mixed_package());
    let b = TempFile::with("manifest-b", &mixed_package());
    let one = osptool(&[
        "manifest",
        &a.path().display().to_string(),
        &b.path().display().to_string(),
        "--stats",
    ]);
    let two = osptool(&[
        "manifest",
        &b.path().display().to_string(),
        &a.path().display().to_string(),
        "--stats",
    ]);
    assert_eq!(one.0, EXIT_OK);
    assert_eq!(two.0, EXIT_OK);
    // Five distinct identities in each: the duplicate does not add rows.
    assert!(one.1.contains("rows              5"), "{}", one.1);
    assert!(two.1.contains("rows              5"), "{}", two.1);
}

#[test]
fn a_row_carries_the_documented_keys_in_the_documented_order() {
    let file = TempFile::with("manifest-keys", &common::gmdl_package());
    let path = file.path().display().to_string();
    let out_file = TempFile::with("manifest-keys-out", b"");
    let (code, _stdout, err) = osptool(&[
        "manifest",
        &path,
        "--out",
        &out_file.path().display().to_string(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    let text = String::from_utf8(out_file.read()).expect("utf-8");
    assert_eq!(
        text.trim(),
        "{\"type_id\":\"0x00e6bce5\",\"group_id\":\"0x40616201\",\"instance_id\":\"0x067a0801\",\
         \"type_name\":\"gmdl\",\"group_name\":\"CellImages\",\"size\":1266,\"decode_status\":\"ok\",\
         \"semantic_owner\":null,\"type_name_evidence\":\"VERIFIED\",\"group_name_evidence\":\"VERIFIED\"}"
    );
}

#[test]
fn a_missing_name_is_null_and_not_the_string_unknown() {
    // The reference tool hard-codes `semantic_owner = "UNKNOWN"`, which conflates
    // "no owner established" with a name. This port emits `null`.
    let file = TempFile::with("manifest-nulls", &mixed_package());
    let path = file.path().display().to_string();
    let (code, out, _err) = osptool(&["manifest", &path]);
    assert_eq!(code, EXIT_OK);
    assert!(out.contains("\"semantic_owner\":null"), "{out}");
    assert!(!out.contains("\"semantic_owner\":\"UNKNOWN\""), "{out}");
    // A type with no canonical name is `null` too, with INFERRED evidence: the
    // id is real and observed, the name is not.
    assert!(
        out.contains("\"type_name\":null,\"group_name\":null"),
        "{out}"
    );
    assert!(out.contains("\"type_name_evidence\":\"INFERRED\""), "{out}");
}

#[test]
fn a_missing_out_file_is_an_io_failure_and_the_manifest_is_not_truncated_silently() {
    let file = TempFile::with("manifest-badout", &mixed_package());
    let missing = format!(
        "{}/osptool-no-such-dir-{}/m.jsonl",
        std::env::temp_dir().display(),
        std::process::id()
    );
    let (code, _out, err) = osptool(&[
        "manifest",
        &file.path().display().to_string(),
        "--out",
        &missing,
    ]);
    assert_eq!(code, spore_tools::EXIT_IO, "{err}");
    assert!(!std::path::Path::new(&missing).exists());
}

#[test]
fn a_manifest_written_into_a_directory_and_read_back_is_still_identical() {
    let dir = TempDir::new("manifest-roundtrip");
    let file = TempFile::with("manifest-roundtrip", &mixed_package());
    let out_path = dir.path().join("manifest.jsonl");
    let (code, _out, err) = osptool(&[
        "manifest",
        &file.path().display().to_string(),
        "--out",
        &out_path.display().to_string(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    let first = std::fs::read(&out_path).expect("written");
    let (code2, _out2, err2) = osptool(&[
        "manifest",
        &file.path().display().to_string(),
        "--out",
        &out_path.display().to_string(),
    ]);
    assert_eq!(code2, EXIT_OK, "{err2}");
    assert_eq!(first, std::fs::read(&out_path).expect("written"));
}

#[test]
fn the_stats_top_n_cap_is_the_documented_twenty() {
    assert_eq!(spore_tools::commands::manifest::STATS_TOP_N, 20);
    // A package with more than twenty distinct *named* types must say what it
    // left out. The name buckets come from the canonical table, so the rows have
    // to use real type ids -- twenty-five synthetic ids would all land in the
    // single `<unnamed>` bucket and the cap would never be reached.
    let named: Vec<u32> = spore_core::record::TYPE_NAMES
        .iter()
        .map(|(id, _)| *id)
        .collect();
    assert!(
        named.len() > STATS_TOP_N,
        "the canonical table must be big enough"
    );
    let rows: Vec<Row> = named
        .iter()
        .enumerate()
        .map(|(index, id)| Row::new(*id, 1, index as u32, vec![0; 4]))
        .collect();
    let file = TempFile::with("manifest-many", &common::package_of(&rows));
    let path = file.path().display().to_string();
    let (code, out, _err) = osptool(&["manifest", &path, "--stats"]);
    assert_eq!(code, EXIT_OK);
    assert!(
        out.contains(&format!(
            "{} further type name(s) not shown",
            named.len() - STATS_TOP_N
        )),
        "{out}"
    );
    // And the rows themselves are all still there.
    assert!(
        out.contains(&format!("rows              {}", named.len())),
        "{out}"
    );
}
