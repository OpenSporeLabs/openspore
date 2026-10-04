//! Typed errors for the content layer.
//!
//! Every failure mode is a distinct variant carrying the *coordinates* needed
//! to find the problem: which package, which record key, which section. A
//! single opaque "asset error" string is what this type exists to prevent --
//! when a 995 MB content package yields a wrong record, the operator needs to
//! know which package answered.

use spore_core::ResourceKey;

/// The near-miss suffix appended to an [`AssetError::NotFound`] message.
///
/// A candidate list that lives only in a struct field is invisible to anyone
/// reading a log line, so it has to reach the message. The "nothing to suggest"
/// case is worded differently on purpose: a bare sentence with no suffix reads
/// like an absence of evidence, when it is actually an absence of *suggestions*
/// to give.
fn candidate_hint(candidates: &[ResourceKey]) -> String {
    if candidates.is_empty() {
        return "; no record of that type was found either, so there is nothing to suggest"
            .to_owned();
    }
    // Spell out at most this many, so one log line stays readable.
    const SHOWN: usize = 8;
    let total = candidates.len();
    let noun = if total == 1 { "y" } else { "ies" };
    let list: Vec<String> = candidates
        .iter()
        .take(SHOWN)
        .map(ToString::to_string)
        .collect();
    if total <= SHOWN {
        format!(
            "; {total} nearby identit{noun} of that type: {}",
            list.join(", ")
        )
    } else {
        // The count is the TRUE total, not the number printed. Saying "8 nearby"
        // when 50 exist understates the evidence and reads as if 8 were all of it.
        format!(
            "; {total} nearby identit{noun} of that type, first {SHOWN}: {}",
            list.join(", ")
        )
    }
}

/// Everything that can go wrong between "open a package" and "here is a mesh".
///
/// `PartialEq` is implemented deliberately: an asset pipeline's errors are
/// compared in tests far more often than they are inspected, and a test that
/// has to match three variants to assert "the record was not found" stops
/// being a test of the lookup.
#[derive(Debug, thiserror::Error)]
pub enum AssetError {
    /// The package file could not be opened or mapped.
    #[error("could not open package `{path}`: {source}")]
    Open {
        /// Filesystem path that failed.
        path: String,
        /// Underlying I/O error.
        #[source]
        source: std::io::Error,
    },

    /// The container layer refused the package.
    #[error("package `{package}`: dbpf: {source}")]
    Dbpf {
        /// Package name (file stem).
        package: String,
        /// Underlying DBPF error.
        #[source]
        source: spore_dbpf::DbpfError,
    },

    /// A package's index parsed but no entry matched the requested identity.
    ///
    /// `candidates` is populated by the store with the closest identities it
    /// did find, because "not found" without a hint is the least useful error
    /// in an asset system -- and because it must appear in the *message*: a
    /// candidate list that exists only in a struct field is invisible to anyone
    /// reading a log line.
    #[error("no record `{key}` in any of the {searched} loaded package(s){}", candidate_hint(.candidates))]
    NotFound {
        /// The identity that was requested.
        key: ResourceKey,
        /// How many packages were searched.
        searched: usize,
        /// Near-miss identities, when the store could suggest any.
        candidates: Vec<ResourceKey>,
    },

    /// The record exists but its container type is not one we decode.
    #[error("record `{key}` has type 0x{type_id:08x}, which is not a model container")]
    UnsupportedModelType {
        /// The identity that was requested.
        key: ResourceKey,
        /// The record's type id.
        type_id: u32,
    },

    /// The model record decoded but yielded no usable mesh.
    #[error("record `{key}` decoded as {format} but produced no mesh")]
    EmptyModel {
        /// The identity that was requested.
        key: ResourceKey,
        /// Which container it decoded as.
        format: &'static str,
    },

    /// The GMDL layer refused the record.
    #[error("record `{key}`: gmdl: {source}")]
    Gmdl {
        /// The identity that was requested.
        key: ResourceKey,
        /// Underlying GMDL error.
        #[source]
        source: spore_gmdl::GmdlError,
    },

    /// The RW4 layer refused the record.
    #[error("record `{key}`: rw4: {source}")]
    Rw4 {
        /// The identity that was requested.
        key: ResourceKey,
        /// Underlying RW4 error.
        #[source]
        source: spore_rw4::Rw4Error,
    },

    /// The raster/texture layer refused the record.
    #[error("record `{key}`: texture: {source}")]
    Texture {
        /// The identity that was requested.
        key: ResourceKey,
        /// Underlying texture error.
        #[source]
        source: spore_texture::TextureError,
    },

    /// No packages were registered with the store at all.
    #[error("the content store holds no packages; nothing can be resolved")]
    EmptyStore,

    /// A caller asked for a package by index that does not exist.
    #[error("package index {index} is out of range ({count} loaded)")]
    PackageIndexOutOfRange {
        /// The requested index.
        index: usize,
        /// How many packages are loaded.
        count: usize,
    },
}

