#include "wave13_pilot_core_b01_types.hpp"

// 0x00c472e0 — 38 instructions, 98 bytes, image-base-relative body span
// 0x00c472e0..0x00c47341, INT3 pad 0x00c47342..0x00c47349.
//
// thiscall, void return, no stack arguments of its own. Frame: four saved
// registers (EBX, EBP, ESI, EDI = 16 bytes) and a bare `RET`, so the caller
// owns all stack cleanup. Order of operations is reproduced exactly:
//
//   00c472e3  MOV  ESI, ECX                  receiver -> ESI
//   00c472e5  MOV  EBP, [ESI+0x17c]          sub-object
//   00c472ec  TEST EBP, EBP / 00c472ee JNZ
//   00c472f0  MOV  EBP, ESI                  null sub-object -> self
//   00c472f2  MOV  EAX, [ESI+0x9c]
//   00c472f8  MOV  EDI, [EAX+0x13c]
//   00c472fe  CALL 0x00c451e0                ECX still == ESI
//   00c47305  MOV  EBX, [EAX+0x84]
//   00c4730b  MOV  EAX, [EDX+0x10c]          virtual slot +0x10c
//   00c47311  PUSH 0 / 00c47313 PUSH 0 / 00c47315 PUSH EBP
//   00c47318  CALL EAX                       this, sub, 0, 0
//   00c4731d  MOV  EAX, [EDX+0xa4]           virtual slot +0xa4
//   00c47325  CALL EAX                       this
//   00c4732a  CALL 0x00ce6950                ECX == EDI
//   00c47331  CALL 0x00b3d4a0                no argument consumed (bare RET)
//   00c47338  CALL 0x00aeb7a0                seven stack words, RET 0x1c
//
// The seven stack words, in callee argument order, are the values pushed
// between 0x00c47311 and 0x00c47330 read bottom-up after the CALL
// decrements ESP:
//   arg1 = [cached-sub-object + 0x84]      (pushed last, at 00c47330)
//   arg2 = port_00ce6950(planet record)
//   arg3 = virtual +0xa4()
//   arg4 = virtual +0x10c(sub, 0, 0)
//   arg5 = sub-object (parent-or-self)
//   arg6 = 0
//   arg7 = 0
// 0x00aeb160 proves that reading: at 0x00aeb1a1/0x00aeb1af/0x00aeb1b2/
// 0x00aeb1b5 it stores args 1..4 into +0x18/+0x34/+0x38/+0x3c, at 0x00aeb1cb
// it assigns arg5 into +0x40 after releasing the previous holder through
// vtable slot +0x04, and at 0x00aeb1e3/0x00aeb1e6 it stores args 6 and 7 into
// +0x44 and +0x48.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

void SimMission_00c472e0_publishStateArtifacts(OpaqueMission* self) {
    const OpaqueMission* sub = self->field_17c;
    if (sub == nullptr) {
        sub = self;
    }

    const void* planet = self->field_09c;
    const void* planet_record =
        *reinterpret_cast<void* const*>(
            reinterpret_cast<const std::uint8_t*>(planet) + 0x13c);

    const void* cached = port_00c451e0_get_cached_sub_object(self);
    const Dword state_word = *reinterpret_cast<const Dword*>(
        reinterpret_cast<const std::uint8_t*>(cached) + 0x84);

    auto* const* vftable = reinterpret_cast<void* const*>(self->vftable);
    using Slot10c = Dword(W13_THISCALL*)(OpaqueMission*, const OpaqueMission*, Dword, Dword);
    using Slot0a4 = Dword(W13_THISCALL*)(OpaqueMission*);
    const auto slot_10c = reinterpret_cast<Slot10c>(vftable[0x10c / 4]);
    const auto slot_0a4 = reinterpret_cast<Slot0a4>(vftable[0x0a4 / 4]);

    const Dword outcome = slot_10c(self, sub, 0, 0);
    const Dword secondary = slot_0a4(self);
    const Dword planet_word = port_00ce6950_read_field_184(planet_record);
    Dword* service = port_00b3d4a0_read_service_slot_0167eb44();

    port_00aeb7a0_register_record(service, state_word, planet_word, secondary,
                                  outcome, reinterpret_cast<Dword>(sub), 0, 0);
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
