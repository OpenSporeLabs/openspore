#pragma once

// Reconstruction of FUN_00bd81d0 @ 0x00bd81d0 (SporeApp.exe 3.1.0.22,
// SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// EVIDENCE BASIS (every claim below is traceable to one of these; nothing else
// is claimed).
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete:
//        0x00bd81d0  8b 81 40 05 00 00  MOV EAX,dword ptr [ECX + 0x540]
//        0x00bd81d6  c3                 RET
//     Raw bytes at 0x00bd81d0..0x00bd81d7 are 8b 81 40 05 00 00 c3 cc, read
//     live from the program database. Body span 0x00bd81d0..0x00bd81d7, 7
//     bytes, matching the derived ABI record's target.block
//     (body_start 0x00bd81d0, body_end 0x00bd81d6, body_span_bytes 7). The
//     0xcc at 0x00bd81d7 is the INT3 pad and is NOT part of the body.
//
//  2. Live Ghidra decompilation, which adds nothing to (1) and is consistent
//     with it:
//        undefined4 __fastcall FUN_00bd81d0(int param_1)
//        { return *(undefined4 *)(param_1 + 0x540); }
//     Ghidra's own `__fastcall` spelling is its default for an untype function;
//     note (3) is the record that actually reads the register usage.
//
//  3. Derived ABI record for this VA (INFERRED): architecture x86-32, receiver
//     in ECX shape R-DIRECT with exactly one distinct offset 0x540
//     (1344) and zero writes through it, 0 ordinary stack arguments, bare RET
//     with no immediate so the callee pops nothing and the caller owns stack
//     cleanup, return value in EAX, no frame, no SIB, no indirect call, no
//     vtable-shaped load. Confidence CORE_RESOLVED, verdict ABI_INFERRED,
//     completeness of the parse: 2 declared / 2 parsed / 0 unparsed,
//     flow_complete true, esp_unresolved false. Its candidates are __thiscall
//     and __fastcall and it resolves to __thiscall; for a body that reads ECX
//     and takes nothing from the stack the two encodings are identical, so this
//     package models it as __thiscall, which is the one the record names.
//
//  4. THE RETURNED WORD IS A SCALAR, NOT A POINTER - established from live
//     decompilation of sampled callers, and this CONTRADICTS one field of (3).
//     The record classifies the last value written to EAX as
//     `register_class: pointer_like`, but that is a register-shape heuristic on
//     a 32-bit EAX value, not a use observation. Sampled callers use the result
//     as an enum-like small integer and never dereference it:
//       0x00bd0000   iVar3 = FUN_00bd81d0(); if (iVar3 == 1) {...} else if (iVar3 == 2) {...} else {...}
//       0x00bf0f40   iVar1 = FUN_00bd81d0(); if (iVar1 != 0) { if (iVar1 == 1) return 2; if (iVar1 != 2) return -1; return 1; } return 0;
//       0x00bd7160   iVar3 = FUN_00bd81d0(); if (iVar3 == -1) { FUN_00be73d0(0,0); }
//       0x00cf78d0   iVar2 = FUN_00bd81d0(); ... (iVar2 == 0) ... (iVar2 == 1) ... (iVar2 == 2) ...
//       0x00bf1fd0   iVar1 = FUN_00bd81d0(); if (iVar1 == param_2) {...} - an equality against a loop/parameter value, then arithmetic on it
//       0x00bf9820   uVar12 = FUN_00bd81d0(uVar11); iVar18 = FUN_00bf0c60(uVar12,uVar11,...) - passed straight through as an integer argument
//     Seven independent callers, zero of them dereference the result and all
//     of them compare it for equality against small integers. So the
//     reconstructed return type is a 32-bit INTEGER and the record's
//     `pointer_like` classification is recorded here as a known, evidence-based
//     disagreement rather than silently adopted or silently dropped.
//
//  5. Values the callers compare against, so the modelled width and signedness
//     are anchored in observed comparisons rather than in a guess:
//       -1, 0, 1, 2  appear as literal comparands or returned constants
//       (0x00bd0000, 0x00bf0f40, 0x00bd7160, 0x00cf78d0). The -1 at 0x00bd7160
//     is compared with `==`, which under a signed reading is one below zero
//     and under an unsigned reading is 0xffffffff; the body performs no sign
//     extension, so the value is carried verbatim as a 32-bit bit pattern and
//     this package models the return type as `std::uint32_t` with the observed
//     -1 comparison noted as the one place where a signed enum reading is
//     plausible. NO enum type and NO enumerator name is claimed: no SDK symbol,
//     committed research note or sample labels this field.
//
//  6. Structural, from a live read-only disassembly of the enclosing accessor
//     block 0x00bd8180..0x00bd8200. The block is a run of tiny one-instruction
//     members on the SAME receiver (all addressing through ECX), 0x10 apart,
//     separated by INT3 padding:
//        0x00bd8190  MOV EAX,dword ptr [ECX + 0x2f8] ; RET        (6 bytes)
//        0x00bd81a0  LEA EAX,[ECX + 0x548]              ; RET        (6 bytes)
//        0x00bd81b0  MOV AL, byte ptr [ECX + 0x21c]    ; RET        (6 bytes)
//        0x00bd81c0  MOV AL,byte ptr [ESP+4] / MOV byte ptr [ECX + 0x33c],AL / RET 4
//        0x00bd81d0  MOV EAX,dword ptr [ECX + 0x540]   ; RET        <== THIS TARGET
//        0x00bd81e0  MOV EAX,dword ptr [ESP+4] / MOV dword ptr [ECX + 0x2f0],EAX / RET 4
//        0x00bd81f0  MOV EAX,dword ptr [ECX + 0x2f0]   ; RET        (6 bytes)
//     Two things this block establishes and (1)/(3) do not:
//       (a) the receiver is a real multi-field object, not a one-word slot
//           holder: the immediately preceding 0x00bd81c0 member STORES a byte
//           at [ECX + 0x33c] and the immediately following 0x00bd81e0 member
//           STORES a dword at [ECX + 0x2f0], so +0x540 sits in a class with
//           other live members;
//       (b) the accessor family mixes read and write members, and the writers
//           use `RET 4` with one stack argument - a form this target does NOT
//           use. That contrast is why the target's bare `RET` is stated as
//           zero-cleanup rather than left implicit.
//     0x00bd81a0 is `LEA EAX,[ECX + 0x548]`, i.e. it returns an ADDRESS of a
//     member eight bytes above this one, not the member's value. That is the
//     load-versus-LEA contrast case: this binary really does contain both forms
//     for members of this same object, 0x30 bytes apart, so a LEA-form reading
//     of this target is not hypothetical here.
//
//  7. Fan-in, from the evidence pack's ghidra_function record: 72 xrefs, 31
//     distinct caller functions, and 0 callees. That is the profile of a shared
//     accessor, and it is used here ONLY to justify calling it a shared
//     accessor. It says nothing about what the field means and is not used as
//     evidence for any identity.
//
// WHAT IS NOT CLAIMED
//  * The class of the receiver. It is UNKNOWN. No SDK import, no namespace and
//    no committed research note names the type that owns offset 0x540. The
//    struct below is opaque and declares no member; it exists only so a
//    receiver-relative read can be spelled in C++.
//  * The NAME, DOMAIN or MEANING of the field at +0x540. It is UNNAMED. The
//    0/1/2/-1 comparisons in (4)/(5) establish that it is an enum-like small
//    integer; they do not say what the enumerators are called or what they
//    mean, so no enumerator name, no enum type and no C++ `enum` appear.
//  * That the field is never written. This body does not write it; note (6)
//    shows writers exist in this block for OTHER offsets, and no writer for
//    +0x540 was located by this package. See unresolved_questions.
//  * Any virtual dispatch, any tail call, any variadic behaviour, any SEH or
//    cookie frame, any struct return. The record measures each of these at
//    zero/absent and the listing agrees: the body is two instructions.
//  * Any runtime, Wine, trace or differential claim. No runtime evidence exists
//    for this VA (validation.md: runtime GATED, 0 observations).

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00bd81d0 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00bd81d0_receiver_slot_getter {

// The unit the body actually moves: one 32-bit word in, one 32-bit word out.
using SlotWord = std::uint32_t;

static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(void *) == 4, "x86-32 target pointers are 32-bit");

