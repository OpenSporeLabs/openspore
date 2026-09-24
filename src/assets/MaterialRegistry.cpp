#include "MaterialRegistry.hpp"

#include <utility>

namespace openspore::assets {

namespace {

bool completeKeys(const std::vector<ResourceKey>& keys) {
  for (const ResourceKey& key : keys) {
    if (!key.isComplete()) {
      return false;
    }
  }
  return true;
}

}  // namespace

bool MaterialRegistry::registerMaterial(const MaterialDefinition& definition) {
  if (!completeKeys(definition.textureSlots)) {
    return false;
  }
  return definitions_.emplace(definition.materialId, definition).second;
}

MaterialResolveResult MaterialRegistry::resolve(
    const std::vector<MaterialSlot>& slots) const {
  MaterialResolveResult result;
  result.materials.reserve(slots.size());
  for (const MaterialSlot& slot : slots) {
    if (!completeKeys(slot.textureSlots)) {
      return {MaterialResolveCode::invalid_slot,
              {},
              "material: slot contains an incomplete texture key"};
    }
    const auto found = definitions_.find(slot.materialId);
    if (found == definitions_.end()) {
      return {MaterialResolveCode::unsupported_material,
              {},
              "material: material id is not registered"};
    }
    if (!completeKeys(found->second.textureSlots)) {
      return {MaterialResolveCode::unsupported_material,
              {},
              "material: registered definition is incomplete"};
    }
    result.materials.push_back({slot, found->second});
  }
  return result;
}

std::vector<MaterialSlot> materialSlotsFromGmdl(const GmdlModel& model) {
  std::vector<MaterialSlot> slots;
  slots.reserve(model.materialIds.size());
  for (uint32_t materialId : model.materialIds) {
    slots.push_back({materialId, {}});
  }
  return slots;
}

}  // namespace openspore::assets
