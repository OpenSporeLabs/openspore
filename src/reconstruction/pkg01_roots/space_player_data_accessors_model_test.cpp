#include "space_player_data_accessors.hpp"

#include <cassert>
#include <cstring>
#include <type_traits>

using ContextAccessor = SpaceContextValue (*)();
using StarAccessor = OpaqueActiveStar *(*)();
using PlanetAccessor = ActivePlanetAccessWindow *(*)();
using Field13cAccessor = OpaqueActivePlanetField13c *(*)();

static_assert(std::is_same<decltype(&FUN_01021080), ContextAccessor>::value);
static_assert(std::is_same<decltype(&FUN_01021230), StarAccessor>::value);
static_assert(std::is_same<decltype(&FUN_01021260), PlanetAccessor>::value);
static_assert(std::is_same<decltype(&FUN_010212a0), Field13cAccessor>::value);

template <typename Value>
static void store_field(void *object, std::size_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t *>(object) + offset, &value,
              sizeof(value));
}

template <typename Pointer> static TargetWord pointer_word(Pointer pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

int main() {
  OpaqueActiveStar active_star{};
  ActivePlanetAccessWindow active_planet{};
  OpaqueActivePlanetField13c field_13c{};
  store_field<TargetWord>(active_planet.bytes, 0x13cU,
                          pointer_word(&field_13c));

  SpacePlayerDataAccessPrefix state{};
  state.active_planet_word = pointer_word(&active_planet);
  state.active_star_word = pointer_word(&active_star);
  state.current_context = SpaceContextValue::kGalaxy;

  Simulator__sSpacePlayerData = &state;
  SpacePlayerDataAccessPrefix state_before = state;
  ActivePlanetAccessWindow planet_before = active_planet;

  assert(FUN_01021080() == SpaceContextValue::kGalaxy);
  assert(FUN_01021230() == &active_star);
  assert(FUN_01021260() == &active_planet);
  assert(FUN_010212a0() == &field_13c);
  assert(std::memcmp(&state, &state_before, sizeof(state)) == 0);
  assert(std::memcmp(&active_planet, &planet_before, sizeof(active_planet)) ==
         0);

  state.active_planet_word = 0;
  assert(FUN_01021080() == SpaceContextValue::kGalaxy);
  assert(FUN_01021230() == &active_star);
  assert(FUN_01021260() == nullptr);
  assert(FUN_010212a0() == nullptr);

  state.active_star_word = 0;
  assert(FUN_01021230() == nullptr);

  Simulator__sSpacePlayerData = nullptr;
  assert(FUN_01021260() == nullptr);
  assert(FUN_010212a0() == nullptr);

  return 0;
}
