// PKG-SWARM-W2-005A2ED0 -- model test for VA 0x005a2ed0
//
// A falsification test, not a walk-through. Its job is to BREAK the
// reconstruction, and every case below exists because a specific wrong reading
// of the twenty-two instructions at 0x005a2ed0..0x005a2f1c survives the
// obvious glance and dies here.
//
// WHAT IS OBSERVED. Both direct/indirect transfers out of the body are defined
// here as observers, so the test sees every transfer the body makes, with
// which argument, in which order, and it decides what each callee does to
// memory:
//
//   * deallocate_00f47380  -- the direct call at 0x005a2f11. Records its
//     argument, samples the receiver's three triple words at the instant of the
//     call, optionally overwrites the receiver, and returns a poison EAX.
//   * three dispatch observers -- installed into slot 0, slot 1 (0x04) and
//     slot 2 of a test-owned table, so the slot displacement is measured rather
//     than assumed, and a fourth installed at the address receiver+0x10 itself
//     so a ONE-LEVEL reading is caught jumping somewhere observable.
//
// WHAT IS ASSERTED, and what is NOT, is listed per case. The blanket statement:
//
//   Asserted: the order and value of all six stores; which slot of which table
//   the indirect call reaches; that the indirect callee's receiver is the
//   POINTEE; that the call happens iff the word at +0x10 is non-null; that the
//   deallocation happens iff bit 0 of the stack flag is set; that the flag is
//   read AFTER the indirect call; that the returned pointer is the receiver
//   rather than a re-read of it; that the deallocation callee's return value is
//   discarded; that no byte of the receiver outside the six store displacements
//   is touched; that the body leaves the stack where it found it.
//
//   NOT asserted, because the listing does not fix it: what the six .rdata
//   addresses ARE (the model's job is to store the exact values, which it does,
//   not to know what they are); what class the object at +0x10 belongs to; the
//   name or signature of 0x00f47380 beyond "one 32-bit word in, nothing
//   observable out"; the meaning of bit 0 of the stack argument; whether the
//   indirect callee reads any stack word, which this body never establishes;
//   and the return type's C++ spelling, which the machine record leaves as the
//   phrase "unclassified_in_EAX" and which the sidecar records as a
//   disagreement rather than resolving.

#include "sw2_005a2ed0_types.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace {

using namespace openspore::reconstruction::pkg_swarm_w2_005a2ed0;

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void check_eq_u32(unsigned long actual, unsigned long expected, const char* what) {
  ++g_checks;
  if (actual != expected) {
    ++g_failures;
    std::printf("FAIL: %s (got 0x%lx, expected 0x%lx)\n", what, actual, expected);
  }
}

void check_eq_ptr(const void* actual, const void* expected, const char* what) {
  ++g_checks;
  if (actual != expected) {
    ++g_failures;
    std::printf("FAIL: %s (got %p, expected %p)\n", what, actual, expected);
  }
}

// ---------------------------------------------------------------------------
// The observed machine state of one call.
// ---------------------------------------------------------------------------

struct Observations {
  unsigned deallocate_calls;
  const void* deallocate_argument;
  unsigned dispatch_calls[4];   // one counter per installed dispatch observer
  const void* dispatch_receiver[4];
  unsigned flag_writes;
  unsigned receiver_word_writes;
  Word receiver_sample[3];      // the triple words, sampled at the deallocate call
  Word dispatch_sample[3];      // the triple words, sampled at the dispatch call
  unsigned dispatch_samples_taken;
};

// What the dispatch observers are allowed to do to the machine when they run.
struct DispatchBehaviour {
  bool overwrite_deleting_flag;
  std::uint8_t flag_value;
  bool overwrite_receiver;
  Word receiver_value;
};

Observations g_seen;
DispatchBehaviour g_dispatch_behaviour;

// The return value of the most recent run. It lives at namespace scope because
// the run helper returns its observations by value and the returned POINTER is a
// separate fact from any of them.
const void* g_last_returned = nullptr;

