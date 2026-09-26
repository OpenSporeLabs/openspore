#include <array>
#include <cstdlib>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "property_safe_wave9.hpp"

namespace openspore::reconstruction::pkg_property_safe_wave9 {
namespace {

#if defined(_MSC_VER)
#define PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL __thiscall
#else
#define PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL __attribute__((thiscall))
#endif

using AddFromSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaquePropertyList*);
using GetAltSignature = bool(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, TargetWord, OpaqueProperty**);
using CopyFromSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaquePropertyList*);
using GetIdsSignature = void(PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL*)(
    OpaquePropertyList*, OpaqueWordVector*);

static_assert(
    std::is_same<decltype(&direct_property_list_add_properties_from_006a1600),
                 AddFromSignature>::value,
    "006a1600 is thiscall with one explicit word popped by RET 4");
static_assert(
    std::is_same<decltype(&direct_property_list_get_property_alt_006a1e50),
                 GetAltSignature>::value,
    "006a1e50 is thiscall with two explicit words popped by RET 8");
static_assert(std::is_same<decltype(&property_list_copy_from_006a2a40),
                           CopyFromSignature>::value,
              "006a2a40 is thiscall with one explicit word popped by RET 4");
static_assert(std::is_same<decltype(&property_list_get_property_ids_006a3070),
                           GetIdsSignature>::value,
              "006a3070 is thiscall with one explicit word popped by RET 4");
static_assert(sizeof(decltype(OpaquePropertyListVtable::set_property_14)) == 4,
              "the +0x14 set slot is a single 32-bit pointer");
static_assert(sizeof(decltype(OpaquePropertyListVtable::get_property_alt_20)) ==
                  4,
              "the +0x20 alternate slot is a single 32-bit pointer");
static_assert(
    sizeof(decltype(OpaquePropertyListVtable::get_property_object_28)) == 4,
    "the +0x28 object slot is a single 32-bit pointer");
static_assert(
    std::is_same<decltype(PropertySafePorts::cleanup), PropertyCleanup>::value,
    "the cleanup port keeps the canonical six-word 0x0093db80 call shape");
static_assert(
    std::is_same<decltype(PropertySafePorts::convert), PropertyConvert>::value,
    "the convert port keeps the 0x0093dd80 thiscall shape");
static_assert(
    std::is_same<decltype(PropertySafePorts::map_copy), MapCopy>::value,
    "the map helper stays a thiscall port, never a target record");
static_assert(
    std::is_same<decltype(PropertySafePorts::set_parent), SetParent>::value,
    "the parent helper stays a thiscall port, never a target record");
static_assert(
    std::is_same<decltype(PropertySafePorts::resize_words),
                 ResizeWordVector>::value,
    "the word vector helper stays a thiscall port, never a target record");
static_assert(std::is_same<decltype(PropertySafePorts::get_property_alt_base),
                           GetPropertyAlt>::value,
              "the base lookup stays a thiscall port, never a target record");

std::vector<std::string> events;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

void reset_events() { events.clear(); }

OpaqueProperty fast_property{};
OpaqueProperty parent_property{};
OpaqueProperty list_property{};

TargetWord recorded_ids[16]{};
OpaqueProperty* recorded_values[16]{};
OpaquePropertyList* recorded_receivers[16]{};
std::size_t set_calls = 0;

std::size_t base_port_calls = 0;
OpaquePropertyList* base_port_list = nullptr;
TargetWord base_port_id = 0;
OpaqueProperty** base_port_result = nullptr;
bool base_port_return = false;

std::size_t map_copy_calls = 0;
OpaquePropertyMap* map_copy_destination = nullptr;
const OpaquePropertyMap* map_copy_source = nullptr;

std::size_t set_parent_calls = 0;
OpaquePropertyList* set_parent_list = nullptr;
OpaquePropertyList* set_parent_parent = nullptr;

std::size_t resize_calls = 0;
OpaqueWordVector* resize_vector = nullptr;
TargetWord resize_count = 0;
OpaquePropertyList* resize_probe_list = nullptr;

