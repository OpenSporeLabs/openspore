#!/usr/bin/env python3
"""Generate and query the OpenSpore reconstruction knowledge projection."""
from __future__ import print_function

import argparse
import hashlib
import json
import os
import re
import sys
import tempfile
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_INDEX = ROOT / "reconstruction" / "knowledge" / "index.json"
DEFAULT_BOOTSTRAP = ROOT / "reconstruction" / "knowledge" / "bootstrap.json"
MANIFEST_REL = "knowledgegraph/research/source-reconstruction-manifest.json"
QUEUE_REL = "knowledgegraph/triage/queue-f0e310e0-v6.json"
XREF_REL = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
XREF_SUMMARY_REL = "knowledgegraph/triage/xrefs-2540f2ca.summary.json"
SEMANTIC_REL = "knowledgegraph/research/semantic-decomp.json"
CONFLICT_DIR_REL = "knowledgegraph/research/conflicts"
METADATA_DIR_REL = "reconstruction/metadata"
HANDOFF_DIR_REL = "reconstruction/integrated"

HEX8 = re.compile(r"^(?:0x)?([0-9a-fA-F]{1,8})$")
ADDRESS = re.compile(r"0x[0-9a-fA-F]{4,8}")
BARE_ADDRESS = re.compile(r"(?<![0-9a-fA-F])([0-9a-fA-F]{8})(?![0-9a-fA-F])")
CALL_TYPES = frozenset(("direct-call", "thunk", "external", "computed-call"))
MAX_LIST = 12
MAX_TEXT = 600
MAX_DEPENDENCY_NODES = 50
MAX_DEPENDENCY_EDGES = 30
ANALOGUE_IGNORED_TYPES = frozenset((
    "void", "bool", "char", "short", "int", "long", "float", "double",
    "uint8_t", "uint16_t", "uint32_t", "uint64_t", "int8_t", "int16_t",
    "int32_t", "int64_t", "std::uint8_t", "std::uint16_t",
    "std::uint32_t", "std::uint64_t", "std::int8_t", "std::int16_t",
    "std::int32_t", "std::int64_t",
))


def load_json(path):
    with path.open(encoding="utf-8") as handle:
        return json.load(handle)


def relative(path, root):
    try:
        return str(path.relative_to(root))
    except ValueError:
        return str(path)


def normalize_va(value):
    if isinstance(value, bool):
        raise ValueError("boolean is not a VA")
    if isinstance(value, int):
        number = value
    elif isinstance(value, str):
        text = value.strip().lower()
        if text.startswith("rva:"):
            text = text[4:]
        match = HEX8.match(text)
        if not match:
            raise ValueError("invalid VA: %r" % value)
        number = int(match.group(1), 16)
    else:
        raise ValueError("invalid VA: %r" % value)
    if number < 0 or number > 0xFFFFFFFF:
        raise ValueError("VA outside x86-32 range: %r" % value)
    return "0x%08x" % number


def maybe_va(value):
    try:
        return normalize_va(value)
    except (TypeError, ValueError):
        return None


def sorted_unique(values):
    return sorted(set(value for value in values if value))


def bounded(value, depth=0):
    if isinstance(value, str):
        return value if len(value) <= MAX_TEXT else value[:MAX_TEXT - 3] + "..."
    if isinstance(value, (int, float, bool)) or value is None:
        return value
    if isinstance(value, list):
        return [bounded(item, depth + 1) for item in value[:MAX_LIST]]
    if isinstance(value, dict):
        if depth >= 3:
            return {"keys": sorted(value)[:MAX_LIST]}
        return {str(key): bounded(value[key], depth + 1)
                for key in sorted(value)[:MAX_LIST]}
    return bounded(str(value), depth + 1)


def walk_values(value, wanted, path=()):
    if isinstance(value, dict):
        for key in sorted(value):
            child = value[key]
            if key in wanted:
                yield path + (key,), child
            yield from walk_values(child, wanted, path + (key,))
    elif isinstance(value, list):
        for index, child in enumerate(value):
            yield from walk_values(child, wanted, path + (str(index),))


def address_values(value, path=()):
    found = []
    if isinstance(value, str):
        for match in ADDRESS.finditer(value):
            parsed = maybe_va(match.group(0))
            if parsed:
                found.append(parsed)
        if not ADDRESS.search(value):
            match = BARE_ADDRESS.fullmatch(value.strip())
            parsed = maybe_va(match.group(1)) if match else None
            if parsed:
                found.append(parsed)
    elif isinstance(value, dict):
        for key in sorted(value):
            found.extend(address_values(value[key], path + (key,)))
    elif isinstance(value, list):
        for index, child in enumerate(value):
            found.extend(address_values(child, path + (str(index),)))
    return found


def source_fields(value):
    if isinstance(value, str):
        return [value]
    if isinstance(value, list):
        return [item for item in value if isinstance(item, str)]
    if isinstance(value, dict):
        result = []
        for key in ("source", "path", "artifact", "header", "implementation",
                    "model_test", "canonical_source", "canonical_path"):
            if isinstance(value.get(key), str):
                result.append(value[key])
        return result
    return []


def extract_va(document):
    preferred = ("va", "address", "function_address", "functionAddress",
                 "entry_address", "entry", "body_start")
    for key in preferred:
        if key not in document:
            continue
        value = document[key]
        if isinstance(value, str):
            parsed = maybe_va(value)
            if parsed:
                return parsed
        elif isinstance(value, dict):
            for nested in address_values(value):
                return nested
    for key in ("function_extent", "body", "address_evidence"):
        parsed = address_values(document.get(key))
        if parsed:
            return parsed[0]
    return None


def merge_values(old, new):
    if isinstance(old, list) or isinstance(new, list):
        left = old if isinstance(old, list) else []
        right = new if isinstance(new, list) else []
        return sorted_unique([str(item) for item in left + right])
    if old in (None, "", [], {}):
        return new
    if new in (None, "", [], {}):
        return old
    if old == new:
        return old
    if isinstance(old, dict) and isinstance(new, dict):
        result = dict(old)
        for key, value in new.items():
            result[key] = merge_values(result.get(key), value)
        return result
    return [old, new]


