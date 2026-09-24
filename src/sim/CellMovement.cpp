#include "CellMovement.hpp"

#include <cmath>

namespace openspore::sim {
namespace {

bool finite3(const float values[3]) {
  return std::isfinite(values[0]) && std::isfinite(values[1]) &&
         std::isfinite(values[2]);
}

bool finite4(const float values[4]) {
  return std::isfinite(values[0]) && std::isfinite(values[1]) &&
         std::isfinite(values[2]) && std::isfinite(values[3]);
}

bool nonzero3(const float values[3]) {
  return values[0] != 0.0F || values[1] != 0.0F || values[2] != 0.0F;
}

bool validOrientation(const float values[4]) {
  if (!finite4(values)) {
    return false;
  }
  const float squaredNorm = values[0] * values[0] + values[1] * values[1] +
                            values[2] * values[2] + values[3] * values[3];
  return std::isfinite(squaredNorm) && squaredNorm > 0.0F;
}

CellMovementResult resultWithStatus(CellMovementStatus status,
                                    float deltaTime) {
  CellMovementResult result;
  result.status = status;
  result.deltaTime = deltaTime;
  return result;
}

}

CellMovementResult
intersectCameraRayWithMovementPlaneExact(const CameraRay &cameraRay,
                                         const MovementPlane &movementPlane,
                                         float hit[3]) {
  if (hit == nullptr || !finite3(cameraRay.origin) ||
      !finite3(cameraRay.direction) || !finite3(movementPlane.normal) ||
      !finite3(movementPlane.point) || !nonzero3(cameraRay.direction) ||
      !nonzero3(movementPlane.normal)) {
    return resultWithStatus(CellMovementStatus::invalidInput, 0.0F);
  }

  const float denominator = cameraRay.direction[0] * movementPlane.normal[0] +
                            cameraRay.direction[1] * movementPlane.normal[1] +
                            cameraRay.direction[2] * movementPlane.normal[2];
  if (denominator == 0.0F) {
    return resultWithStatus(CellMovementStatus::parallel, 0.0F);
  }
  if (!std::isfinite(denominator)) {
    return resultWithStatus(CellMovementStatus::invalidInput, 0.0F);
  }

  const float t = ((movementPlane.point[0] - cameraRay.origin[0]) *
                       movementPlane.normal[0] +
                   (movementPlane.point[1] - cameraRay.origin[1]) *
                       movementPlane.normal[1] +
                   (movementPlane.point[2] - cameraRay.origin[2]) *
                       movementPlane.normal[2]) /
                  denominator;
  if (!std::isfinite(t)) {
    return resultWithStatus(CellMovementStatus::invalidInput, 0.0F);
  }
  if (t < 0.0F) {
    return resultWithStatus(CellMovementStatus::behind, 0.0F);
  }

  float localHit[3] = {0.0F, 0.0F, 0.0F};
  for (int i = 0; i < 3; ++i) {
    localHit[i] = cameraRay.origin[i] + cameraRay.direction[i] * t;
  }
  if (!finite3(localHit)) {
    return resultWithStatus(CellMovementStatus::invalidInput, 0.0F);
  }

  CellMovementResult result;
  result.status = CellMovementStatus::updated;
  result.targetHit = true;
  for (int i = 0; i < 3; ++i) {
    hit[i] = localHit[i];
    result.hit[i] = localHit[i];
  }
  return result;
}

CellMovementResult
applyCellMovement(cObjectPool<cCellObjectData> &pool, uint32_t targetIndex,
                  CellMovementLifecycle &movementState,
                  const CellMovementInput &input,
                  const OrientationResolver &orientationResolver) {
  if (!std::isfinite(input.deltaTime) || input.deltaTime < 0.0F) {
    return resultWithStatus(CellMovementStatus::invalidInput, input.deltaTime);
  }

  cCellObjectData *target = pool.lookup(targetIndex);
  if (target == nullptr || !pool.isAllocated(target)) {
    return resultWithStatus(CellMovementStatus::invalidInput, input.deltaTime);
  }

  float hit[3] = {0.0F, 0.0F, 0.0F};
  CellMovementResult result = intersectCameraRayWithMovementPlaneExact(
      input.cameraRay, input.movementPlane, hit);
  result.deltaTime = input.deltaTime;
  if (result.status != CellMovementStatus::updated) {
    return result;
  }

  const OrientationResolution resolution =
      orientationResolver.resolve(input, hit);
  if (resolution.status != OrientationResolutionStatus::resolved) {
    result.status = resolution.status == OrientationResolutionStatus::invalidInput
                        ? CellMovementStatus::invalidOrientation
                        : CellMovementStatus::unresolved;
    return result;
  }
  if (!validOrientation(resolution.orientation)) {
    result.status = CellMovementStatus::invalidOrientation;
    return result;
  }

  for (int i = 0; i < 3; ++i) {
    target->mTargetPosition[i] = hit[i];
    result.hit[i] = hit[i];
  }
  for (int i = 0; i < 4; ++i) {
    target->mTargetOrientation[i] = resolution.orientation[i];
  }
  movementState.moving = true;
  movementState.ownerIndex = targetIndex;
  result.targetUpdated = true;
  result.orientationUpdated = true;
  result.movingStateUpdated = true;
  result.status = CellMovementStatus::updated;
  return result;
}

CellMovementResult
routeCellMovement(cObjectPool<cCellObjectData> &pool, uint32_t targetIndex,
                  CellMovementLifecycle &movementState,
                  const MovementInputRouter &inputRouter,
                  const OrientationResolver &orientationResolver) {
  cCellObjectData *target = pool.lookup(targetIndex);
  if (target == nullptr || !pool.isAllocated(target)) {
    return resultWithStatus(CellMovementStatus::invalidInput, 0.0F);
  }

  CellMovementInput input;
  if (!inputRouter.route(input)) {
    return resultWithStatus(CellMovementStatus::invalidInput, input.deltaTime);
  }
  return applyCellMovement(pool, targetIndex, movementState, input,
                           orientationResolver);
}

}
