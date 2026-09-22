#!/usr/bin/env python3
"""OpenSpore MCP server core: stdlib-only JSON-RPC 2.0 over stdio.

Protocol: newline-delimited JSON on stdin/stdout. One line = one message;
a JSON array on a line is a batch. Methods: ``initialize``, ``tools/list``,
``tools/call``, ``ping``; ``shutdown``/``quit``/``exit`` stop the loop.
Anything under ``notifications/`` is logged and ignored. Every other method
is "method not found".

Framing rules:
  * responses (and only responses) go to stdout, one JSON object per line;
  * all logging goes to stderr, so stdout stays parseable;
  * requests carrying no ``id`` are notifications: processed for side
    effects (e.g. quit) but never answered;
  * a handler exception becomes a -32603 error; the loop keeps running;
  * EOF (or a shutdown/quit/exit method) ends the loop with exit code 0.

Error codes follow JSON-RPC 2.0: -32700 parse, -32600 invalid request,
-32601 method/tool not found, -32602 invalid params, -32603 internal.

No threads, no parallelism, no hidden state beyond the stop flag.

Run from the repo root as ``python3 -m tools.mcp.server`` or directly
as ``python3 tools/mcp/server.py``.
"""
import json
import os
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_HERE))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from tools.mcp import config  # noqa: E402
from tools.mcp import registry  # noqa: E402

SERVER_NAME = "openspore-mcp"
SERVER_VERSION = "0.1.0"

PARSE_ERROR = -32700
INVALID_REQUEST = -32600
METHOD_NOT_FOUND = -32601
INVALID_PARAMS = -32602
INTERNAL_ERROR = -32603

# Methods that stop the loop (as a request they are answered first).
_STOP_METHODS = ("shutdown", "quit", "exit")


def _ok(req_id, result):
    # type: (object, object) -> dict
    return {"jsonrpc": "2.0", "id": req_id, "result": result}


def _error_response(req_id, code, message, data=None):
    # type: (object, int, str, object) -> dict
    error = {"code": code, "message": message}
    if data is not None:
        error["data"] = data
    return {"jsonrpc": "2.0", "id": req_id, "error": error}


def _dump(message):
    # type: (object) -> str
    """Serialise one response message deterministically (sorted keys)."""
    return json.dumps(message, sort_keys=True)


