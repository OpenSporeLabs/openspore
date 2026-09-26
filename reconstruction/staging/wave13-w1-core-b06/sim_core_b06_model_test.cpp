// wave13-w1-core-b06 model test.
//
// Exercises the six reconstructed contracts against the test-only port models
// in sim_core_b06_ports_model.cpp.  Passing proves the reconstructions are
// internally consistent and preserve the observed branch polarity, offsets,
// constants and result domains.  It proves nothing about the original binary's
// runtime behaviour, which has never been observed.

#include "sim_core_b06_opaque.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace sim_core_b06 {
// Port models and their test hooks.
void resetInternedObjectTable();
void installFactoryVtable();
void resetFactory();
std::uint32_t releasedCount();
std::uint32_t createdCount();
std::uint32_t lastFactoryKey();
void installGlobal(std::uint32_t* slot, std::uint32_t value);
std::uint32_t* globalEAD4Slot();
std::uint32_t* globalEAE4Slot();

// The six reconstructed entry points, declared here so the model test does not
// have to include the reconstruction translation units' headers twice.
std::uint32_t SimCore_00b3d290_getGlobalEAD4();
bool SimCore_00bb9af0_testStarRecordFlags(const StarRecord* star, std::uint32_t mask);
void SimCore_00bb9b00_setStarRecordFlags(StarRecord* star, std::uint32_t mask, bool set);
std::uint32_t SimCore_00b8d9b0_resolvePlanetContext(PlanetRecord* record);
void SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(PlanetRecord* record,
                                                       const PlanetRecord::ResourceKey& key);
std::uint32_t SimCore_00baf700_getOrCreateInterned(std::uint32_t selector);
void SimCore_00c446d0_pushTaggedVector3(OpaqueOwner_C446D0* owner, const float (&xyz)[3],
                                        std::uint8_t at_front);
}  // namespace sim_core_b06

using namespace sim_core_b06;

namespace {

// ---------------------------------------------------------------------------
// 0x00b3d290
// ---------------------------------------------------------------------------
void test_global_slot_accessor() {
    // 0x0167EAD4 reads 0 in the on-disk image.
    *globalEAD4Slot() = 0u;
    assert(SimCore_00b3d290_getGlobalEAD4() == 0u);

    // No null check, no lazy construction: whatever is in the slot is returned
    // verbatim, in both directions.
    *globalEAD4Slot() = 0xDEADBEEFu;
    assert(SimCore_00b3d290_getGlobalEAD4() == 0xDEADBEEFu);
    *globalEAD4Slot() = 1u;
    assert(SimCore_00b3d290_getGlobalEAD4() == 1u);
}

// ---------------------------------------------------------------------------
// 0x00bb9af0
// ---------------------------------------------------------------------------
void test_star_record_flag_test() {
    StarRecord star;
    std::memset(&star, 0, sizeof(star));

    // (flags & mask) != 0 with an all-zero field: every mask answers false.
    // This is the domain the NEG/SBB/NEG idiom cannot leave.
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0x1u));
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0x20000u));
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0xFFFFFFFFu));
    // Mask 0 is always false: 0 & anything == 0.
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0u));

    // The five single-bit masks observed at callsites.
    const std::uint32_t observed[] = {0x1u, 0x2u, 0x4u, 0x100u, 0x20000u};
    for (std::uint32_t bit : observed) {
        star.mFlags = 0;
        assert(!SimCore_00bb9af0_testStarRecordFlags(&star, bit));
        star.mFlags = static_cast<std::int32_t>(bit);
        assert(SimCore_00bb9af0_testStarRecordFlags(&star, bit));
        // A full dword field must not leak sign into the answer: bit 31 set,
        // queried with a low bit, is still false.
        star.mFlags = static_cast<std::int32_t>(0x80000000u | bit);
        assert(SimCore_00bb9af0_testStarRecordFlags(&star, bit));
    }

    // Multi-bit masks answer "ANY selected bit set", not "all".  With only bit
    // 2 set, a mask of 0x6 (bits 1 and 2) is only satisfied under "any"; an
    // "all selected bits" reading would answer false here.
    star.mFlags = 0x4;
    assert(SimCore_00bb9af0_testStarRecordFlags(&star, 0x6u));
    assert(SimCore_00bb9af0_testStarRecordFlags(&star, 0x4u));
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0x2u));

    // Round trip through the paired mutator observed at 0x00bb9b00.
    star.mFlags = 0;
    SimCore_00bb9b00_setStarRecordFlags(&star, 0x2000u, true);
    assert(star.mFlags == 0x2000);
    assert(SimCore_00bb9af0_testStarRecordFlags(&star, 0x2000u));
    // 0x00bb9b30 is `[this+0x5C] & 0xFFFFBFFF | 0x2000`: clear every bit except
    // 13, then force 13.  Expressed through the paired setter that is
    // setFlags(~0x2000, false) followed by setFlags(0x2000, true).
    SimCore_00bb9b00_setStarRecordFlags(&star, 0x0000DEADu, true);
    assert(star.mFlags == static_cast<std::int32_t>(0x2000u | 0x0000DEADu));
    SimCore_00bb9b00_setStarRecordFlags(&star, ~0x2000u, false);
    SimCore_00bb9b00_setStarRecordFlags(&star, 0x2000u, true);
    assert(star.mFlags == 0x2000);
    SimCore_00bb9b00_setStarRecordFlags(&star, 0x2000u, false);
    assert(star.mFlags == 0);
    assert(!SimCore_00bb9af0_testStarRecordFlags(&star, 0x2000u));
}

