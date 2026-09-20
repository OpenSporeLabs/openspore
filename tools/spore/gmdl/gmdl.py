#!/usr/bin/env python3
"""Spore GMDL (GameModel, RenderAsset 0xE6BCE5) reader.

Byte layout (little-endian), verified against version-8 game samples:

    version          u32
    refCount         u32
      refCount *     { instanceID, groupID, typeID } u32 x3
    meshCount        u32
    boundingBox      min Vector3 (3 f32) + max Vector3 (3 f32)
    boundingRadius   f32
    numIndexBuffers  u32
      each: primType u32, indexCount u32, indexBits u32, bufferSize u32,
            then indexCount * (indexBits/8) bytes of raw index data
    numVertexDescriptors u32
      each: elementCount u32, then elementCount * RWVertexElement (12B)
            RWVertexElement: stream u16, offset u16, declType u8, declMethod u8,
                            declUsage u8, usageIndex u8, typeCode u32
    numVertexBuffers u32
      each: descriptorIdx u32, vertexCount u32, bufferSize u32, then raw bytes
    meshCount *      { indexBufferIdx u32, vertexBufferIdx u32 }
    meshCount *      materialID u32
    unk              u32 (observed 0)
    materialInfoCount u32
      each: [if version != 9: entryCount u32]
            entryCount * materialInfo entry:
               dataIndex u32
               if 0x20D (texture set): texCount u32, then texCount * { sampler u32,
                   12B extra, instID u32, grpID u32 }
               else: skip ShaderData.getDataSize(dataIndex) bytes
    boneRangeCount   u32
      each: start u32, count u32
    animDataCount    u32
      each: 2 * Transform (64B each) + field u32 + ResourceKey (12B)
            + bakedDeformGroupCount u32 + bakedDeformGroupCount * u32
    unknownKey       { instanceID, groupID, typeID } u32 x3

Usage: gmdl.py <inspect|dump> <file>
  inspect  print a human summary (bbox, buffers, vertex layout, materials)
  dump     raw section walk with offsets (for format development)
"""
import struct
import sys

# ShaderData.getDataSize table (RenderWare ShaderData id -> byte size), used to
# skip materialInfo entries that are not texture sets.
SHADER_DATA_SIZE = {
    0x201: 8, 0x202: 20, 0x203: 8, 0x204: 16, 0x205: 20, 0x206: 256, 0x208: 8,
    0x209: 4, 0x20A: 64, 0x20B: 64, 0x20C: 16, 0x20E: 8, 0x20F: 8, 0x210: 20,
    0x211: 20, 0x212: 32, 0x213: 48, 0x216: 1, 0x217: 1, 0x21C: 32, 0x21E: 16,
    0x220: 16, 0x223: 164, 0x224: 152, 0x226: 16, 0x22D: 16, 0x22E: 16, 0x22F: 16428,
    0x230: 4, 0x231: 12, 0x232: 1, 0x233: 4, 0x235: 4, 0x236: 4, 0x237: 1, 0x238: 1,
    0x23B: 96, 0x23C: 48, 0x241: 64, 0x242: 64, 0x243: 144, 0x244: 1, 0x245: 12,
    0x246: 20, 0x247: 16, 0x248: 16, 0x24A: 48, 0x255: 32, 0x256: 16,
}
SHADER_DATA_0x20D = 100  # texture set (parsed explicitly, not skipped)

DECLTYPE = {0: 'FLOAT1', 1: 'FLOAT2', 2: 'FLOAT3', 3: 'FLOAT4', 4: 'D3DCOLOR', 5: 'UBYTE4',
            6: 'SHORT2', 7: 'SHORT4', 8: 'UBYTE4N', 9: 'SHORT2N', 10: 'SHORT4N',
            11: 'USHORT2N', 12: 'USHORT4N', 13: 'UDEC3', 14: 'DEC3N', 15: 'FLOAT16_2', 16: 'FLOAT16_4'}
DECLTYPE_SIZE = {0: 4, 1: 8, 2: 12, 3: 16, 4: 4, 5: 4, 6: 4, 7: 8, 8: 4, 9: 4,
                 10: 8, 11: 4, 12: 8, 13: 4, 14: 4, 15: 4, 16: 8}
DECLUSAGE = {0: 'POSITION', 1: 'BLENDWEIGHT', 2: 'BLENDINDICES', 3: 'NORMAL', 4: 'PSIZE',
             5: 'TEXCOORD', 6: 'TANGENT', 7: 'BINORMAL', 8: 'TESSFACTOR', 9: 'POSITIONT',
             10: 'COLOR', 11: 'FOG', 12: 'DEPTH', 13: 'SAMPLE'}
PRIM = {1: 'POINTLIST', 2: 'LINELIST', 3: 'LINESTRIP', 4: 'TRIANGLELIST', 5: 'TRIANGLESTRIP', 6: 'TRIANGLEFAN'}


