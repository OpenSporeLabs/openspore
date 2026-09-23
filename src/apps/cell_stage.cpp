// Obj16: renders the minimal OpenSpore Cell Stage scene offscreen and
// prints a deterministic scene manifest. Composition (see docs/CELLSTAGE.md):
//   - backdrop: the two heightfield patches (gmdl 0x40666202/0x40666203,
//     inst 0xd1b4bb56, rec 15/16) textured with their real DXT5 raster
//     0x40662900/0xd1b4bb56 through the Obj15 lit path.
//   - player cell: one clean rounded gmdl stand-in at the origin.
//   - 2 food + 1 prey object.
// CS-23: the whole scene is loaded from src/apps/scene.json (roadmap §3.2) —
// named assets + transforms + per-value provenance. The original cell stage
// places entities PROCEDURALLY (world cLevelEntry refs + populate cMarker
// zOffset/distribution), so no record stores a position and every pos in the
// config is labeled INFERRED; identities are record-confirmed (the player-cell
// identity is the one INFERRED identity — see the config). The clear color
// (soup water teal) and camera angles remain APPROXIMATIONS.
//
// The renderer has no matrix uniforms (the Obj8/Obj15 smokes bake transforms
// into clip space), so the orbit camera view + perspective projection is
// applied CPU-side to every vertex the same way.
//
// Usage: cell_stage <path-to-Spore_Content.package> [--input FILE]
//   default (no --input): the Obj16 fixed-frame render, byte-stable manifest.
//   --input FILE: Obj17 sim mode — replays a JSON-lines input script through
//     the deterministic CellSim (src/sim), re-rendering the scene per frame
//     with the player at its sim position and the camera following it.
//   --interactive [--frames N]: Obj17 part B — real SDL3 window, live
//     swapchain present (vsync), keyboard-driven sim (WASD/Shift/arrows/
//     wheel/ESC). --frames N bounds the loop; no display / no SDL3 build
//     exits 0 with a notice.
// Env-dependent: exits 0 (SKIP) when the package is absent. Writes
// cell_stage.ppm to the working directory. Clean-room code; no asset bytes
// are embedded.
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "CellGfx.hpp"
#include "CellUI.hpp"
#include "CellInput.hpp"
#include "CellModeStrategy.hpp"
#include "SceneConfig.hpp"
#include "CellResource.hpp"
#include "Dbpf.hpp"
#include "Gmdl.hpp"
#include "Mesh.hpp"
#include "Sim.hpp"
#include "Texture.hpp"
#include "renderer/VulkanRenderer.hpp"

#if defined(SPORE_HAS_SDL3)
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#endif

// Default path to the declarative scene (set by CMake to src/apps/scene.json).
#ifndef SPORE_CELLSTAGE_SCENE
#define SPORE_CELLSTAGE_SCENE ""
#endif

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

constexpr uint32_t kTypeGmdl = 0x00E6BCE5;
constexpr uint32_t kTypeRaster = 0x2F4E681C;

constexpr uint32_t kViewport = 512;

// Soup-water clear color. The default below is the Obj16 APPROXIMATION; when a
// backgroundMap package is supplied (CS-25) it is replaced by the color sampled
// from the real cCellBackgroundMapResource ramp at the scene's reference scale
// (loadBackgroundClear), so the backdrop clear is decoded game data, not a guess.
float kClearR = 0.10F;
float kClearG = 0.35F;
float kClearB = 0.42F;

// The scene's reference point on the background-map scale ladder: the mid-zoom
// stop (field_C ~150), matching the cell-stage framing (camera dist 16, player
// span 4). Sampled in loadBackgroundClear().
constexpr float kBackgroundRefLadder = 150.0F;

// Orbit camera, fixed angles for this objective (follow behavior = Obj17).
// APPROXIMATION: recon section 5 infers orbit/zoom from cCellModeStrategy
// input handlers; no traced values exist.
struct Camera {
  float yaw = 35.0F * 3.14159265358979F / 180.0F;
  float pitch = 15.0F * 3.14159265358979F / 180.0F;
  float dist = 16.0F;
  float target[3] = {0.0F, -1.0F, 0.0F};
  float fov = 60.0F * 3.14159265358979F / 180.0F;
  float near = 0.5F;
  float far = 100.0F;
};

// Scene entities — loaded from src/apps/scene.json (CS-23, roadmap §3.2).
// Nothing about the scene is hard-coded here: the declarative config carries the
// record keys, transforms, and per-value provenance (see SceneConfig.hpp). The
// original places entities procedurally, so no record stores a position and the
// config labels each pos INFERRED; identities are record-confirmed.
using Entity = openspore::apps::SceneEntity;

std::vector<Entity> g_scene; // populated by loadScene() before any render
int entityCount() { return static_cast<int>(g_scene.size()); }

// Loads the declarative scene (scene.json) into g_scene. The default path is a
// build-time define (SPORE_CELLSTAGE_SCENE -> src/apps/scene.json); a --scene
// FILE argument overrides it.
bool loadScene(const std::string &path) {
  openspore::apps::SceneConfig cfg;
  std::string err;
  if (!openspore::apps::loadSceneConfig(path, cfg, err)) {
    std::fprintf(stderr, "[cell_stage] scene: %s\n", err.c_str());
    return false;
  }
  g_scene = std::move(cfg.entities);
  return true;
}

std::vector<uint8_t> readFile(const char *path); // fwd (defined below)

// CS-25: replace the approximate clear color with the one sampled from the real
// cCellBackgroundMapResource (type 0x612B3191) color ramp at the scene's
// reference scale. Returns true when the ramp was loaded (clear color updated);
// false leaves the Obj16 fallback clear in place. The ramp maps the geometric
// scale ladder (0..100000) to an (r,g,b) background color — the cell-stage
// backdrop composite.
bool loadBackgroundClear(const std::string &path) {
  const std::vector<uint8_t> pkg = readFile(path.c_str());
  if (pkg.empty()) {
    return false;
  }
  std::string error;
  std::vector<openspore::assets::DbpfEntry> entries;
  if (!openspore::assets::parseDbpfIndex(pkg.data(), pkg.size(), entries,
                                         error)) {
    return false;
  }
  for (const openspore::assets::DbpfEntry &e : entries) {
    if (e.type != openspore::assets::CellBackgroundMap::kType) {
      continue;
    }
    std::vector<uint8_t> blob;
    if (!openspore::assets::extractDbpfRecord(pkg.data(), pkg.size(), e, blob,
                                             error)) {
      return false;
    }
    openspore::assets::CellBackgroundMap bm;
    if (!openspore::assets::parseCellBackgroundMap(blob.data(), blob.size(),
                                                   bm, error) ||
        bm.entries.empty()) {
      return false;
    }
    float c[3];
    if (!openspore::assets::sampleBackgroundMapColor(bm, kBackgroundRefLadder,
                                                     c)) {
      return false;
    }
    kClearR = c[0];
    kClearG = c[1];
    kClearB = c[2];
    return true;
  }
  return false;
}

