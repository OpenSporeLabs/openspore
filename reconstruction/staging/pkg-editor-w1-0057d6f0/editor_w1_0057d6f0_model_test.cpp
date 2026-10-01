// PKG-EDITOR-W1-0057D6F0 -- VA 0x0057d6f0
// Behavioural model test for FUN_0057d6f0 @ 0x0057d6f0.
//
// WHAT IS UNDER TEST. Eleven instructions:
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
// The two direct callees are DEFINED HERE, as observers, which is the only way a
// model of a calling body can be tested at all: the body under test has to call
// something, and this package claims nothing about what either callee does
// internally. Each observer records the call, records the exact pointer it was
// handed, and -- so the delegation is visible rather than assumed -- writes a
// signature dword into the object at offset 0, mimicking the one machine fact
// this package has about 0x00579e20 (it installs a table word there as its first
// act). The model body itself must write nothing.
//
// What is asserted, and what fixes it:
//
//   * the teardown at 0x0057d6f3 happens UNCONDITIONALLY and FIRST, before the
//     option word is examined: the trace order is teardown-then-dispose, and the
//     teardown observer records that no dispose had run when it ran;
//   * the dispose at 0x0057d700 happens ONLY when bit 0 of the option word is
//     set, and nothing else about the option word matters: 0x2, 0x100,
//     0x01000000 and 0x80000000 all mean "do not dispose";
//   * both callees receive the receiver UNADJUSTED -- the same pointer, not the
//     head of the fixture, not a base-relative value -- which is checked by
//     handing the model an INTERIOR pointer and requiring that exact pointer back
//     in EAX and in both observer records;
//   * the return value is the receiver, not a callee's result: the observers
//     scribble on the object and the value still comes back unchanged;
//   * the body writes nothing itself: of a 64-byte sentinel fixture, exactly the
//     four bytes the teardown observer wrote change, and nothing else;
//   * the option word is a stack dword at the callee's entry_ESP+0x4 and is read
//     once: a decoy dword pushed below it, at entry_ESP+0x8, changes nothing, and
//     the model never takes its receiver off the stack;
//   * the terminator pops exactly four bytes: ESP is sampled either side of the
//     call, and with a decoy below the argument the stack comes back one dword
//     lower than it went in -- which is the decoy, left for the caller.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction. Each names a
// wrong reconstruction it is aimed at:
//
//   A  the mask is bit 0 and nothing else: 0x2 and 0x100 must not dispose;
//   B  the condition is not inverted: 0x0 must not dispose, 0x1 must;
//   C  the teardown is unconditional and comes first: flags 0 still tears down,
//      and the trace order is fixed;
//   D  both callees get the same pointer the model returns, unadjusted: an
//      interior receiver comes back interior and both observers see it;
//   E  the return value is the receiver, not the callee's: a callee that writes
//      into the object does not change what comes back;
//   F  the body performs no receiver access of its own: only the four bytes the
//      teardown observer wrote move;
//   G  the argument is a stack dword at entry_ESP+0x4 read once: a decoy at
//      entry_ESP+0x8 and a decoy where a cdecl receiver would be are both inert;
//   H  the cleanup is four bytes on the callee side: measured on ESP, not assumed.
//
// WHAT IS NOW SETTLED, AND HOW IT IS CHECKED HERE.
//
// The machine now DETERMINES this target's calling convention. The derived ABI
// record (reconstruction/evidence/0057d6f0/evidence.json, category abi_derived)
// states calling_convention = __thiscall at confidence INFERRED with
// candidate_conventions ["__thiscall"] and ambiguities [], receiver
// {present true, register ECX, provenance vftable_slot_dispatch, bounds_only
// true, shape null}, and cleanup {bytes 4, side callee, evidence "ret 0x4"} at
// OBSERVED. R1-VFT put the receiver in ECX from the vftable slot and C6B named
// __thiscall from the cleanup side plus that register.
//
// That determination is carried here as DATA, in the header's
// kDerivedConventionVerdict / kDerivedConventionConfidence /
// kCandidateConventionCount / kDerivedReceiverRegister / kReceiverProvenance /
// kObservedCleanupSide, and case_abi_travels_as_data checks it against
// independently spelled literals rather than against itself: a check that
// compares a value with its own header pointer survives any edit of the header,
// which is exactly the edit this case exists to catch.
//
// Two properties of that determination are NOT asserted, because they are
// inferences and not observations:
//
//   * that the convention is OBSERVED. It is INFERRED. Nothing in this
//     repository has watched a caller dispatch through the table at
//     0x013f57f8.
//   * that the convention settles what the receiver IS. It does not. __thiscall
//     says the receiver arrives in ECX; this body never dereferences it, so no
//     class, no type, no field and no layout follows.
//
// What is NOT asserted, and why:
//
//   * What either callee does. Both are observers here; the body is under test,
//     not its callees, and the package asserts only the calls' order, arguments
//     and stack discipline.
//   * The receiver's size, layout, members or identity. This body never
//     dereferences the receiver, so no fixture size below is a claim about the
//     object -- it is only room for the observers to write into.
//   * The meaning of the option word, and of the 31 bits this body never reads.
//     Only bit 0 has behaviour here and the test claims nothing else about it.
//   * That the flag word is a receiver, or that the receiver is the flag word.
//     They are kept apart deliberately: the word at entry_ESP+0x4 is data the
//     body reads one bit of and hands to nobody, and ECX is a value the body
//     copies, hands to both callees and returns. Several cases below drive each
//     of them independently, which is what would fail if they were conflated.
//
// NO CHECK HERE COMPARES A VALUE WITH ITSELF. Every expected value is either a
// literal written out in the case, or a byte taken from kTargetBytes in the
// header -- which is the binary's own /read_memory output, not another assembly
// of the same instructions. In particular the emitted bytes of the reconstructed
// entry are compared against kTargetBytes and never against a second assembly,
// because two independently assembled bodies agreeing with each other would be
// implied by both being pinned to the binary and would only look like coverage.

#include "editor_w1_0057d6f0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_editor_w1_0057d6f0 {

