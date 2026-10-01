// PKG-EDITOR-W1-0057D6F0 -- VA 0x0057d6f0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_0057d6f0 @ 0x0057d6f0.
//
// THE COMPLETE BODY, RE-READ FROM THE IMAGE FOR THIS PACKAGE.
// GhidraMCP /read_memory at 0x0057d6f0 for 30 bytes returns
//
//   56 8b f1 e8 28 c7 ff ff f6 44 24 08 01 74 09 56 e8 7b 9c 9c 00 83 c4 04
//   8b c6 5e c2 04 00
//
// and /disassemble_function at 0x0057d6f0 returns these eleven instructions at
// these eleven addresses:
//
//   0057d6f0  56              PUSH ESI
//   0057d6f1  8b f1           MOV ESI,ECX
//   0057d6f3  e8 28 c7 ff ff  CALL 0x00579e20
//   0057d6f8  f6 44 24 08 01  TEST byte ptr [ESP + 0x8],0x1
//   0057d6fd  74 09           JZ 0x0057d708
//   0057d6ff  56              PUSH ESI
//   0057d700  e8 7b 9c 9c 00  CALL 0x00f47380
//   0057d705  83 c4 04        ADD ESP,0x4
//   0057d708  8b c6           MOV EAX,ESI
//   0057d70a  5e              POP ESI
//   0057d70b  c2 04 00        RET 0x4
//
// Instruction lengths 1+2+5+5+2+1+5+3+2+1+3 = 30, which is
// ghidra_function.body_span_bytes, and the last instruction's three bytes end at
// 0x0057d70d, which is ghidra_function.body_end. abi_derived.parse reports
// {declared_count 11, unparsed 0, degraded false, flow_complete true}, so these
// eleven are the whole body and not a slice of something longer.
//
// STACK ARITHMETIC, WRITTEN OUT, BECAUSE THE ONE STACK READ IN THIS BODY IS
// READ AT AN OFFSET THAT ONLY BALANCES IF BOTH CALLS RESTORE THE POINTER.
// Let E be the callee's entry ESP. Then
//
//   after 0x0057d6f0 PUSH ESI          ESP = E - 4
//   after 0x0057d6f3 CALL 0x00579e20   the callee ends in a bare RET
//                                       (POP ESI; POP EBX; POP ECX; RET, with
//                                       three PUSH ECX/EBX/ESI before it) and
//                                       consumes no stack argument, so on return
//                                       ESP = E - 4
//   0x0057d6f8 reads [ESP + 0x8]       = byte at E + 4
//
// E + 4 is the caller's first ordinary stack argument slot: the return address
// occupies E..E+3 and the first pushed dword occupies E+4..E+7. So the TEST at
// 0x0057d6f8 reads the LOW BYTE of the first stack argument, and that is the
// only argument this body consumes.
//
//   after 0x0057d6ff PUSH ESI          ESP = E - 8
//   after 0x0057d700 CALL 0x00f47380   the callee ends in a bare RET (C3 at
//                                       0x00f47394) and consumes no stack
//                                       argument, so on return ESP = E - 8
//   0x0057d705 ADD ESP,0x4             ESP = E - 4
//   0x0057d70a POP ESI                 ESP = E
//   0x0057d70b RET 0x4                 ESP = E + 4 on the caller's side
//
// So stack_cleanup_bytes is 4, owner "callee", which is what
// abi_derived.abi records (cleanup.bytes 4, cleanup.side "callee",
// cleanup.evidence "ret 0x4", confidence OBSERVED) and what the arithmetic above
// re-derives independently from the three terminators' forms.
//
// THE CALLING CONVENTION, AS THE MACHINE NOW RECORDS IT
// -------------------------------------------------------
// The derived ABI record for this target (evidence pack
// reconstruction/evidence/0057d6f0/evidence.json, category abi_derived) states:
//
//   conventions.calling_convention    : __thiscall
//   conventions.confidence            : INFERRED
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities           : []
//
//   receiver.present        : true
//   receiver.register       : ECX
//   receiver.provenance     : vftable_slot_dispatch
//   receiver.confidence     : INFERRED
//   receiver.bounds_only    : true
//   receiver.shape          : null
//   receiver.distinct_offsets : 0
//   receiver.written_through  : 0
//
//   cleanup.bytes           : 4       confidence OBSERVED
//   cleanup.side            : callee  confidence OBSERVED
//   cleanup.evidence        : "ret 0x4"
//
// So the machine now DETERMINES the convention, in two steps it records
// separately:
//
//   R1-VFT  (INFERRED) "ECX carries the receiver". The address is a slot of the
//                      sound vptr-backed vftable based at 0x013f57f8, so it is a
//                      virtual member of some class; the body reads the register
//                      that dispatch delivered, and a body in the COM /
//                      __stdcall shape takes its receiver from the first popped
//                      stack word and never reads its incoming ECX.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             table 0x013f57f8, cleanup_side callee}
//
//   C6B     (INFERRED) "the calling convention is __thiscall". The callee pops
//                      its own stack arguments, which rules out cdecl and
//                      fastcall, and the receiver arrives in ECX.
//
// This is an INFERRED determination, not an OBSERVED one, and it is carried
// below as DATA (kDerivedConventionVerdict, kDerivedConventionConfidence,
// kCandidateConventionCount, kDerivedReceiverRegister, kReceiverProvenance,
// kObservedCleanupSide) rather than asserted in prose, so that a package which
// quietly reverted to the old abstention -- "no convention, no receiver" --
// fails the model test instead of passing.
//
// It is corroborated from the CALLER side, independently of the vftable rule.
// GhidraMCP /disassemble_bytes over 0x0057a590..0x0057a5d3 gives three
// two-instruction stubs, and they are the only code references to 0x0057d6f0 in
// the whole image apart from the table slot at 0x013f5800:
//
//   0057a5a0  83 e9 10        SUB ECX,0x10    ; 0057a5a3  e9 48 31 00 00  JMP 0x0057d6f0
//   0057a5b0  83 e9 14        SUB ECX,0x14    ; 0057a5b3  e9 38 31 00 00  JMP 0x0057d6f0
//   0057a5c0  83 e9 04        SUB ECX,0x4     ; 0057a5c3  e9 28 31 00 00  JMP 0x0057d6f0
//
// A first argument that a CALLER-side stub reduces by a constant before the
// transfer is a receiver; a by-value parameter is not adjusted. The same three
// stubs also exclude the pack's former other candidate, __stdcall: a free
// function has no receiver for a caller-side stub to adjust by a constant. That
// was the corroboration the record's own "corroboration": "not_available" was
// missing, and the model test drives it as a check rather than as a claim.
//
// WHAT THE CONVENTION DOES NOT SETTLE
// ------------------------------------
// A convention is not an identity. __thiscall says the receiver arrives in ECX;
// it does not say what the receiver IS. This body copies ECX into ESI at
// 0x0057d6f1, hands that VALUE to two other routines and puts it in EAX at
// 0x0057d708, and it never dereferences it: there is no load and no store
// through the receiver anywhere in the eleven instructions. So this package
// names:
//
//   * no owning class, and no vtable identity. R1-VFT names ONE table base
//     (0x013f57f8) and the slot's own displacement (+0x08) as the evidence for
//     the receiver; a slot is not a class, and this binary carries no MSVC RTTI.
//   * no receiver type, shape, object size, vtable-pointer offset or field. The
//     receiver is therefore declared and deliberately left undefined (struct
//     Receiver;), and the only memory operand in the whole body is the stack
//     argument byte read at [ESP + 0x8], based on ESP and not on the receiver.
//   * nothing about the three displacements the entry stubs subtract. Those are
//     read out of the image and asserted as DATA (kThisAdjustingEntryPoints,
//     kThunkThisAdjustments) because they are facts about three other
//     addresses; this body neither adds nor subtracts anything of its own, so
//     whether the incoming ECX points at an object head or at an interior
//     sub-object is NOT settled here and is carried as an open question.
//
// HONESTY NOTE ON WHERE EVERY CLAIM IN THIS HEADER COMES FROM.
//
//  * Receiver. It is declared but NOT DEFINED, and it carries no member, no size
//    and no layout. That is the strongest statement the eleven instructions
//    support. (The teardown routine at 0x00579e20 reaches to +0x5f8 of its own
//    receiver; that is the CALLEE's knowledge, not this body's, and it is not
//    imported here.)
//
//  * The two callees are declared, not defined, and are named after their
//    addresses. Neither name asserts a class, a signature or a role beyond what
//    the callee's own bytes show:
//
//      teardown_00579e20  0x00579e20, 649 instructions, entered with the object
//        in ECX and no stack argument, ends in a bare RET. Its FIRST act is
//        `MOV dword ptr [ESI],0x13f57f8` at 0x00579e27 -- it installs the very
//        table 0x013f57f8 that this body's own address sits in (see below) --
//        after which it releases a long series of members and finally re-points
//        the object's leading words at 0x013eb938. "Teardown" describes that
//        observable behaviour and nothing more. The word "destructor" is NOT
//        used, because the SDK never named it and this binary carries no MSVC
//        RTTI.
//
//      dispose_00f47380   0x00f47380, seven instructions: `MOV EAX,[ESP + 0x4]`,
//        `TEST EAX,EAX`, `JZ 0x00f47394`, and otherwise loads a dword from the
//        absolute 0x016c8b44, pushes the argument and calls 0x009276c0, then
//        falls into the bare RET. So: one cdecl stack argument, a null test on
//        it, and no stack cleanup. "Dispose" describes that shape. The absolute
//        0x016c8b44 is NOT modelled here -- it belongs to the callee, and this
//        body never names it.
//
//  * The stack argument is an unnamed 32-bit word. The machine reads ONE BIT of
//    it -- bit 0 of its low byte, through `TEST byte ptr [ESP + 0x8],0x1` -- and
//    the other 31 bits are never examined by any instruction in this body. It is
//    therefore NOT called a flag set, a mode, a reason or a boolean, and no
//    value of the word is given a meaning. It is DATA, not a receiver: the
//    deleting-destructor flag word lives at entry_ESP+0x4 and the receiver lives
//    in ECX, and the body reads the former and hands on the latter.
//
//  * The table. GhidraMCP /read_memory at 0x013f57f8 for 32 bytes returns
//    90 24 5b 00 | d0 a0 5b 00 | f0 d6 57 00 | f0 fb b1 00 | 00 43 58 00 |
//    50 6c 57 00 | d0 e6 58 00 | 20 7a 58 00, i.e. the table's first two slots hold
//    0x005b2490 and 0x005ba0d0 and its THIRD (displacement +0x08) holds
//    0x0057d6f0. Those are data-segment facts, recorded here for the integrator
//    and checked by the model test. This body never reads the table and never
//    reads the word at the receiver's +0x00, so NO slot is named as a member and
//    no dispatch is modelled. What any slot in that table is CALLED is identified
//    by nothing in this package.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-editor-w1-0057d6f0 requires an x86-32 target"
#endif

