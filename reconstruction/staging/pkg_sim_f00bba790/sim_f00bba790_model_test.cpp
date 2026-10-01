#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "sim_f00bba790.hpp"

namespace openspore::reconstruction::pkg_sim_f00bba790 {
namespace {

#if defined(_MSC_VER)
#define PKG_SIM_F00BBA790_TEST_THISCALL __thiscall
#else
#define PKG_SIM_F00BBA790_TEST_THISCALL __attribute__((thiscall))
#endif

using FlushSignature =
    OpaqueWordVector*(PKG_SIM_F00BBA790_TEST_THISCALL*)(OpaqueSimState*);

static_assert(
    std::is_same<decltype(&sim_00bba790_flush_pending_and_select_vector),
                 FlushSignature>::value,
    "00bba790 takes only the ECX receiver and returns a vector address in EAX");
static_assert(
    std::is_same<decltype(SimPorts::refresh_00bba640), StateRefresh>::value,
    "the 0x00bba640 port keeps the receiver-in-ECX, no-stack-argument shape");
static_assert(std::is_same<decltype(SimPorts::reserve_00e25bd0),
                           VectorReserve>::value,
              "the 0x00e25bd0 port keeps the two-word receiver-call shape");
static_assert(std::is_same<decltype(SimPorts::resize_00d01790),
                           VectorResize>::value,
              "the 0x00d01790 port keeps the one-word receiver-call shape");
static_assert(std::is_same<decltype(SimPorts::keep_pending_00b8d970),
                           NodeKeepPending>::value,
              "the 0x00b8d970 port keeps the element-receiver, byte-result shape");
static_assert(std::is_same<decltype(SimPorts::grow_insert_00aea5d0),
                           VectorGrowInsert>::value,
              "the 0x00aea5d0 port keeps the two-word receiver-call shape");
static_assert(sizeof(SimPorts) == 20,
              "the listing shows exactly five direct call targets");
static_assert(offsetof(OpaqueSimState, active_98) -
                      offsetof(OpaqueSimState, pending_84) ==
                  0x14,
              "the returned vectors sit 0x14 apart in the receiver");

std::vector<std::string> events;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

OpaqueSimNodeDispatchTable dispatch_table{};
OpaqueSimNode node0{};
OpaqueSimNode node1{};
OpaqueSimNode node2{};
OpaqueSimNode* grow_storage[8]{};

std::size_t refresh_calls = 0;
OpaqueSimState* refresh_state = nullptr;

std::size_t reserve_calls = 0;
OpaqueWordVector* reserve_vector = nullptr;
OpaqueSimNode** reserve_first = nullptr;
OpaqueSimNode** reserve_second = nullptr;

std::size_t resize_calls = 0;
OpaqueWordVector* resize_vector = nullptr;
TargetSignedWord resize_count = 0;

std::size_t keep_calls = 0;
OpaqueSimNode* keep_arg[8]{};
bool keep_result[8]{};

std::size_t grow_calls = 0;
OpaqueWordVector* grow_vector[8]{};
OpaqueSimNode** grow_end[8]{};
OpaqueSimNode** grow_slot[8]{};
bool grow_keep_full = false;

std::size_t notify_calls = 0;
OpaqueSimNode* notify_arg[8]{};

void PKG_SIM_F00BBA790_TEST_THISCALL refresh_hook(OpaqueSimState* state) {
  ++refresh_calls;
  refresh_state = state;
  events.push_back("refresh");
}

void PKG_SIM_F00BBA790_TEST_THISCALL
reserve_hook(OpaqueWordVector* vector, OpaqueSimNode** first,
             OpaqueSimNode** second) {
  ++reserve_calls;
  reserve_vector = vector;
  reserve_first = first;
  reserve_second = second;
  events.push_back("reserve");
}

void PKG_SIM_F00BBA790_TEST_THISCALL resize_hook(OpaqueWordVector* vector,
                                                 TargetSignedWord count) {
  ++resize_calls;
  resize_vector = vector;
  resize_count = count;
  events.push_back("resize");
}

std::uint8_t PKG_SIM_F00BBA790_TEST_THISCALL
keep_pending_hook(OpaqueSimNode* node) {
  check(keep_calls < 8u);
  keep_arg[keep_calls] = node;
  const bool result = keep_result[keep_calls];
  ++keep_calls;
  events.push_back("keep");
  return result ? 1u : 0u;
}

void PKG_SIM_F00BBA790_TEST_THISCALL
grow_insert_hook(OpaqueWordVector* vector, OpaqueSimNode** end,
                 OpaqueSimNode** slot) {
  check(grow_calls < 8u);
  check(end == vector->end);
  grow_vector[grow_calls] = vector;
  grow_end[grow_calls] = end;
  grow_slot[grow_calls] = slot;
  ++grow_calls;
  events.push_back("grow");
  if (grow_keep_full) {
    OpaqueSimNode** const single = grow_storage + (grow_calls - 1u);
    vector->begin = single;
    vector->end = single;
    vector->capacity = single + 1;
  } else if (vector->begin == nullptr) {
    vector->begin = grow_storage;
    vector->end = grow_storage;
    vector->capacity = grow_storage + 8;
  }
  *vector->end = *slot;
  ++vector->end;
}

void PKG_SIM_F00BBA790_TEST_THISCALL notify_hook(OpaqueSimNode* node) {
  check(notify_calls < 8u);
  notify_arg[notify_calls] = node;
  ++notify_calls;
  events.push_back("notify");
}

struct Fixture {
  OpaqueSimState state{};
  OpaqueSimNode* pending_storage[4]{};
  OpaqueSimNode* active_storage[4]{};

