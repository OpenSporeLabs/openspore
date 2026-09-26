// Original body at VA 0x004adc20 (FUN_004adc20), 22 bytes / 10 instructions.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x004adc20. __thiscall, one 4-byte stack word, callee-cleaned (RET 0x4).
// Writes the low byte of the incoming stack word to self+0x4f. Sibling
// accessors on the same receiver: 0x004adc40 reads +0x4f, 0x004adba0 and
// 0x004adbe0 write +0x4c and +0x4d, 0x004adb60 writes +0x4e.
extern "C" __attribute__((thiscall)) void FUN_004adc20_SetFlag4F(OpaqueEditorBlockSettings* self,
                                       std::uint8_t value);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
