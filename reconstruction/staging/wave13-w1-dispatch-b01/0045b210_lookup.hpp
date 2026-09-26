// Original body at VA 0x0045b210 (FUN_0045b210), 121 bytes / 45 instructions.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x0045b210. __thiscall, one 4-byte stack word, callee-cleaned (RET 0x4).
// Looks `id` up in the hash map embedded at self+0x8 and returns the mapped
// 32-bit value, or 0 when the id is absent. The incoming stack word is the id
// and it is handed to 0x00421950 by address (LEA EAX,[EBP+8]).
extern "C" __attribute__((thiscall)) std::uint32_t FUN_0045b210_LookupValueById(OpaqueIdRegistry* self,
                                                       std::uint32_t id);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
