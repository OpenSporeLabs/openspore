// CS-24: real cell-stage GMDL family. The cell models live at groups
// 0x40616201 (primary LOD) / 0x40616202 (low LOD), 88 gmdl records / 44
// instances, all sharing the cell material 0xD7BE35F9. The previous stand-in
// 0x40637E03 was a BUILDING (identity REJECTED) — the scene now points at real
// cell-family records.
//
// This is the real_asset_test pattern: load the chosen records from the local
// install at test time, decode each via the GMDL walk, and assert per-record
// vertex counts + material id WITHOUT committing asset bytes. Skips gracefully
// when SPORE/ is absent.
//
// Usage: cell_gmdl_test <path-to-Spore_Content.package>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Dxt5.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace {

int g_failures = 0;
void check(bool cond, const char* label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}

constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kCellMaterial = 0xD7BE35F9;

struct Expect {
  const char* name;
  uint32_t group;
  uint32_t inst;
  uint32_t expectVerts;
  uint32_t expectTris;
};

// The records the scene loads (CS-24) + the low-LOD pair. Vertex/tri counts
// are VERIFIED against the C++ GMDL walk on 3.1.0.22.
const Expect kExpected[] = {
    {"player_cell (hi)", 0x40616201, 0x0C7963FB, 668, 3198 / 3},
    {"food_a (hi)", 0x40616201, 0xB0B9BAFF, 613, 2472 / 3},
    {"food_b (hi)", 0x40616201, 0xD9007204, 631, 2712 / 3},
    {"prey_c (hi, larger)", 0x40616201, 0x0D64F036, 1250, 5874 / 3},
    {"player_cell (lo)", 0x40616202, 0x0C7963FB, 125, 408 / 3},
};
constexpr int kCount = sizeof(kExpected) / sizeof(kExpected[0]);

std::vector<uint8_t> readFile(const char* path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) {
    return {};
  }
  f.seekg(0, std::ios::end);
  const long n = f.tellg();
  if (n <= 0) {
    return {};
  }
  f.seekg(0, std::ios::beg);
  std::vector<uint8_t> b(static_cast<size_t>(n));
  f.read(reinterpret_cast<char*>(b.data()), n);
  if (!f) {
    return {};
  }
  return b;
}

void pushU16(std::vector<uint8_t>& bytes, uint16_t value) {
  bytes.push_back(static_cast<uint8_t>(value & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 8u) & 0xFFu));
}

void pushU32(std::vector<uint8_t>& bytes, uint32_t value) {
  bytes.push_back(static_cast<uint8_t>(value & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 8u) & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 16u) & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 24u) & 0xFFu));
}

void pushF32(std::vector<uint8_t>& bytes, float value) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  pushU32(bytes, bits);
}

std::vector<uint8_t> buildGmdl(uint32_t version = 8, uint32_t indexBits = 16,
                               bool badIndex = false,
                               bool badPosition = false) {
  std::vector<uint8_t> bytes;
  pushU32(bytes, version);
  pushU32(bytes, 0);
  pushU32(bytes, 1);
  for (float value : {0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F}) {
    pushF32(bytes, value);
  }
  pushF32(bytes, 0.7071F);
  pushU32(bytes, 1);
  pushU32(bytes, 4);
  pushU32(bytes, 3);
  pushU32(bytes, indexBits);
  pushU32(bytes, 6);
  pushU16(bytes, 0);
  pushU16(bytes, 1);
  pushU16(bytes, badIndex ? 3 : 2);
  pushU32(bytes, 1);
  pushU32(bytes, 1);
  pushU16(bytes, 0);
  pushU16(bytes, 0);
  bytes.push_back(2);
  bytes.push_back(0);
  bytes.push_back(0);
  bytes.push_back(0);
  pushU32(bytes, 0);
  pushU32(bytes, 1);
  pushU32(bytes, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 36);
  for (float value : {0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F}) {
    if (badPosition && value == 0.0F) {
      pushF32(bytes, std::numeric_limits<float>::quiet_NaN());
    } else {
      pushF32(bytes, value);
    }
  }
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0x12345678u);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  return bytes;
}

