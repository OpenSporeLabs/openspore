// Standalone model test for the wave13-w1-dispatch-b04 reconstructions.
//
// Every assertion below is a fact that was read out of SporeApp.exe with a
// live ghidra_* tool call, not a fact about the reconstruction. The test
// pins the observable contracts: the reference-count transition and its
// delete-on-zero arm, the acquire/store/release ordering of the intrusive
// assign, the shape of the handle sweep including its skip and exclusion
// rules, the two field getters, and the six constants the bounding-box ctor
// writes.
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "00409c00_bounding_box_ctor.hpp"
#include "0043cad0_rigblock_handle_sweep.hpp"
#include "0043eed0_editor_part_blend_getter.hpp"
#include "004ad450_related_pointer_getter.hpp"
#include "004b09b0_intrusive_ref_assign.hpp"
#include "007b86e0_object_release.hpp"

namespace os = openspore::reconstruction::wave13_w1_dispatch_b04;

namespace {

int g_delete_calls = 0;
unsigned int g_delete_flag = 0;
std::vector<std::string> g_trace;
std::vector<std::string> g_sweep_trace;
std::uint8_t g_model_flag_4c = 0;
std::uint8_t g_model_flag_4d = 0;
int g_complementary_sweep_calls = 0;
std::uint32_t g_marker_tag = 0;
int g_marker_calls = 0;
void* g_applied_payload = nullptr;
std::vector<os::RefCountedPointee_004b09b0*> g_acquired;
std::vector<os::RefCountedPointee_004b09b0*> g_released;

}  // namespace

// The ports are declared `extern "C"` inside the reconstruction namespace, so
// their definitions reopen that namespace rather than the global one.
namespace openspore {
namespace reconstruction {
namespace wave13_w1_dispatch_b04 {

extern "C" void __attribute__((thiscall)) PORT_embedded_base_deleting_dtor_0041d780(
    EmbeddedPolymorphicBase_007b86e0* self, unsigned int delete_memory) {
    g_delete_calls++;
    g_delete_flag = delete_memory;
    // 0x0041d78a stores the base vtable over *self before the optional free.
    self->vptr = nullptr;
}

extern "C" void __attribute__((thiscall)) PORT_pointee_acquire_004b09b0(
    RefCountedPointee_004b09b0* self) {
    g_acquired.push_back(self);
    g_trace.push_back("acquire");
}

extern "C" void __attribute__((thiscall)) PORT_pointee_release_004b09b0(
    RefCountedPointee_004b09b0* self) {
    g_released.push_back(self);
    g_trace.push_back("release");
}

extern "C" std::uint8_t __attribute__((thiscall)) PORT_sub_object_flag_4c_004adb80(
    const void* sub_object) {
    assert(sub_object != nullptr);
    return g_model_flag_4c;
}

extern "C" std::uint8_t __attribute__((thiscall)) PORT_sub_object_flag_4d_004adbc0(
    const void* sub_object) {
    assert(sub_object != nullptr);
    return g_model_flag_4d;
}

extern "C" void __attribute__((thiscall)) PORT_sweep_unselected_0043ce40(
    RigblockHandleSweep_0043cad0* self) {
    (void)self;
    g_complementary_sweep_calls++;
    g_sweep_trace.push_back("sweep_state_1");
}

extern "C" void __attribute__((thiscall)) PORT_handle_set_state_0044ae00(void* handle, int state,
                                              bool toggle) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "h%u:%d:%d",
                  static_cast<unsigned>(reinterpret_cast<std::uintptr_t>(handle)),
                  state, toggle ? 1 : 0);
    g_sweep_trace.push_back(buf);
}

extern "C" void __attribute__((thiscall)) PORT_marker_004a88d0(std::uint32_t tag) {
    g_marker_calls++;
    g_marker_tag = tag;
}

extern "C" void __attribute__((thiscall)) PORT_apply_to_related_004b9440(void* related, void* payload) {
    g_applied_payload = payload;
    assert(related != nullptr);
}

}  // namespace wave13_w1_dispatch_b04
}  // namespace reconstruction
}  // namespace openspore

