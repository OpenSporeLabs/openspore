#pragma once

// Reconstruction of 0x0052e640 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e,
// image base 0x00400000, RVA 0x0012e640).
//
// WHAT THE BODY IS, EXACTLY
// -------------------------
// The complete recovered body is 15 bytes and 8 instructions. The bytes were
// read twice, from two independent Ghidra paths that agree:
// /disassemble_function 0x0052e640 and /read_memory 0x0052e640, which returns
// 558bec51894dfc32c08be55dc20c00cc -- the 15 body bytes followed by the cc
// inter-function pad at 0x0052e64f.
//
//   55           PUSH EBP
//   8b ec        MOV EBP,ESP
//   51           PUSH ECX
//   89 4d fc     MOV dword ptr [EBP + -0x4],ECX
//   32 c0        XOR AL,AL
//   8b e5        MOV ESP,EBP
//   5d           POP EBP
//   c2 0c 00     RET 0xc
//
// That is the whole of it. Stated as facts, each traceable to the listing:
//
//   * a standard EBP prologue and its exact inverse as the epilogue
//     (PUSH EBP / MOV EBP,ESP ... MOV ESP,EBP / POP EBP), with no register
//     saved other than EBP;
//   * one 4-byte frame local, reserved by PUSH ECX, and one dword written into
//     it: the word carried in ECX at entry. The write lands on exactly the
//     word PUSH ECX reserved - [EBP-0x4] is that frame slot - and the listing
//     never reads that word back, so the store is dead in this body;
//   * ECX is READ (PUSH ECX and then MOV [EBP-0x4],ECX) and is never
//     dereferenced, so the body itself shows the word and not what it points at;
//   * AL is zeroed, and AL alone: the low byte of EAX and nothing else, so bits
//     8..31 of EAX are whatever the caller left there. Both recorded consumers
//     read the byte alone (MOVZX EAX,AL at 0x0050a46d and 0x0050a5db), so the
//     byte is the contract;
//   * three 4-byte stack words, at entry_ESP+0x4 / +0x8 / +0xc, are popped by
//     the callee and are never read or written by any instruction;
//   * no branch, no call, no jump, no loop, no global: the body is
//     straight-line and transfers control nowhere.
//
// THE CALLING CONVENTION, AS THE MACHINE NOW RECORDS IT
// -------------------------------------------------------
// The derived ABI record for this target (evidence pack
// reconstruction/evidence/0052e640/evidence.json, category abi_derived) states:
//
//   conventions.calling_convention : __thiscall
//   conventions.confidence         : INFERRED
//   conventions.candidate_conventions : ["__thiscall"]
//   conventions.ambiguities        : []
//
//   receiver.present      : true
//   receiver.register     : ECX
//   receiver.provenance   : vftable_slot_dispatch
//   receiver.confidence   : INFERRED
//   receiver.bounds_only  : true
//   receiver.shape        : null
//   receiver.distinct_offsets : 0
//   receiver.written_through  : 0
//
// So the machine DETERMINES the convention, in two steps it records
// separately:
//
//   R1-VFT (INFERRED)  "ECX carries the receiver". 0x0052e640 is slot 8 of the
//                      sound vptr-backed vftable at 0x013f2194, one of 25 such
//                      tables, so it is a virtual member of some class; the body
//                      reads the incoming ECX before writing it, and a body that
//                      reads the register a vtable dispatch delivered uses the
//                      object. The rule also records why the read is the
//                      discriminator: the callee pops its own stack arguments,
//                      which is the COM / __stdcall interface form, and that is
//                      the one shape in which a virtual member takes its
//                      receiver from the first popped stack word instead - a
//                      body in that form never reads its incoming ECX.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             slot_index 8, table 0x013f2194, membership_count 25,
//             cleanup_side callee, incoming_ecx_reads 1}
//
//   C6B   (INFERRED)  "the calling convention is __thiscall". The callee pops
//                      its own stack arguments, which rules out cdecl and
//                      fastcall, and the receiver arrives in ECX.
//
// This is an INFERRED determination, not an OBSERVED one, and it is reported as
// such. The rule establishes that the receiver is a member-function receiver; it
// does not establish which class owns the vftable it sits in.
//
// It is corroborated from the caller side, independently of the vftable rule:
// both direct call sites, 0x0050a468 and 0x0050a5d6 inside 0x0050a0a0, push
// exactly three dwords, load ECX from the caller's own captured receiver
// (MOV ECX,[EBP-0x2c], its entry capture at 0x0050a0a9) and issue the CALL with
// no ADD ESP after it. Three pushed words, a register-carried receiver and
// callee cleanup is precisely what __thiscall with three stack arguments means.
// The sibling predicate 0x0050a920, called from the same block, is the same
// shape with four popped words, and it does dereference its ECX - so the
// ECX-capture prologue is a receiver idiom here and this body is one of its
// members.
//
// What the machine proves about the stack, at OBSERVED confidence:
//
//   cleanup.bytes        : 12         confidence OBSERVED
//   cleanup.side         : callee     confidence OBSERVED
//   cleanup.evidence     : "ret 0xc"
//   cleanup.corroboration: not_available
//
// THREE callee-popped words is the shape, and it is kept exactly: the
// reconstructed entry declares four parameters - the receiver plus three stack
// words - and its own `ret $12` performs the pop.
//
// WHAT THE CONVENTION DOES NOT SETTLE
// ------------------------------------
// A convention is not an identity. __thiscall says the receiver arrives in ECX;
// it does not say what the receiver IS. The body reads that word, stores it in a
// dead frame slot and never dereferences it, so this package names:
//
//   * no owning class. R1-VFT names ONE table and slot (0x013f2194, slot 8) as
//     the evidence for the receiver and counts 25 tables that hold this address;
//     a slot index is not a class, the binary has no MSVC RTTI, and the other 24
//     tables are not individually attributed here;
//   * no receiver type, shape, object size, vtable-pointer offset or field - the
//     only memory operand in the whole body is the callee's own frame slot at
//     [EBP + -0x4], based on EBP, and it is not a field of anything;
//   * no global, no callee, no branch, and no argument read: none appears in the
//     complete 8-instruction listing.
//
// The receiver is therefore carried in the entry as the plain 4-byte word the
// machine proves it to be, and nothing is asserted beyond that width.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "reconstruction of 0x0052e640 requires an x86-32 target"
#endif

