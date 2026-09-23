#!/usr/bin/env python3
"""Reconstruction worker for the cell-stage campaign (waves 2-4).

`context` assembles a COMPLETE static context pack for one target from static
sources only: campaign plan, committed Ghidra exports, KG (spore.db, read-only),
in-tree code. No network, no live Ghidra/MCP. `record` writes the outcome back
into the campaign doc + STATE.md (+ optional KG test row).

Usage:
  recon_worker.py context CS-05 [--out FILE]
  recon_worker.py record CS-13 --status DONE --summary "..." [--test NAME --result pass] [--drift "..."] [--dry-run]
"""
import argparse
import datetime
import json
import os
import re
import sqlite3
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
CAMPAIGN = os.path.join(REPO, "docs", "analysis", "campaigns",
                        "cell-stage-campaign.md")
STATE = os.path.join(REPO, "docs", "STATE.md")
EXPORTS = os.path.join(REPO, ".spore-analysis", "ghidra-exports")
DEC_DIR = os.path.join(EXPORTS, "decompiled_sdk")
DB = os.path.join(REPO, "knowledgegraph", "spore.db")

# Wave-2 decode targets share the CS-03 serializer core (oracle + C++ reader).
WAVE2_IDS = {f"CS-{n:02d}" for n in range(5, 13)}
TEST_PAIRS = {  # src area -> (representative C++ test, python test)
    "src/sim": ("src/sim/tests/sim_contract_test.cpp", "tests/test_sim.py"),
    "src/assets": ("src/assets/tests/cellres_test.cpp", "tests/test_formats.py"),
    "src/apps": ("src/replace/tests/diff_test.cpp", "tests/test_cellstage.py"),
    "src/replace": ("src/replace/tests/diff_test.cpp", "tests/test_cellstage.py"),
}
DEFAULT_TEST_PAIR = ("src/assets/tests/assets_test.cpp", "tests/test_formats.py")


def _read_tsv(path, cols):
    with open(path) as f:
        lines = [ln.rstrip("\n") for ln in f if ln.strip()]
    assert lines[0].split("\t") == cols, f"{path}: unexpected header"
    return [dict(zip(cols, ln.split("\t"))) for ln in lines[1:]]


def load_exports():
    fns = _read_tsv(os.path.join(EXPORTS, "functions.tsv"),
                    ["address", "name", "size", "is_thunk", "is_external", "section"])
    with open(os.path.join(EXPORTS, "sdk_functions.tsv")) as f:
        sdk = {p: q for p, q in (ln.rstrip("\n").split("\t")
                                 for ln in f if ln.strip())}
    structs = _read_tsv(os.path.join(EXPORTS, "structs.tsv"),
                        ["name", "size", "field_count"])
    fields = _read_tsv(os.path.join(EXPORTS, "structs_fields.tsv"),
                       ["struct_name", "field_name", "type", "offset", "size"])
    with open(os.path.join(EXPORTS, "vtables.json")) as f:
        vtables = json.load(f)
    return {
        "fnmap": {r["address"].lower(): r for r in fns},
        "fnbyname": {r["name"]: r["address"].lower() for r in fns},
        "sdk": {k.lower(): v for k, v in sdk.items()},
        "structs": {s["name"]: s for s in structs},
        "struct_base": {s["name"].rsplit("/", 1)[-1]: s["name"] for s in structs},
        "fields": fields,
        "vtables": vtables,
    }


def kg_conn():
    c = sqlite3.connect(f"file:{DB}?mode=ro", uri=True)
    c.row_factory = sqlite3.Row
    return c


def campaign_lines():
    with open(CAMPAIGN) as f:
        return f.read().splitlines()


def target_section(lines, tid):
    """(start, end_exclusive, section_text) for the `**<tid> ...**` block."""
    pat = re.compile(r"^\s*\*\*" + re.escape(tid) + r"\b")
    start = next((i for i, ln in enumerate(lines) if pat.match(ln)), None)
    if start is None:
        sys.exit(f"error: target {tid!r} not found in campaign doc")
    end = next((j for j in range(start + 1, len(lines))
                if (re.match(r"\s*\*\*CS-\d{2}\b", lines[j])
                    or re.match(r"#{1,3} ", lines[j])
                    or lines[j].strip() == "---")), len(lines))
    return start, end, "\n".join(lines[start:end])


def _va8(s):
    s = s.lower().replace("0x", "")
    return s.zfill(8)[-8:] if s else None