def extract_abi(document):
    candidates = []
    for key in ("observed_original_abi", "original_native_abi", "live_abi",
                 "implementation_abi_and_boundary", "native_port_abi",
                 "port_abi", "boundary_abi", "abi", "calling_convention"):
        if key in document:
            candidates.append(document[key])
    selected = {}
    wanted = {
        "architecture", "calling_convention", "convention", "return_type",
        "return_width_bytes", "return_register", "stack_cleanup_bytes",
        "stack_cleanup_owner", "hidden_this_register", "hidden_receiver",
        "hidden_this", "hidden_this_type", "receiver_register", "receiver",
        "stack_arguments", "ordinary_stack_arguments",
        "ordinary_stack_argument_slots", "saved_registers", "ret_form",
        "termination", "return_semantics", "return", "return_observation",
    }
    for candidate in candidates:
        if isinstance(candidate, str):
            selected.setdefault("calling_convention", candidate)
            continue
        for path, value in walk_values(candidate, wanted):
            key = path[-1]
            if key in selected and selected[key] not in (None, "", [], {}):
                continue
            selected[key] = bounded(value)
    convention = selected.get("calling_convention")
    if convention is None and isinstance(document.get("signature_status"), str):
        text = document["signature_status"].lower()
        if "thiscall" in text:
            convention = "thiscall"
        elif "cdecl" in text:
            convention = "cdecl"
        elif "fastcall" in text:
            convention = "fastcall"
        elif "stdcall" in text:
            convention = "stdcall"
    if convention is not None:
        selected["calling_convention"] = convention
    return selected


def extract_types(document, manifest_types):
    result = set(manifest_types)
    wanted = {
        "type", "type_name", "type_identity", "ghidra_type", "live_type",
        "staging_type", "receiver_type", "hidden_this_type", "class_type",
        "return_type", "empire_type", "space_player_data_type",
    }
    for path, value in walk_values(document, wanted):
        if isinstance(value, str):
            result.add(value)
        elif isinstance(value, list):
            result.update(item for item in value if isinstance(item, str))
    for key in ("type_dependencies", "types", "related_types",
                "related_structures", "structures", "port_abis"):
        value = document.get(key)
        if isinstance(value, list):
            result.update(item for item in value if isinstance(item, str))
    return sorted_unique(result)


def ref_id(address, name, kind):
    if address:
        return "%s:%s" % (kind, address)
    if name:
        return "%s:%s" % (kind, name)
    return None


def extract_refs(document):
    refs = {}
    keys = ("address", "global_address", "table_address", "vtable_address",
            "vptr", "primary_vtable", "secondary_vtable", "tertiary_vtable")
    names = ("name", "global_name", "service_global", "service_name",
             "source_global", "root_global", "state_global")
    roles = ("role", "meaning", "observation", "identity", "access")

    def add(kind, key, value, path):
        address = None
        name = None
        role = None
        if isinstance(value, str):
            text = value.strip()
            address = maybe_va(text)
            if not address and (text.startswith("DAT_") or
                                text.startswith("s") and "Global" in text):
                name = text
            if address is None and kind == "global" and len(text) < 100:
                name = text
        elif isinstance(value, dict):
            for address_key in keys:
                if address_key in value:
                    address = maybe_va(value[address_key])
                    if address:
                        break
            for name_key in names:
                if name_key in value and isinstance(value[name_key], str):
                    name = value[name_key]
                    break
            for role_key in roles:
                if role_key in value and isinstance(value[role_key], str):
                    role = value[role_key]
                    break
            if address is None:
                address = next(iter(address_values(value)), None)
        if kind == "vtable" and address is None:
            return
        if kind == "service" and address is None and not name:
            return
        identifier = ref_id(address, name, kind)
        if identifier is None:
            return
        entry = refs.setdefault(identifier, {
            "id": identifier, "kind": kind, "address": address,
            "name": name, "roles": [], "evidence_paths": [],
        })
        if role and role not in entry["roles"]:
            entry["roles"].append(role)
        evidence_path = ".".join(path)
        if evidence_path not in entry["evidence_paths"]:
            entry["evidence_paths"].append(evidence_path)

    def visit(value, path=()):
        if isinstance(value, dict):
            for key in sorted(value):
                child = value[key]
                lower = key.lower()
                if "global" in lower or lower in ("root", "service_slot"):
                    add("global", key, child, path + (key,))
                if "service" in lower or lower in ("activation_service",):
                    add("service", key, child, path + (key,))
                if "vtable" in lower or lower in ("table_address", "pseudorel"):
                    add("vtable", key, child, path + (key,))
                visit(child, path + (key,))
        elif isinstance(value, list):
            for index, child in enumerate(value):
                visit(child, path + (str(index),))

    visit(document)
    for entry in refs.values():
        entry["roles"] = sorted_unique(entry["roles"])
        entry["evidence_paths"] = sorted_unique(entry["evidence_paths"])
    return sorted(refs.values(), key=lambda entry: entry["id"])


def extract_metadata(root):
    result = defaultdict(lambda: {
        "paths": [], "schemas": [], "types": [], "globals": [],
        "vtables": [], "services": [], "unresolved_questions": [],
        "blockers": [], "runtime_gates": [], "source_files": [],
        "evidence": [], "abi": {},
    })
    metadata_dir = root / METADATA_DIR_REL
    for path in sorted(metadata_dir.rglob("*.json")):
        try:
            document = load_json(path)
        except (OSError, ValueError):
            continue
        va = extract_va(document)
        if va is None:
            continue
        entry = result[va]
        path_text = relative(path, root)
        entry["paths"].append(path_text)
        if isinstance(document.get("schema"), str):
            entry["schemas"].append(document["schema"])
        entry["types"].extend(extract_types(document, []))
        for ref in extract_refs(document):
            entry[ref["kind"] + "s"].append(ref["id"])
        for key in ("unresolved_questions", "blockers", "runtime_gates",
                    "source_files", "source_provenance", "evidence"):
            value = document.get(key)
            if isinstance(value, list):
                entry["unresolved_questions" if key == "unresolved_questions"
                      else "blockers" if key == "blockers"
                      else "runtime_gates" if key == "runtime_gates"
                      else "source_files" if key == "source_files"
                      else "evidence"].extend(
                          item for item in value if isinstance(item, str))
        entry["abi"] = merge_values(entry["abi"], extract_abi(document))
        implementation = document.get("implementation")
        if isinstance(implementation, dict):
            entry["source_files"].extend(source_fields(implementation))
            if implementation.get("runtime_gate"):
                entry["runtime_gates"].append(implementation["runtime_gate"])
        entry["source_files"].extend(source_fields(document.get("source")))
        entry["source_files"].extend(source_fields(document.get("intended_paths")))
        entry["evidence"].extend(source_fields(document))
    for entry in result.values():
        for key in entry:
            if isinstance(entry[key], list):
                entry[key] = sorted_unique(entry[key])
    return dict(result)


def extract_handoffs(root):
    result = defaultdict(lambda: {
        "paths": [], "packages": [], "runtime_gates": [],
        "evidence": [], "source_files": [], "review_status": [],
    })
    handoff_dir = root / HANDOFF_DIR_REL
    for path in sorted(handoff_dir.rglob("handoff.json")):
        try:
            document = load_json(path)
        except (OSError, ValueError):
            continue
        path_text = relative(path, root)
        package_rows = document.get("packages", [])
        function_rows = document.get("functions", [])
        package_ids = []
        for package in package_rows:
            if isinstance(package, dict) and isinstance(package.get("id"), str):
                package_ids.append(package["id"])
                for va in package.get("functions", []):
                    parsed = maybe_va(va)
                    if parsed:
                        entry = result[parsed]
                        entry["paths"].append(path_text)
                        entry["packages"].append(package["id"])
                        entry["source_files"].extend(
                            item for item in package.get("canonical_files", [])
                            if isinstance(item, str))
                        entry["evidence"].extend(
                            item for item in package.get("evidence_files", [])
                            if isinstance(item, str))
        for function in function_rows:
            if not isinstance(function, dict):
                continue
            parsed = maybe_va(function.get("va"))
            if not parsed:
                continue
            entry = result[parsed]
            entry["paths"].append(path_text)
            entry["packages"].append(str(function.get("package", "")))
            entry["source_files"].extend(
                item for item in function.get("canonical_files", [])
                if isinstance(item, str))
            entry["evidence"].extend(
                item for item in function.get("evidence", [])
                if isinstance(item, str))
            entry["runtime_gates"].extend(
                item for item in function.get("runtime_gates", [])
                if isinstance(item, str))
        for key in ("review_status", "integration_status"):
            if isinstance(document.get(key), str):
                for va in list(result):
                    if path_text in result[va]["paths"]:
                        result[va]["review_status"].append(document[key])
    for entry in result.values():
        for key in entry:
            if isinstance(entry[key], list):
                entry[key] = sorted_unique(item for item in entry[key] if item)
    return dict(result)


def compact_semantic(record):
    confidence = record.get("confidence")
    if isinstance(confidence, dict):
        confidence = {key: confidence[key] for key in sorted(confidence)
                      if key in ("overall", "identity", "mechanics", "runtime",
                                 "ownership", "persistence", "events")}
    readiness = record.get("readiness")
    if isinstance(readiness, dict):
        readiness = {key: readiness[key] for key in sorted(readiness)
                     if key in ("status", "next_action", "runtime_required",
                                "runtime_performed", "runtime_promoted",
                                "unlock_requirements")}
    return {
        "va": maybe_va(record.get("va")),
        "name": record.get("semantic_name") or record.get("name"),
        "package": record.get("package"),
        "subsystem": record.get("subsystem"),
        "classification": record.get("classification"),
        "confidence": bounded(confidence),
        "readiness": bounded(readiness),
        "family": record.get("semantic_family"),
        "category": record.get("category"),
        "downstream_unlock_count": record.get("downstream_unlock_count"),
        "unresolved_questions": bounded(record.get("unresolved_questions", [])),
        "contradictions": bounded(record.get("contradictions", [])),
        "interfaces": bounded(record.get("interfaces", [])),
        "state_events": bounded(record.get("state_events", [])),
        "invariants": bounded(record.get("invariants", [])),
        "evidence": bounded(record.get("evidence", [])),
        "source": record.get("source"),
        "triangulation_status": record.get("triangulation_status"),
    }


def extract_semantic(root):
    path = root / SEMANTIC_REL
    document = load_json(path)
    records = {}
    for record in document.get("records", []):
        parsed = maybe_va(record.get("va"))
        if parsed:
            records[parsed] = compact_semantic(record)
    contradictions = []
    for item in document.get("contradictions", []):
        if not isinstance(item, dict):
            continue
        contradictions.append({
            "kind": "semantic_decomp_contradiction",
            "va": maybe_va(item.get("va")),
            "anchors": address_values(item.get("value", item)),
            "source": item.get("source"),
            "path": item.get("path"),
            "statement": bounded(item.get("value", item)),
        })
    families = []
    for family in document.get("family_index", []):
        if isinstance(family, dict):
            families.append({
                "family": family.get("family"),
                "members": [maybe_va(item) or item for item in family.get(
                    "assigned_members", [])],
                "source_workers": family.get("source_workers", []),
            })
    return records, contradictions, families


def rejection_entries(value, path=()):
    result = []
    if isinstance(value, dict):
        status = " ".join(str(value.get(key, "")) for key in (
            "status", "classification", "decision", "merge_decision",
            "resolution_status", "taxonomy"))
        for key in ("claim", "statement", "hypothesis", "preferred_claim"):
            text = value.get(key)
            if isinstance(text, str) and ("reject" in text.lower() or
                                          "do not promote" in text.lower() or
                                          "not promoted" in text.lower()):
                result.append({
                    "path": ".".join(path + (key,)),
                    "text": bounded(text),
                    "status": bounded(status) if status else None,
                })
        if "reject" in status.lower():
            for key in ("claim", "statement", "preferred_claim", "reason"):
                if key in value:
                    result.append({
                        "path": ".".join(path + (key,)),
                        "text": bounded(value[key]),
                        "status": bounded(status),
                    })
        for key in sorted(value):
            result.extend(rejection_entries(value[key], path + (key,)))
    elif isinstance(value, list):
        for index, child in enumerate(value):
            result.extend(rejection_entries(child, path + (str(index),)))
    unique = {}
    for item in result:
        unique[(item["path"], str(item["text"]), str(item["status"]))] = item
    return list(unique.values())


def extract_conflicts(root, semantic_contradictions):
    result = list(semantic_contradictions)
    for path in sorted((root / CONFLICT_DIR_REL).glob("*.json")):
        try:
            document = load_json(path)
        except (OSError, ValueError):
            continue
        entries = document.get("conflicts")
        if not isinstance(entries, list):
            entries = document.get("records", [])
        if not isinstance(entries, list):
            continue
        for entry in entries:
            if not isinstance(entry, dict):
                continue
            conflict_id = entry.get("conflict_id") or entry.get("id")
            if not conflict_id:
                continue
            resolution = entry.get("resolution")
            if isinstance(resolution, dict):
                resolution_status = resolution.get("status") or resolution.get(
                    "taxonomy")
            else:
                resolution_status = resolution
            rejected = rejection_entries(entry)
            unresolved = entry.get("unresolved_reason")
            if not rejected and not unresolved and resolution_status not in (
                    "unresolved", "CONFLICT_REMAINS", "preserve"):
                continue
            result.append({
                "kind": "conflict_ledger",
                "conflict_id": conflict_id,
                "subject": entry.get("subject") or entry.get("domain"),
                "anchors": address_values(entry)[:16],
                "resolution": bounded(resolution),
                "resolution_status": resolution_status,
                "rejected": bounded(rejected),
                "unresolved_reason": bounded(unresolved),
                "source": relative(path, root),
            })
    unique = {}
    for item in result:
        key = (item.get("kind"), item.get("conflict_id"), item.get("va"),
               item.get("source"), str(item.get("statement", "")))
        unique[key] = item
    return sorted(unique.values(), key=lambda item: (
        item.get("kind", ""), str(item.get("conflict_id", item.get("va", ""))),
        str(item.get("source", "")), str(item.get("statement", ""))))


def load_xrefs(root, target_vas):
    edges = defaultdict(lambda: {
        "callers": set(), "callees": set(), "external_callees": set(),
        "vtable_refs": 0, "data_refs": 0, "edge_rows": [],
    })
    path = root / XREF_REL
    with path.open(encoding="utf-8") as handle:
        next(handle, None)
        for line in handle:
            fields = line.rstrip("\n").split("\t")
            if len(fields) < 4:
                continue
            caller = maybe_va(fields[0])
            raw_callee = fields[1]
            callee = maybe_va(raw_callee)
            reference_type = fields[2]
            callsite = maybe_va(fields[3]) or fields[3]
            if caller not in target_vas and callee not in target_vas:
                continue
            if caller in target_vas:
                entry = edges[caller]
                if callee in target_vas and reference_type in CALL_TYPES:
                    entry["callees"].add(callee)
                elif callee is None and reference_type == "external":
                    entry["external_callees"].add(raw_callee)
                if reference_type == "vtable-ref":
                    entry["vtable_refs"] += 1
                elif reference_type == "data-ref":
                    entry["data_refs"] += 1
                if reference_type in CALL_TYPES:
                    entry["edge_rows"].append({
                        "direction": "out", "other": callee or raw_callee,
                        "reference_type": reference_type, "callsite": callsite,
                    })
            if callee in target_vas and reference_type in CALL_TYPES:
                entry = edges[callee]
                entry["callers"].add(caller)
                entry["edge_rows"].append({
                    "direction": "in", "other": caller,
                    "reference_type": reference_type, "callsite": callsite,
                })
    for entry in edges.values():
        entry["callers"] = sorted(entry["callers"])
        entry["callees"] = sorted(entry["callees"])
        entry["external_callees"] = sorted_unique(entry["external_callees"])
        entry["edge_rows"] = sorted(
            entry["edge_rows"],
            key=lambda item: (item["direction"], str(item["other"]),
                              item["reference_type"], str(item["callsite"])))
    return dict(edges)


def strongly_connected_components(adjacency):
    index = {}
    low = {}
    stack = []
    on_stack = set()
    components = []
    counter = [0]

    def visit(node):
        index[node] = counter[0]
        low[node] = counter[0]
        counter[0] += 1
        stack.append(node)
        on_stack.add(node)
        for target in sorted(adjacency.get(node, ())):
            if target not in index:
                visit(target)
                low[node] = min(low[node], low[target])
            elif target in on_stack:
                low[node] = min(low[node], index[target])
        if low[node] == index[node]:
            component = []
            while True:
                item = stack.pop()
                on_stack.remove(item)
                component.append(item)
                if item == node:
                    break
            components.append(sorted(component))

    for node in sorted(adjacency):
        if node not in index:
            visit(node)
    components.sort(key=lambda item: item[0])
    return {
        node: {"id": "scc-%04d" % (position + 1), "size": len(component)}
        for position, component in enumerate(components)
        for node in component
    }


def dependency_record(va, edge, names, known_reconstructed, scc):
    callers = []
    for caller in edge["callers"]:
        callers.append({
            "va": caller,
            "name": names.get(caller),
            "reconstructed": caller in known_reconstructed,
        })
    callees = []
    for callee in edge["callees"]:
        callees.append({
            "va": callee,
            "name": names.get(callee),
            "reconstructed": callee in known_reconstructed,
        })
    nearby = sorted_unique(
        [item["va"] for item in callers + callees if item["reconstructed"]])
    return {
        "fan_in": len(callers),
        "fan_out": len(callees),
        "callers": callers[:MAX_DEPENDENCY_NODES],
        "callees": callees[:MAX_DEPENDENCY_NODES],
        "callers_truncated": len(callers) > MAX_DEPENDENCY_NODES,
        "callees_truncated": len(callees) > MAX_DEPENDENCY_NODES,
        "external_callees": edge["external_callees"],
        "vtable_reference_count": edge["vtable_refs"],
        "data_reference_count": edge["data_refs"],
        "nearby_reconstructed": nearby,
        "scc": scc.get(va),
        "edges": edge["edge_rows"][:MAX_DEPENDENCY_EDGES],
        "edges_truncated": len(edge["edge_rows"]) > MAX_DEPENDENCY_EDGES,
    }


