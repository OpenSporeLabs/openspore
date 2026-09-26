import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools.reconstruction_tooling import cli
from tools.reconstruction_tooling.context import build as build_context
from tools.reconstruction_tooling.evidence import DECOMPILATION_KEYS, collect
from tools.reconstruction_tooling.frontier import frontier
from tools.reconstruction_tooling.models import ROOT, canonical_json, normalize_va
from tools.reconstruction_tooling.swarm import swarm
from tools.reconstruction_tooling.validate import _function_spans, _source, _target_span, validate


class ToolingTest(unittest.TestCase):
    def test_normalize_va(self):
        self.assertEqual(normalize_va("0xe5b790"), "0x00e5b790")
        self.assertEqual(normalize_va("e5b790"), "0x00e5b790")
        with self.assertRaises(ValueError):
            normalize_va("not-a-va")

    def test_frontier_uses_claims_and_reasons(self):
        result = frontier()
        self.assertGreater(result["total"], 0)
        self.assertTrue(result["targets"])
        for target in result["targets"]:
            self.assertIn("score", target)
            self.assertIn("reasons", target)
            self.assertIn("claim", target)
            self.assertIn(target["disposition"], {"eligible", "deferred", "excluded"})

    def test_persisted_evidence_does_not_claim_live(self):
        pack = collect(va="0x00e5b790", live=False, write=False)
        self.assertEqual(pack["evidence_state"], "PERSISTED")
        self.assertFalse(pack["collector"]["live_requested"])
        self.assertIn("categories", pack)
        self.assertEqual(pack["target"]["va"], "0x00e5b790")
        self.assertTrue(all(item["mode"] != "live" for item in pack["provenance"]))
        self.assertEqual(pack["categories"]["runtime"]["evidence_state"], "MISSING")

    def test_missing_record_does_not_claim_global_conflicts(self):
        pack = collect(va="0x0000dead", live=False, write=False)
        self.assertEqual(pack["categories"]["contradictions"]["availability"], "unavailable")
        self.assertEqual(pack["conflicts"], [])

    def test_integrate_status_does_not_apply(self):
        with patch("tools.reconstruction_tooling.cli.integrate_apply", side_effect=AssertionError("unexpected apply")):
            output = io.StringIO()
            with contextlib.redirect_stdout(output):
                code = cli.main(["integrate", "status", "--json"])
        self.assertEqual(code, 0)
        self.assertTrue(json.loads(output.getvalue())["ok"])

    def test_context_is_deterministic(self):
        first_evidence = collect(va="0x00e5b790", live=False, write=False)
        second_evidence = collect(va="0x00e5b790", live=False, write=False)
        first = build_context(va="0x00e5b790", evidence=first_evidence, write=False)
        second = build_context(va="0x00e5b790", evidence=second_evidence, write=False)
        self.assertEqual(first["content_sha256"], second["content_sha256"])
        self.assertEqual(len(first["sections"]), 15)

    def test_target_span_parser_and_identity_guard(self):
        record = {"name": "FUN_0102d1b0", "va": "0x0102d1b0"}
        text = 'extern "C" void PKG_THISCALL pkg12_space_0102d1b0() {\n  return;\n}\n'
        self.assertTrue(_function_spans(text))
        self.assertIsNone(_target_span(text, record))
        record = {"name": "MovePlayerToMousePosition", "va": "0x00e5b790"}
        text = 'extern "C" void PKG_CDECL cell_move_player_to_mouse_position_00e5b790(float value) {\n  return;\n}\n'
        self.assertIsNotNone(_target_span(text, record))

    def test_validation_reports_all_required_categories(self):
        report = validate(va="0x00e5b790", write=False)
        self.assertIn(report["status"], {"PASS", "WARN", "FAIL", "UNKNOWN", "NOT_AVAILABLE"})
        for name in ("ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS", "CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS", "EVIDENCE COVERAGE"):
            self.assertIn(name, report["checks"])

    def test_swarm_is_dependency_aware(self):
        plan = swarm(limit=10)
        self.assertIn("targets", plan)
        for target in plan["targets"]:
            self.assertIn("dependencies", target)
            self.assertIn("claimable", target)
            self.assertIn("evidence_ready", target)
        self.assertLessEqual(len(plan["targets"]), 10)

    def test_unsupported_live_option_is_rejected(self):
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            code = cli.main(["frontier", "--live", "--json"])
        self.assertEqual(code, 2)
        self.assertEqual(json.loads(output.getvalue())["code"], "unsupported_option")

    def test_cli_json_is_one_document(self):
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            code = cli.main(["frontier", "--json", "--limit", "1"])
        self.assertEqual(code, 0)
        document = json.loads(output.getvalue())
        self.assertEqual(document["$schema"], "openspore-cli-result-1")
        self.assertTrue(document["ok"])

    def test_global_json_before_subcommand(self):
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            code = cli.main(["--json", "frontier", "--limit", "1"])
        self.assertEqual(code, 0)
        self.assertTrue(json.loads(output.getvalue())["ok"])


