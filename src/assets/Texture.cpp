#include "Texture.hpp"

#include <algorithm>
#include <cstdio>

#include "Dxt5.hpp"
#include "Stream.hpp"

namespace openspore::assets {

namespace {

uint32_t mipDim(uint32_t base, uint32_t mip) {
  return std::max<uint32_t>(1, base >> mip);
}

} // namespace

bool parseRasterEnvelope(const uint8_t *data, size_t size, RasterEnvelope &out,
                         std::string &error) {
  if (size < kRasterEnvSize) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "raster: %zu bytes < %zu-byte envelope", size,
                  kRasterEnvSize);
    error = buf;
    return false;
  }
  Reader r(data, size);
  out.version = r.readU32();
  out.width = r.readU32();
  out.height = r.readU32();
  out.mipCount = r.readU32();
  out.field10 = r.readU32();
  out.fourcc = r.readU32();
  out.field18 = r.readU32();
  out.field1c = r.readU32();
  if (!r.ok()) {
    error = "raster: truncated envelope";
    return false;
  }
  return true;
}

bool rasterLayerCount(size_t recordSize, const RasterEnvelope &env,
                      std::string &error) {
  if (recordSize < kRasterEnvSize) {
    error = "raster: record smaller than envelope";
    return false;
  }
  size_t chain = dxt5ChainSize(env.width, env.height, env.mipCount);
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

bool decodeRasterMips(const uint8_t *data, size_t size,
                      std::vector<ImageRGBA> &mips, RasterEnvelope &env,
                      std::string &error) {
  if (!parseRasterEnvelope(data, size, env, error)) return false;
  if (env.fourcc != kDxt5Fourcc) {
    char buf[48];
    std::snprintf(buf, sizeof(buf), "raster: unsupported fourcc 0x%08X",
                  env.fourcc);
    error = buf;
    return false;
  }
  if (env.mipCount == 0) {
    error = "raster: mipCount 0";
    return false;
  }
  if (!rasterLayerCount(size, env, error)) return false;

  // Layer 0 payload starts after every layer header (nLayers * 16 bytes).
  size_t chain = dxt5ChainSize(env.width, env.height, env.mipCount);
  size_t nLayers =
      (size - kRasterEnvSize) / (kRasterLayerHdr + chain);
  size_t off = kRasterEnvSize + nLayers * kRasterLayerHdr;

  mips.clear();
  mips.reserve(env.mipCount);
  for (uint32_t m = 0; m < env.mipCount; ++m) {
    uint32_t mw = mipDim(env.width, m);
    uint32_t mh = mipDim(env.height, m);
    size_t ms = dxt5MipSize(env.width, env.height, m);
    if (off + ms > size) {
      char buf[64];
      std::snprintf(buf, sizeof(buf), "raster: mip %u slice exceeds record", m);
      error = buf;
      return false;
    }
    ImageRGBA img;
    img.width = mw;
    img.height = mh;
    if (!decodeDxt5Mip(data + off, ms, mw, mh, img.pixels, error)) return false;
    mips.push_back(std::move(img));
    off += ms;
  }
  return true;
}

} // namespace openspore::assets
