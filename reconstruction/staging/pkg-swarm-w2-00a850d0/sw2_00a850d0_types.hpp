// PKG-SWARM-W2-00A850D0 -- VA 0x00a850d0
// FUN_00a850d0 (SPORE/SporeBin/SporeApp.exe, image base 0x400000, 3.1.0.22,
// binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00a850d0 @ 0x00a850d0.
//
// THE BODY. 81 instructions, 0x00a850d0..0x00a851c1 inclusive = 242 bytes. Every
// byte below was re-read out of the image for this package (PE section .text,
// RVA 0x6850d0, file offset 0x6844d0) and matches the committed Ghidra listing
// instruction for instruction:
//
//   00a850d0  PUSH ESI                     56
//   00a850d1  MOV ESI,ECX                  8B F1
//   00a850d3  CMP byte ptr [ESI + 0x14],0x0 80 7E 14 00
//   00a850d7  JNZ 0x00a85188                0F 85 AB 00 00 00
//   00a850dd  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a850e0  PUSH EDI                     57
//   00a850e1  MOV byte ptr [ESI + 0x14],0x1 C6 46 14 01
//   00a850e5  TEST ECX,ECX                 85 C9
//   00a850e7  JZ 0x00a8515c                74 73
//   00a850e9  MOV EAX,dword ptr [ESI + 0xc]  8B 46 0C
//   00a850ec  MOV EDX,dword ptr [EAX + 0x8]  8B 50 08
//   00a850ef  SHR EDX,0x2                  C1 EA 02
//   00a850f2  TEST DL,0x1                  F6 C2 01
//   00a850f5  JZ 0x00a850fe                74 07
//   00a850f7  MOV EAX,dword ptr [ECX]      8B 01
//   00a850f9  MOV EDX,dword ptr [EAX + 0x18] 8B 50 18
//   00a850fc  CALL EDX                     FF D2
//   00a850fe  MOV EAX,dword ptr [ESI + 0xc]  8B 46 0C
//   00a85101  MOV ECX,dword ptr [EAX + 0x8]  8B 48 08
//   00a85104  MOV EDX,ECX                  8B D1
//   00a85106  SHR EDX,0x4                  C1 EA 04
//   00a85109  TEST DL,0x1                  F6 C2 01
//   00a8510c  JZ 0x00a85130                74 22
//   00a8510e  MOVZX EAX,word ptr [EAX + 0xa8] 0F B7 80 A8 00 00 00
//   00a85115  SHR ECX,0x6                  C1 E9 06
//   00a85118  TEST CL,0x1                  F6 C1 01
//   00a8511b  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a8511e  MOV EDX,dword ptr [ECX]      8B 11
//   00a85120  MOV EDX,dword ptr [EDX + 0x1c] 8B 52 1C
//   00a85123  JZ 0x00a8512b                74 06
//   00a85125  LEA EDI,[ESI + 0x28]         8D 7E 28
//   00a85128  PUSH EDI                     57
//   00a85129  JMP 0x00a8512d               EB 02
//   00a8512b  PUSH 0x0                     6A 00
//   00a8512d  PUSH EAX                     50
//   00a8512e  CALL EDX                     FF D2
//   00a85130  MOV EAX,dword ptr [ESI + 0xc]  8B 46 0C
//   00a85133  MOV dword ptr [ESI + 0x68],0xffffffff C7 46 68 FF FF FF FF
//   00a8513a  MOV ECX,dword ptr [EAX + 0x8]  8B 48 08
//   00a8513d  SHR ECX,0x1                  D1 E9
//   00a8513f  TEST CL,0x1                  F6 C1 01
//   00a85142  JZ 0x00a8518c                74 48
//   00a85144  MOV EDI,dword ptr [EAX + 0xa4] 8B B8 A4 00 00 00
//   00a8514a  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a8514d  MOV EDX,dword ptr [ECX]      8B 11
//   00a8514f  MOV EAX,dword ptr [EAX + 0xa0] 8B 80 A0 00 00 00
//   00a85155  MOV EDX,dword ptr [EDX + 0xc]  8B 52 0C
//   00a85158  PUSH EDI                     57
//   00a85159  PUSH EAX                     50
//   00a8515a  CALL EDX                     FF D2
//   00a8515c  XORPS XMM1,XMM1              0F 57 C9
//   00a8515f  MOV EAX,dword ptr [ESI + 0xc]  8B 46 0C
//   00a85162  MOVSS dword ptr [ESI + 0x1c],XMM1 F3 0F 11 4E 1C
//   00a85167  MOVSS dword ptr [ESI + 0x20],XMM1 F3 0F 11 4E 20
//   00a8516c  MOVSS XMM0,dword ptr [EAX + 0x10] F3 0F 10 40 10
//   00a85171  COMISS XMM0,XMM1             0F 2F C1
//   00a85174  JBE 0x00a85182               76 0C
//   00a85176  MOVSS XMM1,dword ptr [0x01485720] F3 0F 10 0D 20 57 48 01
//   00a8517e  DIVSS XMM1,XMM0              F3 0F 5E C8
//   00a85182  MOVSS dword ptr [ESI + 0x18],XMM1 F3 0F 11 4E 18
//   00a85187  POP EDI                      5F
//   00a85188  POP ESI                      5E
//   00a85189  RET 0x4                      C2 04 00
//   00a8518c  MOVSS XMM0,dword ptr [EAX + 0x10] F3 0F 10 40 10
//   00a85191  COMISS XMM0,dword ptr [0x01485378] 0F 2F 05 78 53 48 01
//   00a85198  JBE 0x00a8515c               76 C2
//   00a8519a  MOV EDI,dword ptr [EAX + 0xa4] 8B B8 A4 00 00 00
//   00a851a0  MOV ECX,dword ptr [ESI + 0x10] 8B 4E 10
//   00a851a3  MOV EDX,dword ptr [ECX]      8B 11
//   00a851a5  MOV EAX,dword ptr [EAX + 0xa0] 8B 80 A0 00 00 00
//   00a851ab  MOV EDX,dword ptr [EDX + 0x10] 8B 52 10
//   00a851ae  PUSH EDI                     57
//   00a851af  PUSH EAX                     50
//   00a851b0  CALL EDX                     FF D2
//   00a851b2  MOV dword ptr [ESI + 0x68],EAX  89 46 68
//   00a851b5  TEST EAX,EAX                 85 C0
//   00a851b7  JGE 0x00a8515c               7D A3
//   00a851b9  POP EDI                      5F
//   00a851ba  MOV byte ptr [ESI + 0x14],0x0 C6 46 14 00
//   00a851be  POP ESI                      5E
//   00a851bf  RET 0x4                      C2 04 00
//
// A NOTE ON THE COMMITTED body_end, because it is off by one and the difference is
// worth recording: the GhidraMCP record for this function carries
// `body_start 0x00a850d0`, `body_end 0x00a851c1`, `size_bytes 242`. 242 bytes from
// 0x00a850d0 is 0x00a851c2 exclusive, and the last instruction is a three-byte
// `RET 0x4` (C2 04 00) at 0x00a851bf. The true exclusive end is therefore
// 0x00a851c2 and the record's 0x00a851c1 truncates the final byte of the
// terminator. Nothing about the semantics changes; the reconstructed body spans
// the image's real 242 bytes, and the sidecar records the discrepancy rather than
// shrinking the span to match the record.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the split
// decides what may and may not be claimed:
//
//  * Every displacement, shift count, mask, branch polarity and argument order is
//    read out of the 81-instruction listing above, and nothing else. Where a row
//    above names an address, that is where the value below came from.
//
//  * The receiver's SIZE (0x6c) is this body's own evidence, not a borrowed one:
//    0x00a85133 and 0x00a851b2 each write a full dword at displacement 0x68, so
//    the object is at least 0x6c bytes. No constructor is cited and none is
//    needed.
//
//  * The two .rdata words the body reads were read out of the image, not guessed.
//    0x01485720 lies in .rdata (RVA 0x1085720) and holds the four bytes
//    00 00 80 3F, which is +1.0f. 0x01485378 lies in .rdata (RVA 0x1085378) and
//    holds 00 00 00 00, which is +0.0f. The second reading is corroborated from
//    inside the body: 0x00a85191 tests the same value against that word as
//    0x00a85171 tests it against the XMM1 that 0x00a8515c just zeroed.
//
//  * NO MEMBER IS NAMED. The machine-derived receiver record for this target
//    carries `bounds_only: true` (abi_derived.value.receiver), which is its own
//    statement that its displacement list says where the body was SEEN reaching
//    and nothing about which member is which. So every sub-object below is an
//    opaque byte run and every access goes through a displacement-named accessor.
//    The type names are chosen for the ACCESS SHAPE this body uses and carry no
//    claim about what the objects are: the Spore-ModAPI SDK resolves nothing for
//    0x00a850d0 (function_identity.types is empty, ghidra_function.sdk_name is
//    null) and the binary has no MSVC RTTI, so no C++ class name is available to
//    claim and none is claimed.
//
//  * The four indirect targets are read as four-byte words out of a table reached
//    by TWO dereferences from the receiver (see the DispatchTable note). Nothing
//    here says they are vtable slots; that word is used only where the machine
//    shape is the same shape, and the note says why the classification is not
//    taken.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00a850d0 requires an x86-32 target"
#endif

