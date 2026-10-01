// PKG-DFW-005C8BC0 -- VA 0x005c8bc0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Opaque boundary types and the transcribed machine record for the body at
// 0x005c8bc0..0x005c8be4.
//
// THE COMPLETE BODY, RE-READ FROM THE IMAGE FOR THIS PACKAGE.
// GhidraMCP /read_memory at 0x005c8bc0 for 39 bytes returns
//
//   8b c1 8b 4c 24 04 81 f9 6e 51 3f ee 74 16 81 f9 d0 9d 00 2f 74 0e
//   33 d2 81 f9 2b ed de 72 0f 95 c2 4a 23 c2 c2 04 00
//
// which decodes instruction for instruction to the twelve lines the evidence pack
// carries (reconstruction/evidence/005c8bc0/evidence.json, category disassembly),
// at exactly the addresses it carries, consuming all 39 bytes with nothing left
// over. abi_derived.parse reports {declared_count 12, unparsed 0, degraded false,
// flow_complete true}, so these twelve are the whole body and not a slice.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// The derived ABI record for this target (evidence pack, category abi_derived)
// states, field for field, at the time this header was written:
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
// in the two steps the record itself separates:
//
//   R1-VFT  (INFERRED) "ECX carries the receiver". 0x005c8bc0 is word 7 (slot 7)
//                      of the vptr-backed vftable the record bases at 0x013f82fc,
//                      so it is a virtual member of some class, and the body READS
//                      the register such a dispatch delivers -- `MOV EAX,ECX` at
//                      0x005c8bc0 is one incoming-ECX read. The rule
//                      discriminates that from the COM / __stdcall interface form,
//                      which takes its receiver from the first popped stack word
//                      and never reads its incoming ECX. The same step records
//                      cleanup_side = callee, which is what makes the two forms
//                      distinguishable.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             table 0x013f82fc, slot_index 7, cleanup_side callee}
//
//   C6B     (INFERRED) "the calling convention is __thiscall". The callee pops
//                      its own stack word, which rules out cdecl and fastcall,
//                      and the receiver arrives in ECX.
//
// INFERRED, not OBSERVED: nothing in this repository has watched a caller
// dispatch through the table. What WAS observed is the cleanup (`RET 0x4` is in
// the bytes above) and the register-to-register move; the convention and the
// receiver are inferred from those together with the slot membership. Every value
// is carried below as DATA (kDerivedConventionVerdict,
// kDerivedConventionConfidence, kCandidateConventionCount,
// kConventionAmbiguityCount, kDerivedReceiverRegister, kReceiverProvenance,
// kObservedCleanupSide, kReceiverPresent, kReceiverBoundsOnly,
// kReceiverHasShape, kReceiverDereferenceCount, kReceiverDistinctOffsets) so
// that a package which quietly reverted to the old abstention -- "no convention,
// no receiver" -- fails the model test instead of passing.
//
// THE OLD ABSTENTION, AND WHY IT IS GONE.
// A previous revision of this header reported that "the machine-derived ABI record
// for this target abstains from naming a receiver at all
// (receiver_not_determinable: ecx_read_without_deref)" and that "the record itself
// does not choose: it lists __stdcall and __thiscall as candidates with confidence
// UNKNOWN and verdict ABI_UNKNOWN". That is no longer what the record says. The
// reason it used to give -- the body reads ECX without dereferencing it, so a
// receiver cannot be told from an ordinary register argument -- is now handled by
// R1-VFT, which takes the receiver from the vftable-slot membership instead of
// from the body's own dereference count. The record states
// receiver.reason = ecx_read_without_deref and STILL determines
// receiver.present = true, because the two are different questions: the reason
// field records why the body alone could not settle it, and the rule records what
// settles it anyway.
//
// WHAT THE CONVENTION DOES NOT SETTLE. A convention is not an identity.
// __thiscall says the receiver arrives in ECX. It does not say what the receiver
// IS. This body copies ECX into EAX at 0x005c8bc0, overwrites ECX with the
// caller's stack word at 0x005c8bc2 and never reads ECX again; there is no load
// and no store through the receiver in any register, anywhere in the twelve
// instructions. So this package names:
//
//   * no owning class, and no vtable identity. R1-VFT names ONE table base
//     (0x013f82fc) and the slot's own index (7) as the evidence for the receiver;
//     a slot is not a class, and this binary carries no MSVC RTTI and no
//     vtable-detection pass has ever run on it.
//   * no receiver type, shape, object size, vtable-pointer offset, field, member
//     or layout. The record's own `bounds_only true` with an empty `offsets` list
//     is the correct reading here and not a gap in the pack: the body addresses no
//     byte of the receiver, so no displacement of the object was ever seen. NO
//     FIELD OFFSET IS CLAIMED IN EITHER DIRECTION.
//   * nothing about the identity of the receiver -- whether the incoming ECX
//     points at the head of an object or at an interior sub-object is invisible
//     from these twelve instructions, which neither add nor subtract anything.
//
// THE ONE STACK WORD IS DATA, AND IT IS NOT THE RECEIVER.
// The word at entry_ESP+0x4 is read once, at 0x005c8bc2, into ECX -- overwriting
// the register that had just been copied into EAX -- and is then compared, three
// times, against three immediate values. It is never dereferenced, never written,
// never handed anywhere else, and never becomes the value in EAX. It is an
// integral 32-bit comparison value. It is NOT a receiver (that is the ECX input),
// NOT a pointer (nothing in the body treats it as an address), NOT a field (it is
// the caller's own pushed slot, and the body pushes nothing) and NOT a nameable
// identifier (see the third-value note below). The model test drives the two
// independently and asserts that a compared value sitting in ECX with a non-member
// on the stack returns zero, so a reconstruction which folded one into the other
// would be refuted rather than passed.
//
// The three literals are named by VALUE only. A sibling candidate
// (reconstruction/staging/pkg-palette-classid-slot7/) reports a value match
// against the Spore-ModAPI SDK symbol table's ENUM_ENTRY list that would name them
// Object, UTFWin::IWinProc and Palettes::PalettePageUI. That SDK clone is not
// present on this machine, so the match could not be re-derived here and is NOT
// relied upon: no constant in this package carries an SDK name, and the model is
// stated in terms of the three numbers and nothing else.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-005c8bc0 requires an x86-32 target"
#endif

