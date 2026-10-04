//! The declared shape of the snapshot, transcribed field by field from
//! `tools/spore-semantic/internal/semantic/passport.go`.
//!
//! # Every field, in one place
//!
//! The specs below are the whole contract this crate enforces. They are static
//! so that "is this field known?" is answered at compile time for the keys and
//! at run time — with the offending dotted path — for everything else.
//!
//! `required` mirrors the Go struct tags exactly: a field tagged `omitempty` is
//! optional (its absence means "not stated"), and a field without the tag is
//! required even when its value may be `null`. That distinction matters: Go
//! writes `"sdk_name": null` but omits `sdk_name_source` entirely.
//!
//! The unit tests at the bottom assert two invariants a reader of this file
//! cannot check by eye: no spec declares a key twice, and every child spec's
//! path is exactly its parent's path plus the field name — which is what makes
//! an error message like `vtable.value.memberships[3].slot` trustworthy.

use crate::json::{opt, req, ObjMode, Shape, Spec};

/// Builds the seven fact-group envelopes. They differ only in their `value`
/// shape, and one macro keeps them literally identical apart from that.
macro_rules! envelope {
    ($ident:ident, $path:literal, $value:expr) => {
        static $ident: Spec = Spec {
            path: $path,
            mode: ObjMode::Closed(&[
                req("state", Shape::Str),
                req("evidence_level", Shape::Str),
                req("evidence_state", Shape::Str),
                opt("provenance", Shape::StrArrayOrNull),
                opt("reason", Shape::Str),
                opt("value", $value),
            ]),
        };
    };
}

// ---------------------------------------------------------------------------
// The metadata line
// ---------------------------------------------------------------------------

static METADATA: Spec = Spec {
    path: "",
    mode: ObjMode::Closed(&[
        req("record", Shape::Str),
        req("schema", Shape::Str),
        req("binary", Shape::Object(&BINARY)),
        req("generator", Shape::Object(&GENERATOR)),
        req("inputs", Shape::ArrayOrNull(&INPUT_DIGEST)),
        req("absent_inputs", Shape::ArrayOrNull(&ABSENT_INPUT)),
        req("counts", Shape::Object(&COUNTS)),
        req("content_sha256", Shape::Str),
        req("export", Shape::Object(&EXPORT_NOTES)),
    ]),
};

static BINARY: Spec = Spec {
    path: "binary",
    mode: ObjMode::Closed(&[
        req("binary_sha256", Shape::Str),
        req("image_base", Shape::Str),
        req("architecture", Shape::Str),
        req("program", Shape::Str),
        req("version", Shape::Str),
    ]),
};

static GENERATOR: Spec = Spec {
    path: "generator",
    mode: ObjMode::Closed(&[req("name", Shape::Str), req("version", Shape::Str)]),
};

static INPUT_DIGEST: Spec = Spec {
    path: "inputs",
    mode: ObjMode::Closed(&[
        req("path", Shape::Str),
        req("sha256", Shape::Str),
        req("bytes", Shape::Int),
    ]),
};

static ABSENT_INPUT: Spec = Spec {
    path: "absent_inputs",
    mode: ObjMode::Closed(&[req("path", Shape::Str), req("reason", Shape::Str)]),
};

static COUNTS: Spec = Spec {
    path: "counts",
    mode: ObjMode::Closed(&[
        req("functions", Shape::Int),
        req("with_sdk_name", Shape::Int),
        req("with_abi_data", Shape::Int),
        req("with_abi_unknown", Shape::Int),
        req("with_receiver", Shape::Int),
        req("with_receiver_unknown", Shape::Int),
        req("with_vtable_membership", Shape::Int),
        req("with_vtable_attributed", Shape::Int),
        req("with_subsystem", Shape::Int),
        req("with_renderware_role", Shape::Int),
        req("with_reconstruction_package", Shape::Int),
        req("with_promotion", Shape::Int),
        req("with_evidence_pack", Shape::Int),
        req("with_validation", Shape::Int),
        req("with_semantics", Shape::Int),
        req("with_globals", Shape::Int),
        req("with_types", Shape::Int),
        req("with_callers", Shape::Int),
        req("with_callees", Shape::Int),
        req("with_refuted_identity", Shape::Int),
        req("resolved_interior_addresses", Shape::Int),
        req("attached_stray_evidence_packs", Shape::Int),
        req("explicitly_unavailable", Shape::Int),
        req("total_fact_groups", Shape::Int),
    ]),
};

