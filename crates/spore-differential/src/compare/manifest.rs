//! Comparison 6: the manifest -- row count, ordering, and what "decodable" means.
//!
//! Rust `spore_assets::ManifestBuilder::from_store` against
//! `tools/spore/manifest/manifest.py`'s own row builder, over one package.
//!
//! # Three questions
//!
//! 1. Do the two sides produce the same number of rows?
//! 2. Do the rows come out ascending by `(type, group, instance)` on both
//!    sides?
//! 3. Which type ids does each side call decodable?
//!
//! # Question 3 is expected to differ, and is reported as a definition, not a bug
//!
//! `spore-assets` means `DecodeStatus::Ok` = "**this workspace has a per-record
//! decoder for this type id**", and its list is exactly `gmdl`, `rw4`, `raster`
//! -- it was deliberately shortened when `png`/`jpeg`/`gmsh`/`plt` were removed
//! for exactly the reason this comparison exists.
//!
//! `manifest.py` means something looser: `raster`/`jpeg`/`png`/`plt` are `ok`
//! whenever `msize >= 16`, and `gmdl`/`gmsh` get a cheap structural probe.
//!
//! So the two sets are compared and both printed in full, classified as
//! [`DivergenceClass::Definitional`]. Neither side is "wrong": they answer
//! different questions, and the report says so.
//!
//! # One real defect this comparison is expected to expose
//!
//! `manifest.py::probe_gmdl` slices `data[off : off+min(csize,msize,…)]` -- the
//! **stored, still-compressed** bytes -- while every gmdl record in the installed
//! content package is QFS-compressed. The driver calls the module's own `_row`
//! with the module's own `data`, so this harness does **not** correct it: if
//! that is why the oracle calls all 4209 gmdl records `walk-fail`, the report
//! will say so with both lists, and the fix belongs in whichever side owns the
//! definition.

use spore_assets::{ContentStore, ManifestBuilder, Package};

use crate::corpus::{Corpus, LocatedPackage};
use crate::floats::ReportBuilder;
use crate::json::Json;
use crate::oracle::{OracleConfig, OracleError, OracleSession};
use crate::report::{DifferentialReport, Divergence, DivergenceClass, RecordIdentity};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "manifest-rows";

