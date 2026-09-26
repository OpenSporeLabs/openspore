#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "game_input_wave7.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_game_input_wave7 {
namespace {

using namespace openspore::reconstruction::pkg_game_input_wave7;
using ExpectedMouseMoveAbi = bool(TEST_THISCALL*)(OpaqueCellModeStrategy*,
                                                  float, float);

static_assert(
    std::is_same<CellModeStrategyMouseMoveAbi, ExpectedMouseMoveAbi>::value,
    "mouse-move ABI is thiscall with two stack floats");
static_assert(sizeof(CellModeStrategyMouseMoveAbi) == 4,
              "mouse-move ABI slot is 32-bit");
static_assert(offsetof(OpaqueGameInput, keys) == 0,
              "mouse-move key state starts at zero");
static_assert(offsetof(OpaqueGameInput, mouse_x) == 0x2c,
              "mouse-move X state offset");
static_assert(offsetof(OpaqueGameInput, mouse_y) == 0x30,
              "mouse-move Y state offset");
static_assert(offsetof(OpaqueGameInput, mouse_button) == 0x34,
              "mouse-move active button offset");

std::vector<std::string>* events = nullptr;
std::uint8_t route_result = 0;
std::uint8_t ui_gate_result = 0;
std::uint8_t action_00e81120_result = 0;
std::uint8_t action_00e7f630_result = 0;
int failures = 0;
std::int32_t route_key = 0;
KeyModifiers route_modifiers = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* name) {
  if (events != nullptr) {
    events->push_back(name);
  }
}

void TEST_THISCALL refresh(OpaqueGameInput* input) {
  record("refresh");
  input->key_modifiers = 0;
  if ((input->keys[0] & (1u << 16)) != 0) {
    input->key_modifiers |= 1u;
  }
  if ((input->keys[0] & (1u << 17)) != 0) {
    input->key_modifiers |= 2u;
  }
  if ((input->keys[0] & (1u << 18)) != 0) {
    input->key_modifiers |= 4u;
  }
  if ((input->keys[7] & (1u << 1)) != 0) {
    input->key_modifiers |= 8u;
  }
  if ((input->keys[2] & (1u << 27)) != 0) {
    input->key_modifiers |= 16u;
  }
}

std::uint8_t route(std::int32_t key, KeyModifiers modifiers) {
  record("route");
  check(key == route_key);
  check(modifiers == route_modifiers);
  return route_result;
}

std::uint8_t ui_gate() {
  record("ui_gate");
  return ui_gate_result;
}

std::uint8_t action_00e81120(std::int32_t key, KeyModifiers modifiers) {
  record("action_00e81120");
  check(key == route_key);
  check(modifiers == route_modifiers);
  return action_00e81120_result;
}

std::uint8_t action_00e7f630(std::int32_t key, KeyModifiers modifiers) {
  record("action_00e7f630");
  check(key == route_key);
  check(modifiers == route_modifiers);
  return action_00e7f630_result;
}

NativePorts make_ports() {
  NativePorts ports{};
  ports.refresh_006979c0 = refresh;
  ports.key_route_00e82900 = route;
  ports.ui_gate_00e82cc0 = ui_gate;
  ports.action_00e81120 = action_00e81120;
  ports.action_00e7f630 = action_00e7f630;
  return ports;
}

void reset(OpaqueCellInputState& state) {
  state = OpaqueCellInputState{};
  g_cell_input_state_016b3c0c = &state;
  g_game_input_manager_0167eaf8 = nullptr;
  g_game_input_ports = make_ports();
  events->clear();
  route_result = 0;
  ui_gate_result = 0;
  action_00e81120_result = 0;
  action_00e7f630_result = 0;
  route_key = 0;
  route_modifiers = 0;
}