static EXPORT_NOTES: Spec = Spec {
    path: "export",
    mode: ObjMode::Closed(&[
        req("universe_source", Shape::Str),
        req("universe_fallback", Shape::Bool),
        req("evidence_pack_dirs_read", Shape::Int),
        req("orphan_evidence_packs", Shape::Int),
        req("orphan_evidence_pack_paths", Shape::StrArrayOrNull),
    ]),
};

// ---------------------------------------------------------------------------
// A function record
// ---------------------------------------------------------------------------

envelope!(ABI_ENVELOPE, "abi", Shape::Object(&ABI_VALUE));
envelope!(VTABLE_ENVELOPE, "vtable", Shape::Object(&VTABLE_VALUE));
envelope!(GLOBALS_ENVELOPE, "globals", Shape::StrArrayOrNull);
envelope!(TYPES_ENVELOPE, "types", Shape::StrArrayOrNull);
envelope!(
    SEMANTICS_ENVELOPE,
    "semantics",
    Shape::Object(&SEMANTICS_VALUE)
);
envelope!(
    RECONSTRUCTION_ENVELOPE,
    "reconstruction",
    Shape::Object(&RECONSTRUCTION_VALUE)
);

static FUNCTION: Spec = Spec {
    path: "",
    mode: ObjMode::Closed(&[
        req("record", Shape::Str),
        req("identity", Shape::Object(&IDENTITY)),
        req("names", Shape::Object(&NAMES)),
        req("classification", Shape::Object(&CLASSIFICATION)),
        req("abi", Shape::Object(&ABI_ENVELOPE)),
        req("vtable", Shape::Object(&VTABLE_ENVELOPE)),
        req("graph", Shape::Object(&GRAPH)),
        req("globals", Shape::Object(&GLOBALS_ENVELOPE)),
        req("types", Shape::Object(&TYPES_ENVELOPE)),
        req("semantics", Shape::Object(&SEMANTICS_ENVELOPE)),
        req("reconstruction", Shape::Object(&RECONSTRUCTION_ENVELOPE)),
        req("evidence", Shape::Object(&EVIDENCE_BLOCK)),
        opt("provenance", Shape::ArrayOrNull(&PROVENANCE_ENTRY)),
    ]),
};

static IDENTITY: Spec = Spec {
    path: "identity",
    mode: ObjMode::Closed(&[
        req("canonical_va", Shape::Str),
        req("rva", Shape::Str),
        req("size", Shape::Int),
        req("size_known", Shape::Bool),
        req("is_thunk", Shape::Bool),
        req("section", Shape::Str),
        opt("requested", Shape::ArrayOrNull(&REQUESTED_ADDR)),
        req(
            "identity_resolution",
            Shape::ObjectOrNull(&IDENTITY_RESOLUTION),
        ),
    ]),
};

static REQUESTED_ADDR: Spec = Spec {
    path: "identity.requested",
    mode: ObjMode::Closed(&[req("va", Shape::Str), req("offset", Shape::Int)]),
};

static IDENTITY_RESOLUTION: Spec = Spec {
    path: "identity.identity_resolution",
    mode: ObjMode::Closed(&[
        req("rule", Shape::Str),
        req("canonical_va", Shape::Str),
        req("requested", Shape::ArrayOrNull(&REQUESTED_ADDR)),
    ]),
};

static NAMES: Spec = Spec {
    path: "names",
    mode: ObjMode::Closed(&[
        req("ghidra_name", Shape::Str),
        req("normalized_symbol", Shape::StrOrNull),
        req("sdk_name", Shape::StrOrNull),
        opt("sdk_name_source", Shape::Str),
        req("identity_refuted", Shape::ObjectOrNull(&REFUTED_IDENTITY)),
    ]),
};

static REFUTED_IDENTITY: Spec = Spec {
    path: "names.identity_refuted",
    mode: ObjMode::Closed(&[
        req("name", Shape::Str),
        req("superseded", Shape::Str),
        req("superseded_source", Shape::Str),
        req("declared_by", Shape::StrOrNull),
        req("reason", Shape::RawOrNull),
        req("refuted", Shape::RawOrNull),
    ]),
};

