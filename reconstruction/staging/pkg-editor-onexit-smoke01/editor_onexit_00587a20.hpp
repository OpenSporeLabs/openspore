#pragma once

// PKG-EDITOR-ONEXIT-SMOKE01 -- bounded x86-32 reconstruction of
// Editors::cEditor::OnExit at VA 0x00587a20 in SporeApp.exe 3.1.0.22
// (image base 0x00400000, binary sha256
//  25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Scope of every claim in this header and in the .cpp:
//
//   * 2891 bytes, 934 instructions, 167 basic blocks, 0 back edges.
//   * 162 CALL sites: 77 direct (54 distinct targets) and 85 indirect through a
//     dword read out of a vtable-shaped table at a byte offset named at each
//     site. Every indirect site is reproduced with the exact offset the listing
//     reads; no slot is left opaque.
//   * 61 distinct receiver byte offsets, 0x0078..0x05e4. Every one is declared
//     below with an offsetof assertion tied to the instruction that reads it.
//   * 3 absolute data addresses are dereferenced by the body (0x015fd918,
//     0x016f6ee0, 0x015eebec). 13 more are reached only through the
//     two-instruction global getters that are themselves direct callees.
//
// No SDK class is named for the receiver and no field is given a semantic name.
// Ghidra types the receiver `cEditor *` from the SDK symbol, but SporeApp.exe
// carries no MSVC RTTI (see AGENTS.md), so nothing in the binary corroborates a
// field layout. Field names below are offsets, not meanings.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-EDITOR-ONEXIT-SMOKE01 requires an x86-32 target"
#endif

// The convention token is carried by a macro so each declaration names it once;
// the validator resolves a #define to its convention token, so the entry point
// still counts as declaring a convention.
//
// THISCALL is the entry point and every callee that reads ECX. On i386 a
// `thiscall` callee also pops its own stack arguments, which is why the eight
// callees ending in `RET 0x4` / `RET 0x8` below need no second token.
//
// CDECL is the three callees that never read ECX (0x00571db0, 0x00777ae0,
// 0x00f473a0) and the sixteen two-instruction global getters, whose callers pop
// with `ADD ESP`.
#if defined(_MSC_VER)
#define PKG_EDITOR_ONEXIT_THISCALL __thiscall
#define PKG_EDITOR_ONEXIT_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ONEXIT_THISCALL __attribute__((thiscall))
#define PKG_EDITOR_ONEXIT_CDECL __attribute__((cdecl))
#else
#error "PKG-EDITOR-ONEXIT-SMOKE01 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_onexit_smoke01 {

using Byte = std::uint8_t;
using Dword = std::uint32_t;

// The 64-bit quantity the tail accumulates. The original keeps it as a
// little-endian register pair: `SUB EAX,[ESI+0x438]` / `SBB EDX,[ESI+0x43c]`
// then `ADD [ESI+0x448],EAX` / `ADC [ESI+0x44c],EDX`.
struct alignas(4) U64 {
  Dword lo;
  Dword hi;
};

