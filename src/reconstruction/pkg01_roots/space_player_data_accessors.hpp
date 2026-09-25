#pragma once

#include "pkg01_roots.hpp"

#include <cstddef>
#include <cstdint>

struct ActivePlanetAccessWindow {
  std::uint8_t bytes[0x140];
};

struct OpaqueActiveStar {};

struct OpaqueActivePlanetField13c {};

enum class SpaceContextValue : std::uint32_t {
  kNone = 0xffffffffU,
  kPlanet = 0U,
  kSolarSystem = 1U,
  kGalaxy = 2U,
};

struct SpacePlayerDataAccessPrefix {
  TargetWord word_0x00;
  TargetWord active_planet_word;
  TargetWord active_star_word;
  TargetWord word_0x0c;
  SpaceContextValue current_context;
};

static_assert(sizeof(ActivePlanetAccessWindow) == 0x140);
static_assert(sizeof(SpacePlayerDataAccessPrefix) == 0x14);
static_assert(offsetof(SpacePlayerDataAccessPrefix, active_planet_word) ==
              0x04);
static_assert(offsetof(SpacePlayerDataAccessPrefix, active_star_word) == 0x08);
static_assert(offsetof(SpacePlayerDataAccessPrefix, current_context) == 0x10);
static_assert(sizeof(void *) == sizeof(TargetWord));

extern "C" {
extern SpacePlayerDataAccessPrefix *Simulator__sSpacePlayerData;

SpaceContextValue PKG01_CDECL FUN_01021080();
OpaqueActiveStar *PKG01_CDECL FUN_01021230();
ActivePlanetAccessWindow *PKG01_CDECL FUN_01021260();
OpaqueActivePlanetField13c *PKG01_CDECL FUN_010212a0();
}
