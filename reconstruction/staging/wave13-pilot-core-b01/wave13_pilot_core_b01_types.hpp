#pragma once

// Opaque wire types and unresolved ports for the wave-13 pilot core batch
// (package wave13-pilot-core-b01, PKG-11-SIM-CORE).
//
// Every port below is an UNRESOLVED external callee read out of the binary.
// No body is fabricated here: the model test supplies recording stubs, and
// the real implementations are named by VA only.

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-pilot-core-b01 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define W13_THISCALL __thiscall
#define W13_STDCALL __stdcall
#else
#define W13_THISCALL __attribute__((thiscall))
#define W13_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::wave13_pilot_core_b01 {

using Word = std::uint32_t;
using Dword = std::uint32_t;
using DwordPtr = Dword*;

// ---------------------------------------------------------------------------
// 0x00c472e0 / 0x00c471c0 receiver.
//
// Observed layout facts (each proved by a disassembly address recorded in the
// metadata sidecar):
//   +0x09c  read as a pointer, dereferenced at +0x13c
//   +0x130  dword whose bit 1 is tested
//   +0x17c  sub-object pointer, self-substituted when null
// The owning class is NOT established by a vtable: 0x00c472e0 and 0x00c471c0
// appear nowhere in .rdata/.data as a dword, so neither is a virtual slot. The
// offsets are consistent with Spore-ModAPI Spore/Simulator/cMission.h, but the
// layout below stops at the highest offset any observed body touches.
// ---------------------------------------------------------------------------
struct OpaqueMission {
    const void* vftable;              // +0x000
    std::uint8_t unknown_004[0x98];   // +0x004 .. +0x09b
    const void* field_09c;            // +0x09c  (mpSourcePlanet candidate)
    std::uint8_t unknown_0a0[0x90];   // +0x0a0 .. +0x12f
    Dword field_130;                  // +0x130  bit 1 tested by 0x00c471c0
    std::uint8_t unknown_134[0x48];   // +0x134 .. +0x17b
    const OpaqueMission* field_17c;   // +0x17c  sub-object, self-substituted
};

// ---------------------------------------------------------------------------
// 0x00bfc490 receiver. A pointer to it is produced as `parent + 0x5a8`, which
// matches Spore-ModAPI cCreatureBase deriving from cCombatant at +0x5a8.
// Only +0x038 is read as a float and vtable slot +0x58 is the divisor.
// ---------------------------------------------------------------------------
struct OpaqueCombatant {
    const void* vftable;      // +0x000
    std::uint8_t pad_004[0x34];
    float field_038;          // +0x038  numerator (cCombatant::mHealthPoints candidate)
    std::uint8_t tail_03c[0x8c];
};

// ---------------------------------------------------------------------------
// 0x00bbaa60 / 0x00bb9b00 receiver. Observed fields: +0x05c dword bitfield,
// +0x084 a three-pointer vector (begin/end/capacity), +0x0ac a byte count.
// Consistent with Spore-ModAPI Spore/Simulator/cStarRecord.h.
// ---------------------------------------------------------------------------
struct OpaqueVector3 {
    void* begin;      // +0x00
    void* end;        // +0x04
    void* capacity;   // +0x08
};

struct OpaqueStarRecord {
    const void* vftable;          // +0x000
    std::uint8_t pad_004[0x58];
    Dword field_05c;               // +0x05c  bitfield (StarFlags candidate)
    std::uint8_t pad_060[0x24];
    Dword field_070;               // +0x070  StarID (packed, unused by these two)
    std::uint8_t pad_074[0x10];
    OpaqueVector3 field_084;       // +0x084  vector<cPlanetRecordPtr*>
    std::uint8_t pad_090[0x1c];
    std::uint8_t field_0ac;        // +0x0ac  element count
    std::uint8_t pad_0ad[0xa3];
};

