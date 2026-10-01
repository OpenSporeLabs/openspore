// PKG-SWARM-W1-00641490 -- VA 0x00641490
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00641490 @ 0x00641490.
//
// The complete body is 30 instructions in four basic blocks, 0x00641490..0x006414d6
// inclusive, 71 bytes:
//
//   00641490  SUB ESP,0x8
//   00641493  PUSH ESI
//   00641494  MOV ESI,ECX
//   00641496  LEA EAX,[ESI + 0x4]
//   00641499  PUSH EAX
//   0064149a  CALL 0x00552300
//   0064149f  ADD ESP,0x4
//   006414a2  CMP EAX,0x2
//   006414a5  JNZ 0x006414d0
//   006414a7  MOV EDX,dword ptr [ESI]
//   006414a9  MOV EDX,dword ptr [EDX + 0x90]
//   006414af  LEA EAX,[ESP + 0x4]
//   006414b3  PUSH EAX
//   006414b4  MOV ECX,ESI
//   006414b6  CALL EDX
//   006414b8  TEST AL,AL
//   006414ba  JZ 0x006414d0
//   006414bc  MOV EAX,dword ptr [ESP + 0x4]
//   006414c0  AND EAX,dword ptr [ESP + 0x8]
//   006414c4  CMP EAX,-0x1
//   006414c7  JZ 0x006414d0
//   006414c9  MOV AL,0x1
//   006414cb  POP ESI
//   006414cc  ADD ESP,0x8
//   006414cf  RET
//   006414d0  XOR AL,AL
//   006414d2  POP ESI
//   006414d3  ADD ESP,0x8
//   006414d6  RET
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the
// committed listing and the machine do not agree about the length of this body:
//
//  * The committed Ghidra record for this VA carries 25 instructions,
//    body_start 0x00641490, body_end 0x006414cf, body_span_bytes 64. It STOPS AT
//    THE FIRST RET, one byte before the block at 0x006414d0 that all three
//    conditional branches in the body target. objdump over the image bytes
//    (`objdump -D -b binary -m i386 -M intel --adjust-vma=0x400c00
//    --start-address=0x641490 --stop-address=0x6414e0`) reproduces those 25
//    instructions byte for byte at the same addresses and then shows four more:
//    006414d0 XOR AL,AL / 006414d2 POP ESI / 006414d3 ADD ESP,0x8 /
//    006414d6 RET, followed by INT3 padding at 0x006414d7. The live decompilation
//    of this VA merges that block too (its last statement is
//    `return uVar1 & 0xffffff00;`, the merged form of the XOR). So the body under
//    reconstruction is the 30-instruction one above and NOT the 25-instruction
//    slice, and every branch target in it is 0x006414d0. This is also why
//    CONTROL FLOW cannot pass for this target: the three branch targets fall one
//    byte past the span the committed listing bounds, and that span is read from
//    the machine, not from this source.
//
//  * The dispatch word is at receiver+0x00. 0x006414a7 `MOV EDX,dword ptr [ESI]`
//    is the body's only read through the receiver alias and it has no
//    displacement, so it is the entry receiver's own leading word and not a member
//    at any other offset.
//
//  * The address handed to 0x00552300 is receiver+0x04. 0x00641496
//    `LEA EAX,[ESI + 0x4]` forms it and 0x00641499 pushes it; the body forms no
//    other address from the receiver and reads no other receiver word.
//
//  * The slot displacement is 0x90, i.e. dword index 36. 0x006414a9
//    `MOV EDX,dword ptr [EDX + 0x90]` reads it out of the word 0x006414a7 loaded,
//    and 0x006414b6 `CALL EDX` transfers through the register that read produced.
//    That is the canonical two-level shape: object word -> table -> slot -> CALL.
//
//  * The 8-byte frame pair is at entry-8 and entry-4. Resolved once against the
//    entry ESP: `SUB ESP,0x8` and `PUSH ESI` put ESP at entry-12, so 0x006414af
//    `LEA EAX,[ESP + 0x4]` is entry-8, and after the slot call returns
//    (callee-owned cleanup) ESP is back at entry-12, so 0x006414bc `MOV
//    EAX,[ESP + 0x4]` is entry-8 and 0x006414c0 `AND EAX,[ESP + 0x8]` is entry-4.
//    Both reads therefore land inside the eight bytes the prologue reserved, which
//    is what fixes the pair's extent at 8 and its two words at pair+0 and pair+4.
//    The frame then balances: POP ESI plus ADD ESP,0x8 returns ESP to its entry
//    value on BOTH exits, and the terminator is a bare RET with no immediate, so
//    the function takes no ordinary stack argument at all.
//
//  * The two status words compared against the constant are the pair's own two
//    words and they are combined with a bitwise AND before the comparison:
//    0x006414c0 AND then 0x006414c4 `CMP EAX,-0x1`. AND is all-ones exactly when
//    BOTH operands are all-ones, so the test rejects the pair only when both
//    words are 0xffffffff. 0x006417d0 -- the function this body dispatches to in
//    the table run at 0x013ff648 -- makes the same test on the same pair with two
//    separate compares (`CMP DWORD PTR [EAX],0xffffffff` / `CMP DWORD PTR
//    [EAX+0x4],0xffffffff`), which is a second, independent witness that the two
//    words are a pair and that all-ones in both means "absent".
//
//  * What the body writes is exactly one byte of the return register on each exit:
//    0x006414c9 `MOV AL,0x1` and 0x006414d0 `XOR AL,AL`. Both are 8-bit
//    operations, so the low byte is the whole of the value the body produces and
//    the upper three bytes of EAX are dead on both paths (on the true path they
//    carry bits 8..31 of the AND result, on the false paths whatever the last
//    thing to run in EAX left there). The record's return_semantics is the
//    register-class label "integral_in_EAX" and no record narrows it to a width;
//    see unresolved_questions in the sidecar.
//
//  * No member is named anywhere in this header. The receiver is a 0x10-byte
//    opaque run, and the reason that bound and not another is a fact about two
//    different bodies: this body reaches receiver+0x00 and forms receiver+0x04,
//    and 0x00552300 -- read from its own bytes, where 0x00552318 `MOV
//    EAX,[EBP+0x8]` / 0x0055231b `MOV ECX,[EAX]` / 0x00552320 `MOV
//    EDX,[EAX+0x4]` / 0x00552326 `MOV EAX,[EAX+0x8]` -- dereferences the pointer
//    this body hands it and reads three dwords at its +0, +4 and +8. Its argument
//    IS receiver+0x04, so the three dwords it reads are receiver+0x04, +0x08 and
//    +0x0c, and 0x10 is the end of the run. Naming those three words would be a
//    claim about what they are for, which neither listing makes.
//
//  * The dispatch table is NOT given a size or a layout. 0x90 is the highest
//    displacement any record shows this body reading, and the byte before the
//    table at 0x013ff648 in the image is a float constant (0x3f000000), so where
//    the table's slot 0 begins is not established either. The table is therefore
//    carried as an address, and the only thing said about it anywhere is the one
//    displacement the instruction stream reads.
//
// WHAT THE SLOT DISPLACEMENT IS CALLED. The xref export records this body at six
// data addresses and the index associates the VA with thirteen vtable ids. Reading
// the image at those addresses settles three distinct things and refutes three
// others, and none of it is used as a slot-index claim:
//
//   0x013ff648  the run of code pointers at this address contains 0x00641490 at
//               +0x80 and 0x006417d0 at +0x90. The xref from 0x013ff6c8 is
//               0x013ff648+0x80, i.e. the slot holding this body, so that
//               address is a slot entry of the run and not an arbitrary dword.
//   0x01489090  and 0x014893b0  carry the same two values at the same two
//               offsets, so three tables agree.
//   0x01462764  and 0x0147cbbc  carry 0x00641490 at +0x74 and 0x006417d0 at
//               +0x84 -- the same 0x10 spacing, four bytes lower. One fixed
//               displacement cannot be +0x80 in one table and +0x74 in another,
//               so the two groups are either secondary tables in a multiple-
//               inheritance layout or the record's table starts are off by four
//               bytes. Which of the two is NOT established here and no slot INDEX
//               is claimed for this body in any case: this record has no MSVC
//               RTTI (no complete-object locator precedes the run) and the byte
//               before 0x013ff648 is a float, so no index 0 can be located.
//   0x013ff6ac, 0x014627bc, 0x0147ca30, 0x0147ca70, 0x0147cc14, 0x014890f4
//               contain float constants, ASCII text or a different pointer run at
//               the offsets the record implies. They are recorded here so a later
//               reader does not re-derive them, and nothing in this model rests
//               on any of them.
//
//   What IS claimed, because it is read out of the instruction stream and nothing
//   else: the body dispatches the table word it finds at receiver+0x00, at slot
//   displacement 0x90, and in the three tables that agree the entry at that
//   displacement is 0x006417d0. The body itself never names that address -- the
//   target is a run-time value in EDX -- so the model calls through the loaded
//   pointer and the model test's observer stands in for 0x006417d0.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00641490 requires an x86-32 target"
#endif

