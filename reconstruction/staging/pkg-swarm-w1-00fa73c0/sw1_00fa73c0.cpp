// PKG-SWARM-W1-00FA73C0 -- VA 0x00fa73c0
// FUN_00fa73c0 @ 0x00fa73c0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 46 instructions, 0x00fa73c0..0x00fa744b inclusive, 140 bytes
// (ghidra_function.body_start 0x00fa73c0, body_end 0x00fa744b, size_bytes 140).
// Every line of the model below is annotated with the instruction it comes from.
// The listing this was written against was re-derived from the image bytes for this
// package (objdump -b binary -m i386 -M intel over the 140 bytes at file offset
// 0xba67c0) and matches the committed Ghidra listing instruction for instruction at
// all 46 addresses; the full listing is reproduced in the package header.
//
// WHAT THE BODY DOES, IN ORDER, ALL OF IT FIXED BY THE BYTES:
//
//   1. copy two words out of the receiver, at +0x798 and +0x79c          (0x00fa73c4, 0x00fa73cb)
//   2. hand 0x00f9f770 the triple (+0x79c, +0x79c, +0x798)                (0x00fa73d1..0x00fa73d4)
//   3. drop those three words itself                                      (0x00fa7400)
//   4. snap the word at +0x79c in whole 0xac steps toward the word at +0x798
//                                                                       (0x00fa73d9..0x00fa73f2)
//   5. call the sub-object's dispatch word at table displacement +0x18 three
//      times, with the immediates 0x0536250c, 0x0536250d and 0x03a23f9a     (0x00fa73f8..0x00fa7426)
//   6. call 0x00fbaf10 and then 0x00fbaf50, both on the sub-object at +0x20c
//      and both with the literal 0                                        (0x00fa7428..0x00fa743d)
//   7. increment the word at +0x814                                       (0x00fa7442)
//
// STEP 2 IS PROVABLY A NO-OP FOR THIS CALLER, and that is worth stating because it
// is the kind of thing a decompilation hides. 0x00fa73d2 and 0x00fa73d3 push the
// SAME register (EDI) twice, so arguments 1 and 2 of 0x00f9f770 are bit-for-bit
// equal. 0x00f9f770's own body compares exactly those two words first
// (0x00f9f77a `CMP ESI,EBX`) and jumps to 0x00f9f7a1 on equality, where it loads
// its THIRD word and returns it. So the callee runs no loop, never reaches its
// 0xac-strided element walk, and returns the value the caller already had in EBX.
// Its return value is then dead: the very next instruction is 0x00fa73d9
// `SUB EDI,EBX`, which does not read EAX. The model still performs the call -- it
// is in the listing and its arguments are observable -- and the model test asserts
// both the argument identity and the deadness of the result.
//
// FRAME, resolved once against the entry ESP so every displacement below is a fact.
// Entry ESP is 0 in the walk. Nothing in the 46 instructions touches EBP, does a
// SUB ESP or a LEA on ESP, so the only stack movement is the pairs below, and
// abi_derived.parse agrees (frame {fp false, sub null, lea_esp null, and_esp null,
// mov_ebp_esp false}, local_extent 0).
//
//   0x00fa73c0  PUSH EBX                 -> -4    saved EBX, read back by 0x00fa744a
//   0x00fa73c1  PUSH ESI                 -> -8    saved ESI, read back by 0x00fa7449
//   0x00fa73ca  PUSH EDI                 -> -12   saved EDI, read back by 0x00fa7448
//   0x00fa73d1  PUSH EBX                 -> -16
//   0x00fa73d2  PUSH EDI                 -> -20
//   0x00fa73d3  PUSH EDI                 -> -24
//   0x00fa73d4  CALL 0x00f9f770           -> -28   callee ends in a bare RET, -> -24
//   0x00fa7400  ADD ESP,0xc              -> -12   the body drops the three words itself
//   0x00fa7403  PUSH 0x0536250c          -> -16
//   0x00fa7408  CALL EAX                 -> -20   dispatched callee ends in RET 4, -> -12
//   0x00fa7412  PUSH 0x0536250d          -> -16
//   0x00fa7417  CALL EAX                 -> -20                              -> -12
//   0x00fa7421  PUSH 0x03a23f9a          -> -16
//   0x00fa7426  CALL EAX                 -> -20                              -> -12
//   0x00fa742e  PUSH 0x0                 -> -16
//   0x00fa7430  CALL 0x00fbaf10          -> -20   callee ends in RET 4,     -> -12
//   0x00fa743b  PUSH 0x0                 -> -16
//   0x00fa743d  CALL 0x00fbaf50          -> -20   callee ends in RET 4,     -> -12
//   0x00fa7448  POP EDI                  -> -8
//   0x00fa7449  POP ESI                  -> -4
//   0x00fa744a  POP EBX                  -> 0
//   0x00fa744b  RET                      -> +4    the caller's ESP after its CALL
//
// Two things fall out of that walk and both are load-bearing:
//
//   * The frame carries NO ordinary arguments. Three words go down and three come
//     up, and every word the body pushes for a callee is either dropped by the
//     body itself or by that callee. So the signature is __thiscall with a
//     receiver and nothing else, which is why this package's function takes one
//     parameter. Ghidra's own record for this VA carries parameter_count 0 and
//     signature "undefined FUN_00fa73c0(void)" and the decompilation models the
//     receiver as an explicit `int param_1`; that is the same single receiver seen
//     through a stack-slot fiction, and the walk above is the reason it does not
//     imply a second argument.
//   * Each of the three dispatched callees MUST remove its own pushed word. The
//     body never executes a second `ADD ESP`, and the walk only returns to -12
//     after each CALL if the callee did `ret 4` rather than a bare `ret`. A bare
//     `ret` would leave ESP at -16 after the first call, and the three epilogue
//     POPs would then read the three immediate arguments instead of the saved
//     registers and would return to the wrong address. The model test asserts
//     this ledger arithmetic rather than trusting a convention comment.
//
// VIRTUAL DISPATCH: three, all through the SAME chain and all at the SAME table
// displacement. Each is resolved afresh, never cached:
//
//   0x00fa73f8  MOV ECX,DWORD PTR [ESI + 0x28]   level 0: the receiver's word
//   0x00fa73fb  MOV EDX,DWORD PTR [ECX]          level 1: the sub-object's word 0
//   0x00fa73fd  MOV EAX,DWORD PTR [EDX + 0x18]   level 2: table dword index 6
//   0x00fa7408  CALL EAX
//   0x00fa740a..0x00fa740f                       the same three loads again
//   0x00fa7417  CALL EAX
//   0x00fa7419..0x00fa741e                       the same three loads again
//   0x00fa7426  CALL EAX
//
// Two levels of indirection, not one: the word at receiver+0x28 is a pointer to an
// object, and the DISPATCH WORD is that object's word 0, not the receiver's word.
// abi_derived.dispatch records {indirect_calls 3, call_offsets [], vtable_shaped_loads
// 0}; the 3 agrees with the listing, and the 0 for vtable_shaped_loads does not --
// the tool does not classify `MOV EDX,[ECX]` / `MOV EAX,[EDX+0x18]` as a
// vtable-shaped pair. The listing is followed here and the disagreement is recorded
// in the sidecar. The reload fact is observable and the model test drives it: if
// the first dispatched callee re-points the sub-object's dispatch word, the second
// and third calls must go to the NEW word.
//
// One ordering detail that has no consequence in C++ but is stated for the record:
// the first chain is resolved at 0x00fa73f8..0x00fa73fd BEFORE the `ADD ESP,0xc` at
// 0x00fa7400, and only then is the immediate pushed. The second and third chains
// are resolved after the cleanup. Since the resolution touches no stack, moving it
// across the cleanup is unobservable; the model resolves each chain immediately
// before its own call and the ordering is not claimed as load-bearing.
//
// GLOBALS: none. No instruction in the 46 names a data-segment address, and every
// absolute operand in the body is either a code address (the three CALL rel32) or
// an immediate the body pushes. The two table bases 0x016d6d30 and 0x016d6d70 that
// the two 0xfbaf* callees index live in those CALLEES, not in this body, and lie
// outside every section header in this file, so their contents are not recoverable
// from this image and nothing here claims anything about them.

