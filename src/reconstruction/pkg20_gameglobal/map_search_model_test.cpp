#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>

#include "map_search.hpp"

namespace openspore::reconstruction::pkg20_gameglobal {

using MapSnapshot = std::array<std::uint8_t, sizeof(OrderedMap)>;
using EntrySnapshot = std::array<std::uint8_t, sizeof(OrderedMapEntry)>;

MapSnapshot snapshot(const OrderedMap& map) {
  MapSnapshot result{};
  std::memcpy(result.data(), &map, result.size());
  return result;
}

EntrySnapshot snapshot(const OrderedMapEntry& entry) {
  EntrySnapshot result{};
  std::memcpy(result.data(), &entry, result.size());
  return result;
}

bool unchanged(const OrderedMap& map, const MapSnapshot& before) {
  return std::memcmp(&map, before.data(), before.size()) == 0;
}

bool unchanged(const OrderedMapEntry& entry, const EntrySnapshot& before) {
  return std::memcmp(&entry, before.data(), before.size()) == 0;
}

void run() {
  OrderedMap exact_map{};
  OrderedMapEntry exact{};
  exact.key = 20;
  exact_map.anchor.parent = &exact.base;
  exact_map.size = 1;

  const MapSnapshot exact_map_before = snapshot(exact_map);
  const EntrySnapshot exact_entry_before = snapshot(exact);
  OrderedMapEntry* exact_result = nullptr;
  TargetWord exact_query = 20;
  pkg20_gameglobal_00e5c780(&exact_map, &exact_result, &exact_query);
  assert(exact_result == &exact);
  assert(unchanged(exact_map, exact_map_before));
  assert(unchanged(exact, exact_entry_before));

  OrderedMap empty_map{};
  const MapSnapshot empty_before = snapshot(empty_map);
  OrderedMapEntry* empty_sentinel =
      reinterpret_cast<OrderedMapEntry*>(&empty_map.anchor);
  OrderedMapEntry* empty_result = nullptr;
  TargetWord empty_query = 20;
  pkg20_gameglobal_00e5c780(&empty_map, &empty_result, &empty_query);
  assert(empty_result == empty_sentinel);
  assert(unchanged(empty_map, empty_before));

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

  const MapSnapshot before = snapshot(map);
  const EntrySnapshot low_before = snapshot(low);
  const EntrySnapshot middle_before = snapshot(middle);
  const EntrySnapshot high_before = snapshot(high);
  OrderedMapEntry* sentinel = reinterpret_cast<OrderedMapEntry*>(&map.anchor);
  OrderedMapEntry* result = nullptr;
  TargetWord query = 20;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
  assert(unchanged(low, low_before));
  assert(unchanged(middle, middle_before));
  assert(unchanged(high, high_before));

  query = 10;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
  assert(unchanged(low, low_before));
  assert(unchanged(middle, middle_before));
  assert(unchanged(high, high_before));

  query = 25;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
  assert(unchanged(low, low_before));
  assert(unchanged(middle, middle_before));
  assert(unchanged(high, high_before));

  query = 5;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
  assert(unchanged(low, low_before));
  assert(unchanged(middle, middle_before));
  assert(unchanged(high, high_before));

  query = 35;
  pkg20_gameglobal_00e5c780(&map, &result, &query);
  assert(result == sentinel);
  assert(unchanged(map, before));
  assert(unchanged(low, low_before));
  assert(unchanged(middle, middle_before));
  assert(unchanged(high, high_before));
}

}

int main() { openspore::reconstruction::pkg20_gameglobal::run(); }
