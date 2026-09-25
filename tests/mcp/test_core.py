"""Unit tests for the MCP server core (tools/mcp).

Covers: startup/initialize, tools/list (exact 21 names), stub dispatch,
unknown tool, malformed JSON, malformed requests/params, tool exceptions
(server keeps running), batch handling, notifications, clean shutdown on
EOF/quit, and stdout/stderr separation.

Run from the repo root:
    python3 -m unittest discover -s tests -t . -v
    python3 -m unittest tests.mcp.test_core -v
"""
import io
import json
import os
import unittest

from tools.mcp import config
from tools.mcp import registry
from tools.mcp import server as srv

EXPECTED_TOOLS = [
    "pipeline_state", "target_select",
    "kg_query", "kg_neighbors", "kg_record",
    "dossier_read", "dossier_regenerate",
    "ghidra_decompile", "ghidra_function", "ghidra_search",
    "ghidra_snapshot_save",
    "asset_resolve", "asset_scan",
    "vtable_lookup",
    "trace_run", "trace_analyze", "trace_status",
    "test_run", "status_update", "fixture_check", "queue_op",
]


def run_lines(lines):
    """Feed lines to a Server; return (exit_code, stdout_text, stderr_text)."""
    inp = io.StringIO("".join(line + "\n" for line in lines))
    out = io.StringIO()
    err = io.StringIO()
    code = srv.main(inp, out, err)
    return code, out.getvalue(), err.getvalue()


def responses(stdout_text):
    """Parse stdout lines; every line must be one JSON message."""
    return [json.loads(line)
            for line in stdout_text.splitlines() if line.strip()]


def req(req_id, method, params=None):
    message = {"jsonrpc": "2.0", "id": req_id, "method": method}
    if params is not None:
        message["params"] = params
    return json.dumps(message)


class TestRegistry(unittest.TestCase):
    def test_exact_tool_names(self):
        self.assertEqual(registry.tool_names(), EXPECTED_TOOLS)

    def test_list_tools_shapes(self):
        tools = registry.list_tools()
        self.assertEqual(len(tools), 21)
        for tool in tools:
            self.assertIn("name", tool)
            self.assertIn("description", tool)
            schema = tool["inputSchema"]
            self.assertEqual(schema["type"], "object")
            self.assertIn("properties", schema)

    def test_dispatch_stub(self):
        # asset_resolve landed with Subagent 5: real handler, structured
        # result (invalid_params here -- no package -- or no_spo without
        # SPORE/), never the not_implemented stub.
        result = registry.dispatch("asset_resolve", {})
        self.assertNotEqual(result["status"], "not_implemented")
        self.assertEqual(result["tool"], "asset_resolve")

    def test_dispatch_defaults_params(self):
        result = registry.dispatch("pipeline_state")
        self.assertEqual(result["status"], "ok")

    def test_dispatch_unknown(self):
        with self.assertRaises(registry.ToolUnknown):
            registry.dispatch("no_such_tool", {})

    def test_dispatch_non_dict_params(self):
        with self.assertRaises(registry.InvalidParams):
            registry.dispatch("pipeline_state", ["not", "a", "dict"])


class TestServerCore(unittest.TestCase):
    def test_initialize(self):
        code, out, err = run_lines([req(1, "initialize", {})])
        self.assertEqual(code, 0)  # EOF after the request: clean shutdown.
        (resp,) = responses(out)
        self.assertEqual(resp["id"], 1)
        self.assertEqual(resp["result"], {
            "protocolVersion": "2025-06-18",
            "capabilities": {"tools": {"listChanged": False}},
            "serverInfo": {
                "name": "openspore-mcp",
                "version": "0.1.0",
            },
        })
        self.assertNotIn("server", resp["result"])
        self.assertNotIn("version", resp["result"])
        self.assertNotIn("protocol", resp["result"])
        self.assertNotIn("tools", resp["result"])

    def test_tools_list(self):
        code, out, _err = run_lines([req(1, "tools/list")])
        self.assertEqual(code, 0)
        (resp,) = responses(out)
        names = [tool["name"] for tool in resp["result"]["tools"]]
        self.assertEqual(names, EXPECTED_TOOLS)

    def test_tools_call_real(self):
        code, out, _err = run_lines([
            req(7, "tools/call",
                {"name": "asset_resolve", "arguments": {"record": "Foo"}}),
        ])
        self.assertEqual(code, 0)
        (resp,) = responses(out)
        self.assertEqual(resp["id"], 7)
        self.assertNotEqual(resp["result"]["status"], "not_implemented")
        self.assertEqual(resp["result"]["tool"], "asset_resolve")

    def test_unknown_tool(self):
        _code, out, _err = run_lines([
            req(1, "tools/call", {"name": "nope", "arguments": {}}),
        ])
        (resp,) = responses(out)
        self.assertEqual(resp["error"]["code"], -32601)
        self.assertIn("nope", resp["error"]["message"])

    def test_unknown_method(self):
        _code, out, _err = run_lines([req(1, "frobnicate")])
        (resp,) = responses(out)
        self.assertEqual(resp["error"]["code"], -32601)

    def test_malformed_json(self):
        _code, out, _err = run_lines(["{oops not json"])
        (resp,) = responses(out)
        self.assertEqual(resp["error"]["code"], -32700)
        self.assertIsNone(resp["id"])

    def test_malformed_request_missing_method(self):
        _code, out, _err = run_lines([json.dumps({"jsonrpc": "2.0", "id": 2})])
        (resp,) = responses(out)
        self.assertEqual(resp["id"], 2)
        self.assertEqual(resp["error"]["code"], -32600)

    def test_malformed_request_non_object(self):
        _code, out, _err = run_lines([json.dumps("just a string")])
        (resp,) = responses(out)
        self.assertEqual(resp["error"]["code"], -32600)

    def test_malformed_params_variants(self):
        _code, out, _err = run_lines([
            req(1, "tools/call"),  # no params at all -> missing name
            req(2, "tools/call", {"arguments": {}}),  # name missing
            req(3, "tools/call", {"name": 42}),  # name not a string
            req(4, "tools/call",
                {"name": "kg_query", "arguments": [1, 2]}),  # args not object
            req(5, "tools/call", ["a", "list"]),  # params not an object
        ])
        resps = responses(out)
        self.assertEqual(len(resps), 5)
        for resp in resps:
            self.assertEqual(resp["error"]["code"], -32602,
                             "expected -32602, got %r" % (resp,))

    def test_tool_exception_does_not_crash(self):
        def boom(_params):
            raise RuntimeError("kaboom")

        registry.HANDLERS["__test_boom"] = boom
        try:
            _code, out, err = run_lines([
                req(1, "tools/call",
                    {"name": "__test_boom", "arguments": {}}),
                req(2, "ping"),  # server must still be alive.
            ])
        finally:
            del registry.HANDLERS["__test_boom"]
        first, second = responses(out)
        self.assertEqual(first["error"]["code"], -32603)
        self.assertIn("kaboom", json.dumps(first["error"]))
        self.assertEqual(second["result"], {"status": "ok"})
        self.assertIn("__test_boom", err)  # failure logged to stderr.

    def test_batch(self):
        _code, out, _err = run_lines([json.dumps([
            {"jsonrpc": "2.0", "id": 1, "method": "ping"},
            {"jsonrpc": "2.0", "id": 2, "method": "tools/list"},
            {"jsonrpc": "2.0", "method": "notifications/initialized"},
        ])])
        (line,) = [line for line in out.splitlines() if line.strip()]
        batch = json.loads(line)
        self.assertIsInstance(batch, list)
        self.assertEqual(len(batch), 2)  # notification yields no response.
        by_id = {item["id"]: item for item in batch}
        self.assertEqual(by_id[1]["result"], {"status": "ok"})
        self.assertEqual(len(by_id[2]["result"]["tools"]), 21)

    def test_empty_batch_is_invalid_request(self):
        _code, out, _err = run_lines(["[]"])
        (resp,) = responses(out)
        self.assertEqual(resp["error"]["code"], -32600)

    def test_notification_gets_no_response(self):
        _code, out, _err = run_lines([
            json.dumps({"jsonrpc": "2.0", "method": "notifications/initialized"}),
            req(1, "ping"),
        ])
        (resp,) = responses(out)
        self.assertEqual(resp["id"], 1)

    def test_clean_shutdown_on_eof(self):
        code, out, err = run_lines([])
        self.assertEqual(code, 0)
        self.assertEqual(out, "")
        self.assertIn("starting", err)
        self.assertIn("stopped", err)

    def test_clean_shutdown_on_quit_request(self):
        code, out, _err = run_lines([
            req(1, "ping"),
            req(2, "quit"),  # answered, then the loop stops...
            req(3, "ping"),  # ...so this is never processed.
        ])
        self.assertEqual(code, 0)
        resps = responses(out)
        self.assertEqual([resp["id"] for resp in resps], [1, 2])
        self.assertEqual(resps[1]["result"], {"status": "shutdown"})

    def test_quit_notification_stops_silently(self):
        code, out, _err = run_lines([
            json.dumps({"jsonrpc": "2.0", "method": "quit"}),
            req(1, "ping"),
        ])
        self.assertEqual(code, 0)
        self.assertEqual(responses(out), [])

    def test_blank_lines_ignored(self):
        _code, out, _err = run_lines(["", "   ", req(1, "ping")])
        (resp,) = responses(out)
        self.assertEqual(resp["result"], {"status": "ok"})

    def test_stdout_stderr_separation(self):
        _code, out, err = run_lines([
            req(1, "initialize", {}),
            req(2, "tools/call", {"name": "pipeline_state"}),
            "{broken json",
        ])
        for line in out.splitlines():
            message = json.loads(line)  # every stdout line parses...
            self.assertEqual(message["jsonrpc"], "2.0")  # ...as JSON-RPC.
            self.assertTrue("result" in message or "error" in message)
        self.assertTrue(err.strip())  # ...and logs went to stderr.


class TestConfig(unittest.TestCase):
    def test_root_resolves_to_repo(self):
        self.assertTrue(os.path.isdir(config.OPENSPORE_ROOT))
        self.assertTrue(os.path.exists(
            os.path.join(config.OPENSPORE_ROOT, "opencode.json")))

    def test_resolve(self):
        path = config.resolve("tools", "mcp", "server.py")
        self.assertTrue(os.path.isfile(path))

    def test_binary_sha256(self):
        import hashlib
        import tempfile

        with tempfile.NamedTemporaryFile(delete=False) as tmp:
            tmp.write(b"openspore-core")
        try:
            self.assertEqual(config.binary_sha256(tmp.name),
                             hashlib.sha256(b"openspore-core").hexdigest())
        finally:
            os.unlink(tmp.name)


if __name__ == "__main__":
    unittest.main()
