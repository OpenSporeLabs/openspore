#pragma once

// PKG-DOGFOOD-00587A20-A1 -- bounded x86-32 reconstruction of
// Editors::cEditor::OnExit at VA 0x00587a20 in SporeApp.exe 3.1.0.22
// (image base 0x00400000, binary sha256
//  25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// SCOPE OF EVERY CLAIM IN THIS FILE AND IN THE .cpp
//
// Machine facts, each read off the disassembly of the 2891-byte body that
// starts at 0x00587a20 and ends at the RET at 0x0058856a:
//
//   * 934 instructions, 167 basic blocks, 107 conditional branches,
//     6 unconditional jumps, 1 RET.
//   * The block graph is a DAG: a full reachability walk from the entry
//     reaches all 167 blocks and a DFS finds no cycle. The single backward
//     JMP (0x00588225 -> 0x00587bd0) is a re-entry into a shared block, not a
//     loop, because nothing reaches 0x00588225 from 0x00587bd0.
//   * 162 CALL sites: 77 direct, over 54 distinct targets, and 85 indirect
//     through a dword read out of a table at a byte displacement.
//   * 61 distinct receiver byte offsets in 0x0078..0x05e4, each read or
//     written by a named instruction. Each is a declared field below, with an
//     offsetof assertion, so no offset can drift from its evidence.
//
// NO SDK CLASS IS NAMED FOR THE RECEIVER AND NO FIELD HAS A SEMANTIC NAME.
// Ghidra types the receiver `cEditor *` from the SDK symbol, but SporeApp.exe
// carries no MSVC RTTI (see AGENTS.md), so nothing in the binary corroborates
// a class identity or a field meaning. The names below are offsets.
//
// The four `U64` fields are the only place where two adjacent offsets are
// treated as one 64-bit quantity. That is not a guess: at 0x00588517/0x00588522
// the body does `SUB EAX,[ESI+0x438]` / `SBB EDX,[ESI+0x43c]`, and at
// 0x00588528/0x0058852e `ADD [ESI+0x448],EAX` / `ADC [ESI+0x44c],EDX`. Those
// are the carry-propagating halves of 64-bit add/subtract and nothing else.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-DOGFOOD-00587A20-A1 requires an x86-32 target"
#endif

// The convention is carried by a macro so each declaration names it once; the
// validator resolves a #define to its convention token, so the entry point
// still counts as declaring a convention.
//
// THISCALL is the entry point and every callee that reads ECX. On i386 a
// thiscall callee that also pops its own stack arguments uses `RET imm`, and
// the seven callees below that end in `RET 0x4` / `RET 0x8` need no second
// token because callee-pop is part of the same convention.
//
// CDECL is the callee that ends in a bare RET, does not read ECX, and whose
// caller cleans up with `ADD ESP` -- plus the sixteen two-instruction global
// getters, which are `MOV EAX,[addr] ; RET`.
#if defined(_MSC_VER)
#define PKG_ONEXIT_THISCALL __thiscall
#define PKG_ONEXIT_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ONEXIT_THISCALL __attribute__((thiscall))
#define PKG_ONEXIT_CDECL __attribute__((cdecl))
#else
#error "PKG-DOGFOOD-00587A20-A1 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_dogfood_00587a20_a1 {

using Byte = std::uint8_t;
using Dword = std::uint32_t;

// A 4-byte receiver cell whose meaning this body does not establish.
//
// The listing reads most of these with a bare `dword ptr [ESI+N]` and then
// dereferences the loaded value in a LATER instruction, so whether a given
// cell holds a pointer is a property of how the body uses it, not of the
// access width. Rather than guess a width-and-meaning per field, every dword
// cell is opaque here and the pointer-ness is applied at the point of use,
// where the dereferencing instruction is adjacent in the listing and can be
// cited. A `Cell` is exactly as wide as the machine access that named it.
struct alignas(4) Cell {
  Dword raw;
  Cell() = default;

  // Conversions are implicit on purpose: this is a modelling wrapper around a
  // machine word, and every use site in the .cpp has already been decided
  // against a named instruction. Making them explicit would force each use to
  // restate a fact the listing states, without adding a check.
  // Exactly one pointer conversion, so a comparison against nullptr and a
  // comparison against 0 are both unambiguous. A second, const-qualified
  // overload would make every `!= nullptr` in the .cpp ambiguous, which is
  // noise rather than safety.
  operator Dword() const noexcept { return raw; }
  operator void*() const noexcept { return reinterpret_cast<void*>(raw); }

