#!/usr/bin/env python3
"""Spore DBPF (v3) reader.
Header (96B): magic(4) major(4) minor(4) pad(20) idxMaj(4) idxCount(4) pad(4)
              idxSize(4) pad(12) idxMinor(4) idxOffset(4) pad(28)
Index: flags(4) [typeID(4)] [groupID(4)] [unknown(4)] then items:
  [typeID(4)] [groupID(4)] instanceID(4) chunkOff(4|8) cSize(4, bit31 set)
  memSize(4) comp(2: 0=none 0xffff=refpack) saved(1) pad(1)
Usage: dbpf.py [--out DIR] <file> [exts|list <pat>|get <idx>|find <pat>|dumpdir|decompress <idx>]
"""
import struct
import sys
import os
import argparse
from collections import Counter


def le(d, o, f='I'):
    return struct.unpack_from('<' + f, d, o)[0]


def type4cc(t):
    return struct.pack('<I', t).decode('latin1', 'replace')


def read(pkg):
    data = open(pkg, 'rb').read()
    magic = data[:4].decode('latin1')
    big = magic == 'DBBF'
    assert magic in ('DBPF', 'DBBF'), f"bad magic {magic!r}"
    major, minor = le(data, 4), le(data, 8)
    idxMaj, idxCount = le(data, 0x20), le(data, 0x24)
    idxSize = le(data, 0x2C)
    idxMinor, idxOff = le(data, 0x3C), le(data, 0x40)
    print(f"# {os.path.basename(pkg)} magic={magic} v{major}.{minor} idxCount={idxCount} idxSize={idxSize} idxOff=0x{idxOff:x} idxMinor={idxMinor} filesize={len(data)}", file=sys.stderr)

    o = idxOff
    flags = le(data, o); o += 4
    typeID = -1; groupID = -1
    if flags & 1:
        typeID = le(data, o); o += 4
    if flags & 2:
        groupID = le(data, o); o += 4
    if flags & 4:
        o += 4
    items = []
    for i in range(idxCount):
        t = typeID; g = groupID
        if t == -1:
            t = le(data, o); o += 4
        if g == -1:
            g = le(data, o); o += 4
        inst = le(data, o); o += 4
        if big:
            off = struct.unpack_from('<Q', data, o)[0]; o += 8
        else:
            off = le(data, o); o += 4
        csize = le(data, o) & 0x7fffffff; o += 4
        msize = le(data, o); o += 4
        comp = le(data, o, 'H'); o += 2
        saved = data[o]; o += 2
        items.append(dict(type=t, group=g, inst=inst, off=off, csize=csize,
                          msize=msize, comp=(comp == 0xFFFF), saved=saved))
    return data, items


def qfs_decompress(buf):
    """EA QFS (RefPack) decompression, per community-documented spec (Sims2Wiki DBPF Compression)."""
    if buf[0] not in (0x10, 0x50) or buf[1] != 0xFB:
        raise ValueError(f"bad QFS header {buf[:2].hex()}")
    decomp_size = (buf[2] << 16) | (buf[3] << 8) | buf[4]
    pin = 5
    out = bytearray(decomp_size)
    size = 0
    n = len(buf)
    while size < decomp_size:
        c = buf[pin]; pin += 1
        if c >= 252:
            npd = c & 3
            ntc = 0
            co = 0
        elif c >= 224:
            npd = ((c & 0x1F) << 2) + 4
            ntc = 0
            co = 0
        elif c >= 192:
            b1, b2, b3 = buf[pin], buf[pin + 1], buf[pin + 2]; pin += 3
            npd = c & 3
            ntc = ((c & 0x0C) << 6) + b3 + 5
            co = ((c & 0x10) << 12) + (b1 << 8) + b2 + 1
        elif c >= 128:
            b1, b2 = buf[pin], buf[pin + 1]; pin += 2
            npd = (b1 & 0xC0) >> 6
            ntc = (c & 0x3F) + 4
            co = ((b1 & 0x3F) << 8) + b2 + 1
        else:
            b1 = buf[pin]; pin += 1
            npd = c & 3
            ntc = ((c & 0x1C) >> 2) + 3
            co = ((c & 0x60) << 3) + b1 + 1
        if npd > 0:
            out[size:size + npd] = buf[pin:pin + npd]
            pin += npd
            size += npd
        for _ in range(ntc):
            out[size] = out[size - co]
            size += 1
    return bytes(out)


def getdata(data, it):
    raw = data[it['off']:it['off'] + it['csize']]
    if it['comp']:
        return qfs_decompress(raw)
    return raw


def main(argv=None):
    default_out = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'out')
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--out', default=default_out,
                    help=f'output directory for extracted records (default: {default_out})')
    ap.add_argument('file', help='path to a .package file')
    ap.add_argument('cmd', nargs='?', default='exts',
                    choices=['exts', 'list', 'get', 'find', 'dumpdir', 'decompress'])
    ap.add_argument('arg', nargs='?', default='',
                    help='pattern (list/find) or record index (get/decompress)')
    a = ap.parse_args(argv)

    data, items = read(a.file)
    os.makedirs(a.out, exist_ok=True)

    if a.cmd == 'exts':
        c = Counter(it['type'] for it in items)
        for t, n in c.most_common(60):
            print(f"{n:8d}  type={type4cc(t)!r}  (0x{t:08x})")
    elif a.cmd == 'list':
        for i, it in enumerate(items):
            s = type4cc(it['type'])
            if a.arg and a.arg not in s and a.arg not in f"{it['group']:x}{it['inst']:x}":
                continue
            print(f"{i:6d}  {s}  g=0x{it['group']:08x} i=0x{it['inst']:08x} off=0x{it['off']:x} csize={it['csize']} msize={it['msize']} comp={it['comp']}")
    elif a.cmd == 'find':
        for i, it in enumerate(items):
            s = type4cc(it['type'])
            if a.arg and a.arg not in s and a.arg not in f"{it['group']:x}{it['inst']:x}":
                continue
            print(f"{i:6d}  {s}  g=0x{it['group']:08x} i=0x{it['inst']:08x} off=0x{it['off']:x} msize={it['msize']}")
    elif a.cmd == 'get':
        i = int(a.arg)
        it = items[i]
        blob = getdata(data, it)
        safe = type4cc(it['type']).replace('\x00', '_').replace('\\', '_')
        fn = os.path.join(a.out, f"{safe}_{it['group']:x}_{it['inst']:x}_{i}")
        open(fn, 'wb').write(blob)
        print(f"wrote {fn} ({len(blob)} bytes)")
    elif a.cmd == 'decompress':
        i = int(a.arg)
        it = items[i]
        blob = getdata(data, it)
        safe = type4cc(it['type']).replace('\x00', '_').replace('\\', '_')
        fn = os.path.join(a.out, f"decomp_{safe}_{it['group']:x}_{it['inst']:x}_{i}")
        open(fn, 'wb').write(blob)
        print(f"wrote {fn} ({len(blob)} bytes, comp={it['comp']})")
    elif a.cmd == 'dumpdir':
        for i, it in enumerate(items):
            if it['group'] == 0x1C7AC81 and it['inst'] == 0x1C7AC81:
                blob = getdata(data, it)
                print(f"dir record idx={i} msize={it['msize']} csize={it['csize']}")
                print(blob.decode('latin1', 'replace')[:3000])
                fn = os.path.join(a.out, 'dirprop')
                open(fn, 'wb').write(blob)
                print(f"wrote {fn}")
                break
    return 0


if __name__ == '__main__':
    sys.exit(main())
