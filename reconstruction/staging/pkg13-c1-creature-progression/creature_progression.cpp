#include "creature_progression.hpp"

#include <cstring>

extern "C" float DAT_0169e398 = 0.0F;

namespace openspore::reconstruction::pkg13_c1_creature_progression {
namespace {

float ReadProgressionPlayerPoints(const ProgressionPlayerAccessWindow* player) {
  float points;
  std::memcpy(&points, player->bytes.data() + 0x10f0U, sizeof(points));
  return points;
}

}

NativePorts g_native_ports{nullptr, nullptr, nullptr};

extern "C" void PKG13_C1_CDECL
Simulator_cCreatureGameData_SetEvolutionPoints_raw_00d2e480(float points) {
  DAT_0169e398 = points;
}

extern "C" std::int32_t PKG13_C1_CDECL
pkg13_progression_brain_level_00d2e830() {
  OpaqueNounManager* noun_manager = g_native_ports.get_noun_manager();
  ProgressionPlayerAccessWindow* player =
      g_native_ports.get_progression_player(noun_manager);
  const float current_points = ReadProgressionPlayerPoints(player);
  float accumulated_points = 0.0F;

  for (std::int32_t level = 0; level < 4; ++level) {
    accumulated_points =
        accumulated_points + g_native_ports.get_level_requirement(level);
    if (current_points < accumulated_points) {
      return level;
    }
  }

  return 4;
}

}
