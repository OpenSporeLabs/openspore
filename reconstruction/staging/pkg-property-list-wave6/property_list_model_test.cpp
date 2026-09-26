#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstdint>
#include <cstring>
#include <vector>

#include "property_list.hpp"

namespace openspore::reconstruction::pkg_property_list_wave6 {

namespace {

#if defined(_MSC_VER)
#define WAVE6_TEST_THISCALL __thiscall
#else
#define WAVE6_TEST_THISCALL __attribute__((thiscall))
#endif

struct Trace {
  std::vector<int> events;
  std::vector<Wave6Word> words;
  std::vector<Wave6Word> word_counts;
  std::vector<Wave6Word> word_modes;
  std::vector<Wave6Property*> properties;
  std::vector<Wave6Word> property_modes;
  int fail_word_call = -1;
  int fail_property_call = -1;
};

Trace trace;
Wave6PropertyList* release_receiver = nullptr;
Wave6PropertyList* clear_receiver = nullptr;
Wave6PropertyList* add_38_receiver = nullptr;
Wave6PropertyList* add_38_argument = nullptr;
Wave6PropertyList* add_30_receiver = nullptr;
Wave6PropertyList* add_30_argument = nullptr;
Wave6PropertyList* parent_receiver = nullptr;
Wave6Word parent_property_id = 0;
bool parent_query_result = true;
bool parent_writes_output = false;
Wave6Property* parent_property = nullptr;

Wave6Property* missing_property() {
  return reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x016027d0u));
}

bool write_words(Wave6OpaqueStream*, const Wave6Word* values, Wave6Word count,
                 Wave6Word mode) {
  trace.events.push_back(1);
  const int call = static_cast<int>(trace.words.size());
  trace.words.push_back(*values);
  trace.word_counts.push_back(count);
  trace.word_modes.push_back(mode);
  return call != trace.fail_word_call;
}

bool write_property(Wave6OpaqueStream*, Wave6Property* property,
                    Wave6Word mode) {
  trace.events.push_back(2);
  const int call = static_cast<int>(trace.properties.size());
  trace.properties.push_back(property);
  trace.property_modes.push_back(mode);
  return call != trace.fail_property_call;
}

void WAVE6_TEST_THISCALL release_this(Wave6PropertyList* self) {
  assert(self == release_receiver);
  trace.events.push_back(1);
}

void WAVE6_TEST_THISCALL clear_this(Wave6PropertyList* self) {
  assert(self == clear_receiver);
  trace.events.push_back(3);
}

void WAVE6_TEST_THISCALL add_all_38(Wave6PropertyList* self,
                                    Wave6PropertyList* argument) {
  assert(self == add_38_receiver);
  assert(argument == add_38_argument);
  trace.events.push_back(2);
}

void WAVE6_TEST_THISCALL add_all_30(Wave6PropertyList* self,
                                    Wave6PropertyList* argument) {
  assert(self == add_30_receiver);
  assert(argument == add_30_argument);
  trace.events.push_back(4);
}

bool WAVE6_TEST_THISCALL parent_has(Wave6PropertyList* self,
                                    Wave6Word property_id) {
  assert(self == parent_receiver);
  assert(property_id == parent_property_id);
  trace.events.push_back(10);
  return parent_query_result;
}

bool WAVE6_TEST_THISCALL parent_get_alt(Wave6PropertyList* self,
                                        Wave6Word property_id,
                                        Wave6Property** result) {
  assert(self == parent_receiver);
  assert(property_id == parent_property_id);
  trace.events.push_back(11);
  if (parent_writes_output) {
    *result = parent_property;
  }
  return parent_query_result;
}

bool WAVE6_TEST_THISCALL parent_get(Wave6PropertyList* self,
                                    Wave6Word property_id,
                                    Wave6Property** result) {
  assert(self == parent_receiver);
  assert(property_id == parent_property_id);
  trace.events.push_back(12);
  if (parent_writes_output) {
    *result = parent_property;
  }
  return parent_query_result;
}

Wave6Property* WAVE6_TEST_THISCALL parent_get_object(Wave6PropertyList* self,
                                                     Wave6Word property_id) {
  assert(self == parent_receiver);
  assert(property_id == parent_property_id);
  trace.events.push_back(13);
  return parent_query_result ? parent_property : missing_property();
}

Wave6PropertyListVtable make_vtable() {
  Wave6PropertyListVtable vtable{};
  vtable.release_04 = release_this;
  vtable.parent_has_1c = parent_has;
  vtable.parent_get_alt_20 = parent_get_alt;
  vtable.parent_get_24 = parent_get;
  vtable.parent_get_object_28 = parent_get_object;
  vtable.add_all_30 = add_all_30;
  vtable.add_all_38 = add_all_38;
  vtable.clear_48 = clear_this;
  return vtable;
}