// The convention macros. PKG_52E640_NAKED_THISCALL is the one the reconstructed
// entry point carries: it is the single token that lets the entry be both a
// byte-faithful naked transcription of the 15 target bytes and a normally
// declarable prototype that names the convention the machine derived.
#define PKG_52E640_THISCALL __attribute__((thiscall))
#define PKG_52E640_CDECL __attribute__((cdecl))
#define PKG_52E640_NAKED_THISCALL __attribute__((naked, thiscall))

namespace openspore::reconstruction::pkg_w2_0052e640 {

// -- identity ---------------------------------------------------------------
// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x0052e640.
inline constexpr std::uint32_t kTargetVa = 0x0052e640u;
inline constexpr std::uint32_t kBodyFirstByte = 0x0052e640u;
inline constexpr std::uint32_t kBodyLastByte = 0x0052e64eu;  // inclusive last byte
inline constexpr std::uint32_t kBodyEndExclusive = 0x0052e64fu;
inline constexpr std::size_t kBodySpanBytes = 15u;
inline constexpr std::size_t kInstructionCount = 8u;

// -- the machine body, as read from the binary ------------------------------
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x55,  // 0x0052e640  PUSH EBP
    0x8b,  // 0x0052e641  MOV EBP,ESP
    0xec,  // 0x0052e642    second byte
    0x51,  // 0x0052e643  PUSH ECX
    0x89,  // 0x0052e644  MOV dword ptr [EBP + -0x4],ECX
    0x4d,  // 0x0052e645    ModRM
    0xfc,  // 0x0052e646    displacement
    0x32,  // 0x0052e647  XOR AL,AL
    0xc0,  // 0x0052e648    ModRM
    0x8b,  // 0x0052e649  MOV ESP,EBP
    0xe5,  // 0x0052e64a    ModRM
    0x5d,  // 0x0052e64b  POP EBP
    0xc2,  // 0x0052e64c  RET 0xc
    0x0c,  // 0x0052e64d    immediate, low byte
    0x00,  // 0x0052e64e    immediate, high byte
};

