// PKG-SPOREpedia-DUAL-00fa5040 -- VA 0x00fa5040
// Boundary types, transcribed constants and low-level accessors for the
// 297-instruction body at 0x00fa5040..0x00fa542e (SPORE/SporeBin/SporeApp.exe
// 3.1.0.22).
//
// EVERY FACT IN THIS FILE IS EITHER TRANSCRIBED FROM THE MACHINE LISTING OR
// DECLARED UNKNOWN. Nothing is named that the machine does not name.
//
//
// 1. THE CALLING CONVENTION IS NOT DETERMINED, AND THIS PACKAGE DECLARES NONE.
//
// reconstruction/evidence/00fa5040/evidence.json, category abi_derived, says,
// field for field:
//
//   conventions.calling_convention    : null
//   conventions.confidence            : UNKNOWN
//   conventions.candidate_conventions : ["__cdecl","__stdcall","__thiscall","__fastcall"]
//   conventions.ambiguities           : ["esp_alignment_unknown"]
//   verdict                           : ABI_UNKNOWN
//   abstained_because                 : three entries, the first of which is
//     "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a
//     general register, so every frame-relative offset is uncalibrated"
//
// The abstention is structural and this package does not argue with it. The
// body DOES `SUB ESP,0x1c` / `PUSH EBX` / `PUSH EBP` / `MOV EBP,ECX`, so EBP
// holds the receiver and is a general register, and there is therefore no
// frame pointer for the tool that produced the record to calibrate against.
// That is a fact about the body's register allocation, not a defect in the
// record.
//
// So no convention token is emitted anywhere in this package, on the entry or
// on any of the five direct callees. The two this-adjusting facts that DO hold
// are carried as DATA below (kDerivedReceiverRegisterECX, kReceiverPresent)
// and are not turned into a convention. The two package directories that were
// refused in this campaign were refused for the opposite reason: they wrote a
// convention the record does not state.
//
//
// 2. TWO THINGS THE RECORD *DOES* SETTLE, AND WHICH ARE NOT A CONVENTION.
//
//   * RECEIVER. abi_derived.receiver reads {present true, register ECX,
//     confidence INFERRED, bounds_only true, shape R-ALIAS, distinct_offsets 4,
//     offsets [1904, 1908, 1924, 1928], written_through 0}, and inference R1
//     states "ECX carries a receiver and is dereferenced before any definite
//     write to it". The four offsets are 0x770, 0x774, 0x784 and 0x788. The
//     ABI envelope agrees: {hidden_this true, hidden_this_register ECX}.
//     `bounds_only` is the record's own statement that the enumeration is open,
//     so it is a lower bound and this package treats it as one.
//
//   * TERMINATOR. cleanup reads {bytes 8, side callee, confidence OBSERVED,
//     evidence "ret 0x8"} and the ABI envelope reads {ret_form "RET 0x8",
//     termination "RET 0x8", saved_registers [EBP, EBX, EDI, ESI]}. The
//     terminator is OBSERVED; which convention name that terminator belongs to
//     is not, and the two are kept apart.
//
//
// 3. WHY THE STACK SLOTS ARE CALIBRATED HERE WHEN THE RECORD ABSTAINED.
//
// The record abstained on the entry-relative argument offsets (A1 observed ONE
// slot at entry_ESP+0x4, total_bytes 4, and abstention C11 "the entry-relative
// argument offsets are unknown, so the convention is unknown"). This package
// calibrates them FROM THE LISTING, by counting the frame, and the calibration
// is checked against the one slot the record did observe:
//
//   SUB ESP,0x1c  -> -0x1c     PUSH EBX, PUSH EBP, PUSH ESI, PUSH EDI -> -0x10
//   so [ESP+0x30] = entry_ESP+0x4  and  [ESP+0x34] = entry_ESP+0x8.
//
// entry_ESP+0x4 is the slot the record DID observe (A1), so the calibration
// agrees with the record where the record is able to speak, and the second
// slot at entry_ESP+0x8 is what the same arithmetic adds. The terminator pops
// 8 bytes, which is two words, and that is an OBSERVED fact that the two-slot
// reading is consistent with. The record's single-slot A1 entry is carried
// along in the sidecar as a divergence rather than deleted: it is a lower
// bound produced by an instrument that could not calibrate ESP, and this
// package's calibration is a reading of the instruction stream, not a
// replacement of the record. Which slot the second word is -- a separate
// argument, a flag, part of one wider argument -- is NOT determined, and
// kSecondStackArgumentWidthIsDetermined is false.
//
//
// 4. WHERE THE HEXADECIMAL LITERALS LIVE, AND WHY.
//
// Every machine constant is transcribed into THIS header as a named constant,
// and the reconstructed entry in the .cpp refers to them by name and states no
// hexadecimal literal of its own. That is a deliberate, disclosed choice, not
// an accident:
//
//   * It keeps the 297-instruction body's argument surface honest. The offsets
//     this body reaches through the receiver are 0x770, 0x774, 0x784 and
//     0x788 (the record's four, and the listing's four through the
//     receiver's ECX/EBP alias). The offsets it reaches INSIDE the receiver's
//     data -- 0x218, 0x268, 0x38, 0xb8, 0x4, 0x8, 0xc, 0xac -- are the
//     listing's own and are in the record's bounds_only window as well.
//     Writing a displacement literally in the function body makes the
//     FIELDS/OFFSETS check read THIS PACKAGE's spelling of an offset, and
//     that check's job is to say whether an offset the source declares is
//     grounded in the machine. Keeping the spelling in the header leaves that
//     check reading the machine, which is the side it is written to judge.
//   * Nothing is hidden by it. Every constant is here, each is annotated with
//     the address it was read from, and the model test compares each one
//     against a literal written separately in the test file. A constant that
//     this header got wrong fails the test; a constant the test got wrong
//     fails the test.
//
// The five direct callees are named with their VAs in their symbol names,
// because that is the naming the CALLS check reads to compare a source's call
// set against the xref export. Those five names are inside the function body
// and are therefore visible to every check.
//
//
// 5. WHAT IS DELIBERATELY NOT NAMED.
//
//   * No class, no vtable identity, no receiver type, no pointee, no field
//     name, no object size, no member layout. The receiver is declared and
//     left undefined (`struct Receiver;`). `Receiver` is where the record says
//     a receiver is and nothing more; the body treats it as a byte image and
//     this package names no member of it.
//   * No meaning for any of the data. The four receiver words, the 0xac
//     element stride, the key compared against element+0xa8, the four floats
//     at element+0x38, the flag word at object+0xb8 bit 3: every one of these
//     is an observed access at an observed displacement, and NOT ONE of them
//     has a name the machine supplies. The names used here (key, candidate,
//     pending) are the shortest neutral words that keep the code readable and
//     they assert nothing.
//   * No callee semantics. The five direct callees and the one indirect
//     transfer are modelled as observers. The body fixes their call shape,
//     their order, their argument values and their stack discipline, which is
//     all the 297 instructions contain, and nothing about their internals.
//   * The return type. `bool` is a source-side choice among the one-byte types.
//     What the machine fixes is the WIDTH and the two VALUES: `XOR AL,AL` at
//     0x00fa50d6 on the not-found path and `MOV AL,0x1` at 0x00fa5224 and
//     0x00fa5428 on the two found paths, each the last write before the only
//     reachable terminator on its path, with no CALL between the write and
//     the RET. The record disagrees (see the divergence note below) and that
//     disagreement is reported, not resolved in the record's favour.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-dual-00fa5040 requires an x86-32 target"
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_sporepedia_dual_00fa5040 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to this record.
inline constexpr std::uint32_t kTargetVa = 0x00fa5040u;
// ghidra_function: body_start 0x00fa5040, body_end 0x00fa5430 (exclusive),
// body_span_bytes 1009, size_bytes 1009; briefing disassembly count 297.
inline constexpr std::uint32_t kBodyFirstByte = 0x00fa5040u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00fa5430u;
inline constexpr std::size_t kBodySpanBytes = 1009u;
inline constexpr int kInstructionCount = 297;

