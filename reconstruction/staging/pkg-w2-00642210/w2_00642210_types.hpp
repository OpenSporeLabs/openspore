// PKG-W2-00642210 -- VA 0x00642210
// Boundary types for the 11-instruction body at 0x00642210..0x0064222b.
//
// Everything here is named from the listing, from the machine-derived ABI record
// in the evidence pack, or from bytes read back out of the image. Where the
// evidence abstains, the type says so rather than filling the gap; the gaps are
// listed at the bottom of this file and each one is a real open question, not a
// placeholder to be tidied later.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// The derived ABI record for this target (reconstruction/evidence/00642210/
// evidence.json, category abi_derived) states, field for field:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : INFERRED
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities           : []
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
// in the two steps the record itself separates:
//
//   R1-VFT  (INFERRED) "ECX carries the receiver". This address is a slot of the
//                      vftable the record bases at 0x013ff648, and the body READS
//                      the register such a dispatch delivers -- a COM / __stdcall
//                      shaped body takes its receiver from the first popped stack
//                      word and never reads its incoming ECX. That is the
//                      distinction the rule discriminates on.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             table 0x013ff648, cleanup_side callee}
//
//   C6B     (INFERRED) "the calling convention is __thiscall". The callee pops
//                      its own stack word, which rules out cdecl and fastcall,
//                      and the receiver arrives in ECX.
//
// THE CALLER SIDE CORROBORATES IT, INDEPENDENTLY, AND IS NOT THE SOURCE OF THE
// CLAIM. There is no direct CALL into 0x00642210 anywhere in the image
// (dependencies.callers is empty with callers_truncated false, and the xref
// export records no incoming call edge). The only two code references to the
// address are tail JMPs, each immediately preceded by a caller-side ECX
// adjustor. GhidraMCP /disassemble_bytes over 0x00642150..0x0064218f gives:
//
//   00642170  83 e9 10        SUB ECX,0x10   ;  00642173  e9 98 00 00 00  JMP 0x00642210
//   00642180  83 e9 14        SUB ECX,0x14   ;  00642183  e9 88 00 00 00  JMP 0x00642210
//
// A first argument that a CALLER-side stub reduces by a constant before the
// transfer is a receiver; a by-value parameter is not adjusted by its caller.
// The same two stubs exclude the pack's former other candidate, __stdcall: a
// free function has no receiver for a caller-side stub to adjust by a constant.
// This is CORROBORATION. The determination above stands on R1-VFT and C6B; the
// stubs are a second machine source that agrees, not the reason for the claim.
//
// WHAT THE CONVENTION DOES NOT SETTLE. A convention is not an identity.
// __thiscall says the receiver arrives in ECX. It does not say what the receiver
// IS. This body copies ECX into ESI at 0x00642211, hands that VALUE to two other
// routines and puts it in EAX at 0x00642228, and it never dereferences it: there
// is no load and no store through the receiver anywhere in the eleven
// instructions, in any register. So this package names:
//
//   * no owning class, and no vtable identity. R1-VFT names ONE table base
//     (0x013ff648) and the slot's own displacement (+0x00) as the evidence for
//     the receiver; a slot is not a class, and this binary carries no MSVC RTTI.
//   * no receiver type, shape, object size, vtable-pointer offset or field. The
//     receiver is therefore declared and deliberately left undefined
//     (struct Receiver;), and the only memory operand in the whole body is the
//     stack byte at [ESP + 0x8].
//   * no relationship between the two entry stubs and any base address. ECX
//     arrives at two different displacements and the body neither adds nor
//     subtracts anything of its own, so the base relationships are UNRESOLVED
//     and are not guessed here.
//
// THE ONE POPPED STACK WORD IS DATA, NOT A RECEIVER, AND THE PACKAGE KEEPS THEM
// APART. The word at entry_ESP+0x4 is read for bit 0 of its low byte and for
// nothing else. It is never handed to either callee, never becomes the value in
// EAX, and never has a register. The receiver is a different value entirely: it
// arrives in ECX, is aliased into ESI, is passed to 0x00642190 in ECX and to
// 0x00f47380 on the stack, and is what the tail puts in EAX. Conflating the two
// would be the one substantive ABI error available here, so the model test drives
// the option word over the whole byte range and the receiver independently, and
// plants values that make the two distinguishable.

