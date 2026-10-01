"""Claim-aware reconstruction orchestrator.

Separation of concerns, deliberately preserved:

===========================  =================================================
``openspore frontier/swarm`` planning, scoring, evidence, validation
this module                 worker lifecycle (claim -> brief -> run -> record)
``queue_op``/``investigations``  ownership and leases
``reconstruction_knowledge``/``spore.db``  knowledge source of truth
===========================  =================================================

There is no scheduler database, no second claim system, and no second manifest
here. The plan is derived from the frontier on every call and thrown away; the
only durable state is the canonical queue row.

Per target, in order:

1. ``plan`` groups the swarm output into dependency waves (see ``schedule``).
2. ``claim`` takes an atomic lease, inserting the queue row first when the
   frontier target has none.
3. ``brief`` reuses ``evidence`` + ``context`` + the frontier row to build the
   worker package. Nothing is re-derived.
4. ``launch`` runs the worker. A checkpoint write doubles as the lease
   heartbeat, so a long job does not go stale under itself.
5. ``ingest`` parses the reply with a strict contract. A malformed reply is
   counted and released, never guessed at. A launch that never produced a
   process at all is a *launch* failure, not a malformed reply, and is never
   filed as one. A transport that has already delivered a reply for this target
   and has none left is neither: it is ``retry_pending``, because the answer was
   received and judged and the next attempt needs another child session.
6. ``validate`` runs the existing validator against the candidate. It returns
   two independent dimensions: a static verdict on the reconstruction, and a
   runtime verdict for the original process.
7. ``reconcile`` decides the terminal disposition. Only a static validator PASS
   on an IMPLEMENTED/PARTIAL/STRUCTURAL_ONLY outcome may complete a target; WARN
   and FAIL route to review and to a bounded retry respectively. Completion means
   the static reconstruction was accepted against the binary. It never means the
   original process was observed, so every completion carries its runtime gate.
8. ``release``/``close`` end the lease. Evidence is always written *before* the
   lease ends, so a crash between the two leaves a recoverable row whose
   checkpoint explains what happened. An exception after a successful ``claim``
   is handled like a crash between the two: the checkpoint records the failure
   and the lease is released, so no row is ever left ``active`` behind an
   orchestrator that has already recorded an error.
"""

import json
import os
import shlex
import sqlite3
import subprocess
import threading
import time
from pathlib import Path

from . import queue as q
from . import schedule as sched
from . import worker_contract as wc
from .context import build as build_context
from .evidence import collect
from .frontier import _index, frontier
from .models import (ROOT, ToolError, canonical_json, normalize_va,
                     relative, sha256_json)
from .recover import recover
from . import swarm as swarm_mod
# The validator's evidence-side resolvers are imported as well as ``validate``
# itself, because ``session_plan`` reports evidence *availability* and the only
# honest way to report it is through the same functions the checks are decided
# by. Re-reading them here would create a second, drifting definition of "a
# verified pack" and of "a complete listing". ``collect_inputs`` uses the same
# resolver for the same reason: whether a pack on disk may be trusted is one
# question with one answer, and the orchestrator and the validator must not hold
# two opinions about it.
from .validate import (EVIDENCE_REL, EVIDENCE_SOURCE_PERSISTED,
                       EVIDENCE_SOURCE_RECOLLECTED, PERSISTED_ABSENT,
                       PERSISTED_VERIFIED, _evidence_destination, _listing,
                       _persisted_pack, _read_source, _source, _target_span,
                       validate)

# The pack-level state ``evidence.collect`` stamps when a live request actually
# produced a live observation. It is read, never re-derived, for the same reason
# ``_persisted_pack`` is reused above: "was this collection live?" is a question
# the collector has already answered about its own output, and answering it a
# second time here would be a second opinion that can disagree.
EVIDENCE_STATE_LIVE = "LIVE"
# The third pack source, for the one collection no existing name covers: a live
# read this process actually made. The other two are the validator's own words,
# reused so the same pack is never called two different things in two reports.
EVIDENCE_SOURCE_LIVE = "collected_live"

PLAN_SCHEMA = "openspore-orchestration-plan-1"
RUN_SCHEMA = "openspore-orchestration-run-1"
SESSION_PLAN_SCHEMA = "openspore-orchestration-session-plan-1"
SESSION_TASK_SCHEMA = "openspore-orchestration-session-task-1"

# Which reply channel a worker ran in, reported by every launch event and by the
# run summary. The distinction is load-bearing and not cosmetic: ``opencode
# run --format default`` concatenates every assistant text block into stdout, so
# a worker that narrates before it calls a tool answers with a blob that is not
# a JSON document. A run that cannot say which channel it used cannot explain a
# ``malformed_worker_output``.
CHANNEL_JSONL = "opencode-jsonl"
CHANNEL_ARGV = "argv-passthrough"
CHANNEL_CUSTOM = "custom"
# The primary transport. A reconstruction worker is a native child session of the
# orchestrating agent session, so the orchestrator spawns it and hands its FINAL
# message back; nothing is scraped from stdout and no log file is read. It is
# reported the same way the subprocess channels are -- on the ``launch`` event and
# in ``summary.worker_channel`` -- because a run that cannot say which transport
# produced its answers cannot explain a ``malformed_worker_output``.
CHANNEL_NATIVE = "native-session"
# The reply file name for one target's final message: ``<va8>.txt``, the bare
# 8-hex queue spelling of the VA.
REPLY_SUFFIX = ".txt"

# The transport contract, stated once and shipped verbatim in ``session_task``.
# It is a statement about *where the answer goes*, not about what the answer may
# contain: ``ingest``/``parse_result`` still decides, with the same 15 refusals
# and no per-field leniency, whether the bytes are a result.
REPLY_FORMAT = {
    "channel": CHANNEL_NATIVE,
    "transport": "child_session",
    "authoritative": "the child session's FINAL message, verbatim",
    "instruction": (
        "End your FINAL message with the result object inside a single fenced "
        "```json block, and put nothing after that block. The closing ``` is the "
        "last thing in the message."
    ),
    "parser_reads": (
        "the final text block when the reply carries several, otherwise the "
        "whole reply"
    ),
    "fence": "```json\n{...one openspore-worker-result-1 object...}\n```",
    "exactly_once": (
        "emit the result object exactly once; two result objects are refused as "
        "ambiguous, never merged and never picked between"
    ),
    "no_result": (
        "a reply with no result object is discarded and retried, so an "
        "unfinished investigation is worth nothing"
    ),
    "reply_file": "write your FINAL message verbatim to <replies>/<va8>.txt",
    "note": (
        "this adapter transports bytes; it does not parse them. The child "
        "session is not more trusted than a subprocess worker."
    ),
}

# Bounds. Every loop in this module is bounded so a pathological target can
# never become an unbounded agent loop.
MAX_ITERATIONS = 64
MAX_ATTEMPTS = 3
MAX_VALIDATION_RETRIES = 2
MAX_TOTAL_ATTEMPTS = 12
MAX_MALFORMED = 2
HEARTBEAT_SECONDS = 600
# The longest legitimate single stage (implement, format, compile, model test)
# is well under this; 1.5x headroom means a slow but live worker is not stolen.
LEASE_TTL = 1800


class OrchestrationBoundExceeded(ToolError):
    """Raised when a bound trips, so a regression fails loudly instead of hanging."""

    def __init__(self, message, details=None):
        super().__init__("orchestration_bound_exceeded", message, 1, details)


# --------------------------------------------------------------------------- #
# planning
# --------------------------------------------------------------------------- #
def projection_staleness(root=ROOT):
    # type: (object) -> dict
    """Report whether the generated projection is behind its inputs.

    Read-only, and deliberately does NOT regenerate anything. Two reasons.
    First, ``input_hashes`` in the projection only covers four files (the
    manifest, the triage queue, the xref table and the semantic ledger) while
    ``build_index`` also reads every ``reconstruction/metadata/**`` record and
    every ``reconstruction/integrated/**/handoff.json``, so a hash comparison is
    necessary but not sufficient. Second, another agent may be mid-write, in
    which case regenerating would publish a torn view of their work.

    The orchestrator therefore reports staleness and leaves the decision to a
    human. Regeneration is one command: ``openspore integrate apply``.
    """
    try:
        from .integrate import check as integrate_check

        report = integrate_check(root)
    except ToolError as exc:
        return {"status": "UNKNOWN", "reason": exc.message}
    newest_input = None
    try:
        import glob

        candidates = (list(glob.glob(str(Path(root) / "reconstruction/metadata/*/*.json")))
                      + list(glob.glob(str(Path(root) / "reconstruction/integrated/*/handoff.json")))
                      + [str(Path(root) / path) for path in
                         ("knowledgegraph/research/source-reconstruction-manifest.json",
                          "knowledgegraph/triage/queue-f0e310e0-v6.json",
                          "knowledgegraph/triage/xrefs-2540f2ca.tsv",
                          "knowledgegraph/research/semantic-decomp.json")])
        newest_input = max((os.path.getmtime(path) for path in candidates
                            if os.path.exists(path)), default=None)
    except OSError:  # pragma: no cover - defensive
        newest_input = None
    generated = []
    for name in ("reconstruction/knowledge/index.json",
                 "reconstruction/knowledge/bootstrap.json"):
        path = Path(root) / name
        if path.exists():
            generated.append(int(os.path.getmtime(path)))
    behind = bool(newest_input and generated and max(generated) < int(newest_input))
    return {
        "status": report.get("status"),
        "index_match": report.get("index_match"),
        "bootstrap_match": report.get("bootstrap_match"),
        "source_of_truth": report.get("source_of_truth"),
        "generated_behind_inputs": behind,
        "regeneration_command": "python3 tools/openspore.py integrate apply",
        "note": ("reported, never regenerated: a concurrent agent may own the "
                 "generated projection. input_hashes covers only four files, so "
                 "this comparison is the complete staleness check."),
        "counts": _projection_counts(report),
    }


def _projection_counts(report):
    # type: (dict) -> dict
    detail = report.get("counts") or {}
    return {key: detail[key] for key in
            ("manifest_functions", "indexed_records", "metadata_records",
             "reconstructed_records")
            if key in detail}


def _read_only_db():
    # type: () -> object
    from tools.mcp import config

    path = config.db_path()
    if not os.path.exists(path):
        return None
    try:
        return sqlite3.connect("file:%s?mode=ro" % path, uri=True, timeout=5.0)
    except sqlite3.Error:  # pragma: no cover - defensive
        return None


