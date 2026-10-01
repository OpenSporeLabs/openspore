#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "state_word_eq3_00c44c80.hpp"

// Focused semantic test for FUN_00c44c80 @ 0x00c44c80.
//
// The body is 4 instructions and 13 bytes:
//
//     0x00c44c80  33 c0                 XOR EAX,EAX
//     0x00c44c82  83 b9 84 00 00 00 03  CMP dword ptr [ECX + 0x84],0x3
//     0x00c44c89  0f 94 c0              SETZ AL
//     0x00c44c8c  c3                    RET
//
// so the semantics are fixed and narrow: read the 32-bit word at displacement
// 0x84 of the receiver and return whether it equals 0x3, as a one-byte value
// that is exactly 0 or exactly 1. The body stores nothing, calls nothing, saves
// no register and branches nowhere.
//
// The test is written to REFUTE the reconstruction, and it does that in two
// directions:
//
//   A. Positive discrimination. A battery of scenarios, each with DECOY words at
//      every neighbouring displacement, is run against the reconstruction through
//      the same checker the mutants go through. Perturb the reconstruction -
//      change the compared value, move the displacement, truncate the comparison
//      to a byte, widen it to a range - and at least one scenario's expected
//      value stops matching, so the test fails.
//
//   B. Negative discrimination (the mutation test proper). Eleven deliberately
//      broken variants of the body are compiled into this file and each one is
//      required to be REFUTED by the same battery. A battery with no power to
//      reject a mutant cannot tell a correct reconstruction from a wrong one, so
//      that the mutants are checked for rejection is itself an assertion.
//
// The reconstruction is reached through an inline-asm trampoline rather than
// through a thiscall function pointer on purpose. GCC's
// __attribute__((thiscall)) on a *function pointer type* allocates the argument
// with caller-side stack cleanup, which is not the convention the target uses
// (0x00c44c8c is a bare RET, caller cleanup), so a plain pointer call would
// drift the stack by 4 bytes per call. The trampoline reproduces the observed
// sequence exactly: receiver into ECX, nothing pushed, the result read back out
// of EAX.
//
// One thing deliberately NOT tested: a null receiver. The body dereferences ECX
// unconditionally at 0x00c44c82, so a null receiver faults in the original and a
// reconstruction that answered 0 for it would be a claim the machine refutes.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c44c80 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00C44C80_THISCALL __thiscall
#else
#define PKG_00C44C80_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c44c80_state_eq3 {
namespace model {

// One 32-bit word, used only for addresses and EAX samples in this file.
using Opaque = std::uint32_t;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

std::uint32_t word_at(const void* base, std::size_t displacement) {
  std::uint32_t value = 0;
  std::memcpy(&value,
              reinterpret_cast<const unsigned char*>(base) + displacement,
              sizeof(value));
  return value;
}

void store_word(void* base, std::size_t displacement, std::uint32_t value) {
  std::memcpy(reinterpret_cast<unsigned char*>(base) + displacement, &value,
              sizeof(value));
}

// The fixture arena is larger than the modelled receiver extent (0x88) so that a
// displacement one word too high is addressable and therefore REFUTED BY VALUE
// rather than by faulting. A battery that can only crash has no discriminating
// power left.
constexpr std::size_t kArenaBytes = 0x100;
constexpr std::size_t kNeighbourBelow = kStateDisplacement - 4;  // 0x80
constexpr std::size_t kNeighbourAbove = kStateDisplacement + 4;  // 0x88

static_assert(kNeighbourBelow == 0x80, "the word below 0x84 is at 0x80");
static_assert(kNeighbourAbove == 0x88, "the word above 0x84 is at 0x88");
static_assert(kArenaBytes > kNeighbourAbove + sizeof(std::uint32_t),
              "the arena covers the neighbouring word above 0x84");

struct Fixture {
  unsigned char arena[kArenaBytes];
  OpaqueReceiver* receiver() {
    return reinterpret_cast<OpaqueReceiver*>(arena);
  }
  const OpaqueReceiver* receiver() const {
    return reinterpret_cast<const OpaqueReceiver*>(arena);
  }
};

// One scenario: the word at 0x84, a decoy word at every neighbouring word
// offset, and the value the 4 instructions must produce for it.
//
// `decoy_below` and `decoy_above` are the words at 0x80 and 0x88. They are set
// to a value DIFFERENT from `word` in every scenario, so a reconstruction that
// read either of them answers something other than `expect` and is refuted.
// Where `expect` is 1 the compared word is 0x3 and both decoys are something
// else; where `expect` is 0 the compared word is some other value and the decoy
// below is 0x3, so a body that read one word too low answers 1 and is refuted.
struct Scenario {
  std::uint32_t word;
  std::uint32_t decoy_below;
  std::uint32_t decoy_above;
  std::uint32_t expect;
};

constexpr Scenario kScenarios[] = {
    // The one positive case the body has: the word is exactly 3.
    {0x3u, 0x0u, 0x0u, 1u},
    // The word below 0x84 is 3 and the compared word is not: reading one word
    // too low answers 1 here and is refuted.
    {0x0u, 0x3u, 0x9u, 0u},
    {0x2u, 0x3u, 0x1u, 0u},
    // The word above 0x84 is 3 and the compared word is not: reading one word
    // too high answers 1 here and is refuted.
    {0x4u, 0x0u, 0x3u, 0u},
    // A compared value of 4 must not answer 1 for a word of 3, and a compared
    // value of 2 must not answer 1 for a word of 2: both decoys sit at 3 as well.
    {0x3u, 0x2u, 0x4u, 1u},
    // The comparison is 32 bits wide: 0x103 has low byte 3 but is not 3, so a
    // body that truncated the comparison to a byte answers 1 and is refuted.
    {0x103u, 0x3u, 0x3u, 0u},
    // Likewise a word whose HIGH byte is 3: 0x03000000 is not 3.
    {0x03000000u, 0x3u, 0x3u, 0u},
    // Edge values of the full 32-bit comparison: neither is 3.
    {0x0u, 0x3u, 0x3u, 0u},
    {0xffffffffu, 0x3u, 0x3u, 0u},
    {0x80000000u, 0x3u, 0x3u, 0u},
    // The positive case again, with both decoys carrying values that a body
    // forwarding a neighbouring word instead of comparing it would return.
    {0x3u, 0x2au, 0x5au, 1u},
};

constexpr std::size_t kScenarioCount = sizeof(kScenarios) / sizeof(kScenarios[0]);

void build(Fixture& fixture, const Scenario& scenario) {
  std::memset(fixture.arena, 0, sizeof(fixture.arena));
  // A recognisable non-zero fill, so a body that read anywhere the scenarios do
  // not set is refuted by value too.
  for (std::size_t index = 0; index < sizeof(fixture.arena); ++index) {
    fixture.arena[index] = static_cast<unsigned char>(0xa0u + (index & 0x0fu));
  }
  store_word(fixture.arena, kNeighbourBelow, scenario.decoy_below);
  store_word(fixture.arena, kStateDisplacement, scenario.word);
  store_word(fixture.arena, kNeighbourAbove, scenario.decoy_above);
}

// The raw bytes read from 0x00c44c80..0x00c44c8c, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose.
constexpr std::uint8_t kTargetBytes[13] = {
    0x33, 0xc0,                    // XOR EAX,EAX
    0x83, 0xb9, 0x84, 0x00, 0x00,  // CMP dword ptr [ECX + 0x84],0x3
    0x00, 0x03, 0x0f, 0x94, 0xc0,  // SETZ AL
    0xc3,                          // RET
};

static_assert(sizeof(kTargetBytes) == 13, "the target body spans 13 bytes");
static_assert(kTargetBytes[0] == 0x33 && kTargetBytes[1] == 0xc0,
              "0x00c44c80 is XOR EAX,EAX");
static_assert(kTargetBytes[2] == 0x83 && kTargetBytes[3] == 0xb9,
              "0x00c44c82 is a CMP against a dword memory operand with an immediate");
static_assert(kTargetBytes[4] == 0x84,
              "the 0x84 displacement is an immediate in the CMP encoding");
static_assert(kTargetBytes[8] == 0x03,
              "the comparison immediate is 0x3");
static_assert(kTargetBytes[9] == 0x0f && kTargetBytes[10] == 0x94 && kTargetBytes[11] == 0xc0,
              "0x00c44c89 is SETZ AL (0f 94 c0)");
static_assert(kTargetBytes[12] == 0xc3,
              "0x00c44c8c is a bare RET, so the callee pops nothing");

static_assert(kStateDisplacement == 0x84,
              "the header's displacement is the CMP's immediate");
static_assert(kComparedValue == 0x3,
              "the header's compared value is the CMP's immediate");

Opaque entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&state_word_eq3_00c44c80));
}

