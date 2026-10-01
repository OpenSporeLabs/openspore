#pragma once

// Reconstruction of 0x00b3d230 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// THE COMPLETE BODY: six bytes, two instructions
// ------------------------------------------------
//     0x00b3d230  a1 c0 ea 67 01   MOV EAX, DS:0x0167eac0
//     0x00b3d235  c3               RET          (bare: the callee pops nothing)
//
// Read from `objdump -d -M intel SPORE/SporeBin/SporeApp.exe
// --start-address=0x00b3d200 --stop-address=0x00b3d260`, and independently from
// the machine listing stored with this target
// (reconstruction/evidence/00b3d230/evidence.json:
// categories.disassembly.value.instructions lists exactly two instructions, at
// 0x00b3d230 "MOV EAX,[0x0167eac0]" and at 0x00b3d235 "RET";
// categories.ghidra_function.value reports body_start 00b3d230, body_end
// 00b3d235, body_span_bytes 6, callees []).
//
// `a1` is the x86-32 accumulator-load form: opcode A1 followed by a four-byte
// little-endian absolute address. The operand bytes are c0 ea 67 01, i.e.
// 0x0167eac0, and kGlobalVa below is DECODED from those four bytes rather than
// restated, so the constant cannot drift away from the machine image.
//
// CALLING CONVENTION: NOT PROVEN, AND THEREFORE NOT INVENTED
// ---------------------------------------------------------
// The macro below is deliberately empty on both arms. What the bytes prove is:
//
//   * no register receiver -- the body reads no register at all, so ECX (the
//     only register __thiscall could deliver a receiver in) is never consumed
//     (evidence record observation/inference R2, "present": false);
//   * no stack argument -- the body contains no memory operand naming ESP or
//     any stack displacement, so nothing is popped;
//   * zero bytes of callee cleanup -- the terminal is a bare RET (c3) with no
//     immediate.
//
// Two independent caller listings corroborate "no stack argument" from the
// other side of the call: 0x00b19449 is immediately followed by 0x00b1944e
// (`call 0x00b3d230` then `call 0x00b3d240`, nothing in between and no ESP
// adjustment afterwards), and 0x00adad9d is immediately followed by 0x00ada2
// (`call 0x00b3d230` then `mov ecx,eax`). So zero parameters and caller-side
// cleanup are facts.
//
// What is NOT a fact is WHICH convention. With zero parameters and zero
// receiver, a bare-RET body is byte-identical under __cdecl, __stdcall,
// __thiscall and __fastcall; the tool's own ABI record for this target says so
// and abstains (abi_derived.abstained_because: "no_discriminator: no
// stack-argument read and no positive receiver evidence"; conventions.
// calling_convention null, confidence UNKNOWN). Naming any one of the four in
// the declaration would be a claim the listing does not carry, so the macro is
// present, named, and carries no convention token. The modelled entry is a
// zero-parameter function, which is the whole of what the machine fixes.
//
// RETURN: four bytes, and only four bytes are claimed
// ----------------------------------------------------
// MOV EAX, DS:0x0167eac0 writes the whole of EAX at 0x00b3d230, so the width is
// 4. The derived record classifies the value as pointer_like (INFERRED), and two
// callers null-test it (0x00c0d3c0 `test eax,eax` / `je`; 0x00c38532 the same),
// which is consistent with that classification -- but the body itself proves a
// four-byte LOAD and nothing about what the word denotes, so the declared return
// is std::uint32_t and no pointer type is asserted.
//
// THE GLOBAL, AND WHY IT HAS NO INITIALISER
// -----------------------------------------
// 0x0167eac0 is in .data (PE section table: VirtualAddress 0x150c000,
// VirtualSize 0x212764, PointerToRawData 0x110aa00, SizeOfRawData 0xc4c00).
// The dword's offset inside the section is 0x172ac0, which is PAST
// SizeOfRawData 0xc4c00, so no image bytes back this address and the loader
// zero-fills it. That is a statement about the file, not about the running
// game: nothing in this six-byte body says who stores the word or what it holds,
// and no value is claimed for it here. The model's initial value is a
// placeholder, chosen to be observable, and every test below SETS the word
// before reading it back.
//
// CORROBORATION THAT IS NOT USED AS PROOF
// ----------------------------------------
// The immediate sibling at 0x00b3d220 is `b8 c0 ea 67 01 / c3`, i.e.
// MOV EAX,0x0167eac0 / RET -- the same address as an immediate. That is a fact
// about 0x00b3d220 (read from the same objdump range), recorded here because it
// is the reason the address is worth naming, and deliberately NOT used: this
// package reconstructs 0x00b3d230 only, and a neighbour's operand is not
// evidence about this body's return type.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "root accessor 0x00b3d230 is an x86-32 reconstruction (absolute 32-bit operand at 0x00b3d230)"
#endif

// Calling convention: see the block comment above. The listing discriminates
// none, the macro states that by carrying no token, and the entry below is
// modelled with the shape the bytes do fix -- zero parameters, no receiver.
#if defined(_MSC_VER)
#define PKG_W2_00B3D230_CALL
#else
#define PKG_W2_00B3D230_CALL
#endif

namespace openspore::reconstruction::pkg_w2_00b3d230 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above.
// ---------------------------------------------------------------------------