def plan(root=ROOT, limit=20, wave_limit=None, include_deferred=True):
    # type: (...) -> dict
    """Produce the dispatch plan. Read-only: no claim is taken, no row is written.

    Deterministic by construction -- same frontier and same queue state give
    byte-identical output, which is what makes the plan comparable across runs.

    The view is deliberately wider than ``swarm``: targets that are currently
    ``deferred`` because they call an un-reconstructed callee are scheduled too,
    just not dispatched in the first wave. They are what makes dependency
    ordering observable -- a wave boundary that exists only in the plan would
    be untestable, and the ordering itself is what lets a later wave become
    eligible once its prerequisite lands.
    """
    page_limit = max(1000, min(int(limit) * 20, 10000)) if limit else 1000
    survey = frontier(root=root,
                      args=type("Args", (), {"limit": page_limit, "offset": 0})())
    binary_sha256 = survey.get("binary_sha256")
    if survey.get("status") == "blocked":
        return {
            "$schema": PLAN_SCHEMA,
            "status": "blocked",
            "warning": survey.get("warning", "frontier survey is blocked"),
            "binary_sha256": binary_sha256,
            "waves": [],
            "targets": [],
            "summary": {},
        }
    try:
        index = _index(root)
    except (OSError, ValueError) as exc:
        raise ToolError("index_unavailable",
                        "reconstruction projection cannot be built: %s" % exc, 4)

    dispatchable = set()
    for target in swarm_mod.eligible(survey):
        dispatchable.add(target["va"])
    considered = []
    for target in survey.get("targets", []):
        if target.get("disposition") not in ("eligible", "deferred"):
            continue
        if not include_deferred and target["va"] not in dispatchable:
            continue
        if target["va"] not in dispatchable and \
                (target.get("claim") or {}).get("state") in (
                    "claimed", "active_unowned", "stale_binary",
                    "coordination_missing", "completed", "blocked"):
            continue
        considered.append(swarm_mod.decorate(target, binary_sha256))
    # The eligible set is what the run dispatches; keep it bounded by `limit`
    # so a run is a batch, while deferred targets are kept whole because they
    # are the continuation of the batch, not part of it. A falsy ``limit`` is no
    # cap at all: a caller that names its targets explicitly must not have the
    # batch silently truncated to whatever else outranks it, and the only way to
    # guarantee that is to plan the whole eligible set and filter afterwards.
    capped = [item for item in considered if item["va"] in dispatchable]
    rest = [item for item in considered if item["va"] not in dispatchable]
    capped = sorted(capped, key=lambda item: (-item["priority"], item["va"]))
    rest = sorted(rest, key=lambda item: (-item["priority"], item["va"]))
    targets = (capped + rest) if not limit else capped[:max(0, int(limit))] + rest

    connection = _read_only_db()
    try:
        partition = sched.scc_partition(root=root,
                                        vas=[item["va"] for item in targets],
                                        db=connection)
    finally:
        if connection is not None:
            connection.close()
    classified = sched.classify(targets, index, partition)
    for item in classified:
        item["dispatchable"] = item["va"] in dispatchable
    waves = sched.waves(classified)
    if wave_limit is not None:
        waves = waves[:max(0, int(wave_limit))]
    summary = {
        "targets": len(classified),
        "dispatchable": sum(1 for item in classified if item["dispatchable"]),
        "by_role": _count(item["role"] for item in classified),
        "by_cluster": _count(item["cluster"] for item in classified if item["cluster"]),
        "by_subsystem": _count(item["subsystem"] for item in classified
                               if item["subsystem"]),
        "queue_addressable": sum(1 for item in targets if item["queue_row"]),
        "queue_missing": sum(1 for item in targets if not item["queue_row"]),
        "waves": len(waves),
        "wave_widths": [len(item["targets"]) for item in waves],
        "coordinated_units": sum(1 for item in classified
                                 if item["role"] == "coordinated"),
        "in_cycle": sum(1 for item in classified
                        if item["scc"].get("cycle_size", 1) > 1),
        "largest_cycle": max([item["scc"].get("cycle_size", 1)
                              for item in classified] or [1]),
        "dependency_degraded": bool(partition.get("degraded")),
        "scc_evidence_edges": int(partition.get("edge_count") or 0),
        "universe_call_edges": int(partition.get("universe_edges") or 0),
    }
    return {
        "$schema": PLAN_SCHEMA,
        "status": "ok",
        "binary_sha256": binary_sha256,
        "database": q.default_db(),
        "summary": summary,
        "waves": waves,
        "targets": sorted(classified,
                          key=lambda item: (-item["score"], item["va"])),
    }


def _count(values):
    # type: (object) -> dict
    result = {}
    for value in values:
        result[value] = result.get(value, 0) + 1
    return dict(sorted(result.items()))


# --------------------------------------------------------------------------- #
# native child sessions: the primary worker transport
# --------------------------------------------------------------------------- #
# A reconstruction worker is a native child session of the orchestrating agent
# session. This module is not that session and does not spawn anything: it
# answers three questions for the orchestrator and nothing else.
#
#   session_plan          which targets, and what evidence each one has
#   session_task          everything one child session needs for one target
#   session_result_worker a worker callable that reads back the children's
#                        final messages
#
# The subprocess path below (``launch``, ``opencode_worker``, ``command_line``)
# is unchanged and remains the documented escape hatch for an external worker.
# The child-session path goes through the *same* ``process_target`` with a worker
# that satisfies the same ``package -> (raw, detail)`` contract, which is the
# whole design: the disposition loop cannot tell a child session from a
# subprocess, so neither can it be weakened for one of them.
def _expected_static_evidence(root, va, record):
    # type: (object, str, dict) -> dict
    """What static evidence exists for ``va`` -- availability, never a verdict.

    Three facts, and they are the three the validator's checks are decided by:
    whether an evidence pack is persisted *and* verifies, whether a complete
    untruncated machine listing exists, and whether a source span resolves.
    Each is read through the validator's own resolver, so a plan can never
    disagree with the verdict it precedes about what evidence is there.

    No verdict is derived and none is implied. A target with all three available
    is not thereby validatable: whether the checks then agree is a question for
    ``validate``, against a candidate that does not exist yet. Predicting a
    verdict from evidence availability would be a guess about a future artefact,
    and a wrong one would be indistinguishable from a real result.
    """
    destination = _evidence_destination(root, va)
    pack, state, _note = _persisted_pack(destination, va)
    categories = (pack or {}).get("categories") or {}
    listing = _listing(categories)
    source = _source(root, record)
    span = _target_span(_read_source(source["path"]), record) if source else None
    return {
        "evidence_pack": {
            "path": "%s/%s/evidence.json" % (EVIDENCE_REL, va[2:]),
            "state": state,
            "verified": state == PERSISTED_VERIFIED,
        },
        "listing": {
            # ``_listing`` returns ``None`` for absent *and* for truncated: a
            # partial body is not a listing, so one flag covers both and the
            # instruction count says which of the two a present listing is.
            "available": listing is not None,
            "instructions": len(listing[0]) if listing is not None else None,
        },
        "source_span": {
            "artifact": (relative(source["path"], root) if source else None),
            "role": source["role"] if source else None,
            "resolved": span is not None,
        },
    }


def _session_entry(root, record, index):
    # type: (object, dict, dict) -> dict
    """One plan record, projected into the shape a child session is handed."""
    va = record["va"]
    knowledge = ((index or {}).get("records") or {}).get(va) or {}
    return {
        "va": va,
        "queue_id": record.get("queue_id"),
        "queue_va": record.get("queue_va") or va[2:],
        "name": record.get("name"),
        "package": knowledge.get("package"),
        "subsystem": record.get("subsystem"),
        "cluster": record.get("cluster"),
        "role": record.get("role"),
        "reason": record.get("reason"),
        "dispatchable": bool(record.get("dispatchable")),
        # ``classify`` renames the swarm entry's ``priority`` to ``score``; both
        # names are carried because the briefing's ``frontier_reason`` reads one
        # and the operator reads the other.
        "priority": record.get("score"),
        "score": record.get("score"),
        "open_callees": list(record.get("open_callees") or []),
        "claim_state": record.get("claim_state"),
        "scc": {
            "id": (record.get("scc") or {}).get("id"),
            "size": (record.get("scc") or {}).get("size", 1),
            "members": list((record.get("scc") or {}).get("members") or [va]),
        },
        "evidence_level": knowledge.get("evidence_level"),
        "expected_static_evidence": _expected_static_evidence(root, va, knowledge),
    }


def session_plan(root=ROOT, limit=20, targets=None, live=False,
                 include_deferred=False):
    # type: (...) -> dict
    """The dispatch plan, shaped for a child session. Read-only; claims nothing.

    This is ``plan()`` with a narrower selection and a per-target evidence
    summary, for the orchestrating agent session to read before it spawns
    anything. It is not a second scheduler: every scheduling fact -- role, wave,
    open callees, SCC, score -- is the one ``plan()`` computed, and the
    selection is ``plan()``'s own ``dispatchable``/``deferred``/``excluded``
    split rather than a new one.

    **It does not claim.** There is no lease, no row write and no compare-and-set
    here, and that is deliberate: the compare-and-set lives in ``queue.claim`` as
    called by ``process_target``, so two orchestrating sessions that read the same
    plan both lose or both win the claim for the same reason a subprocess run
    does, and a plan that took a lease would be holding work nobody is about to
    do. Claim a target by running it.

    ``targets`` narrows the selection to a named batch, the same way ``run``'s
    ``vas`` does. A VA that is not in the plan is reported in
    ``requested_absent`` rather than dropped, because a plan that quietly
    omits what the caller asked for is a plan the caller cannot trust.

    ``counts`` describes *this selection*, so ``deferred`` is 0 at the default:
    ``plan`` drops a frontier-deferred target entirely when it is called with
    ``include_deferred=False``, and this module does not count a target it did
    not return. Pass ``include_deferred=True`` to schedule the continuation of
    the batch as well, which is what makes a later wave visible in the plan.

    Deterministic by construction, to the same standard as ``plan()``: no clock,
    no absolute path, no dependence on dict iteration order. Two calls against
    the same root and the same queue state are byte-identical, which is what
    makes two session plans comparable.

    ``live`` is accepted so a caller can pass its own flag through unchanged, and
    reported as ``live`` in the document. Nothing here collects evidence -- the
    evidence report reads only what is already persisted -- so on this read-only
    planning path it has nothing to switch, and saying so in the document is
    better than pretending the flag did something.
    """
    planning = plan(root=root, limit=limit, include_deferred=include_deferred)
    if planning.get("status") != "ok":
        return {
            "$schema": SESSION_PLAN_SCHEMA,
            "status": "blocked",
            "warning": planning.get("warning", "frontier survey is blocked"),
            "binary_sha256": planning.get("binary_sha256"),
            "counts": {"eligible": 0, "deferred": 0, "excluded": 0},
            "selected": 0,
            "targets": [],
        }
    records = planning.get("targets") or []
    wanted = None
    if targets:
        try:
            wanted = {normalize_va(item) for item in targets}
        except (TypeError, ValueError) as exc:
            raise ToolError("invalid_va", str(exc), 2)
    try:
        index = _index(root)
    except (OSError, ValueError) as exc:
        raise ToolError("index_unavailable",
                        "reconstruction projection cannot be built: %s" % exc, 4)
    entries = []
    eligible = deferred = excluded = 0
    for record in records:
        if wanted is not None and record["va"] not in wanted:
            continue
        # ``role`` is the availability ladder and ``dispatchable`` is the
        # frontier's view of the same question. They are reported separately
        # rather than merged into one ``excluded`` bucket, because a target the
        # frontier deferred and one the scheduler will not schedule are different
        # facts and a caller acting on the difference is scheduling a wave.
        if record.get("role") in ("blocked", "claimed", "completed"):
            excluded += 1
        elif record.get("dispatchable"):
            eligible += 1
        else:
            deferred += 1
        entries.append(_session_entry(root, record, index))
    # Same order ``plan`` publishes, so a caller can diff the two documents.
    entries.sort(key=lambda item: (-(item["score"] or 0), item["va"]))
    return {
        "$schema": SESSION_PLAN_SCHEMA,
        "status": "ok",
        "binary_sha256": planning.get("binary_sha256"),
        "database": planning.get("database"),
        "transport": {
            "channel": CHANNEL_NATIVE,
            "transport": "child_session",
            "authoritative": REPLY_FORMAT["authoritative"],
            "instruction": REPLY_FORMAT["instruction"],
            "reply_file": REPLY_FORMAT["reply_file"],
        },
        "counts": {"eligible": eligible, "deferred": deferred,
                   "excluded": excluded},
        "selected": len(entries),
        "include_deferred": bool(include_deferred),
        "live": bool(live),
        "claimed": False,
        "requested": sorted(wanted) if wanted is not None else None,
        "requested_absent": (sorted(wanted - {item["va"] for item in entries})
                             if wanted is not None else []),
        "summary": planning.get("summary") or {},
        "targets": entries,
    }


