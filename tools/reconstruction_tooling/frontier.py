import json
import sqlite3
from pathlib import Path

from .models import ROOT, ToolError, normalize_va, optional_json

try:
    from tools import reconstruction_knowledge as rk
except ImportError as exc:
    raise RuntimeError("reconstruction knowledge module is unavailable") from exc

QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
DB_REL = "knowledgegraph/spore.db"
EVIDENCE_ORDER = {
    "UNKNOWN": 0,
    "APPROXIMATION": 1,
    "INFERRED": 2,
    "SUPPORTED": 3,
    "OBSERVED": 4,
    "CONFIRMED": 5,
    "VERIFIED": 6,
}
PRIORITY = {"P0": 35, "P1": 21, "P2": 11, "P3": 4}
CALL_TYPES = {"direct-call", "thunk", "external", "computed-call"}


_INDEX_CACHE = {}


def _index(root):
    root = Path(root).resolve()
    key = str(root)
    if key in _INDEX_CACHE:
        return _INDEX_CACHE[key]
    try:
        index, _bootstrap = rk.build_index(root)
    except Exception as exc:
        raise ToolError("index_unavailable", "reconstruction projection cannot be built from canonical inputs: %s" % exc, 4)
    index = dict(index)
    index["_tooling_projection"] = {"rebuilt": True, "source": "ephemeral reconstruction_knowledge.build_index", "disk_path": "reconstruction/knowledge/index.json"}
    _INDEX_CACHE[key] = index
    return index


def _queue(root):
    path = Path(root) / QUEUE_REL
    document = optional_json(path)
    if not isinstance(document, dict):
        raise ToolError("frontier_unavailable", "canonical triage queue is unavailable: %s" % QUEUE_REL, 4)
    return document


def _manifest_binary(root, index):
    binary = index.get("binary", {}) if isinstance(index, dict) else {}
    if isinstance(binary, dict) and binary.get("sha256"):
        return str(binary["sha256"])
    document = optional_json(Path(root) / MANIFEST_REL) or {}
    binary = document.get("binary", {}) if isinstance(document, dict) else {}
    return binary.get("sha256") if isinstance(binary, dict) else None


def _claims(root, vas):
    if not vas:
        return None
    root = Path(root)
    if root.resolve() == ROOT.resolve():
        try:
            from tools.mcp import config
            database = config.db_path()
            if not Path(database).exists():
                return None
            connection = sqlite3.connect("file:%s?mode=ro" % database, uri=True, timeout=2)
            try:
                table = connection.execute("select 1 from sqlite_master where type='table' and name='investigations'").fetchone()
            finally:
                connection.close()
            if table is None:
                return None
            from tools.mcp.reconstruction_tools import _claims as canonical_claims
            return canonical_claims(set(vas))
        except (ImportError, OSError, sqlite3.Error):
            return None
    path = root / DB_REL
    if not path.exists():
        return None
    result = {}
    try:
        connection = sqlite3.connect("file:%s?mode=ro" % path, uri=True, timeout=2)
        try:
            table = connection.execute("select 1 from sqlite_master where type='table' and name='investigations'").fetchone()
            if table is None:
                return None
            columns = {row[1] for row in connection.execute("pragma table_info(investigations)")}
            wanted = [name for name in ("id", "va", "status", "implementer_id", "binary_sha256", "block_reason", "stage", "updated_at") if name in columns]
            for row in connection.execute("select %s from investigations where kind='function'" % ",".join(wanted)):
                item = dict(zip(wanted, row))
                try:
                    va = normalize_va(item.get("va"))
                except (TypeError, ValueError):
                    continue
                if va in vas:
                    result.setdefault(va, []).append(item)
        finally:
            connection.close()
    except sqlite3.Error:
        return None
    return result


def _queue_rows(root, index):
    rows = {}
    document = _queue(root)
    for row in document.get("queue", []):
        if not isinstance(row, dict):
            continue
        try:
            va = normalize_va(row.get("va"))
        except (TypeError, ValueError):
            continue
        rows[va] = row
    for row in index.get("frontier", []):
        if not isinstance(row, dict):
            continue
        try:
            va = normalize_va(row.get("va"))
        except (TypeError, ValueError):
            continue
        rows.setdefault(va, row)
    return rows


def _status(record, row):
    if record and record.get("status"):
        return str(record["status"])
    try:
        return rk.status_for(record or {}, row or {})
    except Exception:
        return (row or {}).get("queue_state") or "unresolved"


