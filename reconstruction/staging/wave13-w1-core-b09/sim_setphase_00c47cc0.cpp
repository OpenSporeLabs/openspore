// 0x00c47cc0 - state / phase setter, with a dedicated tail when the new value
// is 3.
//
// Body span 0x00c47cc0..0x00c47d6f, 178 bytes, 43 instructions, all read from
// the live disassembly. ABI: __thiscall with one stack dword. The receiver is
// ECX, the argument is read out of [ESP + 0x4] at 0x00c47cc0 BEFORE the frame is
// reserved, and the epilogue is RET 0x4, so the callee pops the argument.
// No return value is produced.
//
// Order of operations, as observed:
//   1. EAX = [ESP + 0x4] (the argument); SUB ESP,0x40
//   2. if (this->phase_84 == arg) return            0x00c47cc7 / JZ 0x00c47d6c
//   3. this->phase_84 = arg                          0x00c47cd3
//   4. if (buffer_a.head != buffer_a.tail) { *head = u16(0); tail = head; }
//                                                    0x00c47cd9..0x00b3dcf2
//   5. same shape for buffer_b at +0x15c / +0x160     0x00c47cf8..0x00c47d11
//   6. if (this->phase_84 != 3) return                0x00c47d17 / JNZ 0x00c47d6c
//   7. build a 0x3c-byte temporary on the stack, fetch the app system, call its
//      slot +0x14 with (0x038cf2fd, &temporary, 0), then run the temporary's
//      destructor 0x00421cf0
//
// Classification BOUNDED_SEMANTIC: the body is complete, but the meaning of the
// state word, the owner class, the temporary's class and the callee behind the
// app-system slot +0x14 are not established.

#include "sim_setphase_00c47cc0.hpp"

#include "b09_opaque_ports.hpp"

extern "C" B09_THISCALL void SimSetPhase_00c47cc0_reconstruct(OpaquePhaseOwnerObserved* self,
                                                 std::int32_t value) {
    // 0x00c47cc7: CMP dword ptr [ECX + 0x84],EAX ; 0x00c47ccd JZ 0x00c47d6c
    if (self->phase_84 == static_cast<std::uint32_t>(value)) {
        return;
    }

    // 0x00c47cd3: MOV dword ptr [ECX + 0x84],EAX
    self->phase_84 = static_cast<std::uint32_t>(value);

    // 0x00c47cd9..0x00c47cf2. The head is re-read after the store, so the tail
    // is set from the head, not from the value that was compared.
    if (self->buffer_a_head_14c != self->buffer_a_tail_150) {
        *self->buffer_a_head_14c = 0;
        self->buffer_a_tail_150 = self->buffer_a_head_14c;
    }

    // 0x00c47cf8..0x00c47d11
    if (self->buffer_b_head_15c != self->buffer_b_tail_160) {
        *self->buffer_b_head_15c = 0;
        self->buffer_b_tail_160 = self->buffer_b_head_15c;
    }

    // 0x00c47d17: CMP dword ptr [ECX + 0x84],0x3 ; 0x00c47d1e JNZ 0x00c47d6c
    if (self->phase_84 != static_cast<std::uint32_t>(kPhaseValue3TriggersTail)) {
        return;
    }

    // 0x00c47d20..0x00c47d46, store order reproduced exactly. The first vtable
    // store is dead: it is overwritten four instructions later. Only the five
    // stores the body actually performs are made; the rest of the frame stays
    // whatever the caller's stack held, as in the original.
    OpaqueBakeQueueTemporary temporary;
    temporary.vtable_a = 0x013eb90cu;  // 0x00c47d28, dead
    temporary.field_04 = 0u;           // 0x00c47d35, XCHG with a zeroed EDX
    temporary.vtable_a = 0x013eb844u;  // 0x00c47d37
    temporary.pairs[0].first = reinterpret_cast<std::uint32_t>(self);  // 0x00c47d46
    temporary.pairs[5].first = 0x038cf2fdu;  // 0x00c47d20, byte offset +0x30
    temporary.pairs[6].first = 0u;           // 0x00c47d3e, byte offset +0x38

    // 0x00c47d4a CALL 0x0067dcc0, which is MOV EAX,[0x015fd890] ; RET.
    OpaqueAppSystemIfcObserved* app = static_cast<OpaqueAppSystemIfcObserved*>(
        opaque_AppSystem_Get_0067dcc0());

    // 0x00c47d4f: EDX = [EAX] ; 0x00c47d51: EDX = [EDX + 0x14]
    // 0x00c47d54..0x00c47d5f push, in order, 0 then &temporary then 0x038cf2fd
    // 0x00c47d60: MOV ECX,EAX ; 0x00c47d62: CALL EDX
    app->slot_14(0x038cf2fdu, temporary, 0u);

    // 0x00c47d64 LEA ECX,[ESP] ; 0x00c47d67 CALL 0x00421cf0
    opaque_TemporaryDtor_00421cf0(&temporary);
}
