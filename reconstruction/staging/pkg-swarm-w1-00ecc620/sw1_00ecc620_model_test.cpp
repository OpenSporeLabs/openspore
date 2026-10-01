// PKG-SWARM-W1-00ECC620 -- VA 0x00ecc620
// Behavioural model test for the vector deleting destructor at 0x00ecc620.
//
// Both direct callees -- 0x00642190 and 0x00f47380 -- are defined here as
// observers, so the test sees every transfer the reconstruction makes, with which
// arguments, in which order, and gets to decide what each of them does to memory.
//
// What is asserted is what the 26-instruction listing fixes and nothing more:
//
//   * the two calls to 0x00f47380, and which address each one is handed;
//   * the one call to 0x00642190, with the receiver in ECX, on BOTH arms of the
//     span guard;
//   * the order of all three: span free, then base destructor, then self free;
//   * the three dispatch words written, their exact 32-bit values, and their
//     displacements (0x00, 0x10, 0x14);
//   * that the three stores are visible to the base-destructor observer, i.e. that
//     they precede it;
//   * the two span words read (+0x80 and +0x88), and that the word at +0x84 --
//     which the constructor does write and a sibling function does read -- is not;
//   * the span predicate itself, walked across its boundary and against the
//     signed reading of `CMP ECX,0x2` / `JLE`;
//   * the two guards being independent: a null begin is skipped even when the span
//     is wide, and a narrow span is skipped even when the begin is non-null;
//   * the flag test: one BYTE of entry+4, mask 0x01, so bits 1..7 are ignored;
//   * that the return value is the receiver on every path;
//   * that no byte of the receiver outside the three dispatch words changes, so
//     "this body writes nothing else" is asserted rather than assumed;
//   * the ABI: the argument word is popped by the CALLEE, measured by sampling ESP
//     inside a trampoline rather than asserted as a convention.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   H  the `JLE` at 0x00ecc64b is SIGNED: distances whose masked value has bit 31
//      set are negative, and a model that read it as unsigned would deallocate
//      them;
//   I  the boundary is 4, not 3 and not 1: the mask makes 3 indistinguishable from
//      2, and a model that compared against 0, 1 or 2 gets the 3 case wrong;
//   J  the span is a BYTE distance and is never divided by an element size: a model
//      that divided by 4 would reject a distance of 4;
//   K  the pair read is (+0x80, +0x88) and not (+0x80, +0x84): the constructor
//      writes all three words and a sibling at 0x00ecc530 reads the middle one, so
//      a decoy at +0x84 must stay inert;
//   L  the second 0x00f47380 call is handed the RECEIVER, not the word stored at
//      receiver+0x00: the observer poisons that word, and the argument must not
//      change;
//   M  the flag mask is 0x01 over ONE BYTE: 0x02 must not free and 0x03 must;
//   N  the three dispatch words are three distinct values at three distinct
//      displacements: neighbour decoys at +0x04, +0x08, +0x0c, +0x18 must not move;
//   O  the span free precedes the base destructor, and the self free follows it: a
//      model that hoisted either call is caught by the observers' sampling;
//   P  a null begin must not be deallocated even when the span test passes.
//
// What is NOT asserted, and why:
//
//   * What 0x00642190 does to the receiver. The observer writes a poison word to
//     receiver+0x00 in one case and nothing in the others; nothing in this body's
//     listing reads the receiver after that call, so the reconstruction asserts no
//     dependency on what it left, and the byte-diff cases run with the poison
//     switch off. The dependency the test DOES assert is the opposite direction:
//     that the self-free argument does not follow whatever the callee wrote.
//   * The meaning of the three constants. They are data addresses in the image and
//     this package names none of them; the test asserts the exact 32-bit values
//     because the instructions fix them, and asserts nothing about the words they
//     point at.
//   * Whether the span words are a range, a list of pointers, a string or anything
//     else. The body subtracts them; the reconstruction subtracts them; the test
//     drives the boundary of the arithmetic and does not claim what the words
//     are for.
//   * The two `ADD ESP,0x4` around the 0x00f47380 calls. For a leaf callee that
//     does not touch the caller's stack, callee-pops and caller-pops return are
//     the same machine behaviour, and a black-box observer cannot tell them
//     apart. The convention is fixed by the callee's own bare `C3` at 0x00f47394,
//     which is real evidence, but it is not evidence this test can exercise. The
//     `RET 0x4`, which DOES move the caller's ESP across the return, is measured.
//   * EAX at any point other than the return. EAX is dead between 0x00ecc637 and
//     0x00ecc671 on both arms; the declared return type is fixed by 0x00ecc671
//     alone and that is the only EAX the test looks at.

