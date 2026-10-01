// PKG-SWARM-W1-005732F0 -- VA 0x005732f0 (FUN_005732f0)
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// The complete body: 19 instructions, 0x005732f0..0x0057332b inclusive
// (ghidra_function.body_start 0x005732f0, body_end 0x0057332b, size_bytes 60).
// Every line of the model below is annotated with the instruction it comes from,
// and the listing it was written against was re-derived from the image bytes for
// this package (objdump over SPORE/SporeBin/SporeApp.exe) rather than taken on
// trust; it agrees with the committed Ghidra listing instruction for instruction.
//
//   005732f0  PUSH ESI
//   005732f1  MOV ESI,ECX
//   005732f3  MOV ECX,dword ptr [ESI + 0x308]
//   005732f9  TEST ECX,ECX
//   005732fb  JZ 0x0057330e
//   005732fd  MOV dword ptr [ESI + 0x308],0x0
//   00573307  MOV EAX,dword ptr [ECX]
//   00573309  MOV EDX,dword ptr [EAX + 0x4]
//   0057330c  CALL EDX
//   0057330e  MOV ECX,dword ptr [ESI + 0x30c]
//   00573314  TEST ECX,ECX
//   00573316  JZ 0x0057332a
//   00573318  MOV dword ptr [ESI + 0x30c],0x0
//   00573322  MOV EAX,dword ptr [ECX]
//   00573324  MOV EDX,dword ptr [EAX + 0x4]
//   00573327  POP ESI
//   00573328  JMP EDX
//   0057332a  POP ESI
//   0057332b  RET
//
// FRAME. Entry ESP is untouched by every instruction except the PUSH at 0x005732f0
// and the two POPs, and the two POPs are on MUTUALLY EXCLUSIVE paths (0x00573327 is
// the tail path, 0x0057332a the return path). So the frame is one word and it
// balances to zero on all three paths, with no stack arguments and no stack
// allocation anywhere: the terminator is a bare `RET` (byte c3, no immediate), which
// agrees with abi_derived.cleanup {bytes 0, side caller} and with inference C5.
//
// That is also the one place a machine-derived record on this target is misleading,
// and it is worth naming because it looks like a defect in the body and is not:
// abi_derived.abstained_because reads "flow_not_modelled: the linear ESP walk ends at
// -4, so the listing is not one path". A linear walk pops twice (0x00573327 and
// 0x0057332a) for a single push and lands at -4. The listing is not one path -- it is
// three -- and on each of them the walk balances to exactly 0. The record's
// observation is a property of the walk, not of the frame.
//
// WHY THE PROLOGUE SPILLS THE RECEIVER. 0x005732f1 copies ECX into ESI and then
// 0x005732f3 overwrites ECX with the member at receiver+0x308. That is the whole
// reason the PUSH/POP pair exists: ECX is the receiver register of BOTH transfers
// (0x0057330c and 0x00573328 transfer to a word read out of a table, with the member
// object in ECX), so the incoming receiver has to be parked in ESI before the first
// member is loaded, and it is read back through ESI at 0x0057330e after the first
// transfer returns. The model keeps the two roles separate for the same reason: the
// body addresses the receiver through `self` and the members travel as locals.
//
// VIRTUAL DISPATCH: two sites, both proven, both the same shape. abi_derived.dispatch
// records indirect_calls 2 and call_offsets []; the 19 instructions contain no direct
// transfer at all, so this file declares no direct callee. Each site is a two-level
// load -- the object's own leading word, then the table word at displacement 0x4 --
// and each is followed by a transfer through a register:
//
//   0x0057330c  CALL EDX     after 0x00573307 / 0x00573309
//   0x00573328  JMP  EDX     after 0x00573322 / 0x00573324
//
// The second one is a TAIL transfer and the model spells it as a return of the
// transfer's value, which is the same observable thing: at 0x00573327 the frame word
// has already been popped, so the callee resumes on this body's caller's stack and
// its EAX is this body's return value. That is a modelling choice, and the one
// observable consequence of the machine taking the tail is the ESP the callee sees --
// on the machine's tail path ESP is the caller's entry ESP, while in this model the
// callee is entered with the model's frame still live. Nothing in this package's
// evidence fixes the callee's stack, so the test does not assert it; see the
// model test's "not asserted" list.
//
// GLOBALS: none. The complete 19-instruction listing names no data-segment address and
// no absolute operand outside the body. The only other data word anywhere near this
// target is the entry that points at THIS body in the table at 0x013f57f8
// (0x013f5844, the sole recorded xref, and 0x013f5844 - 0x013f57f8 = 0x4c, the
// nineteenth slot of a 29-slot table). That word is a reference to this body, not a
// reference BY it: no instruction of this body reads the table, and the table is not
// used as evidence for anything in the model -- the slot this body DISPATCHES is
// 0x4 inside a table it reads out of a member object, which is a different table at a
// different address and is only known at run time.
//
// The record also associates this VA with the table (vtables ["vtable:0x013f57f8"])
// while the xref export records zero vtable references for it, and those two are not
// independent of each other, so neither is used as an oracle here; the two-level shape
// above comes from the listing's own bytes.

