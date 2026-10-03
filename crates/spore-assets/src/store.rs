//! The content store: package priority, identity resolution, record reads.
//!
//! # Package priority
//!
//! Spore ships its data as many overlapping packages (`PatchData`,
//! `Spore_Content`, `Spore_Graphics`, `Spore_EP1_Content_01`, ...). The same
//! `(type, group, instance)` identity appears in more than one of them, and
//! which copy wins is a *product* decision, not a format one. So the store
//! takes an explicit ordered list and resolves **first match wins**. There is
//! no implicit sort, no "largest package wins", and no deduplication: the
//! order the caller passes in is the order that is honoured, which makes the
//! decision auditable.
//!
//! The C++ reference only ever handled one package image per provider
//! (`docs/BOUNDARIES.md` B1 scope limit). Multi-package resolution is new
//! behaviour and is labelled as such wherever it is used.

use spore_core::ResourceKey;
use spore_dbpf::DbpfEntry;

use crate::error::AssetError;
use crate::package::Package;

/// A located record: which package answered, and the index row.
#[derive(Debug, Clone, Copy)]
pub struct RecordRef<'a> {
    /// Position of the answering package in the store's priority order.
    pub package_index: usize,
    /// The answering package's display name.
    pub package_name: &'a str,
    /// The index row.
    pub entry: &'a DbpfEntry,
}

impl<'a> RecordRef<'a> {
    /// The identity this record answers to.
    pub fn key(&self) -> ResourceKey {
        self.entry.key
    }
}

/// An ordered set of packages with first-match-wins resolution.
#[derive(Debug, Default)]
pub struct ContentStore {
    packages: Vec<Package>,
}

impl ContentStore {
    /// An empty store. Every lookup fails with [`AssetError::EmptyStore`].
    pub fn new() -> Self {
        Self {
            packages: Vec::new(),
        }
    }

    /// An empty store with room for `capacity` packages.
    pub fn with_capacity(capacity: usize) -> Self {
        Self {
            packages: Vec::with_capacity(capacity),
        }
    }

    /// Appends a package at the **lowest** priority.
    pub fn push(&mut self, package: Package) {
        self.packages.push(package);
    }

    /// Inserts a package at the **highest** priority.
    ///
    /// This is how a patch package overrides base content: load the base
    /// packages first, then `push_front` the patch.
    pub fn push_front(&mut self, package: Package) {
        self.packages.insert(0, package);
    }

    /// The packages in resolution order.
    pub fn packages(&self) -> &[Package] {
        &self.packages
    }

    /// How many packages are loaded.
    pub fn len(&self) -> usize {
        self.packages.len()
    }

    /// Whether the store holds no packages.
    pub fn is_empty(&self) -> bool {
        self.packages.is_empty()
    }

    /// The package names in resolution order, for diagnostics.
    pub fn package_names(&self) -> Vec<&str> {
        self.packages.iter().map(|p| p.name()).collect()
    }

    /// Finds the first package holding `key`.
    ///
    /// A `key` with a [`spore_core::WILDCARD`] component matches on the
    /// components that are present, so a partial identity can be used to ask
    /// "does this group contain a gmdl at all?". Wildcards resolve to the
    /// lowest package index, then to the lowest matching row in that package,
    /// so the answer is deterministic.
    pub fn find(&self, key: &ResourceKey) -> Result<RecordRef<'_>, AssetError> {
        if self.packages.is_empty() {
            return Err(AssetError::EmptyStore);
        }
        let mut candidates: Vec<ResourceKey> = Vec::new();
        for (package_index, package) in self.packages.iter().enumerate() {
            if let Some(entry) = package.index().find_matching(key) {
                return Ok(RecordRef {
                    package_index,
                    package_name: package.name(),
                    entry,
                });
            }
            // Only collect suggestions from the first package that has any
            // record of the requested type, so the hint stays small and
            // relevant instead of dumping a whole type histogram.
            if candidates.is_empty() && key.type_id != spore_core::WILDCARD {
                candidates = package
                    .index()
                    .of_type(key.type_id)
                    .take(8)
                    .map(|e| e.key)
                    .collect();
            }
        }
        Err(AssetError::NotFound {
            key: *key,
            searched: self.packages.len(),
            candidates,
        })
    }

    /// Whether any package holds `key`.
    pub fn contains(&self, key: &ResourceKey) -> bool {
        self.find(key).is_ok()
    }

    /// Extracts and decompresses the bytes of `key`.
    pub fn read(&self, key: &ResourceKey) -> Result<Vec<u8>, AssetError> {
        let found = self.find(key)?;
        spore_dbpf::extract_record(self.packages[found.package_index].bytes(), found.entry).map_err(
            |source| AssetError::Dbpf {
                package: found.package_name.to_owned(),
                source,
            },
        )
    }

    /// Extracts the bytes of `key` from one specific package, bypassing the
    /// priority order.
    ///
    /// Needed whenever a record must be read from the package that was *not*
    /// the answer -- for example a base-content model shadowed by a patch, or
    /// the same identity in two packages during a differential comparison.
    pub fn read_from(
        &self,
        package_index: usize,
        key: &ResourceKey,
    ) -> Result<Vec<u8>, AssetError> {
        let package =
            self.packages
                .get(package_index)
                .ok_or(AssetError::PackageIndexOutOfRange {
                    index: package_index,
                    count: self.packages.len(),
                })?;
        let entry = package.index().find(key).ok_or(AssetError::NotFound {
            key: *key,
            searched: 1,
            candidates: Vec::new(),
        })?;
        spore_dbpf::extract_record(package.bytes(), entry).map_err(|source| AssetError::Dbpf {
            package: package.name().to_owned(),
            source,
        })
    }

    /// Every record identity of `type_id` across all packages, in resolution
    /// order (package order, then index order), de-duplicated.
    pub fn identities_of_type(&self, type_id: u32) -> Vec<ResourceKey> {
        let mut seen = std::collections::HashSet::new();
        let mut out = Vec::new();
        for package in &self.packages {
            for entry in package.index().of_type(type_id) {
                if seen.insert(entry.key) {
                    out.push(entry.key);
                }
            }
        }
        out
    }
}
