#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 engine-runtime reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define W6_CDECL __cdecl
#define W6_THISCALL __thiscall
#else
#define W6_CDECL __attribute__((cdecl))
#define W6_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_engine_runtime {

static_assert(sizeof(void*) == 4, "wave6 engine-runtime pointers are 32-bit");
static_assert(sizeof(std::uint16_t) == 2,
              "wave6 engine-runtime UTF-16 units are 16-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "wave6 engine-runtime words are 32-bit");

struct OpaqueWave6ConfigManager {
  std::uint32_t opaque_word = 0;
};

extern OpaqueWave6ConfigManager* g_wave6_config_manager_015fd89c;

extern "C" OpaqueWave6ConfigManager* W6_CDECL app_config_manager_get_0067dcf0();

struct OpaqueWave6AppService {
  std::array<std::uint8_t, 0x20> opaque{};
};

struct OpaqueWave6AppSystem {
  std::array<std::uint8_t, 0x16c> opaque_prefix_000{};
  std::uint32_t service_gate_16c = 0;
  std::array<std::uint8_t, 2> opaque_170{};
  std::uint8_t lifecycle_state_172 = 0;
  std::array<std::uint8_t, 5> opaque_173{};
};

static_assert(offsetof(OpaqueWave6AppSystem, service_gate_16c) == 0x16c,
              "wave6 app-system service gate offset");
static_assert(offsetof(OpaqueWave6AppSystem, lifecycle_state_172) == 0x172,
              "wave6 app-system lifecycle state offset");
static_assert(sizeof(OpaqueWave6AppSystem) == 0x178,
              "wave6 app-system observed extent");

struct Wave6AppLifecyclePorts {
  using GetAppSystem = OpaqueWave6AppService*(W6_CDECL*)();
  using InvokeSlot18 = std::uint32_t(W6_THISCALL*)(OpaqueWave6AppService*,
                                                   std::uint32_t, std::uint32_t,
                                                   std::uint32_t,
                                                   std::uint32_t);

  GetAppSystem get_app_system_0067dcc0 = nullptr;
  InvokeSlot18 invoke_slot_18 = nullptr;
};

extern Wave6AppLifecyclePorts* g_wave6_app_lifecycle_ports;

extern "C" std::uint32_t W6_THISCALL
app_system_service_gate_dispatch_007e5f30(OpaqueWave6AppSystem* system);

struct OpaqueWave6WideString {
  std::uint16_t* begin = nullptr;
  std::uint16_t* end = nullptr;
  std::uint16_t* capacity = nullptr;
};

static_assert(sizeof(OpaqueWave6WideString) == 12,
              "wave6 wide-string carrier is three pointers");
static_assert(offsetof(OpaqueWave6WideString, begin) == 0,
              "wave6 wide-string begin offset");
static_assert(offsetof(OpaqueWave6WideString, end) == 4,
              "wave6 wide-string end offset");
static_assert(offsetof(OpaqueWave6WideString, capacity) == 8,
              "wave6 wide-string capacity offset");

struct OpaqueWave6PluginRegistration {
  std::array<std::uint8_t, 0x138> opaque_prefix_000{};
  OpaqueWave6WideString first_command_line_copy_138;
  std::array<std::uint8_t, 4> opaque_144{};
  OpaqueWave6WideString second_command_line_copy_148;
};

static_assert(offsetof(OpaqueWave6PluginRegistration,
                       first_command_line_copy_138) == 0x138,
              "wave6 first command-line copy offset");
static_assert(offsetof(OpaqueWave6PluginRegistration,
                       second_command_line_copy_148) == 0x148,
              "wave6 second command-line copy offset");
static_assert(sizeof(OpaqueWave6PluginRegistration) == 0x154,
              "wave6 plugin-registration observed extent");

struct Wave6WideStringPorts {
  using Append00423650 = void(W6_THISCALL*)(OpaqueWave6WideString*,
                                            const std::uint16_t*,
                                            const std::uint16_t*);
  using Append004f6510 = void(W6_THISCALL*)(OpaqueWave6WideString*,
                                            std::uint16_t);

  Append00423650 append_00423650 = nullptr;
  Append004f6510 append_004f6510 = nullptr;
};

extern Wave6WideStringPorts* g_wave6_wide_string_ports;

extern "C" void W6_THISCALL app_system_initialize_plugins_007e93d0(
    OpaqueWave6PluginRegistration* registration,
    const std::uint16_t* command_line,
    const std::uint16_t* second_command_line);

}

#undef W6_CDECL
#undef W6_THISCALL
