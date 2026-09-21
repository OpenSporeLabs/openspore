// Synthetic byte-buffer tests for openspore_assets (DBPF index parse,
// QFS round-trip, GMDL walk, mesh bounds). No real asset bytes: every input
// is hand-built below. Exit 0 on PASS, 1 on FAIL. Clean-room code.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"
#include "compat/MeshSource.hpp"
#include "compat/ResourceProvider.hpp"

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

bool near(float a, float b, float eps = 1e-5F) {
  return std::fabs(a - b) <= eps;
}

void pushU32(std::vector<uint8_t> &b, uint32_t v) {
  b.push_back(static_cast<uint8_t>(v & 0xFFu));
  b.push_back(static_cast<uint8_t>((v >> 8) & 0xFFu));
  b.push_back(static_cast<uint8_t>((v >> 16) & 0xFFu));
  b.push_back(static_cast<uint8_t>((v >> 24) & 0xFFu));
}

void pushU16(std::vector<uint8_t> &b, uint16_t v) {
  b.push_back(static_cast<uint8_t>(v & 0xFFu));
  b.push_back(static_cast<uint8_t>((v >> 8) & 0xFFu));
}

void pushF32(std::vector<uint8_t> &b, float v) {
  uint32_t bits = 0;
  std::memcpy(&bits, &v, 4);
  pushU32(b, bits);
}

// Minimal DBPF image: 96-byte header + flags + 2 rows (one raw, one QFS).
// The QFS record decodes to "ABCD": header 10 FB 000004, token 0xE0 (4
// literals), then the four bytes.
std::vector<uint8_t> buildDbpf() {
  std::vector<uint8_t> b;
  b.insert(b.end(), {'D', 'B', 'P', 'F'});
  pushU32(b, 3); // major
  pushU32(b, 0); // minor
  b.insert(b.end(), 20, 0);
  pushU32(b, 3);      // index major
  pushU32(b, 2);      // index count
  pushU32(b, 0);      // pad
  pushU32(b, 2 * 28); // index size
  b.insert(b.end(), 12, 0);
  pushU32(b, 3);  // index minor
  pushU32(b, 96); // index offset
  b.insert(b.end(), 28, 0);
  // b.size() == 96 here
  pushU32(b, 0); // index flags: per-row type+group
  // Row 0: raw record.
  const uint32_t off0 = 96 + 4 + 2 * 28;
  pushU32(b, 0x11111111);
  pushU32(b, 0x22222222);
  pushU32(b, 0x33333333);
  pushU32(b, off0);
  pushU32(b, 0x80000004u); // stored size with top bit set (masked by reader)
  pushU32(b, 4);           // mem size
  pushU16(b, 0);           // comp = none
  b.push_back(0);
  b.push_back(0);
  // Row 1: QFS record decoding to "ABCD".
  const uint32_t off1 = off0 + 4;
  pushU32(b, 0x44444444);
  pushU32(b, 0x55555555);
  pushU32(b, 0x66666666);
  pushU32(b, off1);
  pushU32(b, 0x8000000Au);
  pushU32(b, 4);
  pushU16(b, 0xFFFF); // comp = QFS
  b.push_back(0);
  b.push_back(0);
  // Payloads.
  b.insert(b.end(), {0xDE, 0xAD, 0xBE, 0xEF});
  b.insert(b.end(), {0x10, 0xFB, 0x00, 0x00, 0x04, 0xE0, 'A', 'B', 'C', 'D'});
  return b;
}

