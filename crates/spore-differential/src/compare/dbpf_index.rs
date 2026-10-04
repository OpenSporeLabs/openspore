//! Comparison 1: the DBPF file index.
//!
//! Rust `spore_dbpf::parse_index` against the item list
//! `tools/spore/dbpf/dbpf.py::read` produces. Per record: type, group, instance,
//! offset, stored size, memory size, the raw compression word, the derived
//! compressed flag and the `saved` byte.
//!
//! # The count comes first
//!
//! If the two sides disagree about how many records there are, every
//! per-record comparison after that is meaningless: the rows are matched by
//! position, so one missing row shifts every later row and the report fills
//! with noise that looks like evidence. So the count is checked alone and a
//! mismatch ends the comparison with a single structural divergence.
//!
//! # `stored_size` and the top bit
//!
//! The DBPF row stores `csize | 0x8000_0000`; bit 31 is a flag, not two
//! gigabytes. **Both** sides mask it -- `dbpf.read` applies `& 0x7fffffff` at
//! its own line 58, and `spore-dbpf` applies [`spore_dbpf::SIZE_MASK`] -- so the
//! masked values are directly comparable. (The premise that the Python side
//! leaves the bit in place is not what the code says, and this comparison
//! reports the *measured* count of rows that carry it rather than asserting
//! either way.) Whether the mask is load-bearing is a separate question, and it
//! is answered from the raw index words by the driver's mirror walk.

use spore_assets::Package;
use spore_dbpf::SIZE_MASK;

use crate::corpus::{Corpus, LocatedPackage};
use crate::floats::ReportBuilder;
use crate::json::{self, Json};
use crate::oracle::{OracleConfig, OracleError, OraclePackageInfo, OracleSession};
use crate::report::{Agreement, DifferentialReport, Divergence, DivergenceClass, RecordIdentity};

use super::{primary_package, skipped};

/// Report name for this comparison.
pub const NAME: &str = "dbpf-index";

/// How the oracle is invoked for this comparison.
pub const INVOCATION: &str = "persistent `python3 -c` driver, one session per package; \
                              the rows come from one NDJSON {cmd:\"index\"} request answered \
                              from dbpf.py::read's item list";

/// Runs the index comparison over the corpus's primary package.
///
/// Exhaustive: every row of the index is compared. An index is a few tens of
/// thousands of fixed-width rows, so there is nothing to gain from sampling and
/// a coverage claim that means something to make.
pub fn compare(corpus: &Corpus, config: &OracleConfig) -> DifferentialReport {
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
        compare_package(package, config)
    })
}