def session_task(root, entry, implementer_id, live=False, write=False, attempt=1,
                 previous=None):
    # type: (...) -> dict
    """Everything one child session needs for one target, in one document.

    Pure read plus a brief build. It does **not** claim the lease and it does not
    write: ``q.ensure_row`` is deliberately not called here, so a task can be
    built, printed and handed to a child session before anything is owned. The
    claim is taken in ``process_target``, which is where the compare-and-set
    lives, and a task document that had already claimed would hand a child
    session a lease it never took.

    The full briefing travels here, not a digest of it, because a child session
    can read every section verbatim and a digest would send it exploring the
    repository instead of reconstructing anything. ``prompt_markdown`` is the same
    package rendered for a human-scale prompt and is a convenience, never the data
    channel.

    ``reply_format`` states the transport in machine-readable form: the child's
    FINAL message is the authoritative answer, it must end with the result object
    in one fenced ```` ```json ```` block with nothing after it, the parser reads
    the final text block when the reply carries several, and a reply with no
    result object is discarded and retried. A child session that does not know
    this produces exactly the ``malformed_worker_output`` a subprocess worker
    produces when it writes prose.
    """
    va = normalize_va(entry["va"])
    planning = plan(root=root, limit=200, include_deferred=True)
    if planning.get("status") != "ok":
        raise ToolError("frontier_blocked",
                        planning.get("warning", "frontier survey is blocked"), 4)
    record = next((item for item in planning["targets"] if item["va"] == va), None)
    if record is None:
        # A task may legitimately name a target the plan does not schedule -- a
        # human re-briefing one row, or a follow-up on a closed one -- so this is
        # a synthesised record rather than a refusal. ``brief`` tolerates both
        # shapes for exactly this reason.
        record = {"va": va, "queue_va": va[2:],
                  "queue_id": entry.get("queue_id"),
                  "name": entry.get("name"),
                  "subsystem": entry.get("subsystem"),
                  "role": entry.get("role"), "reason": entry.get("reason"),
                  "score": entry.get("priority", entry.get("score")),
                  "dispatchable": entry.get("dispatchable"),
                  "claim_state": entry.get("claim_state"),
                  "scc": entry.get("scc") or {"id": None, "size": 1,
                                             "members": [va]},
                  "queue_row": None, "open_callees": entry.get("open_callees") or []}
    inputs = collect_inputs(root, va, live=live, write=write)
    package = brief(root, record, inputs, implementer_id,
                    entry.get("queue_id") or record.get("queue_id"),
                    planning["binary_sha256"], attempt=attempt,
                    previous=previous)
    constraints = package.get("reconstruction_constraints") or {}
    return {
        "$schema": SESSION_TASK_SCHEMA,
        "status": "ok",
        "va": va,
        "queue_id": package["target"].get("queue_id"),
        "name": package["target"].get("name"),
        "subsystem": package["target"].get("subsystem"),
        "package": package["target"].get("package"),
        "role": record.get("role"),
        "dispatchable": bool(record.get("dispatchable")),
        "binary_sha256": planning["binary_sha256"],
        "briefing": package,
        "prompt_markdown": wc.render_briefing_markdown(package),
        "result_contract": package["result_contract"],
        "result_template": wc.result_template(
            va, implementer_id=implementer_id,
            queue_id=package["target"].get("queue_id")),
        "write_under": constraints.get("write_under"),
        "metadata_sidecar": constraints.get("metadata_sidecar"),
        "reply_format": REPLY_FORMAT,
        "attempt": int(attempt),
        "max_attempts": MAX_ATTEMPTS,
        "claim_taken": False,
    }


def _reply_path(reply_dir, va):
    # type: (object, str) -> str
    return os.path.join(str(reply_dir), va[2:] + REPLY_SUFFIX)


def session_result_worker(replies=None, reply_dir=None, default_raw=None):
    # type: (object, object, object) -> object
    """A worker callable backed by child-session replies, not by a process.

    The contract is the existing one, ``package -> (raw, detail)``, so this drops
    straight into ``process_target`` and ``run`` with no change to the
    disposition loop. ``raw`` is the child's FINAL message, verbatim, and it goes
    into ``ingest`` -> ``wc.parse_result`` **unchanged**: no pre-parsing, no
    ``json.loads`` here, no per-field leniency. A child session is not more
    trusted than a subprocess worker, and the only way to keep that true is for
    this adapter to move bytes and nothing else.

    ``replies`` maps a normalised VA to a reply; ``reply_dir`` points at a
    directory of ``<va8>.txt`` files, read **lazily at call time** so a reply may
    land after the plan was built -- which is the normal case, because the plan
    is built first and the children answer afterwards. ``default_raw`` is used
    when neither holds a reply, which is what makes a recorded fixture replayable.

    A reply is **popped** once consumed. A second call for the same VA reports
    ``source: "absent"`` and ``exhausted: True`` rather than silently replaying
    the same bytes, and that is what keeps the in-process retry loop honest: a
    retry is a *new child session*, not a re-read of the last one. Replaying a
    reply would make ``process_target`` re-adjudicate one answer as if it were
    two, which would spend the retry budget on nothing and let a target that
    cannot improve close on its first answer.

    ``absent`` covers two different facts, and the detail dict separates them
    because ``process_target`` has to report them differently:
    ``delivered: True`` means this adapter already handed a reply over for that
    VA and has nothing left, so the next iteration is waiting on *another child
    session*; ``delivered: False`` means the transport never had a reply for this
    target at all, which is a child that never answered and is a real failure
    worth the malformed budget. Only this adapter knows which, because only this
    adapter popped the reply -- so the fact is reported as a fact and never
    inferred from the bytes.

    Either way ``raw`` is ``None`` and ``parse_result(None)`` produces the
    existing ``worker produced no output`` refusal, so a subprocess worker that
    printed nothing and a child session that never wrote a file still fail
    closed, identically and with no new refusal invented for them. Producing a
    *further* reply for a target is not this adapter's job; the orchestrating
    session spawns another child session and writes another ``<va8>.txt``.

    Neither a claim nor a write happens here, and the detail dict is shaped like
    ``launch``'s so ``process_target`` reads it with the same code it uses for a
    subprocess: ``returncode`` 0 and ``timed_out`` False because a child session
    that answered did not crash, and ``failure`` ``None`` for the same reason --
    a child session has no exit status, and inventing one would file an answer
    as a launch failure.
    """
    store = {}
    if isinstance(replies, dict):
        for key, value in replies.items():
            try:
                store[normalize_va(key)] = value
            except (TypeError, ValueError):
                continue
    elif replies:
        store[normalize_va(replies)] = default_raw
    spent = set()
    # VAs this adapter has actually handed a reply over for. Separate from
    # ``spent`` because the two answer different questions: ``spent`` says "do not
    # look again", and this says "there was something to hand over" -- which is
    # the difference between a transport that is empty and a transport that has
    # already delivered. Only this set can tell them apart, so it is the only
    # thing that reports the difference.
    delivered = set()
    lock = threading.Lock()

    def _consume(va):
        # type: (str) -> tuple
        """Take this VA's reply, once. Whoever gets it, gets it.

        ``spent`` is marked *before* the sources are consulted, so an adapter
        that has already reported ``absent`` for a target has spent it and will
        not pick a late file up. That is the same rule the in-process retry loop
        depends on -- a retry is a new child session -- and it is why a fresh
        attempt is a fresh adapter as well as a fresh session.

        An existing but empty file is returned as ``""``, not as ``None``: "the
        child wrote nothing" and "the child wrote no file" are different facts
        and ``parse_result`` has a different refusal for each (``worker produced
        empty output`` versus ``worker produced no output``). Collapsing them
        here would lose that distinction before the contract ever saw it.

        ``delivered`` is marked on exactly the paths that returned bytes, so it
        answers "did this transport ever have a reply for this target?" without
        re-reading anything. An empty file counts: the child answered, and the
        contract is what refuses the answer.
        """
        with lock:
            if va in spent:
                return None, "absent"
            spent.add(va)
            if va in store:
                raw = store.pop(va)
                delivered.add(va)
                return raw, "reply_map"
            if reply_dir is not None:
                path = _reply_path(reply_dir, va)
                try:
                    if os.path.isfile(path):
                        with open(path, encoding="utf-8") as handle:
                            raw = handle.read()
                        delivered.add(va)
                        return raw, "reply_dir"
                except OSError:
                    return None, "absent"
            if default_raw is not None:
                delivered.add(va)
                return default_raw, "reply_map"
        return None, "absent"

    def detail_for(va, source, exhausted):
        # type: (str, str, bool) -> dict
        """One launch detail, plus whether this adapter delivered for ``va``.

        ``delivered`` is read under the lock because another target of the same
        run may be reading it concurrently, and it is always present so a
        consumer never has to distinguish "false" from "absent".
        """
        with lock:
            handed_over = va in delivered
        return {"returncode": 0, "timed_out": False, "failure": None,
                "channel": CHANNEL_NATIVE, "transport": "child_session",
                "source": source, "exhausted": bool(exhausted),
                "delivered": handed_over}

    def invoke(package):
        va = normalize_va(package["target"]["va"])
        raw, source = _consume(va)
        # ``is None``, never a falsy test: an empty reply is a reply, and the
        # contract has a different refusal for it.
        if raw is None:
            return None, detail_for(va, source, True)
        return raw, detail_for(va, source, False)
    invoke.channel = CHANNEL_NATIVE
    invoke.transport = "child_session"
    return invoke


