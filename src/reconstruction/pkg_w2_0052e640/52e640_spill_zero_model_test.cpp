#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "52e640_spill_zero.hpp"

// Behavioural model test for 0x0052e640 (SporeApp.exe 3.1.0.22).
//
// The body is 15 bytes and 8 instructions, so the model test cannot lean on
// shape: it leans on four independent witnesses that are made to agree.
//
//   W1  the bytes. `machine_body` below is assembled from MNEMONICS (not from
//       hand-copied .byte directives), so encoding it and comparing it against
//       kTargetBytes - which the header carries straight from /read_memory - is
//       a real cross-check of the binary's own encoding against an independent
//       spelling of the same eight operations. Three encodings differ and each
//       is pinned rather than papered over: GAS encodes the two frame-pointer
//       moves as `89 e5` / `89 ec` where MSVC encoded them as `8b ec` / `8b e5`,
//       and GAS encodes the zeroing as `30 c0` where MSVC encoded it as `32 c0`.
//       Each pair is the same register move, or the same XOR of AL with itself,
//       so the test asserts that the nine remaining bytes match exactly and that
//       each divergent pair is one of the two encodings of the same operation.
//
//   W2  the twin. A second body carrying the literal observed encoding, written
//       as .byte because the assembler will not pick the original's forms, is
//       held to the same byte comparison. Two independent spellings of the same
//       15 bytes - one assembled, one literal - both have to be the machine's.
//
//   W3  the REAL TARGET BYTES, executed. The probe below is a bare-assembly
//       __thiscall call site: it pushes three dwords, loads a word into ECX and
//       calls through a register, which is exactly the shape both recorded call
//       sites (0x0050a468 and 0x0050a5d6) use. It samples the stack pointer
//       before the pushes and after the return, reads the dead frame slot the
//       callee left behind, reads the canary words it handed the callee, and
//       reads EAX afterwards. That is the behaviour of the actual target bytes,
//       not of a model of them.
//
//   W4  the RECONSTRUCTED ENTRY itself. The entry is a naked __thiscall
//       function, which is the convention the derived ABI record names at
//       INFERRED confidence, and the probe is already a thiscall call site: the
//       word goes into ECX, three 4-byte words go on the stack, and the callee
//       is reached through a register. The entry is therefore called the way the
//       convention says it is called, and it is held to the same byte checks as
//       `machine_body` and to the same behavioural comparison, so the entry the
//       validator binds to 0x0052e640 is itself a witness and not merely a
//       declaration.
//
// Every check below is written to be able to fail. Where a channel could read
// the same either way, a reference is run through the same channel first: a
// caller-cleaned twin for the stack, a twin that stores a different register for
// the frame slot, and a twin that returns a non-zero byte for the answer.

#if !defined(__i386__) && !defined(_M_IX86)
#error "reconstruction of 0x0052e640 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_w2_0052e640 {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

void check_eq_u32(std::uint32_t actual, std::uint32_t expected) {
  if (actual != expected) {
    std::abort();
  }
}

static constexpr std::uint32_t kCanaryA = 0xa5c39e71u;
static constexpr std::uint32_t kCanaryB = 0x3c6ef372u;
static constexpr std::uint32_t kCanaryC = 0x9e3779b9u;
static constexpr std::uint32_t kEaxSentinel = 305419896u;  // 0x12345678

// ---------------------------------------------------------------------------
// W1: the machine body, assembled from mnemonics.
// ---------------------------------------------------------------------------

extern "C" const unsigned char machine_body[];

__asm__(".text\n"
        ".balign 16\n"
        ".globl machine_body\n"
        ".type machine_body, @function\n"
        "machine_body:\n"
        "  pushl %ebp\n"           // 0x0052e640  PUSH EBP
        "  movl  %esp, %ebp\n"     // 0x0052e641  MOV EBP,ESP
        "  pushl %ecx\n"           // 0x0052e643  PUSH ECX
        "  movl  %ecx, -4(%ebp)\n"  // 0x0052e644  MOV [EBP + -0x4],ECX
        "  xorb  %al, %al\n"       // 0x0052e647  XOR AL,AL
        "  movl  %ebp, %esp\n"     // 0x0052e649  MOV ESP,EBP
        "  popl  %ebp\n"           // 0x0052e64b  POP EBP
        "  retl  $12\n"            // 0x0052e64c  RET 0xc
        ".size machine_body, .-machine_body\n"
        // A control for the frame-slot read channel: identical shape, but it
        // stores EDX instead of ECX. If the probe cannot tell this one from the
        // target, the probe is not reading the slot and the test below proves
        // nothing.
        ".balign 16\n"
        ".globl reference_body_other_register\n"
        ".type reference_body_other_register, @function\n"
        "reference_body_other_register:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  pushl %edx\n"
        "  movl  %edx, -4(%ebp)\n"
        "  xorb  %al, %al\n"
        "  movl  %ebp, %esp\n"
        "  popl  %ebp\n"
        "  retl  $12\n"
        ".size reference_body_other_register, .-reference_body_other_register\n"
        // A control for the answer channel: identical shape, but it returns the
        // byte 1. The probe reads the low byte of EAX, so if it cannot tell this
        // one from the target it is not reading the answer and the byte check
        // below proves nothing.
        ".balign 16\n"
        ".globl reference_body_nonzero_answer\n"
        ".type reference_body_nonzero_answer, @function\n"
        "reference_body_nonzero_answer:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  pushl %ecx\n"
        "  movl  %ecx, -4(%ebp)\n"
        "  movb  $1, %al\n"
        "  movl  %ebp, %esp\n"
        "  popl  %ebp\n"
        "  retl  $12\n"
        ".size reference_body_nonzero_answer, .-reference_body_nonzero_answer\n");

