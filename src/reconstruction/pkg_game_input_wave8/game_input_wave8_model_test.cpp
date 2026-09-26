#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "game_input_wave8.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_game_input_wave8 {
namespace {

__attribute__((cdecl, naked)) void openspore_w8_probe_sentinel_health_tick(
    std::int32_t mode, float amount) {
  __asm__ __volatile__(
      "movl %esp, %ecx\n\t"
      "movl 4(%ecx), %edx\n\t"
      "addl $0xa5a5a5a5, %edx\n\t"
      "movl %edx, 4(%ecx)\n\t"
      "movl 8(%ecx), %edx\n\t"
      "addl $0x5a5a5a5a, %edx\n\t"
      "movl %edx, 8(%ecx)\n\t"
      "retl\n\t");
}

__attribute__((cdecl, naked)) void openspore_w8_probe_residue_health_tick(
    std::int32_t mode, float amount) {
  __asm__ __volatile__(
      "movl %esp, %edx\n\t"
      "movl 4(%edx), %eax\n\t"
      "addl $0xa5a5a5a5, %eax\n\t"
      "movl %eax, 4(%edx)\n\t"
      "movl 8(%edx), %eax\n\t"
      "addl $0x5a5a5a5a, %eax\n\t"
      "movl %eax, 8(%edx)\n\t"
      "retl\n\t");
}

using ExpectedMouseDownAbi = bool(TEST_THISCALL*)(OpaqueCellModeStrategy*,
                                                  MouseButton, float, float,
                                                  MouseState);
using ExpectedMouseUpAbi = bool(TEST_THISCALL*)(OpaqueCellModeStrategy*,
                                                MouseButton, float, float,
                                                MouseState);
using ExpectedMouseWheelAbi = bool(TEST_THISCALL*)(OpaqueCellModeStrategy*,
                                                   WheelDelta, float, float,
                                                   MouseState);
using ExpectedHealthTickAbi = void(TEST_CDECL*)(std::int32_t, float);

static_assert(
    std::is_same<CellModeStrategyMouseDownAbi, ExpectedMouseDownAbi>::value,
    "mouse-down ABI is thiscall with four stack words");
static_assert(
    std::is_same<CellModeStrategyMouseUpAbi, ExpectedMouseUpAbi>::value,
    "mouse-up ABI is thiscall with four stack words");
static_assert(
    std::is_same<CellModeStrategyMouseWheelAbi, ExpectedMouseWheelAbi>::value,
    "mouse-wheel ABI is thiscall with four stack words");
static_assert(sizeof(CellModeStrategyMouseDownAbi) == 4,
              "mouse-down ABI slot is 32-bit");
static_assert(sizeof(CellModeStrategyMouseUpAbi) == 4,
              "mouse-up ABI slot is 32-bit");
static_assert(sizeof(CellModeStrategyMouseWheelAbi) == 4,
              "mouse-wheel ABI slot is 32-bit");
static_assert(std::is_same<HealthTickTarget, ExpectedHealthTickAbi>::value,
              "health-tick port is a plain-RET two-stack-word shape with no "
              "C++ channel for the in-EAX sentinel");
static_assert(sizeof(HealthTickTarget) == 4, "health-tick port is 32-bit");
static_assert(sizeof(std::int32_t) == 4, "health-tick mode stack word width");
static_assert(sizeof(float) == 4, "health-tick amount stack word width");
static_assert(kHealthTickDeadReceiver == 0xffffffffu,
              "health-tick dead receiver residue literal");
static_assert(sizeof(HealthTickRawObservation) == 16,
              "raw observation covers ECX, EAX, and exactly two stack words");
static_assert(offsetof(HealthTickRawObservation, sentinel_eax) == 0,
              "raw observation EAX word offset");
static_assert(offsetof(HealthTickRawObservation, residue_ecx) == 4,
              "raw observation ECX word offset");
static_assert(offsetof(HealthTickRawObservation, mode_word) == 8,
              "raw observation first stack word offset");
static_assert(offsetof(HealthTickRawObservation, amount_bits) == 12,
              "raw observation second stack word offset");
static_assert(kMouseButtonLeft == 0x3e8, "left mouse button literal");
static_assert(kMouseButtonRight == 0x3ea, "right mouse button literal");
static_assert(kMouseStateDownRaycastMask == 0x3,
              "mouse-down state mask literal");
static_assert(kMouseStateWheelZoomMask == 0x1, "wheel zoom state mask literal");
static_assert(kMouseStateWheelHealthMask == 0x2,
              "wheel health state mask literal");
static_assert(kRaycastCapacity == 0x200, "raycast capacity literal");
static_assert(kRaycastMaxDistanceBits == 0x7f7fffffu,
              "raycast maximum distance bit literal");
static_assert(kWheelStep == 0x78, "wheel step literal");
static_assert(kHealthTickMode == 3, "health tick mode literal");
static_assert(mouse_state_low_byte(0x12345603u) == 0x03, "low byte extraction");
static_assert(mouse_state_low_byte(0x00000100u) == 0x00,
              "state bits above the low byte are ignored");

std::vector<std::string>* events = nullptr;
int failures = 0;

OpaqueGameInput* last_input = nullptr;
MouseButton last_button = 0;
WheelDelta last_wheel = 0;
float last_x = 0.0F;
float last_y = 0.0F;
MouseState last_state = 0;

OpaqueRenderer renderer_object{};
OpaqueLayer layer_object{};
OpaqueCellObject picked_object{};
OpaqueCellSubObject sub_object{};
OpaqueCellGame game_object{};
OpaqueCellInputState cell_object{};

OpaqueCellObject* pick_result = nullptr;
std::int32_t sub_object_mode = 0;
std::int32_t raycast_hits = 0;
TargetWord raycast_buffer_first = 0;
bool wheel_gate_result = true;
int wheel_gate_calls = 0;
TargetWord lookup_result = 0;
std::int32_t zoom_out_argument = 0;
std::int32_t zoom_in_argument = 0;
std::int32_t health_tick_mode = 0;
float health_tick_amount = 0.0F;
bool health_tick_called = false;
bool health_tick_saw_sentinel = false;
int health_tick_calls = 0;
float unproject_screen_x = 0.0F;
float unproject_screen_y = 0.0F;
const Vec3Raw* unproject_first = nullptr;
const Vec3Raw* unproject_second = nullptr;
const Vec3Raw* unproject_int_first = nullptr;
const Vec3Raw* unproject_int_second = nullptr;
TargetWord raycast_scene = 0;
const Vec3Raw* raycast_first = nullptr;
const Vec3Raw* raycast_second = nullptr;
std::uint8_t* raycast_buffer = nullptr;
std::int32_t raycast_capacity = 0;
float raycast_max_distance = 0.0F;
std::int32_t handle_seen_by_reset = 0x5a5a5a5a;
std::int32_t handle_seen_by_resolve = 0;
std::int32_t handle_seen_by_release = 0;
OpaqueCellObject* clicked_object = nullptr;
OpaqueCellInputState repointed_cell{};
bool repoint_cell_on_pick = false;

constexpr TargetWord kNativeSentinelWord = 0x016b3c14u;
constexpr TargetWord kProbeWordWitnessLow = 0xa5a5a5a5u;
constexpr TargetWord kProbeWordWitnessHigh = 0x5a5a5a5au;
static_assert(kProbeWordWitnessLow == 0xa5a5a5a5u, "probe first word witness");
static_assert(kProbeWordWitnessHigh == 0x5a5a5a5au,
              "probe second word witness");

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

void TEST_THISCALL mouse_down(OpaqueGameInput* input, MouseButton button,
                              float x, float y, MouseState state) {
  record("mouse_down");
  last_input = input;
  last_button = button;
  last_x = x;
  last_y = y;
  last_state = state;
}

void TEST_THISCALL mouse_up(OpaqueGameInput* input, MouseButton button, float x,
                            float y, MouseState state) {
  record("mouse_up");
  last_input = input;
  last_button = button;
  last_x = x;
  last_y = y;
  last_state = state;
}

void TEST_THISCALL mouse_wheel(OpaqueGameInput* input, WheelDelta delta,
                               float x, float y, MouseState state) {
  record("mouse_wheel");
  last_input = input;
  last_wheel = delta;
  last_x = x;
  last_y = y;
  last_state = state;
}

OpaqueCellObject* TEST_CDECL pick_object() {
  record("pick");
  if (repoint_cell_on_pick) {
    g_cell_input_state_016b3c0c = &repointed_cell;
  }
  return pick_result;
}

void TEST_CDECL on_object_clicked(OpaqueCellObject* object) {
  record("clicked");
  clicked_object = object;
}

void TEST_THISCALL handle_reset(std::int32_t* handle) {
  record("handle_reset");
  handle_seen_by_reset = *handle;
  *handle = 0;
}

OpaqueCellSubObject* TEST_CDECL resolve_sub_object(std::int32_t* handle) {
  record("resolve");
  handle_seen_by_resolve = *handle;
  *handle = 0x13572468;
  sub_object.mode_00d4 = sub_object_mode;
  return &sub_object;
}

void TEST_THISCALL handle_release(std::int32_t* handle) {
  record("handle_release");
  handle_seen_by_release = *handle;
}

OpaqueRenderer* TEST_CDECL renderer_get() {
  record("renderer_get");
  return &renderer_object;
}

OpaqueLayer* TEST_THISCALL renderer_layer_slot(OpaqueRenderer* renderer) {
  record("renderer_layer");
  check(renderer == &renderer_object);
  return &layer_object;
}

void TEST_THISCALL unproject(OpaqueLayer* layer, float x, float y,
                             Vec3Raw* first, Vec3Raw* second) {
  record("unproject");
  check(layer == &layer_object);
  unproject_screen_x = x;
  unproject_screen_y = y;
  unproject_first = first;
  unproject_second = second;
  first->x = 0x11111111u;
  first->y = 0x22222222u;
  first->z = 0x33333333u;
  second->x = 0x44444444u;
  second->y = 0x55555555u;
  second->z = 0x66666666u;
}

void TEST_THISCALL unproject_int(OpaqueLayer* layer, Vec3Raw* first,
                                 Vec3Raw* second) {
  record("unproject_int");
  check(layer == &layer_object);
  unproject_int_first = first;
  unproject_int_second = second;
  first->x = 0x77777777u;
  first->y = 0x88888888u;
  first->z = 0x99999999u;
  second->x = 0xaaaaaaaau;
  second->y = 0xbbbbbbbbu;
  second->z = 0xcccccccu;
}

std::int32_t TEST_CDECL raycast(TargetWord scene, Vec3Raw* first,
                                Vec3Raw* second, std::uint8_t* buffer,
                                std::int32_t capacity, float max_distance) {
  record("raycast");
  raycast_scene = scene;
  raycast_first = first;
  raycast_second = second;
  raycast_buffer = buffer;
  raycast_capacity = capacity;
  raycast_max_distance = max_distance;
  std::memcpy(&buffer[0], &raycast_buffer_first, sizeof(TargetWord));
  buffer[4] = 0x5au;
  buffer[5] = 0x5au;
  buffer[6] = 0x5au;
  buffer[7] = 0x5au;
  return raycast_hits;
}

bool TEST_CDECL wheel_gate() {
  record("wheel_gate");
  ++wheel_gate_calls;
  return wheel_gate_result;
}

TargetWord TEST_THISCALL local_object_lookup(OpaqueCellObjectIndex* index,
                                             TargetWord id) {
  record("local_object_lookup");
  check(index == &game_object.object_index_01c);
  check(id == game_object.local_object_411c);
  return lookup_result;
}

void TEST_CDECL zoom_out(std::int32_t amount) {
  record("zoom_out");
  zoom_out_argument = amount;
}

void TEST_CDECL zoom_in(std::int32_t amount) {
  record("zoom_in");
  zoom_in_argument = amount;
}

void TEST_CDECL health_tick(std::int32_t mode, float amount) {
  record("health_tick");
  health_tick_called = true;
  ++health_tick_calls;
  health_tick_mode = mode;
  health_tick_amount = amount;
}

NativePorts make_ports() {
  NativePorts ports{};
  ports.mouse_down_00697ab0 = mouse_down;
  ports.mouse_up_00697af0 = mouse_up;
  ports.mouse_wheel_00697b40 = mouse_wheel;
  ports.pick_object_00e6c780 = pick_object;
  ports.on_object_clicked_00e643e0 = on_object_clicked;
  ports.handle_reset_00743b50 = handle_reset;
  ports.resolve_sub_object_00e4ce40 = resolve_sub_object;
  ports.handle_release_00e82130 = handle_release;
  ports.renderer_get_0067dd10 = renderer_get;
  ports.renderer_layer_slot_58 = renderer_layer_slot;
  ports.layer_unproject_007c4730 = unproject;
  ports.layer_unproject_int_007c4900 = unproject_int;
  ports.raycast_00e87200 = raycast;
  ports.wheel_gate_00b1fbf0 = wheel_gate;
  ports.local_object_lookup_00b721d0 = local_object_lookup;
  ports.zoom_out_00e50f60 = zoom_out;
  ports.zoom_in_00e51060 = zoom_in;
  ports.health_tick_00e7d070 = health_tick;
  return ports;
}

void reset() {
  game_object = OpaqueCellGame{};
  cell_object = OpaqueCellInputState{};
  sub_object = OpaqueCellSubObject{};
  game_object.scene_object_40fc = 0x0badc0deu;
  game_object.local_object_411c = 0x0000beefu;
  g_cell_game_016b3c04 = &game_object;
  g_cell_input_state_016b3c0c = &cell_object;
  g_object_sentinel_016b3c14 = 0x016b3c14u;
  g_game_input_wave8_ports = make_ports();
  events->clear();
  last_input = nullptr;
  last_button = 0;
  last_wheel = 0;
  last_x = 0.0F;
  last_y = 0.0F;
  last_state = 0;
  pick_result = &picked_object;
  sub_object_mode = 0;
  raycast_hits = 0;
  raycast_buffer_first = 0xcafebabeu;
  wheel_gate_result = true;
  wheel_gate_calls = 0;
  lookup_result = 0;
  zoom_out_argument = 0;
  zoom_in_argument = 0;
  health_tick_called = false;
  health_tick_mode = 0;
  health_tick_amount = 0.0F;
  health_tick_saw_sentinel = false;
  health_tick_calls = 0;
  unproject_screen_x = 0.0F;
  unproject_screen_y = 0.0F;
  unproject_first = nullptr;
  unproject_second = nullptr;
  unproject_int_first = nullptr;
  unproject_int_second = nullptr;
  raycast_scene = 0;
  raycast_first = nullptr;
  raycast_second = nullptr;
  raycast_buffer = nullptr;
  raycast_capacity = 0;
  raycast_max_distance = 0.0F;
  handle_seen_by_reset = 0x5a5a5a5a;
  handle_seen_by_resolve = 0;
  handle_seen_by_release = 0;
  clicked_object = nullptr;
  repointed_cell = OpaqueCellInputState{};
  repoint_cell_on_pick = false;
  cell_object.selected_object_00c4 = 0x99999999u;
  cell_object.pick_result_00c0 = 0x99999999u;
}

bool has(const char* name, std::size_t index) {
  return index < events->size() && events->at(index) == name;
}

void check_order(const char* const* names, std::size_t count) {
  check(events->size() == count);
  for (std::size_t index = 0; index < count; ++index) {
    check(has(names[index], index));
  }
}

float from_bits(std::uint32_t bits) {
  float value = 0.0F;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

std::int32_t native_wheel_step_reference(std::int32_t wheel_delta) {
  std::int64_t product =
      static_cast<std::int64_t>(wheel_delta) *
      static_cast<std::int64_t>(static_cast<std::int32_t>(0x88888889u));
  std::int32_t high = static_cast<std::int32_t>(product >> 32);
  high = static_cast<std::int32_t>(high + wheel_delta);
  high = static_cast<std::int32_t>(high >> 6);
  const std::uint32_t sign_bit = static_cast<std::uint32_t>(high) >> 31;
  return static_cast<std::int32_t>(sign_bit + static_cast<std::uint32_t>(high));
}

void test_wheel_step_quotient() {
  static const std::int32_t kNativeExpected[] = {
      0,    1,    59,   60,   61,   119,  120,  121,   239,   240,   241,  600,
      601,  999,  1000, 1001, 1200, 4800, -1,   -59,   -60,   -61,   -119, -120,
      -121, -239, -240, -241, -600, -601, -999, -1000, -1001, -1200, -4800};
  for (std::int32_t value : kNativeExpected) {
    check(wheel_step_quotient(value) == native_wheel_step_reference(value));
  }
  check(wheel_step_quotient(240) == 2);
  check(wheel_step_quotient(-120) == -1);
  check(wheel_step_quotient(480) == 4);
  check(wheel_step_quotient(1200) == 10);

  check(wheel_step_quotient(0) == 0);
  check(wheel_step_quotient(1) == 0);
  check(wheel_step_quotient(59) == 0);
  check(wheel_step_quotient(60) == 0);
  check(wheel_step_quotient(61) == 0);
  check(wheel_step_quotient(119) == 0);
  check(wheel_step_quotient(120) == 1);
  check(wheel_step_quotient(121) == 1);
  check(wheel_step_quotient(239) == 1);
  check(wheel_step_quotient(240) == 2);
  check(wheel_step_quotient(241) == 2);

  check(wheel_step_quotient(-1) == 0);
  check(wheel_step_quotient(-59) == 0);
  check(wheel_step_quotient(-60) == 0);
  check(wheel_step_quotient(-61) == 0);
  check(wheel_step_quotient(-119) == 0);
  check(wheel_step_quotient(-120) == -1);
  check(wheel_step_quotient(-121) == -1);
  check(wheel_step_quotient(-239) == -1);
  check(wheel_step_quotient(-240) == -2);
  check(wheel_step_quotient(-241) == -2);

  check(wheel_step_quotient(0x7fffffff) == 17895697);
  check(wheel_step_quotient(-0x7fffffff - 1) == -17895697);
  check(wheel_step_quotient(0x7fffffff) == 0x7fffffff / kWheelStep);
  check(wheel_step_quotient(-0x7fffffff - 1) == (-0x7fffffff - 1) / kWheelStep);

  for (std::int32_t value = -300000; value <= 300000; ++value) {
    if (wheel_step_quotient(value) != native_wheel_step_reference(value)) {
      check(false);
    }
  }
}

void test_constants() {
  check(float_bits(float_from_bits(kRaycastMaxDistanceBits)) ==
        kRaycastMaxDistanceBits);
  check(float_from_bits(kRaycastMaxDistanceBits) ==
        3.40282346638528859812e+38F);
  check(float_bits(0.0F) == 0u);
  check(wheel_step_quotient(0) == 0);
  check(wheel_step_quotient(119) == 0);
  check(wheel_step_quotient(120) == 1);
  check(wheel_step_quotient(240) == 2);
  check(wheel_step_quotient(-119) == 0);
  check(wheel_step_quotient(-120) == -1);
  check(wheel_step_quotient(-240) == -2);
  check(wheel_step_quotient(121) == 1);
  check(wheel_step_quotient(-121) == -1);
  check(wheel_step_quotient(0x7fffffff) == 0x7fffffff / kWheelStep);
  check(wheel_step_quotient(-0x7fffffff - 1) == (-0x7fffffff - 1) / kWheelStep);
}

void test_mouse_down_raycast_path() {
  OpaqueCellModeStrategy strategy{};
  reset();
  sub_object_mode = 7;
  cell_object.selected_object_00c4 = 0x12345678u;
  const float x = from_bits(0xc0490fdbu);
  const float y = from_bits(0x40490fdbu);
  raycast_hits = 4;
  check(
      cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e9, x, y, 0x3u));
  check(events->size() == 5);
  check(has("mouse_down", 0));
  check(has("renderer_get", 1));
  check(has("renderer_layer", 2));
  check(has("unproject", 3));
  check(has("raycast", 4));
  check(last_input == &cell_object.input);
  check(last_button == 0x3e9);
  check(last_x == x);
  check(last_y == y);
  check(last_state == 0x3u);
  check(float_bits(unproject_screen_x) == 0xc0490fdbu);
  check(float_bits(unproject_screen_y) == 0x40490fdbu);
  check(unproject_second == unproject_first + 1);
  check(raycast_buffer != nullptr);
  check(raycast_buffer != &cell_object.unproject_out_0100[0]);
  check(raycast_first == unproject_first);
  check(raycast_second == unproject_second);
  check(raycast_scene == 0x0badc0deu);
  check(raycast_capacity == 0x200);
  check(float_bits(raycast_max_distance) == 0x7f7fffffu);
  check(cell_object.pick_result_00c0 == 0xcafebabeu);
  check(cell_object.selected_object_00c4 == 0x12345678u);

  reset();
  raycast_hits = 0;
  cell_object.pick_result_00c0 = 0x11111111u;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0x1u));
  check(events->size() == 5);
  check(cell_object.pick_result_00c0 == 0x11111111u);
  check(cell_object.selected_object_00c4 == 0x99999999u);

  reset();
  raycast_hits = 2;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0x2u));
  check(events->size() == 5);
  check(cell_object.pick_result_00c0 == 0xcafebabeu);

  reset();
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                   0x4u));
  check(has("pick", 1));
  check(has("unproject", 3) == false);
  check(events->size() == 6);
  check(cell_object.selected_object_00c4 == 0u);
  check(cell_object.pick_result_00c0 == 0x99999999u);

  reset();
  raycast_hits = -3;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0xffffff03u));
  check(has("unproject", 3));
  check(cell_object.pick_result_00c0 == 0xcafebabeu);
}

