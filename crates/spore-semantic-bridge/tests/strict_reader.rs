//! The strict reader, exercised over synthetic JSON written for this suite.
//!
//! Every refusal demonstrated here is one the format's own contract asks for.
//! The committed artifact cannot demonstrate any of them: it is valid, and a test
//! that needed a corrupted file in order to prove the reader is strict would be a
//! test that only runs on a broken checkout.

mod support;

use spore_semantic_bridge::{
    BridgeError, Canonicalization, EvidenceLevel, RuntimeGate, Snapshot, TriState,
};
use support::{fixture, metadata_line, one, record, snapshot_file, TempFile};

// The needles are the exact substrings of the minimal record that each test
// replaces. Naming them keeps the tests readable and keeps every `{}` literal
// out of a `format!`, where a doubled brace would silently mean something else.
const ABI_UNAVAILABLE: &str = concat!(
    r#""abi":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
    r#""reason":"no_evidence_pack"}"#,
);
const VTABLE_UNAVAILABLE: &str = concat!(
    r#""vtable":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
    r#""reason":"no_vtable_membership"}"#,
);
const RECON_UNAVAILABLE: &str = concat!(
    r#""reconstruction":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
    r#""reason":"no_reconstruction_package"}"#,
);
const GLOBALS_UNAVAILABLE: &str = concat!(
    r#""globals":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
    r#""reason":"no_global_references"}"#,
);
const SEMANTICS_UNAVAILABLE: &str = concat!(
    r#""semantics":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
    r#""reason":"no_semantic_record"}"#,
);
const GRAPH_EMPTY: &str = concat!(
    r#""graph":{"caller_count":0,"callee_count":0,"vtable_reference_count":0,"#,
    r#""data_reference_count":0}"#,
);

const ABI_THISCALL: &str = concat!(
    r#""abi":{"state":"available","evidence_level":"INFERRED","evidence_state":"DERIVED","#,
    r#""provenance":["reconstruction/knowledge/index.json","GhidraMCP /disassemble_function"],"#,
    r#""value":{"origin":"abi_inference","schema":"openspore-abi-inference-1","#,
    r#""convention":"__thiscall","convention_confidence":"INFERRED","verdict":"ABI_INFERRED","#,
    r#""completeness":"CORE_RESOLVED","#,
    r#""receiver":{"present":"true","register":"ECX","confidence":"INFERRED","shape":"R-ALIAS","#,
    r#""provenance":null,"bounds_only":true,"max_offset":16,"written_through":3},"#,
    r#""cleanup":null,"return":null,"sret":null,"variadic":"UNKNOWN","#,
    r#""stack_argument_slots":4,"seh_or_cookie_frame":false,"declared":null}}"#,
);

const ABI_UNDETERMINED: &str = concat!(
    r#""abi":{"state":"available","evidence_level":"UNKNOWN","evidence_state":"DERIVED","#,
    r#""provenance":["reconstruction/evidence/00401000/evidence.json"],"#,
    r#""value":{"origin":"abi_inference","schema":"openspore-abi-inference-1","convention":null,"#,
    r#""convention_confidence":"UNKNOWN","verdict":"ABI_UNKNOWN","completeness":null,"#,
    r#""receiver":{"present":"null","register":null,"confidence":"UNKNOWN","shape":null,"#,
    r#""provenance":null,"bounds_only":null,"max_offset":null,"written_through":null},"#,
    r#""cleanup":null,"return":null,"sret":null,"variadic":null,"stack_argument_slots":null,"#,
    r#""seh_or_cookie_frame":null,"declared":null}}"#,
);

const VTABLE_ONE_MEMBERSHIP: &str = concat!(
    r#""vtable":{"state":"available","evidence_level":"INFERRED","evidence_state":"DERIVED","#,
    r#""provenance":["reconstruction/knowledge/index.json"],"#,
    r#""value":{"memberships":[{"table_va":"0x013f57f8","slot":8,"slot_width":12}],"#,
    r#""abi_attributed":null,"triage_addresses":[],"triage_family":null}}"#,
);

const SEMANTICS_WITH_QUESTIONS: &str = concat!(
    r#""semantics":{"state":"available","evidence_level":"INFERRED","evidence_state":"PERSISTED","#,
    r#""provenance":["reconstruction/knowledge/index.json"],"#,
    r#""value":{"classification":null,"semantic_status":"static_reconstruction_runtime_gated","#,
    r#""name":null,"subsystem":null,"triangulation_status":null,"downstream_unlock_count":null,"#,
    r#""source":null,"confidence":{},"evidence":[],"notes":[],"#,
    r#""unresolved_questions":["is the helper a pure move?"],"semantic_family":null,"#,
    r#""source_workers":[]}}"#,
);

/// A reconstruction record whose runtime gate is `gated`.
fn recon_with_gate(gated: bool) -> String {
    format!(
        concat!(
            r#""reconstruction":{{"state":"available","evidence_level":"INFERRED","#,
            r#""evidence_state":"PERSISTED","#,
            r#""provenance":["reconstruction/knowledge/index.json"],"#,
            r#""value":{{"package":"WAVE6-PRESENTATION","status":"reconstructed","#,
            r#""review_status":"approved","integration_status":"integrated","reconstructed":true,"#,
            r#""blocked":false,"promoted":"false","promotion_schema":null,"#,
            r#""promotion_supersedes":null,"static_status":null,"#,
            r#""generated_source":["src/x.cpp"],"handoffs":[],"metadata":[],"#,
            r#""runtime_gated":{gated},"runtime_validated":0,"runtime_blocking_reason":null,"#,
            r#""validation":null}}}}"#
        ),
        gated = gated
    )
}

