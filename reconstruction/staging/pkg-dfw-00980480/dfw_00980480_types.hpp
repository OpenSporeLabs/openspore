// PKG-DFW-00980480 -- VA 0x00980480
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Boundary types for the reconstruction of 0x00980480. The complete machine body
// is two instructions and eight bytes:
//
//   00980480  83 e9 04        SUB ECX, 0x4
//   00980483  e9 a8 fe ff ff  JMP 0x00980330
//
// (bytes read back from the binary this session: 83 e9 04 e9 a8 fe ff ff, so the
// rel32 0xfffffea8 taken from 0x00980488 lands on 0x00980330 exactly).
//
// Because the body names no class, no member, no layout and no interface, this
// header declares no member and no struct. Two decisions carry the whole surface
// and both are stated here rather than left implicit:
//
//   1. The receiver is an opaque pointer, not `PerspectiveEffect *`. The Ghidra
//      signature on this address is
//      `bool UTFWin::PerspectiveEffect::HandleUIMessage(PerspectiveEffect *this,
//      IWindow *pWindow, Message *message)`, and the triage record carries the
//      same SDK name. That name is nevertheless not adopted here, because the
//      machine contradicts the rest of the same signature: the tail callee pops
//      exactly one stack word (`RET 0x4` at 0x0098034b and 0x00980350), so the
//      body cannot be the two-argument virtual the SDK documents, and the
//      unresolved question already recorded against this target says exactly
//      that ("either the SDK signature is a documentation-only entry or the
//      Ghidra symbol at 0x00980480 is attached to the wrong body"). Adopting the
//      class would also mean adopting the arity the machine refutes, so the
//      receiver stays opaque and the class name is carried in the sidecar as a
//      recorded, unadopted claim.
//
//   2. The single stack word is an opaque 32-bit value, not `Message *`. The word
//      is never dereferenced by anything in this body, and the one record that
//      constrains it -- the tail callee's own listing, which loads it
//      (`MOV EAX,dword ptr [ESP + 0x4]` at 0x00980330) and compares it against
//      the immediate 0xef865d7e (`CMP EAX,0xef865d7e` at 0x00980334) -- treats
//      it as a value, not as a pointer. The SDK's `Message *` label is a
//      documentation claim and is not carried into the model.
//
// The receiver adjustment is the one constant this package states, and it is
// stated as the literal 0x4 in the model body rather than hoisted into a named
// constant, so the constant is the machine constant and not this package's name
// for it. 0x4 is a machine displacement on the address, not a field offset: the
// body never dereferences anything, so nothing here is a member access.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-00980480 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_dfw_00980480 {

// The record's own return_type token, spelled so the declared return type is
// that token verbatim: the persisted ABI record for this VA says
// return_type "Opaque*" with return_semantics "delegated result in EAX,
// forwarded verbatim from 0x00980330". No record for this target says what the
// forwarded word points at, so the pointee is the only honest type for it and
// `Opaque*` resolves to void*.
//
// The live Ghidra record disagrees, and the disagreement is deliberate and
// unresolved rather than smoothed over: ghidra_function reports return_type
// "bool" and the decompilation renders `bool bVar1 = (bool)FUN_00980330();`.
// The machine never normalises a byte -- the tail callee materialises
// `LEA EAX,[ECX + 0xc]` (0x00980348) or `XOR EAX,EAX` (0x0098034e) and returns
// that word through `RET 0x4`, so an arbitrary 32-bit value can arrive in EAX
// and no byte-normalising instruction exists anywhere on the path. The model
// therefore follows the machine and returns the record's own opaque word.
using Opaque = void;

// The one 4-byte stack word this body forwards untouched. It is the caller's
// word, not one this body pushes: the listing has no PUSH at all, and the ABI
// record places exactly one stack word with stack_cleanup_bytes 4 and
// stack_cleanup_owner "callee" -- the tail callee pops it, not this body.
using MessageWord = std::uint32_t;

