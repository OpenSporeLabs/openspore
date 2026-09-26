#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C4 creature wave3 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG13-C4 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG13-C4 target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG13-C4 target reals are 32-bit");

#if defined(_MSC_VER)
#define PKG13_C4_CDECL __cdecl
#define PKG13_C4_THISCALL __thiscall
#else
#define PKG13_C4_CDECL __attribute__((cdecl))
#define PKG13_C4_THISCALL __attribute__((thiscall))
#endif

extern "C" {
extern float DAT_013ef480;
extern float DAT_0146a32c;
extern float DAT_01470f1c;
extern float DAT_01485720;
extern float DAT_0150c900;
extern float DAT_0168d910;
extern float DAT_0168d914;
extern float DAT_0168d918;
extern float DAT_0168d964[9];
extern float DAT_0168d988;
extern float DAT_0168d98c;
extern float DAT_0168d990;
}

namespace openspore::reconstruction::pkg13_c4_creature_wave3 {

inline constexpr std::uint32_t kCreatureStateSizeBytes = 0xFC0U;
inline constexpr std::size_t kLocomotiveObjectOffset = 0xC0U;
inline constexpr std::size_t kSpeedScalarFieldOffset = 0x2A0U;
inline constexpr std::size_t kProjectionBypassFieldOffset = 0x2B0U;
inline constexpr std::size_t kTransitResetFieldOffset = 0x330U;
inline constexpr std::size_t kSpeedModeFlagOffset = 0xBB0U;
inline constexpr std::size_t kContainerOffset = 0xBC0U;
inline constexpr std::size_t kContainerBeginWordOffset = 0x00U;
inline constexpr std::size_t kContainerEndWordOffset = 0x04U;
inline constexpr std::size_t kEffectPool2Offset = 0xD68U;
inline constexpr std::size_t kSpeedStateFieldOffset = 0xF98U;

inline constexpr std::uint16_t kPropertyFlagPosition = 0x0004U;
inline constexpr std::uint16_t kPropertyFlagRotation = 0x0002U;
inline constexpr std::int16_t kPropertyCountPerTransform = 2;
inline constexpr std::int16_t kPropertyTagValue = 3;
inline constexpr std::int32_t kStandardSpeedState = 2;
inline constexpr std::int32_t kStandardSpeedMode = 1;

struct Vector3 {
  float x = 0.0F;
  float y = 0.0F;
  float z = 0.0F;
};

struct Matrix3 {
  float m[9] = {};
};

struct alignas(4) OpaqueLocomotiveObject {
  std::uint32_t vtable_word = 0;
  std::uint8_t opaque[0x530] = {};
};

struct alignas(4) OpaqueEffectPool {
  std::uint32_t opaque_word = 0;
  std::uint8_t opaque[0x9C] = {};
};

struct alignas(4) OpaqueCreatureState {
  std::uint8_t bytes[kCreatureStateSizeBytes] = {};
};

struct alignas(4) OpaqueEffectsManager {
  std::uint32_t vtable_word = 0;
  std::uint8_t opaque[0x3C] = {};
};

struct alignas(4) OpaqueVisualEffect {
  std::uint32_t vtable_word = 0;
  std::uint8_t opaque[0x3C] = {};
};

struct LocomotionRequest {
  void* release_handle;
  std::uint32_t reserved_word_04;
  std::uint32_t reserved_word_08;
  std::uint8_t undetermined_0c[8];
  Vector3 dst_position;
  float goal_stop_distance;
  std::uint32_t reserved_word_24;
  std::uint8_t undetermined_28[36];
  std::uint8_t orientation_flag;
  std::uint8_t undetermined_4d[3];
  Vector3 perpendicular_unit;
  std::uint32_t property_tag_5c;
  float acceptable_stop_distance;
  float threshold_64;
  float limit_68;
  float residual_6c;
  std::uint32_t reserved_word_70;
};

struct EffectTransformProperties {
  std::uint16_t property_flags;
  std::int16_t property_count;
  Vector3 world_position;
  float uniform_scale;
  Matrix3 rotation;
};

struct alignas(4) OpaqueEmbeddedContainer {
  std::uint32_t begin_word = 0;
  std::uint32_t end_word = 0;
  std::uint8_t undetermined[0x3F8] = {};
};

static_assert(sizeof(OpaqueEmbeddedContainer) ==
                  kCreatureStateSizeBytes - kContainerOffset,
              "PKG13-C4 embedded container covers the creature window tail");

static_assert(sizeof(Vector3) == 12, "PKG13-C4 Vector3 is three reals");
static_assert(sizeof(Matrix3) == 36, "PKG13-C4 Matrix3 is nine reals");
static_assert(sizeof(LocomotionRequest) == 0x74,
              "PKG13-C4 locomotion request spans +0x00..+0x73");
static_assert(offsetof(LocomotionRequest, release_handle) == 0x00,
              "PKG13-C4 request release handle at +0x00");
static_assert(offsetof(LocomotionRequest, reserved_word_04) == 0x04,
              "PKG13-C4 request zeroed word at +0x04");
static_assert(offsetof(LocomotionRequest, reserved_word_08) == 0x08,
              "PKG13-C4 request zeroed word at +0x08");
static_assert(offsetof(LocomotionRequest, undetermined_0c) == 0x0C,
              "PKG13-C4 request undetermined bytes start at +0x0C");
static_assert(offsetof(LocomotionRequest, dst_position) == 0x14,
              "PKG13-C4 request destination position at +0x14");
static_assert(offsetof(LocomotionRequest, goal_stop_distance) == 0x20,
              "PKG13-C4 request goal stop distance at +0x20");
static_assert(offsetof(LocomotionRequest, reserved_word_24) == 0x24,
              "PKG13-C4 request zeroed word at +0x24");
static_assert(offsetof(LocomotionRequest, undetermined_28) == 0x28,
              "PKG13-C4 request undetermined block starts at +0x28");
static_assert(offsetof(LocomotionRequest, orientation_flag) == 0x4C,
              "PKG13-C4 request orientation flag byte at +0x4C");
static_assert(offsetof(LocomotionRequest, undetermined_4d) == 0x4D,
              "PKG13-C4 request undetermined bytes start at +0x4D");
static_assert(offsetof(LocomotionRequest, perpendicular_unit) == 0x50,
              "PKG13-C4 request perpendicular unit at +0x50");
static_assert(offsetof(LocomotionRequest, property_tag_5c) == 0x5C,
              "PKG13-C4 request property tag at +0x5C");
static_assert(offsetof(LocomotionRequest, acceptable_stop_distance) == 0x60,
              "PKG13-C4 request acceptable stop distance at +0x60");
static_assert(offsetof(LocomotionRequest, threshold_64) == 0x64,
              "PKG13-C4 request threshold at +0x64");
static_assert(offsetof(LocomotionRequest, limit_68) == 0x68,
              "PKG13-C4 request limit at +0x68");
static_assert(offsetof(LocomotionRequest, residual_6c) == 0x6C,
              "PKG13-C4 request residual at +0x6C");
static_assert(offsetof(LocomotionRequest, reserved_word_70) == 0x70,
              "PKG13-C4 request zeroed word at +0x70");
static_assert(sizeof(EffectTransformProperties) == 0x38,
              "PKG13-C4 effect transform properties span +0x00..+0x37");
static_assert(offsetof(EffectTransformProperties, property_flags) == 0x00,
              "PKG13-C4 property flags at +0x00");
static_assert(offsetof(EffectTransformProperties, property_count) == 0x02,
              "PKG13-C4 property count at +0x02");
static_assert(offsetof(EffectTransformProperties, world_position) == 0x04,
              "PKG13-C4 property position at +0x04");
static_assert(offsetof(EffectTransformProperties, uniform_scale) == 0x10,
              "PKG13-C4 property scale at +0x10");
static_assert(offsetof(EffectTransformProperties, rotation) == 0x14,
              "PKG13-C4 property rotation at +0x14");

inline std::uint32_t CreatureWord(const OpaqueCreatureState* creature,
                                  std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, creature->bytes + offset, sizeof(value));
  return value;
}

