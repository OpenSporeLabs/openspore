//! Comparison 5: the raster envelope and the DXT5 base mip.
//!
//! Rust `spore_texture::parse_envelope` / `spore_texture::decode_raster` against
//! `tools/spore/raster/raster.py::parse_envelope` / `::decode` and
//! `tools/spore/dxt5/dxt5.py::decode_image`, for a deterministic bounded sample.
//!
//! # Two comparisons, two confidences
//!
//! * The 32-byte envelope is compared field by field (eight `u32`s). Both sides
//!   read the envelope without validating it, so this is a clean field
//!   comparison.
//! * The decoded base mip is compared by `sha256(rgba)[:16]`, which is exactly
//!   what `raster.py`'s own CLI prints. A hash is the right instrument here: the
//!   decoded image is megabytes, and "are these the same bytes" is the only
//!   question that matters. Only a small number of records are decoded, because
//!   decoding is the expensive part.
//!
//! # The `0x15xx` luminance family is an expected refusal
//!
//! `spore-texture` refuses any `fourcc` other than `DXT5` **by name**, and says
//! in its own error text that the `0x15xx` family is a different format rather
//! than an unrecognised one. `raster.py::parse_envelope` accepts any `fourcc`
//! (it does not validate) but `raster.py::decode` refuses a non-DXT5 fourcc
//! too. So a `0x15xx` record produces a field-for-field envelope comparison
//! that agrees, plus a decode refusal on both sides -- which is
//! [`Agreement::BothFailed`], never a divergence.

use spore_assets::Package;
use spore_core::record::type_id;

use crate::corpus::{Corpus, LocatedPackage};
use crate::floats::ReportBuilder;
use crate::json::Json;
use crate::oracle::{classify_refusal, OracleConfig, OracleError, OracleSession};
use crate::report::{Agreement, DifferentialReport, Divergence, DivergenceClass};
use crate::sample::{describe_sample, sample_indices};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "raster-envelope-dxt5";

/// How the oracle is invoked.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; one \
                              NDJSON {cmd:\"raster\", i:N} request per sampled record, answered \
                              from raster.py::parse_envelope and raster.py::decode \
                              (which calls dxt5.py::decode_image)";

/// How many records the default sample draws for the envelope comparison.
pub const DEFAULT_SAMPLE: usize = 150;

/// How many of the sampled records are also decoded and hashed.
pub const DEFAULT_DECODE_SAMPLE: usize = 12;

/// The `0x15xx` luminance family, as the two sides each spell it.
pub const LUMINANCE_LOW: u32 = 0x1500;
/// Upper bound of the refused luminance family.
pub const LUMINANCE_HIGH: u32 = 0x15FF;

/// True when `fourcc` is in the luminance family Rust refuses by name.
#[must_use]
pub fn is_luminance(fourcc: u32) -> bool {
    (LUMINANCE_LOW..=LUMINANCE_HIGH).contains(&fourcc)
}

/// Runs the raster comparison over the corpus's primary package.
pub fn compare(corpus: &Corpus, config: &OracleConfig) -> DifferentialReport {
    compare_with_budgets(corpus, config, DEFAULT_SAMPLE, DEFAULT_DECODE_SAMPLE)
}

/// Runs the raster comparison with explicit sample budgets.
pub fn compare_with_budgets(
    corpus: &Corpus,
    config: &OracleConfig,
    budget: usize,
    decode_budget: usize,
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
        compare_package(package, config, budget, decode_budget)
    })
}