const RECON_PROMOTED: &str = concat!(
    r#""reconstruction":{"state":"available","evidence_level":"SUPPORTED","#,
    r#""evidence_state":"PERSISTED","provenance":["reconstruction/knowledge/index.json"],"#,
    r#""value":{"package":"PKG-1","status":"candidate","review_status":null,"#,
    r#""integration_status":null,"reconstructed":false,"blocked":false,"promoted":"true","#,
    r#""promotion_schema":"openspore-promotion-record-1","promotion_supersedes":null,"#,
    r#""static_status":"PASS","generated_source":[],"handoffs":[],"metadata":[],"#,
    r#""runtime_gated":false,"runtime_validated":null,"runtime_blocking_reason":null,"#,
    r#""validation":null}}"#,
);

const RECON_WITH_VALIDATION: &str = concat!(
    r#""reconstruction":{"state":"available","evidence_level":"OBSERVED","#,
    r#""evidence_state":"PERSISTED","provenance":["reconstruction/knowledge/index.json"],"#,
    r#""value":{"package":null,"status":"candidate","review_status":null,"#,
    r#""integration_status":null,"reconstructed":false,"blocked":false,"promoted":"false","#,
    r#""promotion_schema":null,"promotion_supersedes":null,"static_status":null,"#,
    r#""generated_source":[],"handoffs":[],"metadata":[],"runtime_gated":false,"#,
    r#""runtime_validated":null,"runtime_blocking_reason":null,"#,
    r#""validation":{"schema":"openspore-structural-validation-1","#,
    r#""coverage":{"ABI":{"status":"PASS","coverage":"partial","detail":"stated","evidence":[]},"#,
    r#""A DIMENSION FROM A FUTURE VERSION":{"status":"WARN","coverage":"partial","#,
    r#""detail":"d","evidence":[]}},"#,
    r#""runtime":{"status":"NOT_AVAILABLE","coverage":"none","detail":"n","evidence":[]},"#,
    r#""static_rollup":{"pass":2,"ratio":0.5}}}}"#,
);

/// Parses one record line through the whole reader: write it as the only record
/// of a snapshot, open the snapshot, look the record up.
///
/// The fixture is held for the duration so the file outlives the snapshot, which
/// is the lifetime rule a real caller has.
fn only_record(body: &str) -> Result<spore_semantic_bridge::Passport, BridgeError> {
    let fixture = one(body);
    fixture.opened()?.lookup(0x0040_1000)
}

fn with(needle: &str, replacement: &str) -> String {
    record("0x00401000", "0x00001000", 10).replace(needle, replacement)
}

// ---------------------------------------------------------------------------
// Envelope: present and unavailable
// ---------------------------------------------------------------------------

#[test]
fn an_available_group_carries_its_grade_and_provenance() {
    let passport = only_record(&with(ABI_UNAVAILABLE, ABI_THISCALL)).expect("valid");
    let abi = passport.abi();
    assert!(abi.is_available());
    assert_eq!(abi.level(), EvidenceLevel::Inferred);
    assert_eq!(
        abi.evidence_state(),
        spore_semantic_bridge::EvidenceState::Derived
    );
    assert_eq!(passport.convention().value().copied(), Some("__thiscall"));
    assert_eq!(passport.convention().level(), EvidenceLevel::Inferred);
    assert_eq!(
        passport.receiver_present(),
        Some(TriState::True),
        "a \"true\" receiver is not undetermined"
    );
    assert_eq!(abi.provenance().len(), 2);
    assert_eq!(
        abi.provenance()[1].source_class,
        spore_semantic_bridge::SourceClass::Ghidra,
        "a Ghidra reference is a live Ghidra observation"
    );
    assert_eq!(
        abi.provenance()[0].source_class,
        spore_semantic_bridge::SourceClass::CommittedArtifact
    );
    assert_eq!(
        abi.provenance()[1].reference,
        "GhidraMCP /disassemble_function"
    );
}

#[test]
fn an_unavailable_group_is_a_first_class_answer_not_a_default() {
    let passport = only_record(&record("0x00401000", "0x00001000", 10)).expect("valid");
    let abi = passport.abi();
    assert!(abi.is_unavailable());
    assert_eq!(abi.reason(), Some("no_evidence_pack"));
    assert_eq!(abi.level(), EvidenceLevel::Unknown);
    assert_eq!(
        abi.evidence_state(),
        spore_semantic_bridge::EvidenceState::Missing
    );
    assert!(abi.provenance().is_empty());
    assert_eq!(abi.value(), None);
    assert!(!passport.convention().is_available());
    assert_eq!(passport.convention().reason(), Some("no_evidence_pack"));
    assert!(!passport.vtable_memberships().is_available());
    assert_eq!(
        passport.vtable_memberships().reason(),
        Some("no_vtable_membership")
    );
    assert!(!passport.unresolved_questions().is_available());
    assert!(!passport.reconstruction().is_available());
    assert!(!passport.promoted().is_available());
    assert!(passport.globals().is_unavailable());
    assert!(passport.types().is_unavailable());
}

