#!/usr/bin/env python3
"""observe.py — one-command capture + analysis for a wine/game scenario (stdlib).

Usage:
    python3 tools/observatory/observe.py <scenario> [--duration SEC]

Runs probe_tracer in --launch wine mode with probes/<scenario>.json, writes
out/obs_<scenario>.jsonl, then runs analyze.py over it.
"""
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TRACER = os.path.join(HERE, "probe_tracer")


def main(argv):
    if not argv or argv[0].startswith("-"):
        print("usage: observe.py <scenario> [--duration SEC]", file=sys.stderr)
        return 2
    scenario = argv[0]
    duration = "20"
    if "--duration" in argv:
        i = argv.index("--duration")
        if i + 1 >= len(argv):
            print("error: --duration needs a value", file=sys.stderr)
            return 2
        duration = argv[i + 1]
    probe = os.path.join(HERE, "probes", scenario + ".json")
    if not os.path.exists(probe):
        print(f"error: no probe file {probe}", file=sys.stderr)
        return 1
    if not os.path.exists(TRACER):
        print(f"error: tracer not built ({TRACER}); run: make -C tools/observatory",
              file=sys.stderr)
        return 1
    outdir = os.path.join(HERE, "out")
    os.makedirs(outdir, exist_ok=True)
    out = os.path.join(outdir, f"obs_{scenario}.jsonl")
    # Module = PE name for wine targets (matched as a maps-path suffix).
    module = "SporeApp.exe"
    try:
        with open(probe) as f:
            txt = f.read()
        if '"module"' in txt:
            import json
            module = json.loads(txt).get("module", module)
    except Exception:
        pass
    cmd = [TRACER, "--launch", "wine", "--launch-arg",
           "SPORE/SporeBin/SporeApp.exe",
           probe, out, "--duration", duration,
           "--module", module, "--wait-module", "60"]
    print("+ " + " ".join(cmd))
    rc = subprocess.run(cmd).returncode
    if rc != 0:
        print(f"tracer exited {rc}; see its stderr above", file=sys.stderr)
        return rc
    print(f"wrote {out}; analyzing...")
    rc = subprocess.run([sys.executable, os.path.join(HERE, "analyze.py"), out]).returncode
    return rc


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