# --------------------------------------------------------------------------- #
# worker launching
# --------------------------------------------------------------------------- #
def agent_argv(briefing, command="opencode", model=None, output_format="json",
               attach=None, agent=None):
    # type: (dict, str, object, str, object, object) -> list
    """The command line for a real agent launch.

    A pure function so the launch path is testable with zero nondeterminism.
    Never a shell string -- argv is always a list. The full briefing travels on
    stdin as JSON (see ``launch``); the Markdown rendering is appended as the
    prompt subject, so it is a human-scale convenience rather than the data
    channel and cannot be relied on for large briefings.

    ``--format json`` is not a preference, it is the contract. OpenCode's
    ``--format default`` writes *every* assistant text block to stdout joined by
    newlines, so a worker that narrates before it uses a tool -- which is the
    normal shape of a real reconstruction -- emits its preamble and its answer
    as one blob, and ``json.loads`` of that blob dies on the first character.
    ``--format json`` instead writes a newline-delimited event stream in which
    text, tool calls and tool results are separate, typed events, so the result
    block is separable from the narration by structure rather than by guessing.
    ``--print-logs`` keeps diagnostics on stderr, which is where they belong.

    The parser accepts either channel, so a hand-written worker command that
    omits the flag still works; this is the default because it is the shape
    that does not need prose scraping.

    ``attach`` exists because a real agent does not read stdin. The Markdown
    rendering is ~1.7KB for a ~25KB briefing, so a worker told only by that
    rendering has no evidence at all and goes exploring the repository instead
    of reconstructing anything. Passing the briefing's path attaches the real
    payload through the CLI's own file channel, which is the mitigation the
    stdin limitation calls for.

    The prompt is placed immediately after ``run``, before the flags. OpenCode's
    ``--file`` is an array option and greedily swallows trailing positionals, so
    a prompt placed last would be read as a filename. For the same reason every
    value option (``--model``, ``--agent``, ``--format``) is emitted before
    ``--file``, which is the only array option here.
    """
    prompt = wc.render_briefing_markdown(briefing)
    if attach:
        prompt = ("The complete briefing JSON is attached as `%s`. It is the "
                  "authoritative data channel: read it before doing anything "
                  "else, because the summary below is only a digest of it.\n\n%s"
                  % (attach, prompt))
    argv = [command, "run", prompt, "--print-logs"]
    if output_format:
        argv.extend(["--format", str(output_format)])
    if model:
        argv.extend(["--model", str(model)])
    if agent:
        argv.extend(["--agent", str(agent)])
    if attach:
        argv.extend(["--file", str(attach)])
    return argv


def launch(argv, stdin_payload, cwd=None, env=None, timeout=3600):
    # type: (list, object, object, object, int) -> dict
    """Run a worker as a child process and collect its reply.

    Returns a structured result rather than raising, so a crashed worker is a
    routable outcome. argv is a list (never shell=True); the child is reaped;
    the timeout is enforced; nothing escapes the given cwd.

    The payload is encoded to bytes here because ``subprocess`` on Python 3.13+
    rejects a ``str`` for ``input``; doing it at the boundary keeps the
    orchestrator out of that version detail.
    """
    if isinstance(stdin_payload, (dict, list)):
        payload = canonical_json(stdin_payload).encode("utf-8")
    elif stdin_payload is None:
        payload = b""
    elif isinstance(stdin_payload, (bytes, bytearray)):
        payload = bytes(stdin_payload)
    else:
        payload = str(stdin_payload).encode("utf-8")
    child_env = dict(env or os.environ)
    child_env.setdefault("OPENSPORE_WORKER_BRIEFING", "1")
    try:
        completed = subprocess.run(
            argv,
            input=payload,
            cwd=cwd,
            env=child_env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=timeout,
            check=False,
        )
    except subprocess.TimeoutExpired as exc:
        return {"returncode": None, "timed_out": True,
                "stdout": exc.stdout or b"",
                "stderr": (exc.stderr or b"")[:2000], "argv": list(argv),
                "failure": "timeout"}
    except (OSError, ValueError, TypeError, IndexError) as exc:
        # ``IndexError`` is here because ``subprocess`` reads ``argv[0]`` itself:
        # an empty command line raises it, which is a spawn failure like any
        # other and must be reported as one rather than escaping the lifecycle.
        return {"returncode": None, "timed_out": False, "stdout": b"",
                "stderr": str(exc)[:2000].encode("utf-8"), "argv": list(argv),
                "failure": "spawn_failed"}
    return {
        "returncode": completed.returncode,
        "timed_out": False,
        "stdout": completed.stdout or b"",
        "stderr": (completed.stderr or b"")[-2000:],
        "argv": list(argv),
        "failure": None if completed.returncode == 0 else "nonzero_exit",
    }


def _stderr_text(launch_detail, limit=400):
    # type: (dict, int) -> str
    """The launch failure's own words, on one bounded line.

    ``launch`` reports a spawn failure by putting the ``OSError`` in ``stderr``
    and the truth in ``failure``. An operator reading a run summary needs the
    message ("No such file or directory"), not the byte string, and the byte
    string can be two kilobytes of a traceback.
    """
    raw = (launch_detail or {}).get("stderr") or b""
    if isinstance(raw, (bytes, bytearray)):
        raw = bytes(raw).decode("utf-8", "replace")
    return " ".join(str(raw).split())[:limit]


def _worker_command(launch_detail):
    # type: (dict) -> object
    """argv[0] only. argv[1] is the briefing digest, which is kilobytes."""
    argv = (launch_detail or {}).get("argv") or []
    return argv[0] if argv else None


# --------------------------------------------------------------------------- #
# per-target lifecycle
# --------------------------------------------------------------------------- #
def _resolve_row(target, binary_sha256, root):
    # type: (dict, str, object) -> dict
    """Ensure a queue row exists and return its canonical id."""
    existing = q.get(va=target["queue_va"], binary_sha256=binary_sha256)
    if q.ok(existing):
        return existing["investigation"]
    inserted = q.ensure_row(
        target["queue_va"], name=target.get("name"),
        subsystem=target.get("subsystem"), binary_sha256=binary_sha256,
        why_interesting="frontier score %s; reason codes %s"
                        % (target.get("score"), ",".join(target.get("reason_codes") or [])),
    )
    if not q.ok(inserted):
        raise ToolError("queue_insert_failed",
                        "cannot create a queue row for %s: %s"
                        % (target["va"], inserted.get("message")), 1,
                        {"queue": inserted})
    return inserted.get("investigation") or {}


def _bump(attempts, key):
    # type: (dict, str) -> dict
    updated = dict(attempts or {})
    try:
        current = int(updated.get(key, 0))
    except (TypeError, ValueError):
        current = 0
    updated[key] = current + 1
    try:
        updated["_total"] = int(updated.get("_total", 0)) + 1
    except (TypeError, ValueError):
        updated["_total"] = 1
    return updated


def _read_attempts(row):
    # type: (dict) -> dict
    raw = (row or {}).get("attempts")
    if not raw:
        return {}
    try:
        value = json.loads(raw) if isinstance(raw, str) else raw
    except ValueError:
        return {}
    return value if isinstance(value, dict) else {}


def collect_inputs(root, va, live=False, write=False):
    # type: (...) -> dict
    """Evidence + context + validation for one target, all read-side.

    **One collection per target**, and ``evidence``/``context``/``validate`` are
    all handed the SAME object. That discipline exists because a second
    collection silently drops ``live``: the validator used to adjudicate
    ABI-adjacent claims against a pack with no disassembly and no live function
    in it while the briefing it was judging quoted one. Re-collecting also
    doubled the Ghidra round trips and produced two packs that could not be
    compared by digest.

    The single collection is the *persisted* one wherever a pack that verifies
    exists, and that is the whole point. ``collect(live=False)`` cannot produce
    a disassembly listing -- it never calls the live disassembly endpoint, so it
    stores ``disassembly = unavailable`` -- while the verified pack on disk
    carries one. Collecting instead of loading therefore threw away
    hash-anchored machine evidence that was already there, and handed the
    *weaker* of the two packs to ``validate`` as ``evidence=``, which overrides
    the validator's own reuse of the persisted pack: a candidate that had
    already reached a static PASS standalone came back ``NOT_AVAILABLE`` inside
    the pipeline, and the worker was briefed with ``DISASSEMBLY`` in
    ``missing_sections`` for a target whose listing was on disk.

    Precedence, in full:

    * ``live=False`` and a pack verifies -> that pack. ``collect`` is not called,
      so there is still no second round trip.
    * ``live=True`` -> a live collection, which wins whenever it produced a live
      observation (the pack's own ``evidence_state`` is ``LIVE``). A live read is
      the point of asking for ``live``; a persisted pack must never be preferred
      over one.
    * ``live=True`` and the live read produced nothing -> the verified pack, as
      the fallback. It is the only pack that can carry a listing, so a failed
      live read must not cost the target the evidence it already had.
    * no pack, or one that fails verification -> ``collect``, as before. The
      verification failure is reported in ``pack_note`` rather than swallowed: a
      pack that could not be trusted must not vanish silently into a weaker
      collection.

    ``write`` follows the validator's rule rather than a second one: a pack file
    that exists but did not verify is never overwritten, because a collection
    made on this path cannot produce a listing and would destroy the only copy
    of evidence this path cannot re-derive.

    Provenance stays honest because the pack is used exactly as it was written:
    the briefing's ``evidence.state`` is the pack's own ``evidence_state`` and
    its ``content_sha256`` is the pack's own digest, so a ``PERSISTED`` pack is
    never labelled ``live`` and a ``LIVE`` one is never relabelled to hide where
    it came from. ``pack_source`` names the pack that was used;
    ``pack_state``/``pack_note`` describe the pack on disk and say which of the
    four rules above applied to it. The validator is told the pack is
    caller-supplied because it is: this function, not the validator, decided.
    """
    va = normalize_va(va)
    destination = _evidence_destination(root, va)
    pack, state, note = _persisted_pack(destination, va)
    verified = pack is not None and state == PERSISTED_VERIFIED
    if live:
        collected = collect(root=root, va=va, live=True, write=write)
        if collected.get("evidence_state") != EVIDENCE_STATE_LIVE and verified:
            # A live read that produced no live observation. The verified pack is
            # the fallback. Its failed live attempts are not grafted onto it:
            # the pack is used exactly as it was written, and the failed read is
            # visible as ``live=True`` with ``pack_source == persisted_pack``.
            source = EVIDENCE_SOURCE_PERSISTED
            evidence = pack
        else:
            source = EVIDENCE_SOURCE_LIVE
            evidence = collected
    elif verified:
        source = EVIDENCE_SOURCE_PERSISTED
        evidence = pack
    else:
        source = EVIDENCE_SOURCE_RECOLLECTED
        evidence = collect(root=root, va=va, live=False,
                           write=bool(write) and state == PERSISTED_ABSENT)
    context = build_context(root=root, va=va, evidence=evidence, live=live,
                            write=write)
    try:
        validation = validate(root=root, va=va, evidence=evidence,
                              context=context, write=False)
    except ToolError:
        validation = {"status": "NOT_AVAILABLE", "checks": {}}
    return {"evidence": evidence, "context": context, "validation": validation,
            "pack_source": source, "pack_state": state, "pack_note": note}


def brief(root, target, inputs, implementer_id, inv_id, binary_sha256,
          attempt=1, previous=None):
    # type: (...) -> dict
    """Build the worker package for a target.

    The target may be either a raw ``swarm`` entry (``priority``/``reason_codes``)
    or a classified plan record (``score``/``reason``), because the CLI brief
    path and the run path hand over different shapes. Normalising here is what
    keeps the worker from receiving a blank FRONTIER REASON section.
    """
    return wc.briefing(
        target["va"], root=root, target=target,
        evidence=inputs["evidence"], context=inputs["context"],
        validation=inputs["validation"], implementer_id=implementer_id,
        inv_id=inv_id, binary_sha256=binary_sha256,
        scc=target.get("scc"), attempt=attempt, max_attempts=MAX_ATTEMPTS,
        previous=previous,
    )


def ingest(raw, va, inv_id):
    # type: (object, str, str) -> dict
    """Parse a worker reply. Returns a typed result, never raises."""
    return wc.parse_result(raw, va=va, inv_id=inv_id)


