"""Unit tests for the asset/runtime/validation MCP tools (Subagent 5).

Covers tools/mcp/safety.py, tools/mcp/asset_tools.py and
tools/mcp/runtime_tools.py plus their registry wiring.

Stdlib unittest only; temp dirs; no wine/SPORE/display required: the
no_spo path is forced by pointing OPENSPORE_ROOT at an empty temp dir,
missing externals are forced via monkeypatched precondition helpers or
dedicated env overrides, and gate tests never set OPENSPORE_MCP_TRUSTED
except in the explicitly trusted cases (restored afterwards).

Run from the repo root:
    python3 -m unittest tests.mcp.test_assets_runtime -v
"""
import fcntl
import hashlib
import json
import os
import shutil
import tempfile
import unittest

from tools.mcp import asset_tools
from tools.mcp import config
from tools.mcp import registry
from tools.mcp import runtime_tools
from tools.mcp import safety

ROOT = config.OPENSPORE_ROOT

_ENV_KEYS = ("OPENSPORE_MCP_TRUSTED", "OPENSPORE_MCP_LOCK",
             "OPENSPORE_MCP_BUILD_DIR", "OPENSPORE_MCP_CTEST",
             "OPENSPORE_MCP_STATUS_FILE", "OPENSPORE_MCP_FIXTURES",
             "OPENSPORE_MCP_SIM_TEST", "DISPLAY")


def _write_jsonl(path, events):
    with open(path, "w") as fh:
        for event in events:
            fh.write(json.dumps(event) + "\n")


def _sample_events():
    return [
        {"t": 1, "rel": 0, "tid": 7, "name": "entry"},
        {"t": 2, "rel": 500, "tid": 7, "name": "App::Init"},
        {"t": 3, "rel": 1500, "tid": 8, "name": "App::Init"},
        {"t": 4, "rel": 2500, "tid": 7, "name": "entry"},
    ]


class _EnvCase(unittest.TestCase):
    """Save/restore env + repo-root + monkeypatched helpers per test."""

    def setUp(self):
        self._env = {key: os.environ.get(key) for key in _ENV_KEYS}
        self._root = config.OPENSPORE_ROOT
        self._wine = runtime_tools._has_wine
        self._display = runtime_tools._has_display
        self.tmp = tempfile.mkdtemp(prefix="openspore-mcp-test-")
        self.addCleanup(shutil.rmtree, self.tmp, True)
        self.addCleanup(self._restore)

    def _restore(self):
        for key, value in self._env.items():
            if value is None:
                os.environ.pop(key, None)
            else:
                os.environ[key] = value
        config.OPENSPORE_ROOT = self._root
        runtime_tools._has_wine = self._wine
        runtime_tools._has_display = self._display

    def fake_root(self):
        """Point OPENSPORE_ROOT at an empty temp dir (forces no_spo)."""
        empty = os.path.join(self.tmp, "empty-root")
        os.makedirs(empty)
        config.OPENSPORE_ROOT = empty
        return empty

    def fake_spore(self, packages=()):
        """Temp root with SPORE/ holding (empty) .package files."""
        root = os.path.join(self.tmp, "fake-root")
        spo = os.path.join(root, "SPORE", "Data")
        os.makedirs(spo)
        for name in packages:
            with open(os.path.join(spo, name), "wb") as fh:
                fh.write(b"\x00" * 64)
        config.OPENSPORE_ROOT = root
        return root


