//! `types`: the canonical tables and the per-package histogram, including the
//! prop-directory scrape ported from `tools/spore/typescan.py`.

mod common;

use common::{osptool, package_of, Row, TempFile, MINI_PACKAGE};
use spore_assets::{ContentStore, Package};
use spore_tools::commands::types::{
    prop_directory_names, rank_types, scrape_pairs, PROP_DIRECTORY_GROUP,
};
use spore_tools::EXIT_OK;

#[test]
fn the_canonical_type_table_is_printed_in_id_order() {
    let (code, out, err) = osptool(&["types"]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains(&format!(
            "canonical type table ({} entries)",
            spore_core::record::TYPE_NAMES.len()
        )),
        "{out}"
    );
    let rows: Vec<&str> = out.lines().skip(2).collect();
    assert_eq!(rows.len(), spore_core::record::TYPE_NAMES.len());
    for (row, (id, name)) in rows.iter().zip(spore_core::record::TYPE_NAMES.iter()) {
        assert!(row.contains(&format!("0x{id:08x}")), "{row}");
        assert!(row.trim_end().ends_with(name), "{row}");
    }
    // Ascending.
    let ids: Vec<u32> = spore_core::record::TYPE_NAMES
        .iter()
        .map(|(id, _)| *id)
        .collect();
    let mut sorted = ids.clone();
    sorted.sort_unstable();
    assert_eq!(ids, sorted, "the canonical table itself must stay sorted");
}

#[test]
fn the_group_table_is_opt_in_and_matches_the_canonical_one() {
    let (_code, without, _err) = osptool(&["types"]);
    assert!(!without.contains("canonical group table"), "{without}");
    let (code, with, err) = osptool(&["types", "--group"]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        with.contains(&format!(
            "canonical group table ({} entries)",
            spore_core::record::GROUP_NAMES.len()
        )),
        "{with}"
    );
    for (id, name) in spore_core::record::GROUP_NAMES.iter() {
        assert!(
            with.contains(&format!("0x{id:08x}  {name}")),
            "missing {name}"
        );
    }
}

#[test]
fn a_package_histogram_counts_by_type_id_with_names() {
    let rows = vec![
        Row::new(0x00e6_bce5, 1, 1, vec![0; 4]),
        Row::new(0x00e6_bce5, 1, 2, vec![0; 4]),
        Row::new(0x2f4e_681b, 2, 1, vec![0; 4]),
        Row::new(0xdead_beef, 3, 1, vec![0; 4]),
    ];
    let file = TempFile::with("types-histogram", &package_of(&rows));
    let path = file.path().display().to_string();
    let (code, out, err) = osptool(&["types", "--package", &path]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains("per-package type histogram (4 record(s))"),
        "{out}"
    );
    // Most frequent first, then the equal-count pair in first-appearance order.
    assert!(out.contains("      2  0x00e6bce5  gmdl"), "{out}");
    assert!(out.contains("      1  0x2f4e681b  rw4"), "{out}");
    assert!(out.contains("      1  0xdeadbeef  ?"), "{out}");
    // An unknown id prints `?`, exactly as typescan.py does.
    assert_eq!(out.matches("  ?").count(), 1, "{out}");
}

#[test]
fn the_histogram_explains_that_the_prop_record_maps_types_not_instances() {
    let file = TempFile::with(
        "types-prop-note",
        &package_of(&[Row::new(1, 2, 3, vec![0; 4])]),
    );
    let path = file.path().display().to_string();
    let (_code, out, _err) = osptool(&["types", "--package", &path]);
    assert!(
        out.contains("prop directory, which maps TYPE IDS TO NAMES"),
        "{out}"
    );
    assert!(out.contains("and says nothing about instance ids"), "{out}");
    assert!(
        out.contains("0x01C7AC81:0x01C7AC81"),
        "the record is named by its identity so a reader can look it up: {out}"
    );
}

#[test]
fn the_prop_directory_names_override_the_canonical_table() {
    // `typescan.py` starts from the canonical table and lets each regex hit
    // overwrite it, so a package-local spelling wins. Here the blob names a type
    // the canonical table already knows, under a different name.
    let blob = b"0x00e6bce5GmdlLocal0x2f4e681brw4";
    let rows = vec![
        Row::new(0x00e6_bce5, 1, 1, vec![0; 4]),
        Row::new(0x2f4e_681b, 2, 1, vec![0; 4]),
        Row::new(
            0x01c7_ac81,
            PROP_DIRECTORY_GROUP,
            PROP_DIRECTORY_GROUP,
            blob.to_vec(),
        ),
    ];
    let image = package_of(&rows);
    let file = TempFile::with("types-propoverride", &image);
    let path = file.path().display().to_string();
    let (code, out, err) = osptool(&["types", "--package", &path]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains("0x00e6bce5  GmdlLocal"),
        "the package's own name must win: {out}"
    );
    assert!(
        out.contains("0x2f4e681b  rw4"),
        "both spellings parse: {out}"
    );

    // And the library-level view agrees with what was printed.
    let mut store = ContentStore::new();
    store.push(Package::from_vec("t", image).expect("a valid package"));
    let scraped = prop_directory_names(&store);
    assert!(
        scraped.contains(&(0x00e6_bce5, "GmdlLocal".to_owned())),
        "{scraped:?}"
    );
    assert!(
        scraped.contains(&(0x2f4e_681b, "rw4".to_owned())),
        "{scraped:?}"
    );
}

