#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "editor runtime wave8 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_EDITOR_RUNTIME_WAVE8_THISCALL __thiscall
#else
#define PKG_EDITOR_RUNTIME_WAVE8_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_runtime_wave8 {

using TargetWord = std::uint32_t;

static_assert(sizeof(void*) == 4, "wave8 target pointers are 32-bit");
static_assert(sizeof(float) == 4, "wave8 target floats are 32-bit");
static_assert(sizeof(TargetWord) == 4, "wave8 target words are 32-bit");

struct OpaqueCreature {
  TargetWord vtable_00 = 0;
  float opaque_04[3]{};
  float orientation_10[4]{};
};

static_assert(offsetof(OpaqueCreature, orientation_10) == 0x10,
              "creature orientation row");
static_assert(sizeof(OpaqueCreature) == 0x20, "creature observed extent");

struct OpaqueCreatureWalkController {
  TargetWord opaque_00[2]{};
  OpaqueCreature* creature_08 = nullptr;
  std::array<std::uint8_t, 0x38> opaque_0c{};
  float target_angle_44 = 0.0f;
  float angle_48 = 0.0f;
};

static_assert(offsetof(OpaqueCreatureWalkController, creature_08) == 0x08,
              "controller creature pointer");
static_assert(offsetof(OpaqueCreatureWalkController, target_angle_44) == 0x44,
              "controller target angle");
static_assert(offsetof(OpaqueCreatureWalkController, angle_48) == 0x48,
              "controller applied angle");
static_assert(sizeof(OpaqueCreatureWalkController) == 0x4c,
              "controller observed extent");

struct OpaqueCreatureWalkControllerGlobals {
  float half_angle_01471064 = 0.5f;
  float orientation_x_015e5a0c = 0.0f;
  float orientation_y_015e5a10 = 0.0f;
  float orientation_z_015e5a14 = 0.0f;
};

extern OpaqueCreatureWalkControllerGlobals g_creature_walk_controller_globals;

extern "C" void PKG_EDITOR_RUNTIME_WAVE8_THISCALL
editor_creature_walk_controller_set_target_angle_0059b2f0(
    OpaqueCreatureWalkController* controller, float angle, bool apply_now);

}

#undef PKG_EDITOR_RUNTIME_WAVE8_THISCALL
