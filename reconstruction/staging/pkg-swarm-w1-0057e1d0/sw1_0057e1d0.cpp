// PKG-SWARM-W1-0057E1D0 -- VA 0x0057e1d0
// FUN_0057e1d0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 23 instructions, 0x0057e1d0..0x0057e212 inclusive
// (ghidra_function.body_start 0x0057e1d0, body_end 0x0057e212, size 67, and the
// five trailing 0xCC bytes at 0x0057e213..0x0057e217 are inter-function
// padding, not instructions). Every line of the model below is annotated with the
// instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust. Reading 0x0057e1d0..0x0057e211 out of
// SporeApp.exe gives, in order:
//
//   0057e1d0  56                    PUSH ESI
//   0057e1d1  8b f1                 MOV ESI,ECX
//   0057e1d3  8b 46 0c              MOV EAX,dword ptr [ESI + 0xc]
//   0057e1d6  8b 4e 14              MOV ECX,dword ptr [ESI + 0x14]
//   0057e1d9  2b c8                 SUB ECX,EAX
//   0057e1db  83 e1 fe              AND ECX,0xfffffffe
//   0057e1de  83 f9 02              CMP ECX,0x2
//   0057e1e1  7e 0d                 JLE 0x0057e1f0
//   0057e1e3  85 c0                 TEST EAX,EAX
//   0057e1e5  74 09                 JZ 0x0057e1f0
//   0057e1e7  50                    PUSH EAX
//   0057e1e8  e8 93 91 9c 00        CALL 0x00f47380
//   0057e1ed  83 c4 04              ADD ESP,0x4
//   0057e1f0  f6 44 24 08 01        TEST byte ptr [ESP + 0x8],0x1
//   0057e1f5  c7 46 04 94 03 ef 01  MOV dword ptr [ESI + 0x4],0x13ef094
//   0057e1fc  c7 06 38 03 eb 01     MOV dword ptr [ESI],0x13eb938
//   0057e202  74 09                 JZ 0x0057e20d
//   0057e204  56                    PUSH ESI
//   0057e205  e8 76 91 9c 00        CALL 0x00f47380
//   0057e20a  83 c4 04              ADD ESP,0x4
//   0057e20d  8b c6                 MOV EAX,ESI
//   0057e20f  5e                    POP ESI
//   0057e210  c2 04 00              RET 0x4
//
// The 23 instructions, their addresses, their lengths, both branch targets and
// both call targets all agree with the committed Ghidra listing instruction for
// instruction, so nothing below rests on a re-interpretation.
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk; `RET 0x4` then lands ESP at
// +8, which is entry+4 (return address) +4 (the one argument word), so the frame
// balances. Two independent checks agree: the single `PUSH ESI` at 0x0057e1d0
// and its matching `POP ESI` at 0x0057e20f cancel, and after 0x0057e20a's
// `ADD ESP,0x4` the stack is back at entry-4, so 0x0057e1f0's `[ESP + 0x8]` is
// entry+4 -- the one ordinary stack argument -- and not the saved ESI.
//
//   entry-4   the saved ESI, pushed at 0x0057e1d0 and restored at 0x0057e20f
//   entry+4   the one ordinary argument, a BYTE. 0x0057e1f0 tests its low bit
//
// So the argument is a byte, not a word, and `RET 0x4` consumes it: the callee
// owns the cleanup, which together with the ECX receiver is what makes this
// __thiscall and rules out cdecl and fastcall. Ghidra's own record agrees
// (observed_conventions __thiscall, hidden_this_register ECX, ret_form "RET 0x4",
// stack_cleanup_owner callee, ordinary_stack_arguments[0] = entry_ESP+0x4, size
// 1, read true, and ghidra's own parameter list is empty).
//
// CONTROL FLOW: three conditional branches, all with absolute targets inside the
// recovered body span 0x0057e1d0..0x0057e212 -- JLE 0x0057e1f0 (0x0057e1e1),
// JZ 0x0057e1f0 (0x0057e1e5) and JZ 0x0057e20d (0x0057e202) -- and no other
// transfer. The graph closes inside the span.
//
// BRANCH 1 IS SIGNED, and that is the single highest-risk fact in this body.
// 0x0057e1de/0x0057e1e1 are `CMP ECX,0x2` / `JLE`, and JLE (0x7E) is the signed
// form. ECX at that point is `([ESI+0x14] - [ESI+0x0c]) & 0xfffffffe`, computed
// with 32-bit wraparound, and the AND clears the low bit rather than the sign.
// A difference whose bit 31 survives the AND is NEGATIVE as a signed 32-bit
// value, so it is <= 2 and the release is skipped. An unsigned reconstruction of
// the same three instructions would release instead. The model test drives four
// inputs on which the two disagree, and the model below reads the value as signed
// because the opcode is signed.
//
// BRANCH 2 IS UNSIGNED in effect but a zero test either way: 0x0057e1e3
// `TEST EAX,EAX` / 0x0057e1e5 `JZ` fires on exactly one value, 0, and the
// model test drives the null-begin case with a wide span so a reconstruction that
// dropped the test would release a null pointer's word.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 23
// instructions contain no register- or memory-operand transfer. The two constants
// the body STORES are dispatch-table ADDRESSES; the body never READS a word
// through one, and no slot boundary is declared anywhere in this model. The
// record's vtable association (vtable:0x013f57f8, this body at that table's own
// displacement +0x70 -- confirmed by reading the table's bytes, where
// 0x013f5868 holds 0x0057e1d0) is recorded here for the integrator and is
// deliberately NOT modelled as a member at +0x00, because this body's listing
// contains no read of +0x00 at all -- only a write.
//
// GLOBALS: none reached by this body. The two absolute operands it names are the
// immediate constants of the two MOV-immediate stores, and both are addressed as
// values written into the receiver rather than as storage this body loads from.
// The one global that belongs to the release path, 0x016c8b44, is read by
// 0x00f47380 and not by this body; it is recorded in the header next to that
// callee.

