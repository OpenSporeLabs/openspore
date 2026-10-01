// PKG-W2-00F96840 -- VA 0x00f96840
// Boundary facts for the 15-instruction body at 0x00f96840..0x00f96869.
//
// Every value below is transcribed from one of exactly two machine sources:
//
//   * the disassembly listing and the 42 bytes read back out of the image
//     (GhidraMCP /disassemble_function and /read_memory at 0x00f96840), and
//   * reconstruction/evidence/00f96840/evidence.json, category abi_derived.
//
// Where those two sources abstain, this header abstains with them and says which
// one abstained. Every gap listed at the bottom of this file is a real open
// question, not a placeholder to be tidied away, and none of them is filled in
// with a plausible guess.
//
// THE CALLING CONVENTION IS NOT CLAIMED, AND THAT IS THE MACHINE'S ANSWER, NOT
// AN OMISSION. The derived ABI record for this target states, field for field:
//
//   conventions.calling_convention    : null
//   conventions.confidence            : UNKNOWN
//   conventions.candidate_conventions : ["__cdecl", "__stdcall", "__thiscall",
//                                       "__fastcall"]
//   conventions.ambiguities           : []
//   verdict                           : ABI_UNKNOWN
//   abstained_because                 : ["no_terminal_ret: function has no RET
//                                       instruction"]
//   cleanup.bytes                     : null
//   cleanup.side                      : null
//   cleanup.confidence                : UNKNOWN
//
// The last instruction is JMP EDX at 0x00f96868 and there is no RET anywhere in
// the body, so the record's own C6B rule -- which names a convention from a
// callee-side cleanup together with a receiver register -- has no terminator to
// read, and the record abstains with that exact reason. Four candidates remain
// and none is selected. This package therefore declares NO calling convention:
// there is no PKG_W2_00F96840_THISCALL macro, no __thiscall, no __cdecl, and the
// reconstructed entry names no convention token. Declaring one would be
// asserting a fact the record states it cannot determine, and a receiver in ECX
// is not by itself a convention: a __stdcall COM body and a __thiscall C++
// object method both present their receiver in the first popped stack word, and
// nothing in these 42 bytes distinguishes them.
//
// WHAT THE RECORD *DOES* ESTABLISH IS THE RECEIVER, AND IT IS A REAL
// DERIVATION, NOT A GUESS. Category abi_derived states:
//
//   receiver.present          : true
//   receiver.register         : ECX
//   receiver.confidence       : INFERRED
//   receiver.shape            : "R-ALIAS"
//   receiver.bounds_only      : true
//   receiver.distinct_offsets : 2
//   receiver.offsets          : [0, 2068]      (0x0 and 0x814)
//   receiver.max_offset       : 2068           (0x814)
//   receiver.written_through  : 1
//
// on inference R1 (INFERRED), "ECX carries a receiver and is dereferenced before
// any definite write to it", from observations obs-0002, obs-0003 and obs-0009.
// The body corroborates that reading directly: ECX is copied into ESI at
// 0x00f96841 and never written again until 0x00f9684f, so every displacement
// that names the object is written through the alias. Exactly two distinct
// receiver displacements exist, and this header carries exactly those two:
// 0x00 (the object's first word, read three times) and 0x814 (written with the
// immediate 0 once). bounds_only is the record's own statement that the
// enumeration is open, so no member is named and no size, layout or type is
// claimed. `Receiver` is declared and deliberately left undefined.
//
// NO CLASS, NO VTABLE IDENTITY, NO FIELD NAME. The body reads the word at the
// receiver's +0x00 three times and uses it as a table pointer, and the machine
// record's own vtables category associates this address with vtable 0x01490be8
// (this body is a slot OF that table -- it is referenced BY it at 0x01490c70,
// so the association is the opposite of the body dispatching). None of that
// names an owning class: this binary carries no MSVC RTTI, no SDK name is
// recorded for the table, and a slot is not a class. The three displacements the
// body reads THROUGH the table word -- 0x70, 0x60 and 0x84 -- are carried here as
// the machine's own dispatch record names them, and nothing is claimed about
// which members they are or what the three routines do.
//
// THE RETURN IS NOT CLASSIFIED, AND NO RETURN TYPE IS CLAIMED. The record says
// return register EAX, register_class "pointer_like", confidence INFERRED,
// type null, void_possible false, envelope return_semantics
// "pointer_like_in_EAX". None of that is a C type, and the body has no return
// at all: its only exit is the tail jump at 0x00f96868, so the value the caller
// eventually sees in EAX is whatever the routine at table slot 0x84 leaves there,
// and that routine is outside this body. Naming a return type here would name the
// return type of a function this reconstruction has not analysed. The
// reconstruction consequently declares its entry `void`, which is a statement
// about the ENTRY -- it has no return of its own -- and not a claim about EAX.
//
// FRAME. No PUSH EBP, no MOV EBP,ESP, no SUB ESP, no stack allocation and no
// spill: parse.frame reads push_ebp false, mov_ebp_esp false, sub null,
// local_extent 0, seh_or_cookie_frame false. The body's entire local state is
// the one register it saves, ESI, at 0x00f96840 and 0x00f96867. PUSH ESI is the
// whole prologue and POP ESI the whole epilogue; the body pops before the tail
// jump, so the tail target is entered with the caller's stack exactly as it was.

