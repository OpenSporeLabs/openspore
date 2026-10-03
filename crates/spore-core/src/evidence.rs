//! The evidence and provenance vocabulary.
//!
//! # The problem this solves
//!
//! OpenSpore states a great many things about Spore that are *not* facts. "The
//! file bounding box covers the LOD range", "UBYTE4 normals are biased", "this
//! group is `CellModels`" — each is a claim with a different strength behind
//! it. When an engine stores such a claim as a bare `f32` or a bare `bool`,
//! the grade is lost at the moment it is written and can never be recovered.
//! A later reader cannot tell an observation from an inference.
//!
//! [`EvidenceLevel`] is the seven-rung grade scale used across the repository.
//! It is deliberately a *total* order so "strongest claim wins" is expressible
//! as `max()` and never as a hand-ranked if-chain.
//!
//! # Unavailable is not zero
//!
//! [`Fact`] carries the same distinction the semantic exchange format does: a
//! group can be `Available` with a value, or `Unavailable` meaning *we looked
//! and found nothing*. `Unavailable` is never represented as a zero value, an
//! empty collection, or `false`. Collapsing the two is how "we did not look"
//! turns into "we looked and found nothing".
//!
//! See `docs/tooling/semantic-exchange.md` §5 for the normative format contract
//! and `docs/tooling/validation-dimensions.md` for how the grades are produced.

use core::fmt;

/// How strongly a claim is supported.
///
/// The rung names and their order are the repository's canonical 7-level scale
/// (`knowledgegraph/scale.py`, `docs/analysis/dossiers/*`). They are **not**
/// interchangeable with the older 5-level scale, which is read-only compat.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum EvidenceLevel {
    /// Nothing supports the claim and nothing was found.
    Unknown,
    /// A placeholder standing in for a value nobody has observed.
    Approximation,
    /// Derived by reasoning from observed facts, not directly observed.
    Inferred,
    /// Observed, but only as a single sample or through a partial decode.
    Supported,
    /// Seen directly at runtime or in a real record.
    Observed,
    /// Corroborated by a name from the community SDK plus a matching layout.
    Confirmed,
    /// Established against the original binary by a repeatable differential.
    Verified,
}

impl EvidenceLevel {
    /// The canonical spelling used in every committed artifact.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Unknown => "UNKNOWN",
            Self::Approximation => "APPROXIMATION",
            Self::Inferred => "INFERRED",
            Self::Supported => "SUPPORTED",
            Self::Observed => "OBSERVED",
            Self::Confirmed => "CONFIRMED",
            Self::Verified => "VERIFIED",
        }
    }

    /// Parses a canonical spelling. Unknown input becomes [`Self::Unknown`]
    /// rather than an error: a label this build does not know is, by
    /// definition, not evidence this build understands.
    pub fn parse(text: &str) -> Self {
        match text {
            "APPROXIMATION" => Self::Approximation,
            "INFERRED" => Self::Inferred,
            "SUPPORTED" => Self::Supported,
            "OBSERVED" => Self::Observed,
            "CONFIRMED" => Self::Confirmed,
            "VERIFIED" => Self::Verified,
            _ => Self::Unknown,
        }
    }

    /// The strongest of two grades; `Unknown` loses to everything.
    pub fn strongest(self, other: Self) -> Self {
        self.max(other)
    }
}

impl fmt::Display for EvidenceLevel {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// *How* a fact was obtained, independent of *how strong* it is.
///
/// A [`EvidenceLevel`] says how much to trust a value. This says whether it
/// came out of a live disassembly, a committed artifact, or a derivation. The
/// two are orthogonal: a derivation can be `VERIFIED` and a live capture can be
/// merely `SUPPORTED`.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum EvidenceState {
    /// Produced by a live query against a running analysis tool.
    Live,
    /// Computed by a committed tool from committed inputs.
    Derived,
    /// Read verbatim out of a committed artifact.
    Persisted,
    /// Expected by the schema but absent from the source.
    Missing,
}