#include "swarm_w1_005732f0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_005732f0 {
namespace {

// 00573309  MOV EDX,dword ptr [EAX + 0x4]
// 00573324  MOV EDX,dword ptr [EAX + 0x4]
//
// The second half of the two-level load, with the slot displacement as a parameter
// so the call site names the literal 0x4 that the listing prints. The two halves of
// the load are separate functions on purpose: the first half is `table_of` in the
// header (a bare dereference, no displacement) and the second is this, so a model
// that conflated them -- reading the object's leading word as the table AND adding
// the slot displacement to it, or skipping the first dereference -- is a two-line
// change here rather than something the shape of the code hides.
SlotFn load_slot(const Word* table, std::size_t displacement) {
  const Word* const word = *reinterpret_cast<const Word* const*>(
      reinterpret_cast<std::uintptr_t>(table) + displacement);
  return reinterpret_cast<SlotFn>(reinterpret_cast<std::uintptr_t>(word));
}

}  // namespace

// The machine's own three-instruction transfer:
//
//   ECX <- the object           (0x00573307 / 0x00573322 leave the object in ECX)
//   EDX <- the table word       (0x00573309 / 0x00573324)
//   transfer to EDX             (0x0057330c CALL EDX, 0x00573328 JMP EDX)
//
// expressed as one helper because a plain C++ call through a function pointer would
// put the ENCLOSING receiver in ECX -- the model's own `this` -- and would therefore
// transfer to the wrong object. The listing is unambiguous about which object the
// machine passes: the member word it read at 0x005732f3 / 0x0057330e and never
// touched again. The model test observes ECX at the far side of this transfer and
// compares it against exactly that object, so the register the listing fixes is
// measured rather than asserted.
//
// ONE WORD IS PUSHED, and it is a property of the model's SlotFn type, not of the
// machine. SlotFn is declared cdecl and takes the receiver as an ordinary argument,
// so a call through it has to hand that argument over on the stack; the machine
// pushes NOTHING at either transfer (0x0057330c is preceded by no PUSH, and
// 0x00573328 is preceded only by the POP that tears the frame down). The stack word
// is popped immediately after the call and is never visible to the model, and the
// test checks that the stack argument and ECX name the SAME object, which is what
// makes the adapter's extra word harmless rather than a second, competing claim.
//
// EAX is taken back into the result, which is the whole of the return value the
// machine propagates on both of its paths.
Word dispatch_slot(SlotFn slot, void* object) {
  Word result = 0;
  __asm__ __volatile__("movl %[object], %%ecx\n\t"
                       "pushl %[object]\n\t"
                       "call *%[slot]\n\t"
                       "addl $4, %%esp\n\t"
                       "movl %%eax, %[result]"
                       : [result] "=&r"(result)
                       : [object] "m"(object), [slot] "m"(slot)
                       : "eax", "ecx", "memory");
  return result;
}

