//! Read-only checks against a real `SPORE/Data/Spore_Content.package`.
//!
//! # Why this file is skipped by default
//!
//! The package is a ~995 MB git-ignored game install. A default test run must not
//! depend on it, so every test here **returns early** when the file is absent and
//! says so in its output rather than failing. Run them for real with:
//!
//! ```text
//! cargo test -p spore-tools --test real_package -- --ignored --nocapture
//! ```
//!
//! Nothing here writes to the package or to `SPORE/`: every command used opens a
//! read-only memory map, and the one that writes (`extract`) targets a temporary
//! directory.

use std::path::PathBuf;

use spore_tools::EXIT_OK;

/// The real content package, if it is installed.
fn content_package() -> Option<PathBuf> {
    let path =
        PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../../SPORE/Data/Spore_Content.package");
    if path.exists() {
        Some(path)
    } else {
        println!("skipped: {} is not installed", path.display());
        None
    }
}

/// Runs `osptool` with owned arguments and returns `(code, stdout, stderr)`.
fn run(args: Vec<String>) -> (i32, String, String) {
    let mut out = Vec::new();
    let mut err = Vec::new();
    let code = spore_tools::main_with(args, &mut out, &mut err);
    (
        code,
        String::from_utf8(out).expect("stdout is utf-8"),
        String::from_utf8(err).expect("stderr is utf-8"),
    )
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn list_limit_five_against_the_real_content_package() {
    let Some(path) = content_package() else {
        return;
    };
    let (code, out, err) = run(vec![
        "list".to_owned(),
        path.display().to_string(),
        "--limit".to_owned(),
        "5".to_owned(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    let lines: Vec<&str> = out.lines().collect();
    // One summary line, one column header, five rows.
    assert_eq!(lines.len(), 7, "{out}");
    assert!(lines[0].contains("Spore_Content"), "{}", lines[0]);
    assert!(lines[0].contains("5 shown"), "{}", lines[0]);
    assert!(lines[0].contains("(limit 5)"), "{}", lines[0]);
    for row in &lines[2..] {
        assert!(row.contains("0x"), "{row}");
    }
    // The summary names the full index size, which is the number worth knowing.
    // The corpus is version-pinned: `Spore_Content.package` holds 17 119 records,
    // of which 4 209 are gmdl -- a figure the format crates already cite, so a
    // change here means the game data changed, not the tool.
    let total: u64 = lines[0]
        .split_whitespace()
        .find_map(|token| token.parse::<u64>().ok())
        .expect("a record count");
    assert_eq!(total, 17_119, "the pinned corpus index size changed");

    // And the documented per-type count agrees with `verify`.
    let (code, census, err) = run(vec![
        "verify".to_owned(),
        path.display().to_string(),
        "--type".to_owned(),
        "0x00e6bce5".to_owned(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(census.contains("walked         4209"), "{census}");
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn list_with_names_and_json_against_the_real_content_package() {
    let Some(path) = content_package() else {
        return;
    };
    let (code, out, err) = run(vec![
        "list".to_owned(),
        path.display().to_string(),
        "--names".to_owned(),
        "--json".to_owned(),
        "--limit".to_owned(),
        "20".to_owned(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    let value = spore_tools::json::parse(out.trim()).expect("valid JSON");
    let spore_tools::json::Json::Arr(rows) = &value else {
        panic!("expected an array")
    };
    assert_eq!(rows.len(), 20);
    // The real package is full of named types, so at least one name must resolve.
    assert!(
        out.contains("gmdl") || out.contains("raster") || out.contains("rw4"),
        "the canonical names must appear: {out}"
    );
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn describe_the_documented_vertical_slice_record() {
    let Some(path) = content_package() else {
        return;
    };
    // `spore_engine::cli::PRESET_DOCUMENTED_ASSET`.
    let (code, out, err) = run(vec![
        "describe".to_owned(),
        path.display().to_string(),
        "0x00e6bce5:0x40637e03:0x067a07f0".to_owned(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(out.contains("decoder: gmdl (decoded"), "{out}");
    // The documented slice (`spore_engine::cli::PRESET_DOCUMENTED_ASSET`):
    // 1156 bytes decompressed from a 794-byte QFS record, one mesh, 32 vertices,
    // 60 indices (20 triangles) and a 24-byte stride -- POSITION/FLOAT3 at 0,
    // NORMAL/UBYTE4 at 12, TEXCOORD/FLOAT2 at 16.
    assert!(out.contains("index memory size       1156 bytes"), "{out}");
    assert!(out.contains("index compression       qfs"), "{out}");
    assert!(out.contains("mesh count         1"), "{out}");
    assert!(out.contains("vertices=32"), "{out}");
    assert!(out.contains("indices=60"), "{out}");
    assert!(out.contains("[0] 3 element(s), stride 24"), "{out}");
    assert!(out.contains("usage=3 (NORMAL)"), "{out}");
    assert!(out.contains("texture refs       3"), "{out}");
    assert!(
        out.contains("trailer            complete (1156 of 1156 bytes validated)"),
        "{out}"
    );
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn verify_the_whole_real_content_package_streams() {
    let Some(path) = content_package() else {
        return;
    };
    // The point of `verify`: one record at a time, so this must finish on a
    // 995 MB image without accumulating. The assertion is on the counts, not on
    // memory, because a memory assertion in a test is not portable.
    let (code, out, err) = run(vec!["verify".to_owned(), path.display().to_string()]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains("scope          every record in the package"),
        "{out}"
    );
    let walked: u64 = out
        .lines()
        .find_map(|line| line.strip_prefix("walked         "))
        .and_then(|value| value.trim().parse().ok())
        .expect("a walked count");
    // 17 119 for the pinned corpus; this is a floor, and the exact figure is
    // asserted in the `list` test so a change is attributed there.
    assert!(walked >= 10_000, "walked {walked} records");
    let bucket = |name: &str| -> u64 {
        out.lines()
            .find_map(|line| line.strip_prefix(&format!("{name:<13}")))
            .and_then(|value| value.trim().parse().ok())
            .unwrap_or(0)
    };
    assert_eq!(
        bucket("decoded") + bucket("failed") + bucket("container") + bucket("no decoder"),
        walked
    );
    assert!(
        bucket("decoded") > 0,
        "the content package has decodable records"
    );
    println!("{out}");
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn verify_one_type_against_the_real_content_package() {
    let Some(path) = content_package() else {
        return;
    };
    let (code, out, err) = run(vec![
        "verify".to_owned(),
        path.display().to_string(),
        "--type".to_owned(),
        "0x2f4e681b".to_owned(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(
        out.contains("scope          type 0x2f4e681b (rw4)"),
        "{out}"
    );
    println!("{out}");
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn manifest_the_real_content_package_is_deterministic() {
    let Some(path) = content_package() else {
        return;
    };
    // The reference tool's defining property, checked on the real corpus rather
    // than only on a fixture.
    let first = run(vec![
        "manifest".to_owned(),
        path.display().to_string(),
        "--stats".to_owned(),
    ]);
    let second = run(vec![
        "manifest".to_owned(),
        path.display().to_string(),
        "--stats".to_owned(),
    ]);
    assert_eq!(first.0, EXIT_OK, "{}", first.2);
    assert_eq!(first, second, "two runs over the real package must agree");
    assert!(first.1.contains("rows "), "{}", first.1);
    println!("{}", first.1);
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn types_against_the_real_content_package_uses_the_prop_directory() {
    let Some(path) = content_package() else {
        return;
    };
    let (code, out, err) = run(vec![
        "types".to_owned(),
        "--group".to_owned(),
        "--package".to_owned(),
        path.display().to_string(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(out.contains("canonical type table"), "{out}");
    assert!(out.contains("canonical group table"), "{out}");
    assert!(out.contains("per-package type histogram"), "{out}");
    // The prop directory of the real package is what makes this interesting, and
    // it is found by group and instance with no constraint on the type id.
    assert!(out.contains("0x01C7AC81:0x01C7AC81"), "{out}");
    println!(
        "{}",
        out.lines().rev().take(20).collect::<Vec<_>>().join("\n")
    );
}

#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn a_real_record_can_be_extracted_into_a_temporary_directory() {
    let Some(path) = content_package() else {
        return;
    };
    let dir = std::env::temp_dir().join(format!("osptool-real-{}", std::process::id()));
    std::fs::create_dir_all(&dir).expect("a writable temporary directory");
    let (code, out, err) = run(vec![
        "extract".to_owned(),
        path.display().to_string(),
        "0x00e6bce5:0x40637e03:0x067a07f0".to_owned(),
        "--out".to_owned(),
        dir.display().to_string(),
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert!(out.contains("wrote "), "{out}");
    let written: Vec<_> = std::fs::read_dir(&dir)
        .expect("readable")
        .map(|entry| entry.expect("entry").path())
        .collect();
    assert_eq!(written.len(), 1, "{out}");
    // The bytes on disk are exactly what `find` reports as the record's memory
    // size, which is the same number the index carries.
    let bytes = std::fs::read(&written[0]).expect("readable");
    assert_eq!(
        bytes.len(),
        1156,
        "the documented slice's decompressed size"
    );
    let _ = std::fs::remove_dir_all(&dir);
}

/// The heap high-water mark of a whole-package walk, measured.
///
/// `verify` is specified to be memory-flat, and "it does not accumulate" is a
/// claim about memory that means nothing unless something measures it. This
/// spawns the real binary and reads `/proc/<pid>/status`, so the number comes
/// from the kernel rather than from this crate's opinion of itself.
///
/// # `RssAnon`, not `VmHWM`
///
/// `VmHWM` is the **wrong** metric here and reads ~968 MB, which looks like a
/// catastrophic failure. It counts file-backed resident pages, and a memory-mapped
/// 995 MB package that is read end to end has all of its pages resident. That
/// memory is page cache: reclaimable at will, shared with every other reader of the
/// same file, and not a byte the tool allocated.
///
/// `RssAnon` is anonymous memory -- what the process actually allocated. Measured
/// on the current corpus:
///
/// | package | size | records | `RssAnon` peak | `RssFile` |
/// |---|---|---|---|---|
/// | `Spore_Content` | 995 MB | 17 119 | **3.9 MB** | 960 MB |
/// | `Spore_Graphics` | 943 MB | 24 707 | **9.3 MB** | 753 MB |
///
/// What the few megabytes hold is the parsed index (one `DbpfEntry` per row, which
/// `parse_index` returns as a `Vec` and which is unavoidable at this API), the
/// counters, and the map of *distinct* error messages. None of it grows with the
/// payload, which is the claim.
///
/// Linux-only (`/proc`); elsewhere it prints and returns.
#[test]
#[ignore = "needs SPORE/Data/Spore_Content.package"]
fn a_whole_package_walk_stays_memory_flat() {
    let Some(path) = content_package() else {
        return;
    };
    let exe = env!("CARGO_BIN_EXE_osptool");
    let mut child = std::process::Command::new(exe)
        .arg("verify")
        .arg(&path)
        .stdout(std::process::Stdio::null())
        .stderr(std::process::Stdio::null())
        .spawn()
        .expect("the binary must be runnable");

    let status_file = format!("/proc/{}/status", child.id());
    let mut anon_kb = 0u64;
    let mut file_kb = 0u64;
    while matches!(child.try_wait(), Ok(None)) {
        if let Ok(text) = std::fs::read_to_string(&status_file) {
            for line in text.lines() {
                let Some((key, rest)) = line.split_once(':') else {
                    continue;
                };
                let Some(value) = rest.split_whitespace().next() else {
                    continue;
                };
                match (key, value.parse::<u64>().unwrap_or(0)) {
                    ("RssAnon", value) => anon_kb = anon_kb.max(value),
                    ("RssFile", value) => file_kb = file_kb.max(value),
                    _ => {}
                }
            }
        }
        std::thread::sleep(std::time::Duration::from_millis(20));
    }
    assert!(child.wait().expect("the walk exits").success());
    if anon_kb == 0 {
        println!("skipped: /proc/<pid>/status RssAnon unavailable on this platform");
        return;
    }
    let package_mb = std::fs::metadata(&path)
        .map(|m| m.len() / (1024 * 1024))
        .unwrap_or(0);
    println!("peak RssAnon {anon_kb} kB, peak RssFile {file_kb} kB, package {package_mb} MB");
    assert!(
        anon_kb < 64 * 1024,
        "peak heap {anon_kb} kB over a {package_mb} MB package: the walk is accumulating"
    );
}
