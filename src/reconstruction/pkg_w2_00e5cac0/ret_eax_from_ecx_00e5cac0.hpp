// PKG-W2-00E5CAC0 -- VA 0x00e5cac0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// THE COMPLETE BODY. Five bytes, two instructions, no callee, no memory operand
// of any kind, no branch, no indirect transfer:
//
//   00e5cac0  8B C1       MOV EAX,ECX
//   00e5cac2  C2 04 00    RET 0x4
//
// GhidraMCP /read_memory at 0x00e5cac0 returns `8bc1c20400cccccccccccccccccccccc`
// for the first 16 bytes: the five body bytes above, then 0xCC inter-function
// padding. Nothing in this package reaches past 0x00e5cac4.
//
// WHAT THE BODY IS, TIED TO THE BYTES.
//
//   8B C1  MOV r32, r/m32. ModRM 0xC1 is mod=11 (register/register, no
//         displacement), reg=000 (EAX, the destination) and r/m=001 (ECX, the
//         source). All 32 bits of ECX are copied into EAX. No flag is touched
//         and no memory is read or written: both operands are registers.
//   C2 04 00  RET imm16. The opcode is followed by a 16-bit little-endian
//         immediate, 0x0004, so the callee pops four bytes off its own stack
//         frame on return. That is the only stack effect the body has.
//
// So the body is a pure register pass-through with a four-byte callee-side
// stack cleanup: the value in ECX on entry is the value in EAX on exit, and
// the one 4-byte slot that `RET 0x4` accounts for is never read.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// The derived ABI record for this target (reconstruction/evidence/00e5cac0/
// evidence.json, category abi_derived) states, field for field:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : INFERRED
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities           : []
//   verdict                           : ABI_INFERRED   (conflicts: [] empty)
//
//   receiver.present         : true
//   receiver.register        : ECX
//   receiver.provenance      : vftable_slot_dispatch
//   receiver.confidence      : INFERRED
//   receiver.bounds_only     : true
//   receiver.shape           : null
//   receiver.distinct_offsets : 0
//   receiver.offsets         : []
//   receiver.written_through  : 0
//
//   cleanup.bytes    : 4      confidence OBSERVED
//   cleanup.side     : callee confidence OBSERVED
//   cleanup.evidence : "ret 0x4"
//
// in the two steps the record itself separates, and both are reproduced in the
// data block at the bottom of this file:
//
//   R1-VFT  (INFERRED) "ECX carries the receiver". 0x00e5cac0 is slot 28 of the
//                      vptr-backed vftable at 0x013f57f8, so it is a virtual
//                      member of some class, and the body READS the register such
//                      a dispatch delivers (MOV EAX,ECX, one incoming ECX read).
//                      The rule discriminates that from the COM / __stdcall
//                      interface form, which takes its receiver from the first
//                      popped stack word and never reads its incoming ECX. The
//                      record states the cleanup side as `callee` in the same
//                      step, which is what makes the two forms distinguishable.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             table 0x013f57f8, slot_index 28, membership_count 3,
//             incoming_ecx_reads 1, cleanup_side callee}
//
//   C6B     (INFERRED) "the calling convention is __thiscall". The callee pops
//                      its own stack word, which rules out cdecl and fastcall,
//                      and the receiver arrives in ECX.
//
// INFERRED, not OBSERVED: nothing here has watched a caller dispatch through a
// table. What WAS observed is the cleanup (`RET 0x4` is in the bytes) and the
// register-to-register move; the convention and the receiver are inferred from
// those together with the slot membership.
//
// CORROBORATION FROM THE CALLER SIDE, WHICH IS NOT THE SOURCE OF THE CLAIM.
//
// GhidraMCP /read_memory gives a this-adjustor at 0x007fbd8d and 0x007fbd9d, and
// the two other direct call sites carry no adjustor at all:
//
//   007fbd61  e8 5a 0d 66 00   CALL 0x00e5cac0    ; no ECX adjustor before it
//   007fbd8d  83 c1 0c         ADD ECX,0xc
//   007fbd90  e8 2b 0d 66 00   CALL 0x00e5cac0    ; ECX is this + 0xc here
//   007fbd9d  83 c1 0c         ADD ECX,0xc        ; a different callee follows
//   007fbfc8  e8 f3 0a 66 00   CALL 0x00e5cac0    ; no ECX adjustor before it
//
// A first argument that a CALLER-side instruction reduces, or increases, by a
// constant before the transfer is a receiver; a by-value parameter is not
// adjusted by its caller. That is a second, independent machine source which
// agrees with R1-VFT, and it is recorded here as CORROBORATION. The
// determination stands on R1-VFT and C6B.
//
// The three vptr-backed tables that name this address -- 0x013f57f8 (slot 28),
// 0x0140116c (slot 6) and 0x01485550 (slot 21), each confirmed by reading the
// word at table_base + 4*slot back out of the image as 0x00e5cac0 -- are the
// membership R1-VFT reasons from. They are NOT three classes: identical folding
// and vtable merging both put one address in several tables, and the five bytes
// cannot tell those apart. No class, no vtable identity and no slot boundary is
// claimed anywhere in this package, and the model test dispatches only through a
// table it builds itself.
//
// WHAT THE CONVENTION DOES NOT SETTLE. A convention is not an identity.
//
// __thiscall says the receiver arrives in ECX. It does not say what the receiver
// IS. This body copies ECX into EAX and does nothing else: it never dereferences
// the register in any register, and it neither adds nor subtracts from it. So:
//
//   * no owning class and no vtable identity. R1-VFT names ONE table base and
//     the slot's own index as the evidence for the receiver; a slot is not a
//     class, and this binary carries no MSVC RTTI.
//   * no receiver type, shape, object size, vtable-pointer offset, field,
//     member or layout. The receiver is therefore declared and deliberately left
//     UNDEFINED (`struct Receiver;`), and the record's `bounds_only true` with an
//     empty `offsets` list is the correct reading rather than a gap. NO FIELD
//     OFFSET IS CLAIMED IN EITHER DIRECTION: the body shows none, so this
//     package asserts neither a field at any offset nor the absence of one as a
//     property of the object.
//   * nothing about the relationship between the three tables, or between the
//     unadjusted and the +0xc-adjusted call sites.
//
// THE ONE POPPED STACK WORD IS DATA, NOT A RECEIVER, AND THE PACKAGE KEEPS THEM
// APART. The word at entry_ESP+0x4 is never read: the machine record says so
// directly (`source: "ret_immediate"`, `observed: false`, `read: false`,
// `written: false`), and the code says so too -- the body has no stack operand.
// A 4-byte slot is modelled because the terminal immediate accounts for exactly
// four bytes; that is the popped area and not a parameter count, so the slot is
// named for the bytes and not for a meaning. It is a DIFFERENT value from the
// receiver, and the model test drives the two independently so that a
// reconstruction which folds one into the other is refuted.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-w2-00e5cac0 staging requires an x86-32 target"
#endif

