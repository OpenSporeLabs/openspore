import argparse
import json
import os
import shlex
import sys

from . import orchestrate as orch
from . import queue as q
from . import worker_contract as wc
from .context import build as build_context
from .coverage import coverage
from .evidence import collect
from .frontier import frontier
from .integrate import apply as integrate_apply
from .integrate import check as integrate_check
from .integrate import status as integrate_status
from .models import ROOT, ToolError, canonical_json, normalize_va
from .ownership import apply as ownership_apply
from .ownership import inventory as ownership_inventory
from .ownership import resolve as ownership_resolve
from .promote import apply as promote_apply
from .promote import plan as promote_plan
from .recover import recover
from .satisfy import apply as satisfy_apply
from .satisfy import plan as satisfy_plan
from .swarm import swarm
from .validate import validate


def _common(parser):
    parser.add_argument("--format", choices=("human", "json"), default=argparse.SUPPRESS)
    parser.add_argument("--json", action="store_true", default=argparse.SUPPRESS)
    parser.add_argument("--live", action="store_true", default=argparse.SUPPRESS)
    parser.add_argument("--no-write", action="store_true", default=argparse.SUPPRESS)
    return parser


def _parser():
    parser = argparse.ArgumentParser(prog="openspore", description="OpenSpore reconstruction tooling")
    parser.add_argument("--format", choices=("human", "json"), default="human")
    parser.add_argument("--json", action="store_true")
    sub = parser.add_subparsers(dest="command", required=True)
    frontier_parser = _common(sub.add_parser("frontier", help="rank current reconstruction targets"))
    frontier_parser.add_argument("--package")
    frontier_parser.add_argument("--subsystem")
    frontier_parser.add_argument("--status")
    frontier_parser.add_argument("--semantic")
    frontier_parser.add_argument("--dependency", choices=("any", "ready", "open"), default="any")
    frontier_parser.add_argument("--runtime", choices=("required", "none"))
    frontier_parser.add_argument("--claimed", action=argparse.BooleanOptionalAction, default=None)
    frontier_parser.add_argument("--unclaimed", action="store_true")
    frontier_parser.add_argument("--gameplay")
    frontier_parser.add_argument("--limit", type=int, default=20)
    frontier_parser.add_argument("--offset", type=int, default=0)

    evidence_parser = _common(sub.add_parser("evidence", help="collect a deterministic evidence pack"))
    evidence_parser.add_argument("va")

    context_parser = _common(sub.add_parser("context", help="build an agent-ready context brief"))
    context_parser.add_argument("va")

    recover_parser = _common(sub.add_parser("recover", help="collect evidence, context, and validation"))
    recover_parser.add_argument("va")

    validate_parser = _common(sub.add_parser("validate", help="validate a reconstruction against available evidence"))
    validate_parser.add_argument("va")

    integrate = sub.add_parser("integrate", help="check or apply generated reconstruction projections")
    integrate.add_argument("action", choices=("status", "check", "apply"))
    integrate.add_argument("--format", choices=("human", "json"), default=argparse.SUPPRESS)
    integrate.add_argument("--json", action="store_true", default=argparse.SUPPRESS)

    promote_parser = _common(sub.add_parser(
        "promote", help="plan or apply promotion of validated staging packages into src/"))
    promote_parser.add_argument("action", choices=("plan", "apply"))
    promote_parser.add_argument("package", help="dashed or underscored package name")
    promote_parser.add_argument("--va", action="append", dest="vas",
                               help="restrict to these VAs (repeatable)")
    promote_parser.add_argument("--overwrite", action="store_true",
                                help="apply over a drifted installed package")
    promote_parser.add_argument("--no-build", action="store_true",
                                help="skip the compile step of the gate")
    promote_parser.add_argument("--no-ctest", action="store_true",
                                help="skip the ctest step of the gate")
    promote_parser.add_argument("--rebuild", action="store_true",
                                help="re-gate a package that is already promoted and identical")
    promote_parser.add_argument("--out")

    satisfy_parser = _common(sub.add_parser(
        "satisfy",
        help="plan or apply the dependency-promotion of a promoted package"))
    satisfy_parser.add_argument("action", choices=("plan", "apply"))
    satisfy_parser.add_argument("vas", nargs="*", metavar="va",
                                help="target VAs; all promoted VAs when omitted")
    satisfy_parser.add_argument("--va", action="append", dest="flags",
                                help="target a VA by flag instead (repeatable)")
    satisfy_parser.add_argument("--reason", help="recorded in the manifest change_log")
    satisfy_parser.add_argument("--verify-build", action="store_true",
                                help="re-run build_gate on the installed package instead of "
                                     "trusting the recorded verdict")
    satisfy_parser.add_argument("--dry-run", action="store_true",
                                help="report the decision without writing the manifest")
    satisfy_parser.add_argument("--out")

    swarm_parser = _common(sub.add_parser("swarm", help="produce a dependency-aware work queue"))
    swarm_parser.add_argument("--limit", type=int, default=20)
    swarm_parser.add_argument("--out")

    orchestrate_parser = _common(sub.add_parser(
        "orchestrate",
        help="plan or run the claim-aware reconstruction pipeline"))
    orchestrate_parser.add_argument("action", choices=("plan", "run", "brief",
                                                       "session-plan",
                                                       "session-task",
                                                       "session-run",
                                                       "reclaim", "reap"))
    orchestrate_parser.add_argument("va", nargs="?")
    orchestrate_parser.add_argument("--limit", type=int, default=20)
    orchestrate_parser.add_argument("--worker", help="argv of the worker command; the briefing arrives on stdin")
    orchestrate_parser.add_argument(
        "--worker-channel", choices=orch.WORKER_CHANNELS, default=argparse.SUPPRESS,
        help="which reply channel a --worker runs in: auto routes an opencode "
             "command through the deterministic JSONL stream, jsonl demands it, "
             "argv is the verbatim escape hatch (env: OPENSPORE_WORKER_CHANNEL)")
    orchestrate_parser.add_argument("--worker-id",
                                    help="lease holder identity (required for run)")
    orchestrate_parser.add_argument("--max-workers", type=int, default=4)
    orchestrate_parser.add_argument("--ttl", type=int, default=orch.LEASE_TTL)
    orchestrate_parser.add_argument("--timeout", type=int, default=3600)
    orchestrate_parser.add_argument("--allow-stale", action="store_true")
    orchestrate_parser.add_argument("--dry-run", action="store_true")
    orchestrate_parser.add_argument("--attempt", type=int, default=1)
    orchestrate_parser.add_argument("--va", action="append", dest="vas",
                                    help="restrict the run to these targets (repeatable)")
    orchestrate_parser.add_argument("--out")
    # The child-session verbs. ``--replies`` is the reply directory the
    # orchestrating agent session wrote its children's final messages into, and
    # ``--include-deferred`` exists so the deferred half of a plan -- the
    # continuation of the batch -- is reachable from the command line and not
    # only from the module.
    orchestrate_parser.add_argument(
        "--replies",
        help="directory of <va8>.txt child-session replies (session-run)")
    orchestrate_parser.add_argument(
        "--include-deferred", action="store_true",
        default=argparse.SUPPRESS,
        help="session-plan: also schedule targets the frontier deferred")

    claim_parser = _common(sub.add_parser(
        "claim", help="atomically lease a target through the canonical queue"))
    claim_parser.add_argument("va")
    claim_parser.add_argument("--worker-id", required=True)
    claim_parser.add_argument("--ttl", type=int, default=q.DEFAULT_TTL)
    claim_parser.add_argument("--allow-stale", action="store_true")
    claim_parser.add_argument("--allow-blocked", action="store_true")

    release_parser = _common(sub.add_parser(
        "release", help="end a lease without ending the investigation"))
    release_parser.add_argument("va")
    release_parser.add_argument("--worker-id", required=True)
    release_parser.add_argument("--to", choices=("queued", "blocked"),
                                default="queued")
    release_parser.add_argument("--reason")

    template_parser = _common(sub.add_parser(
        "worker-template", help="print the worker result contract skeleton"))
    template_parser.add_argument("va")
    template_parser.add_argument("--worker-id")

    ownership_parser = _common(sub.add_parser(
        "ownership",
        help="inventory or reconcile duplicate VA ownership across packages"))
    ownership_parser.add_argument("action", choices=("plan", "inventory", "apply", "resolve"))
    ownership_parser.add_argument("vas", nargs="*", metavar="va",
                                  help="restrict to these VAs (repeatable or positional)")
    ownership_parser.add_argument("--va", action="append", dest="flags",
                                  help="target a VA by flag instead (repeatable)")
    ownership_parser.add_argument("--out")

    coverage_parser = _common(sub.add_parser("coverage", help="report deterministic reconstruction coverage (read-only)"))
    coverage_parser.add_argument("--gameplay", action="store_true", help="restrict the matrix to the gameplay universe")
    coverage_parser.add_argument("--history", action="store_true", help="include the recoverable history checkpoints")
    coverage_parser.add_argument("--no-local-db", action="store_true", help="skip the gitignored machine-local SQLite inputs")
    coverage_parser.add_argument("--markdown", action="store_true", help="render the markdown report instead of JSON")
    coverage_parser.add_argument("--out", help="write the report to this path (explicit opt-in write)")
    return parser


