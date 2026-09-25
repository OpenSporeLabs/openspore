#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-20 property adapter requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg20_property_adapter {

using TargetWord = std::uint32_t;

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

struct DirectPropertyList {
  void* vftable;
  TargetWord ref_count;
  std::array<std::uint8_t, 0x0c> name_key;
  void* final_release_callback;
  PropertyMap properties;
  void* parent;
  TargetWord operations_done;
  TargetWord fast_access_count;
  TargetWord* values;
  std::array<std::uint8_t, 0x14> opaque_40_53;
};

using MaterializeProperty = void (*)(Property& destination,
                                     const Property& source);
using CleanupProperty = void (*)(Property& property, TargetWord argument);

struct PropertyAdapterServices {
  MaterializeProperty materialize;
  CleanupProperty cleanup;
};

static_assert(sizeof(TargetWord) == 4, "PKG-20 target words are 32-bit");
static_assert(sizeof(void*) == 4, "PKG-20 target pointers are 32-bit");
static_assert(sizeof(Property) == 0x14,
              "PKG-20 observed temporary Property extent");
static_assert(offsetof(Property, flags) == 0x10,
              "PKG-20 observed Property flags offset");
static_assert(offsetof(Property, type) == 0x12,
              "PKG-20 observed Property type offset");
static_assert(sizeof(PropertyMapEntry) == 0x18,
              "PKG-20 observed map entry stride");
static_assert(offsetof(PropertyMapEntry, property) == 0x04,
              "PKG-20 observed map property offset");
static_assert(sizeof(PropertyMap) == 0x18,
              "PKG-20 observed property-map extent");
static_assert(offsetof(PropertyMap, entries_begin) == 0x00,
              "PKG-20 property-map begin offset");
static_assert(offsetof(PropertyMap, entries_end) == 0x04,
              "PKG-20 property-map end offset");
static_assert(offsetof(PropertyMap, lookup_mode) == 0x14,
              "PKG-20 property-map lookup mode offset");
static_assert(sizeof(DirectPropertyList) == 0x54,
              "PKG-20 DirectPropertyList extent");
static_assert(offsetof(DirectPropertyList, properties) == 0x18,
              "PKG-20 DirectPropertyList map offset");
static_assert(offsetof(DirectPropertyList, fast_access_count) == 0x38,
              "PKG-20 DirectPropertyList fast-count offset");
static_assert(offsetof(DirectPropertyList, values) == 0x3c,
              "PKG-20 DirectPropertyList values offset");
static_assert(offsetof(DirectPropertyList, opaque_40_53) == 0x40,
              "PKG-20 DirectPropertyList opaque tail offset");

#if defined(_MSC_VER)
#define PKG20_PROPERTY_THISCALL __thiscall
#else
#define PKG20_PROPERTY_THISCALL __attribute__((thiscall))
#endif

PropertyAdapterServices& property_adapter_services();

bool PKG20_PROPERTY_THISCALL app_direct_property_list_get_direct_bool_006a25a0(
    DirectPropertyList* list, TargetWord property_id);

#undef PKG20_PROPERTY_THISCALL

}
