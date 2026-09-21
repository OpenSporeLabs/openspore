"""Material/texture decode oracles (Obj15): DXT5, raster envelope,
GMDL refCount-BE, and the PNG32-is-RW4 finding.

Synthetic tests run anywhere; tests marked REAL need SPORE/Data/
Spore_Content.package (GOG install) and skip cleanly when absent. Extracted
records land only under /tmp. Run from the repo root:

    python3 -m unittest discover -s tests -t . -v
"""
import hashlib
import os
import struct
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG = os.path.join(ROOT, 'SPORE', 'Data', 'Spore_Content.package')
HAVE_PKG = os.path.exists(PKG)

sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'dbpf'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'gmdl'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'raster'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'spore', 'dxt5'))
import dbpf as dbpfmod  # noqa: E402
import dxt5 as dxt5mod  # noqa: E402
import raster as rastermod  # noqa: E402

GMDL = 0x00E6BCE5
RASTER = 0x2F4E681C
PNG32 = 0x2F4E681B

# (group, instance, refBE, meshCount) from docs/MATERIALS-DESIGN.md section 3.
REFCOUNT_RECORDS = [
    (0x40627100, 0x067B0FBC, 5, 1),
    (0x40646200, 0x62A5E270, 9, 2),
    (0x40656203, 0x24A7C08A, 2, 2),
]

_PKG_DATA = {}


def _pkg_data():
    if not _PKG_DATA:
        _PKG_DATA['data'], _PKG_DATA['items'] = dbpfmod.read(PKG)
    return _PKG_DATA


def _extract(group, inst, typ=None):
    store = _pkg_data()
    for it in store['items']:
        if it['group'] == group and it['inst'] == inst and (typ is None or it['type'] == typ):
            return dbpfmod.getdata(store['data'], it)
    return None


def _write_tmp(data):
    fd, path = tempfile.mkstemp(dir='/tmp', suffix='.bin')
    with os.fdopen(fd, 'wb') as f:
        f.write(data)
    return path


def _bswap32(x):
    # GMDL ref file-keys store the type word byte-reversed vs the DBPF index.
    return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24)


class TestDxt5Synthetic(unittest.TestCase):
    def test_chain_size(self):
        self.assertEqual(dxt5mod.chain_size(512, 512, 10), 174776)
        self.assertEqual(dxt5mod.chain_size(1, 1, 1), 8)
        # 64x1: mips 64,32,16,8 wide -> 16,8,4,2 blocks x 1 -> 128+64+32+16.
        self.assertEqual(dxt5mod.chain_size(64, 1, 4), 128 + 64 + 32 + 16)
        # 10x10: block counts 3x3, 2x2, 1x1, 1x1 -> 72+32+8+8.
        self.assertEqual(dxt5mod.chain_size(10, 10, 4), 3 * 3 * 8 + 2 * 2 * 8 + 8 + 8)

    def test_block_two_color_full_alpha(self):
        # a0=255 > a1=0 (reversed ramp, endpoints 0/255). c0=0x20 (bit5 set ->
        # (8,0,0)), c1=0x00 -> (0,0,0); c0>c1 -> 2-color palette; all texel
        # bits 00 -> palette[0], alpha 255.
        block = bytes([255, 0, 0x20, 0x00, 0, 0, 0, 0])
        rgba = dxt5mod.decode_image(block, 4, 4)
        # reversed ramp a0=0 a1=255, all codes 0 -> round(6*255/8)=191.
        for p in range(16):
            self.assertEqual(tuple(rgba[p * 4:p * 4 + 4]), (8, 0, 0, 191), f'texel {p}')

    def test_block_four_color_alpha_ramp(self):
        # a0=0 < a1=255 (unreversed). 0xE4 byte -> codes 0,1,2,3 per row;
        # av: code0=round(63.75)=64, code1=0, code2=255, code3=64.
        # c0=0x00 < c1=0x20 -> 4-color palette (0,0,0)/(8,0,0)/(0,0,0)/(0,0,0).
        block = bytes([0, 255, 0x00, 0x08, 0xE4, 0xE4, 0xE4, 0xE4])
        rgba = dxt5mod.decode_image(block, 4, 4)
        expect = [(0, 0, 0, 64), (8, 0, 0, 0), (0, 0, 0, 255), (0, 0, 0, 64)]
        for p in range(16):
            self.assertEqual(tuple(rgba[p * 4:p * 4 + 4]), expect[p % 4], f'texel {p}')

    def test_tail_clamp(self):
        # 6x6 image: 4 blocks; texels outside the image must not be written.
        block = bytes([255, 0, 0x3F, 0x0F, 0, 0, 0, 0])
        rgba = dxt5mod.decode_image(block * 4, 6, 6)
        self.assertEqual(len(rgba), 6 * 6 * 4)
        # texel 0: code 0, reversed ramp a0=0 a1=255 -> round(6*255/8)=191.
        self.assertEqual(tuple(rgba[:4]), (8, 0, 0, 191))