def _json_mode(args):
    return bool(getattr(args, "json", False) or getattr(args, "format", None) == "json")


def _envelope(command, result, live=False):
    return {
        "$schema": "openspore-cli-result-1",
        "command": command,
        "status": "ok" if not isinstance(result, dict) or result.get("status") not in ("error", "FAIL", "blocked") else "error",
        "ok": not isinstance(result, dict) or result.get("status") not in ("error", "FAIL", "blocked"),
        "source": {"requested": "live" if live else "persisted", "live": bool(live), "mode": result.get("evidence_state", "persisted") if isinstance(result, dict) else "persisted"},
        "result": result,
        "warnings": [],
        "changed": bool(result.get("changed", False)) if isinstance(result, dict) else False,
        "idempotent": True,
    }


def _print_envelope(envelope, as_json):
    if as_json:
        sys.stdout.write(canonical_json(envelope))
        return
    if not envelope.get("ok", True):
        print("error %s: %s" % (envelope.get("code", "tool_error"), envelope.get("message", "tool failed")))
        return
    result = envelope.get("result", {})
    command = envelope.get("command")
    if command == "frontier":
        for target in result.get("targets", []):
            reasons = ", ".join(item.get("code", "") for item in target.get("reasons", []))
            print("%s  score=%s  %s  %s" % (target.get("va"), target.get("score"), target.get("disposition"), reasons))
        print("total=%s shown=%s" % (result.get("total"), result.get("count")))
    elif command in ("evidence", "context", "recover", "validate"):
        print("target=%s status=%s" % (result.get("target", result.get("va", "unknown")), result.get("validation_status", result.get("status", "ok"))))
        for key in ("paths", "evidence", "context", "validation", "workflow"):
            if key in result:
                print("%s=%s" % (key, json.dumps(result[key], sort_keys=True)))
    elif command == "orchestrate":
        _print_orchestrate(result)
    elif command == "coverage":
        if "markdown" in result:
            print(result["markdown"])
        else:
            universes = result.get("universes") or {}
            print("universes: internal=%s gameplay=%s non_gameplay=%s"
                  % (universes.get("internal_functions"), universes.get("gameplay_functions"),
                     universes.get("non_gameplay_functions")))
            for record in result.get("dimensions") or []:
                def cell(value):
                    return "-" if value is None else str(value)
                print("  %-48s covered=%-7s universe=%-7s pct=%-9s gameplay=%-7s %s"
                      % (record.get("id"), cell(record.get("covered")),
                         cell(record.get("universe")), cell(record.get("pct")),
                         cell(record.get("gameplay_covered")),
                         record.get("provenance") if record.get("available") else "unavailable"))
            for item in result.get("cannot_determine") or []:
                print("cannot_determine: %s - %s" % (item.get("metric"), item.get("reason")))
            print("note: these dimensions are deliberately NOT summed; there is no overall percentage")
    else:
        print(json.dumps(result, indent=2, sort_keys=True, ensure_ascii=False))


