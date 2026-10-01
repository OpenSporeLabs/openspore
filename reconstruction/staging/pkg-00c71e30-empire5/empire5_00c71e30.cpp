#include "empire5_00c71e30.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares, and note 9 of the header is where the
// question of whether the bytes discriminate __thiscall from __fastcall is
// answered (they do not - see note 9 - so the macro follows the derived
// record's own name for the shape and nothing below depends on the difference).
#if defined(_MSC_VER)
#define PKG_00C71E30_THISCALL __thiscall
#else
#define PKG_00C71E30_THISCALL __attribute__((thiscall))
#endif

// 0x00c71e30 FUN_00c71e30 - a two-guard delegation whose passing arm reaches a
// table slot through the receiver, then a one-argument lookup.
//
// Raw bytes 0x00c71e30..0x00c71e6a:
//     56                 PUSH ESI
//     8b f1              MOV ESI,ECX
//     8b 8e 3c 01 00 00  MOV ECX,dword ptr [ESI + 0x13c]
//     85 c9              TEST ECX,ECX
//     74 2a              JZ 0x00c71e67
//     e8 6e bc f1 ff     CALL 0x00b8dab0
//     83 f8 05           CMP EAX,0x5
//     75 20              JNZ 0x00c71e67
//     8b 86 d4 00 00 00  MOV EAX,dword ptr [ESI + 0xd4]
//     8b 50 4c           MOV EDX,dword ptr [EAX + 0x4c]
//     8d 8e d4 00 00 00  LEA ECX,[ESI + 0xd4]
//     ff d2              CALL EDX
//     50                 PUSH EAX
//     e8 42 b4 ec ff     CALL 0x00b3d2a0
//     8b c8              MOV ECX,EAX
//     e8 0b 75 f3 ff     CALL 0x00ba9370
//     5e                 POP ESI
//     c3                 RET
//     33 c0              XOR EAX,EAX
//     5e                 POP ESI
//     c3                 RET
//     cc cc cc cc cc     INT3 pad (NOT part of the body)
//
// The shape in one sentence: if the receiver holds a non-null pointer at
// +0x13c, and that delegated object reports the scalar 5, then call the slot
// nineteen words along the table its own receiver holds at +0xd4 - passing that
// receiver's ADDRESS - and hand the slot's result to a one-argument lookup
// whose receiver is a global-slot read.
//
// ESI is not a place this body keeps the receiver across its calls. 0x00c71e31
// COPIES the receiver into ESI and the prologue's PUSH ESI exists because that
// copy makes ESI callee-saved state (header note 3). The receiver is re-read
// from ESI at 0x00c71e33, 0x00c71e47 and 0x00c71e50, and the one call that
// happens between those reads is 0x00c71e3d - whose callee is seven bytes that
// never name ESI. ECX is a different matter again: 0x00c71e5e overwrites it
// with the previous call's result, so the last callee's receiver is that
// result and nothing has to survive it.
//
// The displacement is spelled literally as a value, NOT as `receiver->field`.
// The disassembly establishes the displacement (0x13c and 0xd4), the width
// (32-bit) and the base (ESI); it establishes nothing about which member of any
// type occupies either word, and the receiver record says so itself
// (`bounds_only: true`). A member name here would be a field-identity assertion
// with nothing behind it.
//
// What is deliberately NOT done here:
//   * no name for the word at +0x13c, for the word at +0xd4, or for the
//     receiver's class;
//   * no claim that the table at +0xd4 is a C++ vtable - the two-level load
//     SHAPE is proven, the identity behind it is not;
//   * no null check on the RECEIVER itself - the body reads through it
//     unconditionally and does not test it, so a null receiver faults exactly
//     as the machine does;
//   * no interpretation of the constant 5, which is the immediate 0x00c71e42
//     compares against and nothing the evidence names;
//   * no source-level return type beyond the 32-bit width both arms are proven
//     to produce - one sampled caller dereferences the result and one null-tests
//     it, so the game-level type is UNKNOWN;
//   * no mask, saturate, range check or default of any kind on any path;
//   * no calling convention claim beyond the shape header note 9 states, and no
//     variadic behaviour (the record's `variadic` is UNKNOWN).

