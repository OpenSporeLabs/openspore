"""CI/integration test suite for the OpenSpore MCP server (tools/mcp).

Exercises the ACTUAL stdio protocol: every test spawns
``python3 tools/mcp/server.py`` as a subprocess with pipes and speaks
newline-delimited JSON-RPC 2.0 to it. No in-process Server shortcuts.

Coverage (one bullet per group):
  * server launch ............ TestLaunch
  * request/response protocol  TestProtocol
  * all 24 tools smoke ....... TestAllToolsSmoke ({} + minimal params)
  * malformed input .......... TestMalformed
  * error handling ........... TestErrorHandling
  * KG temp-DB ops ............ TestKnowledgeGraph
  * queue ops ................ TestQueue
  * decompilation cache ...... TestDecompileCache
  * provenance ............... TestProvenance
  * stale-state .............. TestStaleState
  * clean shutdown ........... TestShutdown
  * stdout contamination ..... TestStdoutClean
  * fresh-clone safety ....... TestFreshClone (empty HOME, SPORE absent)

Fresh-clone rules: temp OPENSPORE_DB + OPENSPORE_MCP_CACHE per test,
Ghidra forced offline (dead loopback port), approval trust stripped,
DISPLAY stripped, ctest forced missing. A tool that needs unavailable
external state must answer a graceful blocked/offline/degraded result,
never crash the server.

Run from the repo root:
    python3 -m unittest tests.mcp.test_server -v
"""
import hashlib
import json
import os
import select
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__))))
SERVER_SCRIPT = os.path.join(ROOT, "tools", "mcp", "server.py")

EXPECTED_TOOLS = [
    "pipeline_state", "target_select", "function_context",
    "frontier_context", "reconstruction_status",
    "kg_query", "kg_neighbors", "kg_record",
    "dossier_read", "dossier_regenerate",
    "ghidra_decompile", "ghidra_function", "ghidra_search",
    "ghidra_snapshot_save",
    "asset_resolve", "asset_scan",
    "vtable_lookup",
    "trace_run", "trace_analyze", "trace_status",
    "test_run", "status_update", "fixture_check", "queue_op",
]

# Per-tool minimal arguments for the smoke pass ({} is covered separately).
SMOKE_ARGS = {
    "pipeline_state": {},
    "target_select": {},
    "function_context": {"va": "0x00e5b790"},
    "frontier_context": {"limit": 1},
    "reconstruction_status": {"va": "0x00e5b790"},
    "kg_query": {},
    "kg_neighbors": {"name": "srv-smoke-absent"},
    "kg_record": {"reason": "srv smoke probe"},
    "dossier_read": {"topic": "cell-movement"},
    "dossier_regenerate": {"topic": "cell-movement"},
    "ghidra_decompile": {"function": "0x00401000"},
    "ghidra_function": {"address": "0x00401000"},
    "ghidra_search": {"pattern": "FUN_"},
    "ghidra_snapshot_save": {},
    "asset_resolve": {},
    "asset_scan": {},
    "vtable_lookup": {"address": "0x00400000"},
    "trace_run": {},
    "trace_analyze": {},
    "trace_status": {},
    "test_run": {},
    "status_update": {},
    "fixture_check": {},
    "queue_op": {"op": "list"},
}

# In-band "graceful" codes for tools whose externals are unavailable here
# (Ghidra offline, SPORE/probes/build absent, human gates closed).
GRACEFUL_CODES = frozenset([
    "approval_required", "ghidra_offline", "ghidra_no_endpoint",
    "no_spo", "blocked_no_probe", "blocked_no_tracer", "blocked_no_wine",
    "blocked_no_display", "blocked_no_ctest", "blocked_no_build",
    "blocked_no_resolver", "blocked_no_functions", "blocked_no_snapshot",
    "blocked_no_dossier_module", "blocked_no_emitter", "blocked_unreadable",
    "empty_database", "not_found", "no_vtables", "no_section",
    "missing_param", "missing_reason", "invalid_params", "invalid_status",
    "invalid_evidence", "empty_decompile", "resolver_failed",
    "machine_locked", "corrupt_fixtures", "corrupt_dossier",
    "write_failed", "evidence_cap", "evidence_required",
    "regenerate_failed", "emitter_failed", "nondeterministic_emitter",
    "trace_launch_failed", "test_launch_failed", "unstable_read",
    "corrupt_status", "already_claimed", "nothing_to_update",
])

READ_TIMEOUT = 20.0


