// PKG-SWARM-W1-00F9B7F0 -- VA 0x00f9b7f0
// FUN_00f9b7f0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body: 64 instructions, 0x00f9b7f0..0x00f9b8b0 inclusive
// (ghidra_function.body_start 0x00f9b7f0, body_end 0x00f9b8b0, size 193). The
// listing was re-read out of the image for this package rather than taken on
// trust -- the 193 bytes at 0x00f9b7f0 were re-exported and each instruction
// boundary, branch target, call target and displacement was checked against it
// -- because the frame walk below does not close under any reading of the
// dispatches, and a wrong boundary would have hidden that.
//
//   00f9b7f0  SUB ESP,0x18
//   00f9b7f3  PUSH ESI
//   00f9b7f4  MOV ESI,ECX
//   00f9b7f6  MOV ECX,dword ptr [ESI + 0x28]
//   00f9b7f9  TEST ECX,ECX
//   00f9b7fb  JZ 0x00f9b8ac
//   00f9b801  MOV EAX,dword ptr [ECX]
//   00f9b803  MOV EAX,dword ptr [EAX + 0x24]
//   00f9b806  PUSH EDI
//   00f9b807  LEA EDX,[ESP + 0x8]
//   00f9b80b  PUSH EDX
//   00f9b80c  PUSH 0x3ad556a
//   00f9b811  XOR EDI,EDI
//   00f9b813  CALL EAX
//   00f9b815  TEST AL,AL
//   00f9b817  JZ 0x00f9b82b
//   00f9b819  MOV ECX,dword ptr [ESP + 0x8]
//   00f9b81d  CMP word ptr [ECX + 0x12],0xa
//   00f9b822  JNZ 0x00f9b82b
//   00f9b824  CALL 0x0041ea00
//   00f9b829  MOV EDI,dword ptr [EAX]
//   00f9b82b  CMP EDI,dword ptr [ESI + 0x814]
//   00f9b831  PUSH EBX
//   00f9b832  LEA EBX,[ESI + 0x814]
//   00f9b838  JZ 0x00f9b8aa
//   00f9b83a  MOV EDX,dword ptr [ESI]
//   00f9b83c  MOV EAX,dword ptr [EDX + 0x80]
//   00f9b842  MOV ECX,ESI
//   00f9b844  CALL EAX
//   00f9b846  MOV EDI,dword ptr [ESI + 0x28]
//   00f9b849  MOV ECX,0xa
//   00f9b84e  MOV word ptr [ESP + 0x22],CX
//   00f9b853  MOV EDX,0x2
//   00f9b858  PUSH EBX
//   00f9b859  LEA ECX,[ESP + 0x14]
//   00f9b85d  MOV word ptr [ESP + 0x24],DX
//   00f9b862  CALL 0x00427fd0
//   00f9b867  MOV EAX,dword ptr [EDI]
//   00f9b869  MOV EDX,dword ptr [EAX + 0x14]
//   00f9b86c  LEA ECX,[ESP + 0x10]
//   00f9b870  PUSH ECX
//   00f9b871  PUSH 0x3ad556a
//   00f9b876  MOV ECX,EDI
//   00f9b878  CALL EDX
//   00f9b87a  TEST byte ptr [ESP + 0x20],0x4
//   00f9b87f  JZ 0x00f9b88c
//   00f9b881  PUSH 0x0
//   00f9b883  LEA ECX,[ESP + 0x14]
//   00f9b887  CALL 0x0093db80
//   00f9b88c  MOV ESI,dword ptr [ESI + 0x28]
//   00f9b88f  PUSH 0x0
//   00f9b891  PUSH 0x0
//   00f9b893  PUSH 0x31389b5
//   00f9b898  CALL 0x006b1f90
//   00f9b89d  ADD ESP,0x4
//   00f9b8a0  PUSH EAX
//   00f9b8a1  PUSH ESI
//   00f9b8a2  CALL 0x006b4b60
//   00f9b8a7  ADD ESP,0x10
//   00f9b8aa  POP EBX
//   00f9b8ab  POP EDI
//   00f9b8ac  POP ESI
//   00f9b8ad  ADD ESP,0x18
//   00f9b8b0  RET
//
// FRAME.  The prologue commits 0x18 (SUB ESP,0x18) plus one word (PUSH ESI);
// the epilogue at 0x00f9b8ac..0x00f9b8b0 gives one word back (POP ESI) and
// drops 0x18 (ADD ESP,0x18), so the entry edge that jumps straight to
// 0x00f9b8ac balances at 0x1c. The other two edges arrive at 0x00f9b8aa, which
// pops three words, so they must arrive at 0x24. Three cleanups are read
// straight out of the callees' own last bytes and are facts, not choices:
//
//   0x0041ea00  0x0041ea5d MOV ESP,EBP / 0x0041ea5f POP EBP / 0x0041ea60 RET
//               (C3)                                       -> removes 0
//   0x00427fd0  0x00428051 C2 04 00                        -> removes 4
//   0x0093db80  0x0093dbb7 C2 04 00                        -> removes 4
//   0x006b1f90  0x006b1fb2 POP ECX / 0x006b1fb3 RET (C3)   -> removes 0
//   0x006b4b60  0x006b4caa ADD ESP,0x18 / 0x006b4cad RET   -> removes 0
//
// which leaves the two indirect dispatches to account for the rest. Both are
// pinned at 8, and by two independent arguments each:
//
//   0x00f9b813  the call is reached with 0x28 committed and 0x00f9b831 adds the
//               fourth word the epilogue pops, so 0x28 - x + 4 = 0x24 gives
//               x = 8. 8 is also the ordinary value for a two-argument callee
//               that owns its cleanup, which is what ECX being live across the
//               call already suggests.
//   0x00f9b878  the block 0x00f9b83a..0x00f9b8a7 pushes 36 bytes and retires 20
//               of them itself (ADD ESP,0x4 and ADD ESP,0x10), so its five
//               callees must remove 16; 4 + x + 4 + 0 + 0 = 16 gives x = 8.
//
// The alternatives are not viable, which is what makes this more than a bare
// arithmetic necessity. With 4 at 0x00f9b878 the frame would close numerically
// but the epilogue's POP EDI and POP ESI would read the words pushed at
// 0x00f9b831 and 0x00f9b806 shifted by one, so the body would not restore its
// callee-saved registers. With 0 it does not close at all. And 8 is the only
// assignment under which every stack-relative address in the listing lands on a
// field of the frame object: with 4, 0x00f9b87a would test entry-0x08, four
// bytes below the flags word 0x00f9b85d wrote, and 0x0093db80 would receive the
// frame object rather than the record 0x00427fd0 was handed. The dispatch
// targets are behind a table read out of memory, so no listing of theirs can be
// consulted; this is the strongest statement available and it is still an
// INFERENCE, recorded as such in the sidecar.
//
// WHAT THE BODY DOES, in the order the listing does it:
//
//   1. Gate on the object the receiver holds at +0x28; a null object returns
//      without touching anything else (0x00f9b7f6..0x00f9b7fb).
//   2. Ask that object, through the table its first word points at, the entry at
//      +0x24, for property 0x03ad556a, writing a 0x18-byte answer into the
//      frame (0x00f9b801..0x00f9b813). A zero byte answer means "no".
//   3. If the answer came back non-zero, load the frame's LEADING word and test
//      the halfword at +0x12 of THAT for 0x0a (0x00f9b819..0x00f9b822). This
//      is the one place where a two-level read happens and the model's most
//      fragile shape.
//   4. On a match, hand the same loaded word to 0x0041ea00 and load the dword
//      the callee returns (0x00f9b824..0x00f9b829) -- a member read, not an
//      address, because 0x0041ea00's own listing returns one of
//      *(dword*)this / this / 0 / 0x015d1164.
//   5. If that dword equals the receiver's own word at +0x814, return (0x00f9b82b
//      ..0x00f9b838). Otherwise continue.
//   6. Call the receiver's own table entry at +0x80 with no arguments
//      (0x00f9b83a..0x00f9b844).
//   7. Pre-load the record at frame+0x04 with type 0x0a and flags 0x0002
//      (0x00f9b849..0x00f9b85d) and then call 0x00427fd0 on it with the
//      ADDRESS of the receiver's word at +0x814 (0x00f9b858..0x00f9b862). The
//      pre-load is what lets the callee's own success condition
//      (0x00427ffd AND ECX,0x2 with 0x00428009 CMP EAX,0xa) be satisfied; its
//      other arm would call 0x0093dd80, a callee of 0x00427fd0 that this body
//      never reaches.
//   8. Ask the object at +0x28 again, through the entry at +0x14, for the same
//      property, this time writing into frame+0x04 (0x00f9b846..0x00f9b878).
//   9. If the byte at frame+0x10 has bit 0x04, call 0x0093db80 with the frame
//      object itself and the argument 0 (0x00f9b87a..0x00f9b887). The callee's
//      own first act is the same test on the same object (0x0093db83), and with
//      the argument 0 its clearing half does not run (0x0093d9d JZ).
//  10. Look the tag 0x031389b5 up with 0x006b1f90 and bind the result to the
//      object at +0x28 through 0x006b4b60 (0x00f9b88c..0x00f9b8a2).
//
// NOT MODELLED: the two calls' return values that nothing reads (the +0x80
// entry's EAX and 0x006b4b60's AL), the three saved registers, the four
// argument words the two cdecl calls leave behind, and the identity of the
// +0x24 / +0x14 / +0x80 table entries.

