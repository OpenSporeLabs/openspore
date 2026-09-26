#!/usr/bin/env python3
"""Real handlers for the KG-spine MCP tools (stdlib only).

Implements ``kg_query``, ``kg_neighbors``, ``kg_record``, ``queue_op``,
``pipeline_state`` and ``target_select`` against the shared sidecar
``knowledgegraph/spore.db``. Handler contract matches registry.py:
``handler(params: dict) -> dict``; synchronous, no threads, no hidden
state (the DB path is resolved per call via config.db_path() so the
OPENSPORE_DB override works without a restart).

Conventions (mirror knowledgegraph/kg.py + seed.py, never reinvented):
  * node ordering is always ``ORDER BY label, name`` (deterministic);
  * ambiguous node names (same name, several labels) are structured
    errors, exactly like ``kg.py _node_id``;
  * evidence levels are the 7-level scale from knowledgegraph/scale.py
    (single source of truth; imported when available, mirrored fallback
    otherwise) -- kg_record rejects anything else and never writes a
    replacement ``status`` (scale/status live in
    docs/replacement-status.json, not in the KG);
  * queue writes use INSERT OR IGNORE on the (kind, va, binary_sha256)
    dedup key; done/dropped rows are never deleted; missing ids are
    structured ``not_found`` errors;
  * read tools only ever SELECT: stale binary identities stay queryable,
    historical evidence is never deleted.

Domain failures are in-band ``{"status": "error", "code": ..., ...}``
dicts (never exceptions), so registry.dispatch() callers can assert on
them without tripping the server's -32603 path.
"""
import datetime
import glob
import json
import os
import sqlite3

from tools.mcp import config

try:
    # Single source of truth for the 7-level scale.
    from knowledgegraph.scale import EV as _SCALE_EV
    from knowledgegraph.scale import EV_ORDER as _SCALE_EV_ORDER
except ImportError:  # pragma: no cover - exercised only off-repo-root
    _SCALE_EV_ORDER = ("UNKNOWN", "APPROXIMATION", "INFERRED",
                       "SUPPORTED", "OBSERVED", "CONFIRMED", "VERIFIED")
    _SCALE_EV = {"UNKNOWN": 0.0, "APPROXIMATION": 0.3, "INFERRED": 0.5,
                 "SUPPORTED": 0.75, "OBSERVED": 0.85, "CONFIRMED": 0.9,
                 "VERIFIED": 1.0}

EV_LEVELS = tuple(_SCALE_EV_ORDER)
_EV_SET = frozenset(EV_LEVELS)

# Stage/lifecycle vocabulary for investigations (seed.py §2/§3).
_INVESTIGATION_STATUSES = ("queued", "active", "blocked", "done", "dropped")
_INVESTIGATION_KINDS = ("function", "subsystem")
_TERMINAL_STATUSES = ("done", "dropped")
# Columns queue_op update/close may touch; id/kind/binary_sha256 are
# identity and never rewritten.
_QUEUE_WRITABLE = ("mode", "why_interesting", "stage", "status",
                   "block_reason", "prerequisites", "attempts",
                   "checkpoint", "evidence_refs", "implementer_id",
                   "adjudicator_id", "name", "subsystem", "va")
# Progress vocabulary used by the orchestrator (docs/analysis/ORCHESTRATOR.md
# stage machine). ``status`` carries lifecycle, ``stage`` carries progress, so
# a blocked row keeps its stage and unblocking is a pure status transition.
_STAGES = ("QUEUED", "SELECTED", "DOSSIER", "STATIC", "ASSETS", "CONTRACT",
           "REPLACE", "VALIDATE", "RECORDED")
# Documented block_reason prefixes. Free text stays accepted; these are the
# machine-readable classes the orchestrator routes on (docs/tooling/
# orchestration.md). Enforced nowhere -- advisory only.
_BLOCK_REASON_PREFIXES = (
    "validation_warn", "validation_unknown", "validation_fail",
    "malformed_worker_output", "dependency_blocked", "no_evidence",
    "ghidra_offline", "machine_locked", "no_spo", "approval_required",
    "escalated", "obsolete",
)
# Floor for a lease TTL. Zero would make every active row instantly stealable,
# which turns a single racing worker into a double-ownership bug.
_MIN_STALE_AFTER_SECONDS = 60
# Lease clock formats seen in the sidecar. ``datetime('now')`` (SQLite, used by
# every queue_op write) produces the first; rows seeded outside queue_op carry
# ISO-8601 with a trailing Z. A clock we cannot read is never stale: the row
# stays locked and requires an explicit, human-asserted release.
_LEASE_TIME_FORMATS = ("%Y-%m-%d %H:%M:%S", "%Y-%m-%dT%H:%M:%SZ",
                       "%Y-%m-%dT%H:%M:%S")

_NODE_COLS = ("id", "label", "name", "attrs_json", "confidence", "origin",
              "note", "created_at", "evidence_level", "updated_at",
              "binary_sha256")


def _err(code, message, **extra):
    # type: (str, str, object) -> dict
    result = {"status": "error", "ok": False, "code": code,
              "message": message}
    result.update(extra)
    return result


def _connect():
    # type: () -> sqlite3.Connection
    db = config.db_path()
    # An explicit timeout (rather than sqlite3's implicit 5s busy handler)
    # keeps a multi-worker claim stampede from surfacing as an opaque
    # "database is locked" db_error.
    conn = sqlite3.connect(db, timeout=30.0)
    conn.row_factory = sqlite3.Row
    conn.execute("PRAGMA busy_timeout=30000")
    return conn


_SCHEMA_READY = set()


def _missing_table(conn, name):
    # type: (sqlite3.Connection, str) -> bool
    row = conn.execute(
        "SELECT 1 FROM sqlite_master WHERE type='table' AND name=?",
        (name,)).fetchone()
    return row is None


def _ensure_schema(conn):
    # type: (sqlite3.Connection) -> None
    """Create sidecar tables if absent (idempotent; write paths only).

    executescript() takes a write lock, so it is run once per database per
    process. Re-running it inside every write op would widen the window in
    which a competing BEGIN IMMEDIATE has to wait.
    """
    db = config.db_path()
    if db in _SCHEMA_READY:
        return
    schema = config.resolve("knowledgegraph", "schema.sql")
    with open(schema) as fh:
        conn.executescript(fh.read())
    _SCHEMA_READY.add(db)


def _parse_attrs(raw):
    # type: (object) -> object
    if raw is None:
        return {}
    if isinstance(raw, dict):
        return raw
    if isinstance(raw, str):
        try:
            parsed = json.loads(raw)
        except ValueError:
            return raw
        return parsed
    return raw


def _node_dict(row):
    # type: (sqlite3.Row) -> dict
    return {
        "id": row["id"],
        "label": row["label"],
        "name": row["name"],
        "attrs": _parse_attrs(row["attrs_json"]),
        "confidence": row["confidence"],
        "origin": row["origin"],
        "note": row["note"],
        "evidence_level": row["evidence_level"],
        "binary_sha256": row["binary_sha256"],
        "created_at": row["created_at"],
        "updated_at": row["updated_at"],
    }


def _node_brief(row):
    # type: (sqlite3.Row) -> dict
    """Slim node projection (S2.1 scope G): identity + evidence only.

    Drops attrs/confidence/origin/note/id/binary_sha256/created_at/
    updated_at -- the read payload must not repeat per-node timestamps
    (the DB is authoritative) or the build identity per node. Full
    details stay available via kg_query or kg_neighbors detail=true.
    """
    return {
        "name": row["name"],
        "label": row["label"],
        "evidence_level": row["evidence_level"],
    }