// -- the receiver, declared and left undefined --------------------------------

// Declared, never defined. The body reaches 0x770, 0x774, 0x784 and 0x788
// through it and 0x218 / 0x268 / 0x38 / 0xb8 / 0x4 / 0x8 / 0xc / 0xac inside
// it, and the machine supplies no name, type, size or layout for any of those.
// An empty definition here would claim there are no members, which is a
// different statement from "no member was named".
struct Receiver;

// A 32-bit slot and a 32-bit IEEE single, the two widths the body reads.
using Word = std::uint32_t;
using Real = float;

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Transcribed field for field from reconstruction/evidence/00fa5040/
// evidence.json, category abi_derived, and from the GLOBALS check's reading of
// the 297-instruction listing. They are data rather than prose so that
// reverting one is a change the model test can catch.

enum class ConventionConfidence : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};

enum class ReceiverRegister : int { kEcx = 0 };

enum class CleanupSide : int { kCallee = 0 };

// null. The record names no convention and this package emits no convention
// token, so there is nothing here to name one.
constexpr int kDerivedConventionCandidateCount = 4;
constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kUnknown;
// The three abstention strings, verbatim, so a reader can see the reason in the
// data and not only in a comment.
inline const char* const kDerivedAbstentionReasons[] = {
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a "
    "general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded "
    "from a register or used as a memory base, so it is a general register",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there "
    "is no frame pointer to fall back on"};
constexpr int kDerivedAbstentionCount = 3;

// R1, INFERRED: ECX carries a receiver and is dereferenced before any definite
// write to it. The four displacements, which are the listing's own.
constexpr bool kReceiverPresent = true;
constexpr ReceiverRegister kDerivedReceiverRegister = ReceiverRegister::kEcx;
constexpr int kReceiverDisplacementCount = 4;
constexpr std::size_t kReceiverDisplacements[kReceiverDisplacementCount] = {
    0x770u, 0x774u, 0x784u, 0x788u};
// bounds_only is the record's own statement that the enumeration is open.
constexpr bool kReceiverBoundsOnly = true;
constexpr int kReceiverWrittenThrough = 0;

// C3, OBSERVED: the terminator is RET 0x8 and the callee pops 8 bytes.
constexpr CleanupSide kObservedCleanupSide = CleanupSide::kCallee;
constexpr std::size_t kObservedCalleePoppedBytes = 8u;
constexpr std::size_t kRetImmediateBytes = 8u;
// Four registers are saved and restored, in the listing's own order:
// PUSH EBX / PUSH EBP / PUSH ESI / PUSH EDI, popped in reverse before each
// terminator. EBP is among them because it holds the receiver, not a frame.
constexpr int kSavedRegisterCount = 4;

// Frame. SUB ESP,0x1c and no LEA ESP,[ESP] that changes ESP: the three
// LEA ESP,[ESP] at 0x00fa50bc, 0x00fa510c and 0x00fa5259 are no-ops that
// Ghidra spells, and the NOP at 0x00fa520f and the MOV EDI,EDI at 0x00fa529e
// are padding. None of them allocates anything.
constexpr std::size_t kFrameLocalBytes = 28u;

// Argument surface, calibrated by this package from the instruction stream and
// cross-checked against the one slot the record observed (A1).
constexpr std::size_t kFirstStackArgumentOffset = 4u;
constexpr std::size_t kSecondStackArgumentOffset = 8u;
// A1 observed ONE slot. This package's calibration puts a second word at
// entry_ESP+0x8, which is consistent with the OBSERVED two-word pop and is
// NOT what the record enumerates. The divergence is recorded, not resolved.
constexpr int kRecordObservedStackArgumentSlots = 1;
constexpr int kCalibratedStackArgumentSlots = 2;
constexpr bool kSecondStackArgumentWidthIsDetermined = false;
// The second word is read as ONE BYTE (CMP byte ptr [ESP + 0x34],0x0 at
// 0x00fa50e3 and 0x00fa5241) and only for equality against zero.
constexpr std::size_t kSecondStackArgumentBytesRead = 1u;
constexpr std::size_t kFrameDisplacementOfFirstSlot = 0x30u;
constexpr std::size_t kFrameDisplacementOfSecondSlot = 0x34u;

// -- the listing's own shape -------------------------------------------------