// The convention is spelled once, here, and #undef'd again at the bottom so the
// body re-defines the same macro instead of depending on this header's lifetime.
//
// GCC rejects the bare MSVC keyword in the attribute position on some versions,
// so the attribute form is the portable spelling and the keyword form is kept for
// MSVC. Either way the token `thiscall` is carried once per macro, which is what
// the validator's convention resolution follows.
#if defined(_MSC_VER)
#define PKG_W2_00E5CAC0_THISCALL __thiscall
#else
#define PKG_W2_00E5CAC0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_w2_00e5cac0 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x00e5cac0.
inline constexpr std::uint32_t kTargetVa = 0x00e5cac0u;
inline constexpr std::uint32_t kBodyFirstByte = 0x00e5cac0u;
inline constexpr std::uint32_t kBodyLastByte = 0x00e5cac4u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x00e5cac5u;

// -- the receiver, and the popped stack word ----------------------------------

// The receiver. Declared and left UNDEFINED on purpose: the body never
// dereferences it, so its size, layout, members and object identity are all
// unproven, and an empty definition here would be a claim that there are no
// members rather than a statement that none was observed. The model test supplies
// its own opaque byte run through a cast for exactly that reason.
struct Receiver;

// The one ordinary stack slot at entry_ESP+0x4: four bytes wide because the
// terminal immediate accounts for four bytes, and never read. A dword is declared
// for its width, not for a parameter count.
using Word = std::uint32_t;

