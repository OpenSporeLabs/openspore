#include <cstdio>
#include <string>
#include <vector>

#include "CellModeStrategy.hpp"

namespace {

int g_failures = 0;

void check(bool condition, const char* label) {
  std::printf("%s: %s\n", condition ? "ok" : "FAIL", label);
  if (!condition) {
    ++g_failures;
  }
}

struct RecordingMode final : openspore::gamemode::IGameMode {
  explicit RecordingMode(std::vector<std::string>* events, std::string id)
      : events(events), id(std::move(id)) {}

  void initialize() override { events->push_back(id + ":initialize"); }
  void dispose() override { events->push_back(id + ":dispose"); }
  void onEnter() override { events->push_back(id + ":enter"); }
  void onExit() override { events->push_back(id + ":exit"); }
  void onKeyDown(const openspore::gamemode::InputEvent&) override {}
  void onMouseMove(const openspore::gamemode::InputEvent&) override {}
  void onMouseDown(const openspore::gamemode::InputEvent&) override {}
  void onMouseUp(const openspore::gamemode::InputEvent&) override {}
  void onMouseWheel(const openspore::gamemode::InputEvent&) override {}
  void update(float) override { events->push_back(id + ":update"); }

  std::vector<std::string>* events;
  std::string id;
};

}  // namespace

int main() {
  using openspore::gamemode::CellModeStrategy;
  using openspore::gamemode::GameModeManager;
  using openspore::gamemode::InputEvent;
  using openspore::gamemode::InputEventType;
  using openspore::gamemode::InputKey;

  CellModeStrategy strategy;
  check(!strategy.mInitialized && !strategy.mEntered,
        "cell strategy starts outside both lifecycle states");
  strategy.initialize();
  check(strategy.mInitialized && !strategy.mEntered,
        "initialize does not enter the mode");
  strategy.update(1.0F);
  check(strategy.mFrame == 0, "update is inert before enter");
  strategy.onEnter();
  check(strategy.mEntered, "enter activates the mode");
  strategy.update(1.0F);
  strategy.update(1.0F);
  check(strategy.mFrame == 2, "entered update advances once per call");
  InputEvent event;
  event.type = InputEventType::kKeyDown;
  event.key = InputKey::kW;
  event.virtualKey = static_cast<std::uint32_t>(InputKey::kW);
  strategy.onKeyDown(event);
  check(strategy.mGotKey && strategy.mLastInput.key == InputKey::kW,
        "key down records normalized input");
  strategy.onKeyUp(event);
  check(strategy.mGotInput &&
            strategy.mLastInput.type == InputEventType::kKeyDown,
        "last input is observable after callbacks");
  strategy.onExit();
  check(!strategy.mEntered && !strategy.mGfx.displayActive,
        "exit deactivates the mode and its display");
  strategy.dispose();
  check(!strategy.mInitialized && !strategy.mEntered && strategy.mFrame == 0,
        "dispose clears lifecycle and frame state");
  check(!strategy.mUI.loaded, "dispose releases the owned UI state");

  std::vector<std::string> events;
  RecordingMode cell(&events, "cell");
  RecordingMode menu(&events, "menu");
  GameModeManager manager;
  check(manager.add(&cell, "Cell") == &cell, "registry accepts named mode");
  check(manager.add(&menu, "Menu") == &menu, "registry accepts second mode");
  check(manager.size() == 2 && manager.mActiveIndex == 0,
        "registry starts at active index zero");
  check(manager.active() == &cell, "active returns index zero mode");

  check(manager.activate(1), "activation accepts a valid index");
  check(manager.mActiveIndex == 1 && manager.active() == &menu,
        "activation commits the new active index");
  check(events.size() == 2 && events[0] == "cell:exit" &&
            events[1] == "menu:enter",
        "different-mode activation orders old exit before new enter");

  events.clear();
  check(manager.activate(1), "same-index activation succeeds");
  check(events.empty(), "same-index activation is a no-op");
  check(manager.activateByName("mEnU"), "name activation is case-insensitive");
  check(events.empty(), "same-mode name activation is a no-op");

  check(manager.activateByName("Cell"), "name activation selects another mode");
  check(manager.mActiveIndex == 0 && events.size() == 2 &&
            events[0] == "menu:exit" && events[1] == "cell:enter",
        "name activation preserves transition ordering");
  events.clear();
  check(!manager.activate(7), "out-of-range activation fails");
  check(manager.mActiveIndex == 0 && events.empty(),
        "failed activation preserves active index and lifecycle");
  check(!manager.activateByName("missing"), "unknown name activation fails");

  manager.update(0.25F);
  check(events.size() == 1 && events[0] == "cell:update",
        "manager updates only the active mode");
  events.clear();
  cell.initialize();
  menu.initialize();
  check(manager.registerMode(&cell, "cell") == false,
        "registry rejects duplicate case-insensitive names");
  check(manager.registerMode(nullptr, "null") == false,
        "registry rejects a null mode");

  events.clear();
  manager.dispose();
  check(manager.size() == 0 &&
            manager.mActiveIndex == openspore::gamemode::kNoActiveIndex,
        "manager dispose clears modes and active index");
  check(events.size() == 3 && events[0] == "cell:exit" &&
            events[1] == "cell:dispose" && events[2] == "menu:dispose",
        "manager disposes active mode before registered modes");

  std::printf("cellmode_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
