#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "dogfood_008db310.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {
namespace {

int failures = 0;
unsigned int dispatch_calls = 0;

struct ObservedCall {
  OpaqueWriteCarrier* receiver;
  void* destination;
  OpaqueWord destination_size;
};

ObservedCall observed{};

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void* address_of(OpaqueWord value) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(value));
}

OpaqueWord raw_of(void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

bool PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
dispatch_014368bc(OpaqueWriteCarrier* receiver, void* destination,
                  OpaqueWord destination_size) {
  observed.receiver = receiver;
  observed.destination = destination;
  observed.destination_size = destination_size;
  ++dispatch_calls;
  return pf_index_write_bounds_008db310(receiver, destination,
                                        destination_size);
}

const OpaqueWord kSlotCount = 4u;
const OpaqueWord kEndSlot = 3u;

struct OpaqueFixture {
  OpaqueWriteCarrier carrier{};
  OpaqueItemNode nodes[4]{};
  OpaqueItemNode* slots[kSlotCount]{};
  OpaqueItemNode* end_node = nullptr;
};

void initialize(OpaqueFixture& fixture) {
  dispatch_calls = 0u;
  observed = ObservedCall{};
  g_pf_index_write_008db310_ports = OpaquePorts{};

  for (OpaqueWord i = 0u; i < 4u; ++i) {
    fixture.nodes[i] = OpaqueItemNode{};
    fixture.nodes[i].record_begin_0c = 0u;
    fixture.nodes[i].record_size_10 = 0u;
    fixture.nodes[i].next_1c = nullptr;
  }
  for (OpaqueWord i = 0u; i < kSlotCount; ++i) {
    fixture.slots[i] = nullptr;
  }
  fixture.end_node = &fixture.nodes[3];
  fixture.slots[kEndSlot] = fixture.end_node;

  fixture.carrier = OpaqueWriteCarrier{};
  fixture.carrier.slots_2c = fixture.slots;
  fixture.carrier.end_slot_30 = kEndSlot;
}

void place(OpaqueFixture& fixture, OpaqueWord slot, OpaqueWord node_index,
           OpaqueWord record_begin, OpaqueWord record_size) {
  fixture.slots[slot] = &fixture.nodes[node_index];
  fixture.nodes[node_index].record_begin_0c = record_begin;
  fixture.nodes[node_index].record_size_10 = record_size;
  fixture.nodes[node_index].next_1c = nullptr;
}

void test_zero_extent_returns_true_before_the_map_is_read() {
  OpaqueFixture fixture{};
  initialize(fixture);
  fixture.carrier.slots_2c = nullptr;
  fixture.carrier.end_slot_30 = 0xffffffffu;

  const bool result =
      pf_index_write_bounds_008db310(&fixture.carrier, &fixture, 0u);

  check(result);
  check(dispatch_calls == 0u);
  check(fixture.carrier.slots_2c == nullptr);
  check(fixture.carrier.end_slot_30 == 0xffffffffu);
}

void test_overlapping_record_returns_false() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2000u, 0x40u);
  fixture.nodes[0].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_adjacent_records_are_not_overlaps() {
  OpaqueFixture after{};
  initialize(after);
  place(after, 0u, 0u, 0x2020u, 0x10u);
  after.nodes[0].next_1c = after.end_node;

  const bool after_result = pf_index_write_bounds_008db310(
      &after.carrier, address_of(0x2010u), 0x10u);
  check(after_result);

  OpaqueFixture before{};
  initialize(before);
  place(before, 0u, 0u, 0x2000u, 0x10u);
  before.nodes[0].next_1c = before.end_node;

  const bool before_result = pf_index_write_bounds_008db310(
      &before.carrier, address_of(0x2010u), 0x10u);
  check(before_result);
}

void test_zero_sized_record_is_never_compared() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2014u, 0u);
  fixture.nodes[0].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_range_compare_is_unsigned_across_wrap() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0u, 0x80000010u);
  fixture.nodes[0].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x1000u), 0x10u);

  check(!result);
}

void test_chain_interior_node_is_examined() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  fixture.nodes[1].record_begin_0c = 0x2010u;
  fixture.nodes[1].record_size_10 = 0x10u;
  fixture.nodes[1].next_1c = fixture.end_node;
  fixture.nodes[0].next_1c = &fixture.nodes[1];

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_end_node_terminates_before_any_range_test() {
  OpaqueFixture fixture{};
  initialize(fixture);
  fixture.slots[0] = fixture.end_node;
  place(fixture, 1u, 0u, 0x2000u, 0x40u);

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_null_slots_are_skipped_before_the_first_test() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 2u, 0u, 0x2000u, 0x40u);
  fixture.nodes[0].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_chain_end_resumes_at_the_next_slot() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  place(fixture, 2u, 1u, 0x2010u, 0x10u);
  fixture.nodes[1].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(!result);
}

