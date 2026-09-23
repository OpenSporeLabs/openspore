#!/usr/bin/env python3
"""CS-09 cCellLootTableResource oracle (TYPE 0xD92AF091).

115 instances across Spore_Game (53) / Spore_PatchData (53, repack
duplicates) / Spore_EP1_Data (9); 45 unique records. File layout
(evidence-confirmed):

    u32 entries        dead ptr slot
    i32 numEntries     0..9
    f32 minRadius      all 0
    f32 maxRadius      all 0
    f32 initialAlpha   all 1
    f32 expelForce     0 / 1 / 4
    i32 effect         all 0
    u8  mustHavePart   0 / 1 (+3 pad)
    f32 delay          0 / 1
    numEntries * cLootTableEntry (28 B each)

cLootTableEntry (28 B, 7 fields):
    u32  type         Cell(1) / Table(2) / Nothing(0)
    u32  cell         0 or a cell record ref (all resolve)
    u32  table        0 or a loot-table record ref (all resolve)
    f32  weight       ~0.01..90 (percent-ish, not a 0..1 fraction)
    i32  count        0..4
    i32  countDelta   0 / 1
    i32  levelOffset  -3..1

Usage:
    cellloot.py validate           # decode all records, assert domains
    cellloot.py dump <inst_hex>    # dump one record (any package)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
TYPE = 0xD92AF091
CELL_TYPE = 0xDFAD9F51
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/Spore_PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    cell_insts = set()
    loot_insts = set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] == TYPE:
                loot_insts.add(it['inst'] & 0xFFFFFFFF)
                blob = getdata(data, it)
                if blob not in seen:
                    seen[blob] = (rel, it['group'], it['inst'] & 0xFFFFFFFF)
            elif it['type'] == CELL_TYPE:
                cell_insts.add(it['inst'] & 0xFFFFFFFF)
    recs = [(loc[2], blob) for blob, loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, cell_insts, loot_insts


def decode(blob, cell_insts, loot_insts):
    if len(blob) < 36:
        raise ValueError("too small: %d" % len(blob))
    ptr, n, minR, maxR, initA, expelF, effect, mhp = struct.unpack_from(
        '<2i4fiB3x', blob, 0)
    delay = struct.unpack_from('<f', blob, 32)[0]
    if n < 0:
        raise ValueError("negative numEntries %d" % n)
    if len(blob) != 36 + 28 * n:
        raise ValueError("span %d != %d" % (len(blob), 36 + 28 * n))
    off = 36
    entries = []
    unresolved = []
    for _ in range(n):
        t, c, tb = struct.unpack_from('<3I', blob, off)
        w = struct.unpack_from('<f', blob, off + 12)[0]
        cnt, cd, lo = struct.unpack_from('<3i', blob, off + 16)
        if c and c not in cell_insts:
            unresolved.append(('cell', c))
        if tb and tb not in loot_insts:
            unresolved.append(('table', tb))
        entries.append({'type': t, 'cell': c, 'table': tb, 'weight': w,
                        'count': cnt, 'countDelta': cd, 'levelOffset': lo})
        off += 28
    return {'entriesPtr': ptr, 'numEntries': n, 'minRadius': minR,
            'maxRadius': maxR, 'initialAlpha': initA, 'expelForce': expelF,
            'effect': effect, 'mustHavePart': mhp, 'delay': delay,
            'entries': entries, 'unresolved': unresolved}


def issues(r):
    out = []
    if not (0.0 <= r['minRadius'] <= 10.0):
        out.append('minRadius=%r' % r['minRadius'])
    if not (0.0 <= r['maxRadius'] <= 10.0):
        out.append('maxRadius=%r' % r['maxRadius'])
    if not (0.0 <= r['initialAlpha'] <= 2.0):
        out.append('initialAlpha=%r' % r['initialAlpha'])
    if not (0.0 <= r['expelForce'] <= 100.0):
        out.append('expelForce=%r' % r['expelForce'])
    if r['effect'] != 0:
        out.append('effect=%d' % r['effect'])
    if r['mustHavePart'] not in (0, 1):
        out.append('mustHavePart=%d' % r['mustHavePart'])
    if not (0.0 <= r['delay'] <= 10.0):
        out.append('delay=%r' % r['delay'])
    if r['unresolved']:
        out.append('unresolved refs: %s' %
                   ['%s=0x%08x' % (k, v) for k, v in r['unresolved']][:3])
    for e in r['entries']:
        if e['type'] > 5:
            out.append('entry.type=%d' % e['type'])
        if not (0.0 <= e['weight'] <= 1000.0):
            out.append('weight=%r' % e['weight'])
        if not (-10 <= e['count'] <= 64):
            out.append('count=%d' % e['count'])
        if not (-10 <= e['countDelta'] <= 64):
            out.append('countDelta=%d' % e['countDelta'])
        if not (-16 <= e['levelOffset'] <= 16):
            out.append('levelOffset=%d' % e['levelOffset'])
    return out


def main():
    recs, cell_insts, loot_insts = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for inst, blob in recs:
            if inst == want:
                r = decode(blob, cell_insts, loot_insts)
                print('inst=%08x  minR=%.2f maxR=%.2f initA=%.2f expelF=%.2f '
                      'effect=%d mhp=%d delay=%.2f nE=%d'
                      % (inst, r['minRadius'], r['maxRadius'],
                         r['initialAlpha'], r['expelForce'], r['effect'],
                         r['mustHavePart'], r['delay'], r['numEntries']))
                for e in r['entries']:
                    print('  entry: type=%d cell=0x%08x table=0x%08x '
                          'weight=%.3f count=%d cDelta=%d lOff=%d'
                          % (e['type'], e['cell'], e['table'], e['weight'],
                             e['count'], e['countDelta'], e['levelOffset']))
                return
        sys.exit('no record with inst %08x' % want)

    total = len(recs)
    bad = 0
    canon, canon2 = [], []
    for inst, blob in recs:
        try:
            r = decode(blob, cell_insts, loot_insts)
            r2 = decode(blob, cell_insts, loot_insts)
        except ValueError as ex:
            print('DECODE FAIL %08x: %s' % (inst, ex))
            bad += 1
            continue
        probs = issues(r)
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
        canon.append(repr(r))
        canon2.append(repr(r2))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('loot tables: %d  cellInsts=%d  violations=%d  double_run=%s'
          % (total, len(cell_insts), bad, same))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
