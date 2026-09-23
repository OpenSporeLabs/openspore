// cCellModeStrategy + cGameModeManager (CS-28, clean-room).
//
// The original cCellModeStrategy is a 12-byte struct behind the 27-slot vtable:
// +0x00 vtable ptr, +0x04 mbEnableLoadingCards, +0x09 field_09, +0x0A field_0A.
// It owns the cell-stage singletons (sCellGame / sCellGFX / sCellUI) — global
// pointers in the original, owned here for clean-room encapsulation.
//
//   Initialize (slot 6)  allocates the singletons, resets the flags, creates the
//                        world, and calls cCellGFX::Initialize.
//   OnEnter    (slot 8)  starts the display (cCellGFX::StartDisplay) + enables
//                        the mode.
//   OnExit     (slot 9)  resets the background-map color globals
//                        (DAT_01550adc <- DAT_016b3bf0) + disables the mode.
//   Update     (slot 17) drives the real per-frame tick (FUN_00e806b0).
//   Dispose    (slot 7)  frees the pool, resets the globals, disposes the GFX +
//                        world, and frees the singletons.
//
// cGameModeManager is a 52-byte struct (mnActiveIndex at +0x28 = 40) holding
// the registered modes; SetActiveModeAt(index) calls OnExit on the current mode
// then activates + OnEnter the new index.
#pragma once

#include "CellGfx.hpp"
#include "CellUI.hpp"
#include "IGameMode.hpp"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace openspore::gamemode {

// DAT_016b3bf0 — the background-map clear-color defaults OnExit/Dispose restore.
inline constexpr float kDefaultBgClearR = 0.0F;
inline constexpr float kDefaultBgClearG = 0.0F;
inline constexpr float kDefaultBgClearB = 0.0F;

// DAT_01550adc — the live background-map clear-color globals.
struct BgClear {
  float r = kDefaultBgClearR;
  float g = kDefaultBgClearG;
  float b = kDefaultBgClearB;
};

class CellModeStrategy : public IGameMode {
 public:
  // +0x04 mbEnableLoadingCards (the original's documented flag).
  bool mEnableLoadingCards = false;

  // +0x09 / +0x0A lifecycle flags (clean-room names for the documented fields).
  bool mInitialized = false;
  bool mEntered = false;

  BgClear mBgClear;  // the background-map clear globals (DAT_01550adc).

  // The owned cell-stage resources (original sCellGFX / sCellUI).
  openspore::cellgfx::CellGfx mGfx;
  openspore::cellui::CellUI mUI;

  // Per-frame tick counter (Update / FUN_00e806b0).
  std::uint64_t mFrame = 0;

  // Last routed key (OnKeyDown / slot 11) — for testability.
  InputEvent mLastKey;
  bool mGotKey = false;

  void initialize() override;
  void dispose() override;
  void onEnter() override;
  void onExit() override;
  void onKeyDown(const InputEvent &ev) override;
  void onMouseMove(const InputEvent &) override;
  void onMouseDown(const InputEvent &) override;
  void onMouseUp(const InputEvent &) override;
  void onMouseWheel(const InputEvent &) override;
  void update(float delta) override;
};

class GameModeManager {
 public:
  struct Entry {
    IGameMode *mode = nullptr;
  };

  std::uint32_t mActiveIndex = 0;  // +0x28

  IGameMode *add(IGameMode *mode);
  IGameMode *active() const;
  std::size_t size() const;

  // SetActiveModeAt: OnExit the current mode (if it differs), then activate +
  // OnEnter the new index. Returns false if the index is out of range.
  bool setActiveModeAt(std::uint32_t index);

 private:
  std::vector<Entry> mEntries;
};

} // namespace openspore::gamemode
