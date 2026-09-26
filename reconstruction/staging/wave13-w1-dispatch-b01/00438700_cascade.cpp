#include "00438700_cascade.hpp"

namespace openspore {
namespace wave13_w1_dispatch_b01 {

// Flag-bit indices. The 60-bit field at +0xdc8 is written by index through
// 0x00435a10, which rejects any index >= 0x3c. SDK candidate names come from
// Spore/Editors/EditorRigblock.h enum EditorRigblockBoolAttributes; the SDK
// enumerator for index 0x0B is a duplicate of 0x0A and is therefore not usable,
// so bit 11 is left unnamed here rather than invented.
enum : std::uint32_t {
    kFlagIsVertebra = 7u,   // 0x80  - SDK: kEditorRigblockModelIsVertebra
    kFlagUnnamed_0B = 11u,  // 0x800 - no SDK enumerator at 0x0B
};

namespace {
inline bool TestFlag(const OpaqueEditorRigblock* p, std::uint32_t bit) {
    return ((p->flags_dc8 >> bit) & 1u) != 0u;
}
}  // namespace

// 0x00438700, instruction by instruction:
//
//  0x00438710  CALL 0x004388b0        self, other            (unconditional)
//  0x00438718  CMP [ECX+0x28],0 ; JZ 0x004388a2            exit when no sub-object
//  0x00438728  CALL 0x004adc40        sub-object; AL tested
//  0x00438738  bit 7 of other->flags_dc8 ; JNZ 0x004388a2   IsVertebra -> exit
//  0x0043878f  CMP self->field_3e0,0
//     self->field_3e0 != 0:
//  0x004387a1  CMP other->field_3e0,0 ; JZ 0x004387d4 -> JMP 0x004388a2 (exit)
//  0x004387cf  CALL 0x004388b0        self->field_3e0, other->field_3e0
//     self->field_3e0 == 0:
//  0x004387dc  CMP other->field_3e0,0 ; JZ 0x004388a2       exit
//  0x004387f3  CALL 0x004a7e60        self, cdecl, 4 bytes cleaned
//  0x00438818  bit 11 of self->flags_dc8
//     bit 11 clear -> 0x0043888a: CALL 0x004388b0  self, other->field_3e0
//     bit 11 set   -> 0x00438859: CALL 0x0044f220   self
//                     FLDZ / FILD / FUCOMIP / LAHF / TEST AH,0x44 / JP
//                     the helper runs only on the equal edge, i.e. only when the
//                     dword at self+0x1c0 is 0.
//
// The original reaches 0x00438859 only after 0x004387fb already established
// that 0x004a7e60(self) was non-zero in AL, so on a deterministic 0x004a7e60
// the bit-11 sub-branch also runs the helper. The reconstruction keeps the
// re-read rather than collapsing it, because the second call's full-dword
// result is what the FUCOMIP actually tests.
extern "C" __attribute__((thiscall)) void FUN_00438700_AdoptCascadeFrom(OpaqueEditorRigblock* self,
                                              OpaqueEditorRigblock* other) {
    Port_004388b0(self, other);

    if (self->field_028 == nullptr) {
        return;
    }
    if (Port_004adc40(self->field_028) == 0u) {
        return;
    }
    if (TestFlag(other, kFlagIsVertebra)) {
        return;
    }

    if (self->field_3e0 != nullptr) {
        if (other->field_3e0 == nullptr) {
            return;
        }
        Port_004388b0(self->field_3e0, other->field_3e0);
        return;
    }

    if (other->field_3e0 == nullptr) {
        return;
    }
    if (Port_004a7e60(self) == 0u) {
        return;
    }

    if (!TestFlag(self, kFlagUnnamed_0B)) {
        Port_004388b0(self, other->field_3e0);
        return;
    }
    if (Port_0044f220(self) == 0u) {
        Port_004388b0(self, other->field_3e0);
    }
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore
