#!/usr/bin/env python3
"""Canonical deterministic knowledge-graph seed generator.

Replaces the hand-written ``seed_sprint.py`` literals (SCALABILITY row #5,
docs/RE-AUTOMATION-ARCHITECTURE.md §5). Emits the whole seed as SQL through
the same upsert code path as ``kg.py`` (one connection, one transaction),
sourced ONLY from committed inputs so it runs in a bare fresh clone:

  1. knowledgegraph/seed-literals.json   -- today's 96/115/14, verbatim
  2. docs/replacement-status.json         -- 18 subsystems + attrs.gate
  3. --sdk-xml (external; graceful skip)  -- 1,670 fun:<va> + investigations
  4. docs/analysis/dossiers/*.json        -- dossier + function nodes
  5. docs/analysis/vtables.json           -- 306 cls + 12 inheritsFrom chains
  6. docs/REPLACEMENT-ABI.md             -- struct + field rows
  7. committed observatory trace manifests -- obs nodes + trace_run rows

Invariants (pinned by test):
  * byte-deterministic: sorted emit, canonicalized attrs_json
  * idempotent: re-running under the same identity is a no-op
  * reproduces 96/115/14 from seed-literals.json alone
  * every evidence_level derived through §3 (scale.py) -- no hand-typed
    confidence
  * all 9 replacement statuses map without KeyError
  * stale-state: rows seeded under a DIFFERENT binary_sha256 survive a
    re-seed (investigations INSERT OR IGNORE keeps the old-identity row)
"""
import argparse
import glob
import hashlib
import json
import os
import re
import sqlite3
import sys

import scale

HERE = os.path.dirname(os.path.abspath(__file__))
DEFAULT_DB = os.path.join(HERE, "spore.db")

# §2/§3 stage + lifecycle vocabulary.
_LIFECYCLE = ("queued", "active", "blocked", "done", "dropped")
_QUEUED_STATUSES = {"unknown", "hypothesis", "inferred", "supported",
                    "approximated", "replaced-stub", "replaced-approx"}
_DONE_STATUSES = {"replaced-verified"}


def _canonical_json(obj):
    return json.dumps(obj, sort_keys=True, separators=(",", ":"),
                      ensure_ascii=False)


def _nearest_level(conf):
    """Map a legacy REAL confidence to the nearest §3 EV level.

    EV is level->confidence (display only). Reverse it for persisted legacy
    confidence values; exact ties break toward the weaker level. Deterministic.
    """
    best, best_d = None, None
    for lvl, cc in scale.EV.items():
        d = abs(conf - cc)
        if best_d is None or d < best_d or (
                d == best_d and scale.EV_ORDER.index(lvl)
                < scale.EV_ORDER.index(best)):
            best, best_d = lvl, d
    return best


def _level_from_status(status):
    return scale.evidence_for_status(status)  # raises ValueError, never KeyError


def _norm_va(va):
    if va is None:
        return None
    va = va.lower().replace("0x", "")
    return va.zfill(8)[-8:]


def _is_external_missing(path):
    return path is None or not os.path.exists(path)


