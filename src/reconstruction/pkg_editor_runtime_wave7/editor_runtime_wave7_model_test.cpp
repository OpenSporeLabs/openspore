#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <string>
#include <vector>

#include "editor_runtime_wave7.hpp"

#if defined(_MSC_VER)
#define PKG_W7_TEST_THISCALL __thiscall
#define PKG_W7_TEST_CDECL __cdecl
#else
#define PKG_W7_TEST_THISCALL __attribute__((thiscall))
#define PKG_W7_TEST_CDECL __attribute__((cdecl))
#endif

namespace {

using namespace openspore::reconstruction::pkg_editor_runtime_wave7;

std::vector<std::string> trace;

void check(bool condition) {
  if (!condition) {
    std::fprintf(stderr, "check failed\ntrace:");
    for (const std::string& value : trace) {
      std::fprintf(stderr, " %s", value.c_str());
    }
    std::fprintf(stderr, "\n");
    std::fflush(stderr);
    std::abort();
  }
}

bool near(float lhs, float rhs) {
  check(std::fabs(lhs - rhs) <= 1.0e-4f);
  return true;
}

void record(const char* value) { trace.emplace_back(value); }

void expect_trace(std::initializer_list<const char*> expected) {
  check(trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(trace[index] == value);
    ++index;
  }
  trace.clear();
}

OpaqueControllerMapPorts map_ports{};
OpaqueControllerPorts controller_ports{};
OpaqueFixedBasis basis{};

OpaqueAnimWorld g_world{};
OpaqueControllerMap g_map{};
OpaqueControllerNode g_root{};
OpaqueControllerNode g_low{};
OpaqueControllerNode g_high{};
OpaqueController g_low_controller{};
OpaqueController g_high_controller{};
std::int32_t g_low_key = 10;
std::int32_t g_high_key = 20;
bool g_find_miss = false;
int g_find_calls = 0;
int g_lower_bound_calls = 0;
OpaqueController* g_null_value = nullptr;
void* g_lower_bound_out_seen = nullptr;
bool g_lower_bound_out_first = false;
bool g_ray_words[8]{};

void PKG_W7_TEST_THISCALL fake_lower_bound(OpaqueControllerMap* map,
                                           OpaqueControllerNode** out,
                                           const std::int32_t* key) {
  ++g_lower_bound_calls;
  g_lower_bound_out_seen = out;
  record("map-lower-bound");
  if (out == nullptr || key == nullptr) {
    check(false);
  }
  g_lower_bound_out_first = true;
  if (*key <= g_low_key) {
    *out = &g_low;
  } else if (*key <= g_high_key) {
    *out = &g_high;
  } else {
    *out = map->sentinel_004;
  }
}

void* PKG_W7_TEST_THISCALL fake_find(OpaqueControllerMap* map,
                                     const std::int32_t* key) {
  static_cast<void>(map);
  ++g_find_calls;
  record("map-find");
  if (!g_find_miss && *key == g_low_key) {
    return &g_low.value_14;
  }
  if (!g_find_miss && *key == g_high_key) {
    return &g_high.value_14;
  }
  return &g_null_value;
}

void reset_world() {
  trace.clear();
  g_root.right_00 = nullptr;
  g_root.left_04 = &g_low;
  g_root.parent_08 = &g_high;
  g_low.left_04 = nullptr;
  g_low.right_00 = &g_high;
  g_high.left_04 = nullptr;
  g_high.right_00 = nullptr;
  g_map.sentinel_004 = &g_root;
  g_map.root_00c = &g_low;
  g_map.size_010 = 2;
  g_low.key_10 = g_low_key;
  g_low.value_14 = &g_low_controller;
  g_high.key_10 = g_high_key;
  g_high.value_14 = &g_high_controller;
  g_null_value = nullptr;
  g_world = OpaqueAnimWorld{};
  g_world.controllers_008 = g_map;
  g_world.map_enabled_038 = 1;
  g_world.animation_enabled_03c = 1;
  g_find_miss = false;
  g_find_calls = 0;
  g_lower_bound_calls = 0;
  g_lower_bound_out_seen = nullptr;
  g_lower_bound_out_first = false;
  for (int i = 0; i < 8; ++i) {
    g_ray_words[i] = false;
  }
  g_low_controller = OpaqueController{};
  g_high_controller = OpaqueController{};
  map_ports.lower_bound_00e5c780 = fake_lower_bound;
  map_ports.find_0059c740 = fake_find;
  g_controller_map_ports = &map_ports;
  g_controller_ports = &controller_ports;
  g_fixed_basis = &basis;
}

void test_lower_bound_receives_valid_output_pointer() {
  reset_world();
  check(anim_world_get_creature_controller_0059cac0(&g_world, 10) ==
        &g_low_controller);
  check(g_lower_bound_out_seen != nullptr);
  expect_trace({"map-lower-bound", "map-find"});

  reset_world();
  check(anim_world_get_creature_controller_0059cac0(&g_world, 20) ==
        &g_high_controller);
  check(g_lower_bound_out_seen != nullptr);
  expect_trace({"map-lower-bound", "map-find"});

  reset_world();
  check(anim_world_get_creature_controller_0059cac0(&g_world, 30) == nullptr);
  check(g_lower_bound_out_seen != nullptr);
  expect_trace({"map-lower-bound"});
  check(g_find_calls == 0);

  reset_world();
  g_find_miss = true;
  check(anim_world_get_creature_controller_0059cac0(&g_world, 15) == nullptr);
  check(g_lower_bound_out_seen != nullptr);
  expect_trace({"map-lower-bound", "map-find"});

  reset_world();
  g_world.map_enabled_038 = 0;
  check(anim_world_get_creature_controller_0059cac0(&g_world, 10) == nullptr);
  check(g_lower_bound_calls == 0);
  check(g_find_calls == 0);
  check(trace.empty());
}

float g_forward_angle = 0.0f;
bool g_forward_apply_now = false;
const Vector3* g_forward_position = nullptr;
Vector3 g_forward_copy{};
bool g_forward_apply = false;
bool g_forward_ignore_z = false;
int g_forward_calls = 0;

void PKG_W7_TEST_THISCALL fake_forward_angle(OpaqueController*, float angle,
                                             bool apply_now) {
  ++g_forward_calls;
  g_forward_angle = angle;
  g_forward_apply_now = apply_now;
  record("controller-set-angle");
}

void PKG_W7_TEST_THISCALL fake_forward_position(OpaqueController*,
                                                const Vector3* position,
                                                bool apply_now, bool ignore_z) {
  ++g_forward_calls;
  g_forward_position = position;
  g_forward_copy = *position;
  g_forward_apply = apply_now;
  g_forward_ignore_z = ignore_z;
  record("controller-set-position");
}

void test_anim_world_set_target_angle() {
  reset_world();
  controller_ports.set_target_angle_0059b2f0 = fake_forward_angle;
  g_forward_calls = 0;
  anim_world_set_target_angle_0059cea0(&g_world, 10, 1.5f, true);
  expect_trace({"map-lower-bound", "map-find", "controller-set-angle"});
  check(g_forward_calls == 1);
  check(g_forward_angle == 1.5f);
  check(g_forward_apply_now);

  reset_world();
  g_forward_calls = 0;
  anim_world_set_target_angle_0059cea0(&g_world, 30, 2.5f, false);
  expect_trace({"map-lower-bound"});
  check(g_forward_calls == 0);

  reset_world();
  g_forward_calls = 0;
  g_world.map_enabled_038 = 0;
  anim_world_set_target_angle_0059cea0(&g_world, 10, 3.5f, true);
  check(g_forward_calls == 0);
  check(trace.empty());

  reset_world();
  g_forward_calls = 0;
  g_find_miss = true;
  anim_world_set_target_angle_0059cea0(&g_world, 15, 4.5f, true);
  check(g_forward_calls == 0);
}

void test_anim_world_set_target_position() {
  reset_world();
  controller_ports.set_target_position_0059b0f0 = fake_forward_position;
  g_forward_calls = 0;
  const Vector3 value{1.0f, 2.0f, 3.0f};
  anim_world_set_target_position_0059cf00(&g_world, 20, value, true, true);
  expect_trace({"map-lower-bound", "map-find", "controller-set-position"});
  check(g_forward_calls == 1);
  check(g_forward_position != nullptr);
  check(g_forward_position != &value);
  check(g_forward_copy.x == 1.0f);
  check(g_forward_copy.y == 2.0f);
  check(g_forward_copy.z == 3.0f);
  check(g_forward_apply);
  check(g_forward_ignore_z);

  reset_world();
  g_forward_calls = 0;
  anim_world_set_target_position_0059cf00(&g_world, 99, value, false, false);
  expect_trace({"map-lower-bound"});
  check(g_forward_calls == 0);

  reset_world();
  g_forward_calls = 0;
  g_world.map_enabled_038 = 0;
  anim_world_set_target_position_0059cf00(&g_world, 10, value, true, false);
  check(g_forward_calls == 0);
}

OpaqueCreatureVTable play_vtable{};
OpaqueCreature play_creature{};
OpaqueController* g_publish_target = nullptr;
OpaqueWord g_published_id = 0;
int g_publish_calls = 0;

void PKG_W7_TEST_THISCALL fake_publish(OpaqueController* controller,
                                       OpaqueWord animation_id) {
  ++g_publish_calls;
  g_publish_target = controller;
  g_published_id = animation_id;
  record("publish-animation-id");
}

OpaqueWord g_applied_animation = 0;
std::uint32_t g_applied_extra = 0;
int g_apply_calls = 0;

void PKG_W7_TEST_THISCALL fake_apply_animation(void*, OpaqueWord animation,
                                               std::uint32_t extra) {
  ++g_apply_calls;
  g_applied_animation = animation;
  g_applied_extra = extra;
  record("creature-apply-animation");
}

void test_anim_world_play_animation_publishes_id() {
  reset_world();
  play_vtable = OpaqueCreatureVTable{};
  play_vtable.slots_00[1] = reinterpret_cast<void*>(&fake_apply_animation);
  play_creature = OpaqueCreature{};
  play_creature.vtable = &play_vtable;
  g_low_controller.creature_008 = &play_creature;
  controller_ports.publish_animation_id_007cd950 = fake_publish;
  g_apply_calls = 0;
  g_publish_calls = 0;

  anim_world_play_animation_0059cb10(&g_world, 10, 0x1234u);
  expect_trace({"map-lower-bound", "map-find", "creature-apply-animation",
                "publish-animation-id"});
  check(g_apply_calls == 1);
  check(g_applied_animation == 0x1234u);
  check(g_applied_extra == 0u);
  check(g_publish_calls == 1);
  check(g_publish_target == &g_low_controller);
  check(g_published_id == 0x1234u);

  reset_world();
  play_vtable = OpaqueCreatureVTable{};
  play_vtable.slots_00[1] = reinterpret_cast<void*>(&fake_apply_animation);
  play_creature.vtable = &play_vtable;
  g_low_controller.creature_008 = &play_creature;
  controller_ports.publish_animation_id_007cd950 = fake_publish;
  g_apply_calls = 0;
  g_publish_calls = 0;
  g_world.animation_enabled_03c = 0;
  anim_world_play_animation_0059cb10(&g_world, 10, 0x55u);
  expect_trace({"map-lower-bound", "map-find"});
  check(g_apply_calls == 0);
  check(g_publish_calls == 0);

  reset_world();
  play_vtable = OpaqueCreatureVTable{};
  play_vtable.slots_00[1] = reinterpret_cast<void*>(&fake_apply_animation);
  play_creature.vtable = &play_vtable;
  g_low_controller.creature_008 = nullptr;
  controller_ports.publish_animation_id_007cd950 = fake_publish;
  g_apply_calls = 0;
  g_publish_calls = 0;
  anim_world_play_animation_0059cb10(&g_world, 10, 0x55u);
  check(g_apply_calls == 0);
  check(g_publish_calls == 0);

  reset_world();
  play_vtable = OpaqueCreatureVTable{};
  play_vtable.slots_00[1] = reinterpret_cast<void*>(&fake_apply_animation);
  play_creature.vtable = &play_vtable;
  g_low_controller.creature_008 = &play_creature;
  controller_ports.publish_animation_id_007cd950 = fake_publish;
  g_apply_calls = 0;
  g_publish_calls = 0;
  g_world.map_enabled_038 = 0;
  anim_world_play_animation_0059cb10(&g_world, 10, 0x55u);
  check(g_apply_calls == 0);
  check(g_publish_calls == 0);
  check(trace.empty());
}

OpaquePickerWorldVTable picker_vtable{};
OpaquePickerWorld picker{};
OpaqueShadowWorldVTable shadow_vtable{};
OpaqueShadowWorld shadow{};
OpaqueController controller{};
OpaqueRayQuery g_queries[4]{};
Vector3 g_origins[4]{};
int g_ray_calls = 0;
int g_notify_calls = 0;
OpaqueWord g_notify_arg = 0;
std::uint32_t g_collision_index = 33u;

std::uint32_t PKG_W7_TEST_THISCALL fake_set_active(void*, OpaqueWord collision,
                                                   bool flag) {
  static_cast<void>(flag);
  record("picker-set-active");
  check(collision == kCollisionClassRay_026f3933);
  return g_collision_index;
}

std::uint32_t PKG_W7_TEST_THISCALL
fake_raycast(void*, OpaqueRaycastOut* out, const Vector3* origin,
             OpaqueWord word_2, const OpaqueRayQuery* query, OpaqueWord word_4,
             OpaqueRaycastOut* aux, OpaqueWord word_6, OpaqueWord word_7) {
  ++g_ray_calls;
  record("shadow-raycast");
  g_ray_words[0] = out != nullptr;
  g_ray_words[1] = origin != nullptr;
  g_ray_words[2] = word_2;
  g_ray_words[3] = query != nullptr;
  g_ray_words[4] = word_4;
  g_ray_words[5] = aux != nullptr;
  g_ray_words[6] = word_6;
  g_ray_words[7] = word_7;
  if (out == nullptr || aux == nullptr || origin == nullptr ||
      query == nullptr) {
    check(false);
  }
  OpaqueRaycastOut hit{};
  hit.x = 7.25f;
  hit.y = 8.5f;
  hit.z = 9.75f;
  hit.w = 1.0f;
  *out = hit;
  OpaqueRaycastOut extra{};
  extra.x = 3.5f;
  extra.y = 4.5f;
  extra.z = 5.5f;
  extra.w = 0.5f;
  *aux = extra;
  std::memcpy(&g_origins[g_ray_calls - 1], origin, sizeof(Vector3));
  std::memcpy(&g_queries[g_ray_calls - 1], query, sizeof(OpaqueRayQuery));
  return 1u;
}

OpaquePickerWorld* PKG_W7_TEST_CDECL fake_picker_world() {
  record("picker-world-get");
  return &picker;
}

void PKG_W7_TEST_THISCALL fake_notify(OpaqueCreature*, OpaqueWord argument) {
  ++g_notify_calls;
  g_notify_arg = argument;
  record("creature-notify");
}

OpaqueCreatureVTable update_vtable{};
OpaqueCreature update_creature{};
OpaqueCreatureModel g_model{};

void* g_bounds_arg1 = nullptr;
OpaqueWord g_bounds_arg3 = 7u;
OpaqueWord g_bounds_arg4 = 9u;
void* g_bounds_arg5 = nullptr;
int g_bounds_calls = 0;
void* g_bounds_handle = reinterpret_cast<void*>(0x2000);
void* g_bounds_extra = reinterpret_cast<void*>(0x3000);

void PKG_W7_TEST_THISCALL fake_get_bounds(void*, void* arg1, OpaqueWord arg2,
                                          OpaqueWord arg3, void* arg4) {
  ++g_bounds_calls;
  record("creature-get-bounds");
  g_bounds_arg1 = arg1;
  g_bounds_arg5 = arg4;
  g_bounds_arg3 = arg2;
  g_bounds_arg4 = arg3;
  *static_cast<void**>(arg1) = g_bounds_handle;
  *static_cast<void**>(arg4) = g_bounds_extra;
}

float g_blend_value = 0.5f;
bool g_blend_result = true;
int g_blend_calls = 0;
bool g_query_bounds = false;
bool g_query_smoothing = false;
void* g_manager_owner = nullptr;
std::uint8_t g_owner_bytes[64]{};
Vector3 g_lerp_out{1.0f, 0.0f, 0.0f};
float g_lerp_scalar = 0.0f;
float g_lerp_scalars[2] = {0.0f, 0.0f};
int g_lerp_calls = 0;
float g_angle_from = 0.0f;
float g_angle_to = 0.0f;
float g_angle_step = 0.0f;
int g_angle_calls = 0;
float g_angle_sweep_step = 0.0f;
const Vector3* g_project_args[6] = {nullptr, nullptr, nullptr,
                                    nullptr, nullptr, nullptr};
Vector3 g_project_vals[6]{};
int g_project_calls = 0;
Vector4 g_look_row_copy{};
int g_look_calls = 0;
bool g_look_blocked = false;
const Vector3* g_rotate_axis_seen = nullptr;
float g_rotate_angle = 0.0f;
int g_rotate_calls = 0;
Vector3 g_cross_out{0.0f, 0.0f, 1.0f};
Vector3 g_look_out{0.0f, 1.0f, 0.0f};

bool PKG_W7_TEST_THISCALL fake_get_blend_5c(void*, void*, void* out, void*) {
  ++g_blend_calls;
  record("creature-query-blend");
  *static_cast<float*>(out) = g_blend_value;
  return g_blend_result;
}

void* PKG_W7_TEST_CDECL fake_manager_get() {
  record("manager-get");
  return reinterpret_cast<void*>(0x1000);
}

void* PKG_W7_TEST_THISCALL fake_manager_slot_40(void*, void* handle) {
  static_cast<void>(handle);
  record("manager-slot-40");
  return g_manager_owner;
}

bool PKG_W7_TEST_CDECL fake_query_bounds(void*) {
  record("manager-query-00a02710");
  return g_query_bounds;
}

bool PKG_W7_TEST_CDECL fake_query_smoothing(void*) {
  record("manager-query-00a027a0");
  return g_query_smoothing;
}

const Vector3* PKG_W7_TEST_CDECL fake_lerp_vector(const Vector4*,
                                                  const Vector3*,
                                                  const Vector3*,
                                                  float scalar) {
  ++g_lerp_calls;
  record("lerp-vector");
  g_lerp_scalar = scalar;
  if (g_lerp_calls <= 2) {
    g_lerp_scalars[g_lerp_calls - 1] = scalar;
  }
  return &g_lerp_out;
}

float PKG_W7_TEST_CDECL fake_lerp_angle(float from, float to, float step) {
  ++g_angle_calls;
  record("lerp-angle");
  g_angle_from = from;
  g_angle_to = to;
  g_angle_step = step;
  if (g_angle_calls == 2) {
    g_angle_sweep_step = step;
  }
  return to;
}

float PKG_W7_TEST_CDECL fake_project(const Vector3* vector,
                                     const Vector3* basis_a,
                                     const Vector3* basis_b) {
  g_project_args[g_project_calls] = vector;
  g_project_args[g_project_calls + 1] = basis_a;
  g_project_args[g_project_calls + 2] = basis_b;
  g_project_vals[g_project_calls] = *vector;
  g_project_vals[g_project_calls + 1] = *basis_a;
  g_project_vals[g_project_calls + 2] = *basis_b;
  g_project_calls += 3;
  record("project");
  return 0.25f;
}

float g_wrap_angle_override = 0.0f;
bool g_wrap_angle_overridden = false;

float PKG_W7_TEST_CDECL fake_wrap_angle(float value) {
  record("wrap-angle");
  return g_wrap_angle_overridden ? g_wrap_angle_override : value;
}

const Vector3* PKG_W7_TEST_CDECL fake_look_direction(const Vector3* axis,
                                                     const Vector3* toward,
                                                     const Vector4* row) {
  static_cast<void>(axis);
  static_cast<void>(toward);
  ++g_look_calls;
  g_look_row_copy = *row;
  record("look-direction");
  return &g_look_out;
}

bool PKG_W7_TEST_CDECL fake_look_blocked(const Vector3*) {
  record("look-blocked");
  return g_look_blocked;
}

const Vector3* PKG_W7_TEST_CDECL fake_cross(const Vector4*, const Vector3*) {
  record("cross");
  return &g_cross_out;
}

void PKG_W7_TEST_CDECL fake_rotate(Vector3* out, const Vector3* axis,
                                   float angle) {
  ++g_rotate_calls;
  g_rotate_axis_seen = axis;
  g_rotate_angle = angle;
  record("rotate");
  out->x = 1.0f;
  out->y = 2.0f;
  out->z = 3.0f;
}

void reset_controller() {
  trace.clear();
  basis = OpaqueFixedBasis{};
  basis.orientation[0] = 0.0f;
  basis.orientation[1] = 1.0f;
  basis.orientation[2] = 0.0f;
  basis.projection[0] = 1.0f;
  basis.projection[1] = 0.0f;
  basis.projection[2] = 0.0f;
  controller = OpaqueController{};
  update_creature = OpaqueCreature{};
  update_vtable = OpaqueCreatureVTable{};
  update_vtable.get_bounds_58 = fake_get_bounds;
  update_vtable.get_blend_5c = fake_get_blend_5c;
  update_creature.vtable = &update_vtable;
  controller.creature_008 = &update_creature;
  controller.shadow_00c = &shadow;
  picker_vtable = OpaquePickerWorldVTable{};
  picker_vtable.set_active_28 = fake_set_active;
  picker = OpaquePickerWorld{};
  picker.vtable = &picker_vtable;
  shadow_vtable = OpaqueShadowWorldVTable{};
  shadow_vtable.raycast_24 = fake_raycast;
  shadow = OpaqueShadowWorld{};
  shadow.vtable = &shadow_vtable;
  g_model = OpaqueCreatureModel{};
  update_creature.model_17c = &g_model;
  controller_ports.picker_world_0067dd80 = fake_picker_world;
  controller_ports.notify_00a047d0 = fake_notify;
  controller_ports.publish_animation_id_007cd950 = fake_publish;
  controller_ports.manager_get_0067cb20 = fake_manager_get;
  controller_ports.manager_slot_40 = fake_manager_slot_40;
  controller_ports.manager_query_00a02710 = fake_query_bounds;
  controller_ports.manager_query_00a027a0 = fake_query_smoothing;
  controller_ports.lerp_vector_00699600 = fake_lerp_vector;
  controller_ports.lerp_angle_0069b840 = fake_lerp_angle;
  controller_ports.project_0069b760 = fake_project;
  controller_ports.wrap_angle_0059ac00 = fake_wrap_angle;
  controller_ports.look_direction_0059aed0 = fake_look_direction;
  controller_ports.look_blocked_0059ab70 = fake_look_blocked;
  controller_ports.cross_00436ce0 = fake_cross;
  controller_ports.rotate_00576b00 = fake_rotate;
  g_fixed_basis = &basis;
  g_controller_ports = &controller_ports;
  g_ray_calls = 0;
  g_notify_calls = 0;
  g_collision_index = 33u;
  g_manager_owner = nullptr;
  std::memset(&g_owner_bytes, 0, sizeof(g_owner_bytes));
  g_bounds_calls = 0;
  g_bounds_arg1 = nullptr;
  g_bounds_arg5 = nullptr;
  g_bounds_arg3 = 7u;
  g_bounds_arg4 = 9u;
  g_bounds_arg5 = nullptr;
  g_query_bounds = false;
  g_query_smoothing = false;
  g_blend_value = 0.5f;
  g_blend_result = true;
  g_blend_calls = 0;
  g_lerp_out = Vector3{1.0f, 0.0f, 0.0f};
  g_lerp_scalar = 0.0f;
  g_lerp_scalars[0] = 0.0f;
  g_lerp_scalars[1] = 0.0f;
  g_lerp_calls = 0;
  g_angle_from = 0.0f;
  g_angle_to = 0.0f;
  g_angle_step = 0.0f;
  g_angle_sweep_step = 0.0f;
  g_angle_calls = 0;
  for (std::size_t index = 0; index < 6; ++index) {
    g_project_args[index] = nullptr;
    g_project_vals[index] = Vector3{};
  }
  g_project_calls = 0;
  g_look_row_copy = Vector4{};
  g_look_calls = 0;
  g_look_blocked = false;
  g_rotate_axis_seen = nullptr;
  g_rotate_angle = 0.0f;
  g_rotate_calls = 0;
  g_cross_out = Vector3{0.0f, 0.0f, 1.0f};
  g_look_out = Vector3{0.0f, 1.0f, 0.0f};
  g_publish_calls = 0;
  g_publish_target = nullptr;
  g_published_id = 0;
  std::memset(&g_queries, 0, sizeof(g_queries));
  std::memset(&g_origins, 0, sizeof(g_origins));
}

void test_controller_set_target_position_scales_long_only() {
  reset_controller();
  const Vector3 long_value{3.0f, 4.0f, 12.0f};
  controller_set_target_position_0059b0f0(&controller, &long_value, false,
                                          false);
  const float scale = 5.0f / 13.0f;
  check(near(controller.position_020.x, 3.0f));
  check(near(controller.position_020.y, 4.0f));
  check(near(controller.position_020.z, 12.0f));
  check(near(controller.offset_02c.x, 3.0f * scale));
  check(near(controller.offset_02c.y, 4.0f * scale));
  check(near(controller.offset_02c.z, 12.0f * scale));
  const float sum = (3.0f * scale) * (3.0f * scale) +
                    (4.0f * scale) * (4.0f * scale) +
                    (12.0f * scale) * (12.0f * scale);
  check(near(std::sqrt(sum), 5.0f));

  reset_controller();
  const Vector3 short_value{0.3f, 0.4f, 0.0f};
  controller_set_target_position_0059b0f0(&controller, &short_value, false,
                                          false);
  check(near(controller.offset_02c.x, 0.3f));
  check(near(controller.offset_02c.y, 0.4f));
  check(near(controller.offset_02c.z, 0.0f));
  check(near(controller.position_020.x, 0.3f));
  check(g_ray_calls == 0);
  check(g_notify_calls == 0);
  check(trace.empty());
}

void test_controller_set_target_position_ignore_z_order() {
  reset_controller();
  const Vector3 value{3.0f, 4.0f, 12.0f};
  controller_set_target_position_0059b0f0(&controller, &value, false, true);
  check(near(controller.offset_02c.z, 0.0f));
  check(near(controller.position_020.z, 12.0f));
  const float scale = 5.0f / 13.0f;
  check(near(controller.offset_02c.x, 3.0f * scale));
}

void test_controller_set_target_position_apply() {
  reset_controller();
  const Vector3 value{6.0f, 8.0f, 0.0f};
  controller_set_target_position_0059b0f0(&controller, &value, true, false);
  expect_trace({"picker-world-get", "picker-set-active", "shadow-raycast",
                "creature-notify"});
  check(g_ray_calls == 1);
  check(g_notify_calls == 1);
  check(g_notify_arg == 1u);
  check(near(update_creature.position.x, 3.0f));
  check(near(update_creature.position.y, 4.0f));
  check(near(update_creature.position.z, 7.25f));
  check(near(controller.current_038.x, 3.0f));
  check(near(controller.current_038.y, 4.0f));
  check(near(controller.current_038.z, 0.0f));
  check(near(g_origins[0].x, 3.0f));
  check(near(g_origins[0].y, 4.0f));
  check(near(g_origins[0].z, -500.0f));
  check(g_queries[0].flag_14 == 4u);
  check(g_queries[0].flag_15 == 0u);
  check(g_queries[0].collision_mask[0] == 0u);
  check(g_queries[0].collision_mask[1] == 0x00000002u);
  check(g_queries[0].collision_mask[2] == 0u);
  check(g_queries[0].collision_mask[3] == 0u);
  check(g_queries[0].collision_mask[4] == 0u);
}

void test_controller_set_target_position_ignore_z_skips_ray() {
  reset_controller();
  const Vector3 value{6.0f, 8.0f, 0.0f};
  controller_set_target_position_0059b0f0(&controller, &value, true, true);
  expect_trace({"creature-notify"});
  check(g_ray_calls == 0);
  check(near(update_creature.position.z, 0.0f));
  check(near(update_creature.position.x, 3.0f));
}

void test_controller_update_ray_query_record_layout() {
  reset_controller();
  controller.follow_ground_054 = 0u;
  g_collision_index = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(g_ray_calls == 1);
  check(offsetof(OpaqueRayQuery, collision_mask) == 0x00u);
  check(offsetof(OpaqueRayQuery, flag_14) == 0x14u);
  check(offsetof(OpaqueRayQuery, flag_15) == 0x15u);
  check(sizeof(OpaqueRayQuery) == 0x18u);
  check(g_queries[0].flag_14 == 4u);
  check(g_queries[0].flag_15 == 0u);
  check(g_queries[0].collision_mask[0] == 0x00000002u);
  check(g_queries[0].collision_mask[1] == 0u);
  check(g_queries[0].collision_mask[2] == 0u);
  check(g_queries[0].collision_mask[3] == 0u);
  check(g_queries[0].collision_mask[4] == 0u);
}

void test_controller_set_target_position_collision_overflow() {
  reset_controller();
  g_collision_index = 0x40u;
  const Vector3 value{6.0f, 8.0f, 0.0f};
  controller_set_target_position_0059b0f0(&controller, &value, true, false);
  check(g_ray_calls == 1);
  check(g_queries[0].collision_mask[0] == 0u);
  check(g_queries[0].collision_mask[1] == 0u);
  check(g_queries[0].collision_mask[2] == 0u);
  check(g_queries[0].collision_mask[3] == 0u);
  check(g_queries[0].collision_mask[4] == 0u);
}

void test_controller_update_early_returns() {
  reset_controller();
  controller.creature_008 = nullptr;
  controller_update_0059b4b0(&controller, 16);
  check(trace.empty());

  reset_controller();
  controller.shadow_00c = nullptr;
  controller_update_0059b4b0(&controller, 16);
  check(trace.empty());
}

void test_controller_update_bounds_callback_arguments() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_bounds_calls == 1);
  check(g_bounds_arg1 != nullptr);
  check(g_bounds_arg5 != nullptr);
  check(g_bounds_arg1 != g_bounds_arg5);
  check(*static_cast<void**>(g_bounds_arg1) == g_bounds_handle);
  check(*static_cast<void**>(g_bounds_arg5) == g_bounds_extra);
  check(g_bounds_arg3 == 0u);
  check(g_bounds_arg4 == 0u);
}

