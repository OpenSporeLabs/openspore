// PKG-SWARM-W1-00F9B7F0 -- VA 0x00f9b7f0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00f9b7f0 @ 0x00f9b7f0, the virtual member
// installed at slot +0x84 of the dispatch table that begins at 0x01490be8.
//
//   * 0x01490c6c -- 0x01490c6f holds the dword 0x00f9b7f0, read straight out of
//     the image, and 0x01490c6c is exactly 0x01490be8 + 0x84. The neighbouring
//     table words read 0x00f967d0 (+0x78), 0x00f9b620 (+0x7c), 0x00faa5c0
//     (+0x80), 0x00f9b7f0 (+0x84), 0x00f96840 (+0x88), 0x00f9fef0 (+0x8c). So
//     the table is a flat run of virtual slots and this body is one of them.
//     Nothing else in this package depends on that fact and no member is named
//     from it: this binary carries no MSVC RTTI, so the table is only a
//     pointer array.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM, because the
// split matters to a reader:
//
//  * The three receiver displacements this body itself shows -- 0x00, 0x28 and
//    0x814 -- are read out of its own 64-instruction listing and are the
//    complete set it reaches:
//      0x00f9b83a MOV EDX,[ESI]                  the receiver's own dispatch word
//      0x00f9b7f6 MOV ECX,[ESI + 0x28]            read, and the gate for the whole body
//      0x00f9b846 MOV EDI,[ESI + 0x28]            re-read for the second dispatch
//      0x00f9b88c MOV ESI,[ESI + 0x28]            re-read for the tail call
//      0x00f9b82b CMP EDI,[ESI + 0x814]           compared against the candidate
//      0x00f9b832 LEA EBX,[ESI + 0x814]           the address handed to 0x00427fd0
//    The body writes NO byte of the receiver on any path. 0x00..0x27,
//    0x29..0x813 and 0x815.. are never touched, so the receiver is an opaque
//    run and every access is a displacement.
//
//  * The 0x14-byte record layout is NOT shown by this body. It is read off the
//    three direct callees that are handed such a record, whose raw bytes were
//    re-read for this package:
//      - 0x0041ea00 (receiver in ECX): reads WORD [this+0x10] and masks it with
//        0x30 (0x0041ea24/0x0041ea28), reads WORD [this+0x12] and compares it
//        with 0x0a and 0x10 (0x0041ea0c..0x0041ea1c), and returns either
//        *(dword*)this (0x0041ea30), this (0x0041ea47), 0 (0x0041ea4c) or the
//        literal 0x015d1164 (0x0041ea58).
//      - 0x00427fd0 (receiver in ECX, one stack word, ends C2 04 00): reads
//        WORD [this+0x10] and masks 0x4 then 0x2 (0x00427fda/0x00427fde,
//        0x00427ff9/0x00427ffd), reads WORD [this+0x12] and compares 0x0a
//        (0x00428005/0x00428009), writes *(dword*)this (0x00428016), writes
//        WORD [this+0x12] = 0x0a (0x00428020) and WORD [this+0x10] = (this+0x10)
//        & 0x2 (0x00428031). It touches nothing at or past +0x14.
//      - 0x0093db80 (receiver in ECX, one stack word read as a byte, ends
//        C2 04 00): TEST BYTE [ESI+0x10],0x4 (0x0093db83), TEST BYTE
//        [ESI+0x10],0x2 (0x0093dba4), and writes WORD [ESI+0x12] = 0
//        (0x0093dbae) and WORD [ESI+0x10] = 0 (0x0093dbb2).
//    Those three bodies touch no byte beyond +0x13, which is what fixes 0x14.
//
//  * The local frame object is 0x18 bytes and is fixed by the machine, not
//    named: `SUB ESP,0x18` at 0x00f9b7f0 and `ADD ESP,0x18` at 0x00f9b8ad are
//    the only two things that give its size, and 0x00f9b807 (`LEA EDX,[ESP+8]`
//    with ESP = entry-0x20) is the first byte of it.
//
//  * ONE OBJECT, NOT TWO, and that is forced by the frame walk rather than by
//    any name. 0x00427fd0 is handed entry-0x14 at 0x00f9b859 `LEA
//    ECX,[ESP+0x14]` with ESP = entry-0x28; 0x0093db80 is handed entry-0x14 at
//    0x00f9b883 with the same displacement, and the +0x14 dispatch's out
//    argument at 0x00f9b86c is entry-0x14 too. All three therefore get the
//    SAME 0x14-byte record, embedded at frame+0x04. The two words this body
//    pre-stores land on entry-0x02 and entry-0x04, which are exactly +(0x12)
//    and +(0x10) of that record, and the guard byte it tests at 0x00f9b87a
//    `TEST BYTE PTR [ESP+0x20],0x4` is entry-0x04, the very flags word it
//    wrote. So the frame is one struct -- a leading dword the +0x24 dispatch
//    publishes, then a 0x14-byte record the rest of the body works on -- and a
//    model that puts the record at frame+0x00, that gives 0x0093db80 a
//    different object from 0x00427fd0, or that reads the guard four bytes below
//    the flags word, is wrong. The model test pins all three.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00f9b7f0 requires an x86-32 target"
#endif

