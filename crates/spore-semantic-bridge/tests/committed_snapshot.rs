//! The committed 98 MB artifact: integrity, coverage, and the engine-facing
//! answers.
//!
//! Every test here skips **loudly** when the file is absent. The artifact is
//! optional by contract, so a machine without it must still run the suite
//! green — and a test that reported success without having read anything would
//! be worse than one that says it did not run.

mod support;

use spore_semantic_bridge::{
    BridgeError, Canonicalization, EvidenceLevel, RuntimeGate, Snapshot, TriState,
};

/// The digest the metadata line declares, pinned here so a change to the
/// exporter cannot pass unnoticed.
const EXPECTED_CONTENT_SHA256: &str =
    "5920dfa1827f55c6c7d09197d77cc3e5e989f1a441b58b341a4d9ec9410f3a81";

/// The record count the artifact holds, also declared by `metadata.counts`.
const EXPECTED_RECORDS: usize = 58_757;

fn snapshot() -> Option<&'static Snapshot> {
    static ONCE: std::sync::OnceLock<Option<Snapshot>> = std::sync::OnceLock::new();
    static PATH: std::sync::OnceLock<std::path::PathBuf> = std::sync::OnceLock::new();
    let path = support::committed_path()?;
    let _ = PATH.set(path);
    ONCE.get_or_init(|| {
        let path = PATH.get().expect("path was just set");
        Some(
            Snapshot::open(path)
                .unwrap_or_else(|error| panic!("the committed snapshot must open: {error}")),
        )
    })
    .as_ref()
}

macro_rules! snapshot_or_skip {
    () => {
        match snapshot() {
            Some(snapshot) => snapshot,
            None => {
                eprintln!(
                    "SKIPPED: knowledge/semantic/function-passport-v1.jsonl is not present; the \
                     artifact is optional and this case cannot run without it"
                );
                return;
            }
        }
    };
}

// ---------------------------------------------------------------------------
// 3. verify(): the digest covers the record lines only
// ---------------------------------------------------------------------------

#[test]
fn the_content_digest_covers_the_record_lines_only_and_matches_the_pinned_value() {
    let snapshot = snapshot_or_skip!();
    assert_eq!(
        snapshot.declared_content_sha256(),
        EXPECTED_CONTENT_SHA256,
        "the committed metadata line declares this digest"
    );

    // Line 1 is excluded, so the field is not self-referential: recomputing over
    // lines 2..N must reproduce it exactly.
    let verification = snapshot.verify().expect("the digest must match");
    assert_eq!(
        verification.declared_content_sha256, EXPECTED_CONTENT_SHA256,
        "the declared digest"
    );
    assert_eq!(
        verification.computed_content_sha256, EXPECTED_CONTENT_SHA256,
        "the digest recomputed here over the record lines only"
    );
    assert_eq!(verification.declared_record_count, EXPECTED_RECORDS);
    assert_eq!(verification.computed_record_count, EXPECTED_RECORDS);
    // Line 1 is excluded, and provably so: the record bytes plus the metadata
    // line's own bytes and its terminator account for the whole file.
    let file_bytes = std::fs::metadata(snapshot.path())
        .expect("the file is there")
        .len();
    let header_bytes = {
        use std::io::BufRead;
        let mut reader = std::io::BufReader::new(
            std::fs::File::open(snapshot.path()).expect("the file is readable"),
        );
        let mut line = Vec::new();
        reader.read_until(b'\n', &mut line).expect("line 1 reads");
        line.len() as u64
    };
    assert_eq!(
        verification.record_bytes + header_bytes,
        file_bytes,
        "every byte of the file is either the metadata line or a record line"
    );
    assert!(
        header_bytes < verification.record_bytes / 100,
        "the metadata line is one line of {}; it is excluded from the digest",
        header_bytes
    );
}

#[test]
fn the_header_record_count_and_the_body_agree() {
    let snapshot = snapshot_or_skip!();
    assert_eq!(snapshot.function_count(), EXPECTED_RECORDS);
    assert_eq!(
        snapshot.metadata().counts.functions as usize,
        snapshot.function_count()
    );
    assert_eq!(
        snapshot.metadata().counts.total_fact_groups,
        7 * EXPECTED_RECORDS as i64,
        "seven fact groups per passport is the denominator the exporter declares"
    );
}

