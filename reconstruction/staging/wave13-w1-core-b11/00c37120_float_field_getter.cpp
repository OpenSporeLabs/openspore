// reconstruction/staging/wave13-w1-core-b11/00c37120_float_field_getter.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c37120 (image base
// 0x00400000). Body 0x00c37120..0x00c37126, 2 instructions, 7 bytes.
//
// Observed contract: the receiver's 32-bit float at field offset +0x768 is
// pushed onto the x87 stack and returned. Nothing else happens: no global, no
// callee, no branch, no stack argument, no saved register.
//
// Evidence:
//   0x00c37120: FLD dword ptr [ECX + 0x768]   (d9 81 68 07 00 00)
//   0x00c37127: RET                            (c3)
//   live read at 0x00c37120: d9 81 68 07 00 00 c3 cc cc cc cc cc cc cc cc cc
//
// Corroboration: 15 xref sites, all in the same 5-byte CALL form. Every window
// inspected treats the result as an x87 value in arithmetic (0x00dc0329,
// 0x00fe1540, 0x0101ba91, 0x0101d166, 0x0101d1a0, 0x01017c37), never as an
// integer or a pointer.
//
// Not claimed: the owning class (0x00dc0230 passes [ESI + 0x68c] as the
// receiver, so the receiver is a sub-object there), and the domain meaning of
// the float.

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00c37120 {

// Observed receiver offset of the returned float.
inline constexpr std::size_t kFloatOffset = 0x768;

// Returns the receiver's float at +0x768.
//
// The return type is float, so the x87 push is emitted by the compiler; the
// reconstruction is written to match the two observed instructions, not to be
// a hand-rolled asm blob.
Float float_field_768(FloatField768Owner* self) {
    // 0x00c37120: FLD dword ptr [ECX + 0x768]
    return self->field768;
    // 0x00c37127: RET  (bare - the callee pops nothing)
}

}  // namespace t00c37120
}  // namespace b11
}  // namespace openspore