def _child_env(db_path, cache_dir, extra=None):
    """Build the subprocess env: isolated, offline, ungated, displayless."""
    env = dict(os.environ)
    env.pop("OPENSPORE_MCP_TRUSTED", None)  # gates must stay closed
    env.pop("DISPLAY", None)  # no display, even if the CI box has one
    env["OPENSPORE_DB"] = db_path
    env["OPENSPORE_MCP_CACHE"] = cache_dir
    # Dead loopback port: Ghidra is deterministically offline, fast.
    env["OPENSPORE_GHIDRA"] = "http://127.0.0.1:9"
    env["OPENSPORE_MCP_LOCK"] = os.path.join(cache_dir, "machine.lock")
    # Force the deterministic blocked_no_ctest path (never run ctest here).
    env["OPENSPORE_MCP_CTEST"] = "/nonexistent-openspore-ctest-for-ci"
    if extra:
        env.update(extra)
    return env


def _probe_sha():
    """Mirror ghidra_tools._binary_identity for cache-key pre-population."""
    path = os.path.join(ROOT, "SPORE", "SporeBin", "SporeApp.exe")
    if not os.path.exists(path):
        return "unknown"
    digest = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


class StdioServer(object):
    """One spawned server.py with line-oriented request/response helpers."""

    def __init__(self, env):
        self.proc = subprocess.Popen(
            [sys.executable, SERVER_SCRIPT],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, text=True, bufsize=1,
            cwd=ROOT, env=env)
        self.raw_lines = []  # every stdout line, for contamination checks
        self.stderr_text = ""
        self.returncode = None

    # -- low-level framing ------------------------------------------------ #
    def send_raw(self, text):
        self.proc.stdin.write(text + "\n")
        self.proc.stdin.flush()

    def send(self, message):
        self.send_raw(json.dumps(message, sort_keys=True))

    def read_line(self, timeout=READ_TIMEOUT):
        proc = self.proc
        ready, _, _ = select.select([proc.stdout], [], [], timeout)
        if not ready:
            raise AssertionError(
                "timed out after %ss waiting for server response" % timeout)
        line = proc.stdout.readline()
        if line == "":
            raise AssertionError("server closed stdout unexpectedly")
        self.raw_lines.append(line)
        return line

    def read_response(self, timeout=READ_TIMEOUT):
        return json.loads(self.read_line(timeout))

    # -- JSON-RPC helpers ------------------------------------------------- #
    def request(self, method, params=None, req_id=1, timeout=READ_TIMEOUT):
        message = {"jsonrpc": "2.0", "id": req_id, "method": method}
        if params is not None:
            message["params"] = params
        self.send(message)
        return self.read_response(timeout)

    def notify(self, method, params=None):
        message = {"jsonrpc": "2.0", "method": method}
        if params is not None:
            message["params"] = params
        self.send(message)

    def call_tool(self, name, arguments=None, req_id=1,
                  timeout=READ_TIMEOUT):
        return self.request("tools/call",
                            {"name": name,
                             "arguments": arguments or {}},
                            req_id=req_id, timeout=timeout)

    def assert_no_response(self, timeout=1.0):
        ready, _, _ = select.select([self.proc.stdout], [], [], timeout)
        if ready:
            extra = self.proc.stdout.readline()
            if extra == "":
                return  # EOF: server already exited, also silence.
            self.raw_lines.append(extra)
            raise AssertionError(
                "expected silence, server sent: %r" % (extra,))

    def shutdown(self, via="quit"):
        """Stop the server; record returncode + stderr. Never raises."""
        proc = self.proc
        if proc.poll() is None and via:
            try:
                self.request(via, None, req_id="bye-%s" % via, timeout=5)
            except Exception:
                pass
        try:
            proc.stdin.close()
        except Exception:
            pass
        try:
            proc.wait(timeout=15)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait(timeout=15)
        self.returncode = proc.returncode
        try:
            self.stderr_text = proc.stderr.read()
        except Exception:
            self.stderr_text = ""