  void reset() {
    std::memset(this, 0, sizeof(*this));
    std::memset(&dispatch_table, 0, sizeof(dispatch_table));
    std::memset(&node0, 0, sizeof(node0));
    std::memset(&node1, 0, sizeof(node1));
    std::memset(&node2, 0, sizeof(node2));
    std::memset(grow_storage, 0, sizeof(grow_storage));
    events.clear();
    refresh_calls = 0;
    refresh_state = nullptr;
    reserve_calls = 0;
    reserve_vector = nullptr;
    reserve_first = nullptr;
    reserve_second = nullptr;
    resize_calls = 0;
    resize_vector = nullptr;
    resize_count = 0;
    keep_calls = 0;
    resize_count = 0;
    grow_calls = 0;
    notify_calls = 0;
    std::memset(keep_arg, 0, sizeof(keep_arg));
    std::memset(keep_result, 0, sizeof(keep_result));
    std::memset(grow_vector, 0, sizeof(grow_vector));
    std::memset(grow_end, 0, sizeof(grow_end));
    std::memset(grow_slot, 0, sizeof(grow_slot));
    std::memset(notify_arg, 0, sizeof(notify_arg));
    grow_keep_full = false;
    dispatch_table.notify_00 = notify_hook;
    node0.dispatch_table_00 = &dispatch_table;
    node1.dispatch_table_00 = &dispatch_table;
    node2.dispatch_table_00 = &dispatch_table;
    state.active_98.begin = active_storage;
    state.active_98.end = active_storage;
    state.active_98.capacity = active_storage + 4;
  }

  void bind_pending(std::size_t count) {
    state.pending_84.begin = pending_storage;
    state.pending_84.end = pending_storage + count;
    state.pending_84.capacity = pending_storage + 4;
  }
};

SimPorts observed_ports() {
  SimPorts ports = sim_f00bba790_ports();
  ports.refresh_00bba640 = refresh_hook;
  ports.reserve_00e25bd0 = reserve_hook;
  ports.resize_00d01790 = resize_hook;
  ports.keep_pending_00b8d970 = keep_pending_hook;
  ports.grow_insert_00aea5d0 = grow_insert_hook;
  return ports;
}

void test_clear_state_bit_returns_pending_without_ports() {
  Fixture fixture;
  fixture.reset();
  fixture.bind_pending(2u);
  fixture.state.state_5c = 0xbfu;
  sim_f00bba790_set_ports(observed_ports());

  OpaqueWordVector* const result =
      sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(result == &fixture.state.pending_84);
  check(refresh_calls == 1u);
  check(refresh_state == &fixture.state);
  check(reserve_calls == 0u);
  check(resize_calls == 0u);
  check(keep_calls == 0u);
  check(grow_calls == 0u);
  check(notify_calls == 0u);
  check(events.size() == 1u);
  check(events[0] == "refresh");
}

void test_set_state_bit_returns_active_for_empty_pending() {
  Fixture fixture;
  fixture.reset();
  fixture.bind_pending(0u);
  fixture.state.state_5c = 0x41u;
  sim_f00bba790_set_ports(observed_ports());

  OpaqueWordVector* const result =
      sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(result == &fixture.state.active_98);
  check(refresh_calls == 1u);
  check(reserve_calls == 1u);
  check(reserve_vector == &fixture.state.active_98);
  check(reserve_first == fixture.active_storage);
  check(reserve_second == fixture.active_storage);
  check(resize_calls == 1u);
  check(resize_vector == &fixture.state.active_98);
  check(resize_count == 0);
  check(keep_calls == 0u);
  check(grow_calls == 0u);
  check(notify_calls == 0u);
}

void test_elements_move_in_order_and_dispatch_once() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.pending_storage[1] = &node1;
  fixture.pending_storage[2] = &node2;
  fixture.bind_pending(3u);
  sim_f00bba790_set_ports(observed_ports());