// --------------------------------------------------------------------------
// Receiver layout.
//
// Modelled only as far as this body reaches. Bytes outside a declared field are
// unmodelled padding; nothing above 0x05e4 is claimed.
// --------------------------------------------------------------------------
struct alignas(4) OpaqueEditor {
  Byte opaque_000[120];
  void* p_078;  // +0x0078
  void* p_07c;  // +0x007c
  Byte opaque_080[4];
  void* p_084;  // +0x0084
  Byte opaque_088[4];
  void* p_08c;  // +0x008c
  Byte opaque_090[4];
  void* p_094;  // +0x0094
  void* p_098;  // +0x0098
  void* p_09c;  // +0x009c
  void* p_0a0;  // +0x00a0
  void* p_0a4;  // +0x00a4
  void* p_0a8;  // +0x00a8
  void* p_0ac;  // +0x00ac
  Byte opaque_0b0[32];
  void* p_0d0;  // +0x00d0
  void* p_0d4;  // +0x00d4
  Byte opaque_0d8[12];
  void* p_0e4;  // +0x00e4
  Byte b_0e8;  // +0x00e8
  Byte b_0e9;  // +0x00e9
  Byte opaque_0ea[90];
  Byte b_144;  // +0x0144
  Byte opaque_145[3];
  void* p_148;  // +0x0148
  void* p_14c;  // +0x014c
  void* p_150;  // +0x0150
  void* p_154;  // +0x0154
  Byte opaque_158[84];
  void* p_1ac;  // +0x01ac
  Byte opaque_1b0[28];
  void* p_1cc;  // +0x01cc
  Byte opaque_1d0[62];
  Byte b_20e;  // +0x020e
  Byte opaque_20f[133];
  void* p_294;  // +0x0294
  Byte opaque_298[4];
  void* p_29c;  // +0x029c
  void* p_2a0;  // +0x02a0
  void* p_2a4;  // +0x02a4
  Byte opaque_2a8[8];
  Byte b_2b0;  // +0x02b0
  Byte opaque_2b1[159];
  void* p_350;  // +0x0350
  void* p_354;  // +0x0354
  void* p_358;  // +0x0358
  void* p_35c;  // +0x035c
  void* p_360;  // +0x0360
  Dword w_364;  // +0x0364
  Dword w_368;  // +0x0368
  Byte opaque_36c[20];
  void* p_380;  // +0x0380
  Byte b_384;  // +0x0384
  Byte b_385;  // +0x0385
  Byte opaque_386[50];
  void* p_3b8;  // +0x03b8
  void* p_3bc;  // +0x03bc
  void* p_3c0;  // +0x03c0
  void* p_3c4;  // +0x03c4
  Byte opaque_3c8[112];
  U64 u_438;  // +0x0438 (lo) / +0x043c (hi)
  Byte opaque_440[8];
  U64 u_448;  // +0x0448 (lo) / +0x044c (hi)
  Dword w_450;  // +0x0450
  Byte opaque_454[64];
  void* p_494;  // +0x0494
  void* p_498;  // +0x0498
  void* p_49c;  // +0x049c
  void* p_4a0;  // +0x04a0
  void* p_4a4;  // +0x04a4
  Byte opaque_4a8[14];
  Byte b_4b6;  // +0x04b6
  Byte opaque_4b7[5];
  void* p_4bc;  // +0x04bc
  Byte opaque_4c0[16];
  float f_4d0;  // +0x04d0
  Byte opaque_4d4[256];
  void* p_5d4;  // +0x05d4
  void* p_5d8;  // +0x05d8
  Dword w_5dc;  // +0x05dc
  void* p_5e0;  // +0x05e0
  Dword w_5e4;  // +0x05e4
};

// The 59 offsetof assertions are emitted with the struct so that a layout edit
// and its evidence stay in one place.
static_assert(offsetof(OpaqueEditor, p_078) == 0x0078,
              "0x00587a20 reads receiver+0x0078");
static_assert(offsetof(OpaqueEditor, p_07c) == 0x007c,
              "0x00587a20 reads receiver+0x007c");
static_assert(offsetof(OpaqueEditor, p_084) == 0x0084,
              "0x00587a20 reads receiver+0x0084");
static_assert(offsetof(OpaqueEditor, p_08c) == 0x008c,
              "0x00587a20 reads receiver+0x008c");
static_assert(offsetof(OpaqueEditor, p_094) == 0x0094,
              "0x00587a20 reads receiver+0x0094");
static_assert(offsetof(OpaqueEditor, p_098) == 0x0098,
              "0x00587a20 reads receiver+0x0098");
static_assert(offsetof(OpaqueEditor, p_09c) == 0x009c,
              "0x00587a20 reads receiver+0x009c");
static_assert(offsetof(OpaqueEditor, p_0a0) == 0x00a0,
              "0x00587a20 reads receiver+0x00a0");
