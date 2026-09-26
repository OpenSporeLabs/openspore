// 0x00b8d970 - 9-byte single-bit extractor from a flag word.
//
// Body span 0x00b8d970..0x00b8d978, 9 bytes, 4 instructions, read from the live
// disassembly and confirmed byte for byte by a live memory read
// (8b 41 2c c1 e8 08 24 01 c3).
//
// ABI: __thiscall. ECX is the receiver, EDX is scratch. No stack argument, no
// frame, no callee, no global, no side effect, bare RET.
//
// Return: a FULL dword in EAX, exactly 0 or exactly 1. SHR EAX,8 clears bits
// 0..7 and bit 31; AND AL,1 then clears bits 8..31, so the whole register ends
// up 0 or 1 and the upper three bytes are provably zero.
//
// NOTE ON THE DECOMPILER: Ghidra renders this as
// "*(uint *)(param_1 + 0x2c) >> 8 & 0xffffff01", which is wrong - it models
// the AND as a 0xffffff01 mask on the full dword. The disassembly proves the
// mask is 1 and that it applies to AL only. The reconstruction follows the
// disassembly.
//
// Classification BOUNDED_SEMANTIC: the body, the ABI, the offset, the shift,
// the mask and the return width are OBSERVED, but the owner class and the
// meaning of the flag word are not established. The bit number 8 and the
// bitfield nature of +0x2c ARE established, by the inlined duplicate at
// 0x00b8d9ff..0x00b8da12 which performs the identical SHR/AND on the same field
// and then separately tests bit 0x800 of it.

#include "sim_flagbit_00b8d970.hpp"

extern "C" B09_THISCALL std::uint32_t SimFlagBit_00b8d970_reconstruct(OpaqueFlagWordOwnerObserved* self) {
    // 0x00b8d970 MOV EAX,[ECX + 0x2c] ; 0x00b8d973 SHR EAX,8 ;
    // 0x00b8d976 AND AL,1        ; 0x00b8d978 RET
    return (self->flags_2c >> 8) & 1u;
}
