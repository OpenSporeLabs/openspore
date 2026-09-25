#include "resource_index.hpp"

#include <cstring>
#include <new>

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_RESOURCE_THISCALL __thiscall
#else
#define WAVE6_RESOURCE_THISCALL __attribute__((thiscall))
#endif

namespace {

ResourceNode** default_allocate(IndexAllocator*, TargetWord bytes, TargetWord,
                                TargetWord) {
  return static_cast<ResourceNode**>(::operator new(bytes));
}

void default_zero_fill(ResourceNode** buckets, TargetWord value,
                       TargetWord bytes) {
  std::memset(buckets, value, bytes);
}

TargetWord default_release(IndexAllocator*, ResourceNode** buckets,
                           TargetWord) {
  ::operator delete(buckets);
  return 0;
}

const IndexServices kDefaultServices{default_allocate, default_zero_fill,
                                     default_release};

}

IndexServices& index_services() {
  static IndexServices services = kDefaultServices;
  return services;
}

void set_index_services(const IndexServices* services) {
  index_services() = services == nullptr ? kDefaultServices : *services;
}

TargetWord WAVE6_RESOURCE_THISCALL resource_manager_initialize_008de530(
    IndexOwner* owner, TargetWord bucket_count) {
  IndexServices& services = index_services();
  const TargetWord destination_bytes = bucket_count * 4u + 4u;
  ResourceNode** destination = services.allocate(
      owner->allocator, destination_bytes, 0, owner->allocation_tag);
  services.zero_fill(destination, 0, destination_bytes);
  destination[bucket_count] = reinterpret_cast<ResourceNode*>(
      static_cast<std::uintptr_t>(UINT32_MAX));

  for (TargetWord bucket = 0; bucket < owner->source_bucket_count; ++bucket) {
    ResourceNode* node = owner->source_buckets[bucket];
    while (node != nullptr) {
      ResourceNode* next = node->next;
      const TargetWord destination_bucket = node->key % bucket_count;
      owner->source_buckets[bucket] = next;
      node->next = destination[destination_bucket];
      destination[destination_bucket] = node;
      node = next;
    }
  }

  TargetWord result = owner->source_bucket_count;
  if (owner->source_bucket_count > 1) {
    result = services.release(owner->allocator, owner->source_buckets,
                              owner->source_bucket_count * 4u + 4u);
  }
  owner->source_buckets = destination;
  owner->source_bucket_count = bucket_count;
  return result;
}

#undef WAVE6_RESOURCE_THISCALL

}
