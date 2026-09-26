// Original body at VA 0x004adb40 (FUN_004adb40), 17 bytes / 9 instructions.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x004adb40. __thiscall, no stack argument, bare RET. Loads the 4-byte
// IEEE-754 single at self+0x44 and returns it on the x87 stack in ST(0).
// Sibling accessors on the same receiver: 0x004adaa0 -> +0x38,
// 0x004adb00 -> +0x40, 0x004adc00 -> setter for +0x48.
extern "C" __attribute__((thiscall)) float FUN_004adb40_GetField44(OpaqueEditorBlockSettings* self);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
