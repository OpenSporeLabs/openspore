"""Focused tests for the KG-spine MCP tools (tools/mcp/kg_tools.py).

Uses a temporary SQLite database (tempfile + knowledgegraph/schema.sql;
no proprietary assets, no Ghidra, no game binary) selected through the
OPENSPORE_DB env override. Covers: node lookup/search, traversal,
evidence retrieval, investigation retrieval, queue ops (insert/list/get/
update/close, dedup idempotency, missing-ID errors), provenance/
staleness, and ordering determinism.

Run from the repo root:
    python3 -m unittest tests.mcp.test_kg -v
"""
import json
import os
import shutil
import sqlite3
import tempfile
import unittest

from tools.mcp import config
from tools.mcp import ghidra_tools
from tools.mcp import kg_tools
from tools.mcp import registry

SHA_A = "a" * 64  # current build identity in these fixtures
SHA_B = "b" * 64  # stale build identity: must stay queryable, never purged

SEED_NODES = [
    # Deliberately scrambled: queries must still come back ordered.
    ("Subsystem", "sub:cell-movement", "VERIFIED", None),
    ("Function", "fun:00e5b800", "INFERRED", SHA_B),
    ("Structure", "struct:PlayerEntity", "SUPPORTED", SHA_A),
    ("Function", "fun:00e5b790", "OBSERVED", SHA_A),
    ("Class", "cls:00e5b790", "CONFIRMED", SHA_A),
    ("Class", "SameName", "INFERRED", SHA_A),
    ("Function", "SameName", "SUPPORTED", SHA_A),
    ("Function", "pct%_weird", "UNKNOWN", SHA_A),
]

SEED_EDGES = [
    ("fun:00e5b790", "calls", "cls:00e5b790"),
    ("cls:00e5b790", "documents-by", "struct:PlayerEntity"),
]

SEED_INVS = [
    ("fun:00e5b790:Move", "function", "00e5b790", "Move",
     None, "replace", "queued", "QUEUED", SHA_A, None),
    ("fun:00e5b900:Active", "function", "00e5b900", "ActiveFn",
     None, "replace", "active", "QUEUED", SHA_A, "alice"),
    ("sub:resource", "subsystem", None, None,
     "resource", "understand", "blocked", "QUEUED", SHA_A, None),
    ("fun:00e5b800:Old", "function", "00e5b800", "OldFn",
     None, "replace", "done", "RECORDED", SHA_B, None),
]


class TempDBTestCase(unittest.TestCase):
    """Each test gets a fresh temp DB seeded with the fixture above."""

    def setUp(self):
        self._old_db = os.environ.get("OPENSPORE_DB")
        self.tmpdir = tempfile.mkdtemp(prefix="openspore-kg-test-")
        self.db = os.path.join(self.tmpdir, "test.db")
        os.environ["OPENSPORE_DB"] = self.db
        schema = config.resolve("knowledgegraph", "schema.sql")
        with open(schema) as fh:
            sql = fh.read()
        conn = sqlite3.connect(self.db)
        conn.executescript(sql)
        with conn:
            for label, name, ev, sha in SEED_NODES:
                conn.execute(
                    "INSERT INTO node(label,name,evidence_level,"
                    "binary_sha256) VALUES(?,?,?,?)",
                    (label, name, ev, sha))
            idmap = {}
            for row in conn.execute("SELECT id, name FROM node"):
                idmap.setdefault(row[1], row[0])
            for src, rel, dst in SEED_EDGES:
                conn.execute(
                    "INSERT INTO edge(src,dst,rel) VALUES(?,?,?)",
                    (idmap[src], idmap[dst], rel))
            conn.execute(
                "INSERT INTO test_result(name,stage,pass) VALUES(?,?,?)",
                ("seed_test", "cell", 1))
            for (iid, kind, va, nm, sub, mode,
                 status, stage, sha, impl) in SEED_INVS:
                conn.execute(
                    "INSERT INTO investigations(id,kind,va,name,subsystem,"
                    "mode,why_interesting,stage,status,implementer_id,"
                    "binary_sha256) VALUES(?,?,?,?,?,?,?,?,?,?,?)",
                    (iid, kind, va, nm, sub, mode, "fixture",
                     stage, status, impl, sha))
        conn.close()

    def tearDown(self):
        if self._old_db is None:
            os.environ.pop("OPENSPORE_DB", None)
        else:
            os.environ["OPENSPORE_DB"] = self._old_db
        shutil.rmtree(self.tmpdir, ignore_errors=True)

    # -- helpers ------------------------------------------------------ #
    def node_count(self):
        conn = sqlite3.connect(self.db)
        n = conn.execute("SELECT COUNT(*) FROM node").fetchone()[0]
        conn.close()
        return n

    def inv_count(self):
        conn = sqlite3.connect(self.db)
        n = conn.execute("SELECT COUNT(*) FROM investigations").fetchone()[0]
        conn.close()
        return n


