// See WorldObject.hpp. Clean-room implementation, independently authored.
#include "WorldObject.hpp"

#include <algorithm>
#include <cmath>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

bool isLowerAscii(uint8_t b) {
  return b >= 'a' && b <= 'z';
}

bool isFiniteIn(float v, float lim) {
  return std::isfinite(v) && std::fabs(v) < lim;
}

} // namespace

bool parseWorldObject(const uint8_t *data, size_t size, WorldObject &out,
                      std::string &error) {
  if (size < kWorldObjectHeaderSize) {
    error = "record smaller than header (" + std::to_string(size) + " bytes)";
    return false;
  }
  Reader r(data, kWorldObjectHeaderSize);
  out.magic = r.readU32();
  out.version = r.readU32();
  out.countC = r.readU32();
  out.countD = r.readU32();
  out.countE = r.readU32();
  if (!r.ok()) {
    error = "truncated header";
    return false;
  }
  if (out.magic != kWorldObjectMagic) {
    error = "bad magic 0x" + std::to_string(out.magic);
    return false;
  }
  if (out.version != 9 && out.version != 10) {
    error = "unsupported version " + std::to_string(out.version);
    return false;
  }

  out.size = size;
  const size_t bodyStart = kWorldObjectHeaderSize;
  const uint8_t *body = data + bodyStart;
  const size_t bodyLen = size - bodyStart;
  out.bodyBytes = bodyLen;

  // Extract part-name strings: runs of 3+ lowercase ASCII bytes.
  out.names.clear();
  for (size_t i = 0; i < bodyLen;) {
    if (isLowerAscii(body[i])) {
      size_t j = i;
      while (j < bodyLen && isLowerAscii(body[j])) {
        ++j;
      }
      if (j - i >= 3) {
        WorldObjectName n;
        n.offset = i + bodyStart;
        n.name.assign(reinterpret_cast<const char *>(body + i), j - i);
        out.names.push_back(n);
      }
      i = j;
    } else {
      ++i;
    }
  }

  // Extract plausible vector3s over the data region (skip name bytes).
  out.vec3s.clear();
  for (size_t i = 0; i + 12 <= bodyLen;) {
    bool inName = false;
    for (const auto &n : out.names) {
      const size_t ns = n.offset - bodyStart;
      if (i >= ns && i + 3 < ns + n.name.size()) {
        inName = true;
        break;
      }
    }
    if (inName) {
      ++i;
      continue;
    }
    Reader vr(body + i, 12);
    const float x = vr.readF32();
    const float y = vr.readF32();
    const float z = vr.readF32();
    if (isFiniteIn(x, 16.0F) && isFiniteIn(y, 16.0F) && isFiniteIn(z, 16.0F) &&
        std::max({std::fabs(x), std::fabs(y), std::fabs(z)}) >= 0.001F) {
      WorldObjectVec3 v;
      v.offset = i + bodyStart;
      v.value = {x, y, z};
      out.vec3s.push_back(v);
      i += 12;
    } else {
      i += 4;
    }
  }

  // Byte accounting: body = name bytes + data bytes; header + body == size.
  for (const auto &n : out.names) {
    out.bodyNameBytes += n.name.size();
  }
  out.bodyDataBytes = bodyLen - out.bodyNameBytes;
  out.accounted = kWorldObjectHeaderSize + out.bodyNameBytes + out.bodyDataBytes;
  return true;
}

} // namespace openspore::assets
