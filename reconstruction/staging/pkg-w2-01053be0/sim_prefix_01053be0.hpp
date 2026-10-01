// PKG-W2-01053BE0 -- VA 0x01053be0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// THE RECOVERED SPAN, AND WHAT IT IS NOT.
//
// The evidence pack (reconstruction/evidence/01053be0/evidence.json) carries 95
// instructions, 288 bytes, 0x01053be0..0x01053cff inclusive. All 288 bytes were
// read back from the image and are transcribed at the bottom of this file; they
// are exactly the 95 instructions of the listing at exactly its addresses, with
// nothing left over.
//
// That span is a PREFIX of a longer function, and the record says so itself:
//
//   parse.declared_count 95, parse.flow_complete false, completeness PARTIAL
//   parse.esp_unresolved true, unparsed 0, degraded false
//   abstained_because[0] "no_terminal_ret: the listing is a prefix of a longer function"
//   abstained_because[2] "truncated_listing: the last instruction is neither a
//                         return nor an out-of-listing transfer, so the listing
//                         stops mid-function"
//
// The last recovered instruction is 8d 49 00 -- LEA ECX,[ECX] at 0x01053cfd, a
// three-byte instruction with no operands and no transfer. Control therefore
// runs off the end of the recovered span. Nothing in the span returns.
//
// NO CONVENTION IS DECLARED IN THIS PACKAGE, ON PURPOSE.
//
// reconstruction/evidence/01053be0/evidence.json, category abi_derived, states
// field for field:
//
//   verdict                            : ABI_UNKNOWN
//   conventions.calling_convention     : null
//   conventions.confidence             : UNKNOWN
//   conventions.candidate_conventions  : ["__cdecl","__stdcall","__thiscall","__fastcall"]
//   conventions.ambiguities            : []
//   cleanup                            : {bytes null, side null, confidence UNKNOWN,
//                                        evidence null, corroboration not_available}
//   return                             : {register "ST0", register_class float_or_x87,
//                                        confidence APPROXIMATION, type null,
//                                        void_possible false,
//                                        aggregate_evidence.bulk_write false}
//
// A convention token in the entry would therefore be a choice, not a reading.
// This package declares none, and the reconstructed entry is a plain function
// whose first parameter is the word the record names as the receiver. The
// record DOES establish the receiver:
//
//   receiver {present true, register ECX, confidence INFERRED, bounds_only true,
//             shape R-ALIAS, distinct_offsets 1, offsets [0], max_offset 0,
//             written_through 0}
//
// and the body reads that word and copies it (MOV EDI,ECX at 0x01053be7, byte
// 8b f9) before any definite write to ECX (MOV ECX,EAX at 0x01053bee). The
// alias is why the record's shape is R-ALIAS, and the single enumerated offset
// 0x0 is the word the body loads through it at 0x01053ca0 (MOV EAX,[EDI], byte
// 8b 07). No other displacement is reached through the receiver, so no other
// field offset is claimed -- and because `bounds_only` is true, the empty part
// of that statement is an absence of observation, not a property of the object.
//
// NO CLASS, NO TABLE IDENTITY, NO RECEIVER TYPE, NO LAYOUT. `Receiver` and the
// object reached through it are declared and left undefined. The two computed
// transfers are modelled as computed transfers and nothing more: no slot
// boundary, no offset-to-slot mapping, no base-class relation is claimed, and
// the addresses named below are the addresses the listing itself contains.
//
// THE TAIL HOP: THERE IS NONE, AND NONE IS ASSERTED.
//
// This address is named in tools/reconstruction_tooling/evidence.py as one of
// the two for which a pre-existing `tail_call.target` field is PROVABLY WRONG,
// and it is the fixture 01053be0_second_wrong_tail_target in
// tests/fixtures/abi/vftable/ (tests/vftable_corpus.py, group "not_forwarded").
// The record this package judges against carries no target to read:
//
//   tail_call {present false, form null, target null, after_frame_setup false}
//
// That is the honest reading of the listing, and this package re-derives it from
// the instructions rather than taking it on trust:
//
//   * There is no RET anywhere in the 288 bytes.
//   * There is exactly ONE unconditional direct JMP in the span, at 0x01053c6a
//     (eb 2a), and its target 0x01053c96 is INSIDE the recovered span -- it is
//     control flow, not a transfer out of the body. The xref-export rule in
//     tools/reconstruction_tooling/validate.py filters exactly this case.
//   * Every other transfer out of the span is CONDITIONAL: JZ 0x01053c6c
//     (0x01053c0c), JZ 0x01053c96 (0x01053c42, 0x01053c73), JNZ 0x01053cf3
//     (0x01053cb0) and JLE 0x01053d3b (0x01053cf9). A conditional branch is not
//     an exit; control comes back.
//
// So the span has two ways out and neither is a tail hop:
//
//   exit 1  the JLE at 0x01053cf9 to 0x01053d3b, which is OUTSIDE the span;
//   exit 2  the fall-through at 0x01053d00, reached from 0x01053cfb (XOR EBX,EBX)
//           and 0x01053cfd (LEA ECX,[ECX]), also OUTSIDE the span.
//
// Neither is unconditional, neither is inside the recovered span, and the record
// names no convention to forward and no cleanup to forward. T1-FWD therefore
// cannot fire here on any of its preconditions, which is exactly what the
// fixture is named for. No tail target is asserted in this package, and no
// address outside the recovered span is claimed as the span's callee.
//
// FOR THE RECORD, AND LABELLED AS WHAT IT IS: reading the image PAST the
// recovered span (GhidraMCP /disassemble_bytes at 0x01053cff) shows that
// 0x01053d3b holds 5f 8b c6 5e 5d 5b 83 c4 18 c2 08 00 -- POP EDI; MOV EAX,ESI;
// POP ESI; POP EBP; POP EBX; ADD ESP,0x18; RET 0x8. That is where flow goes, and
// it is a continuation of the same function, not a callee. It is recorded here
// because the question "what does this body do at its exit" cannot be answered
// from the listing and this is the honest way to say so. It is NOT used as a
// basis for any claim the reconstruction makes: the return path, the epilogue,
// the 0x8 callee-side cleanup and the value left in EAX all lie outside the
// recovered span, none of them is modelled, and the entry therefore returns
// nothing the recovered span can be shown to produce.
//
// TWO FLOAT CONSTANTS, READ BACK FROM THE IMAGE, AND DEAD.
//
//   0x01477fbc  00 00 48 43  = 200.0f   (FLD float ptr [0x01477fbc], d9 05 bc 7f 47 01)
//   0x013f1cac  00 00 48 42  =  50.0f   (FLD float ptr [0x013f1cac], d9 05 ac 1c 3f 01)
//
// Each FLD is consumed by the FSTP that follows it (d9 5c 24 04 and d9 1c 24),
// so the x87 stack top is EMPTY at every point the recovered span can end. That
// is worth stating because the record's `return` sub-record names ST0 at
// APPROXIMATION confidence on the stated basis "an x87 or SSE instruction
// appears in the body" (inference RT1) -- a basis the byte transcript does not
// support inside this span. The disagreement is reported in the package's
// unresolved questions and is NOT resolved here.
//
// The two FSTPs write ESP+0x4 and ESP+0 after the SUB ESP,0x8 at 0x01053cb8.
// Nothing in the recovered span reads either cell again: the address the body
// goes on to pass to 0x00b3d350 is LEA EAX,[ESP+0x24] at 0x01053cbf, which is
// a different word. The two stores are therefore reproduced here, and no claim
// is made that either constant reaches any callee.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-w2-01053be0 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_w2_01053be0 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA, which is
// what binds this source span to 0x01053be0 in the validator.
inline constexpr std::uint32_t kTargetVa = 0x01053be0u;
inline constexpr std::uint32_t kSpanFirstByte = 0x01053be0u;
inline constexpr std::uint32_t kSpanLastByte = 0x01053cffu;
inline constexpr std::uint32_t kSpanEndExclusive = 0x01053d00u;

