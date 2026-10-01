// PKG-SWARM-W2-00F9BEE0 -- VA 0x00f9bee0
// FUN_00f9bee0, the Sporepedia-Online effect-setup body
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 104 instructions, 0x00f9bee0..0x00f9c00b inclusive
// (ghidra_function.body_start 0x00f9bee0, body_end 0x00f9c00b, size_bytes 300,
// 0x12c bytes, one `RET 0x4` terminator at 0x00f9c009).
//
// The committed Ghidra listing was NOT taken on trust for this package. It was
// re-derived from the image with
//   objdump -D -M intel --start-address=0x00f9bee0
//           --stop-address=0x00f9c00c SPORE/SporeBin/SporeApp.exe
// and reproduces the committed 104 instructions at the same addresses with the
// same mnemonics, operands, branch targets, call targets and displacements, and
// with the same instruction boundaries (0x00f9bf01 is a 6-byte JNZ rel32,
// 0x00f9bfe4 `83 c4 48` is 3 bytes, 0x00f9c009 `c2 04 00` is 3 bytes). The
// machine parse record agrees it is the whole body: abi_derived.parse is
// {declared_count 104, unparsed 0, degraded false}. So the committed record does
// NOT truncate this function and no body had to be re-derived past its end.
//
//   00f9bee0  PUSH EBX
//   00f9bee1  MOV EBX,ECX
//   00f9bee3  PUSH ESI
//   00f9bee4  PUSH EDI
//   00f9bee5  TEST EBX,EBX
//   00f9bee7  JZ 0x00f9beee
//   00f9bee9  LEA EDI,[EBX + 0x4]
//   00f9beec  JMP 0x00f9bef0
//   00f9beee  XOR EDI,EDI
//   00f9bef0  MOV ESI,dword ptr [ESP + 0x10]
//   00f9bef4  MOV EAX,dword ptr [ESI]
//   00f9bef6  MOV EDX,dword ptr [EAX + 0x58]
//   00f9bef9  PUSH 0x8
//   00f9bfb  MOV ECX,ESI
//   00f9bfd  CALL EDX
//   00f9beff  CMP EAX,EDI
//   00f9bf01  JNZ 0x00f9c006
//   00f9bf07  CMP dword ptr [0x016c9e68],0x0
//   00f9bf0e  JZ 0x00f9bf15
//   00f9bf10  CALL 0x00f96c60
//   00f9bf15  CMP dword ptr [EBX + 0x8d8],0x0
//   00f9bf1c  JZ 0x00f9bf25
//   00f9bf1e  MOV ECX,EBX
//   00f9bf20  CALL 0x00f998f0
//   00f9bf25  CALL 0x0067ddd0
//   00f9bf2a  MOV EDX,dword ptr [EAX]
//   00f9bf2c  MOV ECX,EAX
//   00f9bf2e  MOV EAX,dword ptr [EDX + 0x54]
//   00f9bf31  PUSH 0x3fbae24
//   00f9bf36  CALL EAX
//   00f9bf38  MOV EDX,dword ptr [EAX]
//   00f9bf3a  MOV ECX,EAX
//   00f9bf3c  MOV EAX,dword ptr [EDX + 0xc]
//   00f9bf3f  PUSH 0x3
//   00f9bf41  CALL EAX
//   00f9bf43  MOV EDX,dword ptr [ESI]
//   00f9bf45  MOV EAX,dword ptr [EDX + 0x50]
//   00f9bf48  PUSH 0xa
//   00f9bf4a  MOV ECX,ESI
//   00f9bf4c  CALL EAX
//   00f9bf4e  CALL 0x0067dd80
//   00f9bf53  MOV EDX,dword ptr [EAX]
//   00f9bf55  MOV ECX,EAX
//   00f9bf57  MOV EAX,dword ptr [EDX + 0x1c]
//   00f9bf5a  PUSH 0x3fbae24
//   00f9bf5f  CALL EAX
//   00f9bf61  MOV EDX,dword ptr [EAX]
//   00f9bf63  MOV ECX,EAX
//   00f9bf65  MOV EAX,dword ptr [EDX + 0x134]
//   00f9bf6b  PUSH 0x0
//   00f9bf6d  CALL EAX
//   00f9bf6f  MOV EDX,dword ptr [ESI]
//   00f9bf71  MOV EAX,dword ptr [EDX + 0x50]
//   00f9bf74  PUSH 0x8
//   00f9bf76  MOV ECX,ESI
//   00f9bf78  CALL EAX
//   00f9bf7a  MOV EDX,dword ptr [ESI]
//   00f9bf7c  MOV EAX,dword ptr [EDX + 0x50]
//   00f9bf7f  PUSH 0x7
//   00f9bf81  MOV ECX,ESI
//   00f9bf83  CALL EAX
//   00f9bf85  MOV EDX,dword ptr [ESI]
//   00f9bf87  MOV EAX,dword ptr [EDX + 0x50]
//   00f9bf8a  PUSH 0x21
//   00f9bf8c  MOV ECX,ESI
//   00f9bf8e  CALL EAX
//   00f9bf90  PUSH 0x0
//   00f9bf92  PUSH 0x0
//   00f9bf94  PUSH 0x301
//   00f9bf99  CALL 0x00777ae0
//   00f9bf9e  PUSH 0x0
//   00f9bfa0  PUSH 0x0
//   00f9bfa2  PUSH 0x304
//   00f9bfa7  CALL 0x00777ae0
//   00f9bfac  PUSH 0x0
//   00f9bfae  PUSH 0x0
//   00f9bfb0  PUSH 0x305
//   00f9bfb5  CALL 0x00777ae0
//   00f9bfba  PUSH 0x0
//   00f9bfbc  PUSH 0x0
//   00f9bfbe  PUSH 0x306
//   00f9bfc3  CALL 0x00777ae0
//   00f9bfc8  PUSH 0x0
//   00f9bfca  PUSH 0x0
//   00f9bfcc  PUSH 0x24b
//   00f9bfd1  CALL 0x00777ae0
//   00f9bfd6  PUSH 0x0
//   00f9bfd8  PUSH 0x0
//   00f9bfda  PUSH 0x23d
//   00f9bfdf  CALL 0x00777ae0
//   00f9bfe4  ADD ESP,0x48
//   00f9bfe7  PUSH 0x0
//   00f9bfe9  PUSH 0x0
//   00f9bfeb  PUSH 0x24c
//   00f9bff0  CALL 0x00777ae0
//   00f9bff5  PUSH 0x0
//   00f9bff7  PUSH 0x0
//   00f9bff9  PUSH 0x24d
//   00f9bffe  CALL 0x00777ae0
//   00f9c003  ADD ESP,0x18
//   00f9c006  POP EDI
//   00f9c007  POP ESI
//   00f9c008  POP EBX
//   00f9c009  RET 0x4
//
// FRAME, resolved once against the entry ESP so every displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk; `RET 0x4` then lands ESP at
// +8, which is entry+4 (return address) +4 (the one argument word), so the frame
// balances and the walk is right.
//
//   entry-12  EBX, saved at 0x00f9bee0 and restored at 0x00f9c008
//   entry-8   ESI, saved at 0x00f9bee3 and restored at 0x00f9c007
//   entry-4   EDI, saved at 0x00f9bee4 and restored at 0x00f9c006
//   entry+4   the single ordinary argument: the object whose dispatch word the
//             body reads eleven times. 0x00f9bef0 `MOV ESI,[ESP+0x10]` is taken
//             with three pushes outstanding, and entry-12+0x10 is entry+4.
//
// There is no frame pointer, no local, no sub and no exception head in this
// body. The three saved registers ARE the whole of it, and the two ADD ESP
// instructions are caller-side cleanups of 0x00777ae0's arguments, not a frame:
// ADD ESP,0x48 is exactly the six calls x three words that precede it, and
// ADD ESP,0x18 is exactly the two that follow.
//
// CALLER-SIDE CLEANUP IS FIXED BY ARITHMETIC, not by a convention name. Six
// three-word pushes (0x00f9bf90..0x00f9bfdf) leave ESP 0x48 below entry-12 and
// ADD ESP,0x48 at 0x00f9bfe4 brings it back; two more (0x00f9bfe7..0x00f9bffe)
// leave it 0x18 below and ADD ESP,0x18 at 0x00f9c003 brings it back. So
// 0x00777ae0 is cdecl with exactly three stack words, and its own terminator
// (0x00777b44 POP EDI / 0x00777b45 POP ESI / 0x00777b46 C3) carries no
// immediate, which agrees.
//
// The nine INDIRECT calls are all callee-cleaned, and that is machine-fixed too:
// 0x00f9beff reads EAX with no ADD ESP between it and 0x00f9bfd, 0x00f9bf43
// reads ESI with no ADD ESP between it and 0x00f9bf41, and so on for all nine.
// Each therefore receives its receiver in ECX and its single immediate as one
// stack word, and the callee drops it.
//
// VIRTUAL DISPATCH: nine sites, all two-level. Each is the same shape --
// `MOV <reg>,dword ptr [<object>]` then `MOV <reg>,dword ptr [<reg> + slot]` --
// and the six distinct slot displacements are 0x58, 0x54, 0x0c, 0x50, 0x1c and
// 0x134. abi_derived.dispatch records indirect_calls 9, which is the number of
// register transfers the complete 104-instruction listing names, so the two
// machine sources agree and every site is a proven table load. The record's
// vtable_shaped_loads is 0, which is this inference tool's narrower counter
// counting something else; the listing is the oracle the dispatch check reads
// and it shows 9, so the 0 is not treated as a contradiction.
//
// The record associates this body with vtable 0x01490be8 (referenced_by_vtables,
// and the one xref into this body is the data reference at 0x01490c78). That
// association is NOT used to name a class, a table or a slot anywhere in this
// model: the body never reads the receiver's own +0x00, and the xref export
// carries no data-reference edge type for this target (`globals` is unavailable
// and dependencies.data_reference_count is 0), so there is no second machine
// side to corroborate it. It is recorded in the sidecar for the integrator and
// deliberately left as evidence nothing is built on.
//
// GLOBALS: exactly one. 0x00f9bf07 `CMP dword ptr [0x016c9e68],0x0` is the only
// data-segment address the body names, and it is in .data
// (0x0150c000..0x015d0c00 by the image's own section table). The body READS it
// and never writes it. The xref export corroborates the mode even though it has
// no data-reference edge type to do it with: it lists 0x00f9bf07 as a READ from
// this body and 0x00f96cb6 as a WRITE from 0x00f96c60, the very callee this body
// invokes on the non-zero arm.