/// Runs the raster comparison over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
    budget: usize,
    decode_budget: usize,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {}; Rust side: spore_texture::parse_envelope and decode_dxt5_mip; oracle: \
         raster.py::parse_envelope and raster.py::decode (dxt5.py::decode_image)",
        package.name
    ));

    let opened = Package::open(package.name.clone(), &package.path).map_err(|error| {
        OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
    })?;
    let image = opened.bytes();
    let targets: Vec<(usize, spore_dbpf::DbpfEntry)> = opened
        .index()
        .entries()
        .iter()
        .enumerate()
        .filter(|(_, entry)| entry.type_id == type_id::RASTER)
        .map(|(index, entry)| (index, *entry))
        .collect();

    if targets.is_empty() {
        builder.skip(format!(
            "{} holds no 0x{:08x} (raster) records, so there is nothing to compare",
            package.name,
            type_id::RASTER
        ));
        return Ok(builder.finish());
    }
    // The sample is over the FILTERED raster list; the oracle addresses records
    // by their PACKAGE row. See the note in `gmdl::compare_package` -- mixing
    // the two numbering systems compares two different records.
    let sampled = sample_indices(targets.len(), budget);
    let decoded: Vec<usize> = sampled.iter().copied().take(decode_budget).collect();
    builder.note(format!(
        "{} raster record(s) in {}; envelope compared on {}; base mip decoded and hashed on {}",
        targets.len(),
        package.name,
        sampled.len(),
        decoded.len()
    ));
    builder.note(describe_sample(targets.len(), budget, sampled.len()));

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;
    let mut luminance_refusals = 0usize;

    for sample in &sampled {
        let Some((package_index, entry)) = targets.get(*sample) else {
            continue;
        };
        let identity = info.identity(
            *package_index,
            entry.type_id,
            entry.group_id,
            entry.instance_id,
        );
        let bytes = match spore_dbpf::extract_record(image, entry) {
            Ok(bytes) => bytes,
            Err(error) => {
                builder.record(Agreement::RustOnly(format!(
                    "spore_dbpf::extract_record refused the record before the envelope was read: \
                     {error}"
                )));
                continue;
            }
        };

        let rust_envelope = spore_texture::parse_envelope(&bytes);
        // The PACKAGE row, not the position in the raster-filtered list.
        let oracle = session.request_record("raster", *package_index);

        let oracle_envelope = match oracle.as_ref().ok().and_then(|reply| reply.get("env")) {
            Some(env) => env.clone(),
            None => {
                let agreement = classify_refusal(
                    oracle.as_ref().map(|_| ()).map_err(|error| error.message()),
                    rust_envelope
                        .as_ref()
                        .map(|_| ())
                        .map_err(|error| error.to_string()),
                );
                builder.record(agreement);
                continue;
            }
        };

        let Ok(envelope) = rust_envelope else {
            let rust_error = rust_envelope.expect_err("the Ok arm was just handled");
            let why = oracle.as_ref().err().map_or_else(
                || "the oracle sent no envelope".to_owned(),
                OracleError::message,
            );
            builder.divergence(
                Divergence::value(
                    identity,
                    "envelope",
                    format!("<refused: {why}>"),
                    rust_error.to_string(),
                )
                .with_class(DivergenceClass::OneSidedDecode),
            );
            continue;
        };

        compare_envelope_fields(&mut builder, &identity, &oracle_envelope, &envelope);

        if !decoded.contains(sample) {
            continue;
        }
        let fourcc = envelope.fourcc;
        let rust_decode = spore_texture::decode_raster(&bytes);
        let oracle_sha: Result<String, String> = oracle
            .as_ref()
            .ok()
            .and_then(|reply| reply.get("mip0_sha16"))
            .and_then(Json::as_str)
            .map_or_else(
                || Err(oracle_reason(oracle.as_ref())),
                |sha| Ok(sha.to_owned()),
            );

        if let Some(rust_error) = rust_decode.as_ref().err() {
            if is_luminance(fourcc) {
                luminance_refusals += 1;
            }
            let agreement = classify_refusal(
                oracle_sha.clone().map(|_| ()),
                rust_decode
                    .as_ref()
                    .map(|_| ())
                    .map_err(|error| error.to_string()),
            );
            builder.record(agreement.clone());
            if let Agreement::BothFailed { oracle, rust } = agreement {
                builder.note(format!(
                    "{identity}: both sides refused to decode this raster; oracle={oracle:?} \
                     rust={rust:?}"
                ));
            }
            if is_luminance(fourcc) {
                builder.note(format!(
                    "{identity}: fourcc 0x{fourcc:08x} is in the 0x15xx luminance family, which \
                     spore-texture refuses by name because it is a different format rather than an \
                     unrecognised one. This refusal is expected and is classified as both-failed, \
                     not as a divergence. Rust said: {}",
                    rust_error
                ));
            }
            continue;
        }
        let decoded_image = rust_decode.expect("checked above");
        let first = decoded_image.layers.first().and_then(|layer| layer.first());
        let rust_sha = first.map(|mip| spore_sha_hex16(&mip.pixels));
        match (rust_sha.clone(), oracle_sha.clone()) {
            (Some(rust_hex), Ok(oracle_hex)) => {
                if rust_hex == oracle_hex {
                    builder.record(Agreement::Equal);
                } else {
                    builder.divergence(
                        Divergence::value(identity, "mip0.sha256[:16]", oracle_hex, rust_hex)
                            .with_note(format!(
                                "{}x{} base mip, RGBA8, hashed after decode; the oracle prints \
                             exactly this digest in raster.py's own CLI output",
                                first.map_or(0, |mip| mip.width),
                                first.map_or(0, |mip| mip.height)
                            )),
                    );
                }
            }
            _ => {
                builder.divergence(
                    Divergence::value(
                        identity,
                        "mip0.sha256[:16]",
                        oracle_sha
                            .clone()
                            .err()
                            .unwrap_or_else(|| "<no digest>".to_owned()),
                        rust_sha.unwrap_or_else(|| "<no digest>".to_owned()),
                    )
                    .with_class(DivergenceClass::OneSidedDecode)
                    .with_note("only one side produced a digest for the base mip"),
                );
            }
        }
    }

    if luminance_refusals > 0 {
        builder.note(format!(
            "{luminance_refusals} sampled raster(s) were in the 0x15xx luminance family and were \
             refused by name on both sides; see the per-record notes"
        ));
    }
    Ok(builder.finish())
}