#[test]
fn the_header_identifies_the_binary_and_its_analysis_state() {
    let snapshot = snapshot_or_skip!();
    assert_eq!(snapshot.image_base(), 0x0040_0000);
    assert_eq!(snapshot.binary().architecture, "x86:LE:32");
    assert_eq!(snapshot.binary().program, "SporeApp.exe");
    assert_eq!(snapshot.binary().version, "3.1.0.22");
    assert_eq!(snapshot.binary_sha256().len(), 64);
    assert_eq!(snapshot.schema(), "spore-semantic-snapshot-1");
    assert_eq!(snapshot.metadata().generator.name, "spore-semantic");
    assert_eq!(snapshot.metadata().inputs.len(), 685);
    assert!(snapshot.metadata().absent_inputs.is_empty());
    assert!(!snapshot.metadata().export.universe_fallback);
    assert!(
        snapshot
            .metadata()
            .inputs
            .iter()
            .all(|input| !input.path.starts_with('/')),
        "the format carries repo-relative paths and no absolute host paths"
    );
}

#[test]
fn a_mismatched_binary_requirement_is_refused_before_any_fact_is_trusted() {
    let snapshot = snapshot_or_skip!();
    assert!(snapshot.require_binary(snapshot.binary_sha256()).is_ok());
    match snapshot.require_binary(&"0".repeat(64)) {
        Err(BridgeError::BinaryMismatch { snapshot, required }) => {
            assert_eq!(snapshot.len(), 64);
            assert_eq!(required, "0".repeat(64));
        }
        other => panic!("expected a binary mismatch, got {other:?}"),
    }
}

// ---------------------------------------------------------------------------
// The counters, recomputed from the bodies and compared with the header
// ---------------------------------------------------------------------------