// The two conventions this body actually uses, spelled per toolchain. Both are
// machine facts taken from the callees' own last bytes, not choices:
//
//   PKG_SW1_00F9B7F0_THISCALL  the four __thiscall edges.
//       0x0041ea00  0x0041ea5d MOV ESP,EBP / 0x0041ea5f POP EBP / 0x0041ea60 RET
//                   (C3, no immediate) -- receiver in ECX, no stack words, so
//                   the callee has nothing to pop.
//       0x00427fd0  0x00428051 C2 04 00  (RET 0x4)
//       0x0093db80  0x0093dbb7 C2 04 00  (RET 0x4)
//       the two indirect dispatches at 0x00f9b813 and 0x00f9b878: ECX is live
//                   across both (set at 0x00f9b7f6 and 0x00f9b876 respectively)
//                   and no register argument is named, so the receiver travels
//                   in ECX.
//
//   PKG_SW1_00F9B7F0_CDECL     the two tail callees, both of which end in a bare
//       0x006b1f90  0x006b1fb3 RET after 0x006b1fb2 POP ECX (C3)
//       0x006b4b60  0x006b4cad RET after 0x006b4caa ADD ESP,0x18, inside its own
//                   SEH frame (0x006b4b60 MOV EAX,FS:[0x0] / 0x006b4b66 PUSH
//                   -0x1 / 0x006b4b68 PUSH 0x120e6c2 / 0x006b4b6d PUSH EAX /
//                   0x006b4b6e MOV FS:[0x0],ESP)
//       Neither returns with an immediate, so the CALLER owns the cleanup. The
//       body honours that with ADD ESP,0x4 at 0x00f9b89d and ADD ESP,0x10 at
//       0x00f9b8a7.
#if defined(_MSC_VER)
#define PKG_SW1_00F9B7F0_THISCALL __thiscall
#define PKG_SW1_00F9B7F0_CDECL __cdecl
#else
#define PKG_SW1_00F9B7F0_THISCALL __attribute__((thiscall))
#define PKG_SW1_00F9B7F0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00f9b7f0 {

using Word = std::uint32_t;

// The 0x14-byte record the three callees above are all handed, and an OPAQUE BYTE
// RUN: nothing inside it is named.
//
// WHY NOTHING INSIDE IS NAMED, stated once because the reason is identical for
// every record in this header. The machine-derived receiver record for this VA is
// `bounds_only` (abi.receiver: register ECX, offsets [0, 40, 2068],
// written_through 0), which says where the body was SEEN reaching and says
// nothing about which member is which. No other machine record in this pack
// carries a member name either, so a name here would be an identity claim that
// nothing in this evidence can confirm or refute, and the framework's
// FIELDS/OFFSETS check says so about the source span for exactly this reason. A
// DISPLACEMENT is a location claim and this pack settles those, so every place
// the body reaches is named as a displacement, is annotated with the instruction
// that prints it, and is reached through an accessor rather than through a member.
//
// The SIZE is still fixed here, and by the callees' own bytes rather than by a
// name: all three touch no byte past +0x13 -- 0x0041ea00 reads only +0x10 and
// +0x12, 0x00427fd0 writes only *(dword*)this, +0x10 and +0x12, and 0x0093db80
// tests and writes only +0x10 and +0x12 -- so 0x14 bytes is the whole of what
// this package can show the record is.
struct ValueRecord {
  std::array<std::uint8_t, 0x14> opaque{};
};
static_assert(sizeof(ValueRecord) == 0x14, "0x0041ea00 / 0x00427fd0 / 0x0093db80 touch no byte past +0x13");

