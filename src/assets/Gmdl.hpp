// Minimal Spore GMDL (GameModel, type 0x00E6BCE5) record walker.
//
// Independently authored for OpenSpore. Walks the version-8 record layout
// needed for static single-mesh assets: header + bounds, index buffers, vertex
// descriptors/buffers, mesh refs, material IDs, and the material-info section.
// That renderable prefix is validated strictly (truncation is a hard error).
// The trailing bone-range / anim-data / baked-deform / resource-key block is
// animation data this path never consumes and has two on-disk variants, so it
// is accepted as an opaque trailer. Anything outside that path — version 9+
// records, undocumented shader-data IDs, 32-bit indices beyond the 16-bit path
// — is a hard error, not a silent skip.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

// D3DVERTEXELEMENT-style vertex element (12 bytes on disk).
struct GmdlVertexElement {
  uint16_t stream = 0;
  uint16_t offset = 0;
  uint8_t declType = 0;   // e.g. 2=FLOAT3, 5=UBYTE4, 1=FLOAT2
  uint8_t declMethod = 0; // always 0 (default) on the supported path
  uint8_t declUsage = 0;  // e.g. 0=POSITION, 3=NORMAL, 5=TEXCOORD
  uint8_t usageIndex = 0;
  uint32_t typeCode = 0;
};

struct GmdlIndexBuffer {
  uint32_t primType = 0; // 4 = triangle list on the supported path
  uint32_t indexCount = 0;
  uint32_t indexBits = 0; // 16 on the supported path
  std::vector<uint8_t> bytes;
};

struct GmdlVertexBuffer {
  uint32_t descIndex = 0;
  uint32_t vertexCount = 0;
  std::vector<uint8_t> bytes;
};

struct GmdlMeshRef {
  uint32_t indexBuffer = 0;
  uint32_t vertexBuffer = 0;
};

// Texture-set (0x20D) reference: the instance/group key of the referenced
// texture record (the on-disk entry carries no type word).
struct GmdlTextureRef {
  uint32_t instance = 0;
  uint32_t group = 0;
};

struct GmdlModel {
  uint32_t version = 0;
  uint32_t meshCount = 0;
  std::array<float, 3> bboxMin = {0, 0, 0};
  std::array<float, 3> bboxMax = {0, 0, 0};
  float radius = 0.0F;
  std::vector<GmdlIndexBuffer> indexBuffers;
  std::vector<std::vector<GmdlVertexElement>> descriptors;
  std::vector<GmdlVertexBuffer> vertexBuffers;
  std::vector<GmdlMeshRef> meshes;
  std::vector<uint32_t> materialIds;
  // Texture-set references in order of appearance (all meshes).
  std::vector<GmdlTextureRef> textureRefs;
  std::array<uint32_t, 3> unknownKey = {0, 0, 0};
  size_t consumed = 0; // input bytes consumed; equals input size on full parse
};

// Parses a whole GMDL record. False + error on any truncated, versioned-out,
// or undocumented content on the walk.
bool parseGmdl(const uint8_t *data, size_t size, GmdlModel &out,
               std::string &error);

// Interleaved vertex stride implied by one descriptor (max end offset).
// 0 when a decl type has no documented size (caller treats as an error).
uint32_t gmdlVertexStride(const std::vector<GmdlVertexElement> &desc);

} // namespace openspore::assets