#[test]
fn a_package_with_no_prop_directory_falls_back_to_the_canonical_table() {
    // `mini_package.dbpf` holds no `0x1C7AC81:0x1C7AC81` record, so every name
    // comes from the canonical table and the three synthetic ids read `?`.
    let (code, out, err) = osptool(&["types", "--package", MINI_PACKAGE]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains("per-package type histogram (3 record(s))"),
        "{out}"
    );
    assert!(out.contains("0x58545354  ?"), "{out}");
    assert!(out.contains("0x31534651  ?"), "{out}");
    assert!(out.contains("0x42574152  ?"), "{out}");

    let mut store = ContentStore::new();
    store.push(Package::open("mini", MINI_PACKAGE).expect("opens"));
    assert!(
        prop_directory_names(&store).is_empty(),
        "no prop directory means no scraped names, and that is not an error"
    );
}

#[test]
fn the_prop_record_is_located_by_group_and_instance_only() {
    // The oracle does not constrain the type id, so a prop record of *any* type
    // is found. An implementation that also required a particular type would
    // silently find nothing in a package that uses a different one.
    for type_id in [0x00b1_b104u32, 0x0000_0001, 0xdead_beef] {
        let rows = vec![Row::new(
            type_id,
            PROP_DIRECTORY_GROUP,
            PROP_DIRECTORY_GROUP,
            b"0x00e6bce5gmdl".to_vec(),
        )];
        let image = package_of(&rows);
        let mut store = ContentStore::new();
        store.push(Package::from_vec("t", image).expect("a valid package"));
        assert_eq!(
            prop_directory_names(&store),
            vec![(0x00e6_bce5, "gmdl".to_owned())],
            "prop record with type 0x{type_id:08x} must still be found"
        );
    }
}

#[test]
fn the_scrape_reproduces_the_oracle_case_for_case() {
    // Golden answers taken from running `tools/spore/typescan.py`'s
    // filter-and-regex under Python 3. See the same table in the unit tests;
    // this one goes through the whole pipeline including the printable filter.
    for (blob, expected) in [
        (
            &b"0x00e6bce5gmdl0x2f4e681brw40x2f4e681craster"[..],
            vec![
                (0x00e6_bce5, "gmdl"),
                (0x2f4e_681b, "rw4"),
                (0x2f4e_681c, "raster"),
            ],
        ),
        (&b"0x00e6bce5gmdl and more"[..], vec![]),
        (&b"0x00E6BCE5gmdl"[..], vec![]),
        (&b"0x00e6bce5g"[..], vec![(0x00e6_bce5, "g")]),
    ] {
        let text: String = blob
            .iter()
            .map(|&byte| char::from(byte))
            .filter(|c| !c.is_control() && !c.is_whitespace() || *c == ' ')
            .collect();
        let got: Vec<(u32, String)> = scrape_pairs(&text);
        let want: Vec<(u32, String)> = expected
            .into_iter()
            .map(|(id, name)| (id, name.to_owned()))
            .collect();
        assert_eq!(got, want, "blob {blob:?}");
    }
}

#[test]
fn the_histogram_is_ranked_by_count_then_first_appearance() {
    // Counts: 1 -> 3, 2 -> 1, 3 -> 2. Order: count descending, and the equal-count
    // tie-break is first appearance, which here does not bite -- so this pins the
    // primary key. The tie-break has its own unit test next to `rank_types`.
    assert_eq!(
        rank_types([1u32, 1, 1, 2, 3, 3].into_iter()),
        vec![(1, 3), (3, 2), (2, 1)]
    );
    // An empty index yields nothing rather than an empty-but-present bucket.
    assert!(rank_types(std::iter::empty()).is_empty());
}

#[test]
fn two_runs_produce_identical_output() {
    let file = TempFile::with(
        "types-determinism",
        &package_of(&[
            Row::new(0x00e6_bce5, 1, 1, vec![0; 4]),
            Row::new(0x2f4e_681b, 2, 1, vec![0; 4]),
        ]),
    );
    let path = file.path().display().to_string();
    let args = ["types", "--group", "--package", path.as_str()];
    assert_eq!(osptool(&args), osptool(&args));
}
