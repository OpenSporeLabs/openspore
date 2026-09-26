#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "sim_tool_wave9.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_tool_wave9 {
namespace {

using ExpectedDeleteAbi = void(TEST_THISCALL*)(OpaqueDeleteOwner*);
using ExpectedPositionAbi = void(TEST_THISCALL*)(OpaqueAoEState*,
                                                 OpaqueVector*);
using ExpectedSelectionAbi =
    OpaqueSelectionState*(TEST_THISCALL*)(OpaqueSelectionState*, TargetWord);
using ExpectedBeamAbi = bool(TEST_CDECL*)(OpaqueToolState*);
using ExpectedSpecialAbi = bool(TEST_THISCALL*)(OpaqueSpecialState*,
                                                OpaqueSelectionContext*,
                                                TargetWord, TargetWord);

static_assert(
    std::is_same<decltype(&target_00b72370), ExpectedDeleteAbi>::value,
    "delete target ABI");
static_assert(
    std::is_same<decltype(&target_01052f90), ExpectedPositionAbi>::value,
    "position target ABI");
static_assert(
    std::is_same<decltype(&target_01053790), ExpectedSelectionAbi>::value,
    "selection target ABI");
static_assert(std::is_same<decltype(&target_01053db0), ExpectedBeamAbi>::value,
              "beam target ABI");
static_assert(
    std::is_same<decltype(&target_01054080), ExpectedSpecialAbi>::value,
    "special target ABI");
static_assert(sizeof(decltype(&target_00b72370)) == 4,
              "delete target pointer width");
static_assert(sizeof(decltype(&target_01052f90)) == 4,
              "position target pointer width");
static_assert(sizeof(decltype(&target_01053790)) == 4,
              "selection target pointer width");
static_assert(sizeof(decltype(&target_01053db0)) == 4,
              "beam target pointer width");
static_assert(sizeof(decltype(&target_01054080)) == 4,
              "special target pointer width");

int failures = 0;
std::vector<std::string> events;
std::vector<TargetWord> notified_values;

OpaquePooledObjectVTable pooled_vtable{};
OpaquePooledObject pooled{};
OpaquePooledObject* pool_result = nullptr;
OpaqueOwnerLink* notify_link = nullptr;
int notify_count = 0;

OpaqueRefVTable ref_vtable{};
OpaqueBeamTarget beam_target{};
OpaqueToolState tool_state{};
OpaqueRelationshipState relationship{};
int release_count = 0;

OpaqueSelectionState selection_state{};
OpaqueSelectionState* transition_state = nullptr;
int transition_count = 0;

OpaquePositionVTable position_vtable{};
OpaquePositionSource position_source{};
OpaqueVector queried_vector{};
OpaquePositionSource* query_source = nullptr;
OpaqueVector* query_scratch = nullptr;
TargetWord query_mode = 0;
int query_count = 0;

OpaqueSpecialState special_state{};
OpaqueSelectionContext selection_context{};
OpaqueSpecialState* special_receiver = nullptr;
OpaqueSelectionContext* special_context = nullptr;
TargetWord special_second = 0;
TargetWord special_third = 0;
std::uint8_t special_result = 0;
int special_count = 0;

OpaqueRelationshipState* drained_relationship = nullptr;
int drain_count = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* value) { events.emplace_back(value); }

OpaquePooledObject* TEST_CDECL pool_root() {
  record("pool_root");
  return pool_result;
}

void TEST_THISCALL pooled_notify(OpaquePooledObject* object,
                                 OpaqueOwnerLink* link, TargetWord value) {
  record("notify");
  check(object == &pooled);
  notify_link = link;
  notified_values.push_back(value);
  ++notify_count;
}

void TEST_CDECL selection_transition(OpaqueSelectionState* state) {
  record("selection_transition");
  transition_state = state;
  ++transition_count;
}

std::uint8_t TEST_THISCALL special_select(OpaqueSpecialState* state,
                                          OpaqueSelectionContext* context,
                                          TargetWord second, TargetWord third) {
  record("special_select");
  special_receiver = state;
  special_context = context;
  special_second = second;
  special_third = third;
  ++special_count;
  return special_result;
}

void TEST_THISCALL event_drain(OpaqueRelationshipState* state) {
  record("event_drain");
  drained_relationship = state;
  check(state->state_55a0 == 0U);
  ++drain_count;
}

