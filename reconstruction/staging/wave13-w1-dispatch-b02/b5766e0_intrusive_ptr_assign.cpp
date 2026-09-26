// Wave-13 worker batch b02 -- target 0x005766e0
// Reconstructed from the live disassembly of 0x005766e0..0x00576712
// (27 instructions). Every statement is anchored to an instruction address;
// see reconstruction/metadata/wave13-w1-dispatch-b02/005766e0.json.

#include "b5766e0_intrusive_ptr_assign.hpp"

namespace openspore::wave13::b02 {

// 0x005766e0, __thiscall, one stack argument, callee cleanup of 4 bytes
// (RET 0x4 at 0x00576712), returns the receiver in EAX.
RefHolder* FUN_005766e0_reconstruct(RefHolder* self, RefCounted** new_value) {
    // 0x005766e0: MOV EAX,dword ptr [ESP + 0x4] reads the argument BEFORE the
    // three pushes, so [ESP + 0x4] is the entry [ESP + 0x4] and the argument is
    // a pointer to a pointer, not a pointer to a value.
    // 0x005766e4..0x005766e8: three saved registers.
    // 0x005766e6: MOV ESI,dword ptr [EAX] -- the incoming value is loaded
    // through the argument, a second indirection.
    // 0x005766e9: MOV EDI,ECX -- the receiver arrives in ECX.
    RefCounted* const incoming = *new_value;

    // 0x005766eb: MOV EBX,dword ptr [EDI] -- the holder's current value.
    RefCounted* const current = self->value;

    // 0x005766ed/0x005766ef: CMP ESI,EBX / JZ 0x0057670d. An assignment of the
    // value already held does nothing at all: no AddRef, no store, no Release.
    // Without this the store-then-release order below would release the pointer
    // it had just AddRef'd.
    if (incoming == current) {
        return self;
    }

    // 0x005766f1/0x005766f3: TEST ESI,ESI / JZ 0x005766fe -- a null incoming
    // value skips the AddRef and goes straight to the store.
    if (incoming != nullptr) {
        // 0x005766f5/0x005766f7: the incoming pointer's vtable and its slot
        // +0x04.
        // 0x005766fa/0x005766fc: the call is __thiscall with the incoming
        // pointer as the receiver and no stack argument.
        ref_counted_add_ref_port(incoming);
    }

    // 0x005766fe: MOV dword ptr [EDI],ESI -- the store happens AFTER the
    // AddRef and BEFORE the Release of the previous occupant, which is what
    // makes the sequence exception-safe with respect to the refcount.
    self->value = incoming;

    // 0x00576700/0x00576702: TEST EBX,EBX / JZ 0x0057670d -- a null previous
    // occupant skips the Release.
    if (current != nullptr) {
        // 0x00576704/0x00576706: the previous occupant's vtable and its slot
        // +0x08, four bytes further along than the AddRef slot.
        // 0x00576709/0x0057670b: __thiscall on the previous occupant, no stack
        // argument. The return value is discarded.
        ref_counted_release_port(current);
    }

    // 0x0057670d: MOV EAX,EDI -- the receiver is returned on every path,
    // including the two early exits.
    // 0x0057670f..0x00576712: POP EDI; POP ESI; POP EBX; RET 0x4.
    return self;
}

}  // namespace openspore::wave13::b02