class TestKgQuery(TempDBTestCase):
    def test_all_ordered_deterministically(self):
        first = registry.dispatch("kg_query", {})
        second = registry.dispatch("kg_query", {})
        self.assertEqual(first["status"], "ok")
        keys = [(n["label"], n["name"]) for n in first["nodes"]]
        self.assertEqual(keys, sorted(keys))
        self.assertEqual(first["total"], len(SEED_NODES))
        self.assertEqual(first, second)  # byte-stable across calls

    def test_label_filter(self):
        result = registry.dispatch("kg_query", {"label": "Function"})
        self.assertEqual(result["status"], "ok")
        self.assertTrue(result["nodes"])
        for node in result["nodes"]:
            self.assertEqual(node["label"], "Function")
        names = [n["name"] for n in result["nodes"]]
        self.assertEqual(names, sorted(names))

    def test_name_substring(self):
        result = registry.dispatch("kg_query", {"query": "00e5b790"})
        names = sorted(n["name"] for n in result["nodes"])
        self.assertEqual(names, ["cls:00e5b790", "fun:00e5b790"])

    def test_like_escaping(self):
        # '%' and '_' in the query are literals, not wildcards.
        result = registry.dispatch("kg_query", {"query": "%"})
        self.assertEqual([n["name"] for n in result["nodes"]],
                         ["pct%_weird"])
        result = registry.dispatch("kg_query", {"query": "00e5b79_"})
        self.assertEqual(result["nodes"], [])

    def test_evidence_filter(self):
        result = registry.dispatch(
            "kg_query", {"evidence": "OBSERVED"})
        self.assertEqual([n["name"] for n in result["nodes"]],
                         ["fun:00e5b790"])
        bad = registry.dispatch("kg_query", {"evidence": "RUMOR"})
        self.assertEqual(bad["status"], "error")
        self.assertEqual(bad["code"], "invalid_evidence")

    def test_limit_offset(self):
        page1 = registry.dispatch("kg_query", {"limit": 3, "offset": 0})
        page2 = registry.dispatch("kg_query", {"limit": 3, "offset": 3})
        self.assertEqual(page1["count"], 3)
        names1 = [n["name"] for n in page1["nodes"]]
        names2 = [n["name"] for n in page2["nodes"]]
        self.assertFalse(set(names1) & set(names2))
        bad = registry.dispatch("kg_query", {"limit": "many"})
        self.assertEqual(bad["code"], "invalid_params")

    def test_evidence_provenance_on_nodes(self):
        result = registry.dispatch(
            "kg_query", {"query": "fun:00e5b800"})
        (node,) = result["nodes"]
        self.assertEqual(node["evidence_level"], "INFERRED")
        self.assertEqual(node["binary_sha256"], SHA_B)  # stale, queryable


