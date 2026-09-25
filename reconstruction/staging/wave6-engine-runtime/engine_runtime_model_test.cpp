#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "engine_runtime.hpp"

namespace {

using openspore::reconstruction::wave6_engine_runtime::
    g_wave6_app_lifecycle_ports;
using openspore::reconstruction::wave6_engine_runtime::
    g_wave6_config_manager_015fd89c;
using openspore::reconstruction::wave6_engine_runtime::
    g_wave6_wide_string_ports;
using openspore::reconstruction::wave6_engine_runtime::OpaqueWave6AppService;
using openspore::reconstruction::wave6_engine_runtime::OpaqueWave6AppSystem;
using openspore::reconstruction::wave6_engine_runtime::OpaqueWave6ConfigManager;
using openspore::reconstruction::wave6_engine_runtime::
    OpaqueWave6PluginRegistration;
using openspore::reconstruction::wave6_engine_runtime::OpaqueWave6WideString;
using openspore::reconstruction::wave6_engine_runtime::Wave6AppLifecyclePorts;
using openspore::reconstruction::wave6_engine_runtime::Wave6WideStringPorts;

#if defined(_MSC_VER)
#define TEST_CDECL __cdecl
#define TEST_THISCALL __thiscall
#else
#define TEST_CDECL __attribute__((cdecl))
#define TEST_THISCALL __attribute__((thiscall))
#endif

int failures = 0;

void check(bool condition, const char* message) {
  static_cast<void>(message);
  if (!condition) {
    ++failures;
  }
}

OpaqueWave6AppService* observed_service = nullptr;
OpaqueWave6AppSystem* observed_system = nullptr;
std::vector<std::uint32_t> lifecycle_arguments;
std::uint8_t lifecycle_state_seen_by_callback = 0xffU;

OpaqueWave6AppService* TEST_CDECL get_app_system_0067dcc0() {
  return observed_service;
}

std::uint32_t TEST_THISCALL invoke_slot_18(OpaqueWave6AppService* service,
                                           std::uint32_t selector,
                                           std::uint32_t first,
                                           std::uint32_t second,
                                           std::uint32_t third) {
  observed_service = service;
  lifecycle_arguments = {selector, first, second, third};
  lifecycle_state_seen_by_callback = observed_system->lifecycle_state_172;
  return 0x89abcdefU;
}

std::vector<std::string> wide_string_trace;
std::vector<std::uint16_t> appended_units;
std::vector<std::size_t> assigned_lengths;
std::vector<OpaqueWave6WideString*> assigned_destinations;
std::vector<const std::uint16_t*> assigned_sources;

void TEST_THISCALL assign_wide_string(OpaqueWave6WideString* destination,
                                      const std::uint16_t* source,
                                      const std::uint16_t* end) {
  const std::string name = destination == nullptr ? "null" : "destination";
  wide_string_trace.emplace_back("assign:" + name);
  assigned_lengths.push_back(static_cast<std::size_t>(end - source));
  assigned_destinations.push_back(destination);
  assigned_sources.push_back(source);
}

void TEST_THISCALL append_wide_string(OpaqueWave6WideString* destination,
                                      std::uint16_t unit) {
  const std::string name = destination == nullptr ? "null" : "destination";
  wide_string_trace.emplace_back("append:" + name);
  appended_units.push_back(unit);
}

void test_config_manager_accessor() {
  OpaqueWave6ConfigManager manager{};
  g_wave6_config_manager_015fd89c = &manager;
  check(openspore::reconstruction::wave6_engine_runtime::
                app_config_manager_get_0067dcf0() == &manager,
        "config accessor returns published pointer");
  g_wave6_config_manager_015fd89c = nullptr;
  check(openspore::reconstruction::wave6_engine_runtime::
                app_config_manager_get_0067dcf0() == nullptr,
        "config accessor preserves null slot");
  g_wave6_config_manager_015fd89c =
      reinterpret_cast<OpaqueWave6ConfigManager*>(0x11111111U);
  check(reinterpret_cast<std::uintptr_t>(
            openspore::reconstruction::wave6_engine_runtime::
                app_config_manager_get_0067dcf0()) == 0x11111111U,
        "config accessor returns unchecked opaque word");
  g_wave6_config_manager_015fd89c = nullptr;
}

void test_lifecycle_gate_and_dispatch() {
  observed_service = nullptr;
  lifecycle_arguments.clear();
  lifecycle_state_seen_by_callback = 0xffU;
  g_wave6_app_lifecycle_ports = nullptr;

  OpaqueWave6AppSystem gated{};
  gated.lifecycle_state_172 = 0;
  openspore::reconstruction::wave6_engine_runtime::
      app_system_service_gate_dispatch_007e5f30(&gated);
  check(gated.lifecycle_state_172 == 1,
        "zero gate still publishes lifecycle state");
  check(observed_service == nullptr, "zero gate performs no service lookup");

  OpaqueWave6AppService service{};
  observed_service = &service;
  Wave6AppLifecyclePorts ports{};
  ports.get_app_system_0067dcc0 = &get_app_system_0067dcc0;
  ports.invoke_slot_18 = &invoke_slot_18;
  g_wave6_app_lifecycle_ports = &ports;

  OpaqueWave6AppSystem dispatching{};
  dispatching.service_gate_16c = 0xffffffffU;
  dispatching.lifecycle_state_172 = 0;
  observed_system = &dispatching;
  lifecycle_state_seen_by_callback = 0xffU;
  const std::uint32_t result = openspore::reconstruction::wave6_engine_runtime::
      app_system_service_gate_dispatch_007e5f30(&dispatching);
  check(result == 0x89abcdefU, "service callback EAX result passes through");
  check(observed_service == &service, "service lookup result reaches slot");
  check(lifecycle_arguments ==
            std::vector<std::uint32_t>({0x0462dde3U, 0U, 0U, 0U}),
        "service slot receives selector and three zero words");
  check(dispatching.lifecycle_state_172 == 1,
        "dispatch path publishes lifecycle state");
  check(lifecycle_state_seen_by_callback == 1,
        "callback observes lifecycle publication before dispatch");
  g_wave6_app_lifecycle_ports = nullptr;
}

void test_plugin_initialization_order() {
  Wave6WideStringPorts ports{};
  ports.assign_00423650 = &assign_wide_string;
  ports.append_004f6510 = &append_wide_string;
  g_wave6_wide_string_ports = &ports;

  std::array<std::uint16_t, 4> command_line = {
      static_cast<std::uint16_t>('c'),
      static_cast<std::uint16_t>('m'),
      static_cast<std::uint16_t>('d'),
      0U,
  };
  OpaqueWave6PluginRegistration registration{};
  wide_string_trace.clear();
  appended_units.clear();
  assigned_lengths.clear();
  assigned_destinations.clear();
  assigned_sources.clear();

  openspore::reconstruction::wave6_engine_runtime::
      app_system_initialize_plugins_007e93d0(&registration,
                                             command_line.data());

  check(wide_string_trace == std::vector<std::string>(
                                 {"assign:destination", "append:destination",
                                  "assign:destination", "append:destination"}),
        "plugin initialization copies and appends in two pairs");
  check(assigned_lengths == std::vector<std::size_t>({3U, 3U}),
        "both assignments receive the source terminator");
  check(appended_units == std::vector<std::uint16_t>({0x005cU, 0x005cU}),
        "both copies append one backslash unit");
  check(assigned_destinations ==
            std::vector<OpaqueWave6WideString*>{
                &registration.first_command_line_copy_138,
                &registration.second_command_line_copy_148},
        "assignments target the first and second observed windows");
  check(assigned_sources ==
            std::vector<const std::uint16_t*>{command_line.data(),
                                              command_line.data()},
        "both assignments receive the same command-line pointer");
  check(offsetof(OpaqueWave6PluginRegistration, first_command_line_copy_138) ==
            0x138U,
        "first destination offset is exact");
  check(offsetof(OpaqueWave6PluginRegistration, second_command_line_copy_148) ==
            0x148U,
        "second destination offset is exact");

  std::array<std::uint16_t, 1> empty_command_line = {0U};
  wide_string_trace.clear();
  appended_units.clear();
  assigned_lengths.clear();
  assigned_destinations.clear();
  assigned_sources.clear();
  openspore::reconstruction::wave6_engine_runtime::
      app_system_initialize_plugins_007e93d0(&registration,
                                             empty_command_line.data());
  check(assigned_lengths == std::vector<std::size_t>({0U, 0U}),
        "empty command line produces two zero-length assignments");
  check(appended_units == std::vector<std::uint16_t>({0x005cU, 0x005cU}),
        "empty command line still appends two separators");
  g_wave6_wide_string_ports = nullptr;
}

}

int main() {
  test_config_manager_accessor();
  test_lifecycle_gate_and_dispatch();
  test_plugin_initialization_order();
  return failures == 0 ? 0 : 1;
}

#undef TEST_CDECL
#undef TEST_THISCALL
