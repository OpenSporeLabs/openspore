#!/usr/bin/env python3
"""Tool registry for the OpenSpore MCP server (stdlib only).

Holds the 24 tool schemas plus the handler dispatch table. The KG-spine
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
from tools.mcp import reconstruction_tools
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


def _schema(name, description, properties, required=None,
            required_one_of=None):
    # type: (str, str, Dict[str, Any], object, object) -> Dict[str, Any]
    """Build one tool schema entry (MCP-style inputSchema naming).

    ``required`` is conjunctive (JSON-Schema semantics): every listed
    field must be present. Conditional "one-of" requirements (e.g. one
    of function/address/rva/name) are NOT forced into ``required``;
    they are documented in the description prose plus the additive
    ``required_one_of`` note (a list of alias groups, each group a
    list of which at least one must be supplied). Unknown extra
    fields are always accepted (``additionalProperties`` True).
    """
    entry = {
        "name": name,
        "description": description,
        "inputSchema": {
            "type": "object",
            "properties": properties,
            "required": list(required or []),
            "additionalProperties": True,
        },
    }  # type: Dict[str, Any]
    if required_one_of:
        entry["required_one_of"] = [list(group)
                                    for group in required_one_of]
    return entry


# The 24 tools (exact names). Properties document the real handler
# params, including every accepted alias (e.g. pattern/query,
# topic/path, function/address/rva/name); conjunctive requirements
# live in inputSchema.required while conditional one-of requirements
# live in the additive required_one_of note + description prose.
# Names are stable: implementing subagents may extend properties but must
# keep the names.
TOOL_SCHEMAS = [
    _schema("pipeline_state",
            "Report current pipeline stage, open blockers, and next actions.",
            {"section": {"type": "string"}}),
    _schema("target_select",
            "Select the active analysis target (binary, address, or symbol).",
            {"target": {"type": "string"},
              "limit": {"type": "integer"},
              "status": {"type": "string"}}),
    _schema("function_context",
            "Return bounded reconstruction context for one VA: status, "
            "source, callers, callees, types, globals, ABI, runtime gates, "
            "semantic findings, contradictions, and reconstructed analogues.",
            {"va": {"type": "string"},
             "address": {"type": "string"},
             "limit": {"type": "integer"}},
            required_one_of=[["va", "address"]]),
    _schema("frontier_context",
            "Return the current bounded reconstruction frontier with triage "
            "priority, dependency signals, exact inspect paths, and active "
            "coordination claims when the KG sidecar is available.",
            {"package": {"type": "string"},
             "subsystem": {"type": "string"},
             "status": {"type": "string"},
             "limit": {"type": "integer"}}),
    _schema("reconstruction_status",
            "Return the compact authoritative reconstruction status for one VA.",
            {"va": {"type": "string"},
             "address": {"type": "string"}},
            required_one_of=[["va", "address"]]),
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
            "List neighbours/edges of a knowledge-graph node. "
            "brief (default true): nodes carry {name,label,"
            "evidence_level} only; detail=true (or brief=false) "
            "restores full node rows. limit (default 100, cap 500) "
            "bounds the node list; total_nodes/truncated report it.",
            {"name": {"type": "string"},
              "rel": {"type": "string"},
              "depth": {"type": "integer"},
              "brief": {"type": "boolean"},
              "detail": {"type": "boolean"},
              "limit": {"type": "integer"}},
            required=["name"]),
    _schema("kg_record",
            "Record a cross-tool result (test outcome, decision, mapping).",
             {"kind": {"type": "string"},
              "payload": {"type": "object"},
              "reason": {"type": "string"},
              "nodes": {"type": "array"},
              "edges": {"type": "array"},
              "tests": {"type": "array"},
              "test_rows": {"type": "array"},
              "binary_sha256": {"type": "string"}},
            required=["reason"]),
    _schema("dossier_read",
            "Read a dossier file or section for a target. "
            "One of 'topic'/'path' is required (aliases). "
            "'section' (one top-level key) and 'keys' (alias "
            "'selection'; a top-level key name or array of top-level "
            "key names) are mutually exclusive; large "
            "evidence blobs are compacted by default (flagged via "
            "truncated/truncated_paths) and restored verbatim with "
            "expand=true (alias full=true). md=true also returns the "
            "markdown rendering.",
            {"topic": {"type": "string"},
              "path": {"type": "string"},
              "section": {"type": "string"},
              "keys": {"type": "array", "items": {"type": "string"}},
              "selection": {"type": ["string", "array"],
                            "items": {"type": "string"}},
              "expand": {"type": "boolean"},
              "full": {"type": "boolean"},
              "md": {"type": "boolean"}},
            required_one_of=[["topic", "path"]]),
    _schema("dossier_regenerate",
            "Regenerate a dossier from current analysis state. "
            "One of 'topic'/'path' is required (aliases).",
            {"topic": {"type": "string"},
             "path": {"type": "string"},
             "snapshot": {"type": "string"},
             "out_dir": {"type": "string"}},
            required_one_of=[["topic", "path"]]),
    _schema("ghidra_decompile",
            "Decompile one function via the Ghidra bridge. "
            "One of 'function'/'address'/'rva'/'name' is required.",
            {"function": {"type": "string"},
             "address": {"type": "string"},
             "rva": {"type": "string"},
             "name": {"type": "string"},
             "program": {"type": "string"},
             "image_base": {"type": "string"},
             "ghidra_version": {"type": "string"},
             "force": {"type": "boolean"}},
            required_one_of=[["function", "address", "rva", "name"]]),
    _schema("ghidra_function",
            "Fetch function metadata (address, signature, xrefs). "
            "One of 'function'/'address'/'rva'/'name' is required.",
            {"function": {"type": "string"},
             "address": {"type": "string"},
             "rva": {"type": "string"},
             "name": {"type": "string"},
             "program": {"type": "string"},
             "image_base": {"type": "string"}},
            required_one_of=[["function", "address", "rva", "name"]]),
    _schema("ghidra_search",
            "Search functions/symbols by name pattern. "
            "One of 'pattern'/'query' is required (aliases).",
            {"pattern": {"type": "string"},
             "query": {"type": "string"},
             "limit": {"type": "integer"},
             "program": {"type": "string"},
             "image_base": {"type": "string"}},
            required_one_of=[["pattern", "query"]]),
    _schema("ghidra_snapshot_save",
            "Save the current Ghidra program state snapshot. "
            "One of 'topic'/'label' is required (aliases).",
            {"topic": {"type": "string"},
             "label": {"type": "string"},
             "functions": {"type": "array"},
             "addresses": {"type": "array"},
             "program": {"type": "string"},
             "image_base": {"type": "string"}},
            required_one_of=[["topic", "label"]]),
    _schema("asset_resolve",
            "Resolve an asset record to type/group/instance identity. "
            "'package' is required; one of 'record' (T:G:I) / 'type' "
            "(+ optional 'group', 'instance') is required.",
            {"package": {"type": "string"},
             "record": {"type": "string"},
             "type": {"type": "string"},
             "type_id": {"type": "string"},
             "group": {"type": "string"},
             "group_id": {"type": "string"},
             "instance": {"type": "string"},
             "instance_id": {"type": "string"},
             "limit": {"type": "integer"}},
            required=["package"],
            required_one_of=[["record", "type", "type_id"]]),
    _schema("asset_scan",
            "Scan a package for asset records ('package' omitted = "
            "SPORE/ inventory mode).",
            {"package": {"type": "string"},
             "limit": {"type": "integer"}}),
    _schema("vtable_lookup",
            "Look up vtable / class-hierarchy info. One of "
            "'class'/'class_name'/'address'/'namespace'/'subsystem' "
            "is required. Slots are projected to {ptr,func} by default "
            "(null-valued keys stripped); detail=true (alias "
            "full_slots=true) returns the full slot dicts. limit "
            "(default 20, cap 500) bounds the match list; "
            "total_matches/truncated report it.",
            {"class": {"type": "string"},
              "class_name": {"type": "string"},
              "address": {"type": "string"},
              "namespace": {"type": "string"},
              "subsystem": {"type": "string"},
              "limit": {"type": "integer"},
              "detail": {"type": "boolean"},
              "full_slots": {"type": "boolean"}},
            required_one_of=[["class", "class_name", "address",
                               "namespace", "subsystem"]]),
    _schema("trace_run",
            "Run a differential trace scenario under Wine (gated: "
            "re-call with approve=true under OPENSPORE_MCP_TRUSTED=1). "
            "'scenario' is required once approved.",
            {"scenario": {"type": "string"},
             "duration": {"type": "integer"},
             "timeout": {"type": "integer"},
             "out_dir": {"type": "string"},
             "approve": {"type": "boolean"}}),
    _schema("trace_analyze",
            "Analyze a captured trace run. One of 'run_id'/'scenario' "
            "/'path' is required.",
            {"run_id": {"type": "string"},
             "scenario": {"type": "string"},
             "path": {"type": "string"}},
            required_one_of=[["run_id", "scenario", "path"]]),
    _schema("trace_status",
            "Report status of trace runs (read-only listing).",
            {"out_dir": {"type": "string"},
             "examples_dir": {"type": "string"}}),
    _schema("test_run",
            "Run the repo test suite or a selector subset.",
            {"selector": {"type": "string"},
             "test": {"type": "string"},
             "timeout": {"type": "integer"}}),
    _schema("status_update",
            "Promote/demote one subsystem entry in "
            "docs/replacement-status.json (gated: re-call with "
            "approve=true under OPENSPORE_MCP_TRUSTED=1). 'subsystem' "
            "(alias 'name') and 'status' are required once approved.",
            {"text": {"type": "string"},
             "subsystem": {"type": "string"},
             "name": {"type": "string"},
             "status": {"type": "string"},
             "evidence": {"type": "array"},
             "trace_manifest": {"type": "string"},
             "approve": {"type": "boolean"}}),
    _schema("fixture_check",
            "Verify synthetic fixtures reproduce byte-identically "
            "(identity mode read-only; rebuild=true is gated).",
            {"name": {"type": "string"},
             "rebuild": {"type": "boolean"},
             "fixtures_path": {"type": "string"}}),
    _schema("queue_op",
            "Coordinate queue operations. op=claim atomically leases an open "
            "investigation, refuses duplicate active owners, preserves "
            "terminal rows, and requires explicit stale/blocked overrides. "
            "op=release ends a lease without ending the investigation. Every "
            "write to a leased row requires implementer_id to match the lease "
            "holder. op=get accepts either id or va.",
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
              "disposition": {"type": "string"},
              "to": {"type": "string"},
              "reason": {"type": "string"},
              "block_reason": {"type": "string"},
              "prerequisites": {"type": "string"},
              "attempts": {"type": "string"},
              "checkpoint": {"type": "string"},
              "evidence_refs": {"type": "string"},
              "implementer_id": {"type": "string"},
              "adjudicator_id": {"type": "string"},
              "binary_sha256": {"type": "string"},
              "stale_after_seconds": {"type": "integer"},
              "allow_stale": {"type": "boolean"},
              "allow_blocked": {"type": "boolean"},
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
    "function_context": reconstruction_tools.function_context,
    "frontier_context": reconstruction_tools.frontier_context,
    "reconstruction_status": reconstruction_tools.reconstruction_status,
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

    Error-code split (JSON-RPC -32602 vs in-band codes): InvalidParams
    here (and -32602 in server.py) is reserved for a malformed
    envelope -- params/arguments that are not an object, or a missing
    / non-string tool name. Domain validation (a well-formed object
    that names a missing/invalid field) NEVER raises here; handlers
    return an in-band ``{"status": "error", "code": ..., "message":
    ...}`` dict instead (``invalid_params`` for bad values, the
    legacy ``missing_param``/``missing_reason`` codes -- each carrying
    an additive ``field`` key naming the missing field -- for absent
    ones). Moving domain errors to -32602 would break the opencode
    retry loop and the GRACEFUL_CODES contract.
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