namespace openspore::reconstruction::pkg_00c71e30_empire5 {

// The two injection points the header declares, defined here because they are
// part of the modelled package and not of the machine. See the header for why
// they exist and for what is deliberately NOT modelled behind them.
SlotWord g_global_slot_value = 0;
SlotWord g_lookup_result = 0;

// The observation channel the modelled lookup records its two inputs into, so
// the entry's argument routing is something the model test can read rather than
// something it has to be told. See the header.
LookupObservation g_lookup_observation = {nullptr, 0u, 0u};

SlotWord PKG_00C71E30_THISCALL helper_00b8dab0(DelegatedReceiver* receiver) {
  // 0x00b8dab0 8b 81 94 01 00 00  MOV EAX,dword ptr [ECX + 0x194]
  // 0x00b8dab6 c3                 RET
  //
  // The MECHANISM of the promotion target, reproduced so the receiver this entry
  // hands over is observable and can be asserted. Read live at 0x00b8dab0 for
  // this package; the promoted package pkg-00b8dab0-field194-getter is the
  // record of that address and is not restated here (header note 4).
  //
  // One 32-bit load through the receiver that was handed over, one return. No
  // branch, no test, no write, no mask - so whatever word sits at +0x194 of the
  // transferred object comes back bit for bit, and a word of zero comes back as
  // a published zero. There is deliberately no null check: that body is seven
  // bytes and contains none, so adding one would be modelling something the
  // listing does not have, and a dropped guard in the CALLER is then a genuine
  // fault rather than a silent default.
  return delegated_target_word_at(receiver);
}

SlotWord PKG_00C71E30_THISCALL helper_00b3d2a0() {
  // 0x00b3d2a0 a1 e4 ea 67 01  MOV EAX,moffs32 [0x0167eae4]
  // 0x00b3d2a5 c3                RET
  //
  // Modelled for its INTERFACE, and for nothing else (header note 7). The real
  // body reads one word from an absolute data address and returns it; the
  // address is that function's, not this body's, and it is named nowhere in
  // this package.
  //
  // Two facts about the interface are load-bearing and both are why this is
  // spelled with no parameter at all. First, it takes NO receiver and NO
  // argument: the opcode is 0xa1, the `MOV EAX, moffs32` form, which carries a
  // 32-bit absolute address and NO ModRM byte at all - so there is no register
  // field present that a receiver could have arrived in, and none a stack
  // argument could have been read through. Second, its RET is the bare 0xc3, so
  // it pops NOTHING - which is what leaves the word pushed at 0x00c71e58 alive
  // for 0x00ba9370 to consume.
  //
  // What this body reads is NOT modelled, so the result below is whatever the
  // caller of this function supplies. That is deliberate: the entry uses this
  // value only as the RECEIVER of the last call, and what the model test needs
  // to check is the routing - that this call's result, and not the pushed word,
  // is what 0x00ba9370 receives.
  return g_global_slot_value;
}

SlotWord PKG_00C71E30_THISCALL lookup_empire_00ba9370(EmpireIndex* receiver,
                                                     std::uint32_t political_id) {
  // 0x00ba9370 Simulator_LookupEmpireByPoliticalId, read live at that address.
  // Modelled for its interface and nothing more (header note 7):
  //
  //     0x00ba9370  55           PUSH ECX
  //     0x00ba9371  83 7c 24 08 ff  CMP dword ptr [ESP + 0x8],-0x1
  //     0x00ba9376  56           PUSH ESI
  //     0x00ba9377  8b f1        MOV ESI,ECX
  //     ...
  //     0x00ba939f  5e           POP ESI
  //     0x00ba93a0  59           POP ECX
  //     0x00ba93a1  c2 04 00     RET 0x4
  //     ...
  //     0x00ba93a6  5e           POP ESI
  //     0x00ba93a7  59           POP ECX
  //     0x00ba93a8  c2 04 00     RET 0x4
  //
  // THREE facts are transcribed here and the rest of the body is not:
  //
  //   1. Its receiver arrives in ECX (0x00ba9377 copies it), so the second
  //      parameter of this model is not its receiver - the first is.
  //   2. It READS one ordinary stack argument. `CMP dword ptr [ESP + 0x8],-0x1`
  //      at 0x00ba9371 executes after its own `PUSH ECX`, so [ESP+0x8] is
  //      [ESP+4] of its ENTRY frame - which is the word 0x00c71e58 pushed.
  //   3. Its two exits are both `RET 0x4`, so the CALLEE pops that one word.
  //
  // Fact 3 is what makes the whole of the entry's stack behaviour decidable,
  // and it is why the argument is spelled as a real parameter here: on i386
  // `__thiscall` with a stack parameter emits `ret $4`, which makes the cleanup
  // a fact of the emitted code that the model test can MEASURE off ESP instead
  // of a claim in a comment. It is also what separates fact 3 from the entry's
  // own `POP ESI` at 0x00c71e65: two different words, taken by two different
  // mechanisms, and the entry's POP cannot reach one that a RET already took.
  //
  // The container walk this body actually performs - the `[EAX+0x14]` load at
  // 0x00ba939c, the `LEA ECX,[ESI+0x150]` at 0x00ba9385 and the
  // `ADD ESI,0x154` at 0x00ba9392 - is observed and deliberately NOT modelled.
  // So `EmpireIndex`'s extent is pointer-sized and nothing in this package may
  // be read as a recovered layout for it. What the lookup RETURNS is likewise
  // not this function's business: the real one yields either zero or a word
  // pulled out of a container, and this model yields the planted result.
  //
  // Its two INPUTS are recorded, because those are what this body actually
  // decided and what a reconstruction of the routing has to be accountable for.
  g_lookup_observation.receiver = receiver;
  g_lookup_observation.argument = political_id;
  ++g_lookup_observation.call_count;
  return g_lookup_result;
}

SlotWord PKG_00C71E30_THISCALL empire5_00c71e30(OpaqueReceiver* receiver) {
  // 0x00c71e31 8b f1  MOV ESI,ECX
  //
  // The receiver's ALIAS, and the whole reason for the prologue's PUSH ESI.
  // ESI is callee-saved on i386, so once this instruction writes it the body
  // owes its caller a restored ESI - which is what 0x00c71e30 and 0x00c71e65
  // do. Nothing about a cross-call hand-off is being arranged here; see header
  // note 3, which settles that question against the listing.
  const std::uintptr_t alias = reinterpret_cast<std::uintptr_t>(receiver);

  // 0x00c71e33 8b 8e 3c 01 00 00  MOV ECX,dword ptr [ESI + 0x13c]
  //
  // A 32-bit LOAD (opcode 0x8b, not LEA's 0x8d) of the word the receiver holds
  // at displacement 0x13c. ModRM 0x8e: mod=10 so a disp32 follows, reg=001 so
  // the destination is ECX, rm=110 so the base is ESI. Base and destination
  // DIFFERING is the mechanism: the receiver is read through the alias and the
  // LOADED WORD IS NOW IN ECX, in place of it.
  //
  // Nothing is written to the receiver, or to any object, here. The value is
  // treated as nothing more than something testable: no tag, no type word, no
  // arithmetic, and no claim that it is a pointer to any particular class.
  const std::uint32_t delegated =
      *reinterpret_cast<const std::uint32_t*>(alias + 0x13c);

  // 0x00c71e39 85 c9  TEST ECX,ECX
  // 0x00c71e3b 74 2a  JZ 0x00c71e67
  //
  // `85 c9` is TEST with reg=ECX and rm=ECX, so the flags come from the word
  // 0x00c71e33 loaded and NOT from the incoming receiver. TEST writes no
  // register and JZ writes only EFLAGS, so at 0x00c71e3d ECX still holds that
  // loaded word - which is what makes the call below a receiver hand-over.
  if (delegated == 0) {
    // 0x00c71e67 33 c0  XOR EAX,EAX
    // 0x00c71e69 5e     POP ESI
    // 0x00c71e6a c3     RET
    //
    // THE NULL ARM, and the arm BOTH guards converge on: 0x00c71e3b's operand is
    // 0x00c71e67 and 0x00c71e45's operand is ALSO 0x00c71e67, so this is one
    // arm reached two ways, not two arms. That is why this body has two returns
    // rather than three.
    //
    // `33 c0` is XOR EAX,EAX - the r/m32,r32 form with EAX both sides - so all
    // thirty-two bits of EAX are written with zero here and nothing of the
    // return is left unproven. Zero is transcribed, not interpreted: nothing in
    // the evidence names what it means, and one sampled caller null-tests the
    // result while another dereferences it, which is consistent with a null
    // pointer and with an integer 0 alike.
    return kNullArmValue;
  }

  // 0x00c71e3d e8 6e bc f1 ff  CALL 0x00b8dab0
  //
  // THE HAND-OVER, and the chain that makes it one. Nothing between 0x00c71e33
  // and here writes ECX - 0x00c71e39 and 0x00c71e3b write EFLAGS only - so
  // 0x00b8dab0 receives, as its own receiver, the word this body loaded from
  // receiver+0x13c. That target is `MOV EAX,dword ptr [ECX + 0x194]` / `RET`,
  // seven bytes read live, so the value that comes back is the 32-bit word at
  // (that object) + 0x194. The +0x194 belongs to the DELEGATED object and not to
  // this body's receiver; the two are different objects at different
  // displacements and this package names neither.
  const SlotWord delegated_scalar = helper_00b8dab0(
      reinterpret_cast<DelegatedReceiver*>(static_cast<std::uintptr_t>(delegated)));

  // 0x00c71e42 83 f8 05  CMP EAX,0x5
  // 0x00c71e45 75 20     JNZ 0x00c71e67
  //
  // `83 f8 05` is the `CMP r/m32, imm8` form, which SIGN-EXTENDS its immediate
  // to thirty-two bits - so this compares all of EAX against +5, not a byte of
  // it. The immediate is transcribed, not interpreted.
  if (delegated_scalar != 0x5) {
    return kNullArmValue;
  }

  // 0x00c71e47 8b 86 d4 00 00 00  MOV EAX,dword ptr [ESI + 0xd4]
  //
  // The INNER LEVEL of the two-level load: a 32-bit LOAD (0x8b, not 0x8d) of
  // the word the receiver holds at displacement 0xd4, into EAX. So EAX now
  // holds a POINTER, and the table this body dispatches through starts there.
  //
  // This word is the embedded object's TABLE POINTER - it is not the object. The
  // object lives AT `receiver + 0xd4`, and 0x00c71e50 below is what forms its
  // address; this instruction reads the pointer out of it. Conflating the two
  // would be the classic mistake in this shape, and the model test separates
  // them by pointer identity.
  //
  // Deliberately a dereference at the literal displacement rather than a call to
  // the header's accessor: the offset is written here so the validator can see
  // it in this span, and the model test checks the two forms against each other.
  const void* const table =
      *reinterpret_cast<const void* const*>(alias + 0xd4);

  // 0x00c71e4d 8b 50 4c  MOV EDX,dword ptr [EAX + 0x4c]
  //
  // THE OUTER LEVEL. ModRM 0x50 is mod=01, so the displacement is a single disp8
  // byte, and that byte is 0x4c; reg=010 so the destination is EDX, rm=000 so
  // the base is EAX - the table pointer just loaded. 0x4c is 76, which is
  // nineteen four-byte words, so this reads the word nineteen slots along the
  // table.
  //
  // EDX is now the callee. Written as a read of the table word rather than as a
  // register assignment, because a MOV and an assignment are the same thing
  // here and the displacement is the part worth seeing.
  const SlotFunction target = slot_target_at(table, 0x4c);

  // 0x00c71e50 8d 8e d4 00 00 00  LEA ECX,[ESI + 0xd4]
  //
  // THE LEA, and the load/address distinction this body makes decidable. The
  // opcode is 0x8d where 0x00c71e47's was 0x8b, over the SAME displacement, so
  // the two instructions ask different questions of one address: 0x00c71e47
  // dereferences it and 0x00c71e50 forms it. The dispatch's receiver is
  // therefore the ADDRESS of the embedded object - not the table pointer stored
  // there, and not this body's own receiver. The two are different pointers and
  // the model test asserts that the callee was handed the address.
  //
  // That the argument is an address and not a value is the fact most easily got
  // wrong in this shape, and it is the one a reconstruction that passed `table`
  // straight through would get wrong.
  DispatchedObject* const dispatched_argument =
      reinterpret_cast<DispatchedObject*>(alias + 0xd4);

  // 0x00c71e56 ff d2  CALL EDX
  //
  // The one indirect transfer in the body. ModRM 0xd2 is mod=11, so the target
  // is a REGISTER and there is no displacement operand here to be mistaken for
  // the slot offset - 0x4c was consumed by 0x00c71e4d and is not seen again.
  //
  // In source this is an ordinary indirect call through the slot pointer, which
  // is the closest source form of `CALL EDX`. Whether a given compiler emits
  // exactly this instruction is an emitted-code property and not a source-level
  // one, so the model test asserts the CALL and the receiver it was given -
  // which is what the bytes pin - and does not pretend to assert the encoding.
  const SlotWord delegated_political = target(dispatched_argument);

  // 0x00c71e58 50  PUSH EAX
  // 0x00c71e59 e8 42 b4 ec ff  CALL 0x00b3d2a0
  //
  // One word is pushed, and the callee pushed over takes NO argument and pops
  // NOTHING: 0x00b3d2a0 is `MOV EAX,[absolute]` / bare `RET`. So the pushed word
  // survives this call untouched, and the value that comes back is a word read
  // from an absolute address belonging to THAT function. That value goes
  // straight into ECX at 0x00c71e5e and becomes the last call's receiver.
  const SlotWord index = helper_00b3d2a0();

  // 0x00c71e5e 8b c8  MOV ECX,EAX
  //
  // ECX is OVERWRITTEN here with the previous call's result. So the receiver of
  // 0x00ba9370 is that result and NOT this body's receiver, and nothing about
  // ECX needs to survive the call at 0x00c71e59 - it is simply rewritten. A
  // reconstruction that kept handing its own receiver to the last call would be
  // describing a different body.
  EmpireIndex* const lookup_receiver =
      reinterpret_cast<EmpireIndex*>(static_cast<std::uintptr_t>(index));

  // 0x00c71e60 e8 0b 75 f3 ff  CALL 0x00ba9370
  //
  // The pushed word is THIS call's argument, not the previous call's. Three
  // independent facts say so, and they are the reason the argument is written
  // here rather than left implicit: 0x00ba9370 reads [ESP+0x8] on entry (one
  // PUSH below its own), which is the word 0x00c71e58 pushed; both of its exits
  // are `RET 0x4`, so the CALLEE pops it; and the entry's own `POP ESI` is
  // already spoken for restoring the CALLER's ESI. The argument is therefore
  // spelled as a parameter, which on i386 makes that four-byte `RET 0x4` real
  // and measurable rather than asserted - see header note 7.
  const SlotWord found = lookup_empire_00ba9370(lookup_receiver,  // NOLINT
                                                delegated_political);

  // 0x00c71e65 5e  POP ESI
  // 0x00c71e66 c3  RET
  //
  // The epilogue, and it restores the CALLER's ESI - the word saved by
  // `PUSH ESI` at 0x00c71e30. It is NOT popping the word pushed at 0x00c71e58:
  // 0x00ba9370's `RET 0x4` has already taken that, and a POP cannot reach below
  // a word a callee's RET consumed.
  //
  // EAX is untouched by either of these, so the lookup's result crosses back to
  // the caller bit for bit. That is the passing arm's return, and it is the only
  // thing that is.
  return found;
}

}