def _print_orchestrate(result):
    """Human rendering for ``orchestrate``, one shape per document.

    The verb is recovered from the result rather than from ``argv``: every
    document this CLI produces carries its own ``$schema``, and reading it back
    means a new verb gets a human rendering without this function being told
    what it is printing. Anything it does not recognise falls through to the
    generic JSON dump, which is what ``plan``, ``brief``, ``reap`` and
    ``reclaim`` have always rendered as and what they must keep rendering as.
    """
    schema = str(result.get("$schema") or "")
    if schema.startswith("openspore-orchestration-session-plan"):
        _print_session_plan(result)
        return
    if schema.startswith("openspore-orchestration-session-task"):
        _print_session_task(result)
        return
    if schema == orch.RUN_SCHEMA or isinstance(result.get("results"), list):
        _print_run_summary(result)
        return
    print(json.dumps(result, indent=2, sort_keys=True, ensure_ascii=False))


def _print_session_plan(result):
    counts = result.get("counts") or {}
    print("selected=%s eligible=%s deferred=%s excluded=%s transport=%s"
          % (result.get("selected"), counts.get("eligible"),
             counts.get("deferred"), counts.get("excluded"),
             (result.get("transport") or {}).get("channel")))
    for target in result.get("targets") or []:
        evidence = target.get("expected_static_evidence") or {}
        print("%s  %-12s %-10s dispatchable=%-5s pack=%-8s listing=%-5s span=%-5s  %s"
              % (target.get("va"), target.get("role"),
                 target.get("package") or "-", target.get("dispatchable"),
                 (evidence.get("evidence_pack") or {}).get("state"),
                 (evidence.get("listing") or {}).get("available"),
                 (evidence.get("source_span") or {}).get("resolved"),
                 target.get("name") or ""))
    for va in result.get("requested_absent") or []:
        print("not in this plan: %s" % va)


