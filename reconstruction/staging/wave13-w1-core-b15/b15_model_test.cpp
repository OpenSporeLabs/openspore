// Model test for the six wave13-w1-core-b15 reconstructions.
//
// It links the six reconstruction translation units against recording stubs for
// the opaque ports declared in b15_opaque_types.hpp and asserts the observable
// behaviour that the disassembly pins down: the guard predicate and release
// order of 0x00ff2e30, the popcount arithmetic of 0x00ff0870, the pure store of
// 0x00c0b370, the pure load of 0x00c0c2f0, the seven gates of 0x00dd6df0 and
// the three-way selector of 0x00d1e610.
//
// The stubs live in this file only. They are host models of UNRESOLVED call
// targets; they are not reconstructions of the original callees.

#include "b15_opaque_types.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace openspore::wave13_w1_core_b15 {
void destroy_00ff2e30(OpaqueNode* self) noexcept;
void set_field_e3c_00c0b370(OpaqueSimState* self, std::int32_t value) noexcept;
std::int32_t counter_minus_used_bits_00ff0870(const OpaqueCounter* self) noexcept;
std::int32_t get_field_eac_00c0c2f0(const OpaqueSimState* self) noexcept;
bool attach_00dd6df0(OpaqueRecordMap* self, const std::uint16_t* arg1,
                     std::uint32_t arg2) noexcept;
std::uint32_t dispatch_active_object_00d1e610() noexcept;
}  // namespace openspore::wave13_w1_core_b15

namespace {

using namespace openspore::wave13_w1_core_b15;

int g_failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}

// --- recording state for the ports -----------------------------------------

struct Call {
    const char* name;
    std::uintptr_t arg0;
};

std::vector<Call> g_log;

void record(const char* name, std::uintptr_t arg0 = 0) {
    g_log.push_back(Call{name, arg0});
}

bool lookup_a_ok = true;
bool lookup_f0_ok = true;
bool lookup_0c_ok = true;

const std::uint8_t* g_found_range_first = nullptr;
const std::uint8_t* g_found_range_last = nullptr;
OpaqueRecord* g_erase_key = nullptr;

std::uint32_t g_selector = 0xffffffffu;
std::uint32_t g_selector_scratch = 0;
OpaqueSimSubsystem g_subsystem_a{};
OpaqueSimSubsystem g_subsystem_b{};
OpaqueSimHolder g_holder{};

// --- port definitions ------------------------------------------------------

void heap_release_port(void* payload) noexcept {
    record("heap_release", reinterpret_cast<std::uintptr_t>(payload));
}

void node_release_contents_port(OpaqueNode* self) noexcept {
    record("release_contents", reinterpret_cast<std::uintptr_t>(self));
}

void* tree_lower_bound_port(void* tree, void** out_node, const std::uint32_t* key) noexcept {
    record("tree_lower_bound", *key);
    *out_node = static_cast<void*>(g_subsystem_a.handle_70);  // reuse as node slot
    return out_node;
}

void* global_lookup_port(std::uint32_t descriptor) noexcept {
    record("global_lookup", descriptor);
    if (descriptor == 0x035ee914u) {
        return lookup_a_ok ? const_cast<std::uint32_t*>(&g_selector_scratch) : nullptr;
    }
    return const_cast<std::uint32_t*>(&g_selector_scratch);
}

void* virtual_slot_f0_port(void* handle, std::uint32_t arg, std::uint32_t flag) noexcept {
    record("vslot_f0", (static_cast<std::uintptr_t>(arg) << 8) | flag);
    (void)handle;
    return lookup_f0_ok ? const_cast<std::uint32_t*>(&g_selector_scratch) : nullptr;
}

void* virtual_slot_0c_port(void* handle, std::uint32_t arg) noexcept {
    record("vslot_0c", arg);
    (void)handle;
    return lookup_0c_ok ? const_cast<std::uint32_t*>(&g_selector_scratch) : nullptr;
}

void wide_string_normalise_port(const std::uint16_t* text) noexcept {
    record("wide_normalise", reinterpret_cast<std::uintptr_t>(text));
}

void record_process_port(OpaqueRecordMap* self, OpaqueRecord* rec) noexcept {
    record("record_process", reinterpret_cast<std::uintptr_t>(rec));
    (void)self;
}

OpaqueRecord* record_find_by_range_port(OpaqueRecordMap* self, OpaqueRecord* rec) noexcept {
    (void)self;
    (void)rec;
    record("record_find_by_range");
    return g_found_range_first != nullptr ? &g_record : nullptr;
}

