"""Unit tests for the Ghidra/dossier MCP tools (tools/mcp).

Covers: decompile disk-cache key behaviour (same key hits; changed
binary/rva/version/program miss), provenance retention, malformed
cache failing safe, graceful offline ``ghidra_offline`` (never raises),
RVA handling, dossier/vtable reads, deterministic writers, registry
wiring, and no-arbitrary-exec (params can never become shell commands
or escape the repo/tool dirs).

Run from the repo root:
    python3 -m unittest tests.mcp.test_ghidra -v
"""
import glob
import json
import os
import shutil
import tempfile
import unittest

from tools.mcp import cache as decompile_cache
from tools.mcp import config
from tools.mcp import ghidra_tools as gt
from tools.mcp import registry

ROOT = config.OPENSPORE_ROOT

_C_TEXT = "void FUN_00e806b0(void) { /* fake decompilation */ }\n"


class FakeClient(object):
    """In-test GhidraMCP stand-in (no network, no threads)."""

    def __init__(self, version="12.1.2-test"):
        self.base = "http://127.0.0.1:8089"
        self.calls = []
        self._version = version

    def version(self):
        return self._version

    def check_connection(self):
        return {"status": "ok"}

    def decompile(self, address):
        self.calls.append(("decompile", address))
        return {"status": "ok", "decompiled":
                "void at_%s(void) {}" % address.replace("0x", "")}

    def function_by_address(self, address):
        self.calls.append(("function_by_address", address))
        return {"status": "ok",
                "data": {"name": "FUN_%s" % address.replace("0x", ""),
                         "address": address, "size_bytes": 28,
                         "namespace": None, "callers": [],
                         "callees": ["FUN_00e5b790"]}}

    def analyze_function(self, address):
        self.calls.append(("analyze_function", address))
        return {"status": "ok", "data": {"signature": "void f(void)"}}

    def search_functions(self, pattern, limit=50):
        self.calls.append(("search_functions", pattern))
        return {"status": "ok", "functions": [
            {"name": "App::cCellModeStrategy::Update",
             "address": "0x00e80980", "namespace": "App"},
            {"name": "FUN_00e806b0", "address": "0x00e806b0",
             "namespace": None}]}


class OfflineClient(FakeClient):
    """Bridge down: every call is the structured offline error."""

    def version(self):
        return "unknown"

    def decompile(self, address):
        self.calls.append(("decompile", address))
        return {"status": "error", "code": "ghidra_offline",
                "message": "down", "hint": "start headless server"}

    def function_by_address(self, address):
        self.calls.append(("function_by_address", address))
        return {"status": "error", "code": "ghidra_offline",
                "message": "down"}

    def analyze_function(self, address):
        self.calls.append(("analyze_function", address))
        return {"status": "error", "code": "ghidra_offline",
                "message": "down"}

    def search_functions(self, pattern, limit=50):
        self.calls.append(("search_functions", pattern))
        return {"status": "error", "code": "ghidra_offline",
                "message": "down"}


class RaisingClient(FakeClient):
    """Transport raising raw exceptions (client must never propagate)."""

    def decompile(self, address):
        raise ConnectionRefusedError("bridge gone")


class GhidraTestBase(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="openspore-ghidra-")
        self._old_cache = os.environ.get("OPENSPORE_MCP_CACHE")
        os.environ["OPENSPORE_MCP_CACHE"] = self.tmp
        self._old_factory = gt._CLIENT_FACTORY
        self.fake = FakeClient()
        gt._CLIENT_FACTORY = lambda: self.fake
        gt._FUNCTION_MEMO.clear()
        gt._VTABLES_DOC["loaded"] = False
        gt._VTABLES_DOC["doc"] = None
        gt._DOSSIER_MOD["loaded"] = False
        gt._DOSSIER_MOD["mod"] = None

    def tearDown(self):
        gt._CLIENT_FACTORY = self._old_factory
        gt._FUNCTION_MEMO.clear()
        gt._VTABLES_DOC["loaded"] = False
        gt._VTABLES_DOC["doc"] = None
        gt._DOSSIER_MOD["loaded"] = False
        gt._DOSSIER_MOD["mod"] = None
        if self._old_cache is None:
            os.environ.pop("OPENSPORE_MCP_CACHE", None)
        else:
            os.environ["OPENSPORE_MCP_CACHE"] = self._old_cache
        shutil.rmtree(self.tmp, ignore_errors=True)


