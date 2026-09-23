// CS-27: cCellUI HUD — Load constants + ShowHealthRollover formula.
//
// Verifies the clean-room CellUI mirrors the original:
//   - load() sets the "GlobalUICell-3" element + layout constants (20.0f / 1.0f).
//   - showHealthRollover() early-outs when the cell has no GFX object (index 0),
//     and otherwise records field_8 = initialHealth * (1/6) with
//     mDisappearTime = 0.5f (the decompiled *(+0x24) = 0x3f000000).
#include "CellUI.hpp"

#include <cmath>
#include <cstdio>
#include <string>

namespace {
int g_failures = 0;
void check(bool cond, const char *label) {
  std::printf("%s: %s\n", cond ? "ok" : "FAIL", label);
  if (!cond) {
    ++g_failures;
  }
}
bool near(float a, float b) { return std::abs(a - b) < 1e-4F; }
} // namespace

using openspore::cellui::CellUI;

int main() {
  CellUI ui;
  ui.load();
  check(ui.loaded, "cellui: load() marks loaded");
  check(std::string(ui.globalUi) == "GlobalUICell-3",
        "cellui: GlobalUICell-3 element");
  check(near(ui.layoutA, 20.0F), "cellui: layoutA == 20.0f (0x41a00000)");
  check(near(ui.layoutB, 1.0F), "cellui: layoutB == 1.0f (0x3f800000)");

  // No GFX object -> no rollover (original early-out).
  check(ui.showHealthRollover(0, 3, 12) == -1,
        "cellui: no GFX object -> no rollover");
  check(ui.rollovers.empty(), "cellui: rollover pool empty after no-GFX call");

  // Live GFX object -> rollover with field_8 = hp/6, mDisappearTime = 0.5f.
  const int idx = ui.showHealthRollover(1, 3, 12);
  check(idx == 0, "cellui: first rollover at pool index 0");
  if (idx == 0) {
    check(near(ui.rollovers[0].field_8, 12.0F / 6.0F),
          "cellui: rollover field_8 == initialHealth/6");
    check(near(ui.rollovers[0].mDisappearTime, 0.5F),
          "cellui: rollover mDisappearTime == 0.5f (0x3f000000)");
    check(ui.rollovers[0].mObjectPoolIndex == 3,
          "cellui: rollover object pool index recorded");
  }

  // A second cell's rollover appends.
  const int idx2 = ui.showHealthRollover(1, 7, 24);
  check(idx2 == 1, "cellui: second rollover at pool index 1");
  if (idx2 == 1) {
    check(near(ui.rollovers[1].field_8, 24.0F / 6.0F),
          "cellui: second rollover field_8 == 24/6");
  }

  std::printf("cellui_test: %s\n", g_failures == 0 ? "ALL PASS" : "FAIL");
  return g_failures == 0 ? 0 : 1;
}