inline void SetCreatureWord(OpaqueCreatureState* creature, std::size_t offset,
                            std::uint32_t value) {
  std::memcpy(creature->bytes + offset, &value, sizeof(value));
}

inline float CreatureFloat(const OpaqueCreatureState* creature,
                           std::size_t offset) {
  float value = 0.0F;
  std::memcpy(&value, creature->bytes + offset, sizeof(value));
  return value;
}

inline void SetCreatureFloat(OpaqueCreatureState* creature, std::size_t offset,
                             float value) {
  std::memcpy(creature->bytes + offset, &value, sizeof(value));
}

inline std::uint8_t CreatureByte(const OpaqueCreatureState* creature,
                                 std::size_t offset) {
  return creature->bytes[offset];
}

inline void SetCreatureByte(OpaqueCreatureState* creature, std::size_t offset,
                            std::uint8_t value) {
  creature->bytes[offset] = value;
}

inline OpaqueLocomotiveObject* LocomotiveObjectOf(
    OpaqueCreatureState* creature) {
  return reinterpret_cast<OpaqueLocomotiveObject*>(creature->bytes +
                                                   kLocomotiveObjectOffset);
}

inline OpaqueEffectPool* EffectPool2Of(OpaqueCreatureState* creature) {
  return reinterpret_cast<OpaqueEffectPool*>(creature->bytes +
                                             kEffectPool2Offset);
}

