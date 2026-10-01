// PKG-SPOREPEDIA-SLOT-RELEASE -- VA 0x00641e10
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Opaque boundary types for the reconstruction of FUN_00641e10. No machine
// record for this target names a class, a member, a dispatch table or a slot
// target, so nothing here carries a member name: the receiver is an opaque
// word-addressed block and every access is stated as a machine displacement.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-slot-release requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL __thiscall
#define PKG_SPOREPEDIA_SLOT_RELEASE_CDECL __cdecl
#else
#define PKG_SPOREPEDIA_SLOT_RELEASE_THISCALL __attribute__((thiscall))
#define PKG_SPOREPEDIA_SLOT_RELEASE_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sporepedia_slot_release {

using Word = std::uint32_t;

// The machine ABI record classifies the word this body leaves in EAX as
// "unclassified_in_EAX" (register_class aggregate_unknown, return.type null,
// void_possible false). The name is the record's own; the spelling below is the
// width the record's own return register implies, and nothing more.
using unclassified_in_EAX = Word;

// The first word of the pointee at 0x00641e24. It is read and then indexed, so
// it is a pointer to a word block. Its type is not established by the machine.
using OpaqueDispatchTable = void;

// 0x00641e26 reads the second word of that block and 0x00641e29 transfers
// control through it. Nothing in the record names the callee, so the slot target
// is a function pointer of the shape the transfer itself implies: the receiver
// in ECX (ECX still holds the pointee when CALL EDX executes), no stack
// argument, and no stack cleanup afterwards in this body.
#if defined(_MSC_VER)
using OpaqueSlotTarget = void(__thiscall *)(void *);
#else
using OpaqueSlotTarget = void(__attribute__((thiscall)) *)(void *);
#endif

// The one direct callee of the body, 0x005bf0e0. Its own record
// (ghidra_get_function_by_address 0x005bf0e0: "undefined FUN_005bf0e0(void)")
// names neither a convention nor a return type, so the caller-cleaned two-word
// shape this body uses -- two pushes, CALL, ADD ESP,0x8 at 0x00641e35 -- is what
// the argument and cleanup of the declaration below state. Its result is a
// four-byte word by the live decompilation of that address
// ("undefined4 FUN_005bf0e0(undefined4 *, undefined4)", returning 1 or 0 on the
// two paths it shows); this body's own ABI record does not classify the word it
// inherits, so the return type below stays the record's own name.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_SLOT_RELEASE_CDECL
FUN_005bf0e0(void *first, void *second);

}  // namespace openspore::reconstruction::pkg_sporepedia_slot_release
