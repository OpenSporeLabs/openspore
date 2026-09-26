// Clean-room reconstruction of SporeApp.exe 0x00451e50.
//
// 17 instructions, 0x00451e50..0x00451e80, 51 bytes. Instruction addresses in
// the comments are the proof for every statement below.

#include "editor_rigblock_00451e50.hpp"

namespace openspore {
namespace dispatch_b05 {

// 0x00451e50: PUSH EBP / MOV EBP,ESP / SUB ESP,0x8
// 0x00451e56: MOV dword ptr [EBP - 0x8],ECX   -> the receiver is spilled to the
//                                               frame; this is a __thiscall.
// 0x00451e5c: CMP dword ptr [EAX + 0x18c],0x0
// 0x00451e63: JZ 0x00451e7d                   -> the only early exit.
// 0x00451e68: MOV EDX,dword ptr [ECX + 0x18c]
// 0x00451e6e: ADD EDX,0x1c                    -> base = nested + 0x1c
// 0x00451e7a: MOV dword ptr [EAX + 0x1c],ECX  -> store at nested + 0x38
// 0x00451e80: RET 0x4                         -> the callee pops the one stack
//                                                dword; there is no return value.
extern "C" void EditorRigblock_00451e50_SetNestedValue(
    Rigblock00451e50* self, std::int32_t value) {
    // 0x00451e63: a null nested pointer makes the whole call a silent no-op.
    // Nothing is written, no flag is set, and no exception path exists. The
    // guard is evaluated BEFORE the pointer is used, exactly as in the binary.
    if (self->field_18c == nullptr) {
        return;
    }

    // The +0x1c intermediate at 0x00451e6e is a compiler artefact of the
    // original source dereferencing a typed pointer; the observable effect is a
    // single aligned 32-bit store at nested + 0x38.
    auto* const nested = reinterpret_cast<NestedRigblockValue00451e50*>(
        self->field_18c);
    nested->field_38 = value;
}

}  // namespace dispatch_b05
}  // namespace openspore