// ---------------------------------------------------------------------------
// 0x00b3d850 receiver. A three-slot cursor handle: cursor, end, owner.
// Slot +0x08 is loaded into ECX before the port call; the port never reads it.
// ---------------------------------------------------------------------------
struct OpaqueCursor {
    void** cursor;    // +0x00
    void** end;       // +0x04
    void* owner;      // +0x08
};

// ---------------------------------------------------------------------------
// Unresolved ports, named by VA only.
// ---------------------------------------------------------------------------

// 0x00b3d4a0: two instructions, `MOV EAX,[0x0167eb44]` / `RET`. Consumes no
// stack argument (bare RET). 0x0167eb44 is zero in the file image.
Dword* W13_STDCALL port_00b3d4a0_read_service_slot_0167eb44();

// 0x00c451e0: thiscall, lazily creates and caches a refcounted sub-object in
// the mission at +0x090, keyed by the int at +0x08c. Returns that pointer.
const void* W13_THISCALL port_00c451e0_get_cached_sub_object(OpaqueMission* self);

// 0x00ce6950: `MOV EAX,[ECX+0x184]` / `RET`. Reads ECX but ends in a bare RET,
// so nothing is popped on its behalf: the convention is this-pointer-in-ECX
// with caller-side stack cleanup.
Dword port_00ce6950_read_field_184(const void* self);

// 0x00aeb7a0: thunk, `JMP 0x00aeb160`. 0x00aeb160 is thiscall, takes seven
// stack arguments and ends in `RET 0x1c`, so the callee pops all seven.
void* W13_THISCALL port_00aeb7a0_register_record(
    void* service, Dword arg1, Dword arg2, Dword arg3, Dword arg4, Dword arg5,
    Dword arg6, Dword arg7);

// 0x01046fc0: cdecl, `MOV EAX,[0x016e00d4]` then a lazy create that ends in a
// bare RET. Ignores every argument it is handed; other callsites push words for
// it and leave them on the stack, the 0x00c471c0 callsite pushes none.
void* port_01046fc0_get_simulator_service();

// 0x01048ce0: thiscall void. Guarded by 0x01021080; drives 0x01048c10 seven
// times with the indices 0..6, then tail-jumps to 0x01047000.
void W13_THISCALL port_01048ce0_flush_pending(void* simulator_service);

// 0x00bba640: thiscall void, cdecl stack. Resizes the receiver's +0x084 vector
// to the element count at +0x0ac and repopulates it.
void W13_THISCALL port_00bba640_sync_planet_vector(OpaqueStarRecord* self);

// 0x00c02600: `RET 0x4`, one stack argument at [ESP+4], ECX never read.
// Returns 1 only when all four of its conditions hold.
std::uint8_t W13_STDCALL port_00c02600_is_accepted_element(void* element);

// ---------------------------------------------------------------------------
// Reconstructed entry points. Names embed the 8-hex VA so the tooling can
// locate the body.
// ---------------------------------------------------------------------------

// 0x00c472e0: 38 instructions, thiscall, void return.
void SimMission_00c472e0_publishStateArtifacts(OpaqueMission* self);

// 0x00c471c0: 42 instructions, thiscall, void return.
void SimMission_00c471c0_settleStateArtifacts(OpaqueMission* self);

// 0x00bfc490: 8 instructions, thiscall, x87 float return.
float Combatant_00bfc490_healthFraction(OpaqueCombatant* self);

// 0x00bbaa60: 8 instructions, thiscall plus one callee-popped stack word.
void* StarRecord_00bbaa60_getPlanetRecordByIndex(OpaqueStarRecord* self,
                                                 std::uint32_t index);

// 0x00bb9b00: 9 instructions, thiscall plus two callee-popped stack words.
void StarRecord_00bb9b00_setFlagsMask(OpaqueStarRecord* self, Dword mask,
                                      std::uint8_t set);

// 0x00b3d850: 15 instructions, thiscall, returns the receiver handle.
OpaqueCursor* Cursor_00b3d850_advanceToAccepted(OpaqueCursor* self);

}  // namespace
