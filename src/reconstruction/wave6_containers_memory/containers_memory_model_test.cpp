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
    wave6_reference_00432a50;
using openspore::reconstruction::wave6_containers_memory::
    wave6_set_fixed_pool_allocator_ports;
using openspore::reconstruction::wave6_containers_memory::
    Wave6FixedPoolAllocator;
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

void reset_ports() {
  fixed_pool_trace = {};
  wave6_set_fixed_pool_allocator_ports(initialize_port, leave_port);
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
  test_reference_increment();
}