#[test]
fn the_recomputed_coverage_counters_agree_with_the_header() {
    // A hand-edited header is caught even when the content digest still matches,
    // because the counters are recomputable from the record bodies.
    let snapshot = snapshot_or_skip!();
    let counts = snapshot.metadata().counts;
    let mut seen = Seen::default();

    snapshot
        .for_each_passport(|passport| {
            seen.functions += 1;
            if passport.sdk_name().is_available() {
                seen.with_sdk_name += 1;
            }
            if let Some(record) = passport.abi().value() {
                if record.convention.is_some() {
                    seen.with_abi_data += 1;
                } else {
                    seen.with_abi_unknown += 1;
                }
                match passport.receiver_present() {
                    Some(TriState::True) => seen.with_receiver += 1,
                    Some(TriState::Undetermined) => seen.with_receiver_unknown += 1,
                    _ => {}
                }
            }
            if passport
                .vtable_memberships()
                .value()
                .is_some_and(|list| !list.is_empty())
            {
                seen.with_vtable_membership += 1;
            }
            if passport.classification().renderware_role.is_some() {
                seen.with_renderware_role += 1;
            }
            if passport.classification().subsystem.is_some() {
                seen.with_subsystem += 1;
            }
            if passport.semantics().is_available() {
                seen.with_semantics += 1;
            }
            if passport.globals().is_available() {
                seen.with_globals += 1;
            }
            if passport.types().is_available() {
                seen.with_types += 1;
            }
            if !passport.callers().is_empty() {
                seen.with_callers += 1;
            }
            if !passport.callees().is_empty() || !passport.external_callees().is_empty() {
                seen.with_callees += 1;
            }
            if passport.identity_refuted().is_some() {
                seen.with_refuted_identity += 1;
            }
            if let Some(record) = passport.reconstruction().value() {
                if record.package.is_some() {
                    seen.with_reconstruction_package += 1;
                }
                if record.promoted == TriState::True {
                    seen.with_promotion += 1;
                }
                if record.validation.is_some() {
                    seen.with_validation += 1;
                }
            }
            if passport.evidence_locations().pack.is_some() {
                seen.with_evidence_pack += 1;
            }
            seen.explicitly_unavailable += 7 - [
                passport.abi().is_available(),
                passport.vtable().is_available(),
                passport.globals().is_available(),
                passport.types().is_available(),
                passport.semantics().is_available(),
                passport.reconstruction().is_available(),
                passport
                    .reconstruction()
                    .value()
                    .is_some_and(|record| record.validation.is_some()),
            ]
            .iter()
            .filter(|present| **present)
            .count() as i64;
            Ok(())
        })
        .expect("the whole file streams");

    assert_eq!(seen.functions, counts.functions);
    assert_eq!(seen.with_sdk_name, counts.with_sdk_name);
    assert_eq!(seen.with_abi_data, counts.with_abi_data);
    assert_eq!(seen.with_abi_unknown, counts.with_abi_unknown);
    assert_eq!(seen.with_receiver, counts.with_receiver);
    assert_eq!(seen.with_receiver_unknown, counts.with_receiver_unknown);
    assert_eq!(seen.with_vtable_membership, counts.with_vtable_membership);
    assert_eq!(seen.with_renderware_role, counts.with_renderware_role);
    assert_eq!(seen.with_subsystem, counts.with_subsystem);
    assert_eq!(seen.with_semantics, counts.with_semantics);
    assert_eq!(seen.with_globals, counts.with_globals);
    assert_eq!(seen.with_types, counts.with_types);
    assert_eq!(seen.with_callers, counts.with_callers);
    assert_eq!(seen.with_callees, counts.with_callees);
    assert_eq!(seen.with_refuted_identity, counts.with_refuted_identity);
    assert_eq!(
        seen.with_reconstruction_package,
        counts.with_reconstruction_package
    );
    assert_eq!(seen.with_promotion, counts.with_promotion);
    assert_eq!(seen.with_validation, counts.with_validation);
    assert_eq!(seen.with_evidence_pack, counts.with_evidence_pack);
    assert_eq!(
        seen.explicitly_unavailable, counts.explicitly_unavailable,
        "the number of stated 'we looked and found nothing' answers must agree with the header"
    );
}

#[derive(Default)]
struct Seen {
    functions: i64,
    with_sdk_name: i64,
    with_abi_data: i64,
    with_abi_unknown: i64,
    with_receiver: i64,
    with_receiver_unknown: i64,
    with_vtable_membership: i64,
    with_renderware_role: i64,
    with_subsystem: i64,
    with_reconstruction_package: i64,
    with_promotion: i64,
    with_evidence_pack: i64,
    with_validation: i64,
    with_semantics: i64,
    with_globals: i64,
    with_types: i64,
    with_callers: i64,
    with_callees: i64,
    with_refuted_identity: i64,
    explicitly_unavailable: i64,
}

// ---------------------------------------------------------------------------
// Engine-facing answers, on records the documentation names
// ---------------------------------------------------------------------------