class TestKgNeighbors(TempDBTestCase):
    def test_depth1(self):
        result = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790"})
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["depth"], 1)
        edge_set = {(e["src"], e["rel"], e["dst"])
                    for e in result["edges"]}
        self.assertEqual(edge_set, {
            ("fun:00e5b790", "calls", "cls:00e5b790"),
            ("cls:00e5b790", "documents-by", "struct:PlayerEntity"),
        })
        names = sorted(n["name"] for n in result["nodes"])
        self.assertEqual(names, ["cls:00e5b790", "fun:00e5b790",
                                 "struct:PlayerEntity"])

    def test_depth2_reaches_further(self):
        d1 = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 1})
        d2 = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 2})
        self.assertLessEqual(d1["edge_count"], d2["edge_count"])
        names2 = sorted(n["name"] for n in d2["nodes"])
        self.assertIn("struct:PlayerEntity", names2)
        # Deterministic: repeated calls are identical.
        again = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 2})
        self.assertEqual(d2, again)

    def test_rel_filter(self):
        result = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "rel": "calls"})
        self.assertEqual(
            [(e["src"], e["rel"], e["dst"]) for e in result["edges"]],
            [("fun:00e5b790", "calls", "cls:00e5b790")])

    def test_missing_node(self):
        result = registry.dispatch("kg_neighbors", {"name": "nope"})
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "not_found")

    def test_ambiguous_name(self):
        result = registry.dispatch("kg_neighbors", {"name": "SameName"})
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "ambiguous")
        self.assertEqual(sorted(result["labels"]), ["Class", "Function"])

    def test_bad_depth(self):
        for bad in (0, 3, "deep"):
            result = registry.dispatch(
                "kg_neighbors", {"name": "fun:00e5b790", "depth": bad})
            self.assertEqual(result["status"], "error", bad)
        missing = registry.dispatch("kg_neighbors", {})
        self.assertEqual(missing["code"], "missing_param")


class TestKgNeighborsSlimming(TempDBTestCase):
    """brief default / detail restore / limit cap (S2.1 scope G)."""

    FULL_ROW_KEYS = {"id", "label", "name", "attrs", "confidence",
                     "origin", "note", "evidence_level", "binary_sha256",
                     "created_at", "updated_at"}

    def test_brief_default_shape(self):
        result = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790"})
        self.assertEqual(result["status"], "ok", result)
        self.assertFalse(result["detail"], result)
        self.assertEqual(result["limit"], 100, result)
        self.assertFalse(result["truncated"], result)
        self.assertEqual(result["total_nodes"], len(result["nodes"]),
                         result)
        for node in result["nodes"]:
            self.assertEqual(set(node.keys()),
                             {"name", "label", "evidence_level"}, node)
            # No per-node timestamps / build identity / attrs in brief.
            for banned in ("created_at", "updated_at", "binary_sha256",
                           "attrs", "confidence", "origin", "note", "id"):
                self.assertNotIn(banned, node, node)

    def test_detail_restores_full_rows(self):
        full = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "detail": True})
        self.assertEqual(full["status"], "ok", full)
        self.assertTrue(full["detail"], full)
        for node in full["nodes"]:
            self.assertEqual(set(node.keys()), self.FULL_ROW_KEYS, node)
        # brief=false is the alias path; same rows, same order.
        alias = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "brief": False})
        self.assertEqual(alias["detail"], True, alias)
        self.assertEqual(alias["nodes"], full["nodes"], alias)
        # brief values agree with the full rows on shared evidence keys.
        brief = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790"})
        self.assertEqual(len(brief["nodes"]), len(full["nodes"]))
        for b_node, f_node in zip(brief["nodes"], full["nodes"]):
            self.assertEqual(b_node["name"], f_node["name"])
            self.assertEqual(b_node["label"], f_node["label"])
            self.assertEqual(b_node["evidence_level"],
                             f_node["evidence_level"])

    def test_limit_cap_and_truncated(self):
        bounded = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "limit": 2})
        self.assertEqual(bounded["node_count"], 2, bounded)
        self.assertEqual(bounded["total_nodes"], 3, bounded)
        self.assertTrue(bounded["truncated"], bounded)
        # Over-cap limits clamp to 500 (flag stays honest).
        big = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "limit": 9999})
        self.assertEqual(big["limit"], 500, big)
        self.assertFalse(big["truncated"], big)
        self.assertEqual(big["total_nodes"], 3, big)
        bad = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "limit": "many"})
        self.assertEqual(bad["code"], "invalid_params", bad)
        neg = registry.dispatch(
            "kg_neighbors", {"name": "cls:00e5b790", "limit": -1})
        self.assertEqual(neg["code"], "invalid_params", neg)

    def test_deterministic_order_and_repeat(self):
        first = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 2})
        second = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 2})
        self.assertEqual(first, second)  # byte-stable across calls
        keys = [(n["label"], n["name"]) for n in first["nodes"]]
        self.assertEqual(keys, sorted(keys))

    def test_brief_smaller_than_detail_no_evidence_loss(self):
        brief = registry.dispatch(
            "kg_neighbors", {"name": "fun:00e5b790", "depth": 2})
        full = registry.dispatch(
            "kg_neighbors",
            {"name": "fun:00e5b790", "depth": 2, "detail": True})
        brief_size = len(json.dumps(brief, sort_keys=True))
        full_size = len(json.dumps(full, sort_keys=True))
        self.assertLess(brief_size, full_size)
        # Zero evidence-field loss: every brief value equals the full row.
        self.assertEqual(len(brief["nodes"]), len(full["nodes"]))
        for b_node, f_node in zip(brief["nodes"], full["nodes"]):
            for key, value in b_node.items():
                self.assertEqual(value, f_node[key])


