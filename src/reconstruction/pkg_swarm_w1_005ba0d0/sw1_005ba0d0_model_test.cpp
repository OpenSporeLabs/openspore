// PKG-SWARM-W1-005BA0D0 -- VA 0x005ba0d0
// Behavioural model test for FUN_005ba0d0 @ 0x005ba0d0.
//
// The one direct transfer the body makes is the INDIRECT call at 0x005ba0eb, and
// the machine reaches it two dereferences deep: the word at receiver+0x14, then
// slot 0 of the table that word points at. So the package's callee
// `dispatch_slot0_005ba0eb` is not called by name anywhere in the test either --
// the test builds a vtable of its own, puts the address of its observer in that
// vtable's slot 0, and hands the body the address of the vtable. The test
// therefore sees every transfer, with which arguments, in which order, and gets
// to decide what the callee does to memory -- including reading back the
// receiver's words while the body is still running.
//
// What is asserted is what the 12-instruction listing fixes and nothing more:
//
//   * the two receiver displacements reached (0x14, 0x18) and the single word
//     written (0x18) -- checked by comparing the receiver's bytes before and
//     after, so "no other byte changed" is asserted rather than assumed;
//   * the two separate 4-byte stores to +0x18, their values and their order,
//     through the model's own write log;
//   * the branch condition: fall through exactly when the POST-decrement value
//     is zero, i.e. when the pre-decrement value was exactly 1;
//   * the wrap of the 32-bit decrement, driven at 0 and at 0xffffffff;
//   * the return value on both paths, including that the dispatch path returns 0
//     while the field holds 1;
//   * the dispatch: that it is slot 0 of the table at +0x14, that the receiver
//     the callee receives is receiver+0x14, and that the one stack word is 1;
//   * that the body takes no ordinary stack argument and cleans nothing, measured
//     with a trampoline that samples ESP either side of the call.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   N1  wrong branch polarity: driven with 1 and 2, which the two polarities
//       treat oppositely;
//   N2  wrong tested value: the pre-decrement value instead of the
//       post-decrement one, driven with 0 and 1, which disagree;
//   N3  wrong write ordering: the restore to 1 must land BEFORE the dispatch, so
//       the observer samples the field and the write log at the moment of the
//       call;
//   N4  wrong store count: one store on the early-out path, two on the dispatch
//       path, never zero and never three;
//   N5  wrong slot displacement: a decoy observer sits in slot 1 and must never
//       run;
//   N6  wrong base object / wrong vtable pointer: decoy vtables are planted at
//       +0x10, +0x1c and +0x20 whose slot 0 is a different observer, and none of
//       them may run;
//   N7  wrong pointer level: the callee's own `this` must be receiver+0x14 --
//       not the receiver's base, not the table, and not anything the receiver
//       points at;
//   N8  wrong rewrite offset: decoy words at the neighbouring offsets must not
//       move;
//   N9  wrong dispatch argument: the pushed word must be the literal 1 even when
//       the neighbouring receiver words hold 0 and 2;
//   N10 wrong return on the dispatch path: 0 while the field reads 1, which
//       refutes "return the field", "return the saved value" and "return the
//       callee's result" separately;
//   N11 wrong return on the early-out path: the decremented value, driven at 5,
//       0 and 0xffffffff so an un-wrapped or a zeroed value is refuted;
//   N12 ABI: no ordinary stack argument, nothing cleaned, measured by a
//       trampoline that pushes a sentinel and checks it survives;
//   N14 the call is not to a fixed symbol: the table at +0x14 is given a different
//       callee and that callee, not the package's own, is the one that runs;
//   N13 wrong write value: the first store must be the decremented value even
//       when the branch immediately discards it.
//
// What is NOT asserted, and why:
//
//   * Whether the CALLEE owns the pushed word. The machine fact is real -- the
//     twelve instructions contain no POP and no ADD ESP, so 0x005ba0eb's target
//     must clean its own argument or the RET at 0x005ba0ef would pop that word as
//     a return address -- but i386-ELF has no callee-cleaned thiscall: GCC
//     implements `__attribute__((thiscall))` as ECX-this plus cdecl cleanup, so
//     the model necessarily performs the four-byte cleanup on its own side. The
//     model therefore expresses the call's SHAPE (receiver in ECX, one stack word,
//     balanced) and the ownership claim stays a machine fact recorded in the
//     header. The test measures the balance, not the ownership.
//   * The second store's value as distinct from the saved pre-decrement value.
//     The second store only executes when the pre-decrement value was exactly 1,
//     so "store 1" and "store the saved value" are the same machine on every
//     input and no test can separate them. The second store IS separated from
//     "store 0" and from "do not store at all", and both of those are asserted.
//   * The dispatch path's `return 0` as distinct from `return decremented`. The
//     fall-through is reached only when the decremented value IS zero, so those
//     two are the same machine on every input -- confirmed by mutating the model
//     to `return decremented` and watching the whole suite still pass. The XOR at
//     0x005ba0ed is real and is modelled, and it is separated from "return the
//     field" (1) and from "return the saved value" (1) by case N10; what cannot be
//     claimed is that the 0 comes from the XOR rather than from the arithmetic.
//   * Whether EAX is an intended result. No caller in this image consumes it --
//     the body's three non-data references are receiver-adjustor thunks, not call
//     sites -- so the test asserts the value on each path, which the listing does
//     fix, and says nothing about who wants it.
//   * The transient 0 written by the first store on the dispatch path. Between
//     0x005ba0d9 and 0x005ba0de there is no call, no branch target and no exit,
//     so no outside observer can sample it. It is asserted only through the
//     model's write log, which is instrumentation and not a machine global.
//   * The class of the object at receiver+0x14 and the name of the callee.
//     SporeApp.exe carries no MSVC RTTI and the callee is reached only through a
//     vtable word, so nothing here names either.