# --------------------------------------------------------------------------- #
# Canonical record accumulators.
# --------------------------------------------------------------------------- #
class Seed:
    def __init__(self, sha):
        self.sha = sha  # None => build-agnostic (NULL in nullable cols, §5)
        self.identity = sha if sha is not None else "build-agnostic"
        self.nodes = {}     # (label, name) -> record dict
        self.edges = {}     # (src_label, src_name, dst_label, dst_name, rel) -> True
        self.tests = {}     # name -> record dict
        self.investigations = {}  # id -> record dict
        self.fields = {}    # (struct_label, struct_name, offset) -> record dict
        self.trace_runs = {} # jsonl_path -> record dict

    # -- nodes ------------------------------------------------------------ #
    def upsert_node(self, label, name, attrs=None, confidence=None,
                    origin=None, note=None, evidence=None):
        key = (label, name)
        if key not in self.nodes:
            ev = evidence or "UNKNOWN"
            if confidence is None:
                confidence = scale.EV.get(ev, 0.0)
            self.nodes[key] = {
                "label": label, "name": name,
                "attrs": dict(attrs or {}),
                "confidence": float(confidence),
                "origin": origin or "unknown",
                "note": note,
                "evidence_level": ev,
            }
        else:
            rec = self.nodes[key]
            for k, v in (attrs or {}).items():
                rec["attrs"].setdefault(k, v)  # verbatim/first source wins
            if evidence:
                rec["evidence_level"] = evidence

    def add_edge(self, src_label, src_name, dst_label, dst_name, rel):
        self.edges[(src_label, src_name, dst_label, dst_name, rel)] = True

    def add_test(self, name, stage=None, seed=None, expected=None,
                 actual=None, passed=None):
        if name not in self.tests:
            self.tests[name] = {"name": name, "stage": stage, "seed": seed,
                                "expected": expected, "actual": actual,
                                "pass": passed}

    def add_investigation(self, id_, kind, *, va=None, name=None,
                          subsystem=None, mode="replace", why="",
                          stage="QUEUED", status="queued", block_reason=None,
                          prerequisites=None, evidence_refs=None):
        if id_ in self.investigations:
            return
        self.investigations[id_] = {
            "id": id_, "kind": kind, "va": va, "name": name,
            "subsystem": subsystem, "mode": mode, "why_interesting": why,
            "stage": stage, "status": status, "block_reason": block_reason,
            "prerequisites": _canonical_json(prerequisites) if prerequisites else None,
            "attempts": None, "checkpoint": None,
            "evidence_refs": _canonical_json(evidence_refs) if evidence_refs else None,
            "implementer_id": None, "adjudicator_id": None,
            "binary_sha256": self.identity,
        }

    def add_field(self, struct_label, struct_name, offset, role, *,
                  offset_evidence=None, meaning_evidence=None, value=None,
                  source=None):
        key = (struct_label, struct_name, offset)
        if key in self.fields:
            return
        ev = offset_evidence or "UNKNOWN"
        self.fields[key] = {
            "struct_label": struct_label, "struct_name": struct_name,
            "offset": offset, "role": role,
            "offset_evidence": ev,
            "meaning_evidence": meaning_evidence or ev,
            "value": value, "source": source,
        }

    def add_trace_run(self, jsonl_path, *, events_total=None, probes_sha256=None,
                      wine_version=None, display_env=None, outcome=None):
        if jsonl_path not in self.trace_runs:
            self.trace_runs[jsonl_path] = {
                "binary_sha256": self.identity,
                "probes_sha256": probes_sha256,
                "wine_version": wine_version, "display_env": display_env,
                "events_total": events_total, "jsonl_path": jsonl_path,
                "outcome": outcome,
            }


# --------------------------------------------------------------------------- #
# Input 1: seed-literals.json (the verbatim baseline).
# --------------------------------------------------------------------------- #
def load_literals(seed, path):
    if _is_external_missing(path):
        print(f"seed: skip (missing): {path}", file=sys.stderr)
        return 0
    with open(path) as f:
        data = json.load(f)
    for n in data.get("nodes", []):
        seed.upsert_node(
            n["label"], n["name"],
            attrs=n.get("attrs") or {},
            confidence=n.get("confidence"),
            origin=n.get("origin"),
            note=n.get("note"),
            evidence=_nearest_level(n.get("confidence", 0.0)),
        )
    for e in data.get("edges", []):
        seed.add_edge(e["src_label"], e["src_name"], e["dst_label"],
                      e["dst_name"], e["rel"])
    for t in data.get("test_rows", []):
        seed.add_test(t["name"], stage=t.get("stage"), seed=t.get("seed"),
                      expected=t.get("expected"), actual=t.get("actual"),
                      passed=t.get("pass"))
    return len(data.get("nodes", []))


