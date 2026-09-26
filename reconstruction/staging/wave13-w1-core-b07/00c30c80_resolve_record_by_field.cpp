// reconstruction/staging/wave13-w1-core-b07/00c30c80_resolve_record_by_field.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c30c80 (image base
// 0x00400000). Body 0x00c30c80..0x00c30ca5, 13 instructions, 38 bytes.
//
// Contract reconstructed from the binary: the receiver carries a 32-bit record
// id at +0xb0. An id of -1 is the "unset" sentinel and yields 0 without any
// further work. Otherwise the id is resolved through the global handle table
// at 0x0167eae4; an unresolved handle also yields 0. A resolved handle is
// tail-transferred to 0x00bba500, whose result becomes this function's result
// without any further processing.
//
// Not claimed: the identity of the receiver class and the domain meaning of
// the id, the handle table and the 0x4e0-stride record the accessors reach.

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00c30c80 {

// 0x00b3d2a0 is two instructions: MOV EAX,dword ptr [0x0167eae4] / RET. It
// has a bare RET, so it leaves the handle it was handed on the stack, and that
// word becomes the stack argument of 0x00ba6d80 (which retires it with
// RET 0x4). That is why the handle is pushed before the global is fetched.
inline constexpr Word kUnsetId = 0xffffffffu;

// Resolves the id at this+0xb0 to a record pointer, or 0.
Word resolve_record_by_field(RecordIdOwner* self, GlobalHandleTableFn handleTable,
                             ResolveHandleFn resolveHandle, RecordAccessorFn recordAccessor) {
    // 0x00c30c80 MOV EAX,dword ptr [ECX + 0xb0]
    // 0x00c30c86 CMP EAX,-0x1
    // 0x00c30c89 JZ 0x00c30ca3 -> XOR EAX,EAX ; RET
    const Word id = self->fieldB0;
    if (id == kUnsetId) {
        return 0;
    }

    // 0x00c30c8b PUSH EAX / 0x00c30c8c CALL 0x00b3d2a0 / 0x00c30c91 MOV ECX,EAX
    // / 0x00c30c93 CALL 0x00ba6d80 (RET 0x4 consumes the pushed id)
    const Word table = handleTable();
    const Word record = resolveHandle(table, id);

    // 0x00c30c98 TEST EAX,EAX / 0x00c30c9a JZ 0x00c30ca3
    if (record == 0) {
        return 0;
    }

    // 0x00c30c9c MOV ECX,EAX / 0x00c30c9e JMP 0x00bba500 -- a tail transfer,
    // not a call, so 0x00bba500's result is this function's result.
    return recordAccessor(record);
}

}  // namespace t00c30c80
}  // namespace b07
}  // namespace openspore