namespace {

// ---- helpers ---------------------------------------------------------------

// A fake handle with the flag bytes at the same absolute offsets the binary
// reads, so the fixture cannot alias one handle's flag with another's.
struct FakeHandle {
    std::uint8_t bytes[0x1D8];
};

std::uint8_t& AxisPinOf(FakeHandle& h) { return h.bytes[0x92]; }
std::uint8_t& BallPinOf(FakeHandle& h) { return h.bytes[0x5D]; }
std::uint8_t& MorphPinOf(FakeHandle& h) { return h.bytes[0x1D4]; }

void ClearFake(FakeHandle* h, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t b = 0; b < sizeof(h[i].bytes); ++b) {
            h[i].bytes[b] = 0;
        }
    }
}

void ResetSweepTrace() {
    g_sweep_trace.clear();
    g_complementary_sweep_calls = 0;
    g_marker_calls = 0;
    g_marker_tag = 0;
    g_model_flag_4c = 0;
    g_model_flag_4d = 0;
}

void Test007b86e0() {
    // 0x00c6a960, the slot +0x00 partner, is ++ref_count at the same offset.
    os::RefCountedObject_007b86e0 obj{};
    obj.ref_count = 1;
    void* const base_before = obj.embedded_base.vptr;

    // 0x007b86e6 ADD EAX,-1 / 0x007b86ec JNZ: a count above 1 returns the
    // decremented value and never touches the embedded base. A count of 2
    // therefore returns 1 and leaves the field at 1.
    obj.ref_count = 2;
    assert(os::FUN_007b86e0_release(&obj) == 1);
    assert(obj.ref_count == 1);
    assert(g_delete_calls == 0);

    // A count of 1 takes the zero arm: the field is restored to 1 at
    // 0x007b86ee before the destructor at 0x007b86fb runs, and the result is 0.
    assert(os::FUN_007b86e0_release(&obj) == 0);
    assert(obj.ref_count == 1);
    assert(g_delete_calls == 1);
    // 0x007b86f9: the constant pushed as the deleting-destructor flag.
    assert(g_delete_flag == 1u);
    // 0x0041d780 overwrites *self with the base vtable.
    assert(obj.embedded_base.vptr == nullptr);
    assert(base_before == nullptr);

    // The count is never left below 1, so repeated calls each take the zero
    // arm and each re-enter the destructor exactly once.
    g_delete_calls = 0;
    os::EmbeddedPolymorphicBase_007b86e0 base2{};
    obj.embedded_base = base2;
    assert(os::FUN_007b86e0_release(&obj) == 0);
    assert(obj.ref_count == 1);
    assert(g_delete_calls == 1);
    assert(os::FUN_007b86e0_release(&obj) == 0);
    assert(obj.ref_count == 1);
    assert(g_delete_calls == 2);
}

void Test004b09b0() {
    os::RefCountedPointee_004b09b0 a{};
    os::RefCountedPointee_004b09b0 b{};
    os::IntrusiveRefHolder_004b09b0 holder{};

    g_acquired.clear();
    g_released.clear();
    g_trace.clear();

    // 0x004b09bf / JZ: assigning the value already held touches nothing and
    // still returns the holder.
    holder.held = &a;
    os::IntrusiveRefHolder_004b09b0* const same =
        os::FUN_004b09b0_assign(&holder, &a);
    assert(same == &holder);
    assert(g_trace.empty());

    // Fresh assign from empty: acquire, store, no release.
    g_trace.clear();
    holder.held = nullptr;
    assert(os::FUN_004b09b0_assign(&holder, &a) == &holder);
    assert(holder.held == &a);
    assert((g_trace == std::vector<std::string>{"acquire"}));

    // Replace: acquire BEFORE the store, release AFTER it.
    g_trace.clear();
    assert(os::FUN_004b09b0_assign(&holder, &b) == &holder);
    assert(holder.held == &b);
    assert((g_trace == std::vector<std::string>{"acquire", "release"}));
    assert(g_acquired.back() == &b);
    assert(g_released.back() == &a);

    // 0x004b09cb: a null incoming value is not dereferenced, and the outgoing
    // one still is.
    g_trace.clear();
    assert(os::FUN_004b09b0_assign(&holder, nullptr) == &holder);
    assert(holder.held == nullptr);
    assert((g_trace == std::vector<std::string>{"release"}));

    // Null over null is the early exit.
    g_trace.clear();
    assert(os::FUN_004b09b0_assign(&holder, nullptr) == &holder);
    assert(g_trace.empty());
}