/// The eight envelope words, field by field.
fn compare_envelope_fields(
    builder: &mut ReportBuilder,
    identity: &crate::report::RecordIdentity,
    oracle: &Json,
    envelope: &spore_texture::RasterEnvelope,
) {
    for (field, rust_value) in [
        ("version", envelope.version),
        ("width", envelope.width),
        ("height", envelope.height),
        ("mipCount", envelope.mip_count),
        ("field_10", envelope.field_10),
        ("fourcc", envelope.fourcc),
        ("field_18", envelope.field_18),
        ("field_1c", envelope.field_1c),
    ] {
        // The oracle spells mipCount where Rust spells mip_count; both are
        // reported under one name so the field path means one thing.
        match oracle.get(field).and_then(Json::as_u32) {
            None => builder.note(format!(
                "{identity}: the oracle envelope carried no `{field}` field, so it was not compared"
            )),
            Some(value) if value == rust_value => {}
            Some(value) => builder.divergence(Divergence::value(
                identity.clone(),
                format!("envelope.{field}"),
                format!("0x{value:08x} ({value})"),
                format!("0x{rust_value:08x} ({rust_value})"),
            )),
        }
    }
    builder.record(Agreement::Equal);
}

fn oracle_reason(oracle: Result<&Json, &OracleError>) -> String {
    match oracle {
        Ok(_) => "the oracle reply carried no digest".to_owned(),
        Err(error) => format!("the oracle refused or failed: {}", error.message()),
    }
}

