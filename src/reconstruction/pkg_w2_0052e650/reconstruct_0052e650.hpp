#pragma once

// Reconstruction of 0x0052e650 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e,
// image base 0x00400000, RVA 0x0012e650).
//
// WHAT THE BODY IS, EXACTLY
// -------------------------
// The complete recovered body is 13 bytes and 7 instructions. The bytes were
// read twice, from two independent Ghidra paths that agree:
// /disassemble_function 0x0052e650 and /read_memory 0x0052e650:13.
//
//   55           PUSH EBP
//   8b ec        MOV EBP,ESP
//   51           PUSH ECX
//   89 4d fc     MOV dword ptr [EBP + -0x4],ECX
//   8b e5        MOV ESP,EBP
//   5d           POP EBP
//   c2 04 00     RET 0x4
//
// That is the whole of it. Stated as facts, each traceable to the listing:
//
//   * a standard EBP prologue and its exact inverse as the epilogue
//     (PUSH EBP / MOV EBP,ESP ... MOV ESP,EBP / POP EBP), with no register
//     saved other than EBP;
//   * one 4-byte frame local, reserved by PUSH ECX, and one dword written into
//     it: the word carried in ECX at entry. The write lands on exactly the
//     word PUSH ECX reserved - [EBP-0x4] is the frame slot - and the listing
//     never reads that word back, so the store is dead in this body;
//   * ECX is READ twice (PUSH ECX, MOV [EBP-4],ECX) and is never dereferenced,
//     so the machine does not show an object behind it;
//   * EAX is never written, so nothing is returned;
//   * one 4-byte stack word, at entry_ESP+0x4, is never read and never
//     written;
//   * no branch, no call, no jump, no flag test, no loop, no global: the body
//     is straight-line and transfers control nowhere.
//
// THE CALLING CONVENTION, AS THE MACHINE NOW RECORDS IT
// -------------------------------------------------------
// The derived ABI record for this target (evidence pack
// reconstruction/evidence/0052e650/evidence.json, category abi_derived) states:
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
// So the machine now DETERMINES the convention, in two steps it records
// separately:
//
//   R1-VFT (INFERRED)  "ECX carries the receiver". The address is slot 5 of the
//                      sound vptr-backed vftable at 0x013ef620, one of 199 such
//                      tables, so it is a virtual member of some class; the body
//                      reads the incoming ECX before writing it, and a body that
//                      reads the register a vtable dispatch delivered uses the
//                      object. The rule also records why the read is the
//                      discriminator: a body in the COM / __stdcall form would
//                      take its receiver from the first popped stack word
//                      instead and would never read its incoming ECX.
//     value: {receiver_register ECX, receiver_provenance vftable_slot_dispatch,
//             slot_index 5, table 0x013ef620, membership_count 199,
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
// at 0x0055c630 the instruction SUB ECX,0x8 immediately precedes CALL
// 0x0052e650 at 0x0055c633, which is the this-adjustor MSVC emits when a caller
// converts a primary-base pointer into a base-subobject pointer. The caller
// therefore passes `this - 8` in ECX, and `this` is exactly the word __thiscall
// puts in ECX.
//
// What the machine proves about the stack, at OBSERVED confidence:
//
//   cleanup.bytes        : 4          confidence OBSERVED
//   cleanup.side         : callee     confidence OBSERVED
//   cleanup.evidence     : "ret 0x4"
//   cleanup.corroboration: not_available
//
// __thiscall does not pop its own arguments, so the callee-side cleanup is
// carried by the reconstructed entry's own `ret $4` and, independently, as
// DATA in CleanupSide52e650. The two are separate facts about the same machine
// behaviour and both are kept.
//
// WHAT THE CONVENTION DOES NOT SETTLE
// ------------------------------------
// A convention is not an identity. __thiscall says the receiver arrives in ECX;
// it does not say what the receiver IS. The body reads that word, stores it in a
// dead frame slot and never dereferences it, so this package names:
//
//   * no owning class. R1-VFT names ONE table and slot (0x013ef620, slot 5) as
//     the evidence for the receiver, and counts 199 tables that hold this
//     address; a slot index is not a class, the binary has no MSVC RTTI, and the
//     other 198 tables are not individually attributed here;
//   * no receiver type, shape, object size, vtable-pointer offset or field - the
//     only memory operand in the whole body is the callee's own frame slot at
//     [EBP + -0x4], based on EBP;
//   * no global, no callee, no branch and no return value: none appears in the
//     complete 7-instruction listing.
//
// The receiver is therefore carried in the entry as the plain 4-byte word the
// machine proves it to be, and nothing is asserted beyond that width.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "reconstruction of 0x0052e650 requires an x86-32 target"
#endif