#include "sw1_00ecc620_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00ecc620 {
namespace {

// Machine displacements, as literals: the five this body reaches.
constexpr std::size_t kWord00Offset = 0x00u;
constexpr std::size_t kWord10Offset = 0x10u;
constexpr std::size_t kWord14Offset = 0x14u;
constexpr std::size_t kSpanBeginOffset = 0x80u;
constexpr std::size_t kSpanEndOffset = 0x88u;
constexpr std::size_t kReceiverSize = 0x8cu;

enum Call : int {
  kCallFree = 0,
  kCallBaseDestroy = 1,
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

struct Observation {
  int log[8] = {};
  int log_length = 0;

  int free_calls = 0;
  Word free_argument[4] = {};
  // The receiver's three dispatch words as the free observer found them at the
  // moment of the call: proves the stores precede the first 0x00f47380 call.
  Word free_seen_at_00 = 0;
  Word free_seen_at_10 = 0;
  Word free_seen_at_14 = 0;
  Word free_seen_at_80 = 0;
  Word free_seen_at_84 = 0;
  Word free_seen_at_88 = 0;
  // When set, the observer poisons the receiver's +0x00 word. Lets the test drive
  // the "the self free is handed the RECEIVER, not the stored word" case.
  bool free_poison_vptr = false;
  Word free_poison_vptr_value = 0;

  int destroy_calls = 0;
  OpaqueSporepediaAssetData* destroy_receiver = nullptr;
  // Sampled INSIDE the base-destructor call, so the position of the three stores
  // and of the span free in the sequence is observable rather than assumed.
  Word destroy_seen_at_00 = 0;
  Word destroy_seen_at_10 = 0;
  Word destroy_seen_at_14 = 0;
  Word destroy_seen_at_80 = 0;
  Word destroy_seen_at_88 = 0;
  bool destroy_saw_span_free = false;
  // When set, the observer rewrites receiver+0x00 -- the word the model's own
  // first store just put there -- so the self-free argument can be checked against
  // a receiver whose stored word has moved.
  bool destroy_poison_vptr = false;
  Word destroy_poison_vptr_value = 0;

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
  bool log_is(Call a, Call b, Call c) const {
    return log_length == 3 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b) &&
           log[2] == static_cast<int>(c);
  }
};

Observation g_obs;

// A receiver large enough for every word this body touches, plus a sentinel tail
// so an overrun past 0x8b would show up in the byte comparison.
struct Receiver {
  unsigned char bytes[kReceiverSize + 8];
};

// The receiver the current case is exercising, so an observer can sample a
// receiver byte at a moment the caller cannot see.
Receiver* g_active_receiver = nullptr;

// A span pair plus a non-null middle word, laid out at the constructor's three
// displacements. `middle` is the word at +0x84, which this body never reads and
// the test uses as a decoy.
struct Span {
  Word begin;
  Word middle;
  Word end;
};

Receiver make_receiver(const Span& span) {
  Receiver receiver;
  std::memset(&receiver, 0, sizeof receiver);
  std::memcpy(receiver.bytes + kWord00Offset, "\x11\x22\x33\x44", 4);
  std::memcpy(receiver.bytes + kWord10Offset, "\x55\x66\x77\x88", 4);
  std::memcpy(receiver.bytes + kWord14Offset, "\x99\xaa\xbb\xcc", 4);
  std::memcpy(receiver.bytes + kSpanBeginOffset, &span.begin, sizeof span.begin);
  std::memcpy(receiver.bytes + kSpanBeginOffset + 4, &span.middle, sizeof span.middle);
  std::memcpy(receiver.bytes + kSpanEndOffset, &span.end, sizeof span.end);
  return receiver;
}

// A span whose end is `begin + distance` in wrapped 32-bit arithmetic, and whose
// middle word carries a decoy value.
Span make_span(Word begin, Word distance, Word middle) {
  Span span;
  span.begin = begin;
  span.middle = middle;
  span.end = begin + distance;
  return span;
}

Word word_of(const Receiver& receiver, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, receiver.bytes + offset, sizeof value);
  return value;
}

OpaqueSporepediaAssetData* as_asset(Receiver& receiver) {
  return reinterpret_cast<OpaqueSporepediaAssetData*>(&receiver);
}

// How many bytes of the receiver changed at each of the three dispatch words, and
// how many changed anywhere else. The body writes exactly those three words and
// nothing else, so every changed byte has to fall inside one of them.
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
    const bool in00 = index >= kWord00Offset && index < kWord00Offset + 4;
    const bool in10 = index >= kWord10Offset && index < kWord10Offset + 4;
    const bool in14 = index >= kWord14Offset && index < kWord14Offset + 4;
    if (in00 || in10 || in14) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

}  // namespace