// Minimal version-8 GMDL: one right-triangle mesh, POSITION/FLOAT3 only,
// prim 4 (trilist), 16-bit indices, empty material/bone/anim trailer.
std::vector<uint8_t> buildGmdl() {
  std::vector<uint8_t> b;
  pushU32(b, 8); // version
  pushU32(b, 0); // refCount
  pushU32(b, 1); // meshCount
  pushF32(b, 0.0F);
  pushF32(b, 0.0F);
  pushF32(b, 0.0F); // bboxMin
  pushF32(b, 1.0F);
  pushF32(b, 1.0F);
  pushF32(b, 0.0F);    // bboxMax
  pushF32(b, 0.7071F); // radius
  pushU32(b, 1);       // numIndexBuffers
  pushU32(b, 4);       // prim = trilist
  pushU32(b, 3);       // indexCount
  pushU32(b, 16);      // indexBits
  pushU32(b, 6);       // bufferSize
  pushU16(b, 0);
  pushU16(b, 1);
  pushU16(b, 2);
  pushU32(b, 1); // numVertexDescriptors
  pushU32(b, 1); // elementCount
  pushU16(b, 0);
  pushU16(b, 0);  // stream, offset
  b.push_back(2); // declType FLOAT3
  b.push_back(0); // declMethod
  b.push_back(0); // declUsage POSITION
  b.push_back(0); // usageIndex
  pushU32(b, 0);  // typeCode
  pushU32(b, 1);  // numVertexBuffers
  pushU32(b, 0);  // descIndex
  pushU32(b, 3);  // vertexCount
  pushU32(b, 36); // bufferSize
  const float verts[9] = {0, 0, 0, 1, 0, 0, 0, 1, 0};
  for (float v : verts) {
    pushF32(b, v);
  }
  pushU32(b, 0);
  pushU32(b, 0);          // mesh: indexBuffer 0, vertexBuffer 0
  pushU32(b, 0x12345678); // materialID
  pushU32(b, 0);          // unk
  pushU32(b, 0);          // materialInfoCount
  pushU32(b, 0);          // boneRangeCount
  pushU32(b, 0);          // animDataCount
  pushU32(b, 0);
  pushU32(b, 0);
  pushU32(b, 0); // unknownKey
  return b;
}

void testDbpfIndex() {
  using namespace openspore::assets;
  const std::vector<uint8_t> img = buildDbpf();
  std::vector<DbpfEntry> entries;
  std::string error;
  check(parseDbpfIndex(img.data(), img.size(), entries, error),
        "dbpf: synthetic index parses");
  check(entries.size() == 2, "dbpf: two index rows");
  if (entries.size() == 2) {
    check(entries[0].type == 0x11111111 && entries[0].group == 0x22222222 &&
              entries[0].instance == 0x33333333,
          "dbpf: row 0 identity");
    check(entries[0].offset == 96 + 4 + 56 && entries[0].storedSize == 4 &&
              entries[0].memSize == 4 && !entries[0].compressed,
          "dbpf: row 0 extent (size mask applied, uncompressed)");
    check(entries[1].compressed && entries[1].memSize == 4 &&
              entries[1].storedSize == 10,
          "dbpf: row 1 QFS flag + sizes");
    check(findDbpfEntry(entries, 0x44444444, 0x55555555, 0x66666666) == 1,
          "dbpf: find by identity");
    check(findDbpfEntry(entries, 1, 2, 3) == -1, "dbpf: missing entry is -1");
  }
}

void testDbpfRejects() {
  using namespace openspore::assets;
  std::vector<DbpfEntry> entries;
  std::string error;
  const std::vector<uint8_t> tiny = {'D', 'B', 'P', 'F'};
  check(!parseDbpfIndex(tiny.data(), tiny.size(), entries, error),
        "dbpf: truncated image rejected");
  std::vector<uint8_t> bad(96, 0);
  std::memcpy(bad.data(), "XXXX", 4);
  check(!parseDbpfIndex(bad.data(), bad.size(), entries, error),
        "dbpf: bad magic rejected");
  std::vector<uint8_t> dbbf(96, 0);
  std::memcpy(dbbf.data(), "DBBF", 4);
  check(!parseDbpfIndex(dbbf.data(), dbbf.size(), entries, error),
        "dbpf: DBBF variant rejected");
}

