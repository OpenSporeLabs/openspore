#include "stream_lifecycle.hpp"

#if defined(_MSC_VER)
#define WAVE6_STREAM_THISCALL __thiscall
#else
#define WAVE6_STREAM_THISCALL __attribute__((thiscall))
#endif

using namespace openspore::reconstruction::wave6_serialization_persistence;

namespace {

bool WAVE6_STREAM_THISCALL default_memory_resize(MemoryStream*, std::uint32_t) {
  return false;
}

bool WAVE6_STREAM_THISCALL default_stream_child_flush(StreamChild*) {
  return true;
}

void WAVE6_STREAM_THISCALL default_free_block(OpaqueAllocator*, void*) {}

void default_free_object(StreamChild*) {}

std::uint32_t position_for(const MemoryStream& stream, std::uint32_t operation,
                           std::uint32_t amount) {
  if (operation == 0) {
    return amount;
  }
  if (operation == 1) {
    return stream.position + amount;
  }
  if (operation == 2) {
    return stream.size + amount;
  }
  return stream.position;
}

}

extern "C" float g_memory_stream_resize_factor;
float g_memory_stream_resize_factor = 1.5F;
extern "C" OpaqueAllocator* g_stream_child_allocator;
OpaqueAllocator* g_stream_child_allocator = nullptr;

namespace openspore::reconstruction::wave6_serialization_persistence {

MemoryStreamServices& memory_stream_services() {
  static MemoryStreamServices services{default_memory_resize};
  return services;
}

StreamChildLifecycleServices& stream_child_lifecycle_services() {
  static StreamChildLifecycleServices services{
      default_stream_child_flush, default_free_block, default_free_object};
  return services;
}

}

extern "C" void __attribute__((naked, thiscall))
memory_stream_initialize_0093bd50(MemoryStream* stream,
                                  std::uint32_t ignored_word) {
  __asm__(
      "movss g_memory_stream_resize_factor, %xmm0\n\t"
      "movl %ecx, %eax\n\t"
      "xorl %ecx, %ecx\n\t"
      "movl $0x0143eb78, (%eax)\n\t"
      "movl %ecx, 0x04(%eax)\n\t"
      "movl %ecx, 0x08(%eax)\n\t"
      "movl %ecx, 0x0c(%eax)\n\t"
      "movl %ecx, 0x10(%eax)\n\t"
      "movl %ecx, 0x14(%eax)\n\t"
      "movb %cl, 0x18(%eax)\n\t"
      "movb %cl, 0x19(%eax)\n\t"
      "movss %xmm0, 0x1c(%eax)\n\t"
      "movl %ecx, 0x20(%eax)\n\t"
      "ret $4");
}

namespace openspore::reconstruction::wave6_serialization_persistence {

bool WAVE6_STREAM_THISCALL memory_stream_set_position_0093c0c0(
    MemoryStream* stream, std::uint32_t operation, std::uint32_t amount) {
  const std::uint32_t original_position = stream->position;
  const std::uint32_t target = position_for(*stream, operation, amount);
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

void WAVE6_STREAM_THISCALL stream_child_teardown_0093b5a0(StreamChild* child) {
  auto& services = stream_child_lifecycle_services();
  child->vtable = reinterpret_cast<void*>(0x0143eaac);
  if (child->active_parent != nullptr) {
    services.flush(child);
    child->opaque_1c = 0;
    child->opaque_20 = 0;
    child->opaque_2c = 0;
    child->opaque_30 = 0;
    child->opaque_0c = 0;
    child->opaque_10 = 0;
    IStream* const parent = child->active_parent;
    if (parent != nullptr) {
      parent->vtable->release(parent);
    }
    child->active_parent = nullptr;
  }
  if (child->owned_block_14 != nullptr) {
    services.free_block(g_stream_child_allocator, child->owned_block_14);
  }
  if (child->owned_block_24 != nullptr) {
    services.free_block(g_stream_child_allocator, child->owned_block_24);
  }
  child->vtable = reinterpret_cast<void*>(0x013f3a68);
}

StreamChild* WAVE6_STREAM_THISCALL stream_child_close_and_maybe_delete_0093b610(
    StreamChild* child, std::uint32_t delete_flags) {
  stream_child_teardown_0093b5a0(child);
  if ((delete_flags & 1U) != 0) {
    stream_child_lifecycle_services().free_object(child);
  }
  return child;
}

}

#undef WAVE6_STREAM_THISCALL
