#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "linked_flag_probe_00c0c0e0.hpp"

// Focused semantic test for FUN_00c0c0e0 @ 0x00c0c0e0.
//
// The body is 9 instructions and 28 bytes:
//
//     0x00c0c0e0  8b 81 84 0e 00 00     MOV EAX,dword ptr [ECX + 0xe84]
//     0x00c0c0e6  85 c0                 TEST EAX,EAX
//     0x00c0c0e8  74 0f                 JZ 0x00c0c0f9
//     0x00c0c0ea  80 b8 88 03 00 00 00  CMP byte ptr [EAX + 0x388],0x0
//     0x00c0c0f1  74 06                 JZ 0x00c0c0f9
//     0x00c0c0f3  b8 01 00 00 00        MOV EAX,0x1
//     0x00c0c0f8  c3                    RET
//     0x00c0c0f9  33 c0                 XOR EAX,EAX
//     0x00c0c0fb  c3                    RET
//
// so the semantics are fixed and narrow: read a 32-bit word at 0xe84 of the
// receiver; if it is zero return 0; otherwise read one byte at 0x388 of the
// object that word addresses and return 1 if that byte is non-zero, else 0. The
// body stores nothing and calls nothing.
//
// The test is written to REFUTE the reconstruction, and it does that in two
// directions:
//
//   A. Positive discrimination. A battery of scenarios, each with a DECOY at
//      every neighbouring displacement, is run against the reconstruction
//      through the same checker the mutants go through. Perturb the
//      reconstruction - flip a comparison, move a displacement, drop the guard,
//      forward the flag byte - and at least one scenario's expected value stops
//      matching, so the test fails.
//
//   B. Negative discrimination (the mutation test proper). Ten deliberately
//      broken variants of the body are compiled into this file and each one is
//      required to be REFUTED by the same battery. A battery with no power to
//      reject a mutant cannot tell a correct reconstruction from a wrong one, so
//      that the mutants are checked for rejection is itself an assertion.
//
// The reconstruction is reached through an inline-asm trampoline rather than
// through a thiscall function pointer on purpose. GCC's
// __attribute__((thiscall)) on a *function pointer type* allocates the argument
// with caller-side stack cleanup, which is not the convention the target uses
// (0x00c0c0f8 and 0x00c0c0fb are both bare RETs, caller cleanup), so a plain
// pointer call would drift the stack by 4 bytes per call. The trampoline
// reproduces the observed sequence exactly: receiver into ECX, nothing pushed,
// the result read back out of EAX.
//
// One thing deliberately NOT tested: a null receiver. The body dereferences ECX
// unconditionally at 0x00c0c0e0, so a null receiver faults in the original and a
// reconstruction that returned 0 for it would be a claim the machine refutes.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c0c0e0 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so it is respelled here; it is the
// same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00C0C0E0_THISCALL __thiscall
#else
#define PKG_00C0C0E0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe {
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

Opaque byte_at(const void* base, std::size_t displacement) {
  return static_cast<Opaque>(
      *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement));
}

