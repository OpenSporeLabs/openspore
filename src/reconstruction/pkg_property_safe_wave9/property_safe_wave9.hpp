#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG property safe wave9 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_property_safe_wave9 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

struct OpaquePropertyList;

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_THISCALL __attribute__((thiscall))
#endif

struct OpaqueProperty {
  std::array<std::uint8_t, 0x10> value;
  std::uint16_t flags;
  std::uint16_t type;
};

struct OpaquePropertyEntry {
  TargetWord id;
  OpaqueProperty property;
};

struct OpaquePropertyMap {
  OpaquePropertyEntry* begin;
  OpaquePropertyEntry* end;
  OpaquePropertyEntry* capacity;
  std::array<std::uint8_t, 8> opaque_0c_13;
  std::uint8_t lookup_mode;
  std::array<std::uint8_t, 3> opaque_15_17;
};

using ReleasePropertyList =
    void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*);
using SetProperty = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                            TargetWord,
                                                            OpaqueProperty*);
using GetPropertyAlt = bool(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(
    OpaquePropertyList*, TargetWord, OpaqueProperty**);
using GetProperty = bool(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                            TargetWord,
                                                            OpaqueProperty**);
using GetPropertyObject = OpaqueProperty*(
    PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*, TargetWord);

struct OpaquePropertyListVtable {
  void* slot_00;
  ReleasePropertyList release_04;
  void* slots_08_10[3];
  SetProperty set_property_14;
  void* slot_18;
  void* slot_1c;
  GetPropertyAlt get_property_alt_20;
  GetProperty get_property_24;
  GetPropertyObject get_property_object_28;
  void* slots_2c_48[8];
};

struct OpaquePropertyList {
  OpaquePropertyListVtable* vtable;
  TargetWord ref_count;
  std::array<std::uint8_t, 0x0c> name_key;
  void* release_callback;
  OpaquePropertyMap properties;
  OpaquePropertyList* parent;
  TargetWord operations_done;
  TargetWord fast_count;
  TargetWord* fast_values;
  std::array<std::uint8_t, 0x14> opaque_40_53;
};

struct OpaqueWordVector {
  TargetWord* begin;
  TargetWord* end;
  TargetWord* capacity;
};

using MapCopy = OpaquePropertyMap*(
    PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyMap*,
                                       const OpaquePropertyMap*);
using SetParent = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                          OpaquePropertyList*);
using ResizeWordVector =
    void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(OpaqueWordVector*, TargetWord);
using PropertyConvert = void(PKG_PROPERTY_SAFE_WAVE9_THISCALL*)(
    OpaqueProperty*, TargetWord, std::uint16_t, const void*, TargetWord,
    TargetWord);
using PropertyCleanup = void (*)(TargetWord, OpaqueProperty*, TargetWord,
                                 TargetWord, TargetWord, TargetWord);

struct PropertySafePorts {
  PropertyCleanup cleanup;
  PropertyConvert convert;
  MapCopy map_copy;
  SetParent set_parent;
  ResizeWordVector resize_words;
  GetPropertyAlt get_property_alt_base;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueProperty) == 0x14, "opaque property size");
static_assert(offsetof(OpaqueProperty, value) == 0x00, "property value offset");
static_assert(offsetof(OpaqueProperty, flags) == 0x10, "property flags offset");
static_assert(offsetof(OpaqueProperty, type) == 0x12, "property type offset");
static_assert(sizeof(OpaquePropertyEntry) == 0x18, "property entry stride");
static_assert(offsetof(OpaquePropertyEntry, id) == 0x00, "entry id offset");
static_assert(offsetof(OpaquePropertyEntry, property) == 0x04,
              "entry property offset");
static_assert(sizeof(OpaquePropertyMap) == 0x18, "property map size");
static_assert(offsetof(OpaquePropertyMap, begin) == 0x00, "map begin offset");
static_assert(offsetof(OpaquePropertyMap, end) == 0x04, "map end offset");
static_assert(offsetof(OpaquePropertyMap, capacity) == 0x08,
              "map capacity offset");
static_assert(offsetof(OpaquePropertyMap, lookup_mode) == 0x14,
              "map lookup mode offset");
static_assert(sizeof(OpaquePropertyList) == 0x54, "property list size");
static_assert(offsetof(OpaquePropertyList, properties) == 0x18,
              "property list map offset");
static_assert(offsetof(OpaquePropertyList, parent) == 0x30,
              "property list parent offset");
static_assert(offsetof(OpaquePropertyList, operations_done) == 0x34,
              "property list operation count offset");
static_assert(offsetof(OpaquePropertyList, fast_count) == 0x38,
              "property list fast count offset");
static_assert(offsetof(OpaquePropertyList, fast_values) == 0x3c,
              "property list fast values offset");
static_assert(offsetof(OpaquePropertyList, opaque_40_53) == 0x40,
              "property list tail offset");
static_assert(offsetof(OpaquePropertyList, ref_count) == 0x04,
              "property list reference count offset");
static_assert(offsetof(OpaquePropertyListVtable, release_04) == 0x04,
              "property list release slot offset");
static_assert(offsetof(OpaquePropertyListVtable, set_property_14) == 0x14,
              "property list set slot offset");
static_assert(offsetof(OpaquePropertyListVtable, get_property_alt_20) == 0x20,
              "property list alternate get slot offset");
static_assert(offsetof(OpaquePropertyListVtable, get_property_24) == 0x24,
              "property list get slot offset");
static_assert(offsetof(OpaquePropertyListVtable, get_property_object_28) ==
                  0x28,
              "property list object get slot offset");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "word vector size");
static_assert(offsetof(OpaqueWordVector, begin) == 0x00,
              "word vector begin offset");
static_assert(offsetof(OpaqueWordVector, end) == 0x04,
              "word vector end offset");
static_assert(offsetof(OpaqueWordVector, capacity) == 0x08,
              "word vector capacity offset");

PropertySafePorts& property_safe_ports();
void property_safe_set_ports(const PropertySafePorts& ports);
void property_safe_reset_ports();

void PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other);
bool PKG_PROPERTY_SAFE_WAVE9_THISCALL
direct_property_list_get_property_alt_006a1e50(OpaquePropertyList* list,
                                               TargetWord property_id,
                                               OpaqueProperty** result);
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other);
void PKG_PROPERTY_SAFE_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination);

#undef PKG_PROPERTY_SAFE_WAVE9_THISCALL

}