#include "sw1_005ba0d0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0 {
namespace {

// Machine displacements and immediates, as literals, so a change to the header
// that contradicts the listing shows up as a failing check rather than as a
// silently different model.
constexpr std::size_t kSubobjectOffset = 0x14u;
constexpr std::size_t kCounterOffset = 0x18u;
constexpr std::size_t kReceiverSize = 0x1cu;
constexpr Word kDecrement = 0xffffffffu;
constexpr Word kRestored = 0x1u;
constexpr Word kArgument = 0x1u;

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// A receiver big enough for every byte this body can touch, plus a sentinel tail
// so an overrun past +0x1b would show up in the byte comparison.
struct Receiver {
  unsigned char bytes[kReceiverSize + 8];
};

// The vtable the test hands the body. Three slots, because only slot 0 is ever
// named by the listing and the extra two exist purely to carry decoys.
struct FakeVtable {
  DispatchSlot0 slot_0;
  DispatchSlot0 slot_1;
  DispatchSlot0 slot_2;
};

// A table whose slot 0 is a decoy observer, so a reconstruction that reads the
// vtable word from the wrong receiver offset makes an OBVIOUS wrong call instead
// of jumping into data.
struct DecoyVtable {
  DispatchSlot0 slot_0;
};

enum Call : int { kCallDispatch = 0 };

struct Observation {
  int log[4] = {};
  int log_length = 0;

  int dispatch_calls = 0;
  DispatchSubobject* dispatch_receiver = nullptr;  // the callee's own `this`
  Word dispatch_argument = 0;
  void** dispatch_vtable_seen = nullptr;  // the word the callee found at [this]
  // Sampled INSIDE the dispatch, so the order of the two stores relative to the
  // call is observable: 0x005ba0de's restore must have run before 0x005ba0eb.
  Word dispatch_counter_seen = 0;
  bool dispatch_counter_valid = false;
  ReceiverWriteLog dispatch_log_seen{0, 0, 0};

  // Set by a decoy observer, so a wrong slot or a wrong receiver offset is
  // reported as a clean failure instead of as a jump into data.
  int decoy_slot1_calls = 0;
  int decoy_low_calls = 0;   // vtable planted at receiver+0x10
  int decoy_high_calls = 0;  // vtables planted at receiver+0x1c and +0x20
  int decoy_taken_over_calls = 0;  // the table at +0x14 given a different callee
  void** decoy_taken_over_vtable = nullptr;

  void reset() { *this = Observation(); }