def _print_session_task(result):
    print("va=%s queue_id=%s name=%s" % (result.get("va"), result.get("queue_id"),
                                         result.get("name")))
    print("write_under=%s" % result.get("write_under"))
    print("metadata_sidecar=%s" % result.get("metadata_sidecar"))
    print("attempt=%s of %s  claimed=%s" % (result.get("attempt"),
                                            result.get("max_attempts"),
                                            result.get("claim_taken")))
    print("briefing_sha256=%s"
          % ((result.get("briefing") or {}).get("content_sha256")))
    print("")
    print(result.get("prompt_markdown") or "")
    print("")
    print("## Reply format")
    print("")
    for name, value in sorted((result.get("reply_format") or {}).items()):
        print("- %s: %s" % (name, value))


def _print_run_summary(result):
    summary = result.get("summary") or {}
    if result.get("dry_run"):
        # A dry run has no channel, no counts and no lease; its only fact is how
        # many targets it would have dispatched, and saying that is the whole
        # point of the flag.
        print("dry_run: planned=%s (no lease was taken)"
              % summary.get("planned"))
        return
    print("targets=%s complete=%s static_validated=%s runtime_validated=%s "
          "runtime_gated=%s review=%s blocked=%s skipped=%s partial=%s error=%s"
          % (summary.get("targets"), summary.get("complete"),
             summary.get("static_validated"), summary.get("runtime_validated"),
             summary.get("runtime_gated"), summary.get("review_required"),
             summary.get("blocked"), summary.get("skipped"),
             summary.get("partial"), summary.get("error")))
    print("channel=%s transport=%s waves=%s implementer=%s"
          % (summary.get("worker_channel"), summary.get("worker_transport"),
             summary.get("waves"), summary.get("implementer_id")))
    for record in result.get("results") or []:
        print("  %s  %-14s %-24s static=%-14s runtime=%-6s %s"
              % (record.get("va"), record.get("status"), record.get("code"),
                 record.get("static_validation"), record.get("runtime_status"),
                 record.get("message") or ""))


def _result_or_raise(result, code):
    if not isinstance(result, dict):
        raise ToolError(code, "queue operation returned a non-mapping result", 1)
    if result.get("status") == "error":
        raise ToolError(result.get("code", code),
                        result.get("message", "queue operation failed"), 1,
                        result)
    return result


def _resolve(va):
    """Normalize a VA and find its canonical queue row (inserting if needed)."""
    bare = normalize_va(va)[2:]
    found = q.get(va=bare)
    if q.ok(found):
        return bare, found["investigation"]
    planning = orch.plan(limit=1)
    return bare, None


