//! The Cell-stage records, against the real game data.
//!
//! **Ignored by default.** These tests need the git-ignored `SPORE/` tree, so
//! they run only when asked for on a machine that has the game installed:
//!
//! ```text
//! cargo test -p spore-cellcontent --release --test real_corpus -- --ignored --nocapture
//! ```
//!
//! The package directory comes from `OPENSPORE_SPORE_DATA` when set, and
//! otherwise from the repository's own `SPORE/`. If neither exists the tests
//! still pass — by saying so — because a missing game install is not a failure
//! of this crate. **No Spore byte is ever written to disk or compared against a
//! committed fixture**: the bytes are read through `spore-assets` and every
//! assertion is about counts, extents and domain invariants.
//!
//! What these tests measure, and what they deliberately do not:
//!
//! * **counts per record type** across the three packages that hold them;
//! * **decoded / refused**, with the distinct refusal reasons named;
//! * **domain issues**, grouped by kind, so a checker that starts manufacturing
//!   findings is visible as a number rather than as a wall of text;
//! * **reference resolution**, split into resolved / missed / non-finding — the
//!   three-way split being the point.
//!
//! What they do **not** do: compare a decoded value against a golden literal.
//! There is no committed fixture for these records and inventing one would mean
//! committing a Spore byte.

mod support;

use std::collections::BTreeMap;
use std::path::{Path, PathBuf};

use spore_assets::{ContentStore, Package};
use spore_cellcontent::{
    decode, CellCatalogue, CellContentRecord, CellIssue, CellReferenceError, IssueKind,
    SUPPORTED_TYPES,
};

use support::all_types;

/// The packages that hold the Cell-stage records, relative to the **install
/// root** (the directory named `SPORE`).
///
/// **Patches are pushed first, deliberately.** See
/// [`the_globals_record_has_two_revisions_in_one_install`] for why: the base
/// package holds a *264-byte* revision of the globals record where the patches
/// hold the 276-byte one, and `ContentStore` resolves first match wins.
const PACKAGES: [(&str, &str); 3] = [
    ("Spore_Game", "Data/Spore_Game.package"),
    ("PatchData", "Data/PatchData.package"),
    ("Spore_EP1_Data", "DataEP1/Spore_EP1_Data.package"),
];

/// The install root, from `OPENSPORE_SPORE_DATA` when set.
///
/// The variable names the directory that *contains* `Data/` and `DataEP1/` --
/// the same `SPORE/` the oracles walk -- and not a single `.package` file.
fn spore_root() -> Option<PathBuf> {
    if let Ok(root) = std::env::var("OPENSPORE_SPORE_DATA") {
        if !root.is_empty() {
            let path = PathBuf::from(&root);
            assert!(
                path.is_dir(),
                "OPENSPORE_SPORE_DATA={root:?} is not a directory"
            );
            return Some(path);
        }
    }
    let path = Path::new(concat!(env!("CARGO_MANIFEST_DIR"), "/../../SPORE"));
    path.is_dir().then(|| path.to_owned())
}

/// Opens the store, or `None` when the game is not installed.
///
/// Returns `None` **only** for a missing install; a package that exists but
/// fails to open is a hard failure, because that is a real regression.
fn open_store() -> Option<(ContentStore, Vec<(String, PathBuf)>)> {
    let root = spore_root()?;
    let mut store = ContentStore::new();
    let mut opened = Vec::new();
    let mut packages = Vec::new();
    for (name, relative) in PACKAGES {
        let path = root.join(relative);
        if !path.is_file() {
            continue;
        }
        let package =
            Package::open(name, &path).unwrap_or_else(|error| panic!("{name} must open: {error}"));
        packages.push((name.to_owned(), path, package));
    }
    // `push_front` inserts at index 0, so walking the table in order and pushing
    // each package to the front leaves the *last* row with the highest priority:
    // `Spore_EP1_Data` overrides `PatchData` overrides `Spore_Game`. That is the
    // correct order for a patch overlay and it is also what makes the globals
    // record resolve to its 276-byte revision -- see
    // `the_globals_record_has_two_revisions_in_one_install`.
    for (name, path, package) in packages {
        store.push_front(package);
        opened.push((name, path));
    }
    assert!(
        !opened.is_empty(),
        "OPENSPORE_SPORE_DATA pointed at a directory with none of the three packages"
    );
    Some((store, opened))
}

