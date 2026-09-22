#!/usr/bin/env python3
"""GhidraMCP REST client for the OpenSpore MCP server (stdlib only).

Speaks to the headless GhidraMCP bridge over plain ``http.client``.
Never raises on transport failure: every method returns a plain dict
that is either ``{"status": "ok", ...}``, the structured offline
error ``{"status": "error", "code": "ghidra_offline", ...}``, or a
bridge-level rejection ``{"status": "error",
"code": "ghidra_rest_error", ...}`` (the bridge answered but refused
the query, e.g. an empty search term).

Configuration (env, read per call so tests need no restart):
  * ``OPENSPORE_GHIDRA_HOST`` (default ``127.0.0.1``)
  * ``OPENSPORE_GHIDRA_PORT`` (default ``8089``)
  * ``OPENSPORE_GHIDRA`` (full ``http://host:port`` URL; overrides the
    host/port pair when set, per docs/RE-AUTOMATION-ARCHITECTURE.md §4)

Only ``http`` loopback targets are ever contacted; anything else is a
``ghidra_offline``-style config error, never an attempted connection.
No child processes, no command shells, no file access.
"""
import http.client
import json
import os
import socket
import urllib.parse

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 8089
DEFAULT_TIMEOUT = 10.0

OFFLINE_HINT = ("start the headless GhidraMCP server "
                "(see AGENTS.md); dossiers/snapshots keep working "
                "from committed artifacts")


def _config():
    # type: () -> tuple
    """Resolve (host, port) from env. Never raises."""
    url = os.environ.get("OPENSPORE_GHIDRA")
    if url:
        try:
            parts = urllib.parse.urlparse(url)
            if parts.scheme not in ("http", ""):
                return None, None, (
                    "OPENSPORE_GHIDRA must be an http:// URL, got %r" % url)
            host = parts.hostname or DEFAULT_HOST
            port = parts.port or DEFAULT_PORT
            return host, port, None
        except (ValueError, OverflowError) as exc:
            return None, None, "bad OPENSPORE_GHIDRA %r: %s" % (url, exc)
    host = os.environ.get("OPENSPORE_GHIDRA_HOST", DEFAULT_HOST)
    try:
        port = int(os.environ.get("OPENSPORE_GHIDRA_PORT",
                                  str(DEFAULT_PORT)))
    except (TypeError, ValueError):
        return None, None, "bad OPENSPORE_GHIDRA_PORT %r" % (
            os.environ.get("OPENSPORE_GHIDRA_PORT"),)
    return host, port, None


def _offline(message, **extra):
    # type: (str, object) -> dict
    result = {"status": "error", "ok": False, "code": "ghidra_offline",
              "message": message, "hint": OFFLINE_HINT}
    result.update(extra)
    return result


