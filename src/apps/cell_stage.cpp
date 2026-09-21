// Obj16: renders the minimal OpenSpore Cell Stage scene offscreen and
// prints a deterministic scene manifest. Composition (see docs/CELLSTAGE.md):
//   - backdrop: the two heightfield patches (gmdl 0x40666202/0x40666203,
//     inst 0xd1b4bb56, rec 15/16) textured with their real DXT5 raster
//     0x40662900/0xd1b4bb56 through the Obj15 lit path.
//   - player cell: one clean rounded gmdl stand-in at the origin.
//   - 2 food + 1 prey object at hard-coded positions.
// Evidence labels: asset identity CONFIRMED (bytes parsed); the player-cell
// identity and every scene position are APPROXIMATIONS (no scene/world-object
// records are decoded yet — recon section 4). The clear color (soup water
// teal) and camera angles are APPROXIMATIONS.
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

// Soup-water clear color — APPROXIMATION (no cell background record decoded).
constexpr float kClearR = 0.10F;
constexpr float kClearG = 0.35F;
constexpr float kClearB = 0.42F;

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

// Scene entities. group/inst are CONFIRMED (parsed from the package); every
// pos is a hard-coded APPROXIMATION (world-obj records 0x0f43029a not decoded).
struct Entity {
  const char *role;
  uint32_t group;
  uint32_t inst;
  float pos[3];
  float targetSpan; // bbox max span scaled to this size, centered, then pos
  size_t expectVerts;
  bool textured;
};

