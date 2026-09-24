// cCellGame state object implementation (see CellGame.hpp for evidence labels).
#include "CellGame.hpp"

#include <cmath>
#include <limits>

namespace openspore::sim {
namespace {

// Size table DAT_01483bd0 (VERIFIED, SporeApp.exe 3.1.0.22 .rdata):
// the per-tier base sizes. CreateCellObject scales by 0.033333335 (= 1/30).
const float kScaleTable[8] = {10.0F,   30.0F,   100.0F,   300.0F,
                              1000.0F, 3000.0F, 10000.0F, 30000.0F};

}  // namespace

CellGameLifecycleResult CellGame::initialize() {
  return initialize(CellGameConfig{});
}

CellGameLifecycleResult CellGame::initialize(const CellGameConfig& config) {
  if (config.poolCapacity == 0 ||
      config.poolCapacity >
          static_cast<uint32_t>(std::numeric_limits<int32_t>::max()) ||
      config.timeScale <= 0.0F || !std::isfinite(config.timeScale)) {
    return {CellGameLifecycleStatus::failure};
  }

  mCells.initialize(config.poolCapacity);
  mMovementState = {};
  mConfiguredCapacity = config.poolCapacity;
  mInitialized = true;
  mTickCount = 0;
  mElapsedSeconds = 0.0F;

  mQueryPool = {};
  mQueryBgPool = {};
  mPool4 = {};
  mPool5 = {};
  mPool6 = {};
  mpCellQuery = 0;
  mpCellQueryBackground = 0;
  mpCurrentWorld = {};
  mpCurrentWorldBackground = {};
  mAvatarCellIndex = cObjectPool<cCellObjectData>::kInvalidIndex;

  field_5194 = 0;
  field_5198 = 0;
  flag_5168 = 0;
  flag_5169 = 0;
  field_515C = 0;
  field_5160 = 0;
  field_516C = 0;
  flag_5148 = 0;
  field_514C = config.timeScale;
  field_5150 = config.timeScale;
  flag_518C = 0;
  field_4124 = 0x14;
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
  flag_51DA = 0;
  bgBBoxMin = kBBoxSrcY - 7.5F;
  bgBBoxZ0 = kBBoxSrcZ;
  bgBBoxMax = kBBoxSrcX + 10.0F;
  bgVisibleMin = kBBoxSrcX - 10.0F;
  bgBBoxMax2 = kBBoxSrcY + 7.5F;
  bgBBoxZ1 = kBBoxSrcZ;
  return {CellGameLifecycleStatus::success};
}

CellGameLifecycleResult CellGame::reset() {
  if (!mInitialized || mConfiguredCapacity == 0) {
    return {CellGameLifecycleStatus::failure};
  }
  return initialize(CellGameConfig{mConfiguredCapacity, field_514C});
}

CellGameLifecycleResult CellGame::tick(float deltaSeconds) {
  if (!mInitialized || deltaSeconds < 0.0F || !std::isfinite(deltaSeconds)) {
    return {CellGameLifecycleStatus::failure};
  }
  mElapsedSeconds += deltaSeconds * field_514C;
  ++mTickCount;
  return {CellGameLifecycleStatus::success};
}

uint32_t CellGame::createCellObject(const CellResourceSpec& resource,
                                    const float position[3], float elevation,
                                    CellStageScale scaleLevel, float sizeFactor,
                                    float cellSize, bool applySize,
                                    const float* targetOrientation) {
  if (!mInitialized || position == nullptr) {
    return cObjectPool<cCellObjectData>::kInvalidIndex;
  }
  // Pool alloc (lines 57-59): pop a free object; exhaustion → invalid index.
  cCellObjectData* obj = mCells.allocate();
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

  // Position (61-63) + elevation (122) + opacity (123-124) + size block
  // (126-132).
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

CellMovementResult CellGame::applyCellMovement(
    uint32_t targetIndex, const CellMovementInput& input,
    const OrientationResolver& orientationResolver) {
  if (!mInitialized) {
    CellMovementResult result;
    result.deltaTime = input.deltaTime;
    return result;
  }
  return openspore::sim::applyCellMovement(mCells, targetIndex, mMovementState,
                                           input, orientationResolver);
}

CellMovementResult CellGame::routeCellMovement(
    uint32_t targetIndex, const MovementInputRouter& inputRouter,
    const OrientationResolver& orientationResolver) {
  if (!mInitialized) {
    return CellMovementResult{};
  }
  return openspore::sim::routeCellMovement(
      mCells, targetIndex, mMovementState, inputRouter, orientationResolver);
}

}  // namespace openspore::sim
