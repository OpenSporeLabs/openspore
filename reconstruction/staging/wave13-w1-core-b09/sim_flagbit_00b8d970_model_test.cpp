// Model test for 0x00b8d970. Pins the bit index (8, not 0 and not the low byte),
// the one-bit mask, and the full-dword 0-or-1 return width.

#include "sim_flagbit_00b8d970.hpp"

#include <cstdio>

extern "C" B09_THISCALL std::uint32_t SimFlagBit_00b8d970_reconstruct(
    OpaqueFlagWordOwnerObserved*);

namespace {

OpaqueFlagWordOwnerObserved g_owner{};

int failures = 0;

void expect(const char* what, std::uint32_t bits, std::uint32_t want) {
    g_owner.flags_2c = bits;
    const std::uint32_t got = SimFlagBit_00b8d970_reconstruct(&g_owner);
    if (got != want) {
        std::printf("FAIL %s: flags 0x%08x gave %u want %u\n", what, bits, got, want);
        ++failures;
    }
}

}  // namespace

int main() {
    expect("all clear", 0x00000000u, 0u);
    expect("only bit 8 set", 0x00000100u, 1u);
    expect("only bit 0 set", 0x00000001u, 0u);
    expect("only bit 7 set", 0x00000080u, 0u);
    expect("only bit 9 set", 0x00000200u, 0u);
    expect("bits 0 and 8", 0x00000101u, 1u);
    expect("bits 0, 8 and 11", 0x00000901u, 1u);
    expect("bit 8 and bit 0x800", 0x00000900u, 1u);
    expect("only bit 0x800", 0x00000800u, 0u);
    expect("all bits", 0xffffffffu, 1u);
    expect("bit 31 only", 0x80000000u, 0u);

    // The return must be a full dword of 0 or 1, never a shifted remnant.
    g_owner.flags_2c = 0xffffff00u;
    if (SimFlagBit_00b8d970_reconstruct(&g_owner) != 1u) {
        std::printf("FAIL upper-byte-only pattern did not give 1\n");
        ++failures;
    }
    g_owner.flags_2c = 0x0000ff00u;
    if (SimFlagBit_00b8d970_reconstruct(&g_owner) != 1u) {
        std::printf("FAIL narrow pattern did not give 1\n");
        ++failures;
    }

    // The neighbouring state field at +0x28 must not affect the result.
    g_owner.state_28 = 0xffffffffu;
    g_owner.flags_2c = 0u;
    if (SimFlagBit_00b8d970_reconstruct(&g_owner) != 0u) {
        std::printf("FAIL state field leaked into the result\n");
        ++failures;
    }

    if (failures == 0) {
        std::printf("00b8d970 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
