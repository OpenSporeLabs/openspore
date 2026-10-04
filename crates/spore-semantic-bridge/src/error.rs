//! Every way this crate can refuse something.
//!
//! The variants are the Rust spelling of the Go CLI's stable exit codes, so a
//! consumer can branch on the *kind* of refusal rather than on a message:
//!
//! | variant | Go exit code | meaning |
//! |---|---|---|
//! | [`BridgeError::SnapshotUnavailable`] | 7 | no snapshot file — the artifact is optional |
//! | [`BridgeError::Corrupt`] | 5 | not a readable snapshot: bad JSON, truncated line, duplicate VA, unsorted records |
//! | [`BridgeError::UnsupportedSchema`] | 6 | a schema id or a field set this build does not implement |
//! | [`BridgeError::BinaryMismatch`] | 4 | the snapshot describes another binary |
//! | [`BridgeError::UnknownFunction`] | 2 | not an entry and not inside any body |
//! | [`BridgeError::UnknownSymbol`] / [`BridgeError::AmbiguousSymbol`] | 3 / 8 | name lookup |

use crate::address::AddressError;
use crate::json::JsonError;
use std::io;
use std::path::PathBuf;

/// Something this crate refuses to do.
///
/// Nothing here is ever returned as an empty success. The rule the whole
/// exchange rests on — *a miss yields an explicit error naming the address, the
/// binary and the size of the index, never an empty object* — is a type-level
/// guarantee: every fallible answer is a `Result`.
#[derive(Debug, thiserror::Error)]
#[non_exhaustive]
pub enum BridgeError {
    /// No snapshot file was found where one was expected.
    ///
    /// This is the artifact's *optionality* made visible: the engine builds and
    /// runs with no snapshot at all, and this is the error it gets if it asks
    /// for one that is not there.
    #[error(
        "no semantic snapshot at {path}; the artifact is optional and the engine does not need it"
    )]
    SnapshotUnavailable {
        /// Where this crate looked.
        path: PathBuf,
    },

    /// The snapshot file exists but could not be read.
    #[error("cannot read semantic snapshot {path}: {source}")]
    Io {
        /// The file being read.
        path: PathBuf,
        /// The underlying I/O failure.
        #[source]
        source: io::Error,
    },

    /// The file is not a readable snapshot.
    ///
    /// Malformed JSON, a truncated line, a blank line, a repeated JSON key, a
    /// non-canonical VA spelling inside a record, a duplicate canonical VA, or
    /// records that are not strictly ascending.
    #[error("corrupt semantic snapshot {path}:{line}: {detail}")]
    Corrupt {
        /// The file being read.
        path: PathBuf,
        /// The 1-based line number, or 0 when the failure is not line-bound.
        line: usize,
        /// What is wrong.
        detail: String,
    },

    /// The file is readable but declares a schema this build does not
    /// implement — a different `schema` id, or a field this build has never
    /// heard of.
    ///
    /// This is deliberately a *different* variant from [`BridgeError::Corrupt`].
    /// "The bytes are broken" and "these bytes mean something this build does
    /// not understand" are different diagnoses, and the consumer contract
    /// distinguishes them (exit 6 versus exit 5). A record carrying a field
    /// from a future schema is refused, never half-read.
    #[error("unsupported schema in {path}:{line}: {detail}")]
    UnsupportedSchema {
        /// The file being read.
        path: PathBuf,
        /// The 1-based line number, or 0 when the failure is not line-bound.
        line: usize,
        /// What is unknown, including the offending field's dotted path.
        detail: String,
    },

    /// `metadata.content_sha256` does not match the record bytes.
    #[error("content digest mismatch in {path}: metadata declares {declared}, record lines hash to {computed}")]
    ContentDigestMismatch {
        /// The file being read.
        path: PathBuf,
        /// The digest the header claims.
        declared: String,
        /// The digest this crate computed over the record lines.
        computed: String,
    },

    /// The snapshot's own record count disagrees with its metadata counters.
    #[error(
        "record count mismatch in {path}: metadata declares {declared}, body holds {computed}"
    )]
    RecordCountMismatch {
        /// The file being read.
        path: PathBuf,
        /// What `metadata.counts.functions` says.
        declared: usize,
        /// How many record lines the body actually holds.
        computed: usize,
    },

    /// The snapshot describes a different binary than the caller required.
    ///
    /// `binary_sha256` is half of the join key, so a mismatched snapshot answers
    /// a different question than the caller asked.
    #[error("binary mismatch: snapshot describes {snapshot}, caller requires {required}")]
    BinaryMismatch {
        /// The snapshot's `metadata.binary.binary_sha256`.
        snapshot: String,
        /// What the caller pinned.
        required: String,
    },

    /// The requested address is not a function entry and is not inside any
    /// known function body.
    ///
    /// This includes padding *between* two bodies, which is the case the
    /// repository has already decided to leave alone: `0x00925050` lies between
    /// `FUN_00925000` (ending `0x0092504a`) and `FUN_009250c0`, and
    /// re-pointing it would be inventing a mapping.
    #[error(
        "unknown function: {requested:#010x} is not a function entry and is not inside any known function body (image base {image_base:#010x}, {indexed} functions indexed)"
    )]
    UnknownFunction {
        /// The address that could not be placed.
        requested: u32,
        /// The snapshot's declared image base.
        image_base: u32,
        /// How many functions the snapshot indexes.
        indexed: usize,
    },

    /// No passport carries the requested name.
    #[error("unknown symbol {name:?}")]
    UnknownSymbol {
        /// The name that matched nothing.
        name: String,
    },

    /// More than one passport carries the requested name.
    ///
    /// Ambiguity is *reported*, never resolved: names are a convenience index
    /// and addresses are the key.
    #[error("ambiguous symbol {name:?}: {matches} canonical functions carry it; pick by address")]
    AmbiguousSymbol {
        /// The name that several passports share.
        name: String,
        /// How many carry it.
        matches: usize,
    },

    /// An address spelling this build refuses.
    #[error("{path}: {source}")]
    NonCanonicalVa {
        /// The field the spelling was read from, or `input` for caller input.
        path: String,
        /// The refusal.
        #[source]
        source: AddressError,
    },
}