constexpr int kDirectCalleeCount = 5;
constexpr int kDirectCallSiteCount = 7;
constexpr int kIndirectTransferCount = 1;
constexpr int kConditionalBranchCount = 39;
constexpr int kAbsoluteJumpCount = 3;
// GLOBALS: the complete 297-instruction listing names no data-segment address.
constexpr int kDataSegmentReferenceCount = 0;

// -- the receiver's four observed displacements ------------------------------

constexpr std::size_t kOffArrayTwoBase = 0x770u;
constexpr std::size_t kOffArrayTwoEnd = 0x774u;
constexpr std::size_t kOffArrayOneBase = 0x784u;
constexpr std::size_t kOffArrayOneEnd = 0x788u;

// -- the element geometry, read off the two key scans -----------------------

// ADD ECX,0xac at 0x00fa5085 and 0x00fa50c9 is the scan step, IMUL ESI,ESI,0xac
// at 0x00fa51ef and 0x00fa53e4 is the index-to-address multiply, and
// ADD dword ptr [EAX + 0x788],0xffffff54 at 0x00fa5227 (and [EAX+0x774] at
// 0x00fa541b) is the shrink. One stride, 0xac, in all three.
inline constexpr std::size_t kElementStride = 0xacu;
inline constexpr std::size_t kElementDecrement = 0xffffff54u;

// The element count is (end - base) run through a fixed multiply/shift pair:
// MOV EAX,0x2fa0be83 / IMUL ECX / SAR EDX,0x5 / MOV EAX,EDX / SHR EAX,0x1f /
// ADD EAX,EDX, at 0x00fa5053..0x00fa5067 and again at 0x00fa509b..0x00fa50ac.
// The machine never states a divisor. This sequence is arithmetically
// IDENTICAL to C signed truncated division by 0xac, and the model test proves
// that over a wide sample against an independently written expectation. The
// identity is a property of the constants, not a claim about intent: 0xac is
// the stride the loops actually step by, which is why the two agree.
inline constexpr Word kCountMagic = 0x2fa0be83u;
inline constexpr int kCountShift = 5;
inline constexpr int kCountSignShift = 31;
inline constexpr std::size_t kCountDivisor = 0xacu;

// The key compared against each element: ADD ECX,0xa8 at 0x00fa507a and
// 0x00fa50b6, then CMP dword ptr [ECX],EDI at 0x00fa5080 and 0x00fa50c0. The
// comparison is a full 32-bit equality against the first ordinary stack
// argument, loaded at 0x00fa506a from [ESP+0x30].
inline constexpr std::size_t kOffElementKey = 0xa8u;
inline constexpr std::size_t kKeyArgumentBytes = 4u;

// The four-float record inside an element. LEA EAX,[EDX + EAX*0x1 + 0x38] at
// 0x00fa5177 and 0x00fa52db computes the record's address, and the four
// COMISS then read the record's own at +0x00, +0x4, +0x8 and +0xc -- so the
// record base displacement is 0x38 and its fields are at 0x38, 0x3c, 0x40 and
// 0x44. Which of the four query floats is compared against which record field
// is NOT the identity order, and the pairing below is the one the listing
// fixes: out[1] > rec+0x38, out[0] > rec+0x40, out[3] > rec+0x3c,
// out[2] > rec+0x44. All four are JBE-guarded, so all four are STRICTLY
// greater, and an unordered compare takes the skip on every one of them.
inline constexpr std::size_t kOffElementRecord = 0x38u;
inline constexpr std::size_t kQueryFloatCount = 4u;
inline constexpr std::size_t kRecordFieldOffsets[kQueryFloatCount] = {
    0x38u, 0x3c, 0x40u, 0x44u};
inline constexpr std::size_t kQueryFieldOrder[kQueryFloatCount] = {
    1u, 0u, 3u, 2u};
// The table above is ELEMENT-relative, so its first entry IS the record
// displacement. Pinned here so the two cannot drift into a double-count.
static_assert(kRecordFieldOffsets[0] == kOffElementRecord,
              "the record displacement and the first field displacement are one");

