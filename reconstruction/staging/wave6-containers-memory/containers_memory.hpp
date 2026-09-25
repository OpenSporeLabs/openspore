#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave6 containers and memory staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define WAVE6_THISCALL __thiscall
#define WAVE6_STDCALL __stdcall
#else
#define WAVE6_THISCALL __attribute__((thiscall))
#define WAVE6_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::wave6_containers_memory {

struct Wave6FixedPoolAllocator {
  void* vftable;
  void* allocator;
  std::int32_t field_8;
  std::int32_t field_c;
  std::int32_t field_10;
  std::size_t object_size;
  std::int32_t field_18;
  std::int32_t field_1c;
};

struct Wave6MemoryStream {
  void* vftable;
  void* shared_pointer;
  std::int32_t reference_count;
  std::uint32_t size;
  std::uint32_t capacity;
  std::uint32_t position;
  std::uint8_t resize_enabled;
  std::uint8_t clear_new_memory;
  std::uint8_t reserved_1a[2];
  float resize_factor;
  std::int32_t resize_increment;
};

struct Wave6ReferenceCounted {
  void* vftable;
  std::int32_t reference_count;
};

using Wave6InitializeCriticalSectionPort = void(WAVE6_STDCALL*)(void*,
                                                                std::uint32_t);
using Wave6LeaveCriticalSectionPort = void(WAVE6_STDCALL*)(void*);
using Wave6MemoryStreamResizePort = bool(WAVE6_THISCALL*)(Wave6MemoryStream*,
                                                          std::uint32_t);

static_assert(sizeof(void*) == 4, "wave6 target pointers are 32-bit");
static_assert(sizeof(Wave6FixedPoolAllocator) == 32,
              "wave6 fixed-pool layout size");
static_assert(offsetof(Wave6FixedPoolAllocator, object_size) == 0x14,
              "wave6 fixed-pool object size offset");
static_assert(offsetof(Wave6FixedPoolAllocator, field_18) == 0x18,
              "wave6 fixed-pool active count offset");
static_assert(offsetof(Wave6FixedPoolAllocator, field_1c) == 0x1c,
              "wave6 fixed-pool trailing field offset");
static_assert(sizeof(Wave6MemoryStream) == 36, "wave6 memory-stream size");
static_assert(offsetof(Wave6MemoryStream, size) == 0x0c,
              "wave6 memory-stream size offset");
static_assert(offsetof(Wave6MemoryStream, capacity) == 0x10,
              "wave6 memory-stream capacity offset");
static_assert(offsetof(Wave6MemoryStream, position) == 0x14,
              "wave6 memory-stream position offset");
static_assert(offsetof(Wave6MemoryStream, resize_enabled) == 0x18,
              "wave6 memory-stream resize flag offset");
static_assert(offsetof(Wave6MemoryStream, resize_factor) == 0x1c,
              "wave6 memory-stream resize factor offset");
static_assert(offsetof(Wave6MemoryStream, resize_increment) == 0x20,
              "wave6 memory-stream resize increment offset");
static_assert(offsetof(Wave6ReferenceCounted, reference_count) == 0x04,
              "wave6 reference count offset");

void* wave6_fixed_pool_allocator_alloc_00926100(
    Wave6FixedPoolAllocator* allocator);
std::int32_t wave6_fixed_pool_allocator_free_00926140(
    Wave6FixedPoolAllocator* allocator);
WAVE6_THISCALL bool wave6_memory_stream_seek_0093c0c0(Wave6MemoryStream* stream,
                                                      std::uint32_t operation,
                                                      std::uint32_t amount);
WAVE6_THISCALL std::uint32_t wave6_reference_00432a50(
    Wave6ReferenceCounted* object);

void wave6_set_fixed_pool_allocator_ports(
    Wave6InitializeCriticalSectionPort initialize,
    Wave6LeaveCriticalSectionPort leave);
void wave6_set_memory_stream_resize_port(Wave6MemoryStreamResizePort resize);

}

#undef WAVE6_THISCALL
#undef WAVE6_STDCALL