void store_byte(void* base, std::size_t displacement, std::uint8_t value) {
  *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

void store_word(void* base, std::size_t displacement, std::uint32_t value) {
  *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

// The raw bytes read from 0x00c0c0e0..0x00c0c0fb, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose.
constexpr std::uint8_t kTargetBytes[28] = {
    0x8b, 0x81, 0x84, 0x0e, 0x00, 0x00,  // MOV EAX,dword ptr [ECX + 0xe84]
    0x85, 0xc0,                          // TEST EAX,EAX
    0x74, 0x0f,                          // JZ 0x00c0c0f9
    0x80, 0xb8, 0x88, 0x03, 0x00, 0x00,  // CMP byte ptr [EAX + 0x388],0x0
    0x00,
    0x74, 0x06,                          // JZ 0x00c0c0f9
    0xb8, 0x01, 0x00, 0x00, 0x00,        // MOV EAX,0x1
    0xc3,                                // RET
    0x33, 0xc0,                          // XOR EAX,EAX
    0xc3,                                // RET
};

static_assert(sizeof(kTargetBytes) == 28, "the target body spans 28 bytes");
static_assert(kTargetBytes[0] == 0x8b && kTargetBytes[1] == 0x81 &&
                  kTargetBytes[2] == 0x84 && kTargetBytes[3] == 0x0e,
              "0x00c0c0e0 is MOV EAX,dword ptr [ECX + 0xe84]: the 0xe84 displacement is an immediate");
static_assert(kTargetBytes[12] == 0x88 && kTargetBytes[13] == 0x03,
              "0x00c0c0ea is CMP byte ptr [EAX + 0x388],0x0: the 0x388 displacement is an immediate");
static_assert(kTargetBytes[24] == 0xc3 && kTargetBytes[27] == 0xc3,
              "both terminators are a bare RET, so the callee pops nothing");
// The two displacements, read out of the encodings above rather than out of
// prose, and tied to the header's constants so the two statements of each
// displacement cannot drift apart.
static_assert((0x0e << 8 | kTargetBytes[2]) == kReceiverLinkDisplacement,
              "the header's receiver displacement is the MOV's immediate");
static_assert((kTargetBytes[13] << 8 | kTargetBytes[12]) == kLinkedFlagDisplacement,
              "the header's linked-object displacement is the CMP's immediate");
static_assert(kReceiverLinkDisplacement == (0xe84u),
              "0xe84 is the value 3716, compared semantically not by spelling");
static_assert(kLinkedFlagDisplacement == (0x388u),
              "0x388 is the value 904, compared semantically not by spelling");

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

// The arenas are larger than the modelled extents so a decoy can be written at
// every displacement ADJACENT to the two the body uses. The adjacent
// displacements are past the end of the modelled object, so they cannot live
// inside it; the arena is the only place to put them. The modelled extents
// themselves are untouched and are checked by the header's static_asserts.
constexpr std::size_t kReceiverArenaBytes = 0xe90;  // 0xe88 is one past the modelled extent
constexpr std::size_t kLinkedArenaBytes = 0x3a0;    // 0x389 is one past the modelled extent

// The neighbours of the two real displacements. 0xe84 and 0x388 are the only two
// the body may use.
constexpr std::size_t kLinkNeighbourBelow = 0xe80;
constexpr std::size_t kLinkNeighbourAbove = 0xe88;
constexpr std::size_t kFlagNeighbourBelow = 0x384;
constexpr std::size_t kFlagNeighbourAbove = 0x38c;

struct Fixture {
  alignas(4) std::uint8_t receiver_arena[kReceiverArenaBytes] = {};
  alignas(4) std::uint8_t linked_arena[kLinkedArenaBytes] = {};
  alignas(4) std::uint8_t decoy_arena[kLinkedArenaBytes] = {};

  OpaqueReceiver* receiver() {
    return reinterpret_cast<OpaqueReceiver*>(receiver_arena);
  }
  OpaqueLinkedObject* linked() {
    return reinterpret_cast<OpaqueLinkedObject*>(linked_arena);
  }
  OpaqueLinkedObject* decoy() {
    return reinterpret_cast<OpaqueLinkedObject*>(decoy_arena);
  }
};

// What the machine returns for one arrangement of the two objects.
struct Scenario {
  bool link_is_null;    // the 32-bit word at 0xe84
  std::uint8_t flag;    // the byte at 0x388 of the linked object
  std::uint32_t expect; // the value EAX holds on return
};

// A non-zero flag byte that is not 1. The body returns 1 for it, not the byte:
// this is the scenario that separates "returns the constant 1" from "forwards
// the flag" and from "returns the raw comparison result".
constexpr std::uint8_t kNonUnitFlag = 0x2a;

// Build one scenario. Every byte of every arena is filled with a non-zero
// pattern first, so a read of any uninitialised displacement is visible, and a
// decoy is planted at each neighbouring displacement pointing at an object whose
// 0x388 byte carries the OPPOSITE answer. A reconstruction that read a
// neighbouring displacement therefore returns the other value and is caught.
void build(Fixture& fixture, const Scenario& scenario) {
  for (std::size_t index = 0; index < kReceiverArenaBytes; ++index) {
    fixture.receiver_arena[index] = static_cast<std::uint8_t>(index + 1u);
  }
  for (std::size_t index = 0; index < kLinkedArenaBytes; ++index) {
    fixture.linked_arena[index] = static_cast<std::uint8_t>(index + 1u);
    fixture.decoy_arena[index] = static_cast<std::uint8_t>(index + 1u);
  }

  const std::uint8_t opposite =
      scenario.expect != 0 ? static_cast<std::uint8_t>(0x00) : static_cast<std::uint8_t>(0xff);

  // The real linked object, reached through the real 0xe84 word.
  store_byte(fixture.linked(), kLinkedFlagDisplacement, scenario.flag);

  // The decoy object: its 0x388 byte says the opposite of what the scenario
  // expects, so a body that followed either neighbour word returns the wrong
  // answer.
  store_byte(fixture.decoy(), kLinkedFlagDisplacement, opposite);

  if (scenario.link_is_null) {
    store_word(fixture.receiver(), kReceiverLinkDisplacement, 0);
  } else {
    store_word(fixture.receiver(), kReceiverLinkDisplacement, pointer_word(fixture.linked()));
  }
  store_word(fixture.receiver(), kLinkNeighbourBelow, pointer_word(fixture.decoy()));
  store_word(fixture.receiver(), kLinkNeighbourAbove, pointer_word(fixture.decoy()));

  // Decoys around the flag displacement, on the REAL linked object, so a body
  // that read 0x384 or 0x38c instead of 0x388 sees the opposite answer.
  store_byte(fixture.linked(), kFlagNeighbourBelow, opposite);
  store_byte(fixture.linked(), kFlagNeighbourAbove, opposite);
}

// The scenario battery. Five arrangements, chosen so each of the body's three
// observable decisions is pinned by at least one and the two shared zero exits
// are both reached.
const Scenario kScenarios[] = {
    {false, 0x00, 0},  // link present, flag clear  -> the 0x00c0c0f1 branch
    {false, 0x01, 1},  // link present, flag set    -> the 0x00c0c0f3 return
    {false, kNonUnitFlag, 1},  // link present, flag set but not 1 -> still 1
    {true, 0x00, 0},   // link absent               -> the 0x00c0c0e8 branch
    {true, 0xff, 0},   // link absent, flag would-be set -> still 0
};
constexpr std::size_t kScenarioCount = sizeof(kScenarios) / sizeof(kScenarios[0]);

// ---------------------------------------------------------------------------
// Reaching the reconstruction
// ---------------------------------------------------------------------------

Opaque entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&linked_flag_probe_00c0c0e0));
}