void test_controller_update_interpolation_is_unconditional() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_rate_04c = 1.0f;
  g_query_bounds = false;
  controller_update_0059b4b0(&controller, 16);
  check(g_bounds_calls == 1);
  check(g_lerp_calls == 2);
  check(g_lerp_scalars[0] == 0.0f);
  check(g_lerp_scalars[1] == 0.0f);

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_rate_04c = 1.0f;
  g_query_bounds = true;
  g_blend_result = false;
  controller_update_0059b4b0(&controller, 16);
  check(g_lerp_calls == 2);
  check(g_lerp_scalars[0] == 0.0f);
  check(g_lerp_scalars[1] == 0.0f);

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_rate_04c = 1.0f;
  g_query_bounds = true;
  g_blend_result = true;
  g_blend_value = 0.5f;
  controller_update_0059b4b0(&controller, 16);
  check(g_lerp_calls == 2);
  check(g_lerp_scalars[0] == 0.5f * 0.016f);
  check(g_lerp_scalars[1] == 2.0f * 0.5f * 0.016f);

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_rate_04c = 1.0f;
  g_query_bounds = true;
  g_blend_result = true;
  g_blend_value = 2.0f;
  controller_update_0059b4b0(&controller, 16);
  check(g_lerp_calls == 2);
  check(g_lerp_scalars[0] == 1.0f * 0.016f);
}

