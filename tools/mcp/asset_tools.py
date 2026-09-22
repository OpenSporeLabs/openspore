#!/usr/bin/env python3
"""Real handlers for the asset MCP tools (stdlib only).

Implements ``asset_resolve`` and ``asset_scan`` as a thin facade over
``tools/spore/asset_resolver.py --json`` (run as a subprocess with a
fixed argv list -- no shell, params can never become commands).

Clean-room rules (never reinvented, see RE-AUTOMATION-ARCHITECTURE.md §15):

  * metadata only -- record identity (type/group/instance/size/offset),
    never payload bytes;
  * package paths are constrained to the repo ``SPORE/`` tree (relative
    paths resolved under it; absolute paths must already lie inside it;
    ``..`` escapes are rejected);
  * user-owned asset inputs only; nothing is ever copied into tracked
    paths and no binaries are packaged;
  * absent ``SPORE/`` degrades to the structured ``no_spo`` result,
    never a crash.

Handler contract matches registry.py: ``handler(params: dict) -> dict``;
synchronous, no threads, no hidden state.
"""
import json
import os
import subprocess
import sys

from tools.mcp import config

RESOLVER_SCRIPT = config.resolve("tools", "spore", "asset_resolver.py")
SPORE_SUBDIR = "SPORE"

# Cap on rows surfaced per call (metadata stays small and deterministic).
_DEFAULT_LIMIT = 100
_MAX_LIMIT = 1000
_SUBPROCESS_TIMEOUT = 120


def _err(code, message, **extra):
    # type: (str, str, object) -> dict
    result = {"status": "error", "ok": False, "code": code,
              "message": message}
    result.update(extra)
    return result


def _spo_root():
    # type: () -> str
    return config.resolve(SPORE_SUBDIR)


def _spo_available():
    # type: () -> bool
    return os.path.isdir(_spo_root())


def _no_spo(tool):
    # type: (str) -> dict
    return _err("no_spo",
                "SPORE/ absent: asset metadata unavailable; "
                "identity degraded, nothing read",
                tool=tool,
                note="no_spo: install the user-owned GOG build under "
                     "SPORE/ (git-ignored, never committed)")


def _within(root, path):
    # type: (str, str) -> bool
    real_root = os.path.realpath(root)
    real_path = os.path.realpath(path)
    return real_path == real_root or real_path.startswith(real_root + os.sep)


def constrain_package(raw):
    # type: (object) -> dict
    """Resolve a ``package`` param to an absolute path inside SPORE/.

    Returns ``{"ok": True, "path": ...}`` or ``{"error": ...}`` (never
    raises). Rejects ``..`` escapes, absolute paths outside the tree,
    and shell metacharacters masquerading as paths.
    """
    if raw is None or (isinstance(raw, str) and not raw.strip()):
        return {"error": "missing 'package': name a .package file "
                         "under SPORE/ (see asset_scan inventory)"}
    if not isinstance(raw, str):
        return {"error": "'package' must be a string, got %s"
                         % type(raw).__name__}
    text = raw.strip()
    if ".." in text.split(os.sep) or ".." in text.split("/"):
        return {"error": "'package' must stay inside SPORE/: %r" % (raw,)}
    root = _spo_root()
    if os.path.isabs(text):
        candidate = os.path.normpath(text)
    else:
        candidate = os.path.normpath(os.path.join(root, text))
    if not _within(root, candidate):
        return {"error": "'package' must stay inside SPORE/: %r" % (raw,)}
    return {"ok": True, "path": candidate}


def _limit(params):
    # type: (dict) -> int
    try:
        limit = int(params.get("limit", _DEFAULT_LIMIT))
    except (TypeError, ValueError):
        return _DEFAULT_LIMIT
    return max(1, min(limit, _MAX_LIMIT))


def _run_resolver(argv_extra, tool):
    # type: (list, str) -> dict
    """Run asset_resolver.py --json with a fixed argv list. Never raises."""
    if not os.path.exists(RESOLVER_SCRIPT):
        return _err("blocked_no_resolver",
                    "tools/spore/asset_resolver.py missing; "
                    "cannot resolve asset metadata here",
                    tool=tool)
    cmd = [sys.executable, RESOLVER_SCRIPT] + list(argv_extra) + ["--json"]
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              timeout=_SUBPROCESS_TIMEOUT)
    except (OSError, subprocess.SubprocessError) as exc:
        return _err("resolver_failed",
                    "asset resolver subprocess failed: %s: %s"
                    % (type(exc).__name__, exc),
                    tool=tool)
    if proc.returncode != 0 and not proc.stdout.strip():
        return _err("resolver_failed",
                    "asset resolver exited %d: %s"
                    % (proc.returncode, proc.stderr.strip()[-500:]),
                    tool=tool, returncode=proc.returncode)
    try:
        payload = json.loads(proc.stdout)
    except ValueError as exc:
        return _err("resolver_failed",
                    "asset resolver returned unparseable JSON: %s" % exc,
                    tool=tool)
    return {"ok": True, "payload": payload,
            "returncode": proc.returncode}


def _parse_int(value):
    # type: (object) -> int | None
    try:
        return int(str(value).strip(), 0)
    except (TypeError, ValueError):
        return None