#ifndef RECONSTRUCTION_STAGING_PKG_W2_00642210_W2_00642210_TYPES_HPP_
#define RECONSTRUCTION_STAGING_PKG_W2_00642210_W2_00642210_TYPES_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-w2-00642210 requires an x86-32 target"
#endif

// The convention is spelled once, here, and the reconstructed entry names the
// macro.
//
//   PKG_W2_00642210_THISCALL       the convention on an ordinary declarable
//                                  function. It is what the model test gives the
//                                  first callee, which the machine enters the
//                                  same way (object in ECX, bare RET).
//   PKG_W2_00642210_NAKED_THISCALL the same convention on the naked
//                                  byte-faithful transcription of the target's
//                                  own 30 bytes.
//
// GCC rejects the bare MSVC keyword in the attribute position on some versions,
// so the attribute form is the portable spelling and the keyword form is kept
// for MSVC. Either way the token `thiscall` is carried once per macro, which is
// what the validator's convention resolution follows.
#if defined(_MSC_VER)
#define PKG_W2_00642210_THISCALL __thiscall
#define PKG_W2_00642210_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_W2_00642210_THISCALL __attribute__((thiscall))
#define PKG_W2_00642210_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00642210 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x00642210.
inline constexpr std::uint32_t kTargetVa = 0x00642210u;
inline constexpr std::uint32_t kBodyFirstByte = 0x00642210u;
inline constexpr std::uint32_t kBodyLastByte = 0x0064222du;
inline constexpr std::uint32_t kBodyEndExclusive = 0x0064222eu;

// -- the receiver, and the option word ---------------------------------------

// The receiver. Declared and left UNDEFINED on purpose: the body never
// dereferences it, so its size, layout, members and object identity are all
// unproven, and an empty definition here would be a claim that there are no
// members rather than a statement that none was observed.
struct Receiver;

// The one ordinary stack argument: a 32-bit slot at entry_ESP+0x4 whose low
// BYTE and, within that, whose bit 0 is all the body ever looks at. A dword is
// declared because the slot is four bytes wide, not because four bytes are read;
// 0x00642218 reads one byte of it.
using OptionWord = std::uint32_t;

// The immediate at 0x00642218. The body's only immediate operand, and the only
// bit of caller-supplied data it ever examines.
constexpr OptionWord kOptionBit0 = 0x1u;

// -- extent, restated from the eleven instructions ---------------------------

constexpr int kInstructionCount = 11;
constexpr std::size_t kBodySpanBytes = 30;
constexpr int kBasicBlockCount = 2;  // the fall-through head and the JZ target
constexpr int kConditionalBranches = 1;
constexpr int kDirectCalleeCount = 2;
constexpr int kIndirectTransfers = 0;
constexpr int kGlobalReferences = 0;
constexpr int kStackArgumentSlots = 1;
constexpr std::size_t kStackCleanupBytes = 4;