#include "sw1_00fa73c0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0 {
namespace {

// 0x00fa73e2  SAR EDX,0x5 -- an arithmetic right shift of a 32-bit value, written
// out of a logical shift plus a sign fill so that no step depends on an
// implementation-defined right shift of a negative value. `count` is 5 in the one
// place this is used, and the zero case is guarded because `x << 32` is undefined.
std::int32_t sar32(std::int32_t value, unsigned count) {
  const std::uint32_t bits = static_cast<std::uint32_t>(value);
  const std::uint32_t fill =
      (value < 0 && count != 0u) ? (~Word{0u} << (32u - count)) : Word{0u};
  return static_cast<std::int32_t>((bits >> count) | fill);
}

// 0x00fa73f8..0x00fa73fd, 0x00fa740a..0x00fa740f, 0x00fa7419..0x00fa741e -- the
// three-load dispatch chain, as a function so that the model resolves it once per
// call exactly as the machine does.
//
// Level 0 (0x00fa73f8) reads the receiver's word at kDispatchObjectDisplacement.
// Level 1 (0x00fa73fb) dereferences THAT, so the value just read is a pointer to an
// object and the word at the object's displacement 0 is the dispatch word.
// Level 2 (0x00fa73fd) indexes the dispatch word at kDispatchWordDisplacement,
// i.e. dword index 6.
//
// The receiver of the call is the level-0 value, not the level-1 table and not the
// outer receiver: ECX still holds the word 0x00fa73f8 loaded when the CALL at
// 0x00fa7408 executes, which is why the call is a thiscall on the sub-object.
DwordThunk resolve_dispatch_target(void* sub_object) {
  void* const dispatch_word = *pointer_at(sub_object, 0x00);
  return reinterpret_cast<DwordThunk>(
      *word_at(dispatch_word, kDispatchWordDisplacement));
}

}  // namespace

