#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-GAME-MODE-WAVE7 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE7_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE7_THISCALL __attribute__((thiscall))
#else
#error "PKG-GAME-MODE-WAVE7 requires an MSVC or GCC thiscall convention"
#endif

static_assert(sizeof(void*) == 4,
              "PKG-GAME-MODE-WAVE7 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4,
              "PKG-GAME-MODE-WAVE7 target words are 32-bit");

namespace openspore::reconstruction::pkg_game_mode_wave7 {

struct AppModeRegistry;
struct OpaqueAppMode;
struct OpaqueNotificationManager;
struct StrategyState;
struct OpaqueBridge;
struct OpaqueAppSystem;
struct OpaqueGraphics;
struct CellModeOwner;
struct CellModeObject;

using AppModeOnEnter = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueAppMode*);
using AppModeOnExit = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueAppMode*);
using AppModeActivateByIndex =
    bool(PKG_GAME_MODE_WAVE7_THISCALL*)(AppModeRegistry*, std::int32_t);

struct AppModeVtable {
  std::uintptr_t slots_00[6];
  AppModeOnEnter on_enter;
  AppModeOnExit on_exit;
  std::uintptr_t slot_20;
  std::uintptr_t slots_24[7];
  AppModeActivateByIndex activate_by_index;
};

struct OpaqueAppMode {
  AppModeVtable* vtable;
};

struct AppModeEntry {
  OpaqueAppMode* mode;
  std::uint32_t notification_word;
  const char* name_begin;
  const char* name_end;
  std::uint32_t opaque_10;
  std::uint32_t opaque_14;
};

struct AppModeRegistry {
  AppModeVtable* vtable;
  std::uint8_t opaque_04[0x10];
  AppModeEntry* entries_begin;
  AppModeEntry* entries_end;
  std::uint32_t opaque_1c;
  std::uint32_t opaque_20;
  std::uint32_t opaque_24;
  std::uint32_t active_index;
  std::uint32_t opaque_2c;
};

struct AppNotificationRecord {
  std::uint32_t kind;
  std::uint32_t word;
  std::uint32_t state;
};

using AppNotificationAcquire = OpaqueNotificationManager* (*)();
using AppNotificationDispatch = void(PKG_GAME_MODE_WAVE7_THISCALL*)(
    OpaqueNotificationManager*, std::uint32_t, AppNotificationRecord*);
using AppNotificationDestroy =
    void(PKG_GAME_MODE_WAVE7_THISCALL*)(AppNotificationRecord*);

struct AppNotificationVtable {
  std::uintptr_t slots_00[5];
  AppNotificationDispatch dispatch;
};

struct OpaqueNotificationManager {
  AppNotificationVtable* vtable;
};

struct AppNotificationPorts {
  AppNotificationAcquire acquire = nullptr;
  AppNotificationDispatch dispatch = nullptr;
  AppNotificationDestroy destroy = nullptr;
};

struct AppModePorts {
  AppNotificationPorts notifications{};
};

extern "C" AppModePorts g_app_mode_ports;

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL
app_mode_activate_index_007d8c80(AppModeRegistry* registry, std::int32_t index);
extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
app_mode_activate_007d85b0(AppModeRegistry* registry, std::int32_t index);
extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL
app_mode_activate_by_name_007d8360(AppModeRegistry* registry, const char* name);

using StrategyAxisValue =
    std::uint32_t(PKG_GAME_MODE_WAVE7_THISCALL*)(StrategyState*);

struct StrategyVtable {
  std::uintptr_t slots_00[7];
  StrategyAxisValue axis_a;
  StrategyAxisValue axis_b;
};

struct StrategyState {
  StrategyVtable* vtable;
  std::uint8_t opaque_04[8];
  std::uint32_t committed_a;
  std::uint32_t committed_b;
  std::uint32_t pending;
  std::uint32_t request_kind;
};

inline constexpr std::uint32_t kNoPendingStrategyRequest = 0xffffffffU;

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL strategy_request_ready_00b5b840(
    StrategyState* strategy, std::uint32_t requested);
extern "C" void PKG_GAME_MODE_WAVE7_THISCALL strategy_queue_primary_00b5b880(
    StrategyState* strategy, std::uint32_t requested);
extern "C" void PKG_GAME_MODE_WAVE7_THISCALL strategy_queue_secondary_00b5b8a0(
    StrategyState* strategy, std::uint32_t requested);
extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
strategy_commit_primary_00b5b8c0(StrategyState* strategy);
extern "C" void PKG_GAME_MODE_WAVE7_THISCALL
strategy_commit_secondary_00b5b8e0(StrategyState* strategy);

