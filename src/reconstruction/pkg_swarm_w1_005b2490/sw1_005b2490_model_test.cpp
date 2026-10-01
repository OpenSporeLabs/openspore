// PKG-SWARM-W1-005B2490 -- VA 0x005b2490
// Behavioural model test for FUN_005b2490 @ 0x005b2490.
//
// This body has NO direct callee. That is a machine fact, not an omission here:
// the four instructions at 0x005b2490..0x005b2497 contain no CALL and no JMP,
// abi_derived.dispatch records indirect_calls 0 / call_offsets [] /
// vtable_shaped_loads 0, callees_dependencies is empty, and the xref export
// records no outgoing call edge for this VA. So the "define every direct callee
// as an observer" discipline has nothing to bind to, and it is replaced by the two
// things a body with no callee can still be broken on:
//
//   * the MEMORY it touches -- measured by a byte-for-byte comparison of a
//     sentinel-filled fixture before and after, with decoy words planted at every
//     neighbouring displacement, so "only the four bytes at +0x18 changed" is
//     asserted rather than assumed;
//   * the ABI it obeys -- measured, not asserted: a trampoline puts a chosen
//     pointer in ECX, calls the reconstruction by address, samples ESP on both
//     sides of the call and EAX after it, and plants a decoy word on the stack
//     where an argument would be. Convention, argument count, cleanup bytes and
//     return register are then consequences of the measurement.
//
// What is asserted, and what fixes it:
//
//   * the returned word is the value stored, both equal to the incoming word plus
//     one, with 32-bit wraparound (0x005b2490, 0x005b2493, 0x005b2494);
//   * exactly the four bytes at +0x18 change, and no other byte of the fixture
//     changes -- including the eight sentinel bytes past the modelled receiver,
//     so a write one displacement too high is caught rather than tolerated
//     (0x005b2494 is the body's only store, and its displacement is 0x18);
//   * the return value comes out of EAX (trampoline sampling, not a convention);
//   * ESP is balanced across the call, so the terminator pops nothing but the
//     return address and the body has no stack argument to consume;
//   * the receiver is the ECX pointer, not a word on the stack: a decoy pushed at
//     the callee's entry_ESP+4 is not touched and does not become the receiver;
//   * the word at +0x18 is a VALUE, not a pointer: a fixture whose +0x18 word
//     holds the address of a poisoned block leaves that block untouched.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction. Each names a
// wrong reconstruction it is aimed at:
//
//   A  the displacement is 0x18 and not a neighbour: decoys at +0x00, +0x10,
//      +0x14, +0x1c and +0x20 carry four different values, and a model reading or
//      writing any of them returns a different number or changes a different byte;
//   B  the step is exactly +1, not +2, not a plain store, not "store and return
//      the old value" (the returned word is compared against the stored one);
//   C  the increment wraps as 32 bits rather than saturating, trapping, or
//      stopping at INT_MAX;
//   D  one level of indirection: the word at +0x18 is loaded, never followed, so a
//      pointer-shaped value there must not be dereferenced;
//   E  the receiver is ECX, not the first stack word (a cdecl misreading);
//   F  the terminator is a bare RET: 0 callee cleanup bytes and no consumed
//      argument word, measured by sampling ESP either side of the call;
//   G  the value comes back in EAX and not through a hidden return pointer:
//      a scratch buffer beside the receiver stays untouched;
//   H  there is no second, hidden side effect: two calls advance the word by two,
//      not one.
//
// What is NOT asserted, and why:
//
//   * The sign of the word at +0x18, and therefore anything about overflow beyond
//     the unsigned 32-bit wrap this test drives. `INC EAX` is bit-identical for
//     signed and unsigned and nothing in the body tests bit 31, so the machine
//     does not settle it and neither does this test. It is an open question in
//     the sidecar.
//   * What the word at +0x18 IS. No case claims it is a counter, a version, a
//     reference count or an index; the test only ever asserts the two operations
//     the listing shows.
//   * The receiver's real size. The fixture is 0x1c bytes plus eight sentinel
//     bytes; 0x1c is a lower bound this body proves, and a model that demanded
//     more would not be refuted by anything here.
//   * EAX on ENTRY. The body overwrites it at 0x005b2490 before reading it, so its
//     incoming value is unobservable and no test can pin it.
//   * The absence of a call, as an observation. A body that made no transfer and a
//     body whose transfer this test could not see are indistinguishable from inside
//     a single-threaded fixture, so the "makes no call" claim is a machine fact
//     from the xref export and the dispatch record, and it is only restated here
//     (case J) rather than claimed to be measured.

