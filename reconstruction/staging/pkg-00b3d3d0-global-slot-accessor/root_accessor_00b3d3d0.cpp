#include "root_accessor_00b3d3d0.hpp"

// 0x00b3d3d0 -- shared-state root accessor: load one global dword, return it.
//
// Raw bytes, read from
// `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=0x00b3d3c0
// --stop-address=0x00b3d3d8` and matching, instruction for instruction, the
// live Ghidra bridge's listing of the same binary:
//
//     0x00b3d3d0  a1 20 eb 67 01   MOV EAX, DS:0x0167eb20
//     0x00b3d3d5  c3               RET
//
// The whole body is two instructions and there is nothing else in it: no
// branch, no call, no indirect transfer, no flag test, no register save, no
// stack access, no store, and exactly one memory operand -- the absolute
// address 0x0167eb20. So there is nothing to transcribe but that single 32-bit
// load. INT3 padding brackets the body at 0x00b3d3cc..0x00b3d3cf and
// 0x00b3d3d6..0x00b3d3df, which is the body boundary seen from the other side.
//
// What is modelled, and what is deliberately not:
//
//   * the load is a READ of one dword and the only store in the body is to EAX.
//     Nothing writes the global, so the modelled entry does not write it either;
//   * the returned value is the 4-byte word itself. Both cited callers move it
//     straight into ECX as a receiver (0x00ba8988 `mov ecx,eax` then
//     `call 0x0103ca40`; 0x00fda848 `mov ecx,eax` then `call 0x01039730`), and
//     the pack classifies the return as `pointer_like`, but that is a fact
//     about the callers' use of the value and a low-confidence classifier. The
//     body proves a four-byte load and nothing about what the word denotes, so
//     the return type is uint32_t and no pointer or pointee type is asserted;
//   * the convention is not stated, because the listing does not state one: no
//     register is read, no stack word is named, and the RET is bare, which is
//     byte-identical under all four x86-32 conventions. The two caller listings
//     push nothing immediately before the call and adjust nothing afterwards, so
//     zero parameters is corroborated from the far side of the call as well;
//   * the modelled image's guard words are test scaffolding invented here. They
//     are not the neighbouring dwords of .data and nothing is claimed about what
//     lives at 0x0167eb20.
//
// The modelled slot starts at zero. That is a placeholder, not a claim: the VA
// lies past .data's SizeOfRawData, so the image carries no initializer for it
// (see the header), and this body does not say who fills it. In particular the
// closure synthesis in docs/analysis/simulator-root-closure.md characterises
// 0x00b3d2a0/0x00b3d300/0x00b3d3a0/0x00b3d400 over the slots 0x0167eae0,
// 0x0167eae4, 0x0167eb0c and 0x0167eb60 and never mentions 0x0167eb20, so no
// manager identity is imported for this one and none is asserted here.

namespace openspore::reconstruction::pkg_00b3d3d0 {

RootSlotImage g_root_slot_image{};

Word& g_0167eb20 = g_root_slot_image.slot;

// The declared return is spelled `uint32_t` rather than this package's
// `Word` alias. The alias IS `std::uint32_t` and the header asserts its
// width; the validator measures the *declared* return's width from the
// spelling and an alias names no width, so the alias spelling made this
// dimension NOT_AVAILABLE on a body whose machine return width is proven.
// Same type, one token changed.
uint32_t PKG_00B3D3D0_CALL root_accessor_00b3d3d0(){
  // 0x00b3d3d0  A1 20 EB 67 01   MOV EAX, DS:0x0167eb20
  // 0x00b3d3d5  C3               RET
  return g_0167eb20;
}

}  // namespace openspore::reconstruction::pkg_00b3d3d0