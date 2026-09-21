#!/usr/bin/env python3
"""dossier.py — generate an RE Dossier (docs/RE-DOSSIER-SCHEMA.md) from
committed evidence only (Obj 31A/31B).

Inputs (all committed; no live Ghidra server, no external deps):
  * tools/re/data/ghidra_snapshot_<topic>.json   (Ghidra function cluster)
  * docs/analysis/vtables.json                   (vtable scan, address merge)
  * knowledgegraph/spore.db                      (shared SQLite knowledge graph)
  * SPORE/Data/Spore_Content.package             (optional; DBPF index check;
    the minimal index reader below mirrors tools/spore/dbpf/dbpf.py's layout)
  * tools/observatory/out/*.jsonl                (optional; runtime traces)

Usage:
  python3 tools/re/dompiler.py <topic> [--snapshot PATH] [--out-dir DIR]

Decompiler output is EVIDENCE, NOT TRUTH (no MSVC RTTI). Missing optional
inputs degrade to explicit records — never a failure, never a fabrication
(a topic with no trace records runtime.obtained=false with a reason).
"""
import argparse
import glob
import json
import os
import sqlite3
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", ".."))
DEFAULT_OUT = os.path.join(ROOT, "docs", "analysis", "dossiers")

EVIDENCE_VOCAB = [
    "OBSERVED", "VERIFIED", "CONFIRMED", "SUPPORTED",
    "INFERRED", "APPROXIMATION", "UNKNOWN",
]

