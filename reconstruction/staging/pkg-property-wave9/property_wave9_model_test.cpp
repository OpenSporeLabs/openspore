#include <cstdlib>
#include <cstring>
#include <iterator>

#include "property_wave9.hpp"

namespace openspore::reconstruction::pkg_property_wave9 {

struct OpaqueStream {
  TargetWord marker;
};

namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_WAVE9_TEST_THISCALL __thiscall
#else
#define PKG_PROPERTY_WAVE9_TEST_THISCALL __attribute__((thiscall))
#endif

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::array<int, 64> events{};
std::size_t event_count = 0;
OpaqueProperty fast_property{};
OpaqueProperty parent_property{};
OpaquePropertyList replacement_parent{};
OpaquePropertyList* observed_list = nullptr;
OpaquePropertyEntry* observed_end = nullptr;
MapCopy default_map_copy_entry = nullptr;
TargetWord set_ids[8]{};
OpaqueProperty* set_values[8]{};
std::size_t set_calls = 0;
std::size_t conversion_calls = 0;
TargetWord conversion_type = 0;
std::uint16_t conversion_flags = 0;
OpaqueProperty* conversion_destination = nullptr;
TargetWord conversion_entry_id = 0;
std::size_t error_calls = 0;
OpaqueProperty* error_property = nullptr;
OpaqueProperty* error_properties[8]{};
OpaquePropertyEntry* error_map_ends[8]{};
std::size_t error_property_count = 0;
OpaquePropertyList* released_parent = nullptr;
TargetWord factory_key_a = 0;
TargetWord factory_key_b = 0;

struct ReadScript {
  std::size_t word_call = 0;
  std::size_t property_call = 0;
  TargetWord count = 0;
  bool count_success = true;
  bool key_success = true;
  std::array<bool, 4> id_success{{true, true, true, true}};
  std::array<TargetWord, 4> ids{{0, 0, 0, 0}};
  std::array<bool, 4> property_success{{true, true, true, true}};
};

ReadScript read_script;

void record(int event) {
  check(event_count < events.size());
  events[event_count] = event;
  ++event_count;
}

void PKG_PROPERTY_WAVE9_TEST_THISCALL set_property_hook(OpaquePropertyList*,
                                                        TargetWord property_id,
                                                        OpaqueProperty* value) {
  check(set_calls < 8u);
  set_ids[set_calls] = property_id;
  set_values[set_calls] = value;
  ++set_calls;
  record(20 + static_cast<int>(property_id));
}

OpaqueProperty* PKG_PROPERTY_WAVE9_TEST_THISCALL
get_fast_hook(OpaquePropertyList*, TargetWord property_id) {
  record(30 + static_cast<int>(property_id));
  return &fast_property;
}

bool PKG_PROPERTY_WAVE9_TEST_THISCALL parent_get_alt_hook(
    OpaquePropertyList*, TargetWord property_id, OpaqueProperty** result) {
  record(40 + static_cast<int>(property_id));
  if (property_id != 700u) {
    return false;
  }
  *result = &parent_property;
  return true;
}

void PKG_PROPERTY_WAVE9_TEST_THISCALL
set_parent_hook(OpaquePropertyList*, OpaquePropertyList* parent) {
  record(parent == nullptr ? 3 : 4);
}

OpaquePropertyMap* PKG_PROPERTY_WAVE9_TEST_THISCALL
map_copy_hook(OpaquePropertyMap* destination, const OpaquePropertyMap* source) {
  record(1);
  const auto count = static_cast<TargetWord>(
      (reinterpret_cast<std::uintptr_t>(source->end) -
       reinterpret_cast<std::uintptr_t>(source->begin)) /
      sizeof(OpaquePropertyEntry));
  destination->end = destination->begin + count;
  for (TargetWord index = 0; index < count; ++index) {
    destination->begin[index] = source->begin[index];
  }
  return destination;
}

void PKG_PROPERTY_WAVE9_TEST_THISCALL
conversion_hook(OpaqueProperty* destination, TargetWord type,
                std::uint16_t flags, const void*, TargetWord, TargetWord) {
  conversion_destination = destination;
  conversion_entry_id =
      reinterpret_cast<OpaquePropertyEntry*>(
          reinterpret_cast<std::uint8_t*>(destination) - sizeof(TargetWord))
          ->id;
  ++conversion_calls;
  conversion_type = type;
  conversion_flags = flags;
  record(100 + static_cast<int>(type));
}

void error_hook(TargetWord, OpaqueProperty* property, TargetWord, TargetWord,
                TargetWord, TargetWord) {
  ++error_calls;
  error_property = property;
  if (error_property_count < 8u) {
    error_properties[error_property_count] = property;
    error_map_ends[error_property_count] =
        observed_list == nullptr ? nullptr : observed_list->properties.end;
    ++error_property_count;
  }
  record(200);
  if (observed_end != nullptr) {
    check(observed_list != nullptr);
    check(observed_list->properties.end == observed_end);
  }
}

void PKG_PROPERTY_WAVE9_TEST_THISCALL release_hook(OpaquePropertyList* parent) {
  released_parent = parent;
  check(observed_list != nullptr);
  check(observed_list->parent == nullptr);
  record(5);
}

OpaquePropertyList* PKG_PROPERTY_WAVE9_TEST_THISCALL
create_hook(OpaquePropertyListFactory*, TargetWord key_a, TargetWord key_b,
            OpaquePropertyList** result) {
  factory_key_a = key_a;
  factory_key_b = key_b;
  *result = &replacement_parent;
  record(6);
  return *result;
}

bool read_words_hook(OpaqueStream*, TargetWord* destination, TargetWord count,
                     TargetWord mode) {
  record(10 + static_cast<int>(count * 10u + mode));
  if (read_script.word_call == 0u) {
    *destination = read_script.count;
    ++read_script.word_call;
    return read_script.count_success;
  }
  if (read_script.word_call == 1u && (read_script.count & 0x80000000u) != 0) {
    for (TargetWord index = 0; index < count; ++index) {
      destination[index] = 11u + index * 11u;
    }
    ++read_script.word_call;
    return read_script.key_success;
  }
  const auto index = (read_script.count & 0x80000000u) != 0
                         ? read_script.word_call - 2u
                         : read_script.word_call - 1u;
  *destination = index < read_script.ids.size() ? read_script.ids[index] : 0u;
  ++read_script.word_call;
  return index < read_script.id_success.size() ? read_script.id_success[index]
                                               : false;
}

bool read_property_hook(OpaqueStream*, OpaqueProperty* property, TargetWord) {
  const auto index = read_script.property_call++;
  property->type = static_cast<std::uint16_t>(100u + index);
  property->flags = 0;
  property->value[0] = static_cast<std::uint8_t>(40u + index);
  record(60 + static_cast<int>(index));
  return index < read_script.property_success.size()
             ? read_script.property_success[index]
             : false;
}

OpaquePropertyListFactoryVtable factory_vtable_value{};
OpaquePropertyListFactory property_list_factory{&factory_vtable_value};

OpaquePropertyListFactory* get_factory_hook() {
  record(7);
  return &property_list_factory;
}

OpaquePropertyListFactoryVtable* factory_vtable() {
  return &factory_vtable_value;
}

OpaquePropertyList* create_property_list() {
  static OpaquePropertyList list{};
  return &list;
}

void reset_observations() {
  events.fill(0);
  event_count = 0;
  observed_list = nullptr;
  observed_end = nullptr;
  set_calls = 0;
  conversion_calls = 0;
  conversion_type = 0;
  conversion_flags = 0;
  conversion_destination = nullptr;
  conversion_entry_id = 0;
  error_calls = 0;
  error_property = nullptr;
  std::fill(std::begin(error_properties), std::end(error_properties), nullptr);
  std::fill(std::begin(error_map_ends), std::end(error_map_ends), nullptr);
  error_property_count = 0;
  released_parent = nullptr;
  factory_key_a = 0;
  factory_key_b = 0;
  read_script = ReadScript{};
}

void configure_runtime() {
  auto& runtime = property_list_runtime();
  runtime.conversion = conversion_hook;
  runtime.error = error_hook;
  runtime.map_copy = map_copy_hook;
  runtime.set_parent = set_parent_hook;
  runtime.read_words = read_words_hook;
  runtime.read_property = read_property_hook;
  runtime.get_factory = get_factory_hook;
  factory_vtable()->create_from_key_2c = create_hook;
}

void test_layouts() {
  check(sizeof(OpaqueProperty) == 0x14u);
  check(sizeof(OpaquePropertyEntry) == 0x18u);
  check(sizeof(OpaquePropertyMap) == 0x18u);
  check(sizeof(OpaquePropertyList) == 0x54u);
  check(offsetof(OpaquePropertyList, properties) == 0x18u);
  check(offsetof(OpaquePropertyList, parent) == 0x30u);
  check(offsetof(OpaquePropertyList, operations_done) == 0x34u);
  check(offsetof(OpaquePropertyList, fast_count) == 0x38u);
  check(offsetof(OpaquePropertyList, fast_values) == 0x3cu);
}

void test_direct_add_and_get_alt() {
  reset_observations();
  OpaquePropertyListVtable list_vtable{};
  OpaquePropertyListVtable parent_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList other{};
  OpaquePropertyEntry entries[2]{};
  list.vtable = &list_vtable;
  list_vtable.set_property_14 = set_property_hook;
  list_vtable.get_property_object_28 = get_fast_hook;
  entries[0].id = 11u;
  entries[1].id = 12u;
  other.properties.begin = entries;
  other.properties.end = entries + 2;

  direct_property_list_add_properties_from_006a1600(&list, &other);
  check(set_calls == 2u);
  check(set_ids[0] == 11u);
  check(set_ids[1] == 12u);
  check(set_values[0] == &entries[0].property);
  check(list.operations_done == 1u);

  direct_property_list_add_properties_from_006a1600(&list, &list);
  check(set_calls == 2u);
  check(list.operations_done == 1u);

  list.fast_count = 2u;
  OpaqueProperty* result = nullptr;
  check(direct_property_list_get_property_alt_006a1e50(&list, 1u, &result));
  check(result == &fast_property);

  list.fast_count = 0u;
  OpaquePropertyEntry local[2]{};
  local[0].id = 20u;
  local[1].id = 30u;
  list.properties.begin = local;
  list.properties.end = local + 2;
  check(direct_property_list_get_property_alt_006a1e50(&list, 20u, &result));
  check(result == &local[0].property);

  OpaquePropertyList parent{};
  parent.vtable = &parent_vtable;
  parent_vtable.get_property_alt_20 = parent_get_alt_hook;
  list.parent = &parent;
  result = reinterpret_cast<OpaqueProperty*>(1u);
  check(direct_property_list_get_property_alt_006a1e50(&list, 700u, &result));
  check(result == &parent_property);
  result = reinterpret_cast<OpaqueProperty*>(1u);
  check(!direct_property_list_get_property_alt_006a1e50(&list, 701u, &result));
  check(result == reinterpret_cast<OpaqueProperty*>(1u));
}

void test_copy_and_clear_order() {
  reset_observations();
  OpaquePropertyListVtable list_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList other{};
  OpaquePropertyEntry source[2]{};
  OpaquePropertyEntry destination[2]{};
  list.vtable = &list_vtable;
  list_vtable.set_property_14 = set_property_hook;
  list.parent = create_property_list();
  other.properties.begin = source;
  other.properties.end = source + 2;
  other.properties.lookup_mode = 0x5au;
  list.properties.begin = destination;
  list.properties.end = destination + 1;
  list.properties.capacity = destination + 2;

  property_list_copy_from_006a2a40(&list, &other);
  check(event_count == 2u);
  check(events[0] == 1);
  check(events[1] == 4);
  check(list.properties.end == destination + 2);
  check(list.properties.begin[0].id == source[0].id);
  check(list.properties.lookup_mode == 0x5au);
  check(list.operations_done == 0u);

  property_list_copy_from_006a2a40(&list, &list);
  check(event_count == 2u);

  OpaquePropertyList clear_list{};
  OpaquePropertyEntry clear_entries[2]{};
  clear_entries[0].property.flags = 0x0004u;
  clear_entries[1].property.flags = 0u;
  clear_list.properties.begin = clear_entries;
  clear_list.properties.end = clear_entries + 2;
  clear_list.properties.capacity = clear_entries + 2;
  observed_list = &clear_list;
  observed_end = clear_list.properties.end;
  event_count = 0;
  error_calls = 0;
  property_list_clear_006a2a80(&clear_list);
  check(error_calls == 1u);
  check(events[0] == 200);
  check(clear_list.properties.end == clear_entries);
  check(clear_list.operations_done == 1u);

  TargetWord fast_values[2]{0x11111111u, 0x22222222u};
  clear_entries[0].property.flags = 0x0004u;
  clear_entries[1].property.flags = 0u;
  clear_list.properties.end = clear_entries + 2;
  clear_list.fast_values = fast_values;
  clear_list.fast_count = 2u;
  observed_end = clear_entries + 2;
  event_count = 0;
  error_calls = 0;
  direct_property_list_clear_006a2b20(&clear_list);
  check(fast_values[0] == 0x11110000u);
  check(fast_values[1] == 0x22222222u);
  check(clear_list.properties.end == clear_entries);
  check(error_calls == 1u);
  check(clear_list.operations_done == 1u);

  fast_values[0] = 0x11111111u;
  fast_values[1] = 0x22222222u;
  clear_list.properties.end = clear_entries + 2;
  clear_list.fast_count = 6u;
  observed_end = clear_entries + 2;
  event_count = 0;
  error_calls = 0;
  direct_property_list_clear_006a2b20(&clear_list);
  check(fast_values[0] == 0u);
  check(fast_values[1] == 0x22220000u);
  check(clear_list.properties.end == clear_entries);
  check(error_calls == 1u);
  check(clear_list.operations_done == 1u);
}

void test_default_map_copy_path() {
  reset_observations();
  check(default_map_copy_entry != nullptr);
  OpaquePropertyMap source{};
  OpaquePropertyMap destination{};
  OpaquePropertyEntry source_entries[2]{};
  OpaquePropertyEntry destination_entries[2]{};
  source_entries[0].id = 0x1234u;
  source_entries[0].property.type = 5u;
  source_entries[0].property.value[0] = 0xa1u;
  source_entries[1].id = 0x5678u;
  source_entries[1].property.type = 6u;
  source_entries[1].property.flags = 0x0008u;
  source_entries[1].property.value[0] = 0xb2u;
  source.begin = source_entries;
  source.end = source_entries + 2;
  destination_entries[0].id = 0xaaaau;
  destination_entries[0].property.type = 5u;
  destination_entries[0].property.flags = 0x0002u;
  destination_entries[0].property.value[0] = 0x01u;
  destination_entries[1].id = 0xbbbbu;
  destination_entries[1].property.value[0] = 0x02u;
  destination.begin = destination_entries;
  destination.end = destination_entries + 2;
  destination.capacity = destination_entries + 2;

  check(default_map_copy_entry(&destination, &destination) == &destination);
  check(destination.end == destination_entries + 2);
  check(destination_entries[0].id == 0xaaaau);
  check(destination_entries[1].id == 0xbbbbu);
  check(conversion_calls == 0u);

  check(default_map_copy_entry(&destination, &source) == &destination);
  check(destination.end == destination_entries + 2);
  check(destination_entries[0].id == 0x1234u);
  check(destination_entries[1].id == 0x5678u);
  check(destination_entries[0].property.value[0] == 0xa1u);
  check(destination_entries[0].property.type == 5u);
  check(destination_entries[0].property.flags == 0x0002u);
  check(destination_entries[1].property.value[0] == 0x02u);
  check(conversion_calls == 1u);
  check(conversion_type == 6u);
  check(conversion_flags == 0x0008u);
  check(conversion_destination == &destination_entries[1].property);
  check(conversion_entry_id == 0x5678u);

  OpaquePropertyMap grown{};
  check(default_map_copy_entry(&grown, &source) == &grown);
  check(grown.begin != nullptr);
  check(grown.end == grown.begin + 2);
  check(grown.capacity == grown.begin + 2);
  check(grown.begin[0].id == 0x1234u);
  check(grown.begin[1].id == 0x5678u);
  check(grown.begin[0].property.value[0] == 0xa1u);
  check(conversion_calls == 2u);
  check(conversion_destination == &grown.begin[1].property);
  check(conversion_entry_id == 0x5678u);
  delete[] grown.begin;
}

void test_direct_copy_order() {
  reset_observations();
  OpaquePropertyListVtable list_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList other{};
  OpaquePropertyEntry existing{};
  OpaquePropertyEntry source[2]{};
  TargetWord fast_values[1]{0x12345678u};
  list.vtable = &list_vtable;
  list_vtable.set_property_14 = set_property_hook;
  list.properties.begin = &existing;
  list.properties.end = &existing + 1;
  list.properties.capacity = &existing + 1;
  list.parent = create_property_list();
  list.fast_values = fast_values;
  list.fast_count = 1u;
  existing.property.flags = 0x0004u;
  source[0].id = 41u;
  source[1].id = 42u;
  other.properties.begin = source;
  other.properties.end = source + 2;
  observed_list = &list;
  observed_end = &existing + 1;

  direct_property_list_copy_from_006a2ad0(&list, &other);
  check(event_count == 4u);
  check(events[0] == 200);
  check(events[1] == 61);
  check(events[2] == 62);
  check(events[3] == 4);
  check(set_calls == 2u);
  check(fast_values[0] == 0x12345678u);
  check(list.properties.end == &existing);
  check(list.operations_done == 0u);

  event_count = 0;
  set_calls = 0;
  direct_property_list_copy_from_006a2ad0(&list, &list);
  check(event_count == 0u);
  check(set_calls == 0u);
}

void test_set_and_remove() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyEntry entries[4]{};
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 4;
  entries[0].id = 10u;
  entries[0].property.type = 9u;
  entries[0].property.flags = 0x0002u;
  entries[0].property.value[0] = 1u;
  list.properties.end = entries + 1;