def u(b, o, f='I'):
    return struct.unpack_from('<' + f, b, o)[0]


def f32(b, o):
    return struct.unpack_from('<f', b, o)[0]


def shader_data_size(k):
    return SHADER_DATA_SIZE.get(k, 0)


class Gmdl:
    def __init__(self, path):
        self.path = path
        self.b = open(path, 'rb').read()
        self.parse()

    def parse(self):
        b = self.b
        o = 0
        self.version = u(b, o); o += 4
        self.refCount = u(b, o); o += 4
        self.refs = []
        for _ in range(self.refCount):
            self.refs.append((u(b, o), u(b, o + 4), u(b, o + 8)))
            o += 12

        self.meshCount = u(b, o); o += 4
        self.bboxMin = [f32(b, o + 4 * x) for x in range(3)]
        self.bboxMax = [f32(b, o + 4 * x + 12) for x in range(3)]
        o += 24
        self.radius = f32(b, o); o += 4

        self.numIndexBuffers = u(b, o); o += 4
        self.indexBuffers = []
        for _ in range(self.numIndexBuffers):
            prim = u(b, o); cnt = u(b, o + 4); bits = u(b, o + 8); sz = u(b, o + 12)
            o += 16
            stride = cnt * max(1, bits // 8)
            data = b[o:o + stride]; o += stride
            self.indexBuffers.append(dict(prim=prim, count=cnt, bits=bits, size=sz, data=data))

        self.numVertexDescriptors = u(b, o); o += 4
        self.vertexDescriptors = []
        for _ in range(self.numVertexDescriptors):
            ec = u(b, o); o += 4
            elems = []
            for _ in range(ec):
                stream = u(b, o, 'H'); off = u(b, o + 2, 'H')
                typ = b[o + 4]; meth = b[o + 5]; usage = b[o + 6]; uidx = b[o + 7]
                tcode = u(b, o + 8); o += 12
                elems.append(dict(stream=stream, off=off, type=typ, method=meth,
                                  usage=usage, usageIndex=uidx, typeCode=tcode))
            self.vertexDescriptors.append(elems)

        self.numVertexBuffers = u(b, o); o += 4
        self.vertexBuffers = []
        for _ in range(self.numVertexBuffers):
            di = u(b, o); vc = u(b, o + 4); sz = u(b, o + 8); o += 12
            data = b[o:o + sz]; o += sz
            self.vertexBuffers.append(dict(descIdx=di, vertexCount=vc, size=sz, data=data))

        self.meshes = []
        for _ in range(self.meshCount):
            self.meshes.append((u(b, o), u(b, o + 4)))
            o += 8
        self.materialIDs = [u(b, o + 4 * m) for m in range(self.meshCount)]
        o += 4 * self.meshCount
        self.unk = u(b, o); o += 4

        self.materialInfos = []
        mCount = u(b, o); o += 4
        for _ in range(mCount):
            entryCount = u(b, o); o += 4 if self.version != 9 else 0
            entries = []
            for _ in range(entryCount):
                di = u(b, o); o += 4
                if di == 0x20D:
                    tc = u(b, o); o += 4
                    texs = []
                    for _ in range(tc):
                        si = u(b, o); o += 4
                        ex = b[o:o + 12]; o += 12
                        ii = u(b, o); gg = u(b, o + 4); o += 8
                        texs.append((si, ex, ii, gg))
                    entries.append(('texset', di, tc, texs))
                else:
                    sz = shader_data_size(di)
                    o += sz
                    entries.append(('shader', di, sz, None))
            self.materialInfos.append(entries)

        self.boneRanges = []
        nbr = u(b, o); o += 4
        for _ in range(nbr):
            a = u(b, o); c = u(b, o + 4); o += 8
            self.boneRanges.append((a, c))

        self.animDatas = []
        nad = u(b, o); o += 4
        for _ in range(nad):
            o += 64 * 2 + 4 + 12  # 2 Transform (64B) + field + ResourceKey
            bc = u(b, o); o += 4
            o += bc * 4
            self.animDatas.append(bc)

        self.unknownKey = (u(b, o), u(b, o + 4), u(b, o + 8))
        o += 12
        self.finalOffset = o

    def matches(self):
        return self.finalOffset == len(self.b)

    def vertex_stride(self, desc):
        if not desc:
            return 0
        return max(e['off'] + DECLTYPE_SIZE.get(e['type'], 0) for e in desc)

    def inspect(self):
        print(f"== {self.path}: version={self.version} refs={self.refCount} meshCount={self.meshCount}")
        print(f"   bbox min=({self.bboxMin[0]:.3f},{self.bboxMin[1]:.3f},{self.bboxMin[2]:.3f}) "
              f"max=({self.bboxMax[0]:.3f},{self.bboxMax[1]:.3f},{self.bboxMax[2]:.3f}) radius={self.radius:.4f}")
        print(f"   indexBuffers={self.numIndexBuffers}")
        for k, ib in enumerate(self.indexBuffers):
            print(f"     [{k}] prim={ib['prim']}:{PRIM.get(ib['prim'], '?')} "
                  f"count={ib['count']} bits={ib['bits']} bufSize={ib['size']}")
        print(f"   vertexDescriptors={self.numVertexDescriptors}")
        for k, desc in enumerate(self.vertexDescriptors):
            print(f"     [{k}] elements={len(desc)} stride~{self.vertex_stride(desc)}B")
            for e in desc:
                print(f"        stream={e['stream']} off={e['off']} "
                      f"type={e['type']}:{DECLTYPE.get(e['type'], '?')} meth={e['method']} "
                      f"usage={e['usage']}:{DECLUSAGE.get(e['usage'], '?')} ui={e['usageIndex']} typeCode={e['typeCode']}")
        print(f"   vertexBuffers={self.numVertexBuffers}")
        for k, vb in enumerate(self.vertexBuffers):
            stride = self.vertex_stride(self.vertexDescriptors[vb['descIdx']]) if vb['descIdx'] < len(self.vertexDescriptors) else 0
            print(f"     [{k}] descIdx={vb['descIdx']} vtxCount={vb['vertexCount']} bufSize={vb['size']} (stride~{stride}B)")
        for m, (ibi, vbi) in enumerate(self.meshes):
            print(f"   mesh[{m}] idxBuf={ibi} vtxBuf={vbi} materialID=0x{self.materialIDs[m]:08x}")
        print(f"   unk={self.unk} materialInfos={len(self.materialInfos)}")
        for mi, entries in enumerate(self.materialInfos):
            print(f"     materialInfo[{mi}] entries={len(entries)}")
            for kind, di, extra, payload in entries:
                if kind == 'texset':
                    print(f"       texset id=0x{di:03x} texCount={extra}")
                    for si, ex, ii, gg in payload:
                        print(f"         sampler={si} extra={ex.hex()} inst=0x{ii:08x} grp=0x{gg:08x}")
                else:
                    print(f"       shader id=0x{di:03x} size={extra}")
        print(f"   boneRanges={len(self.boneRanges)} animDatas={len(self.animDatas)}")
        ik, ig, it = self.unknownKey
        print(f"   unknownKey inst=0x{ik:08x} grp=0x{ig:08x} type=0x{it:08x}")
        print(f"   final offset 0x{self.finalOffset:x} / file 0x{len(self.b):x}  "
              f"{'MATCH' if self.matches() else 'MISMATCH'}")

    def dump(self):
        print(f"== raw dump {self.path} (file 0x{len(self.b):x})")
        print(f"  version=0x{self.version:x}")
        print(f"  refCount={self.refCount}")
        print(f"  meshCount={self.meshCount}")
        print(f"  bbox min={[round(x, 4) for x in self.bboxMin]} max={[round(x, 4) for x in self.bboxMax]}")
        print(f"  boundingRadius={self.radius:.4f}")
        print(f"  numIndexBuffers={self.numIndexBuffers}")
        for ib in self.indexBuffers:
            print(f"    prim=0x{ib['prim']:x} count={ib['count']} bits={ib['bits']} size={ib['size']}")
        print(f"  numVertexDescriptors={self.numVertexDescriptors}")
        for desc in self.vertexDescriptors:
            print(f"    elements={len(desc)}")
            for e in desc:
                print(f"      stream={e['stream']} off={e['off']} type={e['type']} meth={e['method']} usage={e['usage']} ui={e['usageIndex']} typeCode={e['typeCode']}")
        print(f"  numVertexBuffers={self.numVertexBuffers}")
        for vb in self.vertexBuffers:
            print(f"    descIdx={vb['descIdx']} vtxCount={vb['vertexCount']} size={vb['size']}")
        print(f"  meshes={self.meshes}")
        print(f"  materialIDs={[f'0x{x:08x}' for x in self.materialIDs]}")
        print(f"  unk={self.unk}")
        print(f"  materialInfos={len(self.materialInfos)}")
        print(f"  boneRanges={self.boneRanges}")
        print(f"  animDatas={self.animDatas}")
        print(f"  unknownKey={self.unknownKey}")
        print(f"  finalOffset=0x{self.finalOffset:x} "
              f"{'MATCH' if self.matches() else 'MISMATCH (file 0x%08x)' % len(self.b)}")


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) != 2:
        print("usage: gmdl.py <inspect|dump> <file>", file=sys.stderr)
        return 2
    cmd, path = argv
    g = Gmdl(path)
    if cmd == 'inspect':
        g.inspect()
    elif cmd == 'dump':
        g.dump()
    else:
        print(f"unknown command {cmd!r}", file=sys.stderr)
        return 2
    return 0 if g.matches() else 1


if __name__ == '__main__':
    sys.exit(main())
