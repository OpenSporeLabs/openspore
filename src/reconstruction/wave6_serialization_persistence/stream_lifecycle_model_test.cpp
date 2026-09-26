#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <vector>

#include "stream_lifecycle.hpp"

#if defined(_MSC_VER)
#define WAVE6_STREAM_THISCALL __thiscall
#else
#define WAVE6_STREAM_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::wave6_serialization_persistence {

struct OpaqueAllocator {
  std::uint32_t value;
};

}

namespace {

using namespace openspore::reconstruction::wave6_serialization_persistence;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::vector<int> events;
StreamChild* observed_child = nullptr;
IStream* expected_parent = nullptr;
OpaqueAllocator first_allocator{1};
OpaqueAllocator second_allocator{2};
void* freed_first = nullptr;
void* freed_second = nullptr;

void invoke_initializer(MemoryStream& stream, std::uint32_t ignored_word) {
  volatile std::uintptr_t stream_address =
      reinterpret_cast<std::uintptr_t>(&stream);
  volatile std::uintptr_t eax_result = 0;
  volatile std::uint32_t ecx_result = 0;
  volatile std::uint32_t edx_result = 0;
  volatile std::uint32_t flags_result = 0;
  volatile std::uint32_t xmm_result = 0;
  __asm__ volatile(
      "pushl %[ignored]\n\t"
      "movl %[stream_address], %%ecx\n\t"
      "movl $0x9abcdef0, %%edx\n\t"
      "call memory_stream_initialize_0093bd50\n\t"
      "movl %%eax, %[eax_result]\n\t"
      "movl %%ecx, %[ecx_result]\n\t"
      "movl %%edx, %[edx_result]\n\t"
      "movd %%xmm0, %[xmm_result]\n\t"
      "pushfl\n\t"
      "popl %[flags_result]\n\t"
      : [eax_result] "=m"(eax_result), [ecx_result] "=m"(ecx_result),
        [edx_result] "=m"(edx_result), [xmm_result] "=m"(xmm_result),
        [flags_result] "=m"(flags_result)
      : [stream_address] "b"(stream_address), [ignored] "r"(ignored_word)
      : "memory");
  check(eax_result == stream_address);
  check(ecx_result == 0);
  check(edx_result == 0x9abcdef0U);
  check(xmm_result == 0x40100000U);
  check((flags_result & 0x00000c45U) == 0x00000044U);
}

bool WAVE6_STREAM_THISCALL resize_success(MemoryStream* stream,
                                          std::uint32_t requested_size) {
  events.push_back(1);
  check(stream->position == requested_size);
  stream->capacity = requested_size + 3;
  return true;
}

bool WAVE6_STREAM_THISCALL resize_failure(MemoryStream* stream,
                                          std::uint32_t requested_size) {
  events.push_back(2);
  check(stream->position == requested_size);
  return false;
}

void WAVE6_STREAM_THISCALL release_parent(IStream* parent) {
  events.push_back(3);
  check(parent == expected_parent);
  check(observed_child != nullptr);
  check(observed_child->active_parent == expected_parent);
  check(observed_child->opaque_0c == 0);
  check(observed_child->opaque_1c == 0);
  check(observed_child->opaque_20 == 0);
  check(observed_child->opaque_2c == 0);
  check(observed_child->opaque_30 == 0);
  check(observed_child->opaque_10 == 0);
}

bool WAVE6_STREAM_THISCALL flush_child(StreamChild* child) {
  events.push_back(4);
  check(child == observed_child);
  check(child->active_parent == expected_parent);
  return false;
}

void WAVE6_STREAM_THISCALL free_block(OpaqueAllocator* allocator,
                                      void* pointer) {
  events.push_back(5);
  if (freed_first == nullptr) {
    check(allocator == &first_allocator);
    freed_first = pointer;
    g_stream_child_allocator = &second_allocator;
  } else {
    check(allocator == &second_allocator);
    freed_second = pointer;
  }
}

void free_object(StreamChild* child) {
  events.push_back(6);
  check(child == observed_child);
  check(child->vtable == reinterpret_cast<void*>(0x013f3a68));
  check(child->active_parent == nullptr);
  check(child->owned_block_14 == freed_first);
  check(child->owned_block_24 == freed_second);
  observed_child = nullptr;
}

void reset_child(StreamChild& child) {
  std::memset(&child, 0, sizeof(child));
  events.clear();
  observed_child = &child;
  expected_parent = nullptr;
  freed_first = nullptr;
  freed_second = nullptr;
  g_stream_child_allocator = &first_allocator;
  auto& services = stream_child_lifecycle_services();
  services.flush = flush_child;
  services.free_block = free_block;
  services.free_object = free_object;
}

void test_memory_stream_initialization() {
  MemoryStream stream{};
  std::memset(&stream, 0xa5, sizeof(stream));
  g_memory_stream_resize_factor = 2.25F;
  invoke_initializer(stream, 0x12345678U);
  g_memory_stream_resize_factor = 1.5F;
  check(stream.vtable == reinterpret_cast<MemoryStreamVtable*>(0x0143eb78));
  check(stream.shared_pointer == nullptr);
  check(stream.reference_count == 0);
  check(stream.size == 0);
  check(stream.capacity == 0);
  check(stream.position == 0);
  check(stream.resize_enabled == 0);
  check(stream.clear_new_memory == 0);
  check(stream.opaque_1a == 0xa5);
  check(stream.opaque_1b == 0xa5);
  check(stream.resize_factor == 2.25F);
  check(stream.resize_increment == 0);
}

void test_memory_stream_position_without_growth() {
  MemoryStream stream{};
  stream.size = 5;
  stream.capacity = 100;
  stream.position = 3;
  stream.resize_enabled = 0;
  memory_stream_services().resize = resize_success;

  check(memory_stream_set_position_0093c0c0(&stream, 0, 2));
  check(stream.position == 2);
  check(memory_stream_set_position_0093c0c0(&stream, 1, 2));
  check(stream.position == 4);
  check(!memory_stream_set_position_0093c0c0(&stream, 2, 2));
  check(stream.position == 5);
  check(stream.capacity == 100);
  check(memory_stream_set_position_0093c0c0(&stream, 3, 99));
  check(stream.position == 5);
  check(!memory_stream_set_position_0093c0c0(
      &stream, 0, std::numeric_limits<std::uint32_t>::max()));
  check(stream.position == 5);
  check(memory_stream_set_position_0093c0c0(&stream, 0, 2));
  check(stream.position == 2);
}

void test_memory_stream_growth_and_rollback() {
  MemoryStream stream{};
  stream.size = 5;
  stream.capacity = 50;
  stream.position = 3;
  stream.resize_enabled = 1;
  events.clear();

  memory_stream_services().resize = resize_success;
  check(memory_stream_set_position_0093c0c0(&stream, 2, 9));
  check(events.size() == 1);
  check(stream.position == 14);
  check(stream.size == 5);
  check(stream.capacity == 17);

  events.clear();
  memory_stream_services().resize = resize_failure;
  check(!memory_stream_set_position_0093c0c0(&stream, 0, 20));
  check(events.size() == 1);
  check(stream.position == 14);
  check(stream.size == 5);
  check(stream.capacity == 17);
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
  child.active_parent = &parent;
  child.opaque_08 = 10;
  child.opaque_0c = 11;
  child.owned_block_14 = &first_block;
  child.opaque_18 = 12;
  child.opaque_1c = 13;
  child.opaque_20 = 14;
  child.owned_block_24 = &second_block;
  child.opaque_28 = 15;
  child.opaque_2c = 16;
  child.opaque_30 = 17;
  child.opaque_10 = 18;
  expected_parent = &parent;

  stream_child_teardown_0093b5a0(&child);

  check(events == std::vector<int>({4, 3, 5, 5}));
  check(child.vtable == reinterpret_cast<void*>(0x013f3a68));
  check(child.active_parent == nullptr);
  check(child.opaque_08 == 10);
  check(child.opaque_0c == 0);
  check(child.owned_block_14 == &first_block);
  check(child.opaque_18 == 12);
  check(child.opaque_1c == 0);
  check(child.opaque_20 == 0);
  check(child.owned_block_24 == &second_block);
  check(child.opaque_28 == 15);
  check(child.opaque_2c == 0);
  check(child.opaque_30 == 0);
  check(child.opaque_10 == 0);
  check(freed_first == &first_block);
  check(freed_second == &second_block);
  check(g_stream_child_allocator == &second_allocator);
}

void test_stream_child_lifecycle_delete_bit() {
  StreamChild child{};
  reset_child(child);
  check(stream_child_close_and_maybe_delete_0093b610(&child, 0xfeU) == &child);
  check(events.empty());

  IStreamVtable parent_vtable{};
  parent_vtable.release = release_parent;
  IStream parent{&parent_vtable};
  std::uint32_t first_block = 3;
  std::uint32_t second_block = 4;
  reset_child(child);
  child.active_parent = &parent;
  child.owned_block_14 = &first_block;
  child.opaque_1c = 5;
  child.opaque_20 = 6;
  child.owned_block_24 = &second_block;
  child.opaque_2c = 7;
  child.opaque_30 = 8;
  child.opaque_10 = 9;
  expected_parent = &parent;

  StreamChild* const result =
      stream_child_close_and_maybe_delete_0093b610(&child, 1U);
  check(result == &child);
  check(events == std::vector<int>({4, 3, 5, 5, 6}));
  check(observed_child == nullptr);
}

}

#undef WAVE6_STREAM_THISCALL

int main() {
  test_memory_stream_initialization();
  test_memory_stream_position_without_growth();
  test_memory_stream_growth_and_rollback();
  test_stream_child_teardown_order();
  test_stream_child_lifecycle_delete_bit();
  return 0;
}