class SwarmQueueAddressabilityTest(unittest.TestCase):
    BACKWARD_COMPATIBLE_KEYS = ("va", "priority", "dependencies", "evidence_ready", "claimable", "reason_codes")
    QUEUE_KEYS = ("queue_va", "queue_id", "queue_row", "binary_sha256")

    def test_swarm_targets_are_queue_addressable(self):
        plan = swarm(limit=10)
        self.assertTrue(plan["targets"], "expected at least one claimable swarm target")
        for target in plan["targets"]:
            for key in self.QUEUE_KEYS:
                self.assertIn(key, target)
            self.assertRegex(target["queue_va"], r"^[0-9a-f]{8}$")
            self.assertEqual(target["queue_va"], target["va"][2:])
            self.assertIsInstance(target["queue_row"], bool)
            self.assertEqual(target["queue_id"] is None, not target["queue_row"])
            self.assertEqual(target["binary_sha256"], plan["binary_sha256"])

    def test_swarm_targets_keep_backward_compatible_keys(self):
        plan = swarm(limit=10)
        self.assertTrue(plan["targets"])
        for target in plan["targets"]:
            for key in self.BACKWARD_COMPATIBLE_KEYS:
                self.assertIn(key, target)

    def test_swarm_is_deterministic(self):
        self.assertEqual(canonical_json(swarm(limit=5)), canonical_json(swarm(limit=5)))

    def test_swarm_counts_are_consistent(self):
        plan = swarm(limit=10)
        addressable = sum(1 for target in plan["targets"] if target["queue_row"])
        missing = sum(1 for target in plan["targets"] if not target["queue_row"])
        self.assertEqual(plan["queue_addressable"], addressable)
        self.assertEqual(plan["queue_missing"], missing)
        self.assertEqual(plan["queue_addressable"] + plan["queue_missing"], len(plan["targets"]))


class ClaimAwareSourceResolutionTest(unittest.TestCase):
    def _real_staging_source(self):
        staging = ROOT / "reconstruction" / "staging"
        if not staging.is_dir():
            return None
        for path in sorted(staging.rglob("*.cpp")):
            return path.relative_to(ROOT).as_posix()
        return None

    def test_validator_resolves_staging_sources(self):
        real = self._real_staging_source()
        if real is not None:
            resolved = _source(ROOT, {"source": {"files": [real]}})
            self.assertIsNotNone(resolved, "expected %s to resolve" % real)
            self.assertEqual(resolved["role"], "staging")
            self.assertEqual(resolved["path"].resolve(), (ROOT / real).resolve())
            return
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target = root / "reconstruction" / "staging" / "pkg" / "unit.cpp"
            target.parent.mkdir(parents=True)
            target.write_text("// staging artifact\n", encoding="utf-8")
            resolved = _source(root, {"source": {"files": ["reconstruction/staging/pkg/unit.cpp"]}})
            self.assertIsNotNone(resolved)
            self.assertEqual(resolved["role"], "staging")
            self.assertEqual(resolved["path"].resolve(), target.resolve())

    def test_validator_prefers_canonical_over_staging(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            canonical = root / "src" / "reconstruction" / "pkg" / "unit.cpp"
            staging = root / "reconstruction" / "staging" / "pkg" / "unit.cpp"
            for path in (canonical, staging):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("// artifact\n", encoding="utf-8")
            record = {"source": {"file": "reconstruction/staging/pkg/unit.cpp", "files": ["src/reconstruction/pkg/unit.cpp"]}}
            resolved = _source(root, record)
            self.assertIsNotNone(resolved)
            self.assertEqual(resolved["role"], "canonical")
            self.assertEqual(resolved["path"].resolve(), canonical.resolve())

    def test_validator_still_rejects_unknown_directories(self):
        with tempfile.TemporaryDirectory() as directory:
            outer = Path(directory)
            root = outer / "root"
            (root / "build").mkdir(parents=True)
            (root / "build" / "foo.cpp").write_text("// build artifact\n", encoding="utf-8")
            (outer / "outside.cpp").write_text("// outside artifact\n", encoding="utf-8")
            rejected = (
                "build/foo.cpp",
                "/etc/passwd",
                "../outside.cpp",
                "reconstruction/staging/../outside.cpp",
                "src/../outside.cpp",
            )
            for value in rejected:
                with self.subTest(value=value):
                    self.assertIsNone(_source(root, {"source": {"file": value, "files": [value]}}))


class PersistedDecompilationTest(unittest.TestCase):
    def test_persisted_decompilation_is_populated(self):
        self.assertIn("decompiled_evidence", DECOMPILATION_KEYS)
        pack = collect(va="0x00e5b790", live=False, write=False)
        category = pack["categories"]["decompilation"]
        self.assertEqual(category["availability"], "available", "committed snapshots must expose decompilation text; keys=%r" % (DECOMPILATION_KEYS,))
        self.assertEqual(category["evidence_state"], "PERSISTED")
        self.assertEqual(category["evidence_level"], "INFERRED")
        self.assertIsNone(category["reason"])
        self.assertTrue(category["provenance"])
        self.assertTrue(str(category["value"]).strip())

    def test_evidence_pack_is_deterministic(self):
        first = collect(va="0x00e5b790", live=False, write=False)
        second = collect(va="0x00e5b790", live=False, write=False)
        self.assertEqual(first["content_sha256"], second["content_sha256"])
        self.assertEqual(canonical_json(first), canonical_json(second))


if __name__ == "__main__":
    unittest.main()