void configure_dispatch_receivers(Wave6PropertyList* list,
                                  Wave6PropertyList* parent,
                                  Wave6PropertyList* add_38_source,
                                  Wave6PropertyList* add_30_source) {
  release_receiver = parent;
  clear_receiver = list;
  add_38_receiver = list;
  add_38_argument = add_38_source;
  add_30_receiver = list;
  add_30_argument = add_30_source;
}

void test_copy_all_properties_from() {
  Wave6PropertyListVtable vtable = make_vtable();
  Wave6PropertyList list{};
  Wave6PropertyList other{};
  Wave6PropertyList parent{};
  list.vtable = &vtable;
  other.vtable = &vtable;
  parent.vtable = &vtable;
  configure_dispatch_receivers(&list, &parent, &other, &other);

  trace = Trace{};
  app_property_list_copy_all_properties_from_006a14d0(&list, &list);
  assert(trace.events.empty());

  list.parent_30 = &parent;
  app_property_list_copy_all_properties_from_006a14d0(&list, &other);
  assert(trace.events == std::vector<int>{1, 3, 2});
  assert(list.parent_30 == nullptr);

  trace = Trace{};
  app_property_list_copy_all_properties_from_006a14d0(&list, &other);
  assert(trace.events == std::vector<int>{3, 2});
}

void test_add_all_properties_from() {
  Wave6PropertyListVtable vtable = make_vtable();
  Wave6PropertyList list{};
  Wave6PropertyList other{};
  Wave6PropertyList parent{};
  list.vtable = &vtable;
  other.vtable = &vtable;
  parent.vtable = &vtable;
  configure_dispatch_receivers(&list, &parent, &parent, &other);

  other.parent_30 = &parent;
  trace = Trace{};
  app_property_list_add_all_properties_from_006a1510(&list, &other);
  assert(trace.events == std::vector<int>{2, 4});
  assert(other.parent_30 == &parent);

  other.parent_30 = nullptr;
  trace = Trace{};
  app_property_list_add_all_properties_from_006a1510(&list, &other);
  assert(trace.events == std::vector<int>{4});
}

void test_write_success_and_payload_delegation() {
  std::array<Wave6PropertyEntry, 2> entries{};
  entries[0].id = 7;
  entries[1].id = 9;
  for (std::size_t index = 0; index < entries.size(); ++index) {
    entries[index].property.opaque_00_0f.fill(
        static_cast<std::uint8_t>(0xa0u + index));
    entries[index].property.flags_10 = 0x10u;
    entries[index].property.type_12 = 9u;
  }
  Wave6PropertyList list{};
  list.entries_begin_18 = entries.data();
  list.entries_end_1c = entries.data() + entries.size();
  std::array<std::uint8_t, 0x10> stream_bytes{};

  Wave6NativePorts previous = wave6_property_list_native_ports();
  wave6_property_list_native_ports() =
      Wave6NativePorts{write_words, write_property};
  trace = Trace{};
  assert(app_property_list_write_006a1540(
      &list, reinterpret_cast<Wave6OpaqueStream*>(stream_bytes.data())));
  assert(trace.events == std::vector<int>{1, 1, 2, 1, 2});
  assert(trace.words == std::vector<Wave6Word>{2, 7, 9});
  assert(trace.word_counts == std::vector<Wave6Word>{1, 1, 1});
  assert(trace.word_modes == std::vector<Wave6Word>{0, 0, 0});
  assert(trace.properties == std::vector<Wave6Property*>{&entries[0].property,
                                                         &entries[1].property});
  assert(trace.property_modes == std::vector<Wave6Word>{0, 0});
  assert(entries[0].property.flags_10 == 0x10u);
  assert(entries[0].property.type_12 == 9u);
  assert(entries[1].property.flags_10 == 0x10u);
  assert(entries[1].property.type_12 == 9u);

  trace = Trace{};
  list.entries_begin_18 = entries.data();
  list.entries_end_1c = entries.data();
  assert(app_property_list_write_006a1540(
      &list, reinterpret_cast<Wave6OpaqueStream*>(stream_bytes.data())));
  assert(trace.events == std::vector<int>{1});
  assert(trace.words == std::vector<Wave6Word>{0});

  wave6_property_list_native_ports() = previous;
}

void test_write_failure_short_circuit() {
  std::array<Wave6PropertyEntry, 3> entries{};
  entries[0].id = 1;
  entries[1].id = 2;
  entries[2].id = 3;
  Wave6PropertyList list{};
  list.entries_begin_18 = entries.data();
  list.entries_end_1c = entries.data() + entries.size();
  std::array<std::uint8_t, 0x10> stream_bytes{};

  Wave6NativePorts previous = wave6_property_list_native_ports();
  wave6_property_list_native_ports() =
      Wave6NativePorts{write_words, write_property};

  trace = Trace{};
  trace.fail_word_call = 0;
  assert(!app_property_list_write_006a1540(
      &list, reinterpret_cast<Wave6OpaqueStream*>(stream_bytes.data())));
  assert(trace.events == std::vector<int>{1});
  assert(trace.properties.empty());

  trace = Trace{};
  trace.fail_word_call = 2;
  assert(!app_property_list_write_006a1540(
      &list, reinterpret_cast<Wave6OpaqueStream*>(stream_bytes.data())));
  assert(trace.events == std::vector<int>{1, 1, 2, 1});
  assert(trace.words == std::vector<Wave6Word>{3, 1, 2});
  assert(trace.properties == std::vector<Wave6Property*>{&entries[0].property});
  trace = Trace{};
  trace.fail_property_call = 0;
  assert(!app_property_list_write_006a1540(
      &list, reinterpret_cast<Wave6OpaqueStream*>(stream_bytes.data())));
  assert(trace.events == std::vector<int>{1, 1, 2});
  assert(trace.properties == std::vector<Wave6Property*>{&entries[0].property});

  wave6_property_list_native_ports() = previous;
}

