// PKG-SWARM-W1-00DD0BC0 -- VA 0x00dd0bc0
// Behavioural model test for the scalar deleting destructor at 0x00dd0bc0.
//
// Both direct callees -- 0x00642190 (the base destructor) and 0x00f47380 (the
// deallocation port) -- are defined here as observers, so the test sees every
// transfer the reconstruction makes, with which argument, in which order, and gets
// to decide what each of them does to memory. Each observer also samples the
// receiver AT THE MOMENT OF THE CALL, which is what makes the write ordering
// testable rather than merely assertable.
//
// What is asserted is what the 14-instruction listing fixes and nothing more:
//
//   * exactly two transfers, one to 0x00642190 and one to 0x00f47380, in that
//     order, the second one only on the deallocating arm;
//   * the base destructor runs on BOTH arms, so the destruction is unconditional;
//   * three dword stores into the receiver, at displacements 0x00, 0x10 and 0x14,
//     with the immediates 0x0147c9f8, 0x0147c9e8 and 0x0147cc78 -- checked by
//     exact value AND by a byte-level diff of the whole object, so "only those
//     twelve bytes changed" is asserted rather than assumed;
//   * all three stores precede BOTH calls (measured inside each observer);
//   * the deallocation port receives the receiver's own address, not a member of
//     it and not a pointer to it;
//   * the branch condition: bit 0 of the low byte of the flag word, and nothing
//     else, with a table of inputs on which a non-zero test, a 0x2 mask, an
//     inverted polarity and a wrong displacement all disagree;
//   * the returned word is the receiver on both arms, checked both by a direct
//     call and by reading EAX after a raw call;
//   * the flag occupies one four-byte stack slot and the CALLEE pops it
//     (RET 0x4), measured by sampling ESP around a raw call rather than asserted
//     as a convention.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   M1 wrong constant: the three immediates are 0x147c9f8 / 0x147c9e8 / 0x147cc78
//      in that order at those displacements, and three other plausible table
//      addresses planted as decoys in the object's untouched words are not used;
//   M2 off-by-one displacement in either direction: the words at +0x04, +0x08,
//      +0x0c, +0x18, +0x1c and +0x20 are planted and must be untouched, and the
//      count of changed bytes is pinned at exactly twelve;
//   M3 wrong branch polarity: 0x00 must not deallocate and 0x01 must;
//   M4 wrong mask: 0x02, 0x04, 0x80, 0x100 and 0xfe must all NOT deallocate, and
//      0x03, 0xff and 0x101 must, so "any non-zero" and "mask 0x2" both die;
//   M5 wrong pointer level: the port gets the receiver's address, not
//      receiver+0x10 and not the address of the receiver variable;
//   M6 wrong write ordering: a body that deallocates before storing, or stores
//      after the base destructor, is caught by the observers reading the words
//      mid-call;
//   M7 missing store: a body that installs only the primary dispatch word is
//      caught by the two subobject words and by the twelve-byte count;
//   M8 receiver mutated through a copy: a body that stored into a local instead
//      of into the receiver leaves the object untouched and fails the diff;
//   M9 wrong return: null, or the receiver's +0x10, or nothing at all;
//  M10 wrong ABI: a caller-cleaned variant leaves ESP four bytes low after a raw
//      call, and the measurement compares it against the pre-push value.
//
// What is NOT asserted, and why:
//
//   * The order AMONG the three stores. All three precede both calls, and that is
//     measured (M6). Their relative order is not observable at any callee
//     boundary this test can place, so asserting it would be asserting a
//     property of the listing's text rather than of the body.
//   * The WIDTH of the flag read. The machine reads one byte and masks 0x01; bit 0
//     of the low byte IS bit 0 of the four-byte slot, so no input whatsoever
//     distinguishes a one-byte read from a four-byte read of bit 0. The declared
//     parameter type is therefore not observable from this body and the test makes
//     no claim about it; what IS observable, and asserted, is that the slot is four
//     bytes wide and popped by the callee (M10).
//   * The caller-side cleanup of the deallocation call, 0x00dd0be9 `ADD ESP,0x4`.
//     This is stated as a limit rather than as a passing check, because it is one.
//     The port is a black box here, and for a leaf callee a callee-pops return and a
//     caller-pops return are the same machine behaviour: mutating this file's own
//     port observer to `return` instead of popping the word, and again to pop it
//     twice, both leave every check in this file green. The convention is fixed by
//     0x00f47394 being a bare `C3`, which is real evidence, but it is not evidence a
//     black-box observer can exercise. M10 covers the OTHER cleanup, the flag word's
//     own `RET 0x4`, which is a whole dword on top of a call the body makes itself
//     and is genuinely measurable.
//   * What 0x00642190 and 0x00f47380 do internally. Both are observers here. The
//     only facts this package uses about either are the ones its own body needs:
//     0x00642190's tail-jump terminator (so it pops no caller argument) and
//     0x00f47380's bare `C3` (so the caller drops the pushed word). Neither
//     observer implements any of 0x00642190's real behaviour.
//   * That the three stored constants are "the right" class tables. The test
//     asserts the literal values, which the three MOV immediates fix, and nothing
//     about what they are for.
//   * The object's total size, its class, its SDK name and its RTTI. No record in
//     this repository establishes any of them. The 0xcc bytes of padding after
//     0x00dd0bf1 are not modelled because nothing can reach them.