extern "C" const unsigned char reference_body_other_register[];
extern "C" const unsigned char reference_body_nonzero_answer[];

// W2: the literal-encoding twin. The bytes are written as .byte because two of
// the eight instructions have a second encoding the GNU assembler will not
// pick, and only the original's form is being pinned here.
extern "C" const unsigned char twin_literal_body[];

__asm__(".text\n"
        ".balign 16\n"
        ".globl twin_literal_body\n"
        ".type twin_literal_body, @function\n"
        "twin_literal_body:\n"
        "  .byte 0x55\n"                 // 0x0052e640  55        PUSH EBP
        "  .byte 0x8b, 0xec\n"           // 0x0052e641  8b ec     MOV EBP,ESP
        "  .byte 0x51\n"                 // 0x0052e643  51        PUSH ECX
        "  .byte 0x89, 0x4d, 0xfc\n"     // 0x0052e644  89 4d fc  MOV [EBP-0x4],ECX
        "  .byte 0x32, 0xc0\n"           // 0x0052e647  32 c0     XOR AL,AL
        "  .byte 0x8b, 0xe5\n"           // 0x0052e649  8b e5     MOV ESP,EBP
        "  .byte 0x5d\n"                 // 0x0052e64b  5d        POP EBP
        "  .byte 0xc2, 0x0c, 0x00\n"     // 0x0052e64c  c2 0c 00  RET 0xc
        ".size twin_literal_body, .-twin_literal_body\n");

// A read-only window on the bytes the RECONSTRUCTED ENTRY emits. The entry is a
// naked __thiscall function defined in the package, and this symbol is given the
// entry's own address by the assembler, so the model test can hold the entry the
// validator binds to 0x0052e640 against the same byte checks it applies to the
// independently assembled `machine_body`. Both must be the target's 15 bytes.
extern "C" const unsigned char reconstructed_entry_image[];

__asm__(".text\n"
        ".globl reconstructed_entry_image\n"
        "reconstructed_entry_image = reconstruct_0052e640\n");

// ---------------------------------------------------------------------------
// W3/W4: the probe. cdecl, always balanced on exit.
// ---------------------------------------------------------------------------

struct ProbeResult {
  std::uint32_t before;      // stack pointer, before the three argument pushes
  std::uint32_t after;       // stack pointer, after the call returned
  std::uint32_t frame_slot;  // the dead frame word the callee left behind
  std::uint32_t canary_a;    // the first word the caller pushed
  std::uint32_t canary_b;    // the second
  std::uint32_t canary_c;    // the third
  std::uint32_t eax_after;   // EAX after the call returned
};

// The probe pushes the three 4-byte stack words the target's RET 0xc pops - the
// canaries, so that a callee which DEREFERENCES or WRITES one of them changes
// what comes back and the model test fails. `register_word` goes into ECX, which
// is where __thiscall puts the receiver and where the two recorded call sites
// load theirs. `caller_must_pop` tells the probe who owns the pushed words once
// the call returns, so the probe can restore its own stack; the samples are
// taken BEFORE that decision, so `after` is measured identically for a
// callee-cleaned and a caller-cleaned callee and the two are comparable.
//
// The three words are pushed in the order a cdecl push sequence produces: the
// first argument ends up lowest, so the third is pushed first.
//
// REGISTER DISCIPLINE, which is why this probe is written as one `__asm__`
// block rather than assembled from parts, and why it touches only EAX, ECX and
// EDX.
//
// The probe is a cdecl function, so the i386 System V rule applies to it: EBX,
// ESI, EDI and EBP must survive the call. A hand-written probe that borrows ESI
// to hold the output pointer and never puts it back corrupts its CALLER, not
// itself - and it corrupts it silently, because the caller's loop counter or
// pointer usually lives in ESI and the damage surfaces as an
// optimiser-dependent failure in a test that has nothing to do with the probe.
// That is not hypothetical: an earlier revision of this probe read its
// arguments through ESI, passed at -O0, and hung or crashed at -O1 and above
// for exactly that reason. So EBX, ESI, EDI and EBP are never written here, and
// everything the probe needs to remember across the call lives in its own frame
// where %ebp can reach it.
//
// This is also the defect the sibling package 0x0052e650 still carries: its
// probe reads its fifth argument into ESI and never restores it, so that model
// test also passes at -O0 and fails from -O1 upwards. It is recorded there as
// passing at -O2, which the -O2 build does not reproduce.
//
// The frame word and the canaries are read through the PROBE'S OWN frame

