#pragma once

// Reconstruction of FUN_00b8dab0 @ 0x00b8dab0 (SporeApp.exe 3.1.0.22,
// snapshot 2540f2ca).
//
// EVIDENCE BASIS (every claim below traces to exactly one of these; nothing
// else is claimed).
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete:
//        0x00b8dab0  8b 81 94 01 00 00   MOV EAX,dword ptr [ECX + 0x194]
//        0x00b8dab6  c3                  RET
//     Raw bytes at 0x00b8dab0..0x00b8dab8 read live from the program
//     database: 8b 81 94 01 00 00 c3 cc. The body is therefore 7 bytes,
//     0x00b8dab0..0x00b8dab6; the trailing 0xcc is INT3 padding between this
//     function and the next entry and is NOT part of the body. Independently
//     re-read from the pinned image with objdump (see note 5).
//
//  2. Live Ghidra decompilation, consistent with (1) and adding nothing:
//        undefined4 __fastcall FUN_00b8dab0(int param_1)
//        { return *(undefined4 *)(param_1 + 0x194); }
//
//  3. Derived ABI record for this VA (INFERRED, ABI_INFERRED): x86-32;
//     ECX read before any definite write and dereferenced, so ECX carries a
//     receiver; bare RET with no immediate and no stack reads, so the callee
//     pops nothing and the caller owns stack cleanup; 0 ordinary stack
//     arguments; return value in EAX; not a struct-return (entry slot 0 is not
//     written through a pointer); no indirect call and no vtable-shaped load in
//     the body.
//
//  4. Committed call-graph sidecar knowledgegraph/triage/xrefs-2540f2ca.tsv
//     records 78 direct call edges into 0x00b8dab0 from 30 distinct caller
//     functions. High fan-in, all static.
//
//  5. Structural, from an objdump disassembly of the pinned image over
//     0x00b8d900..0x00b8dd00 (read-only): 0x00b8dab0 is the ONLY access to
//     [ECX + 0x194] in that 0x400-byte window. The immediate neighbours are
//     members of the same accessor family on the same receiver and pin the
//     load/LEA distinction in this very family:
//        0x00b8da48  mov [ecx+0x190],eax     a WRITE of a neighbouring word
//        0x00b8da60  lea eax,[ecx+0x188]    an ADDRESS (LEA) of a neighbour
//        0x00b8da70  mov eax,[ecx+0x184]    a LOAD of a neighbour
//                    sub eax,0x1000000 ; ret
//        0x00b8da80  mov eax,[esp+4] ; mov [ecx+0x184],eax ; ret 0x4
//                    a SETTER for +0x184: one stack argument, callee cleanup
//        0x00b8dac0  mov eax,[ecx+0x2c] ; shr eax,2 ; and al,1 ; ret
//        0x00b8dad0  lea eax,[ecx+0x198]    an ADDRESS of the word AFTER 0x194
//        0x00b8dae6  mov [ecx+0x198],edx    a WRITE of +0x198
//        0x00b8daef  mov [ecx+0x19c],edx    a WRITE of +0x19c
//     So a LEA and a MOV-load of the same shape both occur here, and the one at
//     0x00b8dab0 is unambiguously the load: opcode 0x8b, and a LEA of that
//     address would return an address rather than the stored word.
//
//  6. Receiver-negative claim: knowledgegraph/triage/datarefs-2540f2ca.tsv
//     contains ZERO rows for 0x00b8dab0. A function reached only through a
//     vtable would appear as the target of a data reference from its table, so
//     on this pinned snapshot 0x00b8dab0 is not the target of any recorded
//     data reference - consistent with the 78/78 direct-call edges of (4) and
//     with the body's zero indirect dispatch of (3). This is a recorded
//     absence, not an exhaustive proof that no table exists.
//
//  7. Return-value use, from four sampled callers, all of which obtain the
//     receiver in ECX immediately before the call and then use the result as a
//     SCALAR in an ORDERED comparison:
//        0x00ae587b  call 0x00b8dab0 ; cmp eax,0x5       ; jz
//        0x00b8da45  call 0x00b8dab0 ; cmp eax,0x5       ; jnz
//        0x00bade0a  call 0x00b8dab0 ; cmp eax,0x2       ; jl
//        0x00c8b609  call 0x00b8dab0 ; cmp eax,[esp+0x10] ; jle
//        0x00c8b616  call 0x00b8dab0 ; mov [esp+0x10],eax
//     A signed ordered comparison against a small constant, and a running
//     maximum reduced with JLE, are scalar semantics. No sampled caller
//     dereferences the result.
//
//  8. THE ABI RECORD'S return CLASS IS OVERSTATED FOR THIS BODY, and the
//     reconstruction follows the callers, not the record. The derived record
//     classifies the EAX value as `register_class: pointer_like` on the
//     strength of a single heuristic ("the last value written to EAX"), with
//     `confidence: INFERRED` and `corroboration: not_available`. That
//     heuristic cannot distinguish a loaded word from a computed address. The
//     four callers of (7) use the value as an ordered scalar and never as an
//     address, so this package models the return as a 32-bit unsigned scalar
//     and records the disagreement rather than adopting the record's class.
//
// WHAT IS NOT CLAIMED
//  * The class of the receiver, or the name of the word at +0x194. The
//    receiver record is `bounds_only: true` - "where the body was SEEN
//    reaching", not a layout - so no field name appears anywhere below and the
//    displacement is spelled literally. A member name here would be a
//    field-identity assertion with nothing behind it.
//  * What the scalar MEANS. `CMP EAX,0x5 / JZ` and `CMP EAX,0x2 / JL` say the
//    value behaves like an ordinal or threshold, but nothing in the evidence
//    pack names a game concept for it. The name below stops at "scalar".
//  * Any writer of the word at +0x194. Within the 0x400-byte accessor window
//    of (5) there is none; beyond that window this package makes no claim, and
//    absence of a direct writer is never an immutability claim.
//  * The receiver's size. 0x198 below is a MODELLING BOUND - the prefix
//    through the one word the body reads - not a recovered allocation size,
//    even though the sibling accessors of (5) show words at +0x198 and +0x19c.
//  * Signedness at the source level. The body is a bare 32-bit load and copies
//    bits; the signed reading comes from the JLT-family comparisons of (7),
//    which is why the type is unsigned here and the ordered comparisons are
//    modelled explicitly in the test.
//  * Any calling convention other than __thiscall, and any ordinary stack
//    argument. The encoding has a ModRM byte, so a register receiver is
//    admissible; it names no memory operand relative to ESP, so no stack
//    argument is read.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b8dab0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00B8DAB0_THISCALL __thiscall
#else
#define PKG_00B8DAB0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00b8dab0_field194_getter {