std::vector<uint8_t> buildRaster(
    uint32_t fourcc = openspore::assets::kDxt5Fourcc) {
  std::vector<uint8_t> bytes;
  pushU32(bytes, 1);
  pushU32(bytes, 4);
  pushU32(bytes, 4);
  pushU32(bytes, 1);
  pushU32(bytes, 8);
  pushU32(bytes, fourcc);
  pushU32(bytes, 0x40000u);
  pushU32(bytes, 0xFFFFu);
  bytes.insert(bytes.end(), 16, 0);
  bytes.insert(bytes.end(), {0, 255, 0, 8, 0xE4, 0xE4, 0xE4, 0xE4});
  return bytes;
}

void testSyntheticGeometry() {
  using namespace openspore::assets;
  const std::vector<uint8_t> valid = buildGmdl();
  GmdlModel model;
  std::string error;
  check(parseGmdl(valid.data(), valid.size(), model, error),
        "gmdl synthetic: version 8 parses");
  check(model.consumed == valid.size() && model.meshes.size() == 1,
        "gmdl synthetic: full model extent consumed");
  Mesh mesh;
  check(meshFromGmdl(model, 0, mesh, error) && mesh.positions.size() == 3 &&
            mesh.indices.size() == 3,
        "mesh synthetic: supported position/index path decodes");
  check(parseGmdl(nullptr, 1, model, error) == false,
        "gmdl synthetic: null input explicit");
  const std::vector<uint8_t> version9 = buildGmdl(9);
  check(!parseGmdl(version9.data(), version9.size(), model, error) &&
            error.find("unsupported version") != std::string::npos,
        "gmdl synthetic: v9 unsupported explicit");
  const std::vector<uint8_t> wide = buildGmdl(8, 32);
  check(parseGmdl(wide.data(), wide.size(), model, error) &&
            !meshFromGmdl(model, 0, mesh, error) &&
            error.find("unsupported index width") != std::string::npos,
        "mesh synthetic: 32-bit indices unsupported explicit");
  const std::vector<uint8_t> badIndex = buildGmdl(8, 16, true);
  check(parseGmdl(badIndex.data(), badIndex.size(), model, error) &&
            !meshFromGmdl(model, 0, mesh, error) &&
            error.find("out of range") != std::string::npos,
        "mesh synthetic: index bounds explicit");
  const std::vector<uint8_t> badPosition = buildGmdl(8, 16, false, true);
  check(parseGmdl(badPosition.data(), badPosition.size(), model, error) &&
            !meshFromGmdl(model, 0, mesh, error) &&
            error.find("non-finite") != std::string::npos,
        "mesh synthetic: non-finite positions explicit");
  std::vector<uint8_t> truncated = valid;
  truncated.resize(48);
  check(!parseGmdl(truncated.data(), truncated.size(), model, error),
        "gmdl synthetic: truncated geometry explicit");
}

