//! What a comparison found: identity, verdict, and the two values that differ.

use core::fmt;
use std::collections::BTreeMap;

/// Which record a verdict is about.
///
/// Every comparison is over records in a named package, and a bare offset into
/// that package is not an identity anyone can look up later. The triple is
/// carried in full, and the index is carried too because a package may (and in
/// the real corpus does) hold two rows with the same triple.
#[derive(Debug, Clone, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct RecordIdentity {
    /// File name of the package, e.g. `Spore_Content.package`.
    pub package: String,
    /// Ordinal of the row in that package's index.
    pub index: usize,
    /// Record type id.
    pub type_id: u32,
    /// Group id.
    pub group_id: u32,
    /// Instance id.
    pub instance_id: u32,
}

impl RecordIdentity {
    /// Identity for row `index` of `entry`, in `package`.
    #[must_use]
    pub fn new(
        package: impl Into<String>,
        index: usize,
        type_id: u32,
        group_id: u32,
        instance_id: u32,
    ) -> Self {
        Self {
            package: package.into(),
            index,
            type_id,
            group_id,
            instance_id,
        }
    }

    /// Identity for a record with no package row behind it (a loose fixture).
    #[must_use]
    pub fn loose(package: impl Into<String>) -> Self {
        Self {
            package: package.into(),
            index: usize::MAX,
            type_id: 0,
            group_id: 0,
            instance_id: 0,
        }
    }
}

impl fmt::Display for RecordIdentity {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        if self.index == usize::MAX {
            return write!(f, "{} (loose record)", self.package);
        }
        write!(
            f,
            "{}[{}] t=0x{:08x} g=0x{:08x} i=0x{:08x}",
            self.package, self.index, self.type_id, self.group_id, self.instance_id
        )
    }
}

/// The verdict for one record.
///
/// `BothFailed` is deliberately **not** a divergence. Two decoders refusing the
/// same bytes is agreement about the bytes; reporting it as a disagreement
/// would drown the disagreements that are real.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Agreement {
    /// Both sides produced the same value, field by field.
    Equal,
    /// Both sides produced a value and they are not the same. Each reason is a
    /// human sentence; the quotable pair for each is a [`Divergence`] in the
    /// same report.
    ///
    /// This variant exists for the cases where there is no single field to
    /// blame -- a differing record *count*, a whole record one side could not
    /// read. Naming those as one field called `parse` would be a lie about the
    /// shape of the disagreement.
    Diverged(Vec<String>),
    /// Only the oracle produced a value; the Rust side refused. A finding, and
    /// not a crash.
    OracleOnly(String),
    /// Only the Rust side produced a value; the oracle refused. A finding, and
    /// not a crash.
    RustOnly(String),
    /// Neither side produced a value. Both messages are kept, because "both
    /// refused" is only informative if you can read *why* each refused.
    BothFailed {
        /// The oracle's message, verbatim.
        oracle: String,
        /// The Rust message, verbatim.
        rust: String,
    },
}

impl Agreement {
    /// The fixed-vocabulary label this verdict is tallied under.
    #[must_use]
    pub const fn label(&self) -> &'static str {
        match self {
            Self::Equal => "equal",
            Self::Diverged(_) => "diverged",
            Self::OracleOnly(_) => "oracle-only",
            Self::RustOnly(_) => "rust-only",
            Self::BothFailed { .. } => "both-failed",
        }
    }

    /// Whether this verdict carries no finding.
    ///
    /// `Equal` and `BothFailed` are both clean: agreement, and agreement about
    /// a refusal. `Diverged`, `OracleOnly` and `RustOnly` are all findings --
    /// exactly one side producing a value is a divergence in the only sense
    /// that matters, and calling it clean would hide it.
    #[must_use]
    pub const fn is_clean(&self) -> bool {
        matches!(self, Self::Equal | Self::BothFailed { .. })
    }
}

impl Agreement {
    /// The message this verdict carries, or `None` for `Equal` and for a
    /// `Diverged` (whose reasons are quotable individually as `Divergence`s).
    #[must_use]
    pub fn message(&self) -> Option<String> {
        match self {
            Self::Equal | Self::Diverged(_) => None,
            Self::OracleOnly(why) | Self::RustOnly(why) => Some(why.clone()),
            Self::BothFailed { oracle, rust } => Some(format!("oracle={oracle} | rust={rust}")),
        }
    }
}

impl fmt::Display for Agreement {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Equal => f.write_str("equal"),
            Self::Diverged(reasons) => write!(f, "diverged ({} reason(s))", reasons.len()),
            Self::OracleOnly(why) => write!(f, "oracle-only: {why}"),
            Self::RustOnly(why) => write!(f, "rust-only: {why}"),
            Self::BothFailed { oracle, rust } => {
                write!(f, "both refused: oracle={oracle:?} rust={rust:?}")
            }
        }
    }
}

