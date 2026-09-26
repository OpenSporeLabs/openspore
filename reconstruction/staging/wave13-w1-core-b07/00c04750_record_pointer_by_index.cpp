// reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c04750 (image base
// 0x00400000). Body 0x00c04750..0x00c04787, 20 instructions, 56 bytes.
//
// Contract reconstructed from the binary: a pointer computation, not a value
// lookup. Two guards must pass before anything is returned:
//   1. the current-mode pointer returned by 0x00b5b800 must equal the global
//      object at 0x01654c10 (0x00c04758 CMP EAX,0x1654c10);
//   2. the sub-object resolved from the id at this+0x1c through 0x00b18530 must
//      be non-null (0x00c04768 TEST ESI,ESI).
// When both hold the result is index * 0x4e0 + [subObject + 0x70], where the
// index comes from 0x00f3c0e0 applied to the global at 0x016c7aa4 (+0x74).
// Either guard failing yields 0. The 0x4e0 stride and the record fields read by
// neighbours (+0x4a8 at 0x00c047bc, +0x4ec at 0x00c32f2f, +0x504 at
// 0x00bba531) identify the result as a pointer to a 0x4e0-stride record, not
// an offset.
//
// Not claimed: the identity of the receiver, the sub-object, the index and the
// record type. 0x00f3c0e0 dereferences App::sScenarioMode (an SDK global) and
// branches on [sScenarioMode + 0xcc] == 2, which is suggestive of a
// level/planet index but is not established.

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00c04750 {

// 0x00b5b800 -- cdecl, no arguments; returns -1 or the current-mode pointer.
// 0x00b18530 -- thiscall; returns 0 when [this + 0x1c] == -1, else the object
// 0x00f3e8a0 resolves for that id.
// 0x00f3c0e0 -- returns the current index.
// The sentinel the mode pointer must equal (0x00c04758 CMP EAX,0x1654c10).
inline constexpr Word kModeSentinelGlobal = 0x01654c10;

// Returns recordBase + index * 0x4e0, or 0 when a guard fails.
Word record_pointer_by_index(LevelOwner* self, CurrentModeFn currentMode,
                             ResolveSubObjectFn resolveSubObject, CurrentIndexFn currentIndex) {
    // 0x00c04753 CALL 0x00b5b800
    const Word mode = currentMode();
    // 0x00c04758 CMP EAX,0x1654c10 / 0x00c0475d JNZ 0x00c04784
    if (mode != kModeSentinelGlobal) {
        return 0;
    }

    // 0x00c0475f MOV ECX,ESI / 0x00c04761 CALL 0x00b18530
    const Word subObject = resolveSubObject(reinterpret_cast<Word>(self));
    // 0x00c04768 TEST ESI,ESI / 0x00c0476a JZ 0x00c04784
    if (subObject == 0) {
        return 0;
    }

    // 0x00c0476c MOV EAX,[0x016c7aa4] / 0x00c04771 MOV ECX,[EAX + 0x74]
    // 0x00c04774 CALL 0x00f3c0e0
    const Word index = currentIndex();
    // 0x00c04779 IMUL EAX,EAX,0x4e0
    // 0x00c0477f ADD EAX,dword ptr [ESI + 0x70]
    return index * kRecordStride + *pointer_at<Word>(subObject + 0x70);
}

}  // namespace t00c04750
}  // namespace b07
}  // namespace openspore
