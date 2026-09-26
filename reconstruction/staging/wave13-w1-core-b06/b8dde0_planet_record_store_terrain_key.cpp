// 0x00b8dde0 — cPlanetRecord::mGeneratedTerrainKey, change-checked store.
//
// Original bytes (ghidra_read_memory 0x00b8dde0,80 =
// 8b 44 24 04 8b 10 3b 91 a4 01 00 00 75 16 8b 50 04 3b 91 a8 01 00 00
// 75 0b 8b 50 08 3b 91 ac 01 00 00 74 1a 8b 10 89 91 a4 01 00 00
// 8b 50 04 89 91 a8 01 00 00 8b 40 08 89 81 ac 01 00 00 c2 08 00 cc ...):
//   0x00b8dde0  8b 44 24 04     MOV EAX, dword ptr [ESP + 0x4]
//   0x00b8dde4  8b 10           MOV EDX, dword ptr [EAX]
//   0x00b8dde6  3b 91 a4010000  CMP EDX, dword ptr [ECX + 0x1A4]
//   0x00b8ddec  75 16           JNZ 0x00b8de04
//   0x00b8ddee  8b 50 04        MOV EDX, dword ptr [EAX + 0x4]
//   0x00b8ddf1  3b 91 a8010000  CMP EDX, dword ptr [ECX + 0x1A8]
//   0x00b8ddf7  75 0b           JNZ 0x00b8de04
//   0x00b8ddf9  8b 50 08        MOV EDX, dword ptr [EAX + 0x8]
//   0x00b8ddfc  3b 91 ac010000  CMP EDX, dword ptr [ECX + 0x1AC]
//   0x00b8de02  74 1a           JZ 0x00b8de1e
//   0x00b8de04  8b 10           MOV EDX, dword ptr [EAX]
//   0x00b8de06  89 91 a4010000  MOV dword ptr [ECX + 0x1A4], EDX
//   0x00b8de0c  8b 50 04        MOV EDX, dword ptr [EAX + 0x4]
//   0x00b8de0f  89 91 a8010000  MOV dword ptr [ECX + 0x1A8], EDX
//   0x00b8de15  8b 40 08        MOV EAX, dword ptr [EAX + 0x8]
//   0x00b8de18  89 81 ac010000  MOV dword ptr [ECX + 0x1AC], EAX
//   0x00b8de1e  c2 08 00        RET 0x8
//
// The comparison chain short-circuits: the store block is entered from any of
// three JNZ/JZ targets, and it is SKIPPED entirely (falling to 0x00b8de1e)
// only when all three dwords already match.  The store is unconditional once
// entered: a partially-matching key still rewrites all three words, including
// the ones that already agreed.  The `MOV EAX,[EAX+0x8]` at 0x00b8de15 instead
// of a third MOV EDX is a peephole, not a semantic difference.
//
// The receiver is Simulator::cPlanetRecord and the target is
// cPlanetRecord::mGeneratedTerrainKey:
//   * Spore-ModAPI "Spore ModAPI/Spore/Simulator/cPlanetRecord.h" declares
//     /* 184h */ PlanetID mKey; /* 1A4h */ ResourceKey mGeneratedTerrainKey;
//     with ASSERT_SIZE(cPlanetRecord, 0x1B0).
//   * "Spore ModAPI/Spore/ResourceKey.h" defines ResourceKey as three uint32
//     (instanceID, typeID, groupID) => exactly the 0xC bytes written here, and
//     asserts sizeof 0xC by construction.
//   * 0x00b8d8e0 is `MOV EAX, param_1 + 0x1A4` — the addressor for that member,
//     and callers 0x00ba606c / 0x00ba60ff pair a load from it with this store.
//   * 0x00b8dd60, the paired getter immediately below this body, zeroes
//     [this+0x1A4..0x1AC] and treats the first dword as a "materialise me"
//     sentinel, which is why the write here is worth skipping when unchanged.
//   * caller 0x00bbac80 sets mPlanets[0]'s key from the manager returned by
//     getGlobalEAE4(), reading cStarRecord::mStarterWorldID at +0x58 and
//     cStarRecord::mFlags bit 15 at +0x5C on the way.
//   * caller 0x00c713c0 passes the literal 0 as the second argument, which
//     selects the "no change" (back-append) direction of the owner's twin.
//
// NOTE: this is NOT the SDK's `cPlanetRecord::SetGeneratedTerrainKey`, which is
// a plain unconditional `mGeneratedTerrainKey = key;`.  The change check is
// real and observable, so the SDK method name is recorded as a candidate only.

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Copies a 12-byte ResourceKey into record->mGeneratedTerrainKey, but only
// when at least one of its three dwords differs from what is already stored.
//
// One callee-cleaned stack dword (`RET 0x8`), receiver in ECX, no frame, no
// callees, no return value.
void SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(PlanetRecord* record,
                                                        const PlanetRecord::ResourceKey& key) {
    PlanetRecord::ResourceKey& slot = record->mGeneratedTerrainKey;

    // 0x00b8dde4..0x00b8de02: short-circuiting three-way compare, all equal
    // falls through to 0x00b8de1e (RET) with nothing written.
    if (key.instanceID == slot.instanceID && key.typeID == slot.typeID &&
        key.groupID == slot.groupID) {
        return;
    }

    // 0x00b8de04..0x00b8de18: all three words are rewritten, not just the
    // differing ones.
    slot.instanceID = key.instanceID;  // 0x00b8de06
    slot.typeID = key.typeID;          // 0x00b8de0f
    slot.groupID = key.groupID;        // 0x00b8de18
}

}  // namespace sim_core_b06
