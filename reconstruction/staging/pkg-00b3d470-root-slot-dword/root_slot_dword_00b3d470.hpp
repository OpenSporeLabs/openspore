#pragma once

// Reconstruction of 0x00b3d470 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// THE COMPLETE BODY: six bytes, two instructions
// -------------------------------------------------
//     0x00b3d470  a1 18 eb 67 01   MOV EAX, DS:0x0167eb18
//     0x00b3d475  c3               RET          (bare: the callee pops nothing)
//
// then ten int3 (0xcc) pad bytes through 0x00b3d47f, after which
// 0x00b3d480 begins an unrelated accessor.
//
// Three independent reads agree on those bytes:
//
//   1. the file itself, at the .text file offset for the VA. .text has
//      VirtualAddress 0x00001000 and PointerToRawData 0x00000400 at an image
//      base of 0x00400000, so 0x00b3d470 is file offset 0x0073c870, and the
//      ten bytes read there are `a1 18 eb 67 01 c3 cc cc cc cc`;
//   2. GhidraMCP /read_memory @ http://127.0.0.1:8089, program SporeApp.exe,
//      address 0x00b3d470, length 16 -> the same bytes;
//   3. the machine listing stored with this target
//      (reconstruction/evidence/00b3d470/evidence.json:
//      categories.disassembly.value.instructions lists exactly two
//      instructions, at 0x00b3d470 "MOV EAX,[0x0167eb18]" and at 0x00b3d475
//      "RET"; categories.ghidra_function.value reports body_start 00b3d470,
//      body_end 00b3d475, body_span_bytes 6, size_bytes 6, callees []).
//
// `a1` is the x86-32 accumulator-load form: opcode A1 followed by a four-byte
// little-endian absolute address. The operand bytes are 18 eb 67 01, i.e.
// 0x0167eb18, and kGlobalVa below is DECODED from those four bytes rather than
// restated, so the constant cannot drift away from the machine image.
//
// CALLING CONVENTION: NOT PROVEN, AND THEREFORE NOT INVENTED
// ---------------------------------------------------------
// The macro below is deliberately empty on both arms. What the bytes prove is:
//
//   * no register receiver -- the body reads no register at all, so ECX (the
//     only register __thiscall could deliver a receiver in) is never consumed
//     (evidence record observation obs-0001 is a mem_load, not a register read;
//     inference R2, "present": false);
//   * no stack argument -- the body contains no memory operand naming ESP or
//     any stack displacement, so nothing is popped;
//   * zero bytes of callee cleanup -- the terminal is a bare RET (c3) with no
//     immediate.
//
// Two caller listings corroborate "no stack argument" from the far side of the
// call. 0x00b33784 is `call 0x00b3d470` and is immediately followed at
// 0x00b33789 by `mov ecx,eax` -- nothing in between, and no ESP adjustment
// afterwards. 0x00d3a830 is `call 0x00b3d470` and is immediately followed at
// 0x00d3a835 by `add eax,0x60`. Both push nothing before the call and adjust
// nothing after it, so zero parameters and caller-side cleanup are facts. The
// evidence pack records 24 direct-call edges from 10 distinct caller functions
// into this entry.
//
// What is NOT a fact is WHICH convention. With zero parameters and zero
// receiver, a bare-RET body is byte-identical under __cdecl, __stdcall,
// __thiscall and __fastcall; the tool's own ABI record for this target says so
// and abstains (abi_derived.abstained_because: "no_discriminator: no
// stack-argument read and no positive receiver evidence"; conventions.
// calling_convention null, confidence UNKNOWN; candidates __cdecl, __stdcall,
// __thiscall, __fastcall). Naming any one of the four in the declaration would
// be a claim the listing does not carry, so the macro is present, named, and
// carries no convention token. The modelled entry is a zero-parameter function,
// which is the whole of what the machine fixes.
//
// RETURN: four bytes, and only four bytes are claimed
// ----------------------------------------------------
// MOV EAX, DS:0x0167eb18 writes the whole of EAX at 0x00b3d470, so the width is
// 4. The derived record classifies the value as pointer_like (RT2, INFERRED), and
// the caller at 0x00d3a830 immediately dereferences the result at +0x60
// (`add eax,0x60` / `cmp dword ptr [eax],0` / `jz`), which is consistent with
// that classification -- but the body itself proves a four-byte LOAD and nothing
// about what the word denotes, so the declared return is std::uint32_t and no
// pointer type is asserted.
//
// THE GLOBAL, AND WHY IT HAS NO INITIALISER
// ------------------------------------------
// 0x0167eb18 is in .data. The PE section table of SporeApp.exe (parsed
// directly, and cross-checked against `objdump -h`) gives .data section
// VirtualAddress 0x0110c000, VirtualSize 0x00212764, PointerToRawData
// 0x0110aa00 and SizeOfRawData 0x000c4c00; at the 0x00400000 image base that
// section is mapped at VA 0x0150c000. The dword's offset inside the section is
// 0x00172b18, which is PAST SizeOfRawData 0x000c4c00, so no image bytes back
// this address and the loader zero-fills it. That is a statement about the
// file, not about the running game: nothing in this six-byte body says who
// stores the word or what it holds, and no value is claimed for it here. The
// model's initial value is a placeholder, chosen to be observable, and every
// test below SETS the word before reading it back.
//
// NEIGHBOUR ACCESSORS THAT ARE NOT USED AS PROOF
// -----------------------------------------------
// 0x00b3d480 is `a1 3c eb 67 01 / c3`, i.e. MOV EAX,DS:0x0167eb3c / RET, a
// different dword 0x24 bytes above the one this body names, and 0x00b3d220
// (outside this body) is `b8 c0 ea 67 01 / c3`, MOV EAX,0x0167eac0 / RET. Those
// are facts about their own addresses, recorded only because they are why
// 0x0167eb18 is worth pinning, and deliberately NOT used: this package
// reconstructs 0x00b3d470 only, and a neighbour's operand is not evidence about
// this body's return type. Likewise the semantic family this address belongs to
// is not claimed here -- see unresolved_questions in the worker result.
//
// NO RUNTIME EVIDENCE
// -------------------
// Nothing in this package is OBSERVED or VERIFIED. There is no Wine run, no
// differential trace and no runtime-gate result for 0x00b3d470 in this repo
// (docs/analysis/simulator-root-closure.md:3). Every claim above is static,
// pinned to the bytes of this binary.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "root slot dword 0x00b3d470 is an x86-32 reconstruction (absolute 32-bit operand at 0x00b3d470)"
#endif

