#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <string>
#include <vector>

#include "camera_wave7.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#define PKG_TEST_FASTCALL __fastcall
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#define PKG_TEST_FASTCALL __attribute__((fastcall))
#endif

namespace {

using namespace openspore::reconstruction::pkg_camera_wave7;

int failures = 0;

struct Fixture {
  OpaqueCameraManager manager{};
  OpaqueCamera camera_a{};
  OpaqueCamera camera_b{};
  OpaqueCameraVTable camera_vtable{};
  OpaqueMessageNode message_a{};
  OpaqueMessageNode message_b{};
  OpaqueMessageNode sentinel{};
  OpaqueMessageNode* message_buckets[3]{};
  OpaqueCamera* camera_slots[3]{};
  OpaqueAppSystem app_system{};
  OpaqueAppSystemVTable app_vtable{};
  OpaqueIdGenerator id_generator{};
  OpaqueIdGeneratorVTable id_vtable{};
  std::uint8_t object_storage[2]{};
  OpaqueViewer viewer{};
  OpaqueLightingManager lighting_manager{};
  OpaqueLightingManagerVTable lighting_vtable{};
  OpaqueLightingWorld lighting_world{};
  OpaqueRenderer renderer{};
  OpaqueRendererVTable renderer_vtable{};
  OpaqueCellGame game{};
  OpaqueCellUI ui{};
  OpaqueCellObject player{};
  OpaqueCellObject* player_lookup_result = nullptr;
  OpaqueSerializableData serializable{};
  OpaqueDataReference reference{};
  OpaqueCellGlobalsResource globals{};
  OpaqueVector direction{};
  OpaqueVector origin{};
  OpaqueVector travel{};
  MovementPlane plane{};
  OpaquePool pool_storage{};
  OpaqueWord pool_words[1]{};
  int material_result = 0;
  int material_calls = 0;
  int range_erase_calls = 0;
  float last_delta = 0.0F;
  std::vector<std::string> trace;
};

Fixture* current_fixture = nullptr;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void check_trace(const Fixture& fixture,
                 std::initializer_list<const char*> expected) {
  check(fixture.trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    if (index < fixture.trace.size()) {
      check(fixture.trace[index] == value);
    }
    ++index;
  }
}

std::uint32_t bits(float value) {
  std::uint32_t result = 0;
  std::memcpy(&result, &value, sizeof(result));
  return result;
}

void check_bits(float actual, float expected) {
  check(bits(actual) == bits(expected));
}

OpaqueAppSystem* PKG_TEST_CDECL app_system_get() {
  current_fixture->trace.emplace_back("app-system-get");
  return &current_fixture->app_system;
}

void PKG_TEST_THISCALL release_app(OpaqueAppSystem* system,
                                   OpaqueCameraManager* manager,
                                   OpaqueWord first, OpaqueWord second) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("app-release");
  check(system == &fixture.app_system);
  check(manager == &fixture.manager);
  check(first == 0x00f62defu);
  check(second == 0xffffd8f1u);
}

OpaqueIdGenerator* PKG_TEST_CDECL id_generator_get() {
  current_fixture->trace.emplace_back("id-generator-get");
  return &current_fixture->id_generator;
}

OpaqueIdGenerator* PKG_TEST_CDECL id_generator_get_null() {
  current_fixture->trace.emplace_back("id-generator-get-null");
  return nullptr;
}

void PKG_TEST_THISCALL notify_id(OpaqueIdGenerator* generator, void* object) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("id-notify");
  check(generator == &fixture.id_generator);
  check(object == fixture.manager.object_010);
}

void PKG_TEST_THISCALL clear_messages(OpaqueMessageRegistry* registry,
                                      OpaqueMessageNode** buckets,
                                      OpaqueWord count) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("message-clear");
  check(registry == &fixture.manager.messages_060);
  check(buckets == fixture.message_buckets);
  check(count == 2u);
  fixture.message_buckets[0] = nullptr;
  fixture.message_buckets[1] = nullptr;
}

