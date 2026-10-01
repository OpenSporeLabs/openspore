"""The complete xref evidence the CALLS check needs, read past the projection.

``reconstruction/knowledge/index.json`` carries, per record, a *scheduler
projection* of the Ghidra xref export: ``dependencies.edges`` is
``edge_rows[:MAX_DEPENDENCY_EDGES]`` -- thirty rows -- and
``dependencies.edges_truncated`` is set when there were more
(``reconstruction_knowledge.py:719``). ``validate._machine_callees`` reads that
thirty-row window as the machine callee set, and ``validate.py:1000`` therefore
warns on every record whose window is full, because a lower bound cannot bound a
source.

Two measured facts make that warning both permanent and, for most of the records
that carry it, untrue.

* The projection is sorted by ``(direction, other, reference_type, callsite)``
  and ``"in" < "out"``, so **every incoming edge is written before every outgoing
  one**. ``_machine_callees`` reads only ``direction == "out"`` rows. A
  high-fan-in target therefore spends the whole thirty-row window on incoming
  edges and projects no outgoing edge at all: of the 617 index records, 149 carry
  ``edges_truncated`` and 78 of those have outgoing callees the projection does
  not name -- 47 of them with the projection showing *zero* outgoing callees. So
  the flag is set far more often than the callee set is actually truncated.
* Where the callee set *is* truncated, the export that truncated it is still on
  disk: ``knowledgegraph/triage/xrefs-2540f2ca.tsv``, 223,704 rows / 27.8 MB.
  Nothing forces the verdict to be taken over a lossy view of it.

This module reads that export directly, for one VA at a time, and hands
``validate`` the complete out-edge callee set. It is a reader, not a second
oracle: it shares the CALLS check's own shape (same reference types, same
direction semantics, same "an external callee is an import name and not an
address") so that replacing the projection with it cannot change a verdict
except by giving the check the evidence the projection was withholding.

The design constraint is that ``validate`` is called ~586 times in a corpus
sweep, so a per-call rescan of 27.8 MB is not available. One module-level index,
built in a single pass and cached on the export's identity
(``(path, st_mtime_ns, st_size)``), costs -- measured on the committed
27,823,658-byte export, CPython 3.14.7:

* **cold build 0.46 s**, one pass, 49,451 caller/callee keys, 207,757 call rows;
* **warm read 0.0065 ms**, and the whole of ``decide`` 0.021 ms -- 1.8% of one
  586-target ``validate`` sweep, which is 0.72 s;
* **36.9 MB** retained (2.9 MB pickled), freed with ``reset_cache``.

A per-VA lazy index with a shared pass was the alternative and was measured rather
than argued about. It saves the 36.9 MB but not the work: to know which VAs a
caller row names is the same single pass, and then answering for a VA the first
pass did not need costs a second one. The full index was kept because a validator
process that already holds a 617-record index and a 586-pack evidence corpus has no
trouble with 37 MB, and because one pass that answers every question is a smaller
thing to reason about than a pass plus a fallback.
"""

from pathlib import Path

from .models import normalize_va