#include "sw1_00dd0bc0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0 {
namespace {

// Machine facts as literals, restated so the test is readable without the header.
constexpr std::size_t kObjectBytes = 0x18u;
constexpr std::size_t kD00 = 0x00u;
constexpr std::size_t kD10 = 0x10u;
constexpr std::size_t kD14 = 0x14u;
constexpr Word kV00 = 0x0147c9f8u;
constexpr Word kV10 = 0x0147c9e8u;
constexpr Word kV14 = 0x0147cc78u;

enum Call : int {
  kCallBaseDestroy = 0,
  kCallDeallocate = 1,
};

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Observation {
  int log[8] = {};
  int log_length = 0;

  int destroy_calls = 0;
  OpaqueSporepediaAsset* destroy_receiver = nullptr;
  // Sampled INSIDE the call, so the position of the three stores relative to this
  // call is observable: a bitmask of which of the three words were already stored.
  int destroy_stored_mask = 0;
  int destroy_other_bytes_changed = 0;

  int free_calls = 0;
  Word free_address = 0;
  int free_stored_mask = 0;
  int free_other_bytes_changed = 0;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < 8) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }

  bool log_is(Call a) const {
    return log_length == 1 && log[0] == static_cast<int>(a);
  }
  bool log_is(Call a, Call b) const {
    return log_length == 2 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b);
  }
};

Observation g_obs;

// The object under test, with a sentinel tail so an overrun past 0x17 -- and the
// decoy words the refutation cases plant at 0x18, 0x1c and 0x20 -- all live inside
// the harness rather than in the test's own stack frame.
constexpr std::size_t kHarnessBytes = kObjectBytes + 16u;

struct Harness {
  unsigned char bytes[kHarnessBytes];

  OpaqueSporepediaAsset* asset() {
    return reinterpret_cast<OpaqueSporepediaAsset*>(bytes);
  }
};

// The snapshot the observers compare against, taken before the body runs. Held at
// namespace scope so an observer can diff without a dangling local.
unsigned char g_before[kHarnessBytes];