void PKG_TEST_THISCALL dispose_camera(OpaqueCamera* camera) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back(camera == &fixture.camera_a ? "camera-a-dispose"
                                                         : "camera-b-dispose");
}

void PKG_TEST_THISCALL erase_camera_range(OpaqueCameraVector* vector,
                                          OpaqueCamera** begin,
                                          OpaqueCamera** end) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("camera-range-erase");
  check(vector == &fixture.manager.cameras_080);
  check(begin == fixture.manager.cameras_080.begin_000);
  if (fixture.range_erase_calls == 0) {
    check(end == fixture.camera_slots + 3);
    fixture.manager.cameras_080.end_004 = begin;
  } else {
    check(end == begin);
  }
  ++fixture.range_erase_calls;
}

void verify_camera_lookup() {
  Fixture fixture{};
  fixture.message_buckets[0] = nullptr;
  fixture.message_buckets[1] = &fixture.message_a;
  fixture.message_buckets[2] = &fixture.sentinel;
  fixture.message_a.value_000 = &fixture.camera_a;
  fixture.message_a.key_004 = 17u;
  fixture.message_a.next_008 = &fixture.message_b;
  fixture.message_b.value_000 = &fixture.camera_b;
  fixture.message_b.key_004 = 42u;
  fixture.sentinel.value_000 = &fixture.camera_a;
  fixture.manager.messages_060.buckets_004 = fixture.message_buckets;
  fixture.manager.messages_060.bucket_count_008 = 2u;
  fixture.manager.active_index_0a8 = 9;

  check(camera_manager_set_active_007c64c0(&fixture.manager, 17u) ==
        &fixture.camera_a);
  check(camera_manager_set_active_007c64c0(&fixture.manager, 42u) ==
        &fixture.camera_b);
  check(camera_manager_set_active_007c64c0(&fixture.manager, 99u) == nullptr);
  check(fixture.manager.active_index_0a8 == 9);

  fixture.message_buckets[0] = &fixture.sentinel;
  fixture.manager.messages_060.bucket_count_008 = 0u;
  check(camera_manager_set_active_007c64c0(&fixture.manager, 17u) == nullptr);
}

void verify_camera_dispose() {
  Fixture fixture{};
  current_fixture = &fixture;
  fixture.manager.disposed_00c = 1;
  fixture.manager.object_010 = fixture.object_storage;
  fixture.manager.object_end_014 = fixture.object_storage + 1;
  fixture.object_storage[0] = 0xa5u;
  fixture.manager.messages_060.buckets_004 = fixture.message_buckets;
  fixture.manager.messages_060.bucket_count_008 = 2u;
  fixture.message_buckets[0] = &fixture.message_a;
  fixture.message_buckets[1] = &fixture.message_b;
  fixture.message_buckets[2] = &fixture.sentinel;
  fixture.manager.cameras_080.begin_000 = fixture.camera_slots;
  fixture.manager.cameras_080.end_004 = fixture.camera_slots + 3;
  fixture.manager.cameras_080.capacity_008 = fixture.camera_slots + 3;
  fixture.camera_slots[0] = &fixture.camera_a;
  fixture.camera_slots[1] = nullptr;
  fixture.camera_slots[2] = &fixture.camera_b;
  fixture.camera_vtable.dispose_14 = dispose_camera;
  fixture.camera_a.vtable = &fixture.camera_vtable;
  fixture.camera_b.vtable = &fixture.camera_vtable;
  fixture.app_vtable.release_2c = release_app;
  fixture.app_system.vtable = &fixture.app_vtable;
  fixture.id_vtable.notify_1c = notify_id;
  fixture.id_generator.vtable = &fixture.id_vtable;
  fixture.manager.active_index_0a8 = 7;

  g_camera_manager_ports.app_system_get = app_system_get;
  g_camera_manager_ports.id_generator_get = id_generator_get;
  g_camera_manager_ports.message_registry_clear = clear_messages;
  g_camera_manager_ports.camera_range_erase = erase_camera_range;

  check(camera_manager_dispose_007c6e50(&fixture.manager));
  check_trace(fixture,
              {"app-system-get", "app-release", "id-generator-get", "id-notify",
               "message-clear", "camera-a-dispose", "camera-b-dispose",
               "camera-range-erase", "camera-range-erase"});
  check(fixture.manager.disposed_00c == 0);
  check(fixture.manager.object_end_014 == fixture.manager.object_010);
  check(fixture.object_storage[0] == 0);
  check(fixture.manager.active_index_0a8 == 0);
  check(fixture.range_erase_calls == 2);

  fixture.trace.clear();
  check(camera_manager_dispose_007c6e50(&fixture.manager));
  check(fixture.trace.empty());
  g_camera_manager_ports = CameraManagerPorts{};
  current_fixture = nullptr;
}