# ``reconstruction_knowledge.XREF_REL``. Restated rather than imported so this
# module can be read and tested without the index builder; ``DriftGuards`` pins
# the two values together.
XREF_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
# The ``.externals.tsv`` sidecar that ships beside the edges export. Not read.
# ``load_xrefs`` never opens it either -- it takes the external callee from the
# edges TSV's own ``callee_va`` column, which holds the raw import token
# (``EXT:KERNEL32.DLL::QueryPerformanceCounter``, measured: all 5,481 external
# rows are of that shape and none carries a parseable address), so honouring the
# sidecar would add a second place the same fact can be read from and disagree
# with the first.
XREF_EXTERNALS_REL = "knowledgegraph/triage/xrefs-2540f2ca.externals.tsv"
# The column names ``load_xrefs`` reads positionally, checked here by name. The
# builder skips the first line unconditionally; a file whose header does not name
# these three columns is not this export, and reading 27 MB of it as 223k edge
# rows is the kind of silent nonsense a reader must not produce.
XREF_COLUMNS = ("caller_va", "callee_va", "reference_type")
# ``validate.CALL_REFERENCE_TYPES``, restated for the same reason, and
# ``DriftGuards`` pins the membership.
CALL_REFERENCE_TYPES = ("direct-call", "thunk", "computed-call", "external")
# ``reconstruction_knowledge.MAX_DEPENDENCY_EDGES``, named here as the cap whose
# truncation this module exists to route around. Reported in the check detail
# when the two disagree, so a reader can see the size of the window the record
# was read through.
MAX_PROJECTED_EDGES = 30
# ``validate.INDEX_REL`` / ``validate.EVIDENCE_REL``, restated because a check
# dict names its own evidence. ``DriftGuards`` pins both the paths and the dict
# shape against ``validate``.
INDEX_REL = "reconstruction/knowledge/index.json"
EVIDENCE_REL = "reconstruction/evidence"
# How many addresses a disagreement clause names before it summarises the rest.
# The export records 104 distinct callees for 0x0102df20, and the clause is
# appended to every verdict; listing all of them would make a report unreadable
# for no gain in evidence. The count beside the list is always the true one.
MAX_NAMED_ADDRESSES = 12

STATE_COMPLETE = "complete"
STATE_ABSENT = "absent"
STATE_UNREADABLE = "unreadable"
STATE_SCHEMA_MISMATCH = "schema_mismatch"
# Every state that is not ``complete``. Each is an absence of evidence, and the
# caller must treat it as one: it never yields a callee set, and a caller that
# needs to distinguish "recorded nothing" from "read nothing" can, because
# ``complete`` is the only state that carries a set at all.
DEGRADED_STATES = (STATE_ABSENT, STATE_UNREADABLE, STATE_SCHEMA_MISMATCH)
# The cache is keyed on the export's identity and a corpus sweep uses one root, so
# this is a guard against a long-lived process walking many roots rather than a
# limit the measured workload reaches. The oldest entry is dropped.
MAX_CACHE_ENTRIES = 8

# (path, st_mtime_ns, st_size) -> (state, index, note). The identity tuple is
# what makes the cache safe against the export being regenerated under a running
# sweep: a new mtime or size is a new key, so the stale index is never read.
_CACHE = {}
# Export indexes built in this process. A corpus sweep must leave this at 1; the
# tests assert it, because a cache that does not hold is a 27.8 MB rescan per
# target and the whole design rests on this number.
BUILDS = 0


def _address_or_none(value):
    """``value`` as a canonical ``0x%08x`` VA, or ``None``.

    Built on ``models.normalize_va`` because the CALLS oracle's address test *is*
    that normalisation (``validate._address``), and the reader has to agree with
    it: a callee this rejects and the oracle accepts would show up as a
    disagreement in a verdict, and a callee this accepts and the oracle rejects
    would show up as a false clearance. ``load_xrefs``' ``maybe_va`` rejects
    exactly the same inputs -- an import token, a ``VT:``/``DATA:`` tag, an
    empty cell -- and those are the shapes the export uses for everything that is
    not an address.
    """
    if isinstance(value, bool) or value is None:
        return None
    try:
        return normalize_va(value)
    except (TypeError, ValueError):
        return None


