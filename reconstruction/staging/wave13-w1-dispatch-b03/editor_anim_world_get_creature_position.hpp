#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// A three-component single-precision vector, copied as three dwords exactly as
// the body does. Spore/Editors/EditorCreatureController.h and
// Spore/Anim/AnimatedCreature.h both spell this type Math::Vector3.
struct Vector3 {
  float x;
  float y;
  float z;
};

// The receiver. Only the members this body touches are declared, but the two
// that matter are corroborated by Spore/Editors/cEditorAnimWorld.h:
//   /* 08h */ eastl::map<int, EditorCreatureControllerPtr> mCreatures;
//   /* 38h */ IAnimWorldPtr mpAnimWorld;
// and the +0x0c sentinel is the map's own end-of-tree node, reached through the
// map at +0x08.
struct OpaqueEditorAnimWorld {
  unsigned char pad_000_008[8];
  void* map_end_node;   // +0x08 mCreatures, the tree header's end node
  void* map_tree_root;  // +0x0c mCreatures, the tree header's root slot
  unsigned char pad_010_038[0x38 - 0x10];
  void* mpAnimWorld;    // +0x38 IAnimWorldPtr
};

// Spore/Editors/EditorCreatureController.h:
//   /* 08h */ AnimatedCreaturePtr mpAnimatedCreature;
struct OpaqueCreatureController {
  unsigned char pad_000_008[8];
  void* mpAnimatedCreature;  // +0x08
};

// Spore/Anim/AnimatedCreature.h:
//   /* 00h */ vtable, /* 04h */ Vector3 mPosition, /* 10h */ Quaternion ...
struct OpaqueAnimatedCreature {
  void** vtable;    // +0x00
  Vector3 mPosition;  // +0x04
};

// The eastl::map<int, EditorCreatureControllerPtr> at +0x08. The tree header
// is {end_node, root}; a node is {left, right, key, value}. Node layout and the
// find/get ports are taken from 0x00e5c780 and 0x0059c740, whose bodies were
// both read.
struct MapNode {
  MapNode* left;    // +0x00
  MapNode* right;   // +0x04
  int key;          // +0x08
  int padding_0C;
  void* value;      // +0x10
};

struct OpaqueCreatureMap {
  MapNode* end_node;  // +0x00, compared against the receiver's +0x0c
  MapNode* root;      // +0x04
};

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(sizeof(Vector3) == 12, "the out parameter is three floats");
static_assert(offsetof(OpaqueEditorAnimWorld, map_end_node) == 0x08,
              "mCreatures starts at +0x08 and its end node is its first word");
static_assert(offsetof(OpaqueEditorAnimWorld, map_tree_root) == 0x0c,
              "the receiver's +0x0c is the map's root slot, used as the "
              "not-found sentinel by the CMP at 0x0059d13a");
static_assert(offsetof(OpaqueEditorAnimWorld, mpAnimWorld) == 0x38,
              "the gate at 0x0059d119 reads mpAnimWorld at +0x38");
static_assert(offsetof(OpaqueCreatureController, mpAnimatedCreature) == 0x08,
              "EditorCreatureController::mpAnimatedCreature is read at +0x08");
static_assert(offsetof(OpaqueAnimatedCreature, mPosition) == 0x04,
              "the three copied dwords start at AnimatedCreature+0x04");

// Unresolved ports, taken from the two map functions' own decompiled bodies.
namespace unresolved_ports {

// 0x00e5c780(eastl::map* map, MapNode** out, const int* key).
// BST descent; writes the found node, or the map's end node when absent.
extern MapNode* __thiscall creature_map_find(OpaqueCreatureMap*,
                                             MapNode**, const int*);

// 0x0059c740(eastl::map* map, const int* key) -> value slot.
// Find-or-INSERT: it calls the inserter 0x0059c520 and returns the new node's
// value slot when the key is absent. The target only reaches it after a
// successful find, so no insertion can occur on the observed path.
extern void** __thiscall creature_map_get_or_insert(OpaqueCreatureMap*,
                                                    const int*);

}  // namespace unresolved_ports

// 0x0059d110. __thiscall, ECX receiver, two stack arguments cleaned by the
// callee (RET 0x8), boolean byte return.
bool __thiscall editor_anim_world_get_creature_position_0059d110(
    OpaqueEditorAnimWorld*, int creature_id, Vector3* out_position);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
