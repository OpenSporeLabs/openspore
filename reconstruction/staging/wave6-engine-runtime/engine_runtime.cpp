#include "engine_runtime.hpp"

#if defined(_MSC_VER)
#define W6_CDECL __cdecl
#define W6_THISCALL __thiscall
#else
#define W6_CDECL __attribute__((cdecl))
#define W6_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_engine_runtime {

OpaqueWave6ConfigManager* g_wave6_config_manager_015fd89c = nullptr;
Wave6AppLifecyclePorts* g_wave6_app_lifecycle_ports = nullptr;
Wave6WideStringPorts* g_wave6_wide_string_ports = nullptr;

namespace {

const std::uint16_t* wide_string_end(const std::uint16_t* value) {
  const std::uint16_t* cursor = value;
  while (*cursor != 0) {
    cursor += 1;
  }
  return cursor;
}

}

extern "C" OpaqueWave6ConfigManager* W6_CDECL
app_config_manager_get_0067dcf0() {
  return g_wave6_config_manager_015fd89c;
}

extern "C" std::uint32_t W6_THISCALL
app_system_service_gate_dispatch_007e5f30(OpaqueWave6AppSystem* system) {
  std::uint32_t incoming_eax;
  __asm__ __volatile__("movl %%eax, %0" : "=r"(incoming_eax));
  const bool dispatch_service = system->service_gate_16c != 0;
  system->lifecycle_state_172 = 1;
  if (!dispatch_service) {
    return incoming_eax;
  }
  Wave6AppLifecyclePorts& ports = *g_wave6_app_lifecycle_ports;
  OpaqueWave6AppService* service = ports.get_app_system_0067dcc0();
  return ports.invoke_slot_18(service, 0x0462dde3U, 0U, 0U, 0U);
}

extern "C" void W6_THISCALL app_system_initialize_plugins_007e93d0(
    OpaqueWave6PluginRegistration* registration,
    const std::uint16_t* command_line) {
  Wave6WideStringPorts& ports = *g_wave6_wide_string_ports;
  const std::uint16_t* end = wide_string_end(command_line);
  ports.assign_00423650(&registration->first_command_line_copy_138,
                        command_line, end);
  ports.append_004f6510(&registration->first_command_line_copy_138, 0x005cU);
  end = wide_string_end(command_line);
  ports.assign_00423650(&registration->second_command_line_copy_148,
                        command_line, end);
  ports.append_004f6510(&registration->second_command_line_copy_148, 0x005cU);
}

}

#undef W6_CDECL
#undef W6_THISCALL