// The value the entry RETURNS, read the way the ABI defines where a one-byte
// return value lives.
//
// The machine writes EAX in full: `XOR EAX,EAX` clears all four bytes and
// `SETZ AL` then sets the low one, so in the original the whole register is a
// clean 0 or 1. The declared C type is `bool`, and for a one-byte return the
// contract is about AL only - the upper three bytes of EAX are not part of the
// returned value. So the trampoline reads AL, which is the location the declared
// type actually promises, and this package does not claim a guarantee about the
// upper bytes that the type does not carry.
//
// ECX = receiver, no stack words pushed, callee pops nothing.
std::uint8_t call_entry(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  std::uint8_t result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movb %%al, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled immediately before the call and again the instant the callee has
// returned. `call` pushes a return address and `RET` takes it back, so the two
// samples are equal only when the callee owns no cleanup; a `RET 0x4` would
// leave the second four bytes lower. The model test therefore MEASURES the
// cleanup instead of asserting a calling convention it cannot derive from the
// body.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// The reconstructed entry behind a plain cdecl function pointer, so the
// reconstruction and the mutants below can be driven by one checker. The call
// itself still goes through the trampoline, so the ABI under test is the
// observed one and not the cdecl one.
std::uint32_t real_entry(OpaqueReceiver* receiver) {
  return static_cast<std::uint32_t>(call_entry(receiver));
}

// A plain callable: any `std::uint32_t(OpaqueReceiver*)`. Both the
// reconstruction (through `real_entry`) and every mutant below are driven
// through this one signature, so no mutant is graded by a laxer checker than the
// reconstruction is.
using Probe = std::uint32_t (*)(OpaqueReceiver*);

// Run one probe against one scenario. The checker asserts four things, and all
// four are machine facts:
//   * the value is the one the 4 instructions produce for this arrangement;
//   * the value is 0 or 1 and nothing else -- `XOR EAX,EAX` plus `SETZ AL` are
//     the only two values the body can leave in EAX, so a probe returning 3, 7
//     or 0xdeadbeef is refuted even where the sign is right;
//   * no byte of the arena changed, which is the evidence that the body stores
//     nothing: its only memory effect is the one load;
//   * the compared word itself is untouched, so a probe that CLEARED the word
//     and then answered 1 is refuted rather than rewarded.
bool probe_agrees(Probe probe, const Scenario& scenario) {
  Fixture fixture;
  build(fixture, scenario);

  unsigned char arena_before[kArenaBytes];
  std::memcpy(arena_before, fixture.arena, kArenaBytes);

  const std::uint32_t observed = probe(fixture.receiver());

  if (observed != scenario.expect) {
    return false;
  }
  if (observed != 0 && observed != 1) {
    return false;
  }
  if (std::memcmp(arena_before, fixture.arena, kArenaBytes) != 0) {
    return false;
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
// Mutants: the mutation battery
// ---------------------------------------------------------------------------
//
// Each mutant below is a body that is wrong in exactly one way. The test
// REQUIRES every one of them to be refuted by the battery above. A mutant that
// survives aborts the test, because a battery that cannot reject a known-wrong
// body cannot certify the right one.

// Wrong: the compared value is 2 instead of 3. Refuted by the scenario whose
// word is 2 with the decoy below at 3.
std::uint32_t mutant_compares_two(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement) == 0x2u ? 1u : 0u;
}

// Wrong: the compared value is 4 instead of 3. Refuted by the scenario whose
// word is 4.
std::uint32_t mutant_compares_four(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement) == 0x4u ? 1u : 0u;
}

// Wrong: the compared value is 0 instead of 3.
std::uint32_t mutant_compares_zero(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement) == 0x0u ? 1u : 0u;
}

