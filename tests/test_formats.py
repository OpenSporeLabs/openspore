"""Differential/semantic tests for the OpenSpore format tools (dbpf, rw4, gmdl).

Every test compares a parsed structure (dict) against an inline expected dict of
semantic fields - never raw bytes. Run from the repo root:

    python3 -m unittest discover -s tests -t . -v
"""
import os
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FIX = os.path.join(ROOT, 'tests', 'fixtures')
DBPF_TOOL = os.path.join(ROOT, 'tools', 'spore', 'dbpf', 'dbpf.py')
RW4_TOOL = os.path.join(ROOT, 'tools', 'spore', 'rw4', 'rw4.py')
GMDL_TOOL = os.path.join(ROOT, 'tools', 'spore', 'gmdl', 'gmdl.py')
DBPF = os.path.join(FIX, 'mini_package.dbpf')
RW4 = os.path.join(FIX, 'mini_rw4.rw4')
GMDL = os.path.join(FIX, 'mini.gmdl')

sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'dbpf'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'rw4'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'gmdl'))
import dbpf as dbpfmod  # noqa: E402
import rw4 as rw4mod  # noqa: E402
import gmdl as gmdlmod  # noqa: E402

QFS_PAYLOAD = bytes(range(112)) + b'\x00' * 300  # 412 bytes, must match gen_fixtures.py
REC0 = bytes(range(16))
REC2 = bytes((i * 7) & 0xFF for i in range(64))


def semantic_diff(expected, actual, path='$'):
    lines = []
    if isinstance(expected, dict) and isinstance(actual, dict):
        for k in sorted(set(expected) | set(actual), key=str):
            p = f'{path}.{k}'
            if k not in actual:
                lines.append(f'{p}: missing in actual (expected {expected[k]!r})')
            elif k not in expected:
                lines.append(f'{p}: unexpected in actual {actual[k]!r}')
            elif expected[k] != actual[k]:
                lines.extend(semantic_diff(expected[k], actual[k], p))
    elif expected != actual:
        lines.append(f'{path}: expected {expected!r} got {actual!r}')
    return lines


def assert_semantic(self, expected, actual, label):
    if expected != actual:
        self.fail(f'{label} semantic mismatch:\n' + '\n'.join(semantic_diff(expected, actual)))


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


# ---------------------------------------------------------------- DBPF

