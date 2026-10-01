#pragma once

// Reconstruction of FUN_00b3d390 @ 0x00b3d390 (SporeApp.exe 3.1.0.22,
// SHA-256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// EVIDENCE BASIS (every claim below is traceable to one of these; nothing else
// is claimed).
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete:
//        0x00b3d390  a1 08 eb 67 01   MOV EAX,dword ptr ds:[0x0167eb08]
//        0x00b3d395  c3               RET
//     Independently re-read from the pinned file: the PE raw bytes at that VA
//     are a1 08 eb 67 01 c3 cc cc - the six body bytes, then INT3 pad which is
//     NOT part of the body. Body span 0x00b3d390..0x00b3d396, 6 bytes,
//     matching the committed function table
//     (.spore-analysis/ghidra-exports/functions.tsv, entry 00b3d390, size 6).
//
//  2. Live Ghidra decompilation, which adds nothing to (1) and is consistent
//     with it:
//        undefined4 FUN_00b3d390(void) { return DAT_0167eb08; }
//
//  3. Derived ABI record for this VA (INFERRED): architecture x86-32, no
//     receiver (ECX is never read in any form), 0 ordinary stack arguments,
//     bare RET with no immediate so the callee pops nothing and the caller owns
//     stack cleanup, return value in EAX. The record itself abstains from
//     naming a convention: `abstained_because: no_discriminator: no
//     stack-argument read and no positive receiver evidence`, and reports all
//     four candidate conventions as byte-identical. That is a real property of a
//     zero-parameter entry, so this package does not pick one; the model test
//     argues the cleanup from the ENCODING instead of asserting a convention it
//     cannot derive.
//
//  4. Committed data-reference sidecar knowledgegraph/triage/datarefs-2540f2ca.tsv
//     contains exactly ONE row for 0x0167eb08, and it is this load:
//        00b3d390  0167eb08  read  .data -wr  00b3d390
//     So: one direct reader, zero direct writers anywhere in the pinned image.
//     Independently re-checked against the pinned file: the little-endian
//     encoding 08 eb 67 01 occurs EXACTLY ONCE in all 20,454,960 bytes, at file
//     offset 0x73c791, which is the disp32 of this instruction. Absence of a
//     direct writer is NOT an immutability claim; indirect or bulk publication
//     remains unexcluded, exactly as knowledgegraph/research/root-closure/
//     followup-global-slots.md:22,218 states for the sibling slots.
//
//  5. The whole slot block is UNINITIALISED, read off the PE section table of
//     the pinned file. .data has VirtualAddress 0x0110c000, VirtualSize
//     0x00212764 and SizeOfRawData 0x000c4c00, so raw data covers section
//     offsets 0..0xc4bff only. 0x0167eb08 is at section offset 0x572b08, PAST
//     SizeOfRawData: it lives in .data's zero-filled tail and therefore has no
//     initialiser in the file. The same holds for the entire accessor block's
//     slot range 0x0167eac0..0x0167eb68 (section offsets 0x572ac0..0x572b68),
//     so "no static writer" is a real property of the slot block and not an
//     artefact of a reader that missed something.
//
//  6. Structural, from the committed function table plus the pinned file: the
//     accessor block 0x00b3d220..0x00b3d520 holds 46 functions of which 43 are
//     the six-byte `a1 <disp32> c3` form, and their 43 disp32 values are 43
//     DISTINCT words covering 0x0167eac0..0x0167eb68 with no gap and no
//     duplicate - a bijection from accessor to slot. The span is 168 bytes for
//     43 words, so the table is CONTIGUOUS, and 0x0167eb08 is word 18 of it at
//     table offset 0x48. The immediately preceding function confirms the base
//     independently:
//        0x00b3d220  b8 c0 ea 67 01  MOV EAX,0x0167eac0 ; RET
//     i.e. 0x00b3d220 returns the TABLE ADDRESS as an immediate while
//     0x00b3d230 dereferences it - so the load/LEA distinction is not
//     hypothetical in this block.
//
//  7. Slot neighbourhood, from the committed function table's imported names
//     (only this target's own slot matters):
//        0x0167eb00 -> 0x00b3d370  UNNAMED in the SDK import
//        0x0167eb04 -> 0x00b3d380  UNNAMED
//        0x0167eb08 -> 0x00b3d390  UNNAMED   <- this target
//        0x0167eb0c -> 0x00b3d3a0  Simulator::cStarManager::Get
//        0x0167eb60 -> 0x00b3d400  Simulator::cGameNounManager::Get
//     ADJACENCY IS NOT IDENTITY. This package names no class for 0x0167eb08.
//     The two canonical manager slots recovered in Phase 0 live in this same
//     table (docs/analysis/simulator-root-closure.md:80,113-114) and are
//     semantically unrelated neighbours, not a hint that this slot is a
//     cStarManager; 0x00b3d390 is not, and is not claimed to be, the canonical
//     getter for anything. It is an UNNAMED 0x0167eb08 accessor.
//
//  8. How the returned word is consumed, from the committed edge sidecar
//     knowledgegraph/triage/xrefs-2540f2ca.tsv (101 callsites, 63 distinct
//     caller functions) plus two disassembly windows of the pinned file:
//        0x00bf6f6d  call 0x00b3d390
//        0x00bf6f72  mov ecx,eax          <- straight into a register receiver
//        0x00bf6f74  call 0x0104e340
//        0x00b5fee6  call 0x00b3d390
//        0x00b5feeb  push eax            <- straight into a stack argument
//     So the returned word is used as an OBJECT POINTER, both as a this-receiver
//     and as an argument. It is never compared, masked or arithmetic'd as a
//     scalar at either sampled site. That is all the pointee evidence there is.
//
// WHAT IS NOT CLAIMED
//  * The class of the object in 0x0167eb08, and the class of the one at
//    0x0167eb04 or any other slot in the table. UNKNOWN - see (7).
//  * ANY field offset on the pointee. Unlike sibling 0x00b3d380, no sampled
//    caller of 0x00b3d390 dereferences the result at a named offset: at
//    0x00bf6f72 the pointer is handed straight to 0x0104e340, whose own
//    decompilation is guarded by an unsatisfiable stack comparison and shows no
//    dereference of its parameter at a fixed offset. The pointee type below
//    therefore declares a single opaque byte and NO extent. The single byte is
//    not a recovered size and must not be read as one; it exists only so the
//    returned pointer has a type and the test has a target to plant.
//  * Any writer, teardown, publication order, nullability, thread-safety or
//    AddRef/Release ownership for the slot.
//  * That the slot is ever non-zero. See (5): it is uninitialised, so its value
//    is whatever publication put there.
//  * A calling convention. See (3).

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00b3d390 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b3d390_simulator_slot_getter {

// The unit the body actually moves: one 32-bit word in, one 32-bit word out.
using SlotWord = std::uint32_t;

static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(void *) == 4, "x86-32 target pointers are 32-bit");