// THE THREE DISPLACEMENTS THE CALLEES' OWN LISTINGS NAME. Each is annotated with
// every instruction in this set that prints it. None of them is a member name and
// none claims what the word is for -- only where it is.
//
//   kRecordLeadingDisplacement  0x00  a dword. 0x0041ea30 returns *(dword*)this
//                                      and 0x0041ea47 returns this, which is why
//                                      0x00f9b829 has to LOAD through the returned
//                                      pointer rather than use it; 0x00428016
//                                      writes *(dword*)this; and this body's own
//                                      0x00f9b829 `MOV EDI,[EAX]` reads it with no
//                                      displacement printed at all.
//   kRecordFlagsDisplacement    0x10  a 16-bit word. Bits 0x0002 and 0x0004 are the
//                                      only bits any listing in this set
//                                      establishes: 0x00427fd0 tests bit 0x0004
//                                      and calls 0x0093db80 with the argument 1
//                                      when it is set (0x00427fde/0x00427fe3/
//                                      0x00427fe8), tests bit 0x0002 as part of
//                                      its success condition (0x00427ff9/
//                                      0x00427ffd) and then overwrites the word
//                                      with (word & 0x0002) (0x0042802b/
//                                      0x00428031); 0x0093db80 tests bit 0x0004
//                                      (0x0093db83) and bit 0x0002 (0x0093dba4)
//                                      and, when its byte argument is non-zero
//                                      and bit 0x0002 is clear, zeroes the whole
//                                      word (0x0093dbb2); 0x0041ea00 masks it with
//                                      0x0030 (0x0041ea24/0x0041ea28), so bit
//                                      0x0010 is observed too. THIS BODY touches
//                                      the same word twice: 0x00f9b85d stores 2
//                                      into it and 0x00f9b87a tests its byte
//                                      against 0x04.
//   kRecordTypeDisplacement     0x12  a 16-bit word compared with 0x000a by
//                                      0x0041ea00 (0x0041ea10), by this body
//                                      (0x00f9b81d) and by 0x00427fd0
//                                      (0x00428005/0x00428009), and with 0x0010
//                                      by 0x0041ea00 (0x0041ea1c). 0x00427fd0
//                                      writes 0x000a into it (0x00428020) and
//                                      0x0093db80 zeroes it (0x0093dbae); this
//                                      body writes 0x000a into it at 0x00f9b84e.
constexpr std::size_t kRecordLeadingDisplacement = 0x00;
constexpr std::size_t kRecordFlagsDisplacement = 0x10;
constexpr std::size_t kRecordTypeDisplacement = 0x12;
static_assert(kRecordLeadingDisplacement + sizeof(Word) <= sizeof(ValueRecord),
              "0x00428016 writes a dword at record+0x00, so four bytes exist there");
static_assert(kRecordFlagsDisplacement + 2 <= sizeof(ValueRecord),
              "0x00428031 writes a halfword at record+0x10, so two bytes exist there");
static_assert(kRecordTypeDisplacement + 2 <= sizeof(ValueRecord),
              "0x00428020 writes a halfword at record+0x12, so two bytes exist there");

// The frame, resolved once against the entry ESP. Every stack-relative
// displacement in the body was read off the listing with these values in force;
// the model asserts them (see the model test's frame cases) because a
// reconstruction that silently used a different frame would still compile.
//
//   entry-0x18 .. entry-0x01   the LocalProbe (0x18 bytes, from SUB ESP,0x18)
//   entry-0x1c                 saved ESI           (PUSH ESI  0x00f9b7f3)
//   entry-0x20                 saved EDI           (PUSH EDI  0x00f9b806)
//   entry-0x24                 saved EBX           (PUSH EBX  0x00f9b831)
//   entry-0x28                 the two argument words of the first dispatch,
//                              live only until that callee returns
//                              (PUSH EDX 0x00f9b80b / PUSH 0x3ad556a 0x00f9b80c)
//
// The epilogue is shared by three edges (0x00f9b7fb, 0x00f9b838 and the
// fall-through from 0x00f9b8a7) and restores exactly three words plus the frame
// (POP EBX 0x00f9b8aa / POP EDI 0x00f9b8ab / POP ESI 0x00f9b8ac / ADD ESP,0x18
// 0x00f9b8ad / RET 0x00f9b8b0), so 0x18 + 12 is the frame that BOTH the early
// exit and the slow path must arrive with. That single requirement is what fixes
// the two dispatch cleanups below, and it is checked two further ways: it is
// the only cleanup pair under which every stack-relative address in the listing
// lands on a field of the frame object, and no other assignment of the three
// direct callees' RET immediates closes the frame at all. It is still an
// INFERENCE, because the dispatch targets have no address: see
// unresolved_questions in the sidecar.
constexpr std::size_t kLocalDisplacement = 0x18;
constexpr std::size_t kSavedEsiDisplacement = 0x1c;
constexpr std::size_t kSavedEdiDisplacement = 0x20;
constexpr std::size_t kSavedEbxDisplacement = 0x24;
constexpr std::size_t kFrameTotalDisplacement = 0x24;  // what the epilogue consumes
static_assert(kFrameTotalDisplacement == kLocalDisplacement + 3 * sizeof(Word),
              "0x18 of frame plus three saved registers is what the epilogue drops");

