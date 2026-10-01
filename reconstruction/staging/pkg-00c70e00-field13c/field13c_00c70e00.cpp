#include "field13c_00c70e00.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares, and note 4 of the header is where the
// question of whether the bytes discriminate __thiscall from __fastcall is
// answered (they do not; the macro follows the derived record's own name for
// the shape, and nothing below depends on the difference).
#if defined(_MSC_VER)
#define PKG_00C70E00_THISCALL __thiscall
#else
#define PKG_00C70E00_THISCALL __attribute__((thiscall))
#endif

// 0x00c70e00 FUN_00c70e00 - a receiver-field presence test whose answer is a
// 32-bit dword, with the non-null path transferred to 0x00b8dab0.
//
// Raw bytes 0x00c70e00..0x00c70e17:
//     8b 89 3c 01 00 00   MOV ECX,dword ptr [ECX + 0x13c]
//     85 c9               TEST ECX,ECX
//     74 05               JZ 0x00c70e0f
//     e9 a1 cc f1 ff      JMP 0x00b8dab0
//     b8 01 00 00 00      MOV EAX,0x1
//     c3                  RET
//     cc cc cc            INT3 pad (NOT part of the body)
//
// The shape in one sentence: read a pointer out of the receiver at +0x13c, and
// if it is non-null, become 0x00b8dab0 - which is to say, hand that pointer
// over as a receiver and let it produce the answer.
//
// ECX is this function's receiver. It is read at 0x00c70e00, before any
// definite write to it, as the base of the body's only memory operand; the
// derived record names ECX as both the receiver register and the hidden-this
// register, and four sampled call sites (header note 5) put the receiver in
// ECX with nothing pushed. That is zero ordinary stack arguments, so with the
// bare RET at 0x00c70e14 the callee pops nothing and the caller owns cleanup.
//
// The displacement is spelled literally as a value, NOT as `receiver->field`.
// The disassembly establishes the displacement (0x13c), the width (32-bit) and
// the base (ECX); it establishes nothing about which member of any type
// occupies that word, and the receiver record says so itself (`offsets: [316]`,
// `bounds_only: true`, `types: MISSING`). A member name here would be a
// field-identity assertion with nothing behind it.
//
// What is deliberately NOT done here:
//   * no name for the word at +0x13c, and no name for the receiver's class;
//   * no null check on the RECEIVER itself - the body reads through it
//     unconditionally and does not test it, so a null receiver faults exactly
//     as the machine does;
//   * no interpretation of the constant 1 - it is the immediate 0x00c70e0f
//     writes, not a "true";
//   * no claim that the two paths return the same kind of quantity;
//   * no claim about the word at +0x194, which belongs to the tail target's
//     body and not to this one;
//   * no calling convention claim beyond the shape note 4 of the header
//     states, and no variadic behaviour (the record's `variadic` is UNKNOWN).

