#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-app-lifecycle-wave7 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_LIFECYCLE_THISCALL __thiscall
#define PKG_APP_LIFECYCLE_CDECL __cdecl
#else
#define PKG_APP_LIFECYCLE_THISCALL __attribute__((thiscall))
#define PKG_APP_LIFECYCLE_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave7 {

using OpaqueWord = std::uint32_t;

struct alignas(4) OpaqueAppSystem {
  std::uint8_t opaque[0x68]{};
  OpaqueWord field_68;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueAppSystem) == 0x6c,
              "app system covers the observed field offset");
static_assert(offsetof(OpaqueAppSystem, field_68) == 0x68,
              "app system bit field offset");

using HookWindowsPort = std::uint8_t(PKG_APP_LIFECYCLE_THISCALL*)(
    OpaqueAppSystem*);
using EffectServicePort = OpaqueWord(PKG_APP_LIFECYCLE_CDECL*)();

struct AppLifecyclePorts {
  HookWindowsPort hook_windows_00929bd0 = nullptr;
};

struct EffectCollectionPorts {
  EffectServicePort layer_manager_0067ca90 = nullptr;
  EffectServicePort app_system_0067dcc0 = nullptr;
  EffectServicePort service_0067caa0 = nullptr;
  EffectServicePort renderer_0067dd10 = nullptr;
  EffectServicePort lighting_0067dd50 = nullptr;
  EffectServicePort shadow_world_0067dd80 = nullptr;
  EffectServicePort effects_0067dd90 = nullptr;
  EffectServicePort service_0067ddd0 = nullptr;
  EffectServicePort service_0067cb20 = nullptr;
  EffectServicePort object_template_db_0067cb00 = nullptr;
  EffectServicePort service_0067de30 = nullptr;
  EffectServicePort service_0067ddb0 = nullptr;
  EffectServicePort service_0067cb50 = nullptr;
  EffectServicePort service_0067cb60 = nullptr;
  EffectServicePort service_0067cb70 = nullptr;
  EffectServicePort service_0067cb80 = nullptr;
};

extern AppLifecyclePorts g_app_lifecycle_ports;
extern EffectCollectionPorts g_effect_collection_ports;

extern "C" std::uint8_t PKG_APP_LIFECYCLE_THISCALL
app_cAppSystem_hook_windows_007e6080(OpaqueAppSystem* system);

extern "C" std::uint8_t PKG_APP_LIFECYCLE_CDECL
app_cAppSystem_set_effect_collection_ids_007e6100(const char* instance_ids,
                                                   OpaqueWord* group_ids);

extern "C" std::uint32_t PKG_APP_LIFECYCLE_THISCALL
app_cAppSystem_func88h_00a6c940(OpaqueAppSystem* system, std::int32_t index,
                                std::uint8_t enabled);

}

#undef PKG_APP_LIFECYCLE_CDECL
#undef PKG_APP_LIFECYCLE_THISCALL