// The calling conventions below are spelled per toolchain. GCC and clang reject
// the MSVC convention keywords outright, so the x86-32 form is the only one that
// compiles here; both spellings are kept so the declaration says what it means
// on either toolchain.
//
// thiscall is the reading, not stdcall or cdecl: the persisted ABI record says
// "x86-32 thiscall with the receiver in ECX and one 4-byte stack word, popped by
// the tail callee", and the receiver is independently corroborated by the tail
// callee, which null-checks the pointer it inherits in ECX before using it
// (`TEST ECX,ECX` at 0x00980344 / `JZ` at 0x00980346) and only then forms
// `receiver+0x0c` from it (`LEA EAX,[ECX + 0xc]` at 0x00980348). thiscall is
// also the only convention whose callee-side stack cleanup matches the record's
// "popped by the tail callee": with one stack word the callee reclaims 4 bytes,
// exactly the stack_cleanup_bytes the record states. That cleanup is not an
// assumption about the source -- `g++ -m32` and `clang++ -m32` both emit
// `ret $4` for a `thiscall` function with one 32-bit stack word, which is what
// the callee's own `RET 0x4` on both exits does.
//
// cdecl is declared only so the package can name a caller-cleaned transfer if a
// future target in this family needs one. Nothing in this package uses it.
#if defined(_MSC_VER)
#define PKG_DFW_00980480_THISCALL __thiscall
#define PKG_DFW_00980480_CDECL __cdecl
#else
#define PKG_DFW_00980480_THISCALL __attribute__((thiscall))
#define PKG_DFW_00980480_CDECL __attribute__((cdecl))
#endif

// 0x00980480, the entry point of this package. The symbol embeds the target VA so
// the address is recoverable from the name alone, which is the convention the
// static validator binds a target span on.
//
// The first parameter is the receiver in ECX. The second is the single stack
// word, which this body forwards and never touches; it is declared so the model
// can express the pass-through as an argument rather than by reading the
// caller's frame, which a C++ function cannot honestly do.
//
// The symbol name keeps the `HandleUIMessage` words of the SDK/Ghidra name on
// purpose: the index record names this target
// "UTFWin::PerspectiveEffect::HandleUIMessage", and keeping the words lets the
// static validator bind its own record to this span. It is a name only -- no
// behavioural claim about handling a UI message is made or implied anywhere in
// this package.
extern "C" Opaque* PKG_DFW_00980480_THISCALL
handle_message_00980480(Opaque *entered_receiver, MessageWord forwarded_word);

// 0x00980330, the sole target of the tail transfer at 0x00980483. It is a
// different VA and is NOT reconstructed by this package: only its contract is
// declared here, and the focused model test supplies the observer that lets the
// pass-through behaviour be exercised.
//
// The contract is the three facts the tail callee's own live listing fixes, and
// nothing more:
//
//   0x00980330  MOV EAX,dword ptr [ESP + 0x4]   loads the one stack word
//   0x00980334  CMP EAX,0xef865d7e              compares it against an immediate
//   0x0098033f  JMP 0x00950eb0                  forwards it otherwise
//   0x00980348  LEA EAX,[ECX + 0xc]             answers with receiver+0x0c ...
//   0x0098034b  RET 0x4                          ... and pops the one word
//   0x0098034e  XOR EAX,EAX                      ... or with zero
//   0x00980350  RET 0x4
//
// Two of those matter to this package's declaration. First, the callee reclaims
// the stack word itself (RET 0x4 on both exits), so it is a one-stack-word
// callee-cleaned convention -- thiscall on x86-32 -- not a cdecl one. Second, its
// result is an unnormalised 32-bit word, which is why the return type above is
// the record's opaque pointer and not bool.
//
// The immediate 0xef865d7e is recorded here as a property of the callee, not
// asserted about this body: this body never compares anything.
extern "C" Opaque* PKG_DFW_00980480_THISCALL
tail_00980330(Opaque *adjusted_receiver, MessageWord forwarded_word);

static_assert(sizeof(MessageWord) == 4, "the forwarded stack word is 4 bytes");
static_assert(sizeof(void *) == 4, "x86-32 pointers are 32-bit");

}  // namespace openspore::reconstruction::pkg_dfw_00980480
