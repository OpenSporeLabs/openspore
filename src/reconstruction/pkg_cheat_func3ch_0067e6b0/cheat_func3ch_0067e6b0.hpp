#pragma once

// Bounded clean-room reconstruction of SporeApp.exe 0x0067e6b0
// (App::cCheatManager::func3Ch), build 3.1.0.22, image base 0x00400000.
//
// Scope. Eleven instructions, 0x0067e6b0..0x0067e6cc. The body is a tail call
// to 0x0067e2b0, a bit-0 test of its single stack argument, one conditional
// cdecl call to 0x00f47380 carrying the receiver, and a return of the receiver
// in EAX. Every displacement in the *callee* chain is quoted here as a comment
// and never silently turned into a member access: those words belong to
// functions this package does not implement.
//
// Machine transcript (Ghidra 12.1.2 /disassemble_function, 11 instructions):
//
//   0x0067e6b0  56              PUSH ESI
//   0x0067e6b1  8B F1           MOV ESI,ECX
//   0x0067e6b3  E8 F8 FB FF FF  CALL 0x0067e2b0
//   0x0067e6b8  F6 44 24 08 01  TEST byte ptr [ESP + 0x8],0x1
//   0x0067e6bd  74 09           JZ 0x0067e6c8
//   0x0067e6bf  56              PUSH ESI
//   0x0067e6c0  E8 BB 8C 8C 00  CALL 0x00f47380
//   0x0067e6c5  83 C4 04        ADD ESP,0x4
//   0x0067e6c8  8B C6           MOV EAX,ESI
//   0x0067e6ca  5E              POP ESI
//   0x0067e6cb  C2 04 00        RET 0x4
//
// The body is 29 bytes; the two CC bytes at 0x0067e6cd are padding, which is
// why Ghidra reports the body end as 0x0067e6cd.
//
// Reading the two stack references. PUSH ESI is the only frame change made
// before the first call, so [ESP+0x8] at 0x0067e6b8 is entry_ESP+0x4: the one
// ordinary argument. 0x0067e2b0 pushes nothing and ends in a plain RET
// (0x0067e301), so ESP is unchanged across it and the mapping holds; the test
// is on the low BYTE of that word, i.e. bit 0 only, not the whole word.
//
// Provenance. Live Ghidra decompile + disassemble of 0x0067e6b0, of the sole
// direct callee 0x0067e2b0, of the branch callee 0x00f47380 and of its callee
// 0x009276c0; a reference scan showing 0x0067e6b0 has exactly one inbound
// reference, a DATA reference from 0x01401900 (a vtable slot, no direct
// callers). Layout continuity for the receiver tail comes from the sibling
// entries 0x0067e6f0 / 0x0067e730 recorded in
// reconstruction/evidence/0067e6f0/evidence.json and
// reconstruction/metadata/dogfood-after-02-0067e730/0067e730.json.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "cheat func3Ch 0067e6b0 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CHEAT3_CDECL __cdecl
#define PKG_CHEAT3_THISCALL __thiscall
#else
#define PKG_CHEAT3_CDECL __attribute__((cdecl))
#define PKG_CHEAT3_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_cheat_func3ch_0067e6b0 {

