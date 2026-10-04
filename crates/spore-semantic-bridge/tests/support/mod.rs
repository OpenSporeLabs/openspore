//! Shared fixtures for the integration tests.
//!
//! Everything here is **synthetic**. No Spore asset byte and no committed
//! snapshot line is copied into a test: the synthetic records are written by
//! hand from the schema, and the committed 98 MB artifact is only ever *read*,
//! and only by the tests that are explicitly about it.

#![allow(dead_code)]

use std::path::{Path, PathBuf};

/// A temporary file that removes itself.
///
/// Hand-rolled because this crate's test dependencies are `spore-core` and
/// `thiserror` and nothing else — no `tempfile`.
pub struct TempFile {
    path: PathBuf,
}

impl TempFile {
    /// Writes `contents` to a uniquely named temporary file.
    pub fn new(label: &str, contents: &str) -> Self {
        let mut path = std::env::temp_dir();
        path.push(format!(
            "spore-semantic-bridge-{label}-{}-{:p}.jsonl",
            std::process::id(),
            &contents
        ));
        std::fs::write(&path, contents).expect("the temporary fixture is writable");
        Self { path }
    }

    pub fn path(&self) -> &Path {
        &self.path
    }
}

impl Drop for TempFile {
    fn drop(&mut self) {
        let _ = std::fs::remove_file(&self.path);
    }
}

/// The metadata line, with every counter a synthetic file might need.
///
/// `content_sha256` is a placeholder by default: no synthetic test needs a real
/// digest, and the one that checks the digest path asserts the mismatch.
pub fn metadata_line(functions: usize, content_sha256: &str) -> String {
    let counts = [
        ("functions", functions),
        ("with_sdk_name", 0),
        ("with_abi_data", 0),
        ("with_abi_unknown", 0),
        ("with_receiver", 0),
        ("with_receiver_unknown", 0),
        ("with_vtable_membership", 0),
        ("with_vtable_attributed", 0),
        ("with_subsystem", 0),
        ("with_renderware_role", 0),
        ("with_reconstruction_package", 0),
        ("with_promotion", 0),
        ("with_evidence_pack", 0),
        ("with_validation", 0),
        ("with_semantics", 0),
        ("with_globals", 0),
        ("with_types", 0),
        ("with_callers", 0),
        ("with_callees", 0),
        ("with_refuted_identity", 0),
        ("resolved_interior_addresses", 0),
        ("attached_stray_evidence_packs", 0),
        ("explicitly_unavailable", 0),
        ("total_fact_groups", 0),
    ];
    let counters = counts
        .iter()
        .map(|(key, value)| format!("\"{key}\":{value}"))
        .collect::<Vec<_>>()
        .join(",");
    let header = concat!(
        r#"{"record":"metadata","schema":"spore-semantic-snapshot-1","#,
        r#""binary":{"binary_sha256":"25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e","#,
        r#""image_base":"0x00400000","architecture":"x86:LE:32","program":"SporeApp.exe","version":"3.1.0.22"},"#,
        r#""generator":{"name":"spore-semantic","version":"1"},"inputs":[],"absent_inputs":[],"#,
        r#""counts":{COUNTERS},"content_sha256":"DIGEST","#,
        r#""export":{"universe_source":".spore-analysis/ghidra-exports/functions.tsv","#,
        r#""universe_fallback":false,"evidence_pack_dirs_read":0,"orphan_evidence_packs":0,"#,
        r#""orphan_evidence_pack_paths":[]}}"#,
    );
    header
        .replace("COUNTERS", &counters)
        .replace("DIGEST", content_sha256)
}

/// A minimal, fully valid function record.
///
/// Every fact group is published as an explicit absence and every optional list
/// is omitted, which is the shape 58 085 of the committed records actually have.
pub fn record(va: &str, rva: &str, size: i64) -> String {
    format!(
        concat!(
            r#"{{"record":"function","#,
            r#""identity":{{"canonical_va":"{va}","rva":"{rva}","size":{size},"size_known":true,"#,
            r#""is_thunk":false,"section":".text","identity_resolution":null}},"#,
            r#""names":{{"ghidra_name":"FUN_{bare}","normalized_symbol":"FUN_{bare}","sdk_name":null,"#,
            r#""identity_refuted":null}},"#,
            r#""classification":{{"category":"ENGINE_IMPLEMENTATION","priority":"P3","evidence":"INFERRED","#,
            r#""subsystem":"App","cluster":null,"renderware_role":null,"subsystem_source":"triage_jsonl"}},"#,
            r#""abi":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_evidence_pack"}},"#,
            r#""vtable":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_vtable_membership"}},"#,
            r#""graph":{{"caller_count":0,"callee_count":0,"vtable_reference_count":0,"data_reference_count":0}},"#,
            r#""globals":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_global_references"}},"#,
            r#""types":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_associated_types"}},"#,
            r#""semantics":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_semantic_record"}},"#,
            r#""reconstruction":{{"state":"unavailable","evidence_level":"UNKNOWN","evidence_state":"MISSING","#,
            r#""reason":"no_reconstruction_package"}},"#,
            r#""evidence":{{"pack":null,"pack_state":null,"pack_content_sha256":null,"#,
            r#""target_address_kind":null,"validation_report":null,"promotion_record":null}}}}"#
        ),
        va = va,
        rva = rva,
        size = size,
        bare = va.trim_start_matches("0x"),
    )
}