class ServerBase(unittest.TestCase):
    """Fresh temp DB/cache + one server process per test."""

    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="openspore-srv-")
        self.db = os.path.join(self.tmp, "spore.db")
        self.cache = os.path.join(self.tmp, "cache")
        os.makedirs(self.cache)
        self.extra_env = {}
        self.srv = None
        self.start_server()
        self.addCleanup(self._cleanup)

    def start_server(self, extra=None):
        merged = dict(self.extra_env)
        if extra:
            merged.update(extra)
        self.srv = StdioServer(_child_env(self.db, self.cache, merged))

    def _cleanup(self):
        try:
            if self.srv is not None:
                self.srv.shutdown()
        finally:
            shutil.rmtree(self.tmp, ignore_errors=True)

    # -- shared assertions ------------------------------------------------ #
    def assert_rpc_ok(self, response, req_id):
        self.assertEqual(response.get("jsonrpc"), "2.0", response)
        self.assertEqual(response.get("id"), req_id, response)
        self.assertIn("result", response, response)
        self.assertNotIn("error", response, response)
        return response["result"]

    def assert_rpc_error(self, response, req_id, code):
        self.assertEqual(response.get("jsonrpc"), "2.0", response)
        self.assertEqual(response.get("id"), req_id, response)
        self.assertIn("error", response, response)
        self.assertEqual(response["error"]["code"], code, response)
        return response["error"]

    def assert_inband(self, response, req_id):
        """tools/call answered with an in-band result dict (never a crash)."""
        result = self.assert_rpc_ok(response, req_id)
        self.assertIsInstance(result, dict, response)
        self.assertIn(result.get("status"), ("ok", "error"), response)
        if result["status"] == "error":
            self.assertIs(result.get("ok"), False, response)
            self.assertTrue(result.get("code"), response)
            self.assertTrue(result.get("message"), response)
        return result


# --------------------------------------------------------------------------- #
# Server launch.
# --------------------------------------------------------------------------- #
class TestLaunch(ServerBase):
    def test_launch_initialize(self):
        self.assertIsNone(self.srv.proc.poll(), "server died on launch")
        result = self.assert_rpc_ok(
            self.srv.request("initialize", {}, req_id=1), 1)
        self.assertEqual(result, {
            "protocolVersion": "2025-06-18",
            "capabilities": {"tools": {"listChanged": False}},
            "serverInfo": {
                "name": "openspore-mcp",
                "version": "0.1.0",
            },
        })
        self.assertNotIn("server", result)
        self.assertNotIn("version", result)
        self.assertNotIn("protocol", result)
        self.assertNotIn("tools", result)
        # Still alive after the handshake: launch implies persistence.
        self.assertIsNone(self.srv.proc.poll())

    def test_launch_reports_start_on_stderr(self):
        self.srv.request("ping", None, req_id=1)
        self.srv.shutdown()
        self.assertEqual(self.srv.returncode, 0)
        self.assertIn("starting", self.srv.stderr_text)
        self.assertIn("stopped", self.srv.stderr_text)


# --------------------------------------------------------------------------- #
# Request/response protocol.
# --------------------------------------------------------------------------- #
class TestProtocol(ServerBase):
    def test_ping(self):
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=7), 7)
        self.assertEqual(result, {"status": "ok"})

    def test_tools_list_exact_24(self):
        result = self.assert_rpc_ok(
            self.srv.request("tools/list", None, req_id=2), 2)
        names = [tool["name"] for tool in result["tools"]]
        self.assertEqual(names, EXPECTED_TOOLS)
        for tool in result["tools"]:
            self.assertTrue(tool["description"])
            schema = tool["inputSchema"]
            self.assertEqual(schema["type"], "object")
            self.assertIn("properties", schema)
            self.assertIn("required", schema)

    def test_request_ids_echoed_verbatim(self):
        for req_id in (1, "abc", 0, 999999):
            resp = self.srv.request("ping", None, req_id=req_id)
            self.assertEqual(resp.get("id"), req_id, resp)
            self.assertEqual(resp["result"], {"status": "ok"})

    def test_batch_mixed(self):
        self.srv.send_raw(json.dumps([
            {"jsonrpc": "2.0", "id": 11, "method": "ping"},
            {"jsonrpc": "2.0", "id": 12, "method": "tools/list"},
            {"jsonrpc": "2.0", "method": "notifications/initialized"},
        ]))
        batch = json.loads(self.srv.read_line())
        self.assertIsInstance(batch, list, batch)
        self.assertEqual(len(batch), 2, batch)  # notification: no reply
        by_id = {item["id"]: item for item in batch}
        self.assertEqual(by_id[11]["result"], {"status": "ok"})
        self.assertEqual(len(by_id[12]["result"]["tools"]), 24)


