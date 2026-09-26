// Model test for 0x00b25c30. Pins the early-exit polarity, the first-match
// (not first-non-match) ordering, the identity of the returned pointer, the
// vtable slot offset actually dispatched (+0x58) and the five callee immediates
// in push order.

#include "sim_findfirst_00b25c30.hpp"

#include "b09_opaque_ports.hpp"

#include <cstdio>

extern "C" B09_THISCALL OpaqueRegistryElement* SimFindFirst_00b25c30_reconstruct(
    OpaqueRegistryOwnerObserved*);

namespace {

OpaqueRegistryOwnerObserved g_owner{};

OpaqueRegistryContainerObserved g_container{};
OpaqueRegistryLookup5Args g_seen_args{};
OpaqueRegistryOwnerObserved* g_seen_self = nullptr;
int g_lookup_calls = 0;

OpaqueRegistryElement g_elements[4];
OpaqueRegistryElement* g_element_ptrs[4];

// Per-element predicate state, addressed by the receiver the slot receives.
bool g_result[4];
int g_id_of[4];

std::uintptr_t g_call_order[8];
int g_call_order_len = 0;

int failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL %s\n", what);
        ++failures;
    }
}

// The stand-in for slot +0x58. It receives exactly what the original passes in
// ECX: the interface sub-object at element + 0x120.
bool probe_slot_58(OpaqueRegistryElementIfc120* self) {
    int index = -1;
    for (int i = 0; i < 4; ++i) {
        if (self == &g_elements[i].iface_120) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        return false;
    }
    for (int i = 0; i < g_call_order_len && i < 8; ++i) {
        if (g_call_order[i] == static_cast<std::uintptr_t>(index)) {
            return g_result[index];
        }
    }
    if (g_call_order_len < 8) {
        g_call_order[g_call_order_len++] = static_cast<std::uintptr_t>(index);
    }
    (void)g_id_of;
    return g_result[index];
}

OpaqueSlot58TableObserved g_table{};

}  // namespace

// Test double for the single unresolved callee.
extern "C" OpaqueRegistryContainerObserved* opaque_RegistryLookup5Args_00b21340(
    OpaqueRegistryOwnerObserved* self, const OpaqueRegistryLookup5Args& args) {
    ++g_lookup_calls;
    g_seen_self = self;
    g_seen_args = args;
    return &g_container;
}

namespace {

void set_results(const bool* results, int n) {
    g_call_order_len = 0;
    g_table.slots[0x58 / sizeof(void*)] = reinterpret_cast<void*>(&probe_slot_58);
    for (int i = 0; i < 4; ++i) {
        g_result[i] = (i < n) ? results[i] : false;
        g_id_of[i] = i;
        g_elements[i].iface_120.vtable = &g_table;
    }
    for (int i = 0; i < 4; ++i) {
        g_element_ptrs[i] = &g_elements[i];
    }
    // The container holds an array of 4-byte POINTERS, which is what the
    // SAR-by-2 element count and the [ESI + EBX*4] indexing assume.
    g_container.element_array_begin = g_element_ptrs;
    g_container.element_array_end = g_element_ptrs + 4;
}

std::uintptr_t addr(int i) { return reinterpret_cast<std::uintptr_t>(&g_elements[i]); }

}  // namespace

int main() {
    // The five immediates, in push order.
    const bool none[4] = {false, false, false, false};
    set_results(none, 4);
    OpaqueRegistryElement* r = SimFindFirst_00b25c30_reconstruct(&g_owner);
    check(g_lookup_calls == 1, "callee ran once");
    check(g_seen_self == &g_owner, "receiver forwarded unchanged in ECX");
    check(reinterpret_cast<std::uintptr_t>(g_seen_args.arg1_key_bss_dword) == 0x018c43e8u,
          "arg1 immediate");
    check(reinterpret_cast<std::uintptr_t>(g_seen_args.arg2_code_00b1e500) == 0x00b1e500u,
          "arg2 immediate");
    check(reinterpret_cast<std::uintptr_t>(g_seen_args.arg3_code_00acdff0) == 0x00acdff0u,
          "arg3 immediate");
    check(reinterpret_cast<std::uintptr_t>(g_seen_args.arg4_code_00d3d420) == 0x00d3d420u,
          "arg4 immediate");
    check(reinterpret_cast<std::uintptr_t>(g_seen_args.arg5_code_00cd7d10) == 0x00cd7d10u,
          "arg5 immediate");
    check(r == nullptr, "no match returns null");
    check(g_call_order_len == 4, "all four elements probed");
    for (int i = 0; i < 4; ++i) {
        check(g_call_order[i] == static_cast<std::uintptr_t>(i), "probe order is array order");
    }

    // First match wins and the scan stops there.
    const bool third[4] = {false, false, true, true};
    set_results(third, 4);
    r = SimFindFirst_00b25c30_reconstruct(&g_owner);
    check(reinterpret_cast<std::uintptr_t>(r) == addr(2), "first match returned");
    check(g_call_order_len == 3, "scan stopped at the first match");

    const bool first[4] = {true, true, true, true};
    set_results(first, 4);
    r = SimFindFirst_00b25c30_reconstruct(&g_owner);
    check(reinterpret_cast<std::uintptr_t>(r) == addr(0), "index 0 match returned");
    check(g_call_order_len == 1, "scan stopped at index 0");

    // Empty and inverted spans take the signed early exit.
    g_container.element_array_begin = g_element_ptrs;
    g_container.element_array_end = g_element_ptrs;
    g_call_order_len = 0;
    check(SimFindFirst_00b25c30_reconstruct(&g_owner) == nullptr,
          "zero count returns null");
    check(g_call_order_len == 0, "zero count probes nothing");

    g_container.element_array_end = g_element_ptrs - 1;  // negative span
    check(SimFindFirst_00b25c30_reconstruct(&g_owner) == nullptr,
          "negative span returns null");
    check(g_call_order_len == 0, "negative span probes nothing");

    if (failures == 0) {
        std::printf("00b25c30 model test passed\n");
    }
    return failures == 0 ? 0 : 1;
}