float from_bits(std::uint32_t bits) {
  float value = 0.0F;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

void test_get() {
  OpaqueGameInputManager manager{};
  g_game_input_manager_0167eaf8 = &manager;
  check(simulator_game_input_manager_get_00b3d350() == &manager);
  g_game_input_manager_0167eaf8 = nullptr;
  check(simulator_game_input_manager_get_00b3d350() == nullptr);
}

void test_key_level_behavior() {
  OpaqueCellInputState state{};
  reset(state);
  route_key = 0;
  game_input_on_key_down_00697a50(&state.input, 0, 0x12345678u);
  check(state.input.keys[0] == 1u);
  check(events->size() == 1);
  game_input_on_key_down_00697a50(&state.input, 31, 0);
  check(state.input.keys[0] == 0x80000001u);
  game_input_on_key_up_00697a80(&state.input, 0, 0);
  check(state.input.keys[0] == 0x80000000u);
  game_input_on_key_up_00697a80(&state.input, 31, 0);
  check(state.input.keys[0] == 0u);

  const std::uint32_t before = state.input.keys[0];
  const std::size_t event_count = events->size();
  game_input_on_key_down_00697a50(&state.input, -1, 0);
  game_input_on_key_down_00697a50(&state.input, 0x100, 0);
  game_input_on_key_up_00697a80(&state.input, -1, 0);
  game_input_on_key_up_00697a80(&state.input, 0x100, 0);
  check(state.input.keys[0] == before);
  check(events->size() == event_count);

  game_input_on_key_down_00697a50(&state.input, 255, 0);
  check(state.input.keys[7] == 0x80000000u);
  game_input_on_key_up_00697a80(&state.input, 255, 0);
  check(state.input.keys[7] == 0u);
}

void test_mouse_up() {
  OpaqueCellInputState state{};
  reset(state);
  for (std::uint8_t& button : state.input.mouse_buttons) {
    button = 1;
  }
  state.input.mouse_button = 1000;
  game_input_mouse_up_00697af0(&state.input, 1000, 1.25F, -2.5F, 0xdeadbeefu);
  check(state.input.mouse_buttons[0] == 0);
  check(state.input.mouse_buttons[1] == 1);
  check(state.input.mouse_x == 1.25F);
  check(state.input.mouse_y == -2.5F);
  check(state.input.mouse_button == 0);

  state.input.mouse_button = 1002;
  game_input_mouse_up_00697af0(&state.input, 1001, 3.5F, 4.5F, 0x12345678u);
  check(state.input.mouse_buttons[1] == 0);
  check(state.input.mouse_buttons[2] == 1);
  check(state.input.mouse_button == 1002);
  check(state.input.mouse_x == 3.5F);
  check(state.input.mouse_y == 4.5F);

  OpaqueGameInputBacking backing{};
  backing.pre_object[0] = static_cast<std::byte>(0xa5u);
  backing.input.mouse_button = 1002;
  const std::uintptr_t expected_address =
      reinterpret_cast<std::uintptr_t>(&backing.input) -
      static_cast<std::uintptr_t>(0x3c4u);
  game_input_mouse_up_00697af0(&backing.input, 0, 7.0F, 8.0F, 0x13572468u);
  check(reinterpret_cast<std::uintptr_t>(&backing.pre_object[0]) ==
        expected_address);
  check(static_cast<unsigned int>(backing.pre_object[0]) == 0u);
  check(backing.input.mouse_x == 7.0F);
  check(backing.input.mouse_y == 8.0F);
  check(backing.input.mouse_button == 1002);
}

void test_mouse_move() {
  OpaqueCellInputState state{};
  OpaqueCellModeStrategy strategy{};
  reset(state);
  CellModeStrategyMouseMoveAbi target =
      cell_mode_strategy_on_mouse_move_00e51010;
  check(sizeof(target) == 4);
  const float x = from_bits(0x42u);
  const float y = from_bits(0x37u);
  state.input.keys[2] = 0x4u;
  check(!target(&strategy, x, y));
  check(state.input.keys[2] == 0u);
  check(events->size() == 1);
  check(events->front() == "refresh");

  events->clear();
  check(!target(&strategy, 1.0F, 2.0F));
  check(state.input.keys[2] == 0u);
  check(events->empty());
}

void test_cell_key_down() {
  OpaqueCellInputState state{};
  OpaqueCellModeStrategy strategy{};
  reset(state);

  route_result = 2;
  route_key = 0x48;
  route_modifiers = 2;
  check(cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x48, 2));
  check(events->size() == 1);
  check(events->front() == "route");
  check(state.ui_flag_0937 == 0);
  check(state.input.keys[2] == 0);

  reset(state);
  route_key = 0x48;
  route_modifiers = 2;
  action_00e7f630_result = 0;
  check(!cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x48, 2));
  check(state.ui_flag_0937 == 1);
  check(state.input.keys[2] == 0x100u);
  check(events->size() == 5);
  check(events->at(0) == "route");
  check(events->at(1) == "refresh");
  check(events->at(2) == "ui_gate");
  check(events->at(3) == "action_00e7f630");
  check(events->at(4) == "action_00e81120");

  reset(state);
  route_key = 0x48;
  route_modifiers = 2;
  state.ui_flag_0937 = 1;
  check(!cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x48, 2));
  check(state.ui_flag_0937 == 0);

  reset(state);
  route_key = 0x42;
  route_modifiers = 6;
  action_00e81120_result = 0;
  check(!cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x42, 6));
  check(events->size() == 5);
  check(events->at(3) == "action_00e81120");
  check(events->at(4) == "action_00e7f630");

  reset(state);
  route_key = 0x42;
  route_modifiers = 6;
  action_00e81120_result = 1;
  check(cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x42, 6));
  check(events->size() == 4);
  check(events->at(3) == "action_00e81120");

  reset(state);
  route_key = 0x42;
  route_modifiers = 0;
  action_00e7f630_result = 1;
  check(cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x42, 0));
  check(events->size() == 4);
  check(events->at(3) == "action_00e7f630");

  reset(state);
  route_key = 0x43;
  route_modifiers = 0;
  ui_gate_result = 1;
  check(!cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x43, 0));
  check(events->size() == 3);
  check(events->at(2) == "ui_gate");

  reset(state);
  route_key = 0x42;
  route_modifiers = 0;
  ui_gate_result = 1;
  action_00e7f630_result = 2;
  action_00e81120_result = 0;
  check(!cell_mode_strategy_on_key_down_00e818f0(&strategy, 0x42, 0));
  check(events->size() == 5);
  check(events->at(3) == "action_00e7f630");
  check(events->at(4) == "action_00e81120");
}

int run_tests() {
  std::vector<std::string> test_events;
  events = &test_events;
  test_get();
  test_key_level_behavior();
  test_mouse_up();
  test_mouse_move();
  test_cell_key_down();
  events = nullptr;
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_game_input_wave7::run_tests();
}

#undef TEST_THISCALL
