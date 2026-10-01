// PKG-SWARM-W1-005BA0D0 -- VA 0x005ba0d0
// FUN_005ba0d0 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 12 instructions, 0x005ba0d0..0x005ba0ef inclusive
// (ghidra_function.body_start 0x005ba0d0, body_end 0x005ba0ef, span_bytes 32).
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust, with
// `objdump -d -M intel SPORE/SporeBin/SporeApp.exe` over 0x005ba0d0..0x005ba0f0.
// It reproduces the committed 12 instructions at the same addresses with the same
// operand displacements, and the committed parse record is not degraded, so
// nothing in the model depends on the difference:
//
//   005ba0d0  8b 41 18              mov eax,DWORD PTR [ecx+0x18]
//   005ba0d3  83 c1 14              add ecx,0x14
//   005ba0d6  83 c0 ff              add eax,0xffffffff
//   005ba0d9  89 41 04              mov DWORD PTR [ecx+4],eax
//   005ba0dc  75 11                 jne 0x5ba0ef
//   005ba0de  c7 41 04 01 00 00 00  mov DWORD PTR [ecx+4],0x1
//   005ba0e5  8b 01                 mov eax,DWORD PTR [ecx]
//   005ba0e7  8b 10                 mov edx,DWORD PTR [eax]
//   005ba0e9  6a 01                 push 0x1
//   005ba0eb  ff d2                 call edx
//   005ba0ed  33 c0                 xor eax,eax
//   005ba0ef  c3                    ret
//
// THE WHOLE BODY IN ONE SENTENCE, in the order the instructions execute: read the
// receiver's word at +0x18, subtract one from it, store that back at +0x18, and
// if the result is non-zero return it; if the result is zero, put 1 back at +0x18,
// take the vtable word at +0x14, call its slot 0 with +0x14 as the receiver and
// 1 as the one stack word, and return 0.
//
// FRAME, resolved against the entry ESP so every stack claim below is a fact.
// Entry ESP is 0 in the walk. The body pushes one word at 0x005ba0e9 and pops
// nothing, and its terminator is `c3` with no immediate, so the walk only closes
// if the callee at 0x005ba0eb owns the four bytes it was handed. Two
// independent observations agree: the twelve instructions contain no POP and no
// ADD ESP, and a callee-cleaned __thiscall/__stdcall frame ends the walk at
// entry+0. So:
//
//   entry-4    the argument pushed by `6a 01` at 0x005ba0e9, consumed by the
//              callee, not by this body
//   (no other) the body reads no stack slot, so it takes NO ordinary argument
//
// VIRTUAL DISPATCH: exactly one, and it is an OUTGOING call, not an incoming one.
// `ff d2` at 0x005ba0eb calls a register. The register is built by two loads:
// 0x005ba0e5 reads the word at receiver+0x14 into EAX and 0x005ba0e7 reads the
// dword at [EAX] into EDX. So the target is TWO dereferences deep -- the word at
// +0x14 is a vtable POINTER, and the callee is slot 0 of the table it points at
// (offset 0x00, the displacement of the `8b 10` itself). ECX is not rewritten
// after 0x005ba0d3, so the receiver the callee receives is receiver+0x14 -- the
// address of the subobject, NOT the subobject's pointee and NOT the receiver's
// base. That distinction is the single highest-risk item in this body and case N
// in the model test is aimed at it.
//
// INCOMING DISPATCH, recorded and deliberately NOT modelled as a member. This
// body is listed at fifteen data addresses that Ghidra's vftable analysis
// associates with fifteen tables, and its three non-data references are not call
// sites but receiver-adjustor thunks:
//
//   0x0057a5e0  sub ecx,0x10  /  0x0057a5e3  jmp 0x005ba0d0
//   0x0057a600  sub ecx,0x04  /  0x0057a603  jmp 0x005ba0d0
//   0x005ac9b0  sub ecx,0x14  /  0x005ac9b3  jmp 0x005ba0d0
//
// Each is six bytes and int3-padded to the next sixteen-byte boundary, which is
// the MSVC receiver-adjustor thunk shape, and each rewrites ECX before the tail
// jump. The conclusion the bytes carry is narrow and is the only one claimed:
// `this` for this body is a subobject pointer, and the function is reached
// through vftables of at least three classes whose second base sits at +0x10,
// +0x04 and +0x14 in the complete object respectively. The class names, the
// vftable slot NAMES and the class of the object at receiver+0x14 are NOT
// established: SporeApp.exe carries no MSVC RTTI, and this body never reads the
// word at the receiver's +0x00, so no dispatch word is named there.
//
// The constructor at 0x005ac980 corroborates the two offsets this body touches
// and nothing else: it calls 0x005b0f80 on the fresh object, writes 0x013ec458
// to +0x14, zeroes +0x18, writes 0x013f718c to +0x00 and then 0x013f76c4 to
// +0x14 (`mov DWORD PTR [esi+0x14],0x13f76c4` at 0x005ac99c). The adjacent
// thunk at 0x005ac9b0 is the `sub ecx,0x14` one, so the class that constructor
// builds has a second base at +0x14 -- which is the same offset this body uses
// as its subobject. That is consistency, not proof of a class identity, and it is
// not used as a member name.
//
// GLOBALS: none. abi_derived.globals is empty and the twelve instructions contain
// no absolute operand outside the body, so nothing is declared.

