#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00c485b0 : 8 bytes, 6a 02 e8 09 f7 ff ff / c3
//  0x00c485b0: PUSH 0x2
//  0x00c485b2: CALL 0x00c47cc0                  ; RET 4
//  0x00c485b7: RET
// ECX is never written, so the receiver of 0x00c47cc0 is the receiver of
// 0x00c485b0. The push of 2 is consumed by 0x00c47cc0's own RET 4, so the
// trailing bare RET pops only the return address: the whole body is a tail
// call. 0x00c485b0 itself has no stack argument of its own.
//
// 0x00c47cc0, fully disassembled, is:
//  0x00c47cc0: MOV EAX,dword ptr [ESP + 0x4]     ; the new mode
//  0x00c47cc4: SUB ESP,0x40
//  0x00c47cc7: CMP dword ptr [ECX + 0x84],EAX
//  0x00c47ccd: JZ 0x00c47d6c                     ; already 2 -> no-op
//  0x00c47cd3: MOV dword ptr [ECX + 0x84],EAX
//  0x00c47cd9..0x00c47cf2: if [+0x14c] != [+0x150]:
//        word [+0x14c] = 0 ; [+0x150] = [+0x14c]
//  0x00c47cf8..0x00c47d11: if [+0x15c] != [+0x160]:
//        word [+0x15c] = 0 ; [+0x160] = [+0x15c]
//  0x00c47d17: CMP dword ptr [ECX + 0x84],0x3
//  0x00c47d1e: JNZ 0x00c47d6c                    ; 2 != 3 -> return here
//  0x00c47d20..0x00c47d67: the App::IAppSystem::Init(0x13eb844) state switch
//  0x00c47d6c: ADD ESP,0x40 ; RET 4
// With the constant 2 the state-switch block is statically unreachable, so the
// whole observable effect of 0x00c485b0 is: set +0x84 to 2 and clear the two
// wchar-terminated buffers that start at +0x14c and +0x15c.
void SimTokenOwner_SetMode2_00c485b0(OpaqueSimTokenOwner* owner);

}  // namespace openspore::reconstruction::wave13_w1_core_b10
