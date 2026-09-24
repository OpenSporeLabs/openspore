"""KG schema tests: fresh DDL, legacy migration, idempotency, CHECK (S1).

Covers the schema patch from docs/RE-AUTOMATION-ARCHITECTURE.md §5/§6 and
docs/analysis/SCHEMA-DELTA.md:
  - fresh DB from schema.sql has every table/column/index, user_version=4
  - migration from the pre-patch 41-line schema leaves legacy rows intact
    (byte-for-byte on the original columns) and adds the new columns with
    correct defaults, including legacy 5-level confidence values
  - running _migrate twice is a no-op (full dump identical)
  - one record round-trips in each new table
  - the 7-level evidence CHECK rejects invalid values

Uses temp DBs only; the live knowledgegraph/spore.db is never touched.

Run from the repo root:
    python3 -m unittest discover -s tests -t . -v
"""
import os
import sqlite3
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "knowledgegraph"))

import knowledgegraph.kg as kg

OLD_SCHEMA = """
PRAGMA journal_mode = WAL;

CREATE TABLE IF NOT EXISTS node (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    label       TEXT NOT NULL,
    name        TEXT NOT NULL,
    attrs_json  TEXT NOT NULL DEFAULT '{}',
    confidence  REAL NOT NULL DEFAULT 0.0,
    origin      TEXT NOT NULL DEFAULT 'unknown',
    note        TEXT,
    created_at  TEXT NOT NULL DEFAULT (datetime('now')),
    UNIQUE (label, name)
);

CREATE TABLE IF NOT EXISTS edge (
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    src   INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE,
    dst   INTEGER NOT NULL REFERENCES node(id) ON DELETE CASCADE,
    rel   TEXT NOT NULL,
    UNIQUE (src, dst, rel)
);

CREATE TABLE IF NOT EXISTS test_result (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    name       TEXT NOT NULL,
    stage      TEXT,
    seed       TEXT,
    expected   TEXT,
    actual     TEXT,
    pass       INTEGER,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_node_label ON node(label);
CREATE INDEX IF NOT EXISTS idx_edge_src   ON edge(src);
CREATE INDEX IF NOT EXISTS idx_edge_dst   ON edge(dst);
"""

OLD_NODE_COLS = ["id", "label", "name", "attrs_json", "confidence",
                 "origin", "note", "created_at"]
LEGACY_ROWS = [
    ("Structure", "Creature", '{"hp":30}', 0.75, "sdk", "legacy struct"),
    ("Function", "App::cAppSystem::Init", "{}", 0.25, "sdk", None),
    ("Class", "cCellModeStrategy", "{}", 0.5, "sdk", None),
    ("Observation", "obs:boot:menu", "{}", 0.9, "dynamic", "neg trace"),
    ("Subsystem", "cell-movement", "{}", 1.0, "manual", None),
]
NEW_NODE_COLS = ["id", "label", "name", "attrs_json", "confidence", "origin",
                 "note", "created_at", "evidence_level", "updated_at",
                 "binary_sha256"]
FIELD_COLS = ["id", "struct_id", "offset", "role", "offset_evidence",
              "meaning_evidence", "value", "source", "binary_sha256",
              "created_at", "updated_at"]
TRACE_COLS = ["id", "binary_sha256", "probes_sha256", "wine_version",
              "display_env", "xdotool", "captured_at", "events_total",
              "jsonl_path", "screenshots_count", "screenshots_first",
              "screenshots_last", "screenshots_manifest_path", "outcome",
              "replayable"]
INV_COLS = ["id", "kind", "va", "name", "subsystem", "mode",
            "why_interesting", "stage", "status", "block_reason",
            "prerequisites", "attempts", "checkpoint", "evidence_refs",
            "implementer_id", "adjudicator_id", "created_at", "updated_at",
            "binary_sha256", "triage_status"]
XREF_COLS = ["caller_va", "callee_va", "reference_type", "callsite_va",
             "source", "snapshot_sha256"]
EXPECTED_INDEXES = {"idx_node_label", "idx_edge_src", "idx_edge_dst",
                    "idx_node_name", "idx_node_evidence", "idx_inv_status",
                    "ix_inv_dedup", "idx_field_struct", "idx_trace_run_sha",
                    "idx_triage_prio_cat", "idx_triage_sub_prio",
                    "idx_inv_triage_status", "idx_xref_caller",
                    "idx_xref_callee"}


def full_dump(c):
    out = {"user_version": c.execute("PRAGMA user_version").fetchone()[0]}
    tables = [r[0] for r in c.execute(
        "SELECT name FROM sqlite_master WHERE type='table' "
        "AND name NOT LIKE 'sqlite_%' ORDER BY name")]
    for t in tables:
        cols = [r[1] for r in c.execute(f"PRAGMA table_info({t})")]
        order = "ORDER BY id" if "id" in cols else f"ORDER BY {cols[0]}"
        out[t] = [tuple(r) for r in
                  c.execute(f"SELECT * FROM {t} {order}")]
    out["ddl"] = [tuple(r) for r in c.execute(
        "SELECT type, name, sql FROM sqlite_master "
        "WHERE sql IS NOT NULL ORDER BY type, name")]
    return out