  OpaqueProperty value{};
  value.type = 9u;
  value.flags = 0u;
  value.value[0] = 0x7bu;
  property_list_set_property_006a2e20(&list, 10u, &value);
  check(entries[0].property.type == 9u);
  check(entries[0].property.flags == 0x0002u);
  check(entries[0].property.value[0] == 0x7bu);
  check(list.operations_done == 1u);

  value.value[0] = 0x44u;
  property_list_set_property_006a2e20(&list, 30u, &value);
  check(list.properties.end == entries + 2);
  check(entries[1].id == 30u);
  check(entries[1].property.value[0] == 0x44u);
  check(list.operations_done == 2u);

  value.type = 12u;
  value.flags = 0x0008u;
  property_list_set_property_006a2e20(&list, 40u, &value);
  check(conversion_calls == 1u);
  check(conversion_type == 12u);
  check(conversion_flags == 0x0008u);
  check(entries[2].id == 40u);
  check(list.operations_done == 3u);

  check(property_list_remove_property_006a2ef0(&list, 999u) == 0);
  check(list.operations_done == 4u);
  check(property_list_remove_property_006a2ef0(&list, 10u) == 1);
  check(list.properties.end == entries + 2);
  check(entries[0].id == 30u);
  check(entries[0].property.value[0] == 0x44u);
  check(entries[1].id == 40u);
  check(list.operations_done == 5u);
}

