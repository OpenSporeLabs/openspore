//! The honesty surface: a graded claim and a non-finding are different things,
//! and the crate keeps them apart.
//!
//! The property under test is the one the repository cares about most: a field
//! whose **position and width** are verified and whose **meaning** is not must
//! produce *both* statements — an `OBSERVED` observation of the value and a
//! `Fact::unavailable` about what it means. Collapsing either into the other is
//! how "we did not look" turns into "we looked and found nothing", and how a
//! constant field turns into a fact about the format.

mod support;

use spore_cellcontent::{
    claims, decode, CellContent, CellContentRecord, EvidenceLevel, EvidenceState, ResourceKey,
};

use support::*;

#[test]
fn every_claim_subject_is_unique_and_carries_a_written_basis() {
    for (index, spec) in claims::ALL_CLAIMS.iter().enumerate() {
        assert!(!spec.subject.is_empty());
        assert!(
            spec.basis.len() > 60,
            "{}: a basis too thin to justify a grade",
            spec.subject
        );
        for other in claims::ALL_CLAIMS.iter().skip(index + 1) {
            assert_ne!(spec.subject, other.subject, "duplicate subject");
        }
    }
    assert_eq!(claims::spec_of("no_such_subject"), None);
    assert_eq!(claims::grade_of("no_such_subject"), EvidenceLevel::Unknown);
}

#[test]
fn every_non_finding_is_unknown_missing_and_provenance_free() {
    let mut non_findings = 0;
    for spec in claims::ALL_CLAIMS {
        let Some(reason) = spec.kind.reason() else {
            continue;
        };
        non_findings += 1;
        let fact = claims::non_finding(spec.subject);
        assert!(fact.is_unavailable(), "{}", spec.subject);
        assert!(!fact.is_available(), "{}", spec.subject);
        assert_eq!(fact.level(), EvidenceLevel::Unknown, "{}", spec.subject);
        assert_eq!(
            fact.evidence_state(),
            EvidenceState::Missing,
            "{}",
            spec.subject
        );
        assert_eq!(fact.reason(), Some(reason), "{}", spec.subject);
        assert_eq!(fact.value(), None, "{}", spec.subject);
        assert!(
            fact.provenance().is_empty(),
            "{}: a non-finding has no provenance to repeat",
            spec.subject
        );
        // And it can never carry a value.
        assert!(!spec.kind.can_carry_value(), "{}", spec.subject);
    }
    assert!(
        non_findings >= 8,
        "expected the mean-not-established subjects to be present, found {non_findings}"
    );
}

#[test]
fn every_graded_claim_reports_exactly_its_documented_grade() {
    for spec in claims::ALL_CLAIMS {
        if !spec.kind.can_carry_value() {
            continue;
        }
        let level = spec.kind.level();
        assert_ne!(level, EvidenceLevel::Unknown, "{}", spec.subject);
        let fact = claims::graded(spec.subject, "tests/honesty.rs", "a value");
        assert_eq!(fact.level(), level, "{}", spec.subject);
        assert_eq!(
            fact.evidence_state(),
            EvidenceState::Derived,
            "{}",
            spec.subject
        );
        assert_eq!(fact.provenance().len(), 1, "{}", spec.subject);
        assert_eq!(fact.value(), Some(&"a value"), "{}", spec.subject);
        assert_eq!(fact.reason(), None, "{}", spec.subject);
    }
}

#[test]
fn no_layout_claim_is_stronger_than_observed() {
    // A layout can be measured on real records, so `Observed` is the ceiling.
    // Anything higher would claim a differential against the original binary
    // that this crate has not run.
    for spec in claims::ALL_CLAIMS {
        if spec.kind.level() > EvidenceLevel::Confirmed {
            assert!(
                spec.subject.contains("names") || spec.subject.contains("is_rgb"),
                "{}: only a name corroborated by a matching layout may exceed \
                 Observed, and this crate has run no binary differential",
                spec.subject
            );
        }
    }
    assert_eq!(
        claims::grade_of(claims::GLOBALS_LAYOUT),
        EvidenceLevel::Observed
    );
    assert_eq!(
        claims::grade_of(claims::CELL_LAYOUT),
        EvidenceLevel::Observed
    );
    assert_eq!(
        claims::grade_of(claims::SPAN_RULE_ALL_EXACT_FIT),
        EvidenceLevel::Observed
    );
}

