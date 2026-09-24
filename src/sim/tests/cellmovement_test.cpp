#include "CellGame.hpp"
#include "CellMovement.hpp"

#include <cmath>
#include <cstdio>
#include <limits>

namespace {

int g_failures = 0;

void check(bool condition, const char *label) {
  if (!condition) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  }
}

using namespace openspore::sim;

class Resolver final : public OrientationResolver {
public:
  OrientationResolution resolve(const CellMovementInput &input,
                                const float target[3]) const override {
    ++calls;
    lastTarget[0] = target[0];
    lastTarget[1] = target[1];
    lastTarget[2] = target[2];
    lastDeltaTime = input.deltaTime;
    return resolution;
  }

  mutable int calls = 0;
  mutable float lastTarget[3] = {0.0F, 0.0F, 0.0F};
  mutable float lastDeltaTime = 0.0F;
  OrientationResolution resolution;
};

class Router final : public MovementInputRouter {
public:
  bool route(CellMovementInput &input) const override {
    ++calls;
    if (!available) {
      return false;
    }
    input = value;
    return true;
  }

  mutable int calls = 0;
  bool available = true;
  CellMovementInput value;
};

CellMovementInput validInput() {
  CellMovementInput input;
  input.cameraRay.origin[2] = 5.0F;
  input.cameraRay.direction[2] = -1.0F;
  input.deltaTime = 0.25F;
  return input;
}

void resolveOrientation(Resolver &resolver) {
  resolver.resolution.status = OrientationResolutionStatus::resolved;
  resolver.resolution.orientation[0] = 1.0F;
  resolver.resolution.orientation[1] = 2.0F;
  resolver.resolution.orientation[2] = 3.0F;
  resolver.resolution.orientation[3] = 4.0F;
}

bool near(float actual, float expected) {
  return std::fabs(actual - expected) < 1e-5F;
}

bool near3(const float actual[3], const float expected[3]) {
  return near(actual[0], expected[0]) && near(actual[1], expected[1]) &&
         near(actual[2], expected[2]);
}

void testValidTargetAndLifecycle() {
  Resolver resolver;
  resolveOrientation(resolver);
  cObjectPool<cCellObjectData> pool;
  pool.initialize(1);
  cCellObjectData *target = pool.allocate();
  check(target != nullptr, "pool allocates movement target");
  if (target == nullptr) {
    return;
  }

  CellMovementLifecycle lifecycle;
  const CellMovementResult result =
      applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  const float expected[3] = {0.0F, 0.0F, 0.0F};
  check(result.status == CellMovementStatus::updated && result.targetHit &&
            result.targetUpdated && result.orientationUpdated &&
            result.movingStateUpdated,
        "valid movement atomically updates target orientation and lifecycle");
  check(near3(result.hit, expected) && near3(target->mTargetPosition, expected),
        "valid movement stores the plane hit");
  check(target->mTargetOrientation[0] == 1.0F &&
            target->mTargetOrientation[3] == 4.0F,
        "valid movement stores resolved orientation");
  check(lifecycle.moving && lifecycle.ownerIndex == 0,
        "valid movement owns explicit moving lifecycle");
  check(resolver.calls == 1 && near3(resolver.lastTarget, expected) &&
            near(resolver.lastDeltaTime, 0.25F),
        "orientation resolver receives hit and deltaTime");
}

void testObliquePlane() {
  Resolver resolver;
  resolveOrientation(resolver);
  cObjectPool<cCellObjectData> pool;
  pool.initialize(1);
  cCellObjectData *target = pool.allocate();
  if (target == nullptr) {
    check(false, "oblique test allocates target");
    return;
  }

  CellMovementInput input = validInput();
  input.cameraRay.origin[0] = 0.0F;
  input.cameraRay.origin[1] = 0.0F;
  input.cameraRay.origin[2] = 0.0F;
  input.cameraRay.direction[0] = 2.0F;
  input.cameraRay.direction[1] = 2.0F;
  input.cameraRay.direction[2] = 2.0F;
  input.movementPlane.normal[0] = 1.0F;
  input.movementPlane.normal[1] = 1.0F;
  input.movementPlane.normal[2] = 1.0F;
  input.movementPlane.point[0] = 3.0F;
  input.movementPlane.point[1] = 4.0F;
  input.movementPlane.point[2] = 5.0F;
  CellMovementLifecycle lifecycle;
  const CellMovementResult result =
      applyCellMovement(pool, 0, lifecycle, input, resolver);
  const float expected[3] = {4.0F, 4.0F, 4.0F};
  check(result.status == CellMovementStatus::updated && result.targetHit &&
            near3(result.hit, expected) &&
            near3(target->mTargetPosition, expected),
        "canonical movement plane supports oblique geometry");
}

