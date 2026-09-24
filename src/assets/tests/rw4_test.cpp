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
#include "Rw4.hpp"

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char* label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

std::vector<uint8_t> readFile(const char* path) {
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
  f.read(reinterpret_cast<char*>(b.data()), n);
  if (!f) {
    return {};
  }
  return b;
}

void pushU32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  bytes[offset] = static_cast<uint8_t>(value & 0xFFu);
  bytes[offset + 1] = static_cast<uint8_t>((value >> 8u) & 0xFFu);
  bytes[offset + 2] = static_cast<uint8_t>((value >> 16u) & 0xFFu);
  bytes[offset + 3] = static_cast<uint8_t>((value >> 24u) & 0xFFu);
}

std::vector<uint8_t> buildRw4() {
  using namespace openspore::assets;
  constexpr size_t kSize = 0x13C;
  std::vector<uint8_t> bytes(kSize, 0);
  constexpr uint8_t kMagic[] = {0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32,
                                0x00, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x20,
                                0x04, 0x00, 0x34, 0x35, 0x34, 0x00, 0x30,
                                0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (size_t i = 0; i < sizeof(kMagic); ++i) {
    bytes[i] = kMagic[i];
  }
  pushU32(bytes, 0x1C, Rw4::kTypeModel);
  pushU32(bytes, 0x20, 1);
  pushU32(bytes, 0x24, 1);
  pushU32(bytes, 0x30, 0xF0);
  pushU32(bytes, 0x44, 0x138);
  pushU32(bytes, 0x4C, 4);
  pushU32(bytes, 0x98, Rw4::kManifestTc);
  pushU32(bytes, 0xA4, 0x1C);
  pushU32(bytes, 0xB4, Rw4::kTypesTc);
  pushU32(bytes, 0xB8, 1);
  pushU32(bytes, 0xBC, 0x10030);
  pushU32(bytes, 0xF0, 0);
  pushU32(bytes, 0xF8, 4);
  pushU32(bytes, 0x100, 0);
  pushU32(bytes, 0x104, 0x10030);
  return bytes;
}

void testSyntheticRw4() {
  using namespace openspore::assets;
  const std::vector<uint8_t> valid = buildRw4();
  Rw4 parsed;
  std::string error;
  check(parseRw4(valid.data(), valid.size(), parsed, error),
        "rw4 synthetic: valid container parses");
  check(parsed.ftype == Rw4::kTypeModel && parsed.sectionCount == 1 &&
            parsed.typecodes.size() == 1 && parsed.sections.size() == 1 &&
            parsed.complete(),
        "rw4 synthetic: manifest and section directory decoded");
  check(parsed.sections[0].data == 0x138 && parsed.sections[0].size == 4,
        "rw4 synthetic: BaseResource address adjusted");

  std::vector<uint8_t> badType = valid;
  pushU32(badType, 0x1C, 0x12345678u);
  check(!parseRw4(badType.data(), badType.size(), parsed, error) &&
            error.find("ftype") != std::string::npos,
        "rw4 synthetic: unsupported ftype explicit");

  std::vector<uint8_t> badSection = valid;
  pushU32(badSection, 0xF8, 0xFFFF0000u);
  check(!parseRw4(badSection.data(), badSection.size(), parsed, error),
        "rw4 synthetic: section bounds explicit");

  std::vector<uint8_t> badTypes = valid;
  pushU32(badTypes, 0xB4, 0);
  check(!parseRw4(badTypes.data(), badTypes.size(), parsed, error),
        "rw4 synthetic: invalid SectionTypes header explicit");

  std::vector<uint8_t> badArena = valid;
  pushU32(badArena, 0x44, static_cast<uint32_t>(badArena.size()));
  check(!parseRw4(badArena.data(), badArena.size(), parsed, error),
        "rw4 synthetic: buffer arena bounds explicit");

  check(!parseRw4(nullptr, valid.size(), parsed, error),
        "rw4 synthetic: null input explicit");
  check(!knownRw4TypeCode(0x7000Cu),
        "rw4 synthetic: unknown type code is informational");
}

}  // namespace

int main(int argc, char** argv) {
  using namespace openspore::assets;
  testSyntheticRw4();
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
    for (const DbpfEntry& e : entries) {
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
