#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11 staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-11 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG-11 target words are 32-bit");

namespace openspore::reconstruction::pkg11_sim_core {

enum class StarType : std::uint32_t {
  None = 0,
  GalacticCore = 1,
  BlackHole = 2,
  ProtoPlanetary = 3,
  StarG = 4,
  StarO = 5,
  StarM = 6,
  BinaryOO = 7,
  BinaryOM = 8,
  BinaryOG = 9,
  BinaryGG = 10,
  BinaryGM = 11,
  BinaryMM = 12,
};

inline constexpr std::uint32_t kIsNotStarOrBinaryStarReturnWord = 0x0355c93aU;

extern "C" std::uint32_t Simulator_IsNotStarOrBinaryStar(StarType star_type);

}
