// Model test for 0x00c0ce80 and 0x00ae9f50.
//
// These two bodies have real control flow, so the assertions below pin the
// branch polarity, the two constants read from the image (0.5f at 0x01471064,
// the six-entry table at 0x015D9650) and the two record ids 0x3AC86B5 /
// 0x43F2590 that 0x00ae9f50 submits to AppSystem slot +0x14.

#include "wave13_w1_core_b08.hpp"
#include "wave13_w1_core_b08_reconstructed.hpp"
#include "wave13_w1_core_b08_test_stubs.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>


namespace {

namespace osb2 = openspore::wave13_w1_core_b08;

using openspore::wave13_w1_core_b08::note_check;
using openspore::wave13_w1_core_b08::note_check_f;
using openspore::wave13_w1_core_b08::note_check_count;
using openspore::wave13_w1_core_b08::note_check_u32;

alignas(8) std::uint8_t g_tier_storage[sizeof(osb2::OpaqueC0ce80Tiers)];
alignas(8) std::uint8_t g_sub_storage[sizeof(osb2::OpaqueAe9f50SubObject)];
alignas(8) std::uint8_t g_session_storage[sizeof(osb2::OpaqueAe9f50Session)];
alignas(8) char g_slot64[4] = {'A', 'B', 'C', 0};

osb2::OpaqueC0ce80Tiers* make_tiers() {
    osb2::OpaqueC0ce80Tiers* t =
        reinterpret_cast<osb2::OpaqueC0ce80Tiers*>(g_tier_storage);
    std::memset(g_tier_storage, 0, sizeof(g_tier_storage));
    t->f_C0 = osb2::make_c0_vtable();
    return t;
}

// --- 0x00c0ce80 ----------------------------------------------------------
//
// Reconstructed contract, in order:
//   tier == 0                          -> 0.0f            (TEST EAX,EAX / JZ)
//   index = port_00c0ce30(self, tier, use_base_offset)
//   base  = sentinel ? port_00f31500(...) : table[index]
//   vtable slot +0x58 of this+0xC0 == 0 -> base
//   v = (index + 1) < 6 ? table[index + 1]
//                     : (index != 0)  ? table[index - 1] : base
//   return v + 0.5f * |tier_as_float - v|

void test_c0ce80() {
    osb2::OpaqueC0ce80Tiers* t = make_tiers();

    for (std::size_t i = 0; i < 6; ++i) {
        osb2::g_table_015d9650[i] = static_cast<float>(i) * 10.0f;
    }
    osb2::g_scale_01471064 = 0.5f;

    // tier == 0 short-circuits before every port.
    osb2::reset_log();
    osb2::g_clamp_result = 3;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, 0u, 0u), 0.0f,
            "0x00c0ce80 tier 0 returns 0.0f");
    note_check_count(osb2::log_count(), 0u, "0x00c0ce80 tier 0 calls no port");

    // vslot +0x58 returning 0 short-circuits to the base value.
    osb2::g_sentinel_matches = false;
    osb2::g_clamp_result = 2;
    osb2::g_vslot_58_result = 0;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, 1u, 1u), 20.0f,
            "0x00c0ce80 with slot +0x58 == 0 returns table[index]");

    // vslot +0x58 returning 1 walks the neighbour table. 0x00C0CF24 loads the
    // FIRST STACK WORD as a float, so the tier argument must be supplied as a
    // float bit pattern here, not as a small integer: 0x3FC00000 is 1.5f.
    const std::uint32_t kTier15 = 0x3FC00000u;
    osb2::g_vslot_58_result = 1;
    osb2::g_clamp_result = 2;
    // index + 1 == 3 < 6, so v = table[3] = 30.
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, kTier15, 1u),
                 30.0f + 0.5f * 28.5f,
                 "0x00c0ce80 uses table[index + 1] and 0.5f * |tier - v|");

    // index == 5: index + 1 == 6 fails the unsigned compare and index != 0, so
    // v = table[index - 1] = table[4] = 40.
    osb2::g_clamp_result = 5;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, kTier15, 1u),
                 40.0f + 0.5f * 38.5f,
                 "0x00c0ce80 wraps to table[index - 1] at index 5");

    // index == 0: the unsigned compare (0 + 1 < 6) succeeds, so v = table[1].
    osb2::g_clamp_result = 0;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, kTier15, 1u),
                 10.0f + 0.5f * 8.5f,
                 "0x00c0ce80 at index 0 takes table[1]");

    // The three observed call sites in 0x00C0CF50 pass the tier as the small
    // integers 1, 2 and 3. 0x00C0CF24 reinterprets those bit patterns as
    // floats, where they are denormals of magnitude ~1e-44, so the effective
    // shipping-build result is v + 0.5f * v. This is asserted, not smoothed
    // over: it is the reason the second argument is typed uint32_t here.
    osb2::g_clamp_result = 2;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, 1u, 1u), 45.0f,
                 "0x00c0ce80 with the integer tier 1 reinterprets it as a denormal");
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, 2u, 1u), 45.0f,
                 "0x00c0ce80 with the integer tier 2 reinterprets it as a denormal");

    // Sentinel branch: 0x00B5B800 == 0x01654C10 routes through the lazy
    // singleton and 0x00F31500 instead of the static table.
    osb2::reset_log();
    osb2::g_sentinel_matches = true;
    osb2::g_lazy_singleton = reinterpret_cast<void*>(0x0168D824u);
    osb2::g_table_element_result = 7.5f;
    osb2::g_vslot_58_result = 0;
    osb2::g_clamp_result = 4;
    note_check_f(osb2::SimCore_00c0ce80_tier_value_lookup(t, 1u, 1u), 7.5f,
            "0x00c0ce80 sentinel branch returns the 0x00F31500 value");
    note_check(std::strstr(osb2::log_entry(0), "c0ce30") != nullptr,
          "0x00c0ce80 calls 0x00C0CE30 first");
    note_check(std::strstr(osb2::log_entry(1), "b5b800") != nullptr,
          "0x00c0ce80 then calls 0x00B5B800");
    note_check(std::strstr(osb2::log_entry(2), "c03260") != nullptr,
          "0x00c0ce80 then calls 0x00C03260 on the sentinel branch");
    note_check(std::strstr(osb2::log_entry(3), "f31500") != nullptr,
          "0x00c0ce80 then calls 0x00F31500 on the sentinel branch");

    // use_base_offset == 0 is what makes 0x00C0CE30 add this->f_FA0; the
    // reconstruction forwards the flag verbatim rather than applying it here.
    osb2::reset_log();
    osb2::g_sentinel_matches = false;
    osb2::g_clamp_result = 1;
    osb2::g_vslot_58_result = 0;
    (void)osb2::SimCore_00c0ce80_tier_value_lookup(t, kTier15, 0u);
    note_check(std::strstr(osb2::log_entry(0), "tier=1069547520,useBase=0") != nullptr,
          "0x00c0ce80 forwards use_base_offset == 0 verbatim");

    osb2::g_scale_01471064 = 0.5f;
}