def analogue_record(target, candidates, known_reconstructed, xrefs, semantic_by_va):
    target_types = set(target.get("types", [])) - ANALOGUE_IGNORED_TYPES
    target_vtables = set(target.get("vtables", []))
    target_abi = target.get("abi", {}).get("calling_convention")
    target_semantic_family = (target.get("semantic") or {}).get("family")
    target_edges = set(xrefs.get(target["va"], {}).get("callers", [])) | set(
        xrefs.get(target["va"], {}).get("callees", []))
    ranked = []
    for candidate in candidates:
        if candidate["va"] == target["va"]:
            continue
        score = 0
        reasons = []
        if target.get("package") and target.get("package") == candidate.get("package"):
            score += 8
            reasons.append("same_package")
        if target.get("subsystem") and target.get("subsystem") == candidate.get("subsystem"):
            score += 6
            reasons.append("same_subsystem")
        if target.get("class_type") and target.get("class_type") == candidate.get("class_type"):
            score += 5
            reasons.append("same_class")
        shared_types = sorted(target_types & (
            set(candidate.get("types", [])) - ANALOGUE_IGNORED_TYPES))
        if shared_types:
            score += min(9, len(shared_types) * 3)
            reasons.append("shared_types:" + ",".join(shared_types[:4]))
        shared_vtables = sorted(target_vtables & set(candidate.get("vtables", [])))
        if shared_vtables:
            score += 4
            reasons.append("shared_vtable:" + ",".join(shared_vtables[:2]))
        if target_abi and target_abi == candidate.get("abi", {}).get(
                "calling_convention"):
            score += 2
            reasons.append("same_calling_convention")
        candidate_semantic = candidate.get("semantic") or {}
        if target_semantic_family and target_semantic_family == candidate_semantic.get(
                "family"):
            score += 5
            reasons.append("same_semantic_family")
        if candidate["va"] in target_edges:
            score += 3
            reasons.append("direct_xref_neighbor")
        if score:
            ranked.append({
                "va": candidate["va"],
                "symbol": candidate.get("normalized_symbol"),
                "package": candidate.get("package"),
                "score": score,
                "match_basis": reasons,
            })
    ranked.sort(key=lambda item: (-item["score"], item["va"]))
    return ranked[:8]


def status_for(function, triage):
    body = function.get("body_status")
    integration = function.get("integration_status")
    if body == "blocked" or integration == "blocked":
        return "blocked"
    if integration == "integrated" or body == "integrated":
        return "reconstructed"
    if body == "runtime_gated" or function.get("runtime_gate") or \
            function.get("runtime_gates") or function.get("audit_runtime_gated"):
        return "runtime_gated"
    if triage and triage.get("queue_state") in ("queued", "analyzing",
                                                  "understood", "implemented"):
        return triage["queue_state"]
    return body or triage.get("queue_state") or "unresolved"