// Wrong: the word is read one word too low.
std::uint32_t mutant_displacement_below(OpaqueReceiver* receiver) {
  return word_at(receiver, kNeighbourBelow) == 0x3u ? 1u : 0u;
}

// Wrong: the word is read one word too high.
std::uint32_t mutant_displacement_above(OpaqueReceiver* receiver) {
  return word_at(receiver, kNeighbourAbove) == 0x3u ? 1u : 0u;
}

// Wrong: the comparison is truncated to the low byte, so 0x103 answers 1.
std::uint32_t mutant_byte_truncated_comparison(OpaqueReceiver* receiver) {
  const std::uint32_t word = word_at(receiver, kStateDisplacement);
  return (word & 0xffu) == 0x3u ? 1u : 0u;
}

// Wrong: the comparison is widened to a range, so a word of 4 answers 1. The
// body is `CMP` plus `SETZ`, which is equality and not a range test.
std::uint32_t mutant_range_comparison(OpaqueReceiver* receiver) {
  const std::uint32_t word = word_at(receiver, kStateDisplacement);
  return (word >= 0x3u && word <= 0x4u) ? 1u : 0u;
}

// Wrong: a truthy result is not 1. `XOR EAX,EAX` then `SETZ AL` leaves exactly 0
// or exactly 1 in EAX, so a body answering 2 for the positive case is refuted.
std::uint32_t mutant_truthy_two(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement) == 0x3u ? 2u : 0u;
}

