"""Protocol-level tests for the -32602 vs in-band error split (S2.1 E+F).

Exercises the ACTUAL stdio protocol via subprocess (same harness as
test_server.py): -32602 is reserved for a malformed tools/call envelope
(params/arguments not an object, bad tool name); domain validation
(missing/invalid fields in a well-formed object) stays in-band with
status=error + ok=False + code + message (+ additive ``field`` key for
absent fields). Malformed input must never crash the server.

Run from the repo root:
    python3 -m unittest tests.mcp.test_protocol_errors -v
"""
import json
import unittest

from tests.mcp.test_server import ServerBase


class TestEnvelopeVsDomain(ServerBase):
    def test_arguments_string_is_32602(self):
        self.srv.send_raw(json.dumps({
            "jsonrpc": "2.0", "id": 1, "method": "tools/call",
            "params": {"name": "kg_query", "arguments": "x"}}))
        resp = json.loads(self.srv.read_line())
        self.assert_rpc_error(resp, 1, -32602)

    def test_arguments_list_is_32602(self):
        self.srv.send_raw(json.dumps({
            "jsonrpc": "2.0", "id": 2, "method": "tools/call",
            "params": {"name": "kg_query", "arguments": [1, 2]}}))
        resp = json.loads(self.srv.read_line())
        self.assert_rpc_error(resp, 2, -32602)

    def test_params_list_is_32602(self):
        self.srv.send_raw(json.dumps({
            "jsonrpc": "2.0", "id": 3, "method": "tools/call",
            "params": ["a", "list"]}))
        resp = json.loads(self.srv.read_line())
        self.assert_rpc_error(resp, 3, -32602)

    def test_bad_tool_name_is_32602(self):
        for req_id, params in (
                (4, {"arguments": {}}),
                (5, {"name": 42, "arguments": {}}),
                (6, {"name": "", "arguments": {}})):
            self.srv.send_raw(json.dumps({
                "jsonrpc": "2.0", "id": req_id, "method": "tools/call",
                "params": params}))
            resp = json.loads(self.srv.read_line())
            self.assert_rpc_error(resp, req_id, -32602)

    def test_missing_required_params_are_inband(self):
        # Well-formed objects with absent fields: in-band, never -32602.
        # Seed one investigation first so queue get/update/close reach
        # the id check instead of the empty_database path.
        self.srv.call_tool("queue_op", {
            "op": "insert", "kind": "function", "va": "0x1",
            "binary_sha256": "proto-test-sha"}, req_id=90)
        cases = [
            ("kg_neighbors", {}, "missing_param", "name"),
            ("kg_record", {}, "missing_reason", "reason"),
            ("queue_op", {"op": "get"}, "missing_param", "id"),
            ("queue_op", {"op": "update"}, "missing_param", "id"),
            ("queue_op", {"op": "close"}, "missing_param", "id"),
            ("ghidra_search", {}, "invalid_params", None),
            ("trace_analyze", {}, "blocked_unreadable", None),
        ]
        for i, (tool, args, code, field) in enumerate(cases):
            resp = self.srv.call_tool(tool, args, req_id=100 + i)
            result = self.assert_inband(resp, 100 + i)
            self.assertEqual(result["status"], "error", (tool, result))
            self.assertEqual(result["code"], code, (tool, result))
            if field is not None:
                self.assertEqual(result.get("field"), field,
                                 (tool, result))

    def test_wrong_types_are_inband(self):
        # Well-formed envelope, wrong-typed domain values: in-band.
        resp = self.srv.call_tool("kg_query",
                                  {"limit": "not-an-int"}, req_id=120)
        result = self.assert_inband(resp, 120)
        self.assertEqual(result["status"], "error", result)
        self.assertEqual(result["code"], "invalid_params", result)

        resp = self.srv.call_tool("target_select",
                                  {"limit": "bogus"}, req_id=121)
        result = self.assert_inband(resp, 121)
        self.assertEqual(result["status"], "error", result)
        self.assertEqual(result["code"], "invalid_params", result)

    def test_unknown_fields_do_not_crash(self):
        # additionalProperties True: unknown fields are tolerated.
        resp = self.srv.call_tool(
            "kg_query", {"no_such_field_xyz": 1}, req_id=130)
        self.assert_inband(resp, 130)  # ok or graceful error, not a crash
        resp = self.srv.call_tool(
            "pipeline_state", {"bogus": "x"}, req_id=131)
        result = self.assert_inband(resp, 131)
        self.assertEqual(result["status"], "ok", result)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=132), 132)
        self.assertEqual(result, {"status": "ok"})


class TestMalformedNeverCrashes(ServerBase):
    def test_malformed_json_is_parse_error_then_alive(self):
        self.srv.send_raw("{oops not json")
        resp = json.loads(self.srv.read_line())
        self.assertIsNone(resp["id"], resp)
        self.assertEqual(resp["error"]["code"], -32700, resp)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=140), 140)
        self.assertEqual(result, {"status": "ok"})

    def test_unknown_method_is_32601_then_alive(self):
        resp = self.srv.request("frobnicate", {}, req_id=141)
        self.assert_rpc_error(resp, 141, -32601)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=142), 142)
        self.assertEqual(result, {"status": "ok"})

    def test_unknown_tool_is_32601_then_alive(self):
        resp = self.srv.call_tool("no_such_tool_xyz", {}, req_id=143)
        self.assert_rpc_error(resp, 143, -32601)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=144), 144)
        self.assertEqual(result, {"status": "ok"})

    def test_batch_of_bad_items_never_crashes(self):
        self.srv.send_raw(json.dumps([
            {"jsonrpc": "2.0", "id": 150, "method": "tools/call",
             "params": {"name": "kg_query", "arguments": "x"}},
            {"jsonrpc": "2.0", "id": 151, "method": "frobnicate"},
            {"jsonrpc": "2.0", "id": 152, "method": "tools/call",
             "params": {"name": "kg_neighbors", "arguments": {}}},
            {"jsonrpc": "2.0", "id": 153, "method": "tools/call",
             "params": {"name": "no_such_tool_xyz", "arguments": {}}},
        ]))
        batch = json.loads(self.srv.read_line())
        by_id = {item["id"]: item for item in batch}
        self.assertEqual(by_id[150]["error"]["code"], -32602, batch)
        self.assertEqual(by_id[151]["error"]["code"], -32601, batch)
        # Domain failure rides in-band inside a normal result.
        self.assertEqual(by_id[152]["result"]["status"], "error", batch)
        self.assertEqual(by_id[152]["result"]["code"],
                         "missing_param", batch)
        self.assertEqual(by_id[153]["error"]["code"], -32601, batch)
        result = self.assert_rpc_ok(
            self.srv.request("ping", None, req_id=154), 154)
        self.assertEqual(result, {"status": "ok"})


if __name__ == "__main__":
    unittest.main()
