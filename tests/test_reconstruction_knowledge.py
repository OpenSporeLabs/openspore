"""Tests for generated reconstruction knowledge and atomic queue claims."""
import hashlib
import json
import os
import shutil
import sqlite3
import tempfile
import unittest
from concurrent.futures import ThreadPoolExecutor

from tools import reconstruction_knowledge as knowledge
from tools.mcp import config
from tools.mcp import registry


class ReconstructionKnowledgeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.index = knowledge.load_index(knowledge.DEFAULT_INDEX)

    def test_projection_tracks_manifest_and_source_hash(self):
        manifest = json.loads(
            (knowledge.ROOT / knowledge.MANIFEST_REL).read_text(
                encoding="utf-8"))
        digest = hashlib.sha256(
            (knowledge.ROOT / knowledge.MANIFEST_REL).read_bytes()).hexdigest()
        self.assertEqual(self.index["source_of_truth"]["manifest_sha256"], digest)
        self.assertGreaterEqual(self.index["counts"]["manifest_records"],
                                len(manifest["functions"]))
        self.assertEqual(self.index["counts"]["reconstructed_records"],
                         sum(record["reconstructed"]
                             for record in self.index["records"].values()))
        self.assertIn("0x00596da0", self.index["records"])
        self.assertEqual(self.index["records"]["0x00596da0"]["status"],
                         "reconstructed")

    def test_function_context_contains_bounded_dependencies_and_analogues(self):
        result = knowledge.function_context(
            self.index, "0x00e5b790", limit=3)
        self.assertEqual(result["status"], "ok")
        function = result["function"]
        self.assertTrue(function["reconstructed"])
        self.assertTrue(function["runtime_gated"])
        self.assertEqual(function["source"]["file"],
                         "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp")
        self.assertEqual(len(result["analogues"]), 3)
        self.assertLessEqual(len(result["related_functions"]), 6)
        self.assertLessEqual(len(function["dependencies"]["callers"]), 50)
        self.assertLessEqual(len(function["dependencies"]["callees"]), 50)

    def test_unresolved_frontier_target_has_context(self):
        result = knowledge.function_context(
            self.index, "0x00576c50", limit=4)
        self.assertEqual(result["status"], "ok")
        self.assertFalse(result["function"]["reconstructed"])
        self.assertEqual(result["function"]["ownership"]["claimability"],
                         "queue_candidate")
        self.assertTrue(result["function"]["source"]["decomp"])

    def test_package_type_and_frontier_queries(self):
        package = knowledge.package_context(
            self.index, "PKG-CAMERA-WAVE7", limit=10)
        self.assertEqual(package["status"], "ok")
        self.assertGreaterEqual(package["count"], 1)
        type_result = knowledge.type_context(self.index, "OpaqueNounManager")
        self.assertEqual(type_result["status"], "ok")
        self.assertTrue(type_result["functions"])
        frontier = knowledge.frontier_context(self.index, limit=2)
        self.assertEqual(frontier["status"], "ok")
        self.assertEqual(len(frontier["frontier"]), 2)
        self.assertTrue(frontier["truncated"])
        self.assertTrue(frontier["frontier"][0]["inspect"])

    def test_generation_is_deterministic(self):
        first, first_bootstrap = knowledge.build_index(knowledge.ROOT)
        second, second_bootstrap = knowledge.build_index(knowledge.ROOT)
        self.assertEqual(first, second)
        self.assertEqual(first_bootstrap, second_bootstrap)


