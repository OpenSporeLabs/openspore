#include "canonical_roots.hpp"

#include <cassert>
#include <cstdint>
#include <type_traits>

struct OpaqueNounManager {};
struct OpaqueStarManager {};
struct OpaqueCanonicalNounManager {};
struct OpaqueCanonicalStarManager {};
struct OpaqueSpaceTradingService {};

using AlternateNounAccessor = OpaqueNounManager *(*)();
using AlternateStarAccessor = OpaqueStarManager *(*)();
using CanonicalNounAccessor = OpaqueCanonicalNounManager *(*)();
using CanonicalStarAccessor = OpaqueCanonicalStarManager *(*)();
using SpaceTradingAccessor = OpaqueSpaceTradingService *(*)();

static_assert(
    std::is_same<decltype(&FUN_00b3d300), AlternateNounAccessor>::value);
static_assert(
    std::is_same<decltype(&FUN_00b3d2a0), AlternateStarAccessor>::value);
static_assert(
    std::is_same<decltype(&FUN_00b3d400), CanonicalNounAccessor>::value);
static_assert(
    std::is_same<decltype(&FUN_00b3d3a0), CanonicalStarAccessor>::value);
static_assert(std::is_same<decltype(&Simulator_cSpaceTrading_Get),
                           SpaceTradingAccessor>::value);
static_assert(sizeof(AlternateNounAccessor) == sizeof(void *));
static_assert(sizeof(CanonicalNounAccessor) == sizeof(void *));
static_assert(sizeof(SpaceTradingAccessor) == sizeof(void *));

template <typename Pointer> TargetWord pointer_word(Pointer pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

int main() {
  OpaqueNounManager alternate_noun{};
  OpaqueStarManager alternate_star{};
  OpaqueCanonicalNounManager canonical_noun{};
  OpaqueCanonicalStarManager canonical_star{};
  OpaqueSpaceTradingService trading_service{};

  DAT_0167eae0 = pointer_word(&alternate_noun);
  DAT_0167eae4 = pointer_word(&alternate_star);
  DAT_0167eb60 = pointer_word(&canonical_noun);
  DAT_0167eb0c = pointer_word(&canonical_star);
  DAT_0167eb50 = pointer_word(&trading_service);

  const TargetWord alternate_noun_word = DAT_0167eae0;
  const TargetWord alternate_star_word = DAT_0167eae4;
  const TargetWord canonical_noun_word = DAT_0167eb60;
  const TargetWord canonical_star_word = DAT_0167eb0c;
  const TargetWord trading_service_word = DAT_0167eb50;

  assert(FUN_00b3d300() == &alternate_noun);
  assert(FUN_00b3d2a0() == &alternate_star);
  assert(FUN_00b3d400() == &canonical_noun);
  assert(FUN_00b3d3a0() == &canonical_star);
  assert(Simulator_cSpaceTrading_Get() == &trading_service);
  assert(DAT_0167eae0 == alternate_noun_word);
  assert(DAT_0167eae4 == alternate_star_word);
  assert(DAT_0167eb60 == canonical_noun_word);
  assert(DAT_0167eb0c == canonical_star_word);
  assert(DAT_0167eb50 == trading_service_word);

  DAT_0167eb60 = 0;
  assert(FUN_00b3d400() == nullptr);
  assert(FUN_00b3d300() == &alternate_noun);
  assert(FUN_00b3d2a0() == &alternate_star);
  assert(FUN_00b3d3a0() == &canonical_star);
  assert(Simulator_cSpaceTrading_Get() == &trading_service);

  DAT_0167eb0c = 0;
  assert(FUN_00b3d3a0() == nullptr);
  assert(FUN_00b3d400() == nullptr);
  assert(Simulator_cSpaceTrading_Get() == &trading_service);

  DAT_0167eae0 = 0;
  DAT_0167eae4 = 0;
  DAT_0167eb50 = 0;
  assert(FUN_00b3d300() == nullptr);
  assert(FUN_00b3d2a0() == nullptr);
  assert(FUN_00b3d400() == nullptr);
  assert(FUN_00b3d3a0() == nullptr);
  assert(Simulator_cSpaceTrading_Get() == nullptr);

  return 0;
}