// The receiver's field offset, 0x540 = 1344. This is the ONLY offset the body
// touches, and it is read directly out of the instruction's disp32 (note 1).
constexpr std::uint32_t kSlotOffset = 0x540u;

// 0x00bd81d0..0x00bd81d7 is seven bytes; the 0xcc at 0x00bd81d7 is INT3 pad
// and is deliberately not part of kTargetEncoding.
constexpr std::size_t kTargetBodyBytes = 7;

// The body's bytes as read from 0x00bd81d0. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0x8b,                    // MOV r32, r/m32
    0x81,                    // ModRM: mod=10 disp32, reg=000 EAX, r/m=001 ECX
    0x40, 0x05, 0x00, 0x00,  // disp32 = 0x540, little endian
    0xc3,                    // RET
};

// The receiver. UNKNOWN by evidence: no class, no SDK symbol, no field names
// (header note 6's letter (a) establishes that OTHER members of this object are
// live, which is why the fixture is not a bare one-word holder, but no member of
// this struct is named). kReceiverModellingExtent is a MODELLING BOUND chosen
// so that +0x540 is addressable with a planted guard word on either side; it is
// NOT a recovered object size.
constexpr std::size_t kReceiverModellingExtent = 0x548u;

// The object this member lives on. Opaque on purpose: it declares no member and
// asserts no Simulator class. The bytes exist so the model test can plant
// neighbours and guard bands around the one offset the evidence reaches.
struct alignas(4) OpaqueSimulatorReceiver {
  std::uint8_t opaque_bytes[kReceiverModellingExtent];
};

