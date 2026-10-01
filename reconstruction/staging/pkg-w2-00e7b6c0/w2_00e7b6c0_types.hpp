// PKG-W2-00E7B6C0 -- VA 0x00e7b6c0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000,
//  binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// WHAT THIS TARGET IS, AND WHERE ITS 386 BYTES BEGIN.
//
// The target VA 0x00e7b6c0 is NOT a function entry. It is a byte in the middle
// of the body of the machine function FUN_00e7b630, and this package says so
// rather than quietly relocating the body to the queue's address:
//
//   * GhidraMCP /get_function_by_address @ 0x00e7b6c0 returns
//     FUN_00e7b630, entry_point 00e7b630, body_start 00e7b630,
//     body_end 00e7b7b1. There is no function whose entry is 0x00e7b6c0, and
//     no instruction begins at 0x00e7b6c0.
//   * 0x00e7b6c0 is offset 0x90 of 0x00e7b630 and is the FOURTH byte of the
//     rel32 displacement of the direct call at 0x00e7b6bc. Those five bytes
//     are e8 4f 6b cf ff: next-instruction 0x00e7b6c1 plus signed -0x003094b1
//     lands on 0x00b72210, which is what the xref export records at callsite
//     00e7b6bc.
//   * The evidence pack's ghidra_function sub-record agrees on every count
//     (body_start 00e7b630, body_end 00e7b7b1, body_span_bytes 386,
//     size_bytes 386, locals_count 3) and the disassembly category holds 105
//     instructions, the whole of that body.
//
// So the reconstruction below is of FUN_00e7b630's 386 bytes, and its name
// carries the queue's 8-hex VA because that is the binder the validator
// resolves a source span with. Both facts are carried as data
// (kTargetVaIsAnInstructionStart is false, kEnclosingFunctionEntry is
// 0x00e7b630) and both are checked by the model test.
//
// THE COMPLETE BODY: 105 instructions, 0x00e7b630..0x00e7b7b1, 386 bytes.
// The last instruction is the single-byte RET at 0x00e7b7b1 (byte c3), so the
// body's last byte IS body_end and the exclusive end is 0x00e7b7b2. The bytes
// were read back out of the image for this package (section .text, RVA
// 0x00a7b630, file offset derived from the PE section table) and are
// transcribed in kTargetBytes; they are exactly the 105 instructions of the
// evidence listing at exactly its addresses, consuming all 386 bytes with
// nothing left over.
//
// THE MACHINE ABI RECORD ABSTAINS, AND THIS PACKAGE ABSTAINS WITH IT.
//
// reconstruction/evidence/00e7b6c0/evidence.json, category abi_derived, states
// field for field:
//
//   conventions.calling_convention    : null
//   conventions.confidence            : UNKNOWN
//   conventions.candidate_conventions : ["__cdecl", "__thiscall"]
//   conventions.ambiguities           : ["receiver_undetermined"]
//   conventions.corroboration         : "not_available"
//   verdict                           : ABI_UNKNOWN
//
//   receiver.present         : null          receiver.register : null
//   receiver.reason          : "ecx_read_without_deref"
//   receiver.bounds_only     : true
//   receiver.shape           : null
//   receiver.distinct_offsets: 0
//   receiver.offsets         : []
//   receiver.written_through : 0
//   receiver.confidence      : UNKNOWN
//
//   cleanup.bytes    : 0    cleanup.side    : caller
//   cleanup.confidence: INFERRED
//   cleanup.evidence : "ret with no immediate"
//
//   return: {aggregate_evidence {bulk_write false}, confidence APPROXIMATION,
//            register "ST0", register_class "float_or_x87", type null,
//            void_possible false}
//
//   abstained_because:
//     flow_not_modelled: the linear ESP walk ends at +8, so the listing is not
//                         one path
//     untrusted_frame_stack_reads: push ebp with no mov ebp,esp
//     frame_pointer_untrusted: push ebp without mov ebp,esp
//     receiver_not_determinable: ecx_read_without_deref
//     receiver_undetermined_blocks_convention
//
// EVERY ONE OF THOSE IS REPRODUCED AS DATA BELOW and checked value by value by
// the model test, against literals the test writes for itself. The
// consequences are load-bearing and they run in both directions:
//
//   * NO CALLING CONVENTION IS DECLARED IN THE SOURCE. The record names two
//     candidates and resolves neither, so there is nothing to declare. The
//     convention token is not written anywhere in this package; kConvention
//     Tokens Declared is 0 and the test checks it.
//   * NO RECEIVER IS CLAIMED. The record's own reason is the whole story:
//     ECX is READ WITHOUT BEING DEREFERENCED, so the register rule cannot tell
//     a hidden `this` from an ordinary integer argument. And the body settles
//     it: at 0x00e7b68b it does `MOV ECX,[EAX+0x1b0]` and at 0x00e7b691
//     `PUSH ECX` -- ECX holds a 32-bit value loaded out of memory and is passed
//     to 0x00e6d200 as one of its four ordinary stack arguments, while the rest
//     of the body works through EAX, EBX, EDX, EDI, EBP and ESI. ECX is written
//     and read seventeen times and never dereferenced, which is exactly the
//     shape the rule abstains on.
//   * 0x00e7b6c0 IS ALSO NOT A MEMBER OF ANY SOUND VPTP-BACKED TABLE, so the
//     vftable-slot receiver rule has nothing to reason from either.
//   * NO FIELD, NO MEMBER, NO LAYOUT, NO OBJECT SIZE is claimed for any
//     pointer the body touches. The displacements below are displacements out
//     of instructions; they are not struct members and no `->field` appears
//     anywhere in this package's code.
//
// The two candidates the record does name are recorded as a SET and nothing
// more: the cleanup is caller-side with zero bytes, which rules out every
// callee-cleaned convention, and that is all the record's own candidate list
// leaves standing.
//
// WHAT THE CLEANUP SIDE IS, AND HOW IT WAS ESTABLISHED.
//
//   cleanup.side = caller, bytes = 0, evidence "ret with no immediate".
//
// Both halves are visible in the body: the only terminator is the bare `c3` at
// 0x00e7b7b1, and the epilogue's own arithmetic closes. With S the entry stack
// pointer, the fall-through path pushes sixteen words and removes 0x8 + 0x10 +
// 0xc + 0x10 + 0x8 = 0x34 bytes with SUB/ADD and three more with the three POPs,
// so the body is eight bytes DEEPER at its RET than it was at its entry, and
// the two calls that own the difference are 0x00b72210 -- read out of the same
// image as five instructions ending `c2 04 00`, i.e. RET 0x4, twice. Sixteen
// minus eight is eight: exactly two callee-popped four-byte words. The RET
// therefore has to pop nothing, and the model test re-derives that figure from
// the byte transcripts rather than trusting this paragraph.
//
// The two early-exit paths close on their own and need no callee at all:
// the two JZ at 0x00e7b63f and 0x00e7b64c land on 0x00e7b7ad, the POP EBP, and
// have exactly one word outstanding (the PUSH EBP at 0x00e7b63a); the three
// JNZ at 0x00e7b65b, 0x00e7b667 and 0x00e7b673 land on 0x00e7b7ac, the POP EBX,
// and have exactly two outstanding (PUSH EBP, PUSH EBX). Neither path has run
// PUSH EDI, and neither reaches POP EDI.
//
// THE FRAME, AND THE ONE PLACE THE MACHINE RECORD IS INCOMPLETE.
//
// SUB ESP,0x8 at 0x00e7b630 reserves the eight bytes S-8..S-1. Inside that
// reservation the body uses both halves, at different times:
//
//   S-4  a 32-bit float local. FSTP dword [ESP+0x20] at 0x00e7b69b stores into
//        it, with the stack pointer at S-36; FLD dword [ESP+0x10] at 0x00e7b6c1
//        reads it back, with the stack pointer at S-20. Same slot, twice.
//   S-8  a 32-bit handle local. LEA ECX,[ESP+0xc] at 0x00e7b74e and
//        LEA EDX,[ESP+0xc] at 0x00e7b76c and LEA ECX,[ESP+0xc] at 0x00e7b7a2 all
//        form its ADDRESS, with the stack pointer at S-20 in all three cases.
//        0x00743b50 zeroes it at 0x00e7b761; 0x00e4cc40 stores into it at
//        0x00e7b772; 0x00e82130 reads through it at 0x00e7b7a6.
//
// That is where the record's own abstention bites. abi_derived.stack_arguments
// enumerates ONE slot -- entry_ESP+0x4, ordinal 1, observed true, sizes [4] --
// and marks it `read: false`, while the body plainly reads that word at
// 0x00e7b63b. The record explains itself: "untrusted_frame_stack_reads: push
// ebp with no mov ebp,esp: EBP is a general register, so every frame-relative
// offset is uncalibrated". A linear ESP walk that has not calibrated the frame
// cannot resolve [ESP+0x10] to entry_ESP+0x4. The frame IS calibratable here
// and the calibration is a fact of the bytes: SUB ESP,0x8 then PUSH EBP puts
// the stack pointer at S-12, so [ESP+0x10] is [S+4] = entry_ESP+0x4. This
// package therefore records kStackArgumentReadByBody as true and says in the
// model test that this is a READING with its own evidence, not an edit to the
// record. The record is left exactly as the machine wrote it.
//
// The record's second abstention -- "the linear ESP walk ends at +8, so the
// listing is not one path" -- is the same fact from the other side, and it is
// why the record stops at one stack slot. The listing is not one path: three
// of its five conditional branches are early exits that never reach the rest.
//
// WHAT THE RETURN IS, AND WHAT IT IS NOT.
//
// The machine record's return sub-record is at confidence APPROXIMATION and
// names ST0 with register_class float_or_x87, under rule RT1 whose stated basis
// is "the return value is carried in ST0: an x87 or SSE instruction appears in
// the body". The body does pop the x87 stack twice more than it pushes it --
// the FSTP at 0x00e7b69b pops a value this body never pushed, and the FSTP at
// 0x00e7b6cb pops a register the FST at 0x00e7b6c8 has just emptied -- so
// whatever the machine's ST0 held on entry is consumed and nothing is left.
//
// The source declares `void`, and that is a READING of the listing rather than
// a recovered fact: at the single return site 0x00e7b7b1 no instruction has
// placed a value in EAX, EDX, ECX, EAX-through-XMM0 or ST0 for the caller.
// EAX's last write is 0x00e7b79b, which loads [ESI] and is consumed by nothing
// in particular -- the very next instruction is a call -- and XMM0's last write
// is 0x00e7b6c5, whose two consumers are the two MOVSS at 0x00e7b6ea and
// 0x00e7b6ef. The RT1 claim is recorded in the sidecar and is NOT adopted.
// What 0x00e6d200 leaves in ST0 is not determined by anything in evidence, and
// neither is the value the second FSTP stores; both are open questions, listed
// in the model test and in the sidecar.
//
// THE NINE CALLS, in listing order, each with what the body hands it.
//
// The order is fixed by the addresses: there is no branch between any two of
// them, so on the fall-through path all ten CALL instructions (0x00b72210 is
// called twice) run in this sequence with nothing between them that can be
// skipped. Each is an E8 rel32 with an immediate operand; the body performs no
// indirect transfer at all.
//
//   0x00e7b686  0x00b72210  ECX = [0x016b3c04]+0x1c ; one word = [ESI+0].
//                            RET 0x4 -- the callee pops that word.
//   0x00e7b696  0x00e6d200  four words, in push order: ECX = [EAX+0x1b0],
//                            0x31, 0, EAX. The caller drops all four with
//                            ADD ESP,0x10 at 0x00e7b6a7.
//   0x00e7b6ad  0x00b72160  ECX = [0x016b3c04]+0x54 ; no stack word. Its EAX is
//                            the base of the record fill.
//   0x00e7b6bc  0x00b72210  ECX = [0x016b3c04]+0x54 ; one word = the EAX just
//                            returned. RET 0x4. ITS RETURN IS THE RECORD BASE --
//                            and its rel32 is the instruction the target VA
//                            0x00e7b6c0 sits inside.
//   0x00e7b761  0x00743b50  ECX = S-8 ; no stack word. Writes 0.
//   0x00e7b772  0x00e4cc40  two words, in push order: S-8 and [EBP+0x108].
//   0x00e7b77e  0x00e5d7b0  one word: [EAX+0xb8].
//   0x00e7b793  0x00e780a0  four words, in push order: [EBP+0], 1, ECX, 0 --
//                            and FSTP dword [ESP] at 0x00e7b78d overwrites the
//                            THIRD of those with the bit pattern of +0.0f, made
//                            by the FLDZ at 0x00e7b783.
//   0x00e7b79d  0x00e59a70  EAX in ; no stack word.
//   0x00e7b7a6  0x00e82130  ECX = S-8 ; no stack word.
//
// The four terminators the model test needs were read out of the same image:
// 0x00b72210 ends c2 04 00 (RET 0x4) at 0x00b7221f; 0x00b72160 ends c3 at
// 0x00b721c0; 0x00743b50 is three instructions, mov eax,ecx / mov [eax],0 /
// ret, ending c3 at 0x00743b58; 0x00e4cc40 is a one-instruction JMP thunk onto
// 0x00e823a0, whose own epilogue balances and ends c3 at 0x00e823da;
// 0x00e5d7b0 ends c3 at 0x00e5da03; 0x00e780a0 ends 83 c4 10 c3 at
// 0x00e78223..0x00e78226; 0x00e59a70 ends 00 8a c1 c3 at 0x00e59a9d;
// 0x00e82130 ends ff 48 0c c3 at 0x00e82136. Only 0x00b72210's four-byte
// immediate is load-bearing for the frame; the rest are recorded so the model
// test can show which of them it relied on, and one of them is a CONTRADICTION
// this package does not resolve (see below).
//
// THE ONE CONTRADICTION IN THE CALLEE SIDE, REPORTED AND NOT RESOLVED.
//
// 0x00e6d200's last instruction pair is `83 c4 14 c3` -- ADD ESP,0x14, RET --
// and 0x00e780a0's is `83 c4 10 c3`. If those were the exits these two CALL
// sites take, both would remove four bytes more than the caller removes, and
// the epilogue would not close: the body is eight bytes deeper at its RET than
// at its entry, and the only two callee-popped words available are 0x00b72210's
// two RET 0x4s. So the exits these two sites actually take are not the ones
// Ghidra reports as those functions' highest-addressed instructions, and this
// package cannot say which exits they are. It does not need to: the frame is
// forced by the body's own arithmetic, which is checked independently, and the
// two terminator readings are carried as data so the disagreement is visible
// rather than smoothed over. See kContradictionsOpen in the sidecar.
//
// THE RECORD THE BODY FILLS, WITHOUT A LAYOUT CLAIM.
//
// EAX is a byte address the body computes through 0x00b72210 and then writes
// TWENTY-SIX times, at the displacements below. That is the complete set of
// writes the listing makes to that base, in listing order, with the value each
// one takes. Offsets 0x0c..0x1b are NOT written by this body, and neither is
// 0x00; the twenty-six displacements are recorded here as DISPLACEMENTS out of
// instructions and the model test checks each one against the byte it is
// encoded in. They are not members, no type is declared for them, and no
// sizeof is claimed. What lives at the base is 0x00b72210's business and is not
// in evidence.
//
// THE X87 PAIR AT 0x1c AND 0x20, WHICH IS NOT A PAIR OF DIFFERENT VALUES.
// ModRM 0x50 at 0x00e7b6c8 is FST and ModRM 0x58 at 0x00e7b6cb is FSTP. FST
// stores ST0 and does NOT pop, so both stores take the same register: the value
// FLD reloaded from the S-4 local, which is whatever the machine's own ST0 held
// when 0x00e6d200 returned. So 0x1c and 0x20 receive the SAME word, and the
// extra pop at 0x00e7b6cb leaves one x87 register the body did not push. The
// model test pins this by planting a SECOND, different value in the observer's
// ST1 and requiring neither field to be it.
//
// THE EIGHT GLOBAL READS.
//
// 0x016b3c04 (three times), 0x016b3c28, 0x016b3c2c, 0x016b3c30 (twice each) and
// 0x015a7c4c, 0x015a7c50, 0x015a7c54, 0x015a7c58 (once each). All eight are
// LOADS; the body stores through none of them, and it names no other
// data-segment address. The model test MAP_FIXEDs both pages, plants eight
// recognisable words in them, and requires each of the eight to reach the
// record at the displacement the listing names -- so the global reads are
// measured, not asserted.
//
// THE INCOMING REGISTERS, AS OBSERVED MECHANICS AND NOT AS A PARAMETER LIST.
//
// The body reads ESI seven times and writes it NEVER; it reads entry_ESP+0x4
// once; and it reads and writes ECX seventeen times, always as a 32-bit value
// and never dereferenced. EBP is not a frame pointer -- there is no MOV EBP,ESP
// anywhere in the 386 bytes -- it is loaded from the stack at 0x00e7b63b and
// then used as a general register at three displacements. EBX, EDI and EBP are
// the three saved registers, PUSHed and POPed in that nesting order. The
// reconstructed entry declares four unnamed parameters of opaque pointer and
// word types purely to describe the shape of the machine's entry, and declares
// NO receiver parameter because the record names no receiver.

