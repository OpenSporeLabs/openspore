// See Mesh.hpp. Clean-room implementation, independently authored.
#include "Mesh.hpp"

#include <cmath>
#include <cstring>
#include <limits>

namespace openspore::assets {

namespace {

// Documented decl-type / usage codes accepted on the mesh path.
constexpr uint8_t kFloat3 = 2;
constexpr uint8_t kFloat2 = 1;
constexpr uint8_t kUByte4 = 5;
constexpr uint8_t kUsePosition = 0;
constexpr uint8_t kUseNormal = 3;
constexpr uint8_t kUseTexcoord = 5;
constexpr uint32_t kPrimTriangleList = 4;

bool fail(std::string& error, const std::string& what) {
  error = what;
  return false;
}

float readLEFloat(const uint8_t* p) {
  float v = 0.0F;
  std::memcpy(&v, p, 4);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  uint32_t b = 0;
  std::memcpy(&b, &v, 4);
  b = ((b & 0xFFu) << 24) | ((b & 0xFF00u) << 8) | ((b & 0xFF0000u) >> 8) |
      ((b & 0xFF000000u) >> 24);
  std::memcpy(&v, &b, 4);
#endif
  return v;
}

uint16_t readLEU16(const uint8_t* p) {
  uint16_t v = 0;
  std::memcpy(&v, p, 2);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  v = static_cast<uint16_t>((v << 8) | (v >> 8));
#endif
  return v;
}

}  // namespace

bool meshFromGmdl(const GmdlModel& model, uint32_t meshIndex, Mesh& out,
                  std::string& error) {
  out = Mesh{};
  error.clear();
  if (meshIndex >= model.meshes.size()) {
    return fail(error, "mesh: mesh index out of range");
  }
  const GmdlMeshRef& ref = model.meshes[meshIndex];
  if (ref.indexBuffer >= model.indexBuffers.size() ||
      ref.vertexBuffer >= model.vertexBuffers.size()) {
    return fail(error, "mesh: mesh references missing buffers");
  }
  const GmdlIndexBuffer& ib = model.indexBuffers[ref.indexBuffer];
  const GmdlVertexBuffer& vb = model.vertexBuffers[ref.vertexBuffer];
  if (ib.primType != kPrimTriangleList) {
    return fail(error, "mesh: unsupported primitive type " +
                           std::to_string(ib.primType) + " (want 4=trilist)");
  }
  if (ib.indexBits != 16) {
    return fail(error, "mesh: unsupported index width " +
                           std::to_string(ib.indexBits) + " (want 16)");
  }
  if (ib.indexCount == 0u) {
    return fail(error, "mesh: index buffer is empty");
  }
  if (vb.vertexCount == 0u) {
    return fail(error, "mesh: vertex buffer is empty");
  }
  if ((ib.indexCount % 3u) != 0u) {
    return fail(error, "mesh: triangle-list index count is not divisible by 3");
  }
  if (ib.indexCount > std::numeric_limits<size_t>::max() / 2u ||
      ib.bytes.size() < static_cast<size_t>(ib.indexCount) * 2u) {
    return fail(error, "mesh: index buffer truncated");
  }
  if (vb.descIndex >= model.descriptors.size()) {
    return fail(error, "mesh: bad vertex descriptor index");
  }
  const std::vector<GmdlVertexElement>& desc = model.descriptors[vb.descIndex];
  const GmdlVertexElement* posEl = nullptr;
  const GmdlVertexElement* nrmEl = nullptr;
  const GmdlVertexElement* uvEl = nullptr;
  for (const auto& e : desc) {
    if (e.stream != 0) {
      return fail(error, "mesh: unsupported non-zero stream");
    }
    if (e.declMethod != 0) {
      return fail(error, "mesh: unsupported vertex-declaration method " +
                             std::to_string(e.declMethod));
    }
    if (e.declUsage == kUsePosition && e.declType == kFloat3 &&
        posEl == nullptr) {
      posEl = &e;
    } else if (e.declUsage == kUseNormal && e.declType == kUByte4 &&
               nrmEl == nullptr) {
      nrmEl = &e;
    } else if (e.declUsage == kUseTexcoord && e.declType == kFloat2 &&
               uvEl == nullptr) {
      uvEl = &e;
    }
    // Any other element (COLOR, MATID, TANGENT, extra TEXCOORDs, ...) is not
    // consumed by this renderer and is ignored. Its on-disk size is still
    // validated by gmdlVertexStride below (an undocumented declType yields a
    // zero stride and fails there), so silently skipping is safe.
  }
  if (posEl == nullptr) {
    return fail(error, "mesh: descriptor has no POSITION/FLOAT3");
  }
  const uint32_t stride = gmdlVertexStride(desc);
  if (stride == 0) {
    return fail(error, "mesh: zero vertex stride");
  }
  if (vb.vertexCount > std::numeric_limits<size_t>::max() / stride ||
      vb.bytes.size() < static_cast<size_t>(vb.vertexCount) * stride) {
    return fail(error, "mesh: vertex buffer truncated");
  }

  out.topology = Topology::TriangleList;
  out.positions.reserve(vb.vertexCount);
  if (nrmEl != nullptr) {
    out.normals.reserve(vb.vertexCount);
  }
  if (uvEl != nullptr) {
    out.uvs.reserve(vb.vertexCount);
  }
  for (uint32_t i = 0; i < vb.vertexCount; ++i) {
    const uint8_t* row = vb.bytes.data() + static_cast<size_t>(i) * stride;
    const uint8_t* p = row + posEl->offset;
    const std::array<float, 3> position = {readLEFloat(p), readLEFloat(p + 4),
                                           readLEFloat(p + 8)};
    if (!std::isfinite(position[0]) || !std::isfinite(position[1]) ||
        !std::isfinite(position[2])) {
      out = Mesh{};
      return fail(error, "mesh: non-finite position");
    }
    out.positions.push_back(position);
    if (nrmEl != nullptr) {
      const uint8_t* n = row + nrmEl->offset;
      out.normals.push_back({n[0] / 255.0F, n[1] / 255.0F, n[2] / 255.0F});
    }
    if (uvEl != nullptr) {
      const uint8_t* t = row + uvEl->offset;
      const std::array<float, 2> texcoord = {readLEFloat(t),
                                             readLEFloat(t + 4)};
      if (!std::isfinite(texcoord[0]) || !std::isfinite(texcoord[1])) {
        out = Mesh{};
        return fail(error, "mesh: non-finite texcoord");
      }
      out.uvs.push_back(texcoord);
    }
  }
  out.indices.reserve(ib.indexCount);
  for (uint32_t i = 0; i < ib.indexCount; ++i) {
    const uint16_t idx =
        readLEU16(ib.bytes.data() + static_cast<size_t>(i) * 2);
    if (idx >= vb.vertexCount) {
      out = Mesh{};
      return fail(error, "mesh: index out of range");
    }
    out.indices.push_back(idx);
  }
  computeMeshBounds(out);
  return true;
}

void computeMeshBounds(Mesh& mesh) {
  if (mesh.positions.empty()) {
    mesh.bboxMin = {0, 0, 0};
    mesh.bboxMax = {0, 0, 0};
    mesh.radius = 0.0F;
    return;
  }
  std::array<float, 3> lo = mesh.positions[0];
  std::array<float, 3> hi = mesh.positions[0];
  for (const auto& p : mesh.positions) {
    for (size_t i = 0; i < 3; ++i) {
      if (p[i] < lo[i]) {
        lo[i] = p[i];
      }
      if (p[i] > hi[i]) {
        hi[i] = p[i];
      }
    }
  }
  mesh.bboxMin = lo;
  mesh.bboxMax = hi;
  const std::array<float, 3> center = {
      (lo[0] + hi[0]) * 0.5F, (lo[1] + hi[1]) * 0.5F, (lo[2] + hi[2]) * 0.5F};
  float r = 0.0F;
  for (const auto& p : mesh.positions) {
    const float dx = p[0] - center[0];
    const float dy = p[1] - center[1];
    const float dz = p[2] - center[2];
    const float d = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (d > r) {
      r = d;
    }
  }
  mesh.radius = r;
}

RendererMesh toRendererMesh(const Mesh& mesh) {
  RendererMesh out;
  out.vertices.reserve(mesh.positions.size());
  out.indices = mesh.indices;
  const bool useNormals = mesh.normals.size() == mesh.positions.size();
  const float spanY = mesh.bboxMax[1] - mesh.bboxMin[1];
  for (size_t i = 0; i < mesh.positions.size(); ++i) {
    Vertex v;
    v.pos[0] = mesh.positions[i][0];
    v.pos[1] = mesh.positions[i][1];
    v.pos[2] = mesh.positions[i][2];
    if (useNormals) {
      // Visualization choice: show the stored UBYTE4 normal bytes as color.
      v.color[0] = mesh.normals[i][0];
      v.color[1] = mesh.normals[i][1];
      v.color[2] = mesh.normals[i][2];
    } else {
      // Deterministic height ramp: steel blue low, ember high.
      float t = spanY > 0.0F ? (mesh.positions[i][1] - mesh.bboxMin[1]) / spanY
                             : 0.0F;
      if (t < 0.0F) {
        t = 0.0F;
      }
      if (t > 1.0F) {
        t = 1.0F;
      }
      v.color[0] = 0.15F + 0.75F * t;
      v.color[1] = 0.30F + 0.25F * t;
      v.color[2] = 0.65F - 0.45F * t;
    }
    out.vertices.push_back(v);
  }
  return out;
}

TexMesh toRendererTexMesh(const Mesh& mesh) {
  TexMesh out;
  out.vertices.reserve(mesh.positions.size());
  out.indices = mesh.indices;
  const bool hasNormals = mesh.normals.size() == mesh.positions.size();
  const bool hasUvs = mesh.uvs.size() == mesh.positions.size();
  for (size_t i = 0; i < mesh.positions.size(); ++i) {
    TexVertex v;
    v.pos[0] = mesh.positions[i][0];
    v.pos[1] = mesh.positions[i][1];
    v.pos[2] = mesh.positions[i][2];
    if (hasNormals) {
      v.normal[0] = mesh.normals[i][0];
      v.normal[1] = mesh.normals[i][1];
      v.normal[2] = mesh.normals[i][2];
    } else {
      v.normal[0] = 0.0F;
      v.normal[1] = 0.0F;
      v.normal[2] = 1.0F;
    }
    if (hasUvs) {
      v.uv[0] = mesh.uvs[i][0];
      v.uv[1] = mesh.uvs[i][1];
    } else {
      v.uv[0] = 0.0F;
      v.uv[1] = 0.0F;
    }
    out.vertices.push_back(v);
  }
  return out;
}

}  // namespace openspore::assets