def _reason(code, detail, source="persisted", state="present", ref=None):
    return {"code": code, "detail": detail, "source": source, "state": state, "ref": ref}


def _record_paths(record, root):
    source = record.get("source", {}) if isinstance(record, dict) else {}
    values = []
    for key in ("file",):
        if source.get(key):
            values.append(source[key])
    values.extend(source.get("files", []) or [])
    values.extend((record.get("ownership", {}).get("manifest", {}) or {}).get("source_files", []) or [])
    result = []
    for value in sorted(set(str(item) for item in values if item)):
        path = Path(root) / value
        if path.exists():
            result.append(value)
    return result


def _cluster_key(value):
    if isinstance(value, (dict, list)):
        return json.dumps(value, sort_keys=True, ensure_ascii=False)
    return str(value) if value is not None else ""


def _endpoint_va(value):
    if isinstance(value, dict):
        for key in ("va", "address", "function_address"):
            if key in value:
                try:
                    return normalize_va(value[key])
                except (TypeError, ValueError):
                    return None
        return None
    try:
        return normalize_va(value)
    except (TypeError, ValueError):
        return None


def _analogues(record):
    return sorted(record.get("analogues", []) or [], key=lambda item: (-float(item.get("score", 0) or 0), str(item.get("va", ""))))


def _score(record, row, root, known_records, cluster_counts):
    priority = str(row.get("priority", "")).upper()
    priority_score = PRIORITY.get(priority, 0)
    evidence = str(record.get("evidence_level") or row.get("evidence") or "UNKNOWN").upper()
    evidence_score = EVIDENCE_ORDER.get(evidence, 0) * 4
    dependencies = record.get("dependencies", {}) if isinstance(record, dict) else {}
    callers = [endpoint for endpoint in (_endpoint_va(item) for item in dependencies.get("callers", []) or []) if endpoint]
    callees = [endpoint for endpoint in (_endpoint_va(item) for item in dependencies.get("callees", []) or []) if endpoint]
    source_paths = _record_paths(record, root)
    decomp_path = (record.get("source", {}) or {}).get("decomp") or row.get("decomp_path")
    inspectability = 0
    reasons = []
    if decomp_path and (Path(root) / str(decomp_path)).exists():
        inspectability += 10
        reasons.append(_reason("decomp_available", "persisted decompilation capture exists", ref=str(decomp_path)))
    if source_paths:
        inspectability += 4
        reasons.append(_reason("source_available", "canonical source path exists", ref=source_paths[0]))
    if (record.get("source", {}) or {}).get("metadata"):
        inspectability += 4
    open_callees = []
    for callee in callees:
        target = known_records.get(callee, {})
        if _status(target, {}) not in ("reconstructed", "runtime_gated", "integrated"):
            open_callees.append(callee)
    dependency_uncertain = bool(dependencies.get("callees_truncated") or dependencies.get("edges_truncated"))
    dependency_score = 10 if not open_callees and not dependency_uncertain else 0
    reconstructed_callers = sum(1 for caller in callers if _status(known_records.get(caller, {}), {}) == "reconstructed")
    dependency_score += 3 if reconstructed_callers else 0
    analogue_score = 0
    analogues = _analogues(record)
    if analogues:
        top = float(analogues[0].get("score", 0) or 0)
        analogue_score = 6 if top >= 25 else 4 if top >= 12 else 2 if top >= 5 else 0
    cluster = row.get("cluster") or record.get("cluster")
    cluster_key = _cluster_key(cluster)
    cluster_score = 6 if cluster_counts.get(cluster_key, 0) >= 3 else 3 if cluster_counts.get(cluster_key, 0) >= 1 else 0
    runtime_gates = (record.get("runtime", {}) or {}).get("gates", []) or row.get("runtime_gates", []) or []
    runtime_score = -12 if runtime_gates else 0
    if runtime_gates:
        reasons.append(_reason("runtime_gate", "runtime or operator evidence is still required", ref="runtime.gates"))
    value = max(0, min(100, priority_score + evidence_score + min(24, inspectability) + dependency_score + analogue_score + cluster_score + runtime_score))
    if priority_score:
        reasons.append(_reason("priority", "classifier priority %s" % priority, ref=QUEUE_REL))
    if open_callees:
        reasons.append(_reason("open_dependencies", "internal callees not reconstructed: %s" % ", ".join(open_callees), source="derived", ref="reconstruction/knowledge/index.json#/records"))
    elif dependency_uncertain:
        reasons.append(_reason("dependency_list_truncated", "dependency evidence is truncated; readiness is unknown", source="derived", ref="reconstruction/knowledge/index.json#/records"))
    else:
        reasons.append(_reason("dependencies_ready", "no unresolved internal callees", source="derived", ref="reconstruction/knowledge/index.json#/records"))
    reasons.append(_reason("fan_in", "callers=%d" % len(callers), source="derived", ref="reconstruction/knowledge/index.json#/records"))
    reasons.append(_reason("fan_out", "callees=%d" % len(callees), source="derived", ref="reconstruction/knowledge/index.json#/records"))
    return value, {"priority": priority_score, "evidence": evidence_score, "inspectability": inspectability, "dependencies": dependency_score, "analogues": analogue_score, "cluster": cluster_score, "runtime": runtime_score}, reasons, open_callees, dependency_uncertain


