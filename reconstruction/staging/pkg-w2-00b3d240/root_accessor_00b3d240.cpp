#include "root_accessor_00b3d240.hpp"

// 0x00b3d240 -- shared-state root accessor: load one global dword, return it.
//
// Raw bytes, read from
// `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=0x00b3d230
// --stop-address=0x00b3d260` and matching, instruction for instruction, the
// live Ghidra bridge's listing of the same binary:
//
//     0x00b3d240  a1 c4 ea 67 01   MOV EAX, DS:0x0167eac4
//     0x00b3d245  c3               RET
//
// The whole body is two instructions and there is nothing else in it: no
// branch, no call, no indirect transfer, no flag test, no register save, no
// stack access, no store, and exactly one memory operand -- the absolute
// address 0x0167eac4. So there is nothing to transcribe but that single 32-bit
// load.
//
// What is modelled, and what is deliberately not:
//
//   * the load is a READ of one dword and the only store in the body is to EAX.
//     Nothing writes the global, so the modelled entry does not write it either;
//   * the returned value is the 4-byte word itself. Callers dereference it as an
//     address (0x00b19453 `mov edx,DWORD PTR [eax]`, then 0x00b19457/0x00b1945a
//     `mov eax,DWORD PTR [edx+0x34]` / `call eax`), but that is a fact about the
//     callers' use of the value; the body proves a four-byte load and nothing
//     about what the word denotes, so the return type is uint32_t and no
//     pointer is asserted;
//   * the convention is not stated, because the listing does not state one: no
//     register is read, no stack word is named, and the RET is bare, which is
//     byte-identical under all four x86-32 conventions. Two caller listings
//     (0x00b1929d/0x00b192a2 and 0x00b1944e/0x00b19453) push nothing and adjust
//     nothing around the call, so zero parameters is corroborated from the far
//     side of the call as well;
//   * the modelled image's guard words are test scaffolding invented here. They
//     are not the neighbouring dwords of .data and nothing is claimed about what
//     lives at 0x0167eac4.
//
// The modelled slot starts at zero. That is a placeholder, not a claim: the VA
// lies past .data's SizeOfRawData, so the image carries no initializer for it
// (see the header), and this body does not say who fills it.

namespace openspore::reconstruction::pkg_w2_00b3d240 {

RootSlotImage g_root_slot_image{};

Word& g_0167eac4 = g_root_slot_image.slot;

// `uint32_t` spelled out rather than the package's `Word` alias -- same type,
// and the header already asserts `sizeof(Word) == 4`; the validator measures
// the declared return's width from the spelling, and an alias names none.
uint32 PKG_W2_00B3D240_CALL root_accessor_00b3d240() {
  // 0x00b3d240  A1 C4 EA 67 01   MOV EAX, DS:0x0167eac4
  // 0x00b3d245  C3               RET
  return g_0167eac4;
}

}  // namespace openspore::reconstruction::pkg_w2_00b3d240