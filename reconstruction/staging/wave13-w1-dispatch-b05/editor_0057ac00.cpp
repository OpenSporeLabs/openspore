// Clean-room reconstruction of SporeApp.exe 0x0057ac00.
//
// 166 instructions, 0x0057ac00..0x0057ae01, 516 bytes. Instruction addresses in
// the comments are the proof for every statement below. Unresolved callees are
// declared as ports in the header and are never given invented bodies.

#include "editor_0057ac00.hpp"

namespace openspore {
namespace dispatch_b05 {

namespace {

// 0x0057ad08..0x0057ad10 zero three dwords, i.e. a 12-byte ResourceKey
// (instanceID, typeID, groupID) whose groupID default of Global is written as
// a plain zero.
struct ResourceKey0057ac00 {
    std::uint32_t instance_id;
    std::uint32_t type_id;
    std::uint32_t group_id;
};

}  // namespace

extern "C" EditMask0057ac00* Editor_0057ac00_ComputeGrantedEditMask(
    CEditor0057ac00* self, EditMask0057ac00* out,
    EditHistoryRecord0057ac00* record, const char16_t* part_name,
    std::uint32_t early_out_flag) {
    (void)early_out_flag;  // arg4 is popped by RET 0x10 but never read.

    // 0x0057ac09: MOV ECX,dword ptr [0x015fd918]
    // 0x0057ac0f: PUSH 0x55d7ca1
    // 0x0057ac14: CALL 0x006a25a0
    // 0x0057ac19: TEST AL,AL
    // 0x0057ac1b: JZ 0x0057ac38
    // Global kill switch: when the property is set the whole 16-byte result is
    // zeroed (0x0057ac21 XOR ECX,ECX then four MOV dword ptr [EAX+k],ECX) and
    // the function returns immediately, BEFORE the record is ever consulted.
    if (PropertyManager0057ac00_get_bool006a25a0(
            g_015fd918, kPropGlobalEditingDisabled)) {
        out->word[0] = 0;
        out->word[1] = 0;
        out->word[2] = 0;
        out->word[3] = 0;
        return out;  // 0x0057ac35: RET 0x10
    }

    // 0x0057ac38: LEA EAX,[ESP + 0x38] / PUSH EAX / MOV ECX,ESI
    // 0x0057ac3f: CALL 0x0057a960        -> mask A at [ESP+0x38..0x44]
    // 0x0057ac44: LEA ECX,[ESP + 0x48] / PUSH ECX / MOV ECX,ESI
    // 0x0057ac4b: CALL 0x0057a9e0        -> mask B at [ESP+0x48..0x54]
    EditMask0057ac00 mask_a{};
    EditMask0057ac00 mask_b{};
    Editor0057ac00_collect_local_mask0057a960(self, &mask_a);
    Editor0057ac00_collect_global_mask0057a9e0(self, &mask_b);

    // 0x0057ac50..0x0057ac68: four dword ORs of A and B, in order.
    // 0x0057ac6b: MOV EBX,dword ptr [ESP + 0x60]  -> arg2, the record
    EditMask0057ac00 requested{};
    requested.word[0] = mask_a.word[0] | mask_b.word[0];
    requested.word[1] = mask_a.word[1] | mask_b.word[1];
    requested.word[2] = mask_a.word[2] | mask_b.word[2];
    requested.word[3] = mask_a.word[3] | mask_b.word[3];

    // 0x0057ac6f: PUSH 0x0  (the trailing dword)
    // 0x0057ac71: SUB ESP,0x10  (the 16-byte struct is passed BY VALUE)
    // 0x0057ac74..0x0057ac85: the four ORs are copied into that struct
    // 0x0057ac7b: LEA EDX,[ESP + 0x3c] -> &local_30, the destination mask
    // 0x0057ac82: PUSH EDX
    // 0x0057ac88: CALL 0x004bac30 -> writes the granted mask into local_30
    EditMask0057ac00 granted{};
    EditHistoryRecord0057ac00_evaluate004bac30(record, &granted, requested, 0);

    // 0x0057ac8d: MOV EAX,dword ptr [ESI + 0x2a8]  -> mSaveExtension
    // 0x0057ac93: CMP EAX,0x2b978c46 / JZ
    // 0x0057ac9a: CMP EAX,0x3d97a8e4 / JNZ 0x0057ad03
    // Only creatures (crt) and cells (cll) run the mouth scan.
    if (self->field_2a8_save_extension == kAssetTypeCreature ||
        self->field_2a8_save_extension == kAssetTypeCell) {
        // 0x0057aca1: MOV ECX,dword ptr [ESI + 0x98] -> mpEditorModel
        // 0x0057aca7: XOR EDI,EDI                    -> rigblock index
        // 0x0057aca9: CALL 0x004accf0                 -> rigblock count
        // 0x0057acb0: TEST EBP,EBP / JLE 0x0057acf1    -> empty list falls
        //                                                through to "set the bit"
        const std::int32_t rigblock_count =
            EditorModel0057ac00_rigblock_count004accf0(
                self->field_98_editor_model);

        for (std::int32_t i = 0; i < rigblock_count; ++i) {
            // 0x0057acb4..0x0057acc7: GetRigblock(i) then
            // FUN_00435b60(rigblock, 0xb00f0fec)
            void* const rigblock = EditorModel0057ac00_rigblock_at004accb0(
                self->field_98_editor_model, i);
            const std::uint32_t mouth =
                Rigblock0057ac00_find_capability_value00435b60(
                    rigblock, kModelCapabilityMouth);
            if (mouth != 0) {
                // 0x0057acfb: AND dword ptr [ESP + 0x28],0xfffffbff
                granted.word[0] &= ~0x400u;
                goto capability_scan_done;
            }

            // 0x0057acd0..0x0057ace3: the same for 0x11b79301 (cell mouth)
            const std::uint32_t cell_mouth =
                Rigblock0057ac00_find_capability_value00435b60(
                    rigblock, kModelCapabilityCellMouth);
            if (cell_mouth != 0) {
                granted.word[0] &= ~0x400u;
                goto capability_scan_done;
            }
        }
        // 0x0057acf1: OR dword ptr [ESP + 0x28],0x400
        // Reached when the model has no rigblock at all, or when no rigblock
        // carries either mouth capability: the "mouthless" bit is SET.
        granted.word[0] |= 0x400u;
    }

capability_scan_done:
    // 0x0057ad03: MOV EAX,dword ptr [ESI + 0x24]  -> mpPropList
    // 0x0057ad06: XOR ECX,ECX  -> zero the 12-byte key
    // 0x0057ad14: CMP EAX,ECX / JZ 0x0057ad4f
    // 0x0057ad1c: PUSH &key / PUSH 0x7a926123 / PUSH EAX
    // 0x0057ad23: CALL 0x006a1250
    // 0x0057ad2b: TEST AL,AL / JZ 0x0057ad4f
    {
        ResourceKey0057ac00 key_required = {0, 0, 0};
        if (self->field_24_prop_list != nullptr &&
            PropertyList0057ac00_get_key006a1250(
                self->field_24_prop_list, kPropertyIdMaskBit40000,
                &key_required)) {
            // 0x0057ad2f..0x0057ad39: pass the key's instanceID plus
            // &cEditor::field_48, which the callee read-modify-writes.
            // 0x0057ad41: TEST AL,AL / JNZ 0x0057ad4f -> satisfied, clear the bit
            // 0x0057ad45: OR  dword ptr [ESP + 0x28],0x40000
            const bool satisfied =
                EditHistoryRecord0057ac00_check_required004efb20(
                    record, key_required.instance_id, &self->field_48);
            if (!satisfied) {
                granted.word[0] |= 0x40000u;
            } else {
                granted.word[0] &= ~0x40000u;
            }
        } else {
            // 0x0057ad4f: AND dword ptr [ESP + 0x28],0xfffbffff
            granted.word[0] &= ~0x40000u;
        }
    }

    // 0x0057ad57..0x0057ada0: the identical shape for bit 0x20 with property
    // 0xf5cbe065 and callee 0x004ef880. All three failure paths (no prop list,
    // key lookup failed, predicate returned non-zero) reach 0x0057ada0 and CLEAR
    // the bit, so the bit is never left stale.
    {
        ResourceKey0057ac00 key_optional = {0, 0, 0};
        if (self->field_24_prop_list != nullptr &&
            PropertyList0057ac00_get_key006a1250(
                self->field_24_prop_list, kPropertyIdMaskBit20,
                &key_optional)) {
            const bool allowed =
                EditHistoryRecord0057ac00_check_optional004ef880(
                    record, key_optional.instance_id, &self->field_48);
            if (!allowed) {
                granted.word[0] |= 0x20u;
            } else {
                granted.word[0] &= ~0x20u;
            }
        } else {
            granted.word[0] &= ~0x20u;
        }
    }

    // 0x0057ada5: CMP byte ptr [ESI + 0x4b1],0x0 / JZ 0x0057adc1
    // 0x0057adae: CMP byte ptr [ESI + 0x4b2],0x0 / JNZ 0x0057adc1
    // 0x0057adb7: OR  dword ptr [ESP + 0x28],0x800
    // 0x0057adc1: AND dword ptr [ESP + 0x28],0xfffff7ff
    // Polarity: the bit is set only when 0x4B1 is non-zero AND 0x4B2 is zero.
    if (self->field_4b1 != 0 && self->field_4b2 == 0) {
        granted.word[0] |= 0x800u;
    } else {
        granted.word[0] &= ~0x800u;
    }

    // 0x0057adc9: MOV EDX,dword ptr [ESP + 0x64]   -> arg3, the part name
    // 0x0057adcd: LEA ECX,[ESP + 0x28]            -> &granted.word[0]
    // 0x0057add3: CALL 0x004edf40
    // The return value is never read; only the in/out mask effect matters.
    (void)NameTable0057ac00_refine004edf40(part_name, &granted);

    // 0x0057add8..0x0057adfa: copy the four dwords to the caller's buffer in
    // order word0, word1, word2, word3, and 0x0057ade8..0x0057adfd leave EAX
    // pointing at arg1, which is what the six callers dereference immediately.
    out->word[0] = granted.word[0];
    out->word[1] = granted.word[1];
    out->word[2] = granted.word[2];
    out->word[3] = granted.word[3];
    return out;  // 0x0057ae01: RET 0x10
}

}  // namespace dispatch_b05
}  // namespace openspore
