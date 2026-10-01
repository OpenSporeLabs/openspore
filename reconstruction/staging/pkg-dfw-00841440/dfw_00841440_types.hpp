#pragma once

// PKG-DFW-00841440 -- clean-room reconstruction of SporeApp.exe 0x00841440
// (Ghidra/SDK import name: ArgScript::FormatParser::CreateDefinitionSafe).
//
// Evidence basis, every item re-read from the live read-only Ghidra MCP bridge
// at http://127.0.0.1:8089 on the 3.1.0.22 image (x86:LE:32:default, cspec
// windows, image base 0x00400000, program SporeApp.exe,
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e):
//
//   * /disassemble_function 0x00841440 -> 11 instructions, 0x00841440..0x00841464
//   * /read_memory 0x00841440 40 bytes ->
//     8b542408 85d2 740f 8d42fc 894130 89542408 e929b3ffff
//     33c0 894130 89542408 e91bb3ffff cccccc                      (37 body bytes)
//   * /disassemble_function 0x0083c780 -> 5 instructions, the shared tail
//   * /read_memory 0x0083c780 16 bytes ->
//     8b442404 8b542408 894104 89510c c208                      (15 bytes)
//   * /disassemble_function 0x00844fb0 -> 231 instructions, the unsafe sibling
//     CreateDefinition, re-read here only to settle which stack slot carries
//     which parameter
//   * reconstruction/evidence/00841440/evidence.json (record abi, abi_derived,
//     disassembly, decompilation, ghidra_function, types, vtables)
//   * reconstruction/knowledge/index.json, record 0x00841440
//
// Nothing in this file is inferred from anything else. In particular:
//
//   * no member of the receiver is named, because no record for this target
//     names one: record abi.hidden_this_type records the SDK label
//     "FormatParser *" and immediately records the object as opaque because no
//     FormatParser vtable could be corroborated;
//   * no semantic meaning is attached to the word the body writes at
//     displacement 0x30. The arithmetic is observed; the purpose is not;
//   * no line layout is claimed: the second argument is never dereferenced by
//     this body, so OpaqueLine is deliberately left an incomplete type;
//   * record vtables lists the transitive association vtable:0x0141c0f4 while
//     the same record carries dependencies.vtable_reference_count 0 and this
//     body has no indirect transfer at all. The association is therefore not
//     used here to name a class, a table or a slot, and the model's two ordinary
//     stack words are addressed by machine displacement only.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-DFW-00841440 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");

// Portable spelling of the two conventions this package declares. GCC 16
// rejects the bare __thiscall / __cdecl spellings, so the attribute form is
// used off MSVC. The macro is left defined (not #undef'd at the end of this
// header) because the model test needs it on the extern declaration's
// definition as well, and a definition whose convention differs from its
// declaration would not link on i386.
#if defined(_MSC_VER)
#define PKG_DFW_00841440_THISCALL __thiscall
#define PKG_DFW_00841440_CDECL __cdecl
#else
#define PKG_DFW_00841440_THISCALL __attribute__((thiscall))
#define PKG_DFW_00841440_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_00841440 {

// One 32-bit machine word, the unit every transfer and every displacement in
// this body moves.
using MachineWord = std::uint32_t;

// The second ordinary stack argument, spelled by the SDK prototype
// CreateDefinitionSafe(FormatParser* this, char* pName, Line* argumentsLine).
//
// It is left INCOMPLETE on purpose. This body never dereferences it: it reads
// the word, subtracts 0x4 from the word, stores the word, and hands the word on.
// The unsafe sibling at 0x008450c6 loads its own second stack word into ECX and
// calls 0x00837f30 with it, which is why the word is pointer-like; nothing this
// package reads establishes a width, a field or an alignment for the pointee,
// so no layout is declared here and none is invented.
struct OpaqueLine;

