// Objective-8b vertical slice: draws the real chosen gmdl asset
// (type 0x00E6BCE5 / group 0x40637E03 / instance 0x067A07F0, 32 verts,
// 60 u16 indices) through the OpenSpore Vulkan offscreen renderer and proves
// visible geometry with pixel evidence.
//
// Usage: asset_view <path-to-Spore_Content.package>
// Env-dependent: exits 0 (SKIP) when the package is absent, so CI without
// the game still passes. Writes asset.ppm to the working directory and
// exits non-zero on any structural or pixel assertion failure.
// Clean-room code; no asset bytes are embedded.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"
#include "renderer/VulkanRenderer.hpp"

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

// Chosen asset identity + structural expectations (counts only; see
// docs/ASSET-PATH.md). No proprietary bytes here.
constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kGroup = 0x40637E03;
constexpr uint32_t kInstance = 0x067A07F0;
constexpr size_t kVertexCount = 32;
constexpr size_t kIndexCount = 60;

// Pixel acceptance window, calibrated from the measured render on
// RADV/NAVI31 (measured non-bg = 27685 at 512x512; window = measured
// +/-30%): [19380, 35990]. Bit-identical across runs (same md5).
constexpr uint32_t kViewport = 512;
constexpr size_t kMinDrawn = 19380;
constexpr size_t kMaxDrawn = 35990;

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

