#pragma once

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// 0x00b3d630 - effective scale / extent factor of a Simulator object.
//
// Owner class: NOT established. The address has 10 references, all
// UNCONDITIONAL_CALL; there is not a single DATA reference, so it is not a
// vtable slot and no owning type can be named.
// ---------------------------------------------------------------------------

// The sub-object reached through receiver +0x40. Only two virtual slots were
// observed on it (+0x6c and +0x70) plus a cached 3-float point at +0x40.
// No vtable table address was located, so the concrete callees are unresolved.
struct OpaqueScaleSourceObserved {
    std::uint8_t opaque[0x44];
    float cached_point[3];  // +0x40, +0x44, +0x48
};

struct OpaqueScaleSourceVtableObserved {
    void* unknown_00;
    // ... slots up to +0x6c are unobserved ...
    void* slot_6c;  // +0x6c: thiscall(void* out24) - fills a 6-float block
    void* slot_70;  // +0x70: thiscall(float)     - returns a scalar in ST(0)
};

// The receiver. Only the fields this batch actually read or observed a write to
// are modelled. Field +0x4 and +0xc are two DIFFERENT small enums: +0x4 is the
// selector inside 0x00b3d630 and +0xb3d630's sibling 0x00b3d9c0, while +0xc is
// compared against 2 by callers (0x00b42630) and against 0 by the constructor
// (0x00b4780b). The rest of the object is NOT modelled.
struct OpaqueScaleOwnerObserved {
    std::uint32_t field_00;
    std::uint32_t selector_04;  // 0,1 -> virtual slot +0x70; 2 -> cached z; else 0
    std::uint32_t field_08;
    std::uint32_t field_0c;  // separate enum; compared with 2 and with 0
    float multiplier_10;     // initialised to 1.0f at 0x00b477b0
    float field_14;          // initialised to 1.0f at 0x00b477c6
    float cached_scale_18;   // initialised to 0.0f at 0x00b477f8
    std::uint32_t field_1c;
    std::uint8_t field_34_37[4];  // byte bitfield, low byte set to 1 at 0x00b47789
    std::uint32_t field_38;
    std::uint32_t field_3c;
    OpaqueScaleSourceObserved* source_40;
};

// The three-state selector observed at receiver +0x4. Values 0, 1 and 2 are the
// only ones the body distinguishes; every other value takes the same path as a
// zero scale. No enum name is claimed.
enum ScaleSelectorObserved : std::uint32_t {
    kScaleSelectorVirtual = 0,  // and 1: same path
    kScaleSelectorCachedZ = 2,
};

// The virtual port the receiver dispatches through for selector values 0 and 1.
// Declared, not implemented: the vtable table address and the concrete callee
// were not resolved.
extern "C" float opaque_ScaleSource_slot_0x70(OpaqueScaleSourceObserved* self);
