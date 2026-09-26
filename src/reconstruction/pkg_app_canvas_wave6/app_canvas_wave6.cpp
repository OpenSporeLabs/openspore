#include "app_canvas_wave6.hpp"

#if defined(_MSC_VER)
#define APP_CANVAS_THISCALL __thiscall
#else
#define APP_CANVAS_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_canvas_wave6 {
namespace {

OpaqueCanvasSystems* canvas_systems = nullptr;

OpaqueCanvasSystems& systems() { return *canvas_systems; }

void* handle_from_word(OpaqueWord value) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(value));
}

void dispatch_00847e70(OpaqueCanvas* canvas, OpaqueDispatchRecord* record) {
  if (record->code == 0x01ee1001u && canvas->field_60 != nullptr) {
    canvas->field_60->vtable->dispatch(canvas->field_60, record->zero);
    return;
  }
  if (canvas->field_5c != nullptr) {
    canvas->field_5c->vtable->dispatch(canvas->field_5c, record->code, record,
                                       0);
    return;
  }
  if (canvas->field_64 != nullptr) {
    canvas->field_64(record, canvas->field_68);
  }
}

}

extern "C" OpaqueWord APP_CANVAS_THISCALL
app_canvas_00847a40(OpaqueCanvas* canvas, OpaqueWord value) {
  canvas->field_8 = value;
  const OpaqueWord state = (static_cast<std::uint8_t>(value) & 0x02u) != 0
                               ? 0x80000000u
                               : 0x80000003u;
  return systems().set_thread_state(state);
}

extern "C" OpaqueHandle APP_CANVAS_THISCALL
app_canvas_00847a90(OpaqueCanvas* canvas, std::uint8_t enabled) {
  OpaqueHandle selected = nullptr;
  if (enabled != 0) {
    selected = canvas->field_74;
  }
  return systems().set_active_handle(selected);
}

extern "C" bool APP_CANVAS_THISCALL app_canvas_00847b10(OpaqueCanvas* canvas) {
  OpaqueHandle ancestor = systems().get_ancestor_handle(canvas->field_74, 3);
  const OpaqueWord zoomed = systems().query_zoomed(ancestor);
  return zoomed != 0;
}

extern "C" std::uint16_t APP_CANVAS_THISCALL
app_canvas_00847b40(OpaqueCanvas* canvas) {
  return canvas->field_70;
}

extern "C" bool APP_CANVAS_THISCALL app_canvas_00848020(OpaqueCanvas* canvas) {
  if (canvas->field_74 == nullptr) {
    return true;
  }

  OpaqueDispatchRecord record{0x01ee1005u, canvas, 0};
  dispatch_00847e70(canvas, &record);

  if (canvas->field_74 != nullptr) {
    static_cast<void>(systems().kill_object_timer(canvas->field_74, 0));
    systems().global_state->field_10 = 0;
    static_cast<void>(systems().destroy_handle(canvas->field_74));
    canvas->field_74 = nullptr;
  }

  if (canvas->field_70 != 0) {
    OpaqueHandle module = systems().get_module_handle(nullptr);
    static_cast<void>(systems().unregister_class_handle(
        reinterpret_cast<const char*>(
            static_cast<std::uintptr_t>(canvas->field_70)),
        module));
    canvas->field_70 = 0;
  }

  if (canvas->field_80 != nullptr) {
    static_cast<void>(systems().delete_object_handle(canvas->field_80));
    canvas->field_80 = nullptr;
  }

  if (canvas->field_4d != 0) {
    static_cast<void>(systems().query_system_parameters(
        0x101bu, 0, handle_from_word(canvas->field_8c), 0));
  }
  if (canvas->field_4e != 0) {
    static_cast<void>(
        systems().query_system_parameters(0x5du, canvas->field_90, nullptr, 0));
  }
  if (canvas->field_4f != 0) {
    static_cast<void>(systems().query_system_parameters(
        0x101du, 0, handle_from_word(canvas->field_94), 0));
  }

  return true;
}

extern "C" void APP_CANVAS_THISCALL
app_canvas_00848100(OpaqueCanvas* canvas, OpaqueCanvasExtent* extent) {
  const OpaqueWord first = canvas->field_34;
  const OpaqueWord second = canvas->field_38;
  extent->first = first;
  extent->second = second;
}

void app_canvas_wave6_set_systems(OpaqueCanvasSystems* systems) {
  canvas_systems = systems;
}

}

#undef APP_CANVAS_THISCALL
