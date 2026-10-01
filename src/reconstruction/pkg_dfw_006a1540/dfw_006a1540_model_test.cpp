// PKG-DFW-006A1540 -- model test for the reconstruction of VA 0x006a1540.
//
// Plain int main(), explicit checks, no framework and no external dependency.
// The two callees this package does not own (0x0093aa70 and 0x00693390) are
// defined here as recording observers, so every claim the reconstruction makes
// about the calls it makes is checked against what the machine listing fixes:
// the order of the transfers, the arity and push order of each call's
// arguments, the value stored through the word pointer before each call, the
// address formed for the payload call, the stride, the two separate quotient
// evaluations, the branch that is taken for which input, and the return word on
// every path.

#include "dfw_006a1540_types.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace {

using namespace openspore::reconstruction::pkg_dfw_006a1540;

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char *what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void check_eq_int(long long got, long long want, const char *what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL: %s (got %lld, want %lld)\n", what, got, want);
  }
}

void check_eq_word(Word got, Word want, const char *what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL: %s (got 0x%08x, want 0x%08x)\n", what, got, want);
  }
}

// ---------------------------------------------------------------------------
// Observer state
// ---------------------------------------------------------------------------

enum CallKind { kWriteWords, kWriteEntry };

struct RecordedCall {
  CallKind kind;
  const void *sink;    // argument 1
  Word words_value;    // kWriteWords: the 4-byte word behind argument 2
  Word count;          // kWriteWords: argument 3
  Word format;         // argument 4 of kWriteWords, argument 3 of kWriteEntry
  const void *payload; // kWriteEntry: argument 2
};

std::vector<RecordedCall> g_calls;
std::vector<int> g_words_results;  // consumed in order, one per kWriteWords
std::vector<int> g_entry_results;  // consumed in order, one per kWriteEntry
std::size_t g_words_index = 0;
std::size_t g_entry_index = 0;

// A bound on the recorded sequence, so a reconstruction that iterates far more
// times than the listing allows is reported as a failed check instead of being
// allowed to run the test out of memory.
constexpr std::size_t kMaxRecordedCalls = 256;
int g_record_budget_overflows = 0;

// Indexed access that reports a missing call rather than reading past the end, so
// a wrong reconstruction produces a FAIL line instead of an abort.
const RecordedCall &at(std::size_t index) {
  static const RecordedCall kMissing = {kWriteWords, nullptr, 0u, 0u, 0u, nullptr};
  if (index < g_calls.size()) {
    return g_calls[index];
  }
  check(false, "a transfer the listing makes was not recorded");
  return kMissing;
}

// Hooks used by the mutation cases below. The machine's only call inside the
// body is the one between the two quotient evaluations, and its only memory
// operands are the sink and the two receiver words, so letting the observer move
// a receiver word is the only way to tell the body's re-reads of +0x18 and +0x1c
// apart from a cached copy of either.
OpaquePropertyList *g_receiver = nullptr;
OpaquePropertyEntry *g_new_end = nullptr;
bool g_mutate_on_first_words_call = false;
// When the Nth write-words call returns, move the receiver's +0x18 by this many
// bytes. -1 disables the hook.
long long g_shift_begin_at_words_call = -1;
long long g_shift_begin_bytes = 0;

void reset_observer() {
  g_calls.clear();
  g_words_results.clear();
  g_entry_results.clear();
  g_words_index = 0;
  g_entry_index = 0;
  g_mutate_on_first_words_call = false;
  g_receiver = nullptr;
  g_new_end = nullptr;
  g_shift_begin_at_words_call = -1;
  g_shift_begin_bytes = 0;
}

// Appends a recorded transfer, refusing to grow without bound. Overflowing the
// budget is itself a failed check, so a reconstruction that iterates far more
// times than the listing allows is reported rather than tolerated.
void record(const RecordedCall &call) {
  if (g_calls.size() >= kMaxRecordedCalls) {
    ++g_record_budget_overflows;
    return;
  }
  g_calls.push_back(call);
}

void set_range(OpaquePropertyList *list, OpaquePropertyEntry *begin,
               OpaquePropertyEntry *end) {
  list->range_begin_018 = begin;
  list->range_end_01c = end;
}

