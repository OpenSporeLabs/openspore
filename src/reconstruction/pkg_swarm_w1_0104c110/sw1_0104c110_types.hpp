// PKG-SWARM-W1-0104C110 -- VA 0x0104c110
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_0104c110 @ 0x0104c110, a two-instruction,
// seven-byte member function that is reconstructed here in full: the whole body
// is two instructions and both are reproduced by the model.
//
//   0x0104c110   8B 81 10 02 00 00    MOV EAX, dword ptr [ECX + 0x210]
//   0x0104c116   C3                   RET
//
// SIX MACHINE FACTS, each read out of those seven bytes and each labelled with
// the record it came from:
//
//  1. LENGTH. The body is 0x0104c110..0x0104c116 inclusive, so 7 bytes
//     (ghidra_function.body_span_bytes = 7, entry_point 0x0104c110, body_end
//     0x0104c116). The machine parse is not a slice: abi_derived.parse declares
//     exactly 2 instructions, degraded = false, unparsed = 0, flow_complete =
//     true, local_extent = 0. A body the parse consumed whole is the evidence
//     that there is no third instruction hiding after the RET.
//
//  2. TERMINATOR FORM. The last byte is C3 -- a near return carrying NO imm16.
//     It is not `C2 00 00` and not `C2 nn nn`: the return pops only the return
//     address, so the callee removes zero argument bytes. The derived record
//     agrees (abi.termination "RET", abi.ret_form "RET", cleanup.bytes = 0,
//     cleanup.evidence "ret with no immediate, no stack reads").
//
//  3. NO STACK ARGUMENTS, hence caller-side cleanup. Neither of the two
//     instructions names ESP or EBP in any operand, so the body reads no
//     argument slot: there is nothing at [ESP+4] for it to read, and it spills
//     nothing either. A thiscall member function with ordinary arguments could
//     not look like this. So the whole argument surface is the hidden receiver
//     and the caller owns the stack -- the same conclusion the record reaches
//     (stack_cleanup_bytes 0, stack_cleanup_owner "caller").
//
//  4. THE RECEIVER IS READ AND IS NEVER WRITTEN. 0x0104c110 reads ECX exactly
//     once (abi_derived.observations obs-0001, kind REG_READ, count 1), and the
//     machine-derived receiver record carries shape "R-DIRECT", one distinct
//     displacement (528 = 0x210) and written_through = 0.
//     This is the fact the reconstruction turns on, and it cuts off both ways
//     that a two-instruction body is easy to get wrong:
//
//       * it is NOT a constant stub. There is no immediate, no constant load
//         and no arithmetic: the only operand is a memory read through the
//         receiver, so the returned value is whatever the receiver's memory
//         holds. A model that returned a literal, a default, or a cached
//         constant would be refuted by any receiver whose +0x210 word differs.
//       * it is NOT a pure register trampoline or a thunk. The value comes out
//         of the receiver's memory, and nothing is written back, so the body is
//         a single-field accessor and nothing more.
//
//  5. THE RETURNED VALUE IS FOUR BYTES OF RECEIVER MEMORY, CARRIED IN EAX.
//     obs-0002 records EAX written at index 0 with write_kind "mem_load" and
//     definite = true, and obs-0003 records the RET at index 1. So the last and
//     only definition of EAX before the return is a 32-bit load out of
//     [ECX + 0x210], and no CALL sits between it and the RET. The width 4 is
//     machine evidence (return.register "EAX", return.aggregate_evidence
//     .bulk_write = false, sret.present = false, return.void_possible = false);
//     the C spelling of that width is a source-side choice, made once, below.
//
//  6. NO CALL, NO DISPATCH, NO BRANCH, NO GLOBAL. The xref export records zero
//     outgoing edges for this VA (callees [], external_callees [],
//     dependencies.edges holds only the two incoming call edges);
//     abi_derived.dispatch is indirect_calls 0, call_offsets [], vtable_shaped
//     _loads 0; and the two-instruction listing contains no conditional branch,
//     no jump and no call, so the body is straight-line by the listing's own
//     evidence rather than by assumption. The xref export also carries no
//     data-reference edge type at all (dependencies.data_reference_count = 0),
//     which is why the absence of a global is claimed from the listing alone.
//
// WHAT IS NOT FIXED, AND IS THEREFORE NOT CLAIMED:
//
//  * THE ELEMENT TYPE of the returned word. The machine fixes the width and
//    nothing about meaning: abi_derived.return.type is null, its register_class
//    is the inference string "pointer_like", and its confidence is INFERRED.
//    FieldWord below carries the width and deliberately asserts nothing about
//    what the 32 bits are. See the caller evidence immediately after this list.
//
//  * THE NAME of the member at +0x210, and the name of the class. The triage
//    record for this VA carries sdk_name = null and the Sporepedia cluster
//    label is a classifier output, not a symbol, so no member is named anywhere
//    in this package. The receiver below is an opaque byte run on purpose.
//
//  * THE SIZE of the receiver beyond 0x214. The body reads bytes 0x210..0x213
//    and that is the only bound this package asserts, so the receiver is
//    modelled as exactly 0x214 bytes. The real object is larger -- the one
//    caller also touches +0x60, +0x64 and +0x7c on it -- but nothing in the
//    evidence fixes its extent, and a wider struct here would be invented.
//
// CALLER-SIDE EVIDENCE, recorded because it is the only thing in the whole set
// that touches anything else on the receiver, and because it bears on the one
// open question above. The xref export records exactly one direct caller,
// FUN_00ff3df0, with two callsites, 0x00ff3e26 and 0x00ff3e3c:
//
//    00ff3e1b  MOV EAX,dword ptr [ESI]              the receiver's first dword
//    00ff3e1d  MOV EDX,dword ptr [EAX + 0x4]        is read as a pointer
//    ...
//    00ff3e24  MOV ECX,ESI
//    00ff3e26  CALL 0x0104c110                      (1) result tested SIGNED
//    00ff3e2b  TEST EAX,EAX
//    00ff3e2d  JLE  0x00ff3e55
//    ...
//    00ff3e3a  MOV ECX,ESI
//    00ff3e3c  CALL 0x0104c110                      (2) result stored
//    00ff3e41  MOV dword ptr [ESI + 0x7c],EAX
//
// That is ONE caller out of two call edges. `JLE` is a signed compare, which
// fits a signed 32-bit quantity better than it fits a pointer, and the result is
// stored into a 4-byte member of the same object rather than used as an
// address. Both readings are still available to the evidence, so the element
// type stays open; the model asserts the bit pattern and the width, and nothing
// else. The caller also confirms the receiver is a heap object with a leading
// pointer-shaped word, which is why the receiver type below is named for what
// is known about it and not for a class.
//
// VTABLE ASSOCIATION, used as a mapping and never as a member claim. The 4-byte
// value stored at 0x01490bfc is 0x0104c110, read straight out of the image, and
// 0x01490bfc - 0x01490be8 = 0x14 -- so this body is the slot at displacement
// +0x14 of the table whose first slot is at 0x01490be8, which is the table the
// triage record associates with this VA (vtable:0x01490be8). Slot +0x08 of that
// same table holds 0x00641770, whose own body is three bytes long and reads
// `MOV EAX,[ECX+0x28]; RET` -- the same single-field accessor idiom, encoded in
// three bytes because 0x28 fits in a signed displacement byte and 0x210 does
// not. That corroborates the SHAPE of this body and nothing about its meaning,
// and it is deliberately not read as "the same method under another name":
// two different offsets of the same object, returned the same way, are two
// different accessors.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-0104c110 requires an x86-32 target"
#endif

