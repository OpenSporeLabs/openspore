#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "mode_on_exit.hpp"

namespace {

using openspore::reconstruction::pkg08_cell_mode::cell_mode_on_exit_00e7fc00;
using openspore::reconstruction::pkg08_cell_mode::g_mode_on_exit_globals;
using openspore::reconstruction::pkg08_cell_mode::g_mode_on_exit_ports;
using openspore::reconstruction::pkg08_cell_mode::NativePorts;
using openspore::reconstruction::pkg08_cell_mode::OpaqueGlobalViews;
using openspore::reconstruction::pkg08_cell_mode::OpaqueIterator;
using openspore::reconstruction::pkg08_cell_mode::OpaqueMode;
using openspore::reconstruction::pkg08_cell_mode::OpaqueRecord;
using openspore::reconstruction::pkg08_cell_mode::OpaqueService;

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

std::uint32_t bits(float value) {
  std::uint32_t result;
  std::memcpy(&result, &value, sizeof(result));
  return result;
}

std::uintptr_t stack_pointer() {
  std::uintptr_t result;
  __asm__("movl %%esp, %0" : "=r"(result));
  return result;
}

enum class Call {
  address_00e53580,
  address_00e31100,
  address_00b72230,
  address_00e7e130,
  address_00b72110,
  address_0067ddd0,
  vtable_00000098,
  address_00e64a00,
  address_00e82d40,
};

struct Event {
  Call call = Call::address_00e53580;
  OpaqueMode* mode = nullptr;
  OpaqueRecord* record = nullptr;
  OpaqueService* service = nullptr;
  OpaqueIterator iterator = 0;
  float first = 0.0F;
  std::uint32_t second = 0;
  std::uint32_t third = 0;
  std::uint32_t word0 = 0;
  std::uint32_t word1 = 0;
};

struct GlobalMapping {
  std::uint32_t destination;
  std::uint32_t source;
  std::uint32_t width;
};

constexpr std::array<GlobalMapping, 8> global_mappings{{
    {0x01550adcu, 0x016b3bf0u, 4},
    {0x01550af0u, 0x016b3becu, 4},
    {0x01550a84u, 0x016b3bf8u, 4},
    {0x01550aecu, 0x016b3be8u, 4},
    {0x01550ae0u, 0x016b3be4u, 4},
    {0x0166c004u, 0x016b3bfcu, 4},
    {0x01550ad8u, 0x016b3bf4u, 4},
    {0x01550ae4u, 0x016b3be0u, 4},
}};

struct SourceGlobals {
  float value_016b3be0 = 1.0F;
  float value_016b3be4 = -2.0F;
  float value_016b3be8 = 3.0F;
  float value_016b3bec = 4.0F;
  float value_016b3bf0 = 5.0F;
  std::uint32_t value_016b3bf4 = 0x44444444U;
  std::uint32_t value_016b3bf8 = 0x11111111U;
  std::uint32_t value_016b3bfc = 0x22222222U;
};

struct Fixture {
  std::array<std::byte, 0x58> entry_mode_storage{};
  std::array<std::byte, 0x58> first_owner_storage{};
  std::array<std::byte, 0x58> second_owner_storage{};
  std::array<std::byte, 0x40> record_storage[3]{};
  std::array<std::byte, 4> service_storage{};
  SourceGlobals source{};
  std::array<std::uint32_t, 8> destination_words{
      0xc1400000U, 0xc1800000U, 0xc1200000U, 0xc1700000U,
      0xc1500000U, 0x33333333U, 0xc1300000U, 0xc1600000U,
  };
  std::vector<Event> events;
  std::size_t record_count = 0;
  bool owner_swapped = false;
};

OpaqueMode* as_mode(void* address) {
  return reinterpret_cast<OpaqueMode*>(address);
}

OpaqueRecord* as_record(void* address) {
  return reinterpret_cast<OpaqueRecord*>(address);
}

OpaqueService* as_service(void* address) {
  return reinterpret_cast<OpaqueService*>(address);
}

void add_event(Fixture& fixture, Call call) {
  fixture.events.push_back(Event{call});
}

Fixture* current_fixture = nullptr;

void helper_00e53580() {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::address_00e53580);
  fixture.source.value_016b3be0 += 1.0F;
  fixture.source.value_016b3be4 += 1.0F;
  fixture.source.value_016b3be8 += 1.0F;
  fixture.source.value_016b3bec += 1.0F;
  fixture.source.value_016b3bf0 += 1.0F;
  fixture.source.value_016b3bf4 += 0x01010101U;
  fixture.source.value_016b3bf8 += 0x01010101U;
  fixture.source.value_016b3bfc += 0x02020202U;
}