class KGSchemeTest(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory(prefix="kg-schema-")
        self.db = os.path.join(self._tmp.name, "test.db")
        self._orig_db = kg.DB
        kg.DB = self.db

    def tearDown(self):
        kg.DB = self._orig_db
        self._tmp.cleanup()

    def connect(self):
        return sqlite3.connect(self.db)

    def cols(self, c, table):
        return [r[1] for r in c.execute(f"PRAGMA table_info({table})")]

    def test_fresh_schema(self):
        with open(os.path.join(kg.HERE, "schema.sql")) as f:
            c = self.connect()
            c.executescript(f.read())
            kg._migrate(c)
            tables = {r[0] for r in c.execute(
                "SELECT name FROM sqlite_master WHERE type='table' "
                "AND name NOT LIKE 'sqlite_%'")}
            self.assertEqual(
                tables, {"node", "edge", "test_result", "field",
                         "trace_run", "investigations", "triage", "xref"})
            self.assertEqual(c.execute("PRAGMA user_version").fetchone()[0], 4)
            self.assertEqual(self.cols(c, "node"), NEW_NODE_COLS)
            self.assertEqual(self.cols(c, "field"), FIELD_COLS)
            self.assertEqual(self.cols(c, "trace_run"), TRACE_COLS)
            self.assertEqual(self.cols(c, "investigations"), INV_COLS)
            self.assertEqual(self.cols(c, "xref"), XREF_COLS)
            idx = {r[0] for r in c.execute(
                "SELECT name FROM sqlite_master WHERE type='index' "
                "AND name NOT LIKE 'sqlite_%'")}
            self.assertEqual(idx, EXPECTED_INDEXES)
            c.close()

    def test_migrate_from_old_schema(self):
        c = self.connect()
        c.executescript(OLD_SCHEMA)
        c.executemany(
            "INSERT INTO node(label,name,attrs_json,confidence,origin,note) "
            "VALUES(?,?,?,?,?,?)", LEGACY_ROWS)
        c.execute(
            "INSERT INTO node(label,name,attrs_json,confidence,origin,note,"
            "created_at) VALUES('Test','cell_tick','{}',0.5,'manual',NULL,"
            "'2026-01-01 00:00:00')")
        c.execute("INSERT INTO edge(src,dst,rel) VALUES(1,2,'calls')")
        c.execute("INSERT INTO test_result(name,stage,seed,expected,actual,"
                  "pass) VALUES('cell_tick','cell','12345','A','A',1)")
        c.commit()
        before = {"node": [tuple(r) for r in c.execute(
            "SELECT " + ",".join(OLD_NODE_COLS) + " FROM node ORDER BY id")],
                  "edge": [tuple(r) for r in c.execute(
            "SELECT * FROM edge ORDER BY id")],
                  "test_result": [tuple(r) for r in c.execute(
            "SELECT * FROM test_result ORDER BY id")]}
        kg._migrate(c)
        c.commit()
        after = {"node": [tuple(r) for r in c.execute(
            "SELECT " + ",".join(OLD_NODE_COLS) + " FROM node ORDER BY id")],
                 "edge": [tuple(r) for r in c.execute(
            "SELECT * FROM edge ORDER BY id")],
                 "test_result": [tuple(r) for r in c.execute(
            "SELECT * FROM test_result ORDER BY id")]}
        self.assertEqual(before, after)
        self.assertEqual(self.cols(c, "node"), NEW_NODE_COLS)
        rows = c.execute("SELECT evidence_level, updated_at, binary_sha256 "
                         "FROM node ORDER BY id").fetchall()
        self.assertEqual(len(rows), len(LEGACY_ROWS) + 1)
        for ev, upd, sha in rows:
            self.assertEqual(ev, "UNKNOWN")
            self.assertTrue(upd)
            self.assertIsNone(sha)
        self.assertEqual(c.execute("PRAGMA user_version").fetchone()[0], 4)
        c.close()

    def test_migration_idempotent(self):
        c = self.connect()
        c.executescript(OLD_SCHEMA)
        c.executemany(
            "INSERT INTO node(label,name,attrs_json,confidence,origin,note) "
            "VALUES(?,?,?,?,?,?)", LEGACY_ROWS[:2])
        c.execute("INSERT INTO test_result(name,stage,seed,expected,actual,"
                  "pass) VALUES('cell_tick','cell','12345','A','A',1)")
        c.commit()
        kg._migrate(c)
        c.commit()
        first = full_dump(c)
        kg._migrate(c)
        c.commit()
        second = full_dump(c)
        self.assertEqual(first, second)
        c.close()

    def test_new_tables_roundtrip(self):
        with open(os.path.join(kg.HERE, "schema.sql")) as f:
            c = self.connect()
            c.executescript(f.read())
            kg._migrate(c)
            c.execute("INSERT INTO node(label,name,attrs_json) VALUES("
                      "'Structure','cCellModeStrategy','{}')")
            c.execute(
                "INSERT INTO field(struct_id,offset,role,offset_evidence,"
                "meaning_evidence,value,source,binary_sha256) "
                "VALUES(1,'0x4C','cellPos','VERIFIED','INFERRED',"
                "'0x1234','REPLACEMENT-ABI.md','abc123')")
            row = c.execute("SELECT struct_id,offset,role,offset_evidence,"
                            "meaning_evidence,value FROM field "
                            "WHERE struct_id=1").fetchone()
            self.assertEqual(row, (1, "0x4C", "cellPos", "VERIFIED",
                                   "INFERRED", "0x1234"))
            c.execute(
                "INSERT INTO trace_run(binary_sha256,probes_sha256,"
                "wine_version,display_env,xdotool,events_total,jsonl_path,"
                "screenshots_count,screenshots_first,screenshots_last,"
                "screenshots_manifest_path,outcome) "
                "VALUES('b2','p1','11.0',':0','1.3.1',42,'traces/run.jsonl',"
                "3,'s1.png','s3.png','manifest.json','ok')")
            row = c.execute("SELECT binary_sha256,events_total,"
                            "screenshots_count,screenshots_first,"
                            "screenshots_last,screenshots_manifest_path,"
                            "replayable FROM trace_run WHERE id=1").fetchone()
            self.assertEqual(row, ("b2", 42, 3, "s1.png", "s3.png",
                                   "manifest.json",
                                   "input-logged, stage-deterministic, "
                                   "non-bit-exact"))
            c.execute(
                "INSERT INTO investigations(id,kind,va,name,subsystem,mode,"
                "why_interesting,stage,status,block_reason,prerequisites,"
                "attempts,checkpoint,evidence_refs,implementer_id,"
                "adjudicator_id,created_at,updated_at,binary_sha256) "
                "VALUES('fn:0x00e5b790:MovePlayerToMousePosition','function',"
                "'0x00e5b790','MovePlayerToMousePosition','cell-movement',"
                "'replace','mouse steering','SELECTED','active',NULL,"
                "'[\"gate:cell\"]','{\"SELECTED\":1}','{','[\"dossier:cell-"
                "movement\"]','impl-1','adj-1','2026-01-01 00:00:00',"
                "'2026-01-01 00:00:00','b2')")
            row = c.execute("SELECT id,kind,va,mode,stage,status,"
                            "implementer_id,adjudicator_id,binary_sha256 "
                            "FROM investigations WHERE id LIKE 'fn:%'"
                            ).fetchone()
            self.assertEqual(row, ("fn:0x00e5b790:MovePlayerToMousePosition",
                                   "function", "0x00e5b790", "replace",
                                   "SELECTED", "active", "impl-1", "adj-1",
                                   "b2"))
            c.execute(
                "INSERT INTO xref(caller_va,callee_va,reference_type,"
                "callsite_va,source,snapshot_sha256) "
                "VALUES('00e5b790','00e5c0f0','direct-call','00e5b7aa',"
                "'ghidra:SporeApp.exe','2540f2ca')")
            row = c.execute("SELECT caller_va,callee_va,reference_type,"
                            "callsite_va FROM xref").fetchone()
            self.assertEqual(row, ("00e5b790", "00e5c0f0", "direct-call",
                                   "00e5b7aa"))
            with self.assertRaises(sqlite3.IntegrityError):
                c.execute(
                    "INSERT INTO xref(caller_va,callee_va,reference_type,"
                    "callsite_va,source,snapshot_sha256) "
                    "VALUES('00e5b790','00e5c0f0','BOGUS','00e5b7ab',"
                    "'ghidra:SporeApp.exe','2540f2ca')")
            c.close()

    def test_evidence_level_check(self):
        with open(os.path.join(kg.HERE, "schema.sql")) as f:
            c = self.connect()
            c.executescript(f.read())
            kg._migrate(c)
            c.execute("INSERT INTO node(label,name) VALUES("
                      "'Structure','cCellModeStrategy')")
            with self.assertRaises(sqlite3.IntegrityError):
                c.execute("INSERT INTO node(label,name,evidence_level) "
                          "VALUES('Function','fun:00001234','BOGUS')")
            with self.assertRaises(sqlite3.IntegrityError):
                c.execute("INSERT INTO field(struct_id,offset,role,"
                          "offset_evidence) VALUES(1,'0x0','x','BOGUS')")
            c.execute("INSERT INTO node(label,name,evidence_level) "
                      "VALUES('Function','fun:00005678','VERIFIED')")
            got = c.execute("SELECT evidence_level FROM node "
                            "WHERE name='fun:00005678'").fetchone()[0]
            self.assertEqual(got, "VERIFIED")
            c.close()


if __name__ == "__main__":
    unittest.main()
