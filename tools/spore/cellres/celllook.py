#!/usr/bin/env python3
"""CS-10 cCellLookTableResource + cCellLookAlgorithmResource oracle.

Types 0x8C042499 (look tables) / 0xDBA35AE2 (look algorithms).
Spore_Game + Spore_PatchData (repack duplicates): 11+11 table instances
(9 unique blobs, 10 inst ids), 1+1 algorithm instances (1 unique).
EP1 adds none. File layout (evidence-confirmed):

cCellLookTableResource:
    u32 entries        dead ptr slot
    i32 numEntries
    numEntries * cLookTableEntry (8 B: u32 type 0..11, f32 value 1/5/10)

cCellLookAlgorithmResource:
    u32 entries        dead ptr slot
    i32 numEntries
    numEntries * cLookAlgorithmEntry (20 B):
        u32 type     0 / 1 / 2
        u32 action   0 / 18..22 / 0xFFFFFFFF
        u32 player   look-table ref (resolves)
        u32 npc      look-table ref (resolves)
        u32 epic     look-table ref (resolves)

Usage:
    celllook.py validate           # decode all records, assert domains
    celllook.py dump <inst_hex>    # dump one record (any type, any package)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
LT = 0x8C042499
LA = 0xDBA35AE2
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    lt_insts = set()
    la_insts = set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] not in (LT, LA):
                continue
            blob = getdata(data, it)
            key = (it['type'], blob)
            if key not in seen:
                seen[key] = (rel, it['group'], it['inst'] & 0xFFFFFFFF)
            if it['type'] == LT:
                lt_insts.add(it['inst'] & 0xFFFFFFFF)
            else:
                la_insts.add(it['inst'] & 0xFFFFFFFF)
    recs = [(t, loc[2], blob) for (t, blob), loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, lt_insts, la_insts


def decode_table(blob):
    if len(blob) < 8:
        raise ValueError("too small: %d" % len(blob))
    ptr, n = struct.unpack_from('<2i', blob, 0)
    if n < 0:
        raise ValueError("negative numEntries %d" % n)
    if len(blob) != 8 + 8 * n:
        raise ValueError("span %d != %d" % (len(blob), 8 + 8 * n))
    entries = []
    off = 8
    for _ in range(n):
        t = struct.unpack_from('<i', blob, off)[0]
        v = struct.unpack_from('<f', blob, off + 4)[0]
        entries.append({'type': t, 'value': v})
        off += 8
    return {'ptr': ptr, 'numEntries': n, 'entries': entries}


def decode_algo(blob):
    if len(blob) < 8:
        raise ValueError("too small: %d" % len(blob))
    ptr, n = struct.unpack_from('<2i', blob, 0)
    if n < 0:
        raise ValueError("negative numEntries %d" % n)
    if len(blob) != 8 + 20 * n:
        raise ValueError("span %d != %d" % (len(blob), 8 + 20 * n))
    entries = []
    off = 8
    for _ in range(n):
        t, a, p, q, e = struct.unpack_from('<5I', blob, off)
        entries.append({'type': t, 'action': a, 'player': p, 'npc': q,
                        'epic': e})
        off += 20
    return {'ptr': ptr, 'numEntries': n, 'entries': entries}


def issues_table(r):
    out = []
    for e in r['entries']:
        if not (0 <= e['type'] <= 31):
            out.append('type=%d' % e['type'])
        if e['value'] != e['value'] or e['value'] < 0.0 or e['value'] > 100.0:
            out.append('value=%r' % e['value'])
    return out


def issues_algo(r, lt_insts):
    out = []
    for e in r['entries']:
        if e['type'] > 5:
            out.append('type=%d' % e['type'])
        if e['action'] not in (0, 18, 19, 20, 21, 22, 0xFFFFFFFF) and \
                e['action'] > 60:
            out.append('action=0x%08x' % e['action'])
        for k in ('player', 'npc', 'epic'):
            v = e[k]
            if v and v not in lt_insts:
                out.append('%s=0x%08x' % (k, v))
    return out


def main():
    recs, lt_insts, la_insts = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for t, inst, blob in recs:
            if inst == want:
                if t == LT:
                    r = decode_table(blob)
                    print('lookTable inst=%08x nE=%d' % (inst, r['numEntries']))
                    for e in r['entries']:
                        print('  entry: type=%d value=%.3f'
                              % (e['type'], e['value']))
                else:
                    r = decode_algo(blob)
                    print('lookAlgo inst=%08x nE=%d' % (inst, r['numEntries']))
                    for e in r['entries']:
                        print('  entry: type=%d action=0x%08x p=0x%08x '
                              'n=0x%08x e=0x%08x'
                              % (e['type'], e['action'], e['player'],
                                 e['npc'], e['epic']))
                return
        sys.exit('no record with inst %08x' % want)

    bad = 0
    canon, canon2 = [], []
    for t, inst, blob in recs:
        if t == LT:
            try:
                r = decode_table(blob)
                probs = issues_table(r)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
        else:
            try:
                r = decode_algo(blob)
                probs = issues_algo(r, lt_insts)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
        r2 = decode_table(blob) if t == LT else decode_algo(blob)
        canon.append(repr(r))
        canon2.append(repr(r2))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('look tables=%d  look algos=%d  ltInsts=%d  laInsts=%d  '
          'violations=%d  double_run=%s'
          % (sum(1 for x in recs if x[0] == LT),
             sum(1 for x in recs if x[0] == LA),
             len(lt_insts), len(la_insts), bad, same))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