# --------------------------------------------------------------------------- #
# Cache key behaviour (5 cases) + provenance + malformed-safe.
# --------------------------------------------------------------------------- #
class TestCacheKey(GhidraTestBase):
    KEY = {"binary_sha256": "ab" * 32, "rva": "0xa806b0",
           "ghidra_version": "12.1.2", "program": "SporeApp.exe"}

    def _store(self, **over):
        kw = dict(self.KEY)
        kw.update(over)
        res = decompile_cache.store(kw["binary_sha256"], kw["rva"],
                                    kw["ghidra_version"], kw["program"],
                                    _C_TEXT, root=self.tmp)
        self.assertTrue(res["stored"], res)
        return kw

    def _lookup(self, **over):
        kw = dict(self.KEY)
        kw.update(over)
        return decompile_cache.lookup(kw["binary_sha256"], kw["rva"],
                                      kw["ghidra_version"], kw["program"],
                                      root=self.tmp)

    def test_same_key_hits(self):
        self._store()
        hit = self._lookup()
        self.assertTrue(hit["hit"], hit)
        self.assertEqual(hit["text"], _C_TEXT)

    def test_changed_binary_misses(self):
        self._store()
        self.assertFalse(self._lookup(binary_sha256="cd" * 32)["hit"])

    def test_changed_rva_misses(self):
        self._store()
        self.assertFalse(self._lookup(rva="0xa80980")["hit"])

    def test_changed_version_misses(self):
        self._store()
        self.assertFalse(self._lookup(ghidra_version="11.0")["hit"])

    def test_changed_program_misses(self):
        self._store()
        self.assertFalse(self._lookup(program="SporebinEP1.exe")["hit"])

    def test_provenance_retained(self):
        self._store()
        hit = self._lookup()
        meta = hit["meta"]
        self.assertEqual(meta["key"]["binary_sha256"], self.KEY["binary_sha256"])
        self.assertEqual(meta["key"]["rva"], "0xa806b0")
        self.assertEqual(meta["key"]["ghidra_version"], "12.1.2")
        self.assertEqual(meta["key"]["program"], "SporeApp.exe")

    def test_malformed_meta_fails_safe(self):
        kw = self._store()
        _c, meta_path = decompile_cache.entry_paths(
            kw["binary_sha256"], kw["rva"], kw["ghidra_version"],
            kw["program"], root=self.tmp)
        with open(meta_path, "w") as fh:
            fh.write("{not json!!!")
        hit = self._lookup()
        self.assertFalse(hit["hit"])
        self.assertEqual(hit["reason"], "no_entry")

    def test_non_dict_meta_fails_safe(self):
        kw = self._store()
        _c, meta_path = decompile_cache.entry_paths(
            kw["binary_sha256"], kw["rva"], kw["ghidra_version"],
            kw["program"], root=self.tmp)
        with open(meta_path, "w") as fh:
            json.dump([1, 2, 3], fh)
        self.assertFalse(self._lookup()["hit"])

    def test_missing_body_fails_safe(self):
        kw = self._store()
        c_path, _m = decompile_cache.entry_paths(
            kw["binary_sha256"], kw["rva"], kw["ghidra_version"],
            kw["program"], root=self.tmp)
        os.remove(c_path)
        hit = self._lookup()
        self.assertFalse(hit["hit"])
        self.assertEqual(hit["reason"], "missing_body")

    def test_stale_key_mismatch_fails_safe(self):
        kw = self._store()
        _c, meta_path = decompile_cache.entry_paths(
            kw["binary_sha256"], kw["rva"], kw["ghidra_version"],
            kw["program"], root=self.tmp)
        with open(meta_path) as fh:
            meta = json.load(fh)
        meta["key"]["ghidra_version"] = "tampered"
        with open(meta_path, "w") as fh:
            json.dump(meta, fh)
        hit = self._lookup()
        self.assertFalse(hit["hit"])
        self.assertEqual(hit["reason"], "stale_key")

    def test_layout_shape(self):
        res = decompile_cache.store(self.KEY["binary_sha256"],
                                    self.KEY["rva"],
                                    self.KEY["ghidra_version"],
                                    self.KEY["program"], _C_TEXT,
                                    root=self.tmp)
        rel = os.path.relpath(res["c_path"], self.tmp)
        self.assertTrue(rel.startswith("decompiled/"), rel)
        self.assertTrue(rel.endswith("0xa806b0.c"), rel)
        self.assertTrue(res["c_path"].split("decompiled/")[1].startswith(
            self.KEY["binary_sha256"][:12]))