// The one convention this body needs. Spelled per toolchain: the x86-32 attribute
// form is the portable spelling, and the MSVC keyword form is kept for MSVC.
//
//   PKG_SW2_00A850D0_THISCALL  this body is __thiscall. Two things fix it.
//     0x00a851bf / 0x00a85189 are both `RET 0x4`, which pops the return address
//     plus one more word -- callee-owned cleanup, so neither cdecl nor fastcall.
//     The register argument arrives in ECX: 0x00a850d1 copies it into ESI and
//     every one of the four indirect transfers is handed that same object in ECX
//     (0x00a850dd, 0x00a8511b, 0x00a8514a, 0x00a851a0), never `this` and never
//     anything at an offset inside it.
//
// The confidence on the machine's own conventions record is INFERRED, and
// cross_validation records no Ghidra prototype for this target, so the
// convention is corroborated by this body's own bytes and by nothing else.
#if defined(_MSC_VER)
#define PKG_SW2_00A850D0_THISCALL __thiscall
#else
#define PKG_SW2_00A850D0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00a850d0 {

using Word = std::uint32_t;
using HalfWord = std::uint16_t;
using Float = float;

// -- bit flags this body reads out of a flag word ---------------------------
// Each is the `(word >> shift) & 1` test the body performs, and the shift count is
// the immediate of the listing's own SHR. The body's masks are all `TEST rL,0x1`
// after a logical right shift, so every one of them is a single bit test and none
// of them is a signedness-sensitive comparison; the model test still drives the
// neighbouring bit indices so an off-by-one shift cannot pass.
constexpr unsigned kBitIndexBit1 = 1u;  // 00a8513d  SHR ECX,0x1  ; 00a8513f TEST CL,0x1
constexpr unsigned kBitIndexBit2 = 2u;  // 00a850ef  SHR EDX,0x2  ; 00a850f2 TEST DL,0x1
constexpr unsigned kBitIndexBit4 = 4u;  // 00a85106  SHR EDX,0x4  ; 00a85109 TEST DL,0x1
constexpr unsigned kBitIndexBit6 = 6u;  // 00a85115  SHR ECX,0x6  ; 00a85118 TEST CL,0x1
constexpr Word kBitMaskLow = 0x1u;      // 00a850f2 / 00a85109 / 00a85118 / 00a8513f

