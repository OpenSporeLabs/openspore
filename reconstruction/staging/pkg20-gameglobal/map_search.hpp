#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-20 staging requires an x86-32 target and has no 64-bit fallback"
#endif

namespace openspore::reconstruction::pkg20_gameglobal {

using TargetWord = std::uint32_t;

struct OrderedMapNode {
  OrderedMapNode *left;
  OrderedMapNode *right;
  OrderedMapNode *parent;
  TargetWord color;
};

struct OrderedMapEntry {
  OrderedMapNode base;
  TargetWord key;
};

struct OrderedMap {
  void *compare;
  OrderedMapNode anchor;
  TargetWord size;
  void *allocator;
};

static_assert(sizeof(TargetWord) == 4, "PKG-20 target words are 32-bit");
static_assert(sizeof(void *) == 4, "PKG-20 target pointers are 32-bit");
static_assert(sizeof(OrderedMapNode) == 16,
              "PKG-20 ordered-map base nodes match the observed prefix");
static_assert(offsetof(OrderedMapNode, left) == 0x00,
              "PKG-20 node left offset");
static_assert(offsetof(OrderedMapNode, right) == 0x04,
              "PKG-20 node right offset");
static_assert(offsetof(OrderedMapNode, parent) == 0x08,
              "PKG-20 node parent offset");
static_assert(offsetof(OrderedMapNode, color) == 0x0c,
              "PKG-20 node color offset");
static_assert(sizeof(OrderedMapEntry) == 20,
              "PKG-20 keyed ordered-map entries match the observed prefix");
static_assert(offsetof(OrderedMapEntry, key) == 0x10,
              "PKG-20 node key offset");
static_assert(sizeof(OrderedMap) == 28, "PKG-20 ordered-map size");
static_assert(offsetof(OrderedMap, compare) == 0x00,
              "PKG-20 map comparator offset");
static_assert(offsetof(OrderedMap, anchor) == 0x04,
              "PKG-20 map anchor offset");
static_assert(offsetof(OrderedMap, size) == 0x14, "PKG-20 map size offset");
static_assert(offsetof(OrderedMap, allocator) == 0x18,
              "PKG-20 map allocator offset");

#if defined(_MSC_VER)
#define PKG20_THISCALL __thiscall
#else
#define PKG20_THISCALL __attribute__((thiscall))
#endif

void PKG20_THISCALL pkg20_gameglobal_00e5c780(
    OrderedMap *map, OrderedMapEntry **result, const TargetWord *key);

#undef PKG20_THISCALL

}
