#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-camera-wave7 reconstruction requires an x86-32 target"
#endif

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

static_assert(sizeof(void*) == 4, "pkg-camera-wave7 requires 32-bit pointers");
static_assert(sizeof(float) == 4, "pkg-camera-wave7 requires 32-bit floats");

using OpaqueWord = std::uint32_t;
using OpaqueWide = std::uint16_t;

struct OpaqueCamera;
struct OpaqueCameraManager;
struct OpaqueMessageNode;
struct OpaqueMessageRegistry;
struct OpaqueCameraVector;
struct OpaqueAppSystem;
struct OpaqueIdGenerator;
struct OpaqueViewer;
struct OpaqueLightingManager;
struct OpaqueLightingWorld;
struct OpaqueRenderer;
struct OpaqueCellObject;
struct OpaqueCellGame;
struct OpaqueCellUI;
struct OpaqueDataReference;
struct OpaqueCellGlobalsResource;
struct OpaqueCameraMode;

struct OpaqueCameraManagerVTable {
  void* slots_00[21]{};
};

struct OpaqueCameraVTable {
  void* slots_00[5]{};
  void(PKG_CAMERA_THISCALL* dispose_14)(OpaqueCamera*) = nullptr;
  void* slots_18[2]{};
};

struct OpaqueCamera {
  OpaqueCameraVTable* vtable = nullptr;
  OpaqueWord opaque_004 = 0;
};

struct OpaqueMessageNode {
  OpaqueCamera* value_000 = nullptr;
  OpaqueWord key_004 = 0;
  OpaqueMessageNode* next_008 = nullptr;
};

struct OpaqueMessageRegistry {
  OpaqueWord opaque_000 = 0;
  OpaqueMessageNode** buckets_004 = nullptr;
  OpaqueWord bucket_count_008 = 0;
  OpaqueWord opaque_00c[5]{};
};

struct OpaqueCameraVector {
  OpaqueCamera** begin_000 = nullptr;
  OpaqueCamera** end_004 = nullptr;
  OpaqueCamera** capacity_008 = nullptr;
  OpaqueWord opaque_00c = 0;
};

struct OpaqueCameraManager {
  OpaqueCameraManagerVTable* vtable_000 = nullptr;
  OpaqueWord opaque_004[2]{};
  std::uint8_t disposed_00c = 0;
  std::uint8_t opaque_00d[3]{};
  void* object_010 = nullptr;
  void* object_end_014 = nullptr;
  std::uint8_t opaque_018[0x48]{};
  OpaqueMessageRegistry messages_060{};
  OpaqueCameraVector cameras_080{};
  std::uint8_t opaque_090[0x18]{};
  std::int32_t active_index_0a8 = 0;
  OpaqueWord opaque_0ac = 0;
};

static_assert(offsetof(OpaqueMessageRegistry, buckets_004) == 0x04,
              "message bucket pointer offset");
static_assert(offsetof(OpaqueMessageRegistry, bucket_count_008) == 0x08,
              "message bucket count offset");
static_assert(offsetof(OpaqueCameraManager, messages_060) == 0x60,
              "camera message registry offset");
static_assert(offsetof(OpaqueCameraManager, cameras_080) == 0x80,
              "camera vector offset");
static_assert(offsetof(OpaqueCameraManager, active_index_0a8) == 0xa8,
              "active camera index offset");
static_assert(sizeof(OpaqueMessageRegistry) == 0x20, "message registry size");
static_assert(sizeof(OpaqueCameraVector) == 0x10, "camera vector size");

struct OpaqueAppSystemVTable {
  void* slots_00[11]{};
  void(PKG_CAMERA_THISCALL* release_2c)(OpaqueAppSystem*, OpaqueCameraManager*,
                                        OpaqueWord, OpaqueWord) = nullptr;
};

struct OpaqueAppSystem {
  OpaqueAppSystemVTable* vtable = nullptr;
  OpaqueWord opaque_004 = 0;
};

struct OpaqueIdGeneratorVTable {
  void* slots_00[7]{};
  void(PKG_CAMERA_THISCALL* notify_1c)(OpaqueIdGenerator*, void*) = nullptr;
};

struct OpaqueIdGenerator {
  OpaqueIdGeneratorVTable* vtable = nullptr;
  OpaqueWord opaque_004 = 0;
};

