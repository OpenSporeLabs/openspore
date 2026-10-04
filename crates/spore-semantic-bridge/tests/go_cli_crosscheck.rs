//! Cross-check against the `spore-semantic` CLI, which is the **producer** of
//! this file.
//!
//! # Why this test is `#[ignore]`d
//!
//! `spore-semantic` is an optional external binary. It is not a build or runtime
//! dependency of this crate — it may be installed, it may not, and a consumer of
//! the snapshot never needs it. So this file is `#[ignore]`d by default and
//! **skips, loudly, when the CLI is absent**. It is a cross-check, not a gate:
//!
//! ```sh
//! command -v spore-semantic
//! cargo test -p spore-semantic-bridge --test go_cli_crosscheck -- --ignored --nocapture
//! ```
//!
//! It compares exactly what can be compared without re-implementing the CLI's
//! output format: the canonicalization **rule name** and the **byte offset** for
//! each of the three interior addresses the repository records, plus the padding
//! address that must resolve to nothing.

mod support;

use spore_semantic_bridge::{Canonicalization, Snapshot};

/// The three interior resolutions the repository records.
const KNOWN: [(u32, u32, u32); 3] = [
    (0x00e3_a400, 0x00e3_a270, 400),
    (0x00e7_b6c0, 0x00e7_b630, 144),
    (0x00e7_d2c0, 0x00e7_d070, 592),
];

const PADDING_VA: u32 = 0x0092_5050;

/// The command the CLI is installed as, from the repository's own build line.
const CLI: &str = "spore-semantic";

fn snapshot() -> Option<&'static Snapshot> {
    static ONCE: std::sync::OnceLock<Option<Snapshot>> = std::sync::OnceLock::new();
    static PATH: std::sync::OnceLock<std::path::PathBuf> = std::sync::OnceLock::new();
    let path = support::committed_path()?;
    let _ = PATH.set(path);
    ONCE.get_or_init(|| {
        let path = PATH.get().expect("path was just set");
        Some(Snapshot::open(path).expect("the committed snapshot must open"))
    })
    .as_ref()
}

/// Runs `spore-semantic lookup <va> --json` and returns its stdout.
fn cli_lookup(va: u32) -> Option<String> {
    let output = std::process::Command::new(CLI)
        .arg("lookup")
        .arg(format!("0x{va:08x}"))
        .arg("--json")
        .arg(format!("--snapshot={}", snapshot()?.path().display()))
        .output()
        .ok()?;
    if !output.status.success() {
        eprintln!(
            "SKIPPED: `{CLI} lookup 0x{va:08x} --json` exited {:?}: {}",
            output.status.code(),
            String::from_utf8_lossy(&output.stderr).trim()
        );
        return None;
    }
    String::from_utf8(output.stdout).ok()
}

/// Pulls `"<key>":<value>` out of the CLI's JSON, without a JSON parser.
///
/// Deliberately crude and deliberately local: this is a test reading a trusted
/// local tool's output, and a strict parser here would be a second reader to keep
/// in step. The value returned is the text between the colon and the following
/// comma-or-brace, unquoted.
fn json_field(text: &str, key: &str) -> Option<String> {
    let needle = format!("\"{key}\":");
    let start = text.find(&needle)? + needle.len();
    let rest = &text[start..];
    let end = rest.find([',', '}', ']']).unwrap_or(rest.len());
    Some(rest[..end].trim().trim_matches('"').to_owned())
}

#[test]
#[ignore = "requires the optional spore-semantic CLI; skipped when it is absent"]
fn this_crate_agrees_with_the_producer_on_the_three_known_interior_addresses() {
    if which(CLI).is_none() {
        eprintln!(
            "SKIPPED: `{CLI}` is not on PATH. The producer of this file is optional and nothing \
             in this crate depends on it; install it with \
             `cd tools/spore-semantic && CGO_ENABLED=0 go build -trimpath -o ~/.local/bin/spore-semantic ./cmd/spore-semantic`"
        );
        return;
    }
    let snapshot = snapshot().expect("the committed snapshot must be present for this comparison");
    for (interior, entry, offset) in KNOWN {
        let Some(text) = cli_lookup(interior) else {
            continue;
        };
        let rule = json_field(&text, "rule").expect("the CLI states a rule");
        let cli_entry = json_field(&text, "canonical_va").expect("the CLI states an entry");
        let cli_offset = json_field(&text, "offset").expect("the CLI states an offset");

        let ours = snapshot.resolve(interior);
        assert_eq!(
            rule,
            Canonicalization::ContainingFunctionEntry.as_str(),
            "0x{interior:08x}: rule names must be the same vocabulary"
        );
        assert_eq!(ours.rule, Canonicalization::ContainingFunctionEntry);
        assert_eq!(
            cli_entry,
            format!("0x{entry:08x}"),
            "0x{interior:08x}: the CLI resolved to a different entry"
        );
        assert_eq!(ours.canonical, Some(entry));
        assert_eq!(
            cli_offset,
            offset.to_string(),
            "0x{interior:08x}: the byte offsets must agree"
        );
        assert_eq!(ours.offset, Some(offset));
    }
}

#[test]
#[ignore = "requires the optional spore-semantic CLI; skipped when it is absent"]
fn this_crate_agrees_with_the_producer_that_padding_resolves_to_nothing() {
    if which(CLI).is_none() {
        eprintln!("SKIPPED: `{CLI}` is not on PATH.");
        return;
    }
    let snapshot = snapshot().expect("the committed snapshot must be present for this comparison");
    let resolution = snapshot.resolve(PADDING_VA);
    assert_eq!(resolution.rule, Canonicalization::NonFunctionEntity);
    assert_eq!(resolution.canonical, None);

    let output = std::process::Command::new(CLI)
        .arg("lookup")
        .arg(format!("0x{PADDING_VA:08x}"))
        .arg("--snapshot")
        .arg(snapshot.path())
        .output()
        .expect("the CLI runs");
    assert_eq!(
        output.status.code(),
        Some(2),
        "the CLI exits 2 (unknown function) for an address it cannot place; stderr: {}",
        String::from_utf8_lossy(&output.stderr).trim()
    );
    let text = String::from_utf8_lossy(&output.stdout);
    assert!(
        text.contains("0x00925050")
            || String::from_utf8_lossy(&output.stderr).contains("0x00925050"),
        "a miss names the address it could not place"
    );
}

/// `which`, without a dependency.
fn which(binary: &str) -> Option<std::path::PathBuf> {
    let path = std::env::var_os("PATH")?;
    std::env::split_paths(&path)
        .map(|dir| dir.join(binary))
        .find(|candidate| candidate.is_file())
}
