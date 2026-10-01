// 0x00c77bf0 -- bucket membership probe with insert-on-miss.
//
// SporeApp.exe 3.1.0.22. Clean-room reconstruction from the machine listing
// only; the listing is transcribed below as bytes so the transcription itself
// is under test and every constant in this header is DECODED from those bytes
// rather than restated beside them.
//
// WHAT THE BODY IS
// ----------------
// Thirty-nine instructions, ninety-five bytes, one frame, no indirect
// transfer, no data-segment address, one callee:
//
//   0x00c77bf0  SUB ESP,0x10
//   0x00c77bf3  PUSH EBX / PUSH ESI / PUSH EDI
//   0x00c77bf6  MOV EDI,dword ptr [ESP+0x20]     ; the one stack argument
//   0x00c77bfa  ADD ECX,0x111c                    ; bias the receiver base
//   0x00c77c00  XOR EDX,EDX                      ; high dividend half = 0
//   0x00c77c02  MOV EAX,EDI                       ; low half = the key
//   0x00c77c04  DIV dword ptr [ECX+0x8]           ; EDX = key % bucket_count
//   0x00c77c07  MOV EAX,dword ptr [ECX+0x4]       ; the bucket pointer
//   0x00c77c0a  XOR ESI,ESI                       ; the match counter
//   0x00c77c0c  MOV EDX,dword ptr [EAX+EDX*0x4]   ; first node of the bucket
//   0x00c77c0f  TEST EDX,EDX / JZ 0x00c77c1f      ; null ends the walk
//   0x00c77c13  CMP EDI,dword ptr [EDX]           ; node->key == key ?
//   0x00c77c15  JNZ 0x00c77c18
//   0x00c77c17  INC ESI                           ; count the match
//   0x00c77c18  MOV EDX,dword ptr [EDX+0x4]       ; node->next
//   0x00c77c1b  TEST EDX,EDX / JNZ 0x00c77c13     ; loop
//   0x00c77c1f  TEST ESI,ESI
//   0x00c77c21  SETNZ BL                          ; present := (matches != 0)
//   0x00c77c24  TEST BL,BL
//   0x00c77c26  JNZ 0x00c77c44                    ; a hit skips the insert
//   0x00c77c28  MOV byte ptr [ESP+0x20],BL        ; one byte into the ARG slot
//   0x00c77c2c  MOV EDX,dword ptr [ESP+0x20]      ; read that word back
//   0x00c77c30  PUSH EDX                          ; third argument
//   0x00c77c31  LEA EAX,[ESP+0x10]                ; &value   (the key)
//   0x00c77c35  PUSH EAX
//   0x00c77c36  LEA EDX,[ESP+0x18]                ; &container (12 bytes)
//   0x00c77c3a  PUSH EDX                          ; first argument
//   0x00c77c3b  MOV dword ptr [ESP+0x18],EDI      ; value = key
//   0x00c77c3f  CALL 0x00de5df0
//   0x00c77c44  POP EDI / POP ESI
//   0x00c77c46  MOV AL,BL                         ; return the flag
//   0x00c77c48  POP EBX
//   0x00c77c49  ADD ESP,0x10
//   0x00c77c4c  RET 0x4
//
// It hashes the key into one bucket of a chained hash table held by its
// receiver, counts every node in that chain whose key matches, and -- only when
// the count is zero -- hands the key to 0x00de5df0. The return value is the
// boolean "was it already there", NOT the result of the insert.
//
// WHAT IS CLAIMED, AND WHAT IS NOT
// --------------------------------
// Claimed from the listing above, and only from it:
//   * the two receiver words, at displacements 0x1120 (a pointer to a dword
//     array) and 0x1124 (a divisor);
//   * the bucket index is the UNSIGNED REMAINDER of the key modulo the
//     divisor, and the bucket is read at a FOUR-BYTE stride;
//   * the chain node layout: a key dword at +0 and a next pointer at +4;
//   * the walk counts every match and does not stop at the first;
//   * the insert happens on a miss only, exactly once, with three arguments;
//   * the entry pops its own single stack argument (`RET 0x4`).
//
// NOT claimed, deliberately:
//   * the IDENTITY of the receiver, of the two fields at +0x1120/+0x1124, and
//     of the chain nodes. The machine gives displacements and access widths,
//     nothing more, so the receiver is an incomplete type and the image the
//     model test drives it against is a flat dword run. No member name, no
//     class, no vtable, no SDK symbol.
//   * the semantics of 0x00de5df0. Only the three values this body hands it are
//     modelled, plus the fact that it removes its own three words (see the
//     stack accounting below).
//   * the upper three bytes of EAX. The body writes only AL (0x00c77c46), so
//     the contract is "AL is 0 or 1"; the rest of EAX is whatever the last
//     DIV-loaded table pointer left there and nothing here reads it.
//   * any runtime behaviour. Nothing was executed on the original process.
//
// THE SUBTLE PART: the third argument is NOT a literal zero
// ---------------------------------------------------------
// Ghidra's decompilation renders the third argument as `0`. The byte listing
// says otherwise, and the listing wins. 0x00c77c28 stores ONE byte -- the BL
// the SETNZ produced -- into the dword at [ESP+0x20], which is entry ESP+0x4,
// i.e. the caller's own argument slot, the very word EDI was loaded from at
// 0x00c77bf6. 0x00c77c2c then reads that dword back and pushes it. The only
// path that reaches 0x00c77c28 is the fall-through of `TEST BL,BL / JNZ`, so
// BL is provably 0 there and the stored byte is 0. The value handed over is
// therefore the key with its low byte cleared: `key & 0xffffff00`.
//
// This is the reading that makes the byte store load-bearing rather than dead,
// and it is the one the package claims. A reconstruction that passes a literal
// 0 is wrong for every key whose low byte is set, which is most of them. Both
// readings are carried in the model test as opposing mutants, so the choice is
// adjudicated rather than assumed. What the package does NOT claim is the
// original source expression that produced it -- `key & ~0xffu` and a stale
// stack slot are indistinguishable at this boundary, and only the value the
// callee observes is recoverable.
//
// THE STACK ACCOUNTING, and why the callee cleans its own words
// --------------------------------------------------------------
// Three words enter immediately before CALL 0x00de5df0 and the body removes
// none of them: after the call the next instruction is `POP EDI`. The only way
// the epilogue can be coherent -- three POPs, `ADD ESP,0x10`, then `RET 0x4`
// landing the caller exactly where it started -- is for the callee to remove
// all twelve. So 0x00de5df0 is modelled as a callee-cleanup three-argument
// function, and the model test MEASURES the entry's net stack effect through a
// trampoline calibrated against control callees that pop 0, 4, 8 and 12 bytes,
// so a body that left the three words behind would be seen to come back
// twelve bytes out rather than being believed.
//
// The mutation test: sixteen deliberately wrong bodies live in the model test,
// are driven through the SAME battery the reconstruction is graded by, and
// each is REQUIRED to be refuted. The battery was additionally checked from
// OUTSIDE, by perturbing this package's own .cpp and .hpp in a copy of the
// directory and rebuilding BOTH translation units from the mutated copy under
// the promotion gate (clang++ -std=c++17 -Wall -Wextra -Werror -m32).
// `mutation_test.sh` runs that check and fails if any perturbation survives.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "0x00c77bf0 is an x86-32 reconstruction (ECX receiver, 32-bit absolute callees)"
#endif