// --- 0x00ae9f50 ----------------------------------------------------------

osb2::OpaqueAe9f50Session* make_session(osb2::OpaqueAe9f50SubObject* sub) {
    osb2::OpaqueAe9f50Session* s =
        reinterpret_cast<osb2::OpaqueAe9f50Session*>(g_session_storage);
    std::memset(g_session_storage, 0, sizeof(g_session_storage));
    s->f_20 = sub;
    s->f_64 = g_slot64;
    s->f_68 = g_slot64;
    s->f_74 = -1;
    return s;
}

void reset_ae9f50_knobs() {
    osb2::g_ae9f50_manager = reinterpret_cast<void*>(0x0167EAE4u);
    osb2::g_ae9f50_profile_a = reinterpret_cast<void*>(0x00AA0001u);
    osb2::g_ae9f50_lookup_b = reinterpret_cast<void*>(0x00BB0001u);
    osb2::g_ae9f50_default = reinterpret_cast<void*>(0x00CC0001u);
    osb2::g_app_system = reinterpret_cast<void*>(0x0067DCC0u);
    osb2::g_ae9f50_id_count = 0;
    osb2::g_ae9f50_last_record = nullptr;
    osb2::g_ae9f50_destroy_count = 0;
    osb2::g_b3d380 = nullptr;
    osb2::g_b32250_called = false;
    osb2::g_a206f0 = nullptr;
    osb2::g_tool_manager = nullptr;
    osb2::g_ae8ea0_calls = 0;
    osb2::g_noun_manager = nullptr;
    osb2::g_e14c10_flag = 0;
    osb2::g_ba6d80_entry = nullptr;
    osb2::g_c35240_calls = 0;
    osb2::g_space_trading = nullptr;
    osb2::g_ae0930_calls = 0;
    osb2::g_publish_id = 0;
    osb2::g_publish_value = 0;
}

