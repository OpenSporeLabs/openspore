// Reconstruction of 0x0043eed0 - an x87 float field getter.
//
// Complete body, 9 instructions, 0x0043eed0..0x0043eee3, read live
// (558bec 51 894dfc 8b45fc d980d4010000 8be55dc3, then INT3 pad):
//
//   0x0043eed0  55                push ebp
//   0x0043eed1  89 e5             mov ebp, esp
//   0x0043eed3  51                push ecx
//   0x0043eed4  89 4d fc          mov [ebp-4], ecx
//   0x0043eed7  8b 45 fc          mov eax, [ebp-4]
//   0x0043eeda  d9 80 d4 01 00 00 fld dword ptr [eax+0x1d4]
//   0x0043eee0  8b e5             mov esp, ebp
//   0x0043eee2  5d                pop ebp
//   0x0043eee3  c3                ret
//
// The return is an x87 float in ST(0), not an XMM value: the only FLD in the
// body is the operand load and there is no FSTP, FADD or store to memory, so
// the loaded value is still on the x87 stack when the frame is torn down. That
// is the whole observable contract, and it is why the function has no
// stack-cleanup immediate and why callers read ST(0) directly.
//
// The receiver is an editor part: its children array begin/end sit at
// +0x340 / +0x344 and its attribute bitset at +0xDC8 in the same callers
// (0x0043f3f0, 0x0043ecb0), both of which match the SDK's
// Editors::EditorRigblock. The float at +0x1D4 is not named by the SDK; its
// use in 0x0043ecb0 - the maximum over eligible children, clamped into
// [+0x218, +0x21C] and normalised by (v - lo) / (hi - lo) - makes it a
// normalised blend weight, which is recorded as INFERRED and not as a name.
#pragma once

#include <cstdint>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

struct EditorPart_0043eed0 {
    // Only +0x1D4 is touched by this body. The remaining words below are the
    // neighbouring fields the callers read, listed so the offset is not
    // mistaken for an arbitrary one; the body itself must not rely on them.
    float blend_value;        // +0x1D4  the returned field
    float clamp_low;          // +0x218
    float clamp_high;         // +0x21C
    void** children_begin;    // +0x340
    void** children_end;      // +0x344
    std::uint32_t attributes_lo;  // +0xDC8
    std::uint32_t attributes_hi;  // +0xDC8 + 4
};

extern "C" float __attribute__((thiscall))
FUN_0043eed0_get_blend_value(const EditorPart_0043eed0* self);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
