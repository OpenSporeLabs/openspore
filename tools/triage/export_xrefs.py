#!/usr/bin/env python3
"""Canonicalize, validate, and ingest the Ghidra xref export (stdlib only).

Pipeline:
  1. Raw edge TSV from tools/ghidra/ExportXrefs.java (via Ghidra MCP
     run_script_inline; see knowledgegraph/triage/xrefs-<snap8>.summary.json
     > provenance > method for the exact rerun recipe).
  2. This script sorts (caller_va, callee_va, callsite_va), dedupes exact
     triples, validates closure against the pinned 58757-VA universe plus the
     externals/vtable allowlists, and writes the canonical files:
       knowledgegraph/triage/xrefs-<snap8>.tsv
       knowledgegraph/triage/xrefs-<snap8>.externals.tsv
       knowledgegraph/triage/xrefs-<snap8>.summary.json
  3. --ingest loads edges into spore.db (xref table) and refreshes
     triage.caller_count / triage.callee_count, with integrity checks.

Canonical key: VA8 = 8-char lowercase hex, no prefix (same as classify.py).
EXT tokens:  "EXT:<library>::<name>"  (external/import dests).
VT tokens:   "VT:<va8>"               (known vtable base from vtables.json).

caller_count / callee_count semantics: distinct endpoints over CALL-type
edges only (direct-call, thunk, external, computed-call). data-ref and
vtable-ref rows are kept in the xref table + TSV but do NOT feed the counts.

Determinism: sorted I/O, fixed JSON separators/sort_keys, no wall-clock in
the TSV (generated_at lives only in the summary JSON, excluded from hashes).

Usage:
  export_xrefs.py --edges RAW.tsv --externals RAW.ext.tsv [--ingest]
                  [--exports DIR] [--out DIR] [--db PATH]
                  [--live-functions N] [--missing N] [--script-errors N]
                  [--dry-run]
"""

import argparse
import csv
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

BINARY_SHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
SOURCE_LABEL = "ghidra:SporeApp.exe"
CALL_TYPES = ("direct-call", "thunk", "external", "computed-call")
ALL_TYPES = CALL_TYPES + ("vtable-ref", "data-ref")

HEX8 = re.compile(r"^[0-9a-f]{8}$")
EDGE_HEADER = ["caller_va", "callee_va", "reference_type", "callsite_va",
               "source", "snapshot_sha256"]
EXT_HEADER = ["token", "address", "name"]


def norm_va(s):
    s = (s or "").strip().lower()
    if s.startswith("0x"):
        s = s[2:]
    v = s.zfill(8)[-8:]
    if not HEX8.match(v):
        raise ValueError("not a hex VA: %r" % (s,))
    return v


def input_snapshot(exports):
    h = hashlib.sha256()
    for name in ("functions.tsv", "sdk_functions.tsv", "structs.tsv",
                 "structs_fields.tsv", "vtables.json"):
        with open(os.path.join(exports, name), "rb") as f:
            h.update(f.read())
    dec_names = sorted(os.path.basename(p) for p in glob.glob(
        os.path.join(exports, "decompiled_sdk", "*.c")))
    h.update("\n".join(dec_names).encode())
    return h.hexdigest()


