#!/usr/bin/env python3
"""observe.py — one-command capture + analysis for a wine/game scenario (stdlib).

Usage:
    python3 tools/observatory/observe.py <scenario> [--duration SEC] [--out-dir DIR]

Runs probe_tracer in --launch wine mode with probes/<scenario>.json, writes
<out-dir>/obs_<scenario>.jsonl (default: /tmp/openspore-observatory, disposable;
keep the repo tree clean), then runs analyze.py over it.
"""
import importlib.util
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TRACER = os.path.join(HERE, "probe_tracer")
LOCK = os.path.join(HERE, "lock.py")


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
    outdir = "/tmp/openspore-observatory"
    if "--out-dir" in argv:
        i = argv.index("--out-dir")
        if i + 1 >= len(argv):
            print("error: --out-dir needs a value", file=sys.stderr)
            return 2
        outdir = argv[i + 1]
    probe = os.path.join(HERE, "probes", scenario + ".json")
    if not os.path.exists(probe):
        print(f"error: no probe file {probe}", file=sys.stderr)
        return 1
    if not os.path.exists(TRACER):
        print(f"error: tracer not built ({TRACER}); run: make -C tools/observatory",
              file=sys.stderr)
        return 1
    # Shared machine lock (flock; same file + prefix as tools/mcp/runtime_tools.py
    # and menu_walk.sh): a held lock means the display/GPU is busy, so park
    # fail-closed instead of burning an attempt.
    spec = importlib.util.spec_from_file_location("openspore_lock", LOCK)
    lock = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(lock)
    try:
        lock_fh = lock.acquire("observe:%s" % scenario, task_id=scenario)
    except lock.MachineLocked as exc:
        print("machine_locked: %s held; park, no attempt burn" % lock.lock_path(),
              file=sys.stderr)
        return 5
    try:
        return _run_tracer(scenario, duration, outdir, probe)
    finally:
        lock.release(lock_fh)


def _run_tracer(scenario, duration, outdir, probe):
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
