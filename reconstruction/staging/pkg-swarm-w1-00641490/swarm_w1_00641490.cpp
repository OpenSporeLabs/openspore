// PKG-SWARM-W1-00641490 -- VA 0x00641490
// FUN_00641490 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 30 instructions, 0x00641490..0x006414d6 inclusive, 71 bytes,
// in four basic blocks. Every line of the model below is annotated with the
// instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for
// this package rather than taken on trust, because the committed Ghidra record
// stops one byte before the block its own branches target: it carries 25
// instructions, body_start 0x00641490, body_end 0x006414cf, body_span_bytes 64,
// and every one of the three conditional branches in it targets 0x006414d0, which
// is outside that span. `objdump -D -b binary -m i386 -M intel --adjust-vma=0x400c00
// --start-address=0x641490 --stop-address=0x6414e0 SPORE/SporeBin/SporeApp.exe`
// reproduces those 25 instructions at the same addresses and then shows the four
// that close the body:
//
//   006414d0  XOR AL,AL
//   006414d2  POP ESI
//   006414d3  ADD ESP,0x8
//   006414d6  RET
//
// followed by INT3 padding from 0x006414d7. The live decompilation of this VA
// merges the same block -- its final statement is `return uVar1 & 0xffffff00;`,
// the merged form of the XOR, and its `unaff_ESI` local is the ESI this body's
// own PUSH/POP pair accounts for. The model therefore has four exits, not two, and
// the shared 0x006414d0 block is the one every failing branch lands on.
//
//   00641490  SUB ESP,0x8
//   00641493  PUSH ESI
//   00641494  MOV ESI,ECX
//   00641496  LEA EAX,[ESI + 0x4]
//   00641499  PUSH EAX
//   0064149a  CALL 0x00552300
//   0064149f  ADD ESP,0x4
//   006414a2  CMP EAX,0x2
//   006414a5  JNZ 0x006414d0
//   006414a7  MOV EDX,dword ptr [ESI]
//   006414a9  MOV EDX,dword ptr [EDX + 0x90]
//   006414af  LEA EAX,[ESP + 0x4]
//   006414b3  PUSH EAX
//   006414b4  MOV ECX,ESI
//   006414b6  CALL EDX
//   006414b8  TEST AL,AL
//   006414ba  JZ 0x006414d0
//   006414bc  MOV EAX,dword ptr [ESP + 0x4]
//   006414c0  AND EAX,dword ptr [ESP + 0x8]
//   006414c4  CMP EAX,-0x1
//   006414c7  JZ 0x006414d0
//   006414c9  MOV AL,0x1
//   006414cb  POP ESI
//   006414cc  ADD ESP,0x8
//   006414cf  RET
//   006414d0  XOR AL,AL
//   006414d2  POP ESI
//   006414d3  ADD ESP,0x8
//   006414d6  RET
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk.
//
//   entry-12  the saved ESI, pushed at 0x00641493 and popped on both exits
//   entry-8   the pair's first word. 0x006414af takes its address with
//             `LEA EAX,[ESP + 0x4]` at ESP = entry-12, and 0x006414bc reads it
//             back with `MOV EAX,[ESP + 0x4]` at the same ESP, which is where the
//             slot's single argument lives
//   entry-4   the pair's second word. 0x006414c0 `AND EAX,[ESP + 0x8]` at
//             ESP = entry-12
//   entry+4   the return address. Nothing reads it: the terminator is a bare RET
//             with no immediate, so this body takes no ordinary stack argument
//
// The walk ends at entry+4 on both exits (POP ESI then ADD ESP,0x8 from
// entry-12), which is a bare RET's ESP, and the pair's two reads land inside the
// eight bytes 0x00641490 reserved. Two independent agreements: the address handed
// to the slot at 0x006414af and the address the body reads back at 0x006414bc are
// the same slot, so the callee wrote what the caller reads; and 0x006417d0 -- the
// function the table run at 0x013ff648 holds at displacement 0x90 -- writes
// exactly `[ECX]` and `[ECX+0x4]` of the pointer it is given, which are the two
// words this body ANDs together.
//
// ABI: __thiscall, receiver in ECX, zero ordinary stack arguments, `RET`. The
// machine-derived record agrees (`conventions.calling_convention __thiscall`,
// confidence INFERRED, verdict ABI_INFERRED, cleanup bytes 0 side caller,
// `ghidra_function.parameter_count` 0) and the body bears it out: ECX is aliased
// into ESI at 0x00641494 and every receiver access goes through that alias, which
// is why the record reports register ECX with shape R-ALIAS. The decompilation
// disagrees on two points and the listing is followed on both: it declares a
// `__fastcall` convention and models the receiver as a stack parameter
// (`param_1`, read as `*param_1` and `param_1 + 1`); and it ORs nothing but drops
// the second AND operand into its `unaff_ESI` name, so its
// `uVar1 = unaff_ESI & local_8[0]` is this body's AND of the pair's second word
// with its first, with the operands the other way round. The AND is commutative
// so the value is the same; the frame is not, and the listing's is used.
//
// VIRTUAL DISPATCH: one site, 0x006414b6 `CALL EDX`, and it is a two-level table
// load. 0x006414a7 reads the receiver's word at displacement 0 into EDX, and
// 0x006414a9 reads the word at displacement 0x90 out of the table EDX now holds
// into the same register, which is the register the CALL transfers through. The
// slot displacement 0x90 is the whole of what the machine says about the table,
// and the model declares nothing else about it: no slot index, no table size, no
// class, and no name for the function it lands on (see the header's note on the
// table runs, which is deliberately outside this span).
//
// GLOBALS: none. No instruction in the body names a data-segment address; the only
// absolute operands are the direct call target 0x00552300 and the three branch
// targets 0x006414d0, all of which are code.

