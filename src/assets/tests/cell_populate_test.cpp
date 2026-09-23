// CS-07 cCellPopulateResource decoder test.
//
// Loads the real packages at test time (Spore_Game + Spore_EP1_Data; 21 of
// the 20+1 records — PatchData is a repack), finds every 0xDA141C1B record,
// and asserts:
//   - every record's marker count matches its size (full span)
//   - zero field-domain violations, including that every non-null
//     distributeCell/clusterCell ref resolves to a real 0xDFAD9F51 record
//   - double-decode: parsing each record twice yields byte-identical dumps
//   - spot values: at least one record carries a large marker table (>= 30)
// Skips gracefully (exit 0) when the packages are absent (no SPORE/ in CI).
// Clean-room code; no asset bytes committed.
#include <cmath>
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

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 3) {
    std::printf("usage: cell_populate_test <Spore_Game.package> "
                "<Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> game = readFile(argv[1]);
  const std::vector<uint8_t> ep1 = readFile(argv[2]);
  if (game.empty() && ep1.empty()) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }

  const std::vector<const std::vector<uint8_t> *> pkgs = {
      game.empty() ? nullptr : &game,
      ep1.empty() ? nullptr : &ep1,
  };
  struct PkgData {
    const std::vector<uint8_t> *pkg = nullptr;
    std::vector<DbpfEntry> entries;
  };
  std::vector<PkgData> pkgsData;
  std::unordered_set<uint32_t> cellInsts;
  std::string error;
  for (const std::vector<uint8_t> *pkg : pkgs) {
    if (pkg == nullptr) {
      continue;
    }
    PkgData pd;
    pd.pkg = pkg;
    if (!parseDbpfIndex(pkg->data(), pkg->size(), pd.entries, error)) {
      std::printf("index error: %s\n", error.c_str());
      return 1;
    }
    for (const DbpfEntry &e : pd.entries) {
      if (e.type == CellCell::kType) {
        cellInsts.insert(e.instance);
      }
    }
    pkgsData.push_back(std::move(pd));
  }

  size_t found = 0, parseFail = 0, issues = 0, doubleDiff = 0, bigMarkers = 0,
      totalMarkers = 0;
  for (const PkgData &pd : pkgsData) {
    const std::vector<uint8_t> *pkg = pd.pkg;
    for (const DbpfEntry &e : pd.entries) {
      if (e.type != CellPopulate::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pkg->data(), pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++found;
      CellPopulate a, b;
      if (!parseCellPopulate(blob.data(), blob.size(), a, error)) {
        std::printf("decode error: %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (!parseCellPopulate(blob.data(), blob.size(), b, error)) {
        std::printf("decode error (2nd pass): %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (a.dump() != b.dump()) {
        ++doubleDiff;
      }
      const std::vector<std::string> probs = cellPopulateIssues(a, cellInsts);
      if (!probs.empty()) {
        ++issues;
        for (const std::string &p : probs) {
          std::printf("  issue: %s\n", p.c_str());
        }
      }
      totalMarkers += a.numMarkers;
      if (a.numMarkers >= 30) {
        ++bigMarkers;
      }
    }
  }

  std::printf("populate records: %zu  markers=%zu  cellInsts=%zu  "
              "bigMarkers=%zu\n",
              found, totalMarkers, cellInsts.size(), bigMarkers);
  check(found >= 20, "found >= 20 populate records");
  check(!cellInsts.empty(), "cell instance set non-empty");
  check(parseFail == 0, "every record parses (count matches size, full span)");
  check(issues == 0, "zero field-domain violations (refs resolve)");
  check(doubleDiff == 0, "double-decode byte-identical");
  check(bigMarkers >= 1, "at least one record has a large marker table (>= 30)");

  return g_failures == 0 ? 0 : 1;
}
