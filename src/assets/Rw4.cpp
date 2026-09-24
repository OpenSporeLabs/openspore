// See Rw4.hpp. Clean-room implementation, independently authored.
#include "Rw4.hpp"

#include <cstdio>
#include <limits>
#include <utility>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

constexpr uint8_t kMagic[kRw4MagicSize] = {
    0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32, 0x00, 0x0D, 0x0A,
    0x1A, 0x0A, 0x00, 0x20, 0x04, 0x00, 0x34, 0x35, 0x34, 0x00,
    0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// Documented RW4 object / section type codes (SMFX map, docs/
// RENDERWARE-RESEARCH.md §7.5). Used only to count *undocumented* codes (e.g.
// Spore's 0x7000c / 0x7000f); it is NOT a structural gate.
bool inKnownSet(uint32_t tc) {
  switch (tc) {
    case 0x10030:   // BaseResource
    case 0x10004:   // SectionManifest
    case 0x10005:   // SectionTypes
    case 0x10006:   // SectionExternalArenas
    case 0x10007:   // SectionSubReferences
    case 0x10008:   // SectionAtoms
    case 0x20003:   // Raster
    case 0x20007:   // IndexBuffer
    case 0x20008:   // TextureOverride
    case 0x20009:   // Mesh
    case 0x2001a:   // MeshCompiledStateLink
    case 0x200af:   // BlendShapeBuffer
    case 0x2000b:   // (Spore-specific, unmapped)
    case 0x70001:   // KeyframeAnim
    case 0x70002:   // Skeleton
    case 0x70003:   // AnimationSkin
    case 0x7000b:   // (Spore-specific, unmapped)
    case 0x80003:   // TriangleKDTreeProcedural
    case 0x80005:   // BBox
    case 0xff0000:  // MorphHandle
    case 0xff0001:  // Animations
    case 0xff0002:  // BlendShape
      return true;
    default:
      return false;
  }
}

// u32 -> "0x<hex>" (lowercase, no leading zeros) for the canonical summary.
std::string hexNoPad(uint32_t v) {
  char buf[16];
  std::snprintf(buf, sizeof(buf), "0x%x", v);
  return buf;
}

std::string hexPlain(uint32_t v) {
  char buf[16];
  std::snprintf(buf, sizeof(buf), "%x", v);
  return buf;
}

}  // namespace

bool knownRw4TypeCode(uint32_t tc) { return inKnownSet(tc); }

bool Rw4::complete() const {
  if (sections.size() != sectionCount) {
    return false;
  }
  for (const Rw4Section& s : sections) {
    if (s.size < 0) {
      return false;
    }
    const uint64_t end =
        static_cast<uint64_t>(s.data) + static_cast<uint64_t>(s.size);
    if (end > recordSize) {
      return false;
    }
  }
  return true;
}

size_t Rw4::unknownTypeCodes() const {
  size_t n = 0;
  for (const Rw4Section& s : sections) {
    if (!inKnownSet(s.tc)) {
      ++n;
    }
  }
  return n;
}

std::string Rw4::describe() const {
  std::string line = hexNoPad(ftype) + " obj=" + std::to_string(objCount) +
                     " sec=" + std::to_string(sectionCount) +
                     " buf=" + std::to_string(bufSize);
  for (const Rw4Section& s : sections) {
    line += " | " + hexPlain(s.tc) + " d=" + hexNoPad(s.data) +
            " s=" + std::to_string(s.size);
  }
  return line;
}

