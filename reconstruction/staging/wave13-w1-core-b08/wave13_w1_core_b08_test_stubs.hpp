// wave13-w1-core-b08 — control surface of the host-side port stubs.
//
// Nothing declared here is a reconstruction. The stubs live in
// wave13_w1_core_b08_test_stubs.cpp and exist only so the six reconstructed
// bodies can be driven and their call order asserted.

#ifndef OPENSPORE_WAVE13_W1_CORE_B08_TEST_STUBS_HPP
#define OPENSPORE_WAVE13_W1_CORE_B08_TEST_STUBS_HPP

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

// Shared assertion helpers, counted in g_failures.
extern int g_failures;
void note_check(bool ok, const char* what);
void note_check_u32(std::uint32_t got, std::uint32_t want, const char* what);
void note_check_f(float got, float want, const char* what);
void note_check_count(int got, int want, const char* what);

int run_tiers_and_session_model_tests();

void reset_log();
int log_count();
const char* log_entry(int i);

extern bool g_flag_60c;

// 0x00c0ce80 knobs
extern std::int32_t g_clamp_result;
extern bool g_sentinel_matches;
extern void* g_lazy_singleton;
extern float g_table_element_result;
extern std::uint8_t g_vslot_58_result;
OpaqueC0ce80SubVtable* make_c0_vtable();

// 0x00c47180 knobs
extern int g_slot_c0_calls;
extern void* g_bb59b0_manager_arg;
extern void** g_bb59b0_slot_arg;
OpaqueManagerSlotVtable* make_occupant_vtable();
void bind_manager_occupant_vtable();

// 0x00ae9f50 knobs
extern void* g_dd1ca0;
extern void* g_ae9f50_manager;
extern void* g_ae9f50_profile_a;
extern void* g_ae9f50_lookup_b;
extern void* g_ae9f50_default;
extern void* g_app_system;
extern std::uint32_t g_ae9f50_ids[4];
extern int g_ae9f50_id_count;
extern Ae9f50BootRecord* g_ae9f50_last_record;
extern void* g_ae9f50_destroyed[4];
extern int g_ae9f50_destroy_count;
extern void* g_b3d380;
extern bool g_b32250_called;
extern std::uint32_t g_b32250_id;
extern void* g_a206f0;
extern std::uint32_t g_a206f0_v20;
extern std::uint32_t g_publish_id;
extern std::uint32_t g_publish_value;
extern void* g_tool_manager;
extern int g_ae8ea0_calls;
extern void* g_noun_manager;
extern std::uint32_t g_e14c10_flag;
extern void* g_ba6d80_entry;
extern void* g_01021090;
extern int g_c35240_calls;
extern void* g_space_trading;
extern int g_ae0930_calls;
extern char* g_ae0930_slot;

// 0x00ba61b0 knobs
extern void* g_alloc_result;
extern std::uint32_t g_alloc_size;
extern const char* g_alloc_type_name;
extern int g_construct_calls;
extern std::uint32_t g_set_key_value;
extern int g_register_calls;
extern int g_notify_calls;
extern int g_vslot_0_calls;
OpaqueCPlanetRecordVtable* make_record_vtable();

}  // namespace wave13_w1_core_b08
}  // namespace openspore

#endif  // OPENSPORE_WAVE13_W1_CORE_B08_TEST_STUBS_HPP
