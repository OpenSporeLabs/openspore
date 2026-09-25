#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG direct-property wave6 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_direct_property_wave6 {

using TargetWord = std::uint32_t;

struct OpaqueProperty;
struct OpaqueList;
struct OpaquePropertyService;
struct OpaqueBaseObject;

struct OpaqueProperty {
  std::array<std::uint8_t, 0x10> field_00_0f;
  std::uint16_t field_10;
  std::uint16_t field_12;
};

struct OpaqueMapEntry {
  TargetWord field_00;
  OpaqueProperty field_04;
};

struct OpaqueMap {
  OpaqueMapEntry* field_00;
  OpaqueMapEntry* field_04;
  std::array<std::uint8_t, 0x0c> field_08_13;
  std::uint8_t field_14;
  std::array<std::uint8_t, 3> field_15_17;
};

struct OpaqueWordVector {
  TargetWord* field_00;
  TargetWord* field_04;
  TargetWord* field_08;
};

using OpaquePropertyResolver = OpaqueProperty* (*)(
    OpaquePropertyService*, TargetWord);
using OpaqueListSetProperty = void (*)(OpaqueList*, TargetWord,
                                        OpaqueProperty*);
using OpaqueListGetProperty = OpaqueProperty* (*)(OpaqueList*, TargetWord);
using OpaqueBaseHasProperty = bool (*)(OpaqueBaseObject*, TargetWord);
using OpaqueBaseGetProperty = bool (*)(OpaqueBaseObject*, TargetWord,
                                         OpaqueProperty**);
using OpaqueBaseGetPropertyObject = OpaqueProperty* (*)(OpaqueBaseObject*,
                                                         TargetWord);
using OpaqueBaseInsert = void (*)(OpaqueList*, TargetWord, OpaqueProperty*);
using OpaqueErrorPort = void (*)(TargetWord);
using OpaqueTypeConversion = void (*)(TargetWord, TargetWord, const void*,
                                      TargetWord, TargetWord);

struct OpaquePropertyServiceVtable {
  void* field_00_4c[20];
  OpaquePropertyResolver field_50;
};

struct OpaquePropertyService {
  const OpaquePropertyServiceVtable* field_00;
};

struct OpaqueListVtable {
  void* field_00_10[5];
  OpaqueListSetProperty field_14;
  void* field_18_24[4];
  OpaqueListGetProperty field_28;
};

struct OpaqueBaseVtable {
  void* field_00_18[7];
  OpaqueBaseHasProperty field_1c;
  void* field_20;
  OpaqueBaseGetProperty field_24;
  OpaqueBaseGetPropertyObject field_28;
};

struct OpaqueBaseObject {
  const OpaqueBaseVtable* field_00;
};

struct OpaqueList {
  const OpaqueListVtable* field_00;
  TargetWord field_04;
  std::array<std::uint8_t, 0x0c> field_08_13;
  void* field_14;
  OpaqueMap field_18;
  OpaqueBaseObject* field_30;
  TargetWord field_34;
  TargetWord field_38;
  TargetWord* field_3c;
  OpaqueProperty field_40;
};

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueProperty) == 0x14, "opaque property size");
static_assert(offsetof(OpaqueProperty, field_10) == 0x10,
              "opaque property field_10 offset");
static_assert(offsetof(OpaqueProperty, field_12) == 0x12,
              "opaque property field_12 offset");
static_assert(sizeof(OpaqueMapEntry) == 0x18, "opaque map entry stride");
static_assert(offsetof(OpaqueMapEntry, field_04) == 0x04,
              "opaque map property offset");
static_assert(sizeof(OpaqueMap) == 0x18, "opaque map size");
static_assert(offsetof(OpaqueMap, field_04) == 0x04,
              "opaque map end offset");
static_assert(offsetof(OpaqueMap, field_14) == 0x14,
              "opaque map mode offset");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "opaque vector size");
static_assert(offsetof(OpaqueWordVector, field_04) == 0x04,
              "opaque vector end offset");
static_assert(offsetof(OpaqueWordVector, field_08) == 0x08,
              "opaque vector capacity offset");
static_assert(offsetof(OpaqueList, field_18) == 0x18,
              "opaque list map offset");
static_assert(offsetof(OpaqueList, field_30) == 0x30,
              "opaque list fallback offset");
static_assert(offsetof(OpaqueList, field_34) == 0x34,
              "opaque list operation offset");
static_assert(offsetof(OpaqueList, field_38) == 0x38,
              "opaque list fast count offset");
static_assert(offsetof(OpaqueList, field_3c) == 0x3c,
              "opaque list values offset");
static_assert(offsetof(OpaqueList, field_40) == 0x40,
              "opaque list fast property offset");
static_assert(sizeof(OpaqueList) == 0x54, "opaque list size");
static_assert(offsetof(OpaquePropertyServiceVtable, field_50) == 0x50,
              "property service resolver slot offset");
static_assert(offsetof(OpaqueListVtable, field_14) == 0x14,
              "list property slot offset");
static_assert(offsetof(OpaqueListVtable, field_28) == 0x28,
              "list fast property slot offset");
static_assert(offsetof(OpaqueBaseVtable, field_1c) == 0x1c,
              "base has-property slot offset");
static_assert(offsetof(OpaqueBaseVtable, field_24) == 0x24,
              "base get-property slot offset");
static_assert(offsetof(OpaqueBaseVtable, field_28) == 0x28,
              "base get-object slot offset");

void set_opaque_property_service(OpaquePropertyService* service);
void set_opaque_fast_list(OpaqueList* list);
void set_opaque_base_insert(OpaqueBaseInsert insert);
void set_opaque_error_port(OpaqueErrorPort port);
void set_opaque_type_conversion(OpaqueTypeConversion conversion);

#if defined(_MSC_VER)
#define PKG20_WAVE6_THISCALL __thiscall
#else
#define PKG20_WAVE6_THISCALL __attribute__((thiscall))
#endif

bool PKG20_WAVE6_THISCALL opaque_list_has_property_006a27d0(
    OpaqueList* list, TargetWord property_id);
OpaqueProperty* PKG20_WAVE6_THISCALL opaque_list_get_property_object_006a2800(
    OpaqueList* list, TargetWord property_id);
bool PKG20_WAVE6_THISCALL opaque_list_get_property_006a28c0(
    OpaqueList* list, TargetWord property_id, OpaqueProperty** result);
void PKG20_WAVE6_THISCALL opaque_list_set_property_006a30c0(
    OpaqueList* list, TargetWord property_id, OpaqueProperty* value);
void PKG20_WAVE6_THISCALL opaque_list_get_property_ids_006a3180(
    OpaqueList* list, OpaqueWordVector* destination);

#undef PKG20_WAVE6_THISCALL

}
