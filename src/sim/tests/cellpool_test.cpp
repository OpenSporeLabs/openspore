// CS-16: cObjectPool<cCellObjectData> — allocation + exhaustion.
// Evidence: SDK cObjectPool struct (28 B free-list pool) + the main cell pool's
// VERIFIED capacity 4,096 (0x1000, cCellGame::Initialize allocation). This test
// fills the whole pool, confirms the next allocation fails, then drains and
// refills. Pure C++ + stdlib.
#include <cstdio>
#include <vector>

#include "CellPool.hpp"

namespace {

using openspore::sim::cCellObjectData;
using openspore::sim::cObjectPool;

int g_failures = 0;

void check(bool cond, const char *label) {
  if (cond) {
    std::printf("ok: %s\n", label);
  } else {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  }
}

} // namespace

int main() {
  constexpr int kCap = 0x1000;  // 4096, VERIFIED cell pool capacity
  cObjectPool<cCellObjectData> pool;
  pool.initialize(kCap);

  check(pool.mNumObjects == kCap, "capacity == 4096");
  check(pool.mObjectSize == static_cast<int>(sizeof(cCellObjectData)),
        "mObjectSize == sizeof(cCellObjectData)");
  check(pool.mNumAllocatedObjects == 0, "starts with 0 allocated");
  check(pool.mNextAvailableIndex == 0, "free-list head starts at index 0");

  // Fill the whole pool: every object allocated exactly once.
  std::vector<cCellObjectData *> all;
  all.reserve(kCap);
  bool filled = true;
  for (int i = 0; i < kCap; ++i) {
    cCellObjectData *o = pool.allocate();
    if (!o) {
      filled = false;
      break;
    }
    all.push_back(o);
  }
  check(filled, "allocated all 4096 objects");
  check(pool.mNumAllocatedObjects == kCap, "mNumAllocatedObjects == 4096 at full");

  // Distinct indices covering the full range; allocated objects are
  // self-indexed and no longer idle.
  std::vector<bool> seen(static_cast<size_t>(kCap), false);
  bool distinct = true;
  bool noneIdle = true;
  for (cCellObjectData *o : all) {
    uint32_t idx = pool.index(o);
    if (idx >= static_cast<uint32_t>(kCap) || seen[idx]) {
      distinct = false;
    }
    seen[idx] = true;
    if (!pool.isAllocated(o) || o->mObjectPoolIndex != idx) {
      distinct = false;
    }
    if (o->mIsIdle) {
      noneIdle = false;
    }
  }
  check(distinct, "indices distinct 0..4095, self-index + isAllocated correct");
  check(noneIdle, "all allocated objects are not idle");

  // Exhaustion: one more allocation returns null, count unchanged.
  check(pool.allocate() == nullptr, "allocate at full returns null (exhaustion)");
  check(pool.mNumAllocatedObjects == kCap, "count unchanged after failed alloc");

  // Drain, then refill: deallocate everything, confirm the count resets, and
  // that a full re-allocation again covers every index exactly once.
  for (cCellObjectData *o : all) {
    pool.deallocate(o);
  }
  check(pool.mNumAllocatedObjects == 0, "count back to 0 after full drain");
  std::vector<bool> refilled(static_cast<size_t>(kCap), false);
  bool refillOk = true;
  for (int i = 0; i < kCap; ++i) {
    cCellObjectData *o = pool.allocate();
    if (!o) {
      refillOk = false;
      break;
    }
    refilled[pool.index(o)] = true;
  }
  bool coversAll = true;
  for (bool s : refilled) {
    if (!s) {
      coversAll = false;
    }
  }
  check(refillOk && coversAll, "re-allocate full pool after drain");

  if (g_failures == 0) {
    std::printf("cellpool_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellpool_test: %d FAILURES\n", g_failures);
  return 1;
}
