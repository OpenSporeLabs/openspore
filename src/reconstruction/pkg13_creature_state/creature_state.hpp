#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13 reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-13 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG-13 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG13_CDECL __cdecl
#define PKG13_FASTCALL __fastcall
#define PKG13_THISCALL __thiscall
#else
#define PKG13_CDECL __attribute__((cdecl))
#define PKG13_FASTCALL __attribute__((fastcall))
#define PKG13_THISCALL __attribute__((thiscall))
#endif

struct OpaqueNounManager;
struct OpaqueCreatureGameDataObject;
struct OpaqueTribeState;

extern "C" {
extern float DAT_0169e398;
extern std::uint32_t DAT_0169e394;
extern float DAT_01582e38;
extern float DAT_01582e3c;
extern float DAT_01582e40;
extern float DAT_01582e44;
}

namespace openspore::reconstruction::pkg13_creature_state {

extern "C" {
OpaqueNounManager* PKG13_CDECL FUN_00b3d300();
OpaqueCreatureGameDataObject* PKG13_FASTCALL
FUN_00b1fdb0(OpaqueNounManager* receiver);
float PKG13_CDECL Simulator_cCreatureGameData_GetEvolutionPoints();
float PKG13_CDECL Simulator_cCreatureGameData_GetEvoPointsToNextBrainLevel(
    std::int32_t current_level);
std::uint32_t PKG13_CDECL Simulator_cCreatureGameData_GetAbilityMode();
std::uint32_t PKG13_THISCALL TribeState_test_purchased_tool_bit_00c8ec00(
    OpaqueTribeState* receiver, std::uint32_t tool_index);
}

}  // namespace openspore::reconstruction::pkg13_creature_state
