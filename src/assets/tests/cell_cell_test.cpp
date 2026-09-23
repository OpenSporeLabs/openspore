// CS-05 cCellCellResource decoder test.
//
// Loads the real cell packages at test time (Spore_Game + Spore_EP1_Data;
// the 223 PatchData repack records are duplicates and not re-scanned), finds
// every 0xDFAD9F51 record, and asserts:
//   - all records are exactly 796 B and parse with a full field span
//   - zero field-domain violations across every record
//   - double-decode: parsing each record twice yields byte-identical dumps
//   - spot values: named records are printable, the escape-mission cells are
//     all hp=2 tutorial predators, exactly one bomb-eat and one poison-nova
//     eat record exist, and at least 60 records are named
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
    std::printf("usage: cell_cell_test <Spore_Game.package> "
                "<Spore_EP1_Data.package>\n");
    return 1;
  }
  const std::vector<uint8_t> game = readFile(argv[1]);
  const std::vector<uint8_t> ep1 = readFile(argv[2]);
  if (game.empty() && ep1.empty()) {
    std::printf("SKIP: SPORE packages not found (SPORE/ absent)\n");
    return 0;
  }

  size_t found = 0, parseFail = 0, issues = 0, named = 0,
      escape = 0, escapeHp2 = 0, bombEat = 0, novaEat = 0, doubleDiff = 0;
  std::string error;
  bool allPrintable = true;

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
      if (e.type != CellCell::kType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pkg->data(), pkg->size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++found;
      CellCell a, b;
      if (!parseCellCell(blob.data(), blob.size(), a, error)) {
        std::printf("decode error: %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (!parseCellCell(blob.data(), blob.size(), b, error)) {
        std::printf("decode error (2nd pass): %s\n", error.c_str());
        ++parseFail;
        continue;
      }
      if (a.dump() != b.dump()) {
        ++doubleDiff;
      }
      const std::vector<std::string> probs = cellCellIssues(a);
      if (!probs.empty()) {
        ++issues;
        for (const std::string &p : probs) {
          std::printf("  issue: %s\n", p.c_str());
        }
      }
      if (!a.name.empty()) {
        ++named;
        for (char ch : a.name) {
          if (ch < 0x20 || ch >= 0x7F) {
            allPrintable = false;
          }
        }
      }
      if (a.triggersEscapeMission) {
        ++escape;
        if (a.hp == 2) {
          ++escapeHp2;
        }
      }
      if (a.eat.bomb) {
        ++bombEat;
      }
      if (a.eat.poisonNova) {
        ++novaEat;
      }
    }
  }

  std::printf("cell records: %zu  named=%zu  escape=%zu (hp2=%zu) "
              "bombEat=%zu novaEat=%zu\n",
              found, named, escape, escapeHp2, bombEat, novaEat);
  check(found >= 266, "found >= 266 unique cell records");
  check(parseFail == 0, "every record parses (796 B, full span)");
  check(issues == 0, "zero field-domain violations");
  check(doubleDiff == 0, "double-decode byte-identical");
  check(named >= 60, ">= 60 named (PLACEHOLDER_*) records");
  check(allPrintable, "named records are printable ASCII");
  check(escape >= 15 && escapeHp2 == escape,
        "escape-mission cells are all hp=2 tutorial predators");
  check(bombEat == 1, "exactly one bomb-eat record");
  check(novaEat == 1, "exactly one poison-nova-eat record");

  return g_failures == 0 ? 0 : 1;
}