// Net bytes each call removes from the frame, beyond the return address. The
// three direct ones are the callees' own RET immediates, read out of the image.
// The two dispatch ones are then pinned by the frame, and both land on the
// ordinary value for a two-word callee that owns its cleanup, which is the
// check that makes this reading more than a bare arithmetic necessity:
//
//   0x00f9b813  0x28 committed at the call, and 0x00f9b831 adds the fourth word
//               the epilogue pops: 0x28 - x + 4 = 0x24  =>  x = 8
//   0x00f9b878  the block 0x00f9b83a..0x00f9b8a7 pushes 36 bytes and retires 20
//               of them with ADD ESP,0x4 and ADD ESP,0x10, so its five callees
//               must remove 16; 4 + x + 4 + 0 + 0 = 16  =>  x = 8
//
// and the alternatives are not viable: with x = 4 at 0x00f9b878 the frame
// closes numerically but the epilogue's POP EDI and POP ESI would then read the
// words pushed at 0x00f9b831 and 0x00f9b806 shifted by one, so the body would
// not restore its callee-saved registers, and with x = 0 the frame does not
// close at all. The targets are behind a dispatch table read out of memory, so
// no listing of theirs can be consulted; this is the strongest available
// statement and it is still an INFERENCE (see the sidecar).
constexpr int kCleanupDispatch024 = 8;  // 0x00f9b813, two words at 0x00f9b80b/0x00f9b80c
constexpr int kCleanupHelper41ea00 = 0; // 0x00f9b824, no words pushed, callee ends C3
constexpr int kCleanupValueAssign = 4;  // 0x00f9b862, one word, callee ends C2 04 00
constexpr int kCleanupDispatch014 = 8;  // 0x00f9b878, two words at 0x00f9b870/0x00f9b871
constexpr int kCleanupEditorQuery = 4;  // 0x00f9b887, one word, callee ends C2 04 00
constexpr int kCleanupFactoryLookup = 0;  // 0x00f9b898, three words, callee ends C3
constexpr int kCleanupDispatch080 = 0;    // 0x00f9b844, no words pushed

// The one 0x18-byte object this body builds on its own stack frame, and an opaque
// byte run for the reason ValueRecord is one. Its size is 0x18 because
// `SUB ESP,0x18` at 0x00f9b7f0 and `ADD ESP,0x18` at 0x00f9b8ad are the only two
// things that give it, and nothing else.
//
// WHAT IS INSIDE IT IS STATED AS TWO DISPLACEMENTS AND NOT AS MEMBERS. The
// +0x00 dword is LOADED, not addressed: 0x00f9b819 `MOV ECX,[ESP+0x8]` with
// ESP = entry-0x20, i.e. entry-0x18, and 0x00f9b81d then reads WORD [ECX+0x12]
// and 0x00f9b824 hands that same loaded word to 0x0041ea00 as its ECX receiver.
// So it is a POINTER PUBLISHED BY THE +0x24 DISPATCH, and the type test and the
// resolve are two levels below the frame object. The +0x04 region is the 0x14-byte
// record: 0x00427fd0 is handed entry-0x14 at 0x00f9b859, 0x0093db80 the same
// entry-0x14 at 0x00f9b883, and the +0x14 dispatch's out argument entry-0x14 at
// 0x00f9b86c. 4 + 0x14 == 0x18 exactly, which is why the split has no freedom in
// it, and the two pre-stores plus the guard byte land on the two words
// 0x00427fd0's own listing reads (kRecordFlagsDisplacement and
// kRecordTypeDisplacement). The model test plants decoys at the wrong depth and
// at every neighbouring offset to break all of it.
struct LocalProbe {
  std::array<std::uint8_t, 0x18> opaque{};
};
static_assert(sizeof(LocalProbe) == 0x18, "SUB ESP,0x18 / ADD ESP,0x18");

// Where the 0x14-byte record begins inside the frame object. Read out of the
// three stack-relative address computations that hand it out (0x00f9b859,
// 0x00f9b86c, 0x00f9b883) and checked below against kAssignReceiverFrameOffset,
// so it is a derivation and not a second opinion.
constexpr std::size_t kRecordOffsetInsideFrame = 0x04;
static_assert(kRecordOffsetInsideFrame + sizeof(ValueRecord) == sizeof(LocalProbe),
              "0x04 + 0x14 is the whole 0x18 frame object: no third reading exists");

