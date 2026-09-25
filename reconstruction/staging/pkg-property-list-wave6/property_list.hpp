#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-20 property-list wave6 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_property_list_wave6 {

using Wave6Word = std::uint32_t;

struct Wave6OpaqueStream;
struct Wave6Property;
struct Wave6PropertyList;

#if defined(_MSC_VER)
using Wave6ReleaseThis = void(__thiscall*)(Wave6PropertyList*);
using Wave6ClearThis = void(__thiscall*)(Wave6PropertyList*);
using Wave6AddPropertyList = void(__thiscall*)(Wave6PropertyList*,
                                               Wave6PropertyList*);
using Wave6ParentHas = bool(__thiscall*)(Wave6PropertyList*, Wave6Word);
using Wave6ParentGetAlt = bool(__thiscall*)(Wave6PropertyList*, Wave6Word,
                                            Wave6Property**);
using Wave6ParentGet = bool(__thiscall*)(Wave6PropertyList*, Wave6Word,
                                         Wave6Property**);
using Wave6ParentGetObject = Wave6Property*(__thiscall*)(Wave6PropertyList*,
                                                         Wave6Word);
#else
using Wave6ReleaseThis = void(__attribute__((thiscall)) *)(Wave6PropertyList*);
using Wave6ClearThis = void(__attribute__((thiscall)) *)(Wave6PropertyList*);
using Wave6AddPropertyList =
    void(__attribute__((thiscall)) *)(Wave6PropertyList*, Wave6PropertyList*);
using Wave6ParentHas = bool(__attribute__((thiscall)) *)(Wave6PropertyList*,
                                                         Wave6Word);
using Wave6ParentGetAlt = bool(__attribute__((thiscall)) *)(Wave6PropertyList*,
                                                            Wave6Word,
                                                            Wave6Property**);
using Wave6ParentGet = bool(__attribute__((thiscall)) *)(Wave6PropertyList*,
                                                         Wave6Word,
                                                         Wave6Property**);
using Wave6ParentGetObject =
    Wave6Property*(__attribute__((thiscall)) *)(Wave6PropertyList*, Wave6Word);
#endif

struct Wave6PropertyListVtable {
  Wave6Word opaque_00;
  Wave6ReleaseThis release_04;
  Wave6Word opaque_08;
  Wave6Word opaque_0c;
  Wave6Word opaque_10;
  Wave6Word opaque_14;
  Wave6Word opaque_18;
  Wave6ParentHas parent_has_1c;
  Wave6ParentGetAlt parent_get_alt_20;
  Wave6ParentGet parent_get_24;
  Wave6ParentGetObject parent_get_object_28;
  Wave6Word opaque_2c;
  Wave6AddPropertyList add_all_30;
  Wave6Word opaque_34;
  Wave6AddPropertyList add_all_38;
  Wave6Word opaque_3c;
  Wave6Word opaque_40;
  Wave6Word opaque_44;
  Wave6ClearThis clear_48;
};

struct Wave6Property {
  std::array<std::uint8_t, 0x10> opaque_00_0f;
  std::uint16_t flags_10;
  std::uint16_t type_12;
};

struct Wave6PropertyEntry {
  Wave6Word id;
  Wave6Property property;
};

struct Wave6PropertyList {
  Wave6PropertyListVtable* vtable;
  std::array<std::uint8_t, 0x14> opaque_04_17;
  Wave6PropertyEntry* entries_begin_18;
  Wave6PropertyEntry* entries_end_1c;
  std::array<std::uint8_t, 0x0c> opaque_20_2b;
  std::uint8_t lookup_mode_2c;
  std::array<std::uint8_t, 0x03> opaque_2d_2f;
  Wave6PropertyList* parent_30;
};

using Wave6WriteWords = bool (*)(Wave6OpaqueStream*, const Wave6Word*,
                                 Wave6Word, Wave6Word);
using Wave6WriteProperty = bool (*)(Wave6OpaqueStream*, Wave6Property*,
                                    Wave6Word);