# --------------------------------------------------------------------------- #
# All 24 tools at smoke level over the real protocol.
# --------------------------------------------------------------------------- #
class TestAllToolsSmoke(ServerBase):
    def test_all_24_tools_empty_args_no_crash(self):
        for i, name in enumerate(EXPECTED_TOOLS):
            resp = self.srv.call_tool(name, {}, req_id=100 + i)
            result = self.assert_inband(resp, 100 + i)
            if result["status"] == "error":
                self.assertIn(result["code"], GRACEFUL_CODES,
                              (name, result))
        # Server survived all 24: still answering.
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=999), 999)
        self.assertEqual(result, {"status": "ok"})

    def test_all_24_tools_minimal_args_no_crash(self):
        for i, name in enumerate(EXPECTED_TOOLS):
            resp = self.srv.call_tool(name, SMOKE_ARGS[name], req_id=200 + i)
            result = self.assert_inband(resp, 200 + i)
            if result["status"] == "error":
                self.assertIn(result["code"], GRACEFUL_CODES,
                              (name, result))
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=999), 999)
        self.assertEqual(result, {"status": "ok"})

    def test_human_gates_stay_closed(self):
        # Trust env is stripped: gated tools must refuse, never run.
        for name, args in (("trace_run", {}),
                           ("status_update", {}),
                           ("fixture_check", {"rebuild": True})):
            resp = self.srv.call_tool(name, args, req_id=name)
            result = self.assert_inband(resp, name)
            self.assertEqual(result["status"], "error", (name, result))
            self.assertEqual(result["code"], "approval_required",
                             (name, result))

    def test_test_run_never_executes_here(self):
        resp = self.srv.call_tool("test_run", {"selector": "all"},
                                  req_id=1)
        result = self.assert_inband(resp, 1)
        self.assertEqual(result["status"], "error", result)
        self.assertEqual(result["code"], "blocked_no_ctest", result)


# --------------------------------------------------------------------------- #
# Malformed input.
# --------------------------------------------------------------------------- #
class TestMalformed(ServerBase):
    def test_parse_error(self):
        self.srv.send_raw("{oops not json")
        resp = json.loads(self.srv.read_line())
        self.assertIsNone(resp["id"], resp)
        self.assertEqual(resp["error"]["code"], -32700, resp)

    def test_invalid_requests(self):
        cases = [
            (json.dumps({"jsonrpc": "2.0", "id": 21}), -32600),  # no method
            (json.dumps("just a string"), -32600),  # non-object
            ("[]", -32600),  # empty batch
            (json.dumps({"jsonrpc": "2.0", "id": 22,
                         "method": "frobnicate"}), -32601),  # unknown method
        ]
        for i, (line, code) in enumerate(cases):
            self.srv.send_raw(line)
            resp = json.loads(self.srv.read_line())
            self.assertEqual(resp["error"]["code"], code, (line, resp))
            self.assertEqual(resp["jsonrpc"], "2.0", resp)

    def test_tools_call_param_variants(self):
        # No params at all -> missing name; name missing / not a string;
        # arguments not an object; params not an object.
        lines = [
            json.dumps({"jsonrpc": "2.0", "id": 32, "method": "tools/call"}),
            json.dumps({"jsonrpc": "2.0", "id": 33, "method": "tools/call",
                        "params": {"arguments": {}}}),
            json.dumps({"jsonrpc": "2.0", "id": 34, "method": "tools/call",
                        "params": {"name": 42}}),
            json.dumps({"jsonrpc": "2.0", "id": 35, "method": "tools/call",
                        "params": {"name": "kg_query",
                                   "arguments": [1, 2]}}),
            json.dumps({"jsonrpc": "2.0", "id": 36, "method": "tools/call",
                        "params": ["a", "list"]}),
        ]
        for line in lines:
            self.srv.send_raw(line)
            resp = json.loads(self.srv.read_line())
            self.assertEqual(resp["error"]["code"], -32602, (line, resp))

    def test_blank_lines_ignored(self):
        self.srv.send_raw("")
        self.srv.send_raw("   ")
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=40), 40)
        self.assertEqual(result, {"status": "ok"})


# --------------------------------------------------------------------------- #
# Error handling: failures stay in-band, the server keeps running.
# --------------------------------------------------------------------------- #
class TestErrorHandling(ServerBase):
    def test_unknown_tool_is_method_not_found(self):
        resp = self.srv.call_tool("no_such_tool_xyz", {}, req_id=51)
        self.assert_rpc_error(resp, 51, -32601)
        self.assertIn("no_such_tool_xyz", resp["error"]["message"])

    def test_inband_errors_do_not_kill_server(self):
        # A run of failures, then proof of life.
        self.srv.call_tool("no_such_tool_xyz", {}, req_id=52)
        self.srv.send_raw("{broken json")
        self.srv.read_line()  # consume the -32700 (checked elsewhere)
        self.srv.call_tool("kg_neighbors", {}, req_id=53)  # missing_param
        resp = self.srv.call_tool("queue_op", {}, req_id=54)  # invalid_params
        result = self.assert_inband(resp, 54)
        self.assertEqual(result["code"], "invalid_params", result)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=55), 55)
        self.assertEqual(result, {"status": "ok"})
        self.assertIsNone(self.srv.proc.poll())

    def test_tool_domain_errors_are_inband(self):
        resp = self.srv.call_tool("kg_neighbors", {}, req_id=56)
        result = self.assert_inband(resp, 56)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "missing_param")
        resp = self.srv.call_tool("kg_record", {}, req_id=57)
        result = self.assert_inband(resp, 57)
        self.assertEqual(result["code"], "missing_reason")


