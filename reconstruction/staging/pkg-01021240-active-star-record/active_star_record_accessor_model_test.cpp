#include "active_star_record_accessor.hpp"

#include <cassert>
#include <cstring>
#include <type_traits>

using Accessor = std::uint32_t(PKG_ASR_CDECL *)();

static_assert(std::is_same<decltype(&FUN_01021240), Accessor>::value,
              "the body takes nothing and returns one 32-bit word in EAX");

namespace {

// The two displacements are restated here as literals, independently of the
// package's own constants. A model test that borrowed them would track a change
// to the reconstruction instead of contradicting it, so each case below places
// and expects words at the addresses the machine listing prints.
constexpr std::size_t kObservedContainerDisplacement = 0x8;
constexpr std::size_t kObservedStarDisplacement = 0x48;
constexpr std::size_t kBandByte = 0xa5;

// One flat image per object, band-filled end to end, so a read at any
// displacement the reconstruction did not claim returns the band value and a
// write anywhere shows up as a changed byte.
struct Image {
  alignas(TargetWord) std::uint8_t bytes[256];
};

TargetWord pointer_word(const void *pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

void store_word(Image &image, std::size_t displacement, TargetWord word) {
  std::memcpy(image.bytes + displacement, &word, sizeof(word));
}

}  // namespace

int main() {
  Image container;
  Image star;
  std::memset(container.bytes, kBandByte, sizeof(container.bytes));
  std::memset(star.bytes, kBandByte, sizeof(star.bytes));

  std::uint8_t record_object[8] = {};
  const TargetWord expected = pointer_word(record_object);
  store_word(star, kObservedStarDisplacement, expected);

  const Image star_before = star;

  // Case 1: the star word is present, so the word at the star displacement is
  // returned unchanged. Every other word still holds the band value.
  store_word(container, kObservedContainerDisplacement,
             pointer_word(star.bytes));
  const Image container_before = container;
  Simulator__sSpacePlayerData =
      reinterpret_cast<SpacePlayerDataStarPrefix *>(container.bytes);
  assert(FUN_01021240() == expected);
  assert(FUN_01021240() != static_cast<std::uint32_t>(kBandByte));

  // Read-only on both objects: every band byte survives the call.
  assert(std::memcmp(star.bytes, star_before.bytes, sizeof(star.bytes)) == 0);
  assert(std::memcmp(container.bytes, container_before.bytes,
                     sizeof(container.bytes)) == 0);

  // Case 2: a zero star word takes the guard and returns a zero word.
  store_word(container, kObservedContainerDisplacement, 0);
  assert(FUN_01021240() == 0U);
  assert(std::memcmp(star.bytes, star_before.bytes, sizeof(star.bytes)) == 0);

  // Case 3: a second distinct word round-trips, so the result is the stored
  // word itself and not a neighbouring one.
  const TargetWord second = 0xfeedfaceU;
  store_word(star, kObservedStarDisplacement, second);
  store_word(container, kObservedContainerDisplacement,
             pointer_word(star.bytes));
  assert(FUN_01021240() == second);

  return 0;
}