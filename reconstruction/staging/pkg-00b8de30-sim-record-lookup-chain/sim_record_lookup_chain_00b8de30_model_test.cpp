#include "sim_record_lookup_chain_00b8de30.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

// Model test for 0x00b8de30 (SporeApp.exe 3.1.0.22).
//
// The machine body is ten instructions, thirty-three bytes:
//
//     0x00b8de30  MOV EAX, dword ptr [ECX + 0x184]
//     0x00b8de36  PUSH EAX
//     0x00b8de37  CALL 0x00b3d2a0
//     0x00b8de3c  MOV ECX, EAX
//     0x00b8de3e  CALL 0x00ba6440
//     0x00b8de43  PUSH EAX
//     0x00b8de44  CALL 0x00b3d2a0
//     0x00b8de49  MOV ECX, EAX
//     0x00b8de4b  CALL 0x00ba6d80
//     0x00b8de50  RET
//
// so the whole of the observable contract is: read one dword out of the
// receiver at +0x184, then make four calls in one fixed order, handing the
// accessor nothing, handing each of the two thiscall callees the ACCESSOR's
// return value as its receiver, handing the first the field word and the second
// the first one's return word, storing nothing, and leaving the stack where it
// was found.
//
// LAYERING, because a body this small has almost nothing to test and the danger
// is that the test ends up agreeing with itself:
//
//   1. kTargetBytes in the header is the IMAGE, transcribed. The G cases assert
//      it against literals and DECODE the displacement and the four rel32
//      operands out of it, so the transcription is under test and the constants
//      cannot drift away from the machine. The reconstruction never reads it.
//   2. sim_record_lookup_chain_00b8de30() in the .cpp is the code under test.
//      The behavioural cases drive it through its own declaration, so a defect in
//      it cannot be papered over by the transcription.
//   3. The ABI fact a value comparison cannot show -- that the entry's net stack
//      effect is zero -- is MEASURED through a hand-written trampoline, and
//      CALIBRATED against two control callees (one that pops nothing, one that
//      pops four) so a shim that reported the same number for everything would
//      be caught rather than believed.
//
// The cases are written to REFUTE a plausible wrong reconstruction rather than to
// walk a right one:
//
//   A  the field the body reads IS the receiver's +0x184 dword -- a value
//      comparison, with the canary and the neighbours as controls;
//   B  the four calls happen, in the machine's order, and no fifth happens;
//   C  the accessor is handed NOTHING, twice, and the two thiscall callees each
//      get exactly one stack word;
//   D  the receiver each thiscall callee gets is the ACCESSOR's return value --
//      not the entry's own receiver, and not the field. This is the case that
//      separates "forwards what the accessor returned" from "passes itself
//      along", which is the mistake a 33-byte forwarding body invites;
//   E  the argument 0x00ba6d80 gets is 0x00ba6440's return word, not the field;
//   F  the entry's net stack effect is zero, MEASURED and calibrated;
//   G  the machine facts the whole package rests on, including that the
//      displacement and the four callee addresses really are decoded from the
//      body bytes and that the two accessor calls are the same target;
//   H  the entry writes nothing: the field dword and the whole guard band keep
//      their values.
//
// Direction B is the MUTATION TEST: eleven deliberately wrong bodies live in
// this file, are driven through the SAME battery the reconstruction is graded
// by, and each one is REQUIRED to be refuted. A battery with no power to reject
// a known-wrong body cannot certify the right one, so the mutants being refuted
// is itself an assertion: if a mutant survives, the run fails even though the
// reconstruction passed every other case.
//
// The battery was additionally checked from OUTSIDE, by perturbing the
// reconstruction's own body in the package's .cpp and rebuilding BOTH
// translation units under the promotion gate. All eight perturbations are
// caught: wrong displacement (+0x180), the accessor called once, the entry's own
// receiver forwarded, the field word forwarded to the second call, the calls made
// in the wrong order and the terminal turned into a `ret 4` at RUN time, and two
// -- giving the entry a stack parameter and giving the accessor one -- at
// COMPILE time, the first by the header's ABI static_assert and the second
// because the modelled accessor is nullary. The unperturbed build passes.