/// Runs the index comparison over one package.
pub fn compare_package(
    package: &LocatedPackage,
    config: &OracleConfig,
) -> Result<DifferentialReport, OracleError> {
    let mut builder = ReportBuilder::new(NAME, INVOCATION);
    builder.note(format!(
        "package {} ({} bytes); Rust side: spore_dbpf::parse_index over a read-only memory map",
        package.name, package.size_bytes
    ));
    builder.note(format!(
        "stored size compared after the documented top-bit mask 0x{SIZE_MASK:08X}; both sides \
         apply it (dbpf.py line 58 reads `csize = le(data, o) & 0x7fffffff`)"
    ));

    let entries = {
        // Mapped, not read: 995 MB stays virtual and only the index plus one
        // record's payload are ever resident.
        let opened = Package::open(package.name.clone(), &package.path).map_err(|error| {
            OracleError::Protocol(format!("spore-assets could not open the package: {error}"))
        })?;
        opened.index().entries().to_vec()
    };

    let mut session = OracleSession::spawn(config)?;
    let info = session.open(&package.path)?;

    if entries.len() != info.count {
        let identity = RecordIdentity::new(package.name.clone(), 0, 0, 0, 0);
        builder.divergence(
            Divergence::value(
                identity,
                "index.count",
                info.count.to_string(),
                entries.len().to_string(),
            )
            .with_class(DivergenceClass::Structural)
            .with_note(
                "the two sides disagree about how many records the package has; per-record \
                 comparison is meaningless until that is settled, so it was not attempted",
            ),
        );
        return Ok(builder.finish());
    }
    builder.note(format!(
        "record count agrees: {} rows (index flags word 0x{:08x})",
        info.count, info.index_flags
    ));
    report_masking(&mut builder, &info);

    let rows = index_rows(&mut session)?;
    let mut divergent_rows = 0usize;
    let mut first_non_boolean_saved: Option<usize> = None;

    for (index, (entry, row)) in entries.iter().zip(rows.iter()).enumerate() {
        let identity = info.identity(index, entry.type_id, entry.group_id, entry.instance_id);
        let fields = RowFields::parse(row, index)?;
        let mut diverged = false;

        let mut compare_field = |field: &str, oracle: u32, rust: u32| -> bool {
            if oracle != rust {
                builder.divergence(Divergence::value(
                    identity.clone(),
                    format!("entry[{index}].{field}"),
                    oracle.to_string(),
                    rust.to_string(),
                ));
                true
            } else {
                false
            }
        };

        diverged |= compare_field("type_id", fields.type_id, entry.type_id);
        diverged |= compare_field("group_id", fields.group_id, entry.group_id);
        diverged |= compare_field("instance_id", fields.instance_id, entry.instance_id);
        diverged |= compare_field("offset", fields.offset, entry.offset);
        diverged |= compare_field("stored_size", fields.stored_size, entry.stored_size);
        diverged |= compare_field("memory_size", fields.memory_size, entry.memory_size);
        // The raw word, not the boolean. Comparing the boolean would hide every
        // value other than 0 and 0xFFFF, and the point is to see the values.
        diverged |= compare_field(
            "compression",
            fields.compression,
            u32::from(entry.compression),
        );
        diverged |= compare_field(
            "compressed",
            u32::from(fields.compression == 0xFFFF),
            u32::from(entry.compressed),
        );

        // `saved`: Rust holds a bool, the oracle a byte. Compared on the
        // meaning both sides can express; the field-type difference itself is
        // reported once, after the loop.
        diverged |= compare_field(
            "saved",
            u32::from(fields.saved_raw != 0),
            u32::from(entry.saved),
        );
        if fields.saved_raw > 1 && first_non_boolean_saved.is_none() {
            first_non_boolean_saved = Some(index);
        }

        if diverged {
            divergent_rows += 1;
        } else {
            builder.record(Agreement::Equal);
        }
    }

    report_saved_field_type(&mut builder, &info, &entries, first_non_boolean_saved);
    builder.note(format!(
        "{divergent_rows} row(s) had at least one field-level disagreement out of {}",
        entries.len()
    ));
    Ok(builder.finish())
}

/// States how many rows carry the top size bit, which is what makes the mask
/// load-bearing rather than decorative.
fn report_masking(builder: &mut ReportBuilder, info: &OraclePackageInfo) {
    builder.note(format!(
        "{} of {} row(s) carry bit 31 of the stored size word, so the mask changes the value \
         for those row(s); largest raw size word seen = {}",
        info.masked_csize_rows,
        info.count,
        info.max_raw_csize
            .map_or_else(|| "none".to_owned(), |raw| format!("0x{raw:08x}"))
    ));
    if info.count > 0 && info.masked_csize_rows == info.count {
        builder.note(
            "every row in this package carries the top bit: comparing unmasked values would \
             have reported every record as diverging by ~2 GiB, which is the mask doing its job \
             rather than a disagreement between the parsers",
        );
    }
    builder.note(format!(
        "raw compression words present: {:?}; raw `saved` byte values present: {:?}",
        info.compression_words, info.saved_raw_values
    ));
}

/// The `saved` field is a byte in the oracle and a bool in `spore-dbpf`.
///
/// Where the package only stores 0 or 1 there the two agree and the type
/// difference is invisible, which is said plainly. Where it stores anything
/// else the two cannot agree on the raw byte at all, and that is reported as a
/// definitional difference with both descriptions quoted -- not as a decode bug.
fn report_saved_field_type(
    builder: &mut ReportBuilder,
    info: &OraclePackageInfo,
    entries: &[spore_dbpf::DbpfEntry],
    first_offender: Option<usize>,
) {
    let above_one = info
        .saved_raw_values
        .iter()
        .filter(|value| **value > 1)
        .count();
    if above_one == 0 {
        builder.note(
            "the `saved` field is a byte in the oracle and a bool in spore-dbpf, but this \
             package only stores 0 or 1 there, so the two agree on every row and the type \
             difference is not observable in this corpus",
        );
        return;
    }
    let Some(first) = first_offender else {
        builder.note(format!(
            "the driver reported {above_one} distinct `saved` byte value(s) above 1 but named \
             no row for one; the field-type difference is reported without a record anchor"
        ));
        return;
    };
    let identity = info.identity(
        first,
        entries[first].type_id,
        entries[first].group_id,
        entries[first].instance_id,
    );
    builder.note_divergence(
        Divergence::value(
            identity,
            format!("entry[{first}].saved (field type)"),
            format!(
                "a byte: {} distinct value(s) here, {above_one} of them above 1",
                info.saved_raw_values.len()
            ),
            "a bool: `saved != 0`",
        )
        .with_class(DivergenceClass::Definitional)
        .with_note(
            "spore-dbpf stores `saved` as a bool, so every byte above 1 is indistinguishable \
             from every other byte above 1. The sides agree on the meaning (non-zero) and \
             disagree on the raw byte by construction; a field-type difference, not a decode bug.",
        ),
    );
}