/// Decodes every record of `type_id` and reports the outcome per distinct
/// reason, so a run that starts refusing records says *why* rather than just
/// how many.
#[derive(Debug, Default)]
struct DecodeTally {
    found: usize,
    decoded: usize,
    /// `(reason, count)` — the first line of each distinct error message.
    refusals: BTreeMap<String, usize>,
}

fn decode_all(store: &ContentStore, type_id: u32) -> (DecodeTally, Vec<CellContentRecord>) {
    let mut tally = DecodeTally::default();
    let mut records = Vec::new();
    for key in store.identities_of_type(type_id) {
        tally.found += 1;
        let bytes = store
            .read(&key)
            .unwrap_or_else(|error| panic!("{key} must read: {error}"));
        match decode(type_id, &bytes) {
            Ok(value) => {
                tally.decoded += 1;
                records.push(CellContentRecord::new(key, value));
            }
            Err(error) => {
                let reason = error
                    .to_string()
                    .split("header field")
                    .next()
                    .unwrap_or("unclassified")
                    .trim()
                    .to_owned();
                *tally.refusals.entry(reason).or_default() += 1;
            }
        }
    }
    (tally, records)
}

// ---------------------------------------------------------------------------
// per-type census
// ---------------------------------------------------------------------------

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn every_cell_content_record_in_the_install_decodes() {
    let Some((store, opened)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the directory containing Data/ and \
             DataEP1/ (a missing game install is not a failure of this crate)"
        );
        return;
    };
    println!(
        "packages: {}",
        opened
            .iter()
            .map(|(name, _)| name.as_str())
            .collect::<Vec<_>>()
            .join(", ")
    );

    let mut total_records = 0usize;
    let mut catalogue = CellCatalogue::new();

    // Pass 1: decode every record and fill the catalogue. **Every** record must
    // be in the catalogue before any cross-record check runs -- `cell` is the
    // LAST of the twelve type ids, so validating as we go would report every
    // `populate` and `lootTable` cell reference as unresolved.
    for type_id in SUPPORTED_TYPES {
        let (tally, records) = decode_all(&store, type_id);
        println!(
            "{:<16} 0x{type_id:08x}  found={:<5} decoded={:<5}",
            record_name(type_id),
            tally.found,
            tally.decoded
        );
        for (reason, count) in &tally.refusals {
            println!("    refused {count}: {reason}");
        }
        assert_eq!(
            tally.decoded, tally.found,
            "0x{type_id:08x}: every real record must decode"
        );
        total_records += tally.decoded;
        for record in records {
            catalogue.add(record);
        }
    }

    // Pass 2: validate, with a complete catalogue.
    let mut all_issues: BTreeMap<(&'static str, &'static str), usize> = BTreeMap::new();
    let mut examples: BTreeMap<(&'static str, &'static str), String> = BTreeMap::new();
    for record in catalogue.sorted() {
        for issue in record.value.issues(&catalogue) {
            *all_issues
                .entry((record_name(record.key.type_id), issue.field))
                .or_default() += 1;
            examples
                .entry((record_name(record.key.type_id), issue.field))
                .or_insert_with(|| format!("{} at {}", issue.describe(), record.key));
        }
    }

    println!("\ntotal decoded cell-content records: {total_records}");
    println!(
        "catalogue: {} identities, {} decoded records",
        catalogue.identity_count(),
        catalogue.record_count()
    );
    println!("domain issues by record and field:");
    if all_issues.is_empty() {
        println!("    (none: every record in the install is inside every observed bound)");
    }
    for ((record_name, field), count) in &all_issues {
        println!("    {record_name:<16} {field:<26} {count}");
    }
    for ((record_name, field), example) in &examples {
        println!("        {record_name:<16} {field:<26} {example}");
    }
    assert_eq!(
        total_records,
        catalogue.record_count(),
        "the census and the catalogue must agree"
    );
}

