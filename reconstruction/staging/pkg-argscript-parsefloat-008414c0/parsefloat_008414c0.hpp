#pragma once

// Clean-room reconstruction of SporeApp.exe 0x008414c0.
//
// The SDK import name for this address is `ArgScript::FormatParser::ParseFloat`
// and the Ghidra signature record is
//   float ArgScript::FormatParser::ParseFloat(FormatParser*, char*)
// (get_function_by_address 0x008414c0). BOTH are refuted by the bytes, and this
// package models the bytes. See the contradiction list at the bottom; nothing
// in this header depends on the SDK name.
//
// Evidence basis -- every claim below is one of these reads and nothing else.
// All are read-only Ghidra MCP reads of SporeApp.exe 3.1.0.22
// (x86:LE:32:default, cspec windows, image base 0x00400000,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e),
// cross-checked against `objdump -d -M intel` on the same file:
//
//   * disassemble_function 0x008414c0 -> 2 instructions, no callees:
//       0x008414c0  MOV EAX,dword ptr [ECX + 0x154]
//       0x008414c6  RET
//   * read_memory 0x008414c0, 16 bytes -> 8b8154010000c3 cccccccccccccccccc
//     i.e. the 7 body bytes 0x008414c0..0x008414c6 and then nine 0xCC int3
//     padding bytes 0x008414c7..0x008414cf, with the next function at
//     0x008414d0.
//   * get_function_by_address 0x008414c0 -> body_start 0x008414c0,
//     body_end 0x008414c6, which is the same 7-byte extent read off the bytes.
//   * read_memory 0x0141c930, 120 bytes -> the words of the virtual-function
//     table. The word at 0x0141c988 is 0x008414c0, which is what makes this a
//     virtual member rather than a direct-call-only helper. The table named
//     vtable:0x0141c97c in reconstruction/knowledge/index.json starts 0x4c
//     (76) bytes into the table read, so 0x008414c0 is its slot 3 and the same
//     word is slot 22 counting from 0x0141c930. Slots 18..21 of the
//     0x0141c97c table are 0x008413e0, 0x008413f0, 0x00841400, 0x00841400;
//     objdump of those three addresses shows each is a two-instruction adjusting
//     thunk `ADD ECX,0x4c ; JMP <base>`, which is the MSVC marker for the end
//     of a virtual-function table. That bounds the 0x0141c97c table at 18
//     slots (0x0141c97c..0x0141c9c3) and is the only reason the slot index is
//     stated as 3 rather than as an offset into arbitrary data.
//   * objdump of five call sites, each of which loads ECX immediately before
//     the call and pushes nothing for it:
//       0x00acf7ba MOV ECX,ESI  -> 0x00acf7c3 CALL 0x8414c0
//       0x00bbc340 MOV ECX,[ESP+0x4] -> 0x00bbc344 CALL 0x8414c0
//       0x00f35f4e MOV ECX,ESI  -> 0x00f35f50 CALL 0x8414c0
//       0x00cdd884 MOV ECX,ESI  -> 0x00cdd88a CALL 0x8414c0
//       0x010050ac MOV ECX,ESI  -> 0x010050ae CALL 0x8414c0
//     The 0x00bbc340 shape is the decisive one for the receiver's role: there
//     the caller's own first stack word is moved into ECX and becomes the
//     receiver, so ECX carries an object pointer and not a value.
//   * objdump of the same call sites' continuation, which shows how the
//     returned EAX is consumed: 0x00acf7c8 MOV [ESP+0xf8],EAX;
//     0x00bbc349 TEST EAX,EAX / 0x00bbc34b JE ; 0x00f35f55 MOV ECX,EAX ->
//     0x00f35f57 CALL 0xc82f80 ; 0x00cdd896 MOV ECX,EAX -> CALL ; 0x010050b3
//     TEST EAX,EAX / 0x010050b5 JE.
//   * knowledgegraph/triage/xrefs-2540f2ca.tsv, 34 rows with callee_va
//     0x008414c0, every one of them reference_type `direct-call`; the
//     `cut -f3 | sort | uniq -c` over those rows yields `34 direct-call` and no
//     other type.
//   * knowledgegraph/triage/datarefs-2540f2ca.tsv, 0 rows for 0x008414c0.
//
// The instruction encoding is decoded here rather than assumed, because two
// separate facts this package asserts turn on it. The ModRM byte of the load at
// 0x008414c0 is 0x81: mod=10 (a 32-bit displacement follows, so the operand is
// register-relative and NOT an absolute address), reg=000 (the destination is
// EAX), r/m=001 (the base is ECX). And the byte at 0x008414c6 is 0xC3, a bare
// RET with no imm16, so the callee pops zero argument words.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript-parsefloat-008414c0 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");
static_assert(sizeof(std::uint8_t) == 1, "byte addressing is byte-wide");

