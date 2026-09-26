#include "00573d70_set_primary_part.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

namespace {
// Observed immediates. 0x50a993c is the type id passed to vtable slot +0x0c and
// compared against vtable slot +0x10's return; no SDK name for it was found, so
// it stays a bare constant. 0xd2cfe2ad is the marker handed to 0x00435ed0.
constexpr std::uint32_t kTypeId_50a993c = 0x50a993cu;
constexpr std::uint32_t kMarker_d2cfe2ad = 0xd2cfe2adu;
}  // namespace

// 0x00573d70. Frame is register-only: PUSH EBX / MOV EBX,[ESP+8] / PUSH ESI /
// PUSH ESI-from-ECX / PUSH EDI, plus one PUSH EBP at 0x00573e06 that the
// epilogue at 0x00573f12 pops. EBX carries `part` and is reloaded from
// [ESP+0x14] at 0x00573e5d, which is the incoming stack word 4 slots down.
//
// Guard chain, in order:
//  0x00573d85  part==0 and flag_0140==0            -> flag_0140 = 1
//  0x00573d98  part != field_0e4, or field_0e4 non-null and its +0x1c dword
//              non-zero                            -> continue, else exit
//  0x00573dcf  field_0f4 non-null and != part      -> flag_0140 |= (set to 1),
//                                                     field_0f4 = 0
//  0x00438700-equivalent part-level flag test, here 0x00573dfd:
//              part non-null, part->[0x10] non-null and its +0xdc8 bit 11 set
//                                                     -> flag_0140 = 0
//  0x00573e14  outgoing field_0e4 slot +0x30 (3, 1)
//  0x00573e2f  if flag_0141: slot +0x0c (0x50a993c); on a non-null result whose
//              +0x10 is non-null, mark the matching list entry unselected and
//              clear flag_0141
//  0x00573e7a  publish: slot +0x00 on the new part, field_0e4 = part,
//              slot +0x04 on the old part
//  0x00573e8a  field_0e4 == 0 -> 0x00572020(editor, 0)
//              otherwise: 0x00435ed0(0xd2cfe2ad, editor),
//                         0x00573c00(editor, 0, 0xffffffff),
//                         slot +0x30 (0, 1), then slot +0x10; when that equals
//                         0x50a993c and flag_0140 is set, resolve the sibling of
//                         type 0x50a993c, mark it selected, clear the sibling's
//                         pending entry and set flag_0141 = 1, then return
extern "C" __attribute__((thiscall)) void FUN_00573d70_SetPrimaryPart(OpaqueEditor* editor, void* part,
                                            std::uint32_t arg2) {
    (void)arg2;  // 0x00573d71 is the only stack-slot read in the body.

    if (part == nullptr && editor->flag_0140 == 0u) {
        editor->flag_0140 = 1u;
    }

    if (part == editor->field_0e4) {
        if (editor->field_0e4 == nullptr) {
            return;
        }
        if (Port_0047ec20(editor->field_0e4) == 0u) {
            return;
        }
    }

    if (editor->field_0f4 != nullptr && editor->field_0f4 != part) {
        if (editor->flag_0140 == 0u) {
            editor->flag_0140 = 1u;
        }
        editor->field_0f4 = nullptr;
    }

    if (editor->field_0e4 != part) {
        if (part != nullptr) {
            void* inner = Port_0047e6c0(part);
            if (inner != nullptr) {
                // 0x00573df0: MOV EAX,[EAX+0xdc8] ; SHR EAX,0xb ; TEST AL,1.
                // Bit 11 of the same 60-bit rigblock attribute field that
                // 0x00438700 tests, here on the incoming part.
                if ((*reinterpret_cast<const std::uint32_t*>(
                         reinterpret_cast<const std::uint8_t*>(inner) + 0xdc8) >>
                     11) &
                    1u) {
                    editor->flag_0140 = 0u;
                }
            }
        }

        if (editor->field_0e4 != nullptr) {
            Port_vtbl_30_set_state(editor->field_0e4, 3u, 1u);
            if (editor->flag_0141 != 0u) {
                // 0x00573e2f .. 0x00573e58: resolve the sibling of type
                // 0x50a993c from the OUTGOING part, then mark the list entry
                // that holds that sibling as unselected with flag 1.
                void* rel = Port_vtbl_0c_query(editor->field_0e4, kTypeId_50a993c);
                if (rel != nullptr && Port_0047e6c0(rel) != nullptr) {
                    void* rel_list = Port_0047e6c0(rel);
                    Port_0043e7e0(
                        rel_list,
                        static_cast<std::uint32_t>(Port_0043c3d0(rel_list, rel)),
                        1u);
                }
                editor->flag_0141 = 0u;
            }
        }

        void* old = editor->field_0e4;
        if (part != old) {
            if (part != nullptr) {
                Port_vtbl_addref(part);
            }
            editor->field_0e4 = part;
            if (old != nullptr) {
                Port_vtbl_release(old);
            }
        }

        if (editor->field_0e4 == nullptr) {
            Port_00572020(editor, 0u);
        } else {
            Port_00435ed0(kMarker_d2cfe2ad, editor);
            Port_00573c00(editor, nullptr, 0xffffffffu);
            Port_vtbl_30_set_state(editor->field_0e4, 0u, 1u);
            if (Port_vtbl_10_type_id(editor->field_0e4) == kTypeId_50a993c &&
                editor->flag_0140 != 0u) {
                void* rel = Port_00572770(&editor->field_0e4);
                void* rel_list = Port_0047e6c0(rel);
                std::uint32_t entry = static_cast<std::uint32_t>(
                    Port_0043c3d0(rel_list, rel));
                Port_0043e760(Port_0047e6c0(editor->field_0e4), entry);
                editor->flag_0141 = 1u;
                return;
            }
        }
    }
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
