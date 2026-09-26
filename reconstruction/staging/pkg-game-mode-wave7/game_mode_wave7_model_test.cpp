#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "game_mode_wave7.hpp"

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE7_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE7_THISCALL __attribute__((thiscall))
#else
#error "PKG-GAME-MODE-WAVE7 requires an MSVC or GCC thiscall convention"
#endif

namespace openspore::reconstruction::pkg_game_mode_wave7 {
namespace {

using namespace openspore::reconstruction::pkg_game_mode_wave7;

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void* address_value(std::uintptr_t value) {
  return reinterpret_cast<void*>(value);
}

std::uint8_t load_u8(const void* address, std::size_t offset) {
  std::uint8_t value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(address) + offset,
              sizeof(value));
  return value;
}

std::uint32_t load_u32(const void* address, std::size_t offset) {
  std::uint32_t value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(address) + offset,
              sizeof(value));
  return value;
}

void store_u8(void* address, std::size_t offset, std::uint8_t value) {
  std::memcpy(static_cast<std::uint8_t*>(address) + offset, &value,
              sizeof(value));
}

void store_u32(void* address, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(address) + offset, &value,
              sizeof(value));
}

const char alpha_name[] = "Alpha";
const char beta_name[] = "BETA";

enum class AppEvent {
  acquire,
  exit,
  exit_dispatch,
  exit_destroy,
  enter,
  enter_dispatch,
  enter_destroy,
};

struct NotificationObservation {
  std::uint32_t kind = 0U;
  std::uint32_t word = 0U;
  std::uint32_t state = 0U;
};

bool operator==(const NotificationObservation& left,
                const NotificationObservation& right) {
  return left.kind == right.kind && left.word == right.word &&
         left.state == right.state;
}

struct AppFixture {
  std::vector<AppEvent> events;
  std::vector<NotificationObservation> notifications;
  std::array<OpaqueAppMode, 3> modes{};
  std::array<AppModeVtable, 3> mode_vtables{};
  std::array<AppModeEntry, 3> entries{};
  AppModeRegistry registry{};
  AppModeVtable registry_vtable{};
  AppNotificationVtable notification_vtable{};
  OpaqueNotificationManager notification_manager{};
  AppNotificationRecord* last_record = nullptr;
};

AppFixture* current_app = nullptr;

void PKG_GAME_MODE_WAVE7_THISCALL app_mode_enter(OpaqueAppMode* mode) {
  current_app->events.push_back(AppEvent::enter);
  check(mode == &current_app->modes[1] || mode == &current_app->modes[2]);
}

void PKG_GAME_MODE_WAVE7_THISCALL app_mode_exit(OpaqueAppMode* mode) {
  current_app->events.push_back(AppEvent::exit);
  check(mode == &current_app->modes[0]);
}

bool PKG_GAME_MODE_WAVE7_THISCALL
app_mode_activate_by_index(AppModeRegistry* registry, std::int32_t index) {
  return app_mode_activate_index_007d8c80(registry, index);
}

OpaqueNotificationManager* app_notification_acquire() {
  current_app->events.push_back(AppEvent::acquire);
  return &current_app->notification_manager;
}

void PKG_GAME_MODE_WAVE7_THISCALL
app_notification_dispatch(OpaqueNotificationManager*, std::uint32_t kind,
                          AppNotificationRecord* record) {
  current_app->events.push_back(kind == 0x212d3e7U ? AppEvent::exit_dispatch
                                                   : AppEvent::enter_dispatch);
  current_app->notifications.push_back(
      NotificationObservation{record->kind, record->word, record->state});
  current_app->last_record = record;
}

void PKG_GAME_MODE_WAVE7_THISCALL
app_notification_destroy(AppNotificationRecord* record) {
  current_app->events.push_back(record->kind == 0x212d3e7U
                                    ? AppEvent::exit_destroy
                                    : AppEvent::enter_destroy);
  current_app->last_record = nullptr;
}

