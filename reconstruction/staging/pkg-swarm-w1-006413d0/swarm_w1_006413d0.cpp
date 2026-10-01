// PKG-SWARM-W1-006413D0 -- VA 0x006413d0
// FUN_006413d0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 17 instructions, 0x006413d0..0x006413fa inclusive
// (ghidra_function.body_start 0x006413d0, body_end 0x006413fa, size 43). The
// listing below was re-read out of the image for this package -- 43 bytes at
// 0x006413d0 in SporeApp.exe,
//   568bf18b068b90a4000000 6a00ffd2 8b068b90a8000000 8bceffd2
//   8b068b90ac000000 6a008bceffd2 5ec3
// -- and it agrees with the committed listing instruction for instruction and byte
// for byte, including the three `8B 90` displacements and the two `6A 00` argument
// pushes. Every line of the model below is annotated with the address it comes
// from.
//
//   006413d0  56           PUSH ESI
//   006413d1  8B F1        MOV ESI,ECX
//   006413d3  8B 06        MOV EAX,dword ptr [ESI]
//   006413d5  8B 90 A4 00 00 00   MOV EDX,dword ptr [EAX + 0xa4]
//   006413db  6A 00        PUSH 0x0
//   006413dd  FF D2        CALL EDX
//   006413df  8B 06        MOV EAX,dword ptr [ESI]
//   006413e1  8B 90 A8 00 00 00   MOV EDX,dword ptr [EAX + 0xa8]
//   006413e7  8B CE        MOV ECX,ESI
//   006413e9  FF D2        CALL EDX
//   006413eb  8B 06        MOV EAX,dword ptr [ESI]
//   006413ed  8B 90 AC 00 00 00   MOV EDX,dword ptr [EAX + 0xac]
//   006413f3  6A 00        PUSH 0x0
//   006413f5  8B CE        MOV ECX,ESI
//   006413f7  FF D2        CALL EDX
//   006413f9  5E           POP ESI
//   006413fa  C3           RET
//
// WHAT THE BODY IS, in the only terms the bytes support: a 43-byte straight-line
// wrapper that makes three virtual calls on its own receiver and hands back the
// return word of the last one. There is no branch of any kind -- no conditional
// jump, no unconditional jump, no loop, no switch -- so all 17 instructions fall
// through to the RET in order, and the body is a single basic block. Every
// instruction before the first CALL is an argument setup and every instruction after
// the last CALL is the epilogue.
//
// FRAME, resolved once against the entry ESP. `PUSH ESI` at 0x006413d0 puts the
// saved ESI at entry-4 and nothing else is ever allocated: there is no SUB ESP, no
// local, no second push. The `PUSH 0x0` at 0x006413db therefore writes entry-8, and
// the `PUSH 0x0` at 0x006413f3 writes entry-8 again once the first callee has
// consumed its word. The `POP ESI` at 0x006413f9 takes entry-4 back and the bare
// `C3` at 0x006413fa pops the return address at entry. This is what proves the
// callees clean their own arguments: if any of the three left its pushed word on
// the stack, the POP ESI at 0x006413f9 would pop that word instead of the saved
// ESI and the RET would return to the wrong place. The independent corroboration
// is in the header: the three concrete targets in the table at 0x013ff648 are
// 0x00641cd0 (`RET 4`), 0x00641e10 (bare `RET`) and 0x00641e40 (`RET 4`), which is
// one word, no word, one word -- the same pattern as the three call sites.
//
// VIRTUAL DISPATCH: three register-indirect transfers, and the shape is fixed by
// the operand forms rather than guessed. Each site is
//   (1) one dword load out of the receiver       8B 06      -> EAX
//   (2) one dword load at a displacement of EAX  8B 90 dddd -> EDX
//   (3) one indirect call through EDX            FF D2
// so it is ONE level of indirection through the receiver and then a 4-byte-stride
// read, not a table of tables and not a second dereference. The three
// displacements are 0xa4, 0xa8 and 0xac. The same leading word is re-loaded for
// every transfer (0x006413d3, 0x006413df, 0x006413eb are three separate `8B 06`),
// which is a real property of the machine and not a stylistic choice: a callee
// that replaces the receiver's leading word is seen by the next transfer. The
// machine record reports indirect_calls 3 and call_offsets [] and agrees there is
// no direct callee; it also reports vtable_shaped_loads 0, which is a limitation of
// the record's stride detection rather than a statement about this code -- the load
// chain above is a dispatch chain and the eight vtable records the target carries
// put this body's own address in tables at 0x013ff648, 0x01462764, 0x0147c9e8,
// 0x0147ca30, 0x0147caf8, 0x0147cbbc, 0x01489090 and 0x014893b0.
//
// The per-class target addresses are NOT constants here and the model does not use
// any. Reading the table at 0x013ff648 gives 0x00641cd0 / 0x00641e10 / 0x00641e40
// at the three displacements; the other seven recorded tables give fifteen further
// different values. Modelling three fixed addresses would be a reconstruction of
// one particular class, not of this body.
//
// ARGUMENT SURFACE: none. The receiver arrives in ECX and is copied to ESI at
// 0x006413d1, so the register is not the operand form after that -- the body reads
// the receiver through ESI three times and hands the receiver back in ECX
// explicitly at 0x006413e7 and 0x006413f5. The first transfer does not re-establish
// ECX (0x006413e7 and 0x006413f5 are the two `8B CE` instructions and the first
// call site has none) because nothing between 0x006413d0 and 0x006413dd writes
// ECX: the two loads and the PUSH do not touch it, so the ECX the first callee sees
// is the entry ECX, which is this same receiver. The model passes the one receiver
// to all three, which is what the machine does either way.
//
// The one ordinary argument, at the first and the third transfer, is the immediate
// 0 of `6A 00`. It is a full 4-byte push (`PUSH imm8` sign-extends to 4 bytes) and
// nothing this body computes reaches it. Whether that 0 is meant as a null pointer
// or as a false/0 enum is not settled by the bytes and is not claimed here.
//
// GLOBALS: none. No instruction in the body names a data-segment address; every
// operand is a register, an immediate 0, or a memory reference through ESI or EAX.
//
// RETURN SEMANTICS: EAX, by pass-through. The bare `C3` rules out a hidden return
// pointer (a struct-returning callee pops it with `RET 4`), so this function's result
// is a 32-bit scalar in EAX. EAX is written once after the last transfer, by the
// CALL at 0x006413f7; 0x006413f9 is POP ESI and 0x006413fa is RET, so nothing
// disturbs it. The returns of the transfers at 0xa4 and 0xa8 are therefore dead --
// never moved, never read, never compared -- and the model's return value is the
// third transfer's and nothing else. What the wrapper's own caller does with that
// word is not visible from inside this body; the eight vtable records are the only
// inbound references and none of them is a direct call.

