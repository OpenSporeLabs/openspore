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
   counted and released, never guessed at.
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
   checkpoint explains what happened.
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
                     sha256_json)
from .recover import recover
from . import swarm as swarm_mod
from .validate import validate

PLAN_SCHEMA = "openspore-orchestration-plan-1"
RUN_SCHEMA = "openspore-orchestration-run-1"

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
    # are the continuation of the batch, not part of it.
    capped = [item for item in considered if item["va"] in dispatchable]
    rest = [item for item in considered if item["va"] not in dispatchable]
    capped = sorted(capped, key=lambda item: (-item["priority"], item["va"]))
    rest = sorted(rest, key=lambda item: (-item["priority"], item["va"]))
    targets = capped[:max(0, int(limit))] + rest

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
# worker launching
# --------------------------------------------------------------------------- #
def agent_argv(briefing, command="opencode", model=None, output_format="json",
               attach=None):
    # type: (dict, str, object, str, object) -> list
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
    a prompt placed last would be read as a filename.
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
    except (OSError, ValueError, TypeError) as exc:
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

    One collection per target. The pack built here is threaded straight into
    ``validate`` instead of letting the validator re-collect its own: a second
    collection silently drops ``live``, so the validator used to adjudicate
    ABI-adjacent claims against a pack with no disassembly and no live function
    in it while the briefing it was judging quoted one. Re-collecting also
    doubled the Ghidra round trips and produced two packs that could not be
    compared by digest.
    """
    evidence = collect(root=root, va=va, live=live, write=write)
    context = build_context(root=root, va=va, evidence=evidence, live=live,
                            write=write)
    try:
        validation = validate(root=root, va=va, evidence=evidence,
                              context=context, write=False)
    except ToolError:
        validation = {"status": "NOT_AVAILABLE", "checks": {}}
    return {"evidence": evidence, "context": context, "validation": validation}


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


def process_target(root, target, worker, implementer_id, binary_sha256,
                   live=False, write=False, ttl=LEASE_TTL, cwd=None,
                   worker_env=None, worker_timeout=3600, allow_stale=False,
                   adjudicator_id=None, iterations=None, budget=None,
                   root_index=None):
    # type: (...) -> dict
    """Run one target through the whole lifecycle. Returns a traceable record.

    Safe to call concurrently for *different* targets: every mutation is a
    compare-and-set on that target's own queue row, so two workers never
    contend on the same row unless they raced for the same claim, and that
    race is resolved by ``claim`` returning ``already_claimed`` to the loser.
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
    previous = None
    stop = None
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
        events.append({"op": "launch", "seconds": round(elapsed, 3),
                       "returncode": launch_detail.get("returncode"),
                       "timed_out": launch_detail.get("timed_out")})
        if launch_detail.get("timed_out"):
            parsed = {"accepted": False, "code": "worker_timeout",
                      "reason": "worker exceeded its time budget"}
            raw = None
        else:
            parsed = ingest(raw, va, inv_id)
        if not parsed.get("accepted"):
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

        # Record the evidence before the lease ends.
        q.checkpoint(inv_id, implementer_id,
                     payload={"stage": "VALIDATE", "outcome": outcome,
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
                                  package["content_sha256"]},
                     stage="VALIDATE", attempts=attempts,
                     evidence_refs=sorted(evidence_refs),
                     adjudicator_id=adjudicator_id)
        events.append({"op": "checkpoint", "stage": "VALIDATE",
                       "attempts": attempts})

        if decision["action"] == "complete":
            closed = q.close(inv_id, implementer_id, disposition="done",
                             binary_sha256=binary_sha256)
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
                        "attempts": attempts, "source_files": source_files,
                        "events": events}
            return {"va": va, "queue_id": inv_id, "status": "complete",
                    "code": decision["code"], "outcome": outcome,
                    "validation": verdict, "validation_dimension": "STATIC",
                    "runtime": {"status": runtime.get("status"),
                                "gated": bool(runtime.get("gated")),
                                "gates": runtime.get("gates") or []},
                    "attempts": attempts,
                    "source_files": source_files, "events": events}
        if decision["action"] == "review":
            released = q.release(inv_id, implementer_id, to="blocked",
                                 reason=decision["code"])
            events.append({"op": "release", "to": "blocked",
                           "why": decision["code"]})
            return {"va": va, "queue_id": inv_id, "status": "review_required",
                    "code": decision["code"], "outcome": outcome,
                    "validation": verdict, "attempts": attempts,
                    "source_files": source_files, "events": events}
        if decision["action"] == "block":
            released = q.release(inv_id, implementer_id, to="blocked",
                                 reason="blocked")
            events.append({"op": "release", "to": "blocked", "why": "blocked"})
            return {"va": va, "queue_id": inv_id, "status": "blocked",
                    "code": "blocked", "outcome": outcome,
                    "validation": verdict, "attempts": attempts,
                    "events": events}
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
    events.append({"op": "release", "to": "blocked", "why": reason})
    return {"va": va, "queue_id": inv_id, "status": "blocked",
            "code": reason, "attempts": attempts, "events": events}


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
    def invoke(package):
        return _run_once(argv_builder, package, cwd, env, timeout)
    return invoke


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
                                                   "timed_out": False}
    return invoke


def run(root=ROOT, limit=20, worker=None, implementer_id=None, live=False,
        write=False, max_workers=4, ttl=LEASE_TTL, cwd=None, worker_env=None,
        worker_timeout=3600, allow_stale=False, adjudicators=None,
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
    """
    if worker is None:
        raise ToolError("worker_required",
                        "run() needs a worker; pass a callable or a subprocess "
                        "launcher (orchestration is never launched implicitly)", 2)
    implementation = implementer_id or "orchestrator-%d" % os.getpid()
    planning = plan(root=root, limit=limit)
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

    summary = {
        "targets": len(results),
        "projection": projection_staleness(root),
        "complete": sum(1 for item in results if item.get("status") == "complete"),
        "review_required": sum(1 for item in results
                               if item.get("status") == "review_required"),
        "blocked": sum(1 for item in results if item.get("status") == "blocked"),
        "skipped": sum(1 for item in results if item.get("status") == "skipped"),
        "partial": sum(1 for item in results if item.get("status") == "partial"),
        "error": sum(1 for item in results if item.get("status") == "error"),
        "waves": iterations,
        "seconds": round(time.time() - started, 3),
        "implementer_id": implementation,
        "errors": errors,
    }
    return {"$schema": RUN_SCHEMA, "status": "ok", "summary": summary,
            "plan": planning,
            "results": sorted(results, key=lambda item: str(item.get("va")))}


def command_line(targets, worker_command, implementer_id, cwd=None, env=None,
                 timeout=3600):
    # type: (list, list, str, object, object, int) -> object
    """A worker adapter that shells out to a fixed command per target.

    ``worker_command`` is an argv list. The briefing goes in on stdin as one
    JSON document; the reply is read from stdout. No shell, no interpolation.
    """
    def invoke(package):
        return _run_once(lambda _package: list(worker_command), package,
                         cwd, env, timeout)
    return invoke
