#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-game-input-wave8 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_GAME_INPUT_WAVE8_THISCALL __thiscall
#define PKG_GAME_INPUT_WAVE8_CDECL __cdecl
#else
#define PKG_GAME_INPUT_WAVE8_THISCALL __attribute__((thiscall))
#define PKG_GAME_INPUT_WAVE8_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_game_input_wave8 {

using TargetWord = std::uint32_t;
using MouseState = TargetWord;
using MouseButton = std::int32_t;
using WheelDelta = std::int32_t;

inline constexpr MouseButton kMouseButtonLeft = 0x3e8;
inline constexpr MouseButton kMouseButtonRight = 0x3ea;
inline constexpr std::uint8_t kMouseStateDownRaycastMask = 0x3;
inline constexpr std::uint8_t kMouseStateWheelZoomMask = 0x1;
inline constexpr std::uint8_t kMouseStateWheelHealthMask = 0x2;
inline constexpr std::int32_t kRaycastCapacity = 0x200;
inline constexpr TargetWord kRaycastMaxDistanceBits = 0x7f7fffffu;
inline constexpr WheelDelta kWheelStep = 0x78;
inline constexpr std::int32_t kHealthTickMode = 3;
inline constexpr TargetWord kHealthTickDeadReceiver = 0xffffffffu;
inline constexpr std::int32_t kSubObjectModeOne = 1;
inline constexpr std::int32_t kSubObjectModeTwo = 2;

inline float float_from_bits(TargetWord bits) {
  float value = 0.0F;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

inline TargetWord float_bits(float value) {
  TargetWord bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

inline constexpr std::uint8_t mouse_state_low_byte(MouseState state) {
  return static_cast<std::uint8_t>(state & 0xffu);
}

inline constexpr WheelDelta wheel_step_quotient(WheelDelta delta) {
  return delta / kWheelStep;
}

struct alignas(4) Vec3Raw {
  std::uint32_t x;
  std::uint32_t y;
  std::uint32_t z;
};

struct alignas(4) OpaqueGameInput {
  TargetWord keys[8];
  TargetWord key_modifiers;
  std::uint8_t mouse_buttons[8];
  float mouse_x;
  float mouse_y;
  std::int32_t mouse_button;
  float click_x;
  float click_y;
  MouseState mouse_state;
  std::int32_t mouse_wheel;
};

struct alignas(4) OpaqueCellInputState {
  OpaqueGameInput input;
  std::byte opaque_048_0c0[0x78];
  TargetWord pick_result_00c0;
  std::uint32_t selected_object_00c4;
  std::byte opaque_0c8_100[0x38];
  std::uint8_t unproject_out_0100[0x800];
  std::int32_t health_0900;
  float health_phase_0904;
  std::byte opaque_908_937[0x2f];
  std::uint8_t ui_flag_0937;
};

struct alignas(4) OpaqueCellObjectIndex {
  std::byte opaque[0x40e0];
};

struct alignas(4) OpaqueCellGame {
  std::byte opaque_000[0x1c];
  OpaqueCellObjectIndex object_index_01c;
  TargetWord scene_object_40fc;
  std::byte opaque_4100_411c[0x1c];
  TargetWord local_object_411c;
};

struct alignas(4) OpaqueCellObject {
  std::byte opaque[0x1];
};

struct alignas(4) OpaqueCellSubObject {
  std::byte opaque[0xd4];
  std::int32_t mode_00d4;
};

struct alignas(4) OpaqueCellModeStrategy {
  std::byte opaque[0xc];
};

struct alignas(4) OpaqueRenderer {
  std::byte opaque[0x1];
};

struct alignas(4) OpaqueLayer {
  std::byte opaque[0x1];
};

struct alignas(4) OpaqueMouseDownLocals {
  std::int32_t handle;
  Vec3Raw raycast_in_0;
  Vec3Raw raycast_in_1;
  std::uint8_t out_buffer[0x200];
};

struct alignas(4) OpaqueMouseUpLocals {
  Vec3Raw raycast_in_1;
  Vec3Raw raycast_in_0;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uintptr_t) == 4, "target raw addresses are 32-bit");
static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(MouseState) == 4, "mouse state words are 32-bit");
static_assert(sizeof(MouseButton) == 4, "mouse button words are 32-bit");
static_assert(sizeof(WheelDelta) == 4, "wheel delta words are 32-bit");
static_assert(sizeof(float) == 4, "target floats are 32-bit");
static_assert(sizeof(Vec3Raw) == 12, "unproject triple width");
static_assert(sizeof(OpaqueGameInput) == 0x48, "GameInput storage size");
static_assert(offsetof(OpaqueGameInput, mouse_buttons) == 0x24,
              "GameInput mouse button byte offset");
