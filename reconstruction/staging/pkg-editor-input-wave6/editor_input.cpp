#include "editor_input.hpp"

#include <cmath>
#include <cstring>

#if defined(_MSC_VER)
#define PKG_EDITOR_INPUT_THISCALL __thiscall
#else
#define PKG_EDITOR_INPUT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_input_wave6 {

OpaqueInputHooks* g_input_hooks = nullptr;

namespace {

template <typename Value>
Value load(const void* object, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store(void* object, std::size_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t*>(object) + offset, &value,
              sizeof(value));
}

TargetWord load_u32(const OpaqueEditor* editor, std::size_t offset) {
  return load<TargetWord>(editor, offset);
}

std::int32_t load_i32(const OpaqueEditor* editor, std::size_t offset) {
  return load<std::int32_t>(editor, offset);
}

std::uint8_t load_u8(const OpaqueEditor* editor, std::size_t offset) {
  return load<std::uint8_t>(editor, offset);
}

float load_f32(const OpaqueEditor* editor, std::size_t offset) {
  return load<float>(editor, offset);
}

OpaqueModeTarget* mode_target(OpaqueEditor* editor) {
  return load<OpaqueModeTarget*>(editor, 0x7c);
}

OpaqueSelectionTarget* selection_target(OpaqueEditor* editor) {
  return load<OpaqueSelectionTarget*>(editor, 0x148);
}

bool call_mode_mouse_move(OpaqueEditor* editor, float mouse_x, float mouse_y,
                          TargetWord mouse_state) {
  auto* target = mode_target(editor);
  if (target == nullptr || target->vtable == nullptr ||
      target->vtable->mouse_move_18 == nullptr) {
    return false;
  }
  target->vtable->mouse_move_18(target, mouse_x, mouse_y, mouse_state);
  return true;
}

bool call_mode_mouse_up(OpaqueEditor* editor, TargetWord button, float mouse_x,
                        float mouse_y, TargetWord mouse_state) {
  auto* target = mode_target(editor);
  if (target == nullptr || target->vtable == nullptr ||
      target->vtable->mouse_up_14 == nullptr) {
    return false;
  }
  return target->vtable->mouse_up_14(target, button, mouse_x, mouse_y,
                                     mouse_state);
}

bool call_mode_mouse_down(OpaqueEditor* editor, TargetWord button, float mouse_x,
                          float mouse_y, TargetWord mouse_state) {
  auto* target = mode_target(editor);
  if (target == nullptr || target->vtable == nullptr ||
      target->vtable->mouse_down_10 == nullptr) {
    return false;
  }
  target->vtable->mouse_down_10(target, button, mouse_x, mouse_y, mouse_state);
  return true;
}

bool call_mode_key_down(OpaqueEditor* editor, TargetWord key,
                        TargetWord modifiers) {
  auto* target = mode_target(editor);
  if (target == nullptr || target->vtable == nullptr ||
      target->vtable->key_down_1c == nullptr) {
    return false;
  }
  return target->vtable->key_down_1c(target, key, modifiers);
}

void call_mode_key_up(OpaqueEditor* editor, TargetWord key,
                      TargetWord modifiers) {
  auto* target = mode_target(editor);
  if (target != nullptr && target->vtable != nullptr &&
      target->vtable->key_up_20 != nullptr) {
    target->vtable->key_up_20(target, key, modifiers);
  }
}

bool call_selection_move(OpaqueEditor* editor, float mouse_x, float mouse_y,
                         TargetWord mouse_state) {
  auto* target = selection_target(editor);
  if (target == nullptr || target->vtable == nullptr ||
      target->vtable->mouse_move_1c == nullptr) {
    return false;
  }
  const bool result = target->vtable->mouse_move_1c(target, mouse_x, mouse_y,
                                                     mouse_state);
  if (target->vtable->query_28 != nullptr) {
    const TargetWord query = target->vtable->query_28(target);
    if (g_input_hooks != nullptr) {
      g_input_hooks->selection_side_effect(target, query);
    }
  }
  return result;
}

}

bool PKG_EDITOR_INPUT_THISCALL editor_input_005737d0(OpaqueEditor* editor,
                                                     float mouse_x, float mouse_y,
                                                     TargetWord mouse_state) {
  if (editor == nullptr || load_u8(editor, 0x397) != 0) {
    return false;
  }

  store<float>(editor, 0x28, mouse_x);
  store<float>(editor, 0x2c, mouse_y);
  store<TargetWord>(editor, 0x30, mouse_state);
  store<std::uint8_t>(editor, 0x38, 1);

  if (load_u8(editor, 0x2b3) != 0) {
    store<std::uint8_t>(editor, 0x2b3, 0);
    return true;
  }

  const TargetWord mode = load_u32(editor, 0x31c);
  if (mode == 2 && (mouse_state & 0x38u) != 0) {
    call_mode_mouse_move(editor, mouse_x, mouse_y, mouse_state);
    return false;
  }

  const TargetWord button = load_u32(editor, 0x34);
  const bool near_button = button == 0x3e9 || button == 0x3ea ||
                           (button == 0x3e8 && selection_target(editor) ==
                                                      nullptr);
  if (near_button) {
    const float x_distance = std::fabs(
        mouse_x - static_cast<float>(load_i32(editor, 0xc0)));
    if (x_distance > 3.0F) {
      store<std::uint8_t>(editor, 0x2b4, 0);
      return false;
    }
    const float y_distance = std::fabs(
        mouse_y - static_cast<float>(load_i32(editor, 0xc4)));
    if (y_distance <= 3.0F) {
      return false;
    }
    store<std::uint8_t>(editor, 0x2b4, 0);
    return false;
  }

  if (mode == 0 && selection_target(editor) != nullptr) {
    return call_selection_move(editor, mouse_x, mouse_y, mouse_state);
  }
  if (mode == 2) {
    call_mode_mouse_move(editor, mouse_x, mouse_y, mouse_state);
    return true;
  }
  return true;
}

