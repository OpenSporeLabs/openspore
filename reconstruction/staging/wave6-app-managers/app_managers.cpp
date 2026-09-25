#include "app_managers.hpp"

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

AppManagerGlobals g_wave6_app_manager_globals{};

namespace {

void default_release(void*) {}

void PKG06_WAVE6_STDCALL destroy_mode_entry_range_007d87e0(
    OpaqueModeEntry* begin, OpaqueModeEntry* end) {
  for (; begin < end; begin = reinterpret_cast<OpaqueModeEntry*>(
                          reinterpret_cast<unsigned char*>(begin) + 0x18)) {
    const std::uint32_t name_begin = begin->name_word_08;
    const std::uint32_t name_end = begin->name_word_10;
    const std::uint32_t name_span =
        name_end - static_cast<std::uint32_t>(name_begin);
    if (static_cast<std::int32_t>(name_span) > 1 && name_begin != 0) {
      game_mode_manager_ports().release_00f47380(
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(name_begin)));
    }
    OpaqueMode* mode = begin->mode_00;
    if (mode != nullptr) {
      mode->vtable->slot_04(mode);
    }
  }
}

}

OpaqueGameModeManagerPorts& game_mode_manager_ports() {
  static OpaqueGameModeManagerPorts ports{&default_release};
  if (ports.release_00f47380 == nullptr) {
    ports.release_00f47380 = &default_release;
  }
  return ports;
}

extern "C" OpaqueAppGameModeManager* PKG06_WAVE6_CDECL
App_IGameModeManager_Get_0067dcd0() {
  return reinterpret_cast<OpaqueAppGameModeManager*>(
      static_cast<std::uintptr_t>(
          g_wave6_app_manager_globals.app_game_mode_manager_015fd894));
}

extern "C" OpaqueSimulatorGameModeManager* PKG06_WAVE6_CDECL
Simulator_cGameModeManager_Get_00b3d420() {
  return reinterpret_cast<OpaqueSimulatorGameModeManager*>(
      static_cast<std::uintptr_t>(
          g_wave6_app_manager_globals.simulator_game_mode_manager_0167eb2c));
}

extern "C" void PKG06_WAVE6_THISCALL
GameModeManagerVectorDestroy_007d8cc0(OpaqueGameModeManager* manager) {
  destroy_mode_entry_range_007d87e0(manager->modes_begin_14,
                                    manager->modes_end_18);
  OpaqueModeEntry* begin = manager->modes_begin_14;
  if (begin != nullptr) {
    const std::uint32_t* marker =
        reinterpret_cast<const std::uint32_t*>(begin) - 1;
    if (*marker != 0) {
      game_mode_manager_ports().release_00f47380(begin);
    }
  }
}

extern "C" void PKG06_WAVE6_THISCALL GameModeManagerDestructor_007d8d40(
    OpaqueGameModeManager* manager, std::uint8_t delete_flag) {
  static_cast<void>(delete_flag);
  manager->vtable_00 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x01412598u));
  manager->vtable_04 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x01412584u));
  manager->vtable_08 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x01412580u));
  OpaqueCameraManager* camera_manager = manager->camera_manager_2c;
  if (camera_manager != nullptr) {
    camera_manager->vtable->slot_0c(camera_manager);
  }
  GameModeManagerVectorDestroy_007d8cc0(manager);
  manager->vtable_08 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x013ef094u));
  manager->vtable_04 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x013eb394u));
  manager->vtable_00 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x013eb938u));
}

}

#undef PKG06_WAVE6_CDECL
#undef PKG06_WAVE6_STDCALL
#undef PKG06_WAVE6_THISCALL