// -- extent, as the record states it -----------------------------------------

constexpr int kInstructionCount = 95;
constexpr std::size_t kSpanBytes = 288;
constexpr std::size_t kFrameSubBytes = 24;   // SUB ESP,0x18 at 0x01053be0
constexpr int kSavedRegisterPushes = 4;      // EBX, EBP, ESI, EDI
// 24 + 16, so entry_ESP - 0x28 at every point of the span that has no call or
// push outstanding. Every stack operand below is resolved against this.
constexpr std::ptrdiff_t kPrologueDelta = -(static_cast<std::ptrdiff_t>(kFrameSubBytes) +
                                            4 * static_cast<std::ptrdiff_t>(kSavedRegisterPushes));

constexpr int kConditionalBranchCount = 6;   // JZ x3, JNZ, JL, JLE
constexpr int kUnconditionalDirectJumpCount = 1;
constexpr int kDirectCalleeCount = 6;        // distinct direct CALL targets
constexpr int kDirectCallSiteCount = 10;     // 0x00b3d350 is called five times
constexpr int kComputedTransferCount = 2;    // CALL EAX at 0x01053c19, CALL EDX at 0x01053cac
constexpr int kReceiverDereferenceCount = 1; // MOV EAX,[EDI], offset 0x0 only
constexpr int kStackSlotReadsInSpan = 2;     // entry_ESP+0x4 and entry_ESP+0x8

