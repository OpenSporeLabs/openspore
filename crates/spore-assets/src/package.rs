//! A loaded Spore package: the mapped bytes plus its parsed index.
//!
//! # Why memory mapping
//!
//! `Spore_Content.package` is ~995 MB and `Spore_Graphics.package` ~943 MB.
//! Reading a package into a `Vec<u8>` costs a full resident copy per package
//! for data that is overwhelmingly *not* touched -- most of a content package
//! is geometry and textures the current scene never asks for. A read-only
//! mapping keeps the resident cost proportional to what is actually decoded,
//! which is the difference between an engine that can open the real game data
//! and one that cannot.
//!
//! Tests and small tools use [`PackageBytes::Owned`] so they need no filesystem.

use std::path::Path;

use memmap2::Mmap;
use spore_dbpf::PackageIndex;

use crate::error::AssetError;

/// The bytes of a package, either mapped from disk or held in memory.
#[derive(Debug)]
pub enum PackageBytes {
    /// A read-only memory map of a file.
    Mapped(Mmap),
    /// Bytes held directly (tests, tooling, generated packages).
    Owned(Vec<u8>),
}

impl PackageBytes {
    /// The whole image.
    #[inline]
    pub fn as_slice(&self) -> &[u8] {
        match self {
            Self::Mapped(map) => map,
            Self::Owned(bytes) => bytes,
        }
    }

    #[inline]
    pub fn len(&self) -> usize {
        self.as_slice().len()
    }

    #[inline]
    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

/// One opened package: name, source path, bytes, and index.
#[derive(Debug)]
pub struct Package {
    name: String,
    path: Option<std::path::PathBuf>,
    bytes: PackageBytes,
    index: PackageIndex,
}

impl Package {
    /// Memory-maps `path` and parses its index.
    ///
    /// `name` is the display name used in errors and manifest rows; callers
    /// normally pass the file stem.
    ///
    /// # Safety / policy
    ///
    /// This is the crate's only `unsafe` block, and it exists because
    /// `memmap2` has no safe constructor. It is safe here because
    /// `Mmap::map` yields a `&[u8]` whose lifetime is tied to the returned
    /// `Mmap` -- **not** to the `File` -- and the mapping is read-only. Nothing
    /// can observe a torn or freed mapping through the returned slice, because
    /// the slice cannot outlive the `Mmap` that owns it, and the `Mmap` is
    /// stored in `self.bytes`.
    ///
    /// The Windows-equivalent risk (a file being truncated or replaced under a
    /// live mapping) is why Spore's `.package` files are treated as immutable
    /// inputs: this crate never writes them, and the engine never mutates a
    /// package in place.
    #[allow(unsafe_code)]
    pub fn open(name: impl Into<String>, path: impl AsRef<Path>) -> Result<Self, AssetError> {
        let path = path.as_ref();
        let display = path.display().to_string();
        let file = std::fs::File::open(path).map_err(|source| AssetError::Open {
            path: display.clone(),
            source,
        })?;
        let bytes = unsafe { Mmap::map(&file) }.map_err(|source| AssetError::Open {
            path: display.clone(),
            source,
        })?;
        Self::from_bytes(name, Some(path.to_path_buf()), PackageBytes::Mapped(bytes))
    }

    /// Builds a package from bytes already in hand.
    pub fn from_bytes(
        name: impl Into<String>,
        path: Option<std::path::PathBuf>,
        bytes: PackageBytes,
    ) -> Result<Self, AssetError> {
        let name = name.into();
        let index = PackageIndex::parse(bytes.as_slice()).map_err(|source| AssetError::Dbpf {
            package: name.clone(),
            source,
        })?;
        Ok(Self {
            name,
            path,
            bytes,
            index,
        })
    }

    /// Builds a package from an owned buffer (the test/tooling path).
    pub fn from_vec(name: impl Into<String>, bytes: Vec<u8>) -> Result<Self, AssetError> {
        Self::from_bytes(name, None, PackageBytes::Owned(bytes))
    }

    /// The package's display name.
    pub fn name(&self) -> &str {
        &self.name
    }

    /// The path it was mapped from, when it came from disk.
    pub fn path(&self) -> Option<&Path> {
        self.path.as_deref()
    }

    /// The mapped/owned image.
    #[inline]
    pub fn bytes(&self) -> &[u8] {
        self.bytes.as_slice()
    }

    /// The parsed record index.
    pub fn index(&self) -> &PackageIndex {
        &self.index
    }

    /// How many records the index holds.
    pub fn record_count(&self) -> usize {
        self.index.len()
    }
}
