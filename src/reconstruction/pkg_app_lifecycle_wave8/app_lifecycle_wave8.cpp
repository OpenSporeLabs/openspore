#include "app_lifecycle_wave8.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __thiscall
#define PKG_APP_LIFECYCLE_WAVE8_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __attribute__((thiscall))
#define PKG_APP_LIFECYCLE_WAVE8_CDECL __attribute__((cdecl))
#else
#error "pkg-app-lifecycle-wave8 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave8 {

DisposePorts g_app_lifecycle_wave8_ports{};
DisposeGlobals g_app_lifecycle_wave8_globals{};

namespace {

void* cell_gfx_world_pointer(OpaqueCellGfx* gfx) {
  if (gfx == nullptr) {
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x40u));
  }
  return static_cast<void*>(reinterpret_cast<std::uint8_t*>(gfx) + 0x40u);
}

void* mode_pause_target(OpaqueCellModeStrategy* strategy) {
  if (strategy == nullptr) {
    return nullptr;
  }
  return static_cast<void*>(reinterpret_cast<std::uint8_t*>(strategy) + 0x04u);
}

}

extern "C" bool PKG_APP_LIFECYCLE_WAVE8_THISCALL
app_cCellModeStrategy_Dispose_00e81f30(OpaqueCellModeStrategy* strategy) {
  DisposeGlobals& globals = g_app_lifecycle_wave8_globals;
  DisposePorts& ports = g_app_lifecycle_wave8_ports;
  OpaqueCellGame* const game = globals.cell_game;

  if (game->flag_4121 != 0U) {
    ports.conditional_cleanup();
  }

  const OpaqueWord begin = game->range_begin_519c;
  const OpaqueWord end = game->range_end_51a0;
  const OpaqueWord built = ports.range_build(end, end, begin);
  ports.range_store(&game->range_begin_519c, built, end);
  const std::int32_t count = static_cast<std::int32_t>(end - begin) >> 2;
  game->range_end_51a0 = end + static_cast<OpaqueWord>(count * -4);

  ports.reset_first();
  ports.reset_second();

  globals.destination[0] = globals.source_snapshot[0];
  globals.destination[1] = globals.source_snapshot[1];
  globals.destination[2] = globals.source_snapshot[2];
  globals.destination[3] = globals.source_snapshot[3];
  globals.destination[4] = globals.source_snapshot[4];
  globals.destination[5] = globals.source_snapshot[5];
  globals.destination[6] = globals.source_snapshot[6];
  globals.destination[7] = globals.source_snapshot[7];

  ports.gfx_world_cleanup(cell_gfx_world_pointer(globals.cell_gfx));

  OpaqueService* service = ports.service_get();
  service->vtable->operation_88(service, 0x01010003u, 0u, 0u);
  service = ports.service_get();
  service->vtable->operation_98(service, 7u, 0u);

  OpaqueAppSystem* app_system = ports.app_system_get();
  app_system->vtable->operation_30(
      app_system, reinterpret_cast<OpaqueAppEvent*>(0x00e81c90u), 0x0212d3e7u,
      static_cast<std::int32_t>(0xffffd8f1u));

  OpaqueCellGame* const game_to_release = globals.cell_game;
  if (game_to_release != nullptr) {
    ports.game_destructor(game_to_release);
    ports.free_memory(game_to_release);
  }

  OpaqueCellGfx* const gfx_to_release = globals.cell_gfx;
  if (gfx_to_release != nullptr) {
    ports.gfx_destructor(gfx_to_release);
    ports.free_memory(gfx_to_release);
  }

  OpaqueCellUi* const ui_to_release = globals.cell_ui;
  if (ui_to_release != nullptr) {
    ports.ui_destructor(ui_to_release);
    ports.free_memory(ui_to_release);
  }

  void* const pause_target = mode_pause_target(strategy);
  app_system = ports.app_system_get();
  app_system->vtable->operation_2c(app_system, pause_target, 0x05120262u,
                                   static_cast<std::int32_t>(0xffffd8f1u));
  app_system = ports.app_system_get();
  app_system->vtable->operation_2c(app_system, pause_target, 0x0539a4ceu,
                                   static_cast<std::int32_t>(0xffffd8f1u));
  app_system = ports.app_system_get();
  app_system->vtable->operation_2c(app_system, pause_target, 0x0539a4cfu,
                                   static_cast<std::int32_t>(0xffffd8f1u));

  return true;
}

}

#undef PKG_APP_LIFECYCLE_WAVE8_CDECL
#undef PKG_APP_LIFECYCLE_WAVE8_THISCALL