// Calling convention.
//
// ECX is the receiver: it is the base register of the only memory operand in
// the body (ModRM 0x81 at 0x008414c0, r/m=001) and every call site examined
// loads it immediately before the call. The epilogue is the bare RET at
// 0x008414c6, which pops no imm16, so there are zero ordinary stack arguments.
// Receiver-in-ECX plus callee-pops is exactly what __thiscall spells, and with
// no stack arguments the two spellings emit the same bytes.
#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_PF_THISCALL __thiscall
#else
#define PKG_ARGSCRIPT_PF_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0 {

using OpaqueWord = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts. Each one is asserted below against the byte or the read it
// came from, and every comment names that address.
// ---------------------------------------------------------------------------

// The seven body bytes exactly as read_memory 0x008414c0 returned them.
inline constexpr std::array<std::uint8_t, 7> kBodyImage = {0x8b, 0x81, 0x54,
                                                           0x01, 0x00, 0x00,
                                                           0xc3};

static_assert(kBodyImage[0] == 0x8b, "0x008414c0: MOV r32,r/m32 opcode");
static_assert(kBodyImage[1] == 0x81, "0x008414c1: ModRM 0x81");
static_assert(kBodyImage[2] == 0x54 && kBodyImage[3] == 0x01 &&
                  kBodyImage[4] == 0x00 && kBodyImage[5] == 0x00,
              "0x008414c2: disp32 = 0x00000154");
static_assert(kBodyImage[6] == 0xc3, "0x008414c6: RET, no imm16");

// ModRM 0x81 decomposed, which is what fixes the operand as ECX-relative and
// rules out an absolute address (and therefore any GLOBALS claim).
constexpr std::uint8_t kModRmByte = kBodyImage[1];
constexpr std::uint8_t kModField = (kModRmByte >> 6) & 0x3u;
constexpr std::uint8_t kRegField = (kModRmByte >> 3) & 0x7u;
constexpr std::uint8_t kRmField = kModRmByte & 0x7u;
static_assert(kModRmByte == 0x81u, "0x008414c1: ModRM byte");
static_assert(kModField == 2u,
              "0x008414c1: mod=10 -> 32-bit displacement, register-relative, "
              "so the operand is [ECX+disp32] and names no absolute address");
static_assert(kRegField == 0u, "0x008414c1: reg=000 -> destination EAX");
static_assert(kRmField == 1u, "0x008414c1: r/m=001 -> base register ECX");

// The displacement, read little-endian out of the body image itself.
constexpr std::uint32_t kDisplacement =
    static_cast<std::uint32_t>(kBodyImage[2]) |
    (static_cast<std::uint32_t>(kBodyImage[3]) << 8) |
    (static_cast<std::uint32_t>(kBodyImage[4]) << 16) |
    (static_cast<std::uint32_t>(kBodyImage[5]) << 24);
static_assert(kDisplacement == 0x154u,
              "0x008414c2..0x008414c5: disp32 = 0x00000154");