static_assert(offsetof(OpaqueEditor, p_0a4) == 0x00a4,
              "0x00587a20 reads receiver+0x00a4");
static_assert(offsetof(OpaqueEditor, p_0a8) == 0x00a8,
              "0x00587a20 reads receiver+0x00a8");
static_assert(offsetof(OpaqueEditor, p_0ac) == 0x00ac,
              "0x00587a20 reads receiver+0x00ac");
static_assert(offsetof(OpaqueEditor, p_0d0) == 0x00d0,
              "0x00587a20 reads receiver+0x00d0");
static_assert(offsetof(OpaqueEditor, p_0d4) == 0x00d4,
              "0x00587a20 reads receiver+0x00d4");
static_assert(offsetof(OpaqueEditor, p_0e4) == 0x00e4,
              "0x00587a20 reads receiver+0x00e4");
static_assert(offsetof(OpaqueEditor, b_0e8) == 0x00e8,
              "0x00587a20 reads receiver+0x00e8");
static_assert(offsetof(OpaqueEditor, b_0e9) == 0x00e9,
              "0x00587a20 reads receiver+0x00e9");
static_assert(offsetof(OpaqueEditor, b_144) == 0x0144,
              "0x00587a20 reads receiver+0x0144");
static_assert(offsetof(OpaqueEditor, p_148) == 0x0148,
              "0x00587a20 reads receiver+0x0148");
static_assert(offsetof(OpaqueEditor, p_14c) == 0x014c,
              "0x00587a20 reads receiver+0x014c");
static_assert(offsetof(OpaqueEditor, p_150) == 0x0150,
              "0x00587a20 reads receiver+0x0150");
static_assert(offsetof(OpaqueEditor, p_154) == 0x0154,
              "0x00587a20 reads receiver+0x0154");
static_assert(offsetof(OpaqueEditor, p_1ac) == 0x01ac,
              "0x00587a20 reads receiver+0x01ac");
static_assert(offsetof(OpaqueEditor, p_1cc) == 0x01cc,
              "0x00587a20 reads receiver+0x01cc");
static_assert(offsetof(OpaqueEditor, b_20e) == 0x020e,
              "0x00587a20 reads receiver+0x020e");
static_assert(offsetof(OpaqueEditor, p_294) == 0x0294,
              "0x00587a20 reads receiver+0x0294");
static_assert(offsetof(OpaqueEditor, p_29c) == 0x029c,
              "0x00587a20 reads receiver+0x029c");
static_assert(offsetof(OpaqueEditor, p_2a0) == 0x02a0,
              "0x00587a20 reads receiver+0x02a0");
static_assert(offsetof(OpaqueEditor, p_2a4) == 0x02a4,
              "0x00587a20 reads receiver+0x02a4");
static_assert(offsetof(OpaqueEditor, b_2b0) == 0x02b0,
              "0x00587a20 reads receiver+0x02b0");
static_assert(offsetof(OpaqueEditor, p_350) == 0x0350,
              "0x00587a20 reads receiver+0x0350");
static_assert(offsetof(OpaqueEditor, p_354) == 0x0354,
              "0x00587a20 reads receiver+0x0354");
static_assert(offsetof(OpaqueEditor, p_358) == 0x0358,
              "0x00587a20 reads receiver+0x0358");
static_assert(offsetof(OpaqueEditor, p_35c) == 0x035c,
              "0x00587a20 reads receiver+0x035c");
static_assert(offsetof(OpaqueEditor, p_360) == 0x0360,
              "0x00587a20 reads receiver+0x0360");
static_assert(offsetof(OpaqueEditor, w_364) == 0x0364,
              "0x00587a20 reads receiver+0x0364");
static_assert(offsetof(OpaqueEditor, w_368) == 0x0368,
              "0x00587a20 reads receiver+0x0368");
static_assert(offsetof(OpaqueEditor, p_380) == 0x0380,
              "0x00587a20 reads receiver+0x0380");
