//! Float comparison with a tolerance that is stated, not implied.
//!
//! Both sides lift `f32` record fields to `f64` (Python has no `f32`), so an
//! exact `==` would be a claim about bit patterns rather than about the
//! record. A tolerance is therefore necessary -- and a tolerance applied
//! silently is how a harness reports "no difference" for a difference it chose
//! not to look at.
//!
//! So [`ReportBuilder::float_field`] is the only way a float reaches a
//! comparison's verdict: it applies [`FLOAT_TOLERANCE`], records the tolerance
//! on the report, and quotes both values *in full precision* when they fall
//! outside it. A reader can therefore always recompute the decision.

use crate::report::{DifferentialReport, Divergence, DivergenceClass, RecordIdentity};

/// The relative-or-absolute tolerance used for every float field.
///
/// `1e-4` is the tolerance the repository's other differential tests use, and it
/// is roughly the precision `f32` carries at the magnitudes a bounding box or a
/// bounding radius actually holds: `f32` has ~7 significant decimal digits, so a
/// `1e-4` relative window is comfortably above the representation error and far
/// below any disagreement about a value.
pub const FLOAT_TOLERANCE: f64 = 1e-4;

/// The tolerance, in the words a report prints.
#[must_use]
pub fn describe_tolerance(tolerance: f64) -> String {
    format!("{tolerance:e} (relative or absolute: |a-b| <= tol, or |a-b| <= tol*max(|a|,|b|))")
}

/// The absolute difference, with the non-finite cases spelled out.
///
/// Two NaNs have an undefined difference; reporting `0` for them would be a
/// lie that turns "both read garbage" into "they agree".
#[must_use]
pub fn delta(a: f64, b: f64) -> f64 {
    if a.is_nan() || b.is_nan() {
        f64::NAN
    } else if a.is_infinite() || b.is_infinite() {
        // Both infinite with the same sign is the only finite answer; the
        // caller sees `inf` and treats anything else as a disagreement.
        if a == b {
            0.0
        } else {
            f64::INFINITY
        }
    } else {
        (a - b).abs()
    }
}

/// Whether two floats agree within `tolerance`.
///
/// Both NaN agree (both sides read the same non-value); one NaN does not.
/// Two infinities of the same sign agree; opposite signs do not.
#[must_use]
pub fn agree(a: f64, b: f64, tolerance: f64) -> bool {
    if a.is_nan() || b.is_nan() {
        return a.is_nan() && b.is_nan();
    }
    if a == b {
        return true;
    }
    if a.is_infinite() || b.is_infinite() {
        return false;
    }
    let difference = (a - b).abs();
    if difference <= tolerance {
        return true;
    }
    let scale = a.abs().max(b.abs());
    difference <= tolerance * scale
}

/// Accumulates one comparison's findings.
///
/// The builder owns the bookkeeping so that no comparison can quietly forget to
/// count a record, forget to record the tolerance it used, or emit a divergence
/// without both values.
#[derive(Debug)]
pub struct ReportBuilder {
    comparison: String,
    status: crate::report::Status,
    records_walked: usize,
    agreements: usize,
    outcomes: std::collections::BTreeMap<&'static str, usize>,
    divergences: Vec<Divergence>,
    notes: Vec<String>,
    tolerance: Option<String>,
    max_divergences: usize,
    truncation_noted: bool,
    /// When set, field comparisons do not advance the record counters; the
    /// comparison calls [`ReportBuilder::record`] once per record itself.
    ///
    /// `records_walked` means "records looked at", and a gmdl comparison that
    /// checks twenty fields per record must not report twenty records. Without
    /// this a per-field comparison inflates the record count by an order of
    /// magnitude and every coverage claim built on it becomes false.
    field_mode: bool,
    /// Bounded, de-duplicated samples of non-clean verdict messages per label,
    /// flushed into `notes` by [`ReportBuilder::finish`].
    verdict_samples: std::collections::BTreeMap<&'static str, Vec<String>>,
}

impl ReportBuilder {
    /// A builder for a comparison that will run, invoked as `oracle_invocation`.
    pub fn new(comparison: &str, oracle_invocation: &str) -> Self {
        Self {
            comparison: comparison.to_owned(),
            status: crate::report::Status::Complete,
            records_walked: 0,
            agreements: 0,
            outcomes: std::collections::BTreeMap::new(),
            divergences: Vec::new(),
            notes: vec![format!("oracle invoked as: {oracle_invocation}")],
            tolerance: None,
            max_divergences: 4096,
            truncation_noted: false,
            field_mode: false,
            verdict_samples: std::collections::BTreeMap::new(),
        }
    }