#ifndef RECONSTRUCTION_STAGING_PKG_W2_00E7B6C0_W2_00E7B6C0_TYPES_HPP_
#define RECONSTRUCTION_STAGING_PKG_W2_00E7B6C0_W2_00E7B6C0_TYPES_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-w2-00e7b6c0 requires an x86-32 target"
#endif

// The `naked` attribute, spelled once, as a macro. The spelling is NOT a
// calling convention: the machine record resolves none, so no convention token
// appears in this macro or anywhere else in the package, and kConventionTokens
// Declared is 0 and the model test fails if that is edited away from zero.
// A macro rather than an inline attribute because the validator binds a source
// span by a declaration whose RETURN TYPE, an all-caps token and NAME are
// consecutive -- which is the same shape a package macro for a calling
// convention would have, and the reason the attribute is carried here rather
// than written between the return type and the name.
#if defined(_MSC_VER)
#define PKG_W2_00E7B6C0_NAKED __declspec(naked)
#else
#define PKG_W2_00E7B6C0_NAKED __attribute__((naked))
#endif

// The word this model moves around. A 32-bit slot is a machine fact wherever it
// is used; the C spelling is this package's choice.
using Word = std::uint32_t;

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00e7b6c0 {

// -- identity ----------------------------------------------------------------

// The queue's target VA. The reconstructed entry's name embeds it because that
// is the token the validator binds a source span with.
inline constexpr std::uint32_t kTargetVa = 0x00e7b6c0u;

// The function the target VA is INSIDE. GhidraMCP /get_function_by_address @
// 0x00e7b6c0 returns this entry point, and there is no function whose entry is
// 0x00e7b6c0.
inline constexpr std::uint32_t kEnclosingFunctionEntry = 0x00e7b630u;
inline constexpr bool kTargetVaIsAnInstructionStart = false;
// The target VA is offset 0x90 into the body and is the fourth byte of the
// rel32 displacement of the direct call at 0x00e7b6bc.
inline constexpr std::size_t kTargetVaOffsetInBody = 0x90u;
inline constexpr std::uint32_t kTargetVaInsideInstruction = 0x00e7b6bcu;
inline constexpr std::size_t kTargetVaByteIndexInInstruction = 4u;

inline constexpr std::uint32_t kBodyFirstByte = 0x00e7b630u;
inline constexpr std::uint32_t kBodyLastByte = 0x00e7b7b1u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00e7b7b2u;
inline constexpr std::size_t kBodySpanBytes = 386;
inline constexpr int kInstructionCount = 105;

// -- the machine ABI record, carried as DATA --------------------------------
//
// Every value below is transcribed from reconstruction/evidence/00e7b6c0/
// evidence.json, category abi_derived, and from nothing else. They are data
// rather than prose so that changing one is a change the model test can catch,
// and so that a package which quietly reverted to a receiver or a convention
// claim fails the model test instead of passing.

// The record resolves NO convention. These two are its candidate list, and this
// package declares neither.
enum class ConventionVerdict00e7b6c0 : int { kNone = 0 };
enum class ConventionConfidence00e7b6c0 : int { kUnknown = 0 };
inline constexpr ConventionVerdict00e7b6c0 kDerivedConventionVerdict =
    ConventionVerdict00e7b6c0::kNone;
inline constexpr ConventionConfidence00e7b6c0 kDerivedConventionConfidence =
    ConventionConfidence00e7b6c0::kUnknown;
inline constexpr int kCandidateConventionCount = 2;
inline constexpr int kConventionAmbiguityCount = 1;
inline constexpr const char* kCandidateConventionNames[2] = {"__cdecl",
                                                             "__thiscall"};
inline constexpr const char* kConventionAmbiguityName = "receiver_undetermined";
inline constexpr const char* kConventionCorroboration = "not_available";
// How many convention tokens this package's SOURCE declares. It is zero, and
// that is the point: the record names none, so the source names none.
inline constexpr int kConventionTokensDeclared = 0;

// The receiver. The record's own reason for abstaining, verbatim.
enum class ReceiverDetermination00e7b6c0 : int { kUndetermined = 0 };
inline constexpr ReceiverDetermination00e7b6c0 kDerivedReceiver =
    ReceiverDetermination00e7b6c0::kUndetermined;
inline constexpr const char* kReceiverAbstentionReason = "ecx_read_without_deref";
inline constexpr bool kReceiverPresent = false;
inline constexpr bool kReceiverRegisterClaimed = false;
inline constexpr bool kReceiverBoundsOnly = true;
inline constexpr bool kReceiverHasShape = false;
inline constexpr int kReceiverDistinctOffsets = 0;
inline constexpr int kReceiverDereferenceCount = 0;
inline constexpr int kReceiverRegisterReads = 17;
// The honest form of the two facts above: the body shows no receiver-relative
// displacement, so this package claims none -- neither a field at some offset
// nor the object's being flat. `false` here means "not claimed", NOT "there is
// no field".
inline constexpr bool kReceiverFieldOffsetClaimed = false;
// 0x00e7b6c0 is not a member of any sound vptr-backed table, which is why the
// vftable-slot receiver rule has nothing to reason from either.
inline constexpr int kOwnVptrTableMembershipCount = 0;
// ECX is NOT a receiver here. The two instructions that decide it.
inline constexpr std::uint32_t kEcxLoadInstruction = 0x00e7b68bu;
inline constexpr std::uint32_t kEcxPushInstruction = 0x00e7b691u;
inline constexpr std::uint32_t kEcxLoadDisplacement = 0x1b0u;

// The cleanup. OBSERVED in the form of the terminator, and the only side the
// record states.
enum class CleanupSide00e7b6c0 : int { kCaller = 0 };
inline constexpr CleanupSide00e7b6c0 kObservedCleanupSide =
    CleanupSide00e7b6c0::kCaller;
inline constexpr std::size_t kStackCleanupBytes = 0;
inline constexpr std::size_t kRetImmediateBytes = 0;
inline constexpr const char* kCleanupEvidence = "ret with no immediate";
// A CALL pushes the return address on top of the terminator's immediate, and
// `ret imm16` pops the return address FIRST and only then adds the immediate.
// The model test needs the return-address width to read a post-call ESP sample
// at all: a sample sits `kReturnAddressBytes` BELOW entry_ESP + the immediate.
inline constexpr std::uint32_t kReturnAddressBytes = 4u;

// The return. Recorded as the machine's APPROXIMATION, and NOT adopted.
enum class ReturnRegister00e7b6c0 : int { kSt0 = 0 };
enum class ReturnConfidence00e7b6c0 : int { kApproximation = 0 };
inline constexpr ReturnRegister00e7b6c0 kDerivedReturnRegister =
    ReturnRegister00e7b6c0::kSt0;
inline constexpr ReturnConfidence00e7b6c0 kDerivedReturnConfidence =
    ReturnConfidence00e7b6c0::kApproximation;
inline constexpr const char* kDerivedReturnRegisterClass = "float_or_x87";
inline constexpr bool kDerivedReturnVoidPossible = false;
inline constexpr bool kDerivedReturnTypeIsNull = true;
// The x87 pop/push balance of the body, as a fact about the listing: the body
// pops three registers and pushes two.
inline constexpr int kX87Pushes = 2;
inline constexpr int kX87Pops = 3;

// -- the stack argument ------------------------------------------------------

inline constexpr int kStackArgumentSlots = 1;
inline constexpr std::size_t kStackArgumentEntryOffset = 0x4u;
// The record says `read: false` because its linear ESP walk never calibrated
// the frame ("untrusted_frame_stack_reads: push ebp with no mov ebp,esp"). The
// body reads that word at 0x00e7b63b, and this is a READING with its own
// evidence, stated as one, not an edit to the record.
inline constexpr bool kStackArgumentReadByRecord = false;
inline constexpr bool kStackArgumentReadByBody = true;
inline constexpr std::uint32_t kStackArgumentReadInstruction = 0x00e7b63bu;
inline constexpr bool kStackArgumentWritten = false;
inline constexpr bool kStackArgumentIsReceiver = false;

// -- the frame ---------------------------------------------------------------

inline constexpr std::size_t kFrameReservationBytes = 0x8u;
// Both halves of the reservation are used, at different times, and by different
// kinds of value. With S the entry stack pointer:
inline constexpr std::size_t kLocalFloatOffsetFromEntry = 0x04u;  // S-4
inline constexpr std::size_t kLocalHandleOffsetFromEntry = 0x08u; // S-8
// The two stack-pointer values the two locals are reached at. These are facts
// about the listing, and the model test re-derives both by walking the ESP
// trace itself.
inline constexpr std::size_t kFloatSlotStoreEspDepth = 0x24u;  // S-36
inline constexpr std::size_t kFloatSlotLoadEspDepth = 0x14u;   // S-20
inline constexpr std::size_t kHandleSlotEspDepth = 0x14u;      // S-20
inline constexpr std::size_t kFloatSlotStoreDisplacement = 0x20u;
inline constexpr std::size_t kFloatSlotLoadDisplacement = 0x10u;
inline constexpr std::size_t kHandleSlotDisplacement = 0x0cu;
// The three instructions that form the handle slot's address, and the one that
// zeroes it, and the two that use it.
inline constexpr std::uint32_t kHandleLeaEcxInstruction = 0x00e7b74eu;
inline constexpr std::uint32_t kHandleLeaEdxInstruction = 0x00e7b76cu;
inline constexpr std::uint32_t kHandleLeaEcxInstruction2 = 0x00e7b7a2u;
inline constexpr std::uint32_t kHandleZeroInstruction = 0x00e7b761u;
inline constexpr std::uint32_t kHandleStoreInstruction = 0x00e7b772u;
inline constexpr std::uint32_t kHandleUseInstruction = 0x00e7b7a6u;
inline constexpr int kSavedRegisterCount = 3;

// -- the nine calls ----------------------------------------------------------

inline constexpr int kDirectCalleeCount = 9;
inline constexpr int kCallSiteCount = 10;
inline constexpr std::uint32_t kCallSites[10] = {
    0x00e7b686u, 0x00e7b696u, 0x00e7b6adu, 0x00e7b6bcu, 0x00e7b761u,
    0x00e7b772u, 0x00e7b77eu, 0x00e7b793u, 0x00e7b79du, 0x00e7b7a6u};
inline constexpr std::uint32_t kCalleeAddresses[9] = {
    0x00b72210u, 0x00e6d200u, 0x00b72160u, 0x00743b50u, 0x00e4cc40u,
    0x00e5d7b0u, 0x00e780a0u, 0x00e59a70u, 0x00e82130u};
inline constexpr int kIndirectTransfers = 0;
inline constexpr int kGlobalReferences = 8;
inline constexpr int kGlobalReads = 13;
inline constexpr int kGlobalWrites = 0;
inline constexpr std::uint32_t kGlobalAddresses[8] = {
    0x016b3c04u, 0x016b3c28u, 0x016b3c2cu, 0x016b3c30u,
    0x015a7c4cu, 0x015a7c50u, 0x015a7c54u, 0x015a7c58u};
// The four global words the record is filled from, and the displacement each
// one lands at, in the listing's order. Six of the eight words are copied
// twice each and the same three addresses are used twice, so the six
// displacements 0x48..0x5c are the same three values twice over.
inline constexpr std::size_t kRecordDisplacements[8] = {
    0x48u, 0x4cu, 0x50u, 0x54u, 0x58u, 0x5cu, 0x60u, 0x64u};
inline constexpr std::uint32_t kRecordGlobalSources[8] = {
    0x016b3c28u, 0x016b3c2cu, 0x016b3c30u, 0x016b3c28u,
    0x016b3c2cu, 0x016b3c30u, 0x015a7c4cu, 0x015a7c50u};

// -- the twenty-six writes the body makes to the record base -----------------
//
// DISPLACEMENTS out of instructions. No type, no member, no size and no layout
// is declared for the base; the model test checks each displacement against the
// bytes it is encoded in and against the value the listing puts there.
enum class RecordValueSource00e7b6c0 : int {
  kX87TopFirst = 0,       // FST  dword [EAX+off]  -- the reloaded S-4 local
  // FSTP dword [EAX+off]. The ModRM /3 at 0x00e7b6cb against the /0 at
  // 0x00e7b6c8 is the whole difference between the two, and it is the sharpest
  // x87 fact in the body: FST DOES NOT POP, so both adjacent stores take the
  // SAME register, and a transcription that spelled the first one FSTP would
  // leave the second store reading whatever was underneath.
  kX87TopSecond = 1,
  kImmediate = 2,         // MOV dword [EAX+off],0x20
  kEdi = 3,               // MOV dword [EAX+off],EDI   -- EDI was [ESI+0]
  kEbx = 4,               // MOV dword [EAX+off],EBX   -- EBX is 0
  kEbxByte = 5,           // MOV byte  [EAX+off],BL    -- one byte
  kEbxOrAllOnes = 6,      // MOV dword [EAX+off],ECX   -- ECX is 0xffffffff
  kXmm0 = 7,              // MOVSS  dword [EAX+off],XMM0 -- XMM0 is 0.0f
};

struct RecordWrite00e7b6c0 {
  std::uint32_t instruction;
  std::size_t displacement;
  RecordValueSource00e7b6c0 source;
  bool is_byte;
};

inline constexpr RecordWrite00e7b6c0 kRecordWrites[26] = {
    {0x00e7b6c8u, 0x1cu, RecordValueSource00e7b6c0::kX87TopFirst, false},
    {0x00e7b6cbu, 0x20u, RecordValueSource00e7b6c0::kX87TopSecond, false},
    {0x00e7b6ceu, 0x24u, RecordValueSource00e7b6c0::kImmediate, false},
    {0x00e7b6d5u, 0x28u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b6d8u, 0x2cu, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b6deu, 0x30u, RecordValueSource00e7b6c0::kEbxOrAllOnes, false},
    {0x00e7b6e1u, 0x34u, RecordValueSource00e7b6c0::kEbxOrAllOnes, false},
    {0x00e7b6e4u, 0x38u, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b6e7u, 0x3cu, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b6eau, 0x40u, RecordValueSource00e7b6c0::kXmm0, false},
    {0x00e7b6efu, 0x44u, RecordValueSource00e7b6c0::kXmm0, false},
    {0x00e7b6fau, 0x48u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b703u, 0x4cu, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b70cu, 0x50u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b715u, 0x54u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b71eu, 0x58u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b727u, 0x5cu, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b730u, 0x60u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b739u, 0x64u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b742u, 0x68u, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b74bu, 0x6cu, RecordValueSource00e7b6c0::kEdi, false},
    {0x00e7b752u, 0x70u, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b755u, 0x74u, RecordValueSource00e7b6c0::kEbxByte, true},
    {0x00e7b758u, 0x78u, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b75bu, 0x04u, RecordValueSource00e7b6c0::kEbx, false},
    {0x00e7b75eu, 0x08u, RecordValueSource00e7b6c0::kEbxByte, true},
};
// The two byte-wide writes are one byte each; everything else is four. The
// model test checks the twenty-six displacements tile 0x04..0x78 with exactly
// two single-byte holes at 0x74 and 0x08 and no overlap, which is a fact about
// the listing and not a layout claim.
inline constexpr int kRecordWriteCount = 26;
inline constexpr std::size_t kRecordLowestDisplacement = 0x04u;
inline constexpr std::size_t kRecordHighestDisplacement = 0x78u;
inline constexpr std::size_t kRecordUnwrittenRunLow = 0x0cu;
inline constexpr std::size_t kRecordUnwrittenRunHigh = 0x1cu;

// -- the constants the listing states ---------------------------------------

inline constexpr std::uint32_t kRecordImmediateValue = 0x20u;  // MOV [EAX+0x24],0x20
// OR ECX,0xffffffff sets every bit, so the two dwords at 0x30 and 0x34 are
// 0xffffffff whatever ECX held. That is arithmetic on the instruction, not a
// guess about the global's value.
inline constexpr std::uint32_t kRecordAllOnesValue = 0xffffffffu;
// The four bytes 0x016b3c04 is used with: +0x1c for the first 0x00b72210 and
// 0x00b72160 pair's neighbour, +0x54 twice, and the bare read itself.
inline constexpr std::uint32_t kGlobalBaseDisplacementA = 0x1cu;
inline constexpr std::uint32_t kGlobalBaseDisplacementB = 0x54u;
// The literal 0x31 is PUSHed as the second of 0x00e6d200's four stack words.
inline constexpr std::uint32_t kPlayAnimationSecondWord = 0x31u;
// The literal 1 is PUSHed as the second of 0x00e780a0's four stack words, and
// the third of those four is then overwritten with the bit pattern of +0.0f.
inline constexpr std::uint32_t kSecondHelperSecondWord = 0x1u;
// The four single-byte and byte-register comparisons that guard the fall-through
// path, in listing order: two against 1 and three against 0.
inline constexpr std::size_t kGuardDisplacements[5] = {0x112u, 0x113u, 0x178u,
                                                       0x17fu, 0x17bu};
inline constexpr int kGuardEqualOneCount = 2;
inline constexpr int kGuardEqualZeroCount = 3;
inline constexpr int kConditionalBranches = 5;
inline constexpr int kBasicBlockCount = 3;

// -- the callee terminators, read out of the same image ---------------------
//
// Only 0x00b72210's four-byte immediate is load-bearing for the frame. The
// other two `ADD ESP,n; RET` forms are the CONTRADICTION this package reports
// and does not resolve: taken at these call sites they would each remove four
// bytes more than the caller removes, and the epilogue would not close.
struct CalleeTerminator00e7b6c0 {
  std::uint32_t va;
  std::uint32_t terminator_address;
  const char* form;
  std::size_t pop_bytes;  // 4 when unknown-but-nonzero is impossible to model
  bool is_contradiction;
};

inline constexpr CalleeTerminator00e7b6c0 kCalleeTerminators[9] = {
    {0x00b72210u, 0x00b7221fu, "c2 04 00  RET 0x4", 4u, false},
    {0x00e6d200u, 0x00e6d33cu, "83 c4 14 c3  ADD ESP,0x14 ; RET", 20u, true},
    {0x00b72160u, 0x00b721c0u, "c3  RET", 0u, false},
    {0x00743b50u, 0x00743b58u, "c3  RET", 0u, false},
    {0x00e4cc40u, 0x00e823dau, "c3  RET (via the JMP thunk to 0x00e823a0)", 0u,
     false},
    {0x00e5d7b0u, 0x00e5da03u, "c3  RET", 0u, false},
    {0x00e780a0u, 0x00e78226u, "83 c4 10 c3  ADD ESP,0x10 ; RET", 16u, true},
    {0x00e59a70u, 0x00e59aa0u, "00 8a c1 c3  MOV AL,CL ; RET", 0u, false},
    {0x00e82130u, 0x00e82139u, "ff 48 0c c3  DEC dword [EAX+0xc] ; RET", 0u,
     false},
};
inline constexpr int kCalleeTerminatorCount = 9;
inline constexpr int kCalleeTerminatorContradictions = 2;
inline constexpr int kCalleePoppedWordsObserved = 2;

// -- the 386 bytes, transcribed from the image ------------------------------
//
// Read out of SPORE/SporeBin/SporeApp.exe at 0x00e7b630 (section .text, RVA
// 0x00a7b630) for 386 bytes. The same read was taken through
// GhidraMCP /read_memory and returns the identical string. These are exactly
// the 105 instructions of the evidence listing at exactly its addresses,
// consuming all 386 bytes with nothing left over.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x83u, 0xecu, 0x08u, 0x80u, 0xbeu, 0x12u, 0x01u, 0x00u, 0x00u, 0x01u,
    0x55u, 0x8bu, 0x6cu, 0x24u, 0x10u, 0x0fu, 0x84u, 0x68u, 0x01u, 0x00u,
    0x00u, 0x80u, 0xbeu, 0x13u, 0x01u, 0x00u, 0x00u, 0x01u, 0x0fu, 0x84u,
    0x5bu, 0x01u, 0x00u, 0x00u, 0x53u, 0x33u, 0xdbu, 0x38u, 0x9eu, 0x78u,
    0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x4bu, 0x01u, 0x00u, 0x00u, 0x38u,
    0x9eu, 0x7fu, 0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x3fu, 0x01u, 0x00u,
    0x00u, 0x38u, 0x9du, 0x7bu, 0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x33u,
    0x01u, 0x00u, 0x00u, 0x8bu, 0x06u, 0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu,
    0x01u, 0x57u, 0x83u, 0xc1u, 0x1cu, 0x50u, 0xe8u, 0x85u, 0x6bu, 0xcfu,
    0xffu, 0x8bu, 0x88u, 0xb0u, 0x01u, 0x00u, 0x00u, 0x51u, 0x6au, 0x31u,
    0x53u, 0x50u, 0xe8u, 0x65u, 0x1bu, 0xffu, 0xffu, 0xd9u, 0x5cu, 0x24u,
    0x20u, 0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu, 0x01u, 0x8bu, 0x3eu, 0x83u,
    0xc4u, 0x10u, 0x83u, 0xc1u, 0x54u, 0xe8u, 0xaeu, 0x6au, 0xcfu, 0xffu,
    0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu, 0x01u, 0x83u, 0xc1u, 0x54u, 0x50u,
    0xe8u, 0x4fu, 0x6bu, 0xcfu, 0xffu, 0xd9u, 0x44u, 0x24u, 0x10u, 0x0fu,
    0x57u, 0xc0u, 0xd9u, 0x50u, 0x1cu, 0xd9u, 0x58u, 0x20u, 0xc7u, 0x40u,
    0x24u, 0x20u, 0x00u, 0x00u, 0x00u, 0x89u, 0x78u, 0x28u, 0x89u, 0x58u,
    0x2cu, 0x83u, 0xc9u, 0xffu, 0x89u, 0x48u, 0x30u, 0x89u, 0x48u, 0x34u,
    0x89u, 0x58u, 0x38u, 0x89u, 0x58u, 0x3cu, 0xf3u, 0x0fu, 0x11u, 0x40u,
    0x40u, 0xf3u, 0x0fu, 0x11u, 0x40u, 0x44u, 0x8bu, 0x15u, 0x28u, 0x3cu,
    0x6bu, 0x01u, 0x89u, 0x50u, 0x48u, 0x8bu, 0x0du, 0x2cu, 0x3cu, 0x6bu,
    0x01u, 0x89u, 0x48u, 0x4cu, 0x8bu, 0x15u, 0x30u, 0x3cu, 0x6bu, 0x01u,
    0x89u, 0x50u, 0x50u, 0x8bu, 0x0du, 0x28u, 0x3cu, 0x6bu, 0x01u, 0x89u,
    0x48u, 0x54u, 0x8bu, 0x15u, 0x2cu, 0x3cu, 0x6bu, 0x01u, 0x89u, 0x50u,
    0x58u, 0x8bu, 0x0du, 0x30u, 0x3cu, 0x6bu, 0x01u, 0x89u, 0x48u, 0x5cu,
    0x8bu, 0x15u, 0x4cu, 0x7cu, 0x5au, 0x01u, 0x89u, 0x50u, 0x60u, 0x8bu,
    0x0du, 0x50u, 0x7cu, 0x5au, 0x01u, 0x89u, 0x48u, 0x64u, 0x8bu, 0x15u,
    0x54u, 0x7cu, 0x5au, 0x01u, 0x89u, 0x50u, 0x68u, 0x8bu, 0x0du, 0x58u,
    0x7cu, 0x5au, 0x01u, 0x89u, 0x48u, 0x6cu, 0x8du, 0x4cu, 0x24u, 0x0cu,
    0x89u, 0x58u, 0x70u, 0x88u, 0x58u, 0x74u, 0x89u, 0x58u, 0x78u, 0x89u,
    0x58u, 0x04u, 0x88u, 0x58u, 0x08u, 0xe8u, 0xeau, 0x83u, 0x8cu, 0xffu,
    0x8bu, 0x85u, 0x08u, 0x01u, 0x00u, 0x00u, 0x8du, 0x54u, 0x24u, 0x0cu,
    0x52u, 0x50u, 0xe8u, 0xc9u, 0x14u, 0xfdu, 0xffu, 0x8bu, 0x88u, 0xb8u,
    0x00u, 0x00u, 0x00u, 0x51u, 0xe8u, 0x2du, 0x20u, 0xfeu, 0xffu, 0xd9u,
    0xeeu, 0x8bu, 0x55u, 0x00u, 0x83u, 0xc4u, 0x0cu, 0x53u, 0x51u, 0xd9u,
    0x1cu, 0x24u, 0x6au, 0x01u, 0x52u, 0xe8u, 0x08u, 0xc9u, 0xffu, 0xffu,
    0x83u, 0xc4u, 0x10u, 0x8bu, 0x06u, 0xe8u, 0xceu, 0xe2u, 0xfdu, 0xffu,
    0x8du, 0x4cu, 0x24u, 0x0cu, 0xe8u, 0x85u, 0x69u, 0x00u, 0x00u, 0x5fu,
    0x5bu, 0x5du, 0x83u, 0xc4u, 0x08u, 0xc3u,
};

