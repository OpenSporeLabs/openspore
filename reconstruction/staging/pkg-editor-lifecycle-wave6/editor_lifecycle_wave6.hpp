#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "editor lifecycle wave6 reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_editor_lifecycle_wave6 {

static_assert(sizeof(void*) == 4, "wave6 target pointers are 32-bit");
static_assert(sizeof(float) == 4, "wave6 target floats are 32-bit");

struct OpaqueManager;

struct OpaqueEditor {
  alignas(4) std::array<std::byte, 0x600> bytes{};
};

inline constexpr std::size_t kOffsetManager = 0x20;
inline constexpr std::size_t kOffsetMapSentinel = 0x458;
inline constexpr std::size_t kOffsetMapRight = 0x45c;
inline constexpr std::size_t kOffsetMapCount = 0x460;
inline constexpr std::size_t kOffsetMapBytes = 0x464;
inline constexpr std::size_t kOffsetMapTail = 0x468;
inline constexpr std::size_t kOffsetDefaultScalar = 0x6c;
inline constexpr std::size_t kOffsetActive = 0x2b0;
inline constexpr std::size_t kOffsetMode = 0x31c;
inline constexpr std::size_t kOffsetClockBase = 0x438;
inline constexpr std::size_t kOffsetClockAccumulator = 0x448;
inline constexpr std::size_t kOffsetMessageFlag384 = 0x384;
inline constexpr std::size_t kOffsetMessageFlag1c0 = 0x1c0;
inline constexpr std::size_t kOffsetMessageFlag385 = 0x385;
inline constexpr std::size_t kOffsetMessageFlag389 = 0x389;
inline constexpr std::size_t kOffsetMessageFlag390 = 0x390;
inline constexpr std::size_t kOffsetMessageState = 0x37c;
inline constexpr std::size_t kOffsetMessageStateValue = 0x378;
inline constexpr std::size_t kOffsetMessagePayloadOwner = 0x1bc;
inline constexpr std::size_t kOffsetMessageSource = 0x424;
inline constexpr std::size_t kOffsetMessageFlag4a4 = 0x4a4;
inline constexpr std::size_t kOffsetMessageTimer = 0x4a8;
inline constexpr std::size_t kOffsetMessagePending = 0x4a4;
inline constexpr std::size_t kOffsetMessageKey = 0x88;
inline constexpr std::size_t kOffsetMessageKey2 = 0xbc;
inline constexpr std::size_t kOffsetMessageKey3 = 0xc4;
inline constexpr std::size_t kOffsetMessageKey4 = 0xcc;
inline constexpr std::size_t kOffsetMessageSnapshotClock = 0x430;
inline constexpr std::size_t kOffsetTimerLow = 0x5a8;
inline constexpr std::size_t kOffsetExitRelease = 0x5d4;
inline constexpr std::size_t kOffsetBlockedState = 0x4c8;
inline constexpr std::size_t kOffsetBlockedOwner = 0x84;
inline constexpr std::size_t kOffsetExitObjectE0 = 0xe0;
inline constexpr std::size_t kOffsetExitObject94 = 0x94;
inline constexpr std::size_t kOffsetExitModeArg = 0x98;
inline constexpr std::size_t kOffsetExitModeArg2 = 0x9c;
inline constexpr std::size_t kOffsetObjectA0 = 0xa0;
inline constexpr std::size_t kOffsetObjectA8 = 0xa8;
inline constexpr std::size_t kOffsetObjectAc = 0xac;
inline constexpr std::size_t kOffsetObject84 = 0x84;
inline constexpr std::size_t kOffsetObject8c = 0x8c;
inline constexpr std::size_t kOffsetObject88 = 0x88;
inline constexpr std::size_t kOffsetObject15c = 0x15c;
inline constexpr std::size_t kOffsetObject90 = 0x90;
inline constexpr std::size_t kOffsetGlobalFlag5c0 = 0x5c0;
inline constexpr std::size_t kOffsetExitMode = 0x31c;
inline constexpr std::size_t kOffsetExitActive = 0x2b0;

enum class NativeOp : std::uint16_t {
  none,
  dispose_self_1c,
  dispose_remove_hash,
  dispose_acquire_app,
  dispose_render_2c,
  dispose_helper,
  dispose_release_prepare,
  dispose_release_object,
  dispose_release_virtual,
  dispose_shadow_0018,
  dispose_world_0050,
  dispose_viewer_prepare,
  dispose_viewer_reset,
  dispose_viewer_free,
  dispose_preferences,
  dispose_completion,
  initialize_map_prepare,
  initialize_manager_0050,
  initialize_manager_0020,
  initialize_register_hash,
  initialize_services,
  initialize_required_008de1a0,
  initialize_late,
  initialize_listener,
  exit_slot_0034,
  exit_property_int,
  exit_phase,
  exit_release_0008,
  exit_set_mode,
  exit_release_0004,
  exit_accumulate,
  exit_cleanup,
  update_clock_query,
  update_clock_release,
  update_clock_expired,
  update_blocking_10,
  update_timer_gate,
  update_timer_expire,
  update_main,
  update_mode,
  update_play,
  update_finish,
  message_route,
  message_object_000c,
  message_commit,
  message_release,
};

struct NativeCall {
  NativeOp operation = NativeOp::none;
  OpaqueEditor* editor = nullptr;
  std::uint32_t address = 0;
  std::uint32_t slot = 0;
  std::uint32_t first = 0;
  std::uint32_t second = 0;
  std::uint32_t third = 0;
  std::uint32_t fourth = 0;
  std::uint32_t fifth = 0;
  std::int32_t signed_word = 0;
  std::uint64_t qword = 0;
  float first_scalar = 0.0F;
  float second_scalar = 0.0F;
  void* pointer = nullptr;
};

struct NativeResult {
  bool boolean = false;
  std::int32_t signed_word = 0;
  std::uint32_t word = 0;
  std::uint64_t qword = 0;
  void* pointer = nullptr;
};

using NativeCallCallback = NativeResult (*)(const NativeCall&);

struct NativePorts {
  static constexpr char boundary_metadata[] =
      "00576c50: ECX, no stack arguments, AL true, plain RET; "
      "00584300: ECX plus one stack manager, AL result, RET 4; "
      "00587a20: ECX, no stack arguments, void-like, plain RET; "
      "0058be50: ECX plus two stack floats, void-like, RET 8; "
      "00591fa0: ECX plus message id and payload stack words, AL result, RET 8";

  NativeCallCallback call = nullptr;
};

struct OpaqueGlobals {
  const float* source_01465544 = nullptr;
  void** global_service_015eebec = nullptr;
};

extern OpaqueGlobals g_editor_lifecycle_wave6_globals;
extern NativePorts g_editor_lifecycle_wave6_ports;

extern "C" bool __thiscall editor_dispose_00576c50(OpaqueEditor* editor);
extern "C" bool __thiscall editor_initialize_00584300(OpaqueEditor* editor,
                                                      OpaqueManager* manager);
extern "C" void __thiscall editor_on_exit_00587a20(OpaqueEditor* editor);
extern "C" void __thiscall editor_update_0058be50(OpaqueEditor* editor,
                                                  float first_delta,
                                                  float second_delta);
extern "C" bool __thiscall editor_handle_message_00591fa0(
    OpaqueEditor* editor, std::uint32_t message_id, void* message);

}