struct Wave6NativePorts {
  Wave6WriteWords write_words_0093aa70;
  Wave6WriteProperty write_property_00693390;
};

static_assert(sizeof(Wave6Word) == 4, "wave6 target words are 32-bit");
static_assert(sizeof(void*) == 4, "wave6 target pointers are 32-bit");
static_assert(sizeof(Wave6ReleaseThis) == 4, "wave6 thiscall slots are 32-bit");
static_assert(offsetof(Wave6PropertyListVtable, release_04) == 0x04,
              "wave6 release slot offset");
static_assert(offsetof(Wave6PropertyListVtable, parent_has_1c) == 0x1c,
              "wave6 parent HasProperty slot offset");
static_assert(offsetof(Wave6PropertyListVtable, parent_get_alt_20) == 0x20,
              "wave6 parent GetPropertyAlt slot offset");
static_assert(offsetof(Wave6PropertyListVtable, parent_get_24) == 0x24,
              "wave6 parent GetProperty slot offset");
static_assert(offsetof(Wave6PropertyListVtable, parent_get_object_28) == 0x28,
              "wave6 parent GetPropertyObject slot offset");
static_assert(offsetof(Wave6PropertyListVtable, add_all_30) == 0x30,
              "wave6 add-all slot offset");
static_assert(offsetof(Wave6PropertyListVtable, add_all_38) == 0x38,
              "wave6 add-parent slot offset");
static_assert(offsetof(Wave6PropertyListVtable, clear_48) == 0x48,
              "wave6 clear slot offset");
static_assert(offsetof(Wave6Property, flags_10) == 0x10,
              "wave6 property flags offset");
static_assert(offsetof(Wave6Property, type_12) == 0x12,
              "wave6 property type offset");
static_assert(sizeof(Wave6Property) == 0x14, "wave6 property carrier extent");
static_assert(sizeof(Wave6PropertyEntry) == 0x18,
              "wave6 property entry stride");
static_assert(offsetof(Wave6PropertyEntry, property) == 0x04,
              "wave6 entry property offset");
static_assert(offsetof(Wave6PropertyList, entries_begin_18) == 0x18,
              "wave6 property map begin offset");
static_assert(offsetof(Wave6PropertyList, entries_end_1c) == 0x1c,
              "wave6 property map end offset");
static_assert(offsetof(Wave6PropertyList, lookup_mode_2c) == 0x2c,
              "wave6 lookup mode offset");
static_assert(offsetof(Wave6PropertyList, parent_30) == 0x30,
              "wave6 parent offset");

Wave6NativePorts& wave6_property_list_native_ports();

#if defined(_MSC_VER)
#define WAVE6_PROPERTY_THISCALL __thiscall
#else
#define WAVE6_PROPERTY_THISCALL __attribute__((thiscall))
#endif

void WAVE6_PROPERTY_THISCALL
app_property_list_copy_all_properties_from_006a14d0(Wave6PropertyList* list,
                                                    Wave6PropertyList* other);
void WAVE6_PROPERTY_THISCALL app_property_list_add_all_properties_from_006a1510(
    Wave6PropertyList* list, Wave6PropertyList* other);
bool WAVE6_PROPERTY_THISCALL app_property_list_write_006a1540(
    Wave6PropertyList* list, Wave6OpaqueStream* stream);
bool WAVE6_PROPERTY_THISCALL app_property_list_get_property_alt_006a1de0(
    Wave6PropertyList* list, Wave6Word property_id, Wave6Property** result);
bool WAVE6_PROPERTY_THISCALL app_property_list_has_property_006a2470(
    Wave6PropertyList* list, Wave6Word property_id);
Wave6Property* WAVE6_PROPERTY_THISCALL
app_property_list_get_property_object_006a24d0(Wave6PropertyList* list,
                                               Wave6Word property_id);
bool WAVE6_PROPERTY_THISCALL app_property_list_get_property_006a2530(
    Wave6PropertyList* list, Wave6Word property_id, Wave6Property** result);

#undef WAVE6_PROPERTY_THISCALL

}
