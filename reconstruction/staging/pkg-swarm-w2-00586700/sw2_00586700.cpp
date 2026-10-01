// PKG-SWARM-W2-00586700 -- VA 0x00586700
// FUN_00586700 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000).
//
// THE COMPLETE BODY: 89 instructions, 0x00586700..0x005867f3 inclusive, 244
// bytes. ghidra_function records body_start 0x00586700, body_end 0x005867f3,
// size_bytes 244, and the record is NOT truncated: the listing below was
// re-derived from the image bytes for this package (objdump -D -b binary -m
// i386 -M intel over the 0xf4 bytes at this VA's file offset, 0x185b00) and it
// reproduces the committed Ghidra listing instruction for instruction, at the
// same addresses and with the same lengths. 0x005867f3 is `C3`, the last byte
// of the body. All five conditional branch targets -- 0x0058673b, 0x00586754,
// 0x005867b8, 0x005867d1 and 0x00586782 -- lie inside the span.
//
//   00586700  83 ec 0c           SUB ESP,0xc
//   00586703  53                 PUSH EBX
//   00586704  55                 PUSH EBP
//   00586705  8b e9              MOV EBP,ECX
//   00586707  8b 85 d8 04 00 00  MOV EAX,dword ptr [EBP + 0x4d8]
//   0058670d  56                 PUSH ESI
//   0058670e  8d b5 d8 04 00 00  LEA ESI,[EBP + 0x4d8]
//   00586714  57                 PUSH EDI
//   00586715  8b 7e 04           MOV EDI,dword ptr [ESI + 0x4]
//   00586718  8b cf              MOV ECX,EDI
//   0058671a  2b c8              SUB ECX,EAX
//   0058671c  83 f9 23           CMP ECX,0x23
//   0058671f  73 1a              JNC 0x0058673b
//   00586721  8d 54 24 13        LEA EDX,[ESP + 0x13]
//   00586725  2b c7              SUB EAX,EDI
//   00586727  52                 PUSH EDX
//   00586728  83 c0 23           ADD EAX,0x23
//   0058672b  50                 PUSH EAX
//   0058672c  57                 PUSH EDI
//   0058672d  8b ce              MOV ECX,ESI
//   0058672f  c6 44 24 1f 00     MOV byte ptr [ESP + 0x1f],0x0
//   00586734  e8 77 ea f8 ff     CALL 0x005151b0
//   00586739  eb 17              JMP 0x00586752
//   0058673b  8d 58 23           LEA EBX,[EAX + 0x23]
//   0058673e  8b c7              MOV EAX,EDI
//   00586740  2b c7              SUB EAX,EDI
//   00586742  50                 PUSH EAX
//   00586743  57                 PUSH EDI
//   00586744  53                 PUSH EBX
//   00586745  e8 fa 9f c5 00     CALL 0x011e0744
//   0058674a  2b df              SUB EBX,EDI
//   0058674c  83 c4 0c           ADD ESP,0xc
//   0058674f  01 5e 04           ADD dword ptr [ESI + 0x4],EBX
//   00586752  33 c0              XOR EAX,EAX
//   00586754  8b 0e              MOV ECX,dword ptr [ESI]
//   00586756  c6 04 08 00        MOV byte ptr [EAX + ECX * 1],0x0
//   0058675a  40                 INC EAX
//   0058675b  83 f8 23           CMP EAX,0x23
//   0058675e  7c f4              JL 0x00586754
//   00586760  8d 95 f0 04 00 00  LEA EDX,[EBP + 0x4f0]
//   00586766  c7 85 ec 04 00 00  MOV dword ptr [EBP + 0x4ec],0x0
//   00586770  89 54 24 14        MOV dword ptr [ESP + 0x14],EDX
//   00586774  81 c5 0c 05 00 00  ADD EBP,0x50c
//   0058677a  c7 44 24 18 06 00  MOV dword ptr [ESP + 0x18],0x6
//   00586782  8b 44 24 14        MOV EAX,dword ptr [ESP + 0x14]
//   00586786  c7 00 00 00 00 00  MOV dword ptr [EAX],0x0
//   0058678c  8b 75 00           MOV ESI,dword ptr [EBP + 0x0]
//   0058678f  8b 45 fc           MOV EAX,dword ptr [EBP + -0x4]
//   00586792  8d 7d fc           LEA EDI,[EBP + -0x4]
//   00586795  8b ce              MOV ECX,ESI
//   00586797  2b c8              SUB ECX,EAX
//   00586799  83 f9 23           CMP ECX,0x23
//   0058679c  73 1a              JNC 0x005867b8
//   0058679e  8d 54 24 13        LEA EDX,[ESP + 0x13]
//   005867a2  2b c6              SUB EAX,ESI
//   005867a4  52                 PUSH EDX
//   005867a5  83 c0 23           ADD EAX,0x23
//   005867a8  50                 PUSH EAX
//   005867a9  56                 PUSH ESI
//   005867aa  8b cf              MOV ECX,EDI
//   005867ac  c6 44 24 1f 00     MOV byte ptr [ESP + 0x1f],0x0
//   005867b1  e8 fa e9 f8 ff     CALL 0x005151b0
//   005867b6  eb 17              JMP 0x005867cf
//   005867b8  8d 58 23           LEA EBX,[EAX + 0x23]
//   005867bb  8b c6              MOV EAX,ESI
//   005867bd  2b c6              SUB EAX,ESI
//   005867bf  50                 PUSH EAX
//   005867c0  56                 PUSH ESI
//   005867c1  53                 PUSH EBX
//   005867c2  e8 7d 9f c5 00     CALL 0x011e0744
//   005867c7  2b de              SUB EBX,ESI
//   005867c9  83 c4 0c           ADD ESP,0xc
//   005867cc  01 5d 00           ADD dword ptr [EBP + 0x0],EBX
//   005867cf  33 c0              XOR EAX,EAX
//   005867d1  8b 0f              MOV ECX,dword ptr [EDI]
//   005867d3  c6 04 08 00        MOV byte ptr [EAX + ECX * 1],0x0
//   005867d7  40                 INC EAX
//   005867d8  83 f8 23           CMP EAX,0x23
//   005867db  7c f4              JL 0x005867d1
//   005867dd  83 44 24 14 04     ADD dword ptr [ESP + 0x14],0x4
//   005867e2  83 c5 14           ADD EBP,0x14
//   005867e5  83 6c 24 18 01     SUB dword ptr [ESP + 0x18],0x1
//   005867ea  75 96              JNZ 0x00586782
//   005867ec  5f                 POP EDI
//   005867ed  5e                 POP ESI
//   005867ee  5d                 POP EBP
//   005867ef  5b                 POP EBX
//   005867f0  83 c4 0c           ADD ESP,0xc
//   005867f3  c3                 RET
//
// WHAT THE BODY IS. A reset. It does the same operation seven times over --
// once on the address triple stored at self+0x4d8, then once on each of six
// elements whose current word is at self+0x50c+20k -- and the operation is:
//
//     advance the element's current word to start + 35, and zero the 35 bytes
//     at start.
//
// Each occurrence is the same two-armed shape, and both arms end with the same
// 35-byte zero-fill; they differ only in who moves the current word. If
// start..current already spans at least 35 bytes, the body computes
// start+35 - current and ADDs it to the current word itself, with a
// zero-length memcpy in between (0x0058673b..0x0058674f, and 0x005867b8..
// 0x005867cc inside the loop). If it spans less, the body hands the shortfall
// to 0x005151b0 together with the current address and a pointer to a zero byte
// and lets THAT move the word -- this body writes nothing to the current word
// on the slow arm at all. In between it zeroes self+0x4ec once, and inside the
// loop it zeroes one dword of a six-dword run at self+0x4f0 per iteration.
//
// The two zeroing loops RELOAD the start word on every iteration
// (0x00586754 MOV ECX,[ESI] and 0x005867d1 MOV ECX,[EDI]) rather than hoisting
// it. Nothing between the reload and the store can change it on either path --
// the arms that run before the loop write to the CURRENT word or call out, and
// 0x0058674f / 0x005867cc write the word at [ESI+0x4] / [EBP+0x0], which is
// not the word the loop reads -- so the reload is a register-allocation
// artifact with no effect on the result. The model keeps the reload anyway,
// because it costs nothing and it is what the bytes do.
//
// THE COMPARES ARE UNSIGNED, AND THAT IS THE WHOLE BRANCH LOGIC.
// 0x0058671f JNC and 0x0058679c JNC (opcode 0x73) test the flags of
// 0x0058671c / 0x00586799 CMP ECX,0x23, where ECX was built by
// MOV ECX,EDI; SUB ECX,EAX -- i.e. current minus start, computed in 32 bits.
// JNC is "not carry", which is the UNSIGNED >=. Nothing in the disassembly
// says unsigned in words; it is the opcode. This matters whenever current is
// BELOW start: the difference wraps to a huge unsigned value, the unsigned test
// passes, and the body takes the fast arm and sets current to start+35. Read
// signed, the same input would take the slow arm and call 0x005151b0 with a
// shortfall of 35 plus a large positive number. The model test drives exactly
// that input.
//
// THE FAST ARM'S MEMCPY COPIES NOTHING, TWICE. 0x0058673e MOV EAX,EDI and
// 0x00586740 SUB EAX,EDI put a zero in the count slot, and 0x005867bb /
// 0x005867bd do the same inside the loop. The model reproduces the call rather
// than eliding it, so the transfer is observable, and the pointer bump is
// reproduced as the two arithmetic instructions the listing uses
// (0x0058673b LEA EBX,[EAX + 0x23]; 0x0058674a SUB EBX,EDI; 0x0058674f ADD
// dword ptr [ESI + 0x4],EBX) rather than as an assignment, so the wrapping
// arithmetic is the machine's.
//
// NO STRUCT IS NAMED and no field identity is claimed: the machine-derived
// receiver record is bounds_only, which says where the body was seen reaching
// and not what the words there are. The header's note (3) fixes, from
// 0x005151b0's own bytes, that the triple at the callee's this+0x00 / +0x04 /
// +0x08 is an address triple, which is what licenses calling the two words
// this body reads a START and a CURRENT address. Everything else -- the dword
// at self+0x4ec, the six dwords at self+0x4f0+4k, the twelve bytes each loop
// element has beyond the two words this body touches -- is described by its
// displacement and nothing more.
//
// VIRTUAL DISPATCH: none, and none declared. The four transfers in the body
// (0x00586734, 0x00586745, 0x005867b1, 0x005867c2) are all direct, and
// abi_derived.dispatch records indirect_calls 0, call_offsets [] and
// vtable_shaped_loads 0. This body is the code pointer at word index 20 of the
// 29-word run at 0x013f57f8 (the sole xref into this VA is the DATA reference
// from 0x013f5848, which is that run's byte offset 0x50) -- recorded as a fact
// about where the entry point lives, not modelled as dispatch, and no class is
// named. See the header's note (4).
//
// GLOBALS: none reached. The listing's only absolute operands are the two call
// targets and the five conditional branch targets, all of them code. 0x011e0744
// is the CRT memcpy thunk and lives in .text, but it is at an address above
// this validator's hard-coded code/data boundary, so the GLOBALS arm classifies
// it as a data address and warns. That is a property of the boundary constant
// and of the evidence, not of this source; see the sidecar's known_blockers.

