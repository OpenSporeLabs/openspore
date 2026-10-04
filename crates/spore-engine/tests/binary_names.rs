//! The shipped binary is named `openspore`. The crate is `spore-engine`.
//!
//! These names come apart easily and the failure is silent: Cargo defaults a
//! `src/main.rs` binary to the *package* name, so deleting the `[[bin]]` section
//! from `Cargo.toml` renames the binary with no compile error and no warning.
//! Every document, CI step and error message in this repository refers to
//! `openspore`, so a silent rename leaves the docs describing a program that
//! does not exist — which is exactly what happened once.

use std::process::Command;

use spore_engine::cli::{self, LaunchRequest};

/// The workspace-relative path of the built engine binary.
fn engine_binary() -> std::path::PathBuf {
    // target/<profile>/deps/<test binary> -> target/<profile>/openspore
    let mut path = std::env::current_exe().expect("a test binary has a path");
    path.pop();
    if path.ends_with("deps") {
        path.pop();
    }
    path.join("openspore")
}

#[test]
fn the_engine_binary_is_called_openspore_not_spore_engine() {
    // A manifest assertion, not a filesystem one: it holds even before a build,
    // and it names the exact thing that went missing.
    let manifest = std::fs::read_to_string(concat!(env!("CARGO_MANIFEST_DIR"), "/Cargo.toml"))
        .expect("the crate manifest is readable from its source tree");
    assert!(
        manifest.contains("name = \"openspore\""),
        "crates/spore-engine/Cargo.toml must declare [[bin]] name = \"openspore\"; \
         without it Cargo names the binary after the package and every doc reference breaks"
    );
}

#[test]
fn the_engine_binary_answers_help_under_its_shipped_name() {
    let binary = engine_binary();
    if !binary.exists() {
        // `cargo test` builds the lib test harness, not necessarily the bin. The
        // manifest test above is the hermetic guarantee; this one only runs when
        // a binary happens to be present.
        eprintln!("skipping: {} has not been built", binary.display());
        return;
    }
    let output = Command::new(&binary)
        .arg("--help")
        .output()
        .expect("the binary runs");
    assert!(output.status.success(), "openspore --help must exit 0");
    let text = String::from_utf8_lossy(&output.stdout);
    assert!(
        text.contains("openspore"),
        "the usage text must name the binary: {text}"
    );
}

#[test]
fn the_usage_text_agrees_with_the_parser() {
    // The usage string and the parser are two descriptions of the same CLI. If
    // they drift, a user reads a flag that does not exist.
    let usage = cli::usage();

    // Boolean flags: the flag alone must parse. Handing one a value leaves that
    // value to be read as a positional and rejected, which is correct behaviour
    // and not what this test is about.
    for flag in ["--info", "--placeholder", "--texture"] {
        assert!(usage.contains(flag), "usage must document {flag}");
        let parsed = cli::parse([flag]).err();
        assert!(
            !matches!(parsed, Some(cli::CliError::UnknownFlag(_))),
            "usage documents {flag} but the parser rejects it as unknown"
        );
    }

    // Value-taking flags: the flag plus a value must also not come back as an
    // unknown flag. The value itself may legitimately be refused -- `x` is not a
    // path and not a preset -- and that refusal is the correct outcome.
    for flag in ["--package", "--record", "--preset", "--scale", "--title"] {
        assert!(usage.contains(flag), "usage must document {flag}");
        let parsed = cli::parse([flag, "x"]).err();
        assert!(
            !matches!(parsed, Some(cli::CliError::UnknownFlag(_))),
            "usage documents {flag} but the parser rejects it as unknown"
        );
    }
}

#[test]
fn help_is_a_first_class_launch_request() {
    assert_eq!(cli::parse(["--help"]).unwrap(), LaunchRequest::Help);
    assert_eq!(cli::parse(["-h"]).unwrap(), LaunchRequest::Help);
}
