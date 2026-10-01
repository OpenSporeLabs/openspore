// PKG-DFW-0067DC80 -- VA 0x0067dc80
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256 25d42a7a...9d914e)
//
// Boundary declarations for the reconstruction of the body at 0x0067dc80.
//
// What the machine fixes about this body's shape, before any name is chosen:
//
//   * the receiver arrives in ECX and is copied into ESI at 0x0067dc81;
//   * ECX is not written between 0x0067dc81 and the first CALL at 0x0067dc83, so
//     that callee receives the same receiver in ECX with nothing pushed;
//   * exactly one ordinary stack argument exists: the terminator is `RET 0x4`
//     at 0x0067dc9b, so the callee, not the caller, owns that one dword;
//   * only bit 0 of that argument is examined, by a byte test at 0x0067dc88;
//   * the body dereferences the receiver nowhere, so this package declares no
//     member, no layout and no displacement for it.
//
// Nothing else is claimed here. The receiver type is `void` because no record for
// this target names the class and the body never reads a field of it, so `void`
// is the only pointee the evidence supports.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-0067dc80 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_dfw_0067dc80 {

// A dword, and only a dword. The single stack argument is 4 bytes wide because
// `RET 0x4` at 0x0067dc9b pops 4 bytes, and the test at 0x0067dc88 is a BYTE test
// (`TEST byte ptr [ESP + 0x8],0x1`) of that slot, so the body fixes the low byte
// it looks at and says nothing about the other three.
using Word = std::uint32_t;

// The receiver. The body aliases it into ESI at 0x0067dc81, hands that value to
// both callees, and returns it through EAX at 0x0067dc98 -- and never dereferences
// it. The alias is what a vtable-dispatched receiver looks like from the inside;
// what it points at is not established by any record for this target, so the
// pointee is opaque and `void` is the whole of the claim.
using OpaqueMessageManagerBlock = void;

// Calling conventions, spelled per toolchain. GCC 16 rejects the MSVC keywords
// outright, so the x86-32 spelling is the attribute form.
//
// The thiscall spelling is the one the body needs. On x86-32 GCC's
// `__attribute__((thiscall))` implies callee-pops, which is exactly what the
// `RET 0x4` at 0x0067dc9b does: the one ordinary argument is removed by the
// callee's own epilogue and not by an `ADD ESP,4` anywhere in the body. The single
// `ADD ESP,0x4` in this body is at 0x0067dc95, inside the release block, and it
// discards the word this body pushed at 0x0067dc8f for the cdecl callee -- it is
// not this body's own argument cleanup.
#if defined(_MSC_VER)
#define PKG_DFW_0067DC80_THISCALL __thiscall
#define PKG_DFW_0067DC80_CDECL __cdecl
#else
#define PKG_DFW_0067DC80_THISCALL __attribute__((thiscall))
#define PKG_DFW_0067DC80_CDECL __attribute__((cdecl))
#endif

// 0x0067db10 -- the unconditional first direct callee, reached from 0x0067dc83.
//
// Convention, from the callee's own listing (48 instructions, 0x0067db10..0x0067dbb9):
// it reads the receiver in ECX and never in a stack slot, and it ends at
// 0x0067dbb9 with a bare `RET` after `ADD ESP,0x10` -- no immediate, so it pops
// nothing of its own. Zero stack arguments, hidden receiver in ECX: thiscall.
//
// Return type `void`, which is the callee's own recorded prototype
// (`void __fastcall FUN_0067db10(undefined4 *param_1)`). Worth stating plainly:
// that listing's last write to EAX is the `MOV EAX,dword ptr [ECX]` at 0x0067db96
// that loads the dispatch word for the call at 0x0067db9b, so the register is
// scratch there and not a return value. Nothing in this body reads what it leaves
// in EAX, and 0x0067dc98 overwrites EAX on both paths.
//
// The descriptive part of the name -- "complete dtor" -- is a reading, not a
// record. What the callee's own instructions state is narrower and is what the
// name abbreviates: it installs an SEH frame (0x0067db10-0x0067db25), writes
// 0x1401798 into [ESI] at 0x0067db2d and 0x1401790 into [ESI+4] at 0x0067db33,
// walks a member-release sequence under the flags at [ESI+0x11] and [ESI+0x10],
// calls one entry of the object at [ESI+0x0c] through its dispatch word, and
// finally writes 0x13f3a68 into [ESI] at 0x0067dba1. An entry that resets a
// vtable and then a second, different one at the end is running a destructor
// chain; that is the whole basis for the word "dtor" in this name.
extern "C" void PKG_DFW_0067DC80_THISCALL
imessage_manager_complete_dtor_0067db10(OpaqueMessageManagerBlock *receiver);

// 0x00f47380 -- the conditional second direct callee, reached from 0x0067dc90.
//
// Convention, from the callee's own listing (7 instructions, 0x00f47380..0x00f47394):
// it reads its only argument at [ESP + 0x4] (0x00f47380), tests it, and ends at
// 0x00f47394 with a bare `RET` -- no immediate, so the caller owns the argument.
// That is what makes the `ADD ESP,0x4` at 0x0067dc95 part of this body rather
// than part of the callee: one pushed word, one cdecl argument, caller-cleaned.
//
// Return type `void`, again the callee's own recorded prototype
// (`void FUN_00f47380(int param_1)`). Its listing does leave the argument word in
// EAX across the `RET`, which is the same scratch-register pattern noted above;
// this body overwrites EAX at 0x0067dc98 and never reads it.
//
// The descriptive part of the name -- "global release" -- is a reading of the
// callee's own instructions: 0x00f47388 loads a dword from the absolute address
// 0x016c8b44, pushes the argument and calls 0x009276c0, and the whole thing is
// skipped when the argument is zero (0x00f47386). So it is a null-guarded release
// routed through one process-global pointer. No record for this target names what
// that global or 0x009276c0 is, and nothing here claims to.
extern "C" void PKG_DFW_0067DC80_CDECL
imessage_manager_global_release_00f47380(OpaqueMessageManagerBlock *block);

}  // namespace openspore::reconstruction::pkg_dfw_0067dc80