// The frame displacements the listing fixes, derived from the two offsets above
// so the derivation is checked rather than asserted. The frame object starts at
// entry-0x18, so a frame-relative offset d is the entry-ESP displacement 0x18 - d,
// and every row below carries both. The ESP column is the value the walk gives
// at that instruction, which is itself fixed by the cleanup constants further
// down:
//
//   0x00f9b807 LEA EDX,[ESP+0x8],  ESP = entry-0x20 -> entry-0x18: the +0x24
//                                                      dispatch's out argument
//   0x00f9b819 MOV ECX,[ESP+0x8],  ESP = entry-0x20 -> entry-0x18: LOADS the
//                                                      frame's leading dword
//   0x00f9b859 LEA ECX,[ESP+0x14], ESP = entry-0x28 -> entry-0x14: 0x00427fd0
//   0x00f9b85d MOV WORD [ESP+0x24],DX, ESP = entry-0x28 -> entry-0x04: stores 2
//   0x00f9b84e MOV WORD [ESP+0x22],CX, ESP = entry-0x24 -> entry-0x02: stores 0x0a
//   0x00f9b86c LEA ECX,[ESP+0x10], ESP = entry-0x24 -> entry-0x14: the +0x14
//                                                      dispatch's out argument
//   0x00f9b87a TEST BYTE [ESP+0x20],0x4, ESP = entry-0x24 -> entry-0x04: the
//                                                      guard, i.e. record+0x10
//   0x00f9b883 LEA ECX,[ESP+0x14], ESP = entry-0x28 -> entry-0x14: 0x0093db80
constexpr std::size_t kLoadedPointerFrameOffset = 0x00;  // 0x00f9b819 loads this dword
constexpr std::size_t kAssignReceiverFrameOffset = 0x04;  // 0x00427fd0's ECX
constexpr std::size_t kQueryReceiverFrameOffset = 0x04;   // 0x0093db80's ECX
constexpr std::size_t kRefillOutFrameOffset = 0x04;       // 0x00f9b86c, the +0x14 dispatch's out arg
constexpr std::size_t kFlagsStoreFrameOffset = 0x14;      // value 2
constexpr std::size_t kTypeStoreFrameOffset = 0x16;       // value 0x0a
constexpr std::size_t kGuardByteFrameOffset = 0x14;       // the byte tested against 0x04

// The same places as entry-ESP displacements, for the frame note above.
constexpr std::size_t kLoadedPointerEntryOffset = 0x18;
constexpr std::size_t kAssignReceiverEntryOffset = 0x14;
constexpr std::size_t kQueryReceiverEntryOffset = 0x14;
constexpr std::size_t kRefillOutEntryOffset = 0x14;
constexpr std::size_t kFlagsStoreEntryOffset = 0x04;
constexpr std::size_t kTypeStoreEntryOffset = 0x02;
constexpr std::size_t kGuardByteEntryOffset = 0x04;

static_assert(kAssignReceiverFrameOffset == kRecordOffsetInsideFrame,
              "0x00427fd0 receives the frame object + 0x04, not the frame object");
static_assert(kQueryReceiverFrameOffset == kAssignReceiverFrameOffset,
              "0x0093db80 receives the SAME record 0x00427fd0 was handed");
static_assert(kRefillOutFrameOffset == kAssignReceiverFrameOffset,
              "the +0x14 dispatch writes into the record 0x00427fd0 was handed");
static_assert(kLoadedPointerFrameOffset + sizeof(Word) == kRecordOffsetInsideFrame,
              "the published dword ends exactly where the record begins: the frame "
              "object is a leading word and then the record, and nothing else");
static_assert(kFlagsStoreFrameOffset ==
                  kAssignReceiverFrameOffset + kRecordFlagsDisplacement,
              "0x00f9b85d stores 2 at frame+0x14 == record+0x10");
static_assert(kTypeStoreFrameOffset ==
                  kAssignReceiverFrameOffset + kRecordTypeDisplacement,
              "0x00f9b84e stores 0x0a at frame+0x16 == record+0x12");
static_assert(kGuardByteFrameOffset == kFlagsStoreFrameOffset,
              "the guard byte is the very word 0x00f9b85d wrote: record+0x10");