void record_erase_port(OpaqueRecordMap* self, std::uint32_t key) noexcept {
    (void)self;
    g_erase_key = reinterpret_cast<OpaqueRecord*>(static_cast<std::uintptr_t>(key));
    record("record_erase", key);
}

OpaqueSimSubsystem* subsystem_a_port() noexcept { return &g_subsystem_a; }
OpaqueSimSubsystem* subsystem_b_port() noexcept { return &g_subsystem_b; }

std::uint32_t selector_port() noexcept {
    // 0x00b5b800: absent singleton yields 0xffffffff, otherwise [singleton+0x20].
    return g_subsystem_b.handle_70 == 0 ? g_selector : g_subsystem_b.selector_20;
}

// --- scratch objects -------------------------------------------------------

OpaqueNode g_node{};
alignas(8) std::uint8_t g_payload[64];
OpaqueCounter g_counter{};
OpaqueSimState g_state{};
OpaqueRecordMap g_map{};
alignas(8) OpaqueRecord g_record{};
alignas(8) std::uint8_t g_node_bytes[0x20];

void* payload_at(std::size_t index) {
    return &g_payload[index * 8];
}

void set_header(void* payload, std::int32_t header) {
    std::memcpy(static_cast<std::uint8_t*>(payload) - 4, &header, sizeof header);
}

// --- cases -----------------------------------------------------------------

void test_ff2e30() {
    // Gate on the null pointer, then on a zero block header, then release.
    struct Case {
        void* p3c;
        void* p28;
        void* p00;
        int expect_releases;
    };
    const Case cases[] = {
        {nullptr, nullptr, nullptr, 0},
        {payload_at(0), nullptr, nullptr, 1},
        {nullptr, payload_at(1), nullptr, 1},
        {nullptr, nullptr, payload_at(2), 1},
        {payload_at(0), payload_at(1), payload_at(2), 3},
    };

    for (std::size_t i = 0; i < sizeof(g_payload) / 8; ++i) {
        set_header(payload_at(i), 0x20);
    }

    for (const Case& c : cases) {
        g_node.field_00 = c.p00;
        g_node.field_28 = c.p28;
        g_node.field_3c = c.p3c;
        g_log.clear();
        destroy_00ff2e30(&g_node);
        int releases = 0;
        for (const Call& call : g_log) {
            if (std::strcmp(call.name, "heap_release") == 0) {
                ++releases;
            }
        }
        check(releases == c.expect_releases, "0x00ff2e30 release count");
        check(!g_log.empty() && std::strcmp(g_log.front().name, "release_contents") == 0,
              "0x00ff2e30 calls the base port first");
    }

    // A zero header word blocks the release even when the pointer is non-null.
    set_header(payload_at(0), 0);
    g_node.field_00 = nullptr;
    g_node.field_28 = nullptr;
    g_node.field_3c = payload_at(0);
    g_log.clear();
    destroy_00ff2e30(&g_node);
    int releases = 0;
    for (const Call& call : g_log) {
        releases += std::strcmp(call.name, "heap_release") == 0 ? 1 : 0;
    }
    check(releases == 0, "0x00ff2e30 rejects a zero block header");
    set_header(payload_at(0), 0x20);

    // Release order is +0x3c, then +0x28, then +0x00.
    g_node.field_00 = payload_at(2);
    g_node.field_28 = payload_at(1);
    g_node.field_3c = payload_at(0);
    g_log.clear();
    destroy_00ff2e30(&g_node);
    check(g_log.size() == 4, "0x00ff2e30 emits four calls when all three are live");
    if (g_log.size() == 4) {
        check(g_log[1].arg0 == reinterpret_cast<std::uintptr_t>(payload_at(0)), "order +0x3c");
        check(g_log[2].arg0 == reinterpret_cast<std::uintptr_t>(payload_at(1)), "order +0x28");
        check(g_log[3].arg0 == reinterpret_cast<std::uintptr_t>(payload_at(2)), "order +0x00");
    }
}

