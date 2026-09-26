// Original body at VA 0x00438700 (FUN_00438700), 424 bytes / 128 instructions.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x00438700. __thiscall, one 4-byte stack word, callee-cleaned (RET 0x4).
// Cascade-adoption step for one editor rigblock against another. See the .cpp
// for the branch table read out of the disassembly.
extern "C" __attribute__((thiscall)) void FUN_00438700_AdoptCascadeFrom(OpaqueEditorRigblock* self,
                                              OpaqueEditorRigblock* other);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
