#!/usr/bin/env python3
"""Real handlers for the runtime/validation MCP tools (stdlib only).

Implements ``trace_run``, ``trace_analyze``, ``trace_status``,
``test_run``, ``status_update`` and ``fixture_check`` -- the thin facade
over the committed observatory / ctest / fixture / status-board scripts
(docs/RE-AUTOMATION-ARCHITECTURE.md §§4+6).

Safety (never reinvented):

  * HUMAN gates (tools/mcp/safety.py): ``trace_run``, ``status_update``
    and ``fixture_check(rebuild=true)`` refuse with ``approval_required``
    unless re-called with ``approve=true`` under
    ``OPENSPORE_MCP_TRUSTED=1``. Identity-mode ``fixture_check``,
    ``trace_analyze``, ``trace_status`` and ``test_run`` never gate.
  * ``trace_run`` checks preconditions first (probe set, built tracer,
    wine, display, SPORE/ install, machine lock) and surfaces the first
    miss as a structured ``blocked_*`` result. It never claims success
    without observation (the JSONL event count is always reported; zero
    events is a recorded negative result, never a success claim), never
    starts/kills unrelated services (no ``wineserver -k`` here -- that
    would kill other wine processes; generation discipline stays a
    documented operator step), and never modifies the SPORE install.
  * ``status_update`` is the ONLY writer of
    ``docs/replacement-status.json``. It enforces the 9-level vocabulary
    and the evidence cap server-side: a decompilation reference caps at
    ``replaced-approx``; ``replaced-verified`` requires a live trace
    manifest. A worker's "VERIFIED" claim stays a proposition, never
    state.
  * ``test_run`` and ``trace_run`` are machine-lock aware (``flock`` on
    ``/tmp/openspore-machine.lock`` -- kernel-released on death, no
    stale lock): a held lock is the structured ``machine_locked`` code,
    never an attempt burn. ``test_run`` is never cached: every call is a
    fresh measurement.
  * Semantic/reference vs true runtime differential is distinguished in
    ``trace_analyze`` output (``kind``/``differential_note``) and
    provenance (input sha256, event count) is preserved on every result.
  * Clean-room: user-owned asset inputs only; proprietary payload bytes
    are never returned (trace JSONL carries register/timing metadata,
    never game assets); nothing is written into ``SPORE/``.

Handler contract matches registry.py: ``handler(params: dict) -> dict``;
synchronous, no threads, no hidden state. No shell anywhere in this
module: every child process is a fixed argv list, params never become
commands.
"""
import glob
import hashlib
import importlib.util
import json
import os
import shutil
import subprocess
import sys
import tempfile

from tools.mcp import config
from tools.mcp import safety

try:
    from knowledgegraph.scale import STATUS2EV as _STATUS2EV
except ImportError:  # pragma: no cover - exercised only off-repo-root
    _STATUS2EV = {
        "unknown": "UNKNOWN", "hypothesis": "INFERRED",
        "inferred": "INFERRED", "supported": "SUPPORTED",
        "verified": "VERIFIED", "approximated": "APPROXIMATION",
        "replaced-stub": "SUPPORTED", "replaced-approx": "APPROXIMATION",
        "replaced-verified": "VERIFIED",
    }

try:
    import fcntl  # Unix-only; guarded so import never fails.
except ImportError:  # pragma: no cover
    fcntl = None

_OBS_DIR = ("tools", "observatory")
_OUT_SUBDIR = "out"
_EXAMPLES_SUBDIR = "examples"
_PROBES_SUBDIR = "probes"
_DEFAULT_LOCK = "/tmp/openspore-machine.lock"
_TRACE_TIMEOUT = 240
_CTEST_TIMEOUT = 600
_EMIT_TIMEOUT = 300
# Upper bound for caller-supplied subprocess timeouts: a huge/negative
# value must neither hang the single-threaded server nor bypass the
# timeout entirely.
_MAX_TIMEOUT = 900


def _path_allowed(path):
    # type: (str) -> bool
    """True when ``path`` lives under the repo root or the temp dir.

    Tool params that name filesystem locations (trace out-dirs,
    fixture paths, explicit trace inputs) are confined here so a
    compromised/mistaken caller cannot read unrelated user files
    (e.g. /etc/passwd) or write outside disposable space. Env
    overrides (operator configuration) are intentionally exempt:
    they are not attacker-controlled tool input.
    """
    try:
        real = os.path.realpath(path)
    except (OSError, ValueError):
        return False
    for base in (os.path.realpath(config.OPENSPORE_ROOT),
                 os.path.realpath(tempfile.gettempdir())):
        if real == base or real.startswith(base + os.sep):
            return True
    return False


def _clamp_timeout(raw, default):
    # type: (object, int) -> int
    try:
        timeout = int(raw)
    except (TypeError, ValueError):
        return default
    return max(1, min(timeout, _MAX_TIMEOUT))


