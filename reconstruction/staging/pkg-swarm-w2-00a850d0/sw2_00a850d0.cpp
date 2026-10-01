// PKG-SWARM-W2-00A850D0 -- VA 0x00a850d0
// FUN_00a850d0 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000,
// binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The complete body: 81 instructions, 0x00a850d0..0x00a851c1 inclusive = 242
// bytes, re-read out of the image for this package (PE .text, RVA 0x6850d0,
// file offset 0x6844d0). The header carries the byte-for-byte listing; every line
// of the model below is annotated with the instruction it comes from.
//
// WHAT THE BODY DOES, in one paragraph, so a reader can check the model against
// the listing rather than against this sentence. It is a re-entrancy-guarded tick
// on a receiver held in ECX. If the receiver's byte at displacement 0x14 is
// already non-zero it returns immediately, writing nothing. Otherwise it sets
// that byte to 1, reads a dispatch object out of the receiver's word at
// displacement 0x10, and -- if that word is non-zero -- reads a "carrier" object
// out of the receiver's word at displacement 0x0c and dispatches up to three
// methods on the dispatch object, each through a table reached by reading the
// dispatch object's own lead dword, and each guarded by a single bit of the
// carrier's flag word at its displacement 0x08. It then writes a shared tail:
// two zeroed floats on the receiver, and a third that is the reciprocal of the
// carrier's float at displacement 0x10 when that float compares strictly greater
// than zero and zero otherwise. One of the three dispatches stores its result on
// the receiver, and a negative result there resets the guard byte and returns
// early, skipping the tail. The value returned travels in XMM0 on every path that
// writes it and is left untouched on the guard path.
//
// WHAT IS THE POINT OF WRITING IT THIS WAY, stated before the code rather than
// after it. Three things in this body are easy to get wrong in a way that still
// compiles, still runs and still looks plausible, and the model keeps all three
// visible instead of tidying them away:
//
//  1. THE RECEIVER'S WORD AT 0x0c IS READ FOUR TIMES, AND THE CARRIER IT POINTS
//     AT IS A DIFFERENT OBJECT EACH TIME. 0x00a850e9, 0x00a850fe, 0x00a85130 and
//     0x00a8515f are four separate `MOV EAX,[ESI+0xc]`, and the body calls out
//     through a pointer between the first and the second, between the second and
//     the third, and between the third and the fourth. So the flag word tested for
//     bit 2, the flag word tested for bit 4, the halfword pushed to the bit-4
//     call, the flag word tested for bit 1, both stack arguments of the bit-1-set
//     call, the float guarding the bit-1-clear call, and the float whose
//     reciprocal lands on the receiver are each read through a carrier that a
//     callee can replace. A model that reads the pointer once and caches the
//     object is a DIFFERENT function whenever a callee writes the receiver, and
//     nothing in this listing says the callees do not. The model re-reads at each
//     of the four points and the model test drives the swap from inside a callee.
//
//  2. THE RECEIVER'S WORD AT 0x10 IS READ FOUR TIMES TOO, AND THE SECOND, THIRD
//     AND FOURTH READS HAPPEN INSIDE THE ARGUMENT-SETUP OF A CALL. 0x00a8511b,
//     0x00a8514a and 0x00a851a0 each reload it, and each of those is between a
//     previous transfer and the next one. The first dispatch at 0x00a850fc does
//     NOT reload it, because 0x00a850f7 is `MOV EAX,[ECX]` and leaves ECX alone
//     -- so the first call's receiver is the value 0x00a850dd loaded, and the
//     other three calls' receivers are three later reads. The model keeps the
//     four reads apart for the same reason it keeps the four carrier reads apart.
//
//  3. THE RETURN REGISTER IS NOT THE REGISTER THE TAIL STORES. 0x00a8516c loads
//     the carrier's float into XMM0; 0x00a8517e divides INTO XMM1, not into
//     XMM0; 0x00a85182 stores XMM1 on the receiver. So the value the caller
//     receives is the carrier's float and NOT its reciprocal, while the value
//     written to the receiver's displacement 0x18 is the reciprocal (or zero).
//     Returning the reciprocal, or storing XMM0, are both single-token mistakes
//     that a reader would not catch from the prose.
//
// VIRTUAL DISPATCH: four indirect transfers, all `CALL EDX` (FF D2) at 0x00a850fc,
// 0x00a8512e, 0x00a8515a and 0x00a851b0, which agrees with the machine dispatch
// record's `indirect_calls: 4`. Each target is fetched with the two-level shape
// the machine's own classifier calls VTABLE_SLOT:
//
//   site 1  0x00a850f7 / 0x00a850f9   table = *word_at(self,0x10)  slot 0x18
//   site 2  0x00a8511e / 0x00a85120   table = *word_at(self,0x10)  slot 0x1c
//   site 3  0x00a8514d / 0x00a85155   table = *word_at(self,0x10)  slot 0x0c
//   site 4  0x00a851a3 / 0x00a851ab   table = *word_at(self,0x10)  slot 0x10
//
// so the chase is three loads deep from the receiver and every one of them is a
// bare `MOV r,[reg+disp]` with no null or range check on the way. This body IS
// ITSELF A VTABLE ENTRY: the dword at 0x0145802c is 0x00a850d0, and 0x01458024
// -- the table the vtable export associates with this function -- begins
// 0x00a85070, 0x004ae250, 0x00a850d0, 0x00a85790, so this is slot index 2 of
// that table. Nothing here names the class: the SDK resolves nothing for this VA
// and the binary carries no MSVC RTTI.
//
// GLOBALS: two, both read-only .rdata words, and both named in the header with
// their addresses and their values transcribed from the image. They are read, not
// written, and neither is a vtable.
//
// WHAT IS NOT CLAIMED, and why. The four targets' identity: the listing fixes that
// they are four-byte words at four slot displacements of a table, and it does not
// fix who owns that table or what the callees do. The stack-argument cleanup: the
// body never adjusts ESP after the three two-argument calls, so callee-owned
// cleanup is an inference from an absence, not an observation. Whether the three
// callees return anything meaningful in EAX: two of the four results are
// discarded immediately, the fourth is stored, and nothing constrains a callee.
// And the value of XMM0 on the early-return path at 0x00a851b7, which is the
// pre-call value unless the call at 0x00a851b0 clobbered it -- see the sidecar.

