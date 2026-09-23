#!/usr/bin/env python3
"""Bulk-ingest the Ghidra/community analysis exports into the knowledge graph.

Complements knowledgegraph/seed.py: seed.py loads committed canonical inputs;
this loads the Phase 1.5 export bundle (.spore-analysis/ghidra-exports/) --
58,757 functions, 2,035 structs + 25,546 fields, 3,081 vtable candidates,
306 vtable->SDK-class associations, 478 decompiled SDK functions -- and merges
them into knowledgegraph/spore.db over the existing schema (no redesign).

Merge semantics (merge, never overwrite):
  node:   upsert on (label,name); attrs_json is the union of existing +
          incoming (existing keys win); confidence/origin/note/evidence_level
          are preserved on conflict.
  edge:   INSERT OR IGNORE.
  field:  INSERT ... ON CONFLICT(struct_id,offset) DO NOTHING.

Provenance: every ingested row carries origin (community|ghidra), source
(path), revision (where known) and binary_sha256 (build identity).

Usage:
  kg_ingest.py [--exports DIR] [--db PATH] [--dry-run]
"""
import argparse
import glob
import json
import os
import re
import sqlite3
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, ".."))
KG_DIR = os.path.join(REPO, "knowledgegraph")

DEFAULT_EXPORTS = os.path.join(REPO, ".spore-analysis", "ghidra-exports")
DEFAULT_DB = os.path.join(KG_DIR, "spore.db")

# SporeApp.exe 3.1.0.22 (GOG, no DRM) -- see exports manifest.json.
BINARY_SHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
IMAGE_BASE = 0x400000  # PE ImageBase; trace rvas are recorded absolute
SDK_SOURCE = "Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml"
SDK_REVISION = "cbf9206"
EXPORT_REL = ".spore-analysis/ghidra-exports"

_NODE_INSERT = """
INSERT INTO node(label,name,attrs_json,confidence,origin,note,
                 evidence_level,binary_sha256)
VALUES(?,?,?,?,?,?,?,?)"""
_NODE_UPDATE = "UPDATE node SET attrs_json=?, updated_at=datetime('now') WHERE label=? AND name=?"


def _canonical(obj):
    return json.dumps(obj, sort_keys=True, separators=(",", ":"),
                      ensure_ascii=False)


def _va(s):
    s = s.lower().replace("0x", "")
    return s.zfill(8)[-8:] if s else None


def _read_tsv(path, header, cols):
    rows = []
    with open(path) as f:
        lines = [ln.rstrip("\n") for ln in f if ln.strip()]
    if header:
        assert lines[0].split("\t") == cols, f"{path}: unexpected header"
        lines = lines[1:]
    for ln in lines:
        cells = ln.split("\t")
        rows.append(dict(zip(cols, cells)))
    return rows


def load_exports(exports):
    ex = {}
    ex["fns"] = _read_tsv(os.path.join(exports, "functions.tsv"), True,
                          ["address", "name", "size", "is_thunk",
                           "is_external", "section"])
    ex["fnmap"] = {r["address"].lower(): r for r in ex["fns"]}
    ex["sdk"] = {r[0].lower(): r[1]
                 for r in (ln.rstrip("\n").split("\t")
                           for ln in open(os.path.join(
                               exports, "sdk_functions.tsv")) if ln.strip())}
    ex["structs"] = _read_tsv(os.path.join(exports, "structs.tsv"), True,
                              ["name", "size", "field_count"])
    ex["fields"] = _read_tsv(os.path.join(exports, "structs_fields.tsv"), True,
                             ["struct_name", "field_name", "type",
                              "offset", "size"])
    with open(os.path.join(exports, "vtables.json")) as f:
        ex["vtables"] = json.load(f)
    dec = {}
    for path in sorted(glob.glob(os.path.join(exports, "decompiled_sdk", "*.c"))):
        with open(path) as f:
            head = [f.readline() for _ in range(2)]
        m = re.search(r"@ ([0-9a-fA-F]{8,})\s*$", head[1]) if len(head) > 1 else None
        if m:
            dec[_va(m.group(1))] = f"{EXPORT_REL}/decompiled_sdk/" \
                f"{os.path.basename(path)}"
    ex["decompiled"] = dec
    return ex


