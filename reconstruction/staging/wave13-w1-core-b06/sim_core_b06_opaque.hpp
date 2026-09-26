// wave13-w1-core-b06 — shared opaque type / port declarations.
//
// Clean-room static reconstruction of six ORIGINAL SporeApp.exe (3.1.0.22)
// functions.  Every declaration here is either (a) a layout that was read
// directly out of the shipping binary with an instruction address to prove it,
// or (b) an explicitly named opaque port for a callee whose own body was not
// reconstructed by this batch.
//
// Nothing in this file is invented.  Where a type is only partly known it is
// declared with the fields that were OBSERVED and no more; the comment on each
// declaration names the instruction that proves the field.

#pragma once

#include <cstdint>

namespace sim_core_b06 {

// ---------------------------------------------------------------------------
// Global accessors that are themselves trivial bodies read from the binary.
// ---------------------------------------------------------------------------

// 0x00b3d290:  0x00b3d290 MOV EAX,[0x0167EAD4] ; 0x00b3d295 RET
// The whole body.  32 direct callsites, all of the shape
// CALL 0x00b3d290 ; MOV ECX,EAX ; CALL <method>, so the result is a receiver.
std::uint32_t getGlobalEAD4();

// 0x00b3d2a0:  0x00b3d2a0 MOV EAX,[0x0167EAE4] ; 0x00b3d2a5 RET
// The pointee is used as a container host: 0x00bb99e0 reads a map header at
// +0x184 and 0x00c4b220 resolves a lazily-populated pointer slot at +0x1F4.
std::uint32_t getGlobalEAE4();

// 0x00feb9f0:  0x00feb9f0 MOV EAX,[0x016DAC64] ; 0x00feb9f5 RET
std::uint32_t getGlobalDAC64();

// 0x0067de30:  returns DAT_015FD8A8 (decompiled as `return DAT_015fd8a8;`).
std::uint32_t getGlobal_015FD8A8();

// ---------------------------------------------------------------------------
// Node of the ordered associative container walked by 0x00e5c780 / 0x00dd85c0.
// Offsets proven by:
//   0x00e5c780  *puVar2             -> child at +0x00
//   0x00e5c780  puVar2[1]           -> child at +0x04
//   0x00e5c780  (uint)puVar2[4]    -> sort key at +0x10
//   0x00baf730  MOV EAX,[EAX + 0x14] -> mapped value at +0x14
//   0x00bb99a16 MOV EBP,[EBX + 0x14] -> the same slot treated as a cached value
//   0x00bb99a2b MOV EBX,[EBX + 0x10] -> the same slot treated as a PlanetID key
// ---------------------------------------------------------------------------
struct OrderedKeyMapNode {
    std::uint32_t childA;        // +0x00
    std::uint32_t childB;        // +0x04
    std::uint32_t parent;        // +0x08
    std::uint32_t colour;        // +0x0C
    std::uint32_t key;           // +0x10
    std::uint32_t value;         // +0x14
};

// The container that 0x00e5c780 treats as base.  Only the offsets read by
// 0x00e5c780 / 0x00dd85c0 / 0x00baf700 are declared.
struct OrderedKeyMap {
    std::uint32_t rootOrEnd;        // +0x00
    OrderedKeyMapNode* endNode;     // +0x04, compared against at 0x00baf729
    std::uint32_t count;            // +0x08
    OrderedKeyMapNode* rightmost;   // +0x0C, read by 0x00e5c780
};

// The global container at 0x0156C61C.  Live bytes read with
// ghidra_read_memory(0x0156C61C, 16) = 00 00 00 00 | 20 c6 56 01 |
// 20 c6 56 01 | 00 00 00 00, i.e. +0x00 == 0, +0x04 == +0x08 == 0x0156C620,
// +0x0C == 0 (empty at rest).
extern OrderedKeyMap g_internedObjectTable;  // 0x0156C61C

// ---------------------------------------------------------------------------
// Opaque hosts.  Field offsets are OBSERVED; element types are not.
// ---------------------------------------------------------------------------

// The object stored in the .bss slot 0x0167EAD4.  No instruction inside
// 0x00b3d290 touches it, and no static writer for 0x0167EAD4 exists in the
// binary (ghidra_get_xrefs_to 0x0167EAD4 returns exactly one reference: the
// READ at 0x00b3d290), so the slot is populated at runtime.  Type unresolved.
struct OpaqueReceiver_B3D290 {
    std::uint32_t opaque;
};

// The manager returned by getGlobalEAE4().  Only the two offsets this batch
// actually touched are declared.
struct OpaqueManager_EAE4 {
    std::uint8_t opaque[0x184];
    // 0x00bb99e0: 0x00bb99fc LEA ECX,[EDI+0x184] then CALL 0x00e5c780, and
    // 0x00bb9a0b LEA EDX,[EDI+0x188] used as the container end sentinel.
    OrderedKeyMap* registry;    // +0x184
    std::uint32_t endSentinel;  // +0x188
    std::uint8_t opaque2[0x1F4 - 0x18C];
    std::uint32_t* lazySlot;    // +0x1F4, resolved by 0x00c4b220
};

// 0x0067de30's pointee: a factory host reached only through its vtable.
// Slot offsets read in 0x00baf700; neither callee was resolved.
struct OpaqueFactoryVftable {
    std::uint32_t reserved_00;
    std::uint32_t release;       // +0x04, called at 0x00baf763 with ECX = old value
    std::uint32_t reserved_08;
    std::uint32_t reserved_0C;
    std::uint32_t reserved_10;
    std::uint32_t reserved_14;
    std::uint32_t reserved_18;
    std::uint32_t reserved_1C;
    std::uint32_t reserved_20;
    std::uint32_t reserved_24;
    std::uint32_t reserved_28;
    std::uint32_t createOrStore; // +0x2C, called at 0x00baf773
};
struct OpaqueFactoryHost {
    const OpaqueFactoryVftable* vtable;
};

// ---------------------------------------------------------------------------
// Opaque ports.  Declared, not implemented: this batch did not reconstruct
// these bodies, so they must not be given invented implementations.
// ---------------------------------------------------------------------------

// 0x00e5c780 — ordered-container lookup, non-inserting.
// Reads *(base+0x0C), walks child/child, compares the dword at node+0x10
// against *key (unsigned), and writes the found node (or base+0x04) to *out.
void port_00e5c780_lookup(OrderedKeyMap* base, const std::uint32_t* key, OrderedKeyMapNode** out);

// 0x00dd85c0 — ordered-container operator[]: same walk, but inserts a node
// whose key dword is (key & 0xFFFFFF00) with the low byte taken from the
// queried value, and returns &node->value (node+0x14).
std::uint32_t* port_00dd85c0_at(OrderedKeyMap* base, const std::uint32_t* key);

// 0x00c30e80 — 0x00c30e80 PUSH ESI ; MOV ESI,ECX ; ... ; MOV EAX,[ESI+0x58]
// ... CALL 0x00c30cc0 ; ADD ESP,0x8 ; POP ESI ; RET.  Returns a 32-bit hashed
// selector produced by 0x00c30cc0 (a two-level switch returning constants such
// as 0xACB9635D, 0x4FEDE4A6, with a 0x4E5855B9 default).  One ECX receiver.
std::uint32_t port_00c30e80_selectHashedName(OpaqueReceiver_B3D290* receiver);

// ---------------------------------------------------------------------------
// cPlanetRecord.  The identification is OBSERVED, not inferred:
//  * Spore-ModAPI "Spore ModAPI/Spore/Simulator/cPlanetRecord.h" declares
//    /* 28h */ PlanetType mType; /* 2Ch */ int mFlags; /* 184h */ PlanetID
//    mKey; /* 1A4h */ ResourceKey mGeneratedTerrainKey; with
//    ASSERT_SIZE(cPlanetRecord, 0x1B0).
//  * "Spore ModAPI/Spore/ResourceKey.h" declares ResourceKey as three uint32
//    (instanceID, typeID, groupID), i.e. exactly 0xC bytes.
//  * 0x00b8d8e0 returns this+0x1A4, the addressor for that member.
//  * 0x00ce6950 returns *(param_1 + 0x184), read as PlanetID mKey.
// Only the members this batch touched are declared.
// ---------------------------------------------------------------------------
struct PlanetRecord {
    std::uint8_t opaque[0x28];
    std::int32_t mType;   // +0x28  (0x00b8d9f3, 0x00ba6660)
    std::int32_t mFlags;  // +0x2C  (0x00b8d9ff, 0x00b8d9f0, 0x00c44d23)
    std::uint8_t opaque2[0x184 - 0x30];
    std::uint32_t mKey;   // +0x184 PlanetID.internalValue (0x00ce6950)
    std::uint8_t opaque3[0x1A4 - 0x188];
    struct ResourceKey {
        std::uint32_t instanceID;  // +0x00
        std::uint32_t typeID;     // +0x04
        std::uint32_t groupID;    // +0x08
    } mGeneratedTerrainKey;  // +0x1A4, 0xC bytes
};

// Ports used by 0x00b8d9b0.  Bodies observed but not reconstructed here.
std::uint32_t port_00bb99e0_resolveByPlanetId(OpaqueManager_EAE4* manager, PlanetRecord* record);
std::uint32_t port_00fee220_findActiveMissionContext(std::uint32_t global_DAC64, PlanetRecord* record);
std::uint32_t port_00c4b220_resolveSlot1F4(std::uint32_t context);

// ---------------------------------------------------------------------------
// cStarRecord.  Identification is OBSERVED.  Spore-ModAPI
// "Spore ModAPI/Spore/Simulator/cStarRecord.h" declares, in order:
//   /* 3Ch */ Math::Vector3 mPosition;          (0x3C,0x40,0x44)
//   /* 48h */ StarType mType;                   -> FUN_00801920 returns [this+0x48]
//   /* 4Ch */ TechLevel mTechLevel;             -> FUN_00bb9ae0 / FUN_00bb9ad0
//   /* 50h */ bool field_50;                    -> FUN_00bb9b20
//   /* 54h */ uint32_t mEmpireID;
//   /* 58h */ uint32_t mStarterWorldID;         -> 0x00bbac8b CMP EBX,[ESI+0x58]
//   /* 5Ch */ int mFlags;                       -> the field 0x00bb9af0 tests
//   /* 84h */ eastl::vector<cPlanetRecordPtr> mPlanets; -> 0x00bbaa60
// Six independent sibling accessors land on exactly those SDK offsets, and
// 0x00b8d8e0-analogue FUN_00bb9b80 returns this+0x74 (mCitizenSpeciesKey).
// ---------------------------------------------------------------------------
struct StarRecord {
    std::uint8_t opaque[0x3C];
    float mPosition[3];           // +0x3C (0x00bb9ab0 copies three dwords here)
    std::int32_t mType;           // +0x48 (0x00801920: *(param_1 + 0x48))
    std::int32_t mTechLevel;      // +0x4C (0x00bb9ae0: MOV EAX,[ECX + 0x4C])
    std::uint8_t field_50;        // +0x50 (0x00bb9b20: MOV EAX,[ECX + 0x50])
    std::uint8_t pad_51[3];
    std::uint32_t mEmpireID;      // +0x54
    std::uint32_t mStarterWorldID;  // +0x58
    std::int32_t mFlags;          // +0x5C (0x00bb9af0 / 0x00bb9b00 / 0x00bb9b30)
    std::uint8_t opaque2[0x84 - 0x60];
    std::uint32_t* mPlanets;      // +0x84 (0x00bbaa60: *(int *)(param_1 + 0x84))
};

// ---------------------------------------------------------------------------
// The 16-byte element and its EASTL container, for 0x00c446d0.
// Element size 0x10 is proven by 0x00c4472a LEA ESI,[EAX + 0x10] and by the
// growth arithmetic in 0x00c43cc0 ((cur - first) >> 4, capacity << 4 bytes).
// ---------------------------------------------------------------------------
struct TaggedVector3 {
    float x;            // +0x00
    float y;            // +0x04
    float z;            // +0x08
    std::uint32_t tag;  // +0x0C holds (front != 0) ? 1 : 0
};
static_assert(sizeof(TaggedVector3) == 0x10, "element stride must be 0x10");

// 0x00c43cc0 reads param_1[0] (mpFirst), param_1[1] (mpCur), param_1[2]
// (mpEnd) and param_1[4] (+0x10, an allocator-owned sentinel pointer released
// through 0x00f47380).  0x00c446d0 reads +0x00/+0x04/+0x08 only.
struct EastlVector16 {
    TaggedVector3* mpFirst;      // +0x00
    TaggedVector3* mpCur;        // +0x04
    TaggedVector3* mpEnd;        // +0x08
    std::uint32_t pad_0C;
    void* allocatorSentinel;     // +0x10
};

// The owner of that vector.  Unresolved type: the batch proved only that the
// member lives at this+0xF0, that sibling function 0x00c44760 in the same
// region reaches this+0x3E4 and this-0xD4, and that caller 0x00b34380 writes
// the dword 3 at this+0x1F0 immediately after the call.
struct OpaqueOwner_C446D0 {
    std::uint8_t opaque[0xF0];
    EastlVector16 taggedVector3s;  // +0xF0
    std::uint8_t opaque2[0x1F0 - 0x104];
    std::uint32_t field_1F0;       // +0x1F0, written by caller 0x00b34380
};

// Port: 0x00c43cc0.  Its body allocates through 0x00f473a0 with the literal
// "Simulator" and the source path
// "c:\BuildAgent\max-spore001-spore\CMBuild\SporeEP1_RL\Core\UTFKernel\EASTL\include\EASTL/allocator.h"
// and grows capacity as max(1, 2*count) elements of 0x10 bytes.
void port_00c43cc0_insertAt(EastlVector16* vec, TaggedVector3* pos, const TaggedVector3* value);

// Port: 0x00c43f20.  Front-insert fast path plus a return of
// mpFirst + ((pos - mpFirst) >> 4) * 0x10.
TaggedVector3* port_00c43f20_insertAtFront(EastlVector16* vec, TaggedVector3* pos, const TaggedVector3* value);

}  // namespace sim_core_b06