#include "swarm_w1_006413d0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_006413d0 {

extern "C" Word PKG_SWARM_W1_006413D0_THISCALL re_006413d0(
    SporepediaReceiver* receiver) {
  // 006413d0  PUSH ESI
  // 006413d1  MOV ESI,ECX
  //
  // The receiver is copied into ESI and every access in the body goes through ESI.
  // ECX is then reused as the argument register of the second and third transfers
  // (0x006413e7 and 0x006413f5), which is why the machine record reports ECX with
  // shape R-ALIAS and why nothing below reads a receiver field through ECX. The
  // model keeps the receiver in one variable because the body keeps it in one
  // register: all three loads and all three receiver arguments are the same
  // pointer, and the package model test asserts that identity at each site.

  // 006413d3  MOV EAX,dword ptr [ESI]
  //
  // The dispatch word, one level of indirection, read as a dword and nothing else.
  // EAX is a table ADDRESS from here on; it is never treated as a table OBJECT and
  // never dereferenced twice.
  DispatchTable* const table_first = load_dispatch_table(receiver);

  // 006413d5  MOV EDX,dword ptr [EAX + 0xa4]
  //
  // The first target. A dword at displacement 0xa4 of the table -- a 4-byte stride,
  // not a byte offset, and not a slot index the model has any name for.
  const SlotTargetFirst first =
      target_from_word<SlotTargetFirst>(*word_at(table_first, kSlotFirstDisplacement));

  // 006413db  PUSH 0x0
  // 006413dd  CALL EDX
  //
  // One stack word, the literal 0, and the receiver in ECX. ECX is NOT re-established
  // here: the two loads and the PUSH do not write ECX, so the value the callee sees
  // is the entry ECX, which is this same receiver. The callee owns the word (RET 4 in
  // the concrete target 0x00641cd0), which is what keeps ESP at entry-4 for the
  // second transfer. The return word is left in EAX and immediately overwritten by
  // the load at 0x006413df: it is dead.
  (void)first(receiver, 0);

  // 006413df  MOV EAX,dword ptr [ESI]
  //
  // The dispatch word again, NOT the table pointer cached above. The body re-loads
  // it, so a first transfer that rewrites the receiver's leading word changes where
  // the second and third transfers go. The C++ re-load cannot be folded away,
  // because the call above is opaque and the receiver is not a local.
  DispatchTable* const table_second = load_dispatch_table(receiver);

  // 006413e1  MOV EDX,dword ptr [EAX + 0xa8]
  // 006413e7  MOV ECX,ESI
  // 006413e9  CALL EDX
  //
  // The second target, at displacement 0xa8, with NO stack word: nothing is pushed
  // between 0x006413e9's predecessor and the call, and the concrete target
  // 0x00641e10 is the one of the three that ends in a bare RET and pops nothing.
  // The return word is discarded, and discarding it is the point: EAX is overwritten
  // by the load at 0x006413eb.
  const SlotTargetSecond second = target_from_word<SlotTargetSecond>(
      *word_at(table_second, kSlotSecondDisplacement));
  (void)second(receiver);

  // 006413eb  MOV EAX,dword ptr [ESI]
  //
  // The third and last re-load of the same word.
  DispatchTable* const table_third = load_dispatch_table(receiver);

  // 006413ed  MOV EDX,dword ptr [EAX + 0xac]
  //
  // The third target, at displacement 0xac. This is the largest displacement in the
  // body and the reason the modelled table is at least 0xb0 bytes long.
  const SlotTargetThird third = target_from_word<SlotTargetThird>(
      *word_at(table_third, kSlotThirdDisplacement));

  // 006413f3  PUSH 0x0
  // 006413f5  MOV ECX,ESI
  // 006413f7  CALL EDX
  //
  // The third target, with the same literal 0 the first transfer was handed, and
  // with the receiver explicitly reloaded into ECX. This is the only transfer whose
  // return word survives: EAX is not written again before the RET. The concrete
  // target in the table at 0x013ff648 is 0x00641e40, whose terminator is
  // `5B 83 C4 14 C2 04 00` -- POP EBX; ADD ESP,0x14; RET 4 -- so it owns its word
  // and hands the wrapper a 32-bit result in EAX.
  const Word result = third(receiver, 0);

  // 006413f9  POP ESI
  // 006413fa  RET
  //
  // The epilogue, one register and a bare return. There is no ADD ESP and no
  // immediate on the RET, so the body consumes nothing of the caller's and the
  // callee-cleanup of all three transfers is the only stack discipline in play.
  // EAX is untouched between the third CALL and here, so the value leaving the
  // function is exactly what the third target returned.
  return result;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_006413d0
