#!/usr/bin/env python3
"""CS-08 cCellStructureResource oracle (TYPE 0x4B9EF6DC).

207 instances across Spore_Game (169) / Spore_PatchData (169, repack
duplicates) / Spore_EP1_Data (38); 149 unique records. File layout
(evidence-confirmed):

    u32 onDeath        effect ref (21 distinct, incl. 0)
    u32 onDeathSmall   mostly 0
    u32 onDeathLarge   mostly 0
    u32 onHatch        mostly 0
    u32 onStartHatch   all 0
    u32 attachments    dead ptr slot
    i32 numAttachments 1..3
    numAttachments * cSPAttachment (40 B each)

cSPAttachment (40 B, 8 fields):
    i32  bone        0 / 3 / -1
    u32  type        0 / 1 / 3 / 4 / 5 / 6
    u32  structure   all 0
    u32  randomCreature  0 or a random-creature ref (10 distinct)
    i32  effectID    128 distinct (negative ok)
    i32  levelMin    0 / -1
    i32  levelMax    0 / 10 / -1
    f32  color[3]    RGB 0..1.5

Cross-check: every non-null cCellCellResource.structure ref (487) resolves to
a real 0x4B9EF6DC instance.

Usage:
    cellstruct.py validate           # decode all records, assert domains
    cellstruct.py dump <inst_hex>    # dump one record (any package)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'dbpf'))
from dbpf import read, getdata  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                    '..', '..', '..'))
TYPE = 0x4B9EF6DC
CELL_TYPE = 0xDFAD9F51
PKGS = ['SPORE/Data/Spore_Game.package',
        'SPORE/Data/Spore_PatchData.package',
        'SPORE/DataEP1/Spore_EP1_Data.package']


def find_records():
    """Unique record blobs plus the full instance set + cell ref set."""
    seen = {}
    insts = set()
    cell_refs = set()
    for rel in PKGS:
        path = os.path.join(REPO, rel)
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] == TYPE:
                insts.add(it['inst'] & 0xFFFFFFFF)
                blob = getdata(data, it)
                if blob not in seen:
                    seen[blob] = (rel, it['group'], it['inst'] & 0xFFFFFFFF)
            elif it['type'] == CELL_TYPE:
                blob = getdata(data, it)
                ref = struct.unpack_from('<I', blob, 0)[0]
                if ref:
                    cell_refs.add(ref)
    recs = [(loc[2], blob) for blob, loc in
            sorted(seen.items(), key=lambda kv: kv[1][2])]
    return recs, insts, cell_refs


def decode(blob):
    if len(blob) < 28:
        raise ValueError("too small: %d" % len(blob))
    h = struct.unpack_from('<7i', blob, 0)
    onDeath, onDeathSmall, onDeathLarge, onHatch, onStartHatch, ptr, nA = h
    if nA < 0:
        raise ValueError("negative numAttachments %d" % nA)
    if len(blob) != 28 + 40 * nA:
        raise ValueError("span %d != %d" % (len(blob), 28 + 40 * nA))
    off = 28
    atts = []
    for _ in range(nA):
        v = struct.unpack_from('<7i', blob, off)
        c = struct.unpack_from('<3f', blob, off + 28)
        atts.append({'bone': v[0], 'type': v[1] & 0xFFFFFFFF,
                     'structure': v[2] & 0xFFFFFFFF,
                     'randomCreature': v[3] & 0xFFFFFFFF,
                     'effectID': v[4], 'levelMin': v[5], 'levelMax': v[6],
                     'color': c})
        off += 40
    return {'onDeath': onDeath & 0xFFFFFFFF,
            'onDeathSmall': onDeathSmall & 0xFFFFFFFF,
            'onDeathLarge': onDeathLarge & 0xFFFFFFFF,
            'onHatch': onHatch & 0xFFFFFFFF,
            'onStartHatch': onStartHatch & 0xFFFFFFFF,
            'attachmentsPtr': ptr, 'numAttachments': nA, 'atts': atts}


def issues(r):
    out = []
    if r['onStartHatch'] != 0:
        out.append('onStartHatch=0x%08x' % r['onStartHatch'])
    for a in r['atts']:
        if a['bone'] not in (0, 3, -1):
            out.append('bone=%d' % a['bone'])
        if a['type'] > 10:
            out.append('type=%d' % a['type'])
        if a['structure'] != 0:
            out.append('structure=0x%08x' % a['structure'])
        if not (-2**31 <= a['effectID'] < 2**31):
            out.append('effectID out of i32')
        if a['levelMin'] not in (0, -1):
            out.append('levelMin=%d' % a['levelMin'])
        if a['levelMax'] not in (0, 10, -1):
            out.append('levelMax=%d' % a['levelMax'])
        for ch in a['color']:
            if ch != ch or not (0.0 <= ch <= 2.0):
                out.append('color=%r' % (a['color'],))
    return out


def main():
    recs, insts, cell_refs = find_records()
    if len(sys.argv) > 1 and sys.argv[1] == 'dump':
        want = int(sys.argv[2], 16)
        for inst, blob in recs:
            if inst == want:
                r = decode(blob)
                print('inst=%08x  onDeath=0x%08x onDeathSmall=0x%08x '
                      'onDeathLarge=0x%08x onHatch=0x%08x '
                      'onStartHatch=0x%08x nAtt=%d'
                      % (inst, r['onDeath'], r['onDeathSmall'],
                         r['onDeathLarge'], r['onHatch'],
                         r['onStartHatch'], r['numAttachments']))
                for a in r['atts']:
                    print('  att: bone=%d type=%d struct=0x%08x '
                          'rand=0x%08x effect=%d lmin=%d lmax=%d '
                          'color=(%.3f,%.3f,%.3f)'
                          % (a['bone'], a['type'], a['structure'],
                             a['randomCreature'], a['effectID'],
                             a['levelMin'], a['levelMax'],
                             a['color'][0], a['color'][1], a['color'][2]))
                return
        sys.exit('no record with inst %08x' % want)

    total = len(recs)
    bad = 0
    refs_ok = sum(1 for x in cell_refs if x in insts)
    canon, canon2 = [], []
    for inst, blob in recs:
        try:
            r = decode(blob)
            r2 = decode(blob)
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
    print('structure records: %d  insts=%d  cellRefs=%d resolved=%d  '
          'violations=%d  double_run=%s'
          % (total, len(insts), len(cell_refs), refs_ok, bad, same))
    sys.exit(1 if bad or refs_ok != len(cell_refs) else 0)


if __name__ == '__main__':
    main()
