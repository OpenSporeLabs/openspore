#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <vector>

#include "tribe_civilization.hpp"

namespace {

using namespace openspore::reconstruction::pkg13_c2_tribe_civilization;

#if defined(_MSC_VER)
#define PKG13_C2_TEST_THISCALL __thiscall
#else
#define PKG13_C2_TEST_THISCALL __attribute__((thiscall))
#endif

#define PKG13_C2_TEST_CHECK(condition) \
  do {                                 \
    if (!(condition)) {                \
      __builtin_abort();               \
    }                                  \
  } while (false)

enum class TraceKind : std::uint8_t {
  kCurrentPlayer,
  kProjectionLookup,
  kIdentityProbe,
  kEvent,
  kRelease,
};

struct Trace {
  std::vector<TraceKind> entries;
};

Trace trace;
NounProjection* expected_receiver = nullptr;
NounProjectionVector* lookup_result = nullptr;
CurrentPlayerStateAccessWindow* current_result = nullptr;
std::uint32_t observed_create_word = 0;
std::uint32_t observed_clear_word = 0;
std::uint32_t observed_add_word = 0;
std::uint32_t observed_filter_word = 0;
std::uint32_t observed_projection_identity = 0;
std::uint32_t relationship_state = 0x13572468U;
std::uint32_t tribe_state = 0x24681357U;

NounObjectVtable vtable_7{};
NounObjectVtable vtable_max{};
NounObjectVtable vtable_9{};
NounObject object_7{};
NounObject object_max{};
NounObject object_9{};
NounObject* entries[3]{};
NounProjectionVector projection_vector{};
NounProjectionVector empty_vector{};
CurrentPlayerStateAccessWindow current_state{};

std::uint32_t PKG13_C2_TEST_THISCALL probe_7(NounObject* object) {
  PKG13_C2_TEST_CHECK(object == &object_7);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  return 7U;
}

std::uint32_t PKG13_C2_TEST_THISCALL probe_max(NounObject* object) {
  PKG13_C2_TEST_CHECK(object == &object_max);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  return std::numeric_limits<std::uint32_t>::max();
}

std::uint32_t PKG13_C2_TEST_THISCALL probe_9(NounObject* object) {
  PKG13_C2_TEST_CHECK(object == &object_9);
  trace.entries.push_back(TraceKind::kIdentityProbe);
  return 9U;
}

CurrentPlayerStateAccessWindow* current_player() {
  trace.entries.push_back(TraceKind::kCurrentPlayer);
  return current_result;
}

NounProjectionVector* PKG13_C2_TEST_THISCALL projection_lookup(
    NounProjection* receiver, std::uint32_t create_word,
    std::uint32_t clear_word, std::uint32_t add_word, std::uint32_t filter_word,
    std::uint32_t projection_identity) {
  PKG13_C2_TEST_CHECK(receiver == expected_receiver);
  PKG13_C2_TEST_CHECK(create_word == 0x00b21080U);
  PKG13_C2_TEST_CHECK(clear_word == 0x00d3d420U);
  PKG13_C2_TEST_CHECK(add_word == 0x00b236c0U);
  PKG13_C2_TEST_CHECK(filter_word == 0x00b1e500U);
  PKG13_C2_TEST_CHECK(projection_identity == 0x018c816aU);
  observed_create_word = create_word;
  observed_clear_word = clear_word;
  observed_add_word = add_word;
  observed_filter_word = filter_word;
  observed_projection_identity = projection_identity;
  trace.entries.push_back(TraceKind::kProjectionLookup);
  return lookup_result;
}

void install_ports() { g_native_ports = {current_player, projection_lookup}; }

void reset_fixture() {
  trace.entries.clear();
  expected_receiver = nullptr;
  lookup_result = &projection_vector;
  current_result = &current_state;
  observed_create_word = 0;
  observed_clear_word = 0;
  observed_add_word = 0;
  observed_filter_word = 0;
  observed_projection_identity = 0;
  current_state = {};
  current_state.identity = 0;
  projection_vector = {};
  empty_vector = {};
  entries[0] = &object_7;
  entries[1] = &object_max;
  entries[2] = &object_9;
  projection_vector.begin = entries;
  projection_vector.end = entries + 3;
  projection_vector.capacity = entries + 3;
  empty_vector.begin = entries;
  empty_vector.end = entries;
  empty_vector.capacity = entries + 3;
}

void expect_trace(std::initializer_list<TraceKind> expected) {
  PKG13_C2_TEST_CHECK(trace.entries.size() == expected.size());
  std::size_t index = 0;
  for (const TraceKind kind : expected) {
    PKG13_C2_TEST_CHECK(trace.entries[index] == kind);
    ++index;
  }
}

void test_bridge_propagates_current_identity() {
  reset_fixture();
  std::uint32_t receiver_word = 0;
  NounProjection* receiver = reinterpret_cast<NounProjection*>(&receiver_word);
  expected_receiver = receiver;
  current_result = &current_state;
  current_state.identity = std::numeric_limits<std::uint32_t>::max();

  NounObject* result = tribe_civilization_bridge_00b25fb0(receiver);

  PKG13_C2_TEST_CHECK(result == &object_max);
  PKG13_C2_TEST_CHECK(observed_create_word == 0x00b21080U);
  PKG13_C2_TEST_CHECK(observed_clear_word == 0x00d3d420U);
  PKG13_C2_TEST_CHECK(observed_add_word == 0x00b236c0U);
  PKG13_C2_TEST_CHECK(observed_filter_word == 0x00b1e500U);
  PKG13_C2_TEST_CHECK(observed_projection_identity == 0x018c816aU);
  expect_trace({TraceKind::kCurrentPlayer, TraceKind::kProjectionLookup,
                TraceKind::kIdentityProbe, TraceKind::kIdentityProbe});
}

void test_bridge_null_current_returns_receiver() {
  reset_fixture();
  std::uint32_t receiver_word = 0;
  NounProjection* receiver = reinterpret_cast<NounProjection*>(&receiver_word);
  expected_receiver = receiver;
  current_result = nullptr;

  NounObject* result = tribe_civilization_bridge_00b25fb0(receiver);

  PKG13_C2_TEST_CHECK(reinterpret_cast<void*>(result) ==
                      static_cast<void*>(receiver));
  expect_trace({TraceKind::kCurrentPlayer});
}

void test_resolver_invalid_sentinel_and_no_match() {
  reset_fixture();
  std::uint32_t receiver_word = 0;
  NounProjection* receiver = reinterpret_cast<NounProjection*>(&receiver_word);
  expected_receiver = receiver;

  NounObject* sentinel = tribe_civilization_resolver_00b25f40(
      receiver, std::numeric_limits<std::uint32_t>::max());
  PKG13_C2_TEST_CHECK(sentinel == &object_max);
  expect_trace({TraceKind::kProjectionLookup, TraceKind::kIdentityProbe,
                TraceKind::kIdentityProbe});

  reset_fixture();
  expected_receiver = receiver;
  PKG13_C2_TEST_CHECK(tribe_civilization_resolver_00b25f40(receiver, 99U) ==
                      nullptr);
  expect_trace({TraceKind::kProjectionLookup, TraceKind::kIdentityProbe,
                TraceKind::kIdentityProbe, TraceKind::kIdentityProbe});

  reset_fixture();
  expected_receiver = receiver;
  lookup_result = &empty_vector;
  PKG13_C2_TEST_CHECK(tribe_civilization_resolver_00b25f40(receiver, 7U) ==
                      nullptr);
  expect_trace({TraceKind::kProjectionLookup});
}

void test_state_relationship_and_event_order() {
  reset_fixture();
  std::uint32_t receiver_word = 0;
  NounProjection* receiver = reinterpret_cast<NounProjection*>(&receiver_word);
  expected_receiver = receiver;
  current_result = &current_state;
  current_state.identity = 7U;
  const std::uint32_t relationship_before = relationship_state;
  const std::uint32_t tribe_before = tribe_state;

  NounObject* result = tribe_civilization_bridge_00b25fb0(receiver);

  PKG13_C2_TEST_CHECK(result == &object_7);
  PKG13_C2_TEST_CHECK(relationship_state == relationship_before);
  PKG13_C2_TEST_CHECK(tribe_state == tribe_before);
  expect_trace({TraceKind::kCurrentPlayer, TraceKind::kProjectionLookup,
                TraceKind::kIdentityProbe});
  for (const TraceKind kind : trace.entries) {
    PKG13_C2_TEST_CHECK(kind != TraceKind::kEvent);
    PKG13_C2_TEST_CHECK(kind != TraceKind::kRelease);
  }
}

void test_negative_span_skips_probes() {
  reset_fixture();
  std::uint32_t receiver_word = 0;
  NounProjection* receiver = reinterpret_cast<NounProjection*>(&receiver_word);
  expected_receiver = receiver;
  projection_vector.begin = entries + 2;
  projection_vector.end = entries;
  projection_vector.capacity = entries + 3;

  PKG13_C2_TEST_CHECK(tribe_civilization_resolver_00b25f40(receiver, 7U) ==
                      nullptr);
  expect_trace({TraceKind::kProjectionLookup});
}

}

int main() {
  vtable_7.identity = probe_7;
  vtable_max.identity = probe_max;
  vtable_9.identity = probe_9;
  object_7.vtable = &vtable_7;
  object_max.vtable = &vtable_max;
  object_9.vtable = &vtable_9;
  install_ports();
  test_bridge_propagates_current_identity();
  test_bridge_null_current_returns_receiver();
  test_resolver_invalid_sentinel_and_no_match();
  test_state_relationship_and_event_order();
  test_negative_span_skips_probes();
}

#undef PKG13_C2_TEST_THISCALL
#undef PKG13_C2_TEST_CHECK
