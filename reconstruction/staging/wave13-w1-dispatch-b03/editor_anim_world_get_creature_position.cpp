#include "editor_anim_world_get_creature_position.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

namespace {

using unresolved_ports::creature_map_find;
using unresolved_ports::creature_map_get_or_insert;

OpaqueCreatureMap* as_map(OpaqueEditorAnimWorld* world) {
  return reinterpret_cast<OpaqueCreatureMap*>(world->map_end_node);
}

// 0x0059d137 ADD EDI,0xc with EDI = this: the receiver's +0x0c, which is the
// map's root slot and, per 0x00e5c780, the value it stores when the key is
// absent. Comparing the find result against it is the not-found test.
MapNode* not_found_sentinel(const OpaqueEditorAnimWorld* world) {
  return const_cast<MapNode*>(
      static_cast<const MapNode*>(world->map_tree_root));
}

}  // namespace

// Reconstructed body of 0x0059d110 (104 bytes, 43 instructions, image base
// 0x00400000). See reconstruction/metadata/wave13-w1-dispatch-b03/0059d110.json.
//
// Three sequential guards, then a 12-byte copy:
//   1. mpAnimWorld must be non-null                       [+0x38]
//   2. mCreatures must contain creature_id                [map at +0x08]
//   3. controller->mpAnimatedCreature must be non-null    [+0x08 of +0x08]
// Only then are three dwords copied from AnimatedCreature+0x04, which is
// AnimatedCreature::mPosition.
//
// The sibling at 0x0059ca70 is the SDK-declared
// Editors::cEditorAnimWorld::GetAnimatedCreature and carries a byte-identical
// lookup preamble; this function is the same lookup that hands back the
// position instead of the pointer.
bool __thiscall editor_anim_world_get_creature_position_0059d110(
    OpaqueEditorAnimWorld* world, int creature_id, Vector3* out_position) {
  // 0x0059d119 CMP dword ptr [EDI + 0x38],0x0 / 0x0059d121 JZ 0x0059d170
  if (world->mpAnimWorld == nullptr) {
    return false;
  }

  OpaqueCreatureMap* const map = as_map(world);

  // 0x0059d123 LEA ECX,[ESP+0x10] / 0x0059d127 PUSH ECX
  // 0x0059d128 LEA EDX,[ESP+0xc]  / 0x0059d12f PUSH EDX
  // 0x0059d130 MOV ECX,ESI / 0x0059d132 CALL 0x00e5c780
  MapNode* node = nullptr;
  creature_map_find(map, &node, &creature_id);

  // 0x0059d137 ADD EDI,0xc / 0x0059d13a CMP dword ptr [EAX],EDI
  // 0x0059d13c JZ 0x0059d170
  if (node == not_found_sentinel(world)) {
    return false;
  }

  // 0x0059d13e LEA EAX,[ESP+0x10] / 0x0059d142 PUSH ECX
  // 0x0059d143 MOV ECX,ESI / 0x0059d145 CALL 0x0059c740
  // 0x0059d14a MOV ECX,dword ptr [EAX]
  // The find above proved the key exists, so this find-or-insert cannot insert.
  OpaqueCreatureController* const controller =
      static_cast<OpaqueCreatureController*>(
          *creature_map_get_or_insert(map, &creature_id));

  // 0x0059d14c MOV EAX,dword ptr [ECX + 0x8] / 0x0059d14f TEST EAX,EAX
  // 0x0059d151 JZ 0x0059d170
  OpaqueAnimatedCreature* const creature =
      static_cast<OpaqueAnimatedCreature*>(controller->mpAnimatedCreature);
  if (creature == nullptr) {
    return false;
  }

  // 0x0059d153 MOV EDX,[EAX+0x4] / 0x0059d15a MOV [ECX],EDX
  // 0x0059d15c MOV EDX,[EAX+0x8] / 0x0059d15f MOV [ECX+0x4],EDX
  // 0x0059d162 MOV EAX,[EAX+0xc] / 0x0059d166 MOV [ECX+0x8],EAX
  // Three dword moves, not a 12-byte block move, and ECX here is the caller's
  // out pointer loaded at 0x0059d156 from [ESP+0x14].
  out_position->x = creature->mPosition.x;
  out_position->y = creature->mPosition.y;
  out_position->z = creature->mPosition.z;

  // 0x0059d169 MOV AL,0x1 - only the low byte of EAX is written, so bits 8..31
  // are undefined on the success path. Every observed caller tests AL.
  return true;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
