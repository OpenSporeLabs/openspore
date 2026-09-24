#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Gmdl.hpp"
#include "ResourceKey.hpp"
#include "renderer/Renderer.hpp"

namespace openspore::assets {

struct MaterialSlot {
  uint32_t materialId = 0;
  std::vector<ResourceKey> textureSlots;
};

struct MaterialDefinition {
  uint32_t materialId = 0;
  MaterialState state;
  std::vector<ResourceKey> textureSlots;
};

struct ResolvedMaterialSlot {
  MaterialSlot slot;
  MaterialDefinition definition;
};

enum class MaterialResolveCode {
  ok,
  invalid_slot,
  unsupported_material,
};

struct MaterialResolveResult {
  MaterialResolveCode code = MaterialResolveCode::ok;
  std::vector<ResolvedMaterialSlot> materials;
  std::string error;

  explicit operator bool() const { return code == MaterialResolveCode::ok; }
};

class IMaterialRegistry {
 public:
  virtual ~IMaterialRegistry() = default;
  virtual MaterialResolveResult resolve(
      const std::vector<MaterialSlot>& slots) const = 0;
};

class MaterialRegistry final : public IMaterialRegistry {
 public:
  bool registerMaterial(const MaterialDefinition& definition);
  MaterialResolveResult resolve(
      const std::vector<MaterialSlot>& slots) const override;

 private:
  std::unordered_map<uint32_t, MaterialDefinition> definitions_;
};

std::vector<MaterialSlot> materialSlotsFromGmdl(const GmdlModel& model);

}  // namespace openspore::assets