void test_new_entry_flag_four_ownership() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyEntry entries[3]{};
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 3;
  entries[0].id = 10u;
  entries[0].property.flags = 0x0004u;
  entries[0].property.type = 3u;
  entries[0].property.value[0] = 0x21u;
  entries[1].id = 30u;
  entries[1].property.flags = 0x0004u;
  entries[1].property.type = 5u;
  entries[1].property.value[0] = 0x43u;
  list.properties.end = entries + 2;
  observed_list = &list;
  observed_end = nullptr;

  OpaqueProperty value{};
  value.flags = 0x0004u;
  value.type = 7u;
  value.value[0] = 0x65u;
  property_list_set_property_006a2e20(&list, 20u, &value);

  check(list.properties.end == entries + 3);
  check(error_calls == 3u);
  check(error_property_count == 3u);
  check(error_properties[0] == &entries[2].property);
  check(error_properties[1] == &entries[1].property);
  check(error_properties[2] != nullptr);
  check(error_properties[2] != &entries[1].property);
  check(error_map_ends[0] == entries + 2);
  check(error_map_ends[1] == entries + 2);
  check(error_map_ends[2] == entries + 3);
  check(entries[0].id == 10u);
  check(entries[1].id == 20u);
  check(entries[1].property.flags == 0x0004u);
  check(entries[1].property.type == 7u);
  check(entries[1].property.value[0] == 0x65u);
  check(entries[2].id == 30u);
  check(entries[2].property.type == 5u);
  check(list.operations_done == 1u);
}