# Per-topic narrative content. Everything else is derived from the committed
# snapshot / knowledge graph / traces; keep entries evidence-labeled.
TOPIC_NOTES = {
    "cell-movement": {
        "evidence_summary": (
            "Cell-mode per-frame update is vtable-dispatched: App::cCellModeStrategy::Update "
            "(linked VA 0xe80980, vtable @ 0x1485550, no static callers) delegates to the real "
            "update body FUN_00e806b0 (linked VA 0xe806b0), which calls "
            "Simulator::Cell::MovePlayerToMousePosition "
            "(linked VA 0xe5b790). Headline finding: the player is steered by a RAY-PLANE "
            "INTERSECTION — the camera ray (from the mouse position) is intersected with the "
            "movement plane, and the hit point becomes the player's target position and "
            "orientation-to-travel. SDK names are VERIFIED via the march2017 SDK import; the "
            "ray-plane structure is OBSERVED in decompilation (evidence, not truth); the "
            "plane normal/point constant addresses are OBSERVED but their values are INFERRED "
            "(unread); runtime was NOT OBTAINED (see runtime section)."
        ),
        "hypotheses": [
            "The movement plane is a fixed plane at constant depth: normal at DAT_015a7c40/44/48, "
            "point at DAT_016b3c28/2c/30 (addresses OBSERVED; values INFERRED until read at runtime).",
            "sCellGame+0x5158 is a lock/pause flag: movement is skipped while non-zero "
            "(INFERRED from the observed `!= 0 → return` guard).",
            "sCellGame+0x5190+0xe0 is a 'moving' flag, set to 1 when the ray-plane hit succeeds "
            "(INFERRED from the observed store; meaning from decompilation context).",
            "Thrust-style keys (OnKeyDown) are secondary: the movement TARGET is set by the mouse "
            "via the camera ray, not by the keys (INFERRED from the OnKeyDown decompilation note).",
            "The player entity is fetched by index through FUN_00b721d0, the collection-getter at "
            "sCellGame+0x411c (structure OBSERVED; role INFERRED).",
        ],
        "known_unknowns": [
            "Plane normal / plane point constant VALUES — addresses OBSERVED, values unread; a "
            "runtime read is required.",
            "Semantics of the camera-mode word at +0xd4 (which camera modes allow steering).",
            "Meaning of the state word at sCellGame+0x51e0 that branches the update body.",
            "Player entity field semantics at +0x4c..+0x58 (current position) — offsets OBSERVED, "
            "semantics INFERRED.",
            "No runtime trace exists for cell mode: Xvfb is absent, headless menu navigation is "
            "impossible, and the only recorded trace (main_menu) does not reach cell mode.",
        ],
        "asset_relationships": [
            "Scene backdrop: gmdl 0x00E6BCE5 group 0x40666202 / 0x40666203, inst 0xD1B4BB56 "
            "(record presence CONFIRMED against the DBPF index; see resource_refs).",
            "Backdrop raster: 0x2F4E681C group 0x40662900, inst 0xD1B4BB56 "
            "(CONFIRMED; DXT5, near-black RGB alpha mask per docs/CELLSTAGE.md).",
            "Player/food/prey stand-in gmdl records are APPROXIMATION identities (no scene/world-"
            "object records decoded yet; docs/CELLSTAGE.md, recon section 4).",
        ],
        "resource_refs": [
            {"type": "0x00E6BCE5", "group": "0x40666202", "instance": "0x0D1B4BB56",
             "purpose": "backdrop heightfield patch A (scene table, src/apps/cell_stage.cpp)"},
            {"type": "0x00E6BCE5", "group": "0x40666203", "instance": "0x0D1B4BB56",
             "purpose": "backdrop heightfield patch B"},
            {"type": "0x2F4E681C", "group": "0x40662900", "instance": "0x0D1B4BB56",
             "purpose": "backdrop DXT5 raster"},
            {"type": "0x00E6BCE5", "group": "0x40637E02", "instance": "0x067A0801",
             "purpose": "player-cell stand-in (APPROXIMATION identity)"},
            {"type": "0x00E6BCE5", "group": "0x40637E03", "instance": "0x067CEDE8",
             "purpose": "food stand-in A (APPROXIMATION position)"},
            {"type": "0x00E6BCE5", "group": "0x40637E03", "instance": "0x067CEDEA",
             "purpose": "food stand-in B (APPROXIMATION position)"},
            {"type": "0x00E6BCE5", "group": "0x40637E03", "instance": "0x067CEDFB",
             "purpose": "prey stand-in C (APPROXIMATION position)"},
        ],
        "openspore_counterpart": {
            "files": ["src/apps/cell_stage.cpp", "src/sim/Sim.cpp (CellSim)"],
            "label": "APPROXIMATION",
            "note": ("Current movement is keyboard thrust (WASD/Shift) + exponential damping in "
                     "CellSim::update — an APPROXIMATION. It does NOT model mouse-ray → move-plane "
                     "steering (the ray-plane intersection finding above); the sim's camera is a "
                     "follow-cam, and there is no movement plane in the model yet."),
        },
        "replacement_readiness": {
            "status": "approximated",
            "gate": ("Replace keyboard-thrust movement with camera-ray → movement-plane steering in "
                     "CellSim; then a differential check against a Wine cell-mode trace (currently "
                     "absent). See docs/BOUNDARIES.md / docs/replacement-status.json "
                     "(cell-sim-movement-interaction)."),
            "missing_evidence": [
                "runtime trace of cell mode (Xvfb absent; headless menu navigation impossible)",
                "plane normal/point constant values",
                "camera-mode word semantics",
            ],
        },
        "runtime_reason": (
            "No cell-mode trace was recorded. Xvfb is absent on this host and headless menu "
            "navigation is impossible, so the original could only be traced as far as the main "
            "menu; the existing traces (see traces_scanned) are from a small test binary (obs_m32) "
            "and an empty main_menu capture — none reach cell mode. Recorded, not fabricated."
        ),
    },
}


def repo_path(*parts):
    return os.path.join(ROOT, *parts)


def snapshot_path_for(topic, explicit):
    if explicit:
        return explicit
    if topic == "cell-movement":
        return repo_path("tools", "re", "data", "ghidra_snapshot_cell_movement.json")
    return os.path.join(HERE, "data", "ghidra_snapshot_%s.json" % topic)


def load_json(path):
    with open(path) as f:
        return json.load(f)


def norm_hex(x):
    try:
        return int(str(x), 16)
    except ValueError:
        return None