impl EvidenceState {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Live => "LIVE",
            Self::Derived => "DERIVED",
            Self::Persisted => "PERSISTED",
            Self::Missing => "MISSING",
        }
    }

    pub fn parse(text: &str) -> Self {
        match text {
            "LIVE" => Self::Live,
            "DERIVED" => Self::Derived,
            "PERSISTED" => Self::Persisted,
            _ => Self::Missing,
        }
    }
}

impl fmt::Display for EvidenceState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// How a provenance entry was obtained.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum ProvenanceMode {
    /// Read verbatim from a committed artifact.
    Persisted,
    /// Computed by a committed tool.
    Derived,
    /// Produced by a live external tool.
    Live,
    /// Imported from an external, non-OpenSpore producer.
    Imported,
}

impl ProvenanceMode {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Persisted => "persisted",
            Self::Derived => "derived",
            Self::Live => "live",
            Self::Imported => "imported",
        }
    }
}

impl fmt::Display for ProvenanceMode {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// The *kind of source* a claim came from.
///
/// This is a closed vocabulary and the closure is enforced, not advisory. A
/// runtime artifact claiming [`SourceClass::Ghidra`] is refused: that would be
/// a static artifact wearing a runtime file's schema, and the whole point of
/// keeping static and runtime facts apart is that they are not interchangeable.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum SourceClass {
    /// Built by an index generator in this repository.
    GeneratedIndex,
    /// A file committed to this repository.
    CommittedArtifact,
    /// The Ghidra analysis database.
    Ghidra,
    /// A committed derivation tool.
    Derived,
    /// An external runtime producer (for example `spore-recomp`).
    Runtime,
}

impl SourceClass {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::GeneratedIndex => "generated_index",
            Self::CommittedArtifact => "committed_artifact",
            Self::Ghidra => "ghidra",
            Self::Derived => "derived",
            Self::Runtime => "runtime",
        }
    }

    pub fn parse(text: &str) -> Option<Self> {
        match text {
            "generated_index" => Some(Self::GeneratedIndex),
            "committed_artifact" => Some(Self::CommittedArtifact),
            "ghidra" => Some(Self::Ghidra),
            "derived" => Some(Self::Derived),
            "runtime" => Some(Self::Runtime),
            _ => None,
        }
    }

    /// The four source classes a *static* artifact may claim.
    pub const fn static_classes() -> [Self; 4] {
        [
            Self::GeneratedIndex,
            Self::CommittedArtifact,
            Self::Ghidra,
            Self::Derived,
        ]
    }
}

impl fmt::Display for SourceClass {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(self.as_str())
    }
}

/// One "where did this come from" entry.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Provenance {
    /// How it was obtained.
    pub mode: ProvenanceMode,
    /// The path, URL or artifact name.
    pub reference: String,
    /// The kind of source it is.
    pub source_class: SourceClass,
}

impl Provenance {
    pub fn new(
        mode: ProvenanceMode,
        reference: impl Into<String>,
        source_class: SourceClass,
    ) -> Self {
        Self {
            mode,
            reference: reference.into(),
            source_class,
        }
    }

    /// A fact committed verbatim to this repository.
    pub fn committed(reference: impl Into<String>) -> Self {
        Self::new(
            ProvenanceMode::Persisted,
            reference,
            SourceClass::CommittedArtifact,
        )
    }

    /// A fact produced by a committed derivation tool.
    pub fn derived(reference: impl Into<String>) -> Self {
        Self::new(ProvenanceMode::Derived, reference, SourceClass::Derived)
    }

    /// A fact captured from a live analysis tool.
    pub fn live(reference: impl Into<String>) -> Self {
        Self::new(ProvenanceMode::Live, reference, SourceClass::Ghidra)
    }
}

/// Whether a [`Fact`] carries a value.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum FactState {
    /// A value is present; see the envelope's grade and provenance.
    Available,
    /// We looked and found nothing. Not a zero, not an empty collection.
    Unavailable,
}

