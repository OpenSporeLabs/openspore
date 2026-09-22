#!/usr/bin/env python3
"""Shared configuration for the OpenSpore MCP server (stdlib only).

Resolves the repo root, builds absolute paths under it, and hashes the
target binary so later tool implementations can record provenance.

Clean-room note: only computes paths/hashes, never reads game assets.
"""
import hashlib
import os

HERE = os.path.dirname(os.path.abspath(__file__))

# Files/dirs that mark the repo root when walking up from this file.
_MARKERS = ("opencode.json", ".git", "knowledgegraph")

# Chunk size for streaming sha256 (keeps large binaries off the heap).
_CHUNK_SIZE = 65536


def find_repo_root(start=None):
    # type: (str | None) -> str
    """Return the OpenSpore repo root.

    OPENSPORE_ROOT env var wins; otherwise walk up from ``start`` (default:
    this file's directory) until a marker is found. Falls back to two levels
    up from tools/mcp/ so the server still starts outside a checkout.
    """
    env = os.environ.get("OPENSPORE_ROOT")
    if env and os.path.isdir(env):
        return os.path.abspath(env)
    cur = os.path.abspath(start or HERE)
    while True:
        for marker in _MARKERS:
            if os.path.exists(os.path.join(cur, marker)):
                return cur
        parent = os.path.dirname(cur)
        if parent == cur:
            return os.path.abspath(os.path.join(HERE, "..", ".."))
        cur = parent


OPENSPORE_ROOT = find_repo_root()


def resolve(*parts):
    # type: (*str) -> str
    """Join ``parts`` onto the repo root and normalise to an absolute path."""
    return os.path.normpath(os.path.join(OPENSPORE_ROOT, *parts))


def binary_sha256(path, chunk_size=_CHUNK_SIZE):
    # type: (str, int) -> str
    """Return the hex sha256 of the file at ``path`` (streamed, binary mode)."""
    digest = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(chunk_size), b""):
            digest.update(chunk)
    return digest.hexdigest()


def db_path():
    # type: () -> str
    """Return the knowledge-graph SQLite path.

    OPENSPORE_DB env var wins (absolute as-is, relative resolved against
    the repo root) so tests can point at a temporary database; otherwise
    the default git-ignored ``knowledgegraph/spore.db``.
    """
    env = os.environ.get("OPENSPORE_DB")
    if env:
        if os.path.isabs(env):
            return os.path.normpath(env)
        return os.path.normpath(os.path.join(OPENSPORE_ROOT, env))
    return resolve("knowledgegraph", "spore.db")
