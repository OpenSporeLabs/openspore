// cCellGFX preload path (CS-26, clean-room).
//
// The original Simulator::Cell::cCellGFX::Initialize (00e5dba0) builds a global
// sCellGFX object that owns the cell-stage render "worlds" — one RenderWare
// world each for the skybox, background, beach, main model, effects, and
// foreground, plus shadow-map layers and the named layers "CellGame-Background"
// and "CellGame-Main". PreloadResources (00e666f0) then registers the real cell
// + populate resource records, and StartDisplay (00e55120) activates the
// display. This mirrors that structure: a CellGfx state object holding the world
// handles in the original's order, the preloaded record keys, and a display flag.
// (No RenderWare here — each world is a clean-room integer token.)
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace openspore::cellgfx {

// WorldIDs (cCellGFX.h). Values lifted verbatim from the Initialize
// decompilation: the effect-world IDs passed to the world-creator, and the
// shadow-map-layer IDs (SetShadowMapLayer). kModelShadowLayer (0x1010020) is
// the kCellModelWorldID the campaign plan cites for the main model world.
enum class WorldID : std::uint32_t {
  kSkyboxEffectsWorld = 0x1010000,
  kSkyboxShadowLayer = 0x1010010,
  kBackgroundEffectsWorld = 0x1010011,
  kBeachShadowLayer = 0x1010015,
  kBeachEffectsWorld = 0x1010016,
  kModelShadowLayer = 0x1010020,
  kEffectsWorld = 0x1010021,
  kForegroundEffectsWorld = 0x1010031,
};

// The two named render layers Initialize binds to its worlds.
struct LayerName {
  const char *background = "CellGame-Background";
  const char *main = "CellGame-Main";
};

struct CellGfx {
  struct WorldSlot {
    std::uint32_t worldId = 0; // WorldID, or 0 for a non-world slot
    std::uint32_t handle = 0;  // clean-room render-world token
  };

  // The world-handle table, built by initialize() in the sCellGFX order
  // (offsets 0x161a0..0x161d8 in the original).
  std::vector<WorldSlot> slots;
  LayerName layers;
  bool displayActive = false;

  // Preloaded resource record keys (group, instance) — PreloadResources.
  std::vector<std::pair<std::uint32_t, std::uint32_t>> preloadedModels;
  std::vector<std::pair<std::uint32_t, std::uint32_t>> preloadedPopulates;

  // Initialize: build the world-handle table in the original's order. Each of
  // the five effect worlds gets a distinct non-zero token; the shadow layers and
  // named layers are recorded. Idempotent (re-calling rebuilds the same table).
  void initialize();

  // PreloadResources: register the real cell-model + populate record keys in
  // the original's order (cell resource first, then the populate resource).
  void preloadResources(std::vector<std::pair<std::uint32_t, std::uint32_t>> models,
                        std::vector<std::pair<std::uint32_t, std::uint32_t>> populates);

  // StartDisplay: activate the display.
  void startDisplay();

  // The slot holding the given WorldID, or nullptr.
  const WorldSlot *findWorld(WorldID id) const;

  // The main-model world slot (kModelShadowLayer's world) — where scene cells
  // render. nullptr until initialize().
  const WorldSlot *modelWorld() const;
};

} // namespace openspore::cellgfx
