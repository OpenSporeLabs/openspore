#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00c0c080 : 74 bytes, 36 instructions.
// __thiscall, one 4-byte stack argument, callee cleans it (RET 0x4 at
// 0x00c0c0be and 0x00c0c0c7). Returns the matching index in EAX, or the
// sentinel 0xffffffff built by OR EAX,0xffffffff at 0x00c0c0ba.
//  0x00c0c080..0x00c0c083: PUSH EBX / EBP / ESI / EDI
//  0x00c0c084: MOV EDI,ECX
//  0x00c0c086: MOV EAX,dword ptr [EDI]
//  0x00c0c088: MOV EDX,dword ptr [EAX + 0xb0]      ; slot +0xb0, no argument
//  0x00c0c08e: CALL EDX                            ; -> element count
//  0x00c0c090: MOV EBX,EAX
//  0x00c0c092: XOR ESI,ESI                         ; i = 0
//  0x00c0c094: TEST EBX,EBX
//  0x00c0c096: JBE 0x00c0c0b7                      ; count <= 0 -> -1
//  0x00c0c098: MOV EBP,dword ptr [ESP + 0x14]      ; the stack argument
//  0x00c0c09c: LEA ESP,[ESP]                       ; no-op
//  0x00c0c0a0: MOV EAX,dword ptr [EDI]
//  0x00c0c0a2: MOV EDX,dword ptr [EAX + 0xb4]      ; slot +0xb4
//  0x00c0c0a8: PUSH ESI                            ; i
//  0x00c0c0a9: MOV ECX,EDI                         ; receiver
//  0x00c0c0ab: CALL EDX
//  0x00c0c0ad: CMP dword ptr [EAX + 0x8],EBP
//  0x00c0c0b0: JZ 0x00c0c0c1                        ; hit -> return i
//  0x00c0c0b2: INC ESI
//  0x00c0c0b3: CMP ESI,EBX
//  0x00c0c0b5: JC 0x00c0c0a0                       ; signed: i < count
//  0x00c0c0b7..0x00c0c0be: POP EDI/ESI/EBP/EBP,
//        OR EAX,0xffffffff ; POP EBX ; RET 0x4
//  0x00c0c0c1..0x00c0c0c7: POP EDI ; MOV EAX,ESI ; POP ESI/EBP/EBX ; RET 0x4
//
// Sibling users of the same -1 sentinel, in the same code region:
//  0x00c0c140: if (this->find(0x0d) == -1) this->find(0x52);
//  0x00c0c160: if (this->find(0x27) == -1) this->find(0x50);
//  0x00c1aee5 / 0x00c1aef1: the 0x0d / 0x52 pair inlined
std::int32_t SimEntityCollection_FindIndexById_00c0c080(
    OpaqueSimEntityCollection* collection, std::int32_t id);

}  // namespace openspore::reconstruction::wave13_w1_core_b10