// The convention macros. PKG_52E650_NAKED_THISCALL is the one the reconstructed
// entry point carries: it is the single token that lets the entry be both a
// byte-faithful naked transcription of the 13 target bytes and a normally
// declarable prototype that names the convention the machine derived.
#define PKG_52E650_THISCALL __attribute__((thiscall))
#define PKG_52E650_CDECL __attribute__((cdecl))
#define PKG_52E650_NAKED_THISCALL __attribute__((naked, thiscall))

namespace openspore::reconstruction::pkg_w2_0052e650 {

// -- identity ---------------------------------------------------------------
// The name of the reconstructed entry embeds the bare 8-hex target VA so the
// validator can bind the source span to 0x0052e650.
inline constexpr std::uint32_t kTargetVa = 0x0052e650u;
inline constexpr std::uint32_t kBodyFirstByte = 0x0052e650u;
inline constexpr std::uint32_t kBodyLastByte = 0x0052e65cu;  // inclusive last byte
inline constexpr std::uint32_t kBodyEndExclusive = 0x0052e65du;
inline constexpr std::size_t kBodySpanBytes = 13u;
inline constexpr std::size_t kInstructionCount = 7u;

// -- the machine body, as read from the binary ------------------------------
inline constexpr std::uint8_t kTargetBytes[kBodySpanBytes] = {
    0x55,  // 0x0052e650  PUSH EBP
    0x8b,  // 0x0052e651  MOV EBP,ESP
    0xec,  // 0x0052e652    second byte
    0x51,  // 0x0052e653  PUSH ECX
    0x89,  // 0x0052e654  MOV dword ptr [EBP + -0x4],ECX
    0x4d,  // 0x0052e655    ModRM
    0xfc,  // 0x0052e656    displacement
    0x8b,  // 0x0052e657  MOV ESP,EBP
    0xe5,  // 0x0052e658    ModRM
    0x5d,  // 0x0052e659  POP EBP
    0xc2,  // 0x0052e65a  RET 0x4
    0x04,  // 0x0052e65b    immediate, low byte
    0x00,  // 0x0052e65c    immediate, high byte
};

static_assert(kTargetBytes[0] == 0x55, "0x0052e650 is PUSH EBP");
static_assert(kTargetBytes[1] == 0x8b && kTargetBytes[2] == 0xec,
              "0x0052e651 is MOV EBP,ESP (8b ec)");
static_assert(kTargetBytes[3] == 0x51, "0x0052e653 is PUSH ECX");
static_assert(kTargetBytes[4] == 0x89 && kTargetBytes[5] == 0x4d &&
                  kTargetBytes[6] == 0xfc,
              "0x0052e654 is MOV dword ptr [EBP + -0x4],ECX (89 4d fc)");
static_assert(kTargetBytes[7] == 0x8b && kTargetBytes[8] == 0xe5,
              "0x0052e657 is MOV ESP,EBP (8b e5)");
static_assert(kTargetBytes[9] == 0x5d, "0x0052e659 is POP EBP");
static_assert(kTargetBytes[10] == 0xc2 && kTargetBytes[11] == 0x04 &&
                  kTargetBytes[12] == 0x00,
              "0x0052e65a is RET 0x4 (c2 04 00)");
static_assert(kBodyLastByte - kBodyFirstByte + 1u == kBodySpanBytes,
              "13 bytes span 0x0052e650..0x0052e65c inclusive (ghidra "
              "body_end 0x0052e65c, body_span_bytes 13)");
static_assert(kBodyEndExclusive - kBodyFirstByte == kBodySpanBytes,
              "the exclusive end is 0x0052e65d");

// -- frame shape ------------------------------------------------------------
inline constexpr std::int32_t kFrameLocalDisplacementEbp = -4;  // [EBP + -0x4]
inline constexpr std::uint32_t kFrameLocalBytes = 4u;           // one dword
inline constexpr std::size_t kFrameLocalWords = 1u;
// EBP is the only register the prologue and epilogue touch. The machine parse
// record states saved_registers ["EBP"] and the listing shows no other PUSH
// that is balanced by a POP of a general register.
inline constexpr std::size_t kSavedGeneralRegisterCount = 1u;

// -- stack shape ------------------------------------------------------------
inline constexpr std::uint32_t kRetImmediateBytes = 4u;      // RET 0x4
inline constexpr std::uint32_t kStackCleanupBytes = 4u;      // cleanup.bytes
inline constexpr std::size_t kStackArgumentWords = 1u;       // entry_ESP+0x4
inline constexpr std::size_t kStackArgumentOrdinal = 1u;     // ordinal 1
// The pack records this slot as observed=false, read=false, written=false,
// source="ret_immediate": its existence is derived from the terminal immediate
// alone, and the listing shows no instruction that reads or writes it.
inline constexpr bool kStackArgumentObserved = false;
inline constexpr bool kStackArgumentRead = false;
inline constexpr bool kStackArgumentWritten = false;

// The side that pops the 4 bytes. OBSERVED in the machine record
// (cleanup.side = "callee", cleanup.evidence = "ret 0x4").
enum class CleanupSide52e650 { kCallee };

// The derived conventions record, carried verbatim so the determination travels
// with the source instead of being silently dropped. The record names
// __thiscall at INFERRED confidence (rule C6B, on the receiver rule R1-VFT), so
// this enumerator names that one convention and no other.
enum class ConventionVerdict52e650 { kThiscall };

// -- the receiver ------------------------------------------------------------
// The derived receiver sub-record says the receiver is PRESENT and arrives in
// ECX, at INFERRED confidence, with provenance vftable_slot_dispatch. What the
// body proves beyond the register is only its width: one 4-byte word, the width
// of PUSH ECX. It is never dereferenced, so no shape, no object size, no field
// and no layout is claimed for it - and none is modelled.
enum class ReceiverRegister52e650 { kEcx };

inline constexpr CleanupSide52e650 kObservedCleanupSide =
    CleanupSide52e650::kCallee;
inline constexpr ConventionVerdict52e650 kDerivedConventionVerdict =
    ConventionVerdict52e650::kThiscall;
inline constexpr ReceiverRegister52e650 kDerivedReceiverRegister =
    ReceiverRegister52e650::kEcx;
inline constexpr bool kReceiverPresent = true;
inline constexpr bool kReceiverBoundsOnly = true;  // no shape, no offsets
inline constexpr std::size_t kReceiverDerefDereferenceCount = 0u;

// -- the body as counts -----------------------------------------------------
// Every one of these is an observation about the 7-instruction listing. The
// listing is complete and the machine parse record reports declared_count 7,
// degraded false, unparsed 0, flow_complete true, so the listing is the whole
// of the body and an absence read off it is an absence in the body.
inline constexpr bool kEaxWritten = false;                // no instruction writes EAX
inline constexpr std::size_t kFrameLocalWriteCount = 1u;  // one MOV to [EBP-0x4]
inline constexpr std::size_t kFrameLocalReadCount = 0u;   // never read back
inline constexpr std::size_t kConditionalBranchCount = 0u;
inline constexpr std::size_t kDirectTransferCount = 0u;
inline constexpr std::size_t kIndirectTransferCount = 0u;
inline constexpr std::size_t kGlobalReferenceCount = 0u;

// -- the modelled machine ---------------------------------------------------
// Memory is a flat array of 32-bit words addressed by WORD INDEX, so a byte
// displacement of 4 is exactly one word. Nothing in the model needs a byte
// address, and a byte address would add a conversion the machine does not
// contain.
struct MemoryImage52e650 {
  static constexpr std::size_t kWords = 32u;
  std::uint32_t words[kWords];