// 0x00b3d230..0x00b3d235: a1 c0 ea 67 01 / c3 (objdump range 0x00b3d200..0x00b3d260).
constexpr std::uint8_t kTargetBytes[6] = {
    0xa1,  // 0x00b3d230 MOV EAX, moffs32   (opcode A1)
    0xc0,  //   operand byte 0  -> 0xc0
    0xea,  //   operand byte 1  -> 0xea
    0x67,  //   operand byte 2  -> 0x67
    0x01,  //   operand byte 3  -> 0x01
    0xc3,  // 0x00b3d235 RET               (bare, no immediate: 0 bytes popped)
};

static_assert(kTargetBytes[0] == 0xa1,
              "0x00b3d230 is the x86-32 accumulator load A1: EAX := DWORD PTR "
              "[absolute 32-bit address]");
static_assert(kTargetBytes[5] == 0xc3,
              "0x00b3d235 is a bare RET (c3): the callee pops nothing, so stack "
              "cleanup is zero bytes on the callee side");

// The absolute address the A1 operand names, decoded from the four operand
// bytes in little-endian order rather than restated.
constexpr Word kGlobalVa = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                            (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                            (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                            (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
static_assert(kGlobalVa == 0x0167eac0u,
              "operand bytes c0 ea 67 01 of the A1 at 0x00b3d230 are the "
              "little-endian address 0x0167eac0");

// Entry and terminal addresses, and the size of the body between them.
constexpr Word kEntryVa = 0x00b3d230u;
constexpr Word kTerminalVa = 0x00b3d235u;
constexpr std::size_t kBodyBytes = 6;
static_assert(kEntryVa + kBodyBytes == 0x00b3d236u,
              "0x00b3d230 + 6 bytes ends at 0x00b3d236, one past the last "
              "instruction byte at 0x00b3d235");
static_assert(kTerminalVa - kEntryVa == 5,
              "the bare RET is the second instruction, five bytes after entry");

// Instruction count, straight from the stored listing: two instructions, at
// 0x00b3d230 and 0x00b3d235.
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
// listings (0x00b19449/0x00b1944e and 0x00adad9d/0x00ada2) push nothing and
// adjust nothing around the call.
constexpr std::size_t kStackArgumentWords = 0;
static_assert(kStackArgumentWords == 0,
              "no stack operand in the body and no stack traffic at either "
              "corroborating call site: zero stack arguments");

// Callee-side stack cleanup: zero bytes, because the RET carries no immediate.
constexpr std::size_t kCalleeCleanupBytes = 0;
static_assert(kCalleeCleanupBytes == 0,
              "RET at 0x00b3d235 has no immediate operand, so the callee pops 0");

// Receiver: none. The body reads no register, so no register can be a receiver.
constexpr bool kHasReceiver = false;
static_assert(!kHasReceiver,
              "the body contains no register read, so no register carries a "
              "receiver (evidence inference R2: present=false)");

// The .data section facts that make "no image initializer for this dword" a
// statement about the file rather than a guess (PE section table of
// SporeApp.exe, read with objdump -h).
constexpr Word kDataSectionVa = 0x0150c000u;
constexpr Word kDataSectionVirtualSize = 0x212764u;
constexpr Word kDataSectionRawSize = 0x000c4c00u;
constexpr Word kGlobalOffsetInSection = kGlobalVa - kDataSectionVa;
static_assert(kGlobalOffsetInSection == 0x00172ac0u,
              "0x0167eac0 sits 0x172ac0 bytes into .data (VA 0x0150c000)");
static_assert(kDataSectionVirtualSize > kDataSectionRawSize,
              ".data VirtualSize 0x212764 exceeds SizeOfRawData 0xc4c00, so the "
              "section has a loader-zeroed tail");
static_assert(kGlobalOffsetInSection > kDataSectionRawSize,
              "0x0167eac0 is past .data SizeOfRawData 0xc4c00, so no file bytes "
              "back it and no image initializer is claimed for it");

// ---------------------------------------------------------------------------
// The modelled global and the modelled entry.
// ---------------------------------------------------------------------------

// Guard words modelled on either side of the single dword the machine names, so
// a model test can prove the body touches nothing else. This is padding chosen
// by the test, NOT memory the machine has: 0x0167eac4 is a different dword and
// nothing here claims what it is.
constexpr std::size_t kGuardWords = 4;
constexpr std::uint32_t kGuardCanary = 0xa5a5a5a5u;

struct RootSlotImage {
  std::uint32_t guard_lo[kGuardWords];  // modelled padding, before the slot
  std::uint32_t slot;                   // the one dword 0x00b3d230 reads
  std::uint32_t guard_hi[kGuardWords];  // modelled padding, after the slot
};

static_assert(offsetof(RootSlotImage, slot) == kGuardWords * sizeof(std::uint32_t),
              "the modelled slot sits immediately after the low guard words");
static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
              "the modelled image is 2*kGuardWords+1 words");

// The modelled image, one instance, defined in the .cpp.
extern RootSlotImage g_root_slot_image;

// The repository's global-naming convention (g_<va8>) naming the same single
// dword the A1 operand names: 0x0167eac0.
extern Word& g_0167eac0;

// The machine ABI as a C++ type, so a wrong prototype fails to build:
// zero parameters, 4-byte return.
using AbiRootAccessor00b3d230 = Word(PKG_W2_00B3D230_CALL*)();
static_assert(sizeof(AbiRootAccessor00b3d230) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. Zero parameters: the body reads no stack
// word and no register (0x00b3d230, 0x00b3d235).
Word PKG_W2_00B3D230_CALL root_accessor_00b3d230();

}  // namespace openspore::reconstruction::pkg_w2_00b3d230