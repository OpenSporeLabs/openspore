//! The fact-group envelope: the one place where `state: available|unavailable`
//! becomes a [`Fact`].
//!
//! # The rules this module enforces
//!
//! The envelope is the format's answer to a question a bare optional field
//! cannot answer: *did OpenSpore look and find nothing, or did it never look?*
//! Three pairs of conditions make the distinction unforgeable:
//!
//! | `state` | must carry | must **not** carry |
//! |---|---|---|
//! | `available` | a `value` and a non-empty `provenance` | a `reason` |
//! | `unavailable` | a `reason`; `evidence_level == "UNKNOWN"`, `evidence_state == "MISSING"` | a `value`, a `provenance` list |
//!
//! Every violation is refused rather than absorbed. A `value` on an unavailable
//! group would be a weaker statement than `state: "unavailable"`; an `available`
//! group with no provenance would be exactly the unsourced claim
//! [`spore_core::Fact`] exists to prevent.
//!
//! # Grades
//!
//! An `evidence_level` outside the shared 7-rung scale is **refused**, not
//! degraded. That is a deliberate fail-closed choice: an available fact graded
//! `UNKNOWN` would read as "OpenSpore claims nothing here", which is not what
//! the file says. `crate::claims` records the one field where this crate *does*
//! degrade, and why.

use crate::address::{AddressError, Va};
use crate::json::{JsonError, JsonErrorKind, Obj, Val};
use crate::passport::SNAPSHOT_REFERENCE;
use spore_core::{EvidenceLevel, EvidenceState, Fact, Provenance, ProvenanceMode, SourceClass};

const STATE_AVAILABLE: &str = "available";
const STATE_UNAVAILABLE: &str = "unavailable";

/// Every rung of the shared scale, in order.
const LEVELS: [EvidenceLevel; 7] = [
    EvidenceLevel::Unknown,
    EvidenceLevel::Approximation,
    EvidenceLevel::Inferred,
    EvidenceLevel::Supported,
    EvidenceLevel::Observed,
    EvidenceLevel::Confirmed,
    EvidenceLevel::Verified,
];

const EVIDENCE_STATES: [EvidenceState; 4] = [
    EvidenceState::Live,
    EvidenceState::Derived,
    EvidenceState::Persisted,
    EvidenceState::Missing,
];