# --------------------------------------------------------------------------- #
# Input 2: replacement-status.json (18 subsystems + investigations + gate).
# --------------------------------------------------------------------------- #
def load_replacement_status(seed, path):
    if _is_external_missing(path):
        print(f"seed: skip (missing): {path}", file=sys.stderr)
        return 0
    with open(path) as f:
        data = json.load(f)
    count = 0
    for s in data.get("subsystems", []):
        name = s["name"]
        status = s["status"]
        ev = _level_from_status(status)
        attrs = {"status": status}
        if s.get("gate"):
            attrs["gate"] = s["gate"]
        if s.get("openspore_impl"):
            attrs["openspore_impl"] = s["openspore_impl"]
        if s.get("boundary"):
            attrs["boundary"] = s["boundary"]
        if s.get("evidence"):
            attrs["evidence_refs"] = s["evidence"]

        seed.upsert_node(
            "Subsystem", f"sub:{name}", attrs=attrs, origin="manual",
            evidence=ev)

        if status in _DONE_STATUSES:
            inv_status, inv_stage = "done", "RECORDED"
        elif status in _QUEUED_STATUSES:
            inv_status, inv_stage = "queued", "QUEUED"
        else:
            inv_status, inv_stage = "queued", "QUEUED"
        seed.add_investigation(
            f"sub:{name}", "subsystem", subsystem=name,
            why=f"replacement-status: {status}", stage=inv_stage,
            status=inv_status, evidence_refs=s.get("evidence"))
        count += 1
    return count


# --------------------------------------------------------------------------- #
# Input 3: SDK XML import (external; graceful skip when absent).
# --------------------------------------------------------------------------- #
def load_sdk(seed, path):
    if _is_external_missing(path):
        print(f"seed: skip (external, absent): {path}", file=sys.stderr)
        return 0
    try:
        import xml.etree.ElementTree as ET
        tree = ET.parse(path)
    except Exception as exc:  # noqa: BLE001 - graceful skip by design
        print(f"seed: skip (unreadable) {path}: {exc}", file=sys.stderr)
        return 0
    count = 0
    for fn in tree.iter("FUNCTION"):
        name = fn.get("NAME")
        addr = fn.get("ADDRESS")
        if not name or not addr:
            continue
        va = _norm_va(addr)
        if not va:
            continue
        seed.upsert_node("Function", f"fun:{va}",
                         attrs={"sdk_name": name, "address": addr},
                         origin="sdk", evidence="CONFIRMED")
        seed.add_investigation(
            f"fun:{va}:{name}", "function", va=va, name=name, mode="replace",
            why="SDK import", stage="QUEUED", status="queued")
        count += 1
    return count


# --------------------------------------------------------------------------- #
# Input 4: dossier JSONs.
# --------------------------------------------------------------------------- #
def load_dossiers(seed, pattern):
    files = sorted(glob.glob(pattern))
    if not files:
        print(f"seed: skip (no dossiers): {pattern}", file=sys.stderr)
        return 0
    total = 0
    for path in files:
        try:
            with open(path) as f:
                d = json.load(f)
        except Exception as exc:  # noqa: BLE001
            print(f"seed: skip (unreadable) {path}: {exc}", file=sys.stderr)
            continue
        topic = d.get("topic") or os.path.splitext(os.path.basename(path))[0]
        seed.upsert_node("Dossier", f"dossier:{topic}",
                         attrs={"schema": d.get("$schema"),
                                "sources": d.get("sources")},
                         origin="manual", evidence="SUPPORTED")
        for fn in d.get("functions", []):
            va = _norm_va(fn.get("address") or fn.get("rva"))
            if not va:
                continue
            ev = _first_ev_token(fn.get("evidence_level"))
            attrs = {"sdk_name": fn.get("name"), "rva": fn.get("rva"),
                     "address": fn.get("address")}
            if fn.get("signature"):
                attrs["signature"] = fn["signature"]
            if fn.get("dispatch"):
                attrs["dispatch"] = fn["dispatch"]
            seed.upsert_node("Function", f"fun:{va}", attrs=attrs,
                             origin="static", evidence=ev)
            seed.add_edge("Dossier", f"dossier:{topic}", "Function",
                          f"fun:{va}", "documents")
            total += 1
            # The one completed case (cell-movement) seeds done/RECORDED.
            if "MovePlayerToMousePosition" in (fn.get("name") or ""):
                seed.add_investigation(
                    f"fun:{va}:{fn['name']}", "function", va=va,
                    name=fn.get("name"), subsystem=topic, mode="replace",
                    why=f"dossier {topic}: replacement target",
                    stage="RECORDED", status="done",
                    evidence_refs=d.get("sources"))
    return total


def _first_ev_token(prose):
    """Extract the first valid 7-level token from a prose evidence string."""
    if not prose:
        return "INFERRED"
    for tok in str(prose).split():
        u = tok.strip("()[]{};,.`").upper()
        if u in scale.EV_ORDER:
            return u
    return "INFERRED"


