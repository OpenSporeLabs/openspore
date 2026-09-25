#include "diplomacy_primitives.hpp"

#include <cstddef>
#include <cstring>

namespace openspore::reconstruction::pkg13_diplomacy_primitives {
namespace {

template <typename T>
T* pointer_at(const void* object, std::size_t offset) {
  std::uint32_t word;
  std::memcpy(&word, static_cast<const unsigned char*>(object) + offset,
              sizeof(word));
  return reinterpret_cast<T*>(static_cast<std::uintptr_t>(word));
}

struct KeyPair {
  std::uint32_t a;
  std::uint32_t b;
};

std::uint32_t read_u32(const void* object, std::size_t offset) {
  std::uint32_t value;
  std::memcpy(&value, static_cast<const unsigned char*>(object) + offset,
              sizeof(value));
  return value;
}

std::uint8_t read_u8(const void* object, std::size_t offset) {
  return static_cast<const unsigned char*>(object)[offset];
}

}  // namespace

extern "C" OpaqueRelationshipEntry* PKG13_PRIM_STDCALL
RelationshipLookup_00d01410(OpaqueRelationshipMap* map, std::uint32_t key_a,
                            std::uint32_t key_b) {
  KeyPair normalized{key_a, key_b};
  pkg13_unresolved_00d009a0(&normalized.a, &normalized.b);
  OpaqueRelationshipNode* node = nullptr;
  pkg13_unresolved_00d00f80(map, &node, &normalized.a);
  const auto* sentinel = reinterpret_cast<const unsigned char*>(map) + 0x04U;
  if (node == reinterpret_cast<const OpaqueRelationshipNode*>(sentinel)) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueRelationshipEntry*>(
      reinterpret_cast<unsigned char*>(node) + 0x18U);
}

extern "C" OpaqueRelationshipMap* PKG13_PRIM_THISCALL
RelationshipMapSelect_00d01ab0(OpaqueRelationshipManager* receiver,
                               std::uint32_t key_a, std::uint32_t key_b) {
  pkg13_unresolved_00d009a0(&key_a, &key_b);
  OpaqueSpaceContext* context = pkg13_unresolved_010212a0();
  if (context != nullptr) {
    const bool first_high_bit = pkg13_unresolved_00ba6650(key_a) != 0U;
    if (first_high_bit && pkg13_unresolved_00ba6650(key_b) != 0U) {
      return reinterpret_cast<OpaqueRelationshipMap*>(
          reinterpret_cast<unsigned char*>(receiver) + 0x24U);
    }

    std::uint32_t context_key = pkg13_unresolved_00ce6950(context);
    OpaqueRelationshipRecord* begin =
        pointer_at<OpaqueRelationshipRecord>(receiver, 0x9cU);
    OpaqueRelationshipRecord* end =
        pointer_at<OpaqueRelationshipRecord>(receiver, 0xa0U);
    const std::uint32_t ignored_word = read_u8(receiver, 0xb0U);
    OpaqueRelationshipRecord* candidate =
        pkg13_unresolved_00d01210(begin, end, &context_key, ignored_word);
    if (candidate == end) {
      candidate = end;
    } else {
      const std::uintptr_t candidate_address =
          reinterpret_cast<std::uintptr_t>(candidate);
      if (context_key < read_u32(candidate, 0U) ||
          candidate_address == candidate_address + 0x20U) {
        candidate = end;
      }
    }
    if (candidate != end) {
      return reinterpret_cast<OpaqueRelationshipMap*>(
          reinterpret_cast<unsigned char*>(candidate) + 0x04U);
    }
  }
  return reinterpret_cast<OpaqueRelationshipMap*>(
      reinterpret_cast<unsigned char*>(receiver) + 0x24U);
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_primitives
