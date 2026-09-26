#include "c0c080_find_index.hpp"

#include <cstring>

namespace openspore::reconstruction::wave13_w1_core_b10 {

namespace {

// Both slots are indirect calls in the original with ECX pre-loaded to the
// receiver (0x00c0c08e and 0x00c0c0ab both issue CALL EDX with ECX untouched
// since 0x00c0c084). clang has no well-defined thiscall for a free-function
// pointer, so the receiver is spelled as the first ordinary parameter here.
// The observed ECX convention is recorded in the metadata sidecar, not lost.
using CountFn = std::uint32_t(*)(OpaqueSimEntityCollection*);
using AtFn = OpaqueSimEntity* (*)(OpaqueSimEntityCollection*, std::int32_t);

}  // namespace

std::int32_t SimEntityCollection_FindIndexById_00c0c080(
    OpaqueSimEntityCollection* collection, std::int32_t id) {
  // 0x00c0c086 MOV EAX,[EDI] loads the vtable pointer first, so the slots are
  // addressed through the loaded pointer, not through the object.
  // 0x00c0c086 MOV EAX,[EDI] loads the vtable pointer; the two slots are then
  // read out of it with memcpy so the reconstruction always performs the
  // memory reads that 0x00c0c088 and 0x00c0c0a2 perform.
  std::uint32_t vtable;
  std::memcpy(&vtable, &collection->vtable, sizeof(vtable));
  const auto* const vtable_base = reinterpret_cast<const std::uint8_t*>(vtable);

  // 0x00c0c08e: slot +0xb0 is read with ECX already holding the receiver and
  // with no argument pushed, so it is a no-argument count getter.
  CountFn count_fn;
  std::memcpy(&count_fn, vtable_base + 0xb0, sizeof(count_fn));
  // 0x00c0c090 MOV EBX,EAX then 0x00c0c094 TEST EBX,EBX: the count is handled
  // as a 32-bit value and compared as signed by the later JC.
  const std::int32_t count = static_cast<std::int32_t>(count_fn(collection));

  // 0x00c0c096: TEST EBX,EBX / JBE. A zero or negative count skips the loop
  // and falls into the OR EAX,0xffffffff epilogue.
  AtFn at_fn;
  std::memcpy(&at_fn, vtable_base + 0xb4, sizeof(at_fn));

  for (std::int32_t i = 0; i < count; ++i) {
    OpaqueSimEntity* element = at_fn(collection, i);
    if (static_cast<std::int32_t>(element->mId) == id) {
      return i;
    }
  }

  return -1;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10