// Calling convention: see the block comment above. The listing discriminates
// none, the macro states that by carrying no token, and the entry below is
// modelled with the shape the bytes do fix -- zero parameters, no receiver.
#if defined(_MSC_VER)
#define PKG_00B3D470_CALL
#else
#define PKG_00B3D470_CALL
#endif

namespace openspore::reconstruction::pkg_00b3d470 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above.
// ---------------------------------------------------------------------------

// 0x00b3d470..0x00b3d475: a1 18 eb 67 01 / c3 (file offset 0x0073c870).
constexpr std::uint8_t kTargetBytes[7] = {
    0xa1,  // 0x00b3d470 MOV EAX, moffs32   (opcode A1)
    0x18,  //   operand byte 0  -> 0x18
    0xeb,  //   operand byte 1  -> 0xeb
    0x67,  //   operand byte 2  -> 0x67
    0x01,  //   operand byte 3  -> 0x01
    0xc3,  // 0x00b3d475 RET               (bare, no immediate: 0 bytes popped)
    0xcc,  // 0x00b3d476 int3 pad, first of ten through 0x00b3d47f
};

static_assert(kTargetBytes[0] == 0xa1,
              "0x00b3d470 is the x86-32 accumulator load A1: EAX := DWORD PTR "
              "[absolute 32-bit address]");
static_assert(kTargetBytes[5] == 0xc3,
              "0x00b3d475 is a bare RET (c3): the callee pops nothing, so stack "
              "cleanup is zero bytes on the callee side");
static_assert(kTargetBytes[6] == 0xcc,
              "0x00b3d476 is the first of ten int3 pad bytes after the body");