static_assert(kTargetBytes[0] == 0x55, "0x0052e640 is PUSH EBP");
static_assert(kTargetBytes[1] == 0x8b && kTargetBytes[2] == 0xec,
              "0x0052e641 is MOV EBP,ESP (8b ec)");
static_assert(kTargetBytes[3] == 0x51, "0x0052e643 is PUSH ECX");
static_assert(kTargetBytes[4] == 0x89 && kTargetBytes[5] == 0x4d &&
                  kTargetBytes[6] == 0xfc,
              "0x0052e644 is MOV dword ptr [EBP + -0x4],ECX (89 4d fc)");
static_assert(kTargetBytes[7] == 0x32 && kTargetBytes[8] == 0xc0,
              "0x0052e647 is XOR AL,AL (32 c0)");
static_assert(kTargetBytes[9] == 0x8b && kTargetBytes[10] == 0xe5,
              "0x0052e649 is MOV ESP,EBP (8b e5)");
static_assert(kTargetBytes[11] == 0x5d, "0x0052e64b is POP EBP");
static_assert(kTargetBytes[12] == 0xc2 && kTargetBytes[13] == 0x0c &&
                  kTargetBytes[14] == 0x00,
              "0x0052e64c is RET 0xc (c2 0c 00)");
static_assert(kBodyLastByte - kBodyFirstByte + 1u == kBodySpanBytes,
              "15 bytes span 0x0052e640..0x0052e64e inclusive (ghidra "
              "body_end 0x0052e64e, body_span_bytes 15)");
static_assert(kBodyEndExclusive - kBodyFirstByte == kBodySpanBytes,
              "the exclusive end is 0x0052e64f");

// -- frame shape ------------------------------------------------------------
inline constexpr std::int32_t kFrameLocalDisplacementEbp = -4;  // [EBP + -0x4]
inline constexpr std::uint32_t kFrameLocalBytes = 4u;           // one dword
inline constexpr std::size_t kFrameLocalWords = 1u;
// EBP is the only register the prologue and epilogue touch. The machine parse
// record states saved_registers ["EBP"] and the listing shows no other PUSH
// that is balanced by a POP of a general register.
inline constexpr std::size_t kSavedGeneralRegisterCount = 1u;

// -- return shape -----------------------------------------------------------
// XOR AL,AL writes the low byte of EAX and nothing else, so the machine fixes
// the return WIDTH at one byte and the value at 0. Both recorded consumers read
// AL alone, so the byte is the contract and the dword is not. The one-byte C
// type used in the entry is a source-side choice among the one-byte types; the
// width and the constant are machine facts and both are carried here.
inline constexpr std::size_t kReturnWidthBytes = 1u;
inline constexpr std::uint8_t kReturnConstant = 0u;
inline constexpr std::size_t kEaxWriteCount = 1u;  // the single XOR AL,AL

// -- stack shape ------------------------------------------------------------
inline constexpr std::uint32_t kRetImmediateBytes = 12u;    // RET 0xc
inline constexpr std::uint32_t kStackCleanupBytes = 12u;    // cleanup.bytes
inline constexpr std::size_t kStackArgumentWords = 3u;      // ESP+4 / +8 / +0xc
// The pack records all three slots observed=false, read=false, written=false,
// source="ret_immediate", and inference A1-IMM at APPROXIMATION records them as
// the popped area rather than a read parameter count.
inline constexpr bool kStackArgumentObserved = false;
inline constexpr bool kStackArgumentRead = false;
inline constexpr bool kStackArgumentWritten = false;

