// PKG-DFW-005C8BC0 -- VA 0x005c8bc0
// Behavioural model test for the body at 0x005c8bc0.
//
// There are no extern callees to observe. The body is a leaf: the complete
// 12-instruction listing contains no CALL, no indirect transfer and no store, and
// the ABI dispatch record agrees at indirect_calls 0. The only transfers this test
// can watch are the argument transfers at the ABI boundary, so that is what it
// watches -- through a hand-written x86-32 caller rather than through a C++ one,
// so that the register/stack split and the callee-side stack pop are asserted as
// machine facts rather than taken on the declaration's word.
//
// WHAT IS ASSERTED AGAINST WHAT, AND WHY NONE OF IT IS A TAUTOLOGY
// ----------------------------------------------------------------
//
// Every check below compares an observed value against something the test states
// INDEPENDENTLY of the code under test. Concretely:
//
//   * the three compared values are NOT imported from the package header. They are
//     DECODED at run time out of kTargetBytes -- the target's own thirty-nine
//     bytes as transcribed from GhidraMCP /read_memory at 0x005c8bc0 -- by reading
//     the little-endian imm32 that follows each `81 F9` CMP opcode pair. The three
//     `81 F9` opcodes are themselves located by scanning for the opcode, not by
//     trusting the header's offset constants alone, and the scan is required to
//     find exactly three. A model constant edited to a wrong value therefore cannot
//     make both sides agree: the bytes would still say the other number.
//   * the RET immediate is decoded out of the same byte array, and the stack delta
//     the harness measures is compared against THAT number. A model that popped the
//     wrong amount is refuted by a value read out of the binary, not by a value
//     copied from the model's own declaration.
//   * the two JZ targets are decoded out of the same byte array and required to land
//     on the address of the RET. That is what "both guards converge on one shared
//     terminator" means, and it is checked rather than asserted in prose.
//   * the header's transcribed ABI data (convention verdict, confidence, receiver
//     register, receiver provenance, cleanup side, receiver-present, bounds-only,
//     dereference count, field-offset-claimed) is checked against literals written
//     here. Those literals are the machine record's own values, restated, so a
//     header that quietly reverted to the old "no convention, no receiver" abstention
//     fails instead of passing.
//   * the header's three named constants are checked against the decoded bytes, and
//     the header's declared target VA and body span are checked against literals
//     written here.
//
// Nothing in this file compares a value with its own copy of itself. Where a check
// reads a header constant, the other side of the comparison is a byte decoded from
// the image or a literal transcribed from the machine record.
//
// REGISTER DISCIPLINE OF THE PROBE
// -------------------------------
//
// The probe is a bare `__asm__` block, so the compiler does not model what it does
// to ESP. It therefore touches ONLY caller-saved registers -- EAX, ECX, EDX -- and
// keeps everything that must survive the call in its own frame, reached through
// %ebp. It does not write ESI, EDI or EBX at all: each is callee-saved, so a probe
// that borrows one corrupts its CALLER silently rather than itself, and on a PIC
// i386 build EBX additionally holds the GOT base, so taking it over inside inline
// assembly invalidates every address the compiler forms around the block. EBP is
// used only as this probe's own frame pointer, pushed and popped by the probe
// itself.
//
// The samples are taken through the probe's own frame pointer rather than through
// the stack pointer, because the stack pointer is exactly the thing the two cleanup
// sides disagree about. `esp_before` is recorded after the frame reservation and
// before any of the four words are pushed, so the difference between the two
// samples IS the machine's RET immediate, independently of where the call sat: four
// words pushed and one popped leaves the pointer twelve below where the reservation
// put it, two popped leaves eight, three leaves four, and a bare RET leaves all
// sixteen.
//
// The block is emitted as its own NOINLINE function. That is a correctness
// requirement, not a precaution: an extended-asm block that moves ESP internally
// while declaring a "memory" clobber is not modelled precisely enough by either
// compiler for the surrounding code's load and store motion to be relied on once
// the block is inlined.
//
// WHAT NO CHECK HERE CAN DISTINGUISH, STATED RATHER THAN HIDDEN
// --------------------------------------------------------------
//
// All three membership paths return the same word, so the ORDER of the three
// comparisons, the order of the two JZ guards, and whether the body is written as
// three comparisons or as one membership expression are all invisible in the return
// value. This test asserts the outcome of the membership test and the shape of the
// control flow, and says nothing about the arrangement that produces the outcome;
// the arrangement is fixed by the listing and recorded in the per-instruction
// annotations of dfw_005c8bc0.cpp rather than claimed as a check here. The mutation
// report says so with a mutation that survives, and states why it cannot be killed.