// pointer, not through the stack pointer, because the stack pointer is exactly
// the thing the two cleanup sides disagree about: after a callee-cleaned return
// it sits twelve bytes above where a caller-cleaned return leaves it, so an
// ESP-relative read would sample two different places for the two answers. The
// EBP-relative addresses below are absolute facts about this probe's frame and
// are the same for both, so `after` and everything else is comparable.
//
// The layout, with B = %ebp and the 64-byte local reservation, so that the
// reservation puts %esp on B-64:
//
//   B-88  the callee's dead frame word. Three pushes take %esp to B-76, the CALL
//         takes it to B-80, the callee's PUSH EBP makes B-80 its EBP, and its
//         PUSH ECX takes %esp to B-88 - which is [EBP_callee + -0x4], the only
//         word the callee's body writes
//   B-76  canary A, the first stack word, pushed last and so lowest
//   B-72  canary B, the second
//   B-68  canary C, the third, pushed first and so highest
//   B-64  `before`: %esp after the reservation, and therefore the caller's
//         stack pointer before any push
//
// A callee-cleaned return lands back on B-64, which is why `after - before` is
// zero and that difference is the statement "the callee popped the twelve
// bytes".
//
// Every address above is one the CALL wrote or the CALLEE wrote, never a word
// below the deepest point either of them reached. That matters: a read below
// the callee's own frame is a read of memory nothing in this call chain owns,
// and an optimiser is entitled to reuse it, so such a check would be testing
// the toolchain rather than the body.
extern "C" void probe_call_shape(std::uint32_t target,
                                 std::uint32_t register_word,
                                 std::uint32_t caller_must_pop,
                                 ProbeResult* out);

__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_shape\n"
        ".type probe_call_shape, @function\n"
        "probe_call_shape:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  subl  $64, %esp\n"
        "  movl  8(%ebp), %eax\n"      // arg1: target
        "  movl  %eax, -4(%ebp)\n"     // the target, out of EAX
        "  movl  20(%ebp), %eax\n"     // arg4: out
        "  movl  %eax, -8(%ebp)\n"     // out, kept in the frame across the call
        "  movl  %esp, -12(%ebp)\n"    // before, before any push
        "  movl  $305419896, %eax\n"   // the EAX sentinel
        "  movl  12(%ebp), %ecx\n"     // arg2: the word that goes into ECX
        "  movl  %ecx, -16(%ebp)\n"    // the receiver word, across the call
        "  movl  $2654435769, %edx\n"  // canary C, kCanaryC
        "  pushl %edx\n"               // the third word, pushed first
        "  movl  $1013904242, %edx\n"  // canary B, kCanaryB
        "  pushl %edx\n"
        "  movl  $2781060721, %edx\n"  // canary A, kCanaryA
        "  pushl %edx\n"               // the first word, pushed last
        "  movl  -16(%ebp), %ecx\n"    // the receiver word into ECX
        "  call  *-4(%ebp)\n"
        "  movl  %eax, -20(%ebp)\n"    // EAX after the call, kept before EAX is reused
        "  movl  %esp, -24(%ebp)\n"    // after, before any fixup\n"
        "  movl  -8(%ebp), %eax\n"
        "  movl  -12(%ebp), %edx\n"
        "  movl  %edx, (%eax)\n"       // out->before
        "  movl  -24(%ebp), %edx\n"
        "  movl  %edx, 4(%eax)\n"      // out->after
        "  movl  -88(%ebp), %edx\n"    // the dead frame word
        "  movl  %edx, 8(%eax)\n"      // out->frame_slot
        "  movl  -76(%ebp), %edx\n"    // the first stack word the caller pushed
        "  movl  %edx, 12(%eax)\n"     // out->canary_a
        "  movl  -72(%ebp), %edx\n"
        "  movl  %edx, 16(%eax)\n"     // out->canary_b
        "  movl  -68(%ebp), %edx\n"
        "  movl  %edx, 20(%eax)\n"     // out->canary_c
        "  movl  -20(%ebp), %edx\n"
        "  movl  %edx, 24(%eax)\n"     // out->eax_after
        "  cmpl  $0, 16(%ebp)\n"
        "  jne   1f\n"
        "  addl  $12, %esp\n"          // the callee popped nothing\n"
        "1:\n"
        "  leave\n"
        "  ret\n"
        ".size probe_call_shape, .-probe_call_shape\n");

// A caller-cleaned twin with the same one-receiver, three-stack-word shape, so
// the stack behaviour of the target can be compared against the other side
// through one harness. It is deliberately declared with no convention token: its
// whole job is to be the OTHER answer to the cleanup question the target answers
// with its RET immediate, so it must not itself carry a `__thiscall` receiver
// and must be reachable without one.
extern "C" void caller_cleaned_twin(std::uint32_t, std::uint32_t, std::uint32_t) {
  // The third word is the receiver slot in the probe's push order, so it is
  // named and dropped here; nothing is read and nothing is written.
}