#include "sw1_005ba0d0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0 {
namespace {

// Model instrumentation, not a machine global: the ordered pair of 4-byte
// stores the body makes to receiver+0x18. It has to live at namespace scope
// rather than as a local because the first of the two stores is never read by
// the body, and a local that is written and never read is a warning under -Wall.
// See the header for why it is modelled at all.
Word g_write_count = 0;
Word g_write_first = 0;
Word g_write_second = 0;

}  // namespace

ReceiverWriteLog receiver_write_log() {
  ReceiverWriteLog log;
  log.count = g_write_count;
  log.first = g_write_first;
  log.second = g_write_second;
  return log;
}

extern "C" Word PKG_SWARM_W1_005BA0D0_THISCALL re_005ba0d0(
    Swarm005ba0d0Receiver* receiver) {
  // The receiver is taken as a byte run and every access below is a
  // DISPLACEMENT into it. The machine-derived receiver record enumerates
  // offsets [0x18] with register ECX and shape bounds_only -- it says where the
  // body was seen reaching and not which member is which -- and it does not
  // enumerate 0x14 at all, which the listing does reach. No member name is
  // written for any displacement: the two words below are named for where they
  // sit, and the type of each says only what the machine does to it.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 005ba0d0  mov eax,DWORD PTR [ecx+0x18]
  //
  // The first thing the body does, before it touches ECX: one 32-bit read at
  // the receiver's +0x18. Not a byte, not a halfword, not a read through a
  // pointer -- `8b 41 18` is a dword load at displacement 0x18 off the receiver
  // register, and the next instruction writes a dword to +0x18 through the same
  // register, so the width of the two agrees.
  const Word previous = *word_at(self, kReceiverCounterDisplacement);

  // 005ba0d3  add ecx,0x14
  //
  // ECX becomes receiver+0x14 and is never moved again. Every later access in
  // the body is through this register, so the two remaining stores at
  // [ECX+4] land at the receiver's +0x18 -- the same word just read -- and the
  // load at [ECX] lands at the receiver's +0x14. The subobject's base address is
  // formed here, once, and reused for the load and for the callee's receiver.
  std::uint8_t* const subobject = self + kSubobjectShift;

  // 005ba0d6  add eax,0xffffffff
  //
  // `83 c0 ff` is a sign-extended one-byte add of 0xff, i.e. 0xffffffff, on a
  // 32-bit register. The arithmetic WRAPS: 0 becomes 0xffffffff and 0xffffffff
  // becomes 0xfffffffe. There is no CMP and no JCC between this and the store,
  // so the value stored and the value tested are the same value.
  const Word decremented = previous + kDecrementImmediate;

  // 005ba0d9  mov DWORD PTR [ecx+4],eax
  //
  // Unconditional. The decremented word goes back to the receiver's +0x18
  // whatever the branch below decides, so on the early-out path the field's
  // post-state is the value that is also returned, and on the dispatch path this
  // store is a transient 0 that the restore immediately overwrites.
  *word_at(self, kReceiverCounterDisplacement) = decremented;
  g_write_count = 1;
  g_write_first = decremented;

  // 005ba0dc  jne 0x005ba0ef
  //
  // `75 11` is JNZ rel8: taken when ZF is clear, i.e. when EAX is non-zero. The
  // flags come from the ADD at 0x005ba0d6 -- the MOV at 0x005ba0d9 sets none --
  // so the test is exactly "the decremented value is not 0". The taken branch
  // goes straight to the RET, so the early-out path performs no load, no call
  // and no second store, and EAX is still the decremented value at the RET.
  //
  // Equivalently, and this is the form the model's `if` takes: the body falls
  // through exactly when the PRE-decrement value was 1. The 0 -> 0xffffffff wrap
  // is not zero either, so a receiver sitting at 0 takes this branch as well.
  if (decremented != 0u) {
    return decremented;
  }

  // 005ba0de  mov DWORD PTR [ecx+4],0x1
  //
  // The restore, and it is the literal 1 of `c7 41 04 01 00 00 00` -- not the
  // saved pre-decrement value, and not a zero. It is the SECOND of the two
  // stores to the same address and it is what the field holds when the body
  // returns, which is why the value the dispatch path returns (0) and the value
  // the field holds (1) are different numbers.
  *word_at(self, kReceiverCounterDisplacement) = kRestoreValue;
  g_write_count = 2;
  g_write_second = kRestoreValue;

  // 005ba0e5  mov eax,DWORD PTR [ecx]
  //
  // ECX is still receiver+0x14, so this reads the word at +0x14. It is loaded
  // into EAX and NOT called, NOT treated as a function pointer, and NOT
  // immediately dereferenced through the receiver: the next instruction reads
  // THROUGH it. That is the level discipline this body turns on. The word is a
  // vtable pointer (see the header), and the constructor at 0x005ac99c is what
  // puts a table address there.
  void** const vtable = *reinterpret_cast<void***>(subobject);

  // 005ba0e7  mov edx,DWORD PTR [eax]
  //
  // The second load, through the pointer just read. Displacement 0x00 -- the
  // `8b 10` is `mov edx,[eax]`, no offset -- so this is slot 0 of the table and
  // slot 0 is the only slot this body can name. The result goes into EDX, not
  // EAX, and the CALL is `ff d2`, i.e. through EDX.
  //
  // A one-level reconstruction -- calling [receiver+0x14] directly, or reading a
  // neighbour displacement -- survives exactly the two instructions that make
  // this pair two loads deep. Case N of the model test plants decoys that make
  // each of those wrong readings produce a different, observable call.
  DispatchSlot0 const slot =
      reinterpret_cast<DispatchSlot0>(vtable[kDispatchSlot]);

  // 005ba0e9  push 0x1
  //
  // One stack word, the literal 1 of the sign-extended one-byte immediate `6a
  // 01`. The body pushes nothing else and reads no argument slot, so the callee
  // takes exactly one stack word. The push happens AFTER both loads, so the
  // loads cannot be affected by it; the body is also not re-entered here, so
  // there is no window in which an outside observer could see the loads
  // interleaved with the store.
  //
  // 005ba0eb  call edx
  //
  // The indirect call. The receiver is ECX, and ECX is receiver+0x14 -- the
  // address of the subobject, which is also the address the two loads above
  // started from. It is NOT receiver+0x00 and NOT the table pointer: passing
  // either of those is a different machine, and the model test measures the
  // callee's own `this` to keep them apart. The return value lands in EAX and
  // is thrown away by the next instruction.
  //
  // The body performs no stack cleanup after the call, so the callee owns the
  // four bytes: that is the whole basis for the callee-cleaned half of the
  // calling convention declared in the header.
  slot(reinterpret_cast<DispatchSubobject*>(subobject), kDispatchArgument);

  // 005ba0ed  xor eax,eax
  //
  // EAX is zeroed AFTER the call returns, which is the only reason the returned
  // word on this path is 0 rather than whatever the callee left. It is a
  // deliberate second statement, not an artefact: the field holds 1 here and the
  // function returns 0.
  //
  // 005ba0ef  ret
  //
  // The terminator, `c3`, shared with the early-out branch. The frame is already
  // balanced because the callee popped the pushed word, so this RET consumes
  // nothing but the return address.
  return 0u;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_005ba0d0
