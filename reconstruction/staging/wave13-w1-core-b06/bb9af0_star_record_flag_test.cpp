// 0x00bb9af0 — cStarRecord flag-mask predicate.
//
// Original bytes (ghidra_read_memory 0x00bb9af0,32 =
// 8b 41 5c 23 44 24 04 f7 d8 1b c0 f7 d8 c2 04 00 | 80 7c 24 08 00 ...):
//   0x00bb9af0  8b 41 5c        MOV EAX, dword ptr [ECX + 0x5C]
//   0x00bb9af3  23 44 24 04     AND EAX, dword ptr [ESP + 0x4]
//   0x00bb9af7  f7 d8           NEG EAX
//   0x00bb9af9  1b c0           SBB EAX, EAX
//   0x00bb9afb  f7 d8           NEG EAX
//   0x00bb9afd  c2 04 00        RET 0x4
//
// NEG/SBB/NEG is the standard MSVC (x != 0) -> 0/1 idiom: NEG sets CF from
// the operand's sign, SBB EAX,EAX yields 0 or -1, the final NEG yields 0 or 1.
// So the result is exactly `(star->mFlags & mask) != 0`, never a mask value and
// never a negative number.  EAX is 0 or 1 on exit; bits 8..31 are zero.
//
// The receiver is Simulator::cStarRecord.  Spore-ModAPI
// "Spore ModAPI/Spore/Simulator/cStarRecord.h" declares `/* 5Ch */ int mFlags;`
// and five independent siblings in the same 0x00bb9a60-0x00bb9b40 run land on
// exactly the SDK offsets around it:
//   0x00801920  MOV EAX,[param_1 + 0x48]  -> /* 48h */ StarType mType
//   0x00bb9ae0  MOV EAX,[ECX + 0x4C]     -> /* 4Ch */ TechLevel mTechLevel
//   0x00bb9ad0  MOV [ECX + 0x4C],EAX     -> setter for the same
//   0x00bb9b20  MOV EAX,[ECX + 0x50]     -> /* 50h */ bool field_50
//   0x00bb9b80  MOV EAX, param_1 + 0x74  -> /* 74h */ mCitizenSpeciesKey
//   0x00bbaa60  *(int *)(param_1 + 0x84) -> /* 84h */ eastl::vector mPlanets
// and 0x00bba900 (which Ghidra already names
// Simulator__cStarRecord__GetPlanetRecords) reads `[cStarRecord+0x5C] >> 0xC`.
//
// The paired mutator is 0x00bb9b00, sixteen bytes later:
//   0x00bb9b00..0x00bb9b1c  set-or-clear `mask` in [this+0x5C] depending on a
//   trailing char argument, and 0x00bb9b30 forces bit 13 with
//   `[this+0x5C] & 0xFFFFBFFF | 0x2000`, which independently confirms the field
//   is a bit mask rather than a scalar.

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Returns true when any bit selected by `mask` is set in cStarRecord::mFlags.
//
// One callee-cleaned stack dword (`RET 0x4`), receiver in ECX, result in AL.
// Observed masks at callsites are all single bits: 0x1 (0x00bb2273), 0x2
// (0x00bb20e6, 0x00bb2266), 0x4 (0x00bb20d9), 0x100 (0x00b9356d) and 0x20000
// (0x00ba6c3e).  The AND is a full dword mask, so multi-bit masks are also
// correct; nothing in the body restricts the argument to one bit.
bool SimCore_00bb9af0_testStarRecordFlags(const StarRecord* star, std::uint32_t mask) {
    // 0x00bb9af0: MOV EAX,[ECX + 0x5C]
    const std::uint32_t flags = star->mFlags;
    // 0x00bb9af3: AND EAX,[ESP + 0x4]
    const std::uint32_t selected = flags & mask;
    // 0x00bb9af7: NEG EAX ; 0x00bb9af9: SBB EAX,EAX ; 0x00bb9afb: NEG EAX
    // (selected != 0) ? 1 : 0, written so the 0/1 domain is explicit.
    return selected != 0u;
}

// Paired mutator observed at 0x00bb9b00, declared for the model's sake only.
// It is NOT this batch's target; its body was read (ghidra_decompile_function
// 0x00bb9b00) and is reproduced as a contract, not claimed as reconstructed.
void SimCore_00bb9b00_setStarRecordFlags(StarRecord* star, std::uint32_t mask, bool set) {
    if (set) {
        star->mFlags = star->mFlags | mask;
    } else {
        star->mFlags = star->mFlags & ~mask;
    }
}

}  // namespace sim_core_b06
