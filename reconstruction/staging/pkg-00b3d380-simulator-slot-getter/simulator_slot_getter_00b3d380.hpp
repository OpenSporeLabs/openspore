#pragma once

// Reconstruction of FUN_00b3d380 @ 0x00b3d380 (SporeApp.exe 3.1.0.22,
// SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// EVIDENCE BASIS (every claim below is traceable to one of these; nothing else
// is claimed).
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete:
//        0x00b3d380  a1 04 eb 67 01   MOV EAX,dword ptr ds:[0x0167eb04]
//        0x00b3d385  c3               RET
//     raw bytes at 0x00b3d380..0x00b3d386 are a1 04 eb 67 01 c3, read live from
//     the program database and independently re-read from the pinned file; the
//     following 0xcc is the INT3 pad and is NOT part of the body. Body span
//     0x00b3d380..0x00b3d386, 6 bytes, matching the committed function table
//     (.spore-analysis/ghidra-exports/functions.tsv, entry 00b3d380, size 6).
//
//  2. Live Ghidra decompilation, which adds nothing to (1) and is consistent
//     with it:
//        undefined4 FUN_00b3d380(void) { return DAT_0167eb04; }
//
//  3. Derived ABI record for this VA (INFERRED): architecture x86-32, no
//     receiver (ECX is never read in any form), 0 ordinary stack arguments,
//     bare RET with no immediate so the callee pops nothing and the caller owns
//     stack cleanup, return value in EAX. The record itself abstains from naming
//     a convention: `abstained_because: no_discriminator: no stack-argument read
//     and no positive receiver evidence`, and reports all four candidate
//     conventions as byte-identical. That is a real property of a zero-parameter
//     entry, so this package does not pick one; the model test MEASURED the
//     cleanup instead of asserting a convention it cannot derive.
//
//  4. Committed data-reference sidecar knowledgegraph/triage/datarefs-2540f2ca.tsv
//     contains exactly ONE row for 0x0167eb04, and it is this load:
//        00b3d380  0167eb04  read  .data -wr  00b3d380
//     So: one direct reader, zero direct writers anywhere in the pinned image.
//     Independently re-checked against the pinned file: the little-endian
//     encoding 04 eb 67 01 occurs EXACTLY ONCE in all 20,454,960 bytes, at file
//     offset 0x73c781, which is the disp32 of this instruction. Absence of a
//     direct writer is NOT an immutability claim; indirect or bulk publication
//     remains unexcluded, exactly as knowledgegraph/research/root-closure/
//     followup-global-slots.md:22,218 states for the sibling slots.
//
//  5. Committed edge sidecar knowledgegraph/triage/xrefs-2540f2ca.tsv records
//     240 direct callsites of 0x00b3d380 across 165 distinct caller functions.
//     This is the high-fan-in profile of the accessor block, and it says nothing
//     about the pointee's class.
//
//  6. Structural, from an objdump disassembly of the pinned binary over
//     0x00b3d1c0..0x00b3d520 (read-only; the whole block is 0x360 bytes):
//     43 six-byte accessors at 0x00b3d230..0x00b3d510 load 43 DISTINCT
//     consecutive 4-byte words of .data covering 0x0167eac0..0x0167eb68 with no
//     gap and no duplicate - a bijection from accessor to slot over that range.
//     The immediately preceding function confirms the base independently:
//        0x00b3d220  b8 c0 ea 67 01  MOV EAX,0x0167eac0 ; RET
//     i.e. 0x00b3d220 returns the TABLE ADDRESS as an immediate while
//     0x00b3d230 dereferences it. 0x00b3d380/DAT_0167eb04 is therefore table
//     offset 0x44. Ghidra's SDK import names only some of these accessors; the
//     named neighbours of this slot are 0x0167eafc -> Simulator::cGameBehaviorManager::Get
//     (0x00b3d360), 0x0167eb00 -> unnamed (0x00b3d370), 0x0167eb08 -> unnamed
//     (0x00b3d390) and 0x0167eb0c -> Simulator::cStarManager::Get (0x00b3d3a0).
//
//  7. Pointee shape, from three INDEPENDENT callers that dereference the result
//     and only ever reach one field on it:
//        0x01042450  iVar1 = FUN_00b3d380(); if ((*(byte *)(iVar1 + 0x48) & 1) == 0)
//        0x01017b70  iVar2 = FUN_00b3d380(); if ((*(byte *)(iVar2 + 0x48) & 1) == 0)
//        0x01017ce0  iVar2 = FUN_00b3d380(); if ((*(byte *)(iVar2 + 0x48) & 1) == 0)
//     So the returned word is consumed as a POINTER (not compared, not
//     bit-masked as a scalar), and one observed byte field sits at +0x48 with
//     bit 0 tested. That is the only pointee offset any sampled caller shows,
//     and the FIELD IS UNNAMED - no Simulator class, SDK symbol or field name
//     is claimed for it.
//
// WHAT IS NOT CLAIMED
//  * The class of the object in 0x0167eb04. It is UNKNOWN. The type below is
//    opaque and exists only so the return is spelled as the pointer the callers
//    demonstrably dereference. No Simulator::* identity is asserted, even though
//    the slot sits inside the same .data table as the SDK-named manager getters.
//  * Any writer, teardown, publication order, nullability, thread-safety or
//    AddRef/Release ownership for the slot.
//  * A calling convention. See (3).
//  * The size of the pointee. The single observed offset +0x48 is a MODELLING
//    BOUND, not a recovered extent.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b3d380 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b3d380_simulator_slot_getter {