def build_index(root=ROOT):
    root = Path(root)
    manifest_path = root / MANIFEST_REL
    manifest = load_json(manifest_path)
    queue_path = root / QUEUE_REL
    queue = load_json(queue_path)
    semantic, semantic_contradictions, semantic_families = extract_semantic(root)
    metadata = extract_metadata(root)
    handoffs = extract_handoffs(root)
    manifest_functions = {}
    manifest_packages = {}
    manifest_types = {}
    for function in manifest.get("functions", []):
        va = maybe_va(function.get("va") or function.get("function_address"))
        if va:
            manifest_functions[va] = function
    for package in manifest.get("packages", []):
        if isinstance(package, dict) and package.get("id"):
            manifest_packages[str(package["id"])] = package
    for type_record in manifest.get("types", []):
        if isinstance(type_record, dict) and type_record.get("name"):
            manifest_types[str(type_record["name"])] = type_record
    triage_by_va = {}
    for row in queue.get("queue", []):
        if not isinstance(row, dict):
            continue
        va = maybe_va(row.get("va"))
        if va:
            triage_by_va[va] = row
    target_vas = set(manifest_functions) | set(triage_by_va) | set(metadata) | set(handoffs)
    xrefs = load_xrefs(root, target_vas)
    names = {va: (function.get("normalized_symbol") or triage_by_va.get(va, {}).get(
        "name") or "fun:%s" % va[2:]) for va, function in manifest_functions.items()}
    for va, row in triage_by_va.items():
        names.setdefault(va, row.get("name") or "fun:%s" % va[2:])
    adjacency = {va: set(xrefs.get(va, {}).get("callees", ())) for va in target_vas}
    scc = strongly_connected_components(adjacency)
    known_reconstructed = {
        va for va, function in manifest_functions.items()
        if status_for(function, triage_by_va.get(va)) == "reconstructed"
    }
    records = {}
    for va in sorted(target_vas):
        function = manifest_functions.get(va, {})
        triage = triage_by_va.get(va, {})
        meta = metadata.get(va, {})
        handoff = handoffs.get(va, {})
        semantic_record = semantic.get(va)
        types = extract_types(function, function.get("type_dependencies", []))
        types = sorted_unique(types + meta.get("types", []))
        refs = []
        for key in ("globals", "vtables", "services"):
            refs.extend(meta.get(key, []))
        triage_provenance = triage.get("provenance", {})
        refs.extend("vtable:%s" % address for address in
                    (maybe_va(item) for item in
                     triage_provenance.get("vtable_addrs", []))
                    if address)
        refs = {item: item for item in refs}
        source_provenance = list(function.get("source_provenance", []))
        source_provenance.extend(meta.get("evidence", []))
        source_provenance.extend(handoff.get("evidence", []))
        source_files = []
        if isinstance(function.get("source_file"), str):
            source_files.append(function["source_file"])
        source_files.extend(item for item in function.get("source_files", [])
                            if isinstance(item, str))

        source_files.extend(meta.get("source_files", []))
        source_files.extend(handoff.get("source_files", []))
        source_files.extend(triage.get("decomp_path", []) if isinstance(
            triage.get("decomp_path"), list) else
            ([triage["decomp_path"]] if triage.get("decomp_path") else []))
        runtime_gates = []
        if isinstance(function.get("runtime_gate"), str):
            runtime_gates.append(function["runtime_gate"])
        runtime_gates.extend(item for item in function.get("runtime_gates", [])
                            if isinstance(item, str))
        runtime_gates.extend(item for item in function.get(
            "unresolved_runtime_ports", []) if isinstance(item, str))
        if function.get("runtime_validation_status") == "not_run":
            runtime_gates.append("runtime validation not run")
        runtime_gates.extend(meta.get("runtime_gates", []))

        runtime_gates.extend(handoff.get("runtime_gates", []))
        status = status_for(function, triage)
        record = {
            "va": va,
            "normalized_symbol": function.get("normalized_symbol") or triage.get("name"),
            "name": triage.get("name") or function.get("normalized_symbol"),
            "package": function.get("package") or triage.get("package") or
                       (semantic_record or {}).get("package"),
            "subsystem": function.get("subsystem") or triage.get("subsystem") or
                        (semantic_record or {}).get("subsystem"),
            "cluster": triage.get("cluster"),
            "class_type": function.get("class_type"),
            "status": status,
            "reconstructed": status == "reconstructed",
            "blocked": status == "blocked",
            "runtime_gated": status == "runtime_gated" or bool(runtime_gates),
             "runtime_validated": function.get(
                 "audit_runtime_validated", function.get("runtime_validation", 0)),

            "body_status": function.get("body_status"),
            "integration_status": function.get("integration_status"),
            "review_status": function.get("review_status"),
            "audit_status": function.get("audit_status"),
            "evidence_level": function.get("evidence_level") or triage.get("evidence"),
             "confidence": function.get("reconstruction_confidence",
                                         function.get("confidence")),

            "semantic_status": function.get("semantic_status"),
            "types": types,
            "globals": sorted(ref for ref in refs if ref.startswith("global:")),
            "vtables": sorted(ref for ref in refs if ref.startswith("vtable:")),
            "services": sorted(ref for ref in refs if ref.startswith("service:")),
            "abi": meta.get("abi", {}),
            "source": {
                "file": function.get("source_file"),
                "files": sorted_unique(source_files),
                "provenance": sorted_unique(source_provenance),
                "metadata": meta.get("paths", []),
                "handoffs": handoff.get("paths", []),
                "decomp": triage.get("decomp_path"),
            },
            "runtime": {
                "gates": sorted_unique(runtime_gates),
                "validated": function.get("audit_runtime_validated", 0),
                "blocking_reason": function.get("unresolved_questions", [])
                if status == "blocked" else None,
            },
            "unresolved_questions": sorted_unique(
                list(function.get("unresolved_questions", [])) +
                list(meta.get("unresolved_questions", []))),
            "blockers": sorted_unique(meta.get("blockers", [])),
            "triage": bounded(triage) if triage else None,
            "semantic": semantic_record,
            "ownership": {
                "manifest": {
                    "worker_ownership": function.get("worker_ownership"),
                    "record": function.get("ownership"),
                },
                "package": function.get("package") or triage.get("package"),
                "handoff_packages": handoff.get("packages", []),
                "queue_state": triage.get("queue_state"),
                "claimability": "do_not_claim" if status in (
                    "reconstructed", "blocked") else (
                        "runtime_gated_requires_explicit_gate"
                        if status == "runtime_gated" or runtime_gates
                        else "queue_candidate"),
            },
            "dependencies": dependency_record(
                va, xrefs.get(va, {
                    "callers": [], "callees": [], "external_callees": [],
                    "vtable_refs": 0, "data_refs": 0, "edge_rows": [],
                }), names, known_reconstructed, scc),
            "observed_mechanics": bounded(function.get("observed_mechanics", [])),
            "audit_evidence_boundary": function.get("audit_evidence_boundary"),
            "audit_findings": bounded(function.get("audit_findings", [])),
        }
        record["dependencies"]["manifest_callers"] = bounded(
            function.get("caller_dependencies", []))
        record["dependencies"]["manifest_callees"] = bounded(
            function.get("callee_dependencies", []))
        records[va] = record


    for va, record in records.items():
        record["analogues"] = analogue_record(
            record, [item for key, item in records.items()
                     if item.get("reconstructed")],
            known_reconstructed, xrefs, semantic)
    type_functions = defaultdict(list)
    global_functions = defaultdict(list)
    vtable_functions = defaultdict(list)
    service_functions = defaultdict(list)
    for va, record in records.items():
        for type_name in record["types"]:
            type_functions[type_name].append(va)
        for name in record["globals"]:
            global_functions[name].append(va)
        for name in record["vtables"]:
            vtable_functions[name].append(va)
        for name in record["services"]:
            service_functions[name].append(va)
    types_index = {}
    for name, source in manifest_types.items():
        types_index[name] = {
            "name": name,
            "kind": source.get("kind", "known_type"),
            "package": source.get("package"),
            "canonical_source": source.get("canonical_source"),
            "evidence_level": source.get("evidence_level"),
            "fields": bounded(source.get("fields", [])),
            "unresolved_questions": bounded(source.get("unresolved_questions", [])),
            "functions": sorted(type_functions.get(name, [])),
            "source_paths": [MANIFEST_REL],
        }
    for name in sorted(type_functions):
        types_index.setdefault(name, {
            "name": name, "kind": "referenced_type", "package": None,
            "canonical_source": None, "evidence_level": "UNKNOWN",
            "fields": [], "unresolved_questions": [],
            "functions": sorted(type_functions[name]), "source_paths": [],
        })
    def ref_index(prefix, mapping):
        result = {}
        for identifier in sorted(mapping):
            result[identifier] = {
                "id": identifier,
                "functions": sorted(mapping[identifier]),
                "count": len(mapping[identifier]),
            }
        return result
    globals_index = ref_index("global", global_functions)
    vtables_index = ref_index("vtable", vtable_functions)
    services_index = ref_index("service", service_functions)
    abi = defaultdict(lambda: {"count": 0, "functions": [], "sources": []})
    for va, record in records.items():
        convention = record.get("abi", {}).get("calling_convention")
        if convention is None and isinstance(record.get("body_status"), str):
            status_text = record["body_status"].lower()
            if "thiscall" in status_text:
                convention = "thiscall"
        if not convention:
            continue
        entry = abi[str(convention)]
        entry["count"] += 1
        entry["functions"].append(va)
        entry["sources"].extend(record["source"]["metadata"])
    for entry in abi.values():
        entry["functions"] = sorted(entry["functions"])
        entry["sources"] = sorted_unique(entry["sources"])
    package_functions = defaultdict(list)
    for va, record in records.items():
        if record.get("package"):
            package_functions[record["package"]].append(va)
    packages = {}
    for package_id in sorted(set(manifest_packages) | set(package_functions)):
        source = manifest_packages.get(package_id, {})
        vas = package_functions.get(package_id, [])
        package_records = [records[va] for va in vas]
        packages[package_id] = {
            "id": package_id,
            "status": source.get("status", "triage_only"),
            "source_owner": source.get("source_owner"),
            "readiness": source.get("readiness"),
            "function_count": len(vas),
            "reconstructed_count": sum(item["reconstructed"] for item in package_records),
            "blocked_count": sum(item["blocked"] for item in package_records),
            "runtime_gated_count": sum(item["runtime_gated"] for item in package_records),
            "functions": vas,
            "canonical_files": sorted_unique(
                path for item in package_records for path in item["source"]["files"]),
        }
    frontier = []
    for va in sorted(triage_by_va, key=lambda item: (
            triage_by_va[item].get("rank", 999999), item)):
        record = records[va]
        if record["status"] in ("reconstructed", "blocked"):
            continue
        row = triage_by_va[va]
        frontier.append({
            "va": va,
            "symbol": record.get("normalized_symbol"),
            "package": record.get("package"),
            "subsystem": record.get("subsystem"),
            "cluster": row.get("cluster"),
            "priority": row.get("priority"),
            "queue_state": row.get("queue_state"),
            "rank": row.get("rank"),
            "evidence": row.get("evidence"),
            "dependencies": bounded(row.get("dependencies", [])),
            "decomp_path": row.get("decomp_path"),
            "fan_in": record["dependencies"]["fan_in"],
            "fan_out": record["dependencies"]["fan_out"],
            "scc": record["dependencies"].get("scc"),
            "nearby_reconstructed": record["dependencies"]["nearby_reconstructed"],
            "inspect": sorted_unique(
                ([row["decomp_path"]] if row.get("decomp_path") else []) +
                record["source"]["metadata"] + record["source"]["files"])[:12],
            "claimability": record["ownership"]["claimability"],
        })
    dependency_signals = {
        "high_fan_in": [
            {"va": va, "fan_in": records[va]["dependencies"]["fan_in"]}
            for va in sorted(target_vas,
                             key=lambda item: (-records[item]["dependencies"]["fan_in"], item))[:20]
        ],
        "high_fan_out": [
            {"va": va, "fan_out": records[va]["dependencies"]["fan_out"]}
            for va in sorted(target_vas,
                             key=lambda item: (-records[item]["dependencies"]["fan_out"], item))[:20]
        ],
        "strongly_connected_components": sorted(
            (item for item in scc.values() if item["size"] > 1),
            key=lambda item: (-item["size"], item["id"]))[:50],
    }
    conflict_summaries = extract_conflicts(root, semantic_contradictions)
    source_paths = {
        MANIFEST_REL: relative(manifest_path, root),
        QUEUE_REL: relative(queue_path, root),
        XREF_REL: XREF_REL,
        XREF_SUMMARY_REL: XREF_SUMMARY_REL,
        SEMANTIC_REL: SEMANTIC_REL,
    }
    source_hashes = {}
    for path in (manifest_path, queue_path, root / XREF_REL, root / SEMANTIC_REL):
        source_hashes[relative(path, root)] = hashlib.sha256(path.read_bytes()).hexdigest()
    metadata_paths = sorted(metadata)
    index = {
        "$schema": "openspore-reconstruction-knowledge-index-1",
        "artifact": "reconstruction/knowledge/index.json",
        "source_of_truth": {
            "manifest": MANIFEST_REL,
            "manifest_sha256": source_hashes[MANIFEST_REL],
            "triage_queue": QUEUE_REL,
            "xref_export": XREF_REL,
            "semantic_decomp": SEMANTIC_REL,
            "conflict_ledgers": CONFLICT_DIR_REL,
            "metadata_root": METADATA_DIR_REL,
            "handoff_root": HANDOFF_DIR_REL,
        },
        "binary": manifest.get("binary", {}),
        "codegraph": {
            "available": (root / ".codegraph").is_dir(),
            "index": ".codegraph",
            "explore_command": "codegraph explore \"<symbol or file>\"",
        },
        "counts": {
            "manifest_records": len(manifest.get("functions", [])),
            "manifest_functions": len(manifest_functions),
            "triage_targets": len(triage_by_va),
            "indexed_records": len(records),
            "reconstructed_records": len(known_reconstructed),
            "blocked_records": sum(record["blocked"] for record in records.values()),
            "runtime_gated_records": sum(record["runtime_gated"] for record in records.values()),
            "metadata_records": len(metadata_paths),
            "semantic_records": len(semantic),
            "frontier_records": len(frontier),
            "types": len(types_index),
            "globals": len(globals_index),
            "vtables": len(vtables_index),
            "services": len(services_index),
            "contradictions": len(conflict_summaries),
        },
        "input_hashes": source_hashes,
        "records": records,
        "packages": packages,
        "types": types_index,
        "globals": globals_index,
        "vtables": vtables_index,
        "services": services_index,
        "abi_conventions": dict(sorted(abi.items())),
        "frontier": frontier,
        "dependency_signals": dependency_signals,
        "semantic_families": semantic_families,
        "contradictions": conflict_summaries,
    }
    bootstrap = {
        "$schema": "openspore-reconstruction-bootstrap-1",
        "artifact": "reconstruction/knowledge/bootstrap.json",
        "source_of_truth": index["source_of_truth"],
        "binary": index["binary"],
        "codegraph": index["codegraph"],
        "counts": index["counts"],
        "current_frontier": frontier[:20],
        "known_abi": [
            {"convention": key, "count": value["count"],
             "examples": value["functions"][:8]}
            for key, value in sorted(index["abi_conventions"].items())
        ],
        "known_types": [
            {"name": name, "package": value.get("package"),
             "functions": value.get("functions", [])[:8]}
            for name, value in sorted(types_index.items())
            if value.get("functions")
        ][:30],
        "known_globals": [
            {"id": key, "count": value["count"],
             "functions": value["functions"][:8]}
            for key, value in sorted(globals_index.items())
        ][:20],
        "known_vtables": [
            {"id": key, "count": value["count"],
             "functions": value["functions"][:8]}
            for key, value in sorted(vtables_index.items())
        ][:20],
        "next_query": "python3 -m tools.reconstruction_knowledge function --va VA",
    }
    return index, bootstrap


