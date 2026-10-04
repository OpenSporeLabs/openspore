//! The invariants this crate exists to protect.
//!
//! Two of them, both testable and both easy to lose in an edit:
//!
//! 1. **An unknown material id is a non-finding.** `Fact::unavailable` carries no
//!    provenance and is `UNKNOWN`/`MISSING` — never a default colour, never a
//!    name derived from the bits.
//! 2. **No sampler role is claimed.** Every binding is `Unresolved`, and not one
//!    claim anywhere in the crate mentions a texture's purpose.

mod support;

use spore_core::evidence::{EvidenceLevel, EvidenceState, Fact};
use spore_gmdl::GmdlTextureRef;
use spore_material::{
    claims, material_name, model_materials, resolve_model_record, resolve_model_textures,
    resolve_texture, BindingScope, MaterialModel, SamplerRole,
};
use spore_texture::{DXT5_FOURCC, RASTER_TYPE};
use support::*;

/// Every material of the documented asset.
fn documented_materials() -> Vec<MaterialModel> {
    let model = spore_gmdl::parse(&documented_gmdl()).expect("synthetic gmdl parses");
    model_materials(&model)
}

#[test]
fn an_unknown_material_id_is_a_non_finding_with_no_provenance_and_unknown_level() {
    let materials = documented_materials();
    assert_eq!(materials.len(), 1);
    let material = &materials[0];
    assert_eq!(material.material_id, DOCUMENTED_MATERIAL_ID);

    // The invariant, asserted directly on the Fact: unavailable, no provenance,
    // UNKNOWN, MISSING, no value.
    for subject in [claims::MATERIAL_NAME, claims::MATERIAL_ID_MEANING] {
        let claim = material
            .claim(subject)
            .unwrap_or_else(|| panic!("{subject}"));
        let fact: &Fact<&'static str> = &claim.fact;
        assert!(fact.is_unavailable(), "{subject} must be a non-finding");
        assert!(!fact.is_available(), "{subject}");
        assert_eq!(fact.level(), EvidenceLevel::Unknown, "{subject}");
        assert_eq!(fact.evidence_state(), EvidenceState::Missing, "{subject}");
        assert!(
            fact.provenance().is_empty(),
            "{subject}: a non-finding has no provenance to repeat"
        );
        assert_eq!(fact.value(), None, "{subject}");
        assert_eq!(fact.clone().into_value(), None, "{subject}");
        assert_eq!(
            fact.reason(),
            Some("no_material_registry"),
            "{subject}: the reason code is closed and says why"
        );
    }

    // ...and the reason code is the crate's own constant, not a literal typed
    // twice in two places.
    assert_eq!(claims::NO_MATERIAL_REGISTRY, "no_material_registry");
    assert_eq!(
        claims::grade_of(claims::MATERIAL_NAME),
        EvidenceLevel::Unknown
    );
}

#[test]
fn no_material_id_is_ever_given_a_name_or_a_default() {
    // Every id, including the documented one. A registry would change this
    // function; until then it must answer None for everything.
    for id in [DOCUMENTED_MATERIAL_ID, 0, 1, u32::MAX, 0xDEAD_BEEF] {
        assert_eq!(material_name(id), None, "0x{id:08x}");
    }
    assert!(
        documented_materials()
            .iter()
            .all(|material| material.name.is_none()),
        "a name here would be fabricated from the id"
    );
    // And the field is not filled with a colour or a sentinel string either: it
    // is an Option that is None.
    for material in documented_materials() {
        assert!(material.name.is_none());
    }
}

#[test]
fn the_material_id_is_still_carried_verbatim() {
    // Not knowing what an id means is not the same as losing it. The observation
    // and the meaning are recorded as two separate subjects.
    let materials = documented_materials();
    let observed = materials[0]
        .claim(claims::MATERIAL_ID_READ_VERBATIM)
        .expect("the observation is recorded");
    assert!(observed.fact.is_available());
    assert_eq!(observed.fact.level(), EvidenceLevel::Observed);
    assert_eq!(observed.fact.provenance().len(), 1);
    assert_eq!(materials[0].material_id, 0x407D_FDDB);
}

#[test]
fn every_sampler_role_is_unresolved_and_no_claim_names_a_texture_purpose() {
    let materials = documented_materials();
    let material = &materials[0];
    assert_eq!(material.bindings.len(), 3);
    for binding in &material.bindings {
        assert_eq!(
            binding.role,
            SamplerRole::Unresolved,
            "no entry of a texture set carries a decoded role"
        );
        assert_eq!(
            binding.reference,
            documented_texture_refs()[material.bindings.iter().position(|b| b == binding).unwrap()]
        );
    }

    // The role is a non-finding, with its own reason code.
    let role = material.claim(claims::SAMPLER_ROLE).expect("subject");
    assert!(role.fact.is_unavailable());
    assert_eq!(role.fact.level(), EvidenceLevel::Unknown);
    assert_eq!(
        role.fact.reason(),
        Some(claims::TEXTURE_ENTRY_HEADER_NOT_DECODED)
    );
    assert!(role.fact.provenance().is_empty());

    // The binding scope is stated in the type, and the ownership question is a
    // non-finding rather than a guess.
    assert_eq!(material.binding_scope, BindingScope::WholeModel);
    let ownership = material
        .claim(claims::MATERIAL_TEXTURE_OWNERSHIP)
        .expect("subject");
    assert!(ownership.fact.is_unavailable());
    assert_eq!(
        ownership.fact.reason(),
        Some(claims::MATERIAL_BLOCKS_NOT_ASSOCIATED)
    );
}

