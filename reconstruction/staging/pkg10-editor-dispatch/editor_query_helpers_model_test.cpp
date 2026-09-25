#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

#include "editor_query_helpers.hpp"

namespace openspore::reconstruction::pkg10_editor_dispatch {

struct OpaqueEditor {
  std::uint32_t marker;
};

struct OpaqueMaterial {
  std::uint32_t marker;
};

struct OpaquePropertyValue {
  std::uint8_t value;
};

namespace model {

enum class EventKind : std::uint8_t {
  query_callback,
  property_set,
  app_system_get,
  app_system_init,
  debug,
  editor_output,
  editor_apply,
  transition_args,
  transition_b40,
  transition_8d0,
  transition_c4d0,
  service_lookup,
  state_decision,
  transition_dd300,
  transition_72260,
  raw_call,
  port_call,
  mode_flag,
  material_manager_get,
  material_slot30,
  register_material,
  service_slot0c,
  service_slot28,
};

struct Event {
  EventKind kind;
  std::uint32_t first;
  std::uint32_t second;
  std::uint32_t third;
  std::uint32_t fourth;
  const void* object;
};

std::vector<Event> events;
std::array<void*, 32> app_vtable{};
std::array<void*, 32> service_vtable{};
std::array<void*, 32> state_vtable{};
std::array<void*, 32> material_vtable{};
OpaqueService app_system{};
OpaqueService service{};
OpaqueService state_service{};
OpaqueMaterialManager material_manager{};
OpaqueMaterial material{};
OpaqueAppRuntime runtime{};
OpaqueAppProperties app_properties{};
OpaqueService* service_result = nullptr;
OpaqueMaterial* material_result = nullptr;
std::uint32_t state_result = 0;
std::uint32_t output_words[4]{};
std::uint32_t transition_one_value = 0;
std::uint32_t state_decision_value = 0;
std::uint32_t debug_state_at_callback = 0;
OpaqueEditorQueryContext* debug_context = nullptr;
std::uint32_t raw_call_first = 0;
std::uint32_t raw_call_third = 0;

template <typename Function>
void store_slot(void** table, std::size_t offset, Function function) {
  std::memcpy(table + offset / sizeof(void*), &function, sizeof(function));
}

void reset() {
  events.clear();
  service_result = nullptr;
  material_result = nullptr;
  state_result = 0;
  output_words[0] = 0x11111111u;
  output_words[1] = 0x22222222u;
  output_words[2] = 0x33333333u;
  output_words[3] = 0x44444444u;
  transition_one_value = 0;
  state_decision_value = 0;
  debug_state_at_callback = 0;
  debug_context = nullptr;
  raw_call_first = 0;
  raw_call_third = 0;
  runtime.prefix[0x118] = 0;
}

void add(EventKind kind, std::uint32_t first = 0, std::uint32_t second = 0,
         std::uint32_t third = 0, std::uint32_t fourth = 0,
         const void* object = nullptr) {
  events.push_back(Event{kind, first, second, third, fourth, object});
}

}

namespace {

void __cdecl query_callback(std::uint32_t first, OpaquePreferenceQuery* query,
                            std::uint32_t second, std::uint32_t third,
                            std::uint32_t fourth, std::uint32_t) {
  model::add(model::EventKind::query_callback, first, second, third, fourth,
             query);
}

OpaquePreferenceQuery* __thiscall property_set_value_bool(
    OpaquePreferenceQuery* query, OpaquePropertyValue* value) {
  model::add(
      model::EventKind::property_set,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(value)), 0, 0,
      0, query);
  return query;
}

OpaqueService* __cdecl app_system_get() {
  model::add(model::EventKind::app_system_get);
  return &model::app_system;
}

void __thiscall app_system_init(OpaqueService*, std::uint32_t first, void*,
                                void*) {
  model::add(model::EventKind::app_system_init, first);
}

void __cdecl debug_message(std::uint32_t value) {
  model::add(model::EventKind::debug, value);
  if (model::debug_context != nullptr) {
    model::debug_state_at_callback = model::debug_context->state;
  }
}

const std::uint32_t* __thiscall editor_output(OpaqueEditor*, std::uint32_t*) {
  model::add(model::EventKind::editor_output);
  return model::output_words;
}

void __thiscall editor_apply(OpaqueEditorQueryContext*, std::uint32_t first,
                             std::uint32_t second, std::uint32_t third,
                             std::uint32_t fourth) {
  model::add(model::EventKind::editor_apply, first, second, third, fourth);
}

void __thiscall transition_args(OpaqueEditorQueryContext*, std::uint32_t first,
                                std::uint32_t second) {
  model::add(model::EventKind::transition_args, first, second);
}

void __thiscall transition_b40(OpaqueEditorQueryContext*) {
  model::add(model::EventKind::transition_b40);
}

void __thiscall transition_8d0(OpaqueEditorQueryContext*) {
  model::add(model::EventKind::transition_8d0);
}

void __thiscall transition_c4d0(OpaqueEditorQueryContext*,
                                std::uint32_t value) {
  model::transition_one_value = value;
  model::add(model::EventKind::transition_c4d0, value);
}

OpaqueService* __thiscall service_lookup(OpaqueEditorQueryContext*,
                                         std::uint32_t value) {
  model::add(model::EventKind::service_lookup, value);
  return model::service_result;
}

void __thiscall state_decision(OpaqueEditorQueryContext*, std::uint32_t value) {
  model::state_decision_value = value;
  model::add(model::EventKind::state_decision, value);
}

void __thiscall transition_dd300(OpaqueEditorQueryContext*) {
  model::add(model::EventKind::transition_dd300);
}

void __thiscall transition_72260(OpaqueEditorQueryContext*) {
  model::add(model::EventKind::transition_72260);
}

void __cdecl raw_call(std::uint32_t first, OpaqueEditorQueryContext*,
                      std::uint32_t third) {
  model::raw_call_first = first;
  model::raw_call_third = third;
  model::add(model::EventKind::raw_call, first, third);
}

void __cdecl port_call(std::uint32_t value) {
  model::add(model::EventKind::port_call, value);
}

void __cdecl mode_flag(std::uint32_t value) {
  model::add(model::EventKind::mode_flag, value);
}

OpaqueMaterialManager* __cdecl material_manager_get() {
  model::add(model::EventKind::material_manager_get);
  return &model::material_manager;
}

OpaqueMaterial* __thiscall material_slot30(OpaqueMaterialManager*,
                                           std::uint32_t value) {
  model::add(model::EventKind::material_slot30, value);
  return model::material_result;
}

void __cdecl register_material(void* object, const void* value) {
  model::add(
      model::EventKind::register_material,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(value)), 0, 0,
      0, object);
}