// Calling conventions, each spelled once. The entry is __thiscall: receiver in
// ECX, one word on the stack, and the entry removes that word itself (clang
// and gcc both emit `ret $4` for thiscall on i386, which is what 0x00c77c4c
// is). The callee is modelled as callee-cleanup, which is what the three
// un-removed PUSHes above it require.
#if defined(_MSC_VER)
#define PKG_00C77BF0_CALL __thiscall
#define PKG_00C77BF0_CALLEE __stdcall
#else
#define PKG_00C77BF0_CALL __attribute__((thiscall))
#define PKG_00C77BF0_CALLEE __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes transcribed above.
// ---------------------------------------------------------------------------

constexpr std::uint8_t kTargetBytes[95] = {
    0x83, 0xec, 0x10,                    // 0x00c77bf0 SUB ESP,0x10
    0x53,                                // 0x00c77bf3 PUSH EBX
    0x56,                                // 0x00c77bf4 PUSH ESI
    0x57,                                // 0x00c77bf5 PUSH EDI
    0x8b, 0x7c, 0x24, 0x20,              // 0x00c77bf6 MOV EDI,[ESP+0x20]
    0x81, 0xc1, 0x1c, 0x11, 0x00, 0x00,  // 0x00c77bfa ADD ECX,0x111c
    0x33, 0xd2,                          // 0x00c77c00 XOR EDX,EDX
    0x8b, 0xf8,                          // 0x00c77c02 MOV EAX,EDI
    0xf7, 0x71, 0x08,                    // 0x00c77c04 DIV [ECX+0x8]
    0x8b, 0x41, 0x04,                    // 0x00c77c07 MOV EAX,[ECX+0x4]
    0x33, 0xf6,                          // 0x00c77c0a XOR ESI,ESI
    0x8b, 0x14, 0x90,                    // 0x00c77c0c MOV EDX,[EAX+EDX*0x4]
    0x85, 0xd2,                          // 0x00c77c0f TEST EDX,EDX
    0x74, 0x0c,                          // 0x00c77c11 JZ 0x00c77c1f
    0x3b, 0x3a,                          // 0x00c77c13 CMP EDI,[EDX]
    0x75, 0x01,                          // 0x00c77c15 JNZ 0x00c77c18
    0x46,                                // 0x00c77c17 INC ESI
    0x8b, 0x52, 0x04,                    // 0x00c77c18 MOV EDX,[EDX+0x4]
    0x85, 0xd2,                          // 0x00c77c1b TEST EDX,EDX
    0x75, 0xf4,                          // 0x00c77c1d JNZ 0x00c77c13
    0x85, 0xf6,                          // 0x00c77c1f TEST ESI,ESI
    0x0f, 0x95, 0xc3,                    // 0x00c77c21 SETNZ BL
    0x84, 0xdb,                          // 0x00c77c24 TEST BL,BL
    0x75, 0x1c,                          // 0x00c77c26 JNZ 0x00c77c44
    0x88, 0x5c, 0x24, 0x20,              // 0x00c77c28 MOV [ESP+0x20],BL
    0x8b, 0x54, 0x24, 0x20,              // 0x00c77c2c MOV EDX,[ESP+0x20]
    0x52,                                // 0x00c77c30 PUSH EDX
    0x8d, 0x44, 0x24, 0x10,              // 0x00c77c31 LEA EAX,[ESP+0x10]
    0x50,                                // 0x00c77c35 PUSH EAX
    0x8d, 0x54, 0x24, 0x18,              // 0x00c77c36 LEA EDX,[ESP+0x18]
    0x52,                                // 0x00c77c3a PUSH EDX
    0x89, 0x7c, 0x24, 0x18,              // 0x00c77c3b MOV [ESP+0x18],EDI
    0xe8, 0xac, 0xe1, 0x16, 0x00,        // 0x00c77c3f CALL 0x00de5df0
    0x5f,                                // 0x00c77c44 POP EDI
    0x5e,                                // 0x00c77c45 POP ESI
    0x8a, 0xc3,                          // 0x00c77c46 MOV AL,BL
    0x5b,                                // 0x00c77c48 POP EBX
    0x83, 0xc4, 0x10,                    // 0x00c77c49 ADD ESP,0x10
    0xc2, 0x04, 0x00,                    // 0x00c77c4c RET 0x4
};

