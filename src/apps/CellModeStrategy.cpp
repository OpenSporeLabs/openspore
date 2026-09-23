#include "CellModeStrategy.hpp"

namespace openspore::gamemode {

// --- cCellModeStrategy (slot semantics from the decompilation) -------------

void CellModeStrategy::initialize() {
  // Initialize (slot 6): allocate + reset the singletons, create the world,
  // and call cCellGFX::Initialize. Idempotent (re-calling rebuilds state).
  mUI.load();
  mGfx.initialize();
  mBgClear = BgClear();
  mFrame = 0;
  mGotKey = false;
  mInitialized = true;
}

void CellModeStrategy::dispose() {
  // Dispose (slot 7): free the pool, reset the globals, dispose the GFX +
  // world, and clear the singletons.
  mUI.rollovers.clear();
  mBgClear = BgClear();
  mGfx.displayActive = false;
  mGfx.slots.clear();
  mGfx.preloadedModels.clear();
  mGfx.preloadedPopulates.clear();
  mFrame = 0;
  mInitialized = false;
  mEntered = false;
}

void CellModeStrategy::onEnter() {
  // OnEnter (slot 8): start the display + enable the mode.
  mGfx.startDisplay();
  mEntered = true;
}

void CellModeStrategy::onExit() {
  // OnExit (slot 9): reset the background-map color globals + disable the mode.
  mBgClear = BgClear();
  mEntered = false;
}

void CellModeStrategy::onKeyDown(const InputEvent &ev) {
  // OnKeyDown (slot 11): route the key. (The key->action mapping lands in CS-29;
  // here the strategy just records the last event so it is observable.)
  mLastKey = ev;
  mGotKey = true;
}

void CellModeStrategy::onMouseMove(const InputEvent &) {}
void CellModeStrategy::onMouseDown(const InputEvent &) {}
void CellModeStrategy::onMouseUp(const InputEvent &) {}
void CellModeStrategy::onMouseWheel(const InputEvent &) {}

void CellModeStrategy::update(float delta) {
  // Update (slot 17 / FUN_00e806b0): the per-frame tick.
  mFrame++;
  (void)delta;
}

// --- cGameModeManager -------------------------------------------------------

IGameMode *GameModeManager::add(IGameMode *mode) {
  mEntries.push_back(Entry{mode});
  return mode;
}

IGameMode *GameModeManager::active() const {
  if (mEntries.empty()) {
    return nullptr;
  }
  return mEntries[mActiveIndex % mEntries.size()].mode;
}

std::size_t GameModeManager::size() const {
  return mEntries.size();
}

bool GameModeManager::setActiveModeAt(std::uint32_t index) {
  if (mEntries.empty() || index >= mEntries.size()) {
    return false;
  }
  IGameMode *cur = active();
  IGameMode *nxt = mEntries[index].mode;
  if (cur != nullptr && cur != nxt) {
    cur->onExit();
  }
  mActiveIndex = index;
  nxt->onEnter();
  return true;
}

} // namespace openspore::gamemode