// The unit the body actually moves: one 32-bit word in, one 32-bit word out.
using SlotWord = std::uint32_t;

// Receiver of the target function, modelled at exactly the width the machine
// read and no more: 0x198 bytes, 4-byte aligned, i.e. the prefix through the
// one word the body reaches. No member is declared - see the header's "what is
// not claimed". The extent is a modelling bound, not a recovered size.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x198> opaque_bytes{};  // 0x00..0x197
};

// The displacement the body was observed reaching on the receiver, taken from
// the ModRM/disp32 pair of `MOV EAX,dword ptr [ECX + 0x194]`. It is a value,
// not a member: the receiver record enumerates displacements
// (`offsets: [404]`, `bounds_only: true`) and cannot say which member is which.
constexpr std::size_t kFieldDisplacement = 0x194;

// The width of the word the body reads.
constexpr std::size_t kFieldWidth = sizeof(SlotWord);

// The receiver word, read by displacement. This is the ONLY way this package
// touches the receiver; naming a member instead would assert an identity no
// witness in the pack supports.
inline SlotWord field_at(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const SlotWord*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// The displacement is in BYTES, not in 4-byte words. The word this body reads
// therefore sits at word index 101 of the receiver; a model that mistook the
// disp32 for an element COUNT would instead address word 0x194, i.e. byte
// 0x650, which is past the modelled extent entirely.
constexpr std::size_t kFieldIndexInWords = kFieldDisplacement / kFieldWidth;

// 0x00b8dab0..0x00b8dab6 is seven bytes; the 0xcc that follows is INT3 pad
// between this entry and the next and is deliberately not modelled.
constexpr std::size_t kTargetBodyBytes = 7;

// The body's bytes as read from 0x00b8dab0. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0x8b,                          // MOV r32, r/m32
    0x81,                          // ModRM: mod=10 disp32, reg=EAX, rm=ECX
    0x94, 0x01, 0x00, 0x00,        // disp32 = 0x00000194, little endian
    0xc3,                          // RET
};