def _build(path):
    """Index every call row in the export once: ``caller -> (callees, out, in, ext)``.

    One pass, and the value carries three counts beside the callee set, each for a
    reason the check detail needs.

    * ``out`` -- the outgoing call *row* count, which is the quantity the
      projection's thirty-row cap truncates. It, and not the size of ``callees``,
      is what says whether a set is whole: a target called 200 times from 30 sites
      has 200 rows and 30 callees, and its callee set is the whole of it.
    * ``in`` -- the incoming row count, which is what makes a *false* truncation
      legible. ``edges_truncated`` is computed over incoming and outgoing rows
      together (``reconstruction_knowledge.py:720``) and the projection is sorted
      so every incoming row precedes every outgoing one, so a high-fan-in target
      spends the whole thirty-row window on incoming edges and projects none of its
      own callees. Measured on the 617 index records: all 149 that carry the flag
      have more than thirty rows in total, but only 25 have more than thirty
      *outgoing* ones, so the flag is set far more often than a callee set is
      truncated -- and the detail has to be able to say so with a number.
    * ``ext`` -- outgoing rows whose callee is an import token rather than an
      address. Counted separately because ``out - len(callees)`` would also count
      every repeated call site, and reporting that as "external imports" would be a
      number about the wrong thing.

    Rows are gated exactly as ``load_xrefs`` gates them -- at least four
    tab-separated fields, reference type in ``CALL_REFERENCE_TYPES`` -- so the two
    readers count the same rows. A row that is not a call row contributes to
    nothing here: ``vtable-ref`` and ``data-ref`` are references, not calls, and
    the export carries 11,898 and 4,049 of them respectively.
    """
    index = {}
    with path.open(encoding="utf-8") as handle:
        header = handle.readline().rstrip("\n").split("\t")
        if tuple(header[:len(XREF_COLUMNS)]) != XREF_COLUMNS:
            return STATE_SCHEMA_MISMATCH, None, (
                "the xref export at %s declares columns %s, not %s, so it is not the "
                "export this check reads" % (path, header[:len(XREF_COLUMNS)], list(XREF_COLUMNS)))
        for line in handle:
            fields = line.rstrip("\n").split("\t")
            if len(fields) < 4 or fields[2] not in CALL_REFERENCE_TYPES:
                continue
            callee = _address_or_none(fields[1])
            caller = _address_or_none(fields[0])
            if caller is not None:
                entry = index.get(caller)
                if entry is None:
                    entry = index[caller] = [None, 0, 0, 0]
                entry[1] += 1
                if callee is not None:
                    if entry[0] is None:
                        entry[0] = set()
                    entry[0].add(callee)
                else:
                    entry[3] += 1
            if callee is not None:
                entry = index.get(callee)
                if entry is None:
                    entry = index[callee] = [None, 0, 0, 0]
                entry[2] += 1
    for key in list(index):
        entry = index[key]
        # Frozen in place rather than into a second dict: the build's two live
        # structures would otherwise coexist at peak, and the peak is the cost a
        # caller pays inside its own address space.
        index[key] = (frozenset(entry[0]) if entry[0] else frozenset(),
                      entry[1], entry[2], entry[3])
    return STATE_COMPLETE, index, "%d caller/callee key(s) over the whole export" % len(index)


def _export(root):
    """``(state, index, note, path)`` for the export under ``root``.

    The identity tuple is ``(str(path), st_mtime_ns, st_size)``. A sweep that
    validates 586 targets validates them all against one export and pays one
    build; an export regenerated mid-sweep has a different mtime and is indexed
    again rather than read stale.
    """
    path = _xref_path(root)
    try:
        info = path.stat()
    except FileNotFoundError:
        return STATE_ABSENT, None, ("no xref export at %s, so there is no authoritative "
                                    "call evidence for any target and the dependency "
                                    "projection in the index is all there is" % path), path
    except OSError as exc:
        return STATE_UNREADABLE, None, ("the xref export at %s cannot be inspected: %s" % (path, exc)), path
    key = (str(path), info.st_mtime_ns, info.st_size)
    cached = _CACHE.get(key)
    if cached is not None:
        return cached[0], cached[1], cached[2], path
    try:
        state, index, note = _build(path)
    except OSError as exc:
        state, index, note = STATE_UNREADABLE, None, "the xref export at %s is unreadable: %s" % (path, exc)
    except UnicodeDecodeError as exc:
        state, index, note = STATE_UNREADABLE, None, ("the xref export at %s is not the text this check "
                                                      "reads: %s" % (path, exc))
    if state == STATE_COMPLETE:
        global BUILDS
        BUILDS += 1
        if len(_CACHE) >= MAX_CACHE_ENTRIES:
            del _CACHE[next(iter(_CACHE))]
        _CACHE[key] = (state, index, note)
    return state, index, note, path