#[test]
fn no_claim_anywhere_names_a_texture_purpose() {
    // A crate-wide sweep, not a check of one struct: a "diffuse" appearing in a
    // doc comment, a subject or a claim value is the failure this test exists to
    // catch. Only the honest words are allowed.
    const FORBIDDEN: [&str; 6] = [
        "diffuse",
        "specular",
        "normalmap",
        "normal_map",
        "bump",
        "emissive",
    ];

    // Every graded claim value in the crate's own table.
    for spec in claims::ALL_CLAIMS {
        let haystack = format!("{} {} {:?}", spec.subject, spec.basis, spec.kind);
        for word in FORBIDDEN {
            assert!(
                !haystack.to_ascii_lowercase().contains(word),
                "{}: the claims table must not name a purpose ({word})",
                spec.subject
            );
        }
    }

    // Every claim actually recorded for a resolved texture and a material.
    let store = store_over(&[(
        raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        raster_record(8, 8, 2, DXT5_FOURCC, 2),
    )]);
    let resolved = resolve_texture(
        &store,
        GmdlTextureRef {
            instance_id: DOCUMENTED_INSTANCE_ID,
            group_id: 0x4063_2900,
        },
        RASTER_TYPE,
    )
    .unwrap();
    let mut recorded: Vec<String> = resolved
        .claims
        .iter()
        .map(|claim| format!("{} {:?}", claim.subject, claim.fact.value()))
        .collect();
    for material in documented_materials() {
        recorded.extend(
            material
                .claims
                .iter()
                .map(|claim| format!("{} {:?}", claim.subject, claim.fact.value())),
        );
        for binding in &material.bindings {
            recorded.push(format!("{:?}", binding.role));
        }
    }
    for text in &recorded {
        let lowered = text.to_ascii_lowercase();
        for word in FORBIDDEN {
            assert!(
                !lowered.contains(word),
                "a recorded claim names a texture purpose ({word}): {text}"
            );
        }
    }

    // The words the crate does use, to show the sweep above is not vacuous.
    let combined = recorded.join(" ").to_ascii_lowercase();
    assert!(combined.contains("sampler"));
    assert!(combined.contains("texture"));
}

#[test]
fn the_unknowns_view_lists_only_non_findings() {
    let material = &documented_materials()[0];
    let unknowns: Vec<&str> = material
        .unknowns()
        .map(|claim| claim.subject.as_str())
        .collect();
    assert!(unknowns.contains(&claims::MATERIAL_NAME));
    assert!(unknowns.contains(&claims::SAMPLER_ROLE));
    assert!(
        !unknowns.contains(&claims::MATERIAL_ID_READ_VERBATIM),
        "an observation is not an unknown"
    );
    assert_eq!(
        unknowns.len(),
        material.unknowns().count(),
        "the view and the iterator agree"
    );
}

#[test]
fn a_model_with_no_materials_states_none_rather_than_defaulting() {
    // `meshCount` 0: no material ids, no texture references. Three absences, and
    // none of them may become a default material or a fake binding.
    let model = spore_gmdl::parse(&meshless_gmdl()).expect("a mesh-less record parses");
    assert!(model.material_ids.is_empty());
    assert!(model.texture_refs.is_empty());

    assert!(
        model_materials(&model).is_empty(),
        "no material ids means no materials, which is an absence and not an error"
    );

    let store = store_over(&[(documented_model_key(), meshless_gmdl())]);
    let results = resolve_model_textures(&store, &model, RASTER_TYPE);
    assert!(
        results.is_empty(),
        "an empty batch is empty, not a single failure"
    );

    let resolved = resolve_model_record(&store, &documented_model_key(), RASTER_TYPE).unwrap();
    assert!(resolved.textures.is_empty());
    assert!(resolved.materials.is_empty());
}

#[test]
fn the_claims_table_declares_no_subject_this_crate_cannot_record() {
    // Every declared subject is either recorded by a resolution or recorded by a
    // material; a subject nobody writes would be a documented claim with no
    // producer, which is its own kind of dishonesty.
    let store = store_over(&[(
        raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        raster_record(8, 8, 2, DXT5_FOURCC, 2),
    )]);
    let resolved = resolve_texture(&store, documented_texture_refs()[0], RASTER_TYPE).unwrap();
    let mut recorded: Vec<String> = resolved.claims.iter().map(|c| c.subject.clone()).collect();
    for material in documented_materials() {
        recorded.extend(material.claims.iter().map(|c| c.subject.clone()));
    }

    for spec in claims::ALL_CLAIMS {
        assert!(
            recorded.iter().any(|subject| subject == spec.subject),
            "{} is documented but nothing records it",
            spec.subject
        );
    }
    for subject in &recorded {
        assert!(
            claims::spec_of(subject).is_some(),
            "{subject} is recorded but not documented"
        );
    }
    // No subject is recorded twice in one place.
    for material in documented_materials() {
        for (index, claim) in material.claims.iter().enumerate() {
            for other in material.claims.iter().skip(index + 1) {
                assert_ne!(claim.subject, other.subject, "duplicate subject");
            }
        }
    }
}
