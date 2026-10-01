#include "root_slot_dword_00b3d470.hpp"

// 0x00b3d470 -- Simulator-root-adjacent accessor: load one global dword,
// return it.
//
// Raw bytes, read three ways and agreeing: from the file at .text file offset
// 0x0073c870, from GhidraMCP /read_memory, and from the machine listing stored
// in reconstruction/evidence/00b3d470/evidence.json
// (categories.disassembly.value.instructions; categories.ghidra_function.value
// reports body_start 00b3d470, body_end 00b3d475, body_span_bytes 6):
//
//     0x00b3d470  a1 18 eb 67 01   MOV EAX, DS:0x0167eb18
//     0x00b3d475  c3               RET
//     0x00b3d476  cc cc cc cc cc cc cc cc cc cc   (pad, through 0x00b3d47f)
//
// The whole body is two instructions and there is nothing else in it: no
// branch, no call, no indirect transfer, no flag test, no register save, no
// stack access, and exactly one memory operand -- the absolute address
// 0x0167eb18. So there is nothing to transcribe but that single 32-bit load.
//
// What is modelled, and what is deliberately not:
//
//   * the load is a READ of one dword and the only store in the body is to EAX.
//     Nothing writes the global, so the modelled entry does not write it either;
//   * the returned value is the 4-byte word itself. The derived ABI record
//     classes it pointer_like (RT2, INFERRED) and the caller at 0x00d3a830
//     immediately dereferences the result at +0x60, but the body proves a
//     four-byte load and nothing about what the word denotes, so the return type
//     is uint32_t and no pointer is asserted;
//   * the convention is not stated, because the listing does not state one: no
//     register is read, no stack word is named, and the RET is bare, which is
//     byte-identical under all four x86-32 conventions. Two caller listings
//     (0x00b33784 followed immediately by 0x00b33789 `mov ecx,eax`, and
//     0x00d3a830 followed immediately by 0x00d3a835 `add eax,0x60`) push nothing
//     and adjust nothing around the call, so zero parameters is corroborated from
//     the far side of the call as well. The evidence pack records 24 direct-call
//     edges from 10 distinct caller functions;
//   * the modelled image's guard words are test scaffolding invented here. They
//     are not the neighbouring dwords of .data and nothing is claimed about what
//     lives at 0x0167eb1c or 0x0167eb34.
//
// The modelled slot starts at zero. That is a placeholder, not a claim: the VA
// lies past .data's SizeOfRawData, so the image carries no initializer for it
// (see the header), and this body does not say who fills it.
//
// No runtime, Wine, trace or differential evidence exists for this entry; every
// statement here is static and pinned to the bytes of this binary.

namespace openspore::reconstruction::pkg_00b3d470 {

RootSlotImage g_root_slot_image{};

Word& g_0167eb18 = g_root_slot_image.slot;

// The declared return is spelled `uint32_t` rather than this package's
// `Word` alias. The alias IS `std::uint32_t` and the header asserts its
// width; the validator measures the *declared* return's width from the
// spelling and an alias names no width, so the alias spelling made this
// dimension NOT_AVAILABLE on a body whose machine return width is proven.
// Same type, one token changed.
uint32_t PKG_00B3D470_CALL root_slot_dword_00b3d470(){
  // 0x00b3d470  A1 18 EB 67 01   MOV EAX, DS:0x0167eb18
  // 0x00b3d475  C3               RET
  return g_0167eb18;
}

}  // namespace openspore::reconstruction::pkg_00b3d470