/// A value together with how much it is worth believing and where it came from.
///
/// # Invariants
///
/// * `Unavailable` implies [`EvidenceLevel::Unknown`] and
///   [`EvidenceState::Missing`].
/// * `Unavailable` carries **no** provenance: the provenance of a non-finding
///   is fully determined by its `reason`, and repeating repository paths on
///   every absent group would cost bytes to say nothing.
/// * An `Available` fact with empty provenance is a *bug*, not a default;
///   [`Fact::new`] refuses it so the mistake surfaces at the construction site.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Fact<T> {
    state: FactState,
    level: EvidenceLevel,
    evidence_state: EvidenceState,
    provenance: Vec<Provenance>,
    reason: Option<String>,
    value: Option<T>,
}

impl<T> Fact<T> {
    /// Records that a group was looked for and not found.
    ///
    /// `reason` is a closed-vocabulary code where one exists. It is optional
    /// so a source-supplied specific message can be carried verbatim, which is
    /// better than forcing it into a code that does not fit.
    pub fn unavailable(reason: impl Into<String>) -> Self {
        Self {
            state: FactState::Unavailable,
            level: EvidenceLevel::Unknown,
            evidence_state: EvidenceState::Missing,
            provenance: Vec::new(),
            reason: Some(reason.into()),
            value: None,
        }
    }

    /// Records a present value.
    ///
    /// # Panics
    ///
    /// If `provenance` is empty. A present fact with no source is exactly the
    /// unsourced claim this type exists to prevent.
    pub fn new(
        level: EvidenceLevel,
        evidence_state: EvidenceState,
        provenance: Vec<Provenance>,
        value: T,
    ) -> Self {
        assert!(
            !provenance.is_empty(),
            "an available Fact must carry provenance: an unsourced claim is the failure this type prevents"
        );
        Self {
            state: FactState::Available,
            level,
            evidence_state,
            provenance,
            reason: None,
            value: Some(value),
        }
    }

    /// Convenience for a value read straight out of a committed artifact.
    pub fn persisted(level: EvidenceLevel, reference: impl Into<String>, value: T) -> Self {
        Self::new(
            level,
            EvidenceState::Persisted,
            vec![Provenance::committed(reference)],
            value,
        )
    }

    /// Whether a value is present.
    pub const fn state(&self) -> FactState {
        self.state
    }

    /// Whether a value is present.
    pub const fn is_available(&self) -> bool {
        matches!(self.state, FactState::Available)
    }

    /// Whether the group was searched and came up empty.
    pub const fn is_unavailable(&self) -> bool {
        matches!(self.state, FactState::Unavailable)
    }

    /// How strong the claim is. Meaningless when unavailable, and always
    /// [`EvidenceLevel::Unknown`] then.
    pub const fn level(&self) -> EvidenceLevel {
        self.level
    }

    /// How the fact was obtained.
    pub const fn evidence_state(&self) -> EvidenceState {
        self.evidence_state
    }

    /// Where the fact came from. Always empty when unavailable.
    pub fn provenance(&self) -> &[Provenance] {
        &self.provenance
    }

    /// The closed-vocabulary reason a group is unavailable.
    pub fn reason(&self) -> Option<&str> {
        self.reason.as_deref()
    }

    /// The value, if present.
    ///
    /// `None` here means *unavailable*, which is a different statement from a
    /// present value that happens to be zero.
    pub const fn value(&self) -> Option<&T> {
        self.value.as_ref()
    }

    /// Consumes the envelope and yields the value, or `None` when unavailable.
    pub fn into_value(self) -> Option<T> {
        self.value
    }

