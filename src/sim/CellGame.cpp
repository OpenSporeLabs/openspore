// cCellGame state object implementation (see CellGame.hpp for evidence labels).
#include "CellGame.hpp"

#include <cstring>

namespace openspore::sim {
namespace {

float bitsToFloat(uint32_t bits) {
  float f;
  std::memcpy(&f, &bits, sizeof(f));
  return f;
}

// Size table DAT_01483bd0 (VERIFIED, SporeApp.exe 3.1.0.22 .rdata):
// the per-tier base sizes. CreateCellObject scales by 0.033333335 (= 1/30).
const float kScaleTable[8] = {10.0F,  30.0F,   100.0F,  300.0F,
                              1000.0F, 3000.0F, 10000.0F, 30000.0F};

} // namespace

void CellGame::initialize() {
  // OBSERVABLE Initialize sequence (Simulator::Cell::cCellGame::Initialize @
  // 00e80ba0, decompilation). The IAppSystem::SetTimeScale call at the top and
  // the cGameNounManager / collectable-items calls are app-layer side effects
  // this state object does not model; only the sCellGame field writes and the
  // pool allocation are reproduced.

  // Early flag / field resets (decompiled store order).
  field_5194 = 0;
  field_5198 = 0;
  flag_5168 = 0;
  flag_5169 = 0;
  field_515C = 0;
  field_5160 = 0;
  field_516C = 0;

  // Pool allocation: thunk_FUN_00bbb400(0x1000, 0x1000) -> capacity 4096.
  mCells.initialize(0x1000);

  // Time-scale load value (OBSERVED): field_514C = 0x3f000000 (1.0f), and the
  // adjacent field_5150 is written with the same value.
  flag_5148 = 0;
  field_514C = bitsToFloat(0x3F800000u);
  field_5150 = field_514C;
  flag_518C = 0;

  // field_4124 = 0x14 (20).
  field_4124 = 0x14;

  // Late-zeroed block (0x51B0..0x51E0). field_51B4 = 0xffffffff (-1);
  // field_51BC is a runtime value (FUN_00e52b70, INFERRED) left at 0.0f.
  field_51B0 = 0;
  field_51B4 = 0xFFFFFFFFu;
  field_51B8 = 0;
  field_51BC = 0.0F;
  flag_51C0 = 0;
  field_51C4 = 0;
  field_51C8 = 0;
  field_51CC = 0;
  field_51D0 = 0;
  flag_51DB = 0;
  flag_51DC = 0;
  field_51E0 = 0;
  mShowCallMateButtonCountdown = 0.0F;
  field_51D4 = 0;
  field_51D8 = 0;

  // flag_51DA is set to 1 only when serializable data is present on entry; the
  // load-time / no-save path leaves it 0.
  flag_51DA = 0;

  // Background visible-bbox, from the read source constants (VERIFIED).
  bgBBoxMin = kBBoxSrcY - 7.5F;       // DAT_016b3c8c
  bgBBoxZ0 = kBBoxSrcZ + 0.0F;        // DAT_016b3c90
  bgBBoxMax = kBBoxSrcX + 10.0F;      // DAT_016b3c94
  bgVisibleMin = kBBoxSrcX - 10.0F;   // sVisibleBackgroundBBox
  bgBBoxMax2 = kBBoxSrcY + 7.5F;      // DAT_016b3c98
  bgBBoxZ1 = kBBoxSrcZ + 0.0F;        // DAT_016b3c9c
}

uint32_t
CellGame::createCellObject(const CellResourceSpec &resource,
                           const float position[3],
                           float elevation,
                           CellStageScale scaleLevel,
                           float sizeFactor,
                           float cellSize,
                           bool applySize,
                           const float *targetOrientation) {
  // Pool alloc (lines 57-59): pop a free object; exhaustion → invalid index.
  cCellObjectData *obj = mCells.allocate();
  if (!obj) {
    return cObjectPool<cCellObjectData>::kInvalidIndex;
  }
  obj->mIsIdle = 1;  // line 60

  // cellSize (lines 43-56): timeScale = field_514C (1.0 after initialize).
  if (cellSize == 0.0F) {
    float base;
    if (scaleLevel == CellStageScale::None) {
      base = 1.0F;
    } else {
      int32_t lvl = static_cast<int32_t>(scaleLevel);
      base = (lvl >= 0 && lvl < 8) ? kScaleTable[lvl] * 0.033333335F : 1.0F;
    }
    cellSize = (base / field_514C) * resource.size * sizeFactor;
  } else {
    cellSize = sizeFactor * cellSize;
  }

  // Orientation (lines 65-94): fixed → identity quat (DAT_015a7c4c..58);
  // null target → computed yaw (identity at yaw≈0); else copy the target.
  float q[4];
  if (resource.fixedOrientation || targetOrientation == nullptr) {
    q[0] = 0.0F;
    q[1] = 0.0F;
    q[2] = 0.0F;
    q[3] = 1.0F;
  } else {
    for (int i = 0; i < 4; ++i) {
      q[i] = targetOrientation[i];
    }
  }
  for (int i = 0; i < 4; ++i) {
    obj->mTargetOrientation[i] = q[i];
  }

  // Position (61-63) + elevation (122) + opacity (123-124) + size block (126-132).
  obj->mTargetPosition[0] = position[0];
  obj->mTargetPosition[1] = position[1];
  obj->mTargetPosition[2] = position[2];
  obj->mRelativeElevation = elevation;
  obj->mOpacity = 1.0F;
  obj->mTargetOpacity = 1.0F;
  obj->field_A8 = 0.0F;
  obj->field_AC = 10.0F;
  obj->field_BC = cellSize;  // line 125: the computed cellSize
  if (applySize) {
    // line 135: the size is pushed into the transform's uniform scale
    // (offset 0x58 = mTransform[0x10]); mTargetSize(0xb4) is NOT written.
    obj->mTransform[0x10] = cellSize;
  }

  // Model key (lines 167-171) + scale level (line 189).
  obj->mModelKey[0] = resource.modelKey[0];
  obj->mModelKey[1] = resource.modelKey[1];
  obj->mModelKey[2] = resource.modelKey[2];
  obj->mScaleLevel = static_cast<int32_t>(scaleLevel);

  return obj->mObjectPoolIndex;
}

} // namespace openspore::sim