def extract_addresses(sec, fnmap):
    out = [_va8(m.group(0)) for m in
           re.finditer(r"0x[0-9a-fA-F]+|\b[0-9a-f]{8}\b", sec)]
    return [va for va in dict.fromkeys(out) if va in fnmap]


def extract_structs(sec, ex, c):
    """Full struct names mentioned (bare/backticked tokens + `struct <nodeid>`)."""
    hits = {}
    toks = re.findall(r"`([^`\n]+)`", sec) + \
           re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", sec)
    for tok in toks:
        full = ex["struct_base"].get(tok) or ex["structs"].get(tok)
        if full:
            hits[full] = None
    for m in re.finditer(r"\bstruct (\d{4,6})\b", sec):
        r = c.execute("SELECT name FROM node WHERE id=?",
                      (int(m.group(1)),)).fetchone()
        if r and r["name"].startswith("struct:"):
            hits[r["name"][7:]] = None
    return list(hits)


PATH_RE = (r"`((?:src|tests|tools/spore)/[A-Za-z0-9_./{}<>-]+)`|"
           r"(?<![\w/])((?:src|tests|tools/spore)/[A-Za-z0-9_./{}<>-]+)")


def extract_paths(sec):
    return list(dict.fromkeys((m.group(1) or m.group(2)).rstrip(".;,")
                               for m in re.finditer(PATH_RE, sec)
                               if m.group(1) or m.group(2)))


def _head(path, n):
    with open(path) as f:
        return [ln.rstrip("\n") for ln in f][:n]


def _count(path):
    with open(path) as f:
        return sum(1 for _ in f)


def _sec(title, body, placeholder):
    return (f"## {title}\n\n{body}" if body
            else f"## {title}\n\n_{placeholder}_")


