import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools.reconstruction_tooling import cli
from tools.reconstruction_tooling.context import build as build_context
from tools.reconstruction_tooling.evidence import (
    ABI_INFER_REL,
    DECOMPILATION_KEYS,
    INDEX_REL,
    collect,
    render_evidence_markdown,
)
from tools.reconstruction_tooling.frontier import frontier
from tools.reconstruction_tooling.models import ROOT, canonical_json, normalize_va, sha256_json
from tools.reconstruction_tooling.swarm import swarm
from tools.reconstruction_tooling.validate import _function_spans, _pack_digest, _source, _target_span, validate


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

    # The binder itself, exhaustively, is covered in
    # ``tests/test_validation_span_binding.py`` (both the shipped binder and the
    # pre-fix binder run over the same fixture there and the two reports are
    # required equal). These cases are not duplicated here; what follows is the
    # parser plus the identity contract, stated at the level of the individual
    # mistakes a span can be wrong about.
    def test_target_span_parser_and_identity_guard(self):
        # A bare Ghidra placeholder name carries no descriptive words at all --
        # only an address -- so the VA token is the whole binder. The worker
        # briefing contract is that the reconstructed symbol must embed the
        # 8-hex target VA so the validator can locate the span, and for a
        # placeholder that token is the only part of the contract left to bind
        # with. The pre-fix rule additionally demanded the literal word ``fun``
        # in the span, which rejected exactly the symbols a worker is told to
        # write, so this case used to bind nothing at all.
        placeholder = {"name": "FUN_0102d1b0", "va": "0x0102d1b0"}
        text = 'extern "C" void PKG_THISCALL pkg12_space_0102d1b0() {\n  return;\n}\n'
        self.assertTrue(_function_spans(text))
        span = _target_span(text, placeholder)
        self.assertIsNotNone(span, "the VA token is the documented binder and it is present")
        self.assertEqual(span["name"], "pkg12_space_0102d1b0")

        # The identity guards the loosened rule now has to carry itself, since
        # the VA token is the only thing distinguishing a placeholder's span.
        # A symbol without the token: nothing binds, and in particular the
        # binder does not fall back to "the first function in the file".
        self.assertIsNone(_target_span(
            'extern "C" void PKG_THISCALL something_else() {\n  return;\n}\n',
            placeholder))
        # No function span at all. The token is present in the text, but only in
        # a prototype, and a declaration is not a body the checks can read.
        self.assertIsNone(_target_span(
            'extern "C" void PKG_THISCALL pkg12_space_0102d1b0();\n', placeholder))
        # The cross-VA guard, and the one that matters most now: the neighbour
        # shares this target's whole descriptive name, so the token is the only
        # thing that can tell the two spans apart.
        self.assertIsNone(_target_span(
            'extern "C" void PKG_THISCALL pkg12_space_0102d1b1() {\n  return;\n}\n',
            placeholder))

        # A real, non-placeholder name still takes the strict word-narrowed path:
        # the token alone is not enough for it, every name word must appear.
        real = {"name": "App::PropertyList::RemoveProperty", "va": "0x006a2ef0"}
        span = _target_span(
            'extern "C" void PKG_THISCALL property_list_remove_property_006a2ef0() {\n  return;\n}\n',
            real)
        self.assertIsNotNone(span)
        self.assertEqual(span["name"], "property_list_remove_property_006a2ef0")
        # Embeds the VA, but names no part of the function it claims to be.
        self.assertIsNone(_target_span(
            'extern "C" void PKG_THISCALL sim_006a2ef0_flush() {\n  return;\n}\n',
            real))

        # A descriptive name with no ``::`` narrows the same way it always did.
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


