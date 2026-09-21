// Offscreen triangle smoke app: renders one colored triangle (256x256),
// writes triangle.ppm to the working directory, and verifies pixels
// programmatically (center = inside-triangle color, corner = background).
// Exit code 0 on PASS, 1 on FAIL. Clean-room code.
#include <array>
#include <cstdio>
#include <vector>

#include "renderer/VulkanRenderer.hpp"

namespace {

void writePpm(const char *path, const openspore::ImageRGBA &img) {
  std::FILE *f = std::fopen(path, "wb");
  if (f == nullptr) {
    std::fprintf(stderr, "[triangle] cannot open %s for writing\n", path);
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

std::array<uint8_t, 4> pixelAt(const openspore::ImageRGBA &img, uint32_t x,
                               uint32_t y) {
  const size_t i = (static_cast<size_t>(y) * img.width + x) * 4;
  return {img.pixels[i], img.pixels[i + 1], img.pixels[i + 2],
          img.pixels[i + 3]};
}

} // namespace

int main() {
  constexpr uint32_t kSize = 256;
  openspore::VulkanRenderer renderer;
  if (!renderer.init(kSize, kSize)) {
    std::fprintf(stderr, "[triangle] renderer init failed\n");
    return 1;
  }

  // Symmetric triangle around NDC origin: center pixel is inside regardless
  // of Y-flip conventions; corners stay background.
  const openspore::Vertex verts[3] = {
      {{0.0F, -0.5F, 0.0F}, {1.0F, 0.0F, 0.0F}}, // top, red
      {{0.5F, 0.5F, 0.0F}, {0.0F, 1.0F, 0.0F}},  // bottom-right, green
      {{-0.5F, 0.5F, 0.0F}, {0.0F, 0.0F, 1.0F}}, // bottom-left, blue
  };
  const uint32_t indices[3] = {0, 1, 2};
  const openspore::MeshHandle mesh = renderer.createMesh(verts, 3, indices, 3);
  if (mesh == openspore::kInvalidMesh) {
    std::fprintf(stderr, "[triangle] createMesh failed\n");
    return 1;
  }

  renderer.beginFrame(0.0F, 0.0F, 0.0F, 1.0F);
  renderer.drawMesh(mesh);
  renderer.endFrame();

  const openspore::ImageRGBA img = renderer.readbackPixels();
  writePpm("triangle.ppm", img);

  // Expected center color: barycentric mix at NDC (0,0) is
  // 0.5*red + 0.25*green + 0.25*blue = (127, 63, 63). Allow raster slack.
  const auto center = pixelAt(img, kSize / 2, kSize / 2);
  const auto corner = pixelAt(img, 8, 8);
  std::printf("[triangle] device=%s\n", renderer.deviceName().c_str());
  std::printf("[triangle] center=(%u,%u,%u,%u) corner=(%u,%u,%u,%u)\n",
              center[0], center[1], center[2], center[3], corner[0], corner[1],
              corner[2], corner[3]);

  const bool centerOk = center[0] > 80 && center[1] > 30 && center[2] > 30;
  const bool cornerOk = corner[0] < 16 && corner[1] < 16 && corner[2] < 16;
  const bool pass = centerOk && cornerOk;
  std::printf("[triangle] %s (center %s, corner %s)\n", pass ? "PASS" : "FAIL",
              centerOk ? "ok" : "BAD", cornerOk ? "ok" : "BAD");
  renderer.destroyMesh(mesh);
  renderer.shutdown();
  return pass ? 0 : 1;
}
