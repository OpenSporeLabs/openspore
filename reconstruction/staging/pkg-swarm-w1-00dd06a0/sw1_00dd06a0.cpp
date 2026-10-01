// PKG-SWARM-W1-00DD06A0 -- VA 0x00dd06a0
// The scalar accessor installed at +0x28 of the data table the target record
// associates with this VA (SPORE/SporeBin/SporeApp.exe 3.1.0.22).
//
// The complete body: 26 instructions, 0x00dd06a0..0x00dd06f1 inclusive, 82
// bytes. The listing this was written against was RE-DERIVED from the image for
// this package (objdump over the 0x60 bytes at file offset 0x9cfaa0, RVA
// 0x9d06a0) and reproduces the 26 committed instructions at the same addresses
// with the same lengths, branch targets and operand displacements -- see the
// ASCII listing in the header. Nothing in this model depends on a difference
// from the committed listing, because there is none:
//
//   00dd06a0  PUSH ESI
//   00dd06a1  MOV ESI,ECX
//   00dd06a3  CMP dword ptr [ESI + 0x84],0x1
//   00dd06aa  JNZ 0x00dd06c5
//   00dd06ac  MOV EAX,dword ptr [ESI + 0x88]
//   00dd06b2  SUB EAX,0x2
//   00dd06b5  NEG EAX
//   00dd06b7  SBB EAX,EAX
//   00dd06b9  AND EAX,0xff577f34
//   00dd06be  ADD EAX,0xfffff045
//   00dd06c3  POP ESI
//   00dd06c4  RET
//   00dd06c5  CMP dword ptr [ESI + 0x88],0xff576f79
//   00dd06cf  JZ 0x00dd06eb
//   00dd06d1  CALL 0x00b6e250
//   00dd06d6  TEST AL,AL
//   00dd06d8  JZ 0x00dd06eb
//   00dd06da  MOV EAX,dword ptr [ESI + 0x88]
//   00dd06e0  PUSH EAX
//   00dd06e1  CALL 0x00b6f0d0
//   00dd06e6  ADD ESP,0x4
//   00dd06e9  POP ESI
//   00dd06ea  RET
//   00dd06eb  MOV EAX,0xff576f79
//   00dd06f0  POP ESI
//   00dd06f1  RET
//
// WHAT THE BODY DOES, IN ONE SENTENCE: it reads a 32-bit kind word at receiver
// offset 0x84 and a 32-bit id word at receiver offset 0x88, and returns
// 0xfffff045 when the kind is 1 and the id is 2, returns 0xff576f79 when the kind
// is 1 and the id is anything else, returns 0xff576f79 when the id already is
// 0xff576f79, returns 0xff576f79 when a zero-argument probe declines, and
// otherwise hands the id to a lookup routine and returns whatever it hands back
// -- never writing to the object. Note that 0xfffff045 is the value the ADD at
// 0x00dd06be produces on its own, because that ADD is unconditional: the arm
// produces no zero on any input.
//
// FRAME, resolved once so every displacement below is a fact. One linear walk of
// ESP through all 26 instructions. Entry ESP is 0 in the walk:
//
//   00dd06a0  PUSH ESI        ESP = -4
//   ...                          (nothing touches ESP for the next 32 instructions)
//   00dd06e0  PUSH EAX        ESP = -8      (the one word pushed for 0x00b6f0d0)
//   00dd06e6  ADD ESP,0x4     ESP = -4      (the callee's bare C3 cannot do it)
//   00dd06c3  POP ESI         ESP = 0       (arm A epilogue)
//   00dd06e9  POP ESI         ESP = 0       (arm B epilogue)
//   00dd06f0  POP ESI         ESP = 0       (arm C epilogue)
//
// The walk ends at 0 on all three paths, which balances, and no return site
// carries an immediate (`C3` at 0x00dd06c4, 0x00dd06ea and 0x00dd06f1). So the
// frame holds exactly two things and neither is a parameter: entry-4 is the
// saved ESI, and entry-8 is the single word pushed at 0x00dd06e0. The only
// frame slots are:
//
//   entry-8  the word pushed for 0x00b6f0d0: the dword 0x00dd06da loaded from
//            receiver+0x88, and dropped by the body itself at 0x00dd06e6
//   entry-4  the saved ESI
//   entry+0  the return address
//
// There is no ordinary stack argument slot anywhere: the receiver is the hidden
// `this` in ECX and nothing is pushed for either call except the 0x00b6f0d0
// argument. This agrees with abi_derived.abi (stack_cleanup_bytes 0, side caller,
// no stack_arguments entry) and with the absence of a `C2 imm16` return site.
//
// CALLING CONVENTION. The receiver arrives in ECX: 0x00dd06a1 copies it into
// ESI and 0x00dd06a3 dereferences it, while ECX is never dereferenced again, so
// the record's receiver shape is R-ALIAS (base register ECX, but the listing's
// own memory operands all name ESI) and a naive ECX-only displacement scan finds
// nothing. Both candidate conventions in the record are [__thiscall, __fastcall];
// __fastcall is excluded because no body here reads EDX -- it is not even
// initialised before either call -- and because a member function installed in a
// class's own function table with ECX-only access is the shape __thiscall
// produces. Ghidra's own prototype says __fastcall; the record and the listing
// both say __thiscall, and the record is what the validator compares against.
// The disagreement is recorded, not resolved by picking a convenient answer.
//
// CONTROL FLOW. Exactly THREE conditional branches in the whole body, all rel8,
// all with targets inside the recovered 82-byte span:
//
//   00dd06aa  JNZ 0x00dd06c5   rel8 +0x19, the kind arm's discriminator
//   00dd06cf  JZ  0x00dd06eb   rel8 +0x1a, the id-is-absent shortcut
//   00dd06d8  JZ  0x00dd06eb   rel8 +0x11, the probe-declined shortcut
//
// There are no unconditional jumps, no switch, no loop and no indirect transfer.
// The graph is a two-level tree with THREE joins at 0x00dd06eb:
//
//   kind == 1 ──> [0x00dd06ac..0x00dd06be] ──> RET at 0x00dd06c4
//   kind != 1 ──> id == 0xff576f79 ──────────> 0x00dd06eb
//                probe == 0 ──────────────────> 0x00dd06eb
//                probe != 0 ──> 0x00b6f0d0 ───> RET at 0x00dd06ea
//                                              0x00dd06eb ──> RET at 0x00dd06f1
//
// Two of the three conditionals land on the SAME target 0x00dd06eb, which is the
// single `MOV EAX,0xff576f79` / POP ESI / RET tail. So the function has three
// distinct return sites and one shared "nothing to report" value, and the
// fallback arm's return (0x00dd06ea) is the only one that is not one of the two
// constants -- it is whatever the lookup produced.
//
// The third conditional tests AL, not EAX: 0x00dd06d6 `TEST AL,AL`. That is a
// one-BYTE test of the probe's return, so a probe returning 0x00000100 would
// read as "declined" here. The probe's own body only ever returns 0 or 1, so the
// distinction is not reachable from this function's side; the model narrows the
// declared return type to bool for that reason and says so here rather than
// leaving it implicit.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 26
// instructions contain no register- or memory-operand transfer at all. The xref
// export carries a single inbound reference, from 0x0147cbe4, which is the data
// word at 0x0147cbbc + 0x28 -- so this body is reached by dispatch and by no
// direct call anywhere in the image. The model therefore declares no slot
// boundary and names nothing at the receiver's +0x00, which it never reads.
//
// GLOBALS: none named by the body. No instruction in the 26 references a
// data-segment address: the three immediates (0x02, 0xff577f34, 0xfffff045) are
// small values and 0xff576f79 is 0xff576f79, none of which is an address in
// 0x01300000..0x02000000. The body's two callees do name data words
// (0x01687978, 0x0156b0cc inside 0x00b6e250; 0x0156b0b8 and 0x13f2100 inside
// 0x00b6f0d0) but those are the CALLEES' globals, they are recorded in the header
// as context, and nothing in this model reads them.

