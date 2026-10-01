// PKG-DFW-006A1540 -- VA 0x006a1540
// knowledge-record name: App::PropertyList::Write
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Machine listing, 74 instructions, body 0x006a1540..0x006a15f5
// (GhidraMCP /disassemble_function, 0 instructions at 0x006a1540 .. 0x006a15f3,
// last instruction `RET 0x4`). Every line of the body below carries the
// instruction it comes from, so the listing and this file can be compared
// without leaving it. The header names one displacement per instruction; the
// body states the machine operations and therefore carries exactly one literal,
// the 0x18 stride.
//
// ABI, machine-derived (categories.abi_derived, conventions.confidence
// SUPPORTED): __thiscall.
//
//   0x006a1540 PUSH ECX / 0x006a1541 PUSH EBX / 0x006a1542 PUSH EBP
//   0x006a1543 MOV EBP,dword ptr [ESP + 0x10]
//   0x006a1547 PUSH ESI
//   0x006a1548 MOV ESI,ECX
//
// Three pushes precede the load at 0x006a1543, so [ESP+0x10] is
// entry_ESP+0x4: the one ordinary stack argument. EBP is that argument and not a
// frame pointer -- the body contains no MOV EBP,ESP. The body ends in `RET 0x4`,
// so the callee pops that dword, which is what excludes cdecl and fastcall.
//
// The body's three transfers out are all direct calls, and there is no indirect
// transfer of any kind in the 74 instructions:
//
//   0x006a156f  CALL 0x0093aa70   the element count
//   0x006a15b8  CALL 0x0093aa70   one element's word at +0x00
//   0x006a15d0  CALL 0x00693390   one element's address at +0x04
//
// Nothing is claimed about what either callee does. Both are declared in the
// header with the argument count and push order this listing fixes, and defined
// as recording observers by the model test.
//
// The quotient is computed TWICE, and the duplication is load-bearing rather than
// redundant: 0x006a154a..0x006a1568 produces the word that is written to the
// sink, and 0x006a1574..0x006a158b re-reads both receiver words and re-divides,
// with the first call in between. The second quotient is the loop bound
// (0x006a1590 `TEST EAX,EAX` / 0x006a1592 `JLE 0x006a15ed`). Whether the two can
// ever differ is not established by any record -- the only call between them
// writes to a sink, not to the receiver -- so the reconstruction keeps the two
// evaluations separate rather than folding them into one variable. See
// "two_quotients" in the model test for what that costs and what it buys.
//
// The loop carries TWO induction variables and so does the machine:
//
//   EDI   a byte offset, stepped by 0x18 at 0x006a15e2 `ADD EDI,0x18`
//   [ESP+0x18]  a countdown, decremented at 0x006a15e5
//                `SUB dword ptr [ESP + 0x18],0x1` and left by 0x006a15ea
//                `JNZ 0x006a15a0`
//
// They are not interchangeable: the countdown decides when the loop ends, not
// the offset. Both are modelled separately for that reason.
//
// The loop does NOT abort on a failed write. A zero verdict at 0x006a15a2,
// 0x006a15c2 or 0x006a15da all jump to 0x006a15e0, which is the block the tail
// falls through to, re-zeroes the verdict byte and lets the countdown run to
// zero. Every later iteration therefore takes the skip path and touches nothing.

#include "dfw_006a1540_types.hpp"