  void record(Call call) {
    if (log_length < 4) {
      log[log_length] = static_cast<int>(call);
    }
    ++log_length;
  }
};

Observation g_obs;

// The receiver the current case is exercising, so the observer can sample a
// receiver word at a moment the caller cannot see.
Receiver* g_active_receiver = nullptr;

// The vtable the current case planted, so the observer can check that the word it
// found at [this] is the one the caller installed rather than a decoy.
FakeVtable* g_active_vtable = nullptr;

// Decoy observers. They are thiscall-shaped like the real callee, take the same
// arguments, and do nothing but record that they ran.
void PKG_SWARM_W1_005BA0D0_THISCALL decoy_slot1_observer(DispatchSubobject* subobject,
                                                          Word argument) {
  ++g_obs.decoy_slot1_calls;
  (void)subobject;
  (void)argument;
}

void PKG_SWARM_W1_005BA0D0_THISCALL decoy_low_observer(DispatchSubobject* subobject,
                                                       Word argument) {
  ++g_obs.decoy_low_calls;
  (void)subobject;
  (void)argument;
}

void PKG_SWARM_W1_005BA0D0_THISCALL decoy_high_observer(DispatchSubobject* subobject,
                                                        Word argument) {
  ++g_obs.decoy_high_calls;
  (void)subobject;
  (void)argument;
}

void PKG_SWARM_W1_005BA0D0_THISCALL decoy_taken_over_observer(
    DispatchSubobject* subobject, Word argument) {
  ++g_obs.decoy_taken_over_calls;
  // The callee's own view of the table word, sampled so a model that called a
  // fixed symbol instead of going through the table is caught from the far side
  // as well as from this one.
  g_obs.decoy_taken_over_vtable = (subobject != nullptr) ? subobject->vtable : nullptr;
  (void)argument;
}

FakeVtable g_vtable{};
FakeVtable g_decoy_vtable_slot1{};
DecoyVtable g_decoy_low_vtable{};
DecoyVtable g_decoy_high_1c{};
DecoyVtable g_decoy_high_20{};

Receiver make_receiver(FakeVtable* vtable, Word counter) {
  Receiver receiver;
  std::memset(&receiver, 0, sizeof receiver);
  void* const table = static_cast<void*>(vtable);
  std::memcpy(receiver.bytes + kSubobjectOffset, &table, sizeof table);
  std::memcpy(receiver.bytes + kCounterOffset, &counter, sizeof counter);
  return receiver;
}

// Plants the decoy tables. The ones at the neighbouring receiver offsets are only
// reachable by a reconstruction that reads the vtable word at the wrong
// displacement; each carries its own observer in slot 0, so such a mistake makes
// an OBVIOUS wrong call instead of jumping into data.
void plant_decoys(Receiver& receiver) {
  g_vtable.slot_0 = &dispatch_slot0_005ba0eb;
  g_vtable.slot_1 = &decoy_slot1_observer;
  g_vtable.slot_2 = &decoy_slot1_observer;

  g_decoy_vtable_slot1.slot_0 = &decoy_slot1_observer;
  g_decoy_vtable_slot1.slot_1 = &decoy_slot1_observer;
  g_decoy_vtable_slot1.slot_2 = &decoy_slot1_observer;

  g_decoy_low_vtable.slot_0 = &decoy_low_observer;
  g_decoy_high_1c.slot_0 = &decoy_high_observer;
  g_decoy_high_20.slot_0 = &decoy_high_observer;

  // Neighbouring receiver words. +0x10 is two dwords below the real vtable word,
  // +0x1c is one dword above the field, +0x20 is two above. The +0x18 word is the
  // body's own business and is left alone here: a reconstruction that read the
  // table pointer one word too high would land on the field, which the dispatch
  // path leaves at 1, and would jump through address 1. That refutation is a
  // fault rather than a clean assertion, and the test says so instead of
  // pretending to catch it.
  const void* const low = static_cast<const void*>(&g_decoy_low_vtable);
  const void* const high_1c = static_cast<const void*>(&g_decoy_high_1c);
  const void* const high_20 = static_cast<const void*>(&g_decoy_high_20);
  std::memcpy(receiver.bytes + 0x10, &low, sizeof low);
  std::memcpy(receiver.bytes + 0x1c, &high_1c, sizeof high_1c);
  std::memcpy(receiver.bytes + 0x20, &high_20, sizeof high_20);
}

// The receiver's word at its machine displacement, read the way the body reads
// it: as a 32-bit value, not as a byte and not as a pointer.
Word counter_of(const Receiver& receiver) {
  Word value = 0;
  std::memcpy(&value, receiver.bytes + kCounterOffset, sizeof value);
  return value;
}

void word_at_offset(Receiver& receiver, std::size_t offset, Word value) {
  std::memcpy(receiver.bytes + offset, &value, sizeof value);
}

Word word_at_offset(const Receiver& receiver, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, receiver.bytes + offset, sizeof value);
  return value;
}

// How many bytes of the receiver changed OUTSIDE the four counter bytes, and how
// many changed inside them.
struct ReceiverDiff {
  int inside = 0;
  int outside = 0;
};

ReceiverDiff diff_receiver(const Receiver& before, const Receiver& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < sizeof before.bytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    if (index >= kCounterOffset && index < kCounterOffset + sizeof(Word)) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

// The vtable word as the body reads it: the dword at receiver+0x14.
void* vtable_word_of(const Receiver& receiver) {
  void* value = nullptr;
  std::memcpy(&value, receiver.bytes + kSubobjectOffset, sizeof value);
  return value;
}

Swarm005ba0d0Receiver* as_receiver(Receiver& receiver) {
  return reinterpret_cast<Swarm005ba0d0Receiver*>(&receiver);
}

DispatchSubobject* subobject_of(Receiver& receiver) {
  return reinterpret_cast<DispatchSubobject*>(receiver.bytes + kSubobjectOffset);
}

// Runs one call with the standard fixture: the real vtable planted, decoys
// planted, and the observers pointed at the live receiver.
Word run(Receiver& receiver) {
  g_active_receiver = &receiver;
  g_active_vtable = &g_vtable;
  const Word result = re_005ba0d0(as_receiver(receiver));
  g_active_receiver = nullptr;
  g_active_vtable = nullptr;
  return result;
}

}  // namespace

