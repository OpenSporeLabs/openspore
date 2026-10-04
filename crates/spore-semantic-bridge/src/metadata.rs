//! The metadata line: the header that makes a snapshot addressable.
//!
//! It carries no timestamp by design — determinism is a hard requirement of the
//! export, and a clock cannot be both written and excluded from the byte
//! comparison — so the reproducible identity of a snapshot is its
//! `content_sha256` over the record lines plus the `inputs` map, both of which
//! are stable functions of repository state alone.
//!
//! Reading the header enforces three things before a snapshot is usable at all:
//! the record discriminator is `metadata`, the `schema` id is the one this build
//! implements, and `binary_sha256` is 64 lowercase hex characters. A snapshot
//! with no binary identity is not addressable — it cannot be joined to anything.

use crate::address::{AddressError, Va};
use crate::error::BridgeError;
use crate::json::Obj;
use crate::passport::SNAPSHOT_SCHEMA;
use crate::snapshot::BinaryIdentity;

/// One file the export read, with its digest.
///
/// 685 entries on the current checkout. This map is what lets a consumer record
/// *which* OpenSpore analysis state produced a fact: two snapshots with the same
/// `content_sha256` are the same bytes, and two exports with different
/// `inputs` digests differ because the repository moved, not because the
/// exporter is non-deterministic.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct InputDigest {
    /// Repo-relative path. Never absolute — the format carries no host name.
    pub path: String,
    /// The file's digest at export time, 64 lowercase hex characters.
    pub sha256: String,
    /// The file's length at export time.
    pub bytes: u64,
}

/// An authoritative artifact that was absent from the exporting checkout.
///
/// Listing these is what lets a consumer tell "this snapshot has no vtable
/// memberships" apart from "this snapshot was built where the vftable scan does
/// not exist" — two very different facts.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct AbsentInput {
    /// Repo-relative path that was looked for.
    pub path: String,
    /// Why it was not there. Never empty: "not found at this path" is a
    /// statement a consumer can act on.
    pub reason: String,
}

/// Who wrote the snapshot. The version is a constant of the program, not a build
/// stamp, so it does not vary between two runs on one machine.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Generator {
    /// The program that wrote the snapshot, `spore-semantic`.
    pub name: String,
    /// The program's version constant — not a build stamp.
    pub version: String,
}

/// The export-side facts, deliberately kept out of [`Counts`].
///
/// [`Counts`] is cross-checked against the record bodies on load, and an
/// export-side fact cannot be recomputed from them.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ExportNotes {
    /// Which universe artifact supplied canonical identity.
    pub universe_source: String,
    /// True when the git-ignored frozen Ghidra export was absent and the
    /// git-tracked coverage ledger supplied identity instead.
    pub universe_fallback: bool,
    /// How many `reconstruction/evidence/<bare8>/` directories were walked.
    pub evidence_pack_dirs_read: u64,
    /// Packs whose VA lies in no known body. They were read and hashed, and no
    /// passport can reference them; reporting the count keeps that visible
    /// instead of letting it look like they were skipped.
    pub orphan_evidence_packs: u64,
    /// Their paths, so a human can see which.
    pub orphan_evidence_pack_paths: Vec<String>,
}

/// The coverage counters the header declares.
///
/// These are recomputable from the record bodies, so [`crate::Snapshot::verify`]
/// cross-checks them: a hand-edited header is caught even when the content
/// digest still matches.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct Counts {
    /// How many function records the body holds.
    pub functions: i64,
    /// Records carrying `names.sdk_name` — 1 171 on the current checkout.
    pub with_sdk_name: i64,
    /// Records whose ABI record states a convention.
    pub with_abi_data: i64,
    /// Records whose ABI record exists and whose convention is `null`.
    pub with_abi_unknown: i64,
    /// Records whose receiver is `"true"`.
    pub with_receiver: i64,
    /// Records whose receiver is `"null"` — the abstaining case.
    pub with_receiver_unknown: i64,
    /// Records with at least one sound-scan vftable membership.
    pub with_vtable_membership: i64,
    /// Records where a VFT inference rule fired.
    pub with_vtable_attributed: i64,
    /// Records whose `classification.subsystem` is non-null. Note that 49 340 of
    /// them carry the literal string `Unknown` — see `crate::claims`.
    pub with_subsystem: i64,
    /// Records the triage classifier assigned to RenderWare.
    pub with_renderware_role: i64,
    /// Records with a named reconstruction package.
    pub with_reconstruction_package: i64,
    /// Records a promotion marker exists for.
    pub with_promotion: i64,
    /// Records with an evidence pack at their own VA.
    pub with_evidence_pack: i64,
    /// Records carrying a validation report.
    pub with_validation: i64,
    /// Records with a semantic research record.
    pub with_semantics: i64,
    /// Records with at least one global reference.
    pub with_globals: i64,
    /// Records with at least one associated type.
    pub with_types: i64,
    /// Records with at least one inbound call edge.
    pub with_callers: i64,
    /// Records with at least one outbound call edge, internal or external.
    pub with_callees: i64,
    /// Records whose derived name a worker refuted.
    pub with_refuted_identity: i64,
    /// Non-entry addresses the exporter has already mapped onto an entry.
    pub resolved_interior_addresses: i64,
    /// Evidence packs filed under a non-entry VA, attached to the entry whose
    /// body contains them.
    pub attached_stray_evidence_packs: i64,
    /// The number that answers "how much of this snapshot is a stated *we looked
    /// and found nothing*".
    pub explicitly_unavailable: i64,
    /// The denominator for the ratio above: seven fact groups per passport.
    pub total_fact_groups: i64,
}