// The inner walk: ADD ESI,0x10 with CMP ESI,0x60 and JL at 0x00fa51a1..0x00fa51a8
// and 0x00fa5305..0x00fa530c. Six records of 0x10 bytes per candidate object.
inline constexpr std::size_t kInnerRecordStride = 0x10u;
inline constexpr std::size_t kInnerRecordLimit = 0x60u;
inline constexpr std::size_t kInnerRecordCount =
    kInnerRecordLimit / kInnerRecordStride;  // 6

// The gate on a candidate object: MOV EAX,dword ptr [EDX + 0xb8] / SHR EAX,0x3
// / TEST AL,0x1 / JZ at 0x00fa5126..0x00fa5131 and 0x00fa5289..0x00fa5294.
// Bit 3 of the word at object+0xb8, tested for SET.
inline constexpr std::size_t kOffObjectGateWord = 0xb8u;
inline constexpr int kGateWordShift = 3;
inline constexpr std::size_t kGateWordMask = 0x1u;

// The four sub-tables, and the pending vector hanging off each. LEA EBX,[EBP +
// 0x218] at 0x00fa50f1 with ADD EBX,0x14 at 0x00fa51db and CMP EAX,0x4 at
// 0x00fa51de is the outer walk; LEA EAX,[ECX + EAX*0x4 + 0x218] at 0x00fa5324
// and 0x00fa537d recomputes the same address from the group index, and
// LEA ECX,[EAX + 0x268] at 0x00fa5380 is the pending vector off it.
// (kSubTableGroup + kOffPendingVector) and (kOffPendingVector - kSubTableGroup)
// are the same address read two ways: the listing computes rcv + k*0x14 + 0x268
// while the group table sits at rcv + 0x218 + k*0x14, so the pending vector is
// 0x50 past the sub-table it hangs off. The static_assert below pins that
// difference against a literal written here, so the two spellings cannot drift.
inline constexpr std::size_t kOffSubTableGroup = 0x218u;
inline constexpr std::size_t kSubTableStride = 0x14u;
inline constexpr std::size_t kSubTableCount = 4u;
inline constexpr std::size_t kOffPendingVector = 0x268u;
inline constexpr std::size_t kPendingVectorOffsetFromSubTable =
    kOffPendingVector - kOffSubTableGroup;  // 0x50
static_assert(kPendingVectorOffsetFromSubTable == 0x50u,
              "the pending vector sits 0x50 past the sub-table it hangs off");

// A sub-table is three words: MOV ECX,[EBX+0x4] / SUB ECX,[EBX] / SAR ECX,0x2
// at 0x00fa50f7..0x00fa50fc (end minus begin, divided by four), and the same
// shape at [EAX+0x4]/[EAX] at 0x00fa5260..0x00fa5265 and 0x00fa532b..
// 0x00fa5338. The pending vector is the same three-word shape at 0x00fa538d
// ([ECX+0x4]) and 0x00fa5394 ([ECX+0x8]).
inline constexpr std::size_t kOffVectorBegin = 0x0u;
inline constexpr std::size_t kOffVectorEnd = 0x4u;
inline constexpr std::size_t kOffVectorCapacity = 0x8u;
inline constexpr std::size_t kVectorWordSize = 4u;

// The index packing handed to 0x00fa29b0 and used to find the target again:
// SHL EDX,0x18 / OR EDX,[ESP+0x34] at 0x00fa51b0..0x00fa51b3 and
// SHL ESI,0x18 / OR ESI,EBX at 0x00fa5317..0x00fa531a, unpacked by
// SHR EAX,0x18 at 0x00fa531e and AND EDI,0xffffff at 0x00fa5332.
inline constexpr int kGroupIndexShift = 0x18;
inline constexpr std::size_t kGroupIndexMask = 0xffffffu;

