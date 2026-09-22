#!/usr/bin/env python3
"""Real handlers for the Ghidra/dossier MCP tools (stdlib only).

Implements ``ghidra_decompile``, ``ghidra_function``, ``ghidra_search``,
``ghidra_snapshot_save``, ``vtable_lookup``, ``dossier_read`` and
``dossier_regenerate`` against the headless GhidraMCP REST bridge plus
committed artifacts. Handler contract matches registry.py:
``handler(params: dict) -> dict``; synchronous, no threads, no hidden
state beyond the documented in-session memos.

Conventions (mirror docs/analysis/MCP-DESIGN.md §§C/D/F, never reinvented):
  * image base ``0x00400000``; an ``rva`` hex value gets ``+image_base``
    for the VA sent to REST; a value >= image base is treated as a VA;
    anything else is a symbol name resolved via ``/search_functions``;
  * every result carries the uniform envelope: ``mode`` in
    {live,cache,snapshot,offline,unavailable} + ``provenance`` (stable
    string: REST endpoint / disk-cache key / committed path; None only
    when no source was consulted) + binary/program identity
    (``binary_sha256`` of ``SPORE/SporeBin/SporeApp.exe`` or
    ``"unknown"`` + ``no_spo`` note when absent, ``program`` name,
    ``image_base`` where applicable). Legacy ``cached``/``cache`` keys
    are kept verbatim; stored cache metas live under
    ``provenance_detail``;
  * decompilation is EVIDENCE, NOT TRUTH (``evidence_note`` on every
    decompile result);
  * domain failures are in-band ``{"status": "error", "code": ...}``
    dicts (never exceptions); Ghidra unreachable is the structured
    ``ghidra_offline`` code;
  * filesystem access is constrained to repo/tool paths derived from
    ``config.OPENSPORE_ROOT`` (dossiers dir, snapshot data dir, cache
    root): topic/label params must match ``[A-Za-z0-9_-]+`` and ``..``/
    ``/``/absolute paths are rejected -- there is no child-process or
    command-shell use anywhere in this module, so params can never become commands.
"""
import glob
import hashlib
import importlib.util
import json
import os
import re

from tools.mcp import cache as decompile_cache
from tools.mcp import config
from tools.mcp import ghidra_client as client_mod

IMAGE_BASE = 0x400000
DEFAULT_PROGRAM = "SporeApp.exe"
EVIDENCE_NOTE = ("decompiler output = evidence, not truth; "
                 "no MSVC RTTI in this binary")

_TOPIC_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9_-]*$")
_PROGRAM_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9_.-]*$")
_SNAPSHOT_SCHEMA = "ghidra-function-snapshot-1"

# Uniform result envelope (S2.1 scope A): every handler result carries
# ``mode`` (exactly one of the five below) + ``provenance`` (a stable
# source string: REST endpoint, disk-cache key, or committed path;
# None only when no source was consulted, never a guess) alongside the
# pre-existing keys. ``cached``/``cache`` (hit/miss/hit-offline-fallback)
# stay verbatim; stored cache metas move to ``provenance_detail``.
# Mode map: live = REST ok; cache = disk hit; snapshot = committed
# tools/re/data/*.json; offline = bridge down (ghidra_offline);
# unavailable = no_spo / missing file / unvalidated params.
_MODE_LIVE = "live"
_MODE_CACHE = "cache"
_MODE_SNAPSHOT = "snapshot"
_MODE_OFFLINE = "offline"
_MODE_UNAVAILABLE = "unavailable"
_MODES = frozenset([_MODE_LIVE, _MODE_CACHE, _MODE_SNAPSHOT,
                    _MODE_OFFLINE, _MODE_UNAVAILABLE])

_SNAPSHOT_REL = "tools/re/data/ghidra_snapshot_cell_movement.json"
_SNAPSHOT_PROVENANCE = _SNAPSHOT_REL + " (committed)"
_VTABLES_REL = "docs/analysis/vtables.json"
_VTABLES_PROVENANCE = _VTABLES_REL + " (committed)"

_DECOMPILED_REF_RE = re.compile(
    r"^\s*See\s+(tools/re/data/decompiled/\S+\.c)\b")

# In-session memos only (pure reads; disposable like tools/mcp/cache/).
_FUNCTION_MEMO = {}
_VTABLES_DOC = {"loaded": False, "doc": None}
_DOSSIER_MOD = {"loaded": False, "mod": None}

# Injectable client factory (tests monkeypatch this; default reads env).
_CLIENT_FACTORY = client_mod.default_client


def _err(code, message, **extra):
    # type: (str, str, object) -> dict
    result = {"status": "error", "ok": False, "code": code,
              "message": message}
    result.update(extra)
    return result


def _get_client():
    # type: () -> object
    try:
        return _CLIENT_FACTORY()
    except Exception as exc:
        class _Dead(object):
            def __getattr__(self, _name):
                def _fail(*_a, **_k):
                    return {"status": "error", "ok": False,
                            "code": "ghidra_offline",
                            "message": "cannot build Ghidra client: %s: %s"
                                       % (type(exc).__name__, exc)}
                return _fail
        return _Dead()


# --------------------------------------------------------------------------- #
# Uniform envelope + shared name resolution (S2.1 scopes A/B).
# --------------------------------------------------------------------------- #
def _repo_rel(path):
    # type: (str) -> str
    """Repo-relative path string for stable provenance. Never raises."""
    try:
        rel = os.path.relpath(str(path), config.OPENSPORE_ROOT)
    except (OSError, ValueError):
        return str(path)
    return rel.replace(os.sep, "/")


def _rest_provenance(client, endpoint):
    # type: (object, str) -> str
    """Stable REST source string (endpoint + bridge base). Never raises."""
    try:
        base = getattr(client, "base", None) or "unknown"
    except Exception:
        base = "unknown"
    return "GhidraMCP REST %s @ %s" % (endpoint, base)


def _cache_provenance_str(meta, c_path):
    # type: (dict, str) -> str
    """Stable disk-cache source string from a stored meta. Never raises."""
    key = meta.get("key", {}) if isinstance(meta, dict) else {}
    if not isinstance(key, dict):
        key = {}
    return "disk cache %s (key binary_sha256=%s rva=%s ghidra_version=%s program=%s)" % (
        _repo_rel(c_path or "unknown"),
        key.get("binary_sha256", "?"), key.get("rva", "?"),
        key.get("ghidra_version", "?"), key.get("program", "?"))


def _ok_envelope(identity, mode, provenance, def_program, base, **fields):
    # type: (dict, str, str, str, int, object) -> dict
    """Attach the uniform ok-envelope. Additive: keeps all old keys."""
    result = dict(fields)
    result["mode"] = mode
    result["provenance"] = provenance
    result.setdefault("program", def_program)
    result.setdefault("image_base", "0x%x" % base)
    result.update(identity)
    return result


def _error_envelope(code, message, mode, provenance, identity, **extra):
    # type: (str, str, str, str, dict, object) -> dict
    """Attach the uniform error-envelope. Additive: keeps all old keys."""
    result = _err(code, message, mode=mode, provenance=provenance,
                  **extra)
    result.update(identity)
    return result


def _name_failure_provenance(client, code):
    # type: (object, str) -> str
    """Explicit consulted-sources string for a failed name lookup."""
    rest = _rest_provenance(client, "/search_functions")
    state = "unreachable" if code == "ghidra_offline" else "no match"
    return "%s (%s) + %s (no row)" % (rest, state, _SNAPSHOT_PROVENANCE)


def _name_failure_mode(code):
    # type: (str) -> str
    return _MODE_OFFLINE if code == "ghidra_offline" else _MODE_LIVE


def _snapshot_row_by_name(name):
    # type: (str) -> dict | None
    """Exact-name row from the committed snapshot. Never raises."""
    for row in _committed_snapshot_functions():
        if isinstance(row, dict) and row.get("name") == name:
            return row
    return None


def _snapshot_names(limit=20):
    # type: (int) -> list
    """Sorted committed-snapshot function names (for candidates)."""
    names = set()
    for row in _committed_snapshot_functions():
        if isinstance(row, dict) and row.get("name"):
            names.add(row["name"])
    return sorted(names)[:limit]