void testIntersectionBoundary() {
  CameraRay ray;
  ray.origin[2] = -5.0F;
  ray.direction[0] = 1.0F;
  ray.direction[2] = 5e-7F;
  float exactHit[3] = {1.0F, 2.0F, 3.0F};
  float canonicalHit[3] = {1.0F, 2.0F, 3.0F};
  const CellMovementResult exact = intersectCameraRayWithMovementPlaneExact(
      ray, MovementPlane{}, exactHit);
  const bool canonical = rayPlaneHit(ray.origin, ray.direction,
                                     MovementPlane{}, canonicalHit);
  check(exact.status == CellMovementStatus::updated && !canonical &&
            near(exactHit[0], 1.0e7F) && near(exactHit[2], 0.0F),
        "exact helper exposes below canonical epsilon boundary");

  exactHit[0] = 1.0F;
  exactHit[1] = 2.0F;
  exactHit[2] = 3.0F;
  ray.direction[2] = 0.0F;
  const CellMovementResult parallel = intersectCameraRayWithMovementPlaneExact(
      ray, MovementPlane{}, exactHit);
  check(parallel.status == CellMovementStatus::parallel &&
            exactHit[0] == 1.0F && exactHit[1] == 2.0F &&
            exactHit[2] == 3.0F,
        "exact parallel helper is isolated and does not partially write hit");

  ray.origin[2] = -5.0F;
  ray.direction[2] = -1.0F;
  const CellMovementResult behind = intersectCameraRayWithMovementPlaneExact(
      ray, MovementPlane{}, exactHit);
  check(behind.status == CellMovementStatus::behind &&
            exactHit[0] == 1.0F && exactHit[1] == 2.0F &&
            exactHit[2] == 3.0F,
        "exact behind helper is isolated and does not partially write hit");
}

void testInvalidInputsAreAtomic() {
  Resolver resolver;
  resolveOrientation(resolver);
  cObjectPool<cCellObjectData> pool;
  pool.initialize(1);
  cCellObjectData *target = pool.allocate();
  if (target == nullptr) {
    check(false, "invalid input test allocates target");
    return;
  }

  const float oldPosition[3] = {7.0F, 8.0F, 9.0F};
  const float oldOrientation[4] = {0.2F, 0.3F, 0.4F, 0.5F};
  for (int i = 0; i < 3; ++i) {
    target->mTargetPosition[i] = oldPosition[i];
  }
  for (int i = 0; i < 4; ++i) {
    target->mTargetOrientation[i] = oldOrientation[i];
  }
  CellMovementLifecycle lifecycle;
  lifecycle.moving = true;
  lifecycle.ownerIndex = 77;

  const float nan = std::numeric_limits<float>::quiet_NaN();
  const float infinity = std::numeric_limits<float>::infinity();
  CellMovementInput negativeTime = validInput();
  negativeTime.deltaTime = -1.0F;
  CellMovementInput nanTime = validInput();
  nanTime.deltaTime = nan;
  CellMovementInput infiniteTime = validInput();
  infiniteTime.deltaTime = infinity;
  CellMovementInput nanNormal = validInput();
  nanNormal.movementPlane.normal[0] = nan;
  CellMovementInput infinitePoint = validInput();
  infinitePoint.movementPlane.point[2] = infinity;
  CellMovementInput zeroNormal = validInput();
  zeroNormal.movementPlane.normal[2] = 0.0F;
  CellMovementInput zeroDirection = validInput();
  zeroDirection.cameraRay.direction[2] = 0.0F;
  CellMovementInput nanOrigin = validInput();
  nanOrigin.cameraRay.origin[0] = nan;

  const CellMovementInput invalidInputs[] = {
      negativeTime, nanTime,    infiniteTime, nanNormal,
      infinitePoint, zeroNormal, zeroDirection, nanOrigin,
  };
  bool allRejected = true;
  for (const CellMovementInput &input : invalidInputs) {
    const CellMovementResult result =
        applyCellMovement(pool, 0, lifecycle, input, resolver);
    allRejected = allRejected &&
                  result.status == CellMovementStatus::invalidInput &&
                  !result.targetUpdated && !result.orientationUpdated &&
                  !result.movingStateUpdated;
  }
  check(allRejected && resolver.calls == 0 &&
            near3(target->mTargetPosition, oldPosition) &&
            near3(target->mTargetOrientation, oldOrientation) &&
            lifecycle.moving && lifecycle.ownerIndex == 77,
        "invalid time ray and plane values preserve all movement state");

  CellMovementInput zeroTime = validInput();
  zeroTime.deltaTime = 0.0F;
  const CellMovementResult zeroTimeResult =
      applyCellMovement(pool, 0, lifecycle, zeroTime, resolver);
  check(zeroTimeResult.status == CellMovementStatus::updated &&
            resolver.calls == 1 && near(resolver.lastDeltaTime, 0.0F),
        "zero deltaTime is valid movement input");
}

