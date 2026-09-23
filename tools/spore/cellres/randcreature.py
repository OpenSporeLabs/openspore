#!/usr/bin/env python3
"""CS-11 cCellRandomCreatureResource + cCellPowersResource oracle.

Types 0xF9C3D770 (random creatures) / 0x754BE343 (powers).
Spore_Game + Spore_PatchData (repack) + Spore_EP1_Data:
  - random creatures: 10 unique records (24 instances; EP1 adds 3)
  - powers: 1 record (teleportCost 10, teleportRange 10.0)

File layout (evidence-confirmed):

cCellRandomCreatureResource:
    i32 numEntries       1 / 4
    u32 entries          dead ptr slot
    numEntries * cRandomCreatureEntry (28 B):
        u32 type         0 / 1
        u32 creatureID   soft creature id (NOT a cell-record ref; some ids
                         appear in other resource types, one is absent
                         everywhere -> validate as domain, not resolution)
        f32 weight       1.0
        i32 speedMin     -1 / 0 / 2
        i32 speedMax     -1 / 0 / 1 / 2 / 4
        i32 dangerMin    -1 / 0 / 1 / 2 / 3
        i32 dangerMax    -1 / 0 / 2 / 4 / 5 / 8

cCellPowersResource:
    i32 teleportCost     10
    f32 teleportRange    10.0

Usage:
    randcreature.py validate            # decode all records, assert domains
    randcreature.py dump <inst_hex>     # dump one record (any type)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
RC = 0xF9C3D770
PW = 0x754BE343
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    rc_insts, pw_insts = set(), set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] not in (RC, PW):
                continue
            blob = getdata(data, it)
            key = (it['type'], blob)
            if key not in seen:
                seen[key] = (rel, it['group'], it['inst'] & 0xFFFFFFFF)
            if it['type'] == RC:
                rc_insts.add(it['inst'] & 0xFFFFFFFF)
            else:
                pw_insts.add(it['inst'] & 0xFFFFFFFF)
    recs = [(t, loc[2], blob) for (t, blob), loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, rc_insts, pw_insts


def decode_rc(blob):
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
        t, c = struct.unpack_from('<2I', blob, off)
        w = struct.unpack_from('<f', blob, off + 8)[0]
        smin, smax, dmin, dmax = struct.unpack_from('<4i', blob, off + 12)
        entries.append({'type': t, 'creatureID': c, 'weight': w,
                        'speedMin': smin, 'speedMax': smax,
                        'dangerMin': dmin, 'dangerMax': dmax})
        off += 28
    return {'numEntries': n, 'entriesPtr': ptr, 'entries': entries}


def decode_pw(blob):
    if len(blob) < 8:
        raise ValueError("too small: %d" % len(blob))
    cost, rng = struct.unpack_from('<if', blob, 0)
    return {'teleportCost': cost, 'teleportRange': rng}


def issues_rc(r):
    out = []
    for e in r['entries']:
        if e['type'] not in (0, 1):
            out.append('type=%d' % e['type'])
        if not (0.0 <= e['weight'] <= 100.0) or e['weight'] != e['weight']:
            out.append('weight=%r' % e['weight'])
        for k in ('speedMin', 'speedMax', 'dangerMin', 'dangerMax'):
            v = e[k]
            if not (-16 <= v <= 64):
                out.append('%s=%d' % (k, v))
        if e['speedMin'] != -1 and e['speedMax'] != -1 and \
                e['speedMin'] > e['speedMax']:
            out.append('speedMin>speedMax')
        if e['dangerMin'] != -1 and e['dangerMax'] != -1 and \
                e['dangerMin'] > e['dangerMax']:
            out.append('dangerMin>dangerMax')
    return out


def issues_pw(r):
    out = []
    if not (0 <= r['teleportCost'] <= 10000):
        out.append('teleportCost=%d' % r['teleportCost'])
    if not (0.0 <= r['teleportRange'] <= 1000.0) or \
            r['teleportRange'] != r['teleportRange']:
        out.append('teleportRange=%r' % r['teleportRange'])
    return out


def main():
    recs, rc_insts, pw_insts = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for t, inst, blob in recs:
            if inst == want:
                if t == RC:
                    r = decode_rc(blob)
                    print('randCreature inst=%08x nE=%d' % (inst,
                                                             r['numEntries']))
                    for e in r['entries']:
                        print('  entry: type=%d cid=0x%08x weight=%.3f '
                              'sMin=%d sMax=%d dMin=%d dMax=%d'
                              % (e['type'], e['creatureID'], e['weight'],
                                 e['speedMin'], e['speedMax'],
                                 e['dangerMin'], e['dangerMax']))
                else:
                    r = decode_pw(blob)
                    print('powers inst=%08x cost=%d range=%.3f'
                          % (inst, r['teleportCost'], r['teleportRange']))
                return
        sys.exit('no record with inst %08x' % want)

    bad = 0
    canon, canon2 = [], []
    for t, inst, blob in recs:
        if t == RC:
            try:
                r = decode_rc(blob)
                probs = issues_rc(r)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
            r2 = decode_rc(blob)
        else:
            try:
                r = decode_pw(blob)
                probs = issues_pw(r)
            except ValueError as ex:
                print('DECODE FAIL %08x: %s' % (inst, ex))
                bad += 1
                continue
            r2 = decode_pw(blob)
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
        canon.append(repr(r))
        canon2.append(repr(r2))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('rand creatures=%d  powers=%d  rcInsts=%d  pwInsts=%d  '
          'violations=%d  double_run=%s'
          % (sum(1 for x in recs if x[0] == RC),
             sum(1 for x in recs if x[0] == PW),
             len(rc_insts), len(pw_insts), bad, same))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