def write_json_atomic(path, document):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = json.dumps(document, indent=2, sort_keys=True,
                         ensure_ascii=False) + "\n"
    descriptor, temporary = tempfile.mkstemp(prefix=path.name + ".",
                                              dir=str(path.parent))
    try:
        with os.fdopen(descriptor, "w", encoding="utf-8") as handle:
            handle.write(payload)
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temporary, path)
        os.chmod(path, 0o644)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def load_index(path=DEFAULT_INDEX):
    try:
        return load_json(Path(path))
    except (OSError, ValueError) as exc:
        raise ValueError("cannot load reconstruction index %s: %s" % (path, exc))


def record_summary(record):
    keys = ("va", "normalized_symbol", "package", "subsystem", "status",
            "reconstructed", "blocked", "runtime_gated", "confidence",
            "evidence_level")
    return {key: record.get(key) for key in keys}


def function_context(index, va, limit=8):
    record = index.get("records", {}).get(normalize_va(va))
    if record is None:
        return {"status": "error", "code": "not_found",
                "message": "VA is not present in the generated index"}
    limit = max(1, min(int(limit), 25))
    analogues = record.get("analogues", [])[:limit]
    direct = []
    for item in record.get("dependencies", {}).get("callers", []) + \
            record.get("dependencies", {}).get("callees", []):
        if item.get("va") not in direct:
            direct.append(item)
    findings = []
    for finding in index.get("contradictions", []):
        if record["va"] in finding.get("anchors", []) or \
                finding.get("va") == record["va"]:
            findings.append(finding)
    return {
        "status": "ok",
        "source_of_truth": index.get("source_of_truth"),
        "binary": index.get("binary"),
        "function": record,
        "analogues": analogues,
        "related_functions": direct[:limit * 2],
        "contradictions": findings,
    }