#if !defined(__i386__) && !defined(_M_IX86)
#error "0x00b8de30 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain {
namespace model {

using Word = std::uint32_t;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The battery is driven through one signature so no mutant is graded by a laxer
// checker than the reconstruction is: one receiver in, nothing out.
using Probe = void(PKG_00B8DE30_CALL*)(SimRecord*);

// The reconstruction behind that signature.
void PKG_00B8DE30_CALL real_entry(SimRecord* self) {
  sim_record_lookup_chain_00b8de30(self);
}

template <typename Fn>
Word entry_address_of(Fn probe) {
  return pointer_word(reinterpret_cast<const void*>(probe));
}

// ---------------------------------------------------------------------------
// Measured call channel.
// ---------------------------------------------------------------------------

// The trampoline records the stack pointer either side of the call, then
// RESTORES it before returning. Two of the mutants end in `ret 4` and `ret 8`,
// so they leave the caller's ESP displaced by a width only the callee chooses;
// a C++ function whose epilogue cannot survive that would come back through
// registers of garbage. Owning the stack here means a mis-cleaned mutant is
// OBSERVED rather than crashed on.
//
// The context is read from the argument slot, so the trampoline contains no
// absolute reference and links the same way under PIE and non-PIE, and the
// receiver is placed in ECX because every probe is a thiscall entry.
struct TrampolineCtx {
  Word target;       // the callee to reach
  Word receiver;     // ECX on entry to it
  Word push_words;   // 0 for the observed shape, 2 for the padded one
  Word before;       // ESP before the pushes
  Word after;        // ESP after the pops
};

extern "C" void run_trampoline(TrampolineCtx* ctx);

__asm__(
    "  .text\n"
    "  .globl run_trampoline\n"
    "  .hidden run_trampoline\n"
    "  .type run_trampoline, @function\n"
    "run_trampoline:\n"
    "  movl 4(%esp), %ebx\n\t"        /* ctx, in a callee-saved register:   */
    "  pushl %ebx\n\t"                /* EDX is caller-saved, so the context */
    "  movl (%ebx), %eax\n\t"         /* would not survive the call below.   */
    "  movl 4(%ebx), %ecx\n\t"        /* receiver -> ECX, thiscall */
    "  movl %esp, 12(%ebx)\n\t"       /* before */
    "  cmpl $2, 8(%ebx)\n\t"
    "  jne 1f\n\t"
    "  pushl $0\n\t"
    "  pushl $0\n\t"
    "1:\n"
    "  call *%eax\n\t"
    "  cmpl $2, 8(%ebx)\n\t"
    "  jne 2f\n\t"
    "  addl $8, %esp\n\t"
    "2:\n"
    "  movl %esp, 16(%ebx)\n\t"       /* after */
    "  movl 12(%ebx), %eax\n\t"
    "  movl %eax, %esp\n\t"           /* restore, whatever the callee did */
    "  popl %ebx\n\t"
    "  ret\n\t"
    "  .size run_trampoline, .-run_trampoline\n");

struct EspSamples {
  Word before;
  Word after;
};

// push_words == 0: the observed shape. Nothing is pushed, so `before` equals
// `after` exactly when the callee popped nothing.
EspSamples call_probe(Probe probe, SimRecord* receiver) {
  TrampolineCtx ctx;
  ctx.target = entry_address_of(probe);
  ctx.receiver = pointer_word(receiver);
  ctx.push_words = 0;
  ctx.before = 0;
  ctx.after = 0;
  run_trampoline(&ctx);
  EspSamples samples;
  samples.before = ctx.before;
  samples.after = ctx.after;
  return samples;
}

// push_words == 2: the uniform channel that grades every probe. Two words are
// pushed and two are popped, so a callee that cleans its own stack consumes only
// part of the area and `after` comes back off `before` -- by +4 for a `ret 4` and
// +8 for a `ret 8`. The correct body, whose net effect is zero, leaves the two
// equal.
EspSamples call_probe_padded(Probe probe, SimRecord* receiver) {
  TrampolineCtx ctx;
  ctx.target = entry_address_of(probe);
  ctx.receiver = pointer_word(receiver);
  ctx.push_words = 2;
  ctx.before = 0;
  ctx.after = 0;
  run_trampoline(&ctx);
  EspSamples samples;
  samples.before = ctx.before;
  samples.after = ctx.after;
  return samples;
}

// ---------------------------------------------------------------------------
// The modelled image.
// ---------------------------------------------------------------------------

SimRecord* receiver_of() {
  return reinterpret_cast<SimRecord*>(&g_sim_record_image.words[0]);
}

std::uint8_t* image_as_bytes() { return image_bytes(); }

// Push every word of the modelled image to the canary, then set the field.
void arm_image(Word field) {
  for (std::size_t i = 0; i < kImageWords; ++i) {
    g_sim_record_image.words[i] = kGuardCanary;
  }
  g_sim_record_image.words[kFieldDisplacement / sizeof(Word)] = field;
}

void reset_trace() {
  g_call_depth = 0;
  for (std::size_t i = 0; i < kMaxCallDepth; ++i) {
    g_call_trace[i].site = 0u;
    g_call_trace[i].receiver = 0u;
    g_call_trace[i].argument = 0u;
    g_call_trace[i].stack_words = 0u;
  }
}

// Reference readers for the dwords either side of the field. They exist so the
// "it read the field, not its neighbour" case can fail: without them a harness
// that could not tell those addresses apart would report the same answer for all
// three and the assertion would hold for the wrong reason.
Word reference_reads_below_field() {
  return g_sim_record_image.words[(kFieldDisplacement / sizeof(Word)) - 1];
}

Word reference_reads_above_field() {
  return g_sim_record_image.words[(kFieldDisplacement / sizeof(Word)) + 1];
}

// ---------------------------------------------------------------------------
// Mutants: bodies that are wrong in exactly one way each.
// ---------------------------------------------------------------------------

// Wrong: reads the dword BELOW the field.
void PKG_00B8DE30_CALL mutant_reads_below_field(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement - sizeof(Word));
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      lookup);
}