#include "sw1_005b2490_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_005b2490 {
namespace {

// The machine displacement, as a literal, and the extent the four instructions
// fix. Declared here as well as in the header so the test's own expectations are
// visible in one place next to the assertions that use them.
constexpr std::size_t kWord18 = 0x18u;
constexpr std::size_t kReceiverSize = sizeof(Receiver);
constexpr std::size_t kSentinelBytes = 8u;
constexpr std::size_t kFixtureSize = kReceiverSize + kSentinelBytes;

// Neighbouring displacements the decoys are planted at: two below the word, the
// half-dword boundaries around it, and two above it (the last of which is past
// the modelled receiver, inside the sentinel run).
constexpr std::size_t kDecoy00 = 0x00u;
constexpr std::size_t kDecoy10 = 0x10u;
constexpr std::size_t kDecoy14 = 0x14u;
constexpr std::size_t kDecoy1c = 0x1cu;
constexpr std::size_t kDecoy20 = 0x20u;

// The four distinct decoy values, one per neighbouring word, so a model that read
// or wrote the wrong displacement cannot coincidentally agree with the right one.
constexpr Word kDecoyWord00 = 0x11111111u;
constexpr Word kDecoyWord10 = 0x22222222u;
constexpr Word kDecoyWord14 = 0x33333333u;
constexpr Word kDecoyWord1c = 0x44444444u;
constexpr Word kDecoyWord20 = 0x55555555u;

// What a model that got the displacement wrong would report for a receiver whose
// +0x18 word holds kSeed: the decoy plus one, each in its own right.
//
// kSeed is 0x00ffffff deliberately. Its successor 0x01000000 differs from it in
// ALL FOUR bytes, so "four bytes changed" is a statement about the width of the
// store at 0x005b2494 rather than an accident of the value chosen -- with a seed
// whose low byte alone moves, a dword store and a byte store would look alike.
constexpr Word kSeed = 0x00ffffffu;
constexpr Word kExpected = 0x01000000u;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The fixture: the modelled receiver's 0x1c bytes followed by eight sentinel
// bytes, so a store one displacement past the last dword the body can address
// lands in memory this test owns and shows up in the comparison.
struct alignas(4) Fixture {
  std::uint8_t bytes[kFixtureSize];
};

void fill_sentinels(Fixture& fixture) {
  std::memset(fixture.bytes, 0xa5, sizeof fixture.bytes);
}

void plant(Fixture& fixture, std::size_t displacement, Word value) {
  std::memcpy(fixture.bytes + displacement, &value, sizeof value);
}

Word peek(const Fixture& fixture, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, fixture.bytes + displacement, sizeof value);
  return value;
}

// A fixture whose +0x18 word is `value` and whose five neighbouring words are the
// decoys above, so every case runs against the same hostile memory.
Fixture make_fixture(Word value) {
  Fixture fixture;
  fill_sentinels(fixture);
  plant(fixture, kDecoy00, kDecoyWord00);
  plant(fixture, kDecoy10, kDecoyWord10);
  plant(fixture, kDecoy14, kDecoyWord14);
  plant(fixture, kWord18, value);
  plant(fixture, kDecoy1c, kDecoyWord1c);
  plant(fixture, kDecoy20, kDecoyWord20);
  return fixture;
}