impl BridgeError {
    pub(crate) fn corrupt(
        path: impl Into<PathBuf>,
        line: usize,
        detail: impl Into<String>,
    ) -> Self {
        Self::Corrupt {
            path: path.into(),
            line,
            detail: detail.into(),
        }
    }

    pub(crate) fn schema(path: impl Into<PathBuf>, line: usize, detail: impl Into<String>) -> Self {
        Self::UnsupportedSchema {
            path: path.into(),
            line,
            detail: detail.into(),
        }
    }

    pub(crate) fn io(path: impl Into<PathBuf>, source: io::Error) -> Self {
        Self::Io {
            path: path.into(),
            source,
        }
    }

    /// Lifts a reader refusal onto the file and line it came from, keeping the
    /// corrupt / unsupported-schema distinction intact.
    pub(crate) fn from_json(path: impl Into<PathBuf>, line: usize, error: JsonError) -> Self {
        let path = path.into();
        match error.kind {
            crate::json::JsonErrorKind::Syntax => Self::Corrupt {
                path,
                line,
                detail: format!("{}: {}", error.path, error.message),
            },
            crate::json::JsonErrorKind::Schema => Self::UnsupportedSchema {
                path,
                line,
                detail: format!("{}: {}", error.path, error.message),
            },
        }
    }

    /// A refusal about an address spelling read from `field`.
    pub(crate) fn address(field: &str, source: AddressError) -> Self {
        Self::NonCanonicalVa {
            path: field.to_owned(),
            source,
        }
    }
}