def _err(code, message, **extra):
    # type: (str, str, object) -> dict
    result = {"status": "error", "ok": False, "code": code,
              "message": message}
    result.update(extra)
    return result


def _binary_sha256():
    # type: () -> dict
    """Identify the target binary. Never raises; degrades, never fails."""
    path = config.resolve("SPORE", "SporeBin", "SporeApp.exe")
    if not os.path.exists(path):
        return {"binary_sha256": "unknown", "binary_available": False,
                "note": "no_spo: SPORE/ absent; provenance degraded"}
    try:
        return {"binary_sha256": config.binary_sha256(path),
                "binary_available": True}
    except (OSError, IOError) as exc:
        return {"binary_sha256": "unknown", "binary_available": False,
                "note": "no_spo: cannot hash SporeApp.exe: %s" % exc}


def _sha256_file(path):
    # type: (str) -> str | None
    digest = hashlib.sha256()
    try:
        with open(path, "rb") as fh:
            for chunk in iter(lambda: fh.read(65536), b""):
                digest.update(chunk)
    except OSError:
        return None
    return digest.hexdigest()


# --------------------------------------------------------------------------- #
# Machine lock (flock; kernel-released on process death -- no stale lock).
# --------------------------------------------------------------------------- #
def _lock_path():
    # type: () -> str
    env = os.environ.get("OPENSPORE_MCP_LOCK")
    if env:
        if os.path.isabs(env):
            return os.path.normpath(env)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT, env))
    return _DEFAULT_LOCK


def lock_held():
    # type: () -> bool
    """True when another process holds the machine lock. Never raises."""
    if fcntl is None:
        return False
    path = _lock_path()
    try:
        fh = open(path, "a+")
    except OSError:
        return False
    try:
        try:
            fcntl.flock(fh.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
        except (OSError, IOError):
            return True
        try:
            fcntl.flock(fh.fileno(), fcntl.LOCK_UN)
        finally:
            fh.close()
        return False
    except (OSError, IOError):
        try:
            fh.close()
        except (OSError, IOError):
            pass
        return False


def _machine_locked(tool):
    # type: (str) -> dict
    return _err("machine_locked",
                "shared display/GPU busy (lock %s held); park, "
                "no attempt burn" % _lock_path(),
                tool=tool, lock=_lock_path(),
                hint="retry when the holder releases; human commands "
                     "use the same flock prefix")


# --------------------------------------------------------------------------- #
# trace_run: HUMAN-gated differential capture under Wine.
# --------------------------------------------------------------------------- #
def _has_wine():
    # type: () -> bool
    """Wine presence. Module-level (monkeypatchable) for CI-safe tests."""
    return shutil.which("wine") is not None


def _has_display():
    # type: () -> bool
    """Display presence. Module-level (monkeypatchable) for CI-safe tests."""
    return bool(os.environ.get("DISPLAY"))


def _probe_path(scenario):
    # type: (str) -> str
    return config.resolve(*(_OBS_DIR + (_PROBES_SUBDIR,
                                       scenario + ".json")))


def _tracer_path():
    # type: () -> str
    return config.resolve(*(_OBS_DIR + ("probe_tracer",)))


def _observe_script():
    # type: () -> str
    return config.resolve(*(_OBS_DIR + ("observe.py",)))


def _check_scenario(params):
    # type: (dict) -> dict
    raw = params.get("scenario")
    if not isinstance(raw, str) or not raw.strip():
        return {"error": "'scenario' (probe-set name) is required "
                         "and non-empty"}
    scenario = raw.strip()
    if "/" in scenario or "\\" in scenario or ".." in scenario:
        return {"error": "'scenario' must be a probe-set name, not a "
                         "path: %r" % (raw,)}
    if not scenario.replace("-", "").replace("_", "").isalnum():
        return {"error": "'scenario' must be [A-Za-z0-9_-]+, got %r"
                         % (raw,)}
    return {"ok": True, "scenario": scenario}


def trace_run(params):
    # type: (dict) -> dict
    """Run one differential trace scenario (HUMAN-gated, preconditioned)."""
    gate = safety.approval_check("trace_run", params)
    if gate is not None:
        return gate
    identity = _binary_sha256()
    scen = _check_scenario(params)
    if "error" in scen:
        result = _err("invalid_params", scen["error"], tool="trace_run")
        result.update(identity)
        return result
    scenario = scen["scenario"]

    probe = _probe_path(scenario)
    if not os.path.exists(probe):
        result = _err("blocked_no_probe",
                      "no probe set for scenario %r (%s missing); "
                      "committed sets live in tools/observatory/probes/"
                      % (scenario, probe),
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True)
        result.update(identity)
        return result
    if not os.path.exists(_tracer_path()):
        result = _err("blocked_no_tracer",
                      "probe_tracer not built (tools/observatory/"
                      "probe_tracer missing); run: make -C "
                      "tools/observatory",
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True)
        result.update(identity)
        return result
    if not _has_wine():
        result = _err("blocked_no_wine",
                      "wine not found on PATH; cannot boot the original "
                      "as an oracle here",
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True,
                      hint="install wine 11 (see AGENTS.md) and re-issue")
        result.update(identity)
        return result
    if not _has_display():
        result = _err("blocked_no_display",
                      "no display (DISPLAY unset); the game needs :0 or "
                      "the documented Xvfb fallback (EXPERIMENTAL: "
                      "software-GL trap)",
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True)
        result.update(identity)
        return result
    if not identity["binary_available"]:
        result = _err("no_spo",
                      "SPORE/ absent: no original to observe; "
                      "trace blocked, nothing launched",
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True)
        result.update(identity)
        return result
    if lock_held():
        result = _machine_locked("trace_run")
        result["scenario"] = scenario
        result["outcome"] = "blocked"
        result["blocked"] = True
        result.update(identity)
        return result

    try:
        duration = int(params.get("duration", 20))
    except (TypeError, ValueError):
        result = _err("invalid_params", "'duration' must be an integer",
                      tool="trace_run", scenario=scenario)
        result.update(identity)
        return result
    duration = max(1, min(duration, 170))
    try:
        timeout = int(params.get("timeout", _TRACE_TIMEOUT))
    except (TypeError, ValueError):
        timeout = _TRACE_TIMEOUT
    timeout = _clamp_timeout(timeout, _TRACE_TIMEOUT)
    out_dir = params.get("out_dir") or "/tmp/openspore-observatory"
    if not _path_allowed(os.path.abspath(out_dir)):
        result = _err("invalid_params",
                      "'out_dir' must stay under the repo root or the "
                      "system temp dir, got %r" % (params.get("out_dir"),),
                      tool="trace_run", scenario=scenario)
        result.update(identity)
        return result
    cmd = [sys.executable, _observe_script(), scenario,
           "--duration", str(duration), "--out-dir", out_dir]
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              timeout=timeout)
    except (OSError, subprocess.SubprocessError) as exc:
        result = _err("trace_launch_failed",
                      "observe.py failed to launch: %s: %s"
                      % (type(exc).__name__, exc),
                      tool="trace_run", scenario=scenario, outcome="blocked",
                      blocked=True)
        result.update(identity)
        return result
    jsonl = os.path.join(out_dir, "obs_%s.jsonl" % scenario)
    events = _count_lines(jsonl)
    # Never claim success without observation: the event count rides
    # along, and zero events is a recorded negative, not a success.
    outcome = "completed" if proc.returncode == 0 else "tracer_failed"
    if proc.returncode == 0 and events == 0:
        outcome = "completed_zero_events"
    result = {"status": "ok", "tool": "trace_run", "scenario": scenario,
              "outcome": outcome, "returncode": proc.returncode,
              "events": events, "jsonl": jsonl,
              "stdout_tail": proc.stdout[-2000:],
              "stderr_tail": proc.stderr[-2000:],
              "note": "negative results are first-class evidence: "
                      "0 events means the probes never fired, not that "
                      "the behavior matched"}
    result.update(identity)
    return result