inline OpaqueEmbeddedContainer* EmbeddedContainerOf(
    OpaqueCreatureState* creature) {
  return reinterpret_cast<OpaqueEmbeddedContainer*>(creature->bytes +
                                                    kContainerOffset);
}

inline const OpaqueLocomotiveObject* LocomotiveObjectOf(
    const OpaqueCreatureState* creature) {
  return reinterpret_cast<const OpaqueLocomotiveObject*>(
      creature->bytes + kLocomotiveObjectOffset);
}

using GetLocomotivePositionPort =
    const float*(PKG13_C4_THISCALL*)(OpaqueLocomotiveObject * receiver);
using SubmitLocomotionRequestPort = void(PKG13_C4_THISCALL*)(
    OpaqueLocomotiveObject* receiver, LocomotionRequest* request);
using LookupSpeedScalarPort = double(PKG13_C4_THISCALL*)(
    OpaqueCreatureState* creature, std::int32_t key, std::int32_t mode);
using ReleaseRequestHandlePort = void(PKG13_C4_CDECL*)(void* handle);
using CommitContainerGrowthPort =
    void(PKG13_C4_THISCALL*)(OpaqueEmbeddedContainer* container,
                             std::uint32_t begin_word, std::uint32_t end_word);

using GetEffectsManagerPort = OpaqueEffectsManager*(PKG13_C4_CDECL*)();
using CreateVisualEffectPort = bool(PKG13_C4_THISCALL*)(
    OpaqueEffectsManager* manager, std::uint32_t instance_id,
    std::uint32_t group_id, OpaqueVisualEffect** destination);
using ResolveEffectPoolSlotPort = OpaqueVisualEffect**(
    PKG13_C4_THISCALL*)(OpaqueEffectPool * pool, const std::uint32_t* key);
using EffectAddRefPort =
    std::int32_t(PKG13_C4_THISCALL*)(OpaqueVisualEffect* effect);
using EffectReleasePort =
    std::int32_t(PKG13_C4_THISCALL*)(OpaqueVisualEffect* effect);
using EffectStartPort = void(PKG13_C4_THISCALL*)(OpaqueVisualEffect* effect,
                                                 std::int32_t hard_start);
using EffectSetSourceTransformPort = void(PKG13_C4_THISCALL*)(
    OpaqueVisualEffect* effect, const EffectTransformProperties* properties);
using GetLocomotiveQuaternionPort =
    const float*(PKG13_C4_THISCALL*)(OpaqueLocomotiveObject * receiver);
using CopyMatrix3Port = void(PKG13_C4_THISCALL*)(Matrix3* destination,
                                                 const float* source);
using QuaternionToMatrix3Port = void(PKG13_C4_CDECL*)(Matrix3* destination,
                                                      const float* quaternion);

