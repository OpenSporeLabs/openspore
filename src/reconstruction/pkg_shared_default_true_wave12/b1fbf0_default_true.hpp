// PKG-SHARED-DEFAULT-TRUE-WAVE12 -- VA 0x00b1fbf0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, x86-32)
//
// THE COMPLETE BODY. Three bytes, two instructions, no callee, no memory
// operand of any kind, no branch, no indirect transfer:
//
//   00b1fbf0  b0 01   MOV AL,0x1
//   00b1fbf2  c3      RET
//
// GhidraMCP /read_memory at 0x00b1fbf0 returns `b001c3cccccccccc` for the first
// twelve bytes: the three body bytes, then nine 0xCC inter-function pad bytes.
// Nothing in this package reaches past 0x00b1fbf2.
//
// WHAT THE BYTES DECODE TO, FIELD BY FIELD.
//
//   b0        opcode B0 = MOV r8, imm8. One opcode byte, a one-byte register
//             field that the ModRM byte this instruction does NOT have, and a
//             one-byte immediate. The register field of B0 is fixed at AL: the
//             encoding has no ModRM byte at all, so there is no operand-sizing
//             freedom in it and no memory form.
//   01        the immediate, the only value the body ever produces.
//   c3        opcode C3 = RET near, with NO immediate. That absence is the whole
//             of the stack accounting: a RET with no imm16 pops the return
//             address and nothing else, so the callee pops zero bytes and the
//             caller owns all cleanup.
//
// So the body is a leaf constant: it reads no register, no memory and no stack
// word, and its single effect is to place the byte 0x01 in AL.
//
// THE CALLING CONVENTION IS DETERMINED BY THE MACHINE, NOT CHOSEN HERE.
//
// The derived ABI record for this target (reconstruction/evidence/00b1fbf0/
// evidence.json, category abi_derived) states, field for field:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : INFERRED
//   conventions.candidate_conventions : ["__thiscall", "__fastcall"]
//   conventions.ambiguities           : []
//   verdict                           : ABI_INFERRED   (conflicts: [] empty)
//
//   receiver.register        : ECX
//   receiver.provenance      : vftable_slot
//   receiver.confidence      : OBSERVED
//   receiver.present         : false
//   receiver.bounds_only     : true
//   receiver.shape           : null
//   receiver.distinct_offsets : 0
//   receiver.offsets         : []
//   receiver.max_offset      : null
//   receiver.written_through  : 0
//
//   cleanup.bytes    : 0      side: caller   confidence: INFERRED
//   cleanup.evidence : "ret with no immediate, no stack reads"
//
//   return.register       : EAX
//   return.register_class : integral
//   return.type           : null
//
// THE RULE THAT NAMES THE CONVENTION IS V1-VFT, AND IT IS THE ONLY ONE THAT
// DOES. The record's inference list is exactly
// ['C5', 'R2', 'V1-VFT', 'S2', 'RT1', 'RT2'], and only one of those six carries
// a calling-convention claim. It reads, verbatim from the record:
//
//   V1-VFT (INFERRED) "calling convention is __thiscall: 0x00b1fbf0 is slot 3
//   of the vptr-backed vftable at 0x013f57f8, so it is a virtual member of some
//   class; the callee pops nothing and no stack word is read as an argument, so
//   the receiver is in a register, and ECX is the only one that carries one"
//   value: {cleanup_side "caller", membership_count 443,
//           receiver_provenance "vftable_slot", receiver_register "ECX",
//           slot_index 3, table "0x013f57f8"}
//
// There is no C7 or C6B inference on this target, and none is claimed. The two
// conventions the record keeps open are __thiscall and __fastcall; see the
// UNRESOLVED list at the bottom for what that leaves open.
//
// R2 IS A SEPARATE OBSERVATION AND IT POINTS THE OTHER WAY, AND BOTH ARE CARRIED.
//   R2 (OBSERVED) "ECX is never read in any form, so there is no register
//   receiver", value {present: false}.
//
// `receiver.present` is therefore FALSE in the record, and that is not a
// contradiction of V1-VFT: V1-VFT determines the PORT (a register that carries a
// receiver on entry, and ECX is the only one that can) and R2 observes the
// BODY (which never reads that register). The honest statement is "entered as a
// __thiscall member whose body ignores its receiver", and both halves of that
// are in the data block below. This package does not claim the body reads a
// receiver, and does not claim it does not exist on the port.
//
// WHAT IS OBSERVED INSTEAD, ON THE CALLER SIDE, AND IT IS THE STRONGEST
// RECEIPT EVIDENCE IN THE PACKAGE. Six direct call sites hand this function a
// NON-NULL, JUST-LOADED ECX with no instruction in between that could clobber
// it, so the register is not merely a convention's carrier in the abstract --
// a concrete value is demonstrably in it at the transfer. Each is read straight
// off the image (GhidraMCP /disassemble_bytes):
//
//   0098cc74  8b f1        MOV ESI,ECX     ; the caller's own receiver
//   0098cc76  80be10020000 CMP byte ptr [ESI+0x210],0x0
//   0098cc7d  756d        JNZ 0x0098ccec
//   0098cc7f  e86c2f1900   CALL 0x00b1fbf0 ; ECX untouched since 0098cc74
//
//   0096a671  8bd9        MOV EBX,ECX
//   0096a673  e878551b00   CALL 0x00b1fbf0
//
//   0096b3a1  8bf1        MOV ESI,ECX
//   0096b3a3  e848481b00   CALL 0x00b1fbf0
//
//   00a43058  8b8e80bc1500 MOV ECX,dword ptr [ESI + 0x15bc80]
//   00a4305e  85c9        TEST ECX,ECX
//   00a43060  7420        JZ 0x00a43082
//   00a43062  e889cb0d00   CALL 0x00b1fbf0 ; the JZ proves ECX is non-null here
//
//   0082c276  8d4c2414     LEA ECX,[ESP + 0x14]
//   0082c27a  e871392f00   CALL 0x00b1fbf0
//
//   00ee8bf1  8b4e10       MOV ECX,dword ptr [ESI + 0x10]
//   00ee8bf4  8b11        MOV EDX,dword ptr [ECX]
//   00ee8bf6  8b4210       MOV EAX,dword ptr [EDX + 0x10]
//   00ee8bf9  ffd0        CALL EAX        ; the vtable slot itself
//
// 0x00ee8bf6 is the dispatch this package's V1-VFT reason rests on, read
// directly: the address is the word at vtable+0x10 of the object ECX points at.
// The table base the record names, 0x013f57f8, is corroborated by reading the
// word back out of the image: 0x013f57f8 + 4*3 = 0x013f5804, and /read_memory
// there returns `f0fbb100`, i.e. 0x00b1fbf0. The model test re-derives that
// sum from the two constants and checks the product against a literal.
//
// TWO SITES DELIBERATELY NOT COUNTED AS RECEIPT EVIDENCE. At 0x00e7d68e and
// 0x00e7d6bf (inside App::cCellModeStrategy::OnMouseWheel) and at 0x00e81134,
// ECX is not provably intact at the transfer: in the first two there is a CALL
// to 0x00697b40 in between that may clobber it, and in the third ECX is loaded
// into EBX at 0x00e81124 and never reloaded. They are recorded as call sites
// and are NOT used as evidence for the receiver.
//
// A TAIL TRANSFER, NOT A CALL, AT 0x007f53fe. GhidraMCP /disassemble_bytes at
// 0x007f53f0 gives `e9eda73200` = JMP 0x00b1fbf0, so the xref export's
// "direct-call" classification of that row is wrong and is corrected here. Two
// bytes later the same function carries an inlined copy of the identical body:
//
//   007f53fe  e9eda73200   JMP  0x00b1fbf0
//   007f5403  b001         MOV  AL,0x1
//   007f5405  5e           POP  ESI
//   007f5406  c3           RET
//
// A shipped default the compiler can inline but sometimes also emits out of
// line is exactly the shape that produces both, and it is corroboration for
// R2 and for the constant nature of the body.
//
// THE RETURN IS A BYTE, NOT A DWORD, AND THE MODEL TEST MEASURES IT.
//
// The machine return record says only `register EAX`, `register_class
// integral`, `type null` -- it names no width and no C type. The width is
// established here from the instruction, not assumed: opcode B0 is MOV r8,imm8
// and its register field is fixed at AL, so one byte of EAX is written and bits
// 8..31 are whatever the caller left there. Every consumer inspected agrees:
// 0x0098cc84, 0x0096a678, 0x0096b3a8, 0x00e7d693, 0x00e7d6c4, 0x00ee8bfb all
// test the AL byte and none reads the full dword, and 0x00e81139 goes further
// and compares it against the immediate 1 (`3c01`, CMP AL,0x1).
//
// That last observation is what makes the byte claim falsifiable rather than
// decorative, and it is why the model test measures the FULL EAX across a call
// with a poisoned upper half rather than only checking the C++ return value: a
// reconstruction that materialised `mov eax,1` instead would agree on every
// byte-level consumer test and still be a different machine body. Case D of the
// test kills it.
//
// NOT CLAIMED, AND WHY.
//
//   * No class, and no vtable identity. V1-VFT names ONE table base and ONE
//     slot index as the evidence for the receiver. A slot is not a class, and
//     this binary carries no MSVC RTTI (AGENTS.md, and every ghidra_function
//     record in this repository says so). The same address sits at four
//     different slot offsets in three different tables, which one named method
//     could not do; the four offsets are listed with the constants below.
//   * NO FIELD OFFSET IS CLAIMED IN EITHER DIRECTION. The record enumerates
//     zero (`distinct_offsets 0`, `offsets []`, `max_offset null`) and the body
//     contains no memory operand through any register, so there is nothing to
//     ground and nothing to enumerate. `kReceiverFieldOffsetClaimed` is false
//     and means "not claimed", NOT "there is no field".
//   * No receiver type, shape, object size, vptr offset, member or layout. The
//     receiver is declared and left UNDEFINED (`struct Receiver;`). Six call
//     sites hand this function six different objects and the body reads none of
//     them, so the evidence cannot distinguish them and does not try.
//   * Not __fastcall. The record keeps it as a live candidate and this package
//     does not close it; see UNRESOLVED.
//   * Not the SDK method name. Spore/App/IGameMode.h declares
//     `virtual bool func0Ch() = 0;` and DefaultGameMode defines it as
//     `return true;`, which is a plausible match, and the pkg-game-input-wave8
//     record carries a +8 shift argument that would place this address at that
//     slot of the 0x01485550 table. That correspondence is a CANDIDATE for one
//     table and is deliberately not asserted: the same address occupies four
//     distinct offsets across three tables, which is what identical COMDAT
//     folding produces, and a shared address is not an identity.
#ifndef RECONSTRUCTION_STAGING_PKG_SHARED_DEFAULT_TRUE_WAVE12_B1FBF0_DEFAULT_TRUE_HPP_
#define RECONSTRUCTION_STAGING_PKG_SHARED_DEFAULT_TRUE_WAVE12_B1FBF0_DEFAULT_TRUE_HPP_

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-shared-default-true-wave12 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "pkg-shared-default-true-wave12 requires 32-bit pointers");

