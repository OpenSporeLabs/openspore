"""Canonical KG seed spine tests (knowledgegraph/seed.py,
docs/RE-AUTOMATION-ARCHITECTURE.md §5 seed-generator invariants + §6
investigation queue + S1 gate).

Pins, with semantic assertions over a temp sqlite DB (the live
knowledgegraph/spore.db is never touched):

  1.  fresh temp DB + bare-clone seed (no optional inputs) succeeds
  2.  canonical counts reproduced: 96/115/14 from seed-literals.json,
      18 Subsystem nodes, investigations per the S1 gate
      (18 subsystem rows + the one done cell row)
  3.  repeated seed -> identical logical dump (same DB; and two fresh DBs)
  4.  no duplicate (label,name) nodes / (src,dst,rel) edges
  5.  binary/source identity recorded: explicit --binary-sha256 pins every
      identity column; build-agnostic mode -> NULL node/field (doc §5:
      "binary_sha256 (NULL = build-agnostic)"), sentinel "build-agnostic"
      in the NOT NULL investigations/trace_run columns
  6.  stale-state: re-seed under a second identity PRESERVES the first
      identity's queue rows (doc §6: "binary_sha256 != current build =>
      row stale - parked queued, never dropped")
  7.  all 9 replacement statuses seed through seed.py's own mapping without
      KeyError (regression guard for the stale 7-key STATUS2EV dict)
  8.  seed_sprint.py shim forwards to seed.py and writes no divergent data
  9.  seed-literals.json integrity: counts, keys, no absolute paths,
      evidence/confidence values within the §3 scale

Stdlib unittest only; runs in a bare fresh clone (no ~/apps, no SPORE/,
no wine). Run from the repo root:
    python3 -m unittest discover -s tests -t . -v
"""
import json
import os
import re
import shutil
import sqlite3
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from io import StringIO

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
KG = os.path.join(ROOT, "knowledgegraph")
sys.path.insert(0, KG)

import scale  # noqa: E402
import seed  # noqa: E402
import seed_sprint  # noqa: E402

SHA_A = "a" * 64
SHA_B = "b" * 64
MISSING_SDK = "/nonexistent-never-present.xml"


def run_seed(db, *extra):
    """Run seed.py's main() bare-clone style: no SDK xml, committed inputs."""
    argv = ["--db", db, "--sdk-xml", MISSING_SDK] + list(extra)
    with redirect_stdout(StringIO()):
        seed.main(argv)


def logical_dump(path):
    """Full logical state of all 7 tables.

    Excludes id / created_at / updated_at / classified_at / captured_at
    (wall-clock, non-logical); edges and field rows are resolved to node names
    so row ids never leak in.
    """
    c = sqlite3.connect(path)
    out = {}
    for t in ("node", "edge", "test_result", "field", "trace_run",
              "investigations", "triage"):
        cols = [r[1] for r in c.execute(f"PRAGMA table_info({t})")]
        keep = [x for x in cols if x not in ("id", "created_at",
                                             "updated_at", "classified_at",
                                             "captured_at")]
        if t == "node":
            rows = c.execute(
                f"SELECT {', '.join(keep)} FROM node "
                "ORDER BY label, name").fetchall()
        elif t == "edge":
            rows = c.execute(
                "SELECT n1.label, n1.name, e.rel, n2.label, n2.name "
                "FROM edge e "
                "JOIN node n1 ON n1.id = e.src "
                "JOIN node n2 ON n2.id = e.dst "
                "ORDER BY n1.label, n1.name, e.rel, n2.label, n2.name"
            ).fetchall()
        elif t == "test_result":
            rows = c.execute(
                f"SELECT {', '.join(keep)} FROM test_result ORDER BY name"
            ).fetchall()
        elif t == "field":
            sel = ["n.label" if x == "struct_id" else f"f.{x}"
                   for x in keep]
            rows = c.execute(
                f"SELECT {', '.join(sel)} FROM field f "
                "JOIN node n ON n.id = f.struct_id "
                "ORDER BY n.label, n.name, f.offset").fetchall()
        elif t == "trace_run":
            rows = c.execute(
                f"SELECT {', '.join(keep)} FROM trace_run "
                "ORDER BY binary_sha256, jsonl_path, probes_sha256"
            ).fetchall()
        elif t == "triage":
            rows = c.execute(
                f"SELECT {', '.join(keep)} FROM triage ORDER BY va"
            ).fetchall()
        else:  # investigations
            rows = c.execute(
                f"SELECT {', '.join(keep)} FROM investigations ORDER BY id"
            ).fetchall()
        out[t] = rows
    c.close()
    return out


