//! `manifest`: the canonical one-row-per-record report.
//!
//! A direct port of `tools/spore/manifest/manifest.py` (schema v1, CS-22), built
//! on [`spore_assets::ManifestBuilder`].
//!
//! # Determinism is the contract
//!
//! The reference tool's docstring states the reason it exists: it drops and
//! rebuilds its sidecar on every run, inserting rows in a stable
//! `(type, group, instance)` order, "so a double run is byte-identical (the
//! `sim_contract` discipline applied to data)". That property is what makes a
//! manifest reviewable — a report that reorders itself between runs cannot be
//! diffed, and a report that cannot be diffed cannot be used to check whether an
//! asset-pipeline change did what it meant to.
//!
//! Here it is structural rather than hopeful: rows live in a `BTreeMap` keyed by
//! [`spore_core::ResourceKey`], whose ordering is already strict lexicographic on
//! `(type, group, instance)`; JSON keys are an insertion-ordered `Vec`; and
//! nothing in the output depends on a hash map's iteration order, the clock, the
//! environment or the filesystem's readdir order. The test suite asserts
//! byte-identity of two runs directly.
//!
//! # Where the Rust port differs from the Python one, and why
//!
//! * **Sidecar format.** The Python writes a SQLite table; this writes JSON
//!   Lines, because the point of a manifest is to be diffed and reviewed in a
//!   patch, and a binary SQLite file is neither. The columns are the same set.
//! * **`decode_status` is a per-TYPE label, and this crate measures it per record.**
//!   `manifest.py` derives the status from the type *name* (`ok` for
//!   `raster`/`jpeg`/`png`/`plt` whenever `msize >= 16` — a statement about the
//!   index, not about the payload) and then probes `gmdl`. `spore-assets` keeps a
//!   pure type-level classification and this tool prints it verbatim, labelled as
//!   such, because "this build has a decoder family for this type" and "this
//!   record decoded" are different claims.
//!
//!   Measured on `Spore_Content.package` (17 119 records), the gap is large and is
//!   worth stating rather than leaving implied:
//!
//!   | type | manifest `--stats` | `verify`, per record |
//!   |---|---|---|
//!   | gmdl | 4 209 `ok` | 3 472 decoded, 737 failed |
//!   | raster | 2 954 `ok` | 1 374 decoded, 1 580 failed |
//!   | png | 1 642 `ok` | 1 642 `no decoder` |
//!   | rw4 | 1 131 `undecoded` (!) | 1 131 decoded |
//!   | **total** | **8 805 `ok`**, 1 131 wrongly `undecoded` | **5 977 decoded, 2 317 failed** |
//!
//!   Two things follow, and both are why `verify` exists next to this command:
//!
//!   * a manifest that reports 8 805 decodable records overstates by 2 317, every
//!     one of them a record a decoder exists for and refused;
//!   * the same manifest calls all 1 131 **RW4** records `undecoded`, although
//!     `spore-rw4` decodes every one of them. `ManifestBuilder`'s `DECODABLE` list
//!     omits `0x2F4E681B`, and `manifest.py` omits it too, so both inherited the
//!     gap from the same C++-era list.
//!
//!   Neither is a bug in *this* command, which reports what the type table says
//!   and labels it; that is why `--stats` prints the qualifier under every status
//!   count and why the errors are only ever a claim about a record.
//!
//!   Two failure families dominate the 2 317, and both are refusals by name rather
//!   than crashes: 1 207 raster records carry fourcc `0x15xx` (the luminance
//!   family, a *different* format that `spore-texture` refuses rather than
//!   misdecoding), and 619 gmdl records name shader-data id `0x218`, which
//!   `spore-gmdl` refuses because the id is undocumented.
//! * **`format_class`.** The reference derives it from the *type name* through a
//!   24-entry lookup, so an unnamed type falls back to its own name lowercased
//!   and `png`/`jpeg` map onto `raster` — a claim about a name, not about the
//!   bytes. `ManifestRow` does not carry it, so this tool does not print it.

use std::io::Write;

use spore_assets::{ManifestBuilder, ManifestRow};

use crate::json::{hex_id, Json};
use crate::ManifestRequest;

/// How many rows `--stats` shows per type name.
pub const STATS_TOP_N: usize = 20;

