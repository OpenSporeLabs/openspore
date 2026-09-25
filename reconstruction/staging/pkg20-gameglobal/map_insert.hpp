#pragma once

#include <cstddef>
#include <cstdint>

#include "map_search.hpp"

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-20 map insertion staging requires an x86-32 target"
#endif

extern "C" void* __cdecl pkg20_map_allocate_00f473a0(std::uint32_t size,
                                                     const char* domain,
                                                     std::uint32_t flags,
                                                     std::uint32_t alignment,
                                                     const char* source_path,
                                                     std::uint32_t source_line);

extern "C" openspore::reconstruction::pkg20_gameglobal::OrderedMapEntry* __cdecl
pkg20_map_predecessor_009215c0(
    openspore::reconstruction::pkg20_gameglobal::OrderedMapEntry* node);

extern "C" void __cdecl pkg20_map_rebalance_009216a0(
    openspore::reconstruction::pkg20_gameglobal::OrderedMapEntry* node,
    openspore::reconstruction::pkg20_gameglobal::OrderedMapEntry* parent,
    openspore::reconstruction::pkg20_gameglobal::OrderedMapNode* anchor,
    std::uint32_t side);

namespace openspore::reconstruction::pkg20_gameglobal {

using TargetWord = pkg20_gameglobal::TargetWord;

struct MapInsertPair {
  TargetWord key;
  TargetWord value;
};

struct MapInsertResult {
  OrderedMapEntry* entry;
  std::uint8_t inserted;
};

static_assert(sizeof(MapInsertPair) == 8, "map insertion pair size");
static_assert(offsetof(MapInsertPair, key) == 0x00, "map insertion key offset");
static_assert(offsetof(MapInsertPair, value) == 0x04,
              "map insertion value offset");
static_assert(sizeof(MapInsertResult) == 8, "map insertion result size");
static_assert(offsetof(MapInsertResult, entry) == 0x00,
              "map insertion entry offset");
static_assert(offsetof(MapInsertResult, inserted) == 0x04,
              "map insertion flag offset");
static_assert(sizeof(OrderedMapEntry) == 20, "shared map entry prefix size");
static_assert(offsetof(OrderedMapEntry, key) == 0x10, "shared map key offset");
static_assert(sizeof(OrderedMap) == 28, "shared map size");
static_assert(offsetof(OrderedMap, anchor) == 0x04, "shared map anchor offset");
static_assert(offsetof(OrderedMap, size) == 0x14, "shared map size offset");

inline constexpr std::uint32_t kMapNodeAllocationSize = 0x18;
inline constexpr std::uint32_t kMapNodeValueOffset = 0x14;
inline constexpr std::uint32_t kMapAllocationSourceLine = 0xd1;

#if defined(_MSC_VER)
#define PKG20_INSERT_THISCALL __thiscall
#else
#define PKG20_INSERT_THISCALL __attribute__((thiscall))
#endif

void PKG20_INSERT_THISCALL pkg20_gameglobal_00ba83a0(
    OrderedMap* map, MapInsertResult* output, OrderedMapEntry* parent,
    const MapInsertPair* pair, std::uint8_t insertion_side);

MapInsertResult* PKG20_INSERT_THISCALL
pkg20_gameglobal_00ba8420(OrderedMap* map, MapInsertResult* output,
                          void* handoff, const MapInsertPair* pair);

#undef PKG20_INSERT_THISCALL

}
