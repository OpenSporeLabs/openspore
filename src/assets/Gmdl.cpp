// See Gmdl.hpp. Clean-room implementation, independently authored.
#include "Gmdl.hpp"

#include <cstring>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

// Byte size of each documented D3DDECLTYPE code, indexed by code (0..16).
// Codes beyond the table are not understood by this walker.
constexpr uint32_t kDeclTypeSizes[] = {
    4,  // 0 FLOAT1
    8,  // 1 FLOAT2
    12, // 2 FLOAT3
    16, // 3 FLOAT4
    4,  // 4 D3DCOLOR
    4,  // 5 UBYTE4
    4,  // 6 SHORT2
    8,  // 7 SHORT4
    4,  // 8 UBYTE4N
    4,  // 9 SHORT2N
    8,  // 10 SHORT4N
    4,  // 11 USHORT2N
    8,  // 12 USHORT4N
    4,  // 13 UDEC3
    4,  // 14 DEC3N
    4,  // 15 FLOAT16_2
    8,  // 16 FLOAT16_4
};

uint32_t declTypeSize(uint8_t t) {
  return t < sizeof(kDeclTypeSizes) / sizeof(kDeclTypeSizes[0])
             ? kDeclTypeSizes[t]
             : 0;
}

// Byte size of each documented RenderWare ShaderData entry id. Id 0x20D
// (texture set) is decoded explicitly instead of skipped, so it is absent.
struct ShaderSize {
  uint32_t id;
  uint32_t size;
};
constexpr ShaderSize kShaderSizes[] = {
    {0x201, 8}, {0x202, 20}, {0x203, 8}, {0x204, 16}, {0x205, 20},
    {0x206, 256}, {0x208, 8}, {0x209, 4}, {0x20A, 64}, {0x20B, 64},
    {0x20C, 16}, {0x20E, 8}, {0x20F, 8}, {0x210, 20}, {0x211, 20},
    {0x212, 32}, {0x213, 48}, {0x216, 1}, {0x217, 1}, {0x21C, 32},
    {0x21E, 16}, {0x220, 16}, {0x223, 164}, {0x224, 152}, {0x226, 16},
    {0x22D, 16}, {0x22E, 16}, {0x22F, 16428}, {0x230, 4}, {0x231, 12},
    {0x232, 1}, {0x233, 4}, {0x235, 4}, {0x236, 4}, {0x237, 1},
    {0x238, 1}, {0x23B, 96}, {0x23C, 48}, {0x241, 64}, {0x242, 64},
    {0x243, 144}, {0x244, 1}, {0x245, 12}, {0x246, 20}, {0x247, 16},
    {0x248, 16}, {0x24A, 48}, {0x255, 32}, {0x256, 16},
};

uint32_t shaderDataSize(uint32_t id) {
  for (const auto &e : kShaderSizes) {
    if (e.id == id) {
      return e.size;
    }
  }
  return 0;
}

constexpr uint32_t kTextureSetId = 0x20D;
// One texture-set sampler entry: sampler id + 12 opaque bytes +
// instance/group key of the referenced texture (4 + 12 + 8 = 24 bytes).
constexpr size_t kTexEntrySize = 24;

bool fail(std::string &error, const char *what) {
  error = what;
  return false;
}

} // namespace

uint32_t gmdlVertexStride(const std::vector<GmdlVertexElement> &desc) {
  uint32_t stride = 0;
  for (const auto &e : desc) {
    const uint32_t size = declTypeSize(e.declType);
    if (size == 0) {
      return 0;
    }
    const uint32_t end = static_cast<uint32_t>(e.offset) + size;
    if (end > stride) {
      stride = end;
    }
  }
  return stride;
}

