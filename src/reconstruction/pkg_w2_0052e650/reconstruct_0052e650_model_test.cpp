#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "reconstruct_0052e650.hpp"

// Behavioural model test for 0x0052e650 (SporeApp.exe 3.1.0.22).
//
// The body is 13 bytes and 7 instructions, so the model test cannot lean on
// shape: it leans on three independent witnesses that are made to agree.
//
//   W1  the bytes. `machine_body` below is assembled from MNEMONICS (not from
//       hand-copied .byte directives), so encoding it and comparing it against
//       kTargetBytes - which the header carries straight from /read_memory - is
//       a real cross-check of the binary's own encoding against an independent
//       spelling of the same seven operations. The one difference that shows up
//       is stated and pinned rather than papered over: GAS encodes the two
//       frame-pointer moves as `89 e5` / `89 ec` where MSVC encoded them as
//       `8b ec` / `8b e5`. Both are the same register-to-register move; the
//       test asserts that the nine remaining bytes match exactly and that the
//       two pairs that differ are 2-byte register moves between EBP and ESP.
//
//   W2  the interpreter. ExecuteTargetImage runs the 13 target bytes over a
//       word-indexed machine state and REPORTS what happened; it never consults
//       the reconstruction. Its counters - how many times the frame local was
//       written, whether the stack word was read or written, whether EAX was
//       written, where the stack pointer ended up - are filled by decoding
//       instructions, so a model that disagrees with them fails.
//
//   W3  the real machine bytes, executed. The probe below pushes a 4-byte
//       stack word, loads a word into ECX and calls `machine_body` through a
//       register, exactly the shape the two recorded call sites use
//       (0x0055c2ca and 0x0055c633 both do PUSH / MOV ECX / CALL). It samples
//       the stack pointer before the push and after the return, reads the dead
//       frame slot the callee left behind, reads the canary it handed the
//       callee as its stack argument, and reads EAX afterwards. That is the
//       behaviour of the actual target bytes, not of a model of them.
//
//   W4  the RECONSTRUCTED ENTRY itself. The entry is a naked __thiscall
//       function, which is the convention the derived ABI record names at
//       INFERRED confidence, and the probe is already a thiscall call site: the
//       word goes into ECX, one 4-byte word goes on the stack, and the callee is
//       reached through a register. The entry is therefore called the way the
//       convention says it is called, and it is held to the same byte checks as
//       `machine_body` and to the same behavioural comparison, so the entry the
//       validator binds to 0x0052e650 is itself a witness and not merely a
//       declaration.
//
// Every check below is written to be able to fail. Where a channel could read
// the same either way, a reference is run through the same channel first: a
// caller-cleaned twin for the stack, a twin that stores a different register
// for the frame slot.

#if !defined(__i386__) && !defined(_M_IX86)
#error "reconstruction of 0x0052e650 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_w2_0052e650 {
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

static constexpr std::uint32_t kCanary = 0xa5c39e71u;
static constexpr std::uint32_t kEaxSentinel = 305419896u;  // 0x12345678

MachineEntry52e650 make_entry(std::uint32_t ecx_word) {
  MachineEntry52e650 entry;
  entry.eax = 0x11111111u;
  entry.ecx = ecx_word;
  entry.edx = 0x22222222u;
  entry.ebx = 0x33333333u;
  entry.esi = 0x44444444u;
  entry.edi = 0x55555555u;
  // A standard EBP-relative frame: the caller's EBP names a word one above
  // the stack pointer the CALL leaves, which is what EBP = ESP + 8 means on
  // this target. The callee's PUSH EBP saves exactly that value and MOV
  // EBP,ESP leaves the callee's EBP naming the same word, so the frame local
  // at [EBP + -0x4] lands one word below it.
  entry.stack_pointer = 8u;  // the return address sits at word index 8
  entry.frame_pointer_word = entry.stack_pointer - 1u;
  entry.return_address_word = 0x00abcdefu;
  entry.argument_word = kCanary;
  return entry;
}

// ---------------------------------------------------------------------------
// W1: the machine body, assembled from mnemonics.
// ---------------------------------------------------------------------------

extern "C" const unsigned char machine_body[];