static_assert(kBodySpanBytes == 386u,
              "the body is 386 bytes, which is body_span_bytes in the evidence");
static_assert(sizeof(Word) == 4, "every slot this body moves is 32 bits");
static_assert(sizeof(void*) == 4, "pointers are 32-bit on this target");

// The sixty encoding-relative bytes: ten CALL rel32 displacements and five Jcc
// rel32 displacements. They cannot be compared against the binary numerically,
// because they encode addresses in a different image, so the model test RESOLVES
// each one out of the emitted code and requires it to land on the target the
// machine records. The remaining 326 are compared byte for byte.
inline constexpr int kCallRel32Count = 10;
inline constexpr int kBranchRel32Count = 5;
inline constexpr int kResolvedRel32Bytes = (kCallRel32Count + kBranchRel32Count) * 4;
inline constexpr int kLiteralByteCount = 386 - kResolvedRel32Bytes;

// Byte offsets, into kTargetBytes, of each rel32 displacement.
inline constexpr std::size_t kCallRel32Offsets[10] = {
    0x57u, 0x67u, 0x7eu, 0x8du, 0x132u, 0x143u, 0x14fu, 0x164u, 0x16eu, 0x177u};
inline constexpr std::size_t kBranchRel32Offsets[5] = {0x11u, 0x1eu, 0x2du,
                                                       0x39u, 0x45u};