static_assert(offsetof(OpaqueGameInput, mouse_x) == 0x2c,
              "GameInput mouse X offset");
static_assert(offsetof(OpaqueGameInput, mouse_y) == 0x30,
              "GameInput mouse Y offset");
static_assert(offsetof(OpaqueGameInput, mouse_button) == 0x34,
              "GameInput active mouse button offset");
static_assert(offsetof(OpaqueGameInput, click_x) == 0x38,
              "GameInput click X offset");
static_assert(offsetof(OpaqueGameInput, click_y) == 0x3c,
              "GameInput click Y offset");
static_assert(offsetof(OpaqueGameInput, mouse_state) == 0x40,
              "GameInput mouse state offset");
static_assert(offsetof(OpaqueGameInput, mouse_wheel) == 0x44,
              "GameInput wheel accumulator offset");
static_assert(offsetof(OpaqueCellInputState, input) == 0,
              "Cell state starts with GameInput");
static_assert(offsetof(OpaqueCellInputState, pick_result_00c0) == 0xc0,
              "Cell pick result offset");
static_assert(offsetof(OpaqueCellInputState, selected_object_00c4) == 0xc4,
              "Cell selected object offset");
static_assert(offsetof(OpaqueCellInputState, unproject_out_0100) == 0x100,
              "Cell unproject output buffer offset");
static_assert(offsetof(OpaqueCellInputState, health_0900) == 0x900,
              "Cell health offset");
static_assert(offsetof(OpaqueCellInputState, health_phase_0904) == 0x904,
              "Cell health phase offset");
static_assert(offsetof(OpaqueCellInputState, ui_flag_0937) == 0x937,
              "Cell UI flag offset");
static_assert(sizeof(OpaqueCellInputState) == 0x938, "Cell state storage size");
static_assert(offsetof(OpaqueCellGame, object_index_01c) == 0x1c,
              "Cell object index offset");
static_assert(offsetof(OpaqueCellGame, scene_object_40fc) == 0x40fc,
              "Cell scene object offset");
static_assert(offsetof(OpaqueCellGame, local_object_411c) == 0x411c,
              "Cell local object index offset");
static_assert(sizeof(OpaqueCellGame) == 0x4120, "Cell game storage size");
static_assert(sizeof(OpaqueCellObjectIndex) == 0x40e0,
              "Cell object index storage size");
static_assert(offsetof(OpaqueCellSubObject, mode_00d4) == 0xd4,
              "Cell sub-object mode offset");
static_assert(sizeof(OpaqueCellModeStrategy) == 0xc,
              "Cell mode strategy storage size");
static_assert(offsetof(OpaqueMouseDownLocals, raycast_in_0) == 0x4,
              "mouse-down first unproject triple offset");
static_assert(offsetof(OpaqueMouseDownLocals, raycast_in_1) == 0x10,
              "mouse-down second unproject triple offset");
static_assert(offsetof(OpaqueMouseDownLocals, out_buffer) == 0x1c,
              "mouse-down raycast buffer offset");
static_assert(sizeof(OpaqueMouseDownLocals) == 0x21c,
              "mouse-down local frame size");
static_assert(offsetof(OpaqueMouseUpLocals, raycast_in_1) == 0x0,
              "mouse-up second unproject triple offset");
static_assert(offsetof(OpaqueMouseUpLocals, raycast_in_0) == 0xc,
              "mouse-up first unproject triple offset");
static_assert(sizeof(OpaqueMouseUpLocals) == 0x18, "mouse-up local frame size");

using GameInputMouseDown = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueGameInput*, MouseButton, float, float, MouseState);
using GameInputMouseUp = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(OpaqueGameInput*,
                                                              MouseButton,
                                                              float, float,
                                                              MouseState);
