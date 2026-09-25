#pragma once

#include <cstddef>
#include <cstdint>

#include "../pkg20_gameglobal/map_search.hpp"

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_sim_core {

using TargetWord = pkg20_gameglobal::TargetWord;
using OrderedMap = pkg20_gameglobal::OrderedMap;
using OrderedMapEntry = pkg20_gameglobal::OrderedMapEntry;

struct NounProjectionVector {
  std::uint8_t needs_update;
  std::uint8_t padding[3];
  void* begin;
  void* end;
  void* capacity;
  std::int32_t garbage;
  void* allocator;
};

struct NounMapEntry {
  OrderedMapEntry entry;
  NounProjectionVector* value;
};

struct NounMapPair {
  TargetWord key;
  NounProjectionVector* value;
};

struct NounMapInsertResult {
  NounMapEntry* entry;
  std::uint8_t inserted;
};

struct NounListNode {
  std::uint8_t prefix[0x0c];
  void* next_link;
};

struct NounProjection {
  std::uint8_t prefix[0x6c];
  NounListNode list_sentinel;
  std::uint8_t gap[0x1c];
  OrderedMap noun_map;
};

using NounCreateCallback = NounProjectionVector* (*)();
using NounClearCallback = void (*)(NounProjectionVector*);
using NounAddCallback = void (*)(NounProjectionVector*, NounListNode*);
using NounFilterCallback = std::uint8_t (*)(NounListNode*, TargetWord);

static_assert(sizeof(NounProjectionVector) == 24, "PKG-11 noun vector size");
static_assert(offsetof(NounProjectionVector, needs_update) == 0x00,
              "PKG-11 noun vector dirty offset");
static_assert(offsetof(NounProjectionVector, begin) == 0x04,
              "PKG-11 noun vector begin offset");
static_assert(offsetof(NounProjectionVector, end) == 0x08,
              "PKG-11 noun vector end offset");
static_assert(offsetof(NounProjectionVector, capacity) == 0x0c,
              "PKG-11 noun vector capacity offset");
static_assert(offsetof(NounProjectionVector, garbage) == 0x10,
              "PKG-11 noun vector garbage offset");
static_assert(offsetof(NounProjectionVector, allocator) == 0x14,
              "PKG-11 noun vector allocator offset");
static_assert(sizeof(NounMapEntry) == 24, "PKG-11 map entry size");
static_assert(offsetof(NounMapEntry, value) == 0x14, "PKG-11 map value offset");
static_assert(sizeof(NounMapPair) == 8, "PKG-11 map pair size");
static_assert(offsetof(NounMapPair, key) == 0x00, "PKG-11 map pair key offset");
static_assert(offsetof(NounMapPair, value) == 0x04,
              "PKG-11 map pair value offset");
static_assert(sizeof(NounMapInsertResult) == 8,
              "PKG-11 map insertion result size");
static_assert(offsetof(NounMapInsertResult, entry) == 0x00,
              "PKG-11 map insertion entry offset");
static_assert(offsetof(NounMapInsertResult, inserted) == 0x04,
              "PKG-11 map insertion flag offset");
static_assert(sizeof(NounListNode) == 16, "PKG-11 noun list node size");
static_assert(offsetof(NounListNode, next_link) == 0x0c,
              "PKG-11 noun list next offset");
static_assert(offsetof(NounProjection, list_sentinel) == 0x6c,
              "PKG-11 noun list sentinel offset");
static_assert(offsetof(NounProjection, noun_map) == 0x98,
              "PKG-11 noun map offset");
static_assert(sizeof(NounProjection) == 0xb4,
              "PKG-11 noun projection layout size");

#if defined(_MSC_VER)
#define PKG11_THISCALL __thiscall
#else
#define PKG11_THISCALL __attribute__((thiscall))
#endif

NounMapInsertResult* PKG11_THISCALL
noun_projection_insert_00ba8420(OrderedMap* map, NounMapInsertResult* output,
                                const NounMapPair* pair, void* context);

NounProjectionVector* PKG11_THISCALL pkg11_sim_core_00b21340(
    NounProjection* projection, NounCreateCallback create_callback,
    NounClearCallback clear_callback, NounAddCallback add_callback,
    NounFilterCallback filter_callback, TargetWord noun_id);

#undef PKG11_THISCALL

}