/// Reads one fact group.
///
/// `extract` turns the group's `value` into the typed payload; it is only ever
/// called when the envelope says `available`.
pub(crate) fn fact_group<'a, T, F>(envelope: &Obj<'a>, extract: F) -> Result<Fact<T>, JsonError>
where
    F: FnOnce(&Val<'a>) -> Result<T, JsonError>,
{
    let state = envelope.req_str("state")?;
    let level_text = envelope.req_str("evidence_level")?;
    let evidence_state = envelope.req_str("evidence_state")?;
    let provenance = envelope.opt_str_array("provenance")?;
    let reason = envelope.opt_str("reason")?;
    let value = envelope.opt("value");

    match state {
        STATE_AVAILABLE => {
            let Some(value) = value else {
                return Err(schema(
                    envelope,
                    "value",
                    "state is \"available\" but the value is omitted; an available group must carry \
                     the fact it claims to have, or it is claiming nothing at all",
                ));
            };
            if provenance.is_empty() {
                return Err(schema(
                    envelope,
                    "provenance",
                    "state is \"available\" but no provenance is listed; an available fact with no \
                     source is the unsourced claim this reader exists to refuse",
                ));
            }
            if let Some(reason) = reason {
                return Err(schema(
                    envelope,
                    "reason",
                    format!(
                        "state is \"available\" but an absence reason {reason:?} is present; the two \
                         states are not combinable"
                    ),
                ));
            }
            let payload = extract(value)?;
            Ok(Fact::new(
                parse_level(envelope, level_text)?,
                parse_evidence_state(envelope, evidence_state)?,
                provenance.into_iter().map(provenance_from_ref).collect(),
                payload,
            ))
        }
        STATE_UNAVAILABLE => {
            if value.is_some() {
                return Err(schema(
                    envelope,
                    "value",
                    "state is \"unavailable\" but a value is present; `null` or an empty skeleton \
                     would both be weaker statements than the state itself",
                ));
            }
            let Some(reason) = reason.filter(|r| !r.is_empty()) else {
                return Err(schema(
                    envelope,
                    "reason",
                    "state is \"unavailable\" but no reason is given; an unexplained absence is \
                     indistinguishable from a bug in the exporter",
                ));
            };
            if !provenance.is_empty() {
                return Err(schema(
                    envelope,
                    "provenance",
                    "state is \"unavailable\" but a provenance list is present; the provenance of a \
                     non-finding is fully determined by its reason code, and repeating repository \
                     paths on 59k records would say nothing that is not already implied",
                ));
            }
            if level_text != EvidenceLevel::Unknown.as_str() {
                return Err(schema(
                    envelope,
                    "evidence_level",
                    format!(
                        "state is \"unavailable\" but evidence_level is {level_text:?}; an explicit \
                         absence is graded UNKNOWN by contract"
                    ),
                ));
            }
            if evidence_state != EvidenceState::Missing.as_str() {
                return Err(schema(
                    envelope,
                    "evidence_state",
                    format!(
                        "state is \"unavailable\" but evidence_state is {evidence_state:?}; an \
                         explicit absence is MISSING by contract"
                    ),
                ));
            }
            Ok(Fact::unavailable(reason))
        }
        other => Err(schema(
            envelope,
            "state",
            format!(
                "state is {other:?}; the vocabulary is closed at \"available\" and \"unavailable\""
            ),
        )),
    }
}

/// Parses an envelope grade, refusing anything off the shared scale.
fn parse_level(envelope: &Obj<'_>, text: &str) -> Result<EvidenceLevel, JsonError> {
    LEVELS
        .iter()
        .copied()
        .find(|level| level.as_str() == text)
        .ok_or_else(|| {
            schema(
                envelope,
                "evidence_level",
                format!(
                    "{text:?} is not a rung of the shared scale ({}); a grade this build does not \
                     know must not be read as a lower one",
                    LEVELS.map(EvidenceLevel::as_str).join(" | ")
                ),
            )
        })
}

fn parse_evidence_state(envelope: &Obj<'_>, text: &str) -> Result<EvidenceState, JsonError> {
    EVIDENCE_STATES
        .iter()
        .copied()
        .find(|state| state.as_str() == text)
        .ok_or_else(|| {
            schema(
                envelope,
                "evidence_state",
                format!(
                    "{text:?} is not one of {}",
                    EVIDENCE_STATES.map(EvidenceState::as_str).join(" | ")
                ),
            )
        })
}

/// Turns the envelope's free-text provenance string into a typed entry.
///
/// The envelope's `provenance` is a list of *strings*, not of
/// `{mode, ref, source_class}` triples, so the source class has to be recovered
/// from the text. The single rule is the repository's own pairing of "live" with
/// Ghidra: a reference naming the Ghidra bridge is a live Ghidra observation;
/// everything else is a repo-relative committed path. The reference is carried
/// verbatim, so the only derived part is the class, and it is visible.
pub(crate) fn provenance_from_ref(text: &str) -> Provenance {
    if text.trim_start().starts_with("Ghidra") {
        Provenance::new(ProvenanceMode::Live, text, SourceClass::Ghidra)
    } else {
        Provenance::committed(text)
    }
}

/// A [`Provenance`] pointing at this crate's own input, naming the field read.
///
/// Used for the passport's plain nullable fields (`names.sdk_name`,
/// `classification.subsystem`), which the format does not wrap in an envelope.
/// The reference names the file and the field, because that is where *this*
/// crate read the value; where the snapshot states an upstream source it is
/// appended rather than replaced.
pub(crate) fn snapshot_provenance(field: &str, upstream: Option<&str>) -> Provenance {
    let reference = match upstream {
        Some(source) => format!("{SNAPSHOT_REFERENCE}#{field} (source: {source})"),
        None => format!("{SNAPSHOT_REFERENCE}#{field}"),
    };
    Provenance::committed(reference)
}

/// Grades a plain nullable field as an available fact, or reports the absence.
pub(crate) fn graded_scalar<'a>(
    value: Option<&'a str>,
    level: EvidenceLevel,
    field: &str,
    upstream: Option<&str>,
    absent_reason: &'static str,
) -> Fact<&'a str> {
    match value {
        Some(value) => Fact::new(
            level,
            EvidenceState::Persisted,
            vec![snapshot_provenance(field, upstream)],
            value,
        ),
        None => Fact::unavailable(absent_reason),
    }
}