OpaqueIterator iterator_begin_00e31100() {
  add_event(*current_fixture, Call::address_00e31100);
  return 0;
}

OpaqueRecord* iterator_access_00b72230(OpaqueMode* mode,
                                       OpaqueIterator* iterator) {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::address_00b72230);
  Event& event = fixture.events.back();
  event.mode = mode;
  event.iterator = *iterator;
  const std::size_t index = static_cast<std::size_t>(*iterator);
  if (index < fixture.record_count) {
    ++(*iterator);
    return as_record(fixture.record_storage[index].data());
  }
  return nullptr;
}

void record_00e7e130(OpaqueMode* mode, OpaqueRecord* record, float first,
                     std::uint32_t second, std::uint32_t third) {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::address_00e7e130);
  Event& event = fixture.events.back();
  event.mode = mode;
  event.record = record;
  event.first = first;
  event.second = second;
  event.third = third;
  if (!fixture.owner_swapped) {
    g_mode_on_exit_globals.cell_game_016b3c04 =
        fixture.second_owner_storage.data();
    fixture.owner_swapped = true;
  }
}

void iterator_cleanup_00b72110(OpaqueMode* mode) {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::address_00b72110);
  fixture.events.back().mode = mode;
}

OpaqueService* service_acquire_0067ddd0() {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::address_0067ddd0);
  return as_service(fixture.service_storage.data());
}

void service_vtable_0098(OpaqueService* service, std::uint32_t first,
                         std::uint32_t second) {
  Fixture& fixture = *current_fixture;
  add_event(fixture, Call::vtable_00000098);
  Event& event = fixture.events.back();
  event.service = service;
  event.word0 = first;
  event.word1 = second;
}

void helper_00e64a00() { add_event(*current_fixture, Call::address_00e64a00); }

void helper_00e82d40() { add_event(*current_fixture, Call::address_00e82d40); }

NativePorts make_ports() {
  NativePorts ports{};
  ports.helper_00e53580 = helper_00e53580;
  ports.iterator_begin_00e31100 = iterator_begin_00e31100;
  ports.iterator_access_00b72230 = iterator_access_00b72230;
  ports.record_00e7e130 = record_00e7e130;
  ports.iterator_cleanup_00b72110 = iterator_cleanup_00b72110;
  ports.service_acquire_0067ddd0 = service_acquire_0067ddd0;
  ports.service_vtable_0098 = service_vtable_0098;
  ports.helper_00e64a00 = helper_00e64a00;
  ports.helper_00e82d40 = helper_00e82d40;
  return ports;
}

void initialize(Fixture& fixture, std::size_t record_count) {
  current_fixture = &fixture;
  fixture.record_count = record_count;
  fixture.owner_swapped = false;
  fixture.events.clear();
  g_mode_on_exit_globals = OpaqueGlobalViews{};
  g_mode_on_exit_globals.cell_game_016b3c04 =
      fixture.first_owner_storage.data();
  g_mode_on_exit_globals.source_016b3be0 = &fixture.source.value_016b3be0;
  g_mode_on_exit_globals.source_016b3be4 = &fixture.source.value_016b3be4;
  g_mode_on_exit_globals.source_016b3be8 = &fixture.source.value_016b3be8;
  g_mode_on_exit_globals.source_016b3bec = &fixture.source.value_016b3bec;
  g_mode_on_exit_globals.source_016b3bf0 = &fixture.source.value_016b3bf0;
  g_mode_on_exit_globals.source_016b3bf4 = &fixture.source.value_016b3bf4;
  g_mode_on_exit_globals.source_016b3bf8 = &fixture.source.value_016b3bf8;
  g_mode_on_exit_globals.source_016b3bfc = &fixture.source.value_016b3bfc;
  g_mode_on_exit_globals.destination_01550adc =
      reinterpret_cast<float*>(fixture.destination_words.data());
  g_mode_on_exit_globals.destination_01550af0 =
      reinterpret_cast<float*>(fixture.destination_words.data() + 1);
  g_mode_on_exit_globals.destination_01550a84 =
      fixture.destination_words.data() + 2;
  g_mode_on_exit_globals.destination_01550aec =
      reinterpret_cast<float*>(fixture.destination_words.data() + 3);
  g_mode_on_exit_globals.destination_01550ae0 =
      reinterpret_cast<float*>(fixture.destination_words.data() + 4);
  g_mode_on_exit_globals.destination_0166c004 =
      fixture.destination_words.data() + 5;
  g_mode_on_exit_globals.destination_01550ad8 =
      fixture.destination_words.data() + 6;
  g_mode_on_exit_globals.destination_01550ae4 =
      reinterpret_cast<float*>(fixture.destination_words.data() + 7);
  g_mode_on_exit_ports = make_ports();
}

