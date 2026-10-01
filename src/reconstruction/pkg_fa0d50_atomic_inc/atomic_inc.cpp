#include "atomic_inc.hpp"

namespace openspore::reconstruction::pkg_fa0d50_atomic_inc {

std::uint32_t PKG_FA0D50_ATOMIC_INC_THISCALL atomic_increment_00fa0d50(std::uint8_t* receiver) {
  std::uint8_t* const adjusted = receiver + kReceiverAdjust;
  Word* const counter = reinterpret_cast<Word*>(adjusted);
  Word const previous = __atomic_fetch_add(counter, kIncrement, __ATOMIC_SEQ_CST);
  return previous + kIncrement;
}

}  // namespace openspore::reconstruction::pkg_fa0d50_atomic_inc
