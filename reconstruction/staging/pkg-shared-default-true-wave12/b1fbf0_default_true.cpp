#include "b1fbf0_default_true.hpp"

namespace openspore::reconstruction::pkg_shared_default_true_wave12 {

// 0x00b1fbf0 - a three-byte constant body that answers "yes" unconditionally.
//
// The complete body, read live at 0x00b1fbf0 (b0 01 c3, then cc cc cc cc
// cc cc cc as the usual inter-function INT3 pad):
//
//   0x00b1fbf0  b0 01   mov al, 0x1
//   0x00b1fbf2  c3      ret
//
// Nothing else exists: no callee, no global, no memory operand, no stack
// argument, no frame, and no register read of any kind. Only AL is written, so
// bits 8..31 of EAX keep whatever the caller left there, and the bare RET
// carries no immediate, so the callee pops zero stack words.
//
// The receiver parameter is part of the observed port, not of the body. The
// body never dereferences it, but 0x00ee8bf6 loads this same address out of a
// vtable slot and calls it with ECX holding the receiver:
//
//   0x00ee8bf1  8b 4e 10        mov ecx, dword ptr [esi + 0x10]
//   0x00ee8bf4  8b 11           mov edx, dword ptr [ecx]
//   0x00ee8bf6  8b 42 10        mov eax, dword ptr [edx + 0x10]
//   0x00ee8bf9  ff d0           call eax
//   0x00ee8bfb  84 c0           test al, al
//
// so the slot is reached with a populated ECX even though the implementation
// ignores it. The port keeps the parameter for that reason.
//
// No semantic name is claimed. A scan of .rdata/.data for the little-endian
// dword of this address finds 538 stored pointers, and the ones that land
// inside the tables the triage snapshot names sit at four different offsets:
// +0x14 and +0x60 of the table at 0x01485550, +0x10 and +0x14 of the table at
// 0x013fc06c, and +0x0c of the table at 0x013f57f8. One named interface method
// cannot occupy all of those, so this is a shared default body rather than one
// identifiable method.

extern "C" std::uint8_t FUN_00b1fbf0_shared_default_true(
    OpaqueB1Fbf0SlotReceiver* receiver) {
  // The only value this function ever produces is the byte 0x01. Consumers
  // read it with TEST AL,AL, and two call sites (0x0082c27a, 0x00a43062)
  // discard it, which is consistent with a body that has no side effect.
  //
  // This address is also the stored body of a vtable slot, reached through
  // slot +0x10 at 0x00ee8bf6, so the port carries the receiver even though
  // this body never reads it.
  static_cast<void>(receiver);
  return 1;
}

}  // namespace openspore::reconstruction::pkg_shared_default_true_wave12
