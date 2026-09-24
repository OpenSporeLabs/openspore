#pragma once

#include "CellPool.hpp"
#include "Sim.hpp"

#include <cstdint>

namespace openspore::sim {

struct CameraRay {
  float origin[3] = {0.0F, 0.0F, 0.0F};
  float direction[3] = {0.0F, 0.0F, 0.0F};
};

struct CellMovementInput {
  CameraRay cameraRay;
  MovementPlane movementPlane;
  float deltaTime = 0.0F;
};

enum class CellMovementStatus {
  updated,
  invalidInput,
  parallel,
  behind,
  unresolved,
  invalidOrientation,
};

enum class OrientationResolutionStatus {
  resolved,
  unresolved,
  invalidInput,
};

struct OrientationResolution {
  OrientationResolutionStatus status = OrientationResolutionStatus::unresolved;
  float orientation[4] = {0.0F, 0.0F, 0.0F, 1.0F};
};

struct CellMovementLifecycle {
  bool moving = false;
  uint32_t ownerIndex = cObjectPool<cCellObjectData>::kInvalidIndex;
};

class OrientationResolver {
public:
  virtual ~OrientationResolver() = default;

  virtual OrientationResolution resolve(const CellMovementInput &input,
                                        const float target[3]) const = 0;
};

class MovementInputRouter {
public:
  virtual ~MovementInputRouter() = default;

  virtual bool route(CellMovementInput &input) const = 0;
};

struct CellMovementResult {
  CellMovementStatus status = CellMovementStatus::invalidInput;
  bool targetHit = false;
  bool targetUpdated = false;
  bool orientationUpdated = false;
  bool movingStateUpdated = false;
  float hit[3] = {0.0F, 0.0F, 0.0F};
  float deltaTime = 0.0F;

  explicit operator bool() const {
    return status == CellMovementStatus::updated;
  }
};

CellMovementResult
intersectCameraRayWithMovementPlaneExact(const CameraRay &cameraRay,
                                         const MovementPlane &movementPlane,
                                         float hit[3]);

CellMovementResult
applyCellMovement(cObjectPool<cCellObjectData> &pool, uint32_t targetIndex,
                  CellMovementLifecycle &movementState,
                  const CellMovementInput &input,
                  const OrientationResolver &orientationResolver);

CellMovementResult
routeCellMovement(cObjectPool<cCellObjectData> &pool, uint32_t targetIndex,
                  CellMovementLifecycle &movementState,
                  const MovementInputRouter &inputRouter,
                  const OrientationResolver &orientationResolver);

}
