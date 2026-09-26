#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "app_lifecycle_wave7.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave7 {
namespace {

std::vector<std::string>* events = nullptr;
OpaqueAppSystem* observed_hook_system = nullptr;
int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* name) { events->push_back(name); }

std::uint8_t TEST_THISCALL hook_windows(OpaqueAppSystem* system) {
  observed_hook_system = system;
  record("hook_windows_00929bd0");
  return 1u;
}

OpaqueWord layer_manager_0067ca90() {
  record("0067ca90");
  return 0x1001u;
}

OpaqueWord app_system_0067dcc0() {
  record("0067dcc0");
  return 0x1002u;
}

OpaqueWord service_0067caa0() {
  record("0067caa0");
  return 0x1003u;
}

OpaqueWord renderer_0067dd10() {
  record("0067dd10");
  return 0x1004u;
}

OpaqueWord lighting_0067dd50() {
  record("0067dd50");
  return 0x1005u;
}

OpaqueWord shadow_world_0067dd80() {
  record("0067dd80");
  return 0x1006u;
}

OpaqueWord effects_0067dd90() {
  record("0067dd90");
  return 0x1007u;
}

OpaqueWord service_0067ddd0() {
  record("0067ddd0");
  return 0x1008u;
}

OpaqueWord service_0067cb20() {
  record("0067cb20");
  return 0x1009u;
}

OpaqueWord object_template_db_0067cb00() {
  record("0067cb00");
  return 0x100au;
}

OpaqueWord service_0067de30() {
  record("0067de30");
  return 0x100bu;
}

OpaqueWord service_0067ddb0() {
  record("0067ddb0");
  return 0x100cu;
}

OpaqueWord service_0067cb50() {
  record("0067cb50");
  return 0x100du;
}

OpaqueWord service_0067cb60() {
  record("0067cb60");
  return 0x100eu;
}

OpaqueWord service_0067cb70() {
  record("0067cb70");
  return 0x100fu;
}

OpaqueWord service_0067cb80() {
  record("0067cb80");
  return 0x1010u;
}

EffectCollectionPorts make_effect_ports() {
  EffectCollectionPorts ports{};
  ports.layer_manager_0067ca90 = layer_manager_0067ca90;
  ports.app_system_0067dcc0 = app_system_0067dcc0;
  ports.service_0067caa0 = service_0067caa0;
  ports.renderer_0067dd10 = renderer_0067dd10;
  ports.lighting_0067dd50 = lighting_0067dd50;
  ports.shadow_world_0067dd80 = shadow_world_0067dd80;
  ports.effects_0067dd90 = effects_0067dd90;
  ports.service_0067ddd0 = service_0067ddd0;
  ports.service_0067cb20 = service_0067cb20;
  ports.object_template_db_0067cb00 = object_template_db_0067cb00;
  ports.service_0067de30 = service_0067de30;
  ports.service_0067ddb0 = service_0067ddb0;
  ports.service_0067cb50 = service_0067cb50;
  ports.service_0067cb60 = service_0067cb60;
  ports.service_0067cb70 = service_0067cb70;
  ports.service_0067cb80 = service_0067cb80;
  return ports;
}

void reset() {
  events->clear();
  observed_hook_system = nullptr;
  g_app_lifecycle_ports = {};
  g_app_lifecycle_ports.hook_windows_00929bd0 = hook_windows;
  g_effect_collection_ports = make_effect_ports();
}

#if defined(_MSC_VER)
std::uint8_t call_set_effect_with_live_stack_shape(const char* instance_ids,
                                                   OpaqueWord* group_ids) {
  return app_cAppSystem_set_effect_collection_ids_007e6100(instance_ids,
                                                           group_ids);
}
#else
std::uint8_t call_set_effect_with_live_stack_shape(const char* instance_ids,
                                                   OpaqueWord* group_ids) {
  struct CallArguments {
    const char* instance_ids;
    OpaqueWord* group_ids;
  };
  CallArguments arguments{instance_ids, group_ids};
  std::uint32_t result = 0;
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "movl %%esp, %%ebx\n\t"
      "andl $-16, %%esp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %[arguments]\n\t"
      "movl (%%esp), %%edx\n\t"
      "pushl 4(%%edx)\n\t"
      "pushl 0(%%edx)\n\t"
      "call app_cAppSystem_set_effect_collection_ids_007e6100\n\t"
      "movzbl %%al, %[result]\n\t"
      "addl $8, %%esp\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebx, %%esp\n\t"
      "popl %%ebx\n\t"
      : [result] "=&r"(result)
      : [arguments] "r"(&arguments)
      : "eax", "ebx", "ecx", "edx", "cc", "memory");
  return static_cast<std::uint8_t>(result);
}
#endif

