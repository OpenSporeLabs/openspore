#include "007b86e0_object_release.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

extern "C" std::int32_t __attribute__((thiscall)) FUN_007b86e0_release(
    RefCountedObject_007b86e0* self) {
    // 0x007b86e0..0x007b86e6: read the count, bias the receiver to the
    // embedded sub-object, decrement in a register.
    const std::int32_t remaining = self->ref_count - 1;
    self->ref_count = remaining;

    // 0x007b86ec: JNZ 0x007b86ff - the common exit returns the new count in
    // EAX, which the decrement above already left there.
    if (remaining != 0) {
        return remaining;
    }

    // 0x007b86ee: the count is put back to 1 BEFORE the destructor runs, so a
    // re-entrant Release issued from inside the destruction observes a live
    // count of 1 and takes the same branch instead of recursing.
    self->ref_count = 1;

    // 0x007b86f5..0x007b86fb: virtual call on the embedded sub-object at
    // owner+0x04, slot +0x00, with the constant 1 as the single stack
    // argument. The receiver is the sub-object address, not a pointer read
    // out of it, which is what fixes the sub-object as embedded at +0x04.
    PORT_embedded_base_deleting_dtor_0041d780(&self->embedded_base, 1u);

    // 0x007b86fd: XOR EAX,EAX - the caller is told the object is gone, which
    // is why every observed callsite discards the result.
    return 0;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