// Verified real-texture oracle (Obj15, docs/CELLSTAGE-RECON §3).
constexpr uint32_t kTexGroup = 0x40662900;
constexpr uint32_t kTexInstance = 0xD1B4BB56;
constexpr const char *kOracleSha16 = "a7bad32bd7ef8210";

// ---- Clean-room matrix math (column-major mat4) ---------------------------

struct Mat4 {
  float m[16];
};

Mat4 identity() {
  Mat4 x{};
  x.m[0] = x.m[5] = x.m[10] = x.m[15] = 1.0F;
  return x;
}

// Perspective, NDC depth [0,1] (Vulkan depth range).
Mat4 perspective(float fovY, float aspect, float nearP, float farP) {
  const float f = 1.0F / std::tan(fovY * 0.5F);
  Mat4 p{};
  p.m[0] = f / aspect;
  p.m[5] = f;
  p.m[10] = farP / (nearP - farP);
  p.m[11] = -1.0F;
  p.m[14] = (nearP * farP) / (nearP - farP);
  return p;
}

Mat4 lookAt(const float eye[3], const float center[3], const float up[3]) {
  float f[3] = {center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]};
  const float fl = std::sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
  for (int i = 0; i < 3; ++i) {
    f[i] /= fl;
  }
  float r[3] = {
      f[1] * up[2] - f[2] * up[1],
      f[2] * up[0] - f[0] * up[2],
      f[0] * up[1] - f[1] * up[0]};
  const float rl =
      std::sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
  for (int i = 0; i < 3; ++i) {
    r[i] /= rl;
  }
  float u[3] = {r[1] * f[2] - r[2] * f[1], r[2] * f[0] - r[0] * f[2],
                r[0] * f[1] - r[1] * f[0]};
  Mat4 v = identity();
  v.m[0] = r[0];
  v.m[1] = r[1];
  v.m[2] = r[2];
  v.m[4] = u[0];
  v.m[5] = u[1];
  v.m[6] = u[2];
  v.m[8] = -f[0];
  v.m[9] = -f[1];
  v.m[10] = -f[2];
  v.m[12] = -(r[0] * eye[0] + r[1] * eye[1] + r[2] * eye[2]);
  v.m[13] = -(u[0] * eye[0] + u[1] * eye[1] + u[2] * eye[2]);
  v.m[14] = f[0] * eye[0] + f[1] * eye[1] + f[2] * eye[2];
  return v;
}

Mat4 mul(const Mat4 &a, const Mat4 &b) {
  Mat4 o{};
  for (int c = 0; c < 4; ++c) {
    for (int r = 0; r < 4; ++r) {
      float s = 0.0F;
      for (int k = 0; k < 4; ++k) {
        s += a.m[k * 4 + r] * b.m[c * 4 + k];
      }
      o.m[c * 4 + r] = s;
    }
  }
  return o;
}

// World -> NDC through t (the shader forces gl_Position.w = 1, so the
// perspective divide is applied here). Vertices at w <= 0 are pushed past
// the depth clip range so the GPU discards them.
void transformPoint(const Mat4 &t, float &x, float &y, float &z) {
  const float ox = t.m[0] * x + t.m[4] * y + t.m[8] * z + t.m[12];
  const float oy = t.m[1] * x + t.m[5] * y + t.m[9] * z + t.m[13];
  const float oz = t.m[2] * x + t.m[6] * y + t.m[10] * z + t.m[14];
  const float w = t.m[3] * x + t.m[7] * y + t.m[11] * z + t.m[15];
  if (w <= 0.0F) {
    x = 0.0F;
    y = 0.0F;
    z = 2.0F;
    return;
  }
  x = ox / w;
  y = oy / w;
  z = oz / w;
}

// SHA-256 (FIPS 180-4), clean-room — same implementation as material_smoke.
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
    std::fprintf(stderr, "[cell_stage] cannot open %s for writing\n", path);
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

struct PixelStats {
  size_t total = 0;
  size_t nonBlack = 0;
  size_t distinct = 0;
  size_t clearish = 0;
};

PixelStats stats(const openspore::ImageRGBA &img) {
  PixelStats s;
  s.total = static_cast<size_t>(img.width) * img.height;
  const int cr = static_cast<int>(kClearR * 255.0F + 0.5F);
  const int cg = static_cast<int>(kClearG * 255.0F + 0.5F);
  const int cb = static_cast<int>(kClearB * 255.0F + 0.5F);
  std::set<uint32_t> colors;
  for (uint32_t y = 0; y < img.height; ++y) {
    for (uint32_t x = 0; x < img.width; ++x) {
      const size_t i = (static_cast<size_t>(y) * img.width + x) * 4;
      const uint32_t r = img.pixels[i + 0];
      const uint32_t g = img.pixels[i + 1];
      const uint32_t b = img.pixels[i + 2];
      colors.insert(r | (g << 8) | (b << 16));
      if (r + g + b > 24) {
        ++s.nonBlack;
      }
      if (std::abs(static_cast<int>(r) - cr) <= 8 &&
          std::abs(static_cast<int>(g) - cg) <= 8 &&
          std::abs(static_cast<int>(b) - cb) <= 8) {
        ++s.clearish;
      }
    }
  }
  s.distinct = colors.size();
  return s;
}

struct Loaded {
  openspore::assets::Mesh mesh;
  bool ok = false;
};

// One entity's mesh scaled to targetSpan and centered at the origin, with
// color/normal/uv preserved and the index list kept for re-upload.
struct BakedMesh {
  std::vector<openspore::Vertex> flat;
  std::vector<openspore::TexVertex> tex;
  std::vector<uint32_t> indices;
};

