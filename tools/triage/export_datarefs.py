#!/usr/bin/env python3
"""Canonicalize, validate, and commit the Ghidra data-reference sidecar.

Companion to ``export_xrefs.py``: same exporter, same run, same snapshot, same
provenance -- a separate file because the edge export's closure assertion (every
non-EXT/non-VT endpoint is a member of the pinned function universe) is a real
check on real data, and a global address is by construction not a member of it.
Folding these rows into the edge TSV would mean weakening a check that currently
catches corruption, to carry evidence that needs no such check.

Pipeline:
  1. Raw sidecar TSV from tools/ghidra/ExportXrefs.java (optional 8th param
     ``outData``).
  2. This script validates every row against the pinned universe, the frozen
     snapshot, and the segment vocabulary; dedupes exact rows; sorts; and writes
        knowledgegraph/triage/datarefs-<snap8>.tsv
        knowledgegraph/triage/datarefs-<snap8>.summary.json
  3. The summary is what downstream consumers read for the counts, the segment
     vocabulary actually observed, and the provenance.

Canonical key: (caller_va, target_va, access_mode, segment, callsite_va). The
dedupe is on the FULL key, not on (caller, target, callsite) as in the edge file,
because a read and a write of the same address from the same instruction are two
different facts about the body and collapsing them would lose one. Ghidra does
hold genuinely duplicated Reference objects (measured: 7 such rows in the
canonical image, e.g. two identical ``[READ]`` objects to 0x015b0e48 at
0x00f699b0), and those collapse because every field of the key matches.

Address width: x86-32. A target is accepted only as exactly 8 lowercase hex
digits, or it is refused. That is not a formatting preference -- it is the check
that a 64-bit or truncated address cannot enter the file and later be read as an
x86 global.

Usage:
  export_datarefs.py --data RAW.tsv [--out DIR] [--exports DIR]
                     [--exports-live N] [--dry-run]
"""

import argparse
import csv
import hashlib
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
TRIAGE_OUT = os.path.join(REPO, "knowledgegraph", "triage")
DEFAULT_EXPORTS = os.path.join(REPO, ".spore-analysis", "ghidra-exports")

BINARY_SHA = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"
SOURCE_LABEL = "ghidra:SporeApp.exe"

DATA_HEADER = ["caller_va", "target_va", "access_mode", "segment",
               "callsite_va", "source", "snapshot_sha256"]
# Exactly 8 lowercase hex digits. Uppercase is refused rather than folded: a
# canonical artifact whose keys sort differently under two spellings of the same
# address is a file that can disagree with itself.
HEX8 = re.compile(r"^[0-9a-f]{8}$")
ACCESS_MODES = ("read", "write", "readwrite", "other")

# Ghidra writes "<block> <perms>", perms being three characters from xwr in that
# order, '-' for absent. The block name itself is free-form (".data", "tdb",
# "CONST"), so it is not enumerated here: an unknown block name is data, not an
# error, because the name is Ghidra's own label for the address and refusing it
# would drop real evidence on a future re-import.
SEGMENT = re.compile(r"^(?P<block>\S+) (?P<perms>[x-][w-][r-])$")


def norm_va(value):
    """``value`` as a canonical 8-lowercase-hex VA, or raise.

    Deliberately strict and deliberately not tolerant of a ``0x`` prefix: the
    exporter emits bare 8-digit VA8, so a prefix means the row came from
    somewhere else, and accepting it would let two spellings of one address into
    the same artifact.
    """
    text = (value or "").strip()
    if not HEX8.match(text):
        raise ValueError("not a canonical x86-32 VA8: %r" % (value,))
    return text