// The return value (EAX) after calling the entry through the trampoline.
// ECX = receiver, no stack word pushed, callee pops nothing.
Opaque call_entry(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  Opaque result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// The same call, but with EAX pre-loaded with a pattern. Both exits of the body
// write EAX in full (`MOV EAX,0x1` and `XOR EAX,EAX`, both 32-bit), so a correct
// reconstruction leaves none of that pattern behind. A body that wrote only the
// low byte would return 0xdeadbeef or 0xdeadbe00 instead, which is the whole
// reason this variant exists: it is what separates "returns a 32-bit value in
// EAX" from "returns a byte in AL".
Opaque call_entry_with_poisoned_eax(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  Opaque result = 0;
  __asm__ __volatile__("movl $0xdeadbeef, %%eax\n\t"
                       "movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled inside the trampoline, immediately before the call and again the
// instant the callee has returned. `call` pushes a return address and `RET` takes
// it back, so the two samples are equal only when the callee owns no cleanup; a
// `RET 0x4` would leave the second four bytes lower. The test MEASURES the
// cleanup instead of asserting a convention it cannot derive from the body.
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

// Run one probe against one scenario. The checker asserts three things, and all
// three are machine facts:
//   * the value is the one the 9 instructions produce for this arrangement;
//   * the value is 0 or 1 and nothing else -- `MOV EAX,0x1` and `XOR EAX,EAX`
//     are the only two values the body can leave in EAX, so a probe returning
//     2, 7 or 0xdeadbeef is refuted even where the sign is right;
//   * neither arena changed by a single byte, which is the evidence that the
//     body stores nothing: its only memory effects are the two loads.
bool probe_agrees(Probe probe, const Scenario& scenario) {
  Fixture fixture;
  build(fixture, scenario);

  std::uint8_t receiver_before[kReceiverArenaBytes];
  std::uint8_t linked_before[kLinkedArenaBytes];
  std::memcpy(receiver_before, fixture.receiver_arena, kReceiverArenaBytes);
  std::memcpy(linked_before, fixture.linked_arena, kLinkedArenaBytes);

  const std::uint32_t observed = probe(fixture.receiver());

  if (observed != scenario.expect) {
    return false;
  }
  if (observed != 0 && observed != 1) {
    return false;
  }
  if (std::memcmp(receiver_before, fixture.receiver_arena, kReceiverArenaBytes) != 0) {
    return false;
  }
  if (std::memcmp(linked_before, fixture.linked_arena, kLinkedArenaBytes) != 0) {
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

// Wrong: drops the 0x00c0c0e8 guard, so a null link word is treated as set.
// Spelled so that the mutant is REFUTED BY VALUE rather than by faulting: it
// reads the flag byte through whatever the link word holds, and answers 1 when
// the link word is null. A body that genuinely dereferenced a null link would
// be refuted too, but by a signal the battery cannot attribute, and a battery
// that only crashes is a battery with no discriminating power left.
std::uint32_t mutant_no_null_guard(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 1;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kLinkedFlagDisplacement);
  return flag != 0 ? 1u : 0u;
}

// Wrong: inverted polarity. Returns 1 for a CLEAR flag byte.
std::uint32_t mutant_inverted_polarity(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kLinkedFlagDisplacement);
  return flag == 0 ? 1u : 0u;
}

// Wrong: the link word is read one word too low.
std::uint32_t mutant_link_displacement_below(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kLinkNeighbourBelow);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kLinkedFlagDisplacement);
  return flag != 0 ? 1u : 0u;
}

// Wrong: the link word is read one word too high.
std::uint32_t mutant_link_displacement_above(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kLinkNeighbourAbove);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kLinkedFlagDisplacement);
  return flag != 0 ? 1u : 0u;
}