// -- extent, restated from the two instructions -------------------------------

constexpr int kInstructionCount = 2;
constexpr std::size_t kBodySpanBytes = 5;
constexpr int kBasicBlockCount = 1;  // the fall-through head; there is no branch
constexpr int kConditionalBranches = 0;
constexpr int kDirectCalleeCount = 0;
constexpr int kIndirectTransfers = 0;
constexpr int kGlobalReferences = 0;
constexpr int kStackArgumentSlots = 1;
constexpr std::size_t kStackCleanupBytes = 4;

// The five bytes, transcribed from GhidraMCP /read_memory at 0x00e5cac0:
//
//   8b c1 c2 04 00
//
// which is exactly the 2 instructions in the evidence listing, at exactly the
// addresses in the evidence listing, consuming all 5 bytes with nothing left
// over. The 0xCC that follows is the first byte of the inter-function padding,
// so the body is five bytes and not six.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x8bu,             // 00e5cac0  MOV EAX,ECX   opcode
    0xc1u,             //            ModRM 0xC1: mod=11, reg=EAX, r/m=ECX
    0xc2u,             // 00e5cac2  RET imm16      opcode
    0x04u,             //            immediate low byte
    0x00u,             //            immediate high byte -> 0x0004
};

static_assert(kBodySpanBytes == 5u,
              "MOV r32,r/m32 with mod=11 is two bytes and RET imm16 is three, "
              "at 0x00e5cac0");
static_assert(kStackCleanupBytes == 4u, "RET 0x4 at 0x00e5cac2 -- the immediate is 4");
static_assert(sizeof(Word) == 4, "the popped slot is a 32-bit slot");
static_assert(sizeof(void*) == 4, "pointers are 32-bit on this target");

// The byte at 0x00e5cac4, from the same live read. Recorded so the model test can
// check the transcription against the image's own padding rather than against
// nothing.
constexpr std::uint8_t kInterFunctionPad = 0xCCu;

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that
// changing one is a change the model test can catch, and so that a package which
// quietly reverted to the old abstention -- "no convention, no receiver" --
// fails the model test instead of passing.

// The convention the derived record names: __thiscall, with no other candidate.
enum class ConventionVerdict00e5cac0 : int { kThiscall = 0 };

// INFERRED, not OBSERVED and not UNKNOWN. The determination is an inference from
// the vftable-slot rule and the cleanup side; nothing here observed a caller
// dispatching through a table.
enum class ConventionConfidence00e5cac0 : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};

// The register the receiver arrives in.
enum class ReceiverRegister00e5cac0 : int { kEcx = 0 };

// Why the derived record believes a receiver is there at all.
enum class ReceiverProvenance00e5cac0 : int { kVftableSlotDispatch = 0 };

// Which side of the stack argument this callee pops.
enum class CleanupSide00e5cac0 : int { kCallee = 0 };

constexpr ConventionVerdict00e5cac0 kDerivedConventionVerdict =
    ConventionVerdict00e5cac0::kThiscall;
constexpr ConventionConfidence00e5cac0 kDerivedConventionConfidence =
    ConventionConfidence00e5cac0::kInferred;
constexpr int kCandidateConventionCount = 1;
constexpr int kConventionAmbiguityCount = 0;

constexpr ReceiverRegister00e5cac0 kDerivedReceiverRegister =
    ReceiverRegister00e5cac0::kEcx;
constexpr ReceiverProvenance00e5cac0 kReceiverProvenance =
    ReceiverProvenance00e5cac0::kVftableSlotDispatch;
