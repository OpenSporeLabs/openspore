// PKG-SWARM-W1-00ECC620 -- VA 0x00ecc620
// The vector deleting destructor of one Sporepedia::AssetData object
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 26 instructions, 0x00ecc620..0x00ecc676 inclusive
// (ghidra_function.body_start 0x00ecc620, body_end 0x00ecc676, size 87). Every
// line of the model below is annotated with the instruction it comes from. The
// listing this was written against was re-derived from the image bytes for this
// package rather than taken on trust, and it reproduces the 26 committed
// instructions at the same addresses with the same lengths, targets and
// displacements (see the header for the full listing).
//
//   ecc620: 56                    push   esi
//   ecc621: 8b f1                 mov    esi,ecx
//   ecc623: c7 06 b0 93 48 01     mov    DWORD PTR [esi],0x14893b0
//   ecc629: c7 46 10 9c 93 48 01  mov    DWORD PTR [esi+0x10],0x148939c
//   ecc630: c7 46 14 8c 93 48 01  mov    DWORD PTR [esi+0x14],0x148938c
//   ecc637: 8b 86 80 00 00 00     mov    eax,DWORD PTR [esi+0x80]
//   ecc63d: 8b 8e 88 00 00 00     mov    ecx,DWORD PTR [esi+0x88]
//   ecc643: 2b c8                 sub    ecx,eax
//   ecc645: 83 e1 fe              and    ecx,0xfffffffe
//   ecc648: 83 f9 02              cmp    ecx,0x2
//   ecc64b: 7e 0d                 jle    0xecc65a
//   ecc64d: 85 c0                 test   eax,eax
//   ecc64f: 74 09                 je     0xecc65a
//   ecc651: 50                    push   eax
//   ecc652: e8 29 ad 07 00        call   0xf47380
//   ecc657: 83 c4 04              add    esp,0x4
//   ecc65a: 8b ce                 mov    ecx,esi
//   ecc65c: e8 2f 5b 77 ff        call   0x642190
//   ecc661: f6 44 24 08 01        test   BYTE PTR [esp+0x8],0x1
//   ecc666: 74 09                 je     0xecc671
//   ecc668: 56                    push   esi
//   ecc669: e8 12 ad 07 00        call   0xf47380
//   ecc66e: 83 c4 04              add    esp,0x4
//   ecc671: 8b c6                 mov    eax,esi
//   ecc673: 5e                    pop    esi
//   ecc674: c2 04 00              ret    0x4
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk; the single `PUSH ESI` at
// 0x00ecc620 takes it to -4; each `PUSH`/`ADD ESP,0x4` pair around a 0x00f47380
// call is balanced because that callee's terminator is a bare `C3`; and `RET 0x4`
// then lands ESP at +4, which is exactly the return address plus the one
// four-byte argument word. The frame balances to the byte.
//
//   entry+4  the one ordinary stack argument: a four-byte slot holding a word
//            whose low BYTE the body tests against 0x01 at 0x00ecc661. With
//            ESP = entry-4 at that point, entry-4 + 8 = entry+4, which is the
//            first ordinary argument slot; and `RET 0x4` is what pops it. Every
//            other bit of the word is ignored, which the model test drives.
//
// The prologue's `PUSH ESI` is the only thing that moves ESP below entry, so the
// same arithmetic is what fixes the displacement 0x8 and the mask 0x01. There is
// no local storage in this body: it allocates nothing and spills nothing.
//
// RECEIVER, as displacements and not as members. The machine-derived receiver
// record enumerates exactly {ECX, offsets [0, 16, 20, 128, 136], written_through
// 3, bounds_only true}, and the five accesses below are those five displacements
// and no others. Nothing at +0x04..+0x0f, +0x18..+0x7f, +0x81..+0x87 or +0x89
// onward is read or written.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 26
// instructions contain no register- or memory-operand transfer. The body WRITES
// three dispatch words and never reads one. The xref export carries a data-side
// reference from 0x014893b0, whose first word IS this body's address, and two
// code-side references from 0x00ecc603 and 0x00ecc613, which are
// `SUB ECX,0x10; JMP 0x00ecc620` and `SUB ECX,0x14; JMP 0x00ecc620` -- the two
// adjust-and-jump thunks for the subobjects at +0x10 and +0x14. All three are
// recorded in the header as layout evidence and none of them is modelled as a
// slot boundary, because the body never reads a dispatch word to dispatch on.
//
// GLOBALS: none. No instruction in the body names a data-segment address; the
// only absolute operands are the three table immediates, which are stores into
// the receiver and not reads of a global. (0x00f47380 reads the global 0x016c8b44,
// but that is a fact about the CALLEE, recorded in the header, and it is not a
// global this body touches.)

