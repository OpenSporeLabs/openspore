//! `list` against the committed fixture: exact rows, exact columns, exact JSON.

mod common;

use common::{osptool, Row, MINI_PACKAGE};
use spore_tools::{json::Json, EXIT_OK};

/// The three rows of `mini_package.dbpf`, as `gen_fixtures.py` wrote them.
const EXPECTED: &[(&str, &str, &str, u32, u32, &str)] = &[
    // type, group, instance, stored, memory, compression
    ("0x58545354", "0x11111111", "0x22222222", 16, 16, "none"),
    ("0x31534651", "0x33333333", "0x44444444", 421, 412, "qfs"),
    ("0x42574152", "0x55555555", "0x66666666", 64, 64, "none"),
];

#[test]
fn the_row_count_and_index_order_are_exact() {
    let (code, out, _err) = osptool(&["list", MINI_PACKAGE, "--limit", "0"]);
    assert_eq!(code, EXIT_OK);
    let lines: Vec<&str> = out.lines().collect();
    assert_eq!(
        lines.len(),
        5,
        "one summary, one header, three rows:\n{out}"
    );
    assert!(lines[0].contains("mini_package"), "{}", lines[0]);
    assert!(lines[0].contains("3 record(s)"), "{}", lines[0]);
    assert!(lines[0].contains("3 shown"), "{}", lines[0]);
    for (index, expected) in EXPECTED.iter().enumerate() {
        let row = lines[index + 2];
        assert!(
            row.contains(&format!("{index:5}")),
            "row {index} must carry its index: {row}"
        );
        for (kind, id) in [
            ("type", expected.0),
            ("group", expected.1),
            ("instance", expected.2),
        ] {
            assert!(
                row.contains(id),
                "row {index} must contain {kind} {id}: {row}"
            );
        }
        // Both size columns are right-aligned, which is what makes a census
        // scannable; the padding is part of the contract.
        assert!(row.contains(&format!("{:>7}", expected.3)), "stored: {row}");
        assert!(row.contains(&format!("{:>6}", expected.4)), "memory: {row}");
        assert!(row.contains(expected.5), "compression: {row}");
    }
}

#[test]
fn the_column_header_is_the_documented_one() {
    let (_code, out, _err) = osptool(&["list", MINI_PACKAGE]);
    let header = out.lines().nth(1).expect("a header line");
    for column in [
        "idx", "type_id", "group_id", "instance", "stored", "memory", "comp",
    ] {
        assert!(header.contains(column), "missing column {column}: {header}");
    }
    // Without `--names` there are no name columns at all.
    assert!(!header.contains("type_name"));
    assert!(!header.contains("group_name"));
}

#[test]
fn the_default_limit_is_fifty_and_zero_means_unlimited() {
    // Fifty is the documented default: the fixture's three rows cannot show it,
    // so the constant is checked directly and the sentinel through behaviour.
    assert_eq!(spore_tools::DEFAULT_LIST_LIMIT, 50);
    let (_code, capped, _err) = osptool(&["list", MINI_PACKAGE]);
    assert!(capped.contains("3 shown"), "{capped}");
    let (_code, unlimited, _err) = osptool(&["list", MINI_PACKAGE, "--limit", "0"]);
    assert!(unlimited.contains("unlimited"), "{unlimited}");
}

#[test]
fn a_limit_below_the_row_count_reports_that_it_capped() {
    let image = common::package_of(
        &(0..10)
            .map(|index| Row::new(0x1111_1111, 0x2222_2222, index, vec![index as u8; 4]))
            .collect::<Vec<_>>(),
    );
    let file = common::temp_package("limit", &image);
    let path = file.path().display().to_string();

    let (code, out, _err) = osptool(&["list", &path, "--limit", "4"]);
    assert_eq!(code, EXIT_OK);
    assert!(out.contains("4 shown (limit 4)"), "{out}");
    assert_eq!(out.lines().count(), 6, "summary + header + 4 rows");

    let (_code, out, _err) = osptool(&["list", &path, "--limit", "0"]);
    assert!(out.contains("10 shown (unlimited)"), "{out}");
}