#include "sw1_0057e1d0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0 {

extern "C" Object* PKG_SW1_0057E1D0_THISCALL re_0057e1d0(
    Object* receiver, std::uint8_t deleting_flag) {
  // 0057e1d0  PUSH ESI
  // 0057e1d1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the last one at 0x0057e20f. ECX is never read again,
  // which is why nothing below reaches the receiver through ECX and why the
  // machine-derived receiver record reports register ECX with shape R-ALIAS.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT
  // into it. The record enumerates offsets = [0, 4, 12, 20] and is bounds_only:
  // it says where the body was seen reaching and not which member is which, so
  // no member name is written for any of them and the struct declares none.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 0057e1d3  MOV EAX,dword ptr [ESI + 0xc]
  //
  // One dword at the receiver's +0x0c, loaded into EAX and used as a VALUE --
  // pushed straight back out at 0x0057e1e7 with no dereference of any kind in
  // between. It is therefore a pointer, and the model converts it to one exactly
  // once, here, rather than reading a pointer-to-pointer or reading the address
  // of the word instead of its contents.
  const Word run_begin_value = *word_at(self, 0xc);

  // 0057e1d6  MOV ECX,dword ptr [ESI + 0x14]
  //
  // The second dword of the pair, at the receiver's +0x14. Same treatment: a
  // value, never a second level of indirection.
  const Word run_end_value = *word_at(self, 0x14);

  // 0057e1d9  SUB ECX,EAX
  // 0057e1db  AND ECX,0xfffffffe
  // 0057e1de  CMP ECX,0x2
  // 0057e1e1  JLE 0x0057e1f0
  //
  // The difference of the two words with 32-bit wraparound, rounded DOWN to an
  // even number by clearing bit 0, then compared SIGNED against 2. The three
  // steps are reproduced in the machine's own order and with the machine's own
  // spellings so each is separately checkable against the listing.
  //
  // Nothing in this body says what the two words MEASURE. It is not bytes and it
  // is not elements: the mask is a rounding to even, and a rounding to even is
  // the shape of a byte count, but this package does not convert the difference
  // into a count or an element size, because no instruction in the body divides
  // and no record says what the pair holds. The model reproduces the arithmetic
  // and stops there.
  const Word span = (run_end_value - run_begin_value) & 0xfffffffeu;
  const bool span_over_threshold = static_cast<std::int32_t>(span) > 0x2;

  // 0057e1e3  TEST EAX,EAX
  // 0057e1e5  JZ 0x0057e1f0
  // 0057e1e7  PUSH EAX
  // 0057e1e8  CALL 0x00f47380
  // 0057e1ed  ADD ESP,0x4
  //
  // The release of the +0x0c word, guarded twice and in this order: the span
  // first (0x0057e1e1) and the null check second (0x0057e1e5), so a null word
  // with a wide span never reaches the call. The short circuit below is written in
  // that same order, which matters: the null check is a separate instruction with
  // its own branch, and a model that folded it into the span test would be right
  // here by accident and wrong the moment the two were reordered.
  //
  // 0x00f47380 is cdecl -- its terminator is the bare byte C3 at 0x00f47394 --
  // so 0x0057e1ed drops the pushed word itself. The argument is the word read
  // from the receiver, not the receiver.
  if (span_over_threshold && run_begin_value != 0) {
    heap_release_00f47380(reinterpret_cast<void*>(run_begin_value));
  }

  // 0057e1f0  TEST byte ptr [ESP + 0x8],0x1
  //
  // The one ordinary stack argument, a BYTE (the 0xf6 opcode family and the
  // ABI record's sizes [1] both say one byte), tested against bit 0 and nothing
  // else. Every other bit of that byte is ignored, so 0x02 releases and 0xfe does
  // not. ESP is entry-4 here, after 0x0057e1ed's `ADD ESP,0x4` restored the
  // prologue's push, so [ESP + 0x8] is entry+4.
  //
  // The test is read BEFORE the two stores below and the branch that consumes it
  // is taken AFTER them, which is why the flag is computed here and used below:
  // the stores are unconditional and land on both arms.
  const bool delete_object = (deleting_flag & 0x1u) != 0;

  // 0057e1f5  MOV dword ptr [ESI + 0x4],0x13ef094
  //
  // Four bytes at the receiver's +0x04. The stored value is the ADDRESS 0x013ef094
  // and the address's own first dword is 0x0041d780, a .text code address, with
  // four more behind it; 0x013ef094 is a dispatch table and this is its
  // installation into the receiver. It is written FIRST of the pair, at the
  // HIGHER displacement, and that is not tidied up here: the order is the
  // listing's.
  *word_at(self, 0x4) = 0x13ef094u;

  // 0057e1fc  MOV dword ptr [ESI],0x13eb938
  //
  // Four bytes at the receiver's +0x00, written SECOND. 0x013eb938's own first
  // dword is 0x011e06d0, which the image shows to be `JMP DWORD PTR
  // [0x013cc468]` -- an import thunk the bridge names `purecall` -- so this
  // address is a dispatch table too. The zero displacement is written as a
  // decimal 0 because the listing writes it bare, as `[ESI]`, and the source
  // span's literals are compared against the listing's.
  *word_at(self, 0) = 0x13eb938u;

  // 0057e202  JZ 0x0057e20d
  // 0057e204  PUSH ESI
  // 0057e205  CALL 0x00f47380
  // 0057e20a  ADD ESP,0x4
  //
  // The release of the receiver itself, on the same one-word cdecl shape as the
  // call above. Two facts a model has to get right and that the model test drives
  // both ways: the argument is ESI -- the receiver, at the pointer this body was
  // ENTERED with, and not the +0x0c word and not a pointer to the receiver -- and
  // it happens only after both stores above have already been written, which the
  // observer samples at the moment of the call.
  if (delete_object) {
    heap_release_00f47380(receiver);
  }

  // 0057e20d  MOV EAX,ESI
  // 0057e20f  POP ESI
  // 0057e210  RET 0x4
  //
  // The return value is the receiver, on both arms: 0x0057e202's branch target is
  // this very instruction, so the no-release path falls through to it and the
  // release path lands on it after the call. That is why the model returns
  // `receiver` and not the released word, and why the declared return type is a
  // pointer rather than void. The record's own phrase for the same observation is
  // `unclassified_in_EAX` -- a value left in EAX that no record classifies -- and
  // the model test asserts the pointer identity.
  //
  // The epilogue's POP and RET carry no observable this body produces: the saved
  // ESI is restored, and the one argument word is dropped by the callee.
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_0057e1d0
