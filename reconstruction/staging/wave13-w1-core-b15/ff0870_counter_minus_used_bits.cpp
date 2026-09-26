// 0x00ff0870 — 0x00ff0870..0x00ff08af, 21 instructions, 64 bytes.
//
//   0x00ff0870 MOVZX EAX,byte ptr [ECX + 0x28]
//   0x00ff0874 MOV EDX,EAX
//   0x00ff0876 SHR EDX,0x1
//   0x00ff0878 AND EDX,0x55555555
//   0x00ff087e SUB EAX,EDX
//   0x00ff0880 MOV EDX,EAX
//   0x00ff0882 PUSH ESI
//   0x00ff0883 SHR EDX,0x2
//   0x00ff0886 AND EAX,0x33333333
//   0x00ff088b AND EDX,0x33333333
//   0x00ff0891 ADD EDX,EAX
//   0x00ff0893 MOV EAX,dword ptr [ECX + 0x24]
//   0x00ff0896 MOV ESI,EDX
//   0x00ff0898 SHR ESI,0x4
//   0x00ff089b ADD ESI,EDX
//   0x00ff089d AND ESI,0xf0f0f0f
//   0x00ff08a3 IMUL ESI,ESI,0x1010101
//   0x00ff08a9 SHR ESI,0x18
//   0x00ff08ac SUB EAX,ESI
//   0x00ff08ae POP ESI
//   0x00ff08af RET
//
// __thiscall, 32-bit signed return in EAX, receiver in ECX, zero stack
// arguments, bare RET. PUSH ESI / POP ESI is a scratch save only, so the frame
// is balanced and the caller owns cleanup.
//
// This is the textbook SWAR population count, step for step:
//   x        = zero-extended byte at +0x28
//   x - (x>>1 & 0x55555555)              2-bit pair counts
//   (u>>2 & 0x33333333) + (u & 0x33333333) 4-bit nibble counts
//   (v>>4 + v) & 0x0f0f0f0f, then *0x01010101 >> 24   byte counts, summed
// and the result is subtracted from the 32-bit counter loaded from +0x24.
// Because the input is a zero-extended byte the count is over exactly the eight
// bits of that byte, so the return value lies in [counter-8, counter].
//
// Two sibling routines in the same 0x00ff0700..0x00ff0870 block corroborate
// both fields and the popcount shape:
//
//   0x00ff0760  the same SWAR sequence with no MOV EAX,[ECX+0x24]; it returns
//               popcount(byte[+0x28]) alone. Seventeen instructions, bare RET.
//   0x00ff07e0  BL = byte[+0x28]; AL = (BL-1) & BL; stores AL back to +0x28;
//               computes popcount(AL) and popcount(BL) with two more SWAR
//               runs; ESI = popcount(BL) - popcount(AL); if ESI > 0 then
//               DEC dword ptr [ECX + 0x24].
//               i.e. it clears the lowest set bit of the mask and decrements
//               the counter only when a bit was actually set.
//
// So +0x24 is a counter that this mutator drives down and +0x28 is an 8-bit
// occupancy mask, and this function reports counter-minus-mask. A third
// routine in the block, 0x00ff07a0, walks a 7-byte-stride array at
// [+0x7c, +0x80) on the same receiver.
//
// The nine recorded call sites pass the receiver loaded out of a vector of
// pointers, e.g. 0x00c701dd/0x00c701e0 (`MOV ECX,dword ptr [EDX + EDI*0x4]`
// then the call), and consume the answer three different ways:
//   0x00c701e5  CMP EAX,0x1 / JG  -> a search that stops once the value is
//                1 or less, so 0 and 1 are the two distinguished answers
//   0x00c70354  ADD EBP,EAX       -> accumulated into a running total
//   0x00c703e9  ADD dword ptr [ECX],EAX -> accumulated into an out-parameter
//   0x00bbe7c9  the answer is added to the answer of sibling 0x00ff0760 on the
//               same receiver before being compared against a third value
//
// What +0x24 counts in absolute terms, what the 7-byte records at +0x7c are,
// and which class owns the object are NOT established. No vtable holds this
// address: the only references to 0x00ff0870 are nine CALL xrefs and no DATA
// reference.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

// The SWAR population count, reproducing the exact mask/shift sequence the
// binary uses so the emitted code has a chance to match instruction for
// instruction. The argument is a value already zero-extended to 32 bits.
inline std::uint32_t popcount32_swar(std::uint32_t x) noexcept {
    x = x - ((x >> 1) & 0x55555555u);
    x = (x >> 2) + (x & 0x33333333u);
    x = (x >> 4) + (x & 0x0f0f0f0fu);
    x = (x * 0x01010101u) >> 24;
    return x;
}

std::int32_t counter_minus_used_bits_00ff0870(const OpaqueCounter* self) noexcept {
    return static_cast<std::int32_t>(static_cast<std::uint32_t>(self->counter_24) -
                                     popcount32_swar(static_cast<std::uint32_t>(self->mask_28)));
}

}  // namespace openspore::wave13_w1_core_b15