class FunctionIdentityTest(unittest.TestCase):
    """Every record this projection mints must key on a function entry.

    Three addresses in the committed triage queue are not function entries: each
    is the inclusive last byte of the instruction before it, so minting a record
    under the row's own address manufactures a function identity that no
    disassembly supports. ``tools/reconstruction_knowledge.build_index``
    therefore resolves a non-entry onto the entry that contains it and keeps the
    address that was asked for under ``identity_resolution``.
    """

    @classmethod
    def setUpClass(cls):
        cls.universe = knowledge.load_function_universe(knowledge.ROOT)
        cls.index, _bootstrap = knowledge.build_index(knowledge.ROOT)

    # -- the universe itself ------------------------------------------------
    def test_the_universe_is_the_full_frozen_export(self):
        self.assertIsNotNone(self.universe)
        self.assertEqual(len(self.universe), 58757)
        starts = [item[0] for item in self.universe]
        self.assertEqual(starts, sorted(starts))
        self.assertEqual(len(set(starts)), len(starts))

    def test_a_missing_export_leaves_every_address_alone(self):
        # A silently empty universe would make every row look like a non-entry
        # and re-target the entire frontier, so absence must disable the
        # correction rather than perform it against nothing.
        self.assertIsNone(knowledge.load_function_universe(
            knowledge.ROOT / "does-not-exist"))
        self.assertIsNone(knowledge.canonical_identity("0x00e7b6c0", None))
        self.assertIsNone(knowledge.canonical_identity("0x00e7b6c0", []))

    # -- the resolver -------------------------------------------------------
    def test_an_entry_resolves_to_nothing(self):
        for va in ("0x00e7b630", "0x00e7d070", "0x00e3a270", "0x01053be0"):
            self.assertIsNone(
                knowledge.canonical_identity(va, self.universe),
                "%s is a function entry and must not be moved" % va)

    def test_an_interior_address_resolves_to_its_entry_and_offset(self):
        expected = {
            "0x00e7b6c0": ("0x00e7b630", 0x90),   # last byte of a CALL rel32
            "0x00e7d2c0": ("0x00e7d070", 0x250),  # top byte of a moffs32 operand
            "0x00e3a400": ("0x00e3a270", 0x190),  # trailing disp8 byte
        }
        for va, (entry, offset) in sorted(expected.items()):
            placement = knowledge.canonical_identity(va, self.universe)
            self.assertIsNotNone(placement, "%s should resolve" % va)
            self.assertEqual(placement[0], entry)
            self.assertEqual(placement[1], offset)
            self.assertTrue(placement[2], "the entry must carry its own name")

    def test_an_address_outside_every_entry_is_left_alone(self):
        # The universe is not a partition: real padding and a ``size`` that stops
        # short of the final instruction both leave gaps. Resolving into a gap
        # would re-point a target at a function that does not contain it, which is
        # the same class of error the correction exists to remove.
        bounds = [(0x00401000, 0x8, "0x00401000", "FUN_00401000")]
        # 0x00401004 is interior; 0x00401008 is the exclusive end of a
        # 0x00401000..0x00401007 body, and 0x00401010 is the next gap.
        self.assertEqual(knowledge.canonical_identity("0x00401004", bounds),
                         ("0x00401000", 4, "FUN_00401000"))
        self.assertIsNone(knowledge.canonical_identity("0x00401008", bounds))
        self.assertIsNone(knowledge.canonical_identity("0x00401010", bounds))
        self.assertIsNone(knowledge.canonical_identity("0x00400900", bounds))

    # -- the projection -----------------------------------------------------
    def test_no_record_keys_on_a_non_function_entry(self):
        resolved = {record["identity_resolution"]["canonical_va"]
                    for record in self.index["records"].values()
                    if isinstance(record.get("identity_resolution"), dict)}
        offenders = sorted(
            va for va in self.index["records"]
            if knowledge.canonical_identity(va, self.universe) is not None)
        self.assertEqual(offenders, [],
                         "these records are keyed on addresses that are not "
                         "function entries: %s" % offenders)
        # Exactly the three corrected identities, so the check is not vacuous.
        self.assertEqual(
            resolved,
            {"0x00e3a270", "0x00e7b630", "0x00e7d070"})

    def test_a_resolved_record_keeps_the_address_that_was_asked_for(self):
        for requested, canonical in (("0x00e7b6c0", "0x00e7b630"),
                                     ("0x00e7d2c0", "0x00e7d070"),
                                     ("0x00e3a400", "0x00e3a270")):
            self.assertNotIn(requested, self.index["records"])
            record = self.index["records"][canonical]
            resolution = record["identity_resolution"]
            self.assertEqual(resolution["rule"], "containing_function_entry")
            self.assertEqual(resolution["canonical_va"], canonical)
            self.assertEqual([item["va"] for item in resolution["requested"]],
                             [requested])
            self.assertGreater(resolution["requested"][0]["offset"], 0)

    def test_a_canonical_record_names_itself_from_the_universe(self):
        # The queue rows that named the non-entries carried a null name, which is
        # exactly what left them unbindable to any source span downstream. The
        # corrected record must take the entry's own name.
        for canonical, name in (("0x00e7b630", "FUN_00e7b630"),
                                ("0x00e7d070", "FUN_00e7d070"),
                                ("0x00e3a270", "FUN_00e3a270")):
            self.assertEqual(self.index["records"][canonical]["name"], name)

    def test_an_unresolved_record_carries_no_identity_key_at_all(self):
        # Absent rather than null, so an unaffected record stays byte-identical
        # and the presence of the key is itself the signal of a correction.
        record = self.index["records"]["0x00f9fef0"]
        self.assertNotIn("identity_resolution", record)

    def test_the_correction_is_deterministic(self):
        first, _ = knowledge.build_index(knowledge.ROOT)
        second, _ = knowledge.build_index(knowledge.ROOT)
        self.assertEqual(first["records"], second["records"])

    def test_a_real_caller_of_a_resolved_entry_is_named(self):
        # 0x00e6d200 is called by FUN_00e7b630. While the container was masked by
        # the phantom address it reached the index with no name at all.
        callers = self.index["records"]["0x00e6d200"]["dependencies"]["callers"]
        named = {item["va"]: item["name"] for item in callers}
        self.assertEqual(named.get("0x00e7b630"), "FUN_00e7b630")

    # -- the falsifier ------------------------------------------------------
    def test_the_correction_is_load_bearing(self):
        # With the universe withheld, every address resolves to nothing, so the
        # three phantom keys come back and the two corrected entries disappear.
        # This is what the correction removes, stated as an executable claim.
        rows = [row for row in json.loads(
            (knowledge.ROOT / knowledge.QUEUE_REL).read_text(
                encoding="utf-8"))["queue"] if isinstance(row, dict)]
        phantom = {"0x00e3a400", "0x00e7b6c0", "0x00e7d2c0"}
        unresolved = {knowledge.normalize_va(row.get("va")) for row in rows
                      if knowledge.canonical_identity(
                          knowledge.normalize_va(row.get("va")), None) is None}
        self.assertTrue(phantom <= unresolved,
                        "the phantom addresses must be exactly what an "
                        "identity-blind projection would keep")
        # ... and the correction is what stops them being kept.
        self.assertEqual(
            sorted(phantom & {va for va in self.index["records"]}), [],
            "no phantom address may still mint a record")