#ifndef RECONSTRUCTION_STAGING_PKG_W2_00F96840_W2_00F96840_TYPES_HPP_
#define RECONSTRUCTION_STAGING_PKG_W2_00F96840_W2_00F96840_TYPES_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-w2-00f96840 requires an x86-32 target"
#endif

// The entry is NAKED and carries NO calling-convention token. The macro below
// exists only so the declaration keeps the one shape both toolchains accept for a
// byte-faithful transcription, and deliberately names no convention: the derived
// record states conventions.calling_convention = null with confidence UNKNOWN and
// abstained_because "no_terminal_ret: function has no RET instruction", and all
// four candidates (__cdecl, __stdcall, __thiscall, __fastcall) are still open.
// Adding a convention token here would state a fact the machine refuses to state.
#if defined(_MSC_VER)
#define PKG_W2_00F96840_NAKED __declspec(naked)
#else
#define PKG_W2_00F96840_NAKED __attribute__((naked))
#endif

#if defined(_MSC_VER)
#define PKG_W2_00F96840_NOINLINE __declspec(noinline)
#else
#define PKG_W2_00F96840_NOINLINE __attribute__((noinline))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00f96840 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind this source span to 0x00f96840.
inline constexpr std::uint32_t kTargetVa = 0x00f96840u;
inline constexpr std::uint32_t kBodyFirstByte = 0x00f96840u;
inline constexpr std::uint32_t kBodyLastByte = 0x00f96869u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00f9686au;

// -- the receiver ------------------------------------------------------------

// Declared and left UNDEFINED on purpose. The record enumerates two
// displacements and no shape, and bounds_only is its own statement that the
// enumeration is open, so an empty definition here would claim there are no
// members rather than state that none was observed.
struct Receiver;

// The two receiver displacements the machine record enumerates, and nothing
// more. 0x0 is the object's first word, read at 0x00f96843, 0x00f9684a and
// 0x00f96853. 0x814 is written once, with the immediate 0, at 0x00f9685b.
constexpr std::uint32_t kReceiverOffsetFirstWord = 0x000u;
constexpr std::uint32_t kReceiverOffsetZeroed = 0x814u;
constexpr int kReceiverDistinctOffsetCount = 2;
constexpr int kReceiverWrittenThroughCount = 1;

// The immediate the single receiver write stores. 0x00f9685b is
// `MOV dword ptr [ESI + 0x814], 0x0`, and the whole ten-byte encoding was read
// back from the image (c7 86 14 08 00 00 00 00 00 00), so the stored word is
// zero and not merely "a constant".
constexpr std::uint32_t kZeroedWord = 0x00000000u;

// -- the three table slots the body dispatches through ------------------------
//
// Each is a displacement read through the word at the receiver's +0x00 and then
// called (0x70 and 0x60) or jumped to (0x84). These are the machine dispatch
// record's three sites and nothing more: no member is named, and the routine at
// each slot is outside this body.
constexpr std::uint32_t kSlotFirstCall = 0x70u;   // 0x00f96845, CALL EDX at 0x00f96848
constexpr std::uint32_t kSlotSecondCall = 0x60u;  // 0x00f9684c, CALL EDX at 0x00f96851
constexpr std::uint32_t kSlotTailTransfer = 0x84u;  // 0x00f96855, JMP EDX at 0x00f96868
constexpr int kIndirectTransferCount = 3;