void test_ae9f50_null_subobject() {
    osb2::OpaqueAe9f50Session* s = make_session(nullptr);
    reset_ae9f50_knobs();
    osb2::reset_log();
    osb2::SimCore_00ae9f50_session_boot_register(s);
    note_check(osb2::g_ae9f50_id_count == 0,
          "0x00ae9f50 with a null +0x20 sub-object submits nothing");
    note_check(osb2::log_count() == 2,
          "0x00ae9f50 with a null +0x20 sub-object only runs the two prologue calls");
}

void test_ae9f50_c_nonnull_branch() {
    osb2::OpaqueAe9f50SubObject* sub =
        reinterpret_cast<osb2::OpaqueAe9f50SubObject*>(g_sub_storage);
    std::memset(g_sub_storage, 0, sizeof(g_sub_storage));
    sub->f_0C = 0x1234u;   // non-zero -> BL == 0
    sub->f_18 = 0xABCDu;
    sub->f_20 = reinterpret_cast<void*>(0x00D0D0D0u);
    sub->f_24 = 0x00E0E0E0u;
    sub->f_28 = reinterpret_cast<void*>(0x00F0F0F0u);
    sub->f_30 = 0u;

    osb2::OpaqueAe9f50Session* s = make_session(sub);
    reset_ae9f50_knobs();
    osb2::reset_log();
    osb2::SimCore_00ae9f50_session_boot_register(s);

    note_check(osb2::g_ae9f50_id_count == 2,
          "0x00ae9f50 submits two records when +0x0C is non-zero and +0x30 is 0");
    note_check_u32(osb2::g_ae9f50_ids[0], 0x3AC86B5u, "0x00ae9f50 first record id 0x3AC86B5");
    note_check_u32(osb2::g_ae9f50_ids[1], 0x43F2590u, "0x00ae9f50 second record id 0x43F2590");
    note_check(osb2::g_ae9f50_last_record != nullptr &&
              osb2::g_ae9f50_last_record->dword_30 == 0x43F2590u,
          "0x00ae9f50 the second submitted record carries id 0x43F2590");
    note_check(osb2::g_ae9f50_destroy_count == 2,
          "0x00ae9f50 destroys both stack records");
    note_check(osb2::g_e14c10_flag == 1u, "0x00ae9f50 configures the noun manager with 1");
    note_check(osb2::g_publish_id == 0x1E5E7302u, "0x00ae9f50 publishes under 0x1E5E7302");
    note_check(osb2::g_publish_value == 0u,
          "0x00ae9f50 publishes 0 when 0x00A206F0 returns null");
    note_check(osb2::g_ae0930_calls == 0,
          "0x00ae9f50 skips the trading release when +0x64 already equals +0x68");
    note_check(s->f_74 == -1, "0x00ae9f50 leaves +0x74 at -1 when it was already -1");
}