static CLASSIFICATION: Spec = Spec {
    path: "classification",
    mode: ObjMode::Closed(&[
        req("category", Shape::Str),
        req("priority", Shape::Str),
        req("evidence", Shape::Str),
        req("subsystem", Shape::StrOrNull),
        req("cluster", Shape::StrOrNull),
        opt("sdk_structs", Shape::StrArrayOrNull),
        req("renderware_role", Shape::StrOrNull),
        req("subsystem_source", Shape::StrOrNull),
    ]),
};

static ABI_VALUE: Spec = Spec {
    path: "abi.value",
    mode: ObjMode::Closed(&[
        req("origin", Shape::Str),
        req("schema", Shape::Str),
        req("convention", Shape::StrOrNull),
        req("convention_confidence", Shape::Str),
        req("verdict", Shape::StrOrNull),
        req("completeness", Shape::StrOrNull),
        req("receiver", Shape::ObjectOrNull(&RECEIVER)),
        req("cleanup", Shape::ObjectOrNull(&CLEANUP)),
        req("return", Shape::ObjectOrNull(&RETURN_BLOCK)),
        req("sret", Shape::ObjectOrNull(&SRET)),
        req("variadic", Shape::StrOrNull),
        req("stack_argument_slots", Shape::IntOrNull),
        req("seh_or_cookie_frame", Shape::BoolOrNull),
        req("declared", Shape::ObjectOrNull(&DECLARED_ABI)),
    ]),
};

static RECEIVER: Spec = Spec {
    path: "abi.value.receiver",
    mode: ObjMode::Closed(&[
        req("present", Shape::TriBool),
        req("register", Shape::StrOrNull),
        req("confidence", Shape::Str),
        req("shape", Shape::StrOrNull),
        req("provenance", Shape::StrOrNull),
        req("bounds_only", Shape::BoolOrNull),
        req("max_offset", Shape::IntOrNull),
        req("written_through", Shape::IntOrNull),
    ]),
};

static CLEANUP: Spec = Spec {
    path: "abi.value.cleanup",
    mode: ObjMode::Closed(&[
        req("side", Shape::StrOrNull),
        req("bytes", Shape::IntOrNull),
        req("confidence", Shape::Str),
        req("corroboration", Shape::StrOrNull),
        req("evidence", Shape::StrOrNull),
    ]),
};

static RETURN_BLOCK: Spec = Spec {
    path: "abi.value.return",
    mode: ObjMode::Closed(&[
        req("register", Shape::StrOrNull),
        req("register_class", Shape::StrOrNull),
        req("confidence", Shape::Str),
        req("type", Shape::StrOrNull),
        req("void_possible", Shape::BoolOrNull),
        req("bulk_write", Shape::BoolOrNull),
    ]),
};

static SRET: Spec = Spec {
    path: "abi.value.sret",
    mode: ObjMode::Closed(&[
        req("present", Shape::TriBool),
        req("slot", Shape::IntOrNull),
        req("confidence", Shape::Str),
        req("ambiguity", Shape::StrOrNull),
        req("hypothesis_confidence", Shape::Str),
    ]),
};

/// The hand-authored ABI block. Declared so that an unknown field inside it is
/// refused, and deliberately *not* retained: see `Passport::abi_declared`.
static DECLARED_ABI: Spec = Spec {
    path: "abi.value.declared",
    mode: ObjMode::Closed(&[
        req("calling_convention", Shape::StrOrNull),
        req("architecture", Shape::StrOrNull),
        req("hidden_receiver", Shape::StrOrNull),
        req("hidden_this_register", Shape::StrOrNull),
        req("receiver_register", Shape::StrOrNull),
        req("hidden_this", Shape::BoolOrNull),
        req("return_register", Shape::StrOrNull),
        req("return_type", Shape::StrOrNull),
        req("return_semantics", Shape::StrOrNull),
        req("return_observation", Shape::StrOrNull),
        req("return_note", Shape::StrOrNull),
        req("return_width_bytes", Shape::IntOrNull),
        req("hidden_this_type", Shape::StrOrNull),
        req("stack_cleanup_bytes", Shape::IntOrNull),
        req("stack_cleanup_owner", Shape::StrOrNull),
        req("ordinary_stack_argument_slots", Shape::IntOrNull),
        req("termination", Shape::StrOrNull),
        req("ret_form", Shape::StrOrNull),
        req("saved_registers", Shape::StrArrayOrNull),
        req("source", Shape::StrOrNull),
    ]),
};