__asm__(".text\n"
        ".balign 16\n"
        ".globl machine_body\n"
        ".type machine_body, @function\n"
        "machine_body:\n"
        "  pushl %ebp\n"          // 0x0052e650  PUSH EBP
        "  movl  %esp, %ebp\n"    // 0x0052e651  MOV EBP,ESP
        "  pushl %ecx\n"          // 0x0052e653  PUSH ECX
        "  movl  %ecx, -4(%ebp)\n"  // 0x0052e654  MOV [EBP + -0x4],ECX
        "  movl  %ebp, %esp\n"    // 0x0052e657  MOV ESP,EBP
        "  popl  %ebp\n"          // 0x0052e659  POP EBP
        "  retl  $4\n"            // 0x0052e65a  RET 0x4
        ".size machine_body, .-machine_body\n"
        ".balign 16\n"
        ".globl reference_body_other_register\n"
        ".type reference_body_other_register, @function\n"
        "reference_body_other_register:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  pushl %edx\n"
        "  movl  %edx, -4(%ebp)\n"
        "  movl  %ebp, %esp\n"
        "  popl  %ebp\n"
        "  retl  $4\n"
        ".size reference_body_other_register, .-reference_body_other_register\n");

// A control for the frame-slot read channel: identical shape, but it stores
// EDX instead of ECX. If the probe cannot tell this one from the target, the
// probe is not reading the slot and the test below proves nothing.
extern "C" const unsigned char reference_body_other_register[];

// A read-only window on the bytes the RECONSTRUCTED ENTRY emits. The entry is
// a naked __thiscall function defined in the package, and this symbol is given
// the entry's own address by the assembler, so the model test can hold the
// entry the validator binds to 0x0052e650 against the same byte checks it
// applies to the independently assembled `machine_body`. Both must be the
// target's 13 bytes.
extern "C" const unsigned char reconstructed_entry_image[];

__asm__(".text\n"
        ".globl reconstructed_entry_image\n"
        "reconstructed_entry_image = reconstruct_0052e650\n");

// ---------------------------------------------------------------------------
// W3: the probe. cdecl, always balanced on exit.
// ---------------------------------------------------------------------------

struct ProbeResult {
  std::uint32_t before;      // stack pointer word, before the argument push
  std::uint32_t after;       // stack pointer word, after the call returned
  std::uint32_t frame_slot;  // the dead frame word the callee wrote
  std::uint32_t argument;    // the canary the argument pointer still points at
  std::uint32_t eax_after;   // EAX after the call returned
};

// The probe pushes `argument_pointer` as the callee's one 4-byte stack word -
// a pointer, because a pointer is the only kind of argument whose being WRITTEN
// is observable. The canary it points at is read back after the call, so a
// callee that dereferenced and wrote its argument changes it and the model test
// fails. `caller_must_pop` tells the probe who owns the pushed word once the
// call returns, so the probe can restore its own stack; the samples are taken
// BEFORE that decision, so `after` is measured identically for a callee-cleaned
// and a caller-cleaned callee and the two are comparable.
//
// REGISTER DISCIPLINE, which is why this probe is written as one `__asm__` block
// rather than assembled from parts, and why it touches only EAX, ECX and EDX.
//
// The probe is a cdecl function, so the i386 System V rule applies to it: EBX,
// ESI, EDI and EBP must survive the call. A hand-written probe that borrows ESI
// to hold the output pointer and never puts it back corrupts its CALLER, not
// itself - and it corrupts it silently, because the caller's loop counter or
// pointer usually lives in ESI and the damage surfaces as an
// optimiser-dependent failure in a test that has nothing to do with the probe.
// So EBX, ESI, EDI and EBP are never written here, and everything the probe
// needs to remember across the call lives in its own frame where %ebp can reach
// it.
//
// That is not a hypothetical for this package. An earlier revision of this very
// probe read arg4 into EBX and arg5 into ESI, used them to push the argument and
// to write the result word, and never restored either register. EBX and ESI are
// both callee-saved, so the probe was destroying its caller's registers. The
// consequence is a model test that passes at -O0 - where the compiler happens to
// keep its loop counter and pointers on the stack and re-loads them - and that
// aborts from -O1 upwards under both g++ and clang++, where the compiler
// allocates them to EBX/ESI and trusts the callee to preserve them. The failure
// looks like a bug in the reconstruction, because the abort comes from a check
// downstream of a probe that ran perfectly. The sibling package 0x0052e640
// carried the identical defect in its probe and was repaired the same way.
//
// The frame word and the argument canary are read through the PROBE'S OWN frame
// pointer, not through the stack pointer, because the stack pointer is exactly
// the thing the two cleanup sides disagree about: after a callee-cleaned return
// it sits four bytes above where a caller-cleaned return leaves it, so an
// ESP-relative read would sample two different places for the two answers. The
// EBP-relative addresses below are absolute facts about this probe's frame and
// are the same for both, so `after` and everything else is comparable.
//
// The layout, with B = %ebp and the 32-byte local reservation, so that the
// reservation puts %esp on B-32:
//
//   B-48  the callee's dead frame word. The PUSH takes %esp to B-36, the CALL
//         takes it to B-40, the callee's PUSH EBP makes B-40 its EBP, and its
//         PUSH ECX takes %esp to B-48 - which is [EBP_callee + -0x4], the only
//         word the callee's body writes
//   B-36  the callee's one 4-byte stack word: the argument pointer
//   B-32  `before`: %esp after the reservation, and therefore the caller's
//         stack pointer before any push
//   B-24  `eax_after`, B-20 `after`, B-16 the argument pointer, B-12 `before`,
//         B-8 `out`, B-4 the target
//
// A callee-cleaned return lands back on B-32, which is why `after - before` is
// zero and that difference is the statement "the callee popped the four bytes".
//
// Every address above is one the CALL wrote or the CALLEE wrote, never a word
// below the deepest point either of them reached. That matters: a read below the
// callee's own frame is a read of memory nothing in this call chain owns, and an
// optimiser is entitled to reuse it, so such a check would be testing the
// toolchain rather than the body.
extern "C" void probe_call_shape(std::uint32_t target,
                                 std::uint32_t register_word,
                                 std::uint32_t caller_must_pop,
                                 std::uint32_t* argument_pointer,
                                 ProbeResult* out);