  void clear();
  bool in_range(std::int32_t word_index) const;
  std::uint32_t load(std::int32_t word_index) const;
  void store(std::int32_t word_index, std::uint32_t value);
};

// Machine state at entry, expressed only in quantities the listing fixes.
// `stack_pointer` is the word index of the return address the CALL pushed; the
// word the caller pushed as an argument is the next word above it, which is
// exactly `entry_ESP+0x4` in the record's spelling.
struct MachineEntry52e650 {
  std::uint32_t eax = 0u;
  std::uint32_t ecx = 0u;
  std::uint32_t edx = 0u;
  std::uint32_t ebx = 0u;
  std::uint32_t esi = 0u;
  std::uint32_t edi = 0u;
  // EBP and the stack pointer are WORD INDICES in this image, not byte
  // addresses: the only displacement the body uses is -4 bytes, which is
  // exactly one word, so carrying byte addresses would add a conversion the
  // machine does not contain. `frame_pointer_word` is the word EBP names at
  // entry, i.e. what the prologue's PUSH EBP will save.
  std::uint32_t frame_pointer_word = 0u;
  std::uint32_t stack_pointer = 0u;  // word index of the return address
  std::uint32_t return_address_word = 0u;
  std::uint32_t argument_word = 0u;  // entry_ESP+0x4
};

// What executing the 13 target bytes does, observed by the interpreter rather
// than asserted. Every counter here is filled by running the image; none of
// them is a constant the model can set.
struct MachineExit52e650 {
  std::uint32_t eax = 0u;
  std::uint32_t ecx = 0u;
  std::uint32_t frame_pointer_word = 0u;
  std::uint32_t stack_pointer = 0u;
  std::uint32_t frame_local_value = 0u;
  // The word index the value landed in, so a store aimed at the wrong word is
  // reported rather than masked by the store itself.
  std::uint32_t frame_local_word_index = 0u;
  std::uint32_t frame_local_writes = 0u;
  std::uint32_t frame_local_reads = 0u;
  std::uint32_t stack_argument_reads = 0u;
  std::uint32_t stack_argument_writes = 0u;
  std::uint32_t eax_writes = 0u;
  std::uint32_t instructions_executed = 0u;
  // Word index the caller's stack pointer had BEFORE it pushed the argument:
  // two words above the return address at entry, one for the CALL and one for
  // the caller's own PUSH. The callee returning to exactly this index is what
  // "the callee pops the 4 bytes" means, stated as a comparison rather than as
  // a claim.
  std::uint32_t caller_stack_pointer = 0u;
};

// Execute the 13 target bytes, in order, over `entry`. The interpreter
// implements exactly the seven encodings the body contains and refuses any
// other byte, so a body that grew an instruction this model did not read
// cannot be executed silently.
MachineExit52e650 ExecuteTargetImage(const MachineEntry52e650& entry);

// The reconstructed entry point: the instruction sequence of 0x0052e650 ..
// 0x0052e65a, one machine instruction per source line, spelled as a naked
// body so the RET 0x4 the machine performs is the RET 0x4 this entry performs.
//
// The convention is __thiscall, the convention the derived ABI record names at
// INFERRED confidence, so the first parameter is the receiver and arrives in
// ECX. The receiver is typed as the plain 4-byte word the machine proves it to
// be and as nothing more: the body never dereferences it, so no class, no
// receiver type, no field and no layout is claimed for it. `stack_word` is the
// one 4-byte word at entry_ESP+0x4, which the machine never reads and never
// writes and which the callee pops; naming it as a parameter is the source-side
// spelling of the observed callee-side cleanup, and its meaning is not claimed.
extern "C" void PKG_52E650_NAKED_THISCALL reconstruct_0052e650(
    std::uint32_t receiver_word, std::uint32_t stack_word);

// The same single effect in ordinary C++, for the behavioural model test: the
// word carried in the receiver register lands in the one 4-byte frame local and
// the frame is then discarded. The arguments here are passed on the stack by the
// caller rather than popped by the callee, so this is a statement about
// behaviour, not about the stack discipline; `reconstruct_0052e650` is what
// carries the RET 0x4 and the ECX receiver. Its name deliberately does not embed
// the target VA, so the validator's span binder can only bind to the entry above.
extern "C" void PKG_52E650_CDECL apply_frame_store_52e650(
    std::uint32_t* const frame_local_word, const std::uint32_t receiver_word);

// Run the modelled body over a machine entry state and report what a body of
// that shape would leave behind, using the same observation record the
// interpreter fills. The stack behaviour is applied from CleanupSide52e650
// rather than from the C++ signatures, so it is the modelled fact it claims to
// be, and a model that moved the pop to the caller would disagree with the
// interpreter here.
MachineExit52e650 ApplyReconstruction(const MachineEntry52e650& entry);

}  // namespace openspore::reconstruction::pkg_w2_0052e650
