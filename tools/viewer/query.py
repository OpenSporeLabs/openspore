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
from collections import Counter
from functools import lru_cache

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
_OPTIONAL_TABLES = ("triage", "xref")
_MAX_LIMIT = 1000
_MAX_GRAPH_NODES = 500
_MAX_GRAPH_EDGES = 2000
_MAX_ITEMS = 500
_MAX_DETAIL_ITEMS = 100
_MARK_CHUNK = 400
_READINESS_ARTIFACT = "knowledgegraph/triage/reconstruction-readiness-f0e310e0.json"
_CANONICAL_LEDGER = "knowledgegraph/research/track-b-function-accounting.jsonl"
_CANONICAL_SUMMARY = "knowledgegraph/research/global-campaign-2026/track-b-function-accounting.json"
_PACKAGE_ARTIFACT = "knowledgegraph/research/global-campaign-2026/track-o-packages-testability.json"
_RESEARCH_EVENTS = "knowledgegraph/research/gameplay-state-machines.json"
_SIMULATOR_ARTIFACT = "knowledgegraph/triage/simulator-shared-state-interface-f0e310e0.json"


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
    if raw is None:
        return None
    if not isinstance(raw, str):
        return raw
    if not raw.strip():
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
        conn = None
        try:
            conn = sqlite3.connect("file:" + abs_path + suffix, uri=True)
            conn.row_factory = sqlite3.Row
            conn.execute("PRAGMA query_only=ON")
            return conn
        except sqlite3.Error:
            if conn is not None:
                conn.close()
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
        out["optional_tables"] = sorted(tables & set(_OPTIONAL_TABLES))
        out["missing_tables"] = [t for t in _TABLES if t not in tables]
        out["optional_missing"] = [t for t in _OPTIONAL_TABLES
                                   if t not in tables]
        out["schema"] = ("ok" if node_cols and not out["missing_tables"]
                         else "unmigrated")
    except sqlite3.Error:
        out["schema"] = "unopenable"
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
                               % (path, ", ".join(pr.get("missing_tables", []))), pr)
    return conn, None


def _has_table(conn, name):
    return conn.execute(
        "SELECT 1 FROM sqlite_master WHERE type='table' AND name=?",
        (name,)).fetchone() is not None


def _has_column(conn, table, column):
    return any(r["name"] == column for r in conn.execute(
        "PRAGMA table_info(%s)" % table))


def _page(limit=200, offset=0, default=200, maximum=_MAX_LIMIT):
    try:
        limit, offset = int(limit), int(offset)
    except (TypeError, ValueError):
        return None, _err("invalid_params", "'limit'/'offset' must be integers")
    if limit <= 0 or offset < 0:
        return None, _err("invalid_params", "'limit' must be > 0, 'offset' >= 0")
    return (min(limit, maximum), offset), None


def _like(value):
    return str(value).replace("\\", "\\\\").replace("%", "\\%").replace("_", "\\_")


def _chunks(values, size=_MARK_CHUNK):
    values = list(values)
    return [values[i:i + size] for i in range(0, len(values), size)]


def _artifact_path(relative):
    return os.path.join(find_repo_root(), *relative.split("/"))


def _load_json_artifact_cached(path, _mtime_ns, _size):
    try:
        with open(path, "r", encoding="utf-8") as handle:
            value = json.load(handle)
    except (OSError, ValueError) as exc:
        return {"available": False, "reason": type(exc).__name__}
    if not isinstance(value, dict):
        return {"available": False, "reason": "not_an_object"}
    return {"available": True, "value": value}


def _load_json_artifact(relative):
    path = _artifact_path(relative)
    if not os.path.isfile(path):
        return {"available": False, "source": relative, "reason": "missing"}
    stat = os.stat(path)
    loaded = _load_json_artifact_cached(path, stat.st_mtime_ns, stat.st_size)
    loaded["source"] = relative
    loaded["source_refs"] = [relative]
    return loaded


def _source_refs(*values):
    refs = []
    seen = set()
    pending = list(values)
    while pending:
        value = pending.pop(0)
        if isinstance(value, (list, tuple)):
            pending[0:0] = list(value)
            continue
        if isinstance(value, str):
            candidates = [value]
        elif isinstance(value, dict):
            candidates = [value.get(key) for key in ("path", "ref", "source")]
        else:
            candidates = []
        for candidate in candidates:
            if not isinstance(candidate, str) or not candidate:
                continue
            for part in candidate.split(","):
                part = part.strip()
                if part and part not in seen:
                    seen.add(part)
                    refs.append(part)
    return refs


def _bounded(value, limit):
    if isinstance(value, list):
        return value[:limit]
    if isinstance(value, tuple):
        return list(value[:limit])
    return value


def _normalize_va(value):
    value = str(value or "").strip().lower()
    return value[2:] if value.startswith("0x") else value


def _va_candidates(value):
    text = str(value or "").strip().lower()
    if text.startswith("fun:"):
        text = text[4:]
    if text.startswith("0x"):
        text = text[2:]
    if text and len(text) <= 16 and all(char in "0123456789abcdef" for char in text):
        return [text]
    return []


def _readiness_data():
    loaded = _load_json_artifact(_READINESS_ARTIFACT)
    if not loaded.get("available"):
        return {"available": False, "per_function_available": False,
                "source": _READINESS_ARTIFACT,
                "source_refs": [_READINESS_ARTIFACT],
                "states": [], "counts": {}, "functions": {}}
    value = loaded["value"]
    queue = value.get("queue")
    if not isinstance(queue, dict):
        return {"available": False, "per_function_available": False,
                "source": _READINESS_ARTIFACT,
                "source_refs": [_READINESS_ARTIFACT],
                "reason": "missing_queue", "states": [], "counts": {},
                "functions": {}}
    rows = queue.get("per_function")
    per_function = rows if isinstance(rows, list) else []
    by_va = {}
    counts = Counter()
    for row in per_function:
        if not isinstance(row, dict):
            continue
        status = row.get("readiness")
        if isinstance(status, dict):
            status = status.get("status")
        if not isinstance(status, str) or not status:
            continue
        va = _normalize_va(row.get("va"))
        if not va:
            continue
        by_va[va] = row
        counts[status] += 1
    declared = []
    for status in queue.get("readiness_vocabulary", []):
        if isinstance(status, str) and status not in declared:
            declared.append(status)
    declared_counts = queue.get("by_readiness")
    if not isinstance(declared_counts, dict):
        declared_counts = {}
    for status, count in declared_counts.items():
        if isinstance(status, str) and status not in declared:
            declared.append(status)
    for status in sorted(counts):
        if status not in declared:
            declared.append(status)
    meta = value.get("meta") if isinstance(value.get("meta"), dict) else {}
    return {"available": True, "per_function_available": bool(per_function),
            "source": _READINESS_ARTIFACT,
            "source_refs": [_READINESS_ARTIFACT],
            "snapshot": meta.get("snapshot"),
            "states": declared, "counts": dict(counts),
            "declared_counts": dict(declared_counts),
            "functions": by_va, "total": len(by_va)}


def _package_clusters():
    loaded = _load_json_artifact(_PACKAGE_ARTIFACT)
    if not loaded.get("available"):
        return {}
    partition = loaded["value"].get("campaign_partition")
    if not isinstance(partition, dict):
        return {}
    result = {}
    for row in partition.get("cluster_coverage", []):
        if not isinstance(row, dict):
            continue
        cluster = row.get("cluster")
        owner = row.get("owner")
        if not isinstance(cluster, str) or not isinstance(owner, str):
            continue
        packages = []
        for token in owner.replace(" and ", ",").split(","):
            token = token.strip()
            if token.startswith("PKG-") and token not in packages:
                packages.append(token)
        result[cluster] = packages
    return result


def _compact_canonical_function(row, package_map):
    va = _normalize_va(row.get("va"))
    triage = row.get("triage") if isinstance(row.get("triage"), dict) else {}
    evidence = row.get("evidence") if isinstance(row.get("evidence"), dict) else {}
    sdk = row.get("sdk_vtable") if isinstance(row.get("sdk_vtable"), dict) else {}
    decomp = row.get("decomp") if isinstance(row.get("decomp"), dict) else {}
    xref = row.get("xref") if isinstance(row.get("xref"), dict) else {}
    packages = list(package_map.get(row.get("cluster"), []))
    kg_node_id = triage.get("kg_node_id") or ("fun:" + va if va else None)
    sources = _source_refs(
        "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
        _CANONICAL_LEDGER)
    return {
        "id": kg_node_id,
        "va": va,
        "address": va,
        "name": row.get("name"),
        "ghidra_name": row.get("name"),
        "sdk_name": sdk.get("sdk_name") or triage.get("sdk_name"),
        "category": row.get("category"),
        "cluster": row.get("cluster"),
        "subsystem": row.get("subsystem"),
        "package": packages[0] if packages else row.get("category"),
        "packages": packages or ([row.get("category")] if row.get("category") else []),
        "package_kind": "reconstruction_package" if packages else "triage_category",
        "priority": triage.get("priority"),
        "evidence": evidence.get("name_level"),
        "evidence_level": evidence.get("name_level"),
        "caller_count": row.get("caller_count"),
        "callee_count": row.get("callee_count"),
        "struct_names": list(sdk.get("struct_names") or []),
        "vtable_addrs": list(sdk.get("vtable_addrs") or []),
        "decomp_path": triage.get("decomp_path") or decomp.get("path"),
        "decomp_available": decomp.get("available"),
        "gameplay_affinity": row.get("gameplay_affinity"),
        "contract_status": row.get("contract_status"),
        "infrastructure": row.get("infrastructure_or_third_party"),
        "reconstruction_relevance": row.get("reconstruction_relevance"),
        "unresolved_reason": list(row.get("unresolved_reason") or []),
        "provenance": row.get("provenance"),
        "xref": xref,
        "source_refs": sources,
    }


@lru_cache(maxsize=4)
def _load_canonical_ledger_cached(path, _mtime_ns, _size):
    package_map = _package_clusters()
    records = []
    try:
        with open(path, "r", encoding="utf-8") as handle:
            for line in handle:
                try:
                    row = json.loads(line)
                except ValueError:
                    continue
                if isinstance(row, dict) and _normalize_va(row.get("va")):
                    records.append(_compact_canonical_function(row, package_map))
    except OSError as exc:
        return {"available": False, "reason": type(exc).__name__, "rows": []}
    records.sort(key=lambda row: row["va"])
    return {"available": True, "rows": records, "total": len(records)}


def _canonical_ledger():
    path = _artifact_path(_CANONICAL_LEDGER)
    if not os.path.isfile(path):
        return {"available": False, "source": _CANONICAL_LEDGER,
                "source_refs": [_CANONICAL_LEDGER], "rows": [], "total": 0}
    stat = os.stat(path)
    loaded = _load_canonical_ledger_cached(path, stat.st_mtime_ns, stat.st_size)
    loaded["source"] = _CANONICAL_LEDGER
    loaded["source_refs"] = [_CANONICAL_LEDGER]
    return loaded