void test_mouse_down_handle_lifecycle() {
  OpaqueCellModeStrategy strategy{};
  reset();
  sub_object_mode = 1;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0u));
  const char* const expected[] = {"mouse_down",   "pick",    "clicked",
                                  "handle_reset", "resolve", "handle_release"};
  check_order(expected, 6);
  check(handle_seen_by_reset == 0);
  check(handle_seen_by_resolve == 0);
  check(handle_seen_by_release == 0x13572468);
  check(clicked_object == &picked_object);
  check(cell_object.selected_object_00c4 ==
        static_cast<TargetWord>(
            reinterpret_cast<std::uintptr_t>(&picked_object)));

  reset();
  sub_object_mode = 1;
  cell_object.selected_object_00c4 = 0;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3ea, 1.0F, 2.0F,
                                                  0u));
  check(events->size() == 5);
  check(has("clicked", 2) == false);
  check(cell_object.selected_object_00c4 ==
        static_cast<TargetWord>(
            reinterpret_cast<std::uintptr_t>(&picked_object)));

  reset();
  sub_object_mode = 1;
  pick_result = nullptr;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                   0u));
  check(events->size() == 5);
  check(has("clicked", 2) == false);
  check(cell_object.selected_object_00c4 == 0u);

  reset();
  sub_object_mode = 1;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e9, 1.0F, 2.0F,
                                                   0u));
  check(events->size() == 5);
  check(has("clicked", 2) == false);
  check(cell_object.selected_object_00c4 == 0u);

  reset();
  sub_object_mode = 2;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0u));
  check(events->size() == 6);
  check(cell_object.selected_object_00c4 ==
        static_cast<TargetWord>(
            reinterpret_cast<std::uintptr_t>(&picked_object)));

  reset();
  sub_object_mode = 2;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3ea, 1.0F, 2.0F,
                                                   0u));
  check(events->size() == 5);
  check(cell_object.selected_object_00c4 == 0u);

  reset();
  sub_object_mode = 2;
  pick_result = nullptr;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                   0u));
  check(events->size() == 5);
  check(cell_object.selected_object_00c4 == 0u);

  for (std::int32_t mode : {0, 3, -1, 0x7fffffff}) {
    reset();
    sub_object_mode = mode;
    check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F,
                                                     2.0F, 0u));
    check(events->size() == 6);
    check(cell_object.selected_object_00c4 == 0u);
  }

  reset();
  sub_object_mode = 1;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, -1, 1.0F, 2.0F,
                                                   0u));
  check(cell_object.selected_object_00c4 == 0u);
  check(has("clicked", 2) == false);
}