// Which of the three stored words already hold the listing's value, and how many
// bytes outside them have changed. This is the mid-call measurement.
void sample_now(const unsigned char* bytes, int* stored_mask, int* other_changed) {
  int mask = 0;
  if (bytes[kD00 + 0] == static_cast<unsigned char>(kV00) &&
      bytes[kD00 + 1] == static_cast<unsigned char>(kV00 >> 8) &&
      bytes[kD00 + 2] == static_cast<unsigned char>(kV00 >> 16) &&
      bytes[kD00 + 3] == static_cast<unsigned char>(kV00 >> 24)) {
    mask |= 1;
  }
  if (bytes[kD10 + 0] == static_cast<unsigned char>(kV10) &&
      bytes[kD10 + 1] == static_cast<unsigned char>(kV10 >> 8) &&
      bytes[kD10 + 2] == static_cast<unsigned char>(kV10 >> 16) &&
      bytes[kD10 + 3] == static_cast<unsigned char>(kV10 >> 24)) {
    mask |= 2;
  }
  if (bytes[kD14 + 0] == static_cast<unsigned char>(kV14) &&
      bytes[kD14 + 1] == static_cast<unsigned char>(kV14 >> 8) &&
      bytes[kD14 + 2] == static_cast<unsigned char>(kV14 >> 16) &&
      bytes[kD14 + 3] == static_cast<unsigned char>(kV14 >> 24)) {
    mask |= 4;
  }
  int others = 0;
  for (std::size_t index = 0; index < kHarnessBytes; ++index) {
    const bool inside = (index >= kD00 && index < kD00 + 4) ||
                        (index >= kD10 && index < kD10 + 4) ||
                        (index >= kD14 && index < kD14 + 4);
    if (!inside && bytes[index] != g_before[index]) {
      ++others;
    }
  }
  *stored_mask = mask;
  *other_changed = others;
}

}  // namespace

// 0x00dd0bd7 -- the base destructor. Receiver in ECX, no stack argument. The
// observer samples the three stored words at the moment of the call, which is the
// whole point: the three stores are instructions 3, 4 and 5 and this call is
// instruction 6.
extern "C" void PKG_SWARM_W1_00DD0BC0_THISCALL sporepedia_asset_destroy_00642190(
    OpaqueSporepediaAsset* asset) {
  ++g_obs.destroy_calls;
  g_obs.record(kCallBaseDestroy);
  g_obs.destroy_receiver = asset;
  sample_now(reinterpret_cast<const unsigned char*>(asset), &g_obs.destroy_stored_mask,
             &g_obs.destroy_other_bytes_changed);
}

// 0x00dd0be4 -- the deallocation port. cdecl, one pushed word, null-tolerant. The
// observer samples the same two things the base-destructor observer does, so a body
// that deallocated before storing is caught mid-call and not only by the final diff.
extern "C" void PKG_SWARM_W1_00DD0BC0_CDECL sporepedia_free_00f47380(Word address) {
  ++g_obs.free_calls;
  g_obs.record(kCallDeallocate);
  g_obs.free_address = address;
  // The callee's own contract is `MOV EAX,[esp+4]; TEST EAX,EAX; JE` -- a null
  // pointer is a no-op -- so the observer mirrors that instead of faulting, which is
  // a statement about the callee and not about the body under test.
  if (address == 0) {
    return;
  }
  sample_now(reinterpret_cast<const unsigned char*>(address), &g_obs.free_stored_mask,
             &g_obs.free_other_bytes_changed);
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0;

// The object's bytes as a diff against the pre-call snapshot: how many bytes
// changed in total, how many outside the three stored words, and which dword
// offsets moved.
struct Diff {
  int changed = 0;
  int outside = 0;
  int words_changed = 0;
};

Diff diff_against_before(const Harness& harness) {
  Diff diff;
  for (std::size_t index = 0; index < kHarnessBytes; ++index) {
    if (harness.bytes[index] == g_before[index]) {
      continue;
    }
    ++diff.changed;
    const bool inside = (index >= kD00 && index < kD00 + 4) ||
                        (index >= kD10 && index < kD10 + 4) ||
                        (index >= kD14 && index < kD14 + 4);
    if (!inside) {
      ++diff.outside;
    }
  }
  for (std::size_t base = 0; base + 4 <= kObjectBytes; base += 4) {
    if (std::memcmp(harness.bytes + base, g_before + base, 4) != 0) {
      ++diff.words_changed;
    }
  }
  return diff;
}

Word word_of(const Harness& harness, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, harness.bytes + displacement, sizeof value);
  return value;
}

void plant(Harness& harness, std::size_t displacement, Word value) {
  std::memcpy(harness.bytes + displacement, &value, sizeof value);
}

// A fresh object with recognisable, non-table poison in every word the body does
// not write, so a store to the wrong place cannot go unnoticed.
Harness make_harness() {
  Harness harness;
  std::memset(harness.bytes, 0xa5, sizeof harness.bytes);
  return harness;
}

