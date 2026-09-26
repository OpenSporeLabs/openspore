#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG property wave9 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_property_wave9 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

struct OpaquePropertyList;
struct OpaquePropertyListFactory;
struct OpaqueStream;

#if defined(_MSC_VER)
#define PKG_PROPERTY_WAVE9_THISCALL __thiscall
#else
#define PKG_PROPERTY_WAVE9_THISCALL __attribute__((thiscall))
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
    void(PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*);
using SetProperty = void(PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                       TargetWord,
                                                       OpaqueProperty*);
using GetPropertyAlt = bool(PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                          TargetWord,
                                                          OpaqueProperty**);
using GetProperty = bool(PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                       TargetWord,
                                                       OpaqueProperty**);
using GetPropertyObject = OpaqueProperty*(
    PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*, TargetWord);

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

using CreatePropertyListFromKey = OpaquePropertyList*(
    PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyListFactory*, TargetWord,
                                  TargetWord, OpaquePropertyList**);

struct OpaquePropertyListFactoryVtable {
  void* slots_00_28[11];
  CreatePropertyListFromKey create_from_key_2c;
};

struct OpaquePropertyListFactory {
  OpaquePropertyListFactoryVtable* vtable;
};

struct OpaqueWordVector {
  TargetWord* begin;
  TargetWord* end;
  TargetWord* capacity;
};

using PropertyConversion = void(PKG_PROPERTY_WAVE9_THISCALL*)(
    OpaqueProperty*, TargetWord, std::uint16_t, const void*, TargetWord,
    TargetWord);
using PropertyErrorPort = void (*)(TargetWord, OpaqueProperty*, TargetWord,
                                   TargetWord, TargetWord, TargetWord);
using MapCopy = OpaquePropertyMap*(
    PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyMap*, const OpaquePropertyMap*);
using SetParent = void(PKG_PROPERTY_WAVE9_THISCALL*)(OpaquePropertyList*,
                                                     OpaquePropertyList*);
using ReadWords = bool (*)(OpaqueStream*, TargetWord*, TargetWord, TargetWord);
using ReadProperty = bool (*)(OpaqueStream*, OpaqueProperty*, TargetWord);
using GetPropertyListFactory = OpaquePropertyListFactory* (*)();
using ResizeWordVector = void(PKG_PROPERTY_WAVE9_THISCALL*)(OpaqueWordVector*,
                                                            TargetWord);

struct PropertyListRuntime {
  PropertyConversion conversion;
  PropertyErrorPort error;
  MapCopy map_copy;
  SetParent set_parent;
  ReadWords read_words;
  ReadProperty read_property;
  GetPropertyListFactory get_factory;
  ResizeWordVector resize_words;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueProperty) == 0x14, "opaque property size");
static_assert(offsetof(OpaqueProperty, flags) == 0x10,
              "opaque property flags offset");
static_assert(offsetof(OpaqueProperty, type) == 0x12,
              "opaque property type offset");
static_assert(sizeof(OpaquePropertyEntry) == 0x18,
              "opaque property entry stride");
static_assert(offsetof(OpaquePropertyEntry, property) == 0x04,
              "opaque property entry value offset");
static_assert(sizeof(OpaquePropertyMap) == 0x18, "opaque property map size");
static_assert(offsetof(OpaquePropertyMap, begin) == 0x00,
              "opaque property map begin offset");
static_assert(offsetof(OpaquePropertyMap, end) == 0x04,
              "opaque property map end offset");
static_assert(offsetof(OpaquePropertyMap, capacity) == 0x08,
              "opaque property map capacity offset");
static_assert(offsetof(OpaquePropertyMap, lookup_mode) == 0x14,
              "opaque property map lookup mode offset");
static_assert(sizeof(OpaquePropertyList) == 0x54, "opaque property list size");
static_assert(offsetof(OpaquePropertyList, properties) == 0x18,
              "opaque property list map offset");
static_assert(offsetof(OpaquePropertyList, parent) == 0x30,
              "opaque property list parent offset");
static_assert(offsetof(OpaquePropertyList, operations_done) == 0x34,
              "opaque property list operation count offset");
static_assert(offsetof(OpaquePropertyList, fast_count) == 0x38,
              "opaque property list fast count offset");
static_assert(offsetof(OpaquePropertyList, fast_values) == 0x3c,
              "opaque property list fast values offset");
static_assert(offsetof(OpaquePropertyList, opaque_40_53) == 0x40,
              "opaque property list tail offset");
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
static_assert(offsetof(OpaquePropertyListFactoryVtable, create_from_key_2c) ==
                  0x2c,
              "property list factory creation slot offset");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "word vector size");

PropertyListRuntime& property_list_runtime();

void PKG_PROPERTY_WAVE9_THISCALL
direct_property_list_add_properties_from_006a1600(OpaquePropertyList* list,
                                                  OpaquePropertyList* other);
bool PKG_PROPERTY_WAVE9_THISCALL direct_property_list_get_property_alt_006a1e50(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty** result);
void PKG_PROPERTY_WAVE9_THISCALL property_list_copy_from_006a2a40(
    OpaquePropertyList* list, OpaquePropertyList* other);
void PKG_PROPERTY_WAVE9_THISCALL
property_list_clear_006a2a80(OpaquePropertyList* list);
void PKG_PROPERTY_WAVE9_THISCALL direct_property_list_copy_from_006a2ad0(
    OpaquePropertyList* list, OpaquePropertyList* other);
void PKG_PROPERTY_WAVE9_THISCALL
direct_property_list_clear_006a2b20(OpaquePropertyList* list);
void PKG_PROPERTY_WAVE9_THISCALL property_list_set_property_006a2e20(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty* value);
TargetSignedWord PKG_PROPERTY_WAVE9_THISCALL
property_list_remove_property_006a2ef0(OpaquePropertyList* list,
                                       TargetWord property_id);
void PKG_PROPERTY_WAVE9_THISCALL property_list_add_properties_from_006a2f10(
    OpaquePropertyList* list, OpaquePropertyList* other);
bool PKG_PROPERTY_WAVE9_THISCALL
property_list_read_006a2f60(OpaquePropertyList* list, OpaqueStream* stream);
void PKG_PROPERTY_WAVE9_THISCALL property_list_get_property_ids_006a3070(
    OpaquePropertyList* list, OpaqueWordVector* destination);

#undef PKG_PROPERTY_WAVE9_THISCALL

}