// The two conventions below are spelled per toolchain, and both are fixed by
// instruction bytes rather than chosen:
//
//   PKG_SWARM_W1_00641490_THISCALL  this body and the slot it dispatches to.
//     0x00641490 takes its receiver in ECX (0x00641494 MOV ESI,ECX, then every
//     receiver access through ESI), saves ESI across the whole body and returns
//     with a bare RET, so it takes no ordinary stack argument. 0x006417d0, the
//     function the table run at 0x013ff648 holds at displacement 0x90, ends
//     `C2 04 00` (RET 0x4) after writing its one argument's two words -- so it is
//     thiscall with the receiver in ECX and the callee owning the cleanup, which
//     is why 0x006414b6 CALL EDX is followed by no ADD ESP and the two reads at
//     0x006414bc/0x006414c0 are at ESP+4 and ESP+8 rather than ESP+8 and ESP+0xc.
//   PKG_SWARM_W1_00641490_CDECL  0x00552300, whose last three bytes are
//     `8B E5 5D C3` (MOV ESP,EBP; POP EBP; RET) with no immediate: it returns
//     without touching ESP, and 0x0064149f drops its one word with ADD ESP,0x4.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00641490_THISCALL __thiscall
#define PKG_SWARM_W1_00641490_CDECL __cdecl
#else
#define PKG_SWARM_W1_00641490_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_00641490_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00641490 {