def _count_lines(path):
    # type: (str) -> int | None
    try:
        with open(path) as fh:
            return sum(1 for line in fh if line.strip())
    except (OSError, IOError):
        return None


# --------------------------------------------------------------------------- #
# trace_analyze: deterministic read-only summary over a captured JSONL.
# --------------------------------------------------------------------------- #
_ANALYZE_MOD = {"loaded": False, "mod": None}


def _load_analyze_module():
    # type: () -> object
    """Import tools/observatory/analyze.py once (fallback: reimplement)."""
    if _ANALYZE_MOD["loaded"]:
        return _ANALYZE_MOD["mod"]
    path = config.resolve(*(_OBS_DIR + ("analyze.py",)))
    mod = None
    if os.path.exists(path):
        try:
            spec = importlib.util.spec_from_file_location(
                "openspore_analyze", path)
            mod = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(mod)
        except Exception:
            mod = None
    _ANALYZE_MOD["loaded"] = True
    _ANALYZE_MOD["mod"] = mod
    return mod


def _analyze_events(events):
    # type: (list) -> dict
    """Deterministic summary (mirrors analyze.py; fallback when unimportable)."""
    import statistics
    ordered = sorted(events, key=lambda e: e["rel"])
    per_fn = {}
    for event in ordered:
        slot = per_fn.setdefault(event["name"], {"rels": [], "tids": set()})
        slot["rels"].append(event["rel"])
        slot["tids"].add(event.get("tid"))
    functions = {}
    for name in sorted(per_fn):
        rels = sorted(per_fn[name]["rels"])
        if len(rels) >= 2:
            ivals = [b - a for a, b in zip(rels, rels[1:])]
            min_i, med_i = min(ivals), statistics.median(ivals)
        else:
            min_i, med_i = None, None
        functions[name] = {
            "count": len(rels),
            "first_rel_ns": rels[0],
            "min_interval_ns": min_i,
            "median_interval_ns": med_i,
            "tids": sorted(t for t in per_fn[name]["tids"]
                           if t is not None),
        }
    threads = {}
    for event in ordered:
        tid = event.get("tid", "?")
        threads[tid] = threads.get(tid, 0) + 1
    window = 1000000000
    spikes = []
    if ordered:
        nwin = int(ordered[-1]["rel"] // window) + 1
        counts = [0] * nwin
        for event in ordered:
            counts[int(event["rel"] // window)] += 1
        prev = None
        for i, count in enumerate(counts):
            if prev is not None and prev > 0 and count > 3.0 * prev:
                spikes.append({"window": [i * window, (i + 1) * window],
                               "count": count, "prev_count": prev,
                               "ratio": count / prev})
            if count > 0:
                prev = count
    return {"events": len(ordered), "functions": functions,
            "threads": threads, "spikes": spikes}


def _resolve_trace_input(params):
    # type: (dict) -> dict
    """Resolve run_id/path to a JSONL file. Never raises."""
    raw_path = params.get("path")
    if isinstance(raw_path, str) and raw_path.strip():
        candidate = os.path.expanduser(raw_path.strip())
        if not os.path.isfile(candidate):
            return {"error": "trace file not found: %r" % (raw_path,)}
        full = os.path.abspath(candidate)
        if not _path_allowed(full):
            return {"error": "trace 'path' must stay under the repo root "
                             "or the system temp dir, got %r" % (raw_path,)}
        return {"ok": True, "path": full}
    run_id = params.get("run_id", params.get("scenario", ""))
    if not isinstance(run_id, str) or not run_id.strip():
        return {"error": "one of 'run_id' (or 'scenario') / 'path' "
                         "is required"}
    needle = run_id.strip()
    if "/" in needle or "\\" in needle or ".." in needle:
        return {"error": "'run_id' must be a run name, not a path: %r"
                         % (run_id,)}
    for subdir in (_OUT_SUBDIR, _EXAMPLES_SUBDIR):
        base = config.resolve(*(_OBS_DIR + (subdir,)))
        exact = os.path.join(base, "obs_%s.jsonl" % needle)
        if os.path.isfile(exact):
            return {"ok": True, "path": exact, "run_id": needle}
        matches = sorted(glob.glob(os.path.join(base, "*%s*.jsonl" % needle)))
        if matches:
            return {"ok": True, "path": matches[0], "run_id": needle}
    return {"error": "no captured trace for run %r in "
                     "tools/observatory/out/ or examples/" % (needle,)}


def trace_analyze(params):
    # type: (dict) -> dict
    """Deterministic read-only summary of one captured trace."""
    resolved = _resolve_trace_input(params)
    if "error" in resolved:
        return _err("blocked_unreadable", resolved["error"],
                    tool="trace_analyze")
    path = resolved["path"]
    mod = _load_analyze_module()
    try:
        if mod is not None:
            events = mod.load_events(path)
            summary = {"events": len(events),
                       "functions": mod.per_function(events),
                       "threads": mod.thread_histogram(events),
                       "spikes": mod.rate_spikes(events)}
        else:
            raw = []
            with open(path) as fh:
                for line in fh:
                    line = line.strip()
                    if not line:
                        continue
                    try:
                        event = json.loads(line)
                    except ValueError:
                        continue
                    if "name" in event and "rel" in event:
                        raw.append(event)
            summary = _analyze_events(raw)
    except (OSError, IOError, ValueError) as exc:
        return _err("blocked_unreadable",
                    "cannot analyze trace %s: %s: %s"
                    % (path, type(exc).__name__, exc),
                    tool="trace_analyze", path=path)
    # JSON round-trip normalises key types (int tids) so the result is
    # byte-deterministic across identical inputs.
    summary = json.loads(json.dumps(summary, sort_keys=True))
    result = {"status": "ok", "tool": "trace_analyze", "path": path,
              "sha256": _sha256_file(path),
              "kind": "runtime-observation-summary",
              "differential_note": (
                  "this summarizes captured RUNTIME behavior only. A "
                  "semantic check against decompiled reference code is "
                  "not a runtime differential; only a live-trace "
                  "comparison promotes past replaced-approx."),
              "summary": summary}
    if resolved.get("run_id"):
        result["run_id"] = resolved["run_id"]
    return result


# --------------------------------------------------------------------------- #
# trace_status: runs + manifests + fired/missed probes.
# --------------------------------------------------------------------------- #
def _trace_dirs(params):
    # type: (dict) -> tuple
    out_dir = params.get("out_dir") or \
        config.resolve(*(_OBS_DIR + (_OUT_SUBDIR,)))
    examples_dir = params.get("examples_dir") or \
        config.resolve(*(_OBS_DIR + (_EXAMPLES_SUBDIR,)))
    return out_dir, examples_dir


def _describe_jsonl(path):
    # type: (str) -> dict
    try:
        size = os.path.getsize(path)
        mtime = os.path.getmtime(path)
    except OSError:
        return {"path": path, "unreadable": True}
    lines = _count_lines(path)
    names = set()
    try:
        with open(path) as fh:
            for line in fh:
                line = line.strip()
                if not line:
                    continue
                try:
                    event = json.loads(line)
                except ValueError:
                    continue
                if isinstance(event, dict) and "name" in event:
                    names.add(str(event["name"]))
    except (OSError, IOError):
        lines = None
    return {"path": path, "bytes": size, "mtime": mtime,
            "lines": lines, "sha256": _sha256_file(path),
            "probes_fired": sorted(names)}


def trace_status(params):
    # type: (dict) -> dict
    """List trace runs/manifests in out/ + examples/ (read-only)."""
    out_dir, examples_dir = _trace_dirs(params)
    for label, base in (("out_dir", out_dir),
                        ("examples_dir", examples_dir)):
        if not _path_allowed(os.path.abspath(base)):
            return _err("invalid_params",
                        "'%s' must stay under the repo root or the "
                        "system temp dir, got %r" % (label, params.get(label)),
                        tool="trace_status")
    runs, manifests, others = [], [], []
    for base in (out_dir, examples_dir):
        try:
            names = sorted(os.listdir(base))
        except OSError:
            continue
        for name in names:
            full = os.path.join(base, name)
            if os.path.isdir(full):
                others.append({"path": full, "kind": "dir"})
                continue
            if not os.path.isfile(full):
                continue
            if name.endswith(".jsonl"):
                entry = _describe_jsonl(full)
                entry["kind"] = "jsonl"
                entry["run"] = name
                runs.append(entry)
            elif "manifest" in name.lower() or name.endswith(".json"):
                try:
                    entry = {"path": full, "kind": "manifest",
                             "bytes": os.path.getsize(full),
                             "mtime": os.path.getmtime(full),
                             "sha256": _sha256_file(full)}
                except OSError:
                    entry = {"path": full, "kind": "manifest",
                             "unreadable": True}
                manifests.append(entry)
            else:
                others.append({"path": full, "kind": "file"})
    runs.sort(key=lambda e: e.get("path", ""))
    manifests.sort(key=lambda e: e.get("path", ""))
    others.sort(key=lambda e: e.get("path", ""))
    probes = []
    probe_dir = config.resolve(*(_OBS_DIR + (_PROBES_SUBDIR,)))
    try:
        probe_files = sorted(glob.glob(os.path.join(probe_dir, "*.json")))
    except Exception:
        probe_files = []
    for probe_file in probe_files:
        try:
            with open(probe_file) as fh:
                doc = json.load(fh)
            items = doc.get("probes", [])
            probes.append({"scenario": os.path.splitext(
                os.path.basename(probe_file))[0],
                "probes": len(items) if isinstance(items, list) else 0})
        except (OSError, ValueError):
            probes.append({"scenario": os.path.splitext(
                os.path.basename(probe_file))[0], "unreadable": True})
    result = {"status": "ok", "tool": "trace_status",
              "out_dir": out_dir, "examples_dir": examples_dir,
              "runs": runs, "run_count": len(runs),
              "manifests": manifests, "other_files": others,
              "probe_sets": probes,
              "note": "a 0-line JSONL is a valid negative result "
                      "(probes never fired), not a missing run"}
    return result


# --------------------------------------------------------------------------- #
# test_run: ctest wrapper. Never cached, machine-lock aware.
# --------------------------------------------------------------------------- #
def _ctest_bin():
    # type: () -> str | None
    override = os.environ.get("OPENSPORE_MCP_CTEST")
    if override:
        return override
    return shutil.which("ctest")


def _build_dir():
    # type: () -> str
    override = os.environ.get("OPENSPORE_MCP_BUILD_DIR")
    if override:
        if os.path.isabs(override):
            return os.path.normpath(override)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT,
                                             override))
    return config.resolve("build")


def test_run(params):
    # type: (dict) -> dict
    """Run the ctest suite (named subset or all). Fresh measurement."""
    if lock_held():
        return _machine_locked("test_run")
    selector = params.get("selector", params.get("test", "all"))
    if not isinstance(selector, str) or not selector.strip():
        return _err("invalid_params",
                    "'selector' must be a non-empty string",
                    tool="test_run")
    selector = selector.strip()
    if len(selector) > 256:
        return _err("invalid_params", "'selector' too long (max 256)",
                    tool="test_run")
    ctest = _ctest_bin()
    if not ctest or not (os.path.isfile(ctest) or shutil.which(ctest)):
        return _err("blocked_no_ctest",
                    "ctest not found (OPENSPORE_MCP_CTEST=%r); "
                    "install cmake/ctest first"
                    % os.environ.get("OPENSPORE_MCP_CTEST"),
                    tool="test_run")
    build = _build_dir()
    if not os.path.isdir(build):
        return _err("blocked_no_build",
                    "build dir missing: %s; configure first "
                    "(cmake -S . -B build)" % build,
                    tool="test_run", build_dir=build)
    try:
        timeout = int(params.get("timeout", _CTEST_TIMEOUT))
    except (TypeError, ValueError):
        timeout = _CTEST_TIMEOUT
    timeout = _clamp_timeout(timeout, _CTEST_TIMEOUT)
    cmd = [ctest, "--test-dir", build]
    if selector != "all":
        cmd += ["-R", selector]
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              timeout=timeout)
    except (OSError, subprocess.SubprocessError) as exc:
        return _err("test_launch_failed",
                    "ctest failed to launch: %s: %s"
                    % (type(exc).__name__, exc),
                    tool="test_run", selector=selector)
    output = (proc.stdout or "") + (proc.stderr or "")
    tail = "\n".join(output.splitlines()[-30:])
    return {"status": "ok", "tool": "test_run", "selector": selector,
            "build_dir": build,
            "outcome": "passed" if proc.returncode == 0 else "failed",
            "returncode": proc.returncode, "output_tail": tail[-4000:],
            "note": "fresh measurement: test_run is never cached"}