void test_whole_index_without_overlap_returns_true() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x1000u, 0x10u);
  fixture.nodes[0].next_1c = &fixture.nodes[1];
  place(fixture, 2u, 1u, 0x9000u, 0x10u);
  fixture.nodes[1].next_1c = fixture.end_node;

  const bool result = pf_index_write_bounds_008db310(
      &fixture.carrier, address_of(0x2010u), 0x10u);

  check(result);
}

void test_dispatch_port_is_closed_by_default() {
  OpaqueFixture fixture{};
  initialize(fixture);

  check(g_pf_index_write_008db310_ports.dispatch_014368bc == nullptr);
  check(dispatch_calls == 0u);
  check(sizeof(OpaquePorts) == 4);
}

void test_configured_dispatch_receives_the_two_stack_words() {
  OpaqueFixture fixture{};
  initialize(fixture);
  place(fixture, 0u, 0u, 0x2000u, 0x40u);
  fixture.nodes[0].next_1c = fixture.end_node;
  g_pf_index_write_008db310_ports.dispatch_014368bc = &dispatch_014368bc;

  void* const destination = address_of(0x2010u);
  const bool result = g_pf_index_write_008db310_ports.dispatch_014368bc(
      &fixture.carrier, destination, 0x10u);

  check(!result);
  check(dispatch_calls == 1u);
  check(observed.receiver == &fixture.carrier);
  check(observed.destination == destination);
  check(observed.destination_size == 0x10u);
  check(raw_of(observed.destination) == 0x2010u);
  check(observed.receiver != observed.destination);
}

void test_end_slot_word_selects_the_terminator() {
  OpaqueFixture early{};
  initialize(early);
  place(early, 0u, 0u, 0x1000u, 0x10u);
  place(early, 2u, 2u, 0x2010u, 0x10u);
  early.nodes[0].next_1c = &early.nodes[1];
  early.nodes[1].next_1c = &early.nodes[2];
  early.nodes[2].next_1c = nullptr;
  early.carrier.end_slot_30 = 2u;

  const bool early_result = pf_index_write_bounds_008db310(
      &early.carrier, address_of(0x2010u), 0x10u);
  check(early_result);

  OpaqueFixture late{};
  initialize(late);
  place(late, 0u, 0u, 0x1000u, 0x10u);
  place(late, 2u, 2u, 0x2010u, 0x10u);
  late.nodes[0].next_1c = &late.nodes[1];
  late.nodes[1].next_1c = &late.nodes[2];
  late.nodes[2].next_1c = nullptr;
  late.carrier.end_slot_30 = kEndSlot;

  const bool late_result =
      pf_index_write_bounds_008db310(&late.carrier, address_of(0x2010u), 0x10u);
  check(!late_result);
}

void test_carrier_and_node_layout_is_proved() {
  check(sizeof(OpaqueWriteCarrier) == 0x4c);
  check(offsetof(OpaqueWriteCarrier, slots_2c) == 0x2c);
  check(offsetof(OpaqueWriteCarrier, end_slot_30) == 0x30);
  check(sizeof(OpaqueItemNode) == 0x20);
  check(offsetof(OpaqueItemNode, record_begin_0c) == 0x0c);
  check(offsetof(OpaqueItemNode, record_size_10) == 0x10);
  check(offsetof(OpaqueItemNode, next_1c) == 0x1c);
}

void test_modeled_signatures() {
  using EntrySignature = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL*)(
      OpaqueWriteCarrier*, void*, OpaqueWord);
  using DispatchSignature = bool(PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL*)(
      OpaqueWriteCarrier*, void*, OpaqueWord);

  static_assert(std::is_same<decltype(&pf_index_write_bounds_008db310),
                             EntrySignature>::value,
                "entry is thiscall with the carrier plus two stack words");
  static_assert(std::is_same<DispatchSlot014368bc, DispatchSignature>::value,
                "dispatch port carries the same three words");
  static_assert(sizeof(decltype(&pf_index_write_bounds_008db310)) == 4,
                "entry width");
  static_assert(
      std::is_same<decltype(&dispatch_014368bc), DispatchSignature>::value,
      "fake is calling-convention matched to the dispatch port");
}

int run_model() {
  failures = 0;
  test_zero_extent_returns_true_before_the_map_is_read();
  test_overlapping_record_returns_false();
  test_adjacent_records_are_not_overlaps();
  test_zero_sized_record_is_never_compared();
  test_range_compare_is_unsigned_across_wrap();
  test_chain_interior_node_is_examined();
  test_end_node_terminates_before_any_range_test();
  test_null_slots_are_skipped_before_the_first_test();
  test_chain_end_resumes_at_the_next_slot();
  test_whole_index_without_overlap_returns_true();
  test_end_slot_word_selects_the_terminator();
  test_dispatch_port_is_closed_by_default();
  test_configured_dispatch_receives_the_two_stack_words();
  test_carrier_and_node_layout_is_proved();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_orchestrate_dogfood_008db310::
      run_model();
}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
