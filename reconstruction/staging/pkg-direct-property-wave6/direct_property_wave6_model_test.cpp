#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "direct_property_wave6.hpp"

namespace openspore::reconstruction::pkg_direct_property_wave6 {
namespace {

OpaqueProperty properties[8]{};
OpaqueProperty fast_property{};
OpaqueProperty parent_property{};
OpaquePropertyServiceVtable service_vtable{};
OpaquePropertyService service{};
OpaqueListVtable list_vtable{};
OpaqueListVtable fast_list_vtable{};
OpaqueBaseVtable base_vtable{};
OpaqueBaseObject parent{};
OpaqueList fast_list{};
TargetWord fast_values[4]{};
TargetWord list_values[4]{};
OpaqueMapEntry map_entries[4]{};
OpaqueProperty slow_property{};
std::size_t slow_set_calls = 0;
TargetWord slow_set_id = 0;
std::size_t base_insert_calls = 0;
TargetWord base_insert_id = 0;
std::size_t error_calls = 0;
std::size_t conversion_calls = 0;

OpaqueProperty* resolve_property(OpaquePropertyService*,
                                 TargetWord property_id) {
  return &properties[property_id];
}

OpaqueProperty* get_fast_property(OpaqueList*, TargetWord) {
  return &fast_property;
}

void set_slow_property(OpaqueList*, TargetWord property_id,
                       OpaqueProperty* value) {
  ++slow_set_calls;
  slow_set_id = property_id;
  slow_property = *value;
}

bool parent_has_property(OpaqueBaseObject*, TargetWord property_id) {
  return property_id == 77u;
}

bool parent_get_property(OpaqueBaseObject*, TargetWord property_id,
                         OpaqueProperty** result) {
  if (property_id != 78u) {
    return false;
  }
  *result = &parent_property;
  return true;
}

OpaqueProperty* parent_get_property_object(OpaqueBaseObject*,
                                           TargetWord property_id) {
  return property_id == 79u ? &parent_property : nullptr;
}

void insert_base_property(OpaqueList*, TargetWord property_id,
                          OpaqueProperty*) {
  ++base_insert_calls;
  base_insert_id = property_id;
}

void error_port(TargetWord) { ++error_calls; }

void conversion_port(TargetWord, TargetWord, const void*, TargetWord,
                     TargetWord) {
  ++conversion_calls;
}

void set_property(OpaqueProperty& property, std::uint16_t type,
                  std::uint16_t flags, std::uint32_t value) {
  property = OpaqueProperty{};
  property.field_10 = flags;
  property.field_12 = type;
  std::memcpy(property.field_00_0f.data(), &value, sizeof(value));
}

void set_float_property(OpaqueProperty& property, std::uint16_t type,
                        std::uint16_t flags, float value) {
  property = OpaqueProperty{};
  property.field_10 = flags;
  property.field_12 = type;
  std::memcpy(property.field_00_0f.data(), &value, sizeof(value));
}

void set_map_entry(OpaqueMapEntry& entry, TargetWord key,
                   std::uint16_t type, std::uint16_t flags,
                   std::uint32_t value) {
  entry.field_00 = key;
  set_property(entry.field_04, type, flags, value);
}

void configure_list(OpaqueList& list, TargetWord fast_count,
                    TargetWord* values) {
  list = OpaqueList{};
  list.field_00 = &list_vtable;
  list.field_38 = fast_count;
  list.field_3c = values;
}

void configure_map(OpaqueList& list, OpaqueMapEntry* begin,
                   OpaqueMapEntry* end) {
  list.field_18.field_00 = begin;
  list.field_18.field_04 = end;
}

void configure_globals() {
  service_vtable = OpaquePropertyServiceVtable{};
  service_vtable.field_50 = resolve_property;
  service.field_00 = &service_vtable;
  set_opaque_property_service(&service);

  list_vtable = OpaqueListVtable{};
  list_vtable.field_14 = set_slow_property;
  list_vtable.field_28 = get_fast_property;
  fast_list_vtable = OpaqueListVtable{};
  fast_list_vtable.field_14 = set_slow_property;

  base_vtable = OpaqueBaseVtable{};
  base_vtable.field_1c = parent_has_property;
  base_vtable.field_24 = parent_get_property;
  base_vtable.field_28 = parent_get_property_object;
  parent.field_00 = &base_vtable;

  fast_list = OpaqueList{};
  fast_list.field_00 = &fast_list_vtable;
  fast_list.field_38 = 2u;
  fast_list.field_3c = fast_values;
  set_opaque_fast_list(&fast_list);
  set_opaque_base_insert(insert_base_property);
  set_opaque_error_port(error_port);
  set_opaque_type_conversion(conversion_port);
}

void test_layout_and_has_property() {
  OpaqueList list{};
  configure_list(list, 3u, list_values);
  list_values[0] = 0u;
  list_values[1] = 1u;
  list_values[2] = 0u;
  set_map_entry(map_entries[0], 10u, 1u, 0u, 1u);
  set_map_entry(map_entries[1], 20u, 1u, 0u, 1u);
  configure_map(list, map_entries, map_entries + 2);

  assert(opaque_list_has_property_006a27d0(&list, 1u));
  assert(!opaque_list_has_property_006a27d0(&list, 0u));
  assert(opaque_list_has_property_006a27d0(&list, 10u));
  assert(!opaque_list_has_property_006a27d0(&list, 15u));
  list.field_30 = &parent;
  assert(opaque_list_has_property_006a27d0(&list, 77u));
}

void test_get_property_object_and_default() {
  OpaqueList list{};
  configure_list(list, 2u, list_values);
  list.field_18.field_00 = map_entries;
  list.field_18.field_04 = map_entries + 1;
  set_map_entry(map_entries[0], 40u, 1u, 0u, 1u);
  list_values[1] = 0u;
  set_property(properties[1], 1u, 0u, 0u);
  list.field_40 = OpaqueProperty{};
  assert(opaque_list_get_property_object_006a2800(&list, 1u) ==
         &list.field_40);
  assert(list.field_40.field_12 == 1u);
  assert(list.field_40.field_00_0f[0] == 0u);

  set_property(properties[1], 9u, 0u, 0x12345678u);
  list_values[1] = 0x12345678u;
  list.field_40 = OpaqueProperty{};
  assert(opaque_list_get_property_object_006a2800(&list, 1u) ==
         &list.field_40);
  assert(list.field_40.field_12 == 9u);
  assert(list.field_40.field_00_0f[0] == 0x78u);
  assert(list.field_40.field_00_0f[1] == 0x56u);
  assert(list.field_40.field_00_0f[2] == 0x34u);
  assert(list.field_40.field_00_0f[3] == 0x12u);

  set_float_property(properties[1], 0x0du, 0u, 2.5f);
  list.field_40 = OpaqueProperty{};
  std::memcpy(&list_values[1], properties[1].field_00_0f.data(),
              sizeof(float));
  assert(opaque_list_get_property_object_006a2800(&list, 1u) ==
         &list.field_40);
  float object_value = 0.0f;
  std::memcpy(&object_value, list.field_40.field_00_0f.data(),
              sizeof(object_value));
  assert(object_value == 2.5f);

  set_property(properties[1], 2u, 0u, 0x5a5a5a5au);
  list.field_40 = OpaqueProperty{};
  assert(opaque_list_get_property_object_006a2800(&list, 1u) ==
         &list.field_40);
  assert(list.field_40.field_12 == 2u);
  assert(list.field_40.field_00_0f[0] == 0x5au);

  set_property(properties[1], 9u, 0x0010u, 0u);
  list.field_40 = OpaqueProperty{};
  assert(opaque_list_get_property_object_006a2800(&list, 1u) ==
         &list.field_40);
  assert(list.field_40.field_10 == 0x0010u);
  assert(list.field_40.field_12 == 9u);

  list.field_18.field_00 = map_entries;
  list.field_18.field_04 = map_entries + 1;
  set_map_entry(map_entries[0], 50u, 1u, 0u, 1u);
  list.field_38 = 0u;
  assert(opaque_list_get_property_object_006a2800(&list, 50u) ==
         &map_entries[0].field_04);
  assert(opaque_list_get_property_object_006a2800(&list, 51u) != nullptr);
}

void test_get_property_paths() {
  OpaqueList list{};
  configure_list(list, 2u, list_values);
  OpaqueProperty* result = nullptr;
  assert(opaque_list_get_property_006a28c0(&list, 1u, &result));
  assert(result == &fast_property);

  set_map_entry(map_entries[0], 60u, 9u, 0u, 0x01020304u);
  configure_map(list, map_entries, map_entries + 1);
  result = nullptr;
  assert(opaque_list_get_property_006a28c0(&list, 60u, &result));
  assert(result == &map_entries[0].field_04);

  list.field_30 = &parent;
  result = nullptr;
  assert(opaque_list_get_property_006a28c0(&list, 78u, &result));
  assert(result == &parent_property);
  result = reinterpret_cast<OpaqueProperty*>(1u);
  assert(!opaque_list_get_property_006a28c0(&list, 79u, &result));
}

void test_set_property_paths() {
  OpaqueList list{};
  configure_list(list, 2u, list_values);
  fast_list.field_38 = 2u;
  fast_values[1] = 0u;

  set_property(properties[1], 1u, 0u, 1u);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  assert(fast_values[1] == 1u);

  set_property(properties[1], 9u, 0u, 0x12345678u);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  assert(fast_values[1] == 0x12345678u);

  set_float_property(properties[1], 0x0du, 0u, 3.5f);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  float float_value = 0.0f;
  std::memcpy(&float_value, &fast_values[1], sizeof(float_value));
  assert(float_value == 3.5f);

  fast_values[1] = 0x55u;
  set_property(properties[1], 2u, 0u, 0u);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  assert(fast_values[1] == 0x55u);
  set_property(properties[1], 9u, 0x0010u, 0x11111111u);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  assert(fast_values[1] == 0x55u);

  slow_set_calls = 0;
  fast_list.field_38 = 1u;
  set_property(properties[1], 1u, 0u, 1u);
  opaque_list_set_property_006a30c0(&list, 1u, &properties[1]);
  assert(slow_set_calls == 1u);
  assert(slow_set_id == 1u);
  assert(slow_property.field_12 == 1u);
  assert(slow_property.field_00_0f[0] == 1u);

  fast_list.field_38 = 2u;
  set_map_entry(map_entries[0], 70u, 1u, 0u, 0u);
  configure_map(list, map_entries, map_entries + 1);
  OpaqueProperty value{};
  set_property(value, 9u, 0u, 0x01020304u);
  opaque_list_set_property_006a30c0(&list, 70u, &value);
  assert(map_entries[0].field_04.field_12 == 9u);
  assert(map_entries[0].field_04.field_00_0f[0] == 0x04u);
  assert(list.field_34 == 1u);

  base_insert_calls = 0;
  opaque_list_set_property_006a30c0(&list, 71u, &value);
  assert(base_insert_calls == 1u);
  assert(base_insert_id == 71u);
  assert(list.field_34 == 2u);
}

void test_get_property_ids() {
  OpaqueList list{};
  configure_list(list, 4u, list_values);
  set_property(properties[0], 1u, 0u, 0u);
  set_property(properties[1], 1u, 0u, 0u);
  set_property(properties[2], 0u, 0u, 0u);
  set_property(properties[3], 9u, 0u, 0u);
  set_map_entry(map_entries[0], 20u, 1u, 0u, 0u);
  set_map_entry(map_entries[1], 30u, 1u, 0u, 0u);
  configure_map(list, map_entries, map_entries + 2);

  auto* storage = new TargetWord[1]{99u};
  OpaqueWordVector destination{storage, storage + 1, storage + 1};
  opaque_list_get_property_ids_006a3180(&list, &destination);
  assert(destination.field_04 - destination.field_00 == 4);
  assert(destination.field_00[0] == 1u);
  assert(destination.field_00[1] == 3u);
  assert(destination.field_00[2] == 20u);
  assert(destination.field_00[3] == 30u);
  delete[] destination.field_00;

  list.field_38 = 1u;
  list.field_18.field_00 = map_entries;
  list.field_18.field_04 = map_entries;
  storage = new TargetWord[1]{7u};
  destination = OpaqueWordVector{storage, storage + 1, storage + 1};
  opaque_list_get_property_ids_006a3180(&list, &destination);
  assert(destination.field_04 == destination.field_00);
  delete[] destination.field_00;
}

void run() {
  configure_globals();
  test_layout_and_has_property();
  test_get_property_object_and_default();
  test_get_property_paths();
  test_set_property_paths();
  test_get_property_ids();
  set_opaque_property_service(nullptr);
  set_opaque_fast_list(nullptr);
  set_opaque_base_insert(nullptr);
  set_opaque_error_port(nullptr);
  set_opaque_type_conversion(nullptr);
}

}

}

int main() { openspore::reconstruction::pkg_direct_property_wave6::run(); }
