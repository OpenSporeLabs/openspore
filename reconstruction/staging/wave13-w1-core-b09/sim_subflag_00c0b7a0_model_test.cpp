// Model test for 0x00c0b7a0. Pins the two-level offset chain, the != 0
// (not "is one", not "non-negative") truth condition, and the full-dword
// 0-or-1 return width that SBB/NEG produces.

#include "sim_subflag_00c0b7a0.hpp"

#include <cstdio>

extern "C" B09_THISCALL std::uint32_t SimSubFlag_00c0b7a0_reconstruct(
    OpaqueSubFlagOwnerObserved*);

namespace {

OpaqueSubObjectB20Observed g_sub{};
OpaqueSubFlagOwnerObserved g_owner{};

int failures = 0;

void expect(const char* what, std::uint32_t want) {
    const std::uint32_t got = SimSubFlag_00c0b7a0_reconstruct(&g_owner);
    if (got != want) {
        std::printf("FAIL %s: got %u want %u\n", what, got, want);
        ++failures;
    }
}

}  // namespace

int main() {
    g_owner.sub_b20 = &g_sub;

    g_sub.field_60c = 0u;
    expect("zero is false", 0u);

    // Any non-zero value is true, including negatives, which rules out a
    // signed "greater than zero" reading of the CMP.
    const std::uint32_t truthy[] = {1u, 2u, 3u, 0x7fffffffu, 0x80000000u, 0xffffffffu};
    for (std::size_t i = 0; i < sizeof(truthy) / sizeof(truthy[0]); ++i) {
        g_sub.field_60c = truthy[i];
        expect("non-zero is true", 1u);
    }

    // The sibling accessor 0x00c0b780 tests +0x608, four bytes lower, so the two
    // fields must be independent here.
    g_sub.sibling_field_608 = 1u;
    g_sub.field_60c = 0u;
    expect("sibling field at +0x608 does not leak in", 0u);

    // The return must be a full dword of exactly 0 or 1, never an arbitrary
    // true value and never a leftover pointer, because the original SBB/NEG pair
    // overwrites all of EAX.
    g_sub.field_60c = 0x12345678u;
    expect("true case is a full dword 1", 1u);
    g_sub.field_60c = 0u;
    expect("false case is a full dword 0", 0u);

    if (failures == 0) {
        std::printf("00c0b7a0 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
