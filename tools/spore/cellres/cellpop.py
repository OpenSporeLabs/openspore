#!/usr/bin/env python3
"""CS-07 cCellPopulateResource oracle (TYPE 0xDA141C1B).

21 unique records across Spore_Game / Spore_PatchData / Spore_EP1_Data
(the plan's "20" counted Spore_Game only). File layout (evidence-confirmed):

    u32 scale          0 = any, 3 / 4 observed
    u32 maskTexture    all 0 (dead ref)
    u32 numMarkers
    u32 markersPtr     dead ptr slot; observed 0 / 16 (= header size)
    numMarkers * cMarker (76 B each)

cMarker (76 B, 19 fields) — several fields are all-zero dead slots:
    i32  field_0      0
    i32  field_4      0
    i32  field_8      0
    f32  zOffset      0..25
    f32  zOffsetMax   0..35
    i32  field_14     0
    u32  distributeCell  0 (null) or cell record ref (all non-null resolve)
    u32  clusterCell   0 or cell record ref (all 43 non-null resolve)
    u32  encounterPopulate  all 0
    u32  plantType    0..2
    u32  type         0..2
    f32  count        -1 (any) .. 800
    f32  count_easy   -1 .. 8
    f32  count_med    -1 .. 8
    f32  count_hard   -1 .. 7
    i32  size         0..12
    i32  parts        0 / 3 / 4 / 5
    i32  linear       0 / 1
    i32  encounterScale  0

Usage:
    cellpop.py validate            # decode all records, assert domains
    cellpop.py dump <inst_hex>     # dump one record (any package)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
TYPE = 0xDA141C1B
CELL_TYPE = 0xDFAD9F51
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/Spore_PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    seen = {}
    cell_insts = set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] == CELL_TYPE:
                cell_insts.add(it['inst'] & 0xFFFFFFFF)
            if it['type'] == TYPE:
                blob = getdata(data, it)
                if blob not in seen:
                    seen[blob] = (rel, it['group'], it['inst'])
    recs = [(loc[1], loc[2], blob) for blob, loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, cell_insts


def decode(blob, cell_insts):
    if len(blob) < 16:
        raise ValueError("too small: %d" % len(blob))
    scale, mask, nM, ptr = struct.unpack_from('<4i', blob, 0)
    if nM < 0:
        raise ValueError("negative numMarkers %d" % nM)
    if len(blob) != 16 + 76 * nM:
        raise ValueError("span %d != %d" % (len(blob), 16 + 76 * nM))
    off = 16
    markers = []
    unresolved = []
    for _ in range(nM):
        v = struct.unpack_from('<19i', blob, off)
        m = {'field_0': v[0], 'field_4': v[1], 'field_8': v[2],
             'zOffset': struct.unpack_from('<f', blob, off + 12)[0],
             'zOffsetMax': struct.unpack_from('<f', blob, off + 16)[0],
             'field_14': v[5], 'distributeCell': v[6] & 0xFFFFFFFF,
             'clusterCell': v[7] & 0xFFFFFFFF,
             'encounterPopulate': v[8] & 0xFFFFFFFF,
             'plantType': v[9] & 0xFFFFFFFF, 'type': v[10] & 0xFFFFFFFF,
             'count': struct.unpack_from('<f', blob, off + 44)[0],
             'count_easy': struct.unpack_from('<f', blob, off + 48)[0],
             'count_med': struct.unpack_from('<f', blob, off + 52)[0],
             'count_hard': struct.unpack_from('<f', blob, off + 56)[0],
             'size': v[15], 'parts': v[16], 'linear': v[17],
             'encounterScale': v[18]}
        if m['distributeCell'] and m['distributeCell'] not in cell_insts:
            unresolved.append(('distributeCell', m['distributeCell']))
        if m['clusterCell'] and m['clusterCell'] not in cell_insts:
            unresolved.append(('clusterCell', m['clusterCell']))
        markers.append(m)
        off += 76
    return {'scale': scale, 'maskTexture': mask, 'numMarkers': nM,
            'markersPtr': ptr, 'markers': markers, 'unresolved': unresolved}


def issues(r):
    out = []
    if r['scale'] not in (0, 1, 2, 3, 4):
        out.append('scale=%d' % r['scale'])
    if r['maskTexture'] != 0:
        out.append('maskTexture=0x%08x' % r['maskTexture'])
    if r['numMarkers'] > 64:
        out.append('numMarkers=%d' % r['numMarkers'])
    if r['unresolved']:
        out.append('unresolved refs: %s' %
                   ['%s=0x%08x' % (k, v) for k, v in r['unresolved']][:3])
    for m in r['markers']:
        if not (0.0 <= m['zOffset'] <= 100.0):
            out.append('zOffset=%r' % m['zOffset'])
        if not (0.0 <= m['zOffsetMax'] <= 100.0):
            out.append('zOffsetMax=%r' % m['zOffsetMax'])
        if m['plantType'] > 10:
            out.append('plantType=%d' % m['plantType'])
        if m['type'] > 10:
            out.append('type=%d' % m['type'])
        for k in ('count', 'count_easy', 'count_med', 'count_hard'):
            v = m[k]
            if not (v == v) or v < -1.0 or v > 1000.0:
                out.append('%s=%r' % (k, v))
        if not (0 <= m['size'] <= 30):
            out.append('size=%d' % m['size'])
        if m['parts'] < 0 or m['parts'] > 30:
            out.append('parts=%d' % m['parts'])
        if m['linear'] not in (0, 1):
            out.append('linear=%d' % m['linear'])
    return out


def main():
    recs, cell_insts = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for _g, inst, blob in recs:
            if inst == want:
                r = decode(blob, cell_insts)
                print('inst=%08x' % inst)
                print('  scale=%d maskTexture=0x%x numMarkers=%d markersPtr=0x%x'
                      % (r['scale'], r['maskTexture'], r['numMarkers'],
                         r['markersPtr']))
                for m in r['markers']:
                    print('  marker: dist=0x%08x clust=0x%08x enc=0x%08x '
                          'plant=%d type=%d count=%.2f cE=%.2f cM=%.2f cH=%.2f '
                          'size=%d parts=%d lin=%d zOff=%.1f zOffMax=%.1f'
                          % (m['distributeCell'], m['clusterCell'],
                             m['encounterPopulate'], m['plantType'], m['type'],
                             m['count'], m['count_easy'], m['count_med'],
                             m['count_hard'], m['size'], m['parts'],
                             m['linear'], m['zOffset'], m['zOffsetMax']))
                return
        sys.exit('no record with inst %08x' % want)

    total = len(recs)
    bad = 0
    markers = 0
    canon = []
    canon2 = []
    for _g, inst, blob in recs:
        try:
            r = decode(blob, cell_insts)
            r2 = decode(blob, cell_insts)
        except ValueError as ex:
            print('DECODE FAIL %08x: %s' % (inst, ex))
            bad += 1
            continue
        markers += r['numMarkers']
        probs = issues(r)
        if probs:
            bad += 1
            print('ISSUES %08x: %s' % (inst, '; '.join(probs)))
        key = (r['scale'], r['maskTexture'], r['numMarkers'], r['markersPtr'],
               r['markers'])
        canon.append(repr(key))
        canon2.append(repr((r2['scale'], r2['maskTexture'], r2['numMarkers'],
                            r2['markersPtr'], r2['markers'])))
    same = 'identical' if canon == canon2 else 'DIFFER'
    print('populate records: %d  markers=%d  violations=%d  double_run=%s'
          % (total, markers, bad, same))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