def _is_true(value):
    # type: (object) -> bool
    """Deterministic truth flag for optional MCP booleans.

    Accepts real JSON booleans/ints plus the common string spellings;
    anything else (including the string "false") is False. Never raises.
    """
    if isinstance(value, bool):
        return value
    if isinstance(value, (int, float)):
        return value == 1
    if isinstance(value, str):
        return value.strip().lower() in ("1", "true", "yes", "on")
    return False


def _inv_dict(row):
    # type: (sqlite3.Row) -> dict
    return {key: row[key] for key in row.keys()}


# kg_neighbors slimming (S2.1 scope G): brief default, bounded, flagged.
# The node list is sliced after the deterministic (label, name) sort and
# the cap is reported via limit/total_nodes/truncated. Edges stay
# unfiltered (already minimal per-edge dicts); endpoints outside the
# node cap remain resolvable via kg_query.
_NEIGHBORS_DEFAULT_LIMIT = 100
_NEIGHBORS_MAX_LIMIT = 500


def _node_ids_by_name(conn, name):
    # type: (sqlite3.Connection, str) -> list
    return conn.execute(
        "SELECT id, label FROM node WHERE name=? ORDER BY label, id",
        (name,)).fetchall()


# --------------------------------------------------------------------------- #
# kg_query: read-only node lookup (label / name-substring / evidence).
# --------------------------------------------------------------------------- #
def kg_query(params):
    # type: (dict) -> dict
    label = params.get("label")
    substring = params.get("query", params.get("name_substring"))
    evidence = params.get("evidence", params.get("evidence_level"))
    limit = params.get("limit", 50)
    offset = params.get("offset", 0)
    try:
        limit = int(limit)
        offset = int(offset)
    except (TypeError, ValueError):
        return _err("invalid_params",
                    "'limit' and 'offset' must be integers")
    if limit < 0 or offset < 0:
        return _err("invalid_params",
                    "'limit' and 'offset' must be >= 0")
    limit = min(limit, 500)
    if evidence is not None and evidence not in _EV_SET:
        return _err("invalid_evidence",
                    "unknown evidence level %r; expected one of: %s"
                    % (evidence, ", ".join(EV_LEVELS)),
                    value=evidence)

    clauses, args = [], []
    if label is not None:
        clauses.append("label=?")
        args.append(label)
    if substring is not None:
        clauses.append("name LIKE '%' || ? || '%' ESCAPE '\\'")
        args.append(str(substring).replace("\\", "\\\\")
                    .replace("%", "\\%").replace("_", "\\_"))
    if evidence is not None:
        clauses.append("evidence_level=?")
        args.append(evidence)
    where = (" WHERE " + " AND ".join(clauses)) if clauses else ""

    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        if _missing_table(conn, "node"):
            return _err("empty_database",
                        "KG database has no node table; run kg.py init/seed")
        total = conn.execute(
            "SELECT COUNT(*) FROM node" + where, args).fetchone()[0]
        rows = conn.execute(
            "SELECT %s FROM node%s ORDER BY label, name LIMIT ? OFFSET ?"
            % (", ".join(_NODE_COLS), where),
            args + [limit, offset]).fetchall()
    except sqlite3.Error as exc:
        return _err("db_error", "kg_query failed: %s" % exc)
    finally:
        conn.close()
    nodes = [_node_dict(row) for row in rows]
    return {"status": "ok", "tool": "kg_query", "nodes": nodes,
            "count": len(nodes), "total": total,
            "limit": limit, "offset": offset}


# --------------------------------------------------------------------------- #
# kg_neighbors: read-only 1-2 hop traversal around one node name.
#
# Context slimming (S2.1 scope G, deterministic only, no summarizer):
#   * brief (default true): nodes are {name,label,evidence_level} --
#     no per-node created_at/updated_at/binary_sha256 repetition (the
#     DB is authoritative for timestamps; the build identity lives on
#     write/cache paths, not on every read row);
#   * detail=true (or brief=false): full _node_dict rows, same order;
#   * limit (default 100, cap 500): bounds the node list (sliced after
#     the deterministic sort); total_nodes/truncated report the cap, so
#     nothing is silently truncated. Edges are already minimal and stay
#     unfiltered.
# --------------------------------------------------------------------------- #
def kg_neighbors(params):
    # type: (dict) -> dict
    name = params.get("name")
    if not isinstance(name, str) or not name:
        return _err("missing_param",
                    "'name' (node name) is required and must be non-empty",
                    field="name")
    depth = params.get("depth", 1)
    try:
        depth = int(depth)
    except (TypeError, ValueError):
        return _err("invalid_params", "'depth' must be an integer")
    if depth not in (1, 2):
        return _err("invalid_params",
                    "'depth' must be 1 or 2, got %r" % (params.get("depth"),))
    rel = params.get("rel")
    try:
        limit = int(params.get("limit", _NEIGHBORS_DEFAULT_LIMIT))
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit' must be an integer")
    if limit < 0:
        return _err("invalid_params", "'limit' must be >= 0")
    effective = min(limit, _NEIGHBORS_MAX_LIMIT)
    detail = _is_true(params.get("detail", False)) or \
        not _is_true(params.get("brief", True))

    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        if _missing_table(conn, "node") or _missing_table(conn, "edge"):
            return _err("empty_database",
                        "KG database has no node/edge tables")
        matches = _node_ids_by_name(conn, name)
        if not matches:
            return _err("not_found", "node not found: %r" % (name,))
        if len(matches) > 1:
            return _err("ambiguous",
                        "ambiguous node name %r; matches labels: %s"
                        % (name, ", ".join(r["label"] for r in matches)),
                        labels=[r["label"] for r in matches])
        center_id = matches[0]["id"]
        center_label = matches[0]["label"]

        seen = {center_id}
        frontier = {center_id}
        edge_rows = []
        for _ in range(depth):
            if not frontier:
                break
            marks = ",".join("?" for _ in frontier)
            ids = sorted(frontier)
            query = (
                "SELECT e.src, e.rel, e.dst, "
                "n1.name src_name, n1.label src_label, "
                "n2.name dst_name, n2.label dst_label "
                "FROM edge e "
                "JOIN node n1 ON n1.id=e.src "
                "JOIN node n2 ON n2.id=e.dst "
                "WHERE (e.src IN (%s) OR e.dst IN (%s))" % (marks, marks))
            qargs = ids + ids
            if rel is not None:
                query += " AND e.rel=?"
                qargs.append(rel)
            query += " ORDER BY src_name, e.rel, dst_name"
            rows = conn.execute(query, qargs).fetchall()
            frontier = set()
            for row in rows:
                edge_rows.append(row)
                for end in (row["src"], row["dst"]):
                    if end not in seen:
                        seen.add(end)
                        frontier.add(end)
        if seen:
            marks = ",".join("?" for _ in seen)
            node_rows = conn.execute(
                "SELECT %s FROM node WHERE id IN (%s)"
                % (", ".join(_NODE_COLS), marks),
                sorted(seen)).fetchall()
        else:  # pragma: no cover - center is always in seen
            node_rows = []
    except sqlite3.Error as exc:
        return _err("db_error", "kg_neighbors failed: %s" % exc)
    finally:
        conn.close()

    nodes = sorted(((_node_dict(r) if detail else _node_brief(r))
                    for r in node_rows),
                   key=lambda n: (n["label"], n["name"]))
    total_nodes = len(nodes)
    truncated = total_nodes > effective
    nodes = nodes[:effective]
    edges = [{"src": r["src_name"], "src_label": r["src_label"],
              "rel": r["rel"], "dst": r["dst_name"],
              "dst_label": r["dst_label"]} for r in edge_rows]
    edges.sort(key=lambda e: (e["src"], e["rel"], e["dst"]))
    return {"status": "ok", "tool": "kg_neighbors",
            "center": {"name": name, "label": center_label},
            "depth": depth,
            "nodes": nodes, "edges": edges,
            "node_count": len(nodes), "edge_count": len(edges),
            "total_nodes": total_nodes, "truncated": truncated,
            "limit": effective, "detail": detail}


