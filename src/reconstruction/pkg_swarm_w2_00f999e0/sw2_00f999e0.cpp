// PKG-SWARM-W2-00F999E0 -- VA 0x00f999e0
// FUN_00f999e0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body: 80 instructions, 0x00f999e0..0x00f99ab3 inclusive
// (ghidra_function.body_start 0x00f999e0, body_end 0x00f99ab3, size_bytes 212).
// The listing below is re-derived from the image bytes with
// `objdump -d -M intel --start-address=0x00f999e0 --stop-address=0x00f99ab4`, which
// reproduces the committed 80 instructions at the same addresses with identical
// mnemonics, operands, call targets and branch targets. Nothing in this model
// depends on the decompilation, and the one place it is worth reading is the
// compare loop, where it INVERTS both polarities -- see THE COMPARE LOOP below.
//
//   00f999e0  PUSH ESI
//   00f999e1  MOV ESI,ECX                            receiver alias
//   00f999e3  CALL 0x00f48a70                         -> EAX
//   00f999e8  MOV ECX,EAX                             that value becomes a receiver
//   00f999ea  CALL 0x00f699b0                         -> AL
//   00f999ef  TEST AL,AL
//   00f999f1  JNZ 0x00f999f7                          gate 1: keep going
//   00f999f3  XOR AL,AL                               return 0
//   00f999f5  POP ESI
//   00f999f6  RET
//   00f999f7  MOV EAX,dword ptr [ESI]                 the object's own table pointer
//   00f999f9  MOV EDX,dword ptr [EAX + 0x4c]          the word the table holds at +0x4c
//   00f999fc  PUSH 0x7
//   00f999fe  MOV ECX,ESI
//   00f99a00  CALL EDX
//   00f99a02  TEST AL,AL
//   00f99a04  JNZ 0x00f999f3                          gate 2: 0 -> return 0
//   00f99a06  CMP byte ptr [ESI + 0x370],AL           AL is provably 0 here
//   00f99a0c  JNZ 0x00f999f3                          gate 3: nonzero -> return 0
//   00f99a0e  MOV EAX,dword ptr [ESI]                 the table pointer, read AGAIN
//   00f99a10  MOV EDX,dword ptr [EAX + 0x30]          the word the table holds at +0x30
//   00f99a13  MOV ECX,ESI
//   00f99a15  CALL EDX
//   00f99a17  TEST AL,AL
//   00f99a19  JZ  0x00f999f3                          gate 4: 0 -> return 0
//   00f99a1b  CMP byte ptr [ESI + 0x4f4],0x0
//   00f99a22  JZ  0x00f999f3                          gate 5: 0 -> return 0
//   00f99a24  PUSH EDI
//   00f99a25  XOR EDI,EDI                            outer index = 0
//   00f99a27  ADD ESI,0x438                          outer cursor = receiver + 0x438
//   00f99a2d  LEA ECX,[ECX]                          8D 09 -- a two-byte no-op
//   00f99a30  XOR EDX,EDX                            inner index = 0
//   00f99a32  LEA ECX,[ESI + 0xffffff40]             inner cursor = outer - 0xc0
//   00f99a38  JMP 0x00f99a40
//   00f99a40  MOVSS XMM0,dword ptr [ECX - 0x4]        group 0, pair 0, left
//   00f99a45  UCOMISS XMM0,dword ptr [ECX + 0x4]      group 0, pair 0, right
//   00f99a49  LAHF
//   00f99a4a  TEST AH,0x44
//   00f99a4d  JNP 0x00f99a5d                         not exactly equal -> skip pair 1
//   00f99a4f  MOVSS XMM0,dword ptr [ECX]              group 0, pair 1, left
//   00f99a53  UCOMISS XMM0,dword ptr [ECX + 0x8]      group 0, pair 1, right
//   00f99a57  LAHF
//   00f99a58  TEST AH,0x44
//   00f99a5b  JP  0x00f99aaf                          both pairs equal -> return 0
//   00f99a5d  INC EDX
//   00f99a5e  ADD ECX,0x60                           inner stride
//   00f99a61  CMP EDX,0x2
//   00f99a64  JL  0x00f99a40
//   00f99a66  MOVSS XMM0,dword ptr [ESI - 0x4]        group 2, pair 0, left
//   00f99a6b  UCOMISS XMM0,dword ptr [ESI + 0x4]      group 2, pair 0, right
//   00f99a6f  LAHF
//   00f99a70  TEST AH,0x44
//   00f99a73  JNP 0x00f99a83                         not exactly equal -> skip pair 1
//   00f99a75  MOVSS XMM0,dword ptr [ESI]              group 2, pair 1, left
//   00f99a79  UCOMISS XMM0,dword ptr [ESI + 0x8]      group 2, pair 1, right
//   00f99a7d  LAHF
//   00f99a7e  TEST AH,0x44
//   00f99a81  JP  0x00f99aaf                          both pairs equal -> return 0
//   00f99a83  MOVSS XMM0,dword ptr [ESI + 0x5c]       group 3, pair 0, left
//   00f99a88  UCOMISS XMM0,dword ptr [ESI + 0x64]     group 3, pair 0, right
//   00f99a8c  LAHF
//   00f99a8d  TEST AH,0x44
//   00f99a90  JNP 0x00f99aa1                         not exactly equal -> skip pair 1
//   00f99a92  MOVSS XMM0,dword ptr [ESI + 0x60]       group 3, pair 1, left
//   00f99a97  UCOMISS XMM0,dword ptr [ESI + 0x68]     group 3, pair 1, right
//   00f99a9b  LAHF
//   00f99a9c  TEST AH,0x44
//   00f99a9f  JP  0x00f99aaf                          both pairs equal -> return 0
//   00f99aa1  INC EDI
//   00f99aa2  ADD ESI,0x10                           outer stride
//   00f99aa5  CMP EDI,0x6
//   00f99aa8  JL  0x00f99a30
//   00f99aaa  POP EDI
//   00f99aab  MOV AL,0x1                              return 1
//   00f99aad  POP ESI
//   00f99aae  RET
//   00f99aaf  POP EDI
//   00f99ab0  XOR AL,AL                               return 0
//   00f99ab2  POP ESI
//   00f99ab3  RET
//
// FRAME. Entry ESP is 0 in the walk. The prologue pushes ESI (entry-4); the one
// argument word is pushed at 0x00f999fc and is never dropped by the body, so the
// callee owns it; EDI is pushed at 0x00f99a24 (entry-8) only on the arm that reaches
// the loop, and every return site after that point pops it. Each of the three
// return sites is a bare `C3`.
//
//   * The first return site (0x00f999f6) is reached only from 0x00f999f1, i.e.
//     before the argument word is ever pushed, so the frame there is entry-4 and
//     `RET` returns to the caller with the callee having popped nothing.
//   * The other two (0x00f99aae, 0x00f99ab3) are reached only after 0x00f99a00,
//     whose argument word the callee popped, so the frame there is entry-4 again.
//
// Both statements are the same statement: at either of those two sites the ESP in
// effect is entry-4, so the bare `RET` consumes exactly the return address. That
// balance is the whole of the evidence for "this is zero-argument __thiscall with
// caller cleanup", and it is corroborated by the fact that no instruction in the 80
// ever reads a stack displacement other than the two the calls themselves set up.
//
// WHAT THE RETURN WORD IS. The three exits write AL only, so bits 8..31 of the
// return register are the last callee's word with its low byte cleared, and NO
// instruction in the loop writes the return register at all -- `MOVSS` and
// `UCOMISS` touch XMM0 and EFLAGS only. So on every path the high three bytes are
// the value 0x00f699b0 or a table slot returned, and the low byte is the flag. That
// is modelled as instrumentation (dead_return_word) rather than as the return value,
// because the declared 1-byte type promises only the low byte and because the two
// table slots' return widths are not statically knowable -- 0x00fa0e60 zeroes EAX
// before its SETNE, so its high bytes are 0, while a derived class's override is
// not bounded by anything in this image.
//
// GLOBALS: none declared, and that is not an omission. The only global this body
// touches is read inside 0x00f48a70 (`MOV EAX,ds:0x16c8eb0`), which is a different
// VA and a different body's span. Nothing in these 80 instructions names a
// data-segment address, and the model therefore declares none.
//
// VIRTUAL DISPATCH: two sites, both the canonical x86-32 shape and both resolved
// here. 0x00f999f7..0x00f99a00 and 0x00f99a0e..0x00f99a15 each load the object's
// own table pointer out of the receiver, load a word out of THAT at a fixed
// displacement, and call the register. So it is two levels in both cases: the word
// at the receiver's +0x00 is a table address and the slot displacement indexes a
// table, not the receiver. The table address this class uses is 0x01490be8 (read out
// of the image, and the source of the single xref at 0x01490c38 = 0x01490be8 + 0x50,
// this body's own slot). The entries that table holds at +0x4c and +0x30 are
// 0x00fa0e60 and 0x00fa0d80; those two addresses are recorded in the sidecar and are
// deliberately NOT called by name here, because a derived class's runtime object may
// hold different words at either slot and calling a fixed address would be a claim
// the listing does not make. What the listing fixes, and what the model does, is to
// call through whatever word the receiver's own +0x00 names -- read TWICE, at
// 0x00f999f7 and again at 0x00f99a0e, with the first table call in between, and the
// model re-reads it for exactly that reason (model test case P).
//
// THE COMPARE LOOP, and the one place the decompilation is not merely unhelpful but
// INVERTED. Every compare is the same eleven-instruction idiom, and it is worth
// writing out because the polarity is the whole body:
//
//   UCOMISS XMM0, [m32]     ; a ? b, with ZF=PF=CF=1 when either is NaN
//   LAHF                    ; AH bit6 = ZF, AH bit2 = PF
//   TEST AH,0x44            ; result AH & 0x44, and a FRESH parity from it
//   JNP / JP
//
// UCOMISS leaves (ZF,PF) at (0,0) for less and for greater, (1,0) for equal and
// (1,1) for unordered. So AH & 0x44 is 0x00, 0x40 or 0x44, and TEST overwrites the
// parity with the parity of THAT value: 0x00 has zero bits set (PF=0) and 0x44 has
// two (PF=0), while 0x40 has one (PF=1). Therefore:
//
//   JNP taken  <=>  the pair is NOT ordered-equal   (less, greater, or unordered)
//   JNP missed <=>  the pair IS ordered-equal       (equal, and not NaN)
//
// In the pair-0 blocks the branch is JNP and the fall-through is the pair-1 block,
// so pair 1 is only examined when pair 0 IS ordered-equal. In the pair-1 blocks the
// branch is JP, and JP is taken exactly when that pair IS ordered-equal, and it
// targets 0x00f99aaf, which returns 0. So:
//
//   a group rejects iff BOTH of its pairs are ordered-equal, and the body returns 0
//   at the first group that does.
//
// Ghidra's decompilation of this VA reads the same eleven instructions as
// "if (left != right) { if (left2 != right2) return 0; }" -- i.e. it puts the
// fall-through on the NOT-equal side and the early return on the both-unequal side,
// which is the exact complement, and the complement is not a harmless reading: one
// rejects a group where a single pair is equal and the other rejects a group where
// neither is. The listing is followed here, and the two are separately settled by
// the corroborating listing of 0x00f699b0 (this body's own second direct callee),
// which repeats the idiom with `JP` on BOTH pairs and a shared `XOR AL,AL ; POP ESI
// ; RET` at 0x00f69a20 -- the same rejection this body makes, reached from a
// different branch polarity per block. Model test case H drives all four
// pair-1/pair-0 combinations, which is the only way the two readings can be told
// apart.
//
// ORDERED equality, and why the model may write C++ `==`. C++ `==` on `float` is
// false for unordered, so `a == b` IS the machine's exactly-equal test, and the
// model uses it directly. The two cases where a byte-wise or bitwise reading of the
// same four bytes would disagree, and the model test drives both: +0.0f against
// -0.0f is ordered-equal (so the group rejects) while their bit patterns differ,
// and a quiet NaN against the same bit pattern is ordered-unequal (so the group
// passes) while their bytes are identical. The body never writes MXCSR, so the
// default applies and a denormal compares normally; that is stated and not modelled.
//
// GROUP LAYOUT, and why the receiver record cannot corroborate it. Four groups per
// outer iteration, at outer_cursor - 0xc4, outer_cursor - 0x64, outer_cursor - 0x4
// and outer_cursor + 0x5c: the first two are the inner loop's two steps and the last
// two are the two unrolled groups, and consecutive bases are 0x60 apart in all four
// cases, which is also the inner stride at 0x00f99a5e. A group base g is read as four
// floats at g, g+4, g+8 and g+0xc. With the outer stride 0x10 and the outer cursor
// at receiver + 0x438, the twenty-four bases this body scans are receiver +
// 0x374 + 0x10i, 0x3d4 + 0x10i, 0x434 + 0x10i and 0x494 + 0x10i, for i in 0..5, so
// the scan spans receiver + 0x374 .. receiver + 0x4f0.
//
// The machine-derived receiver record enumerates [0, 0x370, 0x434, 0x438, 0x43c,
// 0x440, 0x494, 0x498, 0x49c, 0x4a0, 0x4f4] -- which is the two DIRECT groups of
// outer index 0, the two flag bytes, the table word and the outer cursor. The two
// inner groups' bases are absent, and the reason is visible in the listing rather
// than guessed: the scan that built the record loses the ESI alias at `POP ESI` on
// the first return path (0x00f999f5), which is a write to ESI, and every later
// access is then unattributable to the receiver. So the record is not contradicting
// the layout derived here, it is blind to half of it, and the listing is the
// authority. The model test's case K pins the covered set from both sides: all
// twenty-four scanned bases reject, and the neighbouring bases that are NOT scanned
// do not.
//
// RECEIVER WRITES: none. The 80 instructions contain no memory-destination operand
// at all -- every `MOVSS`/`UCOMISS` is a read, both `MOV EAX,[ESI]` are reads, both
// `MOV EDX,[EAX+...]` are reads, and both `CMP BYTE PTR [ESI+...]` are reads. The one
// memory write in the whole body is the `PUSH 0x7` onto the stack. The record agrees
// (receiver.written_through 0) and the model test asserts it byte for byte over the
// whole modelled receiver.