// The observation log. It is at namespace scope rather than in an unnamed one so
// that the two observers below -- which must have the C language linkage the
// header declares for them, and so must not be internal-linkage definitions --
// can reach it.
namespace probe {

enum Step : int {
  kStepTeardown = 1,
  kStepDispose = 2,
};

constexpr int kTraceCapacity = 16;

// The signature dword the teardown observer writes into the object at offset 0.
// It is chosen so that a receiver pointer can never equal it, so a test that
// compares the object's first word with the returned pointer is comparing two
// different kinds of value.
constexpr std::uint32_t kTeardownSignature = 0x7e3ad00du;

// The window of the object each observer copies aside on entry, BEFORE it writes
// its signature. It has to be wider than the signature's own four bytes, because
// a store the body made into those four bytes before calling the teardown would
// be invisible in any after-the-call comparison: the teardown's write would land
// on top of it. Copying the window at the moment of the call is the only place
// the pre-call state of the object is still observable.
constexpr std::size_t kObserveWindow = 8u;

struct Trace {
  int steps[kTraceCapacity];
  int count;
  // The pointer each callee was handed, and the dispose count at the moment the
  // teardown ran, so ordering is observed rather than inferred.
  Receiver* teardown_object;
  Receiver* dispose_object;
  int dispose_calls_before_teardown;
  int teardown_calls;
  int dispose_calls;
  // What the object looked like when each callee was entered, and whether that
  // callee ran at all (a null receiver has no window to copy).
  std::uint8_t at_teardown[kObserveWindow];
  std::uint8_t at_dispose[kObserveWindow];
  int teardown_sampled;
  int dispose_sampled;
};

Trace g_trace;

// Copy the first kObserveWindow bytes of the object aside. Called on entry to a
// callee, before that callee writes anything, so it records the state the body
// left the object in -- including on the second call, where the teardown has
// already run and its own signature is expected to be there.
void sample_object(Receiver* object, std::uint8_t* window, int* sampled) {
  if (object == nullptr) {
    *sampled = 0;
    return;
  }
  std::memcpy(window, reinterpret_cast<const void*>(object), kObserveWindow);
  *sampled = 1;
}

// Reset between cases; every case starts from a clean log.
void reset() {
  Trace empty;
  std::memset(&empty, 0, sizeof empty);
  g_trace = empty;
}

void note(int step, Receiver* object) {
  if (step == kStepTeardown) {
    g_trace.teardown_calls += 1;
    g_trace.teardown_object = object;
    g_trace.dispose_calls_before_teardown = g_trace.dispose_calls;
  } else {
    g_trace.dispose_calls += 1;
    g_trace.dispose_object = object;
  }
  if (g_trace.count < kTraceCapacity) {
    g_trace.steps[g_trace.count] = step;
    g_trace.count += 1;
  }
}

}  // namespace probe

// -- the two direct callees, as observers -------------------------------------
//
// teardown_00579e20 is entered with the object in ECX and nothing on the stack.
// dispose_00f47380 is entered with one cdecl dword on the stack. Both signatures
// come from the header, so a mismatch between the model's call and the machine's
// calling shape is a compile error rather than a silent pass.

extern "C" void PKG_EDITOR_W1_0057D6F0_THISCALL teardown_00579e20(Receiver* object) {
  probe::note(probe::kStepTeardown, object);
  if (object != nullptr) {
    // Record the object's first window BEFORE writing, so a store the body made
    // into it earlier is caught even where this signature would mask it.
    probe::sample_object(object, probe::g_trace.at_teardown,
                         &probe::g_trace.teardown_sampled);
    // Mimic the one machine fact about 0x00579e20 this package has: it installs
    // a table word at the object's offset 0 as its first act. Only these four
    // bytes may move, and the model body must not be the one moving them.
    const std::uint32_t signature = probe::kTeardownSignature;
    std::memcpy(reinterpret_cast<void*>(object), &signature, sizeof signature);
  }
}

extern "C" void dispose_00f47380(void* block) {
  Receiver* const object = reinterpret_cast<Receiver*>(block);
  probe::note(probe::kStepDispose, object);
  if (object != nullptr) {
    probe::sample_object(object, probe::g_trace.at_dispose,
                         &probe::g_trace.dispose_sampled);
  }
}

// -- a read-only window on the bytes the RECONSTRUCTED ENTRY emits --------------
//
// The entry is a naked __thiscall function defined in the package's .cpp, and this
// symbol is given the entry's own address by the assembler, so the model test can
// hold the very function the validator binds to 0x0057d6f0 against the binary's
// own thirty bytes (kTargetBytes, transcribed from /read_memory). It is a window,
// not a copy: nothing here writes through it.
//
// The anchor allowance is a toolchain artifact, not a relaxation of the claim. A
// position-independent g++ build may prepend a ten-byte __x86.get_pc_thunk.ax PC
// anchor (e8 ?? ?? ?? ?? 05) to a naked function; clang++ emits none. The anchor
// is recognised by that exact opcode pair and the thirty target bytes are then
// required immediately after it, so a toolchain that emitted some other form of
// anchor fails here instead of passing.
extern "C" const unsigned char reconstructed_entry_image[];

__asm__(".text\n"
        ".globl reconstructed_entry_image\n"
        "reconstructed_entry_image = re_0057d6f0\n");

namespace {

// -- the fixture --------------------------------------------------------------

constexpr std::size_t kFixtureBytes = 64u;
constexpr std::size_t kSentinel = 0xa5u;

struct alignas(4) Fixture {
  std::uint8_t bytes[kFixtureBytes];
};

Fixture make_fixture() {
  Fixture fixture;
  std::memset(fixture.bytes, static_cast<int>(kSentinel), sizeof fixture.bytes);
  return fixture;
}

Receiver* at(Fixture& fixture, std::size_t offset) {
  return reinterpret_cast<Receiver*>(&fixture.bytes[offset]);
}

// How many bytes of the fixture changed, and the lowest one that did.
struct Diff {
  int changed = 0;
  int first_changed = -1;
};

Diff diff_fixture(const Fixture& before, const Fixture& after) {
  Diff diff;
  for (std::size_t index = 0; index < kFixtureBytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    diff.changed += 1;
    if (diff.first_changed < 0) {
      diff.first_changed = static_cast<int>(index);
    }
  }
  return diff;
}

std::uint32_t word_at(const Fixture& fixture, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, fixture.bytes + offset, sizeof value);
  return value;
}

