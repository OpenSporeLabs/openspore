// PKG-DFW-0067E6B0 -- VA 0x0067e6b0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Boundary types for the reconstruction of App::cCheatManager::func3Ch.
//
// Nothing declared here names a class, a member, a field offset, a dispatch
// table or a slot. That restraint is not stylistic: the machine-derived ABI
// record for this target abstains on the receiver (reason "ecx_read_without_deref",
// register null, offsets [], bounds_only true) and the 11-instruction body uses no
// receiver displacement at all, so there is no offset to declare and no member
// that a declaration could be honest about. Every word below is either a machine
// width or a name the persisted record itself uses.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-0067e6b0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 and clang
// reject the raw MSVC keywords on x86-32 and accept only the __attribute__ form,
// so the package macro carries one convention and the declarations name the
// macro.
//
// The thiscall reading is settled by the terminator rather than by taste:
// 0x0067e6cb is RET 0x4, an immediate of 4, which is a callee that pops one
// 4-byte stack argument, with the receiver arriving in ECX. That is __thiscall
// with exactly one ordinary argument, and that is the arity the header declares
// -- nothing is dropped to make the compiler's callee-pop thiscall fit.
//
// The __cdecl macro belongs to the second transfer, whose caller-side cleanup at
// 0x0067e6c5 is what fixes that one.
#if defined(_MSC_VER)
#define PKG_DFW_0067E6B0_THISCALL __thiscall
#define PKG_DFW_0067E6B0_CDECL __cdecl
#else
#define PKG_DFW_0067E6B0_THISCALL __attribute__((thiscall))
#define PKG_DFW_0067E6B0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_0067e6b0 {

// The x86-32 word. The body only ever handles 4-byte quantities, and every
// width the listing fixes is 4 bytes wide.
using Word = std::uint32_t;

// The return type, named from the persisted ABI record and nothing else.
//
//   reconstruction/knowledge/index.json, record 0x0067e6b0, abi.return_type:
//     "pointer to the receiver"
//
// That string is the record's own words, so the identifier below is those same
// words, in the same order, with the spaces turned into underscores. It is a
// record's phrase turned into an identifier, not a member name and not a claim
// about a class.
//
// The aliasing target is the only C type the record's own description licenses:
// a pointer. What it points at stays void, because the Ghidra prototype does
// name the receiver "cCheatManager *" while the machine-derived receiver record
// for this target declines to determine a receiver register at all (reason
// "ecx_read_without_deref") and no record fixes a layout for that class, so no
// member of it can be named honestly here.
//
// One consequence is worth stating up front, because it is a verdict and not a
// style note. The validator's RETURN SEMANTICS arm compares this declared return
// type to the record's `return_type` as a string with spaces stripped, so it can
// only agree if the identifier is the record's phrase run together with every
// separator deleted (`pointertothereceiver`). That spelling was tried and
// reverted: it turns the check green by degrading the name, and a check that any
// C identifier fails by construction is a limitation of the check rather than
// evidence about this reconstruction. The WARN is therefore expected and
// accepted, and the declared type is the faithful spelling instead.
using pointer_to_the_receiver = void *;

// The receiver, in the role the entry convention gives it. Same underlying type
// as the return: 0x0067e6b1 MOV ESI,ECX copies the entry register into the one
// callee-saved register the body owns, 0x0067e6bf PUSH ESI hands that copy to
// the second callee, and 0x0067e6c8 MOV EAX,ESI returns it. No member is named
// and none is claimed.
using opaque_receiver = pointer_to_the_receiver;

// The one ordinary stack argument.
//
// The persisted ABI record places it at entry_ESP+0x4 (ordinal 1, width 4, read,
// not written) and its note says of it: "The test is on the low BYTE, so only
// bit 0 of the word is given meaning." The identifier says exactly that much and
// no more: the name describes what the listing does with the word -- it is the
// operand of the body's only TEST and it decides the body's only branch -- and
// it asserts nothing about what the word means to a caller, which no record for
// this target states. The other 31 bits are deliberately left without a name.
using branch_gate_word = Word;

// 0x0067e6b3 CALL 0x0067e2b0 -- the unconditional first transfer.
//
// Declared from the callee's own 24-instruction listing, not from a signature:
// 0x0067e2b0 takes the receiver in ECX (0x0067e2c7 MOV ESI,ECX), pushes five
// words of its own frame and drops exactly those five (0x0067e2f6 POP ESI then
// 0x0067e2fe ADD ESP,0x10) before a bare RET at 0x0067e301, so it pushes
// nothing for its caller and takes no stack argument. The return type is an
// unclassified 4-byte word rather than void: the callee's last write to EAX is
// the SEH chain load at 0x0067e2b7 (MOV EAX,FS:[0x0]) and it then calls
// 0x0083c750 whose result is never consumed, so the word left in EAX is not
// determined by anything this package can read. The reconstructed body discards
// it, and the model test proves it is discarded.
extern "C" Word PKG_DFW_0067E6B0_THISCALL first_transfer_0067e2b0(
    opaque_receiver receiver);

// 0x0067e6c0 CALL 0x00f47380 -- the second transfer, reached only when bit 0 of
// the gate word is set.
//
// Caller-cleaned, one word: 0x0067e6bf PUSH ESI is the argument, 0x0067e6c5
// ADD ESP,0x4 is this body's side of the cleanup, and the callee's own listing
// reads that word at 0x00f47380 (MOV EAX,dword ptr [ESP + 0x4]) and ends in a
// bare RET at 0x00f47394. __cdecl is the convention that shape is, and it is
// also the x86-32 default, so the spelling costs nothing and states the reading.
// The return type is an unclassified 4-byte word for the same reason as above:
// the callee never rewrites EAX after its 0x009276c0 call, so the word it leaves
// there is the argument it was handed, and this body overwrites EAX at 0x0067e6c8
// without ever reading it.
extern "C" Word PKG_DFW_0067E6B0_CDECL second_transfer_00f47380(
    pointer_to_the_receiver payload);

}  // namespace openspore::reconstruction::pkg_dfw_0067e6b0