/// A minimal SHA-256, so the decoded mip can be compared against the digest
/// `raster.py` prints without adding a dependency.
///
/// Only the 16 hex characters the oracle prints are needed, but the full digest
/// is computed anyway: a truncated hash would be a weaker comparison than the
/// one being claimed.
mod spore_sha {
    const K: [u32; 64] = [
        0x428a_2f98,
        0x7137_4491,
        0xb5c0_fbcf,
        0xe9b5_dba5,
        0x3956_c25b,
        0x59f1_11f1,
        0x923f_82a4,
        0xab1c_5ed5,
        0xd807_aa98,
        0x1283_5b01,
        0x2431_85be,
        0x550c_7dc3,
        0x72be_5d74,
        0x80de_b1fe,
        0x9bdc_06a7,
        0xc19b_f174,
        0xe49b_69c1,
        0xefbe_4786,
        0x0fc1_9dc6,
        0x240c_a1cc,
        0x2de9_2c6f,
        0x4a74_84aa,
        0x5cb0_a9dc,
        0x76f9_88da,
        0x983e_5152,
        0xa831_c66d,
        0xb003_27c8,
        0xbf59_7fc7,
        0xc6e0_0bf3,
        0xd5a7_9147,
        0x06ca_6351,
        0x1429_2967,
        0x27b7_0a85,
        0x2e1b_2138,
        0x4d2c_6dfc,
        0x5338_0d13,
        0x650a_7354,
        0x766a_0abb,
        0x81c2_c92e,
        0x9272_2c85,
        0xa2bf_e8a1,
        0xa81a_664b,
        0xc24b_8b70,
        0xc76c_51a3,
        0xd192_e819,
        0xd699_0624,
        0xf40e_3585,
        0x106a_a070,
        0x19a4_c116,
        0x1e37_6c08,
        0x2748_774c,
        0x34b0_bcb5,
        0x391c_0cb3,
        0x4ed8_aa4a,
        0x5b9c_ca4f,
        0x682e_6ff3,
        0x748f_82ee,
        0x78a5_636f,
        0x84c8_7814,
        0x8cc7_0208,
        0x90be_fffa,
        0xa450_6ceb,
        0xbef9_a3f7,
        0xc671_78f2,
    ];

    /// A streaming SHA-256.
    #[derive(Clone)]
    pub struct Sha256 {
        state: [u32; 8],
        buffer: [u8; 64],
        buffered: usize,
        length_bits: u64,
    }

    impl Sha256 {
        #[must_use]
        pub fn new() -> Self {
            Self {
                state: [
                    0x6a09_e667,
                    0xbb67_ae85,
                    0x3c6e_f372,
                    0xa54f_f53a,
                    0x510e_527f,
                    0x9b05_688c,
                    0x1f83_d9ab,
                    0x5be0_cd19,
                ],
                buffer: [0u8; 64],
                buffered: 0,
                length_bits: 0,
            }
        }

        pub fn write(&mut self, byte: u8) {
            self.buffer[self.buffered] = byte;
            self.buffered += 1;
            self.length_bits = self.length_bits.wrapping_add(8);
            if self.buffered == 64 {
                let block = self.buffer;
                self.compress(&block);
                self.buffered = 0;
            }
        }

        pub fn hex16(mut self) -> String {
            let bits = self.length_bits;
            self.write_raw(0x80);
            while self.buffered != 56 {
                self.write_raw(0x00);
            }
            // The length is a big-endian u64 in the last 8 bytes, so the MOST
            // significant byte goes first. Writing it little-endian happens to
            // agree with the reference only when the length is zero, which is
            // exactly the case a test that only hashes the empty string would
            // miss.
            for shift in (0..64).step_by(8).rev() {
                self.write_raw(((bits >> shift) & 0xFF) as u8);
            }
            let mut out = String::with_capacity(16);
            for word in self.state {
                out.push_str(&format!("{word:08x}"));
            }
            // The oracle prints `sha256(rgba).hexdigest()[:16]`.
            out.truncate(16);
            out
        }

