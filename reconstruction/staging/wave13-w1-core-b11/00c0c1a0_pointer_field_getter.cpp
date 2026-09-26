// reconstruction/staging/wave13-w1-core-b11/00c0c1a0_pointer_field_getter.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c0c1a0 (image base
// 0x00400000). Body 0x00c0c1a0..0x00c0c1a6, 2 instructions, 7 bytes.
//
// Observed contract: return the receiver's dword at field offset +0xe84.
// Nothing else happens: no global, no callee, no branch, no stack argument, no
// saved register, and the full 32 bits of EAX are defined by the load.
//
// Evidence:
//   0x00c0c1a0: MOV EAX,dword ptr [ECX + 0xe84]  (8b 81 84 0e 00 00)
//   0x00c0c1a6: RET                             (c3)
//   live read at 0x00c0c1a0: 8b 81 84 0e 00 00 c3 cc cc cc cc cc cc cc cc cc
//
// The matching setter is 0x00c0c180, ten bytes earlier, and pins the field's
// role: it stores its stack argument at [ECX + 0xe84] and, only when that
// argument is non-null, caches [argument + 0x10] at [ECX + 0xe80]. So the
// getter/setter pair owns one pointer field plus a shadow copy of the pointee's
// +0x10 word. The setter has 6 xrefs (0x00c09fa0, 0x00c099e0, 0x00cd8e70,
// 0x00eeccb0 twice, 0x00d7eab0).
//
// Consumer shape, 31 xref sites over 18 caller functions: every inspected site
// null-checks the result (TEST EAX,EAX / JZ) and then reads the pointee at
// +0x330 (0x00c09ba6), +0x384 as a float and +0x389 as a byte (0x00d8d88f),
// +0x390 (0x00ba4220), or +0x3fc..+0x420 as eight dwords (0x00c301f4).
// 0x00cdce40 stores the raw value into a node at [ESI + 0x14].
//
// Not claimed: the owning class and the pointee type. No vtable was located and
// SporeApp.exe carries no MSVC RTTI, so no class identity is asserted.

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00c0c1a0 {

// Observed receiver offset of the returned pointer.
inline constexpr std::size_t kPointerOffset = 0xe84;

// Returns the receiver's dword at +0xe84. The reconstruction returns Dword
// because that is what the load is observed to produce; the consumers then
// treat it as a pointer, which is a use, not a declared type.
Dword pointer_field_e84(PointerFieldE84Owner* self) {
    // 0x00c0c1a0: MOV EAX,dword ptr [ECX + 0xe84]
    return self->fieldE84;
    // 0x00c0c1a6: RET  (bare)
}

}  // namespace t00c0c1a0
}  // namespace b11
}  // namespace openspore