def _snapshot_candidates(name, limit=8):
    # type: (str, int) -> list
    """Substring name hints from the committed snapshot. Never raises."""
    needle = str(name).lower()
    return [n for n in _snapshot_names(100) if needle in n.lower()][:limit]


def _resolve_with_fallback(client, target, image_base=IMAGE_BASE):
    # type: (object, dict, int) -> dict
    """Shared name resolver with committed-snapshot fallback (scope B).

    ``target`` is a ``_target_from_params``/``resolve_target`` dict.
    Address targets pass through untouched (``via="live"``: nothing to
    resolve). Name-only targets resolve via REST ``/search_functions``;
    when that fails, via the committed snapshot by exact name.
    Returns ``{"ok": True, "target": ..., "via": "live"|"snapshot"}`` or
    ``{"error": ..., "code": "not_found"|"ghidra_offline",
    "candidates": [...], "snapshot_names": [...]}`` -- symmetric codes
    for every caller, never a masquerading empty ok. Never raises.
    """
    if not isinstance(target, dict) or target.get("va") is not None \
            or not target.get("name"):
        return {"ok": True, "target": target, "via": "live"}
    name = target["name"]
    try:
        resolved = _resolve_name_to_va(client, name)
    except Exception as exc:
        resolved = {"error": "ghidra_offline: resolver raised %s: %s"
                             % (type(exc).__name__, exc)}
    if "ok" in resolved:
        return {"ok": True, "target": resolved, "via": "live"}
    row = _snapshot_row_by_name(name)
    if row is not None:
        addr = row.get("address")
        if isinstance(addr, str):
            routed = resolve_target(addr, image_base)
        else:
            routed = {"error": "snapshot row %r has no VA address"
                               % (name,)}
        if "ok" in routed:
            routed["name"] = row.get("name") or name
            return {"ok": True, "target": routed, "via": "snapshot"}
    msg = resolved.get("error", "cannot resolve name %r" % (name,))
    code = "ghidra_offline" if msg.startswith("ghidra_offline") \
        else "not_found"
    return {"error": msg, "code": code,
            "candidates": _snapshot_candidates(name),
            "snapshot_names": _snapshot_names()}


def _snapshot_decompiled(va, rva, name):
    # type: (str, str, str) -> tuple
    """Committed-snapshot C evidence for a target. Never raises.

    Returns ``(text, provenance_str)`` or ``(None, None)`` when no row
    covers the target. A ``See tools/re/data/decompiled/<F>.c`` pointer
    is followed to the committed ``.c`` file when readable, else the
    row text is served as-is (source always labelled).
    """
    want_va = str(va or "").lower()
    want_rva = decompile_cache.normalize_rva(rva) if rva else None
    for row in _committed_snapshot_functions():
        if not isinstance(row, dict):
            continue
        match = bool(want_va) and \
            str(row.get("address", "")).lower() == want_va
        if not match and want_rva and isinstance(row.get("rva"), str):
            match = decompile_cache.normalize_rva(row["rva"]) == want_rva
        if not match and name:
            match = row.get("name") == name
        if not match:
            continue
        ev = row.get("decompiled_evidence")
        if not isinstance(ev, str) or not ev.strip():
            continue
        who = row.get("name") or va
        found = _DECOMPILED_REF_RE.match(ev)
        if found:
            rel = found.group(1)
            try:
                with open(config.resolve(*rel.split("/"))) as fh:
                    text = fh.read()
            except (OSError, ValueError):
                text = ""
            if text.strip():
                return text, "%s (committed; snapshot row %s)" % (rel, who)
        return ev, "%s (committed; snapshot row %s)" % (_SNAPSHOT_REL,
                                                       who)
    return None, None


# --------------------------------------------------------------------------- #
# Identity / address helpers.
# --------------------------------------------------------------------------- #
def _binary_identity():
    # type: () -> dict
    """Identify the target binary. Never raises; degrades, never fails."""
    path = config.resolve("SPORE", "SporeBin", "SporeApp.exe")
    if not os.path.exists(path):
        return {"binary_sha256": "unknown", "binary_available": False,
                "note": "no_spo: SPORE/ absent; identity degraded, "
                        "cache keys use 'unknown'"}
    try:
        sha = config.binary_sha256(path)
    except (OSError, IOError) as exc:
        return {"binary_sha256": "unknown", "binary_available": False,
                "note": "no_spo: cannot hash SporeApp.exe: %s" % exc}
    return {"binary_sha256": sha, "binary_available": True}


def _program_name(params):
    # type: (dict) -> str
    raw = params.get("program", DEFAULT_PROGRAM)
    if isinstance(raw, str) and _PROGRAM_RE.match(raw):
        return raw
    return DEFAULT_PROGRAM


def _image_base(params):
    # type: (dict) -> int
    raw = params.get("image_base", IMAGE_BASE)
    try:
        base = int(str(raw), 0)
    except (TypeError, ValueError):
        return IMAGE_BASE
    return base if 0 < base < 0x100000000 else IMAGE_BASE


def _parse_int(text):
    # type: (object) -> int | None
    try:
        return int(str(text).strip(), 0)
    except (TypeError, ValueError):
        pass
    try:
        return int(str(text).strip(), 16)
    except (TypeError, ValueError):
        return None


def resolve_target(spec, image_base=IMAGE_BASE, force_rva=False):
    # type: (object, int, bool) -> dict
    """Split a function/address/rva spec into VA+RVA. Never raises.

    Hex/decimal values >= image_base are VAs, smaller values are RVAs;
    anything else is a symbol name. With ``force_rva`` (the explicit
    ``rva`` param) any integer is an RVA -- required because real RVAs
    (e.g. ``0xa806b0``) can exceed the image base, so the VA heuristic
    cannot apply. Returns ``{"ok": ...}`` or ``{"error": ...}`` (no
    exception -- callers map it to an in-band error).
    """
    if spec is None or (isinstance(spec, str) and not spec.strip()):
        return {"error": "empty function/address/rva/name spec"}
    if isinstance(spec, int):
        value = spec
    elif isinstance(spec, str):
        value = _parse_int(spec)
        if value is None:
            name = spec.strip()
            if len(name) > 256:
                return {"error": "name too long (max 256 chars)"}
            return {"ok": True, "name": name, "va": None, "rva": None}
    else:
        return {"error": "spec must be a hex address or symbol name"}
    if value < 0 or value >= 0x100000000:
        return {"error": "address out of 32-bit range: %r" % (spec,)}
    if force_rva:
        va = value + image_base
        if va >= 0x100000000:
            return {"error": "rva + image_base out of range: %r" % (spec,)}
        return {"ok": True, "name": None, "va": "0x%08x" % va,
                "rva": "0x%x" % value, "va_int": va, "rva_int": value}
    if value >= image_base:
        va, rva = value, value - image_base
    else:
        va, rva = value + image_base, value
    return {"ok": True, "name": None, "va": "0x%08x" % va,
            "rva": "0x%x" % rva, "va_int": va, "rva_int": rva}


def _target_from_params(params, image_base):
    # type: (dict, int) -> dict
    # The explicit 'rva' key is always an RVA (+image_base); the other
    # keys use the VA heuristic (values >= image base are VAs).
    if params.get("rva") not in (None, ""):
        return resolve_target(params["rva"], image_base, force_rva=True)
    for key in ("function", "address", "name"):
        if params.get(key) not in (None, ""):
            return resolve_target(params[key], image_base)
    return {"error": "one of 'function'/'address'/'rva'/'name' is required"}


def _resolve_name_to_va(client, name, limit=20):
    # type: (object, str, int) -> dict
    """Resolve a symbol name via /search_functions. Never raises."""
    try:
        resp = client.search_functions(name, limit)
    except Exception as exc:
        return {"error": "ghidra_offline: search failed: %s: %s"
                         % (type(exc).__name__, exc)}
    if not isinstance(resp, dict) or resp.get("status") != "ok":
        code = resp.get("code", "ghidra_offline") \
            if isinstance(resp, dict) else "ghidra_offline"
        return {"error": "%s: cannot resolve name %r (%s)"
                         % (code, name,
                            resp.get("message", "no detail")
                            if isinstance(resp, dict) else "no detail")}
    items = _as_list(resp)
    exact = [it for it in items
             if isinstance(it, dict) and it.get("name") == name]
    pool = exact or items
    if not pool:
        return {"error": "not_found: no function matches %r" % (name,)}
    addr = _first_address(pool[0])
    if addr is None:
        return {"error": "not_found: match for %r carries no address" % name}
    return resolve_target(addr)