# --------------------------------------------------------------------------- #
# status_update: the ONLY writer of docs/replacement-status.json.
# --------------------------------------------------------------------------- #
def _status_path():
    # type: () -> str
    override = os.environ.get("OPENSPORE_MCP_STATUS_FILE")
    if override:
        if os.path.isabs(override):
            return os.path.normpath(override)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT,
                                             override))
    return config.resolve("docs", "replacement-status.json")


def _trace_manifest_hit(evidence, params):
    # type: (list, dict) -> dict
    """Check replaced-verified's live-runtime requirement. Never raises.

    Returns ``{"ok": True, "manifest": path}`` when some evidence entry
    (or the explicit ``trace_manifest`` param) names an existing file
    under tools/observatory/out/ or examples/, else ``{"error": ...}``.
    """
    allowed = (
        config.resolve(*(_OBS_DIR + (_OUT_SUBDIR,))),
        config.resolve(*(_OBS_DIR + (_EXAMPLES_SUBDIR,))),
    )
    candidates = []
    explicit = params.get("trace_manifest")
    if isinstance(explicit, str) and explicit.strip():
        candidates.append(explicit.strip())
    for entry in evidence:
        if not isinstance(entry, str):
            continue
        text = entry.strip()
        if not text:
            continue
        candidates.append(text)
        # Bare run ids ("obs_main_menu") also count when the file exists.
        if "/" not in text and text.endswith(".jsonl") is False and \
                "." not in os.path.basename(text):
            candidates.append(os.path.join(
                config.resolve(*(_OBS_DIR + (_OUT_SUBDIR,))),
                "obs_%s.jsonl" % text))
    for candidate in candidates:
        if os.path.isabs(candidate):
            full = os.path.normpath(candidate)
        else:
            full = os.path.normpath(os.path.join(config.OPENSPORE_ROOT,
                                                 candidate))
        if not os.path.isfile(full):
            continue
        real = os.path.realpath(full)
        if any(real == os.path.realpath(base) or
               real.startswith(os.path.realpath(base) + os.sep)
               for base in allowed):
            return {"ok": True, "manifest": full}
    return {"error": "no trace manifest: 'replaced-verified' requires "
                     "live runtime evidence (an existing JSONL/manifest "
                     "under tools/observatory/out/ or examples/, or an "
                     "explicit 'trace_manifest' path)"}


