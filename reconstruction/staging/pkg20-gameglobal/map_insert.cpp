#include "map_insert.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG20_INSERT_THISCALL __thiscall
#else
#define PKG20_INSERT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg20_gameglobal {

namespace {

void store_node_value(OrderedMapEntry* node, TargetWord value) {
  auto* bytes = reinterpret_cast<unsigned char*>(node);
  std::memcpy(bytes + kMapNodeValueOffset, &value, sizeof(value));
}

}

void PKG20_INSERT_THISCALL pkg20_gameglobal_00ba83a0(
    OrderedMap* map, MapInsertResult* output, OrderedMapEntry* parent,
    const MapInsertPair* pair, std::uint8_t insertion_side) {
  const auto* anchor = reinterpret_cast<const OrderedMapEntry*>(&map->anchor);
  std::uint32_t side = 0;
  if (insertion_side == 0 && parent != anchor) {
    side = parent->key <= pair->key ? 1u : 0u;
  }

  void* allocation = pkg20_map_allocate_00f473a0(
      kMapNodeAllocationSize, "Simulator", 0, 0,
      reinterpret_cast<const char*>(0x013ebb38u), kMapAllocationSourceLine);
  auto* node = static_cast<OrderedMapEntry*>(allocation);
  node->key = pair->key;
  store_node_value(node, pair->value);

  pkg20_map_rebalance_009216a0(node, parent, &map->anchor, side);
  ++map->size;
  output->entry = node;
}

MapInsertResult* PKG20_INSERT_THISCALL
pkg20_gameglobal_00ba8420(OrderedMap* map, MapInsertResult* output,
                          void* handoff, const MapInsertPair* pair) {
  (void)handoff;
  const TargetWord key = pair->key;
  auto* anchor = reinterpret_cast<OrderedMapEntry*>(&map->anchor);
  auto* candidate = anchor;
  auto* node = reinterpret_cast<OrderedMapEntry*>(map->anchor.parent);
  bool went_right = true;

  while (node != nullptr) {
    candidate = node;
    went_right = key < node->key;
    node = went_right ? reinterpret_cast<OrderedMapEntry*>(node->base.right)
                      : reinterpret_cast<OrderedMapEntry*>(node->base.left);
  }

  if (went_right &&
      candidate != reinterpret_cast<OrderedMapEntry*>(&map->anchor.right)) {
    candidate = pkg20_map_predecessor_009215c0(candidate);
  }

  if (candidate->key >= key) {
    output->entry = candidate;
    output->inserted = 0;
    return output;
  }

  MapInsertResult inserted{};
  pkg20_gameglobal_00ba83a0(map, &inserted, candidate, pair, 0);
  output->entry = inserted.entry;
  output->inserted = 1;
  return output;
}

#undef PKG20_INSERT_THISCALL

}