# --------------------------------------------------------------------------- #
# kg_record: batch node/edge/test writes; reason required; evidence-gated.
# --------------------------------------------------------------------------- #
def _coerce_node(entry, index, default_sha):
    # type: (object, int, object) -> dict
    if not isinstance(entry, dict):
        return {"_error": _err(
            "invalid_params", "nodes[%d] must be an object" % index)}
    if "status" in entry:
        return {"_error": _err(
            "status_forbidden",
            "kg_record never writes replacement status; "
            "status lives in docs/replacement-status.json, not the KG")}
    label, name = entry.get("label"), entry.get("name")
    if not label or not name:
        return {"_error": _err(
            "invalid_params",
            "nodes[%d] requires 'label' and 'name'" % index)}
    evidence = entry.get("evidence_level", "UNKNOWN")
    if evidence not in _EV_SET:
        return {"_error": _err(
            "invalid_evidence",
            "nodes[%d]: unknown evidence level %r; expected one of: %s"
            % (index, evidence, ", ".join(EV_LEVELS)),
            value=evidence)}
    attrs = entry.get("attrs", {})
    if isinstance(attrs, dict) and "status" in attrs:
        return {"_error": _err(
            "status_forbidden",
            "nodes[%d]: attrs must not carry 'status'; "
            "kg_record never writes replacement status" % index)}
    if isinstance(attrs, dict):
        try:
            attrs_json = json.dumps(attrs, sort_keys=True,
                                    separators=(",", ":"),
                                    ensure_ascii=False)
        except (TypeError, ValueError):
            return {"_error": _err(
                "invalid_params",
                "nodes[%d]: 'attrs' is not JSON-serialisable" % index)}
    elif isinstance(attrs, str):
        attrs_json = attrs
    else:
        return {"_error": _err(
            "invalid_params",
            "nodes[%d]: 'attrs' must be an object" % index)}
    confidence = entry.get("confidence")
    if confidence is None:
        confidence = _SCALE_EV.get(evidence, 0.0)
    try:
        confidence = float(confidence)
    except (TypeError, ValueError):
        return {"_error": _err(
            "invalid_params",
            "nodes[%d]: 'confidence' must be numeric" % index)}
    return {"label": label, "name": name, "attrs_json": attrs_json,
            "confidence": confidence,
            "origin": entry.get("origin", "unknown"),
            "note": entry.get("note"),
            "evidence_level": evidence,
            "binary_sha256": entry.get("binary_sha256", default_sha)}


def _coerce_test(entry, index):
    # type: (object, int) -> dict
    if not isinstance(entry, dict):
        return {"_error": _err(
            "invalid_params", "tests[%d] must be an object" % index)}
    if "status" in entry:
        return {"_error": _err(
            "status_forbidden",
            "kg_record never writes replacement status; "
            "record test outcomes only")}
    if not entry.get("name"):
        return {"_error": _err(
            "invalid_params", "tests[%d] requires 'name'" % index)}
    passed = entry.get("pass", entry.get("passed"))
    if isinstance(passed, bool):
        passed = int(passed)
    if passed is not None and passed not in (0, 1):
        return {"_error": _err(
            "invalid_params",
            "tests[%d]: 'pass' must be 0, 1 or null" % index)}
    return {"name": entry["name"], "stage": entry.get("stage"),
            "seed": entry.get("seed"), "expected": entry.get("expected"),
            "actual": entry.get("actual"), "pass": passed}


_NODE_UPSERT = """
INSERT INTO node(label,name,attrs_json,confidence,origin,note,
                 evidence_level,binary_sha256)
VALUES(?,?,?,?,?,?,?,?)
ON CONFLICT(label,name) DO UPDATE SET
  attrs_json=excluded.attrs_json,
  confidence=excluded.confidence,
  origin=excluded.origin,
  note=excluded.note,
  evidence_level=excluded.evidence_level,
  binary_sha256=excluded.binary_sha256,
  updated_at=datetime('now')"""


def kg_record(params):
    # type: (dict) -> dict
    reason = params.get("reason")
    if not isinstance(reason, str) or not reason.strip():
        return _err("missing_reason",
                    "kg_record requires a non-empty 'reason' "
                    "(why this cross-tool result is recorded)",
                    field="reason")
    raw_nodes = params.get("nodes", [])
    raw_edges = params.get("edges", [])
    raw_tests = params.get("tests", params.get("test_rows", []))
    if not isinstance(raw_nodes, list) or not isinstance(raw_edges, list) \
            or not isinstance(raw_tests, list):
        return _err("invalid_params",
                    "'nodes', 'edges' and 'tests' must be arrays")
    default_sha = params.get("binary_sha256")

    nodes = []
    for i, entry in enumerate(raw_nodes):
        coerced = _coerce_node(entry, i, default_sha)
        if "_error" in coerced:
            return coerced["_error"]
        nodes.append(coerced)
    tests = []
    for i, entry in enumerate(raw_tests):
        coerced = _coerce_test(entry, i)
        if "_error" in coerced:
            return coerced["_error"]
        tests.append(coerced)
    for i, entry in enumerate(raw_edges):
        if not isinstance(entry, dict) or \
                not entry.get("src") or not entry.get("dst") \
                or not entry.get("rel"):
            return _err("invalid_params",
                        "edges[%d] requires 'src', 'dst' and 'rel' "
                        "(node names)" % i)

    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        _ensure_schema(conn)
        with conn:
            for node in nodes:
                conn.execute(_NODE_UPSERT, (
                    node["label"], node["name"], node["attrs_json"],
                    node["confidence"], node["origin"], node["note"],
                    node["evidence_level"], node["binary_sha256"]))
            edge_count = 0
            for entry in raw_edges:
                for end_key in ("src", "dst"):
                    matches = _node_ids_by_name(conn, entry[end_key])
                    if not matches:
                        raise _RecordAbort(_err(
                            "not_found", "edge endpoint not found: %r"
                            % (entry[end_key],)))
                    if len(matches) > 1:
                        raise _RecordAbort(_err(
                            "ambiguous",
                            "ambiguous edge endpoint %r; matches labels: %s"
                            % (entry[end_key], ", ".join(
                                r["label"] for r in matches))))
                    entry[end_key + "_id"] = matches[0]["id"]
                conn.execute(
                    "INSERT OR IGNORE INTO edge(src,dst,rel) VALUES(?,?,?)",
                    (entry["src_id"], entry["dst_id"], entry["rel"]))
                edge_count += 1
            for test in tests:
                conn.execute(
                    "INSERT INTO test_result(name,stage,seed,expected,"
                    "actual,pass) VALUES(?,?,?,?,?,?)",
                    (test["name"], test["stage"], test["seed"],
                     test["expected"], test["actual"], test["pass"]))
    except _RecordAbort as abort:
        conn.close()
        return abort.error
    except (sqlite3.Error, OSError) as exc:
        try:
            conn.close()
        except sqlite3.Error:
            pass
        return _err("db_error", "kg_record failed: %s" % exc)
    conn.close()
    return {"status": "ok", "tool": "kg_record", "reason": reason.strip(),
            "inserted": {"nodes": len(nodes), "edges": edge_count,
                         "tests": len(tests)}}


class _RecordAbort(Exception):
    """Internal: abort a kg_record transaction with a structured error."""

    def __init__(self, error):
        super(_RecordAbort, self).__init__(error.get("message", ""))
        self.error = error


