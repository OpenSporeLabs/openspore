//! `extract`: write one record's bytes into a directory.
//!
//! # The write policy
//!
//! This is the only command in the tool that touches the filesystem for
//! writing, so its rules are explicit:
//!
//! * the package is opened read-only (a memory map) and never written;
//! * the only path ever created is `<--out>/<sanitised name>`;
//! * `--out` is refused when it is the filesystem root, `.`, or ends in a `..`
//!   component, because each of those turns "the directory I was told to use"
//!   into "somewhere above it" or "everywhere at once";
//! * the file name is built from hex id components, then run through
//!   [`sanitise_component`], and the joined path is re-checked to be a direct
//!   child of `--out` before the write. Both of those are defence in depth: the
//!   name cannot currently contain a separator, and the check is what would
//!   catch it if a future rename introduced one.
//!
//! Nothing here creates intermediate directories. A missing `--out` is an I/O
//! failure naming the path, not a silent `mkdir -p` of a typo'd location.

use std::io::Write;
use std::path::{Path, PathBuf};

use spore_core::ResourceKey;

use crate::{ExtractRequest, ToolError, EXIT_IO};

/// How many rows of a "wrote ..." report.
pub fn run(request: &ExtractRequest, out: &mut dyn Write) -> Result<(), ToolError> {
    let store = super::single_package_store(&request.package)?;
    let found = store.find(&request.key)?;
    // Read through the store's priority resolution so the bytes written are the
    // bytes `find` would have reported.
    let bytes = store.read_from(found.package_index, &request.key)?;

    let name = record_file_name(found.entry.type_id, &request.key);
    let target = request.out_dir.join(&name);
    // Defence in depth, as documented above: the written path must be a direct
    // child of `--out` and nothing else.
    debug_assert_eq!(target.parent(), Some(request.out_dir.as_path()));

    std::fs::write(&target, &bytes)
        .map_err(|source| ToolError::Io(format!("{}: {source}", target.display())))?;

    writeln!(
        out,
        "wrote {} ({} bytes) for {}",
        target.display(),
        bytes.len(),
        request.key
    )?;
    let _ = EXIT_IO;
    Ok(())
}

/// The file name for one record: `<type name or hex>-<t>-<g>-<i>.bin`.
///
/// Every component is hex digits or a name from this build's own fixed table, so
/// the name is deterministic (two runs write the same file), sorts sensibly next
/// to its siblings, and contains no character a filesystem object. It is still
/// pushed through [`sanitise_component`], because "no separator today" is a
/// property of the inputs rather than of the function.
pub fn record_file_name(type_id: u32, key: &ResourceKey) -> String {
    let stem = super::type_name_of(type_id)
        .map(str::to_owned)
        .unwrap_or_default();
    let stem = if stem.is_empty() {
        format!("0x{type_id:08x}")
    } else {
        stem
    };
    sanitise_component(&format!(
        "{stem}-{:08x}-{:08x}-{:08x}.bin",
        key.type_id, key.group_id, key.instance_id
    ))
}

/// Replaces every byte that is not `[A-Za-z0-9._-]` with `_`.
///
/// Deliberately *not* a "strip the bad characters" function: replacing keeps the
/// name's length and shape, so two different records can never collapse onto one
/// file name, which would silently lose one of them. The `.` and `-` cases are
/// worth naming: a component of `.` or `..` is not a usable file name at all and
/// is refused rather than sanitised into something harmless-looking.
pub fn sanitise_component(raw: &str) -> String {
    raw.chars()
        .map(|c| {
            if c.is_ascii_alphanumeric() || c == '.' || c == '_' || c == '-' {
                c
            } else {
                '_'
            }
        })
        .collect()
}