void test_ff0870() {
    // counter - popcount(mask), cross-checked against a naive count.
    for (std::int32_t counter : {0, 1, 7, 8, 32, -3}) {
        for (unsigned mask = 0; mask < 256; ++mask) {
            unsigned naive = 0;
            for (unsigned b = 0; b < 8; ++b) {
                naive += (mask >> b) & 1u;
            }
            g_counter.counter_24 = counter;
            g_counter.mask_28 = static_cast<std::uint8_t>(mask);
            check(counter_minus_used_bits_00ff0870(&g_counter) ==
                      static_cast<std::int32_t>(static_cast<std::uint32_t>(counter) - naive),
                  "0x00ff0870 counter minus popcount");
        }
    }
    g_counter.counter_24 = 8;
    g_counter.mask_28 = 0xff;
    check(counter_minus_used_bits_00ff0870(&g_counter) == 0, "0x00ff0870 saturates at zero");
    g_counter.counter_24 = 0;
    g_counter.mask_28 = 0x01;
    check(counter_minus_used_bits_00ff0870(&g_counter) == -1, "0x00ff0870 can go negative");
}

void test_c0b370() {
    set_field_e3c_00c0b370(&g_state, 0x341b7b33);
    check(g_state.field_e3c == static_cast<std::int32_t>(0x341b7b33u), "0x00c0b370 stores");
    set_field_e3c_00c0b370(&g_state, -1);
    check(g_state.field_e3c == -1, "0x00c0b370 stores the -1 sentinel");
    set_field_e3c_00c0b370(&g_state, 0x0609ea52);
    check(g_state.field_e3c == static_cast<std::int32_t>(0x0609ea52u),
          "0x00c0b370 stores the literal from 0x00c04363");
}

void test_c0c2f0() {
    g_state.field_eac = 2;
    check(get_field_eac_00c0c2f0(&g_state) == 2, "0x00c0c2f0 returns 2");
    g_state.field_eac = 1;
    check(get_field_eac_00c0c2f0(&g_state) == 1, "0x00c0c2f0 returns 1");
    g_state.field_eac = 0;
    check(get_field_eac_00c0c2f0(&g_state) == 0, "0x00c0c2f0 returns 0");
}

void test_dd6df0() {
    static const std::uint16_t kText[] = {0x0041, 0x0000};

    // Build a one-node tree whose value slot points at g_record.
    std::memcpy(&g_record, &g_record, sizeof g_record);
    void* rec_slot = nullptr;
    std::memcpy(&rec_slot, g_node_bytes + 0x14, sizeof rec_slot);
    rec_slot = &g_record;
    std::memcpy(g_node_bytes + 0x14, &rec_slot, sizeof rec_slot);

    g_map.tree_root_28 = g_node_bytes;
    g_map.tree_header_2c = reinterpret_cast<void*>(0xdeadbeef);
    g_record.flags_0c = 0x41u;  // bit 6 set, bit 0 clear
    g_record.range_first_68 = g_payload;
    g_record.range_last_6c = g_payload + 4;  // non-empty
    g_record.field_148 = 0x1234u;

    auto setup = [&](void* node) { g_subsystem_a.handle_70 = reinterpret_cast<std::uint32_t>(node); };

    lookup_a_ok = lookup_f0_ok = lookup_0c_ok = true;
    g_found_range_first = g_payload;
    g_found_range_last = g_payload + 4;
    g_erase_key = nullptr;

    // Gate 1: null first argument.
    setup(g_node_bytes);
    g_log.clear();
    check(!attach_00dd6df0(&g_map, nullptr, 7u), "gate 1 rejects a null argument");
    check(g_log.empty(), "gate 1 exits before any port call");

    // Gate 2: lookup returns the header sentinel.
    setup(reinterpret_cast<void*>(0xdeadbeef));
    g_log.clear();
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 2 rejects a missing key");

    // Gate 3: null mapped value.
    setup(g_node_bytes);
    rec_slot = nullptr;
    std::memcpy(g_node_bytes + 0x14, &rec_slot, sizeof rec_slot);
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 3 rejects a null record");
    rec_slot = &g_record;
    std::memcpy(g_node_bytes + 0x14, &rec_slot, sizeof rec_slot);

    // Gate 4: global lookup fails.
    lookup_a_ok = false;
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 4 rejects a failed lookup");
    lookup_a_ok = true;

    // Gate 5: vtable +0xf0 fails.
    lookup_f0_ok = false;
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 5 rejects a failed slot +0xf0 call");
    lookup_f0_ok = true;

    // Gate 6: vtable +0x0c fails.
    lookup_0c_ok = false;
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 6 rejects a failed slot +0x0c call");
    lookup_0c_ok = true;

    // Gate 7: empty record payload range.
    g_record.range_last_6c = g_payload;
    check(!attach_00dd6df0(&g_map, kText, 7u), "gate 7 rejects an empty payload range");
    g_record.range_last_6c = g_payload + 4;

    // Full success path.
    g_record.flags_0c = 0x41u;
    g_log.clear();
    check(attach_00dd6df0(&g_map, kText, 0x341b7b33u), "0x00dd6df0 succeeds on the happy path");
    check((g_record.flags_0c & ~0x40u) == 0x01u, "0x00dd6df0 clears bit 6 and sets bit 0");
    check(g_erase_key == reinterpret_cast<OpaqueRecord*>(static_cast<std::uintptr_t>(0x1234u)),
          "0x00dd6df0 erases using the +0x48 field of the located sibling");

    // No sibling means no erase.
    g_found_range_first = nullptr;
    g_erase_key = nullptr;
    g_log.clear();
    check(attach_00dd6df0(&g_map, kText, 7u), "0x00dd6df0 succeeds without a sibling");
    check(g_erase_key == nullptr, "0x00dd6df0 skips the erase when no sibling is found");

    // Verify the three descriptor constants reached the ports unchanged.
    g_log.clear();
    g_found_range_first = nullptr;
    (void)attach_00dd6df0(&g_map, kText, 7u);
    bool saw_lookup = false;
    bool saw_f0 = false;
    bool saw_0c = false;
    for (const Call& call : g_log) {
        saw_lookup |= std::strcmp(call.name, "global_lookup") == 0 && call.arg0 == 0x035ee914u;
        saw_f0 |= std::strcmp(call.name, "vslot_f0") == 0 && (call.arg0 >> 8) == 0x047d4388u &&
                  (call.arg0 & 0xffu) == 1u;
        saw_0c |= std::strcmp(call.name, "vslot_0c") == 0 && call.arg0 == 0x00f15f4bdu;
    }
    check(saw_lookup, "0x00dd6df0 passes 0x035ee914 to the global lookup");
    check(saw_f0, "0x00dd6df0 passes (0x047d4388, 1) to vtable slot +0xf0");
    check(saw_0c, "0x00dd6df0 passes 0x00f15f4bd to vtable slot +0x0c");
}

