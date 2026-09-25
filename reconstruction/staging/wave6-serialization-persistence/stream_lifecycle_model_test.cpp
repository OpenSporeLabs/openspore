#include "stream_lifecycle.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

#if defined(_MSC_VER)
#define WAVE6_STREAM_THISCALL __thiscall
#else
#define WAVE6_STREAM_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::wave6_serialization_persistence;

std::vector<int> events;
StreamChild* observed_child = nullptr;
IStream* expected_parent = nullptr;
void* freed_first = nullptr;
void* freed_second = nullptr;
void* freed_allocator = nullptr;

MemoryStream* invoke_initializer(MemoryStream& stream,
                                 std::uint32_t ignored_debug_name) {
  MemoryStream* result = nullptr;
  __asm__ volatile(
      "pushl %[ignored]\n\t"
      "movl %[stream], %%eax\n\t"
      "call memory_stream_initialize_0093bd50\n\t"
      : "=a"(result)
      : [ignored] "r"(ignored_debug_name), [stream] "r"(&stream)
      : "ecx", "edx", "cc", "memory");
  return result;
}

bool resize_success(MemoryStream* stream, std::uint32_t requested_size) {
  events.push_back(1);
  assert(stream->position == requested_size);
  stream->capacity = requested_size + 3;
  stream->size = requested_size;
  return true;
}

bool resize_failure(MemoryStream* stream, std::uint32_t requested_size) {
  events.push_back(2);
  assert(stream->position == requested_size);
  return false;
}

void WAVE6_STREAM_THISCALL release_parent(IStream* parent) {
  events.push_back(3);
  assert(parent == expected_parent);
  assert(observed_child != nullptr);
  assert(observed_child->parent == expected_parent);
  assert(observed_child->parent_position == 0);
  assert(observed_child->read_buffer_used == 0);
  assert(observed_child->read_buffer_start == 0);
  assert(observed_child->write_buffer_used == 0);
  assert(observed_child->opaque_30 == 0);
}

bool flush_child(StreamChild* child) {
  events.push_back(4);
  assert(child == observed_child);
  assert(child->parent == expected_parent);
  return true;
}

void free_block(void* allocator, void* pointer) {
  events.push_back(5);
  if (freed_first == nullptr) {
    freed_allocator = allocator;
    freed_first = pointer;
  } else {
    freed_second = pointer;
  }
}

void free_object(StreamChild* child) {
  events.push_back(6);
  assert(child == observed_child);
}

void reset_child(StreamChild& child) {
  std::memset(&child, 0, sizeof(child));
  events.clear();
  observed_child = &child;
  expected_parent = nullptr;
  freed_first = nullptr;
  freed_second = nullptr;
  freed_allocator = nullptr;
  auto& services = stream_child_lifecycle_services();
  services.flush = flush_child;
  services.free_block = free_block;
  services.free_object = free_object;
}

void test_memory_stream_initialization() {
  MemoryStream stream{};
  std::memset(&stream, 0xa5, sizeof(stream));
  MemoryStream* result = invoke_initializer(stream, 0x12345678U);
  assert(result == &stream);
  assert(stream.vtable == reinterpret_cast<MemoryStreamVtable*>(0x0143eb78));
  assert(stream.shared_pointer == nullptr);
  assert(stream.reference_count == 0);
  assert(stream.size == 0);
  assert(stream.capacity == 0);
  assert(stream.position == 0);
  assert(stream.resize_enabled == 0);
  assert(stream.clear_new_memory == 0);
  assert(stream.opaque_1a == 0xa5);
  assert(stream.opaque_1b == 0xa5);
  assert(stream.resize_factor == 1.5F);
  assert(stream.resize_increment == 0);
}