def related_functions(index, va, limit=12):
    record = index.get("records", {}).get(normalize_va(va))
    if record is None:
        return {"status": "error", "code": "not_found",
                "message": "VA is not present in the generated index"}
    limit = max(1, min(int(limit), 50))
    result = []
    for analogue in record.get("analogues", []):
        candidate = index["records"].get(analogue["va"])
        if candidate:
            item = record_summary(candidate)
            item["match_basis"] = analogue["match_basis"]
            item["score"] = analogue["score"]
            result.append(item)
    return {"status": "ok", "va": record["va"], "functions": result,
            "count": len(result), "limit": limit}


def type_context(index, name, limit=25):
    if not isinstance(name, str) or not name:
        raise ValueError("type name is required")
    matches = [(key, value) for key, value in index.get("types", {}).items()
               if key.casefold() == name.casefold()]
    if not matches:
        return {"status": "error", "code": "not_found",
                "message": "type is not present in the generated index"}
    type_name, value = matches[0]
    functions = []
    for va in value.get("functions", [])[:max(1, min(int(limit), 100))]:
        if va in index["records"]:
            functions.append(record_summary(index["records"][va]))
    return {"status": "ok", "type": value, "functions": functions,
            "count": len(functions)}


def package_context(index, package, limit=50):
    if not isinstance(package, str) or not package:
        raise ValueError("package is required")
    matches = [(key, value) for key, value in index.get("packages", {}).items()
               if key.casefold() == package.casefold()]
    if not matches:
        return {"status": "error", "code": "not_found",
                "message": "package is not present in the generated index"}
    package_id, value = matches[0]
    functions = [record_summary(index["records"][va])
                 for va in value.get("functions", [])[:max(1, min(int(limit), 200))]
                 if va in index["records"]]
    return {"status": "ok", "package": value, "functions": functions,
            "count": len(functions)}


def frontier_context(index, package=None, subsystem=None, status=None, limit=20):
    rows = index.get("frontier", [])
    if package:
        rows = [row for row in rows if str(row.get("package", "")).casefold() ==
                package.casefold()]
    if subsystem:
        rows = [row for row in rows if str(row.get("subsystem", "")).casefold() ==
                subsystem.casefold()]
    if status:
        rows = [row for row in rows if row.get("queue_state") == status]
    effective = max(1, min(int(limit), 100))
    return {"status": "ok", "count": len(rows), "truncated": len(rows) > effective,
            "frontier": rows[:effective], "total": len(rows),
            "source_of_truth": index.get("source_of_truth")}


def reconstruction_status(index, va):
    record = index.get("records", {}).get(normalize_va(va))
    if record is None:
        return {"status": "error", "code": "not_found",
                "message": "VA is not present in the generated index"}
    return {
        "status": "ok",
        "function": record_summary(record),
        "package": record.get("package"),
        "source_file": (record.get("source") or {}).get("file"),
        "confidence": record.get("confidence"),
        "blocking_reason": (record.get("runtime") or {}).get("blocking_reason"),
        "runtime_gates": (record.get("runtime") or {}).get("gates", []),
        "ownership": record.get("ownership"),
    }


def parse_args(argv):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    subparsers = parser.add_subparsers(dest="command", required=True)
    build = subparsers.add_parser("build")
    build.add_argument("--index", type=Path, default=DEFAULT_INDEX)
    build.add_argument("--bootstrap", type=Path, default=DEFAULT_BOOTSTRAP)
    function = subparsers.add_parser("function")
    function.add_argument("--va", required=True)
    function.add_argument("--limit", type=int, default=8)
    related = subparsers.add_parser("related")
    related.add_argument("--va", required=True)
    related.add_argument("--limit", type=int, default=12)
    type_parser = subparsers.add_parser("type")
    type_parser.add_argument("name")
    type_parser.add_argument("--limit", type=int, default=25)
    package = subparsers.add_parser("package")
    package.add_argument("name")
    package.add_argument("--limit", type=int, default=50)
    frontier = subparsers.add_parser("frontier")
    frontier.add_argument("--package")
    frontier.add_argument("--subsystem")
    frontier.add_argument("--status")
    frontier.add_argument("--limit", type=int, default=20)
    status = subparsers.add_parser("status")
    status.add_argument("--va", required=True)
    for command in (function, related, type_parser, package, frontier, status):
        command.add_argument("--index", type=Path, default=DEFAULT_INDEX)
    return parser.parse_args(argv)


def main(argv=None):
    args = parse_args(argv)
    if args.command == "build":
        index, bootstrap = build_index(args.root)
        write_json_atomic(args.index, index)
        write_json_atomic(args.bootstrap, bootstrap)
        print(json.dumps({"status": "ok", "index": str(args.index),
                          "bootstrap": str(args.bootstrap),
                          "counts": index["counts"]}, sort_keys=True))
        return 0
    index = load_index(args.index)
    if args.command == "function":
        result = function_context(index, args.va, args.limit)
    elif args.command == "related":
        result = related_functions(index, args.va, args.limit)
    elif args.command == "type":
        result = type_context(index, args.name, args.limit)
    elif args.command == "package":
        result = package_context(index, args.name, args.limit)
    elif args.command == "frontier":
        result = frontier_context(index, args.package, args.subsystem,
                                  args.status, args.limit)
    else:
        result = reconstruction_status(index, args.va)
    print(json.dumps(result, sort_keys=True, ensure_ascii=False))
    return 0 if result.get("status") == "ok" else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError) as exc:
        print(json.dumps({"status": "error", "code": "invalid_request",
                          "message": str(exc)}, sort_keys=True))
        sys.exit(2)