void initialize_app_fixture(AppFixture& fixture) {
  current_app = &fixture;
  fixture.events.clear();
  fixture.notifications.clear();
  fixture.last_record = nullptr;
  for (std::size_t index = 0; index < fixture.modes.size(); ++index) {
    fixture.mode_vtables[index] = AppModeVtable{};
    fixture.mode_vtables[index].on_enter = &app_mode_enter;
    fixture.mode_vtables[index].on_exit = &app_mode_exit;
    fixture.modes[index].vtable = &fixture.mode_vtables[index];
  }
  fixture.entries[0] = {&fixture.modes[0],
                        0x1000U,
                        alpha_name,
                        alpha_name + sizeof(alpha_name) - 1U,
                        0U,
                        0U};
  fixture.entries[1] = {&fixture.modes[1],
                        0x2000U,
                        beta_name,
                        beta_name + sizeof(beta_name) - 1U,
                        0U,
                        0U};
  fixture.entries[2] = {&fixture.modes[2], 0x3000U, "", "", 0U, 0U};
  fixture.registry_vtable = AppModeVtable{};
  fixture.registry_vtable.activate_by_index = &app_mode_activate_by_index;
  fixture.registry = AppModeRegistry{};
  fixture.registry.vtable = &fixture.registry_vtable;
  fixture.registry.entries_begin = fixture.entries.data();
  fixture.registry.entries_end =
      fixture.entries.data() + fixture.entries.size();
  fixture.registry.active_index = 0U;
  fixture.notification_vtable = AppNotificationVtable{};
  fixture.notification_vtable.dispatch = &app_notification_dispatch;
  fixture.notification_manager = OpaqueNotificationManager{};
  fixture.notification_manager.vtable = &fixture.notification_vtable;
  g_app_mode_ports = AppModePorts{};
  g_app_mode_ports.notifications.acquire = &app_notification_acquire;
  g_app_mode_ports.notifications.dispatch = &app_notification_dispatch;
  g_app_mode_ports.notifications.destroy = &app_notification_destroy;
}

void test_app_mode_activation_order() {
  AppFixture fixture{};
  initialize_app_fixture(fixture);

  check(app_mode_activate_index_007d8c80(&fixture.registry, 1));
  check(fixture.registry.active_index == 1U);
  check(fixture.events == (std::vector<AppEvent>{
                              AppEvent::exit,
                              AppEvent::acquire,
                              AppEvent::exit_dispatch,
                              AppEvent::exit_destroy,
                              AppEvent::enter,
                              AppEvent::enter_dispatch,
                              AppEvent::enter_destroy,
                          }));
  check(fixture.notifications == (std::vector<NotificationObservation>{
                                     {0x212d3e7U, 0x1000U, 0U},
                                     {0x22d1adcU, 0x2000U, 1U},
                                 }));
  check(fixture.last_record == nullptr);

  fixture.events.clear();
  check(app_mode_activate_index_007d8c80(&fixture.registry, 1));
  check(fixture.events.empty());

  check(!app_mode_activate_index_007d8c80(&fixture.registry, -1));
  check(!app_mode_activate_index_007d8c80(&fixture.registry, 3));
  check(fixture.events.empty());
  check(fixture.registry.active_index == 1U);

  fixture.events.clear();
  fixture.notifications.clear();
  fixture.registry.active_index = 0xffffffffU;
  check(app_mode_activate_index_007d8c80(&fixture.registry, 2));
  check(fixture.registry.active_index == 2U);
  check(fixture.events == (std::vector<AppEvent>{
                              AppEvent::acquire,
                              AppEvent::exit_dispatch,
                              AppEvent::exit_destroy,
                              AppEvent::enter,
                              AppEvent::enter_dispatch,
                              AppEvent::enter_destroy,
                          }));
  check(fixture.notifications == (std::vector<NotificationObservation>{
                                     {0x212d3e7U, 0U, 0U},
                                     {0x22d1adcU, 0x3000U, 1U},
                                 }));
}

