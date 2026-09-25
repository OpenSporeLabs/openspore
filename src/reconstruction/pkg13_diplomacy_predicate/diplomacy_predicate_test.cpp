#include "diplomacy_predicate.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace {

using openspore::reconstruction::pkg13_diplomacy_predicate::
    pkg13_unresolved_00d01410;
using openspore::reconstruction::pkg13_diplomacy_predicate::
    pkg13_unresolved_00d01ab0;
using openspore::reconstruction::pkg13_diplomacy_predicate::
    RelationshipManager_IsAllied2_00d01ff0;

struct ObservedEmpire {
  unsigned char bytes[0x84];
  std::uint32_t political_id;
};

struct ObservedRelationshipEntry {
  float relationship_value;
  std::uint32_t flags;
  std::uint32_t opaque_state;
};

struct ObservedRelationshipManager {
  std::uint32_t opaque_word;
};

struct ObservedRelationshipMap {
  std::uint32_t opaque_word;
};

static_assert(offsetof(ObservedEmpire, political_id) == 0x84,
              "observed political identity offset");
static_assert(offsetof(ObservedRelationshipEntry, flags) == 0x04,
              "observed relationship flags offset");

ObservedRelationshipManager relationship_manager{0x12345678U};
ObservedEmpire empire_a{};
ObservedEmpire empire_b{};
ObservedRelationshipMap observed_relationship_map{};
ObservedRelationshipEntry relationship_entry{1.25F, 0U, 0U};
OpaqueRelationshipEntry* selected_entry =
    reinterpret_cast<OpaqueRelationshipEntry*>(&relationship_entry);
int current_empire_calls = 0;
int select_calls = 0;
int lookup_calls = 0;
OpaqueRelationshipManager* selected_receiver = nullptr;
std::uint32_t selected_key_a = 0U;
std::uint32_t selected_key_b = 0U;

}  // namespace

namespace openspore::reconstruction::pkg12_space {

struct Empire {
  unsigned char bytes[0x84];
  std::uint32_t political_id;
};

static_assert(offsetof(Empire, political_id) == 0x84,
              "PKG-12 dependency identity offset");

Empire* pkg12_space_01021300() {
  ++current_empire_calls;
  return reinterpret_cast<Empire*>(&empire_a);
}

}  // namespace openspore::reconstruction::pkg12_space

namespace openspore::reconstruction::pkg13_diplomacy_predicate {

extern "C" OpaqueRelationshipMap* PKG13_DIPLOMACY_THISCALL
pkg13_unresolved_00d01ab0(OpaqueRelationshipManager* receiver,
                          std::uint32_t key_a, std::uint32_t key_b) {
  ++select_calls;
  selected_receiver = receiver;
  selected_key_a = key_a;
  selected_key_b = key_b;
  return reinterpret_cast<OpaqueRelationshipMap*>(&observed_relationship_map);
}

extern "C" OpaqueRelationshipEntry* PKG13_DIPLOMACY_STDCALL
pkg13_unresolved_00d01410(OpaqueRelationshipMap* map, std::uint32_t key_a,
                          std::uint32_t key_b) {
  ++lookup_calls;
  assert(map ==
         reinterpret_cast<OpaqueRelationshipMap*>(&observed_relationship_map));
  assert(key_a == selected_key_a);
  assert(key_b == selected_key_b);
  return selected_entry;
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_predicate

void ResetObservation() {
  selected_entry =
      reinterpret_cast<OpaqueRelationshipEntry*>(&relationship_entry);
  current_empire_calls = 0;
  select_calls = 0;
  lookup_calls = 0;
  selected_receiver = nullptr;
  selected_key_a = 0U;
  selected_key_b = 0U;
  relationship_manager.opaque_word = 0x12345678U;
  empire_a.political_id = 10U;
  empire_b.political_id = 20U;
  relationship_entry = {1.25F, 2U, 0U};
}

void AssertSingleOrderedHelperPath(ObservedEmpire* first,
                                   ObservedEmpire* second,
                                   std::uint32_t expected_key_a,
                                   std::uint32_t expected_key_b) {
  const std::uint32_t manager_before = relationship_manager.opaque_word;
  const std::uint32_t first_before = first->political_id;
  const std::uint32_t second_before =
      second == nullptr ? 0U : second->political_id;
  const std::uint32_t entry_before = relationship_entry.flags;
  const std::uint8_t result = RelationshipManager_IsAllied2_00d01ff0(
      reinterpret_cast<OpaqueRelationshipManager*>(&relationship_manager),
      reinterpret_cast<OpaqueEmpire*>(first),
      reinterpret_cast<OpaqueEmpire*>(second));

  assert(result == 1U);
  assert(current_empire_calls == 1);
  assert(select_calls == 1);
  assert(lookup_calls == 1);
  assert(selected_receiver ==
         reinterpret_cast<OpaqueRelationshipManager*>(&relationship_manager));
  assert(selected_key_a == expected_key_a);
  assert(selected_key_b == expected_key_b);
  assert(relationship_manager.opaque_word == manager_before);
  assert(first->political_id == first_before);
  assert(second == nullptr || second->political_id == second_before);
  assert(relationship_entry.flags == entry_before);
}

void TestArgumentOrderingAndCurrentEmpireBranches() {
  ResetObservation();
  AssertSingleOrderedHelperPath(&empire_b, &empire_a, 20U, 10U);

  ResetObservation();
  AssertSingleOrderedHelperPath(&empire_a, &empire_b, 20U, 10U);

  ResetObservation();
  AssertSingleOrderedHelperPath(&empire_b, nullptr, 20U, 10U);

  ResetObservation();
  AssertSingleOrderedHelperPath(&empire_a, nullptr, 10U, 10U);
}

void TestAllianceFlagBits() {
  const std::uint32_t flags[] = {0U, 1U, 2U, 3U, 4U, 6U, 0x80000002U};
  for (const std::uint32_t value : flags) {
    ResetObservation();
    relationship_entry.flags = value;
    const std::uint8_t result = RelationshipManager_IsAllied2_00d01ff0(
        reinterpret_cast<OpaqueRelationshipManager*>(&relationship_manager),
        reinterpret_cast<OpaqueEmpire*>(&empire_a),
        reinterpret_cast<OpaqueEmpire*>(&empire_b));
    assert(result == static_cast<std::uint8_t>((value >> 1U) & 1U));
  }
}

void TestNullRelationshipEntry() {
  ResetObservation();
  selected_entry = nullptr;
  const std::uint8_t result = RelationshipManager_IsAllied2_00d01ff0(
      reinterpret_cast<OpaqueRelationshipManager*>(&relationship_manager),
      reinterpret_cast<OpaqueEmpire*>(&empire_a),
      reinterpret_cast<OpaqueEmpire*>(&empire_b));
  assert(result == 0U);
  assert(current_empire_calls == 1);
  assert(select_calls == 1);
  assert(lookup_calls == 1);
}

int main() {
  TestArgumentOrderingAndCurrentEmpireBranches();
  TestAllianceFlagBits();
  TestNullRelationshipEntry();
}