void testQfs() {
  using namespace openspore::assets;
  const std::vector<uint8_t> img = buildDbpf();
  std::vector<DbpfEntry> entries;
  std::string error;
  check(parseDbpfIndex(img.data(), img.size(), entries, error),
        "qfs: index parses for extraction");
  if (entries.size() != 2) {
    return;
  }
  std::vector<uint8_t> raw;
  check(extractDbpfRecord(img.data(), img.size(), entries[0], raw, error),
        "qfs: raw record extracts");
  const std::vector<uint8_t> wantRaw = {0xDE, 0xAD, 0xBE, 0xEF};
  check(raw == wantRaw, "qfs: raw record bytes exact");
  std::vector<uint8_t> decomp;
  check(extractDbpfRecord(img.data(), img.size(), entries[1], decomp, error),
        "qfs: compressed record extracts");
  const std::vector<uint8_t> wantAbcd = {'A', 'B', 'C', 'D'};
  check(decomp == wantAbcd, "qfs: literal-run round-trips to ABCD");
  // Determinism: extract twice, compare.
  std::vector<uint8_t> again;
  check(extractDbpfRecord(img.data(), img.size(), entries[1], again, error),
        "qfs: second extraction succeeds");
  check(again == decomp, "qfs: extraction deterministic");
  // Direct API rejects a bad header.
  const std::vector<uint8_t> bad = {0x00, 0x00, 0x00, 0x00, 0x04};
  std::vector<uint8_t> junk;
  check(!qfsDecompress(bad.data(), bad.size(), junk, error),
        "qfs: bad header rejected");
}

void testGmdlWalk() {
  using namespace openspore::assets;
  const std::vector<uint8_t> blob = buildGmdl();
  GmdlModel model;
  std::string error;
  check(parseGmdl(blob.data(), blob.size(), model, error), "gmdl: parses");
  if (g_failures > 0) {
    std::printf("gmdl error: %s\n", error.c_str());
    return;
  }
  check(model.version == 8, "gmdl: version 8");
  check(model.meshCount == 1 && model.meshes.size() == 1, "gmdl: one mesh");
  check(model.consumed == blob.size(), "gmdl: final offset == record size");
  check(model.indexBuffers.size() == 1 && model.indexBuffers[0].primType == 4 &&
            model.indexBuffers[0].indexCount == 3 &&
            model.indexBuffers[0].indexBits == 16,
        "gmdl: trilist u16 index buffer");
  check(model.vertexBuffers.size() == 1 &&
            model.vertexBuffers[0].vertexCount == 3,
        "gmdl: 3-vertex buffer");
  check(gmdlVertexStride(model.descriptors[0]) == 12, "gmdl: stride 12");
  // Truncation must fail, not parse short.
  std::vector<uint8_t> cut(blob.begin(), blob.end() - 4);
  GmdlModel bad;
  check(!parseGmdl(cut.data(), cut.size(), bad, error),
        "gmdl: truncated record rejected");
}

void testMeshBounds() {
  using namespace openspore::assets;
  const std::vector<uint8_t> blob = buildGmdl();
  GmdlModel model;
  std::string error;
  if (!parseGmdl(blob.data(), blob.size(), model, error)) {
    check(false, "mesh: setup parse (see gmdl test)");
    return;
  }
  Mesh mesh;
  check(meshFromGmdl(model, 0, mesh, error), "mesh: converts");
  if (mesh.positions.size() != 3) {
    check(false, "mesh: three positions");
    return;
  }
  check(near(mesh.positions[2][1], 1.0F), "mesh: vertex data exact");
  check(mesh.indices == std::vector<uint32_t>({0, 1, 2}),
        "mesh: indices 0,1,2");
  check(near(mesh.bboxMin[0], 0.0F) && near(mesh.bboxMin[1], 0.0F) &&
            near(mesh.bboxMin[2], 0.0F),
        "mesh: bbox min (0,0,0)");
  check(near(mesh.bboxMax[0], 1.0F) && near(mesh.bboxMax[1], 1.0F) &&
            near(mesh.bboxMax[2], 0.0F),
        "mesh: bbox max (1,1,0)");
  // Radius = max distance from bbox center (0.5,0.5,0): sqrt(0.5).
  check(near(mesh.radius, 0.70710678F, 1e-4F), "mesh: bounding radius");
  check(mesh.normals.empty() && mesh.uvs.empty(),
        "mesh: no normal/uv without those elements");
  const RendererMesh rm = toRendererMesh(mesh);
  check(rm.vertices.size() == 3 && rm.indices.size() == 3,
        "mesh: renderer mesh sizes");
  // No normals -> height ramp: y=0 verts take the low color, y=1 the high.
  check(near(rm.vertices[0].color[2], 0.65F) &&
            near(rm.vertices[2].color[0], 0.90F),
        "mesh: height-ramp colors deterministic");
  check(near(rm.vertices[1].pos[0], 1.0F), "mesh: renderer positions exact");
}

} // namespace

