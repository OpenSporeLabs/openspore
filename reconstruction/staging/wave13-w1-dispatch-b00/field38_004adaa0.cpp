#include "field38_004adaa0.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// 0x004adaa0 -- 17 bytes, 9 instructions, read live.
//
//   0x004adaa0  55           push ebp
//   0x004adaa1  8bec         mov  ebp, esp
//   0x004adaa3  51           push ecx
//   0x004adaa4  894d fc      mov  dword ptr [ebp - 4], ecx
//   0x004adaa7  8b45 fc      mov  eax, dword ptr [ebp - 4]
//   0x004adaaa  d940 38      fld  float ptr [eax + 0x38]
//   0x004adaad  8be5         mov  esp, ebp
//   0x004adaaf  5d           pop  ebp
//   0x004adab0  c3           ret
//
// Live bytes: 55 8b ec 51 89 4d fc 8b 45 fc d9 40 38 8b e5 5d c3, then
// cc padding to 0x004adac0 where the next accessor starts.
//
// The whole contract is one load. `fld float ptr [eax + 0x38]` pushes the
// single-precision value at receiver + 0x38 onto the x87 stack and ST0 is the
// return; there is no null check on the receiver, so a null or dangling
// receiver faults at 0x004adaaa exactly as in the original. The frame exists
// only to spill ECX; no register is saved and restored, and the RET has no
// immediate, so the caller owns all stack cleanup.
//
// The float reading is corroborated by the accessor at 0x004ada80, which is
// byte-for-byte the mirror image and writes the same offset with MOVSS:
//
//   0x004ada8a  f30f1145 08  movss xmm0, dword ptr [ebp + 8]
//   0x004ada8f  f30f1141 38  movss dword ptr [eax + 0x38], xmm0
//   0x004ada97  c204        ret 4
//
// 0x004adac0 and 0x004adae0 are the same shape for +0x3c and +0x40 (plain
// dword stores, so those two are NOT proven to be floats).
//
// Every inspected call site loads the receiver out of a sub-object at +0x28
// of the caller's own argument and consumes ST0 as a float:
//   0x004a0777  8b5128       mov edx, dword ptr [ecx + 0x28]
//   0x004a0780  e81bd30000   call 0x004adaa0
//   0x004a0785  d835d8ec3e01 fdiv float ptr [0x013eecd8]   ; divisor 20.0f
//   0x004a078b  d95dfc       fstp dword ptr [ebp - 4]
// and 0x0043e43a does the same then multiplies by the float at 0x013eb960.
// The owning type is not established: no vtable for it was located and the
// ModAPI headers have no class with a float at +0x38 that these 26 callers
// resolve to.

extern "C" float __thiscall FUN_004adaa0_reconstruct(
    Opaque4adaa0Float38Owner* self) {
  // The +0x38 load is unguarded, exactly as in the original. Spelling it as a
  // reinterpret_cast keeps the fault-on-null behaviour instead of inventing
  // a defensive check the binary does not have.
  return *reinterpret_cast<const float*>(reinterpret_cast<const std::uint8_t*>(
                                             self) +
                                         0x38);
}

extern "C" void __thiscall FUN_004ada80_reconstruct(
    Opaque4adaa0Float38Owner* self,
    float value) {
  *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(self) + 0x38) =
      value;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
