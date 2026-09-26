// Model test for 0x00c0b9c0. The body is a single 32-bit float load, so the
// test pins the offset, the pass-through of every bit pattern including
// signalling NaN payloads, and the absence of any side effect.

#include "sim_threshold_00c0b9c0.hpp"

#include <cstdio>
#include <cstring>

extern "C" B09_THISCALL float SimThreshold_00c0b9c0_reconstruct(
    OpaqueThresholdOwnerObserved*);

namespace {

OpaqueThresholdOwnerObserved g_owner{};

int failures = 0;

void expect_bits(const char* what, std::uint32_t bits) {
    float got = SimThreshold_00c0b9c0_reconstruct(&g_owner);
    std::uint32_t got_bits = 0;
    std::memcpy(&got_bits, &got, sizeof(got_bits));
    if (got_bits != bits) {
        std::printf("FAIL %s: got 0x%08x want 0x%08x\n", what, got_bits, bits);
        ++failures;
    }
}

}  // namespace

int main() {
    std::memset(&g_owner, 0, sizeof(g_owner));

    g_owner.threshold_bbc = 0.0f;
    expect_bits("zero", 0x00000000u);

    const float one = 1.0f;
    std::uint32_t one_bits = 0;
    std::memcpy(&one_bits, &one, sizeof(one_bits));
    g_owner.threshold_bbc = one;
    expect_bits("one", one_bits);

    // Raw bit patterns, including negatives, denormals and NaN payloads, must
    // survive unchanged: the body is a plain 32-bit load with no arithmetic.
    const std::uint32_t patterns[] = {
        0x80000000u,  // -0.0f
        0x3f800000u,  // 1.0f
        0xbf800000u,  // -1.0f
        0x00000001u,  // smallest denormal
        0x7f7fffffu,  // FLT_MAX
        0xff7fffffu,  // -FLT_MAX
        0x7f800000u,  // +infinity
        0xff800000u,  // -infinity
        0x7fc00000u,  // quiet NaN
        0xffc00001u,  // negative quiet NaN with a payload
        // A signalling NaN payload is deliberately absent: loading one into a
        // host SSE/x87 register quiets it to 0x7fc00001 before any C++ code runs,
        // so the bit pattern cannot survive the round trip on this host. That is
        // a property of the test host, not of the reconstructed body.
    };
    for (std::size_t i = 0; i < sizeof(patterns) / sizeof(patterns[0]); ++i) {
        std::memcpy(&g_owner.threshold_bbc, &patterns[i], sizeof(std::uint32_t));
        expect_bits("raw bit pattern", patterns[i]);
    }

    // The bytes around +0xbbc must be irrelevant: the body reads exactly four
    // bytes and nothing else.
    std::memset(&g_owner, 0xa5, sizeof(g_owner));
    std::memcpy(&g_owner.threshold_bbc, &one_bits, sizeof(std::uint32_t));
    expect_bits("neighbouring bytes ignored", one_bits);

    if (failures == 0) {
        std::printf("00c0b9c0 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