OpaqueService* __thiscall service_slot0c(OpaqueService* service,
                                         std::uint32_t value) {
  model::add(model::EventKind::service_slot0c, value, 0, 0, 0, service);
  return model::service_result;
}

std::uint32_t __thiscall service_slot28(OpaqueService* service) {
  model::add(model::EventKind::service_slot28, model::state_result, 0, 0, 0,
             service);
  return model::state_result;
}

}

OpaqueQueryCallback pkg10_g_query_callback_0154eb48 = &query_callback;
OpaquePropertySetValueBool pkg10_g_property_set_value_bool_00422e20 =
    &property_set_value_bool;
OpaqueAppSystemGet pkg10_g_app_system_get_0067dcc0 = &app_system_get;
OpaqueAppSystemInit pkg10_g_app_system_init_0067dcc0_v14 = &app_system_init;
OpaqueDebugMessage pkg10_g_debug_004a88d0 = &debug_message;
OpaqueEditorOutput pkg10_g_editor_output_00572190 = &editor_output;
OpaqueEditorApply pkg10_g_editor_apply_005dca00 = &editor_apply;
OpaqueTransitionArgs pkg10_g_transition_args_005df470 = &transition_args;
OpaqueTransitionNoArgs pkg10_g_transition_noargs_005dfb40 = &transition_b40;
OpaqueTransitionNoArgs pkg10_g_transition_noargs_005df8d0 = &transition_8d0;
OpaqueTransitionOneArg pkg10_g_transition_one_005dc4d0 = &transition_c4d0;
OpaqueServiceLookup pkg10_g_service_lookup_005dc310 = &service_lookup;
OpaqueStateDecision pkg10_g_state_decision_005dd610 = &state_decision;
OpaqueTransitionNoArgs pkg10_g_transition_noargs_005dd300 = &transition_dd300;
OpaqueTransitionNoArgs pkg10_g_transition_noargs_00572260 = &transition_72260;
OpaqueRawCall pkg10_g_raw_call_0064bc50 = &raw_call;
OpaquePortCall pkg10_g_port_call_006035d0 = &port_call;
OpaqueModeFlag pkg10_g_mode_flag_008098f0 = &mode_flag;
OpaqueMaterialManagerGet pkg10_g_material_manager_get_0067dd30 =
    &material_manager_get;