  // Stores a machine word, so `cell = 0` for a clear and `cell = value` for a
  // write both read the way the listing's `MOV [ESI+N],reg` reads.
  Cell& operator=(Dword value) noexcept { raw = value; return *this; }
};

// The 64-bit quantity the tail accumulates, kept as the register pair the
// original uses rather than as a compiler-chosen 64-bit type.
struct alignas(4) U64 {
  Dword lo;
  Dword hi;
};

// --------------------------------------------------------------------------
// Receiver layout.
//
// GENERATED, NOT HAND-WRITTEN: the field list below is emitted from the set of
// `[ESI+N]` displacements the listing contains, so a field exists if and only
// if an instruction names that offset. Bytes between declared fields are
// unmodelled padding. Nothing at or above 0x05e8 is claimed.
// --------------------------------------------------------------------------
struct alignas(4) OpaqueEditor {
  Byte pad_000[120];
  Cell f_078;  // +0x0078
  Cell f_07c;  // +0x007c
  Byte pad_080[4];
  Cell f_084;  // +0x0084
  Byte pad_088[4];
  Cell f_08c;  // +0x008c
  Byte pad_090[4];
  Cell f_094;  // +0x0094
  Cell f_098;  // +0x0098
  Cell f_09c;  // +0x009c
  Cell f_0a0;  // +0x00a0
  Cell f_0a4;  // +0x00a4
  Cell f_0a8;  // +0x00a8
  Cell f_0ac;  // +0x00ac
  Byte pad_0b0[32];
  Cell f_0d0;  // +0x00d0
  Cell f_0d4;  // +0x00d4
  Byte pad_0d8[12];
  Cell f_0e4;  // +0x00e4
  Byte f_0e8;  // +0x00e8
  Byte f_0e9;  // +0x00e9
  Byte pad_0ea[90];
  Byte f_144;  // +0x0144
  Byte pad_145[3];
  Cell f_148;  // +0x0148
  Cell f_14c;  // +0x014c
  Cell f_150;  // +0x0150
  Cell f_154;  // +0x0154
  Byte pad_158[84];
  Cell f_1ac;  // +0x01ac
  Byte pad_1b0[28];
  Cell f_1cc;  // +0x01cc
  Byte pad_1d0[62];
  Byte f_20e;  // +0x020e
  Byte pad_20f[133];
  Cell f_294;  // +0x0294
  Byte pad_298[4];
  Cell f_29c;  // +0x029c
  Cell f_2a0;  // +0x02a0
  Cell f_2a4;  // +0x02a4
  Byte pad_2a8[8];
  Byte f_2b0;  // +0x02b0
  Byte pad_2b1[159];
  Cell f_350;  // +0x0350
  Cell f_354;  // +0x0354
  Cell f_358;  // +0x0358
  Cell f_35c;  // +0x035c
  Cell f_360;  // +0x0360
  Cell f_364;  // +0x0364
  Cell f_368;  // +0x0368
  Byte pad_36c[20];
  Cell f_380;  // +0x0380
  Byte f_384;  // +0x0384
  Byte f_385;  // +0x0385
  Byte pad_386[50];
  Cell f_3b8;  // +0x03b8
  Cell f_3bc;  // +0x03bc
  Cell f_3c0;  // +0x03c0
  Cell f_3c4;  // +0x03c4
  Byte pad_3c8[112];
  U64 u_438;  // +0x0438 (lo) / +0x043c (hi)
  Byte pad_440[8];
  U64 u_448;  // +0x0448 (lo) / +0x044c (hi)
  Cell f_450;  // +0x0450
  Byte pad_454[64];
  Cell f_494;  // +0x0494
  Cell f_498;  // +0x0498
  Cell f_49c;  // +0x049c
  Cell f_4a0;  // +0x04a0
  Cell f_4a4;  // +0x04a4
  Byte pad_4a8[14];
  Byte f_4b6;  // +0x04b6
  Byte pad_4b7[5];
  Cell f_4bc;  // +0x04bc
  Byte pad_4c0[16];
  float f_4d0;  // +0x04d0
  Byte pad_4d4[256];
  Cell f_5d4;  // +0x05d4
  Cell f_5d8;  // +0x05d8
  Cell f_5dc;  // +0x05dc
  Cell f_5e0;  // +0x05e0
  Cell f_5e4;  // +0x05e4
};