bool parseGmdl(const uint8_t *data, size_t size, GmdlModel &out,
               std::string &error) {
  out = GmdlModel{};
  if (data == nullptr) {
    return fail(error, "gmdl: null input");
  }
  Reader r(data, size);
  out.version = r.readU32();
  if (!r.ok()) {
    return fail(error, "gmdl: truncated header");
  }
  if (out.version != 8) {
    // Version 9 changes the material-info framing and is unvalidated; newer
    // records are outside this walker's tested path.
    error = "gmdl: unsupported version " + std::to_string(out.version) +
            " (want 8)";
    return false;
  }
  const uint32_t refCount = r.readU32();
  for (uint32_t i = 0; i < refCount; ++i) {
    r.skip(12); // {instance, group, type} file key
  }
  out.meshCount = r.readU32();
  for (int i = 0; i < 3; ++i) {
    out.bboxMin[static_cast<size_t>(i)] = r.readF32();
  }
  for (int i = 0; i < 3; ++i) {
    out.bboxMax[static_cast<size_t>(i)] = r.readF32();
  }
  out.radius = r.readF32();
  if (!r.ok()) {
    return fail(error, "gmdl: truncated bounds");
  }

  const uint32_t numIndexBuffers = r.readU32();
  for (uint32_t i = 0; i < numIndexBuffers; ++i) {
    GmdlIndexBuffer ib;
    ib.primType = r.readU32();
    ib.indexCount = r.readU32();
    ib.indexBits = r.readU32();
    const uint32_t bufSize = r.readU32();
    const uint8_t *view = nullptr;
    if (!r.readView(bufSize, view)) {
      return fail(error, "gmdl: truncated index buffer");
    }
    ib.bytes.assign(view, view + bufSize);
    out.indexBuffers.push_back(std::move(ib));
  }

  const uint32_t numDescs = r.readU32();
  for (uint32_t i = 0; i < numDescs; ++i) {
    const uint32_t elements = r.readU32();
    std::vector<GmdlVertexElement> desc;
    desc.reserve(elements);
    for (uint32_t k = 0; k < elements; ++k) {
      GmdlVertexElement e;
      e.stream = r.readU16();
      e.offset = r.readU16();
      e.declType = r.readU8();
      e.declMethod = r.readU8();
      e.declUsage = r.readU8();
      e.usageIndex = r.readU8();
      e.typeCode = r.readU32();
      desc.push_back(e);
    }
    if (!r.ok()) {
      return fail(error, "gmdl: truncated vertex descriptor");
    }
    for (const auto &e : desc) {
      if (declTypeSize(e.declType) == 0) {
        error = "gmdl: undocumented declType " + std::to_string(e.declType) +
                " in descriptor " + std::to_string(i);
        return false;
      }
    }
    out.descriptors.push_back(std::move(desc));
  }

  const uint32_t numVtxBufs = r.readU32();
  for (uint32_t i = 0; i < numVtxBufs; ++i) {
    GmdlVertexBuffer vb;
    vb.descIndex = r.readU32();
    vb.vertexCount = r.readU32();
    const uint32_t bufSize = r.readU32();
    const uint8_t *view = nullptr;
    if (!r.readView(bufSize, view)) {
      return fail(error, "gmdl: truncated vertex buffer");
    }
    vb.bytes.assign(view, view + bufSize);
    if (vb.descIndex >= out.descriptors.size()) {
      return fail(error, "gmdl: vertex buffer with bad descriptor index");
    }
    out.vertexBuffers.push_back(std::move(vb));
  }

  for (uint32_t i = 0; i < out.meshCount; ++i) {
    GmdlMeshRef m;
    m.indexBuffer = r.readU32();
    m.vertexBuffer = r.readU32();
    out.meshes.push_back(m);
  }
  for (uint32_t i = 0; i < out.meshCount; ++i) {
    out.materialIds.push_back(r.readU32());
  }
  r.skip(4); // observed zero word
  if (!r.ok()) {
    return fail(error, "gmdl: truncated mesh table");
  }

  const uint32_t matInfoCount = r.readU32();
  for (uint32_t i = 0; i < matInfoCount; ++i) {
    const uint32_t entries = r.readU32();
    for (uint32_t k = 0; k < entries; ++k) {
      const uint32_t id = r.readU32();
      if (!r.ok()) {
        return fail(error, "gmdl: truncated material info");
      }
      if (id == kTextureSetId) {
        const uint32_t texCount = r.readU32();
        if (!r.skip(static_cast<size_t>(texCount) * kTexEntrySize)) {
          return fail(error, "gmdl: truncated texture set");
        }
      } else {
        const uint32_t skip = shaderDataSize(id);
        if (skip == 0) {
          error = "gmdl: undocumented shader-data id 0x" + std::to_string(id) +
                  " in material info";
          return false;
        }
        if (!r.skip(skip)) {
          return fail(error, "gmdl: truncated shader data");
        }
      }
    }
  }

  const uint32_t boneRanges = r.readU32();
  if (!r.skip(static_cast<size_t>(boneRanges) * 8)) {
    return fail(error, "gmdl: truncated bone ranges");
  }
  const uint32_t animDatas = r.readU32();
  for (uint32_t i = 0; i < animDatas; ++i) {
    // Two baked transforms (64 bytes each) + flags + resource key.
    if (!r.skip(64 * 2 + 4 + 12)) {
      return fail(error, "gmdl: truncated anim data");
    }
    const uint32_t baked = r.readU32();
    if (!r.skip(static_cast<size_t>(baked) * 4)) {
      return fail(error, "gmdl: truncated baked deforms");
    }
  }
  for (int i = 0; i < 3; ++i) {
    out.unknownKey[static_cast<size_t>(i)] = r.readU32();
  }
  if (!r.ok()) {
    return fail(error, "gmdl: truncated trailer");
  }
  out.consumed = r.offset();
  if (out.consumed != size) {
    error = "gmdl: final offset " + std::to_string(out.consumed) +
            " != record size " + std::to_string(size);
    return false;
  }
  return true;
}

} // namespace openspore::assets