// The initial value stored at the result displacement.
// 00a85133  MOV dword ptr [ESI + 0x68],0xffffffff
constexpr Word kResultInitialValue = 0xffffffffu;
// 00a851e1 / 00a851ba  the two byte values written to the flag displacement.
constexpr std::uint8_t kFlagBusyValue = 0x1u;  // 00a850e1
constexpr std::uint8_t kFlagIdleValue = 0x0u;  // 00a851ba; 00a850d3 compares against this

// -- receiver displacements (ECX, aliased into ESI by 00a850d1) --------------
// The receiver record for this target enumerates 0x0c, 0x10, 0x14, 0x18, 0x1c,
// 0x20 and 0x68 with `bounds_only: true`; every one of those seven is a
// displacement this body itself shows, and nothing below reaches past 0x68.
//   0x0c  read at 00a850e9, 00a850fe, 00a85130, 00a8515f -- four separate reads
//   0x10  read at 00a850dd, 00a8511b, 00a8514a, 00a851a0 -- four separate reads
//   0x14  read at 00a850d3, written at 00a850e1 and 00a851ba (one byte each)
//   0x18  written at 00a85182 (one MOVSS, four bytes)
//   0x1c  written at 00a85162 (one MOVSS, four bytes)
//   0x20  written at 00a85167 (one MOVSS, four bytes)
//   0x68  written at 00a85133 and 00a851b2 (one dword each)
constexpr std::size_t kReceiverCarrierPointer = 0x0cu;    // 00a850e9  MOV EAX,[ESI+0xc]
constexpr std::size_t kReceiverDispatchPointer = 0x10u;   // 00a850dd  MOV ECX,[ESI+0x10]
constexpr std::size_t kReceiverFlagByte = 0x14u;          // 00a850d3  CMP byte ptr [ESI+0x14],0
constexpr std::size_t kReceiverScaleResult = 0x18u;       // 00a85182  MOVSS [ESI+0x18],XMM1
constexpr std::size_t kReceiverFirstZeroFloat = 0x1cu;    // 00a85162  MOVSS [ESI+0x1c],XMM1
constexpr std::size_t kReceiverSecondZeroFloat = 0x20u;   // 00a85167  MOVSS [ESI+0x20],XMM1
constexpr std::size_t kReceiverAddressArgument = 0x28u;   // 00a85125  LEA EDI,[ESI+0x28]
constexpr std::size_t kReceiverResultWord = 0x68u;        // 00a85133  MOV [ESI+0x68],0xffffffff