def resolve_named_functions(existing, fnmap):
    """Address-resolve hand-made Function nodes (attrs addr/rva/address).

    Recorded trace values are absolute; dossier RVAs are base-relative. Try
    the raw value first, then IMAGE_BASE + value; the first that is a current
    function entry wins.
    """
    hits, stale, noaddr = {}, {}, []
    for key, row in existing.items():
        if key[0] != "Function" or key[1].startswith("fun:"):
            continue
        attrs = json.loads(row["attrs_json"] or "{}")
        raw = None
        for k in ("addr", "address", "rva"):
            if attrs.get(k):
                raw = attrs[k]
                break
        if raw is None:
            noaddr.append(key[1])
            continue
        v = int(raw, 16)
        cands = [format(v, "08x"), format(IMAGE_BASE + v, "08x")]
        for c in cands:
            if c in fnmap:
                hits[c] = key[1]
                break
        else:
            stale[key[1]] = cands
    return hits, stale, noaddr


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--exports", default=DEFAULT_EXPORTS)
    p.add_argument("--db", default=DEFAULT_DB)
    p.add_argument("--dry-run", action="store_true")
    a = p.parse_args(argv)

    sys.path.insert(0, KG_DIR)
    import kg  # noqa: E402  (schema migration + EV scale, same path as seed.py)

    ex = load_exports(a.exports)
    fnmap, sdk = ex["fnmap"], ex["sdk"]

    c = sqlite3.connect(a.db)
    c.row_factory = sqlite3.Row
    kg._migrate(c)

    existing = {}
    idmap = {}
    for r in c.execute("SELECT id,label,name,attrs_json,origin,confidence,"
                       "evidence_level,note FROM node"):
        existing[(r["label"], r["name"])] = r
        idmap[(r["label"], r["name"])] = r["id"]

    named_hits, named_stale, named_noaddr = \
        resolve_named_functions(existing, fnmap)

    # -- function nodes ----------------------------------------------------
    fun_recs, fun_merged_named = [], []
    fun_stale_named = []
    sdk_named = 0
    name_conflicts = []
    for va, r in fnmap.items():
        if va in named_hits:  # merged into the hand-made node instead
            continue
        base = {"address": va, "ghidra_name": r["name"],
                "size": int(r["size"]), "section": r["section"],
                "is_thunk": r["is_thunk"] == "true",
                "is_external": r["is_external"] == "true",
                "source": f"{EXPORT_REL}/functions.tsv"}
        if va in sdk:
            sdk_named += 1
            origin, ev = "community", "CONFIRMED"
            base["named"] = True
            base["sdk_name"] = sdk[va]
            base["source"] = SDK_SOURCE
            base["revision"] = SDK_REVISION
            if r["name"] != sdk[va]:
                name_conflicts.append((va, sdk[va], r["name"]))
        else:
            origin, ev = "ghidra", "SUPPORTED"
            base["named"] = not r["name"].startswith("FUN_")
        if va in ex["decompiled"]:
            base["decompiled_file"] = ex["decompiled"][va]
        fun_recs.append(("Function", f"fun:{va}", base, origin, ev, None))

    for va, name in named_hits.items():
        r = fnmap[va]
        attrs = {"address": va, "ghidra_name": r["name"], "size": int(r["size"]),
                 "section": r["section"], "ghidra_status": "function-entry"}
        fun_merged_named.append(("Function", name, attrs, None, None, None))
    for name, cands in named_stale.items():
        fun_stale_named.append(("Function", name,
                                {"address_candidates": cands,
                                 "ghidra_status":
                                     "no-function-entry-in-current-program"},
                                None, None, None))

    # -- structure nodes + fields ------------------------------------------
    struct_recs = []
    struct_names = {s["name"] for s in ex["structs"]}
    norm2struct = {}
    for s in ex["structs"]:
        norm = s["name"].lstrip("/").replace("/", "::")
        if norm.startswith("Spore::"):
            norm = norm[len("Spore::"):]
        norm2struct.setdefault(norm, s["name"])
    for s in ex["structs"]:
        is_comm = s["name"].startswith("/Spore/")
        origin = "community" if is_comm else "ghidra"
        ev = "CONFIRMED" if is_comm else "SUPPORTED"
        attrs = {"size": int(s["size"]), "field_count": int(s["field_count"]),
                 "source": f"{EXPORT_REL}/structs.tsv"}
        if is_comm:
            attrs["source"] = SDK_SOURCE
            attrs["revision"] = SDK_REVISION
        struct_recs.append(("Structure", f"struct:{s['name']}", attrs,
                           origin, ev, None))

    comm_structs = {s["name"] for s in ex["structs"]
                    if s["name"].startswith("/Spore/")}
    field_rows = [(f_["struct_name"],
                   "0x" + format(int(f_["offset"]), "x"), f_["field_name"],
                   f_["type"]) for f_ in ex["fields"]]

    class_struct_edges = []
    for key, row in existing.items():
        if key[0] != "Class":
            continue
        attrs = json.loads(row["attrs_json"] or "{}")
        sdk_name = attrs.get("sdk_name")
        if sdk_name and sdk_name in norm2struct:
            class_struct_edges.append(
                ("Class", key[1], "Structure",
                 f"struct:{norm2struct[sdk_name]}", "hasLayout"))

    # -- vtable nodes + edges ----------------------------------------------
    vt_recs, vt_edges = [], []
    cluster_of = {}
    for i, pair in enumerate(ex["vtables"].get("clusters", [])):
        for end in (_va(pair["a"]), _va(pair["b"])):
            if end:
                cluster_of.setdefault(end, []).append(i)
    for cand in ex["vtables"]["candidates"]:
        va = _va(cand["address"])
        if not va:
            continue
        attrs = {"address": cand["address"], "slots": len(cand["slots"]),
                 "score": cand.get("score"),
                 "confidence": cand.get("confidence"),
                 "namespace": cand.get("namespace"),
                 "sdkCount": cand.get("sdkCount"),
                 "fromLongRun": cand.get("fromLongRun"),
                 "source": f"{EXPORT_REL}/vtables.json"}
        if cand.get("firstSlotFunc"):
            attrs["firstSlotFunc"] = cand["firstSlotFunc"]
        if va in cluster_of:
            attrs["clusters"] = sorted(set(cluster_of[va]))
        vt_recs.append(("VTable", f"vt:{va}", attrs, "ghidra",
                       "INFERRED", None))
        for slot in cand["slots"]:
            if not slot.get("func"):
                continue
            va2 = _va(slot.get("ptr") or "")
            if va2 and va2 in fnmap:
                target = named_hits.get(va2, f"fun:{va2}")
                vt_edges.append(("VTable", f"vt:{va}", "Function",
                                 target, "hasSlot"))
    assoc_matched = 0
    for assoc in ex["vtables"].get("sdk_associations", []):
        va = _va(assoc.get("address") or "")
        if not va:
            continue
        attrs = {"subsystems": assoc.get("subsystems") or []}
        for f in assoc.get("sdkFuncs") or []:
            if "::" in f:
                attrs["sdk_name"] = "::".join(f.split("::")[:2])
                break
        vt_recs.append(("VTable", f"vt:{va}", attrs, None, None, None))
        if ("Class", f"cls:{va}") in existing:
            assoc_matched += 1
            vt_edges.append(("VTable", f"vt:{va}", "Class",
                             f"cls:{va}", "represents"))

    # -- emit ---------------------------------------------------------------
    report = {
        "functions": {"rows": len(fnmap), "sdk_named": sdk_named,
                      "name_conflicts": len(name_conflicts),
                      "merged_into_named_nodes": len(named_hits),
                      "named_nodes_stale": len(named_stale),
                      "named_nodes_no_address": len(named_noaddr)},
        "structures": {"rows": len(ex["structs"]),
                       "fields_rows": len(field_rows),
                       "class_hasLayout_edges": len(class_struct_edges)},
        "vtables": {"candidates": len(ex["vtables"]["candidates"]),
                    "sdk_associations": len(ex["vtables"]
                                            .get("sdk_associations", [])),
                    "associations_matched_class": assoc_matched,
                    "edges": len(set(vt_edges))},
        "decompiled_files": len(ex["decompiled"]),
        "investigations_rows_untouched": c.execute(
            "SELECT COUNT(*) FROM investigations").fetchone()[0],
    }

    if a.dry_run:
        print(json.dumps({"dry_run": True, "report": report}, indent=2))
        print(f"  sample name_conflicts: {name_conflicts[:5]}")
        print(f"  stale named nodes: {sorted(named_stale)}")
        return

    all_recs = {}
    for rec in (fun_recs + struct_recs + vt_recs + fun_merged_named
                + fun_stale_named):
        label, name, attrs, origin, ev, note = rec
        k = (label, name)
        if k in all_recs:
            pl, pn, pattrs, po, pe, pnote = all_recs[k]
            merged_in = dict(pattrs)
            merged_in.update(attrs)  # earlier record's keys win
            all_recs[k] = (label, name, merged_in, po or origin,
                           pe or ev, pnote or note)
        else:
            all_recs[k] = rec

    with c:
        n_new = n_upd = 0
        for label, name, attrs, origin, ev, note in all_recs.values():
            cur = existing.get((label, name))
            merged = dict(attrs)
            if cur is not None:
                old = json.loads(cur["attrs_json"] or "{}")
                merged = {**merged, **old}  # existing keys win
                c.execute(_NODE_UPDATE, (_canonical(merged), label, name))
                n_upd += 1
            else:
                conf = kg.scale.EV.get(ev, 0.0) if ev else 0.0
                c.execute(_NODE_INSERT,
                          (label, name, _canonical(merged), conf,
                           origin or "unknown", note, ev or "UNKNOWN",
                           BINARY_SHA))
                n_new += 1
            idmap.setdefault((label, name), None)

        for k in [k for k, v in idmap.items() if v is None]:
            idmap[k] = c.execute(
                "SELECT id FROM node WHERE label=? AND name=?", k
            ).fetchone()["id"]

        e_add = e_skip = e_miss = 0
        for sl, sn, dl, dn, rel in sorted(
                set(vt_edges + class_struct_edges)):
            s, d = idmap.get((sl, sn)), idmap.get((dl, dn))
            if s is None or d is None:
                e_miss += 1
                continue
            cur = c.execute("SELECT 1 FROM edge WHERE src=? AND dst=? AND rel=?",
                            (s, d, rel)).fetchone()
            if cur:
                e_skip += 1
            else:
                c.execute("INSERT INTO edge(src,dst,rel) VALUES(?,?,?)",
                          (s, d, rel))
                e_add += 1

        f_add = f_skip = f_miss = 0
        for struct_name, off, role, typ in field_rows:
            sid = idmap.get(("Structure", f"struct:{struct_name}"))
            if sid is None:
                f_miss += 1
                continue
            cur = c.execute(
                "SELECT 1 FROM field WHERE struct_id=? AND offset=?",
                (sid, off)).fetchone()
            if cur:
                f_skip += 1
            else:
                c.execute(
                    """INSERT INTO field(struct_id,offset,role,offset_evidence,
                       meaning_evidence,value,source,binary_sha256)
                       VALUES(?,?,?,?,?,?,?,?)""",
                    (sid, off, role,
                     "CONFIRMED" if struct_name in comm_structs
                     else "SUPPORTED",
                     "SUPPORTED", typ,
                     f"{EXPORT_REL}/structs_fields.tsv", BINARY_SHA))
                f_add += 1

    report["nodes_new"] = n_new
    report["nodes_merged"] = n_upd
    report["edges_added"] = e_add
    report["edges_existing"] = e_skip
    report["edges_missing_endpoints"] = e_miss
    report["fields_added"] = f_add
    report["fields_existing"] = f_skip
    report["fields_missing_struct"] = f_miss
    c.close()

    print(json.dumps({"report": report}, indent=2))
    print(f"  sample name_conflicts: {name_conflicts[:8]}")
    print(f"  stale named nodes: {sorted(named_stale)}")
    print(f"  no-address named nodes (untouched): {named_noaddr}")


if __name__ == "__main__":
    main()
