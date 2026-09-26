// Wave-13 worker batch b02 -- target 0x00b9aa10
// Reconstructed from the live disassembly of 0x00b9aa10..0x00b9b088
// (430 instructions). Every statement is anchored to an instruction address;
// see reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json.
//
// Notes on two decompiler artefacts that the disassembly refutes:
//  * the inner countdown at [ESP+0x1c] is an INTEGER (SUB dword ptr
//    [ESP+0x1c],0x1 at 0x00b9b047), not the float the pseudocode shows;
//  * the unsigned DIV at 0x00b9adb4 keeps only the remainder in EDX, which is
//    stored at 0x00b9adcb; the quotient in EAX is dead, overwritten at
//    0x00b9adb6.

#include "b9aa10_place_species_on_cube_map.hpp"

namespace openspore::wave13::b02 {
namespace {

// The four constants that reach App::Property::GetBool at 0x00407190 and the
// three that reach App::Property::GetArrayUInt32 at 0x006a0840, all applied to
// record->prop_list at +0x43c.
constexpr std::uint32_t kPropRadiusScale = 0x4934caca;   // 0x00b9ab6c
constexpr std::uint32_t kPropAcceptVector = 0x1ee4cafd;  // 0x00b9abad
constexpr std::uint32_t kPropBucketVector = 0x6b152f47;  // 0x00b9ac41
constexpr std::uint32_t kPropFlagA = 0x80cd38c6;         // 0x00b9accb -> bit 0x10
constexpr std::uint32_t kPropFlagB = 0x3a509d24;         // 0x00b9ad01 -> bit 0x20
constexpr std::uint32_t kPropFlagC = 0x835025da;         // 0x00b9ad17 -> bit 0x40
constexpr std::uint32_t kPropChildArray = 0xdb9bfc2c;    // 0x00b9afeb

// 0x00b9aa42: the calling mode id that suppresses the sorted-table bookkeeping.
constexpr std::uint32_t kModeIdCreatureStage = 0x01654c01;

// 0x00b9abc6 and 0x00b9ac5a index a 3-float Vector3 with a runtime component
// selector read from [0x0156c060]. Modelled as a bounds-checked selector
// because the observed value is a runtime global whose range is unproven.
float component_at(const Vector3& v, std::uint32_t index) {
    return index == 0 ? v.x : (index == 1 ? v.y : v.z);
}

}  // namespace

void FUN_00b9aa10_reconstruct(Vector3* out_pos, const std::uint32_t* ids, std::uint32_t count,
                              std::uint32_t extra);

// 0x00b9aa10, __cdecl, four stack arguments, void return.
//   arg1 [EBP+0x08] : Vector3* used as both an input up-direction and the output
//                     position; 0x00b9addf loads it, 0x00b9ae41 pushes it.
//   arg2 [EBP+0x0c] : base of an array of 32-bit ids; 0x00b9aab1/0x00b9aab4
//                     index it with EAX*4.
//   arg3 [EBP+0x10] : element count; 0x00b9aaa8 and 0x00b9b05f test it.
//   arg4 [EBP+0x14] : opaque extra value, forwarded at 0x00b9af94.
void FUN_00b9aa10_reconstruct(Vector3* out_pos, const std::uint32_t* ids, std::uint32_t count,
                              std::uint32_t extra) {
    // 0x00b9aa1f/0x00b9aa24: two singleton getters; the first result is dropped.
    global_0167eae0_get_port();
    GameInputManagerPort* const input = game_input_manager_get_port();

    // 0x00b9aa2b..0x00b9aa38: the species manager, then one call on it with the
    // pointer to its own +0xa4 sub-object.
    SpeciesManagerPort* const species = species_manager_get_port();
    species_manager_prepare_0a4_port(species);

    // 0x00b9aa3d/0x00b9aa42/0x00b9aa47: bool is_creature_stage =
    //     (current_calling_mode_id() == 0x01654c01). Stored at [ESP+0x13] and
    //     read back at 0x00b9aca2 and 0x00b9ace8.
    const bool is_creature_stage = (current_calling_mode_id_port() == kModeIdCreatureStage);

    // 0x00b9aa4c/0x00b9aa51/0x00b9aa53: the entire body is gated on this
    // singleton being non-null.
    if (global_015fcc74_get_port() == nullptr) {
        return;
    }

    // 0x00b9aa59..0x00b9aa92: a two-pointer out-parameter pair is built on the
    // stack and grown to one element by 0x004cd3c0, then 0x00b9aa97 samples the
    // input manager's delta.
    std::uint32_t ctx_storage[6] = {};
    std::uint32_t* ctx_begin = ctx_storage;
    std::uint32_t* ctx_end = ctx_storage;
    reserve_dword_vector_port(ctx_begin, ctx_end, 1);
    const float delta = input_manager_delta_port(input);

    for (std::uint32_t i = 0; i < count; ++i) {  // 0x00b9aaa8..0x00b9b062
        // 0x00b9aab1/0x00b9aab4: ids[i].
        const std::uint32_t id = ids[i];

        // 0x00b9aabc/0x00b9aac0: resolve the id, with the trailing flag zero.
        SpeciesPlacementRecord* const record = species_manager_resolve_port(species, id, 0);
        if (record == nullptr) {
            continue;  // 0x00b9aac7/0x00b9aac9
        }

        // 0x00b9aacf..0x00b9aae7: first selection attempt, five arguments
        // (out_context, record, 1, 0, 0). A result below 1 triggers the second
        // attempt at 0x00b9aae9..0x00b9ab06, which differs only in the last
        // argument being 1.
        if (species_manager_select_port(species, record, ctx_begin, 1, 0, 0) < 1) {
            if (species_manager_select_port(species, record, ctx_begin, 1, 0, 1) < 1) {
                continue;  // 0x00b9ab06 JLE
            }
        }

        // 0x00b9ab0c/0x00b9ab1b/0x00b9ab2a..0x00b9ab54: uniform value in
        // [f_300, f_304], clamped to the same interval, then a double compare
        // pair that leaves the clamped value in ST0.
        const float lo = record->f_300;
        const float hi = record->f_304;
        const float clamped = lcg_random_unit_port(&g_lcg_state_a) * (hi - lo) + lo;
        const float kept = (clamped < hi && clamped > lo) ? clamped : ((clamped > lo) ? clamped : lo);
        // 0x00b9ab58: CVTSS2SI, round toward zero, then MOV EDI,EAX.
        std::int32_t placements = static_cast<std::int32_t>(kept);

        // 0x00b9ab66/0x00b9ab6c/0x00b9ab76: a probability with default 1.0f.
        const float accept = property_get_float_port(record->prop_list, kPropRadiusScale, 1.0f);

        // 0x00b9ab7f..0x00b9abbb: a 3-vector with default (1,1,1) read live at
        // 0x0156bfc4. 0x00b9abc0/0x00b9abc6: the component selected by
        // [0x0156c060] is scaled by the probability.
        Vector3 accept_vec{};
        property_get_vector3_port(&accept_vec, record->prop_list, kPropAcceptVector,
                                  g_default_vector_1ee4cafd[0], g_default_vector_1ee4cafd[1],
                                  g_default_vector_1ee4cafd[2]);
        const float threshold = component_at(accept_vec, g_vector_component_index_0156c060) * accept;

        // 0x00b9abd4/0x00b9abdd: the second draw, discarded into [ESP+0x1c].
        const float roll = lcg_random_unit_port(&g_lcg_state_a);

        // 0x00b9abe6/0x00b9abf4/0x00b9abf9: COMISS, JC, so the gate passes only
        // when roll <= threshold. The placement count must be positive too.
        if (placements <= 0 || !(roll <= threshold)) {
            continue;
        }

        // 0x00b9abff/0x00b9ac0c/0x00b9ac10: the global serial, pre-incremented.
        std::uint32_t serial = ++g_placement_serial_016895a4;

        // 0x00b9ac1b..0x00b9ac4f: a second 3-vector, default from
        // 0x01688890/94/98, all zero in the file image.
        Vector3 bucket_vec{};
        property_get_vector3_port(&bucket_vec, record->prop_list, kPropBucketVector,
                                  g_default_vector_6b152f47[0], g_default_vector_6b152f47[1],
                                  g_default_vector_6b152f47[2]);

        // 0x00b9ac54/0x00b9ac6c: the chosen component, truncated to an integer.
        const std::int32_t bucket_count =
            static_cast<std::int32_t>(component_at(bucket_vec, g_vector_component_index_0156c060));

        // 0x00b9ac74..0x00b9ac84: when the bucket count is positive the serial
        // is wrapped into 1..bucket_count by an unsigned DIV.
        if (bucket_count > 0) {
            serial = (g_placement_serial_016895a4 % static_cast<std::uint32_t>(bucket_count)) + 1u;
        }

        // 0x00b9ac88..0x00b9aca6: has_ring is (end - begin) >> 2 > 1, i.e. more
        // than one element in the ring array.
        const std::uint32_t ring_len =
            static_cast<std::uint32_t>((record->ring_end - record->ring_begin) >> 2);
        const bool has_ring = ring_len > 1u;

        // 0x00b9ac94/0x00b9acad and 0x00b9acc3/0x00b9acd0: two record floats,
        // each offset by the input-manager delta.
        const float offset_2e0 = record->f_2e0 + delta;
        const float offset_2e4 = record->f_2e4 + delta;

        // 0x00b9ace3/0x00b9ace8/0x00b9acec: three flag bytes, defaulted to
        // false, true (mirroring is_creature_stage) and false.
        bool flag_a = false;
        bool flag_b = is_creature_stage;
        bool flag_c = false;
        // 0x00b9acb1: the address of flag_a is pushed as the out-parameter.
        property_get_bool_port(record->prop_list, kPropFlagA, &flag_a);
        property_get_bool_port(record->prop_list, kPropFlagB, &flag_b);
        property_get_bool_port(record->prop_list, kPropFlagC, &flag_c);

        // 0x00b9ad25..0x00b9ad4b: the three booleans are packed into bit 4, 5
        // and 6 of a dword that starts at zero.
        std::uint32_t flag_mask = 0;
        if (flag_a) {
            flag_mask |= 0x10u;
        }
        if (flag_b) {
            flag_mask |= 0x20u;
        }
        if (flag_c) {
            flag_mask |= 0x40u;
        }

        // 0x00b9ad50..0x00b9ad60: the placement count, as an integer.
        if (placements <= 0) {
            continue;
        }

        // 0x00b9ad62/0x00b9ad66: the ring index is reloaded to the count base
        // at the top of every iteration, so it restarts at 0 each time.
        for (std::uint32_t ring_index = 0;; ++ring_index) {
            // 0x00b9ad6d..0x00b9ad9e: the ring pair. When has_ring is false the
            // two constants 100.0f (0x013ec4d0) and 1000.0f (0x013ec5b4) are
            // used instead. The second read is at +4, i.e. the next element.
            float radius_a;
            float radius_b;
            if (has_ring) {
                radius_a = record->ring_begin[ring_index];
                radius_b = record->ring_begin[ring_index + 1];
            } else {
                radius_a = g_ring_fallback_a_013ec4d0;
                radius_b = g_ring_fallback_b_013ec5b4;
            }

            // 0x00b9ad9e..0x00b9adcb: the wrap index. The DIV at 0x00b9adb4 is
            // 32-bit unsigned with EDX zeroed; only the remainder survives.
            const std::uint32_t ring_span =
                static_cast<std::uint32_t>((record->ring_end - record->ring_begin) >> 2);
            const std::uint32_t wrap_index = (ring_index + 2u) % ring_span;

            // 0x00b9adbe/0x00b9add6..0x00b9ae43: the free-cell search. Two
            // explicit zeros are pushed at 0x00b9adba and 0x00b9adbc, the
            // 0x28-byte float block is built by eight FLD/FSTP pairs
            // 0x00b9ade2..0x00b9ae3d, and 0x00b9ae48 cleans 0x44 bytes.
            const bool found = cube_map_find_free_direction_port(
                out_pos, out_pos, record->u8_334, radius_a, radius_b, record->f_2d4, record->f_2d8,
                record->f_2dc, offset_2e0, offset_2e4, record->f_2e8, record->f_2ec, wrap_index,
                flag_mask, ctx_begin, 0, 0);

            if (found) {
                // 0x00b9ae53/0x00b9ae58: the sorted-table bookkeeping is
                // skipped entirely in the creature-stage case.
                if (!is_creature_stage) {
                    // 0x00b9ae5e..0x00b9ae6c: the id is resolved a second time,
                    // with the trailing flag zero, and +0x14 is read from it.
                    const SpeciesPlacementRecord* const again =
                        species_manager_resolve_port(species, id, 0);
                    const std::uint32_t tag = (again != nullptr) ? again->field_14 : 0u;

                    // 0x00b9ae71..0x00b9ae9f: a two-dword key {serial, tag} is
                    // lower-bounded in the 16-byte-record table at
                    // 0x0168890c..0x01688910 with mode byte 0x01688920.
                    std::uint32_t key[2] = {serial, tag};
                    std::uint32_t range[2] = {0, 0};
                    sorted_range_lower_bound_port(range, g_sorted_table_begin_0168890c,
                                                 g_sorted_table_end_01688910, key,
                                                 g_sorted_table_mode_01688920);

                    // 0x00b9aea4..0x00b9aec3: the branch is taken when the
                    // lower bound moved (key already present) or when it still
                    // equals the table begin, i.e. the table is empty.
                    const bool insert_here =
                        (range[0] == g_sorted_table_end_01688910) ||
                        (range[0] == g_sorted_table_begin_0168890c);

                    if (insert_here) {
                        // 0x00b9aec3..0x00b9aed9: an empty {0, tag} range is
                        // built and its element count taken.
                        std::uint32_t insert_range[6] = {0, 0, 0, 0, 0, 0};
                        insert_range[0] = 0;
                        insert_range[2] = tag;
                        const std::int32_t found_count = sorted_range_count_port(insert_range);

                        // 0x00b9aee0/0x00b9aee2: a non-positive count skips the
                        // whole block.
                        if (found_count > 0) {
                            // 0x00b9aee8/0x00b9aefa: the range's first element.
                            std::uint32_t elem[2] = {0, 0};
                            sorted_range_begin_port(elem, insert_range);

                            // 0x00b9aeff..0x00b9af0d: a 0x41c64e6d LCG step
                            // gives an index in [0, found_count), and the
                            // element is 16 bytes.
                            const std::uint32_t slot =
                                lcg_bounded_port(&g_lcg_state_b,
                                                 static_cast<std::uint32_t>(found_count)) * 0x10u;

                            // 0x00b9af14..0x00b9af55: four dwords are copied
                            // from the chosen element (offsets +8..+0x14) into
                            // the caller's out block, then serial and tag are
                            // stored at +0x10/+0x14 of that block, and
                            // 0x00b9af5c takes the range's end.
                            std::uint32_t payload[6] = {0, 0, 0, 0, 0, 0};
                            payload[0] = slot;  // stands for elem + 8
                            payload[4] = serial;
                            payload[5] = tag;
                            sorted_range_end_port(payload, insert_range);
                        }
                    }
                }

                // 0x00b9af65..0x00b9af84: a uniform random in
                // [f_2f0, f_2f4] is computed and stored to a stack slot that is
                // never read again. Preserved because it consumes two draws
                // from the LCG, which shifts every later draw.
                random_lerp_port(record->f_2f0, record->f_2f4);

                // 0x00b9af87..0x00b9af9d: the commit, with the serial and the
                // caller's fourth argument.
                commit_placement_port(out_pos, record, id, serial, extra);

                // 0x00b9afa2..0x00b9afcc: three radii painted as flag bits.
                cube_map_paint_flags_port(out_pos, record->f_308, record->f_30c, record->f_310);

                // 0x00b9afd1..0x00b9aff1: an optional uint32 array property.
                std::uint32_t child_count = 0;
                std::uint32_t* child_data = nullptr;
                if (property_get_array_u32_port(record->prop_list, kPropChildArray, &child_count,
                                                &child_data) &&
                    child_count > 0) {
                    // 0x00b9b005..0x00b9b016: record->field_10 is forwarded.
                    place_from_property_array_port(out_pos, child_data, child_count,
                                                    static_cast<std::uint32_t>(
                                                        reinterpret_cast<std::uintptr_t>(record->field_10)),
                                                    0);
                }

                // 0x00b9b01e..0x00b9b044: the child-id list recursion, with the
                // element count computed as (end - begin) >> 2.
                const std::uint32_t kids =
                    static_cast<std::uint32_t>((record->child_ids_end - record->child_ids) >> 2);
                if (kids > 0) {
                    FUN_00b9aa10_reconstruct(out_pos, record->child_ids, kids, id);
                }
            }

            // 0x00b9b047/0x00b9b04c: the integer countdown, looping back to
            // 0x00b9ad62 which reloads the ring index.
            if (--placements == 0) {
                break;
            }
        }
    }

    // 0x00b9b068..0x00b9b07f: the out-context block is freed only when the
    // pointer is non-null AND the dword four bytes below it is non-zero, which
    // is a length/cookie check.
    if (ctx_begin != nullptr && *reinterpret_cast<const std::int32_t*>(
                                    reinterpret_cast<const std::uint8_t*>(ctx_begin) - 4) != 0) {
        heap_free_port(ctx_begin);
    }
}

}  // namespace openspore::wave13::b02
