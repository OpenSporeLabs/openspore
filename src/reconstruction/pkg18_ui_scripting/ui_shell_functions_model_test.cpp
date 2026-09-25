#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "ui_shell_functions.hpp"

namespace openspore::reconstruction::pkg18_ui_scripting {
namespace model {

using Shell = OpaqueUiShell;
using Message = OpaqueUiMessage;
using Object = OpaqueUiObject;
using Vtable = OpaqueUiVtable;
using OpaqueWord = Opaque;
using Pointer = std::uint16_t*;
using ConstPointer = const std::uint16_t*;

enum class Kind : std::uint8_t {
  lookup,
  slot_0c,
  slot_10,
  slot_14,
  slot_1c,
  slot_20,
  slot_28,
  slot_3c,
  slot_44,
  slot_4c,
  slot_7c,
  slot_80,
  slot_94,
  slot_dc,
  provider_0,
  provider_4,
  provider_8,
  provider_10,
  app_14,
  coordinate,
  gate,
  debug,
  text,
  build_range,
  range_setup,
  names,
  names_build,
  free,
  parent,
};

struct Event {
  Kind kind;
  OpaqueWord first;
  OpaqueWord second;
  const void* object;
};

std::array<Object, 24> objects{};
std::array<Vtable, 16> vtables{};
alignas(4)
    std::array<unsigned char, sizeof(Object) + sizeof(Shell)> shell_storage{};
Object* parent_object;
Shell* shell;
Object* registry;
Object* child;
Object* text_service;
Object* text_controller;
Object* add_service;
Object* second_service;
Object* mode_service;
Object* secondary_service;
Object* route_item;
Object* presentation;
Object* provider;
Object* app;
Object* app_system;
Pointer source_text;
Event events[256]{};
std::size_t event_count;
std::uint8_t gate_result;
bool app_available;
bool empty_text_range;
OpaqueWord app_value;

void clear_bytes(void* object, std::size_t size) {
  auto* bytes = static_cast<unsigned char*>(object);
  for (std::size_t index = 0; index < size; ++index) {
    bytes[index] = 0;
  }
}

template <typename Value>
void store_object(Object* object, std::size_t offset, Value value) {
  std::memcpy(object->opaque.data() + offset - sizeof(OpaqueWord), &value,
              sizeof(value));
}

template <typename Value>
Value load_object(const Object* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, object->opaque.data() + offset - sizeof(OpaqueWord),
              sizeof(value));
  return value;
}

template <typename Value>
void store_shell(Shell* value, std::size_t offset, Value word) {
  std::memcpy(value->opaque.data() + offset - sizeof(OpaqueWord), &word,
              sizeof(word));
}

template <typename Value>
Value load_shell(const Shell* value, std::size_t offset) {
  Value word{};
  std::memcpy(&word, value->opaque.data() + offset - sizeof(OpaqueWord),
              sizeof(word));
  return word;
}

template <typename Value>
void store_message(Message* message, std::size_t offset, Value word) {
  std::memcpy(message->opaque.data() + offset, &word, sizeof(word));
}

template <typename Value>
Value load_message(const Message* message, std::size_t offset) {
  Value word{};
  std::memcpy(&word, message->opaque.data() + offset, sizeof(word));
  return word;
}

OpaqueWord pointer_word(const void* pointer) {
  return reinterpret_cast<OpaqueWord>(pointer);
}

const void* word_pointer(OpaqueWord word) {
  return reinterpret_cast<const void*>(word);
}

void add(Kind kind, OpaqueWord first = 0, OpaqueWord second = 0,
         const void* object = nullptr) {
  assert(event_count < 256);
  events[event_count++] = Event{kind, first, second, object};
}

OpaqueWord PKG18_THISCALL generic(OpaqueWord) { return 0; }

template <typename To, typename From>
To copy_function(From function) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &function, sizeof(result));
  return result;
}

template <typename Function>
void set_slot(Vtable* vtable, std::size_t offset, Function function) {
  vtable->slots[offset / sizeof(OpaqueWord)] =
      copy_function<Vtable::Slot>(function);
}

Object* make_object(std::size_t index, Vtable* vtable) {
  assert(index < objects.size());
  auto* object = &objects[index];
  clear_bytes(object, sizeof(*object));
  object->vtable = vtable;
  return object;
}

Vtable* make_vtable(std::size_t index) {
  assert(index < vtables.size());
  auto* vtable = &vtables[index];
  clear_bytes(vtable, sizeof(*vtable));
  for (auto& slot : vtable->slots) {
    slot = copy_function<Vtable::Slot>(generic);
  }
  return vtable;
}