#include "sw2_00a850d0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00a850d0 {
// The two .rdata words, at the values the image holds. See the header for why
// they are variables rather than compile-time constants: the machine READS them,
// and a model that folded the read into an immediate could not be refuted by any
// test. Their initialisers are the file bytes of SporeApp.exe 3.1.0.22, and the
// model test overwrites them to show which one the body uses and how.
Float g_image_unit_scalar = 1.0f;  // 0x01485720, bytes 00 00 80 3f
Float g_image_zero_scalar = 0.0f;  // 0x01485378, bytes 00 00 00 00

namespace {

// The model's XMM0, as raw bits. Instrumentation, not a machine global: no
// instruction in the body names it, and the original code has no such word. It
// exists so the guard path at 0x00a850d7 -- which returns without writing XMM0 --
// can return the incoming register contents instead of a value the model invented,
// and so the model test can plant a sentinel and watch it come back untouched.
Word g_xmm0_bits = 0;

// The two transfer helpers. They are named so that neither the word "slot" nor
// the word "dispatch" appears in the call's own name: the machine's dispatch
// classifier reads a call's callee name to decide whether the source is stating a
// slot displacement, and only the four `load_slot` fetches below are slot claims.
//
// The single register argument is the DISPATCH OBJECT in all four cases, and it is
// passed as a `void*` because the machine fixes only that a four-byte word sits in
// ECX at each of the four sites: the same instruction shape would be produced by a
// member function whose `this` is that object, or by a callback array whose entry
// takes the object as its one argument. Nothing in this body separates those.
Word zero_argument_transfer(Word target, void* receiver) {
  return reinterpret_cast<ZeroStackArgumentCallee>(
      static_cast<std::uintptr_t>(target))(receiver);
}

Word two_argument_transfer(Word target, void* receiver, Word first_stack_argument,
                           Word second_stack_argument) {
  return reinterpret_cast<TwoStackArgumentCallee>(
      static_cast<std::uintptr_t>(target))(receiver, first_stack_argument,
                                           second_stack_argument);
}

}  // namespace

Word xmm0_bits() { return g_xmm0_bits; }

void set_xmm0_bits(Word bits) { g_xmm0_bits = bits; }

