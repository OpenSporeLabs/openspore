// 0x00ff2e30 — 0x00ff2e30..0x00ff2e7a, 29 instructions, 75 bytes.
//
// __thiscall, void return, receiver in ECX, zero stack arguments, bare RET
// (no immediate), so the caller owns all stack cleanup.
//
// Observed order of operations, taken from the instruction listing and not
// from the decompiler:
//
//   0x00ff2e30 PUSH ESI
//   0x00ff2e31 MOV ESI,ECX                       receiver -> ESI
//   0x00ff2e33 CALL 0x00ff2d80                    base-class part, ECX untouched
//   0x00ff2e38 MOV EAX,dword ptr [ESI + 0x3c]
//   0x00ff2e3b TEST EAX,EAX        0x00ff2e3d JZ skip3c
//   0x00ff2e3f CMP dword ptr [EAX + -0x4],0x0     0x00ff2e43 JZ skip3c
//   0x00ff2e45 PUSH EAX
//   0x00ff2e46 CALL 0x00f47380
//   0x00ff2e4b ADD ESP,0x4
//   0x00ff2e4e .. 0x00ff2e61   the same three tests against [ESI + 0x28]
//   0x00ff2e64 MOV ESI,dword ptr [ESI]           note: overwrites the saved reg
//   0x00ff2e66 .. 0x00ff2e76   the same three tests against [ESI + 0x00]
//   0x00ff2e79 POP ESI
//   0x00ff2e7a RET
//
// The `CMP dword ptr [reg + -0x4], 0` guard is a real, load-bearing predicate,
// not a null check. The word one dword below a payload is the block header the
// heap manager at 0x00926fd0 itself reads: [payload-8] is the free-list link
// and [payload-4] is size|flags with three flag bits and bit 31 set once the
// block is on the free list. The guard therefore requires a non-zero header
// word. What that word being zero would mean is NOT established, and the
// reconstruction only reproduces the comparison.
//
// Ownership split, as observed and not as a C++ ownership claim: 0x00ff2d80
// releases every element of the ranges [+0x3c,+0x40) and [+0x28,+0x2c) and then
// resets each end pointer back to its begin, leaving the begin pointers intact.
// This function then releases the three remaining pointers at +0x3c, +0x28 and
// +0x00. So the range contents are emptied here and the three pointers are
// freed here.
//
// All five recorded call sites (0x00b8de96, 0x00b8dfab, 0x00b8e78c, 0x00b8e8f3,
// 0x00c8c34d) follow the identical shape "set ECX to the element, CALL this,
// PUSH the same element, CALL 0x00f47380", which is the inlined
// `destructor(); operator delete(p);` sequence.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

// Reads the 4-byte heap block header that sits immediately below a payload.
// Width 1 in the original is not the case here: the CMP is a dword compare.
inline std::int32_t block_header_below(const void* payload) noexcept {
    const auto* header = static_cast<const std::uint8_t*>(payload) - 4;
    std::int32_t value = 0;
    __builtin_memcpy(&value, header, sizeof value);
    return value;
}

void destroy_00ff2e30(OpaqueNode* self) noexcept {
    node_release_contents_port(self);

    void* const p3c = self->field_3c;
    if (p3c != nullptr && block_header_below(p3c) != 0) {
        heap_release_port(p3c);
    }

    void* const p28 = self->field_28;
    if (p28 != nullptr && block_header_below(p28) != 0) {
        heap_release_port(p28);
    }

    void* const p00 = self->field_00;
    if (p00 != nullptr && block_header_below(p00) != 0) {
        heap_release_port(p00);
    }
}

}  // namespace openspore::wave13_w1_core_b15
