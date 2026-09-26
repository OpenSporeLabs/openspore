#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declarations. No field beyond the offsets proven in
// reconstruction/metadata/wave13-w1-dispatch-b00/0045ae10.json is asserted.
struct Opaque45ae10Registry;   // the singleton at 0x015d0c14
struct Opaque45ae10Transform;  // 0x18..0x14 bytes written by 0x00434040

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// Opaque ports. Declared, never given a fabricated body.
extern "C" Opaque45ae10Transform* __thiscall port_00434040_default_transform(
    Opaque45ae10Transform* out,
    std::uint32_t zero);

extern "C" void* __thiscall port_0045ac20_spawn(
    Opaque45ae10Registry* registry,
    std::uint32_t key,
    std::uint32_t mode,
    Opaque45ae10Transform* transform,
    std::uint32_t fourth_arg_uninitialised);

// 0x0045ae10
//
//   void __thiscall FUN_0045ae10(Registry* registry, uint32 key, uint32 mode);
//
// Observed body, 17 instructions, 42 bytes, 0x0045ae10..0x0045ae39.
// Receiver is ECX; the two dword arguments arrive on the stack and are popped
// by the callee (RET 0x8 at 0x0045ae39).
extern "C" void __thiscall FUN_0045ae10_reconstruct(
    Opaque45ae10Registry* registry,
    std::uint32_t key,
    std::uint32_t mode);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