    /// Caps how many divergences are retained.
    ///
    /// The real corpus can produce one per field per record; a report that holds
    /// a million of them is a report nobody reads. The *count* is always exact
    /// and a note records how many were dropped, so a truncated list is never
    /// mistaken for a complete one.
    #[must_use]
    pub fn with_max_divergences(mut self, max: usize) -> Self {
        self.max_divergences = max;
        self
    }

    /// Records the tolerance this comparison applies.
    pub fn set_tolerance(&mut self, tolerance: f64) {
        self.tolerance = Some(describe_tolerance(tolerance));
    }

    /// Appends a note.
    pub fn note(&mut self, note: impl Into<String>) {
        self.notes.push(note.into());
    }

    /// Marks the comparison as not having run.
    pub fn skip(&mut self, reason: impl Into<String>) {
        self.status = crate::report::Status::Skipped(reason.into());
    }

    /// Declares that the comparisons that follow check **fields** of one record,
    /// and that this builder will be told the record's single verdict through
    /// [`ReportBuilder::record`].
    ///
    /// Without this, a field comparison counts as a record of its own.
    pub fn field_mode(&mut self) {
        self.field_mode = true;
    }

    /// Records one record's verdict.
    pub fn record(&mut self, verdict: crate::report::Agreement) {
        self.records_walked += 1;
        *self.outcomes.entry(verdict.label()).or_insert(0) += 1;
        if verdict.is_clean() {
            self.agreements += 1;
        }
        // Sampled whether or not the verdict is clean: `BothFailed` is clean
        // but its two messages are the only thing that says *why* both sides
        // refused, and a histogram of "36" without them is unreadable.
        if let Some(message) = verdict.message() {
            self.sample_verdict(verdict.label(), &message);
        }
    }

    /// How many distinct verdict messages to keep per label.
    const VERDICT_SAMPLES: usize = 6;

    fn sample_verdict(&mut self, label: &'static str, message: &str) {
        let samples = self.verdict_samples.entry(label).or_default();
        if samples.len() < Self::VERDICT_SAMPLES && !samples.iter().any(|s| s == message) {
            samples.push(message.to_owned());
        }
    }

    /// The sampled verdict messages, flushed into the notes at the end of a run.
    fn flush_verdict_samples(&mut self) {
        let samples = std::mem::take(&mut self.verdict_samples);
        for (label, messages) in samples {
            for message in messages {
                self.notes.push(format!("{label}: {message}"));
            }
        }
    }

    /// Records a value equality: both sides produced `value`.
    pub fn equal(&mut self, record: RecordIdentity, field: &str, value: impl Into<String>) {
        if !self.field_mode {
            self.records_walked += 1;
            *self.outcomes.entry("equal").or_insert(0) += 1;
            self.agreements += 1;
        }
        let value = value.into();
        self.note(format!("{record}: {field} = {value} on both sides"));
    }

    /// Compares one float field at [`FLOAT_TOLERANCE`].
    ///
    /// Returns `true` when the two agree. On disagreement the divergence quotes
    /// both values with `{:?}` -- full round-trip precision -- and names the
    /// tolerance and the measured difference, so the decision can be rechecked
    /// from the report alone.
    pub fn float_field(
        &mut self,
        record: RecordIdentity,
        field: &str,
        oracle: f64,
        rust: f64,
        tolerance: f64,
    ) -> bool {
        if agree(oracle, rust, tolerance) {
            if !self.field_mode {
                self.records_walked += 1;
                *self.outcomes.entry("equal").or_insert(0) += 1;
                self.agreements += 1;
            }
            self.set_tolerance(tolerance);
            return true;
        }
        self.set_tolerance(tolerance);
        self.divergence(
            Divergence::value(record, field, format!("{oracle:?}"), format!("{rust:?}")).with_note(
                format!(
                    "floats compared at {}; |a-b| = {:?}",
                    describe_tolerance(tolerance),
                    delta(oracle, rust)
                ),
            ),
        );
        false
    }

    /// Records a field-level divergence.
    ///
    /// Retention is capped but the **count** is not: a report that over a real
    /// corpus can produce one per field per record, and a cap that also capped
    /// the count would turn "there were 40 000 of these" into "there were
    /// 4 096 of these". The note is emitted once, when the cap is first hit.
    pub fn divergence(&mut self, divergence: Divergence) {
        if self.divergences.len() >= self.max_divergences {
            if !self.truncation_noted {
                self.truncation_noted = true;
                self.notes.push(format!(
                    "divergence list truncated at {} entries; further divergences are counted \
                     exactly but not retained",
                    self.max_divergences
                ));
            }
        } else {
            self.divergences.push(divergence);
        }
        if !self.field_mode {
            self.records_walked += 1;
            *self.outcomes.entry("diverged").or_insert(0) += 1;
        }
    }