// The six distinct direct callees, each read back out of the transcript's own
// rel32 displacement. The transcript is the image's bytes; this set is what the
// reconstructed span names.
inline constexpr std::uint32_t kDirectCallees[kDirectCalleeCount] = {
    0x00ffbe50u,  // 0x01053be9  CALL 0x00ffbe50
    0x00a1ad60u,  // 0x01053bf0  CALL 0x00a1ad60
    0x00b3d350u,  // 0x01053c3b, 0x01053c4e, 0x01053c6c, 0x01053c7a, 0x01053cce
    0x00b815a0u,  // 0x01053c55  CALL 0x00b815a0
    0x00b81720u,  // 0x01053c81  CALL 0x00b81720
    0x00b81780u,  // 0x01053cd5  CALL 0x00b81780
};
constexpr int kInputManagerCallSiteCount = 5;

// -- the receiver, the model word and the out-parameter ------------------------

// The word ECX carries on entry. The record names it a receiver at INFERRED
// confidence (receiver.register ECX, present true); it is declared and left
// undefined here, because the body loads exactly one word through it and that
// word is not a pointee this package can describe.
struct Receiver;

// The word 0x00a1ad60 returns. Tested against 0 at 0x01053c0a and read at
// +0x34; unproven beyond that, so no type is given it.
struct ModelWord;

// The 12-byte destination the span writes through. The body performs six
// separate 4-byte stores into it (three MOVSS to zero it, then a MOVSS triple
// or a MOV/MOV/MOV triple). It is spelled as three floats because the machine
// stores single-precision dwords at +0, +4 and +8 -- not because a name, a
// member or an owner is claimed for it.
using Triple = float;
constexpr std::size_t kTripleWords = 3;
constexpr std::size_t kTripleBytes = 12;

// The two floats the FLD/FSTP pairs put on the stack, in the order the listing
// stores them: ESP+0x4 first (0x01477fbc), then ESP+0 (0x013f1cac).
inline constexpr float kFarStackFloat = 200.0f;   // 0x01477fbc, bytes 00 00 48 43
inline constexpr float kNearStackFloat = 50.0f;   // 0x013f1cac, bytes 00 00 48 42
inline constexpr std::uint32_t kFarStackFloatAddress = 0x01477fbcu;
inline constexpr std::uint32_t kNearStackFloatAddress = 0x013f1cacu;

// -- displacements, all of them read off the listing --------------------------
//
// Every one is the displacement the instruction itself carries. They are named
// constants rather than literals in the entry so that the entry's source span
// declares no hexadecimal literal the machine listing could refute.

// 0x01053c0e  MOV EDX,[EAX+0x34]   -- the word that holds the next call's target
constexpr std::size_t kModelTableWordOffset = 0x34u;
// 0x01053c11  ADD EAX,0x34        -- and the same value added to the model word
constexpr std::size_t kModelSelfOffset = 0x34u;
// 0x01053c16  MOV EAX,[EDX+0x2c]  -- the computed call's target word
constexpr std::size_t kTableCallWordOffset = 0x2cu;
// 0x01053ca0  MOV EAX,[EDI]       -- the ONE displacement the receiver record
//                                    enumerates (receiver.offsets == [0])
constexpr std::size_t kReceiverTableOffset = 0x00u;
// 0x01053ca2  MOV EDX,[EAX+0x24]  -- the probe's target word
constexpr std::size_t kReceiverCallWordOffset = 0x24u;
// 0x01053ca5  PUSH 0x1            -- the probe's first stack word
constexpr std::uint32_t kProbeFirstArgument = 0x1u;
// 0x01053cda and 0x01053cf3  CMP EBX,0x3e8
constexpr std::uint32_t kIterationLimit = 0x3e8u;

