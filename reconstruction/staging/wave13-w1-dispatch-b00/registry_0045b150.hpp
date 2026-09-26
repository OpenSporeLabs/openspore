#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declarations. The offsets below are the ones the
// disassembly of 0x0045b150 and its two hash-map ports actually touch.
struct Opaque45b150Registry;  // the object reached through 0x00401050
struct Opaque45b150Node;     // hash-map chain node
struct Opaque45b150Payload;  // the refcounted object stored in node +0x4

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// 0x0045b150's own pair, eight bytes, {node, bucket_slot}.
struct Lookup45b150Pair {
  Opaque45b150Node* node;
  void** bucket_slot;
};

// Opaque ports, declared only.
extern "C" Lookup45b150Pair __thiscall port_00421950_find(
    Opaque45b150Registry* registry,
    Lookup45b150Pair* out,
    const std::uint32_t* key);

extern "C" Lookup45b150Pair __thiscall port_0045b3e0_erase(
    Opaque45b150Registry* registry,
    Lookup45b150Pair* out,
    Opaque45b150Node* node,
    void** bucket_slot);

extern "C" void __thiscall port_0045b150_payload_pre_erase(
    Opaque45b150Payload* payload,
    std::uint32_t flag);

// 0x0045b150
//
//   void __thiscall FUN_0045b150_reconstruct(Opaque45b150Registry* self,
//                                             std::uint32_t key);
//
// Observed body, 65 instructions, 179 bytes, 0x0045b150..0x0045b200.
// Receiver is ECX; one dword stack argument, popped by the callee
// (RET 0x4 at 0x0045b200). Void.
extern "C" void __thiscall FUN_0045b150_reconstruct(
    Opaque45b150Registry* self,
    std::uint32_t key);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
