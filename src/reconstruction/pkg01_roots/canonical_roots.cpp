#include "canonical_roots.hpp"

#include <cstdint>

template <typename T> static T *target_pointer(TargetWord word) {
  return reinterpret_cast<T *>(static_cast<std::uintptr_t>(word));
}

extern "C" {
TargetWord DAT_0167eb60;
TargetWord DAT_0167eb0c;
TargetWord DAT_0167eb50;

OpaqueCanonicalNounManager *PKG01_CDECL FUN_00b3d400() {
  return target_pointer<OpaqueCanonicalNounManager>(DAT_0167eb60);
}

OpaqueCanonicalStarManager *PKG01_CDECL FUN_00b3d3a0() {
  return target_pointer<OpaqueCanonicalStarManager>(DAT_0167eb0c);
}

OpaqueSpaceTradingService *PKG01_CDECL Simulator_cSpaceTrading_Get() {
  return target_pointer<OpaqueSpaceTradingService>(DAT_0167eb50);
}
}