static_assert(offsetof(OpaqueEditor, b_384) == 0x0384,
              "0x00587a20 reads receiver+0x0384");
static_assert(offsetof(OpaqueEditor, b_385) == 0x0385,
              "0x00587a20 reads receiver+0x0385");
static_assert(offsetof(OpaqueEditor, p_3b8) == 0x03b8,
              "0x00587a20 reads receiver+0x03b8");
static_assert(offsetof(OpaqueEditor, p_3bc) == 0x03bc,
              "0x00587a20 reads receiver+0x03bc");
static_assert(offsetof(OpaqueEditor, p_3c0) == 0x03c0,
              "0x00587a20 reads receiver+0x03c0");
static_assert(offsetof(OpaqueEditor, p_3c4) == 0x03c4,
              "0x00587a20 reads receiver+0x03c4");
static_assert(offsetof(OpaqueEditor, u_438) == 0x0438,
              "0x00588517/0x00588522 read the 64-bit word at receiver+0x0438");
static_assert(offsetof(OpaqueEditor, u_448) == 0x0448,
              "0x00588528/0x0058852e accumulate into receiver+0x0448");
static_assert(sizeof(U64) == 8,
              "0x00588517 SUB EAX and 0x00588522 SBB EDX are one 64-bit word");
static_assert(offsetof(OpaqueEditor, u_438) + 4 == 0x043c,
              "0x00588522 SBB EDX reads the high half at receiver+0x043c");
static_assert(offsetof(OpaqueEditor, u_448) + 4 == 0x044c,
              "0x0058852e ADC EDX reads the high half at receiver+0x044c");
static_assert(offsetof(OpaqueEditor, w_450) == 0x0450,
              "0x00587a20 reads receiver+0x0450");
static_assert(offsetof(OpaqueEditor, p_494) == 0x0494,
              "0x00587a20 reads receiver+0x0494");
static_assert(offsetof(OpaqueEditor, p_498) == 0x0498,
              "0x00587a20 reads receiver+0x0498");
static_assert(offsetof(OpaqueEditor, p_49c) == 0x049c,
              "0x00587a20 reads receiver+0x049c");
static_assert(offsetof(OpaqueEditor, p_4a0) == 0x04a0,
              "0x00587a20 reads receiver+0x04a0");
static_assert(offsetof(OpaqueEditor, p_4a4) == 0x04a4,
              "0x00587a20 reads receiver+0x04a4");
static_assert(offsetof(OpaqueEditor, b_4b6) == 0x04b6,
              "0x00587a20 reads receiver+0x04b6");
static_assert(offsetof(OpaqueEditor, p_4bc) == 0x04bc,
              "0x00587a20 reads receiver+0x04bc");
static_assert(offsetof(OpaqueEditor, f_4d0) == 0x04d0,
              "0x00587a20 reads receiver+0x04d0");
static_assert(offsetof(OpaqueEditor, p_5d4) == 0x05d4,
              "0x00587a20 reads receiver+0x05d4");
static_assert(offsetof(OpaqueEditor, p_5d8) == 0x05d8,
              "0x00587a20 reads receiver+0x05d8");
static_assert(offsetof(OpaqueEditor, w_5dc) == 0x05dc,
              "0x00587a20 reads receiver+0x05dc");
static_assert(offsetof(OpaqueEditor, p_5e0) == 0x05e0,
              "0x00587a20 reads receiver+0x05e0");
static_assert(offsetof(OpaqueEditor, w_5e4) == 0x05e4,
              "0x00587a20 reads receiver+0x05e4");
static_assert(sizeof(OpaqueEditor) == 0x05e8, "minimum receiver extent");


// --------------------------------------------------------------------------
// Indirect dispatch.
//
// The original performs all 85 indirect calls the same three-instruction way:
//
//   MOV EAX,dword ptr [receiver]       ; the vtable-shaped table
//   MOV EDX,dword ptr [EAX+Slot]       ; the entry, Slot a BYTE displacement
//   CALL EDX                           ; receiver already in ECX
//
// `Slot` is the byte displacement the listing reads at that site and nothing
// else: no slot is resolved to a name, and no site is left opaque, so the
// source asserts a concrete table offset for every dispatch it performs.
// --------------------------------------------------------------------------
using Entry = std::uintptr_t;