def status_update(params):
    # type: (dict) -> dict
    """Promote/demote one subsystem entry (HUMAN-gated, cap-enforced)."""
    gate = safety.approval_check("status_update", params)
    if gate is not None:
        return gate
    name = params.get("subsystem", params.get("name"))
    if not isinstance(name, str) or not name.strip():
        return _err("invalid_params",
                    "'subsystem' (entry name) is required and non-empty",
                    tool="status_update")
    name = name.strip()
    new_status = params.get("status")
    if not isinstance(new_status, str) or not new_status.strip():
        return _err("invalid_params",
                    "'status' is required and non-empty",
                    tool="status_update", subsystem=name)
    new_status = new_status.strip()
    path = _status_path()
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except (OSError, IOError) as exc:
        return _err("blocked_unreadable",
                    "cannot read %s: %s" % (path, exc),
                    tool="status_update", subsystem=name)
    except ValueError as exc:
        return _err("corrupt_status",
                    "status file is not valid JSON: %s" % exc,
                    tool="status_update", subsystem=name)
    if not isinstance(doc, dict) or \
            not isinstance(doc.get("subsystems"), list):
        return _err("corrupt_status",
                    "status file has no 'subsystems' list",
                    tool="status_update", subsystem=name)
    vocab = doc.get("vocabulary")
    if not isinstance(vocab, list) or not vocab:
        vocab = sorted(_STATUS2EV.keys())
    if new_status not in vocab:
        return _err("invalid_status",
                    "unknown replacement status %r; valid statuses: %s"
                    % (new_status, ", ".join(vocab)),
                    tool="status_update", subsystem=name,
                    value=new_status, vocabulary=sorted(vocab))
    entry = None
    for sub in doc["subsystems"]:
        if isinstance(sub, dict) and sub.get("name") == name:
            entry = sub
            break
    if entry is None:
        return _err("not_found",
                    "no subsystem entry named %r" % (name,),
                    tool="status_update",
                    available=sorted(s.get("name", "?") for s in
                                     doc["subsystems"]
                                     if isinstance(s, dict)))
    evidence = params.get("evidence", entry.get("evidence", []))
    if evidence is None:
        evidence = []
    if not isinstance(evidence, list):
        return _err("invalid_params",
                    "'evidence' must be an array of evidence pointers",
                    tool="status_update", subsystem=name)
    if new_status.startswith("replaced-") and not evidence:
        return _err("evidence_required",
                    "status %r requires at least one evidence pointer "
                    "(test id, manifest path, doc section)" % new_status,
                    tool="status_update", subsystem=name)
    decomp_ref = any(isinstance(e, str) and "decompil" in e.lower()
                     for e in evidence)
    if decomp_ref and new_status == "replaced-verified":
        try:
            level = _STATUS2EV[new_status]
        except KeyError:
            level = "?"
        return _err("evidence_cap",
                    "decompilation reference caps at replaced-approx "
                    "(decompiler output = evidence, not truth): cannot "
                    "set 'replaced-verified' on %r (maps to %s)"
                    % (name, level),
                    tool="status_update", subsystem=name,
                    cap="replaced-approx")
    if new_status == "replaced-verified":
        hit = _trace_manifest_hit(evidence, params)
        if "error" in hit:
            return _err("evidence_cap", hit["error"],
                        tool="status_update", subsystem=name,
                        cap="no manifest ⇒ never replaced-verified")
    previous = entry.get("status")
    merged = list(entry.get("evidence", []) or [])
    for item in evidence:
        if item not in merged:
            merged.append(item)
    entry["status"] = new_status
    entry["evidence"] = merged
    entry["updated_via"] = "status_update (MCP, human-approved)"
    try:
        text = json.dumps(doc, indent=2, sort_keys=False) + "\n"
    except (TypeError, ValueError) as exc:
        return _err("evidence_cap",
                    "new evidence is not JSON-serialisable: %s" % exc,
                    tool="status_update", subsystem=name)
    try:
        with open(path, "w") as fh:
            fh.write(text)
    except (OSError, IOError) as exc:
        return _err("write_failed",
                    "cannot write %s: %s" % (path, exc),
                    tool="status_update", subsystem=name)
    return {"status": "ok", "tool": "status_update", "path": path,
            "subsystem": name, "previous": previous,
            "updated": new_status,
            "evidence_count": len(merged),
            "note": "only writer of docs/replacement-status.json; "
                    "revertible via git"}