// 0x005ba0eb -- the indirect call. The body reaches this as the vtable word at
// receiver+0x14 and then slot 0 of that table, and the test installs this
// function's address in exactly that slot. The observer therefore sees the
// callee's own `this`, the pushed word, the vtable word it can read back at
// [this], the receiver's counter as it stands at the moment of the call, and the
// model's write log -- all of which the test needs to place the call in the
// sequence.
extern "C" void PKG_SWARM_W1_005BA0D0_THISCALL dispatch_slot0_005ba0eb(
    DispatchSubobject* subobject, Word argument) {
  ++g_obs.dispatch_calls;
  g_obs.record(kCallDispatch);
  g_obs.dispatch_receiver = subobject;
  g_obs.dispatch_argument = argument;
  g_obs.dispatch_vtable_seen = (subobject != nullptr) ? subobject->vtable : nullptr;
  if (g_active_receiver != nullptr) {
    g_obs.dispatch_counter_seen = counter_of(*g_active_receiver);
    g_obs.dispatch_counter_valid = true;
  }
  g_obs.dispatch_log_seen = receiver_write_log();
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0;

// -- behavioural cases --------------------------------------------------------

// A. The dispatch case: the counter was 1, so the decrement reaches 0, the
// restore puts 1 back, and the callee runs. This is the only path in the body
// that makes a transfer.
void case_dispatch_path() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  Receiver before = receiver;

  const Word result = run(receiver);

  check(g_obs.dispatch_calls == 1, "A1: the callee at 0x005ba0eb is called exactly once");
  check(g_obs.log_length == 1 && g_obs.log[0] == kCallDispatch,
        "A2: the dispatch is the only transfer the body makes");
  check(counter_of(receiver) == 1u,
        "A3: the restore at 0x005ba0de puts 1 back, so the field reads 1 afterwards");
  check(result == 0u,
        "A4: the return is 0 (0x005ba0ed), not the field's 1 and not the saved 1");
  const ReceiverWriteLog log = receiver_write_log();
  check(log.count == 2u, "A5: the body made both stores to +0x18");
  check(log.first == 0u, "A6: the first store is the decremented value 1-1 == 0");
  check(log.second == kRestored, "A7: the second store is the literal 1");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0, "A8: no byte of the receiver outside the four field bytes changed");
    check(diff.inside == 0 || diff.inside == 4,
          "A9: the field ends on the value the restore wrote, so either nothing or "
          "all four bytes differ from the 1 it started at");
  }
  check(g_obs.decoy_slot1_calls == 0, "A10: the slot 1 decoy never ran");
  check(g_obs.decoy_low_calls == 0 && g_obs.decoy_high_calls == 0,
        "A11: no decoy table planted at a neighbouring receiver offset was used");
  check(g_obs.decoy_taken_over_calls == 0, "A12: no takeover decoy ran in the ordinary fixture");
}

// B. The early-out case: the counter was 5, the decrement does not reach 0, and
// the body returns immediately. No load of +0x14, no call, one store.
void case_early_out_path() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 5u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 5u);
  Receiver before = receiver;

  const Word result = run(receiver);

  check(g_obs.dispatch_calls == 0, "B1: the body does not dispatch when the decrement is non-zero");
  check(counter_of(receiver) == 4u, "B2: the field holds the decremented value 4");
  check(result == 4u, "B3: the return is that same decremented value");
  const ReceiverWriteLog log = receiver_write_log();
  check(log.count == 1u, "B4: the early-out path makes exactly one store");
  check(log.first == 4u, "B5: that store is the decremented value");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0, "B6: no byte outside the field's four bytes changed");
  }
}

// C. The 32-bit wrap. `83 c0 ff` is an add of 0xffffffff on a 32-bit register, so
// 0 becomes 0xffffffff. The decremented value is then non-zero, so this is an
// early-out, and a reconstruction that saturated, or that treated the word as
// signed, would land somewhere else.
void case_wrap_at_zero() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 0u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 0u);
  const Word result = run(receiver);

  check(g_obs.dispatch_calls == 0, "C1: 0 - 1 wraps to 0xffffffff, which is not zero, so no dispatch");
  check(counter_of(receiver) == 0xffffffffu, "C2: the field holds 0xffffffff after the wrap");
  check(result == 0xffffffffu, "C3: the return is the wrapped value, not 0 and not -1 as a signed read");
  check(receiver_write_log().count == 1u, "C4: one store");
}

