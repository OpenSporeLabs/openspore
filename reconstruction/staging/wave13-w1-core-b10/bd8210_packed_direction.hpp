#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00bd8210 : 31 bytes, 8b 01 8b 40 58 83 ec 0c 8d 14 24 52 ff d0
//              50 e8 2c 51 f6 ff 8b c8 e8 65 03 fb ff 83 c4 0c c3
// __thiscall, no stack argument, bare RET at 0x00bd822e.
//  0x00bd8210: MOV EAX,dword ptr [ECX]          ; vtable
//  0x00bd8212: MOV EAX,dword ptr [EAX + 0x58]   ; slot +0x58
//  0x00bd8215: SUB ESP,0xc                      ; 12-byte local
//  0x00bd8218: LEA EDX,[ESP]
//  0x00bd821b: PUSH EDX                         ; &local
//  0x00bd821c: CALL EAX
//  0x00bd821e: PUSH EAX                         ; pointer to 3 floats
//  0x00bd821f: CALL 0x00b3d350                  ; returns [0x0167eaf8]
//  0x00bd8224: MOV ECX,EAX
//  0x00bd8226: CALL 0x00b88590                  ; RET 4
//  0x00bd822b: ADD ESP,0xc
//  0x00bd822e: RET
// The 16-bit index produced by 0x00b88590 is returned unchanged in EAX: at
// 0x00d043c9 the caller stores it and at 0x00d0441a / 0x00d0443f compares it
// for equality against a stored baseline.
std::uint16_t DirectionCarrier_GetPackedDirection_00bd8210(
    OpaqueDirectionCarrier* carrier);

}  // namespace openspore::reconstruction::wave13_w1_core_b10
