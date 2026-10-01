// PKG-SWARM-W2-00A98200 -- VA 0x00a98200
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00a98200 @ 0x00a98200.
//
// THE COMPLETE BODY: 110 instructions, 0x00a98200..0x00a98336 inclusive
// (ghidra_function.body_start 0x00a98200, body_end 0x00a98338, size_bytes 313;
// the committed record's body_end is the LAST BYTE of the RET 0x4, so the
// terminator at 0x00a98336 is inside the body and no instruction is missing).
// abi_derived.parse = {declared_count 110, unparsed 0, degraded false}, so the
// machine parse consumed the listing in full and the count matches it.
//
//   00a98200  SUB ESP,0x50
//   00a98203  PUSH EDI
//   00a98204  MOV EDI,ECX
//   00a98206  CMP byte ptr [EDI + 0x10],0x0
//   00a9820a  JZ 0x00a98332
//   00a98210  PUSH EBP
//   00a98211  PUSH ESI
//   00a98212  MOV byte ptr [EDI + 0x10],0x0
//   00a98216  CALL 0x00883860
//   00a9821b  MOV ESI,EAX
//   00a9821d  XOR EBP,EBP
//   00a9821f  CMP ESI,EBP
//   00a98221  JZ 0x00a98330
//   00a98227  MOV EAX,dword ptr [EDI + 0xc]
//   00a9822a  TEST byte ptr [EAX + 0x8],0x1
//   00a9822e  JZ 0x00a9824c
//   00a98230  MOV EDX,dword ptr [ESI]
//   00a98232  MOV EDX,dword ptr [EDX + 0x14]
//   00a98235  PUSH EBP
//   00a98236  LEA EAX,[ESP + 0x10]
//   00a9823a  PUSH EAX
//   00a9823b  PUSH 0xe7a8472
//   00a98240  MOV ECX,ESI
//   00a98242  MOV dword ptr [ESP + 0x20],EBP
//   00a98246  MOV dword ptr [ESP + 0x18],EBP
//   00a9824a  CALL EDX
//   00a9824c  MOV EAX,dword ptr [EDI + 0xc]
//   00a9824f  MOV ECX,dword ptr [EAX + 0x8]
//   00a98252  SHR ECX,0x1
//   00a98254  TEST CL,0x1
//   00a98257  JZ 0x00a98279
//   00a98259  MOV EDX,dword ptr [ESI]
//   00a9825b  MOV EDX,dword ptr [EDX + 0x14]
//   00a9825e  PUSH EBP
//   00a9825f  LEA EAX,[ESP + 0x10]
//   00a98263  PUSH EAX
//   00a98264  PUSH 0xe7a8472
//   00a98269  MOV ECX,ESI
//   00a9826b  MOV dword ptr [ESP + 0x20],EBP
//   00a9826f  MOV dword ptr [ESP + 0x18],0x1
//   00a98277  CALL EDX
//   00a98279  MOV EAX,dword ptr [EDI + 0xc]
//   00a9827c  MOV ECX,dword ptr [EAX + 0x8]
//   00a9827f  SHR ECX,0x2
//   00a98282  TEST CL,0x1
//   00a98285  JZ 0x00a982a3
//   00a98287  MOV EDX,dword ptr [ESI]
//   00a98289  MOV EDX,dword ptr [EDX + 0x14]
//   00a9828c  PUSH EBP
//   00a9828d  LEA EAX,[ESP + 0x10]
//   00a98291  PUSH EAX
//   00a98292  PUSH 0xe7a8474
//   00a98297  MOV ECX,ESI
//   00a98299  MOV dword ptr [ESP + 0x20],EBP
//   00a9829d  MOV dword ptr [ESP + 0x18],EBP
//   00a982a1  CALL EDX
//   00a982a3  MOV EAX,dword ptr [EDI + 0xc]
//   00a982a6  MOV ECX,dword ptr [EAX + 0x8]
//   00a982a9  SHR ECX,0x4
//   00a982ac  TEST CL,0x1
//   00a982af  JZ 0x00a98330
//   00a982b1  MOV dword ptr [ESP + 0x54],EBP
//   00a982b5  MOV EDX,dword ptr [EAX + 0x8]
//   00a982b8  SHR EDX,0x5
//   00a982bb  TEST DL,0x1
//   00a982be  JZ 0x00a982c7
//   00a982c0  MOV ECX,dword ptr [EAX + 0x10]
//   00a982c3  MOV dword ptr [ESP + 0x1c],ECX
//   00a982c7  MOV EDX,dword ptr [EAX + 0x8]
//   00a982ca  SHR EDX,0x6
//   00a982cd  TEST DL,0x1
//   00a982d0  JZ 0x00a982d9
//   00a982d2  MOV ECX,dword ptr [EAX + 0x14]
//   00a982d5  MOV dword ptr [ESP + 0x24],ECX
//   00a982d9  MOV EDX,dword ptr [EAX + 0x8]
//   00a982dc  SHR EDX,0x7
//   00a982df  TEST DL,0x1
//   00a982e2  JZ 0x00a982eb
//   00a982e4  MOV ECX,dword ptr [EAX + 0x18]
//   00a982e7  MOV dword ptr [ESP + 0x2c],ECX
//   00a982eb  MOV EDX,dword ptr [EAX + 0x8]
//   00a982ee  SHR EDX,0x8
//   00a982f1  TEST DL,0x1
//   00a982f4  JZ 0x00a982fd
//   00a982f6  MOV ECX,dword ptr [EAX + 0x1c]
//   00a982f9  MOV dword ptr [ESP + 0x34],ECX
//   00a982fd  MOV EDX,dword ptr [EAX + 0x8]
//   00a98300  SHR EDX,0x9
//   00a98303  TEST DL,0x1
//   00a98306  JZ 0x00a9830f
//   00a98308  MOV ECX,dword ptr [EAX + 0x20]
//   00a9830b  MOV dword ptr [ESP + 0x3c],ECX
//   00a9830f  MOV ECX,dword ptr [EDI + 0x50]
//   00a98312  MOV dword ptr [ESP + 0x4c],ECX
//   00a98316  LEA EDX,[EDI + 0x18]
//   00a98319  MOV dword ptr [ESP + 0x44],EDX
//   00a9831d  MOV EDX,dword ptr [ESI]
//   00a9831f  MOV EAX,dword ptr [EAX + 0xc]
//   00a98322  MOV EDX,dword ptr [EDX + 0x14]
//   00a98325  PUSH EBP
//   00a98326  LEA ECX,[ESP + 0x20]
//   00a9832a  PUSH ECX
//   00a9832b  PUSH EAX
//   00a9832c  MOV ECX,ESI
//   00a9832e  CALL EDX
//   00a98330  POP ESI
//   00a98331  POP EBP
//   00a98332  POP EDI
//   00a98333  ADD ESP,0x50
//   00a98336  RET 0x4
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM. Three groups,
// kept apart because they have three different strengths:
//
//  (1) EVERY displacement and immediate the body itself shows is machine
//      evidence and is listed with the instruction it came from. Nothing in this
//      header is a second listing's inference unless it says so.
//
//  (2) NOTHING IS NAMED. abi_derived.receiver reports
//      {bounds_only: true, offsets: [12, 16, 80], register: ECX, shape: R-ALIAS},
//      and `bounds_only` is the record's own statement that the enumeration is
//      open -- it says where the body was seen reaching and nothing about which
//      member is which. So every object below is an OPAQUE BYTE RUN and every
//      access is made through a displacement-named accessor
//      (byte_at / word_at) with the displacement held in a named constexpr that
//      the body file static_asserts against the instruction it came from. No
//      struct member name appears anywhere in the reconstructed body, and none
//      is asserted here. The three receiver displacements the record enumerates
//      (0x0c, 0x10, 0x50) are exactly the three the listing shows, plus 0x18
//      which the record did not observe but 0x00a98316 (`LEA EDX,[EDI + 0x18]`)
//      shows; that disagreement is the record's, not the listing's, and the
//      listing governs.
//
//  (3) The two objects reached THROUGH a pointer -- the record at receiver+0x0c
//      and the service returned by 0x00883860 -- are typed only as opaque runs
//      of the exact observed extent. Their extent is a lower bound, not a size:
//      the body reads the record's dwords at +0x08..+0x20 and the service's
//      leading word at +0x00, and nothing beyond. The record is NOT given a
//      "flags word + five payload words" layout even though that is what the
//      displacements look like, because a layout is a claim the machine record
//      cannot make.
//
// THE FRAME, and the one place this header has something unusual to say.
//
// The prologue is `SUB ESP,0x50` / `PUSH EDI` / `PUSH EBP` / `PUSH ESI`, so this
// package's frame base is ESP as it stands AFTER those three pushes. Call it
// FRAME-0. Entry ESP is 0 in the walk, so FRAME-0 = entry-0x5c, and:
//
//   FRAME-0+0x00  the saved ESI      (PUSH ESI, 0x00a98211)
//   FRAME-0+0x04  the saved EBP      (PUSH EBP, 0x00a98210)
//   FRAME-0+0x08  the saved EDI      (PUSH EDI, 0x00a98203)
//   FRAME-0+0x0c  the PAIR, dword 0  (0x00a98246, and its address is taken by
//                                     0x00a98236 LEA EAX,[ESP + 0x10] with
//                                     ESP = FRAME-0-4)
//   FRAME-0+0x14  the PAIR, dword 1  (0x00a98242 MOV [ESP+0x20],EBP with
//                                     ESP = FRAME-0-0xc)
//   FRAME-0+0x1c  the LIST, dword 0  (0x00a982c3, and its address is taken by
//                                     0x00a98326 LEA ECX,[ESP + 0x20] with
//                                     ESP = FRAME-0-4)
//   FRAME-0+0x24  the LIST, dword 1  (0x00a982d5)
//   FRAME-0+0x2c  the LIST, dword 2  (0x00a982e7)
//   FRAME-0+0x34  the LIST, dword 3  (0x00a982f9)
//   FRAME-0+0x3c  the LIST, dword 4  (0x00a9830b)
//   FRAME-0+0x44  the LIST, dword 5  (0x00a98319) -- the receiver's own +0x18
//   FRAME-0+0x4c  the LIST, dword 6  (0x00a98312) -- the receiver's own +0x50
//   FRAME-0+0x54  the LIST, dword 7  (0x00a982b1 MOV [ESP+0x54],EBP) -- literal 0
//
// Every one of those ten is the listing's own `[ESP + n]` operand, taken against
// the ESP value in force at that instruction; that is why the constants below are
// the listing's spellings and not a re-derived base. The stride is 8 for the
// pair's two dwords as well as for the list's eight, so the run reads as ONE
// ten-dword sequence rather than as two objects, and the four bytes between each
// pair of dwords is named by no instruction in the body. Whether the frame is
// really one object of eight-byte-aligned members, or two objects the compiler
// happened to lay out that way, is not settled by these bytes; the model uses the
// single run, because the single run is what the displacements say.
//
// TWO FACTS ABOUT THIS FRAME THAT ARE EASY TO GET WRONG, and both are asserted
// by the model test rather than left as commentary:
//
//  (A) LIST dwords 0..4 ARE NOT INITIALISED BY THIS BODY. Each of them is written
//      only inside `if (flag bit N)`, and 0x00a982b1 zeroes dword 7 before any of
//      them. So on a run where bits 5..9 are clear, the callee at 0x00a9832e is
//      handed five dwords of whatever the frame already held. A reconstruction
//      that zero-fills its list is a DIFFERENT function; the model therefore
//      seeds the frame from an instrumentation word (frame_poison_word) and
//      carries the poison through untouched, and the test drives a run with the
//      bits clear and asserts the poison reaches the callee.
//
//  (B) LIST dword 7 SITS FOUR BYTES ABOVE THE RESERVED WINDOW. `SUB ESP,0x50`
//      reserves FRAME-0+0x00..+0x4f, and 0x00a982b1 writes FRAME-0+0x54, i.e.
//      0x04 past the top of the reservation. That is a property of the bytes, not
//      a modelling choice, and the model's frame is 0x58 bytes wide because the
//      body really does name an address 4 bytes outside the window it reserved.
//      No saved register is clobbered by it: FRAME-0+0x54 is entry-0x08, which is
//      inside the SUB-reserved region and is not any of the three pushed slots
//      (entry-0x04 / -0x08 / -0x0c hold the saved EDI / EBP / ESI).
//
// THE DISPATCH SHAPE. Four sites, all `CALL EDX` (FF D2), and all four fetch the
// target with the same two-level shape: `MOV EDX,[ESI]` then `MOV EDX,[EDX +
// 0x14]`. So the target is the word 0x14 bytes into whatever the service
// object's leading word points at. 0x14 / 4 == slot index 5, which is arithmetic
// and is asserted by nothing. abi_derived.dispatch agrees on the count
// (indirect_calls 4, call_offsets [], vtable_shaped_loads 0).
//
// The repository's own site classifier agrees on the shape: run over this listing
// it returns VTABLE_SLOT with slot displacement 0x14 for all four sites. Read
// that as what it is, though -- the classifier proves a TWO-LEVEL TABLE READ and
// the displacement it reads the slot at, and it does not check where the base
// register's word came from, so it would return the same answer if the leading
// word of the service object were a callback holder rather than a vtable pointer.
// Nothing in this listing identifies the table, and nothing here names one: the
// helper is called load_table_word for the shape the bytes show and for nothing
// more.
//
// FUN_00883860, the one direct callee. Its own five bytes are read from the
// image: `A1 CC 14 65 01` / `C3` -- `MOV EAX,dword ptr [0x016514cc]` / `RET`. So
// it is a cdecl function that takes NO argument of any kind, reads one global
// word, and returns it. Two consequences the model reproduces exactly: the call
// carries no register argument (the ECX that still holds the receiver at
// 0x00a98216 is a stale value, not an argument, and the callee reads no
// register), and the service pointer's only source in the whole program is that
// global. The body never writes the global, so the null test at 0x00a9821f is a
// test of the global's content.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00a98200 requires an x86-32 target"
#endif

