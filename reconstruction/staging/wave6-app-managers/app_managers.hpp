#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 app-manager reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "wave6 app-manager pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "wave6 app-manager words are 32-bit");

#if defined(_MSC_VER)
#define PKG06_WAVE6_CDECL __cdecl
#define PKG06_WAVE6_STDCALL __stdcall
#define PKG06_WAVE6_THISCALL __thiscall
#else
#define PKG06_WAVE6_CDECL __attribute__((cdecl))
#define PKG06_WAVE6_STDCALL __attribute__((stdcall))
#define PKG06_WAVE6_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_app_managers {

struct OpaqueAppGameModeManager;
struct OpaqueSimulatorGameModeManager;

struct AppManagerGlobals {
  std::uint32_t app_game_mode_manager_015fd894 = 0;
  std::uint32_t simulator_game_mode_manager_0167eb2c = 0;
};

extern AppManagerGlobals g_wave6_app_manager_globals;

struct OpaqueMode;
using ModeDispatch = void(PKG06_WAVE6_THISCALL*)(OpaqueMode*);

struct OpaqueModeVtable {
  void* slot_00 = nullptr;
  ModeDispatch slot_04 = nullptr;
};

struct OpaqueMode {
  OpaqueModeVtable* vtable = nullptr;
};

struct OpaqueModeEntry {
  OpaqueMode* mode_00 = nullptr;
  std::uint32_t mode_id_04 = 0;
  std::uint32_t name_word_08 = 0;
  std::uint32_t name_word_0c = 0;
  std::uint32_t name_word_10 = 0;
  std::uint32_t name_word_14 = 0;
};

struct OpaqueCameraManager;
using CameraManagerRelease = void(PKG06_WAVE6_THISCALL*)(OpaqueCameraManager*);

struct OpaqueCameraManagerVtable {
  void* slot_00 = nullptr;
  void* slot_04 = nullptr;
  void* slot_08 = nullptr;
  CameraManagerRelease slot_0c = nullptr;
};

struct OpaqueCameraManager {
  OpaqueCameraManagerVtable* vtable = nullptr;
};

struct OpaqueViewer;

struct OpaqueGameModeManager {
  void* vtable_00 = nullptr;
  void* vtable_04 = nullptr;
  void* vtable_08 = nullptr;
  std::int32_t ref_count_0c = 0;
  std::uint8_t field_10 = 0;
  std::uint8_t padding_11[3] = {};
  OpaqueModeEntry* modes_begin_14 = nullptr;
  OpaqueModeEntry* modes_end_18 = nullptr;
  OpaqueModeEntry* modes_capacity_1c = nullptr;
  std::uint32_t modes_word_20 = 0;
  std::uint32_t modes_word_24 = 0;
  std::int32_t active_index_28 = 0;
  OpaqueCameraManager* camera_manager_2c = nullptr;
  OpaqueViewer* viewer_30 = nullptr;
};

struct OpaqueGameModeManagerPorts {
  using Release = void (*)(void*);
  Release release_00f47380 = nullptr;
};

OpaqueGameModeManagerPorts& game_mode_manager_ports();

static_assert(sizeof(OpaqueModeEntry) == 0x18, "wave6 mode entry stride");
static_assert(offsetof(OpaqueGameModeManager, modes_begin_14) == 0x14,
              "wave6 mode vector begin offset");
static_assert(offsetof(OpaqueGameModeManager, modes_end_18) == 0x18,
              "wave6 mode vector end offset");
static_assert(offsetof(OpaqueGameModeManager, modes_capacity_1c) == 0x1c,
              "wave6 mode vector capacity offset");
static_assert(offsetof(OpaqueGameModeManager, active_index_28) == 0x28,
              "wave6 active index offset");
static_assert(offsetof(OpaqueGameModeManager, camera_manager_2c) == 0x2c,
              "wave6 camera manager offset");
static_assert(sizeof(OpaqueGameModeManager) == 0x34, "wave6 mode manager size");

extern "C" OpaqueAppGameModeManager* PKG06_WAVE6_CDECL
App_IGameModeManager_Get_0067dcd0();

extern "C" OpaqueSimulatorGameModeManager* PKG06_WAVE6_CDECL
Simulator_cGameModeManager_Get_00b3d420();

extern "C" void PKG06_WAVE6_THISCALL
GameModeManagerVectorDestroy_007d8cc0(OpaqueGameModeManager*);

extern "C" void PKG06_WAVE6_THISCALL GameModeManagerDestructor_007d8d40(
    OpaqueGameModeManager*, std::uint8_t delete_flag);

}

#undef PKG06_WAVE6_CDECL
#undef PKG06_WAVE6_STDCALL
#undef PKG06_WAVE6_THISCALL
