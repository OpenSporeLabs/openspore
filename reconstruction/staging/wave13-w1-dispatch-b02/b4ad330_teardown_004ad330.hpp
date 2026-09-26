// Wave-13 worker batch b02 -- target 0x004ad330
// Clean-room reconstruction from SporeApp.exe 3.1.0.22.
//
// Observed shape: 21 instructions, 0x004ad330..0x004ad368, 57 bytes.
// A register-argument teardown method (this in ECX, void return, no stack
// arguments, MOV ESP,EBP before the epilogue so any pushed word is discarded):
//
//   1. 0x004ad280(this)                     -- always
//   2. if (this->field_30 != 0)
//        0x004b9570(this->field_30, this)  -- callee pops the owner word
//
// The owning class is NOT identified. The binary has no MSVC RTTI, this
// address has no data references (ghidra_get_xrefs_to returns 13 references,
// all UNCONDITIONAL_CALL), so it is not a vtable entry and no class can be
// claimed from it. See reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// Partial view of the receiver. Only the single member this function reads is
// named; 0x004ad280 additionally walks a pointer vector at +0x18.
struct TeardownTargetPartial {
    void** vtable;            // +0x00, read by 0x004ad280 at slots +0x00 and +0x08
    std::uint8_t pad04[0x14];
    void** list_begin;        // +0x18, read by 0x004ad280
    void** list_end;          // +0x1c, read by 0x004ad280
    std::uint8_t pad20[0x10];
    void* field_30;           // +0x30, the only member the target itself reads
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never implemented.
// ---------------------------------------------------------------------------

// 0x013ec468 -- a static float table, NOT a type descriptor. ghidra_read_memory
// returns 00000000 3eaaaa9f 00000000 00000000 3d4ccccd 3e4ccccd beb33333,
// i.e. the floats 0.0, 1/3, 0.0, 0.0, 0.05, 0.2, 0.35. 0x004ad280 passes its
// address as the single stack argument to both of its virtual calls.
extern const float g_float_constants_013ec468[7];

// 0x004ad280 -- register argument in ECX, void, bare RET. Two virtual calls on
// the receiver, at vtable slots +0x00 and +0x08, each with the single stack
// argument &g_float_constants_013ec468; then a counted walk of the pointer
// vector at receiver+0x18 calling 0x00451400 on each element's first dword;
// then 0x00454280(begin, end, end) to free the vector storage. Neither the
// vector nor field_30 is nulled.
void base_teardown_004ad280_port(TeardownTargetPartial* self);

// 0x004b9570 -- __thiscall(member, owner) with RET 0x4, so the callee pops the
// owner word. The owner is never read: no instruction touches [EBP + 0x8]. The
// body calls 0x004b98b0(begin, end, &local, end) on member+0x18 and then
// 0x004b97e0(member + 0x18, result).
void finalise_member_004b9570_port(void* member, TeardownTargetPartial* owner);

}  // namespace openspore::wave13::b02