// The same places measured from the RECORD's own base, which is what a caller
// holding the record inside the frame object needs.
constexpr std::size_t kGuardRecordOffset = kGuardByteFrameOffset - kRecordOffsetInsideFrame;
constexpr std::size_t kFlagsStoreRecordOffset = kFlagsStoreFrameOffset - kRecordOffsetInsideFrame;
constexpr std::size_t kTypeStoreRecordOffset = kTypeStoreFrameOffset - kRecordOffsetInsideFrame;
static_assert(kGuardRecordOffset == kRecordFlagsDisplacement,
              "the guard byte is record+0x10, the word 0x0093db80 tests first");
static_assert(kFlagsStoreRecordOffset == kRecordFlagsDisplacement,
              "the 0x0002 store is record+0x10");
static_assert(kTypeStoreRecordOffset == kRecordTypeDisplacement,
              "the 0x0a store is record+0x12");

// And the entry-ESP column, checked against the frame-relative one.
static_assert(kLoadedPointerEntryOffset == kLocalDisplacement - kLoadedPointerFrameOffset,
              "entry displacement of the loaded word");
static_assert(kAssignReceiverEntryOffset == kLocalDisplacement - kAssignReceiverFrameOffset,
              "entry displacement of 0x00427fd0's receiver");
static_assert(kQueryReceiverEntryOffset == kLocalDisplacement - kQueryReceiverFrameOffset,
              "entry displacement of 0x0093db80's receiver");
static_assert(kRefillOutEntryOffset == kLocalDisplacement - kRefillOutFrameOffset,
              "entry displacement of the +0x14 dispatch's out argument");
static_assert(kFlagsStoreEntryOffset == kLocalDisplacement - kFlagsStoreFrameOffset,
              "entry displacement of the 0x02 store");
static_assert(kTypeStoreEntryOffset == kLocalDisplacement - kTypeStoreFrameOffset,
              "entry displacement of the 0x0a store");
static_assert(kGuardByteEntryOffset == kLocalDisplacement - kGuardByteFrameOffset,
              "entry displacement of the guard byte");
static_assert(kFlagsStoreEntryOffset == kLocalDisplacement - kFlagsStoreFrameOffset,
              "entry displacement of the 0x02 store");
static_assert(kTypeStoreEntryOffset == kLocalDisplacement - kTypeStoreFrameOffset,
              "entry displacement of the 0x0a store");
static_assert(kGuardByteEntryOffset == kLocalDisplacement - kGuardByteFrameOffset,
              "entry displacement of the guard byte");
static_assert(kAssignReceiverEntryOffset == kLocalDisplacement - kAssignReceiverFrameOffset,
              "entry displacement of 0x00427fd0's receiver");
static_assert(kQueryReceiverEntryOffset == kLocalDisplacement - kQueryReceiverFrameOffset,
              "entry displacement of 0x0093db80's receiver");

// The receiver. 0x818 bytes, of which this body reads three words and writes
// none. Declared as an opaque run with only the three reached displacements
// named, because the machine-derived receiver record for this VA
// (abi.receiver, receiver.offsets = [0, 40, 2068], register ECX,
// written_through 0) states where the body was seen reaching and not which
// member is which. Calling +0x28 a "model" or a "planet" or +0x814 a "handle"
// would be a story this body's evidence does not carry.
struct alignas(4) Receiver {
  std::array<std::uint8_t, 0x818> opaque{};
};
constexpr std::size_t kReceiverDispatchDisplacement = 0x000;  // 0x00f9b83a MOV EDX,[ESI]
constexpr std::size_t kReceiverObjectDisplacement = 0x028;   // 0x00f9b7f6 / 0x846 / 0x88c
constexpr std::size_t kReceiverWordDisplacement = 0x814;     // 0x00f9b82b / 0x00f9b832
static_assert(kReceiverWordDisplacement + sizeof(Word) == sizeof(Receiver),
              "0x814 + 4 is the last byte the body reads on the receiver");

// The object the receiver holds at +0x28. The body reads exactly one word of it
// -- the one at +0x00 -- and uses that word as a pointer to a dispatch table,
// taking the entry at +0x24 (0x00f9b801/0x00f9b803) and the entry at +0x14
// (0x00f9b867/0x00f9b869). The same two-level shape is used on the receiver
// itself at 0x00f9b83a/0x00f9b83c with the entry at +0x80. No member of either
// object is named.
struct DispatchObject {
  std::array<std::uint8_t, 0x40> opaque{};
};
constexpr std::size_t kDispatchTableDisplacement = 0x00;  // the word that points at the table
constexpr std::size_t kDispatchSlot014 = 0x14;           // 0x00f9b869
constexpr std::size_t kDispatchSlot024 = 0x24;           // 0x00f9b803
constexpr std::size_t kReceiverSlot080 = 0x80;           // 0x00f9b83c

