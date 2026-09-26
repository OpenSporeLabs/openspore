#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00c70150 : 259 bytes, 0x00c70150 .. 0x00c70252 inclusive, 96 instructions.
// cdecl, three pushed stack words at every observed call site (ADD ESP,0xc),
// byte-sized boolean result in AL.
//
// Frame accounting, from the five pushes on the taken path
// (PUSH ECX, PUSH ESI, PUSH EBX, PUSH EBP, PUSH EDI) at ESP0-20:
//   [ESP0 + 0x04] = 1st pushed word : read at 0x00c70152 into ESI, then
//                    OVERWRITTEN at 0x00c7017b with the loop counter and
//                    reloaded from that slot at 0x00c701ef
//   [ESP0 + 0x08] = 2nd pushed word : reloaded at 0x00c70190, never read on
//                    any other path
//   [ESP0 + 0x0c] = 3rd pushed word : read at 0x00c70194 and 0x00c7019a,
//                    used both as the dword-array base ([EAX + EBP*4]) and as
//                    the holder of the dword at +0x84
//   [ESP0 + 0x10] = a 4th slot read as a byte at 0x00c701d0
// The observed callers push only three words, so the [ESP0 + 0x10] read is of a
// slot that no observed call site initialises. That is recorded as unresolved;
// the reconstruction reads it as a fourth cdecl parameter.
std::uint8_t B10_CDECL SimOwner_AnyEntryUnlocked_00c70150(
    OpaqueSimTokenOwner* owner, void* key_or_context,
    OpaqueSimKeySource* key_source, std::uint8_t strict_flag);

}  // namespace openspore::reconstruction::wave13_w1_core_b10
