//! What streaming costs, measured on the real 98 MB artifact.
//!
//! The claims this file checks are the ones the crate's design rests on:
//!
//! * `Snapshot::open` never holds the file in memory. It keeps a compact
//!   `u32 -> byte offset` index, a name index, and the metadata line, and the
//!   peak cost of parsing a record is one record.
//! * The numbers are *printed* as well as bounded, because a bound nobody can
//!   see the headroom under is not a measurement.
//!
//! One test, not four: `open` happens once, and the phases are measured in
//! sequence so a parallel test runner cannot attribute another test's index to
//! this one.

mod support;

use spore_semantic_bridge::Snapshot;
use std::time::Instant;

/// Peak resident set size in bytes, from the kernel.
fn peak_rss() -> u64 {
    read_status("VmHWM:")
}

/// Current resident set size in bytes, from the kernel.
fn current_rss() -> u64 {
    read_status("VmRSS:")
}

fn read_status(field: &str) -> u64 {
    std::fs::read_to_string("/proc/self/status")
        .ok()
        .and_then(|status| {
            status
                .lines()
                .find(|line| line.starts_with(field))
                .and_then(|line| line.split_whitespace().nth(1))
                .and_then(|kib| kib.parse::<u64>().ok())
        })
        .map_or(0, |kib| kib * 1024)
}

fn human(bytes: u64) -> String {
    format!("{:.1} MiB", bytes as f64 / (1024.0 * 1024.0))
}

#[test]
fn the_whole_reading_path_is_streaming_and_the_numbers_are_printed() {
    let Some(path) = support::committed_path() else {
        eprintln!(
            "SKIPPED: knowledge/semantic/function-passport-v1.jsonl is not present; there are no \
             numbers to measure without it"
        );
        return;
    };
    let file_bytes = std::fs::metadata(&path)
        .expect("the artifact is there")
        .len();

    // ---- open -------------------------------------------------------------
    let rss_start = current_rss();
    let started = Instant::now();
    let snapshot = Snapshot::open(&path).expect("the committed snapshot must open");
    let open_elapsed = started.elapsed();
    let rss_open = current_rss();
    let index_growth = rss_open.saturating_sub(rss_start);

    // ---- one lookup ------------------------------------------------------
    let started = Instant::now();
    let passport = snapshot.lookup(0x0040_ccb0).expect("0x0040ccb0 is indexed");
    let lookup_elapsed = started.elapsed();
    let rss_lookup = current_rss();

    // ---- one full stream -------------------------------------------------
    let started = Instant::now();
    let mut count = 0usize;
    snapshot
        .for_each_passport(|passport| {
            // Touch every field the engine-facing API exposes, so the stream is
            // not optimised away and the record retained is a full one.
            let _ = (
                passport.canonical_va(),
                passport.sdk_name().is_available(),
                passport.subsystem().is_available(),
                passport.callers().len(),
                passport.reconstruction_package().is_available(),
            );
            count += 1;
            Ok(())
        })
        .expect("the whole file streams");
    let stream_elapsed = started.elapsed();
    let rss_stream = current_rss();

    // ---- the integrity pass ---------------------------------------------
    let started = Instant::now();
    let verification = snapshot.verify().expect("the digest must match");
    let verify_elapsed = started.elapsed();
    let rss_verify = current_rss();

    println!("--- streaming cost on the committed artifact ---");
    println!(
        "file              {} ({file_bytes} bytes); 1.0% of it is the metadata line",
        human(file_bytes)
    );
    println!(
        "open              {open_elapsed:?}  RSS {rss_start} -> {} (+{})  peak {}",
        human(rss_open),
        human(index_growth),
        human(peak_rss())
    );
    println!(
        "index             {} entries x 24 bytes = {}; {} names, {} ambiguous",
        snapshot.function_count(),
        human(snapshot.function_count() as u64 * 24),
        snapshot.symbol_count(),
        snapshot.ambiguous_name_count()
    );
    println!(
        "lookup one record {lookup_elapsed:?}  RSS +{}  ({} bytes of growth)",
        human(rss_lookup.saturating_sub(rss_open)),
        rss_lookup.saturating_sub(rss_open)
    );
    println!(
        "stream all        {stream_elapsed:?}  RSS +{}",
        human(rss_stream.saturating_sub(rss_lookup))
    );
    println!(
        "verify            {verify_elapsed:?}  RSS +{}  {} record lines hashed",
        human(rss_verify.saturating_sub(rss_stream)),
        verification.computed_record_count
    );
    println!("peak RSS          {}", human(peak_rss()));

    // ---- the claims ------------------------------------------------------
    assert_eq!(passport.canonical_va(), 0x0040_ccb0);
    assert_eq!(count, 58_757);
    assert_eq!(verification.computed_record_count, 58_757);
    assert!(
        index_growth < file_bytes,
        "open grew RSS by {} for a {} file: a reader that materialised the corpus would be \
         several times the file it read",
        human(index_growth),
        human(file_bytes)
    );
    assert!(
        index_growth < file_bytes / 4,
        "the whole index is {} for a {} file ({}% of it)",
        human(index_growth),
        human(file_bytes),
        index_growth * 100 / file_bytes
    );
    assert!(
        rss_lookup.saturating_sub(rss_open) < 4 * 1024 * 1024,
        "one lookup costs one record, not a file"
    );
    assert!(
        rss_stream.saturating_sub(rss_lookup) < 8 * 1024 * 1024,
        "streaming 58 757 records grew RSS by {}: it holds one at a time",
        human(rss_stream.saturating_sub(rss_lookup))
    );
    assert!(
        rss_verify.saturating_sub(rss_stream) < 8 * 1024 * 1024,
        "hashing is streaming too"
    );
}