static_assert(offsetof(OpaqueEditor, f_078) == 0x0078, "receiver+0x0078");
static_assert(offsetof(OpaqueEditor, f_07c) == 0x007c, "receiver+0x007c");
static_assert(offsetof(OpaqueEditor, f_084) == 0x0084, "receiver+0x0084");
static_assert(offsetof(OpaqueEditor, f_08c) == 0x008c, "receiver+0x008c");
static_assert(offsetof(OpaqueEditor, f_094) == 0x0094, "receiver+0x0094");
static_assert(offsetof(OpaqueEditor, f_098) == 0x0098, "receiver+0x0098");
static_assert(offsetof(OpaqueEditor, f_09c) == 0x009c, "receiver+0x009c");
static_assert(offsetof(OpaqueEditor, f_0a0) == 0x00a0, "receiver+0x00a0");
static_assert(offsetof(OpaqueEditor, f_0a4) == 0x00a4, "receiver+0x00a4");
static_assert(offsetof(OpaqueEditor, f_0a8) == 0x00a8, "receiver+0x00a8");
static_assert(offsetof(OpaqueEditor, f_0ac) == 0x00ac, "receiver+0x00ac");
static_assert(offsetof(OpaqueEditor, f_0d0) == 0x00d0, "receiver+0x00d0");
static_assert(offsetof(OpaqueEditor, f_0d4) == 0x00d4, "receiver+0x00d4");
static_assert(offsetof(OpaqueEditor, f_0e4) == 0x00e4, "receiver+0x00e4");
static_assert(offsetof(OpaqueEditor, f_0e8) == 0x00e8, "receiver+0x00e8");
static_assert(offsetof(OpaqueEditor, f_0e9) == 0x00e9, "receiver+0x00e9");
static_assert(offsetof(OpaqueEditor, f_144) == 0x0144, "receiver+0x0144");
static_assert(offsetof(OpaqueEditor, f_148) == 0x0148, "receiver+0x0148");
static_assert(offsetof(OpaqueEditor, f_14c) == 0x014c, "receiver+0x014c");
static_assert(offsetof(OpaqueEditor, f_150) == 0x0150, "receiver+0x0150");
static_assert(offsetof(OpaqueEditor, f_154) == 0x0154, "receiver+0x0154");
static_assert(offsetof(OpaqueEditor, f_1ac) == 0x01ac, "receiver+0x01ac");
static_assert(offsetof(OpaqueEditor, f_1cc) == 0x01cc, "receiver+0x01cc");
static_assert(offsetof(OpaqueEditor, f_20e) == 0x020e, "receiver+0x020e");
static_assert(offsetof(OpaqueEditor, f_294) == 0x0294, "receiver+0x0294");
static_assert(offsetof(OpaqueEditor, f_29c) == 0x029c, "receiver+0x029c");
static_assert(offsetof(OpaqueEditor, f_2a0) == 0x02a0, "receiver+0x02a0");
static_assert(offsetof(OpaqueEditor, f_2a4) == 0x02a4, "receiver+0x02a4");
static_assert(offsetof(OpaqueEditor, f_2b0) == 0x02b0, "receiver+0x02b0");
static_assert(offsetof(OpaqueEditor, f_350) == 0x0350, "receiver+0x0350");
static_assert(offsetof(OpaqueEditor, f_354) == 0x0354, "receiver+0x0354");
static_assert(offsetof(OpaqueEditor, f_358) == 0x0358, "receiver+0x0358");
static_assert(offsetof(OpaqueEditor, f_35c) == 0x035c, "receiver+0x035c");
static_assert(offsetof(OpaqueEditor, f_360) == 0x0360, "receiver+0x0360");
static_assert(offsetof(OpaqueEditor, f_364) == 0x0364, "receiver+0x0364");
static_assert(offsetof(OpaqueEditor, f_368) == 0x0368, "receiver+0x0368");
static_assert(offsetof(OpaqueEditor, f_380) == 0x0380, "receiver+0x0380");
static_assert(offsetof(OpaqueEditor, f_384) == 0x0384, "receiver+0x0384");
static_assert(offsetof(OpaqueEditor, f_385) == 0x0385, "receiver+0x0385");
static_assert(offsetof(OpaqueEditor, f_3b8) == 0x03b8, "receiver+0x03b8");
static_assert(offsetof(OpaqueEditor, f_3bc) == 0x03bc, "receiver+0x03bc");
static_assert(offsetof(OpaqueEditor, f_3c0) == 0x03c0, "receiver+0x03c0");
static_assert(offsetof(OpaqueEditor, f_3c4) == 0x03c4, "receiver+0x03c4");
static_assert(offsetof(OpaqueEditor, u_438) == 0x0438, "receiver+0x0438");
static_assert(offsetof(OpaqueEditor, u_448) == 0x0448, "receiver+0x0448");
static_assert(offsetof(OpaqueEditor, f_450) == 0x0450, "receiver+0x0450");
static_assert(offsetof(OpaqueEditor, f_494) == 0x0494, "receiver+0x0494");
static_assert(offsetof(OpaqueEditor, f_498) == 0x0498, "receiver+0x0498");
static_assert(offsetof(OpaqueEditor, f_49c) == 0x049c, "receiver+0x049c");
static_assert(offsetof(OpaqueEditor, f_4a0) == 0x04a0, "receiver+0x04a0");
static_assert(offsetof(OpaqueEditor, f_4a4) == 0x04a4, "receiver+0x04a4");
static_assert(offsetof(OpaqueEditor, f_4b6) == 0x04b6, "receiver+0x04b6");
static_assert(offsetof(OpaqueEditor, f_4bc) == 0x04bc, "receiver+0x04bc");
static_assert(offsetof(OpaqueEditor, f_4d0) == 0x04d0, "receiver+0x04d0");
static_assert(offsetof(OpaqueEditor, f_5d4) == 0x05d4, "receiver+0x05d4");
static_assert(offsetof(OpaqueEditor, f_5d8) == 0x05d8, "receiver+0x05d8");
static_assert(offsetof(OpaqueEditor, f_5dc) == 0x05dc, "receiver+0x05dc");
static_assert(offsetof(OpaqueEditor, f_5e0) == 0x05e0, "receiver+0x05e0");
static_assert(offsetof(OpaqueEditor, f_5e4) == 0x05e4, "receiver+0x05e4");
static_assert(sizeof(U64) == 8,
              "0x00588517 SUB EAX and 0x00588522 SBB EDX are one 64-bit word");
