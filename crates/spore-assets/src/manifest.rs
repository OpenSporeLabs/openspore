//! The canonical asset manifest.
//!
//! One row per record, keyed on `(type, group, instance)`, sorted ascending.
//! This is a Rust port of `tools/spore/manifest/manifest.py`, which is the
//! C++-era equivalent (`docs/ASSET-IMPORT-ROADMAP.md` §3.1).
//!
//! # Why determinism is the whole point
//!
//! The reference tool's own docstring says it drops and rebuilds the sidecar
//! each run, inserting rows in a stable `(type, group, instance)` order, "so a
//! double run is byte-identical (the sim_contract discipline applied to
//! data)". That is the property worth keeping: a manifest that reorders itself
//! between runs cannot be diffed, and a manifest that cannot be diffed cannot
//! be used to review an asset-pipeline change.
//!
//! Here determinism is achieved by construction rather than by sorting at the
//! end: [`ManifestBuilder`] holds rows in a `BTreeMap` keyed by
//! [`ResourceKey`], whose ordering is already strict lexicographic on
//! `(type, group, instance)`.
//!
//! # What the manifest does *not* do
//!
//! It does not decode record payloads, and it does not name instances. DBPF
//! carries no string table, so an instance id is opaque; the `semantic_owner`
//! column exists in the reference schema and is hard-coded to `UNKNOWN` there,
//! and it is [`None`] here rather than a fabricated string.

use spore_core::record::{group_name, RecordType};
use spore_core::ResourceKey;

use crate::store::ContentStore;

/// How confidently a manifest row's columns are known.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ManifestEvidence {
    /// Established against the original binary or a real record.
    Verified,
    /// Derived by reasoning, not directly observed.
    Inferred,
    /// Not known.
    Unknown,
}

impl ManifestEvidence {
    /// The canonical spelling used in the reference tool's JSON evidence map.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Verified => "VERIFIED",
            Self::Inferred => "INFERRED",
            Self::Unknown => "UNKNOWN",
        }
    }
}

/// What this build can do with a record of a given type.
///
/// The three variants are mutually exclusive and, by construction, cover every
/// type id. `Ok` is the strong claim: a per-record decoder exists in this
/// workspace. It is deliberately *not* "a decoder family exists" — that weaker
/// reading is what let the manifest and the loader contradict each other.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DecodeStatus {
    /// A per-record decoder exists in this workspace. It may still fail on a
    /// particular record; only decoding that record settles that.
    Ok,
    /// A container this build recognises, whose payload is not decoded yet.
    ContainerUndecoded,
    /// A record type with no decoder at all.
    Undecoded,
    /// A record that claims to be a model but failed to decode.
    WalkFail,
}

impl DecodeStatus {
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Ok => "ok",
            Self::ContainerUndecoded => "container-undecoded",
            Self::Undecoded => "undecoded",
            Self::WalkFail => "walk-fail",
        }
    }
}

/// One row of the manifest.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ManifestRow {
    /// `(type, group, instance)`.
    pub key: ResourceKey,
    /// The canonical type name, or `None` when this build has no name.
    pub type_name: Option<&'static str>,
    /// The canonical group name, or `None` when this build has no name.
    pub group_name: Option<&'static str>,
    /// Decompressed byte size. Read straight from the index, so it is exact.
    pub size: u32,
    /// How this record's payload is handled.
    pub decode_status: DecodeStatus,
    /// The owning subsystem, when one has been established.
    pub semantic_owner: Option<String>,
    /// How strongly `type_name` is known.
    pub type_name_evidence: ManifestEvidence,
    /// How strongly `group_name` is known.
    pub group_name_evidence: ManifestEvidence,
}

impl ManifestRow {
    /// The name to display for the type: the canonical name, or `0x%08x`.
    pub fn type_name_or_hex(&self) -> String {
        self.type_name
            .map(str::to_owned)
            .unwrap_or_else(|| format!("0x{:08x}", self.key.type_id))
    }
}