// The immediates this body carries. Each is annotated with the instruction it
// comes from; nothing else in the listing is a constant.
//
//   0x03ad556a  0x00f9b80c PUSH 0x3ad556a and 0x00f9b871 PUSH 0x3ad556a -- the
//               same word is the first stack argument of BOTH dispatches on the
//               object at receiver+0x28.
//   0x031389b5  0x00f9b893 PUSH 0x31389b5 -- the first stack argument of
//               0x006b1f90.
//   0x0a        0x00f9b849 MOV ECX,0xa (stored to record+0x12 at 0x00f9b84e) and
//               0x00f9b81d CMP WORD PTR [ECX+0x12],0xa (the type test).
//   0x02        0x00f9b853 MOV EDX,0x2 (stored to record+0x10 at 0x00f9b85d).
//   0x04        0x00f9b87a TEST BYTE PTR [ESP+0x20],0x4 -- the guard mask.
//   0x00        0x00f9b811 XOR EDI,EDI, 0x00f9b881 PUSH 0x0, 0x00f9b88f
//               PUSH 0x0 and 0x00f9b891 PUSH 0x0.
constexpr Word kPropertyIdA = 0x03ad556a;
constexpr Word kFactoryTagB = 0x031389b5;
constexpr std::uint16_t kTypeCodeTen = 0x000a;
constexpr std::uint16_t kFlagsWordTwo = 0x0002;
constexpr std::uint8_t kGuardMaskFour = 0x04;
constexpr Word kZero = 0x00000000;

// -- the five direct callees ------------------------------------------------
// Each is declared here and defined as an observer by this package's model test.
// Every signature below is fixed by the callee's own bytes, not by any
// decompilation.

// 0x0041ea00, called once at 0x00f9b824. __thiscall, receiver in ECX, no stack
// words, terminator C3 at 0x0041ea60. Returns one of *(dword*)receiver,
// receiver, 0 or the literal 0x015d1164, so the declared return type is a bare
// pointer and NOT the record pointer: 0x00f9b829 `MOV EDI,[EAX]` then
// dereferences whatever comes back, which is a load of a MEMBER, not an address.
extern "C" void* PKG_SW1_00F9B7F0_THISCALL value_resolve_0041ea00(
    ValueRecord* receiver);

// 0x00427fd0, called once at 0x00f9b862. __thiscall, receiver in ECX, one stack
// word, terminator C2 04 00 at 0x00428051. Its own frame reads that word at
// [EBP+0x8] (0x00427fe... 0x00428011) and dereferences it (0x00428014
// `MOV EAX,[EDX]`), so the argument is a POINTER TO A DWORD, not a dword. The
// body forms it with `LEA EBX,[ESI+0x814]` at 0x00f9b832. The destination is
// the frame object at entry-0x14, which is LocalProbe+0x04.
extern "C" ValueRecord* PKG_SW1_00F9B7F0_THISCALL value_assign_00427fd0(
    ValueRecord* destination, const Word* source);

// 0x0093db80, called once at 0x00f9b887 and only under the guard. __thiscall,
// receiver in ECX, one stack word read as a BYTE at [ESP+0x8] after its own
// PUSH ESI (0x0093db9d `CMP BYTE PTR [ESP + 0x8],0x0`), terminator C2 04 00 at
// 0x0093dbb7. The name is the one this target's own record carries for it
// (callees[0].name = editor_query_clear_flags_0093db80). What this body uses it
// for is narrower: the receiver is the same record 0x00427fd0 was handed, and
// the argument is always 0 --
// and with the argument 0 the callee's own clearing half does not run
// (0x0093d9d JZ 0x0093dbb6), so the call has no effect on this path.
extern "C" void PKG_SW1_00F9B7F0_THISCALL editor_query_clear_flags_0093db80(
    ValueRecord* receiver, std::uint8_t argument);

// 0x006b1f90, called once at 0x00f9b898. cdecl: the callee's last two
// instructions are POP ECX (0x006b1fb2) and RET (0x006b1fb3), and the body
// retires four of the twelve bytes it pushed with ADD ESP,0x4 at 0x00f9b89d --
// eight of the three words are therefore left on the stack until 0x00f9b8a7
// drops them, and the declared signature keeps all three words this body
// pushes, in push order. The callee's own 16-instruction body reads none of
// the three: it only touches its own frame and the global at 0x0152fdc4. Its
// return value is a bare dword (a dword at [EAX+0x14], or 0) and this body
// pushes it straight into 0x006b4b60.
extern "C" Word PKG_SW1_00F9B7F0_CDECL factory_lookup_006b1f90(
    Word property_id, Word second, Word third);

