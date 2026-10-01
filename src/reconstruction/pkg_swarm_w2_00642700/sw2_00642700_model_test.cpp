// PKG-SWARM-W2-00642700 -- model test for VA 0x00642700
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// This is a falsification test, not a walk-through. It defines BOTH direct
// callees of the body under reconstruction as OBSERVERS, so it sees every
// transfer the reconstruction makes -- which callee, with which arguments, in
// which order, and what each of them found in memory AT THE MOMENT OF THE CALL
// -- and then drives the reconstruction with inputs chosen to BREAK the
// highest-risk hypotheses rather than to confirm them.
//
// THE TWO DIRECT CALLEES, all defined here as observers and nowhere else (and
// both with the linkage the package header declares, which is why they sit
// outside this file's anonymous namespace):
//
//   0x00556140  cdecl, TWO stack words, no receiver. Sampled for: the argument
//               ORDER (the descriptor first, the key second, fixed by the
//               callee's own reads at 0x0055614d and 0x005561e2), the identity
//               of the descriptor (the ADDRESS of the receiver's own +0x04,
//               formed by 0x00642710 and never the word at the receiver's
//               +0x00), and the five literals in their five fixed positions.
//   0x004558a0  __thiscall, TWO stack words, receiver in ECX. Sampled for: the
//               argument order, the receiver (the ARGUMENT object, not the
//               body's own receiver), the identity of the first word (the
//               vector's cursor, passed BY VALUE), the identity of the second
//               (the ADDRESS of the value, not the value), and -- the point of
//               the whole test -- the value the vector's cursor word held AT
//               THE MOMENT OF THE CALL, which is the only way to see that the
//               slow arm does not advance the cursor before delegating.
//
// WHAT THIS TEST ASSERTS, in one place: the two exit values and the three
// exits; that the gate word is read at the receiver's +0x08 and at no other
// displacement; that a failing gate reaches no callee and leaves the argument
// object byte-identical; the five literals, in order, on the five calls; that
// the descriptor handed to 0x00556140 is the receiver's +0x04 on all five
// calls; the unsigned, STRICT capacity test (cursor == capacity grows, cursor ==
// capacity - 1 appends in place) and its behaviour when the two readings of the
// same words disagree; the null-cursor guard, which skips the STORE but not the
// cursor advance, including on the fifth append where the guard jumps to the
// shared true tail; that the slow arm does not advance the cursor itself; the
// order of the two words handed to 0x004558a0; that the receiver is byte-for-
// byte unchanged; that the argument object's +0x00 and +0x0c are never touched;
// that the value 0x00556140 returns is stored and never dereferenced; and that
// nothing carries between two calls.
//
// WHAT THIS TEST DELIBERATELY DOES NOT ASSERT, and why:
//
//  * The MEANING of the gate word 0x2b978c46, of the five literals, of the
//    word at the receiver's +0x08 as anything other than the compared word, or
//    of the vector's +0x04/+0x08 as anything other than the compared and stored
//    words. No record for this target fixes any of them; the listing shows only
//    that they are compared, passed and stored.
//  * The ADDRESSES of the two value slots. The machine parks the first lookup's
//    result in the frame slot the receiver was pushed into and the other four in
//    the CALLER'S OWN ARGUMENT WORD; the model uses one local for all five,
//    because the incoming argument is dead after 0x0064271e and nothing the
//    machine computes is ever handed back out in a way a caller can observe.
//    Asserting the model's single address here would be a claim the machine
//    contradicts, so the frame fact is recorded in the .cpp and asserted
//    nowhere.
//  * That 0x00556140's result is a pointer to anything in particular, or that
//    0x004558a0's return value is anything. The body stores the first and never
//    reads the second, so the test stores distinctive words and asserts
//    nothing about their meaning.
//  * The upper three bytes of EAX on any exit. The listing writes AL only, so
//    the model's declared return type is one byte wide and no wider value is
//    claimed.
//  * Anything about the C types beyond the width, and nothing at all about the
//    callees' own bodies beyond the four effects of 0x004558a0 that the test
//    reproduces (documented at the observer itself) and the immediate,
//    terminator and argument order of 0x00556140.
//  * A capacity that the grow observer cannot honour. The observer refuses to
//    write through a cursor that is outside the test's own arena and says so at
//    its own definition; the case that needs it is the signed/unsigned case,
//    where the cursor word is deliberately not a real address.

