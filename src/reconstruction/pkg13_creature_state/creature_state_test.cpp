#include "creature_state.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <limits>

namespace {

using openspore::reconstruction::pkg13_creature_state::
    Simulator_cCreatureGameData_GetAbilityMode;
using openspore::reconstruction::pkg13_creature_state::
    Simulator_cCreatureGameData_GetEvolutionPoints;
using openspore::reconstruction::pkg13_creature_state::
    Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel;
using openspore::reconstruction::pkg13_creature_state::
    TribeState_test_purchased_tool_bit_00c8ec00;

struct ObservedNounManager {
  unsigned char bytes[0x58];
};

using BrainLevelGetter =
    std::int32_t(PKG13_THISCALL*)(OpaqueCreatureGameDataObject*);

struct ObservedBrainLevelVirtualTable {
  BrainLevelGetter slots[0xd8 / 4 + 1];
};

struct ObservedCreatureGameDataObject {
  ObservedBrainLevelVirtualTable* vtable;
};

struct ObservedTribeState {
  std::uint32_t leading_word;
  unsigned char bytes[0x19d4];
  std::uint32_t purchased_tools_mask;
};

static_assert(sizeof(BrainLevelGetter) == 4,
              "PKG-13 target function pointers are 32-bit");
static_assert(offsetof(ObservedTribeState, purchased_tools_mask) == 0x19d8,
              "observed purchased-tools mask offset");
static_assert(sizeof(ObservedTribeState) == 0x19dc, "observed consumed extent");

ObservedNounManager noun_manager{};
ObservedCreatureGameDataObject creature_game_data{};
ObservedBrainLevelVirtualTable brain_level_vtable{};
std::int32_t current_brain_level = 0;
int brain_level_calls = 0;

std::int32_t PKG13_THISCALL
GetCurrentBrainLevel(OpaqueCreatureGameDataObject* receiver) {
  assert(receiver ==
         reinterpret_cast<OpaqueCreatureGameDataObject*>(&creature_game_data));
  ++brain_level_calls;
  return current_brain_level;
}

extern "C" OpaqueNounManager* FUN_00b3d300() {
  return reinterpret_cast<OpaqueNounManager*>(&noun_manager);
}

extern "C" OpaqueCreatureGameDataObject* FUN_00b1fdb0(
    OpaqueNounManager* receiver) {
  assert(receiver == reinterpret_cast<OpaqueNounManager*>(&noun_manager));
  std::uintptr_t object;
  std::memcpy(&object, noun_manager.bytes + 0x54, sizeof(object));
  return reinterpret_cast<OpaqueCreatureGameDataObject*>(object);
}

void InstallCreatureGameDataObject() {
  const std::uintptr_t manager_address =
      reinterpret_cast<std::uintptr_t>(&noun_manager);
  const std::uintptr_t object_address =
      reinterpret_cast<std::uintptr_t>(&creature_game_data);
  std::memcpy(noun_manager.bytes + 0x54, &object_address,
              sizeof(object_address));
  std::memset(&brain_level_vtable, 0, sizeof(brain_level_vtable));
  brain_level_vtable.slots[0xd8 / 4] = &GetCurrentBrainLevel;
  creature_game_data.vtable = &brain_level_vtable;
  assert(manager_address != 0U);
}

void TestEvolutionPointsGlobalRead() {
  const float values[] = {0.0F, -0.0F, 1.0F, -1234.5F, 10000.0F, 0.1F};
  for (const float value : values) {
    DAT_0169e398 = value;
    std::uint32_t expected_bits;
    std::memcpy(&expected_bits, &value, sizeof(expected_bits));
    std::uint32_t actual_bits;
    const float actual = Simulator_cCreatureGameData_GetEvolutionPoints();
    std::memcpy(&actual_bits, &actual, sizeof(actual_bits));
    assert(actual_bits == expected_bits);
  }
}

void TestAbilityModeRawWord() {
  const std::uint32_t values[] = {0U, 1U, 2U, 3U, 0x7fffffffU, 0xffffffffU};
  for (const std::uint32_t value : values) {
    DAT_0169e394 = value;
    assert(Simulator_cCreatureGameData_GetAbilityMode() == value);
  }
}

void TestBrainLevelThresholds() {
  DAT_01582e38 = 1000.0F;
  DAT_01582e3c = 2000.0F;
  DAT_01582e40 = 3000.0F;
  DAT_01582e44 = 5000.0F;

  assert(Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(0) ==
         1000.0F);
  assert(Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(1) ==
         2000.0F);
  assert(Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(2) ==
         3000.0F);
  assert(Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(3) ==
         5000.0F);

  brain_level_calls = 0;
  for (const std::int32_t level :
       {-2, 4, 0x7fffffff, std::numeric_limits<std::int32_t>::min()}) {
    current_brain_level = level;
    assert(Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(level) ==
           0.0F);
    assert(brain_level_calls == 0);
  }
}

void TestCurrentBrainLevelVirtualPath() {
  InstallCreatureGameDataObject();
  for (const std::int32_t level : {-1, 0, 1, 2, 3}) {
    current_brain_level = level;
    brain_level_calls = 0;
    const float result =
        Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(-1);
    assert(brain_level_calls == 1);
    const float thresholds[] = {1000.0F, 2000.0F, 3000.0F, 5000.0F};
    const float expected = level >= 0 && level <= 3
                               ? thresholds[static_cast<std::size_t>(level)]
                               : 0.0F;
    assert(result == expected);
  }
}

void TestPurchasedToolBit() {
  ObservedTribeState receiver{};
  receiver.purchased_tools_mask = 0x80000001U;
  auto* opaque = reinterpret_cast<OpaqueTribeState*>(&receiver);

  for (std::uint32_t tool_index = 0; tool_index < 38U; ++tool_index) {
    const std::uint32_t expected =
        (receiver.purchased_tools_mask & (1U << (tool_index & 0x1fU))) != 0U
            ? 1U
            : 0U;
    const std::uint32_t actual =
        TribeState_test_purchased_tool_bit_00c8ec00(opaque, tool_index);
    assert(actual == expected);
  }

  assert(TribeState_test_purchased_tool_bit_00c8ec00(opaque, 32U) == 1U);
  assert(TribeState_test_purchased_tool_bit_00c8ec00(opaque, 0x10000020U) ==
         1U);

  const std::uint32_t before = receiver.purchased_tools_mask;
  TribeState_test_purchased_tool_bit_00c8ec00(opaque, 0xffffffffU);
  assert(receiver.purchased_tools_mask == before);
}

}  // namespace

int main() {
  TestEvolutionPointsGlobalRead();
  TestAbilityModeRawWord();
  TestBrainLevelThresholds();
  TestCurrentBrainLevelVirtualPath();
  TestPurchasedToolBit();
}