// A raw call: one four-byte word is pushed, ECX carries the receiver, the target is
// called through a register, and ESP and EAX are sampled around it. This is what
// makes the argument's stack slot and the callee's cleanup measurable rather than
// assumed, and it lets a full 32-bit value reach the body without the C++ call site
// truncating it to the declared parameter type.
struct RawCall {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
  std::uint32_t returned = 0;
};

RawCall call_raw(OpaqueSporepediaAsset* receiver, std::uint32_t raw_flag) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_00dd0bc0));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  std::uint32_t returned = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated any
  // of the three inputs to them: every "r" operand therefore survives the
  // `movl %[recv], %%ecx` that precedes its use.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[flag]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       "movl %%eax, %[returned]\n\t"
                       : [before] "=m"(before), [after] "=m"(after), [returned] "=m"(returned)
                       : [target] "r"(target), [recv] "r"(receiver), [flag] "r"(raw_flag)
                       : "eax", "ecx", "memory");
  RawCall samples;
  samples.before_push = before;
  samples.after_return = after;
  samples.returned = returned;
  return samples;
}

// -- behaviour cases ----------------------------------------------------------

// Case A -- the flag's bit 0 is set, so the object is deallocated. The deleting
// case: both transfers run, in the order the listing gives them.
void case_flag_set_deallocates() {
  Harness harness = make_harness();
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  OpaqueSporepediaAsset* const receiver = harness.asset();
  OpaqueSporepediaAsset* const returned = re_00dd0bc0(receiver, 0x01);

  check(returned == receiver, "A1: the returned word is the receiver");
  check(g_obs.destroy_calls == 1, "A2: 0x00642190 is called exactly once");
  check(g_obs.destroy_receiver == receiver, "A3: ECX carried the receiver to 0x00642190");
  check(g_obs.free_calls == 1, "A4: 0x00f47380 is called exactly once");
  check(g_obs.log_is(kCallBaseDestroy, kCallDeallocate),
        "A5: the base destructor runs before the deallocation");
  check(word_of(harness, kD00) == kV00, "A6: the word at +0x00 is 0x0147c9f8");
  check(word_of(harness, kD10) == kV10, "A7: the word at +0x10 is 0x0147c9e8");
  check(word_of(harness, kD14) == kV14, "A8: the word at +0x14 is 0x0147cc78");
}

// Case B -- the flag's bit 0 is clear, so the object is destroyed but NOT
// deallocated, and the returned word is still the receiver. The non-deleting case,
// which a reconstruction that returned early on the non-deallocating arm would
// fail: the three stores and the base destructor still have to have happened.
void case_flag_clear_does_not_deallocate() {
  Harness harness = make_harness();
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  OpaqueSporepediaAsset* const receiver = harness.asset();
  OpaqueSporepediaAsset* const returned = re_00dd0bc0(receiver, 0x00);

  check(returned == receiver, "B1: the returned word is the receiver on the non-deleting arm too");
  check(g_obs.destroy_calls == 1, "B2: the base destructor still runs exactly once");
  check(g_obs.destroy_receiver == receiver, "B3: and it still gets the receiver");
  check(g_obs.free_calls == 0, "B4: 0x00f47380 is not called when bit 0 is clear");
  check(g_obs.log_is(kCallBaseDestroy), "B5: the base destructor is the only transfer");
  check(word_of(harness, kD00) == kV00, "B6: the word at +0x00 is still 0x0147c9f8");
  check(word_of(harness, kD10) == kV10, "B7: the word at +0x10 is still 0x0147c9e8");
  check(word_of(harness, kD14) == kV14, "B8: the word at +0x14 is still 0x0147cc78");
}