OpaqueRegisterMaterial pkg10_g_register_material_00809db0 = &register_material;
OpaqueAppProperties* pkg10_g_app_properties_015fd918 = &model::app_properties;
const std::uint8_t pkg10_g_dat_01519a48 = 0;

namespace model {

void configure() {
  store_slot(app_vtable.data(), 0x14, &app_system_init);
  store_slot(service_vtable.data(), 0x0c, &service_slot0c);
  store_slot(state_vtable.data(), 0x28, &service_slot28);
  store_slot(material_vtable.data(), 0x30, &material_slot30);
  app_system.vtable = app_vtable.data();
  service.vtable = service_vtable.data();
  state_service.vtable = state_vtable.data();
  material_manager.vtable = material_vtable.data();
  app_properties.runtime = &runtime;
  pkg10_g_app_properties_015fd918 = &app_properties;
}

}

void test_005dd750() {
  OpaquePreferenceQuery query{};
  OpaquePropertyValue value{0x7f};
  query.flags = 0xffffu;
  query.trailing_flags = 0x1234u;
  model::reset();
  auto* result = editor_query_reset_005dd750(&query, &value);
  assert(result == &query);
  assert(query.flags == 0);
  assert(query.trailing_flags == 0);
  assert(model::events.size() == 1);
  assert(model::events[0].kind == model::EventKind::property_set);
  assert(model::events[0].first == reinterpret_cast<std::uintptr_t>(&value));
  assert(model::events[0].object == &query);

  query.flags = 0x55u;
  query.trailing_flags = 0x66u;
  model::reset();
  result = editor_query_reset_005dd750(&query, nullptr);
  assert(result == &query);
  assert(query.flags == 0);
  assert(query.trailing_flags == 0);
  assert(model::events[0].first == 0);
}

void test_0093db80() {
  OpaquePreferenceQuery query{};
  query.flags = 0x0004u;
  query.trailing_flags = 0x1234u;
  model::reset();
  editor_query_clear_flags_0093db80(&query, 1);
  assert(query.flags == 0);
  assert(query.trailing_flags == 0);
  assert(model::events.size() == 1);
  assert(model::events[0].kind == model::EventKind::query_callback);
  assert(model::events[0].first == 1);
  assert(model::events[0].object == &query);

  query.flags = 0x0006u;
  query.trailing_flags = 0xabcdu;
  model::reset();
  editor_query_clear_flags_0093db80(&query, 1);
  assert(query.flags == 0x0006u);
  assert(query.trailing_flags == 0xabcdu);
  assert(model::events.size() == 1);

  query.flags = 0;
  query.trailing_flags = 0x2222u;
  model::reset();
  editor_query_clear_flags_0093db80(&query, 0);
  assert(query.flags == 0);
  assert(query.trailing_flags == 0x2222u);
  assert(model::events.empty());
}

void test_005ca960() {
  model::configure();
  model::reset();
  assert(editor_query_service_005ca960(nullptr) == nullptr);
  model::service_result = &model::service;
  model::service.vtable = model::service_vtable.data();
  auto* result = editor_query_service_005ca960(&model::service);
  assert(result == &model::service);
  assert(model::events.size() == 1);
  assert(model::events[0].kind == model::EventKind::service_slot0c);
  assert(model::events[0].first == 0x8ed27e7au);
}