# --------------------------------------------------------------------------- #
# fixture_check: identity mode (read-only) + gated rebuild (double-run).
# --------------------------------------------------------------------------- #
def _fixtures_path(params):
    # type: (dict) -> str
    override = params.get("fixtures_path") or \
        os.environ.get("OPENSPORE_MCP_FIXTURES")
    if isinstance(override, str) and override.strip():
        text = os.path.expanduser(override.strip())
        if os.path.isabs(text):
            return os.path.normpath(text)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT, text))
    return config.resolve("tests", "fixtures", "cell", "fixtures.json")


def _emitter_path():
    # type: () -> str
    override = os.environ.get("OPENSPORE_MCP_SIM_TEST")
    if override:
        if os.path.isabs(override):
            return os.path.normpath(override)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT,
                                             override))
    return config.resolve("build", "src", "sim", "sim_test")


def _validate_fixtures(doc):
    # type: (object) -> dict
    if not isinstance(doc, dict):
        return {"error": "fixtures root must be a JSON object"}
    if not isinstance(doc.get("contract"), str):
        return {"error": "fixtures missing string 'contract' version"}
    scenarios = doc.get("scenarios")
    if not isinstance(scenarios, list) or not scenarios:
        return {"error": "fixtures missing non-empty 'scenarios' list"}
    return {"ok": True, "contract": doc["contract"],
            "scenarios": len(scenarios)}