bool parseRw4(const uint8_t* data, size_t size, Rw4& out, std::string& error) {
  out = Rw4{};
  error.clear();
  Rw4 parsed;
  parsed.recordSize = size;

  if (data == nullptr) {
    error = "rw4: null input";
    return false;
  }
  if (size < kRw4MagicSize + 0x78) {
    error =
        "record too small for RW4 header (" + std::to_string(size) + " bytes)";
    return false;
  }
  for (size_t i = 0; i < kRw4MagicSize; ++i) {
    if (data[i] != kMagic[i]) {
      error = "bad RW4 magic";
      return false;
    }
  }

  // Header words (absolute offsets).
  parsed.ftype =
      static_cast<uint32_t>((static_cast<uint32_t>(data[0x1C]) |
                             (static_cast<uint32_t>(data[0x1D]) << 8) |
                             (static_cast<uint32_t>(data[0x1E]) << 16) |
                             (static_cast<uint32_t>(data[0x1F]) << 24)));
  auto u32at = [&](size_t o) {
    return static_cast<uint32_t>(data[o]) |
           (static_cast<uint32_t>(data[o + 1]) << 8) |
           (static_cast<uint32_t>(data[o + 2]) << 16) |
           (static_cast<uint32_t>(data[o + 3]) << 24);
  };
  parsed.objCount = u32at(0x20);
  parsed.sectionCount = u32at(0x24);
  parsed.pSectionInfo = u32at(0x30);
  parsed.pBufferData = u32at(0x44);
  parsed.bufSize = u32at(0x4C);

  if (parsed.pBufferData > size || parsed.bufSize > size - parsed.pBufferData) {
    error = "buffer arena out of bounds";
    return false;
  }
  if (parsed.ftype != Rw4::kTypeModel && parsed.ftype != Rw4::kTypeTexture &&
      parsed.ftype != Rw4::kTypeSpecial) {
    error = "unknown ftype 0x" + hexPlain(parsed.ftype);
    return false;
  }

  // Manifest at 0x98.
  const size_t mo = 0x98;
  if (mo + 0x1C > size) {
    error = "record too small for manifest";
    return false;
  }
  const uint32_t manifestTc = u32at(mo);
  if (manifestTc != Rw4::kManifestTc) {
    error = "manifest typecode 0x" + hexPlain(manifestTc);
    return false;
  }
  const uint32_t o1 = u32at(mo + 0x0C);  // -> SectionTypes
  const uint64_t typesOffValue = static_cast<uint64_t>(mo) + o1;
  if (typesOffValue + 8u > size) {
    error = "SectionTypes out of bounds";
    return false;
  }
  const size_t typesOff = static_cast<size_t>(typesOffValue);
  const uint32_t typesTc = u32at(typesOff);
  if (typesTc != Rw4::kTypesTc) {
    error = "types typecode 0x" + hexPlain(typesTc);
    return false;
  }
  const uint32_t nTypes = u32at(typesOff + 4);
  const uint64_t typesEnd =
      typesOffValue + 8u + static_cast<uint64_t>(nTypes) * 4u;
  if (typesEnd > size) {
    error = "typecode table out of bounds (n=" + std::to_string(nTypes) + ")";
    return false;
  }
  parsed.typecodes.reserve(nTypes);
  for (uint32_t i = 0; i < nTypes; ++i) {
    parsed.typecodes.push_back(
        u32at(typesOff + 8u + static_cast<size_t>(i) * 4u));
  }

  // Section infos.
  if (parsed.pSectionInfo > size ||
      static_cast<uint64_t>(parsed.sectionCount) * 24u >
          size - parsed.pSectionInfo) {
    error = "section-info table out of bounds";
    return false;
  }
  parsed.sections.reserve(parsed.sectionCount);
  for (uint32_t i = 0; i < parsed.sectionCount; ++i) {
    const size_t o =
        static_cast<size_t>(parsed.pSectionInfo) + static_cast<size_t>(i) * 24u;
    Rw4Section s;
    s.pData = u32at(o);
    s.f04 = u32at(o + 4);
    s.size = static_cast<int32_t>(u32at(o + 8));
    s.align = static_cast<int32_t>(u32at(o + 0xC));
    s.tcIndex = static_cast<int32_t>(u32at(o + 0x10));
    s.tc = static_cast<uint32_t>(u32at(o + 0x14));
    const uint64_t data =
        s.tc == 0x10030 ? static_cast<uint64_t>(s.pData) + parsed.pBufferData
                        : s.pData;
    if (data > std::numeric_limits<uint32_t>::max()) {
      error = "section data address overflows";
      return false;
    }
    s.data = static_cast<uint32_t>(data);
    parsed.sections.push_back(s);
  }

  if (!parsed.complete()) {
    error = "section walk not well-formed (bad type code / out-of-bounds data)";
    return false;
  }
  out = std::move(parsed);
  return true;
}

}  // namespace openspore::assets