void test_ae9f50_c_null_branch() {
    osb2::OpaqueAe9f50SubObject* sub =
        reinterpret_cast<osb2::OpaqueAe9f50SubObject*>(g_sub_storage);
    std::memset(g_sub_storage, 0, sizeof(g_sub_storage));
    sub->f_0C = 0u;        // zero -> BL == 1
    sub->f_18 = 0xABCDu;
    sub->f_28 = nullptr;   // forces the 0x00BD9BF0 default
    sub->f_30 = 0u;

    osb2::OpaqueAe9f50Session* s = make_session(sub);
    reset_ae9f50_knobs();
    osb2::reset_log();
    osb2::SimCore_00ae9f50_session_boot_register(s);

    // profile is null on this branch, so the second record's guard
    // (CMP EBP,EAX after 0x01021300) is decided by the 0x01021300 return.
    bool used_default = false;
    for (int i = 0; i < osb2::log_count(); ++i) {
        if (std::strstr(osb2::log_entry(i), "bd9bf0") != nullptr) {
            used_default = true;
        }
    }
    note_check(used_default,
          "0x00ae9f50 falls back to 0x00BD9BF0 when +0x28 is null on the +0x0C == 0 branch");
}

void test_ae9f50_side_effects() {
    osb2::OpaqueAe9f50SubObject* sub =
        reinterpret_cast<osb2::OpaqueAe9f50SubObject*>(g_sub_storage);
    std::memset(g_sub_storage, 0, sizeof(g_sub_storage));
    sub->f_0C = 0x99u;
    sub->f_30 = 0x01u;   // non-zero: the second record is skipped

    osb2::OpaqueAe9f50Session* s = make_session(sub);
    reset_ae9f50_knobs();
    osb2::g_b3d380 = reinterpret_cast<void*>(0x00B3D380u);
    osb2::g_a206f0 = reinterpret_cast<void*>(0x00A206F0u);
    osb2::g_a206f0_v20 = 0x12345678u;
    osb2::g_tool_manager = reinterpret_cast<void*>(0x00B3D490u);
    osb2::g_noun_manager = reinterpret_cast<void*>(0x00B3D400u);
    osb2::g_ba6d80_entry = reinterpret_cast<void*>(0x00BA6D80u);
    osb2::g_01021090 = reinterpret_cast<void*>(0x01021090u);
    osb2::g_space_trading = reinterpret_cast<void*>(0x00B3D4D0u);
    s->f_74 = 0x00ABCDEFu;
    s->f_68 = nullptr;   // differs from f_64, so the release branch is taken
    g_slot64[0] = 'A';

    osb2::reset_log();
    osb2::SimCore_00ae9f50_session_boot_register(s);

    note_check(osb2::g_ae9f50_id_count == 1,
          "0x00ae9f50 submits one record when +0x30 is non-zero");
    note_check_u32(osb2::g_ae9f50_ids[0], 0x3AC86B5u, "0x00ae9f50 still submits 0x3AC86B5");
    note_check(osb2::g_b32250_called && osb2::g_b32250_id == 0x4D02E35u,
          "0x00ae9f50 sets flag 0x4D02E35 when 0x00B3D380 is non-null");
    note_check_u32(osb2::g_publish_value, 0x12345678u,
              "0x00ae9f50 publishes the slot +0x20 result of 0x00A206F0");
    note_check_u32(static_cast<std::uint32_t>(osb2::g_ae8ea0_calls), 1u,
              "0x00ae9f50 resets the tool manager once");
    note_check_u32(static_cast<std::uint32_t>(osb2::g_c35240_calls), 1u,
              "0x00ae9f50 binds the 0x00BA6D80 entry once");
    note_check(s->f_74 == -1, "0x00ae9f50 resets +0x74 to -1");
    note_check_u32(static_cast<std::uint32_t>(osb2::g_ae0930_calls), 1u,
              "0x00ae9f50 releases the trading slot once");
    note_check(g_slot64[0] == 0, "0x00ae9f50 zeroes the byte at *+0x64");
    note_check(s->f_68 == s->f_64, "0x00ae9f50 refreshes +0x68 from +0x64");
}

}  // namespace

int openspore::wave13_w1_core_b08::run_tiers_and_session_model_tests() {
    test_c0ce80();
    test_ae9f50_null_subobject();
    test_ae9f50_c_nonnull_branch();
    test_ae9f50_c_null_branch();
    test_ae9f50_side_effects();
    return 0;
}
