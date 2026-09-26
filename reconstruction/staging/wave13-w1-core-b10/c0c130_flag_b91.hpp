#pragma once

#include "b10_observed_types.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

// 0x00c0c130 : 7 bytes, 8a 81 b1 0b 00 00 / c3
//  0x00c0c130: MOV AL,byte ptr [ECX + 0xbb1]
//  0x00c0c136: RET
// __thiscall, no stack argument, bare RET, byte-sized result in AL only (bits
// 8..31 of EAX are left as the caller left them).
// Every consumer inspected treats the answer as a boolean:
//  0x00c0395d: CALL 0x00c0c130 ; 0x00c03962 TEST AL,AL ; 0x00c03964 JZ
//  0x00c03b17: CALL 0x00c0c130 ; 0x00c03b1c TEST AL,AL ; 0x00c03b1e JNZ
// The adjacent sibling 0x00c0c120 reads the byte at +0xbb0 with the same shape,
// so +0xbb0 and +0xbb1 are two separate byte flags of the same receiver.
std::uint8_t SimEntityCollection_GetFlagB91_00c0c130(
    OpaqueSimEntityCollection* collection);

}  // namespace openspore::reconstruction::wave13_w1_core_b10
