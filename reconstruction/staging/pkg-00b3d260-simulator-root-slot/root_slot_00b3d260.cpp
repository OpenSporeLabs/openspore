#include "root_slot_00b3d260.hpp"

// 0x00b3d260 -- Simulator root-slot accessor: load one global dword, return it.
//
// Raw bytes, read from
// `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=0x00b3d230
// --stop-address=0x00b3d272` and matching the two-instruction listing stored in
// reconstruction/evidence/00b3d260/evidence.json:
//
//     0x00b3d260  a1 d8 ea 67 01   MOV EAX, DS:0x0167ead8
//     0x00b3d265  c3               RET
//
// The whole body is two instructions and there is nothing else in it: no
// branch, no call, no indirect transfer, no flag test, no register save, no
// stack access, and exactly one memory operand -- the absolute address
// 0x0167ead8. So there is nothing to transcribe but that single 32-bit load.
//
// What is modelled, and what is deliberately not:
//
//   * the load is a READ of one dword and the only store in the body is to EAX.
//     Nothing writes the global, so the modelled entry does not write it either;
//   * the returned value is the 4-byte word itself, and the declared return type
//     is the width-computable builtin std::uint32_t. The derived ABI record
//     classes the value pointer_like (INFERRED), and callers demonstrably
//     dereference it as an object base whose first dword is a function table
//     (0x00b32ac4, 0x00c8e600, 0x00c9a755, 0x00d58c38 read [eax], pass the word
//     itself as the receiver and dispatch through +0x24 / +0x30 / +0x38; 0x00fefc71
//     just stores it). That consumer evidence is real, but it does not name the
//     object, so no pointer type and no class are asserted here: the body proves
//     a four-byte load and nothing about what the word denotes;
//   * the convention is not stated, because the listing does not state one: no
//     register is read, no stack word is named, and the RET is bare, which is
//     byte-identical under all four x86-32 conventions. Two caller listings
//     (0x00b32ac4 and 0x00c8e600) push nothing and adjust nothing around the
//     call, so zero parameters is corroborated from the far side of the call as
//     well;
//   * the modelled image's guard words are test scaffolding invented here. They
//     are not the neighbouring dwords of .data and nothing is claimed about what
//     lives at 0x0167ead4 or 0x0167eadc.
//
// The modelled slot starts at zero. That is a placeholder, not a claim: the VA
// lies past .data's SizeOfRawData, so the image carries no initializer for it
// (see the header), and this body does not say who fills it. The project's own
// promoted metadata for the consumer 0x00abf790 records the producer, lifetime
// and reset of 0x0167ead8 as open questions, and this package keeps them open.

namespace openspore::reconstruction::pkg_00b3d260_root_slot {

RootSlotImage g_root_slot_image{};

Word& g_0167ead8 = g_root_slot_image.slot;

std::uint32_t PKG_00B3D260_CALL root_slot_accessor_00b3d260() {
  // 0x00b3d260  A1 D8 EA 67 01   MOV EAX, DS:0x0167ead8
  // 0x00b3d265  C3               RET
  return g_0167ead8;
}

}  // namespace openspore::reconstruction::pkg_00b3d260_root_slot