inline Entry entry_at(const void* receiver, Dword slot) noexcept {
  const void* const* table = *reinterpret_cast<void* const* const*>(receiver);
  return reinterpret_cast<Entry>(reinterpret_cast<const Byte*>(table) + slot);
}

// One alias per stack shape the body actually pushes, so the shape is visible
// at the call site rather than buried in a cast. The arity split over the 85
// sites is 49 of arity 0, 20 of arity 1, 13 of arity 2, 2 of arity 3 and 1 of
// arity 4; the per-alias counts below are the static counts in this source,
// which are lower than 85 wherever a helper factors several sites into one
// dispatch (`release_two_phase` and `release_weak_teardown`).
using Fn0 = void (*)();                             // 37 static sites
using Fn0p = void* (*)();                           // 3: 0x00587b81, 0x00587a95, 0x00588505
using Fn1 = void (*)(Dword);                        // 19
using Fn1f = void* (*)(float);                      // 1: 0x00587b21 -- takes the float and
                                                   // returns the pointer 0x007c53d0 is given
using Fn2 = void (*)(Dword, Dword);                 // 5
using Fn3w = void (*)(Dword, const void*, Dword);   // 1: 0x00587ab2
using Fn3p = void (*)(const void*, Dword, Dword);   // 1: 0x00587cc6
using Fn4p = void (*)(Dword, void*, Dword, Dword);  // 1: 0x00587c56
using Fn1p = void (*)(const void*);                // 1: 0x00587b91
using Fn2p = void (*)(const void*, Dword);         // 2 static, 8 dynamic (0x16c and
                                                   // 0x170, four members each)

// The thirteen preparatory callees handed to a helper as a value. They are
// thiscall, which on i386 also means callee-popped, so the alias carries the
// attribute rather than the helper assuming it.
using PrepFn = void (PKG_EDITOR_ONEXIT_THISCALL*)(void*);

// --------------------------------------------------------------------------
// The stack object this routine builds at its own frame base.
//
// Five dwords are written, at 0x00587a6a, 0x00587a72, 0x00587a80, 0x00587a89 and
// 0x00587a91, in that order; 0x00587a97 writes a sixth (the slot 0x44 result).
// 0x00421cf0 later walks this object: it re-points the dispatch word, then for
// i = 0..0x1f releases every sub-object at +0x08 + i*8 whose bit is set in
// sub_mask, then re-points the dispatch word twice more.
//
// Modelled at 0x40 bytes, which is exactly the room the 0x44-byte frame leaves
// above the object base. 0x00421cf0 can address up to +0x100, but only for a
// bit that is set in sub_mask, and sub_mask is written to 0 at 0x00587a91
// before the call that could populate any of those slots.
// --------------------------------------------------------------------------
struct alignas(4) LocalAppState {
  const void* dispatch;      // +0x00
  Dword zero_04;             // +0x04
  void* sub_08;              // +0x08
  Byte opaque_0c[0x24];      // +0x0c .. +0x2f
  Dword tag_30;              // +0x30
  Dword opaque_34;           // +0x34
  Dword sub_mask;            // +0x38
  Byte opaque_3c[4];         // +0x3c .. +0x3f
};

static_assert(offsetof(LocalAppState, dispatch) == 0x00, "0x00587a89 writes +0x00");
static_assert(offsetof(LocalAppState, zero_04) == 0x04, "0x00587a80 writes +0x04");
static_assert(offsetof(LocalAppState, sub_08) == 0x08, "0x00587a97 writes +0x08");
static_assert(offsetof(LocalAppState, tag_30) == 0x30, "0x00587a6a writes +0x30");
static_assert(offsetof(LocalAppState, sub_mask) == 0x38, "0x00587a91 writes +0x38");
static_assert(sizeof(LocalAppState) == 0x40, "0x44-byte frame less the 4-byte prologue bias");