// The convention is spelled once, here, and the reconstructed entry names the
// macro.
//
//   PKG_EDITOR_W1_0057D6F0_THISCALL       the convention on an ordinary
//                                          declarable function. It is what the
//                                          model test gives the first callee,
//                                          which the machine enters the same
//                                          way (object in ECX, bare RET).
//   PKG_EDITOR_W1_0057D6F0_NAKED_THISCALL  the same convention on the naked
//                                          byte-faithful transcription of the
//                                          target's own 30 bytes.
//
// GCC rejects the bare MSVC keyword in the attribute position on some versions,
// so the attribute form is the portable spelling and the keyword form is kept
// for MSVC. Either way the token `thiscall` is carried once per macro, which is
// what the validator's `_convention_defines` resolves.
#if defined(_MSC_VER)
#define PKG_EDITOR_W1_0057D6F0_THISCALL __thiscall
#define PKG_EDITOR_W1_0057D6F0_NAKED_THISCALL __declspec(naked) __thiscall
#else
#define PKG_EDITOR_W1_0057D6F0_THISCALL __attribute__((thiscall))
#define PKG_EDITOR_W1_0057D6F0_NAKED_THISCALL __attribute__((naked, thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_w1_0057d6f0 {

// -- identity ---------------------------------------------------------------

// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x0057d6f0.
inline constexpr std::uint32_t kTargetVa = 0x0057d6f0u;
inline constexpr std::uint32_t kBodyFirstByte = 0x0057d6f0u;
inline constexpr std::uint32_t kBodyLastByte = 0x0057d70du;
inline constexpr std::uint32_t kBodyEndExclusive = 0x0057d70eu;

// -- boundary and opaque types ---------------------------------------------

// The receiver, declared and deliberately left undefined. This body never reads
// or writes a byte through it; it is a value that is handed to two other routines
// and handed back to the caller. Nothing about its size, layout or members is
// claimed, because nothing in the eleven instructions at 0x0057d6f0 can support
// any of those claims.
struct Receiver;

// The stack argument, as a plain 32-bit word. It is read as a BYTE
// (`TEST byte ptr [ESP + 0x8],0x1`) and only bit 0 of that byte is consulted;
// the other 31 bits are read by no instruction in this body.
using OptionWord = std::uint32_t;

// The one bit this body tests. 0x1, and nothing else: it is the immediate of the
// TEST at 0x0057d6f8 and it is the only immediate operand in the entire body that
// is not an address.
constexpr OptionWord kOptionBit0 = 0x1u;

// -- the extent facts, as values --------------------------------------------

constexpr int kInstructionCount = 11;
constexpr std::size_t kBodySpanBytes = 30;
constexpr int kBasicBlockCount = 2;   // the fall-through head and the JZ target
constexpr int kConditionalBranches = 1;
constexpr int kDirectCalleeCount = 2;
constexpr int kIndirectTransfers = 0;
constexpr int kGlobalReferences = 0;
constexpr int kStackArgumentSlots = 1;
constexpr std::size_t kStackCleanupBytes = 4;