class TestDBPF(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data, cls.items = dbpfmod.read(DBPF)

    def test_header(self):
        with open(DBPF, 'rb') as f:
            b = f.read()
        got = dict(
            magic=b[:4].decode('latin1'), major=u32(b, 4), minor=u32(b, 8),
            idxMaj=u32(b, 0x20), idxCount=u32(b, 0x24), idxSize=u32(b, 0x2C),
            idxMinor=u32(b, 0x3C), idxOffset=u32(b, 0x40), fileSize=len(b))
        want = dict(magic='DBPF', major=3, minor=0, idxMaj=3, idxCount=3,
                    idxSize=84, idxMinor=3, idxOffset=96, fileSize=685)
        assert_semantic(self, want, got, 'DBPF header')

    def test_index(self):
        got = [dict(type=dbpfmod.type4cc(it['type']), typeID=it['type'], group=it['group'],
                    inst=it['inst'], off=it['off'], csize=it['csize'], msize=it['msize'],
                    comp=it['comp']) for it in self.items]
        want = [
            dict(type='TSTX', typeID=0x58545354, group=0x11111111, inst=0x22222222,
                 off=184, csize=16, msize=16, comp=False),
            dict(type='QFS1', typeID=0x31534651, group=0x33333333, inst=0x44444444,
                 off=200, csize=421, msize=412, comp=True),
            dict(type='RAWB', typeID=0x42574152, group=0x55555555, inst=0x66666666,
                 off=621, csize=64, msize=64, comp=False),
        ]
        assert_semantic(self, want, got, 'DBPF index')

    def test_type_id_decode(self):
        got = [dbpfmod.type4cc(it['type']) for it in self.items]
        assert_semantic(self, ['TSTX', 'QFS1', 'RAWB'], got, 'type-ID decode')

    def test_decompressed_content_equality(self):
        got0 = dbpfmod.getdata(self.data, self.items[0])
        got1 = dbpfmod.getdata(self.data, self.items[1])
        got2 = dbpfmod.getdata(self.data, self.items[2])
        assert_semantic(self, len(QFS_PAYLOAD), len(got1), 'QFS decompressed size')
        self.assertEqual(got1, QFS_PAYLOAD, 'QFS decompressed bytes != original payload')
        self.assertEqual(got0, REC0, 'uncompressed record 0 bytes')
        self.assertEqual(got2, REC2, 'uncompressed record 2 bytes')

    def test_deterministic_extraction(self):
        def extract(tag):
            d = tempfile.mkdtemp(prefix=f'spore_{tag}_')
            for i in ('0', '1', '2'):
                subprocess.run([sys.executable, DBPF_TOOL, '--out', d, DBPF, 'get', i],
                               check=True, capture_output=True)
            subprocess.run([sys.executable, DBPF_TOOL, '--out', d, DBPF, 'decompress', '1'],
                           check=True, capture_output=True)
            files = sorted(os.listdir(d))
            out = {}
            for f in files:
                with open(os.path.join(d, f), 'rb') as fh:
                    out[f] = fh.read()
            return out

        a, b = extract('a'), extract('b')
        self.assertEqual(sorted(a), sorted(b), 'extraction file sets differ')
        for f in a:
            self.assertEqual(a[f], b[f], f'extraction of {f} not deterministic')
        self.assertEqual(a['decomp_QFS1_33333333_44444444_1'], QFS_PAYLOAD)


# ---------------------------------------------------------------- RW4

class TestRW4(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        with open(RW4, 'rb') as f:
            cls.b = f.read()

    def _sections(self):
        b = self.b
        secs = []
        for i in range(u32(b, 0x24)):
            o = u32(b, 0x30) + 24 * i
            pData, _f04, size, align, tcIdx, tc = (u32(b, o + 4 * k) for k in range(6))
            ap = pData + u32(b, 0x44) if tc == 0x10030 else pData
            secs.append(dict(tc=tc, tcIdx=tcIdx, size=size, align=align, dataAddr=ap))
        return secs

    def test_magic_header(self):
        b = self.b
        got = dict(magicOk=b[:28] == rw4mod.MAGIC, ftype=u32(b, 0x1C),
                   typeName={1: 'MODEL', 0x04000000: 'TEXTURE'}.get(u32(b, 0x1C)),
                   objCount=u32(b, 0x20), sectionCount=u32(b, 0x24),
                   pSectionInfo=u32(b, 0x30), pBufferData=u32(b, 0x44), bufSize=u32(b, 0x4C))
        want = dict(magicOk=True, ftype=1, typeName='MODEL', objCount=1, sectionCount=3,
                    pSectionInfo=0xF0, pBufferData=0x138, bufSize=80)
        assert_semantic(self, want, got, 'RW4 magic/header')

    def test_manifest_types(self):
        b = self.b
        mo = 0x98
        o1, o2, o3, o4 = u32(b, mo + 0xC), u32(b, mo + 0x10), u32(b, mo + 0x14), u32(b, mo + 0x18)
        to = mo + o1
        n = u32(b, to + 4)
        codes = [u32(b, to + 8 + 4 * i) for i in range(n)]
        got = dict(manifestTC=u32(b, mo), offsets=[o1, o2, o3, o4],
                   typecodes=codes, typeNames=[rw4mod.TYPES.get(c, '?') for c in codes])
        want = dict(manifestTC=0x10004, offsets=[0x1C, 0x34, 0x40, 0x4C],
                    typecodes=[0x10030, 0x20003, 0x40001],
                    typeNames=['BaseResource', 'Raster', 'Mesh'])
        assert_semantic(self, want, got, 'RW4 manifest/types')

    def test_section_table(self):
        want = [
            dict(tc=0x10030, tcIdx=0, size=12, align=1, dataAddr=0x138),
            dict(tc=0x20003, tcIdx=1, size=44, align=1, dataAddr=0x144),
            dict(tc=0x40001, tcIdx=2, size=24, align=1, dataAddr=0x170),
        ]
        assert_semantic(self, want, self._sections(), 'RW4 section table')

    def test_base_resource_addressing(self):
        s = self._sections()[0]
        b = self.b[s['dataAddr']:s['dataAddr'] + s['size']]
        got = dict(instance=u32(b, 0), group=u32(b, 4), type=u32(b, 8))
        want = dict(instance=0x11223344, group=0x55667788, type=0x00E6BCE5)
        assert_semantic(self, want, got, 'BaseResource')

    def test_texture_sample(self):
        s = self._sections()[1]
        b = self.b[s['dataAddr']:s['dataAddr'] + s['size']]
        w, h, fmt = u32(b, 0), u32(b, 4), u32(b, 8)
        texels = struct.unpack_from(f'<{w * h}I', b, 12)
        got = dict(width=w, height=h, format=fmt, texelCount=len(texels), firstTexel=texels[0])
        want = dict(width=4, height=2, format=3, texelCount=8, firstTexel=0)
        assert_semantic(self, want, got, 'Raster/texture sample')

    def test_model_sample(self):
        s = self._sections()[2]
        b = self.b[s['dataAddr']:s['dataAddr'] + s['size']]
        vc, ic, isz = u32(b, 0), u32(b, 4), u32(b, 8)
        indices = list(struct.unpack_from(f'<{ic}H', b, 12))
        got = dict(vertexCount=vc, indexCount=ic, indexBytes=isz, indices=indices)
        want = dict(vertexCount=4, indexCount=6, indexBytes=12, indices=[0, 1, 2, 0, 2, 3])
        assert_semantic(self, want, got, 'Mesh/model sample')

    def test_tool_output(self):
        r = subprocess.run([sys.executable, RW4_TOOL, RW4], capture_output=True, text=True)
        self.assertEqual(r.returncode, 0)
        for needle in ('type=MODEL objCount=1 sectionCount=3', 'pBufferData=0x138 bufSize=80',
                       '0x10030:BaseResource', '0x20003:Raster', '0x40001:Mesh',
                       'data@0x138', 'data@0x144', 'data@0x170'):
            self.assertIn(needle, r.stdout, f'missing tool line: {needle!r}\n{r.stdout}')


# ---------------------------------------------------------------- GMDL

class TestGMDL(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.g = gmdlmod.Gmdl(GMDL)

    def test_parse_matches_file(self):
        self.assertTrue(self.g.matches(),
                        f"finalOffset 0x{self.g.finalOffset:x} != file 0x{len(self.g.b):x}")

    def test_semantic_snapshot(self):
        g = self.g
        got = dict(
            version=g.version, refCount=g.refCount, refs=[list(r) for r in g.refs],
            meshCount=g.meshCount,
            bboxMin=[round(v, 4) for v in g.bboxMin], bboxMax=[round(v, 4) for v in g.bboxMax],
            radius=round(g.radius, 4),
            numIndexBuffers=g.numIndexBuffers,
            indexBuffers=[dict(prim=ib['prim'], count=ib['count'], bits=ib['bits'], bufSize=ib['size'])
                          for ib in g.indexBuffers],
            numVertexDescriptors=g.numVertexDescriptors,
            vertexDescriptors=[[dict(e) for e in desc] for desc in g.vertexDescriptors],
            numVertexBuffers=g.numVertexBuffers,
            vertexBuffers=[dict(descIdx=vb['descIdx'], vertexCount=vb['vertexCount'], bufSize=vb['size'])
                           for vb in g.vertexBuffers],
            meshes=[list(m) for m in g.meshes],
            materialIDs=g.materialIDs, unk=g.unk,
            materialInfoCount=len(g.materialInfos),
            boneRangeCount=len(g.boneRanges), animDataCount=len(g.animDatas),
            unknownKey=list(g.unknownKey),
            finalOffset=g.finalOffset, fileSize=len(g.b))
        want = dict(
            version=8, refCount=1, refs=[[0x11111111, 0x22222222, 0x00E6BCE5]],
            meshCount=1,
            bboxMin=[1.5, -2.25, 0.125], bboxMax=[3.5, 0.75, 2.0], radius=4.25,
            numIndexBuffers=1,
            indexBuffers=[dict(prim=4, count=153, bits=16, bufSize=306)],
            numVertexDescriptors=1,
            vertexDescriptors=[[
                dict(stream=0, off=0, type=2, method=0, usage=0, usageIndex=0, typeCode=0),
                dict(stream=0, off=8, type=1, method=0, usage=5, usageIndex=0, typeCode=0),
            ]],
            numVertexBuffers=1,
            vertexBuffers=[dict(descIdx=0, vertexCount=50, bufSize=800)],
            meshes=[[0, 0]], materialIDs=[0x12345678], unk=0,
            materialInfoCount=0, boneRangeCount=0, animDataCount=0,
            unknownKey=[0, 0, 0],
            finalOffset=1266, fileSize=1266)
        assert_semantic(self, want, got, 'GMDL')

    def test_tool_inspect(self):
        r = subprocess.run([sys.executable, GMDL_TOOL, 'inspect', GMDL],
                           capture_output=True, text=True)
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        for needle in ('version=8 refs=1 meshCount=1', 'count=153 bits=16 bufSize=306',
                       'vtxCount=50 bufSize=800', 'materialID=0x12345678', 'MATCH'):
            self.assertIn(needle, r.stdout, f'missing inspect line: {needle!r}')


if __name__ == '__main__':
    unittest.main(verbosity=2)
