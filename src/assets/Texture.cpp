#include "Texture.hpp"

#include <algorithm>
#include <cstdio>
#include <limits>
#include <utility>

#include "Dxt5.hpp"
#include "Stream.hpp"

namespace openspore::assets {

namespace {

uint32_t mipDim(uint32_t base, uint32_t mip) {
  return mip >= 32u ? 1u : std::max<uint32_t>(1, base >> mip);
}

}  // namespace

bool parseRasterEnvelope(const uint8_t* data, size_t size, RasterEnvelope& out,
                         std::string& error) {
  out = RasterEnvelope{};
  error.clear();
  if (data == nullptr && size != 0) {
    error = "raster: null input";
    return false;
  }
  if (size < kRasterEnvSize) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "raster: %zu bytes < %zu-byte envelope",
                  size, kRasterEnvSize);
    error = buf;
    return false;
  }
  Reader r(data, size);
  RasterEnvelope parsed;
  parsed.version = r.readU32();
  parsed.width = r.readU32();
  parsed.height = r.readU32();
  parsed.mipCount = r.readU32();
  parsed.field10 = r.readU32();
  parsed.fourcc = r.readU32();
  parsed.field18 = r.readU32();
  parsed.field1c = r.readU32();
  if (!r.ok()) {
    error = "raster: truncated envelope";
    return false;
  }
  out = parsed;
  return true;
}

bool rasterLayerCount(size_t recordSize, const RasterEnvelope& env,
                      std::string& error) {
  error.clear();
  if (recordSize < kRasterEnvSize) {
    error = "raster: record smaller than envelope";
    return false;
  }
  size_t chain = dxt5ChainSize(env.width, env.height, env.mipCount);
  if (chain == std::numeric_limits<size_t>::max() ||
      chain > std::numeric_limits<size_t>::max() - kRasterLayerHdr) {
    error = "raster: layer chain exceeds addressable size";
    return false;
  }
  size_t per = kRasterLayerHdr + chain;
  size_t rem = recordSize - kRasterEnvSize;
  if (rem < per) {
    char buf[96];
    std::snprintf(buf, sizeof(buf),
                  "raster: %zu payload bytes < %zu for one layer", rem, per);
    error = buf;
    return false;
  }
  if (rem % per != 0) {
    char buf[96];
    std::snprintf(buf, sizeof(buf),
                  "raster: %zu payload bytes not a multiple of %zu", rem, per);
    error = buf;
    return false;
  }
  return true;
}

bool decodeRasterMips(const uint8_t* data, size_t size,
                      std::vector<ImageRGBA>& mips, RasterEnvelope& env,
                      std::string& error) {
  mips.clear();
  env = RasterEnvelope{};
  error.clear();
  RasterEnvelope parsedEnvelope;
  if (!parseRasterEnvelope(data, size, parsedEnvelope, error)) return false;
  if (parsedEnvelope.width == 0 || parsedEnvelope.height == 0) {
    error = "raster: zero-sized image";
    return false;
  }
  if (parsedEnvelope.fourcc != kDxt5Fourcc) {
    char buf[48];
    std::snprintf(buf, sizeof(buf), "raster: unsupported fourcc 0x%08X",
                  parsedEnvelope.fourcc);
    error = buf;
    return false;
  }
  if (parsedEnvelope.mipCount == 0) {
    error = "raster: mipCount 0";
    return false;
  }
  if (!rasterLayerCount(size, parsedEnvelope, error)) return false;

  size_t chain = dxt5ChainSize(parsedEnvelope.width, parsedEnvelope.height,
                               parsedEnvelope.mipCount);
  size_t nLayers = (size - kRasterEnvSize) / (kRasterLayerHdr + chain);
  size_t off = kRasterEnvSize + nLayers * kRasterLayerHdr;

  std::vector<ImageRGBA> parsedMips;
  parsedMips.reserve(parsedEnvelope.mipCount);
  for (uint32_t m = 0; m < parsedEnvelope.mipCount; ++m) {
    uint32_t mw = mipDim(parsedEnvelope.width, m);
    uint32_t mh = mipDim(parsedEnvelope.height, m);
    size_t ms = dxt5MipSize(parsedEnvelope.width, parsedEnvelope.height, m);
    if (ms > size - off) {
      char buf[64];
      std::snprintf(buf, sizeof(buf), "raster: mip %u slice exceeds record", m);
      error = buf;
      return false;
    }
    ImageRGBA img;
    img.width = mw;
    img.height = mh;
    if (!decodeDxt5Mip(data + off, ms, mw, mh, img.pixels, error)) return false;
    parsedMips.push_back(std::move(img));
    off += ms;
  }
  env = parsedEnvelope;
  mips = std::move(parsedMips);
  return true;
}

}  // namespace openspore::assets