# --------------------------------------------------------------------------- #
# KG temp-DB operations.
# --------------------------------------------------------------------------- #
class TestKnowledgeGraph(ServerBase):
    def test_kg_record_then_query_and_neighbors(self):
        name = "srv-integration-fn"
        resp = self.srv.call_tool("kg_record", {
            "reason": "srv integration probe",
            "nodes": [{"label": "function", "name": name,
                       "attrs": {"va": "0x00401000"}}],
        }, req_id=61)
        result = self.assert_inband(resp, 61)
        self.assertEqual(result["status"], "ok", result)
        self.assertEqual(result["reason"], "srv integration probe")
        self.assertEqual(result["inserted"]["nodes"], 1)

        resp = self.srv.call_tool("kg_query", {"query": name}, req_id=62)
        result = self.assert_inband(resp, 62)
        self.assertEqual(result["status"], "ok", result)
        self.assertTrue(any(node["name"] == name
                            for node in result["nodes"]), result)

        resp = self.srv.call_tool("kg_neighbors", {"name": name}, req_id=63)
        result = self.assert_inband(resp, 63)
        self.assertEqual(result["status"], "ok", result)
        self.assertEqual(result["center"]["name"], name)

    def test_kg_record_rejects_status_writes(self):
        resp = self.srv.call_tool("kg_record", {
            "reason": "status smuggling probe",
            "nodes": [{"label": "function", "name": "srv-evil",
                       "status": "replaced-verified"}],
        }, req_id=64)
        result = self.assert_inband(resp, 64)
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "status_forbidden")

    def test_pipeline_state_reflects_temp_db(self):
        self.srv.call_tool("kg_record", {
            "reason": "pipeline probe",
            "nodes": [{"label": "function", "name": "srv-pipe-fn"}],
        }, req_id=65)
        resp = self.srv.request("tools/call", {
            "name": "pipeline_state", "arguments": {}}, req_id=66)
        result = self.assert_inband(resp, 66)
        self.assertEqual(result["status"], "ok", result)
        self.assertEqual(result["db"]["path"], self.db, result)
        self.assertGreaterEqual(result["kg_counts"].get("node", 0), 1,
                                result)

    def test_target_select_finds_queued_candidate(self):
        self.srv.call_tool("queue_op", {
            "op": "insert", "kind": "function", "va": "0x00401000",
            "name": "srv-target-fn", "binary_sha256": "srv-test-sha",
        }, req_id=67)
        resp = self.srv.call_tool("target_select",
                                  {"target": "srv-target-fn"}, req_id=68)
        result = self.assert_inband(resp, 68)
        self.assertEqual(result["status"], "ok", result)
        self.assertTrue(any(cand["name"] == "srv-target-fn"
                            for cand in result["candidates"]), result)
        self.assertEqual(result["selected"]["name"], "srv-target-fn",
                         result)


# --------------------------------------------------------------------------- #
# Queue operations lifecycle.
# --------------------------------------------------------------------------- #
class TestQueue(ServerBase):
    def test_queue_full_lifecycle(self):
        resp = self.srv.call_tool("queue_op", {
            "op": "insert", "kind": "function", "va": "0x00402000",
            "name": "srv-queue-fn", "binary_sha256": "srv-test-sha",
        }, req_id=71)
        result = self.assert_inband(resp, 71)
        self.assertEqual(result["status"], "ok", result)
        self.assertTrue(result["inserted"], result)
        inv_id = result["id"]

        resp = self.srv.call_tool("queue_op", {"op": "get", "id": inv_id},
                                  req_id=72)
        result = self.assert_inband(resp, 72)
        self.assertEqual(result["investigation"]["id"], inv_id)

        resp = self.srv.call_tool("queue_op", {
            "op": "update", "id": inv_id, "stage": "ACTIVE"}, req_id=73)
        result = self.assert_inband(resp, 73)
        self.assertEqual(result["investigation"]["stage"], "ACTIVE")

        resp = self.srv.call_tool("queue_op", {"op": "list"}, req_id=74)
        result = self.assert_inband(resp, 74)
        self.assertTrue(any(item["id"] == inv_id
                            for item in result["investigations"]), result)

        resp = self.srv.call_tool("queue_op", {"op": "close", "id": inv_id},
                                  req_id=75)
        result = self.assert_inband(resp, 75)
        self.assertTrue(result["closed"], result)

    def test_queue_errors(self):
        # Seed one row first so the investigations table exists; a
        # pristine DB answers empty_database (covered in stale-state).
        resp = self.srv.call_tool("queue_op", {
            "op": "insert", "kind": "function", "va": "0x1",
            "binary_sha256": "srv-test-sha", "id": "srv-bogus"},
            req_id=77)
        self.assert_inband(resp, 77)
        resp = self.srv.call_tool("queue_op",
                                  {"op": "get", "id": "srv-missing-id"},
                                  req_id=76)
        result = self.assert_inband(resp, 76)
        self.assertEqual(result["code"], "not_found", result)

        resp = self.srv.call_tool("queue_op", {
            "op": "update", "id": "srv-bogus", "bogus_field": 1},
            req_id=78)
        result = self.assert_inband(resp, 78)
        self.assertEqual(result["code"], "invalid_params", result)


