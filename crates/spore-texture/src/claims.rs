//! Every claim this crate makes that is **not** verified, with its grade.
//!
//! # Why this module exists
//!
//! A decoder that hands back eight `u32`s has already lost the only interesting
//! question about three of them. [`crate::RasterEnvelope`] carries `field_10`,
//! `field_18` and `field_1c`; nothing in the type says that nobody knows what
//! those words are. That is exactly the failure this repository exists to
//! prevent: an observation and an interpretation becoming indistinguishable
//! after they leave the decoder (see `spore_core::evidence`).
//!
//! So each such statement is recorded here **with its grade**, and the grades
//! for the unresolved envelope words are [`EvidenceLevel::Unknown`] — not
//! `Inferred`, not `Supported`, and not a plausible guess dressed up as
//! `Observed`. A word whose value has been seen in every sample still has an
//! unknown *meaning*, and the value being constant is not evidence about what
//! it is.
//!
//! # The two vocabularies, kept apart
//!
//! * The **observation** ("`field_10` reads 8 in every sampled record; no
//!   decoder reads it") is a fact about bytes and is plain text.
//! * The **meaning** ("`field_10` is a format revision / a bit depth / a
//!   padding hole") is the claim, and it is carried as a [`Fact`]. For an
//!   unresolved field the fact is **unavailable**, which in this repository's
//!   vocabulary means "we looked and found nothing" — never a zero, never a
//!   default, never a silent `false`.
//!
//! # What is *not* here
//!
//! Anything this crate reproduces from two independent implementations
//! (`tools/spore/dxt5/dxt5.py` and `src/assets/Dxt5.cpp`), checked
//! byte-for-byte against the hand-computed golden values in
//! `tests/test_textures.py::TestDxt5Synthetic`. The block layout, the alpha
//! ramp and its half-to-even rounding, the inverted palette test and the R5G5B5
//! channel read are not claims in this module: they are pinned by tests. What
//! *is* recorded is that they depart from the published BC3 specification —
//! as [`DXT5_SPEC_DEVIATIONS`], because "this is not what the spec says" is
//! established. "The spec is what Spore should have written" is not a question
//! this crate asks.

use std::sync::OnceLock;

use spore_core::evidence::{EvidenceLevel, EvidenceState, Fact, Provenance};

/// What the envelope word at `0x10` means.
pub const ENVELOPE_FIELD_10_MEANING: &str = "envelope_field_10_meaning";

/// What the envelope word at `0x18` means.
pub const ENVELOPE_FIELD_18_MEANING: &str = "envelope_field_18_meaning";

/// What the envelope word at `0x1c` means.
pub const ENVELOPE_FIELD_1C_MEANING: &str = "envelope_field_1c_meaning";

/// What the envelope word at `0x00` means beyond "format revision".
pub const ENVELOPE_VERSION_MEANING: &str = "envelope_version_meaning";

/// What the 16 opaque bytes of a layer header hold.
pub const LAYER_HEADER_CONTENTS: &str = "layer_header_contents";

/// Why every layer header precedes every layer payload.
pub const LAYER_INTERLEAVE: &str = "layer_header_payload_interleave";

/// What the `0x15xx` luminance format's records contain.
pub const LUMINANCE_FOURCC: &str = "luminance_fourcc_family";

/// What happens to mip levels beyond 32.
pub const MIPS_BEYOND_32: &str = "mip_chain_beyond_32";

/// How Spore's block decode departs from the published BC3/DXT5 specification.
pub const DXT5_SPEC_DEVIATIONS: &str = "dxt5_spec_deviations";

/// Why an address is a `Fact` and not a value.
///
/// `Unavailable` is the honest state for a field whose meaning nobody
/// established: the repository's rule is that it must not be represented as a
/// zero, an empty string or `false`. Each subject therefore carries either an
/// available meaning with a grade and provenance, or this unavailable envelope.
const NO_MEANING_ESTABLISHED: &str = "meaning_not_established";

/// One recorded claim about the raster format: what was observed, and what (if
/// anything) that observation is known to mean.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TextureClaim {
    /// Stable identifier, e.g. `"envelope_field_10_meaning"`.
    pub subject: &'static str,
    /// What the bytes are observed to be, and what this crate does with them.
    /// This half is always present and is never an interpretation.
    pub observation: &'static str,
    /// The meaning, when one is established. `unavailable` means "we looked and
    /// found nothing", which is not the same as "it is zero".
    pub meaning: Fact<&'static str>,
}