class GhidraClient(object):
    """Thin REST client; stateless, synchronous, stdlib only."""

    def __init__(self, host=None, port=None, timeout=DEFAULT_TIMEOUT):
        # type: (str | None, int | None, float) -> None
        cfg_host, cfg_port, _ = _config()
        self.host = host or cfg_host or DEFAULT_HOST
        self.port = port or cfg_port or DEFAULT_PORT
        self.timeout = timeout

    @property
    def base(self):
        # type: () -> str
        return "http://%s:%d" % (self.host, self.port)

    def _allowlisted(self):
        # type: () -> bool
        return self.host in ("127.0.0.1", "localhost", "::1")

    def request(self, path, params=None, method="GET",
                body=None, timeout=None):
        # type: (str, dict | None, str, dict | None, float | None) -> dict
        """GET/POST one REST endpoint. Never raises."""
        if not path.startswith("/"):
            return _offline("refusing non-absolute REST path %r" % (path,),
                            path=path)
        if not self._allowlisted():
            return {"status": "error", "ok": False, "code": "ghidra_offline",
                    "message": "refusing non-loopback Ghidra host %r"
                               % (self.host,),
                    "hint": "set OPENSPORE_GHIDRA_HOST=127.0.0.1"}
        query = ""
        if params:
            try:
                query = "?" + urllib.parse.urlencode(
                    {k: str(v) for k, v in params.items()})
            except (TypeError, ValueError) as exc:
                return _offline("unencodable REST params: %s" % exc)
        target = path + query
        payload = None
        headers = {}
        if body is not None:
            try:
                payload = json.dumps(body)
            except (TypeError, ValueError) as exc:
                return _offline("unencodable REST body: %s" % exc)
            headers["Content-Type"] = "application/json"
        try:
            conn = http.client.HTTPConnection(
                self.host, self.port,
                timeout=timeout or self.timeout)
            conn.request(method, target, body=payload, headers=headers)
            resp = conn.getresponse()
            raw = resp.read()
            conn.close()
        except (socket.error, OSError, http.client.HTTPException) as exc:
            return _offline("GhidraMCP unreachable at %s%s: %s"
                            % (self.base, target, exc),
                            endpoint=path)
        except Exception as exc:  # never leak transport errors as raises
            return _offline("GhidraMCP request failed: %s: %s"
                            % (type(exc).__name__, exc),
                            endpoint=path)
        if resp.status == 404:
            return {"status": "error", "ok": False, "code": "ghidra_no_endpoint",
                    "message": "GhidraMCP has no endpoint %r (HTTP 404)"
                               % (path,),
                    "hint": OFFLINE_HINT, "endpoint": path}
        if resp.status < 200 or resp.status >= 300:
            return _offline("GhidraMCP HTTP %d on %s" % (resp.status, path),
                            endpoint=path, http_status=resp.status)
        try:
            text = raw.decode("utf-8", errors="replace")
        except Exception as exc:
            return _offline("undecodable GhidraMCP response: %s" % exc,
                            endpoint=path)
        try:
            data = json.loads(text) if text.strip() else {}
        except ValueError:
            # Some endpoints return raw C text, not JSON: wrap it.
            return {"status": "ok", "tool": "ghidra_rest",
                    "endpoint": path, "raw": text}
        if isinstance(data, dict) and "status" in data:
            return data
        if isinstance(data, dict) and "error" in data:
            # Bridge-level rejection (Response.err shape: {"error": ...}
            # with no "status"): a real answer, not a transport failure,
            # so it is an in-band ghidra_rest_error, never a wrapped ok.
            return {"status": "error", "ok": False,
                    "code": "ghidra_rest_error",
                    "message": str(data.get("error")),
                    "endpoint": path, "data": data}
        return {"status": "ok", "tool": "ghidra_rest",
                "endpoint": path, "data": data}

    def check_connection(self):
        # type: () -> dict
        return self.request("/check_connection")

    def decompile(self, address):
        # type: (str) -> dict
        """Decompile one function by hex address (VA). Never raises."""
        return self.request("/decompile_function",
                            {"address": address})

    def function_by_address(self, address):
        # type: (str) -> dict
        return self.request("/get_function_by_address",
                            {"address": address})

    def analyze_function(self, address):
        # type: (str) -> dict
        return self.request("/analyze_function_complete",
                            {"address": address})

    def search_functions(self, pattern, limit=50):
        # type: (str, int) -> dict
        # The headless bridge binds `name_pattern` (and `limit`) from the
        # query string only; body-only params are ignored, so both go in
        # the query (verified against the live GhidraMCP contract).
        return self.request("/search_functions",
                            {"name_pattern": pattern, "limit": limit})

    def get_metadata(self):
        # type: () -> dict
        return self.request("/get_metadata")

    def version(self):
        # type: () -> str
        """Best-effort Ghidra version string; 'unknown' when offline."""
        info = self.get_metadata()
        if not isinstance(info, dict) or info.get("status") != "ok":
            return "unknown"
        data = info.get("data", info)
        if isinstance(data, dict):
            for key in ("ghidra_version", "ghidraVersion", "version"):
                value = data.get(key)
                if value:
                    return str(value)
        return "unknown"


def default_client():
    # type: () -> GhidraClient
    """Build a client from the current env (per call: no hidden state)."""
    host, port, _ = _config()
    return GhidraClient(host=host or DEFAULT_HOST,
                        port=port or DEFAULT_PORT)
