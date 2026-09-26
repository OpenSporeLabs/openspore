#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "editor runtime wave7 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_W7_CDECL __cdecl
#define PKG_W7_THISCALL __thiscall
#else
#define PKG_W7_CDECL __attribute__((cdecl))
#define PKG_W7_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_runtime_wave7 {

static_assert(sizeof(void*) == 4, "editor runtime wave7 pointers are 32-bit");
static_assert(sizeof(float) == 4, "editor runtime wave7 scalars are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "editor runtime wave7 words are 32-bit");

using OpaqueWord = std::uint32_t;

struct Vector2 {
  float x = 0.0f;
  float y = 0.0f;
};

struct Vector3 {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

struct Vector4 {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float w = 0.0f;
};

static_assert(sizeof(Vector2) == 8, "editor vector2 layout");
static_assert(sizeof(Vector3) == 12, "editor vector3 layout");
static_assert(sizeof(Vector4) == 16, "editor vector4 layout");

struct OpaqueFixedBasis {
  float normalize_epsilon[3]{};
  float orientation[3]{};
  float projection[3]{};
};

static_assert(offsetof(OpaqueFixedBasis, normalize_epsilon) == 0x00,
              "normalize epsilon anchor");
static_assert(offsetof(OpaqueFixedBasis, orientation) == 0x0c,
              "orientation basis anchor");
static_assert(offsetof(OpaqueFixedBasis, projection) == 0x18,
              "projection basis anchor");
static_assert(sizeof(OpaqueFixedBasis) == 0x24, "fixed basis extent");

extern OpaqueFixedBasis* g_fixed_basis;

struct OpaqueCreatureVTable {
  void* slots_00[0x58 / 4]{};
  void(PKG_W7_THISCALL* get_bounds_58)(void*, void*, OpaqueWord, OpaqueWord,
                                       void*) = nullptr;
  bool(PKG_W7_THISCALL* get_blend_5c)(void*, void*, void*, void*) = nullptr;
};

static_assert(offsetof(OpaqueCreatureVTable, get_bounds_58) == 0x58,
              "creature bounds slot");
static_assert(offsetof(OpaqueCreatureVTable, get_blend_5c) == 0x5c,
              "creature blend slot");

struct OpaqueCreatureModel {
  std::uint32_t opaque_000[0x2d4 / 4]{};
  std::uint8_t smoothing_enabled_2d4 = 0;
};

static_assert(offsetof(OpaqueCreatureModel, smoothing_enabled_2d4) == 0x2d4,
              "creature model smoothing gate");

struct OpaqueCreature {
  OpaqueCreatureVTable* vtable = nullptr;
  Vector3 position{};
  Vector4 orientation{};
  std::uint32_t opaque_020[0x144 / 4]{};
  Vector3 smoothing{};
  std::uint32_t opaque_170[3]{};
  OpaqueCreatureModel* model_17c = nullptr;
};

static_assert(offsetof(OpaqueCreature, position) == 0x04, "creature position");
static_assert(offsetof(OpaqueCreature, orientation) == 0x10,
              "creature orientation row");
static_assert(offsetof(OpaqueCreature, smoothing) == 0x164,
              "creature smoothing origin");
static_assert(offsetof(OpaqueCreature, model_17c) == 0x17c,
              "creature model slot");

struct OpaqueRayQuery {
  std::uint32_t collision_mask[5]{};
  std::uint8_t flag_14 = 0;
  std::uint8_t flag_15 = 0;
};

static_assert(offsetof(OpaqueRayQuery, collision_mask) == 0x00,
              "ray query collision mask base");
static_assert(offsetof(OpaqueRayQuery, flag_14) == 0x14,
              "ray query first flag byte");
static_assert(offsetof(OpaqueRayQuery, flag_15) == 0x15,
              "ray query second flag byte");
static_assert(sizeof(OpaqueRayQuery) == 0x18, "ray query observed size");

struct OpaqueRaycastOut {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float w = 0.0f;
};

static_assert(sizeof(OpaqueRaycastOut) == 16, "raycast output record size");

struct OpaqueShadowWorldVTable {
  void* slots_00[0x24 / 4]{};
  std::uint32_t(PKG_W7_THISCALL* raycast_24)(void*, OpaqueRaycastOut*,
                                             const Vector3*, OpaqueWord,
                                             const OpaqueRayQuery*, OpaqueWord,
                                             OpaqueRaycastOut*, OpaqueWord,
                                             OpaqueWord) = nullptr;
};

static_assert(offsetof(OpaqueShadowWorldVTable, raycast_24) == 0x24,
              "shadow world raycast slot");

struct OpaqueShadowWorld {
  OpaqueShadowWorldVTable* vtable = nullptr;
  std::uint32_t opaque_004[17]{};
};

static_assert(offsetof(OpaqueShadowWorld, opaque_004) == 0x04,
              "shadow world body");

struct OpaquePickerWorldVTable {
  void* slots_00[0x28 / 4]{};
  std::uint32_t(PKG_W7_THISCALL* set_active_28)(void*, std::uint32_t,
                                                bool) = nullptr;
};

static_assert(offsetof(OpaquePickerWorldVTable, set_active_28) == 0x28,
              "picker world collision class slot");

struct OpaquePickerWorld {
  OpaquePickerWorldVTable* vtable = nullptr;
  std::uint32_t opaque_004[16]{};
};

struct OpaqueController {
  std::uint8_t opaque_000[8]{};
  OpaqueCreature* creature_008 = nullptr;
  OpaqueShadowWorld* shadow_00c = nullptr;
  std::uint8_t opaque_010[12]{};
  OpaqueWord animation_id_01c = 0;
  Vector3 position_020{};
  Vector3 offset_02c{};
  Vector3 current_038{};
  float target_angle_044 = 0.0f;
  float angle_048 = 0.0f;
  float position_rate_04c = 0.0f;
  float angle_rate_050 = 0.0f;
  std::uint8_t follow_ground_054 = 0;
  std::uint8_t snap_when_facing_055 = 0;
  std::uint8_t opaque_056[2]{};
  Vector3 previous_058{};
  Vector3 world_064{};
  std::uint32_t opaque_070[1]{};
  float creep_low_074 = 0.0f;
  float creep_high_078 = 0.0f;
  float creep_remaining_07c = 0.0f;
  float creep_rate_080 = 0.0f;
  std::uint8_t angle_limited_084 = 0;
  std::uint8_t opaque_085[3]{};
};

static_assert(offsetof(OpaqueController, animation_id_01c) == 0x1c,
              "controller animation publication slot");
static_assert(offsetof(OpaqueController, creature_008) == 0x08,
              "controller creature slot");
static_assert(offsetof(OpaqueController, shadow_00c) == 0x0c,
              "controller shadow world slot");
static_assert(offsetof(OpaqueController, position_020) == 0x20,
              "controller raw position");
static_assert(offsetof(OpaqueController, offset_02c) == 0x2c,
              "controller target offset");
static_assert(offsetof(OpaqueController, current_038) == 0x38,
              "controller current offset");
static_assert(offsetof(OpaqueController, target_angle_044) == 0x44,
              "controller target angle");
static_assert(offsetof(OpaqueController, angle_048) == 0x48,
              "controller angle");
static_assert(offsetof(OpaqueController, position_rate_04c) == 0x4c,
              "controller position rate");
static_assert(offsetof(OpaqueController, angle_rate_050) == 0x50,
              "controller angle rate");
static_assert(offsetof(OpaqueController, follow_ground_054) == 0x54,
              "controller ground follow flag");
static_assert(offsetof(OpaqueController, snap_when_facing_055) == 0x55,
              "controller facing snap flag");
static_assert(offsetof(OpaqueController, previous_058) == 0x58,
              "controller previous world position");
static_assert(offsetof(OpaqueController, world_064) == 0x64,
              "controller world position");
static_assert(offsetof(OpaqueController, creep_low_074) == 0x74,
              "controller creep low");
static_assert(offsetof(OpaqueController, creep_high_078) == 0x78,
              "controller creep high");
static_assert(offsetof(OpaqueController, creep_remaining_07c) == 0x7c,
              "controller creep remaining");
static_assert(offsetof(OpaqueController, creep_rate_080) == 0x80,
              "controller creep rate");
static_assert(offsetof(OpaqueController, angle_limited_084) == 0x84,
              "controller angle limited flag");
static_assert(sizeof(OpaqueController) == 0x88, "controller observed extent");

struct OpaqueControllerNode {
  OpaqueControllerNode* right_00 = nullptr;
  OpaqueControllerNode* left_04 = nullptr;
  OpaqueControllerNode* parent_08 = nullptr;
  std::uint32_t color_0c = 0;
  std::int32_t key_10 = 0;
  OpaqueController* value_14 = nullptr;
};

static_assert(offsetof(OpaqueControllerNode, key_10) == 0x10, "map node key");
static_assert(offsetof(OpaqueControllerNode, value_14) == 0x14,
              "map node value");
static_assert(sizeof(OpaqueControllerNode) == 0x18, "map node observed size");

struct OpaqueControllerMap {
  std::uint32_t reserved_000 = 0;
  OpaqueControllerNode* sentinel_004 = nullptr;
  std::uint32_t reserved_008 = 0;
  OpaqueControllerNode* root_00c = nullptr;
  std::uint32_t size_010 = 0;
};

static_assert(offsetof(OpaqueControllerMap, sentinel_004) == 0x04,
              "map sentinel anchor");
static_assert(offsetof(OpaqueControllerMap, root_00c) == 0x0c, "map root");
static_assert(offsetof(OpaqueControllerMap, size_010) == 0x10, "map size");
static_assert(sizeof(OpaqueControllerMap) == 0x14, "map observed size");

struct OpaqueAnimWorld {
  std::uint8_t opaque_000[8]{};
  OpaqueControllerMap controllers_008{};
  std::uint8_t opaque_014[0x1c]{};
  std::uint32_t map_enabled_038 = 0;
  std::uint32_t animation_enabled_03c = 0;
};

static_assert(offsetof(OpaqueAnimWorld, controllers_008) == 0x08,
              "anim world controller map anchor");
static_assert(offsetof(OpaqueAnimWorld, map_enabled_038) == 0x38,
              "anim world map gate");
static_assert(offsetof(OpaqueAnimWorld, animation_enabled_03c) == 0x3c,
              "anim world animation gate");
static_assert(sizeof(OpaqueAnimWorld) == 0x40, "anim world observed extent");

struct OpaqueControllerMapPorts {
  using LowerBound = void(PKG_W7_THISCALL*)(OpaqueControllerMap*,
                                            OpaqueControllerNode**,
                                            const std::int32_t*);
  using Find = void*(PKG_W7_THISCALL*)(OpaqueControllerMap*,
                                       const std::int32_t*);

  LowerBound lower_bound_00e5c780 = nullptr;
  Find find_0059c740 = nullptr;
};

extern OpaqueControllerMapPorts* g_controller_map_ports;

float clamp_offset_length(float length);
float quarter_turn_sign(float wrapped);

extern "C" OpaqueController* PKG_W7_THISCALL
anim_world_get_creature_controller_0059cac0(OpaqueAnimWorld* world,
                                            std::int32_t creature_id);

extern "C" void PKG_W7_THISCALL anim_world_play_animation_0059cb10(
    OpaqueAnimWorld* world, std::int32_t creature_id, OpaqueWord animation_id);

extern "C" void PKG_W7_THISCALL anim_world_set_target_angle_0059cea0(
    OpaqueAnimWorld* world, std::int32_t creature_id, float angle,
    bool apply_now);

extern "C" void PKG_W7_THISCALL anim_world_set_target_position_0059cf00(
    OpaqueAnimWorld* world, std::int32_t creature_id, Vector3 position,
    bool apply_now, bool ignore_z);

struct OpaqueControllerPorts {
  using SetTargetAngle = void(PKG_W7_THISCALL*)(OpaqueController*, float, bool);
  using SetTargetPosition = void(PKG_W7_THISCALL*)(OpaqueController*,
                                                   const Vector3*, bool, bool);
  using Update = void(PKG_W7_THISCALL*)(OpaqueController*, std::int32_t);
  using PublishAnimationId = void(PKG_W7_THISCALL*)(OpaqueController*,
                                                    OpaqueWord);
  using LerpVector = const Vector3*(PKG_W7_CDECL*)(const Vector4*,
                                                   const Vector3*,
                                                   const Vector3*, float);
  using LerpAngle = float(PKG_W7_CDECL*)(float, float, float);
  using Project = float(PKG_W7_CDECL*)(const Vector3*, const Vector3*,
                                       const Vector3*);
  using WrapAngle = float(PKG_W7_CDECL*)(float);
  using LookDirection = const Vector3*(PKG_W7_CDECL*)(const Vector3*,
                                                      const Vector3*,
                                                      const Vector4*);
  using LookBlocked = bool(PKG_W7_CDECL*)(const Vector3*);
  using Cross = const Vector3*(PKG_W7_CDECL*)(const Vector4*, const Vector3*);
  using Rotate = void(PKG_W7_CDECL*)(Vector3*, const Vector3*, float);
  using Notification = void(PKG_W7_THISCALL*)(OpaqueCreature*, OpaqueWord);
  using ManagerGet = void*(PKG_W7_CDECL*)();
  using ManagerSlot40 = void*(PKG_W7_THISCALL*)(void*, void*);
  using ManagerQuery = bool(PKG_W7_CDECL*)(void*);
  using PickerWorldGet = OpaquePickerWorld*(PKG_W7_CDECL*)();

  SetTargetAngle set_target_angle_0059b2f0 = nullptr;
  SetTargetPosition set_target_position_0059b0f0 = nullptr;
  Update update_0059b4b0 = nullptr;
  PublishAnimationId publish_animation_id_007cd950 = nullptr;
  LerpVector lerp_vector_00699600 = nullptr;
  LerpAngle lerp_angle_0069b840 = nullptr;
  Project project_0069b760 = nullptr;
  WrapAngle wrap_angle_0059ac00 = nullptr;
  LookDirection look_direction_0059aed0 = nullptr;
  LookBlocked look_blocked_0059ab70 = nullptr;
  Cross cross_00436ce0 = nullptr;
  Rotate rotate_00576b00 = nullptr;
  Notification notify_00a047d0 = nullptr;
  ManagerGet manager_get_0067cb20 = nullptr;
  ManagerSlot40 manager_slot_40 = nullptr;
  ManagerQuery manager_query_00a02710 = nullptr;
  ManagerQuery manager_query_00a027a0 = nullptr;
  PickerWorldGet picker_world_0067dd80 = nullptr;
};

extern OpaqueControllerPorts* g_controller_ports;

extern "C" void PKG_W7_THISCALL controller_set_target_position_0059b0f0(
    OpaqueController* controller, const Vector3* position, bool apply_now,
    bool ignore_z);

extern "C" void PKG_W7_THISCALL
controller_update_0059b4b0(OpaqueController* controller, std::int32_t dt);

constexpr std::uint32_t kCollisionClassRay_026f3933 = 0x026f3933u;
constexpr OpaqueWord kRayQueryFlag = 4u;
constexpr float kOffsetLimit = 5.0f;
constexpr float kDirectionStep = 2.0f;
constexpr float kTargetLead = 10.0f;
constexpr float kTimeScale = 0.001f;
constexpr float kSmoothingRetain = 0.85f;
constexpr float kSmoothingTake = 0.15f;
constexpr float kLookRadius = 0.1f;
constexpr float kSnapThreshold = 0.000015258789f;
constexpr float kFacingQuarterTurn = 0.7853981634f;
constexpr float kRayOriginHeight = 500.0f;
constexpr float kRayOriginDrop = 1000.0f;
constexpr float kClampCeiling = 1.0f;
constexpr float kSweepFactor = 5.0f;
constexpr float kHalfAngle = 0.5f;
constexpr float kSignNegative = -1.0f;
constexpr float kSignPositive = 1.0f;
constexpr OpaqueWord kNullWord = 0u;
constexpr float kPositiveSign = 1.0f;
constexpr float kNegativeSign = -1.0f;
constexpr float kReconcileHalf = 0.5f;
constexpr float kReconcileFull = 1.0f;
constexpr float kReconcileBias = 1.5f;
constexpr std::uint32_t kMaskBitBound = 0x40u;
constexpr std::uint32_t kMaskBitShift = 32u;

}

#undef PKG_W7_CDECL
#undef PKG_W7_THISCALL
