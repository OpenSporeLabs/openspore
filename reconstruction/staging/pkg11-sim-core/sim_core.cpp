#include "sim_core.hpp"

namespace openspore::reconstruction::pkg11_sim_core {

extern "C" std::uint32_t Simulator_IsNotStarOrBinaryStar(StarType) {
  return kIsNotStarOrBinaryStarReturnWord;
}

}