# --------------------------------------------------------------------------- #
# Input 5: vtables.json (306 cls + 12 inheritance chains only).
# --------------------------------------------------------------------------- #
def load_vtables(seed, path):
    if _is_external_missing(path):
        print(f"seed: skip (missing): {path}", file=sys.stderr)
        return 0
    with open(path) as f:
        vt = json.load(f)
    count = 0
    for assoc in vt.get("sdk_associations", []):
        addr = assoc.get("address")
        va = _norm_va(addr)
        if not va:
            continue
        subs = assoc.get("subsystems") or []
        funcs = assoc.get("sdkFuncs") or []
        # A representative SDK class name is metadata, NEVER the node id.
        sdk_name = None
        for f in funcs:
            if "::" in f:
                sdk_name = "::".join(f.split("::")[:2])
                break
        attrs = {"vtable_address": addr, "slots": assoc.get("slots"),
                 "subsystems": subs}
        if sdk_name:
            attrs["sdk_name"] = sdk_name
        seed.upsert_node("Class", f"cls:{va}", attrs=attrs, origin="static",
                         evidence=_level_from_status("inferred"))
        count += 1
    chains = 0
    for ch in vt.get("inheritance_chains", []):
        base = _norm_va(ch.get("base"))
        derived = _norm_va(ch.get("derived"))
        if not base or not derived:
            continue
        # Ensure endpoints exist even if not in the 306 association set.
        seed.upsert_node("Class", f"cls:{base}",
                         attrs={"vtable_address": ch.get("base"),
                                "chain_role": "base"},
                         origin="static", evidence=_level_from_status("inferred"))
        seed.upsert_node("Class", f"cls:{derived}",
                         attrs={"vtable_address": ch.get("derived"),
                                "chain_role": "derived"},
                         origin="static", evidence=_level_from_status("inferred"))
        seed.add_edge("Class", f"cls:{derived}", "Class", f"cls:{base}",
                      "inheritsFrom")
        chains += 1
    return count, chains


# --------------------------------------------------------------------------- #
# Input 6: REPLACEMENT-ABI.md field tables -> struct + field rows.
# --------------------------------------------------------------------------- #
_ABI_EV = {"UNKNOWN", "APPROXIMATION", "INFERRED", "SUPPORTED", "OBSERVED",
           "CONFIRMED", "VERIFIED"}