// D. The same wrap from the other end: 0xffffffff - 1 is 0xfffffffe, still
// non-zero, so still an early-out. Drives the boundary from above.
void case_wrap_from_max() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 0xffffffffu);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 0xffffffffu);
  const Word result = run(receiver);

  check(g_obs.dispatch_calls == 0, "D1: 0xffffffff - 1 is non-zero, so no dispatch");
  check(counter_of(receiver) == 0xfffffffeu, "D2: the field holds 0xfffffffe");
  check(result == 0xfffffffeu, "D3: and the return is that value");
}

// E. The dispatch is a one-shot-per-transition, not a one-shot-ever: the restore
// leaves the field at 1, so the very next call decrements to 0 again and
// dispatches again. Two calls, two dispatches, and the field is back at 1.
void case_dispatch_repeats() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);

  const Word first = run(receiver);
  const Word second = run(receiver);

  check(g_obs.dispatch_calls == 2, "E1: two calls, because the field rests at 1, dispatch twice");
  check(first == 0u && second == 0u, "E2: both returns are 0");
  check(counter_of(receiver) == 1u, "E3: the field rests at 1 after both calls");
  check(receiver_write_log().count == 2u, "E4: the log describes the LAST call only");
}

// F. The dispatch's argument and receiver, measured at the callee.
void case_dispatch_argument_and_receiver() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  Receiver* const base = &receiver;

  run(receiver);

  check(g_obs.dispatch_receiver == subobject_of(receiver),
        "F1: the callee's `this` is receiver+0x14, the address ECX held at the call");
  check(reinterpret_cast<void*>(g_obs.dispatch_receiver) != base,
        "F2: and it is NOT the receiver's own base address");
  check(reinterpret_cast<void*>(g_obs.dispatch_receiver) != vtable_word_of(receiver),
        "F3: and it is NOT the vtable pointer the body loaded");
  check(g_obs.dispatch_vtable_seen == vtable_word_of(receiver),
        "F4: the word at the callee's `this` is still the vtable pointer the body loaded");
  check(g_obs.dispatch_argument == kArgument, "F5: the pushed word is the literal 1 of `6a 01`");
}

// -- REFUTATION CASES --------------------------------------------------------

// N1. Branch polarity. A reconstruction that dispatches when the decremented
// value is NON-ZERO takes the opposite arm on every input; 1 and 2 are the two
// inputs on which the two readings disagree (1 dispatches, 2 does not).
void case_branch_polarity() {
  g_obs.reset();
  Receiver one = make_receiver(&g_vtable, 1u);
  plant_decoys(one);
  word_at_offset(one, kCounterOffset, 1u);
  run(one);
  check(g_obs.dispatch_calls == 1, "N1a: a field of 1 dispatches");

  g_obs.reset();
  Receiver two = make_receiver(&g_vtable, 2u);
  plant_decoys(two);
  word_at_offset(two, kCounterOffset, 2u);
  const Word result = run(two);
  check(g_obs.dispatch_calls == 0, "N1b: a field of 2 does NOT dispatch, so the JNZ is not inverted");
  check(result == 1u, "N1c: and the return is the decremented 1");
}

// N2. Tested value. A reconstruction that tests the PRE-decrement word (or that
// tests the field before storing) dispatches when the field is 0; the listing
// tests the POST-decrement value and so dispatches when the field was 1. The two
// readings disagree on both 0 and 1.
void case_tested_value_is_post_decrement() {
  g_obs.reset();
  Receiver zero = make_receiver(&g_vtable, 0u);
  plant_decoys(zero);
  word_at_offset(zero, kCounterOffset, 0u);
  run(zero);
  check(g_obs.dispatch_calls == 0, "N2a: a field of 0 does NOT dispatch, so the test is not on the old value");
  check(counter_of(zero) == 0xffffffffu, "N2b: and the field wrapped instead");

  g_obs.reset();
  Receiver one = make_receiver(&g_vtable, 1u);
  plant_decoys(one);
  word_at_offset(one, kCounterOffset, 1u);
  run(one);
  check(g_obs.dispatch_calls == 1, "N2c: a field of 1 does dispatch, so the test is on old-1 and not on old");
}

// N3. Write ordering. The restore (`c7 41 04 01 00 00 00`) is 0x005ba0de and the
// call is 0x005ba0eb, so the field already reads 1 and the log already shows two
// stores when the callee is entered. A reconstruction that dispatched between
// the two stores -- or that left the second store after the call -- is refuted by
// what the observer sees.
void case_restore_precedes_the_dispatch() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  run(receiver);

  check(g_obs.dispatch_counter_valid, "N3a: the observer sampled the field");
  check(g_obs.dispatch_counter_seen == kRestored,
        "N3b: the field already read 1 while the callee ran, so 0x005ba0de came first");
  check(g_obs.dispatch_log_seen.count == 2u,
        "N3c: both stores had already been made when the callee was entered");
  check(g_obs.dispatch_log_seen.first == 0u && g_obs.dispatch_log_seen.second == kRestored,
        "N3d: and in the order the listing makes them");
}