#include "sw1_00ecc620_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00ecc620 {

extern "C" OpaqueSporepediaAssetData* PKG_SWARM_W1_00ECC620_THISCALL re_00ecc620(
    OpaqueSporepediaAssetData* receiver, std::uint8_t deleting_flag) {
  // ecc621  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the two in the guard and the PUSH at 0x00ecc668. ECX
  // is reused as an argument register at 0x00ecc65a, which is why nothing here
  // reads a receiver field through ECX and why the machine-derived receiver record
  // reports register ECX with an alias shape.
  //
  // The receiver is taken as a byte run and every access below is a
  // DISPLACEMENT into it. The record is bounds_only: it says where the body was
  // seen reaching and not which member is which, so no member name is written for
  // any of the five.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // ecc623  MOV DWORD PTR [esi],0x14893b0
  *word_at(self, kReceiverWord00Displacement) = kObjectTableAt00;
  // ecc629  MOV DWORD PTR [esi+0x10],0x148939c
  *word_at(self, kReceiverWord10Displacement) = kObjectTableAt10;
  // ecc630  MOV DWORD PTR [esi+0x14],0x148938c
  *word_at(self, kReceiverWord14Displacement) = kObjectTableAt14;
  //
  // Three stores, three distinct displacements, three distinct constants, and the
  // first of them is not a duplicate of either of the others. Nothing else on the
  // receiver is written by this body, and in particular the words between them --
  // +0x04..+0x0c, +0x18 -- are left alone, which the model test checks by
  // comparing the receiver byte for byte.
  //
  // These three constants are what the class is re-pointed at on the way down,
  // and they are the same three the constructor at 0x00ecc780 installs (header,
  // CORROBORATION #1). They are values, not names: a constant is what the
  // instruction fixes.

  // ecc637  MOV EAX,DWORD PTR [esi+0x80]
  const Word span_begin = *word_at(self, kReceiverSpanBeginDisplacement);
  // ecc63d  MOV ECX,DWORD PTR [esi+0x88]
  const Word span_end = *word_at(self, kReceiverSpanEndDisplacement);
  //
  // Two words, READ ONCE EACH, and they are a pair: the begin of a run and its
  // end. Both are read before anything is written through either of them, and
  // neither is re-read afterwards -- the body does not zero them, does not
  // advance them and does not use them in the flag test.
  //
  // The pair is +0x80/+0x88 and not any other pair of displacements. The
  // constructor writes THREE words there (+0x80, +0x84, +0x88) and this body reads
  // the first and the third, skipping the middle one; a sibling function in the
  // same image, 0x00ecc530, reads +0x80 and +0x84 instead. The word at +0x84 is
  // therefore a real member that this body never looks at, and the model test
  // plants a decoy there which must stay inert.

  // ecc643  SUB ECX,EAX
  // ecc645  AND ECX,0xfffffffe
  // ecc648  CMP ECX,0x2
  // ecc64b  JLE 0xecc65a
  //
  // The distance, end minus begin, as a 32-bit subtraction that WRAPS: the SUB
  // does not trap and the AND does not restore anything. The AND then clears bit
  // 0, so the compared quantity is even; the CMP is against the literal 2; and the
  // branch is `JLE`, a SIGNED less-or-equal, so the body proceeds only when the
  // masked distance is a signed value strictly greater than two.
  //
  // The mask and the bound are a matched pair and the pair is what the test
  // exercises at its boundary. Masked, the distances 0, 1, 2 and 3 all become 0,
  // 0, 2 and 2 and all four are rejected; 4 and 5 become 4 and 4 and both are
  // accepted; and a distance whose top bit is set (0x80000000 and above) is
  // rejected as a negative signed value even though it is enormous unsigned. That
  // last pair of facts is where a reconstruction that read `JLE` as unsigned goes
  // wrong, and the test drives exactly those inputs.
  //
  // What the pair MEANS is a data-shape test and not an element count: the
  // quantity is a byte distance, never divided by anything, and a model that
  // divided it by an element size would answer differently at distance 4. The
  // constructor's own initialisation -- 0x01667bac into +0x80 and 0x01667bae into
  // +0x88, a distance of exactly 2 -- is the rejected case, i.e. the freshly
  // constructed object owns nothing to release.
  //
  // ecc64d  TEST EAX,EAX
  // ecc64f  JE 0xecc65a
  //
  // The second guard, and it is on the BEGIN word, not on the distance. A null
  // begin is skipped even when the span test passed, so the two guards are
  // independent and neither implies the other.
  if (span_requires_deallocation(span_begin, span_end)) {
    // ecc651  PUSH EAX
    // ecc652  CALL 0xf47380
    //
    // The begin word, by value, and it is the BEGIN and not the end: the register
    // pushed here is the one loaded at 0x00ecc637, while the end word is consumed
    // in place by the SUB. The callee is cdecl -- its terminator is a bare `C3` at
    // 0x00f47394 -- so the word stays on the stack across the call.
    //
    // ecc657  ADD ESP,0x4
    //
    // The caller-side drop of that one word, and it is the first instruction after
    // the call, so nothing the callee left in EAX is disturbed by it. EAX is dead
    // afterwards either way: the next thing the body does with a register is
    // `MOV ECX,ESI` at 0x00ecc65a, and the branch at 0x00ecc64b skips straight
    // there without touching EAX.
    sporepedia_free_00f47380(span_begin);
  }

  // ecc65a  MOV ECX,ESI
  //
  // The receiver goes back into ECX. This is not redundant bookkeeping: ECX was
  // the argument register the guard above used, and the base destructor is
  // __thiscall, so the receiver has to be reloaded into it.
  //
  // ecc65c  CALL 0x642190
  //
  // The base-class destructor, and it runs on BOTH arms -- reached by falling
  // through the guard and by branching over it at 0x00ecc64b. It is the only
  // unconditional call in the body, and it takes NO stack argument: the callee's
  // last two instructions are `POP ESI` (0x00642204) and `JMP 0x006412a0`
  // (0x00642205), a tail jump that cannot be popping a caller's argument.
  //
  // It is called with the receiver still carrying the three words this body just
  // stored, so a trace sees 0x014893b0 / 0x0148939c / 0x0148938c at +0x00, +0x10
  // and +0x14 at the moment of entry. The model test's observer samples them
  // there, which is how the ordering of the three stores against this call is
  // asserted rather than assumed.
  sporepedia_asset_destroy_00642190(receiver);

  // ecc661  TEST BYTE PTR [esp+0x8],0x1
  //
  // One BYTE of the entry+4 word, against the immediate 0x01. Bit 0 is the only
  // bit examined: the test reads a single byte of a four-byte slot and the mask
  // covers one bit of that byte, so every other bit of the word is invisible to
  // this body. The model takes the flag as a std::uint8_t for that reason and the
  // test drives values whose high bits differ.
  //
  // Note that the callee above has run by the time this test happens. The flag
  // therefore gates only the storage release, never any part of the class chain.
  //
  // ecc666  JE 0xecc671
  if ((deleting_flag & kDeletingFlagMask) != 0u) {
    // ecc668  PUSH ESI
    // ecc669  CALL 0xf47380
    //
    // The RECEIVER, by value -- and this is the one place in the body where a
    // two-level mistake is available and would be silent. ESI still holds the
    // pointer it was given at 0x00ecc621; it was never reassigned, and the word
    // that 0x00ecc623 stored at [ESI] did not change what ESI points at. Pushing
    // `*word_at(self + 0x00)` instead of `receiver` would hand the deallocator a
    // table address (0x014893b0 before the base destructor runs, whatever the
    // base destructor left behind afterwards) and the observable difference is
    // nil from the body's point of view, so only a test that poisons the stored
    // word can tell the two apart. It does.
    //
    // Order matters here too: this call comes AFTER the base destructor, so by the
    // time the storage is released the whole class chain has already run. The
    // model test asserts that order explicitly.
    //
    // ecc66e  ADD ESP,0x4
    //
    // The caller-side drop of the receiver word, the same cdecl rule as the guard
    // above and for the same reason.
    sporepedia_free_00f47380(reinterpret_cast<Word>(receiver));
  }
  // ecc666  JE 0xecc671 falls in here when bit 0 of the flag is clear.

  // ecc671  MOV EAX,ESI
  //
  // The join, after the flag branch. It runs on both arms, so EAX holds the
  // receiver on every path out of this body -- which is why the declared return
  // type is a pointer to the receiver and not void. The value is read out of the
  // alias register and not re-read from the word at +0x00, for the same reason
  // the PUSH above used ESI.
  //
  // ecc673  POP ESI
  // ecc674  RET 0x4
  //
  // The epilogue, unmodelled: it restores the register the prologue saved and
  // returns past the one four-byte argument word. The `RET 0x4` is the
  // callee-side cleanup the ABI record reports (stack_cleanup_bytes 4, owner
  // callee), and it is the last byte of the body.
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ecc620
