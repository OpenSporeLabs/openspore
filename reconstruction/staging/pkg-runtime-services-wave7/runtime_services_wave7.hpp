#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "runtime services wave7 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define RUNTIME_SERVICES_CDECL __cdecl
#define RUNTIME_SERVICES_THISCALL __thiscall
#else
#define RUNTIME_SERVICES_CDECL __attribute__((cdecl))
#define RUNTIME_SERVICES_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_runtime_services_wave7 {

using TargetWord = std::uint32_t;

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");

struct OpaqueCheatManager {
  TargetWord opaque = 0;
};

struct OpaqueIDGenerator {
  TargetWord opaque = 0;
};

struct RuntimeServiceGlobals {
  TargetWord app_system_015fd890 = 0;
  TargetWord cheat_manager_015fd8ec = 0;
  TargetWord id_generator_015fd8a4 = 0;
};

extern RuntimeServiceGlobals g_runtime_service_globals;

struct OpaqueAppSystem;
struct OpaqueAppSystemVtable;

using GetAppSystem = OpaqueAppSystem*(RUNTIME_SERVICES_CDECL*)();

struct RuntimeServicePorts {
  GetAppSystem get_app_system_0067dcc0 = nullptr;
};

extern RuntimeServicePorts* g_runtime_service_ports;

extern "C" OpaqueCheatManager* RUNTIME_SERVICES_CDECL
app_cheat_manager_get_0067dde0();

extern "C" OpaqueIDGenerator* RUNTIME_SERVICES_CDECL
app_id_generator_get_007c79e0();

struct OpaquePropertyList {
  TargetWord opaque[4]{};
};

struct ResourceKey {
  TargetWord instance_id = 0;
  TargetWord type_id = 0;
  TargetWord group_id = 0;
};

struct CanvasServiceGlobals {
  TargetWord vtable_01579eb0 = 0;
  TargetWord field_01579eb4 = 0;
  TargetWord field_01579eb8 = 0;
};

extern CanvasServiceGlobals g_canvas_service_globals;

struct OpaqueCanvas;
struct CanvasVtable;

using CanvasProbe = bool(RUNTIME_SERVICES_THISCALL*)(OpaqueCanvas*);
using CanvasGetKey = bool(RUNTIME_SERVICES_CDECL*)(OpaquePropertyList*,
                                                   TargetWord, ResourceKey*);

struct CanvasVtable {
  void* slots_00_1c[8]{};
  CanvasProbe probe_20 = nullptr;
};

static_assert(offsetof(CanvasVtable, probe_20) == 0x20, "canvas probe slot");

struct OpaqueCanvas {
  CanvasVtable* vtable = nullptr;
  std::array<std::uint8_t, 0x2c> opaque_04_2f{};
  OpaquePropertyList* property_list_30 = nullptr;
};

static_assert(offsetof(OpaqueCanvas, property_list_30) == 0x30,
              "canvas property list offset");

struct CanvasMessageServerResult {
  TargetWord word_00 = 0;
  TargetWord word_04 = 0;
  TargetWord word_08 = 0;
};

static_assert(sizeof(CanvasMessageServerResult) == 12,
              "canvas message result size");

struct CanvasPorts {
  CanvasGetKey get_key_006a1250 = nullptr;
};

extern CanvasPorts* g_canvas_ports;

extern "C" CanvasMessageServerResult* RUNTIME_SERVICES_THISCALL
app_canvas_get_message_server_00c871d0(OpaqueCanvas* canvas,
                                       CanvasMessageServerResult* result);

struct OpaquePropertyListRef {
  OpaquePropertyList* pointer = nullptr;
};

static_assert(sizeof(OpaquePropertyListRef) == sizeof(TargetWord),
              "property list ref size");

struct OpaquePropManager;
struct OpaquePropManagerVtable;
struct OpaqueResourceFactory;

using GetGlobalPropertyList = bool(RUNTIME_SERVICES_THISCALL*)(
    OpaquePropManager*, TargetWord, TargetWord, OpaquePropertyListRef*);