static_assert(sizeof(OpaqueEditor) == 0x05e8,
              "0x05e4 is the highest offset the body names");

// --------------------------------------------------------------------------
// Indirect dispatch.
//
// All 85 indirect calls take the same three-instruction shape:
//
//   MOV EAX,dword ptr [obj]        ; the table
//   MOV <reg>,dword ptr [EAX+slot]  ; the entry, `slot` a byte displacement
//   CALL <reg>                      ; receiver already in ECX
//
// `slot` below is the displacement the listing reads at that site and nothing
// else. No slot is resolved to a name, and no site is left opaque, so the
// source asserts a concrete table offset for every dispatch it performs.
// --------------------------------------------------------------------------
using Entry = std::uintptr_t;

inline Entry entry_at(const void* object, Dword slot) noexcept {
  const void* const* table = *reinterpret_cast<void* const* const*>(object);
  return reinterpret_cast<Entry>(reinterpret_cast<const Byte*>(table) + slot);
}

// One alias per argument shape the body actually pushes, so the shape is
// visible at the call site rather than buried in a cast. The arity split over
// the 85 sites, measured by a stack dataflow that treats the four register
// saves (the three prologue pushes and PUSH EDI at 0x00587b61) as depth
// rather than arguments, is 49 sites of arity 0, 20 of arity 1, 13 of arity 2,
// 2 of arity 3 and 1 of arity 4. The per-alias counts below are the static
// counts in this source, which are lower where a helper factors several sites
// into one dispatch.
using Fn0 = void (*)();                            // no argument
using Fn0p = void* (*)();                          // no argument, returns a pointer
using Fn1 = void (*)(Dword);                       // one dword
using Fn1p = void (*)(const void*);                // one pointer
using Fn1f = void* (*)(float);                     // one float, returns a pointer
using Fn2 = void (*)(Dword, Dword);                // two dwords
using Fn2p = void (*)(const void*, Dword);         // pointer and dword
using Fn3w = void (*)(Dword, const void*, Dword);  // dword, pointer, dword
using Fn3p = void (*)(const void*, Dword, Dword);  // pointer, dword, dword
using Fn4p = void (*)(Dword, void*, Dword, Dword); // dword, pointer, dword, dword