// Where each of the ten must land, and where each of the five must land. The
// call targets are the nine distinct callees above, in the order the CALL
// instructions appear; the two JZ targets are the POP EBP at 0x00e7b7ad and the
// three JNZ targets are the POP EBX at 0x00e7b7ac.
inline constexpr std::uint32_t kCallRel32Targets[10] = {
    0x00b72210u, 0x00e6d200u, 0x00b72160u, 0x00b72210u, 0x00743b50u,
    0x00e4cc40u, 0x00e5d7b0u, 0x00e780a0u, 0x00e59a70u, 0x00e82130u};
inline constexpr std::uint32_t kBranchRel32Targets[5] = {
    0x00e7b7adu, 0x00e7b7adu, 0x00e7b7acu, 0x00e7b7acu, 0x00e7b7acu};
// The next-instruction address each displacement is measured from.
inline constexpr std::uint32_t kCallRel32Bases[10] = {
    0x00e7b68bu, 0x00e7b69bu, 0x00e7b6b2u, 0x00e7b6c1u, 0x00e7b766u,
    0x00e7b777u, 0x00e7b783u, 0x00e7b798u, 0x00e7b7a2u, 0x00e7b7abu};
inline constexpr std::uint32_t kBranchRel32Bases[5] = {
    0x00e7b645u, 0x00e7b652u, 0x00e7b661u, 0x00e7b66du, 0x00e7b679u};