def _xref_path(root):
    return Path(root) / XREF_REL


def authoritative_callees(root, va):
    """The complete out-edge callee set the xref export records for ``va``.

    Returns ``{"state", "va", "callees", "edge_count", "truncated", "note"}``.

    ``state`` is ``complete`` only when the export was read whole and its header
    names the columns this reads. Every other state -- ``absent``,
    ``unreadable``, ``schema_mismatch`` -- is an absence of evidence, and is
    reported as one: ``truncated`` is then ``True`` and ``callees`` is empty, so
    an empty set can never be read as "this function calls nothing". Only a
    ``complete`` read is entitled to an empty set, and it earns one by recording
    no outgoing call edge.

    ``edge_count`` is the number of outgoing call *rows* for this VA, which is the
    count the projection's thirty-row cap would truncate -- so it, and not the
    size of ``callees``, is what says whether a record's window lost anything. A
    target called 200 times from 30 sites has 200 rows and 30 callees, and the
    callee set is the whole of it.

    A callee that is an import rather than an address contributes to
    ``edge_count`` and not to ``callees``, exactly as ``validate._machine_callees``
    treats the raw token in an ``external`` edge row; ``note`` says how many were
    dropped, because "the export recorded 5 edges and the machine callee set is
    empty" is otherwise indistinguishable from a read failure.
    """
    address = _address_or_none(va)
    if address is None:
        return {"state": STATE_UNREADABLE, "va": str(va), "callees": frozenset(),
                "edge_count": 0, "truncated": True,
                "note": "%r is not an address, so no export row can be read for it; the export "
                        "itself is not implicated and nothing about it was read" % (va,)}
    state, index, note, path = _export(root)
    if state != STATE_COMPLETE:
        return {"state": state, "va": address, "callees": frozenset(), "edge_count": 0,
                "truncated": True, "note": note}
    entry = index.get(address)
    if entry is None:
        return {"state": STATE_COMPLETE, "va": address, "callees": frozenset(), "edge_count": 0,
                "truncated": False,
                "note": ("the xref export at %s carries no outgoing call edge of any reference type for %s; "
                         "it is read whole, so that is a recorded absence and not a missing read"
                         % (path, address))}
    callees, out_rows, in_rows, external = entry
    detail = ["the xref export at %s is read whole: %d outgoing call edge row(s) over %d distinct "
              "address(es) for %s" % (path, out_rows, len(callees), address)]
    if in_rows:
        detail.append("%d incoming call edge row(s) reach it, which the record's bounded projection "
                      "counts against the same %d-row window but which are not callees"
                      % (in_rows, MAX_PROJECTED_EDGES))
    if external:
        detail.append("%d of those rows name an external import rather than an address and are not "
                      "address-comparable, as in the projection" % external)
    return {"state": STATE_COMPLETE, "va": address, "callees": callees, "edge_count": out_rows,
            "truncated": False, "note": "; ".join(detail)}


def reset_cache():
    """Drop the export index and the build counter. The seam tests stub through."""
    _CACHE.clear()
    global BUILDS
    BUILDS = 0


def cache_stats():
    """``(cached indexes, builds)`` for the export index: a measurement seam.

    ``builds`` is what says whether a corpus sweep paid for one pass or for one
    per target, which is the whole reason the index is cached.
    """
    return len(_CACHE), BUILDS


def _named(values, limit=MAX_NAMED_ADDRESSES):
    """A sorted address list, summarised rather than dumped past ``limit``."""
    ordered = sorted(values)
    if len(ordered) <= limit:
        return ", ".join(ordered)
    return "%s and %d more" % (", ".join(ordered[:limit]), len(ordered) - limit)