void reset_observations() {
  std::memset(&g_seen, 0, sizeof(g_seen));
  g_dispatch_behaviour.overwrite_deleting_flag = false;
  g_dispatch_behaviour.flag_value = 0;
  g_dispatch_behaviour.overwrite_receiver = false;
  g_dispatch_behaviour.receiver_value = 0;
}

// The direct callee. Defined HERE and nowhere else: the package's own model
// supplies no body for it, so this is the observer the reconstruction calls.
extern "C" void SWARM_W2_005A2ED0_CDECL deallocate_00f47380(void* pointer) {
  ++g_seen.deallocate_calls;
  g_seen.deallocate_argument = pointer;
  // Sample the receiver's triple words at the instant of the call, so the test
  // can assert that all six stores have already happened by the time the
  // deallocation runs. This is the write-ordering case, and it is the only
  // reason the model bothers to order its stores.
  const std::uint8_t* const self = static_cast<const std::uint8_t*>(pointer);
  if (self != nullptr) {
    g_seen.receiver_sample[0] = *word_at(self, kReceiverWrite00);
    g_seen.receiver_sample[1] = *word_at(self, kReceiverWrite04);
    g_seen.receiver_sample[2] = *word_at(self, kReceiverWrite08);
  }
}

// One dispatch observer body, shared by all four slots. `index` is which counter
// it bumps, so a call that reaches the wrong slot is attributed to the wrong
// counter and the test sees it.
void dispatch_observer(DispatchedObject* self, unsigned index) {
  if (index < 4u) {
    ++g_seen.dispatch_calls[index];
    g_seen.dispatch_receiver[index] = self;
  }
  // Sample the receiver's three triple words at the instant of the indirect
  // call. This is the write-ordering case for the OTHER side of the call: all
  // three stores of the FIRST triple are complete before the dispatch, and none
  // of the second triple's stores has happened yet. A reconstruction that
  // hoisted a second-triple store above the guard, or that deferred a first-triple
  // store below it, is caught here even though the final memory state and the
  // store log can both be made to look right.
  if (g_seen.dispatch_samples_taken == 0u) {
    const std::uint8_t* const self_bytes =
        static_cast<const std::uint8_t*>(receiver_address());
    if (self_bytes != nullptr) {
      g_seen.dispatch_sample[0] = *word_at(self_bytes, kReceiverWrite00);
      g_seen.dispatch_sample[1] = *word_at(self_bytes, kReceiverWrite04);
      g_seen.dispatch_sample[2] = *word_at(self_bytes, kReceiverWrite08);
    }
  }
  ++g_seen.dispatch_samples_taken;
  if (g_dispatch_behaviour.overwrite_deleting_flag) {
    std::uint8_t* const flag = deleting_flag_address();
    if (flag != nullptr) {
      *flag = g_dispatch_behaviour.flag_value;
      ++g_seen.flag_writes;
    }
  }
  if (g_dispatch_behaviour.overwrite_receiver) {
    // A DIFFERENT receiver: the body must not come back and re-read it. This is
    // what makes the "returns the receiver, not the receiver's current first
    // word" claim falsifiable.
    Word* const first = word_at(receiver_address(), kReceiverWrite00);
    if (first != nullptr) {
      *first = g_dispatch_behaviour.receiver_value;
      ++g_seen.receiver_word_writes;
    }
  }
}

// These four are what the reconstruction's own header declares, seen as
// observers. They are installed into a test-owned table so the reconstruction
// calls through the pointer exactly as `ff d2` does -- the model never calls
// these by name.
extern "C" void SWARM_W2_005A2ED0_THISCALL dispatch_slot0(DispatchedObject* self) {
  dispatch_observer(self, 0);
}

extern "C" void SWARM_W2_005A2ED0_THISCALL dispatch_slot1(DispatchedObject* self) {
  dispatch_observer(self, 1);
}

extern "C" void SWARM_W2_005A2ED0_THISCALL dispatch_slot2(DispatchedObject* self) {
  dispatch_observer(self, 2);
}

extern "C" void SWARM_W2_005A2ED0_THISCALL dispatch_other(DispatchedObject* self) {
  dispatch_observer(self, 3);
}