__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_shape\n"
        ".type probe_call_shape, @function\n"
        "probe_call_shape:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  subl  $32, %esp\n"
        "  movl  8(%ebp), %eax\n"     // arg1: target
        "  movl  %eax, -4(%ebp)\n"    // the target, out of EAX
        "  movl  24(%ebp), %eax\n"    // arg5: out
        "  movl  %eax, -8(%ebp)\n"    // out, kept in the frame across the call
        "  movl  20(%ebp), %eax\n"    // arg4: the pointer pushed as argument
        "  movl  %eax, -16(%ebp)\n"   // the argument pointer, across the call
        "  movl  %esp, -12(%ebp)\n"   // before\n"
        "  movl  12(%ebp), %ecx\n"    // arg2: the word that goes into ECX
        "  movl  $305419896, %eax\n"  // the EAX sentinel: nothing may write it
        "  movl  -16(%ebp), %edx\n"   // the argument pointer, out of the frame
        "  pushl %edx\n"              // the callee's 4-byte stack argument
        "  call  *-4(%ebp)\n"
        "  movl  %eax, -24(%ebp)\n"  // EAX after the call, before EAX is reused\n"
        "  movl  %esp, -20(%ebp)\n"   // after, before any fixup\n"
        "  movl  -8(%ebp), %eax\n"    // out, back out of the frame\n"
        "  movl  -12(%ebp), %edx\n"
        "  movl  %edx, (%eax)\n"      // out->before\n"
        "  movl  -20(%ebp), %edx\n"
        "  movl  %edx, 4(%eax)\n"     // out->after\n"
        "  movl  -48(%ebp), %edx\n"   // the dead frame word\n"
        "  movl  %edx, 8(%eax)\n"     // out->frame_slot\n"
        "  movl  -16(%ebp), %edx\n"
        "  movl  (%edx), %edx\n"      // the canary the argument points at\n"
        "  movl  %edx, 12(%eax)\n"    // out->argument\n"
        "  movl  -24(%ebp), %edx\n"
        "  movl  %edx, 16(%eax)\n"    // out->eax_after\n"
        "  cmpl  $0, 16(%ebp)\n"      // arg3: caller_must_pop, off the frame\n"
        "  jne   1f\n"
        "  addl  $4, %esp\n"          // the callee popped nothing\n"
        "1:\n"
        "  leave\n"
        "  ret\n"
        ".size probe_call_shape, .-probe_call_shape\n");

// A caller-cleaned twin with the same one-word signature, so the stack
// behaviour of the target can be compared against the other side through one
// harness. It is deliberately declared with no convention token: its whole job
// is to be the OTHER answer to the cleanup question the target answers with its
// RET immediate, so it must not itself carry an `__thiscall` receiver and must
// be reachable without one.
extern "C" void caller_cleaned_twin(std::uint32_t argument_word) {
  (void)argument_word;
}