# --------------------------------------------------------------------------- #
# REST payload normalisation (GhidraMCP shapes vary by endpoint/version).
# --------------------------------------------------------------------------- #
def _as_list(resp):
    # type: (dict) -> list
    for key in ("functions", "results", "data", "matches"):
        value = resp.get(key)
        if isinstance(value, list):
            return value
    data = resp.get("data")
    if isinstance(data, dict):
        for key in ("functions", "results", "matches"):
            value = data.get(key)
            if isinstance(value, list):
                return value
    return []


def _as_dict(resp):
    # type: (dict) -> dict
    data = resp.get("data", resp)
    if isinstance(data, dict):
        return data
    return {}


def _first_address(item):
    # type: (object) -> str | None
    if isinstance(item, str):
        return item if _parse_int(item) is not None else None
    if isinstance(item, dict):
        for key in ("address", "va", "entry", "addr"):
            value = item.get(key)
            if value is not None and _parse_int(value) is not None:
                return str(value)
    return None


def _extract_code(resp):
    # type: (dict) -> str | None
    """Pull C text out of a /decompile_function payload. Never raises."""
    if not isinstance(resp, dict):
        return None
    if isinstance(resp.get("raw"), str) and resp["raw"].strip():
        return resp["raw"]
    for key in ("decompiled", "decompilation", "c_code", "code",
                "decompile", "result"):
        value = resp.get(key)
        if isinstance(value, str) and value.strip():
            return value
    data = resp.get("data")
    if isinstance(data, str) and data.strip():
        return data
    if isinstance(data, dict):
        for key in ("decompiled", "decompilation", "c_code", "code"):
            value = data.get(key)
            if isinstance(value, str) and value.strip():
                return value
    return None


# --------------------------------------------------------------------------- #
# ghidra_decompile: disk-cached decompilation.
# --------------------------------------------------------------------------- #
def _cache_fallback_scan(binary_sha256, rva, program):
    # type: (str, str, str) -> dict
    """Offline fallback: any stored version for (binary?, rva, program).

    Used only when the live Ghidra version is unknown (bridge offline),
    so a changed live version still misses exactly per the cache key.
    Deterministic: candidates sorted, first wins. Never raises.
    """
    canon = decompile_cache.normalize_rva(rva)
    if canon is None:
        return {"hit": False, "reason": "no_entry"}
    root = decompile_cache.cache_root()
    base_dir = os.path.join(root, "decompiled")
    try:
        binary_dirs = sorted(os.listdir(base_dir))
    except OSError:
        return {"hit": False, "reason": "no_entry"}
    candidates = []
    for sub in binary_dirs:
        meta_path = os.path.join(base_dir, sub, canon + ".meta.json")
        c_path = os.path.join(base_dir, sub, canon + ".c")
        try:
            with open(meta_path) as fh:
                meta = json.load(fh)
        except (OSError, ValueError):
            continue
        if not isinstance(meta, dict):
            continue
        stored = meta.get("key", meta)
        if str(stored.get("rva", "")) != canon:
            continue
        if str(stored.get("program", "")) != program:
            continue
        if binary_sha256 != "unknown" and \
                str(stored.get("binary_sha256", "")) != binary_sha256:
            continue
        try:
            with open(c_path) as fh:
                text = fh.read()
        except OSError:
            continue
        candidates.append((str(stored.get("binary_sha256", "")),
                           str(stored.get("ghidra_version", "")), text, meta,
                           c_path))
    if not candidates:
        return {"hit": False, "reason": "no_entry"}
    candidates.sort()
    _sha, _ver, text, meta, c_path = candidates[0]
    return {"hit": True, "text": text, "meta": meta, "fallback": True,
            "c_path": c_path}