#include "swarm_w1_00641490_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00641490 {

extern "C" std::uint8_t PKG_SWARM_W1_00641490_THISCALL re_00641490(
    SporepediaAssetReceiver* receiver) {
  // 00641493  PUSH ESI
  // 00641494  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the LEA at 0x00641496. ECX is then reused as the
  // argument register of the dispatch at 0x006414b4, which is why the machine
  // record reports register ECX with shape R-ALIAS and why no receiver field is
  // read through ECX anywhere in this body.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT
  // into it. The record enumerates offsets [0] with bounds_only true: it states
  // where the body was seen reaching and not which member is which, so no member
  // name is written for any of it. The two displacements this body uses are 0x00
  // (read) and 0x04 (an address formed, not a read).
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00641490  SUB ESP,0x8
  //
  // The eight bytes are the pair the slot is handed and this body reads back
  // (entry-8 and entry-4 in the frame note above). The model declares that pair
  // below rather than at the top of the function, because the machine only
  // materialises it at 0x006414af, after the status test has already been made.
  //
  // 00641496  LEA EAX,[ESI + 0x4]
  // 00641499  PUSH EAX
  // 0064149a  CALL 0x00552300
  //
  // One word, the address receiver+0x04, and the callee is cdecl: 0x0064149f
  // drops the four bytes itself. The argument is a POINTER and the callee
  // dereferences it -- 0x00552318 `MOV EAX,[EBP+0x8]` then 0x0055231b
  // `MOV ECX,[EAX]` -- reading three dwords at its +0, +4 and +8, so what this
  // body hands over is the address of a 12-byte run inside the receiver, and not
  // the receiver, and not the pair, and not a copy of any of them.
  //
  // 0064149f  ADD ESP,0x4
  //
  // The cdecl cleanup. It is the first thing after the call, so nothing the
  // callee returned in EAX is disturbed by it.
  const Word status = sporepedia_asset_status_00552300(
      word_at(self, kReceiverAssetFieldDisplacement));

  // 006414a2  CMP EAX,0x2
  // 006414a5  JNZ 0x006414d0
  //
  // One compare, one constant, taken as a full 32-bit equality -- not a range,
  // not a mask, and not a signed test. 0x00552300's own listing returns 0x0
  // (0x0055243e), 0x1 (0x0055241a), 0x2 (0x00552439) or the word at [EBP-0x30]
  // (0x005523ec), so the branch decides between exactly one of those four
  // outcomes and "everything else". Nothing here says what the four mean, and
  // none is named.
  if (status != kStatusComparedValue) {
    // 006414d0  XOR AL,AL
    // 006414d2  POP ESI
    // 006414d3  ADD ESP,0x8
    // 006414d6  RET
    //
    // The shared failure exit, and the only exit that produces a value from
    // nothing: an 8-bit clear of AL, so the return is 0. The body never got as
    // far as forming the pair's address, so nothing is read and nothing is
    // dispatched.
    return kFalse;
  }

  // 006414a7  MOV EDX,dword ptr [ESI]
  //
  // The dispatch word, at the receiver's own displacement 0. It is a table
  // address, not a member this body ever looks at again: the next instruction
  // reads through it and it is never dereferenced as an object.
  const void* const vtable =
      reinterpret_cast<const void*>(word_value_at(self, kReceiverDispatchDisplacement));

  // 006414a9  MOV EDX,dword ptr [EDX + 0x90]
  //
  // The slot. 0x90 is a byte displacement and is a whole number of dword slots
  // (asserted in the header), and it is the SECOND load of the two: the first
  // took the table out of the receiver, this one takes the target out of the
  // table. A reconstruction that read the receiver's word as the target itself
  // would skip this instruction, and the model test plants a decoy for exactly
  // that.
  //
  // Nothing is said here about the table beyond that one displacement. The xref
  // export's thirteen vtable associations for this VA disagree with each other
  // about where this body sits inside a run of pointers (three of the tables hold
  // it at +0x80 and two hold it at +0x74, four of the thirteen hold float
  // constants or text at the offsets the record implies), this binary carries no
  // MSVC RTTI, and the byte before the run at 0x013ff648 is a float -- so no slot
  // INDEX is claimed and none is needed by the model.
  const SlotTarget target = reinterpret_cast<SlotTarget>(
      word_value_at(vtable, kDispatchSlotDisplacement));

  // 00641490  SUB ESP,0x8 (the pair's storage, resolved here)
  //
  // The machine does not initialise these eight bytes. It does not have to: the
  // only reader of them is the code below, the only writer is the slot call
  // immediately after it, and this body reads the pair only when that call
  // reported non-zero in AL. So the pair's contents are the callee's to define
  // and this body's to combine. The model zero-initialises the object so that a
  // callee which reports success without writing is observable as (0, 0) rather
  // than as undefined behaviour; that initialiser is a determinism aid and is
  // not a claim that the machine zeroes anything.
  DisplacementRange range{};

  // 006414af  LEA EAX,[ESP + 0x4]
  // 006414b3  PUSH EAX
  // 006414b4  MOV ECX,ESI
  // 006414b6  CALL EDX
  //
  // The dispatch. ECX is the receiver itself (0x006414b4 copies the alias, not
  // the address formed at 0x00641496), and the single stack word is the pair's
  // address. The callee owns the cleanup -- 0x006417d0, the entry the table run at
  // 0x013ff648 holds at this displacement, ends `C2 04 00` -- which is why there
  // is no ADD ESP after the CALL and why the two reads below are at ESP+4 and
  // ESP+8 rather than one word higher. The transfer target is whatever the slot
  // held at run time, so the model calls through the loaded pointer and names no
  // function here.
  const std::uint8_t reported = target(receiver, &range);

  // 006414b8  TEST AL,AL
  // 006414ba  JZ 0x006414d0
  //
  // A zero test of the LOW BYTE of the return register and nothing else. Any
  // value with a non-zero AL takes the surviving path whatever its upper three
  // bytes are, and any value with a zero AL fails whatever its upper three bytes
  // are; the model test drives both directions with disagreeing upper bytes. The
  // branch is `JZ`, so a zero AL is the FAILING case.
  if (reported == kFalse) {
    // 006414d0  XOR AL,AL
    // 006414d2  POP ESI
    // 006414d3  ADD ESP,0x8
    // 006414d6  RET
    //
    // The same shared failure exit as the status test. The pair was written by
    // the call above and is not read on this path -- the model returns before
    // touching it, and the model test poisons the callee's output to show the
    // outcome does not depend on it.
    return kFalse;
  }

  // 006414bc  MOV EAX,dword ptr [ESP + 0x4]
  // 006414c0  AND EAX,dword ptr [ESP + 0x8]
  // 006414c4  CMP EAX,-0x1
  // 006414c7  JZ 0x006414d0
  //
  // The two words of the pair, ANDed, against all-ones. The two facts that make
  // this a pair test and not a value test are separate in the listing and both are
  // modelled: both words are read (0x006414bc and 0x006414c0, at the pair's +0
  // and +4), and the AND is a bitwise AND, so the comparison is all-ones exactly
  // when BOTH words are all-ones. The comparison itself is a full 32-bit equality
  // with the immediate -1, which has no signedness to get wrong.
  //
  // 0x006417d0 makes the same judgement on the same pair with two compares
  // instead of an AND (`CMP DWORD PTR [EAX],0xffffffff` then `CMP DWORD PTR
  // [EAX+0x4],0xffffffff`, both jumping to the same place), which is a second
  // witness that all-ones in both words is the rejected case and that neither word
  // alone decides it.
  const Word combined = static_cast<Word>(
      word_value_at(&range, kPairFirstWordDisplacement) &
      word_value_at(&range, kPairSecondWordDisplacement));
  if (combined == kSentinelRejected) {
    // 006414d0  XOR AL,AL ... 0x006414d6  RET
    //
    // The third and last route into the shared failure exit. Note that the
    // rejected value is produced by the callee, not by this body: 0x006417d0
    // returns 0 on exactly this condition and never writes the pair, so on that
    // callee this branch is unreachable -- but the body tests for it itself, and
    // the model test drives it through a slot target that does report success and
    // does write all-ones in both words.
    return kFalse;
  }

  // 006414c9  MOV AL,0x1
  // 006414cb  POP ESI
  // 006414cc  ADD ESP,0x8
  // 006414cf  RET
  //
  // The surviving exit, and an 8-bit store: the return value is 1 in AL. The
  // upper three bytes of EAX keep bits 8..31 of the AND result -- the machine does
  // not clear them and the body never reads them -- and the record lists no caller
  // for this VA at all (all six of its xrefs are data references from pointer
  // runs), so nothing in this repository observes them. The model returns the byte
  // the machine's AL holds and the model test asserts that the AND value does not
  // leak into it.
  return kTrue;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641490