// The 0x0093aa70 call sites, at 0x006a156f and 0x006a15b8. Four dwords pushed
// right to left (0x0 / 0x1 / &word / sink), the caller removes them again with
// ADD ESP,0x10 at 0x006a158d and 0x006a15bd.
extern "C" bool PKG_DFW_006A1540_CDECL
dfw_write_words_0093aa70(OpaqueStreamSink *sink, const Word *words, Word count,
                         Word format) {
  RecordedCall call;
  call.kind = kWriteWords;
  call.sink = sink;
  call.words_value = words != nullptr ? *words : 0u;
  call.count = count;
  call.format = format;
  call.payload = nullptr;
  record(call);

  const int result =
      g_words_index < g_words_results.size() ? g_words_results[g_words_index] : 0;
  ++g_words_index;

  if (g_mutate_on_first_words_call) {
    g_mutate_on_first_words_call = false;
    g_receiver->range_end_01c = g_new_end;
  }
  if (g_shift_begin_at_words_call >= 0 &&
      static_cast<long long>(g_words_index) - 1 == g_shift_begin_at_words_call) {
    g_receiver->range_begin_018 = reinterpret_cast<OpaquePropertyEntry *>(
        reinterpret_cast<std::uint8_t *>(g_receiver->range_begin_018) +
        g_shift_begin_bytes);
  }
  return result != 0;
}

// The 0x00693390 call site, at 0x006a15d0. Three dwords pushed right to left
// (0x0 / address / sink), the caller removes them with ADD ESP,0xc at
// 0x006a15d5.
extern "C" bool PKG_DFW_006A1540_CDECL
dfw_write_entry_00693390(OpaqueStreamSink *sink, std::uint8_t *payload,
                         Word format) {
  RecordedCall call;
  call.kind = kWriteEntry;
  call.sink = sink;
  call.words_value = 0u;
  call.count = 0u;
  call.format = format;
  call.payload = payload;
  record(call);

  const int result =
      g_entry_index < g_entry_results.size() ? g_entry_results[g_entry_index] : 0;
  ++g_entry_index;
  return result != 0;
}

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

// The receiver is declared exactly as the header declares it: 0x18 opaque bytes
// before the two pointers. The test never reads those bytes; it only needs the
// two pointers to sit on the displacements the listing fixes, which the header's
// static_asserts already prove.
alignas(4) OpaquePropertyList g_list;
std::uint8_t g_sink_object[16];
OpaqueStreamSink *const g_sink = reinterpret_cast<OpaqueStreamSink *>(g_sink_object);

// Builds `count` elements, each 0x18 bytes, with a distinct first word so the
// stride is checkable, and points the receiver at [begin, begin + count).
OpaquePropertyEntry *build_elements(int count, int first_word_base) {
  static OpaquePropertyEntry pool[8];
  for (int i = 0; i < count; ++i) {
    pool[i].word_00 = static_cast<Word>(first_word_base + i);
    std::memset(pool[i].opaque_04_17, static_cast<int>(0xa0 + i),
                sizeof pool[i].opaque_04_17);
  }
  set_range(&g_list, pool, pool + count);
  return pool;
}

// The call sequence the listing fixes for a successful run over `count`
// elements: one count write, then per element a word write followed by an
// entry write.
void expect_call_shape(std::size_t count, const char *label) {
  check_eq_int(static_cast<long long>(g_calls.size()),
               static_cast<long long>(1 + 2 * count), label);
  if (g_calls.empty()) {
    return;
  }
  check(at(0).kind == kWriteWords, "the first transfer is a word write");
  check_eq_word(static_cast<Word>(static_cast<long long>(at(0).count)), 1u,
                "the count word is written with argument 3 == 1");
  check_eq_word(at(0).format, 0u,
                "the count word is written with argument 4 == 0");
}

} // namespace

