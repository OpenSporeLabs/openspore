//! `extract`: bytes out, and the write confined to `--out`.

mod common;

use common::{osptool, package_of, Row, TempDir, MINI_PACKAGE};
use spore_tools::{EXIT_IO, EXIT_OK};

const TSTX: &str = "0x58545354:0x11111111:0x22222222";

#[test]
fn the_written_bytes_equal_the_record_bytes() {
    let dir = TempDir::new("extract-ok");
    let out = dir.path().display().to_string();
    let (code, stdout, err) = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", &out]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert_eq!(
        dir.entries(),
        vec!["0x58545354-58545354-11111111-22222222.bin"]
    );

    let written = std::fs::read(dir.path().join("0x58545354-58545354-11111111-22222222.bin"))
        .expect("the file must exist");
    // The fixture's first record is `bytes(range(16))`.
    let expected: Vec<u8> = (0..16u8).collect();
    assert_eq!(written, expected);
    assert_eq!(written.len(), 16);

    // And the report names the path and the byte count.
    assert!(stdout.contains("wrote "), "{stdout}");
    assert!(stdout.contains("16 bytes"), "{stdout}");
    assert!(stdout.contains(TSTX), "{stdout}");
}

#[test]
fn a_qfs_record_is_written_decompressed() {
    let dir = TempDir::new("extract-qfs");
    let out = dir.path().display().to_string();
    let (code, stdout, _err) = osptool(&[
        "extract",
        MINI_PACKAGE,
        "0x31534651:0x33333333:0x44444444",
        "--out",
        &out,
    ]);
    assert_eq!(code, EXIT_OK);
    let path = dir.entries().pop().expect("one file");
    let written = std::fs::read(dir.path().join(path)).expect("the file must exist");
    // 412 bytes in memory, 421 stored: the difference is the QFS framing, so a
    // 421-byte file would mean the compressed bytes were written verbatim.
    assert_eq!(
        written.len(),
        412,
        "the record must be written decompressed"
    );
    assert_eq!(&written[..16], &(0..16u8).collect::<Vec<u8>>()[..]);
    assert!(stdout.contains("412 bytes"), "{stdout}");
}

