#!/usr/bin/env python3
"""Deterministic full-function triage classifier (triage-v4 / triage-v5,
stdlib only).

Covers all 58,757 functions from .spore-analysis/ghidra-exports/functions.tsv
(closure asserted: every input VA gets exactly one triage row).

Canonical key: VA8 = 8-char lowercase hex, no prefix.
  norm_va(s) = s.lower(), strip one leading '0x' prefix, zfill(8)[-8:]

Usage:
  classify.py [--exports DIR] [--db PATH] [--rules PATH] [--dry-run]

  --rules rules-v4.json (default): v4 behavior unchanged -- upsert triage
      table (idempotent), write projections triage-<snap8>.jsonl +
      summary-<snap8>.json (snapshot hash over the five v4 inputs).
  --rules rules-v5.json: v5 behavior -- same 58757 closure plus graph
      evidence (xrefs TSV), SDK contained-alias policy (boundary-repairs
      JSON), vtable-family attribution, CRT-wrapper middleware rescue,
      priority-quirk fix. Writes a NEW snapshot-hashed projection set
      (triage/summary/clusters/queue/attribution-<snap8>.*) under
      knowledgegraph/triage/ and NEVER touches spore.db by default
      (--db to opt in). 2540f2ca artifacts are never rewritten.

No incremental mode: every run classifies all 58757 functions from the
committed exports; refresh = rerun.

Determinism: inputs sorted, JSON separators/sort_keys fixed, no wall-clock in
projections (classified_at lives only in the DB row). Two runs on the same
inputs produce byte-identical projections.
"""

import argparse
import bisect
import csv
from collections import Counter
import glob
import hashlib
import json
import os
import re
import sqlite3
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
KG_DIR = os.path.join(REPO, "knowledgegraph")
TRIAGE_OUT = os.path.join(KG_DIR, "triage")

DEFAULT_EXPORTS = os.path.join(REPO, ".spore-analysis", "ghidra-exports")
DEFAULT_DB = os.path.join(KG_DIR, "spore.db")
DEFAULT_RULES = os.path.join(HERE, "rules-v4.json")

IMAGE_BASE = 0x400000
CLASSIFIER_VERSION = "triage-v4"
EXPORT_REL = ".spore-analysis/ghidra-exports"
DECOMP_REL = ".spore-analysis/ghidra-exports/decompiled_sdk"

HEX8 = re.compile(r"^[0-9a-f]{8}$")


def norm_va(s):
    s = (s or "").strip().lower()
    if s.startswith("0x"):
        s = s[2:]
    v = s.zfill(8)[-8:]
    if not HEX8.match(v):
        raise ValueError(f"not a hex VA: {s!r}")
    return v


def top_ns(name):
    return name.split("::")[0] if "::" in name else ""


def itanium_components(name):
    """Parse Itanium nested-name components of a _Z symbol.

    Handles length-prefixed scopes plus trailing ctor/dtor codes
    (C1/C2/C3/D0/D1/D2), e.g. _ZN6EditorC2Ev -> ['Editor','Editor'],
    _ZN2UI6WindowC2Ev -> ['UI','Window','Window']. Returns None unless
    the name is a well-formed _ZN...E nested name. Stdlib only.
    """
    if not name.startswith("_ZN"):
        return None
    s = name[3:]
    comps = []
    while s:
        if s[0].isdigit():
            j = 0
            while j < len(s) and s[j].isdigit():
                j += 1
            n = int(s[:j])
            s = s[j:]
            if len(s) < n or n == 0:
                return None
            comps.append(s[:n])
            s = s[n:]
        elif (s[0] in "CD" and len(s) > 1 and s[1].isdigit()
                and comps):
            comps.append(comps[-1])  # C2/D0: repeat innermost class
            s = s[2:]
        else:
            break
    if not comps or not s.startswith("E"):
        return None
    return comps