# --------------------------------------------------------------------------- #
# asset_resolve / asset_scan: degrade + path constraint.
# --------------------------------------------------------------------------- #
class TestAssetDegrade(_EnvCase):
    def test_resolve_no_spo(self):
        self.fake_root()
        res = asset_tools.asset_resolve(
            {"package": "x.package",
             "record": "0x00c677c4:0x00000000:0x00000001"})
        self.assertEqual(res["code"], "no_spo")
        self.assertEqual(res["status"], "error")

    def test_scan_no_spo(self):
        self.fake_root()
        res = asset_tools.asset_scan({"package": "x.package"})
        self.assertEqual(res["code"], "no_spo")

    def test_scan_inventory_lists_fake_packages(self):
        self.fake_spore(["a.package", "b.package"])
        res = asset_tools.asset_scan({})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["mode"], "inventory")
        names = [entry["package"] for entry in res["packages"]]
        self.assertEqual(names, ["Data/a.package", "Data/b.package"])

    def test_traversal_rejected(self):
        self.fake_spore(["a.package"])
        # ".." escapes and absolute paths outside SPORE/ are refused.
        for payload in ("../../etc/passwd", "/etc/passwd",
                        "a/../../etc/passwd"):
            res = asset_tools.asset_scan({"package": payload})
            self.assertEqual(res["code"], "invalid_params", payload)
            res = asset_tools.asset_resolve(
                {"package": payload, "type": "0x00c677c4"})
            self.assertEqual(res["code"], "invalid_params", payload)
        # A backslash is not a separator on Linux: the name stays a
        # harmless relative filename inside SPORE/ (never an escape).
        res = asset_tools.asset_scan({"package": "..\\windows\\x"})
        self.assertIn(res["code"], ("invalid_params", "not_found"), res)
        if res["code"] == "not_found":
            root = os.path.realpath(
                os.path.join(self.tmp, "fake-root", "SPORE"))
            self.assertTrue(
                os.path.realpath(res["path"]).startswith(root + os.sep)
                or os.path.realpath(res["path"]) == root, res)

    def test_missing_package_is_not_found_not_crash(self):
        self.fake_spore()
        res = asset_tools.asset_scan({"package": "nope.package"})
        self.assertEqual(res["code"], "not_found")
        res = asset_tools.asset_resolve(
            {"package": "nope.package", "type": "0x00c677c4"})
        self.assertEqual(res["code"], "not_found")

    def test_record_shape_validated(self):
        self.fake_spore(["a.package"])
        res = asset_tools.asset_resolve(
            {"package": "Data/a.package", "record": "not-a-record"})
        self.assertEqual(res["code"], "invalid_params")
        res = asset_tools.asset_resolve({"package": "Data/a.package"})
        self.assertEqual(res["code"], "invalid_params")


# --------------------------------------------------------------------------- #
# trace_analyze: determinism + read-only.
# --------------------------------------------------------------------------- #
class TestTraceAnalyze(_EnvCase):
    def test_deterministic_over_jsonl(self):
        path = os.path.join(self.tmp, "obs_demo.jsonl")
        _write_jsonl(path, _sample_events())
        first = runtime_tools.trace_analyze({"path": path})
        second = runtime_tools.trace_analyze({"path": path})
        self.assertEqual(first["status"], "ok", first)
        self.assertEqual(first, second)
        self.assertEqual(first["summary"]["events"], 4)
        self.assertEqual(
            sorted(first["summary"]["functions"].keys()),
            ["App::Init", "entry"])
        self.assertEqual(first["summary"]["functions"]["entry"]["count"], 2)
        self.assertEqual(first["kind"], "runtime-observation-summary")
        self.assertIn("differential_note", first)
        expect = hashlib.sha256(open(path, "rb").read()).hexdigest()
        self.assertEqual(first["sha256"], expect)

    def test_missing_file_blocked_not_crash(self):
        res = runtime_tools.trace_analyze(
            {"path": os.path.join(self.tmp, "nope.jsonl")})
        self.assertEqual(res["status"], "error", res)
        self.assertEqual(res["code"], "blocked_unreadable")

    def test_run_id_resolves_committed_example(self):
        # out/obs_main_menu.jsonl is the committed 0-byte negative: it
        # resolves, analyzes, and preserves the negative (0 events).
        res = runtime_tools.trace_analyze({"run_id": "main_menu"})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["summary"]["events"], 0)
        # The committed example with real events, addressed by path.
        example = os.path.join(
            ROOT, "tools", "observatory", "examples",
            "obs_main_menu_example.jsonl")
        res = runtime_tools.trace_analyze({"path": example})
        self.assertEqual(res["status"], "ok", res)
        self.assertGreater(res["summary"]["events"], 0)

    def test_non_json_file_is_zero_events_not_crash(self):
        path = os.path.join(self.tmp, "plain.txt")
        with open(path, "w") as fh:
            fh.write("not json\nstill not json\n")
        res = runtime_tools.trace_analyze({"path": path})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["summary"]["events"], 0)

    def test_unknown_run_id_blocked(self):
        res = runtime_tools.trace_analyze({"run_id": "no-such-run-xyz"})
        self.assertEqual(res["code"], "blocked_unreadable")


