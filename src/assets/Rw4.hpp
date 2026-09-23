// Clean-room parser for RenderWare 4 (RW4) containers, Spore variant.
//
// Independently authored for OpenSpore. RW4 records (TYPE 0x2F4E681B) are the
// 1,131 graphics containers in SPORE/Data/Spore_Content.package (meshes, vertex
// buffers, skeletons, keyframe anims, compiled states). Layout (little-endian):
//
//   +0x00  28 B magic  "RW4w32\0\r\n\x1a\n\0 4\x00\x34\x35\x34\x00\x30\x30\x30\0\0\0\0\0"
//   +0x1C  u32 ftype   1 = MODEL, 0x04000000 = TEXTURE, 0xCAFED00D = SPECIAL
//   +0x20  u32 objCount
//   +0x24  u32 sectionCount
//   +0x30  u32 pSectionInfo   (array of 24-byte section infos)
//   +0x44  u32 pBufferData    (base for BaseResource data pointers)
//   +0x4C  u32 bufSize
//   +0x98  SectionManifest (tc 0x10004) -> o1..o4 offsets to
//            SectionTypes (0x10005, n + typecodes), arenas, subrefs, atoms.
//
// Each 24-byte section info: pData(u32) f04(u32) size(i32) align(i32)
// tcIndex(i32) tc(i32). A section's real data address is
//   pData + pBufferData   when tc == 0x10030 (BaseResource)
//   pData                 otherwise
// The parser walks the whole container and proves every section data pointer and
// type code is well-formed (in-bounds, known type code).
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

constexpr uint32_t kRw4Type = 0x2F4E681B;
constexpr size_t kRw4MagicSize = 28;

// One 24-byte section-info record, with the adjusted data address.
struct Rw4Section {
  uint32_t pData = 0;   // raw offset as stored
  uint32_t f04 = 0;
  int32_t size = 0;
  int32_t align = 0;
  int32_t tcIndex = 0;  // index into the manifest typecode table
  uint32_t tc = 0;      // type code
  uint32_t data = 0;    // adjusted: pData + pBufferData (BaseResource) else pData
};

// A decoded RW4 container.
struct Rw4 {
  static constexpr uint32_t kTypeModel = 1;
  static constexpr uint32_t kTypeTexture = 0x04000000;
  static constexpr uint32_t kTypeSpecial = 0xCAFED00D;
  static constexpr uint32_t kManifestTc = 0x10004;  // SectionManifest
  static constexpr uint32_t kTypesTc = 0x10005;     // SectionTypes

  uint32_t ftype = 0;
  uint32_t objCount = 0;
  uint32_t sectionCount = 0;
  uint32_t pSectionInfo = 0;
  uint32_t pBufferData = 0;
  uint32_t bufSize = 0;

  std::vector<uint32_t> typecodes;  // from SectionTypes (manifest.o1)
  std::vector<Rw4Section> sections;

  size_t recordSize = 0;

  // True when the container is structurally well-formed: the header/manifest/
  // types type codes are correct, every section data pointer + size is
  // in-bounds, and every section size is non-negative. (A section type code
  // outside the documented set is NOT a structural failure — see
  // unknownTypeCodes(); Spore adds codes the base SMFX map omits.)
  bool complete() const;

  // Number of sections whose type code is not in the documented SMFX map
  // (e.g. 0x7000c / 0x7000f Spore-specific codes). Informational only.
  size_t unknownTypeCodes() const;

  // Canonical one-line summary (used by the differential test to diff against
  // the python oracle): type + counts + per-section tc/data/size.
  std::string describe() const;
};

// Parses a whole RW4 record. True + populated on a well-formed walk. False +
// error when the magic does not match, the record is too short, the manifest /
// types type codes are wrong, or a section pointer / type code is out of range.
bool parseRw4(const uint8_t *data, size_t size, Rw4 &out, std::string &error);

// True when a type code is one of the known RW4 object / section types.
bool knownRw4TypeCode(uint32_t tc);

} // namespace openspore::assets