# --------------------------------------------------------------------------- #
# queue_op: list|get|insert|update|close over the investigations table.
# --------------------------------------------------------------------------- #
_INVESTIGATION_INSERT = """
INSERT OR IGNORE INTO investigations
  (id,kind,va,name,subsystem,mode,why_interesting,stage,status,
   block_reason,prerequisites,attempts,checkpoint,evidence_refs,
   implementer_id,adjudicator_id,created_at,updated_at,binary_sha256)
VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,datetime('now'),datetime('now'),?)"""


def _derive_inv_id(kind, va, name, subsystem):
    # type: (str, object, object, object) -> str
    leaf = name or subsystem or ""
    return "%s:%s:%s" % (kind, va or "", leaf)


def normalize_queue_va(va):
    # type: (object) -> object
    """Canonical bare-hex VA as stored in ``investigations.va``.

    The planning layer (``frontier``/``swarm``) speaks ``0x%08x`` while every
    queue row stores 8 lowercase hex characters with no prefix. Normalising at
    the queue boundary is what lets a frontier target be claimed directly
    instead of forcing each caller to re-derive an id. Returns None when the
    value is not a 32-bit address.
    """
    if va is None:
        return None
    text = str(va).strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    if len(text) != 8:
        return None
    try:
        int(text, 16)
    except ValueError:
        return None
    return text


def _find_by_dedup(conn, kind, va, sha):
    # type: (sqlite3.Connection, str, object, str) -> sqlite3.Row | None
    return conn.execute(
        "SELECT * FROM investigations WHERE kind=? "
        "AND COALESCE(va,'')=COALESCE(?,'') AND binary_sha256=? "
        "ORDER BY id LIMIT 1",
        (kind, va, sha)).fetchone()


_QUEUE_OPS = ("list", "get", "insert", "update", "claim", "close", "release",
              "unblock")
_QUEUE_WRITING_OPS = ("insert", "update", "claim", "close", "release",
                      "unblock")


def queue_op(params):
    # type: (dict) -> dict
    op = params.get("op")
    if op not in _QUEUE_OPS:
        return _err("invalid_params",
                    "'op' must be one of %s, got %r"
                    % ("|".join(_QUEUE_OPS), op))
    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        if op in ("list", "get") and (
                _missing_table(conn, "investigations")):
            return _err("empty_database",
                        "KG database has no investigations table")
        if op in _QUEUE_WRITING_OPS:
            _ensure_schema(conn)
        if op == "list":
            return _queue_list(conn, params)
        if op == "get":
            return _queue_get(conn, params)
        if op == "insert":
            return _queue_insert(conn, params)
        if op == "update":
            return _queue_update(conn, params)
        if op == "claim":
            return _queue_claim(conn, params)
        if op == "release":
            return _queue_release(conn, params)
        if op == "unblock":
            return _queue_unblock(conn, params)
        return _queue_close(conn, params)
    except (sqlite3.Error, OSError) as exc:
        return _err("db_error", "queue_op %s failed: %s" % (op, exc))
    finally:
        conn.close()