/// The claims, in declaration order.
///
/// Lazily built because [`Fact`] cannot be constructed in a `const` context:
/// an available fact must carry a `Vec<Provenance>`.
pub fn all_claims() -> &'static [TextureClaim] {
    static CLAIMS: OnceLock<Vec<TextureClaim>> = OnceLock::new();
    CLAIMS.get_or_init(|| {
        vec![
            unresolved(
                ENVELOPE_FIELD_10_MEANING,
                "field_10 reads 8 in every sampled raster (the 512x512 records 0x40662900/01, the \
                 raster_ap_5552/raster_0 family, and the 0x15 record raster_6948). No decoder \
                 reads it: not the Python oracle, not src/assets/Texture.cpp, not this crate. \
                 docs/MATERIALS-DESIGN.md section 1 records it as '=8 every sample; decoder must \
                 NOT rely on it'.",
            ),
            unresolved(
                ENVELOPE_FIELD_18_MEANING,
                "field_18 reads 0x00040000 in every sampled raster, including the 0x15 luminance \
                 record whose field_1c differs from the DXT5 records'. No decoder reads it. It is \
                 carried verbatim by RasterEnvelope so a caller can see it, and never to make a \
                 decision.",
            ),
            unresolved(
                ENVELOPE_FIELD_1C_MEANING,
                "field_1c reads 0x0000FFFF in DXT5 records and holds a float 1.0 in the 0x15 \
                 luminance records, per tools/spore/raster/raster.py. It therefore varies with \
                 the format, which is the whole of what is known about it.",
            ),
            resolved(
                ENVELOPE_VERSION_MEANING,
                "version reads 1 in every sampled raster. No record with any other value has been \
                 seen, so the crate does not validate it: refusing an unobserved version would be \
                 a guess about a format nobody has.",
                EvidenceLevel::Observed,
                "A format revision counter, always 1 in the records sampled so far. Never \
                 validated, because an unobserved value is not a known-bad one.",
                "docs/MATERIALS-DESIGN.md section 1",
            ),
            unresolved(
                LAYER_HEADER_CONTENTS,
                "Each layer is preceded by 16 bytes read as a 4-byte name plus three u32 (one \
                 sample spells the name 'e9D1'). The three words are skipped, never interpreted, \
                 and no layer's presence depends on them.",
            ),
            resolved(
                LAYER_INTERLEAVE,
                "All n layer headers precede all payloads: payloadOff = 32 + n*16 = 0x40 on every \
                 real 512x512 DXT5 record, and the block at that offset is a valid DXT5 block \
                 (20 00 02 00 65 39 00 00).",
                EvidenceLevel::Observed,
                "Headers are grouped at the front of the payload region rather than interleaved \
                 with their payloads. This is what makes layer i start at 32 + n*16 + i*chain.",
                "docs/MATERIALS-DESIGN.md section 1",
            ),
            unresolved(
                LUMINANCE_FOURCC,
                "Records whose fourcc is in the 0x15 family (observed: raster_6948 at 256x256, \
                 and the 1024x1024 raster_1/raster_2 records) are a different format, not DXT5. \
                 This crate decodes none of them and rejects the family by name rather than \
                 letting the BC3 block codec produce plausible garbage.",
            ),
            resolved(
                MIPS_BEYOND_32,
                "dxt5_chain_size charges 8 bytes per mip past 32 because `w >> mip` is undefined \
                 for mip >= 32. The largest chain observed is 10 mips (512x512, mipCount=10), so \
                 no record exercises the rule.",
                EvidenceLevel::Approximation,
                "One 4x4 block per mip beyond 32. Reproduced from the reference so the two agree; \
                 it bounds an absurd header rather than describing how Spore writes a 33rd mip.",
                "src/assets/Dxt5.cpp",
            ),
            resolved(
                DXT5_SPEC_DEVIATIONS,
                "The block decoder departs from the published BC3/DXT5 specification in four \
                 places, all reproduced from tools/spore/dxt5/dxt5.py and src/assets/Dxt5.cpp and \
                 all pinned by tests/dxt5_golden.rs: (1) the palette-size test is inverted - \
                 c0 > c1 yields TWO colours, not four; (2) channels are read R5G5B5, not R6G6B5, \
                 so a 6-bit input yields red in {0,8} only; (3) codes 0 and 3 return a 6/2 blend \
                 of the endpoints rather than the endpoints themselves; (4) there is no \
                 alpha0 == alpha1 collapse.",
                EvidenceLevel::Verified,
                "Spore's decoder, not the BC3 specification, defines these blocks. A change here \
                 changes decoded pixels and must be justified by a record, never by the spec.",
                "tools/spore/dxt5/dxt5.py",
            ),
        ]
    })
}

/// One claim's envelope, or `None` when this build records no claim for
/// `subject`. Absence is not `UNKNOWN`: it means "this build does not say",
/// which is a different statement from "this build says it is unknown".
pub fn claim(subject: &str) -> Option<&'static TextureClaim> {
    all_claims().iter().find(|entry| entry.subject == subject)
}

