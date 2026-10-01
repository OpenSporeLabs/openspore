// PKG-SWARM-W2-00F99980 -- VA 0x00f99980
// FUN_00f99980 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000)
//
// The complete body: 25 instructions, 0x00f99980..0x00f999d7 inclusive
// (ghidra_function.body_start 0x00f99980, body_end 0x00f999d7, size_bytes 88). The
// listing below is re-derived from the image bytes rather than taken from the
// committed Ghidra record: `objdump -D -b binary -m i386 -M intel
// --adjust-vma=0xf99980` over the 0x58 bytes at file offset 0xb98d80 (RVA
// 0xb99980, .text VMA 0x00401000 at file offset 0x400) reproduces the committed 25
// instructions at the same addresses, with the same mnemonics, operands, call
// targets and branch targets. The two instruction boundaries worth naming because
// they are the ones the frame depends on are confirmed from the same bytes:
//
//   00f99983  83 BE A4 08 00 00 FF FF     CMP dword ptr [ESI+0x8a4],0xffffffff   (7)
//   00f999a7  C7 86 A4 08 00 00 FF FF FF FF
//                                        MOV dword ptr [ESI+0x8a4],0xffffffff   (10)
//   00f999c6  C7 86 94 08 00 00 00 00 00 00
//                                        MOV dword ptr [ESI+0x894],0x0        (10)
//   00f999d7  C3                        RET                                     (1)
//
//   00f99980  PUSH ESI
//   00f99981  MOV ESI,ECX                       receiver alias
//   00f99983  CMP dword ptr [ESI + 0x8a4],-0x1
//   00f9998a  JZ 0x00f999a1
//   00f9998c  CALL 0x0067dd50                   EAX = the manager
//   00f99991  MOV ECX,dword ptr [ESI + 0x8a4]   the one stack argument
//   00f99997  MOV EDX,dword ptr [EAX]           the manager's leading word
//   00f99999  MOV EDX,dword ptr [EDX + 0x7c]    the table word 124 bytes in
//   00f9999c  PUSH ECX
//   00f9999d  MOV ECX,EAX                       the manager becomes the receiver
//   00f9999f  CALL EDX                          indirect, callee pops the one word
//   00f999a1  MOV ECX,dword ptr [ESI + 0x894]
//   00f999a7  MOV dword ptr [ESI + 0x8a4],0xffffffff
//   00f999b1  TEST ECX,ECX
//   00f999b3  JZ 0x00f999d6
//   00f999b5  PUSH 0x1
//   00f999b7  CALL 0x00692400
//   00f999bc  MOV ECX,dword ptr [ESI + 0x894]   re-read, after the call
//   00f999c2  TEST ECX,ECX
//   00f999c4  JZ 0x00f999d6
//   00f999c6  MOV dword ptr [ESI + 0x894],0x0
//   00f999d0  POP ESI
//   00f999d1  JMP 0x00690120                    tail call, ECX still the re-read word
//   00f999d6  POP ESI
//   00f999d7  RET
//
// WHAT THE BODY DOES, in the order the instructions do it: if the receiver's word at
// +0x8a4 is not the 0xffffffff sentinel, ask the manager for its table, read the
// word 0x7c into that table and call it with the manager as the receiver and the
// +0x8a4 word as the single argument; then store 0xffffffff into +0x8a4
// unconditionally, whether or not the call ran; then, if the word at +0x894 is
// non-null, call through it with the argument 1, re-read +0x894, and if it is STILL
// non-null, store 0 into it and transfer control to 0x00690120 with that re-read
// word still in ECX. Nothing else is read, nothing else is written, and the only
// two words of memory this body ever changes are those two receiver words.
//
// FRAME, resolved once against the entry ESP so every statement below is a fact.
// Entry ESP is 0 in the walk. 0x00f99980 pushes ESI (entry-4). Each call's own
// terminator settles the stack after it: the indirect callee pops the word pushed
// at 0x00f9999c, 0x00692400 ends `C2 04 00` and pops the word pushed at 0x00f999b5,
// and 0x0067dd50 pushes nothing. So the walk returns to entry-4 after every call, and
// 0x00f999d0 / 0x00f999d6 each POP it back to entry before the RET or the tail
// transfer. The frame therefore balances with NO ordinary stack argument and a bare
// RET, and that is the whole of the argument surface. The proof that the indirect
// callee pops its word is structural rather than assumed: the body reaches 0x00f999d0
// with ONE POP ESI, and if the callee had left the word there the POP would restore
// the argument instead of ESI and the RET at 0x00f999d7 would branch to it.
//
//   entry+4   the return address, consumed by RET / by the tail transfer
//   entry-4   the saved ESI, pushed at 0x00f99980 and popped at 0x00f999d0 or 0x00f999d6
//
// ORDERING, which is most of what is left to get right and all of it is machine:
//
//   * The dispatch happens BEFORE +0x8a4 is cleared (0x00f9999f before
//     0x00f999a7), so the slot call still sees the old value in memory. The model
//     test's slot observer reads the receiver while it runs.
//   * The argument to the slot call was already in ECX at 0x00f99991, before the
//     manager existed, so the argument is the field's value as it stood at ENTRY
//     even if something between could have changed it.
//   * +0x8a4 is cleared UNCONDITIONALLY (0x00f999a7 sits after the JZ merge point
//     0x00f999a1), including on the path where the sentinel was already there, and
//     including on the path where the first +0x894 guard fails.
//   * The +0x894 word is read THREE times: at 0x00f999a1 before the guard, at
//     0x00f999bc after the call, and it is the second read that the second guard
//     tests and that the tail transfer receives. The re-read is real: the call at
//     0x00f999b7 can write the receiver, and the model test makes its observer do
//     exactly that, both clearing the field (which must suppress the store and the
//     tail transfer) and replacing it with a different word (which must become the
//     one handed to 0x00690120).
//   * The store of 0 at 0x00f999c6 happens BEFORE the tail transfer, and does not
//     disturb ECX, so the object released is the one that was read at 0x00f999bc
//     and not the 0 that was just stored. A reconstruction that re-read the field
//     after clearing it would hand 0x00690120 a null receiver, which its own first
//     instruction (TEST ECX,ECX) would take as the null arm.
//
// VIRTUAL DISPATCH: one site, 0x00f9999f, and it is the two-level load the machine
// shows. 0x00f99997 reads the manager's leading word and 0x00f99999 reads the word
// 0x7c into the table that word points at, which is then called. The package's
// dispatch record agrees independently at abi_derived.dispatch.indirect_calls 1, and
// the machine's own classifier reads this site as VTABLE_SLOT with slot_offset 124.
// The model therefore names the slot displacement 0x7c and the typing that puts the
// receiver in ECX, and nothing else: no slot INDEX is claimed, no slot NAME beyond
// the receiver's own record, and no member of the receiver is named at +0x00.
//
// GLOBALS: none, and the claim is a positive one. No instruction in the 25 names a
// data-segment address. The .data word 0x015fd8c0 belongs to 0x0067dd50's own body
// (its first instruction reads it) and is not modelled here; the model reaches the
// manager only through the return value of that call, which is what the machine
// does.
//
// RETURN WORD. No instruction in the body has EAX as a destination, and each of the
// three calls leaves a value there that nothing reads again. So the composition of
// EAX at 0x00f999d7 is:
//
//   sentinel set, +0x894 null    EAX = whatever the caller passed in
//   dispatch, +0x894 null        EAX = the slot's own return word
//   sentinel set, +0x894 set     EAX = 0x00692400's return word
//   dispatch, +0x894 cleared     EAX = 0x00692400's return word
//   the tail path                the return register is 0x00690120's to write: its
//                                own bytes leave EAX = ESI, i.e. 0 on the arm that
//                                decrements the count to zero, and the other arm's
//                                value is in 0x00690120's bytes, not in this body
//
// Four different words, none of them produced here, and the declared type is void.
// The record disagrees and the disagreement is in the sidecar: the canonical claim
// is the machine phrase "unclassified_in_EAX", which no C++ spelling can equal.