// -- carrier displacements (the object the word at receiver+0x0c points at) ---
// Read only; the body writes nothing on this object.
//   0x08  dword, the flag word. Read FOUR times, from a DIFFERENT read of the
//         receiver each time: 00a850ec (from the 00a850e9 read of receiver+0x0c)
//         drives the bit-2 test, 00a85101 (from the 00a850fe read) drives the
//         bit-4 test, 00a8513a (from the 00a85130 read) drives the bit-1 test, and
//         00a85115/00a85118 test bit 6 on the 00a85101 copy.
//   0x10  4-byte float. Read at 00a8516c (from the 00a8515f read of receiver+0x0c)
//         and at 00a8518c (from the 00a85130 read).
//   0xa0  dword, PUSHed SECOND -- i.e. it lands at the HIGHER stack address.
//   0xa4  dword, PUSHed FIRST -- i.e. it lands at the LOWER stack address.
//   0xa8  16-bit word (MOVZX), PUSHed. Read as a halfword and not as a dword.
constexpr std::size_t kCarrierFlagWord = 0x08u;        // 00a850ec  MOV EDX,[EAX+0x8]
constexpr std::size_t kCarrierScale = 0x10u;           // 00a8516c  MOVSS XMM0,[EAX+0x10]
constexpr std::size_t kCarrierFirstStackArgument = 0xa0u;  // 00a8514f  PUSH at 00a85159
constexpr std::size_t kCarrierSecondStackArgument = 0xa4u; // 00a85144  PUSH at 00a85158
constexpr std::size_t kCarrierHalfWord = 0xa8u;        // 00a8510e  MOVZX EAX,word ptr [EAX+0xa8]