extern "C" float PKG_SW2_00A850D0_THISCALL re_00a850d0(Receiver* receiver, Word) {
  // 00a850d0  PUSH ESI
  // 00a850d1  MOV ESI,ECX
  //
  // ESI is the receiver alias and the only register this body saves. Every
  // receiver access below goes through it and the epilogue's POP ESI restores it,
  // so the alias is a frame fact with no other observable. The receiver is taken
  // as a byte run: this header names no member, because the machine-derived
  // receiver record for this target is bounds_only and settles where the body was
  // seen reaching and nothing about which member is which.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00a850d3  CMP byte ptr [ESI + 0x14],0x0
  // 00a850d7  JNZ 0x00a85188
  //
  // THE RE-ENTRANCY GUARD, and it is a byte compare against zero, so the tested
  // condition is "the byte is not zero" and every non-zero value takes the early
  // exit. There is no masking and no signedness to it.
  //
  // 0x00a85188 is `POP ESI; RET 0x4`: the POP EDI at 0x00a85187 is deliberately
  // SKIPPED, and correctly so, because 0x00a850e0 has not run on this path. The
  // model therefore returns here without balancing anything, and -- because
  // nothing on this path writes XMM0 either -- it returns the incoming register
  // contents unchanged. That is the one place a C++ reconstruction is forced to
  // name a value the machine never produced, and the model test plants a sentinel
  // to show the value really is passed through rather than manufactured.
  if (byte_at(self, kReceiverFlagByte) != kFlagIdleValue) {
    return bits_float(xmm0_bits());
  }

  // 00a850dd  MOV ECX,dword ptr [ESI + 0x10]
  //
  // THE FIRST of four reads of the receiver's word at displacement 0x10. It is
  // this one value that the null test below, the first dispatch's register
  // argument and the first dispatch's table base are all taken from.
  const Word dispatch_first = word_at(self, kReceiverDispatchPointer);

  // 00a850e0  PUSH EDI
  // 00a850e1  MOV byte ptr [ESI + 0x14],0x1
  //
  // One BYTE, not a dword: the opcode is C6 46 14 01, the one-byte immediate form
  // of a store through ESI plus a displacement. The store happens before the null
  // test, so on the p == 0 path the guard byte is still raised.
  store_byte(self, kReceiverFlagByte, kFlagBusyValue);

  // 00a850e5  TEST ECX,ECX
  // 00a850e7  JZ 0x00a8515c
  //
  // A null test on the word just loaded, and the taken branch goes straight to the
  // shared float tail -- past every dispatch. So a null dispatch object means no
  // transfer at all AND no store to the receiver's displacement 0x68, which is
  // written only from 0x00a85130 onwards. The model test drives this with a
  // poisoned value at displacement 0x68 and requires it to survive.
  if (dispatch_first != 0u) {
    // 00a850e9  MOV EAX,dword ptr [ESI + 0xc]
    //
    // READ #1 of the receiver's word at displacement 0x0c. This carrier is used
    // for the bit-2 flag test and for nothing else; 0x00a850f7 overwrites EAX
    // before any second use could happen.
    const Word carrier_first = word_at(self, kReceiverCarrierPointer);

    // 00a850ec  MOV EDX,dword ptr [EAX + 0x8]
    const Word flags_first =
        word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_first)),
                kCarrierFlagWord);

    // 00a850ef  SHR EDX,0x2      00a850f2  TEST DL,0x1      00a850f5  JZ 0x00a850fe
    //
    // Bit index 2 of the flag word. The shift is logical and the mask is one bit,
    // so this is a plain bit test with no signedness anywhere in it.
    if (bit_is_set(flags_first, kBitIndexBit2)) {
      // 00a850f7  MOV EAX,dword ptr [ECX]
      //
      // LEVEL TWO of the chase. ECX still holds the word loaded at 0x00a850dd --
      // this instruction writes EAX, not ECX -- so the table base is the lead dword
      // OF THE DISPATCH OBJECT and not the dispatch object itself and not the
      // receiver. The model test puts a live decoy table on the dispatch object's
      // own slots so a one-level model would call something rather than crash.
      const Word table_for_bit2 =
          word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(dispatch_first)),
                  kDispatchLeadDisplacement);

      // 00a850f9  MOV EDX,dword ptr [EAX + 0x18]
      const Word target_for_bit2 = load_slot(table_for_bit2, 0x18u);

      // 00a850fc  CALL EDX
      //
      // The first transfer. NO stack argument at all: the body contains no PUSH
      // between 0x00a850e0 and here, so this callee's only argument is its
      // register receiver, and the model test drives a callee that inspects it.
      // The EAX result is discarded -- 0x00a850fe reloads EAX from the receiver.
      (void)zero_argument_transfer(
          target_for_bit2,
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(dispatch_first)));
    }

    // 00a850fe  MOV EAX,dword ptr [ESI + 0xc]
    //
    // READ #2 of the receiver's word at displacement 0x0c, and it is a SEPARATE
    // read from 0x00a850e9 on purpose: a callee entered above can have written the
    // receiver, and the machine re-reads rather than reusing. The model test drives
    // that swap from inside the bit-2 callee.
    const Word carrier_second = word_at(self, kReceiverCarrierPointer);

    // 00a85101  MOV ECX,dword ptr [EAX + 0x8]
    //
    // ONE read of this carrier's flag word, and the body then tests bit 4 on a
    // shifted COPY (0x00a85104/0x00a85106 shift EDX) and bit 6 on ECX itself
    // (0x00a85115 shifts ECX). The model holds one word for both tests, which is
    // what the listing does; there is no transfer in between for a swap to hide in.
    const Word flags_second =
        word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_second)),
                kCarrierFlagWord);

    // 00a85104  MOV EDX,ECX    00a85106  SHR EDX,0x4
    // 00a85109  TEST DL,0x1    00a8510c  JZ 0x00a85130
    if (bit_is_set(flags_second, kBitIndexBit4)) {
      // 00a8510e  MOVZX EAX,word ptr [EAX + 0xa8]
      //
      // SIXTEEN bits, zero-extended to thirty-two. The opcode is 0F B7, and the
      // model reads a halfword, so a carrier whose word at this displacement has a
      // non-zero high half contributes only its low half. The model test plants a
      // carrier whose dword here is 0xdeadbeef and requires 0x0000beef to be
      // pushed -- a dword read there would push 0xdeadbeef.
      const Word half = half_word_at(
          reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_second)),
          kCarrierHalfWord);

      // 00a85115  SHR ECX,0x6    00a85118  TEST CL,0x1
      //
      // Bit index 6 of the SAME flag word, and this is the branch that chooses
      // between an address of the receiver and a literal zero -- see the argument
      // order note at the transfer below, because the two are easy to swap.
      const bool address_argument_needed = bit_is_set(flags_second, kBitIndexBit6);

      // 00a8511b  MOV ECX,dword ptr [ESI + 0x10]
      //
      // READ #2 of the receiver's word at displacement 0x10, and it lands AFTER
      // the bit-6 test in the listing: the flags 0x00a85123 tests were set by
      // 0x00a85118, and nothing between them here is a flag-writing instruction.
      // The reload is therefore observable -- a callee of the bit-2 dispatch can
      // have replaced the receiver's word at this displacement.
      const Word dispatch_second = word_at(self, kReceiverDispatchPointer);

      // 00a8511e  MOV EDX,dword ptr [ECX]    00a85120  MOV EDX,dword ptr [EDX + 0x1c]
      const Word table_for_bit4 =
          word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(dispatch_second)),
                  kDispatchLeadDisplacement);
      const Word target_for_bit4 = load_slot(table_for_bit4, 0x1cu);

      // 00a85123  JZ 0x00a8512b
      // 00a85125  LEA EDI,[ESI + 0x28]    00a85128  PUSH EDI
      // 00a85129  JMP 0x00a8512d          00a8512b  PUSH 0x0
      // 00a8512d  PUSH EAX
      //
      // ARGUMENT ORDER, read from the pushes backwards. EDI -- either the
      // receiver's own address at displacement 0x28 or a literal zero -- is pushed
      // FIRST and so lands at the HIGHER address, [ESP+4]. EAX, the halfword, is
      // pushed SECOND and so lands at [ESP+0]. The callee therefore sees the
      // halfword as its first stack argument and the address-or-zero as its
      // second. The model test gives the two distinguishable values and asserts
      // which one arrives first, and separately asserts that the address argument
      // is pointer-identical to the receiver's own displacement 0x28.
      const Word address_argument =
          address_argument_needed
              ? reinterpret_cast<Word>(self + kReceiverAddressArgument)
              : 0u;

      // 00a8512e  CALL EDX
      //
      // Two stack arguments and one register argument. The EAX result is
      // discarded -- 0x00a85130 reloads EAX from the receiver.
      (void)two_argument_transfer(
          target_for_bit4,
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(dispatch_second)), half,
          address_argument);
    }

    // 00a85130  MOV EAX,dword ptr [ESI + 0xc]
    //
    // READ #3 of the receiver's word at displacement 0x0c, reached either by the
    // branch at 0x00a8510c or by falling out of the transfer above. It governs the
    // bit-1 test, both stack arguments of the bit-1-set dispatch, and the float and
    // both stack arguments of the bit-1-clear dispatch.
    const Word carrier_third = word_at(self, kReceiverCarrierPointer);

    // 00a85133  MOV dword ptr [ESI + 0x68],0xffffffff
    //
    // A full dword (opcode C7 46 68) of all ones, and it lands HERE: after the
    // bit-4 block and before the bit-1 test, so it precedes the bit-1-set
    // dispatch's transfer and precedes the bit-1-clear dispatch's transfer too.
    // The model test reads the receiver's displacement 0x68 from inside each
    // callee, which is the only way to pin that ordering. It is NOT written on the
    // null path, because that path branched to 0x00a8515c before reaching here.
    store_word(self, kReceiverResultWord, kResultInitialValue);

    // 00a8513a  MOV ECX,dword ptr [EAX + 0x8]
    const Word flags_third =
        word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                kCarrierFlagWord);

    // 00a8513d  SHR ECX,0x1    00a8513f  TEST CL,0x1    00a85142  JZ 0x00a8518c
    //
    // Bit index 1. This one bit selects between the two dispatches that follow,
    // and the two are the closest pair in the body -- 0x0c and 0x10 are adjacent
    // slots of the same table -- so the model test drives each arm and requires
    // the other arm's table word to stay uncalled.
    if (bit_is_set(flags_third, kBitIndexBit1)) {
      // 00a85144  MOV EDI,dword ptr [EAX + 0xa4]
      const Word argument_a4 =
          word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                  kCarrierSecondStackArgument);

      // 00a8514a  MOV ECX,dword ptr [ESI + 0x10]
      //
      // READ #3 of the receiver's word at displacement 0x10. Again inside the
      // argument setup of a transfer, again after the previous one could have
      // changed the receiver.
      const Word dispatch_third = word_at(self, kReceiverDispatchPointer);

      // 00a8514d  MOV EDX,dword ptr [ECX]
      const Word table_for_bit1set =
          word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(dispatch_third)),
                  kDispatchLeadDisplacement);

      // 00a8514f  MOV EAX,dword ptr [EAX + 0xa0]
      //
      // Read AFTER the table base was loaded, and EAX is the register the next
      // push takes its value from -- so the order of 0x00a8514d and 0x00a8514f is
      // what makes this work, and it is the same pattern at 0x00a851a3/0x00a851a5.
      const Word argument_a0 =
          word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                  kCarrierFirstStackArgument);

      // 00a85155  MOV EDX,dword ptr [EDX + 0xc]
      const Word target_for_bit1set = load_slot(table_for_bit1set, 0x0cu);

      // 00a85158  PUSH EDI    00a85159  PUSH EAX    00a8515a  CALL EDX
      //
      // EDI is the carrier's word at displacement 0xa4 and is pushed first, so it
      // is the SECOND argument; EAX is the carrier's word at displacement 0xa0 and
      // is pushed second, so it is the FIRST. The two displacements differ by four
      // bytes and the two pushes are four bytes apart, so a swapped reading here is
      // a swapped pair of observable values and not a cosmetic difference. The EAX
      // result is discarded -- the tail's 0x00a8515f reloads EAX.
      (void)two_argument_transfer(
          target_for_bit1set,
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(dispatch_third)),
          argument_a0, argument_a4);
    } else {
      // 00a85142 taken: 0x00a8518c  MOVSS XMM0,dword ptr [EAX + 0x10]
      //
      // EAX is still READ #3's carrier, so this float, and the two stack arguments
      // further down, all come from the carrier the previous dispatch could have
      // replaced. XMM0 is written here and it is the value this path will return
      // unless the tail overwrites it -- which it does, on every path that reaches
      // 0x00a8515c.
      const Float guard_scale =
          float_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                   kCarrierScale);
      set_xmm0_bits(float_bits(guard_scale));

      // 00a85191  COMISS XMM0,dword ptr [0x01485378]
      // 00a85198  JBE 0x00a8515c
      //
      // A comparison against a .rdata word, and that word is +0.0f (file bytes
      // 00 00 00 00, read out of the image). JBE tests CF or ZF, so it is taken
      // when the float is less than OR EQUAL to zero AND when the comparison is
      // UNORDERED -- which is why the C++ spelling below is `!(guard > zero)` and
      // not `guard < zero`. A NaN therefore skips the dispatch. The test drives
      // a NaN, both zeros and a negative value to separate the two spellings.
      if (guard_scale > g_image_zero_scalar) {
        // 00a8519a  MOV EDI,dword ptr [EAX + 0xa4]
        const Word argument_a4 =
            word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                    kCarrierSecondStackArgument);

        // 00a851a0  MOV ECX,dword ptr [ESI + 0x10]
        //
        // READ #4 and last of the receiver's word at displacement 0x10. The
        // receiver's displacement 0x68 already holds all ones by now, because
        // 0x00a85133 precedes this block -- the model test reads it from inside the
        // callee to pin that.
        const Word dispatch_fourth = word_at(self, kReceiverDispatchPointer);

        // 00a851a3  MOV EDX,dword ptr [ECX]
        const Word table_for_bit1clear =
            word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(dispatch_fourth)),
                    kDispatchLeadDisplacement);

        // 00a851a5  MOV EAX,dword ptr [EAX + 0xa0]
        const Word argument_a0 =
            word_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_third)),
                    kCarrierFirstStackArgument);

        // 00a851ab  MOV EDX,dword ptr [EDX + 0x10]
        const Word target_for_bit1clear = load_slot(table_for_bit1clear, 0x10u);

        // 00a851ae  PUSH EDI    00a851af  PUSH EAX    00a851b0  CALL EDX
        //
        // Same push order as the bit-1-set arm: the carrier's word at 0xa0 is the
        // first stack argument and the word at 0xa4 the second.
        const Word result_for_bit1clear = two_argument_transfer(
            target_for_bit1clear,
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(dispatch_fourth)),
            argument_a0, argument_a4);

        // 00a851b2  MOV dword ptr [ESI + 0x68],EAX
        //
        // The one store of a callee's result anywhere in the body, and it lands
        // AFTER the transfer, so the callee cannot have observed it. The model test
        // reads displacement 0x68 from inside the callee and requires all ones.
        store_word(self, kReceiverResultWord, result_for_bit1clear);

        // 00a851b5  TEST EAX,EAX    00a851b7  JGE 0x00a8515c
        //
        // JGE is the SIGNED comparison, so this is "the result word is not
        // negative as a signed 32-bit integer". A result of 0x80000000 takes the
        // reset path; 0x7fffffff does not. That distinction is invisible to an
        // unsigned rewrite, and the model test drives both.
        if (!result_is_non_negative(result_for_bit1clear)) {
          // 00a851b9  POP EDI
          // 00a851ba  MOV byte ptr [ESI + 0x14],0x0
          //
          // ONE byte, zero: the guard is released only on this path, and the store
          // is to the same displacement 0x14 that 0x00a850d3 tested and
          // 0x00a850e1 set. The model test checks the whole receiver, not just this
          // byte, because the tail was skipped and the two zeroed floats and the
          // reciprocal were NOT written.
          store_byte(self, kReceiverFlagByte, kFlagIdleValue);
          // 00a851be  POP ESI
          // 00a851bf  RET 0x4
          //
          // The early return. XMM0 holds what 0x00a8518c put there, unless the
          // transfer above left something else in it -- which the machine does not
          // say, because on x86-32 whether XMM0 survives a call is the CALLEE's
          // signature and this listing cannot show it. The model returns the
          // pre-call value and the sidecar names the clobber as an open question;
          // the model test does not assert which of the two the real callee does.
          return bits_float(xmm0_bits());
        }
      }
    }
  }

  // 00a8515c  XORPS XMM1,XMM1
  //
  // THE SHARED FLOAT TAIL, entered from four places: the null branch at
  // 0x00a850e7, the fallthrough out of the bit-1-set transfer at 0x00a8515a, the
  // comparison branch at 0x00a85198 and the signed-comparison branch at
  // 0x00a851b7. XMM1 becomes +0.0f -- all sixteen bits clear, and specifically
  // POSITIVE zero, which matters because the COMISS at 0x00a85171 treats -0.0f as
  // equal to it and takes the same branch.
  Float scaled = 0.0f;

  // 00a8515f  MOV EAX,dword ptr [ESI + 0xc]
  //
  // READ #4 of the receiver's word at displacement 0x0c, and the carrier it yields
  // is used for exactly one thing: the float whose reciprocal lands on the
  // receiver. On the null path this is READ #1, because the branch at 0x00a850e7
  // jumped over the first three. The model reads it here unconditionally, which is
  // what both paths have in common.
  const Word carrier_fourth = word_at(self, kReceiverCarrierPointer);

  // 00a85162  MOVSS dword ptr [ESI + 0x1c],XMM1
  store_float(self, kReceiverFirstZeroFloat, 0.0f);

  // 00a85167  MOVSS dword ptr [ESI + 0x20],XMM1
  store_float(self, kReceiverSecondZeroFloat, 0.0f);

  // 00a8516c  MOVSS XMM0,dword ptr [EAX + 0x10]
  //
  // A four-byte IEEE-754 single -- the operand is named `dword ptr` and the
  // instruction is MOVSS, so the width and the precision are both the machine's.
  // XMM0 is overwritten here on every path that reaches the tail, including the
  // one that already loaded it at 0x00a8518c.
  const Float scale =
      float_at(reinterpret_cast<const void*>(static_cast<std::uintptr_t>(carrier_fourth)),
               kCarrierScale);
  set_xmm0_bits(float_bits(scale));

  // 00a85171  COMISS XMM0,XMM1    00a85174  JBE 0x00a85182
  //
  // XMM1 is the zero from 0x00a8515c, so the tested condition is "the float is not
  // strictly greater than zero", INCLUDING the unordered case: a NaN makes COMISS
  // set all three condition flags, so JBE is taken and the reciprocal is skipped.
  // The C++ spelling is `!(scale > 0.0f)`, which is false for a NaN in exactly the
  // same way, and the model test drives a NaN, +0.0f, -0.0f and a negative value.
  if (scale > 0.0f) {
    // 00a85176  MOVSS XMM1,dword ptr [0x01485720]
    //
    // A .rdata word of +1.0f (file bytes 00 00 80 3f). It is a LOAD, and the model
    // reads the model-level variable standing for that word, so a wrong value there
    // is observable rather than baked in.
    const Float unit = g_image_unit_scalar;

    // 00a8517e  DIVSS XMM1,XMM0
    //
    // THE OPERAND ORDER, and it is the one that decides what lands on the
    // receiver: the destination is XMM1, so the .rdata word is the DIVIDEND and
    // the carrier's float is the DIVISOR. The value stored below is therefore
    // unit/scale. Computing scale/unit would produce a plausible, wrong number, and
    // the model test drives a scale of four so the two differ by a factor of
    // sixteen.
    scaled = unit / scale;
  }

  // 00a85182  MOVSS dword ptr [ESI + 0x18],XMM1
  //
  // The reciprocal (or +0.0f) is stored to the receiver's displacement 0x18. Note
  // what is NOT here: XMM0 is untouched by 0x00a8517e, so the value the caller
  // receives at 0x00a85189 is the carrier's float and not its reciprocal.
  store_float(self, kReceiverScaleResult, scaled);

  // 00a85187  POP EDI
  // 00a85188  POP ESI
  // 00a85189  RET 0x4
  //
  // The epilogue balances the one saved register and pops the extra word the
  // terminator consumes. Neither POP nor RET writes XMM0, so the value loaded at
  // 0x00a8516c is what the caller receives. The model test asserts that identity
  // against the carrier's float with a scale that makes the reciprocal a different
  // number entirely.
  return bits_float(xmm0_bits());
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00a850d0