// The unit the body actually moves: one 32-bit word in, one 32-bit word out.
using SlotWord = std::uint32_t;

static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(void *) == 4, "x86-32 target pointers are 32-bit");

// The global whose word this accessor returns. 0x0167eb04 is the .data slot;
// it is a genuine 4-byte-aligned address, not a packed structure, and the
// committed data-reference sidecar records exactly one reference to it in the
// whole image (this load).
//
// It is declared as a REFERENCE to the slot word so that whichever unit links
// the reconstruction supplies the storage. In the real image that storage is
// the fixed .data word at 0x0167eb04; the model test binds it into a window it
// can plant neighbours and guard bands into, which is why kSlotVa below is a
// statement about the IMAGE's address and not about this process's runtime
// address of the same name. A reference is the honest shape for a slot at a
// fixed VA: it cannot be re-seated, which is exactly what the body assumes.
extern "C" {
extern SlotWord& DAT_0167eb04;
}

// 0x0167eb04 itself.
constexpr std::uint32_t kSlotVa = 0x0167eb04u;

// 0x00b3d220 returns this as an immediate (`MOV EAX,0x0167eac0`); 0x00b3d230
// dereferences it. It is the base of the singleton slot table that the 43
// accessors of note (6) enumerate one word at a time.
constexpr std::uint32_t kSlotTableBaseVa = 0x0167eac0u;

// This slot's offset inside that table. 0x0167eb04 - 0x0167eac0 = 0x44.
constexpr std::uint32_t kSlotTableOffset = 0x44u;

// 0x00b3d380..0x00b3d386 is six bytes; the 0xcc after it is INT3 pad and is
// deliberately not part of kTargetEncoding.
constexpr std::size_t kTargetBodyBytes = 6;

// The body's bytes as read from 0x00b3d380. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0xa1,                    // MOV EAX, moffs32
    0x04, 0xeb, 0x67, 0x01,  // disp32 = 0x0167eb04, little endian
    0xc3,                    // RET
};

// The single pointee offset any sampled caller reaches (header note 7): a byte
// at +0x48 whose bit 0 is tested. The field is UNNAMED, so nothing in this
// package names it; the extent below exists only so a fixture can be planted
// far enough for +0x48 to be addressable.
constexpr std::size_t kCallerObservedFlagByteOffset = 0x48u;

// A modelling bound, deliberately NOT a recovered object size. Three callers
// prove the byte at +0x48 is readable and no caller in the sample shows a larger
// offset, so the fixture stops just past the byte the evidence actually reaches.
constexpr std::size_t kObservedPointeeModellingExtent = 0x4cu;

// The pointee of 0x0167eb04. UNKNOWN by evidence: no class, no SDK symbol, no
// field names. The struct exists so the returned pointer is a pointer type
// (see header note 7) and so the model test has something to plant into.
struct alignas(4) OpaqueSimulatorSingleton {
  std::uint8_t opaque_bytes[kObservedPointeeModellingExtent];
};

// x86-32 entry with 0 ordinary stack arguments, no register receiver, a bare
// RET (the callee pops nothing, the caller owns cleanup) and a 32-bit value
// return in EAX. The convention is deliberately left as the plain C default:
// for a zero-parameter entry the encoding is identical under cdecl, stdcall,
// thiscall and fastcall, and the derived ABI record abstains from choosing.
using AbiSlotGetter00b3d380 = OpaqueSimulatorSingleton* (*)();

static_assert(kSlotVa == kSlotTableBaseVa + kSlotTableOffset,
              "the slot address is the table base plus the table offset");
static_assert(kSlotTableOffset == 68u,
              "0x44 is the value 68, compared semantically not by spelling");
static_assert(kSlotVa == 0x0167eb04u,
              "the slot is 0x0167eb04, compared semantically not by spelling");
static_assert(kTargetEncoding[0] == 0xa1u && kTargetEncoding[5] == 0xc3u,
              "0x00b3d380 is MOV EAX,moffs32 and 0x00b3d385 is RET");
static_assert(kTargetEncoding[1] == 0x04u && kTargetEncoding[2] == 0xebu &&
                  kTargetEncoding[3] == 0x67u && kTargetEncoding[4] == 0x01u,
              "the disp32 bytes spell 0x0167eb04, little endian");
static_assert(kSlotVa == (static_cast<std::uint32_t>(kTargetEncoding[1]) |
                          (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
                          (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
                          (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)),
              "the header's slot VA equals the instruction's disp32");
static_assert(kTargetBodyBytes == 6u,
              "the body is 6 bytes, matching the committed function table");
static_assert(kCallerObservedFlagByteOffset < kObservedPointeeModellingExtent,
              "the only observed pointee byte lies inside the fixture extent");
static_assert(sizeof(OpaqueSimulatorSingleton) == kObservedPointeeModellingExtent,
              "the fixture is exactly the modelling extent");
static_assert(std::is_same<AbiSlotGetter00b3d380,
                           OpaqueSimulatorSingleton* (*)()>::value,
              "the modelled entry takes nothing and returns one pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00b3d380.
OpaqueSimulatorSingleton* simulator_slot_getter_00b3d380();

}
