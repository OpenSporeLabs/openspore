// Reconstruction of 0x004ad450 - a one-word pointer field getter.
//
// Complete body, 11 instructions, 0x004ad450..0x004ad468, read live
// (558bec 83ec08 894df8 8b45f8 8b4830 894dfc 8b45fc 8be5 5dc3, then INT3
// pad):
//
//   0x004ad450  55                push ebp
//   0x004ad451  89 e5             mov ebp, esp
//   0x004ad453  83 ec 08          sub esp, 8
//   0x004ad456  89 4d f8          mov [ebp-8], ecx
//   0x004ad459  8b 45 f8          mov eax, [ebp-8]
//   0x004ad45c  8b 48 30          mov ecx, [eax+0x30]
//   0x004ad45f  89 4d fc          mov [ebp-4], ecx
//   0x004ad462  8b 45 fc          mov eax, [ebp-4]
//   0x004ad465  8b e5             mov esp, ebp
//   0x004ad467  5d                pop ebp
//   0x004ad468  c3                ret
//
// One load, one return, no callee, no global, no arithmetic, no branch.
//
// The ABI is settled by the callsites rather than by the body, because the
// body reads nothing but ECX. 0x004a6c30 pushes a value, calls this with ECX
// set from a frame slot, and then calls 0x004b9440 with the return value in ECX
// and the pushed value still on the stack; 0x004b9440 ends in RET 4, so it is
// the callee that pops. 0x004a6c76 calls the same function with nothing pushed
// at all. Both facts together mean this function takes no stack argument and
// leaves ESP untouched, and that its result is a pointer consumed as the next
// receiver - which is what the three call sites in 0x004a6690 do.
//
// The owning class is not established. The sibling at 0x004ad330 in the same
// region reads the same field+0x30, null-checks it, and passes `this` as a
// stack argument to 0x004b9570 with the field value in ECX; the sibling at
// 0x004ad280 walks a pointer vector at +0x18. That fixes a shape - a vptr, a
// pointer range at +0x18, and a single related pointer at +0x30 - and nothing
// more.
#pragma once

#include <cstdint>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

// Receiver with the three words the sibling functions in the same code region
// establish. Only +0x30 is read by this body.
struct RelatedPointerOwner_004ad450 {
    void** vptr;            // +0x00
    std::uint32_t pad_04;   // +0x04
    std::uint32_t pad_08;   // +0x08
    std::uint32_t pad_0c;   // +0x0C
    std::uint32_t pad_10;   // +0x10
    std::uint32_t pad_14;   // +0x14
    void** range_begin;     // +0x18
    void** range_end;       // +0x1C
    std::uint32_t pad_20;   // +0x20
    std::uint32_t pad_24;   // +0x24
    std::uint32_t pad_28;   // +0x28
    std::uint32_t pad_2c;   // +0x2C
    void* related;          // +0x30  the returned field
};

// Port for the consumer the callsites pair with this getter. Declared, not
// defined: 0x004b9440 writes its stack argument into [*(this+0x0C)+0x1C] and
// 0x004b9420 is its sibling, but neither the pointee type nor the field names
// are established.
extern "C" void __attribute__((thiscall))
PORT_apply_to_related_004b9440(void* related, void* payload);

extern "C" void* __attribute__((thiscall))
FUN_004ad450_get_related(const RelatedPointerOwner_004ad450* self);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