// -- the call harness ---------------------------------------------------------
//
// Everything about the ABI is MEASURED here rather than declared: the receiver
// goes in ECX, the option word is pushed, and ESP and EAX are read back on both
// sides of the call.
//
// REGISTER DISCIPLINE, AND WHY THE PROBE IS ONE `__asm__` BLOCK.
//
// The probe is an i386 SysV cdecl function, so EBX, ESI, EDI and EBP must
// survive it. A hand-written probe that borrows ESI to hold an argument or a
// result and never puts it back corrupts its CALLER, not itself -- and it
// corrupts it silently, because the caller's loop counter or pointer usually
// lives in ESI and the damage surfaces as an optimiser-dependent failure in a
// test that has nothing to do with the probe. That is not hypothetical: an
// earlier revision of the sibling package for 0x0052e650 read its fifth argument
// through ESI, passed at -O0, and fails from -O1 upwards for exactly that
// reason.
//
// So this probe touches ONLY caller-saved registers -- EAX, ECX and EDX -- and
// keeps everything that must survive the call in its OWN frame, where %ebp can
// reach it. EBX is not touched at all, which matters twice over: it is
// callee-saved so a probe must not spend it, and on a PIC i386 build it holds
// the GOT base, so taking it over inside the asm invalidates every address GCC
// forms around it. EBP is used only as the frame pointer this probe establishes
// for itself.
//
// The previous revision of this file kept its two values across the call in ESI
// and EDI and spent EBX as a scratch push register. Both were OUTPUT directions,
// which is the safe direction, but the EBX clobber was a latent PIC hazard and
// the whole thing is unnecessary: one bare block with a frame needs none of it.
//
// The samples are taken through the PROBE'S OWN FRAME POINTER, not through the
// stack pointer, because the stack pointer is exactly the thing the two cleanup
// sides disagree about. The block records ESP BEFORE any push and ESP IMMEDIATELY
// after the call returns, and nothing in between: the difference between the two
// IS the machine's RET immediate, independently of where either call happened to
// sit. A reconstruction that pops too FEW bytes comes back four bytes high, which
// the checks read as a number. One that pops too MANY destroys the return
// address, which no harness can recover: that direction is reported as a crash,
// not as a failed check.
//
// `after` is sampled BEFORE any fixup and the frame is torn down with `leave`,
// so the harness never has to step ESP by a guessed amount and a caller-cleaned
// callee and a callee-cleaned one are compared through exactly the same path.
//
// The block is emitted as its own NOINLINE function. That is a correctness
// requirement found by measurement rather than a precaution: an extended-asm
// block that moves ESP internally while declaring a "memory" clobber is not
// modelled precisely enough by either compiler for the surrounding code's load
// and store motion to be relied upon once the block is inlined. Emitting it as
// its own function bounds its influence to that function, whose only contact
// with the fixtures is through pointers.

#if defined(_MSC_VER)
#define PKG_EDITOR_W1_0057D6F0_NOINLINE __declspec(noinline)
#else
#define PKG_EDITOR_W1_0057D6F0_NOINLINE __attribute__((noinline))
#endif

struct Sample {
  std::uint32_t returned = 0;
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
};

// The value EAX is loaded with immediately before the call, so a body that
// leaves EAX alone can be told from one that writes it.
constexpr std::uint32_t kEaxSentinel = 0x12345678u;

// The primitive. `decoy_word` of 0 pushes no second dword; any other value is
// pushed FIRST, so it ends up ABOVE the option word and lands at the callee's
// entry_ESP + 0x8 -- which is the slot 0x0057d6f8 reads when there is one.
//
//   8(%ebp)  target address, called through a register
//  12(%ebp)  the word that goes into ECX
//  16(%ebp)  the option word, pushed last and so lowest
//  20(%ebp)  the decoy word, or 0 for none
//  24(%ebp)  the Sample to fill
//
// The frame, with B = %ebp and a 48-byte reservation:
//
//   B-4   the target address, held across the call
//   B-8   the output pointer, held across the call
//   B-12  `before`: %esp after the reservation, i.e. the caller's stack pointer
//   B-16  the ECX word, held across the call
//   B-20  the option word, held across the call
//   B-24  the decoy word, held across the call
//   B-28  %eax after the call, captured before EAX is reused
//   B-32  `after`: %esp immediately after the call, before any fixup
//
// Every address above is one this probe wrote or the callee wrote, never a word
// below the deepest point either of them reached.
extern "C" void probe_call_shape(std::uint32_t target, std::uint32_t ecx_word,
                                 std::uint32_t option_word,
                                 std::uint32_t decoy_word, Sample* out);

__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_shape\n"
        ".type probe_call_shape, @function\n"
        "probe_call_shape:\n"
        "  pushl %ebp\n"
        "  movl  %esp, %ebp\n"
        "  subl  $48, %esp\n"
        "  movl  8(%ebp), %eax\n"       // the target
        "  movl  %eax, -4(%ebp)\n"      // ... held in the frame across the call
        "  movl  24(%ebp), %eax\n"      // the output pointer
        "  movl  %eax, -8(%ebp)\n"      // ... likewise
        "  movl  %esp, -12(%ebp)\n"     // before: before any push at all
        "  movl  $305419896, %eax\n"    // the EAX sentinel, 0x12345678
        "  movl  12(%ebp), %ecx\n"      // the word that goes into ECX
        "  movl  %ecx, -16(%ebp)\n"
        "  movl  16(%ebp), %ecx\n"      // the option word
        "  movl  %ecx, -20(%ebp)\n"
        "  movl  20(%ebp), %ecx\n"      // the decoy word
        "  movl  %ecx, -24(%ebp)\n"
        "  cmpl  $-1, -24(%ebp)\n"      // kNoDecoyWord: push nothing extra
        "  jz   1f\n"
        "  pushl -24(%ebp)\n"           // pushed first, so it sits higher
        "1:\n"
        "  pushl -20(%ebp)\n"           // the option word, pushed last and lowest
        "  movl  -16(%ebp), %ecx\n"     // the receiver, into ECX
        "  call *-4(%ebp)\n"
        "  movl  %eax, -28(%ebp)\n"     // EAX after the call, before it is reused
        "  movl  %esp, -32(%ebp)\n"     // after, before any fixup
        "  movl  -8(%ebp), %eax\n"
        "  movl  -28(%ebp), %edx\n"
        "  movl  %edx, (%eax)\n"        // out->returned
        "  movl  -12(%ebp), %edx\n"
        "  movl  %edx, 4(%eax)\n"       // out->esp_before
        "  movl  -32(%ebp), %edx\n"
        "  movl  %edx, 8(%eax)\n"       // out->esp_after
        "  leave\n"
        "  ret\n"
        ".size probe_call_shape, .-probe_call_shape\n");

// Templated so that a FUNCTION pointer converts as readily as an object one:
// `re_0057d6f0` is a thiscall function, and a thiscall pointer does not convert
// to `const void*` implicitly on either compiler.
template <typename T>
std::uint32_t address_of(T pointer) {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

PKG_EDITOR_W1_0057D6F0_NOINLINE Sample run_probe(std::uint32_t target,
                                                  Receiver* receiver,
                                                  OptionWord options,
                                                  OptionWord decoy) {
  Sample sample;
  sample.returned = 0u;
  sample.esp_before = 0u;
  sample.esp_after = 0u;
  probe_call_shape(target,
                   static_cast<std::uint32_t>(
                       reinterpret_cast<std::uintptr_t>(receiver)),
                   options, decoy, &sample);
  return sample;
}

// The reconstructed entry, entered the way __thiscall enters it: the receiver in
// ECX and one dword at the callee's entry_ESP+0x4. Nothing else is pushed.
Sample call_model(Receiver* receiver, OptionWord options) {
  return run_probe(address_of(&re_0057d6f0), receiver, options, kNoDecoyWord);
}

// The same call with a second dword pushed BELOW the option word, so at the
// callee's entry the option word sits at entry_ESP+0x4 and the decoy at
// entry_ESP+0x8. A body that read a second argument, or that read the wrong
// slot, would take the decoy.
Sample call_model_over_a_decoy(Receiver* receiver, OptionWord options,
                               OptionWord decoy, std::uint32_t target) {
  return run_probe(target, receiver, options, decoy);
}

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t actual, std::uint32_t expected,
                  const char* what) {
  if (actual != expected) {
    std::fprintf(stderr, "FAILED: %s -- got 0x%08x, expected 0x%08x\n", what,
                 actual, expected);
    ++g_failures;
  }
}