/// The grade of one subject's meaning, or [`EvidenceLevel::Unknown`] when this
/// build records nothing for it.
///
/// The grade is about the *meaning*, not about the observation: an unresolved
/// field is `UNKNOWN` even though its value has been seen in every sample.
pub fn grade_of(subject: &str) -> EvidenceLevel {
    claim(subject).map_or(EvidenceLevel::Unknown, |entry| entry.meaning.level())
}

/// Builds a claim whose meaning nobody established.
///
/// The observation stands on its own; the meaning is a non-finding, and
/// `EvidenceLevel::Unknown` is what that costs.
fn unresolved(subject: &'static str, observation: &'static str) -> TextureClaim {
    TextureClaim {
        subject,
        observation,
        meaning: Fact::unavailable(NO_MEANING_ESTABLISHED),
    }
}

/// Builds a claim whose meaning is established, with a mandatory grade and
/// provenance: an unsourced claim is the failure this module exists to prevent.
fn resolved(
    subject: &'static str,
    observation: &'static str,
    level: EvidenceLevel,
    meaning: &'static str,
    basis: &'static str,
) -> TextureClaim {
    TextureClaim {
        subject,
        observation,
        meaning: Fact::new(
            level,
            EvidenceState::Derived,
            vec![Provenance::derived(basis)],
            meaning,
        ),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn every_unresolved_subject_is_unavailable_and_unknown() {
        // The three envelope words, the layer header and the luminance family.
        // Each must be a non-finding, never a zero and never a guess.
        for subject in [
            ENVELOPE_FIELD_10_MEANING,
            ENVELOPE_FIELD_18_MEANING,
            ENVELOPE_FIELD_1C_MEANING,
            LAYER_HEADER_CONTENTS,
            LUMINANCE_FOURCC,
        ] {
            let entry = claim(subject).unwrap_or_else(|| panic!("{subject} is not recorded"));
            assert!(
                entry.meaning.is_unavailable(),
                "{subject}: an unresolved meaning must be unavailable, not a value"
            );
            assert_eq!(entry.meaning.level(), EvidenceLevel::Unknown, "{subject}");
            assert_eq!(
                entry.meaning.evidence_state(),
                EvidenceState::Missing,
                "{subject}"
            );
            assert_eq!(entry.meaning.value(), None, "{subject}");
            assert!(
                entry.meaning.provenance().is_empty(),
                "{subject}: a non-finding has no provenance to repeat"
            );
            assert_eq!(grade_of(subject), EvidenceLevel::Unknown, "{subject}");
        }
    }

    #[test]
    fn an_established_claim_carries_its_grade_and_provenance() {
        for subject in [
            ENVELOPE_VERSION_MEANING,
            LAYER_INTERLEAVE,
            MIPS_BEYOND_32,
            DXT5_SPEC_DEVIATIONS,
        ] {
            let entry = claim(subject).unwrap_or_else(|| panic!("{subject} is not recorded"));
            assert!(entry.meaning.is_available(), "{subject}");
            assert_ne!(entry.meaning.level(), EvidenceLevel::Unknown, "{subject}");
            assert!(
                !entry.meaning.provenance().is_empty(),
                "{subject}: an unsourced claim is the failure this module exists to prevent"
            );
            assert_eq!(
                entry.meaning.reason(),
                None,
                "{subject}: an available fact has no reason"
            );
            assert_eq!(
                entry.meaning.value(),
                Some(entry.meaning.value().unwrap_or(&""))
            );
        }
    }

    #[test]
    fn observations_are_always_present_and_thin_claims_are_rejected() {
        for entry in all_claims() {
            assert!(!entry.subject.is_empty());
            assert!(
                entry.observation.len() > 40,
                "{}: observation too thin to be evidence",
                entry.subject
            );
            assert_eq!(
                entry.meaning.state(),
                if entry.meaning.is_available() {
                    spore_core::evidence::FactState::Available
                } else {
                    spore_core::evidence::FactState::Unavailable
                }
            );
        }
    }

    #[test]
    fn subjects_are_unique_and_an_unrecorded_subject_is_not_a_guess() {
        let claims = all_claims();
        for (index, entry) in claims.iter().enumerate() {
            for other in claims.iter().skip(index + 1) {
                assert_ne!(entry.subject, other.subject, "duplicate subject");
            }
        }
        assert_eq!(claim("no_such_subject"), None);
        assert_eq!(grade_of("no_such_subject"), EvidenceLevel::Unknown);
    }

    #[test]
    fn the_beyond_32_rule_is_an_approximation_not_an_observation() {
        // Grading the reproduced reference rule as Observed would be a lie: no
        // record has more than 10 mips.
        assert_eq!(grade_of(MIPS_BEYOND_32), EvidenceLevel::Approximation);
        assert_eq!(grade_of(DXT5_SPEC_DEVIATIONS), EvidenceLevel::Verified);
        assert_eq!(grade_of(LAYER_INTERLEAVE), EvidenceLevel::Observed);
    }
}