/// Type ids that are containers rather than decodable payloads.
///
/// Mirrors the reference tool's `_CONTAINERS` set.
const CONTAINER_TYPE_IDS: &[u32] = &[
    spore_core::record::type_id::PROP,
    spore_core::record::type_id::CELL_STRUCTURE,
    0x2399_BE55, // bld
    0x2468_2294, // vcl
    0x2B97_8C46, // crt
    0x3D97_A8E4, // cll
    0x055A_DA24, // cnv
];

/// Accumulates manifest rows in deterministic order.
#[derive(Debug, Default)]
pub struct ManifestBuilder {
    rows: std::collections::BTreeMap<ResourceKey, ManifestRow>,
}

impl ManifestBuilder {
    /// An empty builder.
    pub fn new() -> Self {
        Self::default()
    }

    /// Scans every package and produces one row per record identity.
    ///
    /// Rows are de-duplicated by identity, first package in resolution order
    /// winning -- the same rule [`ContentStore::read`] uses, so the manifest
    /// describes what the store would actually hand back.
    pub fn from_store(store: &ContentStore) -> Self {
        let mut builder = Self::new();
        for package in store.packages() {
            for entry in package.index().entries() {
                builder.insert(ManifestRow {
                    key: entry.key,
                    type_name: RecordType::new(entry.type_id).name(),
                    group_name: group_name(entry.group_id),
                    size: entry.memory_size,
                    decode_status: classify_decode_status(entry.type_id),
                    semantic_owner: None,
                    type_name_evidence: evidence_for_type(entry.type_id),
                    group_name_evidence: evidence_for_group(entry.group_id),
                });
            }
        }
        builder
    }

    /// Adds a row unless its identity is already present.
    ///
    /// Returns `true` when the row was added, `false` when a row for that
    /// identity was already held -- in which case the **first** row is kept,
    /// matching the store's first-package-wins resolution.
    pub fn insert(&mut self, row: ManifestRow) -> bool {
        match self.rows.entry(row.key) {
            std::collections::btree_map::Entry::Occupied(_) => false,
            std::collections::btree_map::Entry::Vacant(slot) => {
                slot.insert(row);
                true
            }
        }
    }

    /// How many distinct identities are held.
    pub fn len(&self) -> usize {
        self.rows.len()
    }

    /// Whether the manifest is empty.
    pub fn is_empty(&self) -> bool {
        self.rows.is_empty()
    }

    /// The rows, ascending by `(type, group, instance)`.
    pub fn rows(&self) -> impl Iterator<Item = &ManifestRow> {
        self.rows.values()
    }

    /// The rows as an owned vector in ascending order.
    pub fn into_rows(self) -> Vec<ManifestRow> {
        self.rows.into_values().collect()
    }

    /// Counts by decode status, for a coverage summary.
    pub fn decode_status_counts(&self) -> std::collections::BTreeMap<&'static str, usize> {
        let mut counts = std::collections::BTreeMap::new();
        for row in self.rows.values() {
            *counts.entry(row.decode_status.as_str()).or_insert(0) += 1;
        }
        counts
    }

    /// Counts by canonical type name (`None` bucketed as `"0x%08x"` is not
    /// possible here without allocation, so unknown types share one bucket).
    pub fn type_counts(&self) -> std::collections::BTreeMap<String, usize> {
        let mut counts = std::collections::BTreeMap::new();
        for row in self.rows.values() {
            let name = match row.type_name {
                Some(name) => name.to_owned(),
                None => String::from("<unnamed>"),
            };
            *counts.entry(name).or_insert(0) += 1;
        }
        counts
    }
}

fn evidence_for_type(type_id: u32) -> ManifestEvidence {
    if RecordType::new(type_id).is_known() {
        ManifestEvidence::Verified
    } else {
        ManifestEvidence::Inferred
    }
}

fn evidence_for_group(group_id: u32) -> ManifestEvidence {
    if group_name(group_id).is_some() {
        ManifestEvidence::Verified
    } else {
        ManifestEvidence::Unknown
    }
}