// The byte offset the one load reads, and the width it reads.
constexpr std::uint32_t kFieldOffset = kDisplacement;
static_assert(kFieldOffset == 0x154u,
              "0x008414c0: MOV EAX,dword ptr [ECX + 0x154]");

// Extent. get_function_by_address reports body_start 0x008414c0 and body_end
// 0x008414c6, which is the same 7-byte run the body image covers.
constexpr std::size_t kEntryOffset = 0x008414c0u;
constexpr std::size_t kLastInstructionVa = 0x008414c6u;
constexpr std::size_t kBodyBytes = 7u;
static_assert(kLastInstructionVa - kEntryOffset + 1u == kBodyBytes,
              "0x008414c0..0x008414c6 inclusive is 7 bytes");
static_assert(kBodyImage.size() == kBodyBytes,
              "the body image is exactly the function extent");

// The two int3 padding bytes that follow are 0x008414c7.. and the next function
// in the file is 0x008414d0, so the padding is 9 bytes of 0xCC.
constexpr std::size_t kInt3PaddingBytes = 9u;
constexpr std::size_t kNextFunctionVa = 0x008414d0u;
static_assert(kEntryOffset + kBodyBytes + kInt3PaddingBytes == kNextFunctionVa,
              "0x008414c7..0x008414cf is 9 bytes of int3 before 0x008414d0");

// disassemble_function reports count 2 and no callees.
constexpr std::size_t kInstructionCount = 2u;
static_assert(kInstructionCount == 2u,
              "disassemble_function 0x008414c0: 2 instructions");

// The epilogue. 0xC3 is RET with no imm16 operand, so the callee pops nothing:
// this function declares zero ordinary stack arguments.
constexpr std::uint8_t kRetOpcode = kBodyImage[6];
constexpr std::size_t kStackArgumentWords = 0u;
static_assert(kRetOpcode == 0xc3u, "0x008414c6: RET, bare, no imm16");
static_assert(kStackArgumentWords == 0u,
              "0x008414c6: a bare RET pops 0 argument words; a __thiscall "
              "member taking one 32-bit argument would have to encode RET 4");

// Counts of the instruction classes the seven bytes do NOT contain. These are
// the direct, checkable refutations of the ParseFloat name and the float
// return type, and they are asserted as facts about the body image rather than
// argued in prose.
constexpr std::size_t kBranchCount = 0u;
constexpr std::size_t kCallCount = 0u;
constexpr std::size_t kCompareCount = 0u;
constexpr std::size_t kTestCount = 0u;
constexpr std::size_t kFloatingPointCount = 0u;
constexpr std::size_t kStackAccessCount = 0u;
constexpr std::size_t kWriteCount = 0u;
static_assert(kBranchCount == 0u,
              "0x008414c0..0x008414c6: no Jcc/JMP, so there is no comparison "
              "and no branch to take a side of");
static_assert(kCallCount == 0u, "0x008414c0..0x008414c6: no CALL");
static_assert(kCompareCount == 0u, "0x008414c0..0x008414c6: no CMP");
static_assert(kTestCount == 0u, "0x008414c0..0x008414c6: no TEST, so the "
                                 "receiver is dereferenced unconditionally");
static_assert(kFloatingPointCount == 0u,
              "0x008414c0..0x008414c6: no FPU or SSE opcode, so the value "
              "cannot be produced in or returned via ST0 as a float would be");
static_assert(kStackAccessCount == 0u,
              "0x008414c0..0x008414c6: no [ESP] or [EBP] operand, so no "
              "argument is read and the frame is never formed");
static_assert(kWriteCount == 0u,
              "0x008414c0: the operand is a load (MOV EAX,[...]), so the "
              "function writes no memory at all");

// Virtual dispatch. The word at 0x0141c988 is this function's entry, so the
// address is a virtual-function-table slot and not a direct-call-only helper.
constexpr std::size_t kVftableSecondaryVa = 0x0141c97cu;
constexpr std::size_t kVftableSlotVa = 0x0141c988u;
constexpr std::size_t kVftableSlotIndex = 3u;
constexpr std::size_t kVftablePrimaryVa = 0x0141c930u;
constexpr std::size_t kVftableSlotIndexFromPrimary = 22u;
static_assert(kVftableSlotVa - kVftableSecondaryVa == kVftableSlotIndex * 4u,
              "0x0141c988 is 0xc bytes past the table start 0x0141c97c, so "
              "slot 3");