class TestKgRecord(TempDBTestCase):
    def test_batch_ok(self):
        before = self.node_count()
        result = registry.dispatch("kg_record", {
            "reason": "fixture cross-tool result",
            "binary_sha256": SHA_A,
            "nodes": [
                {"label": "Function", "name": "fun:newevidence",
                 "evidence_level": "SUPPORTED", "origin": "static",
                 "attrs": {"rva": "0x1234"}},
            ],
            "edges": [{"src": "fun:newevidence", "dst": "fun:00e5b790",
                       "rel": "calls"}],
            "tests": [{"name": "new_test", "stage": "cell", "pass": 1}],
        })
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["inserted"],
                         {"nodes": 1, "edges": 1, "tests": 1})
        self.assertEqual(self.node_count(), before + 1)
        # Evidence-derived confidence follows scale.py (SUPPORTED -> 0.75).
        lookup = registry.dispatch("kg_query", {"query": "fun:newevidence"})
        (node,) = lookup["nodes"]
        self.assertEqual(node["evidence_level"], "SUPPORTED")
        self.assertEqual(node["confidence"], 0.75)
        self.assertEqual(node["attrs"], {"rva": "0x1234"})
        self.assertEqual(node["binary_sha256"], SHA_A)

    def test_missing_reason(self):
        result = registry.dispatch("kg_record", {"nodes": []})
        self.assertEqual(result["code"], "missing_reason")
        blank = registry.dispatch("kg_record", {"reason": "  "})
        self.assertEqual(blank["code"], "missing_reason")

    def test_invalid_evidence_rejected(self):
        result = registry.dispatch("kg_record", {
            "reason": "bad level",
            "nodes": [{"label": "Function", "name": "fun:x",
                       "evidence_level": "HYPOTHESIS"}]})
        self.assertEqual(result["status"], "error")
        self.assertEqual(result["code"], "invalid_evidence")
        self.assertEqual(self.node_count(), len(SEED_NODES))  # no write

    def test_status_never_written(self):
        for payload in (
            {"nodes": [{"label": "Subsystem", "name": "sub:x",
                        "attrs": {"status": "replaced-stub"}}]},
            {"nodes": [{"label": "Subsystem", "name": "sub:x",
                        "status": "replaced-stub"}]},
            {"tests": [{"name": "t", "status": "replaced-stub"}]},
        ):
            payload["reason"] = "status smuggle"
            result = registry.dispatch("kg_record", payload)
            self.assertEqual(result["code"], "status_forbidden", payload)

    def test_edge_endpoint_must_exist_atomic(self):
        before = self.node_count()
        result = registry.dispatch("kg_record", {
            "reason": "dangling edge",
            "nodes": [{"label": "Function", "name": "fun:orphan"}],
            "edges": [{"src": "fun:orphan", "dst": "ghost-node",
                       "rel": "calls"}],
        })
        self.assertEqual(result["code"], "not_found")
        # Whole batch rolled back: the node was not kept either.
        self.assertEqual(self.node_count(), before)


