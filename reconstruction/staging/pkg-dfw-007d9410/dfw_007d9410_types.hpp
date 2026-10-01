// PKG-DFW-007D9410 -- VA 0x007d9410
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  binary SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Opaque boundary types for the reconstruction of the body at 0x007d9410.
//
// Scope of the evidence, stated before anything is typed: the committed pack
// reconstruction/evidence/007d9410/ carries a COMPLETE two-instruction listing for
// this address and no other body:
//
//   007d9410  SUB ECX,0x4
//   007d9413  JMP 0x007d9bb0
//
// (ghidra_function: body_start 0x007d9410, body_end 0x007d9417, body_span_bytes 8,
// size_bytes 8; disassembly count 2; the same two instructions were re-read
// read-only from the live bridge during this session.)
//
// No record for this target names a class, a member, a dispatch table or a slot.
// The binary carries no MSVC RTTI, this body has no indirect transfer, and
// abi_derived.receiver records present=false, register=null, offsets=[] -- the
// derivation saw ECX written and never read, so it declined to call ECX a
// receiver. Therefore nothing below carries a member name, a field, a size or a
// layout. The two pointer types exist only because the machine itself makes a
// distinction here: the pointer that ARRIVES and the pointer this body HANDS ON
// differ by a fixed four bytes, and the body never dereferences either one.

#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-007d9410 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. The x86-32 attribute
// is what the persisted ABI record for this target asserts (calling_convention
// "__thiscall"); it is not the same token on both compilers, and GCC rejects the
// MSVC keyword outright, so the macro is the only portable spelling and both the
// declarations here and the definition in the .cpp name it.
#if defined(_MSC_VER)
#define PKG_DFW_007D9410_THISCALL __thiscall
#define PKG_DFW_007D9410_CDECL __cdecl
#else
#define PKG_DFW_007D9410_THISCALL __attribute__((thiscall))
#define PKG_DFW_007D9410_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_007d9410 {

// A four-byte machine word, used for the one ordinary stack argument this frame
// carries past its tail transfer. It is spelled as a word, not as a type, because
// no record for this target says what the argument is: see the note on the
// argument of mouse_camera_on_key_down_007d9410 below.
using Word = std::uint32_t;

// The return word of this body.
//
// What the machine record actually says about it: the derived ABI envelope
// (abi_derived) records return.register=null, return.register_class="unknown",
// return.type=null and return.confidence="UNKNOWN", i.e. the derivation could
// not even name the register, and its whole verdict is ABI_UNKNOWN, abstained
// with "no_terminal_ret: the only exit observed is a tail jump". The persisted
// ABI record separately claims return_register "EAX" and return_type "bool",
// and the SDK/Ghidra prototype stored on the symbol agrees on bool. Those two
// are records about the DECLARATION SITE -- the slot this body is reached
// through -- and not about anything this body computes: it writes no register
// other than ECX and executes no comparison, so on this listing it has no
// opportunity to produce, normalise or reject a boolean. The model therefore
// forwards the tail target's word under the derived record's own classification
// language and claims nothing about its width beyond what the four-byte register
// arithmetic of the argument word already implies.
//
// The honest cost of that choice is recorded in the package sidecar: a validator
// comparing this source's return type against the persisted "bool" reports a
// WARN, and it should.
using unclassified_in_EAX = Word;

// The pointer that arrives in the entry register.
//
// 007d9410 SUB ECX,0x4 subtracts four from it and the result is what the body
// transfers onward. No record names what it points at, and the body never reads
// through it, so the type is left incomplete: there is no member to name and no
// size to claim. Calling it a "subobject" is a record-level reading only -- the
// persisted ABI record's hidden_receiver field says "ECX holds a pointer to the
// subobject that carries the OnKeyDown virtual; the entry rewinds it to the
// cMouseCamera start" -- and that record's provenance is the knowledge index, not
// the machine; the -4 is the only part of it this listing establishes.
struct OpaqueEnteredReceiver;

// The pointer this body hands to its tail target, four bytes below the one that
// arrived. Kept a distinct incomplete type for the same reason the two values
// are distinct in the machine: the adjustment is the entire content of the body,
// and collapsing the two pointers into one type would hide it.
struct OpaqueReceiver;

// 0x007d9bb0 -- the one address this body transfers control to, reached only by
// the jump at 0x007d9413.
//
// It is NOT part of this package: 0x007d9410 is the target, and the evidence pack
// for it covers no listing of 0x007d9bb0. What is claimed about that address here
// is only the contract the caller side of this body needs, and that contract is
// read off the JMP itself plus the persisted ABI record's ret_form field:
//
//   * it is entered in ECX, carrying the value ECX held after 0x007d9410;
//   * this body pushes nothing before the jump and adjusts nothing after it, so
//     the argument word the caller of 0x007d9410 pushed is still in place when
//     the target runs. The persisted record fixes that surface at exactly one
//     ordinary stack argument slot (ordinary_stack_argument_slots: 1) and
//     describes the target's terminator as POP ESI / RET 0x4, which is what
//     consumes that one word;
//   * its return word is what this body returns, because the body runs no
//     instruction after the jump.
//
// The name below is this package's local alias for that address and asserts
// nothing about it. The return type is unclassified rather than bool for the
// reason given on that alias: no record in this repository gives 0x007d9bb0 a
// return type, so its word is forwarded without one.
extern "C" unclassified_in_EAX PKG_DFW_007D9410_THISCALL
tail_transfer_target_007d9bb0(OpaqueReceiver* receiver, Word argument_word);

// 0x007d9410 -- the reconstructed body.
//
// receiver: the entry register's value, spelled as a pointer only because the
//   instruction at 0x007d9410 does pointer-shaped arithmetic on it. Its incoming
//   meaning is NOT established by this listing: the derived record declines to
//   name a receiver register (abi_derived.receiver.present=false, register=null,
//   distinct_offsets=0, max_offset=null) precisely because the body writes ECX and
//   never reads it. The persisted ABI record calls ECX a hidden receiver; that is
//   recorded, and the model does not need it, because nothing here dereferences.
//
// argument_word: the single ordinary stack argument. This body reads it zero
//   times, so the model passes it on untouched; the one-slot width is fixed by
//   the persisted record (ordinary_stack_argument_slots: 1) and by that same
//   record's account of the target's RET 0x4, not by anything visible here. Its
//   IDENTITY is left open on purpose: the SDK/Ghidra prototype stored on this
//   symbol declares two stack slots, (int virtualKey, KeyModifiers modifiers),
//   while the machine shows one word being dropped. Nothing in this pack says
//   which of the two declared parameters this word is, so it is a Word. The
//   conflict is carried in the sidecar's unresolved_questions rather than settled
//   here.
//
// return: see unclassified_in_EAX.
extern "C" unclassified_in_EAX PKG_DFW_007D9410_THISCALL
mouse_camera_on_key_down_007d9410(OpaqueEnteredReceiver* entered_receiver,
                                  Word argument_word);

}  // namespace openspore::reconstruction::pkg_dfw_007d9410
