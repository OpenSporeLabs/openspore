// CS-28: cCellModeStrategy lifecycle + cGameModeManager mode switching.
//
// Verifies the clean-room strategy mirrors the original slot semantics:
//   - Initialize builds the world table + loads the UI, sets the initialized
//     flag, and does NOT start the display.
//   - OnEnter starts the display and enables the mode.
//   - Update ticks one frame per call.
//   - OnKeyDown routes the key event.
//   - OnExit resets the background-map clear globals + disables the mode.
//   - Dispose frees the rollover pool, destroys the world, stops the display,
//     resets the globals, and clears both lifecycle flags.
//   - The manager's setActiveModeAt OnExits the old mode, OnEnters the new one,
//     and rejects out-of-range indices.
#include "CellModeStrategy.hpp"

#include <cstdio>

namespace {
int g_failures = 0;
void check(bool cond, const char *label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}
} // namespace

using openspore::gamemode::CellModeStrategy;
using openspore::gamemode::GameModeManager;
using openspore::gamemode::kDefaultBgClearR;

int main() {
  CellModeStrategy s;

  // Initial state.
  check(!s.mInitialized, "cellmode: starts uninitialized");
  check(!s.mEntered, "cellmode: starts not-entered");

  // Initialize (slot 6): world table + UI, flag set, display still off.
  s.initialize();
  check(s.mInitialized, "cellmode: initialize() sets initialized");
  check(!s.mGfx.slots.empty(), "cellmode: initialize() builds world table");
  check(s.mUI.loaded, "cellmode: initialize() loads UI");
  check(!s.mGfx.displayActive, "cellmode: initialize() leaves display off");

  // OnEnter (slot 8): start display + enable.
  s.onEnter();
  check(s.mEntered, "cellmode: onEnter() enables mode");
  check(s.mGfx.displayActive, "cellmode: onEnter() starts display");

  // Update (slot 17): one tick per call.
  s.update(1.0f / 60.0f);
  s.update(1.0f / 60.0f);
  check(s.mFrame == 2, "cellmode: update() ticks per frame");

  // OnKeyDown (slot 11): routes the event.
  s.onKeyDown({0x2A, 0, 0, 0});  // VK_LEFT
  check(s.mGotKey && s.mLastKey.virtualKey == 0x2A,
        "cellmode: onKeyDown routes the key");

  // OnExit (slot 9): reset bg globals + disable.
  s.mBgClear.r = 1.0f;  // perturb
  s.onExit();
  check(!s.mEntered, "cellmode: onExit() disables mode");
  check(s.mBgClear.r == kDefaultBgClearR,
        "cellmode: onExit() resets bg clear globals");

  // Dispose (slot 7): free pool, destroy world, stop display, clear flags.
  s.initialize();
  s.onEnter();
  s.mUI.showHealthRollover(1, 0, 120);
  check(!s.mUI.rollovers.empty(), "cellmode: pool populated before dispose");
  s.dispose();
  check(!s.mInitialized, "cellmode: dispose() clears initialized");
  check(!s.mEntered, "cellmode: dispose() clears entered");
  check(s.mUI.rollovers.empty(), "cellmode: dispose() frees pool");
  check(s.mGfx.slots.empty(), "cellmode: dispose() destroys world");
  check(!s.mGfx.displayActive, "cellmode: dispose() stops display");
  check(s.mBgClear.r == kDefaultBgClearR,
        "cellmode: dispose() resets bg clear globals");

  // --- cGameModeManager switching ---
  GameModeManager mgr;
  CellModeStrategy a, b;
  mgr.add(&a);
  mgr.add(&b);
  check(mgr.size() == 2, "manager: two modes registered");
  check(mgr.mActiveIndex == 0, "manager: index 0 active by default");

  // Switch 0 -> 1: OnExit a, OnEnter b.
  a.initialize();
  a.onEnter();
  check(mgr.setActiveModeAt(1), "manager: switch to index 1 ok");
  check(mgr.mActiveIndex == 1, "manager: active index is 1");
  check(!a.mEntered, "manager: old mode OnExit'd");
  check(b.mEntered, "manager: new mode OnEnter'd");
  check(b.mGfx.displayActive, "manager: new mode display started");

  // Out-of-range rejected.
  check(!mgr.setActiveModeAt(7), "manager: out-of-range index rejected");

  std::printf("cellmode_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