void test_app_mode_name_activation() {
  AppFixture fixture{};
  initialize_app_fixture(fixture);

  check(app_mode_activate_by_name_007d8360(&fixture.registry, "beta"));
  check(fixture.registry.active_index == 1U);
  check(fixture.events == (std::vector<AppEvent>{
                              AppEvent::exit,
                              AppEvent::acquire,
                              AppEvent::exit_dispatch,
                              AppEvent::exit_destroy,
                              AppEvent::enter,
                              AppEvent::enter_dispatch,
                              AppEvent::enter_destroy,
                          }));

  fixture.events.clear();
  fixture.registry.active_index = 0U;
  check(!app_mode_activate_by_name_007d8360(&fixture.registry, ""));
  check(!app_mode_activate_by_name_007d8360(&fixture.registry, "missing"));
  check(fixture.events.empty());
  check(fixture.registry.active_index == 0U);
}

std::uint32_t strategy_axis_a_value = 0U;
std::uint32_t strategy_axis_b_value = 0U;

std::uint32_t PKG_GAME_MODE_WAVE7_THISCALL
strategy_axis_a(StrategyState* state) {
  static_cast<void>(state);
  return strategy_axis_a_value;
}

std::uint32_t PKG_GAME_MODE_WAVE7_THISCALL
strategy_axis_b(StrategyState* state) {
  static_cast<void>(state);
  return strategy_axis_b_value;
}

void test_strategy_pending_and_commit() {
  StrategyVtable vtable{};
  vtable.axis_a = &strategy_axis_a;
  vtable.axis_b = &strategy_axis_b;
  StrategyState strategy{};
  strategy.vtable = &vtable;
  strategy.pending = kNoPendingStrategyRequest;
  strategy_axis_a_value = 7U;
  strategy_axis_b_value = 7U;

  check(strategy_request_ready_00b5b840(&strategy, 7U));
  check(!strategy_request_ready_00b5b840(&strategy, 8U));
  strategy_axis_a_value = 8U;
  check(!strategy_request_ready_00b5b840(&strategy, 7U));

  strategy_queue_primary_00b5b880(&strategy, 11U);
  check(strategy.pending == 11U);
  check(strategy.request_kind == 1U);
  strategy_queue_secondary_00b5b8a0(&strategy, 22U);
  check(strategy.pending == 11U);
  check(strategy.request_kind == 2U);
  strategy_commit_secondary_00b5b8e0(&strategy);
  check(strategy.committed_a == 0U);
  check(strategy.committed_b == 11U);
  check(strategy.pending == kNoPendingStrategyRequest);
  check(strategy.request_kind == 0U);

  strategy_queue_primary_00b5b880(&strategy, 33U);
  strategy_commit_primary_00b5b8c0(&strategy);
  check(strategy.committed_a == 33U);
  check(strategy.committed_b == 11U);
  check(strategy.pending == kNoPendingStrategyRequest);
}

enum class BridgeEvent {
  resolve,
  ensure,
  notify_primary,
  notify_secondary,
  action_00b108b0,
  dispatch_00b5e3f0,
  app_init,
  tree,
  target_query,
  target_action,
  reset,
  app_switch,
  graphics,
  payload_write,
  factory,
  register_summarizer,
};

struct BridgeFixture {
  std::vector<BridgeEvent> events;
  std::vector<std::uint32_t> resolved_values;
  std::array<std::uint8_t, 0x30> payload{};
  std::array<std::uint8_t, 0x40> root{};
  std::array<std::uint8_t, 0x10> summarizer{};
  std::array<std::uint8_t, 8> reset_root{};
  OpaqueBridge bridge{};
  OpaqueModeObject mode_a{};
  OpaqueModeObject mode_b{};
  OpaqueModeObject mode{};
  OpaqueScenarioMode scenario_mode{};
  OpaqueAppSystem app_system{};
  OpaqueGraphics graphics{};
  std::array<std::uint32_t, 2> mode_ids{0x24a4f5aU, 0x24a4f5aU};
  std::uint32_t b5b800_value = 0x01654c05U;
  std::vector<std::uint32_t> b5b800_values;
  std::size_t b5b800_index = 0U;
  bool b5ca70_result = true;
  bool b5cb20_result = false;
};

BridgeFixture* current_bridge = nullptr;