void test_controller_update_limits_long_current_offset() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.position_rate_04c = 1.0f;
  g_query_bounds = true;
  g_blend_value = 1.0f;
  g_lerp_out = Vector3{30.0f, 40.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  const float scale = 5.0f / 50.0f;
  check(near(controller.current_038.x, 30.0f * scale));
  check(near(controller.current_038.y, 40.0f * scale));
  check(near(controller.current_038.z, 0.0f));

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.position_rate_04c = 1.0f;
  g_query_bounds = true;
  g_blend_value = 1.0f;
  g_lerp_out = Vector3{1.0f, 0.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(near(controller.current_038.x, 1.0f));
  check(near(controller.current_038.y, 0.0f));
}

void test_controller_update_owner_reset_publishes_zero() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  g_manager_owner = &g_owner_bytes;
  controller_update_0059b4b0(&controller, 16);
  check(g_publish_calls == 1);
  check(g_published_id == 0u);
  check(g_publish_target == &controller);
  check(g_lerp_calls == 2);
  check(g_angle_calls == 1);
  check(g_lerp_scalars[0] == 0.0f);

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  g_manager_owner = &g_owner_bytes;
  g_owner_bytes[0x1d] = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(g_publish_calls == 0);
}

void test_controller_update_limited_projection_operands() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.angle_limited_084 = 1u;
  controller.previous_058 = Vector3{13.0f, 4.0f, 0.0f};
  controller.world_064 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_project_calls == 6);
  check(g_project_args[0] != g_project_args[3]);
  check(g_project_args[0] != g_project_args[1]);
  check(g_project_args[0] != g_project_args[2]);
  check(g_project_args[3] != g_project_args[4]);
  check(g_project_args[3] != g_project_args[5]);
  check(near(g_project_vals[1].x, basis.orientation[0]));
  check(near(g_project_vals[1].y, basis.orientation[1]));
  check(near(g_project_vals[1].z, basis.orientation[2]));
  check(near(g_project_vals[2].x, basis.projection[0]));
  check(near(g_project_vals[2].y, basis.projection[1]));
  check(near(g_project_vals[2].z, basis.projection[2]));
  check(near(g_project_vals[4].x, basis.projection[0]));
  check(near(g_project_vals[4].y, basis.projection[1]));
  check(near(g_project_vals[4].z, basis.projection[2]));
  check(near(g_project_vals[5].x, basis.orientation[0]));
  check(near(g_project_vals[5].y, basis.orientation[1]));
  check(near(g_project_vals[5].z, basis.orientation[2]));
  check(g_angle_calls == 2);
  check(near(g_angle_sweep_step, kSweepFactor));
}

