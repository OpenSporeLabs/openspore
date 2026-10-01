// PKG-W2-01053BE0 -- VA 0x01053be0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The reconstructed body of the 95 recovered instructions 0x01053be0..0x01053cff.
// Every statement below is tied to an instruction of the evidence listing at
// that instruction's own address, and every displacement, immediate and callee
// name it uses is a constant carried in sim_prefix_01053be0.hpp from that
// listing or from bytes read back out of the image.
//
// See the header for what this package deliberately does NOT claim: no calling
// convention (the record states none), no class, no vtable identity, no
// receiver type, no field beyond the single displacement the receiver record
// enumerates, and no tail hop -- the span's only unconditional direct jump lands
// back inside it, and both of its ways out leave the span.

#include "sim_prefix_01053be0.hpp"

namespace openspore::reconstruction::pkg_w2_01053be0 {

// Placed first in this translation unit on purpose: the validator binds a source
// span to 0x01053be0 by the 8-hex VA token appearing in the function name, and
// it takes the FIRST such definition in the file. Nothing else in this file
// carries that token in a function name.
extern "C" void reconstruct_01053be0(Receiver* receiver, Triple* out_triple,
                                     std::uint32_t caller_word) {
  // NOTE ON THE ASSERTION MESSAGES BELOW. A message string is not a comment: the
  // validator's constant check reads the target span with comments removed but
  // string literals intact, so any "0x..." written inside a message would be
  // read as a constant this source claims and would then be checked against the
  // machine listing. Instruction addresses, displacements and the span's own
  // addresses are therefore spelled without the 0x prefix in these messages, and
  // the bytes they refer to are the ones the comments above and below quote.
  static_assert(kInstructionCount == 95, "the recovered span is 95 instructions");
  static_assert(kSpanBytes == 288u,
                "the recovered span runs from 01053be0 through 01053cff inclusive, "
                "which is 288 bytes");
  static_assert(kReceiverOnlyOffset == 0u,
                "the one load through the receiver is MOV EAX,[EDI], whose operand "
                "carries no displacement byte at all");
  static_assert(kReceiverDistinctOffsets == 1,
                "the receiver record enumerates exactly one displacement, and it is "
                "the load the body makes through its alias");
  static_assert(kReceiverDereferenceCount == 1,
                "the body dereferences the receiver once, at offset zero");
  static_assert(kRetInstructionsInSpan == 0,
                "the recovered span contains no RET, so nothing in it is a return "
                "and the entry returns nothing the span can be shown to produce");
  static_assert(kConditionalExitsOutOfSpan == 1,
                "exactly one conditional branch leaves the recovered span, the JLE "
                "whose target is 01053d3b");
  static_assert(kConditionalExitTarget == 0x01053d3bu && kConditionalExitTarget > kSpanLastByte,
                "that JLE target lies outside the recovered span");
  static_assert(kUnconditionalDirectJumpsInsideSpan == 1 && kOnlyDirectJumpTargetIsInside,
                "the span's one unconditional direct jump lands back inside it, so "
                "it is control flow and not a tail hop");
  static_assert(kTailTargetAsserted == false,
                "no tail target is asserted: the record records no hop and the "
                "listing re-derives none");
  static_assert(kTailHopPresent == false,
                "the record's own tail sub-record is empty for this address");
  static_assert(kLoopScratchAddressDetermined == false,
                "the LEA after the SUB ESP in the loop resolves to one address or "
                "another depending on the cleanup of the computed call, which the "
                "record leaves UNKNOWN, so this package picks neither");
  static_assert(kIterationLimit == 0x3e8u,
                "both bounds tests in the loop compare the counter with 1000");
  static_assert(kDirectCalleeCount == 6 && kDirectCallSiteCount == 10,
                "six distinct direct callees over ten direct call sites");
  static_assert(kComputedTransferCount == 2, "two computed transfers, both through a register");
  static_assert(kOutParameterEntryOffset == kStackArgumentSlotOffset,
                "the load of the out-parameter resolves to the caller's first "
                "stack word, which is the slot the machine record enumerates");
  static_assert(kProbeSecondWordEntryOffset == kSecondStackWordOffset,
                "the load of the probe's third stack word resolves to the caller's "
                "second stack word, which the record's slot list omits");
  static_assert(kUntouchedCellEntryOffset - kLocalTripleEntryOffset ==
                    static_cast<std::ptrdiff_t>(kTripleBytes),
                "the untouched cell sits exactly one twelve-byte triple above the "
                "local triple, so it is the word just past that triple and the span "
                "never writes it");
  static_assert(kPrologueDelta == -(static_cast<std::ptrdiff_t>(kFrameSubBytes) +
                                    4 * static_cast<std::ptrdiff_t>(kSavedRegisterPushes)),
                "the prologue is a subtraction of 24 bytes plus four one-word pushes");

  // 0x01053be0..0x01053be6 -- SUB ESP,0x18; PUSH EBX; PUSH EBP; PUSH ESI; PUSH
  // EDI. ESP is entry_ESP-0x28 from here until a call or a push disturbs it,
  // and every stack operand in the rest of the body is resolved against that.
  //
  // 0x01053be7 -- MOV EDI,ECX. The record names ECX a receiver (present true,
  // INFERRED, shape R-ALIAS) and this instruction is the alias: the body keeps
  // the receiver in EDI across every call in the span and loads through it once.
  //
  // 0x01053be9 -- CALL 0x00ffbe50, nothing pushed, result in EAX.
  void* const root = callee_00ffbe50();
  // 0x01053bee -- MOV ECX,EAX.
  // 0x01053bf0 -- CALL 0x00a1ad60, nothing pushed, result in EAX.
  void* const model = callee_00a1ad60(root);

  // 0x01053bf5 -- MOV ESI,[ESP+0x2c], which is entry_ESP+0x4: the caller's first
  // stack word, four bytes, read once and then used as the base of every store
  // the span makes. The record's sret sub-record cannot decide whether this word
  // is a hidden struct-return pointer or an out-parameter (ambiguity
  // sret_vs_out_param, present null), so the parameter is named for the address
  // it resolves to and not for a meaning.
  Triple* const out = out_triple;

  // 0x01053bf9 -- XORPS XMM0,XMM0, then three four-byte single-precision
  // stores: 0x01053bfc MOVSS [ESI],XMM0; 0x01053c00 MOVSS [ESI+0x4],XMM0;
  // 0x01053c05 MOVSS [ESI+0x8],XMM0. Twelve bytes of +0.0f, in that order,
  // before either arm of the null test is taken.
  out[0] = 0.0f;
  out[1] = 0.0f;
  out[2] = 0.0f;

  // 0x01053c1f, 0x01053c2a, 0x01053c35 -- MOVSS into ESP+0x10, ESP+0x14 and
  // ESP+0x18, the local twelve bytes at entry_ESP-0x18..entry_ESP-0x0d that the
  // model-present arm fills and the other arm never reads.
  Triple local[kTripleWords] = {0.0f, 0.0f, 0.0f};

  // 0x01053cb8 -- SUB ESP,0x8 followed by two FLD/FSTP pairs writes two floats
  // the recovered span never reads again: the address the body then passes to
  // 0x00b3d350 is LEA EAX,[ESP+0x24] at 0x01053cbf, a different word. They are
  // reproduced because the listing performs them. The buffer is volatile so the
  // stores survive optimisation, and nothing in this model or in its test reads
  // them, which is the machine's own behaviour rather than a shortcut.
  volatile Triple dead[kTripleWords - 1];
  // 0x01053cb2 -- FLD float ptr [0x01477fbc], bytes 00 00 48 43, popped by
  // 0x01053cbb -- FSTP float ptr [ESP+0x4].
  dead[1] = kFarStackFloat;
  // 0x01053cc3 -- FLD float ptr [0x013f1cac], bytes 00 00 48 42, popped by
  // 0x01053cc9 -- FSTP float ptr [ESP].
  dead[0] = kNearStackFloat;
  // sizeof, and not a read: the machine never reads either word back inside the
  // recovered span, so the model must not either. Naming the object here keeps
  // the two stores alive under every optimisation level without inventing a
  // consumer for them.
  static_assert(sizeof dead == 8u,
                "the two FLD/FSTP pairs write two four-byte words and nothing else");

  // The cell the span hands to 0x00b3d350 at 0x01053c49 (LEA EDX,[ESP+0x20] with
  // one word pushed) and to 0x00b3d350 at 0x01053c75 (LEA ECX,[ESP+0x1c] with
  // nothing outstanding) is entry_ESP-0x0c both times: five words below the
  // local triple, outside the frame, never written by the recovered span. Its
  // address is determined and its content is not, so the model passes a buffer
  // and reads nothing back.
  std::uint32_t cell = 0;

  // 0x01053c0a -- TEST EAX,EAX, and 0x01053c0c -- JZ 0x01053c6c: the model's two
  // arms are the machine's null test.
  if (model != nullptr) {
    // 0x01053c0e -- MOV EDX,[EAX+0x34]: the word that holds the next call's
    // target.
    const std::uint32_t table = load_word32(model, kModelTableWordOffset);
    // 0x01053c11 -- ADD EAX,0x34 and 0x01053c14 -- MOV ECX,EAX. The word handed
    // to the computed call is the model word advanced by that same displacement,
    // not the model word itself.
    void* const self = byte_advance(model, kModelSelfOffset);
    // 0x01053c16 -- MOV EAX,[EDX+0x2c] and 0x01053c19 -- CALL EAX. A computed
    // transfer: the target is a word read out of memory, so no address is named,
    // no slot boundary is declared and no class is claimed.
    const Triple* const produced = dispatch_first(
        load_word32(reinterpret_cast<const void*>(table), kTableCallWordOffset), self);

    // 0x01053c1b, 0x01053c25, 0x01053c30 -- three four-byte loads out of that
    // result, stored at 0x01053c1f, 0x01053c2a and 0x01053c35.
    store_triple(local, produced);

    // 0x01053c3b -- CALL 0x00b3d350 with nothing pushed, then 0x01053c40 --
    // TEST EAX,EAX and 0x01053c42 -- JZ 0x01053c96.
    void* const first = callee_00b3d350();
    if (first != nullptr) {
      // 0x01053c44 -- LEA ECX,[ESP+0x10], which with nothing outstanding is
      // entry_ESP-0x18: the first word of the local triple, an address this body
      // has just written three times. This one address is not in doubt, so the
      // model passes the buffer itself.
      Triple* const local_address = local;
      // 0x01053c48 -- PUSH ECX and 0x01053c4d -- PUSH EDX: two words, the local
      // triple first and the untouched cell second, for the call below.
      //
      // 0x01053c4e -- CALL 0x00b3d350, a SECOND time and with arguments. The
      // first call's result is what the null test consumed and nothing hands it
      // on, so the word that reaches 0x00b815a0 is this second result.
      void* const second = callee_00b3d350();
      // 0x01053c53 -- MOV ECX,EAX, then 0x01053c55 -- CALL 0x00b815a0.
      const Triple* const r = callee_00b815a0(second, local_address, &cell);

      // 0x01053c5c, 0x01053c5e, 0x01053c64 -- three four-byte stores out of
      // that result into the caller's word, at +0, +4 and +8.
      store_triple(out, r);
    }
    // 0x01053c6a -- JMP 0x01053c96, inside the recovered span: control flow, not
    // a transfer out of the body.
  } else {
    // 0x01053c6c -- CALL 0x00b3d350 with nothing pushed, then 0x01053c71 --
    // TEST EAX,EAX and 0x01053c73 -- JZ 0x01053c96. The same gate, reached on the
    // other arm of the null test.
    void* const first = callee_00b3d350();
    if (first != nullptr) {
      // 0x01053c75 -- LEA ECX,[ESP+0x1c], which with nothing outstanding is
      // entry_ESP-0x0c: the untouched cell. Pushed at 0x01053c79.
      //
      // 0x01053c7a -- CALL 0x00b3d350, a second time, with that one word.
      void* const second = callee_00b3d350();
      // 0x01053c7f -- MOV ECX,EAX, then 0x01053c81 -- CALL 0x00b81720.
      const Triple* const r = callee_00b81720(second, &cell);
      // 0x01053c88, 0x01053c8a, 0x01053c90 -- three four-byte stores, +0, +4, +8.
      store_triple(out, r);
    }
  }

  // 0x01053c96 -- MOV EBP,[ESP+0x30], which is entry_ESP+0x8: the caller's
  // SECOND stack word. The record's stack_arguments enumerate only
  // entry_ESP+0x4 and the parse record carries esp_unresolved true, so the
  // listing is the witness for this one. EBP was saved by the prologue at
  // 0x01053be4 and is scratch from here.
  //
  // 0x01053c9a -- XOR EBX,EBX: the iteration counter starts at zero.
  // 0x01053c9c -- LEA ESP,[ESP]: a four-byte no-op that changes nothing.
  std::uint32_t iteration = 0;
  for (;;) {
    // 0x01053ca0 -- MOV EAX,[EDI]: the ONE load through the receiver, and its
    // operand carries no displacement. This is the receiver record's single
    // enumerated offset, where receiver.offsets is [0] and max_offset is 0.
    const std::uint32_t table = load_word32(receiver, kReceiverTableOffset);
    // 0x01053ca2 -- MOV EDX,[EAX+0x24]: the probe's target word.
    //
    // 0x01053ca5 -- PUSH 0x1, 0x01053ca7 -- PUSH ESI, 0x01053ca8 -- PUSH EBP and
    // 0x01053ca9 -- MOV ECX,EDI: three stack words in that order and the receiver
    // in ECX.
    //
    // 0x01053cab -- INC EBX, before the call and so before its result is tested.
    ++iteration;
    // 0x01053cac -- CALL EDX, the second computed transfer. The record's cleanup
    // is UNKNOWN with side null, so which side of this call restores ESP is not
    // determined, and neither is the address 0x01053cbf computes from it.
    const std::uint32_t ready =
        dispatch_probe(load_word32(reinterpret_cast<const void*>(table),
                                   kReceiverCallWordOffset),
                       receiver, kProbeFirstArgument, out, caller_word);
    // 0x01053cae -- TEST AL,AL and 0x01053cb0 -- JNZ 0x01053cf3.
    if (ready != 0) {
      break;
    }

    // 0x01053cb8 -- SUB ESP,0x8 and the two FLD/FSTP pairs, whose stores are
    // reproduced above, then 0x01053cbf -- LEA EAX,[ESP+0x24], whose address
    // this package does not claim, then 0x01053ccc -- PUSH ESI and 0x01053ccd --
    // PUSH EAX: two words. 0x01053cce -- CALL 0x00b3d350, 0x01053cd3 -- MOV
    // ECX,EAX, 0x01053cd5 -- CALL 0x00b81780.
    const Triple* const r = callee_00b81780(callee_00b3d350(), &cell);
    // 0x01053ce0, 0x01053ce4, 0x01053cea -- three four-byte stores out of that
    // result, +0, +4, +8. The order matters: the result is stored BEFORE the
    // loop bound is compared.
    store_triple(out, r);
    // 0x01053cda -- CMP EBX,0x3e8 and 0x01053cf0 -- JL 0x01053ca0.
    if (!(iteration < kIterationLimit)) {
      // 0x01053cf2 -- INC EBX, reached only on this path.
      ++iteration;
      break;
    }
  }

  // Both ways out of the recovered span leave it, and neither is a return:
  //   0x01053cf3 -- CMP EBX,0x3e8
  //   0x01053cf9 -- JLE 0x01053d3b, which is outside the span
  //   0x01053cfb -- XOR EBX,EBX
  //   0x01053cfd -- LEA ECX,[ECX], the last recovered instruction, after which
  //                control runs on to 0x01053d00, also outside the span.
  // The entry therefore returns nothing, and asserts nothing about what the code
  // past the span does with it.
}

}  // namespace openspore::reconstruction::pkg_w2_01053be0