/// Assembles a whole snapshot file from record lines.
pub fn snapshot_file(records: &[String]) -> String {
    let mut out = metadata_line(records.len(), &"0".repeat(64));
    out.push('\n');
    for record in records {
        out.push_str(record);
        out.push('\n');
    }
    out
}

/// Two entries far enough apart to leave a gap, for the canonicalization rules.
pub fn two_entry_file() -> TempFile {
    TempFile::new(
        "two-entry",
        &snapshot_file(&[
            record("0x00401000", "0x00001000", 0x4a),
            record("0x004010c0", "0x000010c0", 0x20),
        ]),
    )
}

/// A snapshot plus the temporary file it reads.
///
/// The [`Snapshot`] deliberately holds a *path*, not an open handle, so the file
/// has to outlive it — and a fixture that deleted itself at the end of `open()`
/// would have turned every later lookup into a `NotFound`. Returning both is the
/// honest shape, and it documents the lifetime rule for real callers too.
pub struct Fixture {
    pub file: TempFile,
    pub snapshot: Result<spore_semantic_bridge::Snapshot, spore_semantic_bridge::BridgeError>,
}

impl Fixture {
    /// The opened snapshot, panicking with the typed error on failure.
    pub fn snapshot(&self) -> &spore_semantic_bridge::Snapshot {
        self.opened()
            .unwrap_or_else(|error| panic!("the fixture must open: {error}"))
    }

    /// The opened snapshot, or the typed error it refused with.
    pub fn opened(
        &self,
    ) -> Result<&spore_semantic_bridge::Snapshot, spore_semantic_bridge::BridgeError> {
        // Cloning the error out keeps the borrow tied to the fixture, which is
        // what has to outlive the snapshot anyway.
        match &self.snapshot {
            Ok(snapshot) => Ok(snapshot),
            Err(error) => Err(clone_error(error)),
        }
    }
}

/// Rebuilds an error so a fixture can hand it out by value.
fn clone_error(error: &spore_semantic_bridge::BridgeError) -> spore_semantic_bridge::BridgeError {
    use spore_semantic_bridge::BridgeError;
    match error {
        BridgeError::SnapshotUnavailable { path } => {
            BridgeError::SnapshotUnavailable { path: path.clone() }
        }
        BridgeError::Corrupt { path, line, detail } => BridgeError::Corrupt {
            path: path.clone(),
            line: *line,
            detail: detail.clone(),
        },
        BridgeError::UnsupportedSchema { path, line, detail } => BridgeError::UnsupportedSchema {
            path: path.clone(),
            line: *line,
            detail: detail.clone(),
        },
        BridgeError::ContentDigestMismatch {
            path,
            declared,
            computed,
        } => BridgeError::ContentDigestMismatch {
            path: path.clone(),
            declared: declared.clone(),
            computed: computed.clone(),
        },
        BridgeError::RecordCountMismatch {
            path,
            declared,
            computed,
        } => BridgeError::RecordCountMismatch {
            path: path.clone(),
            declared: *declared,
            computed: *computed,
        },
        BridgeError::BinaryMismatch { snapshot, required } => BridgeError::BinaryMismatch {
            snapshot: snapshot.clone(),
            required: required.clone(),
        },
        BridgeError::UnknownFunction {
            requested,
            image_base,
            indexed,
        } => BridgeError::UnknownFunction {
            requested: *requested,
            image_base: *image_base,
            indexed: *indexed,
        },
        BridgeError::UnknownSymbol { name } => BridgeError::UnknownSymbol { name: name.clone() },
        BridgeError::AmbiguousSymbol { name, matches } => BridgeError::AmbiguousSymbol {
            name: name.clone(),
            matches: *matches,
        },
        BridgeError::NonCanonicalVa { path, source } => BridgeError::NonCanonicalVa {
            path: path.clone(),
            source: source.clone(),
        },
        BridgeError::Io { path, .. } => BridgeError::SnapshotUnavailable { path: path.clone() },
        other => panic!("unhandled error variant in the test helper: {other:?}"),
    }
}

/// Opens a fixture over exactly these record lines.
pub fn fixture(records: &[String]) -> Fixture {
    let file = TempFile::new("strict", &snapshot_file(records));
    let snapshot = spore_semantic_bridge::Snapshot::open(file.path());
    Fixture { file, snapshot }
}

/// Opens a fixture over one record line.
pub fn one(body: &str) -> Fixture {
    fixture(&[body.to_owned()])
}

/// The location of the committed 98 MB snapshot, or `None` when absent.
///
/// The artifact is optional, so every test that reads it skips loudly rather
/// than failing: a machine without the file must still run this suite green,
/// and one that silently passed without testing anything would be worse.
pub fn committed_path() -> Option<PathBuf> {
    let mut roots: Vec<PathBuf> = Vec::new();
    if let Some(root) = std::env::var_os("OPENSPORE_ROOT") {
        roots.push(PathBuf::from(root));
    }
    let mut cursor = std::env::current_dir().ok();
    while let Some(dir) = cursor {
        roots.push(dir.clone());
        cursor = dir.parent().map(Path::to_path_buf);
    }
    roots
        .into_iter()
        .map(|root| root.join("knowledge/semantic/function-passport-v1.jsonl"))
        .find(|candidate| candidate.is_file())
}