// -- the byte window ---------------------------------------------------------
//
// The two helpers below read the reconstructed entry's own emitted code. They
// are `noinline` for the same reason the call harness is: an extended-asm block
// is not modelled precisely enough by either compiler for surrounding code motion
// to be relied upon once the block is inlined, and a byte witness the optimiser
// may fold is not a witness.

// The address of the first of the thirty target bytes, i.e. the entry with any
// PC anchor stepped over. An anchor is recognised only by the exact opcode pair
// e8 ?? ?? ?? ?? 05; anything else is treated as no anchor, so a toolchain that
// emitted a different prologue makes the byte comparison below fail on byte 0.

PKG_EDITOR_W1_0057D6F0_NOINLINE const unsigned char* entry_body_base() {
  const unsigned char* const image = reconstructed_entry_image;
  const bool anchored = image[0] == 0xe8u && image[5] == 0x05u;
  return image + (anchored ? 10u : 0u);
}

// Where the CALL rel32 at `offset` (an offset into kTargetBytes, counting from the
// byte after the E8 opcode) actually lands, computed from the emitted bytes. This
// is the independent answer to "is that displacement the binary's": the binary's
// own displacement encodes addresses in a different image and cannot be compared
// numerically, so the constraint is instead that the reconstruction's displacement
// resolves to the callee the machine names for that callsite.
PKG_EDITOR_W1_0057D6F0_NOINLINE std::uint32_t resolve_call_target(
    std::size_t displacement_offset) {
  const unsigned char* const image = entry_body_base();
  std::int32_t displacement = 0;
  std::memcpy(&displacement, image + displacement_offset, sizeof displacement);
  const std::uint32_t next = address_of(image + displacement_offset + 4u);
  return next + static_cast<std::uint32_t>(displacement);
}

// -- the cases ----------------------------------------------------------------

// W -- the bytes. The reconstructed entry must emit the binary's thirty bytes.
//
// Twenty-eight of the thirty positions are compared literally against kTargetBytes,
// which is the /read_memory transcript and not another assembly of the same
// instructions. The other two positions are the rel32 displacements of the two
// CALLs, which are checked by resolve_call_target above rather than skipped; and
// the pair at bytes 1..2 is the one register move the assembler is free to spell
// two ways (8b f1 in the binary, 89 ce from GAS, both `MOV ESI,ECX`), so each
// spelling is accepted and each is pinned as one of the two.
void case_the_entry_emits_the_target_bytes() {
  const unsigned char* const body = entry_body_base();

  // The window is a real, non-zero address; a witness read from address 0 would
  // pass every comparison below for the wrong reason.
  check(address_of(body) != 0u, "W1: the entry has an address");
  check(body[0] != 0u, "W2: and the first target byte was actually read");

  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool register_move = index == kEcxToEsiFirstByte ||
                               index == kEcxToEsiSecondByte ||
                               index == kEsiToEaxFirstByte ||
                               index == kEsiToEaxSecondByte;
    // The eight displacement bytes are not skipped, they are checked elsewhere and
    // by a stronger rule: resolve_call_target below requires each of them to land
    // on the callee the machine names for that callsite, which a literal
    // comparison against another image could never do.
    const bool displacement = index >= kCallRel32FirstOffset &&
                              index < kCallRel32FirstOffset + 4u;
    const bool second_displacement =
        index >= kCallRel32SecondOffset &&
        index < kCallRel32SecondOffset + 4u;
    if (!register_move && !displacement && !second_displacement) {
      check(body[index] == kTargetBytes[index],
            "W3: byte-for-byte the binary's own encoding");
    }
  }
  // MOV ESI,ECX: 8b f1 (the binary, and what clang++ emits) or 89 ce (GAS).
  const bool receiver_copy_binary =
      body[kEcxToEsiFirstByte] == 0x8bu && body[kEcxToEsiSecondByte] == 0xf1u;
  const bool receiver_copy_assembler =
      body[kEcxToEsiFirstByte] == 0x89u && body[kEcxToEsiSecondByte] == 0xceu;
  check(receiver_copy_binary || receiver_copy_assembler,
        "W4: bytes 1..2 are one of the two encodings of MOV ESI,ECX");
  // MOV EAX,ESI: 8b c6 (the binary) or 89 f0 (GAS).
  const bool tail_binary =
      body[kEsiToEaxFirstByte] == 0x8bu && body[kEsiToEaxSecondByte] == 0xc6u;
  const bool tail_assembler =
      body[kEsiToEaxFirstByte] == 0x89u && body[kEsiToEaxSecondByte] == 0xf0u;
  check(tail_binary || tail_assembler,
        "W4b: bytes 24..25 are one of the two encodings of MOV EAX,ESI");
  check(kEcxToEsiFirstByte == 1u && kEcxToEsiSecondByte == 2u &&
            kEsiToEaxFirstByte == 24u && kEsiToEaxSecondByte == 25u,
        "W4c: the two divergent pairs are exactly the two register moves");
  // So twenty of the thirty positions are compared literally, four are the two
  // accepted register-move encodings, and eight are the two rel32 displacements
  // that W7 and W8 resolve. That adds up to thirty and nothing is unaccounted for.
  std::size_t literal = 0;
  for (std::size_t index = 0; index < kBodySpanBytes; ++index) {
    const bool register_move = index == kEcxToEsiFirstByte ||
                               index == kEcxToEsiSecondByte ||
                               index == kEsiToEaxFirstByte ||
                               index == kEsiToEaxSecondByte;
    const bool displacement =
        (index >= kCallRel32FirstOffset && index < kCallRel32FirstOffset + 4u) ||
        (index >= kCallRel32SecondOffset && index < kCallRel32SecondOffset + 4u);
    if (!register_move && !displacement) {
      ++literal;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(literal), 18u,
                "W4d: eighteen of the thirty byte positions are compared literally");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 30u,
                "W4e: and the body is thirty bytes");

  // The two CALLs are E8 forms, and each resolves to the machine's own callee for
  // that callsite. A reconstruction that called anything else, in either order,
  // fails here even though its bytes look right.
  check(body[3] == 0xe8u, "W5: the teardown call is the direct E8 form");
  check(body[16] == 0xe8u, "W6: the dispose call is the direct E8 form");
  check(resolve_call_target(kCallRel32FirstOffset) ==
            address_of(&teardown_00579e20),
        "W7: the first CALL's displacement resolves to teardown_00579e20");
  check(resolve_call_target(kCallRel32SecondOffset) ==
            address_of(&dispose_00f47380),
        "W8: the second CALL's displacement resolves to dispose_00f47380");

  // The three unresolvable positions are pinned individually as well, so the
  // failure of W3 above is legible rather than just "some byte".
  check(body[8] == 0xf6u && body[9] == 0x44u && body[10] == 0x24u &&
            body[11] == 0x08u && body[12] == 0x01u,
        "W9: the flag test is F6 44 24 08 01 -- byte read, byte mask 0x1");
  check(body[13] == 0x74u && body[14] == 0x09u,
        "W10: the conditional branch is JZ with a +9 displacement");
  check(body[21] == 0x83u && body[22] == 0xc4u && body[23] == 0x04u,
        "W11: the caller's cleanup for the second callee is ADD ESP,0x4");

  check(body[26] == 0x5eu, "W13: ESI is restored, not left clobbered");
  check(body[27] == 0xc2u && body[28] == 0x04u && body[29] == 0x00u,
        "W14: the terminator is RET 0x4, the callee-side cleanup itself");
  check(body[0] == 0x56u && body[15] == 0x56u,
        "W15: the entry saves ESI at the top and pushes it for the dispose");
}