void verify_camera_dispose_without_id_generator() {
  Fixture fixture{};
  current_fixture = &fixture;
  fixture.manager.disposed_00c = 1;
  fixture.manager.object_010 = fixture.object_storage;
  fixture.manager.object_end_014 = fixture.object_storage + 1;
  fixture.object_storage[0] = 0xa5u;
  fixture.manager.messages_060.buckets_004 = fixture.message_buckets;
  fixture.manager.messages_060.bucket_count_008 = 2u;
  fixture.manager.cameras_080.begin_000 = fixture.camera_slots;
  fixture.manager.cameras_080.end_004 = fixture.camera_slots + 3;
  fixture.manager.cameras_080.capacity_008 = fixture.camera_slots + 3;
  fixture.app_vtable.release_2c = release_app;
  fixture.app_system.vtable = &fixture.app_vtable;
  fixture.manager.active_index_0a8 = 6;

  g_camera_manager_ports.app_system_get = app_system_get;
  g_camera_manager_ports.id_generator_get = id_generator_get_null;
  g_camera_manager_ports.message_registry_clear = clear_messages;
  g_camera_manager_ports.camera_range_erase = erase_camera_range;

  check(camera_manager_dispose_007c6e50(&fixture.manager));
  check_trace(fixture,
              {"app-system-get", "app-release", "id-generator-get-null",
               "message-clear", "camera-range-erase", "camera-range-erase"});
  check(fixture.manager.disposed_00c == 0);
  check(fixture.manager.object_end_014 == fixture.manager.object_010);
  check(fixture.object_storage[0] == 0);
  check(fixture.manager.active_index_0a8 == 0);
  g_camera_manager_ports = CameraManagerPorts{};
  current_fixture = nullptr;
}

OpaqueLightingManager* PKG_TEST_CDECL lighting_manager_get() {
  current_fixture->trace.emplace_back("lighting-manager-get");
  return &current_fixture->lighting_manager;
}

OpaqueLightingWorld* PKG_TEST_THISCALL
get_lighting_world(OpaqueLightingManager* manager) {
  current_fixture->trace.emplace_back("lighting-world");
  check(manager == &current_fixture->lighting_manager);
  return &current_fixture->lighting_world;
}

void PKG_TEST_THISCALL camera_to_point(OpaqueViewer* viewer, float screen_x,
                                       float screen_y, OpaqueVector* direction,
                                       OpaqueVector* origin) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("camera-to-point");
  check(viewer == &fixture.viewer);
  check_bits(screen_x, fixture.lighting_world.screen_x_008);
  check_bits(screen_y, fixture.lighting_world.screen_y_00c);
  *direction = fixture.direction;
  *origin = fixture.origin;
}

void verify_camera_origin_helper() {
  Fixture fixture{};
  current_fixture = &fixture;
  fixture.lighting_world.screen_x_008 = 640;
  fixture.lighting_world.screen_y_00c = 480;
  fixture.lighting_vtable.get_world_1c = get_lighting_world;
  fixture.lighting_manager.vtable = &fixture.lighting_vtable;
  fixture.direction = OpaqueVector{1.0F, 2.0F, 3.0F};
  fixture.origin = OpaqueVector{4.0F, 5.0F, 6.0F};
  g_camera_ray_ports.lighting_manager_get = lighting_manager_get;
  g_camera_ray_ports.camera_to_point = camera_to_point;

  OpaqueVector direction{};
  OpaqueVector origin{};
  camera_light_origin_helper_007c4900(&fixture.viewer, &direction, &origin);
  check_trace(fixture,
              {"lighting-manager-get", "lighting-world", "camera-to-point"});
  check_bits(direction.x, fixture.direction.x);
  check_bits(direction.y, fixture.direction.y);
  check_bits(direction.z, fixture.direction.z);
  check_bits(origin.x, fixture.origin.x);
  check_bits(origin.y, fixture.origin.y);
  check_bits(origin.z, fixture.origin.z);
  g_camera_ray_ports = CameraRayPorts{};
  current_fixture = nullptr;
}