// The convention is spelled once, here, and the reconstructed entry names the
// macro. GCC and clang accept only the attribute form and reject the bare MSVC
// keyword, so the attribute is the portable spelling and the keyword is kept for
// MSVC. Either way the token `thiscall` is carried once per macro, which is what
// the validator's `_convention_defines` resolves.
//
// One consequence is worth stating before an integrator adds -Wpedantic to a build
// gate. C++ has no thiscall for a free function, so spelling this body's shape in
// C++ means putting the attribute on one, and GCC reports exactly that -- "the
// 'thiscall' attribute is used for non-class method" -- under -Wpedantic. The
// warning is a true statement about the modelling compromise and is left to stand
// rather than suppressed: dropping the attribute would put the first word on the
// stack, which 0x005c8bc0 contradicts, and __stdcall would put it in EAX, which
// this body does not read. The required build for this package
// (-Wall -Wextra -Werror) is clean with no diagnostics.
#if defined(_MSC_VER)
#define PKG_DFW_005C8BC0_THISCALL __thiscall
#define PKG_DFW_005C8BC0_CDECL __cdecl
#else
#define PKG_DFW_005C8BC0_THISCALL __attribute__((thiscall))
#define PKG_DFW_005C8BC0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_005c8bc0 {

// -- identity ----------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x005c8bc0.
inline constexpr std::uint32_t kTargetVa = 0x005c8bc0u;
inline constexpr std::uint32_t kBodyFirstByte = 0x005c8bc0u;
inline constexpr std::uint32_t kBodyLastByte = 0x005c8be4u;
inline constexpr std::uint32_t kBodyEndExclusive = 0x005c8be5u;