std::uint32_t address_of(const void* pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

std::uint32_t function_address(void (*code)(std::uint32_t)) {
  return address_of(reinterpret_cast<const void*>(code));
}

ProbeResult probe_machine_body(std::uint32_t register_word) {
  ProbeResult result;
  std::uint32_t canary = kCanary;  // what the argument pointer points at
  std::memset(&result, 0, sizeof(result));
  probe_call_shape(address_of(machine_body), register_word, 0u, &canary,
                   &result);
  return result;
}

ProbeResult probe_caller_cleaned_twin(std::uint32_t register_word) {
  ProbeResult result;
  std::uint32_t canary = kCanary;
  std::memset(&result, 0, sizeof(result));
  probe_call_shape(function_address(caller_cleaned_twin), register_word, 1u,
                   &canary, &result);
  return result;
}

ProbeResult probe_reference_body(std::uint32_t register_word) {
  ProbeResult result;
  std::uint32_t canary = kCanary;
  std::memset(&result, 0, sizeof(result));
  probe_call_shape(address_of(reference_body_other_register), register_word, 0u,
                   &canary, &result);
  return result;
}

// The RECONSTRUCTED ENTRY itself, called through the same harness. The harness
// is already a __thiscall call site - it loads the word into ECX, pushes one
// 4-byte stack word and calls through a register, which is the shape both
// recorded call sites use - so nothing about the call here is a convenience:
// it is the convention the derived record names, exercised.
ProbeResult probe_reconstructed_entry(std::uint32_t receiver_word) {
  ProbeResult result;
  std::uint32_t canary = kCanary;
  std::memset(&result, 0, sizeof(result));
  probe_call_shape(
      address_of(reinterpret_cast<const void*>(reconstruct_0052e650)),
      receiver_word, 0u, &canary, &result);
  return result;
}

}  // namespace model
}  // namespace openspore::reconstruction::pkg_w2_0052e650

namespace {

using namespace openspore::reconstruction::pkg_w2_0052e650;
using model::address_of;
using model::function_address;
using model::caller_cleaned_twin;
using model::check;
using model::check_eq_u32;
using model::kCanary;
using model::kEaxSentinel;
using model::make_entry;
using model::machine_body;
using model::probe_caller_cleaned_twin;
using model::probe_machine_body;
using model::probe_reconstructed_entry;
using model::probe_reference_body;
using model::ProbeResult;
using model::reference_body_other_register;
using model::reconstructed_entry_image;

// -- W1: the bytes ----------------------------------------------------------

// 1. The body the header carries is the body the binary has, byte for byte and
//    instruction for instruction. Every constant here is a claim about the 13
//    bytes, so a package that perturbed one of them dies here.
void test_target_bytes_are_the_listing() {
  check(sizeof(kTargetBytes) == 13u);
  check_eq_u32(kBodySpanBytes, 13u);
  check_eq_u32(kInstructionCount, 7u);
  check_eq_u32(kBodyFirstByte, 0x0052e650u);
  check_eq_u32(kBodyLastByte, 0x0052e65cu);
  check(kTargetBytes[0] == 0x55u);
  check(kTargetBytes[1] == 0x8bu && kTargetBytes[2] == 0xecu);
  check(kTargetBytes[3] == 0x51u);
  check(kTargetBytes[4] == 0x89u && kTargetBytes[5] == 0x4du &&
        kTargetBytes[6] == 0xfcu);
  check(kTargetBytes[7] == 0x8bu && kTargetBytes[8] == 0xe5u);
  check(kTargetBytes[9] == 0x5du);
  check(kTargetBytes[10] == 0xc2u && kTargetBytes[11] == 0x04u &&
        kTargetBytes[12] == 0x00u);
}

// 2. The body carries no transfer of any kind: no near call (0xe8), no near
//    jump (0xe9), no short jump (0xeb), no indirect call/jump group (0xff) and
//    no two-byte opcode prefix (0x0f), which on x86-32 is where every
//    conditional branch lives. The machine dispatch record agrees
//    (dispatch.indirect_calls = 0, vtable_shaped_loads = 0) and the listing
//    has no conditional branch. A model that invented a call, a dispatch or a
//    loop would have to invent one of these bytes.
void test_body_carries_no_transfer() {
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const std::uint8_t byte = kTargetBytes[index];
    check(byte != 0xe8u);  // CALL rel32
    check(byte != 0xe9u);  // JMP rel32
    check(byte != 0xebu);  // JMP rel8
    check(byte != 0xffu);  // CALL/JMP indirect, PUSH/POP segment
    check(byte != 0x0fu);  // two-byte opcode: every conditional branch
  }
  check_eq_u32(kConditionalBranchCount, 0u);
  check_eq_u32(kDirectTransferCount, 0u);
  check_eq_u32(kIndirectTransferCount, 0u);
  check_eq_u32(kGlobalReferenceCount, 0u);
}