// Wrong: the flag byte is read one byte too low.
std::uint32_t mutant_flag_displacement_below(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kFlagNeighbourBelow);
  return flag != 0 ? 1u : 0u;
}

// Wrong: the flag byte is read one byte too high.
std::uint32_t mutant_flag_displacement_above(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kFlagNeighbourAbove);
  return flag != 0 ? 1u : 0u;
}

// Wrong: forwards the flag byte instead of returning the constant 1. The body
// writes 1, so a flag of 0x2a must still come back as 1.
std::uint32_t mutant_forwards_flag_byte(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 0;
  }
  return linked_flag_byte(reinterpret_cast<const OpaqueLinkedObject*>(link),
                          kLinkedFlagDisplacement);
}

// Wrong: a truthy result is not 1. The positive exit is `MOV EAX,0x1`.
std::uint32_t mutant_truthy_two(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  if (link == 0) {
    return 0;
  }
  const std::uint8_t flag = linked_flag_byte(
      reinterpret_cast<const OpaqueLinkedObject*>(link), kLinkedFlagDisplacement);
  return flag != 0 ? 2u : 0u;
}

// Wrong: the second read is never made, so a non-null link answers 1 whatever
// the flag byte says.
std::uint32_t mutant_ignores_flag(OpaqueReceiver* receiver) {
  const std::uint32_t link = receiver_word(receiver, kReceiverLinkDisplacement);
  return link != 0 ? 1u : 0u;
}

// Wrong: always zero -- the `XOR EAX,EAX` arm with the other one deleted.
std::uint32_t mutant_always_zero(OpaqueReceiver* receiver) {
  (void)receiver;
  return 0;
}

struct Mutant {
  const char* name;
  Probe probe;
};

const Mutant kMutants[] = {
    {"no_null_guard", &mutant_no_null_guard},
    {"inverted_polarity", &mutant_inverted_polarity},
    {"link_displacement_below", &mutant_link_displacement_below},
    {"link_displacement_above", &mutant_link_displacement_above},
    {"flag_displacement_below", &mutant_flag_displacement_below},
    {"flag_displacement_above", &mutant_flag_displacement_above},
    {"forwards_flag_byte", &mutant_forwards_flag_byte},
    {"truthy_two", &mutant_truthy_two},
    {"ignores_flag", &mutant_ignores_flag},
    {"always_zero", &mutant_always_zero},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}

