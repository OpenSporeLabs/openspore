#include "space_player_data_accessors.hpp"

#include <cstring>

template <typename Value>
static Value read_field(const void *object, std::size_t offset) {
  Value value;
  std::memcpy(&value, static_cast<const std::uint8_t *>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Pointer> static TargetWord pointer_word(Pointer pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename Pointer> static Pointer *target_pointer(TargetWord word) {
  return reinterpret_cast<Pointer *>(static_cast<std::uintptr_t>(word));
}

extern "C" {
SpacePlayerDataAccessPrefix *Simulator__sSpacePlayerData = nullptr;

SpaceContextValue PKG01_CDECL FUN_01021080() {
  return read_field<SpaceContextValue>(Simulator__sSpacePlayerData, 0x10U);
}

OpaqueActiveStar *PKG01_CDECL FUN_01021230() {
  return target_pointer<OpaqueActiveStar>(
      read_field<TargetWord>(Simulator__sSpacePlayerData, 0x08U));
}

ActivePlanetAccessWindow *PKG01_CDECL FUN_01021260() {
  if (Simulator__sSpacePlayerData == nullptr) {
    return nullptr;
  }
  return target_pointer<ActivePlanetAccessWindow>(
      read_field<TargetWord>(Simulator__sSpacePlayerData, 0x04U));
}

OpaqueActivePlanetField13c *PKG01_CDECL FUN_010212a0() {
  if (Simulator__sSpacePlayerData == nullptr) {
    return nullptr;
  }
  ActivePlanetAccessWindow *active_planet =
      target_pointer<ActivePlanetAccessWindow>(
          read_field<TargetWord>(Simulator__sSpacePlayerData, 0x04U));
  if (active_planet == nullptr) {
    return nullptr;
  }
  return target_pointer<OpaqueActivePlanetField13c>(
      read_field<TargetWord>(active_planet, 0x13cU));
}
}