struct NativePorts {
  GetLocomotivePositionPort get_locomotive_position = nullptr;
  SubmitLocomotionRequestPort submit_locomotion_request = nullptr;
  LookupSpeedScalarPort lookup_speed_scalar = nullptr;
  ReleaseRequestHandlePort release_request_handle = nullptr;
  CommitContainerGrowthPort commit_container_growth = nullptr;
  GetEffectsManagerPort get_effects_manager = nullptr;
  CreateVisualEffectPort create_visual_effect = nullptr;
  ResolveEffectPoolSlotPort resolve_effect_pool_slot = nullptr;
  EffectAddRefPort effect_add_ref = nullptr;
  EffectReleasePort effect_release = nullptr;
  EffectStartPort effect_start = nullptr;
  EffectSetSourceTransformPort effect_set_source_transform = nullptr;
  GetLocomotiveQuaternionPort get_locomotive_quaternion = nullptr;
  CopyMatrix3Port copy_matrix3 = nullptr;
  QuaternionToMatrix3Port quaternion_to_matrix3 = nullptr;
};

static_assert(sizeof(NativePorts) == 15 * 4,
              "PKG13-C4 native port table is fifteen 32-bit slots");
static_assert(sizeof(GetLocomotivePositionPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(SubmitLocomotionRequestPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(LookupSpeedScalarPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(ReleaseRequestHandlePort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(CommitContainerGrowthPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(GetEffectsManagerPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(CreateVisualEffectPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(ResolveEffectPoolSlotPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(EffectAddRefPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(EffectReleasePort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(EffectStartPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(EffectSetSourceTransformPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(GetLocomotiveQuaternionPort) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(CopyMatrix3Port) == 4,
              "PKG13-C4 target function pointers are 32-bit");
static_assert(sizeof(QuaternionToMatrix3Port) == 4,
              "PKG13-C4 target function pointers are 32-bit");

extern NativePorts g_native_ports;

float InverseExtendedUnitLength(const Vector3& value);

void BuildLocomotionRequest(const Vector3& dst_position,
                            Vector3 perpendicular_unit,
                            float goal_stop_distance,
                            float acceptable_stop_distance,
                            LocomotionRequest* request);

extern "C" void PKG13_C4_THISCALL
Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0(
    OpaqueCreatureState* creature, std::int32_t speed_state,
    const Vector3* dst_position, const Vector3* oriented_vector,
    float goal_stop_distance, float acceptable_stop_distance);

extern "C" OpaqueVisualEffect* PKG13_C4_THISCALL
Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460(
    OpaqueCreatureState* creature, std::uint32_t instance_id,
    std::uint32_t pool_key);

extern "C" void PKG13_C4_CDECL
QuaternionToMatrix3_0059c190(Matrix3* destination, const float* quaternion);

extern "C" void PKG13_C4_THISCALL CopyMatrix3_0041cb40(Matrix3* destination,
                                                       const float* source);

static_assert(
    std::is_same<
        decltype(&Simulator_cCreatureBase_LocomotionWalkToInterior_00c1c5c0),
        void(PKG13_C4_THISCALL*)(OpaqueCreatureState*, std::int32_t,
                                 const Vector3*, const Vector3*, float,
                                 float)>::value,
    "PKG13-C4 locomotion interior ABI");
static_assert(
    std::is_same<
        decltype(&Simulator_cCreatureBase_CreateAndStartPool2Effect_00c1d460),
        OpaqueVisualEffect*(PKG13_C4_THISCALL*)(OpaqueCreatureState*,
                                                std::uint32_t,
                                                std::uint32_t)>::value,
    "PKG13-C4 pool2 effect ABI");
static_assert(
    std::is_same<decltype(&QuaternionToMatrix3_0059c190),
                 void(PKG13_C4_CDECL*)(Matrix3*, const float*)>::value,
    "PKG13-C4 quaternion to matrix ABI");
static_assert(
    std::is_same<decltype(&CopyMatrix3_0041cb40),
                 void(PKG13_C4_THISCALL*)(Matrix3*, const float*)>::value,
    "PKG13-C4 matrix copy ABI");

}