void test_controller_update_quarter_turn_sign() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.snap_when_facing_055 = 1u;
  controller.angle_048 = 2.0f;
  controller.world_064 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_rotate_calls == 1);
  check(near(g_rotate_angle, 2.0f + 0.25f - kFacingQuarterTurn));

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.snap_when_facing_055 = 1u;
  controller.angle_048 = -2.0f;
  controller.world_064 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_rotate_calls == 1);
  check(near(g_rotate_angle, -2.0f + 0.25f + kFacingQuarterTurn));

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.snap_when_facing_055 = 1u;
  controller.angle_048 = 0.0f;
  controller.world_064 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_rotate_calls == 0);
}

void test_controller_update_orientation_row_uses_basis() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.angle_048 = 1.0f;
  controller_update_0059b4b0(&controller, 16);
  const float half = kHalfAngle;
  check(near(update_creature.orientation.x, std::sin(half) * 0.0f));
  check(near(update_creature.orientation.y, std::sin(half) * 1.0f));
  check(near(update_creature.orientation.z, std::sin(half) * 0.0f));
  check(near(update_creature.orientation.w, std::cos(half)));

  reset_controller();
  basis.orientation[0] = 2.0f;
  basis.orientation[1] = 3.0f;
  basis.orientation[2] = 4.0f;
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.angle_048 = 1.0f;
  controller_update_0059b4b0(&controller, 16);
  check(near(update_creature.orientation.x, std::sin(half) * 2.0f));
  check(near(update_creature.orientation.y, std::sin(half) * 3.0f));
  check(near(update_creature.orientation.z, std::sin(half) * 4.0f));
  check(near(update_creature.orientation.w, std::cos(half)));
}