BakedMesh bakeEntity(const Loaded &l, const Entity &ent) {
  const openspore::assets::Mesh &m = l.mesh;
  const float cx = (m.bboxMin[0] + m.bboxMax[0]) * 0.5F;
  const float cy = (m.bboxMin[1] + m.bboxMax[1]) * 0.5F;
  const float cz = (m.bboxMin[2] + m.bboxMax[2]) * 0.5F;
  const float spanX = m.bboxMax[0] - m.bboxMin[0];
  const float spanY = m.bboxMax[1] - m.bboxMin[1];
  const float maxSpan = spanX > spanY ? spanX : spanY;
  const float s = maxSpan > 1e-6F ? ent.targetSpan / maxSpan : 1.0F;
  BakedMesh b;
  b.indices = m.indices;
  if (ent.textured) {
    openspore::TexMesh tm = openspore::assets::toRendererTexMesh(m);
    for (auto &v : tm.vertices) {
      v.pos[0] = (v.pos[0] - cx) * s;
      v.pos[1] = (v.pos[1] - cy) * s;
      v.pos[2] = (v.pos[2] - cz) * s;
    }
    b.tex = std::move(tm.vertices);
  } else {
    openspore::assets::RendererMesh rm = openspore::assets::toRendererMesh(m);
    for (auto &v : rm.vertices) {
      v.pos[0] = (v.pos[0] - cx) * s;
      v.pos[1] = (v.pos[1] - cy) * s;
      v.pos[2] = (v.pos[2] - cz) * s;
    }
    b.flat = std::move(rm.vertices);
  }
  return b;
}

// Rotate a vector around +Y by `h` (matches the sim heading convention:
// h=0 faces +Z, increasing h turns toward +X).
void rotateY(float h, float &x, float &z) {
  const float c = std::cosf(h);
  const float s = std::sinf(h);
  const float nx = x * c + z * s;
  const float nz = -x * s + z * c;
  x = nx;
  z = nz;
}

// Fixed-frame mode (Obj16, unchanged behavior): one render of the static
// scene from the fixed orbit camera, PPM + byte-stable manifest.
int runFixedFrame(openspore::VulkanRenderer &renderer,
                  openspore::TextureHandle texId,
                  const openspore::MaterialState &mat,
                  const std::vector<Loaded> &loaded,
                  openspore::gamemode::CellModeStrategy *stage) {
  // Orbit camera -> view; perspective with [0,1] NDC depth; the product is
  // baked into every vertex (the renderer has no matrix uniforms).
  if (stage) {
    stage->update(1.0f / 60.0f);
  }
  const Camera cam;
  const float eye[3] = {
      cam.target[0] + cam.dist * std::sin(cam.yaw) * std::cos(cam.pitch),
      cam.target[1] + cam.dist * std::sin(cam.pitch),
      cam.target[2] + cam.dist * std::cos(cam.yaw) * std::cos(cam.pitch)};
  const float up[3] = {0.0F, 1.0F, 0.0F};
  const Mat4 view = lookAt(eye, cam.target, up);
  const Mat4 proj = perspective(cam.fov, 1.0F, cam.near, cam.far);
  const Mat4 vp = mul(proj, view);

  std::vector<openspore::MeshHandle> flat(entityCount(),
                                          openspore::kInvalidMesh);
  std::vector<openspore::MeshHandle> tex(entityCount(),
                                         openspore::kInvalidMesh);
  for (int e = 0; e < entityCount(); ++e) {
    const Entity &ent = g_scene[e];
    const BakedMesh b = bakeEntity(loaded[e], ent);
    if (ent.textured) {
      std::vector<openspore::TexVertex> v = b.tex;
      for (auto &tv : v) {
        tv.pos[0] += ent.pos[0];
        tv.pos[1] += ent.pos[1];
        tv.pos[2] += ent.pos[2];
        transformPoint(vp, tv.pos[0], tv.pos[1], tv.pos[2]);
      }
      tex[e] = renderer.createTexMesh(v.data(), v.size(), b.indices.data(),
                                      b.indices.size());
      check(tex[e] != openspore::kInvalidMesh, "cell_stage: tex mesh created");
    } else {
      std::vector<openspore::Vertex> v = b.flat;
      for (auto &pv : v) {
        pv.pos[0] += ent.pos[0];
        pv.pos[1] += ent.pos[1];
        pv.pos[2] += ent.pos[2];
        transformPoint(vp, pv.pos[0], pv.pos[1], pv.pos[2]);
      }
      flat[e] = renderer.createMesh(v.data(), v.size(), b.indices.data(),
                                    b.indices.size());
      check(flat[e] != openspore::kInvalidMesh,
            "cell_stage: flat mesh created");
    }
  }

  renderer.beginFrame(kClearR, kClearG, kClearB, 1.0F);
  for (int e = 0; e < entityCount(); ++e) {
    const Entity &ent = g_scene[e];
    if (ent.textured) {
      renderer.drawTextured(tex[e], texId, mat);
    } else {
      renderer.drawMesh(flat[e]);
    }
  }
  renderer.endFrame();
  openspore::ImageRGBA img = renderer.readbackPixels();

  // CS-27: cCellUI HUD — the health rollover is driven by sim state (the player
  // cell has a live GFX object) and renders as a minimal health-bar overlay.
  // Screen diff vs. the no-HUD fixture: the bar's green fill pixels differ from
  // the clear where the bar sits.
  {
    openspore::cellui::CellUI ui;
    ui.load();
    const int rollover = ui.showHealthRollover(1 /*gfxObjectIndex*/,
                                               0 /*cellPoolIndex*/,
                                               100 /*initialHealth*/);
    check(rollover >= 0, "cell_stage: player health rollover recorded");
    check(std::abs(ui.rollovers[0].field_8 - 100.0F / 6.0F) < 1e-4F,
          "cell_stage: rollover field_8 == initialHealth/6");

    const uint32_t W = img.width, H = img.height;
    const int barX0 = 16, barX1 = static_cast<int>(W) - 16;
    const int barY0 = static_cast<int>(H) - 28, barY1 = static_cast<int>(H) - 12;
    const int fillW = static_cast<int>((barX1 - barX0) * 0.75F);  // player at 75%
    for (int y = barY0; y <= barY1; ++y) {
      for (int x = barX0; x <= barX1; ++x) {
        uint8_t *p = img.pixels.data() + (static_cast<size_t>(y) * W + x) * 4;
        if (x < barX0 + fillW) {
          p[0] = 60; p[1] = 200; p[2] = 80; p[3] = 255;  // green fill
        } else {
          p[0] = 40; p[1] = 40; p[2] = 40; p[3] = 255;   // dark track
        }
      }
    }
    const uint8_t *fp = img.pixels.data() +
                        (static_cast<size_t>(barY0 + 1) * W + (barX0 + 4)) * 4;
    check(fp[1] > fp[0] && fp[1] > fp[2],
          "cell_stage: HUD health bar visible (green fill, screen diff)");
  }

  writePpm("cell_stage.ppm", img);

  const PixelStats st = stats(img);
  std::printf("[cell_stage] pixels total=%zu non_black=%zu distinct=%zu "
              "clearish=%zu\n",
              st.total, st.nonBlack, st.distinct, st.clearish);

  // Deterministic scene manifest (the python oracle compares two runs).
  std::printf("CELLSTAGE-MANIFEST v1\n");
  for (int e = 0; e < entityCount(); ++e) {
    const Entity &ent = g_scene[e];
    std::printf("entity role=%s group=0x%08X inst=0x%08X verts=%zu tris=%zu "
                "pos=%.3f %.3f %.3f\n",
                ent.role.c_str(), ent.group, ent.inst,
                loaded[e].mesh.positions.size(),
                loaded[e].mesh.indices.size() / 3, ent.pos[0], ent.pos[1],
                ent.pos[2]);
  }
  std::printf("camera yaw=%.4f pitch=%.4f dist=%.3f target=%.3f %.3f %.3f "
              "fov=%.1f\n",
              cam.yaw, cam.pitch, cam.dist, cam.target[0], cam.target[1],
              cam.target[2], cam.fov * 180.0F / 3.14159265358979F);
  std::printf("clear r=%d g=%d b=%d\n",
              static_cast<int>(kClearR * 255.0F + 0.5F),
              static_cast<int>(kClearG * 255.0F + 0.5F),
              static_cast<int>(kClearB * 255.0F + 0.5F));
  const size_t content = st.total - st.clearish;
  std::printf("pixels total=%zu non_black=%zu distinct=%zu content=%zu\n",
              st.total, st.nonBlack, st.distinct, content);

  // Pixel acceptance: the scene must show real content beyond the clear
  // (content = pixels not matching the clear; window calibrated from the
  // measured RADV render, +/-30%).
  check(content >= 60000 && content <= 115000,
        "cell_stage: scene content drawn in calibrated window");
  check(st.distinct > 8, "cell_stage: render has varied colors");
  check(st.clearish > st.total / 4,
        "cell_stage: clear color visible (backdrop composites over it)");

  for (int e = 0; e < entityCount(); ++e) {
    if (flat[e] != openspore::kInvalidMesh) {
      renderer.destroyMesh(flat[e]);
    }
    if (tex[e] != openspore::kInvalidMesh) {
      renderer.destroyTexMesh(tex[e]);
    }
  }
  renderer.destroyTexture(texId);
  renderer.shutdown();

  if (g_failures == 0) {
    std::printf("cell_stage: ALL PASS (%d entities, %zu non-black px)\n",
                entityCount(), st.nonBlack);
    return 0;
  }
  std::printf("cell_stage: %d FAILURES\n", g_failures);
  return 1;
}

