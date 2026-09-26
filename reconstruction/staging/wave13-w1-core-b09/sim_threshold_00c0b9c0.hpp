#pragma once

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// 0x00c0b9c0 - 7-byte float field accessor.
//
//   0x00c0b9c0  d9 81 bc 0b 00 00   FLD dword ptr [ECX + 0xbbc]
//   0x00c0b9c6  c3                  RET
//
// Owner class: NOT established. 31 references, all UNCONDITIONAL_CALL, no DATA
// reference, so not a vtable slot.
// ---------------------------------------------------------------------------

// The receiver. Only the one field the body reads is modelled; the object is at
// least 0xbc0 bytes because the access is at +0xbbc. Callers of the same class
// in this batch touch +0x5a8, +0xb20 and +0x5e0, so it is a large aggregate.
struct OpaqueThresholdOwnerObserved {
    std::uint8_t opaque_to_0xbbb[0xbbc];
    float threshold_bbc;  // +0xbbc
};