#include "sw2_00642700_types.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w2_00642700 {

// ============================ the scaffolding for the observers ============
//
// The two direct callees themselves are defined at the BOTTOM of this file,
// outside the anonymous namespace: the reconstruction's own translation unit
// reaches them through the package header's external declarations, so an
// internal-linkage definition would be a different function.

namespace {

// ---------------------------------------------------------------- scaffolding

int g_failures = 0;

#define CHECK(condition, ...)                                   \
  do {                                                          \
    if (!(condition)) {                                         \
      ++g_failures;                                             \
      std::printf("FAIL %s:%d: ", __FILE__, __LINE__);           \
      std::printf(__VA_ARGS__);                                 \
      std::printf("\n");                                        \
    }                                                           \
  } while (false)

#define CHECK_EQ_U(actual, expected, label)                                \
  do {                                                                     \
    const unsigned long long a_ = static_cast<unsigned long long>(actual);  \
    const unsigned long long e_ = static_cast<unsigned long long>(expected);\
    if (a_ != e_) {                                                        \
      ++g_failures;                                                        \
      std::printf("FAIL %s:%d: %s is 0x%llx, expected 0x%llx\n", __FILE__, \
                  __LINE__, (label), a_, e_);                              \
    }                                                                      \
  } while (false)

using Body = bool(PKG_SWARM_W2_00642700_THISCALL*)(SporepediaTypeKeySource*,
                                                    SporepediaTypeKeyVector*);

// The arena the in-place arm appends into, and the grow observer's bookkeeping
// about it. 128 words is far more than the five appends need, so no case that
// stays inside it can run off the end.
constexpr std::size_t kArenaWords = 128;
Word g_arena[kArenaWords] = {};

// The objects the test hands the body. Both are generous byte runs so a decoy
// can be planted at any neighbouring displacement and read back as a word.
struct Fixture {
  std::uint8_t source[0x40];  // the body reaches 0x04 and 0x08; the tail is decoys
  std::uint8_t sink[0x40];    // 0x04 and 0x08 are the words; the rest is decoys
};

Fixture g_fixture;

std::vector<std::string> g_log;

// -- what each observer recorded ---------------------------------------------
std::uint32_t g_lookup_calls = 0;
SporepediaTypeDescriptor* g_lookup_descriptor = nullptr;
Word g_lookup_key = 0;
std::vector<Word> g_lookup_keys;  // the key of every call, in order
// The vector's own cursor word, sampled on entry to each lookup. The body reads
// the word AFTER the lookup returns, so this is the state left by the previous
// append -- which is the only way to assert the cursor advance per append rather
// than only at the end of the body.
std::vector<Word> g_cursor_word_at_lookup;

std::uint32_t g_insert_calls = 0;
SporepediaTypeKeyVector* g_insert_self = nullptr;
Word* g_insert_cursor = nullptr;
const Word* g_insert_value_addr = nullptr;
Word g_insert_value = 0;
Word g_insert_cursor_word_at_call = 0;  // the vector's own cursor word, at the call
Word g_insert_capacity_word_at_call = 0;

// How the observers behave is configuration, not code, so one reconstruction
// serves every case.
struct Plan {
  // The word 0x00556140 returns for its Nth call, in call order. Five distinct
  // words, so a body that shifted the call order would be visible.
  Word lookup_result[5] = {0x00000aa1u, 0x00000bb2u, 0x00000cc3u, 0x00000dd4u,
                           0x00000ee5u};
  // Zero the vector's cursor word just before call N (0-based) and every call
  // after it, to drive the null-cursor arm on a chosen iteration or on all of
  // them. 0 is a real setting here, not a false one, hence the -1 default.
  int zero_cursor_from_call = -1;
  // How many ELEMENTS of headroom the grow observer leaves above the new cursor.
  // 0 makes the next append grow again; 2 lets two appends land in place. The
  // unit matters and is stated here because the body under test is exactly where
  // a byte/element confusion hides: the capacity is an ADDRESS, so a headroom of
  // 2 BYTES would leave no room for a 4-byte element and the next append would
  // grow anyway.
  std::size_t grow_capacity_bump = 0;
  // Make 0x00556140 return an address that is not mapped, to prove the body
  // stores its result and never dereferences it.
  bool return_unmapped = false;
  // The cursor and capacity words as the test seeds them.
  Word seed_cursor = 0;
  Word seed_capacity = 0;
};

Plan g_plan;

void configure() {
  std::memset(&g_fixture, 0, sizeof(g_fixture));
  std::memset(g_arena, 0, sizeof(g_arena));
  g_log.clear();
  g_plan = Plan();
  g_lookup_calls = 0;
  g_lookup_descriptor = nullptr;
  g_lookup_key = 0;
  g_lookup_keys.clear();
  g_cursor_word_at_lookup.clear();
  g_insert_calls = 0;
  g_insert_self = nullptr;
  g_insert_cursor = nullptr;
  g_insert_value_addr = nullptr;
  g_insert_value = 0;
  g_insert_cursor_word_at_call = 0;
  g_insert_capacity_word_at_call = 0;
  g_plan.seed_cursor = reinterpret_cast<Word>(&g_arena[0]);
  g_plan.seed_capacity = reinterpret_cast<Word>(&g_arena[kArenaWords]);
  // The argument object's two live words.
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = g_plan.seed_cursor;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = g_plan.seed_capacity;
  // A decoy at the receiver's own +0x00: a full 12-byte vector-shaped object, so
  // a body that took the vector from the wrong base would have something real to
  // write through and would be caught by the pointer checks rather than faulting.
  word_ref(g_fixture.source, kVectorBeginDisplacement) = reinterpret_cast<Word>(&g_arena[0]);
  word_ref(g_fixture.source, kVectorCursorDisplacement) = reinterpret_cast<Word>(&g_arena[0]);
  word_ref(g_fixture.source, kVectorCapacityDisplacement) = reinterpret_cast<Word>(&g_arena[1]);
  // A decoy at the receiver's +0x0c: another word that would be a plausible
  // lookup base one displacement out.
  word_ref(g_fixture.source, kVectorCapacityDisplacement + 4) = 0xdeadc0deu;
  // The gate word, at its own displacement only.
  word_ref(g_fixture.source, kSourceGateDisplacement) = kSourceGateWord;
}

Body the_body() { return &sporepedia_append_five_lookups_00642700; }

SporepediaTypeKeySource* the_source() {
  return reinterpret_cast<SporepediaTypeKeySource*>(g_fixture.source);
}

SporepediaTypeKeyVector* the_sink() {
  return reinterpret_cast<SporepediaTypeKeyVector*>(g_fixture.sink);
}

Word cursor_word() { return *word_at(g_fixture.sink, kVectorCursorDisplacement); }

Word capacity_word() { return *word_at(g_fixture.sink, kVectorCapacityDisplacement); }

std::string joined_log() {
  std::string text;
  for (const std::string& entry : g_log) {
    if (!text.empty()) {
      text += " | ";
    }
    text += entry;
  }
  return text;
}

// The transfer sequence, compared as a SHAPE: "lookup" or "insert". The pointer
// arguments move as the test's arena is consumed, so the exact text of each
// entry is checked by the pointer assertions instead and only the ORDER is
// compared here.
void expect_shape(const char* label, const std::vector<std::string>& got,
                  const std::vector<std::string>& expected) {
  if (got == expected) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s: the transfer SEQUENCE is wrong\n  want: ", label);
  for (std::size_t i = 0; i < expected.size(); ++i) {
    std::printf("%s%s", i ? " | " : "", expected[i].c_str());
  }
  std::printf("\n  got:  ");
  for (std::size_t i = 0; i < got.size(); ++i) {
    std::printf("%s%s", i ? " | " : "", got[i].c_str());
  }
  std::printf("\n");
}

void expect_log(const char* label, const std::vector<std::string>& expected) {
  if (g_log == expected) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s: the transfer sequence is wrong\n  want: ", label);
  for (std::size_t i = 0; i < expected.size(); ++i) {
    std::printf("%s%s", i ? " | " : "", expected[i].c_str());
  }
  std::printf("\n  got:  %s\n", joined_log().c_str());
}

std::size_t count_log(const char* prefix) {
  std::size_t total = 0;
  for (const std::string& entry : g_log) {
    if (entry.compare(0, std::strlen(prefix), prefix) == 0) {
      ++total;
    }
  }
  return total;
}

// The five words the body appends, read back out of the arena in the order they
// were stored. Only meaningful when every append landed in place.
std::vector<Word> arena_words(std::size_t from, std::size_t count) {
  std::vector<Word> out;
  for (std::size_t i = 0; i < count; ++i) {
    out.push_back(g_arena[from + i]);
  }
  return out;
}

void expect_words(const std::vector<Word>& actual, const std::vector<Word>& wanted,
                  const char* label) {
  if (actual == wanted) {
    return;
  }
  ++g_failures;
  std::printf("FAIL %s\n  want:", label);
  for (Word value : wanted) {
    std::printf(" %08x", static_cast<unsigned>(value));
  }
  std::printf("\n  got: ");
  for (Word value : actual) {
    std::printf(" %08x", static_cast<unsigned>(value));
  }
  std::printf("\n");
}

// =============================================================== the cases ===

// A. The gate. A wrong word at the receiver's +0x08 must take the false exit
// alone: no callee reached, and the argument object left byte-identical even
// though the test seeds it with a cursor and a capacity.
void case_gate_word_displacement_and_value() {
  const Word wrong[] = {0x00000000u, 0x2b978c47u, 0x3d97a8e4u, 0xffffffffu};
  for (Word value : wrong) {
    configure();
    word_ref(g_fixture.source, kSourceGateDisplacement) = value;
    std::uint8_t before[0x40];
    std::memcpy(before, g_fixture.sink, sizeof before);
    const bool result = the_body()(the_source(), the_sink());
    CHECK(!result, "A: a gate word of 0x%08x must return false", static_cast<unsigned>(value));
    expect_log("A: the failing gate reaches no callee at all", {});
    CHECK(std::memcmp(before, g_fixture.sink, sizeof before) == 0,
          "A: the argument object is left byte-identical when the gate fails");
  }
  // The mirror image: the gate word planted at the NEIGHBOURING displacements,
  // with the real one wrong, must not take the fast path. This is the wrong
  // receiver-offset decoy.
  configure();
  word_ref(g_fixture.source, kSourceGateDisplacement) = 0x11111111u;
  word_ref(g_fixture.source, kSourceGateDisplacement - 4) = kSourceGateWord;
  word_ref(g_fixture.source, kSourceGateDisplacement + 4) = kSourceGateWord;
  CHECK(!the_body()(the_source(), the_sink()),
        "A2: the gate word at +0x04 or +0x0c does not open the gate");
  expect_log("A2: the gate word is read at one displacement only", {});

  // And the same decoys with the real word correct: the body must still run the
  // whole chain, which is what proves it read +0x08 and not its neighbours.
  configure();
  word_ref(g_fixture.source, kSourceGateDisplacement - 4) = 0x22222222u;
  word_ref(g_fixture.source, kSourceGateDisplacement + 4) = 0x33333333u;
  (void)the_body()(the_source(), the_sink());
  CHECK_EQ_U(g_lookup_calls, 5, "A3: the correct gate word at +0x08 runs all five lookups");
}

// B. The whole chain in place, and the five literals in their five positions.
void case_five_in_place_appends() {
  configure();
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "B: the body reports true once the gate is passed");
  CHECK_EQ_U(g_lookup_calls, 5, "B: exactly five lookups");
  CHECK_EQ_U(g_insert_calls, 0, "B: no reallocation when the capacity allows five appends");

