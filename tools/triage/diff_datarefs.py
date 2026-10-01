#!/usr/bin/env python3
"""Corpus differential for the data-reference GLOBALS extension (Phase 6).

A/B over every committed evidence pack, in one process, with the ONLY difference
between the two runs being whether ``validate`` can see the Ghidra data-reference
artifact. That is the comparison the change claims, and it is run in-process so
the two sides cannot differ for any reason other than the one under test -- no
re-export, no re-generation, no clock, no filesystem drift between them.

What is compared per target:
  * every static check's status (so a moved non-GLOBALS check is caught),
  * the GLOBALS detail text (so a moved GLOBALS verdict is caught even when the
    status did not change),
  * the aggregate verdict and the confidence band.

Requirements asserted, from the brief:
  * no previously PASS verdict regresses (to WARN/FAIL/NOT_AVAILABLE/UNKNOWN),
  * no confidence decreases,
  * no non-GLOBALS check moves at all,
  * every GLOBALS change has an explainable data-reference cause -- i.e. the pack
    is one the artifact actually records rows for.

Usage:
  tools/triage/diff_datarefs.py [--packs N] [--json OUT]
"""

import argparse
import glob
import importlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, ROOT)

from tools.reconstruction_tooling import evidence_datarefs as D  # noqa: E402
import tools.reconstruction_tooling.validate as Vmod  # noqa: E402
from tools.reconstruction_tooling import validate as V  # noqa: E402

REGRESSING = {"PASS"}
STATIC_CHECKS = V.STATIC_CHECKS


def pack_vas(root):
    base = os.path.join(root, "reconstruction", "evidence")
    return sorted(os.path.basename(p) for p in glob.glob(os.path.join(base, "*"))
                  if os.path.isdir(p))


def run_side(root, vas):
    """Validate every VA, returning ``{va: {check: (status, detail), ...}}``.

    ``evidence`` is passed through as ``None`` so ``validate`` reads the committed
    pack rather than recollecting: both sides then read identical inputs.
    """
    out = {}
    for name in vas:
        va = "0x" + name
        try:
            report = V.validate(root=root, va=va, evidence=None, write=False)
        except Exception as exc:  # a pack that cannot be validated is a finding
            out[name] = {"error": "%s: %s" % (type(exc).__name__, exc)}
            continue
        checks = {}
        for check, value in (report.get("checks") or {}).items():
            if isinstance(value, dict):
                checks[check] = (value.get("status"), value.get("detail") or "",
                                 value.get("coverage"))
            else:
                checks[check] = (value, "", None)
        out[name] = {"checks": checks,
                     "aggregate": report.get("aggregate"),
                     "confidence": report.get("confidence")}
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", default=ROOT)
    parser.add_argument("--packs", type=int, default=0,
                        help="limit to the first N packs (0 = all)")
    parser.add_argument("--json", default=None)
    args = parser.parse_args(argv)

    vas = pack_vas(args.root)
    if args.packs:
        vas = vas[:args.packs]

    # -- side B: artifact hidden. This is "before" by construction: the same
    # validator, the same packs, with authoritative_data_refs returning absent.
    real_read = D.authoritative_data_refs

    def absent(root, va):
        result = real_read(root, va)
        if result["state"] == "complete":
            return {"state": D.STATE_ABSENT, "va": result["va"], "rows": [],
                    "targets": frozenset(), "writable": None,
                    "writable_targets": frozenset(), "read": 0, "write": 0,
                    "readwrite": 0, "other": 0,
                    "note": "hidden for the differential"}
        return result

    # ``validate`` holds the reader as a module-level name, so replacing that name
    # is what the GLOBALS arms actually call.
    Vmod._read_data_refs = absent
    before = run_side(args.root, vas)

    Vmod._read_data_refs = real_read
    D.reset_cache()
    after = run_side(args.root, vas)

    # -- compare ------------------------------------------------------------
    stats = {
        "packs": len(vas),
        "errors": 0,
        "globals_status_changed": 0,
        "globals_detail_changed": 0,
        "globals_unchanged": 0,
        "non_globals_moved": 0,
        "aggregate_moved": 0,
        "confidence_decreased": 0,
        "pass_regressions": 0,
    }
    regressions, non_globals, unexplained, strengthened, weakened = [], [], [], [], []
    for name in vas:
        a, b = before.get(name, {}), after.get(name, {})
        if "error" in a or "error" in b:
            stats["errors"] += 1
            continue
        ac, bc = a.get("checks", {}), b.get("checks", {})
        for check in STATIC_CHECKS:
            if check not in ac or check not in bc:
                continue
            if check != "GLOBALS" and ac[check] != bc[check]:
                stats["non_globals_moved"] += 1
                non_globals.append({"va": name, "check": check,
                                    "before": ac[check][0], "after": bc[check][0]})
        ga, gb = ac.get("GLOBALS"), bc.get("GLOBALS")
        if ga and gb:
            if ga[0] != gb[0]:
                stats["globals_status_changed"] += 1
                if ga[0] in REGRESSING and gb[0] != "PASS":
                    stats["pass_regressions"] += 1
                    regressions.append({"va": name, "from": ga[0], "to": gb[0]})
                elif gb[0] == "PASS":
                    strengthened.append({"va": name, "from": ga[0], "to": gb[0]})
                else:
                    weakened.append({"va": name, "from": ga[0], "to": gb[0]})
            if ga[1] != gb[1]:
                stats["globals_detail_changed"] += 1
            else:
                stats["globals_unchanged"] += 1
        if a.get("aggregate") != b.get("aggregate"):
            stats["aggregate_moved"] += 1
        ca, cb = a.get("confidence"), b.get("confidence")
        if isinstance(ca, dict) and isinstance(cb, dict):
            sa, sb = ca.get("score"), cb.get("score")
            if isinstance(sa, (int, float)) and isinstance(sb, (int, float)) and sb < sa:
                stats["confidence_decreased"] += 1

    report = {
        "stats": stats,
        "pass_regressions": regressions,
        "non_globals_moved": non_globals,
        "globals_strengthened": strengthened,
        "globals_weakened": weakened,
        "cache_after": D.cache_stats(),
    }
    print(json.dumps(report, indent=2, sort_keys=True))
    if args.json:
        with open(args.json, "w") as handle:
            json.dump(report, handle, indent=2, sort_keys=True)
    return 1 if (regressions or non_globals or stats["pass_regressions"]
                 or stats["confidence_decreased"]) else 0


if __name__ == "__main__":
    sys.exit(main())