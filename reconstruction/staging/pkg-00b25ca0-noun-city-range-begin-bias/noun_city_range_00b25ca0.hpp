#pragma once

// Reconstruction of FUN_00b25ca0 @ 0x00b25ca0 (SporeApp.exe 3.1.0.22,
// snapshot 2540f2ca).
//
// EVIDENCE BASIS. Every claim below traces to exactly one of these. Nothing
// else is claimed.
//
//  1. Live Ghidra listing of the body - eight instructions, COMPLETE, straight
//     line, no branch, no indirect transfer:
//        0x00b25ca0  68 6a 81 8c 01     PUSH 0x018c816a
//        0x00b25ca5  68 00 e5 b1 00     PUSH 0x00b1e500
//        0x00b25caa  68 c0 36 b2 00     PUSH 0x00b236c0
//        0x00b25caf  68 20 d4 d3 00     PUSH 0x00d3d420
//        0x00b25cb4  68 80 10 b2 00     PUSH 0x00b21080
//        0x00b25cb9  e8 82 b6 ff ff     CALL 0x00b21340
//        0x00b25cbe  83 c0 04           ADD EAX,0x4
//        0x00b25cc1  c3                 RET
//     Raw bytes 0x00b25ca0..0x00b25cc2 read live from the program database:
//        68 6a 81 8c 01 68 00 e5 b1 00 68 c0 36 b2 00 68 20 d4 d3 00
//        68 80 10 b2 00 e8 82 b6 ff ff 83 c0 04 c3
//     The body is therefore 34 bytes, 0x00b25ca0..0x00b25cc2, and 34 is the
//     sum of the eight encodings above (5+5+5+5+5+5+3+1), which is the check
//     that the listing is whole rather than truncated.
//
//  2. Live Ghidra decompilation, consistent with (1) and adding no claim of its
//     own beyond the call's shape:
//        int FUN_00b25ca0(void)
//        { return FUN_00b21340(PTRREF_00B21080, PTRREF_00D3D420,
//                              PTRREF_00B236C0, PTRREF_00B1E500,
//                              &DAT_018c816a) + 4; }
//
//  3. THE CALL IS thiscall WITH A FORWARDED ECX RECEIVER, AND THIS IS THE ONE
//     POINT WHERE THE PACK MUST BE CORRECTED AGAINST ITSELF.
//     (a) The derived ABI record for this VA (ABI_INFERRED) states
//         `receiver: false` and inference R2 "ECX is never read in any form, so
//         there is no register receiver", OBSERVED. That record is a
//         single-VA listing analysis: ECX is indeed never READ by 0x00b25ca0's
//         own eight instructions. But "never read here" is not "no receiver",
//         because ECX can be forwarded - and here it is.
//     (b) The callee 0x00b21340 is thiscall. Live listing of its 80
//         instructions shows `MOV ESI,ECX` as its third instruction
//         (0x00b21346) and `RET 0x14` as its last (0x00b21407): five stack
//         words of callee cleanup, a hidden ECX this. Ghidra decompiles it
//         `char * __thiscall FUN_00b21340(int param_1, ...)`, with param_1 used
//         as the receiver base (`param_1 + 0x98`, `param_1 + 0x78`,
//         `param_1 + 0x9c`).
//     (c) 0x00b25ca0 pushes exactly five words and its own eight instructions
//         contain no write to ECX, so whatever ECX holds on entry arrives in
//         the callee's ECX untouched. Five pushes against `RET 0x14` is exact,
//         not approximate: the argument count matches the callee's cleanup
//         byte count.
//     (d) A caller settles it. Live context at 0x00bf99b6..0x00bf99c4 in
//         FUN_00bf9820:
//           00bf99b6  CALL 0x00b3d300     ; the alternate cGameNounManager*
//           00bf99bb  MOV ECX,EAX
//           00bf99bd  CALL 0x00b25ca0
//           00bf99c2  MOV ECX,dword ptr [EAX]
//           00bf99c4  MOV EDX,dword ptr [EAX + 0x4]
//           00bf99c7  CMP ECX,EDX        ; begin vs end
//         A register is loaded into ECX immediately before the call, and a
//         cGameNounManager is what 0x00b3d300 is recorded as returning
//         (docs/analysis/simulator-root-closure.md, closure matrix row
//         `00b3d300`). A second caller agrees: FUN_00bf0b00 decompiles to
//         `FUN_00b3d300(); piVar2 = (int *)FUN_00b25ca0();`, with the live
//         listing at 0x00bf0b06 `CALL 0x00b3d300` / 0x00bf0b0b `MOV ECX,EAX`
//         / 0x00bf0b10 `CALL 0x00b25ca0`.
//     So the reconstruction declares an ECX receiver. The superseded R2 claim
//     is recorded here rather than silently dropped; see "what is not
//     claimed".
//
//  4. THE FIVE PUSHES ARE IMMEDIATES, NOT MEMORY LOADS, AND THAT IS NOT A
//     DETAIL. Each is the 5-byte opcode 0x68 (`PUSH imm32`); none is 0xff /0x35
//     style. The callee's own listing confirms the consequence: it dereferences
//     them - `CALL dword ptr [ESP + 0x20]` (0x00b2136d), `CALL dword ptr
//     [ESP + 0x28]` (0x00b213a5), `CALL EBP` where EBP came from
//     `[ESP + 0x30]` (0x00b213cd/0x00b213d7), `CALL dword ptr [ESP + 0x34]`
//     (0x00b213e2) - i.e. four of the five are function pointers the callee
//     CALLS, and the fifth is the key operand compared against the receiver's
//     `+0x9c` word (0x00b21363 `LEA EDX,[ESI + 0x9c]`). Four of the five
//     immediates land on instruction bytes read live: 0x00b21080 begins
//     `6a 00 6a 00` (PUSH 0 / PUSH 0), 0x00d3d420 begins `8b 4c 24 04`
//     (MOV ECX,[ESP+4]), 0x00b236c0 begins `8b 4c 24 08`, 0x00b1e500 begins
//     `8b 4c 24 04`. All four are code addresses, not data.
//     The fifth, 0x018c816a, reads as eight zero bytes in the program
//     database, so it is a data address. The Ghidra rendering `PTRREF_00B21080`
//     in note (2) is the decompiler naming an immediate by the address it
//     spells; the machine pushed the NUMBER, and a reconstruction that treated
//     these as five memory reads would be wrong on all five.
//
//  5. THE `ADD EAX,0x4` IS A FIELD BIAS ON THE RETURNED POINTER, AND THE
//     CALLERS SAY WHICH FIELD. The callee returns a pointer to its own
//     NounProjectionVector. The promoted reconstruction of the callee
//     (src/reconstruction/pkg11_sim_core/noun_projection.hpp) fixes that
//     layout by static_assert: `needs_update` at +0x00, `begin` at +0x04, `end`
//     at +0x08. Adding 4 therefore yields the address of `begin`, so the
//     returned pointer addresses a {begin, end} PAIR and not the vector.
//     The callers consume it exactly that way:
//       0x00bf99c2/0x00bf99c4/0x00bf99c7  read [EAX] and [EAX+4], compare them,
//                                         and skip the range when equal;
//       FUN_00bf0b00 decompiles to `iVar1 = piVar2[1]; for (iVar3 = *piVar2;
//                                    iVar3 != iVar1; iVar3 = iVar3 + 4)` -
//                                    a dword-stride walk bounded by [p] and
//                                    [p+4];
//       FUN_00b25f40, a sibling wrapper over the same callee that does NOT
//                    apply the bias, reads the vector directly as
//                    `*(int *)(iVar2 + 8) - *(int *)(iVar2 + 4)` for its count
//                    and `*(int *)(iVar2 + 4) + iVar4 * 4` for its elements -
//                    begin at +4, end at +8, the same two words.
//     Two independent consumers and one unbaised sibling all agree, so the
//     +4 is a bias to `begin` and the returned range is [begin, end).
//
//  6. THE BODY HAS NO BRANCH, NO FLAG TEST, NO SAVE AND NO LOOP. Eight
//     instructions, five of them PUSH, then CALL, ADD, RET. Consequences that
//     are claims rather than omissions:
//     * the five pushes and the call happen on EVERY entry - there is no
//       lazily-taken, cached or conditional path;
//     * ECX is not modified, so the callee sees the caller's receiver
//       (note 3);
//     * the callee consumes the five words - on the machine its last
//       instruction is `RET 0x14`, so it pops all twenty itself - and this
//       body's own trailing RET pops nothing but the return address. With zero
//       ordinary stack arguments declared on 0x00b25ca0 itself, a bare RET is
//       correct: the five words belong to the callee's frame, not this one's.
//       (Which function's LISTING contains the twenty-byte adjustment is a
//       compiler convention, not a semantic difference; see the .cpp's note on
//       the GCC/MSVC split. The observable fact - ESP balanced on exit - is
//       measured by the model test, not asserted here.)
//     * `ADD EAX,0x4` is arithmetic on whatever the callee returned, with no
//       test: a null callee result is not caught here.
//
// WHAT IS NOT CLAIMED
//  * The SDK name of this function. It is in the same address neighbourhood as
//    0x00b25f40 (a kCivilization scan over the same callee) and 0x00b25fb0,
//    and the semantic-caller list in docs/analysis/simulator-root-closure.md
//    carries 0x00b25ca0 alongside 0x00b25f40. That is a NEIGHBOURHOOD, not an
//    identity: no witness names this entry, and a name implying a city or
//    civilization domain would be borrowed. The symbol below says "noun
//    projection city range" only because the callee is the noun projection
//    and the range is that projection's element range - both witnessed - and
//    stops there. 0x00bf9820's metadata uses the phrase "city ownership
//    enumeration wrapper"; that is a CALLER's reading and is NOT adopted.
//  * The receiver's class name. `cGameNounManager` is what the closure
//    document records for the callee and for the 0x00b3d300 source, and this
//    package models the receiver as an opaque extent of 0x9c+1 bytes
//    (through the `+0x9c` word the callee compares against) rather than
//    declaring a struct with member names. No member of the receiver is
//    touched by 0x00b25ca0 itself.
//  * What the five immediates DO beyond "four are called by the callee and one
//    is its key operand". Their identities - which callback is the create, the
//    clear, the add, the filter - are the callee's parameter roles and are not
//    established by this body's eight instructions. They are carried as
//    opaque 32-bit constants with the arity and calling roles the callee's
//    listing shows.
//  * The value of the key operand 0x018c816a. It is a data address whose eight
//    bytes read as zero on this snapshot; whether it is a live global, a
//    zero-initialised slot or a BSS cell is not established here.
//  * Ownership of the returned range. The callee's return is borrowed; this
//    body adds a bias and hands it on. No AddRef, no store, no release, and no
//    null check appears in the body, and none is modelled.
//  * That the biased pointer is dereferenceable. With a null callee result the
//    ADD produces 0x00000004, which is a value the body publishes without
//    complaint. That is a property of the machine code and is modelled, not a
//    bug in the reconstruction.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b25ca0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00B25CA0_THISCALL __thiscall
#else
#define PKG_00B25CA0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00b25ca0_noun_city_range {