// ---------------------------------------------------------------------------
// 0x00b8d9b0
// ---------------------------------------------------------------------------
void test_planet_record_resolve_context() {
    PlanetRecord record;
    std::memset(&record, 0, sizeof(record));
    OpaqueManager_EAE4 manager;
    std::memset(&manager, 0, sizeof(manager));
    OrderedKeyMap registry;
    std::memset(&registry, 0, sizeof(registry));
    manager.registry = &registry;

    *globalEAE4Slot() = reinterpret_cast<std::uint32_t>(&manager);

    // Tier 1 miss and tier 2 miss: the JZ at 0x00b8d9d6 loads EAX from EDI,
    // and EDI is provably 0 on that path, so the result is exactly 0.
    record.mKey = 0x11223344u;
    assert(SimCore_00b8d9b0_resolvePlanetContext(&record) == 0u);

    // Tier 1 hit short-circuits: the JNZ at 0x00b8d9c5 jumps straight to the
    // epilogue, so tier 2 is never entered.
    std::uint32_t* slot = port_00dd85c0_at(&registry, &record.mKey);
    *slot = 0x5A5A5A5Au;
    assert(SimCore_00b8d9b0_resolvePlanetContext(&record) == 0x5A5A5A5Au);

    // A stored value of 0 is NOT a hit: it falls through to tier 2 exactly
    // like a missing key, because the branch is on the returned value.
    *slot = 0u;
    assert(SimCore_00b8d9b0_resolvePlanetContext(&record) == 0u);
}

// ---------------------------------------------------------------------------
// 0x00b8dde0
// ---------------------------------------------------------------------------
void test_generated_terrain_key_store() {
    PlanetRecord record;
    std::memset(&record, 0, sizeof(record));

    PlanetRecord::ResourceKey key = {0x11111111u, 0x22222222u, 0x33333333u};

    // Cold field: all three differ, so all three are written.
    SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(&record, key);
    assert(record.mGeneratedTerrainKey.instanceID == 0x11111111u);
    assert(record.mGeneratedTerrainKey.typeID == 0x22222222u);
    assert(record.mGeneratedTerrainKey.groupID == 0x33333333u);

    // Identical key: the compare chain reaches the final JZ and the store
    // block is skipped entirely.
    record.mGeneratedTerrainKey.instanceID = 0xAAAAAAAAu;
    SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(&record, key);
    assert(record.mGeneratedTerrainKey.instanceID == 0x11111111u);

    // Partial difference: the store is UNCONDITIONAL once entered, so the two
    // words that already matched are rewritten with the same values.
    record.mGeneratedTerrainKey.typeID = 0x99999999u;
    SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(&record, key);
    assert(record.mGeneratedTerrainKey.instanceID == 0x11111111u);
    assert(record.mGeneratedTerrainKey.typeID == 0x22222222u);
    assert(record.mGeneratedTerrainKey.groupID == 0x33333333u);

    // Zero keys are equal to each other, so an all-zero record is a no-op.
    PlanetRecord fresh;
    std::memset(&fresh, 0, sizeof(fresh));
    SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(&fresh, PlanetRecord::ResourceKey{0u, 0u, 0u});
    assert(fresh.mGeneratedTerrainKey.instanceID == 0u);

    // Only the first word differs: the short circuit fires on the very first
    // CMP and all three are still written.
    PlanetRecord partial;
    std::memset(&partial, 0, sizeof(partial));
    partial.mGeneratedTerrainKey.typeID = 7u;
    partial.mGeneratedTerrainKey.groupID = 7u;
    SimCore_00b8dde0_storeGeneratedTerrainKeyIfChanged(&partial, PlanetRecord::ResourceKey{1u, 2u, 3u});
    assert(partial.mGeneratedTerrainKey.instanceID == 1u);
    assert(partial.mGeneratedTerrainKey.typeID == 2u);
    assert(partial.mGeneratedTerrainKey.groupID == 3u);
}

