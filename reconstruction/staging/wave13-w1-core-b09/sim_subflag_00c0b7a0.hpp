#pragma once

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// 0x00c0b7a0 - 19-byte boolean predicate on a two-level sub-object field.
//
//   0x00c0b7a0  8b 81 20 0b 00 00        MOV EAX,dword ptr [ECX + 0xb20]
//   0x00c0b7a6  33 c9                    XOR ECX,ECX
//   0x00c0b7a8  3b 88 0c 06 00 00        CMP ECX,dword ptr [EAX + 0x60c]
//   0x00c0b7ae  1b c0                    SBB EAX,EAX
//   0x00c0b7b0  f7 d8                    NEG EAX
//   0x00c0b7b2  c3                       RET
//
// Owner class: NOT established. 20 references, all UNCONDITIONAL_CALL, no DATA
// reference, so not a vtable slot.
// ---------------------------------------------------------------------------

// The sub-object reached through receiver +0xb20. Callers of the same family in
// this batch also read its +0x504, so it is at least 0x610 bytes. A sibling at
// 0x00c0b780 tests the very same shape at +0x608, four bytes lower.
struct OpaqueSubObjectB20Observed {
    std::uint8_t opaque_to_0x607[0x608];
    std::uint32_t sibling_field_608;  // tested by 0x00c0b780
    std::uint8_t opaque_to_0x60b[4];
    std::uint32_t field_60c;  // +0x60c, the field this predicate tests
};

struct OpaqueSubFlagOwnerObserved {
    std::uint8_t opaque_to_0xb1f[0xb20];
    OpaqueSubObjectB20Observed* sub_b20;  // +0xb20
};