// -- the frame, resolved against the prologue ---------------------------------
//
// ESP is entry_ESP - 0x28 wherever nothing is outstanding. The two operands the
// span reads out of its own incoming argument area are therefore:
//
//   0x01053bf5  MOV ESI,[ESP+0x2c]  ->  entry_ESP+0x4
//   0x01053c96  MOV EBP,[ESP+0x30]  ->  entry_ESP+0x8
//
// Both are 4-byte reads of the caller's stack. The first is the out-parameter
// pointer; the second is the probe's second stack word.
//
// NOTE A DISAGREEMENT WITH THE RECORD, REPORTED AND NOT RESOLVED. The record's
// stack_arguments enumerate ONE slot, entry_ESP+0x4, with total_bytes 4, and it
// also carries parse.esp_unresolved true. The listing shows TWO reads of the
// incoming argument area, the second at entry_ESP+0x8, and the record's own
// observation obs-0014 (STACK_SLOT_READ, base ESP, disp 44, key 4) is the first
// of them. So the record's slot list is incomplete for this body and the
// listing is the stronger witness. Both words are modelled, and the second is
// named for the address it resolves to rather than for a meaning.
//
// The record also reports slots[0].read == false while obs-0014 is a read of
// that same slot. The listing is what this package follows: the word IS read,
// and it is the base of every store the span makes.
constexpr std::ptrdiff_t kOutParameterEntryOffset = 0x04;
constexpr std::ptrdiff_t kProbeSecondWordEntryOffset = 0x08;
// The same two numbers under the names the machine record would use, so the
// entry can assert that its reading of the listing is the reading the record's
// own slot-derivation is keyed on (entry_ESP+0x4 is the slot it enumerates).
constexpr std::ptrdiff_t kStackArgumentSlotOffset = 0x04;
constexpr std::ptrdiff_t kSecondStackWordOffset = 0x08;

// The one address the span hands to 0x00b3d350 and to 0x00b81720, computed from
// the prologue and from the pushes that precede it:
//
//   0x01053c49  LEA EDX,[ESP+0x20]  with one word pushed  ->  entry_ESP-0x0c
//   0x01053c75  LEA ECX,[ESP+0x1c]  with nothing pushed  ->  entry_ESP-0x0c
//
// Five bytes below the frame, so the recovered span never writes it and its
// content is whatever the caller left. Its ADDRESS is determined; its CONTENT
// is not, and nothing here reads it.
constexpr std::ptrdiff_t kUntouchedCellEntryOffset = -0x0c;

// The address the loop hands to 0x00b3d350 at 0x01053cbf,
// LEA EAX,[ESP+0x24], is NOT determined, and this package does not pick a
// reading. ESP there depends on whether the computed call at 0x01053cac pops its
// three stack words itself:
//
//   if that callee pops 3 :  ESP = entry_ESP-0x38  and  [ESP+0x24] = entry_ESP-0x18
//                            -- the first word of the local triple;
//   if it does not       :  ESP = entry_ESP-0x44  and  [ESP+0x24] = entry_ESP-0x24
//                            -- a frame word this span never writes.
//
// The record's cleanup is UNKNOWN with side null, so it settles nothing. The
// model passes a scratch buffer and asserts nothing about the address's identity.
constexpr bool kLoopScratchAddressDetermined = false;

// The local triple the span builds at 0x01053c1f..0x01053c35. It is the first
// stack word of the pair pushed at 0x01053c44/0x01053c48 -- LEA ECX,[ESP+0x10]
// with nothing outstanding, which is entry_ESP-0x18 -- and that address is NOT
// in doubt, so the model passes this buffer there.
constexpr std::ptrdiff_t kLocalTripleEntryOffset = -0x18;