namespace openspore::reconstruction::pkg_00c70e00_field13c {

SlotWord PKG_00C70E00_THISCALL field_194_getter_00b8dab0(
    OpaqueTailReceiver* receiver) {
  // 0x00b8dab0 8b 81 94 01 00 00  MOV EAX,dword ptr [ECX + 0x194]
  // 0x00b8dab6 c3                 RET
  //
  // The MECHANISM of the tail target, reproduced so that the receiver this
  // entry transfers is observable and can be asserted. Read live at 0x00b8dab0
  // for this package; the promoted package pkg-00b8dab0-field194-getter is the
  // record of that address and is not restated here (header note 7).
  //
  // One 32-bit load through the receiver that was handed over, one return. No
  // branch, no test, no write, no mask - so whatever word sits at +0x194 of the
  // transferred object comes back bit for bit, and a word of zero comes back as
  // a published zero.
  //
  // There is deliberately no null check here either. 0x00b8dab0's body is seven
  // bytes and contains none, so a reconstruction that added one would be
  // modelling something the listing does not have; a dropped guard in the
  // CALLER below is therefore a genuine fault, which is one of the mutants the
  // model test is built to kill.
  return tail_field_at(receiver, kTailTargetDisplacement);
}

SlotWord PKG_00C70E00_THISCALL field13c_00c70e00(OpaqueReceiver* receiver) {
  // 0x00c70e00 MOV ECX,dword ptr [ECX + 0x13c]
  //
  // The incoming receiver is ECX; the operand is a 32-bit LOAD (opcode 0x8b,
  // not LEA's 0x8d) of the word the receiver holds at displacement 0x13c. The
  // ModRM byte is 0x89 - mod=10 so a disp32 follows, reg=001 so the destination
  // is ECX, rm=001 so the base is ECX. Base and destination being the same
  // register is the whole mechanism: the incoming receiver is consumed and the
  // LOADED WORD IS NOW IN ECX, in place, with no scratch register.
  //
  // Nothing is written to the receiver, or to any object, by this statement.
  // The value is a POINTER-shaped word as far as this body is concerned, and
  // the body treats it as nothing more than a value it can test: no tag, no
  // type word, no arithmetic. This package does not claim the loaded word is
  // a pointer to any particular class.
  //
  // The LOAD is written as a dereference rather than as `field_at(...)`: the
  // header's accessor performs the same arithmetic in named form, and the
  // model test checks the two against each other. The displacement is spelled
  // literally here so the declared offset is visible in this span rather than
  // only in a constant elsewhere.
  const std::uint32_t loaded =
      *reinterpret_cast<const std::uint32_t*>(
          reinterpret_cast<std::uintptr_t>(receiver) + 0x13c);

  // 0x00c70e06 TEST ECX,ECX
  // 0x00c70e08 JZ 0x00c70e0f
  //
  // `85 c9` is TEST with reg=ECX and rm=ECX, so the flags come from the word
  // 0x00c70e00 loaded - not from the incoming receiver. TEST writes no
  // register; `74 05` is JZ with rel8 = 5, and 5 is exactly the length of the
  // instruction it skips, so the false arm lands on 0x00c70e0f and the TRUE
  // arm is the whole tail transfer at 0x00c70e0a.
  if (loaded == 0) {
    // 0x00c70e0f MOV EAX,0x1
    // 0x00c70e14 RET
    //
    // The null arm. `b8 01 00 00 00` is MOV EAX,imm32 - a full 32-bit
    // immediate write, not the 8-bit form - so all thirty-two bits of EAX are
    // written here and nothing of the return is left unproven. The value 1 is
    // transcribed, not interpreted: nothing in the evidence names what it
    // means, and the sampled callers only ever order the result against 0x4 or
    // 0x5, which is consistent with this being 1, with 1 being a sentinel, and
    // with 1 being an enum member.
    return kNullArmReturn;
  }

  // 0x00c70e0a JMP 0x00b8dab0
  //
  // THE TAIL TRANSFER, and the chain of ECX that makes it one. ECX is not
  // rewritten anywhere between 0x00c70e00 and here: 0x00c70e06 writes EFLAGS
  // and 0x00c70e08 writes EFLAGS, nothing else is between them, and there is
  // no frame teardown to perform because no frame was ever built. So at the
  // moment of the jump ECX still holds the word 0x00c70e00 loaded, and
  // 0x00b8dab0 - which is `MOV EAX,dword ptr [ECX + 0x194]` / `RET` - receives
  // THAT word as its own receiver. That is why the transfer is a tail call and
  // not a nested call: the callee's result lands in the same register the
  // caller would have used, and 0x00c70e0f/0x00c70e14 are simply never reached
  // on this path.
  //
  // In source this is written as the tail-shaped `return`, which is the closest
  // source form of a `JMP`. Whether a given compiler emits a jump or a call
  // plus a return for it is an emitted-code property and not a source-level
  // one; the model test asserts the CALL and the receiver it was given, which
  // is what the bytes pin, and does not pretend to assert the jump.
  return field_194_getter_00b8dab0(
      reinterpret_cast<OpaqueTailReceiver*>(static_cast<std::uintptr_t>(loaded)));
}

}

#undef PKG_00C70E00_THISCALL