static_assert(kTargetBytes[0] == 0x83 && kTargetBytes[1] == 0xec &&
                  kTargetBytes[2] == 0x10,
              "0x00c77bf0 opens with 83 EC 10: SUB ESP,0x10, so the body opens a "
              "sixteen-byte frame and the incoming word at entry ESP+0x4 is "
              "reached at ESP+0x20, not ESP+0x4");
static_assert(kTargetBytes[6] == 0x8b && kTargetBytes[7] == 0x7c &&
                  kTargetBytes[8] == 0x24 && kTargetBytes[9] == 0x20,
              "0x00c77bf6 is 8B 7C 24 20: MOV EDI,dword ptr [ESP+0x20], which is "
              "the argument word -- and which is why the argument is read into "
              "a register before ECX is biased");
static_assert(kTargetBytes[20] == 0xf7 && kTargetBytes[21] == 0x71 &&
                  kTargetBytes[22] == 0x08,
              "0x00c77c04 is F7 71 08: the /6 group opcode DIV with ModRM 0x71, "
              "whose reg field 6 selects the unsigned long divide that leaves "
              "the REMAINDER in EDX -- the bucket index -- and the ModRM's "
              "rm field 1 names ECX+disp8 as the divisor");
static_assert(kTargetBytes[23] == 0x8b && kTargetBytes[24] == 0x41 &&
                  kTargetBytes[25] == 0x04,
              "0x00c77c07 is 8B 41 04: MOV EAX,dword ptr [ECX+0x4], the bucket "
              "array pointer, read AFTER the divide and out of the same biased "
              "base the divisor came from");