// The two conventions this body needs, spelled per toolchain. GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC.
//
//   PKG_SWARM_W2_00A98200_THISCALL  for re_00a98200 itself. Fixed by its own
//     bytes: 0x00a98204 copies ECX into EDI and the body addresses the receiver
//     only through that alias, and 0x00a98336 is `RET 0x4`, which pops the
//     return address plus one word -- callee-owned cleanup, so not cdecl and not
//     fastcall, and a hidden receiver in a register, so not plain cdecl.
//
//   PKG_SWARM_W2_00A98200_CDECL  for the one direct callee, 0x00883860. Fixed by
//     the callee's OWN last byte: it ends in a bare `C3` (read from the image at
//     0x00883864), which is a caller-side cleanup and therefore cdecl, and it
//     pushes nothing itself and takes no register argument.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00A98200_THISCALL __thiscall
#define PKG_SWARM_W2_00A98200_CDECL __cdecl
#else
#define PKG_SWARM_W2_00A98200_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W2_00A98200_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00a98200 {

using Word = std::uint32_t;
using Byte = std::uint8_t;

// -- the receiver's displacements, each tied to the instruction that fixes it --
//
// The receiver record is {bounds_only: true, offsets: [0x0c, 0x10, 0x50],
// register: ECX, shape: R-ALIAS}. Three of the four displacements below are in
// that set; 0x18 is not, and the listing shows it (0x00a98316) where the record
// did not observe it. That is the record being open, which is what bounds_only
// declares, and the listing governs.
constexpr std::size_t kReceiverRecordPointerOffset = 0x0c;  // 0x00a98227
constexpr std::size_t kReceiverLatchOffset = 0x10;           // 0x00a98206, 0x00a98212
constexpr std::size_t kReceiverInteriorOffset = 0x18;        // 0x00a98316 (LEA)
constexpr std::size_t kReceiverPayloadOffset = 0x50;         // 0x00a9830f
// The observed lower bound on the receiver's extent: the highest dword the body
// names is the one at +0x50, which ends at +0x53. Nothing below asserts a size.
constexpr std::size_t kReceiverSpanBytes = 0x54;

