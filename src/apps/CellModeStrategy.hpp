#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "CellGfx.hpp"
#include "CellUI.hpp"
#include "IGameMode.hpp"

namespace openspore::gamemode {

inline constexpr float kDefaultBgClearR = 0.0F;
inline constexpr float kDefaultBgClearG = 0.0F;
inline constexpr float kDefaultBgClearB = 0.0F;
inline constexpr std::uint32_t kNoActiveIndex = 0xFFFFFFFFu;

struct BgClear {
  float r = kDefaultBgClearR;
  float g = kDefaultBgClearG;
  float b = kDefaultBgClearB;
};

class CellModeStrategy : public IGameMode {
 public:
  bool mEnableLoadingCards = false;
  bool mInitialized = false;
  bool mEntered = false;
  BgClear mBgClear;
  openspore::cellgfx::CellGfx mGfx;
  openspore::cellui::CellUI mUI;
  std::uint64_t mFrame = 0;
  InputEvent mLastKey;
  InputEvent mLastInput;
  bool mGotKey = false;
  bool mGotInput = false;

  void initialize() override;
  void dispose() override;
  void onEnter() override;
  void onExit() override;
  void onKeyDown(const InputEvent& event) override;
  void onKeyUp(const InputEvent& event) override;
  void onMouseMove(const InputEvent& event) override;
  void onMouseDown(const InputEvent& event) override;
  void onMouseUp(const InputEvent& event) override;
  void onMouseWheel(const InputEvent& event) override;
  void update(float delta) override;
};

class GameModeManager final : public IGameModeRegistry {
 public:
  struct Entry {
    IGameMode* mode = nullptr;
    std::string name;
  };

  std::uint32_t mActiveIndex = 0;

  IGameMode* add(IGameMode* mode, std::string name = {});
  bool registerMode(IGameMode* mode, std::string name = {}) override;
  IGameMode* active() const override;
  std::size_t size() const;
  bool activate(std::uint32_t index) override;
  bool activateByName(std::string_view name) override;
  bool activate_by_name(std::string_view name) override;
  bool setActiveModeAt(std::uint32_t index);
  void dispose();
  void update(float delta);

 private:
  std::vector<Entry> mEntries;
};

}  // namespace openspore::gamemode