static_assert(kTargetBytes[28] == 0x8b && kTargetBytes[29] == 0x14 &&
                  kTargetBytes[30] == 0x90,
              "0x00c77c0c is 8B 14 90: the SIB byte 0x90 scales the index by "
              "FOUR, so a bucket is a four-byte slot, not a byte");
static_assert(kTargetBytes[35] == 0x3b && kTargetBytes[36] == 0x3a,
              "0x00c77c13 is 3B 3A: a 32-bit CMP of the key against dword ptr "
              "[EDX], which fixes the node's key at displacement 0");
static_assert(kTargetBytes[40] == 0x8b && kTargetBytes[41] == 0x52 &&
                  kTargetBytes[42] == 0x04,
              "0x00c77c18 is 8B 52 04: MOV EDX,dword ptr [EDX+0x4], so the "
              "chain link is at displacement 4 -- a different word from the key");
static_assert(kTargetBytes[49] == 0x0f && kTargetBytes[50] == 0x95 &&
                  kTargetBytes[51] == 0xc3,
              "0x00c77c21 is 0F 95 C3: SETNZ BL, so the flag is a BYTE and not "
              "the EAX dword -- the return contract is AL, nothing wider");
static_assert(kTargetBytes[56] == 0x88 && kTargetBytes[57] == 0x5c &&
                  kTargetBytes[58] == 0x24 && kTargetBytes[59] == 0x20,
              "0x00c77c28 is 88 5C 24 20: opcode 88 is a ONE-BYTE store into "
              "dword ptr [ESP+0x20] -- the argument slot, now holding BL");
static_assert(kTargetBytes[75] == 0x89 && kTargetBytes[76] == 0x7c &&
                  kTargetBytes[77] == 0x24 && kTargetBytes[78] == 0x18,
              "0x00c77c3b is 89 7C 24 18: a four-byte store of EDI into the slot "
              "the second LEA named, so the value handed over by address is the "
              "key");
static_assert(kTargetBytes[84] == 0x5f && kTargetBytes[85] == 0x5e &&
              kTargetBytes[86] == 0x8a && kTargetBytes[87] == 0xc3 &&
              kTargetBytes[88] == 0x5b,
              "the epilogue is POP EDI / POP ESI / MOV AL,BL / POP EBX: nothing "
              "between the CALL and the first POP touches the stack, so the "
              "three words the CALL consumed were removed by the callee");
static_assert(kTargetBytes[92] == 0xc2 && kTargetBytes[93] == 0x04 &&
                  kTargetBytes[94] == 0x00,
              "0x00c77c4c is C2 04 00: RET 4, so the entry pops one word of its "
              "own -- the single argument -- and the caller does not");