// Case C -- the deallocation is the only difference between the two flags. The two
// cases above must leave byte-identical objects except for nothing at all, which is
// the strongest single statement about the branch: this body has no other effect on
// its receiver, and no other effect on the process that the test can observe.
void case_the_flag_changes_nothing_else() {
  Harness deleting = make_harness();
  Harness keeping = make_harness();
  // The two arms run one after the other and the observers are global, so the first
  // arm's counts are captured before the second call overwrites them.
  std::memcpy(g_before, deleting.bytes, sizeof g_before);
  g_obs.reset();
  re_00dd0bc0(deleting.asset(), 0x01);
  const int deleting_free_calls = g_obs.free_calls;
  const int deleting_destroy_calls = g_obs.destroy_calls;

  std::memcpy(g_before, keeping.bytes, sizeof g_before);
  g_obs.reset();
  re_00dd0bc0(keeping.asset(), 0x00);

  check(deleting_free_calls == 1 && g_obs.free_calls == 0,
        "C1: only the flag's bit 0 decides the deallocation");
  check(deleting_destroy_calls == 1 && g_obs.destroy_calls == 1,
        "C2: the base destructor runs on both arms");
  check(std::memcmp(deleting.bytes, keeping.bytes, kHarnessBytes) == 0,
        "C3: the two arms leave byte-identical objects, so the flag's only effect is the call");
}

// Case D -- repeated calls. Three deleting calls and three non-deleting calls over
// the same object: the three stores are idempotent, so the object must settle, and
// the transfer count must be exactly what the two arms allow. A body that, say,
// incremented a word at the receiver would show up here as a seventh changed byte.
void case_repeated_calls_settle() {
  Harness harness = make_harness();
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  for (int index = 0; index < 3; ++index) {
    re_00dd0bc0(harness.asset(), 0x01);
  }
  for (int index = 0; index < 3; ++index) {
    re_00dd0bc0(harness.asset(), 0x00);
  }

  check(g_obs.destroy_calls == 6, "D1: six calls make six base-destructor calls");
  check(g_obs.free_calls == 3, "D2: only the three deleting calls deallocate");
  const Diff diff = diff_against_before(harness);
  check(diff.changed == 12 && diff.outside == 0 && diff.words_changed == 3,
        "D3: six calls still change exactly the three stored words and nothing else");
}

// -- REFUTATION CASES ---------------------------------------------------------
// The cases above show the reconstruction behaving. The ones below are aimed at
// breaking it: each states the wrong reconstruction it is trying to catch.

// M1. WRONG CONSTANT. The three immediates are 0x147c9f8, 0x147c9e8 and 0x147cc78
// in that order at those three displacements. Four other table addresses that this
// very target's own record associates with 0x00dd0bc0 (0x0147ca30, 0x0147ca70,
// 0x0147cac0, 0x0147cc88) are planted in the object's untouched words: a body that
// read an address out of a table instead of using the instruction's own immediate,
// or that swapped two of the three, would write one of them.
void case_m1_wrong_constant() {
  Harness harness = make_harness();
  const Word decoys[4] = {0x0147ca30u, 0x0147ca70u, 0x0147cac0u, 0x0147cc88u};
  plant(harness, 0x04, decoys[0]);
  plant(harness, 0x08, decoys[1]);
  plant(harness, 0x0c, decoys[2]);
  plant(harness, 0x18, decoys[3]);
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  re_00dd0bc0(harness.asset(), 0x01);

  check(word_of(harness, kD00) == kV00, "M1.1: +0x00 holds 0x0147c9f8, not a decoy");
  check(word_of(harness, kD10) == kV10, "M1.2: +0x10 holds 0x0147c9e8, not a decoy");
  check(word_of(harness, kD14) == kV14, "M1.3: +0x14 holds 0x0147cc78, not a decoy");
  check(word_of(harness, 0x04) == decoys[0] && word_of(harness, 0x08) == decoys[1] &&
            word_of(harness, 0x0c) == decoys[2] && word_of(harness, 0x18) == decoys[3],
        "M1.4: none of the four decoys was written over");
}

