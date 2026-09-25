#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-12 player-cache staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-12 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-12 target words are 32-bit");

namespace openspore::reconstruction::pkg12_space {

inline constexpr std::int32_t kInvalidEmpireId = -1;
static_assert(static_cast<std::uint32_t>(kInvalidEmpireId) == 0xffffffffU,
              "PKG-12 invalid empire id is raw 0xffffffff");

struct StagedIdWord {
  std::int32_t value = 0;
};

static_assert(sizeof(StagedIdWord) == 4,
              "PKG-12 staged empire id occupies one target word");

struct Empire;

using EmpireAddRef = void(__thiscall*)(Empire*);
using EmpireRelease = void(__thiscall*)(Empire*);

struct Empire {
  EmpireAddRef add_ref;
  EmpireRelease release;
  std::uint8_t opaque[0x7c]{};
  std::int32_t identity = 0;
};

static_assert(offsetof(Empire, identity) == 0x84,
              "PKG-12 empire identity is at target offset 0x84");
static_assert(sizeof(Empire) == 0x88, "PKG-12 empire model covers offset 0x88");

struct EmpireLookup {
  using RootWithStagedId = void* (*)(StagedIdWord);
  using FindWithStagedId = Empire*(__thiscall*)(void*, StagedIdWord);
  RootWithStagedId root = nullptr;
  FindWithStagedId find = nullptr;
};

struct SpacePlayerCache {
  std::uint8_t opaque[0x18]{};
  std::int32_t empire_id = -1;
  Empire* cached_empire = nullptr;
};

static_assert(offsetof(SpacePlayerCache, empire_id) == 0x18,
              "PKG-12 player empire key is at target offset 0x18");
static_assert(offsetof(SpacePlayerCache, cached_empire) == 0x1c,
              "PKG-12 cached empire is at target offset 0x1c");

extern SpacePlayerCache* g_simulator_space_player_data;
extern const EmpireLookup* g_simulator_empire_lookup;

Empire* refresh_player_empire_staged(SpacePlayerCache& cache,
                                     const EmpireLookup& lookup);
Empire* pkg12_space_01021300();

}
