import json
from pathlib import Path

from .evidence import EVIDENCE_REL
from .models import ROOT, ToolError, compact, normalize_va, write_json_atomic, write_text_atomic

INDEX_REL = "reconstruction/knowledge/index.json"


def _section(state, data, provenance, omitted=0):
    if isinstance(data, dict) and data.get("truncated"):
        omitted = max(omitted, 1)
    return {"state": state, "data": data, "provenance": provenance, "omitted": {"count": omitted}}


def _record(index, va):
    records = index.get("records", {}) if isinstance(index, dict) else {}
    return records.get(va, {}) if isinstance(records, dict) else {}


def _question_values(record, evidence):
    values = []
    values.extend(record.get("unresolved_questions", []) or [])
    values.extend((record.get("runtime", {}) or {}).get("gates", []) or [])
    values.extend((record.get("semantic", {}) or {}).get("unresolved_questions", []) if isinstance(record.get("semantic"), dict) else [])
    conflicts = evidence.get("conflicts", []) or []
    if isinstance(conflicts, dict) and conflicts.get("truncated"):
        conflicts = conflicts.get("preview", "")
    for conflict in conflicts if isinstance(conflicts, list) else []:
        if isinstance(conflict, dict) and conflict.get("statement"):
            values.append(conflict["statement"])
    result = []
    for value in values:
        if isinstance(value, str) and value.strip():
            result.append(value.strip())
        elif value:
            result.append(json.dumps(value, sort_keys=True, ensure_ascii=False))
    return sorted(set(result))