  // The descriptor is the receiver's own +0x04 on EVERY call, and it is an
  // address rather than a loaded word -- so the log's first argument is compared
  // against that address, not against the word stored there.
  SporepediaTypeDescriptor* const want_descriptor =
      reinterpret_cast<SporepediaTypeDescriptor*>(&g_fixture.source[kSourceLookupBaseDisplacement]);
  std::vector<std::string> want;
  for (std::size_t i = 0; i < 5; ++i) {
    char text[160];
    std::snprintf(text, sizeof text, "lookup00556140(self=%p,key=%08x)",
                  static_cast<void*>(want_descriptor),
                  static_cast<unsigned>(i < g_lookup_keys.size() ? g_lookup_keys[i] : 0u));
    want.emplace_back(text);
  }
  expect_log("B: five lookups, in order, with the descriptor as the first argument", want);

  const Word keys[5] = {0xa426730bu, 0xad56080cu, 0xf71fa311u, 0xbeb528cbu, 0x2db6dad3u};
  expect_words(g_lookup_keys, std::vector<Word>(keys, keys + 5),
               "B: the five literals, in the listing's order, one per call");
  CHECK(g_lookup_descriptor == want_descriptor,
        "B: the descriptor is the receiver's +0x04, not the receiver and not +0x00");

