//! Comparison 2: record bytes, i.e. QFS decompression.
//!
//! Rust `spore_dbpf::extract_record` against `dbpf.py::getdata`, byte for byte,
//! for a deterministic bounded sample of the package.
//!
//! # Why the sample
//!
//! `getdata` decompresses into memory and the result must be shipped across a
//! process boundary, so the comparison cost per record is the record's
//! decompressed size. A sample of 200 records covers the whole index's shape
//! (stored and compressed, tiny and large) at a cost the harness can pay inside
//! one test run. The sample is drawn by [`crate::sample::sample_indices`]: the
//! first 50 rows, then every `stride`-th. No random draw, so any divergence
//! reported here can be re-run and land on the same record.
//!
//! # What a byte mismatch reports
//!
//! The first differing offset, the two lengths, and a hex window around the
//! difference from both sides. A decompression bug that only shows up on one
//! record is worthless without the offset, and the offset is the whole point.
//!
//! # One asymmetry worth knowing about
//!
//! `extract_record` additionally requires `payload.len() == memory_size` and
//! fails the record when that is false; `getdata` has no such check and returns
//! whatever it produced. A length disagreement where the bytes agree is
//! therefore reported as a one-sided decode with that named as the reason.

use spore_assets::Package;
use spore_dbpf::DbpfEntry;

use crate::corpus::{Corpus, LocatedPackage};
use crate::floats::ReportBuilder;
use crate::oracle::{classify_refusal, OracleConfig, OracleError, OracleSession};
use crate::report::{DifferentialReport, Divergence, DivergenceClass};
use crate::sample::{describe_sample, sample_indices};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "record-bytes-qfs";

/// How the oracle is invoked for this comparison.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one \
                              NDJSON {cmd:\"bytes\", i:N} request per sampled record, answered \
                              from dbpf.py::getdata and base64-encoded";

/// How many records the default sample draws.
pub const DEFAULT_SAMPLE: usize = 200;

/// Runs the byte comparison over the corpus's primary package.
pub fn compare(corpus: &Corpus, config: &OracleConfig) -> DifferentialReport {
    compare_with_budget(corpus, config, DEFAULT_SAMPLE)
}

/// Runs the byte comparison with an explicit sample budget.
pub fn compare_with_budget(
    corpus: &Corpus,
    config: &OracleConfig,
    budget: usize,
) -> DifferentialReport {
    super::run(NAME, || {
        let Some(package) = primary_package(corpus) else {
            return Ok::<_, OracleError>(skipped(
                NAME,
                format!(
                    "no package located (set {} to a checkout with SPORE/)",
                    crate::corpus::ROOT_ENV
                ),
            ));
        };
        compare_package(package, config, budget)
    })
}

/// Runs the byte comparison over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
    budget: usize,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {}; Rust side: spore_dbpf::extract_record (QFS + memory_size check); \
         oracle: dbpf.py::getdata (QFS only)",
        package.name
    ));

    // One mapping, alive for the whole loop, and one record's payload resident
    // at a time. Nothing accumulates across iterations.
    let mapped = Package::open(package.name.clone(), &package.path).map_err(|error| {
        OracleError::Protocol(format!("spore-assets could not map the package: {error}"))
    })?;
    let entries: Vec<DbpfEntry> = mapped.index().entries().to_vec();
    let image = mapped.bytes();

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;

    let indices = sample_indices(entries.len(), budget);
    builder.note(describe_sample(entries.len(), budget, indices.len()));

    let mut rust_failures = 0usize;
    let mut oracle_failures = 0usize;

    for index in indices {
        let Some(entry) = entries.get(index) else {
            continue;
        };
        let identity = info.identity(index, entry.type_id, entry.group_id, entry.instance_id);

        // One record in flight at a time: the payload is dropped at the end of
        // the iteration and nothing accumulates across the loop.
        let rust = spore_dbpf::extract_record(image, entry);
        let oracle = session.request_record("bytes", index);

        let (rust_bytes, rust_message) = match rust {
            Ok(bytes) => (Some(bytes), String::new()),
            Err(error) => {
                rust_failures += 1;
                (None, error.to_string())
            }
        };

        let oracle_bytes = match &oracle {
            Ok(value) => decode_base64(value),
            Err(_) => {
                oracle_failures += 1;
                None
            }
        };

        match (&rust_bytes, &oracle_bytes) {
            (Some(left), Some(right)) => {
                if left == right {
                    builder.record(crate::report::Agreement::Equal);
                } else {
                    builder.divergence(byte_divergence(
                        identity,
                        entry,
                        left,
                        right,
                        oracle.as_ref().ok(),
                    ));
                }
            }
            (None, None) => {
                let agreement = classify_refusal(
                    oracle.as_ref().map(|_| ()).map_err(OracleError::message),
                    rust_bytes
                        .as_ref()
                        .map(|_| ())
                        .ok_or_else(|| rust_message.clone()),
                );
                if let crate::report::Agreement::BothFailed { oracle, rust } = &agreement {
                    builder.record(agreement.clone());
                    builder.note(format!(
                        "{identity}: both refused this record; oracle={oracle:?} rust={rust:?}"
                    ));
                }
            }
            (Some(left), None) => {
                let why = oracle.as_ref().err().map_or_else(
                    || "the oracle sent no payload".to_owned(),
                    OracleError::message,
                );
                builder.divergence(
                    Divergence::value(
                        identity,
                        "record.bytes",
                        format!("<refused: {why}>"),
                        format!("{} bytes, sha-of-first-16 0x{}", left.len(), head_hex(left)),
                    )
                    .with_class(DivergenceClass::OneSidedDecode)
                    .with_note(
                        "the oracle could not extract this record and the Rust side could; the \
                         length shown is the Rust length",
                    ),
                );
            }
            (None, Some(right)) => {
                let why = oracle.as_ref().err().map_or_else(
                    || "the oracle sent no payload".to_owned(),
                    OracleError::message,
                );
                let _ = why;
                builder.divergence(
                    Divergence::value(
                        identity,
                        "record.bytes",
                        format!("{} bytes, first 16 {}", right.len(), head_hex(right)),
                        format!("<refused: {rust_message}>"),
                    )
                    .with_class(DivergenceClass::OneSidedDecode)
                    .with_note(
                        "the Rust side refused this record and the oracle could not; note that \
                         spore_dbpf::extract_record additionally enforces \
                         `payload.len() == memory_size`, which dbpf.py::getdata does not",
                    ),
                );
            }
        }
    }

    if rust_failures > 0 || oracle_failures > 0 {
        builder.note(format!(
            "{rust_failures} record(s) refused by Rust, {oracle_failures} refused by the oracle"
        ));
    }
    Ok(builder.finish())
}