void testSyntheticTexture() {
  using namespace openspore::assets;
  const std::vector<uint8_t> raster = buildRaster();
  std::vector<openspore::ImageRGBA> mips;
  RasterEnvelope env;
  std::string error;
  check(decodeRasterMips(raster.data(), raster.size(), mips, env, error) &&
            mips.size() == 1 && mips[0].width == 4 && mips[0].height == 4 &&
            mips[0].pixels.size() == 64,
        "raster synthetic: DXT5 envelope and mip decode");
  check(mips[0].pixels[0] == 0 && mips[0].pixels[1] == 0 &&
            mips[0].pixels[2] == 0 && mips[0].pixels[3] == 64 &&
            mips[0].pixels[4] == 8 && mips[0].pixels[7] == 0,
        "raster synthetic: DXT5 block output deterministic");
  const std::vector<uint8_t> unsupported = buildRaster(0x15u);
  check(!decodeRasterMips(unsupported.data(), unsupported.size(), mips, env,
                          error) &&
            error.find("unsupported fourcc") != std::string::npos,
        "raster synthetic: unsupported fourcc explicit");
  std::vector<uint8_t> noMip = raster;
  noMip[12] = 0;
  noMip[13] = 0;
  noMip[14] = 0;
  noMip[15] = 0;
  check(!decodeRasterMips(noMip.data(), noMip.size(), mips, env, error),
        "raster synthetic: zero mip count explicit");
  std::vector<uint8_t> truncated = raster;
  truncated.pop_back();
  check(!decodeRasterMips(truncated.data(), truncated.size(), mips, env, error),
        "raster synthetic: truncated payload explicit");
  std::vector<uint8_t> shortBlock(7, 0);
  std::vector<uint8_t> pixels;
  check(
      !decodeDxt5Mip(shortBlock.data(), shortBlock.size(), 4, 4, pixels, error),
      "dxt5 synthetic: short block chain explicit");
  check(!decodeDxt5Mip(raster.data(), raster.size(), 0, 4, pixels, error),
        "dxt5 synthetic: zero dimension explicit");
  check(dxt5MipSize(UINT32_MAX, UINT32_MAX, 32) == 8,
        "dxt5 synthetic: mip shift bounds explicit");
}

}  // namespace

int main(int argc, char** argv) {
  using namespace openspore::assets;
  testSyntheticGeometry();
  testSyntheticTexture();
  if (argc < 2) {
    std::printf("usage: cell_gmdl_test <Spore_Content.package>\n");
    return g_failures == 0 ? 0 : 1;
  }
  const std::vector<uint8_t> pkg = readFile(argv[1]);
  if (pkg.empty()) {
    std::printf("SKIP: package not found at %s (SPORE/ absent)\n", argv[1]);
    return 0;
  }

  std::string error;
  std::vector<DbpfEntry> entries;
  check(parseDbpfIndex(pkg.data(), pkg.size(), entries, error),
        "cell_gmdl: package index parses");
  if (g_failures > 0) {
    return 1;
  }

  for (const auto& x : kExpected) {
    const int idx = findDbpfEntry(entries, kTypeGmdl, x.group, x.inst);
    char label[128];
    std::snprintf(label, sizeof(label), "cell_gmdl: %s record present", x.name);
    check(idx >= 0, label);
    if (idx < 0) {
      continue;
    }
    const DbpfEntry& e = entries[static_cast<size_t>(idx)];
    std::vector<uint8_t> blob;
    std::snprintf(label, sizeof(label), "cell_gmdl: %s extracts+decompresses",
                  x.name);
    check(extractDbpfRecord(pkg.data(), pkg.size(), e, blob, error), label);
    if (!blob.empty()) {
      GmdlModel m;
      std::snprintf(label, sizeof(label), "cell_gmdl: %s gmdl parses", x.name);
      check(parseGmdl(blob.data(), blob.size(), m, error), label);
      if (m.version == 8) {
        uint32_t vsum = 0;
        uint32_t isum = 0;
        for (const auto& vb : m.vertexBuffers) {
          vsum += vb.vertexCount;
        }
        for (const auto& ib : m.indexBuffers) {
          isum += ib.indexCount;
        }
        std::snprintf(label, sizeof(label), "cell_gmdl: %s verts == %u", x.name,
                      x.expectVerts);
        check(vsum == x.expectVerts, label);
        std::snprintf(label, sizeof(label), "cell_gmdl: %s tris == %u", x.name,
                      x.expectTris);
        check(isum / 3 == x.expectTris, label);
        if (!m.materialIds.empty()) {
          std::snprintf(label, sizeof(label), "cell_gmdl: %s cell material",
                        x.name);
          check(m.materialIds[0] == kCellMaterial, label);
        }
        Mesh mesh;
        std::snprintf(label, sizeof(label), "cell_gmdl: %s mesh converts",
                      x.name);
        check(meshFromGmdl(m, 0, mesh, error), label);
      }
    }
  }

  if (g_failures > 0) {
    std::printf("cell_gmdl: %d FAILURES\n", g_failures);
    return 1;
  }
  std::printf("cell_gmdl: all pass (%d records)\n", kCount);
  return 0;
}