/// How the oracle is invoked.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one NDJSON \
                              {cmd:\"manifest\"} request answered from manifest.py's own _row() \
                              and the same (type, group, instance) sort build() uses";

/// Runs the manifest comparison over the corpus's primary package.
pub fn compare(corpus: &Corpus, config: &OracleConfig) -> DifferentialReport {
    super::run(NAME, || {
        let Some(package) = primary_package(corpus) else {
            return Ok::<_, OracleError>(skipped(
                NAME,
                format!(
                    "no package located (set {} to a checkout with SPORE/)",
                    crate::corpus::ROOT_ENV
                ),
            ));
        };
        compare_package(package, config)
    })
}

/// Runs the manifest comparison over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {}; Rust side: ManifestBuilder::from_store over a ContentStore holding exactly \
         this package; oracle: manifest.py's _row() over the same rows",
        package.name
    ));
    builder.note(
        "the Rust side means DecodeStatus::Ok = \"a per-record decoder exists in this workspace\"; \
         manifest.py means a looser \"looks decodable\" (msize >= 16 for raster-family types, a \
         cheap header probe for gmdl/gmsh). The two sets are therefore EXPECTED to differ and are \
         reported as a definitional difference with both lists quoted.",
    );

    let store = {
        let mut store = ContentStore::new();
        store.push(
            Package::open(package.name.clone(), &package.path).map_err(|error| {
                OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
            })?,
        );
        store
    };
    let manifest = ManifestBuilder::from_store(&store);
    let rows: Vec<_> = manifest.rows().cloned().collect();
    let rust_status_counts = manifest.decode_status_counts();
    let rust_decodable = decodable_types(&rows);

    let mut session = OracleSession::spawn(config)?;
    session.open(&package.path)?;
    let reply = session.request_manifest()?;

    let oracle_rows = reply.get("rows").and_then(Json::as_u32).unwrap_or(0) as usize;
    let identity = RecordIdentity::new(package.name.clone(), 0, 0, 0, 0);

    // ---- 1. row count ------------------------------------------------------
    if rows.len() != oracle_rows {
        builder.divergence(
            Divergence::value(
                identity.clone(),
                "rows",
                oracle_rows.to_string(),
                rows.len().to_string(),
            )
            .with_class(DivergenceClass::Structural)
            .with_note(
                "one row per (type, group, instance); the Rust builder de-duplicates by \
                     identity and the reference builder does the same via its PRIMARY KEY, so a \
                     difference here means the two sides saw different records",
            ),
        );
    } else {
        builder.record(crate::report::Agreement::Equal);
        builder.note(format!("row count agrees: {oracle_rows}"));
    }

    // ---- 2. ordering -------------------------------------------------------
    let rust_ordered = is_ascending(&rows);
    let oracle_ordered = reply.get("ordered").and_then(Json::as_bool);
    builder.note(format!(
        "ordering ascending by (type, group, instance): rust={rust_ordered} oracle={oracle_ordered:?}"
    ));
    if !rust_ordered {
        builder.divergence(
            Divergence::value(
                identity.clone(),
                "rows.ordered",
                format!("{oracle_ordered:?}"),
                "false".to_owned(),
            )
            .with_class(DivergenceClass::Structural)
            .with_note("the Rust rows came out of a BTreeMap keyed by ResourceKey, so this should be unreachable"),
        );
    }
    if oracle_ordered == Some(false) {
        builder.divergence(
            Divergence::value(
                identity.clone(),
                "rows.ordered",
                "false".to_owned(),
                "true".to_owned(),
            )
            .with_class(DivergenceClass::Structural),
        );
    }

    // ---- 3. classification -------------------------------------------------
    let oracle_decodable: Vec<u32> = reply
        .get("decodable")
        .and_then(Json::as_array)
        .map(|items| items.iter().filter_map(Json::as_u32).collect())
        .unwrap_or_default();
    let rust_counts: Vec<String> = rust_status_counts
        .iter()
        .map(|(status, count)| format!("{status}={count}"))
        .collect();
    builder.note(format!(
        "rust decode_status counts (records): {}",
        rust_counts.join(" ")
    ));
    builder.note(format!(
        "oracle per-status type ids: ok={} container-undecoded={} undecoded={} walk-fail={}",
        hex_ids(reply.get("decodable")),
        hex_ids(reply.get("containers")),
        hex_ids(reply.get("undecoded")),
        hex_ids(reply.get("walk_fail")),
    ));
    report_classification(
        &mut builder,
        &identity,
        &rust_decodable,
        &oracle_decodable,
        &reply,
    );

    Ok(builder.finish())
}

/// A list of type ids in hex, so a report never prints a decimal number where
/// every other mention of a type id in this repository is hex.
#[must_use]
fn hex_list(ids: &[u32]) -> String {
    if ids.is_empty() {
        return "(none)".to_owned();
    }
    ids.iter()
        .map(|id| format!("0x{id:08x}"))
        .collect::<Vec<_>>()
        .join(", ")
}

/// The same, for a value straight out of the oracle's reply.
fn hex_ids(value: Option<&Json>) -> String {
    let ids: Vec<u32> = value
        .and_then(Json::as_array)
        .map(|items| items.iter().filter_map(Json::as_u32).collect())
        .unwrap_or_default();
    hex_list(&ids)
}

/// The type ids the Rust side calls `Ok`, i.e. decodable.
fn decodable_types(rows: &[spore_assets::ManifestRow]) -> Vec<u32> {
    let mut types: Vec<u32> = rows
        .iter()
        .filter(|row| row.decode_status == spore_assets::DecodeStatus::Ok)
        .map(|row| row.key.type_id)
        .collect();
    types.sort_unstable();
    types.dedup();
    types
}

fn is_ascending(rows: &[spore_assets::ManifestRow]) -> bool {
    rows.windows(2).all(|pair| {
        let left = (
            pair[0].key.type_id,
            pair[0].key.group_id,
            pair[0].key.instance_id,
        );
        let right = (
            pair[1].key.type_id,
            pair[1].key.group_id,
            pair[1].key.instance_id,
        );
        left <= right
    })
}