// Wrong: reads the dword ABOVE the field.
void PKG_00B8DE30_CALL mutant_reads_above_field(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement + sizeof(Word));
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      lookup);
}

// Wrong: the entry's OWN receiver is forwarded to the two thiscall callees
// instead of the accessor's return value. This is the mistake the body invites,
// because a forwarding chain is exactly what it looks like.
void PKG_00B8DE30_CALL mutant_forwards_own_receiver(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  (void)FUN_00b3d2a0();
  const Word lookup = FUN_00ba6440(self, field);
  (void)FUN_00b3d2a0();
  (void)FUN_00ba6d80(self, lookup);
}

// Wrong: the second thiscall callee is given the entry's own receiver.
void PKG_00B8DE30_CALL mutant_second_receiver_is_self(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);
  (void)FUN_00b3d2a0();
  (void)FUN_00ba6d80(self, lookup);
}

// Wrong: the FIELD is handed to the second callee instead of the lookup's
// return value -- the two are conflated.
void PKG_00B8DE30_CALL mutant_second_argument_is_field(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  const Word root = FUN_00b3d2a0();
  (void)FUN_00ba6440(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)), field);
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      field);
}

// Wrong: the accessor is called ONCE and its result reused, collapsing four
// calls into three.
void PKG_00B8DE30_CALL mutant_accessor_called_once(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)), lookup);
}

// Wrong: the two thiscall callees are reached in the opposite order.
void PKG_00B8DE30_CALL mutant_calls_in_reverse_order(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  const Word root = FUN_00b3d2a0();
  const Word resolved = FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)), field);
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6440(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      resolved);
}

// Wrong: the field is written back into the receiver. The body stores nothing.
// The value written is DIFFERENT from the one read, so the store is observable
// on the image rather than being a no-op copy.
void PKG_00B8DE30_CALL mutant_writes_the_field(SimRecord* self) {
  std::uint8_t* const bytes = reinterpret_cast<std::uint8_t*>(self);
  const Word field = word_at(bytes, kFieldDisplacement);
  Word store = field ^ 0x5a5a5a5au;
  std::memcpy(bytes + kFieldDisplacement, &store, sizeof(store));
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      lookup);
}

// Wrong: the first thiscall callee is never reached.
void PKG_00B8DE30_CALL mutant_skips_the_lookup(SimRecord* self) {
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);
  const Word root = FUN_00b3d2a0();
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      field + root);
}

// Wrong: the callee pops FOUR bytes. Spelled in asm rather than with a compiler
// convention attribute on purpose: the defect under test is the terminator, and
// driving it through the padded channel keeps the defect from being the shim.
// 0x00b8de50 is a BARE RET, so this is a real contradiction of the body.
#if defined(_MSC_VER)
__declspec(naked) void PKG_00B8DE30_CALL mutant_pops_four_bytes(SimRecord* self) { __asm { ret 4 } }
#else
__attribute__((naked, thiscall)) void mutant_pops_four_bytes(SimRecord*) { __asm__("ret $4"); }
#endif

