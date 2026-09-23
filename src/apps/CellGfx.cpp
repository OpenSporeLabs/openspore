#include "CellGfx.hpp"

namespace openspore::cellgfx {

void CellGfx::initialize() {
  slots.clear();
  // Built in the original sCellGFX field order (Initialize @00e5dba0, offsets
  // 0x161a0..0x161d8): each world-bearing slot in address order, each with a
  // distinct non-zero clean-room token. The main-model world is the
  // kModelShadowLayer (0x1010020) slot, bound to the "CellGame-Main" layer.
  slots.push_back({static_cast<std::uint32_t>(WorldID::kBeachShadowLayer), 1});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kBeachEffectsWorld), 2});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kSkyboxEffectsWorld), 3});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kBackgroundEffectsWorld),
                   4});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kSkyboxShadowLayer), 5});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kEffectsWorld), 6});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kModelShadowLayer), 7});
  slots.push_back({static_cast<std::uint32_t>(WorldID::kForegroundEffectsWorld), 8});
  displayActive = false;
}

void CellGfx::preloadResources(
    std::vector<std::pair<std::uint32_t, std::uint32_t>> models,
    std::vector<std::pair<std::uint32_t, std::uint32_t>> populates) {
  preloadedModels = std::move(models);
  preloadedPopulates = std::move(populates);
}

void CellGfx::startDisplay() { displayActive = true; }

const CellGfx::WorldSlot *CellGfx::findWorld(WorldID id) const {
  const std::uint32_t want = static_cast<std::uint32_t>(id);
  for (const WorldSlot &s : slots) {
    if (s.worldId == want) {
      return &s;
    }
  }
  return nullptr;
}

const CellGfx::WorldSlot *CellGfx::modelWorld() const {
  return findWorld(WorldID::kModelShadowLayer);
}

} // namespace openspore::cellgfx