#include "sw2_00f99980_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00f99980 {

extern "C" void PKG_SW2_00F99980_THISCALL re_00f99980(Receiver* receiver) {
  // 00f99980  PUSH ESI
  // 00f99981  MOV ESI,ECX
  //
  // ESI is the receiver alias and every receiver access below goes through it. ECX
  // is then reused three times as an argument or a test register (0x00f99991,
  // 0x00f9999d, 0x00f999a1, 0x00f999bc), which is why the machine-derived receiver
  // record names register ECX with shape R-ALIAS: no receiver access in this body is
  // made through ECX itself.
  //
  // The receiver is taken as a byte run and reached by DISPLACEMENT. The record
  // enumerates offsets [0x894, 0x8a4] and is bounds_only, so it says where the body
  // was seen reaching and not which member is which, and no member is named for
  // either of them.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00f99983  CMP dword ptr [ESI + 0x8a4],-0x1
  // 00f9998a  JZ 0x00f999a1
  //
  // An exact 32-bit equality against 0xffffffff, and nothing else. The three
  // instructions that could plausibly be written here instead are all refuted by
  // this body's own bytes: an unsigned `< 0` would also treat 0xfffffffe as absent,
  // a signed `< 0` would treat every word with the top bit set as absent, and a
  // `-2` sentinel would make 0xfffffffe absent. The model test drives 0x00000000,
  // 0x7fffffff, 0xfffffffe and 0x80000000 through this test and requires the
  // dispatch to run for all four.
  const Word target_word = *word_at(self, kLightingTargetDisplacement);
  const bool target_present = (target_word != kLightingTargetAbsent);

  if (target_present) {
    // 00f9998c  CALL 0x0067dd50
    //
    // The manager. cdecl, no arguments, and its return value is the only thing this
    // body ever does with it besides the two instructions below.
    LightingManager* const manager = graphics_ilightingmanager_get_0067dd50();

    // 00f99991  MOV ECX,dword ptr [ESI + 0x8a4]
    //
    // The single stack argument, loaded from the receiver's +0x8a4 and passed BY
    // VALUE. Nothing in this body dereferences it: the field's word becomes ECX, is
    // pushed, and the field is then overwritten with 0xffffffff four instructions
    // later while ECX still holds the old pointer. The model test plants a poison
    // pattern inside an object at that address and asserts that no byte of it moves.
    //
    // 00f99997  MOV EDX,dword ptr [EAX]
    // 00f99999  MOV EDX,dword ptr [EDX + 0x7c]
    //
    // The two-level table load. First the manager's leading word -- displacement
    // zero, of a DIFFERENT object from the receiver, which is why it is reached
    // through the manager and not through self -- and then the word 0x7c into the
    // table that word points at. 0x7c is a byte displacement: 124 is 31 whole
    // dwords, and load_slot reads it as one.
    const Word* const table =
        *reinterpret_cast<Word* const*>(manager + kObjectTableWordDisplacement);

    // 00f9999c  PUSH ECX
    // 00f9999d  MOV ECX,EAX
    // 00f9999f  CALL EDX
    //
    // The argument on the stack, the manager in ECX, and the transfer through the
    // table word. The callee owns the one argument word, which is what the frame
    // requires (see the frame note at the top of this file), so the slot is typed
    // as a thiscall function pointer -- the one typing that emits these three
    // instructions in this order. The call's own return value is never read: the
    // next instruction after it writes memory, not a register.
    //
    // 0x7c is written as the literal the operand of 0x00f99999 carries rather than
    // through the header's kLightingSlotDisplacement, so the dispatch site states the
    // machine's own displacement in place. The two are the same value and the model
    // test asserts it (V3), and the header's constant carries the arithmetic that
    // says what it is: 124 bytes is 31 whole dwords of a dword-indexed table.
    reinterpret_cast<LightingMethod>(load_slot(table, 0x7c))(
        manager, reinterpret_cast<LightingTarget*>(target_word));
  }

  // 00f999a1  MOV ECX,dword ptr [ESI + 0x894]
  //
  // The second receiver word, read once here and re-read at 0x00f999bc. It is a
  // POINTER: 0x00f999b1 tests it against 0 and 0x00f999b7 hands it to 0x00692400 as
  // that callee's ECX receiver, whose own first instruction is TEST ECX,ECX. The
  // model keeps it as a pointer for that reason; a reconstruction that read the
  // word AT the address it points at would be reading a different object, and the
  // model test plants distinct decoys at the object and at its own neighbourhood.
  RefCountedObject* const owned =
      *reinterpret_cast<RefCountedObject* const*>(self + kRefCountedDisplacement);

  // 00f999a7  MOV dword ptr [ESI + 0x8a4],0xffffffff
  //
  // Unconditional, and after the merge point 0x00f999a1: the field is set to the
  // sentinel whether or not the dispatch ran, and whether or not anything below
  // does. It is the only write this body makes to +0x8a4.
  *word_at(self, kLightingTargetDisplacement) = kLightingTargetAbsent;

  // 00f999b1  TEST ECX,ECX
  // 00f999b3  JZ 0x00f999d6
  //
  // A null test on the word read at 0x00f999a1. The callee defends against the same
  // thing in its own first two instructions, so this guard is not redundant -- it
  // decides whether the call happens at all.
  if (owned != nullptr) {
    // 00f999b5  PUSH 0x1
    // 00f999b7  CALL 0x00692400
    //
    // The word this body read as the callee's ECX receiver, and the literal 1 as
    // its one ordinary argument. The callee reads that word as its own first stack
    // word (0x00692404 `MOV EDX,[ESP+0x4]`), adjusts its receiver by -8
    // (0x00692408), and pops the argument itself (0x00692417 `RET 0x4`) -- which is
    // what keeps the frame balanced to a single POP ESI afterwards. Its return value
    // is discarded: nothing between 0x00f999b7 and 0x00f999d7 reads EAX.
    owned_object_notify_00692400(owned, kReleaseNotificationArgument);

    // 00f999bc  MOV ECX,dword ptr [ESI + 0x894]
    // 00f999c2  TEST ECX,ECX
    // 00f999c4  JZ 0x00f999d6
    //
    // A SECOND read of the same field, after the call, and it is this one that the
    // second guard tests. The re-read is not a stylistic detail of the compiler: the
    // call above can write the receiver, and the model's own observer is given the
    // power to do so. A reconstruction that reused the value read at 0x00f999a1
    // would clear the field and release the object even after the callee had
    // already cleared it, and a reconstruction that never re-read would hand
    // 0x00690120 the STALE object after the callee had replaced it.
    RefCountedObject* const owned_after =
        *reinterpret_cast<RefCountedObject* const*>(self + kRefCountedDisplacement);
    if (owned_after != nullptr) {
      // 00f999c6  MOV dword ptr [ESI + 0x894],0x0
      //
      // The field is cleared BEFORE the transfer below, and the clear does not
      // touch ECX, so what the callee at 0x00690120 receives as its receiver is
      // the word read at 0x00f999bc and not the zero just stored. The model reads
      // the field again after the transfer to assert that the zero is what stayed.
      *word_at(self, kRefCountedDisplacement) = 0;

      // 00f999d0  POP ESI
      // 00f999d1  JMP 0x00690120
      //
      // The epilogue, then the transfer. POP ESI lands ESP back on the entry value,
      // so the jump is a tail call: 0x00690120 sees exactly the stack this body's
      // caller left, returns to that caller itself, and leaves nothing of this
      // frame behind. Its return word becomes this body's return word, which is the
      // reason the declared return type is void while EAX is still not this body's
      // to set. A `return` of that call is written as such below because it is the
      // same transfer, not because C++ can be asked to emit a jump.
      return owned_object_release_00690120(owned_after);
    }
  }

  // 00f999d6  POP ESI
  // 00f999d7  RET
  //
  // The plain exit, reached from the first guard (0x00f999b3) and from the second
  // (0x00f999c4). It restores ESI and returns past the return address alone; EAX is
  // dead here and holds one of the four words listed in the RETURN WORD note above,
  // none of which this body produced.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f99980