  // The five results, stored in the arena in the same order, and the cursor moved
  // five elements forward.
  std::vector<Word> wanted;
  for (Word value : g_plan.lookup_result) {
    wanted.push_back(value);
  }
  expect_words(arena_words(0, 5), wanted, "B: the five results, stored in order");
  CHECK_EQ_U(cursor_word(), reinterpret_cast<Word>(&g_arena[5]),
             "B: the cursor advanced by exactly five 4-byte elements");
  CHECK_EQ_U(capacity_word(), g_plan.seed_capacity, "B: the capacity word is not written in place");
  CHECK_EQ_U(*word_at(g_fixture.sink, kVectorBeginDisplacement), 0u,
             "B: the argument's +0x00 is never written by this body");
}

// C. All five appends reallocating. The observer sees the descriptor of the call
// and, on every one, the cursor word the body had NOT yet advanced.
void case_five_reallocations() {
  configure();
  g_plan.grow_capacity_bump = 0;  // every append grows again
  // cursor == capacity, which is the state the `JNC` sends to the slow arm, and
  // the observer leaves it that way after every reallocation.
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = g_plan.seed_cursor;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = g_plan.seed_cursor;
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "C: five reallocations still report true");
  CHECK_EQ_U(g_insert_calls, 5, "C: one reallocation per append");
  CHECK_EQ_U(count_log("insert004558a0"), 5, "C: five reallocation transfers in the log");

  // The reallocation is handed the ARGUMENT object, the cursor BY VALUE and the
  // ADDRESS of the value -- and, the ordering point, the vector's own cursor word
  // still holds exactly that cursor at the moment of the call.
  CHECK(g_insert_self == the_sink(),
        "C: the reallocation's receiver is the argument object, not this body's receiver");
  CHECK(g_insert_cursor != nullptr && g_insert_cursor != g_insert_value_addr,
        "C: the first word is a cursor and the second is a different address");
  CHECK_EQ_U(static_cast<std::uintptr_t>(g_insert_cursor_word_at_call),
             static_cast<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(g_insert_cursor)),
             "C: the cursor word still holds the value handed over, so the slow arm does "
             "not advance the cursor before delegating");

  // The grow observer's own effect is the only thing that moved the cursor: five
  // reallocations, one element each, and the value landed at the cursor the body
  // passed. So the arena holds the five results contiguously and the cursor sits
  // five elements on.
  std::vector<Word> wanted;
  for (Word value : g_plan.lookup_result) {
    wanted.push_back(value);
  }
  expect_words(arena_words(0, 5), wanted,
               "C: the five results, in order, after five reallocations");
  CHECK_EQ_U(cursor_word(), reinterpret_cast<Word>(&g_arena[5]),
             "C: the cursor advanced by exactly five elements, all of them by the callee");
}