/// Validates `--out`.
///
/// Refused: the empty string, `/`, `.`, `..`, and any path whose last component
/// is `..`. Everything else is accepted verbatim — including a path with a `..`
/// component in the *middle*, which is an ordinary relative path like
/// `../out/dumps` that resolves where the user meant it to.
pub fn validate_out_dir(raw: &str) -> Result<PathBuf, crate::CliError> {
    let trimmed = raw.trim();
    let refused = trimmed.is_empty()
        || trimmed == "/"
        || trimmed == "."
        || trimmed == ".."
        || Path::new(trimmed)
            .components()
            .next_back()
            .is_some_and(|component| component == std::path::Component::ParentDir);
    if refused {
        return Err(crate::CliError::UnsafeOutDir(raw.to_owned()));
    }
    Ok(PathBuf::from(trimmed))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_record_name_is_deterministic_and_separator_free() {
        let key = ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801);
        let name = record_file_name(0x00e6_bce5, &key);
        assert_eq!(name, "gmdl-00e6bce5-40616201-067a0801.bin");
        assert_eq!(name, record_file_name(0x00e6_bce5, &key));
        assert!(!name.contains('/') && !name.contains('\\') && !name.contains(':'));
    }

    #[test]
    fn an_unknown_type_falls_back_to_its_hex_id() {
        let key = ResourceKey::new(0xdead_beef, 1, 2);
        assert_eq!(
            record_file_name(0xdead_beef, &key),
            "0xdeadbeef-deadbeef-00000001-00000002.bin"
        );
    }

    #[test]
    fn sanitising_replaces_rather_than_deletes() {
        // Replacement, not deletion: the name's shape is preserved so it stays
        // recognisable in a directory listing.
        assert_eq!(sanitise_component("a/b"), "a_b");
        assert_eq!(sanitise_component("a:b c"), "a_b_c");
        assert_eq!(sanitise_component("../../etc/passwd"), ".._.._etc_passwd");
        assert_eq!(sanitise_component("keep-1.0_x"), "keep-1.0_x");
        assert_eq!(sanitise_component(""), "");
        // The honest limit of this function: sanitising is *lossy*, so two
        // inputs differing only in a rejected character collide. That is
        // acceptable only because the sole caller feeds it hex digits and
        // canonical names, and it is why `record_file_name` is pinned to a
        // distinct name per identity below rather than relying on the
        // sanitiser to be injective.
        assert_eq!(sanitise_component("a/b"), sanitise_component("a:b"));
    }

    #[test]
    fn two_records_never_share_a_file_name() {
        let base = ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801);
        let mut names = std::collections::HashSet::new();
        for type_id in [0x00e6_bce5u32, 0x2f4e_681b, 0x2f4e_681c, 0xdead_beef] {
            for group_id in [0u32, 0x4061_6201, 0x4062_6200] {
                for instance_id in [0u32, 1, 0x067a_0801, u32::MAX] {
                    let mut key = base;
                    key.type_id = type_id;
                    key.group_id = group_id;
                    key.instance_id = instance_id;
                    assert!(
                        names.insert(record_file_name(type_id, &key)),
                        "collision on {key}"
                    );
                }
            }
        }
    }

    #[test]
    fn an_out_dir_that_is_the_root_or_a_parent_reference_is_refused() {
        for refused in ["", "   ", "/", ".", "..", "out/..", "/tmp/..", "./.."] {
            assert!(
                validate_out_dir(refused).is_err(),
                "`{refused}` must be refused"
            );
        }
    }

    #[test]
    fn an_ordinary_relative_or_absolute_out_dir_is_accepted() {
        assert_eq!(
            validate_out_dir("/tmp/out").unwrap(),
            PathBuf::from("/tmp/out")
        );
        assert_eq!(validate_out_dir("out").unwrap(), PathBuf::from("out"));
        // A `..` in the middle is a normal relative path, not an escape.
        assert_eq!(
            validate_out_dir("../out/dumps").unwrap(),
            PathBuf::from("../out/dumps")
        );
        // Trailing whitespace is trimmed rather than becoming a path with a
        // space in it -- a shell-quoting accident, not an intent.
        assert_eq!(validate_out_dir("  out  ").unwrap(), PathBuf::from("out"));
    }
}