class DerivedAbiCategoryTest(unittest.TestCase):
    """The ``abi_derived`` category: the machine envelope, published additively.

    ``categories["abi"]`` is the ABI *category* and its persisted projection is
    load-bearing -- the committed packs must stay bit-identical -- so the derived
    envelope gets a second key instead of overwriting the first. These tests pin
    both halves of that arrangement: ``abi`` unchanged in both directions, and
    ``abi_derived`` available whenever ``_derived_abi`` produced a record.

    ``_derived_abi`` itself is patched rather than driven through Ghidra: the
    contract under test is what ``collect`` does with the envelope the engine
    hands back, and a patch makes that contract deterministic while
    ``abi_infer`` is still being developed in parallel. The one test that does
    not patch it (the unavailable case) runs the real helper.
    """

    TARGET = "0x006a2a80"
    # The persisted projection. Deliberately the shape a committed record has:
    # the ABI claims, and none of the machine-derived sub-records.
    PERSISTED_ABI = {
        "architecture": "x86-32",
        "calling_convention": "thiscall",
        "hidden_this_register": "ecx",
        "ordinary_stack_arguments": 2,
        "ret_form": "ret 8",
        "return_register": "eax",
        "return_type": "void",
        "stack_cleanup_bytes": 8,
    }
    # The machine envelope. ``parse``, ``dispatch`` and ``receiver`` are the three
    # sub-records the validator's CONSTANTS, VIRTUAL DISPATCH and FIELDS/OFFSETS
    # dimensions read, and no other category carries them.
    DERIVED_ENVELOPE = {
        "schema": "openspore-abi-inference-1",
        "verdict": "partial",
        "completeness": "partial",
        "abi": {"architecture": "x86-32", "calling_convention": "thiscall"},
        "parse": {"declared_count": 3, "degraded": True, "unparsed": 0},
        "dispatch": {"indirect_calls": 2},
        "receiver": {"register": "ecx", "offsets": [4, 8]},
        "observations": [{"id": "obs-1", "kind": "this_register", "at": "0x006a2a80", "index": 0}],
    }
    DERIVED_OBSERVATIONS = ["GhidraMCP /get_function_by_address", "GhidraMCP /disassemble_function"]
    # Every key ``collect`` publishes, so the census is a contract and not a
    # count. ``abi_derived`` is in it: a key that appears only when a derivation
    # happens would make every consumer's key set depend on the machine.
    CATEGORY_KEYS = (
        "abi", "abi_derived", "callees_dependencies", "callers_dependencies",
        "contradictions", "decompilation", "disassembly", "external_callees",
        "function_identity", "ghidra_function", "globals", "reconstruction",
        "runtime", "runtime_metadata", "semantic_hypotheses", "status", "types",
        "vtables",
    )

    def _index(self, abi_marker):
        record = {"va": self.TARGET, "name": "FUN_006a2a80", "status": "unreconstructed"}
        if abi_marker is not None:
            record["abi"] = abi_marker
        return {
            "binary": {"image_base": "0x00400000"},
            "records": {self.TARGET: record},
            "contradictions": [],
            "_tooling_projection": {"rebuilt": False, "source": INDEX_REL},
        }

    def _live_function(self, va):
        return {
            "status": "ok", "mode": "live",
            "provenance": "GhidraMCP /get_function_by_address + /analyze_function_complete",
            "data": {
                "va": va, "name": "FUN_006a2a80",
                # Convention-free on purpose: a Ghidra signature almost never
                # names a convention, and a synthetic one that did would
                # manufacture a live_vs_persisted conflict out of the fixture.
                "signature": "void FUN_006a2a80(int value)",
                "ghidra_calling_convention": "__thiscall", "parameter_count": 1,
                "decompiled": "void FUN_006a2a80(int value) { }",
            },
        }

    def _live_decompile(self, va):
        return {"status": "ok", "mode": "live", "provenance": "GhidraMCP /decompile_function",
                "text": "void FUN_006a2a80(int value) { }"}

    def _live_disassembly(self, va):
        listing = {"instructions": [{"address": va, "text": "push ebp"}], "count": 1}
        return {"status": "ok", "mode": "live", "provenance": "GhidraMCP /disassemble_function",
                "data": listing, "listing": listing}

    def _collect_live(self, abi_marker, out_dir=None, write=False):
        """A live pack over a synthetic index, with the derivation patched in."""
        derived = {"value": self.DERIVED_ENVELOPE, "observations": list(self.DERIVED_OBSERVATIONS)}
        with patch("tools.reconstruction_tooling.evidence._index", return_value=self._index(abi_marker)), \
             patch("tools.reconstruction_tooling.evidence._live_function", side_effect=self._live_function), \
             patch("tools.reconstruction_tooling.evidence._live_decompile", side_effect=self._live_decompile), \
             patch("tools.reconstruction_tooling.evidence._live_disassembly", side_effect=self._live_disassembly), \
             patch("tools.reconstruction_tooling.evidence._derived_abi", return_value=derived):
            return collect(va=self.TARGET, live=True, write=write, out_dir=out_dir)

    def test_persisted_abi_is_untouched_and_derived_is_published(self):
        pack = self._collect_live(self.PERSISTED_ABI)
        abi = pack["categories"]["abi"]
        # Byte-identical to the persisted projection: the very dict handed in, and
        # not the derived envelope. The category label is the persisted one, which
        # is what proves the derived branch did not run.
        self.assertEqual(abi["value"], self.PERSISTED_ABI)
        self.assertEqual(abi["evidence_state"], "PERSISTED")
        self.assertEqual(abi["provenance"], [INDEX_REL])
        for key in ("parse", "dispatch", "receiver"):
            self.assertNotIn(key, abi["value"], "the persisted projection must not gain derived sub-records")
        derived = pack["categories"]["abi_derived"]
        self.assertEqual(derived["availability"], "available")
        # The same envelope, byte for byte.
        self.assertEqual(canonical_json(derived["value"]), canonical_json(self.DERIVED_ENVELOPE))
        for key in ("parse", "dispatch", "receiver"):
            self.assertIn(key, derived["value"], "the derived record must carry %s" % key)
        self.assertEqual(derived["value"]["parse"]["declared_count"], 3)
        self.assertEqual(derived["value"]["dispatch"]["indirect_calls"], 2)
        self.assertEqual(derived["value"]["receiver"]["register"], "ecx")

    def test_absent_persisted_abi_still_fills_abi_and_also_publishes_derived(self):
        pack = self._collect_live(None)
        categories = pack["categories"]
        # The old behaviour, untouched: with no persisted ABI, ``abi`` is the
        # derived envelope and the derived branch runs.
        self.assertEqual(categories["abi"]["availability"], "available")
        self.assertEqual(canonical_json(categories["abi"]["value"]), canonical_json(self.DERIVED_ENVELOPE))
        self.assertEqual(categories["abi"]["evidence_state"], "DERIVED")
        # And the new category holds the same value, so the two agree whenever both
        # are filled rather than being two independent derivations.
        self.assertEqual(categories["abi_derived"]["availability"], "available")
        self.assertEqual(canonical_json(categories["abi_derived"]["value"]), canonical_json(categories["abi"]["value"]))
        self.assertEqual(categories["abi_derived"]["evidence_state"], categories["abi"]["evidence_state"])
        self.assertEqual(categories["abi_derived"]["provenance"], categories["abi"]["provenance"])

    def test_derived_category_uses_the_same_category_arguments(self):
        pack = self._collect_live(self.PERSISTED_ABI)
        derived = pack["categories"]["abi_derived"]
        # ``"derived"`` is the ``source_class`` argument -- the one the existing
        # derived-fills-abi branch passes -- and ``_category`` upper-cases it into
        # ``evidence_state``. Asserting the argument's effect, not the literal the
        # helper stores, is what keeps the two branches provably in step.
        self.assertEqual(derived["evidence_state"], "DERIVED")
        self.assertEqual(derived["evidence_level"], "INFERRED")
        self.assertNotIn(derived["evidence_state"], {"PERSISTED", "LIVE", "MISSING"})
        self.assertEqual(derived["provenance"], [INDEX_REL] + self.DERIVED_OBSERVATIONS)
        self.assertIsNone(derived["reason"])
        self.assertEqual(sorted(derived), ["availability", "evidence_level", "evidence_state", "provenance", "reason", "value"])

    def test_engine_provenance_is_cited_even_when_the_persisted_abi_won(self):
        # The pack-level provenance already cited the engine; the new category is
        # additive and must not have disturbed that list.
        pack = self._collect_live(self.PERSISTED_ABI)
        self.assertIn(ABI_INFER_REL, [item.get("ref") for item in pack["provenance"]])

    def test_absent_derivation_leaves_the_category_present_and_unavailable(self):
        # The real ``_derived_abi``, offline: there is no live listing, so the
        # engine is never reached and the category must still exist.
        pack = collect(va="0x00e5b790", live=False, write=False)
        derived = pack["categories"]["abi_derived"]
        self.assertEqual(derived["availability"], "unavailable")
        self.assertEqual(derived["evidence_state"], "MISSING")
        self.assertEqual(derived["evidence_level"], "UNKNOWN")
        self.assertIsNone(derived["value"])
        self.assertEqual(derived["provenance"], [])
        self.assertIsInstance(derived["reason"], str)
        self.assertTrue(derived["reason"].strip())

    def test_category_key_set_is_stable_with_and_without_a_derivation(self):
        offline = collect(va="0x00e5b790", live=False, write=False)
        derived = self._collect_live(self.PERSISTED_ABI)
        self.assertEqual(sorted(offline["categories"]), sorted(self.CATEGORY_KEYS))
        self.assertEqual(sorted(derived["categories"]), sorted(self.CATEGORY_KEYS))
        self.assertIn("abi_derived", derived["categories"])

    def test_markdown_renderer_emits_a_section_for_the_new_category(self):
        pack = self._collect_live(self.PERSISTED_ABI)
        rendered = render_evidence_markdown(pack)
        self.assertIn("## abi_derived", rendered)
        self.assertIn("## abi\n", rendered)
        self.assertIn("- Availability: `available`", rendered)
        self.assertIn("\"indirect_calls\": 2", rendered)

    def test_content_sha256_still_verifies_through_the_validate_convention(self):
        with tempfile.TemporaryDirectory() as directory:
            pack = self._collect_live(self.PERSISTED_ABI, out_dir=Path(directory), write=True)
            on_disk = json.loads((Path(directory) / "evidence.json").read_text(encoding="utf-8"))
            markdown = (Path(directory) / "evidence.md").read_text(encoding="utf-8")
        # ``_pack_digest`` drops ``paths`` and nulls ``content_sha256`` before
        # hashing, which is exactly how ``collect`` computed it.
        self.assertEqual(_pack_digest(on_disk), on_disk["content_sha256"])
        self.assertEqual(_pack_digest(on_disk), pack["content_sha256"])
        self.assertEqual(on_disk["content_sha256"], sha256_json({k: v for k, v in pack.items() if k != "paths"} | {"content_sha256": None}))
        self.assertIn("- Content SHA-256: `%s`" % on_disk["content_sha256"], markdown)

    def test_truncated_envelope_is_stored_as_returned(self):
        # ``validate._abi_category`` reads a ``{"truncated": true}`` value as "no
        # derived record", so the category must not reshape one into a projection
        # or an empty value on its way in.
        envelope = {"truncated": True, "preview": "..."}
        with patch("tools.reconstruction_tooling.evidence._index", return_value=self._index(self.PERSISTED_ABI)), \
             patch("tools.reconstruction_tooling.evidence._live_function", side_effect=self._live_function), \
             patch("tools.reconstruction_tooling.evidence._live_decompile", side_effect=self._live_decompile), \
             patch("tools.reconstruction_tooling.evidence._live_disassembly", side_effect=self._live_disassembly), \
             patch("tools.reconstruction_tooling.evidence._derived_abi",
                   return_value={"value": envelope, "observations": ["GhidraMCP /disassemble_function"]}):
            pack = collect(va=self.TARGET, live=True, write=False)
        derived = pack["categories"]["abi_derived"]
        self.assertEqual(derived["availability"], "available")
        self.assertEqual(derived["value"], envelope)
        self.assertIs(derived["value"]["truncated"], True)
        self.assertEqual(pack["categories"]["abi"]["value"], self.PERSISTED_ABI)


if __name__ == "__main__":
    unittest.main()
