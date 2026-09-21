#!/usr/bin/env python3
"""Spore DXT5 (BC3) compressed texture decoder.

Pure clean-room decode of the raw 4x4-block chain that follows each raster
layer header. Byte layout per 8-byte block (little-endian packed):

    alpha0         u8   first alpha control value
    alpha1         u8   second alpha control value
    color          u16  c0 = low 6 bits, c1 = next 6 bits (R5G5B5)
    alpha bits     16   2 bits per texel, reading texels left-to-right,
                       top-to-bottom (bit 0 = first texel)

Alpha: if alpha0 > alpha1 the ramp is reversed (intermediate values swap,
the two endpoints stay 0/255 via the standard DXT5 sentinels).
Color: c0 > c1 gives a 2-color palette; otherwise 4 colors with the
intermediate 5-bit values (2*c0+c1)/3 and (c0+c1)/2. 5-bit channels expand
by replication: v -> (v << 3) | (v >> 2).

Usage: dxt5.py <file> <width> <height>
  decodes the file as one mip's raw DXT5 chain and prints a summary.
"""
import struct
import sys


def chain_size(width, height, mip_count):
    """Total bytes of the raw DXT5 chain for all mips of a base size."""
    total = 0
    for m in range(mip_count):
        cw = max(1, width >> m)
        ch = max(1, height >> m)
        total += ((cw + 3) // 4) * ((ch + 3) // 4) * 8
    return total


def _rgb5(v):
    # c0/c1 are 6-bit fields; the oracle reads the color with this exact
    # shift layout (R from bits 9-5, G 14-10, B bit 15), so a 6-bit input
    # yields red in {0,8} only — the black/red alpha-mask signature.
    r = (v >> 5) & 0x1F
    g = (v >> 10) & 0x1F
    b = (v >> 15) & 0x1F
    return (r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2)


def _decode_block(b):
    a0, a1 = b[0], b[1]
    if a0 > a1:
        a0, a1 = a1, a0
        rev = True
    else:
        rev = False

    def av(v2):
        if v2 == 1:
            return 0
        if v2 == 2:
            return 255
        return round((6 * a1 + 2 * a0) / 8) if rev else round((6 * a0 + 2 * a1) / 8)

    c0 = b[2] & 0x3F
    c1 = ((b[2] >> 6) & 0x3) | ((b[3] & 0xF) << 2)
    if c0 > c1:
        pal = [_rgb5(c0), _rgb5(c1)]
    else:
        pal = [_rgb5(c0), _rgb5(c1),
               _rgb5((2 * c0 + c1) // 3), _rgb5((c0 + c1) // 2)]

    alpha = []
    color = []
    for i in range(16):
        v = (b[4 + (i // 4)] >> ((i % 4) * 2)) & 0x3
        alpha.append(av(v))
        color.append(pal[v] if v < len(pal) else pal[0])
    return alpha, color


def decode_image(img, width, height):
    """Decode one mip's raw block chain into row-major RGBA8 bytes."""
    out = bytearray(width * height * 4)
    nbw = (width + 3) // 4
    nbh = (height + 3) // 4
    for by in range(0, height, 4):
        for bx in range(0, width, 4):
            off = ((by // 4) * nbw + (bx // 4)) * 8
            alpha, color = _decode_block(img[off:off + 8])
            for j in range(4):
                for i in range(4):
                    ty = by + j
                    tx = bx + i
                    if ty >= height or tx >= width:
                        continue
                    o = (ty * width + tx) * 4
                    c = color[j * 4 + i]
                    out[o] = c[0]
                    out[o + 1] = c[1]
                    out[o + 2] = c[2]
                    out[o + 3] = alpha[j * 4 + i]
    return bytes(out)


def main(argv):
    if len(argv) != 4:
        print(__doc__)
        return 2
    data = open(argv[1], 'rb').read()
    w, h = int(argv[2]), int(argv[3])
    need = ((w + 3) // 4) * ((h + 3) // 4) * 8
    if len(data) < need:
        print(f'dxt5: {len(data)} bytes < {need} for {w}x{h}')
        return 1
    rgba = decode_image(data[:need], w, h)
    import hashlib
    print(f'dxt5 {w}x{h}: sha256[:16] = {hashlib.sha256(rgba).hexdigest()[:16]}')
    print(f'  distinct RGB = {len(set(rgba[o:o + 3] for o in range(0, len(rgba), 4)))}')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