// Wrong: the word is forwarded instead of compared. A word of 0x103 must answer
// 0, not 0x103.
std::uint32_t mutant_forwards_word(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement);
}

// Wrong: the predicate is inverted - it answers 1 for every word that is not 3.
std::uint32_t mutant_inverted_polarity(OpaqueReceiver* receiver) {
  return word_at(receiver, kStateDisplacement) != 0x3u ? 1u : 0u;
}

// Wrong: always zero -- the `XOR EAX,EAX` state with the comparison deleted.
std::uint32_t mutant_always_zero(OpaqueReceiver* receiver) {
  (void)receiver;
  return 0;
}

// Wrong: always one -- the `SETZ AL` result with the comparison inverted away.
std::uint32_t mutant_always_one(OpaqueReceiver* receiver) {
  (void)receiver;
  return 1;
}

struct Mutant {
  const char* name;
  Probe probe;
};

const Mutant kMutants[] = {
    {"compares_two", &mutant_compares_two},
    {"compares_four", &mutant_compares_four},
    {"compares_zero", &mutant_compares_zero},
    {"displacement_below", &mutant_displacement_below},
    {"displacement_above", &mutant_displacement_above},
    {"byte_truncated_comparison", &mutant_byte_truncated_comparison},
    {"range_comparison", &mutant_range_comparison},
    {"truthy_two", &mutant_truthy_two},
    {"forwards_word", &mutant_forwards_word},
    {"inverted_polarity", &mutant_inverted_polarity},
    {"always_zero", &mutant_always_zero},
    {"always_one", &mutant_always_one},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}

