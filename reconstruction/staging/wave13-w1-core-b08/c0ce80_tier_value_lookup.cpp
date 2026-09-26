// 0x00c0ce80 — SimCore_00c0ce80_tier_value_lookup
//
// 63 instructions, 204 bytes, 4 direct callees, 1 virtual call.
//
// ABI, read from the disassembly rather than the decompiler's prototype:
//   0x00c0ce80 PUSH ECX
//   0x00c0ce81 MOV EAX,[ESP + 0x8]      <- first stack dword, into EAX
//   0x00c0ce91 TEST EAX,EAX              <- tested as an INTEGER, not a float
//   0x00c0ce36 RET 0x8                   <- callee pops two stack words
// Ghidra types the first stack argument as float because 0x00c0cf24 later
// loads the same word with FLD. Both readings are real: the word is tested as
// an integer at 0x00c0ce91 and reinterpreted as a float at 0x00c0cf24.
//
// The PUSH ECX slot is reused: 0x00c0ce8b stores 0.0f over the saved `this`
// (safe, EDI already holds it) and that slot becomes the single float local
// which holds, in turn, the base value and then the neighbour value. The store
// at 0x00c0cef6 is a dead write of base over base; it matters because the
// branch at 0x00c0cf0e can skip the neighbour load and leave base in place.

#include <cstring>

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" float SimCore_00c0ce80_tier_value_lookup(OpaqueC0ce80Tiers* self, std::uint32_t tier,
                                                    std::uint32_t use_base_offset);

extern "C" float SimCore_00c0ce80_tier_value_lookup(OpaqueC0ce80Tiers* self, std::uint32_t tier,
                                                    std::uint32_t use_base_offset) {
    // 0x00c0ce85 XORPS XMM0,XMM0 / 0x00c0ce8b MOVSS [ESP+4],XMM0
    float slot = 0.0f;

    // 0x00c0ce91 TEST EAX,EAX ; 0x00c0ce93 JZ 0x00c0cf43 -> FLD the zero slot
    if (tier == 0u) {
        return slot;
    }

    // 0x00c0cea2 CALL 0x00c0ce30 with (ECX=this, tier, use_base_offset); it
    // ends in RET 0x8 so it consumes both pushed words.
    const std::int32_t index = port_00c0ce30_clamp_index(self, tier, use_base_offset);

    // 0x00c0cea9 CALL 0x00b5b800 ; 0x00c0ceae CMP EAX,0x1654C10 ; JNZ
    if (port_00b5b800_lookup_sentinel() == k_sentinel_01654c10) {
        // 0x00c0ceb5 PUSH ESI ; PUSH EDI ; CALL 0x00c03260 (bare RET, so the two
        // words survive) ; MOV ECX,EAX ; CALL 0x00f31500 (RET 0x8, pops them)
        void* singleton = port_00c03260_lazy_singleton();
        slot = port_00f31500_table_element(singleton, self, index);
    } else {
        // 0x00c0cec9 MOVSS XMM0,[ESI*0x4 + 0x15D9650]
        slot = g_table_015d9650[index];
    }

    // 0x00c0ced8 MOV EDX,[EDI + 0xC0] ; MOV EAX,[EDX + 0x58] ;
    // 0x00c0cee1 LEA ECX,[EDI + 0xC0] ; CALL EAX ; TEST AL,AL ; JZ 0x00c0cf39
    if (self->f_C0->slots[0x58 / sizeof(C0ce80Vslot)](self) == 0u) {
        // 0x00c0cf39 FLD float ptr [ESP + 0x8]
        return slot;
    }

    // 0x00c0cef3 LEA ECX,[ESI + 0x1] ; 0x00c0cefc CMP ECX,0x6 ; JNC
    // 0x00c0cf01 MOVSS XMM0,[ESI*0x4 + 0x15D9654]   (= table[index + 1])
    // 0x00c0cf0c TEST ESI,ESI ; JBE                  (index == 0 keeps base)
    // 0x00c0cf10 MOVSS XMM0,[ESI*0x4 + 0x15D964C]   (= table[index - 1])
    // 0x00c0cf19 MOVSS [ESP + 0x10],XMM0             (overwrites the base slot)
    const std::uint32_t next = static_cast<std::uint32_t>(index) + 1u;
    if (next < 6u) {
        slot = g_table_015d9650[index + 1];
    } else if (index > 0) {
        slot = g_table_015d9650[index - 1];
    }

    // 0x00c0cf1f FLD [ESP+0x8]  (slot)
    // 0x00c0cf24 FLD [ESP+0xC]  (the first stack word, the raw `tier` dword)
    // 0x00c0cf29 FSUBR ST0,ST1  => ST0 = tier_as_float - slot
    // 0x00c0cf2b FABS ; 0x00c0cf2d FMUL float ptr [0x01471064] (0.5f)
    // 0x00c0cf33 FADDP          => slot + 0.5f * |tier - slot|
    float tier_as_float = 0.0f;
    std::memcpy(&tier_as_float, &tier, sizeof(tier_as_float));
    const float delta = tier_as_float - slot;
    return slot + g_scale_01471064 * (delta < 0.0f ? -delta : delta);
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
