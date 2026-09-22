#!/usr/bin/env python3
"""Read-only query layer for the OpenSpore knowledge-graph viewer (stdlib only).

All SQL lives here, explicit and parameterized. The DB is opened per call in
strict read-only mode: ``sqlite3.connect("file:<abs>?mode=ro", uri=True)``;
if that fails (stale -shm side-file, live writer lock) we retry with
``?mode=ro&immutable=1``. Trade-off: immutable=1 skips uncommitted WAL pages;
that is safe here because the committed DB is checkpointed (-wal is 0 bytes)
and the viewer is a pure reader. A missing DB or an unmigrated schema degrades
to structured "degraded" envelopes -- never a traceback, never a 500.

The 7-level evidence scale is imported from knowledgegraph/scale.py (single
source of truth) with an ImportError fallback, mirroring tools/mcp/kg_tools.py.

Run as a CLI:
    python3 tools/viewer/query.py summary
    python3 tools/viewer/query.py nodes --label Function --q 00e5b790
    python3 tools/viewer/query.py node fun:00e5b790
"""
import argparse
import json
import os
import sqlite3
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_HERE))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

try:
    # Single source of truth for the 7-level scale.
    from knowledgegraph.scale import EV  # noqa: F401
    from knowledgegraph.scale import EV_ORDER
except ImportError:  # off-repo-root fallback (mirror tools/mcp/kg_tools.py)
    EV = {"UNKNOWN": 0.0, "APPROXIMATION": 0.3, "INFERRED": 0.5,
          "SUPPORTED": 0.75, "OBSERVED": 0.85, "CONFIRMED": 0.9,
          "VERIFIED": 1.0}
    EV_ORDER = ("UNKNOWN", "APPROXIMATION", "INFERRED",
                "SUPPORTED", "OBSERVED", "CONFIRMED", "VERIFIED")

_MARKERS = ("opencode.json", ".git", "knowledgegraph")
_TABLES = ("node", "edge", "test_result", "field", "trace_run",
           "investigations")


def find_repo_root(start=None):
    env = os.environ.get("OPENSPORE_ROOT")
    if env and os.path.isdir(env):
        return os.path.abspath(env)
    cur = os.path.abspath(start or _HERE)
    while True:
        for marker in _MARKERS:
            if os.path.exists(os.path.join(cur, marker)):
                return cur
        parent = os.path.dirname(cur)
        if parent == cur:
            return os.path.abspath(os.path.join(_HERE, "..", ".."))
        cur = parent


def db_path(cli_db=None):
    """OPENSPORE_DB env wins; --db wins over the default. Abs as-is, rel vs root."""
    raw = cli_db or os.environ.get("OPENSPORE_DB")
    root = find_repo_root()
    if raw:
        if os.path.isabs(raw):
            return os.path.normpath(raw)
        return os.path.normpath(os.path.join(root, raw))
    return os.path.normpath(os.path.join(root, "knowledgegraph", "spore.db"))


# --------------------------------------------------------------------------- #
# Envelopes
# --------------------------------------------------------------------------- #
def _ok(**payload):
    out = dict(payload)
    out["status"] = "ok"  # set last: the envelope field always wins
    return out


def _err(code, message, **extra):
    out = {"status": "error", "code": code, "message": message}
    out.update(extra)
    return out


def _degraded(code, message, probe, **extra):
    out = {"status": "degraded", "code": code, "message": message,
           "probe": probe}
    out.update(extra)
    return out


def _parse_jsonish(raw):
    if not isinstance(raw, str) or not raw.strip():
        return None
    try:
        return json.loads(raw)
    except ValueError:
        return raw


