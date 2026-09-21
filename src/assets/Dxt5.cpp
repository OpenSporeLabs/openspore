#include "Dxt5.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <utility>

namespace openspore::assets {

namespace {

uint32_t ceilDiv4(uint32_t n) { return (n + 3) / 4; }

// Oracle color layout: read the 6-bit field as R5G5B5 with R=bits9-5,
// G=bits14-10, B=bit15, then expand 5->8 bits by replication. A 6-bit
// input therefore yields red in {0,8} only (the black/red mask signature).
std::array<uint8_t, 3> rgb5(uint32_t v) {
    uint32_t r = (v >> 5) & 0x1F;
    uint32_t g = (v >> 10) & 0x1F;
    uint32_t b = (v >> 15) & 0x1F;
    return {static_cast<uint8_t>(r << 3 | r >> 2),
            static_cast<uint8_t>(g << 3 | g >> 2),
            static_cast<uint8_t>(b << 3 | b >> 2)};
}

// Python round() is half-to-even. The numerator 6*a + 2*b is always even,
// so num%8 is in {0,2,4,6} and only the r==4 case is a tie.
uint8_t alphaValue(uint32_t code, uint32_t small, uint32_t large, bool rev) {
    if (code == 1) return 0;
    if (code == 2) return 255;
    uint32_t num = rev ? (6 * large + 2 * small) : (6 * small + 2 * large);
    uint32_t q = num / 8;
    uint32_t r = num % 8;
    uint32_t res;
    if (r == 4) res = (q % 2 == 0) ? q : q + 1;
    else res = (r >= 6) ? q + 1 : q;
    return static_cast<uint8_t>(res);
}

} // namespace

size_t dxt5ChainSize(uint32_t width, uint32_t height, uint32_t mipCount) {
    size_t total = 0;
    for (uint32_t m = 0; m < mipCount; ++m) {
        uint32_t cw = std::max<uint32_t>(1, width >> m);
        uint32_t ch = std::max<uint32_t>(1, height >> m);
        total += static_cast<size_t>(ceilDiv4(cw)) * ceilDiv4(ch) * 8;
    }
    return total;
}

size_t dxt5MipSize(uint32_t width, uint32_t height, uint32_t mip) {
    uint32_t cw = std::max<uint32_t>(1, width >> mip);
    uint32_t ch = std::max<uint32_t>(1, height >> mip);
    return static_cast<size_t>(ceilDiv4(cw)) * ceilDiv4(ch) * 8;
}

bool decodeDxt5Mip(const uint8_t *img, size_t imgSize, uint32_t width,
                   uint32_t height, std::vector<uint8_t> &out,
                   std::string &error) {
    if (width == 0 || height == 0) {
        error = "dxt5: zero-sized mip";
        return false;
    }
    size_t need = dxt5MipSize(width, height, 0);
    if (imgSize < need) {
        char buf[96];
        std::snprintf(buf, sizeof(buf), "dxt5: %zu bytes < %zu for %ux%u",
                      imgSize, need, width, height);
        error = buf;
        return false;
    }

    out.assign(static_cast<size_t>(width) * height * 4, 0);

    uint32_t nbw = ceilDiv4(width);
    for (uint32_t by = 0; by < height; by += 4) {
        for (uint32_t bx = 0; bx < width; bx += 4) {
            size_t off = (static_cast<size_t>(by / 4) * nbw + bx / 4) * 8;
            const uint8_t *b = img + off;

            uint32_t a0 = b[0];
            uint32_t a1 = b[1];
            bool rev = false;
            if (a0 > a1) {
                std::swap(a0, a1);
                rev = true;
            }

            uint32_t c0 = b[2] & 0x3F;
            uint32_t c1 = ((b[2] >> 6) & 0x3) | ((b[3] & 0xF) << 2);

            std::array<uint8_t, 3> pal[4];
            int palSize;
            if (c0 > c1) {
                pal[0] = rgb5(c0);
                pal[1] = rgb5(c1);
                palSize = 2;
            } else {
                pal[0] = rgb5(c0);
                pal[1] = rgb5(c1);
                pal[2] = rgb5((2 * c0 + c1) / 3);
                pal[3] = rgb5((c0 + c1) / 2);
                palSize = 4;
            }

            for (int j = 0; j < 4; ++j) {
                for (int i = 0; i < 4; ++i) {
                    uint32_t ty = by + j;
                    uint32_t tx = bx + i;
                    if (ty >= height || tx >= width) continue;
                    uint32_t idx = j * 4 + i;
                    uint32_t v = (b[4 + (idx / 4)] >> ((idx % 4) * 2)) & 0x3;
                    const auto &c = pal[v < static_cast<uint32_t>(palSize)
                                             ? v
                                             : 0];
                    size_t o = (static_cast<size_t>(ty) * width + tx) * 4;
                    out[o] = c[0];
                    out[o + 1] = c[1];
                    out[o + 2] = c[2];
                    out[o + 3] = alphaValue(v, a0, a1, rev);
                }
            }
        }
    }
    return true;
}

} // namespace openspore::assets