void test_memory_stream_position_without_growth() {
  MemoryStream stream{};
  stream.size = 5;
  stream.position = 3;
  stream.resize_enabled = 0;
  memory_stream_services().resize = resize_success;

  assert(memory_stream_set_position_0093c0c0(&stream, 2, 0));
  assert(stream.position == 2);
  assert(memory_stream_set_position_0093c0c0(&stream, 2, 1));
  assert(stream.position == 4);
  assert(!memory_stream_set_position_0093c0c0(&stream, 2, 2));
  assert(stream.position == 5);
  assert(memory_stream_set_position_0093c0c0(&stream, 1, 0));
  assert(stream.position == 1);
  assert(memory_stream_set_position_0093c0c0(&stream, 99, 3));
  assert(stream.position == 1);
  assert(!memory_stream_set_position_0093c0c0(
      &stream, std::numeric_limits<std::uint32_t>::max(), 0));
  assert(!memory_stream_set_position_0093c0c0(
      &stream, 2, 0));
  assert(stream.position == 5);
}

void test_memory_stream_growth_and_rollback() {
  MemoryStream stream{};
  stream.size = 5;
  stream.position = 3;
  stream.resize_enabled = 1;
  events.clear();

  memory_stream_services().resize = resize_success;
  assert(memory_stream_set_position_0093c0c0(&stream, 9, 0));
  assert(events.size() == 1);
  assert(stream.position == 9);
  assert(stream.size == 9);
  assert(stream.capacity == 12);

  events.clear();
  memory_stream_services().resize = resize_failure;
  assert(!memory_stream_set_position_0093c0c0(&stream, 20, 0));
  assert(events.size() == 1);
  assert(stream.position == 9);
  assert(stream.size == 9);
  assert(stream.capacity == 12);
}

void test_stream_child_teardown_order() {
  IStreamVtable parent_vtable{};
  parent_vtable.release = release_parent;
  IStream parent{&parent_vtable};
  std::uint32_t first_block = 1;
  std::uint32_t second_block = 2;
  StreamChild child{};
  reset_child(child);
  child.vtable = reinterpret_cast<void*>(0xdeadbeef);
  child.parent = &parent;
  child.parent_position = 11;
  child.owned_block_14 = reinterpret_cast<std::uintptr_t>(&first_block);
  child.opaque_18 = 12;
  child.read_buffer_used = 13;
  child.read_buffer_start = 14;
  child.owned_block_24 = reinterpret_cast<std::uintptr_t>(&second_block);
  child.opaque_28 = 15;
  child.write_buffer_used = 16;
  child.opaque_30 = 17;
  expected_parent = &parent;

  stream_child_teardown_0093b5a0(&child);

  assert(events.size() == 4);
  assert(events[0] == 4);
  assert(events[1] == 3);
  assert(events[2] == 5);
  assert(events[3] == 5);
  assert(child.vtable == reinterpret_cast<void*>(0x013f3a68));
  assert(child.parent == nullptr);
  assert(child.parent_position == 0);
  assert(child.read_buffer_used == 0);
  assert(child.read_buffer_start == 0);
  assert(child.write_buffer_used == 0);
  assert(child.opaque_30 == 0);
  assert(child.opaque_18 == 12);
  assert(child.opaque_28 == 15);
  assert(freed_allocator == reinterpret_cast<void*>(0x016c8b44));
  assert(freed_first == &first_block);
  assert(freed_second == &second_block);
}

void test_stream_child_close_delete_flag() {
  StreamChild child{};
  reset_child(child);

  StreamChild* result =
      stream_child_close_and_maybe_delete_0093b610(&child, 0);
  assert(result == &child);
  assert(events.empty());
  assert(child.vtable == reinterpret_cast<void*>(0x013f3a68));

  events.clear();
  result = stream_child_close_and_maybe_delete_0093b610(&child, 0xfeU);
  assert(result == &child);
  assert(events.empty());

  events.clear();
  result = stream_child_close_and_maybe_delete_0093b610(&child, 1U);
  assert(result == &child);
  assert(events.size() == 1);
  assert(events[0] == 6);
}

}

#undef WAVE6_STREAM_THISCALL

int main() {
  test_memory_stream_initialization();
  test_memory_stream_position_without_growth();
  test_memory_stream_growth_and_rollback();
  test_stream_child_teardown_order();
  test_stream_child_close_delete_flag();
  return 0;
}
