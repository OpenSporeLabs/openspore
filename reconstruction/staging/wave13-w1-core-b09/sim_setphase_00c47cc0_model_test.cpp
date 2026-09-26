// Model test for 0x00c47cc0. Checks the idempotence guard, the two buffer
// resets, and that the value-3 tail runs exactly once with the observed
// immediates, the observed owner slot and the observed argument order.

#include "sim_setphase_00c47cc0.hpp"

#include "b09_opaque_ports.hpp"

#include <cstdio>
#include <cstring>

namespace {

std::uint16_t g_buffer_a[8];
std::uint16_t g_buffer_b[8];

OpaquePhaseOwnerObserved g_owner{};
OpaquePhaseOwnerObserved* g_expected_owner = nullptr;

int g_tail_calls = 0;
std::uint32_t g_tail_arg0 = 0;
std::uint32_t g_tail_arg2 = 0;
bool g_tail_saw_owner = false;
bool g_tail_saw_pair5 = false;
bool g_tail_saw_mask_zero = false;

int g_dtor_calls = 0;
std::uint32_t g_dtor_final_vtable = 0;

int failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL %s\n", what);
        ++failures;
    }
}

struct ProbeAppSystem : OpaqueAppSystemIfcObserved {
    void slot_14(std::uint32_t a, OpaqueBakeQueueTemporary& t, std::uint32_t c) override {
        ++g_tail_calls;
        g_tail_arg0 = a;
        g_tail_arg2 = c;
        g_tail_saw_owner =
            t.pairs[0].first == reinterpret_cast<std::uint32_t>(g_expected_owner);
        g_tail_saw_pair5 = t.pairs[5].first == 0x038cf2fdu;
        g_tail_saw_mask_zero = t.pairs[6].first == 0u;
    }
};

ProbeAppSystem g_probe;

}  // namespace

// Test doubles for the two unresolved ports.
extern "C" void* opaque_AppSystem_Get_0067dcc0(void) { return &g_probe; }

extern "C" void opaque_TemporaryDtor_00421cf0(OpaqueBakeQueueTemporary* self) {
    ++g_dtor_calls;
    g_dtor_final_vtable = self->vtable_a;
}

extern "C" B09_THISCALL void SimSetPhase_00c47cc0_reconstruct(
    OpaquePhaseOwnerObserved*, std::int32_t);

int main() {
    std::memset(&g_owner, 0, sizeof(g_owner));
    g_owner.phase_84 = 0xffffffffu;
    g_owner.buffer_a_head_14c = g_owner.buffer_a_tail_150 = g_buffer_a;
    g_owner.buffer_b_head_15c = g_owner.buffer_b_tail_160 = g_buffer_b;
    g_expected_owner = &g_owner;

    // A value other than 3: the phase word is written, the cursors are equal so
    // neither reset arm fires, and the tail is skipped.
    SimSetPhase_00c47cc0_reconstruct(&g_owner, 2);
    check(g_owner.phase_84 == 2u, "phase word written");
    check(g_dtor_calls == 0, "no destructor for a non-3 value");
    check(g_tail_calls == 0, "no tail for a non-3 value");

    // Diverge the cursors so both reset arms actually fire.
    // The body writes the 16-bit zero through the HEAD cursor, so the head is
    // what has to be dirty before the call; the tail is only a comparison
    // operand and is then overwritten with the head.
    g_owner.buffer_a_tail_150 = g_buffer_a + 4;
    g_owner.buffer_b_tail_160 = g_buffer_b + 4;
    g_buffer_a[0] = 0x1234;
    g_buffer_b[0] = 0x5678;
    g_owner.phase_84 = 7u;
    SimSetPhase_00c47cc0_reconstruct(&g_owner, 2);
    check(g_buffer_a[0] == 0u, "buffer a head cleared");
    check(g_owner.buffer_a_tail_150 == g_buffer_a, "buffer a tail pulled back to head");
    check(g_buffer_b[0] == 0u, "buffer b head cleared");
    check(g_owner.buffer_b_tail_160 == g_buffer_b, "buffer b tail pulled back to head");
    check(g_dtor_calls == 0, "still no destructor for a non-3 value");

    // Idempotence: re-setting the same value short-circuits before everything.
    g_owner.buffer_a_tail_150 = g_buffer_a + 4;
    g_owner.phase_84 = 2u;
    g_buffer_a[0] = 0x4321;
    SimSetPhase_00c47cc0_reconstruct(&g_owner, 2);
    check(g_buffer_a[0] == 0x4321u, "unchanged value short-circuits before the buffer reset");
    check(g_dtor_calls == 0, "unchanged value never reaches the tail");

    // Value 3: the tail runs, with the observed immediates and argument order.
    SimSetPhase_00c47cc0_reconstruct(&g_owner, 3);
    check(g_owner.phase_84 == 3u, "phase 3 stored");
    check(g_tail_calls == 1, "tail ran once");
    check(g_tail_arg0 == 0x038cf2fdu, "tail first argument is the observed immediate");
    check(g_tail_arg2 == 0u, "tail third argument is the observed zero");
    check(g_tail_saw_owner, "temporary carries the receiver at pair[0].first");
    check(g_tail_saw_pair5, "temporary pair[5].first holds the observed immediate");
    check(g_tail_saw_mask_zero, "temporary selector mask is zero as observed");
    check(g_dtor_calls == 1, "temporary destroyed after the tail");
    check(g_dtor_final_vtable == 0x013eb844u, "temporary vtable before the destructor");

    if (failures == 0) {
        std::printf("00c47cc0 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
