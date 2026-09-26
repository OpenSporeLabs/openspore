#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-sim-tool-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_TOOL_WAVE9_THISCALL __thiscall
#define PKG_SIM_TOOL_WAVE9_CDECL __cdecl
#else
#define PKG_SIM_TOOL_WAVE9_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOL_WAVE9_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_tool_wave9 {

using TargetWord = std::uint32_t;

inline constexpr TargetWord kDeleteIdentifierValues[] = {
    0x025630b7u, 0x0477c00du, 0x031018b9u, 0x02e9977eu,
    0x032f76e7u, 0x04d80d9eu, 0x00f62defu, 0x0182c582u,
};
inline constexpr TargetWord kDeleteIdentifierCount = 8;
inline constexpr TargetWord kSelectionTable = 0x01403934u;

struct OpaqueOwnerLink;

struct OpaquePooledObject;

using PooledNotify = void(PKG_SIM_TOOL_WAVE9_THISCALL*)(OpaquePooledObject*,
                                                        OpaqueOwnerLink*,
                                                        TargetWord);

struct OpaquePooledObjectVTable {
  void* slots_00[9];
  PooledNotify notify_24;
};

struct alignas(4) OpaquePooledObject {
  const OpaquePooledObjectVTable* vtable_00;
};

struct alignas(4) OpaqueOwnerLink {
  std::uint8_t opaque[1];
};

struct alignas(4) OpaqueDeleteOwner {
  std::uint8_t opaque_000[0x20];
  OpaquePooledObject* published_20;
  OpaqueOwnerLink* link_24;
  const TargetWord* identifiers_28;
  TargetWord identifier_count_2c;
  TargetWord cursor_30;
};

struct alignas(4) OpaqueVector {
  TargetWord x;
  TargetWord y;
  TargetWord z;
};

struct OpaquePositionSource;

using PositionQuery = const OpaqueVector*(
    PKG_SIM_TOOL_WAVE9_THISCALL*)(OpaquePositionSource*, OpaqueVector*,
                                  TargetWord);

struct OpaquePositionVTable {
  void* slots_00[15];
  PositionQuery query_3c;
};

struct alignas(4) OpaquePositionSource {
  const OpaquePositionVTable* vtable_00;
};

struct alignas(4) OpaqueAoEState {
  std::uint8_t opaque[1];
};

struct alignas(4) OpaqueSelectionState {
  const void* vtable_00;
  std::uint8_t opaque_04[8];
};

struct alignas(4) OpaqueSelectionContext {
  std::uint8_t opaque_000[0x12c];
  TargetWord state_12c;
};

struct alignas(4) OpaqueSpecialState {
  const void* vtable_00;
  std::uint8_t opaque_04[8];
};

struct OpaqueBeamTarget;

using RefRelease = void(PKG_SIM_TOOL_WAVE9_THISCALL*)(OpaqueBeamTarget*);

struct OpaqueRefVTable {
  void* add_ref_00;
  RefRelease release_04;
};

struct alignas(4) OpaqueBeamTarget {
  const OpaqueRefVTable* vtable_00;
  std::uint8_t opaque_004[0x151];
  std::uint8_t state_155;
};

struct alignas(4) OpaqueToolState {
  std::uint8_t opaque_000[0x124];
  OpaqueBeamTarget* target_124;
  std::uint8_t opaque_128[0x4c];
  TargetWord state_174;
};

struct alignas(4) OpaqueRelationshipState {
  std::uint8_t opaque_000[0x20];
  TargetWord state_20;
  std::uint8_t opaque_024[0x557c];
  TargetWord state_55a0;
};

using PoolRoot = OpaquePooledObject*(PKG_SIM_TOOL_WAVE9_CDECL*)();
using SelectionTransition =
    void(PKG_SIM_TOOL_WAVE9_CDECL*)(OpaqueSelectionState*);
using SpecialSelect = std::uint8_t(PKG_SIM_TOOL_WAVE9_THISCALL*)(
    OpaqueSpecialState*, OpaqueSelectionContext*, TargetWord, TargetWord);
using EventDrain = void(PKG_SIM_TOOL_WAVE9_THISCALL*)(OpaqueRelationshipState*);

struct NativePorts {
  PoolRoot pool_root_00883860 = nullptr;
  SelectionTransition selection_transition_00f47380 = nullptr;
  SpecialSelect special_select_01053980 = nullptr;
  EventDrain event_drain_00b77aa0 = nullptr;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueVector) == 12, "vector word count");