void test_mouse_up() {
  OpaqueCellModeStrategy strategy{};
  reset();
  cell_object.health_0900 = 0x7fffffff;
  cell_object.health_phase_0904 = 12.5F;
  check(cell_mode_strategy_on_mouse_up_00e5c0f0(
      &strategy, 0x3ea, from_bits(0x3f800000u), from_bits(0x40000000u),
      0xabcdef01u));
  const char* const expected[] = {"mouse_up", "renderer_get", "renderer_layer",
                                  "unproject_int", "raycast"};
  check_order(expected, 5);
  check(last_input == &cell_object.input);
  check(last_button == 0x3ea);
  check(float_bits(last_x) == 0x3f800000u);
  check(float_bits(last_y) == 0x40000000u);
  check(last_state == 0xabcdef01u);
  check(reinterpret_cast<std::uintptr_t>(unproject_int_first) -
            reinterpret_cast<std::uintptr_t>(unproject_int_second) ==
        sizeof(Vec3Raw));
  check(raycast_first == unproject_int_first);
  check(raycast_second == unproject_int_second);
  check(raycast_buffer == &cell_object.unproject_out_0100[0]);
  check(raycast_scene == 0x0badc0deu);
  check(raycast_capacity == 0x200);
  check(float_bits(raycast_max_distance) == 0x7f7fffffu);
  check(cell_object.health_0900 == 0);
  check(float_bits(cell_object.health_phase_0904) == 0u);

  reset();
  raycast_hits = -7;
  check(cell_mode_strategy_on_mouse_up_00e5c0f0(&strategy, 0x3e8, 0.0F, 0.0F,
                                                0u));
  check(cell_object.health_0900 == -7);
  check(float_bits(cell_object.health_phase_0904) == 0u);
  check(events->size() == 5);

  reset();
  pick_result = nullptr;
  cell_object.health_0900 = 5;
  check(cell_mode_strategy_on_mouse_up_00e5c0f0(&strategy, 0x3e8, 0.0F, 0.0F,
                                                0u));
  check(has("pick", 1) == false);
  check(cell_object.health_0900 == 0);
  check(raycast_buffer == &cell_object.unproject_out_0100[0]);
  check(cell_object.unproject_out_0100[0] == 0xbeu);
  check(cell_object.unproject_out_0100[3] == 0xcau);
}

