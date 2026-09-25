#pragma once

#include <cstddef>
#include <cstdint>

#include "../pkg20_gameglobal/map_search.hpp"

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11 empire lookup staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_sim_core {

using TargetWord = pkg20_gameglobal::TargetWord;

struct OpaqueEmpire;

struct OpaqueStarManager {
  std::uint8_t prefix[0x150];
  pkg20_gameglobal::OrderedMap mEmpires;
};

struct EmpireMapEntry {
  pkg20_gameglobal::OrderedMapEntry key_prefix;
  OpaqueEmpire* payload;
};

static_assert(sizeof(void*) == 4, "PKG-11 target pointers are 32-bit");
static_assert(offsetof(OpaqueStarManager, mEmpires) == 0x150,
              "empire map offset");
static_assert(offsetof(pkg20_gameglobal::OrderedMap, anchor) == 0x04,
              "empire map end offset");
static_assert(offsetof(EmpireMapEntry, payload) == 0x14,
              "empire map payload offset");
static_assert(sizeof(EmpireMapEntry) == 24,
              "empire map entry includes the node payload word");

#if defined(_MSC_VER)
#define PKG11_THISCALL __thiscall
#else
#define PKG11_THISCALL __attribute__((thiscall))
#endif

OpaqueEmpire* PKG11_THISCALL Simulator_LookupEmpireByPoliticalId(
    OpaqueStarManager* manager, TargetWord political_id);

#undef PKG11_THISCALL

}
