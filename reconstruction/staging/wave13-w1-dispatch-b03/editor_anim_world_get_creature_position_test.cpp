#include "editor_anim_world_get_creature_position.hpp"

#include <cstdio>
#include <cstring>

namespace {

using openspore::reconstruction::wave13_w1_dispatch_b03::MapNode;
using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueAnimatedCreature;
using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueCreatureController;
using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueCreatureMap;
using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueEditorAnimWorld;
using openspore::reconstruction::wave13_w1_dispatch_b03::Vector3;

OpaqueCreatureController g_controller;
// The map's value slot holds the intrusive_ptr, i.e. a pointer to the
// controller, and map_get returns the address of that slot.
void* g_value_slot = nullptr;
int g_find_calls = 0;
int g_get_calls = 0;
int g_insert_calls = 0;
MapNode* g_forced_result = nullptr;

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    std::printf("FAIL %s\n", what);
    ++failures;
  }
}

}  // namespace

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {
namespace unresolved_ports {

MapNode* __thiscall creature_map_find(OpaqueCreatureMap* map, MapNode** out,
                                      const int* key) {
  ++g_find_calls;
  (void)key;
  *out = g_forced_result != nullptr ? g_forced_result : map->end_node;
  return *out;
}

void** __thiscall creature_map_get_or_insert(OpaqueCreatureMap* map,
                                             const int* key) {
  ++g_get_calls;
  (void)map;
  (void)key;
  ++g_insert_calls;
  return &g_value_slot;
}

}  // namespace unresolved_ports
}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  OpaqueEditorAnimWorld world;
  std::memset(&world, 0, sizeof(world));
  world.map_end_node = nullptr;

  // The map's end node lives at world + 0x0c, which is also the not-found
  // sentinel the body compares against.
  MapNode end_node;
  std::memset(&end_node, 0, sizeof(end_node));
  world.map_tree_root = &end_node;

  OpaqueCreatureMap map;
  map.end_node = &end_node;
  map.root = &end_node;

  auto* const map_storage = reinterpret_cast<unsigned char*>(&world);
  std::memcpy(map_storage + 0x08, &map, sizeof(map));

  std::memset(&g_controller, 0, sizeof(g_controller));
  OpaqueAnimatedCreature creature;
  std::memset(&creature, 0, sizeof(creature));
  creature.mPosition.x = 1.5f;
  creature.mPosition.y = -2.25f;
  creature.mPosition.z = 3.75f;

  MapNode found;
  std::memset(&found, 0, sizeof(found));
  found.key = 7;
  found.value = &g_controller;

  Vector3 out;
  std::memset(&out, 0, sizeof(out));

  // Case 1: mpAnimWorld null. 0x0059d121 JZ is taken.
  world.mpAnimWorld = nullptr;
  g_forced_result = &found;
  g_find_calls = g_get_calls = g_insert_calls = 0;
  expect(!editor_anim_world_get_creature_position_0059d110(&world, 7, &out),
         "null anim world: returns false");
  expect(g_find_calls == 0, "null anim world: no map lookup performed");

  // Case 2: anim world present but the key is absent, so find returns the end
  // node. 0x0059d13c JZ is taken.
  world.mpAnimWorld = &end_node;
  g_forced_result = &end_node;
  g_find_calls = g_get_calls = g_insert_calls = 0;
  expect(!editor_anim_world_get_creature_position_0059d110(&world, 7, &out),
         "absent key: returns false");
  expect(g_get_calls == 0,
         "absent key: find-or-insert is never reached, so no insertion");

  // Case 3: key present but the controller has no animated creature.
  g_value_slot = &g_controller;
  g_controller.mpAnimatedCreature = nullptr;
  g_forced_result = &found;
  g_find_calls = g_get_calls = 0;
  expect(!editor_anim_world_get_creature_position_0059d110(&world, 7, &out),
         "null animated creature: returns false");
  expect(g_get_calls == 1, "null animated creature: the get was performed");

  // Case 4: the full success path.
  g_controller.mpAnimatedCreature = &creature;
  g_find_calls = g_get_calls = 0;
  out.x = out.y = out.z = 0.0f;
  expect(editor_anim_world_get_creature_position_0059d110(&world, 7, &out),
         "full path: returns true");
  expect(g_find_calls == 1 && g_get_calls == 1,
         "full path: exactly one find and one get");
  expect(out.x == 1.5f && out.y == -2.25f && out.z == 3.75f,
         "full path: all three components copied from AnimatedCreature+0x04");

  if (failures == 0) {
    std::printf("0059d110 model test: all cases passed\n");
    return 0;
  }
  std::printf("0059d110 model test: %d failure(s)\n", failures);
  return 1;
}