class TestQueueOp(TempDBTestCase):
    def test_insert_get_list(self):
        inserted = registry.dispatch("queue_op", {
            "op": "insert", "kind": "function", "va": "00112233",
            "name": "BrandNew", "binary_sha256": SHA_A,
            "why_interesting": "fixture",
        })
        self.assertEqual(inserted["status"], "ok")
        self.assertTrue(inserted["inserted"])
        fetched = registry.dispatch(
            "queue_op", {"op": "get", "id": inserted["id"]})
        self.assertEqual(fetched["investigation"]["va"], "00112233")
        self.assertEqual(fetched["investigation"]["status"], "queued")
        listed = registry.dispatch("queue_op", {"op": "list"})
        ids = [i["id"] for i in listed["investigations"]]
        self.assertEqual(ids, sorted(ids))  # deterministic order
        self.assertIn(inserted["id"], ids)

    def test_insert_dedup_idempotent(self):
        before = self.inv_count()
        first = registry.dispatch("queue_op", {
            "op": "insert", "kind": "function", "va": "00e5b790",
            "name": "Move", "binary_sha256": SHA_A,
            "why_interesting": "dup",
        })
        self.assertEqual(first["status"], "ok")
        self.assertFalse(first["inserted"])  # fixture row already queued
        self.assertEqual(first["id"], "fun:00e5b790:Move")
        self.assertEqual(self.inv_count(), before)
        # Same dedup key, different id text: still ignored, survivor kept.
        again = registry.dispatch("queue_op", {
            "op": "insert", "id": "other-id", "kind": "function",
            "va": "00e5b790", "name": "Move",
            "binary_sha256": SHA_A, "why_interesting": "dup2",
        })
        self.assertFalse(again["inserted"])
        self.assertEqual(again["id"], "fun:00e5b790:Move")
        self.assertEqual(self.inv_count(), before)

    def test_missing_ids_are_errors(self):
        for op in ("get", "update", "close"):
            params = {"op": op, "id": "ghost:id"}
            if op == "update":
                params["status"] = "active"
            result = registry.dispatch("queue_op", params)
            self.assertEqual(result["status"], "error", op)
            self.assertEqual(result["code"], "not_found", op)

    def test_update_and_validation(self):
        updated = registry.dispatch("queue_op", {
            "op": "update", "id": "fun:00e5b790:Move",
            "status": "active", "implementer_id": "bob",
        })
        self.assertEqual(updated["status"], "ok")
        self.assertEqual(
            updated["investigation"]["implementer_id"], "bob")
        bad_status = registry.dispatch("queue_op", {
            "op": "update", "id": "fun:00e5b790:Move",
            "status": "vibing",
        })
        self.assertEqual(bad_status["code"], "invalid_status")
        bad_field = registry.dispatch("queue_op", {
            "op": "update", "id": "fun:00e5b790:Move",
            "binary_sha256": "x",
        })
        self.assertEqual(bad_field["code"], "invalid_params")
        empty = registry.dispatch(
            "queue_op", {"op": "update", "id": "fun:00e5b790:Move"})
        self.assertEqual(empty["code"], "nothing_to_update")

    def test_no_duplicate_claims(self):
        result = registry.dispatch("queue_op", {
            "op": "update", "id": "fun:00e5b900:Active",
            "status": "active", "implementer_id": "bob",
        })
        self.assertEqual(result["code"], "already_claimed")

    def test_close_never_deletes(self):
        closed = registry.dispatch(
            "queue_op", {"op": "close", "id": "fun:00e5b790:Move"})
        self.assertEqual(closed["status"], "ok")
        self.assertTrue(closed["closed"])
        self.assertEqual(closed["previous_status"], "queued")
        # Row survives with terminal status...
        fetched = registry.dispatch(
            "queue_op", {"op": "get", "id": "fun:00e5b790:Move"})
        self.assertEqual(fetched["investigation"]["status"], "done")
        # ...and re-closing is idempotent, still present.
        again = registry.dispatch(
            "queue_op", {"op": "close", "id": "fun:00e5b790:Move"})
        self.assertFalse(again["closed"])
        self.assertEqual(again["previous_status"], "done")
        bad_disp = registry.dispatch(
            "queue_op", {"op": "close", "id": "sub:resource",
                         "status": "queued"})
        self.assertEqual(bad_disp["code"], "invalid_params")

    def test_list_filters(self):
        queued = registry.dispatch(
            "queue_op", {"op": "list", "status": "queued"})
        self.assertEqual(
            {i["id"] for i in queued["investigations"]},
            {"fun:00e5b790:Move"})
        bad_op = registry.dispatch("queue_op", {"op": "launch"})
        self.assertEqual(bad_op["code"], "invalid_params")