/// Why a divergence is reported, which decides how a reader should take it.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub enum DivergenceClass {
    /// The two sides read the same bytes and produced different values. This is
    /// the class that matters: one of them is wrong about the format.
    ValueMismatch,
    /// Exactly one side produced a value. Also a bug on whichever side refused
    /// something the other handled.
    OneSidedDecode,
    /// The two sides disagree because they are *asked different questions* --
    /// different definitions of "decodable", different field types, a refusal
    /// one implementation applies by name. Reported in full so it can be read
    /// as a design decision rather than mistaken for a defect, but not counted
    /// as a defect.
    Definitional,
    /// The overall shape differed: record counts, ordering, coverage.
    Structural,
}

impl DivergenceClass {
    /// The fixed-vocabulary label this class is tallied under.
    #[must_use]
    pub const fn label(self) -> &'static str {
        match self {
            Self::ValueMismatch => "value-mismatch",
            Self::OneSidedDecode => "one-sided-decode",
            Self::Definitional => "definitional",
            Self::Structural => "structural",
        }
    }
}

impl fmt::Display for DivergenceClass {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.label())
    }
}

/// One field-level disagreement, quotable on both sides.
///
/// A divergence that cannot quote both values is an opinion, so the constructor
/// takes them and `Display` prints them verbatim between quotes. There is no
/// way to build one with a side missing.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Divergence {
    /// The record this is about.
    pub record: RecordIdentity,
    /// The field path, e.g. `entry[41].stored_size` or `bbox.min[1]`.
    pub field: String,
    /// What the oracle said, verbatim.
    pub oracle: String,
    /// What the Rust side said, verbatim.
    pub rust: String,
    /// How to take it.
    pub class: DivergenceClass,
    /// Optional extra context: the tolerance used, the byte window, why a
    /// refusal is expected.
    pub note: Option<String>,
}

impl Divergence {
    /// A value-level disagreement.
    #[must_use]
    pub fn value(
        record: RecordIdentity,
        field: impl Into<String>,
        oracle: impl Into<String>,
        rust: impl Into<String>,
    ) -> Self {
        Self {
            record,
            field: field.into(),
            oracle: oracle.into(),
            rust: rust.into(),
            class: DivergenceClass::ValueMismatch,
            note: None,
        }
    }

    /// Sets the class.
    #[must_use]
    pub fn with_class(mut self, class: DivergenceClass) -> Self {
        self.class = class;
        self
    }

    /// Sets the note.
    #[must_use]
    pub fn with_note(mut self, note: impl Into<String>) -> Self {
        self.note = Some(note.into());
        self
    }
}

impl fmt::Display for Divergence {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "[{}] {} {}\n      oracle: {:?}\n      rust:   {:?}",
            self.class, self.record, self.field, self.oracle, self.rust
        )?;
        if let Some(note) = &self.note {
            write!(f, "\n      note:   {note}")?;
        }
        Ok(())
    }
}

/// Whether a comparison ran.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Status {
    /// The comparison ran over whatever records it found.
    Complete,
    /// It did not run, and this is why. A missing game install is an ordinary
    /// state, not a failure, so the reason is a sentence and not an error.
    Skipped(String),
}

impl Status {
    /// `true` when the comparison ran.
    #[must_use]
    pub fn is_complete(&self) -> bool {
        matches!(self, Self::Complete)
    }

    /// `true` when the comparison was skipped.
    #[must_use]
    pub fn is_skipped(&self) -> bool {
        matches!(self, Self::Skipped(_))
    }
}

impl fmt::Display for Status {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Complete => f.write_str("complete"),
            Self::Skipped(reason) => write!(f, "skipped: {reason}"),
        }
    }
}

/// Everything one comparison found.
///
/// `agreements` counts records that reached a verdict without a
/// field-level disagreement -- that is, `Equal`, `OracleOnly`, `RustOnly` and
/// `BothFailed` together. `outcomes` breaks that down by label so a caller can
/// tell "both sides agreed on 1131 records" from "both sides agreed on 1131
/// records, 900 of them by both refusing", which are very different claims.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct DifferentialReport {
    /// Name of the comparison, e.g. `rw4-describe`.
    pub comparison: String,
    /// Whether it ran.
    pub status: Status,
    /// Records the comparison looked at.
    pub records_walked: usize,
    /// Records that reached a verdict with no field-level disagreement.
    pub agreements: usize,
    /// Verdict histogram over the fixed vocabulary in [`Agreement::label`].
    pub outcomes: BTreeMap<&'static str, usize>,
    /// Every field-level disagreement, in discovery order.
    pub divergences: Vec<Divergence>,
    /// Free-form context: how the oracle was invoked, what was measured, what
    /// could not be compared and why.
    pub notes: Vec<String>,
    /// The float tolerance this comparison applied, named. `None` when the
    /// comparison has no float field, which is itself worth knowing.
    pub tolerance: Option<String>,
}

