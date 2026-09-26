// 0x00c0c2f0 — 0x00c0c2f0..0x00c0c2f6, 2 instructions, 7 bytes.
//
//   0x00c0c2f0 MOV EAX,dword ptr [ECX + 0xeac]
//   0x00c0c2f6 RET
//
// __thiscall, 32-bit return in EAX, receiver in ECX, zero stack arguments,
// bare RET. The load is a full dword, so the return width is 4, and the body
// reads nothing else and writes nothing at all.
//
// The matching setter sits 16 bytes later at 0x00c0c300:
//
//   0x00c0c300 MOV EAX,dword ptr [ESP + 0x4]
//   0x00c0c304 MOV dword ptr [ECX + 0xeac],EAX
//   0x00c0c30a RET 0x4
//
// so this field is a read/write scalar with a dedicated accessor pair. A third
// accessor at 0x00c0c310 reads bit 15 of the neighbouring dword at +0xb58,
// confirming the region is a dense block of small accessors over one object.
//
// A whole-image scan for the displacement 0xeac returns exactly sixteen
// referencing instructions, all on this one object:
//
//   writes   0x00c03ef4  MOV dword ptr [EDI + 0xeac],0x2
//            0x00c04300  MOV dword ptr [ESI + 0xeac],0x2
//            0x00c1ca34  MOV dword ptr [ESI + 0xeac],EBP   (EBP = 0, XOR at
//                                                          0x00c1ca2e)
//            0x00c1fc7d  MOV dword ptr [ESI + 0xeac],EBX   (bulk initialiser,
//                                                          EBX = 0)
//            0x00c0c304  this class's setter
//   reads    0x00c0587d  CMP dword ptr [ESI + 0xeac],0x2
//            0x00c05960  CMP dword ptr [ESI + 0xeac],0x2
//            0x00c05b4d  CMP dword ptr [ESI + 0xeac],0x1 / JL
//            0x00c0ad54  CMP dword ptr [ESI + 0xeac],0x2
//            0x00c17e11  CMP dword ptr [EDI + 0xeac],0x2
//            0x00c19e5d  CMP dword ptr [EDI + 0xeac],0x2
//            0x00c1e649  CMP dword ptr [ESI + 0xeac],0x2
//            0x00c098b7  MOV EAX,dword ptr [ESI + 0xeac]
//            0x00c249e1  MOV EAX,dword ptr [ESI + 0xeac]   the switch reader
//            0x00c0c2f0  this getter
//
// Value domain, as far as it is observed: initialised to 0 by the bulk
// initialiser, set to 2 at two sites, compared against 1 once and against 2
// seven times. Values above 2 are not excluded by any observed instruction, so
// the field is NOT declared to be a closed three-value enum.
//
// The reader at 0x00c249e1 is a real dispatch on the value, and it is where the
// flag meaning shows through:
//
//   0x00c249e1 MOV EAX,dword ptr [ESI + 0xeac]
//   0x00c249e7 SUB EAX,0x0     0x00c249ea JZ case_zero
//   0x00c249ec SUB EAX,0x1     0x00c249ef JZ case_one
//   0x00c249f1 SUB EAX,0x1     0x00c249f4 JNZ default
//   0x00c249f6 OR EDI,0x1000   case_two
//
// with the sibling cases ORing 0x8 and 0x40 into the same EDI accumulator, so
// this field selects a bit group in a packed flag word. The enum member names
// are NOT recoverable from the binary and the owning class is not located, so
// none is asserted.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

std::int32_t get_field_eac_00c0c2f0(const OpaqueSimState* self) noexcept {
    return self->field_eac;
}

}  // namespace openspore::wave13_w1_core_b15
