// CS-08 cCellStructureResource decoder test.
//
// Loads the real packages at test time (Spore_Game + Spore_PatchData +
// Spore_EP1_Data), finds every 0x4B9EF6DC record (376 instances, 149
// unique), and asserts:
//   - every record's attachment count matches its size (full span)
//   - zero field-domain violations
//   - every non-null cCellCellResource.structure ref resolves to a real
//     0x4B9EF6DC instance
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
    std::printf("usage: cell_structure_test <Spore_Game.package> "
                "<Spore_PatchData.package> <Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> files[3] = {readFile(argv[1]), readFile(argv[2]),
                                         readFile(argv[3])};
  std::vector<PkgData> pkgs;
  std::unordered_set<uint32_t> structInsts;
  std::unordered_set<uint32_t> cellRefs;
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
      if (e.type == CellStructure::kType) {
        structInsts.insert(e.instance);
      }
    }
    pkgs.push_back(std::move(pd));
  }
  if (!any) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }
  // Collect cell.structure refs from the raw cell record blobs.
  for (const PkgData &pd : pkgs) {
    for (const DbpfEntry &e : pd.entries) {
      if (e.type != CellCell::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pd.pkg->data(), pd.pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      if (blob.size() >= 4) {
        const uint32_t ref = static_cast<uint32_t>(blob[0]) |
                             (static_cast<uint32_t>(blob[1]) << 8) |
                             (static_cast<uint32_t>(blob[2]) << 16) |
                             (static_cast<uint32_t>(blob[3]) << 24);
        if (ref) {
          cellRefs.insert(ref);
        }
      }
    }
  }

  size_t found = 0, parseFail = 0, issues = 0, doubleDiff = 0;
  size_t refsOk = 0;
  for (const uint32_t x : cellRefs) {
    if (structInsts.count(x)) {
      ++refsOk;
    }
  }
  for (const PkgData &pd : pkgs) {
    for (const DbpfEntry &e : pd.entries) {
      if (e.type != CellStructure::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pd.pkg->data(), pd.pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++found;
      CellStructure a, b;
      if (!parseCellStructure(blob.data(), blob.size(), a, error)) {
        std::printf("decode error: %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (!parseCellStructure(blob.data(), blob.size(), b, error)) {
        std::printf("decode error (2nd pass): %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (a.dump() != b.dump()) {
        ++doubleDiff;
      }
      const std::vector<std::string> probs = cellStructureIssues(a);
      if (!probs.empty()) {
        ++issues;
        for (const std::string &p : probs) {
          std::printf("  issue: %s\n", p.c_str());
        }
      }
    }
  }

  std::printf("structure records: %zu  insts=%zu  cellRefs=%zu resolved=%zu\n",
              found, structInsts.size(), cellRefs.size(), refsOk);
  check(found >= 200, "found >= 200 structure instances");
  check(!structInsts.empty(), "struct instance set non-empty");
  check(!cellRefs.empty(), "cell.structure ref set non-empty");
  check(refsOk == cellRefs.size(), "all cell.structure refs resolve");
  check(parseFail == 0, "every record parses (count matches size, full span)");
  check(issues == 0, "zero field-domain violations");
  check(doubleDiff == 0, "double-decode byte-identical");

  return g_failures == 0 ? 0 : 1;
}
