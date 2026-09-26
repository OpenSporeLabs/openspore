#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resources {

struct PFIndexNode {
  std::array<std::uint8_t, 0x0c> opaque_00_0b;
  std::uint32_t record_offset;
  std::uint32_t record_size;
  std::array<std::uint8_t, 8> opaque_14_1b;
  PFIndexNode* next;
};

struct PFIndexModifiableWriteCarrier {
  void* vftable;
  void* parent_allocator;
  std::array<std::uint8_t, 0x20> allocator_prefix_08_27;
  std::array<std::uint8_t, 4> opaque_28_2b;
  PFIndexNode** item_buckets;
  std::uint32_t item_bucket_count;
  std::array<std::uint8_t, 0x18> opaque_34_4b;
};

#if defined(_MSC_VER)
#define WAVE6_PF_INDEX_THISCALL __thiscall
#else
#define WAVE6_PF_INDEX_THISCALL __attribute__((thiscall))
#endif

bool WAVE6_PF_INDEX_THISCALL pf_index_modifiable_write_008db310(
    PFIndexModifiableWriteCarrier* index, void* destination,
    std::uint32_t destination_size);

#undef WAVE6_PF_INDEX_THISCALL

static_assert(sizeof(void*) == 4, "wave6 pointers are 32-bit");
static_assert(sizeof(PFIndexNode) == 0x20, "PF index node extent");
static_assert(offsetof(PFIndexNode, record_offset) == 0x0c,
              "PF index record offset");
static_assert(offsetof(PFIndexNode, record_size) == 0x10,
              "PF index record size");
static_assert(offsetof(PFIndexNode, next) == 0x1c, "PF index next offset");
static_assert(sizeof(PFIndexModifiableWriteCarrier) == 0x4c,
              "PF index write carrier extent");
static_assert(offsetof(PFIndexModifiableWriteCarrier, item_buckets) == 0x2c,
              "PF index bucket offset");
static_assert(offsetof(PFIndexModifiableWriteCarrier, item_bucket_count) ==
                  0x30,
              "PF index bucket count offset");

}
