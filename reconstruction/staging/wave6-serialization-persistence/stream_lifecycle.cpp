#include "stream_lifecycle.hpp"

#include <limits>

#if defined(_MSC_VER)
#define WAVE6_STREAM_THISCALL __thiscall
#else
#define WAVE6_STREAM_THISCALL __attribute__((thiscall))
#endif

using namespace openspore::reconstruction::wave6_serialization_persistence;

namespace {

bool default_memory_resize(MemoryStream*, std::uint32_t) { return false; }

bool default_stream_child_flush(StreamChild*) { return true; }

void default_free_block(void*, void*) {}

void default_free_object(StreamChild*) {}

std::uint32_t position_for(const MemoryStream& stream, std::uint32_t distance,
                           std::uint32_t position_type) {
  if (position_type == 0) {
    return distance;
  }
  if (position_type == 1) {
    return stream.position + distance;
  }
  if (position_type == 2) {
    return stream.size + distance;
  }
  return stream.position;
}

}

extern "C" MemoryStream* wave6_memory_stream_initialize_body(
    MemoryStream* stream, std::uint32_t ignored_debug_name) {
  (void)ignored_debug_name;
  stream->vtable = reinterpret_cast<MemoryStreamVtable*>(0x0143eb78);
  stream->shared_pointer = nullptr;
  stream->reference_count = 0;
  stream->size = 0;
  stream->capacity = 0;
  stream->position = 0;
  stream->resize_enabled = 0;
  stream->clear_new_memory = 0;
  stream->resize_factor = 1.5F;
  stream->resize_increment = 0;
  return stream;
}

namespace openspore::reconstruction::wave6_serialization_persistence {

MemoryStreamServices& memory_stream_services() {
  static MemoryStreamServices services{default_memory_resize};
  return services;
}

StreamChildLifecycleServices& stream_child_lifecycle_services() {
  static StreamChildLifecycleServices services{
      reinterpret_cast<void*>(0x016c8b44), default_stream_child_flush,
      default_free_block, default_free_object};
  return services;
}

}

extern "C" MemoryStream* __attribute__((naked, stdcall))
memory_stream_initialize_0093bd50(std::uint32_t) {
  __asm__("pushl %eax\n\t"
          "call wave6_memory_stream_initialize_body\n\t"
          "addl $4, %esp\n\t"
          "ret $4");
}

namespace openspore::reconstruction::wave6_serialization_persistence {

bool WAVE6_STREAM_THISCALL memory_stream_set_position_0093c0c0(
    MemoryStream* stream, std::uint32_t distance,
    std::uint32_t position_type) {
  const std::uint32_t original_position = stream->position;
  const std::uint32_t target = position_for(*stream, distance, position_type);
  stream->position = target;
  if (target <= stream->size) {
    return true;
  }
  if (stream->resize_enabled == 0) {
    stream->position = stream->size;
    return false;
  }
  if (!memory_stream_services().resize(stream, target)) {
    stream->position = original_position;
    return false;
  }
  return true;
}

void WAVE6_STREAM_THISCALL stream_child_teardown_0093b5a0(
    StreamChild* child) {
  auto& services = stream_child_lifecycle_services();
  child->vtable = reinterpret_cast<void*>(0x0143eaac);
  if (child->parent != nullptr) {
    services.flush(child);
    IStream* const parent = child->parent;
    child->read_buffer_used = 0;
    child->read_buffer_start = 0;
    child->write_buffer_used = 0;
    child->opaque_30 = 0;
    child->parent_position = 0;
    if (parent != nullptr) {
      parent->vtable->release(parent);
    }
    child->parent = nullptr;
  }
  if (child->owned_block_14 != 0) {
    services.free_block(
        services.allocator,
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(
            child->owned_block_14)));
  }
  if (child->owned_block_24 != 0) {
    services.free_block(
        services.allocator,
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(
            child->owned_block_24)));
  }
  child->vtable = reinterpret_cast<void*>(0x013f3a68);
}

StreamChild* WAVE6_STREAM_THISCALL
stream_child_close_and_maybe_delete_0093b610(StreamChild* child,
                                              std::uint32_t delete_flags) {
  stream_child_teardown_0093b5a0(child);
  if ((delete_flags & 1U) != 0) {
    stream_child_lifecycle_services().free_object(child);
  }
  return child;
}

}

#undef WAVE6_STREAM_THISCALL
