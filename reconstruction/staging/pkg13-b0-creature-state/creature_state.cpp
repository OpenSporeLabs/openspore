#include "creature_state.hpp"

#include <cstring>

extern "C" {
float DAT_0169e398;
std::uint32_t DAT_0169e394;
float DAT_01582e38;
float DAT_01582e3c;
float DAT_01582e40;
float DAT_01582e44;
}

namespace openspore::reconstruction::pkg13_creature_state {
namespace {

using BrainLevelGetter =
    std::int32_t(PKG13_THISCALL*)(OpaqueCreatureGameDataObject*);

struct BrainLevelVirtualTable {
  BrainLevelGetter slots[0xd8 / 4 + 1];
};

static_assert(sizeof(BrainLevelGetter) == 4,
              "PKG-13 target function pointers are 32-bit");

std::uint32_t read_u32(const void* address) {
  std::uint32_t value;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

}  // namespace

extern "C" float Simulator_cCreatureGameData_GetEvolutionPoints() {
  return DAT_0169e398;
}

extern "C" float Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(
    std::int32_t current_level) {
  float result = 0.0F;
  if (current_level == -1) {
    OpaqueCreatureGameDataObject* object = FUN_00b1fdb0(FUN_00b3d300());
    const auto* vtable =
        *reinterpret_cast<BrainLevelVirtualTable* const*>(object);
    current_level = vtable->slots[0xd8 / 4](object);
  }
  switch (current_level) {
    case 0:
      return DAT_01582e38;
    case 1:
      return DAT_01582e3c;
    case 2:
      return DAT_01582e40;
    case 3:
      return DAT_01582e44;
    default:
      return result;
  }
}

extern "C" std::uint32_t Simulator_cCreatureGameData_GetAbilityMode() {
  return DAT_0169e394;
}

extern "C" std::uint32_t PKG13_THISCALL
TribeState_test_purchased_tool_bit_00c8ec00(OpaqueTribeState* receiver,
                                            std::uint32_t tool_index) {
  const std::uint32_t mask =
      read_u32(reinterpret_cast<const unsigned char*>(receiver) + 0x19d8U);
  const std::uint32_t bit = 1U << ((tool_index & 0xffU) & 0x1fU);
  return (mask & bit) != 0U ? 1U : 0U;
}

}  // namespace openspore::reconstruction::pkg13_creature_state
