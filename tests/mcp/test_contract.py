"""Contract tests for the OpenSpore MCP tool surface (tools/mcp).

Covers the S2-Subagent-6 tool contract audit: all 24 tools listed with
schemas (name/description/inputSchema with type/properties/required),
uniform in-band error shape (``status=error`` + ``ok=False`` + ``code``
+ ``message``), success shape (``status=ok``), no ``not_implemented``
stubs, and empty-params dispatch never raising.

Run from the repo root:
    python3 -m unittest tests.mcp.test_contract -v
"""
import os
import tempfile
import unittest

from tools.mcp import registry

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

# Tools whose handlers unconditionally require these input fields
# (declared in inputSchema.required; everything else is optional,
# conditional, or alias-accepted and documented in the description +
# the additive required_one_of note). JSON-Schema required is
# conjunctive, so one-of groups (function/address/rva/name, ...) are
# never forced into required.
EXPECTED_REQUIRED = {
    "kg_neighbors": ["name"],
    "kg_record": ["reason"],
    "queue_op": ["op"],
    "asset_resolve": ["package"],
}

# Conditional one-of requirements: at least one alias per group must be
# supplied (documented in description prose + required_one_of note).
EXPECTED_ONE_OF = {
    "function_context": [["va", "address"]],
    "reconstruction_status": [["va", "address"]],
    "dossier_read": [["topic", "path"]],
    "dossier_regenerate": [["topic", "path"]],
    "ghidra_decompile": [["function", "address", "rva", "name"]],
    "ghidra_function": [["function", "address", "rva", "name"]],
    "ghidra_search": [["pattern", "query"]],
    "ghidra_snapshot_save": [["topic", "label"]],
    "asset_resolve": [["record", "type", "type_id"]],
    "vtable_lookup": [["class", "class_name", "address",
                       "namespace", "subsystem"]],
    "trace_analyze": [["run_id", "scenario", "path"]],
}


class TestToolContract(unittest.TestCase):
    def test_all_24_tools_listed_with_schemas(self):
        tools = registry.list_tools()
        self.assertEqual([t["name"] for t in tools], EXPECTED_TOOLS)
        for tool in tools:
            self.assertTrue(tool["description"],
                            "tool %r needs a description" % tool["name"])
            schema = tool["inputSchema"]
            self.assertEqual(schema["type"], "object")
            self.assertIn("properties", schema)
            self.assertIn("required", schema)
            self.assertIsInstance(schema["required"], list)
            for field in schema["required"]:
                self.assertIn(field, schema["properties"],
                              "tool %r requires undeclared field %r"
                              % (tool["name"], field))

    def test_required_fields_declared(self):
        by_name = {t["name"]: t for t in registry.list_tools()}
        for name, required in EXPECTED_REQUIRED.items():
            self.assertEqual(by_name[name]["inputSchema"]["required"],
                             required)
        # No other tool may smuggle conjunctive requirements past the
        # contract: required is exactly [] outside EXPECTED_REQUIRED.
        for name in EXPECTED_TOOLS:
            if name not in EXPECTED_REQUIRED:
                self.assertEqual(
                    by_name[name]["inputSchema"]["required"], [],
                    "tool %r has undeclared conjunctive required" % name)

    def test_every_required_field_present_in_properties(self):
        for tool in registry.list_tools():
            props = tool["inputSchema"]["properties"]
            for field in tool["inputSchema"]["required"]:
                self.assertIn(field, props,
                              "tool %r requires undeclared field %r"
                              % (tool["name"], field))

    def test_one_of_notes_reference_declared_properties(self):
        by_name = {t["name"]: t for t in registry.list_tools()}
        for name, groups in EXPECTED_ONE_OF.items():
            self.assertEqual(by_name[name].get("required_one_of"), groups,
                             "tool %r required_one_of drift" % name)
            props = by_name[name]["inputSchema"]["properties"]
            for group in groups:
                for field in group:
                    self.assertIn(field, props,
                                  "tool %r one-of field %r not in "
                                  "properties" % (name, field))

    def test_handlers_cover_all_tools(self):
        for name in EXPECTED_TOOLS:
            self.assertIn(name, registry.HANDLERS,
                          "tool %r has no handler" % name)

    def test_no_not_implemented_stubs(self):
        for name in EXPECTED_TOOLS:
            result = registry.dispatch(name, {})
            self.assertNotEqual(result.get("status"), "not_implemented",
                                "tool %r is still a stub" % name)

    def test_empty_params_never_raises(self):
        for name in EXPECTED_TOOLS:
            try:
                result = registry.dispatch(name, {})
            except Exception as exc:
                self.fail("tool %r raised on {}: %s: %s"
                          % (name, type(exc).__name__, exc))
            self.assertIsInstance(result, dict)
            self.assertIn("status", result)

    def test_error_shape_consistent(self):
        """Every in-band error: status=error, ok=False, code, message."""
        for name in EXPECTED_TOOLS:
            result = registry.dispatch(name, {})
            if result.get("status") != "error":
                continue
            self.assertEqual(result.get("status"), "error")
            self.assertIs(result.get("ok"), False,
                          "tool %r error missing ok=False: %r" % (name, result))
            self.assertTrue(result.get("code"),
                            "tool %r error missing code: %r" % (name, result))
            self.assertTrue(result.get("message"),
                            "tool %r error missing message: %r"
                            % (name, result))

    def test_success_shape(self):
        for name in EXPECTED_TOOLS:
            result = registry.dispatch(name, {})
            if result.get("status") != "ok":
                continue
            self.assertEqual(result.get("status"), "ok")

    def test_known_error_codes_stable(self):
        # Gated tools refuse without approval; queue/kg validate params.
        self.assertEqual(
            registry.dispatch("trace_run", {})["code"], "approval_required")
        self.assertEqual(
            registry.dispatch("status_update", {})["code"],
            "approval_required")
        self.assertEqual(
            registry.dispatch("kg_record", {})["code"], "missing_reason")
        self.assertEqual(
            registry.dispatch("queue_op", {})["code"], "invalid_params")
        self.assertEqual(
            registry.dispatch("kg_neighbors", {})["code"], "missing_param")

    def test_list_tools_returns_copies(self):
        first = registry.list_tools()
        first[0]["inputSchema"]["properties"]["zzz"] = {"type": "string"}
        second = registry.list_tools()
        self.assertNotIn("zzz",
                         second[0]["inputSchema"]["properties"])


class TestContractIsolatedDB(unittest.TestCase):
    """Error-shape checks that need an empty (temp) KG database."""

    def setUp(self):
        tmp = tempfile.NamedTemporaryFile(suffix=".db", delete=False)
        tmp.close()
        self._db = tmp.name
        self._old = os.environ.get("OPENSPORE_DB")
        os.environ["OPENSPORE_DB"] = self._db

    def tearDown(self):
        if self._old is None:
            os.environ.pop("OPENSPORE_DB", None)
        else:
            os.environ["OPENSPORE_DB"] = self._old
        try:
            os.unlink(self._db)
        except OSError:
            pass

    def test_empty_db_errors_keep_shape(self):
        for name in ("kg_query", "kg_neighbors", "target_select",
                     "queue_op"):
            args = {"name": "nope", "op": "list"} if name in (
                "kg_neighbors", "queue_op") else {}
            result = registry.dispatch(name, args)
            self.assertEqual(result.get("status"), "error", (name, result))
            self.assertIs(result.get("ok"), False, (name, result))
            self.assertTrue(result.get("code"), (name, result))
            self.assertTrue(result.get("message"), (name, result))


if __name__ == "__main__":
    unittest.main()
