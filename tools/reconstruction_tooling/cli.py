import argparse
import json
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
from .recover import recover
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

    swarm_parser = _common(sub.add_parser("swarm", help="produce a dependency-aware work queue"))
    swarm_parser.add_argument("--limit", type=int, default=20)
    swarm_parser.add_argument("--out")

    orchestrate_parser = _common(sub.add_parser(
        "orchestrate",
        help="plan or run the claim-aware reconstruction pipeline"))
    orchestrate_parser.add_argument("action", choices=("plan", "run", "brief",
                                                       "reclaim", "reap"))
    orchestrate_parser.add_argument("va", nargs="?")
    orchestrate_parser.add_argument("--limit", type=int, default=20)
    orchestrate_parser.add_argument("--worker", help="argv of the worker command; the briefing arrives on stdin")
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
        worker = orch.command_line(None, argv, args.worker_id, cwd=ROOT,
                                   timeout=args.timeout)
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


def main(argv=None):
    parser = _parser()
    args = parser.parse_args(argv)
    as_json = _json_mode(args)
    try:
        if args.command in ("frontier", "validate", "integrate", "swarm",
                            "orchestrate", "claim", "release",
                            "worker-template", "coverage") and getattr(args, "live", False):
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
        if isinstance(result, dict) and result.get("status") == "blocked":
            envelope["code"] = "blocked"
            envelope["message"] = result.get("warning", "operation is blocked")
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