// L -- the ABI determination travels with the source as data, so a package that
// quietly reverted to the old abstention -- "no convention, no receiver" -- fails
// here instead of passing.
//
// Every enumerator is compared against a literal SPELLING of the value the machine
// record names, not merely against the constant the header points at it. A
// comparison of a value with the header's own pointer to it would be a tautology:
// it would still hold after the header had been changed to say something else, and
// the whole point of carrying the determination as data is that changing the data
// is what must be caught.
void case_abi_travels_as_data() {
  // The convention, spelled here: __thiscall, and no other candidate.
  check(static_cast<int>(kDerivedConventionVerdict) ==
            static_cast<int>(ConventionVerdict57d6f0::kThiscall),
        "L1: the derived convention is __thiscall");
  check(static_cast<int>(ConventionVerdict57d6f0::kThiscall) == 0,
        "L2: and nothing else is spelled by that enumerator");
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 1u,
                "L2a: __thiscall is the ONLY candidate the record names");
  // The determination is INFERRED, not OBSERVED and not UNKNOWN. A package that
  // upgraded the claim to an observed one, or dropped it back to unknown, dies
  // here rather than quietly over- or under-stating it.
  check(kDerivedConventionConfidence == ConventionConfidence::kInferred,
        "L3: the determination is INFERRED");
  check(static_cast<int>(ConventionConfidence::kUnknown) == 0,
        "L3a: the confidence scale spells UNKNOWN as 0");
  check(static_cast<int>(ConventionConfidence::kInferred) == 1,
        "L3b: and INFERRED as 1, which is not UNKNOWN and not OBSERVED");
  check(static_cast<int>(ConventionConfidence::kObserved) == 2,
        "L3c: and OBSERVED as 2, which this determination is not");

  // The receiver, spelled here: present, in ECX, bounds-only, never dereferenced.
  check(static_cast<int>(kDerivedReceiverRegister) ==
            static_cast<int>(ReceiverRegister57d6f0::kEcx),
        "L4: the receiver register is ECX");
  check(static_cast<int>(ReceiverRegister57d6f0::kEcx) == 0,
        "L4a: and the register enumerator spells ECX, not a second register");
  check(kReceiverPresent, "L5: a receiver is present");
  check(!kReceiverAbsent, "L6: and the record does not say it is absent");
  check(kReceiverBoundsOnly, "L7: bounds only: no layout is claimed");
  check(!kReceiverHasShape, "L8: and no shape");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDereferenceCount), 0u,
                "L8a: the body never dereferences the receiver, so no offset");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 0u,
                "L8b: and the record saw no distinct displacement either");
  // The provenance the machine recorded for the receiver, spelled here.
  check(kReceiverProvenance == ReceiverProvenance57d6f0::kVftableSlotDispatch,
        "L9: the receiver's provenance is vftable_slot_dispatch");
  check(static_cast<int>(ReceiverProvenance57d6f0::kVftableSlotDispatch) == 0,
        "L9a: and the provenance enumerator spells vftable_slot_dispatch");

  // The cleanup, spelled here: the callee pops four bytes.
  check(kObservedCleanupSide == CleanupSide57d6f0::kCallee,
        "L10: the observed cleanup side is the callee");
  check(static_cast<int>(CleanupSide57d6f0::kCallee) == 0,
        "L10a: and the cleanup enumerator spells the callee, not the caller");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 4u,
                "L10b: the cleanup is four bytes");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 4u,
                "L10c: which is the terminator's own immediate");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentWords), 1u,
                "L10d: and there is exactly one callee-popped stack word");
  check(kStackArgumentRead, "L11: the one stack argument is read");
  check(!kStackArgumentWritten, "L12: and never written");

  // The convention and the cleanup are separate facts and are carried separately,
  // which is what lets a package state one without the other. The emitted
  // terminator and the emitted first instruction above are the evidence that the
  // source honours both: a `retl $0` would contradict L10 while still satisfying
  // L1, and W14 is what kills it.
}

// The cleanup side, measured against a cdecl twin through one harness, so that
// "callee pops four bytes" is not only a statement about the RET immediate.
//
// The twin is deliberately declared with NO convention token and no receiver: its
// whole job is to be the other answer to the cleanup question this body answers
// with its terminator, so it must not itself carry a thiscall receiver.
// The value the twin leaves in EAX, so the harness output is deterministic and
// so the twin can be told apart from the entry: the entry returns the receiver,
// and this never can, because this has no receiver at all.
constexpr std::uint32_t kTwinEaxSentinel = 0x5a17c0deu;

extern "C" std::uint32_t cdecl_caller_pops_twin(Receiver* object,
                                                OptionWord options) {
  probe::note(probe::kStepTeardown, object);
  probe::note(probe::kStepDispose, object);
  static_cast<void>(options);
  return kTwinEaxSentinel;
}