// -- the record's displacements, each tied to the instruction that fixes it ----
constexpr std::size_t kRecordFlagsOffset = 0x08;    // 0x00a9822a (byte), 0x00a9824f (dword)
constexpr std::size_t kRecordCallKeyOffset = 0x0c;  // 0x00a9831f
constexpr std::size_t kRecordValue0Offset = 0x10;   // 0x00a982c0 -> LIST dword 0
constexpr std::size_t kRecordValue1Offset = 0x14;   // 0x00a982d2 -> LIST dword 1
constexpr std::size_t kRecordValue2Offset = 0x18;   // 0x00a982e4 -> LIST dword 2
constexpr std::size_t kRecordValue3Offset = 0x1c;   // 0x00a982f6 -> LIST dword 3
constexpr std::size_t kRecordValue4Offset = 0x20;   // 0x00a98308 -> LIST dword 4
constexpr std::size_t kRecordSpanBytes = 0x24;      // 0x20 + 4

// The flag word's bits, as the listing separates them. 0x00a9822a tests bit 0 of
// the BYTE at record+0x08; 0x00a9824f and every later read take the DWORD. On
// x86-32 little-endian those name the same low byte, so the two spellings test
// the same bit 0; the model keeps the byte read at bit 0 and the dword read
// everywhere else, exactly as the listing does.
//
// BIT 3 IS NEVER TESTED. No instruction in the body shifts the flag word by 0x3
// and no instruction tests it, so a run with bit 3 set and every other bit clear
// makes no indirect call at all. The shift list below is the whole of the set the
// listing uses and 0x3 is absent from it on purpose.
constexpr Word kFlagBit0Mask = 0x1;    // TEST byte ptr [EAX + 0x8],0x1 @ 0x00a9822a
constexpr Word kFlagProbeMask = 0x1;   // TEST CL,0x1 / TEST DL,0x1 @ 0x00a98254, 0xbb, 0xcd, 0xdf, 0xf1, 0x03
constexpr Word kFlagBit1Shift = 0x1;   // SHR ECX,0x1 @ 0x00a98252 -> LIST call, key 0xe7a8472, PAIR 0
constexpr Word kFlagBit2Shift = 0x2;   // SHR ECX,0x2 @ 0x00a9827f -> call, key 0xe7a8474
constexpr Word kFlagBit4Shift = 0x4;   // SHR ECX,0x4 @ 0x00a982a9 -> the whole LIST call
constexpr Word kFlagBit5Shift = 0x5;   // SHR EDX,0x5 @ 0x00a982b8 -> LIST dword 0
constexpr Word kFlagBit6Shift = 0x6;   // SHR EDX,0x6 @ 0x00a982ca -> LIST dword 1
constexpr Word kFlagBit7Shift = 0x7;   // SHR EDX,0x7 @ 0x00a982dc -> LIST dword 2
constexpr Word kFlagBit8Shift = 0x8;   // SHR EDX,0x8 @ 0x00a982eb -> LIST dword 3
constexpr Word kFlagBit9Shift = 0x9;   // SHR EDX,0x9 @ 0x00a98300 -> LIST dword 4