// The target's own thirty bytes, transcribed from /read_memory at 0x0057d6f0.
// The model test compares the reconstructed entry's emitted bytes against THIS
// array -- against the binary, not against another assembly of the same
// instructions, so the comparison is a cross-check rather than a tautology.
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x56u,                          // 0057d6f0  PUSH ESI
    0x8bu, 0xf1u,                   // 0057d6f1  MOV ESI,ECX
    0xe8u,                          // 0057d6f3  CALL 0x00579e20 (opcode)
    0x28u, 0xc7u, 0xffu, 0xffu,     //           rel32, resolved by the test
    0xf6u, 0x44u, 0x24u, 0x08u, 0x01u,  // 0057d6f8  TEST byte ptr [ESP+0x8],0x1
    0x74u, 0x09u,                   // 0057d6fd  JZ 0x0057d708
    0x56u,                          // 0057d6ff  PUSH ESI
    0xe8u,                          // 0057d700  CALL 0x00f47380 (opcode)
    0x7bu, 0x9cu, 0x9cu, 0x00u,     //           rel32, resolved by the test
    0x83u, 0xc4u, 0x04u,            // 0057d705  ADD ESP,0x4
    0x8bu, 0xc6u,                   // 0057d708  MOV EAX,ESI
    0x5eu,                          // 0057d70a  POP ESI
    0xc2u, 0x04u, 0x00u,            // 0057d70b  RET 0x4
};

// The two rel32 displacements, as offsets into kTargetBytes, and the fact that
// each CALL is a five-byte E8 form. The displacement bytes cannot be compared
// against the binary's (they encode addresses in a different image), so the model
// test resolves them instead and requires each to land on the callee the
// xref export names for that callsite.
constexpr std::size_t kCallRel32FirstOffset = 4u;   // after the E8 at byte 3
constexpr std::size_t kCallRel32SecondOffset = 17u;  // after the E8 at byte 16

// The two instructions whose encoding the assembler is free to spell two ways.
// Both are the register-move direction: the binary encodes MOV r32,r/m32 (8b /r)
// and GAS picks MOV r/m32,r32 (89 /r) for the same operands and the same result.
//
//   0057d6f1  the binary 8b f1 (MOV ESI,ECX); GAS 89 ce (MOV ECX,ESI)
//   0057d708  the binary 8b c6 (MOV EAX,ESI); GAS 89 f0 (MOV ESI,EAX)
//
// clang++ -m32 emits the binary's own pair; g++ emits GAS's. Both spellings are
// accepted by the model test and each is pinned as one of the two; the remaining
// twenty-six byte positions have a single spelling and are compared literally.
constexpr std::size_t kEcxToEsiFirstByte = 1u;
constexpr std::size_t kEcxToEsiSecondByte = 2u;
constexpr std::size_t kEsiToEaxFirstByte = 24u;
constexpr std::size_t kEsiToEaxSecondByte = 25u;

// The word value that tells the probe to push NO second dword. Any other value is
// pushed first, so it lands at the callee's entry_ESP + 0x8 -- which is the slot
// 0x0057d6f8 reads when there is one. Zero is deliberately NOT the sentinel: the
// decoy cases pass 0 and 1 as real decoy words.
constexpr std::uint32_t kNoDecoyWord = 0xffffffffu;