void case_cleanup_side_is_measured_not_only_declared() {
  probe::reset();
  Fixture target_fixture = make_fixture();
  const Sample target = call_model_over_a_decoy(
      at(target_fixture, 0), 1u, 0u, address_of(&re_0057d6f0));
  probe::reset();
  Fixture twin_fixture = make_fixture();
  const Sample twin = call_model_over_a_decoy(
      at(twin_fixture, 0), 1u, 0u, address_of(&cdecl_caller_pops_twin));

  // Both samples are real stack pointers, not a zero the harness never filled.
  check(target.esp_before != 0u && twin.esp_before != 0u,
        "M1: both harnesses sampled a real stack pointer");
  // Both sides were handed the SAME two pushes -- the decoy and the option word --
  // so the only thing that differs between the two deltas is what each callee did
  // with them.
  //
  // The target: its two pushes and its own RET immediate leave one word behind.
  check(target.esp_after == target.esp_before - 4u,
        "M2: the entry popped exactly its own four bytes");
  // The twin: a caller-cleaned callee pops nothing, so both words are still there.
  check(twin.esp_after == twin.esp_before - 8u,
        "M3: the cdecl twin leaves both of its words to the caller");
  // The whole difference between the two sides is the RET immediate, and it is
  // the immediate the binary itself carries at 0x0057d70b.
  check_eq_u32((target.esp_after - target.esp_before) -
                   (twin.esp_after - twin.esp_before),
               static_cast<std::uint32_t>(kRetImmediateBytes),
               "M3a: the whole difference between the two sides is the RET immediate");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 4u,
               "M3b: which is the four bytes the binary's terminator names");

  // The two bodies came back through ONE harness, and they did not come back the
  // same. The twin has no receiver and returns its own sentinel; the entry has a
  // receiver and returns it. A harness that never read EAX -- or that read a
  // register the entry never wrote -- could not tell these two apart, so the
  // stack-delta comparison above is not comparing two identical samples.
  check_eq_u32(twin.returned, kTwinEaxSentinel,
               "M4a: the twin returned its own sentinel through the same channel");
  check(reinterpret_cast<Receiver*>(target.returned) == at(target_fixture, 0),
        "M4: the entry returned the receiver while the twin returned its sentinel");
  check(target.returned != twin.returned,
        "M5: and the two answers differ, so the channel is real");
  check(target.returned != kEaxSentinel,
        "M6: the entry wrote EAX, so the value is not the harness's own sentinel");
}

// Baseline. options == 1: both calls, in that order, on the receiver, and the
// receiver comes back.
void case_baseline_both_calls_in_order() {
  probe::reset();
  Fixture fixture = make_fixture();
  const Fixture before = fixture;
  Receiver* const receiver = at(fixture, 0);

  const Sample sample = call_model(receiver, 1u);

  check(probe::g_trace.count == 2, "A1: exactly two calls were made, teardown and dispose");
  check(probe::g_trace.steps[0] == probe::kStepTeardown,
        "A2: the teardown is the first call");
  check(probe::g_trace.steps[1] == probe::kStepDispose,
        "A3: the dispose is the second call");
  check(probe::g_trace.dispose_calls_before_teardown == 0,
        "A4: no dispose had run when the teardown ran, so the teardown is first");
  check(probe::g_trace.teardown_object == receiver,
        "A5: the teardown received the receiver unadjusted");
  check(probe::g_trace.dispose_object == receiver,
        "A6: the dispose received the same receiver, unadjusted");
  check(reinterpret_cast<Receiver*>(sample.returned) == receiver,
        "A7: EAX carries the receiver on the disposing path too");
  check(sample.esp_after == sample.esp_before,
        "A8: ESP is balanced, so the callee popped its one argument word");
  const Diff diff = diff_fixture(before, fixture);
  check(diff.changed == 4, "A9: only the teardown observer's four signature bytes moved");
  check(diff.first_changed == 0, "A10: and they are the object's first word, at offset 0");
  check(word_at(fixture, 0) == probe::kTeardownSignature,
        "A11: the object carries the teardown's signature word, so the call happened");
}

// A -- the mask is bit 0 and nothing else. Each of these is a wrong
// reconstruction's answer: "any nonzero disposes", "bit 1 disposes", "the sign
// bit disposes", "a high byte disposes".
void case_only_bit_zero_matters() {
  struct Case {
    OptionWord options;
    bool expect_dispose;
  };
  const Case cases[] = {
      {0x00000000u, false},  // nothing set
      {0x00000001u, true},   // bit 0 alone
      {0x00000002u, false},  // bit 1 alone -- a "nonzero means dispose" model disposes
      {0x00000003u, true},   // bits 0 and 1 -- bit 0 decides
      {0x00000004u, false},  // bit 2 alone
      {0x00000100u, false},  // byte 1 -- a "nonzero" model disposes
      {0x00010000u, false},  // byte 2
      {0x01000000u, false},  // byte 3
      {0x80000000u, false},  // bit 31 -- a sign-bit model disposes
      {0xdeadbe00u, false},  // a garbage word whose low byte is zero
      {0xdeadbe01u, true},   // a garbage word with bit 0 set in the low byte
      {0xffffffffu, true},   // every bit set
  };
  const int count = static_cast<int>(sizeof cases / sizeof cases[0]);
  for (int index = 0; index < count; ++index) {
    const Case& item = cases[index];
    probe::reset();
    Fixture fixture = make_fixture();
    const Sample sample = call_model(at(fixture, 0), item.options);
    const bool disposed = (probe::g_trace.dispose_calls == 1);
    char label[160];
    std::snprintf(label, sizeof label,
                  "B%d: options 0x%08x %s dispose", index, item.options,
                  item.expect_dispose ? "must" : "must not");
    check(disposed == item.expect_dispose, label);
    std::snprintf(label, sizeof label,
                  "B%d: options 0x%08x tears down unconditionally", index,
                  item.options);
    check(probe::g_trace.teardown_calls == 1, label);
    std::snprintf(label, sizeof label,
                  "B%d: options 0x%08x still returns the receiver", index,
                  item.options);
    check(reinterpret_cast<Receiver*>(sample.returned) == at(fixture, 0), label);
  }
}

// B -- the condition is not inverted. Stated separately from the table above so
// that one wrong-signed reconstruction is named, not merely enumerated.
void case_condition_is_not_inverted() {
  probe::reset();
  Fixture zero = make_fixture();
  const Sample with_zero = call_model(at(zero, 0), 0u);
  check(probe::g_trace.dispose_calls == 0,
        "C1: options 0x00000000 does not dispose, so the condition is not inverted");
  check(probe::g_trace.teardown_calls == 1, "C2: and it still tears down");
  check(reinterpret_cast<Receiver*>(with_zero.returned) == at(zero, 0),
        "C3: and the non-disposing path returns the receiver too");

  probe::reset();
  Fixture one = make_fixture();
  const Sample with_one = call_model(at(one, 0), 1u);
  check(probe::g_trace.dispose_calls == 1, "C4: options 0x00000001 does dispose");
  check(probe::g_trace.count == 2, "C5: so the two-call trace is teardown then dispose");
  check(reinterpret_cast<Receiver*>(with_one.returned) == at(one, 0),
        "C6: and the disposing path returns the same receiver");
}

