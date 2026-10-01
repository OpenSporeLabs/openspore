#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg_sim_f00bba790 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SIM_F00BBA790_THISCALL __thiscall
#else
#define PKG_SIM_F00BBA790_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sim_f00bba790 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

struct OpaqueSimNode;
struct OpaqueSimNodeDispatchTable;
struct OpaqueWordVector;
struct OpaqueSimState;

using NodeNotify = void(PKG_SIM_F00BBA790_THISCALL*)(OpaqueSimNode*);
using NodeKeepPending =
    std::uint8_t(PKG_SIM_F00BBA790_THISCALL*)(OpaqueSimNode*);
using StateRefresh = void(PKG_SIM_F00BBA790_THISCALL*)(OpaqueSimState*);
using VectorReserve =
    void(PKG_SIM_F00BBA790_THISCALL*)(OpaqueWordVector*, OpaqueSimNode**,
                                      OpaqueSimNode**);
using VectorResize = void(PKG_SIM_F00BBA790_THISCALL*)(OpaqueWordVector*,
                                                       TargetSignedWord);
using VectorGrowInsert =
    void(PKG_SIM_F00BBA790_THISCALL*)(OpaqueWordVector*, OpaqueSimNode**,
                                       OpaqueSimNode**);

struct OpaqueSimNodeDispatchTable {
  NodeNotify notify_00;
};

struct OpaqueSimNode {
  const OpaqueSimNodeDispatchTable* dispatch_table_00;
};

struct OpaqueWordVector {
  OpaqueSimNode** begin;
  OpaqueSimNode** end;
  OpaqueSimNode** capacity;
};

struct OpaqueSimState {
  std::uint8_t opaque_00_5b[0x5c];
  TargetWord state_5c;
  std::uint8_t opaque_60_83[0x24];
  OpaqueWordVector pending_84;
  std::uint8_t opaque_90_97[0x08];
  OpaqueWordVector active_98;
};

struct SimPorts {
  StateRefresh refresh_00bba640;
  VectorReserve reserve_00e25bd0;
  VectorResize resize_00d01790;
  NodeKeepPending keep_pending_00b8d970;
  VectorGrowInsert grow_insert_00aea5d0;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(TargetSignedWord) == 4, "target signed words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueSimNodeDispatchTable) == 4,
              "only the first dispatch slot is observed");
static_assert(offsetof(OpaqueSimNodeDispatchTable, notify_00) == 0x00,
              "dispatch slot offset");
static_assert(sizeof(OpaqueSimNode) == 4, "node extent reaches offset +0x04");
static_assert(offsetof(OpaqueSimNode, dispatch_table_00) == 0x00,
              "node table pointer offset");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "three-word vector extent");
static_assert(offsetof(OpaqueWordVector, begin) == 0x00, "vector begin offset");
static_assert(offsetof(OpaqueWordVector, end) == 0x04, "vector end offset");
static_assert(offsetof(OpaqueWordVector, capacity) == 0x08,
              "vector capacity offset");
static_assert(sizeof(OpaqueSimState) == 0xa4, "receiver observed extent");
static_assert(offsetof(OpaqueSimState, state_5c) == 0x5c,
              "state word offset");
static_assert(offsetof(OpaqueSimState, pending_84) == 0x84,
              "pending vector offset");
static_assert(offsetof(OpaqueSimState, active_98) == 0x98,
              "active vector offset");
static_assert(sizeof(NodeNotify) == 4, "node notify port width");
static_assert(sizeof(NodeKeepPending) == 4, "keep-pending port width");
static_assert(sizeof(StateRefresh) == 4, "refresh port width");
static_assert(sizeof(VectorReserve) == 4, "reserve port width");
static_assert(sizeof(VectorResize) == 4, "resize port width");
static_assert(sizeof(VectorGrowInsert) == 4, "grow-insert port width");
static_assert(sizeof(SimPorts) == 20,
              "five direct call targets, one word of port each");

SimPorts& sim_f00bba790_ports();
void sim_f00bba790_set_ports(const SimPorts& ports);
void sim_f00bba790_reset_ports();

OpaqueWordVector* PKG_SIM_F00BBA790_THISCALL
sim_00bba790_flush_pending_and_select_vector(OpaqueSimState* state);

#undef PKG_SIM_F00BBA790_THISCALL

}