// -- extent, restated from the fifteen instructions --------------------------

constexpr int kInstructionCount = 15;
constexpr std::size_t kBodySpanBytes = 42;
constexpr int kBasicBlockCount = 1;  // straight-line: no branch of any kind
constexpr int kConditionalBranches = 0;
constexpr int kDirectCalleeCount = 0;
constexpr int kGlobalReferences = 0;
constexpr int kStackArgumentSlots = 0;  // nothing is ever pushed for a callee
constexpr int kTerminalRetCount = 0;    // which is why the ABI record abstained
constexpr int kTailTransferCount = 1;
constexpr int kSavedRegisterCount = 1;  // ESI, at 0x00f96840 and 0x00f96867

// -- the forty-two bytes, read back from the image ---------------------------
//
// GhidraMCP /read_memory at 0x00f96840 for 42 bytes returns
//
//   56 8b f1 8b 06 8b 50 70 ff d2 8b 06 8b 50 60 8b ce ff d2 8b 06
//   8b 90 84 00 00 00 c7 86 14 08 00 00 00 00 00 00 8b ce 5e ff e2
//
// which decodes to exactly the fifteen instructions of the evidence listing, at
// exactly the addresses in that listing, consuming all 42 bytes with nothing left
// over: 1+2+2+3+2 +2+3+2+2 +2+6+10+2+1+2 = 42, and ghidra_function reports
// body_start 0x00f96840, body_end 0x00f96869, body_span_bytes 42. The instruction
// lengths sum to body_span_bytes and the last byte falls on body_end, so the
// body span and the listing are the same 42 bytes by two independent routes.
//
// There is no rel32 displacement anywhere in the body: all three transfers are
// register-indirect, so no address in these bytes encodes anything and every one
// of them is compared literally.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x56u,                              // 00f96840  PUSH ESI
    0x8bu, 0xf1u,                       // 00f96841  MOV ESI,ECX
    0x8bu, 0x06u,                       // 00f96843  MOV EAX,[ESI]
    0x8bu, 0x50u, 0x70u,                // 00f96845  MOV EDX,[EAX+0x70]
    0xffu, 0xd2u,                       // 00f96848  CALL EDX
    0x8bu, 0x06u,                       // 00f9684a  MOV EAX,[ESI]
    0x8bu, 0x50u, 0x60u,                // 00f9684c  MOV EDX,[EAX+0x60]
    0x8bu, 0xceu,                       // 00f9684f  MOV ECX,ESI
    0xffu, 0xd2u,                       // 00f96851  CALL EDX
    0x8bu, 0x06u,                       // 00f96853  MOV EAX,[ESI]
    0x8bu, 0x90u, 0x84u, 0x00u, 0x00u, 0x00u,  // 00f96855  MOV EDX,[EAX+0x84]
    0xc7u, 0x86u, 0x14u, 0x08u, 0x00u, 0x00u,  // 00f9685b  MOV [ESI+0x814],0x0
    0x00u, 0x00u, 0x00u, 0x00u,        //           (rest of the 10-byte form)
    0x8bu, 0xceu,                       // 00f96865  MOV ECX,ESI
    0x5eu,                              // 00f96867  POP ESI
    0xffu, 0xe2u,                       // 00f96868  JMP EDX
};

// The four positions whose encoding the assembler is free to spell two ways: the
// binary writes `MOV ESI,ECX` as 8b f1 and `MOV ECX,ESI` as 8b ce, while the GNU
// assembler prefers the operand-reversed forms 89 ce and 89 f1 for the same
// instructions. Each pair is accepted in either spelling and every other one of
// the forty-two positions is compared literally.
constexpr std::size_t kEcxToEsiFirstByte = 1u;
constexpr std::size_t kEcxToEsiSecondByte = 2u;
constexpr std::size_t kEsiToEcxFirstByte = 15u;
constexpr std::size_t kEsiToEcxSecondByte = 16u;
constexpr std::size_t kEsiToEcxSecondOccurrenceFirstByte = 37u;
constexpr std::size_t kEsiToEcxSecondOccurrenceSecondByte = 38u;
constexpr int kDivergentByteCount = 6;  // three register moves, two bytes each
constexpr int kLiteralByteCount = 36;   // 42 - 6

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that
// changing one is a change the model test can catch: every assertion below is
// made against a literal SPELLING written in the test, never against the header's
// own pointer to its constant, because a comparison with that pointer would still
// hold after the header had been changed to say something else.