// ---------------------------------------------------------------------------
// The test's own machine layout.
// ---------------------------------------------------------------------------

// A receiver with a guard band on each side, so "no byte outside the six store
// displacements changed" is asserted over a real diff rather than assumed.
struct ReceiverImage {
  static const std::size_t kGuard = 0x20;
  std::vector<std::uint8_t> bytes;

  ReceiverImage() : bytes(kGuard + sizeof(SwarmW2005a2ed0Receiver) + kGuard, 0) {
    reset();
  }

  void reset() {
    // A distinctive fill so a stray write of a wrong value is visible, and the
    // guard bytes are distinct from the body bytes so the diff localises.
    for (std::size_t i = 0; i < bytes.size(); ++i) {
      bytes[i] = static_cast<std::uint8_t>(0xa0u + (i & 0x0fu));
    }
  }

  SwarmW2005a2ed0Receiver* base() {
    return reinterpret_cast<SwarmW2005a2ed0Receiver*>(&bytes[kGuard]);
  }
  const std::uint8_t* raw() const { return &bytes[0]; }
  std::size_t size() const { return bytes.size(); }
};

// A pointee laid out at the DEPTH the machine reads it at, which is the whole
// point of this file:
//
//   receiver+0x10  ->  a POINTER to this object          (8b 4e 10)
//   pointee+0x00   ->  a POINTER to this table          (8b 01, no displacement)
//   table+0x04     ->  the callee                       (8b 50 04)
//
// so the three levels are three separate objects and the model has to walk two
// of them to reach a function. Collapsing the pointee and the table into one
// array is the one-level misreading this layout exists to prevent.
//
// The table's BASE is published as a member of its own, because that is what has
// to land in the pointee's dispatch word. This was the first draft's own
// one-level bug, twice: it stored `table[0]` in one revision and `sizeof(table)`
// bytes of the table's contents in the next, and in both the model's second load
// produced a function pointer where the machine produces a table pointer, so the
// call went to a wild address and the test died rather than failing. The
// `table_base` member is what the memcpy below copies FROM, which is the only
// form of that expression that stores the address.
//
// The guard band after the object keeps a reading that walks off the end a
// visible diff rather than a silent success.
struct PointeeImage {
  std::vector<std::uint8_t> object;  // the pointee; its +0x00 holds table_base
  void* table[4];
  void* table_base;                   // == table, decayed: the model's slot base

  PointeeImage() : object(0x10 + 0x20, 0), table_base(nullptr) {
    table[0] = reinterpret_cast<void*>(&dispatch_slot0);
    table[1] = reinterpret_cast<void*>(&dispatch_slot1);
    table[2] = reinterpret_cast<void*>(&dispatch_slot2);
    table[3] = reinterpret_cast<void*>(&dispatch_other);
    table_base = table;
    std::memcpy(&object[0], &table_base, sizeof(void*));
  }
  DispatchedObject* base() { return reinterpret_cast<DispatchedObject*>(&object[0]); }
  void replant() { std::memcpy(&object[0], &table_base, sizeof(void*)); }
};

PointeeImage g_pointee;

// Run the body once with a fresh image, and report what was observed.
Observations run_body(ReceiverImage& image, std::uint8_t flag, void* word10,
                      const DispatchBehaviour& behaviour) {
  reset_observations();
  g_dispatch_behaviour = behaviour;
  SwarmW2005a2ed0Receiver* const receiver = image.base();
  // The pointee's own +0x00 is re-planted on every run, so a body that scribbled
  // on it cannot make a later case pass for the wrong reason.
  g_pointee.replant();

  *word_at(receiver, kReceiverRead10) = reinterpret_cast<Word>(word10);
  const Word before00 = *word_at(receiver, kReceiverWrite00);
  const Word before04 = *word_at(receiver, kReceiverWrite04);
  const Word before08 = *word_at(receiver, kReceiverWrite08);
  (void)before00;
  (void)before04;
  (void)before08;

  SwarmW2005a2ed0Receiver* const returned = re_005a2ed0(receiver, flag);
  g_last_returned = returned;
  return g_seen;
}

