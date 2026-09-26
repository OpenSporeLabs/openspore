// Original body at VA 0x004c49e0 (FUN_004c49e0), 67 bytes / 25 instructions,
// read from the live Ghidra bridge. Reconstructed semantics, not encoding.

#pragma once

#include "opaque_types.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// VA 0x004c49e0. __thiscall, one 4-byte stack word, callee-cleaned (RET 0x4).
// Returns this->slot_018 for index 0, this->slot_01c for index 1, and 0 for
// every other index. No guard: a null receiver faults on the selected load.
extern "C" __attribute__((thiscall)) void* FUN_004c49e0_SelectSlotByIndex(OpaqueTwoSlotOwner* self,
                                               std::uint32_t index);

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