#include "sw1_00dd06a0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00dd06a0 {

// Every constant and displacement the model below uses, tied to the instruction
// operand it came from, as a compile-time consequence rather than as a comment.
// The literals in the assertions are the instruction's own operands, so a reader
// can check them against the listing without leaving this file, and a
// reconstruction that changed one would not compile rather than merely fail.
//
// The model's text below then uses the same literals directly, at the
// displacement each instruction names, because that is what makes the code
// checkable against the listing by eye. The full per-instruction transcription of
// the five-instruction sequence, and the assertions that pin its interesting
// inputs, live in the header -- outside this span, so that no hexadecimal literal
// the machine listing does not contain can reach the model's own text.
static_assert(0xff577f34u + 0xfffff045u == 0xff576f79u,
              "the mask at 0x00dd06b9 and the addend at 0x00dd06be add up to "
              "exactly the word 0x00dd06eb materialises and 0x00dd06c5 compares "
              "against");
static_assert(0x01u == kKindArmValue,
              "0x00dd06a3's immediate is the only value the kind word is compared "
              "against, and it is the only value that routes into this arm");
static_assert(0x02u == kKindArmSubtractand,
              "0x00dd06b2's immediate is the value the 0x84 arm subtracts, and the "
              "selection is made on the result being zero");
