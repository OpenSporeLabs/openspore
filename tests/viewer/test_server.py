"""Viewer web-server tests (stdlib only).

Builds a temp SQLite DB from knowledgegraph/schema.sql (synthetic rows
across all six tables) via the OPENSPORE_DB override, starts the viewer on
an ephemeral loopback port, then asserts: every API route answers with a
valid JSON envelope; the committed knowledgegraph/spore.db is bit-identical
(sha256 + mtime, no new -wal/-shm) across a full crawl; a missing DB degrades
to a structured banner instead of a 500; unknown paths 404 with the server
alive; and non-loopback binds are refused.

Run from the repo root:
    python3 -m unittest discover -s tests -t .
"""
import hashlib
import http.client
import json
import os
import shutil
import sqlite3
import tempfile
import threading
import unittest

from tools.viewer import server
from tools.viewer import query

SHA_A = "a" * 64
SHA_B = "b" * 64

COMMITTED_DB = os.path.join(query.find_repo_root(),
                            "knowledgegraph", "spore.db")


def _sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(65536), b""):
            digest.update(chunk)
    return digest.hexdigest()


def _side_files():
    """Names of spore.db + WAL side-files present in knowledgegraph/."""
    root = os.path.dirname(COMMITTED_DB)
    return sorted(n for n in os.listdir(root) if n.startswith("spore.db"))