// The element type of the projected noun list. The callee's own loop walks its
// node links with `ADD ESI,-0xc`, i.e. a 0xc-byte node, and every sampled
// consumer of the returned range steps the range by 4 (`iVar3 = iVar3 + 4`
// in FUN_00bf0b00; `>> 2` on the end-minus-begin span in FUN_00b25f40), so the
// range holds 32-bit words. Typed as a word because that is all the evidence
// fixes; no noun identity is claimed for a word.
using NounRangeWord = std::uint32_t;

// THE RETURNED VALUE, in the shape the callers use it: a {begin, end} pair.
//   offset 0x00  begin   (first element, inclusive)
//   offset 0x04  end     (one past the last element, exclusive)
// Nothing here names a vector, because the machine never returns a vector here:
// it returns the callee's vector pointer BIASED BY 4, which is the address of
// that vector's `begin` field. `end` is at begin+4 because `begin` sits at
// +0x04 in the callee's vector, so `end` lands at +0x08. Both offsets are
// witnessed twice: by the callee's layout static_asserts and by callers
// reading [EAX] and [EAX+4].
struct NounRange {
  NounRangeWord* begin;
  NounRangeWord* end;
};

// The receiver, modelled at exactly the extent the callee is witnessed
// reaching: through the word at +0x9c, which the callee compares its key
// operand against. 0xa0 bytes, 4-byte aligned. This is a MODELLING BOUND on
// the prefix the callee touches, NOT a recovered allocation size, and NOT a
// claim about the receiver's class - no member is declared, because
// 0x00b25ca0 touches none and the callee's field identities are its own
// package's business.
struct alignas(4) OpaqueNounProjection {
  std::array<std::uint8_t, 0xa0> opaque_bytes{};  // 0x00..0x9f
};