// The calling convention, spelled once. Both facts it rests on are machine
// evidence above: the receiver arrives in ECX and is dereferenced before
// anything is written through it (fact 4), and the terminator is a bare C3 with
// no imm16, so the callee removes no argument bytes (fact 2). The derived record
// lists __thiscall and __fastcall as its two candidates; __fastcall is the one
// that does not fit, and the reason is measurable rather than stylistic: a
// __fastcall member function would take a second register argument in EDX, and
// this body never reads EDX, and more to the point a function whose entire
// body is one memory read has no second argument to pass. The record's own
// convention confidence is INFERRED, so this is an INFERRED convention and the
// sidecar says so.
//
// GCC 16 rejects the bare MSVC keywords, so the attribute form is the portable
// spelling and the keyword form is kept for MSVC.
#if defined(_MSC_VER)
#define PKG_SW1_0104C110_THISCALL __thiscall
#else
#define PKG_SW1_0104C110_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_0104c110 {

using Word = std::uint32_t;

// The returned word. It is 4 bytes wide because the only definition of EAX
// before the RET is a dword load (fact 5), and it is spelled as an opaque alias
// rather than as uint32_t so that nothing in this package can be read as a claim
// that the 32 bits are unsigned, or an integer, or a pointer. The one caller
// tests the result with a signed JLE, the machine classifies the register as
// "pointer_like" and the record's own element type is null; all three of those
// are in tension and the model sides with none of them. The model test asserts
// the bit pattern and the width, and states that it asserts no meaning.
using FieldWord = Word;

