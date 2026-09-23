// CS-29: table-driven key->action test.
//
// Verifies the clean-room CellInput table mirrors the app's mapping:
//   - every bound key looks up to its action; an unbound key is nullptr.
//   - the thrust/boost frame reflects the held keys (W/S/A/D/Shift).
//   - the arrow keys produce the right camera deltas (sign-matched).
//   - ESC is the quit key.
//   - the health-display toggle (the original's virtualKey==2) is
//     edge-triggered: consumed on the first read, clear on the next.
#include "CellInput.hpp"

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

using openspore::cellinput::Action;
using openspore::cellinput::CellInput;
using openspore::cellinput::Key;
using openspore::cellinput::Table;

int main() {
  // Table lookup: every bound key -> its action.
  check(*Table::lookup(Key::kW) == Action::kThrustForward, "table: W -> forward");
  check(*Table::lookup(Key::kS) == Action::kThrustBack, "table: S -> back");
  check(*Table::lookup(Key::kA) == Action::kThrustLeft, "table: A -> left");
  check(*Table::lookup(Key::kD) == Action::kThrustRight, "table: D -> right");
  check(*Table::lookup(Key::kShift) == Action::kBoost, "table: Shift -> boost");
  check(*Table::lookup(Key::kEscape) == Action::kQuit, "table: ESC -> quit");
  check(*Table::lookup(Key::kLeft) == Action::kCamLeft, "table: Left -> camLeft");
  check(*Table::lookup(Key::kRight) == Action::kCamRight, "table: Right -> camRight");
  check(*Table::lookup(Key::kUp) == Action::kCamUp, "table: Up -> camUp");
  check(*Table::lookup(Key::kDown) == Action::kCamDown, "table: Down -> camDown");
  check(*Table::lookup(Key::kToggleHealth) == Action::kToggleHealthDisplay,
        "table: toggle -> healthDisplay");
  // An unbound key (a scancode with no action) looks up to nullptr.
  check(Table::lookup(static_cast<Key>(999)) == nullptr, "table: unbound key -> null");

  // Frame: held keys -> thrust/boost.
  CellInput in;
  in.press(Key::kW);
  in.press(Key::kShift);
  {
    const auto f = in.frame();
    check(f.thrustForward && f.boost && !f.thrustBack && !f.thrustLeft &&
              !f.thrustRight,
          "frame: W+Shift -> forward+boost only");
  }
  in.clear();
  {
    const auto f = in.frame();
    check(!f.thrustForward && !f.thrustBack && !f.thrustLeft && !f.thrustRight &&
              !f.boost,
          "frame: empty -> no thrust/boost");
  }
  in.press(Key::kA);
  in.press(Key::kD);
  {
    const auto f = in.frame();
    check(f.thrustLeft && f.thrustRight, "frame: A+D -> both strafe");
  }
  in.clear();

  // Camera directions: the table reports which arrows are held.
  in.press(Key::kLeft);
  in.press(Key::kUp);
  {
    const auto c = in.camera();
    check(c.left && c.up && !c.right && !c.down, "camera: Left+Up -> left/up");
  }
  in.clear();
  in.press(Key::kRight);
  in.press(Key::kDown);
  {
    const auto c = in.camera();
    check(c.right && c.down && !c.left && !c.up, "camera: Right+Down -> right/down");
  }
  in.clear();
  {
    const auto c = in.camera();
    check(!c.any(), "camera: none -> no direction");
  }

  // Quit key.
  check(!in.wantsQuit(), "quit: none -> false");
  in.press(Key::kEscape);
  check(in.wantsQuit(), "quit: ESC -> true");
  in.release(Key::kEscape);
  check(!in.wantsQuit(), "quit: released -> false");

  // Health-display toggle: edge-triggered, consumed on read.
  check(!in.takeToggleHealth(), "toggle: none -> false");
  in.press(Key::kToggleHealth);
  check(in.takeToggleHealth(), "toggle: pressed -> true");
  check(!in.takeToggleHealth(), "toggle: consumed -> false");

  std::printf("cellinput_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
