#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG proplist-setprop w15 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_proplist_setprop_w15 {

using TargetWord = std::uint32_t;

// App::Property -- 0x14 bytes.
// Read directly out of the 0x00542b80 body: the fast path copies four dwords
// from source+0x00..+0x0f into destination+0x00..+0x0f, then writes the type
// word at +0x12 and recomposes the flags word at +0x10 as
// (source.flags & ~0x0002) | (destination.flags & 0x0002). Nothing beyond
// +0x13 is ever touched, so 0x14 is the size.
struct Property {
  std::array<std::uint8_t, 0x10> field_00_0f;
  std::uint16_t field_10;  // flags
  std::uint16_t field_12;  // type
};

// One property map slot -- 0x18 stride.
// The stride is the literal 0x18 in the element-count division inside the
// search at 0x00612db0 (`(last - first) / 0x18`, reached as
// `IMUL 0x2aaaaaab; SAR EDX,2; SHR EDI,31; ADD EDI,EDX; LEA EAX,[EAX+EDX*8]`
// in the 0x006a2940 insert helper) and the `+ 0x18` step in the 0x006a2940
// splice. The key occupies +0x00 and the Property occupies +0x04:
// 0x006a2940 stores the seed's leading dword at slot+0x00, then takes
// `LEA ECX,[EAX + 4]` as the destination Property and clears its words at
// +0x10 and +0x12 before assigning the seed's +4 Property into it.
struct MapEntry {
  TargetWord field_00;    // property id / map key
  Property field_04;      // 0x14 bytes, ends the 0x18 stride
};

// The sorted property array embedded at PropertyList+0x18.
// 0x006a2c50 reads begin at map+0x00 ([ESI]), end at map+0x04 ([ESI+4]) and the
// mode byte at map+0x14 (MOVZX EAX,byte ptr [ESI + 0x14]); 0x006a2940 appends
// with `MOV [ESI + 4], end + 0x18`. Those three offsets are therefore fixed.
struct PropertyMap {
  MapEntry* field_00;                            // begin
  MapEntry* field_04;                            // end
  std::array<std::uint8_t, 0x0c> field_08_13;
  std::uint8_t field_14;                         // mode, passed to the search
};

// Result of 0x006a2c50: an 8-byte out record {iterator, inserted}.
// 0x006a2c50 writes `MOV dword ptr [ECX],EAX` then either
// `MOV byte ptr [ECX + 4],0x0` (the key was already present) or
// `MOV byte ptr [ECX + 4],0x1` (the 0x006a2940 splice ran), and returns that
// same record pointer in EAX.
struct MapLookup {
  MapEntry* field_00;
  std::uint8_t field_04;
  std::uint8_t field_05_07[3];
};

// App::PropertyList.
// Only 0x18/0x1c/0x2c/0x34 are touched by 0x006a2e20 itself and each is proven
// by its own disassembly. 0x30/0x38/0x3c/0x40 are carried over from the already
// reviewed sibling layout in pkg-direct-property-wave6 and are NOT re-derived
// here; they are commented so the distinction survives promotion.
struct PropertyList {
  void* field_00;                              // vtable 0x01408820, slot 0x14
  TargetWord field_04;
  std::array<std::uint8_t, 0x0c> field_08_13;
  void* field_14;
  PropertyMap field_18;                        // proven: begin/end/mode
  // field_1c is PropertyMap::field_04 and field_2c is PropertyMap::field_14
  void* field_30;                              // carried from sibling package
  TargetWord field_34;                         // proven: operation counter
  TargetWord field_38;                         // carried from sibling package
  TargetWord* field_3c;                        // carried from sibling package
  Property field_40;                           // carried from sibling package
};

#if defined(_MSC_VER)
#define PKG15_SETPROP_THISCALL __thiscall
#else
#define PKG15_SETPROP_THISCALL __attribute__((thiscall))
#endif

// 0x00542b80: Property copy/assign, RET 0x4. Destination in ECX, source as one
// stack argument. Reports through 0x0093db80 with argument 1 when the
// destination's own flags carry bit 0x0004, and reinterprets through
// 0x00542c30 when the fast-copy preconditions do not hold.
using PropertyAssign = Property* (PKG15_SETPROP_THISCALL*)(Property*,
                                                             Property*);
// 0x0093db80: single-word property reporter, RET 0x4. Receiver in ECX, one
// stack word. With argument 0 it returns immediately; with argument 1 it zeroes
// the receiver's words at +0x10 and +0x12 when bit 0x0002 is clear.
using SeedErrorPort = void (PKG15_SETPROP_THISCALL*)(MapEntry*, TargetWord);
// 0x006a2c50: map find-or-insert, RET 0x8. Map in ECX, out record and seed as
// two stack arguments; the callee cleans them.
using MapFindOrInsert = MapLookup* (PKG15_SETPROP_THISCALL*)(PropertyMap*,
                                                              MapLookup*,
                                                              MapEntry*);

// 0x00612db0, reproduced because it is the exact search 0x006a2e20 runs before
// choosing the assign arm over the insert arm. Its stride and key are the ones
// MapEntry documents.
MapEntry* property_map_lower_bound(const PropertyMap& map, TargetWord key);

void set_property_assign(PropertyAssign assign);
void set_seed_error_port(SeedErrorPort port);
void set_map_find_or_insert(MapFindOrInsert find_or_insert);

// App::PropertyList::SetProperty @ 006a2e20, reached as vtable 0x01408820
// slot 0x14. Receiver in ECX; exactly two stack arguments (RET 0x8).
void PKG15_SETPROP_THISCALL property_set_006a2e20(
    PropertyList* list, TargetWord property_id, Property* value);

#undef PKG15_SETPROP_THISCALL

}