// The convention is spelled once, here, and the reconstructed entry names the
// macro. GCC rejects the bare MSVC keyword in the attribute position (verified:
// g++ 16.2.1 -m32 fails on `std::uint8_t __thiscall f(...)` with "expected
// initializer before 'f'"), so the attribute form is the portable spelling and
// the keyword form is kept for MSVC. Either way the token `thiscall` is carried
// once per macro, which is what the validator's convention resolution follows.
#if defined(_MSC_VER)
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_THISCALL __thiscall
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_THISCALL __attribute__((thiscall))
#define PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

// The receiver of the slot(s) that resolve to 0x00b1fbf0. Deliberately
// incomplete: the body never dereferences it, so there is nothing to describe
// and every field would be invention.
struct Receiver;

namespace openspore {
namespace reconstruction {
namespace pkg_shared_default_true_wave12 {

// The derived record's own enumerations, restated so the test can check them
// against literals it writes independently. The order is the record's.

enum ConventionVerdict00b1fbf0 {
  kConvThiscall00b1fbf0 = 0,
  kConvFastcall00b1fbf0 = 1
};

enum ConventionConfidence00b1fbf0 {
  kConfidenceObserved00b1fbf0 = 0,
  kConfidenceInferred00b1fbf0 = 1,
  kConfidenceApproximation00b1fbf0 = 2
};

enum ReceiverRegister00b1fbf0 {
  kRegisterEax00b1fbf0 = 0,
  kRegisterEcx00b1fbf0 = 1
};

// The record spells this one `vftable_slot`, not the `vftable_slot_dispatch`
// some sibling packages carry. Kept as written.
enum ReceiverProvenance00b1fbf0 {
  kProvenanceVftableSlot00b1fbf0 = 0
};

enum CleanupSide00b1fbf0 {
  kCleanupCaller00b1fbf0 = 0,
  kCleanupCallee00b1fbf0 = 1
};

enum ReturnClass00b1fbf0 {
  kReturnIntegral00b1fbf0 = 0
};

// -- the determination, from abi_derived.value.conventions -------------------

constexpr ConventionVerdict00b1fbf0 kDerivedConventionVerdict =
    kConvThiscall00b1fbf0;
constexpr ConventionConfidence00b1fbf0 kDerivedConventionConfidence =
    kConfidenceInferred00b1fbf0;
// TWO, not one. The record keeps __fastcall open; this package does not close
// it and the count is what keeps that honest.
constexpr int kCandidateConventionCount = 2;
constexpr int kConventionAmbiguityCount = 0;

// -- the receiver, from abi_derived.value.receiver ---------------------------

constexpr ReceiverRegister00b1fbf0 kReceiverRegister = kRegisterEcx00b1fbf0;
constexpr ReceiverProvenance00b1fbf0 kReceiverProvenance =
    kProvenanceVftableSlot00b1fbf0;
// FALSE, and this is the load-bearing fact about the body: it never reads the
// register V1-VFT says carries the receiver. V1-VFT determines the port; this
// is what the two instructions do.
constexpr bool kReceiverReadByBody = false;
constexpr bool kReceiverPresent = false;
constexpr bool kReceiverBoundsOnly = true;
constexpr bool kReceiverHasShape = false;
constexpr int kReceiverDereferenceCount = 0;
constexpr int kReceiverDistinctOffsets = 0;
constexpr int kReceiverWrittenThrough = 0;
// "not claimed", in EITHER direction. The body shows no offset, so neither a
// field at some offset nor the object's being flat is asserted.
constexpr bool kReceiverFieldOffsetClaimed = false;

// -- the stack, from abi_derived.value.cleanup and the body's RET -----------

// INFERRED, not OBSERVED: a bare RET is compatible with caller cleanup and,
// for a zero-argument body, is also what a callee-cleanup convention with
// nothing to pop would look like. There is no immediate to read a count from.
constexpr CleanupSide00b1fbf0 kObservedCleanupSide = kCleanupCaller00b1fbf0;
constexpr ConventionConfidence00b1fbf0 kCleanupConfidence =
    kConfidenceInferred00b1fbf0;
constexpr std::size_t kStackCleanupBytes = 0;
// A RET with no imm16. Zero is a measurement of the instruction's length, not
// an absence of a value.
constexpr std::size_t kRetImmediateBytes = 0;
constexpr int kStackArgumentSlots = 0;

// -- the return, from the instruction and the machine return record ----------

// The machine record names EAX and the class `integral`, and NO type and NO
// width. The width below is derived from the opcode, not copied from a record.
constexpr int kReturnRegisterId = 0;  // ModRM reg field 000 is EAX
constexpr ReturnClass00b1fbf0 kReturnRegisterClass = kReturnIntegral00b1fbf0;
constexpr std::size_t kReturnWidthBytes = 1;
constexpr bool kMachineRecordNamedReturnType = false;

// -- the extent, from the listing and the live read -------------------------

constexpr std::uint32_t kTargetVa = 0x00b1fbf0u;
constexpr std::uint32_t kBodyFirstByte = 0x00b1fbf0u;
constexpr std::uint32_t kBodyLastByte = 0x00b1fbf2u;
// Where the body ends and the inter-function pad begins.
constexpr std::uint32_t kBodyEndExclusive = 0x00b1fbf3u;
constexpr std::size_t kBodySpanBytes = 3;
constexpr std::size_t kInstructionCount = 2;
constexpr std::size_t kBasicBlockCount = 1;
constexpr std::size_t kConditionalBranches = 0;
constexpr std::size_t kDirectCalleeCount = 0;
constexpr std::size_t kIndirectTransfers = 0;
constexpr std::size_t kGlobalReferences = 0;
// The parse record's own numbers, so the "fully consumed" claim in the
// CONSTANTS check is pinned here too.
constexpr std::size_t kParseDeclaredCount = 2;
constexpr std::size_t kParseUnparsedCount = 0;
constexpr bool kParseDegraded = false;

// The image, as literals. Deliberately NOT shared with the model test: two
// independent transcriptions of the same three bytes, compared position by
// position, so neither can drift silently.
constexpr std::uint8_t kTargetBytes[3] = {0xb0u, 0x01u, 0xc3u};
// /read_memory at 0x00b1fbf3: cc cc cc ...
constexpr std::uint8_t kInterFunctionPad = 0xCCu;

// -- the vtable membership V1-VFT reasons from ------------------------------
//
// 0x013f57f8 + 4*3 = 0x013f5804, and the word the image holds there is
// 0x00b1fbf0. Read back, not inferred. Membership is not identity: the same
// address occupies four distinct offsets in three distinct tables.
constexpr std::uint32_t kVftableBase = 0x013f57f8u;
constexpr int kVftableSlotIndex = 3;
constexpr int kVftableMembershipCount = 443;
// The word the image holds at kVftableBase + 4*kVftableSlotIndex.
constexpr std::uint32_t kVftableSlotWord = 0x00b1fbf0u;
// The three tables and the four offsets, each read back out of the image.
constexpr std::uint32_t kSlotTable0 = 0x013f57f8u;
constexpr std::size_t kSlotOffset0 = 0x0cu;
constexpr std::uint32_t kSlotTable1 = 0x013fc06cu;
constexpr std::size_t kSlotOffset1 = 0x10u;
constexpr std::size_t kSlotOffset2 = 0x14u;
constexpr std::uint32_t kSlotTable2 = 0x01485550u;
constexpr std::size_t kSlotOffset3 = 0x14u;
constexpr std::size_t kSlotOffset4 = 0x60u;
constexpr int kDistinctSlotOffsetCount = 4;

// -- the caller-side receipts ----------------------------------------------
//
// Six sites where ECX holds a value demonstrably live at the transfer. See the
// disassembly block in the header comment; the offsets are reproduced here so
// the test can re-derive the address arithmetic.
constexpr std::uint32_t kEcxReceiptSite0 = 0x0098cc74u;  // MOV ESI,ECX
constexpr std::uint32_t kEcxReceiptCall0 = 0x0098cc7fu;
constexpr std::uint32_t kEcxReceiptSite1 = 0x0096a671u;  // MOV EBX,ECX
constexpr std::uint32_t kEcxReceiptCall1 = 0x0096a673u;
constexpr std::uint32_t kEcxReceiptSite2 = 0x0096b3a1u;  // MOV ESI,ECX
constexpr std::uint32_t kEcxReceiptCall2 = 0x0096b3a3u;
constexpr std::uint32_t kEcxReceiptSite3 = 0x00a43058u;  // MOV ECX,[ESI+..]
constexpr std::uint32_t kEcxReceiptCall3 = 0x00a43062u;
constexpr std::uint32_t kEcxReceiptSite4 = 0x0082c276u;  // LEA ECX,[ESP+0x14]
constexpr std::uint32_t kEcxReceiptCall4 = 0x0082c27au;
constexpr std::uint32_t kEcxReceiptSite5 = 0x00ee8bf1u;  // the vtable dispatch
constexpr std::uint32_t kEcxReceiptCall5 = 0x00ee8bf9u;
constexpr std::size_t kEcxReceiptSiteCount = 6;

// The tail transfer, corrected: the export calls it a direct-call row and the
// instruction is a JMP.
constexpr std::uint32_t kTailTransferInstruction = 0x007f53feu;
constexpr std::uint32_t kTailTransferTarget = 0x00b1fbf0u;
// The inlined duplicate of the same body two bytes later in the same function.
constexpr std::uint32_t kInlinedDuplicateAddress = 0x007f5403u;
// The one consumer that compares the answer against the immediate 1 rather
// than testing it for non-zero: CMP AL,0x1 at 0x00e81139.
constexpr std::uint32_t kByteCompareInstruction = 0x00e81134u;
constexpr std::uint32_t kByteCompareNext = 0x00e81139u;

// FUN_00b1fbf0 @ 0x00b1fbf0, reconstructed as a naked __thiscall transcription
// of the three observed bytes.
//
// NAKED, because for a three-byte body the C++ restatement would be a second
// claim rather than a first one: every compiler here emits `mov al,1; ret` from
// the same source but g++ emits `mov eax,1` -- a DIFFERENT machine body, one
// that writes all four bytes of the return register where the original writes
// one (see the RETURN section above). A naked transcription is the only form in
// which the reconstruction IS the machine body rather than a description of it.
//
// The parameters are unnamed because this function is naked and has no C++ body
// to read them in; a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared
// type describes the shape the machine enters this with: a receiver pointer in
// ECX, and nothing on the stack, because the callee pops nothing.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" std::uint8_t PKG_SHARED_DEFAULT_TRUE_WAVE12_NAKED_THISCALL
re_00b1fbf0_shared_default_true(Receiver*);

}  // namespace pkg_shared_default_true_wave12
}  // namespace reconstruction
}  // namespace openspore

#endif  // RECONSTRUCTION_STAGING_PKG_SHARED_DEFAULT_TRUE_WAVE12_B1FBF0_DEFAULT_TRUE_HPP_