def input_snapshot(exports):
    """The frozen input hash, computed exactly as ``export_xrefs.py`` does.

    Restated rather than imported so this script stands alone, but it must agree
    byte for byte: it is what makes the sidecar's provenance the same statement
    as the edge file's, and a disagreement here would mean the two artifacts
    claim to describe different binaries.
    """
    digest = hashlib.sha256()
    for name in ("functions.tsv", "sdk_functions.tsv", "structs.tsv",
                 "structs_fields.tsv", "vtables.json"):
        with open(os.path.join(exports, name), "rb") as handle:
            digest.update(handle.read())
    import glob
    decoded = sorted(os.path.basename(p) for p in glob.glob(
        os.path.join(exports, "decompiled_sdk", "*.c")))
    digest.update("\n".join(decoded).encode())
    return digest.hexdigest()


def load_universe(exports):
    """The pinned function-entry set, from the same file the edge export uses."""
    pinned = set()
    with open(os.path.join(exports, "functions.tsv"), newline="") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        if reader.fieldnames != ["address", "name", "size", "is_thunk",
                                 "is_external", "section"]:
            raise SystemExit("functions.tsv has columns %s, which is not the "
                             "frozen universe this reads" % (reader.fieldnames,))
        for row in reader:
            address = (row["address"] or "").strip().lower()
            if address.startswith("0x"):
                address = address[2:]
            pinned.add(address.zfill(8)[-8:])
    return pinned


def load_raw(path, snapshot):
    with open(path, newline="") as handle:
        reader = csv.DictReader(handle, delimiter="\t")
        if reader.fieldnames != DATA_HEADER:
            raise SystemExit(
                "sidecar declares columns %s, not %s, so it is not the artifact "
                "this canonicalizer reads" % (reader.fieldnames, DATA_HEADER))
        rows = list(reader)
    for row in rows:
        if row["snapshot_sha256"] != snapshot:
            raise SystemExit("row snapshot mismatch: %r" % (row["snapshot_sha256"],))
        if row["source"] != SOURCE_LABEL:
            raise SystemExit("row source mismatch: %r" % (row["source"],))
    return rows


def canonicalize(rows, pinned):
    """Validate every row, dedupe on the full key, and sort deterministically.

    The per-row checks are the whole safety argument for this file, so each one
    refuses rather than repairs:

    * caller and callsite must be canonical VA8, and the caller must be in the
      pinned universe -- the caller is the function whose body made the
      reference, so a row naming a caller that is not a function entry has no
      body to be evidence about.
    * the target must be canonical VA8. This is the x86-32 width check: a 16-digit
      or 4-digit target is refused, never truncated, because truncation would
      turn an unrepresentable address into a plausible-looking global.
    * access_mode must be in the vocabulary the exporter writes.
    * segment must parse as "<block> <perms>" with perms from xwr.

    A row whose target happens to equal a function entry is NOT refused here. The
    exporter is what separates those (it never emits a function-entry target),
    and a consumer that trusts this file must be able to tell a data address from
    a code address by asking about the segment, not by the coincidence of the
    number. The refusal lives where the fact is, and the tests pin it.
    """
    for row in rows:
        caller = norm_va(row["caller_va"])
        if caller not in pinned:
            raise SystemExit("caller outside pinned universe: %s" % (caller,))
        norm_va(row["callsite_va"])
        norm_va(row["target_va"])
        if row["access_mode"] not in ACCESS_MODES:
            raise SystemExit("unknown access_mode: %r" % (row["access_mode"],))
        if not SEGMENT.match(row["segment"] or ""):
            raise SystemExit("unparseable segment: %r" % (row["segment"],))
    seen = set()
    unique = []
    duplicates = 0
    for row in rows:
        key = (row["caller_va"], row["target_va"], row["access_mode"],
               row["segment"], row["callsite_va"])
        if key in seen:
            duplicates += 1
            continue
        seen.add(key)
        unique.append(row)
    unique.sort(key=lambda r: (r["caller_va"], r["target_va"], r["access_mode"],
                               r["segment"], r["callsite_va"]))
    return unique, len(rows), duplicates