std::array<std::uint32_t, 8> expected_destination_words() {
  SourceGlobals source{};
  source.value_016b3be0 += 1.0F;
  source.value_016b3be4 += 1.0F;
  source.value_016b3be8 += 1.0F;
  source.value_016b3bec += 1.0F;
  source.value_016b3bf0 += 1.0F;
  source.value_016b3bf4 += 0x01010101U;
  source.value_016b3bf8 += 0x01010101U;
  source.value_016b3bfc += 0x02020202U;
  return {
      bits(source.value_016b3bf0), bits(source.value_016b3bec),
      source.value_016b3bf8,       bits(source.value_016b3be8),
      bits(source.value_016b3be4), source.value_016b3bfc,
      source.value_016b3bf4,       bits(source.value_016b3be0),
  };
}

void check_raw_destination_words(const Fixture& fixture,
                                 const std::array<std::uint32_t, 8>& before) {
  const std::array<std::uint32_t, 8> expected = expected_destination_words();
  check(fixture.destination_words != before);
  for (std::size_t index = 0; index < fixture.destination_words.size();
       ++index) {
    check(fixture.destination_words[index] == expected[index]);
    check(global_mappings[index].width == 4);
  }
}

bool same_event(const Event& first, const Event& second) {
  return first.call == second.call && first.mode == second.mode &&
         first.record == second.record && first.service == second.service &&
         first.iterator == second.iterator &&
         bits(first.first) == bits(second.first) &&
         first.second == second.second && first.third == second.third &&
         first.word0 == second.word0 && first.word1 == second.word1;
}

void check_events(const Fixture& fixture, const std::vector<Event>& expected) {
  check(fixture.events.size() == expected.size());
  const std::size_t count = fixture.events.size() < expected.size()
                                ? fixture.events.size()
                                : expected.size();
  for (std::size_t index = 0; index < count; ++index) {
    check(same_event(fixture.events[index], expected[index]));
  }
}

std::vector<Event> expected_events(Fixture& fixture, std::size_t record_count) {
  OpaqueMode* first_owner = as_mode(fixture.first_owner_storage.data() + 0x54);
  OpaqueMode* second_owner =
      as_mode(fixture.second_owner_storage.data() + 0x54);
  OpaqueService* service = as_service(fixture.service_storage.data());
  std::vector<Event> expected;
  Event event{};

  expected.push_back(Event{Call::address_00e53580});
  expected.push_back(Event{Call::address_00e31100});
  event = Event{Call::address_00b72230};
  event.mode = first_owner;
  event.iterator = 0;
  expected.push_back(event);
  for (std::size_t index = 0; index < record_count; ++index) {
    OpaqueMode* owner = index == 0 ? first_owner : second_owner;
    event = Event{Call::address_00e7e130};
    event.mode = owner;
    event.record = as_record(fixture.record_storage[index].data());
    event.first = 0.0F;
    event.second = 0;
    event.third = 1;
    expected.push_back(event);
    event = Event{Call::address_00b72230};
    event.mode = second_owner;
    event.iterator = static_cast<OpaqueIterator>(index + 1);
    expected.push_back(event);
  }

  event = Event{Call::address_00b72110};
  event.mode = record_count == 0 ? first_owner : second_owner;
  expected.push_back(event);
  expected.push_back(Event{Call::address_0067ddd0});
  event = Event{Call::vtable_00000098};
  event.service = service;
  event.word0 = 7;
  event.word1 = 0;
  expected.push_back(event);
  expected.push_back(Event{Call::address_00e64a00});
  expected.push_back(Event{Call::address_00e82d40});
  return expected;
}

void run_case(std::size_t record_count) {
  Fixture fixture{};
  initialize(fixture, record_count);
  const std::array<std::uint32_t, 8> before = fixture.destination_words;
  const std::uintptr_t before_stack = stack_pointer();

  cell_mode_on_exit_00e7fc00(as_mode(fixture.entry_mode_storage.data()));

  const std::uintptr_t after_stack = stack_pointer();
  check(before_stack == after_stack);
  check_raw_destination_words(fixture, before);
  check_events(fixture, expected_events(fixture, record_count));
}

}

int main() {
  run_case(0);
  run_case(1);
  run_case(3);
  return failures == 0 ? 0 : 1;
}