void test_controller_update_normalize_epsilon_is_injected() {
  reset_controller();
  basis.normalize_epsilon[0] = 3.0f;
  basis.normalize_epsilon[1] = 4.0f;
  basis.normalize_epsilon[2] = 0.0f;
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{0.0f, 0.0f, 0.0f};
  controller.previous_058 = Vector3{3.0f, 4.0f, 0.0f};
  controller.world_064 = Vector3{9.0f, 12.0f, 0.0f};
  controller.angle_limited_084 = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(g_project_calls == 6);
  check(near(g_project_vals[0].x, 2.0f / std::sqrt(20.0f)));
  check(near(g_project_vals[0].y, 4.0f / std::sqrt(20.0f)));
  check(near(g_project_vals[0].z, 0.0f));
  check(near(g_project_vals[3].x, 8.0f / std::sqrt(208.0f)));
  check(near(g_project_vals[3].y, 12.0f / std::sqrt(208.0f)));
  check(near(g_project_vals[3].z, 0.0f));

  reset_controller();
  basis.normalize_epsilon[0] = 0.5f;
  basis.normalize_epsilon[1] = 0.5f;
  basis.normalize_epsilon[2] = 0.5f;
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{0.0f, 0.0f, 0.0f};
  controller.previous_058 = Vector3{3.0f, 4.0f, 0.0f};
  controller.world_064 = Vector3{9.0f, 12.0f, 0.0f};
  controller.angle_limited_084 = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(g_project_calls == 6);
  check(near(g_project_vals[0].x, 2.0f));
  check(near(g_project_vals[0].y, 4.0f));
  check(near(g_project_vals[0].z, 0.0f));
  check(near(g_project_vals[3].x, 8.0f));
  check(near(g_project_vals[3].y, 12.0f));
  check(near(g_project_vals[3].z, 0.0f));
}