// The byte-displacement the body adds to the callee's return. OBSERVED as the
// imm8 of `83 c0 04`. It is a FIELD BIAS, and the field it lands on is
// `begin` - see evidence note 5.
constexpr std::uint32_t kBeginFieldBias = 4;

// The five immediates, in PUSH order as the body emits them (0x00b25ca0 is the
// first push, 0x00b25cb4 the last). Because a call pushes arguments in reverse,
// the body's emission order is the REVERSE of the callee's argument order; the
// model's recording callee therefore receives them as
//   arg0 = kArg4AddCallback (pushed 4th)
//   arg1 = kArg3FilterCallback
//   arg2 = kArg2ClearCallback
//   arg3 = kArg1CreateCallback
//   arg4 = kArg5KeyOperand
// and the reverse() in the test is what pins that mapping rather than assuming
// it. Values are the imm32 of each `68` opcode, byte for byte.
constexpr std::uint32_t kArg5KeyOperand = 0x018c816a;   // push 1
constexpr std::uint32_t kArg4AddCallback = 0x00b1e500;  // push 2
constexpr std::uint32_t kArg3FilterCallback = 0x00b236c0;  // push 3
constexpr std::uint32_t kArg2ClearCallback = 0x00d3d420;  // push 4
constexpr std::uint32_t kArg1CreateCallback = 0x00b21080;  // push 5