void test_mouse_wheel_observed_gate() {
  OpaqueCellModeStrategy strategy{};
  reset();
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 480, 1.0F, 2.0F,
                                                   0x3u));
  const char* const expected[] = {"mouse_wheel", "wheel_gate", "wheel_gate",
                                  "zoom_in"};
  check_order(expected, 4);
  check(wheel_gate_calls == 2);
  check(zoom_in_argument == 480);
  check(zoom_out_argument == 0);
  check(health_tick_called == false);
  check(last_input == &cell_object.input);
  check(last_wheel == 480);
  check(last_x == 1.0F);
  check(last_y == 2.0F);
  check(last_state == 0x3u);

  reset();
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -120, 1.0F, 2.0F,
                                                   0u));
  check(events->size() == 2);
  check(has("mouse_wheel", 0));
  check(has("zoom_in", 1));
  check(wheel_gate_calls == 0);
  check(zoom_in_argument == -120);
}

void test_mouse_wheel_zoom_branch() {
  OpaqueCellModeStrategy strategy{};
  reset();
  wheel_gate_result = false;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 240, 1.0F, 2.0F,
                                                   0x1u));
  const char* const expected[] = {"mouse_wheel", "wheel_gate", "zoom_out"};
  check_order(expected, 3);
  check(wheel_gate_calls == 1);
  check(zoom_out_argument == 2);
  check(zoom_in_argument == 0);
  check(health_tick_called == false);

  reset();
  wheel_gate_result = false;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -240, 1.0F, 2.0F,
                                                   0x3u));
  check(events->size() == 3);
  check(has("zoom_out", 2));
  check(zoom_out_argument == -2);
  check(wheel_gate_calls == 1);

  reset();
  wheel_gate_result = false;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 119, 1.0F, 2.0F,
                                                   0x1u));
  check(zoom_out_argument == 0);
}