void test_conversion_destination_behavior() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyEntry entries[1]{};
  entries[0].id = 70u;
  entries[0].property.flags = 0x0002u;
  entries[0].property.type = 1u;
  entries[0].property.value[0] = 0x5au;
  list.properties.begin = entries;
  list.properties.end = entries + 1;
  list.properties.capacity = entries + 1;

  OpaqueProperty source{};
  source.type = 1u;
  source.value[0] = 0x6bu;
  property_list_set_property_006a2e20(&list, 70u, &source);
  check(entries[0].property.value[0] == 0x6bu);

  const OpaqueProperty after_copy = entries[0].property;
  source.flags = 0x0008u;
  source.type = 2u;
  source.value[0] = 0x7bu;
  property_list_set_property_006a2e20(&list, 70u, &source);
  check(conversion_calls == 1u);
  check(conversion_destination == &entries[0].property);
  check(std::memcmp(&entries[0].property, &after_copy,
                    sizeof(OpaqueProperty)) == 0);

  const OpaqueProperty after_flag_mismatch = entries[0].property;
  source.flags = 0u;
  property_list_set_property_006a2e20(&list, 70u, &source);
  check(conversion_calls == 2u);
  check(conversion_destination == &entries[0].property);
  check(std::memcmp(&entries[0].property, &after_flag_mismatch,
                    sizeof(OpaqueProperty)) == 0);
}

