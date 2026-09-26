#pragma once

#include <cstdint>

#include "b09_opaque_ports.hpp"

// ---------------------------------------------------------------------------
// 0x00b25c30 - first-match linear scan over a registry element array.
//
// Owner class: NOT established. 26 references, all UNCONDITIONAL_CALL, no DATA
// reference, so not a vtable slot.
// ---------------------------------------------------------------------------

// The registry element. 0x00b25c30 reads the vtable of the interface embedded at
// byte offset +0x120 and calls slot +0x58 on it with ECX = element + 0x120.
// Callers then use the returned element as a receiver for further calls
// (0x00bd81d0, 0x00bd9b40, 0x00bd7df0) and read its +0x34, so the element is a
// large polymorphic object. No vtable table address was located.
//
// The vtable is modelled as a raw slot array rather than a C++ virtual class so
// that the reconstruction performs the same two loads the original performs:
//   MOV EDX,[EAX + 0x120]        ; the vtable pointer of the embedded interface
//   MOV EAX,[EDX + 0x58]         ; the slot itself
//   CALL EAX                     ; with ECX = EAX + 0x120
struct OpaqueSlot58TableObserved {
    void* slots[(0x58 / sizeof(void*)) + 1];  // slot +0x58 is the last modelled
    // Slots below +0x58 are unobserved. Entries beyond +0x58 were not read.
};

struct OpaqueRegistryElementIfc120 {
    std::uint8_t opaque[0x120];
    const OpaqueSlot58TableObserved* vtable;  // +0x120
};

struct OpaqueRegistryElement {
    std::uint8_t opaque[0x120];
    OpaqueRegistryElementIfc120 iface_120;
};

// The receiver. 0x00b25c30 forwards ECX unchanged to its single callee, so this
// is a __thiscall with no stack arguments of its own.
struct OpaqueRegistryOwnerObserved {
    std::uint8_t opaque;
};

// The single callee, 0x00b21340: __thiscall with ECX forwarded from the caller,
// RET 0x14 (five stack dwords), returning a pointer whose +4 and +8 are a
// begin/end pair of 4-byte-stride elements. Internally it uses a map at
// this+0x98 and a singly linked list at this+0x78. Neither container's element
// type was established and no part of its body is reconstructed here: it is
// declared as an opaque port.
extern "C" OpaqueRegistryContainerObserved* opaque_RegistryLookup5Args_00b21340(
    OpaqueRegistryOwnerObserved* self, const OpaqueRegistryLookup5Args& args);