extern "C" Word PKG_SWARM_W1_005732F0_THISCALL re_005732f0(Receiver* receiver) {
  // 005732f0  PUSH ESI
  // 005732f1  MOV ESI,ECX
  //
  // The receiver alias. `self` is the model of ESI: from 0x005732f3 to 0x00573324
  // every receiver access goes through it, and the machine's ESP is restored from
  // the matching POP before either return. The model keeps the alias as a local
  // pointer rather than naming members, because the machine-derived receiver record
  // is bounds_only: it enumerates the two displacements this body reaches
  // ([0x308, 0x30c], register ECX, written_through 2) and says nothing about which
  // member is which.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // EAX on the path where neither member is present is never written by this body
  // (see the header's P1/P2/P3 table). The model needs a value to return, so it
  // starts from the documented placeholder rather than from something it invented
  // per path.
  Word eax = kEaxUnwrittenOnTheNoMemberPath;

  // 005732f3  MOV ECX,dword ptr [ESI + 0x308]
  //
  // One dereference, one displacement, and the result is a POINTER: every later use
  // of it (0x00573307 MOV EAX,[ECX]) dereferences it again. It is read once and
  // never re-read, which is what the model expresses by holding it in a local: the
  // store at 0x005732fd clears the FIELD, not the local, and the transfer below
  // still receives the object. A model that re-read the field after clearing it
  // would transfer to null; the model test drives exactly that.
  DispatchTarget* const first =
      *reinterpret_cast<DispatchTarget* const*>(self + 0x308);

  // 005732f9  TEST ECX,ECX
  // 005732fb  JZ 0x0057330e
  //
  // An equality test against zero, not a validity test: any non-null word takes the
  // branch, including 1 and 0xdeadbeef. There is no range, alignment or type check
  // anywhere in the body, and the test drives both of those with disagreeing inputs.
  if (first != nullptr) {
    // 005732fd  MOV dword ptr [ESI + 0x308],0x0
    //
    // The clear happens BEFORE the transfer, not after it and not around it. The
    // ordering is observable: the callee can read the receiver and see the field
    // already zero, and the model test's observer reads it at exactly that moment.
    // This is also the body's take-and-clear idiom -- the member is consumed by the
    // transfer below and is not left behind for anyone else.
    *word_at(self, 0x308) = 0x0;

    // 00573307  MOV EAX,dword ptr [ECX]
    //
    // The FIRST dereference: the object's own leading word, with no displacement.
    // Read as a pointer to a table, and used as one immediately.
    const Word* const table = table_of(first);

    // 00573309  MOV EDX,dword ptr [EAX + 0x4]
    //
    // The SECOND dereference, at displacement 0x4. The table word at displacement 0
    // and the words at 0x8 and beyond are never read by this body; the model test
    // plants distinguishable callees in all of them so that a wrong displacement
    // cannot pass unnoticed.
    SlotFn const slot = load_slot(table, 0x4);

    // 0057330c  CALL EDX
    //
    // The first transfer, and the only one this body makes with a CALL. It RETURNS
    // to 0x0057330e, so the second half of the body runs after it and the frame word
    // is still parked on the stack. ECX is the first member (never the receiver: the
    // receiver is in ESI), and EAX takes the callee's return value, which is what
    // leaves this body on the path where the second member is null.
    eax = dispatch_slot(slot, first);
  }

  // 0057330e  MOV ECX,dword ptr [ESI + 0x30c]
  //
  // The second member, reached both by falling out of the branch above and by
  // JUMPING here at 0x005732fb when the first member was null. It is a separate
  // displacement, not the first member plus 4: the model reads it at receiver+0x30c
  // and the test plants decoys at the neighbouring offsets to keep it honest. The
  // receiver is read through the alias, which still holds it even though ECX has been
  // used twice since the prologue.
  DispatchTarget* const second =
      *reinterpret_cast<DispatchTarget* const*>(self + 0x30c);

  // 00573314  TEST ECX,ECX
  // 00573316  JZ 0x0057332a
  //
  // The same equality test against zero, guarding the second transfer.
  if (second != nullptr) {
    // 00573318  MOV dword ptr [ESI + 0x30c],0x0
    //
    // The clear again, before the transfer, and again into the FIELD rather than into
    // the local. Note that this store happens on a path where the first member may
    // never have been touched at all, and on a path where the first transfer has
    // already run: a model that cleared both members together, or cleared the first
    // one only when it was about to be used, is refuted by the byte-level receiver
    // diff the test takes.
    *word_at(self, 0x30c) = 0x0;

    // 00573322  MOV EAX,dword ptr [ECX]        the first dereference, again
    const Word* const table = table_of(second);

    // 00573324  MOV EDX,dword ptr [EAX + 0x4]  the second, at the same 0x4
    SlotFn const slot = load_slot(table, 0x4);

    // 00573327  POP ESI
    // 00573328  JMP EDX
    //
    // The TAIL transfer, and the reason the prologue's POP is on this path rather
    // than at the end: the frame is torn down FIRST and the jump goes straight out
    // of the body, so the callee returns to this body's own caller with the callee's
    // EAX as this body's return value. The model spells it as returning the
    // transfer's value, which is the same EAX the machine propagates.
    //
    // This is the only path on which the SECOND member's transfer determines the
    // return value. When it is taken, the first transfer's EAX is discarded, and
    // the model test plants different return words in the two observers so that
    // swapping them is a failure rather than an accident.
    return dispatch_slot(slot, second);
  }

  // 0057332a  POP ESI
  // 0057332b  RET
  //
  // The return path, reached by JUMPING here at 0x00573316 and by falling out of the
  // second branch. EAX is whatever the last transfer left there -- the first
  // transfer's word on the path where the second member was null, the documented
  // placeholder on the path where neither member was present. The RET is bare: no
  // immediate, so this body cleans up nothing and takes no stack argument, which is
  // compatible with caller cleanup and with zero arguments under either convention.
  return eax;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_005732f0
