#pragma once

// Reconstruction of 0x00b3d260 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e,
// image base 0x00400000).
//
// THE COMPLETE BODY: six bytes, two instructions
// --------------------------------------------------
//     0x00b3d260  a1 d8 ea 67 01   MOV EAX, DS:0x0167ead8
//     0x00b3d265  c3               RET          (bare: the callee pops nothing)
//
// Verified two independent ways, and the two agree byte for byte:
//
//   * `objdump -d -M intel SPORE/SporeBin/SporeApp.exe
//     --start-address=0x00b3d230 --stop-address=0x00b3d272` prints, at
//     0x00b3d260, `a1 d8 ea 67 01  mov eax,ds:0x167ead8` and at 0x00b3d265
//     `c3  ret`, with 0x00b3d266..0x00b3d26f being CC padding (int3), so the
//     function body cannot run past the RET;
//   * the machine listing stored with this target
//     (reconstruction/evidence/00b3d260/evidence.json:
//     categories.disassembly.value.instructions) lists exactly two instructions,
//     "MOV EAX,[0x0167ead8]" at 0x00b3d260 and "RET" at 0x00b3d265, and
//     categories.ghidra_function.value reports body_start 00b3d260, body_end
//     00b3d265, body_span_bytes 6, size_bytes 6, callees [] and 58 xrefs from
//     37 distinct caller functions.
//
// `a1` is the x86-32 accumulator-load form: opcode A1 followed by a four-byte
// little-endian absolute address. The operand bytes are d8 ea 67 01, i.e.
// 0x0167ead8, and kGlobalVa below is DECODED from those four bytes rather than
// restated, so the constant cannot drift away from the machine image.
//
// There is nothing else in the body: no branch, no call, no indirect transfer,
// no flag test, no register save, no stack access, and exactly one memory
// operand. So there is nothing to transcribe but that single 32-bit load, and
// the whole of the modelled behaviour is "return one dword, change nothing".
//
// CALLING CONVENTION: NOT PROVEN, AND THEREFORE NOT INVENTED
// ---------------------------------------------------------
// The macro below is deliberately empty on both arms. What the bytes prove is:
//
//   * no register receiver -- the body reads no register at all, so ECX (the
//     only register __thiscall could deliver a receiver in) is never consumed
//     (evidence record inference R2, "present": false);
//   * no stack argument -- the body contains no memory operand naming ESP or
//     any stack displacement, so nothing is popped;
//   * zero bytes of callee cleanup -- the terminal is a bare RET (c3) with no
//     immediate.
//
// Two independent caller listings corroborate "no stack argument" from the
// other side of the call. At 0x00b32ac4 and at 0x00c8e600 the sequence is a
// bare `call 0x00b3d260` with nothing pushed immediately before it and no ESP
// adjustment immediately after it:
//
//     b32ac4:  call   0xb3d260
//     b32ac9:  mov    edx,DWORD PTR [eax]
//     b32acb:  mov    ecx,eax
//     b32acd:  mov    eax,DWORD PTR [edx+0x30]
//     b32ad0:  call   eax
//
//     c8e600:  call   0xb3d260
//     c8e605:  mov    edx,DWORD PTR [eax]
//     c8e607:  mov    ecx,eax
//     c8e609:  mov    eax,DWORD PTR [edx+0x38]
//     c8e60c:  push   ebp
//     c8e60d:  call   eax
//
// So zero parameters and caller-side cleanup are facts. What is NOT a fact is
// WHICH convention: with zero parameters and zero receiver, a bare-RET body is
// byte-identical under __cdecl, __stdcall, __thiscall and __fastcall, and the
// tool's own ABI record for this target says so and abstains
// (abi_derived.abstained_because: "no_discriminator: no stack-argument read and
// no positive receiver evidence"; conventions.calling_convention null,
// confidence UNKNOWN). Naming any one of the four in the declaration would be a
// claim the listing does not carry, so the macro is present, named, and carries
// no convention token. The modelled entry is a zero-parameter function, which is
// the whole of what the machine fixes.
//
// RETURN: four bytes, and only four bytes are claimed
// ----------------------------------------------------
// MOV EAX, DS:0x0167ead8 writes the whole of EAX at 0x00b3d260, so the width is
// 4. The declared return type is therefore the width-computable builtin
// std::uint32_t, and no pointer type is asserted: the body proves a four-byte
// LOAD and nothing about what the word denotes.
//
// That last point is worth stating plainly because it is the one place a
// reconstruction of this family is most tempted to overreach. Callers clearly
// USE the word as an object base pointer -- the three listings above all do
// `mov edx,[eax]` (a function-table load through the returned word), then
// `mov ecx,eax` (the word itself as the receiver), then dispatch through
// [edx+0x30] at 0x00b32ac4, [edx+0x38] at 0x00c8e600, 0x00c9a75e and 0x00d58c41,
// and [edx+0x24] at 0x00abf793 (the already-promoted
// App::cCheatManager::func48h / opaque_service_forward_00abf790, which the
// project's own metadata records for 0x0167ead8 as "the cheat service global").
// A fourth site, 0x00fefc71, stores the answer verbatim (`mov edi,eax`) instead
// of dispatching through it. So the consumer-side reading is OBSERVED: the word
// is dereferenced as a base pointer whose first dword is a function table, and
// several distinct slots of that table are reached. What is NOT observed, and
// is NOT claimed here, is WHICH object it points at. No class, no vtable
// identity, no field name, no slot owner, no object size and no SDK name are
// asserted, and the declared return type stays the 32-bit word the machine
// actually writes.
//
// THE GLOBAL, AND WHY IT HAS NO INITIALISER
// -----------------------------------------
// 0x0167ead8 is in .data. The PE section table of SporeApp.exe gives .data
// VirtualAddress 0x110c000, VirtualSize 0x212764, SizeOfRawData 0xc4c00,
// PointerToRawData 0x110aa00; with image base 0x00400000 the section is loaded
// at 0x0150c000. The dword's offset inside the section is 0x172ad8, which is
// PAST SizeOfRawData 0xc4c00, so no image bytes back this address and the
// loader zero-fills it. That is a statement about the file, not about the
// running game: nothing in this six-byte body says who stores the word, when,
// or what it holds, and no runtime value is claimed for it here. The model's
// initial value is a placeholder, chosen to be observable, and every test in the
// model test SETS the word before reading it back.
//
// WHO FILLS IT IS UNKNOWN, AND THE PROJECT ALREADY SAYS SO
// --------------------------------------------------------
// 0x0167ead8 is a distinct slot, not a second name for one of the slots the
// Phase-0 Simulator root closure already characterises. The dense slot table
// this address sits in was read from the same objdump window: within
// 0x00b3d200..0x00b3d500 there is exactly one accumulator load per dword for
// 0x0167eac0, 0x0167eac4, 0x0167eac8, 0x0167eacc, 0x0167ead0, 0x0167ead4,
// 0x0167ead8, 0x0167eadc, 0x0167eae0, 0x0167eae4, 0x0167eae8, 0x0167eaec,
// 0x0167eaf0, 0x0167eaf4, 0x0167eaf8 and 0x0167eafc -- seventeen slots, one
// accessor each, no duplication among them. So 0x00b3d260 is the ONLY accessor
// of 0x0167ead8 in that window, and 0x0167ead8 is not reached by the same load
// as any of the documented roots:
//
//   * 0x0167eae0 is the alternate cGameNounManager* read by 0x00b3d300, and
//     0x0167eae4 the alternate cStarManager* read by 0x00b3d2a0
//     (docs/analysis/simulator-root-closure.md:135-136);
//   * 0x0167eaec belongs to the deliberately-unidentified forwarder 0x00b5b800
//     (same document, line 137);
//   * 0x0167eaf8 belongs to cGameInputManager::Get at 0x00b3d350 (line 119).
//
// None of those is this address, and docs/analysis/simulator-root-closure.md
// does not list 0x00b3d260 among its eleven roots at all. The project's own
// promoted metadata for the consumer 0x00abf790 records, for this exact global,
// the open questions "Producer, lifetime, and reset of the service global at
// 0x0167ead8" and "The service global at 0x0167ead8 and its lifetime are
// unresolved" (reconstruction/metadata/pkg-cheat-wave9/00abf790.json:219,236).
// This package therefore claims nothing about the producer, the lifetime, the
// ownership or the pointee type of 0x0167ead8: a second accessor for
// 0x0167eae0 or 0x0167eae4 would have been a duplicate of a closed root, and
// this is not one.
//
// CORROBORATION THAT IS NOT USED AS PROOF
// ----------------------------------------
// The neighbouring slots are each read by their own accessor, in this same
// window: 0x00b3d250 reads 0x0167ead0, 0x00b3d270 reads 0x0167eac8, 0x00b3d280
// reads 0x0167eacc, 0x00b3d290 reads 0x0167ead4 and 0x00b3d2a0 reads 0x0167eae4.
// The one other encoding in the window is the immediate form at 0x00b3d220,
// `b8 c0 ea 67 01 / c3` -- MOV EAX,0x0167eac0 / RET, the address 0x0167eac0 as
// an immediate rather than through memory. That is a fact about 0x00b3d220 and
// about a DIFFERENT slot from this one, recorded here only because it is why
// the address is worth naming at all; it is deliberately NOT used, because this
// package reconstructs 0x00b3d260 only and a neighbour's operand is not
// evidence about this body's return type. Equally, 37 distinct callers and 58
// callsites is a fan-in count, not a semantic classification: this body is
// transcribed from its own two instructions, and nothing here is inferred from
// who calls it.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "root slot 0x00b3d260 is an x86-32 reconstruction (absolute 32-bit operand at 0x00b3d260)"
#endif