// The thirty bytes, transcribed from GhidraMCP /read_memory at 0x00642210:
//
//   56 8b f1 e8 78 ff ff ff f6 44 24 08 01 74 09 56 e8 5b 51 90 00
//   83 c4 04 8b c6 5e c2 04 00
//
// which is exactly the 11 instructions in the evidence listing, at exactly the
// addresses in the evidence listing, consuming all 30 bytes with nothing left
// over. Every displacement in the body was checked against that byte string:
// the CALL rel32 at 0x00642213 is e8 78 ff ff ff, next-instruction 0x00642218
// plus signed -0x88 lands on 0x00642190; the JZ rel8 at 0x0064221d is 74 09,
// next-instruction 0x0064221f plus 9 lands on 0x00642228; the CALL rel32 at
// 0x00642220 is e8 5b 51 90 00, next-instruction 0x00642225 plus 0x90515b lands
// on 0x00f47380; and the TEST at 0x00642218 is f6 44 24 08 01, the /0 byte form
// with displacement 0x8 and immediate 0x1.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x56u,                       // 00642210  PUSH ESI
    0x8bu, 0xf1u,                // 00642211  MOV ESI,ECX
    0xe8u,                       // 00642213  CALL 0x00642190 (opcode)
    0x78u, 0xffu, 0xffu, 0xffu,  //           rel32, resolved by the test
    0xf6u, 0x44u, 0x24u, 0x08u, 0x01u,  // 00642218  TEST byte ptr [ESP+0x8],0x1
    0x74u, 0x09u,                // 0064221d  JZ 0x00642228
    0x56u,                       // 0064221f  PUSH ESI
    0xe8u,                       // 00642220  CALL 0x00f47380 (opcode)
    0x5bu, 0x51u, 0x90u, 0x00u,  //           rel32, resolved by the test
    0x83u, 0xc4u, 0x04u,         // 00642225  ADD ESP,0x4
    0x8bu, 0xc6u,                // 00642228  MOV EAX,ESI
    0x5eu,                       // 0064222a  POP ESI
    0xc2u, 0x04u, 0x00u,         // 0064222b  RET 0x4
};

// The two rel32 displacements, as offsets into kTargetBytes, and the fact that
// each CALL is a five-byte E8 form. The displacement bytes cannot be compared
// against the binary's (they encode addresses in a different image), so the model
// test resolves them instead and requires each to land on the callee the xref
// export names for that callsite.
constexpr std::size_t kCallRel32FirstOffset = 4u;   // after the E8 at byte 3
constexpr std::size_t kCallRel32SecondOffset = 17u;  // after the E8 at byte 16

// The two instructions whose encoding the assembler is free to spell two ways:
// the binary writes MOV ESI,ECX as 8b f1 and MOV EAX,ESI as 8b c6, while the
// GNU assembler prefers 89 ce and 89 f0 for the same operands. Both spellings are
// accepted by the model test, and every other one of the thirty positions is
// compared literally.
constexpr std::size_t kEcxToEsiFirstByte = 1u;
constexpr std::size_t kEcxToEsiSecondByte = 2u;
constexpr std::size_t kEsiToEaxFirstByte = 24u;
constexpr std::size_t kEsiToEaxSecondByte = 25u;

// The word value that tells the harness to push NO second dword. Any other value
// is pushed first, so it lands at the callee's entry_ESP + 0x8 -- which is the
// slot 0x00642218 reads when there is one. Zero is deliberately NOT the
// sentinel: the decoy cases pass 0 and 1 as real decoy words.
constexpr std::uint32_t kNoDecoyWord = 0xffffffffu;

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that
// changing one is a change the model test can catch, and so that a package which
// quietly reverted to the old abstention -- "no convention, no receiver" --
// fails the model test instead of passing.

// The convention the derived record names: __thiscall, with no other candidate.
enum class ConventionVerdict00642210 : int { kThiscall = 0 };

// INFERRED, not OBSERVED and not UNKNOWN. The determination is an inference from
// the vftable-slot rule and the cleanup side; nothing here observed a caller
// dispatching through the table.
enum class ConventionConfidence : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};

// The register the receiver arrives in.
enum class ReceiverRegister00642210 : int { kEcx = 0 };

// Why the derived record believes a receiver is there at all.
enum class ReceiverProvenance00642210 : int { kVftableSlotDispatch = 0 };

// Which side of the stack argument this callee pops.
enum class CleanupSide00642210 : int { kCallee = 0 };

constexpr ConventionVerdict00642210 kDerivedConventionVerdict =
    ConventionVerdict00642210::kThiscall;
constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kInferred;
constexpr int kCandidateConventionCount = 1;

constexpr ReceiverRegister00642210 kDerivedReceiverRegister =
    ReceiverRegister00642210::kEcx;