// -- the byte transcript, read back from the image ---------------------------
//
// GhidraMCP /read_memory at 0x01053be0 for 288 bytes. These 288 bytes are the
// 95 instructions of the evidence listing at the listing's own addresses, and
// the next byte, 0x01053d00, is outside the recovered span. The model test does
// not compare this array with itself: it re-derives every CALL target and every
// displacement from these bytes with its own arithmetic and checks the result
// against literals written separately in that file.
inline constexpr std::uint8_t kTargetBytes[kSpanBytes] = {
    0x83, 0xec, 0x18, 0x53, 0x55, 0x56, 0x57, 0x8b, 0xf9, 0xe8, 0x62, 0x82,  // +0x000
    0xfa, 0xff, 0x8b, 0xc8, 0xe8, 0x6b, 0x71, 0x9c, 0xff, 0x8b, 0x74, 0x24,  // +0x00c
    0x2c, 0x0f, 0x57, 0xc0, 0xf3, 0x0f, 0x11, 0x06, 0xf3, 0x0f, 0x11, 0x46,  // +0x018
    0x04, 0xf3, 0x0f, 0x11, 0x46, 0x08, 0x85, 0xc0, 0x74, 0x5e, 0x8b, 0x50,  // +0x024
    0x34, 0x83, 0xc0, 0x34, 0x8b, 0xc8, 0x8b, 0x42, 0x2c, 0xff, 0xd0, 0xf3,  // +0x030
    0x0f, 0x10, 0x00, 0xf3, 0x0f, 0x11, 0x44, 0x24, 0x10, 0xf3, 0x0f, 0x10,  // +0x03c
    0x40, 0x04, 0xf3, 0x0f, 0x11, 0x44, 0x24, 0x14, 0xf3, 0x0f, 0x10, 0x40,  // +0x048
    0x08, 0xf3, 0x0f, 0x11, 0x44, 0x24, 0x18, 0xe8, 0x10, 0x97, 0xae, 0xff,  // +0x054
    0x85, 0xc0, 0x74, 0x52, 0x8d, 0x4c, 0x24, 0x10, 0x51, 0x8d, 0x54, 0x24,  // +0x060
    0x20, 0x52, 0xe8, 0xfd, 0x96, 0xae, 0xff, 0x8b, 0xc8, 0xe8, 0x46, 0xd9,  // +0x06c
    0xb2, 0xff, 0x8b, 0x08, 0x89, 0x0e, 0x8b, 0x50, 0x04, 0x89, 0x56, 0x04,  // +0x078
    0x8b, 0x40, 0x08, 0x89, 0x46, 0x08, 0xeb, 0x2a, 0xe8, 0xdf, 0x96, 0xae,  // +0x084
    0xff, 0x85, 0xc0, 0x74, 0x21, 0x8d, 0x4c, 0x24, 0x1c, 0x51, 0xe8, 0xd1,  // +0x090
    0x96, 0xae, 0xff, 0x8b, 0xc8, 0xe8, 0x9a, 0xda, 0xb2, 0xff, 0x8b, 0x10,  // +0x09c
    0x89, 0x16, 0x8b, 0x48, 0x04, 0x89, 0x4e, 0x04, 0x8b, 0x50, 0x08, 0x89,  // +0x0a8
    0x56, 0x08, 0x8b, 0x6c, 0x24, 0x30, 0x33, 0xdb, 0x8d, 0x64, 0x24, 0x00,  // +0x0b4
    0x8b, 0x07, 0x8b, 0x50, 0x24, 0x6a, 0x01, 0x56, 0x55, 0x8b, 0xcf, 0x43,  // +0x0c0
    0xff, 0xd2, 0x84, 0xc0, 0x75, 0x41, 0xd9, 0x05, 0xbc, 0x7f, 0x47, 0x01,  // +0x0cc
    0x83, 0xec, 0x08, 0xd9, 0x5c, 0x24, 0x04, 0x8d, 0x44, 0x24, 0x24, 0xd9,  // +0x0d8
    0x05, 0xac, 0x1c, 0x3f, 0x01, 0xd9, 0x1c, 0x24, 0x56, 0x50, 0xe8, 0x7d,  // +0x0e4
    0x96, 0xae, 0xff, 0x8b, 0xc8, 0xe8, 0xa6, 0xda, 0xb2, 0xff, 0x81, 0xfb,  // +0x0f0
    0xe8, 0x03, 0x00, 0x00, 0x8b, 0x08, 0x89, 0x0e, 0x8b, 0x50, 0x04, 0x89,  // +0x0fc
    0x56, 0x04, 0x8b, 0x40, 0x08, 0x89, 0x46, 0x08, 0x7c, 0xae, 0x43, 0x81,  // +0x108
    0xfb, 0xe8, 0x03, 0x00, 0x00, 0x7e, 0x40, 0x33, 0xdb, 0x8d, 0x49, 0x00,  // +0x114
};