// The order the body PUSHES them, i.e. descending address-of-argument.
constexpr std::uint32_t kPushOrder[5] = {
    kArg5KeyOperand, kArg4AddCallback, kArg3FilterCallback,
    kArg2ClearCallback, kArg1CreateCallback,
};

// The order the CALLEE receives them, i.e. ascending argument index. A cdecl
// push sequence pops into ascending slots, so this is kPushOrder reversed.
constexpr std::uint32_t kArgumentOrder[5] = {
    kArg1CreateCallback, kArg2ClearCallback, kArg3FilterCallback,
    kArg4AddCallback, kArg5KeyOperand,
};

// How many words the callee pops. OBSERVED twice and independently: the
// callee's final instruction is `RET 0x14` (0x00b21407), and this body pushes
// exactly five words. 0x14 == 20 == 5 * 4.
constexpr std::size_t kCalleePoppedBytes = 0x14;
constexpr std::size_t kStackArgumentWords = 5;

// The body is eight instructions and 34 bytes. The 34 is not asserted, it is
// the sum of the eight encodings - see kTargetEncoding.
constexpr std::size_t kTargetInstructionCount = 8;
constexpr std::size_t kTargetBodyBytes = 34;

// The encoding as read from 0x00b25ca0, one entry per instruction, so the
// model's claim about push order and the +4 bias is checkable against bytes and
// not only against prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    // 0x00b25ca0  PUSH 0x018c816a
    0x68, 0x6a, 0x81, 0x8c, 0x01,
    // 0x00b25ca5  PUSH 0x00b1e500
    0x68, 0x00, 0xe5, 0xb1, 0x00,
    // 0x00b25caa  PUSH 0x00b236c0
    0x68, 0xc0, 0x36, 0xb2, 0x00,
    // 0x00b25caf  PUSH 0x00d3d420
    0x68, 0x20, 0xd4, 0xd3, 0x00,
    // 0x00b25cb4  PUSH 0x00b21080
    0x68, 0x80, 0x10, 0xb2, 0x00,
    // 0x00b25cb9  CALL 0x00b21340   (rel32 = -0x497e, little endian)
    0xe8, 0x82, 0xb6, 0xff, 0xff,
    // 0x00b25cbe  ADD EAX,0x4
    0x83, 0xc0, 0x04,
    // 0x00b25cc1  RET
    0xc3,
};