# --------------------------------------------------------------------------- #
# RVA handling.
# --------------------------------------------------------------------------- #
class TestRvaHandling(GhidraTestBase):
    def test_rva_hex_gets_image_base(self):
        # Explicit rva forces +image_base even though 0xa806b0 exceeds
        # the base (real snapshot RVAs do; the VA heuristic can't apply).
        t = gt.resolve_target("0xa806b0", force_rva=True)
        self.assertEqual(t["va"], "0x00e806b0")
        self.assertEqual(t["rva"], "0xa806b0")

    def test_va_passthrough(self):
        t = gt.resolve_target("0x00e806b0")
        self.assertEqual(t["va"], "0x00e806b0")
        self.assertEqual(t["rva"], "0xa806b0")

    def test_big_value_without_flag_is_va(self):
        # Ambiguous values default to VA; callers meaning RVA use 'rva'.
        t = gt.resolve_target("0xa806b0")
        self.assertEqual(t["va"], "0x00a806b0")

    def test_bare_hex_is_rva(self):
        # "1234" parses as decimal 1234 < image_base -> RVA.
        t = gt.resolve_target("1234")
        self.assertEqual(t["va"], "0x004004d2")
        self.assertEqual(t["rva"], "0x4d2")

    def test_small_int_is_rva(self):
        t = gt.resolve_target(0x100)
        self.assertEqual(t["va_int"], 0x400100)
        self.assertEqual(t["rva_int"], 0x100)

    def test_name_passthrough(self):
        t = gt.resolve_target("FUN_00e806b0")
        self.assertEqual(t["name"], "FUN_00e806b0")
        self.assertIsNone(t["va"])

    def test_namespaced_name_passthrough(self):
        t = gt.resolve_target("App::cCellModeStrategy::Update")
        self.assertEqual(t["name"], "App::cCellModeStrategy::Update")

    def test_empty_is_error(self):
        self.assertIn("error", gt.resolve_target(""))
        self.assertIn("error", gt.resolve_target(None))

    def test_decompile_accepts_rva_param(self):
        res = gt.ghidra_decompile({"rva": "0xa806b0"})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["va"], "0x00e806b0")
        self.assertEqual(res["image_base"], "0x400000")

    def test_decompile_accepts_name_param(self):
        res = gt.ghidra_decompile({"name": "FUN_00e806b0"})
        self.assertEqual(res["status"], "ok", res)
        self.assertIn("va", res)


