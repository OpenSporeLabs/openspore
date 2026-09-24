#include "map_search.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>

namespace openspore::reconstruction::pkg20_gameglobal {

using Snapshot = std::array<std::uint8_t, sizeof(OrderedMap)>;

Snapshot snapshot(const OrderedMap &map) {
  Snapshot result{};
  std::memcpy(result.data(), &map, result.size());
  return result;
}

bool unchanged(const OrderedMap &map, const Snapshot &before) {
  return std::memcmp(&map, before.data(), before.size()) == 0;
}

void run() {
  OrderedMap map{};
  OrderedMapEntry low{};
  OrderedMapEntry middle{};
  OrderedMapEntry high{};

  low.key = 10;
  middle.key = 20;
  high.key = 30;
  middle.base.left = &low.base;
  middle.base.right = &high.base;
  map.anchor.parent = &middle.base;
  map.size = 3;

  const Snapshot before = snapshot(map);
  OrderedMapEntry *sentinel = reinterpret_cast<OrderedMapEntry *>(&map.anchor);
  OrderedMapEntry *result = nullptr;
  TargetWord query = 20;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == &middle);
  assert(unchanged(map, before));

  query = 25;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));

  query = 5;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));

  query = 35;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
}

}  // namespace openspore::reconstruction::pkg20_gameglobal

int main() {
  openspore::reconstruction::pkg20_gameglobal::run();
}
