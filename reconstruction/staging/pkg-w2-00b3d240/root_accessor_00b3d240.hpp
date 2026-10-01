#pragma once

// Reconstruction of 0x00b3d240 (SporeApp.exe 3.1.0.22).
//
// THE COMPLETE BODY: six bytes, two instructions
// ------------------------------------------------
//     0x00b3d240  a1 c4 ea 67 01   MOV EAX, DS:0x0167eac4
//     0x00b3d245  c3               RET          (bare: the callee pops nothing)
//
// Two INDEPENDENT machine sources agree on exactly this body and on nothing
// longer:
//
//   1. `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=
//      0x00b3d230 --stop-address=0x00b3d260` -- the two instructions above,
//      followed by INT3 padding (cc) at 0x00b3d246..0x00b3d24f, which is the
//      boundary of the body from the other side: the next function starts at
//      0x00b3d250.
//   2. The live Ghidra bridge on the same binary, which reports
//      `FUN_00b3d240`, signature `undefined FUN_00b3d240(void)`, body_start
//      00b3d240, body_end 00b3d245, and a two-instruction listing
//      `00b3d240 MOV EAX,[0x0167eac4]` / `00b3d245 RET`.
//
// The evidence pack committed for this target
// (reconstruction/evidence/00b3d240/evidence.json) does NOT carry the machine
// listing: `categories.disassembly`, `categories.abi_derived`,
// `categories.ghidra_function`, `categories.globals`, `categories.types`,
// `categories.abi` and `categories.decompilation` are all
// availability=unavailable / evidence_state=MISSING on this record, with
// `categories.disassembly.listing_state = "missing"`. Nothing in this package is
// therefore sourced from that pack's disassembly or ABI envelope, and no claim
// below is attributed to it.
//
// `a1` is the x86-32 accumulator-load form: opcode A1 followed by a four-byte
// little-endian absolute address. The operand bytes are c4 ea 67 01, i.e.
// 0x0167eac4, and kGlobalVa below is DECODED from those four bytes rather than
// restated, so the constant cannot drift away from the machine image.
//
// CALLING CONVENTION: NOT PROVEN, AND THEREFORE NOT INVENTED
// ---------------------------------------------------------
// The macro below is deliberately empty on both arms. What the bytes prove is:
//
//   * no register receiver -- the body reads no register at all, so ECX (the
//     only register __thiscall could deliver a receiver in) is never consumed;
//   * no stack argument -- the body contains no memory operand naming ESP or
//     any stack displacement, so nothing is popped;
//   * zero bytes of callee cleanup -- the terminal is a bare RET (c3) with no
//     immediate.
//
// Two caller listings corroborate "no stack argument" from the other side of
// the call. At 0x00b19298/0x00b1929d/0x00b192a2 the sequence is
// `call 0x00b3d280` / `call 0x00b3d240` / `mov edx,DWORD PTR [eax]` -- nothing
// is pushed before either call and nothing adjusts ESP afterwards. At
// 0x00b1944e/0x00b19453 the sequence is `call 0x00b3d240` immediately followed
// by `mov edx,DWORD PTR [eax]`, again with nothing pushed and nothing cleaned.
// So zero parameters and caller-side cleanup are facts.
//
// What is NOT a fact is WHICH convention. With zero parameters and zero
// receiver, a bare-RET body is byte-identical under __cdecl, __stdcall,
// __thiscall and __fastcall: all four pop nothing and consume no register. The
// only convention-discriminating fact the body carries is "the callee pops
// zero bytes", and that is equally true of __cdecl and of __stdcall with zero
// parameters. Naming any one of the four in the declaration would be a claim
// the listing does not carry, so the macro is present, named, and carries no
// convention token. The modelled entry is a zero-parameter function, which is
// the whole of what the machine fixes.
//
// RETURN: four bytes, and only four bytes are claimed
// ----------------------------------------------------
// MOV EAX, DS:0x0167eac4 writes the whole of EAX at 0x00b3d240, so the width is
// 4. Two callers dereference the returned word as an address -- 0x00b19453 is
// `mov edx,DWORD PTR [eax]`, and 0x00b19457/0x00b1945a then load
// `DWORD PTR [edx+0x34]` and `call eax`, so the word's first dword is read as a
// vtable pointer. That is a fact about the CALLERS' use of the return value,
// not about what the word denotes; the body itself proves a four-byte load and
// nothing more, so the declared return is std::uint32_t and no pointer type is
// asserted.
//
// THE GLOBAL, AND WHY IT HAS NO INITIALISER
// -----------------------------------------
// 0x0167eac4 is inside the writable .data segment (the Ghidra bridge reports
// .data at 0x0150c000..0x0171e763, readable and writable). In the PE section
// table .data has VMA 0x0150c000 and SizeOfRawData 0xc4c00, i.e. file-backed
// bytes only through 0x015d0bff, while VirtualSize is 0x212764. This dword's
// offset inside the section is 0x172ac4, which is PAST SizeOfRawData 0xc4c00,
// so no image bytes back this address and the loader zero-fills it. That is a
// statement about the file, not about the running game: nothing in this six-byte
// body says who stores the word or what it holds, and no value is claimed for
// it here. The model's initial value is a placeholder, chosen to be observable,
// and every test below SETS the word before reading it back.
//
// The data-reference sidecar knowledgegraph/triage/datarefs-2540f2ca.tsv (row
// 53898) records exactly one reference for this function:
// `00b3d240  0167eac4  read  .data -wr  00b3d240`. That is the only row in the
// whole artifact whose target is 0x0167eac4, so within that pinned snapshot
// this accessor is the only direct reader of the address. No write row for
// 0x0167eac4 exists in the artifact either, which is a statement about that
// artifact's direct references and NOT a claim that nothing ever stores the
// word: a store through a register holding the address produces no such row.
//
// NEIGHBOUR ACCESSORS, RECORDED AND NOT USED AS PROOF
// ----------------------------------------------------
// The immediate siblings are the same six-byte shape over other addresses:
// 0x00b3d230 reads 0x0167eac0, 0x00b3d250 reads 0x0167ead0, 0x00b3d280 reads
// 0x0167eacc, and 0x00b3d2a0 reads 0x0167eae4 (all read from the same objdump
// range). That is why the address is worth naming, and it is deliberately NOT
// used as evidence: a neighbour's operand is not evidence about this body's
// return type, this body's receiver, or this body's global, and no struct
// layout is claimed for the .data words these addresses happen to be near.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "root accessor 0x00b3d240 is an x86-32 reconstruction (absolute 32-bit operand at 0x00b3d240)"
#endif