def reconcile(outcome, verdict, target, inv_id, implementer_id,
              binary_sha256, attempts, evidence_refs, detail=None):
    # type: (...) -> dict
    """Decide the terminal disposition of a target's run.

    Ordering is deliberate and is the whole safety argument: a target is only
    completed on a static validator PASS of a candidate the worker actually
    produced. ``verdict`` is the static dimension alone. The runtime dimension
    never participates -- no original-process observation exists to promote, and
    a runtime gate is an open capability question, not a completion bar. A target
    closed here has had its reconstruction accepted against the binary, nothing
    more, and the caller records the still-open gate alongside the closure.
    """
    common = {"va": target["va"], "queue_id": inv_id, "outcome": outcome,
              "validation": verdict, "attempts": attempts,
              "evidence_refs": sorted(evidence_refs)}
    if verdict == "FAIL":
        return dict(common, action="retry", code="validation_fail",
                    detail=detail)
    if verdict == "WARN":
        # WARN is a review request, not a failure: no attempt is burned and the
        # target is never closed on a warning.
        return dict(common, action="review", code="validation_warn",
                    detail=detail)
    if verdict in ("UNKNOWN", "NOT_AVAILABLE"):
        if outcome in wc.TERMINAL_OUTCOMES:
            # The worker claimed a candidate but the validator found nothing to
            # check -- almost always because no source artifact exists. That is
            # a defect in the candidate, not a review request, and retrying is
            # the only thing that can fix it. Bounded, so it cannot loop.
            return dict(common, action="retry",
                        code="candidate_not_validatable", detail=detail)
        # An honest STILL_UNKNOWN/BLOCKED really is a review item: there is no
        # candidate to retry, only a question for a human.
        return dict(common, action="review",
                    code="validation_%s" % verdict.lower(), detail=detail)
    if verdict == "PASS" and outcome in wc.TERMINAL_OUTCOMES:
        return dict(common, action="complete", code="validated", detail=detail)
    if outcome in wc.UNSATISFIED_OUTCOMES:
        return dict(common, action="retry", code=outcome.lower(), detail=detail)
    if outcome == "BLOCKED":
        return dict(common, action="block", code="blocked", detail=detail)
    return dict(common, action="review", code="unclassified_outcome",
                detail=detail)


def _worker_launch_defaults(worker, cwd=None, env=None, timeout=None):
    # type: (object, object, object, object) -> bool
    """Forward the per-run launch parameters to a worker that accepts them.

    ``process_target`` takes ``cwd``/``worker_env``/``worker_timeout`` per run,
    but the worker contract is ``package -> (raw, detail)`` and widening it
    would break every worker that already honours it. So the forwarding is done
    through an optional ``configure_launch`` hook: a worker that has one gets
    the values, and a worker that has none -- an in-process test worker, a
    hand-rolled callable -- keeps the parameters it was built with and is
    unaffected.

    Only values that are not ``None`` are forwarded. That is what makes
    ``worker_timeout`` win over an adapter's own default when the caller sets
    one, without a caller that says nothing silently resetting a timeout the
    adapter was deliberately given.
    """
    configure = getattr(worker, "configure_launch", None)
    if configure is None:
        return False
    configure(cwd=cwd, env=env, timeout=timeout)
    return True


def _try_queue(operation, events, op, **shape):
    # type: (object, list, str, object) -> object
    """Run a queue write the failure path depends on, and never raise.

    The whole purpose of the failure path is to end a lease. If the queue write
    that would end it is itself the broken thing, raising from here would leave
    the lease live *and* discard the event trail that says so -- strictly worse
    than reporting ``ok: False`` and letting the lease TTL, or ``reap``, deal
    with a row whose queue is down. So a broken write is recorded, not raised.
    """
    try:
        result = operation()
    except Exception as exc:  # noqa: BLE001
        events.append(dict(shape, op=op, ok=False, code="queue_write_failed",
                           message=str(exc)[:200]))
        return None
    # A non-mapping is treated as a failed write: this path must not be the one
    # that raises, whatever the queue layer handed back.
    if not isinstance(result, dict) or not q.ok(result):
        events.append(dict(shape, op=op, ok=False,
                           code=(q.code(result) if isinstance(result, dict)
                                 else None) or "queue_write_refused"))
        return result
    events.append(dict(shape, op=op, ok=True))
    return result


def _release_after_exception(va, inv_id, implementer_id, events, attempts, exc,
                             lease_open):
    # type: (str, str, str, list, dict, object, bool) -> dict
    """End the lease after an exception, and record why.

    Without this, an exception anywhere after a successful ``claim`` -- in the
    worker callable, in ``validate``, in a queue write -- left the row
    ``status="active"`` under a lease that nobody was going to renew.
    ``run()`` caught the exception one level up and reported ``status: "error"``
    with an empty event list, so the target was invisible to ``reap`` and to the
    next run until a human noticed. That is the unrecoverable state this module
    exists to prevent (module docstring, step 8), and the docstring promised the
    opposite.

    The release is guarded twice. ``lease_open`` is cleared by every code path
    that ends the lease, and only once that call has returned, so an exception
    raised *before* the lease ended still releases it while one raised after it
    does not release a second time; and ``queue.release`` itself refuses any
    implementer that is not the current holder, so a worker that lost its lease
    can never release the new owner's.

    The row is parked rather than requeued. An unhandled exception is a defect
    in this process, not a condition another attempt can satisfy, and parking
    is the only bounded thing to do with one. The exception is converted into a
    record rather than re-raised so the events survive: ``run`` would otherwise
    replace them with an empty list and throw the audit trail away.
    """
    code = getattr(exc, "code", None) or exc.__class__.__name__
    message = str(exc)[:500]
    attempts = _bump(attempts, "_total")
    events.append({"op": "error", "ok": False, "code": code, "message": message})
    # Evidence first, lease second. The checkpoint write is guarded by the lease
    # token, so when the lease is already gone this is refused with
    # ``not_owner`` and records nothing durable -- which is why the events are
    # the audit trail for that case.
    _try_queue(
        lambda: q.checkpoint(
            inv_id, implementer_id,
            payload={"stage": "VALIDATE", "next_action": "human_review",
                     "stop_reason": "orchestrator_exception",
                     "last_error": message, "code": code, "attempts": attempts},
            stage="VALIDATE", attempts=attempts),
        events, "checkpoint", stage="VALIDATE")
    if not lease_open:
        events.append({"op": "release", "to": "none", "ok": True,
                       "why": "lease_already_ended"})
        return {"va": va, "queue_id": inv_id, "status": "error", "code": code,
                "message": message, "attempts": attempts, "events": events,
                "lease_released": False}
    reason = "escalated:%s" % code
    released = _try_queue(
        lambda: q.release(inv_id, implementer_id, to="blocked", reason=reason),
        events, "release", to="blocked", why=reason)
    return {"va": va, "queue_id": inv_id, "status": "error", "code": code,
            "message": message, "attempts": attempts, "events": events,
            "lease_released": bool(released and q.ok(released)
                                   and released.get("released"))}