void test_mouse_wheel_health_branch() {
  OpaqueCellModeStrategy strategy{};
  reset();
  wheel_gate_result = false;
  check(!cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -120, 1.0F, 2.0F,
                                                    0x2u));
  const char* const missing[] = {"mouse_wheel", "wheel_gate",
                                 "local_object_lookup"};
  check_order(missing, 3);
  check(lookup_result == 0);
  check(health_tick_called == false);
  check(zoom_in_argument == 0);
  check(zoom_out_argument == 0);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 120, 1.0F, 2.0F,
                                                   0x2u));
  check(events->size() == 3);
  check(has("local_object_lookup", 2));
  check(health_tick_called == false);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 0, 1.0F, 2.0F,
                                                   0x2u));
  check(health_tick_called == false);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -1, 1.0F, 2.0F,
                                                   0x2u));
  check(events->size() == 4);
  check(has("health_tick", 3));
  check(health_tick_called);
  check(health_tick_mode == 3);
  check(float_bits(health_tick_amount) == 0u);
  check(health_tick_calls == 1);
  check(zoom_in_argument == 0);
  check(zoom_out_argument == 0);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -120, 1.0F, 2.0F,
                                                   0x3u));
  check(events->size() == 3);
  check(has("zoom_out", 2));
  check(wheel_gate_calls == 1);
  check(health_tick_called == false);
}

