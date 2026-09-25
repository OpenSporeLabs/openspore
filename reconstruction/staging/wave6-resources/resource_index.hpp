#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resources {

using TargetWord = std::uint32_t;

struct ResourceKey {
  TargetWord instance_id;
  TargetWord type_id;
  TargetWord group_id;
};

struct ResourceNode {
  TargetWord key;
  ResourceNode* next;
};

struct IndexAllocator {
  void* context;
};

struct IndexOwner {
  std::uint32_t opaque_00;
  ResourceNode** source_buckets;
  TargetWord source_bucket_count;
  std::array<std::uint8_t, 0x10> opaque_0c_1b;
  IndexAllocator* allocator;
  TargetWord allocation_tag;
};

struct IndexServices {
  ResourceNode** (*allocate)(IndexAllocator*, TargetWord, TargetWord,
                             TargetWord);
  void (*zero_fill)(ResourceNode**, TargetWord, TargetWord);
  TargetWord (*release)(IndexAllocator*, ResourceNode**, TargetWord);
};

#if defined(_MSC_VER)
#define WAVE6_RESOURCE_THISCALL __thiscall
#else
#define WAVE6_RESOURCE_THISCALL __attribute__((thiscall))
#endif

IndexServices& index_services();
void set_index_services(const IndexServices* services);
TargetWord WAVE6_RESOURCE_THISCALL resource_manager_initialize_008de530(
    IndexOwner* owner, TargetWord bucket_count);

#undef WAVE6_RESOURCE_THISCALL

static_assert(sizeof(void*) == 4, "wave6 pointers are 32-bit");
static_assert(sizeof(ResourceKey) == 12, "ResourceKey extent");
static_assert(offsetof(ResourceKey, instance_id) == 0,
              "ResourceKey instance offset");
static_assert(offsetof(ResourceKey, type_id) == 4, "ResourceKey type offset");
static_assert(offsetof(ResourceKey, group_id) == 8, "ResourceKey group offset");
static_assert(sizeof(ResourceNode) == 8, "resource node extent");
static_assert(offsetof(ResourceNode, key) == 0, "resource node key offset");
static_assert(offsetof(ResourceNode, next) == 4, "resource node link offset");
static_assert(offsetof(IndexOwner, source_buckets) == 4,
              "index source bucket offset");
static_assert(offsetof(IndexOwner, source_bucket_count) == 8,
              "index source count offset");
static_assert(offsetof(IndexOwner, allocator) == 0x1c,
              "index allocator offset");
static_assert(offsetof(IndexOwner, allocation_tag) == 0x20,
              "index allocation tag offset");
static_assert(sizeof(IndexOwner) == 0x24, "index carrier extent");

}