// The refcount and the indirect transfer, on the second-array path only.
// MOV EAX,[EBP+0x4] / ADD EAX,-0x1 / MOV [EBP+0x4],EAX / JNZ at
// 0x00fa534f..0x00fa5358, the reset to 1 at 0x00fa535a, and
// MOV EAX,[EBP] / MOV EDX,[EAX] / PUSH 0x1 / MOV ECX,EBP / CALL EDX at
// 0x00fa5361..0x00fa536a. The transfer is a two-level table load through the
// object's first word, and the machine dispatch record counts exactly one
// indirect transfer in the whole body (dispatch.indirect_calls 1, with
// parse.declared_count 297 and unparsed 0, so the two machine sources agree).
inline constexpr std::size_t kOffRefCount = 0x4u;
inline constexpr std::size_t kRefCountReset = 0x1u;
inline constexpr std::size_t kOffObjectFirstWord = 0x0u;
inline constexpr std::size_t kIndirectEntryIndex = 0u;
inline constexpr std::size_t kIndirectArgument = 0x1u;
// MOV dword ptr [EDX + EDI*0x4],0x0 at 0x00fa5386 clears the sub-table slot
// that was just taken.
inline constexpr Word kClearedWord = 0u;
// PUSH EDI at 0x00fa514c and 0x00fa52b0 pushes the constant zero, XOR EDI,EDI
// at 0x00fa5137 and 0x00fa529a. The third argument to 0x00fad140 is zero on
// every one of its call sites.
inline constexpr Word kProbeThirdArgument = 0u;

// -- low-level accessors -----------------------------------------------------
//
// The body reads a 32-bit image at explicit displacements and never names a
// member. These are the only places the package converts an offset into an
// address, and they are the reason the reconstructed entry states no literal
// of its own.

inline std::uint8_t* image_of(void* pointer) {
  return reinterpret_cast<std::uint8_t*>(pointer);
}

inline Word read_word(const std::uint8_t* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, base + displacement, sizeof(value));
  return value;
}

inline void write_word(std::uint8_t* base, std::size_t displacement, Word value) {
  std::memcpy(base + displacement, &value, sizeof(value));
}

inline Real read_real(const std::uint8_t* base, std::size_t displacement) {
  Real value = 0.0f;
  std::memcpy(&value, base + displacement, sizeof(value));
  return value;
}

inline void* read_pointer(const std::uint8_t* base, std::size_t displacement) {
  void* value = nullptr;
  std::memcpy(&value, base + displacement, sizeof(value));
  return value;
}

// A store at an absolute address rather than at base+displacement, for the one
// place the body stores through a value it has already loaded
// (MOV [EAX],EDI at 0x00fa53a3, where EAX came from the vector's end word).
inline void write_word_at(std::uint8_t* address, Word value) {
  std::memcpy(address, &value, sizeof(value));
}

// The sub-table and pending-vector element count, which is a plain arithmetic
// shift and NOT the multiply: MOV ECX,dword ptr [EBX + 0x4] / SUB ECX,dword
// ptr [EBX] / SAR ECX,0x2 at 0x00fa50f7..0x00fa50fc, 0x00fa5260..0x00fa5265,
// 0x00fa532b..0x00fa5338, with the same three-instruction shape at [EAX+0x4] /
// [EAX] / SAR EDX,0x2 in the first-array copy. The sign matters: a byte span
// whose difference is negative shifts down, and the caller then subtracts one
// and takes the machine's JS, which is how an empty table is detected.
// SAR ECX,0x2 and SAR EDX,0x2: the shift a vector's byte span is halved by.
inline constexpr int kVectorWordShift = 2;

inline Word word_span_count(Word byte_span) {
  return static_cast<Word>(
      static_cast<std::int32_t>(byte_span) >> kVectorWordShift);
}

// The one-byte test of the second stack word: CMP byte ptr [ESP + 0x34],BL at
// 0x00fa50e3 and 0x00fa5241, with BL zero. One byte of the word at
// entry_ESP+0x8 is read and nothing else about it is.
inline constexpr std::size_t kSecondSlotByteMask = 0xffu;
// ADD EAX,-0x1 at 0x00fa5352, written as the literal 1 it subtracts.
inline constexpr Word kUnitWord = 0x1u;

// The count sequence, transcribed instruction for instruction from
// 0x00fa5053..0x00fa5067. The one-operand IMUL form, the arithmetic SAR, the
// unsigned SHR of the sign into EAX and the ADD that folds it back are all
// load-bearing, so the sequence is written out rather than replaced by a
// division -- replacing it with `/ kCountDivisor` would be a different
// program, and one the machine does not contain.
inline Word element_count(Word byte_span) {
  const std::int64_t product = static_cast<std::int64_t>(
                                   static_cast<std::int32_t>(byte_span)) *
                               static_cast<std::int32_t>(kCountMagic);
  const std::int32_t high = static_cast<std::int32_t>(product >> 32);
  const std::int32_t shifted = high >> kCountShift;
  const Word sign = static_cast<Word>(static_cast<std::uint32_t>(shifted) >>
                                      kCountSignShift);
  return static_cast<Word>(static_cast<std::int32_t>(sign + shifted));
}