def merge_vtables(snapshot):
    """Attach vtable-scan evidence from docs/analysis/vtables.json (match by address)."""
    out = [dict(v) for v in snapshot.get("vtables", [])]
    scan_path = repo_path("docs", "analysis", "vtables.json")
    if not os.path.exists(scan_path):
        return out
    scan = load_json(scan_path)

    def key(x):
        n = norm_hex(x) if x else None
        return "0x%08x" % n if n is not None else str(x).lower()

    by_addr = {}
    for c in scan.get("candidates", []):
        by_addr.setdefault(key(c.get("address")), c)
    for sa in scan.get("sdk_associations", []):
        by_addr.setdefault(key(sa.get("address")), sa)
    for v in out:
        hit = by_addr.get(key(v.get("address")))
        if hit:
            v["scan_match"] = {
                "address": hit.get("address"),
                "slots": hit.get("slots"),
                "confidence": hit.get("confidence"),
                "namespace": hit.get("namespace"),
                "source": "docs/analysis/vtables.json",
            }
    return out


def kg_lookup(topic):
    """Query knowledgegraph/spore.db directly (stdlib sqlite3; no kg.py dependency)."""
    db = repo_path("knowledgegraph", "spore.db")
    if not os.path.exists(db):
        return {"available": False, "nodes": [], "edges": []}
    keywords = [t for t in topic.replace("-", " ").split() if t]
    con = sqlite3.connect(db)
    con.row_factory = sqlite3.Row
    nodes = [dict(r) for r in con.execute(
        "SELECT label, name, attrs_json, confidence, origin "
        "FROM node ORDER BY label, name")]
    edges = [dict(r) for r in con.execute(
        "SELECT n1.name AS src, e.rel AS rel, n2.name AS dst "
        "FROM edge e JOIN node n1 ON n1.id=e.src "
        "JOIN node n2 ON n2.id=e.dst ORDER BY e.rel")]
    con.close()

    def relevant(n):
        text = (n["name"] + " " + (n.get("attrs_json") or "")).lower()
        return any(k in text for k in keywords)

    matched = [n for n in nodes if relevant(n)]
    return {
        "available": True,
        "db": "knowledgegraph/spore.db",
        "nodes": matched if matched else nodes[:20],
        "edges": edges,
    }


def dbpf_index_records(pkg):
    """Minimal DBPF v3 index reader — header + index region only.

    Mirrors tools/spore/dbpf/dbpf.py's layout (96B header; index items
    {type,group,instance,off(4|8),csize,msize,comp,saved,pad}). Returns the
    set of (type,group,instance) IDs, or None if the file is unusable.
    """
    with open(pkg, "rb") as f:
        header = f.read(96)
    if header[:4] not in (b"DBPF", b"DBBF"):
        return None
    le = lambda o: struct.unpack_from("<I", header, o)[0]
    # Header: magic(4) major(4) minor(4) pad(20) idxMaj(4) idxCount(4) pad(4)
    #         idxSize(4) pad(12) idxMinor(4) idxOffset(4) pad(28)
    idx_count, idx_size, idx_off = le(0x24), le(0x2C), le(0x40)
    with open(pkg, "rb") as f:
        f.seek(idx_off)
        buf = f.read(idx_size)
    flags = struct.unpack_from("<I", buf, 0)[0]
    o = 4
    type_id = group_id = -1
    if flags & 1:
        type_id = struct.unpack_from("<I", buf, o)[0]
        o += 4
    if flags & 2:
        group_id = struct.unpack_from("<I", buf, o)[0]
        o += 4
    if flags & 4:
        o += 4
    big = header[:4] == b"DBBF"
    seen = set()
    for _ in range(idx_count):
        t = type_id
        if t == -1:
            t = struct.unpack_from("<I", buf, o)[0]
            o += 4
        g = group_id
        if g == -1:
            g = struct.unpack_from("<I", buf, o)[0]
            o += 4
        i = struct.unpack_from("<I", buf, o)[0]
        o += 4
        o += 8 if big else 4
        o += 12  # csize(4) msize(4) comp(2) saved(1) pad(1)
        seen.add((t, g, i))
    return seen


