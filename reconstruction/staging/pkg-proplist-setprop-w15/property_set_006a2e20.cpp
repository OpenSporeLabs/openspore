#include "property_set_006a2e20.hpp"

#if defined(_MSC_VER)
#define PKG15_SETPROP_THISCALL __thiscall
#else
#define PKG15_SETPROP_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_proplist_setprop_w15 {
namespace {

PropertyAssign property_assign = nullptr;
SeedErrorPort seed_error_port = nullptr;
MapFindOrInsert map_find_or_insert = nullptr;

void PKG15_SETPROP_THISCALL no_seed_error_port(MapEntry*, TargetWord) {}

}

// 0x00612db0: lower_bound over an array of 0x18-stride entries keyed on the
// leading dword. Recomputed here because it is the exact predicate 0x006a2e20
// applies to its own map before deciding assign vs. insert. The listing shows
// the element count as ((last - first) / 0x18) and the key compare as an
// unsigned `CMP`/`JB` pair, i.e. `middle->field_00 < key`.
MapEntry* property_map_lower_bound(const PropertyMap& map, TargetWord key) {
  auto* first = map.field_00;
  auto* last = map.field_04;
  auto count = static_cast<std::ptrdiff_t>(
      (reinterpret_cast<std::uintptr_t>(last) -
       reinterpret_cast<std::uintptr_t>(first)) /
      sizeof(MapEntry));
  while (count > 0) {
    const auto step = static_cast<std::size_t>(count >> 1);
    auto* middle = reinterpret_cast<MapEntry*>(
        reinterpret_cast<std::uintptr_t>(first) + step * sizeof(MapEntry));
    if (middle->field_00 < key) {
      first = reinterpret_cast<MapEntry*>(
          reinterpret_cast<std::uintptr_t>(middle) + sizeof(MapEntry));
      count = count - static_cast<std::ptrdiff_t>(step) - 1;
    } else {
      count = static_cast<std::ptrdiff_t>(step);
    }
  }
  return first;
}

void set_property_assign(PropertyAssign assign) { property_assign = assign; }

void set_seed_error_port(SeedErrorPort port) {
  seed_error_port = port == nullptr ? no_seed_error_port : port;
}

void set_map_find_or_insert(MapFindOrInsert find_or_insert) {
  map_find_or_insert = find_or_insert;
}

