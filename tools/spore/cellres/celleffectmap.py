#!/usr/bin/env python3
"""CS-12 cCellEffectMapResource + cCellBackgroundMapResource oracle.

Types 0x433FB70C (effect map) / 0x612B3191 (background map).
Spore_Game + Spore_PatchData (repack): 1 record each (EP1 adds none).

File layout (evidence-confirmed):

cCellEffectMapResource:
    i32 numEntries       24
    u32 entries          dead ptr slot
    numEntries * cEffectMapEntry (28 B):
        u32 effectID     soft effect id (22/24 absent from these packages)
        u32 type         2 / 3 / 5
        f32 field_8      -1.0 sentinel or 0.42 .. 5700
        f32 field_C      -1.0 sentinel or 0.7 .. 14950
        f32 field_10     0.75 .. 20000
        f32 field_14     0.9 .. 20000
        i32 field_18     0 / 3 / 11

cCellBackgroundMapResource:
    i32 numEntries       12
    u32 entries          dead ptr slot
    numEntries * cBackgroundMapEntry (16 B):
        f32 r, g, b      0 .. 1
        f32 field_C      0.0 / 0.5 / 1.5 / 5 / 15 / 50 / 150 / 500 /
                         1500 / 5000 / 15000 / 100000 (geometric ladder)

Usage:
    effectmap.py validate
    effectmap.py dump <inst_hex>
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
EM = 0x433FB70C
BM = 0x612B3191
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    em_insts, bm_insts = set(), set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] not in (EM, BM):
                continue
            blob = getdata(data, it)
            key = (it['type'], blob)
            if key not in seen:
                seen[key] = (rel, it['group'], it['inst'] & 0xFFFFFFFF)
            (em_insts if it['type'] == EM else bm_insts).add(
                it['inst'] & 0xFFFFFFFF)
    recs = [(t, loc[2], blob) for (t, blob), loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, em_insts, bm_insts


def decode_em(blob):
    if len(blob) < 8:
        raise ValueError("too small: %d" % len(blob))
    n, ptr = struct.unpack_from('<2i', blob, 0)
    if n < 0:
        raise ValueError("negative numEntries %d" % n)
    if len(blob) != 8 + 28 * n:
        raise ValueError("span %d != %d" % (len(blob), 8 + 28 * n))
    entries = []
    off = 8
    for _ in range(n):
        eid, ty = struct.unpack_from('<2I', blob, off)
        f8, fc, f10, f14 = struct.unpack_from('<4f', blob, off + 8)
        i18 = struct.unpack_from('<i', blob, off + 24)[0]
        entries.append({'effectID': eid, 'type': ty, 'f8': f8, 'fC': fc,
                        'f10': f10, 'f14': f14, 'i18': i18})
        off += 28
    return {'numEntries': n, 'entriesPtr': ptr, 'entries': entries}


def decode_bm(blob):
    if len(blob) < 8:
        raise ValueError("too small: %d" % len(blob))
    n, ptr = struct.unpack_from('<2i', blob, 0)
    if n < 0:
        raise ValueError("negative numEntries %d" % n)
    if len(blob) != 8 + 16 * n:
        raise ValueError("span %d != %d" % (len(blob), 8 + 16 * n))
    entries = []
    off = 8
    for _ in range(n):
        r, g, b = struct.unpack_from('<3f', blob, off)
        fc = struct.unpack_from('<f', blob, off + 12)[0]
        entries.append({'r': r, 'g': g, 'b': b, 'fC': fc})
        off += 16
    return {'numEntries': n, 'entriesPtr': ptr, 'entries': entries}


def f_ok(v, lo, hi, sentinel=False):
    if v != v:
        return False
    if sentinel and v == -1.0:
        return True
    return lo <= v <= hi


def issues_em(r):
    out = []
    for e in r['entries']:
        if e['type'] > 31:
            out.append('type=%d' % e['type'])
        if not f_ok(e['f8'], -100.0, 100000.0, sentinel=True):
            out.append('f8=%r' % e['f8'])
        if not f_ok(e['fC'], -100.0, 100000.0, sentinel=True):
            out.append('fC=%r' % e['fC'])
        if not f_ok(e['f10'], 0.0, 100000.0):
            out.append('f10=%r' % e['f10'])
        if not f_ok(e['f14'], 0.0, 100000.0):
            out.append('f14=%r' % e['f14'])
        if not (-16 <= e['i18'] <= 64):
            out.append('i18=%d' % e['i18'])
    return out


def issues_bm(r):
    out = []
    for e in r['entries']:
        for k in ('r', 'g', 'b'):
            if not f_ok(e[k], 0.0, 1.0):
                out.append('%s=%r' % (k, e[k]))
        if not f_ok(e['fC'], 0.0, 100000.0):
            out.append('fC=%r' % e['fC'])
    return out


def main():
    recs, em_insts, bm_insts = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for t, inst, blob in recs:
            if inst == want:
                if t == EM:
                    r = decode_em(blob)
                    print('effectMap inst=%08x nE=%d' % (inst,
                                                          r['numEntries']))
                    for e in r['entries']:
                        print('  entry: id=0x%08x type=%d f8=%.3f fC=%.3f '
                              'f10=%.3f f14=%.3f i18=%d'
                              % (e['effectID'], e['type'], e['f8'], e['fC'],
                                 e['f10'], e['f14'], e['i18']))
                else:
                    r = decode_bm(blob)
                    print('bgMap inst=%08x nE=%d' % (inst, r['numEntries']))
                    for e in r['entries']:
                        print('  entry: rgb=(%.3f,%.3f,%.3f) fC=%.3f'
                              % (e['r'], e['g'], e['b'], e['fC']))
                return
        sys.exit('no record with inst %08x' % want)

    bad = 0
    canon, canon2 = [], []
    for t, inst, blob in recs:
        if t == EM:
            try:
                r = decode_em(blob)
                probs = issues_em(r)
                r2 = decode_em(blob)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
        else:
            try:
                r = decode_bm(blob)
                probs = issues_bm(r)
                r2 = decode_bm(blob)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
        canon.append(repr(r))
        canon2.append(repr(r2))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('effectMaps=%d  bgMaps=%d  emInsts=%d  bmInsts=%d  '
          'violations=%d  double_run=%s'
          % (sum(1 for x in recs if x[0] == EM),
             sum(1 for x in recs if x[0] == BM),
             len(em_insts), len(bm_insts), bad, same))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