using Word = std::uint32_t;

// The 8-byte pair the body reserves with SUB ESP,0x8 and hands to the slot it
// dispatches to, then reads back and ANDs. Two words, at the pair's own +0 and
// +4 -- 0x006414af forms the address, 0x006414bc and 0x006414c0 read the two
// words, and 0x006417d0 writes exactly `[ECX]` and `[ECX+0x4]` on the path where
// it returns non-zero. Nothing says what the two words MEASURE, so they are named
// for their displacements and nothing else; this is a second object from the
// receiver and it is never read through one.
struct DisplacementRange {
  Word field_00;  // the pair's first word: 0x006414bc reads it at ESP+4
  Word field_04;  // the pair's second word: 0x006414c0 reads it at ESP+8
};
static_assert(sizeof(DisplacementRange) == 8, "SUB ESP,0x8 reserves the pair's eight bytes");
static_assert(offsetof(DisplacementRange, field_04) == 4, "the second word is at the pair's +4");

// The receiver. 0x00..0x03 is the dispatch word this body reads at 0x006414a7;
// 0x04..0x0f is the three-dword run 0x00552300 dereferences when this body hands it
// the address formed at 0x00641496. No member is named for any of it: the
// machine-derived receiver record for this VA carries offsets [0] and
// bounds_only true, i.e. it states where the body was seen reaching and not which
// member is which, and calling a word a name, a handle or a type tag would be a
// member story this body's evidence does not carry. The 0x10 bound is the extent
// observed across the two bodies named above and is not a claim that the object
// ends there.
struct alignas(4) SporepediaAssetReceiver {
  std::array<std::uint8_t, 0x10> opaque_00{};  // 0x00..0x0f
};
static_assert(sizeof(SporepediaAssetReceiver) == 0x10,
              "0x00552300 reads the argument's +0, +4 and +8, and the argument is receiver+0x04");

