// PKG-DFW-0067E6B0 -- VA 0x0067e6b0
// App::cCheatManager::func3Ch (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 11 instructions, body 0x0067e6b0..0x0067e6cc inclusive.
// Verified against the live bridge and against the 29 body bytes it reports:
//
//   568bf1 e8f8fbffff f644240801 7409 56 e8bb8c8c00 83c404 8bc6 5e c20400
//
// (then cc cc padding at 0x0067e6cd..0x0067e6ce, so Ghidra's body_end
// 0x0067e6cd is the first padding byte, not an instruction).
//
//   0x0067e6b0  PUSH ESI                       the only callee-save; no EBP frame
//   0x0067e6b1  MOV ESI,ECX                    the receiver is copied once, into ESI
//   0x0067e6b3  CALL 0x0067e2b0                unconditional, nothing pushed
//   0x0067e6b8  TEST byte ptr [ESP + 0x8],0x1 bit 0 of the low byte of entry_ESP+0x4
//   0x0067e6bd  JZ 0x0067e6c8                  clear -> the shared tail
//   0x0067e6bf  PUSH ESI                       the argument of the second callee
//   0x0067e6c0  CALL 0x00f47380
//   0x0067e6c5  ADD ESP,0x4                    caller-cleaned, one word
//   0x0067e6c8  MOV EAX,ESI                    the receiver, on both paths
//   0x0067e6ca  POP ESI
//   0x0067e6cb  RET 0x4                        the callee pops the argument word
//
// The stack arithmetic, which is the one thing in this body that is easy to get
// wrong and which decides where the gate word lives. At entry, [ESP] is the
// return address and [ESP + 0x4] is the argument. PUSH ESI at 0x0067e6b0 moves
// everything up by 4 and leaves the saved register at [ESP + 0x0], so the
// argument is now at [ESP + 0x4]. The call at 0x0067e6b3 pushes and pops its
// own return address around the callee and 0x0067e2b0 is stack-neutral across
// its own call (five pushes at 0x0067e2b0..0x0067e2c6, then POP ESI at
// 0x0067e2f6 and ADD ESP,0x10 at 0x0067e2fe against a bare RET at 0x0067e301),
// so when control returns here the only outstanding frame change is that first
// PUSH. That is why the TEST at 0x0067e6b8 addresses [ESP + 0x8] and reaches
// entry_ESP + 0x4: it is the body's own first ordinary argument, and it is read
// AFTER the first callee has run, not before.
//
// The gate is a byte test with an immediate of 0x1, so only bit 0 of the word
// has any meaning here; the remaining 31 bits are read by the load and ignored.
// The model's parameter is the whole 4-byte word because the record fixes the
// slot width at 4, not because the body uses more than one bit of it.
//
// Return. 0x0067e6c8 MOV EAX,ESI is on the single exit path, so EAX holds the
// receiver on both the taken and the untaken branch. That contradicts the
// persisted SDK/Ghidra prototype, which declares
// "void App::cCheatManager::func3Ch(cCheatManager * this, int param_2)". The
// listing wins here and the declared return type is the persisted ABI record's
// own phrase for what the machine does, "pointer to the receiver". Whether any
// consumer reads that word is NOT established: the only inbound reference to
// this address is the data word of vtable 0x014018b0 at slot 20 (0x01401900),
// and no call site of that slot is known.
//
// The other decompiler disagreement is recorded rather than reproduced. Live
// decompilation prints "FUN_0067e2b0(); if (((uint)this & 1) != 0) {
// FUN_00f47380(); }", i.e. it gates on `this`. That reading is impossible here:
// the instruction bytes are F6 44 24 08 01, a byte test of the stack slot at
// [ESP + 0x8], not of any register. The same decompilation prints "return;"
// against a declared void signature, and warns "Unknown calling convention",
// which is consistent with a __thiscall entry that has no resolved prototype.
//
// Transfers. Exactly two, both direct immediates, matching the two outgoing
// edges the record's xref export carries for this address (0x0067e6b3 ->
// 0x0067e2b0, 0x0067e6c0 -> 0x00f47380). Nothing in the body is computed: the
// dispatch record reports indirect_calls 0 and the listing has no register- or
// memory-operand transfer, so this file declares no slot boundary of any kind,
// and it dereferences nothing -- not the receiver, not the gate word's pointee,
// because the gate word is only ever a test operand.
//
// Memory. The body performs no store. It reads one byte, the low byte of
// entry_ESP+0x4, exactly once, and it does that after the first callee has run.

