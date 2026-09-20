#!/usr/bin/env python3
"""OpenSpore knowledge-graph sidecar CLI.

Small, stdlib-only helper over knowledgegraph/spore.db. The heavy binary/
structure analysis graph lives in Ghidra; this store holds cross-tool memory
(test outcomes, decisions, asset-format mappings).

Usage:
  kg.py init
  kg.py add-node --label Structure --name Creature --attrs '{"hp":30}' --origin sdk
  kg.py add-edge --src Creature --dst BodyPart --rel hasPart
  kg.py query --label Class
  kg.py neighbors --name Creature
  kg.py record-test --name cell_tick --stage cell --seed 12345 --expected A --actual A --pass 1
  kg.py dump
"""
import argparse
import json
import os
import sqlite3
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DB = os.path.join(HERE, "spore.db")
SCHEMA = os.path.join(HERE, "schema.sql")


def conn():
    c = sqlite3.connect(DB)
    c.row_factory = sqlite3.Row
    return c


def cmd_init(_a):
    with open(SCHEMA) as f:
        sql = f.read()
    with conn() as c:
        c.executescript(sql)
    print(f"initialized {DB}")


def _node_id(c, name):
    rows = c.execute("SELECT id FROM node WHERE name=? LIMIT 2", (name,)).fetchall()
    if not rows:
        sys.exit(f"error: node not found: {name!r}")
    if len(rows) > 1:
        sys.exit(f"error: ambiguous node name: {name!r}")
    return rows[0]["id"]


def cmd_add_node(a):
    with conn() as c:
        c.execute(
            """INSERT INTO node(label,name,attrs_json,confidence,origin,note)
               VALUES(?,?,?,?,?,?)
               ON CONFLICT(label,name) DO UPDATE SET
                 attrs_json=excluded.attrs_json,
                 confidence=excluded.confidence,
                 origin=excluded.origin,
                 note=excluded.note""",
            (a.label, a.name, a.attrs or "{}", a.confidence, a.origin, a.note),
        )
    print(f"node: {a.label}/{a.name}")


def cmd_add_edge(a):
    with conn() as c:
        s = _node_id(c, a.src)
        d = _node_id(c, a.dst)
        c.execute(
            "INSERT OR IGNORE INTO edge(src,dst,rel) VALUES(?,?,?)",
            (s, d, a.rel),
        )
    print(f"edge: {a.src} -[{a.rel}]-> {a.dst}")


def cmd_query(a):
    q = "SELECT label,name,attrs_json,confidence,origin FROM node"
    args = []
    if a.label:
        q += " WHERE label=?"
        args.append(a.label)
    q += " ORDER BY label,name"
    with conn() as c:
        for r in c.execute(q, args):
            print(json.dumps(dict(r)))


def cmd_neighbors(a):
    with conn() as c:
        me = _node_id(c, a.name)
        rows = c.execute(
            """SELECT n1.name src, e.rel, n2.name dst
               FROM edge e
               JOIN node n1 ON n1.id=e.src
               JOIN node n2 ON n2.id=e.dst
               WHERE e.src=? OR e.dst=? ORDER BY e.rel""",
            (me, me),
        )
        for r in rows:
            print(f"{r['src']} -[{r['rel']}]-> {r['dst']}")


def cmd_record_test(a):
    with conn() as c:
        c.execute(
            """INSERT INTO test_result(name,stage,seed,expected,actual,pass)
               VALUES(?,?,?,?,?,?)""",
            (a.name, a.stage, a.seed, a.expected, a.actual,
             None if a.pass_ is None else int(a.pass_)),
        )
    print(f"test: {a.name}")


def cmd_dump(_a):
    with conn() as c:
        nodes = [dict(r) for r in c.execute("SELECT * FROM node")]
        edges = [dict(r) for r in c.execute(
            """SELECT n1.name src,e.rel,n2.name dst FROM edge e
               JOIN node n1 ON n1.id=e.src JOIN node n2 ON n2.id=e.dst""")]
        tests = [dict(r) for r in c.execute("SELECT * FROM test_result")]
    print(json.dumps({"nodes": nodes, "edges": edges, "tests": tests}, indent=2))


def main():
    p = argparse.ArgumentParser(description=__doc__)
    sub = p.add_subparsers(dest="cmd", required=True)

    sub.add_parser("init").set_defaults(fn=cmd_init)

    an = sub.add_parser("add-node")
    an.add_argument("--label", required=True)
    an.add_argument("--name", required=True)
    an.add_argument("--attrs", help="JSON object of attributes")
    an.add_argument("--confidence", type=float, default=0.0)
    an.add_argument("--origin", default="manual",
                    help="static|dynamic|sdk|llm|manual")
    an.add_argument("--note")
    an.set_defaults(fn=cmd_add_node)

    ae = sub.add_parser("add-edge")
    ae.add_argument("--src", required=True)
    ae.add_argument("--dst", required=True)
    ae.add_argument("--rel", required=True)
    ae.set_defaults(fn=cmd_add_edge)

    q = sub.add_parser("query")
    q.add_argument("--label")
    q.set_defaults(fn=cmd_query)

    nb = sub.add_parser("neighbors")
    nb.add_argument("--name", required=True)
    nb.set_defaults(fn=cmd_neighbors)

    rt = sub.add_parser("record-test")
    rt.add_argument("--name", required=True)
    rt.add_argument("--stage")
    rt.add_argument("--seed")
    rt.add_argument("--expected")
    rt.add_argument("--actual")
    rt.add_argument("--pass", dest="pass_", choices=["0", "1"], help="0|1, omit if unknown")
    rt.set_defaults(fn=cmd_record_test)

    sub.add_parser("dump").set_defaults(fn=cmd_dump)

    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
