#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declarations for the 0x005dc310 port.
struct Opaque5dc310Layout;   // 0x18 bytes; +0x14 holds the objects pointer
struct Opaque5dc310Window;   // UTFWin::IWindow candidate; concrete type open

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// Opaque ports, declared only.
extern "C" Opaque5dc310Window* __thiscall port_008105b0_find_in_layout(
    Opaque5dc310Layout* layout,
    std::uint32_t control_id,
    std::uint32_t recursive);

// 0x005dc310
//
//   Opaque5dc310Window* __thiscall FUN_005dc310_reconstruct(void* editor_ui,
//                                                           uint32_t control_id);
//
// Observed body, 17 instructions, 39 bytes, 0x005dc310..0x005dc336.
// Receiver is ECX; one dword stack argument, popped by the callee
// (RET 0x4 at 0x005dc334). The result is the last callee's EAX, which the
// decompiler dropped.
extern "C" Opaque5dc310Window* __thiscall FUN_005dc310_reconstruct(
    void* editor_ui,
    std::uint32_t control_id);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
