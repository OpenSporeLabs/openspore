// 0x00c0b780 — SimCore_00c0b780_sub_object_flag_608
//
// Body read live, 6 instructions, 19 bytes, no callees:
//
//   00c0b780  8B 81 20 0B 00 00   MOV EAX,dword ptr [ECX + 0xB20]
//   00c0b786  33 C9              XOR ECX,ECX
//   00c0b788  3B 88 08 06 00 00  CMP ECX,dword ptr [EAX + 0x608]
//   00c0b78E  1B C0              SBB EAX,EAX
//   00c0b790  F7 D8              NEG EAX
//   00c0b792  C3                 RET
//
// The XOR/CMP/SBB/NEG idiom is a branchless `!= 0`: CMP 0,mem sets CF iff the
// memory dword is unsigned-greater than 0, SBB EAX,EAX yields 0 or ~0, NEG maps
// ~0 to 1. Both EAX writes are 32-bit, so the answer is a full dword 0/1, not
// a byte in AL. Every one of the 18 recorded callsites tests AL.
//
// There is no null check on the sub-object at +0xB20. The invariant that the
// sub-object is non-null is a caller obligation, not a guard in this body.

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" std::uint32_t SimCore_00c0b780_sub_object_flag_608(OpaqueC0b780Owner* self);

extern "C" std::uint32_t SimCore_00c0b780_sub_object_flag_608(OpaqueC0b780Owner* self) {
    // MOV EAX,[ECX + 0xB20]
    const std::uint32_t sub = reinterpret_cast<std::uint32_t>(self->f_B20);
    // XOR ECX,ECX ; CMP ECX,[EAX + 0x608] ; SBB EAX,EAX ; NEG EAX
    return *reinterpret_cast<const std::uint32_t*>(sub + 0x608) != 0u ? 1u : 0u;
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