// 0x00ecc652 and 0x00ecc669 -- the deallocation port. cdecl, one stack word. The
// observer records the address it was handed and samples the receiver's dispatch
// words and span words as they stand at that instant, which is what makes the
// ordering of the five stores and two guard tests observable.
extern "C" void PKG_SWARM_W1_00ECC620_CDECL sporepedia_free_00f47380(Word address) {
  ++g_obs.free_calls;
  g_obs.record(kCallFree);
  if (g_obs.free_calls <= 4) {
    g_obs.free_argument[g_obs.free_calls - 1] = address;
  }
  g_obs.free_seen_at_00 = g_obs.free_seen_at_10 = 0;
  g_obs.free_seen_at_14 = 0;
  g_obs.free_seen_at_80 = g_obs.free_seen_at_84 = 0;
  g_obs.free_seen_at_88 = 0;
  // The receiver is recoverable from the argument on the self-free call, but not
  // on the span call, so the observer uses the receiver the base-destructor
  // observer recorded, plus a live one installed by the test below.
  if (g_active_receiver != nullptr) {
    g_obs.free_seen_at_00 = word_of(*g_active_receiver, kWord00Offset);
    g_obs.free_seen_at_10 = word_of(*g_active_receiver, kWord10Offset);
    g_obs.free_seen_at_14 = word_of(*g_active_receiver, kWord14Offset);
    g_obs.free_seen_at_80 = word_of(*g_active_receiver, kSpanBeginOffset);
    g_obs.free_seen_at_84 = word_of(*g_active_receiver, kSpanBeginOffset + 4);
    g_obs.free_seen_at_88 = word_of(*g_active_receiver, kSpanEndOffset);
  }
  if (g_obs.free_poison_vptr && g_active_receiver != nullptr) {
    std::memcpy(g_active_receiver->bytes + kWord00Offset, &g_obs.free_poison_vptr_value,
                sizeof g_obs.free_poison_vptr_value);
  }
}

// 0x00ecc65c -- the base destructor. __thiscall, receiver in ECX, no stack
// argument. The observer samples the receiver's dispatch words and span words at
// the moment of entry, which is what proves the three stores and the guard precede
// it, and optionally poisons receiver+0x00 so the self-free argument can be
// checked against a receiver whose stored word has moved.
extern "C" void PKG_SWARM_W1_00ECC620_THISCALL sporepedia_asset_destroy_00642190(
    OpaqueSporepediaAssetData* asset) {
  ++g_obs.destroy_calls;
  g_obs.record(kCallBaseDestroy);
  g_obs.destroy_receiver = asset;
  if (g_active_receiver != nullptr) {
    g_obs.destroy_seen_at_00 = word_of(*g_active_receiver, kWord00Offset);
    g_obs.destroy_seen_at_10 = word_of(*g_active_receiver, kWord10Offset);
    g_obs.destroy_seen_at_14 = word_of(*g_active_receiver, kWord14Offset);
    g_obs.destroy_seen_at_80 = word_of(*g_active_receiver, kSpanBeginOffset);
    g_obs.destroy_seen_at_88 = word_of(*g_active_receiver, kSpanEndOffset);
    g_obs.destroy_saw_span_free = g_obs.free_calls > 0;
  }
  if (g_obs.destroy_poison_vptr) {
    std::memcpy(asset->opaque_00.data() + kWord00Offset, &g_obs.destroy_poison_vptr_value,
                sizeof g_obs.destroy_poison_vptr_value);
  }
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ecc620

namespace {

using namespace openspore::reconstruction::pkg_swarm_w1_00ecc620;

// Case A -- the span is wide and non-null, the flag is clear. The span is freed,
// the class chain runs, and the storage is NOT released. The three dispatch words
// are written.
OpaqueSporepediaAssetData* case_span_freed_flag_clear() {
  const Word begin = 0x00b0b000u;
  const Span span = make_span(begin, 0x20u, 0xdeadbeefu);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  Receiver before = receiver;
  g_active_receiver = &receiver;

  OpaqueSporepediaAssetData* const result = re_00ecc620(as_asset(receiver), 0x00u);
  g_active_receiver = nullptr;

  check(g_obs.free_calls == 1, "A1: 0x00f47380 is called exactly once (the span)");
  check(g_obs.free_argument[0] == begin,
        "A2: the span free is handed the BEGIN word, not the end word");
  check(g_obs.destroy_calls == 1, "A3: 0x00642190 is called exactly once");
  check(g_obs.log_is(kCallFree, kCallBaseDestroy),
        "A4: the transfer order is span free, then base destructor");
  check(g_obs.destroy_saw_span_free,
        "A5: the base destructor runs after the span free, not before");
  check(g_obs.destroy_seen_at_00 == kObjectTableAt00 &&
            g_obs.destroy_seen_at_10 == kObjectTableAt10 &&
            g_obs.destroy_seen_at_14 == kObjectTableAt14,
        "A6: all three dispatch words are stored BEFORE the base destructor is called");
  check(g_obs.destroy_seen_at_80 == begin && g_obs.destroy_seen_at_88 == begin + 0x20u,
        "A7: the span words are untouched by the body up to the base destructor");
  check(word_of(receiver, kWord00Offset) == kObjectTableAt00 &&
            word_of(receiver, kWord10Offset) == kObjectTableAt10 &&
            word_of(receiver, kWord14Offset) == kObjectTableAt14,
        "A8: the three stored values are the exact 32-bit immediates");
  check(word_of(receiver, kSpanBeginOffset) == begin &&
            word_of(receiver, kSpanEndOffset) == begin + 0x20u,
        "A9: the body does not zero or advance the span words");
  check(word_of(receiver, kSpanBeginOffset + 4) == 0xdeadbeefu,
        "A10: the word at +0x84 is never read and never written by this body");
  check(result == as_asset(receiver), "A11: the return value is the receiver");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0 && diff.inside == 12,
          "A12: exactly the three dispatch words changed, twelve bytes, nothing else");
  }
  return result;
}