// The ten direct CALL sites in the span, for the model test to re-derive from
// the transcript rather than to trust. Each is a 5-byte rel32 call: one 0xe8
// opcode byte, then the next-instruction address plus the signed displacement.
inline constexpr std::uint32_t kAllDirectCallSites[kDirectCallSiteCount] = {
    0x01053be9u, 0x01053bf0u, 0x01053c3bu, 0x01053c4eu, 0x01053c55u,
    0x01053c6cu, 0x01053c7au, 0x01053c81u, 0x01053cceu, 0x01053cd5u,
};
constexpr int kAllDirectCallSiteCount = 10;

// The two computed transfers, by address and by opcode.
constexpr std::uint32_t kFirstComputedCallAddress = 0x01053c19u;   // ff d0  CALL EAX
constexpr std::uint32_t kProbeComputedCallAddress = 0x01053cacu;   // ff d2  CALL EDX

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data so that reverting one to a
// convenient value fails the model test instead of passing quietly.

// The record's own verdict. It is ABI_UNKNOWN, which is why this package
// declares no calling convention.
constexpr bool kDerivedVerdictIsAbiUnknown = true;
constexpr int kCandidateConventionCount = 4;
constexpr bool kConventionDetermined = false;

// receiver {present true, register ECX, confidence INFERRED, bounds_only true,
//           shape R-ALIAS, distinct_offsets 1, offsets [0], max_offset 0,
//           written_through 0}
constexpr bool kReceiverPresent = true;
constexpr int kReceiverRegisterId = 1;         // ECX in the engine's register order
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverIsAliased = true;      // shape R-ALIAS
constexpr int kReceiverDistinctOffsets = 1;
constexpr std::size_t kReceiverOnlyOffset = 0x00u;
constexpr int kReceiverMaxOffset = 0;
constexpr int kReceiverWrittenThrough = 0;

// cleanup {bytes null, side null, confidence UNKNOWN, corroboration not_available}
constexpr bool kCleanupDetermined = false;
constexpr int kCleanupBytes = 0;               // null in the record: not zero bytes
constexpr bool kCleanupSideKnown = false;

// sret {present null, ambiguity sret_vs_out_param, candidates
//       [hidden_sret, out_parameter], hypothesis_confidence INFERRED,
//       confidence UNKNOWN, slot 4}
constexpr bool kStructReturnDecided = false;
constexpr std::ptrdiff_t kStructReturnSlotOffset = 0x04;

// return {register ST0, register_class float_or_x87, confidence APPROXIMATION,
//         type null, void_possible false, aggregate_evidence.bulk_write false}
// The x87 stack is balanced by the byte transcript (each FLD has its FSTP), so
// this record's stated basis does not hold inside the recovered span. Reported,
// not resolved.
constexpr bool kReturnRegisterClaimedSt0 = true;
constexpr bool kReturnWidthDetermined = false;
constexpr bool kReturnTypeDetermined = false;

// The transfer-out accounting re-derived from the listing, as above.
constexpr int kRetInstructionsInSpan = 0;
constexpr int kUnconditionalExitsOutOfSpan = 0;
constexpr int kConditionalExitsOutOfSpan = 1;   // JLE 0x01053d3b at 0x01053cf9
constexpr std::uint32_t kConditionalExitTarget = 0x01053d3bu;
constexpr std::uint32_t kFallThroughExitAddress = 0x01053d00u;
constexpr int kUnconditionalDirectJumpsInsideSpan = 1;  // 0x01053c6a -> 0x01053c96
constexpr std::uint32_t kOnlyDirectJumpTarget = 0x01053c96u;
// The same fact as a predicate, so the entry can assert the geometry without
// writing an address difference of its own: 0x01053c96 lies between the span's
// first and last byte, and the validator's own rule filters exactly this case
// ("a jump that lands back in the body is control flow and not a transfer out").
constexpr bool kOnlyDirectJumpTargetIsInside = true;
constexpr std::uint32_t kLastInstructionAddress = 0x01053cfdu;
constexpr std::uint32_t kLastInstructionOpcode = 0x8d4900u;   // LEA ECX,[ECX]

