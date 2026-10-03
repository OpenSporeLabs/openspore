//! The evidence surface a consumer of this crate can query.
//!
//! The point of these tests is not the wording of a claim but the *shape*: an
//! unresolved field must come back as a non-finding graded `UNKNOWN`, never as a
//! zero or a default, and an established claim must carry provenance.

use spore_core::evidence::{EvidenceLevel, EvidenceState, FactState};
use spore_texture::claims::{
    all_claims, claim, grade_of, DXT5_SPEC_DEVIATIONS, ENVELOPE_FIELD_10_MEANING,
    ENVELOPE_FIELD_18_MEANING, ENVELOPE_FIELD_1C_MEANING, LAYER_HEADER_CONTENTS, LAYER_INTERLEAVE,
    LUMINANCE_FOURCC, MIPS_BEYOND_32,
};

#[test]
fn the_three_unresolved_envelope_words_are_unknown_non_findings() {
    for subject in [
        ENVELOPE_FIELD_10_MEANING,
        ENVELOPE_FIELD_18_MEANING,
        ENVELOPE_FIELD_1C_MEANING,
    ] {
        let entry = claim(subject).expect("recorded");
        assert_eq!(entry.meaning.state(), FactState::Unavailable, "{subject}");
        assert_eq!(entry.meaning.level(), EvidenceLevel::Unknown, "{subject}");
        assert_eq!(
            entry.meaning.evidence_state(),
            EvidenceState::Missing,
            "{subject}"
        );
        assert_eq!(
            entry.meaning.value(),
            None,
            "{subject}: unavailable is not a value"
        );
        assert!(
            entry.meaning.provenance().is_empty(),
            "{subject}: a non-finding has no provenance"
        );
        assert!(
            !entry.observation.is_empty(),
            "{subject}: the observation is still stated"
        );
    }
}

#[test]
fn the_deliberate_deviations_are_recorded_as_verified_against_the_oracle() {
    assert_eq!(grade_of(DXT5_SPEC_DEVIATIONS), EvidenceLevel::Verified);
    let entry = claim(DXT5_SPEC_DEVIATIONS).expect("recorded");
    // The record must name all four departures, or a future reader inherits the
    // belief that this codec follows the published specification.
    let statement = entry.meaning.value().copied().unwrap_or_default();
    let text = format!("{} {statement}", entry.observation);
    for needle in ["inverted", "R5G5B5", "alpha0 == alpha1", "codes 0 and 3"] {
        assert!(
            text.contains(needle),
            "deviation record does not mention {needle:?}"
        );
    }
}

#[test]
fn the_reproduced_reference_rules_are_not_over_graded() {
    // Observed: read off real records.
    assert_eq!(grade_of(LAYER_INTERLEAVE), EvidenceLevel::Observed);
    // Approximation, not Observed: no record has more than 10 mips, so the
    // beyond-32 rule is a bound reproduced from the reference, not an
    // observation of Spore's behaviour.
    assert_eq!(grade_of(MIPS_BEYOND_32), EvidenceLevel::Approximation);
    // Unresolved: the layer header's three words and the luminance format.
    assert_eq!(grade_of(LAYER_HEADER_CONTENTS), EvidenceLevel::Unknown);
    assert_eq!(grade_of(LUMINANCE_FOURCC), EvidenceLevel::Unknown);
}

#[test]
fn an_unrecorded_subject_is_absence_rather_than_a_guess() {
    assert!(claim("no_such_subject").is_none());
    assert_eq!(grade_of("no_such_subject"), EvidenceLevel::Unknown);
    assert!(!all_claims().is_empty());
}