// What the record says about the convention. NOT a determination.
enum class ConventionVerdict00f96840 : int { kUndetermined = 0 };
enum class ConventionConfidence : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};
enum class CandidateConvention00f96840 : int {
  kCdecl = 0,
  kStdcall = 1,
  kThiscall = 2,
  kFastcall = 3
};

constexpr ConventionVerdict00f96840 kDerivedConventionVerdict =
    ConventionVerdict00f96840::kUndetermined;
constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kUnknown;
constexpr int kCandidateConventionCount = 4;
// The convention token this package's own entry declares. There is none, and the
// model test reads this constant to prove it.
constexpr bool kEntryDeclaresConvention = false;

// Why the record abstained, verbatim. Carried as a fact about the record, not as
// this package's own opinion about the convention.
constexpr const char* kAbstentionReason =
    "no_terminal_ret: function has no RET instruction";

// The cleanup side. UNDETERMINED, and the enumerator has no callee/caller
// member to select: there is no terminator carrying an immediate, so the record
// read neither a side nor a byte count, and this package does not read one either.
enum class CleanupSide00f96840 : int { kUndetermined = 0 };
constexpr CleanupSide00f96840 kObservedCleanupSide =
    CleanupSide00f96840::kUndetermined;
constexpr bool kCleanupSideDetermined = false;
constexpr std::size_t kRetImmediateBytes = 0;  // no terminator carries one
constexpr bool kTerminalRetPresent = false;

// The receiver, spelled here: present, in ECX, bounds-only, two displacements.
enum class ReceiverRegister00f96840 : int { kEcx = 0 };
enum class ReceiverShape00f96840 : int { kRegisterAlias = 0 };

constexpr ReceiverRegister00f96840 kDerivedReceiverRegister =
    ReceiverRegister00f96840::kEcx;
constexpr ReceiverShape00f96840 kReceiverShape =
    ReceiverShape00f96840::kRegisterAlias;
constexpr bool kReceiverPresent = true;
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverHasType = false;
constexpr int kReceiverDistinctOffsets = 2;

// The return register, and the fact that no C type is claimed for it.
enum class ReturnRegisterClass00f96840 : int { kPointerLike = 0 };
constexpr ReturnRegisterClass00f96840 kReturnRegisterClass =
    ReturnRegisterClass00f96840::kPointerLike;
constexpr bool kReturnTypeClaimed = false;
constexpr bool kVoidPossibleByMachine = false;

// -- the reconstruction --------------------------------------------------------

// FUN_00f96840 @ 0x00f96840, reconstructed.
//
// A NAKED transcription of the target's own 42 bytes, with NO calling
// convention, because the derived ABI record determines none. The three
// transfers are all register-indirect, so the block names no symbol and needs no
// relocation; every address it touches it reads out of the receiver at run time.
//
// `void` is the honest spelling for the entry: the body has no terminator of its
// own and its last instruction transfers control out through table slot 0x84. It
// is a statement about the ENTRY, not a claim that EAX is left with nothing --
// the machine record says the opposite (return_semantics "pointer_like_in_EAX",
// void_possible false), and the value the caller eventually receives in EAX is the
// tail routine's, which is outside this body. The entry is therefore entered with
// the receiver in ECX, observed mechanically, and the model test drives it
// through a harness that puts that value there.
//
// The parameters are left unnamed because the function is naked and has no C++
// body to read them in; a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared
// shape -- a receiver pointer in ECX, no stack argument -- is the shape the
// listing fixes, not a signature claim.
extern "C" void PKG_W2_00F96840_NAKED re_00f96840(void);

}  // namespace pkg_w2_00f96840
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_W2_00F96840_W2_00F96840_TYPES_HPP_