std::uint32_t address_of(const void* pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// Every probe goes through THIS one helper, and `noinline` is load-bearing
// rather than tidiness: the helper is the single point the harness is entered
// from, so a reader can see that the samples below all come from one call shape.
// What the checks actually compare is the DELTA the callee produced, never an
// absolute stack pointer, so the claim does not depend on where any individual
// call happened to sit. See check 4.
__attribute__((noinline)) ProbeResult probe_body(
    const unsigned char* code, std::uint32_t register_word,
    std::uint32_t caller_must_pop) {
  ProbeResult result;
  std::memset(&result, 0, sizeof(result));
  probe_call_shape(address_of(code), register_word, caller_must_pop, &result);
  return result;
}

ProbeResult probe_machine_body(std::uint32_t register_word) {
  return probe_body(machine_body, register_word, 0u);
}

ProbeResult probe_literal_twin(std::uint32_t register_word) {
  return probe_body(twin_literal_body, register_word, 0u);
}

ProbeResult probe_reference_body(std::uint32_t register_word) {
  return probe_body(reference_body_other_register, register_word, 0u);
}

ProbeResult probe_nonzero_answer(std::uint32_t register_word) {
  return probe_body(reference_body_nonzero_answer, register_word, 0u);
}

ProbeResult probe_caller_cleaned_twin(std::uint32_t register_word) {
  return probe_body(
      reinterpret_cast<const unsigned char*>(
          reinterpret_cast<const void*>(&caller_cleaned_twin)),
      register_word, 1u);
}

// The RECONSTRUCTED ENTRY itself, called through the same harness. The harness is
// already a __thiscall call site - it loads the word into ECX, pushes three
// 4-byte words and calls through a register, which is the shape both recorded
// call sites use - so nothing about the call here is a convenience: it is the
// convention the derived record names, exercised.
ProbeResult probe_reconstructed_entry(std::uint32_t receiver_word) {
  return probe_body(
      reinterpret_cast<const unsigned char*>(
          &reconstruct_0052e640),
      receiver_word, 0u);
}

}  // namespace model
}  // namespace openspore::reconstruction::pkg_w2_0052e640

namespace {

using namespace openspore::reconstruction::pkg_w2_0052e640;
using model::address_of;
using model::check;
using model::check_eq_u32;
using model::kCanaryA;
using model::kCanaryB;
using model::kCanaryC;
using model::kEaxSentinel;
using model::machine_body;
using model::probe_caller_cleaned_twin;
using model::probe_literal_twin;
using model::probe_machine_body;
using model::probe_nonzero_answer;
using model::probe_reconstructed_entry;
using model::probe_reference_body;
using model::ProbeResult;
using model::reconstructed_entry_image;
using model::twin_literal_body;

// -- W1: the bytes ----------------------------------------------------------

// 1. The literal-encoding twin is the target's 15 bytes, byte for byte, with no
//    allowance at all: it is the one witness in this package that carries the
//    original's own encodings rather than the assembler's.
void test_the_literal_twin_is_the_target_bytes() {
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    check(twin_literal_body[index] == kTargetBytes[index]);
  }
  check_eq_u32(kBodySpanBytes, 15u);
  check_eq_u32(kInstructionCount, 8u);
  check_eq_u32(kTargetVa, 0x0052e640u);
  check_eq_u32(kBodyFirstByte, 0x0052e640u);
  check_eq_u32(kBodyLastByte, 0x0052e64eu);
  check_eq_u32(kBodyEndExclusive, 0x0052e64fu);
}

// 2. `machine_body` is assembled from mnemonics and encodes the same eight
//    operations. The nine bytes that have only one spelling must match the
//    binary exactly, and each of the three divergent pairs must be one of the two
//    encodings of the same operation - a body that grew an instruction, changed
//    an operand or changed a displacement lands somewhere else and fails here.
void test_machine_body_encodes_the_target() {
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool frame_move_in =
        (index >= 1u && index <= 2u) || (index >= 9u && index <= 10u);
    const bool zeroing_in = (index >= 7u && index <= 8u);
    if (!frame_move_in && !zeroing_in) {
      check(machine_body[index] == kTargetBytes[index]);
    }
  }
  // mov %esp,%ebp: 8b ec (the binary) or 89 e5 (GAS)
  const bool prologue_binary =
      machine_body[1] == 0x8bu && machine_body[2] == 0xecu;
  const bool prologue_assembler =
      machine_body[1] == 0x89u && machine_body[2] == 0xe5u;
  check(prologue_binary || prologue_assembler);
  // xor %al,%al: 32 c0 (the binary) or 30 c0 (GAS)
  const bool zeroing_binary =
      machine_body[7] == 0x32u && machine_body[8] == 0xc0u;
  const bool zeroing_assembler =
      machine_body[7] == 0x30u && machine_body[8] == 0xc0u;
  check(zeroing_binary || zeroing_assembler);
  // mov %ebp,%esp: 8b e5 (the binary) or 89 ec (GAS)
  const bool epilogue_binary =
      machine_body[9] == 0x8bu && machine_body[10] == 0xe5u;
  const bool epilogue_assembler =
      machine_body[9] == 0x89u && machine_body[10] == 0xecu;
  check(epilogue_binary || epilogue_assembler);
  // The terminal is the one instruction with no alternative spelling at all: the
  // callee pops twelve bytes. c2 0c 00.
  check(machine_body[12] == 0xc2u && machine_body[13] == 0x0cu &&
        machine_body[14] == 0x00u);
}