def process_target(root, target, worker, implementer_id, binary_sha256,
                   live=False, write=False, ttl=LEASE_TTL, cwd=None,
                   worker_env=None, worker_timeout=None, allow_stale=False,
                   adjudicator_id=None, iterations=None, budget=None,
                   root_index=None):
    # type: (...) -> dict
    """Run one target through the whole lifecycle. Returns a traceable record.

    Safe to call concurrently for *different* targets: every mutation is a
    compare-and-set on that target's own queue row, so two workers never
    contend on the same row unless they raced for the same claim, and that
    race is resolved by ``claim`` returning ``already_claimed`` to the loser.

    ``cwd``/``worker_env``/``worker_timeout`` are the per-run launch parameters
    and are forwarded to the worker through its optional ``configure_launch``
    hook -- see ``_worker_launch_defaults``. ``worker_timeout`` defaults to
    ``None``, meaning "whatever the worker was built with", so a run that sets
    no timeout cannot silently override an adapter that was given one.
    """
    if iterations is None:
        iterations = MAX_ITERATIONS
    if budget is None:
        budget = MAX_TOTAL_ATTEMPTS
    va = normalize_va(target["va"])
    events = []
    row = _resolve_row(target, binary_sha256, root)
    inv_id = row.get("id")
    if not inv_id:
        raise ToolError("queue_row_unresolved",
                        "no canonical queue id for %s" % va, 1)

    claimed = q.claim(inv_id, implementer_id, binary_sha256=binary_sha256,
                      ttl=ttl, allow_stale=allow_stale)
    if not q.ok(claimed):
        events.append({"op": "claim", "ok": False, "code": q.code(claimed)})
        return {"va": va, "queue_id": inv_id, "status": "skipped",
                "code": q.code(claimed) or "claim_failed", "events": events,
                "message": claimed.get("message")}
    events.append({"op": "claim", "ok": True, "idempotent": bool(claimed.get("idempotent"))})

    row = claimed.get("investigation") or row
    attempts = _read_attempts(row)
    # The per-run launch parameters reach the worker through its own hook rather
    # than a second argument: the worker contract is ``package -> (raw, detail)``
    # and widening it would break every worker that already honours it.
    _worker_launch_defaults(worker, cwd=cwd, env=worker_env,
                            timeout=worker_timeout)
    previous = None
    stop = None
    # A lease is only ever released by the code path that took it. Every
    # ``release``/``close`` below clears this flag *after* the call returns, so
    # an exception raised before the lease ended still releases it and one
    # raised after it does not release a second time. The exception handler
    # reads the flag, and ``queue.release`` independently refuses any
    # implementer that is not the current holder.
    lease_open = True
    try:
        for _ in range(max(1, int(iterations))):
            if int(attempts.get("_total", 0)) >= budget:
                stop = "attempt_budget"
                break
            inputs = collect_inputs(root, va, live=live, write=write)
            package = brief(root, target, inputs, implementer_id, inv_id,
                            binary_sha256,
                            attempt=int(attempts.get("REPLACE", 0)) + 1,
                            previous=previous)
            events.append({"op": "brief", "content_sha256": package["content_sha256"],
                           "missing_evidence": package["evidence"]["missing_sections"]})
            started = time.time()
            raw, launch_detail = worker(package)
            elapsed = time.time() - started
            launch_failure = launch_detail.get("failure")
            # ``channel``/``transport`` are read from whatever the worker
            # reported, exactly as ``returncode`` and ``failure`` are. A native
            # child-session worker sets them and a subprocess worker does not, and
            # the loop does not branch on either: the transport is recorded so a
            # run's own output proves which one produced it, never so the
            # disposition can depend on it.
            events.append({"op": "launch", "seconds": round(elapsed, 3),
                           "returncode": launch_detail.get("returncode"),
                           "timed_out": launch_detail.get("timed_out"),
                           "failure": launch_failure,
                           "channel": launch_detail.get("channel"),
                           "transport": launch_detail.get("transport"),
                           "source": launch_detail.get("source")})
            if launch_detail.get("timed_out") or launch_failure == "timeout":
                parsed = {"accepted": False, "code": "worker_timeout",
                          "reason": "worker exceeded its time budget"}
                raw = None
            elif launch_failure == "spawn_failed":
                # The worker never ran, so there is no reply to be malformed:
                # filing this as a malformed worker output blames the model for
                # an operator's typo, burns the malformed budget on a condition
                # no reply can fix, and hides the cause. Hence its own branch,
                # its own code, and a parked row rather than a requeue -- a
                # missing binary is the dominant cause and no second attempt can
                # fix it. The checkpoint records argv[0] only, because argv[1]
                # is the briefing digest and must not land in a durable row.
                detail = _stderr_text(launch_detail)
                code = "worker_spawn_failed"
                reason = "escalated:%s" % code
                attempts = _bump(attempts, "_total")
                # Evidence first, lease second, on this path too.
                q.checkpoint(inv_id, implementer_id,
                             payload={"stage": "LAUNCH",
                                      "last_error": detail,
                                      "worker_command": _worker_command(launch_detail),
                                      "launch_failure": launch_failure,
                                      "next_action": "fix_worker_command",
                                      "attempts": attempts},
                             stage="LAUNCH", attempts=attempts)
                q.release(inv_id, implementer_id, to="blocked", reason=reason)
                lease_open = False
                events.append({"op": "release", "to": "blocked", "why": reason})
                return {"va": va, "queue_id": inv_id, "status": "blocked",
                        "code": code, "attempts": attempts, "events": events,
                        "launch_failure": launch_failure, "detail": detail,
                        "message": "worker command could not be executed: %s"
                                   % detail}
            else:
                parsed = ingest(raw, va, inv_id)
            if not parsed.get("accepted"):
                # ``raw is None`` and ``launch_detail["delivered"] is True`` is one
                # fact, not two: the worker answered this target, the answer was
                # ingested and adjudicated, the disposition was a retry, and the
                # transport has no further reply because only the orchestrating
                # session can spawn the child that would produce one. Filing that
                # as ``malformed_worker_output`` blamed the worker's answer for a
                # transport condition, spent the malformed budget on something no
                # reply could fix, and made the run summary the least truthful
                # thing in it. Its own status, its own code, and its own
                # ``next_action`` instead. The branch reads the *detail*, never the
                # reply text and never anything the worker said: a subprocess
                # worker carries no ``delivered`` key at all, so it takes the
                # ``malformed`` arm below unchanged and a worker that printed
                # nothing is still a failure.
                if raw is None and launch_detail.get("delivered") is True:
                    # Not a verdict and not a failure. The row goes back to
                    # ``queued`` -- not blocked, because nothing is wrong with it
                    # -- and the checkpoint names the only thing that can move it.
                    attempts = _bump(attempts, "_total")
                    events.append({"op": "ingest", "ok": False,
                                   "code": parsed.get("code"),
                                   "reason": parsed.get("reason"),
                                   "transport_exhausted": True})
                    q.checkpoint(
                        inv_id, implementer_id,
                        payload={"stage": "REPLACE",
                                 "last_error": parsed.get("reason"),
                                 "next_action": "spawn_another_child_session",
                                 "attempts": attempts},
                        stage="REPLACE", attempts=attempts)
                    q.release(inv_id, implementer_id, to="queued")
                    lease_open = False
                    events.append({"op": "release", "to": "queued",
                                   "why": "retry_pending", "attempts": attempts})
                    return {"va": va, "queue_id": inv_id,
                            "status": "retry_pending",
                            "code": "retry_pending_child_session",
                            "attempts": attempts, "events": events,
                            "detail": parsed.get("reason"),
                            "message": ("this transport has no further reply for "
                                        "%s; another child session has to be "
                                        "spawned to retry it" % va)}
                attempts = _bump(attempts, "_malformed")
                events.append({"op": "ingest", "ok": False,
                               "code": parsed.get("code"),
                               "reason": parsed.get("reason")})
                verdict = None
                outcome = None
                detail = parsed.get("reason")
                if int(attempts.get("_malformed", 0)) >= MAX_MALFORMED:
                    stop = "malformed_worker_output"
                    break
                # Evidence first, lease second: a crash between the two leaves a
                # recoverable active row whose checkpoint explains itself.
                q.checkpoint(inv_id, implementer_id,
                             payload={"stage": "REPLACE", "last_error": parsed.get("reason"),
                                      "raw_sha256": parsed.get("raw_sha256"),
                                      "next_action": "respawn_worker"},
                             stage="REPLACE", attempts=attempts)
                q.release(inv_id, implementer_id, to="queued")
                lease_open = False
                events.append({"op": "release", "to": "queued", "why": parsed.get("code")})
                return {"va": va, "queue_id": inv_id, "status": "partial",
                        "code": parsed.get("code"), "attempts": attempts,
                        "events": events, "detail": detail}
            result = parsed["result"]
            outcome = result.get("outcome")
            events.append({"op": "ingest", "ok": True, "outcome": outcome})

            source_files = [str(item) for item in (result.get("source_files") or [])]
            evidence_refs = set(str(item) for item in (result.get("evidence_refs") or []))
            evidence_refs.update(source_files)
            # Same pack the worker was briefed from. ``validate`` re-collects with
            # ``live=False`` when handed nothing, so omitting this would adjudicate
            # the candidate against a strictly weaker pack than the one the worker
            # could see. ``.get`` keeps the absent-pack case (and any future caller
            # that supplies no pack) on the validator's own collection path.
            validation = validate(root=root, va=va,
                                  evidence=inputs.get("evidence"),
                                  context=inputs.get("context"),
                                  write=write)
            verdict = validation.get("status")
            # The two dimensions are recorded apart so neither can be read as the
            # other. ``verdict`` is the static verdict and is the only thing
            # ``reconcile`` sees; ``runtime`` travels with the row so a closed target
            # still shows that the original process was never observed.
            runtime = validation.get("runtime") or {}
            # The same two facts, named as a pair on every terminal record. A run
            # summary counts the two axes separately, and it can only do that
            # honestly if the per-target record states them separately too --
            # ``validation`` alone would be the static verdict under a name that
            # reads like both. The full report is deliberately *not* attached: a
            # run over twenty targets would carry twenty complete validation
            # reports, and the two numbers a caller reads off them are these.
            static_validation = verdict
            runtime_status = runtime.get("status")
            # ``validated`` is the count of original-process observations behind
            # ``runtime_status``. It is carried because it is what proves the axis
            # was not asserted: ``RUNTIME: PASS`` is only reachable when this is
            # positive, and a reader can check that rather than take it on trust.
            runtime_axis = {"status": runtime.get("status"),
                            "validated": int(runtime.get("validated") or 0),
                            "gated": bool(runtime.get("gated")),
                            "gates": runtime.get("gates") or []}
            events.append({"op": "validate", "status": verdict,
                           "dimension": "STATIC",
                           "runtime_status": runtime.get("status"),
                           "runtime_gated": bool(runtime.get("gated")),
                           "source_role": (validation.get("source") or {}).get("role"),
                           "coverage": (validation.get("coverage") or {}).get("ratio")})

            attempts = _bump(attempts, "REPLACE")
            attempts = _bump(attempts, "VALIDATE")
            if adjudicator_id:
                attempts["VALIDATE_ADJUDICATED"] = attempts.get("VALIDATE_ADJUDICATED", 0) + 1
            decision = reconcile(outcome, verdict, target, inv_id, implementer_id,
                                 binary_sha256, attempts, evidence_refs,
                                 detail=validation.get("checks"))
            previous = {"outcome": outcome, "summary": result.get("summary"),
                        "validation": validation}

            payload = {"stage": "VALIDATE", "outcome": outcome,
                       "validation": verdict,
                       "validation_dimension": "STATIC",
                       "runtime": {"status": runtime.get("status"),
                                   "gated": bool(runtime.get("gated")),
                                   "gates": runtime.get("gates") or []},
                       "summary": result.get("summary"),
                       "source_files": source_files,
                       "failed_checks": sorted(
                           name for name, check in
                           (validation.get("checks") or {}).items()
                           if isinstance(check, dict)
                           and check.get("status") == "FAIL"),
                       "next_action": decision["action"],
                       "briefing_content_sha256":
                           package["content_sha256"]}
            if launch_failure:
                # A nonzero exit is recorded, never acted on. The document is
                # the deliverable and the exit status only describes the
                # process that printed it, so a worker that answered correctly
                # and then crashed has still answered; conversely a launch
                # failure must never be laundered into a validation verdict,
                # which is why the two are never merged into one field.
                payload["launch_failure"] = launch_failure
            # Record the evidence before the lease ends.
            q.checkpoint(inv_id, implementer_id,
                         payload=payload,
                         stage="VALIDATE", attempts=attempts,
                         evidence_refs=sorted(evidence_refs),
                         adjudicator_id=adjudicator_id)
            events.append({"op": "checkpoint", "stage": "VALIDATE",
                           "attempts": attempts})

            if decision["action"] == "complete":
                closed = q.close(inv_id, implementer_id, disposition="done",
                                 binary_sha256=binary_sha256)
                lease_open = False
                events.append({"op": "close", "ok": q.ok(closed),
                               "closed": bool(closed.get("closed"))})
                # ``closed: False`` on an otherwise successful close is the
                # idempotent re-close of a row that is already terminal, i.e. some
                # other actor got there first. Treating that as a completion would
                # both misreport this target and, worse, count a prerequisite as
                # landed that never was -- which would promote its dependents
                # against work that does not exist.
                if not q.ok(closed) or not closed.get("closed"):
                    return {"va": va, "queue_id": inv_id, "status": "conflict",
                            "code": q.code(closed) or ("target_obsolete"
                                                       if q.ok(closed) else "close_refused"),
                            "message": closed.get("message")
                            or ("investigation was already terminal before this "
                                "run closed it; the work was not recorded"),
                            "outcome": outcome, "validation": verdict,
                            "static_validation": static_validation,
                            "runtime_status": runtime_status,
                                "attempts": attempts, "source_files": source_files,
                            "events": events}
                return {"va": va, "queue_id": inv_id, "status": "complete",
                        "code": decision["code"], "outcome": outcome,
                        "validation": verdict, "validation_dimension": "STATIC",
                        "static_validation": static_validation,
                        "runtime_status": runtime_status,
                        "runtime": runtime_axis,
                        "attempts": attempts,
                        "source_files": source_files, "events": events}
            if decision["action"] == "review":
                released = q.release(inv_id, implementer_id, to="blocked",
                                     reason=decision["code"])
                lease_open = False
                events.append({"op": "release", "to": "blocked",
                               "why": decision["code"]})
                return {"va": va, "queue_id": inv_id,
                        "status": "review_required",
                        "code": decision["code"], "outcome": outcome,
                        "validation": verdict, "validation_dimension": "STATIC",
                        "static_validation": static_validation,
                        "runtime_status": runtime_status,
                        "attempts": attempts,
                        "source_files": source_files, "events": events}
            if decision["action"] == "block":
                released = q.release(inv_id, implementer_id, to="blocked",
                                     reason="blocked")
                lease_open = False
                events.append({"op": "release", "to": "blocked", "why": "blocked"})
                return {"va": va, "queue_id": inv_id, "status": "blocked",
                        "code": "blocked", "outcome": outcome,
                        "validation": verdict, "validation_dimension": "STATIC",
                        "static_validation": static_validation,
                        "runtime_status": runtime_status,
                        "attempts": attempts, "events": events}
            # action == retry
            # Bound each retry class by its own counter. A validation FAIL is spent
            # on new code (MAX_VALIDATION_RETRIES re-adjudications); every other
            # retryable disposition is spent on a worker that could not produce a
            # validatable candidate. Sharing one counter would let a target that
            # only ever returns the same unusable answer slip past the cap the
            # operator thinks is protecting them.
            if decision["code"] == "validation_fail":
                bound = MAX_VALIDATION_RETRIES + 1
                retry_key = "VALIDATE"
            else:
                bound = MAX_ATTEMPTS
                retry_key = "_outcomes"
                attempts = _bump(attempts, retry_key)
            if int(attempts.get(retry_key, 0)) >= bound:
                stop = decision["code"]
                break
            q.checkpoint(inv_id, implementer_id,
                         payload={"stage": "VALIDATE", "action": "retry",
                                  "code": decision["code"],
                                  "attempts": attempts,
                                  "next_action": "respawn_worker"},
                         stage="VALIDATE", attempts=attempts)
            q.release(inv_id, implementer_id, to="queued")
            lease_open = False
            events.append({"op": "release", "to": "queued", "why": "retry",
                           "attempts": attempts})
            # The next iteration re-claims with the same worker identity, so the
            # retry is a continuation of the same lease, not a competing one.

        # Every exit path below is a bound tripping, not a verdict.
        attempts = _bump(attempts, "_total")
        q.checkpoint(inv_id, implementer_id,
                     payload={"stage": "VALIDATE", "next_action": "human_review",
                              "stop_reason": stop, "attempts": attempts},
                     stage="VALIDATE", attempts=attempts)
        reason = "escalated:%s" % (stop or "iteration_bound")
        q.release(inv_id, implementer_id, to="blocked", reason=reason)
        lease_open = False
        events.append({"op": "release", "to": "blocked", "why": reason})
        return {"va": va, "queue_id": inv_id, "status": "blocked",
                "code": reason, "attempts": attempts, "events": events}
    except Exception as exc:  # noqa: BLE001 - the lease must not outlive us
        return _release_after_exception(va, inv_id, implementer_id, events,
                                        attempts, exc, lease_open)


