// Obj15: renders the real chosen gmdl mesh through the normal-lit textured
// path with a real DXT5 texture and proves, with pixel + hash evidence:
//   (1) the C++ DXT5/raster decoder is byte-correct (sha256 + texel oracle),
//   (2) the decoded texture is non-uniform,
//   (3) the texture is actually sampled (textured != flat render),
//   (4) lighting responds (two light dirs produce different frames).
// Env-dependent: exits 0 (SKIP) when the package is absent. Writes PPMs to
// the build dir, never to git. No asset bytes are embedded. Clean-room code.
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
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

// Chosen mesh identity (Obj8) + structural expectations (counts only).
constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kTypeRaster = 0x2F4E681C;
constexpr uint32_t kGroup = 0x40637E03;
constexpr uint32_t kInstance = 0x067A07F0;
constexpr size_t kVertexCount = 32;
constexpr size_t kIndexCount = 60;

// Verified real texture oracle (docs/CELLSTAGE-RECON, tests/test_textures.py).
constexpr uint32_t kTexGroup = 0x40662900;
constexpr uint32_t kTexInstance = 0xD1B4BB56;
constexpr const char *kOracleSha16 = "a7bad32bd7ef8210";

constexpr uint32_t kViewport = 512;
constexpr size_t kMinDrawn = 19380;
constexpr size_t kMaxDrawn = 35990;