static_assert(sizeof(void*) == 4, "this reconstruction is 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "opaque words are 32-bit");

// One machine word. The body never states what the argument word means, so it
// is carried as an opaque word and only bit 0 is given a meaning, because the
// listing tests exactly that bit.
using OpaqueWord = std::uint32_t;

// The only bit this body gives meaning to:
//   0x0067e6b8  TEST byte ptr [ESP + 0x8],0x1
// i.e. bit 0 of the low byte of entry_ESP+0x4.
constexpr OpaqueWord kGateMask = 0x1u;

// ---------------------------------------------------------------------------
// The object reached through the receiver word at +0x14
// ---------------------------------------------------------------------------
// These two types describe the CALLEE 0x0067e2b0, not this body, and are
// declared only so the mechanic can be named in the metadata and in the model
// test. 0x0067e2b0 reads 0x0067e2cd  MOV ECX,dword ptr [ESI + 0x14], then
// 0x0067e2dc  MOV EAX,dword ptr [ECX]  and 0x0067e2de  MOV EDX,dword ptr
// [EAX + 0x10] and calls EDX with ECX unchanged.
struct SubObject;

struct SubObjectVTable {
  void* prefix_000[4]{};
  void (PKG_CHEAT3_THISCALL* entry_10)(SubObject*) = nullptr;
};

struct SubObject {
  SubObjectVTable* table_000 = nullptr;
};

static_assert(offsetof(SubObjectVTable, entry_10) == 0x10,
              "the callee calls vtable slot +0x10, the fifth dword");

// ---------------------------------------------------------------------------
// The receiver
// ---------------------------------------------------------------------------
// Offsets are only what the listings of this function and its two
// cross-read siblings show. Nothing else is named, and the gaps are declared
// as opaque words rather than guessed members.
struct CheatManager {
  // +0x00 is the vptr: 0x0067e12b  MOV dword ptr [ESI],0x14018b0 in the
  // constructor 0x0067e100, and 0x0083c750 stores &PTR_purecall_0141b5ac
  // through the same word. It is listed as opaque because no instruction of
  // this body loads it.
  OpaqueWord opaque_000[5]{};       // +0x00 .. +0x13
  SubObject* subobject_014 = nullptr;  // 0x0067e2cd, read by the first callee
  OpaqueWord opaque_018[3]{};       // +0x18 .. +0x23
  OpaqueWord* owner_024 = nullptr;  // 0x0067e139, written by 0x0067e100
  OpaqueWord opaque_028[15]{};      // +0x28 .. +0x63
  std::uint8_t gate_064 = 0;        // sibling 0x0067e6f0 tests this byte
};

static_assert(offsetof(CheatManager, subobject_014) == 0x14,
              "the first callee reads the receiver word at +0x14");
static_assert(offsetof(CheatManager, owner_024) == 0x24,
              "the constructor stores its second argument at +0x24");
static_assert(offsetof(CheatManager, gate_064) == 0x64,
              "the sibling entry 0x0067e6f0 gates on this byte");

// ---------------------------------------------------------------------------
// The global reached by the branch callee
// ---------------------------------------------------------------------------
// 0x00f47388  MOV ECX,dword ptr [0x016c8b44] -- Ghidra names that word
// GeneralAllocator::sInstance. 0x009276c0 then reads [ECX+0x4e4] and brackets
// its call to 0x00926fd0 with an INC/DEC of [that+0x18] and two indirect calls
// through the import slots 0x013cc2d8 and 0x013cc2dc. The import names are NOT
// resolved in this program database, so no API name is claimed here; only the
// displacement and the shape are.
struct AllocatorSingleton {
  OpaqueWord opaque_000[313]{};
  OpaqueWord* lock_04e4 = nullptr;
};

static_assert(offsetof(AllocatorSingleton, lock_04e4) == 0x4e4,
              "the second-hop callee reads its lock word at +0x4e4");

// ---------------------------------------------------------------------------
// Call shapes
// ---------------------------------------------------------------------------
// 0x0067e2b0: receiver in ECX, nothing pushed, plain RET in the callee, so the
// stack is untouched across the call and this is a thiscall with no stack
// argument.
using TeardownEntry = void (PKG_CHEAT3_THISCALL*)(CheatManager* manager);

// 0x00f47380: one argument pushed by the caller (0x0067e6bf PUSH ESI) and
// dropped by the caller (0x0067e6c5 ADD ESP,0x4); the callee ends in a plain
// RET, so this is cdecl with one stack argument. The argument is the receiver.
using SubmitEntry = void (PKG_CHEAT3_CDECL*)(CheatManager* manager);

// Both callees live outside this body, so they are reached through a port
// table the model test can substitute. The VA is kept in each field name; the
// pointer values themselves are not invented.
struct Ports {
  TeardownEntry teardown_0067e2b0 = nullptr;
  SubmitEntry submit_00f47380 = nullptr;
};

extern Ports* g_cheat_func3ch_ports;

// ---------------------------------------------------------------------------
// The entry
// ---------------------------------------------------------------------------
// __thiscall, receiver in ECX, one 4-byte stack argument at entry_ESP+0x4 that
// the callee reclaims itself (RET 0x4 at 0x0067e6cb).
//
// Return type. The SDK/Ghidra signature says void, but the listing writes the
// receiver into EAX at 0x0067e6c8 on the single exit path. The declaration
// below follows the machine and returns that pointer; whether any consumer
// reads it is unproven, because the only inbound reference to this function is
// its vtable slot and no call site of that slot is known. See the sidecar's
// observed_original_abi.return_semantics.
extern "C" CheatManager* PKG_CHEAT3_THISCALL func3_ch_0067e6b0(
    CheatManager* manager, OpaqueWord gate_word);

}

#undef PKG_CHEAT3_CDECL
#undef PKG_CHEAT3_THISCALL