# --------------------------------------------------------------------------- #
# Decompilation cache over stdio (Ghidra offline: cache is the only source).
# --------------------------------------------------------------------------- #
class TestDecompileCache(ServerBase):
    RVA = "0x6f1a2b"
    C_TEXT = "int srv_cache_probe(void){return 7;}\n"

    def _seed_cache(self):
        from tools.mcp import cache as dcc
        old = os.environ.get("OPENSPORE_MCP_CACHE")
        os.environ["OPENSPORE_MCP_CACHE"] = self.cache
        try:
            stored = dcc.store(_probe_sha(), self.RVA, "unknown",
                               "SporeApp.exe", self.C_TEXT)
        finally:
            if old is None:
                os.environ.pop("OPENSPORE_MCP_CACHE", None)
            else:
                os.environ["OPENSPORE_MCP_CACHE"] = old
        self.assertTrue(stored["stored"], stored)

    def test_cache_hit_offline_with_provenance(self):
        self._seed_cache()
        resp = self.srv.call_tool("ghidra_decompile", {"rva": self.RVA},
                                  req_id=81)
        result = self.assert_inband(resp, 81)
        self.assertEqual(result["status"], "ok", result)
        self.assertTrue(result["cached"], result)
        self.assertIn("srv_cache_probe", result["decompiled"], result)
        # Provenance retained: stored key, identity, evidence note.
        self.assertIn("provenance", result, result)
        self.assertIn("evidence_note", result, result)
        self.assertIn("binary_sha256", result, result)
        self.assertEqual(result["rva"], self.RVA, result)


# --------------------------------------------------------------------------- #
# Provenance on every evidence-carrying result.
# --------------------------------------------------------------------------- #
class TestProvenance(ServerBase):
    def test_ghidra_results_carry_identity(self):
        from tools.mcp import cache as dcc
        old = os.environ.get("OPENSPORE_MCP_CACHE")
        os.environ["OPENSPORE_MCP_CACHE"] = self.cache
        try:
            dcc.store(_probe_sha(), "0x6f1a2b", "unknown",
                      "SporeApp.exe", "int srv_prov(void){return 1;}\n")
        finally:
            if old is None:
                os.environ.pop("OPENSPORE_MCP_CACHE", None)
            else:
                os.environ["OPENSPORE_MCP_CACHE"] = old
        resp = self.srv.call_tool("ghidra_decompile", {"rva": "0x6f1a2b"},
                                  req_id=91)
        result = self.assert_inband(resp, 91)
        self.assertEqual(result["status"], "ok", result)
        self.assertIn("binary_sha256", result, result)
        self.assertIn("program", result, result)
        self.assertIn("evidence_note", result, result)

    def test_kg_record_echoes_reason(self):
        resp = self.srv.call_tool("kg_record", {
            "reason": "provenance echo check",
            "tests": [{"name": "srv-prov-test", "pass": 1}],
        }, req_id=92)
        result = self.assert_inband(resp, 92)
        self.assertEqual(result["status"], "ok", result)
        self.assertEqual(result["reason"], "provenance echo check")
        self.assertEqual(result["inserted"]["tests"], 1)

    def test_trace_status_carries_provenance_note(self):
        resp = self.srv.call_tool("trace_status", {}, req_id=93)
        result = self.assert_inband(resp, 93)
        self.assertEqual(result["status"], "ok", result)
        self.assertIn("note", result, result)
        self.assertIn("probe_sets", result, result)


