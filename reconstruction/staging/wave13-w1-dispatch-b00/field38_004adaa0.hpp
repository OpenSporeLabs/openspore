#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declaration. Only the single dword at +0x38 is
// evidenced; no other offset of this type is asserted.
struct Opaque4adaa0Float38Owner;

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// 0x004adaa0
//
//   float __thiscall FUN_004adaa0_get(Opaque4adaa0Float38Owner* self);
//
// Observed body, 9 instructions, 17 bytes, 0x004adaa0..0x004adaab0.
// Receiver is ECX, returned in the x87 ST0 register; the frame is torn down
// with a bare RET (no immediate), so the callee pops nothing.
extern "C" float __thiscall FUN_004adaa0_reconstruct(
    Opaque4adaa0Float38Owner* self);

// Sibling accessor observed at 0x004ada80, kept because the pair is what
// establishes the +0x38 field as a float and not a bit pattern.
//   void __thiscall FUN_004ada80_set(Opaque4adaa0Float38Owner*, float);
extern "C" void __thiscall FUN_004ada80_reconstruct(
    Opaque4adaa0Float38Owner* self,
    float value);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