# --------------------------------------------------------------------------- #
# run
# --------------------------------------------------------------------------- #
def subprocess_worker(argv_builder=None, cwd=None, env=None, timeout=3600):
    # type: (...) -> object
    """Default worker: launch a child process and hand back its stdout.

    ``argv_builder(package) -> argv`` keeps the command line a pure function of
    the briefing, which is what makes the real launch path testable without
    asserting anything about model output.
    """
    state = {"cwd": cwd, "env": env, "timeout": timeout}

    def invoke(package):
        raw, detail = _run_once(argv_builder, package, state["cwd"],
                                state["env"], state["timeout"])
        detail["channel"] = CHANNEL_CUSTOM
        return raw, detail
    invoke.configure_launch = _configurer(state)
    invoke.channel = CHANNEL_CUSTOM
    return invoke


def opencode_worker(command="opencode", model=None, agent=None,
                    output_format="json", attach=None, extra_argv=None,
                    cwd=None, env=None, timeout=3600):
    # type: (...) -> object
    """The production worker: ``opencode`` in the deterministic JSONL channel.

    The argv comes from ``agent_argv`` rather than being assembled here, so
    there is exactly one definition of the launch contract in this module and
    the documented ``--format json`` is what production actually runs -- not
    only what the tests and the docs described.

    The briefing is carried twice, on purpose, for two different jobs:

    * the **positional prompt** is ``agent_argv``'s Markdown digest. With no
      positional, ``opencode run`` reads stdin *as the prompt*, and stdin here
      is one ~25KB JSON data document with no instruction anywhere in it, so
      the agent would be asked to reconstruct something it was never told
      about. The digest is the task statement; it is also the only part of the
      briefing a size-limited command line can carry.
    * **stdin** stays the authoritative data channel (see ``launch``), verbatim
      and hashed, for a worker that does read it.

    ``attach`` closes the remaining gap -- an agent that ignores stdin -- by
    also handing the briefing's path to ``--file``; see ``agent_argv``.

    ``extra_argv`` is appended last, after any ``--file``, so it must not
    contain a positional: OpenCode reads the token after an array option as one
    more of its values. ``worker_adapter`` is what feeds it, and it forwards
    only the operator's flags.
    """
    state = {"cwd": cwd, "env": env, "timeout": timeout}

    def build(package):
        argv = agent_argv(package, command=command, model=model,
                          output_format=output_format, attach=attach,
                          agent=agent)
        if extra_argv:
            argv.extend(str(item) for item in extra_argv)
        return argv

    def invoke(package):
        raw, detail = _run_once(build, package, state["cwd"], state["env"],
                                state["timeout"])
        detail["channel"] = CHANNEL_JSONL
        return raw, detail
    invoke.configure_launch = _configurer(state)
    invoke.channel = CHANNEL_JSONL
    return invoke


def _configurer(state):
    # type: (dict) -> object
    """A ``configure_launch`` hook over an adapter's mutable launch state."""
    def configure_launch(cwd=None, env=None, timeout=None):
        for name, value in (("cwd", cwd), ("env", env), ("timeout", timeout)):
            if value is not None:
                state[name] = value
    return configure_launch


def _run_once(argv_builder, package, cwd, env, timeout):
    argv = argv_builder(package) if argv_builder else None
    if argv is None:
        raise ToolError("worker_unconfigured", "no worker command was configured", 2)
    detail = launch(argv, package, cwd=cwd, env=env, timeout=timeout)
    return detail["stdout"], detail


def callable_worker(function):
    # type: (object) -> object
    """Wrap a plain callable ``package -> dict`` as a worker."""
    def invoke(package):
        return canonical_json(function(package)), {"returncode": 0,
                                                   "timed_out": False,
                                                   "failure": None,
                                                   "channel": CHANNEL_CUSTOM}
    return invoke


def run(root=ROOT, limit=20, worker=None, implementer_id=None, live=False,
        write=False, max_workers=4, ttl=LEASE_TTL, cwd=None, worker_env=None,
        worker_timeout=None, allow_stale=False, adjudicators=None,
        dry_run=False, vas=None):
    # type: (...) -> dict
    """Run the pipeline: plan -> claim -> brief -> worker -> validate -> record.

    Targets inside one wave are dispatched concurrently -- a wave is by
    construction a set with no ordering constraints between its members.
    Targets in different waves run in wave order, which is the only
    serialization the dependency graph justifies.

    ``vas`` restricts the run to a named batch. Without it the run takes the
    top ``limit`` dispatchable targets, which is right for a daemon and wrong
    for a scoped job: a caller that means "these sixteen" must be able to say
    so, or a limit silently becomes a claim on whatever else is at the top of
    the frontier.

    ``cwd``/``worker_env``/``worker_timeout`` are forwarded to the worker
    adapter per target; all three default to ``None``, which means "whatever the
    adapter was built with" rather than a value this layer invents.

    The summary reports the two validation axes apart -- ``static_validated``,
    ``runtime_validated`` and ``runtime_gated`` alongside the disposition
    counters -- because ``complete`` says a target was closed and a closure is a
    static claim. ``runtime_validated`` is 0 unless some canonical record
    reports original-process validation, and a static ``PASS`` never reaches it.
    ``worker_channel``/``worker_transport`` say which transport answered, and
    every ``launch`` event carries the same pair.

    ``retry_pending`` is a disposition counter and not a verdict: it counts the
    targets whose answer was received and judged, whose disposition was a retry,
    and whose retry needs a child session this process cannot spawn. Its rows are
    left ``queued`` for the next session, so it is the one counter a run can
    finish with non-zero and still be a clean run.
    """
    if worker is None:
        raise ToolError("worker_required",
                        "run() needs a worker; pass a callable or a subprocess "
                        "launcher (orchestration is never launched implicitly)", 2)
    implementation = implementer_id or "orchestrator-%d" % os.getpid()
    # A named batch is its own scope, so ``limit`` must not truncate it. The
    # plan is taken whole and filtered below; capping first would silently drop
    # a target the caller asked for by name because something else outranked it,
    # which is indistinguishable from a target that does not exist.
    planning = plan(root=root, limit=(None if vas else limit))
    if planning.get("status") != "ok":
        return {"$schema": RUN_SCHEMA, "status": "blocked",
                "warning": planning.get("warning"), "plan": planning,
                "results": [], "summary": {}}
    if vas:
        wanted = {normalize_va(item) for item in vas}
        planning = dict(planning, targets=[
            item for item in planning["targets"] if item["va"] in wanted])
        planning["waves"] = [
            dict(wave, targets=[entry for entry in wave.get("targets", [])
                                if entry["va"] in wanted])
            for wave in planning.get("waves", [])
        ]
        planning["summary"] = dict(planning.get("summary", {}),
                                   selected=len(wanted))
    by_va = {item["va"]: item for item in planning["targets"]}
    if dry_run:
        return {"$schema": RUN_SCHEMA, "status": "ok", "dry_run": True,
                "plan": planning, "results": [], "summary": {"planned": len(by_va)}}

    started = time.time()
    results = []
    completed = set()
    iterations = 0
    # The plan is computed once, but dispatchability is re-evaluated after
    # every wave. A dependent that was ``deferred`` because it calls an
    # un-reconstructed callee becomes eligible the moment that callee lands, so
    # the wave boundary has to be live -- otherwise the scheduler would compute
    # the ordering and then never act on it.
    pending = list(planning.get("waves", []))
    dispatched = set()
    errors = []

    def ready_entries():
        # type: () -> list
        """Wave entries whose prerequisites are all in ``completed``.

        A target that was ``deferred`` at plan time is promoted here once its
        open callees have landed. Promotion only puts it in front of ``claim``,
        which is still the authority: if the row turns out to be blocked,
        claimed or terminal, the claim refuses and the target is recorded as
        skipped rather than forced through.

        Each target is offered exactly once per run. Re-offering it would turn
        the promotion rule into a spin loop, which is precisely what the
        iteration bound exists to catch.
        """
        out = []
        for wave in pending:
            if wave.get("reason") != "ready":
                continue
            for entry in wave.get("targets") or []:
                va = entry["va"]
                if va in dispatched:
                    continue
                record = by_va.get(va)
                if record is None:
                    continue
                open_callees = record.get("open_callees") or []
                landed = all(dep in completed for dep in open_callees)
                if record.get("dispatchable") or landed:
                    out.append(entry)
        return out

    while True:
        entries = ready_entries()
        if not entries:
            break
        # A coordinated unit is one dispatch slot holding every member of the
        # SCC: mutual recursion cannot be split across workers.
        slots = {}
        for entry in entries:
            unit = entry.get("unit") or entry["va"]
            slots.setdefault(unit, []).append(entry)
            dispatched.add(entry["va"])
        units = sorted(slots.items(), key=lambda item: item[0])
        results_lock = threading.Lock()

        def dispatch(unit_key, members):
            # type: (str, list) -> list
            worker_id = "%s/%s" % (implementation, unit_key)
            local = []
            for entry in members:
                target = dict(by_va[entry["va"]])
                target["scc"] = {"id": unit_key if len(members) > 1 else None,
                                 "size": len(members),
                                 "members": [item["va"] for item in members]}
                try:
                    record = process_target(
                        root, target, worker, worker_id,
                        planning["binary_sha256"], live=live, write=write,
                        ttl=ttl, cwd=cwd, worker_env=worker_env,
                        worker_timeout=worker_timeout, allow_stale=allow_stale,
                        adjudicator_id=(adjudicators or [None])[0],
                        root_index=planning)
                except (ToolError, OSError, ValueError) as exc:
                    record = {"va": entry["va"], "status": "error",
                              "code": getattr(exc, "code", "tool_error"),
                              "message": str(exc), "events": []}
                local.append(record)
            return local

        def thread_fn(unit_key, members):
            try:
                produced = dispatch(unit_key, members)
            except Exception as exc:  # pragma: no cover - defensive
                with results_lock:
                    errors.append("%s: %s" % (unit_key, exc))
                return
            with results_lock:
                results.extend(produced)
                for record in produced:
                    if record.get("status") == "complete":
                        completed.add(record.get("va"))

        # Bounded concurrency: a fixed pool, not a thread per unit, so a wide
        # wave cannot spawn hundreds of processes against a shared DB file.
        pool = []
        for unit_key, members in units:
            while len(pool) >= max(1, int(max_workers)):
                pool.pop(0).join()
            thread = threading.Thread(target=thread_fn, args=(unit_key, members),
                                      name="openspore-%s" % unit_key)
            pool.append(thread)
            thread.start()
        for thread in pool:
            thread.join()
        iterations += 1
        if iterations >= MAX_ITERATIONS:
            raise OrchestrationBoundExceeded(
                "wave iteration bound reached",
                {"waves": iterations, "completed": len(completed)})

    # The two validation axes are counted apart, and apart from ``complete``,
    # because they are three different claims and a run summary that merges them
    # cannot be read honestly.
    #
    # ``static_validated`` is the count of targets closed on a STATIC ``PASS`` of
    # a terminal outcome -- the same condition ``reconcile`` uses to complete a
    # target, read back off the record rather than recomputed. ``complete`` is
    # defined by the queue close, which is why the two are reported separately:
    # a close that lost a race returns ``conflict`` and is not a completion.
    #
    # ``runtime_validated`` is ``validation["runtime"]["status"] == "PASS"`` and
    # nothing else, read off the per-record runtime axis the ``validate`` report
    # produced. That status is only reachable when the canonical record reports
    # ``runtime.validated > 0``, i.e. when the original process was actually
    # observed -- which has never happened here, so this count is 0 and 0 is the
    # correct answer, not a missing one. A static PASS must never be allowed to
    # contribute here: that is precisely the conflation
    # ``validation_dimension: STATIC`` exists to prevent, and letting a static
    # acceptance masquerade as an observation of the original process would be the
    # single worst lie this summary could tell. ``runtime_gated`` counts the
    # honest resting state: a gate open, nothing attempted, nothing failed.
    static_validated = sum(
        1 for item in results
        if item.get("status") == "complete"
        and item.get("validation_dimension") == "STATIC"
        and item.get("validation") == "PASS")
    runtime_validated = sum(
        1 for item in results
        if (item.get("runtime") or {}).get("status") == "PASS")
    runtime_gated = sum(
        1 for item in results
        if (item.get("runtime") or {}).get("status") == "GATED")

    summary = {
        "targets": len(results),
        "projection": projection_staleness(root),
        "complete": sum(1 for item in results if item.get("status") == "complete"),
        "review_required": sum(1 for item in results
                               if item.get("status") == "review_required"),
        "blocked": sum(1 for item in results if item.get("status") == "blocked"),
        "skipped": sum(1 for item in results if item.get("status") == "skipped"),
        "partial": sum(1 for item in results if item.get("status") == "partial"),
        # Counted apart from ``partial`` because it is not a failure of the
        # worker: the reply arrived, was adjudicated, and the disposition was a
        # retry whose next attempt needs a child session this process cannot
        # spawn. Folding it into ``partial`` would relabel a transport condition
        # as a malformed answer, which is the misreport this status exists to
        # stop -- and it is why a run can end with targets still ``queued``.
        "retry_pending": sum(1 for item in results
                             if item.get("status") == "retry_pending"),
        "error": sum(1 for item in results if item.get("status") == "error"),
        "static_validated": static_validated,
        "runtime_validated": runtime_validated,
        "runtime_gated": runtime_gated,
        "waves": iterations,
        "seconds": round(time.time() - started, 3),
        "implementer_id": implementation,
        # Which reply channel this run used, and why. A run that cannot answer
        # that cannot explain a malformed reply, so it is reported at the same
        # level as the counts it explains. ``route`` is present only for a
        # worker the CLI built from an operator's ``--worker`` argv.
        "worker_channel": getattr(worker, "channel", CHANNEL_CUSTOM),
        "worker_route": getattr(worker, "route", None),
        # The transport behind ``worker_channel``, where the worker names one. A
        # child-session worker has no argv and no exit status; the summary still
        # says which transport produced it, and every ``launch`` event carries
        # the same pair, so a run's own output proves its transport.
        "worker_transport": getattr(worker, "transport", None),
        "errors": errors,
    }
    return {"$schema": RUN_SCHEMA, "status": "ok", "summary": summary,
            "plan": planning,
            "results": sorted(results, key=lambda item: str(item.get("va")))}


