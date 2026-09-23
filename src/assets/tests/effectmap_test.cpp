// CS-12 cCellEffectMapResource + cCellBackgroundMapResource decoder test.
//
// Loads the real packages at test time (Spore_Game + PatchData +
// Spore_EP1_Data), finds every 0x433FB70C effect map (1 instance) and
// 0x612B3191 background map (1 instance), and asserts:
//   - every record's entry count matches its size (full span)
//   - zero field-domain violations (float ranges, -1.0 sentinels, rgb 0..1)
//   - double-decode: parsing each record twice yields byte-identical dumps
// Skips gracefully (exit 0) when no package is present (no SPORE/ in CI).
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

struct PkgData {
  const std::vector<uint8_t> *pkg = nullptr;
  std::vector<openspore::assets::DbpfEntry> entries;
};

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 4) {
    std::printf("usage: effectmap_test <Spore_Game.package> "
                "<PatchData.package> <Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> files[3] = {readFile(argv[1]), readFile(argv[2]),
                                         readFile(argv[3])};
  std::vector<PkgData> pkgs;
  std::string error;
  bool any = false;
  for (const std::vector<uint8_t> &file : files) {
    if (file.empty()) {
      continue;
    }
    any = true;
    PkgData pd;
    pd.pkg = &file;
    if (!parseDbpfIndex(file.data(), file.size(), pd.entries, error)) {
      std::printf("index error: %s\n", error.c_str());
      return 1;
    }
    pkgs.push_back(std::move(pd));
  }
  if (!any) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }

  size_t emCount = 0, bmCount = 0, parseFail = 0, issues = 0, doubleDiff = 0;
  CellEffectMap em{}; // last effect map, for the combined issues check
  for (const PkgData &pd : pkgs) {
    for (const DbpfEntry &e : pd.entries) {
      if (e.type != CellEffectMap::kType &&
          e.type != CellBackgroundMap::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pd.pkg->data(), pd.pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      bool isEM = e.type == CellEffectMap::kType;
      CellBackgroundMap bm, bm2;
      if (isEM) {
        CellEffectMap em2;
        if (!parseCellEffectMap(blob.data(), blob.size(), em, error) ||
            !parseCellEffectMap(blob.data(), blob.size(), em2, error)) {
          std::printf("decode error: %s\n", error.c_str());
          ++parseFail;
          continue;
        }
        ++emCount;
        if (em.dump() != em2.dump()) {
          ++doubleDiff;
        }
        const std::vector<std::string> probs =
            cellEffectMapIssues(em, bm);
        if (!probs.empty()) {
          ++issues;
          for (const std::string &p : probs) {
            std::printf("  issue: %s\n", p.c_str());
          }
        }
      } else {
        if (!parseCellBackgroundMap(blob.data(), blob.size(), bm, error) ||
            !parseCellBackgroundMap(blob.data(), blob.size(), bm2, error)) {
          std::printf("decode error: %s\n", error.c_str());
          ++parseFail;
          continue;
        }
        ++bmCount;
        if (bm.dump() != bm2.dump()) {
          ++doubleDiff;
        }
        const std::vector<std::string> probs =
            cellEffectMapIssues(em, bm);
        if (!probs.empty()) {
          ++issues;
          for (const std::string &p : probs) {
            std::printf("  issue: %s\n", p.c_str());
          }
        }
      }
    }
  }

  std::printf("effectMaps=%zu  bgMaps=%zu\n", emCount, bmCount);
  check(emCount >= 1, "found >= 1 effect map");
  check(bmCount >= 1, "found >= 1 background map");
  check(parseFail == 0, "every record parses (count matches size, full span)");
  check(issues == 0, "zero field-domain violations");
  check(doubleDiff == 0, "double-decode byte-identical");

  return g_failures == 0 ? 0 : 1;
}
