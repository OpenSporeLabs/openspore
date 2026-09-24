#include "map_search.hpp"

namespace openspore::reconstruction::pkg20_gameglobal {

#if defined(_MSC_VER)
#define PKG20_THISCALL __thiscall
#else
#define PKG20_THISCALL __attribute__((thiscall))
#endif

void PKG20_THISCALL pkg20_gameglobal_00e5c780(
    OrderedMap *map, OrderedMapEntry **result, const TargetWord *key) {
  OrderedMapEntry *node =
      reinterpret_cast<OrderedMapEntry *>(map->anchor.parent);
  OrderedMapEntry *candidate =
      reinterpret_cast<OrderedMapEntry *>(&map->anchor);
  const TargetWord query = *key;

  while (node != nullptr) {
    if (node->key < query) {
      node = reinterpret_cast<OrderedMapEntry *>(node->base.left);
    } else {
      candidate = node;
      node = reinterpret_cast<OrderedMapEntry *>(node->base.right);
    }
  }

  if (candidate != reinterpret_cast<OrderedMapEntry *>(&map->anchor) &&
      candidate->key <= query) {
    *result = candidate;
  } else {
    *result = reinterpret_cast<OrderedMapEntry *>(&map->anchor);
  }
}

#undef PKG20_THISCALL

}