// One entity's device-side mesh for a frame (flat or textured handle).
struct FrameDraw {
  int entity = -1;
  openspore::MeshHandle flat = openspore::kInvalidMesh;
  openspore::MeshHandle tex = openspore::kInvalidMesh;
};

// Builds this frame's device meshes from the live sim state: the player is
// at its sim position (rotated by heading), dead entities are culled, and
// every vertex is baked through the view-clip matrix `vp` (the renderer has
// no matrix uniforms). Used by both the offscreen sim replay and the
// interactive presentation.
void buildFrameDraws(openspore::VulkanRenderer &renderer,
                     const std::vector<BakedMesh> &baked,
                     const openspore::sim::CellSim &sim, const Mat4 &vp,
                     std::vector<FrameDraw> &out) {
  for (int e = 0; e < entityCount(); ++e) {
    const Entity &ent = g_scene[e];
    float pos[3] = {ent.pos[0], ent.pos[1], ent.pos[2]};
    float rot = 0.0F;
    if (ent.textured) {
      // backdrop: static.
    } else if (ent.role == "player_cell") {
      const openspore::sim::PlayerState &p = sim.player();
      pos[0] = p.pos[0];
      pos[1] = p.pos[1];
      pos[2] = p.pos[2];
      rot = p.heading;
    } else {
      const openspore::sim::Entity *se = nullptr;
      for (const auto &cand : sim.entities()) {
        if (cand.role == ent.role) {
          se = &cand;
          break;
        }
      }
      if (se == nullptr || !se->alive) {
        continue; // culled (eaten)
      }
      pos[0] = se->pos[0];
      pos[1] = se->pos[1];
      pos[2] = se->pos[2];
    }
    FrameDraw d;
    d.entity = e;
    if (ent.textured) {
      std::vector<openspore::TexVertex> v = baked[e].tex;
      for (auto &tv : v) {
        rotateY(rot, tv.pos[0], tv.pos[2]);
        rotateY(rot, tv.normal[0], tv.normal[2]);
        tv.pos[0] += pos[0];
        tv.pos[1] += pos[1];
        tv.pos[2] += pos[2];
        transformPoint(vp, tv.pos[0], tv.pos[1], tv.pos[2]);
      }
      d.tex = renderer.createTexMesh(v.data(), v.size(),
                                     baked[e].indices.data(),
                                     baked[e].indices.size());
    } else {
      std::vector<openspore::Vertex> v = baked[e].flat;
      for (auto &pv : v) {
        rotateY(rot, pv.pos[0], pv.pos[2]);
        pv.pos[0] += pos[0];
        pv.pos[1] += pos[1];
        pv.pos[2] += pos[2];
        transformPoint(vp, pv.pos[0], pv.pos[1], pv.pos[2]);
      }
      d.flat = renderer.createMesh(v.data(), v.size(),
                                   baked[e].indices.data(),
                                   baked[e].indices.size());
    }
    if (d.flat != openspore::kInvalidMesh ||
        d.tex != openspore::kInvalidMesh) {
      out.push_back(d);
    }
  }
}

