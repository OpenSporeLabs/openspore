#include "game_input_wave7.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_GAME_INPUT_THISCALL __thiscall
#else
#define PKG_GAME_INPUT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_game_input_wave7 {

OpaqueGameInputManager* g_game_input_manager_0167eaf8 = nullptr;
OpaqueCellInputState* g_cell_input_state_016b3c0c = nullptr;
NativePorts g_game_input_ports{};

namespace {

std::uint32_t float_bits(float value) {
  std::uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

}

extern "C" OpaqueGameInputManager* simulator_game_input_manager_get_00b3d350() {
  return g_game_input_manager_0167eaf8;
}

extern "C" void PKG_GAME_INPUT_THISCALL game_input_on_key_down_00697a50(
    OpaqueGameInput* input, std::int32_t vk_code, KeyModifiers modifiers) {
  static_cast<void>(modifiers);
  const std::uint32_t key = static_cast<std::uint32_t>(vk_code);
  if (key > 0xffu) {
    return;
  }
  input->keys[key >> 5] |= 1u << (key & 0x1fu);
  g_game_input_ports.refresh_006979c0(input);
}

extern "C" void PKG_GAME_INPUT_THISCALL game_input_on_key_up_00697a80(
    OpaqueGameInput* input, std::int32_t vk_code, KeyModifiers modifiers) {
  static_cast<void>(modifiers);
  const std::uint32_t key = static_cast<std::uint32_t>(vk_code);
  if (key > 0xffu) {
    return;
  }
  input->keys[key >> 5] &= ~(1u << (key & 0x1fu));
  g_game_input_ports.refresh_006979c0(input);
}

extern "C" void PKG_GAME_INPUT_THISCALL game_input_mouse_up_00697af0(
    OpaqueGameInput* input, std::int32_t button, float mouse_x, float mouse_y,
    MouseState mouse_state) {
  static_cast<void>(mouse_state);
  const std::uint8_t zero = 0;
  const std::uintptr_t relative =
      static_cast<std::uintptr_t>(button) - static_cast<std::uintptr_t>(0x3c4u);
  const std::uintptr_t address =
      reinterpret_cast<std::uintptr_t>(input) + relative;
  std::memcpy(reinterpret_cast<void*>(address), &zero, sizeof(zero));
  input->mouse_x = mouse_x;
  input->mouse_y = mouse_y;
  if (input->mouse_button == button) {
    input->mouse_button = 0;
  }
}

extern "C" bool PKG_GAME_INPUT_THISCALL
cell_mode_strategy_on_mouse_move_00e51010(OpaqueCellModeStrategy* strategy,
                                          float mouse_x, float mouse_y) {
  static_cast<void>(strategy);
  game_input_on_key_up_00697a80(&g_cell_input_state_016b3c0c->input,
                                static_cast<std::int32_t>(float_bits(mouse_x)),
                                static_cast<KeyModifiers>(float_bits(mouse_y)));
  return false;
}

extern "C" bool PKG_GAME_INPUT_THISCALL cell_mode_strategy_on_key_down_00e818f0(
    OpaqueCellModeStrategy* strategy, std::int32_t virtual_key,
    KeyModifiers modifiers) {
  static_cast<void>(strategy);
  if (g_game_input_ports.key_route_00e82900(virtual_key, modifiers) != 0) {
    return true;
  }

  if (virtual_key == 0x48 && modifiers == 0x2u) {
    auto* state = g_cell_input_state_016b3c0c;
    state->ui_flag_0937 = state->ui_flag_0937 == 0 ? 1u : 0u;
  }

  game_input_on_key_down_00697a50(&g_cell_input_state_016b3c0c->input,
                                  virtual_key, modifiers);

  const bool special_modifier_path =
      (modifiers & 0x2u) != 0 && (modifiers & 0x4u) != 0;
  if (g_game_input_ports.ui_gate_00e82cc0() != 0 && virtual_key != 0x42) {
    return false;
  }

  if (special_modifier_path) {
    if (g_game_input_ports.action_00e81120(virtual_key, modifiers) == 1) {
      return true;
    }
    return g_game_input_ports.action_00e7f630(virtual_key, modifiers) == 1;
  }

  if (g_game_input_ports.action_00e7f630(virtual_key, modifiers) == 1) {
    return true;
  }
  return g_game_input_ports.action_00e81120(virtual_key, modifiers) == 1;
}

}