def resource_refs(topic, notes):
    """Check referenced record IDs against the package DBPF index (if present)."""
    refs = [dict(r) for r in notes.get("resource_refs", [])]
    pkg = repo_path("SPORE", "Data", "Spore_Content.package")
    if not os.path.exists(pkg):
        return refs, {"available": False,
                      "note": "SPORE/Data/Spore_Content.package absent; record IDs unverified."}
    ids = dbpf_index_records(pkg)
    if ids is None:
        return refs, {"available": False,
                      "note": "package present but index unreadable; record IDs unverified."}
    for r in refs:
        key = (norm_hex(r["type"]), norm_hex(r["group"]), norm_hex(r["instance"]))
        r["status"] = ("CONFIRMED (present in DBPF index)" if key in ids
                       else "UNKNOWN (not found in DBPF index)")
    return refs, {"available": True, "record_count": len(ids),
                  "source": "SPORE/Data/Spore_Content.package"}


def scan_traces(snapshot):
    """Scan Observatory JSONL traces for events whose RVA matches a snapshot function."""
    rvas, addrs = set(), set()
    for fn in snapshot.get("functions", []):
        r = norm_hex(fn.get("rva")) if fn.get("rva") else None
        if r is not None:
            rvas.add(r)
        a = norm_hex(fn.get("address")) if fn.get("address") else None
        if a is not None:
            addrs.add(a)
    traces, matched = [], []
    for path in sorted(glob.glob(repo_path("tools", "observatory", "out", "*.jsonl"))):
        count = 0
        with open(path) as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                try:
                    e = json.loads(line)
                except json.JSONDecodeError:
                    continue
                count += 1
                rva = e.get("rva")
                if not rva:
                    continue
                try:
                    r = norm_hex(rva)
                except ValueError:
                    continue
                if r in rvas or r in addrs:
                    matched.append({
                        "trace": os.path.basename(path),
                        "name": e.get("name"),
                        "rva": rva,
                        "t_ns": e.get("t"),
                        "rel_ns": e.get("rel"),
                        "tid": e.get("tid"),
                        "args": {k: e.get(k) for k in ("eax", "ebx", "ecx", "edx")
                                  if e.get(k) is not None},
                    })
        traces.append({"file": os.path.basename(path), "events": count})
    return {"traces_scanned": traces, "matched_events": matched}


def evidence_levels_present(dossier):
    text = json.dumps(dossier).upper()
    return sorted({v for v in EVIDENCE_VOCAB if v in text})


def build(topic, snap_path, notes):
    snap = load_json(snap_path)
    module = "SporeApp.exe"
    functions = []
    for fn in snap.get("functions", []):
        functions.append({
            "name": fn.get("name"),
            "rva": fn.get("rva"),
            "address": fn.get("address"),
            "module": module,
            "size_bytes": fn.get("size_bytes"),
            "namespace": fn.get("namespace"),
            "signature": fn.get("signature"),
            "dispatch": fn.get("dispatch"),
            "role_inferred": fn.get("role_inferred"),
            "callers": fn.get("callers", []),
            "callees": fn.get("callees", []),
            "globals_referenced": fn.get("globals_referenced", []),
            "key_constants": fn.get("key_constants"),
            "decompiled_evidence": fn.get("decompiled_evidence"),
            "evidence_level": fn.get("evidence_level"),
        })
    runtime = scan_traces(snap)
    obtained = bool(runtime["matched_events"])
    reason = notes.get("runtime_reason") or (
        "No trace event matched any snapshot function RVA."
        if not obtained else "")
    refs, res_note = resource_refs(topic, notes)
    dossier = {
        "$schema": "re-dossier-1",
        "topic": topic,
        "sources": [
            os.path.relpath(snap_path, ROOT),
            "docs/analysis/vtables.json",
            "knowledgegraph/spore.db",
            "tools/observatory/out/*.jsonl",
        ],
        "snapshot_source": snap.get("source"),
        "evidence_summary": notes.get("evidence_summary",
                                      "(no narrative notes for this topic yet)"),
        "functions": functions,
        "callers": {f["name"]: f["callers"] for f in functions},
        "callees": {f["name"]: f["callees"] for f in functions},
        "vtables": merge_vtables(snap),
        "constants": (
            [{"name": k, "function": f["name"], "meaning": v}
             for f in functions if f.get("key_constants")
             for k, v in f["key_constants"].items()]),
        "globals": [dict(g) for g in snap.get("globals", [])],
        "runtime": {
            "obtained": obtained,
            "reason": reason,
            "traces_scanned": runtime["traces_scanned"],
            "matched_events": runtime["matched_events"],
        },
        "resource_refs": refs,
        "resource_note": res_note,
        "knowledge_graph": kg_lookup(topic),
        "asset_relationships": notes.get("asset_relationships", []),
        "hypotheses": notes.get("hypotheses", []),
        "known_unknowns": notes.get("known_unknowns", []),
        "openspore_counterpart": notes.get("openspore_counterpart"),
        "replacement_readiness": notes.get("replacement_readiness"),
    }
    return dossier