def _disagreement(read, projected, dependencies):
    """The clause saying where the export and the record's projection part company.

    Both sets are reported whenever they differ, and neither is preferred here: the
    projection is a prefix of the same rows, so ``export - projection`` is what a
    capped window loses, while ``projection - export`` cannot happen from truncation
    and means the index was built from a different export than the one on disk -- a
    finding about the evidence, not a detail to smooth over. The clause is appended
    to whatever verdict the arm reached, so a disagreement is visible on a PASS as
    well as on a FAIL.
    """
    added = read["callees"] - projected
    removed = projected - read["callees"]
    if not added and not removed:
        return ""
    window = len(dependencies.get("edges") or ())
    parts = ["the record's dependency edge list is a scheduler projection of this export, not the "
             "export itself: it holds %d row(s) and %d address-named callee(s), against the %d "
             "outgoing call edge row(s) and %d distinct callee(s) the export records"
             % (window, len(projected), read["edge_count"], len(read["callees"]))]
    if added:
        parts.append("%d callee(s) the export records are absent from it, and the %d-row window "
                     "capped at MAX_DEPENDENCY_EDGES=%d is why: %s"
                     % (len(added), window, MAX_PROJECTED_EDGES, _named(added)))
    if removed:
        parts.append("%d callee(s) the projection names that this export does not record, which "
                     "truncation cannot produce and which means the index and the export on disk "
                     "disagree: %s" % (len(removed), _named(removed)))
    return "; " + "; ".join(parts)


def _truncation_note(read, dependencies):
    """Why ``edges_truncated`` was set, when the export shows it was irrelevant.

    The flag is computed over incoming *and* outgoing rows, and the projection is
    ordered so the incoming ones come first. A record whose window is full of
    incoming edges carries the flag while its outgoing callee set is complete, so
    the flag alone is not evidence that a callee is missing -- and the detail says
    so with the export's own outgoing count rather than dropping the claim.
    """
    if not (dependencies.get("edges_truncated") or dependencies.get("callees_truncated")):
        return ""
    return ("; the record's edges_truncated flag is set, and it is computed over this record's "
            "incoming and outgoing call rows together, so incoming edges alone can set it; the export "
            "records %d outgoing call edge row(s) for this target, which is the count that bounds a "
            "callee set" % read["edge_count"])


def _check(status, detail, coverage="partial", evidence=None):
    """The shape ``validate._check`` returns.

    Restated rather than imported so this module is readable and testable on its
    own; ``DriftGuards`` asserts the two agree key for key, so a change to
    the validator's shape is a failing test here and not a silently malformed
    check dict.
    """
    return {"status": status, "detail": detail, "coverage": coverage, "evidence": evidence or []}


def _oracle():
    """``validate``'s own CALLS helpers, imported rather than re-derived.

    The source-side callee scan, the listing's direct-transfer scan, the
    intra-procedural jump exclusion and the projection's callee scan are the
    *definition* of what the CALLS check compares. Re-deriving any of them here
    would be a second, drifting copy of the rule this module exists to feed, and
    the one thing it must not do is change a verdict by reading the same evidence
    differently. The import is inside the function because ``validate`` imports
    this module: at call time ``validate`` is fully initialised, so the direction
    of the edge is unambiguous.
    """
    from . import validate
    return validate