namespace {

using namespace openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe;
using namespace openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe::model;
using model::build;
using model::byte_at;
using model::call_entry;
using model::call_entry_measured;
using model::call_entry_with_poisoned_eax;
using model::check;
using model::entry_address;
using model::kMutantCount;
using model::kMutants;
using model::kScenarioCount;
using model::kScenarios;
using model::kNonUnitFlag;
using model::pointer_word;
using model::probe_agrees;
using model::probe_agrees_on_every_scenario;
using model::real_entry;
using model::EspSamples;
using model::Fixture;
using model::Mutant;
using model::Probe;
using model::Scenario;

}

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(std::is_same<AbiLinkedFlagProbe00c0c0e0,
                           std::uint32_t(PKG_00C0C0E0_THISCALL*)(
                               OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words");
static_assert(kScenarioCount == 5, "the battery covers five arrangements");
static_assert(kMutantCount == 10, "the battery has ten known-wrong bodies");
static_assert(kLinkNeighbourBelow < kReceiverLinkDisplacement &&
                  kReceiverLinkDisplacement < kLinkNeighbourAbove,
              "the decoy link words straddle the real one");
static_assert(kFlagNeighbourBelow < kLinkedFlagDisplacement &&
                  kLinkedFlagDisplacement < kFlagNeighbourAbove,
              "the decoy flag bytes straddle the real one");
static_assert(kLinkNeighbourAbove + sizeof(std::uint32_t) <= kReceiverArenaBytes,
              "the upper decoy link word fits in the receiver arena");
static_assert(kFlagNeighbourAbove + sizeof(std::uint8_t) <= kLinkedArenaBytes,
              "the upper decoy flag byte fits in the linked arena");
static_assert(kReceiverArenaBytes >= sizeof(OpaqueReceiver),
              "the receiver arena covers the modelled receiver extent");
static_assert(kLinkedArenaBytes >= sizeof(OpaqueLinkedObject),
              "the linked arena covers the modelled linked extent");


// Direction A: the reconstruction must satisfy the whole battery.
void test_reconstruction_satisfies_every_scenario() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    check(probe_agrees(&real_entry, kScenarios[index]));
  }
  check(probe_agrees_on_every_scenario(&real_entry));
}

// Direction B, the mutation test: every known-wrong body must be rejected. A
// mutant that survives means the battery has lost its power to tell a correct
// body from a wrong one, so the run fails even though the reconstruction itself
// passed direction A.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const Mutant& mutant = kMutants[index];
    check(!probe_agrees_on_every_scenario(mutant.probe));
  }
}

// The battery's two halves are separately witnessed, so a mutation that only
// breaks one decision is still named as broken rather than passing unnoticed.
void test_each_decision_is_individually_pinned() {
  // The guard: a null link word must return 0, not 1 and not a fault.
  check(probe_agrees(&real_entry, kScenarios[3]));
  check(probe_agrees(&real_entry, kScenarios[4]));

  // The zero-flag exit: link present, flag clear, returns 0.
  check(probe_agrees(&real_entry, kScenarios[0]));

  // The one-return exit: link present, flag set, returns exactly 1. A flag byte
  // that is neither 0 nor 1 still returns 1, so the returned value is the
  // constant and not the byte.
  check(probe_agrees(&real_entry, kScenarios[1]));
  check(probe_agrees(&real_entry, kScenarios[2]));

  Fixture fixture;
  build(fixture, kScenarios[2]);
  check(byte_at(fixture.linked(), kLinkedFlagDisplacement) == kNonUnitFlag);
  check(call_entry(fixture.receiver()) == 1u);
}

// The two displacements are offsets into their own objects, and the second one
// is not an index into the first. The body addresses 0xe84 on ECX and 0x388 on
// EAX; a reconstruction that read a neighbouring displacement -- or read one of
// them as an element number rather than a byte offset -- lands somewhere else,
// and the planted decoys make that visible.
void test_displacements_are_offsets_not_indices() {
  Fixture fixture;
  build(fixture, kScenarios[1]);
  check(call_entry(fixture.receiver()) == 1u);

  // The decoys are genuinely planted and genuinely say the opposite, so the
  // answer above can only have come from the real two displacements.
  check(receiver_word(fixture.receiver(), kLinkNeighbourBelow) == pointer_word(fixture.decoy()));
  check(receiver_word(fixture.receiver(), kLinkNeighbourAbove) == pointer_word(fixture.decoy()));
  check(byte_at(fixture.decoy(), kLinkedFlagDisplacement) == 0x00);
  check(byte_at(fixture.linked(), kFlagNeighbourBelow) == 0x00);
  check(byte_at(fixture.linked(), kFlagNeighbourAbove) == 0x00);
  check(byte_at(fixture.linked(), kLinkedFlagDisplacement) == 0x01);

  // Each displacement is measured in BYTES from the base of its own object. A
  // reconstruction that read 0xe84 as a word index would be 0xe84/4 = 0x3a1
  // bytes along, and one that read 0x388 as an element index into the linked
  // object would be 0x388/1 but from the wrong base entirely, so the two
  // measurements are checked separately and against their own bases.
  const std::uintptr_t receiver_base = reinterpret_cast<std::uintptr_t>(fixture.receiver());
  const std::uintptr_t linked_base = reinterpret_cast<std::uintptr_t>(fixture.linked());
  check(reinterpret_cast<std::uintptr_t>(fixture.receiver()) + kReceiverLinkDisplacement ==
        receiver_base + 0xe84);
  check(linked_base + kLinkedFlagDisplacement ==
        reinterpret_cast<std::uintptr_t>(fixture.linked()) + 0x388);
  // The two displacements are on two DIFFERENT bases, which is the point the
  // machine makes with EAX rather than ECX in the second operand.
  check(receiver_base + kReceiverLinkDisplacement != linked_base + kLinkedFlagDisplacement);
}