  OpaqueWordVector* const result =
      sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(result == &fixture.state.active_98);
  check(resize_count == 3);
  check(keep_calls == 3u);
  check(keep_arg[0] == &node0);
  check(keep_arg[1] == &node1);
  check(keep_arg[2] == &node2);
  check(notify_calls == 3u);
  check(notify_arg[0] == &node0);
  check(notify_arg[1] == &node1);
  check(notify_arg[2] == &node2);
  check(fixture.state.active_98.end == fixture.active_storage + 3);
  check(fixture.active_storage[0] == &node0);
  check(fixture.active_storage[1] == &node1);
  check(fixture.active_storage[2] == &node2);
  check(grow_calls == 0u);
  check(fixture.state.pending_84.end == fixture.pending_storage + 3);
}

void test_keep_pending_nonzero_leaves_slot_in_place() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.pending_storage[1] = &node1;
  fixture.pending_storage[2] = &node2;
  fixture.bind_pending(3u);
  keep_result[1] = true;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(keep_calls == 3u);
  check(notify_calls == 2u);
  check(notify_arg[0] == &node0);
  check(notify_arg[1] == &node2);
  check(fixture.state.active_98.end == fixture.active_storage + 2);
  check(fixture.active_storage[0] == &node0);
  check(fixture.active_storage[1] == &node2);
  check(fixture.active_storage[2] == nullptr);
}

void test_full_active_vector_routes_through_grow_port() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.pending_storage[1] = &node1;
  fixture.bind_pending(2u);
  fixture.state.active_98.begin = nullptr;
  fixture.state.active_98.end = nullptr;
  fixture.state.active_98.capacity = nullptr;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(grow_calls == 1u);
  check(grow_vector[0] == &fixture.state.active_98);
  check(grow_end[0] == nullptr);
  check(grow_slot[0] == fixture.pending_storage);
  check(grow_storage[0] == &node0);
  check(grow_storage[1] == &node1);
  check(notify_calls == 1u);
  check(notify_arg[0] == &node1);
  check(fixture.state.active_98.end == grow_storage + 2);
}

void test_full_vector_re_enters_grow_for_every_element() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.pending_storage[1] = &node1;
  fixture.bind_pending(2u);
  fixture.state.active_98.begin = nullptr;
  fixture.state.active_98.end = nullptr;
  fixture.state.active_98.capacity = nullptr;
  grow_keep_full = true;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  grow_keep_full = false;
  check(grow_calls == 2u);
  check(grow_slot[0] == fixture.pending_storage);
  check(grow_slot[1] == fixture.pending_storage + 1);
  check(grow_storage[0] == &node0);
  check(grow_storage[1] == &node1);
  check(notify_calls == 0u);
  check(fixture.state.active_98.end == grow_storage + 2);
}

void test_null_active_end_advances_word_without_storing() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.bind_pending(1u);
  fixture.state.active_98.begin = nullptr;
  fixture.state.active_98.end = nullptr;
  fixture.state.active_98.capacity = fixture.active_storage;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(grow_calls == 0u);
  check(notify_calls == 0u);
  check(reinterpret_cast<std::uintptr_t>(fixture.state.active_98.end) == 4u);
  check(fixture.active_storage[0] == nullptr);
}

