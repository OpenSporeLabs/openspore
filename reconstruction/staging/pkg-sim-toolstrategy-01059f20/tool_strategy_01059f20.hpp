#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-sim-toolstrategy-01059f20 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __thiscall
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __cdecl
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __stdcall
#define PKG_SIM_TOOLSTRATEGY_01059F20_NAKED __declspec(naked)
#else
#define PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOLSTRATEGY_01059F20_CDECL __attribute__((cdecl))
#define PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL __attribute__((stdcall))
#define PKG_SIM_TOOLSTRATEGY_01059F20_NAKED __attribute__((naked))
#endif

namespace openspore::reconstruction::pkg_sim_toolstrategy_01059f20 {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kTargetVa = 0x01059f20u;
inline constexpr TargetWord kToolOwnerPointerOffset = 0x114u;
inline constexpr TargetWord kToolAreaPointerOffset = 0x120u;
inline constexpr TargetWord kToolBeamPointerOffset = 0x124u;
inline constexpr TargetWord kToolFlagsOffset = 0x174u;
inline constexpr TargetWord kToolSizeBytes = 0x2a0u;
inline constexpr TargetWord kBeamFlaggedFieldOffset = 0x154u;
inline constexpr TargetWord kRelationshipStateWordOffset = 0x20u;
inline constexpr TargetWord kRelationshipEventWordOffset = 0x55a0u;
inline constexpr TargetWord kToolOwnerCastTypeEntryVa = 0x013f94d4u;
inline constexpr TargetWord kRelationshipSetterArgument = 7u;
inline constexpr std::size_t kStackCleanupBytes = 12u;

enum SpaceToolFlags : TargetWord {
  kFlagHitOrientsToTerrain = 0x1u,
  kFlagBeamPassThrough = 0x2u,
  kFlagIsHoming = 0x4u,
  kFlagDestroysFloraAndFauna = 0x8u,
  kFlagPicksFlora = 0x10u,
  kFlagUsesAmmo = 0x20u,
  kFlagDisableOnHomeWorld = 0x40u,
  kFlagDisableOnSaveGames = 0x80u,
};

struct Vector3 {
  float x;
  float y;
  float z;
};

struct OpaqueTypeEntry;

struct cSpatialObject;

using SpatialObjectCastSlot =
    void*(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(cSpatialObject*,
                                                   const OpaqueTypeEntry*);

struct OpaqueSpatialObjectVTable {
  void* slots_00[46];
  SpatialObjectCastSlot cast_b8;
};

struct alignas(4) cSpatialObject {
  const OpaqueSpatialObjectVTable* vtable_00;
  std::uint8_t opaque_004[1];
};

struct cDefaultBeamProjectile;

using BeamAddRefSlot =
    void(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(cDefaultBeamProjectile*);
using BeamReleaseSlot =
    void(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(cDefaultBeamProjectile*);
using BeamPredicateSlot =
    bool(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(cDefaultBeamProjectile*);

struct OpaqueBeamProjectileVTable {
  BeamAddRefSlot add_ref_00;
  BeamReleaseSlot release_04;
  void* slots_08[9];
  BeamPredicateSlot predicate_2c;
};

struct alignas(4) cDefaultBeamProjectile {
  const OpaqueBeamProjectileVTable* vtable_00;
  std::uint8_t opaque_004[336];
  std::uint8_t field_154;
  std::uint8_t opaque_155[1];
};

struct alignas(4) cSpaceToolData {
  std::uint8_t opaque_000[276];
  cSpatialObject* mpToolOwner;
  std::uint8_t opaque_118[8];
  void* mpArea;
  cDefaultBeamProjectile* mpBeam;
  std::uint8_t opaque_128[76];
  TargetWord mFlags;
  std::uint8_t opaque_178[296];
};

struct cRelationshipManager {
  std::uint8_t opaque_000[32];
  TargetWord state_20;
  std::uint8_t opaque_024[21884];
  TargetWord event_55a0;
};

struct OpaqueToolStrategy;

using StrategyBridgeSlot = bool(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(
    OpaqueToolStrategy*, cSpaceToolData*, const Vector3*);

struct OpaqueToolStrategyVTable {
  void* slots_00[18];
  StrategyBridgeSlot bridge_48;
};

struct alignas(4) OpaqueToolStrategy {
  const OpaqueToolStrategyVTable* vtable_00;
  std::uint8_t opaque_004[1];
};

using ToolPrecheckPort = bool(PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL*)(
    cSpaceToolData*, const Vector3*, int);
using ToolFlagsGatePort =
    bool(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(cSpaceToolData*);
using RelationshipManagerGetPort =
    cRelationshipManager*(PKG_SIM_TOOLSTRATEGY_01059F20_CDECL*)();
using RelationshipSetEventPort = void(PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL*)(
    cRelationshipManager*, TargetWord);
using ToolPositionUpdatePort = void(PKG_SIM_TOOLSTRATEGY_01059F20_CDECL*)(
    cSpaceToolData*, float, float, float);

struct NativePorts {
  ToolPrecheckPort tool_precheck_010568b0;
  ToolFlagsGatePort tool_flags_picks_flora_0104cd50;
  RelationshipManagerGetPort relationship_manager_get_00b3d3c0;
  RelationshipSetEventPort relationship_set_event_00b7c160;
  ToolPositionUpdatePort tool_position_update_01059170;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaqueSpatialObjectVTable, cast_b8) == 0xb8,
              "cSpatialObject Cast slot offset");
static_assert(offsetof(OpaqueBeamProjectileVTable, release_04) == 0x4,
              "cDefaultBeamProjectile Release slot offset");
static_assert(offsetof(OpaqueBeamProjectileVTable, predicate_2c) == 0x2c,
              "cDefaultBeamProjectile word 0x2c offset");
static_assert(offsetof(OpaqueToolStrategyVTable, bridge_48) == 0x48,
              "strategy bridge slot offset");
static_assert(offsetof(cDefaultBeamProjectile, field_154) == 0x154,
              "cDefaultBeamProjectile flagged field offset");
static_assert(offsetof(cSpaceToolData, mpToolOwner) == 0x114,
              "cSpaceToolData mpToolOwner offset");
static_assert(offsetof(cSpaceToolData, mpArea) == 0x120,
              "cSpaceToolData mpArea offset");
static_assert(offsetof(cSpaceToolData, mpBeam) == 0x124,
              "cSpaceToolData mpBeam offset");
static_assert(offsetof(cSpaceToolData, mFlags) == 0x174,
              "cSpaceToolData mFlags offset");
static_assert(sizeof(cSpaceToolData) == kToolSizeBytes,
              "cSpaceToolData extent");
static_assert(offsetof(cRelationshipManager, event_55a0) == 0x55a0,
              "cRelationshipManager event word offset");
static_assert(kStackCleanupBytes == 3 * sizeof(TargetWord),
              "callee pops three stack words");

extern NativePorts g_tool_strategy_01059f20_ports;

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL
tool_precheck_010568b0(cSpaceToolData*, const Vector3*, int);
extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
tool_flags_picks_flora_0104cd50(cSpaceToolData*);
extern "C" cRelationshipManager* PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
relationship_manager_get_00b3d3c0();
extern "C" void PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
relationship_set_event_00b7c160(cRelationshipManager*, TargetWord);
extern "C" void PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
tool_position_update_01059170(cSpaceToolData*, float, float, float);

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
func_01059f20(OpaqueToolStrategy* strategy, cSpaceToolData* pTool,
              const Vector3* aimPoint, int param_4);

extern "C" bool PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
naked_body_01059f20(OpaqueToolStrategy* strategy, cSpaceToolData* pTool,
                    const Vector3* aimPoint, int param_4);

}

#undef PKG_SIM_TOOLSTRATEGY_01059F20_NAKED
#undef PKG_SIM_TOOLSTRATEGY_01059F20_STDCALL
#undef PKG_SIM_TOOLSTRATEGY_01059F20_CDECL
#undef PKG_SIM_TOOLSTRATEGY_01059F20_THISCALL