void test_controller_update_look_direction_row_argument() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_020 = Vector3{3.0f, 4.0f, 0.0f};
  controller.angle_048 = 1.0f;
  g_lerp_out = Vector3{3.0f, 4.0f, 0.0f};
  g_query_smoothing = true;
  g_model.smoothing_enabled_2d4 = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(trace.size() == 10u);
  check(trace[8] == "look-direction");
  check(trace[9] == "look-blocked");
  check(g_look_calls == 1);
  const float row_half = kHalfAngle;
  check(near(g_look_row_copy.x, update_creature.orientation.x));
  check(near(g_look_row_copy.y, update_creature.orientation.y));
  check(near(g_look_row_copy.z, update_creature.orientation.z));
  check(near(g_look_row_copy.w, std::cos(row_half)));
  check(!(g_look_row_copy.x == update_creature.position.x &&
          g_look_row_copy.y == update_creature.position.y &&
          g_look_row_copy.z == update_creature.position.z));
  check(g_rotate_calls == 0);

  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.position_020 = Vector3{9.0f, 9.0f, 0.0f};
  g_lerp_out = Vector3{3.0f, 4.0f, 0.0f};
  g_query_smoothing = true;
  g_model.smoothing_enabled_2d4 = 1u;
  controller_update_0059b4b0(&controller, 16);
  check(g_look_calls == 0);
  check(g_blend_calls == 0);
  check(trace.size() == 9u);
  check(trace[8] == "cross");
}

