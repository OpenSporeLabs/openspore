#include "root_accessor_00b3d230.hpp"

// 0x00b3d230 -- shared-state root accessor: load one global dword, return it.
//
// Raw bytes, read from
// `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=0x00b3d200
// --stop-address=0x00b3d260` and matching the two-instruction listing stored in
// reconstruction/evidence/00b3d230/evidence.json:
//
//     0x00b3d230  a1 c0 ea 67 01   MOV EAX, DS:0x0167eac0
//     0x00b3d235  c3               RET
//
// The whole body is two instructions and there is nothing else in it: no
// branch, no call, no indirect transfer, no flag test, no register save, no
// stack access, and exactly one memory operand -- the absolute address
// 0x0167eac0. So there is nothing to transcribe but that single 32-bit load.
//
// What is modelled, and what is deliberately not:
//
//   * the load is a READ of one dword and the only store in the body is to EAX.
//     Nothing writes the global, so the modelled entry does not write it either;
//   * the returned value is the 4-byte word itself. The derived ABI record
//     classes it pointer_like (INFERRED) and two callers null-test it
//     (0x00c0d3c0, 0x00c38532), but the body proves a four-byte load and nothing
//     about what the word denotes, so the return type is uint32_t and no
//     pointer is asserted;
//   * the convention is not stated, because the listing does not state one: no
//     register is read, no stack word is named, and the RET is bare, which is
//     byte-identical under all four x86-32 conventions. Two caller listings
//     (0x00b19449/0x00b1944e and 0x00adad9d/0x00ada2) push nothing and adjust
//     nothing around the call, so zero parameters is corroborated from the far
//     side of the call as well;
//   * the modelled image's guard words are test scaffolding invented here. They
//     are not the neighbouring dwords of .data and nothing is claimed about what
//     lives at 0x0167eac4.
//
// The modelled slot starts at zero. That is a placeholder, not a claim: the VA
// lies past .data's SizeOfRawData, so the image carries no initializer for it
// (see the header), and this body does not say who fills it.

namespace openspore::reconstruction::pkg_w2_00b3d230 {

RootSlotImage g_root_slot_image{};

Word& g_0167eac0 = g_root_slot_image.slot;

// `uint32_t` is spelled out rather than the package's `Word` alias: the alias
// is `std::uint32_t` (asserted in the header), but the validator measures the
// declared return's width from the spelling and an alias names no width. This
// is the same type; only the token the validator reads changes.
uint32 PKG_W2_00B3D230_CALL root_accessor_00b3d230() {
  // 0x00b3d230  A1 C0 EA 67 01   MOV EAX, DS:0x0167eac0
  // 0x00b3d235  C3               RET
  return g_0167eac0;
}

}  // namespace openspore::reconstruction::pkg_w2_00b3d230