#include "dfw_0067e6b0_types.hpp"

namespace openspore::reconstruction::pkg_dfw_0067e6b0 {

extern "C" pointer_to_the_receiver PKG_DFW_0067E6B0_THISCALL
dfw_0067e6b0_func3Ch(opaque_receiver receiver,
                     branch_gate_word argument_word) {
  // 0x0067e6b0  PUSH ESI
  // 0x0067e6b1  MOV ESI,ECX
  //
  // The only callee-save in the body, and there is no EBP frame: the listing
  // pushes nothing else and never sets up a frame pointer. ESI stops being the
  // entry register here and becomes the body's private copy of the receiver,
  // which is why both callees below are handed this value rather than a re-read
  // of ECX, and why the epilogue returns it.
  opaque_receiver const esi_receiver = receiver;

  // 0x0067e6b3  CALL 0x0067e2b0
  //
  // Unconditional: it runs on both the taken and the untaken branch, and it runs
  // before the gate word is read. Nothing is pushed for it -- the callee takes
  // the receiver in ECX, which is still the receiver because nothing between
  // 0x0067e6b1 and here overwrote it -- and the call is stack-neutral, so the
  // gate word is still at [ESP + 0x8] when the TEST below reads it.
  //
  // The return word is deliberately discarded. The callee leaves something
  // undefined in EAX, and 0x0067e6b8 does not read EAX and 0x0067e6c8
  // overwrites it, so nothing this body does depends on that word. The model
  // test pins that down with a poison value.
  (void)first_transfer_0067e2b0(receiver);

  // 0x0067e6b8  TEST byte ptr [ESP + 0x8],0x1
  // 0x0067e6bd  JZ 0x0067e6c8
  //
  // One bit of one byte of the body's own first argument, and the only test in
  // the body. The parameter arrives as the whole 4-byte word the record fixes
  // for the slot, and the immediate 0x1 is this body's own use of it: the other
  // 31 bits are read by the load and are not consulted, so a word with any bit
  // above bit 0 set and bit 0 clear takes the branch below the block exactly as
  // a zero word does.
  if ((argument_word & 0x1u) != 0u) {
    // 0x0067e6bf  PUSH ESI
    // 0x0067e6c0  CALL 0x00f47380
    // 0x0067e6c5  ADD ESP,0x4
    //
    // The argument of this transfer is the ESI copy of the receiver, not the
    // gate word and not a re-read of ECX. The cleanup at 0x0067e6c5 is on this
    // side, so the callee is caller-cleaned and takes exactly one word; that
    // matches the callee's own listing, which reads one word at [ESP + 0x4] and
    // ends in a bare RET. The word the callee leaves in EAX is not used: the
    // next instruction to write EAX is 0x0067e6c8.
    (void)second_transfer_00f47380(esi_receiver);
  }

  // 0x0067e6c8  MOV EAX,ESI
  // 0x0067e6ca  POP ESI
  // 0x0067e6cb  RET 0x4
  //
  // The single exit, shared by the taken and the untaken branch, and the only
  // write to the return register in the body. It returns the ESI copy, i.e. the
  // receiver as it was at entry. The saved register is restored before the
  // return, and RET 0x4 drops the argument word the caller pushed, which is the
  // callee-pops side of this entry's __thiscall.
  return esi_receiver;
}

}  // namespace openspore::reconstruction::pkg_dfw_0067e6b0