OpaqueUiObject* PKG18_THISCALL registry_slot_0c(OpaqueUiObject* object,
                                                OpaqueWord value) {
  add(Kind::slot_0c, value, 0, object);
  return child;
}

OpaqueUiObject* PKG18_THISCALL text_slot_0c(OpaqueUiObject* object,
                                            OpaqueWord value) {
  add(Kind::slot_0c, value, 0, object);
  return text_controller;
}

OpaqueUiObject* PKG18_THISCALL route_slot_10(OpaqueUiObject* object) {
  add(Kind::slot_10, 0, 0, object);
  return load_object<Object*>(object, 4);
}

OpaqueWord PKG18_THISCALL route_slot_1c(OpaqueUiObject* object) {
  add(Kind::slot_1c, 0, 0, object);
  return load_object<OpaqueWord>(object, 4);
}

OpaqueWord PKG18_THISCALL route_slot_20(OpaqueUiObject* object) {
  add(Kind::slot_20, 0, 0, object);
  return app_value;
}

void PKG18_THISCALL configuration_slot_28(OpaqueUiObject* object,
                                          OpaqueWord first, OpaqueWord second) {
  add(Kind::slot_28, first, second, object);
}

const std::uint16_t* PKG18_THISCALL text_slot_3c(OpaqueUiObject* object) {
  add(Kind::slot_3c, 0, 0, object);
  return source_text;
}

OpaqueUiObject* PKG18_THISCALL route_slot_44(OpaqueUiObject* object,
                                             OpaqueWord* value) {
  add(Kind::slot_44, pointer_word(value), 0, object);
  return route_item;
}

void PKG18_THISCALL presentation_slot_4c(OpaqueUiObject* object,
                                         OpaqueWord first, OpaqueWord second) {
  add(Kind::slot_4c, first, second, object);
}

void PKG18_THISCALL service_slot_7c(OpaqueUiObject* object, OpaqueWord first,
                                    OpaqueWord second) {
  add(Kind::slot_7c, first, second, object);
}

void PKG18_THISCALL route_slot_80(OpaqueUiObject* object, OpaqueWord value) {
  add(Kind::slot_80, value, 0, object);
}

void PKG18_THISCALL text_slot_94(OpaqueUiObject* object, OpaqueWord first,
                                 OpaqueWord second) {
  add(Kind::slot_94, first, second, object);
}

void PKG18_THISCALL text_slot_dc(OpaqueUiObject* object) {
  add(Kind::slot_dc, 0, 0, object);
}

void PKG18_THISCALL provider_slot_0(OpaqueUiObject* object,
                                    ConstPointer value) {
  add(Kind::provider_0, pointer_word(value), 0, object);
}

OpaqueWord PKG18_THISCALL provider_slot_4(OpaqueUiObject* object) {
  add(Kind::provider_4, 0, 0, object);
  return pointer_word(source_text);
}

void PKG18_THISCALL provider_slot_8(OpaqueUiObject* object,
                                    ConstPointer value) {
  add(Kind::provider_8, pointer_word(value), 0, object);
}

void PKG18_THISCALL provider_slot_10(OpaqueUiObject* object,
                                     ConstPointer value) {
  add(Kind::provider_10, pointer_word(value), 0, object);
}

void PKG18_THISCALL app_system_slot_14(OpaqueUiObject* object, OpaqueWord first,
                                       OpaqueWord second, OpaqueWord third) {
  add(Kind::app_14, first, second, object);
  assert(third == 0);
}

void PKG18_THISCALL shell_slot_1c(Shell* object, OpaqueWord value) {
  add(Kind::slot_1c, value, 0, object);
}

void PKG18_THISCALL parent_slot_1c(Object* object, OpaqueWord value) {
  add(Kind::parent, value, 0, object);
}