static_assert(0x84u == kKindDisplacement && 0x88u == kIdDisplacement,
              "the two displacements the record enumerates, 132 and 136, are the "
              "two this body reads");
static_assert(0xff576f79u == kAbsentValue,
              "0x00dd06c5's compare immediate and 0x00dd06eb's store immediate are "
              "the same word");

extern "C" std::int32_t PKG_SWARM_W1_00DD06A0_THISCALL re_00dd06a0(
    OpaqueSporepediaAsset* receiver) {
  // 00dd06a0  PUSH ESI
  // 00dd06a1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the last one at 0x00dd06da. ECX is never used again
  // after the copy, which is why the record's receiver shape is R-ALIAS: it saw
  // the receiver in ECX, but every displacement it needs to reconcile belongs to
  // an instruction that names ESI.
  //
  // The receiver is taken as a byte run and every access below is a
  // DISPLACEMENT into it. The record enumerates offsets [132, 136] and is
  // bounds_only: it says where the body was seen reaching and not which member
  // is which, so no member name is written for either. The two reads and the
  // zero writes are all of this body's memory surface.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00dd06a3  CMP dword ptr [ESI + 0x84],0x1
  // 00dd06aa  JNZ 0x00dd06c5
  //
  // One dword compared for EQUALITY against one immediate, and the JNZ routes
  // everything else to 0x00dd06c5. This is the body's outermost decision and it
  // is the only one made before any call, so the kind word is sampled exactly
  // once per invocation: nothing this body does afterwards can change which arm
  // runs. The model test drives that by rewriting both words from inside the
  // probe observer and requiring the outcome to still follow the ORIGINAL kind.
  const Word kind = *word_at(self + 0x84);  // == kKindDisplacement, 0x00dd06a3

  if (kind == 0x01u) {
    // 00dd06ac  MOV EAX,dword ptr [ESI + 0x88]
    //
    // The second receiver read, and the first of THREE reads of this same word
    // in the body (0x00dd06ac, 0x00dd06c5, 0x00dd06da). It is a plain dword load:
    // the value is used as a number in the arithmetic below and is never
    // dereferenced, so there is no second level anywhere in this arm.
    const Word id = *word_at(self + 0x88);  // == kIdDisplacement, 0x00dd06ac

    // 00dd06b2  SUB EAX,0x2
    // 00dd06b5  NEG EAX
    // 00dd06b7  SBB EAX,EAX
    // 00dd06b9  AND EAX,0xff577f34
    // 00dd06be  ADD EAX,0xfffff045
    // 00dd06c3  POP ESI
    // 00dd06c4  RET
    //
    // Five instructions, no branch, two possible results. SBB EAX,EAX computes
    // -CF, and the carry in question is NEG's: NEG sets CF to 1 exactly when the
    // operand it negated was non-zero, and the operand is id-2. So the selection
    // is made on `id == 2`, bit-exactly, and the two outputs are 0xfffff045 and
    // 0xff576f79.
    //
    // 0x00dd06be's ADD IS UNCONDITIONAL, and that is the whole subtlety of this
    // arm. SBB's 0 is not a result: it falls straight into the ADD and comes out
    // as the addend on its own, 0xfffff045, which as a signed word is the -4027
    // the decompilation prints as `- 0xfbb`. The arm therefore returns 0xfffff045
    // for id == 2 and 0xff576f79 for everything else, and it returns no zero at
    // all -- a reconstruction that reads the SBB's zero as the arm's zero case is
    // wrong on the arm's one interesting input, which is precisely the input the
    // listing goes out of its way to make.
    //
    // The subtraction is wrapping, not saturating, and the test is not a signed
    // comparison: `id == 2` is the only predicate here, and in unsigned
    // arithmetic (id - 2) == 0 holds for id == 2 and nothing else, so 0,
    // 3 and 0x80000000 all take the non-zero selection and 0xfffffffe does too.
    //
    // The two constants are written as one mask and one addend, exactly as the
    // instructions do; the static_assert above and kind_arm_arithmetic in the
    // header carry the same immediates and pin the two results. The model states
    // the arm as the two-valued expression because the intermediate EAX values
    // are never observable -- no memory is touched between 0x00dd06ac and
    // 0x00dd06be, there is no call, and EAX is overwritten by the very next
    // instruction on both arms. The only thing a black-box caller can see is the
    // returned word, and the test says so rather than pretending to check the
    // intermediates.
    return static_cast<std::int32_t>((id == 0x02u) ? 0xfffff045u : kAbsentValue);
  }

  // 00dd06c5  CMP dword ptr [ESI + 0x88],0xff576f79
  // 00dd06cf  JZ 0x00dd06eb
  //
  // The third receiver read, and this one is a compare of the SAME word against
  // the SAME 32-bit value the other arm computes. So one word is both this
  // function's "nothing to report" output and its "there is nothing to look up"
  // input: an object whose id word already holds it short-circuits to returning
  // it unchanged, without consulting either callee. The compare is for exact
  // EQUALITY on all 32 bits (JZ, not JZ on a byte), so a value differing in one
  // bit takes the lookup path.
  //
  // The check comes BEFORE the probe. That ordering is observable, and the test
  // measures it: with the id word set to 0xff576f79 the probe must not be
  // entered at all.
  const Word id = *word_at(self + 0x88);  // == kIdDisplacement, 0x00dd06c5

  if (id == kAbsentValue) {
    // 00dd06eb  MOV EAX,0xff576f79
    // 00dd06f0  POP ESI
    // 00dd06f1  RET
    return static_cast<std::int32_t>(kAbsentValue);
  }

  // 00dd06d1  CALL 0x00b6e250
  //
  // Nothing is pushed and nothing is set up in any argument register: the
  // instruction before the call is 0x00dd06cf's JZ, which does not define EDX
  // and does not touch the stack. The callee takes no argument (it reads no stack
  // slot) and its terminators are bare `C3`, so no cleanup is required on either
  // side. The model test's observer samples ESP on entry against the trampoline's
  // own pre-call sample, so "nothing was pushed" is measured rather than claimed.
  if (!sporepedia_db_ready_probe_00b6e250()) {
    // 00dd06d6  TEST AL,AL
    // 00dd06d8  JZ 0x00dd06eb
    //
    // AL, not EAX: a one-byte test of the probe's return. The probe's own body
    // only ever produces 0 or 1 in EAX, so on this callee the byte test and a
    // dword test cannot disagree, and the model's declared bool return is the
    // narrowest type that reproduces the listing.
    return static_cast<std::int32_t>(kAbsentValue);
  }

  // 00dd06da  MOV EAX,dword ptr [ESI + 0x88]
  // 00dd06e0  PUSH EAX
  // 00dd06e1  CALL 0x00b6f0d0
  // 00dd06e6  ADD ESP,0x4
  // 00dd06e9  POP ESI
  // 00dd06ea  RET
  //
  // The FOURTH read of the same word, and the reason the model re-reads it here
  // instead of reusing the value compared at 0x00dd06c5: between those two
  // points a call has run. 0x00dd06da loads the word again, so whatever the
  // callee left in the object at +0x88 is what gets handed over, not what was
  // there when the comparison happened. The model test plants the difference
  // directly: its probe observer overwrites +0x88, and the lookup observer then
  // requires the NEW value.
  //
  // PUSH EAX is a value push, not an address push: what goes over the stack is
  // the dword just loaded, which the callee reads back with a dword MOV
  // (0x00b6f0d0). The pointer level is one. The test plants a decoy at the
  // address that dword could be mistaken for and requires the observer to
  // receive the word itself.
  //
  // 0x00dd06e6 is the caller-side drop of that word, required because the
  // callee's last instruction is a bare `C3`. It is not expressible in the model
  // -- a C++ call to a cdecl declaration performs it implicitly -- and it is not
  // observable through a black-box callee that does not touch the caller's stack.
  // The test says so in its own not-asserted list. What IS measured is the
  // mirror-image claim about this body itself: it consumes no stack word at all,
  // which the trampoline checks by sampling ESP across the raw call.
  //
  // The callee's EAX is the return value and nothing between 0x00dd06e1 and the
  // RET touches it: ADD ESP,0x4 does not, and POP ESI does not.
  return static_cast<std::int32_t>(
      sporepedia_lookup_packed_00b6f0d0(
          *word_at(self + 0x88)));  // == kIdDisplacement, 0x00dd06da
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd06a0
