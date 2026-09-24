// CS-15: the cCellGame state object's Initialize sequence.
// Evidence: Simulator::Cell::cCellGame::Initialize @ 00e80ba0 (decompiled).
// The background-bbox source constants DAT_015a7d3c/40/44 were read from the
// static binary (SporeApp.exe 3.1.0.22 .data, VERIFIED). This test asserts the
// OBSERVABLE field writes initialize() performs: time-scale load value, the
// flag resets, the pool capacity, and the background-bbox. Pure C++ + stdlib.
#include "CellGame.hpp"

#include <cmath>
#include <cstdio>

namespace {

using openspore::sim::CellGame;

int g_failures = 0;

void check(bool cond, const char* label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

bool feq(float a, float b) { return a == b; }

}  // namespace

int main() {
  CellGame g;
  g.initialize();

  // Time-scale load value (OBSERVED 0x3f000000 = 1.0f).
  check(feq(g.field_514C, 1.0F), "field_514C time-scale == 1.0f");
  check(feq(g.field_5150, g.field_514C), "field_5150 == field_514C");

  // Pool allocation: capacity 4096 (real cObjectPool, CS-16).
  check(g.mCells.mNumObjects == 0x1000, "mCells.mNumObjects == 4096");
  check(g.mCells.mNumAllocatedObjects == 0, "mCells starts empty");

  // field_4124 = 20.
  check(g.field_4124 == 0x14u, "field_4124 == 20");

  // field_51B4 = -1.
  check(g.field_51B4 == 0xFFFFFFFFu, "field_51B4 == -1");

  // Flag / field resets.
  check(g.flag_5148 == 0 && g.flag_5168 == 0 && g.flag_5169 == 0 &&
            g.flag_518C == 0 && g.flag_51DA == 0,
        "early flags reset to 0");
  check(g.field_515C == 0 && g.field_5160 == 0 && g.field_516C == 0 &&
            g.field_5194 == 0 && g.field_5198 == 0,
        "early fields reset to 0");
  check(g.field_51B0 == 0 && g.field_51B8 == 0 && g.flag_51C0 == 0 &&
            g.field_51C4 == 0 && g.field_51C8 == 0 && g.field_51CC == 0 &&
            g.field_51D0 == 0 && g.flag_51DB == 0 && g.flag_51DC == 0 &&
            g.field_51E0 == 0 && g.field_51D4 == 0 && g.field_51D8 == 0,
        "late block reset to 0");

  // Background-bbox from the read source constants (VERIFIED).
  check(feq(g.bgBBoxMax, 6.023681640625F + 10.0F), "bgBBoxMax == srcX + 10.0");
  check(feq(g.bgVisibleMin, 6.023681640625F - 10.0F),
        "bgVisibleMin == srcX - 10.0");
  check(feq(g.bgBBoxMax2, 3.5216064453125F + 7.5F), "bgBBoxMax2 == srcY + 7.5");
  check(feq(g.bgBBoxMin, 3.5216064453125F - 7.5F), "bgBBoxMin == srcY - 7.5");
  check(feq(g.bgBBoxZ0, 3.5372314453125F), "bgBBoxZ0 == srcZ");
  check(feq(g.bgBBoxZ1, 3.5372314453125F), "bgBBoxZ1 == srcZ");

  // World references default empty, and are settable (world switching).
  check(g.currentWorld().id == 0 && g.currentWorldBackground().id == 0,
        "world references start empty");
  g.setCurrentWorld(42);
  g.setCurrentWorldBackground(7);
  check(g.currentWorld().id == 42 && g.currentWorldBackground().id == 7,
        "setCurrentWorld / setCurrentWorldBackground update references");

  check(g.tick(0.25F).status ==
                openspore::sim::CellGameLifecycleStatus::success &&
            g.mTickCount == 1 && g.mElapsedSeconds == 0.25F,
        "lifecycle: tick advances pure time state");
  check(!g.tick(-1.0F) && g.mTickCount == 1,
        "lifecycle: negative tick fails without mutation");
  check(g.reset() && g.mTickCount == 0 && g.mElapsedSeconds == 0.0F &&
            g.mCells.mNumObjects == 0x1000,
        "lifecycle: reset clears runtime counters and keeps capacity");

  CellGame configured;
  openspore::sim::CellGameConfig config;
  config.poolCapacity = 2;
  check(configured.initialize(config) && configured.mCells.mNumObjects == 2,
        "lifecycle: custom bounded capacity initializes");
  CellGame uninitialized;
  check(uninitialized.createCellObject({}, nullptr, 0.0F,
                                       openspore::sim::CellStageScale::None,
                                       1.0F, 0.0F, false, nullptr) ==
            openspore::sim::cObjectPool<
                openspore::sim::cCellObjectData>::kInvalidIndex,
        "lifecycle: create before initialization is rejected");
  if (g_failures == 0) {
    std::printf("cellgame_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellgame_test: %d FAILURES\n", g_failures);
  return 1;
}