class TestProvenanceAndStaleness(TempDBTestCase):
    def test_stale_identity_stays_queryable(self):
        nodes = registry.dispatch(
            "kg_query", {"evidence": "INFERRED"})
        shas = {n["binary_sha256"] for n in nodes["nodes"]}
        self.assertIn(SHA_B, shas)
        invs = registry.dispatch(
            "queue_op", {"op": "list", "binary_sha256": SHA_B})
        self.assertEqual(
            [i["id"] for i in invs["investigations"]],
            ["fun:00e5b800:Old"])

    def test_new_identity_preserves_old(self):
        before_nodes = self.node_count()
        registry.dispatch("queue_op", {
            "op": "insert", "kind": "function", "va": "00e5b800",
            "name": "OldFn", "binary_sha256": "c" * 64,
            "why_interesting": "re-queue under new build",
        })
        # Old-identity row untouched; both listed.
        old = registry.dispatch(
            "queue_op", {"op": "get", "id": "fun:00e5b800:Old"})
        self.assertEqual(old["investigation"]["binary_sha256"], SHA_B)
        self.assertEqual(old["investigation"]["status"], "done")
        self.assertEqual(self.node_count(), before_nodes)


class TestPipelineAndTarget(TempDBTestCase):
    def test_pipeline_state(self):
        before_nodes, before_invs = self.node_count(), self.inv_count()
        result = registry.dispatch("pipeline_state", {})
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["kg_counts"]["node"], len(SEED_NODES))
        self.assertEqual(result["kg_counts"]["edge"], len(SEED_EDGES))
        self.assertEqual(result["kg_counts"]["investigations"],
                         len(SEED_INVS))
        self.assertEqual(result["investigations_by_status"]["queued"], 1)
        self.assertEqual(result["investigations_by_status"]["done"], 1)
        status_doc = result["replacement_status"]
        self.assertTrue(status_doc["present"])
        with open(config.resolve("docs", "replacement-status.json")) as fh:
            expected = len(json.load(fh)["subsystems"])
        self.assertEqual(status_doc["total"], expected)
        self.assertIn("cell-movement.json", result["dossiers"]["json"])
        # Read-only: counts unchanged.
        self.assertEqual(self.node_count(), before_nodes)
        self.assertEqual(self.inv_count(), before_invs)

    def test_target_select(self):
        before = self.inv_count()
        result = registry.dispatch("target_select", {})
        self.assertEqual(result["status"], "ok")
        # Terminal (done) rows never rank; active outranks queued.
        self.assertEqual(
            [c["status"] for c in result["candidates"]],
            ["active", "queued", "blocked"])
        self.assertEqual(
            [c for c in result["candidates"]
             if c["id"] == "fun:00e5b800:Old"], [])
        picked = registry.dispatch(
            "target_select", {"target": "fun:00e5b790:Move"})
        self.assertEqual(picked["selected"]["va"], "00e5b790")
        missed = registry.dispatch("target_select", {"target": "ghost"})
        self.assertIsNone(missed["selected"])
        self.assertEqual(self.inv_count(), before)  # read-only

    def test_target_select_hit(self):
        picked = registry.dispatch(
            "target_select", {"target": "fun:00e5b790:Move"})
        self.assertEqual(picked["status"], "ok", picked)
        self.assertEqual(picked["select_status"], "selected", picked)
        self.assertEqual(picked["selected"]["id"],
                         "fun:00e5b790:Move", picked)
        self.assertEqual(picked["selected"]["va"], "00e5b790", picked)
        self.assertIn("reason", picked, picked)
        self.assertIn("next_action", picked, picked)
        self.assertIsNotNone(picked.get("score"), picked)

    def test_target_select_miss(self):
        missed = registry.dispatch("target_select", {"target": "ghost"})
        self.assertEqual(missed["status"], "ok", missed)
        self.assertIsNone(missed["selected"], missed)
        self.assertEqual(missed["select_status"], "not_found", missed)
        self.assertIn("queue_op", missed.get("hint", ""), missed)
        self.assertIn("list", missed.get("hint", ""), missed)
        self.assertIn("next_action", missed, missed)

    def test_target_select_no_target_actionable(self):
        result = registry.dispatch("target_select", {})
        self.assertEqual(result["status"], "ok", result)
        self.assertIsNone(result["selected"], result)
        self.assertEqual(result["select_status"], "no_target", result)
        # Guidance, not a bare selected:null.
        self.assertTrue(result.get("reason"), result)
        self.assertTrue(result.get("hint"), result)
        self.assertTrue(result.get("next_action"), result)
        self.assertGreater(len(result["candidates"]), 0, result)

    def test_target_select_status_filter(self):
        only_active = registry.dispatch(
            "target_select", {"status": "active"})
        self.assertEqual(only_active["status"], "ok", only_active)
        self.assertEqual(only_active["filters"], {"status": "active"},
                         only_active)
        self.assertTrue(only_active["candidates"], only_active)
        for cand in only_active["candidates"]:
            self.assertEqual(cand["status"], "active", cand)
        # Rank order unchanged within the filtered pool.
        only_queued = registry.dispatch(
            "target_select", {"status": "queued"})
        self.assertEqual(
            [c["id"] for c in only_queued["candidates"]],
            ["fun:00e5b790:Move"], only_queued)
        bad = registry.dispatch("target_select", {"status": "done"})
        self.assertEqual(bad["status"], "error", bad)
        self.assertEqual(bad["code"], "invalid_params", bad)

    def test_target_select_slim_bounded_truncated(self):
        slim_keys = {"id", "kind", "va", "name", "subsystem", "mode",
                     "stage", "status", "why_ranked"}
        full = registry.dispatch("target_select", {})
        self.assertEqual(full["status"], "ok", full)
        self.assertFalse(full["truncated"], full)
        for cand in full["candidates"]:
            self.assertEqual(set(cand.keys()), slim_keys, cand)
            self.assertIn("status-priority", cand["why_ranked"], cand)
            self.assertIn("stage", cand["why_ranked"], cand)
        bounded = registry.dispatch("target_select", {"limit": 1})
        self.assertEqual(bounded["status"], "ok", bounded)
        self.assertEqual(len(bounded["candidates"]), 1, bounded)
        self.assertEqual(bounded["count"], 1, bounded)
        self.assertTrue(bounded["truncated"], bounded)
        # Top-ranked row survives the bound (active first).
        self.assertEqual(bounded["candidates"][0]["status"], "active",
                         bounded)