int main() {
  // -- the signed division the body performs, 0x006a1550..0x006a1568 ---------
  // Checked against the C division the machine sequence is a reciprocal for,
  // over a table that includes both signs and both sides of a multiple of 0x18.
  {
    static const std::int32_t kSpans[] = {0,      0x18,  0x30,  0x17,  0x19,
                                          0x2f,   0x4f,  0x100, 0x101, -0x18,
                                          -0x19,  -0x30, -0x1,  -0x100, 1,
                                          23,     47,    48,    0x7fffffff,
                                          -0x7fffffff - 1, -0x7fffffff, 0x2e,
                                          0x2f * 0x100, 0x18 * 1000 + 1,
                                          0x18 * 1000 - 1};
    for (std::size_t i = 0; i < sizeof kSpans / sizeof kSpans[0]; ++i) {
      const std::int32_t span = kSpans[i];
      check_eq_int(entry_count_for_span(span), span / 0x18,
                   "the 0x2aaaaaab sequence divides the span by 0x18");
    }
    // Boundaries around one element: a full stride, one byte short, one byte
    // over. The first two differ by a whole quotient, which is the only thing
    // the JLE at 0x006a1592 is sensitive to besides zero and negative.
    check_eq_int(entry_count_for_span(0x18), 1, "0x18 bytes is one element");
    check_eq_int(entry_count_for_span(0x17), 0, "0x17 bytes is no element");
    check_eq_int(entry_count_for_span(0x19), 1, "0x19 bytes is one element");
    check_eq_int(entry_count_for_span(0x2f), 1, "0x2f bytes is one element");
    check_eq_int(entry_count_for_span(0x30), 2, "0x30 bytes is two elements");
    // The negative side: the quotient is negative, and the loop guard is a
    // SIGNED JLE, so a negative quotient skips the loop exactly as a zero
    // quotient does. Nothing in the body clamps it, and the count word written
    // to the sink carries the negative value verbatim.
    check_eq_int(entry_count_for_span(-0x18), -1, "-0x18 bytes is -1 element");
    check_eq_int(entry_count_for_span(-0x19), -1, "-0x19 bytes is -1 element");
    check_eq_int(entry_count_for_span(-0x30), -2, "-0x30 bytes is -2 elements");
    check(entry_count_for_span(-0x18) < 0,
          "a negative span yields a negative quotient, not a clamped zero");
    // A sweep, because the reciprocal sequence is only correct over its whole
    // range if the two roundings were spelled the way the listing spells them.
    for (std::int32_t span = -0x1800; span <= 0x1800; ++span) {
      if (entry_count_for_span(span) != span / 0x18) {
        check(false, "the 0x2aaaaaab sequence matches / 0x18 across the sweep");
        break;
      }
    }
    check(true, "the 0x2aaaaaab sequence matches / 0x18 across -0x1800..0x1800");
  }

  // -- an empty range: only the count write, and the verdict is that call's --
  {
    reset_observer();
    build_elements(0, 100);
    g_words_results = {1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0, "an empty range makes exactly one call");
    check_eq_word(at(0).words_value, 0u,
                  "an empty range writes the count word 0");
    check(at(0).sink == g_sink, "the sink is the first argument");
    check(result, "an empty range returns the count write's verdict");
  }

  // -- an empty range whose count write fails -------------------------------
  {
    reset_observer();
    build_elements(0, 100);
    g_words_results = {0};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0, "a failed count write makes no further call");
    check(!result, "a failed count write returns false");
  }

  // -- three elements, everything succeeds: order, arity, stride, address ----
  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(3, 100);
    g_words_results = {1, 1, 1, 1};
    g_entry_results = {1, 1, 1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(3, "three elements make 1 + 2*3 calls");
    check(result, "a fully successful run returns true");

    check_eq_word(at(0).words_value, 3u,
                  "the first call writes the quotient (end-begin)/0x18");
    check_eq_int(g_words_index, 4, "four word writes: one count, three ids");
    check_eq_int(g_entry_index, 3, "three entry writes");

    for (int i = 0; i < 3; ++i) {
      const std::size_t id = 1u + static_cast<std::size_t>(2 * i);
      check(at(id).kind == kWriteWords,
            "each element is preceded by a word write");
      check(at(id + 1).kind == kWriteEntry,
            "each word write is followed by an entry write");
      check_eq_word(at(id).words_value, static_cast<Word>(100 + i),
                    "the id word is the element's first word at +0x00");
      check_eq_word(at(id).count, 1u, "each id write passes 1 as argument 3");
      check_eq_word(at(id).format, 0u, "each id write passes 0 as argument 4");
      check_eq_word(at(id + 1).format, 0u,
                    "each entry write passes 0 as argument 3");
      check(at(id).sink == g_sink && at(id + 1).sink == g_sink,
            "every call receives the stack argument as its first argument");
      const std::uint8_t *want =
          reinterpret_cast<const std::uint8_t *>(base + i) + 0x4u;
      check(at(id + 1).payload == want,
            "the entry write receives the element base + 0x04");
    }
    // The stride is 0x18, not 0x4 and not 0x20: element 2's id word must be 0x30
    // past the base, which is only true if the offset advanced by 0x18 twice.
    check_eq_word(at(5).words_value, 102u,
                  "the third element's word is two 0x18 strides in");
  }

  // -- the count write fails: no element is touched at all -------------------
  {
    reset_observer();
    build_elements(3, 100);
    g_words_results = {0};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0, "a failed count write stops every element write");
    check(!result, "a failed count write returns false");
  }

  // -- an element's word write fails: that element's payload is never written
  {
    reset_observer();
    build_elements(3, 100);
    g_words_results = {1, 0};
    g_entry_results = {1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    check_eq_int(static_cast<long long>(g_calls.size()), 2,
                 "the first element's failed id write skips its payload write");
    check(at(1).kind == kWriteWords,
          "the second transfer is the failed id write");
    check_eq_int(g_entry_index, 0, "no payload address is ever formed");
    check(!result, "a failed id write returns false");
  }

  // -- an element's payload write fails --------------------------------------
  {
    reset_observer();
    build_elements(3, 100);
    g_words_results = {1, 1, 1, 1};
    g_entry_results = {0};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    check_eq_int(static_cast<long long>(g_calls.size()), 3,
                 "the failing payload write ends the run at element 0");
    check(!result, "a failed payload write returns false");
  }

  // -- a failure in the middle stops the rest, but not the countdown ---------
  // 0x006a15c2 / 0x006a15da jump to 0x006a15e0, which is the tail block, so the
  // countdown keeps running while every later iteration takes the skip path. The
  // observable consequence is that no later element is ever addressed.
  {
    reset_observer();
    build_elements(4, 100);
    g_words_results = {1, 1, 0};
    g_entry_results = {1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    check_eq_int(static_cast<long long>(g_calls.size()), 4,
                 "element 1's failed id write ends the transfer sequence");
    check(at(3).kind == kWriteWords, "the fourth transfer is the failing id");
    check_eq_word(at(3).words_value, 101u,
                  "the failing id is element 1's word, so the stride is 0x18");
    check_eq_int(g_entry_index, 1, "only element 0's payload was written");
    check(!result, "a mid-run failure returns false");
  }

  // -- a negative span: the count word is negative and the loop is skipped ----
  // 0x006a1592 is a signed JLE, so a negative quotient skips the loop exactly
  // as a zero quotient does, after the negative count has already been written.
  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(3, 100);
    set_range(&g_list, base + 2, base);  // span = -2 * 0x18
    g_words_results = {1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0, "a negative span makes only the count write");
    check_eq_word(at(0).words_value, 0xfffffffeu,
                  "a span of -0x30 writes the count word 0xfffffffe");
    check(result, "a negative span returns the count write's verdict");
  }

  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(2, 100);
    set_range(&g_list, base, base);  // span = 0
    g_words_results = {0};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0, "a zero span makes only the count write");
    check_eq_word(at(0).words_value, 0u, "a zero span writes the count 0");
    check(!result, "a zero span with a failing count write returns false");
  }

  // -- two_quotients ---------------------------------------------------------
  // 0x006a154a..0x006a1568 and 0x006a1574..0x006a158b are two evaluations of the
  // same division, separated by the first call. Nothing in the body can make
  // them differ on its own -- the call writes to a sink, not to the receiver --
  // so the only way to observe that they are two evaluations is to let the
  // observer change the receiver's +0x1c across the first call. A reconstruction
  // that folded the two into one variable fails both of the next two cases.
  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(3, 100);
    g_receiver = &g_list;
    g_new_end = base;  // end collapses onto begin
    g_mutate_on_first_words_call = true;
    g_words_results = {1, 1, 1};
    g_entry_results = {1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    expect_call_shape(0,
                      "a receiver emptied by the count write bounds the loop at "
                      "the SECOND quotient, so nothing else is written");
    check_eq_word(at(0).words_value, 3u,
                  "the first quotient is still the count that was written");
    check(result, "the run still returns the count write's verdict");
  }

  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(4, 100);
    set_range(&g_list, base, base + 1);  // the first quotient is one element
    g_receiver = &g_list;
    g_new_end = base + 4;  // end grows to four elements
    g_mutate_on_first_words_call = true;
    g_words_results = {1, 1, 1, 1, 1};
    g_entry_results = {1, 1, 1, 1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    check_eq_int(static_cast<long long>(g_calls.size()), 9,
                 "a receiver grown by the count write makes the loop run the "
                 "SECOND quotient's four elements, not the first quotient's one");
    check_eq_word(at(0).words_value, 1u,
                  "the first quotient was one element and was written as one");
    check_eq_int(g_entry_index, 4, "four payload writes follow the growth");
    check(result, "the grown run returns true");
  }

  // -- the range begin is re-read, per iteration AND per use ----------------
  // 0x006a15a4 reads the receiver's +0x18 to form the id word's address, and
  // 0x006a15c4 reads it AGAIN to form the payload address -- two independent
  // reads of the same displacement in one iteration -- and 0x006a154d reads it a
  // fifth time for the first span. A reconstruction that hoisted the word, or
  // that reused one read for both addresses, is wrong and this case is what says
  // so: the observer moves +0x18 by one stride while element 0's id write is in
  // flight, so the payload address for element 0 must come from the NEW base
  // while its id word came from the old one.
  {
    reset_observer();
    OpaquePropertyEntry *base = build_elements(4, 100);
    set_range(&g_list, base, base + 4);
    g_receiver = &g_list;
    g_shift_begin_at_words_call = 1;  // element 0's id write
    g_shift_begin_bytes = 0x18;
    g_words_results = {1, 1, 1, 1, 1};
    g_entry_results = {1, 1, 1, 1};
    const bool result = proplist_write_006a1540(&g_list, g_sink);
    check_eq_int(static_cast<long long>(g_calls.size()), 9,
                 "moving +0x18 does not change how many transfers are made");
    check(result, "moving +0x18 does not change the return word");
    // Element 0: the id word was read from the OLD base, the payload address is
    // formed from the NEW one (0x006a15c4 re-reads +0x18 after 0x006a15a4).
    check_eq_word(at(1).words_value, 100u,
                  "element 0's id word came from the base before the move");
    check(at(2).payload == reinterpret_cast<const std::uint8_t *>(base + 1) + 0x4u,
          "element 0's payload address came from the base AFTER the move");
    // Element 1: offset 0x18 onto the new base is now pool[2], not pool[1].
    check_eq_word(at(3).words_value, 102u,
                  "element 1's id word uses the new base plus the 0x18 stride");
    check(at(4).payload == reinterpret_cast<const std::uint8_t *>(base + 2) + 0x4u,
          "element 1's payload address uses the new base as well");
    // Element 2: pool[3]. Element 3 walks off the built range into the tail of
    // the static pool, which is zero, so the value is stated rather than
    // assumed -- the point of the case is the address, not the value.
    check_eq_word(at(5).words_value, 103u, "element 2's id word is pool[3]'s word");
    check(at(6).payload == reinterpret_cast<const std::uint8_t *>(base + 3) + 0x4u,
          "element 2's payload address is pool[3] + 0x04");
    check_eq_word(at(7).words_value, 0u,
                  "element 3's id word is the zero the unbuilt pool slot holds");
    check(at(8).payload == reinterpret_cast<const std::uint8_t *>(base + 4) + 0x4u,
          "element 3's payload address is pool[4] + 0x04");
  }

  // -- the word pointer is read after the store, not before -----------------
  // 0x006a156b and 0x006a15b4 both store the quotient or the element word into
  // the spill slot after the four (or three) pushes and before the CALL. The
  // observers read through the pointer they were handed, so a reconstruction
  // that passed the address of a word it had not yet filled would be caught with
  // the value assertions above. This makes the point explicitly.
  {
    reset_observer();
    build_elements(1, 0xdeadbeefu);
    g_words_results = {1};
    g_entry_results = {1};
    (void)proplist_write_006a1540(&g_list, g_sink);
    check_eq_word(at(0).words_value, 1u, "the count word is stored before the call");
    check_eq_word(at(1).words_value, 0xdeadbeefu,
                  "the element word is stored before the call");
  }

  check_eq_int(g_record_budget_overflows, 0,
               "no case recorded more transfers than the listing can make");

  if (g_failures == 0) {
    std::printf("PASS: %d checks\n", g_checks);
    return 0;
  }
  std::printf("FAILED: %d of %d checks\n", g_failures, g_checks);
  return 1;
}