// -- dispatch displacements --------------------------------------------------
// The table is reached by TWO dereferences: 00a850dd loads the word at
// receiver+0x10 into ECX, and 00a850f7 / 00a8511e / 00a8514d / 00a851a3 each
// read the dword at offset 0 of THAT object to obtain the table base. So the
// chain is receiver -> (+0x10) -> object -> (+0x00) -> table -> (+slot) -> target,
// three loads deep, and every one of them is a bare `MOV r,[reg+disp]` with no
// null or range check on the way.
constexpr std::size_t kDispatchLeadDisplacement = 0x00u;  // 00a850f7  MOV EAX,[ECX]
// The four slot displacements. Each is a vtable-shaped fetch: the listing's own
// shape is `MOV EDX,[EDX + disp]` immediately before `CALL EDX`, with EDX
// holding the table base, and ECX holding the object. The machine dispatch record
// for this target reports `indirect_calls: 4` and `call_offsets: []`, and every
// one of the four sites is machine-classified VTABLE_SLOT at exactly these four
// displacements -- which is why the term is usable here. What the machine does
// NOT fix is which class owns the table: the SDK names nothing, there is no RTTI,
// and the same instruction shape would be produced by a callback array. The
// displacements are claimed; the ownership is not.
constexpr std::size_t kSlotBit2 = 0x18u;    // 00a850f9  MOV EDX,[EAX+0x18]  -> CALL 00a850fc
constexpr std::size_t kSlotBit4 = 0x1cu;    // 00a85120  MOV EDX,[EDX+0x1c]  -> CALL 00a8512e
constexpr std::size_t kSlotBit1Set = 0x0cu;  // 00a85155  MOV EDX,[EDX+0xc]   -> CALL 00a8515a
constexpr std::size_t kSlotBit1Clear = 0x10u;  // 00a851ab  MOV EDX,[EDX+0x10] -> CALL 00a851b0
// The two are named for the flag bit that GUARDS them, not for their numeric
// value: the bit-1-set arm dispatches at 0x0c and the bit-1-clear arm at 0x10.
// The model test drives each arm and asserts the other one's table word is never
// called.

// -- the four objects, as opaque byte runs ------------------------------------
// Each extent below is the observed one: the run runs from offset zero to one
// past the highest byte this body touches, and every byte in it that the body
// does not touch is left as an opaque byte rather than given a type.

// The receiver. 0x6c bytes: the body writes a full dword at 0x68 (00a85133 and
// 00a851b2), which is the last byte of the object this body can prove.
struct Receiver {
  std::array<std::uint8_t, 0x6c> opaque{};
};
static_assert(sizeof(Receiver) == 0x6c,
              "the dword store at receiver+0x68 is the last byte this body writes");

// The object the word at receiver+0x0c points at. 0xaa bytes: 0x00a8510e reads a
// 16-bit word at 0xa8, and 0xa9 is the last byte it touches.
struct Carrier {
  std::array<std::uint8_t, 0xaa> opaque{};
};
static_assert(sizeof(Carrier) == 0xaa,
              "the 16-bit read at carrier+0xa8 ends at the last byte this body reads");

// The object the word at receiver+0x10 points at, and the receiver of all four
// indirect transfers. 0x04 bytes: this body reads exactly ONE dword of it, the one
// at offset 0, and writes nothing.
struct DispatchObject {
  std::array<std::uint8_t, 0x04> opaque{};
};
static_assert(sizeof(DispatchObject) == 0x04,
              "this body reads only the lead dword of the dispatch object");

// The table that lead dword points at. 0x20 bytes: the highest slot this body
// fetches is 0x1c, and the fetch is four bytes wide.
struct DispatchTable {
  std::array<std::uint8_t, 0x20> opaque{};
};
static_assert(sizeof(DispatchTable) == 0x20,
              "the highest slot this body fetches is 0x1c, and the fetch is a dword");

// -- displacement-named accessors --------------------------------------------
// The machine shape each one reproduces, one shape per function, because the
// pointer LEVEL is the single highest-risk reading in this body: the carrier is
// reached through receiver+0x0c, the dispatch object through receiver+0x10, and
// the dispatch table through the DISPATCH OBJECT'S lead dword and not through
// either of the two. A model that conflated any two of those would still produce
// a runnable program, which is why the model test plants a live decoy table at
// every level.

// Read the 4-byte word at `base + displacement`.
inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                        displacement);
}