// Calling convention: see the block comment above. The listing discriminates
// none, the macro states that by carrying no token, and the entry below is
// modelled with the shape the bytes do fix -- zero parameters, no receiver.
#if defined(_MSC_VER)
#define PKG_00B3D260_CALL
#else
#define PKG_00B3D260_CALL
#endif

namespace openspore::reconstruction::pkg_00b3d260_root_slot {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above.
// ---------------------------------------------------------------------------

// 0x00b3d260..0x00b3d265: a1 d8 ea 67 01 / c3 (objdump range 0x00b3d230..0x00b3d272).
constexpr std::uint8_t kTargetBytes[6] = {
    0xa1,  // 0x00b3d260 MOV EAX, moffs32   (opcode A1)
    0xd8,  //   operand byte 0  -> 0xd8
    0xea,  //   operand byte 1  -> 0xea
    0x67,  //   operand byte 2  -> 0x67
    0x01,  //   operand byte 3  -> 0x01
    0xc3,  // 0x00b3d265 RET               (bare, no immediate: 0 bytes popped)
};

static_assert(kTargetBytes[0] == 0xa1,
              "0x00b3d260 is the x86-32 accumulator load A1: EAX := DWORD PTR "
              "[absolute 32-bit address]");
static_assert(kTargetBytes[5] == 0xc3,
              "0x00b3d265 is a bare RET (c3): the callee pops nothing, so stack "
              "cleanup is zero bytes on the callee side");

// The absolute address the A1 operand names, decoded from the four operand
// bytes in little-endian order rather than restated.
constexpr Word kGlobalVa = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                            (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                            (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                            (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
static_assert(kGlobalVa == 0x0167ead8u,
              "operand bytes d8 ea 67 01 of the A1 at 0x00b3d260 are the "
              "little-endian address 0x0167ead8");

// Entry and terminal addresses, and the size of the body between them.
constexpr Word kEntryVa = 0x00b3d260u;
constexpr Word kTerminalVa = 0x00b3d265u;
constexpr std::size_t kBodyBytes = 6;
static_assert(kEntryVa + kBodyBytes == 0x00b3d266u,
              "0x00b3d260 + 6 bytes ends at 0x00b3d266, one past the last "
              "instruction byte at 0x00b3d265");
static_assert(kTerminalVa - kEntryVa == 5,
              "the bare RET is the second instruction, five bytes after entry");

// Instruction count, straight from the stored listing: two instructions, at
// 0x00b3d260 and 0x00b3d265.
constexpr std::size_t kInstructionCount = 2;
static_assert(kInstructionCount == 2,
              "the listing has exactly two instructions (MOV EAX,[...]; RET)");

// Stores: zero. The single memory operand is the source of the A1 load, so the
// body performs one READ and no memory write at all.
constexpr std::size_t kMemoryStores = 0;
static_assert(kMemoryStores == 0,
              "MOV EAX,[abs] is a load, so the body stores nothing: the only "
              "write in the whole function is to EAX");

// Return width: MOV EAX writes all four bytes of EAX, so the returned word is
// 4 bytes wide. No narrower and no wider.
constexpr std::size_t kReturnWidthBytes = 4;
static_assert(kReturnWidthBytes == sizeof(Word),
              "the machine writes the whole of EAX, so the returned word is "
              "exactly one 32-bit word");

// Stack arguments: none. The body names no stack memory operand, and two caller
// listings (0x00b32ac4 and 0x00c8e600) push nothing and adjust nothing around
// the call.
constexpr std::size_t kStackArgumentWords = 0;
static_assert(kStackArgumentWords == 0,
              "no stack operand in the body and no stack traffic at either "
              "corroborating call site: zero stack arguments");

// Callee-side stack cleanup: zero bytes, because the RET carries no immediate.
constexpr std::size_t kCalleeCleanupBytes = 0;
static_assert(kCalleeCleanupBytes == 0,
              "RET at 0x00b3d265 has no immediate operand, so the callee pops 0");

// Receiver: none. The body reads no register, so no register can be a receiver.
constexpr bool kHasReceiver = false;
static_assert(!kHasReceiver,
              "the body contains no register read, so no register carries a "
              "receiver (evidence inference R2: present=false)");

// .data section facts that make "no image initializer for this dword" a
// statement about the file rather than a guess (PE section table of
// SporeApp.exe, read from the optional header's section table).
constexpr Word kDataSectionVa = 0x0150c000u;
constexpr Word kDataSectionVirtualSize = 0x00212764u;
constexpr Word kDataSectionRawSize = 0x000c4c00u;
constexpr Word kGlobalOffsetInSection = kGlobalVa - kDataSectionVa;
static_assert(kGlobalOffsetInSection == 0x00172ad8u,
              "0x0167ead8 sits 0x172ad8 bytes into .data (VA 0x0150c000)");
static_assert(kDataSectionVirtualSize > kDataSectionRawSize,
              ".data VirtualSize 0x212764 exceeds SizeOfRawData 0xc4c00, so the "
              "section has a loader-zeroed tail");
static_assert(kGlobalOffsetInSection > kDataSectionRawSize,
              "0x0167ead8 is past .data SizeOfRawData 0xc4c00, so no file bytes "
              "back it and no image initializer is claimed for it");

// The distinctness of this slot from the two slots the Phase-0 Simulator root
// closure already closed. These are stated as ordinary address facts, not as
// claims about what the neighbours mean: the closure's own documentation
// (docs/analysis/simulator-root-closure.md:135-137) carries the semantics of
// 0x0167eae0, 0x0167eae4 and 0x0167eaec, and this package deliberately carries
// none of it. What is claimed is only that 0x0167ead8 is none of those three.
constexpr Word kAlternateNounSlotVa = 0x0167eae0u;  // read by 0x00b3d300
constexpr Word kAlternateStarSlotVa = 0x0167eae4u;  // read by 0x00b3d2a0
constexpr Word kOpaqueForwardSlotVa = 0x0167eaecu;   // read by 0x00b5b800
constexpr Word kInputManagerSlotVa = 0x0167eaf8u;   // read by 0x00b3d350
static_assert(kGlobalVa != kAlternateNounSlotVa && kGlobalVa != kAlternateStarSlotVa &&
                  kGlobalVa != kOpaqueForwardSlotVa && kGlobalVa != kInputManagerSlotVa,
              "0x0167ead8 is a slot of its own: it is not the alternate noun "
              "slot, the alternate star slot, the unidentified forward slot or "
              "the input-manager slot, so it is not a duplicate of any root the "
              "Simulator root closure already characterises");

// ---------------------------------------------------------------------------
// The modelled global and the modelled entry.
// ---------------------------------------------------------------------------

// Guard words modelled on either side of the single dword the machine names, so
// a model test can prove the body touches nothing else. This is padding chosen
// by the test, NOT memory the machine has: 0x0167ead4 and 0x0167eadc are
// different dwords (read by their own accessors 0x00b3d290 and the next one in
// the family) and nothing here claims what either of them is.
constexpr std::size_t kGuardWords = 4;
constexpr std::uint32_t kGuardCanary = 0xa5a5a5a5u;

struct RootSlotImage {
  std::uint32_t guard_lo[kGuardWords];  // modelled padding, before the slot
  std::uint32_t slot;                   // the one dword 0x00b3d260 reads
  std::uint32_t guard_hi[kGuardWords];  // modelled padding, after the slot
};

static_assert(offsetof(RootSlotImage, slot) == kGuardWords * sizeof(std::uint32_t),
              "the modelled slot sits immediately after the low guard words");
static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
              "the modelled image is 2*kGuardWords+1 words");

// The modelled image, one instance, defined in the .cpp.
extern RootSlotImage g_root_slot_image;

// The repository's global-naming convention (g_<va8>) naming the same single
// dword the A1 operand names: 0x0167ead8.
extern Word& g_0167ead8;

// The machine ABI as a C++ type, so a wrong prototype fails to build:
// zero parameters, 4-byte return.
using AbiRootSlotAccessor00b3d260 = std::uint32_t(PKG_00B3D260_CALL*)();
static_assert(sizeof(AbiRootSlotAccessor00b3d260) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. Zero parameters: the body reads no stack
// word and no register (0x00b3d260, 0x00b3d265).
std::uint32_t PKG_00B3D260_CALL root_slot_accessor_00b3d260();

}  // namespace openspore::reconstruction::pkg_00b3d260_root_slot
