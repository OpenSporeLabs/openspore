#include <cstdint>
#include <string>
#include <vector>

#include "app_lifecycle_wave8.hpp"

#if defined(_MSC_VER)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __attribute__((thiscall))
#else
#error "pkg-app-lifecycle-wave8 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave8 {
namespace {

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

struct Fixture {
  std::vector<std::string> events;
  OpaqueCellGame game{};
  OpaqueCellGfx gfx{};
  OpaqueCellUi ui{};
  OpaqueCellModeStrategy strategy{};
  OpaqueService service{};
  OpaqueServiceVtable service_vtable{};
  OpaqueAppSystem app_system{};
  OpaqueAppSystemVtable app_vtable{};
};

Fixture* current_fixture = nullptr;

void record(const char* event) { current_fixture->events.emplace_back(event); }

void conditional_cleanup() { record("conditional-cleanup"); }

OpaqueWord range_build(OpaqueWord first, OpaqueWord second, OpaqueWord third) {
  check(first == 0x1010u);
  check(second == 0x1010u);
  check(third == 0x1000u);
  record("range-build");
  return 0xfeedbeefu;
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL range_store(OpaqueWord* receiver,
                                                  OpaqueWord first,
                                                  OpaqueWord second) {
  check(receiver == &current_fixture->game.range_begin_519c);
  check(first == 0xfeedbeefu);
  check(second == 0x1010u);
  record("range-store");
}

void reset_first() { record("reset-first"); }

void reset_second() { record("reset-second"); }

void gfx_world_cleanup(void* pointer) {
  check(pointer ==
        static_cast<void*>(
            reinterpret_cast<std::uint8_t*>(&current_fixture->gfx) + 0x40u));
  record("gfx-world-cleanup");
}

OpaqueService* service_get() {
  record("service-get");
  return &current_fixture->service;
}

OpaqueAppSystem* app_system_get() {
  record("app-system-get");
  return &current_fixture->app_system;
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL service_operation_88(OpaqueService*,
                                                           OpaqueWord first,
                                                           OpaqueWord second,
                                                           OpaqueWord third) {
  check(first == 0x01010003u);
  check(second == 0u);
  check(third == 0u);
  record("service-88");
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL service_operation_98(OpaqueService*,
                                                           OpaqueWord first,
                                                           OpaqueWord second) {
  check(first == 7u);
  check(second == 0u);
  record("service-98");
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL app_operation_30(OpaqueAppSystem*,
                                                       OpaqueAppEvent* event,
                                                       OpaqueWord kind,
                                                       std::int32_t state) {
  check(reinterpret_cast<std::uintptr_t>(event) == 0x00e81c90u);
  check(kind == 0x0212d3e7u);
  check(state == static_cast<std::int32_t>(0xffffd8f1u));
  record("app-30");
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL app_operation_2c(OpaqueAppSystem*,
                                                       void* target,
                                                       OpaqueWord kind,
                                                       std::int32_t state) {
  void* const expected = static_cast<void*>(
      reinterpret_cast<std::uint8_t*>(&current_fixture->strategy) + 0x04u);
  check(target == expected);
  check(state == static_cast<std::int32_t>(0xffffd8f1u));
  if (kind == 0x05120262u) {
    record("app-2c-5120262");
  } else if (kind == 0x0539a4ceu) {
    record("app-2c-539a4ce");
  } else {
    check(kind == 0x0539a4cfu);
    record("app-2c-539a4cf");
  }
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL game_destructor(OpaqueCellGame* game) {
  check(game == &current_fixture->game);
  record("game-destructor");
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL gfx_destructor(OpaqueCellGfx* gfx) {
  check(gfx == &current_fixture->gfx);
  record("gfx-destructor");
}

void PKG_APP_LIFECYCLE_WAVE8_THISCALL ui_destructor(OpaqueCellUi* ui) {
  check(ui == &current_fixture->ui);
  record("ui-destructor");
}

void free_memory(void* pointer) {
  if (pointer == &current_fixture->game) {
    record("free-game");
  } else if (pointer == &current_fixture->gfx) {
    record("free-gfx");
  } else {
    check(pointer == &current_fixture->ui);
    record("free-ui");
  }
}

void initialize_fixture(Fixture& fixture) {
  current_fixture = &fixture;
  fixture.events.clear();
  fixture.game.flag_4121 = 1u;
  fixture.game.range_begin_519c = 0x1000u;
  fixture.game.range_end_51a0 = 0x1010u;
  for (std::size_t index = 0; index < 8u; ++index) {
    fixture.game.opaque_000[index] = 0u;
  }
  fixture.service_vtable = OpaqueServiceVtable{};
  fixture.service_vtable.operation_88 = service_operation_88;
  fixture.service_vtable.operation_98 = service_operation_98;
  fixture.service.vtable = &fixture.service_vtable;
  fixture.app_vtable = OpaqueAppSystemVtable{};
  fixture.app_vtable.operation_2c = app_operation_2c;
  fixture.app_vtable.operation_30 = app_operation_30;
  fixture.app_system.vtable = &fixture.app_vtable;

  g_app_lifecycle_wave8_ports = DisposePorts{};
  g_app_lifecycle_wave8_ports.conditional_cleanup = conditional_cleanup;
  g_app_lifecycle_wave8_ports.range_build = range_build;
  g_app_lifecycle_wave8_ports.range_store = range_store;
  g_app_lifecycle_wave8_ports.reset_first = reset_first;
  g_app_lifecycle_wave8_ports.reset_second = reset_second;
  g_app_lifecycle_wave8_ports.gfx_world_cleanup = gfx_world_cleanup;
  g_app_lifecycle_wave8_ports.service_get = service_get;
  g_app_lifecycle_wave8_ports.app_system_get = app_system_get;
  g_app_lifecycle_wave8_ports.game_destructor = game_destructor;
  g_app_lifecycle_wave8_ports.gfx_destructor = gfx_destructor;
  g_app_lifecycle_wave8_ports.ui_destructor = ui_destructor;
  g_app_lifecycle_wave8_ports.free_memory = free_memory;
  g_app_lifecycle_wave8_globals = DisposeGlobals{};
  g_app_lifecycle_wave8_globals.cell_game = &fixture.game;
  g_app_lifecycle_wave8_globals.cell_gfx = &fixture.gfx;
  g_app_lifecycle_wave8_globals.cell_ui = &fixture.ui;
  for (std::size_t index = 0; index < 8u; ++index) {
    g_app_lifecycle_wave8_globals.source_snapshot[index] =
        0x1000u + static_cast<OpaqueWord>(index);
    g_app_lifecycle_wave8_globals.destination[index] = 0u;
  }
}

void test_dispose() {
  Fixture fixture{};
  initialize_fixture(fixture);

  check(app_cCellModeStrategy_Dispose_00e81f30(&fixture.strategy));
  const std::vector<std::string> expected = {
      "conditional-cleanup", "range-build",
      "range-store",         "reset-first",
      "reset-second",        "gfx-world-cleanup",
      "service-get",         "service-88",
      "service-get",         "service-98",
      "app-system-get",      "app-30",
      "game-destructor",     "free-game",
      "gfx-destructor",      "free-gfx",
      "ui-destructor",       "free-ui",
      "app-system-get",      "app-2c-5120262",
      "app-system-get",      "app-2c-539a4ce",
      "app-system-get",      "app-2c-539a4cf"};
  check(fixture.events == expected);
  check(fixture.game.range_end_51a0 == 0x1000u);
  for (std::size_t index = 0; index < 8u; ++index) {
    check(g_app_lifecycle_wave8_globals.destination[index] ==
          0x1000u + static_cast<OpaqueWord>(index));
  }
  check(g_app_lifecycle_wave8_globals.cell_game == &fixture.game);
  check(g_app_lifecycle_wave8_globals.cell_gfx == &fixture.gfx);
  check(g_app_lifecycle_wave8_globals.cell_ui == &fixture.ui);
}

}

int run_model() {
  test_dispose();
  return failures == 0 ? 0 : 1;
}

}

int main() {
  return openspore::reconstruction::pkg_app_lifecycle_wave8::run_model();
}

#undef PKG_APP_LIFECYCLE_WAVE8_THISCALL