/// The twelve type ids with the names this crate uses for them in reports.
const NAMES: [(u32, &str); 12] = [
    (spore_cellcontent::GLOBALS_TYPE, "globals"),
    (spore_cellcontent::EFFECT_MAP_TYPE, "effectMap"),
    (spore_cellcontent::BACKGROUND_MAP_TYPE, "backgroundMap"),
    (spore_cellcontent::STRUCTURE_TYPE, "structure"),
    (spore_cellcontent::WORLD_TYPE, "world"),
    (spore_cellcontent::RANDOM_CREATURE_TYPE, "randomCreature"),
    (spore_cellcontent::POWERS_TYPE, "powers"),
    (spore_cellcontent::LOOK_TABLE_TYPE, "look_table"),
    (spore_cellcontent::LOOK_ALGORITHM_TYPE, "look_algorithm"),
    (spore_cellcontent::LOOT_TABLE_TYPE, "lootTable"),
    (spore_cellcontent::POPULATE_TYPE, "populate"),
    (spore_cellcontent::CELL_TYPE, "cell"),
];

fn record_name(type_id: u32) -> &'static str {
    NAMES
        .iter()
        .find(|(id, _)| *id == type_id)
        .map_or("unknown", |(_, name)| *name)
}

// ---------------------------------------------------------------------------
// reference resolution
// ---------------------------------------------------------------------------

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn references_resolve_and_the_non_findings_stay_separate_from_the_misses() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };

    let mut catalogue = CellCatalogue::new();
    for type_id in all_types() {
        let (_, records) = decode_all(&store, type_id);
        for record in records {
            catalogue.add(record);
        }
    }

    let mut emitted = 0usize;
    let mut resolved = 0usize;
    let mut missed = 0usize;
    let mut non_findings: BTreeMap<String, usize> = BTreeMap::new();
    let mut misses: BTreeMap<String, usize> = BTreeMap::new();

    for record in catalogue.sorted() {
        for reference in record.references() {
            emitted += 1;
            let resolver = spore_cellcontent::CellReferenceResolver::new(&catalogue);
            match resolver.resolve(record, &reference, None) {
                Ok(_) => resolved += 1,
                Err(error) => {
                    // The index is part of the field's identity for the two
                    // start-cell slots, which share one `CellReferenceField`.
                    let field = format!("{}#{}", reference.field.as_str(), reference.index);
                    if error.is_non_finding() {
                        *non_findings.entry(field).or_default() += 1;
                    } else {
                        missed += 1;
                        *misses.entry(field).or_default() += 1;
                    }
                    let _ = error;
                }
            }
        }
    }

    println!("references emitted: {emitted}");
    println!("  resolved:            {resolved}");
    println!("  unresolved (missed): {missed}");
    println!(
        "  non-findings:        {}",
        non_findings.values().sum::<usize>()
    );
    println!("non-findings by field:");
    for (field, count) in &non_findings {
        println!("    {field:<32} {count}");
    }
    if !misses.is_empty() {
        println!("misses by field:");
        for (field, count) in &misses {
            println!("    {field:<32} {count}");
        }
    }
    assert!(emitted > 0, "the install holds references");
}

