// CS-02 world-object decoder test.
//
// Loads the real content packages (Spore_Content + Spore_EP1_Content_01) at
// test time, decodes every 0x0F43029A record, and asserts:
//   - the known record count
//   - per-record: magic, version, countC, and that EVERY byte is accounted
//     for (header + body == size, no truncation / over-read)
//   - part-name strings are extracted
// Skips gracefully (exit 0) when the packages are absent (no SPORE/ in CI).
// Clean-room code; no asset bytes committed.
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "WorldObject.hpp"

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

// Known total across both content packages (base + EP1).
constexpr size_t kExpectedRecords = 1365;

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 3) {
    std::printf("usage: worldobj_test <Spore_Content.package> "
                "<Spore_EP1_Content_01.package>\n");
    return 1;
  }
  const std::vector<uint8_t> pkgA = readFile(argv[1]);
  const std::vector<uint8_t> pkgB = readFile(argv[2]);
  if (pkgA.empty() || pkgB.empty()) {
    std::printf("SKIP: content packages not found (SPORE/ absent); "
                "synthetic suite still covers the parser\n");
    return 0;
  }

  std::string error;
  size_t records = 0;
  size_t badMagic = 0, badVersion = 0, zeroC = 0, notAccounted = 0;
  size_t withNames = 0;
  double residualSum = 0.0;
  size_t minSize = ~0U, maxSize = 0;

  for (const auto &pkg : {pkgA, pkgB}) {
    std::vector<DbpfEntry> entries;
    if (!parseDbpfIndex(pkg.data(), pkg.size(), entries, error)) {
      std::printf("index error: %s\n", error.c_str());
      return 1;
    }
    for (const DbpfEntry &e : entries) {
      if (e.type != kWorldObjectType) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pkg.data(), pkg.size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++records;
      WorldObject w;
      if (!parseWorldObject(blob.data(), blob.size(), w, error)) {
        std::printf("decode error (%s): %s\n",
                    e.type == kWorldObjectType ? "0x0f43029a" : "?",
                    error.c_str());
        ++g_failures;
        continue;
      }
      if (w.magic != kWorldObjectMagic) {
        ++badMagic;
      }
      if (w.version != 9 && w.version != 10) {
        ++badVersion;
      }
      if (w.countC == 0) {
        ++zeroC;
      }
      if (w.accounted != w.size) {
        ++notAccounted;
        if (notAccounted <= 8) {
          std::printf("  not-accounted: size=%zu accounted=%zu\n", w.size,
                      w.accounted);
        }
      }
      if (!w.names.empty()) {
        ++withNames;
      }
      const double pred =
          static_cast<double>(w.countC) * 141 + w.countD * 5 +
          static_cast<double>(w.countE) * 12 + 50;
      residualSum += static_cast<double>(w.size) - 20 - pred;
      if (w.size < minSize) {
        minSize = w.size;
      }
      if (w.size > maxSize) {
        maxSize = w.size;
      }
    }
  }

  check(records == kExpectedRecords, "record count 1365");
  check(badMagic == 0, "all magic 0xABB455B7");
  check(badVersion == 0, "all version in {9,10}");
  check(zeroC == 0, "all countC > 0");
  check(notAccounted == 0, "every byte of every record accounted for");
  check(withNames > 0, "part-name strings extracted");
  if (records > 0) {
    std::printf("size range %zu..%zu; mean size-model residual %+.1f B "
                "(string overhead)\n",
                minSize, maxSize, residualSum / static_cast<double>(records));
  }
  if (g_failures == 0) {
    std::printf("worldobj: ALL PASS (%zu records fully decoded)\n", records);
    return 0;
  }
  std::printf("worldobj: %d FAILURES\n", g_failures);
  return 1;
}