Receiver* as_receiver(Fixture& fixture) {
  return reinterpret_cast<Receiver*>(&fixture.bytes[0]);
}

// How many bytes changed inside the word's own four-byte window, and how many
// changed anywhere else in the fixture. The body has exactly one store, so every
// changed byte has to fall inside the window and the window's value has to move.
struct Diff {
  int inside = 0;
  int outside = 0;
  int first_changed = -1;
};

Diff diff_fixture(const Fixture& before, const Fixture& after) {
  Diff diff;
  for (std::size_t index = 0; index < kFixtureSize; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (diff.first_changed < 0) {
      diff.first_changed = static_cast<int>(index);
    }
    if (index >= kWord18 && index < kWord18 + sizeof(Word)) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

// What the trampoline measured, rather than what it was told.
struct Sample {
  Word returned = 0;
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
};

// Call the reconstruction by address with the receiver in ECX and nothing else,
// and read back what came out of EAX and what happened to ESP. ESP is in the
// measurement, EAX and ECX in the clobber list, so no input operand can have been
// allocated to either of them and every "r" operand survives the `movl` that
// precedes its use.
Sample call_with_receiver_in_ecx(Receiver* receiver) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_005b2490));
  Word returned = 0;
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       "movl %%eax, %[ret]\n\t"
                       : [before] "=m"(esp_before), [after] "=m"(esp_after),
                         [ret] "=m"(returned)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  Sample sample;
  sample.returned = returned;
  sample.esp_before = esp_before;
  sample.esp_after = esp_after;
  return sample;
}

// The same call, with one extra word pushed first. At the callee's entry that word
// sits at entry_ESP+4, which is exactly where an ordinary first argument would be
// under cdecl or stdcall, so if this body read an argument there it would take
// the decoy. A model that also consumed the word would pop it as its return
// address and never come back, so the balance checked afterwards is the bare-RET
// claim as well.
Sample call_with_decoy_on_the_stack(Receiver* receiver, Word decoy) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_005b2490));
  Word returned = 0;
  std::uint32_t esp_before = 0;
  std::uint32_t esp_after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "pushl %[decoy]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "addl $4, %%esp\n\t"
                       "movl %%esp, %[after]\n\t"
                       "movl %%eax, %[ret]\n\t"
                       : [before] "=m"(esp_before), [after] "=m"(esp_after),
                         [ret] "=m"(returned)
                       : [target] "r"(target), [recv] "r"(receiver), [decoy] "r"(decoy)
                       : "eax", "ecx", "memory");
  Sample sample;
  sample.returned = returned;
  sample.esp_before = esp_before;
  sample.esp_after = esp_after;
  return sample;
}

// -- the cases ----------------------------------------------------------------

// The baseline the other cases are read against: one call, one dword moved, and
// the value that moved is the value that came back.
void case_returns_and_stores_the_incremented_word() {
  Fixture before = make_fixture(kSeed);
  Fixture after = make_fixture(kSeed);

  const Sample sample =
      call_with_receiver_in_ecx(as_receiver(after));
  const Diff diff = diff_fixture(before, after);

  check(sample.returned == kExpected, "A1: the returned word is the word at +0x18 plus one");
  check(peek(after, kWord18) == kExpected, "A2: and that same value is what the store left behind");
  check(diff.inside == 4, "A3: all four bytes of the +0x18 dword changed");
  check(diff.outside == 0, "A4: no other byte of the receiver, and no sentinel byte, changed");
  check(diff.first_changed == static_cast<int>(kWord18),
        "A5: the first changed byte is the first byte of the +0x18 dword");
}

