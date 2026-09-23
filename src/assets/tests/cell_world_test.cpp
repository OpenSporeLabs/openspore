// CS-06 cCellWorldResource decoder test.
//
// Loads the real packages at test time (Spore_Game + Spore_EP1_Data; 24 of
// the 37 records — the 13 PatchData repack records are duplicates), finds
// every 0x9B8E862F record,
// and asserts:
//   - every record's header counts match its size (full span)
//   - zero field-domain violations across every record
//   - double-decode: parsing each record twice yields byte-identical dumps
//   - spot values: at least one record carries a large advect table (>= 12
//     entries) and at least one level entry uses the 0xFFFFFFFF "any" scale
// Skips gracefully (exit 0) when the packages are absent (no SPORE/ in CI).
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

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 3) {
    std::printf("usage: cell_world_test <Spore_Game.package> "
                "<Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> game = readFile(argv[1]);
  const std::vector<uint8_t> ep1 = readFile(argv[2]);
  if (game.empty() && ep1.empty()) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }

  size_t found = 0, parseFail = 0, issues = 0, doubleDiff = 0, bigAdvect = 0,
      anyScale = 0;
  std::string error;

  const std::vector<const std::vector<uint8_t> *> pkgs = {
      game.empty() ? nullptr : &game,
      ep1.empty() ? nullptr : &ep1,
  };
  for (const std::vector<uint8_t> *pkg : pkgs) {
    if (pkg == nullptr) {
      continue;
    }
    std::vector<DbpfEntry> entries;
    if (!parseDbpfIndex(pkg->data(), pkg->size(), entries, error)) {
      std::printf("index error: %s\n", error.c_str());
      return 1;
    }
    for (const DbpfEntry &e : entries) {
      if (e.type != CellWorld::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pkg->data(), pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++found;
      CellWorld a, b;
      if (!parseCellWorld(blob.data(), blob.size(), a, error)) {
        std::printf("decode error: %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (!parseCellWorld(blob.data(), blob.size(), b, error)) {
        std::printf("decode error (2nd pass): %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (a.dump() != b.dump()) {
        ++doubleDiff;
      }
      const std::vector<std::string> probs = cellWorldIssues(a);
      if (!probs.empty()) {
        ++issues;
        for (const std::string &p : probs) {
          std::printf("  issue: %s\n", p.c_str());
        }
      }
      if (a.numAdvect >= 12) {
        ++bigAdvect;
      }
      for (const CellLevelEntry &le : a.populate) {
        if (le.playerSize == 0xFFFFFFFFu) {
          ++anyScale;
        }
      }
    }
  }

  std::printf("cellworld records: %zu  bigAdvect=%zu  anyScale=%zu\n", found,
              bigAdvect, anyScale);
  check(found >= 24, "found >= 24 cell-world records (game + EP1)");
  check(parseFail == 0, "every record parses (counts match size, full span)");
  check(issues == 0, "zero field-domain violations");
  check(doubleDiff == 0, "double-decode byte-identical");
  check(bigAdvect >= 1, "at least one record has a large advect table (>= 12)");
  check(anyScale >= 1, "at least one level entry uses the 0xFFFFFFFF scale");

  return g_failures == 0 ? 0 : 1;
}
