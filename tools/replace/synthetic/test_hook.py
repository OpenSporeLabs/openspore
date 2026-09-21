#!/usr/bin/env python3
"""Headless before/after test for the synthetic inline-hook proof.

  before: trace `target` (unhooked) via the observatory tracer ->
          only the `orig` probe fires; `replacement` never fires.
  after:  run `target_hooked` DIRECTLY (no tracer). Its constructor has
          already patched `orig`'s entry in-process, so an external tracer
          would just fight the patch over the same bytes. The redirect is
          proven by the observable behavior: output shifts +1000 and
          g_replacement_ran=1.

Exits 0 iff every assertion holds.
"""

import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TRACER = os.path.join(HERE, "..", "..", "observatory", "probe_tracer")


def run_tracer(target_bin, out_jsonl):
    cmd = [
        TRACER,
        "--launch", os.path.join(HERE, target_bin),
        os.path.join(HERE, "probes.json"),
        os.path.join(HERE, out_jsonl),
        "--duration", "10",
        "--wait-module", "5",
        "--module", target_bin,
    ]
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
    if p.returncode != 0:
        print(f"FAIL: tracer on {target_bin} exited {p.returncode}\n{p.stderr}")
        sys.exit(1)
    counts = {}
    with open(os.path.join(HERE, out_jsonl)) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            e = json.loads(line)
            counts[e["name"]] = counts.get(e["name"], 0) + 1
    return counts


def run_target(target_bin):
    p = subprocess.run([os.path.join(HERE, target_bin)],
                       capture_output=True, text=True, timeout=60)
    return p.stdout, p.stderr


def check(label, cond):
    print(f"  [{'PASS' if cond else 'FAIL'}] {label}")
    return bool(cond)


def main():
    ok = True
    print("== BEFORE: unhooked target ==")
    out_b, _ = run_target("target")
    counts_b = run_tracer("target", "out_before.jsonl")
    print(f"  stdout: first line: {out_b.splitlines()[0]!r}, "
          f"last: {out_b.splitlines()[-1]!r}")
    print(f"  probe counts: {counts_b}")
    ok &= check("orig probe fires (calls reached orig)",
                counts_b.get("orig", 0) > 0)
    ok &= check("replacement probe NEVER fires",
                counts_b.get("replacement", 0) == 0)
    ok &= check("output is x*2 (call 1 -> 2)", "call  1: 2" in out_b)
    ok &= check("replacement_ran=0", "replacement_ran=0" in out_b)

    print("== AFTER: hooked target (run directly; in-process patch) ==")
    out_a, err_a = run_target("target_hooked")
    print(f"  stdout: first line: {out_a.splitlines()[0]!r}, "
          f"last: {out_a.splitlines()[-1]!r}")
    ok &= check("output shifted +1000 (call 1 -> 1002)",
                "call  1: 1002" in out_a)
    ok &= check("replacement_ran=1 (replacement actually executed)",
                "replacement_ran=1" in out_a)
    ok &= check("hook self-reported installed", "hook: installed" in err_a)

    print("RESULT:", "PASS" if ok else "FAIL")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