def build_context(tid, ex, c):
    lines = campaign_lines()
    start, end, sec = target_section(lines, tid)
    b = [  # markdown blocks, joined with a blank line
         f"# Context pack: {tid}\n\n_Assembled by "
         "`tools/recon_worker/recon_worker.py` from static sources only "
         "(campaign doc, committed Ghidra exports, KG, in-tree sources). "
         "No live Ghidra/MCP; no network._",
         f"## Campaign plan entry (lines {start + 1}-{end})\n\n{sec}"]

    addrs = extract_addresses(sec, ex["fnmap"])
    rows = [f"| {va} | {ex['fnmap'][va]['name']} | {ex['fnmap'][va]['size']} "
            f"| {ex['fnmap'][va]['section']} | {ex['sdk'].get(va, '—')} |"
            for va in addrs]
    body = ("\n| address | name | size (B) | section | sdk_name |\n"
            "|---|---|---|---|---|\n" + "\n".join(rows)) if rows else ""
    b.append(_sec("Original function facts", body,
                  "no function addresses cited in the entry"))

    named = {}  # sdk/ghidra name -> address
    for va in addrs:
        nm = ex["sdk"].get(va) or ex["fnmap"][va]["name"]
        named[nm] = va
    for tok in re.findall(r"`([A-Z][A-Za-z0-9_]*)`", sec):
        cands = {n for n in ex["sdk"].values()
                 if n == tok or n.endswith("::" + tok)}
        cands |= {n["name"] for n in ex["fnmap"].values()
                  if n["name"] == tok or n["name"].endswith("::" + tok)}
        if len(cands) == 1:
            nm = cands.pop()
            va = ex["fnbyname"].get(nm)
            if va:
                named.setdefault(nm, va)
    decs = []
    for nm in sorted(named):
        path = os.path.join(DEC_DIR, nm.replace("::", "__") + ".c")
        if os.path.exists(path):
            decs.append(f"### `{nm}` @ {named[nm]} — "
                        f"{os.path.relpath(path, REPO)}\n\n```c\n"
                        + "\n".join(_head(path, 100000)) + "\n```")
    b.append(_sec("Decompilation", "\n\n".join(decs),
                  "no decompilation files resolved for this target — decode "
                  "targets cite structs, not functions"))

    structs = extract_structs(sec, ex, c)
    ss = []
    for sname in structs:
        s = ex["structs"][sname]
        rows = [f"| {f['field_name']} | {f['type']} | {f['offset']} "
                f"| {f['size']} |"
                for f in ex["fields"] if f["struct_name"] == sname]
        ss.append(f"### `{sname}` — size {s['size']} B, "
                  f"{s['field_count']} fields\n\n"
                  "| field | type | offset | size |\n|---|---|---|---|\n"
                  + "\n".join(rows))
    b.append(_sec("Structs & fields", "\n\n".join(ss),
                  "no SDK structs named in the entry"))

    classes = set()
    for s in structs:  # -> SDK class name, e.g. App::cCellModeStrategy
        parts = [x for x in s.split("/") if x]
        classes.add("::".join(parts[1:] if parts[0] == "Spore" else parts))
    assocs = []
    for assoc in ex["vtables"].get("sdk_associations", []):
        funcs = assoc.get("sdkFuncs") or []
        if any(f.startswith(cls + "::") for cls in classes for f in funcs):
            assocs.append((assoc, funcs))
    vts = []
    for assoc, funcs in assocs:
        va = _va8(assoc.get("address") or "")
        cand = next((x for x in ex["vtables"]["candidates"]
                     if _va8(x["address"]) == va), None)
        t = (f"### `vt:{va}` — {assoc.get('address')} "
             f"(subsystems: {', '.join(assoc.get('subsystems') or [])})\n\n"
             f"sdk funcs: {', '.join(funcs)}")
        if cand:
            t += f"\n\nslots ({len(cand.get('slots', []))}):"
            t += "\n".join(
                f"  [{i}] {sl.get('ptr')} "
                f"{'-> ' + sl['func'] if sl.get('func') else '(unresolved)'}"
                for i, sl in enumerate(cand.get("slots", [])))
        vts.append(t)
    b.append(_sec("Vtables", "\n\n".join(vts),
                  "no SDK class with a vtable association is mentioned"))

    kg_names = [f"fun:{va}" for va in addrs] + [f"struct:{s}" for s in structs]
    kg_names += [f"vt:{_va8(a.get('address') or '')}" for a, _ in assocs]
    kg_names = [n for n in dict.fromkeys(kg_names) if n.split(":")[1]]
    ks = []
    if kg_names:
        rows = c.execute(
            "SELECT id,label,name,attrs_json,origin,evidence_level,note "
            "FROM node WHERE name IN (%s) ORDER BY name"
            % ",".join("?" * len(kg_names)), kg_names).fetchall()
        for r in rows:
            ks.append(f"### `{r['name']}` (id {r['id']}, {r['label']}, "
                      f"{r['evidence_level']}, origin {r['origin']})\n\n"
                      "```json\n"
                      + json.dumps(json.loads(r["attrs_json"] or "{}"),
                                   indent=1, sort_keys=True)
                      + "\n```"
                      + (f"\nnote: {r['note']}" if r["note"] else ""))
    b.append(_sec("Knowledge graph state", "\n\n".join(ks),
                  "no KG nodes resolved for this target"))

    paths = extract_paths(sec)
    if not paths and tid in WAVE2_IDS:  # compact wave-2 entries cite none
        paths = ["src/assets/CellResource.cpp", "src/assets/CellResource.hpp"]
    if re.search(r"`cell_stage`", sec) and \
            "src/apps/cell_stage.cpp" not in paths:
        paths.append("src/apps/cell_stage.cpp")  # plan shorthand alias
    ip = []
    for p in paths:
        full = os.path.join(REPO, p)
        if os.path.exists(full):
            ip.append(f"### `{p}` ({_count(full)} lines)\n\n```cpp\n"
                      + "\n".join(_head(full, 40)) + "\n```")
    b.append(_sec("In-tree mapping (files the plan cites)", "\n\n".join(ip),
                  "no in-tree paths cited — worker must consult the wave "
                  "header and CS-03 core conventions"))

    oracles = [p for p in paths if p.startswith("tools/spore/")]
    if not oracles and tid in WAVE2_IDS:
        oracles = ["tools/spore/cellres/cellres.py"]
    fx = []
    fixdir = os.path.join(REPO, "tests", "fixtures")
    for root, dirs, files in os.walk(fixdir):
        dirs[:] = [d for d in dirs if d != "__pycache__"]
        for f in sorted(files):
            fx.append(os.path.relpath(os.path.join(root, f), REPO))
    items = [f"- oracle: `{p}` ({_count(os.path.join(REPO, p))} lines)"
             for p in oracles]
    items += [f"- fixture: `{p}`" for p in sorted(fx)]
    b.append("## Oracle & fixtures\n" + "\n" + "\n".join(items))

    area = next((a for a in TEST_PAIRS
                 if any(p.startswith(a) for p in paths)), None)
    cpp_test, py_test = TEST_PAIRS.get(area, DEFAULT_TEST_PAIR)
    blk = "## Test conventions\n"
    ts = []
    for p in (cpp_test, py_test):
        full = os.path.join(REPO, p)
        if os.path.exists(full):
            ts.append(f"### `{p}` (first 30 lines)\n\n```\n"
                      + "\n".join(_head(full, 30)) + "\n```")
    blk += ("\n\n" + "\n\n".join(ts)) if ts else "\n_(no test files found)_"
    b.append(blk.rstrip())

    return "\n\n".join(b)


