// Spore DXT5 (BC3) compressed-texture decoder. Clean-room port of the Python
// oracle (tools/spore/dxt5/dxt5.py); must match it byte-for-byte.
//
// Independently authored for OpenSpore; no EA code, no third-party code.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

// Total raw bytes of the DXT5 block chain for every mip of a base size.
// mip m is ceil(max(1,w>>m)/4) x ceil(max(1,h>>m)/4) blocks of 8 bytes.
size_t dxt5ChainSize(uint32_t width, uint32_t height, uint32_t mipCount);

// Raw bytes of a single mip level of the chain.
size_t dxt5MipSize(uint32_t width, uint32_t height, uint32_t mip);

// Decodes one mip's raw DXT5 block chain into row-major RGBA8 (w*h*4 bytes).
// `img` must be at least dxt5MipSize(width, height, mip) bytes. width/height
// are the mip's own dimensions. False + error on a short block chain.
bool decodeDxt5Mip(const uint8_t *img, size_t imgSize, uint32_t width,
                   uint32_t height, std::vector<uint8_t> &out,
                   std::string &error);

} // namespace openspore::assets