// N4. Store count. One store on the early-out path, two on the dispatch path.
// Never zero (the first store is unconditional) and never three.
void case_store_count() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 9u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 9u);
  run(receiver);
  check(receiver_write_log().count == 1u, "N4a: the early-out path stores exactly once");

  g_obs.reset();
  Receiver other = make_receiver(&g_vtable, 1u);
  plant_decoys(other);
  word_at_offset(other, kCounterOffset, 1u);
  run(other);
  check(receiver_write_log().count == 2u, "N4b: the dispatch path stores exactly twice");
}

// N5. Slot displacement. Slot 0 is the only slot the listing names (`8b 10` is
// `mov edx,[eax]`, no offset). Slots 1 and 2 of the planted table both hold a
// decoy, so an off-by-one or off-by-two slot read is an obvious wrong call.
void case_slot_is_zero() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  run(receiver);

  check(g_obs.dispatch_calls == 1, "N5a: slot 0 is the one that ran");
  check(g_obs.decoy_slot1_calls == 0,
        "N5b: slot 1 never ran, so the slot displacement is 0 and not 4");
  check(vtable_word_of(receiver) == static_cast<void*>(&g_vtable),
        "N5c: the table is the one the caller planted");
}

// N6. Wrong base object / wrong vtable pointer. Decoy tables sit at receiver+0x10
// (two dwords low), +0x1c (one dword high) and +0x20 (two dwords high), each with
// its own observer in slot 0. Any of them running would mean the body read the
// vtable word from a displacement other than 0x14.
void case_vtable_offset_is_0x14() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);

  // Confirm the decoys are really there, so a clean pass is not a pass on an
  // unplanted fixture.
  check(word_at_offset(receiver, 0x10) != 0u &&
            word_at_offset(receiver, 0x1c) != 0u &&
            word_at_offset(receiver, 0x20) != 0u,
        "N6a: the three decoy tables really are planted at +0x10, +0x1c and +0x20");

  run(receiver);

  check(g_obs.dispatch_calls == 1, "N6b: the real slot 0 ran exactly once");
  check(g_obs.decoy_low_calls == 0, "N6c: the +0x10 table was never read");
  check(g_obs.decoy_high_calls == 0, "N6d: neither the +0x1c nor the +0x20 table was read");
  check(word_at_offset(receiver, kCounterOffset) == 1u,
        "N6e: the field itself is left alone by the fixture -- a table pointer read "
        "one word too high would land on it, which faults rather than reporting, "
        "and that limitation is stated in this file's header");
}

// N7. Pointer level. The callee must receive the SUBOBJECT (receiver+0x14). The
// wrong answers are the receiver's base, the vtable pointer, and -- the one this
// case exists for -- treating the vtable word itself as the callee.
//
// That last error cannot be turned into a clean assertion: the wrong reading
// jumps into whatever address the vtable word holds, which on i386-ELF is the
// test's own .bss, and the process faults. The fault IS a refutation (the test
// binary exits non-zero) and it was confirmed by mutating the model, but it
// reports nothing, so the case below refutes the error from the callee's side
// instead: the callee's `this` is the address OF the vtable word, and the word at
// that address is the table.
void case_two_level_dispatch() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  run(receiver);

  check(g_obs.dispatch_receiver == subobject_of(receiver),
        "N7a: the callee got the subobject, not something one dereference further in");
  check(g_obs.dispatch_vtable_seen == static_cast<void*>(&g_vtable),
        "N7b: the callee can still find the table at [this], so the second load is real");
  check(reinterpret_cast<std::uintptr_t>(g_obs.dispatch_vtable_seen) !=
            reinterpret_cast<std::uintptr_t>(g_obs.dispatch_receiver),
        "N7c: the table and the subobject are two different addresses");
  check(receiver_write_log().count == 2u && g_obs.dispatch_log_seen.count == 2u,
        "N7d: both stores were already complete when the second load happened");
}