def render_md(d):
    lines = []
    a = lines.append
    a("# RE Dossier: %s" % d["topic"])
    a("")
    a("> Schema: docs/RE-DOSSIER-SCHEMA.md (re-dossier-1). Generated by "
      "tools/re/dossier.py from committed evidence only.")
    a("> **Decompiler output is EVIDENCE, NOT TRUTH**: no MSVC RTTI — callee types are")
    a("> decompiler guesses. SDK names are verified (march2017 SDK import); FUN_* names are")
    a("> Ghidra autogen addresses, not real names.")
    a("")
    a("## Evidence summary")
    a("")
    a(d["evidence_summary"])
    a("")
    a("## Original functions")
    a("")
    a("| name | RVA | module | size (B) | dispatch / vtable | evidence |")
    a("|---|---|---|---|---|---|")
    for f in d["functions"]:
        a("| %s | %s | %s | %s | %s | %s |" % (
            f["name"], f.get("rva") or "-", f.get("module") or "-",
            f.get("size_bytes") if f.get("size_bytes") is not None else "-",
            f.get("dispatch") or "-", f.get("evidence_level") or "-"))
    a("")
    for f in d["functions"]:
        a("### %s" % f["name"])
        if f.get("signature"):
            a("- signature: `%s`" % f["signature"])
        if f.get("role_inferred"):
            a("- role (INFERRED): %s" % f["role_inferred"])
        if f.get("decompiled_evidence"):
            a("- decompiled evidence (EVIDENCE, NOT TRUTH): %s" % f["decompiled_evidence"])
        if f.get("key_constants"):
            for k, v in f["key_constants"].items():
                a("- constant `%s` = %s (address OBSERVED; value INFERRED)" % (k, v))
        a("")
    a("## Callers")
    a("")
    for name, callers in d["callers"].items():
        fn = next(f for f in d["functions"] if f["name"] == name)
        if callers:
            caller_text = ", ".join(callers)
        elif (fn.get("dispatch") or "").startswith("vtable"):
            caller_text = "none static (vtable-dispatched)"
        else:
            caller_text = "none"
        a("- **%s**: %s" % (name, caller_text))
    a("")
    a("## Callees")
    a("")
    for name, callees in d["callees"].items():
        a("- **%s**: %s" % (name, ", ".join(callees) or "none"))
    a("")
    a("## Strings / constants")
    a("")
    if d["constants"]:
        a("| address | in function | meaning | evidence |")
        a("|---|---|---|---|")
        for c in d["constants"]:
            a("| %s | %s | %s | address OBSERVED / value INFERRED |" % (
                c["name"], c.get("function", "-"), c["meaning"]))
    else:
        a("(none recorded)")
    a("")
    if d["globals"]:
        a("Globals referenced: " + "; ".join(
            "`%s` (%s)" % (g.get("name"), g.get("note", "")) for g in d["globals"]))
        a("")
    a("## Runtime observations")
    a("")
    rt = d["runtime"]
    if rt["obtained"]:
        a("Observed events (source: Observatory traces):")
        for e in rt["matched_events"]:
            a("- %s in %s (T rel=%s, args=%s)" % (
                e.get("name"), e.get("trace"), e.get("rel_ns"),
                json.dumps(e.get("args") or {})))
    else:
        a("**NOT OBTAINED.** %s" % rt["reason"])
    if rt["traces_scanned"]:
        a("")
        a("Traces scanned: " + "; ".join(
            "%s (%d events)" % (t["file"], t["events"]) for t in rt["traces_scanned"]))
    a("")
    a("## Resource references")
    a("")
    if d["resource_refs"]:
        a("| type | group | instance | purpose | status |")
        a("|---|---|---|---|---|")
        for r in d["resource_refs"]:
            a("| %s | %s | %s | %s | %s |" % (
                r["type"], r["group"], r["instance"], r.get("purpose", ""),
                r.get("status", "UNVERIFIED")))
        rn = d["resource_note"]
        if rn.get("available"):
            a("")
            a("Checked against the DBPF index of %s (%d records)." % (
                rn.get("source"), rn.get("record_count", 0)))
        else:
            a("")
            a(rn.get("note", ""))
    else:
        a("[] — %s" % d["resource_note"].get("note", "no record IDs referenced"))
    a("")
    a("## Asset relationships")
    a("")
    for s in d["asset_relationships"] or ["(none recorded)"]:
        a("- %s" % s)
    a("")
    a("## Hypotheses")
    a("")
    for s in d["hypotheses"] or ["(none recorded)"]:
        a("- %s" % s)
    a("")
    a("## Known unknowns")
    a("")
    for s in d["known_unknowns"] or ["(none recorded)"]:
        a("- %s" % s)
    a("")
    a("## OpenSpore counterpart")
    a("")
    oc = d["openspore_counterpart"]
    if oc:
        a("- files: %s" % ", ".join("`%s`" % f for f in oc.get("files", [])))
        a("- faithfulness: %s" % oc.get("label", "-"))
        a("- %s" % oc.get("note", ""))
    else:
        a("(no OpenSpore counterpart yet)")
    a("")
    a("## Replacement readiness")
    a("")
    rr = d["replacement_readiness"]
    if rr:
        a("- status: **%s**" % rr.get("status", "-"))
        a("- gate: %s" % rr.get("gate", "-"))
        a("- missing evidence: %s" % "; ".join(rr.get("missing_evidence", []) or "-"))
    else:
        a("(not assessed)")
    a("")
    return "\n".join(lines) + "\n"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("topic")
    ap.add_argument("--snapshot", default=None)
    ap.add_argument("--out-dir", default=DEFAULT_OUT)
    a = ap.parse_args(argv)

    snap_path = snapshot_path_for(a.topic, a.snapshot)
    if not os.path.exists(snap_path):
        sys.exit("error: snapshot not found: %s" % snap_path)
    notes = TOPIC_NOTES.get(a.topic, {})
    dossier = build(a.topic, snap_path, notes)

    os.makedirs(a.out_dir, exist_ok=True)
    md_path = os.path.join(a.out_dir, "%s.md" % a.topic)
    js_path = os.path.join(a.out_dir, "%s.json" % a.topic)
    with open(md_path, "w") as f:
        f.write(render_md(dossier))
    with open(js_path, "w") as f:
        json.dump(dossier, f, indent=2)
        f.write("\n")

    levels = evidence_levels_present(dossier)
    print("dossier: %s" % a.topic)
    print("  functions: %d" % len(dossier["functions"]))
    print("  evidence levels present: %s" % ", ".join(levels))
    print("  runtime: %s" % ("OBTAINED (%d events)" % len(dossier["runtime"]["matched_events"])
                             if dossier["runtime"]["obtained"]
                             else "NOT OBTAINED"))
    print("  wrote %s" % os.path.relpath(md_path, ROOT))
    print("  wrote %s" % os.path.relpath(js_path, ROOT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
