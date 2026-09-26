#include "camera_wave7.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_CAMERA_CDECL __cdecl
#define PKG_CAMERA_THISCALL __thiscall
#define PKG_CAMERA_FASTCALL __fastcall
#else
#define PKG_CAMERA_CDECL __attribute__((cdecl))
#define PKG_CAMERA_THISCALL __attribute__((thiscall))
#define PKG_CAMERA_FASTCALL __attribute__((fastcall))
#endif

namespace openspore::reconstruction::pkg_camera_wave7 {

CameraManagerPorts g_camera_manager_ports{};
CameraRayPorts g_camera_ray_ports{};
CellGlobalsPorts g_cell_globals_ports{
    reinterpret_cast<const OpaqueWide*>(0x014824a4u), nullptr, nullptr};
CellCameraPorts g_cell_camera_ports{};

namespace {

OpaqueMessageNode* next_bucket(OpaqueMessageRegistry& registry,
                               std::size_t bucket) {
  while (registry.buckets_004[bucket] == nullptr) {
    ++bucket;
  }
  return registry.buckets_004[bucket];
}

}

extern "C" OpaqueCamera* PKG_CAMERA_THISCALL camera_manager_set_active_007c64c0(
    OpaqueCameraManager* manager, OpaqueWord key) {
  OpaqueMessageRegistry& registry = manager->messages_060;
  std::size_t bucket = 0;
  OpaqueMessageNode* node = next_bucket(registry, bucket);
  OpaqueMessageNode* const sentinel =
      registry.buckets_004[registry.bucket_count_008];
  if (node == sentinel) {
    return nullptr;
  }

  for (;;) {
    if (node == sentinel) {
      return nullptr;
    }
    if (node->key_004 == key) {
      return node->value_000;
    }
    node = node->next_008;
    if (node != nullptr) {
      continue;
    }
    ++bucket;
    node = next_bucket(registry, bucket);
  }
}

extern "C" bool PKG_CAMERA_THISCALL
camera_manager_dispose_007c6e50(OpaqueCameraManager* manager) {
  if (manager->disposed_00c == 0) {
    return true;
  }
  manager->disposed_00c = 0;

  OpaqueAppSystem* app_system = g_camera_manager_ports.app_system_get();
  if (app_system != nullptr) {
    app_system->vtable->release_2c(app_system, manager, 0x00f62defu,
                                   0xffffd8f1u);
  }

  OpaqueIdGenerator* id_generator = g_camera_manager_ports.id_generator_get();
  if (manager->object_010 != manager->object_end_014) {
    if (id_generator != nullptr) {
      id_generator->vtable->notify_1c(id_generator, manager->object_010);
    }
    *static_cast<std::uint8_t*>(manager->object_010) = 0;
    manager->object_end_014 = manager->object_010;
  }

  g_camera_manager_ports.message_registry_clear(
      &manager->messages_060, manager->messages_060.buckets_004,
      manager->messages_060.bucket_count_008);

  const std::uintptr_t begin_address =
      reinterpret_cast<std::uintptr_t>(manager->cameras_080.begin_000);
  const std::uintptr_t end_address =
      reinterpret_cast<std::uintptr_t>(manager->cameras_080.end_004);
  const std::size_t camera_count = (end_address - begin_address) >> 2u;
  for (std::size_t index = 0; index < camera_count; ++index) {
    OpaqueCamera* camera = manager->cameras_080.begin_000[index];
    if (camera != nullptr) {
      camera->vtable->dispose_14(camera);
    }
  }

  g_camera_manager_ports.camera_range_erase(&manager->cameras_080,
                                            manager->cameras_080.begin_000,
                                            manager->cameras_080.end_004);
  manager->active_index_0a8 = 0;
  g_camera_manager_ports.camera_range_erase(&manager->cameras_080,
                                            manager->cameras_080.begin_000,
                                            manager->cameras_080.end_004);
  return true;
}

extern "C" void PKG_CAMERA_THISCALL camera_light_origin_helper_007c4900(
    OpaqueViewer* viewer, OpaqueVector* direction, OpaqueVector* origin) {
  OpaqueLightingManager* lighting_manager =
      g_camera_ray_ports.lighting_manager_get();
  OpaqueLightingWorld* lighting_world =
      lighting_manager->vtable->get_world_1c(lighting_manager);
  g_camera_ray_ports.camera_to_point(
      viewer, static_cast<float>(lighting_world->screen_x_008),
      static_cast<float>(lighting_world->screen_y_00c), direction, origin);
}

extern "C" OpaqueCellGlobalsResource* PKG_CAMERA_CDECL
cell_get_globals_data_00e4ce20() {
  g_cell_globals_ports.release_cell_game(g_cell_globals_ports.cell_game_name);
  return g_cell_globals_ports.fetch_cell_globals();
}

extern "C" void PKG_CAMERA_CDECL
cell_move_player_to_mouse_position_00e5b790(float delta_time) {
  OpaqueCellGame* game = g_cell_camera_ports.cell_game;
  if (game->lock_5158 != 0) {
    return;
  }

  OpaqueCellObject* player = g_cell_camera_ports.player_lookup(
      &game->pool_01c, game->avatar_index_411c);
  if (player == nullptr) {
    return;
  }

  g_cell_camera_ports.per_frame(delta_time);

  OpaqueDataReference* reference = nullptr;
  g_cell_camera_ports.reference_init(&reference);
  OpaqueCameraMode* camera_mode =
      g_cell_camera_ports.resolve_reference_00e823a0(
          g_cell_camera_ports.global_cell_reference_015a758c, &reference);
  const std::int32_t mode = camera_mode->mode_d4;
  g_cell_camera_ports.reference_release(&reference);

  OpaqueCellUI* ui = g_cell_camera_ports.cell_ui;
  if (mode >= 0) {
    if (mode < 2) {
      const int material = g_cell_camera_ports.material_check();
      if (material != 0 || ui->flag_24 != 0) {
        goto movement;
      }
      if (ui->flag_26 == 0) {
        return;
      }
    } else if (mode == 2) {
      if (g_cell_camera_ports.material_check() != 0) {
        goto movement;
      }
      if (ui->flag_26 == 0) {
        return;
      }
    } else {
      goto movement;
    }
  }

movement:
  OpaqueRenderer* renderer = g_cell_camera_ports.renderer_get();
  OpaqueViewer* viewer = renderer->vtable->layer_58(renderer);
  OpaqueVector direction{};
  OpaqueVector origin{};
  camera_light_origin_helper_007c4900(viewer, &direction, &origin);

  const MovementPlane& plane = g_cell_camera_ports.movement_plane;
  float denominator = direction.y * plane.normal_y;
  denominator += direction.z * plane.normal_z;
  denominator += direction.x * plane.normal_x;
  if (denominator == 0.0F) {
    return;
  }

  float point_dot = plane.point_y * plane.normal_y;
  point_dot += plane.point_z * plane.normal_z;
  point_dot += plane.point_x * plane.normal_x;
  point_dot = -point_dot;

  float numerator = origin.y * plane.normal_y;
  numerator += origin.z * plane.normal_z;
  numerator += origin.x * plane.normal_x;
  numerator += point_dot;
  float distance = numerator / denominator;
  distance = -distance;
  if (!(distance >= 0.0F)) {
    return;
  }

  player->moving_flag_004 = 0;
  const float scaled_x = direction.x * distance;
  const float scaled_y = direction.y * distance;
  const float scaled_z = direction.z * distance;
  player->target_008 = origin.x + scaled_x;
  player->target_00c = origin.y + scaled_y;
  player->target_010 = origin.z + scaled_z;
  game->serializable_5190->moving_e0 = 1;

  const OpaqueVector travel{
      -(player->target_008 - player->position_04c),
      -(player->target_00c - player->position_050),
      -(player->target_010 - player->position_054),
  };
  g_cell_camera_ports.orientation(&player->orientation_014, &travel,
                                  &plane.normal_x);
}

}
