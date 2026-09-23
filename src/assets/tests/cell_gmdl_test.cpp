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
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"

namespace {

int g_failures = 0;
void check(bool cond, const char *label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}

constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kCellMaterial = 0xD7BE35F9;

struct Expect {
  const char *name;
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

std::vector<uint8_t> readFile(const char *path) {
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
  f.read(reinterpret_cast<char *>(b.data()), n);
  if (!f) {
    return {};
  }
  return b;
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: cell_gmdl_test <Spore_Content.package>\n");
    return 1;
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

  for (const auto &x : kExpected) {
    const int idx = findDbpfEntry(entries, kTypeGmdl, x.group, x.inst);
    char label[128];
    std::snprintf(label, sizeof(label), "cell_gmdl: %s record present",
                  x.name);
    check(idx >= 0, label);
    if (idx < 0) {
      continue;
    }
    const DbpfEntry &e = entries[static_cast<size_t>(idx)];
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
        for (const auto &vb : m.vertexBuffers) {
          vsum += vb.vertexCount;
        }
        for (const auto &ib : m.indexBuffers) {
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
