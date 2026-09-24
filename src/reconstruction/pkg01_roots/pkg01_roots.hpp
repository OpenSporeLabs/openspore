#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-01 staging requires an x86-32 target and has no 64-bit fallback"
#endif

using TargetWord = std::uint32_t;
static_assert(sizeof(TargetWord) == 4, "PKG-01 target words are 32-bit");
static_assert(sizeof(void*) == sizeof(TargetWord),
              "PKG-01 target pointers and pointer words must both be 32-bit");

#if defined(_MSC_VER)
#define PKG01_CDECL __cdecl
#define PKG01_FASTCALL __fastcall
#else
#define PKG01_CDECL __attribute__((cdecl))
#define PKG01_FASTCALL __attribute__((fastcall))
#endif

struct OpaqueNounManager;
struct OpaqueStarManager;
struct OpaqueUIMissionLogManager;
struct OpaqueTimelineEventData;

extern "C" {
extern TargetWord DAT_0167eae0;
extern TargetWord DAT_0167eae4;
extern TargetWord DAT_0167eb64;

OpaqueNounManager* PKG01_CDECL FUN_00b3d300();
OpaqueStarManager* PKG01_CDECL FUN_00b3d2a0();
OpaqueUIMissionLogManager* PKG01_CDECL Simulator_GetUIMissionLogManager();
std::uint32_t PKG01_FASTCALL FUN_00ff3f00(OpaqueTimelineEventData* receiver);
}