class ViewerServerTestCase(unittest.TestCase):
    def setUp(self):
        self._old_db = os.environ.get("OPENSPORE_DB")
        self.tmpdir = tempfile.mkdtemp(prefix="openspore-viewer-test-")
        self.db = os.path.join(self.tmpdir, "viewer.db")
        os.environ["OPENSPORE_DB"] = self.db
        schema = os.path.join(query.find_repo_root(), "knowledgegraph",
                              "schema.sql")
        with open(schema) as fh:
            sql = fh.read()
        conn = sqlite3.connect(self.db)
        conn.executescript(sql)
        with conn:
            nodes = [
                ("Subsystem", "sub:resource", "VERIFIED", SHA_A,
                 json.dumps({"gate": "g1"})),
                ("Function", "fun:00e5b790", "OBSERVED", SHA_A,
                 json.dumps({"address": "0x00e5b790",
                             "sdk_name": "MovePlayerToMousePosition"})),
                ("Class", "cls:00e5b790", "CONFIRMED", SHA_A, "{}"),
                ("Structure", "struct:PlayerEntity", "SUPPORTED", SHA_A,
                 json.dumps({"src": "tools/observatory/probes/dossier.json"})),
                ("Function", "pct%_weird", "UNKNOWN", SHA_B, "{}"),
            ]
            for label, name, ev, sha, attrs in nodes:
                conn.execute(
                    "INSERT INTO node(label,name,attrs_json,evidence_level,"
                    "origin,binary_sha256) VALUES(?,?,?,?,?,?)",
                    (label, name, attrs, ev, "manual", sha))
            idmap = {r[1]: r[0]
                     for r in conn.execute("SELECT id, name FROM node")}
            conn.execute("INSERT INTO edge(src,dst,rel) VALUES(?,?,?)",
                         (idmap["fun:00e5b790"], idmap["cls:00e5b790"],
                          "calls"))
            conn.execute("INSERT INTO edge(src,dst,rel) VALUES(?,?,?)",
                         (idmap["cls:00e5b790"],
                          idmap["struct:PlayerEntity"], "documents-by"))
            conn.execute(
                "INSERT INTO test_result(name,stage,pass) VALUES(?,?,?)",
                ("seed_test", "cell", 1))
            conn.execute(
                "INSERT INTO field(struct_id,offset,role,offset_evidence,"
                "meaning_evidence) VALUES(?,?,?,?,?)",
                (idmap["struct:PlayerEntity"], "0x4C", "cellPos",
                 "OBSERVED", "OBSERVED"))
            conn.execute(
                "INSERT INTO trace_run(binary_sha256,outcome,events_total)"
                " VALUES(?,?,?)", (SHA_A, "ok", 42))
            for inv in (
                    ("fun:00e5b790:Move", "function", "00e5b790", "Move",
                     None, "replace", "fixture", "QUEUED", "queued",
                     '["gate"]', '["dossier"]'),
                    ("sub:resource:understand", "subsystem", None, None,
                     "resource", "understand", "fixture", "RECORDED",
                     "done", None, None)):
                conn.execute(
                    "INSERT INTO investigations(id,kind,va,name,subsystem,"
                    "mode,why_interesting,stage,status,prerequisites,"
                    "evidence_refs,binary_sha256)"
                    " VALUES(?,?,?,?,?,?,?,?,?,?,?,?)",
                    inv + (SHA_A,))
        conn.close()

        # Baseline of the committed DB before any crawl.
        self._committed_before = None
        if os.path.isfile(COMMITTED_DB):
            self._committed_before = (
                _sha256(COMMITTED_DB), os.stat(COMMITTED_DB).st_mtime,
                _side_files())

        self.port = None
        self._start_server()

    def _start_server(self, db_arg=None):
        srv = server.make_server("127.0.0.1", 0, db_arg=db_arg)
        self.port = srv.server_address[1]
        self._thread = threading.Thread(target=srv.serve_forever,
                                        daemon=True)
        self._thread.start()
        self._server = srv

    def tearDown(self):
        if getattr(self, "_server", None) is not None:
            self._server.shutdown()
            self._server.server_close()
        if self._old_db is None:
            os.environ.pop("OPENSPORE_DB", None)
        else:
            os.environ["OPENSPORE_DB"] = self._old_db
        shutil.rmtree(self.tmpdir, ignore_errors=True)

    def get(self, path):
        conn = http.client.HTTPConnection("127.0.0.1", self.port, timeout=10)
        conn.request("GET", path)
        resp = conn.getresponse()
        body = resp.read()
        conn.close()
        try:
            data = json.loads(body)
        except ValueError:
            data = None  # non-JSON body (static assets)
        return resp.status, data, body

    # -- route crawl ------------------------------------------------------ #
    ROUTES = ["/", "/static/viewer.js", "/static/viewer.css",
              "/api/summary", "/api/evidence", "/api/labels",
              "/api/investigations",
              "/api/investigation-list",
              "/api/investigation-list?kind=function&q=Move&limit=5&offset=0",
              "/api/investigation-list?status=queued",
              "/api/investigation-list?keys=00e5b790,Move",
              "/api/subsystems",
              "/api/nodes",
              "/api/nodes?label=Function&q=00e5b790&limit=5&offset=0",
              "/api/nodes?q=pct",
              "/api/node/fun:00e5b790",
              "/api/node/fun:00e5b790/neighbors",
              "/api/node/fun:00e5b790/neighbors?depth=2",
              "/api/investigation/fun:00e5b790:Move"]

    def test_all_routes_answer_with_envelope(self):
        for path in self.ROUTES:
            code, data, body = self.get(path)
            self.assertEqual(code, 200, path)
            if path.startswith("/api/"):
                self.assertIsInstance(data, dict, path)
                self.assertIn(data["status"], ("ok", "degraded"), path)
            else:  # static assets: non-JSON, non-empty
                self.assertTrue(body, path)

    def test_summary_counts(self):
        code, data, _ = self.get("/api/summary")
        self.assertEqual(code, 200)
        self.assertEqual(data["status"], "ok")
        self.assertEqual(data["counts"],
                         {"node": 5, "edge": 2, "test_result": 1,
                          "field": 1, "trace_run": 1,
                          "investigations": 2})
        self.assertEqual(data["distinct_builds"], 2)

    def test_evidence_order_and_counts(self):
        code, data, _ = self.get("/api/evidence")
        self.assertEqual(code, 200)
        dist = data["dist"]
        self.assertEqual(list(dist), list(query.EV_ORDER))
        self.assertEqual(dist["OBSERVED"], 1)
        self.assertEqual(dist["CONFIRMED"], 1)
        self.assertEqual(dist["VERIFIED"], 1)
        self.assertEqual(dist["SUPPORTED"], 1)
        self.assertEqual(dist["UNKNOWN"], 1)

    def test_investigation_status_distribution(self):
        # Envelope keys must not collide with the "status" field: the
        # distribution lives under status_counts/stage_counts.
        code, data, _ = self.get("/api/investigations")
        self.assertEqual(code, 200)
        self.assertEqual(data["status"], "ok")
        self.assertEqual(data["status_counts"], {"done": 1, "queued": 1})
        self.assertEqual(data["stage_counts"], {"QUEUED": 1,
                                                "RECORDED": 1})
        self.assertEqual(data["total"], 2)

    def test_investigation_list(self):
        code, data, _ = self.get("/api/investigation-list?limit=10")
        self.assertEqual(code, 200)
        self.assertEqual(data["status"], "ok")
        self.assertEqual(data["total"], 2)
        self.assertEqual(len(data["investigations"]), 2)
        code, data, _ = self.get("/api/investigation-list?kind=function")
        self.assertEqual(data["total"], 1)
        self.assertEqual(data["investigations"][0]["id"],
                         "fun:00e5b790:Move")
        code, data, _ = self.get("/api/investigation-list?q=Move")
        self.assertEqual(data["total"], 1)
        code, data, _ = self.get("/api/investigation-list?status=done")
        self.assertEqual(data["total"], 1)
        code, data, _ = self.get("/api/investigation-list?limit=0")
        self.assertEqual(code, 400)
        self.assertEqual(data["code"], "invalid_params")

    def test_investigation_list_keys_join(self):
        # Bounded exact-match join: matches va and name, nothing else.
        code, data, _ = self.get(
            "/api/investigation-list?keys=00e5b790,Move")
        self.assertEqual(code, 200)
        self.assertEqual(data["total"], 1)
        self.assertEqual(data["investigations"][0]["id"],
                         "fun:00e5b790:Move")
        code, data, _ = self.get("/api/investigation-list?keys=00000000")
        self.assertEqual(data["total"], 0)
        self.assertEqual(data["investigations"], [])
        code, data, _ = self.get("/api/investigation-list?keys=")
        self.assertEqual(data["total"], 0)

    def test_node_detail_and_neighbors(self):
        code, data, _ = self.get("/api/node/fun:00e5b790")
        self.assertEqual(code, 200)
        node = data["node"]
        self.assertEqual(node["evidence_level"], "OBSERVED")
        self.assertEqual(node["attrs"]["sdk_name"],
                         "MovePlayerToMousePosition")
        self.assertEqual(
            [i["id"] for i in data["investigations"]],
            ["fun:00e5b790:Move"])

        code, data, _ = self.get("/api/node/struct:PlayerEntity")
        self.assertEqual([f["role"] for f in data["fields"]], ["cellPos"])
        self.assertEqual(data["provenance"]["src_ref"],
                         "tools/observatory/probes/dossier.json")

        code, data, _ = self.get("/api/node/fun:00e5b790/neighbors")
        names = {n["name"] for n in data["nodes"]}
        self.assertEqual(names, {"fun:00e5b790", "cls:00e5b790"})
        code, data, _ = self.get("/api/node/fun:00e5b790/neighbors?depth=2")
        names = {n["name"] for n in data["nodes"]}
        self.assertIn("struct:PlayerEntity", names)

        code, data, _ = self.get("/api/node/ghost-node")
        self.assertEqual(code, 404)
        self.assertEqual(data["code"], "not_found")

    def test_investigation_detail_parsed(self):
        code, data, _ = self.get("/api/investigation/fun:00e5b790:Move")
        self.assertEqual(code, 200)
        inv = data["investigation"]
        self.assertEqual(inv["status"], "queued")
        self.assertEqual(inv["prerequisites"], ["gate"])
        self.assertEqual(inv["evidence_refs"], ["dossier"])

    # -- safety pins ------------------------------------------------------- #
    def test_committed_db_untouched_after_full_crawl(self):
        if self._committed_before is None:
            self.skipTest("committed spore.db not present")
        for path in self.ROUTES:
            self.get(path)
        self.get("/api/nodes?q=&limit=1000")
        after = (_sha256(COMMITTED_DB),
                 os.stat(COMMITTED_DB).st_mtime, _side_files())
        self.assertEqual(after[0], self._committed_before[0])
        self.assertEqual(after[1], self._committed_before[1])
        self.assertEqual(after[2], self._committed_before[2])

    def test_missing_db_degrades_not_500(self):
        missing = os.path.join(self.tmpdir, "does-not-exist.db")
        self._server.shutdown()
        self._server.server_close()
        self._start_server(db_arg=missing)
        code, data, _ = self.get("/api/summary")
        self.assertEqual(code, 200)
        self.assertEqual(data["status"], "degraded")
        self.assertEqual(data["code"], "db_missing")
        code, data, _ = self.get("/api/labels")
        self.assertEqual(code, 200)
        self.assertEqual(data["status"], "degraded")

    def test_unknown_path_404_and_alive(self):
        code, data, _ = self.get("/nope/nothing")
        self.assertEqual(code, 404)
        self.assertEqual(data["status"], "error")
        self.assertEqual(data["code"], 404)
        code, _, _ = self.get("/api/summary")
        self.assertEqual(code, 200)

    def test_static_traversal_refused(self):
        code, data, _ = self.get("/static/../query.py")
        self.assertEqual(code, 404)
        self.assertEqual(data["code"], 404)

    def test_non_loopback_bind_refused(self):
        ok, msg = server.validate_bind("127.0.0.1")
        self.assertTrue(ok)
        ok, msg = server.validate_bind("::1")
        self.assertTrue(ok)
        ok, msg = server.validate_bind("0.0.0.0")
        self.assertFalse(ok)
        self.assertIn("loopback", msg)
        with self.assertRaises(SystemExit):
            server.make_server("0.0.0.0", 0)


if __name__ == "__main__":
    unittest.main()