// D. A mixed sequence. The capacity the observer leaves allows two in-place
// appends per reallocation, so the two arms interleave and the order is
// refutable.
void case_mixed_arms() {
  configure();
  g_plan.grow_capacity_bump = 2;
  // Start with the cursor already AT capacity so the first append reallocates.
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = g_plan.seed_cursor;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = g_plan.seed_cursor;
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "D: a mixed sequence reports true");
  CHECK_EQ_U(g_lookup_calls, 5, "D: five lookups in a mixed sequence");
  CHECK_EQ_U(g_insert_calls, 2, "D: two reallocations for a bump of two");

  // The order the log must show: lookup, insert, lookup, lookup, insert,
  // lookup, lookup -- the two arms interleaved, at the iterations the bump of
  // two fixes. Compared as a SHAPE, because the pointer arguments move as the
  // arena is consumed and their exact values are checked elsewhere.
  std::vector<std::string> want;
  for (int i = 0; i < 5; ++i) {
    want.emplace_back("lookup");
    if (i == 0 || i == 3) {
      want.emplace_back("insert");
    }
  }
  std::vector<std::string> shape;
  for (const std::string& entry : g_log) {
    shape.push_back(entry.compare(0, 6, "lookup") == 0 ? "lookup" : "insert");
  }
  expect_shape("D: the arms interleave lookup,insert,lookup,lookup,lookup,insert,lookup", shape,
               want);
  CHECK_EQ_U(shape.size(), 7, "D: seven transfers, five lookups and two reallocations");
  expect_words(arena_words(0, 5),
               std::vector<Word>(g_plan.lookup_result, g_plan.lookup_result + 5),
               "D: the five results, in order, across both arms");
}