void PKG_TEST_CDECL release_cell_game(const OpaqueWide* name) {
  current_fixture->trace.emplace_back("release-cell-game");
  check(name == reinterpret_cast<const OpaqueWide*>(0x014824a4u));
}

OpaqueCellGlobalsResource* PKG_TEST_CDECL fetch_cell_globals() {
  current_fixture->trace.emplace_back("fetch-cell-globals");
  return &current_fixture->globals;
}

void verify_cell_globals_data() {
  Fixture fixture{};
  current_fixture = &fixture;
  g_cell_globals_ports.cell_game_name =
      reinterpret_cast<const OpaqueWide*>(0x014824a4u);
  g_cell_globals_ports.release_cell_game = release_cell_game;
  g_cell_globals_ports.fetch_cell_globals = fetch_cell_globals;
  check(cell_get_globals_data_00e4ce20() == &fixture.globals);
  check_trace(fixture, {"release-cell-game", "fetch-cell-globals"});
  g_cell_globals_ports = CellGlobalsPorts{
      reinterpret_cast<const OpaqueWide*>(0x014824a4u), nullptr, nullptr};
  current_fixture = nullptr;
}

OpaqueCellObject* PKG_TEST_THISCALL lookup_player(OpaquePool* pool,
                                                  OpaqueWord index) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("player-lookup");
  check(pool == &fixture.game.pool_01c);
  check(index == fixture.game.avatar_index_411c);
  return fixture.player_lookup_result;
}

void PKG_TEST_CDECL per_frame(float delta_time) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("per-frame");
  fixture.last_delta = delta_time;
}

void PKG_TEST_FASTCALL init_reference(OpaqueDataReference** output) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("reference-init");
  *output = nullptr;
}

OpaqueCameraMode* PKG_TEST_CDECL resolve_reference(
    OpaqueDataReference* reference, OpaqueDataReference** output) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("camera-mode");
  check(reference == &fixture.reference);
  check(output != nullptr);
  ++fixture.reference.reference_count_00c;
  *output = &fixture.reference;
  return &fixture.globals.camera_mode_014;
}

void PKG_TEST_FASTCALL release_reference(OpaqueDataReference** output) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("reference-release");
  if (*output != nullptr) {
    --(*output)->reference_count_00c;
  }
}

int PKG_TEST_CDECL material_check() {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("material-check");
  ++fixture.material_calls;
  return fixture.material_result;
}

OpaqueRenderer* PKG_TEST_CDECL renderer_get() {
  current_fixture->trace.emplace_back("renderer-get");
  return &current_fixture->renderer;
}

OpaqueViewer* PKG_TEST_THISCALL renderer_layer(OpaqueRenderer* renderer) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("renderer-layer");
  check(renderer == &fixture.renderer);
  return &fixture.viewer;
}

void PKG_TEST_CDECL orientation(float* output, const OpaqueVector* travel,
                                const float* normal) {
  Fixture& fixture = *current_fixture;
  fixture.trace.emplace_back("orientation");
  fixture.travel = *travel;
  check(output == &fixture.player.orientation_014);
  check(normal == &g_cell_camera_ports.movement_plane.normal_x);
  output[0] = 7.0F;
  output[1] = 8.0F;
  output[2] = 9.0F;
  output[3] = 10.0F;
}