void test_mouse_wheel_state_width() {
  OpaqueCellModeStrategy strategy{};
  reset();
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 240, 1.0F, 2.0F,
                                                   0x100u));
  check(events->size() == 2);
  check(wheel_gate_calls == 0);
  check(zoom_in_argument == 240);

  reset();
  wheel_gate_result = false;
  check(!cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 240, 1.0F, 2.0F,
                                                    0x102u));
  check(events->size() == 3);
  check(has("local_object_lookup", 2));
  check(health_tick_called == false);
}

void test_health_tick_raw_boundary() {
  HealthTickTarget sentinel_probe = &openspore_w8_probe_sentinel_health_tick;
  HealthTickTarget residue_probe = &openspore_w8_probe_residue_health_tick;
  HealthTickRawObservation observed{};
  check(sizeof(sentinel_probe) == 4);
  check(sizeof(residue_probe) == 4);
  check(reinterpret_cast<std::uintptr_t>(sentinel_probe) !=
        reinterpret_cast<std::uintptr_t>(residue_probe));

  observed = HealthTickRawObservation{};
  call_health_tick_raw_00e7d070(sentinel_probe, kHealthTickDeadReceiver, 3,
                                0.0F, 0x016b3c14u, &observed);
  check(observed.sentinel_eax == 0x016b3c14u);
  check(observed.sentinel_eax == kNativeSentinelWord);
  check(observed.mode_word ==
        static_cast<TargetWord>(kHealthTickMode) + kProbeWordWitnessLow);
  check(observed.amount_bits == 0u + kProbeWordWitnessHigh);

  observed = HealthTickRawObservation{};
  call_health_tick_raw_00e7d070(sentinel_probe, kHealthTickDeadReceiver, 3,
                                0.0F, 0x00c0ffeeu, &observed);
  check(observed.sentinel_eax == 0x00c0ffeeu);
  check(observed.sentinel_eax != kNativeSentinelWord);
  check(observed.mode_word ==
        static_cast<TargetWord>(kHealthTickMode) + kProbeWordWitnessLow);
  check(observed.amount_bits == 0u + kProbeWordWitnessHigh);

  observed = HealthTickRawObservation{};
  call_health_tick_raw_00e7d070(sentinel_probe, kHealthTickDeadReceiver, 3,
                                0.0F, 0u, &observed);
  check(observed.sentinel_eax == 0u);
  check(observed.mode_word ==
        static_cast<TargetWord>(kHealthTickMode) + kProbeWordWitnessLow);

  observed = HealthTickRawObservation{};
  call_health_tick_raw_00e7d070(residue_probe, kHealthTickDeadReceiver, 3, 0.0F,
                                0x016b3c14u, &observed);
  check(observed.residue_ecx == kHealthTickDeadReceiver);
  check(observed.residue_ecx == 0xffffffffu);
  check(observed.mode_word ==
        static_cast<TargetWord>(kHealthTickMode) + kProbeWordWitnessLow);
  check(observed.amount_bits == 0u + kProbeWordWitnessHigh);

  observed = HealthTickRawObservation{};
  call_health_tick_raw_00e7d070(residue_probe, 0x11223344u, -7, 2.5F, 0u,
                                &observed);
  check(observed.residue_ecx == 0x11223344u);
  check(observed.residue_ecx != kHealthTickDeadReceiver);
  check(observed.mode_word ==
        static_cast<TargetWord>(-7) + kProbeWordWitnessLow);
  check(observed.amount_bits == float_bits(2.5F) + kProbeWordWitnessHigh);
}