// Decode the little-endian imm32 that begins at `offset` in kTargetEncoding.
// Defined for the encoding array so the test can read each push's operand out
// of the bytes instead of restating it.
constexpr std::uint32_t read_imm32(std::size_t offset) {
  return static_cast<std::uint32_t>(kTargetEncoding[offset]) |
         (static_cast<std::uint32_t>(kTargetEncoding[offset + 1]) << 8) |
         (static_cast<std::uint32_t>(kTargetEncoding[offset + 2]) << 16) |
         (static_cast<std::uint32_t>(kTargetEncoding[offset + 3]) << 24);
}

// x86-32 thiscall with a FORWARDED ECX receiver: the body pushes five words
// for the callee, does not touch ECX, and ends in a bare RET because the
// callee already popped its own twenty bytes. Return: the callee's pointer,
// biased by kBeginFieldBias.
using NounRangeWrapper = NounRange* (PKG_00B25CA0_THISCALL*)(
    OpaqueNounProjection* receiver);

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(NounRangeWord) == 4,
              "the range is walked with a 4-byte stride by its callers");
static_assert(sizeof(NounRange) == 8,
              "the callers read exactly two words out of the returned pointer");
static_assert(offsetof(NounRange, begin) == 0x00,
              "begin is the first word of the returned pair");
static_assert(offsetof(NounRange, end) == 0x04,
              "end is the second word of the returned pair");
static_assert(sizeof(OpaqueNounProjection) == 0xa0,
              "modelled receiver extent runs through the +0x9c word");
static_assert(0x9c + sizeof(std::uint32_t) == sizeof(OpaqueNounProjection),
              "the +0x9c word ends the modelled extent");

// The immediate at each push is read out of the encoding, so the header's five
// constants and the body's five bytes cannot drift apart silently. Each PUSH
// imm32 is opcode 0x68 followed by the little-endian operand.
static_assert(kTargetEncoding[0] == 0x68u && read_imm32(1) == kArg5KeyOperand,
              "push 1 is PUSH 0x018c816a");
static_assert(kTargetEncoding[5] == 0x68u && read_imm32(6) == kArg4AddCallback,
              "push 2 is PUSH 0x00b1e500");
static_assert(kTargetEncoding[10] == 0x68u &&
                  read_imm32(11) == kArg3FilterCallback,
              "push 3 is PUSH 0x00b236c0");
static_assert(kTargetEncoding[15] == 0x68u &&
                  read_imm32(16) == kArg2ClearCallback,
              "push 4 is PUSH 0x00d3d420");
static_assert(kTargetEncoding[20] == 0x68u &&
                  read_imm32(21) == kArg1CreateCallback,
              "push 5 is PUSH 0x00b21080");