std::size_t cleanup_calls = 0;
TargetWord cleanup_code = 0;
OpaqueProperty* cleanup_property_ptr = nullptr;
TargetWord cleanup_argument = 0;
TargetWord cleanup_trailing[3]{};

std::size_t convert_calls = 0;

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL set_property_hook(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty* value) {
  check(set_calls < 16u);
  events.push_back("set");
  recorded_receivers[set_calls] = list;
  recorded_ids[set_calls] = property_id;
  recorded_values[set_calls] = value;
  ++set_calls;
}

OpaqueProperty* PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
get_fast_hook(OpaquePropertyList*, TargetWord property_id) {
  events.push_back("fast" + std::to_string(property_id));
  return &fast_property;
}

bool PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL parent_get_alt_hook(
    OpaquePropertyList*, TargetWord property_id, OpaqueProperty** result) {
  events.push_back("parent" + std::to_string(property_id));
  if (property_id != 700u) {
    return false;
  }
  *result = &parent_property;
  return true;
}

bool PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL get_property_alt_base_hook(
    OpaquePropertyList* list, TargetWord property_id, OpaqueProperty** result) {
  ++base_port_calls;
  base_port_list = list;
  base_port_id = property_id;
  base_port_result = result;
  events.push_back("base" + std::to_string(property_id));
  if (base_port_return) {
    *result = &list_property;
  }
  return base_port_return;
}

OpaquePropertyMap* PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
map_copy_hook(OpaquePropertyMap* destination, const OpaquePropertyMap* source) {
  ++map_copy_calls;
  map_copy_destination = destination;
  map_copy_source = source;
  events.push_back("map_copy");
  return destination;
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
set_parent_hook(OpaquePropertyList* list, OpaquePropertyList* parent) {
  ++set_parent_calls;
  set_parent_list = list;
  set_parent_parent = parent;
  events.push_back("set_parent");
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
resize_words_hook(OpaqueWordVector* vector, TargetWord count) {
  ++resize_calls;
  resize_vector = vector;
  resize_count = count;
  events.push_back("resize" + std::to_string(count));
  vector->end = vector->begin + count;
  if (resize_probe_list != nullptr) {
    resize_probe_list->properties.end = resize_probe_list->properties.begin;
  }
}

void cleanup_hook(TargetWord code, OpaqueProperty* property, TargetWord,
                  TargetWord argument, TargetWord fourth, TargetWord fifth) {
  ++cleanup_calls;
  cleanup_code = code;
  cleanup_property_ptr = property;
  cleanup_argument = argument;
  cleanup_trailing[0] = fourth;
  cleanup_trailing[1] = fifth;
}

void PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL convert_hook(OpaqueProperty*,
                                                        TargetWord,
                                                        std::uint16_t,
                                                        const void*, TargetWord,
                                                        TargetWord) {
  ++convert_calls;
}

void reset_counters() {
  set_calls = 0;
  base_port_calls = 0;
  base_port_return = false;
  map_copy_calls = 0;
  set_parent_calls = 0;
  resize_calls = 0;
  cleanup_calls = 0;
  convert_calls = 0;
  reset_events();
}

struct Fixture {
  std::array<OpaquePropertyEntry, 8> source_storage{};
  std::array<OpaquePropertyEntry, 8> destination_storage{};
  std::array<TargetWord, 8> word_storage{};
  OpaquePropertyListVtable vtable{};
  OpaquePropertyListVtable parent_vtable{};
  OpaquePropertyList list{};
  OpaquePropertyList other{};
  OpaquePropertyList parent{};
  OpaqueWordVector words{};

  void reset() {
    std::memset(this, 0, sizeof(*this));
    reset_counters();
  }

  void arm_vtables() {
    vtable.set_property_14 = set_property_hook;
    vtable.get_property_alt_20 = parent_get_alt_hook;
    vtable.get_property_object_28 = get_fast_hook;
    parent_vtable.get_property_alt_20 = parent_get_alt_hook;
    parent_vtable.get_property_object_28 = get_fast_hook;
  }

  void bind(OpaquePropertyList* target, OpaquePropertyEntry* storage,
            TargetWord count) {
    target->vtable = &vtable;
    target->properties.begin = storage;
    target->properties.end = storage + count;
    target->properties.capacity = storage + 8;
    target->properties.lookup_mode = 0;
  }

  void bind_words() {
    words.begin = word_storage.data();
    words.end = word_storage.data();
    words.capacity = word_storage.data() + word_storage.size();
  }
};

PropertySafePorts observed_ports() {
  PropertySafePorts ports = property_safe_ports();
  ports.cleanup = cleanup_hook;
  ports.convert = convert_hook;
  ports.map_copy = map_copy_hook;
  ports.set_parent = set_parent_hook;
  ports.resize_words = resize_words_hook;
  ports.get_property_alt_base = get_property_alt_base_hook;
  return ports;
}

void test_add_from_self_copy_is_noop() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 10u;
  fixture.source_storage[1].id = 11u;
  fixture.source_storage[2].id = 12u;
  fixture.list.operations_done = 7u;

  direct_property_list_add_properties_from_006a1600(&fixture.list,
                                                    &fixture.list);

  check(set_calls == 0u);
  check(events.empty());
  check(fixture.list.operations_done == 7u);
}

void test_add_from_empty_source_still_counts() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 0u);
  fixture.bind(&fixture.other, fixture.destination_storage.data(), 0u);
  fixture.list.operations_done = 41u;

  direct_property_list_add_properties_from_006a1600(&fixture.list,
                                                    &fixture.other);

  check(set_calls == 0u);
  check(events.empty());
  check(fixture.list.operations_done == 42u);
  check(fixture.other.operations_done == 0u);
}

void test_add_from_dispatches_each_source_id_in_order() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 0u);
  fixture.bind(&fixture.other, fixture.destination_storage.data(), 3u);
  fixture.destination_storage[0].id = 5u;
  fixture.destination_storage[1].id = 9u;
  fixture.destination_storage[2].id = 12u;
  fixture.destination_storage[0].property.type = 0x10u;
  fixture.destination_storage[1].property.type = 0x0001u;
  fixture.destination_storage[2].property.type = 0x0002u;
  fixture.list.operations_done = 0u;

  direct_property_list_add_properties_from_006a1600(&fixture.list,
                                                    &fixture.other);

  check(set_calls == 3u);
  check(recorded_ids[0] == 5u);
  check(recorded_ids[1] == 9u);
  check(recorded_ids[2] == 12u);
  check(recorded_receivers[0] == &fixture.list);
  check(recorded_receivers[1] == &fixture.list);
  check(recorded_receivers[2] == &fixture.list);
  check(recorded_values[0] == &fixture.destination_storage[0].property);
  check(recorded_values[1] == &fixture.destination_storage[1].property);
  check(recorded_values[2] == &fixture.destination_storage[2].property);
  check(recorded_values[0]->type == 0x10u);
  check(recorded_values[1]->type == 0x0001u);
  check(recorded_values[2]->type == 0x0002u);
  check(events.size() == 3u);
  check(events[0] == "set");
  check(events[1] == "set");
  check(events[2] == "set");
  check(fixture.list.operations_done == 1u);
}

void test_get_alt_fast_path_uses_object_slot() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 2u);
  fixture.list.fast_count = 4u;
  fixture.list.fast_values = fixture.word_storage.data();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      &fixture.list, 2u, &result);

  check(found);
  check(result == &fast_property);
  check(base_port_calls == 0u);
  check(events.size() == 1u);
  check(events[0] == "fast2");
}

void test_get_alt_fast_boundary_is_unsigned() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 2u);
  fixture.list.fast_count = 4u;
  fixture.list.fast_values = fixture.word_storage.data();
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      &fixture.list, 4u, &result);

  check(!found);
  check(result == nullptr);
  check(base_port_calls == 1u);
  check(base_port_id == 4u);
  check(events.size() == 1u);
  check(events[0] == "base4");
}

void test_get_alt_above_fast_count_reaches_base_port() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 2u);
  fixture.list.fast_count = 4u;
  fixture.list.fast_values = fixture.word_storage.data();
  PropertySafePorts ports = observed_ports();
  base_port_return = true;
  property_safe_set_ports(ports);

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      &fixture.list, 0x80000000u, &result);

  check(found);
  check(result == &list_property);
  check(base_port_calls == 1u);
  check(base_port_list == &fixture.list);
  check(base_port_id == 0x80000000u);
  check(base_port_result == &result);
}

void test_get_alt_zero_fast_count_always_uses_base() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 1u);
  fixture.source_storage[0].id = 3u;
  fixture.list.fast_count = 0u;
  fixture.list.fast_values = nullptr;
  property_safe_set_ports(observed_ports());

  OpaqueProperty* result = nullptr;
  const bool found = direct_property_list_get_property_alt_006a1e50(
      &fixture.list, 0u, &result);

  check(!found);
  check(base_port_calls == 1u);
}

void test_get_alt_base_port_map_hit_and_miss() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 2u;
  fixture.source_storage[1].id = 4u;
  fixture.source_storage[2].id = 6u;
  fixture.list.fast_count = 0u;
  property_safe_reset_ports();

  OpaqueProperty* result = nullptr;
  check(direct_property_list_get_property_alt_006a1e50(&fixture.list, 4u,
                                                       &result));
  check(result == &fixture.source_storage[1].property);
  check(direct_property_list_get_property_alt_006a1e50(&fixture.list, 2u,
                                                       &result));
  check(result == &fixture.source_storage[0].property);
  check(direct_property_list_get_property_alt_006a1e50(&fixture.list, 6u,
                                                       &result));
  check(result == &fixture.source_storage[2].property);
  result = nullptr;
  check(!direct_property_list_get_property_alt_006a1e50(&fixture.list, 5u,
                                                        &result));
  check(result == nullptr);
  check(!direct_property_list_get_property_alt_006a1e50(&fixture.list, 0u,
                                                        &result));
  check(!direct_property_list_get_property_alt_006a1e50(&fixture.list, 7u,
                                                        &result));
  check(!direct_property_list_get_property_alt_006a1e50(&fixture.list, 9u,
                                                        &result));
  check(events.empty());
}

void test_get_alt_base_port_defers_to_parent_slot() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 1u);
  fixture.source_storage[0].id = 2u;
  fixture.list.fast_count = 0u;
  fixture.parent.vtable = &fixture.parent_vtable;
  fixture.list.parent = &fixture.parent;
  property_safe_reset_ports();

  OpaqueProperty* result = nullptr;
  check(!direct_property_list_get_property_alt_006a1e50(&fixture.list, 3u,
                                                        &result));
  check(events.size() == 1u);
  check(events[0] == "parent3");
  check(direct_property_list_get_property_alt_006a1e50(&fixture.list, 700u,
                                                       &result));
  check(result == &parent_property);
}

void test_copy_from_self_copy_is_noop() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 2u);
  fixture.list.properties.lookup_mode = 0x5au;
  fixture.list.parent = &fixture.parent;
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(&fixture.list, &fixture.list);

  check(map_copy_calls == 0u);
  check(set_parent_calls == 0u);
  check(events.empty());
  check(fixture.list.properties.lookup_mode == 0x5au);
}

void test_copy_from_delegates_and_copies_lookup_mode() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 1u);
  fixture.bind(&fixture.other, fixture.source_storage.data(), 2u);
  fixture.other.properties.lookup_mode = 0xa7u;
  fixture.list.properties.lookup_mode = 0x11u;
  fixture.list.parent = &fixture.parent;
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(&fixture.list, &fixture.other);

  check(map_copy_calls == 1u);
  check(map_copy_destination == &fixture.list.properties);
  check(map_copy_source == &fixture.other.properties);
  check(set_parent_calls == 1u);
  check(set_parent_list == &fixture.list);
  check(set_parent_parent == &fixture.parent);
  check(fixture.list.properties.lookup_mode == 0xa7u);
  check(events.size() == 2u);
  check(events[0] == "map_copy");
  check(events[1] == "set_parent");
}

void test_copy_from_reads_lookup_mode_from_source() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 0u);
  fixture.bind(&fixture.other, fixture.source_storage.data(), 0u);
  fixture.list.properties.lookup_mode = 0xffu;
  fixture.other.properties.lookup_mode = 0x00u;
  property_safe_set_ports(observed_ports());

  property_list_copy_from_006a2a40(&fixture.list, &fixture.other);

  check(fixture.list.properties.lookup_mode == 0x00u);
  check(map_copy_calls == 1u);
  check(set_parent_calls == 1u);
}

void test_copy_from_default_map_port_transfers_span() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 0u);
  fixture.bind(&fixture.other, fixture.source_storage.data(), 2u);
  fixture.source_storage[0].id = 21u;
  fixture.source_storage[0].property.type = 0x10u;
  fixture.source_storage[0].property.flags = 0x0006u;
  fixture.source_storage[0].property.value[3] = 0xabu;
  fixture.source_storage[1].id = 22u;
  fixture.source_storage[1].property.type = 0x0001u;
  property_safe_reset_ports();

  property_list_copy_from_006a2a40(&fixture.list, &fixture.other);

  check(fixture.destination_storage[0].id == 21u);
  check(fixture.destination_storage[0].property.type == 0x10u);
  check(fixture.destination_storage[0].property.flags == 0x0006u);
  check(fixture.destination_storage[0].property.value[3] == 0xabu);
  check(fixture.destination_storage[1].id == 22u);
  check(fixture.destination_storage[1].property.type == 0x0001u);
  check(cleanup_calls == 0u);
  check(convert_calls == 0u);
}

void test_default_map_port_self_copy_is_noop() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 0u);
  fixture.destination_storage[0].id = 99u;
  fixture.destination_storage[0].property.type = 0x05u;
  property_safe_reset_ports();

  OpaquePropertyMap* result = property_safe_ports().map_copy(
      &fixture.list.properties, &fixture.list.properties);

  check(result == &fixture.list.properties);
  check(fixture.destination_storage[0].id == 99u);
  check(fixture.destination_storage[0].property.type == 0x05u);
}

void test_default_map_port_bounded_by_destination_capacity() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 0u);
  fixture.list.properties.capacity = fixture.destination_storage.data() + 1;
  fixture.bind(&fixture.other, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 31u;
  fixture.source_storage[1].id = 32u;
  fixture.source_storage[2].id = 33u;
  property_safe_reset_ports();

  property_list_copy_from_006a2a40(&fixture.list, &fixture.other);

  check(fixture.destination_storage[0].id == 31u);
  check(fixture.destination_storage[1].id == 0u);
  check(fixture.destination_storage[2].id == 0u);
}

void test_get_ids_resizes_then_copies_ids() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 4u;
  fixture.source_storage[1].id = 8u;
  fixture.source_storage[2].id = 15u;
  fixture.bind_words();
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(&fixture.list, &fixture.words);

  check(resize_calls == 1u);
  check(resize_vector == &fixture.words);
  check(resize_count == 3u);
  check(fixture.word_storage[0] == 4u);
  check(fixture.word_storage[1] == 8u);
  check(fixture.word_storage[2] == 15u);
  check(fixture.words.end == fixture.words.begin + 3);
  check(events.size() == 1u);
  check(events[0] == "resize3");
}

void test_get_ids_empty_map_resizes_to_zero() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 0u);
  fixture.bind_words();
  fixture.words.end = fixture.word_storage.data() + 4;
  property_safe_set_ports(observed_ports());

  property_list_get_property_ids_006a3070(&fixture.list, &fixture.words);

  check(resize_calls == 1u);
  check(resize_count == 0u);
  check(fixture.words.end == fixture.words.begin);
}

void test_get_ids_passes_raw_signed_quotient() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data() + 4, 3u);
  fixture.bind_words();
  fixture.list.properties.end = fixture.source_storage.data() + 3;
  property_safe_set_ports(observed_ports());
  resize_probe_list = &fixture.list;

  property_list_get_property_ids_006a3070(&fixture.list, &fixture.words);

  check(resize_calls == 1u);
  check(resize_count == 0xffffffffu);
  check(fixture.word_storage[0] == 0u);
  resize_probe_list = nullptr;
}

void test_get_ids_default_port_allocates_and_fills() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 1u;
  fixture.source_storage[1].id = 2u;
  fixture.source_storage[2].id = 3u;
  property_safe_reset_ports();
  OpaqueWordVector words{};

  property_list_get_property_ids_006a3070(&fixture.list, &words);

  check(words.begin != nullptr);
  check(words.end == words.begin + 3);
  check(words.capacity == words.begin + 3);
  check(words.begin[0] == 1u);
  check(words.begin[1] == 2u);
  check(words.begin[2] == 3u);
  delete[] words.begin;
}

void test_get_ids_default_port_grow_preserves_prefix() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 1u;
  fixture.source_storage[1].id = 2u;
  fixture.source_storage[2].id = 3u;
  property_safe_reset_ports();
  OpaqueWordVector words{};
  property_list_get_property_ids_006a3070(&fixture.list, &words);
  check(words.begin[0] == 1u);

  fixture.source_storage[3].id = 4u;
  fixture.source_storage[4].id = 5u;
  fixture.list.properties.end = fixture.source_storage.data() + 5;
  property_list_get_property_ids_006a3070(&fixture.list, &words);

  check(words.end == words.begin + 5);
  check(words.capacity == words.begin + 5);
  check(words.begin[0] == 1u);
  check(words.begin[1] == 2u);
  check(words.begin[2] == 3u);
  check(words.begin[3] == 4u);
  check(words.begin[4] == 5u);
  delete[] words.begin;
}

void test_get_ids_default_port_shrink_keeps_tail() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 3u);
  fixture.source_storage[0].id = 1u;
  fixture.source_storage[1].id = 2u;
  fixture.source_storage[2].id = 3u;
  property_safe_reset_ports();
  OpaqueWordVector words{};
  property_list_get_property_ids_006a3070(&fixture.list, &words);
  check(words.begin[0] == 1u);
  check(words.begin[1] == 2u);
  check(words.begin[2] == 3u);

  fixture.source_storage[0].id = 7u;
  fixture.list.properties.end = fixture.source_storage.data() + 1;
  property_list_get_property_ids_006a3070(&fixture.list, &words);

  check(words.end == words.begin + 1);
  check(words.begin[0] == 7u);
  check(words.begin[1] == 2u);
  check(words.begin[2] == 3u);
  delete[] words.begin;
}

void test_get_ids_default_port_empty_allocates_nothing() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 0u);
  property_safe_reset_ports();
  OpaqueWordVector words{};

  property_list_get_property_ids_006a3070(&fixture.list, &words);

  check(words.begin == nullptr);
  check(words.end == nullptr);
  check(words.capacity == nullptr);
}

void test_targets_never_reach_cleanup_or_convert_ports() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.destination_storage.data(), 2u);
  fixture.bind(&fixture.other, fixture.source_storage.data(), 2u);
  fixture.destination_storage[0].id = 6u;
  fixture.destination_storage[1].id = 18u;
  fixture.source_storage[0].id = 6u;
  fixture.source_storage[0].property.flags = 0x0004u;
  fixture.source_storage[1].id = 18u;
  fixture.source_storage[1].property.flags = 0x0030u;
  fixture.other.properties.lookup_mode = 0x3cu;
  fixture.list.parent = &fixture.parent;
  fixture.bind_words();
  fixture.list.fast_count = 2u;
  fixture.list.fast_values = fixture.word_storage.data();
  property_safe_set_ports(observed_ports());
  base_port_return = true;

  OpaqueProperty* result = nullptr;
  direct_property_list_add_properties_from_006a1600(&fixture.list,
                                                    &fixture.other);
  direct_property_list_get_property_alt_006a1e50(&fixture.list, 1u, &result);
  direct_property_list_get_property_alt_006a1e50(&fixture.list, 40u, &result);
  property_list_copy_from_006a2a40(&fixture.list, &fixture.other);
  property_list_get_property_ids_006a3070(&fixture.list, &fixture.words);

  check(cleanup_calls == 0u);
  check(convert_calls == 0u);
  check(map_copy_calls == 1u);
  check(set_parent_calls == 1u);
  check(resize_calls == 1u);
  check(resize_count == 2u);
  check(base_port_calls == 1u);
  check(set_calls == 2u);
  check(fixture.list.operations_done == 1u);
}

void test_cleanup_port_keeps_canonical_call_shape() {
  Fixture fixture;
  fixture.reset();
  property_safe_set_ports(observed_ports());
  OpaqueProperty property{};
  property.flags = 0x0004u;

  property_safe_ports().cleanup(1u, &property, 0u, 0u, 0u, 0u);

  check(cleanup_calls == 1u);
  check(cleanup_code == 1u);
  check(cleanup_property_ptr == &property);
  check(cleanup_argument == 0u);
  check(cleanup_trailing[0] == 0u);
  check(cleanup_trailing[1] == 0u);
  check(property.flags == 0x0004u);
}

void test_default_cleanup_and_convert_ports_are_inert() {
  property_safe_reset_ports();
  reset_counters();
  OpaqueProperty property{};
  property.flags = 0x0004u;
  property.type = 0x10u;

  property_safe_ports().cleanup(1u, &property, 0u, 0u, 0u, 0u);
  property_safe_ports().convert(&property, 0x10u, 0x0004u, &property, 0x10u,
                                1u);

  check(property.type == 0x10u);
  check(property.flags == 0x0004u);
  check(cleanup_calls == 0u);
  check(convert_calls == 0u);
}

void test_default_set_parent_port_is_inert() {
  property_safe_reset_ports();
  Fixture fixture;
  fixture.reset();
  fixture.list.parent = &fixture.parent;

  property_safe_ports().set_parent(&fixture.list, fixture.list.parent);

  check(fixture.list.parent == &fixture.parent);
  check(set_parent_calls == 0u);
}

void test_signatures_round_trip_through_ports() {
  Fixture fixture;
  fixture.reset();
  fixture.arm_vtables();
  fixture.bind(&fixture.list, fixture.source_storage.data(), 0u);
  AddFromSignature add = direct_property_list_add_properties_from_006a1600;
  GetAltSignature get = direct_property_list_get_property_alt_006a1e50;
  CopyFromSignature copy = property_list_copy_from_006a2a40;
  GetIdsSignature ids = property_list_get_property_ids_006a3070;
  property_safe_reset_ports();
  OpaqueWordVector words{};
  OpaqueProperty* result = nullptr;

  add(&fixture.list, &fixture.list);
  check(!get(&fixture.list, 0u, &result));
  copy(&fixture.list, &fixture.list);
  ids(&fixture.list, &words);

  check(fixture.list.operations_done == 0u);
  check(result == nullptr);
  check(words.begin == nullptr);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_property_safe_wave9;
  test_add_from_self_copy_is_noop();
  test_add_from_empty_source_still_counts();
  test_add_from_dispatches_each_source_id_in_order();
  test_get_alt_fast_path_uses_object_slot();
  test_get_alt_fast_boundary_is_unsigned();
  test_get_alt_above_fast_count_reaches_base_port();
  test_get_alt_zero_fast_count_always_uses_base();
  test_get_alt_base_port_map_hit_and_miss();
  test_get_alt_base_port_defers_to_parent_slot();
  test_copy_from_self_copy_is_noop();
  test_copy_from_delegates_and_copies_lookup_mode();
  test_copy_from_reads_lookup_mode_from_source();
  test_copy_from_default_map_port_transfers_span();
  test_default_map_port_self_copy_is_noop();
  test_default_map_port_bounded_by_destination_capacity();
  test_get_ids_resizes_then_copies_ids();
  test_get_ids_empty_map_resizes_to_zero();
  test_get_ids_passes_raw_signed_quotient();
  test_get_ids_default_port_allocates_and_fills();
  test_get_ids_default_port_grow_preserves_prefix();
  test_get_ids_default_port_shrink_keeps_tail();
  test_get_ids_default_port_empty_allocates_nothing();
  test_targets_never_reach_cleanup_or_convert_ports();
  test_cleanup_port_keeps_canonical_call_shape();
  test_default_cleanup_and_convert_ports_are_inert();
  test_default_set_parent_port_is_inert();
  test_signatures_round_trip_through_ports();
  return 0;
}

#undef PKG_PROPERTY_SAFE_WAVE9_TEST_THISCALL