void test_controller_update_follow_ground_gate() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_ray_calls == 0);
  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_ray_calls == 1);
}

void test_controller_update_creep_clamp() {
  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.creep_remaining_07c = 0.5f;
  controller.creep_low_074 = 0.25f;
  controller.creep_high_078 = 0.25f;
  controller_update_0059b4b0(&controller, 100);
  check(near(controller.creep_remaining_07c, 0.4f));
  check(near(controller.creep_low_074, 0.25f));
  check(near(update_creature.position.z, 0.0f));

  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.creep_low_074 = 0.0f;
  controller.creep_high_078 = 1.0f;
  controller.creep_rate_080 = 100.0f;
  controller_update_0059b4b0(&controller, 16);
  check(near(controller.creep_low_074, 1.0f));
  check(near(update_creature.position.z, 7.25f));
  check(near(g_origins[0].z, -500.0f));

  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.creep_low_074 = 1.0f;
  controller.creep_high_078 = 0.0f;
  controller.creep_rate_080 = 1.0f;
  controller_update_0059b4b0(&controller, 100);
  check(near(controller.creep_low_074, 0.9f));

  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.creep_low_074 = 1.0f;
  controller.creep_high_078 = 0.0f;
  controller.creep_rate_080 = 100.0f;
  controller_update_0059b4b0(&controller, 100);
  check(near(controller.creep_low_074, controller.creep_high_078));

  reset_controller();
  controller.follow_ground_054 = 0u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.creep_low_074 = 0.75f;
  controller.creep_high_078 = 0.75f;
  controller.creep_rate_080 = 100.0f;
  controller_update_0059b4b0(&controller, 100);
  check(near(controller.creep_low_074, 0.75f));
}