void Test0043cad0() {
    static FakeHandle handles[3];
    static FakeHandle ball;
    static FakeHandle morphs[4];
    static std::int32_t morph_storage[4] = {0, 0, 0, 0};

    ClearFake(handles, 3);
    ClearFake(&ball, 1);
    ClearFake(morphs, 4);

    static int model_object = 0;
    os::RigblockHandleSweep_0043cad0 sweep{};
    sweep.model = &model_object;
    sweep.axis_handles[0] = &handles[0];
    sweep.axis_handles[1] = &handles[1];
    sweep.axis_handles[2] = &handles[2];
    sweep.rotation_ball_handle = &ball;
    sweep.exclusion_index = 1;
    morph_storage[0] = reinterpret_cast<std::int32_t>(&morphs[0]);
    morph_storage[1] = reinterpret_cast<std::int32_t>(&morphs[1]);
    morph_storage[2] = reinterpret_cast<std::int32_t>(&morphs[2]);
    morph_storage[3] = reinterpret_cast<std::int32_t>(&morphs[3]);
    sweep.morph_begin = morph_storage;
    sweep.morph_end = morph_storage + 4;
    sweep.attributes_lo = 0;
    sweep.attributes_hi = 0;

    // Baseline: the sub-object +0x4C flag is clear, so the complementary
    // sweep runs, all four named slots and all four morphs are visited with
    // state 3, and the marker fires once.
    ResetSweepTrace();
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_complementary_sweep_calls == 1);
    assert(g_sweep_trace.size() == 9);  // 1 sweep + 4 named + 4 morph
    assert(g_sweep_trace[0] == "sweep_state_1");
    for (std::size_t i = 1; i < g_sweep_trace.size(); ++i) {
        assert(g_sweep_trace[i].find(":3:1") != std::string::npos);
    }
    assert(g_marker_calls == 1);
    // 0x0043cde5 PUSH 0xD0A55625.
    assert(g_marker_tag == 0xD0A55625u);

    // Bit 11 set with the +0x4D flag clear excludes index +0x1B0 == 1, so the
    // morph count drops from 4 to 3.
    ResetSweepTrace();
    sweep.attributes_lo = (1u << 11);
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 8);
    sweep.attributes_lo = 0;

    // Bit 11 set but the +0x4D override set: the exclusion is NOT installed.
    ResetSweepTrace();
    sweep.attributes_lo = (1u << 11);
    g_model_flag_4d = 1;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 9);
    g_model_flag_4d = 0;
    sweep.attributes_lo = 0;

    // A pinned rotation-ball handle is skipped at +0x5D.
    ResetSweepTrace();
    BallPinOf(ball) = 1;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 8);  // 1 sweep + 3 axis + 4 morph
    BallPinOf(ball) = 0;

    // A pinned morph handle is skipped at +0x1D4.
    ResetSweepTrace();
    MorphPinOf(morphs[2]) = 1;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 8);  // 1 sweep + 4 named + 3 morph
    MorphPinOf(morphs[2]) = 0;

    // A pinned axis handle is skipped, but the override visits it anyway.
    ResetSweepTrace();
    AxisPinOf(handles[1]) = 1;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 8);
    AxisPinOf(handles[1]) = 0;

    ResetSweepTrace();
    AxisPinOf(handles[1]) = 1;
    g_model_flag_4c = 1;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_complementary_sweep_calls == 0);  // 0x0043cb0a guard
    // No complementary sweep this time, so 4 named + 4 morphs and no more.
    assert(g_sweep_trace.size() == 8);
    AxisPinOf(handles[1]) = 0;
    g_model_flag_4c = 0;

    // Bit 25 (0x19) suppresses the four named slots only.
    ResetSweepTrace();
    sweep.attributes_lo = (1u << 25);
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 5);  // 1 sweep + 4 morphs

    // Bit 24 (0x18) suppresses the morphs only.
    ResetSweepTrace();
    sweep.attributes_lo = (1u << 24);
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 5);  // 1 sweep + 4 named

    // Both bits: nothing is dispatched and the marker does not fire.
    ResetSweepTrace();
    sweep.attributes_lo = (1u << 24) | (1u << 25);
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 1);
    assert(g_marker_calls == 0);
    sweep.attributes_lo = 0;

    // A null model gates the two flag reads off, which leaves all_handles
    // clear and so still runs the complementary sweep.
    ResetSweepTrace();
    sweep.model = nullptr;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_complementary_sweep_calls == 1);
    sweep.model = &model_object;

    // An empty morph range makes the count zero and the loop body never runs.
    ResetSweepTrace();
    sweep.morph_end = morph_storage;
    os::FUN_0043cad0_propagate_handle_state(&sweep);
    assert(g_sweep_trace.size() == 5);
    sweep.morph_end = morph_storage + 4;
}