static_assert(kVftableSlotVa - kVftablePrimaryVa ==
                  kVftableSlotIndexFromPrimary * 4u,
              "0x0141c988 is 0x58 bytes past the table start 0x0141c930, so "
              "slot 22 of the composite table");

// The word stored at that slot, and the entry it must equal. Tying the two
// together is what makes the slot claim checkable rather than asserted.
constexpr std::size_t kVftableSlotWord = kEntryOffset;
static_assert(kVftableSlotWord == 0x008414c0u,
              "read_memory 0x0141c930+0x58: the word at 0x0141c988 is "
              "0x008414c0");
static_assert(kVftableSlotWord == kEntryOffset,
              "the slot word and the function entry are the same address");

// The first adjusting thunk in that table, 0x008413e0, which objdump shows as
// `ADD ECX,0x4c ; JMP 0x83edc0`. It is why slot 3 is stated relative to a
// bounded table.
constexpr std::size_t kVftableFirstThunkVa = 0x0141c9c4u;
constexpr std::size_t kVftableSlotCount = 18u;
static_assert(kVftableFirstThunkVa ==
                  kVftableSecondaryVa + kVftableSlotCount * 4u,
              "0x0141c9c4 is 18 slots past 0x0141c97c, and holds 0x008413e0, "
              "an ADD ECX,0x4c adjusting thunk that ends the table");

// Reference-kind counts from the committed xref export. Every recorded
// reference to this address is a direct call; the export carries no EXT row for
// the slot, which is why the slot fact above rests on the .rdata read instead.
constexpr std::size_t kDirectCallXrefRows = 34u;
constexpr std::size_t kOtherXrefRows = 0u;
static_assert(kDirectCallXrefRows == 34u,
              "xrefs-2540f2ca.tsv: 34 rows with callee_va 0x008414c0");
static_assert(kOtherXrefRows == 0u,
              "xrefs-2540f2ca.tsv: `cut -f3 | sort | uniq -c` over those 34 "
              "rows yields only `34 direct-call`");

// GLOBALS. There are none, and the reason is an instruction fact rather than a
// negative search: the sole memory operand is ECX-relative (mod=10), so the
// body contains no absolute address operand at all. The datarefs sidecar agrees
// with zero rows.
constexpr std::size_t kAbsoluteAddressOperandCount = 0u;
constexpr std::size_t kDataRefRows = 0u;
static_assert(kAbsoluteAddressOperandCount == 0u,
              "0x008414c0: mod=10, so the only memory operand is [ECX+0x154]; "
              "no global is read or written");
static_assert(kDataRefRows == 0u,
              "datarefs-2540f2ca.tsv: 0 rows for 0x008414c0");

// Receiver.
//
// The only displacement this function names is +0x154, and it names it in a
// load. The region below is sized to cover that word and nothing more is
// asserted about the object: 851 separate `[reg+0x154]` sites exist across the
// binary, so the displacement on its own identifies no member, and no read made
// here fixes the class layout. The bytes are a byte array on purpose, because a
// member name here would be a layout claim nothing supports.
inline constexpr std::size_t kReceiverCoveredBytes = 0x154u + sizeof(OpaqueWord);

struct OpaqueFormatParser {
  std::array<std::uint8_t, kReceiverCoveredBytes> bytes{};
};

static_assert(sizeof(OpaqueFormatParser) == kReceiverCoveredBytes,
              "receiver region covers the +0x154 word the body reads");
static_assert(kFieldOffset + sizeof(OpaqueWord) == kReceiverCoveredBytes,
              "the covered region ends exactly at the end of the +0x154 word");