// Byte diff of the receiver image, guards included.
//
// `planted` is the 32-bit value the test itself wrote into the +0x10 word before
// the call. The body only READS that word, so it must still hold exactly what
// the test put there -- which is itself an assertion, and a cheaper one than
// watching for the write. Everything else outside the three triple words must
// still carry the fill pattern, guard bands included, so a store at a wrong
// displacement or a store one byte wide shows up as a diff.
void expect_only_stores_changed(const ReceiverImage& image, Word planted, const char* what) {
  ReceiverImage pristine;
  std::vector<std::uint8_t> expected = pristine.bytes;
  const std::size_t guard = ReceiverImage::kGuard;

  // The three triple words end holding the second triple's values, whichever
  // order the stores were made in.
  const std::size_t offsets[3] = {kReceiverWrite00, kReceiverWrite04, kReceiverWrite08};
  const Word finals[3] = {kSecondTripleHeadAt00, kSecondTripleHeadAt04, kSecondTripleHeadAt08};
  for (std::size_t slot = 0; slot < 3u; ++slot) {
    const std::size_t at = guard + offsets[slot];
    for (std::size_t byte = 0; byte < sizeof(Word); ++byte) {
      expected[at + byte] = static_cast<std::uint8_t>((finals[slot] >> (8u * byte)) & 0xffu);
    }
  }
  // The +0x10 word is the test's own, and the body must not have touched it.
  for (std::size_t byte = 0; byte < sizeof(Word); ++byte) {
    expected[guard + kReceiverRead10 + byte] =
        static_cast<std::uint8_t>((planted >> (8u * byte)) & 0xffu);
  }
  check(image.bytes == expected, what);
}

// ---------------------------------------------------------------------------
// Cases
// ---------------------------------------------------------------------------

// Case A: the store sequence. Count, displacements, values and -- the part that
// only a log can see -- the ORDER, including the second triple's descending
// displacement.
void case_a_store_sequence() {
  ReceiverImage image;
  run_body(image, 0x00, nullptr, DispatchBehaviour());
  const ReceiverStoreLog log = receiver_store_log();
  check_eq_u32(log.count, 6u, "A: the body makes exactly six stores on every path");
  const std::size_t want_disp[6] = {0x00, 0x04, 0x08, 0x08, 0x04, 0x00};
  const Word want_value[6] = {kFirstTripleHeadAt00, kFirstTripleHeadAt04, kFirstTripleHeadAt08,
                              kSecondTripleHeadAt08, kSecondTripleHeadAt04, kSecondTripleHeadAt00};
  for (int i = 0; i < 6; ++i) {
    check_eq_u32(log.displacement[i], want_disp[i], "A: store displacement, in order");
    check_eq_u32(log.value[i], want_value[i], "A: stored value, in order");
  }
  // A body that wrote the second triple in ASCENDING order would leave the same
  // final memory and the same count; only the order separates them. Stated
  // explicitly so the case is not mistaken for the final-state check.
  check(log.displacement[3] != log.displacement[5],
        "A: the second triple is stored high-to-low, not low-to-high");
}

// Case B: the final state of the receiver, and that only the three triple words
// differ from the fill -- guards included, so an out-of-range store is caught.
void case_b_final_state_and_byte_diff() {
  ReceiverImage image;
  run_body(image, 0x01, nullptr, DispatchBehaviour());
  SwarmW2005a2ed0Receiver* const receiver = image.base();
  check_eq_u32(*word_at(receiver, kReceiverWrite00), kSecondTripleHeadAt00,
               "B: +0x00 holds the second triple's head");
  check_eq_u32(*word_at(receiver, kReceiverWrite04), kSecondTripleHeadAt04,
               "B: +0x04 holds the second triple's head");
  check_eq_u32(*word_at(receiver, kReceiverWrite08), kSecondTripleHeadAt08,
               "B: +0x08 holds the second triple's head");
  expect_only_stores_changed(image, 0u, "B: only the three triple words differ from the fill");
}