/// Line 1 of the snapshot.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Metadata {
    /// The schema id this build implements.
    pub schema: String,
    /// Which binary the facts describe.
    pub binary: BinaryIdentity,
    /// Who wrote the file.
    pub generator: Generator,
    /// Every repo-relative file the export read, with its digest.
    pub inputs: Vec<InputDigest>,
    /// Authoritative artifacts that were absent from the exporting checkout.
    pub absent_inputs: Vec<AbsentInput>,
    /// The coverage counters, cross-checked against the body.
    pub counts: Counts,
    /// SHA-256 over the record lines only. Line 1 is excluded, so the field is
    /// not self-referential.
    pub content_sha256: String,
    /// What the write did, which the record bodies cannot show.
    pub export: ExportNotes,
}

impl Metadata {
    pub(crate) fn parse(
        path: &std::path::Path,
        line: usize,
        obj: &Obj<'_>,
    ) -> Result<Self, BridgeError> {
        let fail = |detail: String| BridgeError::UnsupportedSchema {
            path: path.to_path_buf(),
            line,
            detail,
        };
        let record = obj.req_str("record").map_err(|e| fail(e.to_string()))?;
        if record != "metadata" {
            return Err(BridgeError::corrupt(
                path,
                line,
                format!("first record is {record:?}, expected \"metadata\""),
            ));
        }
        let schema = obj.req_str("schema").map_err(|e| fail(e.to_string()))?;
        if schema != SNAPSHOT_SCHEMA {
            return Err(BridgeError::schema(
                path,
                line,
                format!(
                    "declares schema {schema:?}; this build implements {SNAPSHOT_SCHEMA:?} and \
                     nothing else, because a consumer must not read a future schema as if it were \
                     today's"
                ),
            ));
        }

        let binary = obj
            .req("binary")
            .and_then(|v| v.as_object())
            .map_err(|e| fail(e.to_string()))?;
        let sha256 = binary
            .req_str("binary_sha256")
            .map_err(|e| fail(e.to_string()))?;
        if sha256.len() != 64
            || !sha256
                .bytes()
                .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
        {
            return Err(BridgeError::corrupt(
                path,
                line,
                format!(
                    "binary.binary_sha256 is {sha256:?}, which is not 64 lowercase hex characters; \
                     a snapshot without a usable binary identity is not addressable"
                ),
            ));
        }
        let image_base_text = binary
            .req_str("image_base")
            .map_err(|e| fail(e.to_string()))?;
        let image_base = match Va::parse_canonical(image_base_text) {
            Ok(va) => va.as_u32(),
            Err(error @ AddressError::NotCanonical { .. }) => {
                return Err(BridgeError::corrupt(
                    path,
                    line,
                    format!("binary.image_base: {error}"),
                ))
            }
            Err(error) => return Err(BridgeError::address("binary.image_base", error)),
        };

        let generator = obj
            .req("generator")
            .and_then(|v| v.as_object())
            .map_err(|e| fail(e.to_string()))?;
        let inputs_obj = obj.req("inputs").map_err(|e| fail(e.to_string()))?;
        let mut inputs = Vec::new();
        if let Ok(items) = inputs_obj.as_array() {
            for item in items {
                let entry = item.as_object().map_err(|e| fail(e.to_string()))?;
                inputs.push(InputDigest {
                    path: entry
                        .req_str("path")
                        .map_err(|e| fail(e.to_string()))?
                        .to_owned(),
                    sha256: entry
                        .req_str("sha256")
                        .map_err(|e| fail(e.to_string()))?
                        .to_owned(),
                    bytes: non_negative(entry.req_int("bytes").map_err(|e| fail(e.to_string()))?),
                });
            }
        }
        let mut absent_inputs = Vec::new();
        if let Ok(items) = obj
            .req("absent_inputs")
            .map_err(|e| fail(e.to_string()))?
            .as_array()
        {
            for item in items {
                let entry = item.as_object().map_err(|e| fail(e.to_string()))?;
                absent_inputs.push(AbsentInput {
                    path: entry
                        .req_str("path")
                        .map_err(|e| fail(e.to_string()))?
                        .to_owned(),
                    reason: entry
                        .req_str("reason")
                        .map_err(|e| fail(e.to_string()))?
                        .to_owned(),
                });
            }
        }

        let counts_obj = obj
            .req("counts")
            .and_then(|v| v.as_object())
            .map_err(|e| fail(e.to_string()))?;
        let counts = Counts {
            functions: counter(counts_obj, "functions"),
            with_sdk_name: counter(counts_obj, "with_sdk_name"),
            with_abi_data: counter(counts_obj, "with_abi_data"),
            with_abi_unknown: counter(counts_obj, "with_abi_unknown"),
            with_receiver: counter(counts_obj, "with_receiver"),
            with_receiver_unknown: counter(counts_obj, "with_receiver_unknown"),
            with_vtable_membership: counter(counts_obj, "with_vtable_membership"),
            with_vtable_attributed: counter(counts_obj, "with_vtable_attributed"),
            with_subsystem: counter(counts_obj, "with_subsystem"),
            with_renderware_role: counter(counts_obj, "with_renderware_role"),
            with_reconstruction_package: counter(counts_obj, "with_reconstruction_package"),
            with_promotion: counter(counts_obj, "with_promotion"),
            with_evidence_pack: counter(counts_obj, "with_evidence_pack"),
            with_validation: counter(counts_obj, "with_validation"),
            with_semantics: counter(counts_obj, "with_semantics"),
            with_globals: counter(counts_obj, "with_globals"),
            with_types: counter(counts_obj, "with_types"),
            with_callers: counter(counts_obj, "with_callers"),
            with_callees: counter(counts_obj, "with_callees"),
            with_refuted_identity: counter(counts_obj, "with_refuted_identity"),
            resolved_interior_addresses: counter(counts_obj, "resolved_interior_addresses"),
            attached_stray_evidence_packs: counter(counts_obj, "attached_stray_evidence_packs"),
            explicitly_unavailable: counter(counts_obj, "explicitly_unavailable"),
            total_fact_groups: counter(counts_obj, "total_fact_groups"),
        };

        let export = obj
            .req("export")
            .and_then(|v| v.as_object())
            .map_err(|e| fail(e.to_string()))?;
        let export_notes = ExportNotes {
            universe_source: export
                .req_str("universe_source")
                .map_err(|e| fail(e.to_string()))?
                .to_owned(),
            universe_fallback: export
                .req_bool("universe_fallback")
                .map_err(|e| fail(e.to_string()))?,
            evidence_pack_dirs_read: non_negative(
                export
                    .req_int("evidence_pack_dirs_read")
                    .map_err(|e| fail(e.to_string()))?,
            ),
            orphan_evidence_packs: non_negative(
                export
                    .req_int("orphan_evidence_packs")
                    .map_err(|e| fail(e.to_string()))?,
            ),
            orphan_evidence_pack_paths: export
                .opt_str_array("orphan_evidence_pack_paths")
                .map_err(|e| fail(e.to_string()))?
                .into_iter()
                .map(str::to_owned)
                .collect(),
        };

        let content_sha256 = obj
            .req_str("content_sha256")
            .map_err(|e| fail(e.to_string()))?
            .to_owned();
        if content_sha256.len() != 64
            || !content_sha256
                .bytes()
                .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
        {
            return Err(BridgeError::corrupt(
                path,
                line,
                format!(
                    "content_sha256 is {content_sha256:?}, which is not 64 lowercase hex characters"
                ),
            ));
        }

        Ok(Self {
            schema: schema.to_owned(),
            binary: BinaryIdentity {
                sha256: sha256.to_owned(),
                image_base,
                architecture: binary
                    .req_str("architecture")
                    .map_err(|e| fail(e.to_string()))?
                    .to_owned(),
                program: binary
                    .req_str("program")
                    .map_err(|e| fail(e.to_string()))?
                    .to_owned(),
                version: binary
                    .req_str("version")
                    .map_err(|e| fail(e.to_string()))?
                    .to_owned(),
            },
            generator: Generator {
                name: generator
                    .req_str("name")
                    .map_err(|e| fail(e.to_string()))?
                    .to_owned(),
                version: generator
                    .req_str("version")
                    .map_err(|e| fail(e.to_string()))?
                    .to_owned(),
            },
            inputs,
            absent_inputs,
            counts,
            content_sha256,
            export: export_notes,
        })
    }
}

/// Reads one counter. Every counter is declared required by the schema and its
/// shape is checked during parsing, so this cannot fail; the fallback keeps the
/// accessor total rather than panicking if a spec and this list ever diverge.
fn counter(obj: &Obj<'_>, key: &str) -> i64 {
    obj.req_int(key).unwrap_or(0)
}

fn non_negative(value: i64) -> u64 {
    u64::try_from(value).unwrap_or(0)
}