std::uint32_t bridge_resolve(std::uint32_t value) {
  current_bridge->events.push_back(BridgeEvent::resolve);
  current_bridge->resolved_values.push_back(value);
  return value;
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_ensure(OpaqueBridge* bridge) {
  current_bridge->events.push_back(BridgeEvent::ensure);
  bridge->notification_enabled = 1U;
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_notify_primary(OpaqueBridge*,
                                                        std::uint32_t,
                                                        std::uint32_t) {
  current_bridge->events.push_back(BridgeEvent::notify_primary);
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_notify_secondary(OpaqueBridge*,
                                                          std::uint32_t,
                                                          std::uint32_t) {
  current_bridge->events.push_back(BridgeEvent::notify_secondary);
}

OpaqueModeObject* bridge_get_270() { return &current_bridge->mode_a; }
OpaqueModeObject* bridge_get_280() { return &current_bridge->mode_b; }
OpaqueModeObject* bridge_get_320() { return &current_bridge->mode; }

void PKG_GAME_MODE_WAVE7_THISCALL bridge_action_108(OpaqueModeObject*) {
  current_bridge->events.push_back(BridgeEvent::action_00b108b0);
}

void* bridge_get_b5b800() {
  current_bridge->events.push_back(BridgeEvent::resolve);
  if (current_bridge->b5b800_index < current_bridge->b5b800_values.size()) {
    return address_value(
        current_bridge->b5b800_values[current_bridge->b5b800_index++]);
  }
  return address_value(current_bridge->b5b800_value);
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_dispatch_e3f0(OpaqueBridge*, void*) {
  current_bridge->events.push_back(BridgeEvent::dispatch_00b5e3f0);
}

bool bridge_query_b5ca70() { return current_bridge->b5ca70_result; }
bool bridge_query_e00ac0() { return true; }

OpaqueScenarioMode* bridge_get_scenario_mode() {
  return &current_bridge->scenario_mode;
}

OpaqueAppSystem* bridge_app_system_get() { return &current_bridge->app_system; }

void PKG_GAME_MODE_WAVE7_THISCALL bridge_app14(OpaqueAppSystem*,
                                               std::uint32_t first,
                                               std::uint32_t, std::uint32_t) {
  current_bridge->events.push_back(BridgeEvent::app_init);
  check(first == 0x64eb18eU || first == 0x689c9b9U);
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_app18(OpaqueAppSystem*,
                                               std::uint32_t first,
                                               std::uint32_t, std::uint32_t,
                                               std::uint32_t) {
  current_bridge->events.push_back(BridgeEvent::app_switch);
  check(first == 0x4715068U);
}

OpaqueGraphics* bridge_graphics_get() { return &current_bridge->graphics; }

void PKG_GAME_MODE_WAVE7_THISCALL bridge_graphics40(OpaqueGraphics*) {
  current_bridge->events.push_back(BridgeEvent::graphics);
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_tree(OpaqueModeObject*, const char*) {
  current_bridge->events.push_back(BridgeEvent::tree);
}

bool PKG_GAME_MODE_WAVE7_THISCALL bridge_target_query(void*) {
  current_bridge->events.push_back(BridgeEvent::target_query);
  return true;
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_target_action(void*,
                                                       std::uint32_t first,
                                                       std::uint32_t second) {
  current_bridge->events.push_back(BridgeEvent::target_action);
  check(first == 1U && second == 0U);
}

void* bridge_get_fd9c60() {
  current_bridge->events.push_back(BridgeEvent::reset);
  return current_bridge->reset_root.data();
}

void PKG_GAME_MODE_WAVE7_THISCALL bridge_reset(void*) {
  current_bridge->events.push_back(BridgeEvent::reset);
}

bool bridge_query_01021080() { return false; }
void* bridge_get_01002bd0() { return current_bridge->root.data(); }
bool bridge_query_b5cb20(void*) { return current_bridge->b5cb20_result; }

void* bridge_create_f473a0(std::size_t, const char*, std::uint32_t,
                           std::uint32_t, std::uint32_t, std::uint32_t) {
  current_bridge->events.push_back(BridgeEvent::factory);
  return current_bridge->summarizer.data();
}

void* bridge_get_0067cb40() { return current_bridge->reset_root.data(); }

void PKG_GAME_MODE_WAVE7_THISCALL bridge_register(void*, void*) {
  current_bridge->events.push_back(BridgeEvent::register_summarizer);
}

void initialize_bridge_fixture(BridgeFixture& fixture) {
  current_bridge = &fixture;
  fixture.events.clear();
  fixture.resolved_values.clear();
  fixture.bridge = OpaqueBridge{};
  fixture.mode_a = OpaqueModeObject{};
  fixture.mode_b = OpaqueModeObject{};
  fixture.mode = OpaqueModeObject{};
  fixture.scenario_mode = OpaqueScenarioMode{};
  fixture.app_system = OpaqueAppSystem{};
  fixture.graphics = OpaqueGraphics{};
  fixture.b5b800_value = 0x01654c05U;
  fixture.b5b800_values.clear();
  fixture.b5b800_index = 0U;
  fixture.b5ca70_result = true;
  fixture.b5cb20_result = false;
  g_app_simulator_bridge_ports = BridgePorts{};
  g_bridge_globals = BridgeGlobals{};
  BridgePorts& ports = g_app_simulator_bridge_ports;
  ports.resolve_00b5c9d0 = &bridge_resolve;
  ports.ensure_00b60d80 = &bridge_ensure;
  ports.notify_212d3e7 = &bridge_notify_primary;
  ports.notify_22d1adc = &bridge_notify_secondary;
  ports.get_00b3d270 = &bridge_get_270;
  ports.get_00b3d280 = &bridge_get_280;
  ports.action_00b108b0 = &bridge_action_108;
  ports.get_00b3d320 = &bridge_get_320;
  ports.get_00b5b800 = &bridge_get_b5b800;
  ports.dispatch_00b5e3f0 = &bridge_dispatch_e3f0;
  ports.query_00b5ca70 = &bridge_query_b5ca70;
  ports.query_00e00ac0 = &bridge_query_e00ac0;
  ports.get_scenario_mode = &bridge_get_scenario_mode;
  ports.app_system_get = &bridge_app_system_get;
  ports.app_system_vtable_14 = &bridge_app14;
  ports.app_system_vtable_18 = &bridge_app18;
  ports.graphics_get = &bridge_graphics_get;
  ports.graphics_vtable_40 = &bridge_graphics40;
  ports.tree_node_vtable_2c = &bridge_tree;
  ports.query_00d09660 = &bridge_target_query;
  ports.action_00d100b0 = &bridge_target_action;
  ports.get_00fd9c60 = &bridge_get_fd9c60;
  ports.action_00fde3e0 = &bridge_reset;
  ports.query_01021080 = &bridge_query_01021080;
  ports.get_01002bd0 = &bridge_get_01002bd0;
  ports.query_00b5cb20 = &bridge_query_b5cb20;
  ports.create_00f473a0 = &bridge_create_f473a0;
  ports.get_0067cb40 = &bridge_get_0067cb40;
  ports.register_summarizer = &bridge_register;
}

void test_bridge_resolved_request_and_axes() {
  BridgeFixture fixture{};
  initialize_bridge_fixture(fixture);
  fixture.bridge.notification_enabled = 0U;
  store_u32(fixture.payload.data(), 0x08, 0x11U);
  store_u32(fixture.payload.data(), 0x10, 0x22U);

  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x212d3e7U,
                                           fixture.payload.data()));
  check(fixture.events == (std::vector<BridgeEvent>{
                              BridgeEvent::resolve,
                              BridgeEvent::resolve,
                              BridgeEvent::ensure,
                              BridgeEvent::notify_primary,
                          }));
  check(fixture.resolved_values == (std::vector<std::uint32_t>{0x22U, 0x11U}));
  check(fixture.bridge.notification_enabled == 1U);

  fixture.events.clear();
  fixture.bridge.notification_enabled = 0U;
  store_u32(fixture.payload.data(), 0x08, 0x33U);
  store_u32(fixture.payload.data(), 0x10, 0x33U);
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x22d1adcU,
                                           fixture.payload.data()));
  check(fixture.events ==
        (std::vector<BridgeEvent>{BridgeEvent::resolve, BridgeEvent::resolve}));

  fixture.events.clear();
  store_u32(fixture.payload.data(), 0x08, 1U);
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x255abf5U,
                                           fixture.payload.data()));
  check(fixture.bridge.counter_30 == 0xffffffffU);
  store_u32(fixture.payload.data(), 0x08, 2U);
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x255abf5U,
                                           fixture.payload.data()));
  check(fixture.bridge.counter_30 == 0U);
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x3e9a620U,
                                            fixture.payload.data()));
  check(g_bridge_globals.flag_01686af1 == 1U);
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x3e9a625U,
                                            fixture.payload.data()));
  check(g_bridge_globals.flag_01686af1 == 0U);
}

