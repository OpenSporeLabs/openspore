#!/usr/bin/env python3
"""RW4 container parser (Spore variant) — header, manifest, type codes, section infos, object type codes."""
import struct
import sys

MAGIC = bytes([0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32, 0x00, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x20, 0x04, 0x00,
               0x34, 0x35, 0x34, 0x00, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00])


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


def i32(b, o):
    return struct.unpack_from('<i', b, o)[0]


TYPES = {0x10030: 'BaseResource', 0x10031: '?', 0x10032: '?', 0x10010: '?', 0x10004: 'SectionManifest',
         0x10005: 'SectionTypes', 0x10006: 'SectionExternalArenas', 0x10007: 'SectionSubReferences',
         0x10008: 'SectionAtoms', 0x20003: 'Raster', 0x20001: 'VertexDescription', 0x20002: 'VertexBuffer',
         0x20004: 'IndexBuffer', 0x20005: 'SkinMatrixBuffer', 0x30001: 'AnimationSkin', 0x40001: 'Mesh',
         0x50001: 'MeshCompiledStateLink', 0x60001: 'CompiledState', 0x70001: 'SkinsInK',
         0x80001: 'SkeletonsInK', 0x80002: 'Skeleton', 0x80003: 'BBox', 0x90001: 'MorphHandle',
         0x90002: 'TriangleKDTreeProcedural', 0xA0001: 'Animations', 0xA0002: 'KeyframeAnim',
         0xB0001: 'BlendShape', 0xB0002: 'BlendShapeBuffer', 0xC0001: 'TextureOverride'}


def parse(path):
    with open(path, 'rb') as f:
        b = f.read()
    assert b[:28] == MAGIC, f"bad magic {b[:12].hex()}"
    ftype = u32(b, 0x1C)
    tname = {1: 'MODEL', 0x04000000: 'TEXTURE', 0xCAFED00D: 'SPECIAL'}.get(ftype, f"0x{ftype:08x}")
    objCount = u32(b, 0x20); sectionCount = u32(b, 0x24)
    f28 = u32(b, 0x28); f2C = u32(b, 0x2C)
    pSectionInfo = u32(b, 0x30); f34 = u32(b, 0x34)
    pBufferData = u32(b, 0x44); f48 = u32(b, 0x48); bufSize = u32(b, 0x4C)
    print(f"### {path}")
    print(f"type={tname} objCount={objCount} sectionCount={sectionCount} f28={f28} pSectionInfo=0x{pSectionInfo:x} pBufferData=0x{pBufferData:x} bufSize={bufSize}")
    # manifest at 0x98
    mo = 0x98
    assert u32(b, mo) == 0x10004, f"manifest tc 0x{u32(b, mo):x}"
    f0, f4 = i32(b, mo + 4), i32(b, mo + 8)
    o1, o2, o3, o4 = u32(b, mo + 0xC), u32(b, mo + 0x10), u32(b, mo + 0x14), u32(b, mo + 0x18)
    # types
    to = mo + o1
    assert u32(b, to) == 0x10005, f"types tc 0x{u32(b, to):x}"
    n = u32(b, to + 4)
    codes = [u32(b, to + 8 + 4 * i) for i in range(n)]
    print(f"manifest: f0={f0} f4={f4} types@0x{to:x}(n={n}) arenas@0x{mo + o2:x} subref@0x{mo + o3:x} atoms@0x{mo + o4:x}")
    print("typecodes: " + ", ".join(f"0x{c:x}:{TYPES.get(c, '?')}" for c in codes))
    # section infos
    print("sections:")
    for i in range(sectionCount):
        o = pSectionInfo + 24 * i
        pData, f04, size, align, tci, tc = u32(b, o), u32(b, o + 4), i32(b, o + 8), i32(b, o + 0xC), i32(b, o + 0x10), i32(b, o + 0x14)
        ap = pData + pBufferData if tc == 0x10030 else pData
        print(f"  [{i}] tc=0x{tc:x}:{TYPES.get(tc, '?')} tcIdx={tci} size={size} align={align} data@0x{ap:x}")
    return b


if __name__ == '__main__':
    for p in sys.argv[1:]:
        parse(p)
        print()