// The side that pops the 12 bytes. OBSERVED in the machine record
// (cleanup.side = "callee", cleanup.evidence = "ret 0xc").
enum class CleanupSide52e640 { kCallee };

// The derived conventions record, carried verbatim so the determination travels
// with the source instead of being silently dropped. The record names
// __thiscall at INFERRED confidence (rule C6B, on the receiver rule R1-VFT), so
// this enumerator names that one convention and no other, and
// kCandidateConventionCount records that the record's candidate list held
// exactly that one entry and no ambiguity was left open.
enum class ConventionVerdict52e640 { kThiscall };
inline constexpr std::size_t kCandidateConventionCount = 1u;

// The confidence the record states for the determination. It is INFERRED, not
// OBSERVED and not UNKNOWN, and the distinction is carried as an enumerator
// rather than a comment so that a package which quietly upgraded the claim to an
// observed one, or dropped it back to unknown, is caught by the model test
// instead of being read as settled. The cleanup, by contrast, IS observed, and
// says so in its own field.
enum class ConventionConfidence { kUnknown, kInferred, kObserved };

// How the record says it determined the receiver: by the vtable slot this
// address occupies, not by a dereference the body never performs.
enum class ReceiverProvenance { kVftableSlotDispatch };

// -- the receiver ------------------------------------------------------------
// The derived receiver sub-record says the receiver is PRESENT and arrives in
// ECX, at INFERRED confidence, with provenance vftable_slot_dispatch. What the
// body proves beyond the register is only its width: one 4-byte word, the width
// of PUSH ECX. It is never dereferenced, so no shape, no object size, no field
// and no layout is claimed for it - and none is modelled.
enum class ReceiverRegister52e640 { kEcx };

inline constexpr CleanupSide52e640 kObservedCleanupSide =
    CleanupSide52e640::kCallee;
inline constexpr ConventionVerdict52e640 kDerivedConventionVerdict =
    ConventionVerdict52e640::kThiscall;
inline constexpr ConventionConfidence kDerivedConventionConfidence =
    ConventionConfidence::kInferred;
inline constexpr ConventionConfidence kDerivedReceiverConfidence =
    ConventionConfidence::kInferred;
inline constexpr ReceiverProvenance kReceiverProvenance =
    ReceiverProvenance::kVftableSlotDispatch;
inline constexpr ReceiverRegister52e640 kDerivedReceiverRegister =
    ReceiverRegister52e640::kEcx;
inline constexpr bool kReceiverPresent = true;
inline constexpr bool kReceiverAbsent = false;
inline constexpr bool kReceiverBoundsOnly = true;  // no shape, no offsets
inline constexpr bool kReceiverHasShape = false;   // receiver.shape is null
inline constexpr std::size_t kReceiverDerefDereferenceCount = 0u;

// The determination is ALSO pinned at compile time, and that is not redundancy
// for its own sake. A runtime check is a line, and a line can be deleted or
// short-circuited; mutation testing showed exactly that, with a repointed
// convention surviving once its check was made unreachable. A static_assert has
// no such arm: it holds the same fact at the point where the constant is
// defined, so deleting a runtime check cannot un-hold it, and the failure
// arrives as a build error on the mutant rather than as a pass.
//
// Each assert restates the machine record's own field, not the constant beside
// it, so it fails when the CONSTANT is repointed as well as when the assertion
// is.
static_assert(kDerivedConventionVerdict == ConventionVerdict52e640::kThiscall,
              "0x0052e640: conventions.calling_convention is __thiscall "
              "(abi_derived, INFERRED, rule C6B). It must not be repointed.");
static_assert(kCandidateConventionCount == 1u,
              "0x0052e640: conventions.candidate_conventions is [\"__thiscall\"] "
              "and ambiguities is [], so exactly one convention was determined.");
static_assert(kDerivedConventionConfidence == ConventionConfidence::kInferred,
              "0x0052e640: conventions.confidence is INFERRED, not OBSERVED and "
              "not UNKNOWN. Do not upgrade the claim.");
static_assert(kDerivedReceiverConfidence == ConventionConfidence::kInferred,
              "0x0052e640: receiver.confidence is INFERRED (rule R1-VFT).");