void configure_movement(Fixture& fixture, std::int32_t mode,
                        int material_result) {
  current_fixture = &fixture;
  fixture.game.avatar_index_411c = 3u;
  fixture.game.pool_01c.base_000 = fixture.pool_words;
  fixture.game.pool_01c.count_010 = 1u;
  fixture.game.pool_01c.stride_014 = 4u;
  fixture.game.serializable_5190 = &fixture.serializable;
  fixture.globals.camera_mode_014.mode_d4 = mode;
  fixture.material_result = material_result;
  fixture.plane.normal_x = 0.0F;
  fixture.plane.normal_y = 1.0F;
  fixture.plane.normal_z = 0.0F;
  fixture.plane.point_x = 0.0F;
  fixture.plane.point_y = 0.0F;
  fixture.plane.point_z = 0.0F;
  fixture.direction = OpaqueVector{4.0F, -2.0F, 6.0F};
  fixture.origin = OpaqueVector{1.0F, 2.0F, 3.0F};
  fixture.player.position_04c = 10.0F;
  fixture.player.position_050 = 20.0F;
  fixture.player.position_054 = 30.0F;
  fixture.player.target_008 = 1.0F;
  fixture.player.target_00c = 2.0F;
  fixture.player.target_010 = 3.0F;
  fixture.player.moving_flag_004 = 9u;
  fixture.serializable.moving_e0 = 0u;
  fixture.reference = OpaqueDataReference{};
  fixture.renderer_vtable.layer_58 = renderer_layer;
  fixture.renderer.vtable = &fixture.renderer_vtable;
  fixture.lighting_vtable.get_world_1c = get_lighting_world;
  fixture.lighting_manager.vtable = &fixture.lighting_vtable;
  fixture.lighting_world.screen_x_008 = 320;
  fixture.lighting_world.screen_y_00c = 240;

  g_cell_camera_ports.cell_game = &fixture.game;
  g_cell_camera_ports.cell_ui = &fixture.ui;
  g_cell_camera_ports.global_cell_reference_015a758c = &fixture.reference;
  g_cell_camera_ports.movement_plane = fixture.plane;
  g_cell_camera_ports.player_lookup = lookup_player;
  g_cell_camera_ports.per_frame = per_frame;
  g_cell_camera_ports.reference_init = init_reference;
  g_cell_camera_ports.resolve_reference_00e823a0 = resolve_reference;
  g_cell_camera_ports.reference_release = release_reference;
  g_cell_camera_ports.material_check = material_check;
  g_cell_camera_ports.renderer_get = renderer_get;
  g_cell_camera_ports.orientation = orientation;
  g_camera_ray_ports.lighting_manager_get = lighting_manager_get;
  g_camera_ray_ports.camera_to_point = camera_to_point;
}

void reset_movement_ports() {
  g_cell_camera_ports = CellCameraPorts{};
  g_camera_ray_ports = CameraRayPorts{};
  current_fixture = nullptr;
}

void verify_movement_gates() {
  struct GateCase {
    std::int32_t mode;
    int material;
    std::uint8_t flag24;
    std::uint8_t flag26;
    bool proceeds;
    int material_calls;
  };

  const GateCase cases[] = {
      {-1, 1, 0, 0, true, 0}, {0, 0, 0, 0, false, 1}, {0, 0, 1, 0, true, 1},
      {0, 1, 0, 0, true, 1},  {2, 0, 0, 0, false, 1}, {2, 0, 0, 1, true, 1},
      {2, 1, 0, 0, true, 1},  {3, 1, 0, 0, true, 0},
  };

  for (const GateCase& gate : cases) {
    Fixture fixture{};
    fixture.player_lookup_result = &fixture.player;
    fixture.ui.flag_24 = gate.flag24;
    fixture.ui.flag_26 = gate.flag26;
    configure_movement(fixture, gate.mode, gate.material);
    cell_move_player_to_mouse_position_00e5b790(0.25F);
    check(fixture.material_calls == gate.material_calls);
    check(fixture.last_delta ==
          (gate.proceeds || gate.mode != -1 ? 0.25F : 0.0F));
    check(fixture.reference.reference_count_00c == 0u);
    if (gate.proceeds) {
      check_bits(fixture.player.target_008, 5.0F);
      check_bits(fixture.player.target_00c, 0.0F);
      check_bits(fixture.player.target_010, 9.0F);
      check(fixture.serializable.moving_e0 == 1u);
      check(fixture.player.moving_flag_004 == 0u);
      check_bits(fixture.travel.x, 5.0F);
      check_bits(fixture.travel.y, 20.0F);
      check_bits(fixture.travel.z, 21.0F);
      check_bits(fixture.player.orientation_014, 7.0F);
      check_bits(fixture.player.orientation_018, 8.0F);
      check_bits(fixture.player.orientation_01c, 9.0F);
      check_bits(fixture.player.orientation_020, 10.0F);
    } else {
      check_bits(fixture.player.target_008, 1.0F);
      check_bits(fixture.player.target_00c, 2.0F);
      check_bits(fixture.player.target_010, 3.0F);
      check(fixture.serializable.moving_e0 == 0u);
    }
    reset_movement_ports();
  }
}