# --------------------------------------------------------------------------- #
# trace_status: listing over temp dirs.
# --------------------------------------------------------------------------- #
class TestTraceStatus(_EnvCase):
    def test_listing(self):
        out_dir = os.path.join(self.tmp, "out")
        ex_dir = os.path.join(self.tmp, "examples")
        os.makedirs(out_dir)
        os.makedirs(ex_dir)
        _write_jsonl(os.path.join(out_dir, "obs_b.jsonl"),
                     _sample_events()[:2])
        _write_jsonl(os.path.join(out_dir, "obs_a.jsonl"),
                     _sample_events())
        with open(os.path.join(out_dir, "run.manifest.json"), "w") as fh:
            json.dump({"run": "a"}, fh)
        res = runtime_tools.trace_status(
            {"out_dir": out_dir, "examples_dir": ex_dir})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["run_count"], 2)
        self.assertEqual([r["run"] for r in res["runs"]],
                         ["obs_a.jsonl", "obs_b.jsonl"])
        self.assertEqual(len(res["manifests"]), 1)
        by_run = {r["run"]: r for r in res["runs"]}
        self.assertEqual(by_run["obs_a.jsonl"]["lines"], 4)
        self.assertIn("entry", by_run["obs_a.jsonl"]["probes_fired"])

    def test_missing_dirs_empty_not_crash(self):
        res = runtime_tools.trace_status(
            {"out_dir": os.path.join(self.tmp, "no-out"),
             "examples_dir": os.path.join(self.tmp, "no-ex")})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["run_count"], 0)


# --------------------------------------------------------------------------- #
# Gates: approval_required without approve / without trust.
# --------------------------------------------------------------------------- #
class TestGates(_EnvCase):
    def test_trace_run_needs_approval(self):
        res = runtime_tools.trace_run({"scenario": "main_menu"})
        self.assertEqual(res.get("code"), "approval_required", res)

    def test_trace_run_approve_without_trust_refused(self):
        res = runtime_tools.trace_run(
            {"scenario": "main_menu", "approve": True})
        self.assertEqual(res.get("code"), "approval_required", res)

    def test_status_update_needs_approval(self):
        res = runtime_tools.status_update(
            {"subsystem": "x", "status": "supported"})
        self.assertEqual(res.get("code"), "approval_required", res)

    def test_fixture_rebuild_needs_approval(self):
        res = runtime_tools.fixture_check({"rebuild": True})
        self.assertEqual(res.get("code"), "approval_required", res)
        res = runtime_tools.fixture_check(
            {"rebuild": True, "approve": True})
        self.assertEqual(res.get("code"), "approval_required", res)

    def test_fixture_identity_never_gated(self):
        res = runtime_tools.fixture_check(
            {"fixtures_path": os.path.join(self.tmp, "nope.json")})
        self.assertEqual(res["code"], "not_found", res)
        self.assertNotEqual(res.get("code"), "approval_required")

    def test_safety_shape(self):
        err = safety.approval_check("trace_run", {})
        self.assertEqual(err["code"], "approval_required")
        self.assertEqual(err["status"], "error")
        self.assertIn("requires", err)
        # Identity-mode fixture_check is never gated; rebuild always is.
        self.assertFalse(safety.needs_approval("fixture_check", {}))
        self.assertTrue(
            safety.needs_approval("fixture_check", {"rebuild": True}))
        self.assertTrue(safety.needs_approval("trace_run", {}))
        self.assertFalse(safety.needs_approval("trace_analyze", {}))
        os.environ["OPENSPORE_MCP_TRUSTED"] = "1"
        self.assertIsNone(
            safety.approval_check("trace_run", {"approve": True}))
        self.assertIsNotNone(
            safety.approval_check("trace_run", {"approve": False}))
        self.assertIsNotNone(
            safety.approval_check("trace_run", {}))