void test_health_tick_repeated_call_stability() {
  HealthTickTarget probe = &openspore_w8_probe_sentinel_health_tick;
  HealthTickRawObservation observed{};
  std::uint32_t guard[8];
  for (std::size_t index = 0; index < 8; ++index) {
    guard[index] = 0x24681357u + static_cast<std::uint32_t>(index);
  }
  std::uint32_t* const guard_base = &guard[0];
  for (int iteration = 0; iteration < 4096; ++iteration) {
    call_health_tick_raw_00e7d070(
        probe, kHealthTickDeadReceiver, kHealthTickMode + (iteration & 0x3),
        static_cast<float>(iteration), 0x016b3c14u, &observed);
    check(observed.sentinel_eax == 0x016b3c14u);
    check(observed.mode_word ==
          static_cast<TargetWord>(kHealthTickMode + (iteration & 0x3)) +
              kProbeWordWitnessLow);
    check(observed.amount_bits ==
          float_bits(static_cast<float>(iteration)) + kProbeWordWitnessHigh);
  }
  check(&guard[0] == guard_base);
  for (std::size_t index = 0; index < 8; ++index) {
    check(guard[index] == 0x24681357u + static_cast<std::uint32_t>(index));
  }
}

void test_health_tick_stack_balance() {
  HealthTickTarget probe = &openspore_w8_probe_sentinel_health_tick;
  HealthTickRawObservation observed{};
  std::uint32_t canary[16];
  for (std::size_t index = 0; index < 16; ++index) {
    canary[index] = 0xa5a50000u | static_cast<std::uint32_t>(index);
  }
  std::uint32_t* const canary_base = &canary[0];
  std::uint32_t* const anchor_before = &canary[8];
  std::uint32_t before_word = 0x13572468u;
  const std::uint32_t before_copy = before_word;

  for (int iteration = 0; iteration < 200000; ++iteration) {
    call_health_tick_raw_00e7d070(
        probe, kHealthTickDeadReceiver, 3, 0.0F,
        0x016b3c14u + static_cast<TargetWord>(iteration & 0xffu), &observed);
    check(observed.sentinel_eax ==
          (0x016b3c14u + static_cast<TargetWord>(iteration & 0xffu)));
    check(observed.mode_word ==
          static_cast<TargetWord>(kHealthTickMode) + kProbeWordWitnessLow);
    check(observed.amount_bits == 0u + kProbeWordWitnessHigh);
  }

  check(&canary[0] == canary_base);
  check(&canary[8] == anchor_before);
  for (std::size_t index = 0; index < 16; ++index) {
    check(canary[index] == (0xa5a50000u | static_cast<std::uint32_t>(index)));
  }
  check(before_word == before_copy);
}

