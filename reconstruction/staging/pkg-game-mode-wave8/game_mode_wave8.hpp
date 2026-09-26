#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-GAME-MODE-WAVE8 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_GAME_MODE_WAVE8_THISCALL __thiscall
#define PKG_GAME_MODE_WAVE8_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_GAME_MODE_WAVE8_THISCALL __attribute__((thiscall))
#define PKG_GAME_MODE_WAVE8_CDECL __attribute__((cdecl))
#else
#error "PKG-GAME-MODE-WAVE8 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_game_mode_wave8 {

using ModeWord = std::uint32_t;

inline constexpr ModeWord kModeGalaxy = 0x02ccd1d2U;
inline constexpr ModeWord kModeEditorTarget = 0x00dbdba1U;
inline constexpr ModeWord kModeCell = 0x01654c00U;
inline constexpr ModeWord kModeCreature = 0x01654c01U;
inline constexpr ModeWord kModeTribe = 0x01654c02U;
inline constexpr ModeWord kModeCivilisation = 0x01654c04U;
inline constexpr ModeWord kModeSpace = 0x01654c05U;
inline constexpr ModeWord kModeScenario = 0x01654c10U;
inline constexpr ModeWord kModeEditor = 0x01654c08U;
inline constexpr ModeWord kNoMode = 0xffffffffU;

struct OpaqueModeTransition;
struct OpaqueParticipant;
struct OpaquePairServiceVtable;
struct OpaqueService;
struct OpaqueReturnService;
struct OpaqueService48;
struct OpaqueAppSystem;
struct OpaqueRenderer;
struct OpaqueSpeciesManager;

struct OpaqueService {
  OpaquePairServiceVtable* vtable;
};

struct OpaqueSpeciesManager {
  std::uint8_t opaque[4];
};

using ParticipantTransition =
    void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueParticipant*, ModeWord, ModeWord);
using StrategyTransition =
    void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueModeTransition*, ModeWord);
using StrategyFinalize =
    void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueModeTransition*);
using ServiceTransition = void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*,
                                                              ModeWord,
                                                              ModeWord);
using ServiceEmpty = void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*);
using ServiceReturn = void*(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*);
using ServiceConfigure = bool(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*,
                                                             ModeWord);
using ServiceFinalize =
    std::uint32_t(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*, ModeWord);
using TelemetryReset = void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueService*,
                                                           ModeWord);
using AppInitialize = void(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueAppSystem*,
                                                          ModeWord, ModeWord,
                                                          ModeWord);
using RendererSetViewer =
    OpaqueRenderer*(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueRenderer*);
using RendererQuery = bool(PKG_GAME_MODE_WAVE8_THISCALL*)(OpaqueRenderer*,
                                                          struct TextVector*);
using SpeciesInitialize = void(PKG_GAME_MODE_WAVE8_THISCALL*)(
    OpaqueSpeciesManager*, struct TextVector*);
using ContextQuery = bool(PKG_GAME_MODE_WAVE8_THISCALL*)(void*, ModeWord);
using ContextSet = void(PKG_GAME_MODE_WAVE8_THISCALL*)(void*, ModeWord,
                                                       std::uint8_t);
using ContextReset = void(PKG_GAME_MODE_WAVE8_THISCALL*)(void*);
using ContextFinalize = void(PKG_GAME_MODE_WAVE8_THISCALL*)(void*, ModeWord);
using PairDispatch = void (*)(ModeWord, ModeWord);
using TextAppend = void(PKG_GAME_MODE_WAVE8_THISCALL*)(struct TextVector*,
                                                       const char*,
                                                       const char*);
using TextTransform = struct TextVector*(
    PKG_GAME_MODE_WAVE8_CDECL*)(struct TextVector*, const struct TextVector*);
using TextBuild = struct TextVector*(
    PKG_GAME_MODE_WAVE8_CDECL*)(struct TextVector*, const struct TextVector*,
                                const char*);
using TextFree = void(PKG_GAME_MODE_WAVE8_CDECL*)(const char*);

