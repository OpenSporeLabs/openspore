#include "sim_core.hpp"

#include <cassert>
#include <cstdint>

namespace {

using openspore::reconstruction::pkg11_sim_core::
    kIsNotStarOrBinaryStarReturnWord;
using openspore::reconstruction::pkg11_sim_core::
    Simulator_IsNotStarOrBinaryStar;
using openspore::reconstruction::pkg11_sim_core::StarType;

void test_supported_states() {
  constexpr StarType supported[] = {
      StarType::None,           StarType::GalacticCore, StarType::BlackHole,
      StarType::ProtoPlanetary, StarType::StarG,        StarType::StarO,
      StarType::StarM,          StarType::BinaryOO,     StarType::BinaryOM,
      StarType::BinaryOG,       StarType::BinaryGG,     StarType::BinaryGM,
      StarType::BinaryMM,
  };

  for (const StarType state : supported) {
    const std::uint32_t result = Simulator_IsNotStarOrBinaryStar(state);
    assert(result == kIsNotStarOrBinaryStarReturnWord);
    assert(static_cast<bool>(result));
  }
}

void test_null_and_sentinel_words() {
  const StarType null_word = static_cast<StarType>(0U);
  const StarType all_ones = static_cast<StarType>(0xffffffffU);
  const StarType unsupported = static_cast<StarType>(13U);

  assert(Simulator_IsNotStarOrBinaryStar(null_word) == 0x0355c93aU);
  assert(Simulator_IsNotStarOrBinaryStar(all_ones) == 0x0355c93aU);
  assert(Simulator_IsNotStarOrBinaryStar(unsupported) == 0x0355c93aU);
}

void test_exact_return_width() {
  static_assert(
      sizeof(decltype(Simulator_IsNotStarOrBinaryStar(StarType::None))) == 4,
      "the staged return is a 32-bit machine word");
  static_assert(sizeof(StarType) == 4, "StarType occupies one target word");

  const std::uint32_t result =
      Simulator_IsNotStarOrBinaryStar(StarType::BinaryMM);
  assert((result & 0x000000ffU) == 0x3aU);
  assert((result & 0xffffff00U) == 0x0355c900U);
  assert(result != 0U);
  assert(result != 1U);
}

}

int main() {
  test_supported_states();
  test_null_and_sentinel_words();
  test_exact_return_width();
}