struct CameraManagerPorts {
  using AppSystemGet = OpaqueAppSystem*(PKG_CAMERA_CDECL*)();
  using IdGeneratorGet = OpaqueIdGenerator*(PKG_CAMERA_CDECL*)();
  using MessageRegistryClear = void(PKG_CAMERA_THISCALL*)(
      OpaqueMessageRegistry*, OpaqueMessageNode**, OpaqueWord);
  using CameraRangeErase = void(PKG_CAMERA_THISCALL*)(OpaqueCameraVector*,
                                                      OpaqueCamera**,
                                                      OpaqueCamera**);

  AppSystemGet app_system_get = nullptr;
  IdGeneratorGet id_generator_get = nullptr;
  MessageRegistryClear message_registry_clear = nullptr;
  CameraRangeErase camera_range_erase = nullptr;
};

extern CameraManagerPorts g_camera_manager_ports;

extern "C" OpaqueCamera* PKG_CAMERA_THISCALL camera_manager_set_active_007c64c0(
    OpaqueCameraManager* manager, OpaqueWord key);

extern "C" bool PKG_CAMERA_THISCALL
camera_manager_dispose_007c6e50(OpaqueCameraManager* manager);

struct OpaqueVector {
  float x = 0.0F;
  float y = 0.0F;
  float z = 0.0F;
};

struct OpaqueViewer {
  OpaqueWord opaque_000[4]{};
};

struct OpaqueLightingWorld {
  OpaqueWord opaque_000 = 0;
  OpaqueWord opaque_004 = 0;
  std::int32_t screen_x_008 = 0;
  std::int32_t screen_y_00c = 0;
};

struct OpaqueLightingManagerVTable {
  void* slots_00[7]{};
  OpaqueLightingWorld*(PKG_CAMERA_THISCALL* get_world_1c)(
      OpaqueLightingManager*) = nullptr;
};

struct OpaqueLightingManager {
  OpaqueLightingManagerVTable* vtable = nullptr;
  OpaqueWord opaque_004 = 0;
};

struct CameraRayPorts {
  using LightingManagerGet = OpaqueLightingManager*(PKG_CAMERA_CDECL*)();
  using CameraToPoint = void(PKG_CAMERA_THISCALL*)(OpaqueViewer*, float, float,
                                                   OpaqueVector*,
                                                   OpaqueVector*);

  LightingManagerGet lighting_manager_get = nullptr;
  CameraToPoint camera_to_point = nullptr;
};

extern CameraRayPorts g_camera_ray_ports;

extern "C" void PKG_CAMERA_THISCALL camera_light_origin_helper_007c4900(
    OpaqueViewer* viewer, OpaqueVector* direction, OpaqueVector* origin);

struct OpaqueDataReference {
  OpaqueWord opaque_000[3]{};
  OpaqueWord reference_count_00c = 0;
};

struct OpaqueCameraMode {
  std::uint8_t opaque_000[0xd4]{};
  std::int32_t mode_d4 = 0;
};

struct OpaqueCellGlobalsResource {
  std::uint8_t opaque_000[0x14]{};
  OpaqueCameraMode camera_mode_014{};
};

static_assert(offsetof(OpaqueCameraMode, mode_d4) == 0xd4,
              "camera mode field offset");
static_assert(sizeof(OpaqueDataReference) == 0x10, "data reference size");

struct CellGlobalsPorts {
  using ReleaseCellGame = void(PKG_CAMERA_CDECL*)(const OpaqueWide*);
  using FetchCellGlobals = OpaqueCellGlobalsResource*(PKG_CAMERA_CDECL*)();

  const OpaqueWide* cell_game_name = nullptr;
  ReleaseCellGame release_cell_game = nullptr;
  FetchCellGlobals fetch_cell_globals = nullptr;
};

extern CellGlobalsPorts g_cell_globals_ports;

extern "C" OpaqueCellGlobalsResource* PKG_CAMERA_CDECL
cell_get_globals_data_00e4ce20();

struct OpaquePool {
  OpaqueWord* base_000 = nullptr;
  OpaqueWord opaque_004[3]{};
  OpaqueWord count_010 = 0;
  OpaqueWord stride_014 = 0;
};

struct OpaqueCellObject {
  OpaqueWord index_000 = 0;
  std::uint8_t moving_flag_004 = 0;
  std::uint8_t opaque_005[3]{};
  float target_008 = 0.0F;
  float target_00c = 0.0F;
  float target_010 = 0.0F;
  float orientation_014 = 0.0F;
  float orientation_018 = 0.0F;
  float orientation_01c = 0.0F;
  float orientation_020 = 0.0F;
  std::uint8_t opaque_024[0x28]{};
  float position_04c = 0.0F;
  float position_050 = 0.0F;
  float position_054 = 0.0F;
};

