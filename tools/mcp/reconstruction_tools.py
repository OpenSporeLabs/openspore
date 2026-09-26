#!/usr/bin/env python3
"""MCP adapters for the generated reconstruction knowledge index."""
from __future__ import print_function

import os
import sqlite3
from collections import defaultdict

from tools import reconstruction_knowledge as knowledge
from tools.mcp import config


def _error(code, message, **extra):
    result = {"status": "error", "ok": False, "code": code, "message": message}
    result.update(extra)
    return result


def _index_path():
    override = os.environ.get("OPENSPORE_RECONSTRUCTION_INDEX")
    if override:
        if os.path.isabs(override):
            return override
        return config.resolve(override)
    return config.resolve("reconstruction", "knowledge", "index.json")


def _load_index():
    path = _index_path()
    try:
        return knowledge.load_index(path), path
    except (OSError, ValueError) as exc:
        return None, _error(
            "knowledge_index_missing",
            str(exc),
            index_path=path,
            generation_command="python3 -m tools.reconstruction_knowledge build",
        )


def _claims(vas):
    if not vas:
        return {}
    database = config.db_path()
    if not os.path.exists(database):
        return {}
    wanted = set(vas)
    claims = defaultdict(list)
    try:
        connection = sqlite3.connect(database)
        connection.row_factory = sqlite3.Row
        table = connection.execute(
            "SELECT 1 FROM sqlite_master WHERE type='table' AND name='investigations'"
        ).fetchone()
        if table is None:
            connection.close()
            return {}
        rows = connection.execute(
            "SELECT id,va,status,stage,implementer_id,block_reason,"
            "updated_at,binary_sha256 FROM investigations WHERE kind='function'"
        ).fetchall()
        for row in rows:
            try:
                va = knowledge.normalize_va(row["va"])
            except (TypeError, ValueError):
                continue
            if va not in wanted:
                continue
            claims[va].append({
                "id": row["id"],
                "status": row["status"],
                "stage": row["stage"],
                "implementer_id": row["implementer_id"],
                "block_reason": row["block_reason"],
                "updated_at": row["updated_at"],
                "binary_sha256": row["binary_sha256"],
            })
        connection.close()
    except sqlite3.Error:
        return {}
    for values in claims.values():
        values.sort(key=lambda item: (item["status"], item["id"]))
    return dict(claims)


def _va(params):
    value = params.get("va", params.get("address"))
    if not isinstance(value, str) or not value.strip():
        raise ValueError("va is required")
    return knowledge.normalize_va(value)


def function_context(params):
    try:
        va = _va(params)
        limit = int(params.get("limit", 8))
    except (TypeError, ValueError) as exc:
        return _error("invalid_params", str(exc))
    index, path = _load_index()
    if index is None:
        result = path
        result["tool"] = "function_context"
        return result
    try:
        result = knowledge.function_context(index, va, limit)
    except (KeyError, TypeError, ValueError) as exc:
        return _error("invalid_params", str(exc))
    if result.get("status") == "error":
        result["tool"] = "function_context"
        return result
    record = result["function"]
    result["tool"] = "function_context"
    result["index_path"] = path
    result["claims"] = _claims([record["va"]]).get(record["va"], [])
    return result


def frontier_context(params):
    for key in ("package", "subsystem", "status"):
        if params.get(key) is not None and not isinstance(params.get(key), str):
            return _error("invalid_params", "%s must be a string" % key,
                          field=key)
    try:
        limit = int(params.get("limit", 20))
    except (TypeError, ValueError):
        return _error("invalid_params", "limit must be an integer")
    index, path = _load_index()
    if index is None:
        result = path
        result["tool"] = "frontier_context"
        return result
    result = knowledge.frontier_context(
        index, params.get("package"), params.get("subsystem"),
        params.get("status"), limit)
    result["tool"] = "frontier_context"
    result["index_path"] = path
    claims = _claims([row["va"] for row in result.get("frontier", [])])
    for row in result.get("frontier", []):
        row["claims"] = claims.get(row["va"], [])
    return result


def reconstruction_status(params):
    try:
        va = _va(params)
    except (TypeError, ValueError) as exc:
        return _error("invalid_params", str(exc))
    index, path = _load_index()
    if index is None:
        result = path
        result["tool"] = "reconstruction_status"
        return result
    result = knowledge.reconstruction_status(index, va)
    result["tool"] = "reconstruction_status"
    if result.get("status") == "ok":
        result["index_path"] = path
        result["claims"] = _claims([va]).get(va, [])
    return result