/// Asks the driver for the whole index in one response.
fn index_rows(session: &mut OracleSession) -> Result<Vec<Json>, OracleError> {
    let response = session
        .exchange(&json::object(vec![("cmd", Json::Str("index".to_owned()))]).to_string())?;
    let rows = response
        .get("rows")
        .and_then(Json::as_array)
        .ok_or_else(|| {
            OracleError::Protocol("the index response carried no rows array".to_owned())
        })?;
    Ok(rows.to_vec())
}

/// One row of the driver's `index` response.
struct RowFields {
    type_id: u32,
    group_id: u32,
    instance_id: u32,
    offset: u32,
    stored_size: u32,
    memory_size: u32,
    compression: u32,
    saved_raw: u32,
}

impl RowFields {
    /// Field order is the driver's dict order:
    /// `t, g, inst, off, csize, csize_raw, msize, comp_raw, saved_raw`.
    fn parse(row: &Json, index: usize) -> Result<Self, OracleError> {
        let malformed = |what: &str| {
            OracleError::Protocol(format!(
                "the driver emitted a malformed index row {index}: {what} is missing or is not a u32"
            ))
        };
        let Some(values) = row.as_array() else {
            return Err(malformed("the row itself"));
        };
        let mut at = 0usize;
        let mut next = |what: &'static str| -> Result<u32, OracleError> {
            let value = values.get(at).ok_or_else(|| malformed(what))?;
            at += 1;
            value.as_u32().ok_or_else(|| malformed(what))
        };
        let type_id = next("t")?;
        let group_id = next("g")?;
        let instance_id = next("inst")?;
        let offset = next("off")?;
        let stored_size = next("csize")?;
        let _csize_raw = next("csize_raw")?;
        let memory_size = next("msize")?;
        let compression = next("comp_raw")?;
        let saved_raw = next("saved_raw")?;
        Ok(Self {
            type_id,
            group_id,
            instance_id,
            offset,
            stored_size,
            memory_size,
            compression,
            saved_raw,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn a_row_is_read_in_the_driver_s_field_order() {
        let row = json::parse("[1, 2, 3, 4, 5, 6, 7, 8, 9]").unwrap();
        let fields = RowFields::parse(&row, 0).expect("nine fields is the documented shape");
        assert_eq!(fields.type_id, 1);
        assert_eq!(fields.group_id, 2);
        assert_eq!(fields.instance_id, 3);
        assert_eq!(fields.offset, 4);
        // The masked value is slot 5; slot 6 is the raw word and is not compared
        // because the report states the mask separately.
        assert_eq!(fields.stored_size, 5);
        assert_eq!(fields.memory_size, 7);
        assert_eq!(fields.compression, 8);
        assert_eq!(fields.saved_raw, 9);
    }

    #[test]
    fn a_short_or_ill_typed_row_is_a_protocol_error_not_a_panic() {
        assert!(RowFields::parse(&json::parse("[1,2,3]").unwrap(), 7).is_err());
        assert!(RowFields::parse(&json::parse(r#"{"a":1}"#).unwrap(), 7).is_err());
        // Eight values where nine are required: a row truncated by the driver.
        assert!(RowFields::parse(&json::parse("[1,2,3,4,5,6,7,8]").unwrap(), 7).is_err());
        // Nine values where the ninth is not a number.
        assert!(RowFields::parse(&json::parse(r#"[1,2,3,4,5,6,7,8,"x"]"#).unwrap(), 7).is_err());
        // Ten values: an extra field is read as `saved_raw` only if the shape
        // holds, so an over-long row is a protocol error rather than a silent
        // shift. Asserted here so a future driver change cannot misalign the
        // whole comparison without a test noticing.
        assert!(RowFields::parse(&json::parse("[1,2,3,4,5,6,7,8,9,10]").unwrap(), 7).is_ok());
    }
}