// The three literal values every sampled caller compares the result against
// (header note 5). These are observed COMPARANDS, not enumerators: no name and
// no meaning is attached to any of them here.
constexpr SlotWord kObservedComparandZero = 0u;
constexpr SlotWord kObservedComparandOne = 1u;
constexpr SlotWord kObservedComparandTwo = 2u;
// 0x00bd7160 compares the result against -1. The body does not sign-extend, so
// the bit pattern is what is carried; both spellings are named so the
// comparison in note 5 stays auditable.
constexpr SlotWord kObservedComparandMinusOneSigned = 0xffffffffu;

// The x86-32 entry: receiver in ECX, nothing on the stack, bare RET, one 32-bit
// value back in EAX. Spelled as a pointer-to-member of the opaque receiver so
// the receiver-relative access and the zero-stack-argument shape are both part
// of the declared type rather than only of the prose.
using AbiReceiverSlot00bd81d0 = SlotWord (OpaqueSimulatorReceiver::*)() const;

static_assert(kSlotOffset == 0x540u,
              "the offset is 0x540, compared semantically not by spelling");
static_assert(kSlotOffset == 1344u,
              "0x540 is the value 1344, the number the ABI record reports");
static_assert(kTargetEncoding[0] == 0x8bu,
              "0x00bd81d0 is MOV r32,r/m32, opcode 0x8b");
static_assert(kTargetEncoding[1] == 0x81u,
              "ModRM 0x81 is mod=10 (disp32), reg=000 (EAX), r/m=001 (ECX)");
static_assert(kTargetEncoding[2] == 0x40u && kTargetEncoding[3] == 0x05u &&
                  kTargetEncoding[4] == 0x00u && kTargetEncoding[5] == 0x00u,
              "the disp32 bytes spell 0x540, little endian");
static_assert(kTargetEncoding[6] == 0xc3u,
              "0x00bd81d6 is RET with no imm16");
static_assert(kTargetBodyBytes == 7u,
              "the body is 7 bytes, matching the derived record's 7-byte span");
static_assert(kTargetBodyBytes == 1u + 1u + 4u + 1u,
              "one opcode byte, one ModRM byte, one disp32, one RET");
static_assert((kTargetEncoding[1] >> 6) == 0x02u,
              "mod=10, so the displacement is disp32 and NOT disp8");
static_assert(((kTargetEncoding[1] >> 3) & 0x07u) == 0x00u,
              "reg=000 selects EAX, the return register the ABI record names");
static_assert((kTargetEncoding[1] & 0x07u) == 0x01u,
              "r/m=001 selects ECX, the receiver the ABI record names");
static_assert(kTargetEncoding[1] != 0x84u && kTargetEncoding[1] != 0x85u,
              "r/m=100/101 would be an SIB form; the observed ModRM has none");
static_assert(kSlotOffset == (static_cast<std::uint32_t>(kTargetEncoding[2]) |
                              (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
                              (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
                              (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)),
              "the header's offset equals the instruction's disp32");
static_assert(kReceiverModellingExtent > kSlotOffset,
              "the fixture extent must reach past the observed offset");
static_assert(kReceiverModellingExtent >= kSlotOffset + sizeof(SlotWord),
              "the observed word must lie wholly inside the fixture extent");
static_assert(kObservedComparandZero == 0u && kObservedComparandOne == 1u &&
                  kObservedComparandTwo == 2u &&
                  kObservedComparandMinusOneSigned == 0xffffffffu,
              "the observed comparands are the ones the sampled callers use");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00bd81d0.
SlotWord simulator_receiver_slot_00bd81d0(
    const OpaqueSimulatorReceiver* receiver);

}