struct OpaqueParticipantVtable {
  std::uintptr_t slots_00[5];
  ParticipantTransition slot_14;
  ParticipantTransition slot_18;
};

struct OpaqueParticipant {
  OpaqueParticipantVtable* vtable;
};

struct OpaquePairServiceVtable {
  std::uintptr_t slot_00;
  ServiceTransition slot_04;
  ServiceTransition slot_08;
  ServiceTransition slot_0c;
  std::uintptr_t slot_10;
  ServiceTransition slot_14;
  ServiceTransition slot_18;
};

struct OpaquePairService {
  OpaquePairServiceVtable* vtable;
};

struct OpaqueReturnServiceVtable {
  std::uintptr_t slot_00;
  ServiceReturn slot_04;
};

struct OpaqueReturnService {
  OpaqueReturnServiceVtable* vtable;
};

struct OpaqueService48Vtable {
  std::uintptr_t slots_00[18];
  ServiceEmpty slot_48;
};

struct OpaqueService48 {
  OpaqueService48Vtable* vtable;
};

struct OpaqueAppSystemVtable {
  std::uintptr_t slots_00[5];
  AppInitialize slot_14;
};

struct OpaqueAppSystem {
  OpaqueAppSystemVtable* vtable;
};

struct OpaqueRendererVtable {
  std::uintptr_t slots_00[11];
  RendererSetViewer slot_2c;
};

struct OpaqueRenderer {
  OpaqueRendererVtable* vtable;
};

struct OpaqueModeTransitionVtable {
  std::uintptr_t slots_00[5];
  StrategyTransition slot_14;
  std::uintptr_t slots_18[11];
  StrategyFinalize slot_44;
  std::uintptr_t slots_48[4];
  StrategyFinalize slot_58;
};

struct OpaqueModeTransition {
  OpaqueModeTransitionVtable* vtable;
  std::uint8_t opaque_04[8];
  std::uint8_t transition_flag_0c;
  std::uint8_t opaque_0d[0x4f];
  std::uint8_t* participants_begin;
  std::uint8_t* participants_end;
};

struct OpaqueSimulationState {
  std::uint8_t opaque_00[0x20];
  ModeWord shared_state;
  ModeWord first_mode;
  std::uint8_t transition_flag_28;
};

struct TextVector {
  const char* begin;
  const char* end;
  const char* capacity;
};

struct TextRange {
  const char* begin;
  const char* end;
};

struct SimulatorGlobals {
  std::uint8_t flag_01686af0;
};

using StateFollowupCall = void(PKG_GAME_MODE_WAVE8_THISCALL*)(void*);

struct TransitionPorts {
  OpaqueSimulationState* (*state_root_00b3d320)() = nullptr;
  void* (*state_followup_00b3d380)() = nullptr;
  StateFollowupCall state_followup_call_00b31a90 = nullptr;
  void (*clear_00b2fbe0)() = nullptr;
  StrategyTransition strategy_00b5e3f0 = nullptr;
  void* (*context_get_00805070)() = nullptr;
  ContextQuery context_query_00810760 = nullptr;
  ContextSet context_set_00810660 = nullptr;
  PairDispatch pair_dispatch_00b33970 = nullptr;
  PairDispatch pair_dispatch_00b335d0 = nullptr;
  OpaqueReturnService* (*return_service_get_0067caa0)() = nullptr;
  ContextReset context_reset_008153e0 = nullptr;
  ContextFinalize context_finalize_00812d60 = nullptr;
  OpaqueService* (*pair_service_get_00d38840)() = nullptr;
  OpaqueService* (*pair_service_get_00cd40b0)() = nullptr;
  OpaqueService* (*pair_service_get_00cf74c0)() = nullptr;
  OpaqueService* (*pair_service_get_00fd9c60)() = nullptr;
  OpaqueService* (*pair_service_get_00d1bf00)() = nullptr;
  OpaqueService* (*tail_service_get_0067cab0)() = nullptr;
  ServiceConfigure tail_configure_00801bb0 = nullptr;
  ServiceFinalize tail_finalize_008017f0 = nullptr;
  OpaqueService48* (*service_get_0067ddd0)() = nullptr;
  OpaqueAppSystem* (*app_system_get_0067dcc0)() = nullptr;
  OpaqueService* (*telemetry_service_get_0067de90)() = nullptr;
  TelemetryReset telemetry_reset_007ebce0 = nullptr;
  OpaqueRenderer* (*renderer_get_0067dd10)() = nullptr;
  OpaqueSpeciesManager* (*species_manager_get_00401090)() = nullptr;
  SpeciesInitialize species_initialize_004df310 = nullptr;
  RendererSetViewer renderer_set_viewer_slot_2c = nullptr;
  RendererQuery renderer_query_005805e0 = nullptr;
  TextAppend append_text_00454cb0 = nullptr;
  TextTransform transform_text_0093c570 = nullptr;
  TextBuild build_text_0091ba90 = nullptr;
  TextFree free_text_00f47380 = nullptr;
};