// The signature of the function the body dispatches to. Every part of it is a
// machine fact and none of it is a name: the receiver in ECX is 0x006414b4
// `MOV ECX,ESI`; the single argument is the pair's address, pushed at 0x006414b3
// and popped by the callee (0x006417d0 ends `C2 04 00`); and the return value is
// examined as its low byte only, 0x006414b8 `TEST AL,AL`. The return type is
// declared as the byte the body actually reads and writes rather than as a C++
// `bool`, because the machine fixes the width it touches and not the source-level
// spelling -- see the sidecar's unresolved_questions.
#if defined(_MSC_VER)
using SlotTarget = std::uint8_t(__thiscall*)(SporepediaAssetReceiver* receiver,
                                            DisplacementRange* range);
#else
using SlotTarget = std::uint8_t(__attribute__((thiscall)) *)(SporepediaAssetReceiver* receiver,
                                                            DisplacementRange* range);
#endif

// The displacements and constants this body fixes, as named values. Every entry
// below cites the instruction it was read from in the reconstruction's comments;
// the numbers themselves come from the listing reproduced at the top of this
// header and from nothing else.

// kReceiverDispatchDisplacement: 0x006414a7 `MOV EDX,dword ptr [ESI]`, no
// displacement on the receiver alias.
constexpr std::size_t kReceiverDispatchDisplacement = 0x0;

// kReceiverAssetFieldDisplacement: 0x00641496 `LEA EAX,[ESI + 0x4]`, the address
// pushed at 0x00641499 for 0x00552300. It is an address formed from the receiver
// and not a read of one.
constexpr std::size_t kReceiverAssetFieldDisplacement = 0x4;

// kStatusComparedValue: 0x006414a2 `CMP EAX,0x2`, the single constant the body's
// one direct call is compared against. 0x00552300's own listing returns 0x0
// (0x0055243e XOR EAX,EAX), 0x1 (0x00552400), 0x2 (0x0055241f) or the word at
// [EBP-0x30] (0x005523ec), so the value this body wants is one of at least four
// and the body tests no other.
constexpr Word kStatusComparedValue = 0x2;

// kDispatchSlotDisplacement: 0x006414a9 `MOV EDX,dword ptr [EDX + 0x90]`, the
// slot the transfer at 0x006414b6 goes through. Expressed as a byte displacement
// and, for a reviewer, as the dword index it implies.
constexpr std::size_t kDispatchSlotDisplacement = 0x90;
constexpr std::size_t kDispatchSlotIndex = kDispatchSlotDisplacement / sizeof(Word);
static_assert(kDispatchSlotDisplacement == kDispatchSlotIndex * sizeof(Word),
              "the slot displacement is a whole number of dword slots");

// kPairFirstWordDisplacement and kPairSecondWordDisplacement: the pair's own
// offsets, from 0x006414bc (ESP+4, taken with ESP at entry-12, so entry-8) and
// 0x006414c0 (ESP+8, so entry-4). Both land inside the eight bytes reserved at
// 0x00641490.
constexpr std::size_t kPairFirstWordDisplacement = 0x0;
constexpr std::size_t kPairSecondWordDisplacement = 0x4;

// kPairSize: 0x00641490 `SUB ESP,0x8`, and the extent of the object the slot
// writes (0x006417d0 writes [ECX] and [ECX+0x4] and touches nothing between or
// beyond them).
constexpr std::size_t kPairSize = 0x8;

