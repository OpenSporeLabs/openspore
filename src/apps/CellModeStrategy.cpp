#include "CellModeStrategy.hpp"

#include <cctype>
#include <utility>

namespace openspore::gamemode {

void CellModeStrategy::initialize() {
  mUI.load();
  mGfx.initialize();
  mBgClear = BgClear();
  mFrame = 0;
  mGotKey = false;
  mGotInput = false;
  mLastKey = InputEvent();
  mLastInput = InputEvent();
  mInitialized = true;
  mEntered = false;
}

void CellModeStrategy::dispose() {
  mUI.rollovers.clear();
  mUI.loaded = false;
  mBgClear = BgClear();
  mGfx.displayActive = false;
  mGfx.slots.clear();
  mGfx.preloadedModels.clear();
  mGfx.preloadedPopulates.clear();
  mFrame = 0;
  mInitialized = false;
  mEntered = false;
  mGotKey = false;
  mGotInput = false;
  mLastKey = InputEvent();
  mLastInput = InputEvent();
}

void CellModeStrategy::onEnter() {
  if (!mInitialized) {
    return;
  }
  mGfx.startDisplay();
  mEntered = true;
}

void CellModeStrategy::onExit() {
  mBgClear = BgClear();
  mGfx.displayActive = false;
  mEntered = false;
}

void CellModeStrategy::onKeyDown(const InputEvent& event) {
  mLastKey = event;
  mLastInput = event;
  mGotKey = true;
  mGotInput = true;
}

void CellModeStrategy::onKeyUp(const InputEvent& event) {
  mLastInput = event;
  mGotInput = true;
}

void CellModeStrategy::onMouseMove(const InputEvent& event) {
  mLastInput = event;
  mGotInput = true;
}

void CellModeStrategy::onMouseDown(const InputEvent& event) {
  mLastInput = event;
  mGotInput = true;
}

void CellModeStrategy::onMouseUp(const InputEvent& event) {
  mLastInput = event;
  mGotInput = true;
}

void CellModeStrategy::onMouseWheel(const InputEvent& event) {
  mLastInput = event;
  mGotInput = true;
}

void CellModeStrategy::update(float delta) {
  if (mEntered) {
    ++mFrame;
  }
  (void)delta;
}

IGameMode* GameModeManager::add(IGameMode* mode, std::string name) {
  if (mode == nullptr) {
    return nullptr;
  }
  if (!name.empty()) {
    for (const Entry& entry : mEntries) {
      if (entry.name.size() != name.size()) {
        continue;
      }
      bool equal = true;
      for (std::size_t i = 0; i < name.size(); ++i) {
        const auto left = static_cast<unsigned char>(entry.name[i]);
        const auto right = static_cast<unsigned char>(name[i]);
        if (std::tolower(left) != std::tolower(right)) {
          equal = false;
          break;
        }
      }
      if (equal) {
        return nullptr;
      }
    }
  }
  mEntries.push_back(Entry{mode, std::move(name)});
  return mode;
}

bool GameModeManager::registerMode(IGameMode* mode, std::string name) {
  return add(mode, std::move(name)) != nullptr;
}

IGameMode* GameModeManager::active() const {
  if (mEntries.empty() || mActiveIndex >= mEntries.size()) {
    return nullptr;
  }
  return mEntries[mActiveIndex].mode;
}

std::size_t GameModeManager::size() const { return mEntries.size(); }

bool GameModeManager::activate(std::uint32_t index) {
  if (index >= mEntries.size() || mEntries[index].mode == nullptr) {
    return false;
  }
  if (index == mActiveIndex) {
    return true;
  }

  IGameMode* oldMode = active();
  IGameMode* nextMode = mEntries[index].mode;
  if (oldMode != nullptr) {
    oldMode->onExit();
  }
  mActiveIndex = index;
  nextMode->onEnter();
  return true;
}

bool GameModeManager::activateByName(std::string_view name) {
  if (name.empty()) {
    return false;
  }
  for (std::size_t i = 0; i < mEntries.size(); ++i) {
    if (mEntries[i].name.size() != name.size()) {
      continue;
    }
    bool equal = true;
    for (std::size_t j = 0; j < name.size(); ++j) {
      const auto left = static_cast<unsigned char>(mEntries[i].name[j]);
      const auto right = static_cast<unsigned char>(name[j]);
      if (std::tolower(left) != std::tolower(right)) {
        equal = false;
        break;
      }
    }
    if (equal) {
      return activate(static_cast<std::uint32_t>(i));
    }
  }
  return false;
}

bool GameModeManager::activate_by_name(std::string_view name) {
  return activateByName(name);
}

bool GameModeManager::setActiveModeAt(std::uint32_t index) {
  return activate(index);
}

void GameModeManager::dispose() {
  IGameMode* oldMode = active();
  if (oldMode != nullptr) {
    oldMode->onExit();
  }
  for (const Entry& entry : mEntries) {
    if (entry.mode != nullptr) {
      entry.mode->dispose();
    }
  }
  mEntries.clear();
  mActiveIndex = kNoActiveIndex;
}

void GameModeManager::update(float delta) {
  IGameMode* mode = active();
  if (mode != nullptr) {
    mode->update(delta);
  }
}

}  // namespace openspore::gamemode