/// A byte mismatch, quoted at the first offset where the two differ.
fn byte_divergence(
    identity: crate::report::RecordIdentity,
    entry: &DbpfEntry,
    rust: &[u8],
    oracle: &[u8],
    oracle_reply: Option<&crate::json::Json>,
) -> Divergence {
    let offset = first_difference(rust, oracle);
    let compressed_note = oracle_reply
        .and_then(|reply| reply.get("compressed"))
        .and_then(crate::json::Json::as_bool)
        .map_or_else(|| "unknown".to_owned(), |flag| flag.to_string());
    Divergence::value(
        identity,
        format!("record.bytes[0x{offset:x}]"),
        format!(
            "len={} byte=0x{:02x} window={}",
            oracle.len(),
            oracle.get(offset).copied().unwrap_or(0),
            window_hex(oracle, offset)
        ),
        format!(
            "len={} byte=0x{:02x} window={}",
            rust.len(),
            rust.get(offset).copied().unwrap_or(0),
            window_hex(rust, offset)
        ),
    )
    .with_note(format!(
        "first difference at offset 0x{offset:x}; lengths {} (oracle) vs {} (rust); index row \
         says csize={} msize={} compression=0x{:04x} compressed={compressed_note}",
        oracle.len(),
        rust.len(),
        entry.stored_size,
        entry.memory_size,
        entry.compression
    ))
}

/// The first offset at which two byte strings differ, or the length of the
/// shorter one when one is a prefix of the other.
#[must_use]
pub fn first_difference(left: &[u8], right: &[u8]) -> usize {
    left.iter()
        .zip(right.iter())
        .position(|(a, b)| a != b)
        .unwrap_or_else(|| left.len().min(right.len()))
}