// -- the machine-derived ABI, carried as DATA -------------------------------
//
// Every value below is transcribed from the evidence pack's `abi_derived`
// category (reconstruction/evidence/0057d6f0/evidence.json) and from nothing
// else. They are data rather than prose so that changing one is a change the
// model test can catch.

// The convention the derived record names: __thiscall, with no other candidate.
enum class ConventionVerdict57d6f0 : int { kThiscall = 0 };

// INFERRED, not OBSERVED and not UNKNOWN. The determination is an inference from
// the vftable-slot rule and the cleanup side; nothing here observed a caller.
enum class ConventionConfidence : int { kUnknown = 0, kInferred = 1, kObserved = 2 };

// The register the receiver arrives in.
enum class ReceiverRegister57d6f0 : int { kEcx = 0 };

// Why the derived record believes a receiver is there at all.
enum class ReceiverProvenance57d6f0 : int { kVftableSlotDispatch = 0 };

// Which side of the stack argument this callee pops.
enum class CleanupSide57d6f0 : int { kCallee = 0 };

constexpr ConventionVerdict57d6f0 kDerivedConventionVerdict =
    ConventionVerdict57d6f0::kThiscall;
constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kInferred;
constexpr int kCandidateConventionCount = 1;

constexpr ReceiverRegister57d6f0 kDerivedReceiverRegister =
    ReceiverRegister57d6f0::kEcx;
constexpr ReceiverProvenance57d6f0 kReceiverProvenance =
    ReceiverProvenance57d6f0::kVftableSlotDispatch;
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
constexpr CleanupSide57d6f0 kObservedCleanupSide = CleanupSide57d6f0::kCallee;
constexpr std::size_t kRetImmediateBytes = 4;
constexpr std::size_t kStackArgumentWords = 1;
// The one stack argument is READ (bit 0 of its low byte) and never WRITTEN.
constexpr bool kStackArgumentRead = true;
constexpr bool kStackArgumentWritten = false;

// -- the three this-adjusting entry stubs, and the table slot ---------------
//
// Read as bytes from the image; see the note above. These are facts about three
// other addresses and about one data table, and the body at 0x0057d6f0 neither
// adds nor subtracts anything of its own.
constexpr std::uint32_t kThisAdjustingEntryPoints[] = {0x0057a5a0u, 0x0057a5b0u,
                                                        0x0057a5c0u};
constexpr std::uint32_t kThunkThisAdjustments[] = {0x10u, 0x14u, 0x04u};
constexpr int kThisAdjustingEntryPointCount = 3;

constexpr std::uint32_t kTableBase = 0x013f57f8u;
constexpr std::size_t kOwnSlotDisplacement = 0x08u;

// -- the two direct callees, declared as the model's own out-of-line calls -----
//
// Their addresses are in their names, which is the convention the validator reads
// to compare a source's call set against the xref export. Both are entered the
// way the listing enters them: the teardown with the object in ECX and nothing on
// the stack, the disposer with one cdecl dword on the stack.

// 0x00579e20. Receiver in ECX, no stack argument, bare RET.
extern "C" void PKG_EDITOR_W1_0057D6F0_THISCALL teardown_00579e20(Receiver* object);

// 0x00f47380. One cdecl stack argument, no cleanup (bare RET at 0x00f47394).
extern "C" void dispose_00f47380(void* block);

// -- the reconstruction --------------------------------------------------------

// FUN_0057d6f0 @ 0x0057d6f0, reconstructed.
//
// A naked __thiscall transcription of the target's own thirty bytes. __thiscall
// is what puts the receiver in ECX; the callee-side cleanup of the one stack word
// is carried by this entry's own `retl $4`, which is the machine instruction
// 0x0057d70b itself rather than a statement about it.
//
// The parameters are left unnamed on purpose: this function is naked, so it has
// no C++ body to read them in, and a named parameter in a naked definition is an
// unused-parameter diagnostic under -Wextra on every compiler. The declared
// types describe the shape the machine enters this with -- a receiver pointer in
// ECX and one 32-bit word at entry_ESP+0x4 -- and the model test drives it
// through a call site that builds exactly that shape.
//
// The name embeds the target's 8-hex VA, which is what binds this span to this
// record in the validator.
extern "C" Receiver* PKG_EDITOR_W1_0057D6F0_NAKED_THISCALL re_0057d6f0(
    Receiver*, OptionWord);

}  // namespace openspore::reconstruction::pkg_editor_w1_0057d6f0
