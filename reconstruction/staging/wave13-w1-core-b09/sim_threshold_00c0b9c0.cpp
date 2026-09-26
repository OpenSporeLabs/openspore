// 0x00c0b9c0 - 7-byte float field accessor.
//
// Body span 0x00c0b9c0..0x00c0b9c6, 7 bytes, 2 instructions, read from the live
// disassembly and confirmed byte for byte by a live memory read
// (d9 81 bc 0b 00 00 c3).
//
// ABI: __thiscall. ECX is the receiver and is the ONLY register read. There is
// no stack argument, no frame, no callee, no global and no side effect. The
// bare RET proves the caller owns all stack cleanup.
//
// Return: an IEEE-754 single loaded on the x87 stack in ST(0). The body never
// executes FSTP, so the caller receives it on the x87 stack. This is confirmed
// by every inspected caller, which either FSTPs the result into a local or feeds
// it straight into FCOMIP against a global float.
//   0x00c02dfe  CALL 0x00c0b9c0 ; FLD float ptr [0x01687a10] ; FCOMIP ST0,ST1
//   0x00c22b76  CALL 0x00c0b9c0 ; FSUBR float ptr [0x01687a00]
//   0x00b3e3e0 is not a caller, but the parallel shape is FSTP dword ptr [ESP+N]
//
// Classification BOUNDED_SEMANTIC: the body, the ABI, the offset and the return
// form are all OBSERVED, but the owner class and the meaning of the field are
// not established. What the callers DO establish is that the value is used as a
// tuning threshold or limit compared against tuning globals (0x01687a00,
// 0x01687a0c, 0x01687a10, 0x01687a14) and against a sub-object's own value
// (0x00c22b40..0x00c22b58).

#include "sim_threshold_00c0b9c0.hpp"

extern "C" B09_THISCALL float SimThreshold_00c0b9c0_reconstruct(OpaqueThresholdOwnerObserved* self) {
    // 0x00c0b9c0: FLD dword ptr [ECX + 0xbbc] leaves the value in ST(0);
    // 0x00c0b9c6: RET returns it on the x87 stack.
    return self->threshold_bbc;
}
