#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C3 creature progression wave2 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG13-C3 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG13-C3 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG13_C3_CDECL __cdecl
#define PKG13_C3_THISCALL __thiscall
#else
#define PKG13_C3_CDECL __attribute__((cdecl))
#define PKG13_C3_THISCALL __attribute__((thiscall))
#endif

extern "C" {
extern float DAT_0169e398;
extern float DAT_01582e54;
}

namespace openspore::reconstruction::pkg13_c3_creature_progression_wave2 {

inline constexpr std::uint32_t kAddEvolutionPointsActionId = 0x045ab96eU;

struct OpaqueNounManager {
  std::uint32_t opaque_word = 0;
};

struct OpaqueAvatar;

struct ProgressionPlayerAccessWindow {
  std::array<std::uint8_t, 0x10f4> bytes{};
};

struct OpaqueActionStrategy {
  std::array<std::uint8_t, 0x68> opaque{};
  OpaqueAvatar* transition_receiver = nullptr;
};

struct OpaqueActionPayload {
  OpaqueAvatar* avatar = nullptr;
  std::uint32_t action_word = 0;
  float points = 0.0F;
};

struct OpaqueCreatureGameData {
  std::uint8_t opaque[1]{};
};

using GetNounManagerPort = OpaqueNounManager* (*)();
using GetProgressionPlayerPort = ProgressionPlayerAccessWindow*(
    PKG13_C3_THISCALL*)(OpaqueNounManager * receiver);
using EventGatePort = const void* (*)();
using GetActionStrategyPort = OpaqueActionStrategy* (*)();
using TransitionAvatarPort = void(PKG13_C3_THISCALL*)(OpaqueAvatar* receiver,
                                                      float points);
using GetAvatarPort = OpaqueAvatar*(PKG13_C3_THISCALL*)(OpaqueNounManager *
                                                        receiver);
using ExecuteActionPort = void(PKG13_C3_THISCALL*)(
    OpaqueActionStrategy* strategy, std::uint32_t action_id,
    const OpaqueActionPayload* payload);

struct NativePorts {
  GetNounManagerPort get_noun_manager = nullptr;
  GetProgressionPlayerPort get_progression_player = nullptr;
  EventGatePort get_event_gate = nullptr;
  GetActionStrategyPort get_action_strategy = nullptr;
  TransitionAvatarPort transition_avatar = nullptr;
  GetAvatarPort get_avatar = nullptr;
  ExecuteActionPort execute_action = nullptr;
};

static_assert(sizeof(GetNounManagerPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(GetProgressionPlayerPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(EventGatePort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(GetActionStrategyPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(TransitionAvatarPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(GetAvatarPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(sizeof(ExecuteActionPort) == 4,
              "PKG13-C3 target function pointers are 32-bit");
static_assert(offsetof(ProgressionPlayerAccessWindow, bytes) == 0,
              "PKG13-C3 player access window starts at byte zero");
static_assert(sizeof(ProgressionPlayerAccessWindow) >= 0x10f4,
              "PKG13-C3 player access window includes +0x10f0");
static_assert(offsetof(OpaqueActionStrategy, transition_receiver) == 0x68,
              "PKG13-C3 action transition receiver is at +0x68");
static_assert(sizeof(OpaqueActionPayload) == 12,
              "PKG13-C3 action payload is three words");

extern NativePorts g_native_ports;

const void* event_gate_sentinel();

extern "C" void PKG13_C3_CDECL
Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0(float points);

extern "C" OpaqueCreatureGameData* PKG13_C3_CDECL
Simulator_cCreatureGameData_Get_00d2e340();

static_assert(
    std::is_same<
        decltype(&Simulator_cCreatureGameData_AddEvolutionPoints_raw_00d2e8a0),
        void(PKG13_C3_CDECL*)(float)>::value,
    "PKG13-C3 AddEvolutionPoints ABI");
static_assert(std::is_same<decltype(&Simulator_cCreatureGameData_Get_00d2e340),
                           OpaqueCreatureGameData*(PKG13_C3_CDECL*)()>::value,
              "PKG13-C3 creature accessor ABI");

}