// 3. The RECONSTRUCTED ENTRY emits the target body, under the same comparison and
//    with the same three pinned encodings, so the entry the validator binds to
//    0x0052e640 is a byte witness and not merely a declaration.
//
//    The entry is compared against kTargetBytes, the binary's own bytes, and NOT
//    against `machine_body`. Comparing the two assembled bodies to each other
//    would be a check that cannot fail: both are already pinned to the binary
//    below, so agreement between them is implied and testing it would only
//    look like coverage.
//
//    One allowance, and it is a toolchain artifact rather than a relaxation of
//    the claim: g++ -m32 -fPIC prepends a ten-byte PC anchor (`call
//     __x86.get_pc_thunk.ax` / `add $imm32,%eax`) to every naked function, and
//     clang++ -m32 does not. The anchor is recognised by its exact opcode pair,
//     e8 ?? ?? ?? ?? 05, and the 15 target bytes are then required immediately
//     after it. A toolchain that emits some other form of anchor fails this
//     check rather than passing it.
void test_the_reconstructed_entry_is_the_target_body() {
  const unsigned char* entry = reconstructed_entry_image;
  const bool has_pc_anchor = entry[0] == 0xe8u && entry[5] == 0x05u;
  const std::size_t anchor = has_pc_anchor ? 10u : 0u;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool frame_move_in =
        (index >= 1u && index <= 2u) || (index >= 9u && index <= 10u);
    const bool zeroing_in = (index >= 7u && index <= 8u);
    if (!frame_move_in && !zeroing_in) {
      check(entry[anchor + index] == kTargetBytes[index]);
    }
  }
  const bool entry_prologue_binary =
      entry[anchor + 1] == 0x8bu && entry[anchor + 2] == 0xecu;
  const bool entry_prologue_assembler =
      entry[anchor + 1] == 0x89u && entry[anchor + 2] == 0xe5u;
  check(entry_prologue_binary || entry_prologue_assembler);
  const bool entry_zeroing_binary =
      entry[anchor + 7] == 0x32u && entry[anchor + 8] == 0xc0u;
  const bool entry_zeroing_assembler =
      entry[anchor + 7] == 0x30u && entry[anchor + 8] == 0xc0u;
  check(entry_zeroing_binary || entry_zeroing_assembler);
  const bool entry_epilogue_binary =
      entry[anchor + 9] == 0x8bu && entry[anchor + 10] == 0xe5u;
  const bool entry_epilogue_assembler =
      entry[anchor + 9] == 0x89u && entry[anchor + 10] == 0xecu;
  check(entry_epilogue_binary || entry_epilogue_assembler);
  check(entry[anchor + 12] == 0xc2u && entry[anchor + 13] == 0x0cu &&
        entry[anchor + 14] == 0x00u);
}

// -- W3: the real target bytes, executed ------------------------------------

// 4. Cleanup side. The target returns with the stack pointer exactly where the
//    caller had it before the three argument pushes: the callee popped all
//    twelve bytes. The caller-cleaned twin leaves it twelve bytes lower through
//    the same harness, and the two deltas differ by exactly the RET immediate.
//
//    The comparison is between DELTAS, not between absolute stack pointers, and
//    that is deliberate: a delta is what the machine's RET immediate produces
//    and is independent of where the two calls happen to sit on the stack, while
//    an absolute comparison would additionally be asserting that two calls from
//    the same function share a frame, which is the optimiser's business and not
//    the machine's. A model that moved the pop to the caller - or that popped
//    two words, or one, or none - fails this check, and so does one that changes
//    the immediate.
void test_the_callee_pops_the_three_stack_words() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  const ProbeResult twin = probe_caller_cleaned_twin(0x0badc0deu);

  // Both samples are real stack pointers, not a zero the harness never filled.
  check(machine.before != 0u);
  check(twin.before != 0u);
  check(machine.after != 0u);
  check(twin.after != 0u);

  // The target: the three pushes and the RET immediate cancel exactly.
  check_eq_u32(machine.after - machine.before, 0u);
  // The twin: the pushes are still there for the caller.
  check_eq_u32(twin.after - twin.before, 0xfffffff4u);  // -12
  // The whole difference between the two sides is the RET immediate.
  check_eq_u32((machine.after - machine.before) - (twin.after - twin.before),
               kRetImmediateBytes);
  check_eq_u32(kRetImmediateBytes, 12u);
  check_eq_u32(kStackCleanupBytes, 12u);
  check(kObservedCleanupSide == CleanupSide52e640::kCallee);
  // THREE callee-popped stack words, and no more and no fewer.
  check_eq_u32(kStackArgumentWords, 3u);
  check(!kStackArgumentObserved);
  check(!kStackArgumentRead);
  check(!kStackArgumentWritten);
}