// The global whose word this accessor returns. 0x0167eb08 is a genuine
// 4-byte-aligned .data address, and the committed data-reference sidecar
// records exactly one reference to it in the whole image (this load).
//
// It is declared as a REFERENCE to the slot word so that whichever unit links
// the reconstruction supplies the storage. In the real image that storage is
// the fixed, uninitialised .data word at 0x0167eb08 (evidence note 5); the
// model test binds it into a window it can plant neighbours and guard bands
// into, which is why kSlotVa below is a statement about the IMAGE's address and
// not about this process's runtime address of the same name. A reference is the
// honest shape for a slot at a fixed VA: it cannot be re-seated, which is
// exactly what the body assumes.
extern "C" {
extern SlotWord& DAT_0167eb08;
}

// 0x0167eb08 itself.
constexpr std::uint32_t kSlotVa = 0x0167eb08u;

// 0x00b3d220 returns this as an immediate (`MOV EAX,0x0167eac0`); 0x00b3d230
// dereferences it. It is the base of the singleton slot table that the 43
// accessors of note (6) enumerate one word at a time.
constexpr std::uint32_t kSlotTableBaseVa = 0x0167eac0u;

// This slot's offset inside that table. 0x0167eb08 - 0x0167eac0 = 0x48.
// NOTE: this 0x48 is a TABLE offset. It is an unrelated coincidence of
// arithmetic that the sibling slot 0x0167eb04 has a byte at OBJECT offset
// +0x48; the two numbers must not be conflated, and neither is claimed to
// describe the other.
constexpr std::uint32_t kSlotTableOffset = 0x48u;

// The slot block's extent as declared by the 43 accessors: 43 distinct words
// covering 0x0167eac0..0x0167eb68 with no gap and no duplicate.
// 0x0167eb68 - 0x0167eac0 = 0xa8 = 168 bytes = 42 word steps, i.e. 43 words,
// so the table is CONTIGUOUS and one accessor per word. Nothing in this package
// depends on the other 42 words, but the contiguity is what makes
// kSlotBlockAccessorCount checkable at all.
constexpr std::uint32_t kSlotBlockLastVa = 0x0167eb68u;
constexpr std::uint32_t kSlotBlockSpanBytes = 168u;
constexpr std::size_t kSlotBlockAccessorCount = 43u;