#include "sw1_00f9b7f0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00f9b7f0 {

// Table-shaped reads. The listing reaches both objects through a pointer to a
// table of entry addresses -- `MOV EAX,[ECX]` then `MOV EAX,[EAX+0x24]` on the
// object at receiver+0x28 (0x00f9b801/0x00f9b803), and the same pair on the
// receiver itself (0x00f9b83a/0x00f9b83c). Nothing in the listing reads a member
// of either object except that leading word, so nothing here names one.
namespace {

template <typename Fn>
Fn table_entry(const void* object, std::size_t displacement) {
  const auto* table = reinterpret_cast<const std::uint8_t*>(
      *word_at(const_cast<void*>(object), kDispatchTableDisplacement));
  return reinterpret_cast<Fn>(*word_at(table, displacement));
}

// THE DISPLACEMENT AND IMMEDIATE CONSTANTS, each pinned to the instruction that
// produces it. These are assertions, not documentation: a header value edited away
// from the instruction it was read from breaks the build, and every message names
// that instruction.
//
// They sit HERE, outside the body, on purpose. The machine-derived receiver record
// for this VA is `bounds_only` -- it says where the body was seen reaching and
// nothing about which member is which, and no machine record in this pack carries
// a member name -- so nothing here or in the body names a member, and every place
// the body reaches is a displacement reached through an accessor. Keeping the
// pins out of the body also keeps the body free of hexadecimal literals, so every
// number it uses is a named constant and the reader can trace each one here.

// -- the frame object's own two regions, from the LEA and MOV forms that address
// them (see the header for the entry-ESP column of each row).
static_assert(kLoadedPointerFrameOffset == 0x00,
              "00f9b819 MOV ECX,[ESP+0x8] LOADS the frame object's leading dword");
static_assert(kRecordOffsetInsideFrame == 0x04,
              "00f9b859 LEA ECX,[ESP+0x14] and 00f9b883 LEA ECX,[ESP+0x14] hand the "
              "record to 0x00427fd0 and 0x0093db80");
static_assert(kAssignReceiverFrameOffset == kRecordOffsetInsideFrame,
              "00f9b859 LEA ECX,[ESP+0x14] is 0x00427fd0's ECX");
static_assert(kQueryReceiverFrameOffset == kRecordOffsetInsideFrame,
              "00f9b883 LEA ECX,[ESP+0x14] is 0x0093db80's ECX");
static_assert(kRefillOutFrameOffset == kRecordOffsetInsideFrame,
              "00f9b86c LEA ECX,[ESP+0x10] is the +0x14 dispatch's out argument");
static_assert(kFlagsStoreFrameOffset == 0x14,
              "00f9b85d MOV WORD [ESP+0x24],DX stores 2 at entry-0x04 = frame+0x14");
static_assert(kGuardByteFrameOffset == kFlagsStoreFrameOffset,
              "00f9b87a TEST BYTE [ESP+0x20],0x4 tests entry-0x04: the very word 00f9b85d wrote");
static_assert(kTypeStoreFrameOffset == 0x16,
              "00f9b84e MOV WORD [ESP+0x22],CX stores 0x0a at entry-0x02 = frame+0x16");
static_assert(kLocalDisplacement == 0x18,
              "00f9b7f0 SUB ESP,0x18 and 00f9b8ad ADD ESP,0x18 are the whole frame object");

// -- the record's own three displacements. NOT from this body: the first two are
// printed by the three callees' own listings and the third by this body and by
// two of them. Each message names every instruction in this set that prints it.
static_assert(kRecordLeadingDisplacement == 0x00,
              "00f9b829 MOV EDI,[EAX] reads the leading dword with no displacement "
              "printed; 0041ea30 and 0041ea47 return it, 00428016 writes it");
static_assert(kRecordFlagsDisplacement == 0x10,
              "00427fde/00427ffd/00428031 and 0093db83/0093dba4/0093dbb2 and "
              "0041ea28 all name record+0x10; 00f9b85d stores 2 into it and 00f9b87a "
              "tests its byte against 4");
static_assert(kRecordTypeDisplacement == 0x12,
              "0041ea10/0041ea1c and 00428005/00428009/00428020 and 0093dbae name "
              "record+0x12; 00f9b81d compares it with 0x0a and 00f9b84e stores it");

// -- the receiver's three displacements, all printed by this body's own listing.
static_assert(kReceiverDispatchDisplacement == 0x00, "00f9b83a MOV EDX,[ESI]");
static_assert(kReceiverObjectDisplacement == 0x28,
              "00f9b7f6 MOV ECX,[ESI+0x28], re-read at 00f9b846 and 00f9b88c");
static_assert(kReceiverWordDisplacement == 0x814,
              "00f9b82b CMP EDI,[ESI+0x814] and 00f9b832 LEA EBX,[ESI+0x814]");

// -- the dispatch table displacements.
static_assert(kDispatchTableDisplacement == 0x00,
              "00f9b801 MOV EAX,[ECX] and 00f9b867 MOV EAX,[EDI]");
static_assert(kDispatchSlot024 == 0x24, "00f9b803 MOV EAX,[EAX+0x24]");
static_assert(kDispatchSlot014 == 0x14, "00f9b869 MOV EDX,[EAX+0x14]");
static_assert(kReceiverSlot080 == 0x80, "00f9b83c MOV EAX,[EDX+0x80]");

// -- the immediates. Each is one the listing prints.
static_assert(kPropertyIdA == 0x03ad556a, "00f9b80c and 00f9b871 PUSH 0x3ad556a");
static_assert(kFactoryTagB == 0x031389b5, "00f9b893 PUSH 0x31389b5");
static_assert(kTypeCodeTen == 0x0a,
              "00f9b849 MOV ECX,0xa and 00f9b81d CMP WORD [ECX+0x12],0xa");
static_assert(kFlagsWordTwo == 0x02, "00f9b853 MOV EDX,0x2");
static_assert(kGuardMaskFour == 0x04, "00f9b87a TEST BYTE [ESP+0x20],0x4");
static_assert(kZero == 0x00,
              "00f9b811 XOR EDI,EDI and the three PUSH 0x0 at 00f9b881/00f9b88f/00f9b891");

}  // namespace