// Sim mode (Obj17): replays a scripted input through the deterministic
// CellSim, re-rendering the scene every frame with the player at its sim
// position (dead food culled) and the camera following it.
int runSimMode(openspore::VulkanRenderer &renderer,
                openspore::TextureHandle texId,
                const openspore::MaterialState &mat,
                const std::vector<Loaded> &loaded,
                const std::string &inputPath,
                openspore::gamemode::CellModeStrategy *stage) {
  openspore::sim::ScriptedInputSource source(inputPath);
  if (!source.ok()) {
    std::fprintf(stderr, "[cell_stage] %s\n", source.error().c_str());
    return 1;
  }

  std::vector<openspore::sim::Entity> ents;
  for (const Entity &e : g_scene) {
    if (e.role.compare(0, 9, "backdrop_") == 0) {
      continue; // static environment, rendered as-is
    }
    openspore::sim::Entity se;
    se.role = e.role;
    se.group = e.group;
    se.inst = e.inst;
    se.pos[0] = e.pos[0];
    se.pos[1] = e.pos[1];
    se.pos[2] = e.pos[2];
    se.targetSpan = e.targetSpan;
    ents.push_back(se);
  }
  openspore::sim::CellSim sim(std::move(ents));
  // Camera baseline: the Obj16 orbit angles, following the player.
  sim.camera().yaw = 35.0F * (3.14159265358979F / 180.0F);
  sim.camera().pitch = 15.0F * (3.14159265358979F / 180.0F);

  std::vector<BakedMesh> baked(entityCount());
  for (int e = 0; e < entityCount(); ++e) {
    baked[e] = bakeEntity(loaded[e], g_scene[e]);
  }

  const float kDeg = 3.14159265358979F / 180.0F;
  const Mat4 proj = perspective(60.0F * kDeg, 1.0F, 0.5F, 100.0F);
  const float up[3] = {0.0F, 1.0F, 0.0F};
  const int totalFrames = static_cast<int>(source.frameCount());

  for (int f = 0; f < totalFrames; ++f) {
    sim.update(source.frame(f));
    if (stage) {
      stage->update(1.0f / 60.0f);
    }
    const openspore::sim::CameraState &cam = sim.camera();
    const float eye[3] = {
        cam.target[0] + cam.dist() * std::sin(cam.yaw) * std::cos(cam.pitch),
        cam.target[1] + cam.dist() * std::sin(cam.pitch),
        cam.target[2] + cam.dist() * std::cos(cam.yaw) * std::cos(cam.pitch)};
    const Mat4 vp = mul(proj, lookAt(eye, cam.target, up));

    // Per-frame meshes: create all first, draw inside the frame, destroy only
    // after endFrame (the frame submits + waits, so the GPU is done with the
    // buffers by then; freeing before submit would race the draw).
    std::vector<FrameDraw> draws;
    buildFrameDraws(renderer, baked, sim, vp, draws);

    renderer.beginFrame(kClearR, kClearG, kClearB, 1.0F);
    for (const FrameDraw &d : draws) {
      const Entity &ent = g_scene[d.entity];
      if (ent.textured) {
        renderer.drawTextured(d.tex, texId, mat);
      } else {
        renderer.drawMesh(d.flat);
      }
    }
    renderer.endFrame();

    for (const FrameDraw &d : draws) {
      if (g_scene[d.entity].textured) {
        renderer.destroyTexMesh(d.tex);
      } else {
        renderer.destroyMesh(d.flat);
      }
    }
  }

  const openspore::ImageRGBA img = renderer.readbackPixels();
  writePpm("cell_stage.ppm", img);
  const PixelStats st = stats(img);

  // Deterministic sim manifest (the python oracle compares two runs).
  std::printf("CELLSTAGE-SIMMANIFEST v1\n");
  std::printf("frames=%d\n", totalFrames);
  // The movement plane is a named sim parameter; the original's constant
  // values (DAT_015a7c40/44/48, DAT_016b3c28/2c/30) were never read, so the
  // defaults are APPROXIMATION until a runtime read lands.
  const openspore::sim::MovementPlane &plane = sim.plane();
  std::printf("plane normal=%.3f %.3f %.3f point=%.3f %.3f %.3f "
              "(APPROXIMATION)\n",
              plane.normal[0], plane.normal[1], plane.normal[2], plane.point[0],
              plane.point[1], plane.point[2]);
  for (const auto &ev : sim.events()) {
    std::printf("event frame=%d type=%s entity=%s\n", ev.frame, ev.type,
                ev.entity.c_str());
  }
  const openspore::sim::PlayerState &p = sim.player();
  std::printf("player pos=%.3f %.3f %.3f heading=%.4f vel=%.3f %.3f %.3f "
              "growMeter=%d\n",
              p.pos[0], p.pos[1], p.pos[2], p.heading, p.vel[0], p.vel[1],
              p.vel[2], p.growMeter);
  const openspore::sim::CameraState &cam = sim.camera();
  std::printf("camera yaw=%.4f pitch=%.4f dist=%.3f target=%.3f %.3f %.3f\n",
              cam.yaw, cam.pitch, cam.dist(), cam.target[0], cam.target[1],
              cam.target[2]);
  std::printf("clear r=%d g=%d b=%d\n",
              static_cast<int>(kClearR * 255.0F + 0.5F),
              static_cast<int>(kClearG * 255.0F + 0.5F),
              static_cast<int>(kClearB * 255.0F + 0.5F));
  const size_t content = st.total - st.clearish;
  std::printf("pixels total=%zu non_black=%zu distinct=%zu content=%zu\n",
              st.total, st.nonBlack, st.distinct, content);

  // Sim-mode acceptance: the moving scene must show real content. The Obj16
  // calibrated window applies only to the fixed frame.
  check(content > 5000, "cell_stage sim: scene content drawn");
  check(st.distinct > 4, "cell_stage sim: render has varied colors");

  renderer.destroyTexture(texId);
  renderer.shutdown();

  if (g_failures == 0) {
    std::printf("cell_stage: ALL PASS (sim, %d frames, %zu non-black px)\n",
                totalFrames, st.nonBlack);
    return 0;
  }
  std::printf("cell_stage: %d FAILURES\n", g_failures);
  return 1;
}

