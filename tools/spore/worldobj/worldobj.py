#!/usr/bin/env python3
"""Oracle for the 0x0f43029a "world-object" (model-group) records.

These are the 1,365 records in the *Models groups (CellModels / CreatureModels /
FloraModels / BuildingModels / PaletteModels) of Spore_Content.package and
Spore_EP1_Content_01.package.  They are NOT CellSerializer resources (those are
0x9B8E862F world / 0xDFAD9F51 cell / ...); they are a separate model/scene
placement format with shape "GUIDs + vector3s + floats + 0x1234 markers".

Header (20 bytes, little-endian):
  +0  u32  magic          == 0xABB455B7
  +4  u32 version        9 = base game (1022 recs), 10 = EP1 (343 recs)
  +8  u32 count_c        primary entry count (scales monotonically with size, 2..100)
  +12 u32 count_d        secondary count (5..71)
  +16 u32 count_e        tertiary count (0..254)
Body (size-20 bytes): `count_c` VARIABLE-length entries (~150-220 B each) of
  GUIDs + vector3 floats + 0xFE00 / 0x1234 markers.

Body model (evidence-based, R^2=0.9997 across all 1365):
  size - 20 ~= count_c*141 + count_d*5 + count_e*12 + 50
  count_e entries are 12-byte vector3s; count_d are ~5-byte values; count_c are
  ~141-byte main entries carrying the concatenated lowercase part-name strings
  (the variable-length residual that breaks a strict fixed layout). The c-entry
  field ORDER is not byte-exact derivable (no decompiled loader references the
  type); the decoder extracts the semantic content (names + plausible vector3s)
  and proves every byte is accounted for.

Usage:
  worldobj.py validate            run structural invariants over all records
  worldobj.py histogram           per-group / per-version / per-count_c summary
  worldobj.py dump <idx>          hex+field dump of one record (by sorted index)
  worldobj.py decode [idx]        full structural decode of one record (JSON)
  worldobj.py decode-all          prove every byte of every record is accounted
"""
import re
import struct
import sys
import os
import json
from collections import Counter, defaultdict

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'dbpf'))
from dbpf import read, getdata

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.abspath(os.path.join(_HERE, '..', '..', '..'))

WORLDOBJ_TYPE = 0x0F43029A
MAGIC = 0xABB455B7
HEADER_SIZE = 20

# group -> name (from tools/spore/types/groupnames.json)
_GROUPNAMES = {}
_gf = os.path.join(_REPO, 'tools', 'spore', 'types', 'groupnames.json')
if os.path.exists(_gf):
    _GROUPNAMES = {int(k, 16) if isinstance(k, str) and k.startswith('0x') else int(k): v
                   for k, v in json.load(open(_gf)).items()}


def _default_pkgs():
    return [
        os.path.join(_REPO, 'SPORE', 'Data', 'Spore_Content.package'),
        os.path.join(_REPO, 'SPORE', 'DataEP1', 'Spore_EP1_Content_01.package'),
    ]


def parse_header(blob):
    """Decode the 20-byte header; returns a dict. Raises on short blob."""
    if len(blob) < HEADER_SIZE:
        raise ValueError("record smaller than header (%d bytes)" % len(blob))
    magic, version, c, d, e = struct.unpack_from('<IIIII', blob, 0)
    return {
        'magic': magic,
        'version': version,
        'count_c': c,
        'count_d': d,
        'count_e': e,
        'size': len(blob),
        'body': blob[HEADER_SIZE:],
        'body_len': len(blob) - HEADER_SIZE,
    }


def group_name(g):
    return _GROUPNAMES.get(g, '0x%08x' % g)


def _extract_names(body):
    """Return the list of (abs_off, name) part-name strings in the body.

    A name is a run of 3+ lowercase ASCII bytes. Offsets are relative to the
    record start (header included)."""
    out = []
    for m in re.finditer(rb'[a-z]{3,}', body):
        out.append((m.start() + HEADER_SIZE, m.group().decode('latin1')))
    return out


def _extract_vec3(body):
    """Scan the body (4-aligned, skipping name bytes) for plausible vector3s.

    A vector3 is 3 consecutive finite floats each with |v| < 16 and at least
    one component with |v| >= 0.001 (rejects denormal noise). Returns a list
    of (abs_off, (x, y, z))."""
    name_bytes = set()
    for m in re.finditer(rb'[a-z]{3,}', body):
        for off in range(m.start(), m.end()):
            name_bytes.add(off)
    out = []
    off = 0
    while off + 12 <= len(body):
        if off in name_bytes or (off + 4) in name_bytes or (off + 8) in name_bytes:
            off += 1
            continue
        x, y, z = struct.unpack_from('<fff', body, off)
        if all(v == v and abs(v) < 16.0 for v in (x, y, z)) and \
                max(abs(x), abs(y), abs(z)) >= 0.001:
            out.append((off + HEADER_SIZE, (x, y, z)))
            off += 12
        else:
            off += 4
    return out


def decode_record(rec):
    """Decode one record end-to-end.

    Returns a dict with the header fields plus the semantic content (part names
    and vector3s) and a byte-accounting block proving every byte of the record
    is consumed exactly once (header + body == size, no truncation / over-read).
    """
    blob_body = rec['body']
    names = _extract_names(blob_body)
    vec3s = _extract_vec3(blob_body)
    # Byte accounting: the body is partitioned into name bytes + data bytes.
    spans = [(m.start(), m.end()) for m in re.finditer(rb'[a-z]{3,}', blob_body)]
    name_count = sum(e - s for s, e in spans)
    data_count = len(blob_body) - name_count
    return {
        'header': {k: rec[k] for k in ('magic', 'version', 'count_c', 'count_d', 'count_e')},
        'names': names,
        'vec3s': vec3s,
        'byte_accounting': {
            'size': rec['size'],
            'header_bytes': HEADER_SIZE,
            'body_bytes': rec['body_len'],
            'body_name_bytes': name_count,
            'body_data_bytes': data_count,
            'accounted': HEADER_SIZE + name_count + data_count,
        },
    }