#include "sw2_00f999e0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00f999e0 {
namespace {

// Model instrumentation, not machine state: the composed return register, and the
// last callee's word it is composed from. Only the first is published, through
// dead_return_word(); the second is kept separately so the composition can be written
// once and read in one place, and so the two are never confused for each other in a
// reading of this file. They live at namespace scope because nothing else reads them
// and a local written and never read is a warning under -Wall.
std::uint32_t g_dead_return_word = 0;
std::uint32_t g_last_callee_word = 0;

// Every exit composes the return register the same way -- one flag byte over the last
// callee's word masked to its high 24 bits -- so the composition is written once here
// and read by the accessor the model test publishes. A free function rather than a
// lambda because both words have static storage duration, which a lambda may not
// capture. See THE RETURN WORD note above.
std::uint8_t finish(std::uint8_t flag) {
  g_dead_return_word = (g_last_callee_word & kDeadHighBytesMask) | flag;
  return flag;
}

}  // namespace

std::uint32_t dead_return_word() { return g_dead_return_word; }

// The four floats of one group, compared as two pairs. `pair` 0 is the pair at the
// group base and `pair` 1 is the pair four bytes later, which is the layout every one
// of the four group sites in the listing uses.
bool group_pair_ordered_equal(const std::uint8_t* group, unsigned pair) {
  const std::size_t low = static_cast<std::size_t>(pair) * kPairStride;
  return real_at(group, low) == real_at(group, low + kPairSpan);
}