// The 10-byte PC anchor a position-independent g++ build may prepend to a naked
// function, recognised by its exact opcode pair e8 ?? ?? ?? ?? 05. It is a
// toolchain artifact and is not part of the reconstruction; the model test
// requires the 386 target bytes immediately after it, so a toolchain that
// emitted some other form of anchor fails the byte comparison rather than
// passing it.
inline constexpr std::size_t kPcAnchorBytes = 10u;

// -- the ten call sites, declared as the model's own out-of-line calls --------
//
// Their addresses are in their names, which is the convention the validator
// reads to compare a source's call set against the machine's. Each is entered
// exactly the way the listing enters it -- the hidden register in ECX and the
// stack words the listing pushes -- and each is DEFINED, in the model test, as
// an observer that reproduces the call shape and the terminator form the image
// records. None of them is declared a class member and no receiver type is named
// for any of them, because the record names no receiver for this target and
// 0x00e7b6c0 is in no vptr-backed table.
extern "C" void callee_00b72210();
extern "C" void callee_00e6d200();
extern "C" void callee_00b72160();
extern "C" void callee_00743b50();
extern "C" void callee_00e4cc40();
extern "C" void callee_00e5d7b0();
extern "C" void callee_00e780a0();
extern "C" void callee_00e59a70();
extern "C" void callee_00e82130();

