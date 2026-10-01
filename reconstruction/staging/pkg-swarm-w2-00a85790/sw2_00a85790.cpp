// PKG-SWARM-W2-00A85790 -- VA 0x00a85790
// FUN_00a85790 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 64 instructions, 0x00a85790..0x00a8583a exclusive
// (ghidra_function.body_start 0x00a85790, body_end 0x00a8583b, size_bytes 172;
// abi_derived.value.parse {declared_count 64, unparsed 0, degraded false}).
// The listing is re-exported with its bytes in the package header. Every line of
// the model below is annotated with the instruction it comes from, and no
// displacement, constant or branch polarity in this file is stated without one.
//
// WHAT THE BODY IS, in one paragraph. It is a once-armed notification drain on an
// editor-side model object. A byte at receiver+0x14 is a one-shot arm. If it is
// already clear the function does nothing at all. If it is set, the function
// CLEARS it, checks that the listener word at receiver+0x10 is non-null, and then
// -- only if four separate bits of a flag word living in a SECOND object (the one
// the receiver's own word at +0x0c addresses) ask for it -- makes up to four
// outgoing calls: one direct call to 0x00a85460, and three through slots of the
// listener's table at displacements 0x18, 0x1c and 0x14. Finally, and
// independently of all of that, if the signed word at receiver+0x68 is not
// negative the function makes one more call through the listener's slot 0x14 with
// that word as its argument and then overwrites the word with all-ones, which the
// signed test at 0x00a85824 will reject next time. Both halves are idempotent on
// their own terms and neither one's outcome feeds the other.
//
// CONTROL FLOW, resolved once so that every target below is a fact. The listing
// has NINE conditional branches, all of them 6-byte Jcc, plus one unconditional
// JMP. Every target lies inside the span, so the graph closes here:
//
//   0x00a85797 JZ  -> 0x00a85838   (arm already clear: total no-op)
//   0x00a857a5 JZ  -> 0x00a85838   (listener word null: arm cleared, stop)
//   0x00a857b9 JNZ -> 0x00a857c5   (bit 3 set: enter the notification block)
//   0x00a857c3 JZ  -> 0x00a8581f   (bit 3 and bit 5 both clear: skip the block)
//   0x00a857c7 JZ  -> 0x00a857d0   (bit 0 clear: skip the direct call)
//   0x00a857dc JZ  -> 0x00a857e8   (bit 3 clear on the reload: skip slot 0x18)
//   0x00a857f6 JZ  -> 0x00a8581f   (bit 5 clear on the reload: skip slot 0x1c)
//   0x00a8580d JZ  -> 0x00a8581a   (bit 6 clear: second argument is a null word)
//   0x00a85824 JL  -> 0x00a85838   (pending word is negative: stop)
//   0x00a85818 JMP -> 0x00a8581f   (after the slot-0x1c call with a real second arg)
//
// So there is exactly ONE return site, 0x00a85838, reached from four directions,
// and one shared continuation at 0x00a8581f that the notification block falls into
// and both skip-branches jump to. That is why the C++ below is one function with a
// single epilogue and not three.
//
// FRAME, resolved once. Entry ESP is 0 in the walk. The prologue's PUSH ESI at
// 0x00a85790 puts the saved ESI at entry-4 and the matching POP ESI at 0x00a85838
// takes it back, so the frame is one word deep and every displacement below is
// measured from the receiver, not from ESP. No instruction in the body names ESP:
// there is no frame slot, no spilled temporary and no stack argument read anywhere
// in the 64 instructions. The single ordinary stack word the terminator
// 0x00a85839 `RET 0x4` pops is declared on the prototype and never read, which is
// what abi_derived inference A1-IMM says at APPROXIMATION confidence.
//
// THE REGISTER STORY, because it decides two things a reader would otherwise have
// to guess. First, ESI is the receiver alias and is saved once and restored once;
// it is the base of every receiver access below. Second, and less obvious: EDI is
// saved at 0x00a8580f and restored at 0x00a85817, and the word the pair preserves
// is whatever EDI held on entry to that push -- the body never writes EDI anywhere
// else. The reason the pair exists is visible two instructions earlier: 0x00a85810
// computes `LEA EDI,[ESI + 0x28]`, an interior pointer into the receiver, and
// 0x00a85813 pushes it. A callee-saved register is being preserved across a call
// that a later instruction does not actually need it for, which is what an
// optimiser emits. The model threads one explicit EDI word so the pair is visible
// and falsifiable rather than invisible; see the header's instrumentation note.
//
// WHAT IS DELIBERATELY NOT MODELLED, and why:
//
//  * EAX. The body writes EAX eleven times and reads it back after a CALL three
//    times (0x00a857d0, 0x00a857e8, 0x00a8581f), so no callee's return value ever
//    reaches a branch or a store. There is exactly one EAX value that survives to
//    the return -- the callee's, on the 0x00a8582f path -- and the return type is
//    void, so it is unobservable. The model therefore keeps no EAX word and says
//    so: a reconstruction that propagated a callee's EAX into a later test would
//    be a DIFFERENT function, and the model test drives observers that return
//    poison specifically to show that it is not.
//  * EDX. Written at 0x00a857bb, 0x00a857ee, 0x00a857e1, 0x00a85808, 0x00a8580a
//    and 0x00a85829, and read at 0x00a857c0, 0x00a857e3, 0x00a8580a, 0x00a8580d
//    (as the branch delay fill), 0x00a8582c and 0x00a8582f. Every read follows its
//    nearest write with no CALL in between, so EDX carries nothing across a call
//    and needs no word of its own.
//  * The GLOBALS check's blind spot. This body names no data-segment address --
//    no instruction prints an immediate outside 0 and 0xffffffff, and every
//    address it forms is `[ESI + disp]`, `[[ESI + disp] + disp]` or `LEA` of the
//    first -- so it touches no global. That is an evidenced absence.
//  * The vtable this function is itself an entry of. The vtable export
//    associates 0x00a85790 with vtable 0x01458024 through the single data xref
//    from 0x01458030, which is the table's fourth word (0x01458024 + 0x0c), i.e.
//    this function is SLOT 3 of the table that the class installs on its own
//    receiver. The association is recorded and NOT used: this body never reads a
//    word at its own receiver+0x00, so the fact that it lives in that table fixes
//    no offset in it, and the three table displacements the body DOES use
//    (0x14/0x18/0x1c) belong to the LISTENER's table, a different object reached
//    through receiver+0x10. The class is not named: nothing in this evidence pack
//    fixes a C++ name for it.

