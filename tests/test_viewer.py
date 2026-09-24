"""Focused public-contract tests for the read-only viewer."""

import hashlib
import http.client
import json
import os
import shutil
import sqlite3
import stat
import tempfile
import threading
import unittest

from tools.viewer import query
from tools.viewer import server


ROOT = query.find_repo_root()
SCHEMA = os.path.join(ROOT, "knowledgegraph", "schema.sql")
SHA = "a" * 64


class ViewerQueryContractTestCase(unittest.TestCase):
    def setUp(self):
        self.tmpdir = tempfile.mkdtemp(prefix="openspore-viewer-contract-")
        self.db = os.path.join(self.tmpdir, "viewer.db")
        self._seed_db()
        os.chmod(self.db, stat.S_IRUSR | stat.S_IRGRP | stat.S_IROTH)
        self.before = self._snapshot()
        self.server = server.make_server("127.0.0.1", 0, self.db)
        self.port = self.server.server_address[1]
        self.thread = threading.Thread(
            target=self.server.serve_forever, daemon=True)
        self.thread.start()

    def tearDown(self):
        self.server.shutdown()
        self.server.server_close()
        self.thread.join(timeout=5)
        shutil.rmtree(self.tmpdir, ignore_errors=True)

    def _seed_db(self):
        conn = sqlite3.connect(self.db)
        with open(SCHEMA, encoding="utf-8") as stream:
            conn.executescript(stream.read())
        conn.execute("PRAGMA journal_mode=DELETE")
        triage_columns = {row[1] for row in conn.execute(
            "PRAGMA table_info(triage)")}
        if "triage_status" not in triage_columns:
            conn.execute("ALTER TABLE triage ADD COLUMN triage_status TEXT")
        rows = (
            ("Package", "PKG-07-CELL-MOVEMENT", "SUPPORTED",
             {"package": "PKG-07-CELL-MOVEMENT", "readiness": "READY"}),
            ("Subsystem", "sub:movement", "VERIFIED",
             {"package": "PKG-07-CELL-MOVEMENT", "readiness": "READY"}),
            ("Function", "fun:00100000", "SUPPORTED",
             {"address": "0x00100000", "sdk_name": "MovePlayer",
              "package": "PKG-07-CELL-MOVEMENT", "readiness": "READY"}),
            ("Function", "fun:00100001", "VERIFIED",
             {"address": "0x00100001", "package": "PKG-07-CELL-MOVEMENT",
              "readiness": "NEEDS_RE"}),
            ("Function", "fun:00100002", "OBSERVED",
             {"address": "0x00100002", "package": "PKG-08-CELL-MODE",
              "readiness": "READY"}),
            ("Structure", "struct:Entity", "SUPPORTED",
             {"package": "PKG-07-CELL-MOVEMENT", "readiness": "INFERRED"}),
            ("Class", "cls:00100000", "CONFIRMED",
             {"package": "PKG-07-CELL-MOVEMENT", "readiness": "READY"}),
            ("Function", "ambiguous", "OBSERVED",
             {"package": "PKG-21-UNKNOWN-ROUTING", "readiness": "NEEDS_RE"}),
            ("Structure", "ambiguous", "SUPPORTED",
             {"package": "PKG-21-UNKNOWN-ROUTING", "readiness": "NEEDS_RE"}),
            ("Function", "pct%_literal", "UNKNOWN",
             {"package": "PKG-21-UNKNOWN-ROUTING", "readiness": "NEEDS_RE"}),
        )
        with conn:
            for label, name, evidence, attrs in rows:
                conn.execute(
                    "INSERT INTO node(label,name,attrs_json,evidence_level,"
                    "origin,binary_sha256) VALUES(?,?,?,?,?,?)",
                    (label, name, json.dumps(attrs), evidence, "manual", SHA))
            ids = {name: ident for ident, name in conn.execute(
                "SELECT id, name FROM node")}
            conn.executemany(
                "INSERT INTO triage(va,rva,ghidra_name,norm_name,subsystem,"
                "category,priority,evidence,kg_node_id,snapshot_sha256,"
                "triage_status) VALUES(?,?,?,?,?,?,?,?,?,?,?)",
                (("00100000", "00010000", "MovePlayer", "MovePlayer",
                  "movement", "GAMEPLAY_LOGIC", "P1", "SUPPORTED",
                  "fun:00100000", SHA, "READY"),
                 ("00100001", "00010001", "Read", "Read", "movement",
                  "GAMEPLAY_LOGIC", "P1", "VERIFIED", "fun:00100001", SHA,
                  "NEEDS_RE"),
                 ("00100002", "00010002", "Mode", "Mode", "mode",
                  "GAMEPLAY_LOGIC", "P1", "OBSERVED", "fun:00100002", SHA,
                  "READY")))
            conn.executemany(
                "INSERT INTO edge(src,dst,rel) VALUES(?,?,?)",
                ((ids["fun:00100000"], ids["fun:00100001"], "calls"),
                 (ids["fun:00100001"], ids["fun:00100002"], "calls"),
                 (ids["fun:00100002"], ids["struct:Entity"], "documents-by"),
                 (ids["fun:00100000"], ids["cls:00100000"], "usedBy")))
            conn.execute(
                "INSERT INTO field(struct_id,offset,role,offset_evidence,"
                "meaning_evidence) VALUES(?,?,?,?,?)",
                (ids["struct:Entity"], "0x4c", "position", "OBSERVED",
                 "INFERRED"))
            conn.execute(
                "INSERT INTO test_result(name,stage,pass) VALUES(?,?,?)",
                ("viewer_test", "cell", 1))
            conn.execute(
                "INSERT INTO trace_run(binary_sha256,outcome,events_total) "
                "VALUES(?,?,?)", (SHA, "ok", 7))
            conn.executemany(
                "INSERT INTO investigations(id,kind,va,name,subsystem,mode,"
                "why_interesting,stage,status,triage_status,binary_sha256) "
                "VALUES(?,?,?,?,?,?,?,?,?,?,?)",
                (("fun:00100000:Move", "function", "00100000", "Move",
                  "movement", "replace", "movement", "queued", "queued",
                  "implemented", SHA),
                 ("fun:00100001:Read", "function", "00100001", "Read",
                  "movement", "replace", "movement", "active", "active",
                  "candidate", SHA),
                 ("sub:movement:understand", "subsystem", None, "sub:movement",
                  "movement", "understand", "movement", "done", "done",
                  "implemented", SHA)))
        conn.close()

    def _snapshot(self):
        with open(self.db, "rb") as stream:
            digest = hashlib.sha256(stream.read()).hexdigest()
        return (digest, os.stat(self.db).st_mtime,
                sorted(name for name in os.listdir(self.tmpdir)
                       if name.startswith("viewer.db")))

    def _get(self, path):
        connection = http.client.HTTPConnection(
            "127.0.0.1", self.port, timeout=10)
        connection.request("GET", path)
        response = connection.getresponse()
        body = response.read()
        connection.close()
        return response.status, json.loads(body)

    def test_search_is_filtered_paginated_and_escaped(self):
        result = query.search(q="001000", label="Function", limit=2,
                              offset=0, db=self.db)
        self.assertEqual(result["status"], "ok")
        self.assertEqual(result["total"], 3)
        self.assertEqual(len(result["results"]), 2)
        self.assertTrue(all(node["label"] == "Function"
                            for node in result["results"]))
        self.assertTrue(all("001000" in node["name"]
                            for node in result["results"]))

        second = query.search(q="001000", label="Function", limit=2,
                              offset=2, db=self.db)
        self.assertEqual(second["status"], "ok")
        self.assertEqual(len(second["results"]), 1)
        self.assertFalse({node["id"] for node in result["results"]} &
                         {node["id"] for node in second["results"]})

        wildcard = query.search(q="%_", db=self.db)
        self.assertEqual(wildcard["status"], "ok")
        self.assertEqual([node["name"] for node in wildcard["results"]],
                         ["pct%_literal"])
        self.assertEqual(query.search(q="", db=self.db)["code"],
                         "invalid_params")

    def test_node_lookup_supports_names_ids_and_ambiguity(self):
        by_name = query.node_detail("fun:00100000", self.db)
        self.assertEqual(by_name["status"], "ok")
        self.assertEqual(by_name["node"]["name"], "fun:00100000")
        self.assertEqual(by_name["node"]["attrs"]["sdk_name"], "MovePlayer")
        self.assertEqual([item["id"] for item in by_name["investigations"]],
                         ["fun:00100000:Move"])

        by_id = query.node_detail(str(by_name["node"]["id"]), self.db)
        self.assertEqual(by_id["status"], "ok")
        self.assertEqual(by_id["node"]["id"], by_name["node"]["id"])

        ambiguous = query.node_detail("ambiguous", self.db)
        self.assertEqual(ambiguous["status"], "error")
        self.assertEqual(ambiguous["code"], "ambiguous")
        self.assertEqual(set(ambiguous["labels"]), {"Function", "Structure"})

        missing = query.node_detail("", self.db)
        self.assertEqual(missing["status"], "error")
        self.assertIn(missing["code"], {"missing_param", "invalid_params", "not_found"})

    def test_neighbors_are_depth_bounded_and_include_only_reachable_rows(self):
        first = query.node_neighbors("fun:00100000", depth=1, db=self.db)
        self.assertEqual(first["status"], "ok")
        self.assertEqual({node["name"] for node in first["nodes"]},
                         {"fun:00100000", "fun:00100001", "cls:00100000"})
        self.assertEqual(len(first["edges"]), 2)

        second = query.node_neighbors("fun:00100000", depth=2, db=self.db)
        self.assertEqual(second["status"], "ok")
        self.assertIn("fun:00100002", {node["name"] for node in second["nodes"]})
        self.assertNotIn("struct:Entity", {node["name"] for node in second["nodes"]})
        self.assertGreater(len(second["edges"]), len(first["edges"]))

    def test_aggregation_endpoints_are_consistent_and_empty_safe(self):
        summary = query.summary(self.db)
        self.assertEqual(summary["status"], "ok")
        self.assertEqual(summary["counts"], {
            "node": 10, "edge": 4, "test_result": 1,
            "field": 1, "trace_run": 1, "investigations": 3,
        })
        self.assertEqual(summary["distinct_builds"], 1)

        evidence = query.evidence_distribution(self.db)
        self.assertEqual(list(evidence["dist"]), list(query.EV_ORDER))
        self.assertEqual(evidence["dist"]["SUPPORTED"], 4)
        self.assertEqual(evidence["dist"]["VERIFIED"], 2)
        self.assertEqual(evidence["total"], 10)

        labels = query.node_label_distribution(self.db)
        self.assertEqual(labels["dist"], {
            "Function": 5, "Structure": 2, "Package": 1,
            "Subsystem": 1, "Class": 1,
        })
        self.assertEqual(labels["total"], 10)

        status = query.investigation_status_distribution(self.db)
        self.assertEqual(status["status_counts"], {"active": 1, "done": 1, "queued": 1})
        self.assertEqual(status["total"], 3)

        subsystems = query.subsystem_summary(self.db)
        self.assertEqual(len(subsystems["subsystems"]), 1)
        self.assertEqual(subsystems["subsystems"][0]["investigations"], 3)
        self.assertEqual(subsystems["subsystems"][0]["investigations_by_status"],
                         {"active": 1, "done": 1, "queued": 1})

        self.assertEqual(query.nodes(q="not-present", db=self.db)["nodes"], [])
        self.assertEqual(query.search(q="not-present", db=self.db)["results"], [])
        self.assertEqual(query.packages(q="not-present", db=self.db)["packages"], [])
        self.assertEqual(query.investigations_by_keys(["not-present"], self.db)[
            "investigations"], [])

    def test_package_evidence_and_readiness_filters_are_applied(self):
        package = query.packages(q="PKG-07", db=self.db)
        self.assertEqual(package["status"], "ok")
        self.assertEqual(package["total"], 1)
        self.assertEqual([node["name"] for node in package["packages"]],
                         ["PKG-07-CELL-MOVEMENT"])

        evidence = query.nodes(evidence="SUPPORTED", db=self.db)
        self.assertEqual(evidence["status"], "ok")
        self.assertGreater(evidence["total"], 0)
        self.assertTrue(all(node["evidence_level"] == "SUPPORTED"
                            for node in evidence["nodes"]))

        readiness = query.nodes(readiness="implemented", db=self.db)
        self.assertEqual(readiness["status"], "ok")
        self.assertEqual(readiness["nodes"], [])
        canonical = query.functions(readiness="READY", limit=5,
                                    db=os.path.join(ROOT, "knowledgegraph",
                                                    "spore.db"))
        self.assertEqual(canonical["status"], "ok")
        self.assertTrue(canonical["functions"])
        self.assertTrue(all(item["readiness"] == "READY"
                            for item in canonical["functions"]))
        self.assertEqual(canonical["inventory"]["total"], 58757)
        readiness_distribution = query.readiness_distribution(db=self.db)
        self.assertTrue(readiness_distribution["available"])
        self.assertEqual({item["status"] for item in
                          readiness_distribution["readiness_counts"]},
                         {"READY", "READY_WITH_LOCAL_CONTEXT", "DEPENDENCY_FIRST",
                          "ENGINE_BOUNDARY", "NEEDS_RE", "LIKELY_INFRASTRUCTURE"})
        self.assertEqual(sum(item["count"] for item in
                             readiness_distribution["readiness_counts"]), 368)

    def test_explicit_graph_limit_reports_truncation(self):
        data = query.node_neighbors("fun:00100000", depth=2, limit=1,
                                    edge_limit=1, db=self.db)
        self.assertEqual(data["status"], "ok")
        self.assertEqual(data["limit"], 1)
        self.assertEqual(data["edge_limit"], 1)
        self.assertTrue(data["truncated"])
        self.assertLessEqual(len(data["nodes"]), 1)
        self.assertLessEqual(len(data["edges"]), 1)

        invalid = query.node_neighbors("fun:00100000", depth=2, limit=0,
                                       db=self.db)
        self.assertEqual(invalid["code"], "invalid_params")
        invalid_edges = query.node_neighbors(
            "fun:00100000", depth=2, edge_limit=-1, db=self.db)
        self.assertEqual(invalid_edges["code"], "invalid_params")

    def test_malformed_missing_and_unknown_ids_stay_structured(self):
        malformed = query.node_neighbors("fun:00100000", depth=0,
                                         db=self.db)
        self.assertEqual(malformed["code"], "invalid_params")
        malformed = query.node_neighbors("fun:00100000", depth="bad",
                                         db=self.db)
        self.assertEqual(malformed["code"], "invalid_params")

        missing = query.node_detail("", self.db)
        self.assertEqual(missing["status"], "error")
        self.assertIn(missing["code"], {"missing_param", "invalid_params", "not_found"})

        unknown = query.node_detail("fun:deadbeef", self.db)
        self.assertEqual(unknown["code"], "not_found")
        unknown_va = query.node_detail("0xdeadbeef", self.db)
        self.assertEqual(unknown_va["code"], "not_found")
        unknown_neighbors = query.node_neighbors("0xdeadbeef", db=self.db)
        self.assertEqual(unknown_neighbors["code"], "not_found")

    def test_read_only_queries_and_server_crawl_do_not_mutate_db(self):
        results = (
            query.summary(self.db),
            query.evidence_distribution(self.db),
            query.node_label_distribution(self.db),
            query.investigation_status_distribution(self.db),
            query.subsystem_summary(self.db),
            query.search(q="PKG-07", db=self.db),
            query.nodes(evidence="SUPPORTED", db=self.db),
            query.functions(readiness="READY", limit=2,
                            db=os.path.join(ROOT, "knowledgegraph", "spore.db")),
            query.packages(q="PKG-07", db=self.db),
            query.readiness_distribution(db=self.db),
            query.node_detail("fun:00100000", self.db),
            query.node_neighbors("fun:00100000", depth=2, limit=2,
                                 edge_limit=2, db=self.db),
            query.investigations_list(kind="function", db=self.db),
            query.investigations_by_keys(["00100000", "Move"], self.db),
        )
        for result in results:
            self.assertEqual(result["status"], "ok")

        paths = (
            "/api/summary", "/api/evidence", "/api/labels",
            "/api/investigations", "/api/investigation-list",
            "/api/subsystems", "/api/nodes", "/api/nodes?q=001000",
            "/api/node/fun:00100000",
            "/api/node/fun:00100000/neighbors?depth=2",
        )
        for path in paths:
            response_status, data = self._get(path)
            self.assertEqual(response_status, 200, path)
            self.assertIn(data["status"], {"ok", "degraded", "error"}, path)

        self.assertEqual(self._snapshot(), self.before)
        write_connection = sqlite3.connect(self.db)
        with self.assertRaises(sqlite3.OperationalError):
            write_connection.execute("DELETE FROM node")
        write_connection.close()


if __name__ == "__main__":
    unittest.main()