static VTABLE_VALUE: Spec = Spec {
    path: "vtable.value",
    mode: ObjMode::Closed(&[
        req("memberships", Shape::ArrayOrNull(&VTABLE_MEMBERSHIP)),
        req("abi_attributed", Shape::ObjectOrNull(&VTABLE_ATTRIBUTION)),
        req("triage_addresses", Shape::StrArrayOrNull),
        req("triage_family", Shape::StrOrNull),
    ]),
};

static VTABLE_MEMBERSHIP: Spec = Spec {
    path: "vtable.value.memberships",
    mode: ObjMode::Closed(&[
        req("table_va", Shape::Str),
        req("slot", Shape::Int),
        req("slot_width", Shape::IntOrNull),
    ]),
};

static VTABLE_ATTRIBUTION: Spec = Spec {
    path: "vtable.value.abi_attributed",
    mode: ObjMode::Closed(&[
        req("rule", Shape::Str),
        req("table_va", Shape::Str),
        req("slot", Shape::Int),
        req("confidence", Shape::Str),
        req("receiver_provenance", Shape::StrOrNull),
        req("membership_count", Shape::IntOrNull),
    ]),
};

static GRAPH: Spec = Spec {
    path: "graph",
    mode: ObjMode::Closed(&[
        req("caller_count", Shape::Int),
        req("callee_count", Shape::Int),
        opt("callers", Shape::StrArrayOrNull),
        opt("callees", Shape::StrArrayOrNull),
        opt("external_callees", Shape::StrArrayOrNull),
        req("vtable_reference_count", Shape::Int),
        req("data_reference_count", Shape::Int),
        opt("scc_size", Shape::IntOrNull),
        opt("fan_in", Shape::IntOrNull),
        opt("fan_out", Shape::IntOrNull),
    ]),
};

static SEMANTICS_VALUE: Spec = Spec {
    path: "semantics.value",
    mode: ObjMode::Closed(&[
        req("classification", Shape::StrOrNull),
        req("semantic_status", Shape::StrOrNull),
        req("name", Shape::StrOrNull),
        req("subsystem", Shape::StrOrNull),
        req("triangulation_status", Shape::StrOrNull),
        req("downstream_unlock_count", Shape::IntOrNull),
        req("source", Shape::StrOrNull),
        req("confidence", Shape::ObjectOrNull(&CONFIDENCE_MAP)),
        req("evidence", Shape::ArrayOrNull(&SEMANTIC_CLAIM)),
        req("notes", Shape::StrArrayOrNull),
        req("unresolved_questions", Shape::StrArrayOrNull),
        req("semantic_family", Shape::StrOrNull),
        req("source_workers", Shape::StrArrayOrNull),
    ]),
};

static SEMANTIC_CLAIM: Spec = Spec {
    path: "semantics.value.evidence",
    mode: ObjMode::Closed(&[
        req("claim", Shape::Str),
        req("class", Shape::Str),
        req("source", Shape::Str),
    ]),
};

/// `semantics.value.confidence` is an open-key map whose values are captured
/// verbatim: upstream it is `map[string]json.RawMessage` whose values mix rung
/// names ("SUPPORTED") with numeric scores (0.72), and the exporter carries it
/// raw on purpose so neither spelling is coerced into the other.
static CONFIDENCE_MAP: Spec = Spec {
    path: "semantics.value.confidence",
    mode: ObjMode::RawMap,
};

/// `validation.static_rollup` is the other raw map, for the same reason: mixed
/// counters plus one float ratio.
static STATIC_ROLLUP: Spec = Spec {
    path: "reconstruction.value.validation.static_rollup",
    mode: ObjMode::RawMap,
};

