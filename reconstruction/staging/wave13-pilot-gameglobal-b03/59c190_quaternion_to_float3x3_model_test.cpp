// Standalone model test for reconstruction/staging/wave13-pilot-gameglobal-b03/
// 59c190_quaternion_to_float3x3.{hpp,cpp}.
//
// Build and run:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//       -I reconstruction/staging/wave13-pilot-gameglobal-b03 \
//       reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3.cpp
//       \
//       reconstruction/staging/wave13-pilot-gameglobal-b03/59c190_quaternion_to_float3x3_model_test.cpp
//       \ -o /tmp/opencode/59c190-model && /tmp/opencode/59c190-model
//
// The port below is a TEST DOUBLE for 0x0041cb40, whose body was read in full
// (three 12-byte float3 block copies, __thiscall, RET 0x4, returns `this`). It
// is not a reconstruction of that function, which belongs to another package.

#include "59c190_quaternion_to_float3x3.hpp"

#include <cmath>
#include <cstdio>

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

// Test double for 0x0041cb40: the observed body copies source +0x00, +0x0c and
// +0x18 (each a 12-byte float3 block) to this +0x00, +0x0c, +0x18, reads no
// part of the previous destination value, and returns `this`.
extern "C" Opaque59c190Float3x3* OpaquePort_0041cb40_assign_float3x3(
    Opaque59c190Float3x3* self, const Opaque59c190Float3x3* src) {
  for (int block = 0; block < 3; ++block) {
    const std::size_t base = static_cast<std::size_t>(block) * 3;
    for (int i = 0; i < 3; ++i) {
      self->m[base + i] = src->m[base + i];
    }
  }
  return self;
}

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03

namespace {

using openspore::reconstruction::wave13_pilot_gameglobal_b03::
    GameGlobal_0059c190_quaternion_to_float3x3;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::
    Opaque59c190Float3x3;

int g_failures = 0;

void ExpectNear(const char* what, float got, float want) {
  const float kTol = 1.0e-6f;
  if (!(std::fabs(got - want) <= kTol)) {
    std::printf("FAIL %-6s got % .7f want % .7f\n", what, got, want);
    ++g_failures;
  }
}

void Expect(const char* what, bool ok) {
  if (!ok) {
    std::printf("FAIL %s\n", what);
    ++g_failures;
  }
}

// The flat 9-float block is three consecutive 12-byte float3 groups. Group k
// (m[3k .. 3k+2]) is the image of the k-th basis vector under the rotation, so
// M * v applies the rotation to a column vector.
void ExpectColumn(const char* what, const Opaque59c190Float3x3& m, int column,
                  float ex, float ey, float ez) {
  const int b = column * 3;
  ExpectNear(what, m.m[b + 0], ex);
  ExpectNear(what, m.m[b + 1], ey);
  ExpectNear(what, m.m[b + 2], ez);
}

}  // namespace

int main() {
  Opaque59c190Float3x3 dest;

  // 1. Identity quaternion (0,0,0,1) must give the identity matrix.
  const float kIdentity[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Opaque59c190Float3x3* ret =
      GameGlobal_0059c190_quaternion_to_float3x3(&dest, kIdentity);
  Expect("ret-ptr", ret == &dest);
  ExpectColumn("ident", dest, 0, 1.0f, 0.0f, 0.0f);
  ExpectColumn("ident", dest, 1, 0.0f, 1.0f, 0.0f);
  ExpectColumn("ident", dest, 2, 0.0f, 0.0f, 1.0f);

  // 2. +90 degrees about Z: (0,0,sin45,cos45) sends (1,0,0) -> (0,1,0) and
  //    (0,1,0) -> (-1,0,0).
  const float kS = 0.70710678f;
  const float kQuatZ90[4] = {0.0f, 0.0f, kS, kS};
  GameGlobal_0059c190_quaternion_to_float3x3(&dest, kQuatZ90);
  ExpectColumn("z90", dest, 0, 0.0f, 1.0f, 0.0f);
  ExpectColumn("z90", dest, 1, -1.0f, 0.0f, 0.0f);
  ExpectColumn("z90", dest, 2, 0.0f, 0.0f, 1.0f);

  // 3. +90 degrees about X: (sin45,0,0,cos45) sends (0,1,0) -> (0,0,1).
  const float kQuatX90[4] = {kS, 0.0f, 0.0f, kS};
  GameGlobal_0059c190_quaternion_to_float3x3(&dest, kQuatX90);
  ExpectColumn("x90", dest, 0, 1.0f, 0.0f, 0.0f);
  ExpectColumn("x90", dest, 1, 0.0f, 0.0f, 1.0f);
  ExpectColumn("x90", dest, 2, 0.0f, -1.0f, 0.0f);

  // 4. +90 degrees about Y: (0,sin45,0,cos45) sends (0,0,1) -> (1,0,0).
  const float kQuatY90[4] = {0.0f, kS, 0.0f, kS};
  GameGlobal_0059c190_quaternion_to_float3x3(&dest, kQuatY90);
  ExpectColumn("y90", dest, 0, 0.0f, 0.0f, -1.0f);
  ExpectColumn("y90", dest, 1, 0.0f, 1.0f, 0.0f);
  ExpectColumn("y90", dest, 2, 1.0f, 0.0f, 0.0f);

  // 5. No normalisation happens. Scaling the quaternion by 2 scales the
  //    off-diagonal terms by 4 while the diagonal keeps its 1.0f seed, so
  //    m[1] is 4 where a normalising implementation would give 1.
  const float kScaled[4] = {0.0f, 0.0f, 2.0f * kS, 2.0f * kS};
  GameGlobal_0059c190_quaternion_to_float3x3(&dest, kScaled);
  ExpectNear("no-norm", dest.m[1], 4.0f);
  ExpectNear("no-norm", dest.m[8], 1.0f);

  // 6. The diagonal form 1 - 2*(z*z + y*y) and the antisymmetric pairing of
  //    the off-diagonals are both observable; pin the exact terms.
  const float kQ[4] = {0.1f, 0.2f, 0.3f, 0.4f};
  GameGlobal_0059c190_quaternion_to_float3x3(&dest, kQ);
  const float xx = 0.01f, yy = 0.04f, zz = 0.09f;
  ExpectNear("terms", dest.m[0], 1.0f - (zz + yy) * 2.0f);
  ExpectNear("terms", dest.m[1], (0.4f * 0.3f + 0.1f * 0.2f) * 2.0f);
  ExpectNear("terms", dest.m[2], (0.1f * 0.3f - 0.4f * 0.2f) * 2.0f);
  ExpectNear("terms", dest.m[3], (0.1f * 0.2f - 0.3f * 0.4f) * 2.0f);
  ExpectNear("terms", dest.m[4], 1.0f - (zz + xx) * 2.0f);
  ExpectNear("terms", dest.m[5], (0.1f * 0.4f + 0.3f * 0.2f) * 2.0f);
  ExpectNear("terms", dest.m[6], (0.4f * 0.2f + 0.3f * 0.1f) * 2.0f);
  ExpectNear("terms", dest.m[7], (0.3f * 0.2f - 0.4f * 0.1f) * 2.0f);
  ExpectNear("terms", dest.m[8], 1.0f - (xx + yy) * 2.0f);

  if (g_failures == 0) {
    std::printf("59c190 model test: OK\n");
    return 0;
  }
  std::printf("59c190 model test: %d failure(s)\n", g_failures);
  return 1;
}