void testOrientationFailuresAreAtomic() {
  Resolver resolver;
  cObjectPool<cCellObjectData> pool;
  pool.initialize(1);
  cCellObjectData *target = pool.allocate();
  if (target == nullptr) {
    check(false, "orientation failure test allocates target");
    return;
  }

  const float oldPosition[3] = {7.0F, 8.0F, 9.0F};
  const float oldOrientation[4] = {0.2F, 0.3F, 0.4F, 0.5F};
  for (int i = 0; i < 3; ++i) {
    target->mTargetPosition[i] = oldPosition[i];
  }
  for (int i = 0; i < 4; ++i) {
    target->mTargetOrientation[i] = oldOrientation[i];
  }
  CellMovementLifecycle lifecycle;
  lifecycle.moving = true;
  lifecycle.ownerIndex = 77;

  resolver.resolution.status = OrientationResolutionStatus::unresolved;
  CellMovementResult result =
      applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  check(result.status == CellMovementStatus::unresolved && result.targetHit &&
            !result.targetUpdated && !result.orientationUpdated &&
            !result.movingStateUpdated,
        "unresolved orientation is explicit and non-mutating");

  resolver.resolution.status = OrientationResolutionStatus::invalidInput;
  result = applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  check(result.status == CellMovementStatus::invalidOrientation &&
            !result.targetUpdated && !result.orientationUpdated,
        "invalid orientation status is explicit and non-mutating");

  resolveOrientation(resolver);
  resolver.resolution.orientation[2] =
      std::numeric_limits<float>::quiet_NaN();
  result = applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  check(result.status == CellMovementStatus::invalidOrientation &&
            !result.targetUpdated,
        "nonfinite orientation value is invalid and non-mutating");

  resolver.resolution.orientation[0] = 0.0F;
  resolver.resolution.orientation[1] = 0.0F;
  resolver.resolution.orientation[2] = 0.0F;
  resolver.resolution.orientation[3] = 0.0F;
  result = applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  check(result.status == CellMovementStatus::invalidOrientation &&
            !result.targetUpdated,
        "zero orientation quaternion is invalid and non-mutating");

  check(near3(target->mTargetPosition, oldPosition) &&
            near3(target->mTargetOrientation, oldOrientation) &&
            lifecycle.moving && lifecycle.ownerIndex == 77,
        "all orientation failures preserve target and prior lifecycle");
}