void test_bridge_payload_dispatch_and_writes() {
  BridgeFixture fixture{};
  initialize_bridge_fixture(fixture);
  fixture.mode_a.field_308 = 0x24a4f5aU;
  fixture.mode_b.field_308 = 0x24a4f5aU;
  store_u32(fixture.payload.data(), 0x10, 0x24a4f5aU);
  store_u32(fixture.payload.data(), 0x18, 0x24a4f5aU);
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x0f62adeU,
                                            fixture.payload.data()));
  check(fixture.events == (std::vector<BridgeEvent>{
                              BridgeEvent::action_00b108b0,
                              BridgeEvent::action_00b108b0,
                          }));

  fixture.events.clear();
  store_u32(fixture.payload.data(), 0x18, 0x39393837U);
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x0f62defU,
                                           fixture.payload.data()));
  check(fixture.events ==
        (std::vector<BridgeEvent>{BridgeEvent::resolve,
                                  BridgeEvent::dispatch_00b5e3f0}));

  fixture.events.clear();
  store_u8(fixture.payload.data(), 0, 0U);
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x12a93f05U,
                                            fixture.payload.data()));
  check(load_u8(fixture.payload.data(), 0) == 1U);

  fixture.events.clear();
  store_u8(fixture.payload.data(), 0x0c, 1U);
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0xf1ff568bU,
                                            fixture.payload.data()));
  check(fixture.events.empty());
  store_u8(fixture.payload.data(), 0x0c, 1U);
  fixture.b5cb20_result = false;
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0xf1ff568bU,
                                            fixture.payload.data()));
  check(load_u32(fixture.payload.data(), 0x10) == 0xcdccb5aeU);
  check(load_u32(fixture.payload.data(), 0x14) == 0x00b1b104U);
  check(load_u32(fixture.payload.data(), 0x18) == 0x490f6945U);
  check(load_u8(fixture.payload.data(), 0x0c) == 0U);
}