// tail_call {present false, form null, target null, after_frame_setup false}
// plus the repository's own statement that a pre-existing tail_call.target is
// provably wrong for this address (tools/reconstruction_tooling/evidence.py).
constexpr bool kTailHopPresent = false;
constexpr bool kTailTargetAsserted = false;
constexpr bool kTailTargetFieldProvablyWrong = true;

// -- the six named callees, and the two computed transfers --------------------
//
// These are OBSERVERS. The reconstructed entry names them and does not define
// them; the model test defines each one and drives them. The names carry the
// addresses and nothing else: no semantic name, no class and no meaning is
// claimed for any of the six, because the evidence pack carries no
// decompilation for this target (categories.decompilation is missing) and the
// SDK named none of them.
//
// The parameters spell only what the listing shows about each call site: which
// register and which stack words are live at the transfer. They do NOT assert a
// calling convention. The record names none, and it states cleanup UNKNOWN for
// the target as a whole.

// 0x01053be9  CALL 0x00ffbe50       nothing pushed, result in EAX
void* callee_00ffbe50();
// 0x01053bf0  CALL 0x00a1ad60       ECX = the previous EAX, nothing pushed
void* callee_00a1ad60(void* root);
// 0x01053c3b, 0x01053c4e, 0x01053c6c, 0x01053c7a, 0x01053cce
//                                     nothing in ECX, result in EAX
void* callee_00b3d350();
// 0x01053c55  CALL 0x00b815a0       ECX = the second 0x00b3d350 result, two words pushed
const Triple* callee_00b815a0(void* self, const Triple* local, void* cell);
// 0x01053c81  CALL 0x00b81720       ECX = the second 0x00b3d350 result, one word pushed
const Triple* callee_00b81720(void* self, void* cell);
// 0x01053cd5  CALL 0x00b81780       ECX = the 0x00b3d350 result, nothing pushed
const Triple* callee_00b81780(void* self, void* scratch);

// The two computed transfers, which the model routes through observers so that
// the call is modelled as a call through a word read out of memory rather than
// as a direct call to a named address. Each observer performs the memcpy from
// the word into a function pointer itself; nothing here asserts what the word
// points at, and no slot boundary is declared.
//
// 0x01053c19  CALL EAX    ECX = model+0x34, no stack words, EAX -> three floats
const Triple* dispatch_first(std::uint32_t call_word, void* self);
// 0x01053cac  CALL EDX    ECX = the receiver, three stack words, AL tested
std::uint32_t dispatch_probe(std::uint32_t call_word, void* self, std::uint32_t arg0,
                             Triple* arg1, std::uint32_t arg2);

// -- raw word access, the only way the body reaches memory --------------------

// The body's own reads are 4-byte loads at fixed displacements. This is that
// read, written once so the entry states displacements as names and performs no
// pointer arithmetic of its own.
inline std::uint32_t load_word32(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset, sizeof value);
  return value;
}

// ADD EAX,0x34 at 0x01053c11: a pointer advanced by a displacement the listing
// carries.
inline void* byte_advance(void* base, std::size_t offset) {
  return static_cast<unsigned char*>(base) + offset;
}

// The six 4-byte stores the span makes through the out-parameter, as one
// transfer. The listing stores them one instruction at a time (MOVSS at
// 0x01053c1f, 0x01053c2a, 0x01053c35 in the model-present arm; MOV/MOV/MOV at
// 0x01053c5c..0x01053c67 and 0x01053c88..0x01053c93 in the two other arms; MOV/
// MOV/MOV again at 0x01053ce2..0x01053ced), and every one of them is the same
// shape, so this helper is that shape and no more.
inline void store_triple(Triple* out, const Triple* from) {
  out[0] = from[0];
  out[1] = from[1];
  out[2] = from[2];
}

// -- the reconstruction --------------------------------------------------------

// FUN_01053be0 @ 0x01053be0, reconstructed for the 95 recovered instructions
// 0x01053be0..0x01053cff and for nothing beyond them.
//
// A plain function: the record names no calling convention, so none is declared
// here and the ECX receiver arrives as the first parameter. The entry returns
// nothing, because the recovered span contains no return instruction and leaves
// no value in any return register on either of its two ways out.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" void reconstruct_01053be0(Receiver* receiver, Triple* out_triple,
                                     std::uint32_t caller_word);

}  // namespace openspore::reconstruction::pkg_w2_01053be0