# --------------------------------------------------------------------------- #
# status_update: vocab + evidence cap (trusted, temp status file).
# --------------------------------------------------------------------------- #
class TestStatusUpdate(_EnvCase):
    def _temp_status(self):
        src = os.path.join(ROOT, "docs", "replacement-status.json")
        with open(src) as fh:
            doc = json.load(fh)
        dst = os.path.join(self.tmp, "replacement-status.json")
        with open(dst, "w") as fh:
            json.dump(doc, fh, indent=2)
            fh.write("\n")
        os.environ["OPENSPORE_MCP_STATUS_FILE"] = dst
        os.environ["OPENSPORE_MCP_TRUSTED"] = "1"
        return dst

    def _update(self, **params):
        merged = {"approve": True}
        merged.update(params)
        return runtime_tools.status_update(merged)

    def test_vocab_enforced(self):
        self._temp_status()
        res = self._update(subsystem="simulator-gameplay",
                           status="super-verified")
        self.assertEqual(res["code"], "invalid_status", res)

    def test_unknown_subsystem(self):
        self._temp_status()
        res = self._update(subsystem="no-such-subsystem",
                           status="supported")
        self.assertEqual(res["code"], "not_found", res)

    def test_verified_without_manifest_capped(self):
        self._temp_status()
        res = self._update(subsystem="simulator-gameplay",
                           status="replaced-verified",
                           evidence=["docs/SOME-DOC.md"])
        self.assertEqual(res["code"], "evidence_cap", res)

    def test_decomp_evidence_capped(self):
        self._temp_status()
        res = self._update(
            subsystem="simulator-gameplay",
            status="replaced-verified",
            evidence=["tools/re/data/decompiled/MovePlayerToMousePosition.c",
                      "tools/observatory/out/obs_main_menu.jsonl"])
        self.assertEqual(res["code"], "evidence_cap", res)

    def test_replaced_needs_evidence(self):
        self._temp_status()
        res = self._update(subsystem="simulator-gameplay",
                           status="replaced-stub", evidence=[])
        self.assertEqual(res["code"], "evidence_required", res)

    def test_valid_update_writes(self):
        dst = self._temp_status()
        res = self._update(subsystem="simulator-gameplay",
                           status="supported",
                           evidence=["tests/mcp/test_assets_runtime.py"])
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["previous"], "hypothesis")
        self.assertEqual(res["updated"], "supported")
        with open(dst) as fh:
            doc = json.load(fh)
        entry = [s for s in doc["subsystems"]
                 if s["name"] == "simulator-gameplay"][0]
        self.assertEqual(entry["status"], "supported")
        self.assertIn("tests/mcp/test_assets_runtime.py",
                      entry["evidence"])

    def test_verified_with_live_manifest_allowed(self):
        self._temp_status()
        res = self._update(
            subsystem="simulator-gameplay",
            status="replaced-verified",
            evidence=["tools/observatory/examples/"
                      "obs_main_menu_example.jsonl"])
        self.assertEqual(res["status"], "ok", res)