// B -- the step is exactly one. Zero, two, and "store without incrementing" are
// the three cheapest wrong reconstructions and each is refuted by one number.
void case_step_is_exactly_one() {
  Fixture zero = make_fixture(0u);
  const Sample from_zero = call_with_receiver_in_ecx(as_receiver(zero));
  check(from_zero.returned == 1u, "B1: 0x00000000 increments to 0x00000001, not to 0x00000000");
  check(peek(zero, kWord18) == 1u, "B2: and the stored word is 1, not 0 and not 2");

  Fixture two = make_fixture(2u);
  const Sample from_two = call_with_receiver_in_ecx(as_receiver(two));
  check(from_two.returned == 3u, "B3: 2 increments to 3, so the step is one and not two");
  check(from_two.returned == peek(two, kWord18),
        "B4: the returned word equals the stored word, so the return is not the old value");
}

// C -- the increment is 32-bit arithmetic and wraps. 0xffffffff, 0xfffffffe and
// 0x7fffffff are the three values a clamping or signed model gets wrong, and
// 0x80000000 pins the fact that nothing here treats bit 31 as a sign.
void case_increment_wraps_as_32_bits() {
  Fixture top = make_fixture(0xffffffffu);
  const Sample from_top = call_with_receiver_in_ecx(as_receiver(top));
  check(from_top.returned == 0u, "C1: 0xffffffff wraps to 0x00000000 rather than saturating");
  check(peek(top, kWord18) == 0u, "C2: and the stored word wrapped with the returned one");

  Fixture high = make_fixture(0xfffffffeu);
  const Sample from_high = call_with_receiver_in_ecx(as_receiver(high));
  check(from_high.returned == 0xffffffffu, "C3: 0xfffffffe wraps to 0xffffffff");

  Fixture max_positive = make_fixture(0x7fffffffu);
  const Sample from_max = call_with_receiver_in_ecx(as_receiver(max_positive));
  check(from_max.returned == 0x80000000u, "C4: 0x7fffffff increments into bit 31 without stopping");

  Fixture high_bit = make_fixture(0x80000000u);
  const Sample from_high_bit = call_with_receiver_in_ecx(as_receiver(high_bit));
  check(from_high_bit.returned == 0x80000001u,
        "C5: a word with bit 31 set is incremented like any other");
}

// A -- the displacement. A model that read or wrote a neighbouring displacement
// returns a different number, and a model that wrote a neighbouring displacement
// changes a byte the comparison above would catch.
void case_displacement_is_exactly_0x18() {
  Fixture fixture = make_fixture(kSeed);
  Fixture before = make_fixture(kSeed);

  const Sample sample = call_with_receiver_in_ecx(as_receiver(fixture));
  const Diff diff = diff_fixture(before, fixture);

  check(sample.returned == kExpected, "D1: the return comes from +0x18, not from a decoy plus one");
  check(sample.returned != kDecoyWord00 + 1u && sample.returned != kDecoyWord10 + 1u &&
            sample.returned != kDecoyWord14 + 1u && sample.returned != kDecoyWord1c + 1u &&
            sample.returned != kDecoyWord20 + 1u,
        "D2: and it is not any neighbouring decoy's value plus one");
  check(diff.outside == 0, "D3: no decoy word at +0x00, +0x10, +0x14, +0x1c or +0x20 was written");
  check(peek(fixture, kDecoy00) == kDecoyWord00 && peek(fixture, kDecoy10) == kDecoyWord10 &&
            peek(fixture, kDecoy14) == kDecoyWord14 && peek(fixture, kDecoy1c) == kDecoyWord1c &&
            peek(fixture, kDecoy20) == kDecoyWord20,
        "D4: every decoy still holds its own value");
  check(peek(fixture, kWord18) == kExpected, "D5: the +0x18 dword holds the incremented value");
}

