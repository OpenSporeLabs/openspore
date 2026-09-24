#!/usr/bin/env python3
"""SDK boundary-repair worker (analysis-only, read-only Ghidra).

For each of the 1186 SDK VAs with no function entry (unique-address basis
over .spore-analysis/ghidra-exports/sdk_functions.tsv minus
functions.tsv), inspects the live Ghidra program via READ-ONLY REST
(GET get_function_by_address / get_xrefs_to / read_memory, plus GET
disassemble_function only on tiny thunk entries to resolve the jump
target) and adjudicates exactly one verdict per VA.

Verdicts:
  repaired-contained              VA inside a known function body -> repaired
                                  VA = containing entry (mid-function SDK
                                  label; includes live entries that appeared
                                  since the snapshot).
  repaired-thunk-alias            containing function is a thunk -> repaired
                                  VA = thunk target (or entry if unresolved).
  repaired-prologue-recoverable   VA carries a function prologue + callers /
                                  padding / no container -> defensible new
                                  boundary at VA itself (NOT created here).
  adjudicated-tail-alias          VA in the tail bytes of a known body, no
                                  prologue/callers -> alias, repaired NULL.
  adjudicated-data/vtable-slot-not-code
                                  VA is data (non-.text container, vtable
                                  slot pointer, data xrefs) -> repaired NULL.
  adjudicated-dead-address        no container, no callers, no prologue ->
                                  repaired NULL.

Creates NOTHING in Ghidra (no functions, no disassembly, no re-analysis).
Writes:
  knowledgegraph/triage/sdk-boundary-repairs-<snap8>.json  (full records)
  knowledgegraph/triage/sdk-boundary-repairs-<snap8>.tsv   (compact rows)

Probes are cached under /tmp/opencode/sdk-repair/probes/<va8>.json so reruns
are offline-idempotent and resumable; delete the dir to force re-probing.

Stdlib only. Deterministic: inputs sorted, JSON separators/sort_keys fixed.
"""

import argparse
import csv
import hashlib
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
KG_DIR = os.path.join(REPO, "knowledgegraph")
TRIAGE_OUT = os.path.join(KG_DIR, "triage")
DEFAULT_EXPORTS = os.path.join(REPO, ".spore-analysis", "ghidra-exports")
PROBE_DIR = "/tmp/opencode/sdk-repair/probes"

sys.path.insert(0, os.path.join(REPO, "tools", "mcp"))
from ghidra_client import GhidraClient  # noqa: E402

BINARY_SHA256 = "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e"

VERDICTS = (
    "repaired-contained",
    "repaired-thunk-alias",
    "repaired-prologue-recoverable",
    "adjudicated-tail-alias",
    "adjudicated-data/vtable-slot-not-code",
    "adjudicated-dead-address",
)


def norm_va(s):
    s = (s or "").strip().lower()
    if s.startswith("0x"):
        s = s[2:]
    return s.zfill(8)[-8:]


def load_context(exports):
    fns = {}
    with open(os.path.join(exports, "functions.tsv"), newline="") as f:
        for r in csv.DictReader(f, delimiter="\t"):
            fns[norm_va(r["address"])] = r
    sdk_names = {}
    with open(os.path.join(exports, "sdk_functions.tsv")) as f:
        for ln in f:
            ln = ln.rstrip("\n")
            if not ln.strip():
                continue
            va, name = ln.split("\t")
            sdk_names.setdefault(norm_va(va), []).append(name)
    with open(os.path.join(exports, "vtables.json")) as f:
        vt = json.load(f)
    ptr_info = {}
    for cand in vt["candidates"]:
        cva = norm_va(cand["address"])
        for s in cand.get("slots", []):
            p = norm_va(s.get("ptr") or "x") if s.get("ptr") else None
            if p:
                ptr_info.setdefault(p, []).append({
                    "vtable": cva,
                    "func": s.get("func"),
                    "funcStart": bool(s.get("funcStart")),
                    "sdk": bool(s.get("sdk")),
                })
    with open(os.path.join(REPO, "tools", "triage", "rules-v4.json")) as f:
        rules = json.load(f)
    triage = {}
    tri_path = os.path.join(TRIAGE_OUT, "triage-2540f2ca.jsonl")
    if os.path.exists(tri_path):
        with open(tri_path) as f:
            for ln in f:
                r = json.loads(ln)
                triage[r["va"]] = r
    return fns, sdk_names, ptr_info, rules, triage


