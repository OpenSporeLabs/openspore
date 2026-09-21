// OpenSpore host-side mesh: positions, optional normals/uvs, indices,
// topology, and computed bounds, plus conversion to renderer vertices.
//
// Independently authored for OpenSpore; no EA code, no third-party code.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Gmdl.hpp"
#include "renderer/Renderer.hpp"

namespace openspore::assets {

enum class Topology {
  Points,
  Lines,
  LineStrip,
  TriangleList,
  TriangleStrip,
  TriangleFan,
};

struct Mesh {
  std::vector<std::array<float, 3>> positions;
  // Per-vertex normals decoded from UBYTE4 to [0,1]; empty when the source
  // descriptor carries no NORMAL element.
  std::vector<std::array<float, 3>> normals;
  // Per-vertex texcoords; empty when the source carries no TEXCOORD element.
  std::vector<std::array<float, 2>> uvs;
  std::vector<uint32_t> indices;
  Topology topology = Topology::TriangleList;
  std::array<float, 3> bboxMin = {0, 0, 0};
  std::array<float, 3> bboxMax = {0, 0, 0};
  float radius = 0.0F; // max distance from the bbox center

  bool empty() const { return positions.empty() || indices.empty(); }
};

struct RendererMesh {
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
};

// Extracts one mesh from a parsed GMDL model. Understands POSITION/FLOAT3,
// NORMAL/UBYTE4, and TEXCOORD/FLOAT2 elements on stream 0, 16-bit index
// buffers, and triangle-list topology; anything else is a hard error.
bool meshFromGmdl(const GmdlModel &model, uint32_t meshIndex, Mesh &out,
                  std::string &error);

// Recomputes bboxMin/bboxMax/radius from the positions.
void computeMeshBounds(Mesh &mesh);

// Converts to renderer input. Color is a visualization choice, not original
// behavior: normals present -> color = normal bytes mapped to [0,1];
// otherwise -> a deterministic height ramp (low = steel blue, high = ember).
RendererMesh toRendererMesh(const Mesh &mesh);

// Interleaves positions + normals + uvs into a normal-lit TexMesh. Missing
// normals default to +Z; missing uvs default to (0,0).
TexMesh toRendererTexMesh(const Mesh &mesh);

} // namespace openspore::assets