void writePpm(const char *path, const openspore::ImageRGBA &img) {
  std::FILE *f = std::fopen(path, "wb");
  if (f == nullptr) {
    std::fprintf(stderr, "[asset_view] cannot open %s for writing\n", path);
    return;
  }
  std::fprintf(f, "P6\n%u %u\n255\n", img.width, img.height);
  for (uint32_t y = 0; y < img.height; ++y) {
    for (uint32_t x = 0; x < img.width; ++x) {
      const size_t i = (static_cast<size_t>(y) * img.width + x) * 4;
      std::fputc(img.pixels[i + 0], f);
      std::fputc(img.pixels[i + 1], f);
      std::fputc(img.pixels[i + 2], f);
    }
  }
  std::fclose(f);
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: asset_view <Spore_Content.package>\n");
    return 1;
  }
  const std::vector<uint8_t> pkg = readFile(argv[1]);
  if (pkg.empty()) {
    std::printf("SKIP: package not found at %s (SPORE/ absent)\n", argv[1]);
    return 0;
  }

  std::string error;
  std::vector<DbpfEntry> entries;
  check(parseDbpfIndex(pkg.data(), pkg.size(), entries, error),
        "asset_view: package index parses");
  const int idx = findDbpfEntry(entries, kTypeGmdl, kGroup, kInstance);
  check(idx >= 0, "asset_view: chosen record present");
  if (idx < 0) {
    std::printf("asset_view: %d FAILURES\n", g_failures);
    return 1;
  }
  std::vector<uint8_t> blob;
  check(extractDbpfRecord(pkg.data(), pkg.size(),
                          entries[static_cast<size_t>(idx)], blob, error),
        "asset_view: record extracts");
  GmdlModel model;
  check(parseGmdl(blob.data(), blob.size(), model, error),
        "asset_view: gmdl parses");
  if (g_failures > 0) {
    std::printf("asset_view: %s\n", error.c_str());
    return 1;
  }

  Mesh mesh;
  check(meshFromGmdl(model, 0, mesh, error), "asset_view: mesh converts");
  if (g_failures > 0) {
    std::printf("asset_view: %s\n", error.c_str());
    return 1;
  }
  check(mesh.positions.size() == kVertexCount &&
            mesh.indices.size() == kIndexCount,
        "asset_view: mesh sizes 32v/60i");
  // First-vertex spot check against the Python oracle
  // (pos (-1.0099, 1.8000, 5.3054), normal bytes (230,107,59) as color).
  const RendererMesh base = toRendererMesh(mesh);
  check(base.vertices.size() == kVertexCount &&
            base.indices.size() == kIndexCount,
        "asset_view: renderer mesh sizes 32v/60i");
  check(near(mesh.positions[0][0], -1.0099F) &&
            near(mesh.positions[0][1], 1.8000F) &&
            near(mesh.positions[0][2], 5.3054F),
        "asset_view: first vertex position matches oracle");
  check(near(base.vertices[0].color[0], 230.0F / 255.0F) &&
            near(base.vertices[0].color[1], 107.0F / 255.0F) &&
            near(base.vertices[0].color[2], 59.0F / 255.0F),
        "asset_view: first vertex color matches oracle");
  if (g_failures > 0) {
    std::printf("asset_view: %d FAILURES\n", g_failures);
    return 1;
  }

  // CPU-side orthographic fit into clip space (passthrough shader has no
  // uniforms): model X -> NDC X, model Y -> NDC Y (flipped so model +Y is
  // screen-up), model Z -> NDC depth 0..0.5. Uniform scale from the runtime
  // X/Y extents so the largest screen span is 1.0 NDC = 50% of the viewport.
  // spanX=1.6985 spanY=2.0251 -> s=0.4938; cx=-1.2208 cy=1.1517.
  const float spanX = mesh.bboxMax[0] - mesh.bboxMin[0];
  const float spanY = mesh.bboxMax[1] - mesh.bboxMin[1];
  const float spanZ = mesh.bboxMax[2] - mesh.bboxMin[2];
  const float maxSpan = spanX > spanY ? spanX : spanY;
  const float s = 1.0F / maxSpan;
  const float cx = (mesh.bboxMin[0] + mesh.bboxMax[0]) * 0.5F;
  const float cy = (mesh.bboxMin[1] + mesh.bboxMax[1]) * 0.5F;
  std::printf("[asset_view] fit: span=(%.4f,%.4f,%.4f) s=%.4f c=(%.4f,%.4f)\n",
              spanX, spanY, spanZ, s, cx, cy);
  std::vector<openspore::Vertex> verts = base.vertices;
  for (auto &v : verts) {
    const float z = v.pos[2];
    v.pos[0] = (v.pos[0] - cx) * s;
    v.pos[1] = -((v.pos[1] - cy) * s);
    v.pos[2] = spanZ > 0.0F ? ((z - mesh.bboxMin[2]) / spanZ) * 0.5F : 0.25F;
  }

  openspore::VulkanRenderer renderer;
  if (!renderer.init(kViewport, kViewport)) {
    std::fprintf(stderr, "[asset_view] renderer init failed\n");
    return 1;
  }
  const openspore::MeshHandle handle = renderer.createMesh(
      verts.data(), verts.size(), base.indices.data(), base.indices.size());
  if (handle == openspore::kInvalidMesh) {
    std::fprintf(stderr, "[asset_view] createMesh failed\n");
    return 1;
  }
  renderer.beginFrame(0.0F, 0.0F, 0.0F, 1.0F);
  renderer.drawMesh(handle);
  renderer.endFrame();
  const openspore::ImageRGBA img = renderer.readbackPixels();
  writePpm("asset.ppm", img);

  // Pixel evidence: background is clear-black; drawn colors are normal bytes
  // as color (bright, e.g. first vertex (230,107,59)). A pixel counts as
  // drawn when r+g+b > 24, which keeps antialiased edge pixels.
  size_t drawn = 0;
  double sumX = 0.0;
  double sumY = 0.0;
  uint64_t sumRDrawn = 0;
  uint64_t sumGDrawn = 0;
  uint64_t sumBDrawn = 0;
  uint64_t sumRBg = 0;
  uint64_t sumGBg = 0;
  uint64_t sumBBg = 0;
  size_t bgCount = 0;
  for (uint32_t y = 0; y < img.height; ++y) {
    for (uint32_t x = 0; x < img.width; ++x) {
      const size_t i = (static_cast<size_t>(y) * img.width + x) * 4;
      const uint32_t r = img.pixels[i + 0];
      const uint32_t g = img.pixels[i + 1];
      const uint32_t b = img.pixels[i + 2];
      if (r + g + b > 24) {
        ++drawn;
        sumX += x;
        sumY += y;
        sumRDrawn += r;
        sumGDrawn += g;
        sumBDrawn += b;
      } else {
        ++bgCount;
        sumRBg += r;
        sumGBg += g;
        sumBBg += b;
      }
    }
  }
  const double comX = drawn > 0 ? sumX / drawn : 0.0;
  const double comY = drawn > 0 ? sumY / drawn : 0.0;
  std::printf("[asset_view] device=%s\n", renderer.deviceName().c_str());
  std::printf("[asset_view] drawn=%zu bg=%zu viewport=%ux%u\n", drawn, bgCount,
              img.width, img.height);
  std::printf("[asset_view] center-of-mass=(%.1f,%.1f)\n", comX, comY);
  if (drawn > 0) {
    std::printf(
        "[asset_view] drawn mean=(%.1f,%.1f,%.1f) bg mean=(%.2f,%.2f,%.2f)\n",
        static_cast<double>(sumRDrawn) / drawn,
        static_cast<double>(sumGDrawn) / drawn,
        static_cast<double>(sumBDrawn) / drawn,
        static_cast<double>(sumRBg) / bgCount,
        static_cast<double>(sumGBg) / bgCount,
        static_cast<double>(sumBBg) / bgCount);
  }
  check(drawn >= kMinDrawn && drawn <= kMaxDrawn,
        "asset_view: drawn pixel count in calibrated window");

  renderer.destroyMesh(handle);
  renderer.shutdown();
  if (g_failures == 0) {
    std::printf("asset_view: ALL PASS (32v/60i, %zu drawn px)\n", drawn);
    return 0;
  }
  std::printf("asset_view: %d FAILURES\n", g_failures);
  return 1;
}
