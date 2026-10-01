// PKG-EDITOR-CHILD-007F30D0 -- VA 0x007f30d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)

#include "editor_child_007f30d0.hpp"

// The header spells its convention token once and then #undefs it, so the body
// re-defines the same macro rather than depending on the header's lifetime.
#if defined(_MSC_VER)
#define PKG_EDITOR_CHILD_007F30D0_THISCALL __thiscall
#else
#define PKG_EDITOR_CHILD_007F30D0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_child_007f30d0 {

// The literal body, transcribed from the eleven bytes at 0x007f30d0:
//
//   007f30d0  85 C9       TEST ECX,ECX        ; receiver == 0 ?
//   007f30d2  74 04       JZ 0x007f30d8       ; yes -> the zero arm
//   007f30d4  8D 41 04    LEA EAX,[ECX + 0x4] ; no  -> EAX = receiver + 4
//   007f30d7  C3          RET
//   007f30d8  33 C0       XOR EAX,EAX         ; zero arm: EAX = 0
//   007f30da  C3          RET
//
// Every line below is tied to those bytes rather than to a plausible story:
//
//   85      TEST r/m32,r32. Sets ZF from the AND of the two operands and
//           writes nothing. The receiver is READ here, four bytes wide in the
//           register, and never written.
//   C9      ModRM: mod=11 (register/register), reg=001 (ECX as the first
//           operand), r/m=001 (ECX as the second). Both operands are the same
//           register, so the tested value is the receiver itself.
//   74 04   JZ with disp8 +4: the jump target is the instruction after the
//           three-byte LEA, i.e. 0x007f30d8, the zero arm. The branch is on
//           the receiver being zero, on nothing else.
//   8D 41 04  LEA EAX,[ECX+0x4]. An address computation: the disp8 is added
//           to the address register and the SUM is stored in EAX. No memory
//           is read and none is written -- LEA is the one instruction that
//           forms an address without touching it.
//   C3      RET, no immediate byte behind it. The callee pops zero bytes.
//   33 C0   XOR EAX,EAX. The zero arm's write: all 32 bits of EAX cleared,
//           so no bit of any previous EAX survives into the return.
//
// The displacement pin, outside the function span so the span itself states
// no literal the listing does not carry. This is an assertion and not
// documentation: it fails the build if the header's value is ever edited away
// from the disp8 the listing carries.
static_assert(kChildDisplacement == 0x4u,
              "LEA EAX,[ECX+0x4] at 0x007f30d4 -- the disp8 is 4");

// 0x007f30d0  85 C9 74 04 8D 41 04 C3 33 C0 C3
//
// Written as the two arms it has. The null check is the TEST/JZ pair: the
// receiver is compared against zero and the zero arm returns a null pointer.
// The nonzero arm is the LEA: the returned value is the receiver's address
// plus the disp8, formed as an address and returned as a pointer, never
// dereferenced. The receiver is an opaque byte run and the arithmetic goes
// through the displacement-named accessor, because the machine-derived
// receiver record for this target is `bounds_only` and enumerates no
// displacement of its own -- the LEA takes ECX's address without any memory
// access through it. A member name here would assert an identity for the
// word at +4 that the evidence does not corroborate; the displacement does
// not need that kind of corroborance, so it keeps the name and the word does
// not.
extern "C" OpaqueChild* PKG_EDITOR_CHILD_007F30D0_THISCALL
editor_child_007f30d0(OpaqueReceiver* receiver) {
  if (receiver == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueChild*>(
      reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement);
}

}  // namespace openspore::reconstruction::pkg_editor_child_007f30d0

#undef PKG_EDITOR_CHILD_007F30D0_THISCALL