class SeedSpineTest(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory(prefix="kg-seed-")
        self.dir = self._tmp.name
        self.db = os.path.join(self.dir, "seed.db")

    def tearDown(self):
        self._tmp.cleanup()

    # -- 1. fresh KG + canonical seed succeeds ---------------------------- #
    def test_bare_clone_seed_succeeds(self):
        run_seed(self.db, "--build-agnostic")
        self.assertTrue(os.path.exists(self.db))
        c = sqlite3.connect(self.db)
        tables = {r[0] for r in c.execute(
            "SELECT name FROM sqlite_master WHERE type='table' "
            "AND name NOT LIKE 'sqlite_%'")}
        self.assertEqual(tables, {"node", "edge", "test_result", "field",
                                  "trace_run", "investigations", "triage",
                                  "xref"})
        for t in ("node", "edge", "test_result", "investigations"):
            self.assertGreater(
                c.execute(f"SELECT COUNT(*) FROM {t}").fetchone()[0], 0,
                f"{t} must be non-empty after the canonical seed")
        c.close()

    # -- 2. canonical counts reproduced ----------------------------------- #
    def test_canonical_counts_reproduced(self):
        run_seed(self.db, "--build-agnostic")
        with open(os.path.join(KG, "seed-literals.json")) as f:
            lit = json.load(f)
        self.assertEqual(lit["counts"],
                         {"nodes": 96, "edges": 115, "test_rows": 14})
        self.assertEqual((len(lit["nodes"]), len(lit["edges"]),
                          len(lit["test_rows"])), (96, 115, 14))

        c = sqlite3.connect(self.db)
        missing = [(n["label"], n["name"])
                   for n in lit["nodes"]
                   if not c.execute(
                       "SELECT 1 FROM node WHERE label=? AND name=?",
                       (n["label"], n["name"])).fetchone()]
        self.assertEqual(missing, [],
                         "seed-literals nodes must all survive the seed")
        # 18 Subsystem-labeled nodes (17 literals + cell-movement-mouse-steering)
        self.assertEqual(c.execute(
            "SELECT COUNT(*) FROM node WHERE label='Subsystem'"
        ).fetchone()[0], 18)
        # test_result: exactly the 14 literal rows
        self.assertEqual(
            {r[0] for r in c.execute("SELECT name FROM test_result")},
            {t["name"] for t in lit["test_rows"]})
        # S1 gate (bare clone: SDK xml absent -> 0 fn rows from it):
        # 18 subsystem rows + the one completed cell case.
        self.assertEqual(c.execute(
            "SELECT COUNT(*) FROM investigations "
            "WHERE kind='subsystem'").fetchone()[0], 18)
        fn = c.execute(
            "SELECT id, status, stage FROM investigations "
            "WHERE kind='function'").fetchall()
        self.assertEqual(fn, [("fun:00e5b790:"
                               "Simulator::Cell::MovePlayerToMousePosition",
                               "done", "RECORDED")])
        c.close()

    # -- 3. repeated seed -> same logical state --------------------------- #
    def test_repeated_seed_same_db(self):
        run_seed(self.db, "--build-agnostic")
        first = logical_dump(self.db)
        run_seed(self.db, "--build-agnostic")
        second = logical_dump(self.db)
        self.assertEqual(first, second,
                         "re-seeding under the same identity must be a no-op")

    def test_two_fresh_dbs_identical(self):
        db2 = os.path.join(self.dir, "seed2.db")
        run_seed(self.db, "--build-agnostic")
        run_seed(db2, "--build-agnostic")
        self.assertEqual(logical_dump(self.db), logical_dump(db2),
                         "two fresh DBs must converge on one logical state")

    def test_logical_dump_ignores_trace_capture_time(self):
        db2 = os.path.join(self.dir, "seed2.db")
        run_seed(self.db, "--build-agnostic")
        run_seed(db2, "--build-agnostic")
        c = sqlite3.connect(self.db)
        c.execute("UPDATE trace_run SET captured_at='non-logical'")
        c.commit()
        c.close()
        self.assertEqual(logical_dump(self.db), logical_dump(db2))

    # -- 4. no duplicates -------------------------------------------------- #
    def test_no_duplicate_nodes_or_edges(self):
        run_seed(self.db, "--build-agnostic")
        c = sqlite3.connect(self.db)
        nodes = c.execute("SELECT COUNT(*) FROM node").fetchone()[0]
        distinct_nodes = c.execute(
            "SELECT COUNT(*) FROM (SELECT DISTINCT label, name FROM node)"
        ).fetchone()[0]
        self.assertEqual(nodes, distinct_nodes)
        edges = c.execute("SELECT COUNT(*) FROM edge").fetchone()[0]
        distinct_edges = c.execute(
            "SELECT COUNT(*) FROM (SELECT DISTINCT src, dst, rel FROM edge)"
        ).fetchone()[0]
        self.assertEqual(edges, distinct_edges)
        c.close()

    # -- 5. binary/source identity ------------------------------------------ #
    def test_explicit_binary_sha256_pinned_everywhere(self):
        run_seed(self.db, "--binary-sha256", SHA_A)
        c = sqlite3.connect(self.db)
        for t in ("node", "field", "investigations", "trace_run"):
            vals = {r[0] for r in
                    c.execute(f"SELECT DISTINCT binary_sha256 FROM {t}")}
            self.assertEqual(vals, {SHA_A},
                             f"{t}.binary_sha256 must carry the build id")
        c.close()

    def test_build_agnostic_identity_semantics(self):
        # --build-agnostic flag
        run_seed(self.db, "--build-agnostic")
        c = sqlite3.connect(self.db)
        self.assertEqual(c.execute(
            "SELECT DISTINCT binary_sha256 FROM node").fetchall(), [(None,)])
        self.assertEqual(c.execute(
            "SELECT DISTINCT binary_sha256 FROM field").fetchall(), [(None,)])
        # NOT NULL columns keep the sentinel.
        for t in ("investigations", "trace_run"):
            self.assertEqual(c.execute(
                f"SELECT DISTINCT binary_sha256 FROM {t}").fetchall(),
                [("build-agnostic",)])
        c.close()
        # Default mode with no game binary (what a bare clone sees: committed
        # docs present, no SPORE/): same NULL/sentinel semantics.
        bare_inputs = os.path.join(self.dir, "bare-repo")
        os.makedirs(os.path.join(bare_inputs, "knowledgegraph"))
        os.makedirs(os.path.join(bare_inputs, "docs"))
        shutil.copy(os.path.join(KG, "seed-literals.json"),
                    os.path.join(bare_inputs, "knowledgegraph"))
        shutil.copy(os.path.join(ROOT, "docs", "replacement-status.json"),
                    os.path.join(bare_inputs, "docs"))
        db2 = os.path.join(self.dir, "default-mode.db")
        run_seed(db2, "--inputs", bare_inputs)
        c = sqlite3.connect(db2)
        self.assertEqual(c.execute(
            "SELECT DISTINCT binary_sha256 FROM node").fetchall(), [(None,)])
        self.assertEqual(c.execute(
            "SELECT DISTINCT binary_sha256 FROM investigations"
        ).fetchall(), [("build-agnostic",)])
        c.close()

    # -- 6. stale-state detection ------------------------------------------ #
    def test_stale_rows_preserved_on_identity_flip(self):
        run_seed(self.db, "--binary-sha256", SHA_A)
        c = sqlite3.connect(self.db)
        old_rows = c.execute(
            "SELECT id, kind, status, stage FROM investigations "
            "WHERE binary_sha256=? ORDER BY id", (SHA_A,)).fetchall()
        node_total = c.execute("SELECT COUNT(*) FROM node").fetchone()[0]
        c.close()
        self.assertEqual(len(old_rows), 19)
        self.assertNotIn("dropped", [r[2] for r in old_rows])

        run_seed(self.db, "--binary-sha256", SHA_B)

        c = sqlite3.connect(self.db)
        preserved = c.execute(
            "SELECT id, kind, status, stage FROM investigations "
            "WHERE binary_sha256=? ORDER BY id", (SHA_A,)).fetchall()
        self.assertEqual(preserved, old_rows,
                         "old-identity queue rows must survive a re-seed "
                         "(doc §6: stale rows parked, never dropped)")
        # Staleness is queryable by identity (doc §3 rule 3 / §6):
        stale = c.execute(
            "SELECT COUNT(*) FROM investigations "
            "WHERE binary_sha256 != ?", (SHA_B,)).fetchone()[0]
        self.assertEqual(stale, 19)
        # No identity-B queue rows: the dedup PK keeps the first identity.
        self.assertEqual(c.execute(
            "SELECT COUNT(*) FROM investigations WHERE binary_sha256=?",
            (SHA_B,)).fetchone()[0], 0)
        # Build-sensitive nodes are rebuilt under the new identity.
        self.assertEqual(c.execute(
            "SELECT DISTINCT binary_sha256 FROM node").fetchall(),
            [(SHA_B,)])
        self.assertEqual(c.execute("SELECT COUNT(*) FROM node").fetchone()[0],
                         node_total)
        c.close()

    # -- 7. STATUS2EV through the seed path -------------------------------- #
    def test_all_statuses_seed_without_keyerror(self):
        with open(os.path.join(ROOT, "docs", "replacement-status.json")) as f:
            doc = json.load(f)
        statuses = set(doc["vocabulary"])
        for s in doc["subsystems"]:
            statuses.add(s["status"])
        # The exact mapping seed.py uses for every subsystem:
        for st in sorted(statuses):
            self.assertIn(seed._level_from_status(st), scale.EV)
        self.assertEqual(seed._level_from_status("approximated"),
                         "APPROXIMATION")
        self.assertEqual(seed._level_from_status("replaced-approx"),
                         "APPROXIMATION")
        # ...and the persisted node levels must equal the same mapping.
        run_seed(self.db, "--build-agnostic")
        c = sqlite3.connect(self.db)
        for s in doc["subsystems"]:
            name = f"sub:{s['name']}"  # seed.py's Subsystem naming
            got = c.execute(
                "SELECT evidence_level FROM node "
                "WHERE label='Subsystem' AND name=?",
                (name,)).fetchone()
            self.assertIsNotNone(got, f"missing Subsystem {s['name']}")
            self.assertEqual(got[0], scale.evidence_for_status(s["status"]))
        c.close()

    # -- 8. seed_sprint.py shim -------------------------------------------- #
    def _with_fake_home(self, fn):
        orig = os.environ.get("HOME")
        os.environ["HOME"] = self.dir
        try:
            return fn()
        finally:
            if orig is None:
                del os.environ["HOME"]
            else:
                os.environ["HOME"] = orig

    def test_shim_forwards_unknown_args(self):
        db = os.path.join(self.dir, "shim-forward.db")
        # argv[0] not in {init, seed} -> forwarded verbatim to seed.main.
        self._with_fake_home(
            lambda: seed_sprint.main(["--db", db, "--dry-run"]))
        self.assertFalse(os.path.exists(db),
                         "dry-run forwarding must not write a DB")

    def test_shim_init_writes_canonical_seed_only(self):
        db = os.path.join(self.dir, "shim-init.db")
        orig_db = seed.DEFAULT_DB
        seed.DEFAULT_DB = db
        try:
            # With a fake HOME the default --sdk-xml (~/.apps/...) is absent;
            # the shim's 'init' discards argv and calls seed.main([]).
            self._with_fake_home(lambda: seed_sprint.main(["init"]))
        finally:
            seed.DEFAULT_DB = orig_db
        self.assertTrue(os.path.exists(db))
        c = sqlite3.connect(db)
        self.assertEqual(c.execute(
            "SELECT COUNT(*) FROM node WHERE label='Subsystem'"
        ).fetchone()[0], 18)
        self.assertEqual(c.execute("SELECT COUNT(*) FROM test_result"
                                   ).fetchone()[0], 14)
        self.assertEqual(c.execute("SELECT COUNT(*) FROM investigations"
                                   ).fetchone()[0], 19)
        sha_vals = {r[0] for r in
                    c.execute("SELECT DISTINCT binary_sha256 FROM node")}
        self.assertEqual(len(sha_vals), 1,
                         "shim seed must carry a single build identity")
        nodes = c.execute("SELECT COUNT(*) FROM node").fetchone()[0]
        distinct = c.execute(
            "SELECT COUNT(*) FROM (SELECT DISTINCT label, name FROM node)"
        ).fetchone()[0]
        self.assertEqual(nodes, distinct)
        c.close()

    # -- 9. seed-literals.json integrity ------------------------------------ #
    def test_literals_file_integrity(self):
        with open(os.path.join(KG, "seed-literals.json")) as f:
            raw = f.read()
        lit = json.loads(raw)
        self.assertEqual(lit["counts"]["nodes"], len(lit["nodes"]))
        self.assertEqual(lit["counts"]["edges"], len(lit["edges"]))
        self.assertEqual(lit["counts"]["test_rows"], len(lit["test_rows"]))
        for n in lit["nodes"]:
            self.assertTrue(n.get("label"), "node without label")
            self.assertTrue(n.get("name"), "node without name")
        for e in lit["edges"]:
            for k in ("src_label", "src_name", "dst_label", "dst_name",
                      "rel"):
                self.assertTrue(e.get(k), f"edge missing {k}: {e}")
        for t in lit["test_rows"]:
            self.assertTrue(t.get("name"), "test row without name")
        # Machine-independence: no absolute filesystem paths anywhere.
        for m in re.finditer(
                r"/home/[A-Za-z0-9._-]+|/Users/[A-Za-z0-9._-]+|"
                r"/root/|[A-Za-z]:\\", raw):
            self.fail(f"absolute path in seed-literals.json: {m.group(0)!r}")
        # Confidence values live on the §3 scale; any single-token evidence
        # string is a 7-level or legacy-5 value (never an off-scale literal).
        ev_tokens = set(scale.EV) | set(scale.LEGACY_EV)
        for n in lit["nodes"]:
            conf = n.get("confidence", 0.0)
            self.assertTrue(0.0 <= conf <= 1.0, f"confidence out of [0,1]: {n}")
            # Values may be legacy/off-scale (e.g. 0.25); the canonical
            # mapping is the nearest of the 7 levels (doc §3).
            self.assertIn(seed._nearest_level(conf), scale.EV_ORDER)
            for v in (n.get("attrs") or {}).values():
                if isinstance(v, str) and " " not in v \
                        and v.isupper() and v.isalpha():
                    self.assertIn(v, ev_tokens,
                                  f"off-scale evidence token {v!r} in "
                                  f"{n['name']}")


if __name__ == "__main__":
    unittest.main()
