// Clean-room OpenSpore renderer abstraction.
// Semantic descendant of the original Graphics::IRenderer concept
// (init/shutdown, render targets, active draw state) re-expressed as a
// minimal modern interface. No EA code, no decompiler output.
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace openspore {

// Interleaved position + vertex color. Enough for the first vertical slice;
// richer vertex descriptions arrive with the material system (explicit
// non-goal).
struct Vertex {
  float pos[3];
  float color[3];
};

using MeshHandle = uint32_t;
constexpr MeshHandle kInvalidMesh = 0xFFFFFFFFu;

// Host-side RGBA8 image, row-major, top-left origin.
struct ImageRGBA {
  uint32_t width = 0;
  uint32_t height = 0;
  std::vector<uint8_t> pixels; // size == width * height * 4
};

// Minimal backend contract: lifecycle, one mesh type, one draw call,
// offscreen readback. Swapchain presentation plugs in later as a separate
// presentable backend (see docs/RENDERER-DESIGN.md).
class IRenderer {
public:
  virtual ~IRenderer() = default;

  // Creates device-side state for an offscreen target of width x height.
  virtual bool init(uint32_t width, uint32_t height) = 0;
  virtual void shutdown() = 0;

  virtual MeshHandle createMesh(const Vertex *vertices, size_t vertexCount,
                                const uint32_t *indices, size_t indexCount) = 0;
  virtual void destroyMesh(MeshHandle mesh) = 0;

  // Clears to (r, g, b, a) and opens the single active pass.
  virtual void beginFrame(float r, float g, float b, float a) = 0;
  virtual void drawMesh(MeshHandle mesh) = 0;
  // Closes the pass, submits, and blocks until the GPU is idle.
  virtual void endFrame() = 0;

  // Copies the offscreen color target back to the host.
  virtual ImageRGBA readbackPixels() = 0;
};

} // namespace openspore