void test_bridge_scenario_and_summarizer_paths() {
  BridgeFixture fixture{};
  initialize_bridge_fixture(fixture);
  fixture.scenario_mode.mode_d0 = 2U;
  fixture.b5b800_values = {0x01654c10U, 0x01654c05U};
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x4715068U,
                                           fixture.payload.data()));
  check(fixture.mode.flag_28 == 1U);
  check(fixture.mode.flag_29 == 1U);
  check(fixture.events == (std::vector<BridgeEvent>{
                              BridgeEvent::app_init,
                              BridgeEvent::resolve,
                              BridgeEvent::tree,
                              BridgeEvent::resolve,
                              BridgeEvent::target_query,
                              BridgeEvent::target_action,
                              BridgeEvent::reset,
                              BridgeEvent::reset,
                              BridgeEvent::app_init,
                              BridgeEvent::graphics,
                          }));

  fixture.events.clear();
  fixture.mode.flag_28 = 1U;
  fixture.b5b800_values.clear();
  fixture.b5b800_value = 0x01654c10U;
  check(app_simulator_mode_bridge_00b63510(&fixture.bridge, 0x4715068U,
                                           fixture.payload.data()));
  check(fixture.events == (std::vector<BridgeEvent>{
                              BridgeEvent::app_init,
                              BridgeEvent::resolve,
                              BridgeEvent::tree,
                              BridgeEvent::app_switch,
                          }));

  fixture.events.clear();
  check(!app_simulator_mode_bridge_00b63510(&fixture.bridge, 0xf52feda1U,
                                            fixture.payload.data()));
  check(fixture.events == (std::vector<BridgeEvent>{
                              BridgeEvent::factory,
                              BridgeEvent::register_summarizer,
                          }));
  check(load_u32(fixture.summarizer.data(), 0x00) == 0x01462690U);
  check(load_u32(fixture.summarizer.data(), 0x04) == 0U);
}

