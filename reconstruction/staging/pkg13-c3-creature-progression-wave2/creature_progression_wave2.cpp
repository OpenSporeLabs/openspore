#include "creature_progression_wave2.hpp"

#include <cstring>

extern "C" {
float DAT_0169e398 = 0.0F;
float DAT_01582e54 = 10000.0F;
std::uint32_t DAT_01654c10 = 0U;
}

namespace openspore::reconstruction::pkg13_c3_creature_progression_wave2 {
namespace {

alignas(4) OpaqueCreatureGameData g_creature_game_data{};

float ReadPlayerPoints(const ProgressionPlayerAccessWindow* player) {
  float points = 0.0F;
  std::memcpy(&points, player->bytes.data() + 0x10f0U, sizeof(points));
  return points;
}

void WritePlayerPoints(ProgressionPlayerAccessWindow* player, float points) {
  std::memcpy(player->bytes.data() + 0x10f0U, &points, sizeof(points));
}

}

NativePorts g_native_ports{};

const void* event_gate_sentinel() { return &DAT_01654c10; }

extern "C" void PKG13_C3_CDECL
Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(float points) {
  if (points == 0.0F) {
    return;
  }

  float candidate = DAT_0169e398 + points;
  if (DAT_01582e54 < candidate) {
    candidate = DAT_01582e54;
  }
  DAT_0169e398 = candidate;

  const NativePorts& ports = g_native_ports;
  OpaqueNounManager* noun_manager = ports.get_noun_manager();
  ProgressionPlayerAccessWindow* player =
      ports.get_progression_player(noun_manager);
  WritePlayerPoints(player, ReadPlayerPoints(player) + points);

  const void* event_gate = ports.get_event_gate();
  if (event_gate == event_gate_sentinel()) {
    return;
  }

  OpaqueActionStrategy* strategy = ports.get_action_strategy();
  if (strategy == nullptr) {
    return;
  }

  ports.transition_avatar(strategy->transition_receiver, points);

  OpaqueNounManager* action_manager = ports.get_noun_manager();
  OpaqueActionPayload payload{ports.get_avatar(action_manager), 0U, points};
  ports.execute_action(strategy, kAddEvolutionPointsActionId, &payload);
}

extern "C" OpaqueCreatureGameData* PKG13_C3_CDECL
Simulator_cCreatureGameData_Get_00d2e340() {
  return &g_creature_game_data;
}

}