// App::PropertyList::SetProperty @ 006a2e20.
//
// VIRTUAL DISPATCH: the body occupies slot 0x14 of vtable 0x01408820. Read
// directly from the binary, 64 bytes at 0x01408820 little-endian:
//   +0x08 0x006a1c80  +0x0c 0x006abe20  +0x10 0x00432940  +0x14 0x006a2e20
//   +0x18 0x006a2ef0  +0x1c 0x006a2470  +0x20 0x006a2530  +0x24 0x006a24d0
//   +0x28 0x006a2a40  +0x2c 0x006a1de0  +0x30 0x006a2530  +0x34 0x006a24d0
//   +0x38 0x006a2a40  +0x3c 0x006a2f10  +0x40 0x006a14d0  +0x44 0x006a1510
//   +0x48 0x006a2f60
// so the fifth slot after the two leading destructor-shaped entries holds this
// body, and the SDK export agrees (SetProperty at vftable offset 20 = 0x14).
//
// ABI: RET 0x8 is the whole story. `this` arrives in ECX and exactly two
// explicit arguments follow it on the stack -- arg1 is the property id, arg2 is
// the Property*. The prologue/epilogue pair proves the two-argument form
// independently: after `ADD ESP,0x2c` from the register pops ESP is exactly the
// entry ESP, and `RET 0x8` then consumes the return address plus the two
// argument words. Ghidra's three-parameter prototype is an artifact of the
// function's "Unknown calling convention" classification and is one parameter
// wide; nothing reads a third stack slot. The receiver itself is never read
// back into EAX on any path, so the return type is void.
//
// FRAME: the body installs a structured exception frame over the whole scope
// (`MOV EAX,FS:[0x0]` / `PUSH -1` / `PUSH 0x120d6b8` / `PUSH EAX` /
// `MOV FS:[0x0],ESP`, torn down by `MOV ECX,[ESP + 0x2c]` /
// `MOV FS:[0x0],ECX` at the join). Resolving every [ESP+k] in this body
// against the entry ESP gives: the SEH record at entry-0x0c, the 8-byte
// find-or-insert out record at entry-0x30, a 4-byte compiler state mirror
// written 0 then 0xffffffff at entry-0x2c, the 0x18-byte seed entry at
// entry-0x24, and therefore the seed Property at entry-0x20 with its flags word
// at entry-0x10 and its type word at entry-0x0e. That is why the two zeroing
// stores and the later bit test all land on the seed Property's own words. The
// frame itself has no C++ spelling that is portable to this target, so only its
// observable consequence is modelled.
//
// The two zeroing stores and the post-insert test resolve to the same word only
// under this reading, so they are not independent observations.
void PKG15_SETPROP_THISCALL property_set_006a2e20(
    PropertyList* list, TargetWord property_id, Property* value) {
  MapEntry* found = property_map_lower_bound(list->field_18, property_id);
  // 0x006a2e5e `CMP EAX,EBX` / `JZ` rejects the end iterator; 0x006a2e62
  // `CMP EDX,[EAX]` followed by 0x006a2e64 rejects a found key above the id.
  // That branch is `JC` -- Ghidra's carry-set synonym for the `JB rel8`
  // (opcode 0x72) that the bytes at 0x006a2e64 actually contain -- so it is the
  // unsigned below test `property_id < *found`, exactly as modelled. This is
  // the one instruction in the 0x006a2e20 listing that the toolchain's listing
  // grammar does not consume: `JB` is in the grammar and its `JC` synonym is
  // not, so the instruction is reported unparsed and the whole listing is
  // flagged degraded. It is a real instruction and is reproduced here, not
  // dropped. The `LEA ECX,[EAX + 0x18]` / `CMP EAX,ECX` / `JNZ` triple that
  // follows is the always-true one-past-the-end overflow probe the search
  // leaves behind, so only the two tests above carry the decision.
  if (found != list->field_18.field_04 && !(property_id < found->field_00)) {
    // 0x006a2e79 `LEA ECX,[EAX + 0x4]` -- the existing entry's Property is the
    // assign destination. No insertion and no map mutation on this arm.
    property_assign(&found->field_04, value);
  } else {
    MapEntry seed{};
    seed.field_00 = property_id;
    // 0x006a2e8f / 0x006a2e94 zero the seed Property's flags (entry-0x10) and
    // type (entry-0x0e) before the assign, because 0x00542b80 reads the
    // destination's own bit 0x0002 and bit 0x0004 before it overwrites them.
    seed.field_04.field_10 = 0;
    seed.field_04.field_12 = 0;
    property_assign(&seed.field_04, value);

    MapLookup lookup{};
    map_find_or_insert(&list->field_18, &lookup, &seed);

    // 0x006a2eb7 `TEST byte ptr [ESP + 0x28],0x4` reads the low byte of the
    // word just zeroed, i.e. bit 0x0004 of the seed Property's flags, which the
    // assign above mirrored in from the source. 0x0093db80 is called with
    // ECX = the seed entry and the pushed argument 0; with that argument the
    // callee returns after its own identical bit test, so the call is
    // observationally inert and the source value came from a read-only
    // Property. The 8-byte out record is not consulted.
    if ((seed.field_04.field_10 & 0x4u) != 0) {
      seed_error_port(&seed, 0u);
    }
  }
  // Reached from both arms: 0x006a2e81 jumps straight here and the insert arm
  // falls through, so the counter moves exactly once per call.
  ++list->field_34;
}

#undef PKG15_NOOP_THISCALL
#undef PKG15_SETPROP_THISCALL

}
