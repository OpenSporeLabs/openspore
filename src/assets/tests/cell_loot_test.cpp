// CS-09 cCellLootTableResource decoder test.
//
// Loads the real packages at test time (Spore_Game + Spore_PatchData +
// Spore_EP1_Data), finds every 0xD92AF091 record (115 instances, 45
// unique), and asserts:
//   - every record's entry count matches its size (full span)
//   - zero field-domain violations, including that every non-null entry
//     cell/table ref resolves to a real cell / loot-table record
//   - double-decode: parsing each record twice yields byte-identical dumps
// Skips gracefully (exit 0) when no package is present (no SPORE/ in CI).
// Clean-room code; no asset bytes committed.
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_set>
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
    std::printf("usage: cell_loot_test <Spore_Game.package> "
                "<Spore_PatchData.package> <Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> files[3] = {readFile(argv[1]), readFile(argv[2]),
                                         readFile(argv[3])};
  std::vector<PkgData> pkgs;
  std::unordered_set<uint32_t> cellInsts;
  std::unordered_set<uint32_t> lootInsts;
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
    for (const DbpfEntry &e : pd.entries) {
      if (e.type == CellLootTable::kType) {
        lootInsts.insert(e.instance);
      } else if (e.type == CellCell::kType) {
        cellInsts.insert(e.instance);
      }
    }
    pkgs.push_back(std::move(pd));
  }
  if (!any) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }

  size_t found = 0, parseFail = 0, issues = 0, doubleDiff = 0;
  for (const PkgData &pd : pkgs) {
    for (const DbpfEntry &e : pd.entries) {
      if (e.type != CellLootTable::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pd.pkg->data(), pd.pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++found;
      CellLootTable a, b;
      if (!parseCellLootTable(blob.data(), blob.size(), a, error)) {
        std::printf("decode error: %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (!parseCellLootTable(blob.data(), blob.size(), b, error)) {
        std::printf("decode error (2nd pass): %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (a.dump() != b.dump()) {
        ++doubleDiff;
      }
      const std::vector<std::string> probs =
          cellLootTableIssues(a, cellInsts, lootInsts);
      if (!probs.empty()) {
        ++issues;
        for (const std::string &p : probs) {
          std::printf("  issue: %s\n", p.c_str());
        }
      }
    }
  }

  std::printf("loot tables: %zu  cellInsts=%zu  lootInsts=%zu\n", found,
              cellInsts.size(), lootInsts.size());
  check(found >= 100, "found >= 100 loot-table instances");
  check(!lootInsts.empty(), "loot instance set non-empty");
  check(parseFail == 0, "every record parses (count matches size, full span)");
  check(issues == 0, "zero field-domain violations (refs resolve)");
  check(doubleDiff == 0, "double-decode byte-identical");

  return g_failures == 0 ? 0 : 1;
}
