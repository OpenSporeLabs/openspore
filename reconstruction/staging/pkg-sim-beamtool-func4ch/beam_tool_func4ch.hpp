#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-sim-beamtool-func4ch requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL __thiscall
#define PKG_SIM_BEAMTOOL_FUNC4CH_CDECL __cdecl
#else
#define PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL __attribute__((thiscall))
#define PKG_SIM_BEAMTOOL_FUNC4CH_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_beamtool_func4ch {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kTargetVa = 0x01053db0u;
inline constexpr TargetWord kOwnedBeamTargetOffset = 0x124u;
inline constexpr TargetWord kBeamTargetStateOffset = 0x155u;
inline constexpr TargetWord kToolGateWordOffset = 0x174u;
inline constexpr TargetWord kToolGateMask = 0x10u;
inline constexpr TargetWord kRelationshipStateWordOffset = 0x20u;
inline constexpr TargetWord kRelationshipStateClearMask = 0xfffffffbu;
inline constexpr TargetWord kRelationshipEventWordOffset = 0x55a0u;
inline constexpr TargetWord kStackCleanupBytes = 4u;

struct OpaqueBeamTarget;

using RefRelease = void(PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL*)(OpaqueBeamTarget*);

struct OpaqueBeamTargetVTable {
  void* slots_00[1];
  RefRelease release_04;
};

struct alignas(4) OpaqueBeamTarget {
  const OpaqueBeamTargetVTable* vtable_00;
  std::uint8_t opaque_004[0x151];
  std::uint8_t state_155;
};

struct alignas(4) OpaqueBeamToolState {
  std::uint8_t opaque_000[0x124];
  OpaqueBeamTarget* owned_beam_target_124;
  std::uint8_t opaque_128[0x4c];
  TargetWord gate_174;
};

struct alignas(4) OpaqueRelationshipState {
  std::uint8_t opaque_000[0x20];
  TargetWord state_20;
  std::uint8_t opaque_024[0x557c];
  TargetWord event_55a0;
};

using RelationshipEventDrain =
    void(PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL*)(OpaqueRelationshipState*);

struct NativePorts {
  RelationshipEventDrain relationship_event_drain_00b77aa0 = nullptr;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueBeamTargetVTable) == 8, "beam target table extent");
static_assert(offsetof(OpaqueBeamTargetVTable, release_04) == 4,
              "beam target release slot offset");
static_assert(offsetof(OpaqueBeamTarget, state_155) == 0x155,
              "beam target state offset");
static_assert(sizeof(OpaqueBeamTarget) == 0x158, "beam target extent");
static_assert(offsetof(OpaqueBeamToolState, owned_beam_target_124) == 0x124,
              "owned beam target pointer offset");
static_assert(offsetof(OpaqueBeamToolState, gate_174) == 0x174,
              "tool gate word offset");
static_assert(sizeof(OpaqueBeamToolState) == 0x178, "tool state extent");
static_assert(offsetof(OpaqueRelationshipState, state_20) == 0x20,
              "relationship state word offset");
static_assert(offsetof(OpaqueRelationshipState, event_55a0) == 0x55a0,
              "relationship event word offset");
static_assert(sizeof(OpaqueRelationshipState) == 0x55a4,
              "relationship state extent");
static_assert(sizeof(RelationshipEventDrain) == 4, "event drain port width");

extern NativePorts g_beam_tool_func4ch_ports;
extern OpaqueRelationshipState* g_relationship_state_0167eb14;

extern "C" void PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
beam_target_mark_00cb3c70(OpaqueBeamTarget*);
extern "C" bool PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
beam_tool_gate_0104cd50(OpaqueBeamToolState*);
extern "C" OpaqueRelationshipState* relationship_get_00b3d3c0();
extern "C" void PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
relationship_state_reset_00b78860(OpaqueRelationshipState*);

extern "C" bool PKG_SIM_BEAMTOOL_FUNC4CH_CDECL
func4_ch_01053db0(OpaqueBeamToolState*);

bool beam_tool_func4_ch_model(OpaqueBeamToolState* tool_state);

}

#undef PKG_SIM_BEAMTOOL_FUNC4CH_THISCALL
#undef PKG_SIM_BEAMTOOL_FUNC4CH_CDECL