def load_inputs(exports, rules):
    # -- functions.tsv (with header) --------------------------------------
    fns_path = os.path.join(exports, "functions.tsv")
    with open(fns_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == ["address", "name", "size", "is_thunk",
                                 "is_external", "section"], \
            f"unexpected functions.tsv header: {rdr.fieldnames}"
        fns = list(rdr)
    seen = {}
    for r in fns:
        va = norm_va(r["address"])
        if va in seen:
            raise ValueError(f"duplicate VA in functions.tsv: {va}")
        seen[va] = r
        r["va8"] = va
    assert len(fns) == 58757, f"expected 58757 functions, got {len(fns)}"

    # -- sdk_functions.tsv (headerless, validate hex8) ---------------------
    # Deterministic last-wins on duplicate VA (file order is fixed by the
    # committed export). Known duplicate: 0093b630 (IO::StreamChild::
    # GetAccessFlags then UTFWin::ImageDrawable::GetImageDrawableFlags).
    sdk = {}
    sdk_dupes = []
    sdk_path = os.path.join(exports, "sdk_functions.tsv")
    with open(sdk_path) as f:
        for ln_no, ln in enumerate(f, 1):
            ln = ln.rstrip("\n")
            if not ln.strip():
                continue
            cells = ln.split("\t")
            assert len(cells) == 2, f"sdk_functions.tsv:{ln_no}: {ln!r}"
            va = norm_va(cells[0])  # raises unless hex8
            if va in sdk:
                sdk_dupes.append((va, sdk[va], cells[1], ln_no))
            sdk[va] = cells[1]
    for va, prev, cur, ln_no in sdk_dupes:
        print(f"warning: sdk_functions.tsv:{ln_no}: duplicate VA {va}: "
              f"{prev!r} overwritten by {cur!r} (last-wins)",
              file=sys.stderr)

    # -- structs (for best-effort struct_names) -----------------------------
    structs_path = os.path.join(exports, "structs.tsv")
    with open(structs_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == ["name", "size", "field_count"]
        structs = [r["name"] for r in rdr]
    struct_index = {}
    for full in structs:
        norm = full.lstrip("/").replace("/", "::")
        if norm.startswith("Spore::"):
            norm = norm[len("Spore::"):]
        struct_index.setdefault(norm, []).append(full)
        struct_index.setdefault(norm.split("::")[-1], []).append(full)

    # -- vtables.json (slot membership: func va -> sorted vtable va list) ---
    with open(os.path.join(exports, "vtables.json")) as f:
        vt = json.load(f)
    func_to_vt = {}
    for cand in vt["candidates"]:
        cva = norm_va(cand["address"])
        for slot in cand.get("slots", []):
            if slot.get("funcStart") and slot.get("func"):
                fva = norm_va(slot.get("ptr") or "")
                func_to_vt.setdefault(fva, set()).add(cva)

    # -- decompiled_sdk/ (VA regex on header line 2, kg_ingest-compatible) ---
    decomp = {}
    for path in sorted(glob.glob(os.path.join(exports, "decompiled_sdk",
                                              "*.c"))):
        with open(path) as f:
            head = [f.readline() for _ in range(2)]
        m = re.search(r"@ ([0-9a-fA-F]{8,})\s*$",
                      head[1]) if len(head) > 1 else None
        if m:
            decomp[norm_va(m.group(1))] = \
                f"{DECOMP_REL}/{os.path.basename(path)}"

    # -- snapshot hash (deterministic over raw input bytes) ------------------
    h = hashlib.sha256()
    for name in ("functions.tsv", "sdk_functions.tsv", "structs.tsv",
                 "structs_fields.tsv", "vtables.json"):
        with open(os.path.join(exports, name), "rb") as f:
            h.update(f.read())
    dec_names = sorted(os.path.basename(p) for p in glob.glob(
        os.path.join(exports, "decompiled_sdk", "*.c")))
    h.update("\n".join(dec_names).encode())
    snapshot = h.hexdigest()
    return {"fns": fns, "sdk": sdk, "struct_index": struct_index,
            "func_to_vt": func_to_vt, "decomp": decomp,
            "snapshot": snapshot, "snap8": snapshot[:8]}


def match_structs(sdk_name, struct_index):
    """Best-effort SDK class -> struct name(s). May be empty."""
    if not sdk_name or "::" not in sdk_name:
        return []
    parts = sdk_name.split("::")
    cls = "::".join(parts[:-1]) if len(parts) > 2 else parts[0]
    out = []
    for key in (cls, parts[-2] if len(parts) > 1 else cls):
        for full in struct_index.get(key, []):
            if full not in out:
                out.append(full)
    return sorted(out)


def classify_row(r, sdk, struct_index, func_to_vt, decomp, rules,
                  _tp=None):
    va = r["va8"]
    va_int = int(va, 16)
    rva_int = va_int - IMAGE_BASE
    assert rva_int >= 0, f"VA below ImageBase: {va}"
    gname = r["name"]
    is_thunk = r["is_thunk"] == "true"
    is_ext = r["is_external"] == "true"
    section = r["section"]
    sdk_name = sdk.get(va)
    is_fun = gname.startswith("FUN_")
    vts = sorted(func_to_vt.get(va, ()))
    in_vtable = bool(vts)
    decomp_path = decomp.get(va)

    if _tp is None:
        _tp = ([re.compile(p) for p in
                rules["third_party_global_regexes"]],
               set(rules["third_party_global_names"]))
    tp_res, tp_names = _tp
    is_global = "::" not in gname
    # v3(a): Itanium symbols whose outermost class is a known game class
    # (verified game ctors, e.g. Editor::Editor) are exempt from the ^_Z
    # third-party hit and classified from their demangled scope.
    itanium_comps = itanium_components(gname)
    itanium_game = (bool(itanium_comps) and itanium_comps[0] in
                    rules.get("itanium_game_classes", []))
    eff_name = "::".join(itanium_comps) if itanium_game else gname
    norm_name = (eff_name if itanium_game
                 else (gname[6:] if gname.startswith("thunk_") else gname))
    third_party_hit = (
        is_thunk or is_ext or section != ".text"
        or (is_global and not itanium_game and (gname in tp_names
                            or any(p.search(gname) for p in tp_res)))
    )

    ns = top_ns(sdk_name or eff_name)
    engine_ns = set(rules["engine_namespaces"])
    game_ns = set(rules["game_namespaces"])

    # -- category (first match wins) ---------------------------------------
    reasons = []
    if third_party_hit:
        category = "THIRD_PARTY_OR_RUNTIME"
        reasons.append("thunk/external/section/name-pattern")
    elif sdk_name and top_ns(sdk_name) in engine_ns:
        category = "ENGINE_INTERFACE"
        reasons.append(f"sdk+engine-ns({top_ns(sdk_name)})")
    elif (sdk_name and top_ns(sdk_name) in game_ns and in_vtable):
        # v3(b): SDK-CONFIRMED game-namespace virtuals are gameplay, not
        # generic engine implementation. Singleton Get/Set/Property keeps
        # the GAMEPLAY_SUPPORT reading it has for non-virtual rows.
        if re.search(rules["singleton_regex"], sdk_name):
            category = "GAMEPLAY_SUPPORT"
            reasons.append(f"game-virtual-singleton({top_ns(sdk_name)})")
        else:
            category = "GAMEPLAY_LOGIC"
            reasons.append(f"game-virtual({top_ns(sdk_name)})")
    elif in_vtable:
        category = "ENGINE_IMPLEMENTATION"
        reasons.append(f"vtable-slot(x{len(vts)})")
    elif re.search(rules["singleton_regex"], eff_name):
        category = "GAMEPLAY_SUPPORT"
        reasons.append("singleton-Get/Set/Property")
    elif ((not is_fun and (ns in game_ns or any(
            eff_name.startswith(p) for p in rules["game_global_prefixes"])))
            or (sdk_name and top_ns(sdk_name) in game_ns)):
        category = "GAMEPLAY_LOGIC"
        reasons.append(f"game-ns({ns or 'global'})")
    else:
        category = "UNKNOWN"
        reasons.append("no-rule-matched")
    if itanium_game:
        reasons.append(f"itanium-demangle({'::'.join(itanium_comps)})")

    # -- priority ------------------------------------------------------------
    if is_thunk or is_ext or section != ".text":
        priority = "IGNORE"
    elif sdk_name and in_vtable and decomp_path:
        priority = "P0"
    elif bool(sdk_name) ^ (in_vtable or bool(decomp_path)):
        priority = "P1"
    elif (not is_fun and not sdk_name and
            (ns in game_ns or any(eff_name.startswith(p)
                                   for p in rules["game_global_prefixes"]))):
        priority = "P2"
    else:
        priority = "P3"
    if priority != "IGNORE":
        reasons.append(f"prio:{priority}")

    # -- evidence --------------------------------------------------------------
    if is_thunk or is_ext:
        evidence = "UNKNOWN"
    elif sdk_name:
        evidence = "CONFIRMED"
    elif not is_fun and not is_thunk:
        evidence = "SUPPORTED"
    elif in_vtable or category == "GAMEPLAY_LOGIC":
        evidence = "INFERRED"
    else:
        evidence = "UNKNOWN"

    # -- subsystem ---------------------------------------------------------------
    sub_map = rules["namespace_subsystem"]
    if ns and ns in sub_map:
        subsystem = sub_map[ns]
    elif third_party_hit:
        subsystem = "Runtime"
    elif any(eff_name.startswith(p)
              for p in rules["game_global_prefixes"]):
        subsystem = "GameGlobal"
    else:
        subsystem = "Unknown"

    recon = 1 if (priority in ("P0", "P1") and decomp_path) else 0

    return {
        "va": va,
        "rva": format(rva_int, "08x"),
        "ghidra_name": gname,
        "norm_name": norm_name,
        "subsystem": subsystem,
        "category": category,
        "priority": priority,
        "evidence": evidence,
        "sdk_name": sdk_name,
        "vtable_addrs": vts,
        "struct_names": match_structs(sdk_name, struct_index),
        "caller_count": None,
        "callee_count": None,
        "decomp_path": decomp_path,
        "recon_candidate": recon,
        "rationale": "; ".join(reasons),
        "kg_node_id": f"fun:{va}",
    }


TRIAGE_COLS = ["va", "rva", "ghidra_name", "norm_name", "subsystem",
               "category", "priority", "evidence", "sdk_name",
               "vtable_addrs", "struct_names", "caller_count",
               "callee_count", "decomp_path", "recon_candidate",
               "rationale", "kg_node_id", "snapshot_sha256"]


def classify_all(data, rules):
    tp = ([re.compile(p) for p in rules["third_party_global_regexes"]],
          set(rules["third_party_global_names"]))
    rows = [classify_row(r, data["sdk"], data["struct_index"],
                         data["func_to_vt"], data["decomp"], rules, _tp=tp)
            for r in data["fns"]]
    assert len(rows) == len(data["fns"]) == 58757, \
        f"closure broken: {len(rows)} rows for {len(data['fns'])} functions"
    assert len({r["va"] for r in rows}) == 58757, "duplicate VA in output"
    rows.sort(key=lambda r: r["va"])
    for r in rows:
        r["snapshot_sha256"] = data["snapshot"]
        r["classifier_version"] = CLASSIFIER_VERSION
    return rows


def summarize(rows, data):
    from collections import Counter
    return {
        "classifier_version": CLASSIFIER_VERSION,
        "snapshot_sha256": data["snapshot"],
        "snap8": data["snap8"],
        "total": len(rows),
        "by_category": dict(sorted(Counter(r["category"]
                                           for r in rows).items())),
        "by_priority": dict(sorted(Counter(r["priority"]
                                           for r in rows).items())),
        "by_evidence": dict(sorted(Counter(r["evidence"]
                                           for r in rows).items())),
        "by_subsystem": dict(sorted(Counter(r["subsystem"]
                                            for r in rows).items())),
        "recon_candidates": sum(r["recon_candidate"] for r in rows),
        "p0_list": [r["va"] for r in rows if r["priority"] == "P0"],
    }


UPSERT = """INSERT INTO triage(va,rva,ghidra_name,norm_name,subsystem,category,
  priority,evidence,sdk_name,vtable_addrs,struct_names,caller_count,
  callee_count,decomp_path,recon_candidate,rationale,kg_node_id,
  snapshot_sha256,classifier_version,classified_at)
  VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,datetime('now'))
  ON CONFLICT(va) DO UPDATE SET
  rva=excluded.rva,ghidra_name=excluded.ghidra_name,
  norm_name=excluded.norm_name,subsystem=excluded.subsystem,
  category=excluded.category,priority=excluded.priority,
  evidence=excluded.evidence,sdk_name=excluded.sdk_name,
  vtable_addrs=excluded.vtable_addrs,struct_names=excluded.struct_names,
  caller_count=excluded.caller_count,callee_count=excluded.callee_count,
  decomp_path=excluded.decomp_path,recon_candidate=excluded.recon_candidate,
  rationale=excluded.rationale,kg_node_id=excluded.kg_node_id,
  snapshot_sha256=excluded.snapshot_sha256,
  classifier_version=excluded.classifier_version,
  classified_at=datetime('now')"""


def write_db(db_path, rows, version=CLASSIFIER_VERSION):
    sys.path.insert(0, KG_DIR)
    import kg  # noqa: E402 schema migration, same pattern as seed.py
    c = sqlite3.connect(db_path)
    kg._migrate(c)
    with c:
        for r in rows:
            c.execute(UPSERT, (
                r["va"], r["rva"], r["ghidra_name"], r["norm_name"],
                r["subsystem"], r["category"], r["priority"], r["evidence"],
                r["sdk_name"],
                json.dumps(r["vtable_addrs"], sort_keys=True),
                json.dumps(r["struct_names"], sort_keys=True),
                None, None, r["decomp_path"], r["recon_candidate"],
                r["rationale"], r["kg_node_id"], r["snapshot_sha256"],
                version))
    n = c.execute("SELECT COUNT(*) FROM triage").fetchone()[0]
    c.close()
    assert n == 58757, f"triage table has {n} rows, expected 58757"
    return n


def write_projections(rows, summary):
    os.makedirs(TRIAGE_OUT, exist_ok=True)
    snap8 = summary["snap8"]
    jl = os.path.join(TRIAGE_OUT, f"triage-{snap8}.jsonl")
    sm = os.path.join(TRIAGE_OUT, f"summary-{snap8}.json")
    with open(jl, "w") as f:
        for r in rows:
            f.write(json.dumps(r, sort_keys=True,
                               separators=(",", ":")) + "\n")
    with open(sm, "w") as f:
        json.dump(summary, f, indent=2, sort_keys=True)
    return jl, sm


# ============================ triage-v5 =====================================
# Graph evidence + SDK contained-alias policy + vtable-family attribution +
# middleware identification. All inputs are frozen committed artifacts; the
# v5 snapshot hash extends the v4 core hash with the four v5 inputs.

V5_VERSION = "triage-v5"


def classify_v5(data, v5, rules):
    """v4 category chain (with alias layer) + v5 post-processing."""
    tp = ([re.compile(p) for p in rules["third_party_global_regexes"]],
          set(rules["third_party_global_names"]))
    game_ns = set(rules["game_namespaces"])
    sub_map = rules["namespace_subsystem"]
    fam_min = int(rules["v5_vtable_family"]["min_distinct_sdk_funcs"])

    rows = [classify_row(r, v5["sdk5"], data["struct_index"],
                         data["func_to_vt"], data["decomp"], rules, _tp=tp)
            for r in data["fns"]]
    assert len(rows) == len(data["fns"]) == 58757
    by_va = {r["va"]: r for r in rows}

    fam_attributed = 0
    fam_engine = 0
    fam_anonymous = 0
    crt_wrappers = 0
    quirk_fixed = 0
    vtable_pool = 0

    for r in data["fns"]:
        row = by_va[r["va8"]]
        va = r["va8"]
        is_fun = r["name"].startswith("FUN_")
        in_vtable = bool(row["vtable_addrs"])
        sdk = row["sdk_name"]
        fam = v5["func_family"].get(va)

        # -- vtable family attribution (the 5755 FUN_ pool + any members) ----
        if in_vtable:
            if row["category"] == "ENGINE_IMPLEMENTATION" \
                    and row["evidence"] == "INFERRED":
                vtable_pool += 1
            if fam:
                if fam["ns"] in game_ns and fam["distinct_sdk_funcs"] >= fam_min \
                        and row["category"] == "ENGINE_IMPLEMENTATION":
                    row["category"] = "GAMEPLAY_LOGIC"
                    fam_attributed += 1
                else:
                    fam_engine += 1
                row["rationale"] += (
                    f"; v5-vtable-family({fam['ns']}::{fam['class']},"
                    f"{fam['distinct_sdk_funcs']} distinct sdk slot funcs,"
                    f"via {fam['via']})")
                if row["subsystem"] == "Unknown" and fam["ns"] in sub_map:
                    row["subsystem"] = sub_map[fam["ns"]]
            else:
                fam_anonymous += 1
        row["vtable_family"] = (
            f"{fam['ns']}::{fam['class']}" if fam else None)

        # -- CRT/STL wrapper rescue (UNKNOWN rows only) ------------------------
        imps = sorted(v5["import_fams"].get(va, ()))
        row["import_families"] = imps
        if row["category"] == "UNKNOWN" and row["priority"] != "IGNORE" \
                and "CRT" in imps and not v5["callees"].get(va):
            row["category"] = "THIRD_PARTY_OR_RUNTIME"
            row["evidence"] = "INFERRED"
            row["subsystem"] = "Runtime"
            row["rationale"] += (
                "; v5-crt-wrapper(msvcr90-import-only, 0 internal callees)")
            crt_wrappers += 1

        # -- SCC metadata -------------------------------------------------------
        row["scc_size"] = v5["scc_size"].get(va, 1)
        if row["scc_size"] > 1:
            row["rationale"] += f"; scc({row['scc_size']})"

        # -- alias metadata ------------------------------------------------------
        al = sorted(set(v5["aliases"].get(va, ())))
        row["aliases"] = al
        if al:
            row["rationale"] += (
                f"; v5-sdk-alias(contained; canonical {row['sdk_name']},"
                f"{len(al)} alias name(s))")

        # -- priority quirk fix (v5 definition; v4 set is a subset) ------------
        # Mirrors v4 classify_row exactly (incl. Itanium demangle +
        # thunk_ strip) so unchanged rows keep their v4 priority.
        if row["priority"] != "IGNORE":
            dec = bool(row["decomp_path"])
            itanium_comps = itanium_components(r["name"])
            itanium_game = bool(itanium_comps) and itanium_comps[0] in \
                rules.get("itanium_game_classes", [])
            eff = "::".join(itanium_comps) if itanium_game else (
                r["name"][6:] if r["name"].startswith("thunk_")
                else r["name"])
            ns = top_ns(sdk or eff)
            v4_p2 = (not is_fun and not sdk
                     and (ns in game_ns or any(
                         eff.startswith(p)
                         for p in rules["game_global_prefixes"])))
            if sdk and in_vtable and dec:
                new = "P0"
            elif (sdk and in_vtable) \
                    or (bool(sdk) ^ (in_vtable or dec)):
                new = "P1"
            elif v4_p2:
                new = "P2"
            else:
                new = "P3"
            if new != row["priority"]:
                if new == "P1" and row["priority"] == "P3" \
                        and sdk and in_vtable and not dec:
                    quirk_fixed += 1
                    row["rationale"] += (
                        "; v5-priority-fix(sdk+vtable-no-decomp P3->P1)")
                row["rationale"] = row["rationale"].replace(
                    f"; prio:{row['priority']}", f"; prio:{new}")
            row["priority"] = new

    rows = [by_va[r["va8"]] for r in data["fns"]]
    rows.sort(key=lambda r: r["va"])
    for r in rows:
        r["snapshot_sha256"] = v5["snapshot"]
        r["classifier_version"] = V5_VERSION
    stats = {"vtable_pool": vtable_pool, "fam_attributed": fam_attributed,
             "fam_engine": fam_engine, "fam_anonymous": fam_anonymous,
             "crt_wrappers": crt_wrappers, "quirk_fixed": quirk_fixed}
    return rows, stats


def summarize_v5(rows, data, v5, stats):
    from collections import Counter
    s = {
        "classifier_version": V5_VERSION,
        "snapshot_sha256": v5["snapshot"],
        "snap8": v5["snap8"],
        "total": len(rows),
        "by_category": dict(sorted(Counter(r["category"]
                                           for r in rows).items())),
        "by_priority": dict(sorted(Counter(r["priority"]
                                           for r in rows).items())),
        "by_evidence": dict(sorted(Counter(r["evidence"]
                                           for r in rows).items())),
        "by_subsystem": dict(sorted(Counter(r["subsystem"]
                                            for r in rows).items())),
        "recon_candidates": sum(r["recon_candidate"] for r in rows),
        "p0_list": [r["va"] for r in rows if r["priority"] == "P0"],
    }
    fams = Counter()
    for r in rows:
        if r.get("vtable_family"):
            fams[r["vtable_family"]] += 1
    scc_gt1 = sum(1 for r in rows if r["scc_size"] > 1)
    msvcrt_callers = sum(1 for r in rows if "CRT" in r["import_families"])
    s["v5"] = {
        "alias_policy": v5["alias_stats"],
        "priority_fix_rows": stats["quirk_fixed"],
        "vtable_pool_fun_rows": stats["vtable_pool"],
        "family_attributed_gameplay": stats["fam_attributed"],
        "family_engine_kept": stats["fam_engine"],
        "family_anonymous_debt": stats["fam_anonymous"],
        "crt_wrappers": stats["crt_wrappers"],
        "scc_members_gt1": scc_gt1,
        "msvcr90_callers": msvcrt_callers,
        "top_families": dict(fams.most_common(30)),
        "middleware": {
            "crt_stl": "MSVCR90 import ancestry (362 frozen external dests); "
                       "wrapper rows: MSVCR90-only import calls + zero "
                       "internal callees",
            "renderware": "19 SDK RenderWare:: functions (5 are function "
                          "entries) + vtable families with RenderWare slots; "
                          "no RW import dests (statically linked)",
            "directx": "ABSENT: zero D3D/IDirect-named functions, zero "
                       "d3dx9/D3DX import dests (GOG build uses RenderWare)",
            "eastl": "ABSENT: zero ea::/EASTL symbols in functions/sdk/strings",
            "steam": "SteamAPI_* names -> THIRD_PARTY_OR_RUNTIME (v4 regex)",
        },
    }
    return s


def build_v5_queue(rows, v5, rules):
    """Preserve all 207 v4 queue rows verbatim (state + rank); append v5
    gameplay promotions as candidates. No wall-clock (rerun-stable)."""
    q4 = v5["queue_v4"]
    q = list(q4["queue"])
    queued_va = {x["va"] for x in q}
    fam_min = int(rules["v5_vtable_family"]["min_distinct_sdk_funcs"])
    fam_k = {va: fam["distinct_sdk_funcs"]
             for va, fam in v5["func_family"].items()}

    promoted = []
    for r in rows:
        if r["category"] != "GAMEPLAY_LOGIC":
            continue
        if r["va"] in queued_va:
            continue
        if not r.get("vtable_family"):
            continue
        # defensible: family-backed gameplay with structural slot evidence
        # (family must carry >= fam_min distinct SDK slot funcs)
        if fam_k.get(r["va"], 0) < fam_min:
            continue
        if not (r["evidence"] in ("CONFIRMED", "INFERRED")
                and r["vtable_addrs"]):
            continue
        promoted.append(r)
    promoted.sort(key=lambda r: (-fam_k.get(r["va"], 0), r["va"]))
    rank = len(q)
    for r in promoted:
        rank += 1
        q.append({
            "rank": rank,
            "va": r["va"],
            "rva": r["rva"],
            "name": r["ghidra_name"],
            "subsystem": r["subsystem"],
            "category": r["category"],
            "priority": r["priority"],
            "evidence": r["evidence"],
            "rationale": f"v5-promotion (candidate): {r['rationale']}",
            "queue_state": "candidate",
            "db_triage_status": "candidate",
            "decomp_path": r["decomp_path"],
            "cluster": _row_cluster(r),
            "dependencies": [],
            "kg_node_id": r["kg_node_id"],
            "provenance": {
                "snapshot": v5["snap8"],
                "snapshot_sha256": v5["snapshot"],
                "classifier": V5_VERSION,
                "sdk_name": r["sdk_name"],
                "vtable_addrs": r["vtable_addrs"],
            },
        })
    counts = Counter(x["queue_state"] for x in q)
    return {
        "snap8": v5["snap8"],
        "snapshot_sha256": v5["snapshot"],
        "classifier": V5_VERSION,
        "generator": "tools/triage/classify.py --rules rules-v5.json",
        "ordering": q4["ordering"] + " > v5-promoted candidates (family "
                  "distinct-sdk-func count desc, then va)",
        "queue_state_vocab": q4["queue_state_vocab"],
        "db_mapping": q4["db_mapping"],
        "scope_notes": list(q4["scope_notes"]) + [
            f"triage-v5 2026-09-23: all 207 v4 rows preserved verbatim "
            f"(state, rank, db mapping); +{len(promoted)} v5 family-backed "
            f"gameplay candidates appended; ambiguous/anonymous vtable rows "
            f"stay UNKNOWN debt (not queued). No wall-clock fields (rerun "
            f"byte-identical).",
        ],
        "counts": dict(sorted(counts.items())),
        "total": len(q),
        "queue": q,
        "reproducibility": q4.get("reproducibility", {}),
    }


def _row_cluster(r):
    """Per-row partition into the v4 20-cluster taxonomy (exhaustive;
    every row maps to exactly one cluster). Simulator rows split by name
    keyword the same way the v4 inventory did."""
    sub = r["subsystem"]
    if sub == "Unknown":
        return ("unknown-vtable-impl" if r["vtable_addrs"]
                else "unknown-fun-mass")
    if sub == "Simulator":
        low = r["ghidra_name"].lower()
        if "cell" in low:
            return "sim-cell"
        if "space" in low:
            return "sim-space"
        if any(k in low for k in ("creature", "tribe", "civ")):
            return "sim-creature-tribeciv"
        return "sim-core-systems"
    m = {"UTFWin": "utfwin-framework",
         "App": "app-lifecycle", "Clock": "app-lifecycle",
         "Resource": "resource-io", "IO": "resource-io",
         "Editor": "editor-core",
         "Palettes": "editor-support", "Skinner": "editor-support",
         "Sporepedia": "sporepedia-online", "Pollinator": "sporepedia-online",
         "Terrain": "terrain-world",
         "Graphics": "graphics-render", "RenderWare": "graphics-render",
         "Transform": "graphics-render",
         "UI": "ui-shell",
         "ArgScript": "scripting-content",
         "Swarm": "swarm-anim", "Anim": "swarm-anim", "Math": "swarm-anim",
         "Audio": "audio-input", "GameInput": "audio-input",
         "GameGlobal": "gameglobal-misc", "LocalizedString": "gameglobal-misc",
         "Space": "sim-space",
         "Runtime": "runtime-crt-stl"}
    return m.get(sub, "gameglobal-misc")


def build_v5_clusters(rows, v4_clusters):
    """Recompute the 20-cluster inventory from v5 rows via the exhaustive
    per-row partition (_row_cluster); sum must equal 58757. vtable-family +
    middleware sections are new in v5."""
    per_cluster = Counter(_row_cluster(r) for r in rows)
    assert sum(per_cluster.values()) == len(rows) == 58757
    by_sub = Counter(r["subsystem"] for r in rows)
    out = []
    for cl in v4_clusters:
        c = dict(cl)
        c["function_count"] = per_cluster.get(cl["name"], 0)
        c["v4_function_count"] = cl.get("function_count")
        c["triage_subsystem_counts"] = dict(
            sorted((s, by_sub[s]) for s in cl.get("triage_subsystems", [])
                   if s in by_sub))
        out.append(c)
    total = sum(c["function_count"] for c in out)
    fams = Counter()
    fam_rows = {}
    for r in rows:
        f = r.get("vtable_family")
        if f and r["vtable_addrs"]:
            fams[f] += 1
            fam_rows.setdefault(f, Counter())[r["category"]] += 1
    return {
        "_comment": "triage-v5 cluster inventory: v4 20-cluster taxonomy "
                    "recomputed from v5 rows (subsystem fill from vtable "
                    "families moves rows out of Unknown). Sum must equal "
                    "58757. vtable_family + middleware sections new in v5.",
        "classifier_version": V5_VERSION,
        "snapshot_sha256": rows[0]["snapshot_sha256"],
        "snap8": rows[0]["snapshot_sha256"][:8],
        "required_taxonomy": [
            "GAMEPLAY_LOGIC", "GAMEPLAY_SUPPORT", "ENGINE_INTERFACE",
            "ENGINE_IMPLEMENTATION", "THIRD_PARTY_OR_RUNTIME", "UNKNOWN"],
        "clusters": out,
        "cluster_sum_check": total,
        "vtable_families": {
            "total_functions_in_families": sum(fams.values()),
            "by_family": {
                f: {"member_rows": fams[f],
                    "by_category": dict(sorted(fam_rows[f].items()))}
                for f in sorted(fams, key=lambda f: (-fams[f], f))},
        },
    }


def build_v5_attribution(rows, v5, rules):
    """Per-family vtable breakdown for the 5755 FUN_ pool + middleware
    rationale examples (3-5 per middleware, machine-readable)."""
    from collections import Counter
    pool = [r for r in rows
            if r["category"] in ("ENGINE_IMPLEMENTATION", "GAMEPLAY_LOGIC")
            and r["vtable_addrs"] and r["ghidra_name"].startswith("FUN_")]
    per_ns = Counter()
    per_ns_cat = {}
    for r in pool:
        f = r.get("vtable_family")
        ns = f.split("::")[0] if f else "anonymous"
        per_ns[ns] += 1
        per_ns_cat.setdefault(ns, Counter())[r["category"]] += 1
    def ex(pred, n=5):
        out = []
        for r in sorted(rows, key=lambda x: x["va"]):
            if pred(r):
                out.append({"va": r["va"], "name": r["ghidra_name"],
                            "category": r["category"],
                            "rationale": r["rationale"]})
            if len(out) >= n:
                break
        return out
    rw = ex(lambda r: r["subsystem"] == "RenderWare"
            and not r["ghidra_name"].startswith("thunk_"))
    crt = ex(lambda r: "v5-crt-wrapper" in r["rationale"])
    steam = ex(lambda r: r["ghidra_name"].startswith("SteamAPI_"))
    famg = ex(lambda r: "v5-vtable-family" in r["rationale"]
              and r["category"] == "GAMEPLAY_LOGIC"
              and r["ghidra_name"].startswith("FUN_"))
    return {
        "classifier_version": V5_VERSION,
        "snapshot_sha256": rows[0]["snapshot_sha256"],
        "fun_vtable_pool": len(pool),
        "pool_by_family_ns": {
            ns: {"rows": per_ns[ns], "by_category": dict(
                sorted(per_ns_cat[ns].items()))}
            for ns in sorted(per_ns, key=lambda n: (-per_ns[n], n))},
        "middleware_examples": {
            "renderware": rw,
            "crt_stl_wrappers": crt,
            "steam": steam,
            "vtable_family_gameplay": famg,
        },
    }


def write_v5_projections(rows, summary, v5, rules):
    os.makedirs(TRIAGE_OUT, exist_ok=True)
    snap8 = v5["snap8"]
    paths = {}
    jl = os.path.join(TRIAGE_OUT, f"triage-{snap8}.jsonl")
    with open(jl, "w") as f:
        for r in rows:
            f.write(json.dumps(r, sort_keys=True,
                               separators=(",", ":")) + "\n")
    paths["triage"] = jl

    sm = os.path.join(TRIAGE_OUT, f"summary-{snap8}.json")
    with open(sm, "w") as f:
        json.dump(summary, f, indent=2, sort_keys=True)
    paths["summary"] = sm

    cl4 = json.load(open(os.path.join(TRIAGE_OUT, "clusters-2540f2ca.json")))
    cl = build_v5_clusters(rows, cl4["clusters"])
    clp = os.path.join(TRIAGE_OUT, f"clusters-{snap8}.json")
    with open(clp, "w") as f:
        json.dump(cl, f, indent=2, sort_keys=True)
    paths["clusters"] = clp

    q = build_v5_queue(rows, v5, rules)
    qp = os.path.join(TRIAGE_OUT, f"queue-{snap8}.json")
    with open(qp, "w") as f:
        json.dump(q, f, indent=2, sort_keys=True)
    paths["queue"] = qp

    at = build_v5_attribution(rows, v5, rules)
    atp = os.path.join(TRIAGE_OUT, f"attribution-{snap8}.json")
    with open(atp, "w") as f:
        json.dump(at, f, indent=2, sort_keys=True)
    paths["attribution"] = atp
    return paths


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--exports", default=DEFAULT_EXPORTS)
    p.add_argument("--db", default=None)
    p.add_argument("--rules", default=DEFAULT_RULES)
    p.add_argument("--dry-run", action="store_true")
    a = p.parse_args(argv)

    with open(a.rules) as f:
        rules = json.load(f)
    assert rules["version"] in (CLASSIFIER_VERSION, V5_VERSION), \
        f"rules version {rules['version']} unsupported"

    data = load_inputs(a.exports, rules)

    if rules["version"] == V5_VERSION:
        v5 = load_v5(data, rules, a.exports)
        rows, stats = classify_v5(data, v5, rules)
        summary = summarize_v5(rows, data, v5, stats)
        print(json.dumps(summary, indent=2, sort_keys=True))
        if a.dry_run:
            print("dry-run: no DB writes, no projections")
            return
        paths = write_v5_projections(rows, summary, v5, rules)
        for k in sorted(paths):
            print(f"projection {k}: {paths[k]}")
        if a.db:
            n = write_db(a.db, rows, V5_VERSION)
            print(f"db rows: {n} -> {a.db} (classifier {V5_VERSION})")
        return

    # ---- v4 path (unchanged behavior) --------------------------------------
    assert rules["version"] == CLASSIFIER_VERSION
    rows = classify_all(data, rules)
    summary = summarize(rows, data)
    print(json.dumps(summary, indent=2, sort_keys=True))

    if a.dry_run:
        print("dry-run: no DB writes, no projections")
        return
    db = a.db or DEFAULT_DB
    n = write_db(db, rows)
    jl, sm = write_projections(rows, summary)
    print(f"db rows: {n} -> {db}")
    print(f"projections: {jl}\n             {sm}")

MODULE_FAMILY = {
    "msvcr90.dll": "CRT", "ucrtbase.dll": "CRT",
    "msvcp90.dll": "CRT", "vcruntime": "CRT",
    "kernel32.dll": "WIN32", "gdi32.dll": "WIN32", "user32.dll": "WIN32",
    "advapi32.dll": "WIN32", "winmm.dll": "WIN32", "shell32.dll": "WIN32",
    "ole32.dll": "WIN32", "oleaut32.dll": "WIN32", "uuid.dll": "WIN32",
    "setupapi.dll": "WIN32", "psapi.dll": "WIN32", "ws2_32.dll": "WIN32",
    "wininet.dll": "WIN32", "mswsock.dll": "WIN32", "wintrust.dll": "WIN32",
    "crypt32.dll": "WIN32", "winhttp.dll": "WIN32", "version.dll": "WIN32",
    "iphlpapi.dll": "WIN32", "dwmapi.dll": "WIN32", "uxtheme.dll": "WIN32",
    "shlwapi.dll": "WIN32", "wtsapi32.dll": "WIN32", "gdiplus.dll": "WIN32",
    "msimg32.dll": "WIN32", "comdlg32.dll": "WIN32", "imm32.dll": "WIN32",
    "winspool.dll": "WIN32", "netapi32.dll": "WIN32", "mpr.dll": "WIN32",
    "rpcrt4.dll": "WIN32", "nsi.dll": "WIN32", "wldap32.dll": "WIN32",
    "activeds.dll": "WIN32", "dbghelp.dll": "DEBUG",
}


def _sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        h.update(f.read())
    return h.hexdigest()


def _module_family(token):
    # token: EXT:MODULE.DLL::name
    if "::" in token:
        mod = token.split("::")[0].split(":", 1)[1].lower()
    else:
        mod = token.lower()
    return MODULE_FAMILY.get(mod, "OTHER")


def _slot_class_ns(func_name):
    """'ns::Class::Method' -> ('Class', 'ns'); ctor 'ns::Class::Class'
    handled identically; non-2+-component names -> (None, None)."""
    if not func_name or "::" not in func_name:
        return None, None
    parts = func_name.split("::")
    if len(parts) < 2:
        return None, None
    return parts[1], parts[0]


def load_v5(data, rules, exports):
    """Load the four frozen v5 inputs + derive graph/family structures.

    Returns a dict with everything classify_v5 needs. Deterministic: file
    order is committed; all iterations over sets use sorted().
    """
    xrefs_path = os.path.join(REPO, rules["v5_inputs"]["xrefs"])
    ext_path = os.path.join(REPO, rules["v5_inputs"]["externals"])
    rep_path = os.path.join(REPO, rules["v5_inputs"]["sdk_repairs"])
    queue_path = os.path.join(REPO, rules["v5_inputs"]["queue_v4"])

    # -- xref edges -----------------------------------------------------------
    edges = []
    with open(xrefs_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == ["caller_va", "callee_va", "reference_type",
                                  "callsite_va", "source",
                                  "snapshot_sha256"], rdr.fieldnames
        for r in rdr:
            edges.append(r)

    ext_tokens = {}
    with open(ext_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == ["token", "address", "name"], rdr.fieldnames
        for r in rdr:
            ext_tokens[r["token"].lower()] = r["name"]

    with open(rep_path) as f:
        repairs = json.load(f)
    with open(queue_path) as f:
        queue_v4 = json.load(f)

    fn_set = {r["va8"] for r in data["fns"]}

    # -- VA -> containing function (thunk bodies / alias targets) -------------
    fn_bounds = []
    for r in data["fns"]:
        start = int(r["va8"], 16)
        fn_bounds.append((start, start + int(r["size"]), r["va8"]))
    fn_bounds.sort()
    starts = [b[0] for b in fn_bounds]

    def containing_fn(addr_hex):
        a = int(addr_hex, 16)
        i = bisect_right(starts, a) - 1
        if i < 0:
            return None
        s, e, va = fn_bounds[i]
        return va if s <= a < e else None

    # -- per-function graph evidence ------------------------------------------
    callees = {va: set() for va in fn_set}
    callers = {va: set() for va in fn_set}
    import_fams = {va: set() for va in fn_set}
    dispatch_cands = {va: set() for va in fn_set}

    # slot absolute address -> candidate index (base + 4*i; overlapping
    # regions resolve last-wins in sorted candidate order -- metadata only)
    vt = _read_vtables(exports)
    cands = vt["candidates"]
    slot_to_cand = {}
    for ci, c in enumerate(sorted(cands, key=lambda c: norm_va(c["address"]))):
        base = int(c["address"], 16)
        for i in range(len(c.get("slots", []))):
            slot_to_cand[base + 4 * i] = ci
    cand_sorted = sorted(cands, key=lambda c: norm_va(c["address"]))

    for e in edges:
        caller = e["caller_va"]
        if caller not in fn_set:
            continue
        callee = e["callee_va"]
        if callee.startswith("EXT:"):
            import_fams[caller].add(_module_family(callee))
        elif callee.startswith("VT:"):
            ci = slot_to_cand.get(int(callee[3:], 16))
            if ci is not None:
                dispatch_cands[caller].add(norm_va(cand_sorted[ci]["address"]))
        elif callee in fn_set or (containing_fn(callee) is not None):
            tgt = callee if callee in fn_set else containing_fn(callee)
            callees[caller].add(tgt)
            callers[tgt].add(caller)

    # -- strongly-connected components (iterative Tarjan) ---------------------
    adj = {va: sorted(s) for va, s in callees.items() if s}
    scc_size = {va: 1 for va in fn_set}
    for members in _tarjan(adj, sorted(fn_set)):
        if len(members) > 1:
            for m in members:
                scc_size[m] = len(members)

    # -- vtable families (union-find over pair-clusters + inheritance chains) -
    class_count = {}   # ci -> Counter class -> count
    class_ns = {}      # ci -> class -> Counter ns -> count
    cand_sdk_funcs = {}  # ci -> set of distinct sdk slot func names
    for ci, c in enumerate(cand_sorted):
        cc = {}
        cns = {}
        fns = set()
        for slot in c.get("slots", []):
            if slot.get("funcStart") and slot.get("func") and slot.get("sdk"):
                cls, ns = _slot_class_ns(slot["func"])
                fns.add(slot["func"])
                if cls:
                    cc[cls] = cc.get(cls, 0) + 1
                    cns.setdefault(cls, {})
                    cns[cls][ns] = cns[cls].get(ns, 0) + 1
        class_count[ci] = cc
        class_ns[ci] = cns
        cand_sdk_funcs[ci] = fns

    parent = list(range(len(cand_sorted)))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[max(ra, rb)] = min(ra, rb)

    ci_by_addr = {norm_va(c["address"]): i
                  for i, c in enumerate(cand_sorted)}

    def ci_of(addr):
        return ci_by_addr.get(norm_va(addr))

    for pair in vt.get("clusters", []):
        ia, ib = ci_of(pair.get("a")), ci_of(pair.get("b"))
        if ia is not None and ib is not None:
            union(ia, ib)
    for ch in vt.get("inheritance_chains", []):
        ia, ib = ci_of(ch.get("base")), ci_of(ch.get("derived"))
        if ia is not None and ib is not None:
            union(ia, ib)

    comp_agg = {}  # root -> Counter class counts
    comp_fns = {}  # root -> set distinct sdk funcs
    for ci in range(len(cand_sorted)):
        root = find(ci)
        comp_agg.setdefault(root, {})
        for cls, n in class_count[ci].items():
            comp_agg[root][cls] = comp_agg[root].get(cls, 0) + n
        comp_fns.setdefault(root, set())
        comp_fns[root] |= cand_sdk_funcs[ci]

    def comp_label(root):
        agg = comp_agg.get(root, {})
        if not agg:
            return None, None
        best = min(agg.items(), key=lambda kv: (-kv[1], kv[0]))
        cls = best[0]
        ns_counts = {}
        for ci in range(len(cand_sorted)):
            if find(ci) == root:
                for ns, n in class_ns[ci].get(cls, {}).items():
                    ns_counts[ns] = ns_counts.get(ns, 0) + n
        ns = min(ns_counts.items(), key=lambda kv: (-kv[1], kv[0]))[0] \
            if ns_counts else None
        return cls, ns

    cand_label = {}  # ci -> (class, ns, distinct_sdk_funcs, via)
    for ci, c in enumerate(cand_sorted):
        cls, ns = comp_label(find(ci))
        via = "direct" if class_count[ci] else None
        if not class_count[ci] and cls:
            via = "chain|pair"
        cand_label[ci] = (cls, ns, len(cand_sdk_funcs[ci]), via)

    # candidate address (bare va8) -> ci (for dispatch metadata + family)
    addr_to_ci = ci_by_addr
    func_family = {}  # func va8 -> {class, ns, distinct_sdk_funcs, via, cands}
    for va, caddrs in data["func_to_vt"].items():
        best = None
        for ca in sorted(caddrs):
            ci = addr_to_ci.get(ca.lower())
            if ci is None:
                continue
            cls, ns, k, via = cand_label[ci]
            if not cls:
                continue
            if best is None or k > best[2]:
                best = (cls, ns, k, via, ca)
        if best:
            func_family[va] = {
                "class": best[0], "ns": best[1],
                "distinct_sdk_funcs": best[2], "via": best[3],
                "candidate": best[4],
            }

    # -- SDK contained-alias policy -------------------------------------------
    # Names aggregate per repaired target ACROSS all qualifying records
    # (88 targets carry >=2 distinct SDK slot names). Policy: majority
    # top-namespace (tie: lexicographically smallest namespace), then
    # lexicographically smallest full name inside the winning namespace.
    applied_verdicts = set(rules["v5_alias_policy"]["verdicts_applied"])
    sdk5 = dict(data["sdk"])
    aliases = {va: [] for va in fn_set}
    names_per_target = {}
    applied_records = 0
    skipped_non_fn = 0
    for rec in repairs.get("records", []):
        if rec.get("verdict") not in applied_verdicts:
            continue
        applied_records += 1
        target = rec.get("repaired_va")
        if not target or norm_va(target) not in fn_set:
            skipped_non_fn += 1
            continue
        t = norm_va(target)
        for n in rec.get("sdk_names", []):
            if n:
                names_per_target.setdefault(t, set()).add(n)
    alias_stats = {"applied_records": applied_records, "redundant": 0,
                   "assigned": 0, "multi_name_targets": 0,
                   "skipped_non_fn": skipped_non_fn}
    for t in sorted(names_per_target):
        names = sorted(names_per_target[t])
        canonical = data["sdk"].get(t)
        if canonical:
            alias_stats["redundant"] += 1
            others = [n for n in names if n != canonical]
            if others:
                aliases[t] = sorted(others)
            continue
        if len(names) >= 2:
            alias_stats["multi_name_targets"] += 1
        by_ns = {}
        for n in names:
            by_ns.setdefault(top_ns(n) or n, []).append(n)
        winner_ns = min(by_ns.items(),
                        key=lambda kv: (-len(kv[1]), kv[0]))[0]
        winner = min(by_ns[winner_ns])
        sdk5[t] = winner
        aliases[t] = sorted(n for n in names if n != winner)
        alias_stats["assigned"] += 1

    # -- v5 snapshot hash ------------------------------------------------------
    h = hashlib.sha256()
    h.update(data["snapshot"].encode())          # v4 core input hash
    for pth in (xrefs_path, ext_path, rep_path, queue_path):
        h.update(_sha256_file(pth).encode())
    h.update("\n".join(sorted(fn_set)).encode())  # closure anchor
    snap = h.hexdigest()

    # -- dispatch caller counts per candidate (metadata only) ------------------
    cand_callers = {ca: set() for ca in addr_to_ci}
    for va, caddrs in dispatch_cands.items():
        for ca in caddrs:
            cand_callers[ca].add(va)

    return {
        "edges": edges, "ext_tokens": ext_tokens, "repairs": repairs,
        "queue_v4": queue_v4, "callees": callees, "callers": callers,
        "import_fams": import_fams, "scc_size": scc_size,
        "func_family": func_family, "cand_label": cand_label,
        "addr_to_ci": addr_to_ci, "cand_sorted": cand_sorted,
        "cand_callers": cand_callers, "cand_sdk_funcs": cand_sdk_funcs,
        "sdk5": sdk5, "aliases": aliases, "alias_stats": alias_stats,
        "snapshot": snap, "snap8": snap[:8],
    }


def _read_vtables(exports):
    with open(os.path.join(exports, "vtables.json")) as f:
        return json.load(f)


def _tarjan(adj, nodes):
    """Iterative Tarjan SCC. adj: node -> sorted successors."""
    idx, low, onstack = {}, {}, {}
    stack, comps, counter = [], [], 0
    for start in nodes:
        if start in idx:
            continue
        idx[start] = low[start] = counter
        counter += 1
        stack.append(start)
        onstack[start] = True
        work = [(start, iter(adj.get(start, ())))]
        while work:
            node, it = work[-1]
            advanced = False
            for nxt in it:
                if nxt not in idx:
                    idx[nxt] = low[nxt] = counter
                    counter += 1
                    stack.append(nxt)
                    onstack[nxt] = True
                    work.append((nxt, iter(adj.get(nxt, ()))))
                    advanced = True
                    break
                if onstack.get(nxt):
                    low[node] = min(low[node], idx[nxt])
            if advanced:
                continue
            work.pop()
            if work:
                par = work[-1][0]
                low[par] = min(low[par], low[node])
            if low[node] == idx[node]:
                members = []
                while True:
                    w = stack.pop()
                    onstack[w] = False
                    members.append(w)
                    if w == node:
                        break
                comps.append(members)
    return comps


if __name__ == "__main__":
    main()
