// Reconstruction of 0x0043cad0 - a state-propagation sweep over the handle set
// of one editor part.
//
// Complete body, 251 instructions, 0x0043cad0..0x0043cdf5, read live. Frame
// PUSH EBP / MOV EBP,ESP / SUB ESP,0x78, receiver spilled to [EBP-0x68], bare
// RET, so void and no stack arguments.
//
// Receiver layout, every offset proved by a named instruction in the body:
//
//   +0x028  pointer to a sub-object; only its two flag bytes are read, through
//           the accessor pair 0x004adb80 (+0x4C) and 0x004adbc0 (+0x4D)
//   +0x154  handle slot 0        +0x158 handle slot 1        +0x15C handle slot 2
//   +0x160  handle slot 3
//   +0x1B0  int32 exclusion index
//   +0x6CC  pointer-array begin  +0x6D0 pointer-array end
//   +0xDC8  64-bit attribute bitset, only bits 25, 24 and 11 are tested
//
// Every handle is reached through vtable slot +0x30 and called with the two
// immediates 3 and 1, in that stack order, i.e. func30h(state, true). The bit
// tests are the compiler's expansion of a bounds-checked bit read: the
// CMP imm,0x3c / JNC pair yields 0 for any index at or above 64, which is why
// 0x0043cb5e, 0x0043cc91 and 0x0043cd02 are the three `false` arms.
#pragma once

#include <cstdint>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

// The receiver. The two handle arrays are modelled as raw ranges because the
// body only walks them by (end - begin) >> 2 and never reallocates.
struct RigblockHandleSweep_0043cad0 {
    void* model;                     // +0x028 sub-object with two flag bytes
    void* axis_handles[3];           // +0x154
    void* rotation_ball_handle;      // +0x160
    std::int32_t exclusion_index;    // +0x1B0
    std::int32_t* morph_begin;        // +0x6CC
    std::int32_t* morph_end;          // +0x6D0
    std::uint32_t attributes_lo;      // +0xDC8 low dword, bits 0..31
    std::uint32_t attributes_hi;      // +0xDC8 high dword, bits 32..63
};

// Ports. The three accessor/visitor functions are named after what they were
// observed to do, not after anything the binary proves they are called.
extern "C" std::uint8_t __attribute__((thiscall))
PORT_sub_object_flag_4c_004adb80(const void* sub_object);
extern "C" std::uint8_t __attribute__((thiscall))
PORT_sub_object_flag_4d_004adbc0(const void* sub_object);
extern "C" void __attribute__((thiscall))
PORT_sweep_unselected_0043ce40(RigblockHandleSweep_0043cad0* self);
extern "C" void __attribute__((thiscall))
PORT_handle_set_state_0044ae00(void* handle, int state, bool toggle);
extern "C" void __attribute__((thiscall)) PORT_marker_004a88d0(std::uint32_t tag);

extern "C" void __attribute__((thiscall)) FUN_0043cad0_propagate_handle_state(
    RigblockHandleSweep_0043cad0* self);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