using GameInputMouseWheel = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueGameInput*, WheelDelta, float, float, MouseState);
using PickObject = OpaqueCellObject*(PKG_GAME_INPUT_WAVE8_CDECL*)();
using OnObjectClicked = void(PKG_GAME_INPUT_WAVE8_CDECL*)(OpaqueCellObject*);
using HandleReset = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(std::int32_t*);
using ResolveSubObject =
    OpaqueCellSubObject*(PKG_GAME_INPUT_WAVE8_CDECL*)(std::int32_t*);
using HandleRelease = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(std::int32_t*);
using RendererGet = OpaqueRenderer*(PKG_GAME_INPUT_WAVE8_CDECL*)();
using RendererLayerSlot =
    OpaqueLayer*(PKG_GAME_INPUT_WAVE8_THISCALL*)(OpaqueRenderer*);
using LayerUnproject = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(OpaqueLayer*, float,
                                                            float, Vec3Raw*,
                                                            Vec3Raw*);
using LayerUnprojectInt = void(PKG_GAME_INPUT_WAVE8_THISCALL*)(OpaqueLayer*,
                                                               Vec3Raw*,
                                                               Vec3Raw*);
using RaycastUnproject = std::int32_t(PKG_GAME_INPUT_WAVE8_CDECL*)(
    TargetWord, Vec3Raw*, Vec3Raw*, std::uint8_t*, std::int32_t, float);
using WheelGate = bool(PKG_GAME_INPUT_WAVE8_CDECL*)();
using LocalObjectLookup = TargetWord(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueCellObjectIndex*, TargetWord);
using ZoomOut = void(PKG_GAME_INPUT_WAVE8_CDECL*)(std::int32_t);
using ZoomIn = void(PKG_GAME_INPUT_WAVE8_CDECL*)(std::int32_t);
struct alignas(4) HealthTickRawObservation {
  TargetWord sentinel_eax;
  TargetWord residue_ecx;
  TargetWord mode_word;
  TargetWord amount_bits;
};

using HealthTickTarget = void(PKG_GAME_INPUT_WAVE8_CDECL*)(std::int32_t, float);

inline __attribute__((noinline)) void call_health_tick_raw_00e7d070(
    HealthTickTarget callee, TargetWord receiver_residue, std::int32_t mode,
    float amount, TargetWord sentinel, HealthTickRawObservation* observation) {
  struct alignas(4) HealthTickRawSlots {
    TargetWord residue;
    TargetWord sentinel;
    TargetWord callee_bits;
    TargetWord amount_bits;
    TargetWord mode_word;
    TargetWord seen_mode;
    TargetWord seen_amount;
    TargetWord seen_eax;
    TargetWord seen_ecx;
    TargetWord out_bits;
  };
  HealthTickRawObservation sink{};
  HealthTickRawObservation* const out =
      observation != nullptr ? observation : &sink;
  HealthTickRawSlots slots{};
  slots.residue = receiver_residue;
  slots.sentinel = sentinel;
  std::memcpy(&slots.callee_bits, &callee, sizeof(slots.callee_bits));
  slots.amount_bits = float_bits(amount);
  slots.mode_word = static_cast<TargetWord>(mode);
  std::memcpy(&slots.out_bits, &out, sizeof(slots.out_bits));
  const HealthTickRawSlots* base = &slots;
  TargetWord base_word = 0;
#if defined(_MSC_VER)
  __asm {
    push ebx
    mov ebx, base
    mov ecx, [ebx]
    mov eax, [ebx + 4]
    mov edx, [ebx + 8]
    push dword ptr [ebx + 12]
    push dword ptr [ebx + 16]
    call edx
    mov edx, [esp]
    mov [ebx + 20], edx
    mov edx, [esp + 4]
    mov [ebx + 24], edx
    mov [ebx + 28], eax
    mov [ebx + 32], ecx
    mov edx, [ebx + 36]
    mov eax, [ebx + 28]
    mov [edx], eax
    mov eax, [ebx + 32]
    mov [edx + 4], eax
    mov eax, [ebx + 20]
    mov [edx + 8], eax
    mov eax, [ebx + 24]
    mov [edx + 12], eax
    add esp, 8
    pop ebx
  }
#else
  __asm__ __volatile__("movl %[base], %[out]"
                       : [out] "=r"(base_word)
                       : [base] "m"(base)
                       : "memory");
  __asm__ __volatile__(
      "movl %[base], %%ebx\n\t"
      "movl 0(%%ebx), %%ecx\n\t"
      "movl 4(%%ebx), %%eax\n\t"
      "movl 8(%%ebx), %%edx\n\t"
      "pushl 12(%%ebx)\n\t"
      "pushl 16(%%ebx)\n\t"
      "call *%%edx\n\t"
      "movl 0(%%esp), %%edx\n\t"
      "movl %%edx, 20(%%ebx)\n\t"
      "movl 4(%%esp), %%edx\n\t"
      "movl %%edx, 24(%%ebx)\n\t"
      "movl %%eax, 28(%%ebx)\n\t"
      "movl %%ecx, 32(%%ebx)\n\t"
      "movl 36(%%ebx), %%edx\n\t"
      "movl 28(%%ebx), %%eax\n\t"
      "movl %%eax, 0(%%edx)\n\t"
      "movl 32(%%ebx), %%eax\n\t"
      "movl %%eax, 4(%%edx)\n\t"
      "movl 20(%%ebx), %%eax\n\t"
      "movl %%eax, 8(%%edx)\n\t"
      "movl 24(%%ebx), %%eax\n\t"
      "movl %%eax, 12(%%edx)\n\t"
      "addl $8, %%esp\n\t"
      :
      : [base] "r"(base_word)
      : "eax", "ebx", "ecx", "edx", "memory", "cc");
#endif
  static_cast<void>(base_word);
}

