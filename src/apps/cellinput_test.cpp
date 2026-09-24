#include "CellInput.hpp"

#include <cstdio>

namespace {

int g_failures = 0;

void check(bool condition, const char* label) {
  std::printf("%s: %s\n", condition ? "ok" : "FAIL", label);
  if (!condition) {
    ++g_failures;
  }
}

}  // namespace

int main() {
  using openspore::cellinput::Action;
  using openspore::cellinput::CellInput;
  using openspore::cellinput::Key;
  using openspore::cellinput::Table;
  using openspore::gamemode::InputEventType;
  using openspore::gamemode::MouseButton;

  check(*Table::lookup(Key::kW) == Action::kThrustForward, "table maps W");
  check(*Table::lookup(Key::kS) == Action::kThrustBack, "table maps S");
  check(*Table::lookup(Key::kA) == Action::kThrustLeft, "table maps A");
  check(*Table::lookup(Key::kD) == Action::kThrustRight, "table maps D");
  check(*Table::lookup(Key::kShift) == Action::kBoost, "table maps boost");
  check(*Table::lookup(Key::kEscape) == Action::kQuit, "table maps quit");
  check(*Table::lookup(Key::kLeft) == Action::kCamLeft,
        "table maps left camera");
  check(*Table::lookup(Key::kRight) == Action::kCamRight,
        "table maps right camera");
  check(*Table::lookup(Key::kUp) == Action::kCamUp, "table maps up camera");
  check(*Table::lookup(Key::kDown) == Action::kCamDown,
        "table maps down camera");
  check(*Table::lookup(Key::kToggleHealth) == Action::kToggleHealthDisplay,
        "table maps health toggle");
  check(Table::lookup(static_cast<Key>(999)) == nullptr,
        "unknown key is not mapped");

  CellInput input;
  input.press(Key::kW);
  input.press(Key::kShift);
  const auto frame = input.frame();
  check(frame.thrustForward && frame.boost && !frame.thrustBack &&
            !frame.thrustLeft && !frame.thrustRight,
        "held keys produce normalized movement input");
  input.clear();
  check(!input.frame().thrustForward && !input.frame().boost,
        "clear removes held state");

  input.press(Key::kA);
  input.press(Key::kD);
  check(input.frame().thrustLeft && input.frame().thrustRight,
        "opposite movement keys remain independently observable");
  input.clear();
  input.press(Key::kLeft);
  input.press(Key::kUp);
  const auto camera = input.camera();
  check(camera.left && camera.up && !camera.right && !camera.down,
        "camera directions are normalized");
  input.clear();
  check(!input.camera().any(), "empty camera input is clear");

  check(!input.wantsQuit(), "quit is false without a held key");
  input.press(Key::kEscape);
  check(input.wantsQuit(), "quit is true while held");
  input.release(Key::kEscape);
  check(!input.wantsQuit(), "release ends quit");

  check(!input.takeToggleHealth(), "toggle starts clear");
  input.press(Key::kToggleHealth);
  input.press(Key::kToggleHealth);
  check(input.takeToggleHealth(), "toggle press is edge-triggered");
  check(!input.takeToggleHealth(), "toggle is consumed once");
  input.press(Key::kToggleHealth);
  input.clear();
  check(!input.takeToggleHealth(), "reset drops pending edges");

  const auto keyDown = input.keyDown(Key::kW);
  check(keyDown.type == InputEventType::kKeyDown && keyDown.key == Key::kW &&
            keyDown.virtualKey == static_cast<std::uint32_t>(Key::kW),
        "key down event is typed");
  const auto keyUp = input.keyUp(Key::kW);
  check(keyUp.type == InputEventType::kKeyUp && keyUp.key == Key::kW,
        "key up event is typed");
  const auto move = input.mouseMove(2.0F, 3.0F);
  check(move.type == InputEventType::kMouseMove && move.x == 2.0F &&
            move.y == 3.0F,
        "mouse move event is typed");
  const auto down = input.mouseDown(4.0F, 5.0F, MouseButton::kLeft);
  check(down.type == InputEventType::kMouseDown &&
            down.button == MouseButton::kLeft,
        "mouse down event is typed");
  const auto up = input.mouseUp(4.0F, 5.0F, MouseButton::kLeft);
  check(up.type == InputEventType::kMouseUp && up.button == MouseButton::kLeft,
        "mouse up event is typed");
  const auto wheel = input.mouseWheel(6.0F, 7.0F, -1.0F);
  check(wheel.type == InputEventType::kMouseWheel && wheel.wheel == -1.0F,
        "mouse wheel event is typed");

  std::printf("cellinput_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
