"""Claim-aware adapter over the canonical investigation queue.

This module deliberately owns no claim logic. Every call here delegates to
``tools.mcp.kg_tools.queue_op``, which is the single canonical write path to
the ``investigations`` table (schema.sql:77-114). The adapter exists for two
reasons only:

* the orchestrator needs claims in-process, and ``queue_op`` is otherwise
  reachable only over the MCP stdio server;
* ``frontier``/``swarm`` speak ``0x%08x`` while the queue stores bare 8-char
  hex, so a VA-to-row translation has to live in exactly one place.

Reusing ``queue_op`` verbatim means the concurrency guarantees the existing
tests pin -- ``BEGIN IMMEDIATE`` plus a compare-and-set on
``(status, implementer_id)`` with a ``rowcount != 1`` check -- apply here
unchanged. Do not add a second lease store, a second claim table, or a local
lock file; there is exactly one queue.
"""

import os

try:
    from tools.mcp import kg_tools
except ImportError as exc:  # pragma: no cover - off-repo-root only
    raise RuntimeError("canonical queue module is unavailable") from exc

from .models import ROOT, ToolError, normalize_va

DEFAULT_TTL = 1800
MIN_TTL = 60


def queue_va(va):
    # type: (object) -> str
    """Bare 8-char hex exactly as ``investigations.va`` stores it."""
    return normalize_va(va)[2:]


def _call(params):
    # type: (dict) -> dict
    result = kg_tools.queue_op(params)
    if not isinstance(result, dict):
        raise ToolError("queue_error", "queue_op returned a non-mapping result", 1)
    return result


def ok(result):
    # type: (dict) -> bool
    return result.get("status") == "ok"


def code(result):
    # type: (dict) -> object
    return result.get("code")


def get(va=None, inv_id=None, binary_sha256=None):
    # type: (object, object, object) -> dict
    """Look up a row by id, or by VA when the id is unknown."""
    if inv_id:
        return _call({"op": "get", "id": inv_id, "binary_sha256": binary_sha256})
    if va is None:
        return _call({"op": "get"})
    return _call({"op": "get", "va": queue_va(va), "binary_sha256": binary_sha256})


def ensure_row(va, name=None, subsystem=None, binary_sha256=None, mode="replace",
               why_interesting=None, stage="QUEUED"):
    # type: (...) -> dict
    """Make sure a queue row exists for ``va`` under the current build.

    Idempotent: ``queue_op insert`` is ``INSERT OR IGNORE`` on the unique
    ``(kind, va, binary_sha256)`` dedup key and reports the surviving row on a
    hit, so a retry never creates a duplicate. The VA is normalised to bare hex
    first -- passing the frontier's ``0x`` form would miss the dedup key and
    duplicate a row that already exists.
    """
    if not binary_sha256:
        return _err("missing_param", "ensure_row requires binary_sha256")
    bare = queue_va(va)
    existing = get(va=bare, binary_sha256=binary_sha256)
    if ok(existing):
        return existing
    params = {
        "op": "insert",
        "kind": "function",
        "va": bare,
        "name": name,
        "subsystem": subsystem,
        "mode": mode,
        "binary_sha256": binary_sha256,
        "status": "queued",
        "stage": stage,
    }
    if why_interesting:
        params["why_interesting"] = why_interesting
    return _call(params)


def claim(inv_id, implementer_id, binary_sha256=None, ttl=DEFAULT_TTL,
          allow_stale=False, allow_blocked=False):
    # type: (...) -> dict
    """Atomically lease a row. This is the only way work takes ownership."""
    return _call({
        "op": "claim",
        "id": inv_id,
        "implementer_id": implementer_id,
        "binary_sha256": binary_sha256,
        "stale_after_seconds": max(int(ttl), MIN_TTL),
        "allow_stale": bool(allow_stale),
        "allow_blocked": bool(allow_blocked),
    })


def release(inv_id, implementer_id, to="queued", reason=None):
    # type: (...) -> dict
    """End a lease without ending the investigation. Replay-safe."""
    params = {"op": "release", "id": inv_id, "implementer_id": implementer_id,
              "to": to}
    if reason:
        params["reason"] = reason
    return _call(params)


def checkpoint(inv_id, implementer_id, payload=None, stage=None, attempts=None,
               evidence_refs=None, adjudicator_id=None):
    # type: (...) -> dict
    """Record progress. Doubles as the lease heartbeat.

    ``queue_op update`` writes ``updated_at=datetime('now')`` on every accepted
    write, so a checkpoint write renews the lease. That is why there is no
    separate heartbeat verb: the same write, guarded by the lease token, is
    both the progress record and the renewal.
    """
    import json

    params = {"op": "update", "id": inv_id, "implementer_id": implementer_id}
    if payload is not None:
        params["checkpoint"] = json.dumps(payload, sort_keys=True)
    if stage is not None:
        params["stage"] = stage
    if attempts is not None:
        params["attempts"] = json.dumps(attempts, sort_keys=True)
    if evidence_refs is not None:
        params["evidence_refs"] = json.dumps(list(evidence_refs), sort_keys=True)
    if adjudicator_id is not None:
        params["adjudicator_id"] = adjudicator_id
    return _call(params)


def unblock(inv_id, reason=None):
    # type: (str, object) -> dict
    """Return a blocked row to ``queued``.

    The counterpart to ``release`` for rows that have no lease: a blocked row
    carries no owner, so a lease operation cannot move it. Requires the
    explicit ``allow_blocked`` assertion at the queue boundary.
    """
    return _call({"op": "unblock", "id": inv_id, "allow_blocked": True,
                  "reason": reason})


def close(inv_id, implementer_id=None, disposition="done", binary_sha256=None):
    # type: (...) -> dict
    """Move a row to a terminal status. Never deletes; re-closing is a no-op."""
    return _call({
        "op": "close",
        "id": inv_id,
        "status": disposition,
        "implementer_id": implementer_id,
        "binary_sha256": binary_sha256,
    })


def list_rows(status=None, limit=1000, binary_sha256=None):
    # type: (...) -> list
    params = {"op": "list", "limit": int(limit)}
    if status:
        params["status"] = status
    if binary_sha256:
        params["binary_sha256"] = binary_sha256
    result = _call(params)
    if not ok(result):
        return []
    return result.get("investigations", [])


def _err(code_value, message, **extra):
    # type: (str, str, object) -> dict
    result = {"status": "error", "ok": False, "code": code_value, "message": message}
    result.update(extra)
    return result


def default_db():
    # type: () -> object
    """The database the queue is actually pointed at (for reporting)."""
    from tools.mcp import config

    return config.db_path()


def db_is_isolated():
    # type: () -> bool
    """True when OPENSPORE_DB points somewhere other than the sidecar.

    The orchestrator asserts this before it claims anything, so a test run can
    never write leases into the real 100MB+ knowledge graph.
    """
    from tools.mcp import config

    override = os.environ.get("OPENSPORE_DB")
    if not override:
        return False
    try:
        return os.path.realpath(override) != os.path.realpath(config.db_path()) or \
            not os.path.realpath(config.db_path()).startswith(
                os.path.realpath(str(ROOT)))
    except (OSError, ValueError):  # pragma: no cover - defensive
        return False