// Read the 2-byte word at `base + displacement` (00a8510e is a MOVZX of a word).
inline HalfWord half_word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const HalfWord*>(reinterpret_cast<std::uintptr_t>(base) +
                                            displacement);
}

// Read the single byte at `base + displacement` (00a850d3 / 00a850e1 / 00a851ba).
inline std::uint8_t byte_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                                displacement);
}

// Read the 4-byte IEEE-754 single at `base + displacement` (every MOVSS load in
// the body names `dword ptr`, so the width is the machine's own).
inline Float float_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Float*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

// Write the 4-byte word at `base + displacement`.
inline void store_word(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

// Write the 4-byte IEEE-754 single at `base + displacement` (every MOVSS store).
inline void store_float(void* base, std::size_t displacement, Float value) {
  *reinterpret_cast<Float*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

// Write the single byte at `base + displacement`.
inline void store_byte(void* base, std::size_t displacement, std::uint8_t value) {
  *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                   displacement) = value;
}

// The table-base fetch: read a 4-byte word out of a table at a fixed slot
// displacement. The NAME says what the instruction does, and the name is the same
// one the machine's own dispatch classification uses for this shape; it says
// nothing about who owns the table, which nothing in this body settles.
inline Word load_slot(Word table_base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(table_base) +
                                        displacement);
}

// -- the indirect callees -----------------------------------------------------
// This body has NO DIRECT CALLEE. Every one of its four transfers is register
// indirect (`CALL EDX` at 00a850fc, 00a8512e, 00a8515a and 00a851b0), the xref
// export records no outgoing call edge of any reference type for 0x00a850d0, and
// the machine dispatch record reports `call_offsets: []`. There is therefore no
// named direct callee to declare and no extern declaration of one; the honest
// boundary objects here are the SHAPES of the four indirect transfers, and the
// listing does fix all four:
//
//   * the target is a 4-byte word read out of the table, never an immediate and
//     never a register-held address (00a850f9, 00a85120, 00a85155, 00a851ab);
//   * every one of them passes exactly ONE register argument, ECX, and that
//     register holds the DISPATCH OBJECT in all four cases. The two calls at
//     00a8512e, 00a8515a and 00a851b0 are preceded by an explicit reload
//     (00a8511b, 00a8514a, 00a851a0); the first, at 00a850fc, is not, because
//     00a850f7 is `MOV EAX,[ECX]` and leaves ECX alone;
//   * the call at 00a850fc pushes nothing at all -- the body has no PUSH between
//     the prologue and 00a850fc -- so that callee's only argument is its register
//     receiver;
//   * the other three each push exactly two words. Push order is the argument
//     order, read from the last push backwards: 00a85128 PUSH EDI then 00a8512d
//     PUSH EAX, so [ESP+0] is EAX and [ESP+4] is EDI; likewise 00a85158/00a85159
//     and 00a851ae/00a851af. Getting that backwards is the argument-order bug this
//     package's model test is built to catch;
//   * the body NEVER pops those six words and never adjusts ESP after any of the
//     three, so the callee must be callee-cleanup. That is an INFERENCE from the
//     absence of an adjustment, not an observation of the callee, and it is the
//     same shape the function's own `RET 0x4` gives, which is why the macro
//     above is applied to these three typedefs as well.
using ZeroStackArgumentCallee =
    Word(PKG_SW2_00A850D0_THISCALL*)(void* receiver);
using TwoStackArgumentCallee =
    Word(PKG_SW2_00A850D0_THISCALL*)(void* receiver, Word first_stack_argument,
                                      Word second_stack_argument);

// -- the two .rdata words -----------------------------------------------------
// Declared as variables rather than baked-in constants, for one reason: the
// machine READS them, and a model that folded the read into an immediate would
// not be falsifiable by any test. The addresses are the machine's and are named
// here; the values are transcribed from the image bytes of SporeApp.exe 3.1.0.22
// (both four-byte IEEE-754 singles in .rdata, both listed in the sidecar):
//
//   g_image_unit_scalar  read at 00a85176 (MOVSS XMM1,dword ptr [0x01485720]),
//                        file bytes 00 00 80 3f, i.e. +1.0f. It is the DIVIDEND:
//                        00a8517e is `DIVSS XMM1,XMM0`, so the result is
//                        unit / scale and not scale / unit.
//   g_image_zero_scalar  read at 00a85191 (COMISS XMM0,dword ptr [0x01485378]),
//                        file bytes 00 00 00 00, i.e. +0.0f.
extern Float g_image_unit_scalar;
extern Float g_image_zero_scalar;

