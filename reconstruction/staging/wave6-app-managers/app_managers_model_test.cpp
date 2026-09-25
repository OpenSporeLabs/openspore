#include "app_managers.hpp"

using namespace openspore::reconstruction::wave6_app_managers;

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

namespace {

std::vector<std::string> trace;
void* last_release = nullptr;

#if defined(_MSC_VER)
#define TEST_CDECL __cdecl
#define TEST_THISCALL __thiscall
#else
#define TEST_CDECL __attribute__((cdecl))
#define TEST_THISCALL __attribute__((thiscall))
#endif

void release_callback(void* pointer) {
  trace.emplace_back("release");
  last_release = pointer;
}

void TEST_THISCALL entry_owner_dispatch(OpaqueMode* owner) {
  assert(owner != nullptr);
  trace.emplace_back("entry-owner");
}

void TEST_THISCALL active_mode_dispatch(OpaqueCameraManager* mode) {
  assert(mode != nullptr);
  trace.emplace_back("active");
}

void reset() {
  trace.clear();
  last_release = nullptr;
}

void test_service_accessors_keep_roots_distinct() {
  g_wave6_app_manager_globals.app_game_mode_manager_015fd894 = 0x11111111u;
  g_wave6_app_manager_globals.simulator_game_mode_manager_0167eb2c =
      0x22222222u;
  assert(reinterpret_cast<std::uintptr_t>(
             App_IGameModeManager_Get_0067dcd0()) == 0x11111111u);
  assert(reinterpret_cast<std::uintptr_t>(
             Simulator_cGameModeManager_Get_00b3d420()) == 0x22222222u);
  g_wave6_app_manager_globals.app_game_mode_manager_015fd894 = 0;
  g_wave6_app_manager_globals.simulator_game_mode_manager_0167eb2c = 0;
  assert(App_IGameModeManager_Get_0067dcd0() == nullptr);
  assert(Simulator_cGameModeManager_Get_00b3d420() == nullptr);
}

void test_destructor_order_and_null_paths() {
  reset();
  game_mode_manager_ports().release_00f47380 = &release_callback;

  OpaqueModeVtable owner_vtable{};
  owner_vtable.slot_04 = &entry_owner_dispatch;
  OpaqueMode owner{&owner_vtable};
  OpaqueCameraManagerVtable active_vtable{};
  active_vtable.slot_0c = &active_mode_dispatch;
  OpaqueCameraManager active{&active_vtable};

  struct Allocation {
    std::uint32_t marker;
    OpaqueModeEntry entries[2];
  } allocation{};
  allocation.marker = 1;
  allocation.entries[0].mode_00 = &owner;
  allocation.entries[0].name_word_08 = 0x3000u;
  allocation.entries[0].name_word_10 = 0x3004u;
  allocation.entries[1].mode_00 = nullptr;
  allocation.entries[1].name_word_08 = 0x4000u;
  allocation.entries[1].name_word_10 = 0x4000u;

  OpaqueGameModeManager manager{};
  manager.modes_begin_14 = allocation.entries;
  manager.modes_end_18 = allocation.entries + 2;
  manager.modes_capacity_1c = allocation.entries + 2;
  manager.camera_manager_2c = &active;

  GameModeManagerDestructor_007d8d40(&manager, 0);
  assert(trace == std::vector<std::string>(
                      {"active", "release", "entry-owner", "release"}));
  assert(last_release == allocation.entries);
  assert(reinterpret_cast<std::uintptr_t>(manager.vtable_00) == 0x013eb938u);
  assert(reinterpret_cast<std::uintptr_t>(manager.vtable_04) == 0x013eb394u);
  assert(reinterpret_cast<std::uintptr_t>(manager.vtable_08) == 0x013ef094u);

  reset();
  manager.camera_manager_2c = nullptr;
  manager.modes_begin_14 = nullptr;
  manager.modes_end_18 = nullptr;
  manager.modes_capacity_1c = nullptr;
  GameModeManagerDestructor_007d8d40(&manager, 1);
  assert(trace.empty());
  assert(last_release == nullptr);

  game_mode_manager_ports().release_00f47380 = nullptr;
}

void test_entry_span_and_owner_rules() {
  reset();
  game_mode_manager_ports().release_00f47380 = &release_callback;
  OpaqueModeVtable owner_vtable{};
  owner_vtable.slot_04 = &entry_owner_dispatch;
  OpaqueMode owner{&owner_vtable};
  struct Allocation {
    std::uint32_t marker;
    OpaqueModeEntry entries[2];
  } allocation{};
  allocation.marker = 0;
  allocation.entries[0].mode_00 = &owner;
  allocation.entries[0].name_word_08 = 0x5000u;
  allocation.entries[0].name_word_10 = 0x5001u;
  allocation.entries[1].mode_00 = &owner;
  allocation.entries[1].name_word_08 = 0x6000u;
  allocation.entries[1].name_word_10 = 0x6002u;
  OpaqueGameModeManager manager{};
  manager.modes_begin_14 = allocation.entries;
  manager.modes_end_18 = allocation.entries + 2;
  GameModeManagerVectorDestroy_007d8cc0(&manager);
  assert(trace ==
         std::vector<std::string>({"entry-owner", "release", "entry-owner"}));
  assert(last_release == reinterpret_cast<void*>(0x6000u));
  game_mode_manager_ports().release_00f47380 = nullptr;
}

}

int main() {
  test_service_accessors_keep_roots_distinct();
  test_destructor_order_and_null_paths();
  test_entry_span_and_owner_rules();
  return 0;
}

#undef TEST_CDECL
#undef TEST_THISCALL
