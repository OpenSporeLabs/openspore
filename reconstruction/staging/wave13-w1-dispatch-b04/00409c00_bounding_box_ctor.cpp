#include "00409c00_bounding_box_ctor.hpp"

#include <cstdint>
#include <cstring>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

// Values read live out of the image, reproduced so the reconstruction needs no
// link-time definition of them. 0x013eb258 holds the four bytes 7f 7f ff ff,
// i.e. the float whose bit pattern is 0x7f7fffff, so the constant is built by
// bit pattern rather than by an int-to-float conversion, which would change
// the value.
namespace {

float FloatFromBits(std::uint32_t bits) {
    float out = 0.0f;
    __builtin_memcpy(&out, &bits, sizeof(out));
    return out;
}

}  // namespace

extern "C" const float kFloatMax_013eb258 = FloatFromBits(0x7f7fffffu);

extern "C" const unsigned char kSignMask_013eb8b0[16] = {
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80,
};

namespace {

// 0x00409c62..0x00409c99: MOVSS from 0x013eb258 then XORPS with the mask at
// 0x013eb8b0. The XOR is over 16 bytes but only the low dword survives the
// MOVSS, so the effect is exactly a sign-bit flip of the loaded float.
float NegateSign(float value) {
    unsigned char raw[4];
    __builtin_memcpy(raw, &value, sizeof(raw));
    raw[3] = static_cast<unsigned char>(raw[3] ^ 0x80u);
    float out = 0.0f;
    __builtin_memcpy(&out, raw, sizeof(out));
    return out;
}

}  // namespace

extern "C" void __attribute__((thiscall)) FUN_00409c00_bounding_box_ctor(
    BoundingBox_00409c00* self) {
    // 0x00409c09..0x00409c62: the first group is the plain constant, stored
    // through three locals and then written out at 0x00409c54, 0x00409c59 and
    // 0x00409c5f. Three separate stores, no vector-width store.
    const float kMax = kFloatMax_013eb258;
    self->lower.x = kMax;
    self->lower.y = kMax;
    self->lower.z = kMax;

    // 0x00409c62..0x00409cd0: the second group is the sign-flipped constant,
    // stored at 0x00409cc5, 0x00409cca and 0x00409cd0 with the destination
    // biased by 0x0C.
    const float kNegMax = NegateSign(kMax);
    self->upper.x = kNegMax;
    self->upper.y = kNegMax;
    self->upper.z = kNegMax;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