// Calling convention: see the block comment above. The listing discriminates
// none, the macro states that by carrying no token, and the entry below is
// modelled with the shape the bytes do fix -- zero parameters, no receiver.
#if defined(_MSC_VER)
#define PKG_W2_00B3D240_CALL
#else
#define PKG_W2_00B3D240_CALL
#endif

namespace openspore::reconstruction::pkg_w2_00b3d240 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above.
// ---------------------------------------------------------------------------

// 0x00b3d240..0x00b3d245: a1 c4 ea 67 01 / c3 (objdump range 0x00b3d230..0x00b3d260).
constexpr std::uint8_t kTargetBytes[6] = {
    0xa1,  // 0x00b3d240 MOV EAX, moffs32   (opcode A1)
    0xc4,  //   operand byte 0  -> 0xc4
    0xea,  //   operand byte 1  -> 0xea
    0x67,  //   operand byte 2  -> 0x67
    0x01,  //   operand byte 3  -> 0x01
    0xc3,  // 0x00b3d245 RET               (bare, no immediate: 0 bytes popped)
};

static_assert(kTargetBytes[0] == 0xa1,
              "0x00b3d240 is the x86-32 accumulator load A1: EAX := DWORD PTR "
              "[absolute 32-bit address]");
static_assert(kTargetBytes[5] == 0xc3,
              "0x00b3d245 is a bare RET (c3): the callee pops nothing, so stack "
              "cleanup is zero bytes on the callee side");

