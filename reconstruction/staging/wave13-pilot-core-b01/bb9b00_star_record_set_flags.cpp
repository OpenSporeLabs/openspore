#include "wave13_pilot_core_b01_types.hpp"

// 0x00bb9b00 — 9 instructions, 29 bytes, body span 0x00bb9b00..0x00bb9b1c,
// INT3 pad 0x00bb9b1d..0x00bb9b23.
//
//   00bb9b00  CMP  byte ptr [ESP+0x8],0x0
//   00bb9b05  JZ   0x00bb9b11
//   00bb9b07  MOV  EAX,[ESP+0x4]
//   00bb9b0b  OR   dword ptr [ECX+0x5c],EAX
//   00bb9b0e  RET  0x8
//   00bb9b11  MOV  EDX,[ESP+0x4]
//   00bb9b15  NOT  EDX
//   00bb9b17  AND  dword ptr [ECX+0x5c],EDX
//   00bb9b1a  RET  0x8
//
// ECX is never written, so the update is a read-modify-write of the dword at
// +0x5c. The mask argument is used whole in both directions; the NOT is
// applied to the mask only, never to the field. The two exits differ in stack
// cleanup bytes but both pop the same two words.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

void StarRecord_00bb9b00_setFlagsMask(OpaqueStarRecord* self, Dword mask,
                                      std::uint8_t set) {
    if (set != 0) {
        self->field_05c = self->field_05c | mask;
        return;
    }
    self->field_05c = self->field_05c & ~mask;
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