/// The decode status implied by a record's type alone.
///
/// This is a **type-level** statement: "this build has a decoder family for
/// this type". It is not a statement that any particular record decoded. A
/// record that claims to be a model can still fail, and the only honest way to
/// find out is to decode it -- or, cheaply, to [`probe_gmdl`] its header.
fn classify_decode_status(type_id: u32) -> DecodeStatus {
    if CONTAINER_TYPE_IDS.contains(&type_id) {
        return DecodeStatus::ContainerUndecoded;
    }
    // `Ok` means exactly one thing: **this workspace has a per-record decoder
    // for this type id**. Not "there is a family of formats it resembles", and
    // not "a neighbouring id has one".
    //
    // The list is deliberately short and deliberately agrees with
    // `ModelStore::load` / `TextureStore::load`, so a manifest row and a
    // `verify` run can never contradict each other. Types that were here once
    // and were removed because nothing decodes them:
    //
    // * `png` (0x2F7D0004) and `jpeg` (0x2F7D0002) -- these are **raw PNG and
    //   raw JPEG**, measured 10 487 of 10 487 carrying the PNG magic across
    //   every installed package. An earlier revision of this file claimed they
    //   were RW4 containers and listed them as decodable. Both halves were wrong,
    //   and the manifest advertised decodability the workspace never had.
    // * `gmsh` (0x01C135DA) -- a RenderWare mesh *section*, not a gmdl record.
    //   Routing it to `spore-gmdl` would refuse it or misread it.
    // * `plt` (0x011989B7) -- a palette. Nothing in the workspace decodes one.
    const DECODED: &[u32] = &[
        spore_gmdl::GMDL_TYPE,
        spore_rw4::RW4_TYPE,
        spore_texture::RASTER_TYPE,
    ];
    if DECODED.contains(&type_id) {
        DecodeStatus::Ok
    } else {
        DecodeStatus::Undecoded
    }
}

/// Probes a record's leading bytes for a plausible GMDL header.
///
/// # The bytes must already be decompressed
///
/// Every `gmdl` record in the installed content package is QFS-compressed, so
/// probing the *stored* bytes reads compression tokens and finds nothing. This
/// function must be handed the record **after**
/// [`spore_dbpf::extract_record`](spore_dbpf::extract_record). The reference
/// tool `tools/spore/manifest/manifest.py` makes exactly that mistake, which is
/// why it reports `walk-fail` for all 4209 gmdl records in `Spore_Content`.
///
/// Returns [`DecodeStatus::WalkFail`] when the version word is not the one
/// `spore_gmdl` supports, the big-endian reference count is implausible, or the
/// mesh count is out of range.
///
/// This is a *smoke test on the header*, not a decode: a record can pass here
/// and still fail [`spore_gmdl::parse`].
pub fn probe_gmdl(data: &[u8]) -> DecodeStatus {
    let Some(version) = data.get(0..4) else {
        return DecodeStatus::WalkFail;
    };
    let version = u32::from_le_bytes([version[0], version[1], version[2], version[3]]);
    // `spore_gmdl::SUPPORTED_VERSION`, not a range. The reference tool accepts
    // `1..=4`, which no real gmdl record in this corpus has -- the corpus is
    // entirely version 8 -- so its probe rejects 4209 of 4209 valid records.
    if version != spore_gmdl::SUPPORTED_VERSION {
        return DecodeStatus::WalkFail;
    }
    // refCount is big-endian: the only big-endian word in a gmdl record.
    let Some(rc) = data.get(4..8) else {
        return DecodeStatus::WalkFail;
    };
    let ref_count = u32::from_be_bytes([rc[0], rc[1], rc[2], rc[3]]);
    if ref_count > 10_000 {
        return DecodeStatus::WalkFail;
    }
    // The first non-reference word sits at `8 + ref_count * 12`: an 8-byte
    // header (version + refCount) followed by one 12-byte key per reference.
    // The reference tool computes `(8 + ref_count) * 12`, which multiplies the
    // header offset by the key size and therefore lands in the wrong place for
    // every record with at least one reference.
    let offset = 8usize.saturating_add((ref_count as usize).saturating_mul(12));
    let Some(mc) = data.get(offset..offset + 4) else {
        return DecodeStatus::WalkFail;
    };
    let mesh_count = u32::from_le_bytes([mc[0], mc[1], mc[2], mc[3]]);
    if mesh_count > 10_000 {
        return DecodeStatus::WalkFail;
    }
    DecodeStatus::Ok
}