static RECONSTRUCTION_VALUE: Spec = Spec {
    path: "reconstruction.value",
    mode: ObjMode::Closed(&[
        req("package", Shape::StrOrNull),
        req("status", Shape::StrOrNull),
        req("review_status", Shape::StrOrNull),
        req("integration_status", Shape::StrOrNull),
        req("reconstructed", Shape::BoolOrNull),
        req("blocked", Shape::BoolOrNull),
        req("promoted", Shape::TriBool),
        req("promotion_schema", Shape::StrOrNull),
        req("promotion_supersedes", Shape::RawOrNull),
        req("static_status", Shape::StrOrNull),
        req("generated_source", Shape::StrArrayOrNull),
        req("handoffs", Shape::StrArrayOrNull),
        req("metadata", Shape::StrArrayOrNull),
        req("runtime_gated", Shape::BoolOrNull),
        req("runtime_validated", Shape::IntOrNull),
        // The only `omitempty` pointer in the reconstruction block, so this is
        // the one field here the exporter is allowed to leave out entirely.
        opt("runtime_blocking_reason", Shape::RawOrNull),
        req("validation", Shape::ObjectOrNull(&VALIDATION)),
    ]),
};

static VALIDATION: Spec = Spec {
    path: "reconstruction.value.validation",
    mode: ObjMode::Closed(&[
        req("schema", Shape::Str),
        req("coverage", Shape::ObjectOrNull(&COVERAGE_MAP)),
        req("runtime", Shape::ObjectOrNull(&VALIDATION_CHECK)),
        req("static_rollup", Shape::ObjectOrNull(&STATIC_ROLLUP)),
    ]),
};

/// `map[string]ValidationCheck`: the dimension names are data, not schema, and
/// the format does not close them. Every value is still validated in full.
static COVERAGE_MAP: Spec = Spec {
    path: "reconstruction.value.validation.coverage",
    mode: ObjMode::MapOf(&VALIDATION_CHECK),
};

static VALIDATION_CHECK: Spec = Spec {
    path: "reconstruction.value.validation.coverage",
    mode: ObjMode::Closed(&[
        req("status", Shape::Str),
        req("coverage", Shape::Str),
        req("detail", Shape::Str),
        req("evidence", Shape::StrArrayOrNull),
    ]),
};

static EVIDENCE_BLOCK: Spec = Spec {
    path: "evidence",
    mode: ObjMode::Closed(&[
        req("pack", Shape::StrOrNull),
        req("pack_state", Shape::StrOrNull),
        req("pack_content_sha256", Shape::StrOrNull),
        req("target_address_kind", Shape::StrOrNull),
        req("validation_report", Shape::StrOrNull),
        req("promotion_record", Shape::StrOrNull),
        opt("additional_packs", Shape::ArrayOrNull(&ADDITIONAL_PACK)),
    ]),
};

static ADDITIONAL_PACK: Spec = Spec {
    path: "evidence.additional_packs",
    mode: ObjMode::Closed(&[
        req("pack", Shape::Str),
        req("requested_va", Shape::Str),
        req("offset", Shape::Int),
        req("rule", Shape::Str),
        req("pack_state", Shape::StrOrNull),
        req("pack_content_sha256", Shape::StrOrNull),
    ]),
};

static PROVENANCE_ENTRY: Spec = Spec {
    path: "provenance",
    mode: ObjMode::Closed(&[
        req("mode", Shape::Str),
        req("ref", Shape::Str),
        req("source_class", Shape::Str),
    ]),
};

// ---------------------------------------------------------------------------
// Accessors for the specs, and the two invariants that keep error paths honest
// ---------------------------------------------------------------------------

pub(crate) fn metadata_spec() -> &'static Spec {
    &METADATA
}

pub(crate) fn function_spec() -> &'static Spec {
    &FUNCTION
}

/// Every declared spec, for the coherence tests.
#[cfg(test)]
pub(crate) fn all_specs() -> Vec<&'static Spec> {
    vec![
        &METADATA,
        &BINARY,
        &GENERATOR,
        &INPUT_DIGEST,
        &ABSENT_INPUT,
        &COUNTS,
        &EXPORT_NOTES,
        &FUNCTION,
        &IDENTITY,
        &REQUESTED_ADDR,
        &IDENTITY_RESOLUTION,
        &NAMES,
        &REFUTED_IDENTITY,
        &CLASSIFICATION,
        &ABI_ENVELOPE,
        &ABI_VALUE,
        &RECEIVER,
        &CLEANUP,
        &RETURN_BLOCK,
        &SRET,
        &DECLARED_ABI,
        &VTABLE_ENVELOPE,
        &VTABLE_VALUE,
        &VTABLE_MEMBERSHIP,
        &VTABLE_ATTRIBUTION,
        &GRAPH,
        &GLOBALS_ENVELOPE,
        &TYPES_ENVELOPE,
        &SEMANTICS_ENVELOPE,
        &SEMANTICS_VALUE,
        &SEMANTIC_CLAIM,
        &CONFIDENCE_MAP,
        &RECONSTRUCTION_ENVELOPE,
        &RECONSTRUCTION_VALUE,
        &VALIDATION,
        &COVERAGE_MAP,
        &VALIDATION_CHECK,
        &STATIC_ROLLUP,
        &EVIDENCE_BLOCK,
        &ADDITIONAL_PACK,
        &PROVENANCE_ENTRY,
    ]
}

