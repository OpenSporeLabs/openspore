#include <cassert>
#include <cstdint>
#include <cstring>

#include "map_insert.hpp"

namespace {

using openspore::reconstruction::pkg20_gameglobal::MapInsertPair;
using openspore::reconstruction::pkg20_gameglobal::MapInsertResult;
using openspore::reconstruction::pkg20_gameglobal::OrderedMap;
using openspore::reconstruction::pkg20_gameglobal::OrderedMapEntry;
using openspore::reconstruction::pkg20_gameglobal::OrderedMapNode;
using openspore::reconstruction::pkg20_gameglobal::pkg20_gameglobal_00ba83a0;
using openspore::reconstruction::pkg20_gameglobal::pkg20_gameglobal_00ba8420;
using openspore::reconstruction::pkg20_gameglobal::TargetWord;

alignas(4) unsigned char allocation[0x18];
std::uint32_t allocation_calls;
std::uint32_t allocation_size;
std::uint32_t allocation_flags;
std::uint32_t allocation_alignment;
std::uint32_t allocation_line;
const char* allocation_domain;
const char* allocation_path;
std::uint32_t predecessor_calls;
OrderedMapEntry* predecessor_result;
std::uint32_t rebalance_calls;
OrderedMapEntry* rebalance_node;
OrderedMapEntry* rebalance_parent;
OrderedMapNode* rebalance_anchor;
std::uint32_t rebalance_side;

void reset() {
  std::memset(allocation, 0, sizeof(allocation));
  allocation_calls = 0;
  allocation_size = 0;
  allocation_flags = 0;
  allocation_alignment = 0;
  allocation_line = 0;
  allocation_domain = nullptr;
  allocation_path = nullptr;
  predecessor_calls = 0;
  predecessor_result = nullptr;
  rebalance_calls = 0;
  rebalance_node = nullptr;
  rebalance_parent = nullptr;
  rebalance_anchor = nullptr;
  rebalance_side = 0;
}

void initialize_map(OrderedMap& map) {
  map = OrderedMap{};
  map.anchor.left = &map.anchor;
  map.anchor.right = &map.anchor;
  map.anchor.parent = nullptr;
  map.anchor.color = 0;
}

}

extern "C" void* __cdecl pkg20_map_allocate_00f473a0(
    std::uint32_t size, const char* domain, std::uint32_t flags,
    std::uint32_t alignment, const char* source_path,
    std::uint32_t source_line) {
  ++allocation_calls;
  allocation_size = size;
  allocation_domain = domain;
  allocation_flags = flags;
  allocation_alignment = alignment;
  allocation_path = source_path;
  allocation_line = source_line;
  return allocation;
}

extern "C" OrderedMapEntry* __cdecl pkg20_map_predecessor_009215c0(
    OrderedMapEntry* node) {
  ++predecessor_calls;
  predecessor_result = node;
  return node;
}

extern "C" void __cdecl pkg20_map_rebalance_009216a0(OrderedMapEntry* node,
                                                     OrderedMapEntry* parent,
                                                     OrderedMapNode* anchor,
                                                     std::uint32_t side) {
  ++rebalance_calls;
  rebalance_node = node;
  rebalance_parent = parent;
  rebalance_anchor = anchor;
  rebalance_side = side;
  node->base.left = nullptr;
  node->base.right = nullptr;
  node->base.parent = reinterpret_cast<OrderedMapNode*>(parent);
  node->base.color = 0;
  auto* anchor_entry = reinterpret_cast<OrderedMapEntry*>(anchor);
  auto* node_base = &node->base;
  auto* parent_base = &parent->base;
  if (side == 0) {
    parent_base->right = node_base;
    if (parent == anchor_entry) {
      anchor->parent = node_base;
    } else if (parent == reinterpret_cast<OrderedMapEntry*>(&anchor->right)) {
      anchor->right = node_base;
    }
  } else {
    parent_base->left = node_base;
    if (parent == anchor_entry) {
      anchor->left = node_base;
    } else if (parent == reinterpret_cast<OrderedMapEntry*>(&anchor->left)) {
      anchor->left = node_base;
    }
  }
}

