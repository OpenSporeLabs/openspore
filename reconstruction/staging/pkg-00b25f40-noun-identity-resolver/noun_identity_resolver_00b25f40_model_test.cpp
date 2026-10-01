// Model test and mutation battery for 0x00b25f40.
//
// Two directions, and both must hold:
//   * wrong bodies written inline below are each refuted by the same battery;
//   * externally perturbing noun_identity_resolver_00b25f40.cpp makes the run
//     fail, while the unperturbed build passes.
// The battery reads the reconstruction only through its published port, so it
// can observe what the reconstruction actually forwards and nothing else.

#include <sys/wait.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <vector>

#include "noun_identity_resolver_00b25f40.hpp"

namespace {

using namespace openspore::reconstruction::pkg_00b25f40;

#if defined(_MSC_VER) || defined(__clang__)
#define PKG_00B25F40_TEST_THISCALL __thiscall
#else
#define PKG_00B25F40_TEST_THISCALL __attribute__((stdcall))
#endif

#define PKG_00B25F40_CHECK(condition) \
  do {                                \
    if (!(condition)) {               \
      __builtin_abort();              \
    }                                 \
  } while (false)

enum class TraceKind : std::uint8_t {
  kProjectionLookup,
  kIdentityProbe,
};

struct Trace {
  std::vector<TraceKind> entries;
};

Trace trace;

// What the fake 0x00b21340 saw, and what it returns.
NounProjection* observed_receiver = nullptr;
NounProjectionVector* lookup_result = nullptr;
std::uint32_t word_one = 0;
std::uint32_t word_two = 0;
std::uint32_t word_three = 0;
std::uint32_t word_four = 0;
std::uint32_t word_five = 0;

// The identity each probe reports, and the order probes were entered in.
std::vector<std::uint32_t> reported_identity{7U, 0xdeadbeefU, 9U};
std::vector<NounObject*> probe_order;

// Neighbouring state the body must never touch. Nothing in the listing stores
// to memory outside the saved-register pops, so a counter that stays put is a
// statement about the body rather than about the fixture.
std::uint32_t relationship_state = 0x13572468U;
std::uint32_t political_state = 0x24681357U;

// Armed by the re-read case below. The probe it hangs on repoints the
// container's begin word mid-walk, so a body whose loop head re-reads that word
// (the listing puts `8b 07` MOV EAX,[EDI] at 0x00b25f76, inside the loop) walks
// the new array and one that froze the pointer on the first read does not.
NounProjectionVector* mutable_vector = nullptr;
std::int32_t repoint_on_probe = -1;
NounObject* const* replacement_begin = nullptr;

void repoint_begin_if_armed() {
  if (mutable_vector == nullptr) {
    return;
  }
  const std::int32_t visited = static_cast<std::int32_t>(probe_order.size());
  if (visited == repoint_on_probe) {
    container_begin(mutable_vector) = replacement_begin;
  }
}

NounObjectVtable table_a{};
NounObjectVtable table_b{};
NounObjectVtable table_c{};
NounObject candidate_a{};
NounObject candidate_b{};
NounObject candidate_c{};
NounObject* entries[3]{};
NounProjectionVector vector_fixture{};
NounProjectionVector empty_fixture{};
NounProjectionVector reversed_fixture{};

std::uint32_t PKG_00B25F40_TEST_THISCALL probe_a(NounObject* candidate) {
  PKG_00B25F40_CHECK(candidate == &candidate_a);
  probe_order.push_back(candidate);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  repoint_begin_if_armed();
  return reported_identity[0];
}

std::uint32_t PKG_00B25F40_TEST_THISCALL probe_b(NounObject* candidate) {
  PKG_00B25F40_CHECK(candidate == &candidate_b);
  probe_order.push_back(candidate);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  return reported_identity[1];
}

std::uint32_t PKG_00B25F40_TEST_THISCALL probe_c(NounObject* candidate) {
  PKG_00B25F40_CHECK(candidate == &candidate_c);
  probe_order.push_back(candidate);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  return reported_identity[2];
}

// Sits one word below the slot the body dispatches. The body never enters it; a
// reconstruction that read the neighbouring displacement would, and the run
// would abort here rather than silently agree.
std::uint32_t PKG_00B25F40_TEST_THISCALL
probe_neighbour(NounObject* candidate) {
  PKG_00B25F40_CHECK(false &&
                     "the body dispatched the slot below 0x4c, not the one the "
                     "listing reads at 0x00b25f7d");
  return 0xfeedfaceU + static_cast<std::uint32_t>(
                           reinterpret_cast<std::uintptr_t>(candidate));
}

NounProjectionVector* PKG_00B25F40_TEST_THISCALL projection_lookup(
    NounProjection* receiver, std::uint32_t arg_one, std::uint32_t arg_two,
    std::uint32_t arg_three, std::uint32_t arg_four, std::uint32_t arg_five) {
  observed_receiver = receiver;
  word_one = arg_one;
  word_two = arg_two;
  word_three = arg_three;
  word_four = arg_four;
  word_five = arg_five;
  trace.entries.push_back(TraceKind::kProjectionLookup);
  return lookup_result;
}

void reset_fixture() {
  trace.entries.clear();
  observed_receiver = nullptr;
  lookup_result = &vector_fixture;
  word_one = word_two = word_three = word_four = word_five = 0;
  probe_order.clear();
  reported_identity = {7U, 0xdeadbeefU, 9U};
  table_a = {};
  table_b = {};
  table_c = {};
  table_a.slot_4c = probe_a;
  table_b.slot_4c = probe_b;
  table_c.slot_4c = probe_c;
  table_a.neighbour_below = probe_neighbour;
  table_b.neighbour_below = probe_neighbour;
  table_c.neighbour_below = probe_neighbour;
  mutable_vector = nullptr;
  repoint_on_probe = -1;
  replacement_begin = nullptr;
  candidate_a.first_word = &table_a;
  candidate_b.first_word = &table_b;
  candidate_c.first_word = &table_c;
  entries[0] = &candidate_a;
  entries[1] = &candidate_b;
  entries[2] = &candidate_c;
  // Every container is zeroed BEFORE any slot is written. The three are
  // adjacent globals of exactly two pointer words each, so zeroing one after
  // writing another's slot erases that slot -- which is a bug in the fixture,
  // not a fact about the body, and it is invisible under one compiler's layout
  // and fatal under another's.
  vector_fixture = {};
  empty_fixture = {};
  reversed_fixture = {};
  container_begin(&vector_fixture) = entries;
  container_end(&vector_fixture) = entries + 3;
  container_begin(&empty_fixture) = entries;
  container_end(&empty_fixture) = entries;
  container_begin(&reversed_fixture) = entries + 3;
  container_end(&reversed_fixture) = entries;
}

void install_ports() {
  g_native_ports.noun_projection_lookup_00b21340 = projection_lookup;
  // g_018c816a is deliberately NOT assigned here: its initialiser comes from
  // the reconstruction and the battery checks the value it publishes.
  PKG_00B25F40_CHECK(g_018c816a == 0x018c816aU);
}

void expect_trace(std::initializer_list<TraceKind> expected) {
  PKG_00B25F40_CHECK(trace.entries.size() == expected.size());
  std::size_t index = 0;
  for (const TraceKind kind : expected) {
    PKG_00B25F40_CHECK(trace.entries[index] == kind);
    ++index;
  }
}

std::uint32_t* receiver_storage() {
  static std::uint32_t storage = 0;
  return &storage;
}

NounProjection* receiver() {
  return reinterpret_cast<NounProjection*>(receiver_storage());
}

using Resolver = NounObject*(PKG_00B25F40_TEST_THISCALL*)(NounProjection*,
                                                          std::uint32_t);

// The reconstruction's own entry point, read as bytes. The body's terminator is
// `c2 04 00` RET 0x4 at 0x00b25f95 and 0x00b25f9e: it pops its own four-byte
// stack argument. A caller-cleanup build emits a bare `c3` instead, and on
// x86-32 that is not a spelling difference -- it is a different stack contract,
// so it is checked here against the emitted code rather than against a typedef.
namespace {
// The body's terminator is `c2 04 00` RET 0x4 at 0x00b25f95 and 0x00b25f9e: the
// callee pops its own four-byte stack argument, which on x86-32 is what
// separates this calling convention from caller cleanup. It is asserted on the
// DECLARED type rather than on emitted bytes, because a scan for an opcode byte
// finds that byte inside an immediate operand too (`81 c3 03 00 00 00` in the
// emitted body carries 0xc3 as data) and would decide nothing.
extern "C" NounObject* callee_cleans_this(NounProjection*, std::uint32_t)
#if defined(_MSC_VER) || defined(__clang__)
    __attribute__((thiscall));
#else
    __attribute__((stdcall));
#endif
extern "C" NounObject* caller_cleans_this(NounProjection*, std::uint32_t);

using CalleeCleans = decltype(&callee_cleans_this);
using CallerCleans = decltype(&caller_cleans_this);
using Actual = decltype(&noun_identity_resolver_00b25f40);

static_assert(std::is_convertible<Actual, CalleeCleans>::value,
              "0x00b25f40 ends in RET 0x4, so its declaration must be the "
              "callee-cleans convention");
static_assert(!std::is_convertible<Actual, CallerCleans>::value,
              "0x00b25f40 ends in RET 0x4, so its declaration must NOT be the "
              "caller-cleans convention");
}

void expect_propagated_words() {
  PKG_00B25F40_CHECK(word_one == 0x00b21080U);
  PKG_00B25F40_CHECK(word_two == 0x00d3d420U);
  PKG_00B25F40_CHECK(word_three == 0x00b236c0U);
  PKG_00B25F40_CHECK(word_four == 0x00b1e500U);
  PKG_00B25F40_CHECK(word_five == 0x018c816aU);
}

// -- the battery ------------------------------------------------------------

void case_propagation(Resolver resolve) {
  reset_fixture();
  NounObject* result = resolve(receiver(), 7U);

  PKG_00B25F40_CHECK(observed_receiver == receiver());
  expect_propagated_words();
  PKG_00B25F40_CHECK(result == &candidate_a);
  expect_trace({TraceKind::kProjectionLookup, TraceKind::kIdentityProbe});
}

void case_first_match_returns_early(Resolver resolve) {
  reset_fixture();
  reported_identity = {7U, 7U, 9U};
  NounObject* result = resolve(receiver(), 7U);

  PKG_00B25F40_CHECK(result == &candidate_a);
  PKG_00B25F40_CHECK(probe_order.size() == 1);
  expect_trace({TraceKind::kProjectionLookup, TraceKind::kIdentityProbe});
}

void case_middle_match_probes_in_order(Resolver resolve) {
  reset_fixture();
  reported_identity = {7U, 0xdeadbeefU, 0xdeadbeefU};
  NounObject* result = resolve(receiver(), 0xdeadbeefU);

  PKG_00B25F40_CHECK(result == &candidate_b);
  PKG_00B25F40_CHECK(probe_order.size() == 2);
  PKG_00B25F40_CHECK(probe_order[0] == &candidate_a);
  PKG_00B25F40_CHECK(probe_order[1] == &candidate_b);
}

void case_last_match(Resolver resolve) {
  reset_fixture();
  reported_identity = {7U, 8U, 9U};
  NounObject* result = resolve(receiver(), 9U);

  PKG_00B25F40_CHECK(result == &candidate_c);
  PKG_00B25F40_CHECK(probe_order.size() == 3);
}

void case_no_match_returns_null(Resolver resolve) {
  reset_fixture();
  reported_identity = {7U, 8U, 9U};
  NounObject* result = resolve(receiver(), 11U);

  PKG_00B25F40_CHECK(result == nullptr);
  PKG_00B25F40_CHECK(probe_order.size() == 3);
}

void case_empty_span_skips_probes(Resolver resolve) {
  reset_fixture();
  lookup_result = &empty_fixture;
  NounObject* result = resolve(receiver(), 7U);

  PKG_00B25F40_CHECK(result == nullptr);
  PKG_00B25F40_CHECK(probe_order.empty());
  expect_trace({TraceKind::kProjectionLookup});
}

void case_negative_span_skips_probes(Resolver resolve) {
  reset_fixture();
  lookup_result = &reversed_fixture;
  NounObject* result = resolve(receiver(), 7U);

  PKG_00B25F40_CHECK(result == nullptr);
  PKG_00B25F40_CHECK(probe_order.empty());
  expect_trace({TraceKind::kProjectionLookup});
}

void case_sentinel_identity_accepted(Resolver resolve) {
  reset_fixture();
  reported_identity = {7U, std::numeric_limits<std::uint32_t>::max(), 9U};
  NounObject* result =
      resolve(receiver(), std::numeric_limits<std::uint32_t>::max());

  PKG_00B25F40_CHECK(result == &candidate_b);
  PKG_00B25F40_CHECK(probe_order.size() == 2);
}

void case_high_bit_identity_is_not_sign_extended(Resolver resolve) {
  reset_fixture();
  reported_identity = {0x80000000U, 0x80000001U, 9U};
  NounObject* result = resolve(receiver(), 0x80000001U);

  PKG_00B25F40_CHECK(result == &candidate_b);
}

void case_low_byte_only_identity_is_not_a_match(Resolver resolve) {
  reset_fixture();
  reported_identity = {0x0000ffffU, 0x0000beefU, 9U};
  PKG_00B25F40_CHECK(resolve(receiver(), 0x0000beeeU) == nullptr);
}

// Two candidates whose probe results share a low byte but differ in the rest of
// the word. The body compares the full 32-bit word, so the match is the second
// candidate; a body that compared only the low byte would return the first.
void case_neighbours_sharing_a_low_byte(Resolver resolve) {
  reset_fixture();
  reported_identity = {0x000000abU, 0x0000ffabU, 9U};
  NounObject* result = resolve(receiver(), 0x0000ffabU);

  PKG_00B25F40_CHECK(result == &candidate_b);
  PKG_00B25F40_CHECK(probe_order.size() == 2);
}

// The loop head re-reads the container's begin word (`8b 07` MOV EAX,[EDI] at
// 0x00b25f76, inside the loop), so a probe that repoints the container mid-walk
// changes what the next iteration loads. A body that froze the pointer on the
// first read returns the original third candidate; the body as listed returns
// the candidate the replacement array points at.
void case_begin_is_reread_each_iteration(Resolver resolve) {
  reset_fixture();
  reported_identity = {11U, 12U, 13U};
  // The replacement array is as long as the count the body already computed, so
  // the third iteration reads inside it; the body never recomputes the count.
  // Its element at index 1 is candidate_c, where the original array holds
  // candidate_b, so the two readings of the begin word differ observably.
  NounObject* const tail[3] = {&candidate_c, &candidate_c, &candidate_c};
  replacement_begin = tail;
  repoint_on_probe = 1;
  mutable_vector = &vector_fixture;

  // The listed body probes twice: the first probe repoints the container, so
  // the second iteration loads candidate_c out of the replacement array and its
  // identity is the one asked for. A body that froze the begin word on the
  // first read walks the ORIGINAL array instead -- candidate_b then candidate_c
  // -- so it probes three times and reaches candidate_c only on the third.
  NounObject* result = resolve(receiver(), 13U);

  PKG_00B25F40_CHECK(probe_order.size() == 2);
  PKG_00B25F40_CHECK(probe_order[0] == &candidate_a);
  PKG_00B25F40_CHECK(probe_order[1] == &candidate_c);
  PKG_00B25F40_CHECK(result == &candidate_c);
  mutable_vector = nullptr;
}

void case_no_state_is_written(Resolver resolve) {
  reset_fixture();
  const std::uint32_t relationship_before = relationship_state;
  const std::uint32_t political_before = political_state;
  const std::uint32_t published_before = g_018c816a;

  PKG_00B25F40_CHECK(resolve(receiver(), 7U) == &candidate_a);
  PKG_00B25F40_CHECK(relationship_state == relationship_before);
  PKG_00B25F40_CHECK(political_state == political_before);
  PKG_00B25F40_CHECK(g_018c816a == published_before);
}

void run_battery(Resolver resolve) {
  case_propagation(resolve);
  case_first_match_returns_early(resolve);
  case_middle_match_probes_in_order(resolve);
  case_last_match(resolve);
  case_no_match_returns_null(resolve);
  case_empty_span_skips_probes(resolve);
  case_negative_span_skips_probes(resolve);
  case_sentinel_identity_accepted(resolve);
  case_high_bit_identity_is_not_sign_extended(resolve);
  case_low_byte_only_identity_is_not_a_match(resolve);
  case_neighbours_sharing_a_low_byte(resolve);
  case_begin_is_reread_each_iteration(resolve);
  case_no_state_is_written(resolve);
}

// -- in-file mutants --------------------------------------------------------
//
// Each is a wrong body written against the same fixture and judged by the same
// battery. A battery any of them passes is not measuring the body.

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_no_early_return(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  NounObject* last = nullptr;
  for (std::int32_t i = 0; i < count; ++i) {
    last = container_begin(vector)[i];
    if (candidate_table(last)->slot_4c(last) == ident) {
      continue;
    }
  }
  return last;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_low_byte_compare(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if ((candidate_table(candidate)->slot_4c(candidate) & 0xffU) ==
        (ident & 0xffU)) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL mutant_skips_last(NounProjection* recv,
                                                         std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2) - 1;
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL mutant_off_by_one(NounProjection* recv,
                                                         std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2) + 1;
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL mutant_wrong_shift(NounProjection* recv,
                                                          std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 3);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_unsigned_count(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  // Wrong in the same way the machine's `85 f6 / 7e 19` guard is not: a
  // reversed span must yield no probe at all, and an unsigned count does not.
  const std::int32_t count =
      static_cast<std::int32_t>(static_cast<std::uint32_t>(span) >> 2);
  if (count <= 0 && span < 0) {
    return nullptr;
  }
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL mutant_word_order(NounProjection* recv,
                                                         std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x018c816aU, 0x00b1e500U, 0x00b236c0U, 0x00d3d420U, 0x00b21080U);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_null_receiver(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      nullptr, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  (void)recv;
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_vtable_receiver(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    const NounIdentityProbe probe = candidate_table(candidate)->slot_4c;
    // Wrong: the machine sets ECX to the candidate, not to the table.
    const std::uint32_t observed =
        probe(reinterpret_cast<NounObject*>(candidate_table(candidate)));
    if (observed == ident) {
      return candidate;
    }
  }
  return nullptr;
}

// Returns the container's own element-array word instead of the candidate the
// probe matched. It is a pointer-shaped value of the right width that is not
// the object, so only a check on WHICH pointer comes back refutes it.
NounObject* PKG_00B25F40_TEST_THISCALL
mutant_returns_container(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      return reinterpret_cast<NounObject*>(
          reinterpret_cast<std::uintptr_t>(container_end(vector)));
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_first_read_cached(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  bool have_cached = false;
  std::uint32_t cached = 0;
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    const std::uint32_t observed =
        candidate_table(candidate)->slot_4c(candidate);
    if (!have_cached) {
      cached = observed;
      have_cached = true;
    }
    if (cached == ident) {
      return candidate;
    }
  }
  return nullptr;
}

NounObject* PKG_00B25F40_TEST_THISCALL
mutant_writes_state(NounProjection* recv, std::uint32_t ident) {
  NounProjectionVector* const vector = projection_lookup(
      recv, 0x00b21080U, 0x00d3d420U, 0x00b236c0U, 0x00b1e500U, 0x018c816aU);
  const std::intptr_t span =
      reinterpret_cast<std::intptr_t>(container_end(vector)) -
      reinterpret_cast<std::intptr_t>(container_begin(vector));
  const std::int32_t count = static_cast<std::int32_t>(span >> 2);
  for (std::int32_t i = 0; i < count; ++i) {
    NounObject* const candidate = container_begin(vector)[i];
    if (candidate_table(candidate)->slot_4c(candidate) == ident) {
      relationship_state = ident;
      political_state = ident;
      return candidate;
    }
  }
  return nullptr;
}

struct MutantCase {
  const char* name;
  Resolver body;
};

const MutantCase kMutants[] = {
    {"no early return", mutant_no_early_return},
    {"low byte compare", mutant_low_byte_compare},
    {"skips last element", mutant_skips_last},
    {"off by one", mutant_off_by_one},
    {"wrong shift", mutant_wrong_shift},
    {"unsigned count", mutant_unsigned_count},
    {"word order", mutant_word_order},
    {"null receiver", mutant_null_receiver},
    {"table as probe receiver", mutant_vtable_receiver},
    {"returns container", mutant_returns_container},
    {"first read cached", mutant_first_read_cached},
    {"writes state", mutant_writes_state},
};

// A body is refuted by raising SIGABRT. Each body runs in a forked child so the
// harness observes the refutation instead of dying with it.
int run_in_child(Resolver body) {
  std::fflush(nullptr);
  const pid_t child = fork();
  if (child < 0) {
    return -1;
  }
  if (child == 0) {
    run_battery(body);
    _exit(EXIT_SUCCESS);
  }
  int status = 0;
  if (waitpid(child, &status, 0) != child) {
    return -1;
  }
  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return -1;  // killed by a signal counts as refuted too
}

void expect_refuted(const MutantCase& mutant) {
  PKG_00B25F40_CHECK(run_in_child(mutant.body) != 0);
}

}

int main() {
  install_ports();
  PKG_00B25F40_CHECK(run_in_child(noun_identity_resolver_00b25f40) ==
                     EXIT_SUCCESS);
  for (const MutantCase& mutant : kMutants) {
    expect_refuted(mutant);
  }
  return 0;
}

#undef PKG_00B25F40_TEST_THISCALL
#undef PKG_00B25F40_CHECK