class TestWiring(unittest.TestCase):
    def test_real_handlers_registered(self):
        for name in ("pipeline_state", "target_select", "kg_query",
                     "kg_neighbors", "kg_record", "queue_op"):
            self.assertIs(registry.HANDLERS[name],
                          getattr(kg_tools, name), name)
        for name in ("ghidra_decompile", "ghidra_function", "ghidra_search",
                     "ghidra_snapshot_save", "vtable_lookup",
                     "dossier_read", "dossier_regenerate"):
            self.assertIs(registry.HANDLERS[name],
                          getattr(ghidra_tools, name), name)
        from tools.mcp import asset_tools
        from tools.mcp import runtime_tools
        for name in ("asset_resolve", "asset_scan"):
            self.assertIs(registry.HANDLERS[name],
                          getattr(asset_tools, name), name)
        for name in ("trace_run", "trace_analyze", "trace_status",
                     "test_run", "status_update", "fixture_check"):
            self.assertIs(registry.HANDLERS[name],
                          getattr(runtime_tools, name), name)
        # Nothing renamed: all 21 tools real, no silent stubs.
        self.assertEqual(len(registry.tool_names()), 21)
        self.assertNotEqual(
            registry.dispatch("asset_resolve", {})["status"],
            "not_implemented")

    def test_db_path_env_override(self):
        old = os.environ.get("OPENSPORE_DB")
        try:
            os.environ["OPENSPORE_DB"] = "/tmp/abs-test.db"
            self.assertEqual(config.db_path(), "/tmp/abs-test.db")
            os.environ["OPENSPORE_DB"] = "relative-test.db"
            self.assertEqual(config.db_path(),
                             config.resolve("relative-test.db"))
        finally:
            if old is None:
                os.environ.pop("OPENSPORE_DB", None)
            else:
                os.environ["OPENSPORE_DB"] = old
        self.assertEqual(config.db_path(),
                         config.resolve("knowledgegraph", "spore.db"))


if __name__ == "__main__":
    unittest.main()
