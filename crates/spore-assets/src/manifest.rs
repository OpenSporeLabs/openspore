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

/// Whether a record's payload was successfully decoded.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DecodeStatus {
    /// Decoded (or structurally validated) without error.
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
    // One list, not two branches that happen to agree: a type is either in the
    // set this build has a decoder family for, or it is not.
    const DECODABLE: &[u32] = &[
        spore_gmdl::GMDL_TYPE,
        0x01C1_35DA, // gmsh
        spore_texture::RASTER_TYPE,
        0x2F7D_0002, // jpeg -- an RW4 container, not raw JPEG
        0x2F7D_0004, // png  -- an RW4 container, not raw PNG
        spore_core::record::type_id::PLT,
    ];
    if DECODABLE.contains(&type_id) {
        DecodeStatus::Ok
    } else {
        DecodeStatus::Undecoded
    }
}

/// Probes a record's leading bytes for a plausible GMDL header.
///
/// Returns [`DecodeStatus::WalkFail`] when the version word is outside
/// `1..=4`, the big-endian reference count is implausible, or the mesh count
/// is out of range. This is the reference tool's `probe_gmdl`, and it is a
/// *smoke test on the header*, not a decode.
pub fn probe_gmdl(data: &[u8]) -> DecodeStatus {
    let Some(version) = data.get(0..4) else {
        return DecodeStatus::WalkFail;
    };
    let version = u32::from_le_bytes([version[0], version[1], version[2], version[3]]);
    if !(1..=4).contains(&version) {
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
    let offset = 8usize.saturating_add(ref_count as usize).saturating_mul(12);
    let Some(mc) = data.get(offset..offset + 4) else {
        return DecodeStatus::WalkFail;
    };
    let mesh_count = u32::from_le_bytes([mc[0], mc[1], mc[2], mc[3]]);
    if mesh_count > 10_000 {
        return DecodeStatus::WalkFail;
    }
    DecodeStatus::Ok
}
