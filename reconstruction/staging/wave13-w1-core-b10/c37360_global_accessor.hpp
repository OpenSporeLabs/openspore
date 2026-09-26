#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00c37360 : 6 bytes, a1 68 df 68 01 / c3
//   0x00c37360: MOV EAX,dword ptr [0x0168df68]
//   0x00c37365: RET
// No receiver, no stack argument, bare RET, so the caller owns all cleanup.
// The MOV is a 32-bit load of the pointer stored at 0x0168df68, so EAX holds
// that pointer, not the address of the slot.
// Ghidra records 40 UNCONDITIONAL_CALL references and 25 data references to
// 0x0168df68; the live dword at 0x0168df68 is 0x00000000.
OpaqueSimulatorSubsystem* SimulatorSubsystem_GetGlobal_00c37360();

}  // namespace openspore::reconstruction::wave13_w1_core_b10