// The six instructions 0x00fa73d9..0x00fa73ec, factored out of the body so that
// the model test can drive this exact code over the whole 32-bit domain instead of
// only over a handful of hand-picked inputs. The body below calls it and does
// nothing else with EAX between 0x00fa73d9 and 0x00fa73f2, so factoring changes
// nothing observable; the arithmetic itself is annotated instruction by
// instruction below, and the identity the six instructions implement is proved
// exhaustively by the model test rather than asserted here.
//
// The name carries NO address, and that is deliberate on both counts. It does not
// carry 0x00fa73c0 because that is the entry of the body under reconstruction, not
// of this six-instruction fragment, and a helper stamped with the target's own
// address competes with the target for the address-to-symbol binding a reader
// resolves by name -- sw1_snap_and_dispatch_00fa73c0 below is the definition that
// owns 0x00fa73c0. Nor does it carry 0x00fa73d9, the first instruction it models:
// the OTHER helpers here are named for the addresses they call, and that is
// correct for them (for_each_stride_ac_00f9f770 and select_from_table_a_00fbaf10
// are real CALL targets at 0x00f9f770 and 0x00fbaf10), but this one is a fragment
// folded out of the target itself, not a callee, and naming it after an address
// would read as a transfer of control to 0x00fa73d9 -- which is `SUB EDI,EBX`, the
// first instruction of the body and not the start of anything. So it is named for
// what it computes; the six addresses are in the comment above and on every
// arithmetic line below.
extern "C" Word snap_delta_step(Word range_first, Word cursor) {
  // 00fa73d9  SUB EDI,EBX
  //
  // A 32-bit SUB, so it WRAPS rather than being a checked subtraction. The result
  // is signed from here on because 0x00fa73e0 `IMUL EDI` is the signed
  // one-operand form.
  const Word delta_bits = cursor - range_first;

  // 00fa73db  MOV EAX,0xd05f417d
  // 00fa73e0  IMUL EDI
  //
  // A signed 64-bit product of the delta by the magic; the machine keeps the high
  // half in EDX and the low half in EAX, and only the high half is used.
  const std::int64_t wide =
      static_cast<std::int64_t>(as_signed(delta_bits)) *
      static_cast<std::int64_t>(as_signed(kSnapMagic));

  // 00fa73e2  SAR EDX,0x5
  //
  // The high half, sign-extended to 32 bits by taking EDX's own 32 bits, then
  // shifted arithmetically by 5.
  const std::int32_t high = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(static_cast<std::uint64_t>(wide) >> 32));
  const std::int32_t shifted = sar32(high, kSnapShift);

  // 00fa73e5  MOV EAX,EDX
  // 00fa73e7  SHR EAX,0x1f
  // 00fa73ea  ADD EAX,EDX
  //
  // The add-sign correction. SHR is LOGICAL, so this yields 1 for a negative
  // EDX and 0 for a non-negative one -- not -1, which is what a C++ `>> 31` on a
  // signed value would give. The two addends are combined in unsigned arithmetic
  // so that the 32-bit add wraps exactly as the machine's does.
  const std::uint32_t quotient =
      static_cast<std::uint32_t>(shifted) +
      (static_cast<std::uint32_t>(shifted) >> 31);

  // 00fa73ec  IMUL EAX,EAX,0xac
  //
  // A 32-bit multiply by 0xac, so it wraps.
  return quotient * kSnapStride;
}

extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL sw1_snap_and_dispatch_00fa73c0(
    Receiver* receiver) {
  // 00fa73c2  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the last one at 0x00fa7442. ECX is then free to be an
  // argument register for the 0x00fbaf* calls, which is why nothing here reads a
  // receiver word through ECX and why the machine-derived receiver record reports
  // register ECX with shape R-ALIAS.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT
  // into it. The record enumerates offsets [40, 524, 1944, 1948, 2068] -- 0x28,
  // 0x20c, 0x798, 0x79c, 0x814 -- with bounds_only true, so it says where the body
  // was seen reaching and not which member is which. No member is named for any of
  // them, and nothing at +0x00..+0x27, +0x29..+0x20b, +0x20d..+0x797, +0x79a..+0x813
  // or +0x815..+0x817 is touched.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00fa73c4  MOV EBX,DWORD PTR [ESI + 0x798]
  //
  // The third argument of the call in step 2 and the fixed point of the snap in
  // step 4. Read once, before anything else happens, and never re-read: the only
  // write this body makes anywhere near it is the read-modify-write at 0x00fa73f2,
  // which is at +0x79c and not here.
  const Word range_first = *word_at(self, kRangeFirstFieldDisplacement);

  // 00fa73ca  PUSH EDI              -- saved EDI, restored by 0x00fa7448
  // 00fa73cb  MOV EDI,DWORD PTR [ESI + 0x79c]
  //
  // The word that is both the first and the second argument of the call below, and
  // the word the snap writes. One read, three uses.
  const Word cursor = *word_at(self, kSnapFieldDisplacement);

  // 00fa73d1  PUSH EBX              -- argument 3
  // 00fa73d2  PUSH EDI              -- argument 2
  // 00fa73d3  PUSH EDI              -- argument 1
  // 00fa73d4  CALL 0x00f9f770
  //
  // cdecl, three words, pushed right to left, so argument 1 is the LAST push. The
  // order is fixed by the callee's own frame reads, not by its decompilation:
  // 0x00f9f771 `MOV EBX,[ESP+0xc]` with ESP at entry-4 is argument 2 and
  // 0x00f9f776 `MOV ESI,[ESP+0xc]` with ESP at entry-8 is argument 1, and both of
  // them are the EDI the caller pushed.
  //
  // The value is used and thrown away. 0x00f9f770 compares its arguments 1 and 2
  // for equality at 0x00f9f77a and, on the equality this caller guarantees, takes
  // the early return at 0x00f9f7a1 which loads its argument 3 into EAX. The body
  // then does 0x00fa73d9 `SUB EDI,EBX` and never looks at EAX again, so the result
  // is dead. The model does not use it, and the model test poisons the callee's
  // return to prove that.
  //
  // The words are passed as opaque void* because this body never dereferences
  // them: whether receiver+0x798 and receiver+0x79c hold pointers is unresolved,
  // and the model test plants values that are not dereferenceable to show that
  // nothing in the reconstruction follows them.
  (void)for_each_stride_ac_00f9f770(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(cursor)),
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(cursor)),
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(range_first)));

  // 00fa7400  ADD ESP,0xc
  //
  // The caller-side cleanup, and the ONLY one in the body. It belongs here because
  // 0x00f9f770 ends in a bare RET with no immediate -- both of its exits do
  // (0x00f9f7a0 and 0x00f9f7a7) -- so it returns without touching ESP. In C++ the
  // cleanup is attached to the call above and has no separate spelling; the
  // position of the instruction, after the first dispatch chain is resolved, is
  // recorded in the file header and is not observable.

  // 00fa73d9  SUB EDI,EBX
  // 00fa73db  MOV EAX,0xd05f417d
  // 00fa73e0  IMUL EDI
  // 00fa73e2  SAR EDX,0x5
  // 00fa73e5  MOV EAX,EDX
  // 00fa73e7  SHR EAX,0x1f
  // 00fa73ea  ADD EAX,EDX
  // 00fa73ec  IMUL EAX,EAX,0xac
  //
  // The whole snap amount, as one value. The six instructions are written out
  // inside snap_delta_step with their own addresses so the model test can
  // drive this exact arithmetic over the entire 32-bit domain; the body computes
  // nothing with EAX in between, so the factoring is not observable.
  const Word delta_snap = snap_delta_step(range_first, cursor);

  // 00fa73f2  ADD DWORD PTR [ESI + 0x79c],EAX
  //
  // The only write the body makes before the three dispatches, and a
  // READ-MODIFY-WRITE of memory rather than an add into EDI: the model re-reads
  // the word from the receiver instead of reusing `cursor`, because the instruction
  // reads memory and a reconstruction that assumed the register still held it would
  // be assuming something the machine never checked. Nothing between 0x00fa73cb
  // and here wrote that word, so the two forms agree here -- and the model test
  // proves the observer-visible order rather than assuming it.
  //
  // WHAT THE SIX INSTRUCTIONS ARE EQUAL TO, stated as an identity and not as a
  // guess: over the whole 32-bit signed domain the value added is exactly
  //     -(trunc(delta / 172)) * 172
  // with trunc() the C++ signed integer division, i.e. division rounding toward
  // zero. So for a delta that is an exact multiple of 0xac the word at +0x79c
  // lands ON the word at +0x798, and otherwise it moves in whole 0xac steps toward
  // it, always overshooting it by less than 0xac, and always in the direction of
  // the sign of the delta. The model test proves the identity rather than taking it
  // from this comment, and drives the four ways it can be got wrong: a floor-based
  // shift, a positive-divisor division, an unsigned compare on the delta, and a
  // non-wrapping 32-bit add.
  *word_at(self, kSnapFieldDisplacement) += delta_snap;

  // 00fa73f8  MOV ECX,DWORD PTR [ESI + 0x28]
  // 00fa73fb  MOV EDX,DWORD PTR [ECX]
  // 00fa73fd  MOV EAX,DWORD PTR [EDX + 0x18]
  // 00fa7403  PUSH 0x0536250c
  // 00fa7408  CALL EAX
  {
    // The receiver of the dispatched call is the LEVEL-0 value -- the word read out
    // of the receiver -- because ECX still holds it at the CALL. It is not the
    // dispatch word and not the outer receiver, and the model test plants a decoy
    // at the receiver's own +0x00 to keep those apart.
    void* const first_sub_object = *pointer_at(self, kDispatchObjectDisplacement);
    DwordThunk const first_target = resolve_dispatch_target(first_sub_object);
    first_target(first_sub_object, kFirstDispatchWord);
  }

  // 00fa740a  MOV ECX,DWORD PTR [ESI + 0x28]
  // 00fa740d  MOV EDX,DWORD PTR [ECX]
  // 00fa740f  MOV EAX,DWORD PTR [EDX + 0x18]
  // 00fa7412  PUSH 0x0536250d
  // 00fa7417  CALL EAX
  //
  // The chain is resolved AGAIN, from the receiver, not from anything the previous
  // call left behind and not from the pointer the previous call resolved. A
  // reconstruction that cached the target would miss a re-point.
  {
    void* const second_sub_object = *pointer_at(self, kDispatchObjectDisplacement);
    DwordThunk const second_target = resolve_dispatch_target(second_sub_object);
    second_target(second_sub_object, kSecondDispatchWord);
  }

  // 00fa7419  MOV ECX,DWORD PTR [ESI + 0x28]
  // 00fa741c  MOV EDX,DWORD PTR [ECX]
  // 00fa741e  MOV EAX,DWORD PTR [EDX + 0x18]
  // 00fa7421  PUSH 0x03a23f9a
  // 00fa7426  CALL EAX
  //
  // The third and last dispatch, resolved afresh once more. Same table
  // displacement, different immediate. The immediates are 0x0536250c, 0x0536250d
  // and 0x03a23f9a in that order and are NOT named: nothing in this repository
  // says what any of them means, and the first two being adjacent integers is an
  // observation about their bit patterns and nothing more.
  {
    void* const third_sub_object = *pointer_at(self, kDispatchObjectDisplacement);
    DwordThunk const third_target = resolve_dispatch_target(third_sub_object);
    third_target(third_sub_object, kThirdDispatchWord);
  }

  // 00fa7428  MOV ECX,DWORD PTR [ESI + 0x20c]
  // 00fa742e  PUSH 0x0
  // 00fa7430  CALL 0x00fbaf10
  //
  // A different displacement from the one above, read as a pointer and handed over
  // as the hidden receiver of a DIRECT callee this time -- 0x00fbaf10's own first
  // comparison is `CMP DWORD PTR [ECX+0x5c0],EAX`, so it dereferences ECX and this
  // word must be a pointer. The argument is the immediate 0, pushed with a one-byte
  // `PUSH 0x0` (0x6a 0x00), and the callee removes it with its own `RET 0x4`.
  {
    void* const table_sub_object = *pointer_at(self, kTableObjectDisplacement);
    select_from_table_a_00fbaf10(table_sub_object, 0u);
  }

  // 00fa7435  MOV ECX,DWORD PTR [ESI + 0x20c]
  // 00fa743b  PUSH 0x0
  // 00fa743d  CALL 0x00fbaf50
  //
  // The SAME displacement, re-read from the receiver rather than reused from the
  // register the previous call left it in. If 0x00fbaf10 re-points that word, this
  // call must see the new value, and the model test drives exactly that.
  //
  // 0x00fbaf50 is not the same operation as 0x00fbaf10: its own bytes compare
  // against the receiver word at +0x5c4 where 0x00fbaf10 uses +0x5c0, and it walks
  // the receiver's own +0x1f4 where 0x00fbaf10 biases ECX by +0x20c instead. The
  // model keeps two calls, not one.
  {
    void* const table_sub_object = *pointer_at(self, kTableObjectDisplacement);
    select_from_table_b_00fbaf50(table_sub_object, 0u);
  }

  // 00fa7442  INC DWORD PTR [ESI + 0x814]
  //
  // The last thing the body does, after all five transfers, and a 32-bit
  // read-modify-increment of memory, so it wraps like an ADD would. It is the
  // only write this body makes to the receiver apart from the snap at 0x00fa73f2,
  // and the machine-derived receiver record's written_through 2 is these two.
  ++*word_at(self, kCounterDisplacement);

  // 00fa7448  POP EDI
  // 00fa7449  POP ESI
  // 00fa744a  POP EBX
  // 00fa744b  RET
  //
  // The epilogue, unmodelled: it restores the three saved registers and returns
  // with no immediate, leaving no argument words behind because the frame never
  // had any. It produces no value. EAX is live at 0x00fa744b holding 0x00fbaf50's
  // own return word -- nothing in this body writes EAX for its caller after
  // 0x00fa741e, and 0x00fa7442 does not touch EAX -- and the declared return type
  // is void. That EAX residue is documented, not modelled, and the model test
  // asserts nothing about it; the disagreement between the records over whether
  // this function is void is carried in the sidecar.
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0