# --------------------------------------------------------------------------- #
# Stale-state handling.
# --------------------------------------------------------------------------- #
class TestStaleState(ServerBase):
    def test_stale_ghidra_version_never_serves_stale_text(self):
        from tools.mcp import cache as dcc
        old = os.environ.get("OPENSPORE_MCP_CACHE")
        os.environ["OPENSPORE_MCP_CACHE"] = self.cache
        try:
            dcc.store(_probe_sha(), "0x6f1a2b", "unknown",
                      "SporeApp.exe", "int srv_stale(void){return 2;}\n")
        finally:
            if old is None:
                os.environ.pop("OPENSPORE_MCP_CACHE", None)
            else:
                os.environ["OPENSPORE_MCP_CACHE"] = old
        # Explicit different live version: exact key misses, bridge is
        # offline, so this must be a graceful offline error -- and must
        # never leak the stored text for the wrong key.
        resp = self.srv.call_tool("ghidra_decompile", {
            "rva": "0x6f1a2b", "ghidra_version": "stale-test-v2"},
            req_id=101)
        result = self.assert_inband(resp, 101)
        self.assertEqual(result["status"], "error", result)
        self.assertIn(result["code"],
                      ("ghidra_offline", "empty_decompile"), result)
        self.assertNotIn("srv_stale", json.dumps(result), result)

    def test_empty_db_is_structured_not_crash(self):
        # Fresh temp DB file does not exist yet: reads degrade gracefully.
        resp = self.srv.call_tool("kg_query", {}, req_id=102)
        result = self.assert_inband(resp, 102)
        self.assertEqual(result["status"], "error", result)
        self.assertEqual(result["code"], "empty_database", result)
        resp = self.srv.call_tool("queue_op", {"op": "list"}, req_id=103)
        result = self.assert_inband(resp, 103)
        self.assertEqual(result["code"], "empty_database", result)

    def test_terminal_queue_close_is_idempotent(self):
        resp = self.srv.call_tool("queue_op", {
            "op": "insert", "kind": "subsystem", "subsystem": "srv-stale",
            "binary_sha256": "srv-test-sha"}, req_id=104)
        inv_id = self.assert_inband(resp, 104)["id"]
        first = self.assert_inband(self.srv.call_tool(
            "queue_op", {"op": "close", "id": inv_id}, req_id=105), 105)
        self.assertTrue(first["closed"], first)
        second = self.assert_inband(self.srv.call_tool(
            "queue_op", {"op": "close", "id": inv_id}, req_id=106), 106)
        # Never deleted, never re-closed: idempotent negative.
        self.assertFalse(second["closed"], second)
        self.assertEqual(second["previous_status"], "done", second)

    def test_ambiguous_node_name_is_structured(self):
        self.srv.call_tool("kg_record", {
            "reason": "ambiguity probe",
            "nodes": [{"label": "function", "name": "srv-dup"},
                      {"label": "class", "name": "srv-dup"}],
        }, req_id=107)
        resp = self.srv.call_tool("kg_neighbors", {"name": "srv-dup"},
                                  req_id=108)
        result = self.assert_inband(resp, 108)
        self.assertEqual(result["status"], "error", result)
        self.assertEqual(result["code"], "ambiguous", result)


# --------------------------------------------------------------------------- #
# Clean shutdown.
# --------------------------------------------------------------------------- #
class TestShutdown(ServerBase):
    def test_quit_request_answered_then_exits_zero(self):
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=111), 111)
        self.assertEqual(result, {"status": "ok"})
        resp = self.srv.request("quit", None, req_id=112)
        self.assertEqual(resp["id"], 112, resp)
        self.assertEqual(resp["result"], {"status": "shutdown"}, resp)
        self.srv.shutdown(via=None)  # already stopping; just reap
        self.assertEqual(self.srv.returncode, 0, self.srv.stderr_text)

    def test_shutdown_alias(self):
        resp = self.srv.request("shutdown", None, req_id=113)
        self.assertEqual(resp["result"], {"status": "shutdown"}, resp)
        self.srv.shutdown(via=None)
        self.assertEqual(self.srv.returncode, 0)

    def test_eof_is_clean_shutdown(self):
        self.srv.proc.stdin.close()
        self.srv.proc.wait(timeout=15)
        self.assertEqual(self.srv.proc.returncode, 0)
        self.srv.shutdown(via=None)
        self.assertEqual(self.srv.returncode, 0)

    def test_notification_gets_no_response(self):
        self.srv.notify("notifications/initialized")
        self.srv.assert_no_response()
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=114), 114)
        self.assertEqual(result, {"status": "ok"})

    def test_quit_notification_stops_silently(self):
        self.srv.notify("quit")
        # Give the loop a beat, then reap: no response line was emitted.
        self.srv.assert_no_response(timeout=2.0)
        self.srv.shutdown(via=None)
        self.assertEqual(self.srv.returncode, 0)


