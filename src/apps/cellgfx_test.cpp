// CS-26: the cCellGFX preload path — world-handle table + preloaded records.
//
// Verifies the clean-room CellGfx mirrors the original structure:
//   - initialize() builds the world table with the five effect worlds (exact
//     WorldIDs from the Initialize decompilation) each on a distinct non-zero
//     token, the main-model world present (kCellModelWorldID 0x1010020), and the
//     two named layers.
//   - preloadResources() records the model + populate record keys.
//   - startDisplay() activates the display.
// A second initialize() is idempotent (same table, display reset).
#include "CellGfx.hpp"

#include <cstdio>
#include <set>
#include <string>

namespace {
int g_failures = 0;
void check(bool cond, const char *label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}
} // namespace

using openspore::cellgfx::CellGfx;
using openspore::cellgfx::WorldID;

int main() {
  CellGfx gfx;
  gfx.initialize();

  // Every effect world is present with its exact WorldID.
  check(gfx.findWorld(WorldID::kSkyboxEffectsWorld) != nullptr,
        "cellgfx: skybox world 0x1010000 present");
  check(gfx.findWorld(WorldID::kBackgroundEffectsWorld) != nullptr,
        "cellgfx: background world 0x1010011 present");
  check(gfx.findWorld(WorldID::kBeachEffectsWorld) != nullptr,
        "cellgfx: beach world 0x1010016 present");
  check(gfx.findWorld(WorldID::kEffectsWorld) != nullptr,
        "cellgfx: effects world 0x1010021 present");
  check(gfx.findWorld(WorldID::kForegroundEffectsWorld) != nullptr,
        "cellgfx: foreground world 0x1010031 present");

  // The main-model world is the kCellModelWorldID (shadow layer 0x1010020).
  const CellGfx::WorldSlot *model = gfx.modelWorld();
  check(model != nullptr, "cellgfx: main-model world (0x1010020) present");
  if (model) {
    check(model->worldId == 0x1010020u, "cellgfx: model world id == 0x1010020");
  }

  // Distinct non-zero handles across the whole table.
  std::set<std::uint32_t> handles;
  check(!gfx.slots.empty(), "cellgfx: world table non-empty");
  for (const CellGfx::WorldSlot &s : gfx.slots) {
    check(s.handle != 0, "cellgfx: world handle non-zero");
    handles.insert(s.handle);
  }
  check(handles.size() == gfx.slots.size(), "cellgfx: world handles distinct");

  // Named layers.
  check(std::string(gfx.layers.background) == "CellGame-Background",
        "cellgfx: background layer name");
  check(std::string(gfx.layers.main) == "CellGame-Main",
        "cellgfx: main layer name");

  // PreloadResources records the record keys in order.
  gfx.preloadResources({{0x40616201, 0x3624c460}}, {{0x44415934, 0x3624c460}});
  check(gfx.preloadedModels.size() == 1 &&
            gfx.preloadedModels[0] == std::make_pair(0x40616201u, 0x3624c460u),
        "cellgfx: preloaded model key recorded");
  check(gfx.preloadedPopulates.size() == 1 &&
            gfx.preloadedPopulates[0] == std::make_pair(0x44415934u, 0x3624c460u),
        "cellgfx: preloaded populate key recorded");

  // StartDisplay activates; a fresh initialize() resets it (idempotent table).
  check(!gfx.displayActive, "cellgfx: display starts inactive");
  gfx.startDisplay();
  check(gfx.displayActive, "cellgfx: startDisplay activates");
  const size_t before = gfx.slots.size();
  gfx.initialize();
  check(gfx.slots.size() == before, "cellgfx: initialize() idempotent");
  check(!gfx.displayActive, "cellgfx: initialize() resets display");

  std::printf("cellgfx_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
