//! Comparison 3: the canonical RW4 section-walk line.
//!
//! Rust `spore_rw4::Rw4::describe()` against `tools/spore/rw4/rw4.py::describe`,
//! **as exact strings**. This is the comparison `tests/test_rw4.py` already runs
//! against the C++ walker; this one runs it against the Rust port, over the same
//! real corpus.
//!
//! Nothing here normalises, trims or compares case-insensitively. The whole
//! value of the exercise is that a one-character difference -- a missing `0x`
//! prefix, an unpadded hex digit, a signed size printed as unsigned -- is
//! visible, so anything that would hide one is a defect in this module.

use spore_assets::Package;
use spore_core::record::type_id;

use crate::corpus::{Corpus, LocatedPackage, LocatedRecord, RecordKind};
use crate::floats::ReportBuilder;
use crate::oracle::{classify_refusal, OracleConfig, OracleError, OracleSession};
use crate::report::{DifferentialReport, Divergence, RecordIdentity};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "rw4-describe";

/// How the oracle is invoked for the package-level comparison.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one \
                              NDJSON {cmd:\"rw4\", i:N} request per rw4 record, answered from \
                              rw4.py::describe";

/// How the oracle is invoked for the loose-fixture comparison.
pub const FILE_INVOCATION: &str =
    "`python3 -c` driver, one NDJSON {cmd:\"rw4_file\", path:...} request per file, answered \
     from rw4.py::describe";

/// Runs the RW4 comparison over **every** rw4 record in the primary package.
///
/// Exhaustive by design: `describe` is cheap, the record count is ~1131, and
/// "all of them" is the claim the repository already makes about C++.
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

/// Runs the RW4 comparison over every rw4 record in one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {}; Rust side: spore_rw4::parse(..).describe(); oracle: rw4.py::describe; \
         compared as exact strings with no normalisation",
        package.name
    ));

    let opened = Package::open(package.name.clone(), &package.path).map_err(|error| {
        OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
    })?;
    let image = opened.bytes();
    let targets: Vec<(usize, spore_dbpf::DbpfEntry)> = opened
        .index()
        .entries()
        .iter()
        .enumerate()
        .filter(|(_, entry)| entry.type_id == type_id::RW4)
        .map(|(index, entry)| (index, *entry))
        .collect();

    if targets.is_empty() {
        builder.skip(format!(
            "{} holds no 0x{:08x} (rw4) records, so there is nothing to describe",
            package.name,
            type_id::RW4
        ));
        return Ok(builder.finish());
    }
    builder.note(format!(
        "{} record(s) of type 0x{:08x} (rw4) in {}",
        targets.len(),
        type_id::RW4,
        package.name
    ));

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;

    for (index, entry) in &targets {
        let identity = info.identity(*index, entry.type_id, entry.group_id, entry.instance_id);
        let bytes = match spore_dbpf::extract_record(image, entry) {
            Ok(bytes) => bytes,
            Err(error) => {
                builder.record(crate::report::Agreement::RustOnly(format!(
                    "spore_dbpf::extract_record refused the record before the walker ran: {error}"
                )));
                continue;
            }
        };
        let rust = spore_rw4::parse(&bytes);
        let oracle = session.request_record("rw4", *index);
        record(
            &mut builder,
            identity,
            describe_or_error_result(rust),
            oracle,
        );
    }
    Ok(builder.finish())
}

/// Runs the RW4 comparison over a standalone rw4 record file.
///
/// This is the hermetic path: the committed `mini_rw4.rw4` is an RW4 container
/// that is not inside any package, so the package-level comparison cannot reach
/// it. Running the same two walkers over the same bytes is the same comparison.
pub fn compare_record_file(located: &LocatedRecord, config: &OracleConfig) -> DifferentialReport {
    super::run(NAME, || {
        let mut builder = ReportBuilder::new(NAME, FILE_INVOCATION);
        let identity = RecordIdentity::loose(located.name.clone());
        let bytes = std::fs::read(&located.path).map_err(|error| {
            OracleError::Protocol(format!(
                "could not read {}: {error}",
                located.path.display()
            ))
        })?;
        builder.note(format!(
            "{} ({} bytes), a standalone record; Rust side: spore_rw4::parse(..).describe(); \
             oracle: rw4.py::describe; compared as exact strings",
            located.name, located.size_bytes
        ));
        let mut session = OracleSession::spawn(config)?;
        let rust = describe_or_error(&bytes);
        let oracle = session.request_file("rw4_file", &located.path);
        record(&mut builder, identity, rust, oracle);
        Ok(builder.finish())
    })
}