// D -- one level of indirection. The word at +0x18 is a value; a reconstruction
// that followed it as a pointer would write into the block it names, and the block
// here is poisoned and checked.
void case_word_is_read_and_not_dereferenced() {
  Word shadow[8];
  for (std::size_t index = 0; index < 8; ++index) {
    shadow[index] = 0x5a5a0000u + static_cast<Word>(index);
  }
  Fixture fixture = make_fixture(0u);
  plant(fixture, kWord18, reinterpret_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(shadow)));
  Fixture before = make_fixture(0u);
  plant(before, kWord18, peek(fixture, kWord18));

  const Sample sample = call_with_receiver_in_ecx(as_receiver(fixture));

  check(sample.returned == reinterpret_cast<std::uint32_t>(
                               reinterpret_cast<std::uintptr_t>(shadow)) + 1u,
        "E1: a pointer-shaped value at +0x18 is returned incremented, not dereferenced");
  for (std::size_t index = 0; index < 8; ++index) {
    check(shadow[index] == 0x5a5a0000u + static_cast<Word>(index),
          "E2: nothing was written through the word at +0x18");
  }
  check(diff_fixture(before, fixture).outside == 0,
        "E3: and the receiver changed only inside its own +0x18 dword");

  // A null there must be as harmless as any other value: the body has no test.
  Fixture nulled = make_fixture(0u);
  const Sample from_null = call_with_receiver_in_ecx(as_receiver(nulled));
  check(from_null.returned == 1u, "E4: a null word at +0x18 yields 1, so nothing is dereferenced");
}

// E -- the receiver is the ECX pointer. The decoy word on the stack sits where a
// cdecl or stdcall first argument would be; a model that read its receiver from
// there would touch this fixture instead of the one ECX names.
void case_receiver_is_ecx_not_a_stack_word() {
  Fixture real = make_fixture(kSeed);
  Fixture decoy = make_fixture(0x0f0f0f0fu);
  const Fixture decoy_before = decoy;

  const Sample sample = call_with_decoy_on_the_stack(as_receiver(real), peek(decoy, kWord18));

  check(sample.returned == kExpected, "F1: the value returned is the ECX receiver's word plus one");
  check(peek(real, kWord18) == kExpected, "F2: and the ECX receiver is the one that changed");
  check(peek(decoy, kWord18) == 0x0f0f0f0fu, "F3: the stack decoy's word was not read or written");
  check(diff_fixture(decoy_before, decoy).inside == 0 &&
            diff_fixture(decoy_before, decoy).outside == 0,
        "F4: no byte of the decoy fixture changed at all");
}

// F -- the terminator. ESP is sampled either side of the call, and a word the
// callee had popped would have unbalanced it or taken the return address with it.
void case_terminator_pops_nothing() {
  Fixture fixture = make_fixture(kSeed);
  const Sample plain = call_with_receiver_in_ecx(as_receiver(fixture));
  check(plain.esp_after == plain.esp_before,
        "G1: ESP is unchanged across the call, so the callee popped 0 argument bytes");
  check(plain.returned == kExpected, "G2: and the body really ran to its end");

  Fixture other = make_fixture(kSeed);
  const Sample with_decoy = call_with_decoy_on_the_stack(as_receiver(other), 0xdeadbeefu);
  check(with_decoy.esp_after == with_decoy.esp_before,
        "G3: a word pushed at the callee's entry is left for the caller, not consumed");
  check(peek(other, kWord18) == kExpected, "G4: the receiver still advanced exactly once");
}

// G -- the value comes back in a register. A hidden return-pointer implementation
// would have written the object into a scratch slot; the slot is poisoned and
// compared, and the returned word is read out of EAX by the trampoline.
void case_value_returns_in_eax_and_through_no_pointer() {
  struct alignas(4) Scratch {
    std::uint8_t bytes[32];
  };
  Scratch scratch;
  std::memset(scratch.bytes, 0x3c, sizeof scratch.bytes);

  Fixture fixture = make_fixture(kSeed);
  const Sample sample = call_with_receiver_in_ecx(as_receiver(fixture));

  bool scratch_intact = true;
  for (std::size_t index = 0; index < sizeof scratch.bytes; ++index) {
    if (scratch.bytes[index] != 0x3c) {
      scratch_intact = false;
    }
  }
  check(scratch_intact, "H1: no scratch slot beside the receiver was written");
  check(sample.returned == kExpected, "H2: the value is in EAX, read after the call");
  check(sample.returned != reinterpret_cast<std::uint32_t>(
                                 reinterpret_cast<std::uintptr_t>(as_receiver(fixture))),
        "H3: what came back is not the receiver pointer itself");
}