#[test]
fn a_named_type_gets_its_name_in_the_file_name() {
    let dir = TempDir::new("extract-named");
    let out = dir.path().display().to_string();
    let image = common::gmdl_package();
    let file = common::temp_package("extract-named", &image);
    let path = file.path().display().to_string();
    let (code, _stdout, err) = osptool(&[
        "extract",
        &path,
        "0x00e6bce5:0x40616201:0x067a0801",
        "--out",
        &out,
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    assert_eq!(dir.entries(), vec!["gmdl-00e6bce5-40616201-067a0801.bin"]);
}

#[test]
fn two_records_of_one_package_do_not_overwrite_each_other() {
    let dir = TempDir::new("extract-many");
    let out = dir.path().display().to_string();
    for key in [
        "0x58545354:0x11111111:0x22222222",
        "0x31534651:0x33333333:0x44444444",
        "0x42574152:0x55555555:0x66666666",
    ] {
        let (code, _stdout, err) = osptool(&["extract", MINI_PACKAGE, key, "--out", &out]);
        assert_eq!(code, EXIT_OK, "{err}");
    }
    assert_eq!(dir.entries().len(), 3);
}

#[test]
fn extracting_the_same_record_twice_is_idempotent() {
    let dir = TempDir::new("extract-twice");
    let out = dir.path().display().to_string();
    let first = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", &out]);
    let second = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", &out]);
    assert_eq!(first.0, EXIT_OK);
    assert_eq!(first, second, "the report and the name must both be stable");
    assert_eq!(dir.entries().len(), 1);
}

#[test]
fn the_package_is_never_modified() {
    let before = std::fs::read(MINI_PACKAGE).expect("fixture is readable");
    let dir = TempDir::new("extract-readonly");
    let out = dir.path().display().to_string();
    for key in [
        "0x58545354:0x11111111:0x22222222",
        "0x31534651:0x33333333:0x44444444",
        "0x42574152:0x55555555:0x66666666",
    ] {
        let _ = osptool(&["extract", MINI_PACKAGE, key, "--out", &out]);
    }
    let after = std::fs::read(MINI_PACKAGE).expect("fixture is readable");
    assert_eq!(before, after, "extract must not touch the package");
}

#[test]
fn an_out_dir_that_is_the_root_or_a_parent_reference_is_refused_before_any_write() {
    for refused in ["/", ".", "..", "out/.."] {
        let (code, _stdout, err) = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", refused]);
        assert_eq!(code, spore_tools::EXIT_USAGE, "{err}");
        assert!(err.contains("refused"), "{err}");
    }
}

#[test]
fn a_relative_out_dir_with_a_parent_component_is_accepted_by_the_parser() {
    // A `..` in the *middle* of a relative path is a normal location, not an
    // escape: `../out/dumps` is what a user writes when they want a sibling of
    // the current directory. Only a *trailing* `..` is refused.
    let request =
        spore_tools::parse(["extract", "p", "1:2:3", "--out", "../out/dumps"].map(str::to_owned))
            .expect("an ordinary relative path must parse");
    assert!(matches!(request, spore_tools::Request::Extract(_)));
}

#[test]
fn a_missing_intermediate_directory_is_an_io_failure_and_is_not_created() {
    // `extract` never runs `mkdir -p`. A `--out` whose parent does not exist is a
    // typo, and answering it by creating a directory tree somewhere above the
    // working directory is how a tool writes where nobody meant.
    let missing = format!("../osptool-missing-parent-{}/out", std::process::id());
    let (code, _stdout, err) = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", &missing]);
    assert_eq!(code, EXIT_IO, "{err}");
    assert!(
        !std::path::Path::new(&missing).exists(),
        "no directory tree may be created: {missing}"
    );
    assert!(err.contains("No such file or directory"), "{err}");
}

#[test]
fn a_missing_out_dir_is_an_io_failure_naming_the_path() {
    let missing = format!(
        "{}/osptool-does-not-exist-{}",
        std::env::temp_dir().display(),
        std::process::id()
    );
    let (code, _stdout, err) = osptool(&["extract", MINI_PACKAGE, TSTX, "--out", &missing]);
    assert_eq!(code, EXIT_IO, "{err}");
    assert!(err.contains("osptool-does-not-exist"), "{err}");
    // And nothing was created.
    assert!(!std::path::Path::new(&missing).exists());
}

#[test]
fn a_missing_record_is_exit_three_and_nothing_is_written() {
    let dir = TempDir::new("extract-miss");
    let out = dir.path().display().to_string();
    let (code, _stdout, err) = osptool(&[
        "extract",
        MINI_PACKAGE,
        "0xdeadbeef:0x11111111:0x22222222",
        "--out",
        &out,
    ]);
    assert_eq!(code, spore_tools::EXIT_NOT_FOUND, "{err}");
    assert!(dir.entries().is_empty(), "a miss must not create a file");
}

#[test]
fn a_record_that_cannot_be_extracted_writes_nothing() {
    // The index row claims an extent past the end of the image. `extract` reads
    // the bytes before naming the file, so the refusal happens first.
    let mut image = common::read_fixture("mini_package.dbpf");
    // Row 0's offset word sits after type/group/instance: 100 + 12.
    image[112..116].copy_from_slice(&0x00FF_FFFFu32.to_le_bytes());
    let file = common::temp_package("extract-badextent", &image);
    let path = file.path().display().to_string();
    let dir = TempDir::new("extract-badextent");
    let out = dir.path().display().to_string();
    let (code, _stdout, err) = osptool(&["extract", &path, TSTX, "--out", &out]);
    assert_eq!(code, spore_tools::EXIT_DECODE, "{err}");
    assert!(err.contains("dbpf"), "{err}");
    assert!(
        dir.entries().is_empty(),
        "a failed read must not leave a file"
    );
}

#[test]
fn a_record_with_an_unsupported_compression_word_is_refused_rather_than_written_raw() {
    let mut image = common::read_fixture("mini_package.dbpf");
    // Row 0's compression word: 100 + 24.
    image[124..126].copy_from_slice(&0x1234u16.to_le_bytes());
    let file = common::temp_package("extract-badcomp", &image);
    let path = file.path().display().to_string();
    let dir = TempDir::new("extract-badcomp");
    let out = dir.path().display().to_string();
    let (code, _stdout, err) = osptool(&["extract", &path, TSTX, "--out", &out]);
    assert_eq!(code, spore_tools::EXIT_DECODE, "{err}");
    assert!(err.contains("unsupported compression 0x1234"), "{err}");
    assert!(dir.entries().is_empty());
}

#[test]
fn a_synthetic_package_round_trips_through_extract() {
    // A payload that is not one of the committed fixtures' own bytes, so the
    // comparison is not accidentally comparing the fixture with itself.
    let payload: Vec<u8> = (0..300u32).map(|i| (i % 251) as u8).collect();
    let image = package_of(&[Row::new(
        0x0119_89B7,
        0x406b_6a00,
        0x0000_1234,
        payload.clone(),
    )]);
    let file = common::temp_package("extract-synthetic", &image);
    let path = file.path().display().to_string();
    let dir = TempDir::new("extract-synthetic");
    let out = dir.path().display().to_string();
    let (code, stdout, err) = osptool(&[
        "extract",
        &path,
        "0x011989b7:0x406b6a00:0x00001234",
        "--out",
        &out,
    ]);
    assert_eq!(code, EXIT_OK, "{err}");
    let name = dir.entries().pop().expect("one file");
    assert_eq!(name, "plt-011989b7-406b6a00-00001234.bin");
    assert_eq!(std::fs::read(dir.path().join(&name)).unwrap(), payload);
    assert!(stdout.contains("300 bytes"), "{stdout}");
    // And the written file is still a real file, not a symlink or a directory.
    assert!(dir.path().join(name).is_file());
    // The `Json` reader is used elsewhere in the suite; confirm it stays wired
    // in so a compile error here cannot silently disable that coverage.
    assert!(spore_tools::json::parse("[1]").is_ok());
}