// E. The capacity test's margin, which is what the `JNC` fixes: cursor ==
// capacity reallocates and cursor == capacity - 1 appends in place. Both halves
// are driven and both are read off the FIRST append's arm, which is the append
// the seeded words actually govern -- later appends see words the observer has
// itself rewritten.
void case_capacity_boundary() {
  // The reallocation arm: the two words are EQUAL, and `JNC` is "greater or
  // equal", so this must reallocate.
  configure();
  g_plan.grow_capacity_bump = 4;  // one reallocation, then four in place
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = g_plan.seed_cursor;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = g_plan.seed_cursor;
  (void)the_body()(the_source(), the_sink());
  CHECK_EQ_U(g_insert_calls, 1, "E: cursor == capacity takes the reallocation arm");
  CHECK_EQ_U(count_log("insert"), 1, "E: exactly one reallocation transfer");
  CHECK_EQ_U(g_arena[0], g_plan.lookup_result[0],
             "E: the first result landed at the cursor the body passed");

  // The in-place arm: the cursor is exactly ONE ELEMENT below the capacity, so
  // the `>=` is false and the body appends without delegating.
  configure();
  const Word one_below = g_plan.seed_cursor;
  const Word one_above = one_below + kVectorElementStride;
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = one_below;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = one_above;
  (void)the_body()(the_source(), the_sink());
  CHECK_EQ_U(count_log("insert"), 4,
             "E2: cursor == capacity - 1 appends the FIRST one in place, so the only four "
             "reallocations are the second through fifth appends");
  CHECK_EQ_U(g_arena[0], g_plan.lookup_result[0],
             "E2: the first result was stored in place, one element below the capacity");
  // Sampled on entry to the second lookup, i.e. immediately after the first
  // append: the cursor is exactly one element on, which is the capacity, and that
  // is what forces the second append onto the reallocation arm.
  CHECK(g_cursor_word_at_lookup.size() == 5, "E2: all five lookups were reached");
  if (g_cursor_word_at_lookup.size() == 5) {
    CHECK_EQ_U(g_cursor_word_at_lookup[1], one_above,
               "E2: after the first append the cursor sits exactly on the capacity");
    CHECK_EQ_U(g_cursor_word_at_lookup[0], one_below, "E2: the seeded cursor, sampled at lookup 1");
  }
}

// F. Signed versus unsigned. The two words are chosen so the readings disagree:
// as unsigned the cursor is above the capacity, as signed it is below.
void case_capacity_compare_is_unsigned() {
  configure();
  g_plan.grow_capacity_bump = 0;
  word_ref(g_fixture.sink, kVectorCursorDisplacement) = 0x80000000u;
  word_ref(g_fixture.sink, kVectorCapacityDisplacement) = 0x40000000u;
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "F: the body still reports true");
  CHECK_EQ_U(g_insert_calls, 5,
             "F: 0x80000000 >= 0x40000000 UNSIGNED, so every append reallocates; a signed "
             "reading would have appended in place through 0x80000000");
  CHECK_EQ_U(g_lookup_calls, 5, "F: the gate passed, so all five lookups ran");
}

// G. The null-cursor guard. The store is skipped and the cursor is still
// advanced, on every append and -- separately, through the fifth append's
// jump to the shared true tail -- on the last one.
void case_null_cursor_skips_the_store_only() {
  // The null cursor is re-seeded before every append, because the body re-reads
  // the word each time and an in-place null cursor would leave the word at +4 and
  // the next append would then store through the address 4. Test scaffolding,
  // and declared as such.
  configure();
  g_plan.zero_cursor_from_call = 0;
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "G: a null cursor throughout still reports true");
  CHECK_EQ_U(g_insert_calls, 0, "G: a null cursor is below the capacity, so the in-place arm runs");
  CHECK_EQ_U(g_lookup_calls, 5, "G: all five lookups ran");
  CHECK_EQ_U(cursor_word(), kVectorElementStride,
             "G: the cursor word was advanced by 0x04 even though nothing was stored");
  std::vector<Word> untouched(kArenaWords, 0u);
  expect_words(arena_words(0, 5), std::vector<Word>(5, 0u),
               "G: nothing was written through the null cursor on any of the five appends");

  // The fifth append's null guard jumps to 0x00642826, the shared true tail, so
  // it must skip the store AND still report true. Only the fifth append sees a
  // null cursor here, which is the only way to reach that jump.
  configure();
  g_plan.zero_cursor_from_call = 4;
  const bool second = the_body()(the_source(), the_sink());
  CHECK(second, "G2: a null cursor on the FIFTH append still reports true");
  CHECK_EQ_U(g_insert_calls, 0, "G2: the fifth append took the in-place arm");
  CHECK_EQ_U(g_arena[4], 0u, "G2: the fifth append's store was skipped");
  CHECK_EQ_U(cursor_word(), kVectorElementStride,
             "G2: the fifth append advanced the cursor anyway, before the null test");
  expect_words(arena_words(0, 4), std::vector<Word>(g_plan.lookup_result, g_plan.lookup_result + 4),
               "G2: the first four results, in order");
}

