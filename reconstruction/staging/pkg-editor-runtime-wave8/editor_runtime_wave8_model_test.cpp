#include <cmath>

#include "editor_runtime_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_RUNTIME_WAVE8_TEST_THISCALL __thiscall
#else
#define PKG_EDITOR_RUNTIME_WAVE8_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_runtime_wave8 {
namespace {

int failures = 0;

bool near(float lhs, float rhs) { return std::fabs(lhs - rhs) <= 1.0e-5f; }

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void test_set_target_angle_optional_write() {
  g_creature_walk_controller_globals = OpaqueCreatureWalkControllerGlobals{};
  g_creature_walk_controller_globals.orientation_x_015e5a0c = 1.25f;
  g_creature_walk_controller_globals.orientation_y_015e5a10 = -2.0f;
  g_creature_walk_controller_globals.orientation_z_015e5a14 = 3.5f;
  OpaqueCreature creature{};
  creature.orientation_10[0] = 9.0f;
  creature.orientation_10[1] = 10.0f;
  creature.orientation_10[2] = 11.0f;
  creature.orientation_10[3] = 12.0f;
  OpaqueCreatureWalkController controller{};
  controller.creature_08 = &creature;
  controller.target_angle_44 = 41.0f;
  controller.angle_48 = 42.0f;

  editor_creature_walk_controller_set_target_angle_0059b2f0(&controller, 4.75f,
                                                            false);
  check(controller.target_angle_44 == 4.75f);
  check(controller.angle_48 == 42.0f);
  check(creature.orientation_10[0] == 9.0f);
  check(creature.orientation_10[1] == 10.0f);
  check(creature.orientation_10[2] == 11.0f);
  check(creature.orientation_10[3] == 12.0f);
}

void test_set_target_angle_applied_orientation() {
  g_creature_walk_controller_globals = OpaqueCreatureWalkControllerGlobals{};
  g_creature_walk_controller_globals.orientation_x_015e5a0c = 1.25f;
  g_creature_walk_controller_globals.orientation_y_015e5a10 = -2.0f;
  g_creature_walk_controller_globals.orientation_z_015e5a14 = 3.5f;
  OpaqueCreature creature{};
  OpaqueCreatureWalkController controller{};
  controller.creature_08 = &creature;
  controller.target_angle_44 = -3.0f;
  controller.angle_48 = -4.0f;

  const float angle = 1.75f;
  const float half_angle = angle * 0.5f;
  editor_creature_walk_controller_set_target_angle_0059b2f0(&controller, angle,
                                                            true);
  const float sine = std::sin(half_angle);
  const float cosine = std::cos(half_angle);
  check(controller.target_angle_44 == angle);
  check(controller.angle_48 == angle);
  check(near(creature.orientation_10[0], 1.25f * sine));
  check(near(creature.orientation_10[1], -2.0f * sine));
  check(near(creature.orientation_10[2], 3.5f * sine));
  check(near(creature.orientation_10[3], cosine));
}

void test_set_target_angle_uses_file_orientation_defaults() {
  g_creature_walk_controller_globals = OpaqueCreatureWalkControllerGlobals{};
  OpaqueCreature creature{};
  OpaqueCreatureWalkController controller{};
  controller.creature_08 = &creature;
  const float angle = 0.0f;
  editor_creature_walk_controller_set_target_angle_0059b2f0(&controller, angle,
                                                            true);
  check(controller.target_angle_44 == 0.0f);
  check(controller.angle_48 == 0.0f);
  check(creature.orientation_10[0] == 0.0f);
  check(creature.orientation_10[1] == 0.0f);
  check(creature.orientation_10[2] == 0.0f);
  check(creature.orientation_10[3] == 1.0f);
}

}

}

using namespace openspore::reconstruction::pkg_editor_runtime_wave8;

int main() {
  test_set_target_angle_optional_write();
  test_set_target_angle_applied_orientation();
  test_set_target_angle_uses_file_orientation_defaults();
  return failures == 0 ? 0 : 1;
}