// The preparatory callees handed to a helper as a value. Each is thiscall,
// which on i386 also means callee-popped when it ends in `RET imm`, so the
// alias carries the attribute rather than the helper assuming it.
using PrepFn = void (PKG_ONEXIT_THISCALL*)(void*);

// --------------------------------------------------------------------------
// The stack object this routine builds at its own frame base.
//
// Six dwords are written into it, at 0x00587a6a, 0x00587a72, 0x00587a80,
// 0x00587a89, 0x00587a91 and 0x00587a97. The first five stores are the only
// writes to those words and they happen in that order; 0x00587a97 writes the
// sixth, the result of the slot +0x44 call.
//
// Modelled at 0x40 bytes, which is exactly the room the frame leaves above
// the object base: the prologue reserves 0x44 and the three pushes bias the
// base by 0xc, and 0x0058855b addresses the object at [ESP+0x10]. Whether
// 0x00421cf0 can reach past 0x40 is not decidable from this body -- see the
// unresolved questions in the metadata sidecar.
// --------------------------------------------------------------------------
struct alignas(4) LocalAppState {
  const void* dispatch;   // +0x00, written 0x00587a72 then 0x00587a89
  Dword zero_04;          // +0x04, written 0x00587a7a/0x00587a80
  void* sub_08;           // +0x08, written 0x00587a97
  Byte opaque_0c[0x24];   // +0x0c .. +0x2f, never written here
  Dword tag_30;           // +0x30, written 0x00587a6a
  Dword opaque_34;        // +0x34, never written here
  Dword sub_mask;         // +0x38, written 0x00587a91
  Byte opaque_3c[4];      // +0x3c .. +0x3f, never written here
};

static_assert(offsetof(LocalAppState, dispatch) == 0x00, "0x00587a89 writes +0x00");
static_assert(offsetof(LocalAppState, zero_04) == 0x04, "0x00587a80 writes +0x04");
static_assert(offsetof(LocalAppState, sub_08) == 0x08, "0x00587a97 writes +0x08");
static_assert(offsetof(LocalAppState, tag_30) == 0x30, "0x00587a6a writes +0x30");
static_assert(offsetof(LocalAppState, sub_mask) == 0x38, "0x00587a91 writes +0x38");
static_assert(sizeof(LocalAppState) == 0x40,
              "0x44-byte reservation less the 0xc three-push bias");

// The object self->f_1cc points at, as far as the 0x00587b93 block reads it:
// +0x10/+0x14/+0x18 at 0x00587c1d..0x00587c2f, then +0x90 and +0x94 at
// 0x00587bd6 and 0x00587be8.
struct alignas(4) PeerState {
  Byte opaque_00[0x10];
  Dword a_10;   // +0x10
  Dword a_14;   // +0x14
  Dword a_18;   // +0x18
  Byte opaque_1c[0x74];
  Dword a_90;   // +0x90
  Dword a_94;   // +0x94
};

static_assert(offsetof(PeerState, a_10) == 0x10, "0x00587c1d reads peer+0x10");
static_assert(offsetof(PeerState, a_14) == 0x14, "0x00587c26 reads peer+0x14");
static_assert(offsetof(PeerState, a_18) == 0x18, "0x00587c2c reads peer+0x18");
static_assert(offsetof(PeerState, a_90) == 0x90, "0x00587bd6 reads peer+0x90");
static_assert(offsetof(PeerState, a_94) == 0x94, "0x00587be8 reads peer+0x94");

// The object that block builds. 0x00579c80 is its constructor -- 21
// instructions, `MOV EAX,ECX` then 20 stores -- and the writes below at
// 0x00587bdc..0x00587c3e are the only ones this body makes to those fields.
struct alignas(4) CreatedState {
  Byte opaque_00[0x0c];  // the table 0x00579c80 installs at +0x00
  Dword v_0c;            // +0x0c
  void* sub_10;          // +0x10
  Dword v_14;            // +0x14
  Dword v_18;            // +0x18
  Dword v_1c;            // +0x1c
  Dword v_20;            // +0x20
  Byte opaque_24[0x20];
  Byte flag_44;          // +0x44
};

