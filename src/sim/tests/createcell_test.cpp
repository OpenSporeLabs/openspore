// CS-18: CreateCellObject @ 00e74a20 (1,689 B — largest cell function).
// Fixture-driven: given a resource spec + position + scale + size factor, the
// produced cCellObjectData matches the contract snapshot.
//
// Observable contract (decompilation, docs/analysis/dossiers):
//   cellSize 0     -> base * resource.size * sizeFactor, base=(None?1:table/30)
//   cellSize != 0  -> sizeFactor * cellSize
//   mTargetPosition = position ; mRelativeElevation = elevation
//   mOpacity = mTargetOpacity = 1.0 ; field_AC = 10.0 ; field_BC = cellSize
//   mModelKey = resource.modelKey ; mScaleLevel = tier
//   orientation: fixed / null target -> identity quat ; else the target quat
// Size table DAT_01483bd0 (VERIFIED, .rdata): [10,30,100,300,1000,3000,10000,30000].
#include <cmath>
#include <cstdio>

#include "CellGame.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

using openspore::sim::CellGame;
using openspore::sim::CellStageScale;
using openspore::sim::CellResourceSpec;
using openspore::sim::cCellObjectData;
using openspore::sim::cObjectPool;

bool closeF(float a, float b, float eps = 1e-4F) {
  return std::fabs(a - b) <= eps;
}

// Assert the fields every created object must carry, then the size-specific one.
void assertCommon(const cCellObjectData *o, const float pos[3], float elevation,
                  const uint32_t key[3], CellStageScale tier, float cellSize) {
  check(o->mTargetPosition[0] == pos[0] && o->mTargetPosition[1] == pos[1] &&
            o->mTargetPosition[2] == pos[2],
        "create: mTargetPosition = spawn position");
  check(o->mRelativeElevation == elevation,
        "create: mRelativeElevation = elevation");
  check(o->mOpacity == 1.0F && o->mTargetOpacity == 1.0F,
        "create: mOpacity = mTargetOpacity = 1.0");
  check(o->field_AC == 10.0F, "create: field_AC = 10.0");
  check(closeF(o->field_BC, cellSize), "create: field_BC = computed cellSize");
  check(o->mModelKey[0] == key[0] && o->mModelKey[1] == key[1] &&
            o->mModelKey[2] == key[2],
        "create: mModelKey = resource model key");
  check(o->mScaleLevel == static_cast<int32_t>(tier),
        "create: mScaleLevel = tier");
}

void testNoneScale() {
  CellGame g;
  g.initialize();
  CellResourceSpec res;
  res.size = 2.0F;
  res.modelKey[0] = 11;
  res.modelKey[1] = 22;
  res.modelKey[2] = 33;
  const float pos[3] = {1.0F, -2.0F, 3.0F};
  // None -> base 1.0 : cellSize = 1.0 * 2.0 * 1.5 = 3.0
  auto idx = g.createCellObject(res, pos, 0.5F, CellStageScale::None, 1.5F, 0.0F,
                                true, nullptr);
  cCellObjectData *o = g.objectAt(idx);
  check(o != nullptr, "create: pool alloc returns a live object");
  assertCommon(o, pos, 0.5F, res.modelKey, CellStageScale::None, 3.0F);
}

void testTierScale() {
  CellGame g;
  g.initialize();
  CellResourceSpec res;
  res.size = 30.0F;  // table[4]=1000 -> base 1000/30 ; cellSize = (1000/30)*30 = 1000
  res.modelKey[0] = 7;
  const float pos[3] = {0.0F, 0.0F, 0.0F};
  // tier _10 (value 4) -> table[4]=1000 -> base=1000/30 ; x size 30 -> 1000.0
  auto idx =
      g.createCellObject(res, pos, 0.0F, CellStageScale::_10, 1.0F, 0.0F, false,
                         nullptr);
  cCellObjectData *o = g.objectAt(idx);
  check(o != nullptr, "create: tier scale alloc");
  check(closeF(o->field_BC, 1000.0F, 1e-3F),
        "create: tier _10 -> cellSize 1000.0 (table[4]=1000)");
  check(o->mTargetSize == 0.0F, "create: applySize=false leaves mTargetSize zeroed");
  check(o->mTransform[0x10] == 0.0F, "create: applySize=false leaves transform scale zeroed");
}

void testExplicitSize() {
  CellGame g;
  g.initialize();
  CellResourceSpec res;
  res.size = 1.0F;
  const float pos[3] = {5.0F, 5.0F, 5.0F};
  // explicit cellSize 5.0 * sizeFactor 2.0 = 10.0
  auto idx =
      g.createCellObject(res, pos, 1.0F, CellStageScale::_2, 2.0F, 5.0F, true,
                         nullptr);
  cCellObjectData *o = g.objectAt(idx);
  check(o != nullptr, "create: explicit size alloc");
  check(closeF(o->field_BC, 10.0F), "create: explicit cellSize 5*2 = 10.0");
  check(closeF(o->mTransform[0x10], 10.0F), "create: applySize -> transform scale = 10.0");
}

void testOrientation() {
  CellGame g;
  g.initialize();
  CellResourceSpec res;
  const float pos[3] = {0.0F, 0.0F, 0.0F};
  // fixed orientation -> identity quat {0,0,0,1}
  res.fixedOrientation = true;
  auto a = g.createCellObject(res, pos, 0.0F, CellStageScale::None, 1.0F, 0.0F,
                              false, nullptr);
  cCellObjectData *oa = g.objectAt(a);
  check(oa && oa->mTargetOrientation[3] == 1.0F &&
            oa->mTargetOrientation[0] == 0.0F,
        "create: fixed orientation -> identity quat");
  // target orientation -> copied verbatim
  const float tq[4] = {0.7071F, 0.0F, 0.7071F, 0.0F};
  res.fixedOrientation = false;
  auto b = g.createCellObject(res, pos, 0.0F, CellStageScale::None, 1.0F, 0.0F,
                              false, tq);
  cCellObjectData *ob = g.objectAt(b);
  check(ob && closeF(ob->mTargetOrientation[0], 0.7071F, 1e-4F) &&
            closeF(ob->mTargetOrientation[2], 0.7071F, 1e-4F),
        "create: target orientation copied");
}

void testExhaustion() {
  CellGame g;
  g.initialize();
  CellResourceSpec res;
  const float pos[3] = {0.0F, 0.0F, 0.0F};
  uint32_t made = 0;
  for (uint32_t i = 0; i < 0x1000; ++i) {
    auto idx =
        g.createCellObject(res, pos, 0.0F, CellStageScale::None, 1.0F, 0.0F, false,
                           nullptr);
    if (idx == cObjectPool<cCellObjectData>::kInvalidIndex) {
      break;
    }
    ++made;
  }
  check(made == 0x1000, "create: fills the whole 4096 pool");
  auto over = g.createCellObject(res, pos, 0.0F, CellStageScale::None, 1.0F, 0.0F,
                                 false, nullptr);
  check(over == cObjectPool<cCellObjectData>::kInvalidIndex,
        "create: exhaustion -> invalid index");
  check(g.cells().mNumAllocatedObjects == 0x1000,
        "create: allocated count == capacity");
}

} // namespace

int main() {
  testNoneScale();
  testTierScale();
  testExplicitSize();
  testOrientation();
  testExhaustion();
  if (g_failures == 0) {
    std::printf("createcell_test: ALL PASS\n");
    return 0;
  }
  std::printf("createcell_test: %d FAILURES\n", g_failures);
  return 1;
}