def fixture_check(params):
    # type: (dict) -> dict
    """Verify fixtures (identity) or rebuild them (gated, double-run)."""
    rebuild = bool(params.get("rebuild"))
    if rebuild:
        gate = safety.approval_check("fixture_check", params)
        if gate is not None:
            return gate
    raw_override = params.get("fixtures_path")
    if isinstance(raw_override, str) and raw_override.strip():
        text = os.path.expanduser(raw_override.strip())
        full = os.path.normpath(
            text if os.path.isabs(text)
            else os.path.join(config.OPENSPORE_ROOT, text))
        if not _path_allowed(full):
            return _err("invalid_params",
                        "'fixtures_path' must stay under the repo root or "
                        "the system temp dir, got %r" % (raw_override,),
                        tool="fixture_check", mode="rebuild" if rebuild
                        else "identity")
    path = _fixtures_path(params)
    if not rebuild:
        # Identity mode: read-only recompute + compare. Two independent
        # reads must agree byte-for-byte; the shape is validated; the
        # file is never written.
        try:
            with open(path, "rb") as fh:
                first = fh.read()
            with open(path, "rb") as fh:
                second = fh.read()
        except (OSError, IOError):
            return _err("not_found",
                        "fixtures not found: %s" % path,
                        tool="fixture_check", path=path)
        if hashlib.sha256(first).hexdigest() != \
                hashlib.sha256(second).hexdigest():
            return _err("unstable_read",
                        "fixtures changed between two reads: %s" % path,
                        tool="fixture_check", path=path)
        try:
            doc = json.loads(first.decode("utf-8"))
        except (UnicodeDecodeError, ValueError) as exc:
            return _err("corrupt_fixtures",
                        "fixtures at %s are not valid JSON: %s"
                        % (path, exc),
                        tool="fixture_check", path=path)
        shape = _validate_fixtures(doc)
        if "error" in shape:
            return _err("corrupt_fixtures",
                        "%s: %s" % (path, shape["error"]),
                        tool="fixture_check", path=path)
        return {"status": "ok", "tool": "fixture_check", "mode": "identity",
                "path": path, "sha256": hashlib.sha256(first).hexdigest(),
                "bytes": len(first), "contract": shape["contract"],
                "scenarios": shape["scenarios"],
                "note": "read-only: recomputed + compared, never written"}
    # Rebuild mode (HUMAN-gated above): double-run byte identity BEFORE
    # any write; a non-deterministic emitter writes nothing.
    emitter = _emitter_path()
    if not os.path.isfile(emitter):
        return _err("blocked_no_emitter",
                    "C++ emitter missing (%s); build first "
                    "(cmake --build build --target sim_test) or set "
                    "OPENSPORE_MCP_SIM_TEST" % emitter,
                    tool="fixture_check", mode="rebuild", path=path)
    tmpdir = tempfile.mkdtemp(prefix="openspore-fixtures-")
    try:
        runs = []
        for i in ("a", "b"):
            tmp = os.path.join(tmpdir, "fixtures.%s.json" % i)
            try:
                proc = subprocess.run(
                    [emitter, "--emit-fixtures", tmp],
                    capture_output=True, text=True,
                    timeout=_EMIT_TIMEOUT)
            except (OSError, subprocess.SubprocessError) as exc:
                return _err("emitter_failed",
                            "emitter failed to launch: %s: %s"
                            % (type(exc).__name__, exc),
                            tool="fixture_check", mode="rebuild")
            if proc.returncode != 0:
                return _err("emitter_failed",
                            "emitter exited %d: %s"
                            % (proc.returncode,
                               (proc.stdout + proc.stderr)[-2000:]),
                            tool="fixture_check", mode="rebuild",
                            returncode=proc.returncode)
            try:
                with open(tmp, "rb") as fh:
                    runs.append(fh.read())
            except (OSError, IOError) as exc:
                return _err("emitter_failed",
                            "cannot read emitter output: %s" % exc,
                            tool="fixture_check", mode="rebuild")
        if hashlib.sha256(runs[0]).hexdigest() != \
                hashlib.sha256(runs[1]).hexdigest():
            return _err("nondeterministic_emitter",
                        "emitter outputs differ between runs: refusing "
                        "to write %s" % path,
                        tool="fixture_check", mode="rebuild")
        try:
            shape = _validate_fixtures(
                json.loads(runs[0].decode("utf-8")))
        except (UnicodeDecodeError, ValueError) as exc:
            return _err("emitter_failed",
                        "emitter produced invalid JSON: %s" % exc,
                        tool="fixture_check", mode="rebuild")
        if "error" in shape:
            return _err("emitter_failed",
                        "emitter output invalid: %s" % shape["error"],
                        tool="fixture_check", mode="rebuild")
        try:
            parent = os.path.dirname(path)
            if parent:
                os.makedirs(parent, exist_ok=True)
            with open(path, "wb") as fh:
                fh.write(runs[0])
        except (OSError, IOError) as exc:
            return _err("write_failed",
                        "cannot write %s: %s" % (path, exc),
                        tool="fixture_check", mode="rebuild")
    finally:
        shutil.rmtree(tmpdir, ignore_errors=True)
    return {"status": "ok", "tool": "fixture_check", "mode": "rebuild",
            "path": path, "sha256": hashlib.sha256(runs[0]).hexdigest(),
            "bytes": len(runs[0]), "contract": shape["contract"],
            "scenarios": shape["scenarios"],
            "note": "double-run byte identity held before write"}