def _claim_view(claims, current_binary, coordination_available=True):
    if not coordination_available:
        return {"state": "coordination_missing", "claimable": False, "id": None, "implementer_id": None, "binary_sha256": None, "block_reason": None, "stage": None, "claims": [], "claim_count": 0}
    if not claims:
        return {"state": "unclaimed", "claimable": True, "id": None, "implementer_id": None, "binary_sha256": None, "block_reason": None, "claims": [], "claim_count": 0}
    if isinstance(claims, dict):
        claims = [claims]
    current = [item for item in claims if not item.get("binary_sha256") or item.get("binary_sha256") == current_binary]
    if not current:
        return {"state": "stale_binary", "claimable": False, "id": None, "implementer_id": None, "binary_sha256": None, "block_reason": None, "stage": None, "claims": claims}
    current.sort(key=lambda item: (str(item.get("updated_at") or ""), str(item.get("id") or "")), reverse=True)
    selected = current[0]
    states = {str(item.get("status") or "queued") for item in current}
    if "blocked" in states:
        state = "blocked"
        claimable = False
    elif any(item.get("implementer_id") for item in current if str(item.get("status")) == "active"):
        state = "claimed"
        claimable = False
    elif "active" in states:
        state = "active_unowned"
        claimable = False
    elif states.issubset({"done", "dropped"}):
        state = "completed"
        claimable = False
    else:
        state = "queued_same_sha"
        claimable = True
    top_level = selected if len(current) == 1 or len({(item.get("status"), item.get("implementer_id"), item.get("block_reason"), item.get("stage")) for item in current}) == 1 else {}
    ids = {str(item.get("id")) for item in current if item.get("id")}
    claim_id = next(iter(ids)) if len(ids) == 1 else top_level.get("id")
    return {"state": state, "claimable": claimable, "id": claim_id, "implementer_id": top_level.get("implementer_id"), "binary_sha256": top_level.get("binary_sha256"), "block_reason": top_level.get("block_reason"), "stage": top_level.get("stage"), "claims": current, "claim_count": len(current)}


def _filter_row(target, args):
    row = target
    if getattr(args, "package", None) and str(row.get("package") or "").casefold() != args.package.casefold():
        return False
    if getattr(args, "subsystem", None) and str(row.get("subsystem") or "").casefold() != args.subsystem.casefold():
        return False
    if getattr(args, "status", None) and row.get("status") != args.status and row.get("queue_state") != args.status:
        return False
    if getattr(args, "semantic", None) and str(row.get("evidence_level") or "").upper() != args.semantic.upper():
        return False
    if getattr(args, "dependency", "any") == "ready" and row.get("disposition") != "eligible":
        return False
    if getattr(args, "dependency", "any") == "open" and not row.get("open_dependencies"):
        return False
    if getattr(args, "runtime", None) == "required" and not row.get("runtime_gates"):
        return False
    if getattr(args, "runtime", None) == "none" and row.get("runtime_gates"):
        return False
    if getattr(args, "claimed", None) is True and not row.get("claim", {}).get("implementer_id"):
        return False
    if getattr(args, "claimed", None) is False and row.get("claim", {}).get("implementer_id"):
        return False
    if getattr(args, "unclaimed", False) and not row.get("claim", {}).get("claimable", False):
        return False
    if getattr(args, "gameplay", None) and str(row.get("gameplay_affinity") or row.get("category") or "").casefold() != args.gameplay.casefold():
        return False
    return True