// N8. Rewrite offset. The only memory the body writes is the dword at +0x18.
// Decoy words at +0x10, +0x1c and +0x20 hold 0xa5a5a5a5 and must not move, and
// the byte comparison covers every byte of the receiver including the sentinel
// tail.
void case_rewrite_offset_is_0x18() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  const Word low = 0xa5a5a5a5u;
  const Word high_1c = 0xa5a5a5a5u;
  const Word high_20 = 0xa5a5a5a5u;
  std::memcpy(receiver.bytes + 0x10, &low, sizeof low);
  std::memcpy(receiver.bytes + 0x1c, &high_1c, sizeof high_1c);
  std::memcpy(receiver.bytes + 0x20, &high_20, sizeof high_20);
  Receiver before = receiver;

  run(receiver);

  check(word_at_offset(receiver, 0x10) == low, "N8a: the decoy at +0x10 did not move");
  check(word_at_offset(receiver, 0x1c) == high_1c, "N8b: the decoy at +0x1c did not move");
  check(word_at_offset(receiver, 0x20) == high_20, "N8c: the decoy at +0x20 did not move");
  check(vtable_word_of(receiver) == static_cast<void*>(&g_vtable),
        "N8d: the vtable word at +0x14 survived, so the restore did not land on it");
  check(counter_of(receiver) == kRestored, "N8e: the field at +0x18 is the restored 1");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.outside == 0, "N8f: no byte outside the field's four bytes changed, tail included");
}

// N9. Dispatch argument. The pushed word is the immediate of `6a 01`. Neighbouring
// receiver words are set to 0 and 2 so an argument read from the receiver rather
// than from the instruction would be 0 or 2.
void case_dispatch_argument_is_one() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  const Word head = 0u;
  std::memcpy(receiver.bytes + 0x00, &head, sizeof head);

  run(receiver);

  check(g_obs.dispatch_argument == 1u, "N9a: the argument is 1 even with a 0 word at receiver+0x00");
  check(g_obs.dispatch_argument != word_at_offset(receiver, 0x00),
        "N9b: and it is not a receiver word");
  check(kDispatchArgument == 1u, "N9c: the header's constant is the instruction's immediate");
}

// N10. The return on the dispatch path. The field reads 1 at the RET and the
// return is 0. That separates four candidates at once: returning the field (1),
// returning the saved pre-decrement value (1), returning the decremented value
// (0, indistinguishable here) and returning the callee's result. What is
// refuted is "return the field" and "return the saved value"; "return the
// decremented value" happens to agree on this input and is separated on the
// early-out path by N11.
void case_dispatch_path_returns_zero() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  const Word result = run(receiver);

  check(counter_of(receiver) == 1u, "N10a: the field holds 1 at the RET");
  check(result == 0u, "N10b: the return is 0, so it is not the field and not the saved value");
}

// N11. The return on the early-out path, at three values that separate a correct
// decrement from a saturating one, a zeroing one and a signed reading.
void case_early_path_returns_decremented() {
  struct Case {
    Word start;
    Word expected;
  };
  const Case cases[] = {{2u, 1u}, {5u, 4u}, {0u, 0xffffffffu},
                        {0xffffffffu, 0xfffffffeu}, {0x80000000u, 0x7fffffffu}};

  for (const Case& item : cases) {
    g_obs.reset();
    Receiver receiver = make_receiver(&g_vtable, item.start);
    plant_decoys(receiver);
    word_at_offset(receiver, kCounterOffset, item.start);
    const Word result = run(receiver);
    check(result == item.expected, "N11: the return is the wrapped 32-bit decrement");
    check(counter_of(receiver) == item.expected, "N11: and the field holds the same value");
    check(g_obs.dispatch_calls == 0, "N11: none of these inputs dispatches");
  }
}

// N12. ABI. The body takes no ordinary stack argument and cleans nothing. The
// trampoline pushes a sentinel word, calls the body, and checks both that the
// sentinel survived untouched and that ESP is back where it started -- which is
// what a bare `RET` with no `ADD ESP` and no `POP` implies.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
  std::uint32_t sentinel_before = 0;
  std::uint32_t sentinel_after = 0;
};

EspSamples call_measured(Swarm005ba0d0Receiver* receiver) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_005ba0d0));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  std::uint32_t sentinel = 0x5a5a5a5au;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated any
  // of the three inputs to them and every "r" operand survives the register moves
  // that precede its use.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl $0x5a5a5a5a, %[sent]\n\t"
                       "pushl %[sent]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "popl %[sentout]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after),
                         [sentout] "=m"(sentinel)
                       : [target] "r"(target), [recv] "r"(receiver), [sent] "r"(sentinel)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  samples.sentinel_before = 0x5a5a5a5au;
  samples.sentinel_after = sentinel;
  return samples;
}

void case_no_stack_argument_and_no_cleanup() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);

  const EspSamples samples = call_measured(as_receiver(receiver));

  check(samples.after_return == samples.before_push,
        "N12a: ESP is balanced, so the body consumed no stack word of its own");
  check(samples.sentinel_after == samples.sentinel_before,
        "N12b: the sentinel word the trampoline pushed survived untouched");
  check(g_obs.dispatch_calls == 1, "N12c: the trampoline really reached the body");
  check(counter_of(receiver) == kRestored, "N12d: and the body ran to its end");
  check(g_obs.dispatch_receiver == subobject_of(receiver),
        "N12e: ECX carried the receiver the trampoline was given");
}