def _worker_channel(args):
    """Resolve the worker channel: the flag, then the environment, then ``auto``.

    ``--worker-channel`` and ``OPENSPORE_WORKER_CHANNEL`` exist because the
    routing is a correctness decision (which channel a worker answers in) and
    one caller cannot fix it for the rest. An environment value is honoured
    because a fleet cannot pass a flag to every process, and it is validated
    here rather than trusted, so a typo fails loudly instead of silently
    disabling the deterministic channel.
    """
    chosen = getattr(args, "worker_channel", None) or \
        os.environ.get("OPENSPORE_WORKER_CHANNEL") or "auto"
    if chosen not in orch.WORKER_CHANNELS:
        raise ToolError("worker_channel_invalid",
                        "worker channel must be one of %s, not %r"
                        % (", ".join(orch.WORKER_CHANNELS), chosen), 2)
    return chosen


def _plan_target(va, planning=None):
    """The classified plan record for one VA, or a synthesised stand-in.

    ``session_task`` briefs any VA, not only one the plan schedules -- a human
    re-briefing one row, or a follow-up on a closed target, must not be refused by
    a scheduler. So a target the plan does not carry becomes the record shape
    ``brief`` already tolerates rather than an error, and the task document says
    which of the two it was.
    """
    bare = normalize_va(va)[2:]
    planning = planning if planning is not None else orch.plan(limit=200)
    found = next((item for item in planning.get("targets") or []
                  if item.get("queue_va") == bare or item.get("va") == bare), None)
    if found is not None:
        return found, True
    return {"va": normalize_va(va), "queue_va": bare, "queue_id": None,
            "queue_row": None, "name": None, "subsystem": None, "cluster": None,
            "role": None, "reason": "not_in_plan", "score": 0,
            "dispatchable": False, "claim_state": None,
            "scc": {"id": None, "size": 1, "members": [normalize_va(va)]},
            "open_callees": []}, False


def _session_task(args):
    """``orchestrate session-task <va>`` -- one child's whole brief.

    Deliberately a read: no lease is taken and no queue row is inserted, so the
    document can be built and handed to a child session before anything is owned.
    The claim happens in ``process_target``, and this is what an operator can read
    to see what that will look like.
    """
    if not args.worker_id:
        raise ToolError("worker_id_required",
                        "orchestrate session-task needs --worker-id so the child "
                        "knows whose lease the result will be recorded under", 2)
    return orch.session_task(ROOT, _plan_target(args.va, orch.plan(limit=200))[0],
                             args.worker_id, live=False, write=False,
                             attempt=args.attempt)


def _session_run(args):
    """``orchestrate session-run --replies <dir>`` -- the whole lifecycle.

    One command drives a batch of native child sessions: the same ``run`` every
    other transport uses, with the child-session adapter in place of a launcher.
    Nothing about the disposition changes, which is the point -- a child session
    is held to the same result contract, the same bounds and the same
    compare-and-set as a subprocess worker.
    """
    if not args.replies:
        raise ToolError("replies_required",
                        "orchestrate session-run needs --replies <dir> holding "
                        "one <va8>.txt per child session's final message", 2)
    if not args.worker_id:
        raise ToolError("worker_id_required",
                        "orchestrate session-run needs --worker-id: it is the "
                        "lease holder identity and there is no default that could "
                        "be honest about which session owns the row", 2)
    if not os.path.isdir(args.replies):
        raise ToolError("replies_not_a_directory",
                        "--replies %r is not a directory" % (args.replies,), 2)
    worker = orch.session_result_worker(reply_dir=args.replies)
    return orch.run(ROOT, limit=args.limit, worker=worker,
                    implementer_id=args.worker_id, write=False,
                    max_workers=args.max_workers, ttl=args.ttl,
                    worker_timeout=args.timeout,
                    allow_stale=args.allow_stale, dry_run=args.dry_run,
                    vas=args.vas)


