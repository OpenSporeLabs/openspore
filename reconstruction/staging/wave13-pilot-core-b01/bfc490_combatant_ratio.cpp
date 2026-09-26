#include "wave13_pilot_core_b01_types.hpp"

// 0x00bfc490 — 8 instructions, 15 bytes, body span 0x00bfc490..0x00bfc49e,
// INT3 pad 0x00bfc49f..0x00bfc4a5.
//
//   00bfc490  PUSH ESI
//   00bfc491  MOV  ESI,ECX
//   00bfc493  MOV  EAX,[ESI] / 00bfc495 MOV EDX,[EAX+0x58]
//   00bfc498  CALL EDX                    thiscall, no stack argument
//   00bfc49a  FDIVR float ptr [ESI+0x38]  ST0 = field_0x38 / ST0
//   00bfc49d  POP  ESI
//   00bfc49e  RET
//
// The return is an x87 extended-precision value in ST0, not an EAX dword. The
// decompiler's `float10` cast is an artefact of that; the observed writer is
// FDIVR, whose operand order is reversed relative to FDIV, so the numerator is
// the field and the divisor is the virtual's result.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

float Combatant_00bfc490_healthFraction(OpaqueCombatant* self) {
    auto* const* vftable = reinterpret_cast<void* const*>(self->vftable);
    using Slot58 = float(W13_THISCALL*)(OpaqueCombatant*);
    const auto slot_58 = reinterpret_cast<Slot58>(vftable[0x58 / 4]);

    const float divisor = slot_58(self);
    return self->field_038 / divisor;
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