// H. The receiver is written by nothing. Byte-comparing the whole run is the only
// way to keep that falsifiable rather than assumed.
void case_receiver_is_not_written() {
  configure();
  g_plan.grow_capacity_bump = 2;
  std::uint8_t before[0x40];
  std::memcpy(before, g_fixture.source, sizeof before);
  for (int call = 0; call < 3; ++call) {
    (void)the_body()(the_source(), the_sink());
  }
  CHECK(std::memcmp(before, g_fixture.source, sizeof before) == 0,
        "H: three mixed calls left every byte of the receiver's 0x40-byte run unchanged");

  configure();
  word_ref(g_fixture.source, kSourceGateDisplacement) = 0x12345678u;
  std::memcpy(before, g_fixture.source, sizeof before);
  (void)the_body()(the_source(), the_sink());
  CHECK(std::memcmp(before, g_fixture.source, sizeof before) == 0,
        "H2: the failing gate writes nothing either");
}

// I. The argument object: exactly two of its words move, and the third never
// does. A decoy word is planted at its +0x0c, which is where a body reading the
// capacity one displacement out would look.
void case_argument_object_touches_two_words() {
  configure();
  g_plan.grow_capacity_bump = 1;
  *word_at(g_fixture.sink, kVectorCapacityDisplacement + 4) = 0xdeadc0deu;
  std::uint8_t before[0x40];
  std::memcpy(before, g_fixture.sink, sizeof before);
  (void)the_body()(the_source(), the_sink());
  CHECK_EQ_U(g_fixture.sink[0], 0u, "I: the argument's +0x00 is untouched");
  CHECK_EQ_U(*word_at(g_fixture.sink, kVectorCapacityDisplacement + 4), 0xdeadc0deu,
             "I: the decoy word at the argument's +0x0c is untouched, so a body reading the "
             "capacity one displacement out is refuted");
  const bool cursor_moved = std::memcmp(&before[kVectorCursorDisplacement],
                                        &g_fixture.sink[kVectorCursorDisplacement], 4) != 0;
  const bool capacity_moved = std::memcmp(&before[kVectorCapacityDisplacement],
                                          &g_fixture.sink[kVectorCapacityDisplacement], 4) != 0;
  CHECK(cursor_moved, "I2: the cursor word did move");
  CHECK(!capacity_moved,
        "I2: with every append in place the capacity word is written by nothing at all");
  CHECK_EQ_U(g_insert_calls, 0, "I2: and no reallocation ran");
}


// J. The lookup's result is stored, never dereferenced. The observer returns an
// address that is not mapped on this host, so a body that read through it would
// fault rather than quietly succeed.
void case_lookup_result_is_never_dereferenced() {
  configure();
  g_plan.return_unmapped = true;
  g_plan.grow_capacity_bump = 0;
  const bool result = the_body()(the_source(), the_sink());
  CHECK(result, "J: an unmapped lookup result still reports true");
  CHECK_EQ_U(g_lookup_calls, 5, "J: all five lookups ran");
  CHECK_EQ_U(g_arena[0], 1u,
             "J: the first result is the unmapped word itself, stored verbatim");
  expect_words(arena_words(0, 5), std::vector<Word>(5, 1u),
               "J: all five unmapped results stored verbatim");
}

// K. Nothing carries between two calls. Two runs in a row with different
// observer results: a reconstruction that kept anything alive across calls
// hands the second call the first call's state.
void case_no_state_carries_between_calls() {
  configure();
  (void)the_body()(the_source(), the_sink());
  CHECK_EQ_U(g_arena[0], g_plan.lookup_result[0], "K: the first call's first result");

  configure();
  for (int i = 0; i < 5; ++i) {
    g_plan.lookup_result[i] = 0x0000f00du;
  }
  (void)the_body()(the_source(), the_sink());
  expect_words(arena_words(0, 5), std::vector<Word>(5, 0x0000f00du),
               "K2: the second call re-reads the argument object and re-derives everything");
  CHECK_EQ_U(g_lookup_calls, 5, "K2: the chain ran again in full");
  CHECK_EQ_U(g_insert_calls, 0, "K2: no transfer carried over");
}

}  // namespace

