#include "diplomacy_predicate.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg13_diplomacy_predicate {
namespace {

std::uint32_t read_u32(const void* address) {
  std::uint32_t value;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

}  // namespace

extern "C" std::uint8_t PKG13_DIPLOMACY_THISCALL
RelationshipManager_IsAllied2_00d01ff0(OpaqueRelationshipManager* receiver,
                                       OpaqueEmpire* empire_a,
                                       OpaqueEmpire* empire_b) {
  OpaqueEmpire* current_empire = reinterpret_cast<OpaqueEmpire*>(
      openspore::reconstruction::pkg12_space::pkg12_space_01021300());
  OpaqueEmpire* first_empire = empire_a;
  OpaqueEmpire* second_empire = empire_b;

  if (first_empire == current_empire && second_empire != nullptr) {
    OpaqueEmpire* temporary = first_empire;
    first_empire = second_empire;
    second_empire = temporary;
  }
  if (second_empire == nullptr) {
    second_empire = current_empire;
  }

  const std::uint32_t key_a =
      read_u32(reinterpret_cast<const unsigned char*>(first_empire) + 0x84U);
  const std::uint32_t key_b =
      read_u32(reinterpret_cast<const unsigned char*>(second_empire) + 0x84U);
  OpaqueRelationshipMap* map =
      pkg13_unresolved_00d01ab0(receiver, key_a, key_b);
  OpaqueRelationshipEntry* entry = pkg13_unresolved_00d01410(map, key_a, key_b);
  if (entry == nullptr) {
    return 0U;
  }

  const std::uint32_t flags =
      read_u32(reinterpret_cast<const unsigned char*>(entry) + 0x04U);
  return static_cast<std::uint8_t>((flags >> 1U) & 1U);
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_predicate