impl AssetError {
    /// The record identity this error is about, when it is about one.
    ///
    /// Lets a caller log "while loading X" without matching every variant.
    pub fn key(&self) -> Option<ResourceKey> {
        match self {
            Self::NotFound { key, .. }
            | Self::UnsupportedModelType { key, .. }
            | Self::EmptyModel { key, .. }
            | Self::Gmdl { key, .. }
            | Self::Rw4 { key, .. }
            | Self::Texture { key, .. } => Some(*key),
            Self::Open { .. }
            | Self::Dbpf { .. }
            | Self::EmptyStore
            | Self::PackageIndexOutOfRange { .. } => None,
        }
    }
}

/// Hand-written because `std::io::Error` is not `PartialEq`.
///
/// `Open` compares on `ErrorKind` plus the rendered message, which is stable
/// enough for a test asserting "this path failed to open" and still keeps the
/// real error in the `#[source]` chain for diagnostics. Every other variant
/// contains only `PartialEq` data and compares structurally.
impl PartialEq for AssetError {
    fn eq(&self, other: &Self) -> bool {
        use AssetError::*;
        match (self, other) {
            (
                Open {
                    path: a,
                    source: a_src,
                },
                Open {
                    path: b,
                    source: b_src,
                },
            ) => a == b && a_src.kind() == b_src.kind() && a_src.to_string() == b_src.to_string(),
            (
                Dbpf {
                    package: a,
                    source: a_src,
                },
                Dbpf {
                    package: b,
                    source: b_src,
                },
            ) => a == b && a_src == b_src,
            (
                NotFound {
                    key: ak,
                    searched: ac,
                    candidates: ax,
                },
                NotFound {
                    key: bk,
                    searched: bc,
                    candidates: bx,
                },
            ) => ak == bk && ac == bc && ax == bx,
            (
                UnsupportedModelType {
                    key: a,
                    type_id: at,
                },
                UnsupportedModelType {
                    key: b,
                    type_id: bt,
                },
            ) => a == b && at == bt,
            (EmptyModel { key: a, format: af }, EmptyModel { key: b, format: bf }) => {
                a == b && af == bf
            }
            (
                Gmdl {
                    key: a,
                    source: as_,
                },
                Gmdl { key: b, source: bs },
            ) => a == b && as_ == bs,
            (
                Rw4 {
                    key: a,
                    source: as_,
                },
                Rw4 { key: b, source: bs },
            ) => a == b && as_ == bs,
            (
                Texture {
                    key: a,
                    source: as_,
                },
                Texture { key: b, source: bs },
            ) => a == b && as_ == bs,
            (EmptyStore, EmptyStore) => true,
            (
                PackageIndexOutOfRange {
                    index: ai,
                    count: ac,
                },
                PackageIndexOutOfRange {
                    index: bi,
                    count: bc,
                },
            ) => ai == bi && ac == bc,
            _ => false,
        }
    }
}

#[cfg(test)]
mod message_tests {
    use super::*;

    #[test]
    fn a_not_found_message_carries_its_candidates() {
        // A candidate list that lives only in a struct field is invisible to
        // anyone reading a log line, which is where an asset failure is actually
        // diagnosed.
        let error = AssetError::NotFound {
            key: ResourceKey::new(1, 2, 3),
            searched: 2,
            candidates: vec![ResourceKey::new(9, 8, 7)],
        };
        let message = error.to_string();
        assert!(
            message.contains("0x00000001:0x00000002:0x00000003"),
            "{message}"
        );
        assert!(
            message.contains("0x00000009:0x00000008:0x00000007"),
            "{message}"
        );
        assert!(message.contains("2 loaded package"), "{message}");
    }

    #[test]
    fn a_not_found_with_no_candidates_says_so_rather_than_going_quiet() {
        // An empty suffix would read like "we found nothing at all", which is a
        // different claim from "we have nothing to suggest".
        let error = AssetError::NotFound {
            key: ResourceKey::new(1, 2, 3),
            searched: 1,
            candidates: Vec::new(),
        };
        let message = error.to_string();
        assert!(message.contains("nothing to suggest"), "{message}");
        assert!(!message.contains("nearby"), "{message}");
    }

    #[test]
    fn a_single_candidate_is_not_pluralised() {
        let one = candidate_hint(&[ResourceKey::new(1, 1, 1)]);
        assert!(one.contains("1 nearby identity of that type"), "{one}");
        let two = candidate_hint(&[ResourceKey::new(1, 1, 1), ResourceKey::new(2, 2, 2)]);
        assert!(two.contains("2 nearby identities of that type"), "{two}");
    }

    #[test]
    fn the_candidate_list_is_capped_so_a_log_line_stays_readable() {
        let many: Vec<ResourceKey> = (0..50).map(|i| ResourceKey::new(i, i, i)).collect();
        let hint = candidate_hint(&many);
        assert!(
            hint.contains("50 nearby identities of that type, first 8"),
            "the count must be the true total: {hint}"
        );
        // Only eight identities are spelled out, and each is spelled as
        // `T:G:I`, so the message carries exactly 8 * 3 `0x` prefixes.
        assert_eq!(hint.matches("0x").count(), 24, "{hint}");
        assert!(
            !hint.contains("0x00000032"),
            "the 50th identity must be summarised, not listed: {hint}"
        );
    }
}
