#include "59c190_quaternion_to_float3x3.hpp"

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

const float kG59c190OneF = 1.0f;  // .rdata 0x01485720 -> 00 00 80 3f
const float kG59c190TwoF = 2.0f;  // .rdata 0x01470f1c -> 00 00 00 40

// 0x0059c190, read in full from program="SporeApp.exe":
// 0x0059c190..0x0059c2e6, 79 instructions, 343 bytes, then cc padding from
// 0x0059c2e7. Frame: SUB ESP,0x30 + PUSH ESI; no other callee-save.
//
//   0x0059c190  sub  esp, 0x30
//   0x0059c193  push esi
//   0x0059c194  mov  eax, [esp+0x3c]      ; stack arg 1: the quaternion
//   0x0059c198  movss xmm0, [eax+0x00]   ; a = q.x
//   0x0059c19c  movss xmm6, [eax+0x04]   ; b = q.y
//   0x0059c1a1  movss xmm7, [eax+0x08]   ; c = q.z
//   0x0059c1a6  movss xmm5, [eax+0x0c]   ; d = q.w
//   ... 9 MOVSS stores into the local 36-byte block at [esp+0x10] ...
//   0x0059c2a4  lea  eax, [esp+0x10]      ; &local
//   0x0059c2c0  push eax
//   0x0059c2c1  mov  ecx, esi            ; esi = stack arg 0, the destination
//   0x0059c2db  call 0x0041cb40           ; dest = local
//   0x0059c2e0  mov  eax, esi            ; return the destination
//   0x0059c2e2  pop  esi
//   0x0059c2e3  add  esp, 0x30
//   0x0059c2e6  ret                      ; bare RET: __cdecl, no callee cleanup
//
// The nine stored floats, with the instruction that stores each one. The block
// is three 12-byte float3 groups (offsets 0x00, 0x0c, 0x18), which is what
// 0x0041cb40 copies.
//
//   [esp+0x10] M[0]  0x0059c22d   1.0f - (z*z + y*y) * 2.0f
//   [esp+0x14] M[1]  0x0059c23e   (w*z + x*y) * 2.0f
//   [esp+0x18] M[2]  0x0059c262   (x*z - w*y) * 2.0f
//   [esp+0x1c] M[3]  0x0059c26c   (x*y - z*w) * 2.0f
//   [esp+0x20] M[4]  0x0059c28f   1.0f - (z*z + x*x) * 2.0f
//   [esp+0x24] M[5]  0x0059c2c3   (x*w + z*y) * 2.0f
//   [esp+0x28] M[6]  0x0059c2c9   (w*y + z*x) * 2.0f
//   [esp+0x2c] M[7]  0x0059c2cf   (z*y - w*x) * 2.0f
//   [esp+0x30] M[8]  0x0059c2d5   1.0f - (x*x + y*y) * 2.0f
//
// That is the textbook unit-quaternion rotation matrix stored so that M*v
// applies the rotation to a column vector: M[0..2] is the image of (1,0,0),
// M[3..5] the image of (0,1,0), M[6..8] the image of (0,0,1). No normalisation
// and no length test of the input appears anywhere in the body, so a
// non-unit quaternion yields the unnormalised formula result.
//
// Scratch traffic the body performs and this reconstruction does not need to
// reproduce literally, recorded so the offsets are not mistaken for fields:
//   0x0059c1b9  movss [esp+0x04],xmm5  ; d spilled to the frame
//   0x0059c1e4  movss [esp+0x08],xmm1  ; x*x
//   0x0059c1f1  movss [esp+0x0c],xmm5  ; w*x
//   0x0059c1d7  movss [esp+0x3c],xmm4  ; x*z spilled into the caller's
//                                      ; already-consumed argument slot
extern "C" Opaque59c190Float3x3* GameGlobal_0059c190_quaternion_to_float3x3(
    Opaque59c190Float3x3* dest, const float* quat_xyzw) {
  const float x = quat_xyzw[0];
  const float y = quat_xyzw[1];
  const float z = quat_xyzw[2];
  const float w = quat_xyzw[3];

  // Squares are computed once and reused: xmm2 = z*z (0x0059c1b1),
  // xmm1 = y*y (0x0059c1ed), xmm6 = x*x (0x0059c1cd).
  const float xx = x * x;
  const float yy = y * y;
  const float zz = z * z;

  Opaque59c190Float3x3 local;

  local.m[0] = kG59c190OneF - (zz + yy) * kG59c190TwoF;  // 0x0059c223
  local.m[1] = (w * z + x * y) * kG59c190TwoF;           // 0x0059c23a
  local.m[2] = (x * z - w * y) * kG59c190TwoF;  // 0x0059c24a/0x0059c254
  local.m[3] = (x * y - z * w) * kG59c190TwoF;  // 0x0059c258/0x0059c268
  local.m[4] = kG59c190OneF - (zz + xx) * kG59c190TwoF;  // 0x0059c285
  local.m[5] = (x * w + z * y) * kG59c190TwoF;  // 0x0059c29c/0x0059c2b0
  local.m[6] = (w * y + z * x) * kG59c190TwoF;  // 0x0059c24e/0x0059c2b4
  local.m[7] = (z * y - w * x) * kG59c190TwoF;  // 0x0059c2a8/0x0059c2b8
  local.m[8] =
      kG59c190OneF - (xx + yy) * kG59c190TwoF;  // 0x0059c2a0/0x0059c2bc

  // 0x0059c2c0..0x0059c2db: the local is copied into the destination through
  // the 36-byte port, then the destination pointer is returned.
  OpaquePort_0041cb40_assign_float3x3(dest, &local);
  return dest;
}

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03
