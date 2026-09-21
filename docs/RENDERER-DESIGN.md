# Renderer Design (vertical slice 0)

## What this is
First OpenSpore rendering code: an offscreen Vulkan triangle. It preserves the
semantic concepts identified in `docs/RENDERWARE-RESEARCH.md` §5–6
(`Graphics::IRenderer` lifecycle, main color + depth render targets, active
draw state, mesh = vertex/index buffers + counts) while replacing every D3D9
accident with a modern equivalent. All code is clean-room C++17.

## Backend abstraction
- `src/renderer/Renderer.hpp` — `openspore::IRenderer`: `init(w,h)` /
  `shutdown`, `createMesh` / `destroyMesh`, `beginFrame(clear)` /
  `drawMesh` / `endFrame`, `readbackPixels`. Value types: `Vertex`
  (pos + color), `MeshHandle`, `ImageRGBA` (host RGBA8).
- `src/renderer/VulkanRenderer.{hpp,cpp}` — the only backend. Owns instance,
  device, queue, command pool, offscreen targets, render pass, pipeline,
  fence. No backend factory yet: one backend, constructed directly.

## Frame lifecycle
1. `beginFrame`: wait + reset fence, reset + begin command buffer (one-time
   submit), begin render pass (clear color + depth 1.0).
2. `drawMesh` (×N): bind pipeline, bind vertex/index buffers, `vkCmdDrawIndexed`.
   Mirrors the original per-mesh stream rebind, minus the shader-state cache.
3. `endFrame`: end pass → barrier → copy color image to a linear host-visible
   image → barrier → submit → fence-wait (GPU idle on return).
4. `readbackPixels`: map the linear image (respect `rowPitch`), return RGBA8.

## Resource model
- Buffers: host-visible + coherent vertex/index buffers per mesh (simplest
  correct upload; staging comes with large-asset loading).
- Images: optimal-tiling device-local color (`R8G8B8A8_UNORM`,
  `COLOR_ATTACHMENT | TRANSFER_SRC`) + depth (first supported of
  `D32_SFLOAT` / `D24_UNORM_S8_UINT` / `D16_UNORM`) + linear host-visible
  readback image (`TRANSFER_DST`).
- Shaders: checked-in GLSL (`src/renderer/shaders/triangle.{vert,frag}`,
  trivial passthrough, ours) compiled **at build time** by
  `glslangValidator` (REQUIRED — configure fails without it; no fallback, no
  runtime compiler dependency) and embedded as C arrays (`shaders_spv.h`).
- Device choice: highest score wins (discrete > integrated > virtual > other),
  candidates + selection logged to stderr.

## Smoke test
The app verifies its own pixels and exits non-zero on failure:
`cmake -S . -B build && cmake --build build -j && ctest --test-dir build -R triangle_smoke -V`
(`src/apps/triangle.cpp` renders 256×256, writes `triangle.ppm`, asserts the
center pixel is inside-triangle color and a corner pixel is background black).

## OUT of scope (explicit non-goals)
- Material system / `MaterialShader` cache, lighting, textures, fog.
- Window / swapchain / presentation. Plug-in point: a future
  `PresentableRenderer` (surface + swapchain images as the render-pass
  attachments, `vkQueuePresentKHR` after `endFrame`); `IRenderer` gains a
  `present()`-style method only when that lands.
- Staging uploads, multi-pass, MSAA, animation, any RenderWare emulation.

## Mapping to the original (for later phases)
| Original concept | This slice | Later |
|---|---|---|
| `Graphics::IRenderer` init/resize/state | `IRenderer::init/shutdown` | resize, fullscreen |
| Main color + depth RT | offscreen color + depth images | swapchain views |
| `ActiveState` on-change rebind | bind-per-draw (no cache yet) | state cache |
| `RenderWare::Mesh::Render` draw path | `vkCmdDrawIndexed` | per-material bindings |
| Pre-compiled shaders in packages | build-time SPIR-V embed | SPIR-V material shaders |
