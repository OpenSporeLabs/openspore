// CS-03 cCellGlobalsResource decoder test.
//
// Loads the real SPORE/DataEP1/Spore_EP1_Data.package at test time, finds the
// single 0x2A3CE5B7 globals record, decodes it, and asserts:
//   - exactly one such record exists
//   - size == 276 and every byte is accounted for (field span == size)
//   - all 69 fields present; all floats finite
//   - the enums are small and the known tuning values match the decompiled
//     struct (gameMode 0, numHighLOD_FG 10, numHighLOD_BG 2, flowMultiplier 5)
// Skips gracefully (exit 0) when the package is absent (no SPORE/ in CI).
// Clean-room code; no asset bytes committed.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "CellResource.hpp"
#include "Dbpf.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

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

// u32 value of a named field, or -1 when absent.
long fieldU(const openspore::assets::CellGlobals &g, const char *name) {
  for (const openspore::assets::CellField &f : g.fields) {
    if (f.name == name) {
      return static_cast<long>(f.u);
    }
  }
  return -1;
}

float fieldF(const openspore::assets::CellGlobals &g, const char *name) {
  for (const openspore::assets::CellField &f : g.fields) {
    if (f.name == name) {
      return f.f;
    }
  }
  return 0.0F;
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: cellres_test <Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> pkg = readFile(argv[1]);
  if (pkg.empty()) {
    std::printf("SKIP: Spore_EP1_Data.package not found (SPORE/ absent)\n");
    return 0;
  }

  std::string error;
  std::vector<DbpfEntry> entries;
  if (!parseDbpfIndex(pkg.data(), pkg.size(), entries, error)) {
    std::printf("index error: %s\n", error.c_str());
    return 1;
  }

  size_t found = 0, badFloat = 0;
  CellGlobals g;
  for (const DbpfEntry &e : entries) {
    if (e.type != CellGlobals::kType) {
      continue;
    }
    std::vector<uint8_t> blob;
    if (!extractDbpfRecord(pkg.data(), pkg.size(), e, blob, error)) {
      std::printf("extract error: %s\n", error.c_str());
      ++g_failures;
      continue;
    }
    ++found;
    if (!parseCellGlobals(blob.data(), blob.size(), g, error)) {
      std::printf("decode error: %s\n", error.c_str());
      ++g_failures;
      continue;
    }
    if (!g.complete()) {
      std::printf("  not-complete: size=%zu span=%zu\n", g.size,
                  g.accounted());
      ++g_failures;
    }
    for (const CellField &f : g.fields) {
      if (f.isFloat && !std::isfinite(f.f)) {
        ++badFloat;
      }
    }
  }

  check(found == 1, "exactly one globals record");
  check(g.size == CellGlobals::kSize, "size == 276");
  check(g.fields.size() == CellGlobals::kFieldCount, "69 fields decoded");
  check(g.complete(), "every byte accounted for");
  check(badFloat == 0, "all floats finite");
  check(fieldU(g, "gameMode") == 0, "gameMode == 0");
  check(fieldU(g, "numHighLOD_FG") == 10, "numHighLOD_FG == 10");
  check(fieldU(g, "numHighLOD_BG") == 2, "numHighLOD_BG == 2");
  check(std::fabs(fieldF(g, "flowMultiplier") - 5.0F) < 1e-3F,
        "flowMultiplier == 5");
  check(std::fabs(fieldF(g, "npcSpeedMultiplier") - 0.5F) < 1e-3F,
        "npcSpeedMultiplier == 0.5");

  if (g_failures == 0) {
    std::printf("cellres: ALL PASS (globals record fully decoded)\n");
    return 0;
  }
  std::printf("cellres: %d FAILURES\n", g_failures);
  return 1;
}