// One group, and the decision the eleven instructions make. 0x00f99a4d's JNP skips
// the second compare unless the first pair is ordered-equal, and 0x00f99a5b's JP
// leaves the body when the second one is. See THE COMPARE LOOP above; the two are
// the only reasons this returns true.
bool group_rejects(const std::uint8_t* group) {
  if (!group_pair_ordered_equal(group, 0)) {
    return false;  // 00f99a4d  JNP 0x00f99a5d
  }
  if (!group_pair_ordered_equal(group, 1)) {
    return false;  // 00f99a5b  JP 0x00f99aaf, not taken
  }
  return true;  // 00f99a5b  JP 0x00f99aaf, taken
}

extern "C" std::uint8_t PKG_SW2_00F999E0_THISCALL re_00f999e0(Receiver* receiver) {
  // 00f999e1  MOV ESI,ECX
  //
  // ESI is the receiver alias and every receiver access in the body goes through it;
  // ECX is then handed to 0x00f699b0 and to both table slots, which is why the
  // machine-derived receiver record names register ECX with shape R-ALIAS. The
  // receiver is an opaque byte run: the record is bounds_only, so it says where the
  // body was seen reaching and not which member is which, and no member is named.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00f999e3  CALL 0x00f48a70
  //
  // Six bytes in the image: `MOV EAX,ds:0x16c8eb0 ; RET`. One global read, no stack
  // argument, no ECX use, EAX its only register written. The model declares the read
  // and not the value, and the model test supplies the value.
  //
  // 00f999e8  MOV ECX,EAX
  //
  // That value becomes the RECEIVER of the next call, one level down and a different
  // object from the receiver of this function: reading it as a member of `self`, or
  // as the receiver itself, would be a two-level error. It is a bare value from a
  // getter and the listing uses it only as ECX.
  void* const global_object =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(global_object_00f48a70()));

  // 00f999ea  CALL 0x00f699b0
  //
  // Zero-argument __thiscall on ECX. Its own bytes read [ECX+0x1ce] and
  // [ECX+ESI+0x78] and never a stack slot, and it ends `POP ESI ; RET`.
  g_last_callee_word = global_predicate_00f699b0(global_object);

  // 00f999ef  TEST AL,AL
  // 00f999f1  JNZ 0x00f999f7
  //
  // All EIGHT bits of AL, not bit 0. That matters at 0x00f99a06 below, and the model
  // test drives a callee that returns 0x00000100 -- a word whose low byte is zero and
  // whose bit 0 is zero, and one whose bit 0 is clear while AL is not -- to separate
  // the two readings.
  if (static_cast<std::uint8_t>(g_last_callee_word) == 0) {
    // 00f999f3  XOR AL,AL
    // 00f999f5  POP ESI
    // 00f999f6  RET
    return finish(0);
  }

  // 00f999f7  MOV EAX,dword ptr [ESI]
  //
  // The receiver's word at +0x00, which is a TABLE ADDRESS and not a function
  // pointer. Two levels follow from here, and both are the kind of thing a
  // reconstruction gets wrong by reading one: the slot displacement indexes the
  // table, and the call target is a word of that table. The model test's decoys for
  // this case are a function planted at the receiver's own +0x00 and a second
  // function planted at the table's slot +0x00.
  const Word* const table = reinterpret_cast<const Word*>(
      static_cast<std::uintptr_t>(word_value_at(self, kTableWordDisplacement)));

  // 00f999f9  MOV EDX,dword ptr [EAX + 0x4c]
  const Word target_4c = load_slot(table, 0x4c);
  SlotFirst slot_4c = nullptr;
  std::memcpy(&slot_4c, &target_4c, sizeof slot_4c);

  // 00f999fc  PUSH 0x7
  // 00f999fe  MOV ECX,ESI
  // 00f99a00  CALL EDX
  //
  // One argument word, the byte 7, and the receiver in ECX. The body never drops the
  // word, so the callee owns it: the entry this class's table holds at +0x4c is
  // 0x00fa0e60 and it ends `RET 0x4`, reading the argument as a byte with
  // `MOV DL,[ESP+0x4]`. The model test's observer measures both -- the identity in
  // ECX and the value at entry+4 -- from inside the call.
  g_last_callee_word = slot_4c(receiver, kFirstSlotSelector);

  // 00f99a02  TEST AL,AL
  // 00f99a04  JNZ 0x00f999f3
  //
  // Gate 2, and note the polarity: this one is 0 -> return 0. A reconstruction that
  // reuses the first gate's polarity here returns the complement of the machine.
  if (static_cast<std::uint8_t>(g_last_callee_word) != 0) {
    return finish(0);
  }

  // 00f99a06  CMP byte ptr [ESI + 0x370],AL
  // 00f99a0c  JNZ 0x00f999f3
  //
  // Gate 3, and the comparison is against AL rather than against an immediate. AL is
  // provably zero here: 0x00f99a02's TEST and 0x00f99a04's JNZ not taken together
  // mean the byte the slot returned is 0x00. The model compares against zero and says
  // why, and the model test drives a slot that returns 0x00000000 to show the byte
  // is read on that path, and a slot that returns 0x00000001 to show the path is
  // never taken when AL is nonzero.
  if (*byte_at(self, kFirstFlagDisplacement) != 0) {
    return finish(0);
  }

  // 00f99a0e  MOV EAX,dword ptr [ESI]
  //
  // The table pointer, READ AGAIN, with the first table call in between. The model
  // re-reads it rather than reusing the word loaded before 0x00f999f7, because the
  // listing does: nothing in this body prevents the slot at +0x4c from having
  // rewritten the receiver's +0x00, and the model test case P makes it do exactly
  // that and requires the second call to go to the SECOND table.
  const Word* const table_again = reinterpret_cast<const Word*>(
      static_cast<std::uintptr_t>(word_value_at(self, kTableWordDisplacement)));

  // 00f99a10  MOV EDX,dword ptr [EAX + 0x30]
  const Word target_30 = load_slot(table_again, 0x30);
  SlotSecond slot_30 = nullptr;
  std::memcpy(&slot_30, &target_30, sizeof slot_30);

  // 00f99a13  MOV ECX,ESI
  // 00f99a15  CALL EDX
  //
  // No argument word this time, and the model test's second observer measures that
  // there is nothing at entry+4 to read.
  g_last_callee_word = slot_30(receiver);

  // 00f99a17  TEST AL,AL
  // 00f99a19  JZ  0x00f999f3
  //
  // Gate 4, nonzero -> keep going. Its polarity is the opposite of gate 2's and the
  // same as gate 1's.
  if (static_cast<std::uint8_t>(g_last_callee_word) == 0) {
    return finish(0);
  }

  // 00f99a1b  CMP byte ptr [ESI + 0x4f4],0x0
  // 00f99a22  JZ  0x00f999f3
  //
  // Gate 5, against an immediate this time, and nonzero -> keep going.
  if (*byte_at(self, kSecondFlagDisplacement) == 0) {
    return finish(0);
  }

  // 00f99a24  PUSH EDI
  // 00f99a25  XOR EDI,EDI
  // 00f99a27  ADD ESI,0x438
  //
  // The outer cursor is the receiver plus a fixed displacement, and the outer index
  // is a plain counter. The model keeps the receiver and the counter and recomputes
  // the cursor, where the machine keeps the cursor and the counter; the two are the
  // same value and the recomputation is what lets the model test plant a group at an
  // absolute offset. 0x00f99a2d's `LEA ECX,[ECX]` (bytes 8D 09) is a two-byte no-op
  // and is not modelled.
  for (unsigned outer_index = 0; outer_index < kOuterCount; ++outer_index) {
    std::uint8_t* const outer =
        self + kOuterCursorDisplacement + outer_index * kOuterStride;

    // 00f99a30  XOR EDX,EDX
    // 00f99a32  LEA ECX,[ESI + 0xffffff40]
    // 00f99a38  JMP 0x00f99a40
    //
    // 0xffffff40 is -0xc0, so the inner cursor starts 0xc0 below the outer one, and
    // the JMP is the loop rotation. 0x00f99aa8's JL targets 0x00f99a30, so the inner
    // counter is re-zeroed for every outer iteration, exactly as written.
    std::uint8_t* inner = outer - kInnerBackDisplacement;

    // 00f99a40..00f99a64
    //
    // Two iterations, 0x60 apart, and the two group bases are 0x60 apart, which is
    // why one stride constant serves both the cursor and the layout. The bound is a
    // signed JL against a counter incremented first, so the inner loop visits exactly
    // indices 0 and 1.
    for (unsigned inner_index = 0; inner_index < kInnerCount; ++inner_index) {
      if (group_rejects(inner - kGroupLead)) {
        // 00f99a5b  JP 0x00f99aaf
        return finish(0);
      }
      inner += kGroupStride;
    }

    // 00f99a66..00f99a81
    //
    // The third group, unrolled: its first float is at [ESI - 0x4], the same four
    // bytes below the outer cursor that the inner loop's first float is below its
    // cursor.
    if (group_rejects(outer - kGroupLead)) {
      // 00f99a81  JP 0x00f99aaf
      return finish(0);
    }

    // 00f99a83..00f99a9f
    //
    // The fourth group, also unrolled, 0x60 past the third one's base. Nothing in the
    // listing says why this pair is reached only when the third group did not reject
    // and why the first two are not; that is just the order the body has, and the
    // model reproduces it rather than reordering.
    if (group_rejects(outer + kFourthGroupOffset)) {
      // 00f99a9f  JP 0x00f99aaf
      return finish(0);
    }

    // 00f99aa1  INC EDI
    // 00f99aa2  ADD ESI,0x10
    // 00f99aa5  CMP EDI,0x6
    // 00f99aa8  JL  0x00f99a30
  }

  // 00f99aaa  POP EDI
  // 00f99aab  MOV AL,0x1
  // 00f99aad  POP ESI
  // 00f99aae  RET
  //
  // Only AL is written, so the high three bytes recorded above are left in place and
  // the published word has bit 0 set. The model test reads both halves from one
  // place.
  return finish(1);
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f999e0