void Test0043eed0() {
    os::EditorPart_0043eed0 part{};
    part.blend_value = 0.375f;
    assert(os::FUN_0043eed0_get_blend_value(&part) == 0.375f);
    part.blend_value = -2.5f;
    assert(os::FUN_0043eed0_get_blend_value(&part) == -2.5f);
}

void Test004ad450() {
    int related = 7;
    os::RelatedPointerOwner_004ad450 owner{};
    owner.related = &related;
    assert(os::FUN_004ad450_get_related(&owner) == &related);

    // No null check in the body, so null propagates.
    owner.related = nullptr;
    assert(os::FUN_004ad450_get_related(&owner) == nullptr);

    // The callsites pass the result straight on as the next receiver.
    owner.related = &related;
    int payload = 3;
    os::PORT_apply_to_related_004b9440(
        os::FUN_004ad450_get_related(&owner), &payload);
    assert(g_applied_payload == &payload);
}

void Test00409c00() {
    os::BoundingBox_00409c00 box{};
    std::memset(&box, 0xA5, sizeof(box));
    os::FUN_00409c00_bounding_box_ctor(&box);

    // 0x013eb258 read live = 0x7f7fffff. Built by bit pattern, because an
    // int-to-float conversion of 0x7f7fffff is a different value.
    const float kMax = os::kFloatMax_013eb258;
    assert(os::kFloatMax_013eb258 > 3.0e38f);
    assert(box.lower.x == kMax);
    assert(box.lower.y == kMax);
    assert(box.lower.z == kMax);
    assert(box.upper.x == -kMax);
    assert(box.upper.y == -kMax);
    assert(box.upper.z == -kMax);

    // The second group starts at +0x0C, the layout that fixes the type as two
    // consecutive 12-byte vectors.
    assert(reinterpret_cast<std::uintptr_t>(&box.upper) -
               reinterpret_cast<std::uintptr_t>(&box) ==
           0x0Cu);
    assert(sizeof(os::BoundingBox_00409c00) == 24u);

    // Every store is unconditional, so the ctor is idempotent and needs no
    // initialised storage.
    os::FUN_00409c00_bounding_box_ctor(&box);
    assert(box.lower.x == kMax);
    assert(box.upper.z == -kMax);
}

}  // namespace

int main() {
    Test007b86e0();
    Test004b09b0();
    Test0043cad0();
    Test0043eed0();
    Test004ad450();
    Test00409c00();
    std::printf("wave13-w1-dispatch-b04 model test: all assertions passed\n");
    return 0;
}
