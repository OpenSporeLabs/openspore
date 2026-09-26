#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-game-input-wave7 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_GAME_INPUT_THISCALL __thiscall
#define PKG_GAME_INPUT_CDECL __cdecl
#else
#define PKG_GAME_INPUT_THISCALL __attribute__((thiscall))
#define PKG_GAME_INPUT_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_game_input_wave7 {

using TargetWord = std::uint32_t;
using KeyModifiers = TargetWord;
using MouseState = TargetWord;

struct alignas(4) OpaqueGameInputManager {
  std::byte opaque[0x114];
};

struct alignas(4) OpaqueGameInput {
  TargetWord keys[8];
  KeyModifiers key_modifiers;
  std::uint8_t mouse_buttons[8];
  float mouse_x;
  float mouse_y;
  std::int32_t mouse_button;
  float click_x;
  float click_y;
  MouseState mouse_state;
  std::int32_t mouse_wheel;
};

struct alignas(4) OpaqueGameInputBacking {
  std::byte pre_object[0x3c4];
  OpaqueGameInput input;
};

struct alignas(4) OpaqueCellInputState {
  OpaqueGameInput input;
  std::byte cell_opaque[0x8ef];
  std::uint8_t ui_flag_0937;
};

struct OpaqueCellModeStrategy {
  std::byte opaque[0x100];
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uintptr_t) == 4, "target raw addresses are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(float) == 4, "target floats are 32-bit");
static_assert(sizeof(OpaqueGameInputManager) == 0x114,
              "game input manager storage size");
static_assert(sizeof(OpaqueGameInput) == 0x48, "GameInput storage size");
static_assert(offsetof(OpaqueGameInputBacking, input) == 0x3c4,
              "padded GameInput backing offset");
static_assert(sizeof(OpaqueGameInputBacking) == 0x40c,
              "padded GameInput backing size");
static_assert(offsetof(OpaqueGameInput, key_modifiers) == 0x20,
              "GameInput key modifier offset");
static_assert(offsetof(OpaqueGameInput, mouse_buttons) == 0x24,
              "GameInput mouse button offset");
static_assert(offsetof(OpaqueGameInput, mouse_x) == 0x2c,
              "GameInput mouse X offset");
static_assert(offsetof(OpaqueGameInput, mouse_y) == 0x30,
              "GameInput mouse Y offset");
static_assert(offsetof(OpaqueGameInput, mouse_button) == 0x34,
              "GameInput active mouse button offset");
static_assert(offsetof(OpaqueCellInputState, input) == 0,
              "Cell state starts with GameInput");
static_assert(offsetof(OpaqueCellInputState, ui_flag_0937) == 0x937,
              "Cell UI flag offset");
static_assert(sizeof(OpaqueCellInputState) == 0x938, "Cell state storage size");

using StateRefresh = void(PKG_GAME_INPUT_THISCALL*)(OpaqueGameInput*);
using KeyRoute = std::uint8_t(PKG_GAME_INPUT_CDECL*)(std::int32_t,
                                                     KeyModifiers);
using CellAction = std::uint8_t(PKG_GAME_INPUT_CDECL*)(std::int32_t,
                                                       KeyModifiers);
using CellUiGate = std::uint8_t(PKG_GAME_INPUT_CDECL*)();
using CellModeStrategyMouseMoveAbi =
    bool(PKG_GAME_INPUT_THISCALL*)(OpaqueCellModeStrategy*, float, float);

static_assert(sizeof(StateRefresh) == 4, "refresh port is 32-bit");
static_assert(sizeof(KeyRoute) == 4, "key route port is 32-bit");
static_assert(sizeof(CellAction) == 4, "Cell action port is 32-bit");
static_assert(sizeof(CellUiGate) == 4, "Cell UI gate port is 32-bit");
static_assert(sizeof(CellModeStrategyMouseMoveAbi) == 4,
              "Cell mouse-move ABI slot is 32-bit");

struct NativePorts {
  static constexpr char boundary_metadata[] =
      "006979c0 ECX GameInput refresh plain RET; "
      "00e82900 key route with virtualKey/modifiers stack words; "
      "00e82cc0 no-argument AL gate; "
      "00e81120 and 00e7f630 virtualKey/modifiers stack words, AL result";

  StateRefresh refresh_006979c0 = nullptr;
  KeyRoute key_route_00e82900 = nullptr;
  CellUiGate ui_gate_00e82cc0 = nullptr;
  CellAction action_00e81120 = nullptr;
  CellAction action_00e7f630 = nullptr;
};

extern OpaqueGameInputManager* g_game_input_manager_0167eaf8;
extern OpaqueCellInputState* g_cell_input_state_016b3c0c;
extern NativePorts g_game_input_ports;

extern "C" OpaqueGameInputManager* simulator_game_input_manager_get_00b3d350();
extern "C" void PKG_GAME_INPUT_THISCALL
game_input_on_key_down_00697a50(OpaqueGameInput*, std::int32_t, KeyModifiers);
extern "C" void PKG_GAME_INPUT_THISCALL
game_input_on_key_up_00697a80(OpaqueGameInput*, std::int32_t, KeyModifiers);
extern "C" void PKG_GAME_INPUT_THISCALL game_input_mouse_up_00697af0(
    OpaqueGameInput*, std::int32_t, float, float, MouseState);
extern "C" bool PKG_GAME_INPUT_THISCALL
cell_mode_strategy_on_mouse_move_00e51010(OpaqueCellModeStrategy*, float,
                                          float);
extern "C" bool PKG_GAME_INPUT_THISCALL cell_mode_strategy_on_key_down_00e818f0(
    OpaqueCellModeStrategy*, std::int32_t, KeyModifiers);

#undef PKG_GAME_INPUT_THISCALL
#undef PKG_GAME_INPUT_CDECL

}