# --------------------------------------------------------------------------- #
# Read-only connection + FeatureProbe
# --------------------------------------------------------------------------- #
def _connect(path):
    """Open read-only per call; None if the file is missing/unopenable.

    Primary: ?mode=ro. Fallback: ?mode=ro&immutable=1 (skips uncommitted
    WAL pages; safe because the committed DB is checkpointed, -wal = 0 B).
    """
    abs_path = os.path.abspath(path)
    if not os.path.isfile(abs_path):
        return None
    for suffix in ("?mode=ro", "?mode=ro&immutable=1"):
        try:
            conn = sqlite3.connect("file:" + abs_path + suffix, uri=True)
            conn.row_factory = sqlite3.Row
            return conn
        except sqlite3.OperationalError:
            continue
    return None


def probe(path=None):
    """Startup/first-use probe: exists? migrated? which tables? user_version?"""
    p = db_path(path)
    out = {"db_path": p, "exists": os.path.isfile(p), "schema": "missing"}
    if not out["exists"]:
        return out
    conn = _connect(p)
    if conn is None:
        out["schema"] = "unopenable"
        return out
    try:
        node_cols = [r["name"] for r in conn.execute("PRAGMA table_info(node)")]
        tables = {r["name"] for r in conn.execute(
            "SELECT name FROM sqlite_master WHERE type='table'")}
        out["user_version"] = conn.execute("PRAGMA user_version").fetchone()[0]
        out["tables"] = sorted(tables & set(_TABLES))
        out["missing_tables"] = [t for t in _TABLES if t not in tables]
        out["schema"] = ("ok" if node_cols and not out["missing_tables"]
                         else "unmigrated")
    finally:
        conn.close()
    return out


def _open(db=None):
    """Return (conn, None) on a migrated DB, or (None, degraded-envelope)."""
    path = db_path(db)
    pr = probe(path)
    if pr["schema"] == "missing":
        return None, _degraded("db_missing",
                               "knowledge graph database not found at %s" % path,
                               pr)
    conn = _connect(path)
    if conn is None:
        return None, _degraded("db_unopenable",
                               "database at %s could not be opened read-only" % path,
                               pr)
    if pr["schema"] != "ok":
        conn.close()
        return None, _degraded("schema_unmigrated",
                               "database at %s is missing tables: %s"
                               % (path, ", ".join(pr["missing_tables"])), pr)
    return conn, None


# --------------------------------------------------------------------------- #
# Queries
# --------------------------------------------------------------------------- #
def _node_row(row):
    return {"id": row["id"], "label": row["label"], "name": row["name"],
            "evidence_level": row["evidence_level"], "origin": row["origin"],
            "confidence": row["confidence"], "updated_at": row["updated_at"],
            "binary_sha256": row["binary_sha256"],
            "attrs": _parse_jsonish(row["attrs_json"]) or {}}