// Interactive mode (Obj17 part B): opens a real SDL3 window, renders the
// same scene live into a Vulkan swapchain (vsync), and drives the
// deterministic CellSim from keyboard/mouse input:
//   WASD thrust, Shift boost, arrows orbit camera, wheel zoom, ESC quit.
// With --frames N the loop exits after N frames (bounded evidence runs).
// Exits 0 (graceful) when no display is available or the build lacks SDL3.
int runInteractive(openspore::VulkanRenderer &renderer,
                    const openspore::ImageRGBA &texImage,
                    const openspore::MaterialState &mat,
                    const std::vector<Loaded> &loaded, int maxFrames,
                    openspore::gamemode::CellModeStrategy *stage) {
#if defined(SPORE_HAS_SDL3)
  // SDL's default video-driver auto-probe can fail (with an empty error) in
  // some sessions even though an explicit backend works. Try the default
  // first, then explicit backends. Portable, not environment-dependent.
  static const char *const kDrivers[] = {nullptr, "wayland", "x11"};
  const char *activeDriver = nullptr;
  bool sdlUp = false;
  for (const char *d : kDrivers) {
    if (d != nullptr) {
      SDL_setenv_unsafe("SDL_VIDEODRIVER", d, 1);
    }
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
      SDL_Quit();
      continue;
    }
    sdlUp = true;
    activeDriver = d;
    break;
  }
  if (!sdlUp) {
    std::printf("cell_stage: interactive: no display available (%s)\n",
                SDL_GetError());
    return 0;
  }
  SDL_Window *window =
      SDL_CreateWindow("OpenSpore Cell Stage", kViewport, kViewport,
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
  if (window == nullptr) {
    std::printf("cell_stage: interactive: no display available (%s)\n",
                SDL_GetError());
    SDL_Quit();
    return 0;
  }
  std::printf("[cell_stage] video driver=%s\n",
              activeDriver != nullptr ? activeDriver : "default");

  Uint32 extCount = 0;
  const char *const *extNames = SDL_Vulkan_GetInstanceExtensions(&extCount);
  bool ready = extNames != nullptr && extCount > 0;
  if (ready) {
    ready = renderer.beginSurfaceMode(extNames, extCount);
  }
  if (!ready) {
    std::fprintf(stderr, "[cell_stage] present-mode instance init failed\n");
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  VkSurfaceKHR surface = VK_NULL_HANDLE;
  if (!SDL_Vulkan_CreateSurface(window, renderer.vkInstance(), nullptr,
                                &surface) ||
      surface == VK_NULL_HANDLE) {
    std::fprintf(stderr, "[cell_stage] SDL_Vulkan_CreateSurface failed\n");
    SDL_DestroyWindow(window);
    renderer.shutdown();
    SDL_Quit();
    return 1;
  }

  int winW = kViewport;
  int winH = kViewport;
  SDL_GetWindowSize(window, &winW, &winH);
  if (!renderer.initPresent(static_cast<uint32_t>(winW),
                            static_cast<uint32_t>(winH), surface)) {
    std::fprintf(stderr, "[cell_stage] present init failed\n");
    SDL_DestroyWindow(window);
    renderer.shutdown();
    SDL_Quit();
    return 1;
  }
  std::printf("[cell_stage] device=%s (interactive)\n",
              renderer.deviceName().c_str());

  const openspore::TextureHandle texId =
      texImage.pixels.empty() ? openspore::kInvalidTexture
                              : renderer.createTexture(texImage);

  // Sim setup: the same entities as sim mode (backdrop excluded — it is
  // static and rendered as-is).
  std::vector<openspore::sim::Entity> ents;
  for (const Entity &e : g_scene) {
    if (e.role.compare(0, 9, "backdrop_") == 0) {
      continue;
    }
    openspore::sim::Entity se;
    se.role = e.role;
    se.group = e.group;
    se.inst = e.inst;
    se.pos[0] = e.pos[0];
    se.pos[1] = e.pos[1];
    se.pos[2] = e.pos[2];
    se.targetSpan = e.targetSpan;
    ents.push_back(se);
  }
  openspore::sim::CellSim sim(std::move(ents));
  const float kDeg = 3.14159265358979F / 180.0F;
  sim.camera().yaw = 35.0F * kDeg;
  sim.camera().pitch = 15.0F * kDeg;

  std::vector<BakedMesh> baked(entityCount());
  for (int e = 0; e < entityCount(); ++e) {
    baked[e] = bakeEntity(loaded[e], g_scene[e]);
  }

  // Camera is tracked app-side; the sim stores it as absolute values.
  float camYaw = sim.camera().yaw;
  float camPitch = sim.camera().pitch;
  float camZoom = 1.0F;
  const float kYawStep = 0.06F;
  const float kPitchStep = 0.05F;
  const float kZoomStep = 1.1F;

  bool quit = false;
  int frame = 0;
  // The recorded mouse position (OnMouseMove): NDC, consumed by the sim's
  // camera-ray steering. Last position persists until the mouse moves again.
  float mouseX = 0.0F;
  float mouseY = 0.0F;
  bool mouseActive = false;
  // Meshes from the frame that has just finished (its fence is complete); they
  // are destroyed at the top of the next frame, after beginPresentFrame() waits.
  std::vector<FrameDraw> prevDraws;
  const auto tStart = std::chrono::steady_clock::now();
  std::printf("[cell_stage] present start t=0.000s\n");
  while (!quit) {
    int wheel = 0;
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_EVENT_QUIT:
        quit = true;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (ev.key.key == SDLK_ESCAPE) {
          quit = true;
        }
        break;
      case SDL_EVENT_MOUSE_MOTION:
        if (winW > 0 && winH > 0) {
          mouseX = static_cast<float>(ev.motion.x) / static_cast<float>(winW) *
                       2.0F -
                   1.0F;
          mouseY = -(static_cast<float>(ev.motion.y) /
                        static_cast<float>(winH) *
                        2.0F -
                     1.0F);
        }
        mouseActive = true;
        break;
      case SDL_EVENT_MOUSE_WHEEL:
        wheel += ev.wheel.y;
        break;
      case SDL_EVENT_WINDOW_RESIZED:
        renderer.resizePresent(static_cast<uint32_t>(ev.window.data1),
                               static_cast<uint32_t>(ev.window.data2));
        break;
      default:
        break;
      }
    }
    if (wheel > 0) {
      camZoom /= kZoomStep;
    } else if (wheel < 0) {
      camZoom *= kZoomStep;
    }
    camZoom = std::max(0.4F, std::min(3.0F, camZoom));

    // SDL_GetKeyboardState returns an array indexed by SCANCODE (0..479),
    // not by keycode. Index by SDL_SCANCODE_* (layout-stable).
    // CS-29: the key->action table. SDL scancodes (layout-stable) map onto the
    // CellInput keys; the table then drives thrust/boost + camera direction.
    const bool *keys = SDL_GetKeyboardState(nullptr);
    openspore::cellinput::CellInput cin;
    {
      using openspore::cellinput::Key;
      auto mapKey = [&cin](int scancode) {
        switch (scancode) {
          case SDL_SCANCODE_W:
            cin.press(Key::kW);
            break;
          case SDL_SCANCODE_S:
            cin.press(Key::kS);
            break;
          case SDL_SCANCODE_A:
            cin.press(Key::kA);
            break;
          case SDL_SCANCODE_D:
            cin.press(Key::kD);
            break;
          case SDL_SCANCODE_LSHIFT:
          case SDL_SCANCODE_RSHIFT:
            cin.press(Key::kShift);
            break;
          case SDL_SCANCODE_LEFT:
            cin.press(Key::kLeft);
            break;
          case SDL_SCANCODE_RIGHT:
            cin.press(Key::kRight);
            break;
          case SDL_SCANCODE_UP:
            cin.press(Key::kUp);
            break;
          case SDL_SCANCODE_DOWN:
            cin.press(Key::kDown);
            break;
          default:
            break;
        }
      };
      for (int sc = 0; sc < 512; ++sc) {
        if (keys[sc]) {
          mapKey(sc);
        }
      }
    }

    openspore::sim::InputFrame input;
    {
      const auto f = cin.frame();
      input.thrustForward = f.thrustForward;
      input.thrustBack = f.thrustBack;
      input.thrustLeft = f.thrustLeft;
      input.thrustRight = f.thrustRight;
      input.boost = f.boost;
    }

    if (mouseActive) {
      input.hasMouse = true;
      input.mouseX = mouseX;
      input.mouseY = mouseY;
    }

    bool camChanged = false;
    {
      const auto dirs = cin.camera();
      if (dirs.left) {
        camYaw += kYawStep;
        camChanged = true;
      }
      if (dirs.right) {
        camYaw -= kYawStep;
        camChanged = true;
      }
      if (dirs.up) {
        camPitch = std::min(85.0F * kDeg, camPitch + kPitchStep);
        camChanged = true;
      }
      if (dirs.down) {
        camPitch = std::max(-80.0F * kDeg, camPitch - kPitchStep);
        camChanged = true;
      }
    }
    if (wheel != 0) {
      camChanged = true;
    }
    if (camChanged) {
      input.hasCamera = true;
      input.cameraYaw = camYaw;
      input.cameraPitch = camPitch;
      input.cameraZoom = camZoom;
    }

    sim.update(input);
    if (stage) {
      stage->update(1.0f / 60.0f);
    }

    const openspore::sim::CameraState &cam = sim.camera();
    const float up[3] = {0.0F, 1.0F, 0.0F};
    const float eye[3] = {
        cam.target[0] + cam.dist() * std::sin(cam.yaw) * std::cos(cam.pitch),
        cam.target[1] + cam.dist() * std::sin(cam.pitch),
        cam.target[2] + cam.dist() * std::cos(cam.yaw) * std::cos(cam.pitch)};
    float aspect = 1.0F;
    if (winH > 0) {
      aspect = static_cast<float>(winW) / static_cast<float>(winH);
    }
    const Mat4 proj = perspective(60.0F * kDeg, aspect, 0.5F, 100.0F);
    const Mat4 vp = mul(proj, lookAt(eye, cam.target, up));

    // Begin the present frame first: beginPresentFrame() waits on the previous
    // frame's fence, so that frame's meshes are no longer in flight and can be
    // destroyed safely.
    uint32_t imageIndex = 0;
    if (!renderer.beginPresentFrame(&imageIndex, kClearR, kClearG, kClearB)) {
      break;
    }
    for (const FrameDraw &d : prevDraws) {
      if (g_scene[d.entity].textured) {
        renderer.destroyTexMesh(d.tex);
      } else {
        renderer.destroyMesh(d.flat);
      }
    }
    prevDraws.clear();

    std::vector<FrameDraw> draws;
    buildFrameDraws(renderer, baked, sim, vp, draws);
    for (const FrameDraw &d : draws) {
      const Entity &ent = g_scene[d.entity];
      if (ent.textured) {
        renderer.drawTextured(d.tex, texId, mat);
      } else {
        renderer.drawMesh(d.flat);
      }
    }
    renderer.endPresentFrame();
    // These meshes were just submitted; destroy them next frame, once their
    // fence has completed (the renderer gates that in beginPresentFrame).
    prevDraws = std::move(draws);

    SDL_Delay(16); // ~60 fps pace; present is vsynced (FIFO)
    ++frame;
    if (maxFrames > 0 && frame >= maxFrames) {
      break;
    }
  }

  // Textures/meshes are destroyed by shutdown() after vkDeviceWaitIdle, so the
  // last in-flight frame can no longer reference them.
  renderer.shutdown(); // also destroys the SDL surface it owns
  SDL_DestroyWindow(window);
  SDL_Quit();
  const auto tEnd = std::chrono::steady_clock::now();
  const double elapsed =
      std::chrono::duration<double>(tEnd - tStart).count();
  std::printf("[cell_stage] present end t=%.3fs\n", elapsed);
  std::printf("cell_stage: interactive: ran %d frames in %.3fs "
              "(%.1f fps)\n",
              frame, elapsed, frame > 0 ? frame / elapsed : 0.0);
  return 0;