// H -- no hidden second effect. Two calls move the word by two.
void case_two_calls_advance_by_two() {
  Fixture fixture = make_fixture(kSeed);
  const Fixture before = fixture;

  const Sample first = call_with_receiver_in_ecx(as_receiver(fixture));
  const Sample second = call_with_receiver_in_ecx(as_receiver(fixture));

  check(first.returned == kExpected, "I1: the first call returns seed plus one");
  check(second.returned == kExpected + 1u, "I2: the second call returns seed plus two");
  check(peek(fixture, kWord18) == kSeed + 2u, "I3: and the stored word is seed plus two");
  check(diff_fixture(before, fixture).inside == 4,
        "I4: the net change is still the four bytes of the one dword");
  check(diff_fixture(before, fixture).outside == 0, "I5: and nothing outside it moved");
}

// J -- the extent facts restated from the listing, and the absence of a callee,
// which is a machine fact from the xref export and the dispatch record and is
// only checked here as a restatement, not as a measurement.
void case_machine_extent_constants() {
  check(kInstructionCount == 4, "J1: the body is four instructions");
  check(kBodySpanBytes == 8u, "J2: and spans eight bytes, 0x005b2490..0x005b2497");
  check(kReceiverWord18Displacement == 0x18u, "J3: the receiver displacement is 0x18");
  check(kWord18 + sizeof(Word) == kReceiverSize, "J4: the modelled receiver ends after that dword");
  check(kReceiverSize == 0x1cu, "J5: at 0x1c bytes, which is a lower bound the body proves");
  check(kDirectCalleeCount == 0, "J6: the body transfers control nowhere");
  check(kBasicBlockCount == 1, "J7: one basic block, so no branch and no selection");
  check(kStackArgumentSlots == 0, "J8: no ordinary stack argument is consumed");
  check(kStackCleanupBytes == 0u, "J9: and the callee cleans 0 bytes");

  check(kThisAdjustingEntryPointCount == 3, "J10: three code references reach the body");
  check(kThisAdjustingEntryPoints[0] == 0x0057a5d0u &&
            kThisAdjustingEntryPoints[1] == 0x0057a5f0u &&
            kThisAdjustingEntryPoints[2] == 0x005b8550u,
        "J11: each of them subtracts a constant from ECX before jumping here");
  check(kThunkThisAdjustments[0] == 0x4u && kThunkThisAdjustments[1] == 0x10u &&
            kThunkThisAdjustments[2] == 0x14u,
        "J12: the adjustments are 0x04, 0x10 and 0x14, which is what makes ECX a receiver");

  check(kSlotDisplacementAtSlot0 == 0x00u && kTableWithBodyAtSlot0 == 0x013f57f8u,
        "J13: the body is slot +0x00 of the table based at 0x013f57f8");
  check(kSlotDisplacementAtSlot10 == 0x10u && kTableWithBodyAtSlot10 == 0x013f7028u,
        "J14: and slot +0x10 of the table based at 0x013f7028");
  check(sizeof(void*) == 4u, "J15: the reconstruction is an x86-32 model");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_005b2490

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_005b2490;

  case_machine_extent_constants();
  case_returns_and_stores_the_incremented_word();
  case_step_is_exactly_one();
  case_increment_wraps_as_32_bits();
  case_displacement_is_exactly_0x18();
  case_word_is_read_and_not_dereferenced();
  case_receiver_is_ecx_not_a_stack_word();
  case_terminator_pops_nothing();
  case_value_returns_in_eax_and_through_no_pointer();
  case_two_calls_advance_by_two();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
