//! `list`: enumerate a package's index rows in DBPF file order.
//!
//! File order, not sorted order, on purpose. The index order is the order the
//! container stores, so it is what a byte-level comparison against the file sees;
//! `manifest` is the command that sorts, because a canonical report has to.
//!
//! The type and group name columns are opt-in (`--names`). They are useful when
//! reading a census and noise when eyeballing a single package, and a column
//! whose only content is occasionally `-` is a column most people skip.

use std::io::Write;

use spore_dbpf::DbpfEntry;

use crate::json::{hex_id, Json};
use crate::{ListRequest, ToolError};

/// `list`: filter, cap and print.
pub fn run(request: &ListRequest, out: &mut dyn Write) -> Result<(), ToolError> {
    let store = super::single_package_store(&request.package)?;
    let package = &store.packages()[0];

    let rows: Vec<&DbpfEntry> = package
        .index()
        .entries()
        .iter()
        .filter(|entry| request.type_id.is_none_or(|wanted| entry.type_id == wanted))
        .filter(|entry| {
            request
                .group_id
                .is_none_or(|wanted| entry.group_id == wanted)
        })
        .collect();

    let shown = if request.limit == 0 {
        rows.len()
    } else {
        rows.len().min(request.limit)
    };

    if request.json {
        let array = Json::Arr(
            rows.iter()
                .take(shown)
                .enumerate()
                .map(|(index, entry)| row_json(entry, index))
                .collect(),
        );
        writeln!(out, "{array}")?;
        return Ok(());
    }

    let name = package.name();
    writeln!(
        out,
        "# {name}: {} record(s) in the index, {shown} shown{}",
        package.record_count(),
        if shown < rows.len() {
            format!(" (limit {})", request.limit)
        } else if request.limit == 0 {
            " (unlimited)".to_owned()
        } else {
            String::new()
        }
    )?;
    writeln!(out, "{}", header(request.names))?;
    for (index, entry) in rows.iter().take(shown).enumerate() {
        writeln!(out, "{}", row_text(entry, index, request.names))?;
    }
    Ok(())
}

/// The column header. The `names` variant inserts one column per name.
fn header(names: bool) -> String {
    if names {
        "  idx  type_id     type_name     group_id     group_name      instance  stored  memory  comp".to_owned()
    } else {
        "  idx  type_id     group_id     instance  stored  memory  comp".to_owned()
    }
}

/// One row, as a human line.
fn row_text(entry: &DbpfEntry, index: usize, names: bool) -> String {
    let type_cell = if names {
        format!(
            "0x{:08x} {:<12}",
            entry.type_id,
            super::type_name_of(entry.type_id).unwrap_or("-")
        )
    } else {
        format!("0x{:08x} ", entry.type_id)
    };
    let group_cell = if names {
        format!(
            "0x{:08x} {:<13}",
            entry.group_id,
            super::group_name_of(entry.group_id).unwrap_or("-")
        )
    } else {
        format!("0x{:08x} ", entry.group_id)
    };
    format!(
        "{index:5}  {type_cell}{group_cell}0x{:08x}  {:7}  {:6}  {}",
        entry.instance_id,
        entry.stored_size,
        entry.memory_size,
        super::compression_text(entry)
    )
}

/// One row as a JSON object, with a fixed key order.
///
/// Every id is a `0x`-prefixed hex *string* rather than a number, so the value
/// lifts out of this document and straight back into `osptool find`. Key order
/// is insertion order: this is why two runs over the same package are
/// byte-identical.
fn row_json(entry: &DbpfEntry, index: usize) -> Json {
    Json::obj()
        .push("index", Json::from(index))
        .push("type_id", hex_id(entry.type_id))
        .push("type_name", Json::from(super::type_name_of(entry.type_id)))
        .push("group_id", hex_id(entry.group_id))
        .push(
            "group_name",
            Json::from(super::group_name_of(entry.group_id)),
        )
        .push("instance_id", hex_id(entry.instance_id))
        .push("offset", hex_id(entry.offset))
        .push("stored_size", Json::from(entry.stored_size))
        .push("memory_size", Json::from(entry.memory_size))
        .push("compression", hex_id(u32::from(entry.compression)))
        .push("compressed", Json::from(entry.compressed))
}

#[cfg(test)]
mod tests {
    use super::*;
    use spore_assets::{ContentStore, Package};

    const FIXTURE: &str = concat!(
        env!("CARGO_MANIFEST_DIR"),
        "/../../tests/fixtures/mini_package.dbpf"
    );

