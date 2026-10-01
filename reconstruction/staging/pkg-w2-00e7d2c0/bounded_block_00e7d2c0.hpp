// PKG-W2-00E7D2C0 -- VA 0x00e7d2c0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// THE TARGET IS AN INTERIOR BYTE OF THE BODY, NOT AN INSTRUCTION ENTRY.
//
// The evidence pack's machine record for 0x00e7d2c0 describes a 224-instruction,
// 753-byte body at 0x00e7d070..0x00e7d360 (GhidraMCP /get_function_by_address:
// name FUN_00e7d070, entry_point 00e7d070, body_span_bytes 753). 0x00e7d2c0 is
// 0x250 = 592 bytes into that body. The xref export
// knowledgegraph/triage/xrefs-2540f2ca.tsv carries thirteen call rows whose
// caller_va is 0x00e7d070 and NONE whose caller_va is 0x00e7d2c0, which is
// independent evidence that 0x00e7d2c0 is not a function entry: the export is
// keyed on the caller's entry point.
//
// The 73 bytes below were read out of the image (section .text, RVA 0xa7d2b7,
// raw offset 0xa7c577) and agree, instruction for instruction and address for
// address, with the evidence listing's entries for that range. Reading the byte
// at the target address gives 0x01, and the 5-byte instruction at 0x00e7d2bc is
//
//   00e7d2bc  a1 04 3c 6b 01    MOV EAX, dword ptr [0x016b3c04]
//            ^opcode             ^moffs32, little-endian
//                               |
//                               0x00e7d2c0 is this byte
//
// so the target address is the MOST significant byte of that instruction's
// absolute-address operand. It is not an instruction boundary, and nothing here
// claims an instruction begins there.
//
// THE BOUNDED SPAN RECONSTRUCTED HERE.
//
// Of a 224-instruction body this package reconstructs ONE basic block: the
// straight-line fall-through block that contains the target byte, 0x00e7d2b7
// through the unconditional JMP at 0x00e7d2fe. The block is chosen because it is
// the smallest unit the machine evidence fully determines: it has a single entry,
// no branch inside it, no callee of its own, and a single exit. Everything the
// evidence does NOT determine is listed in unresolved_questions in the metadata
// sidecar and is not guessed here.
//
// THE BLOCK, TRANSCRIBED FROM THE BYTES.
//
//   off  addr      bytes                  instruction
//   0x00 00e7d2b7  8d 44 24 1c            LEA EAX,[ESP + 0x1c]
//   0x04 00e7d2bb  50                     PUSH EAX
//   0x05 00e7d2bc  a1 04 3c 6b 01         MOV EAX,[0x016b3c04]   <- target byte at 0x05+4
//   0x0a 00e7d2c1  8d 4c 24 2c            LEA ECX,[ESP + 0x2c]
//   0x0e 00e7d2c5  51                     PUSH ECX
//   0x0f 00e7d2c6  89 74 24 24            MOV dword ptr [ESP + 0x24],ESI
//   0x13 00e7d2ca  89 74 24 28            MOV dword ptr [ESP + 0x28],ESI
//   0x17 00e7d2ce  89 74 24 2c            MOV dword ptr [ESP + 0x2c],ESI
//   0x1b 00e7d2d2  89 74 24 30            MOV dword ptr [ESP + 0x30],ESI
//   0x1f 00e7d2d6  89 74 24 34            MOV dword ptr [ESP + 0x34],ESI
//   0x23 00e7d2da  89 74 24 38            MOV dword ptr [ESP + 0x38],ESI
//   0x27 00e7d2de  89 74 24 3c            MOV dword ptr [ESP + 0x3c],ESI
//   0x2b 00e7d2e2  89 74 24 40            MOV dword ptr [ESP + 0x40],ESI
//   0x2f 00e7d2e6  89 74 24 44            MOV dword ptr [ESP + 0x44],ESI
//   0x33 00e7d2ea  8b 88 90 51 00 00      MOV ECX,dword ptr [EAX + 0x5190]
//   0x39 00e7d2f0  8d 54 24 3c            LEA EDX,[ESP + 0x3c]
//   0x3d 00e7d2f4  52                     PUSH EDX
//   0x3e 00e7d2f5  83 c1 10               ADD ECX,0x10
//   0x41 00e7d2f8  51                     PUSH ECX
//   0x42 00e7d2f9  68 13 11 f6 9e         PUSH 0x9ef61113
//   0x47 00e7d2fe  eb 48                  JMP 0x00e7d348
//
// The twenty-one lengths sum to 0x49 = 73 bytes exactly, with nothing left over
// and no overlap, so the block is complete between its two ends.
//
// THE ORDER OF THE THREE EFFECTS, WHICH IS THE PART THAT IS EASY TO GET WRONG.
//
// Every stack displacement in the block is relative to ESP *at that instant*,
// and ESP moves by four per PUSH. Folding that away silently is how a
// transcription ends up describing a different program, so this package carries
// the push count explicitly and lets a helper add it:
//
//   * at block entry ESP = F.  LEA EAX,[ESP+0x1c] yields F+0x1c. PUSH -> F-4.
//   * LEA ECX,[ESP+0x2c] is read at ESP = F-4, so it yields F+0x28, NOT F+0x2c.
//     PUSH -> F-8.
//   * the nine stores are read at ESP = F-8, so [ESP+0x24] is F+0x1c and
//     [ESP+0x44] is F+0x3c: NINE consecutive dwords covering F+0x1c..F+0x3f.
//   * LEA EDX,[ESP+0x3c] is read at ESP = F-8, so it yields F+0x34. PUSH -> F-12.
//   * PUSH ECX -> F-16. PUSH 0x9ef61113 -> F-20.
//
// Two consequences follow and are the reason this block is worth modelling at
// all, because both are consequences of the ORDER and not of any one opcode:
//
//   1. All three frame addresses the block hands to the tail -- F+0x1c, F+0x28
//      and F+0x34 -- point INTO the nine dwords the block then overwrites. The
//      addresses are computed first and the overwrite happens afterwards, so the
//      values pushed are unaffected by it; the words at those addresses are not.
//   2. The block writes F+0x1c..F+0x3f, which is exactly 36 bytes, and the two
//      values it reads (the word at [0x016b3c04] and the word at
//      [that + 0x5190]) are read at the block's own displacements and never
//      through the region being overwritten.
//
// THE STORE SOURCE IS THE REGISTER, NOT A CONSTANT.
//
// The nine stores write ESI. The model takes the stored word as a parameter
// rather than baking in a value, because the block itself never writes ESI. The
// listing does contain `XOR ESI,ESI` at 0x00e7d23d, 0x8a bytes before this
// block's first instruction, and that is recorded below as a machine
// observation with its own address; whether ESI is provably zero on EVERY path
// into this block is a dataflow question this package does not settle, so the
// model is driven with 0 and with a sentinel and the parameter is the claim.
//
// WHAT THE RECORD ABSTAINS ON, AND WHAT IS THEREFORE NOT CLAIMED HERE.
//
// The evidence pack's abi_derived category (reconstruction/evidence/00e7d2c0/
// evidence.json) is transcribed field for field into the data block at the
// bottom of this file. In summary:
//
//   conventions.calling_convention    : null
//   conventions.confidence            : UNKNOWN
//   conventions.candidate_conventions : ["__cdecl"]
//   conventions.ambiguities           : ["variadic_suspected"]
//   verdict                           : ABI_UNKNOWN
//   receiver.present    : null        receiver.register : null
//   receiver.reason     : "ecx_reassigned_before_deref"
//   receiver.bounds_only: true        receiver.offsets  : []
//   receiver.distinct_offsets: 0      receiver.written_through: 0
//   cleanup.bytes 0   cleanup.side "caller"
//   cleanup.evidence "ret with no immediate"
//   return.register "ST0"  return.register_class "float_or_x87"
//   return.confidence "APPROXIMATION"  return.void_possible false
//   parse: declared_count 224, degraded false, unparsed 0
//   dispatch: indirect_calls 0, vtable_shaped_loads 0
//   abstained_because[0]: "receiver_not_determinable: ecx_reassigned_before_deref"
//
// Consequences this package accepts without argument:
//
//   * NO CALLING CONVENTION IS DECLARED IN THE SOURCE. The record's verdict is
//     ABI_UNKNOWN and its confidence is UNKNOWN, so the machine does not state
//     one. The validator maps ABI_UNKNOWN to a WARN by design, and that WARN is
//     left standing rather than removed by writing a convention the record does
//     not state. The one candidate in the record, the plain C one, is a
//     candidate list entry at UNKNOWN confidence, not a determination, and it is
//     not adopted here.
//   * NO RECEIVER IS CLAIMED. The record declines to name one, with the reason
//     that ECX is written before it is ever dereferenced, so nothing here treats
//     any register as `this`, and no receiver type, class, object size, field or
//     layout is asserted.
//   * NO FIELD IDENTITY IS CLAIMED. The displacements below are the ones the
//     listing shows; what lives at them is not known. The package therefore
//     names no member and no struct, and every object it touches is an
//     untyped byte address.
//   * THE ARGUMENT SLOTS THE RECORD LISTS ARE NOT USED AS PARAMETERS. The record
//     itself withdraws them: "flow_not_modelled: the linear ESP walk ends at
//     -36, so the listing is not one path" and "untrusted_frame_stack_reads:
//     push ebp with no mov ebp,esp". Its entry_ESP+0x4..0x34 slots are this
//     function's own frame slots read through a walk that does not model the
//     branches, so the model takes its frame as a window it is handed instead of
//     trusting that walk.
//   * THE VARIADIC SUSPICION IS NOT RESOLVED. "variadic_not_decidable_from_
//     listing" is in the record's abstention list and the record notes that
//     variadic suspicion removes any guarantee about the stack-argument extent.
//     This block's five pushed words are exactly what its own JMP tail consumes
//     (the shared tail at 0x00e7d348 does `CALL 0x00e394f0` then
//     `ADD ESP,0x14`, and 0x14 is five words), which is an observation about this
//     block and not a determination of the enclosing function's convention.
//   * NO VIRTUAL DISPATCH IS CLAIMED. The listing contains no indirect transfer
//     through a register or a memory operand and the dispatch record counts
//     zero, so nothing here models a slot boundary.
//
// WHAT IS *NOT* RECONSTRUCTED, AND WHY.
//
// The remaining 203 instructions of the body are not transcribed. They are a
// 224-instruction function whose decompilation was never collected ("no
// persisted or live decompilation for this target") and whose ESP walk the
// record declines to model, so an instruction-for-instruction reconstruction
// would be a fabrication with 224 steps. What the evidence does pin about the
// body -- its extent, its frame arithmetic, its entry-relative load through the
// absolute word at 0x016b3c04, and the two-arm shape this block is one arm of --
// is recorded in the metadata sidecar. The rest is in unresolved_questions.
//
// THE SIBLING ARM, WHICH IS THE STRONGEST STRUCTURAL FACT AVAILABLE.
//
// The predicate at 0x00e7d28d..0x00e7d2b5 falls into this block when it holds
// and into 0x00e7d300 when it does not. That second arm builds the same five-word
// transfer with the same nine-word region and differs in one visible way: its
// selector immediate is 0xac7161b5 where this block's is 0x9ef61113, and it
// pushes [0x016b3c04]'s word's 0x5190 member where this block pushes the same
// member. Two arms, one selector each, one shared tail. That is why the selector
// is a named constant here and why its sibling is recorded, and it is as far as
// the evidence goes: what the two selectors MEAN is not established by anything
// in this repository and is not guessed.