/// 16 bytes of hex starting at `offset`, with `..` where the slice runs out.
fn window_hex(bytes: &[u8], offset: usize) -> String {
    let end = (offset + 16).min(bytes.len());
    let slice = bytes.get(offset..end).unwrap_or(&[]);
    let mut out = slice
        .iter()
        .map(|byte| format!("{byte:02x}"))
        .collect::<Vec<_>>()
        .join(" ");
    if end < bytes.len() {
        out.push_str(" ..");
    } else if offset > 0 {
        out.insert_str(0, ".. ");
    }
    out
}

fn head_hex(bytes: &[u8]) -> String {
    let end = bytes.len().min(16);
    bytes
        .get(..end)
        .unwrap_or(&[])
        .iter()
        .map(|byte| format!("{byte:02x}"))
        .collect::<Vec<_>>()
        .join("")
}

/// Reads the driver's base64 payload. A malformed encoding is a protocol error,
/// never a silently empty buffer.
fn decode_base64(value: &crate::json::Json) -> Option<Vec<u8>> {
    let text = value.get("b64")?.as_str()?;
    let mut out = Vec::with_capacity(text.len() / 4 * 3);
    let mut accumulator = 0u32;
    let mut bits = 0u32;
    for ch in text.bytes() {
        let digit = match ch {
            b'A'..=b'Z' => u32::from(ch - b'A'),
            b'a'..=b'z' => u32::from(ch - b'a') + 26,
            b'0'..=b'9' => u32::from(ch - b'0') + 52,
            b'+' => 62,
            b'/' => 63,
            b'=' => break,
            b'\n' | b'\r' => continue,
            _ => return None,
        };
        accumulator = (accumulator << 6) | digit;
        bits += 6;
        if bits >= 8 {
            bits -= 8;
            out.push(((accumulator >> bits) & 0xFF) as u8);
        }
    }
    Some(out)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn base64_round_trips_through_the_hand_rolled_decoder() {
        for payload in [
            &b""[..],
            b"a",
            b"ab",
            b"abc",
            b"abcd",
            &[0u8, 255, 128, 7, 3][..],
        ] {
            let encoded = {
                let mut text = String::new();
                const ALPHABET: &[u8] =
                    b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
                for chunk in payload.chunks(3) {
                    let b = [
                        chunk[0],
                        *chunk.get(1).unwrap_or(&0),
                        *chunk.get(2).unwrap_or(&0),
                    ];
                    let n = (u32::from(b[0]) << 16) | (u32::from(b[1]) << 8) | u32::from(b[2]);
                    let indices = [n >> 18 & 63, n >> 12 & 63, n >> 6 & 63, n & 63];
                    for (position, index) in indices.iter().enumerate() {
                        if position > chunk.len() {
                            text.push('=');
                        } else {
                            text.push(ALPHABET[*index as usize] as char);
                        }
                    }
                }
                text
            };
            let value = crate::json::object(vec![("b64", crate::json::Json::Str(encoded.clone()))]);
            assert_eq!(decode_base64(&value).as_deref(), Some(payload), "{encoded}");
        }
    }

    #[test]
    fn a_non_base64_payload_is_rejected_rather_than_read_as_empty() {
        let value = crate::json::object(vec![("b64", crate::json::Json::Str("not*base64".into()))]);
        assert_eq!(decode_base64(&value), None);
        let empty = crate::json::object(vec![("len", crate::json::Json::Num(4.0))]);
        assert_eq!(decode_base64(&empty), None);
    }

    #[test]
    fn the_first_difference_is_reported_where_the_bytes_part_company() {
        assert_eq!(first_difference(&[1, 2, 3], &[1, 2, 3]), 3);
        assert_eq!(first_difference(&[1, 2, 3], &[1, 9, 3]), 1);
        assert_eq!(first_difference(&[1, 2], &[1, 2, 3]), 2);
        assert_eq!(first_difference(&[], &[1]), 0);
    }

    #[test]
    fn a_window_is_hex_and_marks_where_it_ran_out() {
        assert_eq!(window_hex(&[0xAB; 4], 0), "ab ab ab ab");
        assert_eq!(window_hex(&[0xAB; 4], 2), ".. ab ab");
        assert!(window_hex(&[0xAB; 4], 0).ends_with("ab ab ab ab"));
    }
}