impl DifferentialReport {
    /// A report for a comparison that did not run.
    #[must_use]
    pub fn skipped(comparison: &str, reason: impl Into<String>) -> Self {
        Self {
            comparison: comparison.to_owned(),
            status: Status::Skipped(reason.into()),
            records_walked: 0,
            agreements: 0,
            outcomes: BTreeMap::new(),
            divergences: Vec::new(),
            notes: Vec::new(),
            tolerance: None,
        }
    }

    /// The count of one verdict label, or `0`.
    #[must_use]
    pub fn outcome(&self, label: &str) -> usize {
        self.outcomes.get(label).copied().unwrap_or(0)
    }

    /// `true` when the comparison ran and found no finding at all.
    ///
    /// Not merely "the divergence list is empty": a record only one side could
    /// decode records no divergence but is still a finding, so the verdict
    /// histogram decides this too.
    #[must_use]
    pub fn is_clean(&self) -> bool {
        self.status.is_complete()
            && self.divergences.is_empty()
            && self.outcome("diverged") == 0
            && self.outcome("oracle-only") == 0
            && self.outcome("rust-only") == 0
    }

    /// `true` when every record the comparison reached agreed.
    #[must_use]
    pub fn all_records_agree(&self) -> bool {
        self.records_walked > 0
            && self.agreements == self.records_walked
            && self.divergences.is_empty()
    }

    /// A one-paragraph human summary, including the first divergences.
    #[must_use]
    pub fn summary(&self) -> String {
        let mut out = format!(
            "{} [{}]: walked {} record(s), {} agreement(s), {} divergence(s)",
            self.comparison,
            self.status,
            self.records_walked,
            self.agreements,
            self.divergences.len()
        );
        if let Some(tolerance) = &self.tolerance {
            out.push_str(&format!("; float tolerance {tolerance}"));
        }
        for (label, count) in &self.outcomes {
            out.push_str(&format!("\n  {label}: {count}"));
        }
        for note in &self.notes {
            out.push_str(&format!("\n  note: {note}"));
        }
        // The retained list is capped by the builder, so it can be shorter than
        // the `diverged` count. Print what is retained and say how many of the
        // total it covers -- a reader must never take a capped list for the
        // whole set, and the header already states the exact count.
        const SHOWN: usize = 20;
        let shown = self.divergences.len().min(SHOWN);
        for divergence in self.divergences.iter().take(SHOWN) {
            out.push_str(&format!("\n  {divergence}"));
        }
        let total = self.outcome("diverged");
        if total > shown {
            out.push_str(&format!(
                "\n  ... showing {shown} of {total} divergence(s); see the notes for the cap"
            ));
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn identity() -> RecordIdentity {
        RecordIdentity::new(
            "mini_package.package",
            1,
            0x2F4E_681B,
            0x3333_3333,
            0x4444_4444,
        )
    }

    #[test]
    fn a_divergence_quotes_both_sides_in_its_text() {
        let text = Divergence::value(identity(), "describe", "0x1 obj=1", "0x1 obj=2").to_string();
        assert!(text.contains("\"0x1 obj=1\""), "{text}");
        assert!(text.contains("\"0x1 obj=2\""), "{text}");
        assert!(text.contains("describe"));
        assert!(text.contains("mini_package.package[1]"));
        assert!(text.contains("t=0x2f4e681b"));
    }

    #[test]
    fn a_refusal_by_both_sides_is_agreement_not_divergence() {
        let agreement = Agreement::BothFailed {
            oracle: "ValueError: unsupported fourcc 0x00001500".to_owned(),
            rust: "texture: unsupported fourcc 0x00001500".to_owned(),
        };
        assert!(agreement.is_clean());
        assert_eq!(agreement.label(), "both-failed");
    }

    #[test]
    fn the_outcome_histogram_keeps_a_refusal_visible_next_to_an_equality() {
        let mut report = DifferentialReport::skipped("x", "y");
        report.status = Status::Complete;
        report.records_walked = 3;
        report.agreements = 3;
        for label in ["equal", "equal", "both-failed"] {
            *report.outcomes.entry(label).or_insert(0) += 1;
        }
        assert_eq!(report.outcome("equal"), 2);
        assert_eq!(report.outcome("both-failed"), 1);
        assert!(report.all_records_agree());
        assert!(report.is_clean());
    }
}