static_assert(offsetof(OpaqueCellObject, moving_flag_004) == 0x04,
              "cell moving flag offset");
static_assert(offsetof(OpaqueCellObject, target_008) == 0x08,
              "cell target offset");
static_assert(offsetof(OpaqueCellObject, orientation_014) == 0x14,
              "cell orientation offset");
static_assert(offsetof(OpaqueCellObject, position_04c) == 0x4c,
              "cell current position offset");
static_assert(sizeof(OpaqueCellObject) == 0x58, "cell object size");

struct OpaqueSerializableData {
  std::uint8_t opaque_000[0xe0]{};
  std::uint8_t moving_e0 = 0;
};

struct OpaqueCellGame {
  std::uint8_t opaque_000[0x1c]{};
  OpaquePool pool_01c{};
  std::uint8_t opaque_034[0x411c - 0x34]{};
  OpaqueWord avatar_index_411c = 0;
  std::uint8_t opaque_4120[0x5158 - 0x4120]{};
  OpaqueWord lock_5158 = 0;
  std::uint8_t opaque_515c[0x5190 - 0x515c]{};
  OpaqueSerializableData* serializable_5190 = nullptr;
  std::uint8_t opaque_5194[0x51e4 - 0x5194]{};
};

static_assert(offsetof(OpaqueCellGame, pool_01c) == 0x1c, "cell pool offset");
static_assert(offsetof(OpaqueCellGame, avatar_index_411c) == 0x411c,
              "cell avatar index offset");
static_assert(offsetof(OpaqueCellGame, serializable_5190) == 0x5190,
              "cell serializable pointer offset");
static_assert(offsetof(OpaqueCellGame, lock_5158) == 0x5158,
              "cell lock offset");

struct OpaqueCellUI {
  std::uint8_t opaque_000[0x24]{};
  std::uint8_t flag_24 = 0;
  std::uint8_t opaque_25 = 0;
  std::uint8_t flag_26 = 0;
  std::uint8_t opaque_27 = 0;
};

struct OpaqueRendererVTable {
  void* slots_00[22]{};
  OpaqueViewer*(PKG_CAMERA_THISCALL* layer_58)(OpaqueRenderer*) = nullptr;
};

struct OpaqueRenderer {
  OpaqueRendererVTable* vtable = nullptr;
  OpaqueWord opaque_004 = 0;
};

struct MovementPlane {
  float normal_x = 0.0F;
  float normal_y = 0.0F;
  float normal_z = 0.0F;
  float point_x = 0.0F;
  float point_y = 0.0F;
  float point_z = 0.0F;
};

struct CellCameraPorts {
  using PlayerLookup = OpaqueCellObject*(PKG_CAMERA_THISCALL*)(OpaquePool*,
                                                               OpaqueWord);
  using PerFrame = void(PKG_CAMERA_CDECL*)(float);
  using ReferenceInit = void(PKG_CAMERA_FASTCALL*)(OpaqueDataReference**);
  using ResolveReference = OpaqueCameraMode*(
      PKG_CAMERA_CDECL*)(OpaqueDataReference*, OpaqueDataReference**);
  using ReferenceRelease = void(PKG_CAMERA_FASTCALL*)(OpaqueDataReference**);
  using MaterialCheck = int(PKG_CAMERA_CDECL*)();
  using RendererGet = OpaqueRenderer*(PKG_CAMERA_CDECL*)();
  using Orientation = void(PKG_CAMERA_CDECL*)(float*, const OpaqueVector*,
                                              const float*);

  OpaqueCellGame* cell_game = nullptr;
  OpaqueCellUI* cell_ui = nullptr;
  OpaqueDataReference* global_cell_reference_015a758c = nullptr;
  MovementPlane movement_plane{};
  PlayerLookup player_lookup = nullptr;
  PerFrame per_frame = nullptr;
  ReferenceInit reference_init = nullptr;
  ResolveReference resolve_reference_00e823a0 = nullptr;
  ReferenceRelease reference_release = nullptr;
  MaterialCheck material_check = nullptr;
  RendererGet renderer_get = nullptr;
  Orientation orientation = nullptr;
};

extern CellCameraPorts g_cell_camera_ports;

extern "C" void PKG_CAMERA_CDECL
cell_move_player_to_mouse_position_00e5b790(float delta_time);

}

#undef PKG_CAMERA_CDECL
#undef PKG_CAMERA_THISCALL
#undef PKG_CAMERA_FASTCALL
