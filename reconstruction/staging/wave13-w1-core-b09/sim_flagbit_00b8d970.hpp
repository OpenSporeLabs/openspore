#pragma once

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// 0x00b8d970 - 9-byte single-bit extractor from a flag word.
//
//   0x00b8d970  8b 41 2c     MOV EAX,dword ptr [ECX + 0x2c]
//   0x00b8d973  c1 e8 08     SHR EAX,0x8
//   0x00b8d976  24 01        AND AL,0x1
//   0x00b8d978  c3           RET
//
// Owner class: NOT established. 31 references, all UNCONDITIONAL_CALL, no DATA
// reference, so not a vtable slot.
// ---------------------------------------------------------------------------

// The receiver. Only the two fields this batch observed is modelled. +0x28 is a
// small state that callers compare against 0 and 1 before consulting the flag
// word; +0x2c is a packed flag word, proved by the inlined duplicate at
// 0x00b8d9ff..0x00b8da12, which shifts the same word by 8 AND tests bit 0 of the
// result and then separately tests bit 0x800 of the same word.
struct OpaqueFlagWordOwnerObserved {
    std::uint8_t opaque_to_0x27[0x28];
    std::uint32_t state_28;   // compared with 0 and 1 by callers
    std::uint32_t flags_2c;   // bitfield; bit 8 is the flag this function reads
};