void reset() {
  clear_bytes(objects.data(), sizeof(objects));
  clear_bytes(vtables.data(), sizeof(vtables));
  clear_bytes(shell_storage.data(), sizeof(shell_storage));
  event_count = 0;
  gate_result = 0;
  app_available = true;
  empty_text_range = false;
  app_value = 0x12345678u;
  source_text =
      const_cast<std::uint16_t*>(reinterpret_cast<const std::uint16_t*>(u"AB"));

  auto* parent_vtable = make_vtable(0);
  auto* shell_vtable = make_vtable(1);
  auto* service_vtable = make_vtable(2);
  auto* child_vtable = make_vtable(3);
  auto* text_vtable = make_vtable(4);
  auto* text_controller_vtable = make_vtable(5);
  auto* presentation_vtable = make_vtable(6);
  auto* provider_vtable = make_vtable(7);
  auto* route_vtable = make_vtable(8);
  auto* app_vtable = make_vtable(9);
  set_slot(parent_vtable, 0x1c, parent_slot_1c);
  set_slot(shell_vtable, 0x1c, shell_slot_1c);
  set_slot(service_vtable, 0x0c, registry_slot_0c);
  set_slot(service_vtable, 0x7c, service_slot_7c);
  set_slot(service_vtable, 0x80, route_slot_80);
  set_slot(service_vtable, 0x3c, text_slot_3c);
  set_slot(child_vtable, 0x28, configuration_slot_28);
  set_slot(text_vtable, 0x0c, text_slot_0c);
  set_slot(text_vtable, 0x1c, route_slot_1c);
  set_slot(text_vtable, 0x7c, service_slot_7c);
  set_slot(text_vtable, 0x3c, text_slot_3c);
  set_slot(text_controller_vtable, 0x94, text_slot_94);
  set_slot(text_controller_vtable, 0xdc, text_slot_dc);
  set_slot(presentation_vtable, 0x4c, presentation_slot_4c);
  set_slot(presentation_vtable, 0x44, route_slot_44);
  set_slot(provider_vtable, 0x00, provider_slot_0);
  set_slot(provider_vtable, 0x04, provider_slot_4);
  set_slot(provider_vtable, 0x08, provider_slot_8);
  set_slot(provider_vtable, 0x10, provider_slot_10);
  set_slot(route_vtable, 0x10, route_slot_10);
  set_slot(route_vtable, 0x80, route_slot_80);
  set_slot(app_vtable, 0x20, route_slot_20);

  parent_object = reinterpret_cast<Object*>(shell_storage.data());
  shell = reinterpret_cast<Shell*>(shell_storage.data() + sizeof(OpaqueWord));
  parent_object->vtable = parent_vtable;
  shell->vtable = shell_vtable;
  registry = make_object(0, service_vtable);
  child = make_object(1, child_vtable);
  text_service = make_object(2, text_vtable);
  text_controller = make_object(3, text_controller_vtable);
  add_service = make_object(4, service_vtable);
  second_service = make_object(5, service_vtable);
  mode_service = make_object(6, service_vtable);
  secondary_service = make_object(7, service_vtable);
  route_item = make_object(8, route_vtable);
  presentation = make_object(9, presentation_vtable);
  provider = make_object(10, provider_vtable);
  app = make_object(11, app_vtable);
  app_system = make_object(12, make_vtable(13));
  set_slot(app_system->vtable, 0x14, app_system_slot_14);
  store_shell(shell, 0x14, pointer_word(registry));
  store_shell(shell, 0x18, pointer_word(registry));
  store_shell(shell, 0x1c, pointer_word(provider));
  store_shell(shell, 0x34, pointer_word(text_service));
  store_object(route_item, 4, pointer_word(registry));
}

OpaqueUiObject* lookup(OpaqueUiObject* owner, OpaqueWord id, OpaqueWord flag) {
  add(Kind::lookup, id, flag, owner);
  switch (id) {
    case 0x272eb68eu:
      return registry;
    case 0x453ef531u:
      return registry;
    case 0xc7ceb1bdu:
      return text_service;
    case 0xd0e6d04bu:
      return secondary_service;
    case 0xaddc11efu:
      return add_service;
    case 0x5415e48u:
      return second_service;
    case 0x0552c901u:
      return mode_service;
    default:
      return nullptr;
  }
}

}

}

using namespace openspore::reconstruction::pkg18_ui_scripting;

extern "C" OpaqueUiObject* PKG18_THISCALL
pkg18_re_008105b0(OpaqueUiObject* owner, Opaque id, Opaque flag) {
  return openspore::reconstruction::pkg18_ui_scripting::model::lookup(owner, id,
                                                                      flag);
}

extern "C" std::uint8_t pkg18_re_008053b0() {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::gate, gate_result, 0, nullptr);
  return gate_result;
}

extern "C" void pkg18_re_00804f80(float x, float y, Opaque* message,
                                  Opaque* message_id) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::coordinate, static_cast<Opaque>(x), static_cast<Opaque>(y),
      message);
  (void)message_id;
}

extern "C" OpaqueUiObject* pkg18_re_0067caa0() {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  return presentation;
}

extern "C" void PKG18_THISCALL pkg18_re_005bf950(OpaqueUiShell* shell,
                                                 const std::uint16_t* text) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::text, pointer_word(text), 0, shell);
}

extern "C" void pkg18_re_00435ed0(Opaque id, Opaque value) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::debug, id, value, nullptr);
}

extern "C" OpaqueUiObject* pkg18_re_0067dcc0() {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  return app_system;
}

