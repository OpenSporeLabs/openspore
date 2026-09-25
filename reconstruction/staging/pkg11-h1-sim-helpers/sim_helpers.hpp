#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11 simulator helpers staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_h1_sim_helpers {

struct OpaqueSimulationManager;
struct OpaqueRelationshipManager;

using SharedGateValue = std::uint32_t;

inline constexpr std::uint32_t kPurecallVtable = 0x01444434U;
inline constexpr std::uint32_t kPrimaryVtable = 0x0146155CU;
inline constexpr std::uint32_t kSecondaryVtable = 0x01461538U;

struct OpaqueProgressionBadgeBase {
  std::uint32_t primary_vtable;
  std::uint32_t state_04;
  std::uint32_t secondary_vtable;
  std::uint8_t state_0c;
  std::uint8_t state_0d;
  std::uint8_t state_0e;
};

static_assert(sizeof(OpaqueProgressionBadgeBase) >= 0x0f,
              "base constructor writes a 15-byte prefix");

extern "C" OpaqueSimulationManager* manager_root_00b3d320();

extern "C" SharedGateValue __attribute__((fastcall))
read_shared_gate_00a42730(OpaqueSimulationManager* manager);

extern "C" __attribute__((naked)) SharedGateValue
pkg11_sim_helpers_00b5b800();

extern "C" void __attribute__((thiscall))
pkg11_sim_helpers_00b5b6c0(OpaqueProgressionBadgeBase* receiver);

extern "C" OpaqueRelationshipManager* g_relationship_manager_0167eb14;

extern "C" __attribute__((naked)) OpaqueRelationshipManager*
pkg11_sim_helpers_00b3d3c0();

static_assert(offsetof(OpaqueProgressionBadgeBase, primary_vtable) == 0x00,
              "primary vtable offset");
static_assert(offsetof(OpaqueProgressionBadgeBase, state_04) == 0x04,
              "state field offset");
static_assert(offsetof(OpaqueProgressionBadgeBase, secondary_vtable) == 0x08,
              "secondary vtable offset");
static_assert(offsetof(OpaqueProgressionBadgeBase, state_0c) == 0x0c,
              "state byte offset");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");

}