def probe_va(client, va8):
    """Read-only probe of one VA. Returns dict; cached on disk."""
    os.makedirs(PROBE_DIR, exist_ok=True)
    cache = os.path.join(PROBE_DIR, va8 + ".json")
    if os.path.exists(cache):
        with open(cache) as f:
            return json.load(f)
    out = {"va": va8}
    r = client.request("/get_function_by_address", {"address": "0x" + va8})
    if r.get("status") == "ok":
        out["containing"] = r["data"]
    else:
        out["containing"] = None
        out["containing_error"] = str(r.get("message", r.get("code")))
    x = client.request("/get_xrefs_to", {"address": "0x" + va8, "limit": 10})
    if x.get("status") == "ok" and isinstance(x.get("data"), dict):
        d = x["data"]
        out["xrefs_total"] = d.get("total", 0)
        out["xrefs_sample"] = d.get("references", [])[:10]
    else:
        out["xrefs_total"] = None
        out["xrefs_sample"] = []
    m = client.request("/read_memory",
                       {"address": "0x" + va8, "length": 16})
    if m.get("status") == "ok" and isinstance(m.get("data"), dict):
        out["bytes16"] = m["data"].get("hex")
    else:
        out["bytes16"] = None
    va_int = int(va8, 16)
    mb = client.request("/read_memory",
                        {"address": "0x%08x" % (va_int - 4,), "length": 4})
    if mb.get("status") == "ok" and isinstance(mb.get("data"), dict):
        out["bytes_before4"] = mb["data"].get("hex")
    else:
        out["bytes_before4"] = None
    with open(cache, "w") as f:
        json.dump(out, f, sort_keys=True, separators=(",", ":"))
    return out


def prologue_strength(hex16):
    """0 = none, 1 = weak (single push starter), 2 = strong."""
    if not hex16:
        return 0
    b = bytes.fromhex(hex16)
    if b[:3] == b"\x55\x8b\xec" or b[:2] == b"\x8b\xff":
        return 2
    if b[0:1] in (b"\x53", b"\x56", b"\x57") and len(b) >= 4:
        if b[1:2] in (b"\x53", b"\x56", b"\x57"):
            return 2  # multi-push thiscall-style prologue
        if b[1:2] in (b"\x8b", b"\x83", b"\x81", b"\xe9", b"\xe8"):
            return 1
        return 0
    if b[0] == 0x83 and len(b) > 2 and b[1] == 0xEC:
        return 1  # frameless sub-esp leaf
    return 0


def has_prologue(hex16):
    return prologue_strength(hex16) > 0


def has_padding(hex4):
    if not hex4:
        return False
    b = bytes.fromhex(hex4)
    return b in (b"\xcc\xcc\xcc\xcc",) or b.endswith(b"\xcc\xcc") \
        or b == b"\x90\x90\x90\x90"


def looks_like_tail(hex16):
    if not hex16:
        return False
    b = bytes.fromhex(hex16)
    return b[0] in (0xC3, 0xC2, 0xEB, 0xE9) or b[:2] == b"\xFF\x25"


def resolve_thunk_target(client, entry_va8):
    """Read-only: disassemble tiny thunk entry, parse JMP target."""
    d = client.request("/disassemble_function",
                       {"address": "0x" + entry_va8})
    if d.get("status") != "ok":
        return None, "disasm-unavailable"
    insns = (d.get("data") or {}).get("instructions") or \
        (d.get("data") or {}).get("listing") or []
    if not insns:
        return None, "empty-listing"
    first = insns[0] if isinstance(insns, list) else None
    if not first:
        return None, "unparsed-listing"
    text = str(first.get("instruction") or first)
    up = text.upper()
    import re
    if "JMP" not in up:
        return None, "entry-not-jmp:%s" % text[:60]
    m = re.search(r"0x([0-9A-Fa-f]{4,8})", text)
    if m:
        tgt = norm_va(m.group(1))
        # dword-ptr thunk: JMP [addr] -> dereference to get the target
        if "[" in text:
            r = client.request("/read_memory",
                               {"address": "0x" + tgt, "length": 4})
            try:
                raw = (r.get("data") or {}).get("hex") or ""
                val = int.from_bytes(bytes.fromhex(raw), "little")
                return "%08x" % val, "dword-ptr-thunk"
            except (ValueError, TypeError):
                return tgt, "ptr-addr-unreadable"
        return tgt, "rel-jmp-thunk"
    return None, "jmp-target-unparsed:%s" % text[:60]


