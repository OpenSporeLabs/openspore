// PKG-DFW-0067DC80 -- VA 0x0067dc80
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 11 instructions, body 0x0067dc80..0x0067dc9d inclusive
// (Ghidra body_end 0x0067dc9d, body_span_bytes 30; the final instruction
// `RET 0x4` occupies 0x0067dc9b..0x0067dc9d, and the two `CC` bytes at
// 0x0067dc9e are inter-function padding outside the body). Raw bytes read
// from the image: 56 8bf1 e888feffff f644240801 7409 56 e8eb968c00 83c404
// 8bc6 5e c20400.
//
//   0067dc80  PUSH ESI
//   0067dc81  MOV ESI,ECX                  the receiver alias; ECX left intact
//   0067dc83  CALL 0x0067db10              first direct transfer, unconditional
//   0067dc88  TEST byte ptr [ESP + 0x8],0x1   bit 0 of the one stack argument
//   0067dc8d  JZ 0x0067dc98                -> the shared tail
//   0067dc8f  PUSH ESI                     the word handed to the release
//   0067dc90  CALL 0x00f47380              second direct transfer, conditional
//   0067dc95  ADD ESP,0x4                  discards the pushed word (cdecl)
//   0067dc98  MOV EAX,ESI                  both paths return the receiver
//   0067dc9a  POP ESI
//   0067dc9b  RET 0x4                      callee pops the one dword argument
//
// The frame arithmetic at 0x0067dc88, since the displacement is the one thing in
// this body a reader cannot take on trust. On entry ESP points at the return
// address and the single dword argument is at ESP+4. PUSH ESI at 0x0067dc80 puts
// the saved register at ESP+0 and the return address at ESP+4. The CALL at
// 0x0067dc83 puts its return address at ESP+0, so the saved register is at
// ESP+4 and the argument is at ESP+8. The CALL has returned by the time the TEST
// runs, so the argument is back at ESP+8. The tested word is the argument and not
// the saved register or the return address, and it is read at its LOW BYTE only --
// the encoding is `f6 44 24 08 01`, a `TEST r/m8, imm8`.
//
// ABI, machine-derived and corroborated by the two callees' own listings: the
// receiver is in ECX, the body has exactly one ordinary stack argument of 4 bytes,
// the callee owns that cleanup (`RET 0x4`, and no `ADD ESP,4` of its own anywhere
// in the body outside the release block), EAX is the return register and carries
// the receiver, and ESI is the only callee-saved register the body disturbs.
//
// Both transfers are direct immediates. abi_derived.dispatch records
// indirect_calls=0 and call_offsets=[] and the listing contains no register- or
// memory-operand transfer, so this file declares no slot, no dispatch table and
// no index anywhere. The one indirect call in the neighbourhood is inside the
// FIRST CALLEE at 0x0067db9b, and it belongs to that body, not to this one.
//
// The receiver is never dereferenced here. There is no memory operand in this
// body other than the stack slot the TEST reads, so this package declares no
// member, no field and no displacement of the receiver, and the port types in the
// header are `void` for that reason alone.
//
// On the name: the canonical record names this body `App::IMessageManager::Get`,
// and the function symbol below carries that name plus the target address so the
// validator can bind the span. The machine does not corroborate the word "Get",
// and this reconstruction does not assert it. What the image does state is
// visible in three places and is recorded in the sidecar: the dword at vtable
// 0x01401798+0 is 0x0067dc80, so this body is the first virtual entry of the
// object whose destructor is 0x0067db10; that same destructor stores 0x1401798
// into [ESI] at 0x0067db2d and then a different vtable, 0x13f3a68, into [ESI] at
// 0x0067dba1; and this body returns its own receiver, and releases that same
// receiver when bit 0 of its single argument is set. That is a scalar deleting
// destructor shape. "Get" is carried as the record's label and flagged, not
// believed; a live search of the bridge for the substring `IMessageManager`
// returns exactly one function, this one, so there is no sibling symbol to
// cross-check the label against.

#include "dfw_0067dc80_types.hpp"

namespace openspore::reconstruction::pkg_dfw_0067dc80 {

extern "C" void* PKG_DFW_0067DC80_THISCALL
App_IMessageManager_Get_0067dc80(OpaqueMessageManagerBlock *receiver,
                                 Word deletingDestructorFlag) {
  // 0067dc80  PUSH ESI
  // 0067dc81  MOV ESI,ECX
  //
  // The incoming ESI is saved and the receiver is aliased. The alias exists
  // because the body needs the receiver to survive across both calls while ECX
  // is free to be a scratch register -- it is a register save, not a copy of
  // anything. ECX is not written between 0x0067dc81 and the CALL below, so the
  // receiver reaches the first callee in ECX with nothing pushed.
  OpaqueMessageManagerBlock *const receiverAlias = receiver;

  // 0067dc83  CALL 0x0067db10
  //
  // The first direct transfer, and it is unconditional: the listing places it
  // before the argument is even read, so it runs for every value of the flag.
  // Nothing is pushed, so the callee's zero-argument thiscall leaves the stack
  // exactly as it found it and the `ADD ESP,0x4` further down still has only the
  // one word this body pushed itself to account for.
  imessage_manager_complete_dtor_0067db10(receiverAlias);

  // 0067dc88  TEST byte ptr [ESP + 0x8],0x1
  // 0067dc8d  JZ 0x0067dc98
  //
  // One byte of the one argument, masked with 1. The other 31 bits are never
  // looked at by this body, so the test is a bit-0 test and not a
  // zero-or-nonzero test of the whole word. The branch target is inside the body
  // and is the shared tail, so a clear bit 0 skips the release and nothing else:
  // the EAX materialisation, the register restore and the epilogue all still run.
  if ((deletingDestructorFlag & 1u) != 0u) {
    // 0067dc8f  PUSH ESI
    // 0067dc90  CALL 0x00f47380
    // 0067dc95  ADD ESP,0x4
    //
    // The pushed word is the receiver alias itself, not an offset from it: the
    // machine has no base adjustment anywhere in this body, and the one
    // instruction that could have formed an address, SUB, is absent from the
    // listing. The callee is cdecl and ends in a bare RET, so the ADD ESP is the
    // caller's half of a one-argument call and belongs to this body.
    imessage_manager_global_release_00f47380(receiverAlias);
  }

  // 0067dc98  MOV EAX,ESI
  // 0067dc9a  POP ESI
  // 0067dc9b  RET 0x4
  //
  // EAX is materialised from ESI on BOTH paths, so the receiver is returned
  // whether or not the release ran, and it is returned unchanged by the release:
  // nothing between the CALL at 0x0067dc90 and this MOV stores into the alias.
  // The record types the return as `void*`; the machine shows the receiver's own
  // dword in EAX, which is what `void*` names and no more.
  return receiverAlias;
}

}  // namespace openspore::reconstruction::pkg_dfw_0067dc80