// The byte at 0x00b8dab7: INT3 padding, NOT part of the body. Named so the
// model's boundary can be checked against the image.
constexpr std::uint8_t kTargetPadByte = 0xcc;

// The direct-call edges recorded for this target, from the committed sidecar
// (note 4). Recorded as a count, because no call site is transcribed here and
// the number is the part of (4) that a claim could otherwise be checked on.
constexpr std::size_t kRecordedDirectCallEdges = 78;

// x86-32 thiscall: receiver in ECX, 0 ordinary stack arguments, the callee pops
// nothing (bare RET) so the caller owns stack cleanup, and one 32-bit scalar
// comes back in EAX.
using AbiScalarField19400b8dab0 = std::uint32_t(PKG_00B8DAB0_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(OpaqueReceiver) == 0x198,
              "modelled receiver extent runs through the reached word");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kFieldDisplacement + kFieldWidth == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modelled extent");
static_assert(kFieldDisplacement == 0x194u,
              "the displacement is 0x194, compared semantically not by spelling");
static_assert(kFieldDisplacement == 404u, "0x194 is the value 404");
static_assert(kFieldIndexInWords == 101u,
              "0x194 is 101 four-byte words past the base");
static_assert((kFieldIndexInWords * kFieldWidth) * kFieldWidth >
                  sizeof(OpaqueReceiver),
              "reading the disp32 as an element count would address byte 0x650");
static_assert((kFieldDisplacement % kFieldWidth) == 0u,
              "the displacement is 4-byte aligned, as a word read requires");

// The encoding IS the observed one, and its disp32 IS the header's
// displacement, so the two statements cannot drift apart.
static_assert(kTargetEncoding[0] == 0x8bu, "0x00b8dab0 is MOV r32, r/m32");
static_assert(kTargetEncoding[1] == 0x81u,
              "ModRM 0x81 is mod=10 (disp32) reg=000 (EAX) rm=001 (ECX)");
static_assert((kTargetEncoding[1] >> 6) == 2u, "mod=10 selects a disp32");
static_assert(((kTargetEncoding[1] >> 3) & 7u) == 0u, "reg=000 selects EAX");
static_assert((kTargetEncoding[1] & 7u) == 1u, "rm=001 selects ECX");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[2]) |
               (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)) ==
                  kFieldDisplacement,
              "the instruction's disp32 is the header's displacement");
static_assert(kTargetEncoding[6] == 0xc3u, "0x00b8dab6 is a bare RET");
static_assert(kTargetEncoding[6] != 0xc2u,
              "RET 0xc2 would be RET imm16; 0xc3 pops nothing");
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the encoding array is exactly the modelled body length");
static_assert(kTargetPadByte == 0xccu, "0x00b8dab7 is INT3 pad, not body");

static_assert(std::is_same<AbiScalarField19400b8dab0,
                           std::uint32_t(PKG_00B8DAB0_THISCALL*)(
                               OpaqueReceiver*)>::value,
              "the modelled entry carries the ECX receiver and returns one word");

// Entry point under reconstruction. The name embeds the 8-hex target VA so
// the validator can bind this span to 0x00b8dab0.
std::uint32_t PKG_00B8DAB0_THISCALL scalar_field_194_00b8dab0(
    OpaqueReceiver* receiver);

}

#undef PKG_00B8DAB0_THISCALL