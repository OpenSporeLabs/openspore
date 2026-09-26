// 0x00c47180 — SimCore_00c47180_manager_slot_replace
//
// 17 instructions, 51 bytes, 2 direct callees, 1 virtual call.
//
//   00c47180  55                    PUSH ESI
//   00c47181  8D B1 E8 01 00 00     LEA ESI,[ECX + 0x1E8]
//   00c47187  8B 0E                 MOV ECX,dword ptr [ESI]
//   00c47189  85 C9                 TEST ECX,ECX
//   00c4718B  74 10                 JZ 0x00c4719D
//   00c4718D  89 06                 MOV dword ptr [ESI],0
//   00c47193  8B 01                 MOV EAX,[ECX]
//   00c47195  8B 50 C0              MOV EDX,[EAX + 0xC0]
//   00c4719B  FF D2                 CALL EDX
//   00c4719D  8B 44 24 08           MOV EAX,[ESP + 0x8]
//   00c471A1  56                    PUSH ESI
//   00c471A2  50                    PUSH EAX
//   00c471A3  E8 ...                CALL 0x00B3D2A0
//   00c471A8  8B C8                 MOV ECX,EAX
//   00c471AA  E8 ...                CALL 0x00BB59B0
//   00c471AF  5E                    POP ESI
//   00c471B0  C2 04 00              RET 0x4
//
// Two facts a decompiler-only reading would miss:
//   1. The slot is cleared to 0 at 0x00c4718D BEFORE the virtual call, and the
//      call still receives the old pointer because ECX was loaded at
//      0x00c47187 and never reloaded. Detach-then-clear ordering is the
//      contract, not clear-then-detach.
//   2. The incoming stack argument is dead. 0x00B3D2A0 is exactly
//      `MOV EAX,[0x0167EAE4] ; RET`; it consumes nothing, so the word pushed at
//      0x00c471A2 survives and is popped by 0x00BB59B0's `RET 0x8` as its
//      second argument. One dead word, one live word: &this->f_1E8.

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" void SimCore_00c47180_manager_slot_replace(OpaqueC47180Owner* self,
                                                      std::uint32_t unused_arg);

extern "C" void SimCore_00c47180_manager_slot_replace(OpaqueC47180Owner* self,
                                                      std::uint32_t /*unused_arg*/) {
    // LEA ESI,[ECX + 0x1E8]
    void** slot = &self->f_1E8;

    // MOV ECX,[ESI] ; TEST ECX,ECX ; JZ
    void* occupant = *slot;
    if (occupant != nullptr) {
        // MOV [ESI],0 -- cleared first ...
        *slot = nullptr;
        // MOV EAX,[ECX] ; MOV EDX,[EAX + 0xC0] ; CALL EDX -- ... and ECX, not
        // memory, is what still carries the evicted pointer into the call.
        OpaqueManagerSlotOccupant* o = static_cast<OpaqueManagerSlotOccupant*>(occupant);
        o->vtable->slots[0xC0 / sizeof(C47180Vslot)](o);
    }

    // The pushed argument is discarded by 0x00B3D2A0, which reads only the
    // global at 0x0167EAE4.
    void* manager = port_00b3d2a0_manager_getter();
    port_00bb59b0_replace(self, manager, slot);
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
