// See Rw4.hpp. Clean-room implementation, independently authored.
#include "Rw4.hpp"

#include <cstdio>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

constexpr uint8_t kMagic[kRw4MagicSize] = {
    0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32, 0x00, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x20, 0x04, 0x00, 0x34, 0x35, 0x34, 0x00, 0x30, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

// Documented RW4 object / section type codes (SMFX map, docs/
// RENDERWARE-RESEARCH.md §7.5). Used only to count *undocumented* codes (e.g.
// Spore's 0x7000c / 0x7000f); it is NOT a structural gate.
bool inKnownSet(uint32_t tc) {
  switch (tc) {
    case 0x10030: // BaseResource
    case 0x10004: // SectionManifest
    case 0x10005: // SectionTypes
    case 0x10006: // SectionExternalArenas
    case 0x10007: // SectionSubReferences
    case 0x10008: // SectionAtoms
    case 0x20003: // Raster
    case 0x20007: // IndexBuffer
    case 0x20008: // TextureOverride
    case 0x20009: // Mesh
    case 0x2001a: // MeshCompiledStateLink
    case 0x200af: // BlendShapeBuffer
    case 0x2000b: // (Spore-specific, unmapped)
    case 0x70001: // KeyframeAnim
    case 0x70002: // Skeleton
    case 0x70003: // AnimationSkin
    case 0x7000b: // (Spore-specific, unmapped)
    case 0x80003: // TriangleKDTreeProcedural
    case 0x80005: // BBox
    case 0xff0000: // MorphHandle
    case 0xff0001: // Animations
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

} // namespace

bool knownRw4TypeCode(uint32_t tc) { return inKnownSet(tc); }

bool Rw4::complete() const {
  if (sections.size() != sectionCount) {
    return false;
  }
  for (const Rw4Section &s : sections) {
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
  for (const Rw4Section &s : sections) {
    if (!inKnownSet(s.tc)) {
      ++n;
    }
  }
  return n;
}

std::string Rw4::describe() const {
  std::string line =
      hexNoPad(ftype) + " obj=" + std::to_string(objCount) +
      " sec=" + std::to_string(sectionCount) + " buf=" +
      std::to_string(bufSize);
  for (const Rw4Section &s : sections) {
    line += " | " + hexPlain(s.tc) + " d=" + hexNoPad(s.data) + " s=" +
            std::to_string(s.size);
  }
  return line;
}

bool parseRw4(const uint8_t *data, size_t size, Rw4 &out, std::string &error) {
  out = Rw4{};
  out.recordSize = size;

  if (size < kRw4MagicSize + 0x78) {
    error = "record too small for RW4 header (" + std::to_string(size) +
            " bytes)";
    return false;
  }
  for (size_t i = 0; i < kRw4MagicSize; ++i) {
    if (data[i] != kMagic[i]) {
      error = "bad RW4 magic";
      return false;
    }
  }

  // Header words (absolute offsets).
  out.ftype = static_cast<uint32_t>(
      (static_cast<uint32_t>(data[0x1C]) |
       (static_cast<uint32_t>(data[0x1D]) << 8) |
       (static_cast<uint32_t>(data[0x1E]) << 16) |
       (static_cast<uint32_t>(data[0x1F]) << 24)));
  auto u32at = [&](size_t o) {
    return static_cast<uint32_t>(data[o]) |
           (static_cast<uint32_t>(data[o + 1]) << 8) |
           (static_cast<uint32_t>(data[o + 2]) << 16) |
           (static_cast<uint32_t>(data[o + 3]) << 24);
  };
  out.objCount = u32at(0x20);
  out.sectionCount = u32at(0x24);
  out.pSectionInfo = u32at(0x30);
  out.pBufferData = u32at(0x44);
  out.bufSize = u32at(0x4C);

  if (out.ftype != Rw4::kTypeModel && out.ftype != Rw4::kTypeTexture &&
      out.ftype != Rw4::kTypeSpecial) {
    error = "unknown ftype 0x" + hexPlain(out.ftype);
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
  const uint32_t typesOff = mo + o1;
  if (typesOff + 8 > size) {
    error = "SectionTypes out of bounds";
    return false;
  }
  const uint32_t typesTc = u32at(typesOff);
  if (typesTc != Rw4::kTypesTc) {
    error = "types typecode 0x" + hexPlain(typesTc);
    return false;
  }
  const uint32_t nTypes = u32at(typesOff + 4);
  if (typesOff + 8 + 4u * nTypes > size) {
    error = "typecode table out of bounds (n=" + std::to_string(nTypes) + ")";
    return false;
  }
  out.typecodes.reserve(nTypes);
  for (uint32_t i = 0; i < nTypes; ++i) {
    out.typecodes.push_back(u32at(typesOff + 8 + 4u * i));
  }

  // Section infos.
  const uint64_t secEnd =
      static_cast<uint64_t>(out.pSectionInfo) + 24u * out.sectionCount;
  if (secEnd > size) {
    error = "section-info table out of bounds";
    return false;
  }
  out.sections.reserve(out.sectionCount);
  for (uint32_t i = 0; i < out.sectionCount; ++i) {
    const size_t o = out.pSectionInfo + 24u * i;
    Rw4Section s;
    s.pData = u32at(o);
    s.f04 = u32at(o + 4);
    s.size = static_cast<int32_t>(u32at(o + 8));
    s.align = static_cast<int32_t>(u32at(o + 0xC));
    s.tcIndex = static_cast<int32_t>(u32at(o + 0x10));
    s.tc = static_cast<uint32_t>(u32at(o + 0x14));
    s.data = (s.tc == 0x10030) ? (s.pData + out.pBufferData) : s.pData;
    out.sections.push_back(s);
  }

  if (!out.complete()) {
    error = "section walk not well-formed (bad type code / out-of-bounds data)";
    return false;
  }
  return true;
}

} // namespace openspore::assets