def ghidra_decompile(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    sha = identity["binary_sha256"]
    program = _program_name(params)
    base = _image_base(params)
    force = bool(params.get("force", False))
    target = _target_from_params(params, base)
    if "error" in target and "ok" not in target:
        return _error_envelope("invalid_params", target["error"],
                               _MODE_UNAVAILABLE, None, identity,
                               tool="ghidra_decompile", program=program,
                               image_base="0x%x" % base,
                               evidence_note=EVIDENCE_NOTE)
    client = _get_client()
    if target.get("name") and target.get("va") is None:
        res = _resolve_with_fallback(client, target, base)
        if "ok" not in res:
            return _error_envelope(
                res["code"], res["error"],
                _name_failure_mode(res["code"]),
                _name_failure_provenance(client, res["code"]),
                identity, tool="ghidra_decompile",
                program=program, image_base="0x%x" % base,
                candidates=res.get("candidates", []),
                snapshot_names=res.get("snapshot_names", []),
                evidence_note=EVIDENCE_NOTE)
        target = res["target"]
    rva, va = target["rva"], target["va"]

    version = params.get("ghidra_version")
    if not version:
        try:
            version = client.version()
        except Exception:
            version = "unknown"
    version = str(version or "unknown")

    if not force:
        hit = decompile_cache.lookup(sha, rva, version, program)
        if hit["hit"]:
            return _ok_envelope(
                identity, _MODE_CACHE,
                _cache_provenance_str(hit["meta"], hit.get("c_path")),
                program, base, status="ok", tool="ghidra_decompile",
                va=va, rva=decompile_cache.normalize_rva(rva),
                program=program, image_base="0x%x" % base,
                ghidra_version=hit["meta"].get(
                    "key", {}).get("ghidra_version", version),
                cached=True, cache="hit",
                decompiled=hit["text"],
                provenance_detail=hit["meta"],
                evidence_note=EVIDENCE_NOTE)
        if version == "unknown":
            # Offline: live version unknowable, serve any stored version
            # for (binary?, rva, program) with provenance intact.
            fallback = _cache_fallback_scan(sha, rva, program)
            if fallback["hit"]:
                return _ok_envelope(
                    identity, _MODE_CACHE,
                    _cache_provenance_str(fallback["meta"],
                                          fallback.get("c_path")),
                    program, base, status="ok", tool="ghidra_decompile",
                    va=va,
                    rva=decompile_cache.normalize_rva(rva),
                    program=program, image_base="0x%x" % base,
                    ghidra_version=fallback["meta"].get(
                        "key", {}).get("ghidra_version", "unknown"),
                    cached=True, cache="hit-offline-fallback",
                    decompiled=fallback["text"],
                    provenance_detail=fallback["meta"],
                    evidence_note=EVIDENCE_NOTE,
                    note="Ghidra offline; served from disk cache "
                         "(stored key retained in provenance_detail)")
    live_code, live_msg, live_hint = None, None, None
    try:
        resp = client.decompile(va)
    except Exception as exc:
        resp = None
        live_code, live_msg = (
            "ghidra_offline",
            "GhidraMCP request failed: %s: %s"
            % (type(exc).__name__, exc))
    if live_code is None:
        if not isinstance(resp, dict) or resp.get("status") != "ok":
            live_code = resp.get("code", "ghidra_offline") \
                if isinstance(resp, dict) else "ghidra_offline"
            detail = resp.get("message", "no detail") \
                if isinstance(resp, dict) else "no detail"
            live_msg = "decompile %s failed: %s" % (va, detail)
            live_hint = resp.get("hint") if isinstance(resp, dict) \
                else None
    code_text = _extract_code(resp) if live_code is None else None
    if live_code is None and not code_text:
        live_code, live_msg = (
            "empty_decompile",
            "Ghidra returned no decompilation text for %s" % va)
    if live_code is not None:
        # Live failed: committed fallbacks before admitting failure
        # (symmetric with ghidra_function's snapshot card): disk scan
        # when the live version is unknowable (unless force bypasses
        # the cache), then the snapshot row.
        if version == "unknown" and not force:
            fallback = _cache_fallback_scan(sha, rva, program)
            if fallback["hit"]:
                return _ok_envelope(
                    identity, _MODE_CACHE,
                    _cache_provenance_str(fallback["meta"],
                                          fallback.get("c_path")),
                    program, base, status="ok", tool="ghidra_decompile",
                    va=va,
                    rva=decompile_cache.normalize_rva(rva),
                    program=program, image_base="0x%x" % base,
                    ghidra_version=fallback["meta"].get(
                        "key", {}).get("ghidra_version", "unknown"),
                    cached=True, cache="hit-offline-fallback",
                    decompiled=fallback["text"],
                    provenance_detail=fallback["meta"],
                    evidence_note=EVIDENCE_NOTE,
                    note="Ghidra offline; served from disk cache "
                         "(stored key retained in provenance_detail)")
        snap_text, snap_prov = _snapshot_decompiled(
            va, rva, target.get("name"))
        if snap_text:
            return _ok_envelope(
                identity, _MODE_SNAPSHOT, snap_prov, program, base,
                status="ok", tool="ghidra_decompile",
                va=va, rva=decompile_cache.normalize_rva(rva),
                program=program, image_base="0x%x" % base,
                ghidra_version=version,
                cached=False, cache="snapshot-fallback",
                decompiled=snap_text,
                evidence_note=EVIDENCE_NOTE,
                note="Ghidra decompile failed (%s); served from "
                     "committed snapshot" % live_code)
        return _error_envelope(
            live_code, live_msg,
            _MODE_OFFLINE if live_code == "ghidra_offline"
            else _MODE_LIVE,
            _rest_provenance(client, "/decompile_function"),
            identity, tool="ghidra_decompile", va=va, rva=rva,
            program=program, image_base="0x%x" % base,
            hint=live_hint)
    stored = decompile_cache.store(
        sha, rva, version, program, code_text,
        extra={"va": va, "image_base": "0x%x" % base})
    return _ok_envelope(
        identity, _MODE_LIVE,
        _rest_provenance(client, "/decompile_function"), program, base,
        status="ok", tool="ghidra_decompile",
        va=va, rva=decompile_cache.normalize_rva(rva),
        program=program, image_base="0x%x" % base,
        ghidra_version=version,
        cached=False, cache="miss",
        decompiled=code_text,
        cache_store=stored.get("stored", False),
        evidence_note=EVIDENCE_NOTE)


# --------------------------------------------------------------------------- #
# ghidra_function: metadata card (MCP-DESIGN §F shape).
# --------------------------------------------------------------------------- #
def _committed_snapshot_functions():
    # type: () -> list
    path = config.resolve("tools", "re", "data",
                          "ghidra_snapshot_cell_movement.json")
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except (OSError, ValueError):
        return []
    funcs = doc.get("functions")
    return funcs if isinstance(funcs, list) else []


def _vtable_join(va_int):
    # type: (int) -> dict
    """Join vtables.json evidence for one VA. Never raises."""
    doc = _load_vtables()
    va_hex = "0x%08x" % va_int
    at_here, referencing, sdk = [], [], []
    try:
        candidates = doc.get("candidates", [])
    except AttributeError:
        candidates = []
    if not isinstance(candidates, list):
        candidates = []
    for cand in candidates:
        if not isinstance(cand, dict):
            continue
        addr = str(cand.get("address", "")).lower()
        slots = cand.get("slots", [])
        slot_ptrs = []
        if isinstance(slots, list):
            for slot in slots:
                ptr = slot.get("ptr") if isinstance(slot, dict) else slot
                if ptr is not None:
                    slot_ptrs.append(str(ptr).lower())
        if addr == va_hex:
            at_here.append({"address": cand.get("address"),
                            "slots": cand.get("slots")
                            if isinstance(cand.get("slots"), int)
                            else len(slot_ptrs),
                            "confidence": cand.get("confidence"),
                            "namespace": cand.get("namespace")})
        elif va_hex in slot_ptrs:
            referencing.append(cand.get("address"))
    try:
        assocs = doc.get("sdk_associations", [])
    except AttributeError:
        assocs = []
    if not isinstance(assocs, list):
        assocs = []
    for assoc in assocs:
        if not isinstance(assoc, dict):
            continue
        if str(assoc.get("address", "")).lower() == va_hex:
            sdk.append({"address": assoc.get("address"),
                        "subsystems": assoc.get("subsystems", []),
                        "sdk_funcs": (assoc.get("sdkFuncs", []) or [])[:10]})
    return {"vtable_at": at_here, "referenced_by_vtables": referencing[:20],
            "sdk_associations": sdk}


def ghidra_function(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    program = _program_name(params)
    base = _image_base(params)
    target = _target_from_params(params, base)
    if "error" in target and "ok" not in target:
        return _error_envelope("invalid_params", target["error"],
                               _MODE_UNAVAILABLE, None, identity,
                               tool="ghidra_function", program=program,
                               image_base="0x%x" % base,
                               evidence_note=EVIDENCE_NOTE)
    client = _get_client()
    if target.get("name") and target.get("va") is None:
        res = _resolve_with_fallback(client, target, base)
        if "ok" not in res:
            return _error_envelope(
                res["code"], res["error"],
                _name_failure_mode(res["code"]),
                _name_failure_provenance(client, res["code"]),
                identity, tool="ghidra_function",
                program=program, image_base="0x%x" % base,
                candidates=res.get("candidates", []),
                snapshot_names=res.get("snapshot_names", []),
                evidence_note=EVIDENCE_NOTE)
        target = res["target"]
    va = target.get("va")
    if va is not None and va in _FUNCTION_MEMO:
        card = dict(_FUNCTION_MEMO[va])
        card["mode"] = _MODE_CACHE
        card["provenance"] = "in-session memo (originally: %s)" % (
            card.get("provenance", "unknown"),)
        card.update(identity)
        return card

    info, analysis = None, None
    online = va is not None
    if online:
        try:
            info = client.function_by_address(va)
            analysis = client.analyze_function(va)
        except Exception:
            info, analysis = None, None
    info_d = _as_dict(info) if isinstance(info, dict) else {}
    if isinstance(info, dict) and info.get("status") != "ok":
        info_d = {}
    analysis_d = _as_dict(analysis) \
        if isinstance(analysis, dict) else {}
    if isinstance(analysis, dict) and analysis.get("status") != "ok":
        analysis_d = {}

    if not info_d and not analysis_d:
        # Offline/degraded: serve the committed snapshot row when it
        # covers this target, else a justified ghidra_offline.
        for row in _committed_snapshot_functions():
            if not isinstance(row, dict):
                continue
            match = (va is not None and
                     str(row.get("address", "")).lower() == va.lower())
            name = target.get("name") or params.get("name")
            if not match and name:
                match = row.get("name") == name
            if match:
                return _ok_envelope(
                    identity, _MODE_SNAPSHOT, _SNAPSHOT_PROVENANCE,
                    program, base, status="ok", tool="ghidra_function",
                    va=row.get("address"), rva=row.get("rva"),
                    name=row.get("name"), program=program,
                    image_base="0x%x" % base,
                    size_bytes=row.get("size_bytes"),
                    namespace=row.get("namespace"),
                    signature=row.get("signature"),
                    dispatch=row.get("dispatch"),
                    callers=row.get("callers"),
                    callees=row.get("callees"),
                    sdk_name=None, sdk_type=None,
                    subsystem=None,
                    evidence_note=EVIDENCE_NOTE,
                    note="served from committed snapshot; Ghidra "
                         "offline or no live data for target")
        return _error_envelope(
            "ghidra_offline",
            "Ghidra unreachable and no committed snapshot covers "
            "%r" % (va or target.get("name"),),
            _MODE_OFFLINE,
            _rest_provenance(client, "/get_function_by_address")
            + " (unreachable) + " + _SNAPSHOT_PROVENANCE + " (no row)",
            identity, tool="ghidra_function", program=program,
            image_base="0x%x" % base)

    merged = dict(info_d)
    for key, value in analysis_d.items():
        merged.setdefault(key, value)
    va_int = _parse_int(va) if va is not None else None
    join = _vtable_join(va_int) if va_int is not None else \
        {"vtable_at": [], "referenced_by_vtables": [],
         "sdk_associations": []}
    card = _ok_envelope(
        identity, _MODE_LIVE,
        _rest_provenance(client, "/get_function_by_address + "
                                 "/analyze_function_complete"),
        program, base, status="ok", tool="ghidra_function",
        va=va, rva=target.get("rva"),
        name=merged.get("name") or target.get("name"),
        program=program, image_base="0x%x" % base,
        size_bytes=merged.get("size_bytes", merged.get("size")),
        namespace=merged.get("namespace"),
        signature=merged.get("signature"),
        dispatch=merged.get("dispatch"),
        callers=merged.get("callers"),
        callees=merged.get("callees"),
        sdk_name=merged.get("sdk_name"),
        sdk_type=merged.get("sdk_type"),
        subsystem=merged.get("subsystem"),
        vtables=join,
        evidence_note=EVIDENCE_NOTE)
    if va is not None:
        _FUNCTION_MEMO[va] = {k: v for k, v in card.items()
                              if k not in identity}
    return card


# --------------------------------------------------------------------------- #
# ghidra_search: name-pattern search (S2.1 scope C: search_status + truncated).
#
# search_status values (exactly these four; no second index exists, the
# bridge answers substring matches only, and bridge failure is already
# the ghidra_offline/ghidra_no_endpoint code family):
#   * "matched" -- live index consulted, >= 1 hit;
#   * "matched_zero" -- live index consulted, 0 hits (ok with count 0;
#     carries a hint with an SDK-prefix suggestion);
#   * "offline_no_index" -- bridge down (ghidra_offline error path);
#   * "invalid_query" -- invalid_params error path (empty/too-long
#     pattern, non-integer limit).
# "truncated" is True when the live index returned more rows than
# ``limit`` (matches are then the first ``limit`` after the deterministic
# sort). Additive keys only: count/status/mode/provenance shapes stay.
# --------------------------------------------------------------------------- #
_SEARCH_ZERO_HINT = (
    "live index consulted, 0 hits; try an SDK-prefixed substring "
    "(e.g. 'App::', 'cCell', 'FUN_') or check the pattern spelling")
def ghidra_search(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    program = _program_name(params)
    base = _image_base(params)
    pattern = params.get("pattern", params.get("query", ""))
    if not isinstance(pattern, str) or not pattern.strip():
        return _error_envelope(
            "invalid_params",
            "'pattern' (name substring) is required and non-empty",
            _MODE_UNAVAILABLE, None, identity,
            tool="ghidra_search", program=program,
            image_base="0x%x" % base,
            search_status="invalid_query")
    pattern = pattern.strip()
    if len(pattern) > 256:
        return _error_envelope(
            "invalid_params", "'pattern' too long (max 256 chars)",
            _MODE_UNAVAILABLE, None, identity,
            tool="ghidra_search", program=program,
            image_base="0x%x" % base,
            search_status="invalid_query")
    try:
        limit = int(params.get("limit", 50))
    except (TypeError, ValueError):
        return _error_envelope(
            "invalid_params", "'limit' must be an integer",
            _MODE_UNAVAILABLE, None, identity,
            tool="ghidra_search", program=program,
            image_base="0x%x" % base,
            search_status="invalid_query")
    limit = max(1, min(limit, 500))
    client = _get_client()
    try:
        resp = client.search_functions(pattern, limit)
    except Exception as exc:
        return _error_envelope(
            "ghidra_offline",
            "GhidraMCP request failed: %s: %s"
            % (type(exc).__name__, exc),
            _MODE_OFFLINE,
            _rest_provenance(client, "/search_functions")
            + " (unreachable)",
            identity, tool="ghidra_search", pattern=pattern,
            program=program, image_base="0x%x" % base,
            search_status="offline_no_index")
    if not isinstance(resp, dict) or resp.get("status") != "ok":
        code = resp.get("code", "ghidra_offline") \
            if isinstance(resp, dict) else "ghidra_offline"
        extra_status = "offline_no_index" \
            if code == "ghidra_offline" else None
        return _error_envelope(
            code, resp.get("message", "search failed")
            if isinstance(resp, dict) else "search failed",
            _MODE_OFFLINE if code == "ghidra_offline" else _MODE_LIVE,
            _rest_provenance(client, "/search_functions"),
            identity, tool="ghidra_search", pattern=pattern,
            program=program, image_base="0x%x" % base,
            hint=resp.get("hint") if isinstance(resp, dict)
            else None,
            **({"search_status": extra_status}
               if extra_status is not None else {}))
    items = _as_list(resp)
    truncated = len(items) > limit
    matches = []
    for item in items[:limit]:
        if isinstance(item, dict):
            matches.append({
                "name": item.get("name"),
                "address": item.get("address", item.get("va")),
                "namespace": item.get("namespace")})
        else:
            matches.append({"name": str(item), "address": None,
                            "namespace": None})
    matches.sort(key=lambda m: (str(m.get("name")),
                                str(m.get("address"))))
    if matches:
        return _ok_envelope(
            identity, _MODE_LIVE,
            _rest_provenance(client, "/search_functions"), program, base,
            status="ok", tool="ghidra_search",
            pattern=pattern, program=program, image_base="0x%x" % base,
            matches=matches, count=len(matches),
            truncated=truncated, search_status="matched")
    return _ok_envelope(
        identity, _MODE_LIVE,
        _rest_provenance(client, "/search_functions"), program, base,
        status="ok", tool="ghidra_search",
        pattern=pattern, program=program, image_base="0x%x" % base,
        matches=[], count=0,
        truncated=truncated, search_status="matched_zero",
        hint=_SEARCH_ZERO_HINT)


# --------------------------------------------------------------------------- #
# ghidra_snapshot_save: deterministic capture writer.
# --------------------------------------------------------------------------- #
_SNAPSHOT_NOTE = (
    "Decompiler output is EVIDENCE, NOT TRUTH: Ghidra has no MSVC RTTI "
    "for this binary, so many callee types are mis-attributed. SDK symbol "
    "names are CONFIRMED via the march2017 SDK XML import; FUN_* names "
    "are Ghidra autogen (address-based) and are NOT real names. "
    "RVA = address - image_base.")


def _snapshot_functions(params, client, sha, program, base, version):
    # type: (dict, object, str, str, int, str) -> tuple
    """Build snapshot function rows. Never raises.

    Returns (rows, offline_count). Each row carries its own
    ``decompiled_evidence`` (C text, cached or live) or an explicit
    null + ``evidence_note`` when Ghidra is offline and uncached.
    """
    raw_funcs = params.get("functions", params.get("addresses"))
    specs = []
    if isinstance(raw_funcs, list):
        specs = raw_funcs
    elif isinstance(raw_funcs, str) and raw_funcs.strip():
        specs = [raw_funcs]
    elif params.get("topic") == "cell-movement" or \
            params.get("label") == "cell-movement":
        specs = [row.get("address")
                 for row in _committed_snapshot_functions()
                 if isinstance(row, dict) and row.get("address")]
    rows, offline = [], 0
    for spec in specs:
        target = resolve_target(spec, base)
        if "ok" not in target:
            rows.append({"spec": spec, "error": target.get("error")})
            continue
        if target.get("name") and target.get("va") is None:
            resolved = _resolve_name_to_va(client, target["name"])
            if "ok" in resolved:
                target = resolved
            else:
                rows.append({"spec": spec, "name": target.get("name"),
                             "decompiled_evidence": None,
                             "evidence_note": resolved.get("error")})
                offline += 1
                continue
        va, rva = target["va"], target["rva"]
        hit = decompile_cache.lookup(sha, rva, version, program)
        if not hit["hit"] and version == "unknown":
            hit = _cache_fallback_scan(sha, rva, program)
        text = hit["text"] if hit["hit"] else None
        if text is None:
            try:
                resp = client.decompile(va)
            except Exception:
                resp = {"status": "error", "code": "ghidra_offline"}
            text = _extract_code(resp) \
                if isinstance(resp, dict) and resp.get("status") == "ok" \
                else None
            if text is not None:
                decompile_cache.store(sha, rva, version, program, text,
                                      extra={"va": va})
        row = {"name": target.get("name") or va, "address": va,
               "rva": decompile_cache.normalize_rva(rva),
               "decompiled_evidence": text}
        if text is None:
            row["evidence_note"] = \
                "ghidra_offline: no cached decompilation for %s" % va
            offline += 1
        rows.append(row)
    rows.sort(key=lambda r: str(r.get("address", r.get("spec", ""))))
    return rows, offline


def ghidra_snapshot_save(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    sha = identity["binary_sha256"]
    program = _program_name(params)
    base = _image_base(params)
    topic = params.get("topic", params.get("label", ""))
    if not isinstance(topic, str) or not _TOPIC_RE.match(topic):
        return _error_envelope(
            "invalid_params",
            "'topic' (or 'label') is required: "
            "[A-Za-z0-9][A-Za-z0-9_-]*",
            _MODE_UNAVAILABLE, None, identity,
            tool="ghidra_snapshot_save", program=program,
            image_base="0x%x" % base)
    client = _get_client()
    try:
        version = client.version()
    except Exception:
        version = "unknown"
    version = str(version or "unknown")

    rows, offline = _snapshot_functions(params, client, sha, program,
                                        base, version)
    if not rows:
        return _error_envelope(
            "blocked_no_functions",
            "snapshot %r has no function list and no committed "
            "snapshot to default from; pass 'functions' "
            "(addresses/names). Upstream capture script "
            "tools/re/ghidra_snapshot.py does not exist "
            "(RE-AUTOMATION-ARCHITECTURE.md §2 weakness 2), so "
            "new topics cannot be enumerated from Ghidra here."
            % topic,
            _MODE_UNAVAILABLE,
            _SNAPSHOT_PROVENANCE + " (no default rows)",
            identity, tool="ghidra_snapshot_save", topic=topic,
            program=program, image_base="0x%x" % base)
    if offline and offline == len(rows):
        return _error_envelope(
            "ghidra_offline",
            "Ghidra unreachable and no cached decompilation for "
            "any of the %d function(s); snapshot %r blocked "
            "(not written). Populate tools/mcp/cache/ while "
            "online, or work from the committed snapshot."
            % (len(rows), topic),
            _MODE_OFFLINE,
            _rest_provenance(client, "/decompile_function")
            + " (unreachable); disk cache empty for target(s)",
            identity, tool="ghidra_snapshot_save", topic=topic,
            program=program, image_base="0x%x" % base)
    doc = {"$schema": _SNAPSHOT_SCHEMA,
           "source": "Ghidra 12.1.2 headless (%s, via GhidraMCP REST; "
                     "saved by tools/mcp/ghidra_tools.py "
                     "ghidra_snapshot_save)" % program,
           "image_base": "0x%x" % base,
           "note": _SNAPSHOT_NOTE,
           "functions": rows,
           "meta": {"binary_sha256": sha, "ghidra_version": version,
                    "program": program,
                    "offline_functions": offline,
                    "source_rest": client.base
                    if hasattr(client, "base") else "unknown"},
           "image_base_note": "RVA = address - image_base."}
    text = json.dumps(doc, indent=2, sort_keys=True) + "\n"
    out_dir = config.resolve("tools", "re", "data")
    out_path = os.path.join(out_dir, "ghidra_snapshot_%s.json" % topic)
    digest = hashlib.sha256(text.encode("utf-8")).hexdigest()
    save_mode = _MODE_LIVE if version != "unknown" else _MODE_CACHE
    save_prov = _repo_rel(out_path) + " (written)"
    try:
        os.makedirs(out_dir, exist_ok=True)
        if os.path.exists(out_path):
            with open(out_path) as fh:
                previous = fh.read()
            if previous == text:
                return _ok_envelope(
                    identity, save_mode, save_prov, program, base,
                    status="ok", tool="ghidra_snapshot_save",
                    topic=topic, path=out_path,
                    outcome="unchanged", sha256=digest,
                    functions=len(rows),
                    offline_functions=offline, program=program,
                    image_base="0x%x" % base)
            outcome = "changed"
        else:
            outcome = "created"
        with open(out_path, "w") as fh:
            fh.write(text)
    except OSError as exc:
        return _error_envelope(
            "write_failed", "cannot write snapshot: %s" % exc,
            _MODE_UNAVAILABLE, save_prov, identity,
            tool="ghidra_snapshot_save", topic=topic,
            program=program, image_base="0x%x" % base)
    return _ok_envelope(
        identity, save_mode, save_prov, program, base,
        status="ok", tool="ghidra_snapshot_save",
        topic=topic, path=out_path, outcome=outcome,
        sha256=digest, functions=len(rows),
        offline_functions=offline, program=program,
        image_base="0x%x" % base)


def _is_true(value):
    # type: (object) -> bool
    """Deterministic truth flag for optional MCP booleans.

    Accepts real JSON booleans/ints plus the common string spellings;
    anything else (including the string "false") is False. Never raises.
    """
    if isinstance(value, bool):
        return value
    if isinstance(value, (int, float)):
        return value == 1
    if isinstance(value, str):
        return value.strip().lower() in ("1", "true", "yes", "on")
    return False


def _strip_nones(mapping):
    # type: (dict) -> dict
    """Drop None/null-valued keys deterministically. Never infers."""
    return {k: v for k, v in mapping.items() if v is not None}


def _slim_slot(slot):
    # type: (object) -> dict
    """Project one vtable slot to its {ptr, func} identity pair.

    Non-dict entries carry no func identity: they become a ptr-only
    dict (never inferred). None-valued keys are stripped.
    """
    if isinstance(slot, dict):
        return _strip_nones({"ptr": slot.get("ptr"),
                             "func": slot.get("func")})
    return {"ptr": slot}


# --------------------------------------------------------------------------- #
# vtable_lookup: read-only over docs/analysis/vtables.json.
#
# Context slimming (S2.1 scope G, deterministic only, no summarizer):
#   * slots project to {ptr, func} pairs; None-valued match keys are
#     stripped (never inferred); null/empty slot arrays are omitted;
#   * default limit is 20 (cap stays 500); total_matches + truncated
#     always report the bound, so nothing is silently truncated;
#   * detail=true (alias full_slots=true) returns the full slot dicts
#     and un-stripped match dicts, still bounded by limit.
# Envelope identity (mode/provenance/binary_sha256/image_base) stays.
# --------------------------------------------------------------------------- #
def _load_vtables():
    # type: () -> dict
    if _VTABLES_DOC["loaded"]:
        return _VTABLES_DOC["doc"] or {}
    path = config.resolve("docs", "analysis", "vtables.json")
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except (OSError, ValueError):
        doc = {}
    if not isinstance(doc, dict):
        doc = {}
    _VTABLES_DOC["doc"] = doc
    _VTABLES_DOC["loaded"] = True
    return doc


def vtable_lookup(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    doc = _load_vtables()
    if not doc:
        return _error_envelope(
            "no_vtables",
            "docs/analysis/vtables.json missing or unparseable",
            _MODE_UNAVAILABLE, _VTABLES_REL + " (missing or unparseable)",
            identity, tool="vtable_lookup")
    klass = params.get("class", params.get("class_name", ""))
    address = params.get("address", "")
    namespace = params.get("namespace", "")
    subsystem = params.get("subsystem", "")
    try:
        limit = int(params.get("limit", 20))
    except (TypeError, ValueError):
        return _error_envelope(
            "invalid_params", "'limit' must be an integer",
            _MODE_UNAVAILABLE, None, identity,
            tool="vtable_lookup")
    limit = max(1, min(limit, 500))
    if not any(isinstance(v, str) and v.strip()
               for v in (klass, address, namespace, subsystem)):
        return _error_envelope(
            "invalid_params",
            "one of 'class'/'address'/'namespace'/'subsystem' "
            "is required",
            _MODE_UNAVAILABLE, None, identity,
            tool="vtable_lookup")
    addr_norm = None
    if isinstance(address, str) and address.strip():
        addr_int = _parse_int(address.strip())
        if addr_int is None:
            return _error_envelope(
                "invalid_params",
                "'address' must be hex, got %r" % (address,),
                _MODE_UNAVAILABLE, None, identity,
                tool="vtable_lookup")
        addr_norm = "0x%08x" % addr_int
    candidates = doc.get("candidates", [])
    if not isinstance(candidates, list):
        candidates = []
    matches = []
    for cand in candidates:
        if not isinstance(cand, dict):
            continue
        keep = True
        if addr_norm is not None:
            keep = str(cand.get("address", "")).lower() == addr_norm
        if keep and isinstance(namespace, str) and namespace.strip():
            keep = namespace.strip().lower() in \
                str(cand.get("namespace", "")).lower()
        if keep and isinstance(subsystem, str) and subsystem.strip():
            assocs = doc.get("sdk_associations", [])
            sub_hit = False
            if isinstance(assocs, list):
                for assoc in assocs:
                    if not isinstance(assoc, dict):
                        continue
                    if str(assoc.get("address", "")).lower() == \
                            str(cand.get("address", "")).lower():
                        subs = assoc.get("subsystems", []) or []
                        if subsystem.strip() in subs:
                            sub_hit = True
                            break
            keep = sub_hit
        if keep and isinstance(klass, str) and klass.strip():
            needle = klass.strip().lower()
            hay = " ".join([
                str(cand.get("namespace", "")),
                str(cand.get("firstSlotFunc", ""))] +
                [str(s.get("func", "")) for s in
                 (cand.get("slots", []) or [])[:10]
                 if isinstance(s, dict)]).lower()
            keep = needle in hay
        if keep:
            slots = cand.get("slots")
            if _is_true(params.get("detail", False)) or \
                    _is_true(params.get("full_slots", False)):
                match = {
                    "address": cand.get("address"),
                    "slots": slots,
                    "confidence": cand.get("confidence"),
                    "namespace": cand.get("namespace"),
                    "firstSlotFunc": cand.get("firstSlotFunc")}
            else:
                match = _strip_nones({
                    "address": cand.get("address"),
                    "confidence": cand.get("confidence"),
                    "namespace": cand.get("namespace"),
                    "firstSlotFunc": cand.get("firstSlotFunc")})
                if isinstance(slots, list) and slots:
                    match["slots"] = [_slim_slot(s) for s in slots]
            matches.append(match)
    matches.sort(key=lambda m: str(m.get("address")))
    meta = doc.get("meta", {}) if isinstance(doc.get("meta"), dict) \
        else {}
    total_matches = len(matches)
    truncated = total_matches > limit
    result = {"status": "ok", "tool": "vtable_lookup",
              "mode": _MODE_SNAPSHOT, "provenance": _VTABLES_PROVENANCE,
              "source": "docs/analysis/vtables.json",
              "image_base": meta.get("image_base"),
              "total_candidates": len(candidates),
              "matches": matches[:limit], "count": min(total_matches,
                                                       limit),
              "total_matches": total_matches, "truncated": truncated,
              "limit": limit}
    result.update(identity)
    return result


# --------------------------------------------------------------------------- #
# dossier_read / dossier_regenerate: read-only + deterministic writers over
# docs/analysis/dossiers/ (constrained paths, no shell).
#
# Context slimming (S2.1 scope G, deterministic only, no summarizer):
#   * markdown stays opt-in (md=true); the default read carries the JSON
#     dossier only;
#   * section selects one top-level key; keys[] projects a deterministic
#     subset of top-level keys (dossier file order, echo sorted);
#     section and keys are mutually exclusive;
#   * large evidence blobs are compacted by default -- long strings and
#     long lists become {truncated:true, kind, length/count, preview/
#     items head, ref} -- and restored verbatim with expand=true;
#     compaction is always flagged (truncated + truncated_paths +
#     expand_hint), never silent; evidence is never destroyed;
#   * focused section reads carry only that section (no duplication of
#     sibling decompile/caller/callee payloads); every success lists
#     available_sections.
# Envelope identity (mode/provenance/binary_sha256/path) stays.
# --------------------------------------------------------------------------- #
_DOSSIER_STR_BLOB_LIMIT = 2000
_DOSSIER_LIST_BLOB_LIMIT = 100
_DOSSIER_PREVIEW_CHARS = 200
_DOSSIER_EXPAND_HINT = ("truncated: re-call dossier_read with the same "
                        "topic/section/keys plus expand=true for the "
                        "full evidence")


def _compact_dossier_value(value, ref, expand, truncated_paths):
    # type: (object, str, bool, list) -> object
    """Compact one dossier value deterministically. Never raises.

    Strings longer than _DOSSIER_STR_BLOB_LIMIT and lists longer than
    _DOSSIER_LIST_BLOB_LIMIT become compact summaries (head +
    length/count + ref) unless expand is true. Dicts recurse with
    extended refs. Every compaction appends its ref to
    truncated_paths. With expand=true the value passes through
    untouched (full evidence path).
    """
    if expand:
        return value
    if isinstance(value, str):
        if len(value) > _DOSSIER_STR_BLOB_LIMIT:
            truncated_paths.append(ref)
            return {"truncated": True, "kind": "text",
                    "length": len(value),
                    "preview": value[:_DOSSIER_PREVIEW_CHARS],
                    "ref": ref}
        return value
    if isinstance(value, list):
        if len(value) > _DOSSIER_LIST_BLOB_LIMIT:
            truncated_paths.append(ref)
            head = [_compact_dossier_value(
                item, "%s[%d]" % (ref, i), expand, truncated_paths)
                for i, item in enumerate(
                    value[:_DOSSIER_LIST_BLOB_LIMIT])]
            return {"truncated": True, "kind": "list",
                    "count": len(value), "items": head,
                    "ref": ref}
        return [_compact_dossier_value(
            item, "%s[%d]" % (ref, i), expand, truncated_paths)
            for i, item in enumerate(value)]
    if isinstance(value, dict):
        return {k: _compact_dossier_value(
            v, "%s.%s" % (ref, k), expand, truncated_paths)
            for k, v in value.items()}
    return value


def _dossier_dir():
    # type: () -> str
    return config.resolve("docs", "analysis", "dossiers")


def _dossier_topic(params):
    # type: (dict) -> str | None
    raw = params.get("topic", params.get("path", ""))
    if not isinstance(raw, str):
        return None
    text = raw.strip()
    # Reject path separators / parent refs outright (never basename-strip:
    # "a/b" must not silently become dossier "b").
    if not text or "/" in text or "\\" in text or ".." in text:
        return None
    name = text
    if name.endswith(".json"):
        name = name[:-5]
    elif name.endswith(".md"):
        name = name[:-3]
    if not _TOPIC_RE.match(name):
        return None
    return name


def _available_topics():
    # type: () -> list
    try:
        files = glob.glob(os.path.join(_dossier_dir(), "*.json"))
    except Exception:
        return []
    return sorted(os.path.splitext(os.path.basename(p))[0] for p in files)


def dossier_read(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    topic = _dossier_topic(params)
    if topic is None:
        return _error_envelope(
            "invalid_params",
            "'topic' (or 'path') must name a dossier "
            "([A-Za-z0-9][A-Za-z0-9_-]*); no directories, "
            "no shell",
            _MODE_UNAVAILABLE, None, identity,
            tool="dossier_read",
            available_topics=_available_topics())
    path = os.path.join(_dossier_dir(), topic + ".json")
    rel = _repo_rel(path)
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except IOError:
        return _error_envelope(
            "not_found", "no dossier for topic %r" % topic,
            _MODE_UNAVAILABLE, rel + " (missing)", identity,
            tool="dossier_read",
            available_topics=_available_topics())
    except ValueError as exc:
        return _error_envelope(
            "corrupt_dossier",
            "dossier %r is not valid JSON: %s" % (topic, exc),
            _MODE_UNAVAILABLE, rel + " (unparseable)", identity,
            tool="dossier_read", topic=topic)
    if not isinstance(doc, dict):
        return _error_envelope(
            "corrupt_dossier",
            "dossier %r is not a JSON object" % topic,
            _MODE_UNAVAILABLE, rel + " (unparseable)", identity,
            tool="dossier_read", topic=topic)
    section = params.get("section")
    keys = params.get("keys", params.get("selection"))
    expand = _is_true(params.get("expand", False)) or \
        _is_true(params.get("full", False))
    if section is not None and keys is not None:
        return _error_envelope(
            "invalid_params",
            "'section' and 'keys' are mutually exclusive: pass one "
            "focused selector (or neither for the whole dossier)",
            _MODE_SNAPSHOT, rel + " (committed)", identity,
            tool="dossier_read", topic=topic,
            available_sections=sorted(doc.keys()))
    base_ref = rel + "#" + topic
    truncated_paths = []  # type: list
    if section is not None:
        if not isinstance(section, str) or section not in doc:
            return _error_envelope(
                "no_section",
                "dossier %r has no section %r" % (topic, section),
                _MODE_SNAPSHOT, rel + " (committed)", identity,
                tool="dossier_read", topic=topic,
                available_sections=sorted(doc.keys()))
        data = _compact_dossier_value(doc[section],
                                      base_ref + "." + section,
                                      expand, truncated_paths)
        result = {"status": "ok", "tool": "dossier_read", "topic": topic,
                  "mode": _MODE_SNAPSHOT,
                  "provenance": rel + " (committed)",
                  "path": path, "section": section,
                  "data": data,
                  "available_sections": sorted(doc.keys())}
    elif keys is not None:
        if isinstance(keys, str):
            keys = [keys]
        if not isinstance(keys, list) or not keys or not all(
                isinstance(k, str) for k in keys):
            return _error_envelope(
                "invalid_params",
                "'keys' must be a non-empty array of top-level "
                "dossier key names",
                _MODE_SNAPSHOT, rel + " (committed)", identity,
                tool="dossier_read", topic=topic,
                available_sections=sorted(doc.keys()))
        unknown = [k for k in keys if k not in doc]
        if unknown:
            return _error_envelope(
                "no_section",
                "dossier %r has no key(s) %s" % (topic, sorted(unknown)),
                _MODE_SNAPSHOT, rel + " (committed)", identity,
                tool="dossier_read", topic=topic,
                available_sections=sorted(doc.keys()))
        wanted = set(keys)
        projected = {k: _compact_dossier_value(doc[k], base_ref + "." + k,
                                               expand, truncated_paths)
                     for k in doc if k in wanted}
        result = {"status": "ok", "tool": "dossier_read", "topic": topic,
                  "mode": _MODE_SNAPSHOT,
                  "provenance": rel + " (committed)",
                  "path": path, "keys": sorted(wanted),
                  "dossier": projected,
                  "available_sections": sorted(doc.keys())}
    else:
        dossier = {k: _compact_dossier_value(doc[k], base_ref + "." + k,
                                             expand, truncated_paths)
                   for k in doc}
        result = {"status": "ok", "tool": "dossier_read", "topic": topic,
                  "mode": _MODE_SNAPSHOT,
                  "provenance": rel + " (committed)",
                  "path": path, "dossier": dossier,
                  "available_sections": sorted(doc.keys())}
    truncated = bool(truncated_paths)
    result["truncated"] = truncated
    if truncated:
        result["truncated_paths"] = sorted(truncated_paths)
        result["expand_hint"] = _DOSSIER_EXPAND_HINT
    result.update(identity)
    if _is_true(params.get("md", False)):
        md_path = os.path.join(_dossier_dir(), topic + ".md")
        try:
            with open(md_path) as fh:
                result["markdown"] = fh.read()
        except IOError:
            result["markdown"] = None
    return result


def _load_dossier_module():
    # type: () -> object
    if _DOSSIER_MOD["loaded"]:
        return _DOSSIER_MOD["mod"]
    path = config.resolve("tools", "re", "dossier.py")
    if not os.path.exists(path):
        _DOSSIER_MOD["loaded"] = True
        _DOSSIER_MOD["mod"] = None
        return None
    try:
        spec = importlib.util.spec_from_file_location(
            "openspore_dossier", path)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
    except Exception:
        _DOSSIER_MOD["loaded"] = True
        _DOSSIER_MOD["mod"] = None
        return None
    _DOSSIER_MOD["loaded"] = True
    _DOSSIER_MOD["mod"] = mod
    return mod


def dossier_regenerate(params):
    # type: (dict) -> dict
    topic = _dossier_topic(params)
    if topic is None:
        return _err("invalid_params",
                    "'topic' (or 'path') must name a dossier "
                    "([A-Za-z0-9][A-Za-z0-9_-]*); no directories, "
                    "no shell",
                    tool="dossier_regenerate",
                    available_topics=_available_topics())
    explicit = params.get("snapshot")
    if isinstance(explicit, str) and explicit.strip():
        # The explicit snapshot override is caller-controlled input:
        # confine it to the repo tree so it cannot pull arbitrary
        # files (e.g. /etc/passwd) into the dossier build.
        text = os.path.expanduser(explicit.strip())
        full = os.path.normpath(
            text if os.path.isabs(text)
            else os.path.join(config.OPENSPORE_ROOT, text))
        root = os.path.realpath(config.OPENSPORE_ROOT)
        real = os.path.realpath(full)
        if real != root and not real.startswith(root + os.sep):
            return _err("invalid_params",
                        "'snapshot' must stay under the repo root, "
                        "got %r" % (explicit,),
                        tool="dossier_regenerate", topic=topic)
    mod = _load_dossier_module()
    if mod is None:
        return _err("blocked_no_dossier_module",
                    "tools/re/dossier.py unavailable; dossier %r "
                    "cannot regenerate here" % topic,
                    tool="dossier_regenerate", topic=topic)
    try:
        snap_path = mod.snapshot_path_for(topic, params.get("snapshot"))
    except (AttributeError, TypeError) as exc:
        return _err("blocked_no_dossier_module",
                    "dossier module lacks snapshot_path_for: %s" % exc,
                    tool="dossier_regenerate", topic=topic)
    if not os.path.exists(snap_path):
        return _err("blocked_no_snapshot",
                    "no snapshot for topic %r (%s missing). Upstream "
                    "capture script tools/re/ghidra_snapshot.py does not "
                    "exist (RE-AUTOMATION-ARCHITECTURE.md §2 weakness 2), "
                    "so new-topic dossiers cannot be generated; run "
                    "ghidra_snapshot_save first."
                    % (topic, snap_path),
                    tool="dossier_regenerate", topic=topic,
                    snapshot=snap_path)
    notes = getattr(mod, "TOPIC_NOTES", {}).get(topic, {})
    try:
        dossier = mod.build(topic, snap_path, notes)
        md_text = mod.render_md(dossier)
        js_text = json.dumps(dossier, indent=2) + "\n"
    except Exception as exc:
        return _err("regenerate_failed",
                    "dossier build failed for %r: %s: %s"
                    % (topic, type(exc).__name__, exc),
                    tool="dossier_regenerate", topic=topic)
    out_dir = params.get("out_dir", _dossier_dir())
    if os.path.abspath(out_dir) != os.path.abspath(_dossier_dir()):
        return _err("invalid_params",
                    "'out_dir' outside docs/analysis/dossiers/ refused",
                    tool="dossier_regenerate", topic=topic)
    md_path = os.path.join(out_dir, "%s.md" % topic)
    js_path = os.path.join(out_dir, "%s.json" % topic)
    try:
        os.makedirs(out_dir, exist_ok=True)
        previous_md = open(md_path).read() \
            if os.path.exists(md_path) else None
        previous_js = open(js_path).read() \
            if os.path.exists(js_path) else None
    except OSError as exc:
        return _err("regenerate_failed",
                    "cannot read existing dossier %r: %s" % (topic, exc),
                    tool="dossier_regenerate", topic=topic)
    if previous_md is None or previous_js is None:
        outcome = "created"
    elif previous_md == md_text and previous_js == js_text:
        outcome = "unchanged"
    else:
        outcome = "changed"
    if outcome != "unchanged":
        try:
            with open(md_path, "w") as fh:
                fh.write(md_text)
            with open(js_path, "w") as fh:
                fh.write(js_text)
        except OSError as exc:
            return _err("write_failed",
                        "cannot write dossier %r: %s" % (topic, exc),
                        tool="dossier_regenerate", topic=topic)
    readiness = None
    if isinstance(dossier, dict):
        readiness = dossier.get("replacement_readiness")
    return {"status": "ok", "tool": "dossier_regenerate", "topic": topic,
            "outcome": outcome, "md_path": md_path, "json_path": js_path,
            "readiness": readiness}