void test_controller_update_negative_dt_wraps() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  g_query_bounds = true;
  controller.position_rate_04c = 0.5f;
  controller_update_0059b4b0(&controller, -1);
  const float wrapped = static_cast<float>(0xffffffffu) * kTimeScale;
  check(wrapped > 4.0e6f);
  check(g_lerp_calls >= 1);
  check(g_lerp_scalar > 2.0e6f);
}

void test_controller_update_smoothing_copy_path() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.angle_048 = 1.0f;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.world_064 = Vector3{4.0f, 5.0f, 6.0f};
  controller_update_0059b4b0(&controller, 16);
  check(g_ray_calls == 0);
  check(near(update_creature.position.x, 1.0f));
  check(near(update_creature.position.y, 0.0f));
  check(near(update_creature.smoothing.x, 11.0f));
  check(near(update_creature.smoothing.y, 0.0f));
  check(near(update_creature.smoothing.z, 0.0f));
}

}

void test_offset_rescale_uses_ordered_comparison() {
  const float nan_value = std::numeric_limits<float>::quiet_NaN();
  check(clamp_offset_length(3.0f) == 3.0f);
  check(clamp_offset_length(5.0f) == 5.0f);
  check(clamp_offset_length(9.0f) == kOffsetLimit);
  check(std::isnan(clamp_offset_length(nan_value)));
}

void test_quarter_turn_sign_follows_comiss_jbe() {
  check(quarter_turn_sign(-0.5f) == kNegativeSign);
  check(quarter_turn_sign(0.0f) == kPositiveSign);
  check(quarter_turn_sign(0.5f) == kPositiveSign);
  const float nan_value = std::numeric_limits<float>::quiet_NaN();
  check(quarter_turn_sign(nan_value) == kPositiveSign);
}

void test_quarter_turn_nan_skips_rotate_guard() {
  reset_controller();
  controller.follow_ground_054 = 1u;
  controller.current_038 = Vector3{3.0f, 4.0f, 0.0f};
  controller.snap_when_facing_055 = 1u;
  controller.angle_048 = 1.0f;
  controller.world_064 = Vector3{3.0f, 4.0f, 0.0f};
  g_wrap_angle_overridden = true;
  g_wrap_angle_override = std::numeric_limits<float>::quiet_NaN();
  controller_update_0059b4b0(&controller, 16);
  g_wrap_angle_overridden = false;
  check(g_rotate_calls == 0);
  check(near(controller.angle_048, 1.0f));
}

void test_lower_bound_argument_order_is_out_then_key() {
  reset_world();
  OpaqueController* found =
      anim_world_get_creature_controller_0059cac0(&g_world, g_low_key);
  check(found == &g_low_controller);
  check(g_lower_bound_out_first);
  check(g_lower_bound_out_seen != nullptr);
}

void test_raycast_receives_eight_stack_words() {
  reset_controller();
  controller.follow_ground_054 = 0u;
  controller_update_0059b4b0(&controller, 16);
  check(g_ray_calls == 1);
  check(g_ray_words[0]);
  check(g_ray_words[1]);
  check(!g_ray_words[2]);
  check(g_ray_words[3]);
  check(!g_ray_words[4]);
  check(g_ray_words[5]);
  check(!g_ray_words[6]);
  check(!g_ray_words[7]);
}

void test_blend_slot_returns_bool() {
  reset_controller();
  g_blend_result = true;
  g_blend_value = 0.5f;
  float blend_out = 0.0f;
  Vector4 blend_weight{};
  check(update_vtable.get_blend_5c != nullptr);
  const bool result = update_vtable.get_blend_5c(&update_creature, nullptr,
                                                 &blend_out, &blend_weight);
  check(result);
  check(g_blend_calls == 1);
  check(blend_out == 0.5f);
  g_blend_result = false;
  const bool miss = update_vtable.get_blend_5c(&update_creature, nullptr,
                                               &blend_out, &blend_weight);
  check(!miss);
  check(g_blend_calls == 2);
}

int main() {
  test_lower_bound_receives_valid_output_pointer();
  test_anim_world_set_target_angle();
  test_anim_world_set_target_position();
  test_anim_world_play_animation_publishes_id();
  test_controller_set_target_position_scales_long_only();
  test_controller_set_target_position_ignore_z_order();
  test_controller_set_target_position_apply();
  test_controller_set_target_position_ignore_z_skips_ray();
  test_controller_set_target_position_collision_overflow();
  test_controller_update_early_returns();
  test_controller_update_bounds_callback_arguments();
  test_controller_update_interpolation_is_unconditional();
  test_controller_update_limits_long_current_offset();
  test_controller_update_owner_reset_publishes_zero();
  test_controller_update_limited_projection_operands();
  test_offset_rescale_uses_ordered_comparison();
  test_quarter_turn_sign_follows_comiss_jbe();
  test_quarter_turn_nan_skips_rotate_guard();
  test_lower_bound_argument_order_is_out_then_key();
  test_raycast_receives_eight_stack_words();
  test_controller_update_ray_query_record_layout();
  test_blend_slot_returns_bool();
  test_controller_update_quarter_turn_sign();
  test_controller_update_orientation_row_uses_basis();
  test_controller_update_normalize_epsilon_is_injected();
  test_controller_update_look_direction_row_argument();
  test_controller_update_follow_ground_gate();
  test_controller_update_creep_clamp();
  test_controller_update_negative_dt_wraps();
  test_controller_update_smoothing_copy_path();
  std::printf("editor runtime wave7 model tests passed\n");
  return 0;
}

#undef PKG_W7_TEST_CDECL
#undef PKG_W7_TEST_THISCALL