extern "C" TransitionPorts g_game_mode_wave8_ports;
extern "C" SimulatorGlobals g_game_mode_wave8_globals;

extern "C" void PKG_GAME_MODE_WAVE8_THISCALL
simulator_strategy_transition_00b5f040(OpaqueModeTransition*, ModeWord,
                                       ModeWord);
extern "C" void PKG_GAME_MODE_WAVE8_THISCALL
simulator_strategy_transition_00b5dbb0(OpaqueModeTransition*, ModeWord,
                                       ModeWord);

static_assert(sizeof(void*) == 4,
              "PKG-GAME-MODE-WAVE8 target pointers are 32-bit");
static_assert(sizeof(ModeWord) == 4,
              "PKG-GAME-MODE-WAVE8 mode words are 32-bit");
static_assert(offsetof(OpaqueParticipantVtable, slot_14) == 0x14,
              "participant transition vtable slot");
static_assert(offsetof(OpaqueParticipantVtable, slot_18) == 0x18,
              "participant transition vtable slot");
static_assert(sizeof(OpaquePairServiceVtable) == 0x1c,
              "pair service vtable window");
static_assert(offsetof(OpaqueService48Vtable, slot_48) == 0x48,
              "service transition vtable slot");
static_assert(offsetof(OpaqueRendererVtable, slot_2c) == 0x2c,
              "renderer viewer vtable slot");
static_assert(offsetof(OpaqueModeTransitionVtable, slot_44) == 0x44,
              "strategy transition vtable slot");
static_assert(offsetof(OpaqueModeTransitionVtable, slot_58) == 0x58,
              "mode transition vtable slot");
static_assert(offsetof(OpaqueModeTransition, transition_flag_0c) == 0x0c,
              "transition flag offset");
static_assert(offsetof(OpaqueModeTransition, participants_begin) == 0x5c,
              "participant vector begin offset");
static_assert(offsetof(OpaqueModeTransition, participants_end) == 0x60,
              "participant vector end offset");
static_assert(offsetof(OpaqueSimulationState, shared_state) == 0x20,
              "shared state offset");
static_assert(offsetof(OpaqueSimulationState, first_mode) == 0x24,
              "first mode state offset");
static_assert(offsetof(OpaqueSimulationState, transition_flag_28) == 0x28,
              "transition state flag offset");
static_assert(std::is_same_v<decltype(&simulator_strategy_transition_00b5f040),
                             void(PKG_GAME_MODE_WAVE8_THISCALL*)(
                                 OpaqueModeTransition*, ModeWord, ModeWord)>,
              "strategy transition ABI");
static_assert(std::is_same_v<decltype(&simulator_strategy_transition_00b5dbb0),
                             void(PKG_GAME_MODE_WAVE8_THISCALL*)(
                                 OpaqueModeTransition*, ModeWord, ModeWord)>,
              "mode transition ABI");

}

#undef PKG_GAME_MODE_WAVE8_THISCALL
#undef PKG_GAME_MODE_WAVE8_CDECL