    /// Maps the value while keeping the envelope intact.
    pub fn map<U, F: FnOnce(T) -> U>(self, f: F) -> Fact<U> {
        Fact {
            state: self.state,
            level: self.level,
            evidence_state: self.evidence_state,
            provenance: self.provenance,
            reason: self.reason,
            value: self.value.map(f),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn levels_order_from_unknown_to_verified() {
        let mut levels = [
            EvidenceLevel::Verified,
            EvidenceLevel::Unknown,
            EvidenceLevel::Supported,
            EvidenceLevel::Approximation,
            EvidenceLevel::Observed,
            EvidenceLevel::Confirmed,
            EvidenceLevel::Inferred,
        ];
        levels.sort();
        assert_eq!(
            levels,
            [
                EvidenceLevel::Unknown,
                EvidenceLevel::Approximation,
                EvidenceLevel::Inferred,
                EvidenceLevel::Supported,
                EvidenceLevel::Observed,
                EvidenceLevel::Confirmed,
                EvidenceLevel::Verified,
            ]
        );
    }

    #[test]
    fn level_round_trips_through_its_canonical_spelling() {
        for level in [
            EvidenceLevel::Unknown,
            EvidenceLevel::Approximation,
            EvidenceLevel::Inferred,
            EvidenceLevel::Supported,
            EvidenceLevel::Observed,
            EvidenceLevel::Confirmed,
            EvidenceLevel::Verified,
        ] {
            assert_eq!(EvidenceLevel::parse(level.as_str()), level);
        }
    }

    #[test]
    fn an_unrecognised_grade_is_not_evidence_we_understand() {
        // A future label must degrade to UNKNOWN, never to a guess.
        assert_eq!(EvidenceLevel::parse("CONFIRMEDISH"), EvidenceLevel::Unknown);
        assert_eq!(EvidenceLevel::parse("verified"), EvidenceLevel::Unknown);
        assert_eq!(EvidenceLevel::parse("VERIFIED "), EvidenceLevel::Unknown);
    }

    #[test]
    fn strongest_prefers_the_higher_rung() {
        assert_eq!(
            EvidenceLevel::Unknown.strongest(EvidenceLevel::Observed),
            EvidenceLevel::Observed
        );
        assert_eq!(
            EvidenceLevel::Verified.strongest(EvidenceLevel::Inferred),
            EvidenceLevel::Verified
        );
    }

    #[test]
    fn unavailable_is_unknown_and_missing_and_carries_no_provenance() {
        let fact = Fact::<u32>::unavailable("no_evidence_pack");
        assert!(fact.is_unavailable());
        assert!(!fact.is_available());
        assert_eq!(fact.level(), EvidenceLevel::Unknown);
        assert_eq!(fact.evidence_state(), EvidenceState::Missing);
        assert!(
            fact.provenance().is_empty(),
            "a non-finding has no provenance to repeat"
        );
        assert_eq!(fact.reason(), Some("no_evidence_pack"));
        assert_eq!(fact.value(), None);
    }

    #[test]
    fn available_facts_keep_value_grade_and_provenance() {
        let fact = Fact::persisted(EvidenceLevel::Verified, "docs/ASSET-PATH.md", 1156usize);
        assert!(fact.is_available());
        assert_eq!(fact.level(), EvidenceLevel::Verified);
        assert_eq!(fact.evidence_state(), EvidenceState::Persisted);
        assert_eq!(fact.provenance().len(), 1);
        assert_eq!(
            fact.provenance()[0].source_class,
            SourceClass::CommittedArtifact
        );
        assert_eq!(
            fact.reason(),
            None,
            "an available fact has no absence reason"
        );
        assert_eq!(fact.value(), Some(&1156));
    }

    #[test]
    #[should_panic(expected = "must carry provenance")]
    fn an_available_fact_without_provenance_is_refused_at_construction() {
        let _ = Fact::new(
            EvidenceLevel::Verified,
            EvidenceState::Derived,
            Vec::new(),
            1u8,
        );
    }

    #[test]
    fn map_preserves_the_envelope() {
        let fact = Fact::persisted(EvidenceLevel::Supported, "docs/x.md", 21u32).map(|v| v * 2);
        assert_eq!(fact.level(), EvidenceLevel::Supported);
        assert_eq!(fact.value(), Some(&42));
        assert_eq!(fact.provenance().len(), 1);

        let absent = Fact::<u32>::unavailable("no_types").map(|v| v * 2);
        assert!(absent.is_unavailable());
        assert_eq!(absent.reason(), Some("no_types"));
    }

    #[test]
    fn source_class_vocabulary_is_closed() {
        assert_eq!(SourceClass::parse("ghidra"), Some(SourceClass::Ghidra));
        assert_eq!(SourceClass::parse("runtime"), Some(SourceClass::Runtime));
        assert_eq!(SourceClass::parse("disassembly"), None);
        // The static vocabulary deliberately excludes `runtime`.
        assert!(!SourceClass::static_classes().contains(&SourceClass::Runtime));
    }
}