static_assert(sizeof(GameInputMouseDown) == 4, "mouse-down port is 32-bit");
static_assert(sizeof(GameInputMouseUp) == 4, "mouse-up port is 32-bit");
static_assert(sizeof(GameInputMouseWheel) == 4, "mouse-wheel port is 32-bit");
static_assert(sizeof(PickObject) == 4, "pick port is 32-bit");
static_assert(sizeof(OnObjectClicked) == 4, "clicked port is 32-bit");
static_assert(sizeof(HandleReset) == 4, "handle reset port is 32-bit");
static_assert(sizeof(ResolveSubObject) == 4, "resolve port is 32-bit");
static_assert(sizeof(HandleRelease) == 4, "handle release port is 32-bit");
static_assert(sizeof(RendererGet) == 4, "renderer port is 32-bit");
static_assert(sizeof(RendererLayerSlot) == 4, "renderer layer port is 32-bit");
static_assert(sizeof(LayerUnproject) == 4, "unproject port is 32-bit");
static_assert(sizeof(LayerUnprojectInt) == 4,
              "integer unproject port is 32-bit");
static_assert(sizeof(RaycastUnproject) == 4, "raycast port is 32-bit");
static_assert(sizeof(WheelGate) == 4, "wheel gate port is 32-bit");
static_assert(sizeof(LocalObjectLookup) == 4, "object lookup port is 32-bit");
static_assert(sizeof(ZoomOut) == 4, "zoom-out port is 32-bit");
static_assert(sizeof(ZoomIn) == 4, "zoom-in port is 32-bit");
static_assert(sizeof(HealthTickTarget) == 4, "health-tick port is 32-bit");

using CellModeStrategyMouseDownAbi = bool(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueCellModeStrategy*, MouseButton, float, float, MouseState);
using CellModeStrategyMouseUpAbi = bool(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueCellModeStrategy*, MouseButton, float, float, MouseState);
using CellModeStrategyMouseWheelAbi = bool(PKG_GAME_INPUT_WAVE8_THISCALL*)(
    OpaqueCellModeStrategy*, WheelDelta, float, float, MouseState);

static_assert(sizeof(CellModeStrategyMouseDownAbi) == 4,
              "mouse-down ABI slot is 32-bit");
static_assert(sizeof(CellModeStrategyMouseUpAbi) == 4,
              "mouse-up ABI slot is 32-bit");
static_assert(sizeof(CellModeStrategyMouseWheelAbi) == 4,
              "mouse-wheel ABI slot is 32-bit");