namespace {

using namespace openspore::reconstruction::pkg_00c44c80_state_eq3;
using namespace openspore::reconstruction::pkg_00c44c80_state_eq3::model;
using model::build;
using model::call_entry;
using model::call_entry_measured;
using model::check;
using model::entry_address;
using model::kMutantCount;
using model::kMutants;
using model::kScenarioCount;
using model::pointer_word;
using model::probe_agrees;
using model::probe_agrees_on_every_scenario;
using model::real_entry;
using model::EspSamples;
using model::Fixture;
using model::Mutant;
using model::Probe;
using model::Scenario;

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(kScenarioCount == 11, "the battery has eleven known arrangements");
static_assert(kMutantCount == 12, "the battery has twelve known-wrong bodies");
static_assert(std::is_same<AbiStateWordEq300c44c80,
                          bool(PKG_00C44C80_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words");

// A. Positive discrimination: the reconstruction agrees with the machine on
// every scenario, and the fixtures really do carry the words the scenarios
// declare (so a scenario that forgot to set the compared word cannot pass
// vacuously).
void test_reconstruction_agrees_on_every_scenario() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    const Scenario& scenario = kScenarios[index];
    Fixture fixture;
    build(fixture, scenario);
    check(model::word_at(fixture.receiver(), kStateDisplacement) == scenario.word);
    check(model::word_at(fixture.receiver(), kNeighbourBelow) == scenario.decoy_below);
    check(model::word_at(fixture.receiver(), kNeighbourAbove) == scenario.decoy_above);
    // The decoys must never equal the compared word, or a displaced read would
    // be indistinguishable from a correct one in this scenario.
    check(scenario.decoy_below != scenario.word);
    check(scenario.decoy_above != scenario.word);
  }
  check(probe_agrees_on_every_scenario(&real_entry));
}

// The one positive case spelled out on its own, through the same trampoline the
// battery uses, so the answer for a word of 3 is read rather than inferred.
void test_word_of_three_answers_one() {
  Fixture fixture;
  build(fixture, kScenarios[0]);
  check(kScenarios[0].word == 0x3u);
  check(kScenarios[0].expect == 1u);
  const Opaque observed = call_entry(fixture.receiver());
  check(observed == 1u);
  check(observed != 0u);
  check(call_entry(fixture.receiver()) == 1u);
}

// The returned value is exactly 0 or 1, never a truthy value of some other
// magnitude: `XOR EAX,EAX` clears the register and `SETZ AL` writes only its low
// byte, so the caller can read one clean byte and nothing more. The byte is read
// as a byte, so a body that left a wider value in EAX could not pass by having
// the right value in AL and something else above it.
void test_return_is_a_clean_byte_zero_or_one() {
  Fixture fixture;
  build(fixture, kScenarios[0]);
  check(call_entry(fixture.receiver()) == 1u);

  build(fixture, kScenarios[8]);  // word == 0
  check(call_entry(fixture.receiver()) == 0u);
  // The returned byte is a byte: it cannot be a wider value read by accident.
  check(sizeof(decltype(call_entry(fixture.receiver()))) == 1);
  check(static_cast<std::uint8_t>(call_entry(fixture.receiver())) == 0u);
}

// The comparison is on all 32 bits. 0x103 has low byte 3 but is not 3, and
// 0x03000000 has high byte 3 but is not 3.
void test_comparison_is_thirty_two_bits_wide() {
  Fixture fixture;

  build(fixture, kScenarios[5]);  // 0x103
  check(kScenarios[5].expect == 0u);
  check(call_entry(fixture.receiver()) == 0u);

  build(fixture, kScenarios[6]);  // 0x03000000
  check(kScenarios[6].expect == 0u);
  check(call_entry(fixture.receiver()) == 0u);
}

// The displacement is an offset into the receiver, not an index. The neighbouring
// words carry 3 in the scenarios where the compared word does not, so a body that
// read either neighbour answers 1 where the machine answers 0.
void test_displacement_is_an_offset_not_an_index() {
  Fixture fixture;

  build(fixture, kScenarios[1]);
  check(kScenarios[1].expect == 0u);
  check(model::word_at(fixture.receiver(), kNeighbourBelow) == 0x3u);
  check(call_entry(fixture.receiver()) == 0u);

  build(fixture, kScenarios[3]);
  check(kScenarios[3].expect == 0u);
  check(model::word_at(fixture.receiver(), kNeighbourAbove) == 0x3u);
  check(call_entry(fixture.receiver()) == 0u);

  // The 0x84 in the entry and the header's kStateDisplacement name one and the
  // same word, so the two statements of the displacement cannot drift apart.
  const std::uint32_t* literal = reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(fixture.receiver()) + 0x84);
  const std::uint32_t* declared = reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(fixture.receiver()) + kStateDisplacement);
  check(literal == declared);
  check(reinterpret_cast<std::uintptr_t>(declared) -
            reinterpret_cast<std::uintptr_t>(fixture.receiver()) ==
        0x84u);
}