/// `manifest`: build, then optionally emit JSON Lines, a JSON array, and stats.
///
/// The "wrote &lt;file&gt;" confirmation goes to **stderr**, so stdout carries nothing
/// but the requested document and `manifest ... --json > out.json` is a valid
/// pipeline whether or not `--out` was also given.
pub fn run(
    request: &ManifestRequest,
    out: &mut dyn Write,
    err: &mut dyn Write,
) -> Result<(), crate::ToolError> {
    let store = super::open_store(&request.packages)?;
    let builder = ManifestBuilder::from_store(&store);

    if let Some(path) = &request.out_file {
        let rendered = render_json_lines(&builder);
        std::fs::write(path, &rendered)
            .map_err(|source| crate::ToolError::Io(format!("{}: {source}", path.display())))?;
        writeln!(
            err,
            "osptool: wrote {} ({} rows, {} bytes)",
            path.display(),
            builder.len(),
            rendered.len()
        )?;
    }

    if request.json {
        let array = Json::Arr(builder.rows().map(row_json).collect());
        writeln!(out, "{array}")?;
    }

    if request.stats {
        writeln!(out, "{}", stats_text(&builder))?;
    }

    if request.out_file.is_none() && !request.json && !request.stats {
        // A manifest with no destination is a user mistake, not a silent
        // 100 000-row dump: this is the one command whose output is normally
        // meant to go somewhere durable.
        writeln!(out, "{}", render_json_lines(&builder).trim_end())?;
    }
    Ok(())
}

/// The whole manifest as JSON Lines: one object per line, fixed key order.
pub fn render_json_lines(builder: &ManifestBuilder) -> String {
    let mut out = String::new();
    for row in builder.rows() {
        out.push_str(&row_json(row).to_line());
    }
    out
}

/// One row as a JSON object, keys in the documented order.
///
/// Every id is a hex string, so a value copied out of a manifest is a usable
/// `osptool describe` argument. `type_name`/`group_name`/`semantic_owner` are
/// `null` rather than `"UNKNOWN"` when there is no name — a missing value and
/// the string "UNKNOWN" are different facts, and the reference tool conflates
/// them (its `semantic_owner` is hard-coded `"UNKNOWN"`).
pub fn row_json(row: &ManifestRow) -> Json {
    Json::obj()
        .push("type_id", hex_id(row.key.type_id))
        .push("group_id", hex_id(row.key.group_id))
        .push("instance_id", hex_id(row.key.instance_id))
        .push("type_name", Json::from(row.type_name))
        .push("group_name", Json::from(row.group_name))
        .push("size", Json::from(row.size))
        .push("decode_status", Json::from(row.decode_status.as_str()))
        .push("semantic_owner", Json::from(row.semantic_owner.as_deref()))
        .push(
            "type_name_evidence",
            Json::from(row.type_name_evidence.as_str()),
        )
        .push(
            "group_name_evidence",
            Json::from(row.group_name_evidence.as_str()),
        )
}

/// The `--stats` summary.
pub fn stats_text(builder: &ManifestBuilder) -> String {
    let mut out = String::new();
    out.push_str(&format!("rows              {}\n", builder.len()));
    out.push_str("by decode status  (type-level classification, not a per-record decode)\n");
    let status_counts = builder.decode_status_counts();
    let widest = status_counts.keys().map(|k| k.len()).max().unwrap_or(0);
    for (status, count) in &status_counts {
        out.push_str(&format!("  {status:<widest$}  {count}\n"));
    }

    out.push_str(&format!("top {STATS_TOP_N} type names\n"));
    // Tie-break is by name ascending, so the summary is itself byte-stable.
    // Without it the order of two equal counts would depend on the BTreeMap's
    // key iteration, which is stable but reads as arbitrary in a report.
    let mut ranked: Vec<(String, usize)> = builder.type_counts().into_iter().collect();
    ranked.sort_by(|left, right| right.1.cmp(&left.1).then_with(|| left.0.cmp(&right.0)));
    let label_width = ranked
        .iter()
        .take(STATS_TOP_N)
        .map(|(name, _)| name.len())
        .max()
        .unwrap_or(0);
    for (name, count) in ranked.iter().take(STATS_TOP_N) {
        out.push_str(&format!("  {count:>9}  {name:<label_width$}\n"));
    }
    if ranked.len() > STATS_TOP_N {
        out.push_str(&format!(
            "  ({} further type name(s) not shown)\n",
            ranked.len() - STATS_TOP_N
        ));
    }
    out
}

/// The type-name counts as a sorted table, for callers that want the data
/// rather than the rendering.
pub fn ranked_type_counts(builder: &ManifestBuilder) -> Vec<(String, usize)> {
    let mut ranked: Vec<(String, usize)> = builder.type_counts().into_iter().collect();
    ranked.sort_by(|left, right| right.1.cmp(&left.1).then_with(|| left.0.cmp(&right.0)));
    ranked
}