void TEST_THISCALL release_target(OpaqueBeamTarget* target) {
  record("release");
  check(target == &beam_target);
  check(target->state_155 == 1u);
  check(tool_state.target_124 == nullptr);
  ++release_count;
}

const OpaqueVector* TEST_THISCALL query_position(OpaquePositionSource* source,
                                                 OpaqueVector* scratch,
                                                 TargetWord mode) {
  record("query");
  query_source = source;
  query_scratch = scratch;
  query_mode = mode;
  ++query_count;
  return &queried_vector;
}

NativePorts make_ports() {
  NativePorts ports{};
  ports.pool_root_00883860 = pool_root;
  ports.selection_transition_00f47380 = selection_transition;
  ports.special_select_01053980 = special_select;
  ports.event_drain_00b77aa0 = event_drain;
  return ports;
}

void reset() {
  events.clear();
  notified_values.clear();
  pooled_vtable = OpaquePooledObjectVTable{};
  pooled_vtable.notify_24 = pooled_notify;
  pooled = OpaquePooledObject{&pooled_vtable};
  pool_result = &pooled;
  notify_link = nullptr;
  notify_count = 0;
  ref_vtable = OpaqueRefVTable{};
  ref_vtable.release_04 = release_target;
  beam_target = OpaqueBeamTarget{};
  beam_target.vtable_00 = &ref_vtable;
  tool_state = OpaqueToolState{};
  relationship = OpaqueRelationshipState{};
  release_count = 0;
  selection_state = OpaqueSelectionState{};
  transition_state = nullptr;
  transition_count = 0;
  position_vtable = OpaquePositionVTable{};
  position_vtable.query_3c = query_position;
  position_source = OpaquePositionSource{&position_vtable};
  queried_vector = OpaqueVector{0x01020304u, 0x11121314u, 0x21222324u};
  query_source = nullptr;
  query_scratch = nullptr;
  query_mode = 0xffffffffu;
  query_count = 0;
  special_state = OpaqueSpecialState{};
  selection_context = OpaqueSelectionContext{};
  special_receiver = nullptr;
  special_context = nullptr;
  special_second = 0;
  special_third = 0;
  special_result = 0;
  special_count = 0;
  drained_relationship = nullptr;
  drain_count = 0;
  g_sim_tool_wave9_ports = make_ports();
  g_position_source_0167eac4 = &position_source;
  g_relationship_state_0167eb14 = &relationship;
}

void test_delete_publication_and_callbacks() {
  reset();
  alignas(4) std::uint8_t published_storage[0x38]{};
  auto* const published_receiver =
      reinterpret_cast<OpaqueDeleteOwner*>(published_storage + 4);
  auto* const published_link = reinterpret_cast<OpaqueOwnerLink*>(
      reinterpret_cast<std::uint8_t*>(published_receiver) - 4);
  target_00b72370(published_receiver);
  check(events.size() == 9);
  check(events[0] == "pool_root");
  check(published_receiver->published_20 == &pooled);
  check(published_receiver->link_24 == published_link);
  check(published_receiver->link_24 != nullptr);
  check(published_receiver->identifiers_28 == kDeleteIdentifierValues);
  check(published_receiver->identifier_count_2c == 8u);
  check(published_receiver->cursor_30 == 0u);
  check(notify_count == 8);
  check(notify_link == published_link);
  check(notified_values.size() == kDeleteIdentifierCount);
  for (TargetWord index = 0U; index < kDeleteIdentifierCount; ++index) {
    check(notified_values[index] == kDeleteIdentifierValues[index]);
  }

  reset();
  pool_result = nullptr;
  alignas(4) std::uint8_t empty_storage[0x38]{};
  auto* const empty_receiver =
      reinterpret_cast<OpaqueDeleteOwner*>(empty_storage + 4);
  auto* const empty_link = reinterpret_cast<OpaqueOwnerLink*>(
      reinterpret_cast<std::uint8_t*>(empty_receiver) - 4);
  target_00b72370(empty_receiver);
  check(events.size() == 1);
  check(empty_receiver->published_20 == nullptr);
  check(empty_receiver->link_24 == empty_link);
  check(empty_receiver->link_24 != nullptr);
  check(empty_receiver->identifier_count_2c == 8u);
  check(notify_count == 0);
}

