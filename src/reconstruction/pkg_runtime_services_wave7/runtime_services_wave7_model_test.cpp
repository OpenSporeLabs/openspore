#include <cstdint>

#include "runtime_services_wave7.hpp"

#if defined(_MSC_VER)
#define TEST_CDECL __cdecl
#define TEST_THISCALL __thiscall
#else
#define TEST_CDECL __attribute__((cdecl))
#define TEST_THISCALL __attribute__((thiscall))
#endif
#include <iostream>

namespace {

using namespace openspore::reconstruction::pkg_runtime_services_wave7;

int failures = 0;
int canvas_key_calls = 0;
bool canvas_key_result = false;
OpaquePropertyList* canvas_key_list = nullptr;
TargetWord canvas_key_id = 0;
OpaquePropManager* property_manager_receiver = nullptr;
TargetWord property_manager_instance = 0;
TargetWord property_manager_zero = 0;
OpaquePropertyListRef* property_manager_destination = nullptr;
bool property_manager_result = false;
OpaqueAppSystem* message_service_receiver = nullptr;
TargetWord message_send_id = 0;
OpaqueEditorAnimEvent* message_send_event = nullptr;
TargetWord message_send_zero = 0;
int message_send_calls = 0;
TargetWord message_post_id = 0;
OpaqueEditorAnimEvent* message_post_event = nullptr;
TargetWord message_post_zero_1 = 0;
TargetWord message_post_zero_2 = 0;
int message_post_calls = 0;

void check(bool condition, const char* message) {
  if (!condition) {
    ++failures;
    std::cerr << message << '\n';
  }
}

template <typename Pointer>
TargetWord word_from_pointer(Pointer pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

bool TEST_THISCALL canvas_probe_true(OpaqueCanvas* canvas) {
  return canvas->opaque_04_2f[0] != 0;
}

bool TEST_THISCALL canvas_probe_false(OpaqueCanvas*) { return false; }

bool canvas_get_key(OpaquePropertyList* property_list, TargetWord property_id,
                    ResourceKey* destination) {
  ++canvas_key_calls;
  canvas_key_list = property_list;
  canvas_key_id = property_id;
  if (canvas_key_result) {
    destination->instance_id = 0x12345678u;
    destination->type_id = 0x87654321u;
    destination->group_id = 0xabcdef01u;
  }
  return canvas_key_result;
}

bool TEST_THISCALL
get_global_property_list(OpaquePropManager* manager, TargetWord instance_id,
                         TargetWord zero, OpaquePropertyListRef* destination) {
  property_manager_receiver = manager;
  property_manager_instance = instance_id;
  property_manager_zero = zero;
  property_manager_destination = destination;
  if (destination != nullptr) {
    destination->pointer = reinterpret_cast<OpaquePropertyList*>(
        static_cast<std::uintptr_t>(0x22446688u));
  }
  return property_manager_result;
}

OpaqueAppSystem* TEST_CDECL get_message_service() {
  return message_service_receiver;
}

void TEST_THISCALL message_send_callback(OpaqueAppSystem* service,
                                         TargetWord id,
                                         OpaqueEditorAnimEvent* event,
                                         TargetWord zero) {
  message_service_receiver = service;
  message_send_id = id;
  message_send_event = event;
  message_send_zero = zero;
  ++message_send_calls;
}

void TEST_THISCALL message_post_callback(OpaqueAppSystem* service,
                                         TargetWord id,
                                         OpaqueEditorAnimEvent* event,
                                         TargetWord zero_1, TargetWord zero_2) {
  message_service_receiver = service;
  message_post_id = id;
  message_post_event = event;
  message_post_zero_1 = zero_1;
  message_post_zero_2 = zero_2;
  ++message_post_calls;
}

void test_service_accessors() {
  OpaqueCheatManager cheat{};
  OpaqueIDGenerator id_generator{};
  g_runtime_service_globals.cheat_manager_015fd8ec = word_from_pointer(&cheat);
  g_runtime_service_globals.id_generator_015fd8a4 =
      word_from_pointer(&id_generator);
  check(app_cheat_manager_get_0067dde0() == &cheat,
        "cheat manager global identity");
  check(app_id_generator_get_007c79e0() == &id_generator,
        "id generator global identity");

  g_runtime_service_globals.cheat_manager_015fd8ec = 0;
  g_runtime_service_globals.id_generator_015fd8a4 = 0;
  check(app_cheat_manager_get_0067dde0() == nullptr, "cheat manager null slot");
  check(app_id_generator_get_007c79e0() == nullptr, "id generator null slot");
}

void test_canvas_message_server() {
  CanvasVtable active_vtable{};
  active_vtable.probe_20 = &canvas_probe_true;
  OpaqueCanvas canvas{};
  canvas.vtable = &active_vtable;
  canvas.opaque_04_2f[0] = 1;
  g_canvas_service_globals.vtable_01579eb0 = 0x11111111u;
  g_canvas_service_globals.field_01579eb4 = 0x22222222u;
  g_canvas_service_globals.field_01579eb8 = 0x33333333u;

  CanvasMessageServerResult result{0xffffffffu, 0xffffffffu, 0xffffffffu};
  check(app_canvas_get_message_server_00c871d0(&canvas, &result) == &result,
        "canvas active result identity");
  check(result.word_00 == 0x11111111u, "canvas active vtable word");
  check(result.word_04 == 0x22222222u, "canvas active field 04");
  check(result.word_08 == 0x33333333u, "canvas active field 08");
  check(canvas_key_calls == 0, "canvas active key lookup skipped");

  active_vtable.probe_20 = &canvas_probe_false;
  OpaquePropertyList property_list{};
  canvas.property_list_30 = &property_list;
  canvas_key_result = true;
  canvas_key_calls = 0;
  CanvasPorts canvas_ports{&canvas_get_key};
  g_canvas_ports = &canvas_ports;
  result = {0xffffffffu, 0xffffffffu, 0xffffffffu};
  check(app_canvas_get_message_server_00c871d0(&canvas, &result) == &result,
        "canvas fallback result identity");
  check(canvas_key_calls == 1, "canvas fallback key lookup count");
  check(canvas_key_list == &property_list, "canvas fallback property list");
  check(canvas_key_id == 0xa6a37fc4u, "canvas fallback property id");
  check(result.word_00 == 0x12345678u, "canvas fallback key instance");
  check(result.word_04 == 0x00b1b104u, "canvas fallback field 04");
  check(result.word_08 == 0x05f4d5e7u, "canvas fallback field 08");

  canvas_key_result = false;
  result = {0xffffffffu, 0xffffffffu, 0xffffffffu};
  app_canvas_get_message_server_00c871d0(&canvas, &result);
  check(result.word_00 == 0u && result.word_04 == 0u && result.word_08 == 0u,
        "canvas failed key fallback clears result");
}

void test_property_manager() {
  OpaquePropManagerVtable property_vtable{};
  property_vtable.get_global_property_list_2c = &get_global_property_list;
  OpaquePropManager manager{};
  manager.vtable = &property_vtable;
  OpaquePropertyListRef destination{};
  property_manager_result = true;
  check(app_prop_manager_get_global_property_list_006a3310(&manager, 0x1234u,
                                                           &destination),
        "property manager dispatch result");
  check(property_manager_receiver == &manager,
        "property manager receiver dispatch");
  check(property_manager_instance == 0x1234u,
        "property manager instance argument");
  check(property_manager_zero == 0u, "property manager zero argument");
  check(property_manager_destination == &destination,
        "property manager destination argument");
  check(destination.pointer == reinterpret_cast<OpaquePropertyList*>(
                                   static_cast<std::uintptr_t>(0x22446688u)),
        "property manager output pointer");

  property_manager_result = false;
  check(!app_prop_manager_get_global_property_list_006a3310(&manager, 0x5678u,
                                                            &destination),
        "property manager false result");

  TargetWord destination_types[2]{0xaaaaaaaaU, 0xbbbbbbbbU};
  check(
      app_prop_manager_get_supported_types_006a3400(nullptr, nullptr, 0) == 1u,
      "supported types null destination count");
  check(app_prop_manager_get_supported_types_006a3400(
            nullptr, destination_types, 0) == 1u,
        "supported types zero count result");
  check(destination_types[0] == 0xaaaaaaaaU &&
            destination_types[1] == 0xbbbbbbbbU,
        "supported types zero count does not write");
  check(app_prop_manager_get_supported_types_006a3400(
            nullptr, destination_types, 1) == 1u,
        "supported types positive count result");
  check(destination_types[0] == 0x00b1b104u, "supported types first word");
  check(destination_types[1] == 0xbbbbbbbbu,
        "supported types second word unchanged");
}

void test_editor_message_send() {
  OpaqueAppSystemVtable service_vtable{};
  service_vtable.message_send_14 = &message_send_callback;
  OpaqueAppSystem service{};
  service.vtable = &service_vtable;
  message_service_receiver = &service;
  RuntimeServicePorts ports{&get_message_service};
  g_runtime_service_ports = &ports;

  OpaqueEditorModel model{};
  OpaqueEditorAnimEvent event{};
  message_send_calls = 0;
  editor_anim_event_message_send_0059d8b0(&event, 0x11111111u, 0x22222222u,
                                          &model, 0x33333333u, true, 1.25f,
                                          false, 0x44444444u, -2.5f);
  check(message_send_calls == 1, "message send call count");
  check(message_service_receiver == &service, "message send service receiver");
  check(message_send_id == 0xd1511790u, "message send event id");
  check(message_send_event == &event, "message send event pointer");
  check(message_send_zero == 0u, "message send trailing zero");
  check(event.field_0c == 0x33333333u, "message send field 0c");
  check(event.field_10 == 0x22222222u, "message send field 10");
  check(event.editor_model_14 == &model, "message send editor model");
  check(event.event_id_18 == 0x11111111u, "message send event id field");
  check(event.flag_1c == 1u, "message send flag 1c");
  check(event.value_20 == 1.25f, "message send value 20");
  check(event.flag_24 == 0u, "message send flag 24");
  check(event.field_28 == 0x44444444u, "message send field 28");
  check(event.value_2c == -2.5f, "message send value 2c");
}

void test_editor_message_post() {
  OpaqueAppSystemVtable service_vtable{};
  service_vtable.message_post_18 = &message_post_callback;
  OpaqueAppSystem service{};
  service.vtable = &service_vtable;
  message_service_receiver = &service;
  RuntimeServicePorts ports{&get_message_service};
  g_runtime_service_ports = &ports;

  OpaqueEditorModel model{};
  OpaqueEditorAnimEvent event{};
  message_post_calls = 0;
  editor_anim_event_message_post_0059d840(&event, 0xaaaaaaaaU, 0xbbbbbbbbU,
                                          &model, 0xccccccccU, false, 3.5f,
                                          true, 0xddddddddU, 4.5f);
  check(message_post_calls == 1, "message post call count");
  check(message_service_receiver == &service, "message post service receiver");
  check(message_post_id == 0xd1511790u, "message post event id");
  check(message_post_event == &event, "message post event pointer");
  check(message_post_zero_1 == 0u && message_post_zero_2 == 0u,
        "message post trailing zeros");
  check(event.field_0c == 0xccccccccU, "message post field 0c");
  check(event.field_10 == 0xbbbbbbbbU, "message post field 10");
  check(event.editor_model_14 == &model, "message post editor model");
  check(event.event_id_18 == 0xaaaaaaaaU, "message post event id field");
  check(event.flag_1c == 0u, "message post flag 1c");
  check(event.value_20 == 3.5f, "message post value 20");
  check(event.flag_24 == 1u, "message post flag 24");
  check(event.field_28 == 0xddddddddU, "message post field 28");
  check(event.value_2c == 4.5f, "message post value 2c");
}

void test_missing_message_service() {
  OpaqueEditorAnimEvent event{};
  event.field_0c = 0xaaaaaaaaU;
  message_service_receiver = nullptr;
  RuntimeServicePorts ports{&get_message_service};
  g_runtime_service_ports = &ports;
  editor_anim_event_message_send_0059d8b0(&event, 1u, 2u, nullptr, 3u, true,
                                          4.0f, true, 5u, 6.0f);
  editor_anim_event_message_post_0059d840(&event, 1u, 2u, nullptr, 3u, true,
                                          4.0f, true, 5u, 6.0f);
  check(event.field_0c == 0xaaaaaaaaU, "missing service leaves event unpacked");
}

}

int main() {
  test_service_accessors();
  test_canvas_message_server();
  test_property_manager();
  test_editor_message_send();
  test_editor_message_post();
  test_missing_message_service();
  if (failures != 0) {
    std::cerr << failures << " failure(s)\n";
    return 1;
  }
  return 0;
}
