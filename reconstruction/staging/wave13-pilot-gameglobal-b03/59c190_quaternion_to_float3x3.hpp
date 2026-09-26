#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-pilot-gameglobal-b03 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4,
              "wave13-pilot-gameglobal-b03 requires 32-bit pointers");

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

// 36-byte by-value object that 0x0059c190 fills. The callee at 0x0041cb40
// copies it as three consecutive 12-byte float3 blocks (source +0x00,
// +0x0c, +0x18), so the layout below is the observed one and nothing more is
// claimed about the owning type: SporeApp.exe has no MSVC RTTI and no vtable
// was located for it.
struct Opaque59c190Float3x3 {
  float m[9];
};
static_assert(sizeof(Opaque59c190Float3x3) == 36,
              "0x0059c190 destination is a 36-byte object");

// Opaque port for 0x0041cb40.
//
// Observed with program="SporeApp.exe":
//   0x0041cb40  PUSH EBP / MOV EBP,ESP / SUB ESP,0x30
//   0x0041cb46  MOV dword ptr [EBP - 0x30],ECX        ; receiver saved
//   ... three blocks, each: three MOVSS loads from [src + 0x00|0x04|0x08]
//       through three MOVSS stores to [this + 0x00|0x04|0x08] ...
//   0x0041cb0f  MOV EAX,dword ptr [EBP - 0x30]        ; returns `this`
//   0x0041cb15  RET 0x4
// It is a __thiscall copy-assign of the 36-byte object: three 12-byte float3
// blocks, no read of the old destination value, one stack argument, receiver in
// ECX. It is declared here, not implemented: it is a different function that
// belongs to another package, so this file does not fabricate its body.
extern "C" Opaque59c190Float3x3* OpaquePort_0041cb40_assign_float3x3(
    Opaque59c190Float3x3* self, const Opaque59c190Float3x3* src);

// The two .rdata constants the body loads.
//
//   0x01485720 -> 00 00 80 3f = 1.0f   (0x0059c1fe, 0x0059c272, 0x0059c282)
//   0x01470f1c -> 00 00 00 40 = 2.0f   (0x0059c217)
extern const float kG59c190OneF;  // 0x01485720
extern const float kG59c190TwoF;  // 0x01470f1c

// 0x0059c190 - quaternion -> 3x3 rotation matrix.
//
// Observed ABI (0x0059c190 .. 0x0059c2e6, 79 instructions, bare RET):
//   * no ECX receiver; the first stack argument is the destination / hidden
//     return buffer and the second is a pointer to four consecutive floats
//   * stack arg 0 ([ESP_entry+4]) : destination of the 36-byte result
//   * stack arg 1 ([ESP_entry+8]) : const float[4] = (x, y, z, w)
//   * returns stack arg 0 unchanged in EAX
//     (0x0059c295 MOV ESI,[ESP+0x38]; 0x0059c2e0 MOV EAX,ESI)
//
// `0x0059d788`/`0x0059d78d` and `0x00b818fe`/`0x00b818ff` are two inspected
// call sites and both push the quaternion pointer first and the destination
// second, so the argument order above is the observed one.
extern "C" Opaque59c190Float3x3* GameGlobal_0059c190_quaternion_to_float3x3(
    Opaque59c190Float3x3* dest, const float* quat_xyzw);

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03