// M2. OFF-BY-ONE DISPLACEMENT, either direction. Every dword of the object other
// than the three the body stores is poisoned, the object is extended by a sentinel
// tail, and the number of changed bytes is pinned at exactly twelve. A body that
// stored at 0x04, 0x08, 0x0c, 0x18, 0x1c or 0x20 -- or at 0x0c/0x13/0x18 instead of
// 0x10/0x14/0x18 -- changes a byte the test catches, and the count moves off twelve.
void case_m2_displacements_are_exact() {
  Harness harness = make_harness();
  plant(harness, 0x04, 0x04040404u);
  plant(harness, 0x08, 0x08080808u);
  plant(harness, 0x0c, 0x0c0c0c0cu);
  plant(harness, 0x18, 0x18181818u);  // one past the modelled object
  plant(harness, 0x1c, 0x1c1c1c1cu);
  plant(harness, 0x20, 0x20202020u);  // two past it
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  re_00dd0bc0(harness.asset(), 0x01);

  const Diff diff = diff_against_before(harness);
  check(diff.outside == 0, "M2.1: no byte outside the three stored words changed");
  check(diff.changed == 12, "M2.2: exactly twelve bytes changed, so three whole words and no more");
  check(diff.words_changed == 3, "M2.3: exactly three dwords of the object moved");
  check(word_of(harness, 0x04) == 0x04040404u && word_of(harness, 0x08) == 0x08080808u &&
            word_of(harness, 0x0c) == 0x0c0c0c0cu,
        "M2.4: the words at +0x04, +0x08 and +0x0c are untouched");
  check(word_of(harness, 0x18) == 0x18181818u && word_of(harness, 0x1c) == 0x1c1c1c1cu &&
            word_of(harness, 0x20) == 0x20202020u,
        "M2.5: nothing past the modelled object was written either");
}

// M3 + M4. POLARITY AND MASK. One table drives the whole branch through a raw call,
// so a full 32-bit value reaches the body without the C++ call site truncating it.
// 0x00/0x02/0x04/0x80/0x100/0xfe must NOT deallocate and 0x01/0x03/0xff/0x101 must.
// That kills: an inverted test, a "non-zero" test, a 0x2 mask, a 0x4 mask, a test on
// any bit above 0, and a body that read the argument at the wrong stack displacement
// (which would see the return address's low word instead and could not produce this
// pattern at all).
void case_m3_m4_polarity_and_mask() {
  struct Row {
    std::uint32_t flag;
    bool expect_free;
  };
  // Two failures here are the test's own table being wrong, not the
  // reconstruction: 0x7f and 0x7fffffff both have bit 0 set, and the first run of
  // this case caught exactly those two rows. The table is left in the corrected
  // form because the point of the case is that bit 0 is the ONLY bit consulted --
  // 0xfe and 0xfffffffe are its two largest neighbours with bit 0 clear, and 0x80
  // and 0x80000000 are its two largest neighbours with bit 0 clear and nothing else
  // either, so a mask above 0, a "non-zero" test and an inverted test each get at
  // least one row they cannot satisfy.
  const Row rows[] = {
      {0x00000000u, false},  {0x00000001u, true},  {0x00000002u, false},
      {0x00000003u, true},   {0x00000004u, false}, {0x0000007eu, false},
      {0x0000007fu, true},   {0x00000080u, false}, {0x00000081u, true},
      {0x000000feu, false},  {0x000000ffu, true},  {0x00000100u, false},
      {0x00000101u, true},   {0x00000102u, false}, {0x7ffffffeu, false},
      {0x7fffffffu, true},   {0x80000000u, false}, {0xfffffffeu, false},
      {0xffffffffu, true},
  };

  for (const Row& row : rows) {
    Harness harness = make_harness();
    std::memcpy(g_before, harness.bytes, sizeof g_before);
    g_obs.reset();

    const RawCall raw = call_raw(harness.asset(), row.flag);

    check(raw.returned == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                             harness.asset())),
          "M3/M4: the returned word is the receiver for every flag value");
    check(g_obs.destroy_calls == 1,
          "M3/M4: the base destructor runs exactly once for every flag value");
    if (row.expect_free) {
      check(g_obs.free_calls == 1, "M3/M4: a flag with bit 0 set deallocates exactly once");
    } else {
      check(g_obs.free_calls == 0, "M3/M4: a flag with bit 0 clear never deallocates");
    }
    check(word_of(harness, kD00) == kV00 && word_of(harness, kD10) == kV10 &&
              word_of(harness, kD14) == kV14,
          "M3/M4: the three stores happen on every flag value, on both arms");
  }
}