# --------------------------------------------------------------------------- #
# No stdout logging contamination.
# --------------------------------------------------------------------------- #
class TestStdoutClean(ServerBase):
    def test_every_stdout_line_is_jsonrpc(self):
        self.srv.request("initialize", {}, req_id=121)
        self.srv.call_tool("pipeline_state", {}, req_id=122)
        self.srv.call_tool("kg_neighbors", {}, req_id=123)  # in-band error
        self.srv.send_raw("{broken json")  # parse error
        self.srv.read_line()
        self.srv.send_raw(json.dumps([
            {"jsonrpc": "2.0", "id": 124, "method": "ping"},
            {"jsonrpc": "2.0", "method": "notifications/initialized"},
        ]))
        self.srv.read_line()  # batch array
        for line in self.srv.raw_lines:
            self.assertTrue(line.strip(), "blank line on stdout")
            message = json.loads(line)  # every line parses ...
            items = message if isinstance(message, list) else [message]
            for item in items:
                self.assertEqual(item.get("jsonrpc"), "2.0", item)
                self.assertTrue("result" in item or "error" in item,
                                item)
        self.srv.shutdown()
        self.assertTrue(self.srv.stderr_text.strip(),
                        "expected log output on stderr")


# --------------------------------------------------------------------------- #
# Fresh-clone safety: empty HOME, SPORE absent, no secrets.
# --------------------------------------------------------------------------- #
class TestFreshClone(ServerBase):
    def test_empty_home_server_works(self):
        home = os.path.join(self.tmp, "empty-home")
        os.makedirs(home)
        self.srv.shutdown(via=None)
        self.srv.proc.wait(timeout=15)
        self.start_server(extra={"HOME": home})
        result = self.assert_rpc_ok(
            self.srv.request("initialize", {}, req_id=131), 131)
        self.assertEqual(result["serverInfo"]["name"], "openspore-mcp")
        result = self.assert_rpc_ok(
            self.srv.request("tools/list", None, req_id=132), 132)
        self.assertEqual(len(result["tools"]), 24)

    def test_spore_absent_degrades_gracefully(self):
        empty_root = os.path.join(self.tmp, "empty-root")
        os.makedirs(empty_root)
        self.srv.shutdown(via=None)
        self.srv.proc.wait(timeout=15)
        # Bare clone: no SPORE/, no dossiers, no committed snapshots --
        # but the real temp DB/cache/scratch env stays wired.
        self.start_server(extra={"OPENSPORE_ROOT": empty_root})
        result = self.assert_rpc_ok(
            self.srv.request("initialize", {}, req_id=141), 141)
        self.assertEqual(result["serverInfo"]["name"], "openspore-mcp", result)

        resp = self.srv.call_tool("asset_resolve", {}, req_id=142)
        result = self.assert_inband(resp, 142)
        self.assertEqual(result["code"], "no_spo", result)

        resp = self.srv.call_tool("asset_scan", {}, req_id=143)
        result = self.assert_inband(resp, 143)
        self.assertEqual(result["code"], "no_spo", result)

        # Gates close before any external check: still approval_required.
        resp = self.srv.call_tool("trace_run", {}, req_id=144)
        result = self.assert_inband(resp, 144)
        self.assertEqual(result["code"], "approval_required", result)

        # Ghidra unreachable here: structured offline, never a crash.
        resp = self.srv.call_tool("ghidra_decompile",
                                  {"function": "0x00401000"}, req_id=145)
        result = self.assert_inband(resp, 145)
        self.assertEqual(result["status"], "error", result)
        self.assertIn(result["code"], ("ghidra_offline", "not_found"),
                      result)

        # KG schema.sql lives under the (empty) root: schema init fails,
        # but the failure is a structured db_error, not a traceback.
        resp = self.srv.call_tool("kg_record", {
            "reason": "fresh-clone probe",
            "nodes": [{"label": "function", "name": "srv-fresh"}],
        }, req_id=146)
        result = self.assert_inband(resp, 146)
        self.assertEqual(result["status"], "error", result)

        # Proof of life + clean shutdown from the degraded state.
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=147), 147)
        self.assertEqual(result, {"status": "ok"})
        self.assertIsNone(self.srv.proc.poll())

    def test_no_trust_env_leaks_in(self):
        self.assertNotEqual(os.environ.get("OPENSPORE_MCP_TRUSTED"), "1")
        resp = self.srv.call_tool("status_update", {"subsystem": "x"},
                                  req_id=151)
        result = self.assert_inband(resp, 151)
        self.assertEqual(result["code"], "approval_required", result)


if __name__ == "__main__":
    unittest.main()