// 3. The mnemonic spelling in the model test assembles to the binary's own
//    encoding. Nine of the thirteen bytes must match exactly - the prologue
//    push, the PUSH ECX, the MOV with its ModRM and displacement, the POP and
//    the three terminal RET bytes - so a model test that perturbed a constant,
//    an offset or the terminal immediate dies here. The two frame-pointer
//    moves are held to a weaker, stated claim: both the binary's `8b ec` /
//    `8b e5` and the assembler's `89 e5` / `89 ec` are the same
//    register-to-register move between EBP and ESP, so either is accepted and
//    neither is asserted. That difference is a real fact about this package
//    and it is not papered over; see the package metadata.
void test_machine_body_encodes_the_target() {
  check(sizeof(kTargetBytes) == 13u);
  const unsigned char* emitted = machine_body;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool frame_move_pair =
        (index >= 1u && index <= 2u) || (index >= 7u && index <= 8u);
    if (!frame_move_pair) {
      check(emitted[index] == kTargetBytes[index]);
    }
  }
  const bool entry_is_binary = emitted[1] == 0x8bu && emitted[2] == 0xecu;
  const bool entry_is_assembler = emitted[1] == 0x89u && emitted[2] == 0xe5u;
  check(entry_is_binary || entry_is_assembler);
  const bool leave_is_binary = emitted[7] == 0x8bu && emitted[8] == 0xe5u;
  const bool leave_is_assembler = emitted[7] == 0x89u && emitted[8] == 0xecu;
  check(leave_is_binary || leave_is_assembler);
  // The reference twin is the same shape, differs only in which register the
  // frame word comes from, and cleans up the same way: that is what makes it
  // usable as the control for the frame-slot read channel.
  const unsigned char* control = reference_body_other_register;
  check(control[3] == 0x52u);  // PUSH EDX, against PUSH ECX
  check(control[4] == 0x89u && control[5] == 0x55u && control[6] == 0xfcu);
  check(control[9] == 0x5du);
  check(control[10] == 0xc2u && control[11] == 0x04u && control[12] == 0x00u);
}

// 3b. The bytes the RECONSTRUCTED ENTRY emits are the target's bytes. The
//     entry is what the validator binds to 0x0052e650, so holding it to the
//     same byte checks as the independently assembled `machine_body` is what
//     makes the entry - not merely the model beside it - a claim about these 13
//     bytes. It is also held to `machine_body` itself, so the two
//     transcriptions of the same seven operations cannot drift apart. As in
//     check 3, the nine non-frame-move bytes must match exactly and each of the
//     two frame-move pairs may be either encoding of the same register move.
//
//     One allowance, and it is a toolchain artifact rather than a relaxation
//     of the claim: g++ -m32 -fPIC prepends a ten-byte PC anchor
//     (`call __x86.get_pc_thunk.ax` / `add $imm32,%eax`) to every naked
//     function, and clang++ -m32 does not. The anchor is recognised by its
//     exact opcode pair, e8 ?? ?? ?? ?? 05, and the 13 target bytes are then
//     required immediately after it. A toolchain that emits some other form of
//     anchor fails this check rather than passing it.
void test_the_reconstructed_entry_is_the_target_body() {
  const unsigned char* entry = reconstructed_entry_image;
  const bool has_pc_anchor = entry[0] == 0xe8u && entry[5] == 0x05u;
  const std::size_t anchor = has_pc_anchor ? 10u : 0u;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool frame_move_pair =
        (index >= 1u && index <= 2u) || (index >= 7u && index <= 8u);
    if (!frame_move_pair) {
      check(entry[anchor + index] == kTargetBytes[index]);
    }
    check(entry[anchor + index] == machine_body[index]);
  }
  const bool entry_is_binary =
      entry[anchor + 1] == 0x8bu && entry[anchor + 2] == 0xecu;
  const bool entry_is_assembler =
      entry[anchor + 1] == 0x89u && entry[anchor + 2] == 0xe5u;
  check(entry_is_binary || entry_is_assembler);
  const bool leave_is_binary =
      entry[anchor + 7] == 0x8bu && entry[anchor + 8] == 0xe5u;
  const bool leave_is_assembler =
      entry[anchor + 7] == 0x89u && entry[anchor + 8] == 0xecu;
  check(leave_is_binary || leave_is_assembler);
}

