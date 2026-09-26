// 0x00b8d9b0 — cPlanetRecord two-tier context resolver.
//
// Original bytes (ghidra_read_memory 0x00b8d9b0,64 =
// 56 8b f1 57 56 e8 e6 f8 fa ff 8b c8 e8 1f c0 02 00 8b f8 85 ff 75 1c
// 56 e8 23 e0 45 00 8b c8 e8 4c 08 46 00 85 c0 74 09 5f 8b c8 5e
// e9 3f d8 0b 00 8b c7 5f 5e c3):
//   0x00b8d9b0  56             PUSH ESI
//   0x00b8d9b1  8b f1          MOV ESI, ECX
//   0x00b8d9b3  57             PUSH EDI
//   0x00b8d9b4  56             PUSH ESI                ; arg for 0x00b3d2a0's chain
//   0x00b8d9b5  e8 e6f8faff    CALL 0x00b3d2a0         ; -> [0x0167EAE4]
//   0x00b8d9ba  8b c8          MOV ECX, EAX
//   0x00b8d9bc  e8 1fc00200    CALL 0x00bb99e0         ; RET 4: pops the PUSH ESI
//   0x00b8d9c1  8b f8          MOV EDI, EAX
//   0x00b8d9c3  85 ff          TEST EDI, EDI
//   0x00b8d9c5  75 1c          JNZ 0x00b8d9e3
//   0x00b8d9c7  56             PUSH ESI                ; arg for 0x00feb9f0's chain
//   0x00b8d9c8  e8 23e04500    CALL 0x00feb9f0         ; -> [0x016DAC64], plain RET
//   0x00b8d9cd  8b c8          MOV ECX, EAX
//   0x00b8d9cf  e8 4c084600    CALL 0x00fee220         ; RET 4: pops the PUSH ESI
//   0x00b8d9d4  85 c0          TEST EAX, EAX
//   0x00b8d9d6  74 09          JZ 0x00b8d9e1
//   0x00b8d9d8  5f             POP EDI
//   0x00b8d9d9  8b c8          MOV ECX, EAX
//   0x00b8d9db  5e             POP ESI
//   0x00b8d9dc  e9 3fd80b00    JMP 0x00c4b220          ; tail transfer
//   0x00b8d9e1  8b c7          MOV EAX, EDI           ; EDI == 0 here
//   0x00b8d9e3  5f             POP EDI
//   0x00b8d9e4  5e             POP ESI
//   0x00b8d9e5  c3             RET
//
// Stack discipline, verified against the callees' own terminators:
//   0x00bb99e0 ends in RET 0x4 and 0x00fee220 ends in RET 0x4 (both read live
//   with ghidra_disassemble_function), so each consumes the single PUSH that
//   precedes it.  Every path therefore leaves a balanced stack and 0x00b8d9b0
//   itself takes no stack argument and returns with a bare RET.
//
// The receiver is Simulator::cPlanetRecord.  0x00ce6950 inside 0x00bb99e0
// returns *(param_1 + 0x184), which the SDK places at
// /* 184h */ PlanetID mKey, and Spore-ModAPI
// "Spore ModAPI/Spore/Simulator/StarID.h:68-79" defines PlanetID as a single
// uint32 packing ((planetIndex & 0xFF) << 24) | (starID & 0x00FFFFFF).  The
// same record's 0x28/0x2C are read by the sibling 0x00b8d9f0, matching
// /* 28h */ PlanetType mType and /* 2Ch */ int mFlags.
//
// TIER 1 (0x00bb99e0), read from its disassembly:
//   key      = record->mKey                              (0x00bb99e5/e9)
//   node     = lower_bound(manager->registry, key)       (0x00bb99fc/a02)
//   if (node == manager->registry_end) return 0          (0x00bb9a0b..a13, a5b..a60)
//   *slot    = node->value (node+0x14)                   (0x00bb9a16)
//   refresh  = port_00bb7940(node->value, 0)             (0x00bb9a22)
//   if (*slot changed) propagate *slot to the context    (0x00bb9a27..a4c)
//   return *slot                                        (0x00bb9a51)
// TIER 2 (only when tier 1 returned 0):
//   context  = port_00fee220([0x016DAC64], record)       (0x00b8d9c8/cf)
//   if (context == 0) return 0                           (0x00b8d9d4/d6/e1)
//   return tail port_00c4b220(context)                   (0x00b8d9dc)
// where 0x00c4b220 (ghidra_disassemble_function) is
//   slot = (uint*)((char*)context + 0x1F4); 0x00b3d2a0(); port_00bb7940(slot,0);
//   return *slot;
// and 0x00fee220 pushes 0x2AA5ADA, which Spore-ModAPI
// "Spore ModAPI/Spore/Simulator/cMission.h:49" declares as
// `static const uint32_t TYPE = 0x2AA5ADA;`, then filters the type list with a
// virtual call at vtable slot +0x0C carrying 0x463329E and the predicate
// `[record+0x15] != 0 || [entry+0x13C] == record`.
//
// The three callees' return domains are NOT established, so the value is
// modelled as an opaque context handle.  Callers only null-test it:
//   0x00b8d9f0 0x00b8da09 -> TEST EAX,EAX ; JNZ (bail out of a visibility test)
//   0x00c44d00 0x00c44d16 -> TEST EAX,EAX ; JNZ
//   0x00bba870 0x00bba885 -> loop over a pointer array, return true on first hit

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Resolves the live simulation context that owns `record`, or 0.
//
// Tier 1: keyed lookup of record->mKey in the global manager's ordered
// registry, refreshing the mapped cache slot in place.
// Tier 2: only when tier 1 yields nothing, find the currently active mission
// context that claims this record and resolve its lazily-populated slot at
// +0x1F4.
std::uint32_t SimCore_00b8d9b0_resolvePlanetContext(PlanetRecord* record) {
    // 0x00b8d9b5: the manager singleton; 0x00b8d9bc: keyed resolve, and the
    // callee's RET 4 consumes the PUSH ESI at 0x00b8d9b4.
    auto* manager = reinterpret_cast<OpaqueManager_EAE4*>(getGlobalEAE4());
    const std::uint32_t tier1 = port_00bb99e0_resolveByPlanetId(manager, record);

    // 0x00b8d9c3 TEST EDI,EDI / 0x00b8d9c5 JNZ 0x00b8d9e3: a non-null tier-1
    // answer short-circuits straight to the return, skipping tier 2 entirely.
    if (tier1 != 0u) {
        return tier1;
    }

    // 0x00b8d9c8: second global; 0x00b8d9cf: active-mission search, whose
    // RET 4 consumes the PUSH ESI at 0x00b8d9c7.
    const std::uint32_t context = port_00fee220_findActiveMissionContext(getGlobalDAC64(), record);

    // 0x00b8d9d4 TEST EAX,EAX / 0x00b8d9d6 JZ 0x00b8d9e1, where 0x00b8d9e1
    // is MOV EAX,EDI and EDI is provably 0 on this path.
    if (context == 0u) {
        return 0u;
    }

    // 0x00b8d9d8..0x00b8d9dc: pop both saved registers, load ECX with the
    // context and tail-transfer to 0x00c4b220.
    return port_00c4b220_resolveSlot1F4(context);
}

}  // namespace sim_core_b06