#[cfg(test)]
mod regression_tests {
    use super::*;

    /// Each test here pins a bug that was found by cross-checking against the
    /// real corpus or the Python oracle. They are grouped because they share a
    /// single cause: the manifest inherited a type list from a C++-era tool
    /// without re-checking it against the bytes.
    fn store_with(records: Vec<(u32, u32, u32)>) -> ContentStore {
        // A package built in memory is overkill here; the classifier and the
        // probe are both pure functions of their inputs, so test them directly.
        let _ = records;
        ContentStore::new()
    }

    #[test]
    fn png_and_jpeg_are_not_classified_as_decodable() {
        // They are raw PNG/JPEG (measured 10 487 of 10 487 with the PNG magic)
        // and no crate here decodes them. Marking them `Ok` would advertise
        // decodability the workspace does not have.
        assert_eq!(
            classify_decode_status(0x2F7D_0004),
            DecodeStatus::Undecoded,
            "png is raw PNG and undecoded here"
        );
        assert_eq!(
            classify_decode_status(0x2F7D_0002),
            DecodeStatus::Undecoded,
            "jpeg is raw JPEG and undecoded here"
        );
    }

    #[test]
    fn rw4_is_classified_as_decodable_because_spore_rw4_decodes_it() {
        // The DECODED list omitted 0x2F4E681B while `ModelStore::load` accepts
        // it, so the manifest contradicted the loader on 1131 real records.
        assert_eq!(
            classify_decode_status(spore_rw4::RW4_TYPE),
            DecodeStatus::Ok
        );
        assert_eq!(
            classify_decode_status(spore_gmdl::GMDL_TYPE),
            DecodeStatus::Ok
        );
        assert_eq!(
            classify_decode_status(spore_texture::RASTER_TYPE),
            DecodeStatus::Ok
        );
        assert_eq!(
            classify_decode_status(spore_core::record::type_id::PROP),
            DecodeStatus::ContainerUndecoded
        );
        assert_eq!(classify_decode_status(0x1234_5678), DecodeStatus::Undecoded);
    }

    #[test]
    fn the_probe_accepts_the_version_the_decoder_actually_supports() {
        // The reference tool accepts versions 1..=4 and therefore rejects every
        // real record, because the corpus is entirely version 8.
        let mut record = vec![0u8; 64];
        record[0..4].copy_from_slice(&spore_gmdl::SUPPORTED_VERSION.to_le_bytes());
        // One big-endian reference, so meshCount lands at 8 + 1*12 = 20.
        record[4..8].copy_from_slice(&1u32.to_be_bytes());
        record[20..24].copy_from_slice(&3u32.to_le_bytes());
        assert_eq!(probe_gmdl(&record), DecodeStatus::Ok);

        // And it must reject the versions the reference tool accepted, because
        // spore_gmdl::parse does not accept them either.
        let mut v7 = record.clone();
        v7[0..4].copy_from_slice(&7u32.to_le_bytes());
        assert_eq!(probe_gmdl(&v7), DecodeStatus::WalkFail);
    }

    #[test]
    fn the_probe_reads_mesh_count_at_header_plus_references() {
        // `(8 + ref_count) * 12` -- the reference tool's arithmetic -- points at
        // 240 for ref_count == 1, where the real word is at 20. A record whose
        // mesh count is valid at 20 and garbage at 240 separates the two.
        let mut record = vec![0u8; 512];
        record[0..4].copy_from_slice(&spore_gmdl::SUPPORTED_VERSION.to_le_bytes());
        record[4..8].copy_from_slice(&1u32.to_be_bytes());
        record[20..24].copy_from_slice(&1u32.to_le_bytes());
        record[240..244].copy_from_slice(&99_999u32.to_le_bytes());
        assert_eq!(
            probe_gmdl(&record),
            DecodeStatus::Ok,
            "the probe must read 8 + ref_count*12, not (8 + ref_count)*12"
        );
    }