// The two property identifiers this body pushes. Both are pushed as the FIRST
// stack argument of an indirect call; neither is an address, and neither is
// present anywhere else in the body.
constexpr Word kKeyFlagOffA = 0xe7a8472;  // PUSH @ 0x00a9823b and 0x00a98264
constexpr Word kKeyFlagOffB = 0xe7a8474;  // PUSH @ 0x00a98292

// The one literal stored into a frame word rather than pushed: 0x00a9826f writes
// it into the PAIR's dword 0 and nothing else ever stores a non-zero there.
constexpr Word kPairFlagOn = 0x1;  // MOV dword ptr [ESP + 0x18],0x1 @ 0x00a9826f

// -- the service object's displacements ---------------------------------------
constexpr std::size_t kServiceLeadingWordOffset = 0x00;  // MOV EDX,[ESI] @ 0x00a98230, 0x00a98259, 0x00a98287, 0x00a9831d
constexpr std::size_t kServiceSlotDisplacement = 0x14;   // MOV EDX,[EDX + 0x14] @ 0x00a98232, 0x00a9825b, 0x00a98289, 0x00a98322
// The displacement divided by the 4-byte slot width. Arithmetic only, asserted by
// nothing: named so a reader counting slots in a table need not redo the divide.
constexpr std::size_t kServiceSlotIndex = kServiceSlotDisplacement / 4;  // 5
// The service object's observed lower bound: the body reads its leading word and
// nothing else on it.
constexpr std::size_t kServiceSpanBytes = 0x04;