# --------------------------------------------------------------------------- #
# fixture_check: identity mode + rebuild gating.
# --------------------------------------------------------------------------- #
class TestFixtureCheck(_EnvCase):
    def _fixtures(self, doc):
        path = os.path.join(self.tmp, "fixtures.json")
        with open(path, "w") as fh:
            json.dump(doc, fh)
        return path

    def _valid_doc(self):
        return {"contract": "cell-sim-contract/1",
                "scenarios": [{"name": "a"}, {"name": "b"}]}

    def test_identity_ok(self):
        path = self._fixtures(self._valid_doc())
        res = runtime_tools.fixture_check({"fixtures_path": path})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["mode"], "identity")
        self.assertEqual(res["scenarios"], 2)
        self.assertEqual(res["contract"], "cell-sim-contract/1")
        with open(path, "rb") as fh:
            expect = hashlib.sha256(fh.read()).hexdigest()
        self.assertEqual(res["sha256"], expect)

    def test_identity_corrupt(self):
        path = os.path.join(self.tmp, "bad.json")
        with open(path, "w") as fh:
            fh.write("{not json")
        res = runtime_tools.fixture_check({"fixtures_path": path})
        self.assertEqual(res["code"], "corrupt_fixtures", res)

    def test_identity_bad_shape(self):
        path = self._fixtures({"contract": "x", "scenarios": []})
        res = runtime_tools.fixture_check({"fixtures_path": path})
        self.assertEqual(res["code"], "corrupt_fixtures", res)

    def test_rebuild_blocked_without_emitter(self):
        os.environ["OPENSPORE_MCP_TRUSTED"] = "1"
        os.environ["OPENSPORE_MCP_SIM_TEST"] = os.path.join(
            self.tmp, "no-emitter")
        res = runtime_tools.fixture_check(
            {"rebuild": True, "approve": True,
             "fixtures_path": os.path.join(self.tmp, "out.json")})
        self.assertEqual(res["code"], "blocked_no_emitter", res)
        self.assertFalse(
            os.path.exists(os.path.join(self.tmp, "out.json")))


# --------------------------------------------------------------------------- #
# Blocked (not crash) when externals are missing.
# --------------------------------------------------------------------------- #
class TestBlocked(_EnvCase):
    def _trusted(self):
        os.environ["OPENSPORE_MCP_TRUSTED"] = "1"

    def test_trace_run_unknown_scenario_blocked(self):
        self._trusted()
        res = runtime_tools.trace_run(
            {"scenario": "no-such-scenario-xyz", "approve": True})
        self.assertEqual(res["code"], "blocked_no_probe", res)
        self.assertTrue(res.get("blocked"))

    def test_trace_run_no_wine_blocked(self):
        self._trusted()
        runtime_tools._has_wine = lambda: False
        res = runtime_tools.trace_run(
            {"scenario": "main_menu", "approve": True})
        self.assertEqual(res["code"], "blocked_no_wine", res)

    def test_trace_run_no_display_blocked(self):
        self._trusted()
        runtime_tools._has_wine = lambda: True
        runtime_tools._has_display = lambda: False
        res = runtime_tools.trace_run(
            {"scenario": "main_menu", "approve": True})
        self.assertEqual(res["code"], "blocked_no_display", res)

    def _hold_lock(self):
        path = os.path.join(self.tmp, "machine.lock")
        with open(path, "w") as fh:
            fh.write("")
        fh = open(path, "w")
        fcntl.flock(fh.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
        self.addCleanup(fh.close)
        os.environ["OPENSPORE_MCP_LOCK"] = path

    def test_test_run_machine_locked(self):
        self._hold_lock()
        res = runtime_tools.test_run({"selector": "all"})
        self.assertEqual(res["code"], "machine_locked", res)

    def test_trace_run_machine_locked(self):
        self._trusted()
        self._hold_lock()
        runtime_tools._has_wine = lambda: True
        runtime_tools._has_display = lambda: True
        res = runtime_tools.trace_run(
            {"scenario": "main_menu", "approve": True})
        self.assertEqual(res["code"], "machine_locked", res)

    def test_test_run_no_build_blocked(self):
        os.environ["OPENSPORE_MCP_BUILD_DIR"] = os.path.join(
            self.tmp, "no-build-dir")
        res = runtime_tools.test_run({"selector": "all"})
        self.assertEqual(res["code"], "blocked_no_build", res)

    def test_test_run_fake_ctest(self):
        if not os.path.exists("/bin/true") or \
                not os.path.exists("/bin/false"):
            self.skipTest("needs /bin/true + /bin/false")
        build = os.path.join(self.tmp, "build")
        os.makedirs(build)
        os.environ["OPENSPORE_MCP_BUILD_DIR"] = build
        os.environ["OPENSPORE_MCP_CTEST"] = "/bin/true"
        res = runtime_tools.test_run({"selector": "all"})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["outcome"], "passed")
        os.environ["OPENSPORE_MCP_CTEST"] = "/bin/false"
        res = runtime_tools.test_run({"selector": "some_test"})
        self.assertEqual(res["status"], "ok", res)
        self.assertEqual(res["outcome"], "failed")