// Case C: the guard condition. A null word at +0x10 skips the call and NOTHING
// else -- the three stores below the branch still happen.
void case_c_null_guard() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x01, nullptr, DispatchBehaviour());
  check_eq_u32(seen.dispatch_calls[0] + seen.dispatch_calls[1] + seen.dispatch_calls[2] +
                   seen.dispatch_calls[3],
               0u, "C: a null word at +0x10 makes no dispatch call");
  check_eq_u32(receiver_store_log().count, 6u,
               "C: a null word at +0x10 does not skip any store");
  check_eq_ptr(last_dispatched_pointee(), nullptr, "C: the loaded word was null");
}

// Case D: the slot displacement is 0x04, i.e. dword index 1. Slots 0 and 2 of
// the same table hold different observers, so reading slot 0 or slot 2 is a
// different, observable call.
void case_d_slot_displacement() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x00, g_pointee.base(), DispatchBehaviour());
  check_eq_u32(seen.dispatch_calls[1], 1u, "D: exactly one call reaches slot 0x04");
  check_eq_u32(seen.dispatch_calls[0], 0u, "D: slot 0 is not the one called");
  check_eq_u32(seen.dispatch_calls[2], 0u, "D: slot 2 is not the one called");
  check_eq_u32(seen.dispatch_calls[3], 0u, "D: slot 3 is not the one called");
  check_eq_u32(dispatch_call_count(), 1u, "D: the body counts exactly one dispatch");
}

// Case E: TWO-LEVEL dereference. The body's indirect callee must be the table
// at the pointee's own +0x00, reached through the word at receiver+0x10.
//
// The decoy is a table installed at the ADDRESS receiver+0x10 itself, with a
// distinct observer in its slot 0x04. A one-level reading -- treating the word
// at +0x10 as a dispatch word and calling its slot -- reaches that decoy, and
// the test sees the wrong counter move.
void case_e_two_level_dereference() {
  ReceiverImage image;
  // A decoy table at the address of the receiver's +0x10 word.
  static void* decoy_table[4];
  decoy_table[0] = reinterpret_cast<void*>(&dispatch_slot0);
  decoy_table[1] = reinterpret_cast<void*>(&dispatch_other);
  decoy_table[2] = reinterpret_cast<void*>(&dispatch_slot2);
  decoy_table[3] = reinterpret_cast<void*>(&dispatch_slot0);

  const Observations seen =
      run_body(image, 0x00, g_pointee.base(), DispatchBehaviour());
  check_eq_u32(seen.dispatch_calls[1], 1u, "E: the two-level call reaches the pointee's table");
  check_eq_u32(seen.dispatch_calls[3], 0u,
               "E: a one-level reading would have called the decoy at +0x10's address");
  (void)decoy_table;
}

// Case F: the indirect callee's RECEIVER is the pointee -- not receiver+0x10,
// not the receiver base. Each wrong candidate is a different pointer the test can
// name, and the observer records exactly what it was handed.
void case_f_dispatch_receiver_is_the_pointee() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x00, g_pointee.base(), DispatchBehaviour());
  check_eq_ptr(seen.dispatch_receiver[1], g_pointee.base(),
               "F: the indirect callee's receiver is the POINTEE");
  SwarmW2005a2ed0Receiver* const receiver = image.base();
  check(seen.dispatch_receiver[1] != receiver,
        "F: the indirect callee's receiver is not the receiver base");
  check(seen.dispatch_receiver[1] !=
            reinterpret_cast<void*>(word_at(receiver, kReceiverRead10)),
        "F: the indirect callee's receiver is not the address of the +0x10 word");
  check_eq_ptr(last_dispatched_pointee(), g_pointee.base(),
               "F: the body reports the pointee it dispatched through");
}

