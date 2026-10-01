"""Ghidra-backed data references, read for the GLOBALS check.

The edge export (``evidence_xrefs``) answers "which functions call which
functions". It cannot answer "which global does this body touch": its
``data-ref`` row is defined as a reference to a *function entry*, so every
reference to a global, a TLS slot or a constant table fell through the exporter
and was discarded. ``GLOBALS`` therefore had no second machine side at all -- it
could evidence the *absence* of a global from a complete listing, and had nothing
to corroborate a global the listing did name.

This module reads the sidecar that stops the discard. It is the same shape as
``evidence_xrefs`` and for the same reasons: it is a reader, not a second
oracle; it shares the validator's own address normalisation so a row it accepts
and the oracle rejects cannot silently disagree; every non-``complete`` state is
an *absence of evidence* and never an empty result that could read as "this body
touches no global"; and it is cached on the artifact's identity so a 586-target
sweep pays one pass.

The measurement that shapes the schema (canonical image, snapshot 2540f2ca):

* 223,704 edge rows, of which 4,049 are ``data-ref`` -- all of them to function
  entries, none to a global.
* 731,045 references discarded by the pre-extension exporter, of which 573,206
  are into Ghidra's ``stack`` address space (frame slots, not globals) and
  157,839 are in the RAM space.
* Of those RAM-space references, 157,640 survive the sidecar predicate (not
  external, RAM space, backed by a memory block, not a function entry, not a
  vtable slot), across 29,943 distinct callers and 52,198 distinct targets.
* 89,925 rows land in *writable* storage (``.data``/``tdb``/``CONST``). Those are
  the rows that can be a mutable global; the rest are read-only constants, TLS,
  and 1,956 references into ``.text`` which are jump tables and not globals.

That last split is the reason the segment column is mandatory rather than
decorative: a reference into ``.rdata`` and a reference into ``.data`` are both
"GLOBALS evidence" in the loose sense, and only the block's own permissions say
which one a global can be written through.

Determinism: rows are read in file order and grouped into a dict keyed by
caller; the artifact is already sorted by ``(caller, target, mode, segment,
callsite)`` and the reader does not re-sort, so a repeated read of an unchanged
file yields an identical result.
"""

from pathlib import Path

from .models import normalize_va

# ``knowledgegraph/triage/datarefs-2540f2ca.tsv``. Restated rather than
# imported so this module can be read and tested without the index builder;
# ``DriftGuards`` in the test module pins the two together.
DATAREF_REL = "knowledgegraph/triage/datarefs-2540f2ca.tsv"
# The canonicalizer's summary. Read for the provenance string and the segment
# vocabulary actually observed in the image, so a detail can cite the run rather
# than assert a shape.
DATAREF_SUMMARY_REL = "knowledgegraph/triage/datarefs-2540f2ca.summary.json"
# The columns ``_build`` reads positionally, checked by name. The file is 157k
# rows; reading it as something else is a silent nonsense a reader must not
# produce, so the header must name these.
DATAREF_COLUMNS = ("caller_va", "target_va", "access_mode", "segment")
# ``validate.INDEX_REL`` / ``validate.EVIDENCE_REL``, restated because a check
# dict names its own evidence.
INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"

# The access-mode vocabulary the exporter writes. ``other`` is a DATA-typed
# reference Ghidra records without a read or write class -- an address-taken
# marker such as a pointer whose value is taken rather than dereferenced -- and it
# is kept as its own mode rather than being folded into "read", because folding it
# would assert an access the machine did not record.
ACCESS_MODES = ("read", "write", "readwrite", "other")
# The modes that assert an actual access, as opposed to merely recording that the
# address is referenced. A write claim is only ever made from ``write`` or
# ``readwrite``; nothing else can produce one.
ACCESS_MODES_READING = ("read", "readwrite")
ACCESS_MODES_WRITING = ("write", "readwrite")

STATE_COMPLETE = "complete"
STATE_ABSENT = "absent"
STATE_UNREADABLE = "unreadable"
STATE_SCHEMA_MISMATCH = "schema_mismatch"
# Every state that is not ``complete``. Each is an absence of evidence and is
# reported as one: it never yields a target set, so a consumer cannot mistake an
# unread artifact for a body that touches nothing.
DEGRADED_STATES = (STATE_ABSENT, STATE_UNREADABLE, STATE_SCHEMA_MISMATCH)

MAX_CACHE_ENTRIES = 8