// -- the frame ---------------------------------------------------------------
// The base is ESP as it stands after the prologue's three pushes; see the header
// note. Every literal below IS a `[ESP + n]` operand the listing writes.
constexpr std::size_t kFrameReservedBytes = 0x50;  // SUB ESP,0x50 @ 0x00a98200
constexpr std::size_t kListWord0Offset = 0x1c;      // MOV dword ptr [ESP + 0x1c],ECX @ 0x00a982c3
constexpr std::size_t kListWord1Offset = 0x24;      // MOV dword ptr [ESP + 0x24],ECX @ 0x00a982d5
constexpr std::size_t kListWord2Offset = 0x2c;      // MOV dword ptr [ESP + 0x2c],ECX @ 0x00a982e7
constexpr std::size_t kListWord3Offset = 0x34;      // MOV dword ptr [ESP + 0x34],ECX @ 0x00a982f9
constexpr std::size_t kListWord4Offset = 0x3c;      // MOV dword ptr [ESP + 0x3c],ECX @ 0x00a9830b
constexpr std::size_t kListWord5Offset = 0x44;      // MOV dword ptr [ESP + 0x44],EDX @ 0x00a98319
constexpr std::size_t kListWord6Offset = 0x4c;      // MOV dword ptr [ESP + 0x4c],ECX @ 0x00a98312
constexpr std::size_t kListWord7Offset = 0x54;      // MOV dword ptr [ESP + 0x54],EBP @ 0x00a982b1
// The list's dwords are 8 bytes apart, and the pair's are too: 0x0c then 0x14.
// So the frame is ONE run of ten dwords on a single 8-byte stride, starting at
// +0x0c, and the four-byte gap between each pair of dwords is never named by any
// instruction in the body. The stride is an identity over the two list constants
// above, so there is exactly one place it is stated.
constexpr std::size_t kFrameStride = kListWord1Offset - kListWord0Offset;  // 8
// The pair: its first dword's address is what 0x00a98236/0x00a9825f/0x00a9828d
// compute, and its second dword is what 0x00a98242/0x00a9826b/0x00a98299 write.
constexpr std::size_t kPairBaseOffset = 0x0c;
constexpr std::size_t kPairSecondWordOffset = kPairBaseOffset + kFrameStride;  // 0x14
// The list: its first dword's address is what 0x00a98326 computes, which is two
// strides above the pair's.
constexpr std::size_t kListBaseOffset = kPairBaseOffset + 2 * kFrameStride;  // 0x1c
constexpr std::size_t kListWordCount = 8;
constexpr std::size_t kPairWordCount = 2;
// The model's frame width: 0x58, so that kListWord7Offset + 4 is inside it. The
// prologue reserved 0x50, so the last dword genuinely sits 4 bytes past the
// reservation (see the header note, item B).
constexpr std::size_t kFrameByteCount = 0x58;