#[test]
fn a_convention_of_null_is_undetermined_not_absent() {
    let passport = only_record(&with(ABI_UNAVAILABLE, ABI_UNDETERMINED)).expect("valid");
    assert!(
        passport.abi().is_available(),
        "the ABI record exists; only its convention is undetermined"
    );
    assert_eq!(
        passport.convention().reason(),
        Some(spore_semantic_bridge::REASON_CONVENTION_UNDETERMINED)
    );
    assert_ne!(
        passport.convention().reason(),
        passport.abi().reason(),
        "an undetermined convention is a different statement from no ABI record"
    );
    assert_eq!(
        passport.receiver_present(),
        Some(TriState::Undetermined),
        "\"null\" is a load-bearing known-unknown, not false"
    );
    assert_ne!(passport.receiver_present(), Some(TriState::False));
}

#[test]
fn an_available_question_list_is_not_the_same_as_no_semantic_record() {
    let body = with(SEMANTICS_UNAVAILABLE, SEMANTICS_WITH_QUESTIONS);
    let with_questions = only_record(&body).expect("valid");
    let questions = with_questions.unresolved_questions();
    assert!(questions.is_available());
    assert_eq!(
        questions.value().expect("present"),
        &["is the helper a pure move?"]
    );

    let without = only_record(&record("0x00401000", "0x00001000", 10)).expect("valid");
    let absent = without.unresolved_questions();
    assert!(absent.is_unavailable());
    assert_eq!(absent.reason(), Some("no_semantic_record"));
    assert!(
        absent.value().is_none(),
        "an empty slice here would claim there are no open questions, which is a different \
         statement from having no semantic record"
    );
}

// ---------------------------------------------------------------------------
// Envelope: the combinations the contract forbids
// ---------------------------------------------------------------------------