bool PKG_EDITOR_INPUT_THISCALL editor_input_00585890(OpaqueEditor* editor,
                                                     TargetWord key,
                                                     TargetWord modifiers) {
  if (editor == nullptr) {
    return false;
  }
  if (g_input_hooks != nullptr) {
    g_input_hooks->game_key_up(
        static_cast<void*>(reinterpret_cast<std::uint8_t*>(editor) + 0xf8),
        key, modifiers);
    g_input_hooks->state_refresh(editor);
  }
  if (load_u32(editor, 0x31c) == 2) {
    call_mode_key_up(editor, key, modifiers);
  }
  if (g_input_hooks != nullptr) {
    g_input_hooks->state_refresh(editor);
  }
  if (key >= 0x10 && key <= 0x12) {
    store<TargetWord>(editor, 0x30, key);
  }
  return false;
}

bool PKG_EDITOR_INPUT_THISCALL editor_input_00585d10(OpaqueEditor* editor,
                                                     TargetWord wheel_delta,
                                                     float mouse_x, float mouse_y,
                                                     TargetWord mouse_state) {
  if (editor == nullptr || g_input_hooks == nullptr) {
    return false;
  }
  return g_input_hooks->dispatch_wheel(editor, wheel_delta, mouse_x, mouse_y,
                                       mouse_state, 0) != 0;
}

bool PKG_EDITOR_INPUT_THISCALL editor_input_00588570(OpaqueEditor* editor,
                                                     TargetWord button,
                                                     float mouse_x, float mouse_y,
                                                     TargetWord mouse_state) {
  if (editor == nullptr) {
    return false;
  }
  store<float>(editor, 0x68, 0.0F);
  if (load_u8(editor, 0x397) != 0) {
    return false;
  }
  if (selection_target(editor) != nullptr || load_u32(editor, 0x34) != 0) {
    return true;
  }
  store<TargetWord>(editor, 0x34, button);

  if (load_u8(editor, 0x472) != 0 && g_input_hooks != nullptr) {
    g_input_hooks->mouse_down_precheck(editor);
  }
  if (load_u8(editor, 0x4d4) != 0) {
    if (g_input_hooks != nullptr) {
      g_input_hooks->mouse_down_blocked(editor);
    }
    return true;
  }
  if (g_input_hooks == nullptr || !g_input_hooks->graphics_available() ||
      load_u32(editor, 0x84) == 0) {
    return false;
  }

  const TargetWord mode = load_u32(editor, 0x31c);
  if (mode == 2) {
    if (button == 0x3e8) {
      call_mode_mouse_down(editor, button, mouse_x, mouse_y, mouse_state);
    }
    return g_input_hooks->mouse_down_tail(editor, button, mouse_x, mouse_y,
                                          mouse_state);
  }
  if (mode == 1) {
    if (load_u32(editor, 0xcc) == 0 || button != 0x3e8) {
      return false;
    }
    const TargetWord flags = load_u32(editor, 0x3c);
    if ((flags & (1u | 0x10u)) != 0) {
      g_input_hooks->mouse_down_mode1(editor, button, mouse_x, mouse_y,
                                      mouse_state);
    }
    return false;
  }
  if (mode == 0) {
    return g_input_hooks->mouse_down_mode0(editor, button, mouse_x, mouse_y,
                                           mouse_state);
  }
  return g_input_hooks->mouse_down_tail(editor, button, mouse_x, mouse_y,
                                        mouse_state);
}