#[cfg(test)]
mod tests {
    use super::*;
    use spore_assets::{DecodeStatus, ManifestEvidence};
    use spore_core::ResourceKey;

    /// A builder holding one row per `(instance, type name)`.
    ///
    /// Built through the public `ManifestBuilder::insert` rather than through a
    /// package, because these tests are about the ordering and truncation rules
    /// and not about reading a container. Insertion order is the reverse of the
    /// key order on purpose: if any of it leaked into the output, these tests
    /// would see it.
    fn builder_of(entries: &[(u32, &'static str)]) -> ManifestBuilder {
        let mut builder = ManifestBuilder::new();
        for (instance, name) in entries {
            let key = ResourceKey::new(0x00e6_bce5, 0x4061_6201, *instance);
            builder.insert(ManifestRow {
                key,
                type_name: Some(name),
                group_name: Some("CellImages"),
                size: 16,
                decode_status: DecodeStatus::Ok,
                semantic_owner: None,
                type_name_evidence: ManifestEvidence::Verified,
                group_name_evidence: ManifestEvidence::Unknown,
            });
        }
        builder
    }

    #[test]
    fn the_stats_tie_break_is_by_name_so_the_summary_is_stable() {
        let first = ranked_type_counts(&builder_of(&[(1, "aaa"), (2, "bbb"), (3, "aaa")]));
        let second = ranked_type_counts(&builder_of(&[(1, "bbb"), (2, "aaa"), (3, "aaa")]));
        assert_eq!(first, second, "insertion order must not reach the output");
        assert_eq!(
            first,
            vec![("aaa".to_owned(), 2), ("bbb".to_owned(), 1)],
            "the higher count leads; equal counts sort by name ascending"
        );
    }

    #[test]
    fn the_summary_caps_at_the_documented_row_count_and_says_so() {
        // Thirty distinct static names, so the summary's truncation is the only
        // thing under test.
        static NAMES: [&str; 30] = [
            "type00", "type01", "type02", "type03", "type04", "type05", "type06", "type07",
            "type08", "type09", "type10", "type11", "type12", "type13", "type14", "type15",
            "type16", "type17", "type18", "type19", "type20", "type21", "type22", "type23",
            "type24", "type25", "type26", "type27", "type28", "type29",
        ];
        let entries: Vec<(u32, &'static str)> = NAMES
            .iter()
            .enumerate()
            .map(|(index, name)| (index as u32, *name))
            .collect();
        let builder = builder_of(&entries);
        let text = stats_text(&builder);
        let shown = text
            .lines()
            .filter(|line| line.contains("  type") && !line.contains("type name"))
            .count();
        assert_eq!(shown, STATS_TOP_N);
        assert!(text.contains("10 further type name(s) not shown"));
        // Highest count first: every row has count 1 here, so this checks the
        // alphabetical arm of the tie-break instead.
        assert!(text.contains("type00"));
        assert!(!text.contains("type29 "));
    }

    #[test]
    fn the_summary_labels_its_status_counts_as_type_level() {
        let text = stats_text(&builder_of(&[(1, "gmdl")]));
        assert!(text.contains("rows              1"));
        assert!(
            text.contains("type-level classification, not a per-record decode"),
            "a status count is a claim about the type table: {text}"
        );
    }

    #[test]
    fn two_renders_of_one_builder_are_byte_identical() {
        let builder = builder_of(&[(3, "raster"), (1, "gmdl"), (2, "rw4")]);
        assert_eq!(render_json_lines(&builder), render_json_lines(&builder));
        assert_eq!(stats_text(&builder), stats_text(&builder));
    }

    #[test]
    fn a_row_is_json_with_ids_as_hex_strings_and_names_as_null() {
        let mut builder = ManifestBuilder::new();
        builder.insert(ManifestRow {
            key: ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801),
            type_name: Some("gmdl"),
            group_name: None,
            size: 1266,
            decode_status: DecodeStatus::Ok,
            semantic_owner: None,
            type_name_evidence: ManifestEvidence::Verified,
            group_name_evidence: ManifestEvidence::Unknown,
        });
        assert_eq!(
            render_json_lines(&builder),
            "{\"type_id\":\"0x00e6bce5\",\"group_id\":\"0x40616201\",\"instance_id\":\"0x067a0801\",\
             \"type_name\":\"gmdl\",\"group_name\":null,\"size\":1266,\"decode_status\":\"ok\",\
             \"semantic_owner\":null,\"type_name_evidence\":\"VERIFIED\",\
             \"group_name_evidence\":\"UNKNOWN\"}\n"
        );
    }
}
