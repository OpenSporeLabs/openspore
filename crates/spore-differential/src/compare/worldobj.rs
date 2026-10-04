//! Comparison 7: the `0x0F43029A` world-object records -- report only.
//!
//! `tools/spore/worldobj/worldobj.py` is an oracle with **no Rust counterpart**:
//! nothing in this workspace decodes a world-object record. There is therefore
//! nothing to diff, and pretending otherwise would be the most misleading thing
//! this crate could do.
//!
//! So this module measures the oracle's side of the record set and states the
//! gap explicitly: how many records exist, what the oracle says their headers
//! hold, and that the Rust side has no implementation to compare them against.
//! When one lands, the place to add the comparison is here.

use spore_assets::Package;
use spore_core::record::type_id;

use crate::corpus::{Corpus, LocatedPackage};
use crate::floats::ReportBuilder;
use crate::oracle::{OracleConfig, OracleError, OracleSession};
use crate::report::{Agreement, DifferentialReport, Divergence, DivergenceClass, RecordIdentity};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "worldobj-oracle-only";

/// How the oracle is invoked.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one NDJSON \
                              {cmd:\"worldobj\", i:N} request per record, answered from \
                              worldobj.py::parse_header";

/// The world-object type id.
pub const WORLDOBJ_TYPE: u32 = 0x0F43_029A;

/// Runs the report-only world-object probe over the corpus's primary package.
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

/// Reports the oracle's world-object record set over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {}; REPORT ONLY -- no Rust decoder exists for 0x{WORLDOBJ_TYPE:08x}, so there \
         is nothing to diff",
        package.name
    ));

    let opened = Package::open(package.name.clone(), &package.path).map_err(|error| {
        OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
    })?;
    let targets: Vec<(usize, spore_dbpf::DbpfEntry)> = opened
        .index()
        .entries()
        .iter()
        .enumerate()
        .filter(|(_, entry)| entry.type_id == WORLDOBJ_TYPE)
        .map(|(index, entry)| (index, *entry))
        .collect();

    if targets.is_empty() {
        builder.skip(format!(
            "{} holds no 0x{WORLDOBJ_TYPE:08x} records",
            package.name
        ));
        return Ok(builder.finish());
    }

    // The oracle's own record set is reported; the missing half is recorded as a
    // definitional gap so a reader cannot mistake "one side had nothing to say"
    // for "both sides agreed".
    let first = targets.first().expect("checked non-empty");
    let identity = RecordIdentity::new(
        package.name.clone(),
        first.0,
        first.1.type_id,
        first.1.group_id,
        first.1.instance_id,
    );
    builder.note_divergence(
        Divergence::value(
            identity,
            "worldobj 0x0f43029a",
            format!(
                "{} record(s) of type 0x{WORLDOBJ_TYPE:08x} in {}",
                targets.len(),
                package.name
            ),
            "no decoder: this type id is not implemented in any crate in this workspace",
        )
        .with_class(DivergenceClass::Definitional)
        .with_note(
            "worldobj.py documents these records as GUIDs + vector3s + 0x1234 markers with a \
             20-byte header, and reports that its byte accounting closes over all of them. That is \
             a claim about the oracle only. Until a Rust decoder exists this crate can neither \
             confirm nor contradict any of it.",
        ),
    );

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;
    let mut magic_ok = 0usize;
    let mut versions: std::collections::BTreeMap<String, usize> = std::collections::BTreeMap::new();

    for (index, entry) in &targets {
        let record_identity =
            info.identity(*index, entry.type_id, entry.group_id, entry.instance_id);
        match session.request_record("worldobj", *index) {
            Ok(reply) => {
                let magic = reply
                    .get("header")
                    .and_then(|header| header.get("magic"))
                    .and_then(crate::json::Json::as_u32);
                let version = reply
                    .get("header")
                    .and_then(|header| header.get("version"))
                    .and_then(crate::json::Json::as_u32);
                if magic == Some(0xABB4_55B7) {
                    magic_ok += 1;
                }
                *versions
                    .entry(version.map_or_else(|| "absent".to_owned(), |value| value.to_string()))
                    .or_insert(0) += 1;
                builder.record(Agreement::OracleOnly(format!(
                    "oracle decoded the header; the Rust side has no decoder for \
                     0x{WORLDOBJ_TYPE:08x}"
                )));
                let _ = record_identity;
            }
            Err(error) => {
                builder.record(Agreement::BothFailed {
                    oracle: error.message(),
                    rust: "no decoder exists, so nothing could be attempted".to_owned(),
                });
            }
        }
    }

    builder.note(format!(
        "oracle header survey over {} record(s): magic 0xabb455b7 in {magic_ok}, version histogram \
         {versions:?}. Compare spore-assets' own type name for this id, if it has one, before \
         assuming the oracle is describing the same records: this crate uses the constant 0x{WORLDOBJ_TYPE:08x} \
         and does not consult a name table.",
        targets.len()
    ));
    let named = spore_core::record::RecordType::new(type_id::GMDL).name();
    let _ = named;
    Ok(builder.finish())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_type_id_matches_the_one_the_oracle_documents() {
        // worldobj.py's module constant. If this ever drifts the comparison would
        // silently walk nothing.
        assert_eq!(WORLDOBJ_TYPE, 0x0F43_029A);
    }

    #[test]
    fn an_empty_corpus_skips_rather_than_reports_a_clean_run() {
        let report = compare(&Corpus::empty(), &OracleConfig::detect());
        assert!(report.status.is_skipped());
        assert!(!report.is_clean());
    }
}
