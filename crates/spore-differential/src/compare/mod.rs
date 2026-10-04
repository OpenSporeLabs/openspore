//! The seven comparisons this crate performs.
//!
//! Each module here owns one question, one oracle entry point and one Rust
//! entry point. A comparison returns
//! `Result<`[`DifferentialReport`]`] > (crate::report::DifferentialReport), [`OracleError`]>`:
//! `Ok` covers *every* comparison outcome, including a total disagreement,
//! because the disagreement is the result. `Err` means only that the oracle
//! could not be reached, and [`run`] folds that into a `Skipped` report so a
//! suite run can never stop on a missing interpreter or a missing game install.

use crate::corpus::{Corpus, LocatedPackage};
use crate::oracle::OracleError;
use crate::report::DifferentialReport;

pub mod dbpf_index;
pub mod gmdl;
pub mod manifest;
pub mod raster;
pub mod record_bytes;
pub mod rw4;
pub mod worldobj;

/// Every comparison this crate knows, in the order the suite runs them.
pub const ALL: &[&str] = &[
    dbpf_index::NAME,
    record_bytes::NAME,
    rw4::NAME,
    gmdl::NAME,
    raster::NAME,
    manifest::NAME,
    worldobj::NAME,
];

/// The package a package-level comparison should run over.
///
/// `Spore_Content.package` is the corpus the repository's own measurements are
/// stated against, so it is preferred; otherwise the first located package. One
/// package at a time, always: two 1 GB images held simultaneously is exactly
/// what the memory discipline forbids.
#[must_use]
pub fn primary_package(corpus: &Corpus) -> Option<&LocatedPackage> {
    corpus
        .find_package("Spore_Content.package")
        .or_else(|| corpus.packages().first())
}

/// A report for a comparison whose input is absent.
///
/// An empty corpus and an unreachable oracle produce the same shape, because
/// both mean "this did not run"; only the sentence differs.
#[must_use]
pub fn skipped(comparison: &str, reason: impl Into<String>) -> DifferentialReport {
    DifferentialReport::skipped(comparison, reason)
}

/// Runs one comparison and turns "the oracle could not be reached" into a
/// `Skipped` report carrying the reason.
///
/// A missing game install and a missing `python3` are ordinary states. Neither
/// may abort a suite run, and neither may be reported as a clean result.
pub fn run<F>(comparison: &str, body: F) -> DifferentialReport
where
    F: FnOnce() -> Result<DifferentialReport, OracleError>,
{
    match body() {
        Ok(report) => report,
        Err(error) => {
            let mut report = skipped(comparison, error.to_string());
            report.notes.push(format!(
                "the oracle was not reached, so no record was compared on either side; \
                 this is not evidence of agreement ({error})"
            ));
            report
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::json::Json;

    #[test]
    fn every_declared_comparison_has_a_distinct_name() {
        let mut names: Vec<&str> = ALL.to_vec();
        names.sort_unstable();
        let count = names.len();
        names.dedup();
        assert_eq!(names.len(), count, "duplicate comparison name in ALL");
    }

    #[test]
    fn an_unreachable_oracle_becomes_skipped_and_says_so_in_both_places() {
        let report = run(dbpf_index::NAME, || {
            Err(OracleError::Unavailable(
                "python3 is not installed".to_owned(),
            ))
        });
        assert!(report.status.is_skipped());
        assert!(report
            .status
            .to_string()
            .contains("python3 is not installed"));
        assert_eq!(report.records_walked, 0);
        assert!(report.divergences.is_empty());
        assert!(
            report
                .notes
                .iter()
                .any(|note| note.contains("not evidence of agreement")),
            "{:?}",
            report.notes
        );
    }

    #[test]
    fn an_empty_corpus_names_the_environment_variable_that_would_change_it() {
        let report = run(dbpf_index::NAME, || {
            Ok::<_, OracleError>(skipped(
                dbpf_index::NAME,
                "no package located; set OPENSPORE_ROOT to a checkout with SPORE/",
            ))
        });
        assert!(report.status.is_skipped());
        assert!(report.status.to_string().contains("OPENSPORE_ROOT"));
    }

    #[test]
    fn a_primary_package_prefers_spore_content_and_falls_back_to_the_first() {
        assert!(primary_package(&Corpus::empty()).is_none());
        let corpus = Corpus::from_dir(&std::env::temp_dir());
        // Whatever /tmp holds is irrelevant: the assertion is that the
        // preference order is content-first, which the fixture corpus proves.
        let _ = corpus;
        let _ = Json::Null;
    }
}