#[cfg(test)]
mod tests {
    use super::*;

    fn child_of(shape: Shape) -> Option<&'static Spec> {
        match shape {
            Shape::ArrayOrNull(spec) | Shape::Object(spec) | Shape::ObjectOrNull(spec) => {
                Some(spec)
            }
            _ => None,
        }
    }

    #[test]
    fn no_object_declares_the_same_key_twice() {
        for spec in all_specs() {
            if let ObjMode::Closed(fields) = spec.mode {
                for (i, field) in fields.iter().enumerate() {
                    for other in &fields[i + 1..] {
                        assert_ne!(
                            field.key, other.key,
                            "{} declares {:?} twice",
                            spec.path, field.key
                        );
                    }
                }
            }
        }
    }

    /// The dotted path a traversal produces for one field.
    fn reached_path(parent: &str, key: &str) -> String {
        if parent.is_empty() {
            key.to_owned()
        } else {
            format!("{parent}.{key}")
        }
    }

    #[test]
    fn every_child_specs_path_is_a_path_a_traversal_actually_produces() {
        // A spec reached from one place must name exactly that place. A spec
        // reached from several places — `REQUESTED_ADDR` is an element of both
        // `identity.requested` and `identity.identity_resolution.requested` —
        // may name any of them, because the reader computes error paths from the
        // traversal and never navigates by the declared string.
        let mut reached: Vec<(&'static Spec, String)> = Vec::new();
        for spec in all_specs() {
            match spec.mode {
                // An open-key object's element spec is reached at the map's own
                // path: the keys between them are data, not schema.
                ObjMode::MapOf(child) => reached.push((child, spec.path.to_owned())),
                ObjMode::Closed(fields) => {
                    for field in fields {
                        if let Some(child) = child_of(field.shape) {
                            reached.push((child, reached_path(spec.path, field.key)));
                        }
                    }
                }
                ObjMode::RawMap => {}
            }
        }
        for child in all_specs() {
            let every_path: Vec<&str> = reached
                .iter()
                .filter(|(spec, _)| std::ptr::eq(*spec, child))
                .map(|(_, path)| path.as_str())
                .collect();
            if every_path.is_empty() {
                continue;
            }
            assert!(
                every_path.contains(&child.path),
                "{} declares path {:?} but is reached at {every_path:?}",
                child.path,
                child.path
            );
        }
    }

    #[test]
    fn an_open_map_child_spec_shares_its_parents_path() {
        for spec in all_specs() {
            let ObjMode::MapOf(child) = spec.mode else {
                continue;
            };
            assert_eq!(
                child.path, spec.path,
                "{}: an open-key object's element spec must sit at the map's own path,                  because the keys between them are data rather than schema",
                spec.path
            );
        }
    }

    #[test]
    fn the_fact_group_envelopes_declare_the_same_fields() {
        let envelopes = [
            &ABI_ENVELOPE,
            &VTABLE_ENVELOPE,
            &GLOBALS_ENVELOPE,
            &TYPES_ENVELOPE,
            &SEMANTICS_ENVELOPE,
            &RECONSTRUCTION_ENVELOPE,
        ];
        let expected = [
            ("state", true),
            ("evidence_level", true),
            ("evidence_state", true),
            ("provenance", false),
            ("reason", false),
            ("value", false),
        ];
        // Six groups carry a top-level envelope; the seventh counted group,
        // validation, lives inside reconstruction.value and is not enveloped.
        assert_eq!(envelopes.len(), 6);
        for envelope in envelopes {
            let ObjMode::Closed(fields) = envelope.mode else {
                unreachable!()
            };
            let got: Vec<(&str, bool)> = fields.iter().map(|f| (f.key, f.required)).collect();
            assert_eq!(got, expected, "{}", envelope.path);
        }
    }
}
