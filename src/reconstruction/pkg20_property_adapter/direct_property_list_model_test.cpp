#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>

#include "direct_property_list.hpp"

namespace openspore::reconstruction::pkg20_property_adapter {

using TestOpaqueCleanupPort = void (*)(TargetWord, Property*, TargetWord,
                                       TargetWord, TargetWord, TargetWord);
void set_opaque_cleanup_port(TestOpaqueCleanupPort);

namespace {

int cleanup_calls = 0;
TargetWord cleanup_argument = 0;
bool cleanup_saw_flag = false;

void set_entry(PropertyMapEntry& entry, TargetWord key, TargetWord value,
               std::uint16_t type, std::uint8_t flags = 0,
               std::uint8_t flags_high = 0) {
  entry.key = key;
  entry.property.opaque_prefix[0] = static_cast<std::uint8_t>(value);
  entry.property.flags = flags;
  entry.property.opaque_0x11 = flags_high;
  entry.property.type = type;
}

void cleanup_materialize(Property& destination, const Property& source) {
  std::memcpy(destination.opaque_prefix.data(), source.opaque_prefix.data(),
              destination.opaque_prefix.size());
  destination.flags = 4;
  destination.opaque_0x11 = 0;
  destination.type = 1;
}

void cleanup_hook(Property& property, TargetWord argument) {
  ++cleanup_calls;
  cleanup_argument = argument;
  cleanup_saw_flag = (property.flags & 4) != 0;
  property.opaque_prefix[0] = 0;
}

int opaque_cleanup_calls = 0;
TargetWord opaque_cleanup_arg1 = 0;
TargetWord opaque_cleanup_arg2 = 0;
TargetWord opaque_cleanup_arg3 = 0;
TargetWord opaque_cleanup_arg4 = 0;
Property* opaque_cleanup_property = nullptr;
TargetWord opaque_cleanup_arg6 = 0;
Property captured_property{};
std::uintptr_t captured_property_address = 0;
bool captured_property_valid = false;

void capture_materialize(Property& destination, const Property& source) {
  std::memcpy(destination.opaque_prefix.data(), source.opaque_prefix.data(),
              destination.opaque_prefix.size());
  destination.flags =
      static_cast<std::uint8_t>((source.flags & ~0x02u) | 0x02u);
  destination.opaque_0x11 = source.opaque_0x11;
  destination.type = source.type;
  captured_property = destination;
  captured_property_address = reinterpret_cast<std::uintptr_t>(&destination);
  captured_property_valid = true;
}

bool list_tail_unchanged(const DirectPropertyList& list) {
  for (const auto value : list.opaque_40_53) {
    if (value != 0xa5) {
      return false;
    }
  }
  return true;
}

void opaque_cleanup_hook(TargetWord arg1, Property* property, TargetWord arg2,
                         TargetWord arg3, TargetWord arg4, TargetWord arg6) {
  ++opaque_cleanup_calls;
  opaque_cleanup_arg1 = arg1;
  opaque_cleanup_arg2 = arg2;
  opaque_cleanup_arg3 = arg3;
  opaque_cleanup_arg4 = arg4;
  opaque_cleanup_property = property;
  opaque_cleanup_arg6 = arg6;
}

void test_fast_hit() {
  DirectPropertyList list{};
  std::array<TargetWord, 2> values{1, 0};
  list.fast_access_count = values.size();
  list.values = values.data();

  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 0));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 1));
  assert(list.properties.entries_begin == nullptr);
  assert(list.properties.entries_end == nullptr);
}

void test_map_hit_and_exact_key() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 3> entries{};
  set_entry(entries[0], 10, 1, 1);
  set_entry(entries[1], 20, 1, 1);
  set_entry(entries[2], 30, 1, 1);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + entries.size();

  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 10));
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 20));
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 30));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 9));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 15));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 25));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 35));
}

void test_bool_void_and_false_values() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 3> entries{};
  set_entry(entries[0], 40, 0, 1);
  set_entry(entries[1], 41, 1, 0x10);
  set_entry(entries[2], 42, 0, 2);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + entries.size();

  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 40));
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 41));
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 42));
}

void test_materialization_paths() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 4> entries{};
  list.opaque_40_53.fill(0xa5);

  set_entry(entries[0], 60, 1, 1, 0x01, 0x34);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + 1;
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 60));
  assert(list_tail_unchanged(list));

  set_entry(entries[1], 61, 1, 0x10);
  list.properties.entries_begin = entries.data() + 1;
  list.properties.entries_end = entries.data() + 2;
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 61));
  assert(list_tail_unchanged(list));

  set_entry(entries[2], 62, 1, 1, 0x08);
  list.properties.entries_begin = entries.data() + 2;
  list.properties.entries_end = entries.data() + 3;
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 62));
  assert(list_tail_unchanged(list));

  std::uint8_t value = 1;
  std::uint32_t pointer_word =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&value));
  set_entry(entries[3], 63, 0, 1, 0x30);
  std::memcpy(entries[3].property.opaque_prefix.data(), &pointer_word,
              sizeof(pointer_word));
  list.properties.entries_begin = entries.data() + 3;
  list.properties.entries_end = entries.data() + 4;
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 63));
  assert(list_tail_unchanged(list));
}

void test_null_and_empty_map() {
  DirectPropertyList list{};

  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 0));

  std::array<PropertyMapEntry, 1> entries{};
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data();
  assert(!app_direct_property_list_get_direct_bool_006a25a0(&list, 1));
}

void test_stack_local_materialization_isolation() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 1> entries{};
  set_entry(entries[0], 52, 1, 1, 0x01, 0x34);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + entries.size();
  list.opaque_40_53.fill(0xa5);

  auto& services = property_adapter_services();
  const auto previous = services;
  services.materialize = capture_materialize;
  captured_property_valid = false;
  captured_property_address = 0;
  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 52));
  assert(captured_property_valid);
  const auto list_begin = reinterpret_cast<std::uintptr_t>(&list);
  const auto list_end = list_begin + sizeof(list);
  assert(captured_property_address < list_begin ||
         captured_property_address >= list_end);
  assert(captured_property.flags == 0x03);
  assert(captured_property.opaque_0x11 == 0x34);
  assert(captured_property.type == 1);
  assert(list_tail_unchanged(list));

  services = previous;
}

void test_default_cleanup_callback_port() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 1> entries{};
  set_entry(entries[0], 51, 1, 1, 0x04);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + entries.size();
  list.opaque_40_53.fill(0xa5);

  set_opaque_cleanup_port(opaque_cleanup_hook);
  opaque_cleanup_calls = 0;
  opaque_cleanup_arg1 = 1;
  opaque_cleanup_arg2 = 1;
  opaque_cleanup_arg3 = 1;
  opaque_cleanup_arg4 = 1;
  opaque_cleanup_property = nullptr;
  opaque_cleanup_arg6 = 0;

  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 51));
  assert(opaque_cleanup_calls == 1);
  assert(opaque_cleanup_arg1 == 1);
  assert(opaque_cleanup_arg2 == 0);
  assert(opaque_cleanup_arg3 == 0);
  assert(opaque_cleanup_arg4 == 0);
  const auto list_begin = reinterpret_cast<std::uintptr_t>(&list);
  const auto list_end = list_begin + sizeof(list);
  const auto property_address =
      reinterpret_cast<std::uintptr_t>(opaque_cleanup_property);
  assert(property_address < list_begin || property_address >= list_end);
  assert(opaque_cleanup_arg6 == 0);
  assert(list_tail_unchanged(list));

  set_opaque_cleanup_port(nullptr);
}

void test_temporary_cleanup_order() {
  DirectPropertyList list{};
  std::array<PropertyMapEntry, 1> entries{};
  set_entry(entries[0], 50, 1, 1);
  list.properties.entries_begin = entries.data();
  list.properties.entries_end = entries.data() + entries.size();
  list.opaque_40_53.fill(0xa5);

  auto& services = property_adapter_services();
  const auto previous = services;
  services.materialize = cleanup_materialize;
  services.cleanup = cleanup_hook;
  cleanup_calls = 0;
  cleanup_argument = 1;
  cleanup_saw_flag = false;

  assert(app_direct_property_list_get_direct_bool_006a25a0(&list, 50));
  assert(cleanup_calls == 1);
  assert(cleanup_argument == 0);
  assert(cleanup_saw_flag);
  assert(list_tail_unchanged(list));

  services = previous;
}

void run() {
  test_fast_hit();
  test_map_hit_and_exact_key();
  test_bool_void_and_false_values();
  test_materialization_paths();
  test_null_and_empty_map();
  test_stack_local_materialization_isolation();
  test_default_cleanup_callback_port();
  test_temporary_cleanup_order();
}

}

}

int main() { openspore::reconstruction::pkg20_property_adapter::run(); }