def decide(*, record, categories, abi_outer, abi_inner, listing,
           scoped_text, target_span, source_path, dependencies, root):
    """The CALLS verdict taken over the complete xref export, or ``None`` to defer.

    ``None`` means "the authoritative evidence is not available, and every arm of
    ``validate``'s own CALLS block applies unchanged" -- including today's
    truncated-projection warning. It is returned for every state that is not
    ``complete``, and for one more case, described below. So the wire-in is
    behaviour-preserving by construction: with the export missing, unreadable, of
    another shape, or the record unsearched, this function is a no-op.

    The precedence, once the export has been read whole:

    0. The record must also carry an ``edges`` *list*. That list is the index's
       own record that the record was searched at all, and the reader cannot
       supply it: a VA the export has no row for is indistinguishable from a VA
       the export never covered. Reading its empty set as "calls nothing" is
       exactly how an absence of evidence becomes a clearance, so a record
       without the list defers and ``validate``'s own ``xref_present`` gate keeps
       governing it.
    1. No source span, no target span: ``NOT_AVAILABLE``, verbatim. A source that
       cannot be located is not judged at all, and that outranks every finding
       below.
    2. An empty authoritative callee set with no listing: ``NOT_AVAILABLE``,
       verbatim. Neither oracle exists to agree or disagree with.
    3. A source-named callee the export does not record: ``FAIL``. This speaks
       first, and it speaks the same way it did when the projection was the
       oracle: a named callee with no edge is a contradiction, whatever the
       listing holds, and widening the evidence does not soften it -- 0x00588570
       moves from ``WARN`` to ``FAIL`` for exactly this reason.
    4. With a listing, the machine-vs-machine rule, in three arms: both oracles
       empty is a ``PASS`` as an evidenced absence; the two sets disagree is a
       ``FAIL`` with both directions named; the two name the same set is a
       ``PASS``. A tail call the export does not record and a listing that is a
       slice are both statements about the evidence, and inconsistent evidence is
       not a pass.
    5. Without a listing, the three source-vs-xref arms, unchanged: no
       address-named callee is a ``WARN``, and either matching or being a subset
       of the machine callee set is a ``PASS``.

    So ``machines_agree`` -- the flag ``validate`` derives -- is true exactly when
    a listing exists, because a complete export cannot be a lower bound. That
    single fact is what replaces the truncation warning, and it is what lets the
    machine-vs-machine arms become reachable at all.

    ``abi_outer`` and ``abi_inner`` are accepted and not read: no ABI record
    adjudicates a call set, and the parameters are here so this call can be made
    from the same block the other dimension checks are made from. ``categories`` is
    not read either, for the same reason -- ``listing`` is the only part of the
    pack CALLS consumes, and it is passed already resolved.
    """
    read = authoritative_callees(root, record.get("va"))
    if read["state"] != STATE_COMPLETE:
        return None
    if not isinstance(dependencies.get("edges"), list):
        return None
    if not source_path or not target_span:
        return _check("NOT_AVAILABLE", "target source span is not deterministically available", "none")

    oracle = _oracle()
    machine_calls = read["callees"]
    source_calls = oracle._callee_addresses(scoped_text, record)
    # ``listing`` is ``None`` for a pack with no usable disassembly, and that is an
    # absence of the second oracle rather than an empty second oracle -- so the
    # listing-side set is computed from nothing and the arms that need a listing are
    # the ones that check for it.
    listing_addresses, listing_texts = listing if listing is not None else (None, None)
    listing_transfers = oracle._direct_transfer_targets(listing_texts)
    # A jump back into the listing's own span is intra-procedural control flow and
    # not a transfer out of the body, so it is excluded from the set the export is
    # compared against -- and reported wherever the set is reported, so a filtered
    # jump stays distinguishable from a real disagreement.
    intra_jumps = oracle._intra_procedural_jump_targets(listing_addresses, listing_texts)
    filtered_jumps = intra_jumps or set()
    listing_calls = listing_transfers - filtered_jumps
    jump_note = ""
    if filtered_jumps:
        low, high = oracle._span_bounds(listing_addresses)
        jump_note = ("; %d intra-procedural jump(s) target inside the recovered body span 0x%08x..0x%08x "
                     "are excluded, because a jump that lands back in the body is control flow and not a "
                     "transfer out of it: %s"
                     % (len(filtered_jumps), low, high, ", ".join(sorted(filtered_jumps))))
    suffix = "; " + read["note"] \
        + _disagreement(read, oracle._machine_callees(dependencies), dependencies) \
        + _truncation_note(read, dependencies)

    # -- arm 2: neither oracle exists ---------------------------------------
    if not machine_calls and listing is None:
        return _check("NOT_AVAILABLE",
                      "the xref export records no call edge out of this target and no listing is "
                      "available; neither call oracle exists, so there is nothing to agree or disagree "
                      "with" + suffix, "none", [INDEX_REL])
    # -- arm 3: the source-vs-xref refutation, which speaks first ------------
    if source_calls - machine_calls:
        missing = sorted(source_calls - machine_calls)
        return _check("FAIL", "the source-vs-xref rule: %d address-named source call(s) have no call "
                              "edge in the xref export: %s" % (len(missing), ", ".join(missing)) + suffix,
                      "partial", [INDEX_REL])
    # -- arms 7-9: no listing, so only the source and the export can be compared -
    if listing is None:
        # -- arm 7: nothing address-named in the source, so nothing compared --
        if not source_calls:
            return _check("WARN", "the source span names no address-suffixed callee, so its %d "
                                  "call(s) cannot be compared with the machine" % len(machine_calls)
                          + suffix, "partial", [INDEX_REL])
        # -- arms 8-9: every named claim is a machine callee ------------------
        if source_calls == machine_calls:
            return _check("PASS", "the source-vs-xref rule: all %d machine callee(s) and all %d "
                                  "address-named source call(s) agree with the xref export; no listing "
                                  "is available for the second machine side"
                          % (len(machine_calls), len(source_calls)) + suffix, "partial", [INDEX_REL])
        return _check("PASS", "the source-vs-xref rule: every one of the %d address-named source "
                              "call(s) is a machine callee; %d further callee(s) are not "
                              "address-named in the source" % (len(source_calls), len(machine_calls - source_calls))
                      + suffix, "partial", [INDEX_REL])
    # -- arms 4-6: the machine-vs-machine rule, which needs both oracles --------
    # -- arm 4: both oracles searched and both empty -------------------------
    if not machine_calls and not listing_calls:
        return _check("PASS", "the machine-vs-machine rule: the xref export and the complete "
                              "%d-instruction listing each record no outgoing transfer, which is "
                              "evidence that this target makes no call; the source span names none "
                              "either%s%s" % (len(listing_texts), jump_note, suffix),
                      "complete", [INDEX_REL, EVIDENCE_REL])
    # -- arm 5: two bounded machine sources that disagree ---------------------
    if machine_calls != listing_calls:
        extra = sorted(listing_calls - machine_calls)
        absent = sorted(machine_calls - listing_calls)
        detail = ("the machine-vs-machine rule: the xref export records %d callee(s) and the complete "
                  "%d-instruction listing %d direct transfer(s), and the two sets disagree%s"
                  % (len(machine_calls), len(listing_texts), len(listing_calls), jump_note))
        if extra:
            detail += "; %d transfer(s) the body makes are not in the export: %s" % (len(extra), ", ".join(extra))
        if absent:
            detail += "; %d export callee(s) the body does not show: %s" % (len(absent), _named(absent))
        return _check("FAIL", detail + suffix, "partial", [INDEX_REL, EVIDENCE_REL])
    # -- arm 6: the two name the same set ------------------------------------
    return _check("PASS", "the machine-vs-machine rule: the xref export and the complete "
                          "%d-instruction listing name the same %d direct transfer target(s)%s%s; the "
                          "source span names %d of them and no others"
                  % (len(listing_texts), len(machine_calls),
                     (", including a target reached only by a jump"
                      if machine_calls & oracle._jump_transfer_targets(listing_texts) else ""),
                     jump_note + suffix, len(source_calls)),
                  "complete", [INDEX_REL, EVIDENCE_REL])