void test_position_publication() {
  reset();
  OpaqueAoEState receiver{};
  receiver.opaque[0] = 0xa5u;
  OpaqueVector output{0xdeadbeefu, 0xcafebabeu, 0x80000001u};
  target_01052f90(&receiver, &output);
  check(events.size() == 1);
  check(events[0] == "query");
  check(query_source == &position_source);
  check(query_scratch != nullptr);
  check(query_mode == 0u);
  check(query_count == 1);
  check(output.x == queried_vector.x);
  check(output.y == queried_vector.y);
  check(output.z == queried_vector.z);
  check(receiver.opaque[0] == 0xa5u);
}

void test_selection_transition() {
  reset();
  selection_state.vtable_00 = reinterpret_cast<const void*>(0x12345678u);
  OpaqueSelectionState* result = target_01053790(&selection_state, 0u);
  check(result == &selection_state);
  check(selection_state.vtable_00 ==
        reinterpret_cast<const void*>(kSelectionTable));
  check(transition_count == 0);

  result = target_01053790(&selection_state, 0x00000102u);
  check(result == &selection_state);
  check(transition_count == 0);

  result = target_01053790(&selection_state, 0x00000101u);
  check(result == &selection_state);
  check(transition_count == 1);
  check(transition_state == &selection_state);
  check(selection_state.vtable_00 ==
        reinterpret_cast<const void*>(kSelectionTable));
}

void test_beam_release_and_event_writes() {
  reset();
  check(target_01053db0(&tool_state));
  check(events.size() == 0);
  check(release_count == 0);
  check(drain_count == 0);

  reset();
  tool_state.target_124 = &beam_target;
  tool_state.state_174 = 0x10u;
  check(target_01053db0(&tool_state));
  check(events.size() == 2);
  check(events[0] == "release");
  check(events[1] == "event_drain");
  check(beam_target.state_155 == 1u);
  check(tool_state.target_124 == nullptr);
  check(release_count == 1);
  check(drained_relationship == &relationship);
  check(drain_count == 1);
  check(relationship.state_20 == 0xfffffffbu);
  check(relationship.state_55a0 == 0u);

  reset();
  tool_state.state_174 = 0x10u;
  relationship.state_20 = 0x12345678u;
  relationship.state_55a0 = 0x9abcdef0u;
  check(target_01053db0(&tool_state));
  check(drain_count == 1);
  check(relationship.state_20 == 0x12345674u);
  check(relationship.state_55a0 == 0u);
}

void test_beam_gate_width() {
  const TargetWord states[] = {0u, 0x0fu, 0x10u, 0x1fu, 0x20u, 0xffffffffu};
  const bool expected[] = {false, false, true, true, false, true};
  for (std::size_t index = 0; index < 6; ++index) {
    reset();
    tool_state.state_174 = states[index];
    check(target_01053db0(&tool_state));
    check(release_count == 0);
    check(drain_count == (expected[index] ? 1 : 0));
  }
}

void test_special_sentinel_and_forwarding() {
  reset();
  special_result = 0u;
  check(!target_01054080(&special_state, &selection_context, 0x12345678u,
                         0x80000001u));
  check(events.size() == 1);
  check(events[0] == "special_select");
  check(special_receiver == &special_state);
  check(special_context == &selection_context);
  check(special_second == 0x12345678u);
  check(special_third == 0x80000001u);
  check(special_count == 1);

  reset();
  special_result = 0x80u;
  check(target_01054080(&special_state, &selection_context, 0u, 0u));
  check(special_count == 1);

  for (TargetWord sentinel : {TargetWord{1}, TargetWord{0xffffffff}}) {
    reset();
    selection_context.state_12c = sentinel;
    check(target_01054080(&special_state, &selection_context, 0xaaaaaaaa,
                          0x55555555u));
    check(events.empty());
    check(special_count == 0);
  }
}

void test_constants_and_bits() {
  static_assert(kDeleteIdentifierCount == 8, "identifier count");
  static_assert(kSelectionTable == 0x01403934u, "selection table address");
  check(sizeof(kDeleteIdentifierValues) ==
        kDeleteIdentifierCount * sizeof(TargetWord));
  check(kDeleteIdentifierValues[0] == 0x025630b7u);
  check(kDeleteIdentifierValues[7] == 0x0182c582u);
  check((kSelectionTable & 3u) == 0u);
}

int run_tests() {
  test_constants_and_bits();
  test_delete_publication_and_callbacks();
  test_position_publication();
  test_selection_transition();
  test_beam_release_and_event_writes();
  test_beam_gate_width();
  test_special_sentinel_and_forwarding();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_sim_tool_wave9::run_tests();
}

#undef TEST_THISCALL
#undef TEST_CDECL
