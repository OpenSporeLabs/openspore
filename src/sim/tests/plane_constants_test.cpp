// CS-01: the cell-stage movement-plane constants pinned from the original
// binary (SporeApp.exe 3.1.0.22, GOG). Evidence:
//   - normal: section .data, image 0x015a7c40/44/48 (file offset 0x11a6640)
//     = {0.0f, 0.0f, 1.0f} — VERIFIED static read.
//   - point: image 0x016b3c28/2c/30 sits in BSS (zero in the static image,
//     written at runtime, per-world) — load-time {0,0,0}.
// The MovementPlane defaults in Sim.hpp must equal exactly these values.
// Pure C++ + stdlib; CI-safe.
#include <cmath>
#include <cstdio>

#include "Sim.hpp"

namespace {

using openspore::sim::MovementPlane;
using openspore::sim::rayPlaneHit;

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

// The values read from the binary (the pin this test enforces).
constexpr float kNormal[3] = {0.0F, 0.0F, 1.0F};
constexpr float kPoint[3] = {0.0F, 0.0F, 0.0F};

} // namespace

int main() {
  const MovementPlane plane; // defaults under test

  for (int i = 0; i < 3; ++i) {
    check(plane.normal[i] == kNormal[i], "default normal component matches binary read");
    check(plane.point[i] == kPoint[i], "default point component matches BSS load-time value");
  }

  // Behavioral: with the pinned plane (z=0), a straight-down ray at the
  // origin from 12 units above hits exactly the origin (the original's
  // t = dot(n, p-o)/dot(n,d) with t>=0 guard).
  {
    const float origin[3] = {0.0F, 0.0F, 12.0F};
    const float dir[3] = {0.0F, 0.0F, -1.0F};
    float hit[3] = {-1.0F, -1.0F, -1.0F};
    const bool hitOk = rayPlaneHit(origin, dir, plane, hit);
    check(hitOk, "down ray from (0,12,0) hits the z=0 plane");
    check(hit[0] == 0.0F && hit[1] == 0.0F && hit[2] == 0.0F,
          "hit is exactly the origin");
  }

  // A ray parallel to the pinned plane (horizontal) must NOT hit.
  {
    const float origin[3] = {5.0F, 7.0F, 0.0F};
    const float dir[3] = {1.0F, 0.0F, 0.0F};
    float hit[3] = {0.0F, 0.0F, 0.0F};
    check(!rayPlaneHit(origin, dir, plane, hit),
          "horizontal ray is parallel to the plane: no hit");
  }

  if (g_failures == 0) {
    std::printf("plane_constants_test: ALL PASS\n");
    return 0;
  }
  std::printf("plane_constants_test: %d FAILURES\n", g_failures);
  return 1;
}
