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

# --------------------------------------------------------------------------- #
# Calling-convention vocabulary.
#
# HARD POLICY: a calling convention reported by Ghidra is an OBSERVATION
# ABOUT GHIDRA's own model of a function, never a verdict about the
# function's real ABI. Nothing in this module (or in ghidra_tools) may use
# these strings to set a calling convention, a receiver/"this" or an sret
# claim -- they exist purely so the ABI cross-validation path can compare
# them against a first-principles reading and notice disagreement.
#
# Measured over all 58757 functions of SporeApp.exe (3.1.0.22):
#   unknown = 58691 (99.8877%), __cdecl = 30, __stdcall = 28,
#   __thiscall = 7, __fastcall = 1, empty = 0.
# So ~99.89% of functions carry NO INFORMATION here. The tokens below are
# therefore treated as silence -- NOT as agreement and NOT as disagreement.
# --------------------------------------------------------------------------- #
CC_NO_INFO_TOKENS = frozenset(["", "unknown", "default", "none", "null"])

CC_INFORMATIVE = "informative"
CC_NO_INFORMATION = "no_information"
CC_UNAVAILABLE = "unavailable"

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


def classify_calling_convention(value):
    # type: (object) -> tuple
    """(string_or_None, signal) for one raw Ghidra convention value.

    Never raises. ``signal`` is one of:

      * ``CC_NO_INFORMATION`` -- Ghidra reported nothing usable
        (absent, None, blank, ``unknown``, ``default``, ``none``,
        ``null``). This is SILENCE: it must never be scored as agreement
        or as disagreement with an independent reading, and it must
        never be promoted into a convention/receiver/sret claim.
      * ``CC_INFORMATIVE`` -- Ghidra holds an actual convention name
        (e.g. ``__thiscall``). Even then the string stays an
        observation about Ghidra, not a verdict.
      * ``CC_UNAVAILABLE`` -- the endpoint was not consulted at all, or
        answered with an error; also silence.
    """
    if value is None:
        return None, CC_NO_INFORMATION
    text = str(value).strip()
    if text.lower() in CC_NO_INFO_TOKENS:
        return None, CC_NO_INFORMATION
    return text, CC_INFORMATIVE


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

    def analyze_function(self, name, include_completeness=True):
        # type: (str, bool) -> dict
        """``/analyze_function_complete`` for one function. Never raises.

        THE PARAMETER IS ``name``, NOT ``address`` -- confirmed against
        the live bridge schema (``GET /mcp/schema``), whose
        ``analyze_function_complete`` entry declares::

            {"name":                {"source": "query", "required": true},
             "include_xrefs":       {"source": "query", "required": false,
                                     "default": "true"},
             ...,
             "include_completeness": {"source": "query",
                                      "required": false,
                                      "default": "false"}}

        Sending ``address=`` therefore binds nothing and the bridge
        answers ``{"error": "Function not found: null"}`` -- which is
        how this whole payload used to be dropped on the floor.
        Ghidra resolves the ``name`` argument by address OR by symbol
        name, so a VA string is passed straight through (verified live:
        both ``name=0x008db310`` and
        ``name=Resource::PFIndexModifiable::Write`` return the same
        6192-byte body).

        ``include_completeness`` defaults to ON because the bridge only
        emits the ``completeness`` block -- and therefore only
        ``completeness.has_calling_convention`` -- when the flag is set
        (verified live: the key is entirely absent without it).

        Unknown extra query keys such as ``address`` are ignored by the
        bridge rather than rejected, but sending one is pointless: only
        ``name`` is bound.
        """
        params = {"name": str(name)}
        if include_completeness:
            params["include_completeness"] = "true"
        return self.request("/analyze_function_complete", params)

    def function_documentation(self, address):
        # type: (str) -> dict
        """``/get_function_documentation`` for one function. Never raises.

        The ONLY endpoint that returns a per-function calling-convention
        STRING (the other source is the boolean
        ``analyze_function_complete.completeness.has_calling_convention``).
        Kept as an explicit, on-demand call: adding it to the
        ``ghidra_function`` request chain would double that tool's
        round-trips to surface a non-``unknown`` value for 0.11% of
        functions.
        """
        return self.request("/get_function_documentation",
                            {"address": address})

    def function_signature(self, address):
        # type: (str) -> dict
        """``/get_function_signature`` for one function. Never raises.

        Source of the ``param_count`` / ``instruction_count`` /
        ``basic_block_count`` observations. Also on-demand only, and
        note 99.19% of SporeApp.exe functions report ``param_count == 0``,
        so it is rarely informative.
        """
        return self.request("/get_function_signature", {"address": address})

    def calling_convention(self, address, has_calling_convention=None):
        # type: (str, bool | None) -> dict
        """Cross-validation-only calling-convention observation.

        Deliberately LAZY and deliberately separate from
        ``analyze_function``: it costs one extra HTTP GET, and the
        population statistic (99.8877% ``unknown`` over 58757 functions)
        says that call almost never buys anything. The ABI
        cross-validation path calls this explicitly when it wants to
        compare Ghidra's opinion against its own reading.

        Returns ``{"ghidra_calling_convention": str | None,
        "ghidra_has_calling_convention": bool | None,
        "ghidra_calling_convention_signal": "informative" |
        "no_information" | "unavailable", ...}``.

        ``has_calling_convention`` is the caller's already-fetched
        ``completeness.has_calling_convention`` boolean, passed through
        when given; when omitted it stays ``None`` (unknown) rather than
        being inferred, because a missing observation is not a ``False``.

        POLICY: the returned values are an OBSERVATION ABOUT GHIDRA.
        They can never set a calling convention, a receiver or an sret
        claim, and ``no_information``/``unavailable`` is silence -- not
        agreement and not disagreement.
        """
        response = self.function_documentation(address)
        ok = isinstance(response, dict) and response.get("status") == "ok"
        data = {}
        if ok:
            candidate = response.get("data")
            data = candidate if isinstance(candidate, dict) else response
        if not isinstance(data, dict):
            data = {}
        raw = data.get("calling_convention")
        if ok:
            text, signal = classify_calling_convention(raw)
        else:
            # Bridge unreachable / refused: silence, not a negative.
            text, signal = None, CC_UNAVAILABLE
        if has_calling_convention is None:
            flag = None
        else:
            flag = bool(has_calling_convention)
        return {
            "status": "ok" if ok else "error",
            "ok": bool(ok),
            "ghidra_calling_convention": text,
            "ghidra_has_calling_convention": flag,
            "ghidra_calling_convention_signal": signal,
            "ghidra_calling_convention_raw": (
                None if raw is None else str(raw)),
            "convention_role": "cross-validation-only",
            "endpoint": "/get_function_documentation",
            "address": str(address),
            "error": None if ok else (
                response.get("message") if isinstance(response, dict)
                else "unusable response"),
        }

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
