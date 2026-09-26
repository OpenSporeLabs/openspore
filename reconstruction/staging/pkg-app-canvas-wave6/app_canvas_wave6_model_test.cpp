#include <cassert>
#include <cstddef>
#include <cstdint>

#include "app_canvas_wave6.hpp"

#if defined(_MSC_VER)
#define APP_CANVAS_THISCALL __thiscall
#define APP_CANVAS_STDCALL __stdcall
#else
#define APP_CANVAS_THISCALL __attribute__((thiscall))
#define APP_CANVAS_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_app_canvas_wave6 {
namespace {

enum class Kind : std::uint8_t {
  thread_state,
  active_handle,
  ancestor,
  zoomed,
  message,
  fallback,
  timer,
  destroy,
  module,
  unregister,
  delete_object,
  system_parameters
};

struct Event {
  Kind kind;
  OpaqueWord first;
  OpaqueWord second;
  OpaqueWord third;
  OpaqueHandle handle;
  OpaqueHandle second_handle;
  OpaqueCanvas* canvas;
  OpaqueDispatchRecord* record;
  OpaqueMessageManager* manager;
  void* owner;
};

Event events[64];
std::size_t event_count = 0;
OpaqueWord thread_result = 0;
OpaqueHandle active_result = nullptr;
OpaqueHandle ancestor_result = nullptr;
OpaqueWord zoomed_result = 0;
OpaqueWord operation_result = 0;
OpaqueHandle module_result = nullptr;
OpaqueDispatchRecord observed_record{};
OpaqueCanvas* observed_canvas = nullptr;
OpaqueMessageManager* observed_manager = nullptr;
void* observed_owner = nullptr;
OpaqueGlobalState global_state{};
OpaqueCanvasSystems systems{};

OpaqueHandle handle(OpaqueWord value) {
  return reinterpret_cast<OpaqueHandle>(static_cast<std::uintptr_t>(value));
}

Event& next_event() {
  assert(event_count < sizeof(events) / sizeof(events[0]));
  Event& event = events[event_count++];
  event = Event{};
  return event;
}

OpaqueWord APP_CANVAS_STDCALL port_thread_state(OpaqueWord value) {
  Event& event = next_event();
  event.kind = Kind::thread_state;
  event.first = value;
  return thread_result;
}

OpaqueHandle APP_CANVAS_STDCALL port_active_handle(OpaqueHandle value) {
  Event& event = next_event();
  event.kind = Kind::active_handle;
  event.handle = value;
  return active_result;
}

OpaqueHandle APP_CANVAS_STDCALL port_ancestor_handle(OpaqueHandle value,
                                                     OpaqueWord flags) {
  Event& event = next_event();
  event.kind = Kind::ancestor;
  event.handle = value;
  event.first = flags;
  return ancestor_result;
}

OpaqueWord APP_CANVAS_STDCALL port_zoomed(OpaqueHandle value) {
  Event& event = next_event();
  event.kind = Kind::zoomed;
  event.handle = value;
  return zoomed_result;
}

OpaqueWord APP_CANVAS_STDCALL port_timer(OpaqueHandle value, OpaqueWord id) {
  Event& event = next_event();
  event.kind = Kind::timer;
  event.handle = value;
  event.first = id;
  return operation_result;
}

OpaqueWord APP_CANVAS_STDCALL port_destroy(OpaqueHandle value) {
  Event& event = next_event();
  event.kind = Kind::destroy;
  event.handle = value;
  return operation_result;
}

OpaqueHandle APP_CANVAS_STDCALL port_module(const char* name) {
  Event& event = next_event();
  event.kind = Kind::module;
  event.handle = const_cast<char*>(name);
  return module_result;
}

OpaqueWord APP_CANVAS_STDCALL port_unregister(const char* name,
                                              OpaqueHandle module) {
  Event& event = next_event();
  event.kind = Kind::unregister;
  event.handle = const_cast<char*>(name);
  event.second_handle = module;
  return operation_result;
}

OpaqueWord APP_CANVAS_STDCALL port_delete(OpaqueHandle value) {
  Event& event = next_event();
  event.kind = Kind::delete_object;
  event.handle = value;
  return operation_result;
}

OpaqueWord APP_CANVAS_STDCALL port_system_parameters(OpaqueWord action,
                                                     OpaqueWord parameter,
                                                     void* value,
                                                     OpaqueWord flags) {
  Event& event = next_event();
  event.kind = Kind::system_parameters;
  event.first = action;
  event.second = parameter;
  event.handle = value;
  event.third = flags;
  return operation_result;
}

void APP_CANVAS_THISCALL port_message(OpaqueMessageManager* manager,
                                      OpaqueWord code,
                                      OpaqueDispatchRecord* record,
                                      OpaqueWord zero) {
  Event& event = next_event();
  event.kind = Kind::message;
  event.first = code;
  event.third = zero;
  event.record = record;
  event.manager = manager;
  observed_record = *record;
}

void port_fallback(OpaqueDispatchRecord* record, void* owner) {
  Event& event = next_event();
  event.kind = Kind::fallback;
  event.owner = owner;
  event.record = record;
  observed_record = *record;
  observed_owner = owner;
}

void reset() {
  event_count = 0;
  thread_result = 0x12345678u;
  active_result = handle(0xaaaa0000u);
  ancestor_result = handle(0xbbbb0000u);
  zoomed_result = 0;
  operation_result = 0;
  module_result = handle(0xcccc0000u);
  observed_record = OpaqueDispatchRecord{};
  observed_canvas = nullptr;
  observed_manager = nullptr;
  observed_owner = nullptr;
  global_state = OpaqueGlobalState{};
  global_state.field_10 = 0xdeadbeefu;
  systems = OpaqueCanvasSystems{};
  systems.set_thread_state = port_thread_state;
  systems.set_active_handle = port_active_handle;
  systems.get_ancestor_handle = port_ancestor_handle;
  systems.query_zoomed = port_zoomed;
  systems.kill_object_timer = port_timer;
  systems.destroy_handle = port_destroy;
  systems.get_module_handle = port_module;
  systems.unregister_class_handle = port_unregister;
  systems.delete_object_handle = port_delete;
  systems.query_system_parameters = port_system_parameters;
  systems.global_state = &global_state;
  app_canvas_wave6_set_systems(&systems);
}

void test_thread_state_and_active_handle() {
  reset();
  OpaqueCanvas canvas{};
  canvas.field_74 = handle(0x11110000u);

  assert(app_canvas_00847a40(&canvas, 0u) == thread_result);
  assert(canvas.field_8 == 0u);
  assert(event_count == 1);
  assert(events[0].kind == Kind::thread_state);
  assert(events[0].first == 0x80000003u);

  assert(app_canvas_00847a40(&canvas, 2u) == thread_result);
  assert(canvas.field_8 == 2u);
  assert(events[1].first == 0x80000000u);

  assert(app_canvas_00847a40(&canvas, 0x102u) == thread_result);
  assert(canvas.field_8 == 0x102u);
  assert(events[2].first == 0x80000000u);

  assert(app_canvas_00847a40(&canvas, 0x100u) == thread_result);
  assert(canvas.field_8 == 0x100u);
  assert(events[3].first == 0x80000003u);

  assert(app_canvas_00847a90(&canvas, 0) == active_result);
  assert(events[4].kind == Kind::active_handle);
  assert(events[4].handle == nullptr);
  assert(app_canvas_00847a90(&canvas, 1) == active_result);
  assert(events[5].handle == canvas.field_74);
  canvas.field_74 = nullptr;
  assert(app_canvas_00847a90(&canvas, 1) == active_result);
  assert(events[6].handle == nullptr);
}

void test_window_query_and_word_return() {
  reset();
  OpaqueCanvas canvas{};
  canvas.field_74 = handle(0x22220000u);
  ancestor_result = handle(0x33330000u);

  assert(!app_canvas_00847b10(&canvas));
  assert(event_count == 2);
  assert(events[0].kind == Kind::ancestor);
  assert(events[0].handle == canvas.field_74);
  assert(events[0].first == 3u);
  assert(events[1].kind == Kind::zoomed);
  assert(events[1].handle == ancestor_result);

  zoomed_result = 0xffffffffu;
  assert(app_canvas_00847b10(&canvas));
  assert(event_count == 4);

  canvas.field_74 = nullptr;
  ancestor_result = nullptr;
  zoomed_result = 0;
  assert(!app_canvas_00847b10(&canvas));
  assert(events[4].handle == nullptr);

  canvas.field_70 = 0x1234u;
  assert(app_canvas_00847b40(&canvas) == 0x1234u);
  canvas.field_70 = 0;
  assert(app_canvas_00847b40(&canvas) == 0);
}

void test_cleanup_virtual_path() {
  reset();
  OpaqueCanvas canvas{};
  OpaqueMessageManagerVtable message_vtable{};
  OpaqueMessageManager message_manager{};
  message_vtable.dispatch = port_message;
  message_manager.vtable = &message_vtable;
  canvas.field_5c = &message_manager;
  canvas.field_74 = handle(0x44440000u);
  canvas.field_70 = 0x4321u;
  canvas.field_80 = handle(0x55550000u);
  canvas.field_4d = 1;
  canvas.field_4e = 1;
  canvas.field_4f = 1;
  canvas.field_8c = 0x11111111u;
  canvas.field_90 = 0x22222222u;
  canvas.field_94 = 0x33333333u;
  observed_canvas = &canvas;
  observed_manager = &message_manager;

  assert(app_canvas_00848020(&canvas));
  assert(event_count == 9);
  assert(events[0].kind == Kind::message);
  assert(events[0].first == 0x01ee1005u);
  assert(events[0].third == 0u);
  assert(events[0].record != nullptr);
  assert(events[0].manager == &message_manager);
  assert(events[0].record->code == 0x01ee1005u);
  assert(events[0].record->canvas == observed_canvas);
  assert(events[0].record->zero == 0u);
  assert(observed_record.code == 0x01ee1005u);
  assert(observed_record.canvas == observed_canvas);
  assert(observed_record.zero == 0u);
  assert(events[1].kind == Kind::timer);
  assert(events[1].handle == handle(0x44440000u));
  assert(events[1].first == 0u);
  assert(events[2].kind == Kind::destroy);
  assert(events[2].handle == handle(0x44440000u));
  assert(events[3].kind == Kind::module);
  assert(events[3].handle == nullptr);
  assert(events[4].kind == Kind::unregister);
  assert(events[4].handle == handle(0x4321u));
  assert(events[4].second_handle == module_result);
  assert(events[5].kind == Kind::delete_object);
  assert(events[5].handle == handle(0x55550000u));
  assert(events[6].kind == Kind::system_parameters);
  assert(events[6].first == 0x101bu);
  assert(events[6].second == 0u);
  assert(events[6].handle == handle(0x11111111u));
  assert(events[6].third == 0u);
  assert(events[7].kind == Kind::system_parameters);
  assert(events[7].first == 0x5du);
  assert(events[7].second == 0x22222222u);
  assert(events[7].handle == nullptr);
  assert(events[8].kind == Kind::system_parameters);
  assert(events[8].first == 0x101du);
  assert(events[8].second == 0u);
  assert(events[8].handle == handle(0x33333333u));
  assert(canvas.field_74 == nullptr);
  assert(canvas.field_70 == 0);
  assert(canvas.field_80 == nullptr);
  assert(global_state.field_10 == 0u);
}

void test_cleanup_fallback_and_early_return() {
  reset();
  OpaqueCanvas canvas{};
  canvas.field_74 = handle(0x66660000u);
  canvas.field_64 = port_fallback;
  canvas.field_68 = handle(0x77770000u);

  assert(app_canvas_00848020(&canvas));
  assert(event_count == 3);
  assert(events[0].kind == Kind::fallback);
  assert(events[0].owner == handle(0x77770000u));
  assert(observed_owner == handle(0x77770000u));
  assert(observed_record.code == 0x01ee1005u);
  assert(observed_record.canvas == &canvas);
  assert(events[1].kind == Kind::timer);
  assert(events[2].kind == Kind::destroy);
  assert(canvas.field_74 == nullptr);

  const std::size_t count = event_count;
  static_cast<void>(count);
  canvas.field_70 = 0x8765u;
  canvas.field_80 = handle(0x88880000u);
  systems.global_state = nullptr;
  assert(app_canvas_00848020(&canvas));
  assert(event_count == count);
  assert(canvas.field_70 == 0x8765u);
  assert(canvas.field_80 == handle(0x88880000u));
  systems.global_state = &global_state;
}

void test_extent_copy() {
  reset();
  OpaqueCanvas canvas{};
  OpaqueCanvasExtent extent{};
  canvas.field_34 = 0x89abcdefu;
  canvas.field_38 = 0xfedcba98u;
  app_canvas_00848100(&canvas, &extent);
  assert(extent.first == 0x89abcdefu);
  assert(extent.second == 0xfedcba98u);
  assert(event_count == 0);
}

void run() {
  test_thread_state_and_active_handle();
  test_window_query_and_word_return();
  test_cleanup_virtual_path();
  test_cleanup_fallback_and_early_return();
  test_extent_copy();
}

}

}

int main() {
  openspore::reconstruction::pkg_app_canvas_wave6::run();
  return 0;
}

#undef APP_CANVAS_THISCALL
#undef APP_CANVAS_STDCALL