// M5. WRONG POINTER LEVEL. The deallocation port must receive the receiver's own
// address. The first word of the object is poisoned with a plausible address, so a
// body that passed the receiver's contents, or a member of the receiver, in place of
// the receiver, is caught by the address comparison rather than only by the byte
// diff.
void case_m5_port_receives_the_receiver_address() {
  Harness harness = make_harness();
  plant(harness, 0x00, 0xfeedfaceu);  // a plausible address, to be overwritten
  std::memcpy(g_before, harness.bytes, sizeof g_before);

  g_obs.reset();
  OpaqueSporepediaAsset* const receiver = harness.asset();
  re_00dd0bc0(receiver, 0x01);

  const std::uint32_t expect = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(receiver));
  check(g_obs.free_address == expect, "M5.1: the port receives the receiver's own address");
  check(g_obs.free_address != expect + 0x10u,
        "M5.2: and not the address of the subobject dispatch word at +0x10");
  check(g_obs.free_address != expect + 0x14u,
        "M5.3: and not the address of the subobject dispatch word at +0x14");
  check(g_obs.free_address != 0xfeedfaceu,
        "M5.4: and not the pointer the object happened to contain");
  check(g_obs.destroy_receiver == receiver,
        "M5.5: the base destructor receives the same address, not a copy of it");
}

// M6. WRONG WRITE ORDERING. The three stores are instructions 3, 4 and 5; the two
// calls are 6 and 8. Each observer samples the three words and the rest of the object
// at the moment of its call, so a body that deallocates before storing, or that
// stores after the base destructor, is caught mid-call rather than only at the end.
void case_m6_stores_precede_both_calls() {
  Harness deleting = make_harness();
  std::memcpy(g_before, deleting.bytes, sizeof g_before);
  g_obs.reset();
  re_00dd0bc0(deleting.asset(), 0x01);

  check(g_obs.destroy_stored_mask == 0x7,
        "M6.1: all three words were already stored when 0x00642190 was entered");
  check(g_obs.destroy_other_bytes_changed == 0,
        "M6.2: and nothing outside them had changed at that moment either");
  check(g_obs.free_stored_mask == 0x7,
        "M6.3: all three words were still stored when 0x00f47380 was entered");
  check(g_obs.free_other_bytes_changed == 0,
        "M6.4: and still nothing outside them");

  // The same on the non-deleting arm, where only the first observation exists.
  Harness keeping = make_harness();
  std::memcpy(g_before, keeping.bytes, sizeof g_before);
  g_obs.reset();
  re_00dd0bc0(keeping.asset(), 0x00);
  check(g_obs.destroy_stored_mask == 0x7,
        "M6.5: and on the non-deleting arm too, all three precede the base destructor");
}

// M7 + M8. MISSING STORE, AND A RECEIVER MUTATED THROUGH A COPY. The final diff
// must show all three words moved, so a body that installed only the primary
// dispatch word leaves eight changed bytes instead of twelve. And because the diff
// is taken against the object the CALLER owns, a body that stored into a local copy
// and returned success leaves the object completely untouched -- zero changed bytes.
void case_m7_m8_object_moved_in_place() {
  Harness harness = make_harness();
  std::memcpy(g_before, harness.bytes, sizeof g_before);
  g_obs.reset();
  re_00dd0bc0(harness.asset(), 0x01);

  const Diff diff = diff_against_before(harness);
  check(diff.words_changed == 3 && diff.changed == 12,
        "M7: all three stored words are present, so no store is missing");
  check(diff.changed != 0,
        "M8: the object itself changed, so the stores went to the receiver and not to a copy");
  check(harness.bytes[0] != 0xa5u, "M8.2: the very first byte of the receiver moved");
  check(harness.bytes[kD10] != 0xa5u && harness.bytes[kD14] != 0xa5u,
        "M8.3: and so did the two subobject words at +0x10 and +0x14");
}

// M9. WRONG RETURN. The returned word is the receiver on both arms (cases A and B
// check it directly); here it is checked after a raw call, so the value in EAX is
// the one the machine's MOV EAX,ESI would leave, and not a value a compiler
// synthesised for the C++ call site.
void case_m9_returned_word_is_the_receiver() {
  for (std::uint32_t flag = 0; flag < 2u; ++flag) {
    Harness harness = make_harness();
    std::memcpy(g_before, harness.bytes, sizeof g_before);
    g_obs.reset();
    const RawCall raw = call_raw(harness.asset(), flag == 0u ? 0x01u : 0x00u);
    check(raw.returned == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                             harness.asset())),
          "M9: EAX holds the receiver after a raw call, on both arms");
  }
}