// C -- the teardown is unconditional and is not a second entry to the same
// conditional. The option word does not gate it, and no value of the option word
// makes it run twice.
void case_teardown_is_unconditional() {
  const OptionWord probes[] = {0u, 1u, 2u, 4u, 0x100u, 0x80000000u, 0xffffffffu};
  const int count = static_cast<int>(sizeof probes / sizeof probes[0]);
  for (int index = 0; index < count; ++index) {
    probe::reset();
    Fixture fixture = make_fixture();
    call_model(at(fixture, 0), probes[index]);
    char label[160];
    std::snprintf(label, sizeof label,
                  "D%d: options 0x%08x still makes the teardown call, once", index,
                  probes[index]);
    check(probe::g_trace.teardown_calls == 1, label);
    std::snprintf(label, sizeof label, "D%d: options 0x%08x makes no third call",
                  index, probes[index]);
    check(probe::g_trace.count == 1 + (probe::g_trace.dispose_calls == 1 ? 1 : 0),
          label);
  }
}

// D -- the pointer. The receiver handed in is an interior pointer of the fixture
// and every observation of it must come back as that same interior pointer. A
// model that adjusted the receiver -- as the entry stubs do, by 0x10, 0x14 and
// 0x04 -- or that passed the fixture head to either callee is refuted here.
void case_receiver_is_passed_and_returned_unadjusted() {
  const std::size_t offsets[] = {0u, 1u, 4u, 8u, 16u};
  const int count = static_cast<int>(sizeof offsets / sizeof offsets[0]);
  for (int index = 0; index < count; ++index) {
    const std::size_t offset = offsets[index];
    probe::reset();
    Fixture fixture = make_fixture();
    Receiver* const receiver = at(fixture, offset);
    const Sample sample = call_model(receiver, 1u);
    char label[160];
    std::snprintf(label, sizeof label,
                  "E%d: a receiver at +%u is what EAX carries, unadjusted", index,
                  static_cast<unsigned>(offset));
    check(reinterpret_cast<Receiver*>(sample.returned) == receiver, label);
    std::snprintf(label, sizeof label,
                  "E%d: and the teardown at +%u got that same pointer", index,
                  static_cast<unsigned>(offset));
    check(probe::g_trace.teardown_object == receiver, label);
    std::snprintf(label, sizeof label, "E%d: and so did the dispose, for +%u", index,
                  static_cast<unsigned>(offset));
    check(probe::g_trace.dispose_object == receiver, label);
  }
}

// E -- the return value is the receiver, not a callee's result. The observer
// writes a signature into the object and the value that comes back is still the
// pointer; and the pointer is not the word the teardown left in the object, which
// is what a model returning the object's first word would give.
void case_return_value_is_the_receiver_not_a_callee_result() {
  probe::reset();
  Fixture fixture = make_fixture();
  Receiver* const receiver = at(fixture, 8);
  const Sample sample = call_model(receiver, 1u);

  check(reinterpret_cast<Receiver*>(sample.returned) == receiver,
        "F1: what came back is the receiver pointer");
  check(word_at(fixture, 8) == probe::kTeardownSignature,
        "F2: the object at the receiver now holds the teardown's signature");
  check(sample.returned != probe::kTeardownSignature,
        "F3: the returned value is not the word the teardown wrote into the object");
  check(reinterpret_cast<Receiver*>(sample.returned) !=
            reinterpret_cast<Receiver*>(&fixture.bytes[0]),
        "F4: and it is not the head of the fixture either");
}

// F -- the body performs no receiver access of its own. The teardown observer
// writes four bytes at the receiver; every other byte of a 64-byte sentinel
// fixture must be untouched, including the bytes before an interior receiver and
// the twelve bytes past its first word.
void case_body_writes_nothing_but_the_callees_effects() {
  probe::reset();
  Fixture fixture = make_fixture();
  const Fixture before = fixture;
  Receiver* const receiver = at(fixture, 4);
  call_model(receiver, 1u);
  const Diff diff = diff_fixture(before, fixture);
  check(diff.changed == 4, "G1: exactly four bytes moved, the teardown's signature");
  check(diff.first_changed == 4, "G2: at the receiver's own offset 0, not the fixture's");
  for (std::size_t index = 0; index < 4; ++index) {
    check(fixture.bytes[index] == kSentinel,
          "G3: no byte before an interior receiver was written");
  }
  for (std::size_t index = 8; index < kFixtureBytes; ++index) {
    check(fixture.bytes[index] == kSentinel, "G4: no byte past the receiver was written");
  }

  // The same on the non-disposing path: the teardown is the only writer there.
  probe::reset();
  Fixture other = make_fixture();
  const Fixture other_before = other;
  call_model(at(other, 4), 0u);
  const Diff other_diff = diff_fixture(other_before, other);
  check(other_diff.changed == 4, "G5: the non-disposing path writes the same four bytes");
  check(probe::g_trace.dispose_calls == 0, "G6: and makes no second call");
}

// G2 -- the same claim from the only place it is observable. A store the body
// made into the object's first four bytes BEFORE the teardown would be invisible
// in any after-the-call comparison, because the teardown observer's signature
// write lands on top of it. So the object is sampled by the callee at the moment
// it is entered: the window must still be the pristine sentinel pattern when the
// teardown runs, and by the time the dispose runs it must hold exactly the
// teardown's four signature bytes and four untouched bytes -- nothing else, and
// no store in between the two calls.
void case_object_is_pristine_until_the_teardown_reaches_it() {
  probe::reset();
  Fixture fixture = make_fixture();
  call_model(at(fixture, 0), 1u);
  check(probe::g_trace.teardown_sampled == 1, "G7: the teardown was sampled");
  check(probe::g_trace.dispose_sampled == 1, "G8: the dispose was sampled");
  for (std::size_t index = 0; index < probe::kObserveWindow; ++index) {
    check(probe::g_trace.at_teardown[index] == static_cast<std::uint8_t>(kSentinel),
          "G9: the object was untouched when the teardown was entered");
  }
  for (std::size_t index = 0; index < 4; ++index) {
    const std::uint8_t expected = static_cast<std::uint8_t>(
        (probe::kTeardownSignature >> (8u * index)) & 0xffu);
    check(probe::g_trace.at_dispose[index] == expected,
          "G10: by the time the dispose ran, the teardown's signature was there");
  }
  for (std::size_t index = 4; index < probe::kObserveWindow; ++index) {
    check(probe::g_trace.at_dispose[index] == static_cast<std::uint8_t>(kSentinel),
          "G11: and the four bytes above it were still pristine, so nothing wrote between the calls");
  }

  // The non-disposing path: the teardown's signature is in the object at the end
  // and no second sample exists, because no second call was made.
  probe::reset();
  Fixture other = make_fixture();
  call_model(at(other, 0), 0u);
  check(probe::g_trace.dispose_sampled == 0, "G12: no dispose means no second sample");
  for (std::size_t index = 0; index < probe::kObserveWindow; ++index) {
    check(probe::g_trace.at_teardown[index] == static_cast<std::uint8_t>(kSentinel),
          "G13: and the object was pristine on the non-disposing path too");
  }
}