/// `spore_rw4::parse(..).describe()`, or the parser's own message.
fn describe_or_error(bytes: &[u8]) -> Result<String, String> {
    describe_or_error_result(spore_rw4::parse(bytes))
}

/// The same, from an already-obtained parse result.
fn describe_or_error_result(
    parsed: Result<spore_rw4::Rw4, spore_rw4::Rw4Error>,
) -> Result<String, String> {
    parsed
        .map(|container| container.describe())
        .map_err(|error| error.to_string())
}

/// The body both entry points share: classify one record's two answers.
fn record(
    builder: &mut ReportBuilder,
    identity: RecordIdentity,
    rust: Result<String, String>,
    oracle: Result<crate::json::Json, OracleError>,
) {
    // The oracle's answer, reduced to the one string this comparison is about,
    // with the driver's refusal message kept verbatim.
    let oracle_line: Result<String, String> = match oracle {
        Ok(value) => value
            .get("describe")
            .and_then(crate::json::Json::as_str)
            .map_or_else(
                || Err("the rw4 response carried no describe field".to_owned()),
                |line| Ok(line.to_owned()),
            ),
        Err(error) => Err(error.message()),
    };

    match (&rust, &oracle_line) {
        (Ok(left), Ok(right)) => {
            if left == right {
                builder.record(crate::report::Agreement::Equal);
            } else {
                builder.divergence(
                    Divergence::value(identity, "describe", right.clone(), left.clone()).with_note(
                        format!(
                            "exact-string comparison; oracle string is {} bytes, rust string is \
                             {} bytes; first differing character index = {}",
                            right.len(),
                            left.len(),
                            first_character_difference(left, right)
                        ),
                    ),
                );
            }
        }
        _ => {
            let agreement = classify_refusal(
                oracle_line.as_ref().map(|_| ()).map_err(Clone::clone),
                rust.as_ref().map(|_| ()).map_err(Clone::clone),
            );
            if let crate::report::Agreement::BothFailed { oracle, rust } = &agreement {
                builder.record(agreement.clone());
                builder.note(format!(
                    "{identity}: both walkers refused this record; oracle={oracle:?} rust={rust:?}. \
                     spore-rw4 validates the magic, the arena bounds and the file type, and \
                     rw4.py::describe checks none of them, so a refusal here means the record is \
                     not an RW4 container at all rather than that the walks disagree."
                ));
            }
        }
    }
}

/// The character index at which two strings first differ, or the length of the
/// shorter one when one is a prefix of the other.
#[must_use]
pub fn first_character_difference(left: &str, right: &str) -> usize {
    left.char_indices()
        .zip(right.chars())
        .find(|((_, left_char), right_char)| left_char != right_char)
        .map_or_else(|| left.len().min(right.len()), |((offset, _), _)| offset)
}

/// The RW4 record type's own id, for a report that wants to name it.
pub const RW4_TYPE: u32 = type_id::RW4;

/// True when `record` is an rw4 standalone record.
#[must_use]
pub fn is_rw4_record(located: &LocatedRecord) -> bool {
    located.kind == RecordKind::Rw4
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_first_character_difference_is_found_in_bytes_and_falls_back_to_the_shorter_length() {
        assert_eq!(first_character_difference("abc", "abc"), 3);
        assert_eq!(first_character_difference("abc", "abd"), 2);
        assert_eq!(first_character_difference("abc", "ab"), 2);
        assert_eq!(first_character_difference("0x1 obj=1", "0x1 obj=2"), 8);
    }

    #[test]
    fn a_one_character_difference_would_be_reported_not_absorbed() {
        // The whole reason this module compares exact strings.
        let oracle = "0x1 obj=1 sec=3 buf=80 | 10030 d=0x138 s=12";
        let rust = "0x01 obj=1 sec=3 buf=80 | 10030 d=0x138 s=12";
        assert_ne!(oracle, rust);
        assert_eq!(first_character_difference(rust, oracle), 2);
    }
}