def hypothetical_change(va8, sdk_name, fns, full, rules, triage):
    """Would attaching sdk_name to va8's triage row change
    (category, priority, evidence)? Returns (changed, detail)."""
    sys.path.insert(0, HERE)
    import classify as C
    row = triage.get(va8)
    snap_row = fns.get(va8)
    if row is None or snap_row is None:
        return True, "adds-row-or-live-only (no v4 triage row at %s)" % va8
    before = (row["category"], row["priority"], row["evidence"])
    r = dict(snap_row)
    r["va8"] = va8
    sdk = dict(full["sdk"])
    sdk[va8] = sdk_name
    new = C.classify_row(r, sdk, full["struct_index"],
                         full["func_to_vt"], full["decomp"], rules)
    after = (new["category"], new["priority"], new["evidence"])
    if after != before:
        return True, "%s->%s" % ("|".join(before), "|".join(after))
    return False, "stable:%s" % ("|".join(before),)


def adjudicate(va8, names, probe, fns, ptr_info, sorted_fns):
    cont = probe.get("containing")
    xtotal = probe.get("xrefs_total") or 0
    b16 = probe.get("bytes16")
    prol = has_prologue(b16)
    pad = has_padding(probe.get("bytes_before4"))
    vtslots = ptr_info.get(va8, [])
    ev = []
    ev.append("sdk=%s" % (";".join(names)))
    if cont:
        entry = norm_va(cont.get("address") or cont.get("entry_point"))
        bs = norm_va(cont.get("body_start") or entry)
        be = norm_va(cont.get("body_end") or entry)
        off = int(va8, 16) - int(entry, 16)
        tail = int(be, 16) - int(va8, 16)
        ev.append("containing=%s(off+%d,tail-%d,%s..%s,%s)" % (
            entry, off, tail, bs, be, cont.get("name")))
    else:
        entry = off = tail = None
        ev.append("containing=NONE(%s)" %
                  (probe.get("containing_error") or "?"))
    ev.append("xrefs_to=%s" % (xtotal if probe.get("xrefs_total") is not None
                               else "ERR"))
    if xtotal and probe.get("xrefs_sample"):
        callers = sorted({norm_va(s.get("from_function", "?")[-8:])
                          if isinstance(s.get("from_function"), str)
                          and len(s.get("from_function", "")) >= 8
                          else str(s.get("from_address", "?"))
                          for s in probe["xrefs_sample"]})
        ev.append("callers=%s" % ",".join(callers[:6]))
    ev.append("bytes=%s" % (b16 or "UNREADABLE"))
    ev.append("prologue=%s padding=%s" % (prol, pad))
    if vtslots:
        ev.append("vtable_slots=%d(%s)" % (
            len(vtslots),
            ",".join(sorted({s["vtable"] for s in vtslots}))))
    import bisect
    i = bisect.bisect_left(sorted_fns, va8)
    prev_va = sorted_fns[i - 1] if i > 0 else None
    next_va = sorted_fns[i] if i < len(sorted_fns) else None
    ev.append("neighbors=%s|%s" % (prev_va, next_va))

    snap_cont = fns.get(entry) if entry else None
    is_thunk = snap_cont is not None and \
        snap_cont.get("is_thunk") == "true"
    section = (snap_cont or {}).get("section", "?")

    if cont and is_thunk:
        return ("repaired-thunk-alias", entry, "thunk-container",
                "medium", ev)
    if prol and (xtotal > 0 or pad or not cont):
        strength = prologue_strength(b16)
        if xtotal > 0 and (pad or not cont):
            conf = "high"
        elif xtotal > 0 or pad or (strength == 2 and not cont):
            conf = "medium"
        else:
            conf = "low"
        return ("repaired-prologue-recoverable", va8,
                "prologue-at-va(strength%d)" % strength, conf, ev)
    if cont and entry == va8:
        return ("repaired-contained", entry, "live-entry-present",
                "high", ev)
    if cont:
        if tail is not None and tail <= 16 and \
                (looks_like_tail(b16) or xtotal == 0) and not prol:
            return ("adjudicated-tail-alias", None,
                    "tail-bytes-no-callers", "medium", ev)
        if section != ".text":
            return ("adjudicated-data/vtable-slot-not-code", None,
                    "non-text-container:%s" % section, "high", ev)
        if vtslots and xtotal == 0 and not prol:
            return ("adjudicated-data/vtable-slot-not-code", None,
                    "vtable-ptr-no-code", "medium", ev)
        conf = "high" if xtotal > 0 else \
            ("medium" if b16 else "low")
        return ("repaired-contained", entry,
                "containing-function-fallback", conf, ev)
    # no container
    if vtslots:
        return ("adjudicated-data/vtable-slot-not-code", None,
                "vtable-slot-ptr-no-container",
                "high" if xtotal == 0 else "medium", ev)
    if xtotal > 0:
        return ("adjudicated-data/vtable-slot-not-code", None,
                "data-xrefs-no-prologue", "medium", ev)
    if b16 is None:
        return ("adjudicated-dead-address", None,
                "unmapped-unreadable", "medium", ev)
    return ("adjudicated-dead-address", None,
            "no-container-no-callers-no-prologue", "low", ev)


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--exports", default=DEFAULT_EXPORTS)
    p.add_argument("--snap8", default="2540f2ca")
    p.add_argument("--probe-only", action="store_true")
    p.add_argument("--no-probe", action="store_true",
                   help="offline: use cached probes only")
    a = p.parse_args(argv)

    with open(os.path.join(a.exports, "functions.tsv"), "rb") as f:
        pass
    fns, sdk_names, ptr_info, rules, triage = load_context(a.exports)
    snap_path = os.path.join(TRIAGE_OUT, "summary-%s.json" % a.snap8)
    snapshot_sha256 = json.load(open(snap_path))["snapshot_sha256"]

    missing = sorted(va for va in sdk_names if va not in fns)
    present = sorted(va for va in sdk_names if va in fns)
    assert len(missing) == 1186, "missing=%d, expected 1186" % len(missing)
    assert len(present) == 477, "present=%d, expected 477" % len(present)
    print("missing=%d present=%d distinct=%d" %
          (len(missing), len(present), len(sdk_names)), flush=True)

    client = GhidraClient(timeout=30)
    if not a.no_probe:
        chk = client.check_connection()
        assert chk.get("status") == "ok", "Ghidra bridge offline: %r" % chk
        meta = client.request("/get_metadata")
        prog = (meta.get("data") or {}).get("program_name")
        assert prog == "SporeApp.exe", "wrong program: %r" % prog
    sorted_fns = sorted(fns)
    sys.path.insert(0, HERE)
    import classify as C
    full = C.load_inputs(DEFAULT_EXPORTS, rules)

    records = []
    thunk_targets = {}
    for n, va8 in enumerate(missing):
        if a.no_probe:
            cache = os.path.join(PROBE_DIR, va8 + ".json")
            if not os.path.exists(cache):
                raise SystemExit("no cached probe for %s (run with probe)"
                                 % va8)
            with open(cache) as f:
                probe = json.load(f)
        else:
            probe = probe_va(client, va8)
        verdict, repaired, method, conf, ev = adjudicate(
            va8, sdk_names[va8], probe, fns, ptr_info, sorted_fns)
        if verdict == "repaired-thunk-alias" and repaired and not a.no_probe:
            if repaired not in thunk_targets:
                tgt, how = resolve_thunk_target(client, repaired)
                thunk_targets[repaired] = (tgt, how)
            tgt, how = thunk_targets[repaired]
            ev.append("thunk_target=%s(%s)" % (tgt, how))
            if tgt and len(tgt) == 8 and tgt in fns:
                repaired = tgt
                method = "thunk-target-resolved"
        if verdict.startswith("repaired") and repaired:
            if verdict == "repaired-prologue-recoverable":
                changed, delta = hypothetical_change(
                    va8, sdk_names[va8][-1], fns, full, rules, triage)
                changed = True  # new row regardless; delta is advisory
                delta = "adds-row;hypothetical:" + delta
            else:
                changed, delta = hypothetical_change(
                    repaired, sdk_names[va8][-1], fns, full,
                    rules, triage)
        else:
            changed, delta = False, "no-triage-row-affected"
        records.append({
            "sdk_va": va8,
            "sdk_names": sdk_names[va8],
            "verdict": verdict,
            "repaired_va": repaired,
            "method": method,
            "confidence": conf,
            "changes_classification": changed,
            "classification_delta": delta,
            "evidence": "; ".join(ev),
            "probe": probe,
        })
        if (n + 1) % 200 == 0:
            print("probed+adjudicated %d/%d" % (n + 1, len(missing)),
                  flush=True)
    if a.probe_only:
        print("probe-only: cached %d probes" % len(missing))
        return

    assert len(records) == 1186
    assert len({r["sdk_va"] for r in records}) == 1186, "duplicate VA!"
    assert all(r["verdict"] in VERDICTS for r in records)

    rec_bytes = json.dumps(
        [{k: r[k] for k in ("sdk_va", "sdk_names", "verdict", "repaired_va",
                            "method", "confidence", "changes_classification",
                            "classification_delta", "evidence")}
         for r in records],
        sort_keys=True, separators=(",", ":")).encode()
    repairs_sha = hashlib.sha256(rec_bytes).hexdigest()
    doc = {
        "artifact": "sdk-boundary-repairs",
        "snap8": a.snap8,
        "snapshot_sha256": snapshot_sha256,
        "binary_sha256": BINARY_SHA256,
        "provenance": {
            "method": "tools/triage/repair_sdk_boundaries.py "
                      "(read-only Ghidra REST on SporeApp.exe: "
                      "get_function_by_address/get_xrefs_to/read_memory, "
                      "disassemble_function on thunk entries only; "
                      "no functions created, no re-analysis)",
            "exports": ".spore-analysis/ghidra-exports "
                       "(functions.tsv/sdk_functions.tsv/vtables.json), "
                       "triage-v4 rules+rows for classification deltas",
            "note": "generated_at excluded from all hashes; repairs_sha256 "
                    "covers the adjudication records only.",
        },
        "counts": {v: sum(1 for r in records if r["verdict"] == v)
                   for v in VERDICTS},
        "repairs_sha256": repairs_sha,
        "records": sorted(records, key=lambda r: r["sdk_va"]),
    }
    jp = os.path.join(TRIAGE_OUT,
                      "sdk-boundary-repairs-%s.json" % a.snap8)
    with open(jp, "w") as f:
        json.dump(doc, f, indent=2, sort_keys=True)
    tp = os.path.join(TRIAGE_OUT,
                      "sdk-boundary-repairs-%s.tsv" % a.snap8)
    with open(tp, "w", newline="") as f:
        w = csv.writer(f, delimiter="\t")
        w.writerow(["sdk_va", "sdk_names", "verdict", "repaired_va",
                    "method", "confidence", "changes_classification",
                    "classification_delta", "evidence"])
        for r in doc["records"]:
            w.writerow([r["sdk_va"], ";".join(r["sdk_names"]), r["verdict"],
                        r["repaired_va"] or "NULL", r["method"],
                        r["confidence"], str(r["changes_classification"]),
                        r["classification_delta"], r["evidence"]])
    from collections import Counter
    print(json.dumps({"counts": doc["counts"],
                      "by_conf": dict(sorted(Counter(
                          r["confidence"] for r in records).items())),
                      "changes": sum(1 for r in records
                                     if r["changes_classification"]),
                      "repairs_sha256": repairs_sha}, indent=2))
    print("wrote %s\nwrote %s" % (jp, tp))


if __name__ == "__main__":
    main()
