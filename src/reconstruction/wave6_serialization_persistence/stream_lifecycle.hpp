#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave6 serialization persistence requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "wave6 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "wave6 target words are 32-bit");
static_assert(sizeof(float) == 4, "wave6 target floats are 32-bit");

#if defined(_MSC_VER)
#define WAVE6_STREAM_THISCALL __thiscall
#else
#define WAVE6_STREAM_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_serialization_persistence {

struct MemoryStreamVtable {
  void* slots[15];
};

struct MemoryStream {
  MemoryStreamVtable* vtable;
  void* shared_pointer;
  std::int32_t reference_count;
  std::uint32_t size;
  std::uint32_t capacity;
  std::uint32_t position;
  std::uint8_t resize_enabled;
  std::uint8_t clear_new_memory;
  std::uint8_t opaque_1a;
  std::uint8_t opaque_1b;
  float resize_factor;
  std::int32_t resize_increment;
};

static_assert(sizeof(MemoryStream) == 0x24,
              "memory stream extent is observed at 0x24 bytes");
static_assert(offsetof(MemoryStream, reference_count) == 0x08,
              "memory stream reference count is at 0x08");
static_assert(offsetof(MemoryStream, size) == 0x0c,
              "memory stream size is at 0x0c");
static_assert(offsetof(MemoryStream, capacity) == 0x10,
              "memory stream capacity is at 0x10");
static_assert(offsetof(MemoryStream, position) == 0x14,
              "memory stream position is at 0x14");
static_assert(offsetof(MemoryStream, resize_enabled) == 0x18,
              "memory stream resize flag is at 0x18");
static_assert(offsetof(MemoryStream, clear_new_memory) == 0x19,
              "memory stream clear flag is at 0x19");
static_assert(offsetof(MemoryStream, resize_factor) == 0x1c,
              "memory stream resize factor is at 0x1c");
static_assert(offsetof(MemoryStream, resize_increment) == 0x20,
              "memory stream resize increment is at 0x20");

struct IStream;

using IStreamRelease = void(WAVE6_STREAM_THISCALL*)(IStream*);

struct IStreamVtable {
  void* slots[2];
  IStreamRelease release;
  void* remaining_slots[12];
};

static_assert(offsetof(IStreamVtable, release) == 0x08,
              "stream release is at vtable offset 0x08");
static_assert(sizeof(IStreamVtable) == 0x3c,
              "stream vtable extent is observed at 0x3c bytes");

struct IStream {
  IStreamVtable* vtable;
};

struct StreamChild {
  void* vtable;
  IStream* active_parent;
  std::uint32_t opaque_08;
  std::uint32_t opaque_0c;
  std::uint32_t opaque_10;
  void* owned_block_14;
  std::uint32_t opaque_18;
  std::uint32_t opaque_1c;
  std::uint32_t opaque_20;
  void* owned_block_24;
  std::uint32_t opaque_28;
  std::uint32_t opaque_2c;
  std::uint32_t opaque_30;
};

static_assert(sizeof(StreamChild) == 0x34,
              "stream child teardown extent is observed at 0x34 bytes");
static_assert(offsetof(StreamChild, active_parent) == 0x04,
              "stream child active parent is at 0x04");
static_assert(offsetof(StreamChild, owned_block_14) == 0x14,
              "first owned child block is at 0x14");
static_assert(offsetof(StreamChild, owned_block_24) == 0x24,
              "second owned child block is at 0x24");

struct OpaqueAllocator;

using MemoryStreamResize = bool(WAVE6_STREAM_THISCALL*)(MemoryStream*,
                                                        std::uint32_t);
using StreamChildFlush = bool(WAVE6_STREAM_THISCALL*)(StreamChild*);
using StreamChildFreeBlock = void(WAVE6_STREAM_THISCALL*)(OpaqueAllocator*,
                                                          void*);
using StreamChildFreeObject = void (*)(StreamChild*);

struct MemoryStreamServices {
  MemoryStreamResize resize = nullptr;
};

struct StreamChildLifecycleServices {
  StreamChildFlush flush = nullptr;
  StreamChildFreeBlock free_block = nullptr;
  StreamChildFreeObject free_object = nullptr;
};

extern "C" float g_memory_stream_resize_factor;
extern "C" OpaqueAllocator* g_stream_child_allocator;

MemoryStreamServices& memory_stream_services();
StreamChildLifecycleServices& stream_child_lifecycle_services();

extern "C" void __attribute__((naked, thiscall))
memory_stream_initialize_0093bd50(MemoryStream* stream,
                                  std::uint32_t ignored_word);

bool WAVE6_STREAM_THISCALL memory_stream_set_position_0093c0c0(
    MemoryStream* stream, std::uint32_t operation, std::uint32_t amount);

void WAVE6_STREAM_THISCALL stream_child_teardown_0093b5a0(StreamChild* child);

StreamChild* WAVE6_STREAM_THISCALL stream_child_close_and_maybe_delete_0093b610(
    StreamChild* child, std::uint32_t delete_flags);

}

#undef WAVE6_STREAM_THISCALL