static_assert(sizeof(OpaquePooledObjectVTable) == 0x28,
              "pooled object table extent");
static_assert(offsetof(OpaquePooledObjectVTable, notify_24) == 0x24,
              "pooled notify slot offset");
static_assert(sizeof(OpaqueDeleteOwner) == 0x34, "delete owner extent");
static_assert(offsetof(OpaqueDeleteOwner, published_20) == 0x20,
              "published object offset");
static_assert(offsetof(OpaqueDeleteOwner, link_24) == 0x24,
              "owner link offset");
static_assert(offsetof(OpaqueDeleteOwner, identifiers_28) == 0x28,
              "identifier table offset");
static_assert(offsetof(OpaqueDeleteOwner, identifier_count_2c) == 0x2c,
              "identifier count offset");
static_assert(offsetof(OpaqueDeleteOwner, cursor_30) == 0x30,
              "identifier cursor offset");
static_assert(sizeof(OpaquePositionVTable) == 0x40,
              "position source table extent");
static_assert(offsetof(OpaquePositionVTable, query_3c) == 0x3c,
              "position query slot offset");
static_assert(sizeof(OpaqueSelectionState) == 0x0c, "selection state extent");
static_assert(sizeof(OpaqueSelectionContext) == 0x130,
              "selection context extent");
static_assert(offsetof(OpaqueSelectionContext, state_12c) == 0x12c,
              "selection sentinel offset");
static_assert(sizeof(OpaqueSpecialState) == 0x0c, "special state extent");
static_assert(sizeof(OpaqueRefVTable) == 8, "reference table extent");
static_assert(offsetof(OpaqueRefVTable, release_04) == 4,
              "reference release slot offset");
static_assert(offsetof(OpaqueBeamTarget, state_155) == 0x155,
              "beam target state offset");
static_assert(sizeof(OpaqueBeamTarget) == 0x158, "beam target extent");
static_assert(offsetof(OpaqueToolState, target_124) == 0x124,
              "beam target pointer offset");
static_assert(offsetof(OpaqueToolState, state_174) == 0x174,
              "tool state word offset");
static_assert(sizeof(OpaqueToolState) == 0x178, "tool state extent");
static_assert(offsetof(OpaqueRelationshipState, state_20) == 0x20,
              "relationship state word offset");
static_assert(offsetof(OpaqueRelationshipState, state_55a0) == 0x55a0,
              "relationship event word offset");
static_assert(sizeof(OpaqueRelationshipState) == 0x55a4,
              "relationship state extent");
static_assert(sizeof(PoolRoot) == 4, "pool root port width");
static_assert(sizeof(SelectionTransition) == 4,
              "selection transition port width");
static_assert(sizeof(SpecialSelect) == 4, "special select port width");
static_assert(sizeof(EventDrain) == 4, "event drain port width");

extern NativePorts g_sim_tool_wave9_ports;
extern OpaquePositionSource* g_position_source_0167eac4;
extern OpaqueRelationshipState* g_relationship_state_0167eb14;

extern "C" OpaquePositionSource* position_source_get_00b3d240();
extern "C" void PKG_SIM_TOOL_WAVE9_THISCALL
beam_mark_00cb3c70(OpaqueBeamTarget*);
extern "C" bool PKG_SIM_TOOL_WAVE9_THISCALL
beam_gate_0104cd50(OpaqueToolState*);
extern "C" OpaqueRelationshipState* relationship_get_00b3d3c0();

extern "C" void PKG_SIM_TOOL_WAVE9_THISCALL target_00b72370(OpaqueDeleteOwner*);
extern "C" void PKG_SIM_TOOL_WAVE9_THISCALL target_01052f90(OpaqueAoEState*,
                                                            OpaqueVector*);
extern "C" OpaqueSelectionState* PKG_SIM_TOOL_WAVE9_THISCALL
target_01053790(OpaqueSelectionState*, TargetWord);
extern "C" bool PKG_SIM_TOOL_WAVE9_CDECL target_01053db0(OpaqueToolState*);
extern "C" bool PKG_SIM_TOOL_WAVE9_THISCALL target_01054080(
    OpaqueSpecialState*, OpaqueSelectionContext*, TargetWord, TargetWord);

}

#undef PKG_SIM_TOOL_WAVE9_THISCALL
#undef PKG_SIM_TOOL_WAVE9_CDECL