bool PKG_EDITOR_INPUT_THISCALL editor_input_0058ac10(OpaqueEditor* editor,
                                                     TargetWord key,
                                                     TargetWord modifiers) {
  if (editor == nullptr) {
    return false;
  }
  if (g_input_hooks != nullptr) {
    g_input_hooks->game_key_down(
        static_cast<void*>(reinterpret_cast<std::uint8_t*>(editor) + 0xf8),
        key, modifiers);
    g_input_hooks->state_refresh(editor);
    g_input_hooks->state_refresh(editor);
  }
  if (load_u8(editor, 0x397) != 0) {
    return false;
  }
  if (load_u32(editor, 0x31c) == 2 &&
      call_mode_key_down(editor, key, modifiers)) {
    return true;
  }
  if ((key & 0x40u) != 0 || key < 8 || key > 0xbf) {
    return false;
  }

  const bool primary_clear =
      g_input_hooks != nullptr && !g_input_hooks->key_gate_primary();
  const bool secondary_clear =
      g_input_hooks != nullptr && !g_input_hooks->key_gate_secondary();

  if ((key == 8 || key == 0x2e) && primary_clear && secondary_clear) {
    auto* object = load<OpaqueEditorObject*>(editor, 0xd4);
    if (object != nullptr && selection_target(editor) == nullptr &&
        (load<TargetWord>(object, 0xdc8) & (1u << 7)) == 0 &&
        load_u8(editor, 0x472) == 0) {
      g_input_hooks->key_path(editor, key, 0);
      return true;
    }
  }

  if (key == 0x0d && primary_clear && secondary_clear &&
      g_input_hooks->key_path_ready(key)) {
    g_input_hooks->key_path(editor, key, 0x0d);
    return true;
  }

  if (key >= 0x10 && key <= 0x12) {
    store<TargetWord>(editor, 0x30, key);
    return false;
  }

  if (key == 0x1b && primary_clear && secondary_clear &&
      g_input_hooks->key_path_ready(key)) {
    if (load_u32(editor, 0xd4) == 0 && load_u8(editor, 0xe9) == 0) {
      g_input_hooks->key_path(editor, key, 0x10d);
      return true;
    }
    if (load_u32(editor, 0x148) == 0) {
      if (load_u8(editor, 0xe9) != 0) {
        g_input_hooks->key_pending_clear(editor);
        store<std::uint8_t>(editor, 0xe9, 0);
      }
      return true;
    }
  }

  if ((key == 0x26 || key == 0x28) && primary_clear && secondary_clear) {
    const TargetWord delta = key == 0x26 ? 0x78u : 0xffffff88u;
    if (g_input_hooks->dispatch_wheel(editor, delta, load_f32(editor, 0x28),
                                      load_f32(editor, 0x2c),
                                      load_u32(editor, 0x30), 1u) != 0) {
      return true;
    }
    return true;
  }

  if ((key == 0x31 || key == 0x32 || key == 0x33 || key == 0x34 ||
       key == 0x35) &&
      (load_u8(editor, 0x3c) & 1u) != 0) {
    const TargetWord command = key == 0x31   ? 0x13u
                               : key == 0x32 ? 0x14u
                               : key == 0x33 ? 0x16u
                               : key == 0x34 ? 0x17u
                                             : 0x18u;
    g_input_hooks->key_command(editor, key, command);
    return true;
  }

  if ((key == 0x59 || key == 0x5a) && (key & 7u) == 2 &&
      load_u32(editor, 0x31c) != 2) {
    g_input_hooks->key_undo_redo(editor, key);
    return false;
  }

  return false;
}

bool PKG_EDITOR_INPUT_THISCALL editor_input_0058b650(OpaqueEditor* editor,
                                                     TargetWord button,
                                                     float mouse_x, float mouse_y,
                                                     TargetWord mouse_state) {
  if (editor == nullptr) {
    return false;
  }
  if (load_u32(editor, 0x34) != button) {
    return false;
  }
  store<TargetWord>(editor, 0x34, 0);

  const TargetWord mode = load_u32(editor, 0x31c);
  if (mode == 2) {
    call_mode_mouse_up(editor, button, mouse_x, mouse_y, mouse_state);
    return false;
  }
  if (mode != 0) {
    return false;
  }

  auto* selection = selection_target(editor);
  if (button == 0x3e9 || (button == 0x3e8 && selection == nullptr)) {
    if (g_input_hooks != nullptr) {
      g_input_hooks->mouse_up_simple(editor, button, mouse_x, mouse_y,
                                     mouse_state);
    }
    return false;
  }
  if ((button == 0x3e8 || button == 0x3ea) && selection != nullptr) {
    if (selection->vtable == nullptr || selection->vtable->mouse_up_10 == nullptr) {
      return false;
    }
    const bool result = selection->vtable->mouse_up_10(
        selection, button, mouse_x, mouse_y, mouse_state);
    const bool status = selection->vtable->status_34 != nullptr &&
                        selection->vtable->status_34(selection);
    if (status && g_input_hooks != nullptr) {
      g_input_hooks->selection_side_effect(selection, 1);
    }
    if (selection->vtable->finish_30 != nullptr) {
      selection->vtable->finish_30(selection);
    }
    store<OpaqueSelectionTarget*>(editor, 0x148, nullptr);
    if (selection->vtable->release_04 != nullptr) {
      selection->vtable->release_04(selection);
    }
    if (g_input_hooks != nullptr) {
      g_input_hooks->mouse_up_cleanup(editor, button,
                                      static_cast<std::uint8_t>(result),
                                      static_cast<std::uint8_t>(status));
    }
    return result;
  }
  return false;
}

}

#undef PKG_EDITOR_INPUT_THISCALL