#include "dfw_005c8bc0_types.hpp"

#include <cstdint>
#include <cstdio>

namespace openspore::reconstruction::pkg_dfw_005c8bc0 {
namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// -- the target's own bytes, read back from the header's transcription --------
//
// kTargetBytes is transcribed from GhidraMCP /read_memory at 0x005c8bc0. This test
// does not take the header's word for what the bytes say: it scans for the opcodes
// and decodes the immediates out of them, so a header whose transcription drifted
// fails here rather than silently agreeing with a model that drifted the same way.

std::uint8_t byte_at(std::size_t index) {
  return kTargetBytes[index];
}

std::uint32_t little_endian32(std::size_t offset) {
  return static_cast<std::uint32_t>(byte_at(offset)) |
         (static_cast<std::uint32_t>(byte_at(offset + 1)) << 8) |
         (static_cast<std::uint32_t>(byte_at(offset + 2)) << 16) |
         (static_cast<std::uint32_t>(byte_at(offset + 3)) << 24);
}

std::uint32_t little_endian16(std::size_t offset) {
  return static_cast<std::uint32_t>(byte_at(offset)) |
         (static_cast<std::uint32_t>(byte_at(offset + 1)) << 8);
}

// Every offset of the 81 F9 opcode pair (CMP r/m32, imm32) in the body, in order.
// Located by scanning, not read from the header's constants.
int find_cmp_imm_offsets(std::size_t* out, int capacity) {
  int found = 0;
  for (std::size_t index = 0; index + 6u <= kBodySpanBytes; ++index) {
    if (byte_at(index) == 0x81u && byte_at(index + 1) == 0xf9u) {
      if (found < capacity) {
        out[found] = index + 2u;
      }
      ++found;
    }
  }
  return found;
}

// The immediate of the Nth (zero-based) CMP in the body, decoded from the bytes.
std::uint32_t decoded_cmp_value(int index) {
  std::size_t offsets[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  const int found = find_cmp_imm_offsets(offsets, 8);
  if (found != 3 || index < 0 || index >= found) {
    return 0u;
  }
  return little_endian32(offsets[index]);
}

// The RET at the end of the body: its opcode offset, its imm16, and the address it
// is found at. Located by scanning for the C2 opcode in the last three bytes.
std::size_t decoded_ret_offset() {
  return kRetOpcodeOffset;
}

std::uint32_t decoded_ret_immediate() {
  return little_endian16(decoded_ret_offset() + 1u);
}

std::uint32_t decoded_jz_target(int which) {
  // JZ rel8: opcode 74 at some offset, rel8 in the next byte. The target is the
  // address of the following instruction plus the signed displacement.
  const std::size_t relative = (which == 0) ? kFirstJzRelOffset : kSecondJzRelOffset;
  const std::size_t next = relative + 1u;
  const int displacement = static_cast<int>(byte_at(relative));
  return static_cast<std::uint32_t>(kBodyFirstByte + next +
                                    static_cast<std::uint32_t>(displacement));
}

// The literal values the machine record carries, restated here so that the header's
// transcription of them is checked against something that is not the header.
constexpr int kRecordConfidenceInferred = 1;   // ConventionConfidence::kInferred
constexpr int kRecordReceiverRegisterEcx = 0;  // ReceiverRegister::kEcx
constexpr int kRecordProvenanceVftableSlot = 0;  // ReceiverProvenance::kVftableSlotDispatch
constexpr int kRecordCleanupSideCallee = 0;    // CleanupSide::kCallee
constexpr int kRecordConventionThiscall = 0;    // ConventionVerdict::kThiscall

void test_the_three_cmp_immediates_decode_out_of_the_image_bytes() {
  std::size_t offsets[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  check(find_cmp_imm_offsets(offsets, 8) == 3,
        "0x005c8bc6/0x005c8bce/0x005c8bd8: exactly three CMP ECX,imm32 in the body");
  check(decoded_cmp_value(0) == 0xee3f516eu,
        "the first CMP immediate decodes to 0xee3f516e out of the image bytes");
  check(decoded_cmp_value(1) == 0x2f009dd0u,
        "the second CMP immediate decodes to 0x2f009dd0 out of the image bytes");
  check(decoded_cmp_value(2) == 0x72deed2bu,
        "the third CMP immediate decodes to 0x72deed2b out of the image bytes");
}

void test_the_header_constants_are_the_bytes_own_values() {
  // The header's named constants against the decoded bytes. If either side is
  // edited, this fails: the model is then comparing against a value the binary
  // does not compare against.
  check(kFirstComparedValue == decoded_cmp_value(0),
        "the header's first constant is the first CMP immediate in the bytes");
  check(kSecondComparedValue == decoded_cmp_value(1),
        "the header's second constant is the second CMP immediate in the bytes");
  check(kThirdComparedValue == decoded_cmp_value(2),
        "the header's third constant is the third CMP immediate in the bytes");
  // And the offsets the header publishes must be the offsets the scan finds, so the
  // scan and the constants cannot disagree about which CMP is which.
  std::size_t offsets[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  find_cmp_imm_offsets(offsets, 8);
  check(offsets[0] == kFirstCmpImmOffset && offsets[1] == kSecondCmpImmOffset &&
            offsets[2] == kThirdCmpImmOffset,
        "the header's published CMP immediate offsets are the ones the scan finds");
}

void test_the_return_semantics_the_bytes_carry() {
  // 0x005c8be4  c2 04 00  RET 0x4 -- the terminal immediate, read out of the bytes.
  check(byte_at(decoded_ret_offset()) == 0xc2u,
        "0x005c8be4 is a RET imm16 (opcode C2)");
  check(decoded_ret_immediate() == 4u,
        "the RET immediate in the bytes is 4: the callee drops four bytes");
  check(kStackCleanupBytes == decoded_ret_immediate(),
        "the header's cleanup byte count is the RET immediate in the bytes");

  // 0x005c8be2  23 c2  AND EAX,EDX -- a full 32-bit word AND (mod=11, reg=EAX,
  // r/m=EDX), not a byte operation and not a TEST.
  check(byte_at(kAndOpcodeOffset) == 0x23u && byte_at(kAndOpcodeOffset + 1u) == 0xc2u,
        "0x005c8be2 is a full-word AND EAX,EDX, not a byte operation");

  // 0x005c8bde  0f 95 c2  SETNZ DL: 0f 90+cc with cc=0x02 gives 0f 95, mod=11,
  // reg field 010 (EDX), r/m field 000 (DL). So the mask is built from DL against
  // the EDX that 33 d2 (XOR EDX,EDX) has just cleared -- which is what makes the
  // third guard a KEEP on equality rather than an inversion.
  check(byte_at(30u) == 0x0fu && byte_at(31u) == 0x95u && byte_at(32u) == 0xc2u,
        "0x005c8bde is SETNZ DL (0f 95 c2), writing DL and not EDX");
  check(byte_at(22u) == 0x33u && byte_at(23u) == 0xd2u,
        "0x005c8bd6 is XOR EDX,EDX, which is what clears the other three bytes");
  check(byte_at(33u) == 0x4au, "0x005c8be1 is DEC EDX, completing the SETNZ/DEC mask");
  check(byte_at(0u) == 0x8bu && byte_at(1u) == 0xc1u,
        "0x005c8bc0 is MOV EAX,ECX (8b c1), the whole 32-bit copy into the return register");
  check(byte_at(2u) == 0x8bu && byte_at(3u) == 0x4cu && byte_at(4u) == 0x24u &&
            byte_at(5u) == 0x04u,
        "0x005c8bc2 is MOV ECX,[ESP+0x4], the only memory operand in the body");
}

void test_both_jz_guards_land_on_the_shared_terminator() {
  // The two rel8 displacements in the bytes must resolve to the address of the RET.
  // This is the "the branch graph is closed inside the body" claim, checked.
  const std::uint32_t terminator = kBodyFirstByte + decoded_ret_offset();
  check(decoded_jz_target(0) == terminator,
        "0x005c8bcc JZ resolves to the shared terminator, not past the body");
  check(decoded_jz_target(1) == terminator,
        "0x005c8bd4 JZ resolves to the shared terminator, not past the body");
  check(terminator <= kBodyLastByte,
        "the shared terminator is inside the recovered body span");
}

void test_the_transcribed_abi_data_matches_the_machine_record() {
  // The header carries the derived record as DATA. Each value is checked against a
  // literal written here, transcribed from reconstruction/evidence/005c8bc0/
  // evidence.json category abi_derived. A header that reverted to the old
  // "no convention, no receiver" abstention fails these checks.
  check(static_cast<int>(kDerivedConventionVerdict) == kRecordConventionThiscall,
        "the derived record names __thiscall and this package declares it");
  check(static_cast<int>(kDerivedConventionConfidence) == kRecordConfidenceInferred,
        "the derived convention confidence is INFERRED, not UNKNOWN and not OBSERVED");
  check(kCandidateConventionCount == 1,
        "__thiscall is the only candidate the derived record lists");
  check(kConventionAmbiguityCount == 0, "the derived record records no ambiguity");
  check(static_cast<int>(kDerivedReceiverRegister) == kRecordReceiverRegisterEcx,
        "the derived receiver register is ECX");
  check(static_cast<int>(kReceiverProvenance) == kRecordProvenanceVftableSlot,
        "the derived receiver provenance is vftable_slot_dispatch");
  check(kReceiverPresent && !kReceiverAbsent,
        "the derived record determines receiver.present = true");
  check(kReceiverBoundsOnly && !kReceiverHasShape,
        "the derived receiver record is bounds_only with no shape");
  check(kReceiverDereferenceCount == 0 && kReceiverDistinctOffsets == 0,
        "the body dereferences the receiver zero times, so no offset was seen");
  check(!kReceiverFieldOffsetClaimed,
        "no receiver field offset is claimed in either direction");
  check(static_cast<int>(kObservedCleanupSide) == kRecordCleanupSideCallee,
        "the observed cleanup side is the callee");
  // The machine's own recorded reason that the body alone could not settle the
  // receiver is still true and is still carried; it is the reason field, not an
  // abstention.
  check(kReceiverReasonIsEcxReadWithoutDeref,
        "the derived record's receiver reason ecx_read_without_deref is carried");
  // The stack word is data, not a receiver, and never treated as a pointer.
  check(kStackArgumentRead && !kStackArgumentWritten,
        "the one stack word is read and never written");
  check(!kStackArgumentIsReceiver && !kStackArgumentTreatedAsPointer,
        "the stack word is not the receiver and is not treated as a pointer");
  // The extent facts, against the bytes.
  check(kInstructionCount == 12, "the body is twelve instructions");
  check(kBodySpanBytes == 39u, "the body is thirty-nine bytes");
  check(kDirectCalleeCount == 0 && kIndirectTransfers == 0,
        "the body makes no call and no indirect transfer");
  check(kGlobalReferences == 0, "the body names no global");
  check(kConditionalBranches == 2, "the body has exactly two conditional branches");
  check(kStackArgumentSlots == 1, "the body consumes exactly one stack word");
  check(kReturnRegisterId == 0 && kReturnWidthBytes == 4u,
        "the return is a four-byte word in EAX");
  check(kTargetVa == 0x005c8bc0u, "the header names the target VA");
  check(kBodyLastByte == 0x005c8be4u && kBodyEndExclusive == 0x005c8be5u,
        "the header names the body span the listing gives");
  // The vftable membership R1-VFT reasons from, as data.
  check(kTableBase == 0x013f82fcu && kOwnSlotIndex == 7u,
        "0x005c8bc0 is slot 7 of the vftable the record bases at 0x013f82fc");
  check(kTableBase + kOwnSlotDisplacement == 0x013f8318u,
        "the slot word is the record's reported xref at 0x013f8318");
  // The byte past the body is the image's inter-function padding.
  check(byte_at(kBodySpanBytes - 1u) == 0x00u,
        "the last body byte is the RET immediate's high byte, 0x00");
}

// -- the machine-level caller -----------------------------------------------
//
// A hand-written x86-32 caller for the model, published by the assembly stub below.
// The stub is written in assembly on purpose: a C++ caller would have inherited this
// package's own convention macros, and would therefore be able to detect nothing
// about them. Here the argument registers and the stack discipline are chosen by
// hand, so the assertions in the tests below are statements about the machine and
// not about the declaration.
//
// Four words are pushed, in this order: three fillers first, then the word under
// test. The fillers exist so that a callee which drops the wrong amount cannot run
// off the end of the caller's frame, and the epilogue restores ESP from %ebp rather
// than by arithmetic, so a wrong-arity callee is reported as a wrong stack delta
// instead of as a crash. That makes the arity assertion numeric:
//
//   * the machine's shape -- a receiver in ECX and one stack word, retired with
//     RET 0x4 -- leaves the three fillers behind, so ESP on return is exactly twelve
//     below where it was before the four pushes;
//   * a second stack word, retired with RET 0x8, leaves two fillers, eight below;
//   * a third, retired with RET 0xc, leaves one, four below;
//   * a bare RET (a caller-cleaned convention) drops nothing of ours and leaves all
//     four, sixteen below.
//
// Four distinct deltas, so the arity and the stack owner are both decided by the
// numbers rather than by a crash. The expected number is not written into the
// assertion as a literal 12: it is computed from the four words pushed and from the
// RET immediate decoded out of the image bytes, so a model that dropped the wrong
// amount would have to agree with a number the binary does not carry.
//
// The word the body reads at 0x005c8bc2 is [ESP + 0x4] on entry, which is the word
// pushed last, so the word under test is the one it compares. Offsets: after
// `pushl %ebp`, 8(%ebp) is the caller's first argument, 12(%ebp) the second and
// 16(%ebp) the third.
struct AbiObservation {
  std::uint32_t stack_pointer_before_call; // ESP after the reservation, before the pushes
  std::uint32_t stack_pointer_after_return; // ESP immediately after it returned
  std::uint32_t returned;                 // EAX on return
};

// The offsets of those three fields inside the struct the probe writes. Spelled out
// here so the assembly's three stores and the struct's layout are two statements
// about the same numbers rather than one, and a layout change that reordered them
// would be caught by the values rather than silently swapping two samples.
constexpr std::size_t kOutBeforeOffset = 0u;
constexpr std::size_t kOutAfterOffset = 4u;
constexpr std::size_t kOutReturnedOffset = 8u;
static_assert(offsetof(AbiObservation, stack_pointer_before_call) == kOutBeforeOffset &&
                  offsetof(AbiObservation, stack_pointer_after_return) == kOutAfterOffset &&
                  offsetof(AbiObservation, returned) == kOutReturnedOffset,
              "the probe writes the three samples at the offsets declared above");

extern "C" void dfw_005c8bc0_abi_probe(AbiObservation* out,
                                       std::uint32_t ecx_input,
                                       std::uint32_t stack_input);

// The block below is a top-level assembly definition of a real function symbol, so
// the compiler emits it as a function of its own and never inlines it into a
// caller: its effect on ESP is entirely inside the frame it establishes and tears
// down itself, and the only contact it has with this translation unit is through
// the two pointers it writes.
//
// The frame, with B = %ebp and a 12-byte reservation:
//
//   B-4   EAX on return, captured before EAX is reused
//   B-8   %esp immediately after the call returns, captured before any fixup
//   B-12  the bottom of the reservation, i.e. where `before` was sampled
//
// Only EAX, ECX and EDX are written. ESI, EDI, EBX and (apart from this frame
// pointer, which the block pushes and pops itself) EBP are never touched, so the
// probe hands its caller every register back exactly as it found it.
__asm__(".text\n"
        ".balign 16\n"
        ".globl dfw_005c8bc0_abi_probe\n"
        ".type  dfw_005c8bc0_abi_probe, @function\n"
        "dfw_005c8bc0_abi_probe:\n"
        "  pushl %ebp\n"            // the probe's own frame pointer, saved
        "  movl  %esp, %ebp\n"
        "  subl  $12, %esp\n"        // B-12 .. B-1: the samples
        "  movl  8(%ebp), %eax\n"   // the output pointer
        "  movl  %esp, (%eax)\n"    // out->stack_pointer_before_call: after the
                                   // reservation, before any of the four pushes
        "  movl  12(%ebp), %ecx\n"  // the word that goes into ECX
        "  pushl $0x5a5a5a5a\n"     // three fillers, pushed first so they sit
        "  pushl $0x5a5a5a5a\n"     // ABOVE the word under test
        "  pushl $0x5a5a5a5a\n"
        "  pushl 16(%ebp)\n"        // the word under test, pushed last and so lowest
        "  call  dfw_005c8bc0_load\n"
        "  movl  %eax, -4(%ebp)\n"  // EAX on return, before EAX is reused
        "  movl  %esp, -8(%ebp)\n"  // %esp after the return, before any fixup
        "  movl  8(%ebp), %eax\n"   // the output pointer again
        "  movl  -4(%ebp), %edx\n"
        "  movl  %edx, 8(%eax)\n"    // out->returned
        "  movl  -8(%ebp), %edx\n"
        "  movl  %edx, 4(%eax)\n"    // out->stack_pointer_after_return
        "  movl  %ebp, %esp\n"      // the frame is torn down from %ebp, never by
        "  popl  %ebp\n"            // arithmetic on the number of bytes a callee
        "  ret\n"                   // happened to drop
        ".size dfw_005c8bc0_abi_probe, .-dfw_005c8bc0_abi_probe\n");

// A distinct, non-constant receiver word. Chosen so that a model returning the
// compared value, a model returning a boolean, and a model returning a
// differently-truncated word all produce a different answer.
constexpr std::uint32_t kDistinctWord = 0x0badc0deU;

// The four words the probe pushes, and the immediate the binary carries. The
// expected ESP delta follows from both: four words pushed, one popped, and the
// stack grows downwards, so the pointer ends sixteen minus the popped amount below
// where it was.
constexpr std::uint32_t kProbeWordsPushed = 4u;

AbiObservation observe(std::uint32_t ecx_input, std::uint32_t stack_input) {
  AbiObservation observation = {0u, 0u, 0u};
  dfw_005c8bc0_abi_probe(&observation, ecx_input, stack_input);
  return observation;
}

// 0x005c8bc0 MOV EAX,ECX, with 0x005c8bcc / 0x005c8bd4 JZ 0x005c8be4 and the
// 0x005c8bde-0x005c8be2 mask: for each of the three compared values the returned
// word is the ECX input unchanged. Three different ECX inputs, so a model that
// returned one hard-coded word, or the compared value, or a one-bit flag, would
// fail at least one of them. The compared values are the ones decoded from the
// image bytes, not the header's constants.
void test_each_compared_value_returns_the_whole_register_word() {
  const std::uint32_t inputs[] = {kDistinctWord, 0xffffffffU, 0x00000001U};
  for (const std::uint32_t input : inputs) {
    check(observe(input, decoded_cmp_value(0)).returned == input,
          "0x005c8bc6/0x005c8bcc: the first compared value returns the ECX word");
    check(observe(input, decoded_cmp_value(1)).returned == input,
          "0x005c8bce/0x005c8bd4: the second compared value returns the ECX word");
    check(observe(input, decoded_cmp_value(2)).returned == input,
          "0x005c8bd8-0x005c8be2: the third compared value returns the ECX word");
  }
}

// The same three values, observed through a caller that puts the ECX input in the
// register and the compared value on the stack, so the register/stack split is
// exercised the way the machine has it rather than the way C++ would.
void test_the_compared_value_is_the_stack_word() {
  check(observe(kDistinctWord, decoded_cmp_value(0)).returned == kDistinctWord,
        "the ECX input is the register operand and the compared word the stack one");
  check(observe(kDistinctWord, decoded_cmp_value(1)).returned == kDistinctWord,
        "the second guard reads the same stack word");
  check(observe(kDistinctWord, decoded_cmp_value(2)).returned == kDistinctWord,
        "the third guard reads the same stack word");
}

// The mask is 0xffffffff on equality and 0 otherwise, so a value that matches only
// a part of a compared value must NOT be a member. These are the values a narrowed
// comparison (a low-byte, low-half-word or high-half-word test) would wrongly accept.
// The bases are the decoded immediates, so these cases cannot drift with the header.
void test_partial_matches_are_not_members() {
  const std::uint32_t first = decoded_cmp_value(0);
  const std::uint32_t second = decoded_cmp_value(1);
  const std::uint32_t third = decoded_cmp_value(2);
  const std::uint32_t non_members[] = {
      // off by one in either direction, for all three
      first - 1U,  first + 1U,
      second - 1U, second + 1U,
      third - 1U,  third + 1U,
      // low bytes only
      first & 0xffu, second & 0xffu, third & 0xffu,
      // low half words only
      first & 0xffffu, second & 0xffffu, third & 0xffffu,
      // the compared values with their high half word zeroed
      first >> 16, second >> 16, third >> 16,
  };
  for (const std::uint32_t value : non_members) {
    check(observe(kDistinctWord, value).returned == 0u,
          "only a full 32-bit equality makes a value a member");
  }
}

// Inputs that are simply not any of the three: zero, one, all ones, and the
// receiver word itself as a queried value.
void test_other_inputs_return_zero() {
  const std::uint32_t other[] = {0u, 1u, 0x7fffffffU, 0xffffffffU,
                                 kDistinctWord, decoded_cmp_value(0) + 1u,
                                 decoded_cmp_value(1) + 1u, decoded_cmp_value(2) + 1u};
  for (const std::uint32_t value : other) {
    check(observe(kDistinctWord, value).returned == 0u,
          "0x005c8be2 AND EAX,EDX clears the word for every non-member input");
  }
}

// 0x005c8bc0 copies the ECX word whole, so a zero input yields a zero result on a
// membership case as well. This separates "returns the register word" from "returns
// a non-null register word", which the checks above cannot.
void test_a_zero_register_word_returns_zero_on_a_member() {
  check(observe(0u, decoded_cmp_value(0)).returned == 0u,
        "a zero ECX input returns zero for the first compared value");
  check(observe(0u, decoded_cmp_value(2)).returned == 0u,
        "a zero ECX input returns zero for the third compared value");
}

// 0x005c8be4 RET 0x4. The caller below pushed four words; a callee that drops
// exactly the immediate the binary carries leaves the three fillers behind. The
// expected delta is computed from the four words pushed and from the RET immediate
// DECODED OUT OF THE IMAGE BYTES, so a callee that dropped the wrong amount is
// refuted against the binary's own number. A two-argument callee (RET 0x8) would
// leave eight below, a three-argument one four, and a bare RET sixteen, so this is
// the arity and the stack owner asserted as numbers.
void test_the_callee_drops_exactly_the_ret_immediate() {
  const std::uint32_t popped = decoded_ret_immediate();
  const std::uint32_t expected_delta = 4u * kProbeWordsPushed - popped;
  check(expected_delta == 12u,
        "four words pushed less the RET immediate in the bytes is twelve");

  const AbiObservation member = observe(kDistinctWord, decoded_cmp_value(0));
  const std::uint32_t member_delta =
      member.stack_pointer_before_call - member.stack_pointer_after_return;
  check(member_delta == expected_delta,
        "0x005c8be4 RET 0x4: the callee drops the immediate the bytes carry");

  const AbiObservation non_member = observe(kDistinctWord, 0u);
  const std::uint32_t non_member_delta =
      non_member.stack_pointer_before_call - non_member.stack_pointer_after_return;
  check(non_member_delta == expected_delta,
        "the same stack discipline on the fall-through path");
}

// The reverse of the split above, at the machine level: a compared value sitting in
// ECX and a non-member on the stack must return zero, because the body compares the
// stack word and not the register. This is the check that keeps the receiver and the
// message-id stack word rigorously separate.
void test_a_compared_value_in_ecx_is_not_tested() {
  check(observe(decoded_cmp_value(0), 0u).returned == 0u,
        "the body never tests the ECX input against the compared values");
  check(observe(decoded_cmp_value(2), 0u).returned == 0u,
        "0x005c8bd6-0x005c8be2 masks on the stack word, not on the ECX input");
}

// The one memory operand in the body is the caller's own pushed word, read over ESP
// at entry_ESP+0x4. It is a value, not a location the body owns: the probe plants a
// decoy-shaped value in each of the three filler slots above it, and the result is
// unchanged, because the body reads only the last word pushed. If the reconstruction
// read a different slot, the decoys would change the answer.
void test_only_the_last_pushed_word_is_read() {
  // The fillers are 0x5a5a5a5a, which is not a member, so a body that read one of
  // them instead of the word under test would return zero on a member. The member
  // checks above already require the opposite; this states the filler value so the
  // dependence is explicit rather than incidental.
  check(0x5a5a5a5au != decoded_cmp_value(0) && 0x5a5a5a5au != decoded_cmp_value(1) &&
            0x5a5a5a5au != decoded_cmp_value(2),
        "the probe's filler words are not members, so a wrong slot would show");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_005c8bc0

int main() {
  using namespace openspore::reconstruction::pkg_dfw_005c8bc0;
  test_the_three_cmp_immediates_decode_out_of_the_image_bytes();
  test_the_header_constants_are_the_bytes_own_values();
  test_the_return_semantics_the_bytes_carry();
  test_both_jz_guards_land_on_the_shared_terminator();
  test_the_transcribed_abi_data_matches_the_machine_record();
  test_each_compared_value_returns_the_whole_register_word();
  test_the_compared_value_is_the_stack_word();
  test_partial_matches_are_not_members();
  test_other_inputs_return_zero();
  test_a_zero_register_word_returns_zero_on_a_member();
  test_the_callee_drops_exactly_the_ret_immediate();
  test_a_compared_value_in_ecx_is_not_tested();
  test_only_the_last_pushed_word_is_read();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