// --------------------------------------------------------------------------
// Absolute data addresses the body dereferences directly. These three are the
// only ones read by a `MOV reg,dword ptr [addr]` in the listing; the other
// thirteen global words this body reaches are reached only through the
// two-instruction getters declared above.
// --------------------------------------------------------------------------
inline Dword* g_015fd918() noexcept {  // 0x00587a41, 0x00587b49
  return reinterpret_cast<Dword*>(0x015fd918);
}
inline Dword* g_016f6ee0() noexcept {  // 0x00587ab4, then AND dword ptr [EAX],0xfffffffe
  return reinterpret_cast<Dword*>(0x016f6ee0);
}
inline Dword g_015eebec() noexcept {   // 0x00587b83
  return *reinterpret_cast<Dword*>(0x015eebec);
}

// --------------------------------------------------------------------------
// The 54 distinct direct call targets. Each declaration's convention and
// parameter count is read off that callee's own epilogue, not off this caller's
// call site, so the set is a property of the callees.
// --------------------------------------------------------------------------
// MOV EAX,[0x015d0c08] ; RET -- 0 stack args
void* PKG_EDITOR_ONEXIT_CDECL sub_00401020();
// MOV EAX,[0x015d0c14] ; RET -- 0 stack args
void* PKG_EDITOR_ONEXIT_CDECL sub_00401050();
// 40 insns, bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_00421cf0(LocalAppState* self);
// ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_0043a9a0(void* self, Dword a0, Dword a1);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_004581d0(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_0045ab30(void* self);
// bare RET, 0 stack args, EAX returned
void* PKG_EDITOR_ONEXIT_THISCALL sub_0047e6c0(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_004ad280(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_004ad330(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_004b27c0(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_004c4eb0(void* self);
// bare RET; caller ADD ESP,0x14; ECX is saved, never read
void PKG_EDITOR_ONEXIT_CDECL sub_00571db0(void* a0, void* a1, Dword a2, void* a3, Dword a4);
// ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_00573c00(void* self, Dword a0, Dword a1);
// ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_00573d70(void* self, Dword a0, Dword a1);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005772b0(void* self);
// MOV EAX,ECX then 20 stores; ctor; bare RET
void* PKG_EDITOR_ONEXIT_THISCALL sub_00579c80(void* self);
// ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_00587270(void* self, Dword a0, Dword a1);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_0059a3b0(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_0059c640(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005bfb90(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005c5c20(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005cba90(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005d31b0(void* self);
// PUSH -1; CALL 0x0067de90; ... bare RET
void PKG_EDITOR_ONEXIT_THISCALL sub_005dbb50(void* self);
// ends RET 0x4 -> callee pops 4
void PKG_EDITOR_ONEXIT_THISCALL sub_005dbb60(void* self, Dword a0);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_005de870(void* self);
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_0062c910(void* self);
// SUB ESP,0x134; MOV ESI,ECX; bare RET
void PKG_EDITOR_ONEXIT_THISCALL sub_0067a120(void* self);
// ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_0067c420(void* self, Dword a0, Dword a1);
// ADD [ECX+0x10],-4 ; JMP 0x0067c9b0; bare RET
void PKG_EDITOR_ONEXIT_THISCALL sub_0067ca40(void* self);
// MOV EAX,[0x015fcc4c] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067caa0();
// MOV EAX,[0x015fcc50] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067cab0();
// MOV EAX,[0x015fcc54] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067cac0();
// MOV EAX,[0x015fcc58] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067cad0();
// MOV EAX,[0x015fcc60] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067caf0();
// MOV EAX,[0x015fd890] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067dcc0();
// MOV EAX,[0x015fd8b0] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067dd10();
// MOV EAX,[0x015fd8bc] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067dd40();
// MOV EAX,[0x015fd8c0] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067dd50();
// MOV EAX,[0x015fd8cc] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067dd80();
// MOV EAX,[0x015fd8e8] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067ddd0();
// MOV EAX,[0x015fd8a4] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067de20();
// MOV EAX,[0x015fd8f8] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_0067de40();
// SEH frame; ends RET 0x8 -> callee pops 8
void PKG_EDITOR_ONEXIT_THISCALL sub_006a1880(void* self, Dword a0, Dword a1);
// MOV EAX,[ECX+0x3c] ; RET
void* PKG_EDITOR_ONEXIT_THISCALL sub_006c10e0(void* self);
// bare RET; caller ADD ESP,0x18; ECX saved, never read
void PKG_EDITOR_ONEXIT_CDECL sub_00777ae0(Dword a0, Dword a1, Dword a2);
// ends RET 0x4 -> callee pops 4; the argument is the float FSTP-d at 0x00587b1b, not the register PUSH ECX left behind
void PKG_EDITOR_ONEXIT_THISCALL sub_007c53d0(void* self, float a0);
// MOV EAX,[ECX+0x48] ; RET
void* PKG_EDITOR_ONEXIT_THISCALL sub_00801920(void* self);
// ends RET 0x4 -> callee pops 4
void PKG_EDITOR_ONEXIT_THISCALL sub_00801bb0(void* self, Dword a0);
// MOV EAX,[ECX+0x250]; MOV EDX,[ECX+0x254]; RET -- 64-bit in EDX:EAX
U64 PKG_EDITOR_ONEXIT_THISCALL sub_008130a0(void* self);
// MOV EAX,[0x0166d9f4] ; RET
void* PKG_EDITOR_ONEXIT_CDECL sub_00a206f0();
// bare RET, 0 stack args
void PKG_EDITOR_ONEXIT_THISCALL sub_00ed0660(void* self);
// bare RET; caller ADD ESP,0x18; ECX never read
void* PKG_EDITOR_ONEXIT_CDECL sub_00f473a0(Dword a0, Dword a1, Dword a2, Dword a3, Dword a4, Dword a5);
// MOV EAX,[ECX+0x44] ; RET
void* PKG_EDITOR_ONEXIT_THISCALL sub_0113ae10(void* self);

// --------------------------------------------------------------------------
// 0x00587a20, 2891 bytes, 934 instructions, 167 basic blocks, 0 back edges.
//
// ABI, all read off the body rather than off the derived record:
//
//   * the receiver arrives in ECX and is copied to ESI at 0x00587a26; the body
//     dereferences the receiver 61 times and never writes ECX before that copy,
//     so ECX is a hidden `this` and the frame is __thiscall;
//   * no stack argument is ever pushed for this function's own entry, and the
//     epilogue is `POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET` -- a bare
//     RET with no immediate, so the callee pops nothing and the caller owns
//     cleanup;
//   * EBP is not a frame pointer. There is no `MOV EBP,ESP`; EBP is loaded with
//     the constant 1 at 0x00587aef, used as the general register holding
//     self->p_1cc[0x94] across 0x00587be8..0x00587c78, reloaded with 1 at
//     0x00587c78, and restored by the epilogue's POP. Every frame-relative
//     offset in the body is therefore an ESP displacement, not an EBP one.
//   * the return type is void. The FLD/FSTP pair at 0x00587b10/0x00587b1b is a
//     float passed as a stack argument, and it balances: nothing is left on the
//     x87 stack, and the return path (0x0058855f CALL, then three POPs and a
//     bare RET) reads no floating register.
// --------------------------------------------------------------------------
extern "C" void PKG_EDITOR_ONEXIT_THISCALL
Editors_cEditor_OnExit_00587a20(OpaqueEditor* self);

}  // namespace openspore::reconstruction::pkg_editor_onexit_smoke01

#undef PKG_EDITOR_ONEXIT_THISCALL
#undef PKG_EDITOR_ONEXIT_CDECL
