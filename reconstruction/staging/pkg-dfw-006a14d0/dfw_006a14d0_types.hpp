// PKG-DFW-006A14D0 -- VA 0x006a14d0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x00400000)
//
// Boundary types and declarations for the reconstruction of
// App::PropertyList::CopyAllPropertiesFrom at 0x006a14d0.
//
// This header declares no member and no field. No record for this target names a
// class, a member, a field or a slot semantic: the knowledge index carries
// class_type = null and types = ["void"], the Ghidra prototype resolves to
// "void App::PropertyList::CopyAllPropertiesFrom(PropertyList *, PropertyList *)"
// with the class name imported from the Spore-ModAPI symbol XML rather than from
// anything in the binary (SporeApp.exe carries no MSVC RTTI), and the ABI record
// enumerates a receiver displacement set without saying which member is which.
// So every access below is stated as a machine displacement, and the two object
// types here are deliberately incomplete: they exist to keep the two pointer
// roles the body distinguishes apart at compile time, and to say nothing about
// layout.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-006a14d0 requires an x86-32 target"
#endif

// Portable calling-convention spellings.
//
// __thiscall is machine-derived for this target from two independent facts in the
// listing, and not from the decompiler, which reports "Unknown calling convention"
// and gives the function no convention at all:
//   (1) the receiver arrives in ECX and is dereferenced through the ESI alias
//       0x006a14d6 makes of it, at 0x006a14dc and 0x006a14f1, before any definite
//       write to ECX; and
//   (2) the terminator is RET 0x4 at 0x006a1506, a callee-cleaned four-byte pop,
//       which excludes cdecl and fastcall.
// So the convention carries a hidden receiver in ECX and one ordinary stack word
// at entry_ESP+0x4, and the callee owns the cleanup. That is exactly what
// __attribute__((thiscall)) means on GCC/Clang for -m32 and what __thiscall means
// on MSVC, so the same argument count is right on both toolchains and the caveat
// about a bare-RET body does not arise for this VA.
#if defined(_MSC_VER)
#define PKG_DFW_006A14D0_THISCALL __thiscall
#define PKG_DFW_006A14D0_CDECL __cdecl
#else
#define PKG_DFW_006A14D0_THISCALL __attribute__((thiscall))
#define PKG_DFW_006A14D0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_006a14d0 {

using Word = std::uint32_t;

// The receiver of 0x006a14d0 and the single ordinary stack argument it is given.
// The SDK symbol the target is named after spells this class "PropertyList"; the
// spelling here is this package's own and claims no members. Two machine facts are
// the only ones claimed: the body's first operand-level read of the receiver is
// the dword at displacement 0x00, which it then uses as the base of a table of
// 4-byte words (0x006a14f1 MOV EAX,dword ptr [ESI]), and the object at that base
// is never written through.
struct OpaquePropertyList;

// The word the receiver holds at displacement 0x30 (0x006a14dc
// MOV ECX,dword ptr [ESI + 0x30]).
//
// This is deliberately NOT given the name Ghidra's decompiled output prints for
// it. The imported SDK structure calls that word "mpParent" and the decompiled
// body prints "pPVar1", but that name is derived from the imported
// SporeGhidra_march2017 symbol XML and not from anything in the binary, and the
// evidence pack's own unresolved_questions say so. What the listing does support
// is narrower and is all that is claimed here: the word is 4 bytes wide, it is
// compared against zero and the body skips a block when it is zero, and when it
// is not zero it is dereferenced as a table of 4-byte words and dispatched through
// that table's word at displacement 0x04 with no stack argument (0x006a14ea
// MOV EAX,dword ptr [ECX] / 0x006a14ec MOV EDX,dword ptr [EAX + 0x4] /
// 0x006a14ef CALL EDX). The two vtable images this body is installed in both hold
// 0x00432b50 at displacement 0x04, and that callee's own listing opens with
// "MOV dword ptr [EBP + -0x10],ECX" (0x00432b56), so the object really is handed
// to a receiver-taking callee. What it IS -- a parent, an owner, a back-link -- is
// not established by any record for this target and is not asserted here.
struct OpaqueVtableObject;

// The two control transfers this body makes are indirect: it loads a 4-byte word
// out of a table and transfers control to the address that word holds
// (0x006a14ef, 0x006a14f8 and 0x006a1502, all three "CALL EDX"). The listing
// fixes the arity of each of the three -- no stack word is pushed for the first
// two, exactly one is pushed for the third -- but it does not fix the callee's own
// prototype: no record for 0x00432b50, 0x006a2a80, 0x006a2b20 or 0x006a1510 gives
// this target a calling convention, and each of the four is dispatched by this
// target rather than called directly by it, so each is reached from more than one
// caller with unknown expectations.
//
// So the transfer is modelled by handing the ADDRESS to a bridge, not by calling
// through a function pointer. That is a model device and it is stated as one: the
// datum this body actually produces at 0x006a14ec/0x006a14f3/0x006a14fc is an
// address, and a portable __thiscall function-pointer type cannot be spelled for
// an unknown callee without inventing a signature. The bridges carry the address,
// so a test still sees exactly which address the body chose, on which object, and
// with how many arguments.
extern "C" void PKG_DFW_006A14D0_CDECL dispatch_through_slot_0(void *target_address,
                                                                void *receiver);

// The one-argument form, for the transfer at 0x006a1502, which is preceded by the
// single PUSH EDI at 0x006a14ff.
extern "C" void PKG_DFW_006A14D0_CDECL dispatch_through_slot_1(void *target_address,
                                                                void *receiver,
                                                                void *argument);

}  // namespace openspore::reconstruction::pkg_dfw_006a14d0
