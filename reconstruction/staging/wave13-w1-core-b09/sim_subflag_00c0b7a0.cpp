// 0x00c0b7a0 - 19-byte boolean predicate on a two-level sub-object field.
//
// Body span 0x00c0b7a0..0x00c0b7b2, 19 bytes, 6 instructions, read from the
// live disassembly and confirmed byte for byte by a live memory read
// (8b 81 20 0b 00 00 33 c9 3b 88 0c 06 00 00 1b c0 f7 d8 c3).
//
// ABI: __thiscall. ECX is the receiver; it is clobbered by the XOR at
// 0x00c0b7a6, which is a compare-against-zero idiom, not a receiver use. No
// stack argument, no frame, no callee, no global, no side effect, bare RET.
//
// Return: a FULL dword in EAX, exactly 0 or exactly 1 - not just AL. The
// 0x00c0b7a6..0x00c0b7b0 sequence is the standard materialisation:
//   CMP ECX(0), [EAX + 0x60c]   ->  CF = ([EAX + 0x60c] != 0), unsigned
//   SBB EAX, EAX                ->  EAX = 0 - 0 - CF  =  0xFFFFFFFF or 0
//   NEG EAX                     ->  EAX = 1 or 0
// Both consumers shapes agree: 0x00ba2835 and 0x00d2c1e6 use TEST AL,AL while
// 0x00d2c164 uses MOVZX ESI,AL, so the low byte is the value and the upper three
// bytes are provably zero.
//
// Classification BOUNDED_SEMANTIC: the body, the ABI, both offsets, the
// polarity and the return width are OBSERVED, but the owner class and the
// meaning of the field at +0x60c are not established.
//
// NOT CLAIMED: the receiver is not null-checked and neither is sub_b20. The
// body dereferences sub_b20 + 0x60c unconditionally, so a null sub_b20 faults.
// The original does not guard that and neither does this reconstruction.

#include "sim_subflag_00c0b7a0.hpp"

extern "C" B09_THISCALL std::uint32_t SimSubFlag_00c0b7a0_reconstruct(
    OpaqueSubFlagOwnerObserved* self) {
    // 0x00c0b7a0: MOV EAX,dword ptr [ECX + 0xb20]
    OpaqueSubObjectB20Observed* sub = self->sub_b20;

    // 0x00c0b7a6 XOR ECX,ECX ; 0x00c0b7a8 CMP ECX,dword ptr [EAX + 0x60c]
    // 0x00c0b7ae SBB EAX,EAX ; 0x00c0b7b0 NEG EAX
    // The materialisation is written out rather than folded into a comparison so
    // that the return really is a full dword 0 or 1, matching the SBB/NEG pair:
    //   SBB EAX,EAX with EAX = 0 gives 0 or 0xFFFFFFFF, NEG then gives 1 or 0.
    const std::uint32_t value = sub->field_60c;
    const std::uint32_t all_ones = 0u - static_cast<std::uint32_t>(value != 0u);
    return 0u - all_ones;
}