#[test]
fn the_type_and_group_filters_are_exact() {
    let (code, out, _err) = osptool(&["list", MINI_PACKAGE, "--type", "0x31534651"]);
    assert_eq!(code, EXIT_OK);
    let rows: Vec<&str> = out.lines().skip(2).collect();
    assert_eq!(rows.len(), 1, "{out}");
    assert!(rows[0].contains("0x31534651") && rows[0].contains("qfs"));

    let (_code, out, _err) = osptool(&["list", MINI_PACKAGE, "--group", "0x33333333"]);
    assert_eq!(out.lines().skip(2).count(), 1, "{out}");

    let (_code, out, _err) = osptool(&[
        "list",
        MINI_PACKAGE,
        "--type",
        "0x31534651",
        "--group",
        "0x11111111",
    ]);
    assert_eq!(
        out.lines().skip(2).count(),
        0,
        "an impossible pair yields no rows: {out}"
    );
}

#[test]
fn names_adds_two_columns_and_never_invents_a_name() {
    let (code, out, _err) = osptool(&["list", MINI_PACKAGE, "--names", "--limit", "1"]);
    assert_eq!(code, EXIT_OK);
    let header = out.lines().nth(1).expect("a header line");
    assert!(header.contains("type_name"), "{header}");
    assert!(header.contains("group_name"), "{header}");
    // The fixture's ids are synthetic: `TSTX`/`QFS1`/`RAWB` are not in the
    // canonical table, so the cell must be `-` rather than a guessed name.
    let row = out.lines().nth(2).expect("a row");
    assert!(row.contains('-'), "{row}");

    // A named type shows its name.
    let image = common::gmdl_package();
    let file = common::temp_package("names", &image);
    let path = file.path().display().to_string();
    let (code, out, _err) = osptool(&["list", &path, "--names"]);
    assert_eq!(code, EXIT_OK);
    assert!(out.contains("gmdl"), "{out}");
    assert!(out.contains("CellImages"), "{out}");
}

#[test]
fn the_json_view_has_the_documented_shape() {
    let (code, out, _err) = osptool(&["list", MINI_PACKAGE, "--json", "--limit", "0"]);
    assert_eq!(code, EXIT_OK);
    assert_eq!(out.lines().count(), 1, "a JSON array on one line");

    // Parsed back with the crate's own strict reader, so neither a syntax error
    // nor a lost field can pass. Substring assertions on top of that pin the
    // contents; the parse proves the document is real JSON.
    let parsed = spore_tools::json::parse(out.trim()).expect("valid JSON");
    let Json::Arr(rows) = &parsed else {
        panic!("expected a JSON array, got {parsed}")
    };
    assert_eq!(rows.len(), 3);
    let value = parsed.to_string();
    assert_eq!(value.matches("\"type_id\"").count(), 3, "{value}");
    for expected in EXPECTED {
        assert!(
            value.contains(&format!("\"type_id\":\"{}\"", expected.0)),
            "{value}"
        );
        assert!(
            value.contains(&format!("\"group_id\":\"{}\"", expected.1)),
            "{value}"
        );
        assert!(
            value.contains(&format!("\"instance_id\":\"{}\"", expected.2)),
            "{value}"
        );
    }
    // Ids are hex strings, so the document round-trips into another command.
    assert!(value.contains("\"type_id\":\"0x58545354\""), "{value}");
    // Unknown names are `null`, never a four-character code.
    assert!(value.contains("\"type_name\":null"), "{value}");
    // And the compression word is carried verbatim alongside the derived flag.
    assert!(value.contains("\"compression\":\"0x00000000\""), "{value}");
    assert!(value.contains("\"compression\":\"0x0000ffff\""), "{value}");
    assert!(value.contains("\"compressed\":true"), "{value}");
}

#[test]
fn the_json_view_reports_an_unlimited_run_identically_to_the_text_view() {
    // Same rows, so the counts in the two views must agree.
    let (_code, text, _err) = osptool(&["list", MINI_PACKAGE, "--limit", "0"]);
    let (_code, json, _err) = osptool(&["list", MINI_PACKAGE, "--json", "--limit", "0"]);
    assert!(text.contains("3 shown"));
    assert_eq!(json.matches("\"instance_id\"").count(), 3);
}

#[test]
fn two_runs_over_the_same_package_are_byte_identical() {
    let one = osptool(&["list", MINI_PACKAGE, "--json", "--names", "--limit", "0"]);
    let two = osptool(&["list", MINI_PACKAGE, "--json", "--names", "--limit", "0"]);
    assert_eq!(one, two);
    let one = osptool(&["list", MINI_PACKAGE, "--names", "--limit", "0"]);
    let two = osptool(&["list", MINI_PACKAGE, "--names", "--limit", "0"]);
    assert_eq!(one, two);
}
