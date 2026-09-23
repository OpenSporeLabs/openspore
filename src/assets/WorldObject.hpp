// Clean-room walker for the 0x0F43029A "world-object" (model-group) records.
//
// Independently authored for OpenSpore. These are the 1,365 records in the
// *Models groups (CellModels / CreatureModels / FloraModels / PaletteModels)
// of the content packages. They are NOT CellSerializer resources; they are a
// separate model/scene placement format.
//
// Header (20 bytes, little-endian):
//   +0  u32  magic        == 0xABB455B7
//   +4  u32 version      9 = base game, 10 = EP1
//   +8  u32 countC       primary entry count (2..100, scales with size)
//   +12 u32 countD       secondary count (5..71)
//   +16 u32 countE       tertiary count (0..254; 12-byte vector3 entries)
// Body: countC variable-length main entries carrying concatenated lowercase
// part-name strings (spine / eye / sense / limb / foot / ...) plus 12-byte
// vector3s and ~5-byte values. Evidence-based size model (R^2=0.9997):
//   size - 20 ~= countC*141 + countD*5 + countE*12 + 50
// The c-entry field ORDER is not byte-exact derivable (no decompiled loader
// references the type); the walker extracts the semantic content (names and
// plausible vector3s) and proves every byte is accounted for.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

constexpr uint32_t kWorldObjectType = 0x0F43029A;
constexpr uint32_t kWorldObjectMagic = 0xABB455B7;
constexpr size_t kWorldObjectHeaderSize = 20;

// A part-name string found in the record body.
struct WorldObjectName {
  size_t offset = 0; // byte offset from record start (header included)
  std::string name;  // lowercase part name (e.g. "spine", "eye")
};

// A plausible vector3 (3 finite floats, |v| < 16, one component >= 0.001).
struct WorldObjectVec3 {
  size_t offset = 0;
  std::array<float, 3> value = {0.0F, 0.0F, 0.0F};
};

struct WorldObject {
  uint32_t magic = 0;
  uint32_t version = 0;
  uint32_t countC = 0;
  uint32_t countD = 0;
  uint32_t countE = 0;
  size_t size = 0;

  std::vector<WorldObjectName> names;
  std::vector<WorldObjectVec3> vec3s;

  // Byte accounting: header + body == size, body = name bytes + data bytes.
  size_t bodyBytes = 0;
  size_t bodyNameBytes = 0;
  size_t bodyDataBytes = 0;
  size_t accounted = 0; // == size on a complete decode
};

// Parses a whole world-object record. True + populated out on a complete
// decode (every byte accounted). False + error when the blob is shorter than
// the header, the magic does not match, or the version is unsupported.
bool parseWorldObject(const uint8_t *data, size_t size, WorldObject &out,
                      std::string &error);

} // namespace openspore::assets