# --------------------------------------------------------------------------- #
# Registry wiring: exact names, no silent stubs.
# --------------------------------------------------------------------------- #
class TestWiring(unittest.TestCase):
    REAL = {
        "asset_resolve": asset_tools.asset_resolve,
        "asset_scan": asset_tools.asset_scan,
        "trace_run": runtime_tools.trace_run,
        "trace_analyze": runtime_tools.trace_analyze,
        "trace_status": runtime_tools.trace_status,
        "test_run": runtime_tools.test_run,
        "status_update": runtime_tools.status_update,
        "fixture_check": runtime_tools.fixture_check,
    }

    def test_names_unchanged(self):
        self.assertEqual(len(registry.tool_names()), 24)
        for name in self.REAL:
            self.assertIn(name, registry.tool_names())

    def test_handlers_are_real(self):
        for name, func in self.REAL.items():
            self.assertIs(registry.HANDLERS[name], func, name)

    def test_no_silent_stubs(self):
        for name in self.REAL:
            if name == "test_run":
                continue  # exercises ctest: covered separately below.
            res = registry.dispatch(name, {})
            self.assertIsInstance(res, dict, name)
            self.assertNotEqual(res.get("status"), "not_implemented",
                                name)

    def test_test_run_wired_without_running_suite(self):
        old = os.environ.get("OPENSPORE_MCP_BUILD_DIR")
        try:
            os.environ["OPENSPORE_MCP_BUILD_DIR"] = os.path.join(
                tempfile.gettempdir(), "openspore-no-such-build-xyz")
            res = registry.dispatch("test_run", {})
        finally:
            if old is None:
                os.environ.pop("OPENSPORE_MCP_BUILD_DIR", None)
            else:
                os.environ["OPENSPORE_MCP_BUILD_DIR"] = old
        self.assertIsInstance(res, dict)
        self.assertNotEqual(res.get("status"), "not_implemented")
        self.assertEqual(res.get("code"), "blocked_no_build")

    def test_new_modules_use_no_shell(self):
        for mod in ("safety.py", "asset_tools.py", "runtime_tools.py"):
            with open(os.path.join(ROOT, "tools", "mcp", mod)) as fh:
                src = fh.read()
            for token in ("shell=True", "os.system", "os.popen",
                          "os.exec", "__import__", "eval(", "exec("):
                self.assertNotIn(token, src, "%s in %s" % (token, mod))

    def test_malicious_params_have_no_effect(self):
        before = set(os.listdir(self.tmpdir_root()))
        evil = ["; rm -rf /", "$(whoami)", "`id`", "a|b", "x && y",
                "../../tmp/pwned", "/etc/passwd"]
        for payload in evil:
            asset_tools.asset_scan({"package": payload})
            asset_tools.asset_resolve(
                {"package": payload, "type": "0x00c677c4"})
            runtime_tools.trace_run({"scenario": payload})
            runtime_tools.trace_analyze(
                {"path": os.path.join(tempfile.gettempdir(),
                                      "openspore-evil", payload)})
            runtime_tools.status_update({"subsystem": payload,
                                         "status": payload})
        after = set(os.listdir(self.tmpdir_root()))
        self.assertEqual(before, after)
        self.assertFalse(os.path.exists("/tmp/pwned"))

    def tmpdir_root(self):
        return tempfile.gettempdir()


if __name__ == "__main__":
    unittest.main()