void test_null_element_is_stored_without_dispatch() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = nullptr;
  fixture.pending_storage[1] = &node1;
  fixture.bind_pending(2u);
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(keep_calls == 2u);
  check(keep_arg[0] == nullptr);
  check(notify_calls == 1u);
  check(notify_arg[0] == &node1);
  check(fixture.state.active_98.end == fixture.active_storage + 2);
  check(fixture.active_storage[0] == nullptr);
  check(fixture.active_storage[1] == &node1);
}

void test_reversed_pending_span_skips_the_loop() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.state.pending_84.begin = fixture.pending_storage + 3;
  fixture.state.pending_84.end = fixture.pending_storage + 1;
  fixture.state.pending_84.capacity = fixture.pending_storage + 4;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(resize_count == -2);
  check(keep_calls == 0u);
  check(grow_calls == 0u);
  check(notify_calls == 0u);
  check(fixture.state.active_98.end == fixture.active_storage);
}

void test_observed_call_order() {
  Fixture fixture;
  fixture.reset();
  fixture.state.state_5c = 0x40u;
  fixture.pending_storage[0] = &node0;
  fixture.bind_pending(1u);
  fixture.state.active_98.begin = nullptr;
  fixture.state.active_98.end = nullptr;
  fixture.state.active_98.capacity = nullptr;
  sim_f00bba790_set_ports(observed_ports());

  sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(events.size() == 5u);
  check(events[0] == "refresh");
  check(events[1] == "reserve");
  check(events[2] == "resize");
  check(events[3] == "keep");
  check(events[4] == "grow");
}

void test_port_set_matches_the_listing() {
  sim_f00bba790_reset_ports();
  const SimPorts ports = sim_f00bba790_ports();
  check(ports.refresh_00bba640 != nullptr);
  check(ports.reserve_00e25bd0 != nullptr);
  check(ports.resize_00d01790 != nullptr);
  check(ports.keep_pending_00b8d970 != nullptr);
  check(ports.grow_insert_00aea5d0 != nullptr);

  Fixture fixture;
  fixture.reset();
  sim_f00bba790_set_ports(observed_ports());
  const SimPorts bound = sim_f00bba790_ports();
  check(bound.refresh_00bba640 == refresh_hook);
  check(bound.reserve_00e25bd0 == reserve_hook);
  check(bound.resize_00d01790 == resize_hook);
  check(bound.keep_pending_00b8d970 == keep_pending_hook);
  check(bound.grow_insert_00aea5d0 == grow_insert_hook);
  sim_f00bba790_reset_ports();
}

void test_inert_ports_keep_the_fast_path_reachable() {
  Fixture fixture;
  fixture.reset();
  fixture.bind_pending(1u);
  sim_f00bba790_reset_ports();

  OpaqueWordVector* const result =
      sim_00bba790_flush_pending_and_select_vector(&fixture.state);

  check(result == &fixture.state.pending_84);
  check(refresh_calls == 0u);
  check(fixture.state.active_98.end == fixture.active_storage);
}

void test_signature_round_trips_through_a_function_pointer() {
  Fixture fixture;
  fixture.reset();
  fixture.bind_pending(0u);
  fixture.state.state_5c = 0x40u;
  sim_f00bba790_set_ports(observed_ports());
  FlushSignature flush = sim_00bba790_flush_pending_and_select_vector;

  OpaqueWordVector* const result = flush(&fixture.state);

  check(result == &fixture.state.active_98);
  check(refresh_calls == 1u);
  check(resize_count == 0);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_sim_f00bba790;
  test_clear_state_bit_returns_pending_without_ports();
  test_set_state_bit_returns_active_for_empty_pending();
  test_elements_move_in_order_and_dispatch_once();
  test_keep_pending_nonzero_leaves_slot_in_place();
  test_full_active_vector_routes_through_grow_port();
  test_full_vector_re_enters_grow_for_every_element();
  test_null_active_end_advances_word_without_storing();
  test_null_element_is_stored_without_dispatch();
  test_reversed_pending_span_skips_the_loop();
  test_observed_call_order();
  test_port_set_matches_the_listing();
  test_inert_ports_keep_the_fast_path_reachable();
  test_signature_round_trips_through_a_function_pointer();
  return 0;
}

#undef PKG_SIM_F00BBA790_TEST_THISCALL