// Case B -- the same span with the flag SET. Three transfers, in order.
void case_flag_set_frees_the_storage() {
  const Word begin = 0x00c0c000u;
  const Span span = make_span(begin, 0x10u, 0x11111111u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  unsigned char* const base = receiver.bytes;
  g_active_receiver = &receiver;

  OpaqueSporepediaAssetData* const result = re_00ecc620(as_asset(receiver), 0x01u);
  g_active_receiver = nullptr;

  check(g_obs.free_calls == 2, "B1: 0x00f47380 is called twice (the span and the storage)");
  check(g_obs.free_argument[0] == begin, "B2: the first free is the span begin");
  check(g_obs.free_argument[1] == reinterpret_cast<Word>(base),
        "B3: the second free is handed the RECEIVER address itself");
  check(g_obs.destroy_calls == 1, "B4: the base destructor still runs exactly once");
  check(g_obs.log_is(kCallFree, kCallBaseDestroy, kCallFree),
        "B5: the transfer order is span free, base destructor, storage free");
  check(result == as_asset(receiver), "B6: the return value is the receiver on the freeing arm");
}

// Case C -- the constructor's own span. 0x01667bae - 0x01667bac == 2, which the
// mask and the bound reject, so nothing is deallocated and only the class chain
// runs. This is the case that shows the guard is a data-shape test.
void case_constructor_span_is_not_freed() {
  const Span span = make_span(0x01667bacu, 0x02u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  unsigned char* const base = receiver.bytes;
  g_active_receiver = &receiver;

  re_00ecc620(as_asset(receiver), 0x01u);
  g_active_receiver = nullptr;

  check(g_obs.free_calls == 1, "C1: the span is not freed, so only the storage free remains");
  check(g_obs.free_argument[0] == reinterpret_cast<Word>(base),
        "C2: and that one free is the receiver, not the span begin 0x01667bac");
  check(g_obs.destroy_calls == 1, "C3: the base destructor still runs");
  check(g_obs.log_is(kCallBaseDestroy, kCallFree),
        "C4: the transfer order is base destructor, storage free");
}

// Case D -- an empty span (begin == end, distance 0) with the flag clear: no call
// to the deallocation port at all. The only observable effect is the three stores.
void case_empty_span_calls_nothing() {
  const Span span = make_span(0x00d0d000u, 0x00u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  g_active_receiver = &receiver;

  re_00ecc620(as_asset(receiver), 0x00u);
  g_active_receiver = nullptr;

  check(g_obs.free_calls == 0, "D1: 0x00f47380 is not called at all");
  check(g_obs.destroy_calls == 1, "D2: 0x00642190 is still called");
  check(g_obs.log_is(kCallBaseDestroy), "D3: the base destructor is the only transfer");
  check(word_of(receiver, kWord14Offset) == kObjectTableAt14,
        "D4: the third dispatch word is written even when nothing is freed");
}

// Case E -- the span is wide but the begin is NULL. The second guard is
// independent of the first, so nothing is deallocated.
void case_null_begin_is_skipped() {
  const Span span = make_span(0x00000000u, 0x1000u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  g_active_receiver = &receiver;

  re_00ecc620(as_asset(receiver), 0x00u);
  g_active_receiver = nullptr;

  check(g_obs.free_calls == 0, "E1: a null span begin is never deallocated");
  check(g_obs.destroy_calls == 1, "E2: the base destructor still runs");
  check(g_obs.log_is(kCallBaseDestroy), "E3: the base destructor is the only transfer");
}

// -- REFUTATION CASES --------------------------------------------------------
// The cases above show the reconstruction behaving. The ones below are aimed at
// breaking it: each states the wrong reconstruction it is trying to catch.

// H. `CMP ECX,0x2` with `JLE` is a SIGNED compare. The discriminating inputs are
// the distances whose masked value has bit 31 set: huge unsigned, negative signed.
// A model that read the branch as unsigned would deallocate every one of them.
void case_distance_compare_is_signed() {
  const Word source = 0x00100000u;

  struct Input {
    Word distance;
    bool expect_free;
  };
  // Masked values: 0x80000000, 0x80000002, 0xfffffffe, 0xc0000000, 0x00000000e.
  const Input inputs[] = {
      {0x80000000u, false},  // masked 0x80000000: negative signed, huge unsigned
      {0x80000001u, false},  // masked 0x80000000: the same
      {0x80000002u, false},  // masked 0x80000002
      {0x80000003u, false},  // masked 0x80000002: the same
      {0xfffffffeu, false},  // masked 0xfffffffe: -2 signed
      {0xffffffffu, false},  // masked 0xfffffffe: -2 signed
      {0xc0000000u, false},  // masked 0xc0000000: -1073741824 signed
      {0x7fffffffu, true},   // masked 0x7ffffffe: the largest accepted value
      {0x7ffffffeu, true},   // masked 0x7ffffffe: the same
  };

  for (const Input& input : inputs) {
    g_obs.reset();
    Receiver receiver = make_receiver(make_span(source, input.distance, 0u));
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    const bool freed = g_obs.free_calls == 1;
    check(freed == input.expect_free,
          "H: the masked distance is compared as a SIGNED value against 2");
  }
}

// I. The boundary. The mask clears bit 0, so 3 becomes 2 and must be REJECTED, and
// 4 must be ACCEPTED. A model comparing against 0, 1 or 2 instead of using the
// mask-then-compare pair gets one of these two wrong.
void case_distance_boundary() {
  struct Input {
    Word distance;
    bool expect_free;
    const char* what;
  };
  const Input inputs[] = {
      {0x00000000u, false, "I: distance 0 is rejected"},
      {0x00000001u, false, "I: distance 1 is rejected (the mask makes it 0)"},
      {0x00000002u, false, "I: distance 2 is rejected (it IS the bound)"},
      {0x00000003u, false, "I: distance 3 is rejected (the mask makes it 2)"},
      {0x00000004u, true, "I: distance 4 is accepted (the first accepted value)"},
      {0x00000005u, true, "I: distance 5 is accepted (the mask makes it 4)"},
      {0x00000006u, true, "I: distance 6 is accepted"},
      {0x00000007u, true, "I: distance 7 is accepted (the mask makes it 6)"},
  };

  for (const Input& input : inputs) {
    g_obs.reset();
    Receiver receiver = make_receiver(make_span(0x00100000u, input.distance, 0u));
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check((g_obs.free_calls == 1) == input.expect_free, input.what);
  }
}

// J. The span is a raw BYTE distance: the body subtracts and masks and compares,
// and divides by nothing. Distance 4 is accepted, which a model that divided the
// distance by a four-byte element size would reject.
void case_distance_is_not_divided() {
  for (Word distance : {4u, 6u, 8u, 12u, 16u}) {
    g_obs.reset();
    Receiver receiver = make_receiver(make_span(0x00200000u, distance, 0u));
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check(g_obs.free_calls == 1,
          "J: the distance is never divided, so small even distances are accepted");
  }
}

// K. The pair the body reads is (+0x80, +0x88). A decoy at +0x84 -- the word the
// constructor writes and the word a sibling function at 0x00ecc530 reads -- is
// planted with a value chosen to flip the decision on its own, and must stay inert.
void case_span_pair_is_80_and_88() {
  // If the model had read (+0x80, +0x84) it would see a distance of 0x40 and free;
  // the truth is a distance of 0, so it must not. The mirror flips it: the real
  // pair is wide, and the +0x84 decoy is zero, so a model reading (+0x80, +0x84)
  // would see a distance of 0 and refuse to free.
  {
    g_obs.reset();
    Span span;
    span.begin = 0x00300000u;
    span.middle = 0x00300040u;  // would look like a distance of 0x40 at (+0x80,+0x84)
    span.end = 0x00300000u;     // the real distance is 0
    Receiver receiver = make_receiver(span);
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check(g_obs.free_calls == 0,
          "K1: the span end is the word at +0x88, not the one at +0x84");
    check(word_of(receiver, kSpanBeginOffset + 4) == 0x00300040u,
          "K2: the decoy at +0x84 is left exactly as it was found");
  }
  {
    g_obs.reset();
    Span span;
    span.begin = 0x00310000u;
    span.middle = 0x00310000u;  // would look like a distance of 0 at (+0x80,+0x84)
    span.end = 0x00310040u;     // the real distance is 0x40
    Receiver receiver = make_receiver(span);
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check(g_obs.free_calls == 1,
          "K3: the mirror case frees, so a model reading (+0x80,+0x84) is refuted both ways");
  }
  // And the neighbouring displacements: a wide-looking decoy at +0x7c and at +0x8c
  // must not move the decision either.
  {
    g_obs.reset();
    Span span;
    span.begin = 0x00400000u;
    span.middle = 0x00400000u;
    span.end = 0x00400000u;  // real distance 0 -> no free
    Receiver receiver = make_receiver(span);
    Word near_low = 0x00400100u;
    Word near_high = 0x00400300u;
    std::memcpy(receiver.bytes + kSpanBeginOffset - 4, &near_low, sizeof near_low);
    std::memcpy(receiver.bytes + kSpanEndOffset + 4, &near_high, sizeof near_high);
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check(g_obs.free_calls == 0,
          "K4: the words at +0x7c and +0x8c are not part of the pair");
    check(word_of(receiver, kSpanBeginOffset - 4) == 0x00400100u &&
              word_of(receiver, kSpanEndOffset + 4) == 0x00400300u,
          "K5: and neither of them was written");
  }
}

// L. WRONG POINTER LEVEL. The second 0x00f47380 call is handed the receiver, not
// the word stored at receiver+0x00. The base-destructor observer poisons that word
// with a value that could never be a heap address, and the free observer poisons
// it again; the argument must not follow.
void case_self_free_is_handed_the_receiver() {
  const Span span = make_span(0x00500000u, 0x08u, 0u);

  g_obs.reset();
  g_obs.destroy_poison_vptr = true;
  g_obs.destroy_poison_vptr_value = 0x5eed0000u;
  g_obs.free_poison_vptr = true;
  g_obs.free_poison_vptr_value = 0x5eed0000u;
  Receiver receiver = make_receiver(span);
  unsigned char* const base = receiver.bytes;
  g_active_receiver = &receiver;

  re_00ecc620(as_asset(receiver), 0x01u);
  g_active_receiver = nullptr;

  check(g_obs.free_argument[1] == reinterpret_cast<Word>(base),
        "L1: the storage free is handed the RECEIVER even though the stored word was poisoned");
  check(g_obs.free_argument[1] != g_obs.destroy_poison_vptr_value &&
            g_obs.free_argument[1] != kObjectTableAt00,
        "L2: it is neither the poisoned word nor the dispatch-table constant");
  check(g_obs.free_seen_at_00 == 0x5eed0000u,
        "L3: the free observer really did see the poisoned word at receiver+0x00");
  check(word_of(receiver, kWord00Offset) == 0x5eed0000u,
        "L4: the poison is still in place, so the argument cannot have come from it");
}

// M. The flag test is one BYTE of entry+4 against the immediate 0x01. Bits 1..7
// are ignored, so 0x02 must NOT free the storage and 0x03 must.
void case_flag_mask_is_bit_zero_of_one_byte() {
  struct Input {
    std::uint8_t flag;
    bool expect_free;
    const char* what;
  };
  const Input inputs[] = {
      {0x00u, false, "M1: flag 0x00 does not free"},
      {0x01u, true, "M2: flag 0x01 frees"},
      {0x02u, false, "M3: flag 0x02 does NOT free (only bit 0 is examined)"},
      {0x03u, true, "M4: flag 0x03 frees (bit 0 is set)"},
      {0x04u, false, "M5: flag 0x04 does not free"},
      {0x80u, false, "M6: flag 0x80 does not free (the high bit of the byte is not bit 0)"},
      {0xfeu, false, "M7: flag 0xfe does not free"},
      {0xffu, true, "M8: flag 0xff frees"},
  };

  for (const Input& input : inputs) {
    g_obs.reset();
    // A narrow span, so the ONLY possible call is the storage free and the count
    // of calls is exactly the flag's effect.
    Span span;
    span.begin = 0x00600000u;
    span.middle = 0u;
    span.end = 0x00600000u;
    Receiver receiver = make_receiver(span);
    unsigned char* const base = receiver.bytes;
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), input.flag);
    g_active_receiver = nullptr;
    check((g_obs.free_calls == 1) == input.expect_free, input.what);
    if (input.expect_free) {
      check(g_obs.free_argument[0] == reinterpret_cast<Word>(base),
            "M: and the one free is the receiver");
    }
  }
}

// N. The three dispatch words are three DISTINCT values at three DISTINCT
// displacements. Neighbour decoys at +0x04, +0x08, +0x0c and +0x18 are planted with
// values that would be obvious if a store went to the wrong place, and must not
// move.
void case_dispatch_words_are_three_distinct_slots() {
  const Span span = make_span(0x00700000u, 0x00u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  // Neighbour decoys: four distinct words straddling the three real slots, each
  // one a value a store landing at the wrong displacement would leave behind.
  const Word decoy_04 = 0xdead0004u;
  const Word decoy_08 = 0xdead0008u;
  const Word decoy_0c = 0xdead000cu;
  const Word decoy_18 = 0xdead0018u;
  std::memcpy(receiver.bytes + 0x04u, &decoy_04, sizeof decoy_04);
  std::memcpy(receiver.bytes + 0x08u, &decoy_08, sizeof decoy_08);
  std::memcpy(receiver.bytes + 0x0cu, &decoy_0c, sizeof decoy_0c);
  std::memcpy(receiver.bytes + 0x18u, &decoy_18, sizeof decoy_18);
  Receiver before = receiver;
  g_active_receiver = &receiver;
  re_00ecc620(as_asset(receiver), 0x00u);
  g_active_receiver = nullptr;

  check(word_of(receiver, kWord00Offset) == 0x014893b0u, "N1: the word at +0x00 is 0x014893b0");
  check(word_of(receiver, kWord10Offset) == 0x0148939cu, "N2: the word at +0x10 is 0x0148939c");
  check(word_of(receiver, kWord14Offset) == 0x0148938cu, "N3: the word at +0x14 is 0x0148938c");
  check(kObjectTableAt00 != kObjectTableAt10 && kObjectTableAt10 != kObjectTableAt14 &&
            kObjectTableAt00 != kObjectTableAt14,
        "N4: the three constants are pairwise distinct");
  check(word_of(receiver, 0x04u) == decoy_04, "N5: the word at +0x04 is untouched");
  check(word_of(receiver, 0x08u) == decoy_08, "N6: the word at +0x08 is untouched");
  check(word_of(receiver, 0x0cu) == decoy_0c, "N7: the word at +0x0c is untouched");
  check(word_of(receiver, 0x18u) == decoy_18, "N8: the word at +0x18 is untouched");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.outside == 0 && diff.inside == 12,
          "N9: exactly twelve bytes changed, all inside the three dispatch words");
  }
}

// O. ORDERING, in both directions. The span free must precede the base destructor
// and the storage free must follow it. The base-destructor observer records how
// many frees had already happened, and the second free observer samples the words
// the base destructor left behind.
void case_call_order_is_span_then_destroy_then_self() {
  const Span span = make_span(0x00800000u, 0x40u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  g_active_receiver = &receiver;
  re_00ecc620(as_asset(receiver), 0x01u);
  g_active_receiver = nullptr;

  check(g_obs.destroy_saw_span_free, "O1: the span free happened before the base destructor");
  check(g_obs.log_is(kCallFree, kCallBaseDestroy, kCallFree),
        "O2: the three transfers, in order: span free, base destructor, storage free");
  check(g_obs.free_argument[0] == 0x00800000u, "O3: the first free is the span begin");
  check(g_obs.free_argument[1] == reinterpret_cast<Word>(receiver.bytes),
        "O4: the second free is the receiver");
}

// P. A null begin with a huge span is still not deallocated. A model that
// implemented only the span test and forgot 0x00ecc64d would call the port with 0.
void case_null_begin_with_huge_span_is_not_deallocated() {
  struct Input {
    Word distance;
    const char* what;
  };
  const Input inputs[] = {
      {0x00000010u, "P1: a null begin with a 16-byte span is not deallocated"},
      {0x7fffffffu, "P2: a null begin with the largest positive span is not deallocated"},
      {0x80000000u, "P3: a null begin with a negative-as-signed span is not deallocated"},
  };

  for (const Input& input : inputs) {
    g_obs.reset();
    Span span;
    span.begin = 0u;
    span.middle = 0u;
    span.end = input.distance;
    Receiver receiver = make_receiver(span);
    unsigned char* const base = receiver.bytes;
    g_active_receiver = &receiver;
    re_00ecc620(as_asset(receiver), 0x00u);
    g_active_receiver = nullptr;
    check(g_obs.free_calls == 0, input.what);
    check(g_obs.destroy_calls == 1, "P: the base destructor still runs in that case");
    (void)base;
  }
}

// Q. ABI. The terminator is `RET 0x4`, so the callee owns the argument word. ESP
// is sampled inside a trampoline, before the pushes and after the return: the two
// are equal only when the callee popped all four bytes. A caller-cleaned
// convention would leave the second sample four bytes lower.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(OpaqueSporepediaAssetData* receiver, std::uint32_t flag_word) {
  const std::uint32_t target =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&re_00ecc620));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  // EAX and ECX are in the clobber list, so the compiler cannot have allocated
  // either input to them: every "r" operand therefore survives the `movl ...,%ecx`
  // that precedes its use. The flag is handed over as a full 32-bit word because
  // the stack slot IS four bytes wide (`RET 0x4`); only its low byte is read back
  // by the body, which is what the byte-level flag cases exercise.
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[flag]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver), [flag] "r"(flag_word)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