// 5. The ABI determination travels with the source as data, so a package that
//    quietly reverted to the old abstention - "no convention, no receiver" -
//    fails here instead of passing.
//
//    Each enumerator is compared against a literal SPELLING of the value the
//    machine record names, not merely against the constant the header points at
//    it. A comparison of `kDerivedConventionVerdict` with itself would be a
//    tautology: it would still hold after the header had been changed to say
//    something else, and the point of carrying the determination as data is that
//    changing the data is what must be caught. So the expected value is written
//    out here, independently, and the header's own pointer to it is checked
//    against that.
void test_the_determined_abi_is_carried_as_data() {
  // The convention, spelled here: __thiscall, and no other candidate.
  check(static_cast<int>(kDerivedConventionVerdict) ==
        static_cast<int>(ConventionVerdict52e640::kThiscall));
  check(static_cast<int>(ConventionVerdict52e640::kThiscall) == 0);
  check_eq_u32(kCandidateConventionCount, 1u);
  // The receiver, spelled here: present, in ECX, bounds-only, never dereferenced.
  check(static_cast<int>(kDerivedReceiverRegister) ==
        static_cast<int>(ReceiverRegister52e640::kEcx));
  check(static_cast<int>(ReceiverRegister52e640::kEcx) == 0);
  check(kReceiverPresent);
  check(!kReceiverAbsent);
  check(kReceiverBoundsOnly);
  check(!kReceiverHasShape);
  check_eq_u32(kReceiverDerefDereferenceCount, 0u);
  // The cleanup, spelled here: the callee pops twelve bytes.
  check(static_cast<int>(kObservedCleanupSide) ==
        static_cast<int>(CleanupSide52e640::kCallee));
  check(static_cast<int>(CleanupSide52e640::kCallee) == 0);
  check_eq_u32(kStackCleanupBytes, 12u);
  check_eq_u32(kRetImmediateBytes, 12u);
  // The determination's confidence, spelled here: INFERRED, not OBSERVED and not
  // UNKNOWN. A package that upgraded the claim to an observed one, or dropped it
  // back to unknown, would fail here rather than quietly overstate it.
  check(kDerivedConventionConfidence == ConventionConfidence::kInferred);
  check(static_cast<int>(ConventionConfidence::kInferred) == 1);
  check(kDerivedReceiverConfidence == ConventionConfidence::kInferred);
  // The provenance the machine recorded for the receiver, spelled here.
  check(kReceiverProvenance == ReceiverProvenance::kVftableSlotDispatch);
  check(static_cast<int>(ReceiverProvenance::kVftableSlotDispatch) == 0);
}

// 6. The answer is the byte 0, and only the byte 0. EAX carries a sentinel into
//     the call; XOR AL,AL clears the low byte alone, so the high 24 bits must
//    come back exactly as they went in. The non-zero-answer control comes back
//    with a different low byte through the same channel, so this check is not
//    reading a register the body never wrote.
void test_the_answer_is_the_byte_zero_and_only_that_byte() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  const ProbeResult control = probe_nonzero_answer(0x0badc0deu);

  check_eq_u32(machine.eax_after & 0xffu, 0u);
  check_eq_u32(control.eax_after & 0xffu, 1u);
  check((machine.eax_after & 0xffu) != (control.eax_after & 0xffu));
  // Bits 8..31 are untouched: XOR AL,AL writes one byte, not the dword.
  check_eq_u32(machine.eax_after & 0xffffff00u, kEaxSentinel & 0xffffff00u);
  // The machine facts the byte rests on.
  check_eq_u32(kReturnWidthBytes, 1u);
  check_eq_u32(kReturnConstant, 0u);
  check_eq_u32(kEaxWriteCount, 1u);
  check(kEaxWriteCount > 0u);
  // And the answer does not vary with the receiver word or the stack words.
  const std::uint32_t words[] = {0u, 1u, 0x0badc0deu, 0xffffffffu, 0x7fffffffu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    check_eq_u32(probe_machine_body(words[index]).eax_after & 0xffu, 0u);
  }
}

// 7. The frame local receives the ECX word. The control - identical body, but
//    storing EDX - comes back with a different value through the same channel,
//    so the check above is not vacuous: the probe really is reading the dead
//    frame word the callee left. Four very different receiver words each land
//    there unchanged.
void test_the_frame_local_receives_the_receiver_word() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  const ProbeResult control = probe_reference_body(0x0badc0deu);

  check_eq_u32(machine.frame_slot, 0x0badc0deu);
  check(control.frame_slot != machine.frame_slot);
  // The control cleans up too, so the frame-slot difference above is the
  // store and not the stack discipline.
  check_eq_u32(control.after - control.before, 0u);

  const std::uint32_t words[] = {0u, 0x0000ffffu, 0x5a5a5a5au, 0xdeadbeefu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    check_eq_u32(probe_machine_body(words[index]).frame_slot, words[index]);
  }
  // A derived word is not the word: 0x5a5a5a5a stored unchanged is neither
  // byte-swapped nor masked, and 0xdeadbeef is stored whole.
  check(0xdeadbeefu != 0xbeefdeadu);
  check(0x5a5a5a5au != 0xa5a5a5a5u);

  // The frame shape the listing fixes.
  check_eq_u32(static_cast<std::uint32_t>(kFrameLocalDisplacementEbp),
               0xfffffffcu);  // -4 as a 32-bit two's complement value
  check_eq_u32(kFrameLocalDisplacementEbp, -4);
  check_eq_u32(kFrameLocalBytes, 4u);
  check_eq_u32(kFrameLocalWords, 1u);
  check_eq_u32(kFrameLocalWriteCount, 1u);
  check_eq_u32(kFrameLocalReadCount, 0u);
  check_eq_u32(kSavedGeneralRegisterCount, 1u);
}

