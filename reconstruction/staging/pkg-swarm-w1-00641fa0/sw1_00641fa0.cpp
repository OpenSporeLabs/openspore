// PKG-SWARM-W1-00641FA0 -- VA 0x00641fa0
// FUN_00641fa0, the unnamed Sporepedia boolean predicate
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 22 instructions, 0x00641fa0..0x00641fcd inclusive, 46 bytes
// (ghidra_function.body_start 0x00641fa0, body_end 0x00641fcd, body_span_bytes 46,
// size_bytes 46). Every line below is annotated with the instruction it comes
// from, and the listing it was written against was re-decoded from the 46 image
// bytes for this package rather than taken on trust -- the byte string is in the
// header, it decodes to these 22 instructions, and it ends exactly at
// 0x00641fcd + 1.
//
//   00641fa0  PUSH ESI
//   00641fa1  MOV ESI,ECX
//   00641fa3  CMP dword ptr [ESI + 0x1c],0x0
//   00641fa7  JZ 0x00641fca
//   00641fa9  LEA EAX,[ESI + 0x4]
//   00641fac  PUSH EAX
//   00641fad  CALL 0x00641900
//   00641fb2  ADD ESP,0x4
//   00641fb5  TEST AL,AL
//   00641fb7  JZ 0x00641fca
//   00641fb9  MOV EDX,dword ptr [ESI]
//   00641fbb  MOV EAX,dword ptr [EDX + 0x68]
//   00641fbe  MOV ECX,ESI
//   00641fc0  CALL EAX
//   00641fc2  TEST AL,AL
//   00641fc4  JZ 0x00641fca
//   00641fc6  MOV AL,0x1
//   00641fc8  POP ESI
//   00641fc9  RET
//   00641fca  XOR AL,AL
//   00641fcc  POP ESI
//   00641fcd  RET
//
// SHAPE: a three-input conjunction with a shared false exit. All three JZ targets
// are the same instruction, 0x00641fca, and there is no other branch. The gates
// are tested in the fixed order: the receiver's own word at +0x1c, then the
// direct callee, then the virtual slot. The two callee tests are `TEST AL,AL` /
// `JZ`, i.e. fall through on NONZERO -- not on one.
//
// VIRTUAL DISPATCH: one indirect call, and it is TWO-LEVEL. 0x00641fb9 loads the
// table pointer out of the receiver's own +0x00, 0x00641fbb loads the slot word
// out of the TABLE at +0x68, and 0x00641fc0 calls the register. Neither level is
// optional and neither may be collapsed: reading `*(receiver + 0x68)` instead of
// `*(*(receiver + 0x00) + 0x68)` is a different address on every live object, and
// the model test plants a valid slot pointer at receiver+0x68 to make exactly
// that mistake observable rather than fatal.
//
// The machine-derived ABI record agrees on the shape: dispatch.indirect_calls 1,
// dispatch.call_offsets [] and dispatch.vtable_shaped_loads 0 -- the second of
// those is the record saying the load is a plain dword load at a displacement,
// with no shape it could recognise as a vtable access, which is why nothing below
// relies on the record for the slot and the listing supplies it.
//
// The slot index is 26 (0x68 / 4), which is NOT the index this body itself sits
// at in any of the three tables it is xref'd into: the data-side xrefs put it at
// 0x013ff6ac+0x0c (index 3), 0x01462764+0x64 (index 25) and 0x01489090+0x70
// (index 28), and reading those tables' own bytes shows their index 26 holds
// 0x00b1fbf0 and 0x006418b0 respectively -- a different function each time. So
// the two indices are provably independent and the +0x68 in the listing is the
// only thing that fixes the dispatch index.
//
// ABI: __thiscall, receiver in ECX, no ordinary stack argument, `RET` with no
// immediate on both exits, one saved register (ESI, pushed at 0x00641fa0 and
// popped at 0x00641fc8 and 0x00641fcc). The record agrees on all of it:
// abi.calling_convention __thiscall, abi.saved_registers ["ESI"], abi.ret_form
// "RET", abi.stack_cleanup_bytes 0, abi.stack_cleanup_owner "caller",
// abi.receiver_register "ECX", and receiver.offsets [0, 28] -- which is exactly
// the two displacements this body reaches, 0x00 and 0x1c, and 0x04 is a LEA
// rather than a load so the record does not list it.
//
// FIELDS: the machine-derived receiver record for this VA carries `bounds_only`
// with offsets [0, 28]. That states where the body was SEEN REACHING and not
// which member is which, so it can neither confirm nor refute a member name --
// and this file names none. The receiver is an opaque byte run; every access is a
// displacement through `word_at` (a load) or `address_at` (a LEA), and the table
// the receiver's leading word leads to has no type and no members at all. Each
// displacement is a named constexpr in the header, printed there against the one
// instruction that fixes it, and pinned by a static_assert.
//
// GLOBALS: none. No instruction in the body names a data-segment address.
//
// WRITES: none. There is no store instruction anywhere in the 22. The body reads
// two dwords of the receiver, takes the address of a third region of it, reads one
// dword of the table, and returns. The model test compares the receiver's bytes
// and the table's bytes before and after every call and requires them identical,
// so "this body caches nothing" is asserted rather than assumed.
//
// The decompiler disagrees in two places and the listing wins both times. Ghidra
// prints `__fastcall FUN_00641fa0(int *param_1)`; there is no use of EDX anywhere
// in the 22 instructions and the receiver demonstrably arrives in ECX
// (0x00641fa1, and 0x00641fbe reloading it for the indirect call), so the
// convention is __thiscall. And Ghidra prints `FUN_00641900(param_1 + 1)`, which
// is the same address this body pushes -- `param_1 + 1` on an `int *` is
// receiver + 4 -- but stated as a value the decompiler inferred rather than as
// the sub-object's address the machine forms with a LEA. Both printings agree on
// the control flow, and the model follows the listing.