// -- W2: the interpreter ----------------------------------------------------

// 4. Executing the 13 bytes over a machine state reports the body the listing
//    describes: seven instructions consumed, one write of the frame local, no
//    read of it, no read or write of the stack word, no write of EAX, and a
//    stack pointer that lands exactly where the caller's stood before it pushed
//    its argument. That last comparison IS "the callee pops four bytes".
void test_interpreter_reports_the_listing() {
  const MachineEntry52e650 entry = make_entry(0x0badc0deu);
  const MachineExit52e650 exit_code = ExecuteTargetImage(entry);

  check_eq_u32(exit_code.instructions_executed, 7u);
  check_eq_u32(exit_code.frame_local_value, 0x0badc0deu);
  check_eq_u32(exit_code.frame_local_writes, 1u);
  check_eq_u32(exit_code.frame_local_reads, 0u);
  check_eq_u32(exit_code.stack_argument_reads, 0u);
  check_eq_u32(exit_code.stack_argument_writes, 0u);
  check_eq_u32(exit_code.eax_writes, 0u);
  check_eq_u32(exit_code.eax, entry.eax);       // EAX untouched: nothing returned
  check_eq_u32(exit_code.stack_pointer, exit_code.caller_stack_pointer);
  // The value landed exactly one word below the word EBP names at entry, which
  // is what [EBP + -0x4] is in a word-indexed image.
  check_eq_u32(exit_code.frame_local_word_index, entry.frame_pointer_word - 1u);
  // Two words above the return address: the CALL's own word and the word
  // the caller pushed for the callee. Returning here is what popping that
  // word means.
  check(exit_code.stack_pointer == entry.stack_pointer + 2u);
}

// 5. The reconstruction and the machine image agree on every observable, for
//    several register words, including zero and a word that would be an invalid
//    pointer. ECX is never dereferenced, so the answer cannot depend on it -
//    a model that read the register as a pointer would fault or differ here.
void test_reconstruction_matches_the_machine_image() {
  const std::uint32_t words[] = {0u, 1u, 0x0badc0deu, 0xffffffffu, 0x7fffffffu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    const MachineEntry52e650 entry = make_entry(words[index]);
    const MachineExit52e650 machine = ExecuteTargetImage(entry);
    const MachineExit52e650 model = ApplyReconstruction(entry);

    check_eq_u32(model.frame_local_value, machine.frame_local_value);
    check_eq_u32(model.frame_local_value, words[index]);
    check_eq_u32(model.frame_local_writes, machine.frame_local_writes);
    check_eq_u32(model.frame_local_reads, machine.frame_local_reads);
    check_eq_u32(model.stack_argument_reads, machine.stack_argument_reads);
    check_eq_u32(model.stack_argument_writes, machine.stack_argument_writes);
    check_eq_u32(model.eax_writes, machine.eax_writes);
    check_eq_u32(model.eax, machine.eax);
    check_eq_u32(model.frame_pointer_word, machine.frame_pointer_word);
    check_eq_u32(model.frame_local_word_index, machine.frame_local_word_index);
    check_eq_u32(model.stack_pointer, machine.stack_pointer);
    check_eq_u32(model.stack_pointer, model.caller_stack_pointer);
  }
}

// 6. The stored word is the register word, unmodified, and nothing else in the
//    machine state depends on it. Four very different words each land in the
//    frame local unchanged, and the surrounding state - EAX, the stack pointer,
//    the frame pointer, the write/read counters - is identical for all four. A
//    mutant that transformed the word (masked it, byte-swapped it, zeroed it,
//    or stored something derived from it) fails the first loop; a mutant that
//    made the body react to the word (a branch, a test, a conditional store)
//    fails the second.
void test_every_register_word_is_stored_unchanged() {
  const std::uint32_t words[] = {0u, 0x0000ffffu, 0x5a5a5a5au, 0xdeadbeefu};
  MachineExit52e650 first;
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    const MachineEntry52e650 entry = make_entry(words[index]);
    const MachineExit52e650 model = ApplyReconstruction(entry);
    check_eq_u32(model.frame_local_value, words[index]);
    if (index == 0u) {
      first = model;
      continue;
    }
    check_eq_u32(model.eax, first.eax);
    check_eq_u32(model.frame_pointer_word, first.frame_pointer_word);
    check_eq_u32(model.stack_pointer, first.stack_pointer);
    check_eq_u32(model.caller_stack_pointer, first.caller_stack_pointer);
    check_eq_u32(model.frame_local_writes, first.frame_local_writes);
    check_eq_u32(model.frame_local_reads, first.frame_local_reads);
    check_eq_u32(model.stack_argument_reads, first.stack_argument_reads);
    check_eq_u32(model.stack_argument_writes, first.stack_argument_writes);
    check_eq_u32(model.eax_writes, first.eax_writes);
    check_eq_u32(model.instructions_executed, first.instructions_executed);
  }
  // A derived word is not the word: 0x5a5a5a5a stored unchanged is not any of
  // the neighbours, and 0xdeadbeef is stored whole rather than as 0xbeefdead.
  check(0xdeadbeefu != 0xbeefdeadu);
}

