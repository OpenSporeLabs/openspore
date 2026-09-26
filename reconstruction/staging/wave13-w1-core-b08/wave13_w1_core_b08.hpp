// wave13-w1-core-b08 — shared opaque declarations for PKG-11-SIM-CORE batch b08.
//
// Every type and port below is declared from evidence read live out of
// SPORE/SporeBin/SporeApp.exe (3.1.0.22, image base 0x00400000,
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// No port in this file is reconstructed: they are the *unresolved* callees of
// the six reconstructed functions. They are declared, never fabricated. The
// test stub translation unit supplies recording stubs so the reconstructed
// control flow can be exercised.
//
// SporeApp.exe carries no MSVC RTTI, so no class identity is asserted for any
// opaque receiver below. Field offsets are the only layout facts claimed, and
// every one of them is annotated with the instruction that proves it.

#ifndef OPENSPORE_WAVE13_W1_CORE_B08_HPP
#define OPENSPORE_WAVE13_W1_CORE_B08_HPP

#include <cstdint>

namespace openspore {
namespace wave13_w1_core_b08 {

struct OpaqueC0ce80Tiers;
struct OpaqueCPlanetRecord;
struct OpaqueManagerSlotOccupant;

// ---------------------------------------------------------------------------
// 0x00c0b780
// ---------------------------------------------------------------------------

// Owning type of the receiver of 0x00c0b780 is NOT established. Two field
// offsets are observed on it:
//   +0xB20 : pointer to a sub-object  (0x00c0b780: MOV EAX,dword ptr [ECX + 0xB20])
//   +0xB88 : int, read by the sibling 0x00c0b8e0 as (a->f_B88 - b->f_B88)
struct OpaqueC0b780Owner {
    std::uint32_t opaque_prefix[0x2C8];  // 0x2C8 dwords == 0xB20 bytes
    void* f_B20;                        // +0xB20
    std::uint32_t opaque_to_B88[0x19];
    std::int32_t f_B88;                 // +0xB88
};

// Owning type of the sub-object at receiver+0xB20 is NOT established.
// 0x00c0b780 reads +0x608; sibling 0x00c0b7a0 reads +0x60C; 0x00c0cdb0, reached
// through the same receiver field, reads +0x544.
struct OpaqueC0b780SubObject {
    std::uint32_t opaque_prefix[0x151];  // 0x151 dwords == 0x544 bytes
    std::uint32_t f_544;                 // +0x544
    std::uint32_t opaque_to_608[0x30];
    std::uint32_t f_608;                 // +0x608, the flag 0x00c0b780 tests
    std::uint32_t f_60C;                 // +0x60C, the flag 0x00c0b7a0 tests
};

// Sibling predicate 0x00c0b7a0 has the identical shape and a different flag
// offset. Declared because caller 0x00ba27b0 alternates the two in one
// decision tree; it is not part of this target's contract.
bool port_00c0b7a0_flag_60c(OpaqueC0b780Owner* self);

// ---------------------------------------------------------------------------
// 0x00c0ce80
// ---------------------------------------------------------------------------

// Slot +0x58 of the table whose first dword lives at receiver+0xC0, invoked
// with ECX = receiver+0xC0:
//   0x00c0ce80: MOV EDX,[EDI + 0xC0] ; MOV EAX,[EDX + 0x58] ;
//               LEA ECX,[EDI + 0xC0] ; CALL EAX ; TEST AL,AL
using C0ce80Vslot = std::uint8_t (*)(OpaqueC0ce80Tiers*);
struct OpaqueC0ce80SubVtable {
    C0ce80Vslot slots[0x58 / sizeof(C0ce80Vslot) + 1];  // index 0x58/4 == 22
};

// Receiver of 0x00c0ce80. Observed fields only.
struct OpaqueC0ce80Tiers {
    std::uint32_t opaque_prefix[0x30];
    OpaqueC0ce80SubVtable* f_C0;   // +0xC0, its first dword is the table pointer
    std::uint32_t opaque_to_FA0[0x3B7];
    std::int32_t f_FA0;            // +0xFA0
    float f_FA8;                   // +0xFA8 cache slot 0
    float f_FAC;                   // +0xFAC cache slot 1
    float f_FB0;                   // +0xFB0 cache slot 2
    float f_FB4;                   // +0xFB4 cache slot 3
    std::uint32_t opaque_to_B20[0x2DA];
    void* f_B20;                   // +0xB20
    std::uint32_t opaque_to_BB0[0x2A3];
    std::uint8_t f_BB0;            // +0xBB0
};

// Six dwords, all zero in the file image at 0x015D9650.
extern float g_table_015d9650[6];
// Signed per-tier index deltas at 0x015716D8; file image reads 0, -1, 0, 1.
extern std::int32_t g_tier_delta_015716d8[];
// 0.5f, read at 0x01471064 (file image 0x3F000000).
extern float g_scale_01471064;
// Sentinel compared at 0x00c0ce80: CMP EAX,0x1654C10.
extern void* const k_sentinel_01654c10;

// Unresolved callees of 0x00c0ce80, in observed call order.
std::int32_t port_00c0ce30_clamp_index(OpaqueC0ce80Tiers* self, std::uint32_t tier,
                                       std::uint32_t use_base_offset);  // real 0x00c0ce30
void* port_00b5b800_lookup_sentinel();                                  // real 0x00b5b800
void* port_00c03260_lazy_singleton();                                   // real 0x00c03260
float port_00f31500_table_element(void* singleton, void* self, std::int32_t index);  // real 0x00f31500

// ---------------------------------------------------------------------------
// 0x00b8dad0
// ---------------------------------------------------------------------------

// Three consecutive dwords. Spore-ModAPI declares ResourceKey as
// { uint32_t instanceID; uint32_t typeID; uint32_t groupID; }
// (Spore ModAPI/Spore/ResourceKey.h), which is 12 bytes; the sibling setter
// 0x00b8dae0 copies exactly three dwords into receiver+0x198, and 0x00ba61b0
// names the object it constructs "Simulator/cPlanetRecord".
struct ResourceKey3 {
    std::uint32_t dword_0;
    std::uint32_t dword_4;
    std::uint32_t dword_8;
};

using CPlanetRecordVslot0 = void (*)(OpaqueCPlanetRecord*);
struct OpaqueCPlanetRecordVtable {
    CPlanetRecordVslot0 slot_00;  // +0x00, the only slot 0x00ba61b0 calls
};

// Owning type established only as far as the layout agreement goes:
// +0x184 PlanetID, +0x188 ResourceKey, +0x194 TechLevel, +0x198 ResourceKey,
// +0x1A4 ResourceKey (Spore ModAPI/Spore/Simulator/cPlanetRecord.h), and
// 0x00ba61b0 allocates 0x1B0 bytes while passing the literal
// "Simulator/cPlanetRecord" to the allocator at 0x00f473a0.
struct OpaqueCPlanetRecord {
    OpaqueCPlanetRecordVtable* vtable;        // +0x00
    std::uint32_t dword_04;                  // +0x04
    std::uint32_t f_08;                      // +0x08, set to the planet id
    std::uint32_t f_0C;                      // +0x0C, set to 0x5220CB8
    std::uint32_t f_10;                      // +0x10, set to 1
    std::uint32_t opaque_prefix[0x5C];       // +0x14 .. +0x183
    std::uint32_t f_184;                     // +0x184
    ResourceKey3 f_188;                      // +0x188
    std::uint32_t f_194;                     // +0x194
    ResourceKey3 f_198;                      // +0x198, the block this target returns
};

// ---------------------------------------------------------------------------
// 0x00c47180
// ---------------------------------------------------------------------------

// Slots +0xBC and +0xC0 of the table whose first dword is the occupant's
// +0x00. 0x00c47180 calls +0xC0 on the evicted occupant; callee 0x00bb59b0
// calls +0xC0 on the previous holder and +0xBC on the incoming one.
using C47180Vslot = void (*)(OpaqueManagerSlotOccupant*);
struct OpaqueManagerSlotVtable {
    C47180Vslot slots[0xC0 / sizeof(C47180Vslot) + 1];  // index 0xC0/4 == 48
};

struct OpaqueManagerSlotOccupant {
    OpaqueManagerSlotVtable* vtable;        // +0x00
};

// Receiver of 0x00c47180. One field observed.
struct OpaqueC47180Owner {
    std::uint32_t opaque_prefix[0x7A];  // 0x7A dwords == 0x1E8 bytes
    void* f_1E8;                        // +0x1E8, the manager slot
};

// Read by 0x00b3d2a0, which is exactly `MOV EAX,[0x0167EAE4] ; RET`.
extern void* g_manager_0167eae4;

// Unresolved callees of 0x00c47180.
void* port_00b3d2a0_manager_getter();  // real 0x00b3d2a0, ignores its arguments
void port_00bb59b0_replace(OpaqueC47180Owner* self, void* manager, void** slot_io);  // real 0x00bb59b0

// ---------------------------------------------------------------------------
// 0x00ae9f50
// ---------------------------------------------------------------------------

// Sub-object at receiver+0x20. Observed fields only.
struct OpaqueAe9f50SubObject {
    std::uint32_t f_00;
    std::uint32_t f_04;
    std::uint32_t f_08;
    std::uint32_t f_0C;      // CMP dword [EAX+0xC],0 sets the branch polarity
    std::uint32_t f_10;
    std::uint32_t f_14;
    std::uint32_t f_18;      // key pushed before port_00b3d2a0
    void* f_20;              // 0x00ae9fe5: MOV ECX,[EDI + 0x20]
    std::uint32_t f_24;
    void* f_28;              // 0x00ae9fde: MOV EAX,[EDI + 0x28]
    std::uint32_t f_2C;
    std::uint8_t f_30;       // CMP byte [EAX+0x30],0 gates the second record
};

// The 0x34-byte stack record 0x00ae9f50 builds and hands to AppSystem slot
// +0x14. Its first dword is a CODE pointer, not a data vtable: the file image
// holds 0x004230E0 at 0x013EB844 and 0x0040FDC0 at 0x013EB90C, and both are
// Ghidra function entries. Only the dwords 0x00ae9f50 actually writes are
// modelled; the rest are left untouched exactly as the original leaves them.
struct Ae9f50BootRecord {
    void (*code_00)(void);  // +0x00  <- 0x004230E0
    std::uint32_t dword_04;
    std::uint32_t sub_f_0C;  // +0x08  <- sub->f_0C
    std::uint32_t dword_0C;  // +0x0C  <- not written by this function
    void* profile;           // +0x10
    void* sub_f_20;          // +0x18
    void* sub_f_24;          // +0x20
    std::uint32_t dword_28;  // +0x28  <- not written
    std::uint32_t dword_2C;  // +0x2C  <- not written
    std::uint32_t dword_30;  // +0x30  <- 0x3AC86B5 / 0x43F2590
    std::uint32_t dword_34;  // +0x34
    std::uint32_t dword_38;  // +0x38  <- 0
};

// Receiver of 0x00ae9f50. Observed fields only.
struct OpaqueAe9f50Session {
    std::uint32_t opaque_prefix[0x08];
    OpaqueAe9f50SubObject* f_20;  // +0x20, the whole body is guarded on it
    std::uint32_t f_24;
    std::uint32_t f_28;
    std::uint32_t opaque_to_64[0x0E];
    char* f_64;                  // +0x64, compared with f_68 and zeroed
    char* f_68;                  // +0x68, cached copy of f_64
    std::uint32_t opaque_to_74[0x02];
    std::int32_t f_74;           // +0x74, planet id, reset to -1
};

// 0x00ae9f50's unresolved ports, in observed call order.
void* port_00dd1ca0_get();             // real 0x00dd1ca0, bare RET, 6 bytes
void port_00dd30d0_apply(void* a);     // real 0x00dd30d0, bare RET
void* port_00b3d2a0_manager_get();     // real 0x00b3d2a0, bare RET
void* port_00ba9370_map_lookup(void* mgr, std::uint32_t key);      // real 0x00ba9370, RET 0x4
void* port_00b3d300_lookup();          // real 0x00b3d300, bare RET, 6 bytes
void* port_00b20750_map_lookup(void* mgr, std::uint32_t key);      // real 0x00b20750, RET 0x4
void* port_00bd9bf0_default();         // real 0x00bd9bf0, bare RET, 7 bytes
void* port_0067dcc0_app_system();      // App::IAppSystem::Get
// Slot +0x14 of the AppSystem table, invoked as
//   PUSH 0 ; PUSH &record ; PUSH id ; MOV ECX,app_system ; CALL slot
// i.e. (app_system, id, record, 0).
void port_0067dcc0_vslot_14(void* app_system, std::uint32_t id, Ae9f50BootRecord* rec,
                            std::uint32_t zero);
// Slot +0x20 of the table at the object 0x00A206F0 returns, receiver in ECX.
// This is the only indirect call in 0x00ae9f50's own body.
std::uint32_t port_a206f0_vslot_20(void* obj);
void* port_01021300_current();         // real 0x01021300, bare RET
void port_00421cf0_destroy_record(void* rec);  // real 0x00421cf0, bare RET
void* port_00b3d380_get();             // real 0x00b3d380, bare RET, 6 bytes
void port_00b32250_set_flag(void* mgr, std::uint32_t id);  // real 0x00b32250, RET 0x4
void* port_00a206f0_get();             // real 0x00a206f0, bare RET, 6 bytes
void port_00435ed0_publish(std::uint32_t id, std::uint32_t value);  // real 0x00435ed0, bare RET
void* port_00b3d490_tool_manager();    // Simulator::cToolManager::Get
void port_00ae8ea0_reset(void* tool_manager);  // real 0x00ae8ea0, bare RET
void* port_00b3d400_noun_manager();    // Simulator::cGameNounManager::Get
void port_00e14c10_configure(void* nouns, std::uint32_t flag);  // real 0x00e14c10, RET 0x4
void* port_00ba6d80_lookup(void* mgr, std::uint32_t planet_id);  // real 0x00ba6d80, RET 0x4
void* port_01021090_get();             // real 0x01021090, bare RET, 9 bytes
void port_00c35240_bind(void* obj, void* arg);  // real 0x00c35240, bare RET
void* port_00b3d4d0_space_trading();   // Simulator::cSpaceTrading::Get
void port_00ae0930_release(void* trading, char* slot, std::uint32_t one, std::uint32_t z0,
                          std::uint32_t z1, std::uint32_t z2, std::uint32_t z3);  // real 0x00ae0930, RET 0x18

// ---------------------------------------------------------------------------
// 0x00ba61b0
// ---------------------------------------------------------------------------

// Unresolved ports of 0x00ba61b0, in observed call order.
void* port_00f473a0_alloc(std::uint32_t size, const char* type_name, std::uint32_t a3,
                          std::uint32_t a4, std::uint32_t a5, std::uint32_t a6);  // real 0x00f473a0
void port_00b8e180_construct(OpaqueCPlanetRecord* self);  // real 0x00b8e180, bare RET
void port_00b8da80_set_key(OpaqueCPlanetRecord* self, std::uint32_t planet_id);  // real 0x00b8da80, RET 0x4
void port_006ac040_register(void* record, std::uint32_t one);  // real 0x006ac040, bare RET
void port_006ad010_notify(void* record);                       // real 0x006ad010, bare RET

}  // namespace wave13_w1_core_b08
}  // namespace openspore

#endif  // OPENSPORE_W1_CORE_B08_HPP