class QueueClaimTest(unittest.TestCase):
    def setUp(self):
        self.old_db = os.environ.get("OPENSPORE_DB")
        self.old_index = os.environ.get("OPENSPORE_RECONSTRUCTION_INDEX")
        self.tmpdir = tempfile.mkdtemp(prefix="openspore-claim-test-")
        self.db = os.path.join(self.tmpdir, "claims.db")
        os.environ["OPENSPORE_DB"] = self.db
        connection = sqlite3.connect(self.db)
        with open(config.resolve("knowledgegraph", "schema.sql"),
                  encoding="utf-8") as handle:
            connection.executescript(handle.read())
        connection.execute(
            "INSERT INTO investigations(id,kind,va,name,subsystem,mode,"
            "why_interesting,stage,status,binary_sha256) "
            "VALUES(?,?,?,?,?,?,?,?,?,?)",
            ("fn:00b3d300:root", "function", "00b3d300", "root", None,
             "replace", "fixture", "QUEUED", "queued", "a" * 64))
        connection.commit()
        connection.close()

    def tearDown(self):
        if self.old_db is None:
            os.environ.pop("OPENSPORE_DB", None)
        else:
            os.environ["OPENSPORE_DB"] = self.old_db
        if self.old_index is None:
            os.environ.pop("OPENSPORE_RECONSTRUCTION_INDEX", None)
        else:
            os.environ["OPENSPORE_RECONSTRUCTION_INDEX"] = self.old_index
        shutil.rmtree(self.tmpdir, ignore_errors=True)

    def claim(self, implementer):
        return registry.dispatch("queue_op", {
            "op": "claim", "id": "fn:00b3d300:root",
            "implementer_id": implementer, "binary_sha256": "a" * 64,
        })

    def test_concurrent_claim_has_one_winner(self):
        with ThreadPoolExecutor(max_workers=2) as executor:
            results = list(executor.map(self.claim, ("alice", "bob")))
        winners = [result for result in results if result.get("claimed")]
        self.assertEqual(len(winners), 1, results)
        self.assertEqual(sum(result.get("code") == "already_claimed"
                             for result in results), 1, results)

    def test_legacy_update_activation_is_atomic(self):
        def activate(implementer):
            return registry.dispatch("queue_op", {
                "op": "update", "id": "fn:00b3d300:root",
                "status": "active", "implementer_id": implementer,
            })
        with ThreadPoolExecutor(max_workers=2) as executor:
            results = list(executor.map(activate, ("alice", "bob")))
        self.assertEqual(sum(result.get("status") == "ok" for result in results),
                         1, results)
        self.assertEqual(sum(result.get("code") == "already_claimed"
                             for result in results), 1, results)

    def test_same_owner_claim_is_idempotent(self):
        first = self.claim("alice")
        second = self.claim("alice")
        self.assertTrue(first["claimed"])
        self.assertFalse(second["claimed"])
        self.assertTrue(second["idempotent"])

    def test_stale_claim_requires_explicit_reclaim(self):
        connection = sqlite3.connect(self.db)
        connection.execute(
            "UPDATE investigations SET status='active', implementer_id='alice', "
            "updated_at='2000-01-01 00:00:00' WHERE id=?",
            ("fn:00b3d300:root",))
        connection.commit()
        connection.close()
        refused = self.claim("bob")
        self.assertEqual(refused["code"], "already_claimed")
        self.assertTrue(refused["stale"])
        allowed = registry.dispatch("queue_op", {
            "op": "claim", "id": "fn:00b3d300:root",
            "implementer_id": "bob", "binary_sha256": "a" * 64,
            "allow_stale": True, "stale_after_seconds": 60,
        })
        self.assertTrue(allowed["claimed"])

    def test_terminal_and_blocked_claims_fail_closed(self):
        connection = sqlite3.connect(self.db)
        connection.execute(
            "UPDATE investigations SET status='done' WHERE id=?",
            ("fn:00b3d300:root",))
        connection.commit()
        connection.close()
        result = self.claim("alice")
        self.assertEqual(result["code"], "already_completed")

        connection = sqlite3.connect(self.db)
        connection.execute(
            "UPDATE investigations SET status='blocked', block_reason='gate' "
            "WHERE id=?", ("fn:00b3d300:root",))
        connection.commit()
        connection.close()
        result = self.claim("alice")
        self.assertEqual(result["code"], "blocked")

    def test_mcp_function_context_includes_active_claim(self):
        connection = sqlite3.connect(self.db)
        connection.execute(
            "UPDATE investigations SET status='active', implementer_id='alice' "
            "WHERE id=?", ("fn:00b3d300:root",))
        connection.commit()
        connection.close()
        result = registry.dispatch("function_context", {"va": "0x00b3d300"})
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["claims"][0]["implementer_id"], "alice")


