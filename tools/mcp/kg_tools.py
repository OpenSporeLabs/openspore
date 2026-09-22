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
    conn = sqlite3.connect(db)
    conn.row_factory = sqlite3.Row
    return conn


def _missing_table(conn, name):
    # type: (sqlite3.Connection, str) -> bool
    row = conn.execute(
        "SELECT 1 FROM sqlite_master WHERE type='table' AND name=?",
        (name,)).fetchone()
    return row is None


def _ensure_schema(conn):
    # type: (sqlite3.Connection) -> None
    """Create sidecar tables if absent (idempotent; write paths only)."""
    schema = config.resolve("knowledgegraph", "schema.sql")
    with open(schema) as fh:
        conn.executescript(fh.read())


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


def _find_by_dedup(conn, kind, va, sha):
    # type: (sqlite3.Connection, str, object, str) -> sqlite3.Row | None
    return conn.execute(
        "SELECT * FROM investigations WHERE kind=? "
        "AND COALESCE(va,'')=COALESCE(?,'') AND binary_sha256=? "
        "ORDER BY id LIMIT 1",
        (kind, va, sha)).fetchone()


def queue_op(params):
    # type: (dict) -> dict
    op = params.get("op")
    if op not in ("list", "get", "insert", "update", "close"):
        return _err("invalid_params",
                    "'op' must be one of list|get|insert|update|close, "
                    "got %r" % (op,))
    try:
        conn = _connect()
    except sqlite3.Error as exc:
        return _err("db_unavailable", "cannot open KG database: %s" % exc)
    try:
        if op in ("list", "get") and (
                _missing_table(conn, "investigations")):
            return _err("empty_database",
                        "KG database has no investigations table")
        if op in ("insert", "update", "close"):
            _ensure_schema(conn)
        if op == "list":
            return _queue_list(conn, params)
        if op == "get":
            return _queue_get(conn, params)
        if op == "insert":
            return _queue_insert(conn, params)
        if op == "update":
            return _queue_update(conn, params)
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
    if not inv_id:
        return _err("missing_param",
                    "queue_op get requires 'id'",
                    field="id")
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    if row is None:
        return _err("not_found",
                    "investigation not found: %r" % (inv_id,), id=inv_id)
    return {"status": "ok", "tool": "queue_op", "op": "get",
            "investigation": _inv_dict(row)}


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
               if k not in _QUEUE_WRITABLE and k not in ("op", "id")]
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
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    if row is None:
        return _err("not_found",
                    "investigation not found: %r" % (inv_id,), id=inv_id)
    if updates.get("status") == "active" and row["status"] == "active" \
            and row["implementer_id"] \
            and updates.get("implementer_id") \
            and updates["implementer_id"] != row["implementer_id"]:
        return _err("already_claimed",
                    "investigation %r already claimed by %r"
                    % (inv_id, row["implementer_id"]), id=inv_id)
    with conn:
        conn.execute(
            "UPDATE investigations SET %s, updated_at=datetime('now') "
            "WHERE id=?" % ", ".join("%s=?" % k for k in sorted(updates)),
            [updates[k] for k in sorted(updates)] + [inv_id])
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "update",
            "id": inv_id, "investigation": _inv_dict(row)}


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
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    if row is None:
        return _err("not_found",
                    "investigation not found: %r" % (inv_id,), id=inv_id)
    if row["status"] in _TERMINAL_STATUSES:
        # Terminal rows are never deleted and never re-closed: idempotent.
        return {"status": "ok", "tool": "queue_op", "op": "close",
                "id": inv_id, "closed": False,
                "previous_status": row["status"],
                "investigation": _inv_dict(row)}
    previous = row["status"]
    with conn:
        conn.execute(
            "UPDATE investigations SET status=?, updated_at=datetime('now') "
            "WHERE id=?", (disposition, inv_id))
    row = conn.execute(
        "SELECT * FROM investigations WHERE id=?", (inv_id,)).fetchone()
    return {"status": "ok", "tool": "queue_op", "op": "close",
            "id": inv_id, "closed": True,
            "previous_status": previous,
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