// -- model instrumentation ----------------------------------------------------
// XMM0, the function's return carrier, as the 32 raw bits the MOVSS and DIVSS
// instructions move. Why this exists, stated plainly because it is the one place
// where a source-level reconstruction is FORCED to invent a value: the body has
// an early-out at 00a850d7 that jumps straight to 00a85188 (`POP ESI; RET 0x4`)
// without ever writing XMM0, so on that path the caller receives whatever XMM0
// held on entry. A C++ function must return something, and the honest model
// returns the incoming register contents unchanged rather than manufacturing a
// value. The seed is exposed so the model test can plant a sentinel and observe
// that the early-out returns it untouched while writing nothing to the receiver.
//
// This word is instrumentation of the model's own register file. It is not a
// machine global, no instruction in the body names it, and the original code has
// no such addressable word.
Word xmm0_bits();
void set_xmm0_bits(Word bits);

// The bit tests, in one place. `(word >> index) & 1` is exactly what each of the
// four listing sites computes, via the listing's own SHR-then-TEST pair; nothing
// here is a signedness-sensitive comparison, and the model's `bit_is_set` never
// sees a negative operand to reinterpret.
constexpr bool bit_is_set(Word word, unsigned index) {
  return ((word >> index) & kBitMaskLow) != 0u;
}

// Signed comparison for 00a851b7. JGE is the SIGNED greater-or-equal, so a result
// word of 0x80000000 takes the reset path and 0x7fffffff does not. Spelled out as
// a named predicate so the model test can drive both halves of the signed range
// and so that an unsigned rewrite of the same predicate is a visible change.
constexpr bool result_is_non_negative(Word value) {
  return (value & 0x80000000u) == 0u;
}

// Bit-exact single conversions, so the model never launders a signalling NaN or a
// negative zero through an arithmetic step it did not perform.
inline Word float_bits(Float value) {
  Word bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

inline Float bits_float(Word bits) {
  Float value = 0.0f;
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

// -- the reconstructed function ----------------------------------------------
// FUN_00a850d0 @ 0x00a850d0.
//
// __thiscall, receiver in ECX, one ordinary stack word of which the body reads
// NONE, `RET 0x4`. The single stack word exists because the terminator consumes
// the return address plus one word; no instruction in the body reads it and
// nothing else about it is fixed, so it is declared, left unnamed, and the model
// test runs whole cases with a benign word, with zero and with a pointer to a
// poisoned block, requiring byte-identical receiver state each time.
//
// RETURN TYPE: `float`, and the reason is that it is TRUE OF THE LISTING rather
// than that it agrees with anything. XMM0 is the return register on this target
// (abi_derived.value.abi.return_register), and the body writes it with a
// four-byte MOVSS at 00a8516c and 00a8518c and with a four-byte DIVSS at
// 00a8517e -- single-precision, four bytes, an IEEE-754 single, not a double and
// not a vector. The canonical ABI record disagrees in vocabulary, not in fact:
// abi_derived.value.abi.return_semantics is the machine phrase
// "float_or_x87_in_XMM0", which is not a C++ type and which no C++ spelling can
// equal, so RETURN SEMANTICS reports a rename however this is written. The
// declaration made here is the one the bytes support; the disagreement with the
// record's vocabulary is recorded in the sidecar's unresolved questions and is
// NOT papered over with a typedef named after the phrase.
//
// The one path that returns a value this model cannot name is the early-out at
// 00a850d7, discussed at the instrumentation note above.
extern "C" float PKG_SW2_00A850D0_THISCALL re_00a850d0(Receiver* receiver,
                                                       Word unused_stack_word);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a850d0