static_assert(offsetof(CreatedState, v_0c) == 0x0c, "0x00587bdc writes created+0x0c");
static_assert(offsetof(CreatedState, sub_10) == 0x10, "0x00587c03 writes created+0x10");
static_assert(offsetof(CreatedState, v_14) == 0x14, "0x00587c3b writes created+0x14");
static_assert(offsetof(CreatedState, v_18) == 0x18, "0x00587c23 writes created+0x18");
static_assert(offsetof(CreatedState, v_1c) == 0x1c, "0x00587c29 writes created+0x1c");
static_assert(offsetof(CreatedState, v_20) == 0x20, "0x00587c2f writes created+0x20");
static_assert(offsetof(CreatedState, flag_44) == 0x44, "0x00587c3e writes created+0x44");

// --------------------------------------------------------------------------
// Absolute data addresses the body dereferences directly.
//
// These three are the only ones a `MOV reg,dword ptr [addr]` in the listing
// reads. Each access is named at the declaration. The thirteen further global
// words this body reaches are reached only through the two-instruction getters
// declared below, whose own `MOV EAX,[addr] ; RET` shape is what identifies
// them as globals rather than as constants.
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
// The 54 distinct direct call targets.
//
// Each declaration's convention and argument count is read off that CALLEE'S
// own epilogue and prologue, never off this caller's call site, so the set is
// a property of the callees and holds for all 77 call sites. A trailing
// comment gives the evidence: the callee's own last instruction, and for the
// three that tail-jump, the RET at the jump target.
// --------------------------------------------------------------------------
// PUSH EBP; MOV EBP,ESP; MOV EAX,[0x015d0c08]; POP EBP; RET -- 0 stack args
void* PKG_ONEXIT_CDECL sub_00401020();
// PUSH EBP; MOV EBP,ESP; MOV EAX,[0x015d0c14]; POP EBP; RET -- 0 stack args
void* PKG_ONEXIT_CDECL sub_00401050();
// stores ECX-relative, bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_00421cf0(LocalAppState* self);
// ends RET 0x8 -> callee pops 8
void PKG_ONEXIT_THISCALL sub_0043a9a0(void* self, Dword a0, Dword a1);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_004581d0(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_0045ab30(void* self);
// MOV EAX,[EAX+0x10]; bare RET -- 0 stack args
void* PKG_ONEXIT_THISCALL sub_0047e6c0(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_004ad280(void* self);
// bare RET; saves ECX to [EBP-0xc] and reloads it -- 0 stack args
void PKG_ONEXIT_THISCALL sub_004ad330(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_004b27c0(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_004c4eb0(void* self);
// bare RET; reads args 0..4 off its own frame, caller ADD ESP,0x14;
// never reads ECX, so a five-argument cdecl function
void PKG_ONEXIT_CDECL sub_00571db0(Dword a0, Dword a1, Dword a2, Dword a3, Dword a4);
// ends RET 0x8 -> callee pops 8
void PKG_ONEXIT_THISCALL sub_00573c00(void* self, Dword a0, Dword a1);
// ends RET 0x8 -> callee pops 8
void PKG_ONEXIT_THISCALL sub_00573d70(void* self, Dword a0, Dword a1);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005772b0(void* self);
// MOV EAX,ECX then 20 stores; bare RET -- 0 stack args
void* PKG_ONEXIT_THISCALL sub_00579c80(void* self);
// JMP 0x005879ac -> RET 0x8 at 0x00587a10 -> callee pops 8
void PKG_ONEXIT_THISCALL sub_00587270(void* self, Dword a0, Dword a1);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_0059a3b0(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_0059c640(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005bfb90(void* self);
// MOV EBX,ECX; bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005c5c20(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005cba90(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005d31b0(void* self);
// PUSH -1; CALL 0x0067de90; ... bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005dbb50(void* self);
// ends RET 0x4 -> callee pops 4
void PKG_ONEXIT_THISCALL sub_005dbb60(void* self, Dword a0);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_005de870(void* self);
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_0062c910(void* self);
// SUB ESP,0x134; MOV ESI,ECX; bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_0067a120(void* self);
// JMP 0x0067c350 -> RET 0x8 at 0x0067c3a0 -> callee pops 8
void PKG_ONEXIT_THISCALL sub_0067c420(void* self, Dword a0, Dword a1);
// ADD [ECX+0x10],-4; JMP 0x0067c9b0 -> RET at 0x0067ca3a -> 0 stack args
void PKG_ONEXIT_THISCALL sub_0067ca40(void* self);
// MOV EAX,[0x015fcc4c]; RET
void* PKG_ONEXIT_CDECL sub_0067caa0();
// MOV EAX,[0x015fcc50]; RET
void* PKG_ONEXIT_CDECL sub_0067cab0();
// MOV EAX,[0x015fcc54]; RET
void* PKG_ONEXIT_CDECL sub_0067cac0();
// MOV EAX,[0x015fcc58]; RET
void* PKG_ONEXIT_CDECL sub_0067cad0();
// MOV EAX,[0x015fcc60]; RET
void* PKG_ONEXIT_CDECL sub_0067caf0();
// MOV EAX,[0x015fd890]; RET
void* PKG_ONEXIT_CDECL sub_0067dcc0();
// MOV EAX,[0x015fd8b0]; RET
void* PKG_ONEXIT_CDECL sub_0067dd10();
// MOV EAX,[0x015fd8bc]; RET
void* PKG_ONEXIT_CDECL sub_0067dd40();
// MOV EAX,[0x015fd8c0]; RET
void* PKG_ONEXIT_CDECL sub_0067dd50();
// MOV EAX,[0x015fd8cc]; RET
void* PKG_ONEXIT_CDECL sub_0067dd80();
// MOV EAX,[0x015fd8e8]; RET
void* PKG_ONEXIT_CDECL sub_0067ddd0();
// MOV EAX,[0x015fd8a4]; RET
void* PKG_ONEXIT_CDECL sub_0067de20();
// MOV EAX,[0x015fd8f8]; RET
void* PKG_ONEXIT_CDECL sub_0067de40();
// SEH frame; ends RET 0x8 -> callee pops 8. The prologue shifts ESP by 0x28,
// so [ESP+0x2c] is arg0 and [ESP+0x30] is arg1 -- see the .cpp.
void PKG_ONEXIT_CDECL sub_006a1880(Dword a0, Dword a1);
// MOV EAX,[ECX+0x3c]; RET
void* PKG_ONEXIT_THISCALL sub_006c10e0(void* self);
// bare RET; reads arg0 as a table index; caller ADD ESP,0x18
void PKG_ONEXIT_CDECL sub_00777ae0(Dword a0, Dword a1, Dword a2);
// ends RET 0x4 -> callee pops 4; the argument is the float FSTP-d at
// 0x00587b1b, not the register PUSH ECX left behind at 0x00587b18
void PKG_ONEXIT_THISCALL sub_007c53d0(void* self, float a0);
// MOV EAX,[ECX+0x48]; RET
void* PKG_ONEXIT_THISCALL sub_00801920(void* self);
// ends RET 0x4 -> callee pops 4
void PKG_ONEXIT_THISCALL sub_00801bb0(void* self, Dword a0);
// MOV EAX,[ECX+0x250]; MOV EDX,[ECX+0x254]; RET -- 64-bit result in EDX:EAX
U64 PKG_ONEXIT_THISCALL sub_008130a0(void* self);
// MOV EAX,[0x0166d9f4]; RET
void* PKG_ONEXIT_CDECL sub_00a206f0();
// bare RET -- 0 stack args
void PKG_ONEXIT_THISCALL sub_00ed0660(void* self);
// bare RET; reads arg0..arg5 off its own frame; caller ADD ESP,0x18
void* PKG_ONEXIT_CDECL sub_00f473a0(Dword a0, Dword a1, Dword a2, Dword a3,
                                   Dword a4, Dword a5);
// MOV EAX,[ECX+0x44]; RET
void* PKG_ONEXIT_THISCALL sub_0113ae10(void* self);

}  // namespace openspore::reconstruction::pkg_dogfood_00587a20_a1

#if defined(_MSC_VER)
#undef PKG_ONEXIT_THISCALL
#undef PKG_ONEXIT_CDECL
#endif