def _orchestrate(args, as_json):
    action = args.action
    if action == "plan":
        result = orch.plan(limit=args.limit)
    elif action == "brief":
        bare, row = _resolve(args.va)
        planning = orch.plan(limit=200)
        target = next((item for item in planning["targets"]
                       if item["queue_va"] == bare), None)
        if target is None:
            raise ToolError("target_not_in_plan",
                            "%s is not a dispatchable frontier target" % args.va, 2)
        if row is None:
            row = q.ensure_row(bare, name=target.get("name"),
                               subsystem=target.get("subsystem"),
                               binary_sha256=planning["binary_sha256"])
        if row.get("investigation"):
            row = row["investigation"]
        inputs = orch.collect_inputs(ROOT, target["va"], live=False, write=False)
        result = orch.brief(ROOT, target, inputs, args.worker_id,
                            row.get("id"), planning["binary_sha256"],
                            attempt=args.attempt)
    elif action == "session-plan":
        result = orch.session_plan(ROOT, limit=args.limit, targets=args.vas,
                                   live=getattr(args, "live", False),
                                   include_deferred=getattr(
                                       args, "include_deferred", False))
    elif action == "session-task":
        result = _session_task(args)
    elif action == "session-run":
        result = _session_run(args)
    elif action == "reclaim":
        # Reap leases whose holder is gone. Never auto-steals a live lease: it
        # only releases rows the caller names explicitly.
        bare, row = _resolve(args.va)
        if row is None:
            raise ToolError("not_found", "no queue row for %s" % args.va, 2)
        result = _result_or_raise(
            q.claim(row["id"], args.worker_id,
                    binary_sha256=row.get("binary_sha256"),
                    ttl=args.ttl, allow_stale=args.allow_stale),
            "reclaim_failed")
    elif action == "reap":
        rows = q.list_rows(status="active", limit=1000)
        entries = []
        for row in rows:
            entries.append({
                "id": row.get("id"), "va": row.get("va"),
                "implementer_id": row.get("implementer_id"),
                "updated_at": row.get("updated_at"), "stage": row.get("stage"),
                "attempts": row.get("attempts"),
            })
        result = {"status": "ok", "active_leases": len(entries),
                  "leases": entries,
                  "note": ("report only; releasing a lease requires naming the "
                           "holder with `orchestrate reclaim --allow-stale` "
                           "or `release`")}
    else:
        if not args.worker:
            raise ToolError("worker_required",
                            "orchestrate run needs --worker <command>", 2)
        argv = shlex.split(args.worker)
        # The adapter is chosen, not assumed: an opencode command without an
        # explicit --format is routed through the deterministic JSONL channel,
        # anything else keeps the verbatim argv escape hatch. The choice is
        # reported in the run summary (``worker_channel``/``worker_route``) and
        # on every ``launch`` event, so a run proves which channel it used.
        worker = orch.worker_adapter(argv, args.worker_id,
                                     mode=_worker_channel(args),
                                     cwd=ROOT, timeout=args.timeout)
        result = orch.run(ROOT, limit=args.limit, worker=worker,
                          implementer_id=args.worker_id, write=False,
                          max_workers=args.max_workers, ttl=args.ttl,
                          worker_timeout=args.timeout,
                          allow_stale=args.allow_stale, dry_run=args.dry_run,
                          vas=args.vas)
    if args.out:
        from .models import write_json_atomic
        write_json_atomic(args.out, result)
        result = dict(result, path=str(args.out))
    return result


def _written(args, result):
    # type: (object, object) -> object
    """Honour ``--out`` the way ``orchestrate`` does: write, then name the path."""
    if not getattr(args, "out", None):
        return result
    from .models import write_json_atomic

    write_json_atomic(args.out, result)
    return dict(result, path=str(args.out))


def _one_va(values, verb):
    # type: (object, str) -> object
    """Collapse a repeatable ``--va`` list to the scalar the planner wants.

    ``argparse``'s ``action="append"`` hands the CLI a list, and the promotion
    planner is scalar-typed: ``promote._load_candidates`` calls ``_bare(va)`` ->
    ``normalize_va(va)`` on a single address, so forwarding the list failed with
    ``invalid VA: ['0x00901930']`` before any plan was built. The programmatic
    API (``promote.plan(root, package, va)``) is scalar already and stays that
    way -- only the CLI's own list is unwrapped here.

    More than one address is refused rather than quietly reduced to the last:
    the planner narrows to a single ``wanted_va``, so silently honouring one of
    several would decide a promotion on an address the caller did not name.
    A bare string is already a scalar and is passed through, not iterated.
    """
    if values is None:
        return None
    if isinstance(values, str):
        return values or None
    items = [value for value in values if value is not None]
    if not items:
        return None
    if len(items) > 1:
        raise ToolError("unsupported_option",
                        "%s narrows to one address; %d were given (%s). Pass one "
                        "--va, or run the verb once per address." % (
                            verb, len(items), ", ".join(str(v) for v in items)), 2)
    return items[0]