static_assert(kReceiverProvenance == ReceiverProvenance::kVftableSlotDispatch,
              "0x0052e640: receiver.provenance is vftable_slot_dispatch.");
static_assert(kDerivedReceiverRegister == ReceiverRegister52e640::kEcx,
              "0x0052e640: receiver.register is ECX.");
static_assert(kReceiverPresent,
              "0x0052e640: receiver.present is true.");
static_assert(kReceiverBoundsOnly,
              "0x0052e640: receiver.bounds_only is true - the record bounds the "
              "receiver and names no field.");
static_assert(!kReceiverHasShape,
              "0x0052e640: receiver.shape is null; no receiver type is claimed.");
static_assert(kObservedCleanupSide == CleanupSide52e640::kCallee,
              "0x0052e640: cleanup.side is \"callee\" (OBSERVED, \"ret 0xc\").");
static_assert(kStackCleanupBytes == 12u && kRetImmediateBytes == 12u,
              "0x0052e640: RET 0xc pops 12 bytes, so THREE callee-popped stack "
              "words. Do not change the count.");
static_assert(kStackArgumentWords == 3u,
              "0x0052e640: the popped area is three dwords, at entry_ESP+0x4, "
              "+0x8 and +0xc.");
static_assert(kReturnWidthBytes == 1u && kReturnConstant == 0u,
              "0x0052e640: XOR AL,AL writes one byte of EAX and writes it with "
              "the value 0.");

// -- the body as counts -----------------------------------------------------
// Every one of these is an observation about the 8-instruction listing. The
// listing is complete and the machine parse record reports declared_count 8,
// degraded false, unparsed 0, flow_complete true, so the listing is the whole
// of the body and an absence read off it is an absence in the body.
inline constexpr std::size_t kFrameLocalWriteCount = 1u;   // one MOV to [EBP-0x4]
inline constexpr std::size_t kFrameLocalReadCount = 0u;    // never read back
inline constexpr std::size_t kConditionalBranchCount = 0u;
inline constexpr std::size_t kDirectTransferCount = 0u;
inline constexpr std::size_t kIndirectTransferCount = 0u;
inline constexpr std::size_t kGlobalReferenceCount = 0u;

// The reconstructed entry point: the instruction sequence of 0x0052e640 ..
// 0x0052e64c, one machine instruction per source line, spelled as a naked body
// so the RET 0xc the machine performs is the RET 0xc this entry performs.
//
// The convention is __thiscall, the convention the derived ABI record names at
// INFERRED confidence, so the first parameter is the receiver and arrives in
// ECX and the remaining three are the three callee-popped stack words. The
// receiver is typed as the plain 4-byte word the machine proves it to be and as
// nothing more: the body never dereferences it, so no class, no receiver type,
// no field and no layout is claimed for it. The stack words are named because
// `ret $12` pops them, not because the body reads them - which it does not, and
// the model test proves that for a spread of values.
extern "C" std::uint8_t PKG_52E640_NAKED_THISCALL reconstruct_0052e640(
    std::uint32_t receiver_word, std::uint32_t first, std::uint32_t second,
    std::uint32_t third);

// The same single effect in ordinary C++, for the behavioural model test: the
// word carried in the receiver register lands in the one 4-byte frame local, the
// three stack words are read by nothing, and the answer is the byte 0. The
// arguments here are passed on the stack by the caller rather than popped by
// the callee, so this is a statement about behaviour, not about the stack
// discipline; `reconstruct_0052e640` is what carries the RET 0xc and the ECX
// receiver. Its name deliberately does not embed the target VA, so the
// validator's span binder can only bind to the entry above.
extern "C" std::uint8_t PKG_52E640_CDECL apply_frame_store_52e640(
    std::uint32_t* const frame_local_word, const std::uint32_t receiver_word,
    const std::uint32_t first, const std::uint32_t second,
    const std::uint32_t third);

}  // namespace openspore::reconstruction::pkg_w2_0052e640