def summary(db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        counts = {}
        for table in _TABLES:
            counts[table] = conn.execute(
                "SELECT COUNT(*) FROM %s" % table).fetchone()[0]
        builds = conn.execute(
            "SELECT COUNT(DISTINCT binary_sha256) FROM node"
            " WHERE binary_sha256 IS NOT NULL").fetchone()[0]
        return _ok(db_path=db_path(db), db_exists=True,
                   user_version=probe(db)["user_version"],
                   counts=counts, distinct_builds=builds)
    finally:
        conn.close()


def evidence_distribution(db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        counts = {level: 0 for level in EV_ORDER}
        other = {}
        for level, n in conn.execute(
                "SELECT evidence_level, COUNT(*) FROM node"
                " GROUP BY evidence_level").fetchall():
            if level in counts:
                counts[level] = n
            else:
                other[level] = n
        return _ok(dist=counts, total=sum(counts.values()),
                   off_scale=other)
    finally:
        conn.close()


def node_label_distribution(db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        dist = {}
        for label, n in conn.execute(
                "SELECT label, COUNT(*) FROM node"
                " GROUP BY label ORDER BY COUNT(*) DESC, label").fetchall():
            dist[label] = n
        return _ok(dist=dist, total=sum(dist.values()))
    finally:
        conn.close()


def investigation_status_distribution(db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        status = dict(conn.execute(
            "SELECT status, COUNT(*) FROM investigations"
            " GROUP BY status ORDER BY status").fetchall())
        stage = dict(conn.execute(
            "SELECT stage, COUNT(*) FROM investigations"
            " GROUP BY stage ORDER BY stage").fetchall())
        # "status_counts"/"stage_counts": the bare "status"/"stage" payload
        # keys would be shadowed by the envelope's "status" field in _ok().
        return _ok(status_counts=status, stage_counts=stage,
                    total=sum(status.values()))
    finally:
        conn.close()


def investigations_list(kind=None, q=None, status=None,
                        limit=200, offset=0, db=None):
    """Paged read-only investigations list/search (parameterized SQL).

    Explicit columns only; q substring-matches name OR va (escaped LIKE,
    same convention as nodes()). Backs the function view's per-function
    investigation-state join.
    """
    try:
        limit, offset = int(limit), int(offset)
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit'/'offset' must be integers")
    if limit <= 0 or offset < 0:
        return _err("invalid_params", "'limit' must be > 0, 'offset' >= 0")
    limit = min(limit, 1000)
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        clauses, args = [], []
        if kind is not None:
            clauses.append("kind=?")
            args.append(kind)
        if status is not None:
            clauses.append("status=?")
            args.append(status)
        if q is not None:
            esc = (str(q).replace("\\", "\\\\").replace("%", "\\%")
                   .replace("_", "\\_"))
            clauses.append(
                "(name LIKE ? ESCAPE '\\' OR va LIKE ? ESCAPE '\\')")
            args += ["%" + esc + "%", "%" + esc + "%"]
        where = (" WHERE " + " AND ".join(clauses)) if clauses else ""
        total = conn.execute(
            "SELECT COUNT(*) FROM investigations%s" % where,
            args).fetchone()[0]
        rows = conn.execute(
            "SELECT id, kind, va, name, subsystem, stage, status,"
            " block_reason, updated_at FROM investigations%s"
            " ORDER BY id LIMIT ? OFFSET ?" % where,
            args + [limit, offset]).fetchall()
        return _ok(total=total, limit=limit, offset=offset,
                   investigations=[dict(r) for r in rows])
    finally:
        conn.close()


_MAX_KEYS = 200


def investigations_by_keys(keys, db=None):
    """Bounded exact-match investigation lookup for client-side joins.

    ``keys``: iterable of raw keys (lowercased names / va sans 0x prefix);
    matches ``va IN (keys) OR name IN (keys)`` in ONE parameterized query.
    Capped at _MAX_KEYS unique entries so the payload stays bounded by the
    requesting page, never by table size.
    """
    seen, uniq = set(), []
    for k in keys:
        k = str(k).strip()
        if k and k not in seen:
            seen.add(k)
            uniq.append(k)
    uniq = uniq[:_MAX_KEYS]
    if not uniq:
        return _ok(total=0, keys=0, investigations=[])
    marks = ",".join("?" * len(uniq))
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        rows = conn.execute(
            "SELECT id, kind, va, name, subsystem, stage, status,"
            " block_reason, updated_at FROM investigations"
            " WHERE va IN (%s) OR name IN (%s)" % (marks, marks),
            uniq + uniq).fetchall()
        return _ok(total=len(rows), keys=len(uniq),
                   investigations=[dict(r) for r in rows])
    finally:
        conn.close()


def subsystem_summary(db=None):
    """Subsystem nodes + related investigations (subsystem stem or node name)."""
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        # One LEFT JOIN: per-subsystem rollup without fetching every
        # investigation row (substr(name,5) == name[4:] strips "sub:").
        rows = conn.execute(
            "SELECT s.name AS name, i.status AS status, COUNT(i.id) AS n"
            " FROM node s LEFT JOIN investigations i"
            " ON i.subsystem = CASE WHEN s.name LIKE 'sub:%'"
            " THEN substr(s.name, 5) ELSE s.name END"
            " OR i.name = s.name"
            " WHERE s.label='Subsystem' GROUP BY s.name, i.status"
            " ORDER BY s.name, i.status").fetchall()
        by_sub = {}
        for r in rows:
            by_sub.setdefault(r["name"], {})[r["status"]] = r["n"]
        subs = []
        for row in conn.execute(
                "SELECT * FROM node WHERE label='Subsystem'"
                " ORDER BY name").fetchall():
            dist = by_sub.get(row["name"], {})
            node = _node_row(row)
            node["investigations"] = sum(dist.values())
            node["investigations_by_status"] = dist
            subs.append(node)
        return _ok(subsystems=subs)
    finally:
        conn.close()


def nodes(label=None, q=None, limit=200, offset=0, db=None):
    try:
        limit, offset = int(limit), int(offset)
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit'/'offset' must be integers")
    if limit <= 0 or offset < 0:
        return _err("invalid_params", "'limit' must be > 0, 'offset' >= 0")
    limit = min(limit, 1000)
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        clauses, args = [], []
        if label is not None:
            clauses.append("label=?")
            args.append(label)
        if q is not None:
            esc = (str(q).replace("\\", "\\\\").replace("%", "\\%")
                   .replace("_", "\\_"))
            clauses.append("name LIKE ? ESCAPE '\\'")
            args.append("%" + esc + "%")
        where = (" WHERE " + " AND ".join(clauses)) if clauses else ""
        total = conn.execute(
            "SELECT COUNT(*) FROM node%s" % where, args).fetchone()[0]
        rows = conn.execute(
            "SELECT * FROM node%s ORDER BY label, name LIMIT ? OFFSET ?"
            % where, args + [limit, offset]).fetchall()
        return _ok(total=total, limit=limit, offset=offset,
                   nodes=[_node_row(r) for r in rows])
    finally:
        conn.close()


def _resolve_node(conn, ref):
    if str(ref).isdigit():
        row = conn.execute("SELECT * FROM node WHERE id=?",
                           (ref,)).fetchone()
        if row is None:
            return None, _err("not_found", "no node with id %s" % ref)
        return row, None
    rows = conn.execute(
        "SELECT * FROM node WHERE name=? ORDER BY label, id",
        (str(ref),)).fetchall()
    if not rows:
        return None, _err("not_found", "no node named %r" % ref)
    if len(rows) > 1:
        return None, _err(
            "ambiguous", "name %r matches %d labels" % (ref, len(rows)),
            labels=[r["label"] for r in rows])
    return rows[0], None


def node_detail(ref, db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        row, bad = _resolve_node(conn, ref)
        if bad:
            return bad
        node = _node_row(row)
        node["note"] = row["note"]
        node["created_at"] = row["created_at"]
        fields = [dict(f) for f in conn.execute(
            "SELECT * FROM field WHERE struct_id=? ORDER BY id",
            (row["id"],))]
        va_candidates = {row["name"]}
        for key in ("address", "rva"):
            val = node["attrs"].get(key)
            if isinstance(val, str):
                va_candidates.add(val[2:] if val.lower().startswith("0x")
                                  else val)
        # Bounded: one parameterized query over the <=3 candidate keys,
        # never a full-table scan (exact match, same semantics as before).
        cands = sorted(va_candidates)
        marks = ",".join("?" * len(cands))
        invs = [dict(iv) for iv in conn.execute(
            "SELECT id, kind, va, name, subsystem, mode, stage, status,"
            " binary_sha256 FROM investigations"
            " WHERE name = ? OR va IN (%s)" % marks,
            [row["name"]] + cands)]
        out = _ok(node=node, fields=fields, investigations=invs)
        if isinstance(node["attrs"], dict):
            out["provenance"] = {
                "origin": row["origin"],
                "binary_sha256": row["binary_sha256"],
                "src_ref": node["attrs"].get("src"),
                "dossier": node["attrs"].get("dossier"),
                "address": node["attrs"].get("address"),
                "rva": node["attrs"].get("rva"),
                "sdk_name": node["attrs"].get("sdk_name"),
            }
        return out
    finally:
        conn.close()


def node_neighbors(ref, depth=1, db=None):
    if depth not in (1, 2):
        return _err("invalid_params", "'depth' must be 1 or 2")
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        row, bad = _resolve_node(conn, ref)
        if bad:
            return bad
        visited = {row["id"]: 0}
        frontier = {row["id"]}
        edges, seen_edges = [], set()
        for d in range(1, depth + 1):
            if not frontier:
                break
            marks = ",".join("?" * len(frontier))
            rows = conn.execute(
                "SELECT id, src, dst, rel FROM edge"
                " WHERE src IN (%s) OR dst IN (%s) ORDER BY id"
                % (marks, marks), list(frontier) + list(frontier)).fetchall()
            next_frontier = set()
            for e in rows:
                if e["id"] not in seen_edges:
                    seen_edges.add(e["id"])
                    edges.append({"id": e["id"], "src": e["src"],
                                  "dst": e["dst"], "rel": e["rel"]})
                for a, b in ((e["src"], e["dst"]), (e["dst"], e["src"])):
                    if a in frontier and b not in visited:
                        visited[b] = d
                        next_frontier.add(b)
            frontier = next_frontier
        marks = ",".join("?" * len(visited))
        found = {r["id"] for r in conn.execute(
            "SELECT id FROM node WHERE id IN (%s)" % marks,
            list(visited))}
        nodes_out = [_node_row(r) for r in conn.execute(
            "SELECT * FROM node WHERE id IN (%s) ORDER BY label, name"
            % marks, sorted(found))]
        return _ok(node=_node_row(row), depth=depth,
                   nodes=nodes_out, edges=edges)
    finally:
        conn.close()


def investigation_detail(inv_id, db=None):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        row = conn.execute(
            "SELECT * FROM investigations WHERE id=?",
            (str(inv_id),)).fetchone()
        if row is None:
            return _err("not_found",
                        "no investigation with id %r" % inv_id)
        inv = dict(row)
        for key in ("prerequisites", "attempts", "checkpoint",
                    "evidence_refs"):
            if inv.get(key) is not None:
                inv[key] = _parse_jsonish(inv[key])
        return _ok(investigation=inv)
    finally:
        conn.close()


# --------------------------------------------------------------------------- #
# CLI
# --------------------------------------------------------------------------- #
def main(argv=None):
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("command", choices=[
        "summary", "evidence", "labels", "investigations",
        "investigations-list", "subsystems",
        "nodes", "node", "neighbors", "investigation"])
    ap.add_argument("ref", nargs="?", help="node id/name or investigation id")
    ap.add_argument("--db", default=None, help="DB path (abs, or rel vs repo root)")
    ap.add_argument("--label", default=None)
    ap.add_argument("--q", default=None)
    ap.add_argument("--limit", type=int, default=200)
    ap.add_argument("--offset", type=int, default=0)
    ap.add_argument("--depth", type=int, default=1)
    ap.add_argument("--kind", default=None)
    ap.add_argument("--status", default=None)
    args = ap.parse_args(argv)
    if args.command in ("node", "neighbors", "investigation") and not args.ref:
        ap.error("%s requires a ref" % args.command)
    if args.command == "summary":
        result = summary(args.db)
    elif args.command == "evidence":
        result = evidence_distribution(args.db)
    elif args.command == "labels":
        result = node_label_distribution(args.db)
    elif args.command == "investigations":
        result = investigation_status_distribution(args.db)
    elif args.command == "investigations-list":
        result = investigations_list(args.kind, args.q, args.status,
                                     args.limit, args.offset, args.db)
    elif args.command == "subsystems":
        result = subsystem_summary(args.db)
    elif args.command == "nodes":
        result = nodes(args.label, args.q, args.limit, args.offset, args.db)
    elif args.command == "node":
        result = node_detail(args.ref, args.db)
    elif args.command == "neighbors":
        result = node_neighbors(args.ref, args.depth, args.db)
    else:
        result = investigation_detail(args.ref, args.db)
    print(json.dumps(result, indent=2, sort_keys=True))
    return 0 if result.get("status") == "ok" else 1


if __name__ == "__main__":
    sys.exit(main())