def _parse_md_field_tables(text):
    """Yield (section, offset, role, evidence) from markdown field tables."""
    rows = []
    current_struct = None
    for line in text.splitlines():
        low = line.lower()
        if "sCellGame" in line and ("global" in low or "##" in line):
            current_struct = "Simulator::Cell::sCellGame"
        if line.strip().startswith("## 3.") or "player entity layout" in low:
            current_struct = "PlayerEntity"
        if not line.strip().startswith("|"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 3:
            continue
        if cells[0] in ("field", "offset (from sCellGame)",
                        "offset (from player)", "---") \
                or set(cells[0]) <= {"-"}:
            continue
        raw_off = cells[0].replace("`", "")
        offsets = re.findall(r"0[xX][0-9a-fA-F]+", raw_off)
        if not offsets:
            offsets = ["0x" + b for b in re.findall(
                r"(?<![0-9a-fA-Fx])\b[0-9a-fA-F]{2,}\b", raw_off)]
        if not offsets:
            continue
        role = cells[1].replace("`", "")
        ev = cells[2].split("(")[0].strip().strip("`").upper()
        if ev not in _ABI_EV:
            ev = "INFERRED"
        for off in offsets:
            rows.append((current_struct, off.lower(), role, ev))
    return rows


def load_abi(seed, path):
    if _is_external_missing(path):
        print(f"seed: skip (missing): {path}", file=sys.stderr)
        return 0, 0
    with open(path) as f:
        text = f.read()
    rows = _parse_md_field_tables(text)
    structs = {}
    for struct, offset, role, ev in rows:
        if not struct:
            continue
        structs.setdefault(struct, "SUPPORTED")
        seed.upsert_node("Structure", f"struct:{struct}", origin="static",
                         evidence=structs[struct])
        seed.add_field("Structure", f"struct:{struct}", offset, role,
                       offset_evidence=ev, meaning_evidence=ev,
                       source="docs/REPLACEMENT-ABI.md")
    return len(rows), len(structs)


# --------------------------------------------------------------------------- #
# Input 7: committed observatory trace manifests.
# --------------------------------------------------------------------------- #
def load_traces(seed, pattern):
    files = sorted(glob.glob(pattern))
    if not files:
        print(f"seed: skip (no committed traces): {pattern}", file=sys.stderr)
        return 0
    total = 0
    for path in files:
        base = os.path.basename(path)
        stem = re.sub(r"\.jsonl$", "", base)
        stem = re.sub(r"_example$", "", stem)
        trace = stem
        with open(path) as f:
            lines = [ln for ln in f if ln.strip()]
        events_total = len(lines)
        probes_sha = hashlib.sha256(
            "\n".join(lines).encode("utf-8")).hexdigest()
        seed.upsert_node("Observation", f"obs:{trace}:committed",
                         attrs={"manifest": base, "events_total": events_total},
                         origin="dynamic", evidence="OBSERVED")
        seed.add_trace_run(base, events_total=events_total,
                           probes_sha256=probes_sha)
        total += 1
    return total


# --------------------------------------------------------------------------- #
# Emit.
# --------------------------------------------------------------------------- #
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


def _emit(seed, db_path, dry_run):
    nodes = sorted(seed.nodes.values(), key=lambda r: (r["label"], r["name"]))
    edges = sorted(seed.edges.keys())
    tests = sorted(seed.tests.values(), key=lambda r: r["name"])
    invs = sorted(seed.investigations.values(), key=lambda r: r["id"])
    fields = sorted(seed.fields.values(),
                    key=lambda r: (r["struct_name"], r["offset"]))

    if dry_run:
        print("seed: --dry-run (no writes)")
        print(f"  db            : {db_path}")
        print(f"  binary_sha256 : {seed.sha}")
        print(f"  nodes         : {len(nodes)}")
        print(f"  edges         : {len(edges)}")
        print(f"  tests         : {len(tests)}")
        print(f"  investigations: {len(invs)}")
        print(f"  fields        : {len(fields)}")
        print(f"  trace_runs    : {len(seed.trace_runs)}")
        return

    c = sqlite3.connect(db_path)
    c.row_factory = sqlite3.Row
    import kg
    kg._migrate(c)
    try:
        c.executescript(open(os.path.join(HERE, "schema.sql")).read())
    except Exception:
        pass
    with c:
        for r in nodes:
            c.execute(
                _NODE_UPSERT,
                (r["label"], r["name"], _canonical_json(r["attrs"]),
                 r["confidence"], r["origin"], r["note"],
                 r["evidence_level"], seed.sha))
        idmap = {}
        for r in nodes:
            row = c.execute(
                "SELECT id FROM node WHERE label=? AND name=?",
                (r["label"], r["name"])).fetchone()
            idmap[(r["label"], r["name"])] = row["id"]
        for sl, sn, dl, dn, rel in edges:
            s, d = idmap.get((sl, sn)), idmap.get((dl, dn))
            if s is None or d is None:
                continue
            c.execute("INSERT OR IGNORE INTO edge(src,dst,rel) VALUES(?,?,?)",
                      (s, d, rel))
        for t in tests:
            c.execute("DELETE FROM test_result WHERE name=?", (t["name"],))
            c.execute(
                "INSERT INTO test_result(name,stage,seed,expected,actual,pass)"
                " VALUES(?,?,?,?,?,?)",
                (t["name"], t["stage"], t["seed"], t["expected"],
                 t["actual"], t["pass"]))
        for iv in invs:
            c.execute(
                """INSERT OR IGNORE INTO investigations
                   (id,kind,va,name,subsystem,mode,why_interesting,stage,status,
                    block_reason,prerequisites,attempts,checkpoint,evidence_refs,
                    implementer_id,adjudicator_id,binary_sha256)
                   VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)""",
                (iv["id"], iv["kind"], iv["va"], iv["name"], iv["subsystem"],
                 iv["mode"], iv["why_interesting"], iv["stage"], iv["status"],
                 iv["block_reason"], iv["prerequisites"], iv["attempts"],
                 iv["checkpoint"], iv["evidence_refs"], iv["implementer_id"],
                 iv["adjudicator_id"], iv["binary_sha256"]))
        for fl in fields:
            sid = idmap.get((fl["struct_label"], fl["struct_name"]))
            if sid is None:
                continue
            c.execute(
                """INSERT INTO field(struct_id,offset,role,offset_evidence,
                   meaning_evidence,value,source,binary_sha256)
                   VALUES(?,?,?,?,?,?,?,?)
                   ON CONFLICT(struct_id,offset) DO UPDATE SET
                     role=excluded.role,
                     offset_evidence=excluded.offset_evidence,
                     meaning_evidence=excluded.meaning_evidence,
                     value=excluded.value,
                     source=excluded.source,
                     binary_sha256=excluded.binary_sha256,
                     updated_at=datetime('now')""",
                (sid, fl["offset"], fl["role"], fl["offset_evidence"],
                 fl["meaning_evidence"], fl["value"], fl["source"], seed.sha))
        for tr in seed.trace_runs.values():
            # Idempotent re-seed: a committed manifest under the SAME identity
            # is the same run; a DIFFERENT identity keeps its own row.
            c.execute(
                "DELETE FROM trace_run WHERE jsonl_path=? AND binary_sha256=?",
                (tr["jsonl_path"], tr["binary_sha256"]))
            c.execute(
                """INSERT INTO trace_run
                   (binary_sha256,probes_sha256,wine_version,display_env,
                    events_total,jsonl_path,outcome)
                   VALUES(?,?,?,?,?,?,?)""",
                (tr["binary_sha256"], tr["probes_sha256"],
                 tr["wine_version"], tr["display_env"], tr["events_total"],
                 tr["jsonl_path"], tr["outcome"]))
    c.close()
    print(f"seed: wrote {len(nodes)} nodes, {len(edges)} edges, "
          f"{len(tests)} tests, {len(invs)} investigations, "
          f"{len(fields)} fields -> {db_path}")


# --------------------------------------------------------------------------- #
# CLI.
# --------------------------------------------------------------------------- #
def _resolve_sha(args):
    if args.binary_sha256:
        return args.binary_sha256
    if args.build_agnostic:
        return None
    exe = os.path.join(args.inputs, "SPORE", "SporeBin", "SporeApp.exe")
    if os.path.exists(exe):
        h = hashlib.sha256()
        with open(exe, "rb") as f:
            for chunk in iter(lambda: f.read(1 << 20), b""):
                h.update(chunk)
        return h.hexdigest()
    # Build-agnostic: no pinned binary. NULL in node/field (§5 spec: NULL =
    # build-agnostic); the sentinel "build-agnostic" covers the NOT NULL
    # investigations/trace_run columns only.
    return None


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--db", default=DEFAULT_DB, help="target sqlite db")
    p.add_argument("--binary-sha256", help="build identity (hex sha256)")
    p.add_argument("--source-identity",
                   help="provenance label (carried into dry-run report)")
    p.add_argument("--build-agnostic", action="store_true",
                   help="do not tie the seed to a specific binary")
    p.add_argument("--sdk-xml",
                   default=os.path.expanduser(
                       "~/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml"))
    p.add_argument("--traces",
                   default=os.path.join(HERE, "..", "tools", "observatory",
                                        "examples"))
    p.add_argument("--inputs", default=os.path.join(HERE, ".."),
                   help="base dir for committed inputs (default: repo root)")
    p.add_argument("--dry-run", action="store_true",
                   help="report counts + manifest, write nothing")
    args = p.parse_args(argv)

    root = os.path.abspath(args.inputs)
    sha = _resolve_sha(args)
    seed = Seed(sha)

    # Fixed source priority: verbatim baseline first, then enrichment.
    load_literals(seed, os.path.join(root, "knowledgegraph",
                                     "seed-literals.json"))
    load_replacement_status(seed, os.path.join(root, "docs",
                                               "replacement-status.json"))
    load_sdk(seed, args.sdk_xml)
    load_dossiers(seed, os.path.join(root, "docs", "analysis", "dossiers",
                                     "*.json"))
    load_vtables(seed, os.path.join(root, "docs", "analysis", "vtables.json"))
    load_abi(seed, os.path.join(root, "docs", "REPLACEMENT-ABI.md"))
    load_traces(seed, os.path.join(args.traces, "*.jsonl"))

    _emit(seed, args.db, args.dry_run)


if __name__ == "__main__":
    main()