// -- the objects -------------------------------------------------------------
// Every object is an opaque byte run of the extent this body was observed
// reaching. No member is named anywhere: the machine receiver record is
// bounds_only and carries no member names, so a name would be a claim no record
// in this pack can make. The alignment is stated so the displacement-named
// accessors below are aligned dword accesses, as the listing's are.
struct alignas(4) Receiver {
  std::array<Byte, kReceiverSpanBytes> opaque_00_53{};
};
struct alignas(4) Record {
  std::array<Byte, kRecordSpanBytes> opaque_00_23{};
};
struct alignas(4) ServiceObject {
  std::array<Byte, kServiceSpanBytes> opaque_00_03{};
};

// The two frame objects, named for WHERE they live and for nothing else. The
// PAIR is two dwords; the LIST is eight dwords at an 8-byte stride. Neither
// object's meaning is established by any record here: the listing shows the
// callee receiving their addresses and the body writing the words, and nothing
// says what the words mean.
struct PropertyPair {
  Word dword[kPairWordCount];
};
struct PropertyList {
  Word dword[kListWordCount];
};

// -- displacement-named accessors --------------------------------------------
// One machine shape each, spelled once. `base` is an address; `offset` is a
// displacement the listing wrote. No accessor takes or names a member.
inline Byte byte_at(const void* base, std::size_t offset) {
  return *reinterpret_cast<const Byte*>(reinterpret_cast<std::uintptr_t>(base) + offset);
}
inline Byte& mutable_byte_at(void* base, std::size_t offset) {
  return *reinterpret_cast<Byte*>(reinterpret_cast<std::uintptr_t>(base) + offset);
}
inline Word word_at(const void* base, std::size_t offset) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + offset);
}
inline Word& mutable_word_at(void* base, std::size_t offset) {
  return *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + offset);
}
// The address `offset` bytes into `base`: what `LEA` computes, and what the body
// pushes as the second argument of all four indirect calls.
inline void* address_at(void* base, std::size_t offset) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(base) + offset);
}
// The two-level table fetch the listing performs four times
// (`MOV EDX,[ESI]` then `MOV EDX,[EDX + 0x14]`). `table_word` is a REGISTER
// VALUE the machine is treating as an address, so it is taken as a Word.
//
// NOT NAMED `vtable`. The shape is a two-level table read and the displacement it
// reads is 0x14, which is what the repo's own site classifier reports for all
// four sites -- but that classifier does not check where the base register's word
// came from, so it would report the same shape if the service object's leading
// word were a callback holder instead of a vtable pointer. Nothing in this listing
// identifies the table, and this header does not claim to. The helper says only
// what the bytes say.
inline Word load_table_word(Word table_word, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(table_word) +
                                        displacement);
}