// ---------------------------------------------------------------------------
// layout spot-checks against the measured corpus
// ---------------------------------------------------------------------------

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn the_fixed_extent_records_hold_their_documented_length_on_every_record() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };
    for (type_id, extent) in [
        (
            spore_cellcontent::GLOBALS_TYPE,
            spore_cellcontent::GLOBALS_SIZE,
        ),
        (
            spore_cellcontent::CELL_TYPE,
            spore_cellcontent::cell::CELL_SIZE,
        ),
        (
            spore_cellcontent::POWERS_TYPE,
            spore_cellcontent::spawn::POWERS_SIZE,
        ),
    ] {
        let keys = store.identities_of_type(type_id);
        assert!(
            !keys.is_empty(),
            "0x{type_id:08x} is absent from the install"
        );
        for key in &keys {
            let bytes = store.read(key).unwrap_or_else(|e| panic!("{key}: {e}"));
            assert_eq!(
                bytes.len(),
                extent,
                "{key} is {} bytes, not the documented {extent}",
                bytes.len()
            );
        }
        println!(
            "0x{type_id:08x}: {} records, all {extent} bytes",
            keys.len()
        );
    }
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn every_real_cell_name_decodes_as_utf16() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };
    let mut named = 0usize;
    let mut total = 0usize;
    let mut longest = 0usize;
    let mut samples: Vec<(u32, String)> = Vec::new();
    for key in store.identities_of_type(spore_cellcontent::CELL_TYPE) {
        let bytes = store.read(&key).expect("reads");
        let spore_cellcontent::CellContent::Cell(cell) =
            decode(spore_cellcontent::CELL_TYPE, &bytes).expect("decodes")
        else {
            panic!("wrong variant");
        };
        total += 1;
        longest = longest.max(cell.name.chars().count());
        if !cell.name.is_empty() {
            named += 1;
            if samples.len() < 8 {
                samples.push((key.instance_id, cell.name.clone()));
            }
        }
        // Every real name is short: a buffer full of characters would mean the
        // decoder is reading bytes as code units somewhere.
        assert!(
            cell.name.chars().count() <= spore_cellcontent::cell::NAME_UNITS,
            "{key}: a name longer than the buffer means the width is wrong"
        );
    }
    println!("cell records: {total}, named: {named}, longest name: {longest} chars");
    for (instance, name) in &samples {
        println!("    0x{instance:08x} {name:?}");
    }
    assert!(named > 0, "a stock install has named cells");
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn the_globals_record_is_the_documented_size_and_has_a_sane_domain() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };
    let keys = store.identities_of_type(spore_cellcontent::GLOBALS_TYPE);
    assert_eq!(keys.len(), 1, "a stock install has one globals record");
    let key = keys[0];
    println!("globals record: {key}");
    assert_eq!(
        key,
        spore_cellcontent::globals::KNOWN_GLOBALS_KEY,
        "the documented identity of the one globals record"
    );
    let bytes = store.read(&key).expect("reads");
    let spore_cellcontent::CellContent::Globals(globals) =
        decode(spore_cellcontent::GLOBALS_TYPE, &bytes).expect("decodes")
    else {
        panic!("wrong variant");
    };
    assert_eq!(spore_cellcontent::globals::GLOBALS_LAYOUT.len(), 69);
    let catalogue = CellCatalogue::new();
    let issues = spore_cellcontent::globals_issues(&globals, &catalogue);
    for issue in &issues {
        println!("    {}", issue.describe());
    }
    println!(
        "globals domain issues against an empty catalogue: {}",
        issues.len()
    );
    // Only the seventeen reference slots can complain here, because they are the
    // only fields with no in-domain zero.
    assert!(
        issues
            .iter()
            .all(|issue| issue.kind == IssueKind::UnresolvedReference),
        "the one real globals record has no out-of-domain value: {:?}",
        issues.iter().map(CellIssue::describe).collect::<Vec<_>>()
    );
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn the_background_ramp_samples_and_envelopes_over_the_real_record() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };
    let keys = store.identities_of_type(spore_cellcontent::BACKGROUND_MAP_TYPE);
    assert_eq!(keys.len(), 1, "a stock install has one background map");
    let bytes = store.read(&keys[0]).expect("reads");
    let spore_cellcontent::CellContent::BackgroundMap(ramp) =
        decode(spore_cellcontent::BACKGROUND_MAP_TYPE, &bytes).expect("decodes")
    else {
        panic!("wrong variant");
    };
    println!(
        "background ramp: {} stops at {:?}",
        ramp.entries.len(),
        ramp.entries.iter().map(|e| e.field_c).collect::<Vec<_>>()
    );
    let envelope = spore_cellcontent::background_color_envelope(&ramp).expect("non-empty");
    println!("colour envelope (min rgb, max rgb): {envelope:?}");
    for ladder in [0.0f32, 1.0, 50.0, 5000.0, 1.0e6] {
        let colour = spore_cellcontent::sample_background_color(&ramp, ladder)
            .unwrap_or_else(|| panic!("a non-empty ramp samples at {ladder}"));
        println!("    ladder {ladder:>10}: rgb = {colour:?}");
    }
    // The observed ladder is geometric on its interior steps, alternating a
    // factor of 3.0 and 3.33. Two ends are not ladder steps: the first stop is
    // `0.0` (no predecessor, and `log2(0)` is undefined), and the last is
    // `100000`, a clamp above the final `3.33` step rather than another step of
    // it -- its ratio is 6.67.
    for pair in ramp.entries.windows(2).skip(1).take(ramp.entries.len() - 3) {
        let ratio = pair[1].field_c / pair[0].field_c;
        assert!(
            (2.9..=3.4).contains(&ratio),
            "the ladder is not geometric at {}: ratio {ratio}",
            pair[0].field_c
        );
    }
    assert_eq!(ramp.entries.last().map(|e| e.field_c), Some(100000.0));
    assert_eq!(ramp.entries.first().map(|e| e.field_c), Some(0.0));
    assert_eq!(
        spore_cellcontent::background_map_issues(&ramp),
        Vec::new(),
        "the one real background map is inside every observed bound"
    );
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn every_reference_error_the_install_produces_is_typed() {
    let Some((store, _)) = open_store() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to the install root containing Data/ and DataEP1/"
        );
        return;
    };
    let mut catalogue = CellCatalogue::new();
    for type_id in all_types() {
        let (_, records) = decode_all(&store, type_id);
        for record in records {
            catalogue.add(record);
        }
    }
    let resolver = spore_cellcontent::CellReferenceResolver::new(&catalogue);
    let mut kinds: BTreeMap<&'static str, usize> = BTreeMap::new();
    for record in catalogue.sorted() {
        for reference in record.references() {
            if let Err(error) = resolver.resolve(record, &reference, None) {
                let name = match error {
                    CellReferenceError::IncompleteSource { .. } => "incomplete-source",
                    CellReferenceError::SourceMismatch { .. } => "source-mismatch",
                    CellReferenceError::NotAReference { .. } => "not-a-reference",
                    CellReferenceError::UnknownTypeWord { .. } => "unknown-type-word",
                    CellReferenceError::OutsideFamily { .. } => "outside-family",
                    CellReferenceError::TargetTypeMismatch { .. } => "target-type-mismatch",
                    CellReferenceError::NotFound { .. } => "not-found",
                    CellReferenceError::Ambiguous { .. } => "ambiguous",
                };
                *kinds.entry(name).or_default() += 1;
            }
        }
    }
    println!("reference failures by variant:");
    for (name, count) in &kinds {
        println!("    {name:<22} {count}");
    }
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn the_globals_record_has_two_revisions_in_one_install() {
    // FINDING, pinned as a regression test.
    //
    // `0x2A3CE5B7:0x00000000:0xa426730b` exists in THREE packages with TWO
    // byte-distinct revisions:
    //
    //   Spore_Game        264 bytes
    //   PatchData         276 bytes
    //   Spore_EP1_Data    276 bytes  (byte-identical to PatchData)
    //
    // A word-level alignment shows the 264-byte copy is NOT a truncation and NOT
    // a shift: it is the same record with exactly three fields absent --
    // `gameMode` (offset 0), `startingCellKey` (offset 56) and `controlMethod`
    // (offset 212). Every other word is byte-identical. So
    // `cCellGlobalsResource` grew by three fields between the base game and the
    // expansion pack, and the three it gained are all "which mode / which cell /
    // which control scheme" selectors.
    //
    // `docs`-wise this is not recorded anywhere: `src/assets/CellResource.hpp`
    // says the record "lives in SPORE/DataEP1/Spore_EP1_Data.package", which is
    // true of that package and silent about the other two. `tools/spore/cellres/
    // cellres.py` only ever loads the EP1 copy, so its `size=276 fields=69
    // violations=0` line never sees the base revision.
    //
    // Consequence for a caller: the honest answer to the 264-byte copy is a
    // typed refusal. Padding it out to 276 would fabricate three fields, and
    // `decode` does not do that.
    let Some(root) = spore_root() else {
        eprintln!("skipping: set OPENSPORE_SPORE_DATA to the install root");
        return;
    };
    let type_id = spore_cellcontent::GLOBALS_TYPE;
    let mut lengths: Vec<(&str, usize)> = Vec::new();
    let mut blobs: Vec<(&str, Vec<u8>)> = Vec::new();
    for (name, relative) in PACKAGES {
        let path = root.join(relative);
        if !path.is_file() {
            continue;
        }
        let package = Package::open(name, &path).expect("opens");
        for key in package.index().of_type(type_id) {
            let bytes = spore_cellcontent_bytes(&package, key);
            lengths.push((name, bytes.len()));
            blobs.push((name, bytes));
        }
    }
    assert!(!lengths.is_empty(), "no globals record in the install");
    for (name, len) in &lengths {
        println!("globals in {name:<20} is {len} bytes");
    }
    assert!(
        lengths
            .iter()
            .any(|(_, len)| *len == spore_cellcontent::GLOBALS_SIZE),
        "at least one copy is the documented 276 bytes: {lengths:?}"
    );

    // The short revision is refused with a typed error, not padded.
    for (name, bytes) in &blobs {
        if bytes.len() == spore_cellcontent::GLOBALS_SIZE {
            assert!(
                decode(type_id, bytes).is_ok(),
                "the 276-byte copy in {name} must decode"
            );
            continue;
        }
        let error = decode(type_id, bytes).expect_err("the short revision is refused");
        assert_eq!(
            error,
            spore_cellcontent::CellContentError::ExtentMismatch {
                type_id,
                actual: bytes.len(),
                expected: spore_cellcontent::GLOBALS_SIZE,
            },
            "the {name} copy is refused with the lengths, not invented"
        );
    }

    // And the three absent fields are exactly the ones the alignment names.
    let short = blobs
        .iter()
        .find(|(_, bytes)| bytes.len() != spore_cellcontent::GLOBALS_SIZE)
        .map(|(_, bytes)| bytes.as_slice());
    let long = blobs
        .iter()
        .find(|(_, bytes)| bytes.len() == spore_cellcontent::GLOBALS_SIZE)
        .map(|(_, bytes)| bytes.as_slice());
    if let (Some(short), Some(long)) = (short, long) {
        let absent = ["gameMode", "startingCellKey", "controlMethod"];
        for name in absent {
            let index = spore_cellcontent::globals::GLOBALS_LAYOUT
                .iter()
                .position(|spec| spec.name == name)
                .unwrap_or_else(|| panic!("{name} is not a layout field"));
            let word = u32::from_le_bytes([
                long[index * 4],
                long[index * 4 + 1],
                long[index * 4 + 2],
                long[index * 4 + 3],
            ]);
            // The word is absent from the short copy: it appears 66-3 times
            // where it appears 69 times in the long one, and the remaining 63
            // words are byte-identical. Recompute the short record with the
            // three words spliced out and require equality.
            let mut spliced = Vec::with_capacity(long.len() - 12);
            for (position, _) in spore_cellcontent::globals::GLOBALS_LAYOUT
                .iter()
                .enumerate()
            {
                if absent.contains(&spore_cellcontent::globals::GLOBALS_LAYOUT[position].name) {
                    continue;
                }
                spliced.extend_from_slice(&long[position * 4..position * 4 + 4]);
                let _ = word;
            }
            assert_eq!(
                spliced.as_slice(),
                short,
                "removing exactly {name} (and its two siblings) must reproduce \
                 the base revision byte for byte"
            );
        }
    }
}

/// Reads one record's bytes straight out of a single package, bypassing the
/// store's priority order — the only way to see the base revision of a record
/// that a patch overrides.
fn spore_cellcontent_bytes(package: &Package, entry: &spore_dbpf::DbpfEntry) -> Vec<u8> {
    spore_dbpf::extract_record(package.bytes(), entry)
        .unwrap_or_else(|error| panic!("{} must read: {error}", entry.key))
}
