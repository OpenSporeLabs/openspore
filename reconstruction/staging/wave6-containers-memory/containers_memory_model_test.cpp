#include <cassert>
#include <cstdint>
#include <limits>

#include "containers_memory.hpp"

#if defined(_MSC_VER)
#define WAVE6_TEST_THISCALL __thiscall
#define WAVE6_TEST_STDCALL __stdcall
#else
#define WAVE6_TEST_THISCALL __attribute__((thiscall))
#define WAVE6_TEST_STDCALL __attribute__((stdcall))
#endif

namespace {

using openspore::reconstruction::wave6_containers_memory::
    wave6_fixed_pool_allocator_alloc_00926100;
using openspore::reconstruction::wave6_containers_memory::
    wave6_fixed_pool_allocator_free_00926140;
using openspore::reconstruction::wave6_containers_memory::
    wave6_memory_stream_seek_0093c0c0;
using openspore::reconstruction::wave6_containers_memory::
    wave6_reference_00432a50;
using openspore::reconstruction::wave6_containers_memory::
    wave6_set_fixed_pool_allocator_ports;
using openspore::reconstruction::wave6_containers_memory::
    wave6_set_memory_stream_resize_port;
using openspore::reconstruction::wave6_containers_memory::
    Wave6FixedPoolAllocator;
using openspore::reconstruction::wave6_containers_memory::Wave6MemoryStream;
using openspore::reconstruction::wave6_containers_memory::Wave6ReferenceCounted;

struct FixedPoolTrace {
  int initialize_calls;
  int leave_calls;
  std::uint32_t spin_count;
  Wave6FixedPoolAllocator* initialized;
  Wave6FixedPoolAllocator* left;
};

FixedPoolTrace fixed_pool_trace{};

void WAVE6_TEST_STDCALL initialize_port(void* object,
                                        std::uint32_t spin_count) {
  ++fixed_pool_trace.initialize_calls;
  fixed_pool_trace.spin_count = spin_count;
  fixed_pool_trace.initialized = static_cast<Wave6FixedPoolAllocator*>(object);
}

void WAVE6_TEST_STDCALL leave_port(void* object) {
  ++fixed_pool_trace.leave_calls;
  fixed_pool_trace.left = static_cast<Wave6FixedPoolAllocator*>(object);
}

struct ResizeTrace {
  int calls;
  std::uint32_t requested;
  std::uint32_t position_before;
};

ResizeTrace resize_trace{};

bool WAVE6_TEST_THISCALL resize_success(Wave6MemoryStream* stream,
                                        std::uint32_t requested) {
  ++resize_trace.calls;
  resize_trace.requested = requested;
  resize_trace.position_before = stream->position;
  stream->capacity = requested;
  return true;
}

bool WAVE6_TEST_THISCALL resize_failure(Wave6MemoryStream* stream,
                                        std::uint32_t requested) {
  ++resize_trace.calls;
  resize_trace.requested = requested;
  resize_trace.position_before = stream->position;
  return false;
}

void reset_ports() {
  fixed_pool_trace = {};
  resize_trace = {};
  wave6_set_fixed_pool_allocator_ports(initialize_port, leave_port);
  wave6_set_memory_stream_resize_port(resize_failure);
}

void test_fixed_pool_alloc() {
  reset_ports();
  Wave6FixedPoolAllocator allocator{};
  allocator.field_18 = 7;
  assert(wave6_fixed_pool_allocator_alloc_00926100(&allocator) == &allocator);
  assert(allocator.field_18 == 0);
  assert(fixed_pool_trace.initialize_calls == 1);
  assert(fixed_pool_trace.spin_count == 10);
  assert(fixed_pool_trace.initialized == &allocator);
  assert(wave6_fixed_pool_allocator_alloc_00926100(nullptr) == nullptr);
  assert(fixed_pool_trace.initialize_calls == 1);
}

void test_fixed_pool_free() {
  reset_ports();
  Wave6FixedPoolAllocator allocator{};
  allocator.field_18 = 2;
  assert(wave6_fixed_pool_allocator_free_00926140(&allocator) == 1);
  assert(allocator.field_18 == 1);
  assert(fixed_pool_trace.leave_calls == 1);
  assert(fixed_pool_trace.left == &allocator);

  allocator.field_18 = std::numeric_limits<std::int32_t>::min();
  assert(wave6_fixed_pool_allocator_free_00926140(&allocator) ==
         std::numeric_limits<std::int32_t>::max());
  assert(allocator.field_18 == std::numeric_limits<std::int32_t>::max());
  assert(fixed_pool_trace.leave_calls == 2);
}

void test_memory_stream_seek_without_growth() {
  reset_ports();
  Wave6MemoryStream stream{};
  stream.capacity = 10;
  stream.position = 4;
  stream.resize_enabled = 1;
  assert(wave6_memory_stream_seek_0093c0c0(&stream, 0, 3));
  assert(stream.position == 3);
  assert(wave6_memory_stream_seek_0093c0c0(&stream, 1, 2));
  assert(stream.position == 5);
  assert(wave6_memory_stream_seek_0093c0c0(&stream, 2, -1u));
  assert(stream.position == 9);
  assert(wave6_memory_stream_seek_0093c0c0(&stream, 7, 100));
  assert(stream.position == 9);
  assert(resize_trace.calls == 0);
}

void test_memory_stream_seek_with_growth() {
  reset_ports();
  wave6_set_memory_stream_resize_port(resize_success);
  Wave6MemoryStream stream{};
  stream.capacity = 10;
  stream.position = 4;
  stream.resize_enabled = 1;
  assert(wave6_memory_stream_seek_0093c0c0(&stream, 0, 20));
  assert(stream.position == 20);
  assert(stream.capacity == 20);
  assert(resize_trace.calls == 1);
  assert(resize_trace.requested == 20);
  assert(resize_trace.position_before == 20);
}

void test_memory_stream_seek_clamp_and_failure_rollback() {
  reset_ports();
  Wave6MemoryStream clamped{};
  clamped.capacity = 5;
  clamped.position = 2;
  clamped.resize_enabled = 0;
  assert(!wave6_memory_stream_seek_0093c0c0(&clamped, 0, 9));
  assert(clamped.position == 5);
  assert(resize_trace.calls == 0);

  Wave6MemoryStream rolled_back{};
  rolled_back.capacity = 5;
  rolled_back.position = 2;
  rolled_back.resize_enabled = 1;
  assert(!wave6_memory_stream_seek_0093c0c0(&rolled_back, 1, 5));
  assert(rolled_back.position == 2);
  assert(resize_trace.calls == 1);
  assert(resize_trace.requested == 7);
  assert(resize_trace.position_before == 7);
}

void test_reference_increment() {
  Wave6ReferenceCounted object{};
  object.reference_count = 4;
  assert(wave6_reference_00432a50(&object) == 5u);
  assert(object.reference_count == 5);
  object.reference_count = std::numeric_limits<std::int32_t>::max();
  assert(wave6_reference_00432a50(&object) ==
         static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::min()));
  assert(object.reference_count == std::numeric_limits<std::int32_t>::min());
}

}

#undef WAVE6_TEST_THISCALL
#undef WAVE6_TEST_STDCALL

int main() {
  test_fixed_pool_alloc();
  test_fixed_pool_free();
  test_memory_stream_seek_without_growth();
  test_memory_stream_seek_with_growth();
  test_memory_stream_seek_clamp_and_failure_rollback();
  test_reference_increment();
}