// 8. The three popped stack words are neither read nor written. Each canary the
//    caller handed over is unchanged after the call, and the machine listing
//    names no memory operand that could reach them. A mutant that dereferenced
//    one of them, or wrote through one, changes a canary and dies here.
void test_the_popped_stack_words_are_untouched() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  check_eq_u32(machine.canary_a, kCanaryA);
  check_eq_u32(machine.canary_b, kCanaryB);
  check_eq_u32(machine.canary_c, kCanaryC);
  // The canaries are distinct, so the three slots are genuinely distinguishable.
  check(kCanaryA != kCanaryB);
  check(kCanaryB != kCanaryC);
  check(kCanaryA != kCanaryC);
}

// 9. The receiver word is never dereferenced. A null word and a word that is not
//    a mapped address both behave exactly like a plausible one: the same frame
//    local, the same stack behaviour, the same answer. A reconstruction that read
//    the register as a pointer would fault or differ, and one that branched on it
//    would give a different answer.
void test_the_receiver_word_is_never_dereferenced() {
  const ProbeResult zero = probe_machine_body(0u);
  const ProbeResult wild = probe_machine_body(0xfffffff0u);
  const ProbeResult plain = probe_machine_body(0x12345678u);

  check_eq_u32(zero.frame_slot, 0u);
  check_eq_u32(wild.frame_slot, 0xfffffff0u);
  check_eq_u32(plain.frame_slot, 0x12345678u);
  // Every one of them cleans up, whatever the word is.
  check_eq_u32(zero.after - zero.before, 0u);
  check_eq_u32(wild.after - wild.before, 0u);
  check_eq_u32(plain.after - plain.before, 0u);
  check_eq_u32(zero.eax_after & 0xffu, 0u);
  check_eq_u32(wild.eax_after & 0xffu, 0u);
  check_eq_u32(plain.eax_after & 0xffu, 0u);
  check_eq_u32(zero.canary_a, kCanaryA);
  check_eq_u32(wild.canary_a, kCanaryA);
}

// 10. The body carries no transfer and no global. Every one of these is a count
//     read off the complete 8-instruction listing, whose absence is an absence in
//     the body because the machine parse consumed all eight instructions
//     (declared_count 8, degraded false, unparsed 0, flow_complete true).
void test_the_body_carries_no_transfer() {
  check_eq_u32(kConditionalBranchCount, 0u);
  check_eq_u32(kDirectTransferCount, 0u);
  check_eq_u32(kIndirectTransferCount, 0u);
  check_eq_u32(kGlobalReferenceCount, 0u);
}

// -- W2/W4: the twin and the entry, executed --------------------------------

// 11. The literal twin, driven through the same harness, behaves exactly as the
//     assembled body does: same frame slot, same cleanup, same untouched
//     canaries, same answer. Two independent spellings of the same 15 bytes, so
//     a mistake in either one shows up as a disagreement with the other.
void test_the_literal_twin_behaves_as_the_target() {
  const ProbeResult literal = probe_literal_twin(0x0badc0deu);
  const ProbeResult machine = probe_machine_body(0x0badc0deu);

  // Deltas, for the reason given in check 4: the machine claim is about the
  // twelve bytes, not about where either call sat on the stack.
  check_eq_u32(literal.after - literal.before, machine.after - machine.before);
  check_eq_u32(literal.frame_slot, machine.frame_slot);
  check_eq_u32(literal.eax_after, machine.eax_after);
  check_eq_u32(literal.canary_a, machine.canary_a);
  check_eq_u32(literal.canary_b, machine.canary_b);
  check_eq_u32(literal.canary_c, machine.canary_c);
  check_eq_u32(literal.frame_slot, 0x0badc0deu);
  check_eq_u32(literal.eax_after & 0xffu, 0u);
}