#[test]
fn a_promoted_sdk_named_engine_interface_reports_every_graded_fact() {
    // `docs/tooling/semantic-exchange.md` §7.2 names this record as the worked
    // example: promoted, SDK-named, full record.
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x0040_ccb0).expect("0x0040ccb0 is indexed");

    assert_eq!(
        passport.sdk_name().value().copied(),
        Some("Transform::PreTransformBy")
    );
    assert_eq!(passport.sdk_name_source(), Some("sdk_functions.tsv"));
    assert_eq!(passport.sdk_namespace(), Some("Transform"));
    assert_eq!(passport.ghidra_name(), "Transform::PreTransformBy");
    assert_eq!(
        passport.normalized_symbol(),
        Some("transform_pre_transform_by_0040ccb0")
    );

    assert_eq!(
        passport.category().value().copied(),
        Some("ENGINE_INTERFACE")
    );
    assert_eq!(
        passport.subsystem().value().copied(),
        Some("Graphics.Transform")
    );
    assert!(passport.classification().has_named_subsystem());
    assert_eq!(
        passport.classification().subsystem_source.as_deref(),
        Some("reconstruction_knowledge_index")
    );

    assert_eq!(passport.convention().value().copied(), Some("__thiscall"));
    assert_eq!(
        passport.convention().level(),
        EvidenceLevel::Inferred,
        "an inferred convention is graded INFERRED, not promoted to a higher rung"
    );
    let abi = passport.abi();
    assert!(abi.is_available());
    assert_eq!(
        abi.evidence_state(),
        spore_semantic_bridge::EvidenceState::Derived
    );
    assert_eq!(abi.provenance().len(), 3);
    assert_eq!(passport.receiver_present(), Some(TriState::True));
    assert_eq!(
        passport
            .abi()
            .value()
            .expect("available")
            .receiver
            .as_ref()
            .map(|r| r.register.clone()),
        Some(Some("ECX".to_owned()))
    );

    assert_eq!(passport.callers().len(), 25);
    assert_eq!(
        passport.callees(),
        &[0x0041_daf0, 0x0041_dca0, 0x0041_ddb0, 0x0041_de20]
    );
    assert!(passport.callees().windows(2).all(|w| w[0] < w[1]));
    assert_eq!(
        passport.graph().caller_count as usize,
        passport.callers().len()
    );
    assert_eq!(passport.graph().scc_size, Some(1));

    assert_eq!(
        passport.reconstruction_package().value().copied(),
        Some("WAVE6-PRESENTATION")
    );
    assert_eq!(
        passport.runtime_gate().value(),
        Some(&RuntimeGate::Open),
        "runtime_gated: true is an open gate, not a failure and not a pass"
    );
    assert_eq!(passport.promoted().value(), Some(&false));
    assert_eq!(
        passport
            .reconstruction()
            .value()
            .expect("available")
            .integration_status
            .as_deref(),
        Some("integrated")
    );
    assert!(passport.unresolved_questions().is_available());

    let validation = passport
        .reconstruction()
        .value()
        .expect("available")
        .validation
        .as_ref()
        .expect("this record carries a validation report");
    assert_eq!(validation.coverage["ABI"].status, "PASS");
    assert_eq!(validation.coverage["ABI"].coverage, "partial");
    assert_eq!(validation.coverage.len(), 9);
    assert!(validation.runtime.is_some());
}

#[test]
fn an_abstaining_abi_record_is_reported_as_undetermined() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x0041_dc10).expect("0x0041dc10 is indexed");
    assert!(passport.abi().is_available());
    let record = passport.abi().value().expect("available");
    assert_eq!(record.convention, None);
    assert_eq!(record.verdict.as_deref(), Some("ABI_UNKNOWN"));
    assert_eq!(record.convention_confidence, EvidenceLevel::Unknown);
    assert_eq!(
        passport.convention().reason(),
        Some(spore_semantic_bridge::REASON_CONVENTION_UNDETERMINED)
    );
    assert_eq!(passport.receiver_present(), Some(TriState::Undetermined));
}

#[test]
fn a_promoted_word_getter_reports_promotion_and_its_static_verdict() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x00c0_bbd0).expect("indexed");
    assert_eq!(passport.promoted().value(), Some(&true));
    let record = passport.reconstruction().value().expect("available");
    assert_eq!(
        record.promotion_schema.as_deref(),
        Some("openspore-promotion-record-1")
    );
    assert_eq!(record.static_status.as_deref(), Some("PASS"));
    assert_eq!(record.runtime_gate, RuntimeGate::Closed);
    let validation = record.validation.as_ref().expect("validation present");
    assert_eq!(validation.coverage["ABI"].status, "PASS");
    assert_eq!(validation.coverage["ABI"].coverage, "partial");
}

#[test]
fn a_vftable_backed_record_carries_its_memberships() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x0040_2ab0).expect("indexed");
    let memberships = passport.vtable_memberships();
    assert!(memberships.is_available());
    let list: &[spore_semantic_bridge::VTableMembership] = memberships.value().expect("present");
    assert!(!list.is_empty());
    for membership in list {
        assert!(membership.byte_displacement() % 4 == 0);
        if let Some(width) = membership.slot_width {
            assert!(
                membership.slot < width,
                "slot {} is outside a table of {width} slots",
                membership.slot
            );
        }
    }
}