#[test]
fn the_meaning_less_claims_are_exactly_the_non_findings() {
    for subject in [
        claims::GLOBALS_FIELD_208_MEANING,
        claims::AI_MOVEMENT_STYLE_MEANING,
        claims::AI_FOOD_MEANING,
        claims::DEAD_MARKER_FIELD,
        claims::ATTACHMENT_STRUCTURE_FIELD,
        claims::EFFECT_ID_REGISTRY,
        claims::CREATURE_ID_REGISTRY,
        claims::EFFECT_MAP_FIELD_MEANING,
        claims::LOOT_HEADER_PADDING,
        claims::ADVERT_FLOW_FIELD_TYPE,
        claims::REFERENCE_TYPE_WORD_ABSENT,
    ] {
        assert!(
            claims::grade_of(subject) == EvidenceLevel::Unknown,
            "{subject} must be a non-finding: its value is not established"
        );
        assert!(!claims::spec_of(subject).unwrap().kind.can_carry_value());
    }
}

#[test]
fn a_subject_that_does_not_apply_to_a_record_type_is_none_not_a_non_finding() {
    // Three states, kept apart: applicable-and-known, applicable-and-unknown,
    // and not-applicable-at-all.
    let globals = decode(spore_cellcontent::GLOBALS_TYPE, &globals_zeroed()).expect("decodes");
    assert!(
        globals.claim("no_such_subject").is_none(),
        "not applicable, and different from a non-finding"
    );
    let applicable = globals
        .claim(claims::GLOBALS_LAYOUT)
        .expect("globals carries its layout claim");
    assert!(applicable.is_available());
    assert_eq!(applicable.level(), EvidenceLevel::Observed);
    let non_finding = globals
        .claim(claims::GLOBALS_FIELD_208_MEANING)
        .expect("globals carries the field_208 non-finding");
    assert!(non_finding.is_unavailable());
    assert_eq!(non_finding.reason(), Some(claims::MEANING_NOT_ESTABLISHED));
}

#[test]
fn the_three_opaque_field_families_are_observed_but_meaningless() {
    // 1. cMarker's four dead fields.
    let populate = match decode(spore_cellcontent::POPULATE_TYPE, &populate(1, 0, 0)) {
        Ok(CellContent::Populate(value)) => value,
        other => panic!("{other:?}"),
    };
    let fact = populate.markers[0].dead_fields_meaning();
    assert!(fact.is_unavailable());
    assert_eq!(fact.reason(), Some(claims::DEAD_FIELD_OBSERVED_ZERO));
    assert_eq!(fact.level(), EvidenceLevel::Unknown);
    // ... while the VALUES are observed and carried.
    assert_eq!(populate.markers[0].dead_fields().len(), 4);
    assert!(populate.markers[0]
        .dead_fields()
        .iter()
        .all(|(_, v)| *v == 0));

    // 2. cSPAttachment's opaque slots.
    let structure = match decode(spore_cellcontent::STRUCTURE_TYPE, &structure(1, 0)) {
        Ok(CellContent::Structure(value)) => value,
        other => panic!("{other:?}"),
    };
    let attachment = structure.attachments[0];
    assert_eq!(
        attachment.structure_meaning().reason(),
        Some(claims::DEAD_FIELD_OBSERVED_ZERO)
    );
    assert_eq!(
        attachment.effect_id_meaning().reason(),
        Some(claims::NO_EFFECT_REGISTRY)
    );
    assert_eq!(attachment.structure, 0, "observed");
    assert_eq!(attachment.effect_id, 100, "observed");

    // 3. The lootTable header's three pad bytes.
    let loot = match decode(spore_cellcontent::LOOT_TABLE_TYPE, &loot_table(1, 0, 0)) {
        Ok(CellContent::LootTable(value)) => value,
        other => panic!("{other:?}"),
    };
    assert_eq!(loot.header_padding, [0, 0, 0], "observed");
    let record = CellContentRecord::new(
        ResourceKey::new(spore_cellcontent::LOOT_TABLE_TYPE, 0, 1),
        CellContent::LootTable(loot),
    );
    let fact = record
        .claim(claims::LOOT_HEADER_PADDING)
        .expect("a loot table carries the padding non-finding");
    assert!(fact.is_unavailable());
    assert_eq!(fact.reason(), Some(claims::PADDING_NOT_INTERPRETED));

    // 4. The five positional effect-map fields.
    let effect = match decode(spore_cellcontent::EFFECT_MAP_TYPE, &effect_map(1)) {
        Ok(CellContent::EffectMap(value)) => value,
        other => panic!("{other:?}"),
    };
    assert_eq!(
        effect.entries[0].positional_meaning().reason(),
        Some(claims::MEANING_NOT_ESTABLISHED)
    );
    assert_eq!(
        effect.entries[0].floats().len(),
        4,
        "the positions are known"
    );
}