# --------------------------------------------------------------------------- #
# Decompile handler: cache hit/miss, force, offline.
# --------------------------------------------------------------------------- #
class TestDecompile(GhidraTestBase):
    def test_miss_then_hit_one_upstream_call(self):
        first = gt.ghidra_decompile({"function": "0x00e806b0"})
        self.assertEqual(first["status"], "ok", first)
        self.assertFalse(first["cached"])
        self.assertIn("decompiled", first)
        self.assertIn("evidence_note", first)
        self.assertIn("binary_sha256", first)
        self.assertIn("program", first)
        second = gt.ghidra_decompile({"function": "0x00e806b0"})
        self.assertEqual(second["status"], "ok", second)
        self.assertTrue(second["cached"])
        upstream = [c for c in self.fake.calls if c[0] == "decompile"]
        self.assertEqual(len(upstream), 1)

    def test_force_bypasses_cache(self):
        gt.ghidra_decompile({"function": "0x00e806b0"})
        res = gt.ghidra_decompile({"function": "0x00e806b0", "force": True})
        self.assertEqual(res["status"], "ok", res)
        self.assertFalse(res["cached"])
        upstream = [c for c in self.fake.calls if c[0] == "decompile"]
        self.assertEqual(len(upstream), 2)

    def test_offline_cold_is_structured_error(self):
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_decompile({"function": "0x00e12345"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "ghidra_offline")

    def test_offline_raising_client_never_raises(self):
        gt._CLIENT_FACTORY = RaisingClient
        res = gt.ghidra_decompile({"function": "0x00e12345"})
        self.assertEqual(res["status"], "error", res)
        self.assertIn(res["code"], ("ghidra_offline", "empty_decompile"))

    def test_offline_warm_cache_serves_provenance(self):
        gt.ghidra_decompile({"function": "0x00e806b0"})
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_decompile({"function": "0x00e806b0"})
        self.assertEqual(res["status"], "ok", res)
        self.assertTrue(res["cached"])
        self.assertIn("provenance", res)

    def test_missing_spec_is_invalid_params(self):
        res = gt.ghidra_decompile({})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")


class TestFunctionAndSearch(GhidraTestBase):
    def test_function_card_shape(self):
        res = gt.ghidra_function({"address": "0x00e806b0"})
        self.assertEqual(res["status"], "ok", res)
        for key in ("va", "rva", "name", "program", "binary_sha256",
                    "evidence_note"):
            self.assertIn(key, res, key)
        self.assertEqual(res["va"], "0x00e806b0")

    def test_function_memoized(self):
        gt.ghidra_function({"address": "0x00e806b0"})
        gt.ghidra_function({"address": "0x00e806b0"})
        by_addr = [c for c in self.fake.calls
                   if c[0] == "function_by_address"]
        self.assertEqual(len(by_addr), 1)

    def test_function_offline_uses_committed_snapshot(self):
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_function({"address": "0x00e80980"})
        self.assertEqual(res["status"], "ok", res)
        self.assertIn("committed", res.get("provenance", ""))

    def test_function_offline_unknown_is_ghidra_offline(self):
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_function({"address": "0x00123456"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "ghidra_offline")

    def test_search_shape(self):
        res = gt.ghidra_search({"pattern": "CellMode"})
        self.assertEqual(res["status"], "ok", res)
        self.assertIn("matches", res)
        self.assertIn("binary_sha256", res)

    def test_search_empty_pattern_rejected(self):
        res = gt.ghidra_search({"pattern": "  "})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")

    def test_search_offline_is_ghidra_offline(self):
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_search({"pattern": "CellMode"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "ghidra_offline")


# --------------------------------------------------------------------------- #
# vtable_lookup / dossier_read over committed data.
# --------------------------------------------------------------------------- #
class TestVtableLookup(GhidraTestBase):
    def test_by_address(self):
        res = gt.vtable_lookup({"address": "0x013fa8f0"})
        self.assertEqual(res["status"], "ok", res)
        self.assertGreaterEqual(res["count"], 1)
        self.assertEqual(res["matches"][0]["address"], "0x013fa8f0")

    def test_by_namespace(self):
        res = gt.vtable_lookup({"namespace": "UTFWin"})
        self.assertEqual(res["status"], "ok", res)
        self.assertGreater(res["count"], 0)

    def test_by_subsystem(self):
        res = gt.vtable_lookup({"subsystem": "UTFWin"})
        self.assertEqual(res["status"], "ok", res)
        self.assertGreater(res["count"], 0)

    def test_no_filter_rejected(self):
        res = gt.vtable_lookup({})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")

    def test_bad_address_rejected(self):
        res = gt.vtable_lookup({"address": "not-an-address!!!"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")


class TestDossierRead(GhidraTestBase):
    def test_read_topic(self):
        res = gt.dossier_read({"topic": "cell-movement"})
        self.assertEqual(res["status"], "ok", res)
        self.assertIn("dossier", res)

    def test_read_section(self):
        res = gt.dossier_read({"topic": "cell-movement",
                               "section": "functions"})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["section"], "functions")

    def test_missing_section_lists_sections(self):
        res = gt.dossier_read({"topic": "cell-movement",
                               "section": "nope"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "no_section")
        self.assertIn("available_sections", res)

    def test_missing_topic_lists_topics(self):
        res = gt.dossier_read({"topic": "no-such-topic"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "not_found")
        self.assertIn("cell-movement", res.get("available_topics", []))

    def test_traversal_rejected(self):
        for bad in ("../re/dossier", "/etc/passwd", "a/b", "..",
                    "x; rm -rf /", ""):
            res = gt.dossier_read({"topic": bad})
            self.assertEqual(res["status"], "error", bad)
            self.assertEqual(res["code"], "invalid_params", bad)


class TestDossierRegenerate(GhidraTestBase):
    def test_cell_movement_idempotent(self):
        first = gt.dossier_regenerate({"topic": "cell-movement"})
        self.assertEqual(first["status"], "ok", first)
        self.assertIn(first["outcome"], ("unchanged", "changed", "created"))
        js_path = os.path.join(ROOT, "docs", "analysis", "dossiers",
                               "cell-movement.json")
        md_path = os.path.join(ROOT, "docs", "analysis", "dossiers",
                               "cell-movement.md")
        with open(js_path, "rb") as fh:
            before_js = fh.read()
        with open(md_path, "rb") as fh:
            before_md = fh.read()
        second = gt.dossier_regenerate({"topic": "cell-movement"})
        self.assertEqual(second["status"], "ok", second)
        self.assertEqual(second["outcome"], "unchanged")
        with open(js_path, "rb") as fh:
            self.assertEqual(fh.read(), before_js)
        with open(md_path, "rb") as fh:
            self.assertEqual(fh.read(), before_md)

    def test_unknown_topic_blocked_not_stub(self):
        res = gt.dossier_regenerate({"topic": "no-such-topic-xyz"})
        self.assertEqual(res["status"], "error", res)
        self.assertEqual(res["code"], "blocked_no_snapshot")
        self.assertNotEqual(res.get("code"), "not_implemented")

    def test_traversal_rejected(self):
        res = gt.dossier_regenerate({"topic": "../../tmp/evil"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")


# --------------------------------------------------------------------------- #
# ghidra_snapshot_save: deterministic writer (+ justified blocked states).
# --------------------------------------------------------------------------- #
class TestSnapshotSave(GhidraTestBase):
    TOPIC = "test-scratch-topic"
    PATH = os.path.join(ROOT, "tools", "re", "data",
                        "ghidra_snapshot_%s.json" % TOPIC)

    def tearDown(self):
        super(TestSnapshotSave, self).tearDown()
        try:
            os.remove(self.PATH)
        except OSError:
            pass

    def test_created_then_unchanged(self):
        first = gt.ghidra_snapshot_save(
            {"topic": self.TOPIC, "functions": ["0x00e806b0"]})
        self.assertEqual(first["status"], "ok", first)
        self.assertEqual(first["outcome"], "created")
        with open(self.PATH, "rb") as fh:
            body = fh.read()
        second = gt.ghidra_snapshot_save(
            {"topic": self.TOPIC, "functions": ["0x00e806b0"]})
        self.assertEqual(second["status"], "ok", second)
        self.assertEqual(second["outcome"], "unchanged")
        with open(self.PATH, "rb") as fh:
            self.assertEqual(fh.read(), body)
        doc = json.loads(body.decode("utf-8"))
        self.assertEqual(doc["$schema"], "ghidra-function-snapshot-1")
        self.assertIn("binary_sha256", doc["meta"])

    def test_bad_topic_rejected(self):
        res = gt.ghidra_snapshot_save(
            {"topic": "../evil", "functions": ["0x00e806b0"]})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")
        self.assertFalse(os.path.exists(
            os.path.join(ROOT, "tools", "re", "data",
                         "ghidra_snapshot_.._evil.json")))

    def test_no_functions_blocked_with_reason(self):
        res = gt.ghidra_snapshot_save({"topic": "brand-new-topic-xyz"})
        self.assertEqual(res["status"], "error", res)
        self.assertEqual(res["code"], "blocked_no_functions")
        self.assertIn("ghidra_snapshot.py", res.get("message", ""))

    def test_offline_cold_blocked_not_stub(self):
        gt._CLIENT_FACTORY = OfflineClient
        res = gt.ghidra_snapshot_save(
            {"topic": "offline-cold-xyz",
             "functions": ["0x00123456"]})
        self.assertEqual(res["status"], "error", res)
        self.assertEqual(res["code"], "ghidra_offline")


# --------------------------------------------------------------------------- #
# Registry wiring + no-arbitrary-exec.
# --------------------------------------------------------------------------- #
class TestRegistryWiring(GhidraTestBase):
    REAL_TOOLS = ["ghidra_decompile", "ghidra_function", "ghidra_search",
                  "ghidra_snapshot_save", "vtable_lookup", "dossier_read",
                  "dossier_regenerate"]

    def test_names_unchanged(self):
        for name in self.REAL_TOOLS:
            self.assertIn(name, registry.tool_names())

    def test_no_silent_stubs(self):
        args = {
            "ghidra_decompile": {"function": "0x00e806b0"},
            "ghidra_function": {"address": "0x00e806b0"},
            "ghidra_search": {"pattern": "Cell"},
            "ghidra_snapshot_save": {"topic": "test-wiring-scratch",
                                     "functions": ["0x00e806b0"]},
            "vtable_lookup": {"namespace": "UTFWin"},
            "dossier_read": {"topic": "cell-movement"},
            "dossier_regenerate": {"topic": "cell-movement"},
        }
        scratch = os.path.join(
            ROOT, "tools", "re", "data",
            "ghidra_snapshot_test-wiring-scratch.json")
        try:
            for name in self.REAL_TOOLS:
                res = registry.dispatch(name, dict(args[name]))
                self.assertIsInstance(res, dict, name)
                self.assertNotEqual(res.get("status"), "not_implemented",
                                    name)
        finally:
            try:
                os.remove(scratch)
            except OSError:
                pass

    def test_unknown_tool_still_unknown(self):
        with self.assertRaises(registry.ToolUnknown):
            registry.dispatch("ghidra_nope", {})


class TestNoArbitraryExec(GhidraTestBase):
    def test_module_uses_no_shell(self):
        with open(os.path.join(ROOT, "tools", "mcp",
                               "ghidra_tools.py")) as fh:
            src = fh.read()
        for token in ("subprocess", "os.system", "popen", "os.exec",
                      "shell=True", "__import__", "eval(", "exec("):
            self.assertNotIn(token, src, token)
        with open(os.path.join(ROOT, "tools", "mcp",
                               "ghidra_client.py")) as fh:
            client_src = fh.read()
        for token in ("subprocess", "os.system", "popen", "os.exec",
                      "shell=True"):
            self.assertNotIn(token, client_src, token)

    def test_malicious_params_have_no_effect(self):
        before = set(glob.glob(os.path.join(ROOT, "docs", "analysis",
                                            "dossiers", "*")))
        evil = ["; rm -rf /", "$(whoami)", "`id`", "a|b", "x && y",
                "../../tmp/pwned", "/etc/passwd"]
        for payload in evil:
            gt.dossier_read({"topic": payload})
            gt.dossier_regenerate({"topic": payload})
            gt.ghidra_snapshot_save({"topic": payload,
                                     "functions": ["0x00e806b0"]})
            gt.ghidra_search({"pattern": payload})
            gt.ghidra_decompile({"function": payload})
        after = set(glob.glob(os.path.join(ROOT, "docs", "analysis",
                                           "dossiers", "*")))
        self.assertEqual(before, after)
        self.assertFalse(os.path.exists("/tmp/pwned"))
        self.assertFalse(os.path.exists(
            os.path.join(ROOT, "tmp", "pwned")))

    def test_out_dir_escape_refused(self):
        res = gt.dossier_regenerate({"topic": "cell-movement",
                                     "out_dir": "/tmp"})
        self.assertEqual(res["status"], "error")
        self.assertEqual(res["code"], "invalid_params")


if __name__ == "__main__":
    unittest.main()
