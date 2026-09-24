#include "InputRouter.hpp"

#include <cstdio>

#include "CellInput.hpp"
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
  void initialize() override {}
  void dispose() override {}
  void onEnter() override {}
  void onExit() override {}
  void onKeyDown(const openspore::gamemode::InputEvent& event) override {
    ++keyDown;
    last = event;
  }
  void onKeyUp(const openspore::gamemode::InputEvent& event) override {
    ++keyUp;
    last = event;
  }
  void onMouseMove(const openspore::gamemode::InputEvent& event) override {
    ++mouseMove;
    last = event;
  }
  void onMouseDown(const openspore::gamemode::InputEvent& event) override {
    ++mouseDown;
    last = event;
  }
  void onMouseUp(const openspore::gamemode::InputEvent& event) override {
    ++mouseUp;
    last = event;
  }
  void onMouseWheel(const openspore::gamemode::InputEvent& event) override {
    ++mouseWheel;
    last = event;
  }
  void update(float) override {}

  int keyDown = 0;
  int keyUp = 0;
  int mouseMove = 0;
  int mouseDown = 0;
  int mouseUp = 0;
  int mouseWheel = 0;
  openspore::gamemode::InputEvent last;
};

}  // namespace

int main() {
  using openspore::cellinput::CellInput;
  using openspore::cellinput::Key;
  using openspore::gamemode::GameModeManager;
  using openspore::gamemode::InputEvent;
  using openspore::gamemode::InputEventType;
  using openspore::input::InputRouter;
  using openspore::input::RouteResult;

  RecordingMode inactive;
  RecordingMode active;
  GameModeManager manager;
  manager.add(&inactive, "Inactive");
  manager.add(&active, "Active");
  InputRouter router;
  router.setRegistry(&manager);

  check(router.activeMode() == &inactive,
        "router follows the registry active index");
  check(router.route(InputEvent()) == RouteResult::kRouted,
        "input routes to the initial active mode");
  check(inactive.keyDown == 1 && active.keyDown == 0,
        "only the active mode receives input");

  check(manager.activate(1), "router test switches the active mode");
  check(router.route(InputEvent()) == RouteResult::kRouted,
        "input routes after activation");
  check(active.keyDown == 1 && inactive.keyDown == 1,
        "new active mode receives later input");

  CellInput input;
  check(router.route(input.keyDown(Key::kW)) == RouteResult::kRouted,
        "typed key down is routed");
  check(router.route(input.keyUp(Key::kW)) == RouteResult::kRouted,
        "typed key up is routed");
  check(router.route(input.mouseMove(1.0F, 2.0F)) == RouteResult::kRouted,
        "typed mouse move is routed");
  check(router.route(input.mouseDown(
            1.0F, 2.0F, openspore::gamemode::MouseButton::kLeft)) ==
            RouteResult::kRouted,
        "typed mouse down is routed");
  check(router.route(input.mouseUp(1.0F, 2.0F,
                                   openspore::gamemode::MouseButton::kLeft)) ==
            RouteResult::kRouted,
        "typed mouse up is routed");
  check(
      router.route(input.mouseWheel(1.0F, 2.0F, 1.0F)) == RouteResult::kRouted,
      "typed mouse wheel is routed");
  check(active.keyDown == 2 && active.keyUp == 1 && active.mouseMove == 1 &&
            active.mouseDown == 1 && active.mouseUp == 1 &&
            active.mouseWheel == 1,
        "all normalized callbacks reach the active mode");
  check(inactive.keyUp == 0 && inactive.mouseMove == 0 &&
            inactive.mouseDown == 0 && inactive.mouseUp == 0 &&
            inactive.mouseWheel == 0,
        "inactive mode receives no later callbacks");

  InputEvent unsupported;
  unsupported.type = static_cast<InputEventType>(255);
  check(router.route(unsupported) == RouteResult::kUnsupportedEvent,
        "unknown event type is rejected explicitly");
  router.clear();
  check(router.route(InputEvent()) == RouteResult::kNoActiveMode,
        "missing active mode is rejected explicitly");
  check(router.route(unsupported) == RouteResult::kUnsupportedEvent,
        "unsupported input is rejected without an active mode");
  router.setActiveMode(&active);
  check(router.route(InputEvent()) == RouteResult::kRouted,
        "direct active mode routes without a registry");
  check(active.keyDown == 3, "direct mode receives routed input");

  std::printf("input_router_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
