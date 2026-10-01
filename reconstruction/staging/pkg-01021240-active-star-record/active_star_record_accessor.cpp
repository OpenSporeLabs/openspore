#include "active_star_record_accessor.hpp"

#include <cstring>

namespace {

TargetWord word_at(const void *base, std::size_t displacement) {
  TargetWord value;
  std::memcpy(&value,
              static_cast<const std::uint8_t *>(base) + displacement,
              sizeof(value));
  return value;
}

const void *object_at(TargetWord word) {
  return reinterpret_cast<const void *>(static_cast<std::uintptr_t>(word));
}

}  // namespace

extern "C" {

SpacePlayerDataStarPrefix *Simulator__sSpacePlayerData = nullptr;

std::uint32_t PKG_ASR_CDECL FUN_01021240() {
  static_assert(kContainerWord == 0x016dda8c);
  // 0x01021240 MOV EAX,[0x016dda8c] / MOV EAX,[EAX + 0x8]: the container word is
  // read with no test of its own, so a null container is dereferenced here just
  // as the machine does it. The only null test in the body guards the star word.
  const TargetWord active_star =
      word_at(Simulator__sSpacePlayerData, kActiveStarDisplacement);
  if (active_star == 0) {
    return 0;
  }
  return word_at(object_at(active_star), kStarRecordDisplacement);
}

}  // extern "C"