// Reconstruction of 0x00409c00 - the default constructor of a 24-byte
// two-Vector3 aggregate, initialised to the inverted bounding volume.
//
// Complete body, 49 instructions, 0x00409c00..0x00409cd6, read live
// (558bec 83ec34 894dcc ... 8be55dc3, then INT3 pad).
//
// Two constants, both read live and neither computed:
//
//   0x013eb258  = 7f 7f ff ff  -> float +FLT_MAX (0x7f7fffff)
//   0x013eb8b0  = 00 00 00 80 x4 -> a 16-byte all-lanes sign mask
//
// The body stores +FLT_MAX into the three floats at receiver+0x00,
// +0x04 and +0x08, then stores the XOR of +FLT_MAX with the sign mask -
// that is, -FLT_MAX - into receiver+0x0C, +0x10 and +0x14. The XORPS
// is applied to a 16-byte mask but only the low dword of each result is
// stored by the following MOVSS, so each negation is a single sign-bit flip
// and the upper lanes are discarded.
//
// Nothing is read from the old contents of the receiver: every one of the six
// stores is unconditional and none of them depends on a prior load of the
// destination, so the constructor is idempotent and does not require the
// storage to be initialised.
//
// The 24-byte size and the +0x0C offset of the second group match
// `struct BoundingBox { Vector3 lower; Vector3 upper; }` from the SDK
// (Spore/MathUtils.h), where Vector3 is 12 bytes and `upper` therefore sits at
// 0x0C - an offset that is only natural for two consecutive 12-byte vectors.
// The SDK's own inline default ctor writes -1/+1, which contradicts the
// constants observed here; the SDK body is a placeholder and the binary is the
// authority. The observed values, min above max, are the identity element
// for a union/intersection-style accumulator, i.e. the "empty box" state.
#pragma once

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

struct Vector3_00409c00 {
    float x;  // +0x00
    float y;  // +0x04
    float z;  // +0x08
};

// 24 bytes: two consecutive 12-byte vectors, the second unaligned to 4.
struct BoundingBox_00409c00 {
    Vector3_00409c00 lower;  // +0x00
    Vector3_00409c00 upper;  // +0x0C
};

// The single global the body reads is +FLT_MAX at 0x013eb258; the negation
// comes from XORing with the all-lanes sign mask at 0x013eb8b0, which is
// reproduced here as the sign flip the instructions perform.
extern "C" const float kFloatMax_013eb258;
extern "C" const unsigned char kSignMask_013eb8b0[16];

extern "C" void __attribute__((thiscall))
FUN_00409c00_bounding_box_ctor(BoundingBox_00409c00* self);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