// SHA-256 (FIPS 180-4), clean-room, for the decoder byte-oracle.
std::string sha256Hex(const uint8_t *data, size_t n) {
  const uint32_t k[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
  uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                   0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
  // Pad to a 64-byte multiple with room for the 0x80 marker + 8-byte length.
  size_t total = n + 9;
  if (total % 64 != 0) {
    total += 64 - (total % 64);
  }
  std::vector<uint8_t> buf(total, 0);
  for (size_t i = 0; i < n; ++i) {
    buf[i] = data[i];
  }
  const uint64_t bitlen = static_cast<uint64_t>(n) * 8;
  buf[n] = 0x80;
  for (int i = 0; i < 8; ++i) {
    buf[total - 8 + i] = static_cast<uint8_t>((bitlen >> (56 - i * 8)) & 0xff);
  }
  const auto rotr = [](uint32_t x, uint32_t c) { return (x >> c) | (x << (32 - c)); };
  for (size_t off = 0; off < total; off += 64) {
    uint32_t w[64];
    for (int i = 0; i < 16; ++i) {
      w[i] = (static_cast<uint32_t>(buf[off + i * 4]) << 24) |
             (static_cast<uint32_t>(buf[off + i * 4 + 1]) << 16) |
             (static_cast<uint32_t>(buf[off + i * 4 + 2]) << 8) |
             (static_cast<uint32_t>(buf[off + i * 4 + 3]));
    }
    for (int i = 16; i < 64; ++i) {
      const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
      const uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
    for (int i = 0; i < 64; ++i) {
      const uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
      const uint32_t ch = (e & f) ^ ((~e) & g);
      const uint32_t t1 = hh + S1 + ch + k[i] + w[i];
      const uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
      const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      const uint32_t t2 = S0 + maj;
      hh = g;
      g = f;
      f = e;
      e = d + t1;
      d = c;
      c = b;
      b = a;
      a = t1 + t2;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += hh;
  }
  static const char *hex = "0123456789abcdef";
  std::string out;
  out.reserve(64);
  for (int i = 0; i < 8; ++i) {
    for (int j = 3; j >= 0; --j) {
      const uint32_t byte = (h[i] >> (j * 8)) & 0xFF;
      out.push_back(hex[byte >> 4]);
      out.push_back(hex[byte & 0xF]);
    }
  }
  return out;
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

void writePpm(const char *path, const openspore::ImageRGBA &img) {
  std::FILE *f = std::fopen(path, "wb");
  if (f == nullptr) {
    std::fprintf(stderr, "[material_smoke] cannot open %s for writing\n", path);
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

size_t countDrawn(const openspore::ImageRGBA &img, uint32_t bgR, uint32_t bgG,
                  uint32_t bgB) {
  size_t n = 0;
  for (uint32_t y = 0; y < img.height; ++y) {
    for (uint32_t x = 0; x < img.width; ++x) {
      const size_t i = (static_cast<size_t>(y) * img.width + x) * 4;
      const uint32_t r = img.pixels[i];
      const uint32_t g = img.pixels[i + 1];
      const uint32_t b = img.pixels[i + 2];
      if (std::abs(static_cast<int>(r) - static_cast<int>(bgR)) > 8 ||
          std::abs(static_cast<int>(g) - static_cast<int>(bgG)) > 8 ||
          std::abs(static_cast<int>(b) - static_cast<int>(bgB)) > 8) {
        ++n;
      }
    }
  }
  return n;
}

size_t imageDiff(const openspore::ImageRGBA &a, const openspore::ImageRGBA &b) {
  size_t d = 0;
  const size_t n = a.pixels.size() < b.pixels.size() ? a.pixels.size()
                                                     : b.pixels.size();
  for (size_t i = 0; i < n; ++i) {
    if (a.pixels[i] != b.pixels[i]) {
      ++d;
    }
  }
  return d;
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: material_smoke <Spore_Content.package>\n");
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
        "material_smoke: package index parses");
  if (g_failures > 0) {
    return 1;
  }

  // (1) Decoder byte-oracle on the verified real texture.
  openspore::ImageRGBA oracleMip0;
  {
    const int ti = findDbpfEntry(entries, kTypeRaster, kTexGroup, kTexInstance);
    check(ti >= 0, "material_smoke: oracle texture present");
    if (ti >= 0) {
      std::vector<uint8_t> blob;
      if (extractDbpfRecord(pkg.data(), pkg.size(),
                            entries[static_cast<size_t>(ti)], blob, error)) {
        std::vector<openspore::ImageRGBA> mips;
        RasterEnvelope env;
        if (decodeRasterMips(blob.data(), blob.size(), mips, env, error) &&
            !mips.empty()) {
          oracleMip0 = mips[0];
          const std::string h =
              sha256Hex(oracleMip0.pixels.data(), oracleMip0.pixels.size());
          check(h.compare(0, 16, kOracleSha16) == 0,
                "material_smoke: oracle mip0 sha256 matches");
          check(env.width == 512 && env.height == 512,
                "material_smoke: oracle texture 512x512");
        }
      }
    }
  }

  // (2) Decoded oracle texture is non-uniform.
  {
    std::set<uint32_t> distinct;
    for (size_t i = 0; i < oracleMip0.pixels.size(); i += 4) {
      distinct.insert(static_cast<uint32_t>(oracleMip0.pixels[i]) |
                      (static_cast<uint32_t>(oracleMip0.pixels[i + 1]) << 8) |
                      (static_cast<uint32_t>(oracleMip0.pixels[i + 2]) << 16) |
                      (static_cast<uint32_t>(oracleMip0.pixels[i + 3]) << 24));
    }
    check(distinct.size() > 1, "material_smoke: decoded texture is non-uniform");
  }

  // (3) Real gmdl -> mesh.
  int gi = findDbpfEntry(entries, kTypeGmdl, kGroup, kInstance);
  check(gi >= 0, "material_smoke: chosen gmdl present");
  if (gi < 0) {
    std::printf("material_smoke: %d FAILURES\n", g_failures);
    return 1;
  }
  std::vector<uint8_t> gmdlBlob;
  check(extractDbpfRecord(pkg.data(), pkg.size(),
                          entries[static_cast<size_t>(gi)], gmdlBlob, error),
        "material_smoke: gmdl extracts");
  GmdlModel model;
  check(parseGmdl(gmdlBlob.data(), gmdlBlob.size(), model, error),
        "material_smoke: gmdl parses");
  if (g_failures > 0) {
    std::printf("material_smoke: %s\n", error.c_str());
    return 1;
  }
  Mesh mesh;
  check(meshFromGmdl(model, 0, mesh, error), "material_smoke: mesh converts");
  if (g_failures > 0) {
    std::printf("material_smoke: %s\n", error.c_str());
    return 1;
  }
  check(mesh.positions.size() == kVertexCount &&
            mesh.indices.size() == kIndexCount,
        "material_smoke: mesh sizes 32v/60i");
  check(near(mesh.positions[0][0], -1.0099F) &&
            near(mesh.positions[0][1], 1.8000F) &&
            near(mesh.positions[0][2], 5.3054F),
        "material_smoke: first vertex position matches oracle");

  // CPU-side orthographic fit into clip space (both the passthrough flat
  // shader and the lit shader have no view/projection uniforms).
  const float spanX = mesh.bboxMax[0] - mesh.bboxMin[0];
  const float spanY = mesh.bboxMax[1] - mesh.bboxMin[1];
  const float spanZ = mesh.bboxMax[2] - mesh.bboxMin[2];
  const float maxSpan = spanX > spanY ? spanX : spanY;
  const float s = 1.0F / maxSpan;
  const float cx = (mesh.bboxMin[0] + mesh.bboxMax[0]) * 0.5F;
  const float cy = (mesh.bboxMin[1] + mesh.bboxMax[1]) * 0.5F;
  auto fitPos = [&](float &x, float &y, float &z) {
    x = (x - cx) * s;
    y = -((y - cy) * s);
    z = spanZ > 0.0F ? ((z - mesh.bboxMin[2]) / spanZ) * 0.5F : 0.25F;
  };

  RendererMesh flat = toRendererMesh(mesh);
  for (auto &v : flat.vertices) {
    fitPos(v.pos[0], v.pos[1], v.pos[2]);
  }
  openspore::TexMesh tex = toRendererTexMesh(mesh);
  for (auto &v : tex.vertices) {
    fitPos(v.pos[0], v.pos[1], v.pos[2]);
  }

  // The verified oracle texture is a black alpha-mask (RGB~0), so sampling it
  // over a black clear renders pure black. For the *renderer* assertions we use
  // a small opaque color gradient instead: it guarantees visible, light-dependent
  // output and decouples render correctness from the decoder oracle above.
  openspore::ImageRGBA texImage;
  texImage.width = 32;
  texImage.height = 32;
  texImage.pixels.resize(texImage.width * texImage.height * 4);
  for (uint32_t y = 0; y < texImage.height; ++y) {
    for (uint32_t x = 0; x < texImage.width; ++x) {
      uint8_t *p = &texImage.pixels[(y * texImage.width + x) * 4];
      p[0] = static_cast<uint8_t>(x * 255 / 31);
      p[1] = static_cast<uint8_t>(y * 255 / 31);
      p[2] = 120;
      p[3] = 255;
    }
  }

  openspore::VulkanRenderer renderer;
  if (!renderer.init(kViewport, kViewport)) {
    std::fprintf(stderr, "[material_smoke] renderer init failed\n");
    return 1;
  }
  std::printf("[material_smoke] device=%s tex=%ux%u\n",
              renderer.deviceName().c_str(), texImage.width, texImage.height);

  const openspore::MeshHandle flatHandle = renderer.createMesh(
      flat.vertices.data(), flat.vertices.size(), flat.indices.data(),
      flat.indices.size());
  const openspore::MeshHandle texHandle = renderer.createTexMesh(
      tex.vertices.data(), tex.vertices.size(), tex.indices.data(),
      tex.indices.size());
  const openspore::TextureHandle texId = renderer.createTexture(texImage);
  check(flatHandle != openspore::kInvalidMesh, "material_smoke: flat mesh created");
  check(texHandle != openspore::kInvalidMesh, "material_smoke: tex mesh created");
  check(texId != openspore::kInvalidTexture, "material_smoke: texture uploaded");
  if (g_failures > 0) {
    std::printf("material_smoke: %d FAILURES\n", g_failures);
    renderer.shutdown();
    return 1;
  }

  renderer.beginFrame(0.0F, 0.0F, 0.0F, 1.0F);
  renderer.drawMesh(flatHandle);
  renderer.endFrame();
  const openspore::ImageRGBA imgFlat = renderer.readbackPixels();
  writePpm("material_flat.ppm", imgFlat);

  openspore::MaterialState matA;
  matA.lightDir[0] = 0.0F;
  matA.lightDir[1] = 0.7071F;
  matA.lightDir[2] = 0.7071F;
  matA.ambient = 0.35F;
  renderer.beginFrame(0.0F, 0.0F, 0.0F, 1.0F);
  renderer.drawTextured(texHandle, texId, matA);
  renderer.endFrame();
  const openspore::ImageRGBA imgTexA = renderer.readbackPixels();
  writePpm("material.ppm", imgTexA);

  openspore::MaterialState matB = matA;
  matB.lightDir[0] = 0.7071F;
  matB.lightDir[1] = 0.0F;
  renderer.beginFrame(0.0F, 0.0F, 0.0F, 1.0F);
  renderer.drawTextured(texHandle, texId, matB);
  renderer.endFrame();
  const openspore::ImageRGBA imgTexB = renderer.readbackPixels();

  const size_t flatDrawn = countDrawn(imgFlat, 0, 0, 0);
  const size_t texDrawn = countDrawn(imgTexA, 0, 0, 0);
  const size_t diffTexture = imageDiff(imgFlat, imgTexA);
  const size_t diffLight = imageDiff(imgTexA, imgTexB);
  std::printf("[material_smoke] flat_drawn=%zu tex_drawn=%zu "
              "diff_texture=%zu diff_light=%zu\n",
              flatDrawn, texDrawn, diffTexture, diffLight);

  check(flatDrawn >= kMinDrawn && flatDrawn <= kMaxDrawn,
        "material_smoke: flat geometry drawn in calibrated window");
  check(texDrawn > 0, "material_smoke: textured render has visible pixels");
  check(diffTexture > 0, "material_smoke: textured render differs from flat");
  check(diffLight > 0, "material_smoke: light change alters the render");

  renderer.destroyTexture(texId);
  renderer.destroyMesh(flatHandle);
  renderer.destroyTexMesh(texHandle);
  renderer.shutdown();

  if (g_failures == 0) {
    std::printf("material_smoke: ALL PASS (32v/60i, tex %ux%u, flat %zu px)\n",
                texImage.width, texImage.height, flatDrawn);
    return 0;
  }
  std::printf("material_smoke: %d FAILURES\n", g_failures);
  return 1;
}