def load_universe(exports):
    pinned = set()
    with open(os.path.join(exports, "functions.tsv"), newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == ["address", "name", "size", "is_thunk",
                                  "is_external", "section"]
        for row in rdr:
            pinned.add(norm_va(row["address"]))
    assert len(pinned) == 58757, "pinned universe: %d != 58757" % len(pinned)
    with open(os.path.join(exports, "vtables.json")) as f:
        vt = json.load(f)
    vtable_bases = set()
    for cand in vt["candidates"]:
        vtable_bases.add(norm_va(cand["address"]))
    return pinned, vtable_bases


def load_raw(edges_path, externals_path, snapshot):
    with open(edges_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == EDGE_HEADER, rdr.fieldnames
        rows = list(rdr)
    with open(externals_path, newline="") as f:
        rdr = csv.DictReader(f, delimiter="\t")
        assert rdr.fieldnames == EXT_HEADER, rdr.fieldnames
        exts = list(rdr)
    for r in rows:
        assert r["snapshot_sha256"] == snapshot, "row snapshot mismatch"
        assert r["source"] == SOURCE_LABEL, "row source mismatch"
    return rows, exts


def canonicalize(rows, exts, pinned, vtable_bases):
    ext_tokens = set()
    for e in exts:
        assert e["token"].startswith("EXT:"), e["token"]
        ext_tokens.add(e["token"])
    raw_n = len(rows)
    for r in rows:
        for col in ("caller_va", "callsite_va"):
            assert HEX8.match(r[col]), (col, r[col])
        assert r["reference_type"] in ALL_TYPES, r["reference_type"]
        assert r["caller_va"] in pinned, "caller outside pinned set"
        c = r["callee_va"]
        if c.startswith("EXT:"):
            assert c in ext_tokens, "callee EXT token not in allowlist"
        elif c.startswith("VT:"):
            assert norm_va(c[3:]) in vtable_bases, "VT base not allowlisted"
        else:
            assert HEX8.match(c), ("callee_va", c)
            assert c in pinned, "callee outside pinned set"
    seen = set()
    uniq = []
    dupes = 0
    for r in rows:
        k = (r["caller_va"], r["callee_va"], r["callsite_va"])
        if k in seen:
            dupes += 1
            continue
        seen.add(k)
        uniq.append(r)
    uniq.sort(key=lambda r: (r["caller_va"], r["callee_va"],
                             r["callsite_va"]))
    exts_sorted = sorted(exts, key=lambda e: e["token"])
    assert len({e["token"] for e in exts_sorted}) == len(exts_sorted), \
        "duplicate EXT tokens"
    return uniq, exts_sorted, raw_n, dupes


def coverage(rows, pinned):
    call_rows = [r for r in rows if r["reference_type"] in CALL_TYPES]
    # distinct endpoints per VA (call-type edges only)
    in_set = {}
    out_set = {}
    for r in call_rows:
        if HEX8.match(r["callee_va"]):
            in_set.setdefault(r["callee_va"], set()).add(r["caller_va"])
        out_set.setdefault(r["caller_va"], set()).add(r["callee_va"])
    with_caller = sum(1 for va in pinned if va in in_set)
    with_callee = sum(1 for va in pinned if va in out_set)
    return {
        "functions": len(pinned),
        "with_caller": with_caller,
        "with_callee": with_callee,
        "pct_with_caller": round(100.0 * with_caller / len(pinned), 2),
        "pct_with_callee": round(100.0 * with_callee / len(pinned), 2),
    }, in_set, out_set


def write_canonical(rows, exts, out_dir, snap8):
    os.makedirs(out_dir, exist_ok=True)
    tsv = os.path.join(out_dir, "xrefs-%s.tsv" % snap8)
    ext = os.path.join(out_dir, "xrefs-%s.externals.tsv" % snap8)
    with open(tsv, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=EDGE_HEADER, delimiter="\t",
                           lineterminator="\n")
        w.writeheader()
        w.writerows(rows)
    with open(ext, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=EXT_HEADER, delimiter="\t",
                           lineterminator="\n")
        w.writeheader()
        w.writerows(exts)
    h = hashlib.sha256()
    with open(tsv, "rb") as f:
        h.update(f.read())
    return tsv, ext, h.hexdigest()


def ingest(db_path, rows, in_set, out_set, snapshot, zero_fill=False):
    sys.path.insert(0, KG_DIR)
    import kg  # noqa: E402 schema migration, same pattern as seed.py
    c = sqlite3.connect(db_path)
    kg._migrate(c)
    cols = [r[1] for r in c.execute("PRAGMA table_info(xref)")]
    assert cols == ["caller_va", "callee_va", "reference_type",
                    "callsite_va", "source", "snapshot_sha256"], cols
    with c:
        c.executemany(
            "INSERT OR IGNORE INTO xref(caller_va,callee_va,reference_type,"
            "callsite_va,source,snapshot_sha256) VALUES(?,?,?,?,?,?)",
            [(r["caller_va"], r["callee_va"], r["reference_type"],
              r["callsite_va"], r["source"], r["snapshot_sha256"])
             for r in rows])
        n_xref = c.execute("SELECT COUNT(*) FROM xref").fetchone()[0]
        assert n_xref == len(rows), "xref %d != tsv %d" % (n_xref, len(rows))
        # integrity: every pinned endpoint resolves to a triage row
        n_triage = c.execute("SELECT COUNT(*) FROM triage").fetchone()[0]
        assert n_triage == 58757, "triage has %d rows" % n_triage
        orphans = c.execute(
            "SELECT COUNT(*) FROM (SELECT caller_va AS va FROM xref "
            "UNION SELECT callee_va FROM xref "
            "WHERE callee_va NOT LIKE 'EXT:%' AND callee_va NOT LIKE 'VT:%') "
            "AS eps LEFT JOIN triage ON triage.va = eps.va "
            "WHERE triage.va IS NULL"
        ).fetchone()[0]
        assert orphans == 0, "%d xref endpoints without triage row" % orphans
        updates = 0
        for va in {r["caller_va"] for r in rows} | {
                r["callee_va"] for r in rows if HEX8.match(r["callee_va"])}:
            cur = c.execute(
                "UPDATE triage SET caller_count=?, callee_count=? WHERE va=?",
                (len(in_set.get(va, ())), len(out_set.get(va, ())), va))
            updates += cur.rowcount
        nulls = c.execute(
            "SELECT COUNT(*) FROM triage WHERE caller_count IS NULL").fetchone()[0]
        zero_filled = 0
        if zero_fill:
            # Full-universe scan (every pinned VA resolved to a live function
            # entry): NULL would lie, 0 is observed. Only safe when the
            # exporter saw all pinned functions (missing == 0).
            cur = c.execute(
                "UPDATE triage SET caller_count=0 WHERE caller_count IS NULL")
            zero_filled += cur.rowcount
            cur = c.execute(
                "UPDATE triage SET callee_count=0 WHERE callee_count IS NULL")
            zero_filled += cur.rowcount
            nulls = c.execute(
                "SELECT COUNT(*) FROM triage WHERE caller_count IS NULL"
            ).fetchone()[0]
    c.close()
    return {"xref_rows": n_xref, "triage_rows": n_triage,
            "triage_updated": updates, "triage_nulls_remaining": nulls,
            "zero_filled_cells": zero_filled}


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--edges", required=True)
    p.add_argument("--externals", required=True)
    p.add_argument("--exports", default=DEFAULT_EXPORTS)
    p.add_argument("--out", default=TRIAGE_OUT)
    p.add_argument("--db", default=DEFAULT_DB)
    p.add_argument("--live-functions", type=int, default=None)
    p.add_argument("--missing", type=int, default=None)
    p.add_argument("--script-errors", type=int, default=None)
    p.add_argument("--ingest", action="store_true")
    p.add_argument("--dry-run", action="store_true")
    a = p.parse_args(argv)

    snapshot = input_snapshot(a.exports)
    snap8 = snapshot[:8]
    pinned, vtable_bases = load_universe(a.exports)
    rows, exts = load_raw(a.edges, a.externals, snapshot)
    uniq, exts_sorted, raw_n, dupes = canonicalize(rows, exts, pinned,
                                                   vtable_bases)
    cov, in_set, out_set = coverage(uniq, pinned)
    from collections import Counter
    by_type = dict(sorted(Counter(r["reference_type"]
                                  for r in uniq).items()))

    if a.dry_run:
        print(json.dumps({"dry_run": True, "raw": raw_n, "unique": len(uniq),
                          "dupes": dupes, "by_type": by_type,
                          "coverage": cov,
                          "externals": len(exts_sorted)}, indent=2,
                         sort_keys=True))
        return

    tsv, ext_path, sha = write_canonical(uniq, exts_sorted, a.out, snap8)
    summary = {
        "artifact": "xref-export",
        "snapshot_sha256": snapshot,
        "snap8": snap8,
        "binary_sha256": BINARY_SHA,
        "source": SOURCE_LABEL,
        "files": {
            "edges": os.path.relpath(tsv, REPO),
            "externals": os.path.relpath(ext_path, REPO),
            "sha256_edges_tsv": sha,
        },
        "raw_rows": raw_n,
        "unique_rows": len(uniq),
        "duplicate_triples_removed": dupes,
        "by_reference_type": by_type,
        "externals_count": len(exts_sorted),
        "coverage": cov,
        "closure": {
            "pinned_universe": len(pinned),
            "callers_all_pinned": True,
            "callees_pinned_or_allowlisted": True,
            "vtable_allowlist": len(vtable_bases),
        },
        "provenance": {
            "method": "tools/ghidra/ExportXrefs.java via Ghidra MCP "
                      "run_script_inline on SporeApp.exe (analyzed, no "
                      "re-analysis); params file /tmp/opencode/xref-job/ "
                      "params.tsv with shard=0 shards=1; canonicalized with "
                      "tools/triage/export_xrefs.py (sort+uniq).",
            "live_functions": a.live_functions,
            "pinned_missing_at_address": a.missing,
            "script_errors": a.script_errors,
            "generated_at_note": "generated_at excluded from all hashes; "
                                 "sha256 covers the edges TSV bytes only.",
        },
    }
    if a.ingest:
        rep = ingest(a.db, uniq, in_set, out_set, snapshot,
                     zero_fill=(a.missing == 0))
        summary["ingest"] = rep
        print(json.dumps(rep, indent=2, sort_keys=True))
    sm = os.path.join(a.out, "xrefs-%s.summary.json" % snap8)
    with open(sm, "w") as f:
        json.dump(summary, f, indent=2, sort_keys=True)
    print(json.dumps(summary, indent=2, sort_keys=True))
    print("wrote: %s\n       %s\n       %s" % (tsv, ext_path, sm))


if __name__ == "__main__":
    main()