def _queue_list(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    clauses, args = [], []
    for key in ("status", "stage", "kind", "binary_sha256"):
        if params.get(key) is not None:
            clauses.append("%s=?" % key)
            args.append(params[key])
    where = (" WHERE " + " AND ".join(clauses)) if clauses else ""
    try:
        limit = int(params.get("limit", 100))
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit' must be an integer")
    if limit < 0:
        return _err("invalid_params", "'limit' must be >= 0")
    rows = conn.execute(
        "SELECT * FROM investigations%s ORDER BY id LIMIT ?" % where,
        args + [min(limit, 1000)]).fetchall()
    items = [_inv_dict(row) for row in rows]
    return {"status": "ok", "tool": "queue_op", "op": "list",
            "investigations": items, "count": len(items)}


def _queue_get(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    inv_id = params.get("id")
    if not inv_id and params.get("va"):
        # The frontier/swarm layer speaks "0x%08x"; the queue stores bare
        # 8-char hex. Accepting both here keeps one address space instead of
        # forcing every caller to re-derive the id.
        row = _queue_find_by_va(conn, params["va"],
                                params.get("binary_sha256"))
        if row is None:
            return _err("not_found",
                        "no investigation for va %r" % (params["va"],),
                        va=params["va"])
        return {"status": "ok", "tool": "queue_op", "op": "get",
                "id": row["id"], "investigation": _inv_dict(row)}
    if not inv_id:
        return _err("missing_param",
                    "queue_op get requires 'id' (or 'va')",
                    field="id")
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    if row is None:
        return _err("not_found",
                    "investigation not found: %r" % (inv_id,), id=inv_id)
    return {"status": "ok", "tool": "queue_op", "op": "get",
            "id": inv_id, "investigation": _inv_dict(row)}


def _queue_find_by_va(conn, va, sha=None):
    # type: (sqlite3.Connection, object, object) -> object
    bare = normalize_queue_va(va)
    if bare is None:
        return None
    if sha:
        return conn.execute(
            "SELECT * FROM investigations WHERE kind='function' AND va=? "
            "AND binary_sha256=? ORDER BY id LIMIT 1", (bare, sha)).fetchone()
    return conn.execute(
        "SELECT * FROM investigations WHERE kind='function' AND va=? "
        "ORDER BY id LIMIT 1", (bare,)).fetchone()


def _queue_insert(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    kind = params.get("kind")
    sha = params.get("binary_sha256")
    if kind not in _INVESTIGATION_KINDS:
        return _err("invalid_params",
                    "'kind' must be one of %s, got %r"
                    % ("/".join(_INVESTIGATION_KINDS), kind))
    if not sha:
        return _err("missing_param",
                    "queue_op insert requires 'binary_sha256' "
                    "(build identity; stale identities are preserved, "
                    "never overwritten)",
                    field="binary_sha256")
    status = params.get("status", "queued")
    if status not in _INVESTIGATION_STATUSES:
        return _err("invalid_status",
                    "unknown investigation status %r; expected one of: %s"
                    % (status, ", ".join(_INVESTIGATION_STATUSES)),
                    value=status)
    va = params.get("va")
    inv_id = params.get("id") or _derive_inv_id(
        kind, va, params.get("name"), params.get("subsystem"))
    with conn:
        cur = conn.execute(_INVESTIGATION_INSERT, (
            inv_id, kind, va, params.get("name"), params.get("subsystem"),
            params.get("mode", "replace"),
            params.get("why_interesting", ""),
            params.get("stage", "QUEUED"), status,
            params.get("block_reason"), params.get("prerequisites"),
            params.get("attempts"), params.get("checkpoint"),
            params.get("evidence_refs"), params.get("implementer_id"),
            params.get("adjudicator_id"), sha))
        if cur.rowcount == 0:
            # Dedup hit (id or the (kind, va, binary_sha256) key):
            # never overwrite, report the surviving row.
            existing = _find_by_dedup(conn, kind, va, sha)
            if existing is None:
                existing = conn.execute(
                    "SELECT * FROM investigations WHERE id=?",
                    (inv_id,)).fetchone()
            return {"status": "ok", "tool": "queue_op", "op": "insert",
                    "inserted": False,
                    "id": existing["id"] if existing else inv_id,
                    "note": "duplicate ignored: investigation with "
                            "(kind, va, binary_sha256) already queued"}
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "insert",
            "inserted": True, "id": inv_id,
            "investigation": _inv_dict(row) if row else None}


def _queue_update(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    inv_id = params.get("id")
    if not inv_id:
        return _err("missing_param", "queue_op update requires 'id'",
                    field="id")
    updates = {k: params[k] for k in _QUEUE_WRITABLE if k in params}
    unknown = [k for k in params
               if k not in _QUEUE_WRITABLE and
               k not in ("op", "id", "allow_blocked", "implementer_id",
                         "stale_after_seconds", "reason")]
    if unknown:
        return _err("invalid_params",
                    "unknown update field(s): %s; writable: %s"
                    % (", ".join(sorted(unknown)),
                       ", ".join(_QUEUE_WRITABLE)))
    if not updates:
        return _err("nothing_to_update",
                    "queue_op update requires at least one of: %s"
                    % ", ".join(_QUEUE_WRITABLE))
    if "status" in updates and \
            updates["status"] not in _INVESTIGATION_STATUSES:
        return _err("invalid_status",
                    "unknown investigation status %r; expected one of: %s"
                    % (updates["status"], ", ".join(_INVESTIGATION_STATUSES)),
                    value=updates["status"])
    if updates.get("status") == "active":
        # Activation is its own lane so the blocked/terminal/owner guards in
        # _queue_update_active stay authoritative.
        updates.setdefault("implementer_id", params.get("implementer_id"))
        return _queue_update_active(conn, inv_id, updates, params)
    return _queue_update_owned(conn, inv_id, updates, params)


def _queue_update_owned(conn, inv_id, updates, params):
    # type: (sqlite3.Connection, str, dict, dict) -> dict
    """Non-activation writes, guarded by a lease-token CAS.

    Three properties this restores, all of which the previous unguarded
    ``WHERE id=?`` write lacked:

    * a write to a row held under a lease (``status='active'``) requires
      ``implementer_id`` to equal the row's current owner, so a displaced
      worker cannot clobber its successor;
    * terminal rows are immutable, so ``done``/``dropped`` cannot be
      resurrected;
    * the compare-and-set makes concurrent writers produce exactly one winner
      instead of a silent last-write-wins.
    """
    implementer = params.get("implementer_id")
    if not isinstance(implementer, str) or not implementer.strip():
        implementer = updates.get("implementer_id")
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        if row["status"] in _TERMINAL_STATUSES:
            conn.rollback()
            return _err("already_completed",
                        "investigation %r is terminal (%s); terminal rows are "
                        "never rewritten" % (inv_id, row["status"]),
                        id=inv_id, previous_status=row["status"])
        if row["status"] == "active":
            if not isinstance(implementer, str) or not implementer.strip():
                conn.rollback()
                return _err("not_owner",
                            "investigation %r is leased by %r; a write to an "
                            "active row requires implementer_id to match the "
                            "lease holder"
                            % (inv_id, row["implementer_id"]),
                            id=inv_id,
                            implementer_id=row["implementer_id"])
            if row["implementer_id"] != implementer:
                conn.rollback()
                return _err("not_owner",
                            "investigation %r is leased by %r, not %r"
                            % (inv_id, row["implementer_id"], implementer),
                            id=inv_id,
                            implementer_id=row["implementer_id"],
                            next_action="the lease was taken over; re-read the "
                                        "row and re-plan instead of writing")
        # Ownership and status transitions have their own verbs; keeping them
        # out of a generic update is what stops the active+unowned state
        # (unrecoverable for every other op) from being expressible.
        for guarded in ("status", "implementer_id"):
            if guarded in updates:
                conn.rollback()
                return _err("invalid_params",
                            "queue_op update may not write %r; use claim, "
                            "release or close" % guarded, field=guarded)
        cursor = conn.execute(
            "UPDATE investigations SET %s, updated_at=datetime('now') "
            "WHERE id=? AND status=? AND COALESCE(implementer_id,'')=?" %
            ", ".join("%s=?" % key for key in sorted(updates)),
            [updates[key] for key in sorted(updates)] +
            [inv_id, row["status"], row["implementer_id"] or ""])
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("conflict",
                        "investigation %r changed while being written" % inv_id,
                        id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "update",
            "id": inv_id, "investigation": _inv_dict(row)}


def _queue_update_active(conn, inv_id, updates, params):
    implementer = updates.get("implementer_id")
    allow_blocked = _is_true(params.get("allow_blocked", False))
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        if not isinstance(implementer, str) or not implementer.strip():
            conn.rollback()
            return _err("missing_param",
                        "activating an investigation requires implementer_id",
                        field="implementer_id")
        if row["status"] in _TERMINAL_STATUSES:
            conn.rollback()
            return _err("already_completed",
                        "investigation %r is terminal (%s)" %
                        (inv_id, row["status"]), id=inv_id,
                        previous_status=row["status"])
        if row["status"] == "active" and row["implementer_id"] != implementer:
            conn.rollback()
            return _err("already_claimed",
                        "investigation %r already claimed by %r" %
                        (inv_id, row["implementer_id"]), id=inv_id,
                        implementer_id=row["implementer_id"])
        if row["status"] == "blocked" and not allow_blocked:
            conn.rollback()
            return _err("blocked",
                        "investigation %r is blocked; pass allow_blocked=true "
                        "to activate it" % inv_id, id=inv_id,
                        block_reason=row["block_reason"])
        updates = dict(updates)
        updates["block_reason"] = None
        cursor = conn.execute(
            "UPDATE investigations SET %s, updated_at=datetime('now') "
            "WHERE id=? AND status=? AND COALESCE(implementer_id,'')=?" %
            ", ".join("%s=?" % key for key in sorted(updates)),
            [updates[key] for key in sorted(updates)] +
            [inv_id, row["status"], row["implementer_id"] or ""])
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("already_claimed",
                        "investigation %r changed while being activated" %
                        inv_id, id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "update",
            "id": inv_id, "investigation": _inv_dict(row)}


def _claim_is_stale(updated_at, stale_after_seconds):
    # type: (object, object) -> bool
    """True when a lease clock is readable and older than the TTL.

    Fails closed: a NULL or unparseable clock is never stale, so the row stays
    locked until someone releases it explicitly. Reading the clock correctly
    matters in practice -- rows seeded outside queue_op carry ISO-8601 with a
    trailing Z, which the SQLite ``datetime('now')`` format alone would miss,
    leaving every stale takeover unreachable.
    """
    if not updated_at:
        return False
    timestamp = None
    for fmt in _LEASE_TIME_FORMATS:
        try:
            timestamp = datetime.datetime.strptime(str(updated_at), fmt)
            break
        except (TypeError, ValueError):
            continue
    if timestamp is None:
        return False
    age = (datetime.datetime.now(datetime.timezone.utc).replace(tzinfo=None) -
           timestamp).total_seconds()
    return age >= stale_after_seconds


def _lease_ttl(params):
    # type: (dict) -> object
    """Validate ``stale_after_seconds`` and return it (or an error dict)."""
    try:
        stale_after = int(params.get("stale_after_seconds", 3600))
    except (TypeError, ValueError):
        return _err("invalid_params", "stale_after_seconds must be an integer")
    if stale_after < _MIN_STALE_AFTER_SECONDS:
        return _err("invalid_params",
                    "stale_after_seconds must be >= %d (a zero-length lease "
                    "would make every held claim instantly stealable)"
                    % _MIN_STALE_AFTER_SECONDS,
                    minimum=_MIN_STALE_AFTER_SECONDS, value=stale_after)
    return stale_after


def _queue_claim(conn, params):
    inv_id = params.get("id")
    implementer = params.get("implementer_id")
    if not inv_id:
        return _err("missing_param", "queue_op claim requires 'id'",
                    field="id")
    if not isinstance(implementer, str) or not implementer.strip():
        return _err("missing_param",
                    "queue_op claim requires 'implementer_id'",
                    field="implementer_id")
    stale_after = _lease_ttl(params)
    if isinstance(stale_after, dict):
        return stale_after
    allow_stale = _is_true(params.get("allow_stale", False))
    allow_blocked = _is_true(params.get("allow_blocked", False))
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        expected_sha = params.get("binary_sha256")
        if expected_sha and expected_sha != row["binary_sha256"]:
            conn.rollback()
            return _err("stale_binary",
                        "investigation belongs to a different binary identity",
                        id=inv_id,
                        expected_binary_sha256=expected_sha,
                        actual_binary_sha256=row["binary_sha256"])
        if row["status"] in _TERMINAL_STATUSES:
            conn.rollback()
            return _err("already_completed",
                        "investigation %r is terminal (%s)" %
                        (inv_id, row["status"]), id=inv_id,
                        previous_status=row["status"])
        if row["status"] == "active":
            if row["implementer_id"] == implementer:
                conn.commit()
                return {"status": "ok", "tool": "queue_op", "op": "claim",
                        "claimed": False, "idempotent": True, "id": inv_id,
                        "investigation": _inv_dict(row)}
            stale = _claim_is_stale(row["updated_at"], stale_after)
            if not allow_stale or not stale:
                conn.rollback()
                return _err("already_claimed",
                            "investigation %r is active under %r" %
                            (inv_id, row["implementer_id"]), id=inv_id,
                            implementer_id=row["implementer_id"],
                            stale=stale,
                            stale_after_seconds=stale_after,
                            next_action="retry only after the lease is stale "
                                        "with allow_stale=true")
        if row["status"] == "blocked" and not allow_blocked:
            conn.rollback()
            return _err("blocked",
                        "investigation %r is blocked; pass allow_blocked=true "
                        "to claim it" % inv_id, id=inv_id,
                        block_reason=row["block_reason"])
        expected_status = row["status"]
        expected_owner = row["implementer_id"] or ""
        # A stale takeover silently overwrites implementer_id, which would make
        # the displacement unauditable afterwards. Record the displaced lease
        # holder in the checkpoint so recovery stays explainable.
        displaced = None
        checkpoint = row["checkpoint"]
        if expected_status == "active" and expected_owner:
            displaced = {"owner": expected_owner,
                         "displaced_at": datetime.datetime.now(
                             datetime.timezone.utc).replace(
                                 tzinfo=None).isoformat(timespec="seconds"),
                         "previous_stage": row["stage"],
                         "stale_after_seconds": stale_after}
        assignments = ["status='active'", "implementer_id=?",
                       "block_reason=NULL", "updated_at=datetime('now')"]
        values = [implementer]
        if displaced is not None:
            merged = _merge_checkpoint(checkpoint, displaced)
            assignments.append("checkpoint=?")
            values.append(merged)
        values.extend([inv_id, expected_status, expected_owner])
        cursor = conn.execute(
            "UPDATE investigations SET %s "
            "WHERE id=? AND status=? AND COALESCE(implementer_id,'')=?" %
            ", ".join(assignments), values)
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("already_claimed",
                        "investigation %r changed while being claimed" % inv_id,
                        id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    result = {"status": "ok", "tool": "queue_op", "op": "claim",
              "claimed": True, "idempotent": False, "id": inv_id,
              "investigation": _inv_dict(row) if row else None}
    if displaced is not None:
        result["displaced_owner"] = displaced
    return result


def _merge_checkpoint(raw, addition):
    # type: (object, dict) -> str
    """Fold ``addition`` into a checkpoint blob, preserving what is there.

    Whole-value overwrite on purpose: read-modify-write across a lease
    boundary is exactly the racy pattern the lease exists to prevent.
    """
    if not raw:
        current = {}
    else:
        try:
            current = json.loads(raw)
        except (TypeError, ValueError):
            current = {"unparsed_checkpoint": str(raw)[:500]}
        if not isinstance(current, dict):
            current = {"checkpoint": current}
    history = current.get("lease_history")
    if not isinstance(history, list):
        history = []
    history = (history + [addition])[-8:]
    current["lease_history"] = history
    return json.dumps(current, sort_keys=True)


def _queue_unblock(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    """Return a blocked row to ``queued``.

    Needed because ``blocked`` is deliberately fail-closed: a row parked for
    review has no lease holder, so ``release`` (which is a lease operation and
    therefore requires the holder) cannot move it, and ``close`` on a blocked
    row is an adjudication to a *terminal* state. Without this verb a blocked
    row could only ever be closed, never returned to work -- so any reason that
    turns out to be spurious (an absent validator, a mislabelled block) would
    strand the target permanently.

    There is deliberately no ownership check, because there is no owner; the
    authority is the explicit ``allow_blocked=true`` assertion plus the fact
    that the caller must name the row. ``reason`` records why the block is
    being lifted and is written to ``block_reason`` so the audit trail keeps
    the superseded reason visible until the next claim clears the column.
    """
    inv_id = params.get("id")
    if not inv_id:
        return _err("missing_param", "queue_op unblock requires 'id'",
                    field="id")
    if not _is_true(params.get("allow_blocked", False)):
        return _err("invalid_params",
                    "queue_op unblock requires allow_blocked=true; returning "
                    "blocked work to the queue is an explicit assertion, not a "
                    "side effect", field="allow_blocked")
    reason = params.get("reason")
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        if row["status"] in _TERMINAL_STATUSES:
            conn.rollback()
            return _err("already_completed",
                        "investigation %r is terminal (%s); a completed row "
                        "cannot be returned to the queue" %
                        (inv_id, row["status"]), id=inv_id,
                        previous_status=row["status"])
        if row["status"] == "active" and row["implementer_id"]:
            conn.rollback()
            return _err("already_claimed",
                        "investigation %r is leased by %r; release the lease "
                        "instead of unblocking it" %
                        (inv_id, row["implementer_id"]), id=inv_id,
                        implementer_id=row["implementer_id"])
        if row["status"] != "blocked":
            if not row["block_reason"]:
                conn.commit()
                return {"status": "ok", "tool": "queue_op", "op": "unblock",
                        "id": inv_id, "unblocked": False, "idempotent": True,
                        "previous_status": row["status"],
                        "investigation": _inv_dict(row)}
            # Not blocked by status, yet still carrying a block_reason. The
            # frontier's claim view reads a non-null block_reason as blocked
            # regardless of status, so the row is functionally blocked and
            # unblock has to clear the column. This is what makes unblock
            # converge from any half-blocked state rather than only from
            # status='blocked'.
            previous = row["block_reason"]
            merged = _merge_checkpoint(row["checkpoint"], {
                "unblocked_at": datetime.datetime.now(
                    datetime.timezone.utc).replace(tzinfo=None).isoformat(
                        timespec="seconds"),
                "superseded_block_reason": previous,
                "unblock_reason": reason,
            })
            cursor = conn.execute(
                "UPDATE investigations SET block_reason=NULL, checkpoint=?, "
                "updated_at=datetime('now') WHERE id=?",
                (merged, inv_id))
            if cursor.rowcount != 1:
                conn.rollback()
                return _err("conflict",
                            "investigation %r changed while being unblocked"
                            % inv_id, id=inv_id)
            conn.commit()
            row = conn.execute(
                "SELECT * FROM investigations WHERE id=?",
                (inv_id,)).fetchone()
            return {"status": "ok", "tool": "queue_op", "op": "unblock",
                    "id": inv_id, "unblocked": True, "idempotent": False,
                    "previous_status": row["status"],
                    "previous_block_reason": previous,
                    "investigation": _inv_dict(row)}
        previous = row["block_reason"]
        # block_reason is cleared, not overwritten: the frontier's claim view
        # treats a non-null block_reason as "still blocked", so writing the new
        # reason there would silently re-block the row this call just freed.
        # The superseded reason is preserved in the checkpoint instead.
        merged = _merge_checkpoint(row["checkpoint"], {
            "unblocked_at": datetime.datetime.now(
                datetime.timezone.utc).replace(tzinfo=None).isoformat(
                    timespec="seconds"),
            "superseded_block_reason": previous,
            "unblock_reason": reason,
        })
        cursor = conn.execute(
            "UPDATE investigations SET status='queued', block_reason=NULL, "
            "implementer_id=NULL, checkpoint=?, updated_at=datetime('now') "
            "WHERE id=? AND status='blocked'",
            (merged, inv_id))
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("conflict",
                        "investigation %r changed while being unblocked" % inv_id,
                        id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "unblock",
            "id": inv_id, "unblocked": True, "idempotent": False,
            "previous_status": "blocked", "previous_block_reason": previous,
            "investigation": _inv_dict(row)}


def _queue_close(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    inv_id = params.get("id")
    if not inv_id:
        return _err("missing_param", "queue_op close requires 'id'",
                    field="id")
    disposition = params.get("status", params.get("disposition", "done"))
    if disposition not in _TERMINAL_STATUSES:
        return _err("invalid_params",
                    "queue_op close 'status' must be one of %s, got %r"
                    % ("/".join(_TERMINAL_STATUSES), disposition))
    implementer = params.get("implementer_id")
    expected_sha = params.get("binary_sha256")
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        if row["status"] in _TERMINAL_STATUSES:
            # Terminal rows are never deleted and never re-closed: idempotent.
            conn.commit()
            return {"status": "ok", "tool": "queue_op", "op": "close",
                    "id": inv_id, "closed": False,
                    "previous_status": row["status"],
                    "investigation": _inv_dict(row)}
        if expected_sha and expected_sha != row["binary_sha256"]:
            conn.rollback()
            return _err("stale_binary",
                        "investigation belongs to a different binary identity",
                        id=inv_id,
                        expected_binary_sha256=expected_sha,
                        actual_binary_sha256=row["binary_sha256"])
        if row["status"] == "active" and row["implementer_id"] != implementer:
            conn.rollback()
            return _err("not_owner",
                        "investigation %r is leased by %r; only the lease "
                        "holder may close it" %
                        (inv_id, row["implementer_id"]), id=inv_id,
                        implementer_id=row["implementer_id"],
                        next_action="release the claim instead, or wait for "
                                    "the lease to go stale")
        if row["status"] == "blocked" and not _is_true(
                params.get("allow_blocked", False)):
            # A blocked row has no lease holder, so an ownership check cannot
            # distinguish the worker that unblocked itself from anyone else.
            # Closing a blocked row is an adjudication, not a work item, and
            # must be asserted explicitly -- otherwise a worker whose own
            # validation routed it to review could immediately close it and
            # erase the reason it was parked.
            conn.rollback()
            return _err("blocked",
                        "investigation %r is blocked; closing a blocked row "
                        "requires allow_blocked=true (it is an adjudication, "
                        "not a work item)" % inv_id, id=inv_id,
                        block_reason=row["block_reason"])
        previous = row["status"]
        cursor = conn.execute(
            "UPDATE investigations SET status=?, updated_at=datetime('now') "
            "WHERE id=? AND status=? AND COALESCE(implementer_id,'')=?",
            (disposition, inv_id, previous, row["implementer_id"] or ""))
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("conflict",
                        "investigation %r changed while being closed" % inv_id,
                        id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "close",
            "id": inv_id, "closed": True,
            "previous_status": previous,
            "investigation": _inv_dict(row)}


def _queue_release(conn, params):
    # type: (sqlite3.Connection, dict) -> dict
    """End a lease without ending the investigation.

    A distinct verb rather than ``update{status: queued}`` for three reasons:
    the compare-and-set predicate is fixed (``status='active' AND owner=?``);
    it needs a different replay contract from close and update (replay is a
    success no-op, so the orchestrator can retry it after a crash); and it
    clears the owner, which is what stops the unrecoverable
    ``active + implementer_id IS NULL`` state from being expressible.
    """
    inv_id = params.get("id")
    if not inv_id:
        return _err("missing_param", "queue_op release requires 'id'",
                    field="id")
    implementer = params.get("implementer_id")
    if not isinstance(implementer, str) or not implementer.strip():
        return _err("missing_param", "queue_op release requires "
                    "'implementer_id' (the lease holder)", field="implementer_id")
    destination = params.get("to", "queued")
    if destination not in ("queued", "blocked"):
        return _err("invalid_params",
                    "queue_op release 'to' must be queued or blocked, got %r"
                    % (destination,), value=destination)
    reason = params.get("reason")
    try:
        conn.execute("BEGIN IMMEDIATE")
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
        if row is None:
            conn.rollback()
            return _err("not_found", "investigation not found: %r" % inv_id,
                        id=inv_id)
        if row["status"] in _TERMINAL_STATUSES:
            conn.rollback()
            return _err("already_completed",
                        "investigation %r is terminal (%s); there is no lease "
                        "to release" % (inv_id, row["status"]), id=inv_id,
                        previous_status=row["status"])
        if row["status"] != "active":
            # Replay safety: releasing an unheld row is a success no-op, not
            # an error, so a retried sequence converges instead of failing.
            conn.commit()
            return {"status": "ok", "tool": "queue_op", "op": "release",
                    "id": inv_id, "released": False, "idempotent": True,
                    "to": destination, "previous_status": row["status"],
                    "investigation": _inv_dict(row)}
        if row["implementer_id"] != implementer:
            conn.rollback()
            return _err("not_owner",
                        "investigation %r is leased by %r, not %r; a lease is "
                        "never taken by releasing it"
                        % (inv_id, row["implementer_id"], implementer),
                        id=inv_id, implementer_id=row["implementer_id"],
                        next_action="claim with allow_stale=true once the lease "
                                    "is stale, or escalate to a human")
        cursor = conn.execute(
            "UPDATE investigations SET status=?, implementer_id=NULL, "
            "block_reason=?, updated_at=datetime('now') "
            "WHERE id=? AND status='active' AND COALESCE(implementer_id,'')=?",
            (destination,
             reason if destination == "blocked" else None,
             inv_id, implementer))
        if cursor.rowcount != 1:
            conn.rollback()
            return _err("conflict",
                        "investigation %r changed while being released" % inv_id,
                        id=inv_id)
        conn.commit()
    except sqlite3.Error:
        try:
            conn.rollback()
        except sqlite3.Error:
            pass
        raise
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "release",
            "id": inv_id, "released": True, "idempotent": False,
            "to": destination, "previous_status": "active",
            "investigation": _inv_dict(row)}


# --------------------------------------------------------------------------- #
# pipeline_state: read-only aggregation (KG counts + replacement statuses +
# dossier inventory). Never writes.
# --------------------------------------------------------------------------- #
def pipeline_state(params):
    # type: (dict) -> dict
    del params  # read-only aggregation takes no arguments.
    db = config.db_path()
    counts = {}
    inv_by_status = {}
    missing_tables = []
    db_exists = os.path.exists(db)
    if db_exists:
        try:
            conn = _connect()
        except sqlite3.Error as exc:
            return _err("db_unavailable",
                        "cannot open KG database: %s" % exc)
        try:
            for table in ("node", "edge", "test_result",
                          "investigations", "field", "trace_run"):
                if _missing_table(conn, table):
                    missing_tables.append(table)
                    continue
                counts[table] = conn.execute(
                    "SELECT COUNT(*) FROM %s" % table).fetchone()[0]
            if "investigations" not in missing_tables:
                for row in conn.execute(
                        "SELECT status, COUNT(*) c FROM investigations "
                        "GROUP BY status ORDER BY status").fetchall():
                    inv_by_status[row["status"]] = row["c"]
        except sqlite3.Error as exc:
            return _err("db_error", "pipeline_state failed: %s" % exc)
        finally:
            conn.close()

    status_doc = _read_replacement_status()
    dossiers = _dossier_inventory()
    result = {"status": "ok", "tool": "pipeline_state",
              "db": {"path": db, "exists": db_exists},
              "kg_counts": counts,
              "investigations_by_status": inv_by_status,
              "replacement_status": status_doc,
              "dossiers": dossiers}
    if missing_tables:
        result["missing_tables"] = sorted(missing_tables)
    return result


def _read_replacement_status():
    # type: () -> dict
    path = config.resolve("docs", "replacement-status.json")
    if not os.path.exists(path):
        return {"present": False, "path": path}
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except (OSError, ValueError) as exc:
        return {"present": False, "path": path, "error": str(exc)}
    subsystems = doc.get("subsystems", [])
    by_status = {}
    for sub in subsystems:
        by_status[sub.get("status", "?")] = \
            by_status.get(sub.get("status", "?"), 0) + 1
    return {"present": True, "path": path,
            "schema": doc.get("$schema"),
            "total": len(subsystems),
            "by_status": by_status,
            "subsystems": sorted(s.get("name", "?") for s in subsystems)}


def _dossier_inventory():
    # type: () -> dict
    pattern_json = config.resolve("docs", "analysis", "dossiers", "*.json")
    pattern_md = config.resolve("docs", "analysis", "dossiers", "*.md")
    json_files = sorted(os.path.basename(p)
                        for p in glob.glob(pattern_json))
    md_files = sorted(os.path.basename(p)
                      for p in glob.glob(pattern_md))
    return {"dir": os.path.dirname(pattern_json),
            "json": json_files, "markdown": md_files,
            "count": len(json_files) + len(md_files)}


# --------------------------------------------------------------------------- #
# target_select: read-only ranking over open investigations (S2.1 scope D).
#
# Rank order is frozen: active > queued > blocked, then ORDER BY
# stage, id (never a scoring engine). Each candidate carries
# ``why_ranked`` (its status-priority + stage, i.e. exactly the keys the
# ORDER BY ranks on). Candidate rows are slim --
# {id,kind,va,name,subsystem,mode,stage,status,why_ranked} -- and the
# candidate list is bounded by ``limit`` (default 10, cap 100) with a
# ``truncated`` flag; the full row stays available via
# ``queue_op`` op=get. The optional ``status`` filter narrows the ranked
# pool to one of active|queued|blocked. Selection is actionable: a hit
# returns select_status "selected" (+ score/filters/next_action), a miss
# returns selected None + select_status "not_found" + a hint pointing at
# ``queue_op`` op=list, and a no-target call returns select_status
# "no_target" with guidance instead of a bare selected:null.
# --------------------------------------------------------------------------- #
_TARGET_SLIM_KEYS = ("id", "kind", "va", "name", "subsystem", "mode",
                     "stage", "status")
_TARGET_STATUS_ORDER = {"active": 0, "queued": 1, "blocked": 2}
_TARGET_OPEN_STATUSES = ("active", "queued", "blocked")


def _target_why_ranked(row):
    # type: (object) -> str
    status = row["status"] if "status" in row.keys() else None
    stage = row["stage"] if "stage" in row.keys() else None
    prio = _TARGET_STATUS_ORDER.get(status, "?")
    return ("status-priority %s=%s (active=0 < queued=1 < blocked=2) + "
            "stage %s; rank ORDER BY status-priority, stage, id"
            % (status, prio, stage))


def _target_slim(row):
    # type: (sqlite3.Row) -> dict
    slim = {key: row[key] for key in _TARGET_SLIM_KEYS}
    slim["why_ranked"] = _target_why_ranked(row)
    return slim


def _target_score(row):
    # type: (object) -> int | None
    status = row["status"] if "status" in row.keys() else None
    return _TARGET_STATUS_ORDER.get(status)


def target_select(params):
    # type: (dict) -> dict
    target = params.get("target")
    status_filter = params.get("status")
    if status_filter is not None and \
            status_filter not in _TARGET_OPEN_STATUSES:
        return _err("invalid_params",
                    "'status' must be one of %s, got %r "
                    "(target_select only ranks open investigations)"
                    % ("/".join(_TARGET_OPEN_STATUSES), status_filter))
    try:
        limit = int(params.get("limit", 10))
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit' must be an integer")
    if limit < 0:
        return _err("invalid_params", "'limit' must be >= 0")
    effective = min(limit, 100)
    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        if _missing_table(conn, "investigations"):
            return _err("empty_database",
                        "KG database has no investigations table")
        clauses = ["status IN ('active','queued','blocked')"]
        args = []
        if status_filter is not None:
            clauses.append("status=?")
            args.append(status_filter)
        where = "WHERE " + " AND ".join(clauses)
        # Fetch one extra row to report truncation without dumping.
        rows = conn.execute(
            "SELECT id, kind, va, name, subsystem, mode, stage, status "
            "FROM investigations "
            "%s "
            "ORDER BY CASE status "
            "WHEN 'active' THEN 0 WHEN 'queued' THEN 1 ELSE 2 END, "
            "stage, id LIMIT ?" % where,
            args + [effective + 1]).fetchall()
        selected = None
        if target:
            match = conn.execute(
                "SELECT id, kind, va, name, subsystem, mode, stage, status "
                "FROM investigations "
                "WHERE id=? OR name=? OR va=? ORDER BY id LIMIT 1",
                (target, target, target)).fetchone()
            if match is not None:
                selected = _target_slim(match)
    except sqlite3.Error as exc:
        return _err("db_error", "target_select failed: %s" % exc)
    finally:
        conn.close()
    truncated = len(rows) > effective
    candidates = [_target_slim(row) for row in rows[:effective]]
    filters = {"status": status_filter}
    result = {"status": "ok", "tool": "target_select",
              "candidates": candidates, "count": len(candidates),
              "truncated": truncated, "filters": filters}
    if target is not None:
        result["target"] = target
    if selected is not None:
        result["selected"] = selected
        result["select_status"] = "selected"
        result["score"] = _target_score(selected)
        result["reason"] = ("target %r resolved to investigation %r "
                            "(status %s, stage %s)"
                            % (target, selected["id"],
                               selected["status"], selected["stage"]))
        result["next_action"] = (
            "queue_op op=get id=%r for the full row" % (selected["id"],))
    elif target is not None:
        result["selected"] = None
        result["select_status"] = "not_found"
        result["score"] = None
        result["reason"] = ("target %r matches no investigation "
                            "(searched id, name, va)" % (target,))
        result["hint"] = ("call queue_op op=list to browse available "
                          "targets, then retry target_select with an "
                          "id, name, or va from that list")
        result["next_action"] = result["hint"]
    else:
        result["selected"] = None
        result["select_status"] = "no_target"
        result["score"] = None
        top = candidates[0]["id"] if candidates else None
        result["reason"] = (
            "no target given; showing top-%d ranked open "
            "investigation(s)%s" % (
                len(candidates),
                (" (status filter: %s)" % status_filter)
                if status_filter is not None else ""))
        result["hint"] = (
            "pass 'target' (an id, name, or va%s) or call queue_op "
            "op=list to browse; full rows via queue_op op=get" % (
                " matching status=%s" % status_filter
                if status_filter is not None else
                " from the candidates above",))
        result["next_action"] = (
            "target_select target=%r to select the top-ranked candidate"
            % (top,) if top is not None else
            "queue_op op=list to browse; queue_op op=insert to add work")
    return result