// -- the indirect callee -----------------------------------------------------
// Four sites, one shape: a 4-byte target read out of a table, then a call with
// ECX carrying the SERVICE object and exactly three stack words pushed right to
// left -- the key, the address of a frame object, and a literal zero (EBP, which
// 0x00a9821d zeroed and which nothing after it writes). The return value is never
// read: no instruction between 0x00a9824a and 0x00a9832e reads EAX, and the
// epilogue (POP ESI; POP EBP; POP EDI; ADD ESP,0x50; RET 0x4) does not touch it.
using TableWordCall = void(PKG_SWARM_W2_00A98200_THISCALL*)(ServiceObject* service,
                                                             Word key,
                                                             void* properties,
                                                             Word tail);

inline void invoke_table_word(Word target_word, ServiceObject* service, Word key,
                              void* properties, Word tail) {
  reinterpret_cast<TableWordCall>(reinterpret_cast<std::uintptr_t>(target_word))(service,
                                                                                key,
                                                                                properties,
                                                                                tail);
}

// -- the one direct callee ---------------------------------------------------
// 0x00883860. Its own five bytes, read from the image at that address, are
// `A1 CC 14 65 01` / `C3`: MOV EAX,dword ptr [0x016514cc] / RET. It takes no
// argument -- neither a stack word (the body pushes nothing before the call) nor
// a register one (its own first instruction reads a global) -- and it returns the
// global's content unchanged. The body uses that value for nothing but a null
// test (0x00a9821f) and then, if non-null, as the object whose leading word is
// the table base for the four indirect calls.
//
// The name carries the 8-hex target address so the repository's callee
// comparison can bind it to the xref export's single out-edge (0x00883860,
// reference_type direct-call, callsite 0x00a98216).
extern "C" ServiceObject* PKG_SWARM_W2_00A98200_CDECL openspore_acquire_service_00883860();

