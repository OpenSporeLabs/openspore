// Standalone model test for the 0x0057ac00 reconstruction.
//
// Build (repo instruction form):
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       <this file> editor_0057ac00.cpp -o /tmp/opencode/0057ac00-model
//   /tmp/opencode/0057ac00-model
//
// The ports are stubbed with observable recorders so the invariants proved by
// the disassembly can be asserted.

#include "editor_0057ac00.hpp"

#include <cstdio>
#include <cstring>

namespace openspore {
namespace dispatch_b05 {

std::uint32_t g_015da7ec = 0;
std::uint32_t g_015da7f0 = 0;
std::uint32_t g_015da7f4 = 0;
std::uint32_t g_015da7f8 = 0;
std::uint32_t g_015daa40 = 0;
std::uint32_t g_015daa44 = 0;
std::uint32_t g_015daa48 = 0;
std::uint32_t g_015daa4c = 0;
void* g_015fd918 = nullptr;

namespace {

// --- recorders -------------------------------------------------------------

bool g_editing_disabled = false;
int g_get_bool_calls = 0;
int g_get_key_calls = 0;
std::uint32_t g_get_key_ids[4] = {};
int g_get_key_hit_count = 0;
int g_evaluate_calls = 0;
EditMask0057ac00 g_evaluate_seen{};
std::uint32_t g_evaluate_trailing = 0xffffffffu;
std::int32_t g_rigblock_count = 0;
int g_rigblock_at_calls = 0;
std::int32_t g_rigblock_last_index = -1;
std::uint32_t g_capability_queries = 0;
std::uint32_t g_capability_ids[64] = {};
int g_capability_hit_after = -1;  // rigblock index that yields non-zero
bool g_required_result = true;
bool g_optional_result = true;
int g_required_calls = 0;
int g_optional_calls = 0;
EditMask0057ac00 g_name_refine_in{};

struct FakeRigblock {
    std::uint32_t caps[2];
};

FakeRigblock g_rigblocks[8];

}  // namespace

bool PropertyManager0057ac00_get_bool006a25a0(void* property_manager,
                                              std::uint32_t property_id) {
    (void)property_manager;
    ++g_get_bool_calls;
    if (property_id != kPropGlobalEditingDisabled) return false;
    return g_editing_disabled;
}

bool PropertyList0057ac00_get_key006a1250(const void* prop_list,
                                          std::uint32_t property_id,
                                          void* out_resource_key) {
    if (prop_list == nullptr) return false;
    if (g_get_key_calls < 4) g_get_key_ids[g_get_key_calls] = property_id;
    ++g_get_key_calls;
    // Only the first two lookups (0x7A926123 then 0xF5CBE065) are answered.
    if (g_get_key_hit_count >= 2) return false;
    ++g_get_key_hit_count;
    auto* const key = static_cast<std::uint32_t*>(out_resource_key);
    key[0] = 0x11110000u + static_cast<std::uint32_t>(g_get_key_hit_count);
    key[1] = 0;
    key[2] = 0;
    return true;
}

void Editor0057ac00_collect_local_mask0057a960(const CEditor0057ac00* self,
                                               EditMask0057ac00* out) {
    out->word[0] = out->word[1] = out->word[2] = out->word[3] = 0;
    if (self->field_1cc == nullptr) return;
    out->word[0] = 0x0000000fu;
    out->word[1] = 0x00000080u;
    out->word[2] = 0;
    out->word[3] = 0;
}

EditMask0057ac00* Editor0057ac00_collect_global_mask0057a9e0(
    const CEditor0057ac00* self, EditMask0057ac00* out) {
    (void)self;
    out->word[0] = 0x00000001u;
    out->word[1] = 0x00000020u;
    out->word[2] = 0;
    out->word[3] = 0;
    return out;
}

void CapabilityEvaluator0057ac00_evaluate004f3de0(
    EditMask0057ac00* out, EditHistoryRecord0057ac00* record,
    EditMask0057ac00 requested_mask_by_value, bool early_out) {
    (void)record;
    (void)early_out;
    *out = requested_mask_by_value;
    out->word[0] &= ~0x400u;  // 0x400 is decided locally, never granted here
}

void EditHistoryRecord0057ac00_evaluate004bac30(
    EditHistoryRecord0057ac00* record, EditMask0057ac00* out,
    EditMask0057ac00 requested_mask_by_value, std::uint32_t trailing) {
    ++g_evaluate_calls;
    g_evaluate_seen = requested_mask_by_value;
    g_evaluate_trailing = trailing;
    CapabilityEvaluator0057ac00_evaluate004f3de0(out, record,
                                                 requested_mask_by_value, false);
}

std::uint32_t Rigblock0057ac00_find_capability_value00435b60(
    const void* rigblock, std::uint32_t capability_id) {
    if (g_capability_queries < 64) g_capability_ids[g_capability_queries] = capability_id;
    ++g_capability_queries;
    if (rigblock == nullptr) return 0;
    const auto* const r = static_cast<const FakeRigblock*>(rigblock);
    if (capability_id == kModelCapabilityMouth) return r->caps[0];
    if (capability_id == kModelCapabilityCellMouth) return r->caps[1];
    return 0;
}

std::int32_t EditorModel0057ac00_rigblock_count004accf0(
    const void* editor_model) {
    (void)editor_model;
    return g_rigblock_count;
}

void* EditorModel0057ac00_rigblock_at004accb0(const void* editor_model,
                                              std::int32_t index) {
    (void)editor_model;
    ++g_rigblock_at_calls;
    g_rigblock_last_index = index;
    if (index < 0 || index >= 8) return nullptr;
    return &g_rigblocks[index];
}

bool EditHistoryRecord0057ac00_check_required004efb20(
    EditHistoryRecord0057ac00* record, std::uint32_t key_instance_id,
    std::uint32_t* in_out_mask) {
    (void)record;
    (void)key_instance_id;
    ++g_required_calls;
    *in_out_mask |= 0xdeadbeefu;  // the callee really does mutate cEditor+0x48
    return g_required_result;
}

bool EditHistoryRecord0057ac00_check_optional004ef880(
    EditHistoryRecord0057ac00* record, std::uint32_t key_instance_id,
    std::uint32_t* in_out_mask) {
    (void)record;
    (void)key_instance_id;
    ++g_optional_calls;
    *in_out_mask &= 0x00000000u;
    return g_optional_result;
}

std::uint32_t NameTable0057ac00_refine004edf40(const char16_t* name,
                                               EditMask0057ac00* in_out_mask) {
    (void)name;
    g_name_refine_in = *in_out_mask;
    in_out_mask->word[0] |= 0x10u;  // forces bit 0x10 in the observed build path
    return 0;
}

namespace {

void ResetCounters() {
    g_get_bool_calls = 0;
    g_get_key_calls = 0;
    g_get_key_hit_count = 0;
    g_evaluate_calls = 0;
    g_evaluate_trailing = 0xffffffffu;
    g_rigblock_at_calls = 0;
    g_rigblock_last_index = -1;
    g_capability_queries = 0;
    g_capability_hit_after = -1;
    g_required_calls = 0;
    g_optional_calls = 0;
    g_required_result = true;
    g_optional_result = true;
    g_rigblock_count = 0;
    std::memset(g_rigblocks, 0, sizeof(g_rigblocks));
    g_editing_disabled = false;
}

int RunModelTest() {
    CEditor0057ac00 editor{};
    EditMask0057ac00 out{};
    EditHistoryRecord0057ac00 record{};

    // --- 1. the global kill switch short-circuits everything ---------------
    ResetCounters();
    g_editing_disabled = true;
    editor.field_1cc = reinterpret_cast<void*>(0x1000);
    editor.field_24_prop_list = reinterpret_cast<void*>(0x2000);
    editor.field_2a8_save_extension = kAssetTypeCreature;
    out.word[0] = out.word[1] = out.word[2] = out.word[3] = 0xffffffffu;
    EditMask0057ac00* const r1 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r1 != &out) return 1;             // EAX is the same pointer as arg1
    if (out.word[0] != 0 || out.word[1] != 0 || out.word[2] != 0 ||
        out.word[3] != 0) {
        return 1;                          // all four dwords zeroed
    }
    if (g_evaluate_calls != 0) return 1;   // the record is never consulted
    if (g_rigblock_at_calls != 0) return 1;
    if (g_get_key_calls != 0) return 1;

