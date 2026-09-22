#!/usr/bin/env python3
"""Tool registry for the OpenSpore MCP server (stdlib only).

Holds the 21 tool schemas plus the handler dispatch table. The KG-spine
tools (``pipeline_state``, ``target_select``, ``kg_query``,
``kg_neighbors``, ``kg_record``, ``queue_op``) are real implementations
in kg_tools.py, the Ghidra/dossier tools (``ghidra_decompile``,
``ghidra_function``, ``ghidra_search``, ``ghidra_snapshot_save``,
``vtable_lookup``, ``dossier_read``, ``dossier_regenerate``) are real
implementations in ghidra_tools.py, and the asset/runtime/validation
tools (``asset_resolve``, ``asset_scan``, ``trace_run``,
``trace_analyze``, ``trace_status``, ``test_run``, ``status_update``,
``fixture_check``) are real implementations in asset_tools.py and
runtime_tools.py (approval gates in safety.py) -- dispatch,
unknown-tool, and bad-params paths stay fully wired so the server core
stays testable throughout.

Handler contract: ``handler(params: dict) -> dict``. Handlers must be
synchronous, must not spawn threads, and must keep no hidden state.
"""
import copy
from typing import Any, Callable, Dict, List

from tools.mcp import asset_tools
from tools.mcp import ghidra_tools
from tools.mcp import kg_tools
from tools.mcp import runtime_tools

# Provisional note carried by every stub result so callers can tell
# "server core alive, implementation pending" apart from real output.
_STUB_NOTE = "server core only; full implementation lands with a later subagent"


class ToolUnknown(Exception):
    """Raised by dispatch() when the tool name is not registered."""


class InvalidParams(Exception):
    """Raised by dispatch() when params are not a dict."""


def _make_stub(name, note=_STUB_NOTE):
    # type: (str, str) -> Callable[[Dict[str, Any]], Dict[str, Any]]
    """Build a stub handler returning a structured not_implemented result."""

    def _handler(params):
        # type: (Dict[str, Any]) -> Dict[str, Any]
        return {
            "status": "not_implemented",
            "ok": False,
            "code": "not_implemented",
            "tool": name,
            "params": dict(params),
            "note": note,
        }

    _handler.__name__ = "stub_%s" % name
    return _handler


def _schema(name, description, properties, required=None):
    # type: (str, str, Dict[str, Any], object) -> Dict[str, Any]
    """Build one tool schema entry (MCP-style inputSchema naming)."""
    return {
        "name": name,
        "description": description,
        "inputSchema": {
            "type": "object",
            "properties": properties,
            "required": list(required or []),
            "additionalProperties": True,
        },
    }


# The 21 tools (exact names). Properties for the KG-spine tools document
# the real kg_tools.py params; stub tools keep provisional properties.
# Names are stable: implementing subagents may extend properties but must
# keep the names.
TOOL_SCHEMAS = [
    _schema("pipeline_state",
            "Report current pipeline stage, open blockers, and next actions.",
            {"section": {"type": "string"}}),
    _schema("target_select",
            "Select the active analysis target (binary, address, or symbol).",
            {"target": {"type": "string"},
             "limit": {"type": "integer"}}),
    _schema("kg_query",
            "Query the knowledge-graph sidecar for nodes by label/name.",
            {"query": {"type": "string"},
              "name_substring": {"type": "string"},
              "label": {"type": "string"},
              "evidence": {"type": "string"},
              "evidence_level": {"type": "string"},
              "limit": {"type": "integer"},
              "offset": {"type": "integer"}}),
    _schema("kg_neighbors",
            "List neighbours/edges of a knowledge-graph node.",
            {"name": {"type": "string"},
              "rel": {"type": "string"},
              "depth": {"type": "integer"}},
            required=["name"]),
    _schema("kg_record",
            "Record a cross-tool result (test outcome, decision, mapping).",
            {"kind": {"type": "string"},
              "payload": {"type": "object"},
              "reason": {"type": "string"},
              "nodes": {"type": "array"},
              "edges": {"type": "array"},
              "tests": {"type": "array"},
              "binary_sha256": {"type": "string"}},
            required=["reason"]),
    _schema("dossier_read",
            "Read a dossier file or section for a target.",
            {"path": {"type": "string"},
             "section": {"type": "string"}}),
    _schema("dossier_regenerate",
            "Regenerate a dossier from current analysis state.",
            {"path": {"type": "string"}}),
    _schema("ghidra_decompile",
            "Decompile one function via the Ghidra bridge.",
            {"function": {"type": "string"}}),
    _schema("ghidra_function",
            "Fetch function metadata (address, signature, xrefs).",
            {"address": {"type": "string"},
             "name": {"type": "string"}}),
    _schema("ghidra_search",
            "Search functions/symbols by name pattern.",
            {"pattern": {"type": "string"},
             "limit": {"type": "integer"}}),
    _schema("ghidra_snapshot_save",
            "Save the current Ghidra program state snapshot.",
            {"label": {"type": "string"}}),
    _schema("asset_resolve",
            "Resolve an asset record to type/group/instance identity.",
            {"record": {"type": "string"},
             "type": {"type": "string"}}),
    _schema("asset_scan",
            "Scan a package for asset records.",
            {"package": {"type": "string"}}),
    _schema("vtable_lookup",
            "Look up vtable / class-hierarchy info for a class or address.",
            {"class": {"type": "string"},
             "address": {"type": "string"}}),
    _schema("trace_run",
            "Run a differential trace scenario under Wine (gated).",
            {"scenario": {"type": "string"}}),
    _schema("trace_analyze",
            "Analyze a captured trace run.",
            {"run_id": {"type": "string"},
             "path": {"type": "string"}}),
    _schema("trace_status",
            "Report status of a trace run.",
            {"run_id": {"type": "string"}}),
    _schema("test_run",
            "Run the repo test suite or a selector subset.",
            {"selector": {"type": "string"}}),
    _schema("status_update",
            "Append a status/progress update to shared state.",
            {"text": {"type": "string"}}),
    _schema("fixture_check",
            "Verify synthetic fixtures reproduce byte-identically.",
            {"name": {"type": "string"}}),
    _schema("queue_op",
            "Enqueue a gated/background operation for later approval.",
            {"op": {"type": "string"},
             "payload": {"type": "object"},
             "id": {"type": "string"},
             "kind": {"type": "string"},
             "va": {"type": "string"},
             "name": {"type": "string"},
             "subsystem": {"type": "string"},
             "mode": {"type": "string"},
             "why_interesting": {"type": "string"},
             "stage": {"type": "string"},
              "status": {"type": "string"},
              "binary_sha256": {"type": "string"},
              "limit": {"type": "integer"}},
            required=["op"]),
]