// Case G: the deleting flag is BIT 0, not "non-zero". Driven with 0x00, 0x01,
// 0x02, 0x03, 0x80 and 0xff: a test of `flag != 0` and a test of bit 1 both
// disagree with the real one somewhere in that set.
void case_g_flag_is_bit_zero() {
  struct Case {
    std::uint8_t flag;
    bool deleting;
    const char* what;
  };
  const Case cases[] = {
      {0x00, false, "G: flag 0x00 does not deallocate"},
      {0x01, true, "G: flag 0x01 deallocates"},
      {0x02, false, "G: flag 0x02 does NOT deallocate (bit 1 is not the mask)"},
      {0x03, true, "G: flag 0x03 deallocates"},
      {0x80, false, "G: flag 0x80 does not deallocate"},
      {0xff, true, "G: flag 0xff deallocates"},
  };
  for (const Case& entry : cases) {
    ReceiverImage image;
    const Observations seen = run_body(image, entry.flag, nullptr, DispatchBehaviour());
    check_eq_u32(seen.deallocate_calls, entry.deleting ? 1u : 0u, entry.what);
  }
}

// Case H: the deallocation's ARGUMENT is the receiver, pushed immediately before
// the call.
void case_h_deallocate_argument() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x01, nullptr, DispatchBehaviour());
  check_eq_ptr(seen.deallocate_argument, image.base(),
               "H: the deallocation callee receives the receiver");
  check_eq_u32(seen.deallocate_calls, 1u, "H: the deallocation callee is called once");
}

// Case I: WRITE ORDERING against the deallocation. All six stores are complete
// before the direct call, so the callee samples the second triple and not the
// first. A reconstruction that issued the call before the second triple would
// be caught here even though the final memory state is identical.
void case_i_stores_precede_the_deallocation() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x01, nullptr, DispatchBehaviour());
  check_eq_u32(seen.receiver_sample[0], kSecondTripleHeadAt00,
               "I: +0x00 already holds the second triple when the callee runs");
  check_eq_u32(seen.receiver_sample[1], kSecondTripleHeadAt04,
               "I: +0x04 already holds the second triple when the callee runs");
  check_eq_u32(seen.receiver_sample[2], kSecondTripleHeadAt08,
               "I: +0x08 already holds the second triple when the callee runs");
}

// Case J: the flag is read AFTER the indirect call, not before. The dispatch
// observer overwrites the flag byte from inside the call; if the body had
// sampled it earlier it would act on the value the CALLER passed, and if it
// sampled it after the `je` it would act on the same value anyway. Driving the
// flag 0x00 and having the callee set it to 0x01 therefore separates "read at
// 0x005a2ef5" from both alternatives at once.
void case_j_flag_is_read_after_the_call() {
  ReceiverImage image;
  DispatchBehaviour behaviour;
  behaviour.overwrite_deleting_flag = true;
  behaviour.flag_value = 0x01;
  const Observations seen = run_body(image, 0x00, g_pointee.base(), behaviour);
  check_eq_u32(seen.flag_writes, 1u, "J: the dispatch observer wrote the flag byte once");
  check_eq_u32(seen.deallocate_calls, 1u,
               "J: the body acts on the flag value the callee wrote, not the caller's");

  ReceiverImage image2;
  const Observations seen2 = run_body(image2, 0x01, g_pointee.base(), behaviour);
  check_eq_u32(seen2.deallocate_calls, 1u, "J: the converse direction also deallocates");

  // And the flag is read BEFORE the second triple's stores are made: the stores
  // cannot change it (they are plain MOVs of immediates into memory), so this
  // case cannot separate that ordering, and it is NOT claimed. Stated so the
  // omission is deliberate rather than an oversight.
}

// Case K: the returned pointer is the receiver, not a re-read of the receiver's
// memory. The dispatch observer overwrites the receiver's first word; the body
// must still return the pointer it was entered with.
void case_k_return_is_the_entered_receiver() {
  ReceiverImage image;
  DispatchBehaviour behaviour;
  behaviour.overwrite_receiver = true;
  behaviour.receiver_value = 0xdeadbeefu;
  run_body(image, 0x00, g_pointee.base(), behaviour);
  check_eq_u32(g_seen.receiver_word_writes, 1u, "K: the dispatch observer wrote the receiver");
  check_eq_ptr(g_last_returned, image.base(),
               "K: the body returns the receiver it was entered with");

  // The same on the deallocating path, where the deallocation observer may have
  // done anything at all to memory.
  ReceiverImage image2;
  run_body(image2, 0x01, g_pointee.base(), DispatchBehaviour());
  check_eq_ptr(g_last_returned, image2.base(),
               "K: the deallocating path returns the same pointer");
}

