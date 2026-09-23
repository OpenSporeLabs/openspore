// CS-04 RW4 container-walker test.
//
// Two modes:
//   rw4_test <pkg> [pkg2 ...]   invariant mode: parse every 0x2F4E681B record
//                                and assert the walk is well-formed (magic,
//                                ftype, manifest/types type codes, every
//                                section data pointer in-bounds + known tc).
//   rw4_test --dump <pkg>       print one canonical line per record (the
//                                section walk) so the python differential test
//                                can diff the C++ walker against the oracle.
// Skips gracefully (exit 0) when the packages are absent (no SPORE/ in CI).
// Clean-room code; no asset bytes committed.
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Rw4.hpp"

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
  const bool dump = argc >= 2 && std::string(argv[1]) == "--dump";
  const int first = dump ? 2 : 1;
  if (!dump && argc < 2) {
    std::printf("usage: rw4_test <pkg> [pkg2 ...] | rw4_test --dump <pkg>\n");
    return 1;
  }
  if (dump && argc < 3) {
    std::printf("usage: rw4_test <pkg> [pkg2 ...] | rw4_test --dump <pkg>\n");
    return 1;
  }

  size_t records = 0, notComplete = 0, badFtype = 0;
  std::string error;

  for (int a = first; a < argc; ++a) {
    const std::vector<uint8_t> pkg = readFile(argv[a]);
    if (pkg.empty()) {
      if (!dump) {
        std::printf("SKIP: %s not found (SPORE/ absent)\n", argv[a]);
        return 0;
      }
      continue;
    }
    std::vector<DbpfEntry> entries;
    if (!parseDbpfIndex(pkg.data(), pkg.size(), entries, error)) {
      std::printf("index error: %s\n", error.c_str());
      return 1;
    }
    for (const DbpfEntry &e : entries) {
      if (e.type != kRw4Type) {
        continue;
      }
      std::vector<uint8_t> blob;
      if (!extractDbpfRecord(pkg.data(), pkg.size(), e, blob, error)) {
        std::printf("extract error: %s\n", error.c_str());
        ++g_failures;
        continue;
      }
      ++records;
      Rw4 r;
      if (!parseRw4(blob.data(), blob.size(), r, error)) {
        if (!dump) {
          std::printf("  not-well-formed: %s\n", error.c_str());
        }
        ++notComplete;
        continue;
      }
      if (r.ftype != Rw4::kTypeModel && r.ftype != Rw4::kTypeTexture &&
          r.ftype != Rw4::kTypeSpecial) {
        ++badFtype;
      }
      if (dump) {
        std::printf("%s\n", r.describe().c_str());
      }
    }
  }

  if (dump) {
    return g_failures ? 1 : 0;
  }

  check(records > 0, "rw4 records found");
  check(notComplete == 0, "every record walks well-formed");
  check(badFtype == 0, "all ftype in {MODEL,TEXTURE,SPECIAL}");
  std::printf("rw4: %zu records, %zu not-well-formed, %zu bad-ftype\n", records,
              notComplete, badFtype);
  if (g_failures == 0) {
    std::printf("rw4: ALL PASS (%zu records)\n", records);
    return 0;
  }
  std::printf("rw4: %d FAILURES\n", g_failures);
  return 1;
}