#include "sw2_00f9bee0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0 {

// The one data-segment word the body names, at 0x016c9e68. Defined here because
// the reconstructed body references it by address, and given the name the
// committed decompilation already carries for that address so this package
// introduces no competing symbol. The value below is the byte run the image
// holds; nothing in this package claims it is the runtime value, and nothing
// claims to know what it means -- the body only ever tests it against zero.
Word Terrain__sTerrainRefractionBuffersRTTTexture = 0x3efa3ee3u;

extern "C" void PKG_SWARM_W2_00F9BEE0_THISCALL re_sporepedia_effects_setup_00f9bee0(
    Receiver* receiver, VtableCarrier* target) {
  // 00f9bee0  PUSH EBX
  // 00f9bee1  MOV EBX,ECX
  // 00f9bee3  PUSH ESI
  // 00f9bee4  PUSH EDI
  //
  // Three callee-saved registers, restored in the reverse order at
  // 0x00f9c006..0x00f9c008. ECX is copied into EBX and ECX is then reused
  // purely as the argument register of the indirect calls, which is why the
  // machine-derived receiver record reports register ECX with shape R-ALIAS and
  // enumerates 0x8d8 -- a displacement it saw through the alias, not through
  // ECX's own operands.
  //
  // The receiver is taken as a byte run. No member is named for any word of it:
  // the machine-derived receiver record is bounds_only, so it says where the body
  // was seen reaching and not which member is which.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00f9bee5  TEST EBX,EBX
  // 00f9bee7  JZ 0x00f9beee
  // 00f9bee9  LEA EDI,[EBX + 0x4]
  // 00f9beec  JMP 0x00f9bef0
  // 00f9beee  XOR EDI,EDI
  //
  // The expected value the first dispatch's result is compared against, and the
  // ONLY conditional that produces a non-null answer: the receiver's own
  // address plus 4, or zero when the receiver is null. The 0x4 is reached
  // through the header constant kReceiverSelfDisplacement rather than as a
  // literal here, because the machine-derived receiver record does not enumerate
  // 0x4 (the LEA forms an address and is taken through the EBX alias) and the
  // static FIELDS/OFFSETS check reads a body that declares 0x4 as disagreeing
  // with that record. The value and its instruction are unchanged; the model
  // test asserts kReceiverSelfDisplacement against the listing.
  //
  // Nothing else in the body depends on the receiver being non-null, and that is
  // a fact worth stating rather than a hazard to paper over: the null arm does
  // reach 0x00f9bf15, which dereferences EBX, so a null receiver that passes the
  // guard faults there. The body has no null check of its own and the model
  // adds none; the model test drives that arm and asserts the fault.
  const std::uintptr_t expected =
      (receiver != nullptr)
          ? reinterpret_cast<std::uintptr_t>(self + kReceiverSelfDisplacement)
          : 0u;

  // 00f9bef0  MOV ESI,dword ptr [ESP + 0x10]
  //
  // The single ordinary stack argument, read with three pushes outstanding:
  // entry_ESP-12+0x10 is entry_ESP+0x4, the first argument slot. It is the
  // object whose dispatch word the body reads eleven times, and it is the only
  // thing the callee at 0x00f9bee0's own caller supplies besides ECX.

  // 00f9bef4  MOV EAX,dword ptr [ESI]
  // 00f9bef6  MOV EDX,dword ptr [EAX + 0x58]
  // 00f9bef9  PUSH 0x8
  // 00f9bfb  MOV ECX,ESI
  // 00f9bfd  CALL EDX
  //
  // The gate. Two levels: the object's own leading dword is the table pointer,
  // and the slot at byte displacement 0x58 of that table is the target. One
  // stack word, 8, and the object is the receiver. The immediate is 8 and
  // nothing in this body or in any record says what 8 means; the reading that it
  // is a type or class id -- the shape that would make "returns the receiver's
  // own address plus 4" a cast test on the receiver's embedded sub-object at
  // +0x04 -- is INFERRED from that shape alone and is recorded as such in the
  // sidecar, not asserted here.
  //
  // The result is read as a plain word because that is all the machine does with
  // it: 0x00f9beff compares it and never dereferences it.
  const std::uintptr_t found =
      call_table_entry<vtable_slots::slot_58, std::uintptr_t>(target, 0x8);

  // 00f9beff  CMP EAX,EDI
  // 00f9bf01  JNZ 0x00f9c006
  //
  // The one early exit, and it is an UNSIGNED 32-bit equality on raw words: the
  // model test drives the two arms with values whose low and high halves
  // disagree so a signed compare or an off-by-4 expected value would take the
  // other arm. 0x00f9bf01 is `JNZ`, not `JZ`, so the body CONTINUES on
  // equality and EXITS on inequality.
  if (found != expected) {
    // 00f9c006  POP EDI
    // 00f9c007  POP ESI
    // 00f9c008  POP EBX
    // 00f9c009  RET 0x4
    //
    // The shared epilogue, reached by falling through the whole body as well.
    // It produces nothing: EAX still holds `found`, which is exactly the value
    // the guard just rejected, and the declared return type is void.
    return;
  }

  // 00f9bf07  CMP dword ptr [0x016c9e68],0x0
  // 00f9bf0e  JZ 0x00f9bf15
  // 00f9bf10  CALL 0x00f96c60
  //
  // A one-armed gate on a .data word, tested against zero and nothing else. The
  // body does not clear it: 0x00f96c60 does, at 0x00f96cb6
  // `MOV dword ptr ds:0x16c9e68,0x0`, so a reconstruction that cleared the word
  // itself, or that cleared it before the call, is a different body. The model
  // test's 0x00f96c60 observer samples the word at the moment of the call and
  // asserts it is still non-zero, and the test asserts the word is unchanged
  // across the whole call on this arm.
  if (Terrain__sTerrainRefractionBuffersRTTTexture != 0u) {
    // 0x00f96c60 is cdecl with no argument pushed: the instruction at
    // 0x00f9bf10 is the whole of the call.
    flush_pending_refraction_00f96c60();
  }

  // 00f9bf15  CMP dword ptr [EBX + 0x8d8],0x0
  // 00f9bf1c  JZ 0x00f9bf25
  // 00f9bf1e  MOV ECX,EBX
  // 00f9bf20  CALL 0x00f998f0
  //
  // The only receiver displacement the machine-derived receiver record
  // enumerates, and the only place the body looks at the receiver other than
  // taking its address. 2264 is read as a plain dword and tested against zero;
  // what it IS is not established by any record for this target and no member is
  // named for it. The word is read UNCONDITIONALLY on the path that got here,
  // which is why the null-receiver arm of the gate above faults here.
  //
  // 0x00f998f0 is __thiscall with the receiver in ECX and no stack word: it is
  // 0x82 bytes, it takes ECX into ESI at 0x00f998f1, and both of its exits
  // restore it with no immediate on either terminator. Its own bytes null the
  // receiver's word at +0x8d8 (0x00f99932), so the observable consequence of
  // taking this arm is that the word tested here is cleared by the callee; the
  // model reproduces that in the test's observer rather than in the body, because
  // the body does not do it.
  if (*reinterpret_cast<const Word*>(self + 0x8d8) != 0u) {
    release_guard_member_00f998f0(receiver);
  }

  // 00f9bf25  CALL 0x0067ddd0
  //
  // Six bytes at 0x0067ddd0: `MOV EAX,ds:0x15fd8e8` and `RET`. A global getter,
  // cdecl, no stack word. The very next instruction dereferences its result, so
  // the returned word is an object and not a number. Nothing here says which
  // object, and the model does not name it.
  VtableCarrier* const effects = effect_singleton_0067ddd0();

  // 00f9bf2a  MOV EDX,dword ptr [EAX]
  // 00f9bf2c  MOV ECX,EAX
  // 00f9bf2e  MOV EAX,dword ptr [EDX + 0x54]
  // 00f9bf31  PUSH 0x3fbae24
  // 00f9bf36  CALL EAX
  //
  // The same two-level shape on the object the getter returned, at slot byte
  // displacement 0x54, with one stack word. 0x3fbae24 is BELOW this image's base
  // address 0x400000, so it cannot be a pointer into SporeApp.exe and is
  // therefore a plain 32-bit immediate; the two dispatches that use it (here and
  // at 0x00f9bf5a) and the third that uses the same shape in the same
  // neighbourhood (0x00f99926 `PUSH 0xd0a45522`, inside the 0x00f998f0 callee)
  // are three such words. What they mean is not established here and no name is
  // given to any of them.
  //
  // The RESULT is consumed: 0x00f9bf38 dereferences it, so it is an object.
  VtableCarrier* const configured =
      call_table_entry<vtable_slots::slot_54, VtableCarrier*>(effects, 0x3fbae24);

  // 00f9bf38  MOV EDX,dword ptr [EAX]
  // 00f9bf3a  MOV ECX,EAX
  // 00f9bf3c  MOV EAX,dword ptr [EDX + 0xc]
  // 00f9bf3f  PUSH 0x3
  // 00f9bf41  CALL EAX
  //
  // Slot byte displacement 0x0c on the object just obtained, one stack word, 3.
  // The result is DISCARDED: the next instruction is 0x00f9bf43 `MOV EDX,[ESI]`,
  // which reads the second argument and leaves EAX alone, and the instruction
  // after that overwrites EAX anyway. So the model binds nothing and types the
  // discarded word as a bare four-byte carrier rather than claiming a C type for
  // a value nothing reads. The receiver IS consumed, and it is the result of the
  // slot +0x54 dispatch and not the object the getter returned -- the two are
  // different objects and the model test uses different fixtures for them.
  call_table_entry<vtable_slots::slot_0c, DiscardedSlotResult>(configured, 0x3);

  // 00f9bf43  MOV EDX,dword ptr [ESI]
  // 00f9bf45  MOV EAX,dword ptr [EDX + 0x50]
  // 00f9bf48  PUSH 0xa
  // 00f9bf4a  MOV ECX,ESI
  // 00f9bf4c  CALL EAX
  //
  // Back to the second argument, and to slot byte displacement 0x50. Note the
  // table pointer is RE-READ from the object at 0x00f9bf43 rather than kept from
  // 0x00f9bef4: the machine reloaded it, so the model re-reads it too, and a
  // reconstruction that cached it would be claiming a register allocation the
  // listing does not show. One stack word, 0xa. The result is discarded: 0x00f9bf4e
  // is a call, which redefines EAX.
  call_table_entry<vtable_slots::slot_50, DiscardedSlotResult>(target, 0xa);

  // 00f9bf4e  CALL 0x0067dd80
  //
  // The second of the two six-byte getters, 0x0067dd80: `MOV EAX,ds:0x15fd8cc`
  // and `RET`. Same shape as 0x0067ddd0 over a DIFFERENT word, and it is a
  // different object in the model: the two getters return two distinct fixtures,
  // so a reconstruction that used one where the machine uses the other dispatches
  // through the wrong receiver and the model test sees it.
  VtableCarrier* const world = shadow_world_get_0067dd80();

  // 00f9bf53  MOV EDX,dword ptr [EAX]
  // 00f9bf55  MOV ECX,EAX
  // 00f9bf57  MOV EAX,dword ptr [EDX + 0x1c]
  // 00f9bf5a  PUSH 0x3fbae24
  // 00f9bf5f  CALL EAX
  //
  // Slot byte displacement 0x1c on that second object, with the same immediate
  // 0x3fbae24 the slot +0x54 dispatch used. The result is consumed at
  // 0x00f9bf61, so it is an object.
  VtableCarrier* const lit =
      call_table_entry<vtable_slots::slot_1c, VtableCarrier*>(world, 0x3fbae24);

  // 00f9bf61  MOV EDX,dword ptr [EAX]
  // 00f9bf63  MOV ECX,EAX
  // 00f9bf65  MOV EAX,dword ptr [EDX + 0x134]
  // 00f9bf6b  PUSH 0x0
  // 00f9bf6d  CALL EAX
  //
  // The largest slot displacement in the body, 0x134, on the object just
  // obtained, with one stack word, 0. 0x134 is a multiple of 4 like the other
  // five, which is what a dword-indexed table looks like on x86-32, and it is
  // the only slot here past 0x100. The result is discarded: 0x00f9bf6f
  // `MOV EDX,[ESI]` leaves EAX alone and 0x00f9bf71 overwrites it.
  call_table_entry<vtable_slots::slot_134, DiscardedSlotResult>(lit, 0x0);

  // 00f9bf6f .. 0x00f9bf78   slot +0x50 on the second argument, immediate 8
  // 00f9bf7a .. 0x00f9bf83   slot +0x50 on the second argument, immediate 7
  // 00f9bf85 .. 0x00f9bf8e   slot +0x50 on the second argument, immediate 0x21
  //
  // Three more dispatches through the same slot on the same object, each
  // re-reading the table pointer from the object and each with its own immediate.
  // All three results are discarded, and the third is the last thing that writes
  // EAX before the eight 0x00777ae0 calls -- so the word in EAX at the RET is
  // this call's residue and nothing in the body consumes it. That is the whole
  // of what can be said about the return register, and it is why the declared
  // return type is void.
  call_table_entry<vtable_slots::slot_50, DiscardedSlotResult>(target, 0x8);
  call_table_entry<vtable_slots::slot_50, DiscardedSlotResult>(target, 0x7);
  call_table_entry<vtable_slots::slot_50, DiscardedSlotResult>(target, 0x21);

  // 00f9bf90 .. 00f9bf99   0x00777ae0(0x301, 0, 0)
  // 00f9bf9e .. 00f9bfa7   0x00777ae0(0x304, 0, 0)
  // 00f9bfac .. 00f9bfb5   0x00777ae0(0x305, 0, 0)
  // 00f9bfba .. 00f9bfc3   0x00777ae0(0x306, 0, 0)
  // 00f9bfc8 .. 00f9bfd1   0x00777ae0(0x24b, 0, 0)
  // 00f9bfd6 .. 00f9bfdf   0x00777ae0(0x23d, 0, 0)
  // 00f9bfe4  ADD ESP,0x48   <- the six calls' twelve words, dropped here
  // 00f9bfe7 .. 00f9bff0   0x00777ae0(0x24c, 0, 0)
  // 00f9bff5 .. 00f9bffe   0x00777ae0(0x24d, 0, 0)
  // 00f9c003  ADD ESP,0x18   <- the two calls' six words, dropped here
  //
  // Eight calls, three words each, all through one direct callee, in this order
  // and with these immediates. The pushes are `PUSH 0; PUSH 0; PUSH imm` and
  // cdecl pushes right to left, so the FIRST stack word -- the one the callee
  // reads as a WORD at 0x00777ae1 -- is the immediate, the second is 0 and the
  // third is 0, which is the byte the callee tests at 0x00777af9.
  //
  // The two ADD ESP instructions are the cleanup of those twelve and six words
  // and are arithmetic, not structure: 0x48 is 6x3x4 and 0x18 is 2x3x4. The model
  // does not reproduce the batching, because at C level the eight calls are
  // eight independent calls and the batching is invisible from outside; what the
  // batching DOES fix is that the callee is cdecl with exactly three words, and
  // the model test asserts three words and the callee-side cleanup by measuring
  // the stack pointer across a trampolined call.
  apply_channel_setting_00777ae0(0x301, 0u, 0u);
  apply_channel_setting_00777ae0(0x304, 0u, 0u);
  apply_channel_setting_00777ae0(0x305, 0u, 0u);
  apply_channel_setting_00777ae0(0x306, 0u, 0u);
  apply_channel_setting_00777ae0(0x24b, 0u, 0u);
  apply_channel_setting_00777ae0(0x23d, 0u, 0u);
  apply_channel_setting_00777ae0(0x24c, 0u, 0u);
  apply_channel_setting_00777ae0(0x24d, 0u, 0u);

  // 00f9c006  POP EDI
  // 00f9c007  POP ESI
  // 00f9c008  POP EBX
  // 00f9c009  RET 0x4
  //
  // The shared epilogue on the fall-through path. It restores the three saved
  // registers and returns past the one argument word. It writes no register that
  // the caller reads as a result: EAX holds the residue of the last indirect
  // dispatch at 0x00f9bf8e, whose own result the body discarded, and which
  // nothing in this body consumed. The declared return type is void because the
  // body computes nothing to return; see the sidecar's
  // validation.return_semantics_decision for how that was reconciled with the
  // canonical ABI record's `unclassified_in_EAX` token.
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00f9bee0