def coverage(rows):
    """The population facts a reader needs before trusting a single row."""
    by_mode = {}
    by_segment = {}
    for row in rows:
        by_mode[row["access_mode"]] = by_mode.get(row["access_mode"], 0) + 1
        by_segment[row["segment"]] = by_segment.get(row["segment"], 0) + 1
    callers = set()
    targets = set()
    for row in rows:
        callers.add(row["caller_va"])
        targets.add(row["target_va"])
    return {
        "rows": len(rows),
        "distinct_callers": len(callers),
        "distinct_targets": len(targets),
        "by_access_mode": dict(sorted(by_mode.items())),
        "by_segment": dict(sorted(by_segment.items())),
    }


def write_canonical(rows, out_dir, snap8):
    os.makedirs(out_dir, exist_ok=True)
    path = os.path.join(out_dir, "datarefs-%s.tsv" % snap8)
    with open(path, "w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=DATA_HEADER, delimiter="\t",
                                lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        digest.update(handle.read())
    return path, digest.hexdigest()


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--data", required=True)
    parser.add_argument("--exports", default=DEFAULT_EXPORTS)
    parser.add_argument("--out", default=TRIAGE_OUT)
    parser.add_argument("--exports-live", type=int, default=None)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args(argv)

    snapshot = input_snapshot(args.exports)
    snap8 = snapshot[:8]
    pinned = load_universe(args.exports)
    rows = load_raw(args.data, snapshot)
    unique, raw_count, duplicates = canonicalize(rows, pinned)
    stats = coverage(unique)

    if args.dry_run:
        print(json.dumps({"dry_run": True, "raw": raw_count,
                          "unique": len(unique),
                          "duplicate_rows_removed": duplicates,
                          "coverage": stats}, indent=2, sort_keys=True))
        return

    path, sha = write_canonical(unique, args.out, snap8)
    summary = {
        "artifact": "dataref-export",
        "snapshot_sha256": snapshot,
        "snap8": snap8,
        "binary_sha256": BINARY_SHA,
        "source": SOURCE_LABEL,
        "files": {
            "datarefs": os.path.relpath(path, REPO),
            "sha256_datarefs_tsv": sha,
        },
        "columns": DATA_HEADER,
        "access_modes": list(ACCESS_MODES),
        "raw_rows": raw_count,
        "unique_rows": len(unique),
        "duplicate_rows_removed": duplicates,
        "coverage": stats,
        "excluded_by_design": {
            "stack_space_references": (
                "a reference into Ghidra's stack address space is a frame slot, "
                "not a global; measured 573,206 of 731,045 discarded references "
                "on the canonical image, so emitting them would make this file a "
                "statement about stack frames"),
            "unbacked_addresses": (
                "an address no memory block backs is unmapped; Ghidra records "
                "the reference but there is no storage to name (measured 199)"),
            "function_entries": "already a data-ref row in the edge export",
            "vtable_slots": "already a vtable-ref row in the edge export",
            "external_addresses": "an import thunk has no storage in this image",
        },
        "provenance": {
            "method": "tools/ghidra/ExportXrefs.java optional 8th param outData, "
                      "via Ghidra MCP run_ghidra_script on SporeApp.exe "
                      "(analyzed, no re-analysis); canonicalized with "
                      "tools/triage/export_datarefs.py.",
            "companion_artifact": "knowledgegraph/triage/xrefs-2540f2ca.tsv",
            "live_functions": args.exports_live,
            "generated_at_note": "no wall-clock in the TSV; sha256 covers the "
                                 "TSV bytes only.",
        },
    }
    summary_path = os.path.join(args.out, "datarefs-%s.summary.json" % snap8)
    with open(summary_path, "w") as handle:
        json.dump(summary, handle, indent=2, sort_keys=True)
    print(json.dumps(summary, indent=2, sort_keys=True))
    print("wrote: %s\n       %s" % (path, summary_path))


if __name__ == "__main__":
    main()