// PKG-SWARM-W1-00DD0550 -- VA 0x00dd0550
// FUN_00dd0550 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 16 instructions, 0x00dd0550..0x00dd0573 inclusive, 36
// bytes (ghidra_function.body_start 0x00dd0550, body_end 0x00dd0573,
// size_bytes 36; abi_derived.parse declares 16 instructions with unparsed 0,
// degraded false, flow_complete true). Every line of the model below is
// annotated with the instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust, and the two agree instruction for
// instruction at every address:
//
//   00dd0550  PUSH ESI                      56
//   00dd0551  MOV ESI,ECX                   8B F1
//   00dd0553  CALL 0x00b3d2a0               E8 48 CD D6 FF
//   00dd0558  TEST EAX,EAX                  85 C0
//   00dd055a  JZ 0x00dd0570                 74 14
//   00dd055c  MOV EDX,dword ptr [ESI + 0x80]  8B 96 80 00 00 00
//   00dd0562  TEST EDX,EDX                  85 D2
//   00dd0564  JZ 0x00dd0570                 74 0A
//   00dd0566  PUSH EDX                      52
//   00dd0567  MOV ECX,EAX                   8B C8
//   00dd0569  CALL 0x00ba6dc0               E8 52 68 DD FF
//   00dd056e  POP ESI                       5E
//   00dd056f  RET                           C3
//   00dd0570  XOR EAX,EAX                   33 C0
//   00dd0572  POP ESI                       5E
//   00dd0573  RET                           C3
//
// The 36 bytes were read back out of the image and decoded independently; both
// CALL rel32 fields resolve to the addresses named above
// (0x00dd0558 + 0xFFFFD648 = 0x00b3d2a0 and 0x00dd056e + 0xFFFFDD52 =
// 0x00ba6dc0), so no instruction boundary or operand length is in doubt.
//
// FRAME, resolved against the entry ESP so every claim below is a fact. Entry
// ESP is 0 in the walk; both terminators are bare RET and the walk lands back on
// entry ESP exactly, which is the check that the walk is right:
//
//   0x00dd0550  PUSH ESI            -> entry-4   (the one saved register)
//   0x00dd0566  PUSH EDX            -> entry-8   (0x00ba6dc0's one stack word)
//   0x00ba6dc0  ... RET 0x4         -> entry-4   (the callee drops that word)
//   0x00dd056e  POP ESI             -> entry     (both exits)
//
// There are no ordinary stack arguments of this body's own. That is not an
// absence of evidence: the single PUSH at 0x00dd0566 is provably consumed by
// 0x00ba6dc0's own `RET 0x4`, so no word is live across either terminator, and
// abi_derived.cleanup records bytes 0 on side "caller" with evidence "ret with
// no immediate, no stack reads". The decompilation's `__fastcall (int param_1)`
// is therefore a decompiler artefact, discussed in the header.
//
// CONTROL FLOW: exactly two conditional branches, both `JZ`, and both targets
// are the single 0x00dd0570 arm -- 0x00dd055a and 0x00dd0564. There is one join
// and two exits, both `POP ESI; RET`. Neither test is a signed or unsigned
// comparison: each is a plain `TEST reg,reg` followed by JZ, i.e. equality
// against zero and nothing else. The model test exploits that by driving keys
// whose signed and unsigned readings disagree.
//
// RECEIVER: ECX, aliased into ESI at 0x00dd0551 and addressed only as
// `[ESI + 0x80]` at 0x00dd055c. One displacement, one read, zero writes -- which
// is exactly receiver.offsets [128], register ECX, shape R-ALIAS, written_through
// 0, distinct_offsets 1, max_offset 128 in the machine record.
//
// THE CENTRAL FACT, and the one the model test spends most of its effort on: the
// receiver of 0x00ba6dc0 is NOT this body's receiver. 0x00dd0567 moves the FIRST
// call's EAX into ECX, and 0x00b3d2a0 returns the contents of the global word
// 0x0167eae4. So the value that reaches 0x00ba6dc0 as `this` is a third object,
// unrelated to the `[ESI + 0x80]` read two instructions earlier, and the only
// thing the body does with the 0x80 word is push it as 0x00ba6dc0's one stack
// argument. A reconstruction that passed the receiver, or that passed the 0x80
// word as the `this` argument, would satisfy the decompilation's shape and
// contradict the listing.
//
// VIRTUAL DISPATCH: none inside the body, and none declared. abi_derived.dispatch
// records indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the
// 16 instructions contain no register- or memory-operand transfer. What the
// xrefs DO show is the opposite direction: this body has ZERO direct callers and
// exactly three references, all of type DATA, from 0x0147cab0, 0x0147cb78 and
// 0x0147cc68 -- i.e. it is itself an entry in four vtable tables
// (0x0147ca30, 0x0147ca70, 0x0147caf8, 0x0147cc14), at byte offset +0x80 in the
// first of them. That is why no dispatch word is declared at the receiver's
// +0x00 even though the object is virtually dispatched: the listing never reads
// +0x00, and a named slot would be a claim the machine does not support.
//
// GLOBALS: none in this body. No instruction in the 16 names a data-segment
// address; the only absolute operands are the two CALL rel32 fields, which are
// code. The global word 0x0167eae4 that 0x00b3d2a0 reads belongs to THAT
// function's listing, not to this one, and is recorded in the sidecar as a
// transitive dependency rather than declared here.
//
// RETURN SEMANTICS: one 32-bit integral word in EAX, which is what
// abi_derived.return fixes (register EAX, register_class "integral", type null,
// void_possible false). The value is 0 on the 0x00dd0570 arm (XOR EAX,EAX) and
// otherwise 0x00ba6dc0's own EAX, forwarded untouched: 0x00dd056e is POP ESI,
// which does not touch EAX, and 0x00dd056f is the RET. Nothing in this body
// transforms it.