// This slot's word index inside that block: 0x0167eb08 - 0x0167eac0 = 0x48
// bytes = 18 words. The 18th accessor of the block is therefore this one.
constexpr std::size_t kSlotBlockWordIndex = 18u;

// .data geometry from the pinned PE section table, used by the test to check
// that this slot really is in the uninitialised tail (evidence note 5).
constexpr std::uint32_t kDataSectionVa = 0x0110c000u;
constexpr std::uint32_t kDataSizeOfRawData = 0x000c4c00u;

// 0x00b3d390..0x00b3d396 is six bytes; the 0xcc after it is INT3 pad and is
// deliberately not part of kTargetEncoding.
constexpr std::size_t kTargetBodyBytes = 6;

// The body's bytes as read from 0x00b3d390. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0xa1,                    // MOV EAX, moffs32
    0x08, 0xeb, 0x67, 0x01,  // disp32 = 0x0167eb08, little endian
    0xc3,                    // RET
};

// The pointee of 0x0167eb08. UNKNOWN by evidence: no class, no SDK symbol, no
// field name, and - unlike sibling 0x00b3d380 - no observed field offset
// either (header note 8). The single byte below is deliberately NOT a size
// claim. It exists so the returned pointer is a pointer type and so the model
// test can plant a target whose address the entry must hand back.
struct alignas(4) OpaqueSimulatorSingleton {
  std::uint8_t opaque_byte;
};

// x86-32 entry with 0 ordinary stack arguments, no register receiver, a bare
// RET (the callee pops nothing, the caller owns cleanup) and a 32-bit value
// return in EAX. The convention is deliberately left as the plain C default:
// for a zero-parameter entry the encoding is identical under cdecl, stdcall,
// thiscall and fastcall, and the derived ABI record abstains from choosing.
using AbiSlotGetter00b3d390 = OpaqueSimulatorSingleton* (*)();

static_assert(kSlotVa == kSlotTableBaseVa + kSlotTableOffset,
              "the slot address is the table base plus the table offset");
static_assert(kSlotTableOffset == 72u,
              "0x48 is the value 72, compared semantically not by spelling");
static_assert(kSlotVa == 0x0167eb08u,
              "the slot is 0x0167eb08, compared semantically not by spelling");
static_assert(kSlotVa != 0x0167eb04u && kSlotVa != 0x0167eb0cu,
              "this slot is neither of its two immediate table neighbours");
static_assert(kSlotTableBaseVa <= kSlotVa && kSlotVa <= kSlotBlockLastVa,
              "the slot lies inside the accessor block's slot range");
static_assert(kSlotBlockLastVa - kSlotTableBaseVa == kSlotBlockSpanBytes,
              "the block span is the table's last word minus its base");
static_assert(kSlotBlockAccessorCount * 4u == kSlotBlockSpanBytes + 4u,
              "43 contiguous 4-byte words span 168 bytes plus the last step");
static_assert(kSlotTableOffset / 4u == kSlotBlockWordIndex,
              "the table offset is 18 words in");
static_assert(kSlotVa - kDataSectionVa > kDataSizeOfRawData,
              "0x0167eb08 is past .data's SizeOfRawData, so it is uninitialised");
static_assert(kTargetEncoding[0] == 0xa1u && kTargetEncoding[5] == 0xc3u,
              "0x00b3d390 is MOV EAX,moffs32 and 0x00b3d395 is RET");
static_assert(kTargetEncoding[1] == 0x08u && kTargetEncoding[2] == 0xebu &&
                  kTargetEncoding[3] == 0x67u && kTargetEncoding[4] == 0x01u,
              "the disp32 bytes spell 0x0167eb08, little endian");
static_assert(kSlotVa == (static_cast<std::uint32_t>(kTargetEncoding[1]) |
                          (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
                          (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
                          (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)),
              "the header's slot VA equals the instruction's disp32");
static_assert(kTargetBodyBytes == 6u,
              "the body is 6 bytes, matching the committed function table");
static_assert(std::is_same<AbiSlotGetter00b3d390,
                           OpaqueSimulatorSingleton* (*)()>::value,
              "the modelled entry takes nothing and returns one pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00b3d390.
OpaqueSimulatorSingleton* simulator_slot_getter_00b3d390();

}
