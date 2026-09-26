// Wave-13 worker batch b02 -- target 0x005766e0
// Clean-room reconstruction from SporeApp.exe 3.1.0.22.
//
// Observed shape: 27 instructions, 0x005766e0..0x00576712, 53 bytes.
// A __thiscall refcounted-pointer setter:
//
//   void* assign(RefHolder* self, void** new_value)
//   {
//       void* incoming = *new_value;              // 0x005766e0, 0x005766e6
//       void* current  = self->value;             // 0x005766eb
//       if (incoming == current) return self;      // 0x005766ed, 0x005766ef
//       if (incoming) incoming->vtable[1]();       // 0x005766f1..0x005766fc, slot +0x04
//       self->value = incoming;                    // 0x005766fe
//       if (current) current->vtable[2]();         // 0x00576700..0x0057670b, slot +0x08
//       return self;                               // 0x0057670d
//   }
//
// The vtable slot pair +0x04 / +0x08 is the refcounted protocol, established
// independently from the base vtable at 0x013eb844 recorded in
// reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json, whose +0x04 is
// 0x00432a50 (LOCK; INC [this+4]; return old) and whose +0x08 is 0x00404f90
// (LOCK; DEC [this+4]; at zero set it to 1 and call slot +0x00 with argument 1).
//
// The class of the pointee is NOT claimed, and the function is not named after
// any SDK symbol. See reconstruction/metadata/wave13-w1-dispatch-b02/005766e0.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// The pointee. Only the two slots this function calls are named; the concrete
// class is not identified and no layout beyond the vtable is claimed.
struct RefCounted {
    void** vtable;  // +0x00, with slot +0x04 and slot +0x08 used
};

// The receiver: a single-pointer refcounted holder. Every inspected callsite
// forms it with LEA ECX,[...] and passes the address of a separate dword as the
// argument -- 0x0064af7a uses a stack local with the argument at [EBP + 0x1b0],
// 0x00588ea8 uses [EBP + 0xd8] with the argument at [EBP + 0xd4], and the two
// sites inside the stub at 0x00c3a8a4 and 0x00c3a8cc use [EBX + 0x288] with
// arguments at [EBX + 0x29c] and [EBX + 0x28c].
struct RefHolder {
    RefCounted* value;  // +0x00, the only member
};

// Port for vtable slot +0x04. Independent evidence: 0x00432a50 is
// LOCK; INC [this+4]; return the old value.
void ref_counted_add_ref_port(RefCounted* self);
// Port for vtable slot +0x08. Independent evidence: 0x00404f90 is
// LOCK; DEC [this+4]; on reaching zero set [this+4] = 1 and call slot +0x00
// with argument 1.
void ref_counted_release_port(RefCounted* self);

}  // namespace openspore::wave13::b02