enum class CellEvent {
  factory,
  register_mode,
};

struct CellFixture {
  std::vector<CellEvent> events;
  std::array<std::uint8_t, 8> object_storage{};
  CellModeOwner owner{};
  CellModeOwnerVtable owner_vtable{};
  CellModeObject* object = nullptr;
  std::size_t factory_size = 0U;
  std::uint32_t factory_type = 0U;
  std::array<std::uint32_t, 4> factory_tail{};
  const char* mode_name = nullptr;
  const char* tag_name = nullptr;
};

CellFixture* current_cell = nullptr;

CellModeObject* cell_factory(std::size_t size, std::uint32_t type,
                             std::uint32_t first, std::uint32_t second,
                             std::uint32_t third, std::uint32_t fourth) {
  current_cell->events.push_back(CellEvent::factory);
  current_cell->factory_size = size;
  current_cell->factory_type = type;
  current_cell->factory_tail[0] = first;
  current_cell->factory_tail[1] = second;
  current_cell->factory_tail[2] = third;
  current_cell->factory_tail[3] = fourth;
  current_cell->object =
      reinterpret_cast<CellModeObject*>(current_cell->object_storage.data());
  return current_cell->object;
}

void PKG_GAME_MODE_WAVE7_THISCALL cell_register(CellModeOwner* owner,
                                                CellModeObject* object,
                                                const char* mode_name,
                                                const char* tag_name) {
  current_cell->events.push_back(CellEvent::register_mode);
  check(owner == &current_cell->owner);
  check(object == current_cell->object);
  current_cell->mode_name = mode_name;
  current_cell->tag_name = tag_name;
}

void test_cell_mode_constructor_registration() {
  CellFixture fixture{};
  current_cell = &fixture;
  fixture.owner_vtable = CellModeOwnerVtable{};
  fixture.owner_vtable.register_mode = &cell_register;
  fixture.owner = CellModeOwner{};
  fixture.owner.vtable = &fixture.owner_vtable;
  g_cell_mode_ports = CellModePorts{};
  g_cell_mode_ports.factory = &cell_factory;

  cell_mode_constructor_00e616c0(&fixture.owner);
  check(fixture.factory_size == 0x0cU);
  check(fixture.factory_type == 0x013ebc58U);
  check(fixture.factory_tail ==
        (std::array<std::uint32_t, 4>{{0U, 0U, 0U, 0U}}));
  check(fixture.object->primary_vtable == 0x01485558U);
  check(fixture.object->secondary_vtable == 0x01485550U);
  check(fixture.mode_name == reinterpret_cast<const char*>(0x01654c00U));
  check(fixture.tag_name == reinterpret_cast<const char*>(0x014856d8U));
  check(fixture.events ==
        (std::vector<CellEvent>{CellEvent::factory, CellEvent::register_mode}));

  fixture.events.clear();
  fixture.object_storage.fill(0U);
  cell_mode_constructor_00e616c0(&fixture.owner);
  check(fixture.object->primary_vtable == 0x01485558U);
  check(fixture.object->secondary_vtable == 0x01485550U);
}

int run_tests() {
  test_app_mode_activation_order();
  test_app_mode_name_activation();
  test_strategy_pending_and_commit();
  test_bridge_resolved_request_and_axes();
  test_bridge_payload_dispatch_and_writes();
  test_bridge_scenario_and_summarizer_paths();
  test_cell_mode_constructor_registration();
  return failures == 0 ? 0 : 1;
}

}

}

int main() {
  return openspore::reconstruction::pkg_game_mode_wave7::run_tests();
}

#undef PKG_GAME_MODE_WAVE7_THISCALL