#include "sw2_00586700_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00586700 {

extern "C" int SW2_00586700_THISCALL re_00586700(void* receiver) {
  // 00586700  SUB ESP,0xc          twelve bytes of frame: one value byte, one
  // 00586703  PUSH EBX            cursor, one counter (header note (0))
  // 00586704  PUSH EBP            ...and four callee-saved registers, of which
  // 0058670d  PUSH ESI            EBP is the receiver, not a frame pointer
  // 00586714  PUSH EDI
  std::uint8_t* const self = static_cast<std::uint8_t*>(receiver);

  // 00586705  MOV EBP,ECX
  //
  // THE RESOLUTION OF THE ABI ENVELOPE'S ABSTENTION. The envelope abstained with
  // "push ebp without mov ebp,esp, and EBP is loaded from a register or used as
  // a memory base, so it is a general register" -- and it is this instruction
  // that says what the general register holds. EBP is the receiver, aliased out
  // of ECX on the third instruction of the body, and every displacement below is
  // a displacement in the receiver. 0x00586704 PUSH EBP preserves the caller's
  // EBP (restored at 0x005867ee) exactly as the three pushes around it preserve
  // EBX, ESI and EDI.
  //
  // The three pieces of loop state the machine keeps -- the cursor in the frame
  // word at entry_ESP-8, the counter in the frame word at entry_ESP-4, and the
  // walker's displacement in EBP -- are modelled as three ordinary variables that
  // advance on exactly the schedule 0x005867dd, 0x005867e5 and 0x005867e2 set.
  Word* slot_cursor = word_at(self, kSlotBase);
  Word* walk_end = word_block(self + 0x50c);
  Word remaining = kTripCount;

  // =====================================================================
  // OCCURRENCE 1 of 7: the element whose START word is at self+0x4d8 and
  // whose CURRENT word is the one dword above it. 0x0058670e LEA ESI and
  // 0x00586715 MOV EDI,[ESI + 0x4] fix that pair; 0x00586754 MOV ECX,[ESI]
  // and 0x0058672d MOV ECX,ESI re-read the same two words.
  // =====================================================================

  // 00586707  MOV EAX,dword ptr [EBP + 0x4d8]
  Word* const head_start = word_block(self + 0x4d8);
  // 00586715  MOV EDI,dword ptr [ESI + 0x4]
  Word* const head_current = head_start + kEndWordIndex;

  // 00586715  MOV EDI,dword ptr [ESI + 0x4]
  // 00586718  MOV ECX,EDI
  // 0058671a  SUB ECX,EAX
  // 0058671c  CMP ECX,0x23
  // 0058671f  JNC 0x0058673b
  //
  // UNSIGNED. JNC is opcode 0x73, so this is `(Word)(current - start) >= 35`
  // and NOT a signed comparison. The two operands are the element's two words,
  // one level of indirection each: the words hold ADDRESSES, they are not
  // themselves the addresses, and the comparison is between the addresses and
  // not between anything stored at them.
  if (static_cast<Word>(*head_current - *head_start) >= kBufBytes) {
    // ---- occurrence 1, fast arm: this body moves the CURRENT word itself ----
    //
    // 0058673b  LEA EBX,[EAX + 0x23]
    //   EAX is still the START address here: nothing between 0x00586707 and
    //   this LEA writes EAX, and 0x00586718/0x0058671a used ECX. So the
    //   destination is start + 35, computed as the listing computes it.
    const Word head_destination = *head_start + kBufBytes;
    // 0058673e  MOV EAX,EDI
    // 00586740  SUB EAX,EDI
    //   The count is identically zero -- a register minus itself. The model
    //   keeps the call rather than eliding it, so the transfer stays
    //   observable, and the test measures it.
    // 00586742  PUSH EAX
    // 00586743  PUSH EDI
    // 00586744  PUSH EBX
    // 00586745  CALL 0x011e0744
    (void)memcpy_thunk_011e0744(at(head_destination), at(*head_current), kEmptyCopy);
    // 0058674a  SUB EBX,EDI
    // 0058674c  ADD ESP,0xc
    // 0058674f  ADD dword ptr [ESI + 0x4],EBX
    //   An ADD, not a store: the delta is `start + 35 - current` in 32-bit
    //   wrapping arithmetic, added to whatever the CURRENT word held. When
    //   CURRENT is BELOW start -- which is exactly the input that separates
    //   this unsigned test from a signed one -- the delta is large and the sum
    //   wraps back round to start + 35.
    *head_current = *head_current + static_cast<Word>(head_destination - *head_current);
  } else {
    // ---- occurrence 1, slow arm: 0x005151b0 moves the CURRENT word ----
    //
    // 00586721  LEA EDX,[ESP + 0x13]     the frame's value byte
    // 00586725  SUB EAX,EDI             the shortfall, as begin - current
    // 00586727  PUSH EDX                third stack word: &value_byte
    // 00586728  ADD EAX,0x23            ... so: 35 - (current - start)
    // 0058672b  PUSH EAX                second stack word: the shortfall
    // 0058672c  PUSH EDI                first stack word: the CURRENT address
    // 0058672d  MOV ECX,ESI             the callee's receiver: &START word
    // 0058672f  MOV byte ptr [ESP + 0x1f],0x0   the value byte is zero
    // 00586734  CALL 0x005151b0
    //
    // The value byte is the frame slot at entry_ESP-9 (header note (0)), and
    // 0x0058672f is one of only two instructions that store to it -- the body
    // zero-initialises it immediately before each of the two calls rather than
    // once at entry, and the model does the same.
    //
    // NOTHING writes *head_current in this arm. Advancing it is the callee's
    // job: 0x005151b0's own bytes store the advanced pair at 0x00515291 and
    // 0x005153cc before it returns. A model that also bumped the word here
    // would be doing the callee's work a second time; the test runs this arm
    // with a passive observer precisely to catch that.
    std::uint8_t head_value_byte = 0;
    growable_buffer_fill_005151b0(head_start, at(*head_current),
                                  *head_start - *head_current + kBufBytes, &head_value_byte);
  }

  // 00586752  XOR EAX,EAX
  // 00586754  MOV ECX,dword ptr [ESI]          the START word, re-read
  // 00586756  MOV byte ptr [EAX + ECX * 1],0x0
  // 0058675a  INC EAX
  // 0058675b  CMP EAX,0x23
  // 0058675e  JL 0x00586754
  //
  // 35 BYTES AT THE START ADDRESS. The store is indexed by the loaded word used
  // directly as a base with no displacement added, so the bytes written are at
  // `start + index` and the receiver is not written through at all. The reload
  // of the START word on every iteration is reproduced; see the note above the
  // function for why it cannot change the result.
  for (Word head_index = 0; head_index != kBufBytes; ++head_index) {
    at(*head_start)[head_index] = 0;
  }

  // 00586760  LEA EDX,[EBP + 0x4f0]            the cursor's start displacement
  // 00586766  MOV dword ptr [EBP + 0x4ec],0x0
  //
  // The one dword zeroed outside any loop, and it is never read by this body on
  // any path (header note (5)). The cursor at 0x4f0 is stored into the frame
  // word at entry_ESP-8 by 0x00586770 and is stepped by 0x005867dd.
  *word_block(self + 0x4ec) = 0;

  // 0058677a  MOV dword ptr [ESP + 0x18],0x6
  //
  // Six iterations, counted down (0x005867e5 SUB [ESP+0x18],0x1; 0x005867ea
  // JNZ), so the test is after the decrement and the loop is a do/while.
  do {
    // 00586782  MOV EAX,dword ptr [ESP + 0x14]
    // 00586786  MOV dword ptr [EAX],0x0
    //
    // ONE DWORD of the six-dword run, zeroed through the cursor rather than
    // through a displacement -- which is why 0x4f0 is absent from the machine
    // receiver record's four even though the body plainly reaches it. The store
    // is a DWORD: the four bytes at self + 0x4f0 + 4*k and nothing else.
    *slot_cursor = 0;

    // 0058678c  MOV ESI,dword ptr [EBP + 0x0]     the element's CURRENT word
    // 0058678f  MOV EAX,dword ptr [EBP + -0x4]    the element's START word
    // 00586792  LEA EDI,[EBP + -0x4]              its address, for the callee
    //
    // Recomputed from the walker every iteration, as the listing does, rather
    // than carried in a second cursor: the START word is the one dword BELOW
    // the CURRENT word, which is why the walker's start displacement 0x50c and
    // the receiver record's 0x508 are one element seen from two ends.
    Word* const walk_start = walk_end - kEndWordIndex;
    const Word walk_current_address = *walk_end;
    const Word walk_start_address = *walk_start;

    // 00586795  MOV ECX,ESI
    // 00586797  SUB ECX,EAX
    // 00586799  CMP ECX,0x23
    // 0058679c  JNC 0x005867b8
    //
    // The same UNSIGNED >= on the same 0x23, on the second of the two arms. This
    // is the only control decision the loop makes, and the loop's other four
    // instructions are its bookkeeping.
    if (static_cast<Word>(walk_current_address - walk_start_address) >= kBufBytes) {
      // ---- occurrence N, fast arm: the CURRENT word is moved here ----
      // 005867b8  LEA EBX,[EAX + 0x23]
      const Word walk_destination = walk_start_address + kBufBytes;
      // 005867bb  MOV EAX,ESI
      // 005867bd  SUB EAX,ESI
      // 005867bf  PUSH EAX
      // 005867c0  PUSH ESI
      // 005867c1  PUSH EBX
      // 005867c2  CALL 0x011e0744
      (void)memcpy_thunk_011e0744(at(walk_destination), at(walk_current_address), kEmptyCopy);
      // 005867c7  SUB EBX,ESI
      // 005867c9  ADD ESP,0xc
      // 005867cc  ADD dword ptr [EBP + 0x0],EBX
      *walk_end = *walk_end + static_cast<Word>(walk_destination - walk_current_address);
    } else {
      // ---- occurrence N, slow arm: 0x005151b0 moves the CURRENT word ----
      // 0058679e  LEA EDX,[ESP + 0x13]
      // 005867a2  SUB EAX,ESI
      // 005867a4  PUSH EDX
      // 005867a5  ADD EAX,0x23
      // 005867a8  PUSH EAX
      // 005867a9  PUSH ESI
      // 005867aa  MOV ECX,EDI
      // 005867ac  MOV byte ptr [ESP + 0x1f],0x0
      // 005867b1  CALL 0x005151b0
      //
      // The callee's receiver is `walk_start` -- the address of the START word,
      // taken at 0x00586792 -- not `walk_end` and not the walker. The test
      // asserts that, because the two differ by exactly one word and a
      // reconstruction that passed the wrong one would still "work" on every
      // element it touches.
      std::uint8_t walk_value_byte = 0;
      growable_buffer_fill_005151b0(walk_start, at(walk_current_address),
                                    walk_start_address - walk_current_address + kBufBytes,
                                    &walk_value_byte);
    }

    // 005867cf  XOR EAX,EAX
    // 005867d1  MOV ECX,dword ptr [EDI]             the START word, re-read
    // 005867d3  MOV byte ptr [EAX + ECX * 1],0x0
    // 005867d7  INC EAX
    // 005867d8  CMP EAX,0x23
    // 005867db  JL 0x005867d1
    //
    // The same 35 bytes at the same START address, from the same five
    // instructions with the same two loop heads as occurrence 1.
    for (Word walk_index = 0; walk_index != kBufBytes; ++walk_index) {
      at(*walk_start)[walk_index] = 0;
    }

    // 005867dd  ADD dword ptr [ESP + 0x14],0x4     the cursor advances ONE word
    // 005867e2  ADD EBP,0x14                      the walker advances FIVE
    // 005867e5  SUB dword ptr [ESP + 0x18],0x1     one trip consumed
    // 005867ea  JNZ 0x00586782
    slot_cursor += kSlotStrideWords;
    walk_end += kWalkStrideWords;
    --remaining;
  } while (remaining != 0);

  // 005867ec  POP EDI
  // 005867ed  POP ESI
  // 005867ee  POP EBP
  // 005867ef  POP EBX
  // 005867f0  ADD ESP,0xc
  // 005867f3  RET
  //
  // EAX holds 0x23 here on every one of the seven paths, because the last thing
  // the body wrote to it was 0x005867d7 INC EAX and that loop's exit condition
  // 0x005867d8 CMP EAX,0x23 leaves it at 0x23. The value is a memset counter
  // and means nothing; it is returned because the bytes put it there. See the
  // header's return note and the sidecar's unresolved_questions.
  return static_cast<int>(kBufBytes);
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00586700