namespace {

TargetWord node_value(OrderedMapEntry* node) {
  TargetWord value = 0;
  std::memcpy(&value, reinterpret_cast<unsigned char*>(node) + 0x14,
              sizeof(value));
  return value;
}

void test_empty_insert_allocates_and_hands_off() {
  OrderedMap map;
  initialize_map(map);
  reset();
  MapInsertPair pair{0x12345678u, 0xabcdef01u};
  MapInsertResult output{reinterpret_cast<OrderedMapEntry*>(0x1), 0xa5};

  MapInsertResult* returned =
      pkg20_gameglobal_00ba8420(&map, &output, nullptr, &pair);

  assert(returned == &output);
  assert(allocation_calls == 1);
  assert(allocation_size == 0x18);
  assert(std::strcmp(allocation_domain, "Simulator") == 0);
  assert(allocation_flags == 0);
  assert(allocation_alignment == 0);
  assert(allocation_path == reinterpret_cast<const char*>(0x013ebb38u));
  assert(allocation_line == 0xd1);
  assert(predecessor_calls == 1);
  assert(rebalance_calls == 1);
  assert(rebalance_node == reinterpret_cast<OrderedMapEntry*>(allocation));
  assert(rebalance_parent == reinterpret_cast<OrderedMapEntry*>(&map.anchor));
  assert(rebalance_anchor == &map.anchor);
  assert(rebalance_side == 0);
  assert(output.entry == reinterpret_cast<OrderedMapEntry*>(allocation));
  assert(output.inserted == 1);
  assert(map.size == 1);
  assert(output.entry->key == pair.key);
  assert(node_value(output.entry) == pair.value);
  assert(output.entry->base.left == nullptr);
  assert(output.entry->base.right == nullptr);
  assert(output.entry->base.parent == &map.anchor);
  assert(output.entry->base.color == 0);
  assert(map.anchor.parent == &output.entry->base);
  assert(map.anchor.right == &output.entry->base);
}

void test_duplicate_returns_existing_without_allocation() {
  OrderedMap map;
  initialize_map(map);
  OrderedMapEntry existing{};
  existing.key = 0x42;
  map.anchor.parent = &existing.base;
  map.size = 1;
  reset();
  MapInsertPair pair{0x42, 0x99};
  MapInsertResult output{reinterpret_cast<OrderedMapEntry*>(0x1), 0xa5};

  MapInsertResult* returned =
      pkg20_gameglobal_00ba8420(&map, &output, nullptr, &pair);

  assert(returned == &output);
  assert(output.entry == &existing);
  assert(output.inserted == 0);
  assert(allocation_calls == 0);
  assert(predecessor_calls == 0);
  assert(rebalance_calls == 0);
  assert(map.size == 1);
  assert(existing.key == 0x42);
}

void test_in_between_insert_selects_parent_side() {
  OrderedMap map;
  initialize_map(map);
  OrderedMapEntry existing{};
  existing.key = 20;
  map.anchor.parent = &existing.base;
  map.size = 1;
  reset();
  MapInsertPair pair{25, 0x11223344u};
  MapInsertResult output{reinterpret_cast<OrderedMapEntry*>(0x1), 0xa5};

  MapInsertResult* returned =
      pkg20_gameglobal_00ba8420(&map, &output, nullptr, &pair);

  assert(returned == &output);
  assert(output.entry == reinterpret_cast<OrderedMapEntry*>(allocation));
  assert(output.inserted == 1);
  assert(allocation_calls == 1);
  assert(predecessor_calls == 0);
  assert(rebalance_calls == 1);
  assert(rebalance_parent == &existing);
  assert(rebalance_side == 1);
  assert(existing.base.left == &output.entry->base);
  assert(output.entry->base.parent == &existing.base);
  assert(map.size == 2);
  assert(output.entry->key == 25);
  assert(node_value(output.entry) == pair.value);
}

void test_empty_zero_key_uses_anchor_alias() {
  OrderedMap map;
  initialize_map(map);
  reset();
  MapInsertPair pair{0, 0xaabbccddu};
  MapInsertResult output{reinterpret_cast<OrderedMapEntry*>(0x1), 0xa5};

  MapInsertResult* returned =
      pkg20_gameglobal_00ba8420(&map, &output, nullptr, &pair);

  assert(returned == &output);
  assert(output.entry == reinterpret_cast<OrderedMapEntry*>(&map.anchor));
  assert(output.inserted == 0);
  assert(allocation_calls == 0);
  assert(rebalance_calls == 0);
  assert(map.size == 0);
}

void test_direct_helper_copies_pair_and_preserves_result_flag() {
  OrderedMap map;
  initialize_map(map);
  reset();
  MapInsertPair pair{0x55, 0xaa};
  MapInsertResult output{reinterpret_cast<OrderedMapEntry*>(0x1), 0x7f};

  pkg20_gameglobal_00ba83a0(
      &map, &output, reinterpret_cast<OrderedMapEntry*>(&map.anchor), &pair, 1);

  assert(allocation_calls == 1);
  assert(rebalance_calls == 1);
  assert(rebalance_parent == reinterpret_cast<OrderedMapEntry*>(&map.anchor));
  assert(rebalance_side == 0);
  assert(output.entry == reinterpret_cast<OrderedMapEntry*>(allocation));
  assert(output.inserted == 0x7f);
  assert(map.size == 1);
  assert(output.entry->key == pair.key);
  assert(node_value(output.entry) == pair.value);
}

}

int main() {
  test_empty_insert_allocates_and_hands_off();
  test_duplicate_returns_existing_without_allocation();
  test_in_between_insert_selects_parent_side();
  test_empty_zero_key_uses_anchor_alias();
  test_direct_helper_copies_pair_and_preserves_result_flag();
}