struct OpaquePropManagerVtable {
  void* slots_00_28[11]{};
  GetGlobalPropertyList get_global_property_list_2c = nullptr;
};

static_assert(offsetof(OpaquePropManagerVtable, get_global_property_list_2c) ==
                  0x2c,
              "property manager dispatch slot");

struct OpaquePropManager {
  OpaquePropManagerVtable* vtable = nullptr;
};

extern "C" bool RUNTIME_SERVICES_THISCALL
app_prop_manager_get_global_property_list_006a3310(
    OpaquePropManager* manager, TargetWord instance_id,
    OpaquePropertyListRef* destination);

extern "C" TargetWord RUNTIME_SERVICES_THISCALL
app_prop_manager_get_supported_types_006a3400(OpaqueResourceFactory* factory,
                                              TargetWord* destination,
                                              std::size_t count);

struct OpaqueEditorModel {
  TargetWord opaque = 0;
};

struct OpaqueEditorAnimEvent {
  std::array<std::uint8_t, 0x0c> opaque_00_0b{};
  TargetWord field_0c = 0;
  TargetWord field_10 = 0;
  OpaqueEditorModel* editor_model_14 = nullptr;
  TargetWord event_id_18 = 0;
  std::uint8_t flag_1c = 0;
  std::array<std::uint8_t, 3> opaque_1d_1f{};
  float value_20 = 0.0f;
  std::uint8_t flag_24 = 0;
  std::array<std::uint8_t, 3> opaque_25_27{};
  TargetWord field_28 = 0;
  float value_2c = 0.0f;
};

static_assert(offsetof(OpaqueEditorAnimEvent, field_0c) == 0x0c,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, field_10) == 0x10,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, editor_model_14) == 0x14,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, event_id_18) == 0x18,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, flag_1c) == 0x1c,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, value_20) == 0x20,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, flag_24) == 0x24,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, field_28) == 0x28,
              "event field offset");
static_assert(offsetof(OpaqueEditorAnimEvent, value_2c) == 0x2c,
              "event field offset");

using MessageSend = void(RUNTIME_SERVICES_THISCALL*)(OpaqueAppSystem*,
                                                     TargetWord,
                                                     OpaqueEditorAnimEvent*,
                                                     TargetWord);
using MessagePost = void(RUNTIME_SERVICES_THISCALL*)(OpaqueAppSystem*,
                                                     TargetWord,
                                                     OpaqueEditorAnimEvent*,
                                                     TargetWord, TargetWord);

struct OpaqueAppSystemVtable {
  void* slots_00_10[5]{};
  MessageSend message_send_14 = nullptr;
  MessagePost message_post_18 = nullptr;
};

static_assert(offsetof(OpaqueAppSystemVtable, message_send_14) == 0x14,
              "message send slot");
static_assert(offsetof(OpaqueAppSystemVtable, message_post_18) == 0x18,
              "message post slot");

struct OpaqueAppSystem {
  OpaqueAppSystemVtable* vtable = nullptr;
};

extern "C" void RUNTIME_SERVICES_THISCALL
editor_anim_event_message_send_0059d8b0(
    OpaqueEditorAnimEvent* event, TargetWord event_id, TargetWord secondary_id,
    OpaqueEditorModel* editor_model, TargetWord argument_5, bool flag_6,
    float value_7, bool flag_8, TargetWord argument_9, float value_10);

extern "C" void RUNTIME_SERVICES_THISCALL
editor_anim_event_message_post_0059d840(
    OpaqueEditorAnimEvent* event, TargetWord event_id, TargetWord secondary_id,
    OpaqueEditorModel* editor_model, TargetWord argument_5, bool flag_6,
    float value_7, bool flag_8, TargetWord argument_9, float value_10);

}

#undef RUNTIME_SERVICES_CDECL
#undef RUNTIME_SERVICES_THISCALL