void test_005dfd00() {
  OpaqueEditorQueryContext context{};
  OpaqueEditor editor{};
  context.owner = &editor;
  model::configure();

  model::reset();
  assert(editor_query_dispatch_005dfd00(&context, 0x0ffu) == 0);
  assert(context.active == 1);
  assert(model::events.empty());

  model::reset();
  assert(editor_query_dispatch_005dfd00(&context, 0x100u) == 1);
  assert(context.state == 0x100u);
  assert(model::transition_one_value == 0);
  assert(model::events.size() == 2);
  assert(model::events[0].kind == model::EventKind::debug);
  assert(model::events[1].kind == model::EventKind::transition_c4d0);

  model::reset();
  assert(editor_query_dispatch_005dfd00(&context, 0x101u) == 1);
  assert(context.state == 0x101u);
  assert(model::events.size() == 1);
  assert(model::events[0].kind == model::EventKind::transition_args);
  assert(model::events[0].first == 0x101u);
  assert(model::events[0].second == 1);

  model::reset();
  model::debug_context = &context;
  assert(editor_query_dispatch_005dfd00(&context, 0x104u) == 1);
  assert(context.state == 0x104u);
  assert(model::debug_state_at_callback == 0x104u);
  assert(model::events.size() == 2);
  assert(model::events[0].kind == model::EventKind::debug);
  assert(model::events[1].kind == model::EventKind::transition_args);
  assert(model::events[1].first == 0x104u);
  model::debug_context = nullptr;

  model::reset();
  model::runtime.prefix[0x118] = 1;
  model::material_result = &model::material;
  assert(editor_query_dispatch_005dfd00(&context, 0x105u) == 1);
  assert(context.material_mode == 0x604fab1u);
  assert(context.state == 0x104u);
  assert(model::events.size() == 3);
  assert(model::events[0].kind == model::EventKind::material_manager_get);
  assert(model::events[1].kind == model::EventKind::material_slot30);
  assert(model::events[2].kind == model::EventKind::register_material);
  assert(model::events[2].first ==
         reinterpret_cast<std::uintptr_t>(&pkg10_g_dat_01519a48));

  model::reset();
  model::runtime.prefix[0x118] = 1;
  model::material_result = nullptr;
  assert(editor_query_dispatch_005dfd00(&context, 0x105u) == 1);
  assert(context.state == 0x105u);
  assert(model::raw_call_first == 0xdb184acbu);
  assert(model::raw_call_third == 0x54acb9f1u);
  assert(model::events[3].kind == model::EventKind::raw_call);

  model::reset();
  model::runtime.prefix[0x118] = 1;
  assert(editor_query_dispatch_005dfd00(&context, 0x106u) == 1);
  assert(model::events.size() == 3);
  assert(model::events[0].kind == model::EventKind::debug);
  assert(model::events[1].kind == model::EventKind::port_call);
  assert(model::events[2].kind == model::EventKind::mode_flag);

  model::reset();
  assert(editor_query_dispatch_005dfd00(&context, 0x109u) == 1);
  assert(context.state == 0);
  assert(model::events.size() == 2);
  assert(model::events[0].kind == model::EventKind::editor_output);
  assert(model::events[1].kind == model::EventKind::editor_apply);
  assert(model::events[1].first == 0x11111111u);
  assert(model::events[1].fourth == 0x44444444u);

  model::reset();
  model::service_result = &model::state_service;
  model::state_result = 0;
  assert(editor_query_dispatch_005dfd00(&context, 0x10du) == 1);
  assert(model::state_decision_value == 1);
  assert(model::events[0].kind == model::EventKind::debug);
  assert(model::events[1].kind == model::EventKind::service_lookup);
  assert(model::events[2].kind == model::EventKind::service_slot28);
  assert(model::events[3].kind == model::EventKind::state_decision);
}

}

int main() {
  openspore::reconstruction::pkg10_editor_dispatch::test_005dd750();
  openspore::reconstruction::pkg10_editor_dispatch::test_0093db80();
  openspore::reconstruction::pkg10_editor_dispatch::test_005ca960();
  openspore::reconstruction::pkg10_editor_dispatch::test_005dfd00();
}