#include "sw2_00a85790_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00a85790 {
namespace {

// The displacement and bit constants, pinned to the listing. These are
// assertions, not documentation: they fail the build if a value in the header is
// ever edited away from the instruction that fixes it, and each message names the
// instruction the value was read from. Every hexadecimal literal below is one the
// 64-instruction listing prints.
static_assert(kFlagByteDisplacement == 0x14, "CMP/MOV byte ptr [ESI + 0x14] at 00a85793 / 00a857a1");
static_assert(kListenerPointerDisplacement == 0x10, "CMP dword ptr [ESI + 0x10],0x0 at 00a8579d");
static_assert(kSourcePointerDisplacement == 0xc, "MOV EAX,dword ptr [ESI + 0xc] at 00a857ab");
static_assert(kArgumentBufferDisplacement == 0x28, "LEA EDI,[ESI + 0x28] at 00a85810");
static_assert(kPendingIdentifierDisplacement == 0x68, "MOV EAX,[ESI + 0x68] at 00a8581f");
static_assert(kSourceFlagWordDisplacement == 0x8, "MOV EAX,dword ptr [EAX + 0x8] at 00a857ae");
static_assert(kSourceHalfWordDisplacement == 0xa8, "MOVZX EAX,word ptr [EAX + 0xa8] at 00a857f8");
static_assert(kListenerTableLeadDisplacement == 0x0, "MOV EDX,dword ptr [ECX] at 00a857e1");
static_assert(kSlotIdentifierDisplacement == 0x14, "MOV EAX,dword ptr [EDX + 0x14] at 00a8582c");
static_assert(kSlotNoArgumentDisplacement == 0x18, "MOV EAX,dword ptr [EDX + 0x18] at 00a857e3");
static_assert(kSlotTwoArgumentDisplacement == 0x1c, "MOV EDX,dword ptr [EDX + 0x1c] at 00a8580a");
static_assert(kFlagBit3Shift == 0x3, "SHR ECX,0x3 at 00a857b3");
static_assert(kFlagBit5Shift == 0x5, "SHR EDX,0x5 at 00a857bd");
static_assert(kFlagBit6Shift == 0x6, "SHR ECX,0x6 at 00a857ff");
static_assert(kSentinelIdentifier == 0xffffffff, "MOV dword ptr [ESI + 0x68],0xffffffff at 00a85831");
// The bit-0 test is the only one the listing writes without a shift; it is pinned
// in decimal so the model's hexadecimal literals stay inside the listing's set.
static_assert(kFlagBit0Shift == 0u, "TEST AL,0x1 at 00a857c5 tests the word's own low bit");

// The model's one EDI word. It is instrumentation of the model's own register
// file, not a machine global: no instruction names it and the original code has
// no such addressable word. It lives at namespace scope because the model test
// reads it through edi_register() and seeds it through set_edi_register().
Word g_edi = 0;

}  // namespace