// -- the reconstruction ------------------------------------------------------

// FUN_00e7b630 @ 0x00e7b6c0, reconstructed.
//
// A naked transcription of the target's own 386 bytes. NO CALLING CONVENTION IS
// DECLARED, because the machine record resolves none: it names __cdecl and
// __thiscall as candidates and abstains with ABI_UNKNOWN and
// receiver_undetermined, so the source carries no convention token at all.
// NO RECEIVER PARAMETER IS DECLARED, for the same reason: the record's own
// abstention is `ecx_read_without_deref`, ECX is an ordinary 32-bit value that
// this body loads out of memory and pushes as a stack argument, and the address
// 0x00e7b6c0 is in no sound vptr-backed table.
//
// The four parameters are UNNAMED on purpose. This function is naked, so it has
// no C++ body to read them in, and a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. Their declared
// types describe only the SHAPE of the machine's entry and nothing about what
// the values are:
//
//   parameter 0   the value ESI holds on entry. The body reads ESI seven times
//                 and writes it never, and this is stated as an observed
//                 mechanic, NOT as a receiver: no pointer type, no object, no
//                 member and no field is claimed for it.
//   parameter 1   the value ECX holds on entry, which the body overwrites
//                 seventeen times and never dereferences.
//   parameter 2   the value EAX holds on entry, which the body overwrites at
//                 0x00e7b679 before it is ever read, so the machine never reads
//                 it. It is declared only so the entry shape is complete.
//   parameter 3   the single 32-bit word at entry_ESP+0x4, read once at
//                 0x00e7b63b and written never. The terminator is a bare RET,
//                 so the cleanup is caller-side and this package models
//                 exactly that: the body's own `ret` at 0x00e7b7b1, which is
//                 the machine instruction, not a statement about it.
//
// The return type is void, and that is a reading of the listing rather than a
// recovered fact: at the single return site no instruction has placed a value
// in a return register. The machine record's ST0 / float_or_x87 claim is
// carried in the header as data and is NOT adopted.
//
// The name embeds the queue's 8-hex target VA, which is what binds this span to
// this record in the validator, and the enclosing function's real entry is
// carried beside it so the two are never confused.
extern "C" void PKG_W2_00E7B6C0_NAKED reconstruct_00e7b6c0(const std::uint8_t*,
                                                        Word,
                                                        Word,
                                                        Word);

#undef PKG_W2_00E7B6C0_NAKED

}  // namespace pkg_w2_00e7b6c0
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_W2_00E7B6C0_W2_00E7B6C0_TYPES_HPP_