struct NativePorts {
  static constexpr char boundary_metadata[] =
      "00697ab0 ECX GameInput plus button, x, y, state stack words, callee "
      "RET 0x10; "
      "00697af0 same four stack words, callee RET 0x10; "
      "00697b40 same four stack words, callee RET 0x10, reads the wheel word; "
      "00e6c780 no stack words, returns the picked object or zero; "
      "00e643e0 one cdecl object word, caller ADD ESP 4; "
      "00743b50 ECX handle word, stores zero, plain RET; "
      "00e4ce40 one cdecl handle word, caller ADD ESP 4, returns the resolved "
      "object; "
      "00e82130 ECX handle word, plain RET; "
      "0067dd10 no stack words, returns the renderer from 0x015fd8b0; "
      "renderer vtable plus 0x58 ECX renderer, no stack words, returns the "
      "layer; "
      "007c4730 ECX layer plus screen x, screen y, first triple pointer, "
      "second "
      "triple pointer, callee RET 0x10; "
      "007c4900 ECX layer plus first triple pointer, second triple pointer, "
      "callee RET 8; "
      "00e87200 six cdecl words, caller ADD ESP 0x18, returns the hit count; "
      "00b1fbf0 no stack words, AL gate, observed body returns one; "
      "0b721d0 ECX object index plus one index word, callee RET 4, clobbers "
      "ECX to 0xffffffff on the entry-found return; "
      "00e50f60 one cdecl int word, caller ADD ESP 4; "
      "00e51060 one cdecl raw delta word, caller ADD ESP 4; "
      "00e7d070 ECX receiver never read, exactly two stack words at ESP+0 and "
      "ESP+4 for the mode and the amount, plain callee RET, caller ADD ESP 8; "
      "the two words, the in-EAX sentinel, and the ECX residue are pushed and "
      "loaded only by call_health_tick_raw_00e7d070, and the port prototype is "
      "cdecl with two words because the i386 thiscall convention is "
      "callee-clean and would double-pop against the native caller-side ADD "
      "ESP 8";

  GameInputMouseDown mouse_down_00697ab0 = nullptr;
  GameInputMouseUp mouse_up_00697af0 = nullptr;
  GameInputMouseWheel mouse_wheel_00697b40 = nullptr;
  PickObject pick_object_00e6c780 = nullptr;
  OnObjectClicked on_object_clicked_00e643e0 = nullptr;
  HandleReset handle_reset_00743b50 = nullptr;
  ResolveSubObject resolve_sub_object_00e4ce40 = nullptr;
  HandleRelease handle_release_00e82130 = nullptr;
  RendererGet renderer_get_0067dd10 = nullptr;
  RendererLayerSlot renderer_layer_slot_58 = nullptr;
  LayerUnproject layer_unproject_007c4730 = nullptr;
  LayerUnprojectInt layer_unproject_int_007c4900 = nullptr;
  RaycastUnproject raycast_00e87200 = nullptr;
  WheelGate wheel_gate_00b1fbf0 = nullptr;
  LocalObjectLookup local_object_lookup_00b721d0 = nullptr;
  ZoomOut zoom_out_00e50f60 = nullptr;
  ZoomIn zoom_in_00e51060 = nullptr;
  HealthTickTarget health_tick_00e7d070 = nullptr;
};

extern OpaqueCellGame* g_cell_game_016b3c04;
extern OpaqueCellInputState* g_cell_input_state_016b3c0c;
extern TargetWord g_object_sentinel_016b3c14;
extern NativePorts g_game_input_wave8_ports;

extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_down_00e6c860(OpaqueCellModeStrategy*, MouseButton,
                                          float, float, MouseState);
extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_up_00e5c0f0(OpaqueCellModeStrategy*, MouseButton,
                                        float, float, MouseState);
extern "C" bool PKG_GAME_INPUT_WAVE8_THISCALL
cell_mode_strategy_on_mouse_wheel_00e7d660(OpaqueCellModeStrategy*, WheelDelta,
                                           float, float, MouseState);

#undef PKG_GAME_INPUT_WAVE8_THISCALL
#undef PKG_GAME_INPUT_WAVE8_CDECL

}