extern "C" void PKG18_THISCALL pkg18_re_00579a90(Opaque* range,
                                                 const std::uint16_t* text) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::build_range, pointer_word(text), 0, range);
  range[0] = pointer_word(text);
  range[1] = pointer_word(text + (empty_text_range ? 0 : 2));
}

extern "C" void PKG18_THISCALL pkg18_re_0057eda0(Opaque* range) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::range_setup, 0, 0, range);
}

extern "C" void pkg18_re_00f47380(Opaque pointer) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::free, pointer, 0, nullptr);
}

extern "C" OpaqueUiObject* pkg18_re_00a206f0() {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  return app_available ? app : nullptr;
}

extern "C" OpaqueUiObject* pkg18_re_004010a0(Opaque value, Opaque* output) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::names, value, 0, output);
  output[0] = pointer_word(source_text);
  output[1] = pointer_word(source_text + 2);
  output[2] = 0;
  return app_system;
}

extern "C" Opaque* PKG18_THISCALL pkg18_re_005ecf80(OpaqueUiObject* names,
                                                    Opaque* output,
                                                    Opaque value) {
  using namespace openspore::reconstruction::pkg18_ui_scripting::model;
  add(Kind::names_build, value, pointer_word(names), output);
  return output;
}

namespace {

using namespace openspore::reconstruction::pkg18_ui_scripting;
using namespace openspore::reconstruction::pkg18_ui_scripting::model;

Message message{};

void prepare_shell() {
  reset();
  clear_bytes(&message, sizeof(message));
  store_shell(shell, 0x0c, 1u);
  store_shell(shell, 0x10, 0u);
  store_shell(shell, 0x11, 1u);
  store_shell(shell, 0x20, 1u);
}

void test_dispatch_resource_routes() {
  prepare_shell();
  store_shell(shell, 0x18, 0x1234u);
  store_message(&message, 0, 0x1234u);
  store_message(&message, 8, 0xaaaau);
  assert(pkg18_ui_shell_dispatch_005bf9d0(shell, 0x14418c3fu, &message));
  assert(event_count == 2);
  assert(events[0].kind == Kind::lookup);
  assert(events[1].kind == Kind::slot_80);
  assert(events[1].first == 0xaaaau);

  prepare_shell();
  store_shell(shell, 0x18, 0x1234u);
  store_message(&message, 0, 0x1234u);
  store_message(&message, 8, 0xbbbbu);
  assert(pkg18_ui_shell_dispatch_005bf9d0(shell, 0x073127e6u, &message));
  assert(event_count == 2);
  assert(events[1].first == 0xbbbbu);

  prepare_shell();
  store_shell(shell, 0x18, 0x1234u);
  store_message(&message, 0, 0x1234u);
  store_message(&message, 8, pointer_word(source_text));
  assert(pkg18_ui_shell_dispatch_005bf9d0(shell, 0x7aa519dcu, &message));
  assert(event_count == 1);
  assert(events[0].kind == Kind::text);
  assert(events[0].first == pointer_word(source_text));

  prepare_shell();
  assert(!pkg18_ui_shell_dispatch_005bf9d0(shell, 0u, &message));
  assert(event_count == 0);
}

void test_dispatch_input_chain() {
  prepare_shell();
  std::array<unsigned char, 0x1c> payload{};
  const std::uint32_t payload_kind = 5;
  const std::uint32_t payload_size = 1000;
  const std::uint8_t payload_enabled = 1;
  const std::int32_t payload_x = 7;
  const std::int32_t payload_y = 9;
  std::memcpy(payload.data() + 0x08, &payload_kind, sizeof(payload_kind));
  std::memcpy(payload.data() + 0x0c, &payload_size, sizeof(payload_size));
  std::memcpy(payload.data() + 0x10, &payload_enabled, sizeof(payload_enabled));
  std::memcpy(payload.data() + 0x14, &payload_x, sizeof(payload_x));
  std::memcpy(payload.data() + 0x18, &payload_y, sizeof(payload_y));
  store_message(&message, 8, pointer_word(&payload));
  assert(pkg18_ui_shell_dispatch_005bf9d0(shell, 0x01ee1001u, &message));
  assert(event_count >= 5);
  assert(events[0].kind == Kind::gate);
  assert(events[1].kind == Kind::coordinate);
  assert(events[2].kind == Kind::slot_44);
  assert(events[3].kind == Kind::lookup);
  assert(events[4].kind == Kind::slot_10);
  assert(events[5].kind != Kind::parent);

  reset();
  store_shell(shell, 0x0c, 1u);
  store_object(route_item, 4, 0);
  store_message(&message, 8, pointer_word(&payload));
  assert(pkg18_ui_shell_dispatch_005bf9d0(shell, 0x01ee1001u, &message));
  bool parent_called = false;
  for (std::size_t index = 0; index < event_count; ++index) {
    parent_called = parent_called || events[index].kind == Kind::parent;
  }
  assert(parent_called);
}

void test_set_enabled_order() {
  prepare_shell();
  pkg18_ui_shell_set_enabled_005c0380(shell, 1);
  assert(load_shell<std::uint8_t>(shell, 0x10) == 1);
  assert(events[0].kind == Kind::lookup);
  assert(events[0].first == 0x272eb68eu);
  assert(events[1].kind == Kind::slot_0c);
  assert(events[2].kind == Kind::slot_28);
  assert(events[2].first == 4);
  assert(events[2].second == 1);
  assert(events[5].kind == Kind::slot_28);
  assert(events[5].first == 4);
  assert(events[5].second == 1);
  assert(events[event_count - 2].kind == Kind::debug);
  assert(events[event_count - 1].kind == Kind::app_14);
  assert(events[event_count - 1].first == 0x716d445u);

  const std::size_t count = event_count;
  pkg18_ui_shell_set_enabled_005c0380(shell, 1);
  assert(event_count == count);
}

void test_set_enabled_disable_text_path() {
  prepare_shell();
  store_shell(shell, 0x10, 1u);
  store_shell(shell, 0x11, 1u);
  pkg18_ui_shell_set_enabled_005c0380(shell, 0);
  assert(load_shell<std::uint8_t>(shell, 0x10) == 0);
  bool saw_build = false;
  bool saw_text = false;
  bool saw_free = false;
  for (std::size_t index = 0; index < event_count; ++index) {
    saw_build = saw_build || events[index].kind == Kind::build_range;
    saw_text = saw_text || events[index].kind == Kind::text;
    saw_free = saw_free || events[index].kind == Kind::free;
  }
  assert(saw_build);
  assert(saw_text);
  assert(saw_free);

  prepare_shell();
  store_shell(shell, 0x10, 1u);
  store_shell(shell, 0x11, 1u);
  empty_text_range = true;
  pkg18_ui_shell_set_enabled_005c0380(shell, 0);
  bool saw_provider_fallback = false;
  for (std::size_t index = 0; index < event_count; ++index) {
    saw_provider_fallback =
        saw_provider_fallback || events[index].kind == Kind::provider_4;
  }
  assert(saw_provider_fallback);
}

void test_handle_message_routes() {
  prepare_shell();
  store_shell(shell, 0x10, 1u);
  store_message(&message, 8, 1u);
  store_message(&message, 0x10, 0xdu);
  store_message(&message, 0x14, 0u);
  assert(pkg18_ui_shell_handle_message_005c0100(shell, 0x1234u, &message));
  assert(events[0].kind == Kind::slot_1c);
  assert(events[1].kind == Kind::slot_4c);

  prepare_shell();
  store_message(&message, 8, 1u);
  store_message(&message, 0x10, 9u);
  store_message(&message, 4, pointer_word(text_service));
  store_object(text_service, 4, 0xc7ceb1bdu);
  assert(pkg18_ui_shell_handle_message_005c0100(shell, 0, &message));
  bool submitted = false;
  for (std::size_t index = 0; index < event_count; ++index) {
    submitted = submitted || events[index].kind == Kind::slot_4c;
  }
  assert(submitted);

  prepare_shell();
  store_message(&message, 8, 0x18u);
  store_message(&message, 0x0c, 1u);
  store_message(&message, 0x14, 1u);
  assert(pkg18_ui_shell_handle_message_005c0100(shell, 0, &message));
  assert(events[0].kind == Kind::slot_1c);
  assert(events[0].first == 1);

  prepare_shell();
  store_message(&message, 8, 0x287259f6u);
  store_message(&message, 0x0c, 2u);
  assert(pkg18_ui_shell_handle_message_005c0100(shell, 0, &message));
  bool saw_names = false;
  bool saw_text = false;
  for (std::size_t index = 0; index < event_count; ++index) {
    saw_names = saw_names || events[index].kind == Kind::names_build;
    saw_text = saw_text || events[index].kind == Kind::text;
  }
  assert(saw_names);
  assert(saw_text);

  prepare_shell();
  assert(!pkg18_ui_shell_handle_message_005c0100(shell, 0, &message));
}

}

int main() {
  test_dispatch_resource_routes();
  test_dispatch_input_chain();
  test_set_enabled_order();
  test_set_enabled_disable_text_path();
  test_handle_message_routes();
}