// 0x68 is PUSH imm32. It is NOT a memory push: those are 0xff (group 5) or
// 0x35/0x3d/0x0f-prefixed forms. Every one of the five opcodes is 0x68, which
// is the statement that these five constants are numbers, not five reads.
static_assert(kTargetEncoding[0] == 0x68u && kTargetEncoding[5] == 0x68u &&
                  kTargetEncoding[10] == 0x68u && kTargetEncoding[15] == 0x68u &&
                  kTargetEncoding[20] == 0x68u,
              "all five immediates are PUSH imm32, not memory loads");
static_assert(kTargetEncoding[0] != 0xffu && kTargetEncoding[0] != 0x35u,
              "0xff/0x35 would be a memory operand, not an immediate");

// The CALL's rel32 is negative (the callee is at a LOWER address) and resolves
// to 0x00b21340 from the instruction after it, 0x00b25cbe.
static_assert(kTargetEncoding[25] == 0xe8u,
              "0x00b25cb9 is a direct relative CALL");
static_assert(static_cast<std::int32_t>(read_imm32(26)) ==
                  static_cast<std::int32_t>(-0x497e),
              "the CALL's rel32 is the signed offset 0x00b21340 - 0x00b25cbe");
static_assert((0x00b25cbeu - 0x497eu) == 0x00b21340u,
              "the rel32 lands on the noun projection callee 0x00b21340");

// `83 c0 04` is ADD EAX,imm8. The ModRM 0xc0 is mod=11 (register, no
// displacement), reg=000 (EAX); 0x83 /0 is ADD r/m32,imm8.
static_assert(kTargetEncoding[30] == 0x83u,
              "0x00b25cbe is the ADD r/m32,imm8 form, not 05 (ADD EAX,imm32)");
static_assert((kTargetEncoding[31] >> 6) == 3u,
              "ModRM mod=11 selects a register operand, so no disp follows");
static_assert(((kTargetEncoding[31] >> 3) & 7u) == 0u,
              "ModRM reg=000 selects the ADD /0 form");
static_assert((kTargetEncoding[31] & 7u) == 0u,
              "ModRM rm=000 selects EAX, the return register");
static_assert(kTargetEncoding[32] == kBeginFieldBias,
              "the added immediate is the header's begin-field bias");

// The RET is bare (0xc3), not `RET imm16` (0xc2): this body pops nothing of
// its own, because the callee's RET 0x14 already consumed the five words.
static_assert(kTargetEncoding[33] == 0xc3u && kTargetEncoding[33] != 0xc2u,
              "0x00b25cc1 is a bare RET");

// The body is whole: eight encodings summing to 34 bytes, with no ninth
// instruction and no leftover byte.
static_assert(5u + 5u + 5u + 5u + 5u + 5u + 3u + 1u == kTargetBodyBytes,
              "34 bytes is the sum of the eight encodings, so the listing is whole");
static_assert(kTargetBodyBytes == 34u && kTargetInstructionCount == 8u,
              "eight instructions, 34 bytes");
static_assert(kCalleePoppedBytes == kStackArgumentWords * 4u,
              "the callee's 0x14 cleanup is exactly five pushed words");
static_assert(kCalleePoppedBytes == 20u, "0x14 is the value 20");
static_assert(kBeginFieldBias == 4u, "the bias is 4");
static_assert(kBeginFieldBias == offsetof(NounRange, end),
              "the callee's begin field sits where the returned pair's end does");

// The modelled entry carries the forwarded ECX receiver and returns one
// pointer; it declares no ordinary stack argument, which is what the bare RET
// and the callee-owned cleanup jointly require.
static_assert(std::is_same<NounRangeWrapper,
                           NounRange* (PKG_00B25CA0_THISCALL*)(
                               OpaqueNounProjection*)>::value,
              "the modelled entry is thiscall with an ECX receiver and no "
              "stack argument");
static_assert(sizeof(NounRangeWrapper) == sizeof(void*),
              "the modelled entry is a plain function pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00b25ca0.
NounRange* PKG_00B25CA0_THISCALL noun_city_range_00b25ca0(
    OpaqueNounProjection* receiver);

}

#undef PKG_00B25CA0_THISCALL