// -- boundary types ----------------------------------------------------------

// A 32-bit machine word. This target reads one word and returns one word.
using Word = std::uint32_t;

// The machine ABI record's own name for the word this body leaves in EAX:
// return_semantics "unclassified_in_EAX", return_register EAX,
// return_width_bytes 4, and abi_derived.return records register EAX,
// register_class "aggregate_unknown", type null. The record declines to say what
// the word means, and so does this alias -- it fixes the WIDTH, which the listing
// proves, and claims nothing about the type, the class or the meaning of what
// comes back.
//
// The live decompiler renders the same return as `bool` and tests only the low
// byte of ECX, which is a narrowing the listing does not support: on both
// pass-through paths the body returns all four bytes of the register it was
// given, unmodified. The bool reading is recorded as an open question in the
// sidecar and is not what this model declares.
using unclassified_in_EAX = Word;

// The three values the body compares the single incoming stack word against.
// Named by value, in the order the listing compares them. No SDK name, class
// name or semantic gloss is attached to any of them; see the header comment above
// for why. The model test does NOT import these: it decodes them out of
// kTargetBytes below, so an edit to either one is caught.
inline constexpr Word kFirstComparedValue = 0xee3f516eU;   // 0x005c8bc6
inline constexpr Word kSecondComparedValue = 0x2f009dd0U;  // 0x005c8bce
inline constexpr Word kThirdComparedValue = 0x72deed2bU;   // 0x005c8bd8

// -- extent, restated from the twelve instructions ----------------------------

constexpr int kInstructionCount = 12;
constexpr std::size_t kBodySpanBytes = 39;
constexpr int kBasicBlockCount = 3;  // the head, the two JZ targets and the mask block
constexpr int kConditionalBranches = 2;
constexpr int kDirectCalleeCount = 0;
constexpr int kIndirectTransfers = 0;
constexpr int kGlobalReferences = 0;
constexpr int kStackArgumentSlots = 1;
constexpr std::size_t kStackCleanupBytes = 4;

// The target's own thirty-nine bytes, transcribed from GhidraMCP /read_memory at
// 0x005c8bc0:
//
//   8b c1 8b 4c 24 04 81 f9 6e 51 3f ee 74 16 81 f9 d0 9d 00 2f 74 0e
//   33 d2 81 f9 2b ed de 72 0f 95 c2 4a 23 c2 c2 04 00
//
// The model test compares this array against the binary itself where it can, and
// -- more importantly -- DECODES the three compared immediates and the RET
// immediate out of it at run time and drives the model with the decoded values.
// That is a cross-check rather than a tautology: the bytes come from the image
// and the model's behaviour is then held to them, so neither side can be edited
// alone to make the other agree.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x8bu, 0xc1u,                          // 005c8bc0  MOV EAX,ECX
    0x8bu, 0x4cu, 0x24u, 0x04u,            // 005c8bc2  MOV ECX,[ESP+0x4]
    0x81u, 0xf9u, 0x6eu, 0x51u, 0x3fu, 0xeeu,  // 005c8bc6  CMP ECX,0xee3f516e
    0x74u, 0x16u,                          // 005c8bcc  JZ +0x16 -> 0x005c8be4
    0x81u, 0xf9u, 0xd0u, 0x9du, 0x00u, 0x2fu,  // 005c8bce  CMP ECX,0x2f009dd0
    0x74u, 0x0eu,                          // 005c8bd4  JZ +0x0e -> 0x005c8be4
    0x33u, 0xd2u,                          // 005c8bd6  XOR EDX,EDX
    0x81u, 0xf9u, 0x2bu, 0xedu, 0xdeu, 0x72u,  // 005c8bd8  CMP ECX,0x72deed2b
    0x0fu, 0x95u, 0xc2u,                   // 005c8bde  SETNZ DL
    0x4au,                                 // 005c8be1  DEC EDX
    0x23u, 0xc2u,                          // 005c8be2  AND EAX,EDX (full 32-bit)
    0xc2u, 0x04u, 0x00u,                   // 005c8be4  RET 0x4
};