void test_add_properties_from() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyList other{};
  OpaquePropertyEntry destination[3]{};
  OpaquePropertyEntry source[2]{};
  list.properties.begin = destination;
  list.properties.end = destination;
  list.properties.capacity = destination + 3;
  other.properties.begin = source;
  other.properties.end = source + 2;
  source[0].id = 50u;
  source[0].property.type = 1u;
  source[0].property.value[0] = 1u;
  source[1].id = 60u;
  source[1].property.type = 2u;
  source[1].property.value[0] = 2u;

  property_list_add_properties_from_006a2f10(&list, &other);
  check(list.properties.end == destination + 2);
  check(destination[0].id == 50u);
  check(destination[0].property.value[0] == 1u);
  check(destination[1].id == 60u);
  check(destination[1].property.value[0] == 2u);
  check(list.operations_done == 1u);

  property_list_add_properties_from_006a2f10(&list, &list);
  check(list.operations_done == 1u);
}

void test_read_success_and_failures() {
  reset_observations();
  OpaquePropertyListVtable parent_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList old_parent{};
  OpaquePropertyEntry entries[2]{};
  OpaquePropertyListFactoryVtable factory_vtable{};
  OpaqueStream stream{1u};
  old_parent.vtable = &parent_vtable;
  parent_vtable.release_04 = release_hook;
  list.parent = &old_parent;
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 2;
  factory_vtable.create_from_key_2c = create_hook;
  read_script.count = 0x80000002u;
  read_script.ids[0] = 100u;
  read_script.ids[1] = 200u;
  observed_list = &list;
  observed_end = entries;

  check(property_list_read_006a2f60(&list, &stream));
  check(released_parent == &old_parent);
  check(list.parent == &replacement_parent);
  check(factory_key_a == 11u);
  check(factory_key_b == 33u);
  check(list.properties.end == entries + 2);
  check(entries[0].id == 100u);
  check(entries[0].property.type == 100u);
  check(entries[1].id == 200u);
  check(entries[1].property.type == 101u);
  check(read_script.word_call == 4u);
  check(read_script.property_call == 2u);

  reset_observations();
  OpaquePropertyList failure_list{};
  OpaquePropertyEntry failure_entries[2]{};
  failure_list.properties.begin = failure_entries;
  failure_list.properties.end = failure_entries;
  failure_list.properties.capacity = failure_entries + 2;
  read_script.count = 2u;
  read_script.ids[0] = 300u;
  read_script.property_success[0] = false;
  check(!property_list_read_006a2f60(&failure_list, &stream));
  check(failure_list.properties.end == failure_entries + 2);
  check(failure_entries[0].id == 300u);
  check(failure_entries[1].id == 0u);
  check(read_script.word_call == 2u);
  check(read_script.property_call == 1u);

  reset_observations();
  failure_list.properties.end = failure_entries;
  read_script.count = 2u;
  read_script.count_success = false;
  check(!property_list_read_006a2f60(&failure_list, &stream));
  check(failure_list.properties.end == failure_entries + 2);
  check(read_script.word_call == 1u);
  check(read_script.property_call == 0u);
}

void test_read_failed_key_read() {
  reset_observations();
  OpaquePropertyListVtable parent_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList old_parent{};
  OpaquePropertyEntry entries[3]{};
  OpaquePropertyListFactoryVtable factory_vtable{};
  OpaqueStream stream{1u};
  old_parent.vtable = &parent_vtable;
  parent_vtable.release_04 = release_hook;
  list.parent = &old_parent;
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 3;
  factory_vtable.create_from_key_2c = create_hook;
  read_script.count = 0x80000003u;
  read_script.key_success = false;
  observed_list = &list;
  observed_end = entries;

  check(!property_list_read_006a2f60(&list, &stream));
  check(released_parent == &old_parent);
  check(list.parent == &replacement_parent);
  check(factory_key_a == 11u);
  check(factory_key_b == 33u);
  check(list.properties.end == entries + 3);
  check(entries[0].id == 0u);
  check(entries[1].id == 0u);
  check(entries[2].id == 0u);
  check(read_script.word_call == 2u);
  check(read_script.property_call == 0u);
  check(event_count == 5u);
  check(events[0] == 20);
  check(events[1] == 40);
  check(events[2] == 7);
  check(events[3] == 5);
  check(events[4] == 6);
}

void test_read_short_circuits_entry_loop() {
  reset_observations();
  OpaquePropertyListVtable list_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList parent{};
  OpaquePropertyEntry entries[2]{};
  OpaqueStream stream{1u};
  list.vtable = &list_vtable;
  list_vtable.release_04 = release_hook;
  list.parent = &parent;
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 2;
  read_script.count = 2u;
  read_script.ids[0] = 501u;
  read_script.ids[1] = 502u;
  observed_list = &list;
  observed_end = entries;

  check(property_list_read_006a2f60(&list, &stream));
  check(list.parent == &parent);
  check(released_parent == nullptr);
  check(factory_key_a == 0u);
  check(factory_key_b == 0u);
  check(list.properties.end == entries + 2);
  check(entries[0].id == 501u);
  check(entries[1].id == 502u);
  check(read_script.word_call == 3u);
  check(read_script.property_call == 2u);
  check(event_count == 5u);
  check(events[0] == 20);
  check(events[1] == 20);
  check(events[2] == 60);
  check(events[3] == 20);
  check(events[4] == 61);
}

void test_read_parent_key_indices() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyEntry entries[1]{};
  OpaqueStream stream{1u};
  list.properties.begin = entries;
  list.properties.end = entries;
  list.properties.capacity = entries + 1;
  read_script.count = 0x80000000u;
  read_script.key_success = false;
  observed_list = &list;
  observed_end = entries;

  check(!property_list_read_006a2f60(&list, &stream));
  check(released_parent == nullptr);
  check(list.parent == &replacement_parent);
  check(factory_key_a == 11u);
  check(factory_key_b == 33u);
  check(list.properties.end == entries);
  check(entries[0].id == 0u);
  check(read_script.word_call == 2u);
  check(read_script.property_call == 0u);
  check(event_count == 4u);
  check(events[0] == 20);
  check(events[1] == 40);
  check(events[2] == 7);
  check(events[3] == 6);
}

void test_get_property_ids() {
  reset_observations();
  OpaquePropertyList list{};
  OpaquePropertyEntry entries[3]{};
  entries[0].id = 801u;
  entries[1].id = 802u;
  entries[2].id = 803u;
  list.properties.begin = entries;
  list.properties.end = entries + 3;
  auto* old_storage = new TargetWord[1]{99u};
  OpaqueWordVector destination{old_storage, old_storage + 1, old_storage + 1};

  property_list_get_property_ids_006a3070(&list, &destination);
  check(destination.end - destination.begin == 3);
  check(destination.capacity - destination.begin == 3);
  check(destination.begin[0] == 801u);
  check(destination.begin[1] == 802u);
  check(destination.begin[2] == 803u);
  delete[] destination.begin;
}

void run() {
  const PropertyListRuntime initial_runtime = property_list_runtime();
  default_map_copy_entry = initial_runtime.map_copy;
  configure_runtime();
  test_layouts();
  test_direct_add_and_get_alt();
  test_copy_and_clear_order();
  test_default_map_copy_path();
  test_direct_copy_order();
  test_set_and_remove();
  test_new_entry_flag_four_ownership();
  test_conversion_destination_behavior();
  test_add_properties_from();
  test_read_success_and_failures();
  test_read_failed_key_read();
  test_read_short_circuits_entry_loop();
  test_read_parent_key_indices();
  test_get_property_ids();
  property_list_runtime() = initial_runtime;
}

#undef PKG_PROPERTY_WAVE9_TEST_THISCALL

}

}

int main() { openspore::reconstruction::pkg_property_wave9::run(); }