def cmd_context(a, ex, c):
    pack = build_context(a.target.upper(), ex, c)
    if a.out:
        with open(a.out, "w") as f:
            f.write(pack + "\n")
        print(f"wrote {a.out} ({len(pack)} chars)")
    print(pack)


def cmd_record(a, ex, c):
    tid = a.target.upper()
    lines = campaign_lines()
    start, end, sec = target_section(lines, tid)
    sec_lines = lines[start:end]
    date = datetime.date.today().isoformat()
    new_line = f"· *status*: **{a.status} ({date}).** {a.summary}" \
        + (f" Plan drift: {a.drift}" if a.drift else "")
    idx = next((i for i, ln in enumerate(sec_lines) if "*status*:" in ln), None)
    state_line = f"Cell campaign: {date} {tid} {a.status} — {a.summary}"

    with open(STATE) as f:
        s_lines = f.read().splitlines()
    s_idx = next((i for i, ln in enumerate(s_lines)
                  if ln.startswith("Cell campaign:")), None)
    if s_idx is None:  # first recording: insert under the campaign paragraph
        anchor = next((i for i, ln in enumerate(s_lines)
                       if "cell-stage completion campaign" in ln), None)
        at = anchor + 1 if anchor is not None else 0

    print(f"[record {tid}] campaign doc: "
          + (f"replace line {start + idx + 1}\n  old: {sec_lines[idx]}"
             if idx is not None else f"append after line {end}"))
    print(f"  new: {new_line}")
    print(f"[record {tid}] STATE.md: "
          + (f"replace line {s_idx + 1}\n  old: {s_lines[s_idx]}"
             if s_idx is not None
             else f"{'insert after line ' + str(at + 1) if at else 'prepend'}"))
    print(f"  new: {state_line}")

    cmd = None
    if a.test:
        if a.result is None:
            sys.exit("error: --test requires --result")
        cmd = [sys.executable, os.path.join(REPO, "knowledgegraph", "kg.py"),
               "record-test", "--name", a.test, "--stage", "cell",
               "--pass", "1" if a.result == "pass" else "0"]
        print(f"[record {tid}] KG: {' '.join(cmd)}")
    else:
        print(f"[record {tid}] KG: (no --test given; nothing recorded)")

    if a.dry_run:
        print("[dry-run] no files written")
        return

    if idx is not None:
        lines[start + idx] = new_line
    else:
        lines[end:end] = [new_line]
    with open(CAMPAIGN, "w") as f:
        f.write("\n".join(lines) + "\n")
    if s_idx is not None:
        s_lines[s_idx] = state_line
    else:
        s_lines.insert(at, state_line)
    with open(STATE, "w") as f:
        f.write("\n".join(s_lines) + "\n")
    if cmd:
        r = subprocess.run(cmd, capture_output=True, text=True)
        sys.stdout.write(r.stdout)
        sys.stderr.write(r.stderr)
        if r.returncode != 0:
            sys.exit(f"error: kg.py record-test failed (rc={r.returncode})")
    print(f"[record {tid}] done: campaign doc + STATE.md updated"
          + (" + KG test recorded" if cmd else ""))


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    cx = sub.add_parser("context",
                        help="print the full static context pack for a target")
    cx.add_argument("target", help="target id, e.g. CS-05")
    cx.add_argument("--out", help="also write the pack to this file")
    cx.set_defaults(fn=cmd_context)
    rc = sub.add_parser("record",
                        help="record a target outcome (campaign doc, STATE.md, KG)")
    rc.add_argument("target", help="target id, e.g. CS-13")
    rc.add_argument("--status", required=True,
                    choices=["DONE", "PARTIAL", "BLOCKED"])
    rc.add_argument("--summary", required=True, help="one-line outcome summary")
    rc.add_argument("--test",
                    help="KG test_result row name (calls kg.py record-test)")
    rc.add_argument("--result", choices=["pass", "fail"])
    rc.add_argument("--drift",
                    help="plan-drift notes appended to the status line")
    rc.add_argument("--dry-run", action="store_true",
                    help="print the planned changes; write nothing")
    rc.set_defaults(fn=cmd_record)
    a = p.parse_args()
    a.fn(a, load_exports(), kg_conn())


if __name__ == "__main__":
    main()