def command_line(targets, worker_command, implementer_id, cwd=None, env=None,
                 timeout=3600):
    # type: (list, list, str, object, object, int) -> object
    """A worker adapter that shells out to a fixed command per target.

    ``worker_command`` is an argv list, passed through verbatim. The briefing
    goes in on stdin as one JSON document; the reply is read from stdout. No
    shell, no interpolation. This is the documented escape hatch for an
    arbitrary worker, and it is deliberately *not* the route production takes
    for opencode -- see ``worker_adapter``.
    """
    state = {"cwd": cwd, "env": env, "timeout": timeout}

    def invoke(package):
        raw, detail = _run_once(lambda _package: list(worker_command), package,
                                state["cwd"], state["env"], state["timeout"])
        detail["channel"] = CHANNEL_ARGV
        return raw, detail
    invoke.configure_launch = _configurer(state)
    invoke.channel = CHANNEL_ARGV
    return invoke


# --------------------------------------------------------------------------- #
# worker routing: which channel an operator's --worker argv gets
# --------------------------------------------------------------------------- #
WORKER_CHANNELS = ("auto", "jsonl", "argv")


def _names_opencode(worker_argv):
    # type: (list) -> bool
    """True when argv[0] is the opencode CLI, by base name.

    Base name, not equality: an absolute path, a relative one and the
    ``.exe`` form are the same tool, and an operator who spells out the full
    path must not silently fall out of the deterministic channel.
    """
    if not worker_argv:
        return False
    name = os.path.basename(str(worker_argv[0]))
    return name in ("opencode", "opencode.exe")


def _has_format_flag(worker_argv):
    # type: (list) -> bool
    """True when the operator already chose an output channel themselves."""
    for item in worker_argv[1:]:
        text = str(item)
        if text == "--format" or text.startswith("--format="):
            return True
    return False


def _opencode_passthrough(worker_argv):
    # type: (list) -> list
    """The operator's own opencode flags, minus the subcommand and the prompt.

    Routing through the adapter must not silently drop the flags an operator
    typed -- ``--agent``, ``--model``, ``--thinking``, ``--pure`` are exactly the
    ones a fleet varies per target. The subcommand is dropped because
    ``agent_argv`` already emits ``run``, and everything before the first flag is
    dropped because that is the operator's prompt positionals, which the adapter
    replaces with the briefing digest: keeping them would put a second
    instruction in front of the model.
    ``agent_argv`` already emits the ``--print-logs`` and ``--format`` flags, so
    those are dropped from the passthrough rather than duplicated: the argv the
    adapter produces has to be exactly the documented one, plus only what the
    operator added.
    """
    tail = [str(item) for item in worker_argv[1:]]
    if tail and tail[0] == "run":
        tail = tail[1:]
    for index, item in enumerate(tail):
        if item.startswith("-"):
            tail = tail[index:]
            break
    else:
        return []
    return [item for item in tail
            if item != "--print-logs" and not item.startswith("--format")]


def opencode_route(worker_argv, mode="auto"):
    # type: (list, str) -> dict
    """Decide which adapter an operator's ``--worker`` argv gets, and say why.

    The decision table, in full:

    ==================  ==============  =====================================
    ``argv[0]``         explicit        route
    ==================  ==============  =====================================
    opencode            no ``--format``  ``opencode_worker``, forced JSONL
    opencode            ``--format``     ``command_line``, verbatim
    anything else       no ``--format``  ``command_line``, verbatim
    anything else       ``--format``     ``command_line``, verbatim
    ==================  ==============  =====================================

    ``mode`` moves the whole table: ``argv`` pins the last three rows for every
    command (the escape hatch), and ``jsonl`` demands the first row for every
    command, which is an error for a command that is not opencode because that
    command cannot provide the channel.

    The rule exists because production was running the wrong adapter:
    ``command_line`` passes the operator's argv through verbatim, and the
    documented invocation carried no ``--format``, so every production worker
    ran ``--format default``, which concatenates all assistant text into one
    stdout blob. An explicit ``--format`` means the operator has already made
    this decision, and the parser accepts either channel, so it is honoured.
    """
    if mode not in WORKER_CHANNELS:
        raise ToolError("worker_channel_invalid",
                        "worker channel must be one of %s, not %r"
                        % (", ".join(WORKER_CHANNELS), mode), 2)
    worker_argv = [str(item) for item in (worker_argv or [])]
    names_opencode = _names_opencode(worker_argv)
    explicit_format = _has_format_flag(worker_argv)
    if mode == "argv":
        return {"channel": CHANNEL_ARGV, "mode": mode, "command": None,
                "opencode": names_opencode, "explicit_format": explicit_format,
                "passthrough": worker_argv, "extra_argv": [],
                "reason": "operator pinned the verbatim argv channel"}
    if mode == "jsonl" and not names_opencode:
        raise ToolError("worker_channel_unsupported",
                        "the jsonl worker channel requires an opencode command, "
                        "not %r" % (worker_argv[0] if worker_argv else "",), 2)
    if not names_opencode:
        return {"channel": CHANNEL_ARGV, "mode": mode, "command": None,
                "opencode": False, "explicit_format": explicit_format,
                "passthrough": worker_argv, "extra_argv": [],
                "reason": "not an opencode command; verbatim argv is the "
                          "documented escape hatch"}
    if explicit_format:
        return {"channel": CHANNEL_ARGV, "mode": mode,
                "command": worker_argv[0], "opencode": True,
                "explicit_format": True, "passthrough": worker_argv,
                "extra_argv": [],
                "reason": "operator chose the output channel with --format"}
    return {"channel": CHANNEL_JSONL, "mode": mode, "command": worker_argv[0],
            "opencode": True, "explicit_format": False,
            "passthrough": worker_argv,
            "extra_argv": _opencode_passthrough(worker_argv),
            "reason": "opencode without --format: forced --format json, the "
                      "deterministic event stream"}


def worker_adapter(worker_argv, implementer_id=None, mode="auto", cwd=None,
                   env=None, timeout=3600):
    # type: (list, object, str, object, object, int) -> object
    """Build the worker for an operator ``--worker`` argv, per ``opencode_route``.

    Returns the callable the run dispatches, with ``channel`` and ``route``
    attached so the run summary can report the choice instead of leaving a
    dogfood run to be inferred from the shape of a failure.
    """
    route = opencode_route(worker_argv, mode=mode)
    if route["channel"] == CHANNEL_JSONL:
        worker = opencode_worker(command=route["command"],
                                 extra_argv=route["extra_argv"],
                                 cwd=cwd, env=env, timeout=timeout)
    else:
        worker = command_line(None, list(route["passthrough"]),
                              implementer_id, cwd=cwd, env=env, timeout=timeout)
    worker.route = route
    return worker
