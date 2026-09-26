// Original body at VA 0x00573d70 (FUN_00573d70), 425 bytes / 148 instructions.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x00573d70. __thiscall, two 4-byte stack words, callee-cleaned (RET 0x8).
// `part` is the new primary rigblock; `arg2` is pushed by every observed caller
// and never read by the body. See the .cpp for the full state machine.
extern "C" __attribute__((thiscall)) void FUN_00573d70_SetPrimaryPart(OpaqueEditor* editor, void* part,
                                            std::uint32_t arg2);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