    // --- 2. a plain, non-creature, non-cell editor -------------------------
    ResetCounters();
    editor.field_1cc = reinterpret_cast<void*>(0x1000);
    editor.field_24_prop_list = reinterpret_cast<void*>(0x2000);
    editor.field_2a8_save_extension = 0x12345678u;  // neither crt nor cll
    editor.field_4b1 = 0;
    editor.field_4b2 = 0;
    EditMask0057ac00* const r2 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r2 != &out) return 1;
    if (g_evaluate_calls != 1) return 1;
    if (g_evaluate_trailing != 0) return 1;   // PUSH 0x0 at 0x0057ac6f
    // A|B word0 = 0x0f | 0x01 = 0x0f, then bit 0x400 is NOT set for a non-creature.
    if (g_evaluate_seen.word[0] != 0x0fu) return 1;
    if (g_evaluate_seen.word[1] != 0xa0u) return 1;  // 0x80 | 0x20
    if (g_rigblock_at_calls != 0) return 1;  // mouth scan skipped
    // Both key lookups answered, both predicates true -> bits cleared.
    if (g_get_key_ids[0] != kPropertyIdMaskBit40000) return 1;
    if (g_get_key_ids[1] != kPropertyIdMaskBit20) return 1;
    if (g_required_calls != 1 || g_optional_calls != 1) return 1;
    // 0x4B1 == 0 so bit 0x800 must be CLEAR (0x0057adc1).
    if ((out.word[0] & 0x800u) != 0) return 1;
    // 0x004edf40 forces bit 0x10; bit 0x400 must be absent.
    if ((out.word[0] & 0x10u) == 0) return 1;
    if ((out.word[0] & 0x400u) != 0) return 1;
    // Both helpers really do write through &cEditor::field_48: 0x004efb20 ORs
    // 0xdeadbeef into it, then 0x004ef880 clears it, so the net effect is zero.
    if (editor.field_48 != 0u) return 1;