class Server(object):
    """Single-connection stdio server; injectable streams for tests."""

    def __init__(self, stdin=None, stdout=None, stderr=None):
        self.stdin = stdin if stdin is not None else sys.stdin
        self.stdout = stdout if stdout is not None else sys.stdout
        self.stderr = stderr if stderr is not None else sys.stderr
        self._stop = False

    def log(self, message):
        # type: (str) -> None
        print("[%s] %s" % (SERVER_NAME, message),
              file=self.stderr, flush=True)

    def run(self):
        # type: () -> int
        """Read stdin line by line until EOF or a stop method. Returns 0."""
        self.log("starting (root=%s)" % config.OPENSPORE_ROOT)
        try:
            while not self._stop:
                line = self.stdin.readline()
                if line == "":
                    break  # EOF: clean shutdown.
                if not line.strip():
                    continue  # tolerate blank lines.
                try:
                    out_text = self.handle_line(line)
                except Exception as exc:  # never crash on one bad line.
                    self.log("line failed: %r" % (exc,))
                    out_text = _dump(_error_response(
                        None, INTERNAL_ERROR, "internal error",
                        {"error": "%s: %s" % (type(exc).__name__, exc)}))
                if out_text is not None:
                    print(out_text, file=self.stdout, flush=True)
        except KeyboardInterrupt:
            self.log("interrupted")
        self.log("stopped")
        return 0

    def handle_line(self, line):
        # type: (str) -> str | None
        """Handle one stdin line; return the stdout text or None."""
        try:
            message = json.loads(line)
        except json.JSONDecodeError as exc:
            return _dump(_error_response(
                None, PARSE_ERROR, "parse error",
                {"detail": str(exc)}))
        if isinstance(message, list):
            return self._handle_batch(message)
        response = self.handle_message(message)
        return _dump(response) if response is not None else None

    def _handle_batch(self, messages):
        # type: (list) -> str | None
        if len(messages) == 0:
            return _dump(_error_response(
                None, INVALID_REQUEST, "invalid request: empty batch"))
        responses = []
        for item in messages:
            try:
                response = self.handle_message(item)
            except Exception as exc:
                self.log("batch item failed: %r" % (exc,))
                response = _error_response(
                    None, INTERNAL_ERROR, "internal error",
                    {"error": "%s: %s" % (type(exc).__name__, exc)})
            if response is not None:
                responses.append(response)
        if not responses:
            return None  # batch of pure notifications: stay silent.
        return _dump(responses)

    def handle_message(self, message):
        # type: (object) -> dict | None
        """Handle one decoded message; None means 'send no response'."""
        if not isinstance(message, dict):
            return _error_response(
                None, INVALID_REQUEST,
                "invalid request: message must be an object")
        method = message.get("method")
        req_id = message.get("id")
        is_notification = "id" not in message
        params = message.get("params")
        if not isinstance(method, str) or not method:
            if is_notification:
                self.log("ignoring notification without method")
                return None
            return _error_response(
                req_id, INVALID_REQUEST,
                "invalid request: missing method")
        if method.startswith("notifications/"):
            self.log("notification: %s" % method)
            return None
        handler = {
            "initialize": self._on_initialize,
            "ping": self._on_ping,
            "tools/list": self._on_tools_list,
            "tools/call": self._on_tools_call,
        }.get(method)
        if handler is not None:
            response = handler(req_id, params)
        elif method in _STOP_METHODS:
            self._stop = True
            self.log("stop requested via %r" % method)
            response = _ok(req_id, {"status": "shutdown"})
        else:
            if is_notification:
                self.log("ignoring unknown notification: %s" % method)
                return None
            return _error_response(
                req_id, METHOD_NOT_FOUND,
                "method not found: %s" % method)
        # Notifications are processed for side effects but never answered.
        if is_notification:
            return None
        return response

    def _on_initialize(self, req_id, params):
        # type: (object, object) -> dict
        return _ok(req_id, {
            "server": SERVER_NAME,
            "version": SERVER_VERSION,
            "protocol": "jsonrpc-2.0-stdio",
            "tools": len(registry.tool_names()),
        })

    def _on_ping(self, req_id, params):
        # type: (object, object) -> dict
        return _ok(req_id, {"status": "ok"})

    def _on_tools_list(self, req_id, params):
        # type: (object, object) -> dict
        return _ok(req_id, {"tools": registry.list_tools()})

    def _on_tools_call(self, req_id, params):
        # type: (object, object) -> dict
        """Dispatch one tools/call request.

        -32602 (invalid params) is reserved for a malformed envelope
        only: params not an object, 'name' missing/not a string, or
        'arguments' not an object. A well-formed call whose arguments
        fail domain validation (missing/invalid field) is answered
        with a normal result carrying the handler's in-band error
        dict (status=error, ok=False, code, message) -- never -32602.
        Unknown tools are -32601; handler crashes are -32603.
        """
        if params is None:
            params = {}
        if not isinstance(params, dict):
            return _error_response(
                req_id, INVALID_PARAMS,
                "invalid params: params must be an object")
        name = params.get("name")
        arguments = params.get("arguments", {})
        if not isinstance(name, str) or not name:
            return _error_response(
                req_id, INVALID_PARAMS,
                "invalid params: 'name' must be a non-empty string")
        if not isinstance(arguments, dict):
            return _error_response(
                req_id, INVALID_PARAMS,
                "invalid params: 'arguments' must be an object")
        try:
            result = registry.dispatch(name, arguments)
        except registry.ToolUnknown:
            return _error_response(
                req_id, METHOD_NOT_FOUND, "unknown tool: %s" % name)
        except registry.InvalidParams as exc:
            return _error_response(req_id, INVALID_PARAMS, str(exc))
        except Exception as exc:
            self.log("tool %r failed: %r" % (name, exc))
            return _error_response(
                req_id, INTERNAL_ERROR, "tool %r failed" % name,
                {"error": "%s: %s" % (type(exc).__name__, exc)})
        if not isinstance(result, dict):
            result = {"result": result}
        return _ok(req_id, result)


def main(stdin=None, stdout=None, stderr=None):
    # type: (object, object, object) -> int
    """Entry point; streams default to the process stdio. Returns 0."""
    return Server(stdin, stdout, stderr).run()


if __name__ == "__main__":
    sys.exit(main())