#include "sw1_00641fa0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00641fa0 {

extern "C" std::uint8_t PKG_SW1_00641FA0_THISCALL sporepedia_predicate_00641fa0(
    SporepediaAssetDataOtdb* receiver) {
  // 00641fa0  PUSH ESI
  // 00641fa1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the ECX reload for the indirect call at 0x00641fbe. The
  // push is the save half of the one callee-saved register the body touches; both
  // exits pop it (0x00641fc8, 0x00641fcc). The model does not need to reproduce
  // the push -- the compiler saves whatever it uses -- but it is why ESI is on the
  // record's saved_registers list and why ECX is reported as an R-ALIAS receiver
  // rather than a fixed one.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT
  // into it, through `word_at` (a load) or `address_at` (a LEA). The record
  // enumerates offsets [0x00, 0x1c] and is bounds_only, so it states only where
  // the body was seen reaching and never which member is which: no member of the
  // receiver is named anywhere in this file, and neither is any member of the
  // dispatch table the receiver's leading word leads to.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00641fa3  CMP dword ptr [ESI + 0x1c],0x0
  // 00641fa7  JZ 0x00641fca
  //
  // Gate one. Four bytes at the receiver's own displacement 0x1c, compared against
  // zero, and the JZ is TAKEN when the dword is zero -- so the body proceeds only
  // when the word is NONZERO. This is a compare of the word itself: the body never
  // dereferences it, so it is not a pointer-null test and not a test of anything
  // behind it. The two distinguishable readings, both of which the model test
  // drives, are a one-byte test (a dword of 0x00000100 would be a false to it and
  // is a true here) and a dereference (a pointer to a zero word is a true to it
  // and is a false here).
  //
  // The jump target is the shared false exit, so a zero here means the direct
  // callee is never reached.
  if (word_at(self, kReceiverGateWordDisplacement) == 0u) {
    // 00641fca  XOR AL,AL
    // 00641fcc  POP ESI
    // 00641fcd  RET
    return 0u;
  }

  // 00641fa9  LEA EAX,[ESI + 0x4]
  // 00641fac  PUSH EAX
  // 00641fad  CALL 0x00641900
  // 00641fb2  ADD ESP,0x4
  //
  // Gate two, and the one direct call in the body. What goes over the stack is
  // the ADDRESS of the receiver's +0x04 region, formed by a LEA: no load of
  // [ESI+0x4] happens, so the dword stored there is data for the callee and is
  // never tested here. The word is dropped by this body at 0x00641fb2, which
  // together with 0x00641900's argument-free `RET` epilogue fixes the callee's
  // convention as cdecl with exactly one stack word.
  if (asset_data_sub_predicate_00641900(
          reinterpret_cast<AssetDataSubObject04*>(address_at(self, kReceiverSubObjectDisplacement))) ==
      0u) {
    // 00641fb5  TEST AL,AL
    // 00641fb7  JZ 0x00641fca
    //
    // The two-byte idiom is a test of the whole of AL against zero, so the branch
    // is taken for every zero BYTE -- 0x00 only -- and the fall-through covers
    // every other value, 0x01 through 0xff alike. It is emphatically not a
    // comparison against 1, and the model test drives 0x80 through this gate.
    return 0u;
  }

  // 00641fb9  MOV EDX,dword ptr [ESI]
  //
  // The first level of the two-level dispatch: the table pointer is the dword at
  // the receiver's own displacement 0x00. Note the shape -- the receiver's leading
  // word IS the table pointer, which is why the second level reads through a base
  // taken from that WORD and never through the receiver.
  const Word table_pointer = word_at(self, kReceiverTableDisplacement);

  // 00641fbb  MOV EAX,dword ptr [EDX + 0x68]
  //
  // The second level, and the slot displacement is 0x68, index 26. It is read out
  // of the object the word above addresses, by displacement, so neither level is a
  // load through the other and no member of the table is named. `load_slot` takes
  // the base as a `Word` precisely so the two steps cannot be folded into one
  // dereference: the model test parks a live slot pointer at receiver+0x68 and a
  // second, decoy table behind receiver+0x00, and each of the two mistakes that
  // invites fires a different observer.
  const Word slot_target = load_slot(table_pointer, kDispatchSlotDisplacement);

  // 00641fbe  MOV ECX,ESI
  // 00641fc0  CALL EAX
  //
  // The receiver of the indirect call is the receiver ITSELF -- the value ESI
  // holds, which is the object the caller passed in ECX. It is not the table
  // pointer that 0x00641fb9 just loaded, and it is not the +0x04 sub-object that
  // 0x00641fa9 formed. No stack word is pushed, so this callee is receiver-only.
  if (invoke_dispatch_slot(slot_target, receiver) == 0u) {
    // 00641fc2  TEST AL,AL
    // 00641fc4  JZ 0x00641fca
    //
    // The same byte test as gate two, with the same consequence: nonzero falls
    // through, including the values that are not 1.
    return 0u;
  }

  // 00641fc6  MOV AL,0x1
  // 00641fc8  POP ESI
  // 00641fc9  RET
  //
  // All three gates fell through, and the result is the CONSTANT 1 -- the value
  // the dispatch target returned is not propagated, it is only tested for
  // nonzero. So a target returning 0x37 or 0xff still produces exactly 1, and a
  // target returning 0 produces exactly 0 (through 0x00641fca).
  //
  // The declared return type is uint8_t, and the two are separate claims. The TYPE
  // is a byte because the two exits write AL and not EAX (MOV AL,0x1 here,
  // XOR AL,AL at 0x00641fca), so exactly one byte of the result is this body's
  // own and the upper three are the dispatch target's leftovers -- which no record
  // fixes and the model does not carry. The {0, 1} NORMALISATION is a fact about
  // the value set, not about the type, and is recorded as a machine
  // classification in the sidecar rather than spelled here: a type is not named
  // after a phrase, and a `bool` would be wrong on its own terms because the
  // machine is a byte test and a byte store, not a comparison against true.
  //
  // The three returns above are the same 0x00641fca path the JZs name; writing
  // them as early returns is the same control flow with the shared exit spelled
  // once per arm.
  return 1u;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641fa0