def _canonical_summary():
    loaded = _load_json_artifact(_CANONICAL_SUMMARY)
    if not loaded.get("available"):
        return {"available": False, "source": _CANONICAL_SUMMARY,
                "source_refs": [_CANONICAL_SUMMARY]}
    value = loaded["value"]
    canonical = value.get("canonical_universe")
    xref = value.get("xref")
    headline = value.get("accounting_summary")
    if not isinstance(canonical, dict) or not isinstance(xref, dict) or not isinstance(headline, dict):
        return {"available": False, "source": _CANONICAL_SUMMARY,
                "source_refs": [_CANONICAL_SUMMARY], "reason": "incomplete_summary"}
    return {"available": True, "source": _CANONICAL_SUMMARY,
            "source_refs": loaded["source_refs"],
            "canonical": canonical, "xref": xref, "headline": headline}


def _load_research_index():
    loaded = _load_json_artifact(_RESEARCH_EVENTS)
    if not loaded.get("available"):
        return {"available": False, "source": _RESEARCH_EVENTS,
                "source_refs": [_RESEARCH_EVENTS],
                "state_machines": [], "events": [], "callbacks": [],
                "transitions": []}
    value = loaded["value"]
    return {"available": True, "source": _RESEARCH_EVENTS,
            "source_refs": [_RESEARCH_EVENTS],
            "state_machines": [row for row in value.get("state_machines", [])
                               if isinstance(row, dict)],
            "events": [row for row in value.get("events", [])
                       if isinstance(row, dict)],
            "callbacks": [row for row in value.get("callbacks", [])
                          if isinstance(row, dict)],
            "transitions": [row for row in value.get("transitions", [])
                            if isinstance(row, dict)]}


def _contains_function(item, needles):
    try:
        text = json.dumps(item, sort_keys=True).casefold()
    except (TypeError, ValueError):
        return False
    return any(needle and needle in text for needle in needles)


def _research_item(kind, item, source, limit):
    fields = {
        "state_machine": (
            "id", "name", "domain", "domains", "state_variable",
            "possible_states", "states", "transitions", "events",
            "callbacks", "guards", "entry_actions", "exit_actions",
            "entry_conditions", "side_effects", "relevant_functions",
            "relevant_structures", "producers", "consumers",
            "generated_events", "resulting_state_changes", "validation",
            "validation_strategy", "confidence", "evidence", "provenance"),
        "event": (
            "id", "name", "kind", "status", "confidence", "payload",
            "conditions", "producers", "produced_by", "consumers",
            "consumed_by", "callbacks", "generated_events",
            "resulting_state_changes", "evidence", "provenance"),
        "callback": (
            "id", "name", "address", "addresses", "consumers", "producers",
            "generated_events", "guards", "invocation_trigger",
            "registration_site", "update_contract", "parameters", "returns",
            "semantics", "confidence", "evidence", "provenance"),
        "transition": (
            "id", "machine_id", "machine_name", "from_state", "to_state",
            "event", "cause", "guard", "actions", "domains", "cross_domain",
            "impact_score", "impact_reasons", "source_ids", "sources",
            "provenance", "confidence", "evidence"),
    }[kind]
    out = {"origin": "research", "kind": kind}
    for field in fields:
        if field in item:
            out[field] = _bounded(item[field], limit)
    out["source_refs"] = _source_refs(source, item.get("sources"),
                                      item.get("provenance"), item.get("source"))
    return out


def _research_for_function(va, name, limit):
    research = _load_research_index()
    needles = tuple(sorted({_normalize_va(va), str(name or "").casefold()},
                           key=len, reverse=True))
    if not research.get("available"):
        return [], [], [], [], research
    states = [_research_item("state_machine", row, _RESEARCH_EVENTS, limit)
              for row in research["state_machines"]
              if _contains_function(row, needles)]
    events = [_research_item("event", row, _RESEARCH_EVENTS, limit)
              for row in research["events"]
              if _contains_function(row, needles)]
    callbacks = [_research_item("callback", row, _RESEARCH_EVENTS, limit)
                 for row in research["callbacks"]
                 if _contains_function(row, needles)]
    transitions = [_research_item("transition", row, _RESEARCH_EVENTS, limit)
                   for row in research["transitions"]
                   if _contains_function(row, needles)]
    if not transitions:
        for row in research["state_machines"]:
            if not _contains_function(row, needles):
                continue
            for transition in row.get("transitions", []):
                if not isinstance(transition, dict):
                    continue
                value = _research_item("transition", transition,
                                       _RESEARCH_EVENTS, limit)
                value["source_refs"] = _source_refs(
                    value.get("source_refs"), row.get("sources"),
                    row.get("provenance"))
                transitions.append(value)
    return states[:limit], events[:limit], callbacks[:limit], transitions[:limit], research


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


def evidence_distribution(db=None, limit=None, offset=0):
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
        if limit is None:
            return _ok(dist=counts, total=sum(counts.values()),
                       off_scale=other)
        page, bad = _page(limit, offset, default=len(EV_ORDER), maximum=_MAX_LIMIT)
        if bad:
            return bad
        entries = [(level, counts[level]) for level in EV_ORDER]
        entries += sorted(other.items())
        selected = entries[page[1]:page[1] + page[0]]
        dist = {level: n for level, n in selected if level in counts}
        off_scale = {level: n for level, n in selected if level not in counts}
        return _ok(dist=dist, total=sum(counts.values()) + sum(other.values()),
                   off_scale=off_scale, limit=page[0], offset=page[1])
    finally:
        conn.close()