// ================= the two direct callees, in their own definitions =========
//
// They are written here, outside the anonymous namespace, because the
// reconstruction's translation unit reaches them through the package header's
// external declarations.

void* PKG_SWARM_W2_00642700_CDECL sporepedia_type_lookup_00556140(
    SporepediaTypeDescriptor* descriptor, Word key) {
  ++g_lookup_calls;
  g_lookup_descriptor = descriptor;
  g_lookup_key = key;
  g_lookup_keys.push_back(key);
  g_cursor_word_at_lookup.push_back(*word_at(g_fixture.sink, kVectorCursorDisplacement));
  if (g_plan.zero_cursor_from_call >= 0 &&
      static_cast<int>(g_lookup_keys.size() - 1) >= g_plan.zero_cursor_from_call) {
    // Test scaffolding, and declared as such: the body re-reads the cursor word
    // before every append, so zeroing it here is what drives the null-cursor arm
    // on one chosen iteration without the body caching anything.
    word_ref(g_fixture.sink, kVectorCursorDisplacement) = 0u;
  }
  char text[160];
  std::snprintf(text, sizeof text, "lookup00556140(self=%p,key=%08x)", static_cast<void*>(descriptor),
                static_cast<unsigned>(key));
  g_log.emplace_back(text);
  const Word result =
      g_plan.return_unmapped ? 1u : g_plan.lookup_result[(g_lookup_keys.size() - 1) % 5];
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(result));
}

void PKG_SWARM_W2_00642700_THISCALL sporepedia_vector_insert_004558a0(
    SporepediaTypeKeyVector* self, Word* cursor, const Word* value) {
  ++g_insert_calls;
  g_insert_self = self;
  g_insert_cursor = cursor;
  g_insert_value_addr = value;
  g_insert_value = *value;
  // The ordering sample: what the object held when the call was entered.
  g_insert_cursor_word_at_call = *word_at(self, kVectorCursorDisplacement);
  g_insert_capacity_word_at_call = *word_at(self, kVectorCapacityDisplacement);
  char text[192];
  std::snprintf(text, sizeof text, "insert004558a0(self=%p,cursor=%p,value=%08x)",
                static_cast<void*>(self), static_cast<void*>(cursor),
                static_cast<unsigned>(g_insert_value));
  g_log.emplace_back(text);

  // What 0x004558a0's own body does to the object, read from its image bytes:
  //   00455957/00455959  the value is stored at the cursor it was handed
  //   00455961/00455967  the cursor word becomes that cursor plus one element
  //   00455ac7/00455acd  the capacity word is rebuilt
  //   00455ab6/00455abe  the begin word is rewritten
  // Test scaffolding, and declared as such: the observer refuses to write through
  // a cursor that is outside the test's own arena, because case F deliberately
  // seeds a cursor word that is not an address. That refusal is scaffolding and
  // no claim is made about what the real callee would do there.
  const bool in_arena = cursor >= &g_arena[0] && cursor < &g_arena[kArenaWords];
  if (in_arena) {
    *cursor = *value;
    *word_at(self, kVectorCursorDisplacement) =
        reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
    *word_at(self, kVectorCapacityDisplacement) = reinterpret_cast<Word>(
        reinterpret_cast<std::uintptr_t>(cursor) +
        kVectorElementStride * (1 + g_plan.grow_capacity_bump));
    *word_at(self, kVectorBeginDisplacement) = reinterpret_cast<Word>(cursor);
  }
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00642700

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w2_00642700;  // NOLINT
  case_gate_word_displacement_and_value();
  case_five_in_place_appends();
  case_five_reallocations();
  case_mixed_arms();
  case_capacity_boundary();
  case_capacity_compare_is_unsigned();
  case_null_cursor_skips_the_store_only();
  case_receiver_is_not_written();
  case_argument_object_touches_two_words();
  case_lookup_result_is_never_dereferenced();
  case_no_state_carries_between_calls();
  if (g_failures != 0) {
    std::printf("%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