// The byte offsets inside kTargetBytes that the model test decodes rather than
// restates. Each is the position the instruction above occupies, so a test that
// reads kTargetBytes[8..11] and kTargetBytes[16..19] and kTargetBytes[26..29]
// is reading the three CMP immediates straight out of the binary's own bytes.
constexpr std::size_t kFirstCmpImmOffset = 8;   // 005c8bc6 81 f9 <imm32>
constexpr std::size_t kSecondCmpImmOffset = 16; // 005c8bce 81 f9 <imm32>
constexpr std::size_t kThirdCmpImmOffset = 26;  // 005c8bd8 81 f9 <imm32>
constexpr std::size_t kRetOpcodeOffset = 36;    // 005c8be4 c2 <imm16>
constexpr std::size_t kFirstJzRelOffset = 13;   // 005c8bcc 74 <rel8>
constexpr std::size_t kSecondJzRelOffset = 21;  // 005c8bd4 74 <rel8>
constexpr std::size_t kAndOpcodeOffset = 34;    // 005c8be2 23 c2

// The byte that follows the body. /read_memory returns it as part of the same
// 48-byte read; it is recorded so the model test can check the transcription ends
// where the body does rather than swallowing the padding.
constexpr std::uint8_t kInterFunctionPad = 0xCCu;

// -- the vftable membership R1-VFT reasons from ------------------------------
//
// Read as data, not as a class. /read_memory at 0x013f82fc for 32 bytes gives
// 0x005c9060, 0x00c6fb40, 0x0076ded0, 0x004535b0 as words 0..3, and word 7 -- at
// 0x013f82fc + 28 = 0x013f8318 -- is 0x005c8bc0. Word 0 is an MSVC this-adjusting
// thunk (83 e9 04 / e9 08 00 00 00 at 0x005c9060: SUB ECX,0x4 then JMP), which is
// what makes the table a vtable rather than a plain array of function pointers.
// No owning class, no slot member name and no vtable identity is claimed.
constexpr std::uint32_t kTableBase = 0x013f82fcu;
constexpr std::size_t kOwnSlotDisplacement = 0x1cu;  // 7 * 4
constexpr std::size_t kOwnSlotIndex = 7u;
constexpr int kTableWordCount = 8;
constexpr std::uint32_t kFirstTableWord = 0x005c9060u;
constexpr std::uint32_t kThisAdjustingThunk = 0x005c9060u;
constexpr std::uint32_t kThisAdjustment = 0x04u;

// -- the machine-derived ABI, carried as DATA --------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category and from nothing else. They are data rather than prose so that changing
// one is a change the model test can catch, and so that a package which quietly
// reverted to the old abstention -- "no convention, no receiver" -- fails the model
// test instead of passing.

// The convention the derived record names: __thiscall, with no other candidate.
enum class ConventionVerdict005c8bc0 : int { kThiscall = 0 };

// INFERRED, not OBSERVED and not UNKNOWN. The determination is an inference from
// the vftable-slot rule and the cleanup side; nothing here observed a caller
// dispatching through the table.
enum class ConventionConfidence005c8bc0 : int {
  kUnknown = 0,
  kInferred = 1,
  kObserved = 2
};

// The register the receiver arrives in.
enum class ReceiverRegister005c8bc0 : int { kEcx = 0 };

// Why the derived record believes a receiver is there at all.
enum class ReceiverProvenance005c8bc0 : int { kVftableSlotDispatch = 0 };

