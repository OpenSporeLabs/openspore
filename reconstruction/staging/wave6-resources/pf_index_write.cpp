#include "pf_index_write.hpp"

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_PF_INDEX_THISCALL __thiscall
#else
#define WAVE6_PF_INDEX_THISCALL __attribute__((thiscall))
#endif

bool WAVE6_PF_INDEX_THISCALL pf_index_modifiable_write_008db310(
    PFIndexModifiableWriteCarrier* index, void* destination,
    std::uint32_t destination_size) {
  if (destination_size == 0) {
    return true;
  }

  PFIndexNode* const* buckets = index->item_buckets;
  const std::uint32_t bucket_count = index->item_bucket_count;
  PFIndexNode* const end_node = buckets[bucket_count];
  const std::uintptr_t destination_begin =
      reinterpret_cast<std::uintptr_t>(destination);
  const std::uintptr_t destination_end = destination_begin + destination_size;
  std::uint32_t bucket = 0;

  for (;;) {
    while (bucket <= bucket_count && buckets[bucket] == nullptr) {
      ++bucket;
    }
    if (bucket > bucket_count) {
      return true;
    }
    PFIndexNode* node = buckets[bucket];
    if (node == end_node) {
      return true;
    }
    while (node != nullptr && node != end_node) {
      if (node->record_size != 0) {
        const std::uintptr_t record_begin = node->record_offset;
        const std::uintptr_t record_end = record_begin + node->record_size;
        if (record_begin < destination_end && destination_begin < record_end) {
          return false;
        }
      }
      node = node->next;
    }
    ++bucket;
  }
}

#undef WAVE6_PF_INDEX_THISCALL

}