        fn write_raw(&mut self, byte: u8) {
            self.buffer[self.buffered] = byte;
            self.buffered += 1;
            if self.buffered == 64 {
                let block = self.buffer;
                self.compress(&block);
                self.buffered = 0;
            }
        }

        fn compress(&mut self, block: &[u8; 64]) {
            let mut w = [0u32; 64];
            for (index, word) in w.iter_mut().take(16).enumerate() {
                let base = index * 4;
                *word = u32::from_be_bytes([
                    block[base],
                    block[base + 1],
                    block[base + 2],
                    block[base + 3],
                ]);
            }
            for index in 16..64 {
                let s0 = w[index - 15].rotate_right(7)
                    ^ w[index - 15].rotate_right(18)
                    ^ (w[index - 15] >> 3);
                let s1 = w[index - 2].rotate_right(17)
                    ^ w[index - 2].rotate_right(19)
                    ^ (w[index - 2] >> 10);
                w[index] = w[index - 16]
                    .wrapping_add(s0)
                    .wrapping_add(w[index - 7])
                    .wrapping_add(s1);
            }
            let [mut a, mut b, mut c, mut d, mut e, mut f, mut g, mut h] = self.state;
            for index in 0..64 {
                let s1 = e.rotate_right(6) ^ e.rotate_right(11) ^ e.rotate_right(25);
                let ch = (e & f) ^ ((!e) & g);
                let temp1 = h
                    .wrapping_add(s1)
                    .wrapping_add(ch)
                    .wrapping_add(K[index])
                    .wrapping_add(w[index]);
                let s0 = a.rotate_right(2) ^ a.rotate_right(13) ^ a.rotate_right(22);
                let maj = (a & b) ^ (a & c) ^ (b & c);
                let temp2 = s0.wrapping_add(maj);
                h = g;
                g = f;
                f = e;
                e = d.wrapping_add(temp1);
                d = c;
                c = b;
                b = a;
                a = temp1.wrapping_add(temp2);
            }
            for (slot, value) in self.state.iter_mut().zip([a, b, c, d, e, f, g, h]) {
                *slot = slot.wrapping_add(value);
            }
        }
    }

    impl Default for Sha256 {
        fn default() -> Self {
            Self::new()
        }
    }

    /// The first 16 hex characters of `sha256(bytes)`, which is exactly what
    /// `raster.py` prints.
    #[must_use]
    pub fn hex16_of(bytes: &[u8]) -> String {
        let mut hash = Sha256::new();
        for byte in bytes {
            hash.write(*byte);
        }
        hash.hex16()
    }
}

/// Convenience alias for [`spore_sha::hex16_of`].
fn spore_sha_hex16(bytes: &[u8]) -> String {
    spore_sha::hex16_of(bytes)
}

#[cfg(test)]
mod tests {
    use super::spore_sha::Sha256;
    use super::*;

    #[test]
    fn the_hand_rolled_sha256_matches_the_known_vectors() {
        // If this is wrong every mip comparison is wrong, and it would be wrong
        // quietly: both sides would produce a different-but-stable hex string.
        let hex = |text: &str| {
            let mut hash = Sha256::new();
            for byte in text.as_bytes() {
                hash.write(*byte);
            }
            hash.hex16()
        };
        assert_eq!(hex(""), "e3b0c44298fc1c14");
        assert_eq!(hex("abc"), "ba7816bf8f01cfea");
        assert_eq!(
            hex("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
            "248d6a61d20638b8"
        );
        // Longer than one block, so the buffering and the length encoding are
        // exercised too.
        assert_eq!(hex(&"a".repeat(1000)), "41edece42d63e8d9");
    }

    #[test]
    fn the_luminance_family_is_the_one_the_crate_says_it_is() {
        assert!(is_luminance(0x1500));
        assert!(is_luminance(0x15FF));
        assert!(!is_luminance(0x14FF));
        assert!(!is_luminance(0x1600));
        assert!(!is_luminance(spore_texture::DXT5_FOURCC));
    }
}
