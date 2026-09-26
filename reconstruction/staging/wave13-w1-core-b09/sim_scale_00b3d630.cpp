// 0x00b3d630 - effective scale / extent factor of a Simulator object.
//
// Body span 0x00b3d630..0x00b3d695, 102 bytes, 36 instructions, all read from
// the live disassembly. ABI: __thiscall, receiver in ECX, no stack arguments,
// bare RET, result returned on the x87 stack in ST(0) (FLD / FMUL, never FSTP).
//
// Order of operations, as observed:
//   1. spill 8 bytes of frame, save ESI, ESI = ECX
//   2. XMM1 = this->field_18 ; compare XMM1 against 0.0f (COMISS)
//   3. JBE (CF|ZF, i.e. "<= 0.0 or unordered") leaves the fast path, so the fast
//      path runs only when field_18 > 0.0f in an ordered comparison
//   4. fast path: FLD the spilled field_18 and return it verbatim
//   5. slow path: switch on this->selector_04
//        0 and 1 -> scale = source_40->vtable[0x70]()  (ST(0) float)
//        2       -> scale = source_40->cached_point[2] (the z float at +0x44)
//        other   -> scale stays the 0.0f that was spilled before the switch
//   6. FMUL by this->multiplier_10 and return the product in ST(0)
//
// Classification BOUNDED_SEMANTIC: the body is complete, but the owning class
// and the type behind receiver+0x40 are not established.

#include "sim_scale_00b3d630.hpp"

extern "C" B09_THISCALL float SimScale_00b3d630_reconstruct(OpaqueScaleOwnerObserved* self) {
    const float cached = self->cached_scale_18;

    // 0x00b3d63e COMISS XMM1,XMM0 followed by 0x00b3d64d JBE. The branch is
    // taken when cached <= 0.0f or when the comparison is unordered, so the
    // early return below is only reachable for an ordered cached > 0.0f.
    if (!(cached <= 0.0f)) {
        return cached;  // 0x00b3d64f FLD float ptr [ESP + 0x8]
    }

    // 0x00b3d641 spilled 0.0f to [ESP + 0x4] before the switch, and neither
    // the 0/1 arm nor the default arm overwrites it.
    float scale = 0.0f;

    // 0x00b3d658..0x00b3d668: SUB EAX,0 / JZ / SUB EAX,1 / JZ / SUB EAX,1 / JNZ.
    // Values 0 and 1 share one arm; 2 is the only other handled value.
    switch (self->selector_04) {
        case kScaleSelectorVirtual:
        case 1u: {
            // 0x00b3d684: ECX = source_40, EDX = [ECX], EAX = [EDX + 0x70],
            // CALL EAX. The result arrives in ST(0) and is left there.
            scale = opaque_ScaleSource_slot_0x70(self->source_40);
            break;
        }
        case kScaleSelectorCachedZ:
            // 0x00b3d66a: EAX = source_40 ; 0x00b3d66d: MOVSS XMM0,[EAX + 0x44]
            scale = self->source_40->cached_point[2];
            break;
        default:
            break;
    }

    // 0x00b3d67c FMUL float ptr [ESI + 0x10]
    return scale * self->multiplier_10;
}
