#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-shared-default-true-wave12 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "pkg-shared-default-true-wave12 requires 32-bit pointers");

struct OpaqueB1Fbf0SlotReceiver;

namespace openspore::reconstruction::pkg_shared_default_true_wave12 {

// Opaque receiver of the vtable slot(s) that resolve to 0x00b1fbf0.
//
// 0x00b1fbf0 never dereferences it, but 0x00ee8bf6 does
// (MOV EAX, dword ptr [EDX + 0x10]; CALL EAX) with ECX already loaded from
// [ESI + 0x10] at 0x00ee8bf1, so the slot is entered with a populated
// receiver. Keeping the parameter records that observed port; the
// implementation ignores it.
//
// The observed body is byte-identical under __cdecl, __stdcall, __thiscall
// and __fastcall, because it reads no register, consumes no stack argument and
// returns through a bare RET with no immediate. The persisted ABI record for
// this target carries calling_convention = null, so no convention is asserted
// here either; the model test checks that the thiscall spelling compiles to
// the same three bytes rather than committing to it.
extern "C" std::uint8_t FUN_00b1fbf0_shared_default_true(
    OpaqueB1Fbf0SlotReceiver* receiver);

}  // namespace openspore::reconstruction::pkg_shared_default_true_wave12