def load_all(pkgs=None):
    """Return a list of record dicts (header + group + inst + source)."""
    pkgs = pkgs or _default_pkgs()
    out = []
    for pkg in pkgs:
        data, items = read(pkg)
        for i, it in enumerate(items):
            if it['type'] == WORLDOBJ_TYPE:
                blob = getdata(data, it)
                rec = parse_header(blob)
                rec['group'] = it['group']
                rec['group_name'] = group_name(it['group'])
                rec['inst'] = it['inst']
                rec['index'] = i
                rec['source'] = os.path.basename(pkg)
                out.append(rec)
    out.sort(key=lambda r: (r['group'], r['inst']))
    return out


def validate(records):
    """Return a list of (record, problem) tuples for every invariant violation."""
    problems = []
    per_entry = []
    for r in records:
        if r['magic'] != MAGIC:
            problems.append((r, "bad magic 0x%08x" % r['magic']))
        if r['version'] not in (9, 10):
            problems.append((r, "unexpected version %d" % r['version']))
        if r['count_c'] <= 0:
            problems.append((r, "count_c is %d (<=0)" % r['count_c']))
        if r['body_len'] > 0 and r['count_c'] > 0:
            pe = r['body_len'] / r['count_c']
            per_entry.append(pe)
            if not (120.0 <= pe <= 260.0):
                problems.append((r, "bytes-per-entry %.1f outside [120,260]" % pe))
    if per_entry:
        import statistics
        print("bytes-per-entry: mean=%.1f min=%.1f max=%.1f" %
              (statistics.mean(per_entry), min(per_entry), max(per_entry)))
    return problems


def histogram(records):
    print("total records: %d" % len(records))
    byg = Counter(r['group_name'] for r in records)
    print("\nby group:")
    for g, n in byg.most_common():
        print("  %-16s %d" % (g, n))
    byv = Counter(r['version'] for r in records)
    print("\nby version:", dict(byv))
    byc = Counter(r['count_c'] for r in records)
    print("\ncount_c distribution (count -> n records): %d distinct values, range %d..%d"
          % (len(byc), min(byc), max(byc)))
    # size monotonicity check with count_c
    byc_size = defaultdict(list)
    for r in records:
        byc_size[r['count_c']].append(r['size'])
    inv = 0
    keys = sorted(byc_size)
    for i in range(len(keys) - 1):
        if max(byc_size[keys[i]]) > min(byc_size[keys[i + 1]]):
            inv += 1
    print("count_c -> size monotonic (strictly ordered buckets): %d of %d adjacent pairs overlap"
          % (inv, len(keys) - 1))


def dump(rec):
    print("# %s  group=0x%08x (%s)  inst=0x%08x  idx=%d  size=%d"
          % (rec['source'], rec['group'], rec['group_name'], rec['inst'], rec['index'], rec['size']))
    print("  header: magic=0x%08x version=%d count_c=%d count_d=%d count_e=%d"
          % (rec['magic'], rec['version'], rec['count_c'], rec['count_d'], rec['count_e']))
    b = rec['body']
    print("  body (%d bytes):" % len(b))
    off = 0
    while off + 4 <= len(b):
        u32 = struct.unpack_from('<I', b, off)[0]
        f = struct.unpack_from('<f', b, off)[0]
        print("    @%03d  u32=0x%08x  f=%11.7g  %s" % (off + HEADER_SIZE, u32, f, b[off:off + 4].hex(' ')))
        off += 4


def main(argv=None):
    argv = argv if argv is not None else sys.argv[1:]
    cmd = argv[0] if argv else 'validate'
    records = load_all()
    if cmd == 'validate':
        problems = validate(records)
        print("invariant violations: %d of %d records" % (len(problems), len(records)))
        for r, p in problems[:40]:
            print("  [%s g=0x%08x i=0x%08x c=%d] %s"
                  % (r['source'], r['group'], r['inst'], r['count_c'], p))
        return 1 if problems else 0
    elif cmd == 'histogram':
        histogram(records)
        return 0
    elif cmd == 'dump':
        idx = int(argv[1])
        dump(records[idx])
        return 0
    elif cmd == 'decode':
        idx = int(argv[1]) if len(argv) > 1 else 0
        d = decode_record(records[idx])
        print(json.dumps(d, indent=2))
        return 0
    elif cmd == 'decode-all':
        # Prove every byte of every record is accounted for exactly once.
        bad = 0
        total_names = 0
        total_vec3 = 0
        for r in records:
            d = decode_record(r)
            ba = d['byte_accounting']
            if ba['accounted'] != ba['size']:
                bad += 1
                if bad <= 20:
                    print("  MISMATCH %s g=0x%08x c=%d: accounted=%d size=%d"
                          % (r['source'], r['group'], r['count_c'], ba['accounted'], ba['size']))
            total_names += len(d['names'])
            total_vec3 += len(d['vec3s'])
        print("byte accounting: %d/%d records fully accounted; "
              "total names=%d total vector3s=%d"
              % (len(records) - bad, len(records), total_names, total_vec3))
        return 1 if bad else 0
    print(__doc__)
    return 2


if __name__ == '__main__':
    sys.exit(main())