void test_d1e610() {
    g_subsystem_b.handle_70 = 1;  // singleton present
    g_subsystem_a.object_54 = 0xdeadbeefu;
    g_subsystem_a.handle_70 = 0;
    g_holder.value_11c = 0x00c0ffeeu;

    for (std::uint32_t sel : {0x01654c01u, 0x01654c10u}) {
        g_subsystem_b.selector_20 = sel;
        check(dispatch_active_object_00d1e610() == 0xdeadbeefu,
              "0x00d1e610 returns [subsystem+0x54] for 0x01654c01/0x01654c10");
    }

    g_subsystem_b.selector_20 = 0x01654c02u;
    g_subsystem_a.handle_70 = reinterpret_cast<std::uint32_t>(&g_holder);
    check(dispatch_active_object_00d1e610() == 0x00c0ffeeu,
          "0x00d1e610 returns [handle+0x11c] for 0x01654c02");
    g_subsystem_a.handle_70 = 0;
    check(dispatch_active_object_00d1e610() == 0u,
          "0x00d1e610 returns 0 for 0x01654c02 when the handle is null");

    for (std::uint32_t sel : {0u, 3u, 0x01654c03u, 0x01654c0fu, 0x01654c11u}) {
        g_subsystem_b.selector_20 = sel;
        check(dispatch_active_object_00d1e610() == 0u, "0x00d1e610 default arm returns 0");
    }

    // Absent singleton makes 0x00b5b800 return 0xffffffff, which matches no arm.
    g_subsystem_b.handle_70 = 0;
    g_selector = 0xffffffffu;
    check(dispatch_active_object_00d1e610() == 0u,
          "0x00d1e610 returns 0 when the selector is the all-ones absent marker");
}

}  // namespace

int main() {
    std::memset(g_payload, 0, sizeof g_payload);
    std::memset(&g_node, 0, sizeof g_node);
    std::memset(&g_counter, 0, sizeof g_counter);
    std::memset(&g_state, 0, sizeof g_state);
    std::memset(&g_map, 0, sizeof g_map);
    std::memset(g_node_bytes, 0, sizeof g_node_bytes);

    test_ff2e30();
    test_ff0870();
    test_c0b370();
    test_c0c2f0();
    test_dd6df0();
    test_d1e610();

    if (g_failures != 0) {
        std::printf("%d check(s) failed\n", g_failures);
        return 1;
    }
    std::printf("wave13-w1-core-b15 model test: all checks passed\n");
    return 0;
}
