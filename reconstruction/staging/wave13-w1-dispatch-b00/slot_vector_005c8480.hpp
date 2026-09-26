#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declaration. The receiver is a {first, last, capacity}
// triple of 4-byte slots that hold pointers to a refcounted payload; only
// those three dwords are evidenced.
struct Opaque5c8480SlotVector;

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// Opaque ports, declared only.
extern "C" void* __cdecl port_005c1dc0_shift_slots(void* lower_bound,
                                                  void* source_slot,
                                                  void* destination_slot);
extern "C" void* __cdecl port_00f47380_free(void* block);
extern "C" void* __cdecl port_00f473a0_alloc(std::size_t bytes,
                                             const char* tag,
                                             std::uint32_t group,
                                             std::uint32_t type,
                                             const char* file,
                                             std::uint32_t line);

// Observed at 0x005c855f and 0x005c858f as CALL 0x011e0744, which the briefing
// records as a thunk to the runtime memcpy. The return value is used as the
// running cursor in both cases, which is why the port returns void*.
extern "C" void* __cdecl memcpy(void* destination, const void* source,
                                std::size_t count);

// 0x005c8480
//
//   void __thiscall FUN_005c8480_reconstruct(Opaque5c8480SlotVector* self,
//                                             void* position,
//                                             void** value_in_out);
//
// Observed body, 133 instructions, 335 bytes, 0x005c8480..0x005c85cc.
// Receiver is ECX; two dword stack arguments, popped by the callee
// (RET 0x8 at 0x005c85cc). Void, and note that the second argument is
// overwritten on the way out on the in-capacity path.
extern "C" void __thiscall FUN_005c8480_reconstruct(
    Opaque5c8480SlotVector* self,
    void* position,
    void** value_in_out);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
