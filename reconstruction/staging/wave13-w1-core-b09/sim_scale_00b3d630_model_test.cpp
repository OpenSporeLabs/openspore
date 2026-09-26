// Model test for 0x00b3d630. Static check of the observed branch polarity, the
// selector dispatch and the multiplier, using a stand-in for the virtual port.

#include "sim_scale_00b3d630.hpp"

#include "b09_abi.hpp"

#include <cstdio>

namespace {

float g_virtual_result = 0.0f;
int g_virtual_calls = 0;

OpaqueScaleOwnerObserved g_owner{};
OpaqueScaleSourceObserved g_source{};

}  // namespace

// Test-only stand-in for the unresolved vtable slot +0x70.
extern "C" float opaque_ScaleSource_slot_0x70(OpaqueScaleSourceObserved*) {
    ++g_virtual_calls;
    return g_virtual_result;
}

extern "C" B09_THISCALL float SimScale_00b3d630_reconstruct(
    OpaqueScaleOwnerObserved*);

namespace {

int failures = 0;

void expect_near(const char* what, float got, float want) {
    const float diff = got > want ? got - want : want - got;
    if (!(diff <= 1e-6f)) {
        std::printf("FAIL %s: got %f want %f\n", what, static_cast<double>(got),
                    static_cast<double>(want));
        ++failures;
    }
}

}  // namespace

int main() {
    g_owner.multiplier_10 = 1.0f;
    g_owner.cached_scale_18 = 0.0f;
    g_owner.source_40 = &g_source;
    g_source.cached_point[0] = 11.0f;
    g_source.cached_point[1] = 22.0f;
    g_source.cached_point[2] = 33.0f;

    // field_18 > 0 short-circuits everything, including the virtual call.
    g_virtual_result = 5.0f;
    g_owner.cached_scale_18 = 7.5f;
    expect_near("positive override wins", SimScale_00b3d630_reconstruct(&g_owner), 7.5f);
    if (g_virtual_calls != 0) {
        std::printf("FAIL override path dispatched the virtual port\n");
        ++failures;
    }

    // field_18 == 0 and field_18 < 0 both take the slow path (JBE polarity).
    g_owner.cached_scale_18 = 0.0f;
    for (unsigned selector = 0; selector <= 1u; ++selector) {
        g_virtual_result = 4.0f;
        g_owner.selector_04 = selector;
        expect_near("selector 0/1 uses slot +0x70",
                    SimScale_00b3d630_reconstruct(&g_owner), 4.0f);
    }

    g_owner.selector_04 = 2u;
    g_virtual_calls = 0;
    expect_near("selector 2 uses cached z", SimScale_00b3d630_reconstruct(&g_owner), 33.0f);
    if (g_virtual_calls != 0) {
        std::printf("FAIL selector 2 dispatched the virtual port\n");
        ++failures;
    }

    // Any other selector keeps the spilled 0.0f.
    const unsigned long others[] = {3ul, 4ul, 100ul, 0xfffffffful};
    for (unsigned long v : others) {
        g_owner.selector_04 = static_cast<std::uint32_t>(v);
        expect_near("unhandled selector yields zero", SimScale_00b3d630_reconstruct(&g_owner),
                    0.0f);
    }

    // The multiplier at +0x10 is applied on the slow path only.
    g_owner.selector_04 = 2u;
    g_owner.multiplier_10 = 0.5f;
    expect_near("multiplier applied", SimScale_00b3d630_reconstruct(&g_owner), 16.5f);
    g_owner.cached_scale_18 = 3.0f;
    expect_near("override bypasses multiplier", SimScale_00b3d630_reconstruct(&g_owner), 3.0f);

    if (failures == 0) {
        std::printf("00b3d630 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