// M10. WRONG ABI. The terminator is `RET 0x4`, so the callee owns the flag word. A
// raw call pushes exactly four bytes and nothing else; ESP is sampled before the
// push and after the return, and the two are equal only if the callee popped all
// four. A caller-cleaned variant would leave the second sample four bytes lower.
// This is measured, not asserted as a convention.
void case_m10_argument_word_is_callee_cleaned() {
  Harness harness = make_harness();
  std::memcpy(g_before, harness.bytes, sizeof g_before);
  g_obs.reset();
  const RawCall raw = call_raw(harness.asset(), 0x01u);

  check(raw.after_return == raw.before_push,
        "M10.1: the callee popped the four-byte argument word (RET 0x4), so ESP balances");
  check(g_obs.destroy_calls == 1, "M10.2: the trampoline really reached the body");
  check(g_obs.free_calls == 1, "M10.3: and the body really ran to its end");
  check(word_of(harness, kD00) == kV00 && word_of(harness, kD10) == kV10 &&
            word_of(harness, kD14) == kV14,
        "M10.4: the three stores happened under the raw call as well");
  check(raw.after_return != raw.before_push - 4u,
        "M10.5: and the stack is not four bytes low, which is what a caller-cleaned "
        "variant would leave");
}

// The constants and offsets the reconstruction states, checked against the
// instruction operands they came from.
void verify_machine_constants() {
  check(kObjectTableAt00 == 0x0147c9f8u, "V1: 0x00dd0bc3 stores 0x0147c9f8 at +0x00");
  check(kObjectTableAt10 == 0x0147c9e8u, "V2: 0x00dd0bc9 stores 0x0147c9e8 at +0x10");
  check(kObjectTableAt14 == 0x0147cc78u, "V3: 0x00dd0bd0 stores 0x0147cc78 at +0x14");
  check(kReceiverWord00Displacement == 0x00u, "V4: the primary dispatch word is at +0x00");
  check(kReceiverWord10Displacement == 0x10u, "V5: the first subobject word is at +0x10");
  check(kReceiverWord14Displacement == 0x14u, "V6: the second subobject word is at +0x14");
  check(kDeletingFlagMask == 0x01u, "V7: the mask of the TEST at 0x00dd0bdc is 0x01");
  check(kStackCleanupBytes == 0x04u, "V8: the terminator at 0x00dd0bef pops four bytes");
  check(kPushedWordCleanupBytes == 0x04u, "V9: 0x00dd0be9 drops four bytes for the port");
  check(sizeof(OpaqueSporepediaAsset) == 0x18u,
        "V10: the modelled receiver ends on the last byte the body writes");
  check(kReceiverWord14Displacement + 4 == sizeof(OpaqueSporepediaAsset),
        "V11: the +0x14 word ends the modelled receiver exactly");
  // The two adjusting thunks the layout argument rests on, restated here so the
  // header's constants are checked rather than trusted. Neither is referenced by
  // the model; both are read out of the image at the addresses below.
  check(kAdjustingThunkForDisplacement10 == 0x00dd0bb0u,
        "V12: 0x00dd0bb0 is the `SUB ECX,0x10; JMP` thunk for the +0x10 subobject");
  check(kAdjustingThunkForDisplacement14 == 0x00dd0b40u,
        "V13: 0x00dd0b40 is the `SUB ECX,0x14; JMP` thunk for the +0x14 subobject");
}

}  // namespace

int main() {
  verify_machine_constants();
  case_flag_set_deallocates();
  case_flag_clear_does_not_deallocate();
  case_the_flag_changes_nothing_else();
  case_repeated_calls_settle();
  case_m1_wrong_constant();
  case_m2_displacements_are_exact();
  case_m3_m4_polarity_and_mask();
  case_m5_port_receives_the_receiver_address();
  case_m6_stores_precede_both_calls();
  case_m7_m8_object_moved_in_place();
  case_m9_returned_word_is_the_receiver();
  case_m10_argument_word_is_callee_cleaned();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