// Entry, terminal, and the size of the body between them.
constexpr std::size_t kEntryVa = 0x00c77bf0u;
constexpr std::size_t kTerminalVa = 0x00c77c4cu;
constexpr std::size_t kBodyBytes = 95u;
constexpr std::size_t kInstructionCount = 39u;
constexpr std::size_t kCalleeCount = 1u;
constexpr std::size_t kConditionalBranches = 4u;  // JZ, JNZ, JNZ, JNZ
static_assert(kEntryVa + kBodyBytes == 0x00c77c4fu,
              "0x00c77bf0 + 95 bytes ends at 0x00c77c4f, one past the RET imm16 "
              "at 0x00c77c4e and one past the last body byte");
static_assert(kTerminalVa - kEntryVa == 92u,
              "the terminal is the thirty-ninth instruction, ninety-two bytes "
              "after entry");
static_assert(kCalleeCount == 1u && kConditionalBranches == 4u,
              "the body reaches exactly one callee and takes exactly four "
              "conditional branches");

// The receiver's ECX bias, DECODED from the four operand bytes 1C 11 00 00 of
// the 81 C1 at 0x00c77bfa rather than restated.
constexpr std::size_t kReceiverBias = static_cast<std::size_t>(
    static_cast<std::uint32_t>(kTargetBytes[12]) |
    (static_cast<std::uint32_t>(kTargetBytes[13]) << 8) |
    (static_cast<std::uint32_t>(kTargetBytes[14]) << 16) |
    (static_cast<std::uint32_t>(kTargetBytes[15]) << 24));
static_assert(kReceiverBias == 0x111cu,
              "operand bytes 1C 11 00 00 of the ADD ECX at 0x00c77bfa are the "
              "little-endian immediate 0x111c");

// The two receiver words, in POST-BIAS displacements, each decoded from the
// disp8 of the instruction that reads it.
constexpr std::size_t kBucketArrayDisplacement =
    kReceiverBias + static_cast<std::size_t>(kTargetBytes[25]);
constexpr std::size_t kBucketCountDisplacement =
    kReceiverBias + static_cast<std::size_t>(kTargetBytes[22]);
static_assert(kBucketArrayDisplacement == 0x1120u,
              "disp8 04 of the MOV at 0x00c77c07 over a base biased by 0x111c is "
              "0x1120: the dword array of buckets");
static_assert(kBucketCountDisplacement == 0x1124u,
              "disp8 08 of the DIV at 0x00c77c04 over a base biased by 0x111c is "
              "0x1124: the divisor, i.e. the number of buckets");

// The frame arithmetic that fixes the argument slot. SUB ESP,0x10 plus three
// PUSHes, so entry ESP+0x4 is at ESP+0x20 once inside -- which is the
// displacement both the load at 0x00c77bf6 and the byte store at 0x00c77c28 use.
constexpr std::size_t kFrameBytes = 0x10u;
constexpr std::size_t kSavedRegisterPushes = 3u;
constexpr std::size_t kArgumentSlotDisplacement =
    kFrameBytes + kSavedRegisterPushes * sizeof(Word) + sizeof(Word);
static_assert(kArgumentSlotDisplacement == 0x20u,
              "a sixteen-byte frame plus three saved registers plus the return "
              "address puts entry ESP+0x4 at ESP+0x20, the displacement the "
              "0x00c77bf6 load and the 0x00c77c28 store both state");

// The width of the store at 0x00c77c28. Opcode 88 is a one-byte move, so the
// word pushed at 0x00c77c30 is the key with exactly its low byte replaced by
// BL, and BL is 0 on the only path that reaches the store.
constexpr std::size_t kArgumentSlotStoreWidthBytes = 1u;
constexpr Word kArgumentSlotLowByteMask =
    ~static_cast<Word>((Word(1) << (8u * kArgumentSlotStoreWidthBytes)) - Word(1));
static_assert(kArgumentSlotLowByteMask == 0xffffff00u,
              "a one-byte store into the argument word leaves the upper three "
              "bytes alone, so the value handed to 0x00de5df0 as its third "
              "argument is the key with its low byte cleared");

