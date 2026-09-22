#!/usr/bin/env python3
"""Decompilation disk cache for the OpenSpore MCP server (stdlib only).

Key (EXACT, per docs/RE-AUTOMATION-ARCHITECTURE.md §4):
  ``(binary_sha256, rva, ghidra_version, program)``

Layout:
  ``<root>/decompiled/<binary12>/<rva>.c`` + ``<rva>.meta.json``

``<root>`` is ``tools/mcp/cache`` under the repo root, or
``OPENSPORE_MCP_CACHE`` when set (absolute as-is, relative resolved
against the repo root) so tests can point at temp dirs.

Semantics:
  * same key -> hit (returns stored C text + stored meta, i.e. the
    original provenance, not fresh stamps);
  * changed binary / rva / version / program -> miss (different path
    or meta mismatch);
  * malformed or stale entries (unparseable meta, missing ``.c``,
    key-field mismatch) -> miss, never a crash;
  * the cache dir is git-ignored and disposable: a lost cache is a
    cost, never evidence loss.
"""
import json
import os
import re

from tools.mcp import config

_META_SUFFIX = ".meta.json"
_C_SUFFIX = ".c"
_RVA_RE = re.compile(r"^[0-9a-f]{1,8}$")


def cache_root():
    # type: () -> str
    """Return the cache root dir (created lazily by store(), not here)."""
    env = os.environ.get("OPENSPORE_MCP_CACHE")
    if env:
        if os.path.isabs(env):
            return os.path.normpath(env)
        return os.path.normpath(os.path.join(config.OPENSPORE_ROOT, env))
    return config.resolve("tools", "mcp", "cache")


def normalize_rva(rva):
    # type: (object) -> str | None
    """Canonical ``0x``-prefixed lowercase hex, or None if not an RVA."""
    if rva is None:
        return None
    text = str(rva).strip().lower()
    if text.startswith("0x"):
        text = text[2:]
    text = text.lstrip("0") or "0"
    if not _RVA_RE.match(text):
        return None
    return "0x%s" % text


def cache_key(binary_sha256, rva, ghidra_version, program):
    # type: (str, str, str, str) -> dict
    """Build the exact cache key dict (all four fields, strings)."""
    return {"binary_sha256": str(binary_sha256 or "unknown"),
            "rva": normalize_rva(rva) or str(rva),
            "ghidra_version": str(ghidra_version or "unknown"),
            "program": str(program or "SporeApp.exe")}


def entry_paths(binary_sha256, rva, ghidra_version, program,
                root=None):
    # type: (str, str, str, str, str | None) -> tuple
    """Return (c_path, meta_path) for a key. Creates nothing."""
    key = cache_key(binary_sha256, rva, ghidra_version, program)
    # Sanitize filename components: the digest prefix and the
    # canonical rva are hex in practice, but a non-canonical rva
    # must never become a directory traversal (defense in depth;
    # live callers always pass resolve_target() output).
    raw_short = (key["binary_sha256"] or "unknown")[:12] or "unknown"
    if raw_short == "unknown":
        short = "unknown"  # degraded-identity bucket keeps its name
    else:
        short = re.sub(r"[^0-9a-f]", "",
                       raw_short.lower())[:12] or "unknown"
    rva_file = normalize_rva(key["rva"])
    if rva_file is None:
        rva_file = "invalid-%s" % re.sub(
            r"[^0-9a-z]", "", str(key["rva"]).lower())[:16]
    base = os.path.join(root or cache_root(), "decompiled", short,
                        rva_file)
    return base + _C_SUFFIX, base + _META_SUFFIX


def lookup(binary_sha256, rva, ghidra_version, program,
           root=None):
    # type: (str, str, str, str, str | None) -> dict
    """Cache read. Returns ``{"hit": bool, ...}``; never raises.

    On hit: ``{"hit": True, "text": ..., "meta": {...}}`` where meta
    is the STORED meta (original provenance retained). On miss:
    ``{"hit": False, "reason": ...}``.
    """
    key = cache_key(binary_sha256, rva, ghidra_version, program)
    c_path, meta_path = entry_paths(
        key["binary_sha256"], key["rva"],
        key["ghidra_version"], key["program"], root=root)
    try:
        with open(meta_path) as fh:
            meta = json.load(fh)
    except (OSError, ValueError):
        return {"hit": False, "reason": "no_entry",
                "c_path": c_path, "meta_path": meta_path}
    if not isinstance(meta, dict):
        return {"hit": False, "reason": "malformed_meta",
                "c_path": c_path, "meta_path": meta_path}
    stored = meta.get("key", meta)
    for field in ("binary_sha256", "rva", "ghidra_version", "program"):
        if str(stored.get(field, "")) != key[field]:
            return {"hit": False, "reason": "stale_key",
                    "field": field,
                    "c_path": c_path, "meta_path": meta_path}
    try:
        with open(c_path) as fh:
            text = fh.read()
    except OSError:
        return {"hit": False, "reason": "missing_body",
                "c_path": c_path, "meta_path": meta_path}
    return {"hit": True, "text": text, "meta": meta,
            "c_path": c_path, "meta_path": meta_path}


def store(binary_sha256, rva, ghidra_version, program, text,
          extra=None, root=None):
    # type: (str, str, str, str, str, dict | None, str | None) -> dict
    """Cache write. Returns ``{"stored": bool, ...}``; never raises."""
    key = cache_key(binary_sha256, rva, ghidra_version, program)
    c_path, meta_path = entry_paths(
        key["binary_sha256"], key["rva"],
        key["ghidra_version"], key["program"], root=root)
    meta = {"key": key, "program": key["program"],
            "provenance": "ghidra_decompile via GhidraMCP REST"}
    if isinstance(extra, dict):
        meta.update(extra)
    try:
        parent = os.path.dirname(c_path)
        os.makedirs(parent, exist_ok=True)
        with open(c_path, "w") as fh:
            fh.write(text)
        with open(meta_path, "w") as fh:
            json.dump(meta, fh, indent=2, sort_keys=True)
            fh.write("\n")
    except (OSError, TypeError, ValueError) as exc:
        return {"stored": False, "reason": "write_failed: %s" % exc,
                "c_path": c_path, "meta_path": meta_path}
    return {"stored": True, "c_path": c_path, "meta_path": meta_path,
            "key": key}
