#include "wave13_pilot_core_b01_types.hpp"

// 0x00c471c0 — 42 instructions, 118 bytes, body span 0x00c471c0..0x00c47234.
//
// thiscall, void return, one stack word of its own (PUSH ECX at 0x00c471c0)
// which both exits pop with `ADD ESP,0x4` at 0x00c4720d / 0x00c4722e. The
// final `JMP 0x01048ce0` is a tail transfer, so the flush port owns its own
// stack.
//
//   00c471c4  MOV  EAX,[ESI] / 00c471c6 MOV EDX,[EAX+0xf8] / 00c471cc CALL EDX
//   00c471ce  TEST AL,AL / 00c471d0 JNZ 0x00c471e2      short-circuit OR
//   00c471d4  MOV  EDX,[EAX+0xfc] / 00c471dc CALL EDX
//   00c471de  TEST AL,AL / 00c471e0 JZ  0x00c471e4
//   00c471e2  MOV  AL,0x1                                    -> AL == 1
//   00c471e4  MOV  ECX,[ESI+0x130] / 00c471ea SHR ECX,1
//   00c471ec  MOV  byte ptr [ESP+0x4],AL                      overwrite the
//                                                             pushed receiver
//   00c471f0  TEST CL,0x1 / 00c471f3 JZ 0x00c47215
//   00c471f5  TEST AL,AL / 00c471f7 JNZ 0x00c47215
//   00c471f9  MOV  EAX,[EDX+0x19c] / 00c47203 CALL EAX      no argument
//   00c47205  CALL 0x01046fc0 -> 00c47210 JMP 0x01048ce0     (tail)
//   00c47215  MOV  EAX,[ESP+0x4] / 00c47221 PUSH EAX
//   00c4721b  MOV  EDX,[EDX+0x198] / 00c47224 CALL EDX
//   00c47226  CALL 0x01046fc0 -> 00c47231 JMP 0x01048ce0     (tail)
//
// AL is only ever written whole (MOV AL,0x1), so the predicate that reaches
// the two virtuals is a byte.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

void SimMission_00c471c0_settleStateArtifacts(OpaqueMission* self) {
    auto* const* vftable = reinterpret_cast<void* const*>(self->vftable);
    using Slot0f8 = std::uint8_t(W13_THISCALL*)(OpaqueMission*);
    using Slot0fc = std::uint8_t(W13_THISCALL*)(OpaqueMission*);
    using Slot198 = std::uint8_t(W13_THISCALL*)(OpaqueMission*, std::uint8_t);
    using Slot19c = void(W13_THISCALL*)(OpaqueMission*);

    const auto slot_0f8 = reinterpret_cast<Slot0f8>(vftable[0xf8 / 4]);
    const auto slot_0fc = reinterpret_cast<Slot0fc>(vftable[0xfc / 4]);
    const auto slot_198 = reinterpret_cast<Slot198>(vftable[0x198 / 4]);
    const auto slot_19c = reinterpret_cast<Slot19c>(vftable[0x19c / 4]);

    std::uint8_t settled = slot_0f8(self);
    if (settled == 0) {
        settled = slot_0fc(self);
        if (settled == 0) {
            settled = 0;
        } else {
            settled = 1;
        }
    } else {
        settled = 1;
    }

    // 0x00c471e4/0x00c471ea/0x00c471f0: bit 1 of the dword at +0x130.
    const bool hide_star_name = ((self->field_130 >> 1) & 1) != 0;

    if (hide_star_name && settled == 0) {
        slot_19c(self);
        void* service = port_01046fc0_get_simulator_service();
        port_01048ce0_flush_pending(service);
        return;
    }

    slot_198(self, settled);
    void* service = port_01046fc0_get_simulator_service();
    port_01048ce0_flush_pending(service);
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