// The absolute address the A1 operand names, decoded from the four operand
// bytes in little-endian order rather than restated.
constexpr Word kGlobalVa = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                            (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                            (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                            (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
static_assert(kGlobalVa == 0x0167eb18u,
              "operand bytes 18 eb 67 01 of the A1 at 0x00b3d470 are the "
              "little-endian address 0x0167eb18");

// Where the body sits in the file, so a reader can find the bytes without the
// disassembler. .text: VirtualAddress 0x1000, PointerToRawData 0x400, image
// base 0x00400000.
constexpr Word kImageBase = 0x00400000u;
constexpr Word kTextSectionVa = 0x00001000u;
constexpr Word kTextFileOffset = 0x00000400u;
constexpr Word kFileOffsetOfBody = kTextFileOffset + (0x00b3d470u - kImageBase - kTextSectionVa);
static_assert(kFileOffsetOfBody == 0x0073c870u,
              "0x00b3d470 is file offset 0x0073c870 in .text, where the ten "
              "bytes are a1 18 eb 67 01 c3 cc cc cc cc");

// Entry and terminal addresses, and the size of the body between them.
constexpr Word kEntryVa = 0x00b3d470u;
constexpr Word kTerminalVa = 0x00b3d475u;
constexpr std::size_t kBodyBytes = 6;
static_assert(kEntryVa + kBodyBytes == 0x00b3d476u,
              "0x00b3d470 + 6 bytes ends at 0x00b3d476, one past the last "
              "instruction byte at 0x00b3d475");
static_assert(kTerminalVa - kEntryVa == 5,
              "the bare RET is the second instruction, five bytes after entry");

// Padding width before the next accessor starts at 0x00b3d480.
constexpr std::size_t kInt3PadBytes = 10;
static_assert(0x00b3d480u - (kTerminalVa + 1) == kInt3PadBytes,
              "ten int3 bytes (0x00b3d476..0x00b3d47f) separate the RET at "
              "0x00b3d475 from the next accessor at 0x00b3d480");

// Instruction count, straight from the stored listing: two instructions, at
// 0x00b3d470 and 0x00b3d475.
constexpr std::size_t kInstructionCount = 2;
static_assert(kInstructionCount == 2,
              "the listing has exactly two instructions (MOV EAX,[...]; RET)");

// Return width: MOV EAX writes all four bytes of EAX, so the returned word is
// 4 bytes wide. No narrower and no wider.
constexpr std::size_t kReturnWidthBytes = 4;
static_assert(kReturnWidthBytes == sizeof(Word),
              "the machine writes the whole of EAX, so the returned word is "
              "exactly one 32-bit word");

// Stack arguments: none. The body names no stack memory operand, and two caller
// listings (0x00b33784 -> 0x00b33789 and 0x00d3a830 -> 0x00d3a835) push nothing
// and adjust nothing around the call.
constexpr std::size_t kStackArgumentWords = 0;
static_assert(kStackArgumentWords == 0,
              "no stack operand in the body and no stack traffic at either "
              "corroborating call site: zero stack arguments");

// Callee-side stack cleanup: zero bytes, because the RET carries no immediate.
constexpr std::size_t kCalleeCleanupBytes = 0;
static_assert(kCalleeCleanupBytes == 0,
              "RET at 0x00b3d475 has no immediate operand, so the callee pops 0");

// Receiver: none. The body reads no register, so no register can be a receiver.
constexpr bool kHasReceiver = false;
static_assert(!kHasReceiver,
              "the body contains no register read, so no register carries a "
              "receiver (evidence inference R2: present=false)");

// Direct-call fan-in recorded by the evidence pack: 24 edges from 10 distinct
// caller functions. Recorded as a count only; no caller is interpreted here.
constexpr std::size_t kDirectCallEdges = 24;
constexpr std::size_t kDistinctCallerFunctions = 10;
static_assert(kDirectCallEdges == 24 && kDistinctCallerFunctions == 10,
              "the evidence pack records 24 direct-call edges into 0x00b3d470 "
              "from 10 distinct caller functions");

// The one data reference to this global in the canonical data-reference export
// (knowledgegraph/triage/datarefs-2540f2ca.tsv, snapshot 2540f2ca, binary
// sha256 25d42a7a...d914e) is a single row:
//
//     00b3d470  0167eb18  read  .data -wr  00b3d470  ghidra:SporeApp.exe
//
// i.e. this body is the only recorded reader of 0x0167eb18 in that export, the
// access is a read, and the word lives in the read-write segment `.data`. This
// is a statement ABOUT THE EXPORT, not about the binary: the export is a
// snapshot and AGENTS.md records that the live Ghidra DB has drifted from it, so
// "one row here" is not "one reader in the game". Nothing downstream of this
// body -- no writer, no other reader -- is claimed either way.
constexpr std::size_t kDataRefRowsForGlobal = 1;
static_assert(kDataRefRowsForGlobal == 1,
              "the canonical datarefs export holds exactly one row for "
              "0x0167eb18, and it is a read from 0x00b3d470");

// The .data section facts that make "no image initializer for this dword" a
// statement about the file rather than a guess (PE section table of SporeApp.exe,
// parsed directly and cross-checked with `objdump -h`).
constexpr Word kDataSectionRelativeVa = 0x0110c000u;
constexpr Word kDataSectionVirtualSize = 0x00212764u;
constexpr Word kDataSectionRawSize = 0x000c4c00u;
constexpr Word kDataSectionVa = kImageBase + kDataSectionRelativeVa;
constexpr Word kGlobalOffsetInSection = kGlobalVa - kDataSectionVa;
static_assert(kDataSectionVa == 0x0150c000u,
              ".data is mapped at VA 0x0150c000 (section VA 0x0110c000 plus the "
              "0x00400000 image base)");
static_assert(kGlobalOffsetInSection == 0x00172b18u,
              "0x0167eb18 sits 0x172b18 bytes into .data (VA 0x0150c000)");
static_assert(kDataSectionVirtualSize > kDataSectionRawSize,
              ".data VirtualSize 0x212764 exceeds SizeOfRawData 0xc4c00, so the "
              "section has a loader-zeroed tail");
static_assert(kGlobalOffsetInSection > kDataSectionRawSize,
              "0x0167eb18 is past .data SizeOfRawData 0xc4c00, so no file bytes "
              "back it and no image initializer is claimed for it");

// ---------------------------------------------------------------------------
// The modelled global and the modelled entry.
// ---------------------------------------------------------------------------

// Guard words modelled on either side of the single dword the machine names, so
// a model test can prove the body touches nothing else. This is padding chosen
// by the test, NOT memory the machine has: 0x0167eb1c is a different dword and
// nothing here claims what it is.
constexpr std::size_t kGuardWords = 4;
constexpr std::uint32_t kGuardCanary = 0xa5a5a5a5u;

struct RootSlotImage {
  std::uint32_t guard_lo[kGuardWords];  // modelled padding, before the slot
  std::uint32_t slot;                   // the one dword 0x00b3d470 reads
  std::uint32_t guard_hi[kGuardWords];  // modelled padding, after the slot
};

static_assert(offsetof(RootSlotImage, slot) == kGuardWords * sizeof(std::uint32_t),
              "the modelled slot sits immediately after the low guard words");
static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
              "the modelled image is 2*kGuardWords+1 words");

// The modelled image, one instance, defined in the .cpp.
extern RootSlotImage g_root_slot_image;

// The repository's global-naming convention (g_<va8>) naming the same single
// dword the A1 operand names: 0x0167eb18.
extern Word& g_0167eb18;

// The machine ABI as a C++ type, so a wrong prototype fails to build:
// zero parameters, 4-byte return.
using AbiRootSlotDword00b3d470 = Word(PKG_00B3D470_CALL*)();
static_assert(sizeof(AbiRootSlotDword00b3d470) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. Zero parameters: the body reads no stack
// word and no register (0x00b3d470, 0x00b3d475).
Word PKG_00B3D470_CALL root_slot_dword_00b3d470();

}  // namespace openspore::reconstruction::pkg_00b3d470