namespace openspore::reconstruction::pkg_dfw_006a1540 {

extern "C" bool PKG_DFW_006A1540_THISCALL
proplist_write_006a1540(OpaquePropertyList *list, OpaqueStreamSink *sink) {
  // 0x006a1540  PUSH ECX
  // 0x006a1541  PUSH EBX
  // 0x006a1542  PUSH EBP
  // 0x006a1543  MOV EBP,dword ptr [ESP + 0x10]   -> entry_ESP+0x4, `sink`
  // 0x006a1547  PUSH ESI
  // 0x006a1548  MOV ESI,ECX                      -> the receiver alias
  //
  // The sink is never dereferenced anywhere in the 74 instructions. It appears
  // only as the first argument of the three calls below.
  //
  // 0x006a154a  MOV ECX,dword ptr [ESI + 0x1c]
  // 0x006a154d  SUB ECX,dword ptr [ESI + 0x18]
  // 0x006a1550  MOV EAX,0x2aaaaaab
  // 0x006a1555  IMUL ECX
  // 0x006a1557  SAR EDX,0x2
  // 0x006a155c  MOV EAX,EDX
  // 0x006a1564  SHR EAX,0x1f
  // 0x006a1568  ADD EAX,EDX
  //
  // One element per 0x18 bytes, matching the stride at 0x006a15e2. The
  // quotient is a signed 32-bit count and it is the value handed to the sink.
  Word count_word = static_cast<Word>(list_entry_count(list));

  // 0x006a155a  PUSH 0x0                       fourth argument, 0
  // 0x006a155e  PUSH 0x1                       third argument, 1
  // 0x006a1560  LEA ECX,[ESP + 0x14]           address of the spill slot that
  // 0x006a1567  PUSH ECX                        currently holds the saved ECX,
  //                                              entry_ESP-0x4
  // 0x006a156a  PUSH EBP                       first argument, `sink`
  // 0x006a156b  MOV dword ptr [ESP + 0x1c],EAX the quotient, into that slot
  // 0x006a156f  CALL 0x0093aa70
  // 0x006a158d  ADD ESP,0x10
  //
  // The store at 0x006a156b lands after all four pushes and before the call, so
  // the callee sees the quotient through the pointer it was handed. Only the
  // value is observable: the slot itself is a frame address this reconstruction
  // does not and cannot reproduce, so `count_word` is an ordinary local here.
  bool ok = dfw_write_words_0093aa70(sink, &count_word, 1, 0);

  // 0x006a1574  MOV ECX,dword ptr [ESI + 0x1c]
  // 0x006a1577  SUB ECX,dword ptr [ESI + 0x18]
  // 0x006a157a  MOV BL,AL                        the verdict, captured in BL
  // 0x006a157c  MOV EAX,0x2aaaaaab
  // 0x006a1581  IMUL ECX
  // 0x006a1583  SAR EDX,0x2
  // 0x006a1586  MOV EAX,EDX
  // 0x006a1588  SHR EAX,0x1f
  // 0x006a158b  ADD EAX,EDX
  //
  // Both receiver words are read again and divided again. The reconstruction
  // calls the same accessor a second time rather than reusing `count_word`, so
  // a receiver changed by the call above is followed here.
  std::int32_t remaining = list_entry_count(list);

  // 0x006a1590  TEST EAX,EAX
  // 0x006a1592  JLE 0x006a15ed
  //
  // A signed test. A negative quotient skips the loop exactly as a zero quotient
  // does, and the negative count is still written to the sink first.
  if (remaining > 0) {
    // 0x006a1594  PUSH EDI
    // 0x006a1595  XOR EDI,EDI                    the byte offset, zero
    // 0x006a1597  MOV dword ptr [ESP + 0x18],EAX  the countdown, from the
    //                                             quotient -- this is the slot
    //                                             that held the saved EBP
    // 0x006a159b  JMP 0x006a15a0                  into the loop test
    std::int32_t offset = 0;
    do {
      // 0x006a15a0  TEST BL,BL
      // 0x006a15a2  JZ 0x006a15e0
      //
      // Once the verdict is zero this whole block is skipped, for the rest of
      // the countdown.
      if (ok) {
        // 0x006a15a4  MOV EDX,dword ptr [ESI + 0x18]
        // 0x006a15a7  MOV EAX,dword ptr [EDI + EDX*0x1]
        //
        // The receiver's +0x18 is re-read here rather than hoisted, so
        // `range_begin_at` is called per iteration.
        Word id_word = entry_word_00(range_begin_at(list) + offset);

        // 0x006a15aa  PUSH 0x0                       fourth argument, 0
        // 0x006a15ac  PUSH 0x1                       third argument, 1
        // 0x006a15ae  LEA ECX,[ESP + 0x18]           address of the spill slot
        // 0x006a15b2  PUSH ECX                        that held the saved ESI,
        //                                              entry_ESP-0x10
        // 0x006a15b3  PUSH EBP                       first argument, `sink`
        // 0x006a15b4  MOV dword ptr [ESP + 0x20],EAX the element word, into it
        // 0x006a15b8  CALL 0x0093aa70
        // 0x006a15bd  ADD ESP,0x10
        // 0x006a15c0  TEST AL,AL
        // 0x006a15c2  JZ 0x006a15e0
        if (!dfw_write_words_0093aa70(sink, &id_word, 1, 0)) {
          ok = false;
        } else {
          // 0x006a15c4  MOV EAX,dword ptr [ESI + 0x18]
          // 0x006a15c7  ADD EAX,EDI
          // 0x006a15c9  PUSH 0x0                       third argument, 0
          // 0x006a15cb  ADD EAX,0x4                    the element's +0x04
          // 0x006a15ce  PUSH EAX                       second argument
          // 0x006a15cf  PUSH EBP                       first argument, `sink`
          // 0x006a15d0  CALL 0x00693390
          // 0x006a15d5  ADD ESP,0xc
          // 0x006a15d8  TEST AL,AL
          // 0x006a15da  JZ 0x006a15e0
          if (!dfw_write_entry_00693390(
                  sink, entry_payload_04(range_begin_at(list) + offset), 0)) {
            ok = false;
          } else {
            // 0x006a15dc  MOV BL,0x1
            // 0x006a15de  JMP 0x006a15e2
            ok = true;
          }
        }
      } else {
        // 0x006a15e0  XOR BL,BL
        ok = false;
      }
      // 0x006a15e2  ADD EDI,0x18
      offset = offset + 0x18;
      // 0x006a15e5  SUB dword ptr [ESP + 0x18],0x1
      // 0x006a15ea  JNZ 0x006a15a0
    } while (--remaining != 0);
  }

  // 0x006a15ec  POP EDI          reached only after the countdown reaches zero
  // 0x006a15ed  POP ESI          also the JLE target from 0x006a1592
  // 0x006a15ee  POP EBP
  // 0x006a15ef  MOV AL,BL        the return word, in the low byte only
  // 0x006a15f1  POP EBX
  // 0x006a15f2  POP ECX
  // 0x006a15f3  RET 0x4          the callee pops the one stack argument
  return ok;
}

} // namespace openspore::reconstruction::pkg_dfw_006a1540