// The node layout, from the two displacements in the chain walk.
constexpr std::size_t kNodeKeyDisplacement = 0u;
constexpr std::size_t kNodeNextDisplacement =
    static_cast<std::size_t>(kTargetBytes[42]);
static_assert(kNodeKeyDisplacement == 0u && kNodeNextDisplacement == 4u,
              "the chain walk compares dword ptr [EDX] and follows dword ptr "
              "[EDX+0x4]: the key is the first word and the link is the second, "
              "and they are different words");

// The bucket index, decoded from the DIV's reg field and the SIB scale.
constexpr std::size_t kBucketIndexIsRemainder = 1u;  // F7 /6 leaves EDX = rem
constexpr std::size_t kBucketSlotBytes =
    static_cast<std::size_t>(1u) << (static_cast<std::size_t>(kTargetBytes[30]) >> 6);
static_assert(kBucketIndexIsRemainder == 1u,
              "the divide is the unsigned long form (F7 /6), whose quotient goes "
              "to EAX and whose remainder goes to EDX -- and the SIB that indexes "
              "the bucket array uses EDX");
static_assert(kBucketSlotBytes == 4u,
              "SIB byte 0x90 carries scale 10b, i.e. a four-byte bucket stride");

// The callee's address, decoded from the rel32 of the E8 at 0x00c77c3f. The
// displacement is relative to the END of that five-byte instruction, which is
// kEntryVa + 79 + 5.
constexpr std::size_t kCallOpcodeIndex = 79u;
static_assert(kTargetBytes[kCallOpcodeIndex] == 0xe8u,
              "byte 79 of the transcription is the E8 of the body's only call");
constexpr Word rel32_target(std::size_t at) {
  return static_cast<Word>(
      kEntryVa + at + 5 +
      static_cast<Word>(static_cast<std::int32_t>(
          static_cast<std::uint32_t>(kTargetBytes[at + 1]) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 2]) << 8) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 3]) << 16) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 4]) << 24))));
}
constexpr Word kCalleeVa = rel32_target(kCallOpcodeIndex);
static_assert(kCalleeVa == 0x00de5df0u,
              "the rel32 at 0x00c77c3f resolves to 0x00de5df0, the three-"
              "argument callee the decompilation names at the same site");

// Stack accounting, stated as numbers so the model test can assert them.
constexpr std::size_t kOrdinaryStackArgumentSlots = 1u;
constexpr std::size_t kEntryCleanupBytes = 4u;        // RET 0x4
constexpr std::size_t kCalleeStackArgumentWords = 3u;  // three PUSHes
constexpr std::size_t kCalleeCleanupBytes = 3u * sizeof(Word);
static_assert(kEntryCleanupBytes == sizeof(Word),
              "RET 4 removes one word, and the body read exactly one word off "
              "its own stack (entry ESP+0x4)");
static_assert(kCalleeCleanupBytes == 12u,
              "three words enter in front of the call and the body removes "
              "none of them, so the callee removes all twelve");

// The size of the 12-byte local the first argument points at: the distance from
// the LEA at 0x00c77c36 to the value slot the LEA at 0x00c77c31 named, plus the
// four bytes of that slot. Both are stack displacements, so the difference is
// frame arithmetic rather than a guessed size.
// The container lies ABOVE the value slot: the second LEA names ESP+0x18 and
// the first names ESP+0x10, so the twelve-byte object starts eight bytes higher
// and runs up to the frame's top, and the four-byte key slot sits directly
// below it. `kContainerLocalBytes` is that eight-byte gap plus the width of the
// slot, decoded from the two disp8 operands rather than restated. The DIRECTION
// is stated here and is not asserted of the reconstruction: which way round a
// compiler lays two adjacent locals out is its own choice, and the machine only
// ever shows two addresses.
constexpr std::size_t kContainerLocalBytes =
    static_cast<std::size_t>(kTargetBytes[73]) -
    static_cast<std::size_t>(kTargetBytes[68]) + sizeof(Word);