void test_local_lookup_and_sentinel() {
  std::array<Wave6PropertyEntry, 3> entries{};
  entries[0].id = 10;
  entries[1].id = 20;
  entries[2].id = 30;
  Wave6PropertyList list{};
  list.entries_begin_18 = entries.data();
  list.entries_end_1c = entries.data() + entries.size();
  list.lookup_mode_2c = 0xa5u;
  Wave6Property* out = reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x01234000u));

  assert(app_property_list_get_property_alt_006a1de0(&list, 20, &out));
  assert(out == &entries[1].property);
  out = reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x01234000u));
  assert(app_property_list_get_property_006a2530(&list, 20, &out));
  assert(out == &entries[1].property);
  assert(app_property_list_has_property_006a2470(&list, 20));
  assert(app_property_list_get_property_object_006a24d0(&list, 20) ==
         &entries[1].property);

  Wave6Property* const unchanged = reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x01234000u));
  out = unchanged;
  assert(!app_property_list_get_property_alt_006a1de0(&list, 15, &out));
  assert(out == unchanged);
  out = unchanged;
  assert(!app_property_list_get_property_006a2530(&list, 25, &out));
  assert(out == unchanged);
  assert(!app_property_list_has_property_006a2470(&list, 25));
  assert(app_property_list_get_property_object_006a24d0(&list, 25) ==
         missing_property());
  assert(reinterpret_cast<std::uintptr_t>(
             app_property_list_get_property_object_006a24d0(&list, 25)) ==
         0x016027d0u);

  list.entries_begin_18 = entries.data();
  list.entries_end_1c = entries.data();
  out = unchanged;
  assert(!app_property_list_get_property_alt_006a1de0(&list, 20, &out));
  assert(out == unchanged);
  assert(!app_property_list_has_property_006a2470(&list, 20));
  assert(app_property_list_get_property_object_006a24d0(&list, 20) ==
         missing_property());
}

void test_parent_dispatch() {
  Wave6PropertyListVtable vtable = make_vtable();
  Wave6PropertyList list{};
  Wave6PropertyList parent{};
  Wave6Property returned_property{};
  parent.vtable = &vtable;
  list.parent_30 = &parent;
  parent_receiver = &parent;
  parent_property_id = 15;
  parent_property = &returned_property;
  parent_writes_output = true;
  parent_query_result = true;

  Wave6Property* out = reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x01234000u));
  trace = Trace{};
  assert(app_property_list_has_property_006a2470(&list, 15));
  assert(app_property_list_get_property_alt_006a1de0(&list, 15, &out));
  assert(out == &returned_property);
  out = nullptr;
  assert(app_property_list_get_property_006a2530(&list, 15, &out));
  assert(out == &returned_property);
  assert(app_property_list_get_property_object_006a24d0(&list, 15) ==
         &returned_property);
  assert(trace.events == std::vector<int>{10, 11, 12, 13});

  parent_query_result = false;
  Wave6Property* const unchanged = reinterpret_cast<Wave6Property*>(
      static_cast<std::uintptr_t>(0x01234000u));
  out = unchanged;
  trace = Trace{};
  assert(!app_property_list_get_property_alt_006a1de0(&list, 15, &out));
  assert(out == &returned_property);
  out = unchanged;
  assert(!app_property_list_get_property_006a2530(&list, 15, &out));
  assert(out == &returned_property);
  assert(!app_property_list_has_property_006a2470(&list, 15));
  assert(app_property_list_get_property_object_006a24d0(&list, 15) ==
         missing_property());
  assert(trace.events == std::vector<int>{11, 12, 10, 13});
}

void test_null_receiver_is_unguarded() {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    Wave6Property* out = nullptr;
    const bool result =
        app_property_list_get_property_006a2530(nullptr, 0, &out);
    _exit(result ? 2 : 3);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void run() {
  test_copy_all_properties_from();
  test_add_all_properties_from();
  test_write_success_and_payload_delegation();
  test_write_failure_short_circuit();
  test_local_lookup_and_sentinel();
  test_parent_dispatch();
  test_null_receiver_is_unguarded();
}

#undef WAVE6_TEST_THISCALL

}

}

int main() { openspore::reconstruction::pkg_property_list_wave6::run(); }
