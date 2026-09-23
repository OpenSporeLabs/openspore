// cCellUI HUD (CS-27, clean-room).
//
// The original Simulator::Cell::cCellUI::Load (00e54270) sets up a global
// sCellUI (2372 B, 38 fields): a "GlobalUICell-3" named element, layout
// constants (20.0f @ +0x80, 1.0f @ +0xbc), and HUD element structs.
// ShowHealthRollover (00e62340) is the health-rollover trigger: for a cell with
// a live GFX object it allocates a cCellUIRollover from the rollover pool
// (61914) with field_8 = initialHealth * (1/6) and mDisappearTime = 0.5f
// (the decompiler wrote *(+0x24) = 0x3f000000; 0x24 == offset 36 == mDisappearTime).
// This mirrors that: a CellUI state object + the rollover pool, driven by sim
// state, rendered as a minimal health-bar overlay.
#pragma once

#include <cstdint>
#include <vector>

namespace openspore::cellui {

// cCellUIRollover (rollover pool 61914), 56 B.
struct UIRollover {
  std::uint32_t mObjectPoolIndex = 0;  // 0
  std::uint32_t mCellIndex = 0;        // 4
  float field_8 = 0.0F;                // 8   initialHealth * (1/6)
  int field_C = 0;                     // 12
  float field_10 = 0.0F;               // 16
  float field_14 = 0.0F;               // 20
  float field_18 = 0.0F;               // 24
  float field_1C = 0.0F;               // 28
  float field_20 = 0.0F;               // 32
  float mDisappearTime = 0.0F;         // 36  set to 0.5f by ShowHealthRollover
  float field_28 = 0.0F;               // 40
  float field_2C = 0.0F;               // 44
  bool field_30 = false;               // 48
  std::uint32_t mpLayout = 0;          // 52  UI layout handle
};

struct CellUI {
  // Load (00e54270) constants.
  const char *globalUi = "GlobalUICell-3";
  float layoutA = 20.0F;  // 0x41a00000 @ +0x80
  float layoutB = 1.0F;   // 0x3f800000 @ +0xbc
  bool loaded = false;

  std::vector<UIRollover> rollovers;  // the rollover pool (61914)

  // Load: set the HUD constants + mark loaded. Idempotent.
  void load();

  // ShowHealthRollover (00e62340): when gfxObjectIndex is live, push a
  // rollover (field_8 = initialHealth * (1/6), mDisappearTime = 0.5f) and
  // return its pool index; otherwise -1 (no rollover, matching the original's
  // early-out when mGFXObjectIndex == 0).
  int showHealthRollover(std::uint32_t gfxObjectIndex,
                         std::uint32_t cellPoolIndex, int initialHealth);
};

} // namespace openspore::cellui