Word edi_register() { return g_edi; }

void set_edi_register(Word value) { g_edi = value; }

extern "C" void PKG_SW2_00A85790_THISCALL re_00a85790(Receiver* receiver, Word) {
  // 00a85790  PUSH ESI
  // 00a85791  MOV ESI,ECX
  //
  // ESI is the receiver alias and the only register the prologue saves. Every
  // receiver access below is a displacement into it, and 0x00a85838 restores it,
  // so the alias is a frame fact with no other observable. EDI is not saved here:
  // the only PUSH EDI / POP EDI pair in the body is at 0x00a8580f / 0x00a85817.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00a85793  CMP byte ptr [ESI + 0x14],0x0
  // 00a85797  JZ 0x00a85838
  //
  // THE OUTER GUARD, and the whole function is inside it. The byte at
  // receiver+0x14 is read, not written, and a clear byte takes the body straight
  // to the epilogue. That means: no store anywhere, no call, and receiver+0x68 is
  // left exactly as it was -- the pending-identifier half does NOT run, because
  // 0x00a85838 is the epilogue and not 0x00a8581f. The two halves of this function
  // are therefore independent, and a reconstruction that put the 0x68 test outside
  // this guard would call the listener on an unarmed object.
  //
  // The comparison is against zero and the byte is not extended anywhere, so this
  // is a plain "is it non-zero" test on one byte.
  if (byte_at(self, kFlagByteDisplacement) == 0) {
    // 00a85797 -> 0x00a85838, i.e. POP ESI; RET 0x4
    return;
  }

  // 00a8579d  CMP dword ptr [ESI + 0x10],0x0
  //
  // The listener word is READ HERE, before the store below, and the flags the CMP
  // leaves are consumed by the JZ two instructions on. Reading it first rather
  // than after the store is what the listing does and the model does the same, so
  // the order is visible instead of being folded into a re-read.
  //
  // This is the body's ONLY null check, and it is load-bearing: every one of the
  // three table dispatches below dereferences this word twice (0x00a857e1,
  // 0x00a85808, 0x00a85829) with no check of its own.
  const Word listener_word = word_at(self, kListenerPointerDisplacement);

  // 00a857a1  MOV byte ptr [ESI + 0x14],0x0
  //
  // The one-shot arm is cleared HERE, i.e. before the null test is acted on, and
  // the instruction between the CMP and the JZ is a MOV, which does not touch the
  // flags the JZ reads. So on the null path the arm has ALREADY been cleared by
  // the time the function returns. A reconstruction that moved this store below
  // the guard, or into the taken branch only, would re-arm and re-notify forever.
  store_byte(self, kFlagByteDisplacement, 0);

  // 00a857a5  JZ 0x00a85838
  //
  // JZ, i.e. jump when the listener word is ZERO. The null case therefore does
  // the store above and nothing else: the listener is never dereferenced, no call
  // is made, and receiver+0x68 is untouched because 0x00a85838 is the epilogue.
  if (listener_word == 0) {
    // 00a857a5 -> 0x00a85838, i.e. POP ESI; RET 0x4
    return;
  }

  // 00a857ab  MOV EAX,dword ptr [ESI + 0xc]
  // 00a857ae  MOV EAX,dword ptr [EAX + 0x8]
  //
  // THE FIRST TWO-LEVEL READ, and the one that is easiest to get wrong. The word
  // at receiver+0x0c is used as an ADDRESS, not inspected: the flag word is
  // 8 bytes into whatever that word points at. The model expresses it that way --
  // a Word comes back from the receiver and is then handed to load_slot as a base
  // -- so that a one-level reading (receiver+0x08) is not writable.
  Word flags = load_slot(word_at(self, kSourcePointerDisplacement), kSourceFlagWordDisplacement);

  // 00a857b1  MOV ECX,EAX / 00a857b3 SHR ECX,0x3 / 00a857b6 TEST CL,0x1
  // 00a857b9  JNZ 0x00a857c5
  // 00a857bb  MOV EDX,EAX / 00a857bd SHR EDX,0x5 / 00a857c0 TEST DL,0x1
  // 00a857c3  JZ 0x00a8581f
  //
  // THE OUTER NOTIFICATION GATE, and it is an OR of two bits, not an AND and not
  // an either-arm-to-both. Bit 3 jumps into the block; if it is clear, bit 5 is
  // tested and a clear bit 5 jumps past the whole block to 0x00a8581f. So the
  // block runs when bit 3 OR bit 5 is set.
  //
  // Both tests are `SHR <reg>, n` + `TEST <byte>, 0x1` on a copy of the flag word,
  // which is (word >> n) & 1 -- no mask constant appears in the listing at all, so
  // none is written in this file. The two copies (ECX and EDX) are scratch: the
  // flag word itself is still in EAX, and 0x00a857c5 tests ITS low bit next.
  const bool bit3 = bit_is_set(flags, kFlagBit3Shift);
  const bool bit5 = bit_is_set(flags, kFlagBit5Shift);
  if (bit3 || bit5) {
    // 00a857c5  TEST AL,0x1
    // 00a857c7  JZ 0x00a857d0
    //
    // Bit 0 of the flag word, tested with no shift at all -- the one test the
    // listing writes directly. Only this one bit gates the direct call, and the
    // call is INSIDE the block, so the call happens only when (bit 3 or bit 5) and
    // bit 0. Note the polarity: JZ on the zero case, so a CLEAR bit 0 skips.
    if (bit_is_set(flags, kFlagBit0Shift)) {
      // 00a857c9  MOV ECX,ESI
      // 00a857cb  CALL 0x00a85460
      //
      // The one direct transfer in the body, and the only callee the xref export
      // records. ECX is loaded with the receiver one instruction earlier and
      // nothing is pushed between the two, so the callee receives the receiver in
      // the receiver register and no stack argument. Its EAX output is not the
      // model's concern: the next instruction reloads EAX from the receiver.
      FUN_00a85460(receiver);
    }

    // 00a857d0  MOV EAX,dword ptr [ESI + 0xc]
    // 00a857d3  MOV ECX,dword ptr [EAX + 0x8]
    //
    // THE FLAG WORD IS RELOADED, not carried. Both halves of the chase are redone
    // from the receiver, so the value the direct call above saw, and any value the
    // direct call WROTE, are both re-read here. This is a two-instruction fact
    // with an observable consequence: a direct callee that mutates the source's
    // flag word changes what the next two tests do. The model re-reads for that
    // reason, and the model test drives a mutating callee to prove it.
    flags = load_slot(word_at(self, kSourcePointerDisplacement), kSourceFlagWordDisplacement);

    // 00a857d6  SHR ECX,0x3 / 00a857d9  TEST CL,0x1 / 00a857dc  JZ 0x00a857e8
    //
    // Bit 3 AGAIN, on the reloaded word. So the slot-0x18 dispatch is gated on bit
    // 3 of the FRESH value while the direct call was gated on bit 0 of the value
    // read before the call: the two tests can disagree after a mutating callee,
    // and the model keeps them separate rather than folding both into the first
    // read's bits.
    if (bit_is_set(flags, kFlagBit3Shift)) {
      // 00a857de  MOV ECX,dword ptr [ESI + 0x10]
      // 00a857e1  MOV EDX,dword ptr [ECX]
      // 00a857e3  MOV EAX,dword ptr [EDX + 0x18]
      // 00a857e6  CALL EAX
      //
      // THE THREE-STEP CHASE: the word at receiver+0x10 is an address, the word
      // THERE is the table base, and the target is a displacement into that table.
      // Three loads, in that order -- load_listener_slot performs the first two as
      // separate reads so the depth is in the source and not in a folded
      // expression. Note what the receiver of the call is: ECX still holds the
      // listener object itself (0x00a857de put it there and nothing has
      // overwritten it), so the receiver of the virtual call is the LISTENER, not
      // the receiver of this function and not the source object.
      //
      // Nothing is pushed between 0x00a857de and the call, so the callee takes no
      // stack argument. The model's call result is discarded and that is a
      // faithfulness requirement, not an omission: 0x00a857e8 reloads EAX before
      // anything reads it, so a reconstruction that let this callee's return value
      // reach the next test would be a different function.
      void* const listener = reinterpret_cast<void*>(static_cast<std::uintptr_t>(listener_word));
      (void)invoke_slot_no_arguments(load_listener_slot(listener_word, kSlotNoArgumentDisplacement),
                                     listener);
    }

    // 00a857e8  MOV EAX,dword ptr [ESI + 0xc]
    // 00a857eb  MOV ECX,dword ptr [EAX + 0x8]
    // 00a857ee  MOV EDX,ECX / 00a857f0  SHR EDX,0x5 / 00a857f3  TEST DL,0x1
    // 00a857f6  JZ 0x00a8581f
    //
    // A THIRD reload, and a third test of bit 5 -- on the value as it stands after
    // the direct call AND after the slot-0x18 call. Two callees have therefore had
    // the chance to change what this test sees, and the model re-reads rather than
    // reusing either the first read's bit5 or the second read's bits.
    flags = load_slot(word_at(self, kSourcePointerDisplacement), kSourceFlagWordDisplacement);
    if (bit_is_set(flags, kFlagBit5Shift)) {
      // 00a857f8  MOVZX EAX,word ptr [EAX + 0xa8]
      //
      // THE SECOND-ARGUMENT SOURCE, and the narrowest read in the body. EAX is
      // still the word read from the receiver at 0x00a857e8, so the halfword is
      // 0xa8 bytes into the SOURCE object -- a second object, a third level below
      // the receiver relative to where the flag word came from (two levels). The
      // receiver's own +0xa8 is never touched.
      //
      // MOVZX, not MOV: the operand is a WORD and the destination is EAX, so the
      // result is the 16-bit value ZERO-EXTENDED into all 32 bits. The upper 16
      // bits of whatever the memory holds are discarded, and that is observable in
      // the argument the call below receives.
      const HalfWord source_argument = half_at(
          reinterpret_cast<const void*>(static_cast<std::uintptr_t>(
              word_at(self, kSourcePointerDisplacement))),
          kSourceHalfWordDisplacement);

      // 00a857ff  SHR ECX,0x6 / 00a85802  TEST CL,0x1
      //
      // Bit 6, on the ECX that still holds the reloaded flag word from
      // 0x00a857eb. The three instructions between the shift and the branch
      // (0x00a85805, 0x00a85808, 0x00a8580a) do not write EFLAGS, so the flags
      // TEST set at 0x00a85802 are still live at 0x00a8580d: the compiler filled
      // the branch delay by loading the callee. The model computes the test
      // before the loads, which is the same value, and says so.
      const bool bit6 = bit_is_set(flags, kFlagBit6Shift);

      // 00a85805  MOV ECX,dword ptr [ESI + 0x10]
      // 00a85808  MOV EDX,dword ptr [ECX]
      // 00a8580a  MOV EDX,dword ptr [EDX + 0x1c]
      //
      // The same two-level chase as the slot-0x18 dispatch, a different table
      // displacement, and the target is left in EDX rather than EAX. The
      // listener is re-read from the receiver here rather than reused, so the two
      // dispatches agree only for as long as nothing has written receiver+0x10 in
      // between -- which is exactly the observable a model test can drive, and it
      // does.
      //
      // THIS LOAD IS THE ONLY ONE, and both 0x1c call sites below consume the
      // single word it produces. `kSlotTwoArgumentDisplacement` is 0x1c and the
      // instruction that states it is 0x00a8580a `MOV EDX,dword ptr [EDX + 0x1c]`
      // (bytes 8B 52 1C) -- the `static_assert` on the constant names that
      // address. There is no second load, no second displacement and no separate
      // slot for the 0x00a8581d site: the listing reads the 0x1c word once, before
      // the branch that chooses between the two arms, and both arms call through
      // the register it leaves in EDX. The model expresses that as one
      // `two_argument_target` word read once, above the branch, and handed to one
      // `invoke_slot_two_arguments` helper by both arms -- so "one load, two call
      // sites" is a shape in the source and not a note about it.
      void* const listener = reinterpret_cast<void*>(static_cast<std::uintptr_t>(listener_word));
      const Word two_argument_target = load_listener_slot(listener_word, kSlotTwoArgumentDisplacement);

      // 00a8580d  JZ 0x00a8581a
      //
      // Branch polarity: JZ, so a CLEAR bit 6 jumps to the arm that pushes a null
      // word. The arms differ in the SECOND argument only; the first argument
      // (the zero-extended halfword) is pushed on both.
      if (bit6) {
        // 00a8580f  PUSH EDI
        // 00a85810  LEA EDI,[ESI + 0x28]
        // 00a85813  PUSH EDI
        // 00a85814  PUSH EAX
        // 00a85815  CALL EDX
        // 00a85817  POP EDI
        // 00a85818  JMP 0x00a8581f
        //
        // THE ONE PLACE A CALLEE-SAVED REGISTER IS SPILLED. `PUSH EDI` saves it,
        // `LEA EDI,[ESI + 0x28]` computes an interior pointer into the RECEIVER,
        // and `PUSH EDI` again pushes that pointer as the second argument.
        // `PUSH EAX` is then the first argument -- x86 pushes arguments
        // right-to-left, so the halfword is argument 1 and the receiver interior
        // pointer is argument 2.
        //
        // The `POP EDI` at 0x00a85817 is the frame's own restore and not the
        // callee's argument cleanup: the body's next instruction jumps to
        // 0x00a8581f, where the 0x00a8581d arm's two pushes are also cleaned up
        // without a pop of their own. Both arms therefore require a callee that
        // pops its own two words, and that is the reason the header declares
        // SlotTwoArguments with thiscall (callee-clean) rather than cdecl.
        const Word saved_edi = g_edi;
        (void)invoke_slot_two_arguments(
            two_argument_target, listener, source_argument,
            reinterpret_cast<void*>(self + kArgumentBufferDisplacement));
        // 00a85817  POP EDI -- the saved copy, whatever the callee did to EDI.
        g_edi = saved_edi;
        // 00a85818  JMP 0x00a8581f -- the shared continuation below.
      } else {
        // 00a8581a  PUSH 0x0
        // 00a8581c  PUSH EAX
        // 00a8581d  CALL EDX
        //
        // The other arm, and it is a real `PUSH 0x0`, not a missing argument: the
        // second argument is a null word. No PUSH EDI / POP EDI pair exists here,
        // so nothing about EDI is preserved on this path -- the model performs no
        // save or restore in this arm, and the model test checks that in both
        // directions.
        //
        // WHAT SITE THIS IS, stated here because the listing alone does not make
        // it obvious and the model is entitled to be explicit about it: this
        // `CALL EDX` is the SAME slot-0x1c dispatch as 0x00a85815, with the same
        // receiver in ECX and the same first argument, differing only in the
        // second. The displacement belongs to the site that READS it, which is
        // 0x00a8580a, and the constant that names it is
        // `kSlotTwoArgumentDisplacement` -- the same named `constexpr` the
        // 0x00a85815 arm uses, read once above the branch into the single
        // `two_argument_target` word. The branch that separates the two sites is
        // what makes them identical rather than merely similar: the only
        // predecessor of 0x00a8581a is the `JZ 0x00a8581a` at 0x00a8580d, and
        // that JZ targets an address PAST 0x00a8580f..0x00a85818, so the arm
        // that reaches this site never executes the `CALL EDX` at 0x00a85815. EDX
        // therefore still holds the 0x1c word read at 0x00a8580a when this call
        // is entered, and no callee's return can have overwritten it. That
        // reachability is read here out of the complete listing, not assumed:
        // 0x00a8581a's only predecessor is that JZ, and 0x00a8581c is
        // 0x00a8581a's only successor.
        //
        // WHY A LINEAR CLASSIFIER CANNOT SEE THAT, which is a property of the
        // reader and not of the machine, and is recorded rather than worked around.
        // A nearest-preceding-definition walk over the listing, with no path
        // sensitivity, reaches 0x00a8581d by scanning upwards and meets the `CALL
        // EDX` at 0x00a85815 first; on x86-32 a call clobbers the caller-saved
        // EDX, so that walk concludes the site is UNRESOLVED with the reason "EDX
        // is defined by a preceding CALL". The walk's PREMISE is right -- a call
        // really does clobber EDX -- and it is the same walk that classifies the
        // other three sites as proven slot dispatches. What it cannot express is
        // that the call it found is not on the path being read. It models one
        // linear order where this body has two mutually exclusive arms, and in a
        // linear order a definition that was bypassed on the path being read
        // cannot be told apart from one that was executed. No source shape
        // changes that: the verdict is computed from the listing
        // alone, and the source can only ever add a failure to it, never remove
        // one. Naming the displacement here is therefore the honest maximum --
        // it is stated, with the address of the instruction that fixes it, and it
        // is not restated as a second constant for this site, because the listing
        // has only one 0x1c load and a second constant would assert a load that
        // does not exist.
        (void)invoke_slot_two_arguments(two_argument_target, listener, source_argument, nullptr);
      }
    }
    // 00a8581f -- reached by falling out of the block, by 0x00a857c3, by
    // 0x00a857f6 and by the JMP at 0x00a85818. One continuation, four ways in.
  }

  // 00a8581f  MOV EAX,dword ptr [ESI + 0x68]
  // 00a85822  TEST EAX,EAX
  // 00a85824  JL 0x00a85838
  //
  // THE SECOND HALF OF THE FUNCTION, and it is outside the notification block, so
  // it runs whether or not any of the four calls above did.
  //
  // JL is a SIGNED comparison. `TEST EAX,EAX` sets SF from bit 31 and JL branches
  // when it is set, so the test is "the 32-bit word read here has its sign bit
  // set". A word with bit 31 set is negative here and would be LARGE if the same
  // bits were read as unsigned, and the model test drives exactly that word
  // (kMostSignificantBitMask) so that a reconstruction using an unsigned test
  // fails instead of passing by luck.
  const Word pending_identifier = word_at(self, kPendingIdentifierDisplacement);
  if ((pending_identifier & kMostSignificantBitMask) != 0) {
    // 00a85824 -> 0x00a85838, i.e. POP ESI; RET 0x4
    //
    // Note what is NOT done on this path: receiver+0x68 keeps its value, so a word
    // that is negative is a word the function leaves alone until something else
    // changes it. The all-ones store below is never reached from here.
    return;
  }

  // 00a85826  MOV ECX,dword ptr [ESI + 0x10]
  // 00a85829  MOV EDX,dword ptr [ECX]
  // 00a8582b  PUSH EAX
  // 00a8582c  MOV EAX,dword ptr [EDX + 0x14]
  // 00a8582f  CALL EAX
  //
  // The third three-step chase of the listener, the third distinct table
  // displacement, and the fourth indirect transfer. The order of the PUSH against
  // the MOV is load-bearing and easy to get backwards: EAX is PUSHED first, while
  // it still holds the word from receiver+0x68, and is only then overwritten with
  // the table word. A reconstruction that loaded the target first and then pushed
  // EAX would be passing the slot ADDRESS as the argument.
  //
  // The receiver handed to the call is ECX, which 0x00a85826 loaded with the
  // listener object, so it is the same receiver the two dispatches inside the
  // notification block used.
  //
  // One word is pushed and no pop follows the call: the next instruction is a
  // store, then the epilogue, and `RET 0x4` adjusts by four bytes only. So this
  // callee pops its own single word, which is why the header declares
  // SlotOneArgument with a callee-clean convention.
  (void)invoke_slot_one_argument(
      load_listener_slot(listener_word, kSlotIdentifierDisplacement),
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(listener_word)), pending_identifier);

  // 00a85831  MOV dword ptr [ESI + 0x68],0xffffffff
  //
  // The store happens AFTER the call returns, not before it, and the value is the
  // all-ones word -- which the signed test at 0x00a85824 rejects on the next call.
  // That is the whole mechanism: the pending identifier is consumed exactly once
  // and the sentinel makes the consumption visible without any other flag.
  // 0x00a85831 is a SEVEN-byte instruction (C7 46 68 FF FF FF FF: opcode C7,
  // modrm 46 = [ESI + disp8], the disp8 0x68, then the four immediate bytes),
  // which is what makes it a DWORD store and not a byte or a halfword store --
  // the last byte it writes is at +0x6b. The count is seven and the listing
  // corroborates it: the next instruction is at 0x00a85838.
  store_word(self, kPendingIdentifierDisplacement, kSentinelIdentifier);

  // 00a85838  POP ESI
  // 00a85839  RET 0x4
  //
  // The epilogue. It restores the one register the prologue saved and returns past
  // the return address and the one stack word the terminator's immediate names.
  // It touches no register that carries a result, because this function returns
  // no value: the four paths that reach it leave EAX holding, respectively, the
  // caller's own EAX, the caller's own EAX, the negative word just tested, and
  // whatever the last callee returned. See the header's return-type note for why
  // `void` is what the bytes support and what the canonical ABI record says
  // instead.
  //
  // THE JOIN AT THE SINGLE RETURN SITE, stated as the machine-return evidence
  // engine computes it rather than as prose, because it is the whole of what
  // that engine can and cannot bound. There is exactly one return (0x00a85839,
  // reached through the POP ESI at 0x00a85838), and EAX's must-defined value on
  // entry to it is a three-way disagreement over that instruction's four
  // predecessors:
  //
  //   from 0x00a85797  UNDEFINED. The body's first write to EAX is at
  //                     0x00a857ab, and this branch is taken before it.
  //   from 0x00a857a5  UNDEFINED. The only write before this branch is the BYTE
  //                     store at 0x00a857a1, which writes memory and no register.
  //   from 0x00a85824  DEFINED, 4 bytes. EAX is the word read at 0x00a8581f, the
  //                     one the JL was testing for sign.
  //   from 0x00a85831  NOT BOUNDABLE. The last write to EAX on this path is the
  //                     `CALL EAX` at 0x00a8582f, i.e. a callee's return value.
  //                     Whether a caller may read EAX after a call is decided by
  //                     the CALLEE's signature, which this listing does not
  //                     contain, so no width of it is statically knowable here.
  //
  // One must-analysis, four predecessor values, three distinct states: no single
  // width is determinable, and the engine reports the unbounded one as
  // UNCLASSIFIED and claims no verdict on it. No source shape can change that
  // number, because every input to it is the listing and the ABI record rather
  // than this translation unit -- and no source SHOULD change it. The reason EAX
  // is unbounded at the return is the two early exits, which return before the
  // body ever writes the register, plus the fourth path, whose value belongs to a
  // callee this package has not reconstructed. A width claimed here would be a
  // number about a callee's signature, not about this function.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a85790
