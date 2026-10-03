//! The shape of a *real* gmdl record, from the committed semantic snapshot.
//!
//! `tests/expected/real_gmdl_1006.json` is a semantic snapshot (no asset bytes)
//! of gmdl record 1006 of `SPORE/Data/Spore_Content.package`, captured by the
//! repository's Python oracle. `SPORE/` is git-ignored, so the 80 raw bytes are
//! NOT available here and this file cannot decode the real record. What it can
//! do is:
//!
//! 1. rebuild a synthetic record carrying **exactly those 19 semantic values**,
//!    and check that this decoder recovers all of them - which pins the semantic
//!    surface against a real record without needing its bytes;
//! 2. assert that the rebuilt record is 80 bytes and that its walk lands on that
//!    same offset, which is the `parseMatchesFile: true` /
//!    `finalOffset == fileBytes` fact the snapshot records;
//! 3. assert that every key in the snapshot's `semantics` object is accounted
//!    for by this crate, either by an accessor or by an explicit reason. If the
//!    snapshot grows a field, this fails until someone decides what it means for
//!    this decoder.
//!
//! The floats are rounded to 4 decimal places in the snapshot, so the rebuilt
//! record's bytes are *not* the real record's bytes. Every value below is
//! written from the snapshot verbatim, and the test that matters is that the
//! decoder reads back what was written.

mod common;

use common::{Builder, Trailer};
use spore_core::WILDCARD;
use spore_gmdl::{parse, GMDL_TYPE};

/// The 19 semantic fields of the committed snapshot, in the snapshot's spelling.
const SNAPSHOT_FIELDS: &[&str] = &[
    "animDataCount",
    "bboxMax",
    "bboxMin",
    "boneRangeCount",
    "fileBytes",
    "finalOffset",
    "indexBuffers",
    "materialIDs",
    "materialInfoCount",
    "meshCount",
    "meshes",
    "parseMatchesFile",
    "radius",
    "refCount",
    "refs",
    "unknownKey",
    "version",
    "vertexBuffers",
    "vertexDescriptors",
];

/// Extracts the `"key":` lines of the snapshot's `semantics` object.
fn snapshot_semantic_keys() -> Vec<String> {
    let path = common::real_record_json_path();
    let text = std::fs::read_to_string(&path)
        .unwrap_or_else(|error| panic!("cannot read {}: {error}", path.display()));
    let mut keys = Vec::new();
    let mut inside = false;
    for line in text.lines() {
        let trimmed = line.trim();
        if !inside {
            inside = trimmed.starts_with("\"semantics\"");
            continue;
        }
        // The object ends at its own closing brace; nested arrays close with `]`
        // and are not keys.
        if trimmed.starts_with('}') {
            break;
        }
        // Anything that is not a key (array elements, nested braces) is skipped.
        let Some(rest) = trimmed.strip_prefix('"') else {
            continue;
        };
        let Some((key, _)) = rest.split_once('"') else {
            continue;
        };
        keys.push(key.to_string());
    }
    keys.sort();
    keys
}

#[test]
fn the_snapshot_has_exactly_the_fields_this_test_maps() {
    let keys = snapshot_semantic_keys();
    let mut expected: Vec<String> = SNAPSHOT_FIELDS
        .iter()
        .map(|key| (*key).to_string())
        .collect();
    expected.sort();
    assert_eq!(
        keys, expected,
        "the committed snapshot's semantics object changed; map the new field or drop it from SNAPSHOT_FIELDS"
    );
    assert_eq!(keys.len(), 19, "the snapshot has 19 semantic fields");
}

#[test]
fn every_snapshot_field_is_accounted_for_by_this_crate() {
    // The point of the mapping: no field of the real-record snapshot may be
    // silently dropped. `docs/ASSET-PATH.md` grades each stage, and a field with
    // no home here is a field this decoder quietly ignores.
    const MAPPED: &[(&str, &str)] = &[
        (
            "animDataCount",
            "the walk consumes anim data to reach the trailing key",
        ),
        ("bboxMax", "GmdlModel::bounds_max"),
        ("bboxMin", "GmdlModel::bounds_min"),
        ("boneRangeCount", "GmdlModel::bone_ranges.len()"),
        (
            "fileBytes",
            "the caller's slice length; GmdlModel::consumed",
        ),
        ("finalOffset", "GmdlModel::strict_consumed"),
        ("indexBuffers", "GmdlModel::index_buffers"),
        ("materialIDs", "GmdlModel::material_ids"),
        (
            "materialInfoCount",
            "not stored: decoded in place into GmdlModel::texture_refs",
        ),
        ("meshCount", "GmdlModel::mesh_count"),
        ("meshes", "GmdlModel::meshes"),
        ("parseMatchesFile", "GmdlModel::fully_walked()"),
        ("radius", "GmdlModel::radius"),
        ("refCount", "GmdlModel::referenced_files.len()"),
        ("refs", "GmdlModel::referenced_files"),
        ("unknownKey", "GmdlModel::unknown_key"),
        (
            "version",
            "GmdlModel::version, always SUPPORTED_VERSION after a parse",
        ),
        ("vertexBuffers", "GmdlModel::vertex_buffers"),
        ("vertexDescriptors", "GmdlModel::descriptors"),
    ];
    let keys = snapshot_semantic_keys();
    let mapped: Vec<String> = MAPPED.iter().map(|(key, _)| (*key).to_string()).collect();
    for key in &keys {
        assert!(
            mapped.contains(key),
            "snapshot field {key:?} has no mapping in this file"
        );
    }
    assert_eq!(
        mapped.len(),
        keys.len(),
        "a mapping names a field the snapshot no longer has"
    );
}