// Case L: the deallocation callee's return value is discarded. The model
// cannot observe EAX directly, so this case asserts the consequence instead: the
// body returns the receiver on the deallocating path even when the callee is
// given every chance to leave something else there. The header's `void`
// declaration for the callee is what encodes the observation; this case is the
// behavioural half.
void case_l_callee_return_value_is_discarded() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x01, nullptr, DispatchBehaviour());
  check_eq_u32(seen.deallocate_calls, 1u, "L: the deallocation ran");
  check_eq_ptr(g_last_returned, image.base(),
               "L: the returned pointer is the receiver, not the callee's result");
}

// Case M: the indirect call and the deallocation are INDEPENDENT. All four
// combinations of (word at +0x10 null?, bit 0 of the flag set?) are driven, and
// the pair of counts is fixed in each. A body that nested one guard inside the
// other, or that short-circuited, disagrees with one of the four.
void case_m_guards_are_independent() {
  struct Case {
    bool null_word;
    std::uint8_t flag;
    bool dispatch;
    bool deallocate;
  };
  const Case cases[] = {
      {true, 0x00, false, false},  {true, 0x01, false, true},
      {false, 0x00, true, false},  {false, 0x01, true, true},
  };
  for (const Case& entry : cases) {
    ReceiverImage image;
    void* const word10 = entry.null_word ? nullptr : g_pointee.base();
    const Observations seen = run_body(image, entry.flag, word10, DispatchBehaviour());
    const unsigned dispatched = seen.dispatch_calls[0] + seen.dispatch_calls[1] +
                                seen.dispatch_calls[2] + seen.dispatch_calls[3];
    check_eq_u32(dispatched, entry.dispatch ? 1u : 0u,
                 "M: the dispatch guard follows the word at +0x10 alone");
    check_eq_u32(seen.deallocate_calls, entry.deallocate ? 1u : 0u,
                 "M: the deallocation guard follows bit 0 of the flag alone");
    check_eq_u32(receiver_store_log().count, 6u,
                 "M: the six stores happen on all four paths");
  }
}

// Case N: the six immediates, against the encodings. A transcription slip in
// any one of the six values is caught here even where the store order or the
// dispatch is not exercised.
void case_n_immediates() {
  check_eq_u32(kFirstTripleHeadAt00, 0x013f69c8u, "N: first triple, +0x00");
  check_eq_u32(kFirstTripleHeadAt04, 0x013f69b8u, "N: first triple, +0x04");
  check_eq_u32(kFirstTripleHeadAt08, 0x013f69b4u, "N: first triple, +0x08");
  check_eq_u32(kSecondTripleHeadAt08, 0x013ef094u, "N: second triple, +0x08");
  check_eq_u32(kSecondTripleHeadAt04, 0x013eb394u, "N: second triple, +0x04");
  check_eq_u32(kSecondTripleHeadAt00, 0x013eb938u, "N: second triple, +0x00");
  check_eq_u32(kDispatchSlotDisplacement, 0x04u, "N: the slot displacement is 0x04");
  check_eq_u32(kDeletingFlagMask, 0x01u, "N: the flag mask is one bit");
  check_eq_u32(kReceiverRead10, 0x10u, "N: the read displacement is +0x10");
  // The six are pairwise distinct, which is what makes "a second, different
  // triple" a machine fact rather than a description.
  const Word six[6] = {kFirstTripleHeadAt00, kFirstTripleHeadAt04, kFirstTripleHeadAt08,
                       kSecondTripleHeadAt08, kSecondTripleHeadAt04, kSecondTripleHeadAt00};
  for (int i = 0; i < 6; ++i) {
    for (int j = i + 1; j < 6; ++j) {
      check(six[i] != six[j], "N: the six immediates are pairwise distinct");
    }
  }
}

