#include "wave13_pilot_core_b01_types.hpp"

// 0x00b3d850 — 15 instructions, 32 bytes, body span 0x00b3d850..0x00b3d86f.
//
//   00b3d850  PUSH ESI
//   00b3d851  MOV  ESI,ECX
//   00b3d853  ADD  dword ptr [ESI],0x4        advance the cursor one slot
//   00b3d856  MOV  EAX,[ESI] / 00b3d858 CMP EAX,[ESI+0x4]
//   00b3d85b  JZ   0x00b3d86c                 cursor reached end: stop
//   00b3d85d  MOV  EAX,[EAX]                  load *cursor
//   00b3d85f  PUSH EAX
//   00b3d860  LEA  ECX,[ESI+0x8]              owner loaded, never read there
//   00b3d863  CALL 0x00c02600
//   00b3d868  TEST AL,AL
//   00b3d86a  JZ   0x00b3d853                 not accepted: keep advancing
//   00b3d86c  MOV  EAX,ESI
//   00b3d86e  POP  ESI
//   00b3d86f  RET
//
// Both exits return the receiver, so the only observable effect is the
// advanced cursor in slot +0x00. The loop advances before it tests, which
// means the slot the handle started on is never re-examined.

namespace openspore::reconstruction::wave13_pilot_core_b01 {

OpaqueCursor* Cursor_00b3d850_advanceToAccepted(OpaqueCursor* self) {
    for (;;) {
        self->cursor = self->cursor + 1;
        if (self->cursor == self->end) {
            return self;
        }
        void* element = *self->cursor;
        if (port_00c02600_is_accepted_element(element) != 0) {
            return self;
        }
    }
}

}  // namespace openspore::reconstruction::wave13_pilot_core_b01
