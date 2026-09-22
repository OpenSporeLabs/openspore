#!/usr/bin/env python3
"""Approval gates for the OpenSpore MCP server (stdlib only).

Exactly three human-gated writes (docs/RE-AUTOMATION-ARCHITECTURE.md §4):

  * ``trace_run``              -- runs the original game under Wine (~30 s+)
  * ``status_update``          -- the ONLY writer of docs/replacement-status.json
  * ``fixture_check`` with ``rebuild=true`` (identity mode is never gated)

Gate mechanics: the first call (without approval) returns the structured
``approval_required`` error below. The re-call with ``approve=true`` is
valid ONLY under ``OPENSPORE_MCP_TRUSTED=1`` (default off): a misconfigured
session cannot self-approve, and workers are never issued ``approve=true``
at all (only the orchestrator, as the human's decision).

Handler contract matches registry.py: synchronous, no threads, no hidden
state (env is read per call so tests need no restart).
"""
import os

# Tools whose write path always requires approval.
ALWAYS_GATED = ("trace_run", "status_update")

# approval_required payloads carry what/cost so the human sees the price.
GATE_INFO = {
    "trace_run": {
        "what": "boot the original SporeApp.exe under Wine and capture "
                "a probe_tracer observation (~30 s+, shared display :0)",
        "cost": "medium: display + GPU locked, game process spawned; "
                "never touches SPORE/ contents, never kills other services",
    },
    "status_update": {
        "what": "rewrite docs/replacement-status.json (committed evidence "
                "board; the promotion workers propositioned)",
        "cost": "cheap: one JSON file write, fully revertible via git",
    },
    "fixture_check": {
        "what": "rebuild tests/fixtures/cell/fixtures.json from the C++ "
                "emitter (double-run byte identity required before write)",
        "cost": "cheap: cmake build + emitter run; write only on "
                "byte-identical double run",
    },
}

_TRUSTED_ENV = "OPENSPORE_MCP_TRUSTED"


def is_trusted():
    # type: () -> bool
    """True only when the operator explicitly opted into approvals."""
    return os.environ.get(_TRUSTED_ENV) == "1"


def needs_approval(tool, params):
    # type: (str, dict) -> bool
    """True when ``tool``/``params`` must pass the human gate."""
    if tool in ALWAYS_GATED:
        return True
    if tool == "fixture_check":
        return bool(params.get("rebuild"))
    return False


def approval_check(tool, params):
    # type: (str, dict) -> dict | None
    """Gate check. Returns None when approved, else the structured error.

    Approved iff ``params["approve"] is True`` AND ``is_trusted()``.
    Anything else (missing flag, non-True flag, untrusted session) is
    the same ``approval_required`` refusal: callers can assert on
    ``code == "approval_required"`` without distinguishing why.
    """
    if params.get("approve") is True and is_trusted():
        return None
    info = GATE_INFO.get(tool, {"what": tool, "cost": "unknown"})
    trusted = is_trusted()
    if params.get("approve") is True and not trusted:
        hint = ("%s=1 is not set: this session cannot self-approve; "
                "a trusted operator must re-issue approve=true"
                % _TRUSTED_ENV)
    else:
        hint = ("re-call with approve=true under %s=1 after human sign-off; "
                "workers are never issued approve=true" % _TRUSTED_ENV)
    return {
        "status": "error",
        "ok": False,
        "code": "approval_required",
        "error": "approval_required",
        "message": "approval_required: %s" % info["what"],
        "tool": tool,
        "requires": "human approval",
        "what": info["what"],
        "cost": info["cost"],
        "hint": hint,
    }