void test_health_tick_sentinel_paths() {
  OpaqueCellModeStrategy strategy{};

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  g_object_sentinel_016b3c14 = 0x016b3c14u;
  cell_object.health_0900 = 0x24681357;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -240, 1.0F, 2.0F,
                                                   0x2u));
  const char* const order[] = {"mouse_wheel", "wheel_gate",
                               "local_object_lookup", "health_tick"};
  check_order(order, 4);
  check(health_tick_calls == 1);
  check(health_tick_mode == kHealthTickMode);
  check(float_bits(health_tick_amount) == 0u);
  check(cell_object.health_0900 == static_cast<std::int32_t>(0x24681357u));
  check(cell_object.health_phase_0904 == 0.0F);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  g_object_sentinel_016b3c14 = 0x00c0ffeeu;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -240, 1.0F, 2.0F,
                                                   0x2u));
  check(events->size() == 4);
  check(has("health_tick", 3));
  check(health_tick_mode == kHealthTickMode);
  check(float_bits(health_tick_amount) == 0u);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  g_object_sentinel_016b3c14 = 0u;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -240, 1.0F, 2.0F,
                                                   0x2u));
  check(events->size() == 4);
  check(has("health_tick", 3));
  check(health_tick_mode == kHealthTickMode);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  g_object_sentinel_016b3c14 = 0x016b3c14u;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -960, 1.0F, 2.0F,
                                                   0x2u));
  check(events->size() == 4);
  check(has("health_tick", 3));
  check(health_tick_mode == kHealthTickMode);
  check(float_bits(health_tick_amount) == 0u);
  check(zoom_in_argument == 0);
  check(zoom_out_argument == 0);

  reset();
  wheel_gate_result = false;
  lookup_result = 0x00c0ffeeu;
  g_object_sentinel_016b3c14 = 0x016b3c14u;
  check(cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, 0, 1.0F, 2.0F,
                                                   0x2u));
  check(health_tick_called == false);
  check(health_tick_calls == 0);

  reset();
  wheel_gate_result = false;
  lookup_result = 0u;
  check(!cell_mode_strategy_on_mouse_wheel_00e7d660(&strategy, -240, 1.0F, 2.0F,
                                                    0x2u));
  check(health_tick_called == false);
  check(health_tick_calls == 0);

  reset();
  g_object_sentinel_016b3c14 = 0x016b3c14u;
  check(kHealthTickDeadReceiver != 0u);
  check(kHealthTickDeadReceiver != kNativeSentinelWord);
}

void test_global_reload() {
  OpaqueCellModeStrategy strategy{};
  reset();
  sub_object_mode = 1;
  repoint_cell_on_pick = true;
  check(cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                  0u));
  check(g_cell_input_state_016b3c0c == &repointed_cell);
  check(last_input == &cell_object.input);
  check(repointed_cell.selected_object_00c4 ==
        static_cast<TargetWord>(
            reinterpret_cast<std::uintptr_t>(&picked_object)));
  check(cell_object.selected_object_00c4 == 0x99999999u);

  reset();
  repoint_cell_on_pick = true;
  check(!cell_mode_strategy_on_mouse_down_00e6c860(&strategy, 0x3e8, 1.0F, 2.0F,
                                                   0u));
  check(repointed_cell.selected_object_00c4 == 0u);
  check(cell_object.selected_object_00c4 == 0x99999999u);

  reset();
  check(cell_mode_strategy_on_mouse_up_00e5c0f0(&strategy, 0x3e8, 1.0F, 2.0F,
                                                0u));
  check(cell_object.health_0900 == 0);
  check(float_bits(cell_object.health_phase_0904) == 0u);
  check(raycast_buffer == &cell_object.unproject_out_0100[0]);
}

int run_tests() {
  std::vector<std::string> test_events;
  events = &test_events;
  test_constants();
  test_wheel_step_quotient();
  test_mouse_down_raycast_path();
  test_mouse_down_handle_lifecycle();
  test_mouse_up();
  test_mouse_wheel_observed_gate();
  test_mouse_wheel_zoom_branch();
  test_mouse_wheel_health_branch();
  test_mouse_wheel_state_width();
  test_health_tick_raw_boundary();
  test_health_tick_repeated_call_stability();
  test_health_tick_stack_balance();
  test_health_tick_sentinel_paths();
  test_global_reload();
  events = nullptr;
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_game_input_wave8::run_tests();
}

#undef TEST_THISCALL
#undef TEST_CDECL
