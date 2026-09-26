#include "runtime_services_wave7.hpp"

#include <cstdint>

#if defined(_MSC_VER)
#define RUNTIME_SERVICES_CDECL __cdecl
#define RUNTIME_SERVICES_THISCALL __thiscall
#else
#define RUNTIME_SERVICES_CDECL __attribute__((cdecl))
#define RUNTIME_SERVICES_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_runtime_services_wave7 {

RuntimeServiceGlobals g_runtime_service_globals{};

namespace {

template <typename Pointer>
Pointer pointer_from_word(TargetWord word) {
  return reinterpret_cast<Pointer>(static_cast<std::uintptr_t>(word));
}

OpaqueAppSystem* default_get_app_system() {
  return pointer_from_word<OpaqueAppSystem*>(
      g_runtime_service_globals.app_system_015fd890);
}

bool default_get_key(OpaquePropertyList*, TargetWord, ResourceKey*) {
  return false;
}

RuntimeServicePorts default_runtime_service_ports{
    &default_get_app_system,
};

CanvasPorts default_canvas_ports{
    &default_get_key,
};

}

RuntimeServicePorts* g_runtime_service_ports = &default_runtime_service_ports;
CanvasServiceGlobals g_canvas_service_globals{};
CanvasPorts* g_canvas_ports = &default_canvas_ports;

extern "C" OpaqueCheatManager* RUNTIME_SERVICES_CDECL
app_cheat_manager_get_0067dde0() {
  return pointer_from_word<OpaqueCheatManager*>(
      g_runtime_service_globals.cheat_manager_015fd8ec);
}

extern "C" OpaqueIDGenerator* RUNTIME_SERVICES_CDECL
app_id_generator_get_007c79e0() {
  return pointer_from_word<OpaqueIDGenerator*>(
      g_runtime_service_globals.id_generator_015fd8a4);
}

extern "C" CanvasMessageServerResult* RUNTIME_SERVICES_THISCALL
app_canvas_get_message_server_00c871d0(OpaqueCanvas* canvas,
                                       CanvasMessageServerResult* result) {
  result->word_00 = 0;
  result->word_04 = 0;
  result->word_08 = 0;

  if (canvas->vtable->probe_20(canvas)) {
    result->word_00 = g_canvas_service_globals.vtable_01579eb0;
    result->word_04 = g_canvas_service_globals.field_01579eb4;
    result->word_08 = g_canvas_service_globals.field_01579eb8;
    return result;
  }

  ResourceKey* key = reinterpret_cast<ResourceKey*>(result);
  if (g_canvas_ports->get_key_006a1250(canvas->property_list_30, 0xa6a37fc4u,
                                       key)) {
    result->word_04 = 0x00b1b104u;
    result->word_08 = 0x05f4d5e7u;
  }
  return result;
}

extern "C" bool RUNTIME_SERVICES_THISCALL
app_prop_manager_get_global_property_list_006a3310(
    OpaquePropManager* manager, TargetWord instance_id,
    OpaquePropertyListRef* destination) {
  return manager->vtable->get_global_property_list_2c(manager, instance_id, 0,
                                                      destination);
}

extern "C" TargetWord RUNTIME_SERVICES_THISCALL
app_prop_manager_get_supported_types_006a3400(OpaqueResourceFactory*,
                                              TargetWord* destination,
                                              std::size_t count) {
  if (destination != nullptr && count >= 1) {
    destination[0] = 0x00b1b104u;
  }
  return 1;
}

extern "C" void RUNTIME_SERVICES_THISCALL
editor_anim_event_message_send_0059d8b0(
    OpaqueEditorAnimEvent* event, TargetWord event_id, TargetWord secondary_id,
    OpaqueEditorModel* editor_model, TargetWord argument_5, bool flag_6,
    float value_7, bool flag_8, TargetWord argument_9, float value_10) {
  OpaqueAppSystem* service = g_runtime_service_ports->get_app_system_0067dcc0();
  if (service == nullptr) {
    return;
  }

  event->field_0c = argument_5;
  event->field_10 = secondary_id;
  event->editor_model_14 = editor_model;
  event->event_id_18 = event_id;
  event->flag_1c = static_cast<std::uint8_t>(flag_6);
  event->value_20 = value_7;
  event->flag_24 = static_cast<std::uint8_t>(flag_8);
  event->field_28 = argument_9;
  event->value_2c = value_10;
  service->vtable->message_send_14(service, 0xd1511790u, event, 0);
}

extern "C" void RUNTIME_SERVICES_THISCALL
editor_anim_event_message_post_0059d840(
    OpaqueEditorAnimEvent* event, TargetWord event_id, TargetWord secondary_id,
    OpaqueEditorModel* editor_model, TargetWord argument_5, bool flag_6,
    float value_7, bool flag_8, TargetWord argument_9, float value_10) {
  OpaqueAppSystem* service = g_runtime_service_ports->get_app_system_0067dcc0();
  if (service == nullptr) {
    return;
  }

  event->field_0c = argument_5;
  event->field_10 = secondary_id;
  event->editor_model_14 = editor_model;
  event->event_id_18 = event_id;
  event->flag_1c = static_cast<std::uint8_t>(flag_6);
  event->value_20 = value_7;
  event->flag_24 = static_cast<std::uint8_t>(flag_8);
  event->field_28 = argument_9;
  event->value_2c = value_10;
  service->vtable->message_post_18(service, 0xd1511790u, event, 0, 0);
}

}