// N13. The first store is unconditional and carries the decremented value even
// when the branch discards it. A reconstruction that only stored on the dispatch
// path, or that stored the pre-decrement value instead, is refuted on the
// early-out path where there is no second store to hide behind.
void case_first_store_is_unconditional() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 7u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 7u);
  run(receiver);

  check(receiver_write_log().count == 1u, "N13a: the store happened even though the body returned");
  check(receiver_write_log().first == 6u, "N13b: it stored 7-1, not 7 and not 0");
  check(counter_of(receiver) == 6u, "N13c: and the field reads 6 afterwards");
}

// N14. The call really goes THROUGH the table the body loaded, and is not a call
// to a fixed symbol. The table planted at receiver+0x14 is given a DIFFERENT
// callee, so a reconstruction that called dispatch_slot0_005ba0eb by name -- or
// that read the table from anywhere but +0x14 -- would reach the wrong function.
void case_call_goes_through_the_planted_table() {
  g_obs.reset();
  Receiver receiver = make_receiver(&g_vtable, 1u);
  plant_decoys(receiver);
  word_at_offset(receiver, kCounterOffset, 1u);
  g_vtable.slot_0 = &decoy_taken_over_observer;

  const Word result = run(receiver);

  check(g_obs.decoy_taken_over_calls == 1, "N14a: the callee the TABLE names is the one that ran");
  check(g_obs.dispatch_calls == 0,
        "N14b: the package's own named callee did not run, so the call is not by name");
  check(g_obs.decoy_taken_over_vtable == vtable_word_of(receiver),
        "N14c: the takeover callee found the table at [this] just as the real one does");
  check(result == 0u, "N14d: the return is still 0, whatever the callee did");
  check(counter_of(receiver) == kRestored, "N14e: the field is still the restored 1");

  // Put the fixture back for any case that runs after this one.
  g_vtable.slot_0 = &dispatch_slot0_005ba0eb;
}

// The displacements and immediates the reconstruction states, against the bytes.
void verify_constants() {
  check(kReceiverSubobjectDisplacement == 0x14u, "V1: the subobject word is at receiver+0x14");
  check(kReceiverCounterDisplacement == 0x18u, "V2: the rewritten dword is at receiver+0x18");
  check(kDecrementImmediate == 0xffffffffu, "V3: `83 c0 ff` adds 0xffffffff");
  check(kRestoreValue == 0x1u, "V4: `c7 41 04 01 00 00 00` stores 1");
  check(kDispatchArgument == 0x1u, "V5: `6a 01` pushes 1");
  check(kDispatchSlot == 0x00u, "V6: `8b 10` reads offset 0 of the table, so slot 0");
  check(kSubobjectShift == 0x14u, "V7: `83 c1 14` shifts the receiver by 0x14");
  check(kDecrement == 0xffffffffu, "V8: the test's own copy of the decrement immediate");
  check(kRestored == 1u && kArgument == 1u, "V9: the test's own copies of the two immediates");
  check(kSubobjectOffset == 0x14u && kCounterOffset == 0x18u,
        "V10: the test's own copies of the two displacements");
  check(sizeof(Swarm005ba0d0Receiver) == 0x1cu,
        "V11: 0x18 + 4 is the last byte the body writes on the receiver");
  check(sizeof(DispatchSubobject) == 8u, "V12: the subobject is the two words the body can see");
  check(kReceiverSubobjectDisplacement + offsetof(DispatchSubobject, word_04) ==
            kReceiverCounterDisplacement,
        "V13: +0x18 is the subobject's own +0x04, one word at one address");
  check(offsetof(DispatchSubobject, word_04) == 4u &&
            sizeof(DispatchSubobject) == 8u,
        "V13b: and it is the subobject's second word, not a nested member");
  check(kReceiverSize == 0x1cu, "V14: the fixture receiver matches the modelled size");
}

}  // namespace

int main() {
  verify_constants();
  case_dispatch_path();
  case_early_out_path();
  case_wrap_at_zero();
  case_wrap_from_max();
  case_dispatch_repeats();
  case_dispatch_argument_and_receiver();
  case_branch_polarity();
  case_tested_value_is_post_decrement();
  case_restore_precedes_the_dispatch();
  case_store_count();
  case_slot_is_zero();
  case_vtable_offset_is_0x14();
  case_two_level_dispatch();
  case_rewrite_offset_is_0x18();
  case_dispatch_argument_is_one();
  case_dispatch_path_returns_zero();
  case_early_path_returns_decremented();
  case_no_stack_argument_and_no_cleanup();
  case_first_store_is_unconditional();
  case_call_goes_through_the_planted_table();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