#[test]
fn a_rebuilt_record_with_the_snapshots_values_reads_back_identically() {
    // The snapshot's values for gmdl record 1006: version 8, refCount 0,
    // meshCount 0, the bounds and radius below, no buffers of any kind, no
    // material info, no bone ranges, no anim data, and an unknown key of
    // (0, 0xFFFFFFFF, 0).
    let record = Builder::empty_mesh()
        .bounds(
            [0.1676, 0.4499, -0.6402],
            [0.1798, 0.4499, 16.4433],
            16.4503,
        )
        .trailer(Trailer::Full {
            bone_ranges: Vec::new(),
            anim_datas: Vec::new(),
            unknown_key: [0, WILDCARD, 0],
        })
        .build();

    // fileBytes 80 and finalOffset 80: the rebuilt record is byte-for-byte the
    // size the snapshot recorded, which is only possible because the section list
    // is exactly the one the oracle walked.
    assert_eq!(record.len(), 80);

    let model = parse(&record).expect("the rebuilt record parses");

    assert_eq!(model.version, 8);
    assert_eq!(model.version, spore_gmdl::SUPPORTED_VERSION);
    assert_eq!(model.mesh_count, 0);
    assert_eq!(model.referenced_files.len(), 0);
    assert!(model.meshes.is_empty());
    assert!(model.index_buffers.is_empty());
    assert!(model.descriptors.is_empty());
    assert!(model.vertex_buffers.is_empty());
    assert!(model.material_ids.is_empty());
    assert!(model.texture_refs.is_empty());
    assert!(model.bone_ranges.is_empty());

    // bboxMin [0.1676, 0.4499, -0.6402], bboxMax [0.1798, 0.4499, 16.4433],
    // radius 16.4503 - each within the snapshot's 4-decimal rounding.
    for (seen, expected) in model.bounds_min.iter().zip([0.1676f32, 0.4499, -0.6402]) {
        assert!((seen - expected).abs() <= 1e-4, "{seen} vs {expected}");
    }
    for (seen, expected) in model.bounds_max.iter().zip([0.1798f32, 0.4499, 16.4433]) {
        assert!((seen - expected).abs() <= 1e-4, "{seen} vs {expected}");
    }
    assert!((model.radius - 16.4503).abs() <= 1e-4, "{}", model.radius);

    assert_eq!(model.unknown_key, [0, WILDCARD, 0]);
    assert_eq!(model.consumed, 80, "fileBytes");
    assert_eq!(model.strict_consumed, 80, "finalOffset");
    assert!(model.fully_walked(), "parseMatchesFile");

    // The middle word being the wildcard is an observation, not a coincidence:
    // `0xFFFFFFFF` is exactly spore_core::WILDCARD, which is how a record spells
    // "some group of this type". It is preserved rather than normalised.
    assert_eq!(model.unknown_key[1], spore_core::WILDCARD);
}

#[test]
fn the_snapshot_record_type_is_the_constant_this_crate_exports() {
    // The snapshot's own `typeID` is 15121637 == 0x00E6BCE5.
    assert_eq!(GMDL_TYPE, 0x00E6_BCE5);
    assert_eq!(GMDL_TYPE, 15_121_637);
    assert_eq!(spore_core::RecordType::new(GMDL_TYPE).name(), Some("gmdl"));
    assert_eq!(
        spore_core::fourcc(GMDL_TYPE).as_deref(),
        Some("____"),
        "not a printable four-character code"
    );
}

#[test]
fn every_prefix_of_the_rebuilt_record_answers() {
    let record = Builder::empty_mesh()
        .bounds(
            [0.1676, 0.4499, -0.6402],
            [0.1798, 0.4499, 16.4433],
            16.4503,
        )
        .build();
    for len in 0..=record.len() {
        let prefix = record.get(..len).expect("prefix");
        if let Ok(model) = parse(prefix) {
            assert_eq!(model.consumed, len);
        }
    }
}