/// A refusal about the shape of a value, anchored at a field path.
pub(crate) fn schema(envelope: &Obj<'_>, key: &str, message: impl Into<String>) -> JsonError {
    JsonError {
        kind: JsonErrorKind::Schema,
        path: envelope.child(key),
        message: message.into(),
    }
}

/// Reads a canonical VA list, refusing any spelling that is not `0x%08x`.
///
/// A bad spelling is reported as **corruption**, not as a schema problem: that is
/// how both Go loaders classify it (exit 5), and it is the honest reading — the
/// bytes are fine, the address in them is written in a spelling this build will
/// not accept.
pub(crate) fn va_list(obj: &Obj<'_>, key: &str) -> Result<Vec<u32>, JsonError> {
    let path = obj.child(key);
    let mut out = Vec::new();
    for (index, text) in obj.opt_str_array(key)?.into_iter().enumerate() {
        match Va::parse_canonical(text) {
            Ok(va) => out.push(va.as_u32()),
            Err(AddressError::NotCanonical { reason, .. }) => {
                return Err(JsonError {
                    kind: JsonErrorKind::Syntax,
                    path: format!("{path}[{index}]"),
                    message: format!(
                    "{text:?} is not the canonical \"0x%08x\" spelling ({reason}); refusing it is \
                         what stops one address becoming two entries"
                ),
                })
            }
            Err(other) => {
                return Err(JsonError {
                    kind: JsonErrorKind::Syntax,
                    path: format!("{path}[{index}]"),
                    message: other.to_string(),
                })
            }
        }
    }
    Ok(out)
}

/// Reads one canonical VA field.
pub(crate) fn va_field(obj: &Obj<'_>, key: &str) -> Result<u32, JsonError> {
    let path = obj.child(key);
    let text = obj.req_str(key)?;
    match Va::parse_canonical(text) {
        Ok(va) => Ok(va.as_u32()),
        Err(AddressError::NotCanonical { reason, .. }) => Err(JsonError {
            kind: JsonErrorKind::Syntax,
            path,
            message: format!(
                "{text:?} is not the canonical \"0x%08x\" spelling ({reason}); refusing it is what \
                 stops one address becoming two entries"
            ),
        }),
        Err(other) => Err(JsonError {
            kind: JsonErrorKind::Syntax,
            path,
            message: other.to_string(),
        }),
    }
}

/// Reads a non-negative integer into a `u32`.
pub(crate) fn u32_field(obj: &Obj<'_>, key: &str) -> Result<u32, JsonError> {
    let path = obj.child(key);
    let value = obj.req_int(key)?;
    u32::try_from(value).map_err(|_| JsonError {
        kind: JsonErrorKind::Syntax,
        path,
        message: format!("{value} does not fit in 32 bits"),
    })
}

/// Reads an optional non-negative integer into a `u32`.
pub(crate) fn opt_u32_field(obj: &Obj<'_>, key: &str) -> Result<Option<u32>, JsonError> {
    let path = obj.child(key);
    match obj.opt_int(key)? {
        None => Ok(None),
        Some(value) => u32::try_from(value).map(Some).map_err(|_| JsonError {
            kind: JsonErrorKind::Syntax,
            path,
            message: format!("{value} does not fit in 32 bits"),
        }),
    }
}