def frontier(root=ROOT, args=None):
    root = Path(root)
    index = _index(root)
    records = index.get("records", {}) if isinstance(index.get("records", {}), dict) else {}
    rows = _queue_rows(root, index)
    claims = _claims(root, set(rows))
    current_binary = _manifest_binary(root, index)
    cluster_counts = {}
    for row in rows.values():
        cluster = row.get("cluster")
        if cluster:
            cluster_key = _cluster_key(cluster)
            cluster_counts[cluster_key] = cluster_counts.get(cluster_key, 0) + 1
    targets = []
    for va in sorted(rows):
        row = rows[va]
        record = records.get(va, {})
        status = _status(record, row)
        score, components, reasons, open_callees, dependency_uncertain = _score(record, row, root, records, cluster_counts)
        claim = _claim_view(claims.get(va) if claims is not None else None, current_binary, claims is not None)
        if status in ("reconstructed", "blocked") or claim["state"] in ("completed", "blocked"):
            disposition = "excluded"
            reason_code = "already_completed" if status == "reconstructed" or claim["state"] == "completed" else "blocked"
            reasons.append(_reason(reason_code, "target is not claimable", source="derived"))
        elif claim["state"] in ("claimed", "stale_binary", "active_unowned"):
            disposition = "excluded"
            reasons.append(_reason("claim_conflict", "coordination state is %s" % claim["state"], source="persisted", ref="db:investigations"))
        elif claim["state"] == "coordination_missing":
            disposition = "excluded"
            reasons.append(_reason("coordination_missing", "SQLite claim state could not be read", source="missing", ref="db:investigations"))
        elif open_callees or dependency_uncertain:
            disposition = "deferred"
            reasons.append(_reason("dependency_deferred", "open or truncated internal dependencies require ordered work", source="derived"))
        else:
            disposition = "eligible"
        dependencies = record.get("dependencies", {}) or {}
        callers = [endpoint for endpoint in (_endpoint_va(item) for item in dependencies.get("callers", []) or []) if endpoint]
        callees = [endpoint for endpoint in (_endpoint_va(item) for item in dependencies.get("callees", []) or []) if endpoint]
        target = {
            "va": va,
            "name": row.get("name") or record.get("name") or record.get("normalized_symbol"),
            "package": row.get("package") or record.get("package"),
            "subsystem": row.get("subsystem") or record.get("subsystem"),
            "category": row.get("category"),
            "gameplay_affinity": row.get("gameplay_affinity") or row.get("category"),
            "cluster": row.get("cluster") or record.get("cluster"),
            "status": status,
            "queue_state": row.get("queue_state"),
            "evidence_level": record.get("evidence_level") or row.get("evidence"),
            "score": score,
            "score_components": components,
            "fan_in": len(callers),
            "fan_out": len(callees),
            "runtime_gates": (record.get("runtime", {}) or {}).get("gates", []) or row.get("runtime_gates", []) or [],
            "dependencies": {"open_callees": open_callees, "callers": callers, "callees": callees},
            "open_dependencies": open_callees,
            "dependency_uncertain": dependency_uncertain,
            "disposition": disposition,
            "claim": claim,
            "reasons": reasons,
            "evidence_refs": [QUEUE_REL, "reconstruction/knowledge/index.json#/records/%s" % va],
        }
        if _filter_row(target, args or object()):
            targets.append(target)
    targets.sort(key=lambda item: (-item["score"], str(item.get("va"))))
    total = len(targets)
    limit = max(1, min(int(getattr(args, "limit", 20) or 20), 1000))
    offset = max(0, int(getattr(args, "offset", 0) or 0))
    selected = targets[offset:offset + limit]
    summary = {name: sum(1 for item in targets if item.get("disposition") == name) for name in ("eligible", "deferred", "excluded")}
    return {
        "schema": "openspore-frontier-1",
        "source_of_truth": {"manifest": MANIFEST_REL, "queue": QUEUE_REL, "derived_index": "reconstruction/knowledge/index.json", "claims": "db:investigations"},
        "projection": index.get("_tooling_projection", {"rebuilt": False, "source": "reconstruction/knowledge/index.json"}),
        "binary_sha256": current_binary,
        "scoring": {"version": "frontier-score-1", "note": "ordering aid only; scores are not evidence", "weights": {"priority": PRIORITY, "evidence": "scale order x4"}},
        "summary": summary,
        "count": len(selected),
        "total": total,
        "truncated": offset + len(selected) < total,
        "targets": selected,
    }