// -- W3: the real target bytes, executed ------------------------------------

// 7. Cleanup side. The target returns with the stack pointer exactly where the
//    caller had it before the argument push: the callee popped the word. The
//    caller-cleaned twin leaves it four bytes lower, through the same harness,
//    and the difference between the two is exactly the RET immediate. A model
//    that moved the pop to the caller - or that popped two words, or none -
//    fails this check, and so does one that changes the immediate.
void test_the_callee_pops_the_stack_word() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  const ProbeResult twin = probe_caller_cleaned_twin(0x0badc0deu);

  check(machine.before != 0u);
  check(twin.before != 0u);
  check(machine.before == twin.before);  // same harness, same starting point

  // The target: the push and the RET immediate cancel.
  check_eq_u32(machine.after, machine.before);
  // The twin: the push is still there for the caller.
  check_eq_u32(twin.after, twin.before - 4u);
  // The whole difference between the two sides is the RET immediate.
  check_eq_u32(machine.after - twin.after, kRetImmediateBytes);
  check_eq_u32(kStackCleanupBytes, 4u);
  check(kObservedCleanupSide == CleanupSide52e650::kCallee);
  // The convention the derived record names, and the receiver register it
  // names. Both are carried here as data so a package that quietly reverted to
  // the old abstention fails instead of passing.
  check(kDerivedConventionVerdict == ConventionVerdict52e650::kThiscall);
  check(kDerivedReceiverRegister == ReceiverRegister52e650::kEcx);
  check(kReceiverPresent);
  check(kReceiverBoundsOnly);
}

// 7b. The entry is a __thiscall callee that pops its own stack word. The probe
//     is already a thiscall call site - the word goes into ECX and the callee is
//     reached through a register - so the entry is called exactly the way the
//     derived convention says it is called, and it must behave exactly as the
//     independently assembled target bytes do: same frame slot, same cleanup,
//     same untouched argument, for every receiver word.
//
//     EAX is deliberately not compared here. g++ -m32 -fPIC prepends a
//     __x86.get_pc_thunk.ax PC anchor to the naked entry, and that anchor
//     writes EAX before the transcription runs at all; a PC anchor is not a
//     property of the body. The "nothing is returned" claim is carried where it
//     is a property of the body: by the target bytes in check 3, by the
//     interpreter's zero EAX writes in checks 4 and 10, and by the sentinel
//     coming back out of `machine_body` in check 10.
void test_the_entry_is_a_thiscall_callee_that_pops_its_argument() {
  const std::uint32_t words[] = {0u, 1u, 0x0badc0deu, 0xffffffffu, 0x7fffffffu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    const ProbeResult entry = probe_reconstructed_entry(words[index]);
    const ProbeResult machine = probe_machine_body(words[index]);

    check_eq_u32(entry.before, machine.before);
    check_eq_u32(entry.frame_slot, words[index]);
    check_eq_u32(entry.frame_slot, machine.frame_slot);
    // The callee popped the word it was handed: the push and the RET immediate
    // cancel, and the caller-cleaned twin is the one that leaves it behind.
    check_eq_u32(entry.after, entry.before);
    check_eq_u32(entry.after, machine.after);
    check_eq_u32(entry.argument, kCanary);
    check_eq_u32(entry.argument, machine.argument);
  }
  // And the entry is distinguishable from the other side of the cleanup
  // decision, so the check above is not vacuous.
  const ProbeResult twin = probe_caller_cleaned_twin(0x0badc0deu);
  check_eq_u32(twin.after, twin.before - 4u);
}