void testPoolAndRouteGuards() {
  Resolver resolver;
  resolveOrientation(resolver);
  Router router;
  router.value = validInput();
  cObjectPool<cCellObjectData> pool;
  pool.initialize(1);
  cCellObjectData *target = pool.allocate();
  check(target != nullptr, "pool guard test allocates target");
  if (target == nullptr) {
    return;
  }
  CellMovementLifecycle lifecycle;

  const CellMovementResult outOfRange =
      applyCellMovement(pool, 1, lifecycle, validInput(), resolver);
  const CellMovementResult invalidIndex = applyCellMovement(
      pool, cObjectPool<cCellObjectData>::kInvalidIndex, lifecycle,
      validInput(), resolver);
  const CellMovementResult invalidRoute = routeCellMovement(
      pool, cObjectPool<cCellObjectData>::kInvalidIndex, lifecycle, router,
      resolver);
  check(outOfRange.status == CellMovementStatus::invalidInput &&
            invalidIndex.status == CellMovementStatus::invalidInput &&
            invalidRoute.status == CellMovementStatus::invalidInput &&
            resolver.calls == 0 && router.calls == 0 &&
            !lifecycle.moving,
        "invalid pool indices reject apply and route without mutation");

  const CellMovementResult routed =
      routeCellMovement(pool, 0, lifecycle, router, resolver);
  check(routed.status == CellMovementStatus::updated && router.calls == 1 &&
            lifecycle.moving && lifecycle.ownerIndex == 0,
        "route path commits pool target and lifecycle together");

  Router unavailable;
  unavailable.available = false;
  const float oldPosition[3] = {target->mTargetPosition[0],
                                target->mTargetPosition[1],
                                target->mTargetPosition[2]};
  const CellMovementResult rejected =
      routeCellMovement(pool, 0, lifecycle, unavailable, resolver);
  check(rejected.status == CellMovementStatus::invalidInput &&
            unavailable.calls == 1 && !rejected.targetUpdated &&
            near3(target->mTargetPosition, oldPosition) &&
            lifecycle.moving && lifecycle.ownerIndex == 0,
        "router rejection preserves target and prior lifecycle");

  check(pool.release(target), "pool releases movement target");
  const CellMovementResult freed =
      applyCellMovement(pool, 0, lifecycle, validInput(), resolver);
  check(freed.status == CellMovementStatus::invalidInput &&
            lifecycle.moving && lifecycle.ownerIndex == 0,
        "freed pool target is rejected without lifecycle mutation");
}

void testCellGameHostIntegration() {
  CellGame game;
  const CellGameConfig config{1, 1.0F};
  check(static_cast<bool>(game.initialize(config)),
        "CellGame initializes host integration");
  const float initialPosition[3] = {1.0F, 2.0F, 3.0F};
  const uint32_t targetIndex = game.createCellObject(
      CellResourceSpec{}, initialPosition, 0.0F, CellStageScale::None, 1.0F,
      1.0F, false, nullptr);
  check(targetIndex == 0 && game.isAllocated(targetIndex),
        "CellGame creates pool-backed movement owner");

  Resolver resolver;
  resolveOrientation(resolver);
  Router router;
  router.value = validInput();
  const CellMovementResult result =
      game.routeCellMovement(targetIndex, router, resolver);
  cCellObjectData *target = game.lookup(targetIndex);
  check(target != nullptr && result.status == CellMovementStatus::updated &&
            result.targetUpdated && result.orientationUpdated &&
            result.movingStateUpdated && near3(target->mTargetPosition,
                                                result.hit) &&
            game.mMovementState.moving && game.mMovementState.ownerIndex == 0,
        "CellGame production path reaches pool-backed movement contract");

  resolver.resolution.status = OrientationResolutionStatus::invalidInput;
  const CellMovementResult rejected =
      game.applyCellMovement(targetIndex, validInput(), resolver);
  check(rejected.status == CellMovementStatus::invalidOrientation &&
            !rejected.targetUpdated && game.mMovementState.moving &&
            game.mMovementState.ownerIndex == 0,
        "CellGame production path preserves atomic lifecycle on failure");

  check(static_cast<bool>(game.reset()), "CellGame reset completes");
  check(!game.mMovementState.moving &&
            game.mMovementState.ownerIndex ==
                cObjectPool<cCellObjectData>::kInvalidIndex,
        "CellGame lifecycle clears movement owner");

  CellGame uninitialized;
  const CellMovementResult uninitializedResult =
      uninitialized.routeCellMovement(0, router, resolver);
  check(uninitializedResult.status == CellMovementStatus::invalidInput,
        "uninitialized CellGame rejects production movement");
}

}

int main() {
  testValidTargetAndLifecycle();
  testObliquePlane();
  testIntersectionBoundary();
  testInvalidInputsAreAtomic();
  testOrientationFailuresAreAtomic();
  testPoolAndRouteGuards();
  testCellGameHostIntegration();
  if (g_failures == 0) {
    std::printf("cellmovement_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellmovement_test: %d FAILURES\n", g_failures);
  return 1;
}