// The body stores nothing. Its two memory effects are the load at 0xe84 and the
// load at 0x388, and both bytes of the machine image are unchanged afterwards --
// the receiver including the word at 0xe84, and the linked object including the
// byte at 0x388.
void test_body_writes_no_memory() {
  Fixture fixture;
  build(fixture, kScenarios[1]);

  std::uint8_t receiver_before[model::kReceiverArenaBytes];
  std::uint8_t linked_before[model::kLinkedArenaBytes];
  std::memcpy(receiver_before, fixture.receiver_arena, model::kReceiverArenaBytes);
  std::memcpy(linked_before, fixture.linked_arena, model::kLinkedArenaBytes);

  check(call_entry(fixture.receiver()) == 1u);

  check(std::memcmp(receiver_before, fixture.receiver_arena, model::kReceiverArenaBytes) == 0);
  check(std::memcmp(linked_before, fixture.linked_arena, model::kLinkedArenaBytes) == 0);

  // The same on the other two outcomes.
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture other;
    build(other, kScenarios[index]);
    std::uint8_t before[model::kReceiverArenaBytes];
    std::memcpy(before, other.receiver_arena, model::kReceiverArenaBytes);
    check(call_entry(other.receiver()) == kScenarios[index].expect);
    check(std::memcmp(before, other.receiver_arena, model::kReceiverArenaBytes) == 0);
  }
}

// Both exits write EAX in full, so none of a poisoned EAX survives the call.
// This is what separates "returns a 32-bit value" from "returns a byte in AL".
void test_return_value_is_a_full_32_bit_eax() {
  Fixture poisoned;
  build(poisoned, kScenarios[1]);
  check(call_entry_with_poisoned_eax(poisoned.receiver()) == 1u);

  Fixture cleared;
  build(cleared, kScenarios[0]);
  check(call_entry_with_poisoned_eax(cleared.receiver()) == 0u);

  Fixture absent;
  build(absent, kScenarios[3]);
  check(call_entry_with_poisoned_eax(absent.receiver()) == 0u);
}

// The receiver arrives in ECX and the callee pops nothing, so ESP before the
// call equals ESP after it returns. Measured, not asserted as a convention.
void test_abi_receiver_in_ecx_and_caller_cleans_up() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture fixture;
    build(fixture, kScenarios[index]);

    const EspSamples samples = call_entry_measured(fixture.receiver());
    check(samples.after_return == samples.before_call);
    // Repeated calls must not drift the stack either: a callee that popped a
    // word would show it here on the second call as well.
    const EspSamples again = call_entry_measured(fixture.receiver());
    check(again.after_return == again.before_call);
    check(again.after_return == samples.before_call);
    check(call_entry(fixture.receiver()) == kScenarios[index].expect);
  }
  check(sizeof(AbiLinkedFlagProbe00c0c0e0) == sizeof(void*));
}

// The entry is reached with the receiver in ECX and nothing pushed; the address
// the trampoline calls is the reconstruction's own.
void test_entry_is_reached_through_ecx() {
  Fixture fixture;
  build(fixture, kScenarios[1]);
  check(entry_address() == pointer_word(reinterpret_cast<const void*>(&linked_flag_probe_00c0c0e0)));
  // If the reconstruction read its argument from the stack instead of ECX, the
  // ECX-loaded receiver would be ignored and the call would fault or read a
  // garbage pointer; reaching the positive answer through ECX is the assertion.
  check(call_entry(fixture.receiver()) == 1u);
}

int run_tests() {
  test_reconstruction_satisfies_every_scenario();
  test_every_mutant_is_refuted();
  test_each_decision_is_individually_pinned();
  test_displacements_are_offsets_not_indices();
  test_body_writes_no_memory();
  test_return_value_is_a_full_32_bit_eax();
  test_abi_receiver_in_ecx_and_caller_cleans_up();
  test_entry_is_reached_through_ecx();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_00c0c0e0_linked_flag_probe::run_tests();
}

#undef PKG_00C0C0E0_THISCALL
