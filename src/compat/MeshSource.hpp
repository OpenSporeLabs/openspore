// Clean-room compatibility boundary B2: static mesh supply, plus the
// render-submit seam (B3) feeding it into the existing IRenderer.
//
// Semantic responsibility: parsed-model -> host Mesh -> renderer draw,
// without consumers knowing whether the model came from a package or a
// stub. Independently authored; IRenderer is referenced, not duplicated
// (see src/renderer/Renderer.hpp, docs/RENDERER-DESIGN.md).
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "assets/Gmdl.hpp"
#include "assets/Mesh.hpp"
#include "compat/ResourceProvider.hpp"
#include "renderer/Renderer.hpp"

namespace openspore::compat {

// Abstract mesh source. Producer: GmdlMeshSource. Consumer:
// submitMeshSource below (and any future scene loader).
class IMeshSource {
 public:
  virtual ~IMeshSource() = default;
  virtual bool loadMesh(uint32_t meshIndex, assets::Mesh &out,
                        std::string &error) = 0;
};

// GMDL-backed source: wraps one parsed model (version-8 static path only,
// per src/assets/Gmdl.*). Models arrive via fetchGmdlModel so the
// package-vs-stub choice stays behind IResourceProvider.
class GmdlMeshSource : public IMeshSource {
 public:
  explicit GmdlMeshSource(assets::GmdlModel model)
      : model_(std::move(model)) {}

  bool loadMesh(uint32_t meshIndex, assets::Mesh &out,
                std::string &error) override {
    return assets::meshFromGmdl(model_, meshIndex, out, error);
  }

 private:
  assets::GmdlModel model_;
};

// Seam function: (type, group, instance) -> parsed model through ANY
// resource provider. The same line serves DBPF packages and memory stubs.
inline bool fetchGmdlModel(IResourceProvider &provider, uint32_t type,
                           uint32_t group, uint32_t instance,
                           assets::GmdlModel &model, std::string &error) {
  std::vector<uint8_t> bytes;
  if (!provider.fetch(type, group, instance, bytes, error)) {
    return false;
  }
  return assets::parseGmdl(bytes.data(), bytes.size(), model, error);
}

// Render-submit seam (boundary B3): one mesh from any source into any
// IRenderer backend. Uploads, draws, and releases a transient handle.
inline bool submitMeshSource(IRenderer &renderer, IMeshSource &source,
                             uint32_t meshIndex, std::string &error) {
  assets::Mesh mesh;
  if (!source.loadMesh(meshIndex, mesh, error)) {
    return false;
  }
  const assets::RendererMesh rm = assets::toRendererMesh(mesh);
  const MeshHandle handle = renderer.createMesh(
      rm.vertices.data(), rm.vertices.size(), rm.indices.data(),
      rm.indices.size());
  if (handle == kInvalidMesh) {
    error = "compat: renderer refused mesh";
    return false;
  }
  renderer.drawMesh(handle);
  renderer.destroyMesh(handle);
  return true;
}

static_assert(std::is_base_of<IMeshSource, GmdlMeshSource>::value,
              "GMDL source must satisfy the mesh seam");

}  // namespace openspore::compat
