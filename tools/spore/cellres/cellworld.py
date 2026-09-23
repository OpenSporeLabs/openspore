#!/usr/bin/env python3
"""CS-06 cCellWorldResource oracle (TYPE 0x9B8E862F).

37 records across Spore_Game / Spore_PatchData / Spore_EP1_Data (13 unique;
PatchData is a byte-identical repack). File layout (evidence-confirmed):

    u32 numPopulate
    u32 populatePtr     (dead serialized pointer slot; observed 0 / 0x10)
    u32 numAdvect
    u32 advectPtr       (dead serialized pointer slot; observed 0 / 0x28 / 0x100)
    numPopulate * cLevelEntry   (12 B each)
    numAdvect   * cAdvectEntry  (24 B each)

cLevelEntry (12 B):
    u32  populate     cCellDataReference key (cell resource ref)
    u8   startTile    0/1
    u8[2] pad
    u32  playerSize   1..10 (= scale) or 0xFFFFFFFF (= "any")

cAdvectEntry (24 B) — DRIFT: the SDK types strength/variance/period as int,
but the file stores them as f32 (observed clean floats 0.5..3.5, 0.0, 1.0):
    u32  stageScale   1..13 observed
    i32  playerSize   -1 (= any) .. 11
    f32  strength     0.5..3.5
    f32  variance     0.0
    f32  period       1.0
    u32  advectID     flow-field resource ref

Usage:
    cellworld.py validate            # decode all records, assert domains
    cellworld.py dump <inst_hex>     # dump one record (any package)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
TYPE = 0x9B8E862F
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/Spore_PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] == TYPE:
                blob = getdata(data, it)
                if blob not in seen:
                    seen[blob] = (rel, it['group'], it['inst'])
    return [(loc[1], loc[2], blob) for blob, loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]


def decode(blob):
    if len(blob) < 16:
        raise ValueError("too small: %d" % len(blob))
    nPop, popPtr, nAdv, advPtr = struct.unpack_from('<4i', blob, 0)
    if nPop < 0 or nAdv < 0:
        raise ValueError("negative counts %d/%d" % (nPop, nAdv))
    if len(blob) != 16 + 12 * nPop + 24 * nAdv:
        raise ValueError("span %d != %d" % (len(blob), 16 + 12 * nPop + 24 * nAdv))
    off = 16
    populate = []
    for _ in range(nPop):
        ref, st, _a, _b = struct.unpack_from('<i3b', blob, off)
        ps, = struct.unpack_from('<I', blob, off + 8)
        populate.append({'populate': ref, 'startTile': st, 'playerSize': ps})
        off += 12
    advect = []
    for _ in range(nAdv):
        s0, ps = struct.unpack_from('<2i', blob, off)
        strength, variance, period = struct.unpack_from('<3f', blob, off + 8)
        adv, = struct.unpack_from('<I', blob, off + 20)
        advect.append({'stageScale': s0, 'playerSize': ps, 'strength': strength,
                       'variance': variance, 'period': period, 'advectID': adv})
        off += 24
    return {'numPopulate': nPop, 'populatePtr': popPtr,
            'numAdvect': nAdv, 'advectPtr': advPtr,
            'populate': populate, 'advect': advect}


def issues(r):
    out = []
    if r['numPopulate'] > 64:
        out.append('numPopulate=%d' % r['numPopulate'])
    if r['numAdvect'] > 64:
        out.append('numAdvect=%d' % r['numAdvect'])
    for e in r['populate']:
        if e['startTile'] not in (0, 1):
            out.append('level.startTile=%d' % e['startTile'])
        ps = e['playerSize']
        if ps != 0xFFFFFFFF and (ps == 0 or ps > 10):
            out.append('level.playerSize=0x%08x' % ps)
    for e in r['advect']:
        if not (0 <= e['stageScale'] <= 30):
            out.append('advect.stageScale=%d' % e['stageScale'])
        if not (-1 <= e['playerSize'] <= 30):
            out.append('advect.playerSize=%d' % e['playerSize'])
        for k in ('strength', 'variance', 'period'):
            v = e[k]
            if not (v == v) or abs(v) > 10.0:  # NaN / range
                out.append('advect.%s=%r' % (k, v))
    return out


def main():
    recs = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for inst, _g, blob in [(l, i, b) for (g, i, b) in recs]:
            if inst == want:
                r = decode(blob)
                print('inst=%08x' % inst)
                print('  numPopulate=%d populatePtr=0x%x numAdvect=%d advectPtr=0x%x'
                      % (r['numPopulate'], r['populatePtr'], r['numAdvect'], r['advectPtr']))
                for e in r['populate']:
                    print('  level: populate=0x%08x startTile=%d playerSize=%d'
                          % (e['populate'], e['startTile'], e['playerSize']))
                for e in r['advect']:
                    print('  advect: stage=%d player=%d strength=%.3f variance=%.3f '
                          'period=%.3f advectID=0x%08x'
                          % (e['stageScale'], e['playerSize'], e['strength'],
                             e['variance'], e['period'], e['advectID']))
                return
        sys.exit('no record with inst %08x' % want)

    total = len(recs)
    bad = 0
    first = None
    for group, inst, blob in recs:
        try:
            r = decode(blob)
        except ValueError as ex:
            print('DECODE FAIL %08x: %s' % (inst, ex))
            bad += 1
            continue
        if first is None:
            first = r
        probs = issues(r)
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
    # double-run byte identity: decode twice, compare canonical form
    canon = []
    for _g, _i, blob in recs:
        r = decode(blob)
        canon.append(repr((r['numPopulate'], r['populatePtr'], r['numAdvect'],
                           r['advectPtr'], r['populate'], r['advect'])))
    canon2 = []
    for _g, _i, blob in recs:
        r = decode(blob)
        canon2.append(repr((r['numPopulate'], r['populatePtr'], r['numAdvect'],
                            r['advectPtr'], r['populate'], r['advect'])))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('cellworld records: %d  violations=%d  double_run=%s'
          % (total, bad, same))
    if first is not None:
        print('  sample: numPopulate=%d numAdvect=%d'
              % (first['numPopulate'], first['numAdvect']))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
