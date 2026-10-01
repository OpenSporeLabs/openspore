// PKG-SWARM-W1-00EC4280 -- VA 0x00ec4280
// reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280.cpp
//
// Sporepedia online deleting destructor at 0x00ec4280.
// The complete body is 14 instructions / 50 bytes (0x00ec4280..0x00ec42b1),
// transcribed here instruction by instruction. The raw bytes this file is
// transcribed from, re-read from the image for this package, are:
//
//   568bf1c70690904801c746107c904801c746146c904801e8f4de77fff64424
//   0801740956e8d730080083c4048bc65ec20400cccccccccccc
//
// (0xCC padding from 0x00ec42B2 onward is not part of the body and is not
// reproduced.)

#include "sw1_00ec4280_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00ec4280 {

// Default: no hook installed. Declared extern in the header and DEFINED HERE,
// and never mutated by this file -- the model test may point it somewhere else
// for the duration of a test, which is the only supported way to observe or
// override the machine's flag read at 0x00ec429C.
std::uint8_t (*sw1_delete_flag_read_hook)(std::uint8_t incoming) = nullptr;

// ---------------------------------------------------------------------------
// re_00ec4280 -- the reconstruction.
//
// Trace. "ESP = E" below is the entry value of ESP, i.e. the machine stack
// pointer on entry, with E+0 = the return address of the CALLER and E+4 = the
// one ordinary stack argument (a 4-byte slot whose low byte is the only part
// anything reads). ESP is walked linearly through all fourteen instructions,
// each call being settled by that callee's own terminator.
//
//  0x00ec4280  PUSH ESI                        ESP = E-4
//  0x00ec4281  MOV ESI,ECX                     ESI = the receiver. This is the
//                                               R-ALIAS the machine-derived
//                                               receiver record reports: ECX
//                                               is read once and everything
//                                               after this goes through ESI.
//  0x00ec4283  MOV dword ptr [ESI],0x01489090  store 1/3
//  0x00ec4289  MOV dword ptr [ESI+0x10],0x1489
//                07C                            store 2/3
//  0x00ec4290  MOV dword ptr [ESI+0x14],0x1489
//                06C                            store 3/3
//  0x00ec4297  CALL 0x00642190                 nothing is pushed. ECX still
//                                               holds the receiver (no
//                                               instruction between 0x00ec4281
//                                               and here wrote ECX), so this is
//                                               __thiscall with zero stack
//                                               words. The callee ends in a
//                                               bare-RET 4-instruction tail
//                                               target, so it pops nothing:
//                                               ESP = E-4 again.
//  0x00ec429C  TEST byte ptr [ESP+0x8],0x1     [E-4+8] = [E+4] = the argument
//                                               slot's LOW BYTE. Read AFTER
//                                               the call above -- that ordering
//                                               is observable, see the hook.
//  0x00ec42A1  JZ 0x00ec42AC                   jump when bit 0 is CLEAR.
//  0x00ec42A3  PUSH ESI                        ESP = E-8
//  0x00ec42A4  CALL 0x00F47380                 callee ends in a bare C3, so
//                                               ESP = E-8 after it returns.
//  0x00ec42A9  ADD ESP,0x4                     ESP = E-4. cdecl: the body
//                                               drops the word it pushed.
//  0x00ec42AC  MOV EAX,ESI                     the ONE exit, shared by both
//                                               arms of the branch
//  0x00ec42AE  POP ESI                         ESP = E
//  0x00ec42AF  RET 0x4                         pop the return address and the
//                                               one 4-byte argument slot
//
// Frame check, stated directly rather than as an arithmetic identity: ESP is E-4
// after the PUSH, E-4 again after 0x00642190 (it pops nothing), E-8 across the
// free, E-4 after the ADD, and E after the POP. That is the entry value, and
// RET 0x4 then consumes the return address plus the single argument word. The
// frame balances exactly, so there is exactly one ordinary stack argument and no
// hidden second one, and 0x00ec429C's [ESP+0x8] is the argument slot and not
// something the body allocated for itself.
// ---------------------------------------------------------------------------
extern "C" SporepediaOnlineAsset* SW1_00EC4280_THISCALL re_00ec4280(
    SporepediaOnlineAsset* receiver, std::uint8_t delete_flags) {
  // 0x00ec4280 / 0x00ec4281 -- save the incoming ECX in the machine's ESI. In
  // C++ the parameter already lives in a register, so there is nothing to do;
  // the alias is recorded here because it is why no store below has to name the
  // receiver twice and why `receiver` is the value every later line uses.
  //
  // 0x00ec4283 / 0x00ec4289 / 0x00ec4290 -- the three vptr stores, in THIS
  // order (0x00, 0x10, 0x14), with THESE immediates. Order matters to a
  // reviewer: it is the order the listing performs the stores in, and the
  // callee's own body later performs the same three in a different order, which
  // is one of the reasons the states below are transient.
  *word_at(receiver, kVptrDisplacementPrimary) = kVptrPrimary;
  *word_at(receiver, kVptrDisplacementSecondary) = kVptrSecondary;
  *word_at(receiver, kVptrDisplacementTertiary) = kVptrTertiary;

  // 0x00ec4297 -- CALL 0x00642190 with the receiver in ECX and nothing pushed.
  // The receiver is passed positionally; the __thiscall attribute puts it in
  // ECX, which is exactly the register it was already in at 0x00ec4297.
  sporepedia_asset_destroy_00642190(receiver);

  // 0x00ec429C / 0x00ec42A1 -- TEST the caller's flag byte against 0x01 and
  // branch when it is CLEAR. The read is a BYTE read of a 4-byte slot.
  //
  // The read is placed here, AFTER the call, because that is where the machine
  // puts it. If a hook is installed it is consulted at this point so the test can
  // observe the ordering and the post-call value; with no hook the parameter is
  // used, which is the ordinary path and the one the reconstruction is about.
  const std::uint8_t observed_flags =
      (sw1_delete_flag_read_hook != nullptr) ? sw1_delete_flag_read_hook(delete_flags)
                                             : delete_flags;

  // 0x00ec42A3 / 0x00ec42A4 / 0x00ec42A9 -- free the receiver itself, not a
  // subobject of it and not the receiver's first word. PUSH ESI is PUSH of the
  // receiver; the callee reads it back at its own [ESP+0x4].
  if ((observed_flags & kDeleteFlagMask) != 0) {  // 0x00ec42A1 is JZ
    deallocate_00f47380(receiver);
  }

  // 0x00ec42AC / 0x00ec42AE / 0x00ec42AF -- EAX = ESI = the receiver, restore
  // the saved ESI, and return popping the one argument word. The single exit is
  // shared by both arms, so the return value does NOT depend on the branch.
  return receiver;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ec4280
