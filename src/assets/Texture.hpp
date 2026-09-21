// Spore raster (RenderAsset 0x2F4E681C) envelope + DXT5 mip decoder.
// Clean-room port of the Python oracle (tools/spore/raster/raster.py); the
// DXT5 block math is delegated to Dxt5 so the two stay in lockstep.
//
// Independently authored for OpenSpore; no EA code, no third-party code.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "renderer/Renderer.hpp"

namespace openspore::assets {

// 32-byte raster header. The three trailing words (field10/fourcc/field18/
// field1c) are documented from observation; only fourcc drives decoding.
struct RasterEnvelope {
  uint32_t version = 0;
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t mipCount = 0;
  uint32_t field10 = 0;
  uint32_t fourcc = 0;
  uint32_t field18 = 0;
  uint32_t field1c = 0;
};

constexpr uint32_t kDxt5Fourcc = 0x35545844; // 'DXT5'
constexpr size_t kRasterEnvSize = 32;
constexpr size_t kRasterLayerHdr = 16;

// Reads the 32-byte envelope; false + error on short input.
bool parseRasterEnvelope(const uint8_t *data, size_t size, RasterEnvelope &out,
                         std::string &error);

// nLayers is derived, never trusted: (size - envSize) / (hdr + chainSize).
// False + error when the payload does not divide evenly.
bool rasterLayerCount(size_t recordSize, const RasterEnvelope &env,
                      std::string &error);

// Decodes layer 0 of a DXT5 raster into every mip (mip0 first). Each
// ImageRGBA carries its own width/height; pixels are row-major RGBA8.
// False + error on a non-DXT5 fourcc, mipCount 0, a bad layer split, or a
// mip slice that runs past the record.
bool decodeRasterMips(const uint8_t *data, size_t size,
                      std::vector<ImageRGBA> &mips, RasterEnvelope &env,
                      std::string &error);

} // namespace openspore::assets