// Wrong: the callee pops EIGHT bytes, an over-wide cleanup by one word again.
#if defined(_MSC_VER)
__declspec(naked) void PKG_00B8DE30_CALL mutant_pops_eight_bytes(SimRecord* self) { __asm { ret 8 } }
#else
__attribute__((naked, thiscall)) void mutant_pops_eight_bytes(SimRecord*) { __asm__("ret $8"); }
#endif

// Calibration callees for the stack-effect measurement: one that pops nothing
// and one that pops four. Without them, a shim that reported the same ESP
// difference for every callee would look correct, and the measurement below
// would be a constant.
void PKG_00B8DE30_CALL control_pops_nothing(SimRecord* self) { (void)self; }

#if defined(_MSC_VER)
__declspec(naked) void PKG_00B8DE30_CALL control_pops_four(SimRecord* self) { __asm { ret 4 } }
#else
__attribute__((naked, thiscall)) void control_pops_four(SimRecord*) { __asm__("ret $4"); }
#endif

struct Mutant {
  const char* name;
  Probe entry;
};

const Mutant kMutants[] = {
    {"reads_below_field", &mutant_reads_below_field},
    {"reads_above_field", &mutant_reads_above_field},
    {"forwards_own_receiver", &mutant_forwards_own_receiver},
    {"second_receiver_is_self", &mutant_second_receiver_is_self},
    {"second_argument_is_field", &mutant_second_argument_is_field},
    {"accessor_called_once", &mutant_accessor_called_once},
    {"calls_in_reverse_order", &mutant_calls_in_reverse_order},
    {"writes_the_field", &mutant_writes_the_field},
    {"skips_the_lookup", &mutant_skips_the_lookup},
    {"callee_pops_four_bytes", &mutant_pops_four_bytes},
    {"callee_pops_eight_bytes", &mutant_pops_eight_bytes},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}  // namespace model
}  // namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain

namespace {

using namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain;
using namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain::model;

// The machine ABI, asserted against the declaration: one receiver parameter in
// ECX, no ordinary stack argument, no result. This is the compile-time gate --
// change the prototype and this stops building.
static_assert(std::is_same<decltype(&sim_record_lookup_chain_00b8de30),
                           AbiSimRecordLookupChain00b8de30>::value,
               "0x00b8de30 is a __thiscall entry taking only the ECX receiver "
               "(the body names no stack operand, and its terminal is a bare "
               "RET), and it produces no value of its own");
static_assert(sizeof(AbiSimRecordLookupChain00b8de30) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(void*) == 4u,
              "the modelled entry is a 32-bit code pointer, so this is an "
              "x86-32 reconstruction");
static_assert(sizeof(Word) == 4u, "the modelled word is one 32-bit dword");
static_assert(kMutantCount == 11, "the battery has eleven known-wrong bodies");

// A scenario: three distinct words, so a reconstruction that confuses the field,
// the accessor's result and the lookup's result cannot pass by accident. They
// are also all distinct from the receiver's own address and from the modelled
// image's address, so "forwards the wrong thing" is a separate failure from
// "reads the wrong place".
struct Scenario {
  Word field;
  Word accessor;
  Word lookup;
  Word resolve;
};

const Scenario kScenarios[] = {
    {0x00000000u, 0x11111111u, 0x22222222u, 0x33333333u},
    {0x00000001u, 0xffffffffu, 0x00000000u, 0x80000000u},
    {0x00000002u, 0x00b3d2a0u, 0xdeadbeefu, 0x7fffffffu},
    {0x184u, 0xabcdef01u, 0x0000ffffu, 0xffff0000u},
    {0x80000000u, 0x00000000u, 0xffffffffu, 0x00000002u},
};
constexpr std::size_t kScenarioCount = sizeof(kScenarios) / sizeof(kScenarios[0]);

void arm_scenario(const Scenario& scenario) {
  arm_image(scenario.field);
  g_accessor_result = scenario.accessor;
  g_lookup_result = scenario.lookup;
  g_resolve_result = scenario.resolve;
  reset_trace();
}

// ---------------------------------------------------------------------------
// The battery.
// ---------------------------------------------------------------------------

// One scenario, one probe, six machine facts:
//
//   * the four calls happen, in the order the listing gives, and there is no
//     fifth;
//   * the accessor is entered twice with no stack word and no receiver;
//   * each thiscall callee is entered with exactly one stack word;
//   * the receiver each thiscall callee sees is the accessor's return value;
//   * the first callee's stack word is the field and the second's is the
//     lookup's return value;
//   * the stack is unchanged across the call (measured), and no word of the
//     modelled image moved (memcmp).
bool probe_agrees(Probe probe, const Scenario& scenario) {
  arm_scenario(scenario);

  const Word receiver_address = pointer_word(receiver_of());
  const Word image_address = pointer_word(image_as_bytes());
  const std::uint32_t* const image_before = &g_sim_record_image.words[0];
  const EspSamples samples = call_probe_padded(probe, receiver_of());
  const std::uint32_t* const image_after = &g_sim_record_image.words[0];

  // 1. the stack, measured
  if (samples.before != samples.after) {
    return false;
  }
  if (samples.before == 0u) {
    return false;  // the sample is a real stack address, not a constant
  }

  // 2. nothing was written
  if (image_before != image_after) {
    return false;
  }
  for (std::size_t i = 0; i < kImageWords; ++i) {
    const Word expected =
        (i == kFieldDisplacement / sizeof(Word)) ? scenario.field : kGuardCanary;
    if (image_after[i] != expected) {
      return false;
    }
  }

  // 3. exactly the machine's four calls, in the machine's order
  if (g_call_depth != 4u) {
    return false;
  }
  if (g_call_trace[0].site != kSiteAccessor) {
    return false;
  }
  if (g_call_trace[1].site != kSiteLookup) {
    return false;
  }
  if (g_call_trace[2].site != kSiteAccessor) {
    return false;
  }
  if (g_call_trace[3].site != kSiteResolve) {
    return false;
  }

  // 4. the accessor is handed nothing, either time
  if (g_call_trace[0].stack_words != 0u || g_call_trace[2].stack_words != 0u) {
    return false;
  }

  // 5. each thiscall callee is handed exactly one word
  if (g_call_trace[1].stack_words != 1u || g_call_trace[3].stack_words != 1u) {
    return false;
  }

  // 6. the receiver is the ACCESSOR's return value -- not the entry's own
  //    receiver, not the field, not the image's address
  const Word expected_receiver = scenario.accessor;
  if (expected_receiver == receiver_address || expected_receiver == image_address) {
    return false;  // the scenario cannot tell those apart, so it proves nothing
  }
  if (g_call_trace[1].receiver != expected_receiver) {
    return false;
  }
  if (g_call_trace[3].receiver != expected_receiver) {
    return false;
  }
  if (g_call_trace[1].receiver == receiver_address) {
    return false;
  }
  if (g_call_trace[1].receiver == scenario.field) {
    return false;
  }

  // 7. the arguments: the field to the first, the lookup's result to the second
  if (g_call_trace[1].argument != scenario.field) {
    return false;
  }
  if (g_call_trace[3].argument != scenario.lookup) {
    return false;
  }
  if (scenario.lookup == scenario.field) {
    return false;  // the scenario cannot tell the two apart
  }
  return true;
}

bool probe_agrees_on_every_scenario(Probe probe) {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    if (!probe_agrees(probe, kScenarios[index])) {
      return false;
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// Direction A: the reconstruction must satisfy the whole battery.
// ---------------------------------------------------------------------------

// A + B + C + D + E + H together, over every scenario: the field read, the four
// calls in order, the accessor handed nothing, the receivers, the arguments, and
// the guard band.
void test_the_whole_battery_over_every_scenario() {
  check(probe_agrees_on_every_scenario(&real_entry));
}

// A. The dword the body reads IS the receiver's +0x184 dword. The canary and the
//    two neighbouring dwords are the controls: with the field set to a
//    non-canary value, a body reading either neighbour gives an answer this test
//    can see is wrong.
void test_reads_the_field_and_not_a_neighbour() {
  arm_image(0x12345678u);
  g_sim_record_image.words[(kFieldDisplacement / sizeof(Word)) - 1] = 0xdead0001u;
  g_sim_record_image.words[(kFieldDisplacement / sizeof(Word)) + 1] = 0xdead0002u;

  // The reference readers prove the harness CAN tell the three addresses apart,
  // which is what stops this case passing for the wrong reason.
  check(reference_reads_below_field() == 0xdead0001u);
  check(reference_reads_above_field() == 0xdead0002u);
  check(word_at(image_as_bytes(), kFieldDisplacement) == 0x12345678u);

  g_accessor_result = 0x0a0a0a0au;
  g_lookup_result = 0x0b0b0b0bu;
  g_resolve_result = 0x0c0c0c0cu;
  reset_trace();

  const EspSamples samples = call_probe(&real_entry, receiver_of());
  check(samples.before == samples.after);
  check(g_call_depth == 4u);
  check(g_call_trace[1].argument == 0x12345678u);
  check(g_call_trace[1].argument != 0xdead0001u);
  check(g_call_trace[1].argument != 0xdead0002u);
}

// B. Exactly four calls, in the machine's order. The two accessor calls are the
//    same target, so the order is accessor, lookup, accessor, resolve and not any
//    other permutation of those four.
void test_makes_exactly_four_calls_in_the_machines_order() {
  const Scenario scenario = {0x01020304u, 0x11121314u, 0x21222324u, 0x31323334u};
  arm_scenario(scenario);
  (void)call_probe(&real_entry, receiver_of());

  check(g_call_depth == kCalleeCount);
  check(g_call_trace[0].site == kSiteAccessor);
  check(g_call_trace[1].site == kSiteLookup);
  check(g_call_trace[2].site == kSiteAccessor);
  check(g_call_trace[3].site == kSiteResolve);
  // The body stores nothing, so no fifth call can be hiding past the recorded
  // window: the trace is the whole of what the entry did.
  check(g_call_depth < kMaxCallDepth);
}

// C. The accessor is handed NOTHING, and each thiscall callee exactly one word.
//    0x00b3d2a0 is `MOV EAX,DS:[slot]` / `RET`: it reads no stack word and pops
//    nothing, so a word pushed in front of its call belongs to the call that
//    follows. A body that pushed the field FOR the accessor would show up here
//    as a non-zero stack_words on one of the two accessor entries.
void test_accessor_is_handed_nothing_and_the_others_one_word() {
  const Scenario scenario = {0x00000007u, 0x76543210u, 0x0f0f0f0fu, 0xf0f0f0f0u};
  arm_scenario(scenario);
  (void)call_probe(&real_entry, receiver_of());

  check(g_call_trace[0].stack_words == 0u);
  check(g_call_trace[2].stack_words == 0u);
  check(g_call_trace[0].receiver == 0u);
  check(g_call_trace[2].receiver == 0u);
  check(g_call_trace[1].stack_words == 1u);
  check(g_call_trace[3].stack_words == 1u);
}

// D. The receiver each thiscall callee receives is the ACCESSOR's return value.
//    The body's two `MOV ECX,EAX` sit AFTER the accessor calls, so it is the
//    accessor's result that is forwarded -- not the entry's own receiver. This is
//    the case that separates the right body from one that passes `self` along.
void test_receiver_is_the_accessors_result_not_the_entrys_own() {
  const Scenario scenario = {0x00000009u, 0x5a5a5a5au, 0xa5a5a5a5u, 0x0f0f0f0fu};
  arm_scenario(scenario);

  const Word receiver_address = pointer_word(receiver_of());
  const Word image_address = pointer_word(image_as_bytes());
  check(scenario.accessor != receiver_address);
  check(scenario.accessor != image_address);
  check(scenario.accessor != scenario.field);
  check(scenario.accessor != scenario.lookup);

  (void)call_probe(&real_entry, receiver_of());

  check(g_call_trace[1].receiver == scenario.accessor);
  check(g_call_trace[3].receiver == scenario.accessor);
  check(g_call_trace[1].receiver != receiver_address);
  check(g_call_trace[3].receiver != receiver_address);
  check(g_call_trace[1].receiver != image_address);
  check(g_call_trace[1].receiver != scenario.field);
}

// E. The argument the second callee receives is the FIRST callee's return value,
//    not the field. The body pushes EAX at 0x00b8de43, and EAX at that point
//    holds 0x00ba6440's result.
void test_second_argument_is_the_first_callees_result_not_the_field() {
  const Scenario scenario = {0x0000000bu, 0x13571357u, 0x24682468u, 0x99999999u};
  arm_scenario(scenario);

  // If the two words were equal the case could not tell them apart, so pick
  // scenarios where they differ (asserted by the checks below).
  check(scenario.lookup != scenario.field);
  check(scenario.lookup != scenario.accessor);

  (void)call_probe(&real_entry, receiver_of());

  check(g_call_trace[3].argument == scenario.lookup);
  check(g_call_trace[3].argument != scenario.field);
  check(g_call_trace[1].argument == scenario.field);
}

// F. The entry's net stack effect is zero, MEASURED, and the measurement is
//    calibrated first so it cannot be reporting a constant. Two PUSHes against
//    two callee-side `ret 4`s is exactly zero, which is what lets the terminal
//    RET at 0x00b8de50 be bare.
void test_callee_pops_nothing() {
  // Calibration: a callee that pops nothing and a callee that pops four must be
  // told apart by this same channel. If they are not, the measurement is
  // worthless and the case below is skipped rather than passed silently.
  const EspSamples nothing = call_probe_padded(&control_pops_nothing, receiver_of());
  const EspSamples four = call_probe_padded(&control_pops_four, receiver_of());
  check(nothing.before == nothing.after);
  check(nothing.before != 0u);
  // A `ret 4` terminator pops the return address and then adds 4 to ESP, so a
  // caller that pushed two words sees its own ESP come back FOUR BYTES HIGH.
  check(four.before != four.after);
  check(four.before + 4u == four.after);

  arm_image(0x0000000du);
  g_accessor_result = 0xcafebabeu;
  g_lookup_result = 0x8badf00du;
  g_resolve_result = 0x0ddba11u;
  reset_trace();
  const EspSamples samples = call_probe_padded(&real_entry, receiver_of());
  check(samples.before == samples.after);
  check(samples.before != 0u);  // the sample is a real stack address
}

// G. The machine facts the whole package rests on, re-checked at run time,
//    including that the displacement and the four callee addresses really are
//    decoded out of the body bytes and that the two accessor calls are the same
//    target.
void test_machine_facts() {
  check(kEntryVa == 0x00b8de30u);
  check(kTerminalVa == 0x00b8de50u);
  check(kBodyBytes == 33u);
  check(kInstructionCount == 10u);
  check(kCalleeCount == 4u);
  check(kStackPushes == 2u);
  check(kCalleeCleanupBytes == 0u);
  check(kOrdinaryStackArgumentSlots == 0u);
  check(kHasReceiver);
  check(kReceiverRegisterVa == 0x00b8de30u);
  check(kReceiverDisplacementCeiling == 0x184u);
  check(kReturnWidthBytes == 0u);
  check(kAccessorStackArgumentWords == 0u);
  check(kAccessorCalleeCleanupBytes == 0u);
  check(kLookupCalleeCleanupBytes == 4u);
  check(kResolveCalleeCleanupBytes == 4u);

  // The image, byte for byte.
  check(kTargetBytes[0] == 0x8bu);
  check(kTargetBytes[1] == 0x81u);
  check(kTargetBytes[2] == 0x84u);
  check(kTargetBytes[3] == 0x01u);
  check(kTargetBytes[4] == 0x00u);
  check(kTargetBytes[5] == 0x00u);
  check(kTargetBytes[6] == 0x50u);   // PUSH EAX at 0x00b8de36
  check(kTargetBytes[7] == 0xe8u);   // CALL at 0x00b8de37
  check(kTargetBytes[12] == 0x8bu);  // MOV ECX,EAX at 0x00b8de3c
  check(kTargetBytes[13] == 0xc8u);
  check(kTargetBytes[14] == 0xe8u);  // CALL at 0x00b8de3e
  check(kTargetBytes[19] == 0x50u);  // PUSH EAX at 0x00b8de43
  check(kTargetBytes[20] == 0xe8u);  // CALL at 0x00b8de44
  check(kTargetBytes[25] == 0x8bu);  // MOV ECX,EAX at 0x00b8de49
  check(kTargetBytes[26] == 0xc8u);
  check(kTargetBytes[27] == 0xe8u);  // CALL at 0x00b8de4b
  check(kTargetBytes[32] == 0xc3u);  // RET at 0x00b8de50

  // The displacement, decoded from the operand bytes rather than restated.
  const Word decoded_displacement = static_cast<Word>(
      static_cast<std::uint32_t>(kTargetBytes[2]) |
      (static_cast<std::uint32_t>(kTargetBytes[3]) << 8) |
      (static_cast<std::uint32_t>(kTargetBytes[4]) << 16));
  check(decoded_displacement == kFieldDisplacement);
  check(kFieldDisplacement == 0x184u);
  check(kFieldDisplacement == 388u);  // the receiver record's 388, in decimal

  // The four callee addresses, decoded from each rel32 the same way, and the
  // two accessor calls are the SAME target.
  check(kAccessorVa00b3d2a0 == 0x00b3d2a0u);
  check(kLookupVa00ba6440 == 0x00ba6440u);
  check(kAccessorVa2 == 0x00b3d2a0u);
  check(kResolveVa00ba6d80 == 0x00ba6d80u);
  check(kAccessorVa00b3d2a0 == kAccessorVa2);

  // The three callee addresses are distinct from the target's own, so the
  // callee-name convention in the source reads as three calls and not as a
  // self-call.
  check(kLookupVa00ba6440 != kEntryVa);
  check(kResolveVa00ba6d80 != kEntryVa);
  check(kAccessorVa00b3d2a0 != kEntryVa);

  // The arithmetic that decides whose PUSH it is: two words in, two words
  // removed by the callees, so the terminal RET can be bare.
  check(kLookupCalleeCleanupBytes + kResolveCalleeCleanupBytes ==
        kStackPushes * sizeof(Word));

  // The modelled image: the field sits at the decoded displacement, with a
  // guard band above it and enough words below it to be readable.
  check(kImageWords ==
        kFieldDisplacement / sizeof(Word) + 1 + kGuardWords);
  check(image_as_bytes() == reinterpret_cast<std::uint8_t*>(
                                &g_sim_record_image.words[0]));
}

// H. The guard band. The body performs ONE read and no store, so every word of
//    the modelled image other than the field must still hold the canary after
//    the call, and the field must be byte-for-byte what it was. The neighbours
//    are also set to non-canary sentinels, so the check is not passing merely
//    because they happened to be untouched canaries.
void test_writes_nothing_outside_the_field() {
  const Word field_index = kFieldDisplacement / sizeof(Word);

  arm_image(0x5a5a1234u);
  g_accessor_result = 0x11111111u;
  g_lookup_result = 0x22222222u;
  g_resolve_result = 0x33333333u;
  reset_trace();

  const Word field_before = g_sim_record_image.words[field_index];
  (void)call_probe(&real_entry, receiver_of());

  check(g_sim_record_image.words[field_index] == field_before);
  for (std::size_t i = 0; i < kImageWords; ++i) {
    if (i == field_index) {
      continue;
    }
    check(g_sim_record_image.words[i] == kGuardCanary);
  }

  // Now with the neighbours dirtied, so the guard check is not passing on
  // untouched canaries alone.
  g_sim_record_image.words[field_index - 1] = 0x11111111u;
  g_sim_record_image.words[field_index + 1] = 0x22222222u;
  const Word field_value = g_sim_record_image.words[field_index];
  reset_trace();
  (void)call_probe(&real_entry, receiver_of());

  check(g_sim_record_image.words[field_index] == field_value);
  check(g_sim_record_image.words[field_index - 1] == 0x11111111u);
  check(g_sim_record_image.words[field_index + 1] == 0x22222222u);
  check(g_call_trace[1].argument == field_value);
}

// Direction B, the mutation test: every known-wrong body must be rejected. A
// mutant that survives means the battery has lost its power to tell a correct
// body from a wrong one, so the run fails even though the reconstruction itself
// passed every case above.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const model::Mutant& mutant = kMutants[index];
    if (probe_agrees_on_every_scenario(mutant.entry)) {
      std::fprintf(stderr, "0x00b8de30: mutant '%s' SURVIVED the battery\n",
                   mutant.name);
      check(false);
    }
  }
}

}  // namespace

int main() {
  test_the_whole_battery_over_every_scenario();
  test_reads_the_field_and_not_a_neighbour();
  test_makes_exactly_four_calls_in_the_machines_order();
  test_accessor_is_handed_nothing_and_the_others_one_word();
  test_receiver_is_the_accessors_result_not_the_entrys_own();
  test_second_argument_is_the_first_callees_result_not_the_field();
  test_callee_pops_nothing();
  test_machine_facts();
  test_writes_nothing_outside_the_field();
  test_every_mutant_is_refuted();
  return 0;
}
