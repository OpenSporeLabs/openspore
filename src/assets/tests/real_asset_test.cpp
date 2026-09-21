// Env-dependent real-asset test for openspore_assets.
//
// Loads the chosen Objective-8a asset (a small FloraModels-adjacent static
// gmdl) from the local game install at test time and asserts structural
// expectations WITHOUT committing any asset bytes: only counts, magic and
// version fields, bounding values, and first-vertex spot checks are compared
// against hardcoded expectations.
//
// Usage: real_asset_test <path-to-Spore_Content.package>
// Skips gracefully (exit 0) when the package is absent. Clean-room code.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

bool near(float a, float b, float eps = 1e-3F) {
  return std::fabs(a - b) <= eps;
}

// Chosen asset: smallest geometry-bearing gmdl in Spore_Content whose decode
// path is 100% documented (see docs/ASSET-PATH.md).
constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kGroup = 0x40637E03;
constexpr uint32_t kInstance = 0x067A07F0;
constexpr uint32_t kStoredSize = 794; // QFS bytes on disk
constexpr uint32_t kMemSize = 1156;   // decompressed record bytes
constexpr uint32_t kVertexCount = 32;
constexpr uint32_t kIndexCount = 60; // 20 triangles, trilist, u16
constexpr uint32_t kStride = 24;     // FLOAT3 pos + UBYTE4 normal + FLOAT2 uv
constexpr uint32_t kMaterialId = 0x407DFDDB;
constexpr float kRadius = 13.7738F;
// File-header bbox (metadata stored in the record).
constexpr float kFileMin[3] = {-6.5094F, -3.3870F, 0.0813F};
constexpr float kFileMax[3] = {3.2452F, 6.4511F, 11.8162F};
// Vertex-derived bbox (recomputed from the 32 decoded positions).
constexpr float kGeomMin[3] = {-2.0701F, 0.1391F, 0.0813F};
constexpr float kGeomMax[3] = {-0.3715F, 2.1643F, 5.3262F};

bool near3(const float *a, const float *b, float eps = 1e-3F) {
  return near(a[0], b[0], eps) && near(a[1], b[1], eps) &&
         near(a[2], b[2], eps);
}

std::vector<uint8_t> readFile(const char *path) {
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
  f.read(reinterpret_cast<char *>(b.data()), n);
  if (!f) {
    return {};
  }
  return b;
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: real_asset_test <Spore_Content.package>\n");
    return 1;
  }
  const std::vector<uint8_t> pkg = readFile(argv[1]);
  if (pkg.empty()) {
    // Env-dependent: no game install here (e.g. CI). Skip, do not fail.
    std::printf("SKIP: package not found at %s (SPORE/ absent); "
                "synthetic suite still covers the parsers\n",
                argv[1]);
    return 0;
  }

  std::string error;
  std::vector<DbpfEntry> entries;
  check(parseDbpfIndex(pkg.data(), pkg.size(), entries, error),
        "real: package index parses");
  if (!error.empty() && entries.empty()) {
    std::printf("index error: %s\n", error.c_str());
    return 1;
  }
  const int idx = findDbpfEntry(entries, kTypeGmdl, kGroup, kInstance);
  check(idx >= 0, "real: chosen record (gmdl 40637e03:067a07f0) present");
  if (idx < 0) {
    std::printf("real: %d FAILURES\n", g_failures);
    return 1;
  }
  const DbpfEntry &e = entries[static_cast<size_t>(idx)];
  check(e.compressed, "real: record QFS-flagged");
  check(e.storedSize == kStoredSize, "real: stored size 794");
  check(e.memSize == kMemSize, "real: mem size 1156");

  std::vector<uint8_t> blob;
  check(extractDbpfRecord(pkg.data(), pkg.size(), e, blob, error),
        "real: record extracts + decompresses");
  check(blob.size() == kMemSize, "real: decompressed 1156 bytes");

  GmdlModel model;
  check(parseGmdl(blob.data(), blob.size(), model, error),
        "real: gmdl parses end-to-end");
  if (g_failures > 0) {
    std::printf("gmdl error: %s\n", error.c_str());
    std::printf("real: %d FAILURES\n", g_failures);
    return 1;
  }
  check(model.version == 8, "real: version 8");
  check(model.meshCount == 1, "real: one mesh");
  check(near3(model.bboxMin.data(), kFileMin), "real: file bbox min");
  check(near3(model.bboxMax.data(), kFileMax), "real: file bbox max");
  check(near(model.radius, kRadius), "real: file radius 13.7738");
  check(model.indexBuffers.size() == 1 && model.indexBuffers[0].primType == 4 &&
            model.indexBuffers[0].indexCount == kIndexCount &&
            model.indexBuffers[0].indexBits == 16,
        "real: trilist u16 index buffer, 60 indices");
  check(model.vertexBuffers.size() == 1 &&
            model.vertexBuffers[0].vertexCount == kVertexCount,
        "real: 32-vertex buffer");
  check(gmdlVertexStride(model.descriptors[0]) == kStride,
        "real: stride 24 (pos+normal+uv)");
  check(model.materialIds.size() == 1 && model.materialIds[0] == kMaterialId,
        "real: material id 0x407dfddb");

  Mesh mesh;
  check(meshFromGmdl(model, 0, mesh, error), "real: mesh converts");
  check(mesh.positions.size() == kVertexCount &&
            mesh.indices.size() == kIndexCount,
        "real: mesh sizes 32v/60i");
  check(mesh.normals.size() == kVertexCount && mesh.uvs.size() == kVertexCount,
        "real: normals + uvs decoded");
  check(near3(mesh.bboxMin.data(), kGeomMin), "real: geometry bbox min");
  check(near3(mesh.bboxMax.data(), kGeomMax), "real: geometry bbox max");
  // First-vertex spot check (position + UBYTE4 normal bytes as color).
  check(near(mesh.positions[0][0], -1.0099F) &&
            near(mesh.positions[0][1], 1.8000F) &&
            near(mesh.positions[0][2], 5.3054F),
        "real: first vertex position");
  const RendererMesh rm = toRendererMesh(mesh);
  check(rm.vertices.size() == kVertexCount && rm.indices.size() == kIndexCount,
        "real: renderer mesh sizes");
  check(near(rm.vertices[0].color[0], 230.0F / 255.0F) &&
            near(rm.vertices[0].color[1], 107.0F / 255.0F) &&
            near(rm.vertices[0].color[2], 59.0F / 255.0F),
        "real: first vertex normal-derived color");

  if (g_failures == 0) {
    std::printf("assets real: ALL PASS (32 verts, 60 idx, bounds match)\n");
    return 0;
  }
  std::printf("real: %d FAILURES\n", g_failures);
  return 1;
}