// 0x006b4b60, called once at 0x00f9b8a2. cdecl, terminator RET at
// 0x006b4cad, and the body retires the two words itself with ADD ESP,0x10 at
// 0x00f9b8a7. Argument order is fixed by the push order at 0x00f9b8a0/0x00f9b8a1:
// the first argument is the dword 0x006b1f90 returned and the second is the
// object at receiver+0x28, re-read at 0x00f9b88c. Its own body reads stack
// slots one through five, i.e. it expects more arguments than this call site
// supplies -- see unresolved_questions.
extern "C" std::uint8_t PKG_SW1_00F9B7F0_CDECL object_bind_006b4b60(
    Word token, DispatchObject* object);

// -- the three indirect transfers -------------------------------------------
// Typed function pointers rather than bare calls, so that the model test can
// install a decoy for each and so that the register each receiver travels in is
// part of the declared type. None of these has an address: they are read out of
// the tables the two objects carry, at the displacements named above.

// 0x00f9b844: ECX = the receiver, no stack words, return value never read.
using ReceiverSlot080 = void(PKG_SW1_00F9B7F0_THISCALL*)(Receiver* receiver);

// 0x00f9b813: ECX = the object at receiver+0x28, two stack words -- 0x03ad556a
// then &frame_object -- and a byte return that 0x00f9b815 tests. Net cleanup
// 8 (frame-forced, see kCleanupDispatch024).
using DispatchSlot024 = std::uint8_t(PKG_SW1_00F9B7F0_THISCALL*)(
    DispatchObject* object, Word property_id, LocalProbe* out);

// 0x00f9b878: ECX = the object at receiver+0x28, two stack words -- 0x03ad556a
// then &(frame_object+0x04) -- and a return value never read. Net cleanup 4
// (frame-forced, see kCleanupDispatch014).
using DispatchSlot014 = void(PKG_SW1_00F9B7F0_THISCALL*)(
    DispatchObject* object, Word property_id, ValueRecord* out);

// Convenience readers. The only way this body touches the receiver, the object or
// the frame object: a member access would assert an identity the machine evidence
// does not support, and a DISPLACEMENT is all the evidence supports.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}
inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}
inline std::uint16_t* halfword_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint16_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}
inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// An interior ADDRESS, not a member. The three `LEA` forms the listing uses on
// the frame object (0x00f9b807 `LEA EDX,[ESP+0x8]`, 0x00f9b859 and 0x00f9b883
// `LEA ECX,[ESP+0x14]`, 0x00f9b86c `LEA ECX,[ESP+0x10]`) each compute a
// displacement into the frame object and hand the result to a callee, so the
// callee's receiver is the frame object plus a named constant and never a member
// of it.
inline void* interior(void* base, std::size_t displacement) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// The SAME conversion, but from a `Word` the listing LOADED, which is a different
// machine shape and is kept a different one. 0x00f9b819 `MOV ECX,[ESP+0x8]`
// puts a dword in ECX; 0x00f9b81d then reads WORD [ECX+0x12] and 0x00f9b824 hands
// that same dword to 0x0041ea00 as its receiver register. Taking the base as a
// `Word` is what makes the two-level chase two reads in the source: a
// one-level reading cannot be written through this pair by accident, and the
// model test plants a decoy at the wrong depth to prove it.
inline void* interior_of(Word base_word, std::size_t displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(base_word) + displacement);
}
inline std::uint16_t half_through(Word base_word, std::size_t displacement) {
  return *reinterpret_cast<const std::uint16_t*>(
      static_cast<std::uintptr_t>(base_word) + displacement);
}

// FUN_00f9b7f0 @ 0x00f9b7f0, the reconstructed body.
//
// __thiscall, receiver in ECX, no ordinary stack arguments, terminator RET with
// no immediate at 0x00f9b8b0 (byte C3) -- so the callee pops nothing and the
// caller owns the cleanup, which for a zero-argument callee is the same as a
// `RET 0x0`. The receiver is aliased into ESI at 0x00f9b7f4 and every receiver
// access in the body goes through that alias, which is why the machine-derived
// receiver record names ECX.
//
// The name embeds the eight-hex target VA because reconstruction_knowledge's
// validator resolves the span from the symbol. Ghidra's live record for this VA
// carries ghidra_function.signature "undefined FUN_00f9b7f0(void)",
// ghidra_calling_convention null and return_type "undefined"; none of those is
// used here. The convention and the argument count are derived from the body
// itself, and the return type is an INFERENCE stated as such in the sidecar.
extern "C" void PKG_SW1_00F9B7F0_THISCALL re_00f9b7f0(Receiver* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00f9b7f0