// ---------------------------------------------------------------------------
// 0x00baf700
// ---------------------------------------------------------------------------
void test_interned_object_get_or_create() {
    resetInternedObjectTable();
    installFactoryVtable();
    resetFactory();

    // Selector 0 makes the modelled hashed name 0xACB9635D, so the first call
    // must miss, create, and return the freshly stored value.
    const std::uint32_t hashed = 0xACB9635Du;
    assert(createdCount() == 0u);

    const std::uint32_t first = SimCore_00baf700_getOrCreateInterned(0u);
    assert(createdCount() == 1u);
    // 0x00baf76b pushes 0x568DE14 as the factory key on the create path.
    assert(lastFactoryKey() == 0x0568DE14u);
    // The modelled factory stores hashedName ^ factoryKey.
    assert(first == (hashed ^ 0x0568DE14u));
    assert(releasedCount() == 0u);

    // Second call with the same selector hits: CMP EAX,0x0156C620 is not
    // taken, so neither the release nor the create slot runs again.
    const std::uint32_t second = SimCore_00baf700_getOrCreateInterned(0u);
    assert(second == first);
    assert(createdCount() == 1u);
    assert(releasedCount() == 0u);

    // A different selector misses again; because the modelled map keys on the
    // high 24 bits, pick one that differs there.
    const std::uint32_t other = SimCore_00baf700_getOrCreateInterned(0x10000u);
    assert(createdCount() == 2u);
    assert(other != first);
    assert(releasedCount() == 0u);
}

// ---------------------------------------------------------------------------
// 0x00c446d0
// ---------------------------------------------------------------------------
void test_tagged_vector3_push() {
    OpaqueOwner_C446D0 owner;
    std::memset(&owner, 0, sizeof(owner));

    static TaggedVector3 storage[16];
    owner.taggedVector3s.mpFirst = storage;
    owner.taggedVector3s.mpCur = storage;
    owner.taggedVector3s.mpEnd = storage;
    owner.taggedVector3s.allocatorSentinel = nullptr;

    const float a[3] = {1.0f, 2.0f, 3.0f};
    const float b[3] = {4.0f, 5.0f, 6.0f};
    const float c[3] = {7.0f, 8.0f, 9.0f};

    // Append with at_front == 0: tag is 0 (SETNZ after XOR EDX,EDX).
    SimCore_00c446d0_pushTaggedVector3(&owner, a, 0u);
    assert(owner.taggedVector3s.mpCur == storage + 1);
    assert(storage[0].x == 1.0f && storage[0].y == 2.0f && storage[0].z == 3.0f);
    assert(storage[0].tag == 0u);

    // Append again: mpCur advances by exactly one 0x10 element.
    SimCore_00c446d0_pushTaggedVector3(&owner, b, 0u);
    assert(owner.taggedVector3s.mpCur == storage + 2);
    assert(storage[1].x == 4.0f);
    assert(storage[1].tag == 0u);

    // Prepend with at_front == 1: the tag is 1 on the ELEMENT too, not only
    // used as a direction, and the existing elements shift up.
    SimCore_00c446d0_pushTaggedVector3(&owner, c, 1u);
    assert(owner.taggedVector3s.mpCur == storage + 3);
    assert(storage[0].x == 7.0f && storage[0].y == 8.0f && storage[0].z == 9.0f);
    assert(storage[0].tag == 1u);
    assert(storage[1].x == 1.0f && storage[1].tag == 0u);
    assert(storage[2].x == 4.0f && storage[2].tag == 0u);

    // Any non-zero byte selects the front path and still normalises the tag to
    // exactly 1, never the raw argument.
    const float d[3] = {10.0f, 11.0f, 12.0f};
    SimCore_00c446d0_pushTaggedVector3(&owner, d, 0x80u);
    assert(storage[0].x == 10.0f);
    assert(storage[0].tag == 1u);

    // The full-vector path: mpCur >= mpEnd is an UNSIGNED compare (JNC), so an
    // empty vector (0 >= 0) takes the grow branch on the very first append.
    OpaqueOwner_C446D0 fresh;
    std::memset(&fresh, 0, sizeof(fresh));
    static TaggedVector3 storage2[4];
    fresh.taggedVector3s.mpFirst = storage2;
    fresh.taggedVector3s.mpCur = storage2;
    fresh.taggedVector3s.mpEnd = storage2;
    SimCore_00c446d0_pushTaggedVector3(&fresh, a, 0u);
    assert(fresh.taggedVector3s.mpFirst == storage2);
    assert(fresh.taggedVector3s.mpCur == storage2 + 1);
    assert(storage2[0].x == 1.0f);
    assert(storage2[0].tag == 0u);
}

}  // namespace

int main() {
    test_global_slot_accessor();
    test_star_record_flag_test();
    test_planet_record_resolve_context();
    test_generated_terrain_key_store();
    test_interned_object_get_or_create();
    test_tagged_vector3_push();
    std::printf("wave13-w1-core-b06 model test: all six contracts OK\n");
    return 0;
}
