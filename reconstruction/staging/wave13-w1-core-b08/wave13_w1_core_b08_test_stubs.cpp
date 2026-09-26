// wave13-w1-core-b08 — host-side recording stubs for the opaque ports.
//
// These are NOT reconstructions. Every port below is an unresolved callee of
// one of the six reconstructed functions; the stubs exist only so the
// reconstructed control flow, field offsets and constants can be exercised and
// asserted. Each stub records what it was handed so the model tests can check
// the reconstructed call order, argument values and branch polarity.
//
// The only values hard-coded here are ones read live out of the binary image:
// the file contents of the two tables and the 0.5f multiplier.

#include "wave13_w1_core_b08.hpp"
#include "wave13_w1_core_b08_test_stubs.hpp"

#include <cstdarg>
#include <cstdio>
#include <cmath>
#include <cstring>

namespace openspore {
namespace wave13_w1_core_b08 {

// --- live file-image contents -------------------------------------------

// 0x015D9650 .. 0x015D9667: six dwords, all zero in the shipped image.
float g_table_015d9650[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

// 0x015716D8 onward: file image reads 0, -1, 0, 1.
std::int32_t g_tier_delta_015716d8[4] = {0, -1, 0, 1};

// 0x01471064: 0x3F000000.
float g_scale_01471064 = 0.5f;

// 0x01654C10: the dword is zero in the shipped image; the address is the
// sentinel, not its value.
void* const k_sentinel_01654c10 = reinterpret_cast<void*>(0x01654C10u);

// 0x0167EAE4: read by 0x00B3D2A0.
void* g_manager_0167eae4 = nullptr;

// --- recorder ------------------------------------------------------------

struct CallLog {
    static const int kMax = 512;
    char entries[kMax][96];
    int count = 0;
    void add(const char* fmt, ...);
};

CallLog g_log;

void CallLog::add(const char* fmt, ...) {
    if (count >= kMax) {
        return;
    }
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(entries[count], sizeof(entries[0]), fmt, ap);
    va_end(ap);
    ++count;
}

int g_failures = 0;

void note_check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}

void note_check_u32(std::uint32_t got, std::uint32_t want, const char* what) {
    if (got != want) {
        std::printf("FAIL: %s (got %u want %u)\n", what, got, want);
        ++g_failures;
    }
}

void note_check_f(float got, float want, const char* what) {
    if (!(std::fabs(got - want) < 1e-6f)) {
        std::printf("FAIL: %s (got %f want %f)\n", what, static_cast<double>(got),
                    static_cast<double>(want));
        ++g_failures;
    }
}

void note_check_count(int got, int want, const char* what) {
    if (got != want) {
        std::printf("FAIL: %s (got %d want %d)\n", what, got, want);
        ++g_failures;
    }
}

void reset_log() {
    g_log.count = 0;
    for (int i = 0; i < CallLog::kMax; ++i) {
        g_log.entries[i][0] = '\0';
    }
}

int log_count() {
    return g_log.count;
}

const char* log_entry(int i) {
    return (i >= 0 && i < g_log.count) ? g_log.entries[i] : "<none>";
}

// --- 0x00c0b780 ----------------------------------------------------------

bool g_flag_60c = false;

bool port_00c0b7a0_flag_60c(OpaqueC0b780Owner* self) {
    const std::uint32_t sub = reinterpret_cast<std::uint32_t>(self->f_B20);
    const bool v = *reinterpret_cast<const std::uint32_t*>(sub + 0x60Cu) != 0u;
    g_log.add("b7a0(%08x)=%d", sub, v ? 1 : 0);
    return v;
}

// --- 0x00c0ce80 ----------------------------------------------------------

std::int32_t g_clamp_result = 0;
bool g_sentinel_matches = false;
void* g_lazy_singleton = nullptr;
float g_table_element_result = 0.0f;
std::uint8_t g_vslot_58_result = 0;
OpaqueC0ce80SubVtable* g_c0_vtable = nullptr;

std::int32_t port_00c0ce30_clamp_index(OpaqueC0ce80Tiers* self, std::uint32_t tier,
                                       std::uint32_t use_base_offset) {
    (void)self;
    g_log.add("c0ce30(tier=%u,useBase=%u)=%d", tier, use_base_offset,
              static_cast<int>(g_clamp_result));
    return g_clamp_result;
}

void* port_00b5b800_lookup_sentinel() {
    g_log.add("b5b800()=%s", g_sentinel_matches ? "SENTINEL" : "other");
    return g_sentinel_matches ? k_sentinel_01654c10
                              : reinterpret_cast<void*>(0x00A42730u);
}

void* port_00c03260_lazy_singleton() {
    g_log.add("c03260()=%p", g_lazy_singleton);
    return g_lazy_singleton;
}

float port_00f31500_table_element(void* singleton, void* self, std::int32_t index) {
    (void)self;
    g_log.add("f31500(%p,idx=%d)=%f", singleton, static_cast<int>(index),
              static_cast<double>(g_table_element_result));
    return g_table_element_result;
}

static std::uint8_t stub_vslot_58(OpaqueC0ce80Tiers* sub) {
    (void)sub;
    g_log.add("vslot_58()=%u", static_cast<unsigned>(g_vslot_58_result));
    return g_vslot_58_result;
}

// --- 0x00b8dad0: no ports -----------------------------------------------

// --- 0x00c47180 ----------------------------------------------------------

int g_slot_c0_calls = 0;
void* g_bb59b0_manager_arg = nullptr;
void** g_bb59b0_slot_arg = nullptr;
OpaqueManagerSlotVtable* g_occupant_vtable = nullptr;

static void stub_slot_c0(OpaqueManagerSlotOccupant* o) {
    (void)o;
    ++g_slot_c0_calls;
    g_log.add("vslot_C0()");
}

void* port_00b3d2a0_manager_getter() {
    g_log.add("b3d2a0()=%p", g_manager_0167eae4);
    return g_manager_0167eae4;
}

void port_00bb59b0_replace(OpaqueC47180Owner* self, void* manager, void** slot_io) {
    (void)self;
    g_bb59b0_manager_arg = manager;
    g_bb59b0_slot_arg = slot_io;
    g_log.add("bb59b0(manager=%p,slot=%p)", manager, static_cast<void*>(slot_io));
}

// --- 0x00ae9f50 ----------------------------------------------------------

void* g_dd1ca0 = nullptr;
void* g_ae9f50_manager = nullptr;
void* g_ae9f50_profile_a = nullptr;
void* g_ae9f50_lookup_b = nullptr;
void* g_ae9f50_default = nullptr;
void* g_app_system = nullptr;
std::uint32_t g_ae9f50_ids[4] = {0, 0, 0, 0};
int g_ae9f50_id_count = 0;
Ae9f50BootRecord* g_ae9f50_last_record = nullptr;
void* g_ae9f50_destroyed[4] = {nullptr, nullptr, nullptr, nullptr};
int g_ae9f50_destroy_count = 0;
void* g_b3d380 = nullptr;
bool g_b32250_called = false;
std::uint32_t g_b32250_id = 0;
void* g_a206f0 = nullptr;
std::uint32_t g_a206f0_v20 = 0xABCDu;
std::uint32_t g_publish_id = 0;
std::uint32_t g_publish_value = 0;
void* g_tool_manager = nullptr;
int g_ae8ea0_calls = 0;
void* g_noun_manager = nullptr;
std::uint32_t g_e14c10_flag = 0;
void* g_ba6d80_entry = nullptr;
void* g_01021090 = nullptr;
int g_c35240_calls = 0;
void* g_space_trading = nullptr;
int g_ae0930_calls = 0;
char* g_ae0930_slot = nullptr;

void* port_00dd1ca0_get() {
    g_log.add("dd1ca0()");
    return g_dd1ca0;
}

void port_00dd30d0_apply(void* a) {
    g_log.add("dd30d0(%p)", a);
}

void* port_00b3d2a0_manager_get() {
    return g_ae9f50_manager;
}

void* port_00ba9370_map_lookup(void* mgr, std::uint32_t key) {
    g_log.add("ba9370(%p,key=%08x)=%p", mgr, key, g_ae9f50_profile_a);
    return g_ae9f50_profile_a;
}

void* port_00b3d300_lookup() {
    return g_ae9f50_manager;
}

void* port_00b20750_map_lookup(void* mgr, std::uint32_t key) {
    g_log.add("b20750(%p,key=%08x)=%p", mgr, key, g_ae9f50_lookup_b);
    return g_ae9f50_lookup_b;
}

void* port_00bd9bf0_default() {
    g_log.add("bd9bf0()=%p", g_ae9f50_default);
    return g_ae9f50_default;
}

void* port_0067dcc0_app_system() {
    return g_app_system;
}

void port_0067dcc0_vslot_14(void* app_system, std::uint32_t id, Ae9f50BootRecord* rec,
                            std::uint32_t zero) {
    (void)app_system;
    g_ae9f50_ids[g_ae9f50_id_count] = id;
    ++g_ae9f50_id_count;
    g_ae9f50_last_record = rec;
    g_log.add("appsystem_vslot_14(id=%08x,rec=%p,zero=%u)", id,
              static_cast<void*>(rec), zero);
}

std::uint32_t port_a206f0_vslot_20(void* obj) {
    (void)obj;
    g_log.add("a206f0_vslot_20()=%08x", g_a206f0_v20);
    return g_a206f0_v20;
}

void* port_01021300_current() {
    g_log.add("01021300()");
    return g_dd1ca0;
}

void port_00421cf0_destroy_record(void* rec) {
    if (g_ae9f50_destroy_count < 4) {
        g_ae9f50_destroyed[g_ae9f50_destroy_count] = rec;
    }
    ++g_ae9f50_destroy_count;
    g_log.add("421cf0(%p)", rec);
}

void* port_00b3d380_get() {
    return g_b3d380;
}

void port_00b32250_set_flag(void* mgr, std::uint32_t id) {
    (void)mgr;
    g_b32250_called = true;
    g_b32250_id = id;
    g_log.add("b32250(id=%08x)", id);
}

void* port_00a206f0_get() {
    return g_a206f0;
}

void port_00435ed0_publish(std::uint32_t id, std::uint32_t value) {
    g_publish_id = id;
    g_publish_value = value;
    g_log.add("435ed0(id=%08x,value=%08x)", id, value);
}

void* port_00b3d490_tool_manager() {
    return g_tool_manager;
}

void port_00ae8ea0_reset(void* tool_manager) {
    (void)tool_manager;
    ++g_ae8ea0_calls;
    g_log.add("ae8ea0()");
}

void* port_00b3d400_noun_manager() {
    return g_noun_manager;
}

void port_00e14c10_configure(void* nouns, std::uint32_t flag) {
    (void)nouns;
    g_e14c10_flag = flag;
    g_log.add("e14c10(flag=%u)", flag);
}

void* port_00ba6d80_lookup(void* mgr, std::uint32_t planet_id) {
    g_log.add("ba6d80(%p,id=%08x)=%p", mgr, planet_id, g_ba6d80_entry);
    return g_ba6d80_entry;
}

void* port_01021090_get() {
    return g_01021090;
}

void port_00c35240_bind(void* obj, void* arg) {
    (void)obj;
    (void)arg;
    ++g_c35240_calls;
    g_log.add("c35240()");
}

void* port_00b3d4d0_space_trading() {
    return g_space_trading;
}

void port_00ae0930_release(void* trading, char* slot, std::uint32_t one, std::uint32_t z0,
                          std::uint32_t z1, std::uint32_t z2, std::uint32_t z3) {
    (void)trading;
    (void)z0;
    (void)z1;
    (void)z2;
    (void)z3;
    ++g_ae0930_calls;
    g_ae0930_slot = slot;
    g_log.add("ae0930(slot=%p,one=%u)", static_cast<void*>(slot), one);
}

// --- 0x00ba61b0 ----------------------------------------------------------

void* g_alloc_result = nullptr;
std::uint32_t g_alloc_size = 0;
const char* g_alloc_type_name = nullptr;
int g_construct_calls = 0;
std::uint32_t g_set_key_value = 0;
int g_register_calls = 0;
int g_notify_calls = 0;
int g_vslot_0_calls = 0;

void* port_00f473a0_alloc(std::uint32_t size, const char* type_name, std::uint32_t a3,
                          std::uint32_t a4, std::uint32_t a5, std::uint32_t a6) {
    (void)a3;
    (void)a4;
    (void)a5;
    (void)a6;
    g_alloc_size = size;
    g_alloc_type_name = type_name;
    g_log.add("f473a0(size=%u,type=%s)", size, type_name);
    return g_alloc_result;
}

void port_00b8e180_construct(OpaqueCPlanetRecord* self) {
    (void)self;
    ++g_construct_calls;
    g_log.add("b8e180()");
}

void port_00b8da80_set_key(OpaqueCPlanetRecord* self, std::uint32_t planet_id) {
    (void)self;
    g_set_key_value = planet_id;
    g_log.add("b8da80(id=%08x)", planet_id);
}

void port_006ac040_register(void* record, std::uint32_t one) {
    (void)record;
    (void)one;
    ++g_register_calls;
    g_log.add("6ac040()");
}

void port_006ad010_notify(void* record) {
    (void)record;
    ++g_notify_calls;
    g_log.add("6ad010()");
}

// --- fixture builders ----------------------------------------------------

OpaqueC0ce80SubVtable* make_c0_vtable() {
    static OpaqueC0ce80SubVtable table;
    for (std::size_t i = 0; i < sizeof(table.slots) / sizeof(table.slots[0]); ++i) {
        table.slots[i] = nullptr;
    }
    table.slots[0x58 / sizeof(C0ce80Vslot)] = stub_vslot_58;
    return &table;
}

OpaqueManagerSlotVtable* make_occupant_vtable() {
    static OpaqueManagerSlotVtable table;
    for (std::size_t i = 0; i < sizeof(table.slots) / sizeof(table.slots[0]); ++i) {
        table.slots[i] = nullptr;
    }
    table.slots[0xC0 / sizeof(C47180Vslot)] = stub_slot_c0;
    return &table;
}

void bind_manager_occupant_vtable() {
    g_occupant_vtable = make_occupant_vtable();
}

OpaqueCPlanetRecordVtable* make_record_vtable() {
    static OpaqueCPlanetRecordVtable table;
    table.slot_00 = [](OpaqueCPlanetRecord* r) {
        (void)r;
        ++g_vslot_0_calls;
        g_log.add("record_vslot_0()");
    };
    return &table;
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