#include "swarmw1_00dd0550_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00dd0550 {

extern "C" Word PKG_SWARMW1_00DD0550_THISCALL re_00dd0550(
    SporepediaOnlineReceiver* receiver) {
  // 0x00dd0550  PUSH ESI
  // 0x00dd0551  MOV ESI,ECX
  //
  // The receiver arrives in ECX and is copied into ESI, which is the alias every
  // later receiver access goes through (receiver.shape "R-ALIAS"). The PUSH is
  // the saved-register slot for the value the CALLER had in ESI; it is popped
  // again on both exits and nothing is written to the receiver through it.
  SporepediaOnlineReceiver* alias = receiver;

  // 0x00dd0553  CALL 0x00b3d2a0
  //
  // Unconditional: there is no guard in front of it on either path. The callee
  // is a two-instruction accessor that returns the word at 0x0167eae4 and reads
  // no register and no stack slot, so the ECX value at this call site -- which
  // is `receiver`, because 0x00dd0551 left ECX alone -- is provably ignored and
  // is not modelled as an argument.
  OpaqueStarTable* root = root_slot_00b3d2a0();

  // 0x00dd0558  TEST EAX,EAX
  // 0x00dd055a  JZ 0x00dd0570
  //
  // A null test on the POINTER, and it is the only thing decided before the
  // receiver is read at all. A model that tested the key first, or that read the
  // key before this branch, would touch memory the machine does not touch on
  // this arm.
  if (root == nullptr) {
    // 0x00dd0570  XOR EAX,EAX
    // 0x00dd0572  POP ESI
    // 0x00dd0573  RET
    return 0;
  }

  // 0x00dd055c  MOV EDX,dword ptr [ESI + 0x80]
  //
  // The one and only receiver access in the body: a 32-bit LOAD at displacement
  // 0x80 through the ESI alias. Read as a value, not as a pointer -- the word
  // that lands in EDX is itself tested against zero two instructions later and
  // then PUSHED, so it is a datum, and treating it as an address would be a
  // two-level read the listing does not perform. The static_assert pins the
  // named constant to the literal the instruction encodes.
  //
  // NOTE ON THE MESSAGE TEXT: it deliberately states the displacement as the
  // decimal 128 and spells the instruction address in prose, with no 0x token.
  // A hexadecimal literal inside a string literal is still source text, and the
  // one address this body encodes is not a constant the instruction listing
  // contains -- so writing 0x00dd055c here would put a "source constant" in the
  // span that the machine listing cannot corroborate. 0x80 below is the only
  // literal this span states, and it is the only one the listing shows.
  static_assert(kReceiverKeyDisplacement == 0x80,
                "the machine receiver record enumerates 128 and no other "
                "displacement, and the load instruction encodes 0x80");
  const Word key = *word_at(alias, kReceiverKeyDisplacement);

  // 0x00dd0562  TEST EDX,EDX
  // 0x00dd0564  JZ 0x00dd0570
  //
  // Equality against zero and nothing more: TEST/JZ inspects the sign flag and
  // the zero flag together but JZ reads only ZF, so a key whose top bit is set
  // is NOT negative here. Any signed reading of this test (key < 0, or a
  // `(int)key <= 0` style guard) would wrongly divert 0x80000000..0xffffffff to
  // the zero arm; the model test drives exactly that range.
  if (key == 0) {
    // joins the 0x00dd0570 arm: XOR EAX,EAX; POP ESI; RET
    return 0;
  }

  // 0x00dd0566  PUSH EDX
  // 0x00dd0567  MOV ECX,EAX
  // 0x00dd0569  CALL 0x00ba6dc0
  //
  // The push order and the register roles are both fixed here and are the whole
  // argument surface of the call. PUSH EDX puts the receiver's 0x80 word on the
  // stack as 0x00ba6dc0's single ordinary argument -- callee-cleaned, because
  // that callee returns with `RET 0x4`. MOV ECX,EAX then makes the FIRST call's
  // return value the receiver: the object 0x00b3d2a0 handed back, NOT `alias`.
  // The two are different objects and the model test asserts they stay that way.
  const Word result = lookup_00ba6dc0(root, key);

  // 0x00dd056e  POP ESI
  // 0x00dd056f  RET
  //
  // EAX is forwarded unchanged: POP ESI writes ESI only, and the RET is bare.
  return result;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0550