// G -- the argument is one stack dword at the callee's entry_ESP+0x4, read once,
// and the receiver is the register. A decoy dword pushed below the option word
// (entry_ESP+0x8) must not reach the model, and a fixture standing where a cdecl
// receiver would sit must never be written.
void case_argument_slot_and_receiver_register() {
  probe::reset();
  Fixture real = make_fixture();
  Fixture decoy = make_fixture();
  Receiver* const real_receiver = at(real, 0);
  // 0x00 in the decoy means "do not dispose"; 1 in the option word means "do". A
  // model that read the wrong slot inverts the answer.
  const Sample sample =
      call_model_over_a_decoy(real_receiver, 1u, 0u, address_of(&re_0057d6f0));

  check(probe::g_trace.dispose_calls == 1,
        "H1: the option word at entry_ESP+0x4 is the one that is read");
  check(probe::g_trace.teardown_object == real_receiver,
        "H2: the receiver is the ECX pointer, not a word off the stack");
  check(probe::g_trace.dispose_object == real_receiver,
        "H3: and the dispose got the ECX pointer too");
  check(reinterpret_cast<Receiver*>(sample.returned) == real_receiver,
        "H4: the returned value is the ECX receiver");
  check(sample.esp_after == sample.esp_before - 4u,
        "H5: the callee popped exactly its own four bytes and left the decoy");
  const Diff decoy_diff = diff_fixture(make_fixture(), decoy);
  check(decoy_diff.changed == 0,
        "H6: a separate fixture standing in for a stack receiver is never written");

  // The inverse: the decoy says dispose, the option word says do not. The model
  // must follow the option word.
  probe::reset();
  Fixture other = make_fixture();
  call_model_over_a_decoy(at(other, 0), 0u, 1u, address_of(&re_0057d6f0));
  check(probe::g_trace.dispose_calls == 0,
        "H7: a dispose-set decoy at entry_ESP+0x8 does not dispose anything");
  check(probe::g_trace.teardown_calls == 1, "H8: and the teardown still runs once");
}

// H -- the cleanup is four bytes and it is on the callee side. ESP is sampled
// either side of the call with nothing below the argument and the balance is
// exact; a body that popped its own argument at the terminator would come back
// four bytes HIGH instead.
void case_cleanup_is_four_bytes_on_the_callee_side() {
  probe::reset();
  Fixture fixture = make_fixture();
  const Sample plain = call_model(at(fixture, 0), 1u);
  check(plain.esp_after == plain.esp_before,
        "I1: ESP is unchanged across the call, so four argument bytes were consumed");
  check(reinterpret_cast<Receiver*>(plain.returned) == at(fixture, 0),
        "I2: and the body really ran to its return");

  probe::reset();
  Fixture other = make_fixture();
  const Sample quiet = call_model(at(other, 0), 0u);
  check(quiet.esp_after == quiet.esp_before,
        "I3: the non-disposing path is balanced by the same four bytes");
  check(kStackCleanupBytes == 4u, "I4: and the package states the cleanup as 4 bytes");
  check(kStackArgumentSlots == 1, "I5: and exactly one stack argument slot");
}

// I -- a null receiver is not special-cased. The listing has no test on the
// receiver at all: it is copied, handed out and returned whatever it is, so a
// model that early-returned on null, or that returned something other than null,
// is refuted.
void case_null_receiver_is_not_special_cased() {
  probe::reset();
  const Sample sample = call_model(nullptr, 1u);
  check(probe::g_trace.teardown_calls == 1, "J1: a null receiver still reaches the teardown");
  check(probe::g_trace.dispose_calls == 1, "J2: and the dispose when the bit is set");
  check(probe::g_trace.teardown_object == nullptr &&
            probe::g_trace.dispose_object == nullptr,
        "J3: both callees receive the null pointer as given");
  check(sample.returned == 0u, "J4: and null is what comes back");
  check(sample.esp_after == sample.esp_before, "J5: with the stack still balanced");

  probe::reset();
  const Sample quiet = call_model(nullptr, 0u);
  check(probe::g_trace.dispose_calls == 0, "J6: a null receiver with the bit clear disposes nothing");
  check(quiet.returned == 0u, "J7: and still returns null");
}

// J -- the extent facts, restated from the listing. The counts are the ones the
// eleven instructions give; the entry stubs, their ECX adjustments and the table
// slot are machine facts read out of the image and are checked here as
// restatements, not as measurements of this body.
void case_machine_extent_constants() {
  check(kInstructionCount == 11, "K1: the body is eleven instructions");
  check(kBodySpanBytes == 30u, "K2: and spans thirty bytes, 0x0057d6f0..0x0057d70d");
  check(kConditionalBranches == 1, "K3: one conditional branch, the JZ at 0x0057d6fd");
  check(kBasicBlockCount == 2, "K4: two basic blocks, the head and the branch target");
  check(kDirectCalleeCount == 2, "K5: two direct callees");
  check(kOptionBit0 == 0x1u, "K6: the tested bit is bit 0 and nothing else");

  check(kThisAdjustingEntryPointCount == 3, "K7: three this-adjusting stubs reach the body");
  check(kThisAdjustingEntryPoints[0] == 0x0057a5a0u &&
            kThisAdjustingEntryPoints[1] == 0x0057a5b0u &&
            kThisAdjustingEntryPoints[2] == 0x0057a5c0u,
        "K8: at 0x0057a5a0, 0x0057a5b0 and 0x0057a5c0");
  check(kThunkThisAdjustments[0] == 0x10u && kThunkThisAdjustments[1] == 0x14u &&
            kThunkThisAdjustments[2] == 0x04u,
        "K9: each subtracting 0x10, 0x14 and 0x04 from ECX before jumping here");
  check(kTableBase == 0x013f57f8u, "K10: the table the body sits in is based at 0x013f57f8");
  check(kOwnSlotDisplacement == 0x08u, "K11: at displacement +0x08, its third slot");
  check(sizeof(void*) == 4u, "K12: the reconstruction is an x86-32 model");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_editor_w1_0057d6f0

int main() {
  using namespace openspore::reconstruction::pkg_editor_w1_0057d6f0;

  case_baseline_both_calls_in_order();
  case_the_entry_emits_the_target_bytes();
  case_abi_travels_as_data();
  case_cleanup_side_is_measured_not_only_declared();
  case_only_bit_zero_matters();
  case_condition_is_not_inverted();
  case_teardown_is_unconditional();
  case_receiver_is_passed_and_returned_unadjusted();
  case_return_value_is_the_receiver_not_a_callee_result();
  case_body_writes_nothing_but_the_callees_effects();
  case_object_is_pristine_until_the_teardown_reaches_it();
  case_argument_slot_and_receiver_register();
  case_cleanup_is_four_bytes_on_the_callee_side();
  case_null_receiver_is_not_special_cased();
  case_machine_extent_constants();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