// Case O: the header's displacement constants against the encodings, including
// the frame arithmetic the stack read depends on. A model that read the flag at
// entry_ESP+0x8 instead of entry_ESP+0x4 (i.e. forgot the outstanding push)
// passes every other case and dies here.
void case_o_displacements_and_frame() {
  check_eq_u32(kReceiverWrite00, 0x00u, "O: +0x00 is a store displacement");
  check_eq_u32(kReceiverWrite04, 0x04u, "O: +0x04 is a store displacement");
  check_eq_u32(kReceiverWrite08, 0x08u, "O: +0x08 is a store displacement");
  // One word outstanding (the prologue's `push esi`), so the flag is at
  // entry_ESP+0x4 and the displacement from the CURRENT esp is 0x8.
  check_eq_u32(kDeletingFlagStackDisplacement, 0x08u,
               "O: the flag is read at [esp+0x8] with one word outstanding");
  check_eq_u32(kDeletingFlagStackDisplacement - 4u, 0x04u,
               "O: which is entry_ESP+0x4, the slot `ret 0x4` pops");
  // The slot displacement is a byte displacement, so it is dword index 1 -- not
  // index 0 and not index 2.
  check_eq_u32(kDispatchSlotDisplacement / sizeof(void*), 1u,
               "O: byte displacement 0x04 is dword index 1");
}

// Case P: write ordering on the OTHER side of the indirect call. At the instant
// the dispatch runs, all three stores of the FIRST triple are complete and none
// of the second triple's has happened. The final memory state and the store log
// can both be made to agree with a body that gets this wrong, which is why it is
// asserted from inside the callee rather than after the call.
void case_p_first_triple_is_visible_at_the_dispatch() {
  ReceiverImage image;
  const Observations seen = run_body(image, 0x00, g_pointee.base(), DispatchBehaviour());
  check_eq_u32(seen.dispatch_samples_taken, 1u, "P: the dispatch observer ran once");
  check_eq_u32(seen.dispatch_sample[0], kFirstTripleHeadAt00,
               "P: +0x00 already holds the FIRST triple when the dispatch runs");
  check_eq_u32(seen.dispatch_sample[1], kFirstTripleHeadAt04,
               "P: +0x04 already holds the FIRST triple when the dispatch runs");
  check_eq_u32(seen.dispatch_sample[2], kFirstTripleHeadAt08,
               "P: +0x08 already holds the FIRST triple when the dispatch runs");

  // And the second triple must NOT be there yet, which is the same fact read
  // from the other side: the two triples share all three displacements, so if
  // the first triple were not in place some of these bytes would carry the
  // second triple's values instead. Each is asserted separately because a
  // reconstruction that stored only two of the three first-triple words would
  // satisfy the other two checks alone.
  check(seen.dispatch_sample[0] != kSecondTripleHeadAt00,
        "P: the SECOND triple is not installed when the dispatch runs");
  check(seen.dispatch_sample[1] != kSecondTripleHeadAt04,
        "P: the SECOND triple is not installed when the dispatch runs");
  check(seen.dispatch_sample[2] != kSecondTripleHeadAt08,
        "P: the SECOND triple is not installed when the dispatch runs");
}

}  // namespace

int main() {
  case_a_store_sequence();
  case_b_final_state_and_byte_diff();
  case_c_null_guard();
  case_d_slot_displacement();
  case_e_two_level_dereference();
  case_f_dispatch_receiver_is_the_pointee();
  case_g_flag_is_bit_zero();
  case_h_deallocate_argument();
  case_i_stores_precede_the_deallocation();
  case_j_flag_is_read_after_the_call();
  case_k_return_is_the_entered_receiver();
  case_l_callee_return_value_is_discarded();
  case_m_guards_are_independent();
  case_n_immediates();
  case_o_displacements_and_frame();
  case_p_first_triple_is_visible_at_the_dispatch();

  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