    // --- 3. a creature with a mouth rigblock clears bit 0x400 --------------
    ResetCounters();
    editor.field_1cc = nullptr;  // A is all zero
    editor.field_24_prop_list = nullptr;  // both GetKey calls short-circuit
    editor.field_2a8_save_extension = kAssetTypeCreature;
    editor.field_4b1 = 1;
    editor.field_4b2 = 0;  // => bit 0x800 SET
    g_rigblock_count = 3;
    g_rigblocks[1].caps[0] = 0x5u;  // kModelCapabilityMouth hit on index 1
    EditMask0057ac00* const r3 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r3 != &out) return 1;
    // Rigblock 0 misses both capabilities (2 queries), rigblock 1 hits on the
    // very first query, so the loop stops after 3 queries total.
    if (g_capability_queries != 3) return 1;
    if (g_capability_ids[0] != kModelCapabilityMouth) return 1;
    if (g_capability_ids[1] != kModelCapabilityCellMouth) return 1;
    if (g_capability_ids[2] != kModelCapabilityMouth) return 1;
    if (g_rigblock_last_index != 1) return 1;     // stopped on index 1
    if ((out.word[0] & 0x400u) != 0) return 1;   // AND 0xfffffbff
    if ((out.word[0] & 0x800u) == 0) return 1;   // 0x4B1 set, 0x4B2 clear
    if (g_get_key_calls != 0) return 1;          // no prop list -> no GetKey
    if ((out.word[0] & 0x40000u) != 0) return 1;  // bit cleared
    if ((out.word[0] & 0x20u) != 0) return 1;      // bit cleared

    // --- 4. a creature with no mouth anywhere sets bit 0x400 ---------------
    ResetCounters();
    editor.field_1cc = nullptr;
    editor.field_24_prop_list = nullptr;
    editor.field_2a8_save_extension = kAssetTypeCell;
    editor.field_4b1 = 1;
    editor.field_4b2 = 1;  // => bit 0x800 CLEAR
    g_rigblock_count = 2;
    EditMask0057ac00* const r4 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r4 != &out) return 1;
    if (g_capability_queries != 4) return 1;  // 2 rigblocks x 2 capabilities
    if ((out.word[0] & 0x400u) == 0) return 1;  // OR 0x400
    if ((out.word[0] & 0x800u) != 0) return 1;  // AND 0xfffff7ff

    // --- 5. an empty rigblock list still sets bit 0x400 (0x0057acb2 JLE) ---
    ResetCounters();
    editor.field_1cc = nullptr;
    editor.field_24_prop_list = nullptr;
    editor.field_2a8_save_extension = kAssetTypeCreature;
    g_rigblock_count = 0;
    EditMask0057ac00* const r5 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r5 != &out) return 1;
    if (g_rigblock_at_calls != 0) return 1;
    if ((out.word[0] & 0x400u) == 0) return 1;

    // --- 6. failing predicates set bits 0x40000 and 0x20 -------------------
    ResetCounters();
    editor.field_1cc = nullptr;
    editor.field_24_prop_list = reinterpret_cast<void*>(0x2000);
    editor.field_2a8_save_extension = 0x12345678u;
    g_required_result = false;
    g_optional_result = false;
    EditMask0057ac00* const r6 =
        Editor_0057ac00_ComputeGrantedEditMask(&editor, &out, &record, u"eye", 1);
    if (r6 != &out) return 1;
    if ((out.word[0] & 0x40000u) == 0) return 1;  // OR 0x40000
    if ((out.word[0] & 0x20u) == 0) return 1;    // OR 0x20

    return 0;
}

}  // namespace
}  // namespace dispatch_b05
}  // namespace openspore

int main() {
    if (openspore::dispatch_b05::RunModelTest() != 0) {
        std::printf("0057ac00 model test FAILED\n");
        return 1;
    }
    std::printf("0057ac00 model test OK\n");
    return 0;
}
