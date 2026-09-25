#pragma once

#include "pkg01_roots.hpp"

struct OpaqueCanonicalNounManager;
struct OpaqueCanonicalStarManager;
struct OpaqueSpaceTradingService;

extern "C" {
extern TargetWord DAT_0167eb60;
extern TargetWord DAT_0167eb0c;
extern TargetWord DAT_0167eb50;

OpaqueCanonicalNounManager *PKG01_CDECL FUN_00b3d400();
OpaqueCanonicalStarManager *PKG01_CDECL FUN_00b3d3a0();
OpaqueSpaceTradingService *PKG01_CDECL Simulator_cSpaceTrading_Get();
}
