#!/usr/bin/env python3
"""OPT-IN real-asset differential test (no-op when SPORE/ is absent -> CI-safe).

Extracts one small known GMDL record from a real package, parses it with the
committed tools, and compares the semantic fields against a recorded JSON
expectation (semantic fields only - type IDs, sizes, counts - never asset bytes).

Usage:
    python3 tests/diff_real.py            # compare against recorded expectation
    python3 tests/diff_real.py --record   # re-record expectation from local SPORE/
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'dbpf'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'gmdl'))

SPORE_DIR = os.path.join(ROOT, 'SPORE')
EXPECT_FILE = os.path.join(ROOT, 'tests', 'expected', 'real_gmdl_1006.json')
OUT_DIR = '/tmp/opencode/spore/out'
OUT_FILE = os.path.join(OUT_DIR, 'real_gmdl_1006.bin')


def semantic_diff(expected, actual, path='$'):
    lines = []
    if isinstance(expected, dict) and isinstance(actual, dict):
        for k in sorted(set(expected) | set(actual), key=str):
            p = f'{path}.{k}'
            if k not in actual:
                lines.append(f'{p}: missing in actual (expected {expected[k]!r})')
            elif k not in expected:
                lines.append(f'{p}: unexpected in actual {actual[k]!r}')
            elif expected[k] != actual[k]:
                lines.extend(semantic_diff(expected[k], actual[k], p))
    elif expected != actual:
        lines.append(f'{path}: expected {expected!r} got {actual!r}')
    return lines


def main(argv):
    if not os.path.isdir(SPORE_DIR):
        print("SPORE/ not present in this checkout - real-asset differential test skipped (no-op).")
        print("This is expected on fresh checkouts / CI; the synthetic suite in tests/test_formats.py still runs.")
        return 0

    exp = json.load(open(EXPECT_FILE))
    pkg = os.path.join(ROOT, exp['package'])
    if not os.path.isfile(pkg):
        print(f"{exp['package']} not found - real-asset differential test skipped (no-op).")
        return 0

    import dbpf
    import gmdl

    data, items = dbpf.read(pkg)
    it = None
    for cand in items:
        if (cand['type'] == exp['typeID'] and cand['group'] == exp['group']
                and cand['inst'] == exp['instance']):
            it = cand
            break
    if it is None:
        print(f"FATAL: record (typeID=0x{exp['typeID']:08x}, g=0x{exp['group']:08x}, "
              f"i=0x{exp['instance']:08x}) no longer present in {exp['package']} - content changed upstream.")
        return 1
    idx = items.index(it)
    if idx != exp['index']:
        print(f"note: record index is now {idx}, recorded {exp['index']} (package content shifted)")

    blob = dbpf.getdata(data, it)
    os.makedirs(OUT_DIR, exist_ok=True)
    with open(OUT_FILE, 'wb') as f:
        f.write(blob)
    print(f"extracted {len(blob)} bytes -> {OUT_FILE}")

    g = gmdl.Gmdl(OUT_FILE)
    sem = dict(
        version=g.version, refCount=g.refCount, refs=[list(r) for r in g.refs],
        meshCount=g.meshCount,
        bboxMin=[round(v, 4) for v in g.bboxMin], bboxMax=[round(v, 4) for v in g.bboxMax],
        radius=round(g.radius, 4),
        indexBuffers=[dict(prim=ib['prim'], count=ib['count'], bits=ib['bits'], bufSize=ib['size'])
                      for ib in g.indexBuffers],
        vertexDescriptors=[[dict(e) for e in desc] for desc in g.vertexDescriptors],
        vertexBuffers=[dict(descIdx=vb['descIdx'], vertexCount=vb['vertexCount'], bufSize=vb['size'])
                       for vb in g.vertexBuffers],
        meshes=[list(m) for m in g.meshes],
        materialIDs=g.materialIDs,
        materialInfoCount=len(g.materialInfos),
        boneRangeCount=len(g.boneRanges), animDataCount=len(g.animDatas),
        unknownKey=list(g.unknownKey),
        finalOffset=g.finalOffset, fileBytes=len(g.b), parseMatchesFile=g.matches())

    if '--record' in argv:
        doc = dict(exp)
        doc['semantics'] = sem
        os.makedirs(os.path.dirname(EXPECT_FILE), exist_ok=True)
        with open(EXPECT_FILE, 'w') as f:
            json.dump(doc, f, indent=1, sort_keys=True)
            f.write('\n')
        print(f"recorded {len(sem)} semantic fields -> {os.path.relpath(EXPECT_FILE, ROOT)}")
        return 0

    want = exp['semantics']
    if want != sem:
        print("REAL-ASSET DIFF MISMATCH:")
        print('\n'.join(semantic_diff(want, sem)))
        print(f"(re-record with: python3 {os.path.relpath(__file__, ROOT)} --record)")
        return 1
    print(f"real-asset differential OK: {len(sem)} semantic fields match recorded expectation")
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