// The receiver, ECX at 0x00841440.
//
// Only three displacements are proved, and each only because some instruction
// writes it:
//
//   +0x04   written by the shared tail 0x0083c780 with the FIRST stack word
//   +0x0c   written by the shared tail 0x0083c780 with the SECOND stack word
//   +0x30   written by THIS body (LEA EAX,[EDX-0x4] at 0x00841448 /
//           XOR EAX,EAX at 0x00841457, stored at 0x0084144b / 0x00841459)
//
// The machine-derived receiver record agrees exactly: register ECX, offsets [48],
// bounds_only true, written_through 2. That record states where the body was
// seen reaching and not which member is which, so the three words stay unnamed
// here and are reached only through the displacement constants below.
//
// sizeof is 0x34: the smallest extent that covers the highest displacement this
// package writes (0x30) plus one word. It is a modelling bound, not a claim
// about the object's real size; nothing here observes the object's extent and
// no record for this target states one.
struct alignas(4) OpaqueFormatParser {
  std::uint8_t opaque[0x34];
};

static_assert(sizeof(OpaqueFormatParser) == 0x34,
              "the model covers every displacement this package writes");

// Machine displacements, named after the instructions that write them and for
// no other reason. Each is a physical offset in the receiver, nothing more.
inline constexpr std::size_t kReceiverWord_04 = 0x04;  // 0x0083c788
inline constexpr std::size_t kReceiverWord_0c = 0x0c;  // 0x0083c78b
inline constexpr std::size_t kReceiverWord_30 = 0x30;  // 0x0084144b, 0x00841459

// A 4-byte store to a machine displacement, byte-addressed on purpose: the
// receiver is opaque, so no typed member is asserted and no member name exists
// to be misread as a claim. Used by 0x0084144b and 0x00841459, and by the
// model test's reproduction of the two tail stores.
inline void store_word(void *base, std::size_t displacement, MachineWord value) {
  std::memcpy(static_cast<std::uint8_t *>(base) + displacement, &value,
              sizeof value);
}

// The load side of the same thing, so the model test can read what the body and
// the tail wrote without the model declaring a layout.
inline MachineWord load_word(const void *base, std::size_t displacement) {
  MachineWord value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t *>(base) + displacement,
              sizeof value);
  return value;
}

// The shared tail at 0x0083c780, entered by JMP from 0x00841452 and 0x00841460.
//
// Its five instructions, read verbatim from the bridge:
//
//   0x0083c780  8b 44 24 04   MOV EAX,dword ptr [ESP + 0x4]
//   0x0083c784  8b 54 24 08   MOV EDX,dword ptr [ESP + 0x8]
//   0x0083c788  89 41 04      MOV dword ptr [ECX + 0x4],EAX
//   0x0083c78b  89 51 0c      MOV dword ptr [ECX + 0xc],EDX
//   0x0083c78e  c2 08 00      RET 0x8
//
// Three facts about the target follow from those five instructions and from
// nothing else:
//
//   1. ECX is the receiver. The tail stores through ECX and the body reached it
//      by leaving ECX untouched, so the body's receiver is ECX.
//   2. The target has exactly TWO ordinary stack arguments, at entry [ESP+0x4]
//      and [ESP+0x8]. The tail reads both and RET 0x8 pops 8 bytes, and the
//      body contains no RET, no ADD ESP and no push of its own, so nothing else
//      can be on the frame.
//   3. The body is a TAIL CALL, not a call: control leaves by JMP with the frame
//      untouched, and 0x00841440 contains no return of its own. The epilogue
//      that pops the two argument words belongs to the tail.
//
// 0x0083c780 is NOT a function record of this package and is not owned by it.
// It is a linker-folded two-word setter with many call sites in this image and
// no name, signature or class of its own. So it is declared here and DEFINED IN
// THE MODEL TEST as an observer that records what it was handed.
bool PKG_DFW_00841440_THISCALL dfw_00841440_shared_tail_0083c780(
    OpaqueFormatParser* receiver, char* pName, OpaqueLine* argumentsLine);