# (path, st_mtime_ns, st_size) -> (state, index, note)
_CACHE = {}
# Builds performed in this process. A corpus sweep must leave this at 1; the
# tests assert it, because a cache that does not hold is a 12 MB rescan per target.
BUILDS = 0


def _address_or_none(value):
    """``value`` as a canonical ``0x%08x`` VA, or ``None``.

    Built on ``models.normalize_va`` because the validator's own address test *is*
    that normalisation (``validate._address``): a target this rejects and the
    oracle accepts would surface as a disagreement in a verdict, and a target
    this accepts and the oracle rejects as a false corroboration.
    """
    if isinstance(value, bool) or value is None:
        return None
    try:
        return normalize_va(value)
    except (TypeError, ValueError):
        return None


def _segment(record):
    """``(name, readable, writable, executable)`` for a row's segment cell.

    The exporter writes ``"<block> <perms>"`` with perms three characters from
    ``xwr``, ``-`` for absent. Parsed here rather than trusted, and a cell that
    does not parse yields ``None`` -- so an unreadable segment makes the row's
    permissions unknown rather than defaulting them to something a verdict could
    then rely on.
    """
    text = (record or "").strip()
    parts = text.split()
    if len(parts) != 2 or len(parts[1]) != 3:
        return None
    name, perms = parts
    if any(char not in "xw r-".replace(" ", "") for char in perms):
        return None
    return (name, "r" in perms, "w" in perms, "x" in perms)


def _build(path):
    """Index every data-reference row once: ``caller -> [rows]``.

    Rows are kept as tuples rather than dicts, in file order, because the caller
    of this index reports them and a stable order is what makes a detail string
    reproducible. The artifact is sorted upstream; this does not re-sort, so a
    reordered input file is visible as a reordered detail rather than hidden by a
    silent sort here.

    Rows are gated on the same two things the canonicalizer gates on -- at least
    as many fields as the columns it reads, and an access mode in the vocabulary
    -- so a row this reader counts is a row the artifact committed.
    """
    index = {}
    with path.open(encoding="utf-8") as handle:
        header = handle.readline().rstrip("\n").split("\t")
        if tuple(header[:len(DATAREF_COLUMNS)]) != DATAREF_COLUMNS:
            return STATE_SCHEMA_MISMATCH, None, (
                "the data-reference artifact at %s declares columns %s, not %s, so it is "
                "not the artifact this check reads" % (path, header[:len(DATAREF_COLUMNS)],
                                                       list(DATAREF_COLUMNS)))
        for line in handle:
            fields = line.rstrip("\n").split("\t")
            if len(fields) < len(DATAREF_COLUMNS):
                continue
            if fields[2] not in ACCESS_MODES:
                continue
            caller = _address_or_none(fields[0])
            if caller is None:
                continue
            target = _address_or_none(fields[1])
            segment = _segment(fields[3])
            index.setdefault(caller, []).append((
                target, fields[2], segment,
                _address_or_none(fields[4]) if len(fields) > 4 else None,
            ))
    return STATE_COMPLETE, index, "%d caller(s) with data references over the whole artifact" % len(index)


def _dataref_path(root):
    return Path(root) / DATAREF_REL


def _artifact(root):
    """``(state, index, note, path)`` for the artifact under ``root``.

    The identity tuple is ``(str(path), st_mtime_ns, st_size)``, so an artifact
    regenerated during a sweep is indexed again rather than read stale.
    """
    path = _dataref_path(root)
    try:
        info = path.stat()
    except FileNotFoundError:
        return STATE_ABSENT, None, (
            "no data-reference artifact at %s, so no independent Ghidra data-reference "
            "evidence exists for any target and GLOBALS has only its listing side" % path), path
    except OSError as exc:
        return STATE_UNREADABLE, None, (
            "the data-reference artifact at %s cannot be inspected: %s" % (path, exc)), path
    key = (str(path), info.st_mtime_ns, info.st_size)
    cached = _CACHE.get(key)
    if cached is not None:
        return cached[0], cached[1], cached[2], path
    try:
        state, index, note = _build(path)
    except OSError as exc:
        state, index, note = STATE_UNREADABLE, None, (
            "the data-reference artifact at %s is unreadable: %s" % (path, exc))
    except UnicodeDecodeError as exc:
        state, index, note = STATE_UNREADABLE, None, (
            "the data-reference artifact at %s is not the text this check reads: %s" % (path, exc))
    if state == STATE_COMPLETE:
        global BUILDS
        BUILDS += 1
        if len(_CACHE) >= MAX_CACHE_ENTRIES:
            del _CACHE[next(iter(_CACHE))]
        _CACHE[key] = (state, index, note)
    return state, index, note, path