def _promote(args):
    # type: (object) -> object
    """``promote plan|apply <package>``; ``plan`` never touches ``src/``."""
    va = _one_va(args.vas, "promote")
    if args.action == "plan":
        return _written(args, promote_plan(ROOT, package=args.package, va=va))
    if getattr(args, "no_write", False):
        # ``promote.apply`` has no dry-run parameter and this CLI does not get to
        # add one, so guessing which verb was meant is the one option that is
        # definitely wrong: name the read-only verb instead.
        raise ToolError("unsupported_option",
                        "promote apply has no dry-run mode; use `promote plan` to "
                        "decide without writing to src/", 2)
    return _written(args, promote_apply(
        ROOT, package=args.package, va=va, overwrite=args.overwrite,
        build=not args.no_build, ctest=not args.no_ctest, rebuild=args.rebuild))


def _satisfy(args):
    # type: (object) -> object
    """``satisfy plan|apply <va>...``; VAs may also be named with ``--va``."""
    vas = list(args.vas or []) + list(args.flags or [])
    if args.action == "plan":
        return _written(args, satisfy_plan(ROOT, vas=vas or None))
    return _written(args, satisfy_apply(
        ROOT, vas=vas or None, reason=args.reason,
        dry_run=bool(args.dry_run or getattr(args, "no_write", False)),
        verify_build=args.verify_build))


def _ownership(args):
    # type: (object) -> object
    """``ownership plan|inventory|apply|resolve``; VAs may also be named with ``--va``."""
    vas = list(args.vas or []) + list(args.flags or [])
    if args.action == "inventory":
        return ownership_inventory(ROOT, vas=vas or None)
    if args.action == "apply":
        return _written(args, ownership_apply(
            ROOT, vas=vas or None, write=not getattr(args, "no_write", False)))
    if args.action == "resolve":
        if not vas:
            raise ToolError("missing_param", "ownership resolve needs at least one VA", 2)
        return {"$schema": "openspore-ownership-resolve-1", "status": "ok",
                "decisions": [ownership_resolve(ROOT, value) for value in vas]}
    return ownership_inventory(ROOT, vas=vas or None)