void case_argument_word_is_callee_cleaned() {
  const Span span = make_span(0x00900000u, 0x00u, 0u);

  g_obs.reset();
  Receiver receiver = make_receiver(span);
  g_active_receiver = &receiver;
  const EspSamples samples = call_measured(as_asset(receiver), 0x00u);
  g_active_receiver = nullptr;

  check(samples.after_return == samples.before_push,
        "Q1: the callee popped the argument word (RET 0x4), so ESP is balanced");
  check(g_obs.destroy_calls == 1, "Q2: the trampoline really reached the body");
  check(word_of(receiver, kWord00Offset) == kObjectTableAt00,
        "Q3: and the body really ran to its end");
  check(g_obs.destroy_receiver == as_asset(receiver),
        "Q4: ECX carried the receiver the trampoline was given");
  check(g_obs.destroy_seen_at_00 == kObjectTableAt00,
        "Q5: the three stores are already in place when the base destructor is called");
}

// The displacements and constants the reconstruction states, against the listing's
// own bytes, plus the signedness of the distance compare checked instruction by
// instruction.
void verify_machine_constants() {
  check(kReceiverWord00Displacement == 0x00u, "V1: the first dispatch word is at +0x00");
  check(kReceiverWord10Displacement == 0x10u, "V2: the second is at +0x10");
  check(kReceiverWord14Displacement == 0x14u, "V3: the third is at +0x14");
  check(kReceiverSpanBeginDisplacement == 0x80u, "V4: the span begin is at +0x80");
  check(kReceiverSpanEndDisplacement == 0x88u, "V5: the span end is at +0x88");
  check(kObjectTableAt00 == 0x014893b0u, "V6: the constant of the store at +0x00");
  check(kObjectTableAt10 == 0x0148939cu, "V7: the constant of the store at +0x10");
  check(kObjectTableAt14 == 0x0148938cu, "V8: the constant of the store at +0x14");
  check(kDistanceMask == 0xfffffffeu, "V9: the immediate of AND ECX at 0x00ecc645");
  check(kDistanceBound == 0x02u, "V10: the immediate of CMP ECX at 0x00ecc648");
  check(kDeletingFlagMask == 0x01u, "V11: the immediate of TEST BYTE PTR at 0x00ecc661");
  check(kAdjustingThunkForDisplacement10 == 0x00ecc600u, "V12: the +0x10 thunk");
  check(kAdjustingThunkForDisplacement14 == 0x00ecc610u, "V13: the +0x14 thunk");
  check(sizeof(OpaqueSporepediaAssetData) == 0x8cu,
        "V14: the modeled receiver ends after the last read word");
  check(kReceiverSpanEndDisplacement + 4 == sizeof(OpaqueSporepediaAssetData),
        "V15: the span end word ends the modeled receiver exactly");
  // The distance compare is spelled without an implementation-defined
  // unsigned-to-signed conversion, so it is checked against the plain signed
  // reading of `CMP ECX,0x2` / `JLE` over a table that straddles bit 31.
  {
    const Word probes[] = {0x00000000u, 0x00000001u, 0x00000002u, 0x00000003u,
                           0x00000004u, 0x7ffffffeu, 0x7fffffffu, 0x80000000u,
                           0x80000002u, 0xc0000000u, 0xfffffffeu, 0xffffffffu};
    bool agree = true;
    for (Word value : probes) {
      const std::int32_t signed_reading = static_cast<std::int32_t>(value);
      const bool expected = signed_reading > 2;
      if (signed_greater_than_distance_bound(value) != expected) {
        agree = false;
      }
    }
    check(agree,
          "V16: the masked-distance predicate is the SIGNED reading of CMP 2 / JLE");
  }
}

}  // namespace

int main() {
  verify_machine_constants();
  case_span_freed_flag_clear();
  case_flag_set_frees_the_storage();
  case_constructor_span_is_not_freed();
  case_empty_span_calls_nothing();
  case_null_begin_is_skipped();
  case_distance_compare_is_signed();
  case_distance_boundary();
  case_distance_is_not_divided();
  case_span_pair_is_80_and_88();
  case_self_free_is_handed_the_receiver();
  case_flag_mask_is_bit_zero_of_one_byte();
  case_dispatch_words_are_three_distinct_slots();
  case_call_order_is_span_then_destroy_then_self();
  case_null_begin_with_huge_span_is_not_deallocated();
  case_argument_word_is_callee_cleaned();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
