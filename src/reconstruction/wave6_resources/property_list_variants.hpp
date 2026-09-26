#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::wave6_resources {

using TargetWord = std::uint32_t;

struct Property {
  std::array<std::uint8_t, 0x14> opaque_00_13;
};

struct PropertyMapEntry {
  TargetWord key;
  Property property;
};

struct PropertyMap {
  PropertyMapEntry* entries_begin;
  PropertyMapEntry* entries_end;
  std::array<std::uint8_t, 0x0c> opaque_08_13;
  std::uint8_t lookup_mode;
  std::array<std::uint8_t, 3> opaque_0d_0f;
};

struct PropertyListVtable;

struct ResourceKey {
  TargetWord instance_id;
  TargetWord type_id;
  TargetWord group_id;
};

struct PropertyList {
  PropertyListVtable* vftable;
  TargetWord ref_count;
  ResourceKey name_key;
  void* final_release_callback;
  PropertyMap properties;
  PropertyList* parent;
  TargetWord operations_done;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(Property) == 0x14, "property extent");
static_assert(sizeof(PropertyMapEntry) == 0x18, "property entry stride");
static_assert(offsetof(PropertyMapEntry, property) == 0x04,
              "property entry value offset");
static_assert(sizeof(PropertyMap) == 0x18, "property map extent");
static_assert(offsetof(PropertyMap, entries_begin) == 0,
              "property map begin offset");
static_assert(offsetof(PropertyMap, entries_end) == 4,
              "property map end offset");
static_assert(offsetof(PropertyMap, lookup_mode) == 0x14,
              "property map lookup mode offset");
static_assert(sizeof(PropertyList) == 0x38, "property list extent");
static_assert(offsetof(PropertyList, name_key) == 0x08,
              "property list conceptual key offset");
static_assert(offsetof(PropertyList, properties) == 0x18,
              "property list map offset");
static_assert(offsetof(PropertyList, parent) == 0x30,
              "property list parent offset");
static_assert(offsetof(PropertyList, operations_done) == 0x34,
              "property list operation offset");

#if defined(_MSC_VER)
#define WAVE6_VARIANT_THISCALL __thiscall
#else
#define WAVE6_VARIANT_THISCALL __attribute__((thiscall))
#endif

using HasParentLookup = bool(WAVE6_VARIANT_THISCALL*)(PropertyList* list,
                                                      TargetWord property_id);

struct HasParentVtable {
  void* slots_00_18[7];
  HasParentLookup get_at_1c;
};

using ObjectParentLookup = Property*(
    WAVE6_VARIANT_THISCALL*)(PropertyList * list, TargetWord property_id);

struct ObjectParentVtable {
  void* slots_00_24[10];
  ObjectParentLookup get_at_28;
};

bool WAVE6_VARIANT_THISCALL
property_list_has_property_006a2470(PropertyList* list, TargetWord property_id);
Property* WAVE6_VARIANT_THISCALL property_list_get_property_object_006a24d0(
    PropertyList* list, TargetWord property_id);

#undef WAVE6_VARIANT_THISCALL

static_assert(offsetof(HasParentVtable, get_at_1c) == 0x1c,
              "HasProperty parent slot offset");
static_assert(offsetof(ObjectParentVtable, get_at_28) == 0x28,
              "GetPropertyObject parent slot offset");

}