void verify_movement_rounding_order() {
  Fixture fixture{};
  fixture.player_lookup_result = &fixture.player;
  configure_movement(fixture, -1, 0);
  fixture.plane.normal_x = 0.25F;
  fixture.plane.normal_y = 0.5F;
  fixture.plane.normal_z = 0.75F;
  fixture.plane.point_x = 1.25F;
  fixture.plane.point_y = 2.5F;
  fixture.plane.point_z = 3.75F;
  fixture.direction = OpaqueVector{0.125F, -0.75F, 1.5F};
  fixture.origin = OpaqueVector{0.5F, 1.25F, 2.0F};
  g_cell_camera_ports.movement_plane = fixture.plane;
  cell_move_player_to_mouse_position_00e5b790(1.0F);
  check_bits(fixture.player.target_008, 0.8400000333786011F);
  check_bits(fixture.player.target_00c, -0.7899999618530273F);
  check_bits(fixture.player.target_010, 6.079999923706055F);
  check(fixture.serializable.moving_e0 == 1u);
  reset_movement_ports();
}

void verify_movement_guards_and_plane() {
  Fixture locked{};
  locked.player_lookup_result = &locked.player;
  configure_movement(locked, -1, 0);
  locked.game.lock_5158 = 1u;
  cell_move_player_to_mouse_position_00e5b790(1.0F);
  check(locked.trace.empty());

  Fixture missing{};
  configure_movement(missing, -1, 0);
  missing.player_lookup_result = nullptr;
  cell_move_player_to_mouse_position_00e5b790(1.0F);
  check_trace(missing, {"player-lookup"});

  Fixture parallel{};
  parallel.player_lookup_result = &parallel.player;
  configure_movement(parallel, -1, 0);
  parallel.direction = OpaqueVector{4.0F, 0.0F, 6.0F};
  cell_move_player_to_mouse_position_00e5b790(1.0F);
  check_bits(parallel.player.target_008, 1.0F);
  check_bits(parallel.player.target_00c, 2.0F);
  check_bits(parallel.player.target_010, 3.0F);
  check(parallel.serializable.moving_e0 == 0u);
  check(parallel.reference.reference_count_00c == 0u);

  Fixture backward{};
  backward.player_lookup_result = &backward.player;
  configure_movement(backward, -1, 0);
  backward.direction = OpaqueVector{4.0F, 2.0F, 6.0F};
  cell_move_player_to_mouse_position_00e5b790(1.0F);
  check_bits(backward.player.target_008, 1.0F);
  check_bits(backward.player.target_00c, 2.0F);
  check_bits(backward.player.target_010, 3.0F);
  check(backward.serializable.moving_e0 == 0u);
  reset_movement_ports();
}

}

int main() {
  verify_camera_lookup();
  verify_camera_dispose();
  verify_camera_dispose_without_id_generator();
  verify_camera_origin_helper();
  verify_cell_globals_data();
  verify_movement_gates();
  verify_movement_rounding_order();
  verify_movement_guards_and_plane();
  return failures == 0 ? 0 : 1;
}
