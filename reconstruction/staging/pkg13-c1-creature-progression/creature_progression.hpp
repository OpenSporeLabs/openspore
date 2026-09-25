#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C1 creature progression requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG13-C1 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG13-C1 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG13_C1_CDECL __cdecl
#else
#define PKG13_C1_CDECL __attribute__((cdecl))
#endif

extern "C" {
extern float DAT_0169e398;
}

namespace openspore::reconstruction::pkg13_c1_creature_progression {

struct OpaqueNounManager {
  std::uint32_t opaque_word;
};

struct ProgressionPlayerAccessWindow {
  std::array<std::uint8_t, 0x10f4> bytes{};
};

using GetNounManagerPort = OpaqueNounManager* (*)();
using GetProgressionPlayerPort =
    ProgressionPlayerAccessWindow* (*)(OpaqueNounManager * receiver);
using GetLevelRequirementPort = float (*)(std::int32_t level);

struct NativePorts {
  GetNounManagerPort get_noun_manager;
  GetProgressionPlayerPort get_progression_player;
  GetLevelRequirementPort get_level_requirement;
};

static_assert(sizeof(GetNounManagerPort) == 4,
              "PKG13-C1 target function pointers are 32-bit");
static_assert(sizeof(GetProgressionPlayerPort) == 4,
              "PKG13-C1 target function pointers are 32-bit");
static_assert(sizeof(GetLevelRequirementPort) == 4,
              "PKG13-C1 target function pointers are 32-bit");
static_assert(offsetof(ProgressionPlayerAccessWindow, bytes) == 0,
              "PKG13-C1 access window starts at byte zero");
static_assert(sizeof(ProgressionPlayerAccessWindow) >= 0x10f4,
              "PKG13-C1 access window includes the +0x10f0 field");

extern NativePorts g_native_ports;

extern "C" void PKG13_C1_CDECL
Simulator_cCreatureGameData_SetEvolutionPoints_raw_00d2e480(float points);

extern "C" std::int32_t PKG13_C1_CDECL pkg13_progression_brain_level_00d2e830();

}