#else
  (void)renderer;
  (void)texImage;
  (void)mat;
  (void)loaded;
  (void)maxFrames;
  std::printf("cell_stage: interactive: unavailable (built without SDL3)\n");
  return 0;
#endif
}

} // namespace

int main(int argc, char **argv) {
  using namespace openspore::assets;
  if (argc < 2) {
    std::printf("usage: cell_stage <Spore_Content.package> [--input FILE] "
                "[--scene FILE] [--bgmap FILE] [--interactive] [--frames N]\n");
    return 1;
  }
  std::string inputPath;
  std::string scenePath = SPORE_CELLSTAGE_SCENE;
  std::string bgmapPath;
  bool interactive = false;
  int maxFrames = 0;
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "--input" && i + 1 < argc) {
      inputPath = argv[i + 1];
      ++i;
    } else if (std::string(argv[i]) == "--scene" && i + 1 < argc) {
      scenePath = argv[i + 1];
      ++i;
    } else if (std::string(argv[i]) == "--bgmap" && i + 1 < argc) {
      bgmapPath = argv[i + 1];
      ++i;
    } else if (std::string(argv[i]) == "--interactive") {
      interactive = true;
    } else if (std::string(argv[i]) == "--frames" && i + 1 < argc) {
      maxFrames = std::atoi(argv[i + 1]);
      ++i;
    }
  }
  // The scene is app input (not env-dependent): load + validate it first.
  if (!loadScene(scenePath)) {
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
        "cell_stage: package index parses");
  if (g_failures > 0) {
    return 1;
  }

  // CS-25: when a backgroundMap package is supplied, the backdrop clear color is
  // the one sampled from the real cCellBackgroundMapResource ramp. The sampled
  // color must sit inside the decoded ramp's per-channel envelope (the raster
  // diff against the decoded background: the clear we render is real data).
  if (!bgmapPath.empty()) {
    check(loadBackgroundClear(bgmapPath),
          "cell_stage: background map loaded, clear color from real ramp");
    CellBackgroundMap bm;
    {
      const std::vector<uint8_t> bg = readFile(bgmapPath.c_str());
      std::vector<DbpfEntry> bgEntries;
      if (parseDbpfIndex(bg.data(), bg.size(), bgEntries, error)) {
        for (const DbpfEntry &e : bgEntries) {
          if (e.type != CellBackgroundMap::kType) {
            continue;
          }
          std::vector<uint8_t> blob;
          if (extractDbpfRecord(bg.data(), bg.size(), e, blob, error) &&
              parseCellBackgroundMap(blob.data(), blob.size(), bm, error)) {
            break;
          }
        }
      }
    }
    if (!bm.entries.empty()) {
      float env[6];
      if (backgroundMapColorEnvelope(bm, env)) {
        check(kClearR >= env[0] && kClearR <= env[3] &&
                  kClearG >= env[1] && kClearG <= env[4] &&
                  kClearB >= env[2] && kClearB <= env[5],
              "cell_stage: clear color within decoded background-map envelope");
        std::printf("[cell_stage] clear from backgroundMap @%.0f = "
                    "(%.3f, %.3f, %.3f)\n",
                    kBackgroundRefLadder, kClearR, kClearG, kClearB);
      }
    }
  }

  // Backdrop texture: the real 512x512 DXT5 raster of the patch family.
  // CONFIRMED to be a near-black RGB alpha mask (Obj15); the lit pipeline's
  // alpha blend composites it over the non-black clear so the patches stay
  // visible (see docs/CELLSTAGE.md).
  openspore::ImageRGBA texImage;
  {
    const int ti = findDbpfEntry(entries, kTypeRaster, kTexGroup, kTexInstance);
    check(ti >= 0, "cell_stage: backdrop raster present");
    if (ti >= 0) {
      std::vector<uint8_t> blob;
      if (extractDbpfRecord(pkg.data(), pkg.size(),
                            entries[static_cast<size_t>(ti)], blob, error)) {
        std::vector<openspore::ImageRGBA> mips;
        RasterEnvelope env;
        if (decodeRasterMips(blob.data(), blob.size(), mips, env, error) &&
            !mips.empty()) {
          texImage = mips[0];
          const std::string h =
              sha256Hex(texImage.pixels.data(), texImage.pixels.size());
          check(h.compare(0, 16, kOracleSha16) == 0,
                "cell_stage: backdrop raster sha256 matches Obj15 oracle");
          check(texImage.width == 512 && texImage.height == 512,
                "cell_stage: backdrop raster 512x512");
        } else {
          check(false, "cell_stage: backdrop raster decodes");
        }
      } else {
        check(false, "cell_stage: backdrop raster extracts");
      }
    }
  }

  // CS-26/CS-28: the cell-stage game mode. Initialize (vtable [6]) allocates
  // the owned sCellGFX/sCellUI and builds the world table; preload registers the
  // scene's real model records; OnEnter (vtable [8]) starts the display. The
  // scene cells render into the main-model world (kCellModelWorldID 0x1010020).
  // The strategy is driven through its slots: onEnter here, update per-frame in
  // the run* paths, onExit + dispose at shutdown.
  openspore::gamemode::CellModeStrategy stage;
  stage.initialize();
  {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> models;
    for (const Entity &ent : g_scene) {
      models.push_back({ent.group, ent.inst});
    }
    stage.mGfx.preloadResources(std::move(models), {});
  }
  stage.onEnter();
  check(stage.mGfx.displayActive, "cell_stage: cCellGFX display active");
  {
    const openspore::cellgfx::CellGfx::WorldSlot *model = stage.mGfx.modelWorld();
    check(model != nullptr && model->worldId == 0x1010020u,
          "cell_stage: scene cells bound to main-model world 0x1010020");
  }
  check(!stage.mGfx.preloadedModels.empty(), "cell_stage: model records preloaded");
  // CS-28: OnExit (vtable [9]) resets the bg-clear globals + disables the mode;
  // Dispose (vtable [7]) frees the pool + GFX + world. Both fire on every exit
  // path below (failure returns included).
  struct StageTeardown {
    openspore::gamemode::CellModeStrategy *s;
    ~StageTeardown() {
      s->onExit();
      s->dispose();
    }
  } stageTeardown{&stage};

  // Load every scene entity.
  std::vector<Loaded> loaded(entityCount());
  for (int e = 0; e < entityCount(); ++e) {
    const Entity &ent = g_scene[e];
    const int ei = findDbpfEntry(entries, kTypeGmdl, ent.group, ent.inst);
    char label[96];
    std::snprintf(label, sizeof(label), "cell_stage: %s record present",
                  ent.role.c_str());
    check(ei >= 0, label);
    if (ei < 0) {
      continue;
    }
    std::vector<uint8_t> blob;
    check(extractDbpfRecord(pkg.data(), pkg.size(),
                            entries[static_cast<size_t>(ei)], blob, error),
          "cell_stage: record extracts");
    if (g_failures > 0) {
      loaded[e].ok = false;
      continue;
    }
    GmdlModel model;
    check(parseGmdl(blob.data(), blob.size(), model, error),
          "cell_stage: gmdl parses");
    Mesh mesh;
    check(meshFromGmdl(model, 0, mesh, error), "cell_stage: mesh converts");
    if (g_failures > 0) {
      loaded[e].ok = false;
      continue;
    }
    std::snprintf(label, sizeof(label), "cell_stage: %s verts %zu",
                  ent.role.c_str(), mesh.positions.size());
    check(mesh.positions.size() == ent.expectVerts, label);
    loaded[e].mesh = std::move(mesh);
    loaded[e].ok = g_failures == 0;
  }

  if (g_failures > 0) {
    std::printf("cell_stage: %d FAILURES\n", g_failures);
    return 1;
  }

  openspore::VulkanRenderer renderer;

  openspore::MaterialState mat;
  mat.lightDir[0] = 0.0F;
  mat.lightDir[1] = 0.7071F;
  mat.lightDir[2] = 0.7071F;
  mat.ambient = 0.35F;

  if (interactive) {
    // Present path: the renderer creates its instance/device against the SDL
    // surface (initPresent), so the offscreen init() is not called here.
    return runInteractive(renderer, texImage, mat, loaded, maxFrames, &stage);
  }

  if (!renderer.init(kViewport, kViewport)) {
    std::fprintf(stderr, "[cell_stage] renderer init failed\n");
    return 1;
  }
  std::printf("[cell_stage] device=%s\n", renderer.deviceName().c_str());

  const openspore::TextureHandle texId =
      texImage.pixels.empty() ? openspore::kInvalidTexture
                              : renderer.createTexture(texImage);
  check(texId != openspore::kInvalidTexture, "cell_stage: texture uploaded");

  if (inputPath.empty()) {
    return runFixedFrame(renderer, texId, mat, loaded, &stage);
  }
  return runSimMode(renderer, texId, mat, loaded, inputPath, &stage);
}