static_assert(kContainerLocalBytes == 12u,
              "the two LEAs name ESP+0x18 and ESP+0x10, twelve bytes apart, so "
              "the first argument is the address of a twelve-byte stack object");

// ---------------------------------------------------------------------------
// The modelled receiver and node.
//
// Both are INCOMPLETE on purpose. The machine gives a displacement and an
// access width and nothing else, so a member name or a class here would be a
// claim no evidence in this package corroborates.
// ---------------------------------------------------------------------------

// A guard band above the two fields, so the model test can prove the body reads
// nothing above +0x1124 and writes nothing anywhere in the image.
constexpr std::size_t kGuardWords = 4;
constexpr std::size_t kImageWords =
    kBucketCountDisplacement / sizeof(Word) + 1 + kGuardWords;
constexpr Word kGuardCanary = 0xa5a5a5a5u;

struct BucketTable;

struct BucketTableImage {
  Word words[kImageWords];
};
extern BucketTableImage g_bucket_table_image;

std::uint8_t* image_bytes();

// Reads the dword at `displacement` from `base`, the way the machine's dword
// loads do. The displacement is a parameter rather than a baked-in constant so
// the mutants can be driven through the very same accessor the entry uses.
Word word_at(const std::uint8_t* base, std::size_t displacement);

// The bucket load, as the machine states it: a dword at `byte_offset` into the
// array the receiver holds. The offset is a parameter rather than a baked-in
// multiple so a body that drops the SIB scale of four can be expressed as the
// single-token slip it is.
Word bucket_word(const Word* buckets, std::size_t byte_offset);

// A chain node, as the walk sees it: the key word, then the link word. The
// entry reads both through word_at at the decoded displacements, so this
// struct is the test's storage and the machine's offsets are the entry's.
struct BucketNode {
  Word key;
  BucketNode* next;
};
static_assert(offsetof(BucketNode, key) == kNodeKeyDisplacement,
              "the node's key word sits at displacement 0");
static_assert(offsetof(BucketNode, next) == kNodeNextDisplacement,
              "the node's link word sits at displacement 4");

// ---------------------------------------------------------------------------
// The modelled callee, 0x00de5df0.
//
// Declared with THREE arguments and callee cleanup, because the three words the
// body pushes in front of it are the three it finds on the stack, and because
// the body removes none of them afterwards. Its own semantics are NOT
// reconstructed here: it records what it was handed and returns, which is all
// this body can observe of it.
// ---------------------------------------------------------------------------

struct InsertTraceEntry {
  Word container;  // first argument: the address of the twelve-byte local
  Word value;      // second argument: the address of the key slot
  Word context;    // third argument: the argument word with its low byte cleared
  Word value_at;   // *value, i.e. the dword the second argument points at
};

constexpr std::size_t kMaxInsertDepth = 4;
extern InsertTraceEntry g_insert_trace[kMaxInsertDepth];
extern std::size_t g_insert_depth;

void PKG_00C77BF0_CALLEE FUN_00de5df0(void* container, const Word* value,
                                     Word context);

// ---------------------------------------------------------------------------
// The machine ABI, as C++ types, so a wrong prototype fails to build.
//
// One receiver in ECX, one ordinary stack argument (the key), the entry
// removing that word itself, and a one-byte result in AL.
// ---------------------------------------------------------------------------

using AbiBucketMembershipInsert00c77bf0 =
    bool(PKG_00C77BF0_CALL*)(BucketTable*, Word);
static_assert(sizeof(AbiBucketMembershipInsert00c77bf0) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(void*) == 4u,
              "the modelled entry is a 32-bit code pointer, so this is an "
              "x86-32 reconstruction");
static_assert(sizeof(Word) == 4u, "the modelled word is one 32-bit dword");

// Entry point under reconstruction: does the receiver's table already hold this
// key, and if not, hand it to 0x00de5df0. Returns whether it was there.
bool PKG_00C77BF0_CALL bucket_membership_insert_00c77bf0(BucketTable* self,
                                                        Word key);

}  // namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership
