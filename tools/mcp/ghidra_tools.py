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
  * every result carries explicit binary/program identity
    (``binary_sha256`` of ``SPORE/SporeBin/SporeApp.exe`` or
    ``"unknown"`` + ``no_spo`` note when absent, ``program`` name,
    ``image_base``);
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
                           str(stored.get("ghidra_version", "")), text, meta))
    if not candidates:
        return {"hit": False, "reason": "no_entry"}
    candidates.sort()
    _sha, _ver, text, meta = candidates[0]
    return {"hit": True, "text": text, "meta": meta, "fallback": True}


def ghidra_decompile(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    sha = identity["binary_sha256"]
    program = _program_name(params)
    base = _image_base(params)
    force = bool(params.get("force", False))
    target = _target_from_params(params, base)
    if "error" in target and "ok" not in target:
        return _err("invalid_params", target["error"])
    client = _get_client()
    if target.get("name") and target.get("va") is None:
        resolved = _resolve_name_to_va(client, target["name"])
        if "error" in resolved and "ok" not in resolved:
            msg = resolved["error"]
            code = "ghidra_offline" if msg.startswith("ghidra_offline") \
                else "not_found"
            result = _err(code, msg, tool="ghidra_decompile",
                          program=program, image_base="0x%x" % base,
                          evidence_note=EVIDENCE_NOTE)
            result.update(identity)
            return result
        target = resolved
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
            result = {"status": "ok", "tool": "ghidra_decompile",
                      "va": va, "rva": decompile_cache.normalize_rva(rva),
                      "program": program, "image_base": "0x%x" % base,
                      "ghidra_version": hit["meta"].get(
                          "key", {}).get("ghidra_version", version),
                      "cached": True, "cache": "hit",
                      "decompiled": hit["text"],
                      "provenance": hit["meta"],
                      "evidence_note": EVIDENCE_NOTE}
            result.update(identity)
            return result
        if version == "unknown":
            # Offline: live version unknowable, serve any stored version
            # for (binary?, rva, program) with provenance intact.
            fallback = _cache_fallback_scan(sha, rva, program)
            if fallback["hit"]:
                result = {
                    "status": "ok", "tool": "ghidra_decompile",
                    "va": va,
                    "rva": decompile_cache.normalize_rva(rva),
                    "program": program, "image_base": "0x%x" % base,
                    "ghidra_version": fallback["meta"].get(
                        "key", {}).get("ghidra_version", "unknown"),
                    "cached": True, "cache": "hit-offline-fallback",
                    "decompiled": fallback["text"],
                    "provenance": fallback["meta"],
                    "evidence_note": EVIDENCE_NOTE,
                    "note": "Ghidra offline; served from disk cache "
                            "(stored key retained in provenance)"}
                result.update(identity)
                return result
    try:
        resp = client.decompile(va)
    except Exception as exc:
        return _err("ghidra_offline",
                    "GhidraMCP request failed: %s: %s"
                    % (type(exc).__name__, exc),
                    tool="ghidra_decompile", va=va, rva=rva,
                    program=program, **identity)
    if not isinstance(resp, dict) or resp.get("status") != "ok":
        code = resp.get("code", "ghidra_offline") \
            if isinstance(resp, dict) else "ghidra_offline"
        detail = resp.get("message", "no detail") \
            if isinstance(resp, dict) else "no detail"
        return _err(code, "decompile %s failed: %s" % (va, detail),
                    tool="ghidra_decompile", va=va, rva=rva,
                    program=program,
                    hint=resp.get("hint") if isinstance(resp, dict)
                    else None, **identity)
    code_text = _extract_code(resp)
    if not code_text:
        return _err("empty_decompile",
                    "Ghidra returned no decompilation text for %s" % va,
                    tool="ghidra_decompile", va=va, rva=rva,
                    program=program, **identity)
    stored = decompile_cache.store(
        sha, rva, version, program, code_text,
        extra={"va": va, "image_base": "0x%x" % base})
    result = {"status": "ok", "tool": "ghidra_decompile",
              "va": va, "rva": decompile_cache.normalize_rva(rva),
              "program": program, "image_base": "0x%x" % base,
              "ghidra_version": version,
              "cached": False, "cache": "miss",
              "decompiled": code_text,
              "cache_store": stored.get("stored", False),
              "evidence_note": EVIDENCE_NOTE}
    result.update(identity)
    return result


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
        return _err("invalid_params", target["error"])
    client = _get_client()
    if target.get("name") and target.get("va") is None:
        resolved = _resolve_name_to_va(client, target["name"])
        if "error" not in resolved or "ok" in resolved:
            target = resolved
        else:
            target = {"ok": True, "name": params.get("name"),
                      "va": None, "rva": None}
    va = target.get("va")
    if va is not None and va in _FUNCTION_MEMO:
        card = dict(_FUNCTION_MEMO[va])
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
                card = {"status": "ok", "tool": "ghidra_function",
                        "va": row.get("address"), "rva": row.get("rva"),
                        "name": row.get("name"), "program": program,
                        "image_base": "0x%x" % base,
                        "size_bytes": row.get("size_bytes"),
                        "namespace": row.get("namespace"),
                        "signature": row.get("signature"),
                        "dispatch": row.get("dispatch"),
                        "callers": row.get("callers"),
                        "callees": row.get("callees"),
                        "sdk_name": None, "sdk_type": None,
                        "subsystem": None,
                        "provenance": "tools/re/data/"
                                      "ghidra_snapshot_cell_movement.json "
                                      "(committed; Ghidra offline)",
                        "evidence_note": EVIDENCE_NOTE}
                card.update(identity)
                return card
        return _err("ghidra_offline",
                    "Ghidra unreachable and no committed snapshot covers "
                    "%r" % (va or target.get("name"),),
                    tool="ghidra_function", program=program, **identity)

    merged = dict(info_d)
    for key, value in analysis_d.items():
        merged.setdefault(key, value)
    va_int = _parse_int(va) if va is not None else None
    join = _vtable_join(va_int) if va_int is not None else \
        {"vtable_at": [], "referenced_by_vtables": [],
         "sdk_associations": []}
    card = {"status": "ok", "tool": "ghidra_function",
            "va": va, "rva": target.get("rva"),
            "name": merged.get("name") or target.get("name"),
            "program": program, "image_base": "0x%x" % base,
            "size_bytes": merged.get("size_bytes", merged.get("size")),
            "namespace": merged.get("namespace"),
            "signature": merged.get("signature"),
            "dispatch": merged.get("dispatch"),
            "callers": merged.get("callers"),
            "callees": merged.get("callees"),
            "sdk_name": merged.get("sdk_name"),
            "sdk_type": merged.get("sdk_type"),
            "subsystem": merged.get("subsystem"),
            "vtables": join,
            "evidence_note": EVIDENCE_NOTE}
    card.update(identity)
    if va is not None:
        _FUNCTION_MEMO[va] = {k: v for k, v in card.items()
                              if k not in identity}
    return card


# --------------------------------------------------------------------------- #
# ghidra_search: name-pattern search.
# --------------------------------------------------------------------------- #
def ghidra_search(params):
    # type: (dict) -> dict
    identity = _binary_identity()
    program = _program_name(params)
    pattern = params.get("pattern", params.get("query", ""))
    if not isinstance(pattern, str) or not pattern.strip():
        return _err("invalid_params",
                    "'pattern' (name substring) is required and non-empty",
                    tool="ghidra_search", program=program, **identity)
    pattern = pattern.strip()
    if len(pattern) > 256:
        return _err("invalid_params", "'pattern' too long (max 256 chars)",
                    tool="ghidra_search", program=program, **identity)
    try:
        limit = int(params.get("limit", 50))
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit' must be an integer",
                    tool="ghidra_search", program=program, **identity)
    limit = max(1, min(limit, 500))
    client = _get_client()
    try:
        resp = client.search_functions(pattern, limit)
    except Exception as exc:
        return _err("ghidra_offline",
                    "GhidraMCP request failed: %s: %s"
                    % (type(exc).__name__, exc),
                    tool="ghidra_search", pattern=pattern,
                    program=program, **identity)
    if not isinstance(resp, dict) or resp.get("status") != "ok":
        code = resp.get("code", "ghidra_offline") \
            if isinstance(resp, dict) else "ghidra_offline"
        return _err(code, resp.get("message", "search failed")
                    if isinstance(resp, dict) else "search failed",
                    tool="ghidra_search", pattern=pattern,
                    program=program,
                    hint=resp.get("hint") if isinstance(resp, dict)
                    else None, **identity)
    items = _as_list(resp)
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
    result = {"status": "ok", "tool": "ghidra_search",
              "pattern": pattern, "program": program,
              "matches": matches, "count": len(matches)}
    result.update(identity)
    return result


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
        return _err("invalid_params",
                    "'topic' (or 'label') is required: "
                    "[A-Za-z0-9][A-Za-z0-9_-]*",
                    tool="ghidra_snapshot_save", program=program,
                    **identity)
    client = _get_client()
    try:
        version = client.version()
    except Exception:
        version = "unknown"
    version = str(version or "unknown")

    rows, offline = _snapshot_functions(params, client, sha, program,
                                        base, version)
    if not rows:
        return _err("blocked_no_functions",
                    "snapshot %r has no function list and no committed "
                    "snapshot to default from; pass 'functions' "
                    "(addresses/names). Upstream capture script "
                    "tools/re/ghidra_snapshot.py does not exist "
                    "(RE-AUTOMATION-ARCHITECTURE.md §2 weakness 2), so "
                    "new topics cannot be enumerated from Ghidra here."
                    % topic,
                    tool="ghidra_snapshot_save", topic=topic,
                    program=program, **identity)
    if offline and offline == len(rows):
        return _err("ghidra_offline",
                    "Ghidra unreachable and no cached decompilation for "
                    "any of the %d function(s); snapshot %r blocked "
                    "(not written). Populate tools/mcp/cache/ while "
                    "online, or work from the committed snapshot."
                    % (len(rows), topic),
                    tool="ghidra_snapshot_save", topic=topic,
                    program=program, **identity)
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
    try:
        os.makedirs(out_dir, exist_ok=True)
        if os.path.exists(out_path):
            with open(out_path) as fh:
                previous = fh.read()
            if previous == text:
                result = {"status": "ok", "tool": "ghidra_snapshot_save",
                          "topic": topic, "path": out_path,
                          "outcome": "unchanged", "sha256": digest,
                          "functions": len(rows),
                          "offline_functions": offline,
                          "program": program}
                result.update(identity)
                return result
            outcome = "changed"
        else:
            outcome = "created"
        with open(out_path, "w") as fh:
            fh.write(text)
    except OSError as exc:
        return _err("write_failed", "cannot write snapshot: %s" % exc,
                    tool="ghidra_snapshot_save", topic=topic,
                    program=program, **identity)
    result = {"status": "ok", "tool": "ghidra_snapshot_save",
              "topic": topic, "path": out_path, "outcome": outcome,
              "sha256": digest, "functions": len(rows),
              "offline_functions": offline, "program": program}
    result.update(identity)
    return result