    fn store() -> ContentStore {
        let mut store = ContentStore::new();
        store.push(Package::from_vec("mini", std::fs::read(FIXTURE).unwrap()).unwrap());
        store
    }

    fn text(request: &ListRequest) -> String {
        let mut buffer = Vec::new();
        run(request, &mut buffer).unwrap();
        String::from_utf8(buffer).unwrap()
    }

    #[test]
    fn every_fixture_row_is_listed_in_index_order() {
        let output = text(&ListRequest {
            package: FIXTURE.into(),
            type_id: None,
            group_id: None,
            limit: 0,
            json: false,
            names: false,
        });
        let body: Vec<&str> = output.lines().collect();
        assert_eq!(body.len(), 5, "header line, column header and 3 rows");
        assert!(body[0].contains("mini_package: 3 record(s)"), "{}", body[0]);
        assert!(body[0].contains("unlimited"));
        // TSTX, QFS1, RAWB -- the order gen_fixtures.py wrote them in.
        assert!(body[2].contains("0x58545354") && body[2].contains("0x22222222"));
        assert!(body[3].contains("0x31534651") && body[3].contains("0x44444444"));
        assert!(body[4].contains("0x42574152") && body[4].contains("0x66666666"));
    }

    #[test]
    fn the_limit_caps_rows_and_reports_that_it_did() {
        let output = text(&ListRequest {
            package: FIXTURE.into(),
            type_id: None,
            group_id: None,
            limit: 2,
            json: false,
            names: false,
        });
        let body: Vec<&str> = output.lines().collect();
        assert_eq!(body.len(), 4);
        assert!(body[0].contains("2 shown (limit 2)"));
    }

    #[test]
    fn names_adds_exactly_two_columns_and_marks_an_unknown_id() {
        let without = text(&ListRequest {
            package: FIXTURE.into(),
            type_id: None,
            group_id: None,
            limit: 1,
            json: false,
            names: false,
        });
        let with = text(&ListRequest {
            package: FIXTURE.into(),
            type_id: None,
            group_id: None,
            limit: 1,
            json: false,
            names: true,
        });
        assert!(!without.lines().nth(1).unwrap().contains("type_name"));
        let header = with.lines().nth(1).unwrap();
        assert!(header.contains("type_name") && header.contains("group_name"));
        // The fixture's three ids are synthetic and absent from the canonical
        // tables, so the name cell must read `-` rather than inventing one.
        assert!(with.lines().nth(2).unwrap().contains("-"));
    }

    #[test]
    fn a_compression_word_that_is_neither_none_nor_qfs_stays_visible() {
        let mut image = std::fs::read(FIXTURE).unwrap();
        // Row 1's compression word sits after the row's instance/offset/
        // stored/memory words: 96 + 4 + 28 + 22.
        let at = 96 + 4 + 28 + 24;
        image[at..at + 2].copy_from_slice(&0x1234u16.to_le_bytes());
        let package = Package::from_vec("odd", image).unwrap();
        let mut store = ContentStore::new();
        store.push(package);
        let entry = store.packages()[0].index().entries()[1];
        assert!(!entry.compressed);
        assert_eq!(
            super::super::compression_text(&entry),
            "unsupported(0x1234)"
        );
    }

    #[test]
    fn json_key_order_is_fixed_and_ids_are_hex_strings() {
        let entry = store().packages()[0].index().entries()[0];
        let rendered = row_json(&entry, 0).render();
        let expected_order = [
            "\"index\"",
            "\"type_id\"",
            "\"type_name\"",
            "\"group_id\"",
            "\"group_name\"",
            "\"instance_id\"",
            "\"offset\"",
            "\"stored_size\"",
            "\"memory_size\"",
            "\"compression\"",
            "\"compressed\"",
        ];
        let mut cursor = 0usize;
        for key in expected_order {
            let at = rendered[cursor..]
                .find(key)
                .unwrap_or_else(|| panic!("{key} missing or out of order in {rendered}"));
            cursor += at;
        }
        assert!(rendered.contains("\"type_id\":\"0x58545354\""));
        assert!(
            rendered.contains("\"type_name\":null"),
            "unknown name is null"
        );
        assert!(rendered.contains("\"compressed\":false"));
    }

    #[test]
    fn two_runs_produce_identical_bytes() {
        let request = ListRequest {
            package: FIXTURE.into(),
            type_id: None,
            group_id: None,
            limit: 0,
            json: true,
            names: true,
        };
        assert_eq!(text(&request), text(&request));
    }
}