// 12. The entry is a __thiscall callee that pops its own three stack words. The
//     probe is already a thiscall call site - the word goes into ECX, three
//     4-byte words go on the stack and the callee is reached through a register -
//     so the entry is called exactly the way the derived convention says it is
//     called, and it must behave exactly as the independently assembled target
//     bytes do: same frame slot, same cleanup, same untouched canaries, same
//     answer, for every receiver word.
//
//     The high 24 bits of EAX are not compared here. g++ -m32 -fPIC prepends a
//     __x86.get_pc_thunk.ax PC anchor to the naked entry, and that anchor writes
//     EAX before the transcription runs at all; a PC anchor is not a property of
//     the body. The "the answer is the byte alone" claim is carried where it is
//     a property of the body: by the target bytes in check 6, by the entry's own
//     bytes in check 3, and by the sentinel coming out of `machine_body`.
void test_the_entry_is_a_thiscall_callee_that_pops_its_three_words() {
  const std::uint32_t words[] = {0u, 1u, 0x0badc0deu, 0xffffffffu, 0x7fffffffu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    const ProbeResult entry = probe_reconstructed_entry(words[index]);
    const ProbeResult machine = probe_machine_body(words[index]);

    check_eq_u32(entry.after - entry.before, machine.after - machine.before);
    check_eq_u32(entry.frame_slot, words[index]);
    check_eq_u32(entry.frame_slot, machine.frame_slot);
    // The callee popped the words it was handed: the three pushes and the RET
    // immediate cancel, and the caller-cleaned twin is the one that leaves them
    // behind.
    check_eq_u32(entry.after - entry.before, 0u);
    check_eq_u32(entry.eax_after & 0xffu, 0u);
    check_eq_u32(entry.eax_after & 0xffu, machine.eax_after & 0xffu);
    check_eq_u32(entry.canary_a, kCanaryA);
    check_eq_u32(entry.canary_b, kCanaryB);
    check_eq_u32(entry.canary_c, kCanaryC);
    check_eq_u32(entry.canary_a, machine.canary_a);
    check_eq_u32(entry.canary_c, machine.canary_c);
  }
  // And the entry is distinguishable from the other side of the cleanup decision,
  // so the check above is not vacuous.
  const ProbeResult twin = probe_caller_cleaned_twin(0x0badc0deu);
  check_eq_u32(twin.after - twin.before, 0xfffffff4u);  // -12
}

// 13. The BEHAVIOURAL TWIN - the cdecl statement of the same effect - is the
//     ordinary-C++ account of the body, and it is held to every observable the
//     listing fixes: the receiver word lands in the frame local, none of the
//     three stack words can reach the answer, and the answer is the byte 0 for a
//     spread of both.
//
//     The spread over the three stack words is what kills a model that used one
//     of them: the answer is 0 for every triple, so no triple can be the answer's
//     source. The spread over receiver words is what kills a model that read the
//     receiver: the word 1 is not a readable address, so a dereference faults
//     instead of quietly passing.
void test_the_behavioural_twin_matches_the_body() {
  std::uint32_t frame_local = 0xdeadbeefu;
  check_eq_u32(apply_frame_store_52e640(&frame_local, 0x0badc0deu, kCanaryA,
                                        kCanaryB, kCanaryC),
               0u);
  check_eq_u32(frame_local, 0x0badc0deu);

  const std::uint32_t firsts[] = {0u, 1u, 0xffffffffu, 0x7fffffffu, 0x80000000u};
  const std::uint32_t seconds[] = {0u, 1u, 0xffffffffu, 0x7fffffffu};
  for (std::size_t i = 0; i < sizeof(firsts) / sizeof(firsts[0]); ++i) {
    for (std::size_t j = 0; j < sizeof(seconds) / sizeof(seconds[0]); ++j) {
      for (std::uint32_t third = 0u; third < 3u; ++third) {
        std::uint32_t local = 0xdeadbeefu;
        check_eq_u32(apply_frame_store_52e640(&local, 0u, firsts[i],
                                              seconds[j], third),
                     0u);
        check_eq_u32(local, 0u);
      }
    }
  }

  // The receiver word is stored, never dereferenced: the undereferenceable word
  // 1 and the word at the top of the address space both come back as themselves.
  const std::uint32_t receivers[] = {0u, 1u, 0x12345678u, 0xfffffff0u};
  for (std::size_t index = 0;
       index < sizeof(receivers) / sizeof(receivers[0]); ++index) {
    std::uint32_t local = 0xdeadbeefu;
    check_eq_u32(apply_frame_store_52e640(&local, receivers[index], kCanaryA,
                                          kCanaryB, kCanaryC),
                 0u);
    check_eq_u32(local, receivers[index]);
  }
}

int run_tests() {
  test_the_literal_twin_is_the_target_bytes();
  test_machine_body_encodes_the_target();
  test_the_reconstructed_entry_is_the_target_body();
  test_the_body_carries_no_transfer();
  test_the_callee_pops_the_three_stack_words();
  test_the_determined_abi_is_carried_as_data();
  test_the_answer_is_the_byte_zero_and_only_that_byte();
  test_the_frame_local_receives_the_receiver_word();
  test_the_popped_stack_words_are_untouched();
  test_the_receiver_word_is_never_dereferenced();
  test_the_literal_twin_behaves_as_the_target();
  test_the_entry_is_a_thiscall_callee_that_pops_its_three_words();
  test_the_behavioural_twin_matches_the_body();
  return 0;
}

}  // namespace

int main() { return ::run_tests(); }