#[test]
fn the_ai_field_meanings_are_non_findings_while_the_layout_is_confirmed() {
    let cell = match decode(spore_cellcontent::CELL_TYPE, &cell(0, "x", 0, 0)) {
        Ok(CellContent::Cell(value)) => value,
        other => panic!("{other:?}"),
    };
    assert_eq!(cell.ai.kind, 0x1000, "observed");
    assert!(cell.ai.movement_style_meaning().is_unavailable());
    assert!(cell.ai.food_meaning().is_unavailable());
    assert_eq!(
        cell.claim(claims::AI_MOVEMENT_STYLE_MEANING)
            .expect("applicable")
            .reason(),
        Some(claims::MEANING_NOT_ESTABLISHED)
    );
    // The name encoding is OBSERVED; the surrogate-pairing rule is INFERRED,
    // because no real record exercises it.
    assert_eq!(
        cell.claim(claims::CELL_NAME_ENCODING)
            .expect("applicable")
            .level(),
        EvidenceLevel::Observed
    );
    assert_eq!(
        cell.claim(claims::AI_SURROGATE_PAIRING)
            .expect("applicable")
            .level(),
        EvidenceLevel::Inferred,
        "all 70 observed names are ASCII, so the pairing rule is untested by data"
    );
}

#[test]
fn the_reference_type_word_absence_is_a_non_finding_about_the_format() {
    let fact = claims::non_finding(claims::REFERENCE_TYPE_WORD_ABSENT);
    assert_eq!(fact.reason(), Some(claims::NO_TYPE_WORD_IN_RECORD));
    // The advect flow-field type is graded the same way: the record stores no
    // type word of its own.
    assert_eq!(
        claims::non_finding(claims::ADVERT_FLOW_FIELD_TYPE).reason(),
        Some(claims::NO_TYPE_WORD_IN_RECORD)
    );
    assert_eq!(
        claims::grade_of(claims::ADVERT_FLOW_FIELD_TYPE),
        EvidenceLevel::Unknown
    );
}

#[test]
fn the_advect_float_override_is_graded_observed_not_inferred() {
    // The file disagrees with the SDK header and the file is what is read.
    assert_eq!(
        claims::grade_of(claims::ADVECT_FLOAT_OVERRIDES_SDK_INT),
        EvidenceLevel::Observed
    );
    assert_eq!(
        claims::grade_of(claims::WORLD_POPULATE_RESOLUTION_UNMEASURED),
        EvidenceLevel::Inferred
    );
}

#[test]
fn the_two_sdk_corroborated_names_are_the_only_confirmed_claims() {
    let confirmed: Vec<&str> = claims::ALL_CLAIMS
        .iter()
        .filter(|spec| spec.kind.level() == EvidenceLevel::Confirmed)
        .map(|spec| spec.subject)
        .collect();
    assert_eq!(
        confirmed,
        vec![claims::GLOBALS_FIELD_NAMES, claims::BACKGROUND_RAMP_IS_RGB,],
        "a new Confirmed claim needs a name corroborated by a matching layout"
    );
}

#[test]
fn the_geometric_ladder_claim_is_observed_because_the_values_are() {
    assert_eq!(
        claims::grade_of(claims::BACKGROUND_LADDER_IS_GEOMETRIC),
        EvidenceLevel::Observed
    );
    let ramp = match decode(spore_cellcontent::BACKGROUND_MAP_TYPE, &background_map(6)) {
        Ok(CellContent::BackgroundMap(value)) => value,
        other => panic!("{other:?}"),
    };
    // The synthetic ramp is geometric by construction: 3.333^i.
    for pair in ramp.entries.windows(2) {
        let ratio = pair[1].field_c / pair[0].field_c;
        assert!(
            (ratio - 3.333).abs() < 0.01,
            "the synthetic ladder is not geometric: {ratio}"
        );
    }
}

#[test]
fn a_record_with_no_entries_still_reports_its_applicable_non_findings() {
    // An empty random-creature record has no `creatureID` to ask about, so the
    // claim is the same non-finding rather than a fabricated value.
    let empty = match decode(spore_cellcontent::RANDOM_CREATURE_TYPE, &random_creature(0)) {
        Ok(CellContent::RandomCreature(value)) => value,
        other => panic!("{other:?}"),
    };
    let record = CellContentRecord::new(
        ResourceKey::new(spore_cellcontent::RANDOM_CREATURE_TYPE, 0, 1),
        CellContent::RandomCreature(empty),
    );
    let fact = record
        .claim(claims::CREATURE_ID_REGISTRY)
        .expect("applicable to a random-creature record");
    assert!(fact.is_unavailable());
    assert_eq!(fact.reason(), Some(claims::NO_CREATURE_REGISTRY));
    let layout = record
        .claim(claims::RANDOM_CREATURE_LAYOUT)
        .expect("applicable");
    assert!(layout.is_available());
    assert_eq!(layout.level(), EvidenceLevel::Observed);

    // And the graded helper agrees with the documented grade for every declared
    // subject, which is the property that stops a grade from drifting away from
    // its written basis.
    for spec in claims::ALL_CLAIMS {
        assert_eq!(claims::grade_of(spec.subject), spec.kind.level());
        assert_eq!(claims::spec_of(spec.subject).unwrap().subject, spec.subject);
    }
}
