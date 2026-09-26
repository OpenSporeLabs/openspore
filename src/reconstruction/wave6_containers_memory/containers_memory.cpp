#include "containers_memory.hpp"

namespace openspore::reconstruction::wave6_containers_memory {

#if defined(_MSC_VER)
#define WAVE6_THISCALL __thiscall
#define WAVE6_STDCALL __stdcall
#else
#define WAVE6_THISCALL __attribute__((thiscall))
#define WAVE6_STDCALL __attribute__((stdcall))
#endif

namespace {

void WAVE6_STDCALL default_initialize(void*, std::uint32_t) {}

void WAVE6_STDCALL default_leave(void*) {}

Wave6InitializeCriticalSectionPort initialize_port = default_initialize;
Wave6LeaveCriticalSectionPort leave_port = default_leave;

}

void wave6_set_fixed_pool_allocator_ports(
    Wave6InitializeCriticalSectionPort initialize,
    Wave6LeaveCriticalSectionPort leave) {
  initialize_port = initialize == nullptr ? default_initialize : initialize;
  leave_port = leave == nullptr ? default_leave : leave;
}

void* wave6_fixed_pool_allocator_alloc_00926100(
    Wave6FixedPoolAllocator* allocator) {
  if (allocator == nullptr) {
    return nullptr;
  }
  allocator->field_18 = 0;
  initialize_port(allocator, 10);
  return allocator;
}

std::int32_t wave6_fixed_pool_allocator_free_00926140(
    Wave6FixedPoolAllocator* allocator) {
  const std::int32_t remaining = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(allocator->field_18) - 1u);
  allocator->field_18 = remaining;
  leave_port(allocator);
  return remaining;
}

std::uint32_t WAVE6_THISCALL
wave6_reference_00432a50(Wave6ReferenceCounted* object) {
  const std::int32_t old_count =
      __sync_fetch_and_add(&object->reference_count, 1);
  return static_cast<std::uint32_t>(static_cast<std::uint32_t>(old_count) + 1u);
}

#undef WAVE6_THISCALL
#undef WAVE6_STDCALL

}