// The absolute address the A1 operand names, decoded from the four operand
// bytes in little-endian order rather than restated.
constexpr Word kGlobalVa = static_cast<Word>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                            (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                            (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                            (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
static_assert(kGlobalVa == 0x0167eac4u,
              "operand bytes c4 ea 67 01 of the A1 at 0x00b3d240 are the "
              "little-endian address 0x0167eac4");

// Entry and terminal addresses, and the size of the body between them.
constexpr Word kEntryVa = 0x00b3d240u;
constexpr Word kTerminalVa = 0x00b3d245u;
constexpr std::size_t kBodyBytes = 6;
static_assert(kEntryVa + kBodyBytes == 0x00b3d246u,
              "0x00b3d240 + 6 bytes ends at 0x00b3d246, one past the last "
              "instruction byte at 0x00b3d245");
static_assert(kTerminalVa - kEntryVa == 5,
              "the bare RET is the second instruction, five bytes after entry");

// Instruction count, corroborated by both machine sources: two instructions,
// at 0x00b3d240 and 0x00b3d245.
constexpr std::size_t kInstructionCount = 2;
static_assert(kInstructionCount == 2,
              "both machine sources list exactly two instructions (MOV EAX,[...]; RET)");

// Return width: MOV EAX writes all four bytes of EAX, so the returned word is
// 4 bytes wide. No narrower and no wider.
constexpr std::size_t kReturnWidthBytes = 4;
static_assert(kReturnWidthBytes == sizeof(Word),
              "the machine writes the whole of EAX, so the returned word is "
              "exactly one 32-bit word");

// Stack arguments: none. The body names no stack memory operand, and the two
// caller listings (0x00b1929d/0x00b192a2 and 0x00b1944e/0x00b19453) push
// nothing and adjust nothing around the call.
constexpr std::size_t kStackArgumentWords = 0;
static_assert(kStackArgumentWords == 0,
              "no stack operand in the body and no stack traffic at either "
              "corroborating call site: zero stack arguments");

// Callee-side stack cleanup: zero bytes, because the RET carries no immediate.
constexpr std::size_t kCalleeCleanupBytes = 0;
static_assert(kCalleeCleanupBytes == 0,
              "RET at 0x00b3d245 has no immediate operand, so the callee pops 0");

// Receiver: none. The body reads no register, so no register can be a receiver.
constexpr bool kHasReceiver = false;
static_assert(!kHasReceiver,
              "the body contains no register read, so no register carries a "
              "receiver");

// Writes: none. The only memory operand in the body is the SOURCE of a MOV into
// EAX, and the RET writes nothing, so the body performs no store at all. The
// data-reference sidecar agrees on the mode: its single row for this function
// records `0167eac4 read`, not `write`.
constexpr std::size_t kMemoryStores = 0;
static_assert(kMemoryStores == 0,
              "MOV EAX's operand is a source, not a destination, and RET stores "
              "nothing: zero memory stores in the body");

// The .data section facts that make "no image initializer for this dword" a
// statement about the file rather than a guess (PE section table of
// SporeApp.exe via `objdump -h`, and the Ghidra bridge's segment table for
// VirtualSize).
constexpr Word kDataSectionVa = 0x0150c000u;
constexpr Word kDataSectionVirtualSize = 0x212764u;
constexpr Word kDataSectionRawSize = 0x000c4c00u;
constexpr Word kGlobalOffsetInSection = kGlobalVa - kDataSectionVa;
static_assert(kGlobalOffsetInSection == 0x00172ac4u,
              "0x0167eac4 sits 0x172ac4 bytes into .data (VA 0x0150c000)");
static_assert(kDataSectionVirtualSize > kDataSectionRawSize,
              ".data VirtualSize 0x212764 exceeds SizeOfRawData 0xc4c00, so the "
              "section has a loader-zeroed tail");
static_assert(kGlobalOffsetInSection > kDataSectionRawSize,
              "0x0167eac4 is past .data SizeOfRawData 0xc4c00, so no file bytes "
              "back it and no image initializer is claimed for it");

// ---------------------------------------------------------------------------
// The modelled global and the modelled entry.
// ---------------------------------------------------------------------------

// Guard words modelled on either side of the single dword the machine names, so
// a model test can prove the body touches nothing else. This is padding chosen
// by the test, NOT memory the machine has: 0x0167eac0 and 0x0167ead0 are
// different dwords (read by the neighbours 0x00b3d230 and 0x00b3d250) and
// nothing here claims what either of them is.
constexpr std::size_t kGuardWords = 4;
constexpr std::uint32_t kGuardCanary = 0xa5a5a5a5u;

struct RootSlotImage {
  std::uint32_t guard_lo[kGuardWords];  // modelled padding, before the slot
  std::uint32_t slot;                   // the one dword 0x00b3d240 reads
  std::uint32_t guard_hi[kGuardWords];  // modelled padding, after the slot
};

static_assert(offsetof(RootSlotImage, slot) == kGuardWords * sizeof(std::uint32_t),
              "the modelled slot sits immediately after the low guard words");
static_assert(sizeof(RootSlotImage) == (2 * kGuardWords + 1) * sizeof(std::uint32_t),
              "the modelled image is 2*kGuardWords+1 words");

// The modelled image, one instance, defined in the .cpp.
extern RootSlotImage g_root_slot_image;

// The repository's global-naming convention (g_<va8>) naming the same single
// dword the A1 operand names: 0x0167eac4.
extern Word& g_0167eac4;

// The machine ABI as a C++ type, so a wrong prototype fails to build:
// zero parameters, 4-byte return.
using AbiRootAccessor00b3d240 = Word(PKG_W2_00B3D240_CALL*)();
static_assert(sizeof(AbiRootAccessor00b3d240) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. Zero parameters: the body reads no stack
// word and no register (0x00b3d240, 0x00b3d245).
Word PKG_W2_00B3D240_CALL root_accessor_00b3d240();

}  // namespace openspore::reconstruction::pkg_w2_00b3d240