class FrontierIdentityTest(unittest.TestCase):
    """The frontier must key on the same identity the index resolved.

    ``frontier._queue_rows`` reads the committed triage queue as written -- the
    queue is not rewritten by the correction -- so a row naming a non-entry would
    otherwise reappear as a frontier target even though no index record exists
    for it. The mapping is read back out of the index's own
    ``identity_resolution`` rather than recomputed.
    """

    @classmethod
    def setUpClass(cls):
        from tools.reconstruction_tooling import frontier as frontier_mod
        cls.frontier_mod = frontier_mod
        cls.index, _ = knowledge.build_index(knowledge.ROOT)

    def _plan(self):
        class Args(object):
            limit = 1000
            offset = 0
        return self.frontier_mod.frontier(args=Args())

    def test_the_identity_map_is_read_from_the_index_not_recomputed(self):
        mapping = self.frontier_mod._identity_map(self.index)
        self.assertEqual(mapping, {
            "0x00e3a400": "0x00e3a270",
            "0x00e7b6c0": "0x00e7b630",
            "0x00e7d2c0": "0x00e7d070",
        })

    def test_an_index_without_resolutions_yields_an_empty_mapping(self):
        self.assertEqual(self.frontier_mod._identity_map({}), {})
        self.assertEqual(self.frontier_mod._identity_map({"records": None}), {})

    def test_the_projection_advertises_no_phantom_target(self):
        plan = self._plan()
        advertised = {target["va"] for target in plan.get("targets", [])}
        for phantom in ("0x00e3a400", "0x00e7b6c0", "0x00e7d2c0"):
            self.assertNotIn(phantom, advertised,
                             "%s is not a function entry and must not be "
                             "offered as a reconstruction target" % phantom)
        for canonical in ("0x00e3a270", "0x00e7b630", "0x00e7d070"):
            self.assertIn(canonical, advertised)

    def test_a_resolved_target_defers_on_its_real_dependencies(self):
        # The phantom rows deferred on nothing. The real functions they were
        # standing in for have genuine unreconstructed callees, and the frontier
        # must now say so rather than present them as unblocked.
        targets = {target["va"]: target
                   for target in self._plan().get("targets", [])}
        for canonical, callee in (("0x00e7b630", "0x00e6d200"),
                                  ("0x00e7d070", "0x00e62340")):
            target = targets[canonical]
            self.assertEqual(target["disposition"], "deferred")
            reasons = {reason["code"]: reason for reason in target["reasons"]}
            self.assertIn("open_dependencies", reasons)
            self.assertIn(callee, reasons["open_dependencies"]["detail"])
            self.assertEqual(target["dependencies"]["open_callees"],
                             [callee])


if __name__ == "__main__":
    unittest.main()
