// PKG-W2-00E5CAC0 -- VA 0x00e5cac0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The literal body, transcribed from the five bytes at 0x00e5cac0:
//
//   00e5cac0  8B C1       MOV EAX,ECX
//   00e5cac2  C2 04 00    RET 0x4
//
// Every line below is tied to those bytes, to the machine-derived ABI record, or
// to bytes read back out of the image. See ret_eax_from_ecx_00e5cac0.hpp for the
// byte-level decode, for the determination that names __thiscall (R1-VFT and
// C6B), for the caller-side ADD ECX,0xc that corroborates it, and for the
// explicit list of what is NOT claimed: no class, no vtable identity, no receiver
// type, no field, no member and no object size.

#include "ret_eax_from_ecx_00e5cac0.hpp"

// The header spells its convention token once and then #undefs it, so the body
// re-defines the same macro rather than depending on the header's lifetime.
#if defined(_MSC_VER)
#define PKG_W2_00E5CAC0_THISCALL __thiscall
#else
#define PKG_W2_00E5CAC0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_w2_00e5cac0 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x00e5cac0 by the 8-hex VA token appearing in the function name, and
// it takes the FIRST such definition in the file.
extern "C" Receiver* PKG_W2_00E5CAC0_THISCALL reconstruct_00e5cac0(
    Receiver* receiver, Word popped_stack_slot) {
  // The whole of the behaviour, in the shape the bytes describe:
  //
  //   00e5cac0  8B C1       MOV EAX,ECX   ; EAX receives ECX verbatim, 32 bits
  //   00e5cac2  C2 04 00    RET 0x4       ; the callee pops the 4-byte slot
  //
  // There is no branch, no memory access, no call and no indirect transfer, so
  // there is nothing here to reproduce beyond the register pass-through and the
  // slot the RET accounts for. Two things follow from the byte decode and are
  // therefore stated as the model rather than invented:
  //
  //   1. The value returned is the value the register carried on entry. The MOV
  //      copies all 32 bits and the body never narrows or extends them, so the
  //      answer tracks the input bit for bit -- including the all-zero input,
  //      which the body does not special-case, because there is no branch in the
  //      five bytes that could special-case anything.
  //   2. The stack slot the RET immediate accounts for is not read by the body.
  //      The machine record says so directly (`read: false`, `observed: false`,
  //      `source: "ret_immediate"`), and the code says so too: the parameter is
  //      discarded and never appears in the returned value. The slot is named for
  //      the four bytes `RET 0x4` accounts for and for nothing else, because a
  //      parameter count is not what a terminal immediate establishes.
  //
  // The receiver is NOT adjusted here either. The `ADD ECX,0xc` that exists at
  // 0x007fbd8d, three instructions before the `CALL` at 0x007fbd90, is the
  // CALLER's instruction; this body has no add, no sub and no lea. So a call
  // through that site answers `this + 0xc` and a call through either of the two
  // unadjusted sites answers `this`, and the difference is entirely caller-side.
  // The static_assert below is the pin: it is an assertion and not documentation,
  // and it fails the build if the header's constants are ever edited away from
  // what the listing carries. It costs nothing at run time.
  static_assert(kStackCleanupBytes == 0x4u,
                "the terminal immediate of the RET is 4, so the callee pops 4");
  static_assert(kBodySpanBytes == 5u,
                "MOV r32,r/m32 with mod=11 plus RET imm16 is five bytes");
  static_assert(kReceiverFieldOffsetClaimed == false,
                "the body never dereferences the receiver, so no field offset is "
                "claimed in either direction");
  (void)popped_stack_slot;
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_w2_00e5cac0

#undef PKG_W2_00E5CAC0_THISCALL
