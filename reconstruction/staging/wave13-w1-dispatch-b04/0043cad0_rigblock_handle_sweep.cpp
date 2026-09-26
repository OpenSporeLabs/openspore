#include "0043cad0_rigblock_handle_sweep.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

namespace {

// 0x0043cb1a..0x0043cb5c, repeated verbatim for indices 0x19, 0x18 and 0x0b at
// 0x0043cc4d and 0x0043ccbe. Each instance is:
//     if (index >= 0x3c) -> false
//     word = *(uint32_t*)(self + 0xdc8 + (index >> 5) * 4)
//     return (word >> (index & 0x1f)) & 1
// The `index >= 0x3c` arm is the bounds guard of a 64-bit attribute bitset, so
// an out-of-range index reads as clear rather than faulting.
bool TestAttributeBit(const RigblockHandleSweep_0043cad0* self,
                      std::uint32_t index) {
    if (index >= 0x3cu) {
        return false;
    }
    const std::uint32_t word = (index < 0x20u) ? self->attributes_lo
                                               : self->attributes_hi;
    return ((word >> (index & 0x1fu)) & 1u) != 0u;
}

}  // namespace

extern "C" void __attribute__((thiscall)) FUN_0043cad0_propagate_handle_state(
    RigblockHandleSweep_0043cad0* self) {
    // 0x0043cad9 / 0x0043cadd: two single-byte locals, both cleared first.
    bool all_handles = false;  // [EBP-2]
    bool all_morphs = false;   // [EBP-1]

    // 0x0043cae4: the whole feature is gated on the sub-object being present.
    if (self->model != nullptr) {
        all_handles = PORT_sub_object_flag_4c_004adb80(self->model) != 0;
        all_morphs = PORT_sub_object_flag_4d_004adbc0(self->model) != 0;
    }

    // 0x0043cb06: the "did anything happen" latch, set at every dispatch.
    bool dispatched = false;

    // 0x0043cb0a..0x0043cb15: when the sub-object exists and its +0x4C flag
    // is clear, hand the complementary half of the sweep to 0x0043ce40, which
    // walks the same handle set and calls slot +0x30 with (1, 1).
    if (!all_handles) {
        PORT_sweep_unselected_0043ce40(self);
    }

    // 0x0043cb1a: bit 25 set disables the four named handle slots outright.
    if (!TestAttributeBit(self, 0x19u)) {
        // 0x0043cb6e..0x0043cbf3: the three axis handles, index-compounded at
        // +0x154 + i*4 with the loop bound fixed at 3.
        for (std::uint32_t i = 0; i < 3u; ++i) {
            const std::uintptr_t handle =
                reinterpret_cast<std::uintptr_t>(self->axis_handles[i]);
            // 0x0043cb96: null slots are skipped, not dereferenced.
            if (handle == 0u) {
                continue;
            }
            // 0x0043cbaf: each axis handle carries its own "leave me alone"
            // byte at handle+0x92.
            const std::uint8_t pinned = *reinterpret_cast<const std::uint8_t*>(
                handle + 0x92u);
            // 0x0043cbbc / 0x0043cbc0: skip only when the byte is set AND the
            // override flag is clear. An override visits every handle.
            if (pinned != 0u && !all_handles) {
                continue;
            }
            // 0x0043cbde: PUSH 1 then PUSH 3, so the call is (3, 1).
            PORT_handle_set_state_0044ae00(reinterpret_cast<void*>(handle), 3,
                                           true);
            dispatched = true;
        }

        // 0x0043cbf5..0x0043cc49: the rotation-ball handle at +0x160, whose
        // "leave me alone" byte is at +0x5D rather than +0x92.
        const std::uintptr_t ball =
            reinterpret_cast<std::uintptr_t>(self->rotation_ball_handle);
        if (ball != 0u) {
            const std::uint8_t pinned = *reinterpret_cast<const std::uint8_t*>(
                ball + 0x5du);
            if (pinned == 0u || all_handles) {
                PORT_handle_set_state_0044ae00(
                    reinterpret_cast<void*>(ball), 3, true);
                dispatched = true;
            }
        }
    }

    // 0x0043cc4d: bit 24 set disables the morph-handle sweep.
    if (!TestAttributeBit(self, 0x18u)) {
        // 0x0043ccc2..0x0043cd24: when bit 11 is set and the +0x4D override is
        // clear, one index is excluded. Note the polarity: the exclusion is
        // installed only when BOTH conditions hold, otherwise the index is
        // -1 and no element matches it.
        std::int32_t excluded = -1;
        if (TestAttributeBit(self, 0x0bu) && !all_morphs) {
            excluded = self->exclusion_index;
        }

        // 0x0043cd3b..0x0043cd51: element count is (end - begin) >> 2, i.e.
        // the end pointer is not dereferenced and the count is signed.
        const std::int32_t count = static_cast<std::int32_t>(
            (reinterpret_cast<std::intptr_t>(self->morph_end) -
             reinterpret_cast<std::intptr_t>(self->morph_begin)) >>
            2);
        const std::int32_t* const base = self->morph_begin;

        // 0x0043cd31..0x0043cdd8.
        for (std::int32_t i = 0; i < count; ++i) {
            if (i == excluded) {
                continue;
            }
            const std::uintptr_t handle = static_cast<std::uintptr_t>(base[i]);
            // 0x0043cd8e: morph handles carry the byte at +0x1D4.
            const std::uint8_t pinned = *reinterpret_cast<const std::uint8_t*>(
                handle + 0x1D4u);
            if (pinned != 0u && !all_handles) {
                continue;
            }
            PORT_handle_set_state_0044ae00(reinterpret_cast<void*>(handle), 3,
                                           true);
            dispatched = true;
        }
    }

    // 0x0043cddd..0x0043cdef: the marker fires once, and only if at least one
    // handle was actually visited. Its argument is the immediate 0xD0A55625.
    if (dispatched) {
        PORT_marker_004a88d0(0xD0A55625u);
    }
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
