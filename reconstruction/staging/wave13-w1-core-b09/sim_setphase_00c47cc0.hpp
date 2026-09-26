#pragma once

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// 0x00c47cc0 - state / phase setter with a value-3 side effect.
//
// Owner class: NOT established. 18 references, all UNCONDITIONAL_CALL, no DATA
// reference, so no vtable slot and no owning type.
// ---------------------------------------------------------------------------

// The receiver. Only the fields this batch observed being read or written are
// modelled. The two cleared wchar buffers are modelled as {head, tail} cursor
// pairs because that is the only shape the body proves: it compares the two
// dwords, writes a 16-bit zero through the first and copies it into the second.
struct OpaquePhaseOwnerObserved {
    std::uint8_t opaque_to_0x83[0x84];
    std::uint32_t phase_84;  // the state word this function owns
    std::uint8_t opaque_88_to_0x14b[0xc4];
    std::uint16_t* buffer_a_head_14c;  // wchar_t* cursor
    std::uint16_t* buffer_a_tail_150;  // wchar_t* cursor
    std::uint32_t field_154;
    std::uint32_t field_158;
    std::uint16_t* buffer_b_head_15c;  // wchar_t* cursor
    std::uint16_t* buffer_b_tail_160;  // wchar_t* cursor
};

// The state values observed being passed at call sites. 1, 2, 3, 5, 6, 7, 8 and
// 9 are all attested; 0x00fef4bf also forwards a value it received from a
// virtual slot +0x7c, so the domain is open. No enum name is claimed.
enum PhaseValueObserved : std::int32_t {
    kPhaseValue3TriggersTail = 3,
};