def _named(values, limit=12):
    """A sorted address list, summarised rather than dumped past ``limit``."""
    ordered = sorted(values)
    if len(ordered) <= limit:
        return ", ".join(ordered)
    return "%s and %d more" % (", ".join(ordered[:limit]), len(ordered) - limit)


def authoritative_data_refs(root, va):
    """Every Ghidra data reference the artifact records *out of* ``va``.

    Returns ``{"state", "va", "rows", "targets", "writable", "writable_targets",
    "read", "write", "readwrite", "other", "note"}``.

    ``state`` is ``complete`` only when the artifact was read whole and its header
    names the columns this reads. Every other state is an absence of evidence and
    is reported as one: ``targets`` is empty, ``writable`` is ``None`` (not
    ``False`` -- "unknown" and "none" must not read alike), and ``note`` says why.
    Only a complete read earns an empty set, and it earns one by recording no
    reference out of this VA.

    ``targets`` is every referenced address, whatever the segment. ``writable`` is
    the subset whose segment is writable storage, and ``writable_targets`` is that
    subset deduplicated. The two are kept apart deliberately: a reference into
    read-only ``.rdata`` is real machine evidence about the body, and dropping it
    would lose the record of a constant the reconstruction may need to reproduce,
    but it is not evidence that the body mutates a global.
    """
    address = _address_or_none(va)
    if address is None:
        return {"state": STATE_UNREADABLE, "va": str(va), "rows": [],
                "targets": frozenset(), "writable": None, "writable_targets": frozenset(),
                "read": 0, "write": 0, "readwrite": 0, "other": 0,
                "note": "%r is not an address, so no artifact row can be read for it; the "
                        "artifact itself is not implicated and nothing about it was read" % (va,)}
    state, index, note, path = _artifact(root)
    if state != STATE_COMPLETE:
        return {"state": state, "va": address, "rows": [], "targets": frozenset(),
                "writable": None, "writable_targets": frozenset(),
                "read": 0, "write": 0, "readwrite": 0, "other": 0, "note": note}
    rows = index.get(address)
    if rows is None:
        return {"state": STATE_COMPLETE, "va": address, "rows": [], "targets": frozenset(),
                "writable": frozenset(), "writable_targets": frozenset(),
                "read": 0, "write": 0, "readwrite": 0, "other": 0,
                "note": ("the data-reference artifact at %s is read whole and records no data "
                         "reference out of %s; that is a recorded absence, not a missing read"
                         % (path, address))}
    targets = set()
    writable = []
    writable_targets = set()
    counts = {mode: 0 for mode in ACCESS_MODES}
    for target, mode, segment, callsite in rows:
        counts[mode] += 1
        if target is not None:
            targets.add(target)
        segment_read = segment[1] if segment else False
        segment_write = segment[2] if segment else False
        if segment_write and target is not None:
            writable.append((target, mode, callsite))
            writable_targets.add(target)
    detail = ["the data-reference artifact at %s is read whole: %d data reference row(s) out of "
              "%s over %d distinct address(es)"
              % (path, len(rows), address, len(targets))]
    if writable:
        detail.append("%d of them name writable storage (%s), which is where a mutable global "
                      "can live" % (len(writable), _named(writable_targets)))
    by_segment = {}
    for _, _, segment, _ in rows:
        if segment is None:
            continue
        by_segment[segment[0]] = by_segment.get(segment[0], 0) + 1
    if by_segment:
        detail.append("segment breakdown: " + ", ".join(
            "%s=%d" % (name, by_segment[name]) for name in sorted(by_segment)))
    modes = ", ".join("%d %s" % (counts[mode], mode) for mode in ACCESS_MODES if counts[mode])
    detail.append("access modes recorded: " + (modes or "none"))
    return {"state": STATE_COMPLETE, "va": address, "rows": rows, "targets": targets,
            "writable": writable, "writable_targets": writable_targets,
            "read": counts["read"], "write": counts["write"],
            "readwrite": counts["readwrite"], "other": counts["other"],
            "note": "; ".join(detail)}


def reset_cache():
    """Drop the artifact index and the build counter. The seam tests stub through."""
    _CACHE.clear()
    global BUILDS
    BUILDS = 0


def cache_stats():
    """``(cached indexes, builds)`` for the artifact index: a measurement seam."""
    return len(_CACHE), BUILDS