# --------------------------------------------------------------------------- #
# vtable_lookup: read-only over docs/analysis/vtables.json.
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
    doc = _load_vtables()
    if not doc:
        return _err("no_vtables",
                    "docs/analysis/vtables.json missing or unparseable",
                    tool="vtable_lookup")
    klass = params.get("class", params.get("class_name", ""))
    address = params.get("address", "")
    namespace = params.get("namespace", "")
    subsystem = params.get("subsystem", "")
    try:
        limit = int(params.get("limit", 50))
    except (TypeError, ValueError):
        return _err("invalid_params", "'limit' must be an integer",
                    tool="vtable_lookup")
    limit = max(1, min(limit, 500))
    if not any(isinstance(v, str) and v.strip()
               for v in (klass, address, namespace, subsystem)):
        return _err("invalid_params",
                    "one of 'class'/'address'/'namespace'/'subsystem' "
                    "is required",
                    tool="vtable_lookup")
    addr_norm = None
    if isinstance(address, str) and address.strip():
        addr_int = _parse_int(address.strip())
        if addr_int is None:
            return _err("invalid_params",
                        "'address' must be hex, got %r" % (address,),
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
            matches.append({
                "address": cand.get("address"),
                "slots": cand.get("slots"),
                "confidence": cand.get("confidence"),
                "namespace": cand.get("namespace"),
                "firstSlotFunc": cand.get("firstSlotFunc")})
    matches.sort(key=lambda m: str(m.get("address")))
    meta = doc.get("meta", {}) if isinstance(doc.get("meta"), dict) \
        else {}
    return {"status": "ok", "tool": "vtable_lookup",
            "source": "docs/analysis/vtables.json",
            "image_base": meta.get("image_base"),
            "total_candidates": len(candidates),
            "matches": matches[:limit], "count": len(matches)}


# --------------------------------------------------------------------------- #
# dossier_read / dossier_regenerate: read-only + deterministic writers over
# docs/analysis/dossiers/ (constrained paths, no shell).
# --------------------------------------------------------------------------- #
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
    topic = _dossier_topic(params)
    if topic is None:
        return _err("invalid_params",
                    "'topic' (or 'path') must name a dossier "
                    "([A-Za-z0-9][A-Za-z0-9_-]*); no directories, "
                    "no shell",
                    tool="dossier_read",
                    available_topics=_available_topics())
    path = os.path.join(_dossier_dir(), topic + ".json")
    try:
        with open(path) as fh:
            doc = json.load(fh)
    except IOError:
        return _err("not_found", "no dossier for topic %r" % topic,
                    tool="dossier_read",
                    available_topics=_available_topics())
    except ValueError as exc:
        return _err("corrupt_dossier",
                    "dossier %r is not valid JSON: %s" % (topic, exc),
                    tool="dossier_read", topic=topic)
    if not isinstance(doc, dict):
        return _err("corrupt_dossier",
                    "dossier %r is not a JSON object" % topic,
                    tool="dossier_read", topic=topic)
    section = params.get("section")
    if section is not None:
        if not isinstance(section, str) or section not in doc:
            return _err("no_section",
                        "dossier %r has no section %r" % (topic, section),
                        tool="dossier_read", topic=topic,
                        available_sections=sorted(doc.keys()))
        result = {"status": "ok", "tool": "dossier_read", "topic": topic,
                  "path": path, "section": section,
                  "data": doc[section]}
    else:
        result = {"status": "ok", "tool": "dossier_read", "topic": topic,
                  "path": path, "dossier": doc}
    if params.get("md"):
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