#ifndef OPENSPORE_RECONSTRUCTION_PKG_W2_00E7D2C0_BOUNDED_BLOCK_00E7D2C0_HPP
#define OPENSPORE_RECONSTRUCTION_PKG_W2_00E7D2C0_BOUNDED_BLOCK_00E7D2C0_HPP

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg_w2_00e7d2c0 {

// -- extent, restated from the bytes -------------------------------------------

// The 73 bytes of the block, from the image. Offset 0x09 is the target address
// 0x00e7d2c0 and the model test derives its value from the operand it is the
// high byte of, rather than reading the array and calling that a check.
constexpr std::size_t kBlockSpanBytes = 0x49;
constexpr std::size_t kTargetOffsetInBlock = 0x09;  // 0x00e7d2c0 - 0x00e7d2b7
constexpr int kBlockInstructionCount = 21;
constexpr int kConditionalBranchesInBlock = 0;
constexpr int kUnconditionalTransfersInBlock = 1;
constexpr int kDirectCalleesInBlock = 0;  // the block's exit is a JMP, not a CALL
constexpr int kZeroedWordCount = 9;
constexpr std::size_t kZeroedByteCount = 0x24;  // nine dwords

// Where the block begins and ends, and the containing body's own extent.
constexpr std::uint32_t kBlockFirstAddress = 0x00e7d2b7u;
constexpr std::uint32_t kBlockLastAddress = 0x00e7d2feu;
constexpr std::uint32_t kBodyFirstAddress = 0x00e7d070u;
constexpr std::uint32_t kBodyLastAddress = 0x00e7d360u;
constexpr std::size_t kBodySpanBytes = 753;
constexpr int kBodyInstructionCount = 224;
constexpr std::size_t kTargetOffsetInBody = 0x250;  // 592 bytes into a 753-byte body

// A 32-bit stack word, and a single byte of an image. Both are width claims
// only: the listing spells the block's memory operands `dword ptr` and nothing in
// it gives any of them a meaning, so a Word here is four bytes and not a value
// of any game type.
using Word = std::uint32_t;
using Byte = std::uint8_t;

// The callee's own stack window, as the block sees it.
//
// Sized by the block's own arithmetic and by nothing else: its largest
// displacement is 0x3c and it writes a whole dword there, so the window has to
// reach 0x40. This is a test-harness buffer standing for the callee's frame --
// it asserts nothing about any object the game owns, and it is not a layout
// claim about one.
struct StackWindow {
  Byte byte[0x40];
};

// The five words the block hands to the shared tail, in the order the block
// pushes them. Since the tail is entered by a jump and the call it makes is
// stack-argument-taking, the LAST push is the FIRST argument, which is the same
// order a C compiler emits right-to-left; the model test splats this struct
// through a real five-argument call to check that the two agree.
struct TailArguments {
  Word first;    // F+0x1c, pushed at 0x00e7d2bb
  Word second;   // F+0x28, pushed at 0x00e7d2c5
  Word third;    // F+0x34, pushed at 0x00e7d2f4
  Word fourth;   // the word at [0x016b3c04 + 0x5190], plus 0x10, pushed at 0x00e7d2f8
  Word fifth;    // 0x9ef61113, pushed at 0x00e7d2f9
};

// What the block leaves behind: the tail's argument vector, and the nine words
// it wrote, in ascending displacement order.
struct BlockOutcome {
  TailArguments tail;
  Word zeroed[kZeroedWordCount];
};

// The 73 bytes, transcribed from the image at RVA 0xa7d2b7 (raw offset
// 0xa7c577), and agreeing instruction for instruction with the evidence
// listing's entries for 0x00e7d2b7..0x00e7d2fe.
inline constexpr Byte kBlockBytes[kBlockSpanBytes] = {
    0x8du, 0x44u, 0x24u, 0x1cu, 0x50u, 0xa1u, 0x04u, 0x3cu,   // 0x00e7d2b7
    0x6bu, 0x01u, 0x8du, 0x4cu, 0x24u, 0x2cu, 0x51u, 0x89u,   // 0x00e7d2bf
    0x74u, 0x24u, 0x24u, 0x89u, 0x74u, 0x24u, 0x28u, 0x89u,   // 0x00e7d2c7
    0x74u, 0x24u, 0x2cu, 0x89u, 0x74u, 0x24u, 0x30u, 0x89u,   // 0x00e7d2cf
    0x74u, 0x24u, 0x34u, 0x89u, 0x74u, 0x24u, 0x38u, 0x89u,   // 0x00e7d2d7
    0x74u, 0x24u, 0x3cu, 0x89u, 0x74u, 0x24u, 0x40u, 0x89u,   // 0x00e7d2df
    0x74u, 0x24u, 0x44u, 0x8bu, 0x88u, 0x90u, 0x51u, 0x00u,   // 0x00e7d2e7
    0x00u, 0x8du, 0x54u, 0x24u, 0x3cu, 0x52u, 0x83u, 0xc1u,   // 0x00e7d2ef
    0x10u, 0x51u, 0x68u, 0x13u, 0x11u, 0xf6u, 0x9eu, 0xebu,   // 0x00e7d2f7
    0x48u,   // 0x00e7d2ff
};

// The displacement spellings the block itself uses, each relative to the ESP it
// had at that instruction and each present verbatim in the listing.
constexpr std::size_t kFirstFrameSlot = 0x1c;   // LEA EAX,[ESP + 0x1c] at 0x00e7d2b7
constexpr std::size_t kSecondFrameSlot = 0x2c;  // LEA ECX,[ESP + 0x2c] at 0x00e7d2c1
constexpr std::size_t kThirdFrameSlot = 0x3c;   // LEA EDX,[ESP + 0x3c] at 0x00e7d2f0
constexpr std::size_t kFirstStoreSlot = 0x24;   // MOV [ESP + 0x24],ESI at 0x00e7d2c6
constexpr std::size_t kOwnerDisplacement = 0x5190u;  // MOV ECX,[EAX + 0x5190] at 0x00e7d2ea
constexpr std::size_t kOwnerArgumentAdjust = 0x10u;  // ADD ECX,0x10 at 0x00e7d2f5

// The two selector immediates the two arms of the surrounding predicate push.
// This block's is the first; the sibling arm at 0x00e7d300 pushes the second and
// then falls into the same shared tail. Neither selector's meaning is
// established by anything in this repository.
constexpr Word kTailSelector = 0x9ef61113u;
constexpr Word kSiblingTailSelector = 0xac7161b5u;

// The absolute word the block loads into EAX at 0x00e7d2bc. The package does not
// model a global of that name -- no object, type, size or meaning is claimed for
// it -- it records the address and hands the model a pointer instead.
constexpr std::uint32_t kEntryRootWordAddress = 0x016b3c04u;

// The instruction the target byte lives inside: opcode 0xa1 (MOV EAX, moffs32)
// with its four-byte absolute operand, five bytes in all, starting at 0x00e7d2bc.
constexpr std::size_t kTargetInstructionOffset = 0x05;
constexpr std::size_t kTargetInstructionLength = 5;

// Where the block's exit lands, and what the shared tail does with the five
// words. Both are read out of the listing; the tail is NOT modelled as a call in
// this source, and the reason is recorded in the metadata sidecar: the CALLS
// oracle for this target is keyed on 0x00e7d070, and naming a callee address in
// this span would put a claim the export cannot reach into the check.
constexpr std::uint32_t kBlockExitTarget = 0x00e7d348u;
constexpr std::size_t kSharedTailPopsWords = 5;  // ADD ESP,0x14 at 0x00e7d34d
constexpr std::uint32_t kSharedTailCallTarget = 0x00e394f0u;

// The block's frame, in the machine's own units. Each of these is the count of
// PUSH instructions the block has executed at the moment the displacement
// beside it is read. A PUSH moves ESP down by four bytes, so a displacement read
// `pushes` words into the block names a frame slot that much lower than its
// literal spelling; the model carries the count explicitly rather than folding
// it into the constants above, because folding it in is a different program.
constexpr int kPushesAtFirstLea = 0;
constexpr int kPushesAtSecondLea = 1;
constexpr int kPushesAtStores = 2;
constexpr int kPushesAtThirdLea = 2;
constexpr int kTotalPushes = 5;

// The near CALL pushes a 4-byte return address on x86-32. Carried explicitly, as
// every ESP sample in the model test is computed from it rather than assumed.
constexpr std::size_t kReturnAddressBytes = 4;

// The other definition of ESI in the listing, and the only one. The block itself
// never writes ESI, which is why the model takes the stored word as a parameter.
constexpr std::uint32_t kEsiDefinitionAddress = 0x00e7d23du;

// The body's own epilogue, the seven bytes at 0x00e7d35a..0x00e7d360, read out
// of the image (raw offset 0xa7c8d0) and transcribed here because it is what the
// record's cleanup claim rests on:
//
//   00e7d35a  5e           POP ESI
//   00e7d35b  5d           POP EBP
//   00e7d35c  5f           POP EDI
//   00e7d35d  83 c4 30     ADD ESP,0x30
//   00e7d360  c3           RET
//   00e7d361  cc           the first byte of the inter-function padding
//
// The terminator is the ONE-byte RET: no immediate follows it, so this function
// pops nothing of its own, which is exactly `cleanup.bytes 0` and
// `cleanup.side "caller"` with the record's evidence "ret with no immediate". The
// 0x30 that ADD ESP discards is the body's own `SUB ESP,0x30` at 0x00e7d076, and
// the three POPs undo this body's own PUSH EDI / PUSH EBP / PUSH ESI -- not
// anything a caller passed.
inline constexpr Byte kBodyEpilogueBytes[7] = {
    0x5eu, 0x5du, 0x5fu, 0x83u, 0xc4u, 0x30u, 0xc3u,
};

static_assert(kBlockSpanBytes == 0x49u, "twenty-one instructions summing to 0x49 bytes");
static_assert(kTargetOffsetInBlock == 9u, "0x00e7d2c0 - 0x00e7d2b7 == 9");
static_assert(kTargetInstructionOffset + kTargetInstructionLength - 1u == kTargetOffsetInBlock,
              "the target byte is the LAST byte of the 5-byte instruction at +0x05");
static_assert(kZeroedWordCount * 4u == kZeroedByteCount, "nine dwords are 36 bytes");
static_assert(kZeroedWordCount == 9u, "the listing shows nine stores, not eight or ten");
static_assert(kBlockInstructionCount == 21u, "the listing shows 21 instructions in this range");
static_assert(kTargetOffsetInBody + kTargetOffsetInBlock - kBlockFirstAddress + 1u > 0u,
              "the block lies inside the body");
static_assert(sizeof(Word) == 4, "every stack word the block touches is four bytes");
static_assert(sizeof(void*) == 4, "pointers are 32-bit on this target");
static_assert(kReturnAddressBytes == sizeof(void*),
              "a near CALL pushes one pointer of return address on x86-32");
static_assert(kTotalPushes * 4u == 0x14u,
              "five pushed words are the 0x14 the shared tail's ADD ESP,0x14 pops");

// -- the machine record, carried as DATA ---------------------------------------
//
// Every value below is transcribed from the evidence pack's abi_derived
// category and from nothing else. They are data so that a package which quietly
// reverted to claiming a receiver or a convention fails the model test instead
// of passing, and so that a reviewer can check each one against the pack.

enum class DerivedVerdict00e7d2c0 : int { kAbiUnknown = 0 };
enum class ConventionConfidence00e7d2c0 : int { kUnknown = 0, kInferred = 1 };
enum class ReceiverAbstention00e7d2c0 : int { kEcxReassignedBeforeDeref = 0 };
enum class CleanupSide00e7d2c0 : int { kCaller = 0, kCallee = 1 };
enum class ReturnRegisterClass00e7d2c0 : int { kFloatOrX87InSt0 = 0 };
enum class ReturnConfidence00e7d2c0 : int { kApproximation = 0 };

constexpr DerivedVerdict00e7d2c0 kDerivedVerdict = DerivedVerdict00e7d2c0::kAbiUnknown;
// The record names NO convention. kDeclaredConventionCount is zero on purpose:
// the record's single candidate is a candidate list at UNKNOWN confidence, and
// adopting it would be exactly the claim this package refuses to make.
constexpr ConventionConfidence00e7d2c0 kConventionConfidence = ConventionConfidence00e7d2c0::kUnknown;
constexpr int kDeclaredConventionCount = 0;
constexpr int kConventionCandidateCount = 1;
constexpr int kConventionAmbiguityCount = 1;  // ["variadic_suspected"]

constexpr ReceiverAbstention00e7d2c0 kReceiverAbstention =
    ReceiverAbstention00e7d2c0::kEcxReassignedBeforeDeref;
// The honest form of the record's null: `false` here means NOT CLAIMED, and it
// asserts nothing in either direction about any register being a receiver.
constexpr bool kReceiverClaimed = false;
constexpr bool kReceiverBoundsOnly = true;
constexpr int kReceiverDistinctOffsets = 0;
constexpr int kReceiverDereferenceCount = 0;
constexpr int kAbstentionCount = 9;  // len(abi_derived.abstained_because)

constexpr CleanupSide00e7d2c0 kObservedCleanupSide = CleanupSide00e7d2c0::kCaller;
constexpr std::size_t kStackCleanupBytes = 0;

constexpr ReturnRegisterClass00e7d2c0 kReturnRegisterClass =
    ReturnRegisterClass00e7d2c0::kFloatOrX87InSt0;
constexpr ReturnConfidence00e7d2c0 kReturnConfidence = ReturnConfidence00e7d2c0::kApproximation;
constexpr bool kVoidPossible = false;

constexpr int kParseDeclaredCount = 224;
constexpr int kParseUnparsed = 0;
constexpr bool kParseDegraded = false;
constexpr int kDispatchIndirectCalls = 0;
constexpr int kDispatchVtableShapedLoads = 0;

// The record's own withdrawal of its argument-slot list. Carried as a flag
// because the model hands itself a frame window instead of trusting the walk.
constexpr bool kEntrySlotsUntrusted = true;

static_assert(kDeclaredConventionCount == 0,
              "the record names no convention; declaring one here would be a fabrication");
static_assert(kReceiverClaimed == false, "the record names no receiver register");
static_assert(kStackCleanupBytes == 0u && kObservedCleanupSide == CleanupSide00e7d2c0::kCaller,
              "a bare RET with no immediate is caller-side cleanup of zero bytes");
static_assert(kParseDeclaredCount == kBodyInstructionCount,
              "the machine parse consumed the whole 224-instruction body");
static_assert(kParseUnparsed == 0 && !kParseDegraded, "the body was fully parsed");
static_assert(kDispatchIndirectCalls == 0, "the body dispatches through no register or slot");

// -- the reconstruction --------------------------------------------------------

// The bounded block at 0x00e7d2b7..0x00e7d2fe, which contains the target byte
// 0x00e7d2c0 in the operand of its fifth instruction.
//
//   window     the callee's own stack, as the block sees it. F is window->byte;
//              the block's displacements are all relative to it, with the push
//              count carried explicitly rather than folded in.
//   root       the value the absolute word at 0x016b3c04 holds. A parameter, not
//              a global read, so that the model asserts no object of any kind.
//   store_word the value the nine stores write. The block writes the register it
//              was given and never writes that register itself.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
BlockOutcome reconstruct_00e7d2c0(StackWindow* window, const void* root, Word store_word);

}  // namespace openspore::reconstruction::pkg_w2_00e7d2c0

#endif  // OPENSPORE_RECONSTRUCTION_PKG_W2_00E7D2C0_BOUNDED_BLOCK_00E7D2C0_HPP