struct OpaqueModeObject {
  std::uint8_t opaque_00[0x28];
  std::uint8_t flag_28;
  std::uint8_t flag_29;
  std::uint8_t opaque_2a[0x2de];
  std::uint32_t field_308;
};

struct OpaqueScenarioMode {
  std::uint8_t opaque_00[0xd0];
  std::uint32_t mode_d0;
};

struct OpaqueBridge {
  std::uintptr_t vtable;
  std::uint8_t opaque_04[8];
  std::uint8_t request_axis;
  std::uint8_t notification_enabled;
  std::uint8_t opaque_0e[0x22];
  std::uint32_t counter_30;
};

struct BridgeGlobals {
  std::uint8_t flag_01686af1;
};

extern "C" BridgeGlobals g_bridge_globals;

using BridgeResolve = std::uint32_t (*)(std::uint32_t);
using BridgeEnsure = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueBridge*);
using BridgeNotify = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueBridge*,
                                                         std::uint32_t,
                                                         std::uint32_t);
using BridgeGetMode = OpaqueModeObject* (*)();
using BridgeModeAction = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueModeObject*);
using BridgeGetPointer = void* (*)();
using BridgeDispatchMode = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueBridge*,
                                                               void*);
using BridgeQuery = bool (*)();
using BridgePayloadQuery = bool (*)(void*);
using BridgeAppSystemGet = OpaqueAppSystem* (*)();
using BridgeAppSystem14 = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueAppSystem*,
                                                              std::uint32_t,
                                                              std::uint32_t,
                                                              std::uint32_t);
using BridgeAppSystem18 = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueAppSystem*,
                                                              std::uint32_t,
                                                              std::uint32_t,
                                                              std::uint32_t,
                                                              std::uint32_t);
using BridgeGraphicsGet = OpaqueGraphics* (*)();
using BridgeGraphics40 = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueGraphics*);
using BridgeTreeAction = void(PKG_GAME_MODE_WAVE7_THISCALL*)(OpaqueModeObject*,
                                                             const char*);
using BridgeTargetQuery = bool(PKG_GAME_MODE_WAVE7_THISCALL*)(void*);
using BridgeTargetAction = void(PKG_GAME_MODE_WAVE7_THISCALL*)(void*,
                                                               std::uint32_t,
                                                               std::uint32_t);
using BridgeRootGet = void* (*)();
using BridgeRootAction = void(PKG_GAME_MODE_WAVE7_THISCALL*)(void*);
using BridgeSummarizerCreate = void* (*)(std::size_t, const char*,
                                         std::uint32_t, std::uint32_t,
                                         std::uint32_t, std::uint32_t);
using BridgeSummarizerServiceGet = void* (*)();
using BridgeSummarizerRegister = void(PKG_GAME_MODE_WAVE7_THISCALL*)(void*,
                                                                     void*);

struct OpaqueAppSystem {
  std::uintptr_t vtable;
};

struct OpaqueGraphics {
  std::uintptr_t vtable;
};

struct BridgePorts {
  BridgeResolve resolve_00b5c9d0 = nullptr;
  BridgeEnsure ensure_00b60d80 = nullptr;
  BridgeNotify notify_212d3e7 = nullptr;
  BridgeNotify notify_22d1adc = nullptr;
  BridgeGetMode get_00b3d270 = nullptr;
  BridgeGetMode get_00b3d280 = nullptr;
  BridgeModeAction action_00b108b0 = nullptr;
  BridgeGetMode get_00b3d320 = nullptr;
  BridgeGetPointer get_00b5b800 = nullptr;
  BridgeDispatchMode dispatch_00b5e3f0 = nullptr;
  BridgeQuery query_00b5ca70 = nullptr;
  BridgeQuery query_00e00ac0 = nullptr;
  OpaqueScenarioMode* (*get_scenario_mode)() = nullptr;
  BridgeAppSystemGet app_system_get = nullptr;
  BridgeAppSystem14 app_system_vtable_14 = nullptr;
  BridgeAppSystem18 app_system_vtable_18 = nullptr;
  BridgeGraphicsGet graphics_get = nullptr;
  BridgeGraphics40 graphics_vtable_40 = nullptr;
  BridgeTreeAction tree_node_vtable_2c = nullptr;
  BridgeTargetQuery query_00d09660 = nullptr;
  BridgeTargetAction action_00d100b0 = nullptr;
  BridgeRootGet get_00fd9c60 = nullptr;
  BridgeRootAction action_00fde3e0 = nullptr;
  BridgeQuery query_01021080 = nullptr;
  BridgeRootGet get_01002bd0 = nullptr;
  BridgePayloadQuery query_00b5cb20 = nullptr;
  BridgeSummarizerCreate create_00f473a0 = nullptr;
  BridgeSummarizerServiceGet get_0067cb40 = nullptr;
  BridgeSummarizerRegister register_summarizer = nullptr;
};