// 8. The frame local receives the ECX word. The control - identical body, but
//    storing EDX - comes back with a different value through the same channel,
//    so the check above is not vacuous: the probe really is reading the dead
//    frame word the callee left.
void test_the_frame_local_receives_the_register_word() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  const ProbeResult control = probe_reference_body(0x0badc0deu);

  check_eq_u32(machine.frame_slot, 0x0badc0deu);
  check(control.frame_slot != machine.frame_slot);
  check_eq_u32(control.after, control.before);  // the control cleans up too
}

// 9. The stack argument is neither written nor consumed. The canary word the
//    caller handed over is unchanged after the call, and the machine listing
//    names no memory operand that could read it. A mutant that dereferenced
//    the argument, or wrote through it, changes the canary and dies here.
void test_the_stack_argument_is_untouched() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  check_eq_u32(machine.argument, kCanary);
  check(!kStackArgumentObserved);
  check(!kStackArgumentRead);
  check(!kStackArgumentWritten);
  check_eq_u32(kStackArgumentWords, 1u);
  check_eq_u32(kStackArgumentOrdinal, 1u);
}

// 10. Nothing is returned. EAX carries a sentinel into the call and the same
//     sentinel comes out, so the body wrote no return value; the derived record
//     agrees (return.register = EAX, void_possible, and the interpreter counts
//     zero EAX writes over the whole body). A mutant that returned a value
//     would change EAX here.
void test_nothing_is_returned() {
  const ProbeResult machine = probe_machine_body(0x0badc0deu);
  check_eq_u32(machine.eax_after, kEaxSentinel);
  const MachineExit52e650 exit_code = ExecuteTargetImage(make_entry(0x1234u));
  check_eq_u32(exit_code.eax_writes, 0u);
}

// 11. The register word is never dereferenced. A null word and a word that is
//     not a mapped address both behave exactly like a plausible one: the same
//     frame local, the same stack behaviour, the same EAX. A reconstruction
//     that read the register as a pointer would fault or differ, and one that
//     branched on it would give a different answer.
void test_the_register_word_is_never_dereferenced() {
  const ProbeResult zero = probe_machine_body(0u);
  const ProbeResult wild = probe_machine_body(0xfffffff0u);
  const ProbeResult plain = probe_machine_body(0x12345678u);

  check_eq_u32(zero.frame_slot, 0u);
  check_eq_u32(wild.frame_slot, 0xfffffff0u);
  check_eq_u32(plain.frame_slot, 0x12345678u);
  check_eq_u32(zero.after, zero.before);
  check_eq_u32(wild.after, wild.before);
  check_eq_u32(plain.after, plain.before);
  check_eq_u32(zero.eax_after, kEaxSentinel);
  check_eq_u32(wild.eax_after, kEaxSentinel);
  check_eq_u32(plain.eax_after, kEaxSentinel);
  check_eq_u32(zero.argument, kCanary);
  check_eq_u32(wild.argument, kCanary);
  check_eq_u32(kReceiverDerefDereferenceCount, 0u);
}

// 12. The frame local is one dword at [EBP + -0x4], reserved by PUSH ECX, and
//     never read back. The interpreter puts it exactly one word below the word
//     EBP names at entry, and EBP comes back exactly as it went in.
void test_the_frame_local_is_one_word_below_the_frame_pointer() {
  const MachineEntry52e650 entry = make_entry(0x0badc0deu);
  const MachineExit52e650 exit_code = ExecuteTargetImage(entry);
  check_eq_u32(kFrameLocalDisplacementEbp, -4);
  check_eq_u32(kFrameLocalBytes, 4u);
  check_eq_u32(kFrameLocalWords, 1u);
  check_eq_u32(kFrameLocalWriteCount, 1u);
  check_eq_u32(kFrameLocalReadCount, 0u);
  check_eq_u32(kSavedGeneralRegisterCount, 1u);
  check_eq_u32(exit_code.frame_pointer_word, entry.frame_pointer_word);
}

int run_tests() {
  test_target_bytes_are_the_listing();
  test_body_carries_no_transfer();
  test_machine_body_encodes_the_target();
  test_the_reconstructed_entry_is_the_target_body();
  test_interpreter_reports_the_listing();
  test_reconstruction_matches_the_machine_image();
  test_every_register_word_is_stored_unchanged();
  test_the_callee_pops_the_stack_word();
  test_the_entry_is_a_thiscall_callee_that_pops_its_argument();
  test_the_frame_local_receives_the_register_word();
  test_the_stack_argument_is_untouched();
  test_nothing_is_returned();
  test_the_register_word_is_never_dereferenced();
  test_the_frame_local_is_one_word_below_the_frame_pointer();
  return 0;
}

}  // namespace

int main() { return ::run_tests(); }
