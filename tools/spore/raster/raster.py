#!/usr/bin/env python3
"""Spore raster (RenderAsset 0x2F4E681C) reader.

Byte layout (little-endian), verified against game records:

    version        u32   observed 1
    width          u32
    height         u32
    mipCount       u32
    field@0x10     u32   observed 8 (unresolved)
    fourcc         u32   0x35545844 'DXT5'; 0x15 is a luminance format
                         (out of scope, hard error here)
    field@0x18     u32   observed 0x40000 (unresolved)
    field@0x1c     u32   observed 0xFFFF (unresolved)

    nLayers * { 16-byte layer header, then the raw per-mip chain bytes }

nLayers is DERIVED, never trusted from the header:
    chainSize = sum over mips of ceil(w_m/4) * ceil(h_m/4) * 8
    nLayers   = (recordSize - 32) / (16 + chainSize)
which must divide evenly (verified on the 512x512 DXT5 records: 2 layers).

Usage: raster.py <file>
  prints the envelope, the derived layer count, and the decoded mip0.
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'dxt5'))
import dxt5 as dxt5mod  # noqa: E402

DXT5_FOURCC = 0x35545844
ENV_SIZE = 32
LAYER_HDR = 16


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


def parse_envelope(b):
    """Return the 32-byte envelope as a dict; raises on short input."""
    if len(b) < ENV_SIZE:
        raise ValueError(f'raster: {len(b)} bytes < {ENV_SIZE}-byte envelope')
    env = {
        'version': u32(b, 0x00),
        'width': u32(b, 0x04),
        'height': u32(b, 0x08),
        'mipCount': u32(b, 0x0C),
        'field_10': u32(b, 0x10),
        'fourcc': u32(b, 0x14),
        'field_18': u32(b, 0x18),
        'field_1c': u32(b, 0x1C),
    }
    return env


def chain_size(env):
    return dxt5mod.chain_size(env['width'], env['height'], env['mipCount'])


def layer_count(b, env):
    """Derived layer count; raises when the record size does not divide."""
    per = LAYER_HDR + chain_size(env)
    rem = len(b) - ENV_SIZE
    if rem < per:
        raise ValueError(f'raster: {rem} payload bytes < {per} for one layer')
    if rem % per != 0:
        raise ValueError(f'raster: {rem} payload bytes not a multiple of {per}')
    return rem // per


def mip_size(w, h, m):
    cw = max(1, w >> m)
    ch = max(1, h >> m)
    return ((cw + 3) // 4) * ((ch + 3) // 4) * 8


def decode(b):
    """Decode the raster record. Returns (env, mip0_rgba, mip_list_rgba)."""
    env = parse_envelope(b)
    if env['fourcc'] != DXT5_FOURCC:
        raise ValueError(f'raster: unsupported fourcc 0x{env["fourcc"]:08X}')
    if env['mipCount'] == 0:
        raise ValueError('raster: mipCount 0')
    n = layer_count(b, env)
    off = ENV_SIZE + n * LAYER_HDR  # first payload block of layer 0
    mips = []
    for m in range(env['mipCount']):
        ms = mip_size(env['width'], env['height'], m)
        if off + ms > len(b):
            raise ValueError(f'raster: mip {m} slice exceeds record')
        mips.append(dxt5mod.decode_image(b[off:off + ms],
                                         max(1, env['width'] >> m),
                                         max(1, env['height'] >> m)))
        off += ms
    return env, mips[0], mips


def main(argv):
    if len(argv) != 2:
        print(__doc__)
        return 2
    data = open(argv[1], 'rb').read()
    try:
        env, mip0, mips = decode(data)
    except ValueError as e:
        print(str(e))
        return 1
    import hashlib
    print(f"raster {env['width']}x{env['height']} mipCount={env['mipCount']} "
          f"fourcc=0x{env['fourcc']:08X} layers={layer_count(data, env)}")
    print(f'mip0 sha256[:16] = {hashlib.sha256(mip0).hexdigest()[:16]}')
    w = env['width']
    for (x, y) in [(0, 0), (w - 1, 0), (0, w - 1) if env['width'] == env['height'] else (0, env['height'] - 1), (300, 200)]:
        if x < w and y < env['height']:
            o = (y * w + x) * 4
            print(f'  texel ({x},{y}) RGBA = {tuple(mip0[o:o + 4])}')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