def main(argv=None):
    parser = _parser()
    args = parser.parse_args(argv)
    as_json = _json_mode(args)
    try:
        if args.command in ("frontier", "validate", "integrate", "swarm",
                            "orchestrate", "claim", "release", "promote", "satisfy",
                            "worker-template", "coverage", "ownership") \
                and getattr(args, "live", False):
            raise ToolError("unsupported_option", "--live is not supported for %s" % args.command, 2)
        if args.command == "frontier":
            result = frontier(ROOT, args)
        elif args.command == "evidence":
            result = collect(ROOT, args.va, live=getattr(args, "live", False), write=not getattr(args, "no_write", False))
        elif args.command == "context":
            evidence = collect(ROOT, args.va, live=getattr(args, "live", False), write=not getattr(args, "no_write", False))
            result = build_context(ROOT, args.va, evidence=evidence, live=getattr(args, "live", False), write=not getattr(args, "no_write", False))
        elif args.command == "recover":
            result = recover(ROOT, args.va, live=getattr(args, "live", False), write=not getattr(args, "no_write", False))
        elif args.command == "validate":
            result = validate(ROOT, args.va, write=not getattr(args, "no_write", False))
        elif args.command == "integrate":
            if args.action == "status":
                result = integrate_status(ROOT)
            elif args.action == "check":
                result = integrate_check(ROOT)
            else:
                result = integrate_apply(ROOT)
        elif args.command == "swarm":
            result = swarm(ROOT, limit=args.limit, out=args.out)
        elif args.command == "promote":
            result = _promote(args)
        elif args.command == "satisfy":
            result = _satisfy(args)
        elif args.command == "ownership":
            result = _ownership(args)
        elif args.command == "orchestrate":
            result = _orchestrate(args, as_json)
        elif args.command == "claim":
            bare, row = _resolve(args.va)
            planning_sha = orch.plan(limit=1).get("binary_sha256")
            if row is None:
                _result_or_raise(
                    q.ensure_row(bare, binary_sha256=planning_sha),
                    "queue_insert_failed")
                row = q.get(va=bare)["investigation"]
            result = _result_or_raise(
                q.claim(row["id"], args.worker_id,
                        binary_sha256=row.get("binary_sha256") or planning_sha,
                        ttl=args.ttl, allow_stale=args.allow_stale,
                        allow_blocked=args.allow_blocked),
                "claim_failed")
        elif args.command == "release":
            bare, row = _resolve(args.va)
            if row is None:
                raise ToolError("not_found", "no queue row for %s" % args.va, 2)
            result = _result_or_raise(
                q.release(row["id"], args.worker_id, to=args.to,
                          reason=args.reason),
                "release_failed")
        elif args.command == "worker-template":
            result = {"$schema": "openspore-worker-template-1",
                      "status": "ok",
                      "result": wc.result_template(args.va, args.worker_id),
                      "outcomes": list(wc.OUTCOMES),
                      "verdicts": list(wc.VALIDATION_VERDICTS),
                      "rules": list(wc.WORKER_RULES)}
        elif args.command == "coverage":
            result = coverage(ROOT, args)
        else:
            raise ToolError("unknown_command", "unknown command", 2)
        envelope = _envelope(args.command, result, live=getattr(args, "live", False))
        if isinstance(result, dict) and result.get("status") == "blocked" \
                and args.command in ("promote", "satisfy") \
                and getattr(args, "action", None) == "apply":
            # A refused package or VA is a verdict, not a failed command: the
            # apply adjudicated every target it was given and wrote exactly the
            # admissible ones. ``_envelope`` would report the batch as an error
            # because one row inside it says "blocked" -- the same word, two
            # meanings -- so the rule is left alone and the report is shaped
            # instead. The per-row statuses and ``refused[]`` stay exactly as
            # the engine produced them, ``ok`` names the batch outcome, and the
            # refusals are counted in a warning so they cannot be missed.
            summary = result.get("summary") or {}
            refused = int(summary.get("refused", 0))
            envelope["status"] = "ok"
            envelope["ok"] = True
            envelope.pop("code", None)
            envelope.pop("message", None)
            envelope["warnings"].append(
                "apply_ok_with_refusals: %d of %d target(s) were refused and every "
                "named target was adjudicated; read result.refused for the reason"
                % (refused, int(summary.get("requested", refused) or refused)))
        elif isinstance(result, dict) and result.get("status") == "blocked":
            envelope["code"] = "blocked"
            envelope["message"] = result.get("warning", "operation is blocked")
        elif isinstance(result, dict) and args.command == "orchestrate" \
                and args.action == "session-run":
            # A blocked *batch* is a successful command, not a failed one, and
            # ``_envelope`` would otherwise report it as an error because some
            # target inside it ended blocked -- the same word, two meanings. The
            # rule is left alone and the report is shaped instead: the per-target
            # statuses stay exactly as the lifecycle produced them, and the
            # top-level status names the batch outcome, so ``ok`` is true when
            # every target was adjudicated and false only when the run itself
            # could not be adjudicated at all.
            summary = result.get("summary") or {}
            unadjudicated = (summary.get("error", 0) + summary.get("partial", 0))
            if not summary.get("targets") and not result.get("dry_run"):
                envelope["status"] = "error"
                envelope["ok"] = False
                envelope["code"] = "no_dispatchable_targets"
                envelope["message"] = ("session-run dispatched nothing; the plan "
                                       "offered no target to this worker-id")
            elif unadjudicated:
                envelope["status"] = "error"
                envelope["ok"] = False
                envelope["code"] = "batch_not_adjudicated"
                envelope["message"] = ("%d of %d targets were not adjudicated "
                                       "(error or partial); read summary and the "
                                       "per-target events"
                                       % (unadjudicated, summary.get("targets")))
            else:
                envelope["warnings"].append(
                    "batch_ok_with_blocked_targets: %d target(s) ended blocked, "
                    "which is a per-target disposition and not a command failure"
                    % summary.get("blocked", 0))
        _print_envelope(envelope, as_json)
        return 0
    except ToolError as exc:
        envelope = {"$schema": "openspore-cli-result-1", "command": args.command, "status": "error", "ok": False, "code": exc.code, "message": exc.message, "exit_code": exc.exit_code, "result": exc.details, "warnings": []}
        _print_envelope(envelope, as_json)
        return exc.exit_code
    except (OSError, ValueError, KeyError, TypeError) as exc:
        envelope = {"$schema": "openspore-cli-result-1", "command": args.command, "status": "error", "ok": False, "code": "tool_error", "message": str(exc), "exit_code": 1, "result": {}, "warnings": []}
        _print_envelope(envelope, as_json)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