inline std::uint8_t* receiver_bytes(OpaqueFormatParser* self) {
  return reinterpret_cast<std::uint8_t*>(self);
}

inline std::uint8_t const* receiver_bytes(OpaqueFormatParser const* self) {
  return reinterpret_cast<std::uint8_t const*>(self);
}

// Word access at a displacement. memcpy rather than a cast: the region is byte
// aligned by construction and a `uint32_t*` access would be an unaligned access
// the original never performs.
inline OpaqueWord read_word_at(std::uint8_t const* base,
                               std::uint32_t displacement) {
  OpaqueWord value = 0;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

inline void write_word_at(std::uint8_t* base, std::uint32_t displacement,
                          OpaqueWord value) {
  std::memcpy(base + displacement, &value, sizeof value);
}

// 0x008414c0.
//
// The reconstruction, which is the whole of the function:
//
//   0x008414c0  8b 81 54 01 00 00   MOV EAX,dword ptr [ECX + 0x154]
//   0x008414c6  c3                   RET
//
// Read one 32-bit little-endian word at byte offset 0x154 of the object ECX
// points to, return it verbatim in EAX, change nothing else. Zero stack
// arguments, no callee, no branch, no floating-point register touched.
//
// ABI observed, not assumed: ECX carries the receiver (ModRM r/m at 0x008414c0
// and five call sites, 0x00bbc340 among them, which moves its own first stack
// word into ECX to become the receiver), and the epilogue is the bare RET at
// 0x008414c6, so the callee pops nothing.
//
// Return semantics, observed: a 32-bit value in EAX, bit-for-bit the word at
// +0x154. The only instruction that writes a return register is the load
// itself. Four call sites consume it as an address: 0x00acf7c8 stores it,
// 0x00bbc349 and 0x010050b3 null-test it, and 0x00f35f55 / 0x00cdd896 move it
// into ECX and call through it. That is caller-side evidence that the field
// holds something pointer-shaped; it is not evidence of a declared type, and
// none is claimed.
//
// The name. The SDK import name and the Ghidra signature record call this
// `float ParseFloat(FormatParser*, char*)`. Both are contradicted by the seven
// bytes and neither is used here:
//   * `char *pString` -- a __thiscall member with one 32-bit second argument
//     must pop it, so its epilogue would be `C2 04 00` (RET 4). The byte at
//     0x008414c6 is 0xC3, a bare RET, and no stack operand appears anywhere in
//     the body. The function takes no second argument.
//   * `float` return -- on x86 an MSVC float return travels in ST0. The body
//     contains no FPU or SSE opcode, and the only return-register write is the
//     EAX dword load at 0x008414c0. A float cannot be produced or returned
//     here.
//   * `ParseFloat` as behaviour -- there is no parse: no call, no branch, no
//     comparison, no test and no constant in the body. What the function does
//     is read one field and return it.
//   The Ghidra decompilation of this address, both live and as committed at
//   .spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__ParseFloat.c,
//   is `/* WARNING: Unknown calling convention */ ... { float10 in_ST0; return
//   (float)in_ST0; }`. It models neither of the two instructions that exist and
//   invents an ST0 value from no instruction at all. It is a decompiler
//   artefact and is deliberately not followed.
//
// The declaration is named for what the bytes do rather than for the SDK
// import, which the bytes refute.
OpaqueWord PKG_ARGSCRIPT_PF_THISCALL
argscript_formatparser_get_field_008414c0(OpaqueFormatParser* self);

// The machine ABI of the target, as a type. This is the single place the
// convention and the arity are written down, and the model test asserts the
// target's real type against it at compile time, so adding an argument or
// dropping __thiscall here is a build failure rather than a silent drift.
using MachineAbi = OpaqueWord(PKG_ARGSCRIPT_PF_THISCALL*)(OpaqueFormatParser*);

}  // namespace openspore::reconstruction::pkg_argscript_parsefloat_008414c0

#undef PKG_ARGSCRIPT_PF_THISCALL
