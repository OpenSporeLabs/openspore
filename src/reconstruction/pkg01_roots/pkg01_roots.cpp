#include "pkg01_roots.hpp"

#include <cstring>

template <typename T>
static T* target_pointer(TargetWord word) {
  return reinterpret_cast<T*>(static_cast<std::uintptr_t>(word));
}

extern "C" {
TargetWord DAT_0167eae0;
TargetWord DAT_0167eae4;
TargetWord DAT_0167eb64;

OpaqueNounManager* PKG01_CDECL FUN_00b3d300() {
  return target_pointer<OpaqueNounManager>(DAT_0167eae0);
}

OpaqueStarManager* PKG01_CDECL FUN_00b3d2a0() {
  return target_pointer<OpaqueStarManager>(DAT_0167eae4);
}

OpaqueUIMissionLogManager* PKG01_CDECL Simulator_GetUIMissionLogManager() {
  return target_pointer<OpaqueUIMissionLogManager>(DAT_0167eb64);
}

std::uint32_t PKG01_FASTCALL FUN_00ff3f00(OpaqueTimelineEventData* receiver) {
  std::uint32_t value;
  std::memcpy(&value, reinterpret_cast<const unsigned char*>(receiver) + 0x8cU,
              sizeof(value));
  return value;
}
}