const Entity kEntities[] = {
    // Backdrop: heightfield patches (KG-confirmed terrain pieces, recon §2/§4).
    {"backdrop_a", 0x40666202, 0xD1B4BB56, {-8.0F, -6.0F, 2.0F}, 16.0F,
     1059, true},
    {"backdrop_b", 0x40666203, 0xD1B4BB56, {8.0F, -6.0F, 5.0F}, 16.0F,
     750, true},
    // Player cell stand-in — APPROXIMATION identity: most roundish bbox
    // (aspect 1.50) among the small clean gmdl set; distinct from the
    // 0x4066620x heightfield family.
    {"player_cell", 0x40637E02, 0x067A0801, {0.0F, 0.0F, 0.0F}, 4.0F,
     244, false},
    // Food / prey — APPROXIMATION positions; small clean gmdl records.
    {"food_a", 0x40637E03, 0x067CEDE8, {3.5F, -1.5F, 2.5F}, 2.0F, 79, false},
    {"food_b", 0x40637E03, 0x067CEDEA, {-4.5F, -2.0F, 3.5F}, 3.0F, 435,
     false},
    {"prey_c", 0x40637E03, 0x067CEDFB, {1.5F, -0.5F, -5.0F}, 2.5F, 248,
     false},
};
constexpr int kEntityCount = sizeof(kEntities) / sizeof(kEntities[0]);

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
                  const std::vector<Loaded> &loaded) {
  // Orbit camera -> view; perspective with [0,1] NDC depth; the product is
  // baked into every vertex (the renderer has no matrix uniforms).
  const Camera cam;
  const float eye[3] = {
      cam.target[0] + cam.dist * std::sin(cam.yaw) * std::cos(cam.pitch),
      cam.target[1] + cam.dist * std::sin(cam.pitch),
      cam.target[2] + cam.dist * std::cos(cam.yaw) * std::cos(cam.pitch)};
  const float up[3] = {0.0F, 1.0F, 0.0F};
  const Mat4 view = lookAt(eye, cam.target, up);
  const Mat4 proj = perspective(cam.fov, 1.0F, cam.near, cam.far);
  const Mat4 vp = mul(proj, view);

  std::vector<openspore::MeshHandle> flat(kEntityCount,
                                          openspore::kInvalidMesh);
  std::vector<openspore::MeshHandle> tex(kEntityCount,
                                         openspore::kInvalidMesh);
  for (int e = 0; e < kEntityCount; ++e) {
    const Entity &ent = kEntities[e];
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
  for (int e = 0; e < kEntityCount; ++e) {
    const Entity &ent = kEntities[e];
    if (ent.textured) {
      renderer.drawTextured(tex[e], texId, mat);
    } else {
      renderer.drawMesh(flat[e]);
    }
  }
  renderer.endFrame();
  const openspore::ImageRGBA img = renderer.readbackPixels();
  writePpm("cell_stage.ppm", img);

  const PixelStats st = stats(img);
  std::printf("[cell_stage] pixels total=%zu non_black=%zu distinct=%zu "
              "clearish=%zu\n",
              st.total, st.nonBlack, st.distinct, st.clearish);

  // Deterministic scene manifest (the python oracle compares two runs).
  std::printf("CELLSTAGE-MANIFEST v1\n");
  for (int e = 0; e < kEntityCount; ++e) {
    const Entity &ent = kEntities[e];
    std::printf("entity role=%s group=0x%08X inst=0x%08X verts=%zu tris=%zu "
                "pos=%.3f %.3f %.3f\n",
                ent.role, ent.group, ent.inst,
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

  for (int e = 0; e < kEntityCount; ++e) {
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
                kEntityCount, st.nonBlack);
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
  for (int e = 0; e < kEntityCount; ++e) {
    const Entity &ent = kEntities[e];
    float pos[3] = {ent.pos[0], ent.pos[1], ent.pos[2]};
    float rot = 0.0F;
    if (ent.textured) {
      // backdrop: static.
    } else if (std::strcmp(ent.role, "player_cell") == 0) {
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
               const std::string &inputPath) {
  openspore::sim::ScriptedInputSource source(inputPath);
  if (!source.ok()) {
    std::fprintf(stderr, "[cell_stage] %s\n", source.error().c_str());
    return 1;
  }

  std::vector<openspore::sim::Entity> ents;
  for (const Entity &e : kEntities) {
    if (std::strncmp(e.role, "backdrop_", 9) == 0) {
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

  std::vector<BakedMesh> baked(kEntityCount);
  for (int e = 0; e < kEntityCount; ++e) {
    baked[e] = bakeEntity(loaded[e], kEntities[e]);
  }

  const float kDeg = 3.14159265358979F / 180.0F;
  const Mat4 proj = perspective(60.0F * kDeg, 1.0F, 0.5F, 100.0F);
  const float up[3] = {0.0F, 1.0F, 0.0F};
  const int totalFrames = static_cast<int>(source.frameCount());

  for (int f = 0; f < totalFrames; ++f) {
    sim.update(source.frame(f));
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
      const Entity &ent = kEntities[d.entity];
      if (ent.textured) {
        renderer.drawTextured(d.tex, texId, mat);
      } else {
        renderer.drawMesh(d.flat);
      }
    }
    renderer.endFrame();

    for (const FrameDraw &d : draws) {
      if (kEntities[d.entity].textured) {
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
                   const std::vector<Loaded> &loaded, int maxFrames) {
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
  for (const Entity &e : kEntities) {
    if (std::strncmp(e.role, "backdrop_", 9) == 0) {
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

  std::vector<BakedMesh> baked(kEntityCount);
  for (int e = 0; e < kEntityCount; ++e) {
    baked[e] = bakeEntity(loaded[e], kEntities[e]);
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
    const bool *keys = SDL_GetKeyboardState(nullptr);
    openspore::sim::InputFrame input;
    if (keys[SDL_SCANCODE_W]) {
      input.thrustForward = true;
    }
    if (keys[SDL_SCANCODE_S]) {
      input.thrustBack = true;
    }
    if (keys[SDL_SCANCODE_A]) {
      input.thrustLeft = true;
    }
    if (keys[SDL_SCANCODE_D]) {
      input.thrustRight = true;
    }
    if (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT]) {
      input.boost = true;
    }

    bool camChanged = false;
    if (keys[SDL_SCANCODE_LEFT]) {
      camYaw += kYawStep;
      camChanged = true;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
      camYaw -= kYawStep;
      camChanged = true;
    }
    if (keys[SDL_SCANCODE_UP]) {
      camPitch = std::min(85.0F * kDeg, camPitch + kPitchStep);
      camChanged = true;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
      camPitch = std::max(-80.0F * kDeg, camPitch - kPitchStep);
      camChanged = true;
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
      if (kEntities[d.entity].textured) {
        renderer.destroyTexMesh(d.tex);
      } else {
        renderer.destroyMesh(d.flat);
      }
    }
    prevDraws.clear();

    std::vector<FrameDraw> draws;
    buildFrameDraws(renderer, baked, sim, vp, draws);
    for (const FrameDraw &d : draws) {
      const Entity &ent = kEntities[d.entity];
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
                "[--interactive] [--frames N]\n");
    return 1;
  }
  std::string inputPath;
  bool interactive = false;
  int maxFrames = 0;
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "--input" && i + 1 < argc) {
      inputPath = argv[i + 1];
      ++i;
    } else if (std::string(argv[i]) == "--interactive") {
      interactive = true;
    } else if (std::string(argv[i]) == "--frames" && i + 1 < argc) {
      maxFrames = std::atoi(argv[i + 1]);
      ++i;
    }
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

  // Load every scene entity.
  std::vector<Loaded> loaded(kEntityCount);
  for (int e = 0; e < kEntityCount; ++e) {
    const Entity &ent = kEntities[e];
    const int ei = findDbpfEntry(entries, kTypeGmdl, ent.group, ent.inst);
    char label[96];
    std::snprintf(label, sizeof(label), "cell_stage: %s record present",
                  ent.role);
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
    std::snprintf(label, sizeof(label), "cell_stage: %s verts %zu", ent.role,
                  mesh.positions.size());
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
    return runInteractive(renderer, texImage, mat, loaded, maxFrames);
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
    return runFixedFrame(renderer, texId, mat, loaded);
  }
  return runSimMode(renderer, texId, mat, loaded, inputPath);
}