constexpr bool kReceiverPresent = true;
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverHasShape = false;
// 0, because the two instructions contain no load and no store through the
// receiver in any register, and so no displacement of the object was ever seen.
constexpr int kReceiverDereferenceCount = 0;
constexpr int kReceiverDistinctOffsets = 0;
// The honest form of the two facts above: the body shows no offset, so this
// package claims none -- neither a field at some offset nor the object's being
// flat. `false` here means "not claimed", NOT "there is no field".
constexpr bool kReceiverFieldOffsetClaimed = false;

// Separately OBSERVED, and independent of the convention: the terminator's own
// form is RET 0x4.
constexpr CleanupSide00e5cac0 kObservedCleanupSide = CleanupSide00e5cac0::kCallee;
constexpr std::size_t kRetImmediateBytes = 4;
constexpr std::size_t kStackArgumentWords = 1;
// The one popped stack word is never READ and never WRITTEN. It is DATA. It is
// not the receiver and never becomes one.
constexpr bool kStackArgumentRead = false;
constexpr bool kStackArgumentWritten = false;
constexpr bool kStackArgumentIsReceiver = false;

// The register the answer is returned in, named the way the ModRM byte of the
// body itself names it: reg=000 is EAX, and that is the only register the five
// bytes write. The width is the 4 bytes `MOV EAX,ECX` copies, and EAX carries it
// into the single reachable RET.
constexpr int kReturnRegisterId = 0;  // ModRM reg field: 0 is EAX
constexpr std::size_t kReturnWidthBytes = 4;

// -- the caller-side this-adjustor, and the tables, as CORROBORATION -----------
//
// Read as bytes from the image; see the note at the top of this file. These are
// facts about other addresses and about three data tables, and they CORROBORATE
// the convention R1-VFT derived. They are not its source, and the body at
// 0x00e5cac0 neither adds nor subtracts anything of its own.
//
// The three direct call sites, from the xref export and confirmed by reading
// their rel32 displacements back out of the image.
constexpr std::uint32_t kDirectCallSites[] = {0x007fbd61u, 0x007fbd90u, 0x007fbfc8u};
constexpr int kDirectCallSiteCount = 3;
// The one of them whose ECX the caller adjusts first.
constexpr std::uint32_t kThisAdjustorCallSite = 0x007fbd90u;
constexpr std::uint32_t kThisAdjustorInstruction = 0x007fbd8du;
constexpr std::uint32_t kThisAdjustment = 0x0cu;

// The three vptr-backed tables that name this address, with the slot index each
// one holds it at. table_base + 4 * index was read back out of the image and
// holds 0x00e5cac0 in all three cases. They are membership evidence, not three
// classes, and nothing here claims a class.
constexpr std::uint32_t kTableBases[] = {0x013f57f8u, 0x0140116cu, 0x01485550u};
constexpr int kTableSlotIndices[] = {28, 6, 21};
constexpr int kTableCount = 3;

// -- the reconstruction --------------------------------------------------------

// FUN_00e5cac0 @ 0x00e5cac0, reconstructed.
//
// A __thiscall member whose whole behaviour is `MOV EAX,ECX` followed by
// `RET imm16 0x0004`. __thiscall is what puts the receiver in ECX; the
// callee-side cleanup of the one stack word is carried by the entry's own `retl
// $4`, which is the machine instruction 0x00e5cac2 rather than a statement about
// it. The receiver is forwarded into EAX verbatim and is never dereferenced.
//
// The parameters are named `receiver` and `popped_stack_slot` because this entry
// is an ordinary declarable function, not a naked transcription, so it has a body
// that can read them.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" Receiver* PKG_W2_00E5CAC0_THISCALL reconstruct_00e5cac0(Receiver* receiver,
                                                                 Word popped_stack_slot);

}  // namespace openspore::reconstruction::pkg_w2_00e5cac0

#undef PKG_W2_00E5CAC0_THISCALL
