#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "resource_index.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resources {

struct Property {
  std::array<std::uint8_t, 0x10> opaque_prefix;
  std::uint8_t flags;
  std::uint8_t opaque_0x11;
  std::uint16_t type;
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

struct PropertyList;

using ParentPropertyLookup = bool (*)(PropertyList*, TargetWord, Property**);

struct PropertyListVtable {
  void* slots_00_20[9];
  ParentPropertyLookup get_property_at_24;
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

#if defined(_MSC_VER)
#define WAVE6_PROPERTY_THISCALL __thiscall
#else
#define WAVE6_PROPERTY_THISCALL __attribute__((thiscall))
#endif

bool WAVE6_PROPERTY_THISCALL property_list_get_property_006a2530(
    PropertyList* list, TargetWord property_id, Property** result);

#undef WAVE6_PROPERTY_THISCALL

static_assert(sizeof(Property) == 0x14, "Property extent");
static_assert(offsetof(Property, flags) == 0x10, "Property flags offset");
static_assert(offsetof(Property, type) == 0x12, "Property type offset");
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
static_assert(sizeof(PropertyListVtable) == 0x28,
              "property list vtable prefix extent");
static_assert(offsetof(PropertyListVtable, get_property_at_24) == 0x24,
              "property parent slot offset");
static_assert(sizeof(PropertyList) == 0x38, "PropertyList extent");
static_assert(offsetof(PropertyList, name_key) == 0x08,
              "PropertyList conceptual key offset");
static_assert(offsetof(PropertyList, properties) == 0x18,
              "PropertyList map offset");
static_assert(offsetof(PropertyList, parent) == 0x30,
              "PropertyList parent offset");
static_assert(offsetof(PropertyList, operations_done) == 0x34,
              "PropertyList operation offset");

}
