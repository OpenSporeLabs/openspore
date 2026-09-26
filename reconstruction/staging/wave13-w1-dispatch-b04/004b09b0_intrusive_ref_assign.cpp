#include "004b09b0_intrusive_ref_assign.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

extern "C" IntrusiveRefHolder_004b09b0* FUN_004b09b0_assign(
    IntrusiveRefHolder_004b09b0* self, RefCountedPointee_004b09b0* incoming) {
    // 0x004b09bf: CMP ECX,[EAX] / JZ 0x004b09f9 - assigning the value that is
    // already held is a complete no-op, including the return, which still
    // yields the holder. This is the self-assignment guard.
    if (incoming == self->held) {
        return self;
    }

    // 0x004b09c6..0x004b09c8: copy the outgoing pointer into the frame slot
    // first. The slot is the re-entrancy temporary: if the release at
    // 0x004b09f7 runs a destructor that writes back through this holder, the
    // store at 0x004b09e4 has already happened and the temporary is still
    // the pre-store value.
    RefCountedPointee_004b09b0* const outgoing = self->held;

    // 0x004b09cb..0x004b09dc: acquire the incoming pointer BEFORE it is
    // stored, so the object is kept alive across the store.
    if (incoming != nullptr) {
        PORT_pointee_acquire_004b09b0(incoming);
    }

    // 0x004b09de..0x004b09e4: publish the new value.
    self->held = incoming;

    // 0x004b09e6..0x004b09f7: drop the outgoing reference AFTER the store.
    // Only the non-null case calls; the null case falls straight to the
    // return.
    if (outgoing != nullptr) {
        PORT_pointee_release_004b09b0(outgoing);
    }

    // 0x004b09f9: return this, not the incoming pointer.
    return self;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