// -- model instrumentation ---------------------------------------------------
// The frame's prior content, and WHY this word exists.
//
// 0x00a982b1..0x00a98319 write LIST dwords 7, 6, 5 unconditionally and dwords 0..4
// only inside a flag test, so on a run where bits 5..9 are clear the callee at
// 0x00a9832e is handed five dwords this body never wrote. The machine leaves
// them as they were; a model with a plain local array would leave them as
// whatever the C++ runtime happened to put there, which is not a statement
// anyone can check.
//
// So the model seeds its frame from this one word, and nothing else about it is
// claimed. It is instrumentation of the MODEL's own frame, not a machine global:
// the original code has no addressable word for it, no instruction in the body
// names it, and the value in it is free. The model test drives the clear-bits run
// and asserts the poison reaches the callee unchanged, and separately asserts
// that a set bit replaces it.
Word frame_poison_word();
void set_frame_poison_word(Word poison);

// -- the reconstructed body --------------------------------------------------
// re_00a98200 @ 0x00a98200.
//
// __thiscall, hidden receiver in ECX (aliased into EDI at 0x00a98204 and never
// moved back), and exactly ONE ordinary stack word, consumed by the callee at
// 0x00a98336 (`RET 0x4`). That word is never read: abi_derived.stack_arguments
// records one slot at entry_ESP+0x4 with observed=false and source=ret_immediate,
// and no instruction in the 110 names entry_ESP+0x4. It is declared here and
// left unnamed, so the parameter count the terminator fixes is not quietly
// dropped.
//
// RETURN TYPE IS void, and the reason is the one the listing gives rather than
// the one a name would give. The three exits are 0x00a98332 (reached when the
// receiver's +0x10 byte is already zero -- EAX untouched by this body on that
// path, so whatever the caller had), 0x00a98330 (reached when the service is
// null -- EAX holds the service word the null test just read) and the fall-through
// (EAX holds the last indirect callee's return, which the body never reads). No
// path loads EAX with a value meant for the caller, and the epilogue's POP ESI /
// POP EBP / POP EDI / ADD ESP / RET does not touch EAX. Ghidra's own decompilation
// of the same listing agrees, opening `void __fastcall FUN_00a98200(int param_1)`
// and ending in a bare `return;`.
//
// The canonical machine record disagrees, and the disagreement is recorded rather
// than papered over: abi.value.return_semantics is the phrase
// "unclassified_in_EAX" and abi_derived.return.register_class is
// "aggregate_unknown". That is a machine-vocabulary label for "the bytes leave
// something in EAX and its width is not decidable", not a C++ type, and no C++
// declaration can be string-equal to it. The sidecar states the same and keeps
// the machine phrase in a field of its own.
extern "C" void PKG_SWARM_W2_00A98200_THISCALL re_00a98200(Receiver* receiver,
                                                          Word unused_stack_word);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a98200