// Which side of the stack argument this callee pops.
enum class CleanupSide005c8bc0 : int { kCallee = 0 };

// The machine's own recorded reason that the BODY alone could not settle the
// receiver. It is kept because it is true, and because it explains why R1-VFT
// exists: the record reads ECX and never dereferences it, so the body on its own
// cannot tell a receiver from an ordinary register argument. The record
// nevertheless determines receiver.present = true, from the slot membership.
constexpr bool kReceiverReasonIsEcxReadWithoutDeref = true;

constexpr ConventionVerdict005c8bc0 kDerivedConventionVerdict =
    ConventionVerdict005c8bc0::kThiscall;
constexpr ConventionConfidence005c8bc0 kDerivedConventionConfidence =
    ConventionConfidence005c8bc0::kInferred;
constexpr int kCandidateConventionCount = 1;
constexpr int kConventionAmbiguityCount = 0;

constexpr ReceiverRegister005c8bc0 kDerivedReceiverRegister =
    ReceiverRegister005c8bc0::kEcx;
constexpr ReceiverProvenance005c8bc0 kReceiverProvenance =
    ReceiverProvenance005c8bc0::kVftableSlotDispatch;
constexpr bool kReceiverPresent = true;
constexpr bool kReceiverAbsent = false;
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverHasShape = false;
// 0, because the twelve instructions contain no load and no store through the
// receiver in any register, and so no displacement of the object was ever seen.
constexpr int kReceiverDereferenceCount = 0;
constexpr int kReceiverDistinctOffsets = 0;
// The honest form of the two facts above: the body shows no offset, so this
// package claims none -- neither a field at some offset nor the object's being
// flat. `false` here means "not claimed", NOT "there is no field".
constexpr bool kReceiverFieldOffsetClaimed = false;

// Separately OBSERVED, and independent of the convention: the terminator's own
// form is RET 0x4.
constexpr CleanupSide005c8bc0 kObservedCleanupSide = CleanupSide005c8bc0::kCallee;
constexpr std::size_t kRetImmediateBytes = 4;
constexpr std::size_t kStackArgumentWords = 1;
// The one stack word is READ (three CMP against it) and never WRITTEN. It is
// DATA: an integral comparison value. It is not the receiver, not a pointer and
// not a field.
constexpr bool kStackArgumentRead = true;
constexpr bool kStackArgumentWritten = false;
constexpr bool kStackArgumentIsReceiver = false;
constexpr bool kStackArgumentTreatedAsPointer = false;
// The register the answer is returned in, and its width: 4 bytes, which the
// listing proves on every path to the single reachable RET.
constexpr int kReturnRegisterId = 0;  // 0 is EAX
constexpr std::size_t kReturnWidthBytes = 4;

// -- the reconstruction -------------------------------------------------------

// 0x005c8bc0, reconstructed. A __thiscall entry with one 32-bit stack word.
//
//   receiver_word  the word the caller left in ECX. The body copies it whole into
//                  the return register at 0x005c8bc0 and never dereferences it, so
//                  it is carried as a word and is never converted to a pointer.
//                  Any value is as legal an input as any other; the body has no
//                  notion of one being special.
//   queried_value  the one four-byte word at entry_ESP+0x4, read into ECX at
//                  0x005c8bc2 and compared against the three values above. It is
//                  an integral comparison value, not a pointer and not a receiver.
//
// The return is the receiver word when queried_value equals any of the three, and
// zero otherwise. That is one membership test written three times; the three
// guards are not three different behaviours, and the SETNZ/DEC mask is not an
// inversion of the two JZ guards.
extern "C" unclassified_in_EAX PKG_DFW_005C8BC0_THISCALL
dfw_005c8bc0_load(Word receiver_word, Word queried_value);

}  // namespace openspore::reconstruction::pkg_dfw_005c8bc0