def build(root=ROOT, va=None, evidence=None, live=False, write=True, out_dir=None):
    root = Path(root)
    if va is None:
        raise ToolError("missing_va", "a target VA is required", 2)
    try:
        va = normalize_va(va)
    except (TypeError, ValueError) as exc:
        raise ToolError("invalid_va", str(exc), 2)
    if evidence is None:
        from .evidence import collect
        evidence = collect(root=root, va=va, live=live, write=write, out_dir=out_dir)
    try:
        from .evidence import _index
        index = _index(root)
    except (OSError, ValueError) as exc:
        raise ToolError("index_unavailable", "generated reconstruction index is unavailable: %s" % exc, 4)
    record = _record(index, va)
    categories = evidence.get("categories", {})
    dependencies = record.get("dependencies", {}) or {}
    source = record.get("source", {}) or {}
    runtime = record.get("runtime", {}) or {}
    semantic = record.get("semantic") or {}
    analogues = record.get("analogues", []) or []
    edge_rows = dependencies.get("edge_rows") or dependencies.get("edges") or []
    reconstruction_available = categories.get("reconstruction", {}).get("availability") == "available"
    reconstruction_source = categories.get("reconstruction", {}).get("value") or {} if reconstruction_available else {}
    caller_values = dependencies.get("callers") or []
    callee_values = dependencies.get("callees") or []
    external_values = dependencies.get("external_callees") or []
    type_values = record.get("types") or []
    global_values = record.get("globals") or []
    vtable_values = record.get("vtables") or []
    analogue_values = analogues
    caller_omitted = max(0, len(caller_values) - 16)
    callee_omitted = max(0, len(callee_values) - 16)
    external_omitted = max(0, len(external_values) - 16)
    edge_omitted = max(0, len(edge_rows) - 24)
    type_omitted = max(0, len(type_values) - 16)
    global_omitted = max(0, len(global_values) - 12)
    vtable_omitted = max(0, len(vtable_values) - 12)
    analogue_omitted = max(0, len(analogue_values) - 12)
    # The ABI channel reads the persisted record first and the evidence pack
    # second. Previously it read only the record, which made the channel
    # structurally empty for every record without a persisted ABI -- and
    # ``worker_contract`` then told the worker to "derive it from the
    # disassembly", which is unavailable on the same CLI path. The pack already
    # carries the answer (a derived projection once ``abi_infer`` is present), so
    # the fallback is the only missing link. Provenance follows the *source* of
    # whichever value won, so a derived record is never indistinguishable from a
    # persisted one.
    abi_category = categories.get("abi", {}) or {}
    persisted_abi = record.get("abi")
    if persisted_abi:
        abi_state, abi_value, abi_provenance = (
            "present", compact(persisted_abi, 5000), [INDEX_REL])
    elif abi_category.get("availability") == "available":
        abi_state = "present"
        abi_value = compact(abi_category.get("value"), 5000)
        abi_provenance = list(abi_category.get("provenance") or [INDEX_REL])
    else:
        abi_state, abi_value, abi_provenance = (
            "missing", compact(persisted_abi or {}, 5000), [INDEX_REL])
    sections = {
        "01_assignment": _section("present", {"assignment_id": "openspore-context", "phase": "reconstruction", "objective": "recover bounded source semantics for %s" % va, "target": va}, [INDEX_REL]),
        "02_function_identity": _section("present" if record else "missing", {"va": va, "name": record.get("name") or record.get("normalized_symbol"), "package": record.get("package"), "subsystem": record.get("subsystem"), "class_type": record.get("class_type")}, [INDEX_REL]),
        "03_current_status": _section("present" if record.get("status") else "missing", {"status": record.get("status"), "reconstructed": record.get("reconstructed"), "blocked": record.get("blocked"), "runtime_gated": record.get("runtime_gated"), "runtime_validated": runtime.get("validated", 0)}, [INDEX_REL]),
        "04_evidence_state": _section("present", {"overall": evidence.get("evidence_state"), "live_requested": evidence.get("collector", {}).get("live_requested"), "live_attempts": evidence.get("collector", {}).get("live_attempts", []), "content_sha256": evidence.get("content_sha256")}, [INDEX_REL]),
        "05_decompilation": _section("present" if categories.get("decompilation", {}).get("availability") == "available" else "missing", compact(categories.get("decompilation", {}).get("value"), 10000), categories.get("decompilation", {}).get("provenance", [])),
        "06_abi": _section(abi_state, abi_value, abi_provenance),
        "07_callers_callees": _section("present" if dependencies else "missing", compact({"callers": caller_values[:16], "callees": callee_values[:16], "external_callees": external_values[:16], "edge_rows": edge_rows[:24]}, 10000), [INDEX_REL], caller_omitted + callee_omitted + external_omitted + edge_omitted),
        "08_types_fields_globals": _section("present" if type_values or global_values or vtable_values else "missing", compact({"types": type_values[:16], "globals": global_values[:12], "vtables": vtable_values[:12]}, 6000), [INDEX_REL], type_omitted + global_omitted + vtable_omitted),
        "09_state_event_relationships": _section("present" if record.get("semantic") or runtime.get("gates") else "missing", compact({"semantic": semantic, "runtime": runtime}, 7000), ["knowledgegraph/research/semantic-decomp.json", INDEX_REL]),
        "10_dependencies": _section("present" if dependencies else "missing", compact(dependencies, 10000), [INDEX_REL]),
        "11_related_functions": _section("present" if analogue_values else "missing", compact(analogue_values[:12], 6000), [INDEX_REL], analogue_omitted),
        "12_existing_reconstruction": _section("present" if reconstruction_source else "missing", compact(reconstruction_source, 6000), [INDEX_REL]),
        "13_semantic_hypotheses": _section("present" if semantic else "missing", compact(semantic, 6000), ["knowledgegraph/research/semantic-decomp.json"]),
        "14_conflicts_questions": _section("conflicted" if evidence.get("conflicts") else "present", compact({"conflicts": evidence.get("conflicts", []), "unresolved_questions": _question_values(record, evidence)}, 9000), [INDEX_REL, "knowledgegraph/research/semantic-decomp.json"]),
        "15_validation_and_provenance": _section("present", {"required_categories": ["ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS", "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS", "EVIDENCE COVERAGE"], "provenance": evidence.get("provenance", []), "read_first": [INDEX_REL] + [item for item in (reconstruction_source.get("file"), reconstruction_source.get("decomp")) if item]}, evidence.get("provenance", [])),
    }
    # ``status`` is a claim about this document, so the gate has to be the same
    # test the section used -- otherwise a filled ``06_abi`` and a ``partial``
    # document disagree with no visible reason. It is evaluated on the *category*
    # rather than on the section so the two can never drift.
    #
    # A DERIVED ABI does not satisfy it. Every other ABI source here (the
    # persisted record, a live query) states a convention it read; a derived
    # record is an inference over the disassembly, and a document that calls
    # itself ``complete`` on an inference is exactly the overclaim the
    # DERIVED/INFERRED label exists to prevent. This leaves today's reachable
    # set of ``complete`` documents unchanged -- the section is filled and the
    # worker is unblocked either way -- while keeping the door open for the
    # moment the ABI is observed rather than inferred.
    critical_available = all(
        categories.get(name, {}).get("availability") == "available"
        for name in ("ghidra_function", "decompilation")) and (
            categories.get("abi", {}).get("availability") == "available"
            and categories.get("abi", {}).get("evidence_state") != "DERIVED")
    result = {
        "schema": "openspore-agent-context-1",
        "target": va,
        "status": "complete" if record and critical_available else "partial",
        "context_state_counts": {state: sum(1 for value in sections.values() if value["state"] == state) for state in ("present", "partial", "missing", "conflicted")},
        "sections": sections,
        "content_sha256": None,
    }
    from .models import sha256_json
    result["content_sha256"] = sha256_json(result)
    destination = Path(out_dir) if out_dir else Path(root) / EVIDENCE_REL / va[2:]
    if write:
        write_json_atomic(destination / "context.json", result)
        write_text_atomic(destination / "context.md", render_markdown(result))
    result["paths"] = {"directory": str(destination), "written": bool(write), "context_json": str(destination / "context.json") if write else None, "context_md": str(destination / "context.md") if write else None}
    return result


def _value_lines(value, limit=1600):
    text = json.dumps(value, indent=2, sort_keys=True, ensure_ascii=False) if not isinstance(value, str) else value
    if len(text) <= limit:
        return text
    return text[:limit] + "\n[TRUNCATED]"


def render_markdown(result):
    lines = ["# Reconstruction context %s" % result["target"], "", "- Status: `%s`" % result["status"], "- Content SHA-256: `%s`" % result["content_sha256"], ""]
    for name, section in result["sections"].items():
        lines.extend(["## %s" % name, "", "- State: `%s`" % section["state"], "- Provenance: `%s`" % ", ".join(str(item) for item in section.get("provenance", []) or []), ""])
        if section.get("data") not in (None, {}, []):
            lines.extend(["```json", _value_lines(section["data"]), "```", ""])
    return "\n".join(lines)