// The seven bytes of the original body, in address order, as read out of the
// image. Kept here so the encoding is documented next to the types rather than
// only in prose, and so the model test can assert against it.
//
//   8B 81 10 02 00 00   MOV EAX, dword ptr [ECX + 0x210]
//   ^^^^^^ mod = 10 (disp32), reg = 000 (EAX), rm = 001 (ECX)
//                         10 02 00 00 = displacement 0x210
//   C3                  RET, no imm16
//
// The disp32 form is used here and the disp8 form in the 0x00641770 sibling
// (see the header note) precisely because 0x210 does not fit in a signed
// displacement byte; that is why this accessor is six bytes of MOV where the
// other is three.
inline constexpr std::uint8_t kOriginalEncoding[7] = {0x8b, 0x81, 0x10, 0x02,
                                                       0x00, 0x00, 0xc3};

// The one displacement the body uses: 0x210 = 528. It is the single entry of
// the machine-derived receiver record (receiver.offsets = [528], distinct_offsets
// 1, max_offset 528) and the single displacement the listing's own operand names
// through ECX, so the two machine witnesses agree exactly.
constexpr std::size_t kReceiverFieldDisplacement = 0x210;

// The receiver. Deliberately opaque: the body reads one 4-byte member at
// 0x210 and touches no other byte, so this declares NO member at all. Naming
// the word at 0x210 -- a count, an id, a flag word, a pointer -- would be a
// member story that a two-instruction listing cannot support, and the receiver
// record is explicit that it states where the body was seen reaching and not
// which member is which (bounds_only = true).
//
// 0x214 bytes is the whole of the claim: 0x210 + 4 is the last byte the body
// reads. The real object is larger -- the one caller also writes +0x7c on it --
// and that is not modelled, because nothing here fixes the extent.
//
// This is also why the model reaches the field through a displacement helper
// rather than through `receiver->member`: a member access would assert an
// identity the evidence does not carry, and it is also the shape that makes the
// one-level dereference of fact 4 explicit rather than implicit.
struct alignas(4) OpaqueVtableOwner {
  std::array<std::uint8_t, 0x214> opaque_00{};
};
static_assert(sizeof(OpaqueVtableOwner) == 0x214,
              "0x210 + 4 is the last byte the body reads, and it is the whole claim");
static_assert(kReceiverFieldDisplacement + sizeof(Word) == sizeof(OpaqueVtableOwner),
              "the field at 0x210 ends the modelled receiver exactly");

// The only way the reconstructed body touches the receiver: a word at a stated
// displacement. One dereference, on the receiver pointer itself -- the machine
// reads [ECX + 0x210], which is the receiver's own memory, not the memory of
// anything the receiver points at.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// -- direct callees -----------------------------------------------------------
// NONE, and this is a machine fact rather than an omission. The xref export
// records no outgoing edge for this VA and the listing holds no CALL, no JMP
// and no indirect transfer, so there is no callee to declare here. The model
// test still defines an observer for every transfer the body could make -- there
// is none to define, and the test asserts that count is zero rather than
// leaving it unsaid.
//
// FUN_0104c110 @ 0x0104c110.
//
// __thiscall, receiver in ECX, no ordinary stack arguments, bare `RET` (C3) with
// no immediate, and a 4-byte value returned in EAX. The whole body is one
// 32-bit load out of the receiver at displacement 0x210.
//
// The return type is FieldWord, an opaque 4-byte alias: the width is machine
// evidence and the element type is not (see the header note on the one caller
// and on return.type being null). Nothing here declares an argument, because
// the body reads none (fact 3).
extern "C" FieldWord PKG_SW1_0104C110_THISCALL re_0104c110(
    OpaqueVtableOwner* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_0104c110