extern "C" BridgePorts g_app_simulator_bridge_ports;

extern "C" bool PKG_GAME_MODE_WAVE7_THISCALL app_simulator_mode_bridge_00b63510(
    OpaqueBridge* bridge, std::uint32_t message_id, void* payload);

struct CellModeObject {
  std::uintptr_t primary_vtable;
  std::uintptr_t secondary_vtable;
};

using CellModeFactory = CellModeObject* (*)(std::size_t, std::uint32_t,
                                            std::uint32_t, std::uint32_t,
                                            std::uint32_t, std::uint32_t);
using CellModeRegister = void(PKG_GAME_MODE_WAVE7_THISCALL*)(CellModeOwner*,
                                                             CellModeObject*,
                                                             const char*,
                                                             const char*);

struct CellModeOwnerVtable {
  std::uintptr_t slots_00[8];
  CellModeRegister register_mode;
};

struct CellModeOwner {
  CellModeOwnerVtable* vtable;
  std::uint8_t opaque_04[0x1c];
};

struct CellModePorts {
  CellModeFactory factory = nullptr;
};

extern "C" CellModePorts g_cell_mode_ports;

extern "C" void cell_mode_constructor_00e616c0(CellModeOwner* owner);

static_assert(sizeof(AppModeVtable) == 0x44, "App mode vtable size");
static_assert(offsetof(AppModeVtable, on_enter) == 0x18,
              "App mode OnEnter slot");
static_assert(offsetof(AppModeVtable, on_exit) == 0x1c, "App mode OnExit slot");
static_assert(offsetof(AppModeVtable, activate_by_index) == 0x40,
              "App registry activation slot");
static_assert(sizeof(AppModeEntry) == 0x18, "App mode entry stride");
static_assert(offsetof(AppModeRegistry, entries_begin) == 0x14,
              "App registry entry begin offset");
static_assert(offsetof(AppModeRegistry, entries_end) == 0x18,
              "App registry entry end offset");
static_assert(offsetof(AppModeRegistry, active_index) == 0x28,
              "App registry active index offset");
static_assert(offsetof(StrategyState, committed_a) == 0x0c,
              "strategy primary committed axis");
static_assert(offsetof(StrategyState, committed_b) == 0x10,
              "strategy secondary committed axis");
static_assert(offsetof(StrategyState, pending) == 0x14,
              "strategy pending axis");
static_assert(offsetof(StrategyState, request_kind) == 0x18,
              "strategy request kind");
static_assert(offsetof(OpaqueModeObject, field_308) == 0x308,
              "mode object observed field offset");
static_assert(offsetof(OpaqueBridge, request_axis) == 0x0c,
              "bridge request axis");
static_assert(offsetof(OpaqueBridge, notification_enabled) == 0x0d,
              "bridge notification flag");
static_assert(offsetof(OpaqueBridge, counter_30) == 0x30,
              "bridge counter offset");
static_assert(offsetof(CellModeOwnerVtable, register_mode) == 0x20,
              "Cell mode registration slot");
static_assert(sizeof(CellModeObject) == 8, "Cell mode object size");
static_assert(std::is_same_v<decltype(&app_mode_activate_index_007d8c80),
                             bool(PKG_GAME_MODE_WAVE7_THISCALL*)(
                                 AppModeRegistry*, std::int32_t)>,
              "App mode activation ABI");
static_assert(std::is_same_v<decltype(&strategy_request_ready_00b5b840),
                             bool(PKG_GAME_MODE_WAVE7_THISCALL*)(
                                 StrategyState*, std::uint32_t)>,
              "strategy request ABI");
static_assert(
    std::is_same_v<decltype(&strategy_commit_primary_00b5b8c0),
                   void(PKG_GAME_MODE_WAVE7_THISCALL*)(StrategyState*)>,
    "strategy commit ABI");
static_assert(std::is_same_v<decltype(&cell_mode_constructor_00e616c0),
                             void (*)(CellModeOwner*)>,
              "Cell mode constructor cdecl ABI");

}

#undef PKG_GAME_MODE_WAVE7_THISCALL