#if defined(_MSC_VER)
std::uint32_t call_func88h_with_initial_eax(OpaqueAppSystem* system,
                                            std::int32_t index,
                                            std::uint8_t enabled,
                                            std::uint32_t initial_eax) {
  static_cast<void>(initial_eax);
  return app_cAppSystem_func88h_00a6c940(system, index, enabled);
}
#else
std::uint32_t call_func88h_with_initial_eax(OpaqueAppSystem* system,
                                            std::int32_t index,
                                            std::uint8_t enabled,
                                            std::uint32_t initial_eax) {
  using Function = std::uint32_t(TEST_THISCALL*)(OpaqueAppSystem*, std::int32_t,
                                                 std::uint8_t);
  struct CallArguments {
    OpaqueAppSystem* system;
    std::int32_t index;
    std::uint32_t enabled;
    std::uint32_t initial_eax;
    Function target;
    std::uint32_t result;
  };
  volatile CallArguments arguments{
      system, index, enabled, initial_eax, app_cAppSystem_func88h_00a6c940, 0u};
  __asm__ volatile(
      "movl %[arguments], %%ebx\n\t"
      "movl 0(%%ebx), %%ecx\n\t"
      "movl 12(%%ebx), %%eax\n\t"
      "pushl 8(%%ebx)\n\t"
      "pushl 4(%%ebx)\n\t"
      "call *16(%%ebx)\n\t"
      "movl %%eax, 20(%%ebx)\n\t"
      :
      : [arguments] "r"(&arguments)
      : "eax", "ebx", "ecx", "edx", "cc", "memory");
  return arguments.result;
}
#endif

void test_hook_windows() {
  reset();
  OpaqueAppSystem system{};
  check(app_cAppSystem_hook_windows_007e6080(&system) == 1u);
  check(observed_hook_system == &system);
  check(events->size() == 1u);
  check(events->front() == "hook_windows_00929bd0");
}

void test_set_effect_collection_ids() {
  reset();
  std::array<OpaqueWord, 16> group_ids{};
  group_ids.fill(0xdeadbeefu);
  check(call_set_effect_with_live_stack_shape("GetSharedLibraryVersion",
                                              group_ids.data()) == 1u);
  check(group_ids[0] == 0x0153f864u);
  check(group_ids[1] == 0xdeadbeefu);
  check(events->empty());

  reset();
  group_ids.fill(0xdeadbeefu);
  check(call_set_effect_with_live_stack_shape("GetAppPluginServices",
                                              group_ids.data()) == 1u);
  const std::array<OpaqueWord, 16> expected = {
      0x1001u, 0x1002u, 0x1003u, 0x1004u, 0x1005u, 0x1006u, 0x1007u, 0x1008u,
      0x1009u, 0x100au, 0x100fu, 0x100bu, 0x100cu, 0x100du, 0x100eu, 0x1010u};
  for (std::size_t index = 0; index < group_ids.size(); ++index) {
    check(group_ids[index] == expected[index]);
  }
  const std::array<const char*, 16> names = {
      "0067ca90", "0067dcc0", "0067caa0", "0067dd10", "0067dd50", "0067dd80",
      "0067dd90", "0067ddd0", "0067cb20", "0067cb00", "0067de30", "0067ddb0",
      "0067cb50", "0067cb60", "0067cb70", "0067cb80"};
  check(events->size() == names.size());
  if (events->size() == names.size()) {
    for (std::size_t index = 0; index < names.size(); ++index) {
      check((*events)[index] == names[index]);
    }
  }

  reset();
  group_ids.fill(0xdeadbeefu);
  check(call_set_effect_with_live_stack_shape("Unknown", group_ids.data()) ==
        0u);
  for (const OpaqueWord value : group_ids) {
    check(value == 0xdeadbeefu);
  }
  check(events->empty());
}

void test_func88h() {
  reset();
  OpaqueAppSystem system{};
  system.field_68 = 0x80000000u;
  check(app_cAppSystem_func88h_00a6c940(&system, 31, 1) == 0x80000000u);
  check(system.field_68 == 0x80000000u);

  system.field_68 = 0xffffffffu;
  check(app_cAppSystem_func88h_00a6c940(&system, 0, 0) == 0xfffffffeu);
  check(system.field_68 == 0xfffffffeu);

  system.field_68 = 0x12345678u;
#if defined(_MSC_VER)
  check(call_func88h_with_initial_eax(&system, -1, 1, 0xabcdef01u) == 0u);
  check(system.field_68 == 0x92345678u);
#else
  check(call_func88h_with_initial_eax(&system, -1, 1, 0xabcdef01u) ==
        0x80000000u);
  check(system.field_68 == 0x92345678u);
  system.field_68 = 0x92345678u;
  check(call_func88h_with_initial_eax(&system, -1, 0, 0xabcdef01u) ==
        0x7fffffffu);
  check(system.field_68 == 0x12345678u);
#endif

  system.field_68 = 0x87654321u;
#if defined(_MSC_VER)
  static_cast<void>(call_func88h_with_initial_eax(&system, 32, 1, 0x13572468u));
#else
  check(call_func88h_with_initial_eax(&system, 32, 1, 0x13572468u) ==
        0x13572468u);
#endif
  check(system.field_68 == 0x87654321u);
}

int run_tests() {
  std::vector<std::string> test_events;
  events = &test_events;
  test_hook_windows();
  test_set_effect_collection_ids();
  test_func88h();
  events = nullptr;
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_app_lifecycle_wave7::run_tests();
}

#undef TEST_CDECL
#undef TEST_THISCALL