// FUN_00f9b7f0 @ 0x00f9b7f0.
//
// __thiscall, receiver in ECX, no ordinary stack arguments, terminator RET with
// no immediate at 0x00f9b8b0 (byte C3). The receiver is aliased into ESI at
// 0x00f9b7f4 and every receiver access goes through that alias.
//
// Return type void. Nothing is moved into EAX for a caller: the three exits
// from this body are 0x00f9b8ac (EAX still holds the table entry that
// 0x00f9b803 loaded), 0x00f9b8aa (EAX holds 0x00427fd0's return) and the
// fall-through (EAX holds 0x006b4b60's return), and no path stores a computed
// value into EAX. Ghidra's own record for this VA carries
// ghidra_function.return_type "undefined" and abi.return_semantics
// "unclassified_in_EAX", so this is an INFERENCE from the listing, not a
// recorded fact; it is stated as such in the sidecar.
//
// NOT ASSERTED: the semantic identity of the object at receiver+0x28, of the
// frame's leading word, of the receiver's word at +0x814, and of the three
// table entries. Each is reachable only as a pointer or a raw word here, and
// naming them would be a member story this body does not carry.
//
// EVERY RECORD BELOW IS AN OPAQUE BYTE RUN. The receiver, the 0x18-byte frame
// object and the 0x14-byte record inside it are declared as byte runs and nothing
// inside any of them is named, because the machine-derived receiver record for
// this VA is `bounds_only`: it states where the body was seen reaching and not
// which member is which, and no machine record in this pack carries a member name
// at all, so a name could be neither confirmed nor refuted here. What IS settled
// is every DISPLACEMENT, and each one is a named constant pinned to the
// instruction that prints it by a `static_assert` in the anonymous namespace
// above. That keeps the body free of hexadecimal literals too: every number in it
// is a constant the reader can trace.
extern "C" void PKG_SW1_00F9B7F0_THISCALL re_00f9b7f0(Receiver* self) {
  // 00f9b7f0  SUB ESP,0x18
  // 00f9b7f3  PUSH ESI
  // 00f9b7f4  MOV ESI,ECX
  LocalProbe frame{};

  // 00f9b7f6  MOV ECX,dword ptr [ESI + 0x28]
  // 00f9b7f9  TEST ECX,ECX
  // 00f9b7fb  JZ 0x00f9b8ac
  //
  // The one gate the whole body sits behind. The word is read again twice
  // later (0x00f9b846 and 0x00f9b88c) rather than kept, so the listing does not
  // promise the two reads see the same value; the model re-reads it at both
  // points rather than caching, which is the observable difference.
  auto* object = reinterpret_cast<DispatchObject*>(
      *word_at(self, kReceiverObjectDisplacement));
  if (object == nullptr) {
    // 00f9b7fb  JZ 0x00f9b8ac falls into the epilogue with the frame and one
    // saved register outstanding. No call is made on this path.
    return;
  }

  // 00f9b801  MOV EAX,dword ptr [ECX]
  // 00f9b803  MOV EAX,dword ptr [EAX + 0x24]
  //
  // Two levels: the object's leading word is a pointer to the table, and the
  // table entry at +0x24 is the callee. This is NOT a vtable slot on the object
  // itself, and the model does not read the object as if it were one.
  const auto probe =
      table_entry<DispatchSlot024>(object, kDispatchSlot024);

  // 00f9b806  PUSH EDI
  // 00f9b807  LEA EDX,[ESP + 0x8]
  // 00f9b80b  PUSH EDX
  // 00f9b80c  PUSH 0x3ad556a
  // 00f9b811  XOR EDI,EDI
  // 00f9b811  XOR EDI,EDI
  //
  // The candidate is zeroed on BOTH paths, which is what gives the compare at
  // 0x00f9b82b a defined left side even when the dispatch reports "no" or the
  // type test fails. It is a dword, and the compare is exact equality.
  Word candidate = kZero;

  // 00f9b813  CALL EAX
  //
  // ESP is entry-0x20 at 0x00f9b807, so EDX is entry-0x18: the first byte of
  // the frame object. The two words are pushed right to left, so the callee's
  // first argument is 0x03ad556a and its second is &frame. ECX still holds the
  // object (nothing between 0x00f9b7f6 and here touches it), so the receiver
  // travels in the register and the call is __thiscall with two words. Net
  // cleanup 8, frame-forced; see the frame note above.
  const std::uint8_t probe_present =
      probe(object, kPropertyIdA, &frame);

  // 00f9b815  TEST AL,AL
  // 00f9b817  JZ 0x00f9b82b
  if (probe_present != 0) {
    // 00f9b819  MOV ECX,dword ptr [ESP + 0x8]
    //
    // ESP is entry-0x20 at this point (net cleanup 8 from 0x28), so [ESP+0x8]
    // is entry-0x18 -- the frame object's leading dword at frame+0x00, not the
    // frame's own address. The instruction LOADS a dword, so what lands in ECX is
    // a pointer the dispatch published, and everything below is two levels below
    // the frame. It is held as a Word and re-offset through `half_through` /
    // `interior_of` rather than dereferenced once, so the depth is in the source.
    const Word published = *word_at(&frame, kLoadedPointerFrameOffset);

    // 00f9b81d  CMP word ptr [ECX + 0x12],0xa
    // 00f9b822  JNZ 0x00f9b82b
    //
    // An exact 16-bit equality against 0x0a: not a mask, not a range, and not
    // sign-sensitive. Anything other than 0x0a -- including 0x0b, 0x0a00 and
    // 0x000a seen as different widths -- leaves the candidate at 0. The word is
    // the one 0x0041ea00, 0x00427fd0 and 0x0093db80 all read at +0x12 of their
    // own receiver, which is why the displacement is a named constant and not a
    // member of anything here.
    if (half_through(published, kRecordTypeDisplacement) == kTypeCodeTen) {
      // 00f9b824  CALL 0x0041ea00
      //
      // ECX is the loaded word, unchanged since 0x00f9b819, so this is a
      // __thiscall with no stack words and the callee sees that same dword as its
      // receiver: the callee ends C3 and so removes nothing. Its own listing
      // re-tests [this+0x12] against 0x0a and 0x10 and then returns one of
      // *(dword*)this (0x0041ea30), this (0x0041ea47), 0 (0x0041ea4c) or
      // 0x015d1164 (0x0041ea58).
      void* const resolved = value_resolve_0041ea00(
          static_cast<ValueRecord*>(interior_of(published, kRecordLeadingDisplacement)));

      // 00f9b829  MOV EDI,dword ptr [EAX]
      //
      // A LOAD through the returned pointer, so the candidate is the leading dword
      // of whatever came back -- not the pointer itself. The two shapes
      // 0x0041ea00 can return (the record, or the record's own first word) are
      // therefore not interchangeable, and the model test drives both.
      candidate = *word_at(resolved, kRecordLeadingDisplacement);
    }
  }

  // 00f9b82b  CMP EDI,dword ptr [ESI + 0x814]
  // 00f9b831  PUSH EBX
  // 00f9b832  LEA EBX,[ESI + 0x814]
  // 00f9b838  JZ 0x00f9b8aa
  //
  // An exact 32-bit EQUALITY, so the comparison is unsigned-equality and
  // unsigned-vs-signed confusion cannot change the outcome: any two distinct
  // 32-bit patterns take the fall-through. The receiver's word at +0x814 is
  // only read here and re-addressed by the LEA; it is never written.
  const Word* const receiver_word =
      word_at(self, kReceiverWordDisplacement);
  if (candidate == *receiver_word) {
    // 00f9b838  JZ 0x00f9b8aa -- straight to the epilogue. Nothing below runs.
    return;
  }

  // 00f9b83a  MOV EDX,dword ptr [ESI]
  // 00f9b83c  MOV EAX,dword ptr [EDX + 0x80]
  // 00f9b842  MOV ECX,ESI
  // 00f9b844  CALL EAX
  //
  // The same two-level shape on the receiver itself, at +0x80, with the
  // receiver in ECX and no stack words. The return value is never read: the very
  // next instruction reloads EDI from the receiver. This is the entry the
  // 0x01490be8 table gives this body at its own slot +0x84, so the class it
  // belongs to is polymorphic at least this deep; nothing here names the entry.
  table_entry<ReceiverSlot080>(self, kReceiverSlot080)(self);

  // 00f9b846  MOV EDI,dword ptr [ESI + 0x28]
  //
  // The gate word is read a second time, not carried over from 0x00f9b7f6. A
  // model that cached it would differ if the +0x80 entry changed the receiver's
  // +0x28, and the model test drives exactly that.
  object = reinterpret_cast<DispatchObject*>(
      *word_at(self, kReceiverObjectDisplacement));

  // 00f9b849  MOV ECX,0xa
  // 00f9b84e  MOV word ptr [ESP + 0x22],CX
  //
  // ESP is entry-0x24 here, so [ESP+0x22] is entry-0x02. The 0x18-byte frame
  // starts at entry-0x18, so this is frame+0x16, which is kRecordTypeDisplacement
  // of the record at frame+0x04. It is a 16-bit store of the literal 0x0a, and it
  // lands on the very word 0x0041ea00 (0x0041ea10) and 0x00427fd0 (0x00428009)
  // read at +0x12 of their own receiver -- the +0x10 / +0x12 displacements those
  // two listings name, and not anything this body's own receiver record states.
  *halfword_at(&frame, kTypeStoreFrameOffset) = kTypeCodeTen;

  // 00f9b853  MOV EDX,0x2
  // 00f9b858  PUSH EBX
  // 00f9b859  LEA ECX,[ESP + 0x14]
  // 00f9b85d  MOV word ptr [ESP + 0x24],DX
  //
  // The PUSH at 0x00f9b858 is the single argument of the call that follows, and
  // it is what the two stack-relative forms below are measured against: with
  // ESP now entry-0x28, [ESP+0x24] is entry-0x04 = frame+0x14 = the record's
  // kRecordFlagsDisplacement, and [ESP+0x14] is entry-0x14 = frame+0x04, the
  // record itself. So the stores bracket the call setup in the listing and the
  // value 0x0002 lands on the record's flags word immediately before 0x00427fd0
  // runs -- which is what satisfies that callee's own success condition
  // (0x00427ffd AND ECX,0x2 together with 0x00428009 CMP EAX,0xa) and keeps it off
  // the 0x0093dd80 error path its other arm takes.
  *halfword_at(&frame, kFlagsStoreFrameOffset) = kFlagsWordTwo;

  // The record inside the frame object, as an ADDRESS and not as a member. All
  // three of 0x00427fd0, the +0x14 dispatch and 0x0093db80 are handed the SAME one
  // (0x00f9b859, 0x00f9b86c, 0x00f9b883), and the frame object holds exactly
  // 0x18 bytes, so 0x04 + 0x14 is the whole of what is left after the leading
  // dword. It is formed once here and reused, so the three hand-outs cannot drift
  // apart.
  ValueRecord* const frame_record = static_cast<ValueRecord*>(
      interior(&frame, kRecordOffsetInsideFrame));

  // 00f9b862  CALL 0x00427fd0
  //
  // __thiscall, destination = frame+0x04 in ECX, one stack word = the ADDRESS
  // of the receiver's word at +0x814, terminator C2 04 00 so the callee removes
  // 4. That the argument is a pointer and not the word is the callee's own
  // listing: 0x00428011 MOV EDX,[EBP+0x8] then 0x00428014 MOV EAX,[EDX].
  value_assign_00427fd0(frame_record, receiver_word);

  // 00f9b867  MOV EAX,dword ptr [EDI]
  // 00f9b869  MOV EDX,dword ptr [EAX + 0x14]
  //
  // Same object's table, different entry: +0x14 this time, and through the word
  // re-read at 0x00f9b846.
  const auto refill =
      table_entry<DispatchSlot014>(object, kDispatchSlot014);

  // 00f9b86c  LEA ECX,[ESP + 0x10]
  // 00f9b870  PUSH ECX
  // 00f9b871  PUSH 0x3ad556a
  // 00f9b876  MOV ECX,EDI
  // 00f9b878  CALL EDX
  //
  // ESP is entry-0x28 at 0x00f9b86c, so ECX is entry-0x18 = frame+0x04 -- the
  // same record 0x00427fd0 was just handed. The first argument is the same
  // 0x03ad556a as the +0x24 dispatch used. The return value is never read.
  // Net cleanup 4, frame-forced and NOT the ordinary value for a two-word
  // callee; see the frame note and the sidecar's unresolved_questions.
  refill(object, kPropertyIdA, frame_record);

  // 00f9b87a  TEST BYTE PTR [ESP + 0x20],0x4
  // 00f9b87f  JZ 0x00f9b88c
  //
  // ESP is entry-0x24, so the byte is entry-0x04 = frame+0x14 = the record's
  // kRecordFlagsDisplacement -- the very word 0x00f9b85d stored 2 into and the one
  // 0x0093db80 tests on whatever it is handed (0x0093db83). The mask is a bit test
  // on 0x04, so the branch depends on exactly one bit of exactly one byte, and the
  // low byte is the one at +0x10 on a little-endian target.
  if ((*byte_at(&frame, kGuardByteFrameOffset) & kGuardMaskFour) != 0) {
    // 00f9b881  PUSH 0x0
    // 00f9b883  LEA ECX,[ESP + 0x14]
    // 00f9b887  CALL 0x0093db80
    //
    // ESP is entry-0x28 after the push, so ECX is entry-0x14 = frame+0x04 --
    // the same record 0x00427fd0 was handed and the same one the +0x14 dispatch
    // just wrote. The argument is the literal 0 and the callee ends C2 04 00.
    // With that argument the callee's own clearing half is skipped (0x0093d9d
    // CMP BYTE PTR [ESP+0x8],0x0 / JZ 0x0093dbb6), so the call has no effect on
    // this path; what is observable is that it happens and what it was handed.
    editor_query_clear_flags_0093db80(frame_record, kZero);
  }
  // 00f9b87f  JZ 0x00f9b88c falls in here when the bit is clear.

  // 00f9b88c  MOV ESI,dword ptr [ESI + 0x28]
  //
  // A third read of the gate word, into ESI. ESI is the register the body
  // aliased the receiver into at 0x00f9b7f4, so from here the receiver is no
  // longer reachable in any register -- which is why the last two instructions
  // that would need it read nothing, and why 0x00f9b8ac's POP ESI restores the
  // caller's ESI rather than this.
  object = reinterpret_cast<DispatchObject*>(
      *word_at(self, kReceiverObjectDisplacement));

  // 00f9b88f  PUSH 0x0
  // 00f9b891  PUSH 0x0
  // 00f9b893  PUSH 0x31389b5
  // 00f9b898  CALL 0x006b1f90
  //
  // Three words pushed right to left: 0x031389b5 is the FIRST argument and the
  // two zeros are the second and third. The callee ends POP ECX / RET with no
  // immediate and reads none of the three (its whole body touches only its own
  // frame and the global at 0x0152fdc4), so 0x00f9b89d's ADD ESP,0x4 is not a
  // retirement of the three -- it drops one, and the other two stay until
  // 0x00f9b8a7. The model keeps all three in the callee's signature and the
  // test measures the order they arrive in.
  const Word token = factory_lookup_006b1f90(kFactoryTagB, kZero, kZero);

  // 00f9b89d  ADD ESP,0x4
  // 00f9b8a0  PUSH EAX
  // 00f9b8a1  PUSH ESI
  // 00f9b8a2  CALL 0x006b4b60
  //
  // Argument order is fixed by the push order and nothing else: the dword
  // 0x006b1f90 returned is the FIRST argument and the object is the second.
  // The callee ends RET with no immediate (0x006b4cad) and installs its own SEH
  // frame, so the caller owns the cleanup.
  object_bind_006b4b60(token, object);

  // 00f9b8a7  ADD ESP,0x10
  //
  // Drops the two words of this call together with the eight that 0x00f9b898
  // was handed and did not take -- three from 0x00f9b89d and three that stayed
  // for this ADD. That is what closes the frame at 0x24 and makes 0x00f9b8aa's
  // three pops land on the saved EBX, EDI and ESI in the right order.
  //
  // 00f9b8aa  POP EBX
  // 00f9b8ab  POP EDI
  // 00f9b8ac  POP ESI
  // 00f9b8ad  ADD ESP,0x18
  // 00f9b8b0  RET
  //
  // The epilogue, shared by all three edges. It produces no value, which is why
  // the return type is void. EAX is left holding 0x006b4b60's return here,
  // 0x00427fd0's on the 0x00f9b838 edge, and the +0x24 table entry on the
  // 0x00f9b7fb edge; none of the three is written for a caller.
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00f9b7f0