/// The two classification sets, quoted in full on both sides.
fn report_classification(
    builder: &mut ReportBuilder,
    identity: &RecordIdentity,
    rust_decodable: &[u32],
    oracle_decodable: &[u32],
    reply: &Json,
) {
    if rust_decodable == oracle_decodable {
        builder.note(format!(
            "both sides call the same type ids decodable: {:?}",
            rust_decodable
        ));
        return;
    }
    let rust_only: Vec<u32> = rust_decodable
        .iter()
        .copied()
        .filter(|t| !oracle_decodable.contains(t))
        .collect();
    let oracle_only: Vec<u32> = oracle_decodable
        .iter()
        .copied()
        .filter(|t| !rust_decodable.contains(t))
        .collect();
    let shared: Vec<u32> = rust_decodable
        .iter()
        .copied()
        .filter(|t| oracle_decodable.contains(t))
        .collect();
    builder.note(format!(
        "shared decodable type ids: {}; rust-only: {}; oracle-only: {}",
        hex_list(&shared),
        hex_list(&rust_only),
        hex_list(&oracle_only)
    ));
    builder.note_divergence(
        Divergence::value(
            identity.clone(),
            "decodable type ids",
            format!(
                "oracle-only {} (shared {})",
                hex_list(&oracle_only),
                hex_list(&shared)
            ),
            format!(
                "rust-only {} (shared {})",
                hex_list(&rust_only),
                hex_list(&shared)
            ),
        )
        .with_class(DivergenceClass::Definitional)
        .with_note(format!(
            "the two sides answer different questions, so this is a definition and not a defect: \
             spore-assets means \"a per-record decoder exists in this workspace\" (gmdl, rw4, \
             raster only -- png/jpeg/gmsh/plt were removed deliberately), while manifest.py means \
             \"looks decodable\" (msize >= 16 for raster/jpeg/png/plt, plus a header probe for \
             gmdl/gmsh). The oracle's per-type ids are ok={} / container-undecoded={} / \
             undecoded={} / walk-fail={}.",
            hex_ids(reply.get("decodable")),
            hex_ids(reply.get("containers")),
            hex_ids(reply.get("undecoded")),
            hex_ids(reply.get("walk_fail")),
        )),
    );
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ordering_is_ascending_on_the_triple_and_nothing_else() {
        let rows = |triples: &[(u32, u32, u32)]| -> Vec<spore_assets::ManifestRow> {
            triples
                .iter()
                .map(
                    |(type_id, group_id, instance_id)| spore_assets::ManifestRow {
                        key: spore_core::ResourceKey::new(*type_id, *group_id, *instance_id),
                        type_name: None,
                        group_name: None,
                        size: 0,
                        decode_status: spore_assets::DecodeStatus::Undecoded,
                        semantic_owner: None,
                        type_name_evidence: spore_assets::ManifestEvidence::Unknown,
                        group_name_evidence: spore_assets::ManifestEvidence::Unknown,
                    },
                )
                .collect()
        };
        assert!(is_ascending(&rows(&[(1, 0, 0), (1, 0, 1), (2, 0, 0)])));
        assert!(is_ascending(&rows(&[(1, 0, 0), (1, 0, 0)])));
        assert!(!is_ascending(&rows(&[(2, 0, 0), (1, 0, 0)])));
        assert!(!is_ascending(&rows(&[(1, 1, 0), (1, 0, 9)])));
    }

    #[test]
    fn an_identical_classification_is_reported_as_a_note_not_a_divergence() {
        let mut builder = ReportBuilder::new(NAME, INVOCATION);
        let identity = RecordIdentity::loose("mini_package.package");
        report_classification(
            &mut builder,
            &identity,
            &[0x00E6_BCE5],
            &[0x00E6_BCE5],
            &crate::json::Json::Null,
        );
        let report = builder.finish();
        assert!(report.divergences.is_empty());
        assert!(report
            .notes
            .iter()
            .any(|note| note.contains("same type ids")));
    }

    #[test]
    fn a_differing_classification_is_a_definitional_divergence_with_both_lists() {
        let mut builder = ReportBuilder::new(NAME, INVOCATION);
        let identity = RecordIdentity::loose("Spore_Content.package");
        report_classification(
            &mut builder,
            &identity,
            &[0x00E6_BCE5, 0x2F4E_681B],
            &[0x00E6_BCE5, 0x2F7D_0004],
            &crate::json::Json::Null,
        );
        let report = builder.finish();
        assert_eq!(report.divergences.len(), 1);
        let divergence = &report.divergences[0];
        assert_eq!(divergence.class, DivergenceClass::Definitional);
        // Both sides are quoted verbatim in hex, and so is the shared set: a
        // reader must be able to reconstruct both full lists from the report.
        assert!(
            divergence.oracle.contains("oracle-only 0x2f7d0004"),
            "the oracle's list must be quotable: {divergence}"
        );
        assert!(
            divergence.oracle.contains("shared 0x00e6bce5"),
            "the shared set must be named: {divergence}"
        );
        assert!(
            divergence.rust.contains("rust-only 0x2f4e681b"),
            "the Rust list must be quotable: {divergence}"
        );
    }
}