#[test]
fn a_renderware_record_carries_its_role_and_sdk_type() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x011e_e700).expect("indexed");
    assert_eq!(
        passport.sdk_name().value().copied(),
        Some("RenderWare::CompiledState::SetRaster")
    );
    assert_eq!(
        passport.classification().renderware_role.as_deref(),
        Some("RenderWare")
    );
    assert_eq!(
        passport.classification().sdk_structs,
        vec!["/Spore/RenderWare/CompiledState".to_owned()]
    );
}

#[test]
fn the_one_refuted_identity_is_reported_with_its_reason_kept_as_an_object() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x0084_14c0).expect("indexed");
    let refuted = passport
        .identity_refuted()
        .expect("the one refuted identity");
    assert_eq!(refuted.superseded, "ArgScript::FormatParser::ParseFloat");
    assert_eq!(refuted.superseded_source, "triage_queue");
    assert!(refuted.declared_by.is_some());
    let reason = refuted
        .reason
        .as_ref()
        .expect("the reason is carried verbatim");
    assert!(
        reason.as_str().contains("decompiler_artefact_not_followed"),
        "the reason is keyed by failure mode; flattening it to prose would lose which one fired"
    );
    assert!(refuted.refuted.is_some());
    // The refuted SDK name is still reported as a fact, with its own grade: the
    // format does not retract it, it records the refutation beside it.
    assert_eq!(
        passport.sdk_name().value().copied(),
        Some("ArgScript::FormatParser::ParseFloat")
    );
}

#[test]
fn an_interior_records_extra_evidence_packs_on_the_containing_entry() {
    let snapshot = snapshot_or_skip!();
    let passport = snapshot.lookup(0x00e3_a270).expect("indexed");
    let packs = &passport.evidence_locations().additional_packs;
    assert_eq!(packs.len(), 1);
    assert_eq!(packs[0].requested_va, 0x00e3_a400);
    assert_eq!(packs[0].offset, 400);
    assert_eq!(packs[0].rule, "containing_function_entry");
    assert!(packs[0]
        .pack
        .ends_with("reconstruction/evidence/00e3a400/evidence.json"));
}

#[test]
fn the_literal_zero_promotion_path_is_carried_not_repaired() {
    // A claim in `crate::claims`, checked against the real file.
    let snapshot = snapshot_or_skip!();
    let promoted: Vec<String> = snapshot
        .promoted_passports()
        .map(|passport| {
            let passport = passport.expect("valid");
            passport
                .evidence_locations()
                .promotion_record
                .clone()
                .unwrap_or_else(|| "<none>".to_owned())
        })
        .collect();
    assert_eq!(
        promoted.len(),
        92,
        "92 promotion markers on the current checkout"
    );
    for path in &promoted {
        assert!(
            path.contains("/00000000/"),
            "the exporter spells the directory with a literal zero: {path}"
        );
    }
}

// ---------------------------------------------------------------------------
// The engine-facing query surface, measured against the real corpus
// ---------------------------------------------------------------------------

#[test]
fn a_subsystem_histogram_is_usable_as_a_routing_key() {
    let snapshot = snapshot_or_skip!();
    let histogram = snapshot.subsystem_histogram().expect("streamed");
    let total: usize = histogram.iter().map(|(_, count)| count).sum();
    assert_eq!(total, EXPECTED_RECORDS, "the histogram loses no record");

    let unknown = histogram
        .iter()
        .find(|(name, _)| name == "Unknown")
        .map(|(_, count)| *count)
        .expect("the source sentinel is present");
    assert_eq!(
        unknown, 49_340,
        "a subsystem field is present on every record and 49 340 of them say Unknown"
    );
    assert_eq!(
        snapshot.metadata().counts.with_subsystem as usize,
        EXPECTED_RECORDS,
        "every record has a subsystem FIELD, which is why with_subsystem cannot be a routing \
         quality measure"
    );
}