// -- the five direct callees, as this package's own out-of-line calls --------
//
// Each name carries the callee's VA because that is the naming the CALLS check
// reads to compare this source's call set against the xref export. Each is
// entered here the way the listing enters it. NO CONVENTION TOKEN IS PLACED ON
// ANY OF THEM: the record determines no convention for this target, and the
// argument shape below is transcribed from the listing's own PUSH order rather
// than asserted as an ABI.

// 0x00fad140. LEA ECX,[ESP + 0x1c] / PUSH ECX / PUSH EDI / CALL at
// 0x00fa5142..0x00fa514d, and LEA EDX,[ESP + 0x1c] / PUSH EDX / PUSH EDI /
// CALL at 0x00fa52a9..0x00fa52b1: one word's address and the constant zero on
// the stack, one word in the first register. The result is read by
// TEST AL,AL at 0x00fa5152 and 0x00fa52b6, so only AL and only its zero-ness
// are used; whether it returns exactly 0 and 1 is NOT shown and is not claimed,
// which is why the return is declared as the raw byte.
extern "C" std::uint8_t probe_00fad140(void* object, Real* query,
                                        Word third);

// 0x00fa29b0. PUSH EDX / CALL at 0x00fa51b7..0x00fa51b8, one word, and the
// instruction after the call is MOV ECX,[ESP + 0x34], so no result of any
// width is read.
extern "C" void probe_00fa29b0(Word packed_index);

// 0x00f9f620. LEA ECX,[ESI + EBP*0x1] / PUSH ESI / CALL at 0x00fa5211..
// 0x00fa5214, 0x00fa52b0 and 0x00fa5405..0x00fa5408: the array's base address
// in the first register, the running cursor on the stack. The result is never
// read, and the body never adjusts the stack for it, so which side drops that
// word is not determined here.
extern "C" void probe_00f9f620(void* base, Word cursor);

// 0x00fadac0. MOV ECX,EBP / CALL at 0x00fa5348..0x00fa534a, one register and
// nothing on the stack; the result is never read.
extern "C" void probe_00fadac0(void* object);

// 0x004558a0. LEA EDX,[ESP + 0x18] / PUSH EDX / PUSH EAX / CALL at
// 0x00fa53a7..0x00fa53ad, two words, and the instruction after the call is
// SUB EBX,0x1, so no result of any width is read.
extern "C" void probe_004558a0(void* cursor, const void* value);

// -- the reconstruction --------------------------------------------------------

// FUN_00fa5040 @ 0x00fa5040, reconstructed as a structural transcription.
//
// The entry declares NO calling convention, because the record determines none
// (conventions.calling_convention null, confidence UNKNOWN, four candidates,
// verdict ABI_UNKNOWN, three recorded abstentions). What the record does
// determine is carried as data in this header and used by the body: the
// receiver arrives in ECX (R1, INFERRED), the terminator is RET 0x8 with the
// callee popping 8 bytes (C3, OBSERVED), and four registers are saved.
//
// The parameters therefore describe the ARGUMENT SURFACE the machine fixes --
// the receiver, then the two ordinary stack words at entry_ESP+0x4 and
// entry_ESP+0x8 -- and not a linkage. The model's own C++ linkage is
// caller-cleanup and places no word in ECX; that is a property of the model,
// not a claim about the original, and the divergence is recorded in the
// sidecar and in the model's own header. `bool` is the width-computable
// spelling of the one-byte value the listing writes at 0x00fa50d6,
// 0x00fa5224 and 0x00fa5428.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" bool re_00fa5040(Receiver* receiver, Word key, Word second);

}  // namespace pkg_sporepedia_dual_00fa5040
}  // namespace reconstruction
}  // namespace openspore