# Handler table: name -> callable. Mutable so tests can inject a raiser
# without touching the schema list tools/list serves. KG-spine tools are
# real (kg_tools.py), as are the Ghidra/dossier tools (ghidra_tools.py)
# and the asset/runtime/validation tools (asset_tools.py,
# runtime_tools.py; gates in safety.py).
HANDLERS = {
    schema["name"]: _make_stub(schema["name"]) for schema in TOOL_SCHEMAS
}  # type: Dict[str, Callable[[Dict[str, Any]], Dict[str, Any]]]

_REAL_HANDLERS = {
    "pipeline_state": kg_tools.pipeline_state,
    "target_select": kg_tools.target_select,
    "kg_query": kg_tools.kg_query,
    "kg_neighbors": kg_tools.kg_neighbors,
    "kg_record": kg_tools.kg_record,
    "queue_op": kg_tools.queue_op,
    "ghidra_decompile": ghidra_tools.ghidra_decompile,
    "ghidra_function": ghidra_tools.ghidra_function,
    "ghidra_search": ghidra_tools.ghidra_search,
    "ghidra_snapshot_save": ghidra_tools.ghidra_snapshot_save,
    "vtable_lookup": ghidra_tools.vtable_lookup,
    "dossier_read": ghidra_tools.dossier_read,
    "dossier_regenerate": ghidra_tools.dossier_regenerate,
    "asset_resolve": asset_tools.asset_resolve,
    "asset_scan": asset_tools.asset_scan,
    "trace_run": runtime_tools.trace_run,
    "trace_analyze": runtime_tools.trace_analyze,
    "trace_status": runtime_tools.trace_status,
    "test_run": runtime_tools.test_run,
    "status_update": runtime_tools.status_update,
    "fixture_check": runtime_tools.fixture_check,
}
HANDLERS.update(_REAL_HANDLERS)


def tool_names():
    # type: () -> List[str]
    """Return registered tool names in schema order."""
    return [schema["name"] for schema in TOOL_SCHEMAS]


def list_tools():
    # type: () -> List[Dict[str, Any]]
    """Return the schema list served by tools/list (deep copies)."""
    return copy.deepcopy(TOOL_SCHEMAS)


def dispatch(tool_name, params=None):
    # type: (Any, Any) -> Dict[str, Any]
    """Run one tool handler.

    Raises ToolUnknown for unregistered names and InvalidParams when
    ``params`` is not a dict. Handler exceptions propagate to the caller
    (server.py maps them to a -32603 error, never a crash).
    """
    if tool_name not in HANDLERS:
        raise ToolUnknown("unknown tool: %r" % (tool_name,))
    if params is None:
        params = {}
    if not isinstance(params, dict):
        raise InvalidParams(
            "invalid params for tool %r: expected object, got %s"
            % (tool_name, type(params).__name__)
        )
    return HANDLERS[tool_name](params)