#[test]
fn an_available_group_without_provenance_is_refused() {
    let replacement = concat!(
        r#""abi":{"state":"available","evidence_level":"INFERRED","evidence_state":"DERIVED","#,
        r#""value":{"origin":"abi_inference","schema":"openspore-abi-inference-1","#,
        r#""convention":null,"convention_confidence":"UNKNOWN","verdict":null,"#,
        r#""completeness":null,"receiver":null,"cleanup":null,"return":null,"sret":null,"#,
        r#""variadic":null,"stack_argument_slots":null,"seh_or_cookie_frame":null,"#,
        r#""declared":null}}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.provenance"), "{detail}");
            assert!(detail.contains("no provenance is listed"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_available_group_without_a_value_is_refused() {
    let replacement = concat!(
        r#""abi":{"state":"available","evidence_level":"INFERRED","evidence_state":"DERIVED","#,
        r#""provenance":["reconstruction/knowledge/index.json"]}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.value"), "{detail}");
            assert!(detail.contains("claiming nothing at all"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unavailable_group_that_carries_a_value_is_refused() {
    let replacement = concat!(
        r#""abi":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
        r#""reason":"no_evidence_pack","value":[]}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.value"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unavailable_group_without_a_reason_is_refused() {
    let replacement =
        r#""abi":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING"}"#;
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.reason"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unavailable_group_that_is_not_graded_unknown_is_refused() {
    let replacement = concat!(
        r#""abi":{"state":"unavailable","evidence_level":"INFERRED","evidence_state":"MISSING","#,
        r#""reason":"no_evidence_pack"}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.evidence_level"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unavailable_group_that_claims_provenance_is_refused() {
    let replacement = concat!(
        r#""abi":{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
        r#""provenance":["reconstruction/knowledge/index.json"],"reason":"no_evidence_pack"}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.provenance"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_off_scale_grade_is_refused_rather_than_degraded() {
    let replacement = ABI_THISCALL.replace(
        r#""INFERRED","evidence_state":"DERIVED""#,
        r#""PRETTY_SURE","evidence_state":"DERIVED""#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, &replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("PRETTY_SURE"), "{detail}");
            assert!(detail.contains("not a rung"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unknown_state_is_refused_because_the_vocabulary_is_closed() {
    let replacement = concat!(
        r#""abi":{"state":"maybe","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
        r#""reason":"x"}"#,
    );
    let error = only_record(&with(ABI_UNAVAILABLE, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.state"), "{detail}");
            assert!(detail.contains("closed"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn a_record_carrying_a_non_static_source_class_is_refused() {
    let error =
        only_record(&record_with_provenance("live", "runtime")).expect_err("must be refused");
    assert!(
        matches!(error, BridgeError::UnsupportedSchema { .. }),
        "{error}"
    );
}

// ---------------------------------------------------------------------------
// The four refusals every strict reader owes
// ---------------------------------------------------------------------------

#[test]
fn an_unknown_field_is_refused_by_its_dotted_path() {
    let body = record("0x00401000", "0x00001000", 10).replace(
        r#""section":".text""#,
        r#""section":".text","section_typo":1"#,
    );
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { line, detail, .. } => {
            assert_eq!(line, 2, "the refusal names the line");
            assert!(detail.contains("identity.section_typo"), "{detail}");
            assert!(detail.contains("unknown field"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unknown_field_deep_inside_a_fact_group_is_refused_too() {
    // Validation is total: a field this crate does not retain is still a field
    // this build must recognise, or its meaning may have moved.
    let body = record("0x00401000", "0x00001000", 10).replace(
        r#""classification":{"category":"ENGINE_IMPLEMENTATION""#,
        r#""classification":{"mystery":1,"category":"ENGINE_IMPLEMENTATION""#,
    );
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("classification.mystery"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn an_unknown_field_inside_a_discarded_block_is_refused() {
    // `abi.value.declared` is validated and then thrown away. Discarding it must
    // not mean ignoring it.
    let body = with(ABI_UNAVAILABLE, ABI_THISCALL)
        .replace(r#""declared":null"#, r#""declared":{"surprise":1}"#);
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("abi.value.declared.surprise"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn a_missing_required_field_is_refused_rather_than_defaulted() {
    let body = record("0x00401000", "0x00001000", 10).replace(r#","is_thunk":false"#, "");
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("identity.is_thunk"), "{detail}");
            assert!(detail.contains("required field is absent"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn a_repeated_key_is_refused_rather_than_let_the_last_one_win() {
    let body =
        record("0x00401000", "0x00001000", 10).replace(r#""size":10"#, r#""size":10,"size":99"#);
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("identity.size"), "{detail}");
            assert!(detail.contains("more than once"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn a_non_object_where_an_object_is_required_is_refused() {
    for (needle, replacement) in [
        (GRAPH_EMPTY, r#""graph":7"#),
        (r#""names":{"#, r#""names":["#),
        (ABI_UNAVAILABLE, r#""abi":[]"#),
        (r#""evidence":{"pack":null"#, r#""evidence":null"#),
    ] {
        let error = only_record(&with(needle, replacement)).expect_err("must be refused");
        assert!(
            matches!(error, BridgeError::UnsupportedSchema { .. }),
            "{replacement}: {error}"
        );
    }
}

#[test]
fn a_null_where_a_value_is_required_is_refused() {
    for (field, needle) in [
        ("identity.canonical_va", r#""canonical_va":"0x00401000""#),
        ("names.ghidra_name", r#""ghidra_name":"FUN_00401000""#),
        (
            "classification.category",
            r#""category":"ENGINE_IMPLEMENTATION""#,
        ),
    ] {
        let key = needle
            .split_once(":")
            .map(|(key, _)| key.trim_matches('"'))
            .unwrap_or_default();
        let body =
            record("0x00401000", "0x00001000", 10).replace(needle, &format!("\"{key}\":null"));
        let error = only_record(&body).expect_err("must be refused");
        match error {
            BridgeError::UnsupportedSchema { detail, .. } => {
                assert!(detail.contains(field), "{field} not named in {detail}");
            }
            other => panic!("expected a schema refusal for {field}, got {other}"),
        }
    }
}

#[test]
fn a_nullable_required_field_is_accepted_because_the_format_writes_it_as_null() {
    // The mirror of the previous test, and the reason `required` and
    // "nullable" are separate facts in the schema: `identity_resolution` is
    // always written and is legitimately `null` on 58 754 of 58 757 records.
    let passport = only_record(&record("0x00401000", "0x00001000", 10)).expect("valid");
    assert_eq!(passport.recorded_identity_resolution(), None);
    assert!(passport.identity_refuted().is_none());
    assert!(passport.classification().cluster.is_none());
}

// ---------------------------------------------------------------------------
// Canonical VA spelling
// ---------------------------------------------------------------------------

fn record_with_va(spelling: &str) -> String {
    record("0x00401000", "0x00001000", 10).replace(
        r#""canonical_va":"0x00401000""#,
        &format!(r#""canonical_va":"{spelling}""#),
    )
}

#[test]
fn only_lowercase_0x_and_eight_digits_is_accepted_as_a_canonical_va() {
    let passport = only_record(&record_with_va("0x00401000")).expect("accepted");
    assert_eq!(passport.canonical_va(), 0x0040_1000);
    assert_eq!(passport.canonical_va_text(), "0x00401000");
    assert_eq!(passport.identity().rva, 0x0000_1000);

    for spelling in [
        "925050",
        "00925050",
        "0X00925050",
        "0x925050",
        "0x0040100",
        "0x004010000",
        "0x0040100g",
    ] {
        let error = only_record(&record_with_va(spelling)).expect_err("must be refused");
        match error {
            BridgeError::Corrupt { detail, .. } => {
                assert!(
                    detail.contains("identity.canonical_va"),
                    "{spelling}: {detail}"
                );
                assert!(detail.contains("canonical"), "{spelling}: {detail}");
            }
            other => panic!("{spelling}: expected corruption, got {other}"),
        }
    }
}

#[test]
fn a_non_canonical_va_inside_a_list_is_refused() {
    let replacement = concat!(
        r#""graph":{"caller_count":1,"callee_count":0,"callers":["0X00402000"],"#,
        r#""vtable_reference_count":0,"data_reference_count":0}"#,
    );
    let error = only_record(&with(GRAPH_EMPTY, replacement)).expect_err("must be refused");
    match error {
        BridgeError::Corrupt { detail, .. } => {
            assert!(detail.contains("graph.callers[0]"), "{detail}");
        }
        other => panic!("expected corruption, got {other}"),
    }
}

#[test]
fn a_caller_count_that_disagrees_with_its_list_is_refused() {
    // Not an invariant the format states, but without it a count of 0 beside a
    // non-empty list would read as "no callers".
    let replacement = concat!(
        r#""graph":{"caller_count":3,"callee_count":0,"callers":["0x00402000"],"#,
        r#""vtable_reference_count":0,"data_reference_count":0}"#,
    );
    let error = only_record(&with(GRAPH_EMPTY, replacement)).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("graph.caller_count"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

// ---------------------------------------------------------------------------
// Document-level provenance: the four static classes, and the refusal
// ---------------------------------------------------------------------------

fn record_with_provenance(mode: &str, class: &str) -> String {
    let head = record("0x00401000", "0x00001000", 10);
    let cut = head
        .rfind(",\"evidence\":")
        .expect("the evidence block is present");
    // `head[..cut]` stops just before the `,"evidence":` that `head[cut..]`
    // starts with, so exactly one comma goes in between.
    format!(
        "{},\"provenance\":[{{\"mode\":\"{mode}\",\"ref\":\"a/b.json\",\"source_class\":\"{class}\"}}]{}",
        &head[..cut],
        &head[cut..]
    )
}

#[test]
fn a_static_record_may_not_claim_the_runtime_source_class() {
    let error =
        only_record(&record_with_provenance("live", "runtime")).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(detail.contains("source_class"), "{detail}");
            assert!(detail.contains("static snapshot may not claim"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

#[test]
fn a_static_record_may_claim_exactly_the_four_static_source_classes() {
    for (mode, class) in [
        ("persisted", "committed_artifact"),
        ("derived", "derived"),
        ("live", "ghidra"),
        ("persisted", "generated_index"),
    ] {
        let passport = only_record(&record_with_provenance(mode, class))
            .unwrap_or_else(|error| panic!("{class} must be accepted: {error}"));
        assert_eq!(passport.document_provenance().len(), 1);
        assert_eq!(
            passport.document_provenance()[0].source_class.as_str(),
            class
        );
        assert_eq!(passport.document_provenance()[0].mode.as_str(), mode);
    }
}

#[test]
fn an_unknown_provenance_mode_or_class_is_refused() {
    for (mode, class) in [
        ("imported", "committed_artifact"),
        ("persisted", "disassembly"),
        ("persisted", "RUNTIME"),
    ] {
        let error = only_record(&record_with_provenance(mode, class)).expect_err("must be refused");
        assert!(
            matches!(error, BridgeError::UnsupportedSchema { .. }),
            "{mode}/{class}: {error}"
        );
    }
}

// ---------------------------------------------------------------------------
// Engine-facing surface
// ---------------------------------------------------------------------------

#[test]
fn a_globals_value_is_carried_verbatim_including_the_prose_the_source_writes() {
    // The knowledge index writes sentences into `globals[]`, and the exporter
    // reproduces them rather than rewriting them. Normalising them would be
    // deriving, so the crate carries the sentence.
    let replacement = concat!(
        r#""globals":{"state":"available","evidence_level":"OBSERVED","evidence_state":"PERSISTED","#,
        r#""provenance":["reconstruction/knowledge/index.json"],"#,
        r#""value":["global:No direct gameplay-global data references were identified in the ","#,
        r#""target body."]}"#,
    );
    let passport = only_record(&with(GLOBALS_UNAVAILABLE, replacement)).expect("valid");
    assert_eq!(
        passport.globals().value().expect("present"),
        &[
            "global:No direct gameplay-global data references were identified in the ".to_owned(),
            "target body.".to_owned(),
        ]
    );
    assert_eq!(passport.globals().level(), EvidenceLevel::Observed);
}

#[test]
fn a_slot_is_reached_by_byte_displacement_and_never_by_subscript() {
    let passport = only_record(&with(VTABLE_UNAVAILABLE, VTABLE_ONE_MEMBERSHIP)).expect("valid");
    let memberships = passport.vtable_memberships();
    assert!(memberships.is_available());
    assert_eq!(memberships.level(), EvidenceLevel::Inferred);
    let membership = &memberships.value().expect("present")[0];
    assert_eq!(membership.table_va, 0x013f_57f8);
    assert_eq!(membership.slot, 8);
    assert_eq!(membership.slot_width, Some(12));
    assert_eq!(
        membership.byte_displacement(),
        32,
        "slot 8 of a 32-bit table is table+0x20; a subscript would have advanced by \
         sizeof(StateInterface), a whole pair of slots"
    );
    assert_eq!(
        membership.byte_displacement(),
        membership.slot * 4,
        "the accessor exists so the safe spelling is also the easy one"
    );
}

#[test]
fn an_open_runtime_gate_is_not_a_pass_and_not_a_failure() {
    for (gated, expected, accepts) in [
        (true, RuntimeGate::Open, true),
        (false, RuntimeGate::Closed, false),
    ] {
        let body = with(RECON_UNAVAILABLE, &recon_with_gate(gated));
        let passport = only_record(&body).expect("valid");
        let gate = passport.runtime_gate();
        assert!(gate.is_available());
        assert_eq!(gate.value(), Some(&expected), "runtime_gated={gated}");
        assert_eq!(gate.value().expect("present").as_bool(), Some(gated));
        assert_eq!(expected.accepts_runtime_evidence(), accepts);
        assert_eq!(
            passport.reconstruction_package().value().copied(),
            Some("WAVE6-PRESENTATION")
        );
        assert_eq!(passport.promoted().value(), Some(&false));
    }
}

#[test]
fn an_unstated_runtime_gate_is_its_own_state() {
    let body = with(RECON_UNAVAILABLE, &recon_with_gate(true))
        .replace(r#""runtime_gated":true,"#, r#""runtime_gated":null,"#);
    let passport = only_record(&body).expect("valid");
    assert_eq!(
        passport.runtime_gate().value(),
        Some(&RuntimeGate::Unstated),
        "an available record that says nothing about the gate is Unstated, not Closed"
    );
    assert_eq!(RuntimeGate::default(), RuntimeGate::Unstated);
}

#[test]
fn a_promoted_record_reports_promoted_true() {
    let body = with(RECON_UNAVAILABLE, RECON_PROMOTED).replace(
        r#""promotion_record":null"#,
        r#""promotion_record":"reconstruction/evidence/00000000/promotion.json""#,
    );
    let passport = only_record(&body).expect("valid");
    assert_eq!(passport.promoted().value(), Some(&true));
    assert_eq!(passport.runtime_gate().value(), Some(&RuntimeGate::Closed));
    assert_eq!(
        passport
            .reconstruction()
            .value()
            .expect("present")
            .static_status
            .as_deref(),
        Some("PASS")
    );
    assert_eq!(
        passport.evidence_locations().promotion_record.as_deref(),
        Some("reconstruction/evidence/00000000/promotion.json"),
        "the exporter's literal 00000000 is carried, not repaired"
    );
}

#[test]
fn the_source_unknown_subsystem_sentinel_is_reported_verbatim() {
    let body = record("0x00401000", "0x00001000", 10)
        .replace(r#""subsystem":"App""#, r#""subsystem":"Unknown""#);
    let passport = only_record(&body).expect("valid");
    assert_eq!(passport.subsystem().value().copied(), Some("Unknown"));
    assert!(passport.subsystem().is_available());
    assert!(
        !passport.classification().has_named_subsystem(),
        "the literal \"Unknown\" is a source value, not a subsystem name, and folding it into \
         Fact::unavailable would be deriving"
    );
}

#[test]
fn a_validation_dimension_is_data_and_its_verdict_is_validated() {
    let body = with(RECON_UNAVAILABLE, RECON_WITH_VALIDATION);
    let passport = only_record(&body).expect("valid");
    let validation = passport
        .reconstruction()
        .value()
        .expect("available")
        .validation
        .as_ref()
        .expect("validation present");
    assert_eq!(validation.coverage.len(), 2);
    assert_eq!(validation.coverage["ABI"].status, "PASS");
    assert_eq!(validation.coverage["ABI"].coverage, "partial");
    assert_eq!(
        validation.coverage["A DIMENSION FROM A FUTURE VERSION"].status, "WARN",
        "an open-key map carries a new dimension rather than refusing it"
    );
    assert_eq!(
        validation
            .runtime
            .as_ref()
            .map(|check| check.status.as_str()),
        Some("NOT_AVAILABLE")
    );
    assert_eq!(
        passport.reconstruction_package().reason(),
        Some("no_reconstruction_package"),
        "a null package inside an available record is not the same as no reconstruction"
    );
}

#[test]
fn a_validation_verdict_of_the_wrong_shape_is_still_refused() {
    let broken = RECON_WITH_VALIDATION.replace(
        r#""coverage":{"ABI":{"status":"PASS","coverage":"partial","detail":"stated","evidence":[]}"#,
        r#""coverage":{"ABI":{"status":7,"coverage":"partial","detail":"stated","evidence":[]}"#,
    );
    let body = with(RECON_UNAVAILABLE, &broken);
    let error = only_record(&body).expect_err("must be refused");
    match error {
        BridgeError::UnsupportedSchema { detail, .. } => {
            assert!(
                detail.contains("reconstruction.value.validation.coverage"),
                "{detail}"
            );
        }
        other => panic!("expected a schema refusal, got {other}"),
    }
}

// ---------------------------------------------------------------------------
// The artifact is optional
// ---------------------------------------------------------------------------

#[test]
fn a_missing_snapshot_is_a_typed_error_rather_than_a_panic() {
    let error = Snapshot::open(std::path::Path::new(
        "/nonexistent/function-passport-v1.jsonl",
    ))
    .expect_err("must be typed");
    match error {
        BridgeError::SnapshotUnavailable { path } => {
            assert!(path.ends_with("function-passport-v1.jsonl"));
        }
        other => panic!("expected SnapshotUnavailable, got {other}"),
    }
}

#[test]
fn this_crate_has_no_bevy_dependency() {
    // A crate-level dependency assertion is not expressible in Rust, so the
    // strongest available statement is the one below plus the manifest itself:
    // this crate's `[dependencies]` are `spore-core` and `thiserror`, and
    // `spore-core` declares neither. Both facts are checkable by reading two
    // small files, which is what the assertions do.
    let manifest = std::fs::read_to_string(concat!(env!("CARGO_MANIFEST_DIR"), "/Cargo.toml"))
        .expect("this crate's own manifest is readable");
    let dependencies = manifest
        .split("[dependencies]")
        .nth(1)
        .expect("the manifest declares dependencies");
    assert!(
        !dependencies.contains("bevy"),
        "the dependency block must not mention bevy"
    );
    assert!(dependencies.contains("spore-core"));
    assert!(dependencies.contains("thiserror"));
    assert!(
        !dependencies.contains("serde"),
        "no serde: the reader is hand-rolled so an unknown field can be refused"
    );

    let core_manifest = std::fs::read_to_string(concat!(
        env!("CARGO_MANIFEST_DIR"),
        "/../spore-core/Cargo.toml"
    ))
    .expect("spore-core's manifest is readable");
    assert!(
        !core_manifest.contains("bevy"),
        "spore-core must stay Bevy-free or this crate inherits a window"
    );
    assert!(!core_manifest.contains("serde"));
}

// ---------------------------------------------------------------------------
// Whole-file rules
// ---------------------------------------------------------------------------

#[test]
fn a_digest_mismatch_is_reported_with_both_digests() {
    let file = TempFile::new(
        "bad-digest",
        &snapshot_file(&[record("0x00401000", "0x00001000", 10)]),
    );
    let snapshot = Snapshot::open(file.path()).expect("open does not hash");
    match snapshot.verify() {
        Err(BridgeError::ContentDigestMismatch {
            declared, computed, ..
        }) => {
            assert_eq!(declared, "0".repeat(64));
            assert_eq!(computed.len(), 64);
            assert_ne!(declared, computed);
        }
        other => panic!("expected a digest mismatch, got {other:?}"),
    }
}

#[test]
fn an_unsorted_snapshot_is_refused_because_the_index_would_be_wrong() {
    let file = TempFile::new(
        "unsorted",
        &snapshot_file(&[
            record("0x00401020", "0x00001020", 10),
            record("0x00401000", "0x00001000", 10),
        ]),
    );
    match Snapshot::open(file.path()) {
        Err(BridgeError::Corrupt { detail, line, .. }) => {
            assert_eq!(line, 3);
            assert!(detail.contains("strictly ascending"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn a_duplicate_canonical_va_is_refused() {
    let file = TempFile::new(
        "duplicate",
        &snapshot_file(&[
            record("0x00401000", "0x00001000", 10),
            record("0x00401000", "0x00001000", 10),
        ]),
    );
    match Snapshot::open(file.path()) {
        Err(BridgeError::Corrupt { detail, .. }) => {
            assert!(detail.contains("duplicate canonical VA"), "{detail}");
        }
        other => panic!("expected corruption, got {other:?}"),
    }
}

#[test]
fn a_wrong_schema_id_is_refused_before_any_record_is_read() {
    let body = format!(
        "{}\n",
        metadata_line(1, &"0".repeat(64))
            .replace("spore-semantic-snapshot-1", "spore-semantic-snapshot-2")
    );
    let file = TempFile::new("schema-2", &body);
    match Snapshot::open(file.path()) {
        Err(BridgeError::UnsupportedSchema { line, detail, .. }) => {
            assert_eq!(line, 1);
            assert!(detail.contains("spore-semantic-snapshot-2"), "{detail}");
        }
        other => panic!("expected a schema refusal, got {other:?}"),
    }
}

#[test]
fn a_file_without_a_metadata_line_is_refused() {
    let file = TempFile::new("no-header", &record("0x00401000", "0x00001000", 10));
    match Snapshot::open(file.path()) {
        Err(BridgeError::UnsupportedSchema { line, detail, .. }) => {
            assert_eq!(line, 1);
            assert!(
                detail.contains("unknown field") || detail.contains("required field"),
                "the record was read as a metadata line and refused: {detail}"
            );
        }
        Err(other) => panic!("expected a typed refusal, got {other:?}"),
        Ok(_) => panic!("a record line must not pass as a metadata line"),
    }
}

#[test]
fn an_empty_file_is_refused() {
    let file = TempFile::new("empty", "");
    assert!(matches!(
        Snapshot::open(file.path()),
        Err(BridgeError::Corrupt { .. })
    ));
}

#[test]
fn the_committed_snapshot_is_found_by_walking_up_from_the_working_directory() {
    // `Snapshot::open_committed` is how an engine reaches the artifact without
    // being told where it is. It resolves `$OPENSPORE_SEMANTIC_SNAPSHOT`, then
    // `$OPENSPORE_ROOT`, then the working directory and its ancestors.
    match spore_semantic_bridge::Snapshot::open_committed() {
        Ok(snapshot) => {
            assert!(
                snapshot.path().ends_with("function-passport-v1.jsonl"),
                "{}",
                snapshot.path().display()
            );
            assert!(snapshot.binary_sha256().len() == 64);
        }
        Err(BridgeError::SnapshotUnavailable { path }) => {
            assert!(
                path.ends_with("function-passport-v1.jsonl"),
                "the error names the location searched for: {}",
                path.display()
            );
        }
        other => panic!("expected a snapshot or an optionality error, got {other:?}"),
    }
    // `committed_snapshot_path` answers the same question without reading a byte.
    match spore_semantic_bridge::committed_snapshot_path() {
        Ok(path) => assert!(path.ends_with("function-passport-v1.jsonl")),
        Err(error) => assert!(matches!(error, BridgeError::SnapshotUnavailable { .. })),
    }
}

// ---------------------------------------------------------------------------
// Streaming query surface
// ---------------------------------------------------------------------------

#[test]
fn queries_are_streaming_and_filter_on_named_values() {
    let mut bodies = Vec::new();
    for (index, subsystem) in ["App", "UTFWin", "App", "Simulator"].iter().enumerate() {
        let va = format!("0x{:08x}", 0x0040_1000u32 + (index as u32) * 0x10);
        let rva = format!("0x{:08x}", 0x0000_1000u32 + (index as u32) * 0x10);
        let body = record(&va, &rva, 16).replace(
            r#""subsystem":"App""#,
            &format!(r#""subsystem":"{subsystem}""#),
        );
        bodies.push(body);
    }
    let fixture = fixture(&bodies);
    let snapshot = fixture.snapshot();
    assert_eq!(snapshot.function_count(), 4);
    assert_eq!(snapshot.symbol_count(), 4);

    let app: Vec<u32> = snapshot
        .passports_in_subsystem("App")
        .map(|passport| passport.expect("valid").canonical_va())
        .collect();
    assert_eq!(app.len(), 2, "the filter really filters");

    let histogram = snapshot.subsystem_histogram().expect("streamed");
    assert_eq!(histogram.len(), 3);
    assert_eq!(histogram[0], ("App".to_owned(), 2));
    assert_eq!(histogram[1].0, "Simulator");
    assert_eq!(histogram[2].0, "UTFWin");

    let all: Vec<u32> = snapshot
        .passports()
        .map(|passport| passport.expect("valid").canonical_va())
        .collect();
    assert_eq!(
        all,
        vec![0x0040_1000, 0x0040_1010, 0x0040_1020, 0x0040_1030]
    );
    assert_eq!(snapshot.passports().remaining(), 4);
}

#[test]
fn a_name_lookup_reports_ambiguity_rather_than_resolving_it() {
    let second = record("0x00401010", "0x00001010", 10)
        .replace(
            r#""ghidra_name":"FUN_00401010""#,
            r#""ghidra_name":"FUN_00401000""#,
        )
        .replace(
            r#""normalized_symbol":"FUN_00401010""#,
            r#""normalized_symbol":"FUN_00401000""#,
        )
        .replace(r#""subsystem":"App""#, r#""subsystem":"UTFWin""#);
    let fixture = fixture(&[record("0x00401000", "0x00001000", 10), second]);
    let snapshot = fixture.snapshot();
    assert_eq!(
        snapshot.lookup_symbol("FUN_00401000").expect("found").len(),
        2
    );
    assert_eq!(
        snapshot
            .lookup_symbol("fun_00401000")
            .expect("case-insensitive")
            .len(),
        2
    );
    assert_eq!(snapshot.ambiguous_name_count(), 1);
    match snapshot.resolve_symbol("FUN_00401000") {
        Err(BridgeError::AmbiguousSymbol { name, matches }) => {
            assert_eq!(name, "FUN_00401000");
            assert_eq!(matches, 2);
        }
        other => panic!("expected an ambiguity report, got {other:?}"),
    }
    assert!(
        matches!(
            snapshot.resolve_symbol("UTFWin"),
            Err(BridgeError::UnknownSymbol { .. })
        ),
        "a subsystem is not a name: only normalized_symbol, sdk_name and ghidra_name are indexed"
    );
    assert!(matches!(
        snapshot.resolve_symbol("FUN_00999999"),
        Err(BridgeError::UnknownSymbol { .. })
    ));
}

#[test]
fn a_lookup_miss_names_the_address_the_binary_and_the_index_size() {
    let file = TempFile::new(
        "miss",
        &snapshot_file(&[record("0x00401000", "0x00001000", 10)]),
    );
    let snapshot = Snapshot::open(file.path()).expect("valid");
    match snapshot.lookup(0x0050_0000) {
        Err(BridgeError::UnknownFunction {
            requested,
            image_base,
            indexed,
        }) => {
            assert_eq!(requested, 0x0050_0000);
            assert_eq!(image_base, 0x0040_0000);
            assert_eq!(indexed, 1);
        }
        other => panic!("expected UnknownFunction, got {other:?}"),
    }
    let text = snapshot.lookup(0x0050_0000).unwrap_err().to_string();
    assert!(text.contains("0x00500000"), "{text}");
    assert!(text.contains("1 functions indexed"), "{text}");
}

#[test]
fn the_rule_names_match_the_go_clis_spelling() {
    assert_eq!(Canonicalization::FunctionEntry.as_str(), "function_entry");
    assert_eq!(
        Canonicalization::ContainingFunctionEntry.as_str(),
        "containing_function_entry"
    );
    assert_eq!(
        Canonicalization::NonFunctionEntity.as_str(),
        "non_function_entity"
    );
    for rule in [
        Canonicalization::FunctionEntry,
        Canonicalization::ContainingFunctionEntry,
        Canonicalization::NonFunctionEntity,
    ] {
        assert_eq!(Canonicalization::parse(rule.as_str()), Some(rule));
    }
    assert_eq!(Canonicalization::parse("not_a_rule"), None);
    assert_eq!(TriState::Undetermined.as_str(), "null");
    assert_eq!(TriState::Undetermined, TriState::default());
}