// 0x00841440 -- ArgScript::FormatParser::CreateDefinitionSafe.
//
// 11 instructions, two basic blocks, one forward conditional branch and two
// unconditional tail jumps:
//
//   0x00841440  MOV EDX,dword ptr [ESP + 0x8]     read the SECOND stack word
//   0x00841444  TEST EDX,EDX
//   0x00841446  JZ 0x00841457
//   0x00841448  LEA EAX,[EDX + -0x4]               bias the word down by 4
//   0x0084144b  MOV dword ptr [ECX + 0x30],EAX     the body's one field store
//   0x0084144e  MOV dword ptr [ESP + 0x8],EDX      rewrite the slot it read
//   0x00841452  JMP 0x0083c780
//   0x00841457  XOR EAX,EAX
//   0x00841459  MOV dword ptr [ECX + 0x30],EAX     the same store, a zero word
//   0x0084145c  MOV dword ptr [ESP + 0x8],EDX      rewrite the slot, with zero
//   0x00841460  JMP 0x0083c780
//
// Calling convention: __thiscall, receiver in ECX, two ordinary stack arguments,
// callee cleanup of 8 bytes. That is the persisted record's own claim
// (record abi.calling_convention) and the tail listing corroborates it
// mechanically, as set out above. It is NOT the derived machine ABI's verdict:
// abi_derived.verdict is ABI_UNKNOWN with abstained_because
// "no_terminal_ret: the only exit observed is a tail jump", and
// abi_derived.conventions.confidence is UNKNOWN. The derived record also
// recovered only ONE stack slot (entry_ESP+0x8, observed read) and reports
// stack_arguments.gaps 1 / not_complete true, so on its own it would have missed
// the first argument entirely.
//
// WHICH SLOT IS TESTED, and the one naming dispute this package does not
// resolve by guessing:
//
//   * The machine settles the mechanics beyond argument: the word the body tests
//     is the one at entry [ESP+0x8], the SECOND ordinary stack word. That is
//     fixed by the raw listing, by the machine-derived slot record
//     (entry_ESP+0x8, ordinal 2) and by the tail, which reads [ESP+0x4] into
//     EAX and [ESP+0x8] into EDX.
//   * The NAME of that slot is not settled by the machine. The persisted record
//     calls entry [ESP+0x4] pName and entry [ESP+0x8] argumentsLine on the
//     strength of the SDK prototype and the unsafe sibling. The exported
//     decompilation labels the tested slot pName, but that label is an artifact
//     of Ghidra's own unrecoverable convention guess: it places this at
//     [ESP+0x4] and argumentsLine at [ESP+0xc], which would make three stack
//     arguments against a RET 0x8 that pops two. record unresolved_questions
//     already flags this disagreement.
//   * The record's own supporting citation is also weaker than it reads. It
//     attributes "MOV EDI,dword ptr [ECX + 0x10] at 0x008450b8" to ECX holding
//     the second argument; re-read from the bridge, ECX at 0x008450b8 is
//     [EBP-0x4c], a local set by LEA ECX,[EBP-0x4c] at 0x008450af. The slot
//     assignment still stands on a different instruction of the same sibling:
//     0x008450c6 loads [EBP+0xc] -- the second ordinary stack word of a
//     PUSH EBP / MOV EBP,ESP frame -- into ECX and calls 0x00837f30 with it.
//   * This model therefore keys its behaviour on the machine fact, the SECOND
//     stack word, and names the parameter from the persisted record. Swapping
//     the two parameter names would not change a single modelled effect, and the
//     model test asserts the behaviour against the second word directly, so the
//     unresolved naming question cannot make the reconstruction wrong.
//
// Return: declared bool, from the SDK. The body writes EAX on both paths (the
// biased word, and zero) and the tail then overwrites EAX at 0x0083c780 with the
// first stack word, so both body-level values are dead at the RET and the word a
// caller observes is the first stack word reduced to bool. This package
// therefore does not return the body's own EAX value: it returns whatever the
// tail returns, which is the honest reading of a tail call.
bool PKG_DFW_00841440_THISCALL dfw_00841440_CreateDefinitionSafe(
    OpaqueFormatParser* receiver, char* pName, OpaqueLine* argumentsLine);

}  // namespace openspore::reconstruction::pkg_dfw_00841440