constexpr ReceiverProvenance00642210 kReceiverProvenance =
    ReceiverProvenance00642210::kVftableSlotDispatch;
constexpr bool kReceiverPresent = true;
constexpr bool kReceiverAbsent = false;
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverHasShape = false;
// 0, because the eleven instructions contain no load and no store through the
// receiver in any register, and so no displacement of the object was ever seen.
constexpr int kReceiverDereferenceCount = 0;
constexpr int kReceiverDistinctOffsets = 0;

// Separately OBSERVED, and independent of the convention: the terminator's own
// form is RET 0x4.
constexpr CleanupSide00642210 kObservedCleanupSide = CleanupSide00642210::kCallee;
constexpr std::size_t kRetImmediateBytes = 4;
constexpr std::size_t kStackArgumentWords = 1;
// The one stack argument is READ (bit 0 of its low byte) and never WRITTEN. It is
// DATA. It is not the receiver and never becomes one.
constexpr bool kStackArgumentRead = true;
constexpr bool kStackArgumentWritten = false;
constexpr bool kOptionWordIsReceiver = false;

// -- the two this-adjusting entry stubs, and the table slot ------------------
//
// Read as bytes from the image; see the note at the top of this file. These are
// facts about two other addresses and about one data table, and they are
// CORROBORATION of the convention, not its source. The body at 0x00642210
// neither adds nor subtracts anything of its own.
constexpr std::uint32_t kThisAdjustingEntryPoints[] = {0x00642170u, 0x00642180u};
constexpr std::uint32_t kThunkThisAdjustments[] = {0x10u, 0x14u};
constexpr int kThisAdjustingEntryPointCount = 2;
// The two tail JMPs themselves, at the addresses the xref export names.
constexpr std::uint32_t kEntryJumpAddresses[] = {0x00642173u, 0x00642183u};

// GhidraMCP /read_memory at 0x013ff640 for 24 bytes gives 0x00641340 at
// 0x013ff644, 0x00642210 at 0x013ff648, 0x00c2e4e0 at 0x013ff64c and 0x00641810
// at 0x013ff650 -- so the address the pack's vtables category names is a table
// whose FIRST slot is this body.
constexpr std::uint32_t kTableBase = 0x013ff648u;
constexpr std::size_t kOwnSlotDisplacement = 0x00u;

// -- the two direct callees, declared as the model's own out-of-line calls -----
//
// Their addresses are in their names, which is the convention the validator reads
// to compare a source's call set against the xref export. Both are entered the
// way the listing enters them: the teardown with the object in ECX and nothing on
// the stack, the disposer with one cdecl dword on the stack.

// 0x00642190. Receiver in ECX, no stack argument, bare RET. Owned by another
// package (pkg-swarm-w1, sporepedia_asset_destroy_00642190); this package reads
// none of its source and asserts only the call shape this body fixes.
extern "C" void PKG_W2_00642210_THISCALL teardown_00642190(Receiver* object);

// 0x00f47380. One cdecl stack argument, no cleanup (the body drops it itself at
// 0x00642225). Unnamed in the image and owned by no package; it is an observer.
extern "C" void dispose_00f47380(void* block);

// -- the reconstruction --------------------------------------------------------

// FUN_00642210 @ 0x00642210, reconstructed.
//
// A naked __thiscall transcription of the target's own thirty bytes. __thiscall
// is what puts the receiver in ECX; the callee-side cleanup of the one stack word
// is carried by this entry's own `retl $4`, which is the machine instruction
// 0x0064222b itself rather than a statement about it.
//
// The parameters are left unnamed on purpose: this function is naked, so it has
// no C++ body to read them in, and a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared types
// describe the shape the machine enters this with -- a receiver pointer in ECX
// and one 32-bit word at entry_ESP+0x4 -- and the model test drives it through a
// call site that builds exactly that shape.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" Receiver* PKG_W2_00642210_NAKED_THISCALL re_00642210(Receiver*,
                                                                 OptionWord);

}  // namespace pkg_w2_00642210
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_W2_00642210_W2_00642210_TYPES_HPP_
