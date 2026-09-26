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


if __name__ == "__main__":
    unittest.main()