    /// Records a value that is not a divergence: a definitional or structural
    /// difference that a reader must see without it counting as a defect.
    pub fn note_divergence(&mut self, divergence: Divergence) {
        debug_assert_eq!(
            divergence.class,
            DivergenceClass::Definitional,
            "note_divergence is for definitional findings; a value mismatch must go through divergence()"
        );
        self.divergence(divergence);
    }

    /// The finished report.
    pub fn finish(mut self) -> DifferentialReport {
        self.flush_verdict_samples();
        DifferentialReport {
            comparison: self.comparison,
            status: self.status,
            records_walked: self.records_walked,
            agreements: self.agreements,
            outcomes: self.outcomes,
            divergences: self.divergences,
            notes: self.notes,
            tolerance: self.tolerance,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::report::Agreement;

    fn identity() -> RecordIdentity {
        RecordIdentity::new("mini_package.package", 0, 1, 2, 3)
    }

    #[test]
    fn a_difference_inside_the_tolerance_is_equality_and_the_tolerance_is_named() {
        let mut builder = ReportBuilder::new("float", "in-process");
        let agreed = builder.float_field(
            identity(),
            "bbox.min[1]",
            1.000_05,
            1.000_000_1,
            FLOAT_TOLERANCE,
        );
        assert!(agreed);
        let report = builder.finish();
        assert_eq!(report.outcome("equal"), 1);
        assert!(report.divergences.is_empty());
        let tolerance = report
            .tolerance
            .expect("the report must name the tolerance");
        assert!(tolerance.contains("1e-4"), "{tolerance}");
    }

    #[test]
    fn a_difference_outside_the_tolerance_is_a_divergence_quoting_both_values() {
        let mut builder = ReportBuilder::new("float", "in-process");
        let agreed = builder.float_field(identity(), "radius", 1.0, 1.5, FLOAT_TOLERANCE);
        assert!(!agreed);
        let report = builder.finish();
        assert_eq!(report.outcome("diverged"), 1);
        assert_eq!(report.agreements, 0);
        let divergence = &report.divergences[0];
        assert_eq!(divergence.field, "radius");
        assert!(divergence.oracle.contains('1'));
        assert!(divergence.rust.contains("1.5"));
        assert!(divergence.oracle != divergence.rust);
        assert!(report.tolerance.is_some());
    }

    #[test]
    fn two_nans_agree_and_one_nan_does_not() {
        assert!(agree(f64::NAN, f64::NAN, FLOAT_TOLERANCE));
        assert!(!agree(f64::NAN, 0.0, FLOAT_TOLERANCE));
        assert!(agree(f64::INFINITY, f64::INFINITY, FLOAT_TOLERANCE));
        assert!(!agree(f64::INFINITY, f64::NEG_INFINITY, FLOAT_TOLERANCE));
        assert!(delta(f64::NAN, 1.0).is_nan());
        assert_eq!(delta(f64::INFINITY, f64::INFINITY), 0.0);
    }

    #[test]
    fn the_relative_arm_is_what_catches_a_large_magnitude_and_the_absolute_arm_the_small_one() {
        // 100000 and 100005 differ by 5: 5 > 1e-4, but 5 <= 1e-4 * 100000.
        assert!(agree(100_000.0, 100_005.0, FLOAT_TOLERANCE));
        // 0 and 1e-9: the absolute arm settles it.
        assert!(agree(0.0, 1e-9, FLOAT_TOLERANCE));
        assert!(!agree(0.0, 1e-2, FLOAT_TOLERANCE));
    }

    #[test]
    fn a_record_verdict_is_counted_exactly_once() {
        let mut builder = ReportBuilder::new("v", "in-process");
        builder.record(Agreement::Equal);
        builder.record(Agreement::BothFailed {
            oracle: "a".to_owned(),
            rust: "b".to_owned(),
        });
        let report = builder.finish();
        assert_eq!(report.records_walked, 2);
        assert_eq!(report.agreements, 2);
        assert_eq!(report.outcome("equal"), 1);
        assert_eq!(report.outcome("both-failed"), 1);
    }

    #[test]
    fn a_truncated_divergence_list_says_so_and_keeps_the_count_honest() {
        let mut builder = ReportBuilder::new("v", "in-process").with_max_divergences(2);
        for value in 0..5 {
            builder.divergence(Divergence::value(
                identity(),
                "f",
                value.to_string(),
                (value + 1).to_string(),
            ));
        }
        let report = builder.finish();
        assert_eq!(report.divergences.len(), 2);
        assert_eq!(report.outcome("diverged"), 5);
        assert!(report.notes.iter().any(|n| n.contains("truncated")));
    }
}
