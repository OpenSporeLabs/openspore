#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-10 editor query helpers require an x86-32 target"
#endif

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditor;
struct OpaqueMaterial;
struct OpaquePropertyValue;

struct OpaqueService {
  void* vtable;
};

struct OpaqueMaterialManager {
  void* vtable;
};

struct OpaqueAppRuntime {
  std::uint8_t prefix[0x118];
};

struct OpaqueAppProperties {
  std::uint8_t prefix[0x3c];
  OpaqueAppRuntime* runtime;
};

struct OpaquePreferenceQuery {
  std::uint8_t prefix[0x10];
  std::uint16_t flags;
  std::uint16_t trailing_flags;
};

struct OpaqueEditorQueryContext {
  std::uint8_t prefix_00[0x5c];
  OpaqueEditor* owner;
  std::uint8_t gap_60[0x54];
  std::uint8_t material_registration[0x14];
  std::uint32_t material_mode;
  std::uint32_t state;
  std::uint8_t active;
  std::uint8_t tail[3];
};

static_assert(sizeof(void*) == 4,
              "PKG-10 query helpers require 32-bit pointers");
static_assert(offsetof(OpaquePreferenceQuery, flags) == 0x10,
              "PKG-10 preference query flags offset");
static_assert(offsetof(OpaquePreferenceQuery, trailing_flags) == 0x12,
              "PKG-10 preference query trailing flags offset");
static_assert(sizeof(OpaquePreferenceQuery) == 0x14,
              "PKG-10 preference query size");
static_assert(offsetof(OpaqueEditorQueryContext, owner) == 0x5c,
              "PKG-10 query context owner offset");
static_assert(offsetof(OpaqueEditorQueryContext, material_registration) == 0xb4,
              "PKG-10 query context registration offset");
static_assert(offsetof(OpaqueEditorQueryContext, material_mode) == 0xc8,
              "PKG-10 query context material mode offset");
static_assert(offsetof(OpaqueEditorQueryContext, state) == 0xcc,
              "PKG-10 query context state offset");
static_assert(offsetof(OpaqueEditorQueryContext, active) == 0xd0,
              "PKG-10 query context active offset");
static_assert(sizeof(OpaqueEditorQueryContext) == 0xd4,
              "PKG-10 query context size");

using OpaqueQueryCallback = void(__cdecl*)(std::uint32_t,
                                           OpaquePreferenceQuery*,
                                           std::uint32_t, std::uint32_t,
                                           std::uint32_t, std::uint32_t);
using OpaquePropertySetValueBool = OpaquePreferenceQuery*(
    __thiscall*)(OpaquePreferenceQuery*, OpaquePropertyValue*);
using OpaqueAppSystemGet = OpaqueService*(__cdecl*)();
using OpaqueAppSystemInit = void(__thiscall*)(OpaqueService*, std::uint32_t,
                                              void*, void*);
using OpaqueDebugMessage = void(__cdecl*)(std::uint32_t);
using OpaqueEditorOutput = const std::uint32_t*(__thiscall*)(OpaqueEditor*,
                                                             std::uint32_t*);
using OpaqueEditorApply = void(__thiscall*)(OpaqueEditorQueryContext*,
                                            std::uint32_t, std::uint32_t,
                                            std::uint32_t, std::uint32_t);
using OpaqueTransitionArgs = void(__thiscall*)(OpaqueEditorQueryContext*,
                                               std::uint32_t, std::uint32_t);
using OpaqueTransitionNoArgs = void(__thiscall*)(OpaqueEditorQueryContext*);
using OpaqueTransitionOneArg = void(__thiscall*)(OpaqueEditorQueryContext*,
                                                 std::uint32_t);
using OpaqueServiceLookup =
    OpaqueService*(__thiscall*)(OpaqueEditorQueryContext*, std::uint32_t);
using OpaqueStateDecision = void(__thiscall*)(OpaqueEditorQueryContext*,
                                              std::uint32_t);
using OpaqueRawCall = void(__cdecl*)(std::uint32_t, OpaqueEditorQueryContext*,
                                     std::uint32_t);
using OpaquePortCall = void(__cdecl*)(std::uint32_t);
using OpaqueModeFlag = void(__cdecl*)(std::uint32_t);
using OpaqueMaterialManagerGet = OpaqueMaterialManager*(__cdecl*)();
using OpaqueMaterialSlot30 =
    OpaqueMaterial*(__thiscall*)(OpaqueMaterialManager*, std::uint32_t);
using OpaqueRegisterMaterial = void(__cdecl*)(void*, const void*);
using OpaqueServiceSlot28 = std::uint32_t(__thiscall*)(OpaqueService*);

extern OpaqueQueryCallback pkg10_g_query_callback_0154eb48;
extern OpaquePropertySetValueBool pkg10_g_property_set_value_bool_00422e20;
extern OpaqueAppSystemGet pkg10_g_app_system_get_0067dcc0;
extern OpaqueAppSystemInit pkg10_g_app_system_init_0067dcc0_v14;
extern OpaqueDebugMessage pkg10_g_debug_004a88d0;
extern OpaqueEditorOutput pkg10_g_editor_output_00572190;
extern OpaqueEditorApply pkg10_g_editor_apply_005dca00;
extern OpaqueTransitionArgs pkg10_g_transition_args_005df470;
extern OpaqueTransitionNoArgs pkg10_g_transition_noargs_005dfb40;
extern OpaqueTransitionNoArgs pkg10_g_transition_noargs_005df8d0;
extern OpaqueTransitionOneArg pkg10_g_transition_one_005dc4d0;
extern OpaqueServiceLookup pkg10_g_service_lookup_005dc310;
extern OpaqueStateDecision pkg10_g_state_decision_005dd610;
extern OpaqueTransitionNoArgs pkg10_g_transition_noargs_005dd300;
extern OpaqueTransitionNoArgs pkg10_g_transition_noargs_00572260;
extern OpaqueRawCall pkg10_g_raw_call_0064bc50;
extern OpaquePortCall pkg10_g_port_call_006035d0;
extern OpaqueModeFlag pkg10_g_mode_flag_008098f0;
extern OpaqueMaterialManagerGet pkg10_g_material_manager_get_0067dd30;
extern OpaqueRegisterMaterial pkg10_g_register_material_00809db0;
extern OpaqueAppProperties* pkg10_g_app_properties_015fd918;
extern const std::uint8_t pkg10_g_dat_01519a48;

std::uint8_t __thiscall editor_query_dispatch_005dfd00(
    OpaqueEditorQueryContext* context, std::uint32_t command);
OpaquePreferenceQuery* __thiscall editor_query_reset_005dd750(
    OpaquePreferenceQuery* query, OpaquePropertyValue* value);
void __thiscall editor_query_clear_flags_0093db80(OpaquePreferenceQuery* query,
                                                  std::uint8_t clear_value);
OpaqueService* __cdecl editor_query_service_005ca960(OpaqueService* service);

}