// Null backend: proves IMeshSource feeds IRenderer with no GPU involved.
class NullRenderer : public openspore::IRenderer {
 public:
  bool init(uint32_t, uint32_t) override { return true; }
  void shutdown() override {}
  openspore::MeshHandle createMesh(const openspore::Vertex *, size_t nv,
                                   const uint32_t *, size_t ni) override {
    verts = nv;
    idx = ni;
    return 1;
  }
  void destroyMesh(openspore::MeshHandle) override {}
  void beginFrame(float, float, float, float) override {}
  void drawMesh(openspore::MeshHandle) override { ++draws; }
  void endFrame() override {}
  openspore::ImageRGBA readbackPixels() override { return {}; }
  size_t verts = 0, idx = 0, draws = 0;
};

namespace {

// Boundary test: the same consumer code runs against the DBPF package side
// and the in-memory original-side stub (substitutability), then stub ->
// mesh -> null renderer exercises the render-submit seam.
void testCompatBoundaries() {
  using namespace openspore;
  using namespace openspore::assets;
  using namespace openspore::compat;
  const std::vector<uint8_t> img = buildDbpf();
  const std::vector<uint8_t> gmdl = buildGmdl();
  DbpfResourceProvider dbpf(img.data(), img.size());
  MemoryResourceProvider stub;
  stub.store(0x11111111, 0x22222222, 0x33333333, {0xDE, 0xAD, 0xBE, 0xEF});
  stub.store(0x00E6BCE5, 0x40637E03, 0x067A07F0, gmdl);
  IResourceProvider *sides[2] = {&dbpf, &stub};
  const std::vector<uint8_t> wantRaw = {0xDE, 0xAD, 0xBE, 0xEF};
  for (IResourceProvider *p : sides) {
    std::vector<uint8_t> out;
    std::string error;
    check(p->fetch(0x11111111, 0x22222222, 0x33333333, out, error),
          "compat: same fetch via package and stub");
    check(out == wantRaw, "compat: identical bytes from both sides");
    check(!p->fetch(1, 2, 3, out, error),
          "compat: missing identity fails on both sides");
  }
  GmdlModel model;
  std::string error;
  check(fetchGmdlModel(stub, 0x00E6BCE5, 0x40637E03, 0x067A07F0, model, error),
        "compat: fetchGmdlModel via stub");
  check(model.consumed == gmdl.size(), "compat: stub model fully consumed");
  GmdlMeshSource source(std::move(model));
  Mesh mesh;
  check(source.loadMesh(0, mesh, error), "compat: IMeshSource loads mesh");
  check(mesh.positions.size() == 3, "compat: triangle positions");
  NullRenderer renderer;
  check(submitMeshSource(renderer, source, 0, error),
        "compat: mesh source submits to IRenderer");
  check(renderer.draws == 1 && renderer.verts == 3 && renderer.idx == 3,
        "compat: null backend saw one 3-vert draw");
}

} // namespace

int main() {
  testDbpfIndex();
  testDbpfRejects();
  testQfs();
  testGmdlWalk();
  testMeshBounds();
  testCompatBoundaries();
  if (g_failures == 0) {
    std::printf("assets synthetic: ALL PASS\n");
    return 0;
  }
  std::printf("assets synthetic: %d FAILURES\n", g_failures);
  return 1;
}