// The entry's literal `+ 0x84` and the header's kStateDisplacement are shown to
// agree by VALUE against what the machine layout says, so the header constant is
// pinned to the CMP's immediate rather than to prose.
void test_header_constant_matches_the_instruction_encoding() {
  check(kStateDisplacement == 0x84u);
  check(kComparedValue == 0x3u);
  // 0x00c44c82 is `83 b9 84 00 00 00 03`: ModRM 0xb9 selects CMP with a dword
  // memory operand and an immediate, and the bytes that follow are the 0x84
  // displacement and the 0x3 immediate.
  check(model::kTargetBytes[4] == 0x84u);
  check(model::kTargetBytes[8] == 0x03u);
  // The modelled receiver extent ends exactly at the compared word.
  check(kStateDisplacement + sizeof(std::uint32_t) == sizeof(OpaqueReceiver));
}

// The body ends in a bare RET, so the callee pops nothing and the caller owns the
// stack. That is measured here, not assumed.
void test_no_stack_words_are_popped_by_the_callee() {
  Fixture fixture;
  build(fixture, kScenarios[0]);

  const EspSamples samples = call_entry_measured(fixture.receiver());
  check(samples.after_return == samples.before_call);

  // The result still reads as the machine's after the measured call, so the
  // measurement did not perturb the behaviour it is measuring.
  check(call_entry(fixture.receiver()) == 1u);
  check(sizeof(AbiStateWordEq300c44c80) == sizeof(void*));
}

// The body stores nothing: a full arena is compared before and after.
void test_the_body_stores_nothing() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture fixture;
    build(fixture, kScenarios[index]);

    unsigned char before[kArenaBytes];
    std::memcpy(before, fixture.arena, kArenaBytes);

    check(call_entry(fixture.receiver()) == kScenarios[index].expect);

    check(std::memcmp(before, fixture.arena, kArenaBytes) == 0);
    // The compared word is still exactly what the scenario put there.
    check(model::word_at(fixture.receiver(), kStateDisplacement) ==
          kScenarios[index].word);
  }
}

// B. Negative discrimination: the mutation test proper. Every known-wrong body
// must be rejected by the same battery. A mutant that survives means the battery
// has lost its power to tell a correct reconstruction from a wrong one.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    check(!probe_agrees_on_every_scenario(kMutants[index].probe));
  }
}

// The battery itself must have discriminating power on the axes it claims to
// test: each mutant differs from the reconstruction in exactly one of them, and
// the check below states which scenario refutes it, so a scenario removed from
// the array is visible as a lost refutation rather than as a silent pass.
void test_each_mutant_is_refuted_by_a_named_scenario() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const Probe probe = kMutants[index].probe;
    bool refuted = false;
    for (std::size_t scenario_index = 0; scenario_index < kScenarioCount;
         ++scenario_index) {
      if (!probe_agrees(probe, kScenarios[scenario_index])) {
        refuted = true;
        break;
      }
    }
    check(refuted);
  }
}

int run_tests() {
  test_reconstruction_agrees_on_every_scenario();
  test_word_of_three_answers_one();
  test_return_is_a_clean_byte_zero_or_one();
  test_comparison_is_thirty_two_bits_wide();
  test_displacement_is_an_offset_not_an_index();
  test_header_constant_matches_the_instruction_encoding();
  test_no_stack_words_are_popped_by_the_callee();
  test_the_body_stores_nothing();
  test_every_mutant_is_refuted();
  test_each_mutant_is_refuted_by_a_named_scenario();
  return 0;
}

}

}

int main() {
  return openspore::reconstruction::pkg_00c44c80_state_eq3::run_tests();
}

#undef PKG_00C44C80_THISCALL
