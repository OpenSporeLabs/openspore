#include "dogfood_008db310.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {

OpaquePorts g_pf_index_write_008db310_ports{};

extern "C" bool PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
pf_index_write_bounds_008db310(OpaqueWriteCarrier* index, void* destination,
                               OpaqueWord destination_size) {
  if (destination_size == 0u) {
    return true;
  }

  OpaqueItemNode* const* const slots = index->slots_2c;
  const OpaqueWord end_slot = index->end_slot_30;
  OpaqueItemNode* const end_node = slots[end_slot];
  const std::uintptr_t destination_begin =
      reinterpret_cast<std::uintptr_t>(destination);
  const std::uintptr_t destination_end =
      destination_begin + static_cast<std::uintptr_t>(destination_size);
  OpaqueWord cursor = 0u;
  OpaqueItemNode* node;

  while (cursor <= end_slot && slots[cursor] == nullptr) {
    ++cursor;
  }
  if (cursor > end_slot) {
    return true;
  }
  node = slots[cursor];

  for (;;) {
    if (node == end_node) {
      return true;
    }
    if (node->record_size_10 != 0u) {
      const std::uintptr_t record_begin =
          static_cast<std::uintptr_t>(node->record_begin_0c);
      const std::uintptr_t record_end =
          record_begin + static_cast<std::uintptr_t>(node->record_size_10);
      if (record_begin < destination_end && destination_begin < record_end) {
        return false;
      }
    }
    node = node->next_1c;
    if (node == nullptr) {
      ++cursor;
      while (cursor <= end_slot && slots[cursor] == nullptr) {
        ++cursor;
      }
      if (cursor > end_slot) {
        return true;
      }
      node = slots[cursor];
    }
  }
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