def asset_resolve(params):
    # type: (dict) -> dict
    """Resolve one asset record to type/group/instance identity (metadata)."""
    if not _spo_available():
        return _no_spo("asset_resolve")
    pkg = constrain_package(params.get("package"))
    if "error" in pkg:
        return _err("invalid_params", pkg["error"],
                    tool="asset_resolve",
                    hint="call asset_scan first for the package inventory")
    if not os.path.exists(pkg["path"]):
        return _err("not_found",
                    "package not found under SPORE/: %r"
                    % (params.get("package"),),
                    tool="asset_resolve", path=pkg["path"])

    record = params.get("record")
    type_id = params.get("type", params.get("type_id"))
    group_id = params.get("group", params.get("group_id"))
    inst_id = params.get("instance", params.get("instance_id"))
    if isinstance(record, str) and record.strip():
        parts = [p.strip() for p in record.split(":")]
        if len(parts) != 3:
            return _err("invalid_params",
                        "'record' must be T:G:I (hex), got %r" % (record,),
                        tool="asset_resolve")
        values = [_parse_int(p) for p in parts]
        if any(v is None for v in values):
            return _err("invalid_params",
                        "'record' must be T:G:I (hex), got %r" % (record,),
                        tool="asset_resolve")
        type_id, group_id, inst_id = values
    elif type_id is not None:
        type_id = _parse_int(type_id)
        group_id = _parse_int(group_id) if group_id is not None else None
        inst_id = _parse_int(inst_id) if inst_id is not None else None
        if type_id is None:
            return _err("invalid_params",
                        "'type' must be a hex/int type id",
                        tool="asset_resolve")
    else:
        return _err("invalid_params",
                    "one of 'record' (T:G:I) or 'type' is required",
                    tool="asset_resolve")

    if group_id is not None and inst_id is not None:
        out = _run_resolver(
            [pkg["path"], "--record",
             "0x%x:0x%x:0x%x" % (type_id, group_id, inst_id)],
            "asset_resolve")
        if "error" in out and "ok" not in out:
            result = out
        elif isinstance(out.get("payload"), dict) and \
                "error" in out["payload"]:
            result = _err("not_found",
                          "record 0x%08x:0x%08x:0x%08x not in %s"
                          % (type_id, group_id, inst_id,
                             os.path.basename(pkg["path"])),
                          tool="asset_resolve", package=pkg["path"])
        else:
            result = {"status": "ok", "tool": "asset_resolve",
                      "package": pkg["path"],
                      "record": out.get("payload"),
                      "provenance": "tools/spore/asset_resolver.py "
                                    "--json (metadata only; payload bytes "
                                    "never read)"}
        result.setdefault("package", pkg["path"])
        return result

    out = _run_resolver([pkg["path"], "--type", "0x%x" % type_id],
                        "asset_resolve")
    if "error" in out and "ok" not in out:
        return out
    rows = out.get("payload")
    if not isinstance(rows, list):
        return _err("resolver_failed",
                    "asset resolver returned unexpected shape",
                    tool="asset_resolve")
    limit = _limit(params)
    return {"status": "ok", "tool": "asset_resolve",
            "package": pkg["path"],
            "type": "0x%08x" % type_id,
            "records": rows[:limit], "count": len(rows),
            "truncated": len(rows) > limit,
            "provenance": "tools/spore/asset_resolver.py --json "
                          "(metadata only; payload bytes never read)"}


def asset_scan(params):
    # type: (dict) -> dict
    """Inventory a package (type histogram) or list SPORE/ packages."""
    if not _spo_available():
        return _no_spo("asset_scan")
    raw = params.get("package")
    if raw is None or (isinstance(raw, str) and not raw.strip()):
        # Inventory mode: names + sizes only; no package bytes are read.
        entries = []
        root = _spo_root()
        for dirpath, _dirnames, filenames in os.walk(root):
            for name in sorted(filenames):
                if name.lower().endswith(".package"):
                    full = os.path.join(dirpath, name)
                    try:
                        size = os.path.getsize(full)
                    except OSError:
                        size = None
                    entries.append({
                        "package": os.path.relpath(full, root),
                        "bytes": size,
                    })
        entries.sort(key=lambda e: e["package"])
        return {"status": "ok", "tool": "asset_scan",
                "mode": "inventory",
                "packages": entries, "count": len(entries),
                "provenance": "SPORE/ directory listing (names only; "
                              "no package bytes read)"}
    pkg = constrain_package(raw)
    if "error" in pkg:
        return _err("invalid_params", pkg["error"], tool="asset_scan")
    if not os.path.exists(pkg["path"]):
        return _err("not_found",
                    "package not found under SPORE/: %r" % (raw,),
                    tool="asset_scan", path=pkg["path"])
    out = _run_resolver([pkg["path"], "--typeinfo"], "asset_scan")
    if "error" in out and "ok" not in out:
        return out
    histogram = out.get("payload")
    if not isinstance(histogram, dict):
        return _err("resolver_failed",
                    "asset resolver returned unexpected shape",
                    tool="asset_scan")
    total = sum(entry.get("count", 0) for entry in histogram.values()
                if isinstance(entry, dict))
    return {"status": "ok", "tool": "asset_scan",
            "mode": "type_histogram",
            "package": pkg["path"],
            "records_total": total,
            "types": histogram, "type_count": len(histogram),
            "provenance": "tools/spore/asset_resolver.py --typeinfo "
                          "--json (metadata only; payload bytes never read)"}
