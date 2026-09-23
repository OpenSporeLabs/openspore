#!/usr/bin/env python3
"""Canonical asset manifest v1 (CS-22, docs/ASSET-IMPORT-ROADMAP.md §3.1).

One row per DBPF record, in a rebuildable SQLite sidecar:

    (type, group, instance)   -- primary key
      type_name, group_name   -- from tools/spore/types/{type,group}names.json
      size, format_class      -- measured / derived from the type
      decode_status           -- ok | walk-fail | container-undecoded | undecoded
      semantic_owner          -- UNKNOWN until P3/P4 evidence lands
      evidence                -- per-field label (VERIFIED / INFERRED / UNKNOWN)

Built idempotently: the sidecar is dropped and rebuilt from scratch each run,
rows inserted in a stable (type, group, instance) order, so a double run is
byte-identical (the sim_contract discipline applied to data).

Usage:
    manifest.py build   <package> [--out DB]
    manifest.py verify  <package> [--out DB]
"""
import argparse
import json
import os
import sqlite3
import struct
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
_SPORE = os.path.abspath(os.path.join(_HERE, '..'))
sys.path.insert(0, os.path.join(_SPORE, 'dbpf'))
from dbpf import read  # noqa: E402

_TYPE_F = os.path.join(_SPORE, 'types', 'typenames.json')
_GROUP_F = os.path.join(_SPORE, 'types', 'groupnames.json')
_DEFAULT_DB = os.path.join(_HERE, 'manifest.db')


def _load(f):
    if os.path.exists(f):
        with open(f) as fh:
            return {int(k): v for k, v in json.load(fh).items()}
    return {}


def type4cc(t: int) -> str:
    return struct.pack('<I', t).decode('latin1', 'replace')


# canonical type NAME -> manifest format_class (roadmap §3.1: gmdl/raster/rw4/...)
# The type name comes from types/typenames.json (Spore type IDs are NOT FourCC).
_FORMAT = {
    'gmdl': 'gmdl', 'gmsh': 'gmdl',
    'raster': 'raster', 'png': 'raster', 'jpeg': 'raster', 'plt': 'raster',
    'rw4': 'rw4',
    'prop': 'prop',
    'cll': 'cll',
    'cell': 'cell',
    'animation': 'animation',
    'structure': 'structure',
    'loottable': 'loot',
    'populate': 'populate',
    'world': 'world',
    'effdir': 'effdir',
    'crt': 'crt', 'bld': 'bld', 'vcl': 'vcl', 'flr': 'flr', 'ufo': 'ufo',
    'bem': 'bem', 'cnv': 'container', 'smt': 'smt',
}

_CONTAINERS = {'cll', 'prop', 'bld', 'vcl', 'crt', 'structure', 'cnv'}


def format_class(name: str) -> str:
    low = name.lower()
    if low in _FORMAT:
        return _FORMAT[low]
    return low


def probe_gmdl(data: bytes, off: int, csize: int, msize: int) -> str:
    """Cheap structural GMDL probe (no temp file). ok if the header is sane."""
    n = min(csize, msize, len(data) - off)
    if n < 12:
        return 'undecoded'
    b = data[off:off + n]
    version = struct.unpack_from('<I', b, 0)[0]
    refCount = struct.unpack_from('>I', b, 4)[0]
    if version not in (1, 2, 3, 4) or refCount > 10000:
        return 'walk-fail'
    o = 4 + 4 + 12 * refCount
    if o + 4 > n:
        return 'walk-fail'
    meshCount = struct.unpack_from('<I', b, o)[0]
    if meshCount > 10000:
        return 'walk-fail'
    return 'ok'


def decode_status(name: str, data: bytes, rec: dict) -> str:
    n = name.lower()
    if n in _CONTAINERS:
        return 'container-undecoded'
    if n in ('gmdl', 'gmsh'):
        return probe_gmdl(data, rec['off'], rec['csize'], rec['msize'])
    if n in ('raster', 'jpeg', 'png', 'plt'):
        return 'ok' if rec['msize'] >= 16 else 'undecoded'
    return 'undecoded'


def _row(pkg: str, rec: dict, types: dict, groups: dict, data: bytes) -> tuple:
    t, g, i = rec['type'], rec['group'], rec['inst']
    tn = types.get(t, f"0x{t:08x}")
    gn = groups.get(g, '')
    fc = format_class(tn)
    ds = decode_status(tn, data, rec)
    evidence = {
        'type_name': 'VERIFIED' if t in types else 'INFERRED',
        'group_name': 'VERIFIED' if g in groups else 'UNKNOWN',
        'size': 'VERIFIED',
        'format_class': 'INFERRED',
        'decode_status': 'INFERRED',
        'semantic_owner': 'UNKNOWN',
    }
    return (t, g, i, tn, gn, rec['msize'], fc, ds, 'UNKNOWN', json.dumps(evidence, sort_keys=True))


SCHEMA = """
CREATE TABLE manifest (
  type INTEGER NOT NULL,
  grp INTEGER NOT NULL,
  inst INTEGER NOT NULL,
  type_name TEXT NOT NULL,
  group_name TEXT NOT NULL,
  size INTEGER NOT NULL,
  format_class TEXT NOT NULL,
  decode_status TEXT NOT NULL,
  semantic_owner TEXT NOT NULL,
  evidence TEXT NOT NULL,
  PRIMARY KEY (type, grp, inst)
);
"""


def build(pkg: str, out_db: str = _DEFAULT_DB) -> int:
    types = _load(_TYPE_F)
    groups = _load(_GROUP_F)
    data, items = read(pkg)
    rows = [_row(pkg, r, types, groups, data) for r in items]
    rows.sort(key=lambda r: (r[0], r[1], r[2]))

    if os.path.exists(out_db):
        os.remove(out_db)
    con = sqlite3.connect(out_db)
    try:
        con.executescript(SCHEMA)
        con.executemany(
            'INSERT INTO manifest VALUES (?,?,?,?,?,?,?,?,?,?)', rows)
        con.commit()
    finally:
        con.close()
    return len(rows)


def _sha(p: str) -> str:
    import hashlib
    h = hashlib.sha256()
    with open(p, 'rb') as f:
        for chunk in iter(lambda: f.read(65536), b''):
            h.update(chunk)
    return h.hexdigest()


def verify(pkg: str, out_db: str = _DEFAULT_DB) -> int:
    """Rebuild twice; require byte-identical files and full index coverage."""
    import hashlib
    data, items = read(pkg)
    expected = len(items)

    build(pkg, out_db)
    a = _sha(out_db)
    build(pkg, out_db)
    b = _sha(out_db)

    con = sqlite3.connect(out_db)
    try:
        present = con.execute('SELECT COUNT(*) FROM manifest').fetchone()[0]
    finally:
        con.close()

    print(f"records in index : {expected}")
    print(f"manifest rows    : {present}")
    print(f"sha256 run 1     : {a}")
    print(f"sha256 run 2     : {b}")
    ok_bytes = a == b
    ok_cover = present == expected
    print(f"double-run byte-identical : {ok_bytes}")
    print(f"100% index coverage       : {ok_cover}")
    return 0 if (ok_bytes and ok_cover) else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('build', 'verify'):
        s = sub.add_parser(name)
        s.add_argument('package')
        s.add_argument('--out', default=_DEFAULT_DB)
    a = ap.parse_args(argv)
    if a.cmd == 'build':
        n = build(a.package, a.out)
        print(f"built {a.out}: {n} rows")
        return 0
    return verify(a.package, a.out)


if __name__ == '__main__':
    sys.exit(main())