@unittest.skipUnless(HAVE_PKG, 'SPORE/ package absent')
class TestRealRecords(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        _pkg_data()  # parse the index once for the whole class

    def test_raster_6947_envelope_and_decode(self):
        data = _extract(0x40662900, 0xD1B4BB56, RASTER)
        self.assertIsNotNone(data, 'raster 0x40662900 not in package')
        env = rastermod.parse_envelope(data)
        self.assertEqual(env['width'], 512)
        self.assertEqual(env['height'], 512)
        self.assertEqual(env['mipCount'], 10)
        self.assertEqual(env['fourcc'], rastermod.DXT5_FOURCC)
        self.assertEqual(rastermod.layer_count(data, env), 2)
        _, mip0, mips = rastermod.decode(data)
        self.assertEqual(len(mips), 10)
        w = env['width']
        self.assertEqual(tuple(mip0[0:4]), (0, 0, 0, 0))
        self.assertEqual(tuple(mip0[(w - 1) * 4:w * 4]), (0, 0, 0, 85))
        self.assertEqual(tuple(mip0[(w - 1) * w * 4:(w - 1) * w * 4 + 4]), (0, 0, 0, 2))
        self.assertEqual(tuple(mip0[(200 * w + 300) * 4:(200 * w + 300) * 4 + 4]),
                         (8, 0, 0, 154))
        self.assertEqual(hashlib.sha256(mip0).hexdigest()[:16], 'a7bad32bd7ef8210')
        self.assertEqual(len(set(mip0[o:o + 3] for o in range(0, len(mip0), 4))), 2)

    def test_refcount_be_named_records(self):
        for group, inst, want_refs, want_mesh in REFCOUNT_RECORDS:
            with self.subTest(group=group, inst=inst):
                data = _extract(group, inst, GMDL)
                self.assertIsNotNone(data, f'gmdl 0x{group:08x}/0x{inst:08x} missing')
                ref_be = struct.unpack_from('>I', data, 4)[0]
                ref_le = struct.unpack_from('<I', data, 4)[0]
                self.assertEqual(ref_be, want_refs)
                self.assertEqual(ref_le, ref_be << 24)
                mesh_count = struct.unpack_from('<I', data, 8 + 12 * ref_be)[0]
                self.assertEqual(mesh_count, want_mesh)
                self.assertGreater(8 + 12 * ref_le, len(data),
                                   'LE walk must run off the record end')

    def test_refcount_be_strided_sample(self):
        store = _pkg_data()
        items = [it for it in store['items'] if it['type'] == GMDL]
        self.assertGreater(len(items), 40)
        stride = len(items) // 40
        violations = 0
        with_refs = 0
        for it in items[::stride][:40]:
            raw = dbpfmod.getdata(store['data'], it)
            ver = struct.unpack_from('<I', raw, 0)[0]
            if ver != 8:
                continue
            ref_be = struct.unpack_from('>I', raw, 4)[0]
            ref_le = struct.unpack_from('<I', raw, 4)[0]
            if ref_be:
                with_refs += 1
            if ref_le != ref_be << 24:
                violations += 1
        self.assertEqual(violations, 0)
        self.assertGreaterEqual(with_refs, 1)

    def test_png32_from_record12_refs_are_rw4_wrapped(self):
        # FINDING: DBPF type PNG32 (0x2f4e681b) records are NOT raw PNG.
        # They are RW4 (Ravenwood) containers. This documents the real format
        # so the raw-PNG oracle (tools/spore/png32) is not mistaken for it.
        RW4 = bytes([0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32, 0x00,
                     0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x20, 0x04, 0x00])
        data = _extract(0x40627100, 0x067B0FBC, GMDL)
        self.assertIsNotNone(data)
        refs = [struct.unpack_from('<III', data, 8 + 12 * i) for i in range(5)]
        self.assertEqual(len(refs), 5)
        png_refs = [(_bswap32(i), _bswap32(g))
                    for (i, g, t) in refs if _bswap32(t) == PNG32]
        self.assertTrue(png_refs, f'no PNG32 refs in record 12: {refs}')
        for inst, group in png_refs:
            with self.subTest(group=group, inst=inst):
                blob = _extract(group, inst, PNG32)
                self.assertIsNotNone(blob, f'png32 0x{group:08x}/0x{inst:08x} missing')
                self.assertEqual(blob[:16], RW4,
                                 f'0x{group:08x}/0x{inst:08x} not RW4-wrapped')
                ftype = struct.unpack_from('<I', blob, 0x1C)[0]
                self.assertNotEqual(ftype, 0x04000000, 'expected not a plain TEXTURE')


if __name__ == '__main__':
    unittest.main()
