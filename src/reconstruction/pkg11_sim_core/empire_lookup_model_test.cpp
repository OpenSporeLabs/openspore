#include <cassert>
#include <cstdint>

#include "empire_lookup.hpp"

namespace {

using openspore::reconstruction::pkg11_sim_core::EmpireMapEntry;
using openspore::reconstruction::pkg11_sim_core::OpaqueEmpire;
using openspore::reconstruction::pkg11_sim_core::OpaqueStarManager;
using openspore::reconstruction::pkg11_sim_core::
    Simulator_LookupEmpireByPoliticalId;

OpaqueEmpire* as_empire(std::uint8_t* storage) {
  return reinterpret_cast<OpaqueEmpire*>(storage);
}

void test_sentinel_rejection_does_not_dereference_manager() {
  assert(Simulator_LookupEmpireByPoliticalId(nullptr, 0xffffffffU) == nullptr);
}

void test_exact_hit_returns_payload_at_node_plus_0x14() {
  std::uint8_t empire_storage[4]{};
  OpaqueStarManager manager{};
  EmpireMapEntry entry{};
  entry.key_prefix.key = 20;
  entry.payload = as_empire(empire_storage);
  manager.mEmpires.anchor.parent = &entry.key_prefix.base;
  manager.mEmpires.size = 1;

  assert(Simulator_LookupEmpireByPoliticalId(&manager, 20) ==
         as_empire(empire_storage));
  assert(Simulator_LookupEmpireByPoliticalId(&manager, 15) == nullptr);
  assert(Simulator_LookupEmpireByPoliticalId(&manager, 25) == nullptr);
  assert(Simulator_LookupEmpireByPoliticalId(&manager, 30) == nullptr);
}

void test_exact_key_with_greater_right_child_returns_anchor() {
  std::uint8_t empire_storage[4]{};
  OpaqueStarManager manager{};
  EmpireMapEntry exact{};
  EmpireMapEntry greater{};

  exact.key_prefix.key = 20;
  exact.payload = as_empire(empire_storage);
  greater.key_prefix.key = 25;
  exact.key_prefix.base.right = &greater.key_prefix.base;
  manager.mEmpires.anchor.parent = &exact.key_prefix.base;
  manager.mEmpires.size = 2;

  assert(Simulator_LookupEmpireByPoliticalId(&manager, 20) == nullptr);
}

void test_end_and_null_payload_paths() {
  OpaqueStarManager manager{};
  assert(Simulator_LookupEmpireByPoliticalId(&manager, 7) == nullptr);

  EmpireMapEntry entry{};
  entry.key_prefix.key = 7;
  entry.payload = nullptr;
  manager.mEmpires.anchor.parent = &entry.key_prefix.base;
  manager.mEmpires.size = 1;
  assert(Simulator_LookupEmpireByPoliticalId(&manager, 7) == nullptr);
}

}

int main() {
  test_sentinel_rejection_does_not_dereference_manager();
  test_exact_hit_returns_payload_at_node_plus_0x14();
  test_exact_key_with_greater_right_child_returns_anchor();
  test_end_and_null_payload_paths();
}
