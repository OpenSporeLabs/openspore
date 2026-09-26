#include "editor_runtime_wave8.hpp"

#include <cmath>

#if defined(_MSC_VER)
#define PKG_EDITOR_RUNTIME_WAVE8_THISCALL __thiscall
#else
#define PKG_EDITOR_RUNTIME_WAVE8_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_runtime_wave8 {

OpaqueCreatureWalkControllerGlobals g_creature_walk_controller_globals{};

extern "C" void PKG_EDITOR_RUNTIME_WAVE8_THISCALL
editor_creature_walk_controller_set_target_angle_0059b2f0(
    OpaqueCreatureWalkController* controller, float angle, bool apply_now) {
  controller->target_angle_44 = angle;
  if (!apply_now) {
    return;
  }
  controller->angle_48 = angle;
  OpaqueCreature* creature = controller->creature_08;
  const float half_angle =
      angle * g_creature_walk_controller_globals.half_angle_01471064;
  const float sine = std::sin(half_angle);
  const float cosine = std::cos(half_angle);
  creature->orientation_10[0] =
      g_creature_walk_controller_globals.orientation_x_015e5a0c * sine;
  creature->orientation_10[1] =
      g_creature_walk_controller_globals.orientation_y_015e5a10 * sine;
  creature->orientation_10[2] =
      g_creature_walk_controller_globals.orientation_z_015e5a14 * sine;
  creature->orientation_10[3] = cosine;
}

}

#undef PKG_EDITOR_RUNTIME_WAVE8_THISCALL