// kSentinelRejected: 0x006414c4 `CMP EAX,-0x1`, compared against the AND of the
// pair's two words and read as a full 32-bit equality. This is the all-ones word,
// and AND produces it exactly when both words are all-ones.
constexpr Word kSentinelRejected = 0xffffffffu;

// The two return values, from the two 8-bit stores: 0x006414c9 `MOV AL,0x1` and
// 0x006414d0 `XOR AL,AL`. Nothing else about EAX is claimed on either path.
constexpr std::uint8_t kTrue = 0x1;
constexpr std::uint8_t kFalse = 0x0;

// The only way the body under reconstruction touches any object: a dword at a
// named displacement, or the address of one. A member access would assert an
// identity the machine-derived receiver record cannot corroborate, so the model
// reaches everything through these three helpers.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                          displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// The dword at a displacement, read as an address. This is the shape of both
// loads the body makes: 0x006414a7 reads the receiver's leading word as a table
// and 0x006414a9 reads that table's slot as a transfer target. Two separate
// dereferences, and the model test drives the case where only one of them is done.
inline std::uintptr_t word_value_at(const void* base, std::size_t displacement) {
  return static_cast<std::uintptr_t>(*word_at(base, displacement));
}

static_assert(kPairFirstWordDisplacement + sizeof(Word) == kPairSecondWordDisplacement,
              "the two pair words are adjacent");
static_assert(kPairSecondWordDisplacement + sizeof(Word) == kPairSize,
              "the second word ends the eight bytes the prologue reserved");
static_assert(kReceiverAssetFieldDisplacement < sizeof(SporepediaAssetReceiver),
              "the address handed to 0x00552300 is inside the observed receiver extent");
static_assert(kDispatchSlotDisplacement >= kDispatchSlotIndex * sizeof(Word),
              "the slot is at or after the dword index it implies");

// -- the one direct callee --------------------------------------------------
// Declared here and defined nowhere in this package: the model test defines it as
// an observer. The signature is fixed by the callee's own bytes.
//
// 0x00552300, called at 0x0064149a. cdecl: its terminator is
// `8B E5 5D C3` (MOV ESP,EBP; POP EBP; RET) with no immediate, and this body drops
// the one word itself at 0x0064149f with ADD ESP,0x4. Its single parameter is a
// POINTER -- 0x00552318 MOV EAX,[EBP+0x8] followed by 0x0055231b
// MOV ECX,[EAX] -- and it reads three dwords through it at +0, +4 and +8. This
// body hands it the address receiver+0x04 (0x00641496), never the receiver and
// never the pair. Its return value is one of 0x0, 0x1, 0x2 or the word at
// [EBP-0x30] (0x00552343, 0x0055241a, 0x00552439, 0x005523ec), and this body
// compares it against 0x2 and nothing else.
extern "C" Word PKG_SWARM_W1_00641490_CDECL sporepedia_asset_status_00552300(
    const void* asset_field);

// FUN_00641490 @ 0x00641490.
//
// __thiscall, receiver in ECX, NO ordinary stack argument. The terminator is a
// bare RET (0x006414cf and 0x006414d6, both `C3`), the prologue reserves eight
// bytes and saves ESI, and both exits pop ESI and add the eight bytes back, so
// ESP lands on its entry value with no argument word consumed. The machine ABI
// record agrees on the convention (`__thiscall`, confidence INFERRED, verdict
// ABI_INFERRED, cleanup bytes 0 side caller) and reports parameter_count 0.
//
// The return value is the low byte of EAX, and only the low byte: 0x006414c9
// writes 0x01 there on the surviving path and 0x006414d0 writes 0x00 there on
// every failing path, both with 8-bit instructions. The declared type is
// therefore std::uint8_t. The record's return_semantics is the register-class
// label "integral_in_EAX" with type null, which does not fix a width; the machine
// fixes the width the body touches and this signature declares that.
extern "C" std::uint8_t PKG_SWARM_W1_00641490_THISCALL re_00641490(
    SporepediaAssetReceiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641490