def node_label_distribution(db=None, limit=None, offset=0):
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        if limit is None:
            rows = conn.execute(
                "SELECT label, COUNT(*) FROM node"
                " GROUP BY label ORDER BY COUNT(*) DESC, label").fetchall()
            dist = {label: n for label, n in rows}
            return _ok(dist=dist, total=sum(dist.values()))
        page, bad = _page(limit, offset, default=1000, maximum=_MAX_LIMIT)
        if bad:
            return bad
        total = conn.execute("SELECT COUNT(DISTINCT label) FROM node").fetchone()[0]
        rows = conn.execute(
            "SELECT label, COUNT(*) FROM node GROUP BY label"
            " ORDER BY COUNT(*) DESC, label LIMIT ? OFFSET ?",
            [page[0], page[1]]).fetchall()
        return _ok(dist={label: n for label, n in rows}, total=total,
                   limit=page[0], offset=page[1])
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
                        limit=200, offset=0, db=None, readiness=None):
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
        if readiness is not None:
            return _err(
                "unsupported_filter",
                "investigations.triage_status is not reconstruction readiness; "
                "use /api/functions or /api/readiness")
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
        inv_columns = {r["name"] for r in conn.execute(
            "PRAGMA table_info(investigations)")}
        inv_status = ", triage_status" if "triage_status" in inv_columns else ""
        rows = conn.execute(
            ("SELECT id, kind, va, name, subsystem, stage, status"
             + inv_status + ", block_reason, updated_at FROM investigations%s"
             " ORDER BY id LIMIT ? OFFSET ?") % where,
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


def _attach_readiness(item, readiness):
    attrs = item.get("attrs") if isinstance(item.get("attrs"), dict) else {}
    va = _normalize_va(item.get("va") or item.get("address")
                       or attrs.get("address") or attrs.get("va"))
    row = readiness["functions"].get(va) if readiness.get("available") else None
    status = row.get("readiness") if isinstance(row, dict) else None
    if isinstance(status, dict):
        status = status.get("status")
    item["readiness"] = status if isinstance(status, str) else None
    item["readiness_available"] = bool(row is not None)
    item["readiness_source"] = {
        "available": bool(readiness.get("available")),
        "source": readiness.get("source"),
        "source_refs": readiness.get("source_refs", []),
    }
    if row is not None:
        item["readiness_rationale"] = row.get("readiness_rationale") or row.get("rationale")
        item["readiness_record"] = row
    return item


def _distribution(rows, field):
    counts = Counter(row.get(field) for row in rows if row.get(field) is not None)
    return [{"value": value, "count": counts[value]}
            for value in sorted(counts, key=lambda item: (str(item),))]


def _package_filtered(item, package):
    packages = item.get("packages") or []
    return str(package).casefold() in {str(value).casefold() for value in packages}


def functions(q=None, evidence=None, readiness=None, subsystem=None,
              package=None, limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    limit, offset = page
    readiness_data = _readiness_data()
    canonical = _canonical_ledger()
    summary = _canonical_summary()
    if canonical.get("available"):
        rows = canonical["rows"]
        needle = str(q).casefold() if q is not None else None
        needles = {needle} if needle else set()
        needles.update(_va_candidates(q))
        filtered = []
        for source_row in rows:
            if needles:
                searchable = " ".join(str(source_row.get(key) or "") for key in (
                    "va", "name", "sdk_name", "id", "struct_names")).casefold()
                if not any(candidate in searchable for candidate in needles):
                    continue
            if evidence is not None and source_row.get("evidence") != evidence:
                continue
            if subsystem is not None and source_row.get("subsystem") != subsystem:
                continue
            if package is not None and not _package_filtered(source_row, package):
                continue
            item = dict(source_row)
            item["label"] = "Function"
            item["canonical"] = True
            _attach_readiness(item, readiness_data)
            if readiness is not None and item["readiness"] != readiness:
                continue
            filtered.append(item)
        filtered.sort(key=lambda row: row["va"])
        selected = filtered[offset:offset + limit]
        headline = summary.get("headline", {}) if summary.get("available") else {}
        package_counts = Counter()
        canonical_readiness_counts = Counter()
        for row in rows:
            for value in row.get("packages", []):
                package_counts[value] += 1
            readiness_row = readiness_data.get("functions", {}).get(row["va"])
            if isinstance(readiness_row, dict):
                status = readiness_row.get("readiness")
                if isinstance(status, dict):
                    status = status.get("status")
                if isinstance(status, str):
                    canonical_readiness_counts[status] += 1
        statistics_payload = {
            "evidence": _distribution(rows, "evidence"),
            "subsystem": _distribution(rows, "subsystem"),
            "package": [{"value": value, "count": package_counts[value]}
                        for value in sorted(package_counts)],
            "readiness": [{"status": state, "count": canonical_readiness_counts.get(state, 0)}
                          for state in readiness_data.get("states", [])],
            "readiness_artifact_counts": [
                {"status": state, "count": readiness_data["counts"].get(state, 0)}
                for state in readiness_data.get("states", [])],
            "headline": headline,
        }
        canonical_inventory = {
            "available": True,
            "source": "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
            "accounting_source": canonical.get("source"),
            "source_refs": _source_refs(
                "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
                canonical.get("source_refs")),
            "snapshot": (summary.get("canonical", {}).get("snapshot_sha256")
                         if summary.get("available") else None),
            "total": len(rows),
            "unique_va": len({row["va"] for row in rows}),
            "readiness_available": readiness_data.get("available", False),
            "readiness_artifact_total": readiness_data.get("total", 0),
            "readiness_total": sum(canonical_readiness_counts.values()),
            "readiness_outside_canonical": max(
                0, readiness_data.get("total", 0)
                - sum(canonical_readiness_counts.values())),
            "package_source": _PACKAGE_ARTIFACT if _package_clusters() else None,
        }
        return _ok(available=True, total=len(filtered), limit=limit,
                   offset=offset,
                   source="knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
                   accounting_source=canonical.get("source"),
                   source_refs=_source_refs(
                       "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl",
                       canonical.get("source_refs")),
                   canonical_function=canonical_inventory,
                   inventory=canonical_inventory,
                   statistics=statistics_payload,
                   functions=selected)

    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        if not _has_table(conn, "triage"):
            return _ok(available=False, total=0, limit=limit, offset=offset,
                       source="sqlite:triage", source_refs=["sqlite:triage"],
                       canonical_function={"available": False, "total": 0},
                       inventory={"available": False, "total": 0},
                       functions=[])
        clauses, args = [], []
        if q is not None:
            clauses.append("(ghidra_name LIKE ? ESCAPE '\\' OR norm_name LIKE ? ESCAPE '\\' OR va LIKE ? ESCAPE '\\' OR kg_node_id LIKE ? ESCAPE '\\')")
            pattern = "%" + _like(q) + "%"
            args.extend([pattern] * 4)
        if evidence is not None:
            clauses.append("evidence=?")
            args.append(evidence)
        if subsystem is not None:
            clauses.append("subsystem=?")
            args.append(subsystem)
        if package is not None:
            clauses.append("category=?")
            args.append(package)
        where = " WHERE " + " AND ".join(clauses) if clauses else ""
        db_rows = conn.execute(
            "SELECT va, ghidra_name, norm_name, subsystem, category, priority,"
            " evidence, sdk_name, struct_names, vtable_addrs, caller_count,"
            " callee_count, decomp_path, kg_node_id, snapshot_sha256,"
            " classifier_version FROM triage" + where
            + " ORDER BY va", args).fetchall()
        filtered = []
        for db_row in db_rows:
            struct_names = _parse_jsonish(db_row["struct_names"]) or []
            vtable_addrs = _parse_jsonish(db_row["vtable_addrs"]) or []
            item = {
                "id": db_row["kg_node_id"], "label": "Function",
                "va": _normalize_va(db_row["va"]),
                "address": _normalize_va(db_row["va"]),
                "name": db_row["ghidra_name"], "ghidra_name": db_row["ghidra_name"],
                "norm_name": db_row["norm_name"], "sdk_name": db_row["sdk_name"],
                "category": db_row["category"], "cluster": None,
                "subsystem": db_row["subsystem"], "package": db_row["category"],
                "packages": [db_row["category"]], "package_kind": "triage_category",
                "priority": db_row["priority"], "evidence": db_row["evidence"],
                "evidence_level": db_row["evidence"],
                "caller_count": db_row["caller_count"],
                "callee_count": db_row["callee_count"],
                "struct_names": struct_names, "vtable_addrs": vtable_addrs,
                "decomp_path": db_row["decomp_path"], "canonical": True,
                "provenance": {"snapshot_sha256": db_row["snapshot_sha256"],
                                "classifier_version": db_row["classifier_version"]},
                "source_refs": ["sqlite:triage"],
            }
            _attach_readiness(item, readiness_data)
            if readiness is not None and item["readiness"] != readiness:
                continue
            filtered.append(item)
        selected = filtered[offset:offset + limit]
        canonical_inventory = {
            "available": True, "source": "sqlite:triage",
            "source_refs": ["sqlite:triage"], "snapshot": None,
            "total": len(db_rows), "unique_va": len({row["va"] for row in db_rows}),
            "readiness_available": readiness_data.get("available", False),
            "readiness_total": readiness_data.get("total", 0),
            "package_source": "sqlite:triage.category",
        }
        statistics_payload = {
            "evidence": _distribution(filtered, "evidence"),
            "subsystem": _distribution(filtered, "subsystem"),
            "package": _distribution(filtered, "package"),
            "readiness": [{"status": state, "count": readiness_data["counts"].get(state, 0)}
                          for state in readiness_data.get("states", [])],
            "xrefs": conn.execute("SELECT COUNT(*) FROM xref").fetchone()[0]
                     if _has_table(conn, "xref") else None,
        }
        return _ok(available=True, total=len(filtered), limit=limit,
                   offset=offset, source="sqlite:triage",
                   source_refs=["sqlite:triage"],
                   canonical_function=canonical_inventory,
                   inventory=canonical_inventory,
                   statistics=statistics_payload, functions=selected)
    finally:
        conn.close()


def nodes(label=None, q=None, limit=200, offset=0, db=None,
          evidence=None, origin=None, readiness=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    limit, offset = page
    readiness_data = None
    if readiness is not None:
        if label not in (None, "Function"):
            return _err("unsupported_filter",
                        "reconstruction readiness applies only to Function nodes")
        readiness_data = _readiness_data()
        if not readiness_data.get("per_function_available"):
            return _err("unsupported_filter",
                        "reconstruction readiness artifact has no per-function rows")
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        clauses, args = [], []
        selected_label = "Function" if readiness is not None else label
        if selected_label is not None:
            clauses.append("label=?")
            args.append(selected_label)
        if evidence is not None:
            clauses.append("evidence_level=?")
            args.append(evidence)
        if origin is not None:
            clauses.append("origin=?")
            args.append(origin)
        if q is not None:
            escaped = _like(q)
            va = _va_candidates(q)
            if va:
                clauses.append("(name LIKE ? ESCAPE '\\' OR name=?)")
                args.extend(["%" + escaped + "%", "fun:" + va[0]])
            else:
                clauses.append("name LIKE ? ESCAPE '\\'")
                args.append("%" + escaped + "%")
        where = (" WHERE " + " AND ".join(clauses)) if clauses else ""
        if readiness is None:
            total = conn.execute(
                "SELECT COUNT(*) FROM node" + where, args).fetchone()[0]
            rows = conn.execute(
                "SELECT * FROM node" + where
                + " ORDER BY label, name, id LIMIT ? OFFSET ?",
                args + [limit, offset]).fetchall()
            values = [_node_row(r) for r in rows]
        else:
            rows = conn.execute(
                "SELECT * FROM node" + where
                + " ORDER BY label, name, id", args).fetchall()
            filtered = []
            for row in rows:
                item = _node_row(row)
                _attach_readiness(item, readiness_data)
                if item["readiness"] == readiness:
                    filtered.append(item)
            total = len(filtered)
            values = filtered[offset:offset + limit]
        return _ok(total=total, limit=limit, offset=offset, nodes=values)
    finally:
        conn.close()


def search(q=None, label=None, evidence=None, origin=None, readiness=None,
           limit=200, offset=0, db=None):
    if q is None or not str(q).strip():
        return _err("invalid_params", "'q' must be a non-empty search string")
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    limit, offset = page
    readiness_data = None
    if readiness is not None:
        if label not in (None, "Function"):
            return _err("unsupported_filter",
                        "reconstruction readiness applies only to Function nodes")
        readiness_data = _readiness_data()
        if not readiness_data.get("per_function_available"):
            return _err("unsupported_filter",
                        "reconstruction readiness artifact has no per-function rows")
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        clauses, args = [], []
        escaped = _like(q)
        va = _va_candidates(q)
        if va:
            clauses.append(
                "(name LIKE ? ESCAPE '\\' OR attrs_json LIKE ? ESCAPE '\\'"
                " OR name=?)")
            args += ["%" + escaped + "%", "%" + escaped + "%",
                     "fun:" + va[0]]
        else:
            clauses.append(
                "(name LIKE ? ESCAPE '\\' OR attrs_json LIKE ? ESCAPE '\\')")
            args += ["%" + escaped + "%", "%" + escaped + "%"]
        selected_label = "Function" if readiness is not None else label
        if selected_label is not None:
            clauses.append("label=?")
            args.append(selected_label)
        if evidence is not None:
            clauses.append("evidence_level=?")
            args.append(evidence)
        if origin is not None:
            clauses.append("origin=?")
            args.append(origin)
        where = " WHERE " + " AND ".join(clauses)
        if readiness is None:
            total = conn.execute(
                "SELECT COUNT(*) FROM node" + where, args).fetchone()[0]
            rows = conn.execute(
                "SELECT * FROM node" + where
                + " ORDER BY label, name, id LIMIT ? OFFSET ?",
                args + [limit, offset]).fetchall()
            results = [_node_row(r) for r in rows]
        else:
            rows = conn.execute(
                "SELECT * FROM node" + where
                + " ORDER BY label, name, id", args).fetchall()
            filtered = []
            for row in rows:
                item = _node_row(row)
                _attach_readiness(item, readiness_data)
                if item["readiness"] == readiness:
                    filtered.append(item)
            total = len(filtered)
            results = filtered[offset:offset + limit]
        return _ok(total=total, limit=limit, offset=offset,
                   results=results, nodes=results)
    finally:
        conn.close()


def _resolve_node(conn, ref):
    text = str(ref if ref is not None else "").strip()
    if text.isdigit():
        row = conn.execute("SELECT * FROM node WHERE id=?",
                           (text,)).fetchone()
        if row is None:
            return None, _err("not_found", "no node with id %s" % ref)
        return row, None
    rows = conn.execute(
        "SELECT * FROM node WHERE name=? ORDER BY label, id",
        (text,)).fetchall()
    if rows:
        if len(rows) > 1:
            return None, _err(
                "ambiguous", "name %r matches %d labels" % (ref, len(rows)),
                labels=[r["label"] for r in rows])
        return rows[0], None
    va = _va_candidates(text)
    if va:
        canonical = "fun:" + va[0]
        rows = conn.execute(
            "SELECT * FROM node WHERE name=? ORDER BY label, id",
            (canonical,)).fetchall()
        if rows:
            if len(rows) > 1:
                return None, _err(
                    "ambiguous", "VA %r matches %d labels" % (ref, len(rows)),
                    labels=[r["label"] for r in rows])
            return rows[0], None
    if not text:
        return None, _err("not_found", "no node with empty reference")
    return None, _err("not_found", "no node named %r" % ref)


def node_detail(ref, db=None, limit=_MAX_DETAIL_ITEMS):
    page, bad = _page(limit, 0, default=_MAX_DETAIL_ITEMS,
                      maximum=_MAX_DETAIL_ITEMS)
    if bad:
        return bad
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
        field_total = conn.execute(
            "SELECT COUNT(*) FROM field WHERE struct_id=?",
            (row["id"],)).fetchone()[0]
        fields = [dict(f) for f in conn.execute(
            "SELECT * FROM field WHERE struct_id=? ORDER BY id LIMIT ?",
            (row["id"], page[0]))]
        attrs = node["attrs"] if isinstance(node["attrs"], dict) else {}
        va_candidates = {row["name"]}
        for key in ("va", "address", "rva", "addr"):
            val = attrs.get(key)
            if isinstance(val, str):
                va_candidates.update(_va_candidates(val) or [val])
        cands = sorted(va_candidates)
        marks = ",".join("?" * len(cands))
        inv_columns = {r["name"] for r in conn.execute(
            "PRAGMA table_info(investigations)")}
        inv_status = ", triage_status" if "triage_status" in inv_columns else ""
        inv_where = " WHERE name = ? OR va IN (%s)" % marks
        investigation_total = conn.execute(
            "SELECT COUNT(*) FROM investigations" + inv_where,
            [row["name"]] + cands).fetchone()[0]
        invs = [dict(iv) for iv in conn.execute(
            "SELECT id, kind, va, name, subsystem, mode, stage, status"
            + inv_status + ", binary_sha256 FROM investigations"
            + inv_where + " ORDER BY id LIMIT ?",
            [row["name"]] + cands + [page[0]])]
        out = _ok(node=node, fields=fields, investigations=invs,
                  limit=page[0], field_total=field_total,
                  investigation_total=investigation_total,
                  fields_truncated=field_total > len(fields),
                  investigations_truncated=investigation_total > len(invs),
                  source_refs=["sqlite:node/%s" % row["id"]])
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


def _graph_slice(conn, root_id, depth, limit, edge_limit):
    limit = min(limit, _MAX_GRAPH_NODES)
    edge_limit = min(edge_limit, _MAX_GRAPH_EDGES)
    visited = {root_id: 0}
    frontier = [root_id]
    edges, seen_edges = [], set()
    truncated = False
    for d in range(1, depth + 1):
        if not frontier:
            break
        next_frontier = set()
        for chunk in _chunks(frontier):
            if len(edges) >= edge_limit:
                truncated = True
                break
            marks = ",".join("?" * len(chunk))
            remaining = edge_limit - len(edges) + 1
            rows = conn.execute(
                "SELECT id, src, dst, rel FROM edge"
                " WHERE src IN (%s) OR dst IN (%s)"
                " ORDER BY id LIMIT ?" % (marks, marks),
                chunk + chunk + [remaining]).fetchall()
            for e in rows:
                edge_id = e["id"]
                if edge_id in seen_edges:
                    continue
                endpoint_ok = True
                for a, b in ((e["src"], e["dst"]), (e["dst"], e["src"])):
                    if a in frontier and b not in visited:
                        if len(visited) >= limit:
                            truncated = True
                            endpoint_ok = False
                            break
                        visited[b] = d
                        next_frontier.add(b)
                if not endpoint_ok:
                    continue
                if len(edges) >= edge_limit:
                    truncated = True
                    break
                seen_edges.add(edge_id)
                edges.append({"id": edge_id, "src": e["src"],
                              "dst": e["dst"], "rel": e["rel"]})
            if len(edges) >= edge_limit:
                truncated = True
                break
        if len(edges) >= edge_limit:
            break
        frontier = sorted(next_frontier)
    ids = sorted(visited)
    found = set()
    for chunk in _chunks(ids):
        marks = ",".join("?" * len(chunk))
        found.update(r["id"] for r in conn.execute(
            "SELECT id FROM node WHERE id IN (%s)" % marks, chunk))
    nodes_out = []
    for chunk in _chunks(sorted(found)):
        marks = ",".join("?" * len(chunk))
        nodes_out.extend(_node_row(r) for r in conn.execute(
            "SELECT * FROM node WHERE id IN (%s) ORDER BY label, name, id"
            % marks, chunk))
    nodes_out.sort(key=lambda n: (n["label"], n["name"], n["id"]))
    edges = [e for e in edges if e["src"] in found and e["dst"] in found]
    return nodes_out, edges, truncated


def node_neighbors(ref, depth=1, db=None, limit=_MAX_GRAPH_NODES,
                   edge_limit=_MAX_GRAPH_EDGES):
    try:
        depth = int(depth)
    except (TypeError, ValueError):
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    if depth < 1 or depth > 3:
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    page, bad = _page(limit, 0, default=_MAX_GRAPH_NODES,
                      maximum=_MAX_GRAPH_NODES)
    if bad:
        return bad
    edge_page, bad = _page(edge_limit, 0, default=_MAX_GRAPH_EDGES,
                          maximum=_MAX_GRAPH_EDGES)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        row, bad = _resolve_node(conn, ref)
        if bad:
            return bad
        nodes_out, edges, truncated = _graph_slice(
            conn, row["id"], depth, page[0], edge_page[0])
        return _ok(node=_node_row(row), depth=depth,
                   limit=page[0], edge_limit=edge_page[0],
                   truncated=truncated, nodes=nodes_out, edges=edges)
    finally:
        conn.close()


def subgraph(ref, depth=1, limit=_MAX_GRAPH_NODES,
             edge_limit=_MAX_GRAPH_EDGES, db=None):
    result = node_neighbors(ref, depth, db, limit, edge_limit)
    if result.get("status") != "ok":
        return result
    result["subgraph"] = {"nodes": result["nodes"], "edges": result["edges"]}
    return result


def architecture(root=None, depth=1, limit=_MAX_GRAPH_NODES,
                 edge_limit=_MAX_GRAPH_EDGES, offset=0, db=None):
    try:
        depth = int(depth)
    except (TypeError, ValueError):
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    if depth < 1 or depth > 3:
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    page, bad = _page(limit, offset, default=_MAX_GRAPH_NODES,
                      maximum=_MAX_GRAPH_NODES)
    if bad:
        return bad
    edge_page, bad = _page(edge_limit, 0, default=_MAX_GRAPH_EDGES,
                          maximum=_MAX_GRAPH_EDGES)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        if root is not None:
            root_row, bad = _resolve_node(conn, root)
            if bad:
                return bad
            root_rows = [root_row]
            total_roots = 1
        else:
            root_rows = conn.execute(
                "SELECT * FROM node WHERE label IN ('Subsystem','Package')"
                " ORDER BY label, name, id LIMIT ? OFFSET ?",
                [page[0], page[1]]).fetchall()
            total_roots = conn.execute(
                "SELECT COUNT(*) FROM node WHERE label IN ('Subsystem','Package')"
            ).fetchone()[0]
        all_nodes, all_edges, truncated = {}, {}, False
        for root_row in root_rows:
            nodes_out, edges_out, was_truncated = _graph_slice(
                conn, root_row["id"], depth, page[0], edge_page[0])
            truncated = truncated or was_truncated
            for node in nodes_out:
                if node["id"] not in all_nodes and len(all_nodes) < page[0]:
                    all_nodes[node["id"]] = node
            for edge in edges_out:
                if edge["id"] not in all_edges and len(all_edges) < edge_page[0]:
                    all_edges[edge["id"]] = edge
        nodes_out = sorted(all_nodes.values(),
                           key=lambda n: (n["label"], n["name"], n["id"]))
        edges = [all_edges[key] for key in sorted(all_edges)]
        node_ids = set(all_nodes)
        edges = [e for e in edges
                 if e["src"] in node_ids and e["dst"] in node_ids]
        roots_out = [_node_row(r) for r in root_rows
                     if r["id"] in all_nodes]
        result = _ok(total=total_roots, limit=page[0], offset=page[1],
                     edge_limit=edge_page[0], truncated=truncated,
                     roots=roots_out, nodes=nodes_out, edges=edges)
        result["hierarchy"] = roots_out
        return result
    finally:
        conn.close()


def hierarchy(root=None, depth=1, limit=_MAX_GRAPH_NODES,
              edge_limit=_MAX_GRAPH_EDGES, offset=0, db=None):
    return architecture(root, depth, limit, edge_limit, offset, db)


def packages(q=None, limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        clauses, args = ["label='Package'"], []
        if q is not None:
            clauses.append("name LIKE ? ESCAPE '\\'")
            args.append("%" + _like(q) + "%")
        where = " WHERE " + " AND ".join(clauses)
        total = conn.execute("SELECT COUNT(*) FROM node" + where, args).fetchone()[0]
        rows = conn.execute(
            "SELECT * FROM node" + where
            + " ORDER BY name, id LIMIT ? OFFSET ?",
            args + [page[0], page[1]]).fetchall()
        package_nodes = [_node_row(r) for r in rows]
        ids = [r["id"] for r in rows]
        edges = []
        for chunk in _chunks(ids):
            marks = ",".join("?" * len(chunk))
            edges.extend({"id": r["id"], "src": r["src"], "dst": r["dst"],
                          "rel": r["rel"]} for r in conn.execute(
                              "SELECT id, src, dst, rel FROM edge"
                              " WHERE src IN (%s) OR dst IN (%s)"
                              " ORDER BY id LIMIT ?" % (marks, marks),
                              chunk + chunk + [_MAX_GRAPH_EDGES]))
        edges.sort(key=lambda e: e["id"])
        edges = edges[:_MAX_GRAPH_EDGES]
        return _ok(total=total, limit=page[0], offset=page[1],
                   packages=package_nodes, nodes=package_nodes, edges=edges)
    finally:
        conn.close()


def _type_facet_payload(conn, query, limit, offset, edge_limit):
    terms = []
    for term in (str(query).strip().lower(),):
        if term and term not in terms:
            terms.append(term)
    for term in list(terms):
        if term.startswith("struct:/spore/simulator/"):
            suffix = term[len("struct:/spore/simulator/"):]
            for candidate in ("struct:Simulator::" + suffix,
                              "struct:/Spore/Simulator/" + suffix):
                if candidate.lower() not in {value.lower() for value in terms}:
                    terms.append(candidate)
    matches = []
    for term in terms:
        matches.extend((("name LIKE ? ESCAPE '\\'", "%" + _like(term) + "%"),
                        ("attrs_json LIKE ? ESCAPE '\\'", "%" + _like(term) + "%")))
    facet_where = " AND (" + " OR ".join(clause for clause, _ in matches) + ")"
    facet_args = [value for _, value in matches]
    facets = conn.execute(
        "SELECT * FROM node WHERE label IN ('Class','Structure','VTable')"
        + facet_where + " ORDER BY label, name, id LIMIT ? OFFSET ?",
        facet_args + [limit, offset]).fetchall()
    facet_nodes = [_node_row(row) for row in facets]
    facet_ids = [row["id"] for row in facets]
    if not facet_ids:
        return {"facet_nodes": [], "nodes": [], "incident_nodes": [],
                "holders": [], "edges": [], "edge_truncated": False}
    marks = ",".join("?" * len(facet_ids))
    edges = conn.execute(
        "SELECT id, src, dst, rel FROM edge WHERE src IN (%s) OR dst IN (%s)"
        " ORDER BY id LIMIT ?" % (marks, marks),
        facet_ids + facet_ids + [edge_limit]).fetchall()
    endpoint_ids = {row["src"] for row in edges} | {row["dst"] for row in edges}
    endpoint_ids.difference_update(facet_ids)
    endpoint_rows = []
    for chunk in _chunks(sorted(endpoint_ids)):
        chunk_marks = ",".join("?" * len(chunk))
        endpoint_rows.extend(conn.execute(
            "SELECT * FROM node WHERE id IN (%s) ORDER BY label, name, id"
            % chunk_marks, chunk).fetchall())
    endpoint_nodes = [_node_row(row) for row in endpoint_rows]
    expression = ("COALESCE(json_extract(attrs_json, '$.type'),"
                  "json_extract(attrs_json, '$.value_type'),"
                  "json_extract(attrs_json, '$.type_semantics'))")
    holder_clauses = []
    holder_args = []
    for term in terms:
        holder_clauses.append("%s LIKE ? ESCAPE '\\'" % expression)
        holder_args.append("%" + _like(term) + "%")
    holders = []
    if holder_clauses:
        holders = conn.execute(
            "SELECT * FROM node WHERE json_valid(attrs_json) AND ("
            + " OR ".join(holder_clauses)
            + ") ORDER BY label, name, id LIMIT ? OFFSET ?",
            holder_args + [limit, offset]).fetchall()
    holder_nodes = [_node_row(row) for row in holders]
    all_nodes = {}
    for node in facet_nodes + endpoint_nodes + holder_nodes:
        all_nodes.setdefault(node["id"], node)
    nodes = list(all_nodes.values())[:limit]
    incident_ids = {node["id"] for node in endpoint_nodes}
    incident_nodes = [node for node in nodes if node["id"] in incident_ids]
    holder_ids = {node["id"] for node in holder_nodes}
    holders = [node for node in nodes
               if node["id"] in holder_ids or node["id"] in incident_ids]
    node_ids = {node["id"] for node in nodes}
    normalized_edges = []
    for row in edges:
        if row["src"] in node_ids and row["dst"] in node_ids:
            normalized_edges.append({"id": row["id"], "src": row["src"],
                                     "dst": row["dst"], "rel": row["rel"],
                                     "source_refs": ["sqlite:edge/%s" % row["id"]]})
    return {"facet_nodes": facet_nodes, "nodes": nodes,
            "incident_nodes": incident_nodes[:limit], "holders": holders[:limit],
            "attribute_holders": holder_nodes[:limit],
            "edges": normalized_edges,
            "edge_truncated": len(edges) >= edge_limit}


def types(q=None, limit=200, offset=0, db=None, edge_limit=_MAX_GRAPH_EDGES):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    edge_page, bad = _page(edge_limit, 0, default=_MAX_GRAPH_EDGES,
                           maximum=_MAX_GRAPH_EDGES)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        expression = ("COALESCE(json_extract(attrs_json, '$.type'),"
                      "json_extract(attrs_json, '$.value_type'),"
                      "json_extract(attrs_json, '$.type_semantics'))")
        where = " WHERE json_valid(attrs_json) AND %s IS NOT NULL" % expression
        args = []
        if q is not None:
            where += " AND %s LIKE ? ESCAPE '\\'" % expression
            args.append("%" + _like(q) + "%")
        total = conn.execute(
            "SELECT COUNT(*) FROM (SELECT %s AS type_value, label FROM node%s"
            " GROUP BY type_value, label)" % (expression, where),
            args).fetchone()[0]
        rows = conn.execute(
            "SELECT %s AS type_value, label, COUNT(*) AS n FROM node%s"
            " GROUP BY type_value, label ORDER BY type_value, label LIMIT ? OFFSET ?"
            % (expression, where), args + [page[0], page[1]]).fetchall()
        values = []
        for row in rows:
            item = {"type": row["type_value"], "label": row["label"],
                    "count": row["n"]}
            item["value"] = _parse_jsonish(row["type_value"])
            values.append(item)
        result = _ok(total=total, limit=page[0], offset=page[1], types=values)
        if q is not None and str(q).strip():
            result.update(_type_facet_payload(
                conn, q, page[0], page[1], edge_page[0]))
            result["graph"] = {"nodes": result["nodes"],
                               "edges": result["edges"]}
            result["facet"] = {"query": q, "nodes": result["facet_nodes"],
                               "holders": result["holders"]}
            result["edge_limit"] = edge_page[0]
            result["edge_truncated"] = result.pop("edge_truncated", False)
        return result
    finally:
        conn.close()


def _json_attribute_values(attribute, limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        args = [attribute]
        total = conn.execute(
            "SELECT COUNT(*) FROM (SELECT n.id FROM"
            " (SELECT * FROM node WHERE json_valid(attrs_json)) n,"
            " json_each(n.attrs_json) j WHERE j.key=?"
            " GROUP BY n.id, j.value)", args).fetchone()[0]
        rows = conn.execute(
            "SELECT n.id, n.label, n.name, j.value AS value"
            " FROM (SELECT * FROM node WHERE json_valid(attrs_json)) n,"
            " json_each(n.attrs_json) j"
            " WHERE j.key=? ORDER BY n.label, n.name, n.id"
            " LIMIT ? OFFSET ?", [attribute, page[0], page[1]]).fetchall()
        items = []
        for row in rows:
            items.append({"node": {"id": row["id"], "label": row["label"],
                                   "name": row["name"]},
                          "value": _parse_jsonish(row["value"])})
        return _ok(total=total, limit=page[0], offset=page[1], items=items)
    finally:
        conn.close()


def _db_state_items(result):
    values = []
    for item in result.get("items", []):
        value = dict(item)
        node = value.get("node") or {}
        value["origin"] = "db_attrs"
        value["kind"] = "db_attribute"
        value["source_refs"] = ["sqlite:node/%s" % node.get("id")]
        values.append(value)
    return values


def states(limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    result = _json_attribute_values("states", _MAX_LIMIT, 0, db)
    if result.get("status") != "ok":
        return result
    research = _load_research_index()
    db_values = _db_state_items(result)
    research_values = [_research_item("state_machine", row, _RESEARCH_EVENTS,
                                      min(page[0], _MAX_DETAIL_ITEMS))
                       for row in research.get("state_machines", [])]
    combined = db_values + research_values
    combined.sort(key=lambda item: (
        0 if item.get("origin") == "db_attrs" else 1,
        str(item.get("id") or item.get("name") or ""),
        str(item.get("value") or ""), item.get("source_refs", [])))
    total = len(combined)
    values = combined[page[1]:page[1] + page[0]]
    transitions = [_research_item("transition", row, _RESEARCH_EVENTS,
                                  min(page[0], _MAX_DETAIL_ITEMS))
                   for row in research.get("transitions", [])]
    transitions.sort(key=lambda item: (
        str(item.get("machine_id") or ""), str(item.get("id") or ""),
        str(item.get("from_state") or ""), str(item.get("to_state") or "")))
    result.update({
        "available": research.get("available", False),
        "db_available": True,
        "source": _RESEARCH_EVENTS,
        "source_refs": research.get("source_refs", []),
        "total": total, "limit": page[0], "offset": page[1],
        "items": values, "states": values,
        "transitions": transitions[page[1]:page[1] + page[0]],
    })
    return result


def events(limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    result = _json_attribute_values("events", _MAX_LIMIT, 0, db)
    if result.get("status") != "ok":
        return result
    research = _load_research_index()
    db_values = _db_state_items(result)
    research_values = [_research_item("event", row, _RESEARCH_EVENTS,
                                      min(page[0], _MAX_DETAIL_ITEMS))
                       for row in research.get("events", [])]
    combined = db_values + research_values
    combined.sort(key=lambda item: (
        0 if item.get("origin") == "db_attrs" else 1,
        str(item.get("id") or item.get("name") or ""),
        str(item.get("value") or ""), item.get("source_refs", [])))
    total = len(combined)
    values = combined[page[1]:page[1] + page[0]]
    callbacks = [_research_item("callback", row, _RESEARCH_EVENTS,
                                min(page[0], _MAX_DETAIL_ITEMS))
                 for row in research.get("callbacks", [])]
    callbacks.sort(key=lambda item: (
        str(item.get("id") or ""), str(item.get("name") or ""),
        str(item.get("address") or "")))
    transitions = [_research_item("transition", row, _RESEARCH_EVENTS,
                                  min(page[0], _MAX_DETAIL_ITEMS))
                   for row in research.get("transitions", [])]
    transitions.sort(key=lambda item: (
        str(item.get("id") or ""), str(item.get("event") or ""),
        str(item.get("from_state") or ""), str(item.get("to_state") or "")))
    result.update({
        "available": research.get("available", False),
        "db_available": True,
        "source": _RESEARCH_EVENTS,
        "source_refs": research.get("source_refs", []),
        "total": total, "limit": page[0], "offset": page[1],
        "items": values, "events": values,
        "callbacks": callbacks[page[1]:page[1] + page[0]],
        "transitions": transitions[page[1]:page[1] + page[0]],
    })
    return result


def readiness_distribution(limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    data = _readiness_data()
    values = [{"status": state,
               "count": data.get("counts", {}).get(state, 0),
               "declared_count": data.get("declared_counts", {}).get(state)}
              for state in data.get("states", [])]
    values = values[page[1]:page[1] + page[0]]
    return _ok(available=data.get("available", False),
               per_function_available=data.get("per_function_available", False),
               source=data.get("source"), source_refs=data.get("source_refs", []),
               snapshot=data.get("snapshot"), total=len(data.get("states", [])),
               function_total=data.get("total", 0), limit=page[0],
               offset=page[1], states=data.get("states", []),
               readiness=values, readiness_counts=values)


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


def statistics(limit=200, offset=0, db=None):
    page, bad = _page(limit, offset, default=200)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        counts = {}
        for table in _TABLES:
            counts[table] = conn.execute(
                "SELECT COUNT(*) FROM %s" % table).fetchone()[0]
        optional_counts = {}
        for table in _OPTIONAL_TABLES:
            optional_counts[table] = (conn.execute(
                "SELECT COUNT(*) FROM %s" % table).fetchone()[0]
                if _has_table(conn, table) else None)
        labels = [{"value": r["label"], "count": r["n"]} for r in conn.execute(
            "SELECT label, COUNT(*) AS n FROM node"
            " GROUP BY label ORDER BY label LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        evidence = [{"value": r["evidence_level"], "count": r["n"]} for r in conn.execute(
            "SELECT evidence_level, COUNT(*) AS n FROM node"
            " GROUP BY evidence_level ORDER BY evidence_level LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        relations = [{"value": r["rel"], "count": r["n"]} for r in conn.execute(
            "SELECT rel, COUNT(*) AS n FROM edge"
            " GROUP BY rel ORDER BY rel LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        investigation_statuses = [{"value": r["status"], "count": r["n"]} for r in conn.execute(
            "SELECT status, COUNT(*) AS n FROM investigations"
            " GROUP BY status ORDER BY status LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        investigation_stages = [{"value": r["stage"], "count": r["n"]} for r in conn.execute(
            "SELECT stage, COUNT(*) AS n FROM investigations"
            " GROUP BY stage ORDER BY stage LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        tests = [{"value": r["pass"], "count": r["n"]} for r in conn.execute(
            "SELECT pass, COUNT(*) AS n FROM test_result"
            " GROUP BY pass ORDER BY pass LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        traces = [{"value": r["outcome"], "count": r["n"]} for r in conn.execute(
            "SELECT outcome, COUNT(*) AS n FROM trace_run"
            " GROUP BY outcome ORDER BY outcome LIMIT ? OFFSET ?",
            [page[0], page[1]])]
        canonical_summary = _canonical_summary()
        canonical = canonical_summary.get("canonical", {}) if canonical_summary.get("available") else {}
        xref_summary = canonical_summary.get("xref", {}) if canonical_summary.get("available") else {}
        headline = canonical_summary.get("headline", {}) if canonical_summary.get("available") else {}
        canonical_function = {
            "available": canonical_summary.get("available", False),
            "source": canonical_summary.get("source", _CANONICAL_SUMMARY),
            "source_refs": canonical_summary.get("source_refs", [_CANONICAL_SUMMARY]),
            "total": canonical.get("row_count", optional_counts.get("triage")),
            "unique_va": canonical.get("unique_va_count", optional_counts.get("triage")),
            "snapshot_sha256": canonical.get("snapshot_sha256"),
        }
        xrefs = {
            "available": canonical_summary.get("available", _has_table(conn, "xref")),
            "source": xref_summary.get("source", "sqlite:xref"),
            "source_refs": _source_refs(xref_summary.get("source"), "sqlite:xref"),
            "total": xref_summary.get("artifact_unique_rows", optional_counts.get("xref")),
            "call_type_rows": xref_summary.get("call_type_edge_rows"),
            "reference_types": xref_summary.get("reference_types", {}),
        }
        result = _ok(db_path=db_path(db), db_exists=True,
                      user_version=conn.execute("PRAGMA user_version").fetchone()[0],
                      counts=counts, optional_counts=optional_counts,
                      canonical_triage=canonical_function,
                      canonical_function=canonical_function,
                      xrefs=xrefs,
                      headline_counts=headline,
                      source_refs=_source_refs(
                          _CANONICAL_SUMMARY,
                          xref_summary.get("summary_source")),
                      distinct_builds=conn.execute(
                          "SELECT COUNT(DISTINCT binary_sha256) FROM node"
                          " WHERE binary_sha256 IS NOT NULL").fetchone()[0],
                      limit=page[0], offset=page[1], labels=labels,
                      evidence=evidence, relations=relations,
                      investigation_statuses=investigation_statuses,
                      investigation_stages=investigation_stages,
                      tests=tests, traces=traces)
        result["summary"] = {
            "counts": counts,
            "canonical_triage": canonical_function,
            "xrefs": xrefs,
            "headline_counts": headline,
            "distinct_builds": result["distinct_builds"],
        }
        return result
    finally:
        conn.close()


def simulator_hierarchy(depth=2, limit=_MAX_GRAPH_NODES,
                        edge_limit=_MAX_GRAPH_EDGES, root=None, db=None):
    page, bad = _page(limit, 0, default=_MAX_GRAPH_NODES,
                      maximum=_MAX_GRAPH_NODES)
    if bad:
        return bad
    edge_page, bad = _page(edge_limit, 0, default=_MAX_GRAPH_EDGES,
                          maximum=_MAX_GRAPH_EDGES)
    if bad:
        return bad
    try:
        depth = int(depth)
    except (TypeError, ValueError):
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    if depth < 1 or depth > 3:
        return _err("invalid_params", "'depth' must be an integer from 1 to 3")
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        subsystem_rows = conn.execute(
            "SELECT * FROM node WHERE label='Subsystem' AND (name=?"
            " OR (json_valid(attrs_json) AND json_extract(attrs_json, '$.name')=?))"
            " ORDER BY CASE WHEN name='sub:Simulator' THEN 0 ELSE 1 END, id LIMIT 1",
            ("sub:Simulator", "Simulator")).fetchall()
        subsystem = _node_row(subsystem_rows[0]) if subsystem_rows else None
        loaded = _load_json_artifact(_SIMULATOR_ARTIFACT)
        artifact = loaded.get("value") if loaded.get("available") else {}
        artifact = artifact if isinstance(artifact, dict) else {}
        artifact_roots = [row for row in artifact.get("roots", [])
                          if isinstance(row, dict)]
        roots_by_id = {_normalize_va(row.get("root")): row
                       for row in artifact_roots
                       if _normalize_va(row.get("root"))}
        full_order = []
        for value in artifact.get("root_order", []):
            va = _normalize_va(value)
            if va and va not in full_order:
                full_order.append(va)
        artifact_functions = {}
        for row in artifact.get("nodes", []):
            if isinstance(row, dict) and _normalize_va(row.get("id")):
                artifact_functions[_normalize_va(row.get("id"))] = row
        selected_row = None
        selected_va = None
        if root is not None:
            selected_row, bad = _resolve_node(conn, root)
            if bad:
                selected_va = _normalize_va(root)
                if selected_va not in roots_by_id:
                    return bad
            else:
                name_candidates = _va_candidates(selected_row["name"])
                selected_va = name_candidates[0] if name_candidates else None
                if not selected_va:
                    attrs = selected_row["attrs_json"]
                    attrs = _parse_jsonish(attrs) or {}
                    selected_va = _normalize_va(
                        attrs.get("address") or attrs.get("va") or attrs.get("rva"))
                if selected_row["label"] != "Function" or not selected_va:
                    return _err("not_found", "node %r is not a Function" % root)
        if root is None:
            selected_order = full_order[:page[0]]
        elif selected_va in roots_by_id:
            selected_order = [selected_va]
        else:
            selected_order = full_order[:page[0]]
        selected_roots = [roots_by_id[va] for va in selected_order
                          if va in roots_by_id]
        root_function_ids = set()
        nodes_by_id = {}
        functions_out = []
        selected_function = None

        def add_node(node):
            if not node or node.get("id") in nodes_by_id:
                return node.get("id") if node else None
            nodes_by_id[node["id"]] = node
            return node["id"]

        def function_for_va(va):
            va = _normalize_va(va)
            if not va:
                return None
            rows = conn.execute(
                "SELECT * FROM node WHERE label='Function' AND (name=?"
                " OR name=? OR (json_valid(attrs_json) AND"
                " (json_extract(attrs_json, '$.address')=? OR"
                " json_extract(attrs_json, '$.va')=? OR"
                " json_extract(attrs_json, '$.rva')=?)))"
                " ORDER BY name, id LIMIT 1",
                ("fun:" + va, va, va, va, va)).fetchall()
            if rows:
                return _node_row(rows[0])
            record = artifact_functions.get(va)
            if not record:
                return None
            return {"id": "artifact:function:" + va, "label": "Function",
                    "name": record.get("name") or ("FUN_" + va),
                    "origin": "artifact", "evidence_level": "UNKNOWN",
                    "attrs": {"artifact": record},
                    "source_refs": [_SIMULATOR_ARTIFACT]}

        for artifact_root in selected_roots:
            va = _normalize_va(artifact_root.get("root"))
            function = function_for_va(va)
            if function is None:
                continue
            function = dict(function)
            function["artifact_root"] = artifact_root
            function["source_refs"] = _source_refs(
                _SIMULATOR_ARTIFACT, artifact_root.get("evidence"),
                function.get("attrs", {}).get("source"))
            functions_out.append(function)
            add_node(function)
            root_function_ids.add(function["id"])
            if root is not None and va == selected_va:
                selected_function = function
        if root is not None and selected_va not in roots_by_id:
            selected_function = function_for_va(selected_va)
            if selected_function is None:
                return _err("not_found", "no Function node for %r" % root)
            selected_function = dict(selected_function)
            selected_function["selected"] = True
            selected_function["source_refs"] = _source_refs(
                "sqlite:node/%s" % selected_function["id"],
                _SIMULATOR_ARTIFACT)
            functions_out.append(selected_function)
            add_node(selected_function)
        if subsystem is not None:
            add_node(subsystem)

        structure_nodes = []
        structure_ids_by_name = {}
        structure_records = [row for row in artifact.get("structures", [])
                             if isinstance(row, dict)][:page[0]]
        for record in structure_records:
            name = record.get("name")
            if not isinstance(name, str) or not name:
                continue
            candidate_names = [name, "struct:Simulator::" + name,
                               "struct:/Spore/Simulator/" + name]
            marks = ",".join("?" * len(candidate_names))
            rows = conn.execute(
                "SELECT * FROM node WHERE label='Structure' AND name IN (%s)"
                " ORDER BY name, id" % marks, candidate_names).fetchall()
            ids = []
            for row in rows:
                node = _node_row(row)
                ids.append(add_node(node))
                structure_nodes.append(node)
            if not rows:
                node = {"id": "artifact:structure:" + name,
                        "label": "Structure", "name": name,
                        "origin": "artifact",
                        "evidence_level": record.get("evidence_level", "UNKNOWN"),
                        "attrs": {"artifact": record},
                        "source_refs": [_SIMULATOR_ARTIFACT]}
                add_node(node)
                structure_nodes.append(node)
                ids = [node["id"]]
            structure_ids_by_name[name] = [value for value in ids if value]

        def resolve_structure(ref):
            if not isinstance(ref, str):
                return None
            rows = conn.execute(
                "SELECT * FROM node WHERE label='Structure' AND name=? ORDER BY id LIMIT 1",
                (ref,)).fetchall()
            if rows:
                return add_node(_node_row(rows[0]))
            short_name = ref.split("::")[-1].split("/")[-1]
            values = structure_ids_by_name.get(short_name, [])
            return values[0] if values else None

        def resolve_destination(ref):
            if not isinstance(ref, str):
                return None
            function_va = _normalize_va(ref[4:] if ref.startswith("fun:") else ref)
            if function_va and (ref.startswith("fun:") or len(function_va) == 8):
                node = function_for_va(function_va)
                return add_node(node) if node else None
            if ref.startswith("struct:"):
                return resolve_structure(ref)
            rows = conn.execute(
                "SELECT * FROM node WHERE name=? ORDER BY label, id LIMIT 1",
                (ref,)).fetchall()
            return add_node(_node_row(rows[0])) if rows else None

        edges_by_id = {}

        def add_edge(edge_id, src, dst, rel, source_refs):
            if not src or not dst or src == dst:
                return
            edge = {"id": edge_id, "src": src, "dst": dst, "rel": rel,
                    "source_refs": list(dict.fromkeys(source_refs))}
            edges_by_id.setdefault(edge_id, edge)

        actual_ids = [node_id for node_id in nodes_by_id if isinstance(node_id, int)]
        db_edges = []
        for chunk in _chunks(actual_ids):
            if len(db_edges) >= edge_page[0]:
                break
            marks = ",".join("?" * len(chunk))
            db_edges.extend(conn.execute(
                "SELECT id, src, dst, rel FROM edge WHERE src IN (%s) OR dst IN (%s)"
                " ORDER BY id LIMIT ?" % (marks, marks),
                chunk + chunk + [edge_page[0] - len(db_edges)]).fetchall())
        for edge in db_edges:
            for endpoint in (edge["src"], edge["dst"]):
                if endpoint not in nodes_by_id:
                    row = conn.execute("SELECT * FROM node WHERE id=?",
                                       (endpoint,)).fetchone()
                    if row:
                        add_node(_node_row(row))
            add_edge(edge["id"], edge["src"], edge["dst"], edge["rel"],
                     ["sqlite:edge/%s" % edge["id"]])

        artifact_edges = []
        for edge in artifact.get("edges", []):
            if len(artifact_edges) >= edge_page[0]:
                break
            if not isinstance(edge, dict):
                continue
            src = resolve_destination(edge.get("from"))
            dst = resolve_destination(edge.get("to"))
            if src is None or dst is None:
                continue
            edge_id = "artifact:%s:%s:%s" % (
                edge.get("from"), edge.get("to"), edge.get("kind"))
            add_edge(edge_id, src, dst, edge.get("kind") or "related",
                     [_SIMULATOR_ARTIFACT])
            artifact_edges.append({
                "from": edge.get("from"), "to": edge.get("to"),
                "kind": edge.get("kind"), "evidence_level": edge.get("evidence_level"),
                "evidence": edge.get("evidence"),
                "source_refs": [_SIMULATOR_ARTIFACT]})

        selected_artifact = roots_by_id.get(selected_va)
        if selected_function is not None:
            selected_attrs = selected_function.get("attrs", {})
            closure = selected_attrs.get("root_closure_f0e310e0")
            closure_relationships = closure.get("relationships", []) if isinstance(closure, dict) else []
            for relationship in _bounded(closure_relationships, page[0]):
                if not isinstance(relationship, dict):
                    continue
                dst = resolve_destination(relationship.get("dst"))
                if dst is None:
                    continue
                rel = relationship.get("rel") or "related"
                add_edge("research:%s:%s:%s" % (
                    selected_function["id"], relationship.get("dst"), rel),
                    selected_function["id"], dst, rel,
                    _source_refs(relationship.get("source_refs"),
                                 relationship.get("provenance"),
                                 "sqlite:node/%s" % selected_function["id"]))
            attrs_events = selected_attrs.get("events")
            if attrs_events not in (None, 0, "", [], {}):
                selected_function["events"] = _bounded(attrs_events, page[0])
        if selected_artifact:
            for field in ("dependency_roots", "dependency_helpers"):
                for value in _bounded(selected_artifact.get(field, []), page[0]):
                    dst = resolve_destination(value)
                    if dst is not None and selected_function is not None:
                        add_edge("artifact:%s:%s" % (selected_va, value),
                                 selected_function["id"], dst, "dependency",
                                 [_SIMULATOR_ARTIFACT])

        priority_ids = []
        if subsystem is not None:
            priority_ids.append(subsystem["id"])
        if selected_function is not None:
            priority_ids.append(selected_function["id"])
        priority_ids.extend(function["id"] for function in functions_out)
        graph_nodes = []
        for node_id in priority_ids + list(nodes_by_id):
            if node_id in nodes_by_id and node_id not in {node["id"] for node in graph_nodes}:
                graph_nodes.append(nodes_by_id[node_id])
        graph_nodes = graph_nodes[:page[0]]
        graph_node_ids = {node["id"] for node in graph_nodes}
        graph_edges = [edge for edge in edges_by_id.values()
                       if edge["src"] in graph_node_ids and edge["dst"] in graph_node_ids]
        graph_edges = sorted(graph_edges, key=lambda edge: str(edge["id"]))[:edge_page[0]]
        classes = [node for node in graph_nodes if node.get("label") == "Class"]
        packages = [node for node in graph_nodes if node.get("label") == "Package"]
        dependent_functions = [node for node in graph_nodes
                               if node.get("label") == "Function"
                               and node.get("id") not in root_function_ids
                               and node.get("id") != (selected_function or {}).get("id")]
        research_states = []
        research_events = []
        callbacks = []
        transitions = []
        research = {"available": False, "source_refs": []}
        if selected_function is not None:
            research_states, research_events, callbacks, transitions, research = \
                _research_for_function(selected_va, selected_function.get("name"),
                                       min(page[0], _MAX_DETAIL_ITEMS))
        structures = structure_records
        interfaces = sorted(artifact_edges[:edge_page[0]], key=lambda item: (
            str(item.get("from") or ""), str(item.get("to") or ""),
            str(item.get("kind") or "")))
        return _ok(available=subsystem is not None,
                   artifact_available=bool(loaded.get("available")),
                   root=subsystem, subsystem=subsystem,
                   root_order=selected_order,
                   roots=selected_roots,
                   selected_ref=("fun:" + selected_va) if selected_va else None,
                   selected_function=selected_function,
                   selected_artifact=selected_artifact,
                   nodes=graph_nodes,
                   edges=graph_edges,
                   interfaces=interfaces,
                   functions=functions_out[:page[0]],
                   classes=classes[:page[0]],
                   packages=packages[:page[0]],
                   dependent_functions=dependent_functions[:page[0]],
                   structures=structures,
                   structure_nodes=structure_nodes[:page[0]],
                   state_machines=research_states,
                   events=research_events,
                   callbacks=callbacks,
                   transitions=transitions,
                   source=_SIMULATOR_ARTIFACT,
                   source_refs=loaded.get("source_refs", [_SIMULATOR_ARTIFACT]),
                   snapshot=(artifact.get("snapshot", {}).get("id")
                             if isinstance(artifact.get("snapshot"), dict) else None),
                   limit=page[0], edge_limit=edge_page[0],
                   truncated=(len(selected_order) < len(full_order)
                              or len(db_edges) >= edge_page[0]
                              or len(graph_nodes) >= page[0]
                              or len(edges_by_id) > len(graph_edges)))
    finally:
        conn.close()


def hotspots(limit=100, offset=0, label=None, relation=None, db=None):
    page, bad = _page(limit, offset, default=100, maximum=_MAX_ITEMS)
    if bad:
        return bad
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        label_clause = " WHERE n.label=?" if label is not None else ""
        label_args = [label] if label is not None else []
        total = conn.execute("SELECT COUNT(*) FROM node n" + label_clause,
                             label_args).fetchone()[0]
        rel_where = " WHERE rel=?" if relation is not None else ""
        rel_args = [relation] if relation is not None else []
        has_triage = _has_table(conn, "triage")
        triage_join = ("LEFT JOIN triage t ON t.kg_node_id=n.name"
                       if has_triage else "")
        triage_fields = ("t.caller_count, t.callee_count,"
                         " COALESCE(t.caller_count,0) + COALESCE(t.callee_count,0)"
                         " + d.out_degree + d.in_degree AS score"
                         if has_triage else
                         "NULL AS caller_count, NULL AS callee_count,"
                         " d.out_degree + d.in_degree AS score")
        sql = (
            "WITH degree AS ("
            " SELECT n.id, COALESCE(o.n,0) AS out_degree,"
            " COALESCE(i.n,0) AS in_degree FROM node n"
            " LEFT JOIN (SELECT src, COUNT(*) AS n FROM edge%s"
            " GROUP BY src) o ON o.src=n.id"
            " LEFT JOIN (SELECT dst, COUNT(*) AS n FROM edge%s"
            " GROUP BY dst) i ON i.dst=n.id)"
            " SELECT d.id, n.label, n.name, n.evidence_level, n.origin,"
            " n.confidence, n.updated_at, n.binary_sha256, d.out_degree,"
            " d.in_degree, d.out_degree + d.in_degree AS edge_degree, %s"
            " FROM degree d JOIN node n ON n.id=d.id %s%s"
            " ORDER BY score DESC, d.in_degree DESC, d.out_degree DESC, n.id"
            " LIMIT ? OFFSET ?"
            % (rel_where, rel_where, triage_fields, triage_join, label_clause))
        rows = conn.execute(sql, rel_args + rel_args + label_args
                            + [page[0], page[1]]).fetchall()
        values = [dict(r) for r in rows]
        return _ok(total=total, limit=page[0], offset=page[1],
                   hotspots=values, centrality=values, nodes=values)
    finally:
        conn.close()


def centrality(limit=100, offset=0, label=None, relation=None, db=None):
    return hotspots(limit, offset, label, relation, db)


def _function_candidates(node):
    attrs = node.get("attrs", {})
    values = []
    for key in ("va", "address", "rva", "addr"):
        value = attrs.get(key)
        if isinstance(value, list):
            values.extend(value)
        elif value is not None:
            values.append(value)
    name = str(node.get("name", ""))
    if name.startswith("fun:"):
        values.append(name[4:])
    result = set()
    for value in values:
        value = str(value).strip().lower()
        if value.startswith("0x"):
            value = value[2:]
        if value:
            result.add(value)
    return sorted(result)


def function_detail(ref, limit=200, db=None):
    page, bad = _page(limit, 0, default=200, maximum=_MAX_LIMIT)
    if bad:
        return bad
    base = node_detail(ref, db, limit=page[0])
    if base.get("status") != "ok":
        return base
    node = base["node"]
    if node["label"] != "Function":
        return _err("not_found", "node %r is not a Function" % ref)
    conn, guard = _open(db)
    if conn is None:
        return guard
    try:
        attrs = node.get("attrs", {}) if isinstance(node.get("attrs"), dict) else {}
        candidates = _function_candidates(node)
        triage = None
        if _has_table(conn, "triage") and candidates:
            marks = ",".join("?" * len(candidates))
            row = conn.execute(
                "SELECT * FROM triage WHERE kg_node_id=? OR va IN (%s)"
                " OR ghidra_name IN (%s) ORDER BY va LIMIT 1"
                % (marks, marks),
                [node["name"]] + candidates + candidates).fetchone()
            if row is not None:
                triage = dict(row)
                for key in ("vtable_addrs", "struct_names"):
                    if triage.get(key) is not None:
                        triage[key] = _parse_jsonish(triage[key])
        xrefs = []
        callers = []
        callees = []
        xref_counts = {"rows": 0, "callers": 0, "callees": 0,
                       "incoming_rows": 0, "outgoing_rows": 0,
                       "triage_caller_count": (triage or {}).get("caller_count"),
                       "triage_callee_count": (triage or {}).get("callee_count")}
        if _has_table(conn, "xref") and candidates:
            marks = ",".join("?" * len(candidates))
            incoming = conn.execute(
                "SELECT COUNT(*), COUNT(DISTINCT caller_va) FROM xref"
                " WHERE callee_va IN (%s)" % marks, candidates).fetchone()
            outgoing = conn.execute(
                "SELECT COUNT(*), COUNT(DISTINCT callee_va) FROM xref"
                " WHERE caller_va IN (%s)" % marks, candidates).fetchone()
            combined = conn.execute(
                "SELECT COUNT(*) FROM xref WHERE caller_va IN (%s)"
                " OR callee_va IN (%s)" % (marks, marks),
                candidates + candidates).fetchone()[0]
            xref_counts.update({
                "incoming_rows": incoming[0], "callers": incoming[1],
                "outgoing_rows": outgoing[0], "callees": outgoing[1],
                "rows": combined,
            })
            xref_rows = conn.execute(
                "SELECT caller_va, callee_va, reference_type, callsite_va,"
                " source, snapshot_sha256 FROM xref"
                " WHERE caller_va IN (%s) OR callee_va IN (%s)"
                " ORDER BY caller_va, callee_va, callsite_va, source LIMIT ?"
                % (marks, marks),
                candidates + candidates + [page[0]]).fetchall()
            xrefs = [dict(r) for r in xref_rows]
            callers = [{"va": r["va"]} for r in conn.execute(
                "SELECT DISTINCT caller_va AS va FROM xref"
                " WHERE callee_va IN (%s) ORDER BY caller_va LIMIT ?"
                % marks, candidates + [page[0]]).fetchall()]
            callees = [{"va": r["va"]} for r in conn.execute(
                "SELECT DISTINCT callee_va AS va FROM xref"
                " WHERE caller_va IN (%s) ORDER BY callee_va LIMIT ?"
                % marks, candidates + [page[0]]).fetchall()]
        readiness_data = _readiness_data()
        function_value = dict(node)
        _attach_readiness(function_value, readiness_data)
        va = _normalize_va(function_value.get("readiness_record", {}).get("va")
                           if isinstance(function_value.get("readiness_record"), dict)
                           else None) or (candidates[0] if candidates else None)
        readiness_record = readiness_data.get("functions", {}).get(va) if va else None
        research_states, research_events, callbacks, transitions, research = \
            _research_for_function(va, function_value.get("name"),
                                   min(page[0], _MAX_DETAIL_ITEMS))
        simulator = _load_json_artifact(_SIMULATOR_ARTIFACT)
        simulator_root = None
        if simulator.get("available") and va:
            simulator_root = next((row for row in simulator["value"].get("roots", [])
                                   if isinstance(row, dict)
                                   and _normalize_va(row.get("root")) == va), None)
        structure_names = set()
        for value in _bounded((triage or {}).get("struct_names") or [], page[0]):
            if isinstance(value, str):
                structure_names.add(value)
        closure = attrs.get("root_closure_f0e310e0")
        relationships = closure.get("relationships", []) if isinstance(closure, dict) else []
        for relationship in _bounded(relationships, page[0]):
            destination = relationship.get("dst") if isinstance(relationship, dict) else None
            if isinstance(destination, str) and destination.startswith("struct:"):
                structure_names.add(destination)
        for machine in research_states:
            for value in _bounded(machine.get("relevant_structures", []), page[0]):
                if isinstance(value, str):
                    structure_names.add(value)
        if simulator_root:
            if isinstance(simulator_root.get("backing_structure"), str):
                structure_names.add(simulator_root["backing_structure"])
            for field in _bounded(simulator_root.get("fields", []), page[0]):
                if isinstance(field, dict) and isinstance(field.get("structure"), str):
                    structure_names.add(field["structure"])
        artifact_structures = {}
        if simulator.get("available"):
            artifact_structures = {
                row.get("name"): row for row in _bounded(
                    simulator["value"].get("structures", []), page[0])
                if isinstance(row, dict) and row.get("name")
            }
        related_structures = []
        related_fields = []
        for name in sorted(structure_names)[:page[0]]:
            node_rows = conn.execute(
                "SELECT * FROM node WHERE label='Structure' AND name=?"
                " ORDER BY id LIMIT 1", (name,)).fetchall()
            structure = _node_row(node_rows[0]) if node_rows else None
            fields = []
            if node_rows:
                fields = [dict(field) for field in conn.execute(
                    "SELECT * FROM field WHERE struct_id=? ORDER BY offset, id LIMIT ?",
                    (node_rows[0]["id"], page[0])).fetchall()]
            artifact_structure = artifact_structures.get(name)
            if artifact_structure:
                fields.extend(field for field in _bounded(
                    artifact_structure.get("known_offsets", []), page[0])
                              if isinstance(field, str))
            value = {
                "name": name,
                "node": structure,
                "artifact": artifact_structure,
                "fields": fields,
                "source_refs": _source_refs(
                    "sqlite:node/%s" % structure["id"] if structure else None,
                    _SIMULATOR_ARTIFACT if artifact_structure else None,
                    (artifact_structure or {}).get("provenance")),
            }
            related_structures.append(value)
            for field in fields:
                if len(related_fields) >= page[0]:
                    break
                related_fields.append({"structure": name, "field": field,
                                       "source_ref": "sqlite:field"})
        db_events = []
        if attrs.get("events") not in (None, 0, "", [], {}):
            db_events.append({"origin": "db_attrs",
                              "value": _bounded(attrs["events"], page[0]),
                              "source_refs": ["sqlite:node/%s" % node["id"]]})
        metadata = {
            "id": node["id"], "label": node["label"], "name": node["name"],
            "address": attrs.get("address"), "rva": attrs.get("rva"),
            "va": attrs.get("va"), "addr": attrs.get("addr"),
            "sdk_name": attrs.get("sdk_name"),
            "signature": attrs.get("signature"),
            "source": attrs.get("src") or attrs.get("source"),
            "decompiled_file": attrs.get("decompiled_file"),
            "trace": attrs.get("trace"), "evidence": attrs.get("evidence"),
            "origin": node["origin"], "binary_sha256": node["binary_sha256"],
        }
        engine_boundary = None
        unresolved = []
        if simulator_root:
            engine_boundary = {
                "category": simulator_root.get("category"),
                "contract": simulator_root.get("reconstruction_boundary"),
                "backing_structure": simulator_root.get("backing_structure"),
                "evidence": simulator_root.get("evidence"),
                "source_refs": [_SIMULATOR_ARTIFACT],
            }
            unresolved.extend(_bounded(simulator_root.get("unresolved", []), page[0]))
        source_refs = _source_refs(
            "sqlite:node/%s" % node["id"], "sqlite:triage",
            "sqlite:xref", readiness_data.get("source_refs"),
            research.get("source_refs"),
            [_SIMULATOR_ARTIFACT] if simulator_root else None,
            attrs.get("source"), attrs.get("src"), attrs.get("decompiled_file"),
            (readiness_record or {}).get("provenance"),
            simulator_root.get("evidence") if simulator_root else None)
        source_refs = source_refs[:_MAX_DETAIL_ITEMS]
        base["function"] = function_value
        base["metadata"] = metadata
        base["triage"] = triage
        base["canonical_function"] = {
            "available": triage is not None,
            "va": va,
            "source": "sqlite:triage" if triage is not None else None,
        }
        base["readiness"] = function_value.get("readiness")
        base["readiness_source"] = {
            "available": readiness_record is not None,
            "artifact_available": readiness_data.get("available", False),
            "source": readiness_data.get("source"),
            "source_refs": readiness_data.get("source_refs", []),
        }
        base["readiness_record"] = readiness_record
        base["xrefs"] = xrefs
        base["xref_total"] = xref_counts["rows"]
        base["xref_counts"] = xref_counts
        base["xref_truncated"] = len(xrefs) < xref_counts["rows"]
        base["callers"] = callers
        base["callees"] = callees
        base["related_structures"] = related_structures
        base["fields"] = related_fields
        base["state_machines"] = research_states
        base["events"] = (db_events + research_events)[:page[0]]
        base["callbacks"] = callbacks
        base["transitions"] = transitions
        base["engine_boundary"] = engine_boundary
        base["unresolved"] = list(dict.fromkeys(unresolved))[:page[0]]
        base["source_refs"] = source_refs
        provenance = dict(base.get("provenance", {}))
        provenance.update({
            "triage_kg_node_id": (triage or {}).get("kg_node_id"),
            "triage_snapshot_sha256": (triage or {}).get("snapshot_sha256"),
            "decomp_path": (triage or {}).get("decomp_path"),
            "readiness_snapshot": readiness_data.get("snapshot"),
            "research_snapshot": research.get("available"),
            "source_refs": source_refs,
        })
        base["provenance"] = provenance
        base["limit"] = page[0]
        return base
    finally:
        conn.close()


# --------------------------------------------------------------------------- #
# CLI
# --------------------------------------------------------------------------- #
def main(argv=None):
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("command", choices=[
        "summary", "statistics", "evidence", "labels", "readiness",
        "investigations", "investigations-list", "subsystems",
        "architecture", "hierarchy", "packages", "functions", "search", "types",
        "states", "events", "simulator", "hotspots", "centrality",
        "nodes", "node", "neighbors", "subgraph", "function",
        "investigation"])
    ap.add_argument("ref", nargs="?", help="node id/name or investigation id")
    ap.add_argument("--db", default=None, help="DB path (abs, or rel vs repo root)")
    ap.add_argument("--label", default=None)
    ap.add_argument("--q", default=None)
    ap.add_argument("--limit", type=int, default=200)
    ap.add_argument("--offset", type=int, default=0)
    ap.add_argument("--depth", type=int, default=1)
    ap.add_argument("--edge-limit", type=int, default=2000)
    ap.add_argument("--kind", default=None)
    ap.add_argument("--status", default=None)
    ap.add_argument("--evidence", default=None)
    ap.add_argument("--origin", default=None)
    ap.add_argument("--readiness", default=None)
    ap.add_argument("--subsystem", default=None)
    ap.add_argument("--package", default=None)
    ap.add_argument("--relation", default=None)
    args = ap.parse_args(argv)
    if args.command in ("node", "neighbors", "subgraph", "function",
                        "investigation") and not args.ref:
        ap.error("%s requires a ref" % args.command)
    if args.command == "summary":
        result = summary(args.db)
    elif args.command == "statistics":
        result = statistics(args.limit, args.offset, args.db)
    elif args.command == "evidence":
        result = evidence_distribution(args.db, args.limit, args.offset)
    elif args.command == "labels":
        result = node_label_distribution(args.db, args.limit, args.offset)
    elif args.command == "readiness":
        result = readiness_distribution(args.limit, args.offset, args.db)
    elif args.command == "investigations":
        result = investigation_status_distribution(args.db)
    elif args.command == "investigations-list":
        result = investigations_list(args.kind, args.q, args.status,
                                     args.limit, args.offset, args.db,
                                     args.readiness)
    elif args.command == "subsystems":
        result = subsystem_summary(args.db)
    elif args.command in ("architecture", "hierarchy"):
        result = (architecture if args.command == "architecture" else hierarchy)(
            args.ref, args.depth, args.limit, args.edge_limit, args.offset, args.db)
    elif args.command == "packages":
        result = packages(args.q, args.limit, args.offset, args.db)
    elif args.command == "functions":
        result = functions(args.q, args.evidence, args.readiness,
                           args.subsystem, args.package, args.limit,
                           args.offset, args.db)
    elif args.command == "search":
        result = search(args.q, args.label, args.evidence, args.origin,
                        args.readiness, args.limit, args.offset, args.db)
    elif args.command == "types":
        result = types(args.q, args.limit, args.offset, args.db)
    elif args.command == "states":
        result = states(args.limit, args.offset, args.db)
    elif args.command == "events":
        result = events(args.limit, args.offset, args.db)
    elif args.command == "simulator":
        result = simulator_hierarchy(args.depth, args.limit, args.edge_limit,
                                     args.ref, args.db)
    elif args.command in ("hotspots", "centrality"):
        result = hotspots(args.limit, args.offset, args.label, args.relation,
                          args.db)
    elif args.command == "nodes":
        result = nodes(args.label, args.q, args.limit, args.offset, args.db,
                       args.evidence, args.origin, args.readiness)
    elif args.command == "node":
        result = node_detail(args.ref, args.db)
    elif args.command == "neighbors":
        result = node_neighbors(args.ref, args.depth, args.db, args.limit,
                                args.edge_limit)
    elif args.command == "subgraph":
        result = subgraph(args.ref, args.depth, args.limit, args.edge_limit,
                          args.db)
    elif args.command == "function":
        result = function_detail(args.ref, args.limit, args.db)
    else:
        result = investigation_detail(args.ref, args.db)
    print(json.dumps(result, indent=2, sort_keys=True))
    return 0 if result.get("status") == "ok" else 1


if __name__ == "__main__":
    sys.exit(main())