    #[test]
    fn the_probe_handles_zero_references_at_the_header_offset() {
        let mut record = vec![0u8; 32];
        record[0..4].copy_from_slice(&spore_gmdl::SUPPORTED_VERSION.to_le_bytes());
        record[4..8].copy_from_slice(&0u32.to_be_bytes());
        record[8..12].copy_from_slice(&2u32.to_le_bytes());
        assert_eq!(probe_gmdl(&record), DecodeStatus::Ok);
    }

    #[test]
    fn the_probe_refuses_rather_than_reading_past_a_short_record() {
        for length in 0..24usize {
            let _ = probe_gmdl(&vec![0u8; length]);
        }
        // Implausible reference count.
        let mut record = vec![0u8; 64];
        record[0..4].copy_from_slice(&spore_gmdl::SUPPORTED_VERSION.to_le_bytes());
        record[4..8].copy_from_slice(&20_000u32.to_be_bytes());
        assert_eq!(probe_gmdl(&record), DecodeStatus::WalkFail);
    }

    #[test]
    fn a_manifest_over_an_empty_store_is_empty_rather_than_absent() {
        let builder = ManifestBuilder::from_store(&store_with(Vec::new()));
        assert!(builder.is_empty());
        assert_eq!(builder.len(), 0);
    }

    #[test]
    fn rows_are_unique_and_ascending_regardless_of_insertion_order() {
        let a = ResourceKey::new(2, 0, 0);
        let b = ResourceKey::new(1, 9, 9);
        let c = ResourceKey::new(1, 2, 3);
        let mut builder = ManifestBuilder::new();
        for key in [a, b, c] {
            assert!(builder.insert(ManifestRow {
                key,
                type_name: None,
                group_name: None,
                size: 1,
                decode_status: DecodeStatus::Undecoded,
                semantic_owner: None,
                type_name_evidence: ManifestEvidence::Inferred,
                group_name_evidence: ManifestEvidence::Unknown,
            }));
        }
        let keys: Vec<ResourceKey> = builder.rows().map(|r| r.key).collect();
        assert_eq!(
            keys,
            vec![c, b, a],
            "rows must come out ascending by (type, group, instance): (1,2,3) < (1,9,9) < (2,0,0)"
        );
        assert_eq!(builder.len(), 3);

        // A duplicate identity is refused and the FIRST row is kept, matching
        // the store's first-package-wins resolution.
        assert!(!builder.insert(ManifestRow {
            key: b,
            type_name: None,
            group_name: None,
            size: 999,
            decode_status: DecodeStatus::Ok,
            semantic_owner: None,
            type_name_evidence: ManifestEvidence::Unknown,
            group_name_evidence: ManifestEvidence::Unknown,
        }));
        assert_eq!(builder.len(), 3);
        assert_eq!(builder.rows().find(|r| r.key == b).unwrap().size, 1);
    }

    #[test]
    fn an_unknown_type_name_is_none_not_a_fabricated_hex_string() {
        let row = ManifestRow {
            key: ResourceKey::new(0xDEAD_BEEF, 1, 2),
            type_name: None,
            group_name: None,
            size: 0,
            decode_status: DecodeStatus::Undecoded,
            semantic_owner: None,
            type_name_evidence: ManifestEvidence::Inferred,
            group_name_evidence: ManifestEvidence::Unknown,
        };
        assert_eq!(row.type_name, None);
        assert_eq!(row.type_name_or_hex(), "0xdeadbeef");
        // semantic_owner stays a non-finding: DBPF has no string table, so there
        // is no owner to name.
        assert_eq!(row.semantic_owner, None);
    }
}