#[test]
fn an_sdk_namespace_histogram_totals_the_record_count() {
    let snapshot = snapshot_or_skip!();
    let histogram = snapshot.sdk_namespace_histogram().expect("streamed");
    let total: usize = histogram.iter().map(|(_, count)| count).sum();
    assert_eq!(total, EXPECTED_RECORDS);

    let expected = [
        ("Simulator", 280),
        ("App", 261),
        ("UTFWin", 150),
        ("Resource", 87),
        ("Editors", 75),
        ("IO", 66),
        ("Palettes", 47),
        ("ArgScript", 38),
        ("Graphics", 36),
        ("Terrain", 29),
        ("Skinner", 20),
    ];
    for (namespace, count) in expected {
        assert_eq!(
            histogram
                .iter()
                .find(|(name, _)| name == namespace)
                .map(|(_, count)| *count),
            Some(count),
            "the {namespace} namespace holds {count} SDK names"
        );
    }
    assert_eq!(
        histogram
            .iter()
            .find(|(name, _)| name == "<none>")
            .map(|(_, count)| *count),
        Some(EXPECTED_RECORDS - 1_171)
    );
}

#[test]
fn a_namespace_query_streams_only_the_matching_records() {
    let snapshot = snapshot_or_skip!();
    let utfwin: Vec<u32> = snapshot
        .passports_with_sdk_namespace("UTFWin")
        .map(|passport| {
            let passport = passport.expect("valid");
            assert_eq!(passport.sdk_namespace(), Some("UTFWin"));
            passport.canonical_va()
        })
        .collect();
    assert_eq!(utfwin.len(), 150);
    assert!(utfwin.windows(2).all(|w| w[0] < w[1]));
    assert!(snapshot
        .passports_with_sdk_namespace("NoSuchNamespace")
        .next()
        .is_none());
}

#[test]
fn a_name_lookup_resolves_a_renderware_symbol_to_its_entry() {
    let snapshot = snapshot_or_skip!();
    assert_eq!(
        snapshot
            .resolve_symbol("RenderWare::CompiledState::SetRaster")
            .expect("unambiguous"),
        0x011e_e700
    );
    assert_eq!(
        snapshot
            .lookup_symbol("RenderWare::CompiledState::SetRaster")
            .expect("found"),
        vec![0x011e_e700]
    );
    let matches = snapshot
        .lookup_symbol_passports("Transform::PreTransformBy")
        .expect("found");
    assert_eq!(matches.len(), 1);
    assert_eq!(matches[0].canonical_va(), 0x0040_ccb0);
}

#[test]
fn most_records_state_an_explicit_absence_rather_than_a_default() {
    let snapshot = snapshot_or_skip!();
    let counts = snapshot.metadata().counts;
    assert_eq!(counts.total_fact_groups, 7 * EXPECTED_RECORDS as i64);
    assert!(
        counts.explicitly_unavailable > counts.total_fact_groups * 9 / 10,
        "the artifact is overwhelmingly a record of what was looked for and not found: {} of {}",
        counts.explicitly_unavailable,
        counts.total_fact_groups
    );
    assert!(snapshot.ambiguous_name_count() > 0);
}

#[test]
fn the_rules_and_vocabulary_are_the_ones_the_format_declares() {
    let snapshot = snapshot_or_skip!();
    // The snapshot's own vocabulary, on a real record.
    let passport = snapshot.lookup(0x0040_ccb0).expect("indexed");
    assert_eq!(
        passport.abi().value().expect("present").origin,
        "abi_inference"
    );
    assert_eq!(
        passport.abi().value().expect("present").schema,
        "openspore-abi-inference-1"
    );
    let passport = snapshot.lookup(0x0040_2ab0).expect("indexed");
    if let Some(rule) = &passport.vtable().value().expect("present").attributed_rule {
        assert!(rule.starts_with('R') || rule.starts_with('V'));
    }
    assert_eq!(
        Canonicalization::parse("containing_function_entry"),
        Some(Canonicalization::ContainingFunctionEntry)
    );
}
